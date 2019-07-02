/*!
 * \file    properties.cpp
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   properties dialog class implementation for the Qt uEye demo
 *
 * \par Revision history
 * \li  20.06.2009 - copied from old demo src
 * \li  21.06.2009 - changed Slider, Spinnbox in Qt4 functions
 * \li  21.07.2009 - triggerdelay is now reset to 0, when disabled.
 * \li  01.10.2009 - Framerate and exposure are now editable via Spin control and keyboard
 * \li  02.10.2009 - fix the ueye testimage support. Black testimage was not shown.
 * \li  15.10.2009 - fix mantis 1649 - farbige Testbilder bei Monokameras blockieren
 * \li  01.12.2009 - each image size change calls now the new fct "ChangeImageSize" to allocate
 *                       new sized buffers. So display and save show only AOI data now!
 * \li  03.12.2009 - use new QSliderEx class with slackness for image size handling
 * \li  14.12.2009 - add 6x-16x size support
 *                     - use new is_SetAOI instead of old is_SetImageSize/Pos
 *                     - fix problem with Mono/Color Binnig/Subsampling
 * \li  23.12.2009 - use flash modes also in freerun mode with new freerun FLASH MODES
 * \li  25.01.2010 - changed binning and subsampling additions for Mono and Color
 *                       to (M) and (C) cause of the to small dialog label placeholder.
 *                       TODO: find another solution to write the whole words again.
 * \li  01.02.2010 - AOI size adjustment is checked against minimum image size when using binning, subsampling now
 *                     - fix RefreshPage() for ImageProcessing tab (Mantis 2112)
 * \li  02.02.2010 - fix the keyboard input of framerate slider (Mantis 1998)
 * \li  02.02.2010 - disable QSliderEx SIGNAL valueChanged , when setting the slider manually to avoid
 *                       flickering when enter the size tab. (Mantis 1966)
 * \li  03.02.2010 - set the flash slider pagesteps to factor 200.
 *                     - now the Flash duration 0 is the minimum, followed by the minimum till the maximum. (Mantis2137)
 * \li  04.02.2010 - flash delay is now also set to '0' as minimum. (Mantis2137)
 * \li  04.02.2010 - SetupCapture don't start/stop the live capture anymore to avoid problems with
 *                       the live button status
 * \li  05.02.2010 - moved property functions to separate tabfile sources to improve the overview
 * \li  04.05.2010 - add a new property page for image format control (for new XS camera)
 * \li  18.05.2010 - add special uEye XS features on "XS" Tab
 * \li  03.02.2011 - fixed: make sure UpdateExposureCtrls and UpdateFramerateCtrls are called in the correct order
 *                          as there are functional interdependancies.
 * \li  08.05.2012 - changes on Variables
 * \li  28.05.2013 - changes to support xs
 * \li  28.01.2014 - fixed OnButtonDefault() for xs
 * \li  05.02.2014 - Implemented faster eventthread teardown. Use EVENTTHREAD_WAIT_TIMEOUT for qthread::wait().
 * \li  12.12.2014 - Removed unsused XC property tabs
 */

#include "properties.h"

