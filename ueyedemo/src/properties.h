/*!
 * \file    properties.h
 * \date    22.03.2012
 * \author  IDS Imaging Development Systems GmbH
 * \version $Revision:$
 *
 * \brief   properties dialog class declaration for the Qt uEye demo
 *
 * \par Last modified
 *      on $Date:$ by $Author:$
 *
 * \par Revision history
 * \li  26.06.2009 - created
 * \li  30.07.2009 - added TestImage support
 * \li  03.12.2009 - use new QSliderEx class with slackness for image size handling
 * \li  14.12.2009 - add 6x-16x size support
 * \li  01.02.2010 - add size h/v factor members and a fct to get the factors from the actual
 *                   binning/subsampling mode.
 * \li  18.05.2010 - add special uEye XS features on "XS" Tab
 * \li  18.05.2010 - add XS image Stabilization
 * \li  27.07.2010 - changed some slotnames and connect them manually cause of
 *                   problems with auto signal-slot connection by name
 * \li  06.09.2010 - add m_bHasSoftwareGamma to get sw gamma support, cause of "XS"
 * \li  22.03.2012 - some changes on variables
 * \li  04.05.2012 - changes on Pixelclock settings
 * \li  08.05.2012 - changes on Variables for Pixelclock settings
 * \li  16.05.2012 - Changes to use new functions
 * \li  24.04.2013 - Changes on Image-Size settings
 * \li  03.06.2013 - Add new XS-Functions
 */

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "mainview.h"
#include "eventthread.h"
#include "ui_properties.h"
#include <ueye.h>

#include "qtui.h"
#include <QSlider>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <QLabel>
#include <QTabWidget>
#include <QCheckBox>
#include <QButtonGroup>
#include <QMap>
#include "qsliderex.h"

class Mainview;

/*!
 * \defgroup UEYEPROPERTIES Property dialog
 * \{
 */
/*!
 * \brief Default minimum gain
 */
#define IS_MIN_GAIN 0
/*!
 * \brief Default maximum gain
 */
#define IS_MAX_GAIN 100

/*!
 * \brief Default minimum blacklevel offset
 */
#define IS_MIN_BL_OFFSET 0
/*!
 * \brief Default maximum blacklevel offset
 */
#define IS_MAX_BL_OFFSET 255
/*!
 * \brief default slider check period in msecs
 */
#define SLIDER_CHECK_PERIOD 500 //ms
/*!
 * \brief uEye camera properties dialog
 */
class properties : public QDialog, public Ui::_DlgProperties
{
Q_OBJECT

public:
    /*!
     * \brief Constructor
     * \param hCam          Camera handle as returned from libueye_api
     * \param camInfo       Camera info structure
     * \param sensorInfo    Sensor info structure
     * \param bLive         Live mode indicator
     * \param parent        Qt parent object
     */
    properties (HIDS hCam, CAMINFO camInfo, SENSORINFO sensorInfo, bool bLive, QWidget* parent = 0);
    /*!
     * \brief Destructor
     */
    virtual ~properties ();

    /*!
     * \brief called from outside to allow faster teardown (deconstructor has not to wait so long until event thread has stopped)
     */
    void SignalStopEventThreads();

public slots:
    /*!
     * \brief Received event slot
     * \param event Event ID
     */
    void eventreceived (int event);

    /*! \brief when colormode changed slot */
    void OnClickedColormode(int buttonId);

	/*! \brief Switch to JPEG-Mode */
    void SetJPEGMode(bool bEnable);

    /*! \brief Restore colormode Settings */
    void RestoreColorModeSettings();

	/*! \brief Restore Xs Settings */
    void RestoreXsSettings();
    void RestoreFormatsXs();

    /*! \brief on checkbox state change 'Enable OpenMP' */
    void OnOpenMP_Enable(int iNewState);

    virtual void OnCheckboxHotpixelCorrection(bool);
    virtual void OnCheckboxCameraHotpixelCorrection(bool);
    virtual void OnCheckboxSoftwareUserHotpixelCorrection(bool);
    virtual void OnCheckboxSensorHotpixelCorrection(bool);
    virtual void OnCheckboxAdaptiveHotpixelCorrection(bool);
    virtual void UpdateAdaptiveHotpixelCorrectionNumberDetected(int);
    virtual void UpdateAdaptiveHotpixelCorrectionPercentDetected(double);

    virtual void OnAdaptiveHotpixelCorrectionSensitivity(int);
    virtual void OnAdaptiveHotpixelCorrectionMode(int);
    virtual void OnAdaptiveHotpixelCorrectionDetectAgain(bool);

