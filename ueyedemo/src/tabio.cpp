/*!
 * \file    tabio.cpp
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   properties tab widget for camera input/outputs
 *
 * \par Revision history
 * \li  05.02.2010 - created
 * \li  10.06.2015 - (1.30.0) - Qt3 dependency removed
 */

#include "properties.h"
#include <QDebug>

void properties::initTabIo()
{
    // trigger delay
    m_minTriggerDelay = 0;
    m_maxTriggerDelay = 0;
    m_incTriggerDelay = 0;
    m_nTriggerDelay = 0;
    m_bEnableTriggerDelaySet = FALSE;
    ;
    // flash delay
    m_minFlashDelay = 0;
    m_maxFlashDelay = 0;
    m_incFlashDelay = 0;
    m_nFlashDelay = 0;
    // flash duration
    m_minFlashDuration = 0;
    m_maxFlashDuration = 0;
    m_incFlashDuration = 0;
    m_nFlashDuration = 0;

    // trigger properties
    m_minTriggerDelay = is_SetTriggerDelay (m_hCamera, IS_GET_MIN_TRIGGER_DELAY);
    m_nTriggerDelay = is_SetTriggerDelay (m_hCamera, IS_GET_TRIGGER_DELAY);
    m_bEnableTriggerDelaySet = m_nTriggerDelay > m_minTriggerDelay;

    connect(radioButtonOff, SIGNAL(clicked(bool)), this, SLOT(OnRadioFlash()));
    connect(radioButtonHigh, SIGNAL(clicked(bool)), this, SLOT(OnRadioFlash()));
    connect(radioButtonLow, SIGNAL(clicked(bool)), this, SLOT(OnRadioFlash()));
    connect(radioButtonHiActive, SIGNAL(clicked(bool)), this, SLOT(OnRadioFlash()));
    connect(radioButtonLoActive, SIGNAL(clicked(bool)), this, SLOT(OnRadioFlash()));

}

void properties::UpdateTriggerStatus ()
{
    if (m_bInit || !m_hCamera)
        return;

    INT status = is_SetExternalTrigger (m_hCamera, IS_GET_TRIGGER_STATUS);
    if (status == 1)
        textLabelStatus->setText ("HIGH");
    else
        textLabelStatus->setText ("LOW");
}

void properties::UpdateInputCtrls ()
{
    if (m_bInit || !m_hCamera)
        return;

    QString strTemp;

    // get values
    m_minTriggerDelay = is_SetTriggerDelay (m_hCamera, IS_GET_MIN_TRIGGER_DELAY);
    m_maxTriggerDelay = is_SetTriggerDelay (m_hCamera, IS_GET_MAX_TRIGGER_DELAY);
    m_incTriggerDelay = is_SetTriggerDelay (m_hCamera, IS_GET_TRIGGER_DELAY_GRANULARITY);
    m_nTriggerDelay = is_SetTriggerDelay (m_hCamera, IS_GET_TRIGGER_DELAY);

    // set text
    strTemp.setNum (m_minTriggerDelay, 10);
    textMinTriggerDelay->setText (strTemp + " us");
    strTemp.setNum (m_maxTriggerDelay, 10);
    textMaxTriggerDelay->setText (strTemp + " us");

    m_bInit = TRUE;
    // update slider control
    sliderTriggerDelay->setMinimum (m_minTriggerDelay);
    sliderTriggerDelay->setMaximum (m_maxTriggerDelay);
    sliderTriggerDelay->setSingleStep (m_incTriggerDelay);
    sliderTriggerDelay->setPageStep (4* m_incTriggerDelay );
    sliderTriggerDelay->setValue (m_nTriggerDelay);
    sliderTriggerDelay->setEnabled (m_bEnableTriggerDelaySet);
    // update spin control
    spinBoxTriggerDelay->setMinimum (m_minTriggerDelay);
    spinBoxTriggerDelay->setMaximum (m_maxTriggerDelay);
    spinBoxTriggerDelay->setSingleStep (m_incTriggerDelay);
    spinBoxTriggerDelay->setValue (m_nTriggerDelay);
    spinBoxTriggerDelay->setEnabled (m_bEnableTriggerDelaySet);

    checkBoxEnableTriggerDelay->setChecked (m_bEnableTriggerDelaySet);
    m_bInit = FALSE;

    UpdateTriggerStatus ();
}

