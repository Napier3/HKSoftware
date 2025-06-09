/********************************************************************************
** Form generated from reading UI file 'ImpedanceManuWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPEDANCEMANUWIDGET_H
#define UI_IMPEDANCEMANUWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "../../Module/UI/Controls/SttCheckbox.h"
#include "../../Module/UI/Controls/SttGroupBox.h"
#include "../../Module/UI/Controls/SttLineEdit.h"
#include "../../Module/UI/Controls/SttTabWidget.h"
#include "../../Module/UI/Module/ScrollCtrl/ScrollComboBox.h"
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QImpedanceManuWidget
{
public:
    QGridLayout *gridLayout;
    QSttTabWidget *m_pImpedanceManuTab;
    QWidget *m_pParaSetting_Widget;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_2;
    QRadioButton *m_pRad_Z;
    QScrollComboBox *m_pCmb_FaultType;
    QPushButton *m_pBinarySet_PushButton;
    QScrollComboBox *m_pCmb_CalMode;
    QPushButton *m_pEstimate_PushButton;
    QSttGroupBox *groupBoxCoe;
    QGridLayout *gridLayoutSub;
    QLabel *m_pCacuTypeLabel;
    QScrollComboBox *m_pCmb_CacuType;
    QLabel *m_pAmpLabel;
    QSettingLineEdit *m_pAmpEdit;
    QLabel *m_pAngleLabel;
    QSettingLineEdit *m_pAngleEdit;
    QSttCheckBox *m_pAuto_CheckBox;
    QSttCheckBox *m_pMutation_CheckBox;
    QPushButton *m_pLock_PushButton;
    QPushButton *m_pbn_Down;
    QSttGroupBox *m_pBoutGroupBox;
    QGridLayout *gridLayout_5;
    QSttCheckBox *m_pBout_CheckBox0;
    QSttCheckBox *m_pBout_CheckBox1;
    QSttCheckBox *m_pBout_CheckBox2;
    QSttCheckBox *m_pBout_CheckBox3;
    QPushButton *m_pbn_Up;
    QSttLineEdit *m_pTrigDelayEdit;
    QLabel *m_pRXLabel;
    QSttLineEdit *m_pShortIOrZsAmpEdit;
    QSettingLineEdit *m_pPhiEdit;
    QSettingLineEdit *m_pZEdit;
    QSttLineEdit *m_pShortIOrZsAngleEdit;
    QSttLineEdit *m_pREdit;
    QSttLineEdit *m_pXEdit;
    QLabel *m_pZLabel;
    QRadioButton *m_pRad_RX;
    QSpacerItem *horizontalSpacer_2;
    QSttGroupBox *groupBoxCommon;
    QGridLayout *gridLayoutCommon;
    QLabel *m_PrepareTimeLabel;
    QScrollComboBox *m_pCmb_FirstMode;
    QSttLineEdit *m_PrepareTimeEdit;
    QSettingLineEdit *m_pStartEdit;
    QLabel *m_pStartLabel;
    QLabel *m_PreFaultTimeLabel;
    QLabel *m_pEndLabel;
    QLabel *m_pVarSelecLabel;
    QSettingLineEdit *m_pEndEdit;
    QLabel *m_pTimeLabel;
    QScrollComboBox *m_pCmb_ChangeType;
    QSttLineEdit *m_PreFaultTimeEdit;
    QLabel *m_pStepLabel;
    QSettingLineEdit *m_pTimeEdit;
    QSettingLineEdit *m_pStepEdit;
    QLabel *m_pChangeTypeLabel;
    QScrollComboBox *m_pCmb_SecondMode;
    QLabel *m_pCalModeLabel;
    QLabel *m_pDLLabel;
    QLabel *m_pFaultTypeLabel;
    QLabel *m_pImpedlabel;
    QLabel *m_pTrigDelayLabel;

    void setupUi(QWidget *QImpedanceManuWidget)
    {
        if (QImpedanceManuWidget->objectName().isEmpty())
            QImpedanceManuWidget->setObjectName(QString::fromUtf8("QImpedanceManuWidget"));
        QImpedanceManuWidget->resize(920, 656);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QImpedanceManuWidget->sizePolicy().hasHeightForWidth());
        QImpedanceManuWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(QImpedanceManuWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pImpedanceManuTab = new QSttTabWidget(QImpedanceManuWidget);
        m_pImpedanceManuTab->setObjectName(QString::fromUtf8("m_pImpedanceManuTab"));
        m_pParaSetting_Widget = new QWidget();
        m_pParaSetting_Widget->setObjectName(QString::fromUtf8("m_pParaSetting_Widget"));
        gridLayout_6 = new QGridLayout(m_pParaSetting_Widget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pRad_Z = new QRadioButton(m_pParaSetting_Widget);
        m_pRad_Z->setObjectName(QString::fromUtf8("m_pRad_Z"));

        gridLayout_2->addWidget(m_pRad_Z, 1, 1, 1, 1);

        m_pCmb_FaultType = new QScrollComboBox(m_pParaSetting_Widget);
        m_pCmb_FaultType->setObjectName(QString::fromUtf8("m_pCmb_FaultType"));

        gridLayout_2->addWidget(m_pCmb_FaultType, 0, 1, 1, 2);

        m_pBinarySet_PushButton = new QPushButton(m_pParaSetting_Widget);
        m_pBinarySet_PushButton->setObjectName(QString::fromUtf8("m_pBinarySet_PushButton"));
        m_pBinarySet_PushButton->setAutoDefault(false);

        gridLayout_2->addWidget(m_pBinarySet_PushButton, 8, 6, 1, 1);

        m_pCmb_CalMode = new QScrollComboBox(m_pParaSetting_Widget);
        m_pCmb_CalMode->setObjectName(QString::fromUtf8("m_pCmb_CalMode"));

        gridLayout_2->addWidget(m_pCmb_CalMode, 0, 6, 1, 2);

        m_pEstimate_PushButton = new QPushButton(m_pParaSetting_Widget);
        m_pEstimate_PushButton->setObjectName(QString::fromUtf8("m_pEstimate_PushButton"));
        m_pEstimate_PushButton->setAutoDefault(false);

        gridLayout_2->addWidget(m_pEstimate_PushButton, 8, 7, 1, 1);

        groupBoxCoe = new QSttGroupBox(m_pParaSetting_Widget);
        groupBoxCoe->setObjectName(QString::fromUtf8("groupBoxCoe"));
        gridLayoutSub = new QGridLayout(groupBoxCoe);
        gridLayoutSub->setSpacing(6);
        gridLayoutSub->setContentsMargins(11, 11, 11, 11);
        gridLayoutSub->setObjectName(QString::fromUtf8("gridLayoutSub"));
        m_pCacuTypeLabel = new QLabel(groupBoxCoe);
        m_pCacuTypeLabel->setObjectName(QString::fromUtf8("m_pCacuTypeLabel"));

        gridLayoutSub->addWidget(m_pCacuTypeLabel, 0, 0, 1, 1);

        m_pCmb_CacuType = new QScrollComboBox(groupBoxCoe);
        m_pCmb_CacuType->setObjectName(QString::fromUtf8("m_pCmb_CacuType"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pCmb_CacuType->sizePolicy().hasHeightForWidth());
        m_pCmb_CacuType->setSizePolicy(sizePolicy1);
        m_pCmb_CacuType->setMinimumSize(QSize(0, 0));

        gridLayoutSub->addWidget(m_pCmb_CacuType, 0, 1, 1, 1);

        m_pAmpLabel = new QLabel(groupBoxCoe);
        m_pAmpLabel->setObjectName(QString::fromUtf8("m_pAmpLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pAmpLabel->sizePolicy().hasHeightForWidth());
        m_pAmpLabel->setSizePolicy(sizePolicy2);
        m_pAmpLabel->setMinimumSize(QSize(50, 0));

        gridLayoutSub->addWidget(m_pAmpLabel, 0, 2, 1, 1);

        m_pAmpEdit = new QSettingLineEdit(groupBoxCoe);
        m_pAmpEdit->setObjectName(QString::fromUtf8("m_pAmpEdit"));
        m_pAmpEdit->setAlignment(Qt::AlignCenter);

        gridLayoutSub->addWidget(m_pAmpEdit, 0, 3, 1, 1);

        m_pAngleLabel = new QLabel(groupBoxCoe);
        m_pAngleLabel->setObjectName(QString::fromUtf8("m_pAngleLabel"));
        sizePolicy2.setHeightForWidth(m_pAngleLabel->sizePolicy().hasHeightForWidth());
        m_pAngleLabel->setSizePolicy(sizePolicy2);
        m_pAngleLabel->setMinimumSize(QSize(50, 0));

        gridLayoutSub->addWidget(m_pAngleLabel, 1, 2, 1, 1);

        m_pAngleEdit = new QSettingLineEdit(groupBoxCoe);
        m_pAngleEdit->setObjectName(QString::fromUtf8("m_pAngleEdit"));
        m_pAngleEdit->setAlignment(Qt::AlignCenter);

        gridLayoutSub->addWidget(m_pAngleEdit, 1, 3, 1, 1);


        gridLayout_2->addWidget(groupBoxCoe, 1, 4, 2, 4);

        m_pAuto_CheckBox = new QSttCheckBox(m_pParaSetting_Widget);
        m_pAuto_CheckBox->setObjectName(QString::fromUtf8("m_pAuto_CheckBox"));

        gridLayout_2->addWidget(m_pAuto_CheckBox, 3, 7, 1, 1);

        m_pMutation_CheckBox = new QSttCheckBox(m_pParaSetting_Widget);
        m_pMutation_CheckBox->setObjectName(QString::fromUtf8("m_pMutation_CheckBox"));

        gridLayout_2->addWidget(m_pMutation_CheckBox, 4, 7, 1, 1);

        m_pLock_PushButton = new QPushButton(m_pParaSetting_Widget);
        m_pLock_PushButton->setObjectName(QString::fromUtf8("m_pLock_PushButton"));

        gridLayout_2->addWidget(m_pLock_PushButton, 5, 7, 1, 1);

        m_pbn_Down = new QPushButton(m_pParaSetting_Widget);
        m_pbn_Down->setObjectName(QString::fromUtf8("m_pbn_Down"));

        gridLayout_2->addWidget(m_pbn_Down, 8, 5, 1, 1);

        m_pBoutGroupBox = new QSttGroupBox(m_pParaSetting_Widget);
        m_pBoutGroupBox->setObjectName(QString::fromUtf8("m_pBoutGroupBox"));
        gridLayout_5 = new QGridLayout(m_pBoutGroupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_pBout_CheckBox0 = new QSttCheckBox(m_pBoutGroupBox);
        m_pBout_CheckBox0->setObjectName(QString::fromUtf8("m_pBout_CheckBox0"));

        gridLayout_5->addWidget(m_pBout_CheckBox0, 1, 0, 1, 1);

        m_pBout_CheckBox1 = new QSttCheckBox(m_pBoutGroupBox);
        m_pBout_CheckBox1->setObjectName(QString::fromUtf8("m_pBout_CheckBox1"));

        gridLayout_5->addWidget(m_pBout_CheckBox1, 1, 1, 1, 1);

        m_pBout_CheckBox2 = new QSttCheckBox(m_pBoutGroupBox);
        m_pBout_CheckBox2->setObjectName(QString::fromUtf8("m_pBout_CheckBox2"));

        gridLayout_5->addWidget(m_pBout_CheckBox2, 1, 2, 1, 1);

        m_pBout_CheckBox3 = new QSttCheckBox(m_pBoutGroupBox);
        m_pBout_CheckBox3->setObjectName(QString::fromUtf8("m_pBout_CheckBox3"));

        gridLayout_5->addWidget(m_pBout_CheckBox3, 1, 3, 1, 1);


        gridLayout_2->addWidget(m_pBoutGroupBox, 8, 0, 1, 2);

        m_pbn_Up = new QPushButton(m_pParaSetting_Widget);
        m_pbn_Up->setObjectName(QString::fromUtf8("m_pbn_Up"));

        gridLayout_2->addWidget(m_pbn_Up, 8, 4, 1, 1);

        m_pTrigDelayEdit = new QSttLineEdit(m_pParaSetting_Widget);
        m_pTrigDelayEdit->setObjectName(QString::fromUtf8("m_pTrigDelayEdit"));
        m_pTrigDelayEdit->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_pTrigDelayEdit, 5, 1, 1, 1);

        m_pRXLabel = new QLabel(m_pParaSetting_Widget);
        m_pRXLabel->setObjectName(QString::fromUtf8("m_pRXLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_pRXLabel->sizePolicy().hasHeightForWidth());
        m_pRXLabel->setSizePolicy(sizePolicy3);
        m_pRXLabel->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(m_pRXLabel, 3, 0, 1, 1);

        m_pShortIOrZsAmpEdit = new QSttLineEdit(m_pParaSetting_Widget);
        m_pShortIOrZsAmpEdit->setObjectName(QString::fromUtf8("m_pShortIOrZsAmpEdit"));
        m_pShortIOrZsAmpEdit->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_pShortIOrZsAmpEdit, 4, 1, 1, 1);

        m_pPhiEdit = new QSettingLineEdit(m_pParaSetting_Widget);
        m_pPhiEdit->setObjectName(QString::fromUtf8("m_pPhiEdit"));
        m_pPhiEdit->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_pPhiEdit, 2, 2, 1, 1);

        m_pZEdit = new QSettingLineEdit(m_pParaSetting_Widget);
        m_pZEdit->setObjectName(QString::fromUtf8("m_pZEdit"));
        m_pZEdit->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_pZEdit, 2, 1, 1, 1);

        m_pShortIOrZsAngleEdit = new QSttLineEdit(m_pParaSetting_Widget);
        m_pShortIOrZsAngleEdit->setObjectName(QString::fromUtf8("m_pShortIOrZsAngleEdit"));
        m_pShortIOrZsAngleEdit->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_pShortIOrZsAngleEdit, 4, 2, 1, 1);

        m_pREdit = new QSttLineEdit(m_pParaSetting_Widget);
        m_pREdit->setObjectName(QString::fromUtf8("m_pREdit"));
        m_pREdit->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_pREdit, 3, 1, 1, 1);

        m_pXEdit = new QSttLineEdit(m_pParaSetting_Widget);
        m_pXEdit->setObjectName(QString::fromUtf8("m_pXEdit"));
        m_pXEdit->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_pXEdit, 3, 2, 1, 1);

        m_pZLabel = new QLabel(m_pParaSetting_Widget);
        m_pZLabel->setObjectName(QString::fromUtf8("m_pZLabel"));
        sizePolicy3.setHeightForWidth(m_pZLabel->sizePolicy().hasHeightForWidth());
        m_pZLabel->setSizePolicy(sizePolicy3);
        m_pZLabel->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(m_pZLabel, 2, 0, 1, 1);

        m_pRad_RX = new QRadioButton(m_pParaSetting_Widget);
        m_pRad_RX->setObjectName(QString::fromUtf8("m_pRad_RX"));

        gridLayout_2->addWidget(m_pRad_RX, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        groupBoxCommon = new QSttGroupBox(m_pParaSetting_Widget);
        groupBoxCommon->setObjectName(QString::fromUtf8("groupBoxCommon"));
        sizePolicy3.setHeightForWidth(groupBoxCommon->sizePolicy().hasHeightForWidth());
        groupBoxCommon->setSizePolicy(sizePolicy3);
        gridLayoutCommon = new QGridLayout(groupBoxCommon);
        gridLayoutCommon->setSpacing(6);
        gridLayoutCommon->setContentsMargins(11, 11, 11, 11);
        gridLayoutCommon->setObjectName(QString::fromUtf8("gridLayoutCommon"));
        m_PrepareTimeLabel = new QLabel(groupBoxCommon);
        m_PrepareTimeLabel->setObjectName(QString::fromUtf8("m_PrepareTimeLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(m_PrepareTimeLabel->sizePolicy().hasHeightForWidth());
        m_PrepareTimeLabel->setSizePolicy(sizePolicy4);
        m_PrepareTimeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayoutCommon->addWidget(m_PrepareTimeLabel, 2, 0, 1, 1);

        m_pCmb_FirstMode = new QScrollComboBox(groupBoxCommon);
        m_pCmb_FirstMode->setObjectName(QString::fromUtf8("m_pCmb_FirstMode"));
        sizePolicy1.setHeightForWidth(m_pCmb_FirstMode->sizePolicy().hasHeightForWidth());
        m_pCmb_FirstMode->setSizePolicy(sizePolicy1);

        gridLayoutCommon->addWidget(m_pCmb_FirstMode, 0, 1, 1, 1);

        m_PrepareTimeEdit = new QSttLineEdit(groupBoxCommon);
        m_PrepareTimeEdit->setObjectName(QString::fromUtf8("m_PrepareTimeEdit"));
        m_PrepareTimeEdit->setAlignment(Qt::AlignCenter);

        gridLayoutCommon->addWidget(m_PrepareTimeEdit, 2, 1, 1, 1);

        m_pStartEdit = new QSettingLineEdit(groupBoxCommon);
        m_pStartEdit->setObjectName(QString::fromUtf8("m_pStartEdit"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(m_pStartEdit->sizePolicy().hasHeightForWidth());
        m_pStartEdit->setSizePolicy(sizePolicy5);
        m_pStartEdit->setAlignment(Qt::AlignCenter);

        gridLayoutCommon->addWidget(m_pStartEdit, 1, 1, 1, 1);

        m_pStartLabel = new QLabel(groupBoxCommon);
        m_pStartLabel->setObjectName(QString::fromUtf8("m_pStartLabel"));
        sizePolicy4.setHeightForWidth(m_pStartLabel->sizePolicy().hasHeightForWidth());
        m_pStartLabel->setSizePolicy(sizePolicy4);
        m_pStartLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayoutCommon->addWidget(m_pStartLabel, 1, 0, 1, 1);

        m_PreFaultTimeLabel = new QLabel(groupBoxCommon);
        m_PreFaultTimeLabel->setObjectName(QString::fromUtf8("m_PreFaultTimeLabel"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(m_PreFaultTimeLabel->sizePolicy().hasHeightForWidth());
        m_PreFaultTimeLabel->setSizePolicy(sizePolicy6);
        m_PreFaultTimeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayoutCommon->addWidget(m_PreFaultTimeLabel, 2, 2, 1, 1);

        m_pEndLabel = new QLabel(groupBoxCommon);
        m_pEndLabel->setObjectName(QString::fromUtf8("m_pEndLabel"));
        sizePolicy6.setHeightForWidth(m_pEndLabel->sizePolicy().hasHeightForWidth());
        m_pEndLabel->setSizePolicy(sizePolicy6);
        m_pEndLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayoutCommon->addWidget(m_pEndLabel, 1, 2, 1, 1);

        m_pVarSelecLabel = new QLabel(groupBoxCommon);
        m_pVarSelecLabel->setObjectName(QString::fromUtf8("m_pVarSelecLabel"));
        sizePolicy4.setHeightForWidth(m_pVarSelecLabel->sizePolicy().hasHeightForWidth());
        m_pVarSelecLabel->setSizePolicy(sizePolicy4);
        m_pVarSelecLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayoutCommon->addWidget(m_pVarSelecLabel, 0, 0, 1, 1);

        m_pEndEdit = new QSettingLineEdit(groupBoxCommon);
        m_pEndEdit->setObjectName(QString::fromUtf8("m_pEndEdit"));
        m_pEndEdit->setAlignment(Qt::AlignCenter);

        gridLayoutCommon->addWidget(m_pEndEdit, 1, 3, 1, 1);

        m_pTimeLabel = new QLabel(groupBoxCommon);
        m_pTimeLabel->setObjectName(QString::fromUtf8("m_pTimeLabel"));
        m_pTimeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayoutCommon->addWidget(m_pTimeLabel, 0, 4, 1, 1);

        m_pCmb_ChangeType = new QScrollComboBox(groupBoxCommon);
        m_pCmb_ChangeType->setObjectName(QString::fromUtf8("m_pCmb_ChangeType"));

        gridLayoutCommon->addWidget(m_pCmb_ChangeType, 2, 5, 1, 1);

        m_PreFaultTimeEdit = new QSttLineEdit(groupBoxCommon);
        m_PreFaultTimeEdit->setObjectName(QString::fromUtf8("m_PreFaultTimeEdit"));
        m_PreFaultTimeEdit->setAlignment(Qt::AlignCenter);

        gridLayoutCommon->addWidget(m_PreFaultTimeEdit, 2, 3, 1, 1);

        m_pStepLabel = new QLabel(groupBoxCommon);
        m_pStepLabel->setObjectName(QString::fromUtf8("m_pStepLabel"));
        m_pStepLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayoutCommon->addWidget(m_pStepLabel, 1, 4, 1, 1);

        m_pTimeEdit = new QSettingLineEdit(groupBoxCommon);
        m_pTimeEdit->setObjectName(QString::fromUtf8("m_pTimeEdit"));
        m_pTimeEdit->setAlignment(Qt::AlignCenter);

        gridLayoutCommon->addWidget(m_pTimeEdit, 0, 5, 1, 1);

        m_pStepEdit = new QSettingLineEdit(groupBoxCommon);
        m_pStepEdit->setObjectName(QString::fromUtf8("m_pStepEdit"));
        m_pStepEdit->setAlignment(Qt::AlignCenter);

        gridLayoutCommon->addWidget(m_pStepEdit, 1, 5, 1, 1);

        m_pChangeTypeLabel = new QLabel(groupBoxCommon);
        m_pChangeTypeLabel->setObjectName(QString::fromUtf8("m_pChangeTypeLabel"));
        m_pChangeTypeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayoutCommon->addWidget(m_pChangeTypeLabel, 2, 4, 1, 1);

        m_pCmb_SecondMode = new QScrollComboBox(groupBoxCommon);
        m_pCmb_SecondMode->setObjectName(QString::fromUtf8("m_pCmb_SecondMode"));
        sizePolicy5.setHeightForWidth(m_pCmb_SecondMode->sizePolicy().hasHeightForWidth());
        m_pCmb_SecondMode->setSizePolicy(sizePolicy5);

        gridLayoutCommon->addWidget(m_pCmb_SecondMode, 0, 2, 1, 1);


        gridLayout_2->addWidget(groupBoxCommon, 6, 0, 2, 8);

        m_pCalModeLabel = new QLabel(m_pParaSetting_Widget);
        m_pCalModeLabel->setObjectName(QString::fromUtf8("m_pCalModeLabel"));
        m_pCalModeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_pCalModeLabel, 0, 4, 1, 2);

        m_pDLLabel = new QLabel(m_pParaSetting_Widget);
        m_pDLLabel->setObjectName(QString::fromUtf8("m_pDLLabel"));
        sizePolicy3.setHeightForWidth(m_pDLLabel->sizePolicy().hasHeightForWidth());
        m_pDLLabel->setSizePolicy(sizePolicy3);
        m_pDLLabel->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(m_pDLLabel, 4, 0, 1, 1);

        m_pFaultTypeLabel = new QLabel(m_pParaSetting_Widget);
        m_pFaultTypeLabel->setObjectName(QString::fromUtf8("m_pFaultTypeLabel"));
        sizePolicy3.setHeightForWidth(m_pFaultTypeLabel->sizePolicy().hasHeightForWidth());
        m_pFaultTypeLabel->setSizePolicy(sizePolicy3);
        m_pFaultTypeLabel->setMinimumSize(QSize(0, 50));
        m_pFaultTypeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_pFaultTypeLabel, 0, 0, 1, 1);

        m_pImpedlabel = new QLabel(m_pParaSetting_Widget);
        m_pImpedlabel->setObjectName(QString::fromUtf8("m_pImpedlabel"));
        sizePolicy3.setHeightForWidth(m_pImpedlabel->sizePolicy().hasHeightForWidth());
        m_pImpedlabel->setSizePolicy(sizePolicy3);
        m_pImpedlabel->setMinimumSize(QSize(0, 50));
        m_pImpedlabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_pImpedlabel, 1, 0, 1, 1);

        m_pTrigDelayLabel = new QLabel(m_pParaSetting_Widget);
        m_pTrigDelayLabel->setObjectName(QString::fromUtf8("m_pTrigDelayLabel"));
        sizePolicy3.setHeightForWidth(m_pTrigDelayLabel->sizePolicy().hasHeightForWidth());
        m_pTrigDelayLabel->setSizePolicy(sizePolicy3);
        m_pTrigDelayLabel->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(m_pTrigDelayLabel, 5, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_2, 0, 1, 1, 3);

        m_pImpedanceManuTab->addTab(m_pParaSetting_Widget, QString());

        gridLayout->addWidget(m_pImpedanceManuTab, 0, 0, 1, 1);


        retranslateUi(QImpedanceManuWidget);

        QMetaObject::connectSlotsByName(QImpedanceManuWidget);
    } // setupUi

    void retranslateUi(QWidget *QImpedanceManuWidget)
    {
        QImpedanceManuWidget->setWindowTitle(QApplication::translate("QImpedanceManuWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_pRad_Z->setText(QApplication::translate("QImpedanceManuWidget", "Z", 0, QApplication::UnicodeUTF8));
        m_pBinarySet_PushButton->setText(QApplication::translate("QImpedanceManuWidget", "\345\274\200\345\205\263\351\207\217", 0, QApplication::UnicodeUTF8));
        m_pEstimate_PushButton->setText(QApplication::translate("QImpedanceManuWidget", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        groupBoxCoe->setTitle(QApplication::translate("QImpedanceManuWidget", "\351\233\266\345\272\217\350\241\245\345\201\277\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        m_pCacuTypeLabel->setText(QApplication::translate("QImpedanceManuWidget", "\346\250\241\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_pAmpLabel->setText(QApplication::translate("QImpedanceManuWidget", "\345\271\205\345\200\274:", 0, QApplication::UnicodeUTF8));
        m_pAngleLabel->setText(QApplication::translate("QImpedanceManuWidget", "\347\233\270\350\247\222:", 0, QApplication::UnicodeUTF8));
        m_pAuto_CheckBox->setText(QApplication::translate("QImpedanceManuWidget", "\350\207\252\345\212\250\351\200\222\345\217\230", 0, QApplication::UnicodeUTF8));
        m_pMutation_CheckBox->setText(QApplication::translate("QImpedanceManuWidget", "\347\252\201\345\217\230\351\207\217\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        m_pLock_PushButton->setText(QApplication::translate("QImpedanceManuWidget", "\351\224\201", 0, QApplication::UnicodeUTF8));
        m_pbn_Down->setText(QApplication::translate("QImpedanceManuWidget", "-", 0, QApplication::UnicodeUTF8));
        m_pBoutGroupBox->setTitle(QApplication::translate("QImpedanceManuWidget", "\345\274\200\345\207\272\351\207\217", 0, QApplication::UnicodeUTF8));
        m_pBout_CheckBox0->setText(QApplication::translate("QImpedanceManuWidget", "1", 0, QApplication::UnicodeUTF8));
        m_pBout_CheckBox1->setText(QApplication::translate("QImpedanceManuWidget", "2", 0, QApplication::UnicodeUTF8));
        m_pBout_CheckBox2->setText(QApplication::translate("QImpedanceManuWidget", "3", 0, QApplication::UnicodeUTF8));
        m_pBout_CheckBox3->setText(QApplication::translate("QImpedanceManuWidget", "4", 0, QApplication::UnicodeUTF8));
        m_pbn_Up->setText(QApplication::translate("QImpedanceManuWidget", "+", 0, QApplication::UnicodeUTF8));
        m_pRXLabel->setText(QApplication::translate("QImpedanceManuWidget", "R,X\357\274\210\316\251\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_pZLabel->setText(QApplication::translate("QImpedanceManuWidget", "|Z|\357\274\210\316\251\357\274\211\357\274\214Phi\357\274\210\302\260\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_pRad_RX->setText(QApplication::translate("QImpedanceManuWidget", "R,X", 0, QApplication::UnicodeUTF8));
        groupBoxCommon->setTitle(QApplication::translate("QImpedanceManuWidget", "\351\200\222\345\217\230", 0, QApplication::UnicodeUTF8));
        m_PrepareTimeLabel->setText(QApplication::translate("QImpedanceManuWidget", "\345\270\270\346\200\201\346\227\266\351\227\264\357\274\210s\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_pStartLabel->setText(QApplication::translate("QImpedanceManuWidget", "\345\217\230\345\214\226\345\247\213\345\200\274\357\274\210\316\251\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_PreFaultTimeLabel->setText(QApplication::translate("QImpedanceManuWidget", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264\357\274\210s\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_pEndLabel->setText(QApplication::translate("QImpedanceManuWidget", "\345\217\230\345\214\226\347\273\210\345\200\274\357\274\210\316\251\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_pVarSelecLabel->setText(QApplication::translate("QImpedanceManuWidget", "\345\217\230\351\207\217\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_pTimeLabel->setText(QApplication::translate("QImpedanceManuWidget", "\345\217\230\345\214\226\346\227\266\351\227\264\357\274\210s\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_pStepLabel->setText(QApplication::translate("QImpedanceManuWidget", "\345\217\230\345\214\226\346\255\245\351\225\277\357\274\210\316\251\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_pChangeTypeLabel->setText(QApplication::translate("QImpedanceManuWidget", "\345\217\230\345\214\226\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_pCalModeLabel->setText(QApplication::translate("QImpedanceManuWidget", "\346\265\213\350\257\225\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_pDLLabel->setText(QApplication::translate("QImpedanceManuWidget", "\347\237\255\350\267\257\347\224\265\346\265\201\357\274\210A\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_pFaultTypeLabel->setText(QApplication::translate("QImpedanceManuWidget", "\346\225\205\351\232\234\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_pImpedlabel->setText(QApplication::translate("QImpedanceManuWidget", "\351\230\273\346\212\227\350\276\223\345\205\245\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_pTrigDelayLabel->setText(QApplication::translate("QImpedanceManuWidget", "\350\247\246\345\217\221\345\220\216\345\273\266\346\227\266\357\274\210s\357\274\211:", 0, QApplication::UnicodeUTF8));
        m_pImpedanceManuTab->setTabText(m_pImpedanceManuTab->indexOf(m_pParaSetting_Widget), QString());
    } // retranslateUi

};

namespace Ui {
    class QImpedanceManuWidget: public Ui_QImpedanceManuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPEDANCEMANUWIDGET_H
