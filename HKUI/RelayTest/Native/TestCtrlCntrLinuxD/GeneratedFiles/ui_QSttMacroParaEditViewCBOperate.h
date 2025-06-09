/********************************************************************************
** Form generated from reading UI file 'QSttMacroParaEditViewCBOperate.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSTTMACROPARAEDITVIEWCBOPERATE_H
#define UI_QSTTMACROPARAEDITVIEWCBOPERATE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
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
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QSttMacroParaEditViewCBOperate
{
public:
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_pLabImpedanceWay;
    QRadioButton *m_pChkAmpAngle;
    QRadioButton *m_pChkRX;
    QSpacerItem *verticalSpacer_10;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *m_pLabFaultType;
    QComboBox *m_pCmbFaultType;
    QSpacerItem *verticalSpacer;
    QLabel *m_pLabZ;
    QSettingLineEdit *m_pEditZ;
    QSpacerItem *verticalSpacer_2;
    QLabel *m_pLabImpedanceAngle;
    QSettingLineEdit *m_pEditImpedanceAngle;
    QSpacerItem *verticalSpacer_3;
    QLabel *m_pLabCurShortCircuit;
    QLineEdit *m_pEditCurShortCircuit;
    QSpacerItem *verticalSpacer_4;
    QLabel *m_pLabVolShortCircuit;
    QLineEdit *m_pEditVolShortCircuit;
    QSpacerItem *verticalSpacer_5;
    QLabel *m_pLabFaultDirection;
    QComboBox *m_pCmbFaultDirection;
    QSpacerItem *verticalSpacer_6;
    QLabel *m_pLabFaultQuality;
    QComboBox *m_pCmbFaultQuality;
    QSpacerItem *verticalSpacer_7;
    QLabel *m_pLabLarFaultTime;
    QSettingLineEdit *m_pEditLarFaultTime;
    QCheckBox *m_pChkConversionFault;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_12;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_5;
    QLineEdit *m_pEditPowerAngleLoad;
    QLabel *m_pLabPowerAngleLoad;
    QLabel *m_pLabCurLoad;
    QLineEdit *m_pEditCurLoad;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *m_pLabRFaultDirection;
    QComboBox *m_pCmbRFaultDirection;
    QSettingLineEdit *m_pEditRImpedanceAngle;
    QLabel *m_pLabRZ;
    QLabel *m_pLabRImpedanceAngle;
    QLabel *m_pLabRFaultType;
    QComboBox *m_pCmbRFaultType;
    QLabel *m_pLabConversionTime;
    QLineEdit *m_pEditConversionTime;
    QSettingLineEdit *m_pEditRZ;
    QLabel *m_pLabRCurShortCircuit;
    QLineEdit *m_pEditRCurShortCircuit;
    QLabel *m_pLabRVolShortCircuit;
    QLineEdit *m_pEditRVolShortCircuit;
    QHBoxLayout *horizontalLayout;
    QLabel *m_pLabFaultTrigTime;
    QLineEdit *m_pEditHour;
    QLabel *m_pLabHour;
    QLineEdit *m_pEditMinute;
    QLabel *m_pLabMinute;
    QLineEdit *m_pEditSecond;
    QLabel *m_pLabSecond;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_pBtnCommonParas;
    QPushButton *m_pBtnResultAssess;
    QSpacerItem *verticalSpacer_11;

    void setupUi(QWidget *QSttMacroParaEditViewCBOperate)
    {
        if (QSttMacroParaEditViewCBOperate->objectName().isEmpty())
            QSttMacroParaEditViewCBOperate->setObjectName(QString::fromUtf8("QSttMacroParaEditViewCBOperate"));
        QSttMacroParaEditViewCBOperate->resize(987, 739);
        gridLayout_4 = new QGridLayout(QSttMacroParaEditViewCBOperate);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tabWidget = new QTabWidget(QSttMacroParaEditViewCBOperate);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(10, 5, -1, 5);
        m_pLabImpedanceWay = new QLabel(frame);
        m_pLabImpedanceWay->setObjectName(QString::fromUtf8("m_pLabImpedanceWay"));

        horizontalLayout_4->addWidget(m_pLabImpedanceWay);

        m_pChkAmpAngle = new QRadioButton(frame);
        m_pChkAmpAngle->setObjectName(QString::fromUtf8("m_pChkAmpAngle"));

        horizontalLayout_4->addWidget(m_pChkAmpAngle);

        m_pChkRX = new QRadioButton(frame);
        m_pChkRX->setObjectName(QString::fromUtf8("m_pChkRX"));

        horizontalLayout_4->addWidget(m_pChkRX);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_10, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(10);
        formLayout->setVerticalSpacing(10);
        formLayout->setContentsMargins(10, 0, 10, 0);
        m_pLabFaultType = new QLabel(frame);
        m_pLabFaultType->setObjectName(QString::fromUtf8("m_pLabFaultType"));

        formLayout->setWidget(0, QFormLayout::LabelRole, m_pLabFaultType);

        m_pCmbFaultType = new QComboBox(frame);
        m_pCmbFaultType->setObjectName(QString::fromUtf8("m_pCmbFaultType"));
        m_pCmbFaultType->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, m_pCmbFaultType);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(1, QFormLayout::FieldRole, verticalSpacer);

        m_pLabZ = new QLabel(frame);
        m_pLabZ->setObjectName(QString::fromUtf8("m_pLabZ"));

        formLayout->setWidget(2, QFormLayout::LabelRole, m_pLabZ);

        m_pEditZ = new QSettingLineEdit(frame);
        m_pEditZ->setObjectName(QString::fromUtf8("m_pEditZ"));
        m_pEditZ->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(2, QFormLayout::FieldRole, m_pEditZ);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::FieldRole, verticalSpacer_2);

        m_pLabImpedanceAngle = new QLabel(frame);
        m_pLabImpedanceAngle->setObjectName(QString::fromUtf8("m_pLabImpedanceAngle"));

        formLayout->setWidget(4, QFormLayout::LabelRole, m_pLabImpedanceAngle);

        m_pEditImpedanceAngle = new QSettingLineEdit(frame);
        m_pEditImpedanceAngle->setObjectName(QString::fromUtf8("m_pEditImpedanceAngle"));
        m_pEditImpedanceAngle->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(4, QFormLayout::FieldRole, m_pEditImpedanceAngle);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(5, QFormLayout::FieldRole, verticalSpacer_3);

        m_pLabCurShortCircuit = new QLabel(frame);
        m_pLabCurShortCircuit->setObjectName(QString::fromUtf8("m_pLabCurShortCircuit"));

        formLayout->setWidget(6, QFormLayout::LabelRole, m_pLabCurShortCircuit);

        m_pEditCurShortCircuit = new QLineEdit(frame);
        m_pEditCurShortCircuit->setObjectName(QString::fromUtf8("m_pEditCurShortCircuit"));
        m_pEditCurShortCircuit->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(6, QFormLayout::FieldRole, m_pEditCurShortCircuit);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(7, QFormLayout::FieldRole, verticalSpacer_4);

        m_pLabVolShortCircuit = new QLabel(frame);
        m_pLabVolShortCircuit->setObjectName(QString::fromUtf8("m_pLabVolShortCircuit"));

        formLayout->setWidget(8, QFormLayout::LabelRole, m_pLabVolShortCircuit);

        m_pEditVolShortCircuit = new QLineEdit(frame);
        m_pEditVolShortCircuit->setObjectName(QString::fromUtf8("m_pEditVolShortCircuit"));
        m_pEditVolShortCircuit->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(8, QFormLayout::FieldRole, m_pEditVolShortCircuit);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(9, QFormLayout::FieldRole, verticalSpacer_5);

        m_pLabFaultDirection = new QLabel(frame);
        m_pLabFaultDirection->setObjectName(QString::fromUtf8("m_pLabFaultDirection"));

        formLayout->setWidget(10, QFormLayout::LabelRole, m_pLabFaultDirection);

        m_pCmbFaultDirection = new QComboBox(frame);
        m_pCmbFaultDirection->setObjectName(QString::fromUtf8("m_pCmbFaultDirection"));
        m_pCmbFaultDirection->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(10, QFormLayout::FieldRole, m_pCmbFaultDirection);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(11, QFormLayout::FieldRole, verticalSpacer_6);

        m_pLabFaultQuality = new QLabel(frame);
        m_pLabFaultQuality->setObjectName(QString::fromUtf8("m_pLabFaultQuality"));

        formLayout->setWidget(12, QFormLayout::LabelRole, m_pLabFaultQuality);

        m_pCmbFaultQuality = new QComboBox(frame);
        m_pCmbFaultQuality->setObjectName(QString::fromUtf8("m_pCmbFaultQuality"));
        m_pCmbFaultQuality->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(12, QFormLayout::FieldRole, m_pCmbFaultQuality);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(13, QFormLayout::FieldRole, verticalSpacer_7);

        m_pLabLarFaultTime = new QLabel(frame);
        m_pLabLarFaultTime->setObjectName(QString::fromUtf8("m_pLabLarFaultTime"));

        formLayout->setWidget(14, QFormLayout::LabelRole, m_pLabLarFaultTime);

        m_pEditLarFaultTime = new QSettingLineEdit(frame);
        m_pEditLarFaultTime->setObjectName(QString::fromUtf8("m_pEditLarFaultTime"));
        m_pEditLarFaultTime->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(14, QFormLayout::FieldRole, m_pEditLarFaultTime);

        m_pChkConversionFault = new QCheckBox(frame);
        m_pChkConversionFault->setObjectName(QString::fromUtf8("m_pChkConversionFault"));

        formLayout->setWidget(16, QFormLayout::LabelRole, m_pChkConversionFault);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(16, QFormLayout::FieldRole, verticalSpacer_8);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(15, QFormLayout::FieldRole, verticalSpacer_9);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(17, QFormLayout::LabelRole, verticalSpacer_12);


        verticalLayout->addLayout(formLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setHorizontalSpacing(0);
        gridLayout_5->setVerticalSpacing(20);
        gridLayout_5->setContentsMargins(45, -1, 45, 0);
        m_pEditPowerAngleLoad = new QLineEdit(frame);
        m_pEditPowerAngleLoad->setObjectName(QString::fromUtf8("m_pEditPowerAngleLoad"));
        m_pEditPowerAngleLoad->setMaximumSize(QSize(150, 16777215));

        gridLayout_5->addWidget(m_pEditPowerAngleLoad, 1, 1, 1, 1);

        m_pLabPowerAngleLoad = new QLabel(frame);
        m_pLabPowerAngleLoad->setObjectName(QString::fromUtf8("m_pLabPowerAngleLoad"));

        gridLayout_5->addWidget(m_pLabPowerAngleLoad, 1, 0, 1, 1);

        m_pLabCurLoad = new QLabel(frame);
        m_pLabCurLoad->setObjectName(QString::fromUtf8("m_pLabCurLoad"));

        gridLayout_5->addWidget(m_pLabCurLoad, 0, 0, 1, 1);

        m_pEditCurLoad = new QLineEdit(frame);
        m_pEditCurLoad->setObjectName(QString::fromUtf8("m_pEditCurLoad"));
        m_pEditCurLoad->setMaximumSize(QSize(150, 16777215));

        gridLayout_5->addWidget(m_pEditCurLoad, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_5);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(30, 0, 30, 0);
        m_pLabRFaultDirection = new QLabel(groupBox);
        m_pLabRFaultDirection->setObjectName(QString::fromUtf8("m_pLabRFaultDirection"));

        gridLayout_2->addWidget(m_pLabRFaultDirection, 6, 0, 1, 1);

        m_pCmbRFaultDirection = new QComboBox(groupBox);
        m_pCmbRFaultDirection->setObjectName(QString::fromUtf8("m_pCmbRFaultDirection"));
        m_pCmbRFaultDirection->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_pCmbRFaultDirection, 6, 1, 1, 1);

        m_pEditRImpedanceAngle = new QSettingLineEdit(groupBox);
        m_pEditRImpedanceAngle->setObjectName(QString::fromUtf8("m_pEditRImpedanceAngle"));
        m_pEditRImpedanceAngle->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_pEditRImpedanceAngle, 3, 1, 1, 1);

        m_pLabRZ = new QLabel(groupBox);
        m_pLabRZ->setObjectName(QString::fromUtf8("m_pLabRZ"));

        gridLayout_2->addWidget(m_pLabRZ, 2, 0, 1, 1);

        m_pLabRImpedanceAngle = new QLabel(groupBox);
        m_pLabRImpedanceAngle->setObjectName(QString::fromUtf8("m_pLabRImpedanceAngle"));

        gridLayout_2->addWidget(m_pLabRImpedanceAngle, 3, 0, 1, 1);

        m_pLabRFaultType = new QLabel(groupBox);
        m_pLabRFaultType->setObjectName(QString::fromUtf8("m_pLabRFaultType"));

        gridLayout_2->addWidget(m_pLabRFaultType, 0, 0, 1, 1);

        m_pCmbRFaultType = new QComboBox(groupBox);
        m_pCmbRFaultType->setObjectName(QString::fromUtf8("m_pCmbRFaultType"));
        m_pCmbRFaultType->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_pCmbRFaultType, 0, 1, 1, 1);

        m_pLabConversionTime = new QLabel(groupBox);
        m_pLabConversionTime->setObjectName(QString::fromUtf8("m_pLabConversionTime"));

        gridLayout_2->addWidget(m_pLabConversionTime, 1, 0, 1, 1);

        m_pEditConversionTime = new QLineEdit(groupBox);
        m_pEditConversionTime->setObjectName(QString::fromUtf8("m_pEditConversionTime"));
        m_pEditConversionTime->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_pEditConversionTime, 1, 1, 1, 1);

        m_pEditRZ = new QSettingLineEdit(groupBox);
        m_pEditRZ->setObjectName(QString::fromUtf8("m_pEditRZ"));
        m_pEditRZ->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_pEditRZ, 2, 1, 1, 1);

        m_pLabRCurShortCircuit = new QLabel(groupBox);
        m_pLabRCurShortCircuit->setObjectName(QString::fromUtf8("m_pLabRCurShortCircuit"));

        gridLayout_2->addWidget(m_pLabRCurShortCircuit, 4, 0, 1, 1);

        m_pEditRCurShortCircuit = new QLineEdit(groupBox);
        m_pEditRCurShortCircuit->setObjectName(QString::fromUtf8("m_pEditRCurShortCircuit"));
        m_pEditRCurShortCircuit->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_pEditRCurShortCircuit, 4, 1, 1, 1);

        m_pLabRVolShortCircuit = new QLabel(groupBox);
        m_pLabRVolShortCircuit->setObjectName(QString::fromUtf8("m_pLabRVolShortCircuit"));

        gridLayout_2->addWidget(m_pLabRVolShortCircuit, 5, 0, 1, 1);

        m_pEditRVolShortCircuit = new QLineEdit(groupBox);
        m_pEditRVolShortCircuit->setObjectName(QString::fromUtf8("m_pEditRVolShortCircuit"));
        m_pEditRVolShortCircuit->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_pEditRVolShortCircuit, 5, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);

        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addWidget(frame_2);


        gridLayout->addLayout(verticalLayout_3, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 5, -1, 5);
        m_pLabFaultTrigTime = new QLabel(frame);
        m_pLabFaultTrigTime->setObjectName(QString::fromUtf8("m_pLabFaultTrigTime"));

        horizontalLayout->addWidget(m_pLabFaultTrigTime);

        m_pEditHour = new QLineEdit(frame);
        m_pEditHour->setObjectName(QString::fromUtf8("m_pEditHour"));
        m_pEditHour->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(m_pEditHour);

        m_pLabHour = new QLabel(frame);
        m_pLabHour->setObjectName(QString::fromUtf8("m_pLabHour"));

        horizontalLayout->addWidget(m_pLabHour);

        m_pEditMinute = new QLineEdit(frame);
        m_pEditMinute->setObjectName(QString::fromUtf8("m_pEditMinute"));
        m_pEditMinute->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(m_pEditMinute);

        m_pLabMinute = new QLabel(frame);
        m_pLabMinute->setObjectName(QString::fromUtf8("m_pLabMinute"));

        horizontalLayout->addWidget(m_pLabMinute);

        m_pEditSecond = new QLineEdit(frame);
        m_pEditSecond->setObjectName(QString::fromUtf8("m_pEditSecond"));
        m_pEditSecond->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(m_pEditSecond);

        m_pLabSecond = new QLabel(frame);
        m_pLabSecond->setObjectName(QString::fromUtf8("m_pLabSecond"));

        horizontalLayout->addWidget(m_pLabSecond);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, -1, 10, -1);
        m_pBtnCommonParas = new QPushButton(frame);
        m_pBtnCommonParas->setObjectName(QString::fromUtf8("m_pBtnCommonParas"));

        horizontalLayout_3->addWidget(m_pBtnCommonParas);

        m_pBtnResultAssess = new QPushButton(frame);
        m_pBtnResultAssess->setObjectName(QString::fromUtf8("m_pBtnResultAssess"));

        horizontalLayout_3->addWidget(m_pBtnResultAssess);


        horizontalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 2);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_11, 3, 0, 1, 1);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(QSttMacroParaEditViewCBOperate);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QSttMacroParaEditViewCBOperate);
    } // setupUi

    void retranslateUi(QWidget *QSttMacroParaEditViewCBOperate)
    {
        QSttMacroParaEditViewCBOperate->setWindowTitle(QApplication::translate("QSttMacroParaEditViewCBOperate", "Form", 0, QApplication::UnicodeUTF8));
        m_pLabImpedanceWay->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\351\230\273\346\212\227\350\241\250\347\244\272\346\226\271\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        m_pChkAmpAngle->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "Z-Phi", 0, QApplication::UnicodeUTF8));
        m_pChkRX->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "R-X", 0, QApplication::UnicodeUTF8));
        m_pLabFaultType->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\346\225\205\351\232\234\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        m_pLabZ->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "|Z|(\316\251)", 0, QApplication::UnicodeUTF8));
        m_pLabImpedanceAngle->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\351\230\273\346\212\227\350\247\222(\302\260)", 0, QApplication::UnicodeUTF8));
        m_pLabCurShortCircuit->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\347\237\255\350\267\257\347\224\265\346\265\201(A)", 0, QApplication::UnicodeUTF8));
        m_pLabVolShortCircuit->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\347\237\255\350\267\257\347\224\265\345\216\213(V)", 0, QApplication::UnicodeUTF8));
        m_pLabFaultDirection->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\346\225\205\351\232\234\346\226\271\345\220\221", 0, QApplication::UnicodeUTF8));
        m_pLabFaultQuality->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\346\225\205\351\232\234\346\200\247\350\264\250", 0, QApplication::UnicodeUTF8));
        m_pLabLarFaultTime->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\346\234\200\345\244\247\346\225\205\351\232\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_pChkConversionFault->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\350\275\254\346\215\242\346\200\247\346\225\205\351\232\234", 0, QApplication::UnicodeUTF8));
        m_pLabPowerAngleLoad->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\350\264\237\350\215\267\345\212\237\350\247\222", 0, QApplication::UnicodeUTF8));
        m_pLabCurLoad->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\350\264\237\350\215\267\347\224\265\346\265\201(A)", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        m_pLabRFaultDirection->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\346\225\205\351\232\234\346\226\271\345\220\221", 0, QApplication::UnicodeUTF8));
        m_pLabRZ->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "|Z|(\316\251)\357\274\232", 0, QApplication::UnicodeUTF8));
        m_pLabRImpedanceAngle->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\351\230\273\346\212\227\350\247\222(\302\260)", 0, QApplication::UnicodeUTF8));
        m_pLabRFaultType->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\346\225\205\351\232\234\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        m_pLabConversionTime->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\350\275\254\346\215\242\346\227\266\351\227\264(s)\357\274\232", 0, QApplication::UnicodeUTF8));
        m_pLabRCurShortCircuit->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\347\237\255\350\267\257\347\224\265\346\265\201(A)", 0, QApplication::UnicodeUTF8));
        m_pLabRVolShortCircuit->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\347\237\255\350\267\257\347\224\265\345\216\213(V)", 0, QApplication::UnicodeUTF8));
        m_pLabFaultTrigTime->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\346\225\205\351\232\234\350\247\246\345\217\221\346\227\266\345\210\273:", 0, QApplication::UnicodeUTF8));
        m_pLabHour->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\346\227\266", 0, QApplication::UnicodeUTF8));
        m_pLabMinute->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\345\210\206", 0, QApplication::UnicodeUTF8));
        m_pLabSecond->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\347\247\222", 0, QApplication::UnicodeUTF8));
        m_pBtnCommonParas->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_pBtnResultAssess->setText(QApplication::translate("QSttMacroParaEditViewCBOperate", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QSttMacroParaEditViewCBOperate", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttMacroParaEditViewCBOperate: public Ui_QSttMacroParaEditViewCBOperate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSTTMACROPARAEDITVIEWCBOPERATE_H