properties::properties (HIDS hCam,CAMINFO camInfo,SENSORINFO sensorInfo,bool bLive,QWidget* parent) :
            QDialog (parent),
            m_hCamera (hCam),
            m_bInit (true),
            m_bLive (bLive),
            // pixelclock
            m_maxPixelclock (0),
            m_minPixelclock (0),
            m_incPixelclock (0),
            m_nPixelclockListIndex (0),
            // framerate
            m_maxFramerate (0.0),
            m_minFramerate (0.0),
            m_incFramerate (0.0),
            m_dblFramerate (0.0),
            m_bAutoFramerate (FALSE),
            m_bHasAutoFps (FALSE),
            // exposure time
            m_maxExposure (0.0),
            m_minExposure (0.0),
            m_incExposure (0.0),
            m_dblExposure (0.0),
            m_bAutoExposure (FALSE),
            m_bMaxExposure (FALSE),
            m_bHasAutoExposure (FALSE),
            // masterGain
            m_maxMasterGain (0),
            m_minMasterGain (0),
            m_incMasterGain (0),
            m_nMasterGain (0),
            m_bAutoGain (FALSE),
            m_bHasAutoGain (FALSE),
            // blacklevel
            m_maxBlackLevel (0), m_minBlackLevel (0), m_incBlackLevel (0),
            m_nBlackLevel (0),
            m_bAutoBlackLevel (FALSE),
            m_bHasAutoBlackLevel (FALSE),
            m_bHasManualBlackLevel (FALSE),
            // rgbGains
            m_maxRGBGain (0), m_minRGBGain (0), m_incRGBGain (0),
            m_nRedGain (0),
            m_nGreenGain (0),
            m_nBlueGain (0),
            // features
            m_bSoftwareGammaSet (FALSE), m_bHardwareGammaSet (FALSE),
            m_bHasHardwareGamma (FALSE), m_bGainBoostSet (FALSE),
            m_bHasGainBoost (FALSE),
            // hotpixel
            m_bHotPixelCorrSet(FALSE),
            // aoi
            m_vFactor (1),
            m_hFactor (1),
            m_bXsHasBacklightComp (false),
            m_bXsHasAES (false),
            m_bXsHasAGES (false),
            m_bXsHasAGS (false),
            m_bIsXs (false),
            m_pSliderWidthEx(0),
            m_pSliderHeightEx(0),
            m_pSliderPosXEx(0),
            m_pSliderPosYEx(0),
            m_bColor (false),
            m_bJPEG (false)

{
    setupUi (this);

    QString strTemp, strTemp1;

    m_pDlgMainView = (Mainview*)parent;

    memcpy (&m_CamInfo, &camInfo, sizeof(camInfo));
    memcpy (&m_SensorInfo, &sensorInfo, sizeof(sensorInfo));

    UEYE_AUTO_INFO autoInfo;
    if (is_GetAutoInfo (m_hCamera, &autoInfo) == IS_SUCCESS)
    {
        m_bHasAutoExposure = autoInfo.AutoAbility & AC_SHUTTER;
        m_bHasAutoFps = m_bHasAutoExposure;
        m_bHasAutoGain = autoInfo.AutoAbility & AC_GAIN;
    }
    else
    {
        m_bHasAutoFps = FALSE;
        m_bHasAutoExposure = FALSE;
        m_bHasAutoGain = FALSE;
    }

    m_pTimerUpdateCameraCtrl = new QTimer(this);
    m_pTimerUpdateImageCtrl = new QTimer(this);
    m_pTimerUpdateXsCtrl = new QTimer(this);

    /*! \note if camera uses IMAGE FORMATS instead of continuous AOI size  we have to disable the
     * normal size controls */
    INT nAOISupported = 0;
    INT ret = 0;
    if ((ret=is_ImageFormat(m_hCamera, IMGFRMT_CMD_GET_ARBITRARY_AOI_SUPPORTED, (void*)&nAOISupported,
                       sizeof(nAOISupported))) != IS_SUCCESS)
    {
        qDebug("ERROR: Properties -> initTabSize: is_ImageFormat returns %d", ret);
    }
    if (m_SensorInfo.SensorID == IS_SENSOR_XS ||
        m_SensorInfo.SensorID == IS_SENSOR_UI1008_C ||
        m_SensorInfo.SensorID == IS_SENSOR_UI1013XC)
    {
        // hide unused tabs
        tabWidget->removeTab(tabWidget->indexOf(Size));
        tabWidget->removeTab(tabWidget->indexOf(Processing));
        tabWidget->removeTab(tabWidget->indexOf(InOut));

        // init SizeXS tab page
        initTabSizeXs();
        initTabXs();
        m_bIsXs = true;
    }
    else
    {
        // hide the image format tab page
        tabWidget->removeTab(tabWidget->indexOf(SizeXS));
        tabWidget->removeTab(tabWidget->indexOf(XsFeatures));
        // init the size (aoi) tab parameter
        initTabSize();
        m_bIsXs = false;
    }

    // init the IO tab page
    initTabIo();

    // init the processing tab
    initTabProcessing();

    // init the image tab page
    initTabImage();

    // init the image tab page
    initTabHotpixel();

    // init the camera tab page
    initTabCamera();

    /* init the format tab page
     * \note Before we can do this we have to get the sensorinfo
     */
    initTabFormat();

    // init the advanced tab
    initTabAdvanced();

    m_bInit = FALSE;
}