    virtual void OnRadioWhiteBalance ();
    virtual void OnRadioEdgeEnhancement ();
    virtual void OnSliderChangeFrameRate (int value);
    virtual void OnSliderChangeExposure (int value);
    virtual void OnSpinBoxChangePixelClock (int value);
    virtual void OnSliderChangePixelClock (int value);
    virtual void OnChangePixelClockSetting (int value);
    virtual void OnSliderChangeBlue (int value);
    virtual void OnSliderChangeGreen (int value);
    virtual void OnSliderChangeRed (int value);
    virtual void OnSliderChangeMaster (int value);
    virtual void OnButtonDefault ();

    virtual void checkAutoFps_clicked ();
    virtual void checkAutoExp_clicked ();
    virtual void checkMaxExp_clicked ();
    virtual void checkAutoGain_clicked ();

    virtual void sliderBlackLevel_valueChanged (int value);
    virtual void checkAutoBlacklevel_clicked ();
    virtual void checkBoxSoftwareGamma_clicked ();
    virtual void checkBoxHardwareGamma_clicked ();
    virtual void checkBoxGainBoost_clicked ();

    virtual void tabWidget_currentChanged (int);
    virtual void OnSliderChangeImageWidth(int);
    virtual void OnImageWidthChanged (int);
    virtual void OnSliderChangeImageHeigth(int);
    virtual void OnImageHeightChanged (int);
    virtual void OnSliderChangeImageXPos(int);
    virtual void OnImageXPosChanged (int);
    virtual void OnSliderChangeImageYPos(int);
    virtual void OnImageYPosChanged (int);
    //virtual void OnImageChanged();
    virtual void OnRadioHFormat ();
    virtual void OnRadioVFormat ();
    virtual void OnButtonUpDown ();
    virtual void OnButtonLeftRight ();

    virtual void checkEnableTriggerDelay_clicked ();
    virtual void on_pushButtonPollStatus_clicked ();
    virtual void pushButtonWriteEEPROM_clicked ();
    virtual void sliderTriggerDelay_valueChanged (int);
    virtual void OnRadioFlash ();
    virtual void sliderFlashDelay_valueChanged (int);
    virtual void sliderFlashDuration_valueChanged (int);
    virtual void pushButtonGlobalFlashDelay_clicked ();
    virtual void pushButtonClearEEPROM_clicked ();
    virtual void OnRadioColorCorrection_clicked ();

    virtual void changedFormatsLive (int index);
    virtual void changedFormatsTrigger (int index);

    virtual void OnActivateTestImage ();
    virtual void OnChangedTestImage (int);

    virtual void OnMirrorUpDown ();
    virtual void OnMirrorLeftRight ();

    virtual void OnXsAutoFocus (bool);
    virtual void OnXsFocusOnce ();
    virtual void OnXsLSC (int);
    virtual void OnXsBacklightComp (bool);
    virtual void OnXsFaceDetect (bool);
    virtual void OnXsAES (bool);
    virtual void OnXsAGC (bool);
    virtual void OnXsAGEC (bool);
    virtual void OnXsImgStabilization(bool);
    virtual void OnXsNoise (bool);
    virtual void OnXsJPEGCompression (int value);
    virtual void OnXsJPEGMode (bool);
    virtual void OnXsSharpness (int value);
    virtual void OnXsSaturation (int value);
    virtual void OnXsManualFocus (int value);
    virtual void OnXsFocusDistance ();

    virtual void OnComboBoxPowerDeliveryCurrentIndexChanged(int index);

    virtual void OnAutoUpdateCameraCtrls();
    virtual void OnAutoUpdateImageCtrls();
    virtual void OnAutoUpdateXsCtrls();
    virtual void OnUpdateLive(bool bLive);
    /*
     virtual void          checkBoxPollStatus_clicked();
     virtual void          sliderTriggerDelay_valueChanged(int);
     virtual void          checkBoxEnableTriggerDelay_clicked();

     virtual void          pushButtonGlobalFlashDelay_clicked();
     virtual void          sliderFlashDelay_valueChanged(int);
     virtual void          sliderFlashDuration_valueChanged(int);

     virtual void          pushButtonWriteEeprom_clicked();
     virtual void          pushButtonClearEeprom_clicked();
     virtual void          radioButtonOff_clicked();
     */
    /*!
     * \brief Change frame rate
     */
    void ChangeFramerate (double value);
    /*!
     * \brief Update pixel clock controls
     */
    void ChangeExposure (double value);

    /*!
     * \brief Refresh page
     */
    void RefreshPage ();

protected:
    /*!
     * \brief Show event slot
     * \param \ Show event object
     */
    void showEvent (QShowEvent *);

private:
    /*!
     *  \brief Camera handle as returned from libueye_api
     */
    HIDS m_hCamera;
    /*!
     * \brief Camera info structure
     */
    CAMINFO m_CamInfo;
    /*!
     * \brief Sensor info structure
     */
    SENSORINFO m_SensorInfo;

