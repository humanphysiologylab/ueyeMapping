/*!
 * \file    tabprocessing.cpp
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   properties tab widget for camera imageprocessing
 *
 * \par Revision history
 * \li 05.02.2010 - created
 * \li 27.07.2010 - changed some slotnames and connect them manually cause of
 *                  problems with auto signal-slot connection by name
 * \li 31.05.2011 - removed connection to missing slot changedTestImage().
 */

#include "properties.h"
#include <QDebug>

void properties::initTabProcessing()
{
    // setup Testimages
    int nSupportedImages = 0;
    is_GetSupportedTestImages (m_hCamera, &nSupportedImages);
    populateTestImages (nSupportedImages);

    // create WB finished
    m_pEvWB = new EventThread;
    connect (m_pEvWB, SIGNAL(eventhappen(int)), this, SLOT(eventreceived(int)));
    m_pEvWB->start (m_hCamera, IS_SET_EVENT_WB_FINISHED);

    // connect testimage change
    connect (pB_SetTestImage, SIGNAL(clicked()), this, SLOT(OnActivateTestImage()));
    connect (cb_testimages, SIGNAL(currentIndexChanged(int)), this, SLOT(OnChangedTestImage(int)));
    connect (slider_testimagesValue, SIGNAL(valueChanged(int)), spin_testimagesValue, SLOT(setValue(int)));
    connect (spin_testimagesValue, SIGNAL(valueChanged(int)), slider_testimagesValue, SLOT(setValue(int)));

    // connect color correction
    connect (radioButtonCCOff, SIGNAL(clicked()), this, SLOT(OnRadioColorCorrection_clicked()));
    connect (radioButtonCCNormal, SIGNAL(clicked()), this, SLOT(OnRadioColorCorrection_clicked()));
    connect (radioButtonCCBG40, SIGNAL(clicked()), this, SLOT(OnRadioColorCorrection_clicked()));
    connect (radioButtonCCHQ, SIGNAL(clicked()), this, SLOT(OnRadioColorCorrection_clicked()));

    // connect white balance
    connect (radioButtonOneShot, SIGNAL(clicked()), this, SLOT(OnRadioWhiteBalance()));
    connect (radioButtonAuto, SIGNAL(clicked()), this, SLOT(OnRadioWhiteBalance()));
    connect (radioButtonDisabled, SIGNAL(clicked()), this, SLOT(OnRadioWhiteBalance()));

    // Init testimage
    OnChangedTestImage(0);
}

void properties::UpdateColorCtrls ()
{
    if (m_bInit || !m_hCamera)
        return;

    buttonGroupColorCorrection->setEnabled (IS_COLORMODE_MONOCHROME != m_SensorInfo.nColorMode);

    INT supportedModes = is_SetColorCorrection (m_hCamera, IS_GET_SUPPORTED_CCOR_MODE, 0);
    radioButtonCCNormal->setEnabled (supportedModes & IS_CCOR_ENABLE_NORMAL);
    radioButtonCCBG40->setEnabled (supportedModes & IS_CCOR_ENABLE_BG40_ENHANCED);
    radioButtonCCHQ->setEnabled (supportedModes & IS_CCOR_ENABLE_HQ_ENHANCED);

    INT colorCorrection = 0;
    colorCorrection = is_SetColorCorrection (m_hCamera, IS_GET_CCOR_MODE, 0) & IS_CCOR_ENABLE_MASK;

    switch (colorCorrection)
    {
    case IS_CCOR_ENABLE_NORMAL:
        radioButtonCCNormal->setChecked(true);
        break;
    case IS_CCOR_ENABLE_BG40_ENHANCED:
        radioButtonCCBG40->setChecked(true);
        break;
    case IS_CCOR_ENABLE_HQ_ENHANCED:
        radioButtonCCHQ->setChecked(true);
        break;
    case IS_CCOR_DISABLE:
    default:
        radioButtonOff->setChecked(true);
        break;
    }
}

void properties::OnRadioColorCorrection_clicked ()
{
    if (m_bInit || !m_hCamera)
        return;

    INT colorCorrection = 0;

    if (radioButtonCCNormal->isChecked())
    {
        colorCorrection = IS_CCOR_ENABLE_NORMAL;
    }
    if (radioButtonCCBG40->isChecked())
    {
        colorCorrection = IS_CCOR_ENABLE_BG40_ENHANCED;
    }
    if (radioButtonCCHQ->isChecked())
    {
        colorCorrection = IS_CCOR_ENABLE_HQ_ENHANCED;
    }
    if (radioButtonCCOff->isChecked())
    {
        colorCorrection = IS_CCOR_DISABLE;
    }

    if (IS_SUCCESS != is_SetColorCorrection (m_hCamera, colorCorrection, 0))
    {
        UpdateColorCtrls ();
    }
}

