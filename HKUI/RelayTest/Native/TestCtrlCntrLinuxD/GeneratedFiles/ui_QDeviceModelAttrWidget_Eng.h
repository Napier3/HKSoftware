/********************************************************************************
** Form generated from reading UI file 'QDeviceModelAttrWidget_Eng.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QDEVICEMODELATTRWIDGET_ENG_H
#define UI_QDEVICEMODELATTRWIDGET_ENG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QDeviceModelAttrWidget_Eng
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_10;
    QLabel *label_20;
    QLabel *label_22;
    QCheckBox *checkBox;
    QLabel *label_21;
    QLineEdit *m_editVNom3;
    QLabel *label_23;
    QLineEdit *m_editIPRIM2;
    QLabel *label_19;
    QLabel *label_24;
    QLineEdit *m_editVPrimLL3;
    QComboBox *comboBox_2;
    QComboBox *comboBox;
    QLineEdit *m_editINom2;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_11;
    QLabel *label_25;
    QLineEdit *m_editVMaxLL;
    QLabel *label_26;
    QLineEdit *m_editIMax;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_12;
    QRadioButton *m_radCustomize;
    QRadioButton *m_radHigh;
    QLineEdit *m_editOverloadSupTime;
    QRadioButton *m_radLow;
    QRadioButton *m_radDisconnect;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_13;
    QLabel *label_28;
    QLabel *label_27;
    QLineEdit *m_editDeBounceTime;
    QLineEdit *m_editDeGlitchTime;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QLabel *label_3;
    QLineEdit *m_editBackTime;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_8;
    QLabel *label_10;
    QLineEdit *m_editSubstation;
    QLabel *label_11;
    QLineEdit *m_editSubstatioAddress;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_9;
    QLabel *label_12;
    QLineEdit *m_editBay;
    QLabel *label_13;
    QLineEdit *m_editBayAddress;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QLabel *label;
    QLineEdit *m_editDeviceMode;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *m_editManufacturer;
    QLineEdit *m_editDeviceType;
    QLineEdit *m_editDeviceAddress;
    QLineEdit *m_editSerialnr;
    QLineEdit *m_editProtectedObjectName;
    QLineEdit *m_editAdditionalINF02;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_6;
    QLineEdit *m_editFNom;
    QRadioButton *m_radPhases3;
    QLabel *label_2;
    QLineEdit *m_editVPrimLL;
    QLabel *label_14;
    QLabel *label_17;
    QLabel *label_15;
    QRadioButton *m_radPhases2;
    QLineEdit *m_editINom;
    QLineEdit *m_editVPrimLL2;
    QLabel *label_16;
    QLineEdit *m_editIPRIM;
    QLineEdit *m_editVNom2;
    QLabel *label_18;
    QLineEdit *m_editVNom;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;

    void setupUi(QWidget *QDeviceModelAttrWidget_Eng)
    {
        if (QDeviceModelAttrWidget_Eng->objectName().isEmpty())
            QDeviceModelAttrWidget_Eng->setObjectName(QString::fromUtf8("QDeviceModelAttrWidget_Eng"));
        QDeviceModelAttrWidget_Eng->setWindowModality(Qt::WindowModal);
        QDeviceModelAttrWidget_Eng->resize(1280, 940);
        QDeviceModelAttrWidget_Eng->setMinimumSize(QSize(1200, 614));
        QDeviceModelAttrWidget_Eng->setMaximumSize(QSize(16777215, 16000));
        gridLayout = new QGridLayout(QDeviceModelAttrWidget_Eng);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(QDeviceModelAttrWidget_Eng);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 845));
        tabWidget->setMaximumSize(QSize(16777215, 946));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(430, 250, 440, 431));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        groupBox_5->setMinimumSize(QSize(0, 0));
        groupBox_5->setMaximumSize(QSize(16777, 16777215));
        gridLayout_10 = new QGridLayout(groupBox_5);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(5, -1, 5, -1);
        label_20 = new QLabel(groupBox_5);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMaximumSize(QSize(90, 16777215));
        label_20->setWordWrap(true);

        gridLayout_10->addWidget(label_20, 1, 0, 1, 1);

        label_22 = new QLabel(groupBox_5);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setMaximumSize(QSize(16777215, 16));
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_22, 3, 1, 1, 1);

        checkBox = new QCheckBox(groupBox_5);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setMaximumSize(QSize(141, 16777215));

        gridLayout_10->addWidget(checkBox, 2, 0, 1, 1);

        label_21 = new QLabel(groupBox_5);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_10->addWidget(label_21, 4, 0, 1, 1);

        m_editVNom3 = new QLineEdit(groupBox_5);
        m_editVNom3->setObjectName(QString::fromUtf8("m_editVNom3"));
        m_editVNom3->setMinimumSize(QSize(147, 0));
        m_editVNom3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(m_editVNom3, 4, 2, 1, 1);

        label_23 = new QLabel(groupBox_5);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_23, 3, 2, 1, 1);

        m_editIPRIM2 = new QLineEdit(groupBox_5);
        m_editIPRIM2->setObjectName(QString::fromUtf8("m_editIPRIM2"));
        m_editIPRIM2->setMinimumSize(QSize(147, 0));
        m_editIPRIM2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(m_editIPRIM2, 5, 1, 1, 1);

        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setMinimumSize(QSize(0, 50));
        label_19->setMaximumSize(QSize(90, 16777215));
        label_19->setAutoFillBackground(false);
        label_19->setWordWrap(true);

        gridLayout_10->addWidget(label_19, 0, 0, 1, 1);

        label_24 = new QLabel(groupBox_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_10->addWidget(label_24, 5, 0, 1, 1);

        m_editVPrimLL3 = new QLineEdit(groupBox_5);
        m_editVPrimLL3->setObjectName(QString::fromUtf8("m_editVPrimLL3"));
        m_editVPrimLL3->setMinimumSize(QSize(147, 0));
        m_editVPrimLL3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(m_editVPrimLL3, 4, 1, 1, 1);

        comboBox_2 = new QComboBox(groupBox_5);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(147, 0));
        comboBox_2->setMaximumSize(QSize(1677, 16777215));

        gridLayout_10->addWidget(comboBox_2, 1, 2, 1, 1);

        comboBox = new QComboBox(groupBox_5);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(147, 0));

        gridLayout_10->addWidget(comboBox, 0, 2, 1, 1);

        m_editINom2 = new QLineEdit(groupBox_5);
        m_editINom2->setObjectName(QString::fromUtf8("m_editINom2"));
        m_editINom2->setMinimumSize(QSize(147, 0));
        m_editINom2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(m_editINom2, 5, 2, 1, 1);

        groupBox_7 = new QGroupBox(tab);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(900, 140, 400, 130));
        groupBox_7->setMinimumSize(QSize(0, 0));
        groupBox_7->setMaximumSize(QSize(1677, 16777215));
        groupBox_7->setBaseSize(QSize(500, 0));
        gridLayout_11 = new QGridLayout(groupBox_7);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_25 = new QLabel(groupBox_7);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setMinimumSize(QSize(45, 0));
        label_25->setMaximumSize(QSize(121, 16777215));

        gridLayout_11->addWidget(label_25, 0, 0, 1, 1);

        m_editVMaxLL = new QLineEdit(groupBox_7);
        m_editVMaxLL->setObjectName(QString::fromUtf8("m_editVMaxLL"));
        m_editVMaxLL->setMinimumSize(QSize(0, 0));
        m_editVMaxLL->setMaximumSize(QSize(150, 16777215));
        m_editVMaxLL->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(m_editVMaxLL, 0, 1, 1, 1);

        label_26 = new QLabel(groupBox_7);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setMinimumSize(QSize(45, 0));

        gridLayout_11->addWidget(label_26, 1, 0, 1, 1);

        m_editIMax = new QLineEdit(groupBox_7);
        m_editIMax->setObjectName(QString::fromUtf8("m_editIMax"));
        m_editIMax->setMinimumSize(QSize(0, 0));
        m_editIMax->setMaximumSize(QSize(150, 16777215));
        m_editIMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(m_editIMax, 1, 1, 1, 1);

        groupBox_8 = new QGroupBox(tab);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(890, 290, 400, 130));
        groupBox_8->setMinimumSize(QSize(0, 0));
        groupBox_8->setMaximumSize(QSize(1677, 16777215));
        groupBox_8->setBaseSize(QSize(500, 0));
        gridLayout_12 = new QGridLayout(groupBox_8);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        m_radCustomize = new QRadioButton(groupBox_8);
        m_radCustomize->setObjectName(QString::fromUtf8("m_radCustomize"));

        gridLayout_12->addWidget(m_radCustomize, 0, 1, 1, 1);

        m_radHigh = new QRadioButton(groupBox_8);
        m_radHigh->setObjectName(QString::fromUtf8("m_radHigh"));

        gridLayout_12->addWidget(m_radHigh, 0, 0, 1, 1);

        m_editOverloadSupTime = new QLineEdit(groupBox_8);
        m_editOverloadSupTime->setObjectName(QString::fromUtf8("m_editOverloadSupTime"));
        m_editOverloadSupTime->setMinimumSize(QSize(0, 0));
        m_editOverloadSupTime->setMaximumSize(QSize(240, 16777215));
        m_editOverloadSupTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_editOverloadSupTime->setDragEnabled(false);
        m_editOverloadSupTime->setReadOnly(false);

        gridLayout_12->addWidget(m_editOverloadSupTime, 0, 2, 1, 1);

        m_radLow = new QRadioButton(groupBox_8);
        m_radLow->setObjectName(QString::fromUtf8("m_radLow"));

        gridLayout_12->addWidget(m_radLow, 1, 0, 1, 1);

        m_radDisconnect = new QRadioButton(groupBox_8);
        m_radDisconnect->setObjectName(QString::fromUtf8("m_radDisconnect"));

        gridLayout_12->addWidget(m_radDisconnect, 1, 1, 1, 1);

        groupBox_9 = new QGroupBox(tab);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(900, 450, 400, 130));
        groupBox_9->setMinimumSize(QSize(0, 0));
        groupBox_9->setMaximumSize(QSize(1677, 16777215));
        gridLayout_13 = new QGridLayout(groupBox_9);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_28 = new QLabel(groupBox_9);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_13->addWidget(label_28, 1, 0, 1, 1);

        label_27 = new QLabel(groupBox_9);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setMaximumSize(QSize(121, 16777215));

        gridLayout_13->addWidget(label_27, 0, 0, 1, 1);

        m_editDeBounceTime = new QLineEdit(groupBox_9);
        m_editDeBounceTime->setObjectName(QString::fromUtf8("m_editDeBounceTime"));
        m_editDeBounceTime->setMinimumSize(QSize(0, 0));
        m_editDeBounceTime->setMaximumSize(QSize(150, 16777215));
        m_editDeBounceTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_13->addWidget(m_editDeBounceTime, 0, 1, 1, 1);

        m_editDeGlitchTime = new QLineEdit(groupBox_9);
        m_editDeGlitchTime->setObjectName(QString::fromUtf8("m_editDeGlitchTime"));
        m_editDeGlitchTime->setMaximumSize(QSize(150, 16777215));
        m_editDeGlitchTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_13->addWidget(m_editDeGlitchTime, 1, 1, 1, 1);

        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(900, 30, 400, 80));
        groupBox_6->setMinimumSize(QSize(0, 0));
        groupBox_6->setMaximumSize(QSize(1677, 16777215));
        groupBox_6->setBaseSize(QSize(500, 20));
        gridLayout_7 = new QGridLayout(groupBox_6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(121, 16777215));

        gridLayout_7->addWidget(label_3, 0, 0, 1, 1);

        m_editBackTime = new QLineEdit(groupBox_6);
        m_editBackTime->setObjectName(QString::fromUtf8("m_editBackTime"));
        m_editBackTime->setMinimumSize(QSize(0, 0));
        m_editBackTime->setMaximumSize(QSize(150, 16777215));
        m_editBackTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(m_editBackTime, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 550, 400, 105));
        groupBox_2->setMaximumSize(QSize(1677, 16777215));
        gridLayout_8 = new QGridLayout(groupBox_2);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(98, 0));
        label_10->setMaximumSize(QSize(117, 16777215));

        gridLayout_8->addWidget(label_10, 0, 0, 1, 1);

        m_editSubstation = new QLineEdit(groupBox_2);
        m_editSubstation->setObjectName(QString::fromUtf8("m_editSubstation"));
        m_editSubstation->setMinimumSize(QSize(0, 0));
        m_editSubstation->setMaximumSize(QSize(400, 16777215));

        gridLayout_8->addWidget(m_editSubstation, 0, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(98, 0));

        gridLayout_8->addWidget(label_11, 1, 0, 1, 1);

        m_editSubstatioAddress = new QLineEdit(groupBox_2);
        m_editSubstatioAddress->setObjectName(QString::fromUtf8("m_editSubstatioAddress"));
        m_editSubstatioAddress->setMinimumSize(QSize(0, 0));
        m_editSubstatioAddress->setMaximumSize(QSize(400, 16777215));

        gridLayout_8->addWidget(m_editSubstatioAddress, 1, 1, 1, 1);

        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 670, 400, 105));
        groupBox_3->setMinimumSize(QSize(246, 0));
        groupBox_3->setMaximumSize(QSize(1677, 16777215));
        gridLayout_9 = new QGridLayout(groupBox_3);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(98, 0));
        label_12->setMaximumSize(QSize(117, 16777215));

        gridLayout_9->addWidget(label_12, 0, 0, 1, 1);

        m_editBay = new QLineEdit(groupBox_3);
        m_editBay->setObjectName(QString::fromUtf8("m_editBay"));
        m_editBay->setMinimumSize(QSize(0, 0));
        m_editBay->setMaximumSize(QSize(400, 16777215));

        gridLayout_9->addWidget(m_editBay, 0, 1, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(98, 0));
        label_13->setMaximumSize(QSize(117, 16777215));

        gridLayout_9->addWidget(label_13, 1, 0, 1, 1);

        m_editBayAddress = new QLineEdit(groupBox_3);
        m_editBayAddress->setObjectName(QString::fromUtf8("m_editBayAddress"));
        m_editBayAddress->setMinimumSize(QSize(0, 0));
        m_editBayAddress->setMaximumSize(QSize(400, 16777215));

        gridLayout_9->addWidget(m_editBayAddress, 1, 1, 1, 1);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 400, 520));
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(1677, 16777215));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        m_editDeviceMode = new QLineEdit(groupBox);
        m_editDeviceMode->setObjectName(QString::fromUtf8("m_editDeviceMode"));
        m_editDeviceMode->setMaximumSize(QSize(400, 16777215));

        gridLayout_5->addWidget(m_editDeviceMode, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_5->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_5->addWidget(label_5, 2, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_5->addWidget(label_6, 3, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_5->addWidget(label_7, 4, 0, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 5, 0, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 6, 0, 1, 1);

        m_editManufacturer = new QLineEdit(groupBox);
        m_editManufacturer->setObjectName(QString::fromUtf8("m_editManufacturer"));
        m_editManufacturer->setMaximumSize(QSize(400, 16777215));

        gridLayout_5->addWidget(m_editManufacturer, 1, 1, 1, 1);

        m_editDeviceType = new QLineEdit(groupBox);
        m_editDeviceType->setObjectName(QString::fromUtf8("m_editDeviceType"));
        m_editDeviceType->setMaximumSize(QSize(400, 16777215));

        gridLayout_5->addWidget(m_editDeviceType, 2, 1, 1, 1);

        m_editDeviceAddress = new QLineEdit(groupBox);
        m_editDeviceAddress->setObjectName(QString::fromUtf8("m_editDeviceAddress"));
        m_editDeviceAddress->setMaximumSize(QSize(400, 16777215));

        gridLayout_5->addWidget(m_editDeviceAddress, 3, 1, 1, 1);

        m_editSerialnr = new QLineEdit(groupBox);
        m_editSerialnr->setObjectName(QString::fromUtf8("m_editSerialnr"));
        m_editSerialnr->setMaximumSize(QSize(400, 16777215));

        gridLayout_5->addWidget(m_editSerialnr, 4, 1, 1, 1);

        m_editProtectedObjectName = new QLineEdit(groupBox);
        m_editProtectedObjectName->setObjectName(QString::fromUtf8("m_editProtectedObjectName"));
        m_editProtectedObjectName->setMaximumSize(QSize(400, 16777215));

        gridLayout_5->addWidget(m_editProtectedObjectName, 5, 1, 1, 1);

        m_editAdditionalINF02 = new QLineEdit(groupBox);
        m_editAdditionalINF02->setObjectName(QString::fromUtf8("m_editAdditionalINF02"));
        m_editAdditionalINF02->setMaximumSize(QSize(400, 16777215));

        gridLayout_5->addWidget(m_editAdditionalINF02, 6, 1, 1, 1);

        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(440, 30, 440, 180));
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        groupBox_4->setMinimumSize(QSize(0, 0));
        groupBox_4->setMaximumSize(QSize(16777, 16777215));
        gridLayout_6 = new QGridLayout(groupBox_4);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(5, -1, 5, -1);
        m_editFNom = new QLineEdit(groupBox_4);
        m_editFNom->setObjectName(QString::fromUtf8("m_editFNom"));
        m_editFNom->setMinimumSize(QSize(147, 0));
        m_editFNom->setMaximumSize(QSize(16777, 16777215));
        m_editFNom->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(m_editFNom, 1, 1, 1, 1);

        m_radPhases3 = new QRadioButton(groupBox_4);
        m_radPhases3->setObjectName(QString::fromUtf8("m_radPhases3"));
        m_radPhases3->setLayoutDirection(Qt::LeftToRight);

        gridLayout_6->addWidget(m_radPhases3, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(102, 0));
        label_2->setMaximumSize(QSize(16777, 16777215));

        gridLayout_6->addWidget(label_2, 1, 0, 1, 1);

        m_editVPrimLL = new QLineEdit(groupBox_4);
        m_editVPrimLL->setObjectName(QString::fromUtf8("m_editVPrimLL"));
        m_editVPrimLL->setMinimumSize(QSize(147, 0));
        m_editVPrimLL->setMaximumSize(QSize(16777, 16777215));
        m_editVPrimLL->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(m_editVPrimLL, 3, 1, 1, 1);

        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(64, 16777215));

        gridLayout_6->addWidget(label_14, 0, 0, 1, 1);

        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_17, 2, 2, 1, 1);

        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMaximumSize(QSize(16777, 16777215));

        gridLayout_6->addWidget(label_15, 3, 0, 1, 1);

        m_radPhases2 = new QRadioButton(groupBox_4);
        m_radPhases2->setObjectName(QString::fromUtf8("m_radPhases2"));
        m_radPhases2->setLayoutDirection(Qt::LeftToRight);

        gridLayout_6->addWidget(m_radPhases2, 0, 1, 1, 1);

        m_editINom = new QLineEdit(groupBox_4);
        m_editINom->setObjectName(QString::fromUtf8("m_editINom"));
        m_editINom->setMinimumSize(QSize(147, 0));
        m_editINom->setMaximumSize(QSize(16777, 16777215));
        m_editINom->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(m_editINom, 5, 2, 1, 1);

        m_editVPrimLL2 = new QLineEdit(groupBox_4);
        m_editVPrimLL2->setObjectName(QString::fromUtf8("m_editVPrimLL2"));
        m_editVPrimLL2->setMinimumSize(QSize(147, 0));
        m_editVPrimLL2->setMaximumSize(QSize(16777, 16777215));
        m_editVPrimLL2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(m_editVPrimLL2, 4, 1, 1, 1);

        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMaximumSize(QSize(16777215, 16));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_16, 2, 1, 1, 1);

        m_editIPRIM = new QLineEdit(groupBox_4);
        m_editIPRIM->setObjectName(QString::fromUtf8("m_editIPRIM"));
        m_editIPRIM->setMinimumSize(QSize(147, 0));
        m_editIPRIM->setMaximumSize(QSize(16777, 16777215));
        m_editIPRIM->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(m_editIPRIM, 5, 1, 1, 1);

        m_editVNom2 = new QLineEdit(groupBox_4);
        m_editVNom2->setObjectName(QString::fromUtf8("m_editVNom2"));
        m_editVNom2->setMinimumSize(QSize(147, 0));
        m_editVNom2->setMaximumSize(QSize(16777, 16777215));
        m_editVNom2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(m_editVNom2, 4, 2, 1, 1);

        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setMinimumSize(QSize(64, 0));
        label_18->setMaximumSize(QSize(16777, 16777215));

        gridLayout_6->addWidget(label_18, 5, 0, 1, 1);

        m_editVNom = new QLineEdit(groupBox_4);
        m_editVNom->setObjectName(QString::fromUtf8("m_editVNom"));
        m_editVNom->setMinimumSize(QSize(147, 0));
        m_editVNom->setMaximumSize(QSize(16777, 16777215));
        m_editVNom->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(m_editVNom, 3, 2, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        widget = new QWidget(QDeviceModelAttrWidget_Eng);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnOK = new QPushButton(widget);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(widget);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);


        gridLayout->addWidget(widget, 1, 0, 1, 1);


        retranslateUi(QDeviceModelAttrWidget_Eng);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QDeviceModelAttrWidget_Eng);
    } // setupUi

    void retranslateUi(QWidget *QDeviceModelAttrWidget_Eng)
    {
        QDeviceModelAttrWidget_Eng->setWindowTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\233\266\345\272\217\347\224\265\345\216\213\345\222\214\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\233\266\345\272\217\347\224\265\346\265\201\n"
"\347\232\204\346\226\271\345\220\221\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\344\270\200\346\254\241", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\344\273\252\347\224\250\344\272\222\346\204\237\345\231\250", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\242\235\345\256\232\347\224\265\345\216\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\344\272\214\346\254\241", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\233\266\345\272\217\347\224\265\345\216\213\n"
"\347\232\204\346\226\271\345\220\221\357\274\232", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\242\235\345\256\232\347\224\265\346\265\201\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("QDeviceModelAttrWidget_Eng", "-3 * I0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDeviceModelAttrWidget_Eng", "3 * I0", 0, QApplication::UnicodeUTF8)
        );
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("QDeviceModelAttrWidget_Eng", "3 * V0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDeviceModelAttrWidget_Eng", "-3 * V0", 0, QApplication::UnicodeUTF8)
        );
        groupBox_7->setTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "\346\234\200\345\244\247\345\200\274\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "V max\357\274\232", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "I max\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "\350\277\207\350\275\275\346\243\200\346\265\213\347\201\265\346\225\217\345\272\246", 0, QApplication::UnicodeUTF8));
        m_radCustomize->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\350\207\252\345\256\232\344\271\211", 0, QApplication::UnicodeUTF8));
        m_radHigh->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\253\230", 0, QApplication::UnicodeUTF8));
        m_radLow->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\344\275\216", 0, QApplication::UnicodeUTF8));
        m_radDisconnect->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\346\226\255\345\274\200", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\230\262\346\212\226/\345\211\212\345\263\260\350\277\207\346\273\244", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\230\262\346\212\226\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\261\225\345\256\275\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\205\266\344\273\226\350\243\205\347\275\256\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\350\277\224\345\233\236\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\217\230\347\224\265\347\253\231", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\227\264\351\232\224", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "\350\243\205\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\220\215\347\247\260/\350\257\264\346\230\216\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\210\266\351\200\240\345\216\202\345\225\206\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\350\243\205\347\275\256\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\350\243\205\347\275\256\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\272\217\345\210\227\345\217\267/\345\236\213\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\231\204\345\212\240\344\277\241\346\201\2571\357\274\232", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\231\204\345\212\240\344\277\241\346\201\2572\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("QDeviceModelAttrWidget_Eng", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_radPhases3->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "3", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\242\235\345\256\232\351\242\221\347\216\207\357\274\232", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\347\233\270\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\344\272\214\346\254\241", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\242\235\345\256\232\347\224\265\345\216\213\357\274\232", 0, QApplication::UnicodeUTF8));
        m_radPhases2->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "2", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\344\270\200\346\254\241", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\351\242\235\345\256\232\347\224\265\346\265\201\357\274\232", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QDeviceModelAttrWidget_Eng", "\350\243\205\347\275\256\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDeviceModelAttrWidget_Eng", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDeviceModelAttrWidget_Eng: public Ui_QDeviceModelAttrWidget_Eng {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDEVICEMODELATTRWIDGET_ENG_H
