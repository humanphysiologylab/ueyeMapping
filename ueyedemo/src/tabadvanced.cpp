/*!
 * \file    tabadcanved.cpp
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   properties tab widget for camera advanced features
 *
 * \par Revision history
 * \li  26.09.2017 - created
 */

#include "properties.h"
#include <QDebug>

void properties::initTabAdvanced()
{
    m_availablePowerDeliveryProfiles[IS_POWER_DELIVERY_PROFILE_5V_LOW_POWER] = "5V low power";
    m_availablePowerDeliveryProfiles[IS_POWER_DELIVERY_PROFILE_5V_HIGH_POWER] = "5V high power";
    m_availablePowerDeliveryProfiles[IS_POWER_DELIVERY_PROFILE_9V] = "9V";
    m_availablePowerDeliveryProfiles[IS_POWER_DELIVERY_PROFILE_12V] = "12V";
    m_availablePowerDeliveryProfiles[IS_POWER_DELIVERY_PROFILE_14V8] = "14V8";
    m_availablePowerDeliveryProfiles[IS_POWER_DELIVERY_PROFILE_15V] = "15V";

    UpdatePowerDeliveryControls();

    connect(comboBoxPowerDelivery, SIGNAL(currentIndexChanged(int)), this, SLOT(OnComboBoxPowerDeliveryCurrentIndexChanged(int)));
}

void properties::UpdatePowerDeliveryControls()
{
    comboBoxPowerDelivery->blockSignals(true);

    INT supported = 0;
    INT nRet = is_PowerDelivery(m_hCamera, IS_POWER_DELIVERY_CMD_GET_SUPPORTED, &supported, sizeof(supported));
    if(nRet != IS_SUCCESS)
    {
        supported = 0;
    }

    comboBoxPowerDelivery->setEnabled(supported == TRUE);
    labelPowerDelivery->setEnabled(supported == TRUE);
    groupBoxPowerDelivery->setEnabled(supported == TRUE);

    if(!supported)
    {
        comboBoxPowerDelivery->addItem("-");
        comboBoxPowerDelivery->setToolTip("This camera does not support power delivery.");
    }
    else
    {
        comboBoxPowerDelivery->clear();
        comboBoxPowerDelivery->setToolTip("");

        UINT supportedProfiles = IS_POWER_DELIVERY_PROFILE_INVALID;
        INT nRet = is_PowerDelivery(m_hCamera, IS_POWER_DELIVERY_CMD_GET_SUPPORTED_PROFILES, &supportedProfiles, sizeof(supportedProfiles));
        if(nRet == IS_SUCCESS)
        {
            for(auto const &pair : m_availablePowerDeliveryProfiles)
            {
                if((supportedProfiles & pair.first) == pair.first)
                {
                    comboBoxPowerDelivery->addItem(pair.second, pair.first);
                }
            }
        }

        if(comboBoxPowerDelivery->count() == 0)
        {
            comboBoxPowerDelivery->addItem("No profile supported");
            comboBoxPowerDelivery->setEnabled(false);
        }
        else if(comboBoxPowerDelivery->count() > 0)
        {
            // select current profile
            UINT profile = 0;
            nRet = is_PowerDelivery(m_hCamera, IS_POWER_DELIVERY_CMD_GET_PROFILE, &profile, sizeof(profile));
            if(nRet == IS_SUCCESS)
            {
                for(int i = 0; i < comboBoxPowerDelivery->count(); i++)
                {
                    if(comboBoxPowerDelivery->itemData(i, Qt::UserRole).toUInt() == profile)
                    {
                        comboBoxPowerDelivery->setCurrentIndex(i);
                        break;
                    }
                }
            }
        }
    }

    comboBoxPowerDelivery->blockSignals(false);
}

void properties::OnComboBoxPowerDeliveryCurrentIndexChanged(int index)
{
    if(index >= 0 && index < comboBoxPowerDelivery->count())
    {
        UINT profile = comboBoxPowerDelivery->itemData(index, Qt::UserRole).toUInt();
        INT nRet = is_PowerDelivery(m_hCamera, IS_POWER_DELIVERY_CMD_SET_PROFILE, &profile, sizeof(profile));
        if(nRet != IS_SUCCESS)
        {
            QMessageBox::critical(this, "Failed", QString("Cannot set power delivery profile %1.").arg(profile));
            UpdatePowerDeliveryControls();
        }
    }
}
