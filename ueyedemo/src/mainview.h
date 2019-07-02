/*!
 * \file    mainview.h
 * \date    12.01.2010
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   MainWindow class declaration of the Qt uEye demo
 *
 * \par Last modified
 *
 * \li  22.09.2010 - cma - change QuEyeSdiDemo to uEyeDemo
 */

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "ui_mainview.h"
#include <ueye.h>
#include "properties.h"
#include "eventthread.h"
#include "cameralist.h"
#include "imageinfodlg.h"


#include "qtui.h"
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QColor>
#include <QPainter>
#include <QRadioButton>
#include <QGroupBox>
#include <QSize>
#include <QPoint>
#include <QLayout>
#include <QThread>
#include <QMutex>
#include <QUrl>
#include <QRgb>
#include <QCloseEvent>
#include <QTimerEvent>
#include <QWidget>
#include <QProgressBar>
#include <QTimer>
#include <QTime>
#include <QScrollArea>
#include <QScrollBar>
#include <QVector>
#include "paintlabel.h"
#include "histogram.h"

class properties;
class PaintLabel;

class WorkerThread;

/*!
 * \defgroup MAINVIEW Mainview implementation
 * \{
 * \defgroup MAINVIEWCAMERAHANDLING uEye camera handling
 * \defgroup MAINVIEWDIALOG Mainview dialog items
 * \defgroup EVENTHANDLING app eventhandling
 * \defgroup UEYEEVENTHANDLING uEye event handling
 * \defgroup WORKTRHEADHANDLING handling heavy duty work
 */

/*!
 * \brief Number of image buffer to alloc
 */
#define IMAGE_COUNT     5

/*!
 * \brief default value for max displayed frames per sec
 */
#define UPDATE_TICKS    30

/*!
 * \brief uEye Image parameter structure
 */
typedef struct _UEYE_IMAGE
{
    char *pBuf;
    INT nImageID;
    INT nImageSeqNum;
    INT nBufferSize;
} UEYE_IMAGE, *PUEYE_IMAGE;

/*!
 * \brief supported display scale formats
 */
enum eDisplayMode
{
    display_no = 0, //!< display_no
    display_fit, //!< display_fit
    display_original,//!< display_original
    display_half, //!< display_half
    display_quarter, //!< display_quarter
    display_double
//!< display_double
};

/*!
 * \ingroup WORKTRHEADHANDLING
 * \brief worker thread job enumaration */
enum eWorkerJob
{
    wj_none = 0,
    wj_cameraopen = 1,
    wj_cameraopenlive = 2,
    wj_camerareopen
};

/*! \brief image buffer properties structure */
struct sBufferProps
{
    int width;
    int height;
    int colorformat;
    int bitspp;
    QImage::Format imgformat;
    QRgb *pRgbTable;
    int tableentries;
    int imageformat;

};

/*! \brief camera feature properties structure */
struct sCameraProps
{
    bool bUsesImageFormats;
    int nImgFmtNormal;
    int nImgFmtDefaultNormal;
    int nImgFmtTrigger;
    int nImgFmtDefaultTrigger;

};

/*!
 * \brief MainWindow class declaration
 */
class Mainview:public QMainWindow, public Ui::MainviewClass
{
Q_OBJECT

public:
    /*!
     * \brief standard constructor for the MainWindow object
     * \param parent        Qt parent object
     * \param strStartID    Select the device ID to open
     */
    Mainview (QWidget *parent = 0, QString strStartID = "");
    /*!
     * \brief standard destructor
     */
    virtual ~Mainview ();
    /*!
     * \ingroup WORKTRHEADHANDLING
     * \brief workerthread run function
     */
    void run();
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief returns the number of an image buffer
     * \param pbuf image buffer pointer
     * \return according image number if successful, 0 otherwise
     */
    INT _GetImageNum (char* pbuf);

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief frees all image buffers
     */
    void _FreeImages ();
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief clears all image buffer contents
     */
    void _EmptyImages ();
    /*!
     * \brief returns the ID of an image buffer
     * \param pbuf image buffer pointer
     * \return according image ID if successful, 0 otherwise
     */
    INT _GetImageID (char* pbuf);
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief creates all needed imagebuffers
     * \return  true if successful, false otherwise
     */
    bool _AllocImages ();
    /*!
     * \brief returns the curretn camera handle
     */
    HIDS getCameraHandle() { return m_hCamera; }
    /*! \brief returns the bits per pixel for each color format */
    int GetBitsPerPixel(int colormode);