    /*!
     * \brief Initialization indicator
     */
    bool m_bInit;
    /*!
     * \brief Live operation indicator
     */
    bool m_bLive;

    void RestoreHotpixelCtrls();
    void UpdateHotpixelCtrls();
    void UpdateAdaptiveHotpixelCtrls();

    /*!
     * \brief Update pixel clock controls
     */
    void UpdatePixelclockCtrls ();
    /*!
     * \brief Update frame rate controls
     */
    void UpdateFramerateCtrls ();
    /*!
     * \brief Update exposure controls
     */
    void UpdateExposureCtrls ();
    /*!
     * \brief Update master gain controls
     */
    void UpdateMasterGainCtrls ();
    /*!
     * \brief Update black level controls
     */
    void UpdateBlackLevelCtrls ();
    /*!
     * \brief Update RGB gain controls
     */
    void UpdateRGBGainCtrls ();
    /*!
     * \brief Update feature controls
     */
    void UpdateFeaturesCtrls ();
    /*!
     * \brief Update edge enhancement controls
     */
    void UpdateEdgeEnhCtrls ();

    /*!
     * \brief Update windows size controls
     */
    void UpdateWindowSizeCtrls ();
    /*!
     * \brief Update size and format controls
     */
    void UpdateSizeFormatCtrls ();

    /*!
     * \brief get the vertical and horizontal size factors
     * \param pVFactor pointer to the vFactor storage
     * \param pHFactor pointer to the vFactor storage
     * \return sdk return value
     */
    int getSizeFactor(int *pVFactor, int *pHFactor);
    /*!
     * \brief Update color controls
     */
    void UpdateColorCtrls ();
    /*!
     * \brief Update whitebalance controls
     */
    void UpdateWBCtrls ();

    /*!
     * @brief ApplyBinningSettings
     */
    void ApplyBinningSettings(int binningMode, int nMode);

    /*!
     * @brief ApplySubsamplingSettings
     */
    void ApplySubsamplingSettings(int subsamplingMode, int nMode);

    /*!
     * \brief Update trigger status
     */
    void UpdateTriggerStatus ();
    /*!
     * \brief Update input controls
     */
    void UpdateInputCtrls ();
    /*!
     * \brief Update output controls
     */
    void UpdateOutputCtrls ();
    /*!
     * \brief Update eeprom status
     */
    void UpdateEepromCtrls ();
    /*!
     * \brief Update image format size tab controls
     */
    void UpdateSizeXSCtrls();
    /*!
     * \brief Update special xs feautures tab controls
     */
    void UpdateXsFeatures();
    void UpdateXs_JpegCompressionControls();
    void UpdateXs_SharpnessControls();
    void UpdateXs_SaturationControls();
    void UpdateXs_FocusControls();
    void UpdateXs_AutoParamControls();
    void UpdateXs_Temperature();
    void UpdateXs_LSCControls();

    /*! \brief Update advanced features tab controls */
    void UpdatePowerDeliveryControls();

    /*!
     * \brief Retrieve test image name
     * \param testimage Testimage identifiert from uEye.h
     */
    QString GetTestImageName (int testimage);
    /*!
     * \brief Create test image list depending on camera capabilities
     * \param images Number of images
     */
    void populateTestImages (int images);

    /*! \brief tab camera initialization */
    void initTabCamera();
    /*! \brief tab image initialization */
    void initTabImage();
    /*! \brief tab hotpixel initialization */
    void initTabHotpixel();
    /*! \brief tab size initialization */
    void initTabSize();
    /*! \brief tab format size initialization */
    void initTabSizeXs();
    /*! \brief tab format initialization */
    void initTabFormat();
    /*! \brief tab io initialization */
    void initTabIo();
    /*! \brief tab processing initialization */
    void initTabProcessing();
    void initHotpixelCorrection();
    /*! \brief tab advances initialization */
    void initTabAdvanced();
    /*! \brief tab xs special features initialization */
    void initTabXs();
    void initXs_JpegCompressionControls();
    void initXs_SharpnessControls();
    void initXs_SaturationControls();
    void initXs_FocusControls();
    void initXs_AutoParamControls();
    void initXs_LSCControls();
    /*! \brief disable all color formats */
    void DisableColorFormats();
    /*! \brief hide the 5x5 color formats */
    void DoNotShow5x5();
    /*! \brief update the format tab */
    void UpdateTabFormat();
    /*! \brief checks if colorformats are supported */
    bool CheckColorFormat(UINT ColorFormat, UINT ConvertType);
    /*! \brief enables the supported color formats */
    void EnableSupportedColorFormats();
    /*! \brief create an exclusive buttongroup with all color format radio buttons */
    void createRadioButtonGroup();
    /*! \brief fill the comboboxes with the available image formats from the camera */
    int fillComboBoxImageFormats();
    /*! \brief select the current camera formats */
    void selectComboImageFormats();

