/********************************************************************************
** Form generated from reading UI file 'imageinfodlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEINFODLG_H
#define UI_IMAGEINFODLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imageinfodlgClass
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_1;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_total;
    QPushButton *pBReset;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_4;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QLabel *label_14;
    QLineEdit *lineEdit_Reconnects;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QLabel *label_13;
    QProgressBar *progress_ImageBuffers;
    QLineEdit *lineEdit_ImageBuffers;
    QLineEdit *lineEdit_ImageBuffersInUse;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QLineEdit *lineEdit_MissingPackets;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *imageinfodlgClass)
    {
        if (imageinfodlgClass->objectName().isEmpty())
            imageinfodlgClass->setObjectName(QStringLiteral("imageinfodlgClass"));
        imageinfodlgClass->resize(363, 815);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageinfodlgClass->sizePolicy().hasHeightForWidth());
        imageinfodlgClass->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(imageinfodlgClass);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox = new QGroupBox(imageinfodlgClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_1 = new QLineEdit(groupBox);
        lineEdit_1->setObjectName(QStringLiteral("lineEdit_1"));
        lineEdit_1->setEnabled(true);
        lineEdit_1->setReadOnly(true);

        gridLayout->addWidget(lineEdit_1, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEnabled(true);
        lineEdit_2->setReadOnly(true);

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setEnabled(true);
        lineEdit_3->setReadOnly(true);

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setEnabled(true);
        lineEdit_6->setReadOnly(true);

        gridLayout->addWidget(lineEdit_6, 5, 1, 1, 1);

        lineEdit_9 = new QLineEdit(groupBox);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setEnabled(true);
        lineEdit_9->setReadOnly(true);

        gridLayout->addWidget(lineEdit_9, 8, 1, 1, 1);

        lineEdit_total = new QLineEdit(groupBox);
        lineEdit_total->setObjectName(QStringLiteral("lineEdit_total"));
        lineEdit_total->setEnabled(true);
        lineEdit_total->setReadOnly(true);

        gridLayout->addWidget(lineEdit_total, 9, 1, 1, 1);

        pBReset = new QPushButton(groupBox);
        pBReset->setObjectName(QStringLiteral("pBReset"));

        gridLayout->addWidget(pBReset, 12, 1, 1, 1);

        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setEnabled(true);
        lineEdit_5->setReadOnly(true);

        gridLayout->addWidget(lineEdit_5, 4, 1, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setEnabled(true);
        lineEdit_4->setReadOnly(true);

        gridLayout->addWidget(lineEdit_4, 3, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setEnabled(true);
        lineEdit_7->setReadOnly(true);

        gridLayout->addWidget(lineEdit_7, 6, 1, 1, 1);

        lineEdit_8 = new QLineEdit(groupBox);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setEnabled(true);
        lineEdit_8->setReadOnly(true);

        gridLayout->addWidget(lineEdit_8, 7, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 6, 0, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 7, 0, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 8, 0, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 9, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(imageinfodlgClass);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_5->addWidget(label_14, 0, 0, 1, 1);

        lineEdit_Reconnects = new QLineEdit(groupBox_4);
        lineEdit_Reconnects->setObjectName(QStringLiteral("lineEdit_Reconnects"));
        lineEdit_Reconnects->setEnabled(true);
        lineEdit_Reconnects->setReadOnly(true);

        gridLayout_5->addWidget(lineEdit_Reconnects, 0, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(imageinfodlgClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 30));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 1, 0, 1, 1);

        progress_ImageBuffers = new QProgressBar(groupBox_2);
        progress_ImageBuffers->setObjectName(QStringLiteral("progress_ImageBuffers"));
        progress_ImageBuffers->setValue(24);

        gridLayout_2->addWidget(progress_ImageBuffers, 2, 0, 1, 2);

        lineEdit_ImageBuffers = new QLineEdit(groupBox_2);
        lineEdit_ImageBuffers->setObjectName(QStringLiteral("lineEdit_ImageBuffers"));
        lineEdit_ImageBuffers->setEnabled(true);
        lineEdit_ImageBuffers->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_ImageBuffers, 0, 1, 1, 1);

        lineEdit_ImageBuffersInUse = new QLineEdit(groupBox_2);
        lineEdit_ImageBuffersInUse->setObjectName(QStringLiteral("lineEdit_ImageBuffersInUse"));
        lineEdit_ImageBuffersInUse->setEnabled(true);
        lineEdit_ImageBuffersInUse->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_ImageBuffersInUse, 1, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(imageinfodlgClass);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 40));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_3->addWidget(label_8, 0, 0, 1, 1);

        lineEdit_MissingPackets = new QLineEdit(groupBox_3);
        lineEdit_MissingPackets->setObjectName(QStringLiteral("lineEdit_MissingPackets"));
        lineEdit_MissingPackets->setEnabled(true);
        lineEdit_MissingPackets->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_MissingPackets, 0, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(imageinfodlgClass);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        gridLayout_4->addWidget(buttonBox, 4, 0, 1, 1);


        retranslateUi(imageinfodlgClass);

        QMetaObject::connectSlotsByName(imageinfodlgClass);
    } // setupUi

    void retranslateUi(QWidget *imageinfodlgClass)
    {
        imageinfodlgClass->setWindowTitle(QApplication::translate("imageinfodlgClass", "imageinfodlg", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("imageinfodlgClass", "Capture errors", Q_NULLPTR));
        label->setText(QApplication::translate("imageinfodlgClass", "API no destination memory", Q_NULLPTR));
        label_2->setText(QApplication::translate("imageinfodlgClass", "API conversion failed", Q_NULLPTR));
        label_3->setText(QApplication::translate("imageinfodlgClass", "API image locked", Q_NULLPTR));
        pBReset->setText(QApplication::translate("imageinfodlgClass", "Reset", Q_NULLPTR));
        label_6->setText(QApplication::translate("imageinfodlgClass", "DRV out of buffers", Q_NULLPTR));
        label_5->setText(QApplication::translate("imageinfodlgClass", "DRV device not ready", Q_NULLPTR));
        label_4->setText(QApplication::translate("imageinfodlgClass", "USB transfer failed", Q_NULLPTR));
        label_9->setText(QApplication::translate("imageinfodlgClass", "DEV timeout", Q_NULLPTR));
        label_10->setText(QApplication::translate("imageinfodlgClass", "ETH buffer overflow", Q_NULLPTR));
        label_11->setText(QApplication::translate("imageinfodlgClass", "Missed images", Q_NULLPTR));
        label_12->setText(QApplication::translate("imageinfodlgClass", "Total errors", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("imageinfodlgClass", "Device reconnects", Q_NULLPTR));
        label_14->setText(QApplication::translate("imageinfodlgClass", "Reconnects", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("imageinfodlgClass", "Camera image buffers", Q_NULLPTR));
        label_7->setText(QApplication::translate("imageinfodlgClass", "Number of image buffers", Q_NULLPTR));
        label_13->setText(QApplication::translate("imageinfodlgClass", "Used image buffers", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("imageinfodlgClass", "Resent packets", Q_NULLPTR));
        label_8->setText(QApplication::translate("imageinfodlgClass", "Number of packets", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class imageinfodlgClass: public Ui_imageinfodlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEINFODLG_H