void properties::UpdateOutputCtrls ()
{
    if (m_bInit || !m_hCamera)
        return;

    QString strTemp;

    // get values

    uint flashMode = 0;
    int nRet = 0;
    nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_GET_MODE, (void*)&flashMode, sizeof(flashMode));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> UpdateOutputCtrls: IS_IO_CMD_FLASH_GET_MODE";
    }

    bool flashActive = (flashMode == IO_FLASH_MODE_TRIGGER_HI_ACTIVE)
                        || (flashMode == IO_FLASH_MODE_TRIGGER_LO_ACTIVE)
                        || (flashMode == IO_FLASH_MODE_FREERUN_HI_ACTIVE)
                        || (flashMode == IO_FLASH_MODE_FREERUN_LO_ACTIVE);

    // flash delay && duration
    IO_FLASH_PARAMS param;
    memset(&param, 0, sizeof(param));
    nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_GET_PARAMS_MIN, (void*)&param, sizeof(param));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> UpdateOutputCtrls: IS_IO_CMD_FLASH_GET_PARAMS_MIN";
    }
    else
    {
        m_minFlashDelay = param.s32Delay;
        m_minFlashDuration = param.u32Duration;
        qDebug("UpdateOutputCtrls - minFlashDelay: %d", m_minFlashDelay);
        qDebug("UpdateOutputCtrls - minFlashDuration: %d", m_minFlashDuration);
    }

    nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_GET_PARAMS_MAX, (void*)&param, sizeof(param));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> UpdateOutputCtrls: IS_IO_CMD_FLASH_GET_PARAMS_MAX";
    }
    else
    {
        m_maxFlashDelay = param.s32Delay;
        m_maxFlashDuration = param.u32Duration;
        qDebug("UpdateOutputCtrls - maxFlashDelay: %d", m_maxFlashDelay);
        qDebug("UpdateOutputCtrls - maxFlashDuration: %d", m_maxFlashDuration);
    }

    nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_GET_PARAMS_INC, (void*)&param, sizeof(param));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> UpdateOutputCtrls: IS_IO_CMD_FLASH_GET_PARAMS_INC";
    }
    else
    {
        m_incFlashDelay = param.s32Delay;
        m_incFlashDuration = param.u32Duration;
        qDebug("UpdateOutputCtrls - incFlashDelay: %d", m_incFlashDelay);
        qDebug("UpdateOutputCtrls - incFlashDuration: %d", m_incFlashDuration);
    }

    nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_GET_PARAMS, (void*)&param, sizeof(param));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> UpdateOutputCtrls: IS_IO_CMD_FLASH_GET_PARAMS";
    }
    else
    {
        m_nFlashDelay = param.s32Delay;
        m_nFlashDuration = param.u32Duration;
        qDebug("UpdateOutputCtrls - FlashDelay: %d", m_nFlashDelay);
        qDebug("UpdateOutputCtrls - FlashDuration: %d", m_nFlashDuration);
    }

    // set text
    strTemp.setNum (0, 10);
    textMinFlashDelay->setText (strTemp + " us");
    strTemp.setNum (m_maxFlashDelay, 10);
    textMaxFlashDelay->setText (strTemp + " us");

    strTemp.setNum (0, 10);
    textMinFlashDuration->setText (strTemp + " us");
    strTemp.setNum (m_maxFlashDuration, 10);
    textMaxFlashDuration->setText (strTemp + " us");

    m_bInit = TRUE;
    // update radio Buttons
    switch (flashMode)
    {
    case IO_FLASH_MODE_CONSTANT_HIGH:
        radioButtonHigh->setChecked(true);
        break;
    case IO_FLASH_MODE_CONSTANT_LOW:
        radioButtonLow->setChecked(true);
        break;
    case IO_FLASH_MODE_TRIGGER_HI_ACTIVE:
    case IO_FLASH_MODE_FREERUN_HI_ACTIVE:
        radioButtonHiActive->setChecked(true);
        break;

    case IO_FLASH_MODE_TRIGGER_LO_ACTIVE:
    case IO_FLASH_MODE_FREERUN_LO_ACTIVE:
        radioButtonLoActive->setChecked(true);
        break;
    case IO_FLASH_MODE_OFF :
        default:
        radioButtonOff->setChecked(true);
        break;
    }

    radioButtonHiActive->setEnabled (true);
    radioButtonLoActive->setEnabled (true);
    // update slider control
    sliderFlashDelay->setMinimum (0);
    sliderFlashDelay->setMaximum (m_maxFlashDelay);
    sliderFlashDelay->setSingleStep(m_incFlashDelay);
    sliderFlashDelay->setPageStep(200*m_incFlashDelay);
    sliderFlashDelay->setValue (m_nFlashDelay);
    sliderFlashDelay->setEnabled (flashActive);
    // update spin control
    spinBoxFlashDelay->setMinimum (0);
    spinBoxFlashDelay->setMaximum (m_maxFlashDelay);
    spinBoxFlashDelay->setSingleStep (m_incFlashDelay);
    spinBoxFlashDelay->setValue (m_nFlashDelay);
    spinBoxFlashDelay->setEnabled (flashActive);
    // update slider control
    sliderFlashDuration->setMinimum (0);
    sliderFlashDuration->setMaximum (m_maxFlashDuration);
    sliderFlashDuration->setSingleStep(m_incFlashDuration);
    sliderFlashDuration->setPageStep(200*m_incFlashDuration);
    sliderFlashDuration->setValue (m_nFlashDuration);
    sliderFlashDuration->setEnabled (flashActive);
    // update spin control
    spinBoxFlashDuration->setMinimum (0);
    spinBoxFlashDuration->setMaximum (m_maxFlashDuration);
    spinBoxFlashDuration->setSingleStep (m_incFlashDuration);
    spinBoxFlashDuration->setValue (m_nFlashDuration);
    spinBoxFlashDuration->setEnabled (flashActive);
    // global flash?
    pushButtonGlobalFlashDelay->setEnabled (flashActive && !m_SensorInfo.bGlobShutter);
    m_bInit = FALSE;
}

