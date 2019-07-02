/*!
 * \file    tabsizexs.cpp
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   properties tab widget for camera format size operations
 *
 * \par Revision history
 * \li  04.05.2010 - created
 * \li  27.07.2010 - changed some slotnames and connect them manually cause of
 *                   problems with auto signal-slot connection by name
 * \li  12.12.2014 - Fixed usage of live and trigger image formats
 */

#include "properties.h"

void properties::initTabSizeXs()
{
    fillComboBoxImageFormats();
    selectComboImageFormats();

    /* connect the combobox signals only after the combobox creation */
    connect(cB_FormatsLive, SIGNAL(currentIndexChanged(int)), this, SLOT(changedFormatsLive(int)));
    if(cB_FormatsTrigger->count())
    {
        connect(cB_FormatsTrigger, SIGNAL(currentIndexChanged(int)), this, SLOT(changedFormatsTrigger(int)));
    }

    connect (cB_Mirror_lr, SIGNAL(clicked()), this, SLOT(OnMirrorLeftRight()));
    connect (cB_Mirror_ud, SIGNAL(clicked()), this, SLOT(OnMirrorUpDown()));
}


/*! \brief fill the comboboxes with available image format of a camera
 *
*/
int properties::fillComboBoxImageFormats()
{
    int ret = IS_SUCCESS;
    int nNumber;
    IMAGE_FORMAT_LIST *pFormatList;
    QString strFormat;

    if ((ret=is_ImageFormat(m_hCamera, IMGFRMT_CMD_GET_NUM_ENTRIES, (void*)&nNumber, sizeof(nNumber))) == IS_SUCCESS)
    {
        int i = 0;
        int nSize = sizeof(IMAGE_FORMAT_LIST) + (nNumber - 1) * sizeof(IMAGE_FORMAT_INFO);
        pFormatList = (IMAGE_FORMAT_LIST*)(new char[nSize]);
        pFormatList->nNumListElements = nNumber;
        pFormatList->nSizeOfListEntry = sizeof(IMAGE_FORMAT_INFO);

        if((ret=is_ImageFormat(m_hCamera, IMGFRMT_CMD_GET_LIST, (void*)pFormatList, nSize)) == IS_SUCCESS)
        {
            for(i=0; i<nNumber; i++)
            {
                // Freerun or single snaphot
                if (((pFormatList->FormatInfo[i].nSupportedCaptureModes & CAPTMODE_FREERUN) &&
                     (pFormatList->FormatInfo[i].nSupportedCaptureModes & CAPTMODE_SINGLE)) ||
                     (pFormatList->FormatInfo[i].nSupportedCaptureModes & CAPTMODE_TRIGGER_SOFT_SINGLE)
                   )
                {
                    strFormat = pFormatList->FormatInfo[i].strFormatName;

                    if ((pFormatList->FormatInfo[i].nSupportedCaptureModes & CAPTMODE_FREERUN) &&
                        (pFormatList->FormatInfo[i].nSupportedCaptureModes & CAPTMODE_SINGLE)
                       )
                    {
                        cB_FormatsLive->addItem(strFormat, pFormatList->FormatInfo[i].nFormatID);
                    }

                    if (pFormatList->FormatInfo[i].nSupportedCaptureModes & CAPTMODE_TRIGGER_SOFT_SINGLE)
                    {
                        cB_FormatsTrigger->addItem(strFormat, pFormatList->FormatInfo[i].nFormatID);
                    }
                }
            }
        }
        else
        {
            qDebug("error: is_ImageFormat returned %d", ret);
        }

        if(cB_FormatsTrigger->count() == 0)
        {
            cB_FormatsTrigger->setVisible(false);
            labelSizeTrigger->setVisible(false);
        }

        delete (pFormatList);
    }
    else
    {
        qDebug("error: is_ImageFormat returned %d", ret);
    }
    return ret;
}