    // pixelclock
    int m_maxPixelclock;
    int m_minPixelclock;
    int m_incPixelclock;
    int m_nPixelclockListIndex;
    int m_nPixelclockList[150];
    int m_nNumberOfSupportedPixelClocks;
    // framerate
    double m_maxFramerate;
    double m_minFramerate;
    double m_incFramerate;
    double m_dblFramerate;
    bool m_bAutoFramerate;
    bool m_bHasAutoFps;
    // exposure time
    double m_maxExposure;
    double m_minExposure;
    double m_incExposure;
    double m_dblExposure;
    bool m_bAutoExposure;
    bool m_bMaxExposure;
    bool m_bHasAutoExposure;

    // edgeenhancement
    int m_weakEdgeEnhancement;
    int m_strongEdgeEnhancement;

    // masterGain
    int m_maxMasterGain;
    int m_minMasterGain;
    int m_incMasterGain;
    int m_nMasterGain;
    bool m_bAutoGain;
    bool m_bHasAutoGain;
    // blacklevel
    int m_maxBlackLevel;
    int m_minBlackLevel;
    int m_incBlackLevel;
    int m_nBlackLevel;
    bool m_bAutoBlackLevel;
    bool m_bHasAutoBlackLevel;
    bool m_bHasManualBlackLevel;
    // rgbGains
    int m_maxRGBGain;
    int m_minRGBGain;
    int m_incRGBGain;
    int m_nRedGain;
    int m_nGreenGain;
    int m_nBlueGain;
    // features
    bool m_bSoftwareGammaSet;
    bool m_bHardwareGammaSet;
    bool m_bHasHardwareGamma;
    bool m_bHasSoftwareGamma;
    bool m_bHotPixelCorrSet;
    bool m_bGainBoostSet;
    bool m_bHasGainBoost;

    // aoi
    int m_maxWidth;
    int m_minWidth;
    int m_incWidth;
    int m_nWidth;
    int m_maxHeight;
    int m_minHeight;
    int m_incHeight;
    int m_nHeight;
    int m_maxXPos;
    int m_minXPos;
    int m_incXPos;
    int m_nXPos;
    int m_maxYPos;
    int m_minYPos;
    int m_incYPos;
    int m_nYPos;
    int m_vFactor;
    int m_hFactor;

    // horizontal format
    bool m_bHasColorBinning;
    bool m_bHasColorSubsampling;

    // trigger delay
    int m_minTriggerDelay;
    int m_maxTriggerDelay;
    int m_incTriggerDelay;
    int m_nTriggerDelay;
    bool m_bEnableTriggerDelaySet;
    // flash delay
    int m_minFlashDelay;
    int m_maxFlashDelay;
    int m_incFlashDelay;
    int m_nFlashDelay;
    // flash duration
    int m_minFlashDuration;
    int m_maxFlashDuration;
    int m_incFlashDuration;
    int m_nFlashDuration;

    // power delivery
    std::map<unsigned int, QString> m_availablePowerDeliveryProfiles;

    // xs
    int m_xsMinManualFocus;
    int m_xsMaxManualFocus;
    int m_xsIncManualFocus;
    int m_xsMinSharpness;
    int m_xsMaxSharpness;
    int m_xsIncSharpness;
    int m_xsMinSaturation;
    int m_xsMaxSaturation;
    int m_xsIncSaturation;
    int m_xsMinJPEGCompression;
    int m_xsMaxJPEGCompression;
    int m_xsIncJPEGCompression;
    int m_xsLSCDefaultValue;
    bool m_xsFocusOnceActive;

    bool m_bXsHasBacklightComp;
    bool m_bXsHasAES;
    bool m_bXsHasAGES;
    bool m_bXsHasAGS;
    bool m_bIsXs;

    EventThread *m_pEvWB;

    QTimer *m_pTimer;

    // Timer automatic update
    QTimer *m_pTimerUpdateCameraCtrl;
    QTimer *m_pTimerUpdateImageCtrl;
    QTimer *m_pTimerUpdateXsCtrl;

    Mainview* m_pDlgMainView;

    QSliderEx* m_pSliderWidthEx;
    QSliderEx* m_pSliderHeightEx;
    QSliderEx* m_pSliderPosXEx;
    QSliderEx* m_pSliderPosYEx;

    // tab format variables
    bool m_bColor;
    bool m_bJPEG;
    QButtonGroup *pbgColorFormat;

};

/*!
 * \}
 */// end of doc group UEYEPROPERTIES
#endif // PROPERTIES_H