    void startLive();
    void stopLive();

    WORD* getHotpixelList();
    UINT getHotpixelListSize();
    bool getMarkHotpixel();
    INT getCurrentAOI(IS_RECT* rectAOI);
    DWORD getMaxSensorWidth();
    DWORD getMaxSensorHeight();

signals:
    void adaptiveHotpixelNumberDetectedChanged(int);
    void adaptiveHotpixelPercentDetectedChanged(double);

    /*
     * public mainview class slots
     */
public slots:
    /*!
     * \brief shows the demo about dialog
     */
    void about ();

    /*!
     * \ingroup UEYEEVENTHANDLING
     * \brief uEye event receive slot function
     * \param event been signaled
     */
    void eventreceived (int event);

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief opens / closes the ueye cameras
     */
    void onOpenCamera();
    void onOpenCameraLive();
    void onCloseCamera();

    /*! \brief setups the capture process */
    int SetupCapture();

    /*! \brief setup the Titles */
    void SetupTitles();

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief starts/stops ueye live capture
     */
    void onLive ();

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief capture
     */
    void onSnapshot ();

    /*! \brief initialize new camera colormode and converter */
    //int ChangeColorFormat(int colormode, int colorconverter);

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief save the actual uEye image
     */
    void onSaveImage ();
    

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief loads an image and display it
     */
    void onLoadImage();

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief resets the camera to its default values
     */
    void onResetCamera();
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief imports an camera parameter file
     * \param action triggered menu action
     */
    void onLoadParameter (QAction* action);

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief exports the actual camera parameter to a file
     * \param action triggered menu action
     */
    void onSaveParameter (QAction* action);

    /*! ingroup MAINVIEWCAMERAHANDLING
     * \brief prepares the LoadParameter Menu
     */
    void onPrepareLoadParameter();

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief shows the camera property dialog
     */
    void onProperties ();

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief use external triggers for capture images
     */
    void onUseTrigger ();

    /*!
     * \brief changes the display scale format
     */
    void onDisplay ();

    /*!
     * \brief Enable/Disbale the API error report
     */
    void onApiErrorReport();

    /*!
     * \brief Show/hide the Image Info Dialog
     */
    void onImageInfo();

    /*!
     * \brief Imageinfo timeout slot
     */
    void onImageInfoUpdate();

    /*!
     * \brief enable/disable display rate limit
     */
    void onLimitDisplayRate();

    void closeHistogram();

    void onHistogram(bool show);

    void setMarkHotpixel(bool);

protected:
    void closeEvent (QCloseEvent * e);
    /*!
     * \ingroup EVENTHANDLING
     * \brief overloads parents 'paintEvent' function
     * \param e pointer to Qt paint event
     */
    void paintEvent (QPaintEvent *e);
    /*!
     * \ingroup MAINVIEWDIALOG
     * \brief clears the statusbar info
     */
    void ClearStatusbarInfo();
    /*!
     * \ingroup MAINVIEWDIALOG
     * \brief updates the fps display in the statusbar
     * \param fps new frames per second value
     */
    void UpdateFps (double fps);
    /*!
     * \ingroup MAINVIEWDIALOG
     * \brief updates the frame counter display in the statusbar
     */
    void UpdateCounters ();
    /*!
     * \ingroup MAINVIEWDIALOG
     * \brief updates the mainwindow control elements
     */
    void UpdateControls ();

private:
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    /*!
     * \ingroup MAINVIEWDIALOG
     * \brief creates the mainwindow status bar
     */
    void createStatusBar ();
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief uEye image process function
     */
    void ProcessFrame ();
    /*!
     * \brief uEye image draw/display function
     * \param pBuffer pointer to image buffer to draw
     */
    void DrawImage (char *pBuffer);
    /*!
     * \ingroup WORKTRHEADHANDLING
     * \brief initialize the worker thread
     * \return true if success, otherwise false
     */
    bool prepareWorkThread();
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief function to call when a camera was initialized through the work thread to
     *        finish the initializing work
     * \return ids error code (int)
     */
    int CameraInitialized();

    int openCamera (bool bStartLive);
    int reOpenCamera();