void properties::selectComboImageFormats()
{
    int nFormatIx = 0;

    // find the current live format id in combobox data
    nFormatIx = cB_FormatsLive->findData(m_pDlgMainView->m_CameraProps.nImgFmtNormal);
    if (nFormatIx != -1)
    {
        cB_FormatsLive->setCurrentIndex(nFormatIx);
    }
    else
        qDebug("error: image format %d not found in live formats", m_pDlgMainView->m_CameraProps.nImgFmtNormal);

    if(cB_FormatsTrigger->count() != 0)
    {
        // find the current trigger format id in combobox data
        nFormatIx = cB_FormatsTrigger->findData(m_pDlgMainView->m_CameraProps.nImgFmtTrigger);
        if (nFormatIx != -1)
        {
            cB_FormatsTrigger->setCurrentIndex(nFormatIx);
        }
        else
            qDebug("error: image format %d not found in trigger formats", m_pDlgMainView->m_CameraProps.nImgFmtTrigger);
    }

}

void properties::changedFormatsLive (int index)
{
    int ret = 0;
    qDebug("image format ix LIVE %d choosen.", index);
    int nFormatId = cB_FormatsLive->itemData(index).toInt();
    m_pDlgMainView->m_CameraProps.nImgFmtNormal = nFormatId;

    /* only update image parameters if camera is not in trigger mode */
    if (is_SetExternalTrigger(m_hCamera, IS_GET_EXTERNALTRIGGER) == IS_SET_TRIGGER_OFF)
    {
        if (m_bLive)
            is_StopLiveVideo (m_hCamera, IS_WAIT);

        if ((ret=is_ImageFormat(m_hCamera, IMGFRMT_CMD_SET_FORMAT, (void*)&nFormatId, sizeof(nFormatId))) == IS_SUCCESS)
        {
            m_pDlgMainView->SetupCapture();
            m_pDlgMainView->SetupTitles();
        }
        else
        {
            qDebug("error in on_cB_FormatsLive_currentIndexChanged: is_ImageFormat returned %d", ret);
        }

        if (m_bLive)
        {
            is_CaptureVideo (m_hCamera, IS_DONT_WAIT);
        }
    }
}

void properties::RestoreFormatsXs()
{
    // Restore Format Values to Default
    m_pDlgMainView->m_CameraProps.nImgFmtNormal = m_pDlgMainView->m_CameraProps.nImgFmtDefaultNormal;
    m_pDlgMainView->m_CameraProps.nImgFmtTrigger = m_pDlgMainView->m_CameraProps.nImgFmtDefaultTrigger;
    selectComboImageFormats();
}

void properties::changedFormatsTrigger (int index)
{
    int ret = 0;
    qDebug("image format ix TRIGGER %d choosen.", index);
    int nFormatId = cB_FormatsTrigger->itemData(index).toInt();
    m_pDlgMainView->m_CameraProps.nImgFmtTrigger = nFormatId;

    /* only update image parameters if camera is in trigger mode */
    if (is_SetExternalTrigger(m_hCamera, IS_GET_EXTERNALTRIGGER) == IS_SET_TRIGGER_SOFTWARE)
    {
        if ((ret=is_ImageFormat(m_hCamera, IMGFRMT_CMD_SET_FORMAT, (void*)&nFormatId, sizeof(nFormatId))) == IS_SUCCESS)
        {
            m_pDlgMainView->SetupCapture();
            m_pDlgMainView->SetupTitles();
        }
        else
        {
            qDebug("error in on_cB_FormatsLive_currentIndexChanged: is_ImageFormat returned %d", ret);
        }
    }
}


void properties::OnMirrorUpDown ()
{
    BOOL bEnable = cB_Mirror_ud->isChecked ();
    is_SetRopEffect (m_hCamera, IS_SET_ROP_MIRROR_UPDOWN, bEnable, 0);
}

void properties::OnMirrorLeftRight ()
{
    BOOL bEnable = cB_Mirror_lr->isChecked ();
    is_SetRopEffect (m_hCamera, IS_SET_ROP_MIRROR_LEFTRIGHT, bEnable, 0);
}


