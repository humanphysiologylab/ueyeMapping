/*!
 * \file    tabformat.cpp
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   properties tab widget for color formats
 *
 * \par Revision history
 * \li  13.01.2010 - created
 * \li  04.02.2010 - SetupCapture don't start/stop the live capture anymore to avoid problems with
 *                   the live button status
 * \li  11.02.2010 - Add explicit braces to avoid ambigous 'else' (g++ 4.4.1 warning)
 * \li  08.11.2012 - Update to new color mode defines
 * \li  28.05.2013 - Update to JPEG color conv mode 
 * \li  08.01.2014 - Include uEye.h instead of ueye.h (for consistency with other files)
 * \li  28.01.2014 - Added jpeg (for xs) format handling in EnableSupportedColorFormats()
 *                 - Fixed RestoreColorModeSettings() to set default color mode for xs
 */

#include "properties.h"

#include <ueye.h>


void properties::initTabFormat()
{
    QString strTemp;

    if (IS_COLORMODE_BAYER == m_SensorInfo.nColorMode)
    {
        m_bColor = true;
        strTemp = "Direct raw bayer";
    }
    else if (IS_COLORMODE_CBYCRY == m_SensorInfo.nColorMode)
    {
        if (m_SensorInfo.SensorID == IS_SENSOR_XS)
        {
            m_bJPEG = true;
        }

        strTemp = "Direct raw data";
        //hide debayering quality names
        label_debayering->hide();
        label_sw3x3->hide();
        label_sw5x5->hide();
        label_hw3x3->hide();
        // hide 5x5 buttons, cause not needed for mono cameras
        DoNotShow5x5();
    }
    else
    {
        m_bColor = false;
        strTemp = "Direct raw data";
        //hide debayering quality names
        label_debayering->hide();
        label_sw3x3->hide();
        label_sw5x5->hide();
        label_hw3x3->hide();
        // hide 5x5 buttons, cause not needed for mono cameras
        DoNotShow5x5();
    }
    createRadioButtonGroup();
    DisableColorFormats();

    label_raw_bayer8->setText(strTemp + " (Y8)");

    rb_display_dib->setChecked(true);
    //rb_display_opengl->setEnabled(false);
    label_camera_bandwith->setText("");
    label_camera->setText("");

    connect (chkOpenMP_Enable, SIGNAL(stateChanged(int)), this, SLOT(OnOpenMP_Enable(int)));

    //rb_display_opengl
    UpdateTabFormat();
}

void properties::DoNotShow5x5()
{
    rb_raw_bayer8_5x5->hide();
    rb_grey8_5x5->hide();
    rb_rgb16_5x5->hide();
    rb_rgb24_5x5->hide();
    rb_rgb32_5x5->hide();
}
/*! \brief creates a unique button ID with color fomrat infos in a WORD
 * \note works only with IS_CM_FORMAT_PACKET formats, cause PLANAR uses also the upper 8bits
 */
#define CREATE_ID(_l_,_h_)  ((_l_)|((_h_)<<8))
#define COLORMODE_FROM_ID(_id_)  ((_id_) & 0xFF)
#define COLORCONV_FROM_ID(_id_) (((_id_)>>8) & 0xFF)