void properties::UpdateWBCtrls ()
{
    if (m_bInit || !m_hCamera)
        return;

    int ret = IS_NO_SUCCESS;
    UEYE_AUTO_INFO aInfo;
    is_GetAutoInfo (m_hCamera, &aInfo);

    buttonGroupWhitebalance->setEnabled (AC_WHITEBAL & aInfo.AutoAbility);

    double dblAutoWb = 0.0;
    if ((ret = is_SetAutoParameter (m_hCamera, IS_GET_ENABLE_AUTO_WHITEBALANCE, &dblAutoWb, NULL)) == IS_SUCCESS)
    {
        if (1 == (INT) (dblAutoWb))
        {
            is_SetAutoParameter (m_hCamera, IS_GET_AUTO_WB_ONCE, &dblAutoWb, NULL);
            if (1 == (INT)dblAutoWb)
            {
                radioButtonOneShot->setChecked(true);
            }
            else
            {
                radioButtonAuto->setChecked(true);
            }
        }
        else
        {
            radioButtonDisabled->setChecked(true); //IS_SET_WB_DISABLE
        }
    }
    else
    {
        qDebug("error - SetAutoParameter: err %d", ret);
    }
}

void properties::OnRadioWhiteBalance ()
{
    double dblAutoWb = 0.0;

    if (radioButtonAuto->isChecked())
    {
        dblAutoWb = 0.0;
        is_SetAutoParameter (m_hCamera, IS_SET_AUTO_WB_ONCE, &dblAutoWb, NULL);

        dblAutoWb = 1.0;
        is_SetAutoParameter (m_hCamera, IS_SET_ENABLE_AUTO_WHITEBALANCE, &dblAutoWb, NULL);
    }
    if (radioButtonOneShot->isChecked())
    {
        dblAutoWb = 1.0;
        is_SetAutoParameter (m_hCamera, IS_SET_AUTO_WB_ONCE, &dblAutoWb, NULL);
        is_SetAutoParameter (m_hCamera, IS_SET_ENABLE_AUTO_WHITEBALANCE, &dblAutoWb, NULL);
    }
    if (radioButtonDisabled->isChecked())
    {
        dblAutoWb = 0.0;
        is_SetAutoParameter (m_hCamera, IS_SET_AUTO_WB_ONCE, &dblAutoWb, NULL);
        is_SetAutoParameter (m_hCamera, IS_SET_ENABLE_AUTO_WHITEBALANCE, &dblAutoWb, NULL);
    }
}

void properties::populateTestImages (int images)
{
    unsigned int i = 1, n = 1;
    bool bAdd = true;
    cb_testimages->addItem (GetTestImageName (0), 0);
    do
    {
        bAdd = true;
        // check color images with mono sensors
        if ( ((n==IS_TEST_IMAGE_ANIMATED_WEDGE_COLOR)||(n==IS_TEST_IMAGE_WEDGE_COLOR))
                && (m_SensorInfo.nColorMode != IS_COLORMODE_BAYER))
        {
            bAdd = false;
        }
        if ((images & n ) && bAdd)
        {
            cb_testimages->addItem (GetTestImageName (n), n);
        }
        n = (1 << i);
        i++;
    }
    while (n < 0x80000000);
}

void properties::OnActivateTestImage ()
{
    int curIndex = cb_testimages->currentIndex ();//itemData(index).toInt();
    int testimage = cb_testimages->itemData (curIndex).toInt ();
    int testparam = 0;
    testparam = spin_testimagesValue->value();

    qDebug("set Sensor testimage %d [param %d]", testimage, testparam);
    is_SetSensorTestImage (m_hCamera, testimage, testparam);
}

void properties::OnChangedTestImage (int curIndex)
{
    int testimage = cb_testimages->itemData (curIndex).toInt ();

    int testparam1, testparam2;
    int nRet = is_GetTestImageValueRange (m_hCamera, testimage, &testparam1, &testparam2);

    if (nRet != IS_SUCCESS)
    {
        label_testimagesAdditionalParam->setVisible(false);
        slider_testimagesValue->setVisible(false);
        spin_testimagesValue->setVisible(false);
        label_testimages_min->setVisible(false);
        label_testimages_max->setVisible(false);

        spin_testimagesValue->setValue(0);

        label_testimages_min->setText (QString::number (0));
        label_testimages_max->setText (QString::number (0));
    }
    else
    {
        label_testimagesAdditionalParam->setVisible(true);
        slider_testimagesValue->setVisible(true);
        spin_testimagesValue->setVisible(true);
        label_testimages_min->setVisible(true);
        label_testimages_max->setVisible(true);

        slider_testimagesValue->setRange (testparam1, testparam2);
        spin_testimagesValue->setRange (testparam1, testparam2);

        label_testimages_min->setText (QString::number (testparam1));
        label_testimages_max->setText (QString::number (testparam2));
    }

    qDebug() << GetTestImageName(testimage) << " " << testparam1 << " " << testparam2;
}

