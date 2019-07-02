/*!
 * \file    imageinfodlg.cpp
 * \date    03.02.2010
 * \author  IDS Imaging Development Systems GmbH
 * \version 1.0.4
 *
 * \brief   additional image information dialog
 *
 * \par Last modified
 *      on $Date:$ by $Author:$
 *
 * \par Revision history
 * \li  29.10.2009 - (1.0.0) created
 * \li  02.11.2009 - (1.0.1) fixed UpdateControls() for new UEYEIMAGEINFO struct definition
 * \li  11.11.2009 - don't reset imageinfo dialog contents when shown!
 * \li  11.12.2009 - (1.0.3) reset controls on creation
 * \li  03.02.2010 - (1.0.4) use IS_INVALID_HIDS instead of NULL, which is incorrect for HIDS.
 */
#include "imageinfodlg.h"
#include "mainview.h"

imageinfodlg::imageinfodlg(QWidget *parent) :
    QDialog(parent)
{
    m_pParent = (Mainview*)parent;
    ui.setupUi(this);

    connect(ui.pBReset, SIGNAL(clicked()), this, SLOT(ResetCounters()));
    connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    setWindowTitle(tr("image informations"));

    ResetCounters();
    ClearControls();
}

imageinfodlg::~imageinfodlg()
{

}

void imageinfodlg::closeEvent(QCloseEvent *e)
{
    // signel the parent abot the close event
    emit close();
    // don't close the info dialog, cause the parent should decide to close or not
    e->ignore();
}

void imageinfodlg::showEvent(QShowEvent *e)
{
    Q_UNUSED(e);
}

void imageinfodlg::ClearControls()
{
    ui.progress_ImageBuffers->setValue(0);
    ui.lineEdit_ImageBuffers->setText("0");
    ui.lineEdit_ImageBuffersInUse->setText("0");
    ui.lineEdit_MissingPackets->setText("0");
}

void imageinfodlg::ResetReconnectCounter()
{
    m_nReconnects = 0;
}

void imageinfodlg::IncrementReconnectCounter()
{
    ++m_nReconnects;
}

void imageinfodlg::ResetCounters()
{
    ui.lineEdit_1->setText("0");
    ui.lineEdit_2->setText("0");
    ui.lineEdit_3->setText("0");
    ui.lineEdit_4->setText("0");
    ui.lineEdit_5->setText("0");
    ui.lineEdit_6->setText("0");
    ui.lineEdit_7->setText("0");
    ui.lineEdit_8->setText("0");
    ui.lineEdit_9->setText("0");
    ui.lineEdit_total->setText("0");
    ui.lineEdit_Reconnects->setText("0");

    if (m_pParent->getCameraHandle() != IS_INVALID_HIDS)
    {
        is_CaptureStatus(m_pParent->getCameraHandle(), IS_CAPTURE_STATUS_INFO_CMD_RESET, NULL, 0);
    }
    ResetReconnectCounter();
}

void imageinfodlg::UpdateCounters()
{
    if (m_pParent->getCameraHandle() == IS_INVALID_HIDS)
        return;

    UEYE_CAPTURE_STATUS_INFO CaptureStatusInfo;
    INT nRet = is_CaptureStatus(m_pParent->getCameraHandle(), IS_CAPTURE_STATUS_INFO_CMD_GET, (void*)&CaptureStatusInfo,
                                sizeof(CaptureStatusInfo));

    if (nRet == IS_SUCCESS)
    {
        ui.lineEdit_1->setText(QString::number(CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_API_NO_DEST_MEM]));
        ui.lineEdit_2->setText(QString::number(CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_API_CONVERSION_FAILED]));
        ui.lineEdit_3->setText(QString::number(CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_API_IMAGE_LOCKED]));
        // DRV errors
        ui.lineEdit_4->setText(QString::number(CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_DRV_OUT_OF_BUFFERS]));
        ui.lineEdit_5->setText(QString::number(CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_DRV_DEVICE_NOT_READY]));
        // USB errors
        ui.lineEdit_6->setText(QString::number(CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_USB_TRANSFER_FAILED]));
        // DEV errors
        ui.lineEdit_7->setText(QString::number(CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_DEV_TIMEOUT]));
        // ETH errors
        ui.lineEdit_8->setText(QString::number(CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_ETH_BUFFER_OVERRUN]));
        ui.lineEdit_9->setText(QString::number(CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_ETH_MISSED_IMAGES]));
        // Total errors
        ui.lineEdit_total->setText(QString::number(CaptureStatusInfo.dwCapStatusCnt_Total));
    }
    ui.lineEdit_Reconnects->setText(QString::number(m_nReconnects));
}

void imageinfodlg::UpdateControls(UEYEIMAGEINFO *pImageinfo)
{
    ui.progress_ImageBuffers->setRange(0, (int)pImageinfo->dwImageBuffers);
    ui.progress_ImageBuffers->setValue((int)pImageinfo->dwImageBuffersInUse);

    ui.lineEdit_ImageBuffers->setText(QString::number((int)pImageinfo->dwImageBuffers));
    ui.lineEdit_ImageBuffersInUse->setText(QString::number((int)pImageinfo->dwImageBuffersInUse));
    ui.lineEdit_MissingPackets->setText(QString::number((int)pImageinfo->dwReserved3));

}