    int searchDefImageFormats(int suppportMask);
    /*!
     * \brief Saves the position and window states
     */
    void writeSettings();
    /*!
     * \brief Reeads the position and window states
     */
    void readSettings();
    /*!
     * \brief Initialize the Passive-Multicast
     */
    void initPassiveMulticast();
    /*
     * private mainview class slots
     */
private slots:
    /*!
     * \ingroup WORKTRHEADHANDLING
     * \brief callback slot when worker thread started
     */
    void workThreadStarted();
    /*!
     * \ingroup WORKTRHEADHANDLING
     * * \brief callback slot when worker thread stopped
     */
    void workThreadFinished();
    /*! \brief update progressbar slot */
    void updateProgress();

private:
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief pointer on a camera list class object
     */
    CameraList *pDlgCamerList;
    /*!
     * \brief pointer on a imageinfodlg class object
     */
    imageinfodlg *m_pImageInfoDlg;
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief uEye frame buffer array
     */
    UEYE_IMAGE m_Images[IMAGE_COUNT];
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief uEye camera handle
     */
    HIDS m_hCamera;
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief uEye camera info structmember
     */
    CAMINFO m_CamInfo; // Camera (Board)info
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief uEye CameraList struct member
     */
    UEYE_CAMERA_INFO m_CamListInfo;
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief uEye sensor info struct member */
    SENSORINFO m_SensorInfo; // SensorInfo
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief  holds the uEye sensor width */
    int m_nWidth;
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief holds the uEye sensor height */
    int m_nHeight;
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief holds the current display scale format */
    eDisplayMode m_eDispMode;
    bool m_bReady;
    char *m_pLastBuffer;

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief used color mode */
    int m_nColorMode;
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief Colorindex table for monochrom pictures */
    QRgb m_table[256];
    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \brief display images switch */
    bool m_bDisplayImage;

    /*!
     * \ingroup MAINVIEWCAMERAHANDLING
     * \defgroup CAPTURESTATUS capture status indicators
     * \{
     */
    bool m_bLive;               //!< \brief live indicator
    unsigned long nReceived;    //!< \brief current received frames
    unsigned long nFailed;      //!< \brief current count of failed transfers
    unsigned long nDisplayed;    //!< \brief current displayed images

    bool m_bReopenLive;            //!< \brief live indicator during reopen process
    /*!
     * \}
     */ /* end CAPTURESTATUS */

    /*!
     * \ingroup UEYEEVENTHANDLING
     * \brief DEVICE_REMOVE Event waiting thread member
     */
    EventThread *m_pEvDevremove;
    /*!
     * \ingroup UEYEEVENTHANDLING
     * \brief DEVICE_NEW Event waiting thread member
     */
    EventThread *m_pEvDevnew;
    /*!
     * \ingroup UEYEEVENTHANDLING
     * \brief STATUS_CHANGED Event waiting thread member
     */
    EventThread *m_pEvDevStateChanged;
    /*!
     * \ingroup UEYEEVENTHANDLING
     * \brief FRAME Event waiting thread member
     */
    EventThread *m_pEvFrame;
    /*!
     * \ingroup UEYEEVENTHANDLING
     * \brief TRANSFER_FAILED Event waiting thread member
     */
    EventThread *m_pEvTransferFailed;

    /*!
     * \ingroup UEYEEVENTHANDLING
     * \brief DEVICE_RECONNECTED Event waiting thread member
     */
    EventThread *m_pEvDeviceReconnected;

    /*!
     * \ingroup UEYEEVENTHANDLING
     * \brief PMC Image Changed Event waiting thread member
     */
    EventThread *m_pEvPMCImageChanged;

    /*!
     * \ingroup MAINVIEWDIALOG
     * \brief pointer to the child view object
     */
    PaintLabel *m_imageLabel;
    QScrollArea *m_scrollArea;

    /*!
     * \ingroup MAINVIEWDIALOG
     * \defgroup STATUSBAR Status bar text labels
     * \brief statusbar text labels
     * \{
     */
    QLabel *textStatus;
    QLabel *textStatus_2;
    QLabel *textStatus_3_0;
    QLabel *textStatus_3_1;
    QLabel *textStatus_3_2;
    QLabel *textStatus_3_3;
    QLabel *textStatus_4;
    /*!
     * \}
     */ /* end STATUSBAR */