properties::~properties ()
{
    if (m_pEvWB)
    {
        m_pEvWB->stop ();
        if (m_pEvWB->wait (2 * EVENTTHREAD_WAIT_TIMEOUT) == FALSE)
            m_pEvWB->terminate ();
        delete m_pEvWB;
        m_pEvWB = NULL;
    }
}

void properties::SignalStopEventThreads()
{
    if (m_pEvWB)
    {
        m_pEvWB->stop();
    }
}

// -------------------  showEvent  -----------------------
//
void properties::RefreshPage ()
{
    int curindex = tabWidget->currentIndex ();

    if (curindex == tabWidget->indexOf(Timing))
    {
        // CAMERA
        UpdateExposureCtrls ();
        /* UpdateFramerateCtrls and UpdatePixelclockCtrls depends on the results of UpdateExposureCtrls. */
        UpdatePixelclockCtrls ();
        UpdateFramerateCtrls ();
    }
    else if (curindex == tabWidget->indexOf(Image))
    {
        // IMAGE
        UpdateMasterGainCtrls ();
        UpdateBlackLevelCtrls ();
        UpdateRGBGainCtrls ();
        UpdateFeaturesCtrls ();
        UpdateEdgeEnhCtrls ();
    }
    else if (curindex == tabWidget->indexOf(Hotpixel))
    {
        UpdateHotpixelCtrls();
        UpdateAdaptiveHotpixelCtrls();
    }
    else if (curindex == tabWidget->indexOf(Size))
    {
        // SIZE
        UpdateWindowSizeCtrls ();
        UpdateSizeFormatCtrls ();
    }
    else if (curindex == tabWidget->indexOf(SizeXS))
    {
        // SIZEXS
        UpdateSizeXSCtrls();

    }
    else if (curindex == tabWidget->indexOf(Format))
    {
        // FORMAT
        UpdateTabFormat();
    }
    else if (curindex == tabWidget->indexOf(Processing))
    {
        // IMAGEPROCESSING
        UpdateColorCtrls ();
        UpdateWBCtrls ();
    }
    else if (curindex == tabWidget->indexOf(XsFeatures))
    {
        // XS special features
        UpdateXsFeatures ();
    }
    else if (curindex == tabWidget->indexOf(InOut))
    {
        // I/O
        UpdateTriggerStatus ();
        UpdateInputCtrls ();
        UpdateOutputCtrls ();
        UpdateEepromCtrls ();
    }
    else if (curindex == tabWidget->indexOf(Advanced))
    {
        // Advanced
        UpdatePowerDeliveryControls();
    }
    else
    {
        // asume first page (or better all??)

    } // end switch(tabWidget->currentPageIndex())
}

// -------------------  showEvent  -----------------------
//
void properties::showEvent (QShowEvent *)
{
    RefreshPage ();
}

// -------------------  tabWidget_currentChanged  -----------------------
//
void properties::tabWidget_currentChanged (int)
{
    RefreshPage ();
}

