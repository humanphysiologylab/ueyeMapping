/********************************************************************************
** Form generated from reading UI file 'histogram.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAM_H
#define UI_HISTOGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Histogram
{
public:
    QLabel *labelHistogram;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *histogramLabel0;
    QLabel *histogramLabel128;
    QLabel *histogramLabel255;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayoutActions;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayoutChannels;
    QCheckBox *checkBoxHistogramRed;
    QCheckBox *checkBoxHistogramGreen;
    QCheckBox *checkBoxHistogramBlue;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *Histogram)
    {
        if (Histogram->objectName().isEmpty())
            Histogram->setObjectName(QStringLiteral("Histogram"));
        Histogram->resize(570, 320);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Histogram->sizePolicy().hasHeightForWidth());
        Histogram->setSizePolicy(sizePolicy);
        labelHistogram = new QLabel(Histogram);
        labelHistogram->setObjectName(QStringLiteral("labelHistogram"));
        labelHistogram->setGeometry(QRect(20, 20, 420, 260));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelHistogram->sizePolicy().hasHeightForWidth());
        labelHistogram->setSizePolicy(sizePolicy1);
        labelHistogram->setAutoFillBackground(false);
        labelHistogram->setFrameShape(QFrame::Panel);
        labelHistogram->setFrameShadow(QFrame::Sunken);
        labelHistogram->setLineWidth(1);
        labelHistogram->setAlignment(Qt::AlignCenter);
        labelHistogram->setIndent(-1);
        horizontalLayoutWidget = new QWidget(Histogram);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(19, 279, 421, 21));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        histogramLabel0 = new QLabel(horizontalLayoutWidget);
        histogramLabel0->setObjectName(QStringLiteral("histogramLabel0"));
        histogramLabel0->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(histogramLabel0);

        histogramLabel128 = new QLabel(horizontalLayoutWidget);
        histogramLabel128->setObjectName(QStringLiteral("histogramLabel128"));
        histogramLabel128->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        horizontalLayout->addWidget(histogramLabel128);

        histogramLabel255 = new QLabel(horizontalLayoutWidget);
        histogramLabel255->setObjectName(QStringLiteral("histogramLabel255"));
        histogramLabel255->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        horizontalLayout->addWidget(histogramLabel255);

        verticalLayoutWidget_2 = new QWidget(Histogram);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(450, 20, 101, 281));
        verticalLayoutActions = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayoutActions->setObjectName(QStringLiteral("verticalLayoutActions"));
        verticalLayoutActions->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(verticalLayoutWidget_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 128));
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 30, 81, 80));
        verticalLayoutChannels = new QVBoxLayout(verticalLayoutWidget);
        verticalLayoutChannels->setObjectName(QStringLiteral("verticalLayoutChannels"));
        verticalLayoutChannels->setContentsMargins(0, 0, 0, 0);
        checkBoxHistogramRed = new QCheckBox(verticalLayoutWidget);
        checkBoxHistogramRed->setObjectName(QStringLiteral("checkBoxHistogramRed"));
        checkBoxHistogramRed->setChecked(true);

        verticalLayoutChannels->addWidget(checkBoxHistogramRed);

        checkBoxHistogramGreen = new QCheckBox(verticalLayoutWidget);
        checkBoxHistogramGreen->setObjectName(QStringLiteral("checkBoxHistogramGreen"));
        checkBoxHistogramGreen->setChecked(true);

        verticalLayoutChannels->addWidget(checkBoxHistogramGreen);

        checkBoxHistogramBlue = new QCheckBox(verticalLayoutWidget);
        checkBoxHistogramBlue->setObjectName(QStringLiteral("checkBoxHistogramBlue"));
        checkBoxHistogramBlue->setChecked(true);

        verticalLayoutChannels->addWidget(checkBoxHistogramBlue);


        verticalLayoutActions->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayoutActions->addItem(verticalSpacer);

        pushButtonClose = new QPushButton(verticalLayoutWidget_2);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));

        verticalLayoutActions->addWidget(pushButtonClose);


        retranslateUi(Histogram);

        QMetaObject::connectSlotsByName(Histogram);
    } // setupUi

    void retranslateUi(QDialog *Histogram)
    {
        Histogram->setWindowTitle(QApplication::translate("Histogram", "Dialog", Q_NULLPTR));
        labelHistogram->setText(QApplication::translate("Histogram", "Histogram Placeholder", Q_NULLPTR));
        histogramLabel0->setText(QApplication::translate("Histogram", "0", Q_NULLPTR));
        histogramLabel128->setText(QApplication::translate("Histogram", "128", Q_NULLPTR));
        histogramLabel255->setText(QApplication::translate("Histogram", "255", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Histogram", "Channels", Q_NULLPTR));
        checkBoxHistogramRed->setText(QApplication::translate("Histogram", "Red", Q_NULLPTR));
        checkBoxHistogramGreen->setText(QApplication::translate("Histogram", "Green", Q_NULLPTR));
        checkBoxHistogramBlue->setText(QApplication::translate("Histogram", "Blue", Q_NULLPTR));
        pushButtonClose->setText(QApplication::translate("Histogram", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Histogram: public Ui_Histogram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAM_H