QString properties::GetTestImageName (int testimage)
{
    switch (testimage)
    {
    default:
    case IS_TEST_IMAGE_NONE:
        return "TEST_IMAGE_NONE";
    case IS_TEST_IMAGE_WHITE:
        return "TEST_IMAGE_WHITE";
    case IS_TEST_IMAGE_BLACK:
        return "TEST_IMAGE_BLACK";
    case IS_TEST_IMAGE_HORIZONTAL_GREYSCALE:
        return "TEST_IMAGE_HORIZONTAL_GREYSCALE";
    case IS_TEST_IMAGE_VERTICAL_GREYSCALE:
        return "TEST_IMAGE_VERTICAL_GREYSCALE";
    case IS_TEST_IMAGE_DIAGONAL_GREYSCALE:
        return "TEST_IMAGE_DIAGONAL_GREYSCALE";
    case IS_TEST_IMAGE_WEDGE_GRAY:
        return "TEST_IMAGE_WEDGE_GRAY";
    case IS_TEST_IMAGE_WEDGE_COLOR:
        return "TEST_IMAGE_WEDGE_COLOR";
    case IS_TEST_IMAGE_ANIMATED_WEDGE_GRAY:
        return "TEST_IMAGE_ANIMATED_WEDGE_GRAY";

    case IS_TEST_IMAGE_ANIMATED_WEDGE_COLOR:
        return "TEST_IMAGE_ANIMATED_WEDGE_COLOR";
    case IS_TEST_IMAGE_MONO_BARS:
        return "TEST_IMAGE_MONO_BARS";
    case IS_TEST_IMAGE_COLOR_BARS1:
        return "TEST_IMAGE_COLOR_BARS1";
    case IS_TEST_IMAGE_COLOR_BARS2:
        return "TEST_IMAGE_COLOR_BARS2";
    case IS_TEST_IMAGE_GREYSCALE1:
        return "TEST_IMAGE_GREYSCALE1";
    case IS_TEST_IMAGE_GREY_AND_COLOR_BARS:
        return "TEST_IMAGE_GREY_AND_COLOR_BARS";
    case IS_TEST_IMAGE_MOVING_GREY_AND_COLOR_BARS:
        return "TEST_IMAGE_MOVING_GREY_AND_COLOR_BARS";
    case IS_TEST_IMAGE_ANIMATED_LINE:
        return "TEST_IMAGE_ANIMATED_LINE";

    case IS_TEST_IMAGE_ALTERNATE_PATTERN:
        return "TEST_IMAGE_ALTERNATE_PATTER";
    case IS_TEST_IMAGE_VARIABLE_GREY:
        return "TEST_IMAGE_VARIABLE_GREY";
    case IS_TEST_IMAGE_MONOCHROME_HORIZONTAL_BARS:
        return "TEST_IMAGE_MONOCHROME_HORIZONTAL_BARS";
    case IS_TEST_IMAGE_MONOCHROME_VERTICAL_BARS:
        return "TEST_IMAGE_MONOCHROME_VERTICAL_BARS";
    case IS_TEST_IMAGE_CURSOR_H:
        return "TEST_IMAGE_CURSOR_H";
    case IS_TEST_IMAGE_CURSOR_V:
        return "TEST_IMAGE_CURSOR_V";
    case IS_TEST_IMAGE_COLDPIXEL_GRID:
        return "TEST_IMAGE_COLDPIXEL_GRID";
    case IS_TEST_IMAGE_HOTPIXEL_GRID:
        return "TEST_IMAGE_HOTPIXEL_GRID";

    case IS_TEST_IMAGE_VARIABLE_RED_PART:
        return "TEST_IMAGE_VARIABLE_RED_PART";
    case IS_TEST_IMAGE_VARIABLE_GREEN_PART:
        return "TEST_IMAGE_VARIABLE_GREEN_PART";
    case IS_TEST_IMAGE_VARIABLE_BLUE_PART:
        return "TEST_IMAGE_VARIABLE_BLUE_PART";
    case IS_TEST_IMAGE_SHADING_IMAGE:
        return "TEST_IMAGE_SHADING_IMAGE";
    case IS_TEST_IMAGE_WEDGE_GRAY_SENSOR:
        return "TEST_IMAGE_WEDGE_GRAY";
    case IS_TEST_IMAGE_ANIMATED_WEDGE_GRAY_SENSOR:
        return "TEST_IMAGE_ANIMATED_WEDGE_GRAY";
    case IS_TEST_IMAGE_RAMPING_PATTERN:
        return "TEST_IMAGE_RAMPING_PATTERN";
    }
}