void properties::createRadioButtonGroup()
{
    // create a buttongroup for the color format radiobuttons
    int convSoftNormal = IS_CONV_MODE_SOFTWARE;
    if (m_bColor)
    {
        convSoftNormal = IS_CONV_MODE_SOFTWARE_3X3;
    }

    pbgColorFormat = new QButtonGroup;

    pbgColorFormat->addButton(rb_raw_bayer8_3x3, CREATE_ID(IS_CM_SENSOR_RAW8, convSoftNormal));
    pbgColorFormat->addButton(rb_grey8_3x3, CREATE_ID(IS_CM_MONO8, convSoftNormal));
    pbgColorFormat->addButton(rb_rgb16_3x3, CREATE_ID(IS_CM_BGR565_PACKED, convSoftNormal));
    pbgColorFormat->addButton(rb_rgb24_3x3, CREATE_ID(IS_CM_BGR8_PACKED, convSoftNormal));
    pbgColorFormat->addButton(rb_rgb32_3x3, CREATE_ID(IS_CM_BGRA8_PACKED, convSoftNormal));

    pbgColorFormat->addButton(rb_raw_bayer8_5x5, CREATE_ID(IS_CM_SENSOR_RAW8, IS_CONV_MODE_SOFTWARE_5X5));
    pbgColorFormat->addButton(rb_grey8_5x5, CREATE_ID(IS_CM_MONO8, IS_CONV_MODE_SOFTWARE_5X5));
    pbgColorFormat->addButton(rb_rgb16_5x5, CREATE_ID(IS_CM_BGR565_PACKED, IS_CONV_MODE_SOFTWARE_5X5));
    pbgColorFormat->addButton(rb_rgb24_5x5, CREATE_ID(IS_CM_BGR8_PACKED, IS_CONV_MODE_SOFTWARE_5X5));
    pbgColorFormat->addButton(rb_rgb32_5x5, CREATE_ID(IS_CM_BGRA8_PACKED, IS_CONV_MODE_SOFTWARE_5X5));

    pbgColorFormat->addButton(rb_raw_bayer8_hw, CREATE_ID(IS_CM_SENSOR_RAW8, IS_CONV_MODE_HARDWARE_3X3));
    pbgColorFormat->addButton(rb_grey8_hw, CREATE_ID(IS_CM_MONO8, IS_CONV_MODE_HARDWARE_3X3));
    pbgColorFormat->addButton(rb_rgb16_hw, CREATE_ID(IS_CM_BGR565_PACKED, IS_CONV_MODE_HARDWARE_3X3));
    pbgColorFormat->addButton(rb_rgb24_hw, CREATE_ID(IS_CM_MONO12, IS_CONV_MODE_HARDWARE_3X3));
    pbgColorFormat->addButton(rb_rgb32_hw, CREATE_ID(IS_CM_MONO10, IS_CONV_MODE_HARDWARE_3X3));

    connect (pbgColorFormat, SIGNAL(buttonClicked(int)), this, SLOT(OnClickedColormode(int)));
}

void properties::DisableColorFormats()
{
    rb_raw_bayer8_3x3->setEnabled(false);
    rb_grey8_3x3->setEnabled(false);
    rb_rgb16_3x3->setEnabled(false);
    rb_rgb24_3x3->setEnabled(false);
    rb_rgb32_3x3->setEnabled(false);

    rb_raw_bayer8_5x5->setEnabled(false);
    rb_grey8_5x5->setEnabled(false);
    rb_rgb16_5x5->setEnabled(false);
    rb_rgb24_5x5->setEnabled(false);
    rb_rgb32_5x5->setEnabled(false);

    rb_raw_bayer8_hw->setEnabled(false);
    rb_grey8_hw->setEnabled(false);
    rb_rgb16_hw->setEnabled(false);
    rb_rgb24_hw->setEnabled(false);
    rb_rgb32_hw->setEnabled(false);
    // connect clicked signal for buttongroup
}

bool properties::CheckColorFormat(UINT ColorFormat, UINT ConvertType)
{
    bool ret = false;

    INT CurrentConvertMode, DefaultConvertMode, SupportedConvertModes;

    if (is_GetColorConverter (m_hCamera, ColorFormat, &CurrentConvertMode, &DefaultConvertMode, &SupportedConvertModes)
            == IS_SUCCESS)
    {
        if ((SupportedConvertModes & ConvertType) != 0)
        {
            ret = true;
        }
    }
    return ret;
}