    /*!
     * \ingroup WORKTRHEADHANDLING
     * \brief workerthread jobnumber
     */
    int m_workthread_jobNumber;

    /*!
     * \ingroup WORKTRHEADHANDLING
     * \brief workerthread jobnumber
     */
    eWorkerJob m_eWorkthreadJob;

    /*!
         * \ingroup WORKTRHEADHANDLING
         * \brief workerthread return value
         */
    int m_workthreadReturn;

    /*!
     * \ingroup WORKTRHEADHANDLING
     * \brief worker thread member
     */
    WorkerThread *m_workThread;

    /*!
     * \ingroup WORKTRHEADHANDLING
     * \brief progress indicator
     */
    QProgressBar *m_pProgBar;

    /*!\ingroup WORKTRHEADHANDLING
     * \brief progress indicator text
     */
    QLabel *m_pProgText;

    /*! \brief flag to show if automatic fw upload is used */
    bool m_bAutomaticSEStarterUpload;

    /*! \brief misc timer */
    QTimer *m_pTimer;

    /*! \brief Property dialog */
    properties *m_pPropertiesDlg;

    /*! \brief misc time variable */
    QTime m_Time;
    int m_nUpdateTicks;

    Histogram* m_pHistogramDlg;

    bool m_bMarkHotpixel;
    WORD* m_nHotpixelList;
    UINT m_nHotpixelListSize;
    INT m_nAdaptiveHotpixelNumberDetected = 0;
    double m_nAdaptiveHotpixelPercentDetected = 0;

public:
    struct sBufferProps m_BufferProps;
    struct sCameraProps m_CameraProps;


};


/*!
 * \brief workerthread class declaration
 */
class WorkerThread : public QThread
{
  Q_OBJECT
public:
  WorkerThread(Mainview *mainWindow)
    : mainWindow(mainWindow){};
  virtual ~WorkerThread(){};

  void run() {mainWindow->run();}
protected:
  Mainview *mainWindow;
};

/*!
 * \}
 */// end of doc group MAINVIEW
