/********************************************************************************
** Form generated from reading UI file 'SttMacroParaEditViewFaultGradient.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTMACROPARAEDITVIEWFAULTGRADIENT_H
#define UI_STTMACROPARAEDITVIEWFAULTGRADIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../../Module/UI/Module/ScrollCtrl/ScrollComboBox.h"
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"
#include "../../UI/Controls/SttCheckBox.h"
#include "../Controls/SttLineEdit.h"
#include "../Controls/SttTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_QSttMacroParaEditViewFaultGradient
{
public:
    QVBoxLayout *verticalLayout_2;
    QSttTabWidget *m_tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *m_gpChangeSet;
    QGridLayout *gridLayout;
    QLabel *m_labInit;
    QSettingLineEdit *m_editInit;
    QLabel *m_labFinish;
    QSettingLineEdit *m_editFinish;
    QLabel *m_labStep;
    QSettingLineEdit *m_editStep;
    QLabel *m_labTime;
    QSettingLineEdit *m_editFaultTime;
    QLabel *m_labType;
    QScrollComboBox *m_cbbType;
    QGroupBox *m_gpVarSet;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labVar;
    QScrollComboBox *m_cbbFaultMode;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_labVar_2;
    QScrollComboBox *m_cbbChangeVaule;
    QHBoxLayout *horizontalLayout_8;
    QLabel *m_labShortVm;
    QHBoxLayout *horizontalLayout;
    QSttLineEdit *m_editShortVm;
    QScrollComboBox *m_cbbShortVm;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_labDirection;
    QSttLineEdit *m_editShortVa;
    QHBoxLayout *horizontalLayout_10;
    QLabel *m_labDirection_2;
    QSttLineEdit *m_editAngle;
    QGroupBox *m_gpMannual;
    QGridLayout *gridLayout_3;
    QLabel *m_labTimeBeforeChange;
    QSttLineEdit *m_editTimeBeforeChange;
    QLabel *m_labTimeBeforeFail;
    QSttLineEdit *m_editTimeBeforeFail;
    QLabel *m_labTimeBeforeChange_2;
    QSttLineEdit *m_editFaultBeforeVm;
    QLabel *m_labTimeBeforeFail_2;
    QSttLineEdit *m_editFaultBeforeVa;
    QLabel *m_labTimeBeforeFail_3;
    QSttLineEdit *m_editFaultBeforeAngle;
    QVBoxLayout *verticalLayout;
    QGroupBox *m_gpBin;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout_4;
    QSttCheckBox *m_cbBinJ9;
    QSttCheckBox *m_cbBinD3;
    QSttCheckBox *m_cbBinI8;
    QSttCheckBox *m_cbBinB1;
    QSttCheckBox *m_cbBinC2;
    QRadioButton *m_rbOr;
    QSttCheckBox *m_cbBinF5;
    QSttCheckBox *m_cbBinA0;
    QSttCheckBox *m_cbBinH7;
    QRadioButton *m_rbAnd;
    QSttCheckBox *m_cbBinE4;
    QSttCheckBox *m_cbBinG6;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *m_gpBoutNormal;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_5;
    QSttCheckBox *m_cbBOut3;
    QSttCheckBox *m_cbBOut0;
    QSttCheckBox *m_cbBOut2;
    QSttCheckBox *m_cbBOut1;
    QGroupBox *m_gpBoutError;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_7;
    QSttCheckBox *m_cbBOut2_E5;
    QSttCheckBox *m_cbBOut4_E7;
    QSttCheckBox *m_cbBOut1_E4;
    QSttCheckBox *m_cbBOut3_E6;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnMoreOut;
    QPushButton *m_btnEstimate;
    QButtonGroup *btnGrpOutNormalError;
    QButtonGroup *btnGrpBin;

    void setupUi(QWidget *QSttMacroParaEditViewFaultGradient)
    {
        if (QSttMacroParaEditViewFaultGradient->objectName().isEmpty())
            QSttMacroParaEditViewFaultGradient->setObjectName(QString::fromUtf8("QSttMacroParaEditViewFaultGradient"));
        QSttMacroParaEditViewFaultGradient->resize(1244, 734);
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        QSttMacroParaEditViewFaultGradient->setFont(font);
        verticalLayout_2 = new QVBoxLayout(QSttMacroParaEditViewFaultGradient);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_tabWidget = new QSttTabWidget(QSttMacroParaEditViewFaultGradient);
        m_tabWidget->setObjectName(QString::fromUtf8("m_tabWidget"));
        QFont font1;
        font1.setPointSize(11);
        m_tabWidget->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_gpChangeSet = new QGroupBox(tab);
        m_gpChangeSet->setObjectName(QString::fromUtf8("m_gpChangeSet"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_gpChangeSet->sizePolicy().hasHeightForWidth());
        m_gpChangeSet->setSizePolicy(sizePolicy);
        m_gpChangeSet->setMinimumSize(QSize(0, 230));
        m_gpChangeSet->setMaximumSize(QSize(290, 16777215));
        gridLayout = new QGridLayout(m_gpChangeSet);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, -1, 6, -1);
        m_labInit = new QLabel(m_gpChangeSet);
        m_labInit->setObjectName(QString::fromUtf8("m_labInit"));
        m_labInit->setMinimumSize(QSize(0, 0));
        m_labInit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(m_labInit, 0, 0, 1, 1);

        m_editInit = new QSettingLineEdit(m_gpChangeSet);
        m_editInit->setObjectName(QString::fromUtf8("m_editInit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_editInit->sizePolicy().hasHeightForWidth());
        m_editInit->setSizePolicy(sizePolicy1);
        m_editInit->setMinimumSize(QSize(130, 0));
        m_editInit->setMaximumSize(QSize(160, 16777215));

        gridLayout->addWidget(m_editInit, 0, 1, 1, 1);

        m_labFinish = new QLabel(m_gpChangeSet);
        m_labFinish->setObjectName(QString::fromUtf8("m_labFinish"));
        m_labFinish->setMinimumSize(QSize(0, 0));
        m_labFinish->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(m_labFinish, 1, 0, 1, 1);

        m_editFinish = new QSettingLineEdit(m_gpChangeSet);
        m_editFinish->setObjectName(QString::fromUtf8("m_editFinish"));
        sizePolicy1.setHeightForWidth(m_editFinish->sizePolicy().hasHeightForWidth());
        m_editFinish->setSizePolicy(sizePolicy1);
        m_editFinish->setMinimumSize(QSize(130, 0));
        m_editFinish->setMaximumSize(QSize(160, 16777215));

        gridLayout->addWidget(m_editFinish, 1, 1, 1, 1);

        m_labStep = new QLabel(m_gpChangeSet);
        m_labStep->setObjectName(QString::fromUtf8("m_labStep"));
        m_labStep->setMinimumSize(QSize(0, 0));
        m_labStep->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(m_labStep, 2, 0, 1, 1);

        m_editStep = new QSettingLineEdit(m_gpChangeSet);
        m_editStep->setObjectName(QString::fromUtf8("m_editStep"));
        sizePolicy1.setHeightForWidth(m_editStep->sizePolicy().hasHeightForWidth());
        m_editStep->setSizePolicy(sizePolicy1);
        m_editStep->setMinimumSize(QSize(130, 0));
        m_editStep->setMaximumSize(QSize(160, 16777215));

        gridLayout->addWidget(m_editStep, 2, 1, 1, 1);

        m_labTime = new QLabel(m_gpChangeSet);
        m_labTime->setObjectName(QString::fromUtf8("m_labTime"));
        m_labTime->setMinimumSize(QSize(0, 0));
        m_labTime->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(m_labTime, 3, 0, 1, 1);

        m_editFaultTime = new QSettingLineEdit(m_gpChangeSet);
        m_editFaultTime->setObjectName(QString::fromUtf8("m_editFaultTime"));
        sizePolicy1.setHeightForWidth(m_editFaultTime->sizePolicy().hasHeightForWidth());
        m_editFaultTime->setSizePolicy(sizePolicy1);
        m_editFaultTime->setMinimumSize(QSize(130, 0));
        m_editFaultTime->setMaximumSize(QSize(160, 16777215));

        gridLayout->addWidget(m_editFaultTime, 3, 1, 1, 1);

        m_labType = new QLabel(m_gpChangeSet);
        m_labType->setObjectName(QString::fromUtf8("m_labType"));
        m_labType->setMinimumSize(QSize(0, 0));
        m_labType->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(m_labType, 4, 0, 1, 1);

        m_cbbType = new QScrollComboBox(m_gpChangeSet);
        m_cbbType->setObjectName(QString::fromUtf8("m_cbbType"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_cbbType->sizePolicy().hasHeightForWidth());
        m_cbbType->setSizePolicy(sizePolicy2);
        m_cbbType->setMinimumSize(QSize(130, 0));
        m_cbbType->setMaximumSize(QSize(160, 16777215));

        gridLayout->addWidget(m_cbbType, 4, 1, 1, 1);


        horizontalLayout_3->addWidget(m_gpChangeSet);

        m_gpVarSet = new QGroupBox(tab);
        m_gpVarSet->setObjectName(QString::fromUtf8("m_gpVarSet"));
        sizePolicy.setHeightForWidth(m_gpVarSet->sizePolicy().hasHeightForWidth());
        m_gpVarSet->setSizePolicy(sizePolicy);
        m_gpVarSet->setMinimumSize(QSize(0, 230));
        m_gpVarSet->setMaximumSize(QSize(380, 16777215));
        verticalLayout_5 = new QVBoxLayout(m_gpVarSet);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labVar = new QLabel(m_gpVarSet);
        m_labVar->setObjectName(QString::fromUtf8("m_labVar"));
        m_labVar->setMinimumSize(QSize(0, 0));
        m_labVar->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(m_labVar);

        m_cbbFaultMode = new QScrollComboBox(m_gpVarSet);
        m_cbbFaultMode->setObjectName(QString::fromUtf8("m_cbbFaultMode"));
        sizePolicy2.setHeightForWidth(m_cbbFaultMode->sizePolicy().hasHeightForWidth());
        m_cbbFaultMode->setSizePolicy(sizePolicy2);
        m_cbbFaultMode->setMinimumSize(QSize(190, 0));
        m_cbbFaultMode->setMaximumSize(QSize(190, 16777215));
        m_cbbFaultMode->setMaxVisibleItems(5);

        horizontalLayout_6->addWidget(m_cbbFaultMode);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_labVar_2 = new QLabel(m_gpVarSet);
        m_labVar_2->setObjectName(QString::fromUtf8("m_labVar_2"));
        m_labVar_2->setMinimumSize(QSize(0, 0));
        m_labVar_2->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_7->addWidget(m_labVar_2);

        m_cbbChangeVaule = new QScrollComboBox(m_gpVarSet);
        m_cbbChangeVaule->setObjectName(QString::fromUtf8("m_cbbChangeVaule"));
        sizePolicy2.setHeightForWidth(m_cbbChangeVaule->sizePolicy().hasHeightForWidth());
        m_cbbChangeVaule->setSizePolicy(sizePolicy2);
        m_cbbChangeVaule->setMinimumSize(QSize(190, 0));
        m_cbbChangeVaule->setMaximumSize(QSize(190, 16777215));
        m_cbbChangeVaule->setMaxVisibleItems(5);

        horizontalLayout_7->addWidget(m_cbbChangeVaule);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        m_labShortVm = new QLabel(m_gpVarSet);
        m_labShortVm->setObjectName(QString::fromUtf8("m_labShortVm"));
        m_labShortVm->setMinimumSize(QSize(0, 0));
        m_labShortVm->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_8->addWidget(m_labShortVm);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_editShortVm = new QSttLineEdit(m_gpVarSet);
        m_editShortVm->setObjectName(QString::fromUtf8("m_editShortVm"));
        sizePolicy2.setHeightForWidth(m_editShortVm->sizePolicy().hasHeightForWidth());
        m_editShortVm->setSizePolicy(sizePolicy2);
        m_editShortVm->setMinimumSize(QSize(67, 0));
        m_editShortVm->setMaximumSize(QSize(67, 16777215));
        m_editShortVm->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(m_editShortVm);

        m_cbbShortVm = new QScrollComboBox(m_gpVarSet);
        m_cbbShortVm->setObjectName(QString::fromUtf8("m_cbbShortVm"));
        sizePolicy2.setHeightForWidth(m_cbbShortVm->sizePolicy().hasHeightForWidth());
        m_cbbShortVm->setSizePolicy(sizePolicy2);
        m_cbbShortVm->setMinimumSize(QSize(117, 0));
        m_cbbShortVm->setMaximumSize(QSize(117, 16777215));
        m_cbbShortVm->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);

        horizontalLayout->addWidget(m_cbbShortVm);


        horizontalLayout_8->addLayout(horizontalLayout);


        verticalLayout_5->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        m_labDirection = new QLabel(m_gpVarSet);
        m_labDirection->setObjectName(QString::fromUtf8("m_labDirection"));
        m_labDirection->setMinimumSize(QSize(0, 0));
        m_labDirection->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_9->addWidget(m_labDirection);

        m_editShortVa = new QSttLineEdit(m_gpVarSet);
        m_editShortVa->setObjectName(QString::fromUtf8("m_editShortVa"));
        sizePolicy1.setHeightForWidth(m_editShortVa->sizePolicy().hasHeightForWidth());
        m_editShortVa->setSizePolicy(sizePolicy1);
        m_editShortVa->setMinimumSize(QSize(190, 0));
        m_editShortVa->setMaximumSize(QSize(190, 16777215));

        horizontalLayout_9->addWidget(m_editShortVa);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        m_labDirection_2 = new QLabel(m_gpVarSet);
        m_labDirection_2->setObjectName(QString::fromUtf8("m_labDirection_2"));
        m_labDirection_2->setMinimumSize(QSize(0, 0));
        m_labDirection_2->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_10->addWidget(m_labDirection_2);

        m_editAngle = new QSttLineEdit(m_gpVarSet);
        m_editAngle->setObjectName(QString::fromUtf8("m_editAngle"));
        sizePolicy1.setHeightForWidth(m_editAngle->sizePolicy().hasHeightForWidth());
        m_editAngle->setSizePolicy(sizePolicy1);
        m_editAngle->setMinimumSize(QSize(190, 0));
        m_editAngle->setMaximumSize(QSize(190, 16777215));

        horizontalLayout_10->addWidget(m_editAngle);


        verticalLayout_5->addLayout(horizontalLayout_10);


        horizontalLayout_3->addWidget(m_gpVarSet);

        m_gpMannual = new QGroupBox(tab);
        m_gpMannual->setObjectName(QString::fromUtf8("m_gpMannual"));
        m_gpMannual->setMinimumSize(QSize(0, 230));
        m_gpMannual->setMaximumSize(QSize(340, 16777215));
        gridLayout_3 = new QGridLayout(m_gpMannual);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(6, -1, 6, -1);
        m_labTimeBeforeChange = new QLabel(m_gpMannual);
        m_labTimeBeforeChange->setObjectName(QString::fromUtf8("m_labTimeBeforeChange"));
        m_labTimeBeforeChange->setMinimumSize(QSize(0, 0));
        m_labTimeBeforeChange->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(m_labTimeBeforeChange, 0, 0, 1, 1);

        m_editTimeBeforeChange = new QSttLineEdit(m_gpMannual);
        m_editTimeBeforeChange->setObjectName(QString::fromUtf8("m_editTimeBeforeChange"));
        sizePolicy2.setHeightForWidth(m_editTimeBeforeChange->sizePolicy().hasHeightForWidth());
        m_editTimeBeforeChange->setSizePolicy(sizePolicy2);
        m_editTimeBeforeChange->setMinimumSize(QSize(130, 0));
        m_editTimeBeforeChange->setMaximumSize(QSize(160, 16777215));

        gridLayout_3->addWidget(m_editTimeBeforeChange, 0, 1, 1, 1);

        m_labTimeBeforeFail = new QLabel(m_gpMannual);
        m_labTimeBeforeFail->setObjectName(QString::fromUtf8("m_labTimeBeforeFail"));
        m_labTimeBeforeFail->setMinimumSize(QSize(0, 0));
        m_labTimeBeforeFail->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(m_labTimeBeforeFail, 1, 0, 1, 1);

        m_editTimeBeforeFail = new QSttLineEdit(m_gpMannual);
        m_editTimeBeforeFail->setObjectName(QString::fromUtf8("m_editTimeBeforeFail"));
        sizePolicy2.setHeightForWidth(m_editTimeBeforeFail->sizePolicy().hasHeightForWidth());
        m_editTimeBeforeFail->setSizePolicy(sizePolicy2);
        m_editTimeBeforeFail->setMinimumSize(QSize(130, 0));
        m_editTimeBeforeFail->setMaximumSize(QSize(160, 16777215));

        gridLayout_3->addWidget(m_editTimeBeforeFail, 1, 1, 1, 1);

        m_labTimeBeforeChange_2 = new QLabel(m_gpMannual);
        m_labTimeBeforeChange_2->setObjectName(QString::fromUtf8("m_labTimeBeforeChange_2"));
        m_labTimeBeforeChange_2->setMinimumSize(QSize(0, 0));
        m_labTimeBeforeChange_2->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(m_labTimeBeforeChange_2, 2, 0, 1, 1);

        m_editFaultBeforeVm = new QSttLineEdit(m_gpMannual);
        m_editFaultBeforeVm->setObjectName(QString::fromUtf8("m_editFaultBeforeVm"));
        sizePolicy2.setHeightForWidth(m_editFaultBeforeVm->sizePolicy().hasHeightForWidth());
        m_editFaultBeforeVm->setSizePolicy(sizePolicy2);
        m_editFaultBeforeVm->setMinimumSize(QSize(130, 0));
        m_editFaultBeforeVm->setMaximumSize(QSize(160, 16777215));

        gridLayout_3->addWidget(m_editFaultBeforeVm, 2, 1, 1, 1);

        m_labTimeBeforeFail_2 = new QLabel(m_gpMannual);
        m_labTimeBeforeFail_2->setObjectName(QString::fromUtf8("m_labTimeBeforeFail_2"));
        m_labTimeBeforeFail_2->setMinimumSize(QSize(0, 0));
        m_labTimeBeforeFail_2->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(m_labTimeBeforeFail_2, 3, 0, 1, 1);

        m_editFaultBeforeVa = new QSttLineEdit(m_gpMannual);
        m_editFaultBeforeVa->setObjectName(QString::fromUtf8("m_editFaultBeforeVa"));
        sizePolicy2.setHeightForWidth(m_editFaultBeforeVa->sizePolicy().hasHeightForWidth());
        m_editFaultBeforeVa->setSizePolicy(sizePolicy2);
        m_editFaultBeforeVa->setMinimumSize(QSize(130, 0));
        m_editFaultBeforeVa->setMaximumSize(QSize(160, 16777215));

        gridLayout_3->addWidget(m_editFaultBeforeVa, 3, 1, 1, 1);

        m_labTimeBeforeFail_3 = new QLabel(m_gpMannual);
        m_labTimeBeforeFail_3->setObjectName(QString::fromUtf8("m_labTimeBeforeFail_3"));
        m_labTimeBeforeFail_3->setMinimumSize(QSize(0, 0));
        m_labTimeBeforeFail_3->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(m_labTimeBeforeFail_3, 4, 0, 1, 1);

        m_editFaultBeforeAngle = new QSttLineEdit(m_gpMannual);
        m_editFaultBeforeAngle->setObjectName(QString::fromUtf8("m_editFaultBeforeAngle"));
        sizePolicy2.setHeightForWidth(m_editFaultBeforeAngle->sizePolicy().hasHeightForWidth());
        m_editFaultBeforeAngle->setSizePolicy(sizePolicy2);
        m_editFaultBeforeAngle->setMinimumSize(QSize(130, 0));
        m_editFaultBeforeAngle->setMaximumSize(QSize(160, 16777215));

        gridLayout_3->addWidget(m_editFaultBeforeAngle, 4, 1, 1, 1);


        horizontalLayout_3->addWidget(m_gpMannual);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(2, 1);

        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_gpBin = new QGroupBox(tab);
        m_gpBin->setObjectName(QString::fromUtf8("m_gpBin"));
        m_gpBin->setMinimumSize(QSize(0, 110));
        m_gpBin->setMaximumSize(QSize(16777215, 110));
        horizontalLayout_4 = new QHBoxLayout(m_gpBin);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(-1, -1, 9, 9);
        m_cbBinJ9 = new QSttCheckBox(m_gpBin);
        btnGrpBin = new QButtonGroup(QSttMacroParaEditViewFaultGradient);
        btnGrpBin->setObjectName(QString::fromUtf8("btnGrpBin"));
        btnGrpBin->setExclusive(false);
        btnGrpBin->addButton(m_cbBinJ9);
        m_cbBinJ9->setObjectName(QString::fromUtf8("m_cbBinJ9"));
        QFont font2;
        font2.setPointSize(16);
        m_cbBinJ9->setFont(font2);
        m_cbBinJ9->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinJ9, 0, 9, 1, 1);

        m_cbBinD3 = new QSttCheckBox(m_gpBin);
        btnGrpBin->addButton(m_cbBinD3);
        m_cbBinD3->setObjectName(QString::fromUtf8("m_cbBinD3"));
        m_cbBinD3->setFont(font2);
        m_cbBinD3->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinD3, 0, 3, 1, 1);

        m_cbBinI8 = new QSttCheckBox(m_gpBin);
        btnGrpBin->addButton(m_cbBinI8);
        m_cbBinI8->setObjectName(QString::fromUtf8("m_cbBinI8"));
        m_cbBinI8->setFont(font2);
        m_cbBinI8->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinI8, 0, 8, 1, 1);

        m_cbBinB1 = new QSttCheckBox(m_gpBin);
        btnGrpBin->addButton(m_cbBinB1);
        m_cbBinB1->setObjectName(QString::fromUtf8("m_cbBinB1"));
        m_cbBinB1->setFont(font2);
        m_cbBinB1->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinB1, 0, 1, 1, 1);

        m_cbBinC2 = new QSttCheckBox(m_gpBin);
        btnGrpBin->addButton(m_cbBinC2);
        m_cbBinC2->setObjectName(QString::fromUtf8("m_cbBinC2"));
        m_cbBinC2->setFont(font2);
        m_cbBinC2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinC2, 0, 2, 1, 1);

        m_rbOr = new QRadioButton(m_gpBin);
        m_rbOr->setObjectName(QString::fromUtf8("m_rbOr"));
        m_rbOr->setChecked(true);

        gridLayout_4->addWidget(m_rbOr, 0, 10, 1, 1);

        m_cbBinF5 = new QSttCheckBox(m_gpBin);
        btnGrpBin->addButton(m_cbBinF5);
        m_cbBinF5->setObjectName(QString::fromUtf8("m_cbBinF5"));
        m_cbBinF5->setFont(font2);
        m_cbBinF5->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinF5, 0, 5, 1, 1);

        m_cbBinA0 = new QSttCheckBox(m_gpBin);
        btnGrpBin->addButton(m_cbBinA0);
        m_cbBinA0->setObjectName(QString::fromUtf8("m_cbBinA0"));
        m_cbBinA0->setFont(font2);
        m_cbBinA0->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinA0, 0, 0, 1, 1);

        m_cbBinH7 = new QSttCheckBox(m_gpBin);
        btnGrpBin->addButton(m_cbBinH7);
        m_cbBinH7->setObjectName(QString::fromUtf8("m_cbBinH7"));
        m_cbBinH7->setFont(font2);
        m_cbBinH7->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinH7, 0, 7, 1, 1);

        m_rbAnd = new QRadioButton(m_gpBin);
        m_rbAnd->setObjectName(QString::fromUtf8("m_rbAnd"));
        m_rbAnd->setChecked(false);

        gridLayout_4->addWidget(m_rbAnd, 0, 11, 1, 1);

        m_cbBinE4 = new QSttCheckBox(m_gpBin);
        btnGrpBin->addButton(m_cbBinE4);
        m_cbBinE4->setObjectName(QString::fromUtf8("m_cbBinE4"));
        m_cbBinE4->setFont(font2);
        m_cbBinE4->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinE4, 0, 4, 1, 1);

        m_cbBinG6 = new QSttCheckBox(m_gpBin);
        btnGrpBin->addButton(m_cbBinG6);
        m_cbBinG6->setObjectName(QString::fromUtf8("m_cbBinG6"));
        m_cbBinG6->setFont(font2);
        m_cbBinG6->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinG6, 0, 6, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_4);


        verticalLayout->addWidget(m_gpBin);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_gpBoutNormal = new QGroupBox(tab);
        m_gpBoutNormal->setObjectName(QString::fromUtf8("m_gpBoutNormal"));
        gridLayout_10 = new QGridLayout(m_gpBoutNormal);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_cbBOut3 = new QSttCheckBox(m_gpBoutNormal);
        btnGrpOutNormalError = new QButtonGroup(QSttMacroParaEditViewFaultGradient);
        btnGrpOutNormalError->setObjectName(QString::fromUtf8("btnGrpOutNormalError"));
        btnGrpOutNormalError->setExclusive(false);
        btnGrpOutNormalError->addButton(m_cbBOut3);
        m_cbBOut3->setObjectName(QString::fromUtf8("m_cbBOut3"));
        m_cbBOut3->setFont(font2);
        m_cbBOut3->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(m_cbBOut3, 0, 3, 1, 1);

        m_cbBOut0 = new QSttCheckBox(m_gpBoutNormal);
        btnGrpOutNormalError->addButton(m_cbBOut0);
        m_cbBOut0->setObjectName(QString::fromUtf8("m_cbBOut0"));
        m_cbBOut0->setFont(font2);
        m_cbBOut0->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(m_cbBOut0, 0, 0, 1, 1);

        m_cbBOut2 = new QSttCheckBox(m_gpBoutNormal);
        btnGrpOutNormalError->addButton(m_cbBOut2);
        m_cbBOut2->setObjectName(QString::fromUtf8("m_cbBOut2"));
        m_cbBOut2->setFont(font2);
        m_cbBOut2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(m_cbBOut2, 0, 2, 1, 1);

        m_cbBOut1 = new QSttCheckBox(m_gpBoutNormal);
        btnGrpOutNormalError->addButton(m_cbBOut1);
        m_cbBOut1->setObjectName(QString::fromUtf8("m_cbBOut1"));
        m_cbBOut1->setFont(font2);
        m_cbBOut1->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(m_cbBOut1, 0, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_5, 0, 0, 1, 1);


        horizontalLayout_5->addWidget(m_gpBoutNormal);

        m_gpBoutError = new QGroupBox(tab);
        m_gpBoutError->setObjectName(QString::fromUtf8("m_gpBoutError"));
        gridLayout_9 = new QGridLayout(m_gpBoutError);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        m_cbBOut2_E5 = new QSttCheckBox(m_gpBoutError);
        btnGrpOutNormalError->addButton(m_cbBOut2_E5);
        m_cbBOut2_E5->setObjectName(QString::fromUtf8("m_cbBOut2_E5"));
        m_cbBOut2_E5->setFont(font2);
        m_cbBOut2_E5->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(m_cbBOut2_E5, 0, 1, 1, 1);

        m_cbBOut4_E7 = new QSttCheckBox(m_gpBoutError);
        btnGrpOutNormalError->addButton(m_cbBOut4_E7);
        m_cbBOut4_E7->setObjectName(QString::fromUtf8("m_cbBOut4_E7"));
        m_cbBOut4_E7->setFont(font2);
        m_cbBOut4_E7->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(m_cbBOut4_E7, 0, 3, 1, 1);

        m_cbBOut1_E4 = new QSttCheckBox(m_gpBoutError);
        btnGrpOutNormalError->addButton(m_cbBOut1_E4);
        m_cbBOut1_E4->setObjectName(QString::fromUtf8("m_cbBOut1_E4"));
        m_cbBOut1_E4->setFont(font2);
        m_cbBOut1_E4->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(m_cbBOut1_E4, 0, 0, 1, 1);

        m_cbBOut3_E6 = new QSttCheckBox(m_gpBoutError);
        btnGrpOutNormalError->addButton(m_cbBOut3_E6);
        m_cbBOut3_E6->setObjectName(QString::fromUtf8("m_cbBOut3_E6"));
        m_cbBOut3_E6->setFont(font2);
        m_cbBOut3_E6->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(m_cbBOut3_E6, 0, 2, 1, 1);


        gridLayout_9->addLayout(gridLayout_7, 0, 0, 1, 1);


        horizontalLayout_5->addWidget(m_gpBoutError);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_btnMoreOut = new QPushButton(tab);
        m_btnMoreOut->setObjectName(QString::fromUtf8("m_btnMoreOut"));

        horizontalLayout_2->addWidget(m_btnMoreOut);

        m_btnEstimate = new QPushButton(tab);
        m_btnEstimate->setObjectName(QString::fromUtf8("m_btnEstimate"));

        horizontalLayout_2->addWidget(m_btnEstimate);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_3->setStretch(0, 3);
        verticalLayout_3->setStretch(1, 2);
        m_tabWidget->addTab(tab, QString());

        verticalLayout_2->addWidget(m_tabWidget);


        retranslateUi(QSttMacroParaEditViewFaultGradient);

        m_tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QSttMacroParaEditViewFaultGradient);
    } // setupUi

    void retranslateUi(QWidget *QSttMacroParaEditViewFaultGradient)
    {
        QSttMacroParaEditViewFaultGradient->setWindowTitle(QApplication::translate("QSttMacroParaEditViewFaultGradient", "Form", 0, QApplication::UnicodeUTF8));
        m_gpChangeSet->setTitle(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\351\200\222\345\217\230\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_labInit->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\345\217\230\345\214\226\345\247\213\345\200\274():", 0, QApplication::UnicodeUTF8));
        m_labFinish->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\345\217\230\345\214\226\347\273\210\345\200\274():", 0, QApplication::UnicodeUTF8));
        m_labStep->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\345\217\230\345\214\226\346\255\245\351\225\277():", 0, QApplication::UnicodeUTF8));
        m_labTime->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labType->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_gpVarSet->setTitle(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\345\217\230\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_labVar->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\346\225\205\351\232\234\346\250\241\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labVar_2->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\345\217\230\345\214\226\351\207\217:", 0, QApplication::UnicodeUTF8));
        m_labShortVm->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\347\237\255\350\267\257\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labDirection->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\347\237\255\350\267\257\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labDirection_2->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_gpMannual->setTitle(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labTimeBeforeChange->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\345\217\230\345\214\226\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labTimeBeforeFail->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labTimeBeforeChange_2->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\346\225\205\351\232\234\345\211\215\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labTimeBeforeFail_2->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\346\225\205\351\232\234\345\211\215\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labTimeBeforeFail_3->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\346\225\205\351\232\234\345\211\215\347\233\270\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_gpBin->setTitle(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_cbBinJ9->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "J", 0, QApplication::UnicodeUTF8));
        m_cbBinD3->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "D", 0, QApplication::UnicodeUTF8));
        m_cbBinI8->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "I", 0, QApplication::UnicodeUTF8));
        m_cbBinB1->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "B", 0, QApplication::UnicodeUTF8));
        m_cbBinC2->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "C", 0, QApplication::UnicodeUTF8));
        m_rbOr->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        m_cbBinF5->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "F", 0, QApplication::UnicodeUTF8));
        m_cbBinA0->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "A", 0, QApplication::UnicodeUTF8));
        m_cbBinH7->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "H", 0, QApplication::UnicodeUTF8));
        m_rbAnd->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_cbBinE4->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "E", 0, QApplication::UnicodeUTF8));
        m_cbBinG6->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "G", 0, QApplication::UnicodeUTF8));
        m_gpBoutNormal->setTitle(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\345\274\200\345\207\272\351\207\217\346\255\243\345\270\270\346\200\201", 0, QApplication::UnicodeUTF8));
        m_cbBOut3->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "4", 0, QApplication::UnicodeUTF8));
        m_cbBOut0->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "1", 0, QApplication::UnicodeUTF8));
        m_cbBOut2->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "3", 0, QApplication::UnicodeUTF8));
        m_cbBOut1->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "2", 0, QApplication::UnicodeUTF8));
        m_gpBoutError->setTitle(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\345\274\200\345\207\272\351\207\217\346\225\205\351\232\234\346\200\201", 0, QApplication::UnicodeUTF8));
        m_cbBOut2_E5->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "2", 0, QApplication::UnicodeUTF8));
        m_cbBOut4_E7->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "4", 0, QApplication::UnicodeUTF8));
        m_cbBOut1_E4->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "1", 0, QApplication::UnicodeUTF8));
        m_cbBOut3_E6->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "3", 0, QApplication::UnicodeUTF8));
        m_btnMoreOut->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\346\233\264\345\244\232\345\274\200\345\207\272\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_btnEstimate->setText(QApplication::translate("QSttMacroParaEditViewFaultGradient", "\346\225\264\345\256\232\345\217\212\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab), QApplication::translate("QSttMacroParaEditViewFaultGradient", "\351\200\222\345\217\230\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttMacroParaEditViewFaultGradient: public Ui_QSttMacroParaEditViewFaultGradient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTMACROPARAEDITVIEWFAULTGRADIENT_H