void properties::EnableSupportedColorFormats ()
{
    // Check all supported color formats and enable/disable the corresponding controls

    if (m_bJPEG)
    {
        /* Enable Color modes for XS in JPEG Mode */
        if (CheckColorFormat (IS_CM_SENSOR_RAW8, IS_CONV_MODE_JPEG))
        {
            rb_raw_bayer8_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_SENSOR_RAW8, IS_CONV_MODE_JPEG))
        {
            rb_raw_bayer8_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_MONO8, IS_CONV_MODE_JPEG))
        {
            rb_grey8_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_RGBA8_PACKED, IS_CONV_MODE_JPEG))
        {
            rb_rgb32_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_BGRA8_PACKED, IS_CONV_MODE_JPEG))
        {
            rb_rgb32_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_RGB8_PACKED, IS_CONV_MODE_JPEG))
        {
            rb_rgb24_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_BGR8_PACKED, IS_CONV_MODE_JPEG))
        {
            rb_rgb24_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_BGR565_PACKED, IS_CONV_MODE_JPEG))
        {
            rb_rgb16_3x3->setEnabled(true);
        }
    }
    else
    {
        // For mono cameras
        if (CheckColorFormat (IS_CM_SENSOR_RAW8, IS_CONV_MODE_SOFTWARE))
        {
            rb_raw_bayer8_3x3->setEnabled(true);
        }

        // For color cameras
        if (CheckColorFormat (IS_CM_SENSOR_RAW8, IS_CONV_MODE_SOFTWARE_3X3))
        {
            rb_raw_bayer8_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_SENSOR_RAW8, IS_CONV_MODE_SOFTWARE_5X5))
        {
            rb_raw_bayer8_5x5->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_SENSOR_RAW8, IS_CONV_MODE_HARDWARE_3X3))
        {
            rb_raw_bayer8_hw->setEnabled(true);
        }

        // For mono cameras
        if (CheckColorFormat (IS_CM_MONO8, IS_CONV_MODE_SOFTWARE))
        {
            rb_grey8_3x3->setEnabled(true);
        }

        // For color cameras
        if (CheckColorFormat (IS_CM_MONO8, IS_CONV_MODE_SOFTWARE_3X3))
        {
            rb_grey8_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_MONO8, IS_CONV_MODE_SOFTWARE_5X5))
        {
            rb_grey8_5x5->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_MONO8, IS_CONV_MODE_HARDWARE_3X3))
        {
            rb_grey8_hw->setEnabled(true);
        }

        // For mono cameras
        if (CheckColorFormat (IS_CM_RGBA8_PACKED, IS_CONV_MODE_SOFTWARE))
        {
            rb_rgb32_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_BGRA8_PACKED, IS_CONV_MODE_SOFTWARE))
        {
            rb_rgb32_3x3->setEnabled(true);
        }

        // For color cameras
        if (CheckColorFormat (IS_CM_RGBA8_PACKED, IS_CONV_MODE_SOFTWARE_3X3))
        {
            rb_rgb32_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_BGRA8_PACKED, IS_CONV_MODE_SOFTWARE_3X3))
        {
            rb_rgb32_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_RGBA8_PACKED, IS_CONV_MODE_SOFTWARE_5X5))
        {
            rb_rgb32_5x5->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_RGBA8_PACKED, IS_CONV_MODE_HARDWARE_3X3))
        {
            rb_rgb32_hw->setEnabled(true);
        }

        // For mono cameras
        if (CheckColorFormat (IS_CM_RGB8_PACKED, IS_CONV_MODE_SOFTWARE))
        {
            rb_rgb24_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_BGR8_PACKED, IS_CONV_MODE_SOFTWARE))
        {
            rb_rgb24_3x3->setEnabled(true);
        }

        // For color cameras
        if (CheckColorFormat (IS_CM_RGB8_PACKED, IS_CONV_MODE_SOFTWARE_3X3))
        {
            rb_rgb24_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_BGRA8_PACKED, IS_CONV_MODE_SOFTWARE_3X3))
        {
            rb_rgb24_3x3->setEnabled(true);
        }

        if(CheckColorFormat (IS_CM_RGB8_PACKED, IS_CONV_MODE_SOFTWARE_5X5))
        {
            rb_rgb24_5x5->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_RGB8_PACKED, IS_CONV_MODE_HARDWARE_3X3))
        {
            rb_rgb24_hw->setEnabled(true);
        }

        // For mono cameras
        if (CheckColorFormat (IS_CM_BGR565_PACKED, IS_CONV_MODE_SOFTWARE))
        {
            rb_rgb16_3x3->setEnabled(true);
        }

        // For color cameras
        if (CheckColorFormat (IS_CM_BGR565_PACKED, IS_CONV_MODE_SOFTWARE_3X3))
        {
            rb_rgb16_3x3->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_BGR565_PACKED, IS_CONV_MODE_SOFTWARE_5X5))
        {
            rb_rgb16_5x5->setEnabled(true);
        }

        if (CheckColorFormat (IS_CM_BGR565_PACKED, IS_CONV_MODE_HARDWARE_3X3))
        {
            rb_rgb16_hw->setEnabled(true);
        }
    }

}

void properties::OnClickedColormode(int buttonId)
{
    if (m_bInit || !m_hCamera)
    {
        return;
    }
    if (m_bLive)
    {
        is_StopLiveVideo(m_hCamera, IS_WAIT);
    }
    int colormode = COLORMODE_FROM_ID(buttonId);
    qDebug("clicked colormode: %d", colormode);
    int colorconverter = COLORCONV_FROM_ID(buttonId);
    if(m_bJPEG)
    {
        colorconverter = IS_CONV_MODE_JPEG;
    }
    qDebug("clicked colorconverter: %d", colorconverter);

    int ret;

    ret = is_SetColorConverter(m_hCamera, colormode, colorconverter);
    if (ret != IS_SUCCESS)
    {
        qDebug("error is_SetColorConverter: %d", ret);
    }

    ret = is_SetColorMode(m_hCamera, colormode);
    if (ret != IS_SUCCESS)
    {
        qDebug("error is_SetColorMode: %d", ret);
    }

    m_pDlgMainView->SetupCapture();

    if (m_bLive)
    {
        is_CaptureVideo(m_hCamera, IS_DONT_WAIT);
    }
}

