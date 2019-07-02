/********************************************************************************
** Form generated from reading UI file 'mainview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainviewClass
{
public:
    QAction *actionOpenCamera;
    QAction *actionCloseCamera;
    QAction *actionSave_image;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionSnapshot;
    QAction *actionLive;
    QAction *actionMonochrome;
    QAction *actionColor;
    QAction *actionDisplay;
    QAction *actionProperties;
    QAction *actionView_Fit;
    QAction *actionTrigger;
    QAction *actionOriginal_size;
    QAction *actionHalf_size;
    QAction *actionQuarter_size;
    QAction *actionDouble_size;
    QAction *actionForceCameralist;
    QAction *actionUseErrorReport;
    QAction *actionImageinfo;
    QAction *actionOpenCameraStop;
    QAction *actionLimitDisplayRate;
    QAction *actionResetCamera;
    QAction *actionLoadParamsFromFile;
    QAction *actionLoadParameterSet;
    QAction *actionLoadParameterSet2;
    QAction *actionSaveParameterToFile;
    QAction *actionSaveParameterSet;
    QAction *actionSaveParameterSet2;
    QAction *actionLoad_image;
    QAction *actionHistogram;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menuLoad_parameter;
    QMenu *menuSave_parameter;
    QMenu *menuUEye;
    QMenu *menu;
    QMenu *menuView;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QToolBar *toolBar_display;

    void setupUi(QMainWindow *MainviewClass)
    {
        if (MainviewClass->objectName().isEmpty())
            MainviewClass->setObjectName(QStringLiteral("MainviewClass"));
        MainviewClass->setEnabled(true);
        MainviewClass->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/images/ueye_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainviewClass->setWindowIcon(icon);
        MainviewClass->setAutoFillBackground(false);
        MainviewClass->setToolButtonStyle(Qt::ToolButtonIconOnly);
        actionOpenCamera = new QAction(MainviewClass);
        actionOpenCamera->setObjectName(QStringLiteral("actionOpenCamera"));
        actionOpenCamera->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/images/openplay.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenCamera->setIcon(icon1);
        actionCloseCamera = new QAction(MainviewClass);
        actionCloseCamera->setObjectName(QStringLiteral("actionCloseCamera"));
        actionCloseCamera->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/images/camclose.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCloseCamera->setIcon(icon2);
        actionSave_image = new QAction(MainviewClass);
        actionSave_image->setObjectName(QStringLiteral("actionSave_image"));
        actionSave_image->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_image->setIcon(icon3);
        actionAbout = new QAction(MainviewClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/images/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon4);
        actionExit = new QAction(MainviewClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/prefix1/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon5);
        actionSnapshot = new QAction(MainviewClass);
        actionSnapshot->setObjectName(QStringLiteral("actionSnapshot"));
        actionSnapshot->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/prefix1/images/media_pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSnapshot->setIcon(icon6);
        actionLive = new QAction(MainviewClass);
        actionLive->setObjectName(QStringLiteral("actionLive"));
        actionLive->setCheckable(true);
        actionLive->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/prefix1/images/media_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLive->setIcon(icon7);
        actionMonochrome = new QAction(MainviewClass);
        actionMonochrome->setObjectName(QStringLiteral("actionMonochrome"));
        actionMonochrome->setCheckable(true);
        actionColor = new QAction(MainviewClass);
        actionColor->setObjectName(QStringLiteral("actionColor"));
        actionColor->setCheckable(true);
        actionDisplay = new QAction(MainviewClass);
        actionDisplay->setObjectName(QStringLiteral("actionDisplay"));
        actionDisplay->setCheckable(true);
        actionDisplay->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/prefix2/images/display_no.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisplay->setIcon(icon8);
        actionProperties = new QAction(MainviewClass);
        actionProperties->setObjectName(QStringLiteral("actionProperties"));
        actionProperties->setEnabled(false);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/new/prefix1/images/properties.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProperties->setIcon(icon9);
        actionView_Fit = new QAction(MainviewClass);
        actionView_Fit->setObjectName(QStringLiteral("actionView_Fit"));
        actionView_Fit->setCheckable(true);
        actionView_Fit->setChecked(true);
        actionView_Fit->setEnabled(false);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/new/prefix2/images/display_fit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionView_Fit->setIcon(icon10);
        actionTrigger = new QAction(MainviewClass);
        actionTrigger->setObjectName(QStringLiteral("actionTrigger"));
        actionTrigger->setCheckable(true);
        actionOriginal_size = new QAction(MainviewClass);
        actionOriginal_size->setObjectName(QStringLiteral("actionOriginal_size"));
        actionOriginal_size->setCheckable(true);
        actionOriginal_size->setEnabled(false);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/new/prefix2/images/display_1-1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOriginal_size->setIcon(icon11);
        actionHalf_size = new QAction(MainviewClass);
        actionHalf_size->setObjectName(QStringLiteral("actionHalf_size"));
        actionHalf_size->setCheckable(true);
        actionHalf_size->setEnabled(false);
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/new/prefix2/images/display_1-2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHalf_size->setIcon(icon12);
        actionQuarter_size = new QAction(MainviewClass);
        actionQuarter_size->setObjectName(QStringLiteral("actionQuarter_size"));
        actionQuarter_size->setCheckable(true);
        actionQuarter_size->setEnabled(false);
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/new/prefix2/images/display_1-4.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuarter_size->setIcon(icon13);
        actionDouble_size = new QAction(MainviewClass);
        actionDouble_size->setObjectName(QStringLiteral("actionDouble_size"));
        actionDouble_size->setCheckable(true);
        actionDouble_size->setEnabled(false);
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/new/prefix2/images/display_2-1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDouble_size->setIcon(icon14);
        actionForceCameralist = new QAction(MainviewClass);
        actionForceCameralist->setObjectName(QStringLiteral("actionForceCameralist"));
        actionForceCameralist->setCheckable(true);
        actionUseErrorReport = new QAction(MainviewClass);
        actionUseErrorReport->setObjectName(QStringLiteral("actionUseErrorReport"));
        actionUseErrorReport->setCheckable(true);
        actionImageinfo = new QAction(MainviewClass);
        actionImageinfo->setObjectName(QStringLiteral("actionImageinfo"));
        actionImageinfo->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/new/prefix1/images/imageplus.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImageinfo->setIcon(icon15);
        actionOpenCameraStop = new QAction(MainviewClass);
        actionOpenCameraStop->setObjectName(QStringLiteral("actionOpenCameraStop"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/new/prefix1/images/openstop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenCameraStop->setIcon(icon16);
        actionLimitDisplayRate = new QAction(MainviewClass);
        actionLimitDisplayRate->setObjectName(QStringLiteral("actionLimitDisplayRate"));
        actionLimitDisplayRate->setCheckable(true);
        actionLimitDisplayRate->setEnabled(false);
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/new/prefix1/images/display_rate_limit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLimitDisplayRate->setIcon(icon17);
        actionResetCamera = new QAction(MainviewClass);
        actionResetCamera->setObjectName(QStringLiteral("actionResetCamera"));
        actionLoadParamsFromFile = new QAction(MainviewClass);
        actionLoadParamsFromFile->setObjectName(QStringLiteral("actionLoadParamsFromFile"));
        actionLoadParameterSet = new QAction(MainviewClass);
        actionLoadParameterSet->setObjectName(QStringLiteral("actionLoadParameterSet"));
        actionLoadParameterSet2 = new QAction(MainviewClass);
        actionLoadParameterSet2->setObjectName(QStringLiteral("actionLoadParameterSet2"));
        actionSaveParameterToFile = new QAction(MainviewClass);
        actionSaveParameterToFile->setObjectName(QStringLiteral("actionSaveParameterToFile"));
        actionSaveParameterSet = new QAction(MainviewClass);
        actionSaveParameterSet->setObjectName(QStringLiteral("actionSaveParameterSet"));
        actionSaveParameterSet2 = new QAction(MainviewClass);
        actionSaveParameterSet2->setObjectName(QStringLiteral("actionSaveParameterSet2"));
        actionLoad_image = new QAction(MainviewClass);
        actionLoad_image->setObjectName(QStringLiteral("actionLoad_image"));
        actionLoad_image->setEnabled(false);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/new/prefix1/images/load_image.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_image->setIcon(icon18);
        actionHistogram = new QAction(MainviewClass);
        actionHistogram->setObjectName(QStringLiteral("actionHistogram"));
        actionHistogram->setCheckable(true);
        centralwidget = new QWidget(MainviewClass);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainviewClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainviewClass);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 30));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menuLoad_parameter = new QMenu(menu_File);
        menuLoad_parameter->setObjectName(QStringLiteral("menuLoad_parameter"));
        menuSave_parameter = new QMenu(menu_File);
        menuSave_parameter->setObjectName(QStringLiteral("menuSave_parameter"));
        menuUEye = new QMenu(menubar);
        menuUEye->setObjectName(QStringLiteral("menuUEye"));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainviewClass->setMenuBar(menubar);
        statusbar = new QStatusBar(MainviewClass);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainviewClass->setStatusBar(statusbar);
        toolBar = new QToolBar(MainviewClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainviewClass->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_display = new QToolBar(MainviewClass);
        toolBar_display->setObjectName(QStringLiteral("toolBar_display"));
        MainviewClass->addToolBar(Qt::TopToolBarArea, toolBar_display);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menuUEye->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menu->menuAction());
        menu_File->addAction(menuLoad_parameter->menuAction());
        menu_File->addAction(menuSave_parameter->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(actionSave_image);
        menu_File->addAction(actionLoad_image);
        menu_File->addSeparator();
        menu_File->addAction(actionExit);
        menuLoad_parameter->addAction(actionLoadParamsFromFile);
        menuLoad_parameter->addAction(actionLoadParameterSet);
        menuSave_parameter->addAction(actionSaveParameterToFile);
        menuSave_parameter->addAction(actionSaveParameterSet);
        menuUEye->addAction(actionOpenCamera);
        menuUEye->addAction(actionOpenCameraStop);
        menuUEye->addAction(actionCloseCamera);
        menuUEye->addAction(actionResetCamera);
        menuUEye->addAction(actionForceCameralist);
        menuUEye->addSeparator();
        menuUEye->addAction(actionSnapshot);
        menuUEye->addAction(actionLive);
        menuUEye->addAction(actionTrigger);
        menuUEye->addSeparator();
        menuUEye->addAction(actionUseErrorReport);
        menuUEye->addAction(actionProperties);
        menu->addAction(actionAbout);
        menu->addSeparator();
        menuView->addAction(actionDisplay);
        menuView->addSeparator();
        menuView->addAction(actionView_Fit);
        menuView->addAction(actionOriginal_size);
        menuView->addAction(actionHalf_size);
        menuView->addAction(actionQuarter_size);
        menuView->addAction(actionDouble_size);
        menuView->addSeparator();
        menuView->addAction(actionLimitDisplayRate);
        menuView->addSeparator();
        menuView->addAction(actionHistogram);
        menuView->addAction(actionImageinfo);
        toolBar->addAction(actionOpenCamera);
        toolBar->addAction(actionOpenCameraStop);
        toolBar->addAction(actionCloseCamera);
        toolBar->addSeparator();
        toolBar->addAction(actionSnapshot);
        toolBar->addAction(actionLive);
        toolBar->addSeparator();
        toolBar->addAction(actionSave_image);
        toolBar->addAction(actionLoad_image);
        toolBar->addAction(actionProperties);
        toolBar->addAction(actionImageinfo);
        toolBar_display->addAction(actionDisplay);
        toolBar_display->addAction(actionView_Fit);
        toolBar_display->addAction(actionOriginal_size);
        toolBar_display->addAction(actionHalf_size);
        toolBar_display->addAction(actionQuarter_size);
        toolBar_display->addAction(actionDouble_size);
        toolBar_display->addSeparator();
        toolBar_display->addAction(actionLimitDisplayRate);

        retranslateUi(MainviewClass);

        QMetaObject::connectSlotsByName(MainviewClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainviewClass)
    {
        MainviewClass->setWindowTitle(QApplication::translate("MainviewClass", "uEye Demo", Q_NULLPTR));
        actionOpenCamera->setText(QApplication::translate("MainviewClass", "&open camera live", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpenCamera->setToolTip(QApplication::translate("MainviewClass", "open a uEye and start live", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionOpenCamera->setStatusTip(QApplication::translate("MainviewClass", "open a uEye", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionCloseCamera->setText(QApplication::translate("MainviewClass", "&close camera", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCloseCamera->setToolTip(QApplication::translate("MainviewClass", "close a uEye", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionCloseCamera->setStatusTip(QApplication::translate("MainviewClass", "close a uEye", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionSave_image->setText(QApplication::translate("MainviewClass", "save &image", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainviewClass", "&about uEye Demo", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainviewClass", "&exit", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainviewClass", "close the demo", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionExit->setStatusTip(QApplication::translate("MainviewClass", "close the demo", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("MainviewClass", "Alt+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSnapshot->setText(QApplication::translate("MainviewClass", "&Snapshot", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionSnapshot->setShortcut(QApplication::translate("MainviewClass", "Alt+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionLive->setText(QApplication::translate("MainviewClass", "Start &live", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionLive->setToolTip(QApplication::translate("MainviewClass", "Start/Stop live capture", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionLive->setShortcut(QApplication::translate("MainviewClass", "Alt+L", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMonochrome->setText(QApplication::translate("MainviewClass", "monochrome", Q_NULLPTR));
        actionColor->setText(QApplication::translate("MainviewClass", "color", Q_NULLPTR));
        actionDisplay->setText(QApplication::translate("MainviewClass", "&no display", Q_NULLPTR));
        actionProperties->setText(QApplication::translate("MainviewClass", "&Properties", Q_NULLPTR));
        actionView_Fit->setText(QApplication::translate("MainviewClass", "&fit to window", Q_NULLPTR));
        actionTrigger->setText(QApplication::translate("MainviewClass", "&use HW trigger", Q_NULLPTR));
        actionOriginal_size->setText(QApplication::translate("MainviewClass", "&original size", Q_NULLPTR));
        actionHalf_size->setText(QApplication::translate("MainviewClass", "&half size", Q_NULLPTR));
        actionQuarter_size->setText(QApplication::translate("MainviewClass", "&quarter size", Q_NULLPTR));
        actionDouble_size->setText(QApplication::translate("MainviewClass", "&double size", Q_NULLPTR));
        actionForceCameralist->setText(QApplication::translate("MainviewClass", "&force cameralist", Q_NULLPTR));
        actionUseErrorReport->setText(QApplication::translate("MainviewClass", "use API &error report", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionUseErrorReport->setToolTip(QApplication::translate("MainviewClass", "api error report", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionImageinfo->setText(QApplication::translate("MainviewClass", "&Imageinfo", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionImageinfo->setToolTip(QApplication::translate("MainviewClass", "show/hide additional image infos", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionOpenCameraStop->setText(QApplication::translate("MainviewClass", "ope&n camera stop", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpenCameraStop->setToolTip(QApplication::translate("MainviewClass", "open a uEye stopped", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLimitDisplayRate->setText(QApplication::translate("MainviewClass", "&limit display rate", Q_NULLPTR));
        actionResetCamera->setText(QApplication::translate("MainviewClass", "&Reset to defaults", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionResetCamera->setToolTip(QApplication::translate("MainviewClass", "resets the camera to its default parameters", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLoadParamsFromFile->setText(QApplication::translate("MainviewClass", "&from file...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionLoadParamsFromFile->setToolTip(QApplication::translate("MainviewClass", "load camera parameter from a configuration file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLoadParameterSet->setText(QApplication::translate("MainviewClass", "&Parameter set", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionLoadParameterSet->setToolTip(QApplication::translate("MainviewClass", "load camera parameter from camera set 1", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLoadParameterSet2->setText(QApplication::translate("MainviewClass", "Parameter set 2", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionLoadParameterSet2->setToolTip(QApplication::translate("MainviewClass", "load camera parameter from camera set 2", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSaveParameterToFile->setText(QApplication::translate("MainviewClass", "&to file...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSaveParameterToFile->setToolTip(QApplication::translate("MainviewClass", "save camera parameter to camera configuration file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSaveParameterSet->setText(QApplication::translate("MainviewClass", "&Parameter set", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSaveParameterSet->setToolTip(QApplication::translate("MainviewClass", "save camera parameter to camera set 1", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSaveParameterSet2->setText(QApplication::translate("MainviewClass", "Parameter set 2", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSaveParameterSet2->setToolTip(QApplication::translate("MainviewClass", "save camera parameter to camera set 2", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLoad_image->setText(QApplication::translate("MainviewClass", "l&oad image", Q_NULLPTR));
        actionHistogram->setText(QApplication::translate("MainviewClass", "Histogram", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionHistogram->setToolTip(QApplication::translate("MainviewClass", "Histogram", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        menu_File->setTitle(QApplication::translate("MainviewClass", "&File", Q_NULLPTR));
        menuLoad_parameter->setTitle(QApplication::translate("MainviewClass", "&load parameter", Q_NULLPTR));
        menuSave_parameter->setTitle(QApplication::translate("MainviewClass", "&save parameter", Q_NULLPTR));
        menuUEye->setTitle(QApplication::translate("MainviewClass", "&uEye", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainviewClass", "?", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainviewClass", "&View", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainviewClass", "toolBar", Q_NULLPTR));
        toolBar_display->setWindowTitle(QApplication::translate("MainviewClass", "toolBar_2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainviewClass: public Ui_MainviewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