void properties::UpdateEepromCtrls ()
{
    if (m_bInit || !m_hCamera)
        return;

    unsigned int size = 0;
    int nRet = is_PersistentMemory(m_hCamera, IS_PERSISTENT_MEMORY_GET_SIZE_USER, &size, sizeof(size));
    if (nRet !=  IS_SUCCESS)
    {
        qWarning() << "Could not read persistent memory user size, error code: " << nRet;
        return;
    }

    QByteArray data(size, '\0');

    IS_PERSISTENT_MEMORY persistenMemory;
    persistenMemory.pu8Memory = data.data();
    persistenMemory.u32Count = data.size();
    persistenMemory.u32Offset = 0;
    persistenMemory.s32Option = 0;

    nRet = is_PersistentMemory(m_hCamera, IS_PERSISTENT_MEMORY_READ_USER, &persistenMemory, sizeof(persistenMemory));
    if (nRet !=  IS_SUCCESS)
    {
        qWarning() << "Could not read persistent memory data, error code: " << nRet;
        return;
    }

    lineEditEepromEntry->setText (QString::fromUtf8(data.data(), data.size()));
    m_bInit = FALSE;
}

void properties::on_pushButtonPollStatus_clicked ()
{
    UpdateTriggerStatus ();
}

void properties::checkEnableTriggerDelay_clicked ()
{
    m_bEnableTriggerDelaySet = checkBoxEnableTriggerDelay->isChecked ();

    if (!m_bEnableTriggerDelaySet)
        sliderTriggerDelay_valueChanged (0); // reset trigger delay

    UpdateInputCtrls ();
}

void properties::sliderTriggerDelay_valueChanged (int value)
{
    if (m_bInit || !m_hCamera)
        return;

    value = (value < m_minTriggerDelay) ? m_minTriggerDelay : value;
    value = (value > m_maxTriggerDelay) ? m_maxTriggerDelay : value;

    is_SetTriggerDelay (m_hCamera, value);

    UpdateInputCtrls ();
}

void properties::OnRadioFlash ()
{
    if (m_bInit || !m_hCamera)
        return;

    INT triggerMode = is_SetExternalTrigger (m_hCamera, IS_GET_EXTERNALTRIGGER);

    bool triggerActive = (triggerMode != IS_SET_TRIGGER_OFF);

    INT mode = 0;

    if (radioButtonHigh->isChecked())
    {
        mode = IO_FLASH_MODE_CONSTANT_HIGH;
    }
    if (radioButtonLow->isChecked())
    {
        mode = IO_FLASH_MODE_CONSTANT_LOW ;
    }
    if (radioButtonHiActive->isChecked())
    {
        mode = IO_FLASH_MODE_TRIGGER_HI_ACTIVE;
    }
    if (radioButtonLoActive->isChecked())
    {
        mode = IO_FLASH_MODE_TRIGGER_LO_ACTIVE;
    }
    if (radioButtonOff->isChecked())
    {
        mode = IO_FLASH_MODE_OFF ;
    }

    if (mode == IO_FLASH_MODE_TRIGGER_HI_ACTIVE && !triggerActive)
    {
        mode = IO_FLASH_MODE_FREERUN_HI_ACTIVE;
    }
    if (mode == IO_FLASH_MODE_TRIGGER_LO_ACTIVE && !triggerActive)
    {
        mode = IO_FLASH_MODE_FREERUN_LO_ACTIVE;
    }

    int nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_SET_MODE, (void*)&mode, sizeof(mode));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> OnRadioFlash: IS_IO_CMD_FLASH_SET_MODE";
    }

    UpdateOutputCtrls ();
}