/*!
 * \mainpage
 * The uEye demo is a demonstration application for most uEye camera features. It provides
 * access to camera parameters and allows capturing of single images and image streams.
 *
 * \section VERSION version history
 *  \par V1.19.3
 *  \li  bugfix Mantis 2923: check software gamma support within initTabImage(), cause "XS" has no sw gamma support
 *  \par V1.19.2
 *  \li  changed some slotnames and connect them manually, cause of problems with auto signal-slot connection by name
 *  \par V1.19.1
 *  \li  add XS image stabilization enable on "XS" Tab
 *  \par V1.19.0
 *  \li  add special uEye XS features on "XS" Tab
 *  \par V1.18.3
 *  \li  bugfix using function is_GetActSeqBuf. It is strongly recommended to initialize the function parameter
 *  with valid values. The unused parameters should be "0", cause they could be processed internally.
 *  \par V1.18.2
 *  \li  add new property tab page for control of image size formats
 *  \par V1.18.1
 *  \li  bugfix some errors with colormodes and size controls for XS support
 *  \par V1.18.0
 *  \li  only workable with libueye_api.so.3.61
 *  \li  UI1008XS Implementation
 *  \par V1.17.1 RC2
 *  \li  bugfix: reenable display when closing and opening a camera
 *  \par V1.17.0 RC2
 *  \li  show ids ueye logo in mainview background, when no camera is open
 *  \li  added Demo desktop icons to icon folder
 *  \par V1.16.2 RC2
 *  \li  save image is now possible also when camera is capturing
 *  \par V1.16.1 RC2
 *  \li  add new ids demo icons
 *  \li  change display rate limit to 30 fps
 *  \par V1.16.0 RC2
 *  \li  add load/save camera parameter using the internal memory
 *  \par V1.15.9 RC2
 *  \li  SetupCapture don't start/stop the live capture anymore to avoid problems with the live button status
 *  \par V1.15.8 RC2
 *  \li  the minimum flash delay is now also set to '0'.
 *  \par V1.15.7 RC2
 *  \li  display view button is set to default 'fit' with a new opened camera.
 *  \li  add error checking for loading camera parameter files
 *  \li  Load and save Parameter file is now also possible when camera is capturing
 *  \li  add functionality to reset the camera to its defaults
 *  \par V1.15.6 RC2
 *  \li  set the property flash slider pagesteps to factor 200.
 *  \li  now the flash duration 0 is the minimum, followed by the minimum till the maximum.
 *  \par V1.15.5 RC2
 *  \li  avoid live display flickering when enter the size property tab.
 *  \par V1.15.4 RC2
 *  \li  keyboard input for camera timing controls is now possible.
 *  \par V1.15.3 RC2
 *  \li  release version don't show debug output anymore
 *  \li  imageprocessing tab in property page will be refreshed correctly now
 *  \par V1.15.2 RC2
 *  \li  AOI size adjustment is checked against minimum image size when using binning, subsampling now
 *  \par V1.15.1 RC2
 *  \li  removed keyboard tracking for all size spinbox edit fields. So the spinbox doesn't emit the valueChanged()
 *       signal while typing. It emits the signal later, when the return key is pressed, when keyboard focus is lost,
 *       or when other spinbox functionality is used, e.g. pressing an arrow key
 *  \li  The OK button at the bottom of the property dialog is any more the default button.
 *       So its possible now to enter a new AOI size in the spinbox edit control and finish editing with the enter key.
 *  \par V1.15.0 RC2
 *  \li  add display rate limit and display counter in statusbar
 *  \li  add color format tab in property page, to change the camera image color format
 *  \par V1.14.0 RC2
 *  \li  use flash modes also in freerun mode with new freerun FLASH MODES
 *  \li  use a QScrollArea and a QLabel as paint view.
 *  \li  disable buttons to open a new camera, when opening is in progress.
 *  \par V1.13.2 RC2
 *  \li  reset camera to defaults after opening
 *  \li  set 24bit RGB packed as standard color format
 *  \par V1.13.1 RC2
 *  \li  images will be resized now, when new parameter file is loaded.
 *  \par V1.13.0 RC2
 *  \li  fix problem with Mono/Color Binnig/Subsampling
 *  \li  use new is_SetAOI instead of old is_SetImageSize/Pos
 *  \li  add 6x-8x binning and 6x-16x subsampling at camera property page
 *  \li  fix some GUI stuff
 *  \li  images can now be saved as bmp, lpeg and png
 *  \par V1.12.2 RC2
 *  \li  Give a filename at save image dialog.
 *  \li  reset imageinfo dialog controls on creation
 *  \par V1.12.0 RC2
 *  \li  The current image buffers were now reallocated when a size change is made.
 *       So display and save show now only the AOI data.
 *  \li  add new icons
 *  \li  use new QSliderEx class with slackness for property image size handling to update
 *       image size not with each slider value.
 *  \par V1.11.1
 *  \li  Fix typo in property dialog.
 *  \par V1.11.0 RC1
 *  \li  Automatic firmware upload supported now for SE
 *  \par V1.10.2
 *  \li  bugfix: use new 'IS_INVALID_HIDS' instead of 'NULL' for HIDS compare
 *  \par V1.10.1
 *  \li  bugfix: don't reset imageinfo dialog contents when shown!
 *  \par V1.10.0
 *  \li  add possibility to start camera live or in stop mode
 *  \li  bugfix: patch UpdateControls() for new UEYEIMAGEINFO struct definition in uEye.h
 *  \par V1.9.0 Beta
 *  \li  add modeless imageinfo dlg to see additional image infos
 *  \par V1.8.0 Beta
 *  \li  add commandline option -s\<deviceid\> to start a camera at startup
 *  \par V1.7.3 Beta
 *  \li  bugfix: Status counters were now also updated with event IS_SET_EVNET_TRANSFER_FAILED.
 *  \li  trigger mode now activates the new continuous trigger.
 *  \par V1.7.2 Beta
 *  \li  bugfix: Dialog Save shows now "Save" instead of "Open"
 *  \li  bugfix: color testimages will be blocked with Monocameras
 *  \li  bugfix: failed counter shows now correct capture failed counts
 *  \par V1.7.1 Beta
 *  \li  bugfix: with abort of the cameralist, no camera will be opened anymore
 *  \li  bugfix: API Version textlabel should not be overwritten
 *  \li  bugfix: the uEye Black testimage is now shown.
 *  \par V1.7 Beta
 *  \li  removed memoryboard support, cause it is no more supported with SDK3.40
 *  \li  api error report could be used from the menu to track errors. (On Linux this
 *       errors are only visible when started the demo from the console!)
 *  \li  framerate and exposure are no also adjustable with keyboard and spin control
 *  \par V1.6 Beta
 *  \li  added new SDK3.40 event support IS_SET_EVENT_STATUS_CHANGED
 *  \li  added library version check
 *  \par V1.5 Beta --> released with uEye_3.31Beta
 *  \li  default use no splash, cause not all distributions show this splash correctly
 *  \par V1.4 Beta
 *  \li  added demo version in titlebar
 *  \li  added a splash screen. Use cmd line argument "nosplash" to not see the splash.
 *  \li  new Menu item "uEye->force cameralist" to always force the cameralist to open
 *  \li  Bugfix: when cancel the cameralist no camera will be opened.
 *  \li  Bugfix: when only one camera is plugged and no cameralist is forced, this
 *       camera will be opened
 *  \par V1.3 Beta
 *  \li  statusbar shows now a progressbar indicator, when opening a camera.
 *  \li  cameras will now run automatically when opened
 *  \par V1.2 Beta
 *  \li  statusbar shows now "camera open" message as action indicator, cause the
 *       open process is very long.
 *  \par V1.1 Beta
 *  \li Added cameralist to select a camera to open
 *
 * \section REQUIREMENTS Requirements
 * \subsection SOFTWARE Software requirements
 * \li libc/glibc, the standard C Library (min. v2)
 * \li POSIX threads library (POSIX threads enabled libc)
 * \li Qt4 library, at least Qt 4.4.3
 * \li Qt4 build tools (e.g. qmake)
 *
 * Versions prior to Qt 4.4.3 might also work, but they are untested. We suggest to
 * download the latest Qt4 version from http://www.qtsoftware.com/downloads
 *
 * \section BUILD Build uEyeDemo
 *
 * We recommend to create a copy of the source files in a working directory, so you won't have
 * to be root to build uEyeDemo.
 *
 * a - Locate the proper version of qmake in case you have installed multiple Qt4 versions
 * b - Copy the source files to a working directory, for example ~/uEyeDemo:
 * \code
 * $> cp -R /usr/src/ids/uEyeDemo ~/uEyeDemo
 * \endcode
 * c - Go to the build directory
 * \code
 * $> cd ~/uEyeDemo
 * \endcode
 * c - Run qmake (use explicit binary path if the proper qmake version is not in your $PATH
 * \code
 * $> qmake
 * \endcode
 * d - Build the application
 * \code
 * $> make
 * \endcode
 *
 * The uEyeDemo should compile without errors. After successful build, the binary can be found
 * at the top of the previously choosed working directory. To install, simply copy the binary to
 * /usr/bin or adjust your $PATH environment variable.
 *
 * \section STARTQUSD Start uEyeDemo
 * Start the demo application either from the command line or via your graphical desktop
 * environment. To start fom console, type
 * \code
 * ./uEyeDemo
 * \endcode
 * from the build directory.
 *
 * \section USEQUSD Use uEyeDemo
 * \subsection OPENCAM Open a camera
 * When first started, uEyeDemo has no camera opened. Click on the appropriate menu bar item or
 * choose <em>uEye - Open camera</em> to open a camera. If there are multiple cameras present, a
 * camera list is displayed showing the known cameras and their availability.
 * \subsection CAPTUREIMG Capture images
 * After successfully opening a camera, uEyeDemo provides the possibility to either
 *   - take image snapshots
 *   - set the camera to freerun mode
 *   - or capture images hardware triggered
 * \subsection SAVEIMAGE Save a camera image
 * It is also possible to save the current camera image to a Bitmap with a click on the appropriate
 * menu bar item.
 * \subsection CAMPARAMFILES Camera parameter files
 * One may store camera settings applied via uEyeDemo in an external file for later use. These
 * files may be stored via <em>File - save parameter</em> and loaded via <em>File - load parameter</em>.
 * \subsection CAMPROPERTIES Camera properties
 * A properties dialog provides access to the camera parameters that may be applied via the uEye API.
 * Klick on the appropriate icon to open the parameter dialog. If the camera is in freerun mode,
 * parameter changes will be applied immediately.
 */
#endif // MAINVIEW_H