void properties::SetJPEGMode(bool bEnable)
{
    // Get Color mode
    int nColorMode = is_SetColorMode(m_hCamera, IS_GET_COLOR_MODE);

    // Get convert mode
    int nCurrentConvertMode, nDefaultConvertMode, nSupportedConvertModes = 0;
    is_GetColorConverter(m_hCamera, nColorMode, &nCurrentConvertMode, &nDefaultConvertMode, &nSupportedConvertModes);

    int colorconverter = IS_CONV_MODE_SOFTWARE;
    m_bJPEG = bEnable;

    OnClickedColormode(CREATE_ID(nColorMode, colorconverter));
}

void properties::RestoreColorModeSettings()
{
    if (m_bJPEG)
    {
        /* restore XS default color mode */
        OnClickedColormode(CREATE_ID(IS_CM_BGRA8_PACKED, IS_CONV_MODE_SOFTWARE));
    }
    else if(m_bColor)
    {
    	OnClickedColormode(CREATE_ID(IS_CM_BGRA8_PACKED, IS_CONV_MODE_SOFTWARE_3X3));
    }
    else
    {
    	OnClickedColormode(CREATE_ID(IS_CM_MONO8, IS_CONV_MODE_SOFTWARE));
    }
}

void properties::OnOpenMP_Enable(int iNewState)
{
    if (m_bInit || m_hCamera == 0)
    {
        return;
    }

    UINT nEnabled = iNewState == Qt::Checked ? IS_CONFIG_OPEN_MP_ENABLE : IS_CONFIG_OPEN_MP_DISABLE;

    INT nRet = is_Configuration(IS_CONFIG_OPEN_MP_CMD_SET_ENABLE, &nEnabled, sizeof(UINT));
    if (nRet != IS_SUCCESS)
    {
        qDebug("error: is_Configuration(SET_ENABLE, %d) failed with code %d!", nEnabled, nRet);
        UpdateTabFormat();
    }
    else
    {
        qDebug("Successfully set OpenMP enabled state to %d.", nEnabled);
    }
}

void properties::UpdateTabFormat()
{
    // Get Color mode
    int nColorMode = is_SetColorMode(m_hCamera, IS_GET_COLOR_MODE);

    // Get convert mode
    int nCurrentConvertMode, nDefaultConvertMode, nSupportedConvertModes = 0;
    INT nRet = is_GetColorConverter(m_hCamera, nColorMode, &nCurrentConvertMode, &nDefaultConvertMode, &nSupportedConvertModes);

	createRadioButtonGroup();

    if(m_bJPEG)
    {
        nCurrentConvertMode = IS_CONV_MODE_SOFTWARE;
    }

    if (nRet == IS_SUCCESS)
    {
        // If no Direct3D (DIB mode)
        if (!(is_SetDisplayMode(m_hCamera, IS_GET_DISPLAY_MODE) & IS_SET_DM_DIRECT3D))
        {
            // Enable the color format controls
            EnableSupportedColorFormats();

            // set the colormode radio button
            int buttonid = CREATE_ID(nColorMode, nCurrentConvertMode);
            QAbstractButton * button = pbgColorFormat->button(buttonid);
            if (button)
            {
                button->setChecked(true);
            }
        }
        // Direct3D activated
        else
        {
            // not supported in linux
            ;
        }
    }

    double dummy1, dummy2;
    is_SetAutoParameter (m_hCamera, IS_GET_ENABLE_AUTO_WHITEBALANCE, &dummy1, &dummy2);

    /* OpenMP */
    UINT nOpenMP_Enabled = 0;
    nRet = is_Configuration(IS_CONFIG_OPEN_MP_CMD_GET_ENABLE, &nOpenMP_Enabled, sizeof(UINT));
    if (nRet != IS_SUCCESS)
    {
        qDebug("error: is_Configuration(GET_ENABLE) failed with code %d!", nRet);
    }
    chkOpenMP_Enable->setCheckState(nOpenMP_Enabled == IS_CONFIG_OPEN_MP_ENABLE ? Qt::Checked : Qt::Unchecked);
}