void properties::pushButtonGlobalFlashDelay_clicked ()
{
    if (m_bInit || !m_hCamera)
        return;

    int nRet = 0;
    IO_FLASH_PARAMS flashParam;

    nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_GET_GLOBAL_PARAMS, (void*)&flashParam, sizeof(flashParam));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> pushButtonGlobalFlashDelay_clicked: IS_IO_CMD_FLASH_GET_GLOBAL_PARAMS";
    }

    nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_SET_PARAMS, (void*)&flashParam, sizeof(flashParam));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> pushButtonGlobalFlashDelay_clicked: IS_IO_CMD_FLASH_SET_PARAMS";
    }

    UpdateOutputCtrls ();
}

void properties::sliderFlashDelay_valueChanged (int value)
{
    if (m_bInit || !m_hCamera)
        return;

    int newValue = value;
    /*! \note set the FlashDelay to 0 when smaller than the minimum and the value decrements.
     *  Set it to the minimum Value when incrementing from 0 */
    if (newValue < m_minFlashDelay)
    {
        if (m_nFlashDelay == 0)
            newValue = m_minFlashDelay;
        else
            newValue = 0;
    }
    newValue = (newValue > m_maxFlashDelay) ? m_maxFlashDelay : newValue;
    qDebug("Properties -> sliderFlashDelay_valueChanged: %d (calc %d)", value, newValue);

    IO_FLASH_PARAMS flashParam;
    flashParam.s32Delay = newValue;
    flashParam.u32Duration = m_nFlashDuration;

    int nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_SET_PARAMS, (void*)&flashParam, sizeof(flashParam));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> sliderFlashDelay_valueChanged: IS_IO_CMD_FLASH_SET_PARAMS";
    }

    UpdateOutputCtrls ();
}

void properties::sliderFlashDuration_valueChanged (int value)
{
    if (m_bInit || !m_hCamera)
        return;

    int newValue = value;
    /*! \note set the FlashDuration to 0 when smaller than the minimum and the value decrements.
     *  Set it to the minimum Value when incrementing from 0 */
    if (newValue < m_minFlashDuration)
    {
        if (m_nFlashDuration == 0)
            newValue = m_minFlashDuration;
        else
            newValue = 0;
    }
    newValue = (newValue > m_maxFlashDuration) ? m_maxFlashDuration : newValue;
    qDebug("Properties -> sliderFlashDuration_valueChanged: %d (calc %d)", value, newValue);

    IO_FLASH_PARAMS flashParam;
    flashParam.s32Delay = m_nFlashDelay;
    flashParam.u32Duration = newValue;

    int nRet = is_IO(m_hCamera, IS_IO_CMD_FLASH_SET_PARAMS, (void*)&flashParam, sizeof(flashParam));
    if (nRet != IS_SUCCESS)
    {
        qDebug() << "Error: Properties -> sliderFlashDuration_valueChanged: IS_IO_CMD_FLASH_SET_PARAMS";
    }

    UpdateOutputCtrls ();
}

void properties::pushButtonWriteEEPROM_clicked ()
{
    if (m_bInit || !m_hCamera)
        return;

    QString str = lineEditEepromEntry->text();
    QByteArray data = str.toUtf8();

    IS_PERSISTENT_MEMORY persistenMemory;
    persistenMemory.pu8Memory = data.data();
    persistenMemory.u32Count = data.size();
    persistenMemory.u32Offset = 0;
    persistenMemory.s32Option = 0;

    int nRet = is_PersistentMemory(m_hCamera, IS_PERSISTENT_MEMORY_WRITE_USER, &persistenMemory, sizeof(persistenMemory));
    if (nRet !=  IS_SUCCESS)
    {
        qWarning() << "Could not write persistent memory data, error code: " << nRet;
        return;
    }

    UpdateEepromCtrls ();
}

void properties::pushButtonClearEEPROM_clicked ()
{
    if (m_bInit || !m_hCamera)
        return;

    // get values
    unsigned int size = 0;
    int nRet = is_PersistentMemory(m_hCamera, IS_PERSISTENT_MEMORY_GET_SIZE_USER, &size, sizeof(size));
    if (nRet !=  IS_SUCCESS)
    {
        qWarning() << "Could not read persistent memory user size, error code: " << nRet;
        return;
    }

    QByteArray data(size, '\0');

    IS_PERSISTENT_MEMORY persistenMemory;
    persistenMemory.pu8Memory = data.data();
    persistenMemory.u32Count = data.size();
    persistenMemory.u32Offset = 0;
    persistenMemory.s32Option = 0;

    nRet = is_PersistentMemory(m_hCamera, IS_PERSISTENT_MEMORY_WRITE_USER, &persistenMemory, sizeof(persistenMemory));
    if (nRet !=  IS_SUCCESS)
    {
        qWarning() << "Could not read persistent memory data, error code: " << nRet;
        return;
    }

    UpdateEepromCtrls ();
}