// -------------------  OnButtonDefault  -----------------------
//
void properties::OnButtonDefault ()
{
    if (m_bInit || !m_hCamera)
        return;

    INT colorMode;
    bool wasLive;
    // keep color format
    colorMode = is_SetColorMode (m_hCamera, IS_GET_COLOR_MODE);
    wasLive = (is_CaptureVideo (m_hCamera, IS_GET_LIVE) != 0);
    is_StopLiveVideo (m_hCamera, IS_WAIT);

    // restore all defaults
    is_ResetToDefault (m_hCamera);
    is_SetColorMode (m_hCamera, colorMode);

    // reset demo flags
    m_bEnableTriggerDelaySet = false;
    m_bMaxExposure = false;
    chkOpenMP_Enable->setChecked(true);

    RestoreHotpixelCtrls();

    // reset XS-Tab if needed
    if (m_SensorInfo.SensorID == IS_SENSOR_XS ||
        m_SensorInfo.SensorID == IS_SENSOR_UI1008_C ||
        m_SensorInfo.SensorID == IS_SENSOR_UI1013XC)
    {
        /* set m_bJPEG to true, so RestoreColorModeSettings can choose the correct color mode */
        if (m_SensorInfo.SensorID == IS_SENSOR_XS)
        {
            m_bJPEG = true;
        }
        // reset colormode radio button
        RestoreColorModeSettings();
        RestoreXsSettings();
        RestoreFormatsXs();
    }
    else
    {   // reset colormode radio button
        RestoreColorModeSettings();
    }

    RefreshPage ();

    m_pDlgMainView->SetupCapture();
    m_pDlgMainView->SetupTitles();

    if (wasLive)
        is_CaptureVideo (m_hCamera, IS_DONT_WAIT);
}

void properties::eventreceived (int event)
{
    if(isVisible())
    {
        switch (event)
        {
        case IS_SET_EVENT_WB_FINISHED:
            //printf ("event WB finished detected\n");
            UpdateWBCtrls ();
            break;

        default:
            break;
        }
    }
}

void properties::OnUpdateLive(bool bLive)
{
    m_bLive = bLive;
}

void properties::ApplyBinningSettings(int binningMode, int nMode)
{
    INT ret = IS_SUCCESS;
    int currentBinning = is_SetBinning (m_hCamera, IS_GET_BINNING);
    if ((ret = is_SetBinning (m_hCamera, binningMode | nMode)) != IS_SUCCESS)
    {
        qDebug("error - SetBinning: %d", ret);
    }

    int newBinning = is_SetBinning (m_hCamera, IS_GET_BINNING);
    if((nMode == IS_BINNING_DISABLE) && (currentBinning == newBinning))
    {

        // the binning nMode IS_BINNING_DISABLE was expected, but the device
        // did not changed the format, disable binning.
        if ((ret = is_SetBinning (m_hCamera, IS_BINNING_DISABLE)) != IS_SUCCESS)
        {
            qDebug("error - SetBinning: %d", ret);
        }
    }
}

void properties::ApplySubsamplingSettings(int subsamplingMode, int nMode)
{
    INT ret = IS_SUCCESS;
    int currentSubsampling = is_SetSubSampling(m_hCamera, IS_GET_SUBSAMPLING);
    if ((ret = is_SetSubSampling (m_hCamera, subsamplingMode | nMode)) != IS_SUCCESS)
    {
        qDebug("error - SetSubSampling: %d", ret);
    }

    int newSubsampling = is_SetSubSampling(m_hCamera, IS_GET_SUBSAMPLING);
    if((nMode == IS_SUBSAMPLING_DISABLE) && (currentSubsampling == newSubsampling))
    {
        // the subsampling nMode IS_SUBSAMPLING_DISABLE was expected, but the device
        // did not changed the format, disable subsampling.
        if ((ret = is_SetSubSampling (m_hCamera, IS_SUBSAMPLING_DISABLE)) != IS_SUCCESS)
        {
            qDebug("error - SetSubSampling: %d", ret);
        }
    }
}
