/********************************************************************************
** Form generated from reading UI file 'QPowerDirAddMultDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPOWERDIRADDMULTDLG_H
#define UI_QPOWERDIRADDMULTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../Module/UI/Controls/SttCheckbox.h"
#include "../../Module/UI/Controls/SttGroupBox.h"
#include "../../Module/UI/Controls/SttLineEdit.h"
#include "../../UI/Controls/SettingCtrls/QSettingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QPowerDirAddMultDlg
{
public:
    QGridLayout *gridLayout_8;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_pCancel_PushButton;
    QPushButton *m_pOK_PushButton;
    QSpacerItem *horizontalSpacer;
    QSttGroupBox *m_groupBox;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QSttCheckBox *m_pBABC_CheckBox;
    QSttCheckBox *m_pBBC_CheckBox;
    QSttCheckBox *m_pCCN_CheckBox;
    QSttCheckBox *m_pBBN_CheckBox;
    QSttCheckBox *m_pAAB_CheckBox;
    QSttCheckBox *m_pZeroSeq_CheckBox;
    QSttCheckBox *m_pACA_CheckBox;
    QSttCheckBox *m_pZeroAN_CheckBox;
    QSttCheckBox *m_pAABC_CheckBox;
    QSttCheckBox *m_pNegativeSeq_CheckBox;
    QSttCheckBox *m_pZeroCN_CheckBox;
    QSttCheckBox *m_pNegativeAN_CheckBox;
    QSttCheckBox *m_pBAB_CheckBox;
    QSttCheckBox *m_pNegativeCN_CheckBox;
    QSttCheckBox *m_pNegativeAB_CheckBox;
    QSttCheckBox *m_pZeroBN_CheckBox;
    QSttCheckBox *m_pNegativeBN_CheckBox;
    QSttCheckBox *m_pNegativeBC_CheckBox;
    QSttCheckBox *m_pZeroSeqTest_CheckBox;
    QLabel *m_pTestItemsLabel;
    QCheckBox *m_pABTest_CheckBox;
    QSttCheckBox *m_pCTest_CheckBox;
    QSttCheckBox *m_pNegativeSeqTest_CheckBox;
    QSttCheckBox *m_pBCTest_CheckBox;
    QSttCheckBox *m_pAAN_CheckBox;
    QSttCheckBox *m_pATest_CheckBox;
    QSttCheckBox *m_pBTest_CheckBox;
    QSttCheckBox *m_pCATest_CheckBox;
    QSttCheckBox *m_pCCA_CheckBox;
    QSttCheckBox *m_pBCBC_CheckBox;
    QSttCheckBox *m_pCABC_CheckBox;
    QSttCheckBox *m_pCBC_CheckBox;
    QCheckBox *m_pABAB_CheckBox;
    QSttCheckBox *m_pCACA_CheckBox;
    QSttCheckBox *m_pNegativeCA_CheckBox;
    QLabel *m_pFaultDiffLabel;
    QSttGroupBox *m_groupBox_Results;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_5;
    QLabel *m_pErrorTypeLabel;
    CExBaseListComboBox *m_pCmb_ErrorType;
    QLabel *m_pRelErrorLabel;
    QLabel *m_pAbsErrorLabel;
    QSttLineEdit *m_pAbsErrorEdit;
    QSttLineEdit *m_pRelErrorEdit;
    QSttGroupBox *m_groupBox_FaultParas;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_4;
    QLabel *m_pFaultVLabel;
    QSttLineEdit *m_pFaultVEdit;
    QLabel *m_pFaultILabel;
    QSttLineEdit *m_pFaultIEdit;
    QLabel *m_pFaultTimeLabel;
    QSttLineEdit *m_pFaultTimeEdit;
    QSttGroupBox *m_groupBox_AngleParas;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_3;
    QLabel *m_pMaxSensitAngleLabel;
    QSettingLineEdit *m_pMaxSensitAngleEdit;
    QSttLineEdit *m_pActRangeEdit;
    QLabel *m_pActRangeLabel;
    QLabel *m_pStepLabel;
    QSttLineEdit *m_pStepEdit;

    void setupUi(QDialog *QPowerDirAddMultDlg)
    {
        if (QPowerDirAddMultDlg->objectName().isEmpty())
            QPowerDirAddMultDlg->setObjectName(QString::fromUtf8("QPowerDirAddMultDlg"));
        QPowerDirAddMultDlg->resize(792, 515);
        gridLayout_8 = new QGridLayout(QPowerDirAddMultDlg);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_3, 2, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(220, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_2, 2, 6, 1, 1);

        m_pCancel_PushButton = new QPushButton(QPowerDirAddMultDlg);
        m_pCancel_PushButton->setObjectName(QString::fromUtf8("m_pCancel_PushButton"));
        m_pCancel_PushButton->setAutoDefault(false);

        gridLayout_8->addWidget(m_pCancel_PushButton, 2, 4, 1, 1);

        m_pOK_PushButton = new QPushButton(QPowerDirAddMultDlg);
        m_pOK_PushButton->setObjectName(QString::fromUtf8("m_pOK_PushButton"));
        m_pOK_PushButton->setAutoDefault(false);

        gridLayout_8->addWidget(m_pOK_PushButton, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(220, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer, 2, 1, 1, 1);

        m_groupBox = new QSttGroupBox(QPowerDirAddMultDlg);
        m_groupBox->setObjectName(QString::fromUtf8("m_groupBox"));
        gridLayout = new QGridLayout(m_groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pBABC_CheckBox = new QSttCheckBox(m_groupBox);
        m_pBABC_CheckBox->setObjectName(QString::fromUtf8("m_pBABC_CheckBox"));

        gridLayout_2->addWidget(m_pBABC_CheckBox, 2, 4, 1, 1);

        m_pBBC_CheckBox = new QSttCheckBox(m_groupBox);
        m_pBBC_CheckBox->setObjectName(QString::fromUtf8("m_pBBC_CheckBox"));

        gridLayout_2->addWidget(m_pBBC_CheckBox, 2, 3, 1, 1);

        m_pCCN_CheckBox = new QSttCheckBox(m_groupBox);
        m_pCCN_CheckBox->setObjectName(QString::fromUtf8("m_pCCN_CheckBox"));

        gridLayout_2->addWidget(m_pCCN_CheckBox, 3, 1, 1, 1);

        m_pBBN_CheckBox = new QSttCheckBox(m_groupBox);
        m_pBBN_CheckBox->setObjectName(QString::fromUtf8("m_pBBN_CheckBox"));

        gridLayout_2->addWidget(m_pBBN_CheckBox, 2, 1, 1, 1);

        m_pAAB_CheckBox = new QSttCheckBox(m_groupBox);
        m_pAAB_CheckBox->setObjectName(QString::fromUtf8("m_pAAB_CheckBox"));

        gridLayout_2->addWidget(m_pAAB_CheckBox, 1, 2, 1, 1);

        m_pZeroSeq_CheckBox = new QSttCheckBox(m_groupBox);
        m_pZeroSeq_CheckBox->setObjectName(QString::fromUtf8("m_pZeroSeq_CheckBox"));

        gridLayout_2->addWidget(m_pZeroSeq_CheckBox, 7, 1, 1, 1);

        m_pACA_CheckBox = new QSttCheckBox(m_groupBox);
        m_pACA_CheckBox->setObjectName(QString::fromUtf8("m_pACA_CheckBox"));

        gridLayout_2->addWidget(m_pACA_CheckBox, 1, 3, 1, 1);

        m_pZeroAN_CheckBox = new QSttCheckBox(m_groupBox);
        m_pZeroAN_CheckBox->setObjectName(QString::fromUtf8("m_pZeroAN_CheckBox"));

        gridLayout_2->addWidget(m_pZeroAN_CheckBox, 7, 2, 1, 1);

        m_pAABC_CheckBox = new QSttCheckBox(m_groupBox);
        m_pAABC_CheckBox->setObjectName(QString::fromUtf8("m_pAABC_CheckBox"));

        gridLayout_2->addWidget(m_pAABC_CheckBox, 1, 4, 1, 1);

        m_pNegativeSeq_CheckBox = new QSttCheckBox(m_groupBox);
        m_pNegativeSeq_CheckBox->setObjectName(QString::fromUtf8("m_pNegativeSeq_CheckBox"));

        gridLayout_2->addWidget(m_pNegativeSeq_CheckBox, 8, 1, 1, 1);

        m_pZeroCN_CheckBox = new QSttCheckBox(m_groupBox);
        m_pZeroCN_CheckBox->setObjectName(QString::fromUtf8("m_pZeroCN_CheckBox"));

        gridLayout_2->addWidget(m_pZeroCN_CheckBox, 7, 4, 1, 1);

        m_pNegativeAN_CheckBox = new QSttCheckBox(m_groupBox);
        m_pNegativeAN_CheckBox->setObjectName(QString::fromUtf8("m_pNegativeAN_CheckBox"));

        gridLayout_2->addWidget(m_pNegativeAN_CheckBox, 8, 2, 1, 1);

        m_pBAB_CheckBox = new QSttCheckBox(m_groupBox);
        m_pBAB_CheckBox->setObjectName(QString::fromUtf8("m_pBAB_CheckBox"));

        gridLayout_2->addWidget(m_pBAB_CheckBox, 2, 2, 1, 1);

        m_pNegativeCN_CheckBox = new QSttCheckBox(m_groupBox);
        m_pNegativeCN_CheckBox->setObjectName(QString::fromUtf8("m_pNegativeCN_CheckBox"));

        gridLayout_2->addWidget(m_pNegativeCN_CheckBox, 8, 4, 1, 1);

        m_pNegativeAB_CheckBox = new QSttCheckBox(m_groupBox);
        m_pNegativeAB_CheckBox->setObjectName(QString::fromUtf8("m_pNegativeAB_CheckBox"));

        gridLayout_2->addWidget(m_pNegativeAB_CheckBox, 8, 5, 1, 1);

        m_pZeroBN_CheckBox = new QSttCheckBox(m_groupBox);
        m_pZeroBN_CheckBox->setObjectName(QString::fromUtf8("m_pZeroBN_CheckBox"));

        gridLayout_2->addWidget(m_pZeroBN_CheckBox, 7, 3, 1, 1);

        m_pNegativeBN_CheckBox = new QSttCheckBox(m_groupBox);
        m_pNegativeBN_CheckBox->setObjectName(QString::fromUtf8("m_pNegativeBN_CheckBox"));

        gridLayout_2->addWidget(m_pNegativeBN_CheckBox, 8, 3, 1, 1);

        m_pNegativeBC_CheckBox = new QSttCheckBox(m_groupBox);
        m_pNegativeBC_CheckBox->setObjectName(QString::fromUtf8("m_pNegativeBC_CheckBox"));

        gridLayout_2->addWidget(m_pNegativeBC_CheckBox, 8, 6, 1, 1);

        m_pZeroSeqTest_CheckBox = new QSttCheckBox(m_groupBox);
        m_pZeroSeqTest_CheckBox->setObjectName(QString::fromUtf8("m_pZeroSeqTest_CheckBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pZeroSeqTest_CheckBox->sizePolicy().hasHeightForWidth());
        m_pZeroSeqTest_CheckBox->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_pZeroSeqTest_CheckBox, 7, 0, 1, 1);

        m_pTestItemsLabel = new QLabel(m_groupBox);
        m_pTestItemsLabel->setObjectName(QString::fromUtf8("m_pTestItemsLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pTestItemsLabel->sizePolicy().hasHeightForWidth());
        m_pTestItemsLabel->setSizePolicy(sizePolicy1);
        m_pTestItemsLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_pTestItemsLabel, 0, 0, 1, 1);

        m_pABTest_CheckBox = new QCheckBox(m_groupBox);
        m_pABTest_CheckBox->setObjectName(QString::fromUtf8("m_pABTest_CheckBox"));
        sizePolicy.setHeightForWidth(m_pABTest_CheckBox->sizePolicy().hasHeightForWidth());
        m_pABTest_CheckBox->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_pABTest_CheckBox, 4, 0, 1, 1);

        m_pCTest_CheckBox = new QSttCheckBox(m_groupBox);
        m_pCTest_CheckBox->setObjectName(QString::fromUtf8("m_pCTest_CheckBox"));
        sizePolicy.setHeightForWidth(m_pCTest_CheckBox->sizePolicy().hasHeightForWidth());
        m_pCTest_CheckBox->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_pCTest_CheckBox, 3, 0, 1, 1);

        m_pNegativeSeqTest_CheckBox = new QSttCheckBox(m_groupBox);
        m_pNegativeSeqTest_CheckBox->setObjectName(QString::fromUtf8("m_pNegativeSeqTest_CheckBox"));
        sizePolicy.setHeightForWidth(m_pNegativeSeqTest_CheckBox->sizePolicy().hasHeightForWidth());
        m_pNegativeSeqTest_CheckBox->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_pNegativeSeqTest_CheckBox, 8, 0, 1, 1);

        m_pBCTest_CheckBox = new QSttCheckBox(m_groupBox);
        m_pBCTest_CheckBox->setObjectName(QString::fromUtf8("m_pBCTest_CheckBox"));
        sizePolicy.setHeightForWidth(m_pBCTest_CheckBox->sizePolicy().hasHeightForWidth());
        m_pBCTest_CheckBox->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_pBCTest_CheckBox, 5, 0, 1, 1);

        m_pAAN_CheckBox = new QSttCheckBox(m_groupBox);
        m_pAAN_CheckBox->setObjectName(QString::fromUtf8("m_pAAN_CheckBox"));

        gridLayout_2->addWidget(m_pAAN_CheckBox, 1, 1, 1, 1);

        m_pATest_CheckBox = new QSttCheckBox(m_groupBox);
        m_pATest_CheckBox->setObjectName(QString::fromUtf8("m_pATest_CheckBox"));
        sizePolicy.setHeightForWidth(m_pATest_CheckBox->sizePolicy().hasHeightForWidth());
        m_pATest_CheckBox->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_pATest_CheckBox, 1, 0, 1, 1);

        m_pBTest_CheckBox = new QSttCheckBox(m_groupBox);
        m_pBTest_CheckBox->setObjectName(QString::fromUtf8("m_pBTest_CheckBox"));
        sizePolicy.setHeightForWidth(m_pBTest_CheckBox->sizePolicy().hasHeightForWidth());
        m_pBTest_CheckBox->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_pBTest_CheckBox, 2, 0, 1, 1);

        m_pCATest_CheckBox = new QSttCheckBox(m_groupBox);
        m_pCATest_CheckBox->setObjectName(QString::fromUtf8("m_pCATest_CheckBox"));
        sizePolicy.setHeightForWidth(m_pCATest_CheckBox->sizePolicy().hasHeightForWidth());
        m_pCATest_CheckBox->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_pCATest_CheckBox, 6, 0, 1, 1);

        m_pCCA_CheckBox = new QSttCheckBox(m_groupBox);
        m_pCCA_CheckBox->setObjectName(QString::fromUtf8("m_pCCA_CheckBox"));

        gridLayout_2->addWidget(m_pCCA_CheckBox, 3, 3, 1, 1);

        m_pBCBC_CheckBox = new QSttCheckBox(m_groupBox);
        m_pBCBC_CheckBox->setObjectName(QString::fromUtf8("m_pBCBC_CheckBox"));

        gridLayout_2->addWidget(m_pBCBC_CheckBox, 5, 1, 1, 1);

        m_pCABC_CheckBox = new QSttCheckBox(m_groupBox);
        m_pCABC_CheckBox->setObjectName(QString::fromUtf8("m_pCABC_CheckBox"));

        gridLayout_2->addWidget(m_pCABC_CheckBox, 3, 4, 1, 1);

        m_pCBC_CheckBox = new QSttCheckBox(m_groupBox);
        m_pCBC_CheckBox->setObjectName(QString::fromUtf8("m_pCBC_CheckBox"));

        gridLayout_2->addWidget(m_pCBC_CheckBox, 3, 2, 1, 1);

        m_pABAB_CheckBox = new QCheckBox(m_groupBox);
        m_pABAB_CheckBox->setObjectName(QString::fromUtf8("m_pABAB_CheckBox"));

        gridLayout_2->addWidget(m_pABAB_CheckBox, 4, 1, 1, 1);

        m_pCACA_CheckBox = new QSttCheckBox(m_groupBox);
        m_pCACA_CheckBox->setObjectName(QString::fromUtf8("m_pCACA_CheckBox"));

        gridLayout_2->addWidget(m_pCACA_CheckBox, 6, 1, 1, 1);

        m_pNegativeCA_CheckBox = new QSttCheckBox(m_groupBox);
        m_pNegativeCA_CheckBox->setObjectName(QString::fromUtf8("m_pNegativeCA_CheckBox"));

        gridLayout_2->addWidget(m_pNegativeCA_CheckBox, 8, 7, 1, 1);

        m_pFaultDiffLabel = new QLabel(m_groupBox);
        m_pFaultDiffLabel->setObjectName(QString::fromUtf8("m_pFaultDiffLabel"));
        sizePolicy1.setHeightForWidth(m_pFaultDiffLabel->sizePolicy().hasHeightForWidth());
        m_pFaultDiffLabel->setSizePolicy(sizePolicy1);
        m_pFaultDiffLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_pFaultDiffLabel, 0, 1, 1, 7);


        gridLayout->addLayout(gridLayout_2, 2, 6, 1, 1);


        gridLayout_8->addWidget(m_groupBox, 0, 1, 1, 7);

        m_groupBox_Results = new QSttGroupBox(QPowerDirAddMultDlg);
        m_groupBox_Results->setObjectName(QString::fromUtf8("m_groupBox_Results"));
        horizontalLayout = new QHBoxLayout(m_groupBox_Results);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_pErrorTypeLabel = new QLabel(m_groupBox_Results);
        m_pErrorTypeLabel->setObjectName(QString::fromUtf8("m_pErrorTypeLabel"));

        gridLayout_5->addWidget(m_pErrorTypeLabel, 0, 0, 1, 1);

        m_pCmb_ErrorType = new CExBaseListComboBox(m_groupBox_Results);
        m_pCmb_ErrorType->setObjectName(QString::fromUtf8("m_pCmb_ErrorType"));

        gridLayout_5->addWidget(m_pCmb_ErrorType, 0, 1, 1, 1);

        m_pRelErrorLabel = new QLabel(m_groupBox_Results);
        m_pRelErrorLabel->setObjectName(QString::fromUtf8("m_pRelErrorLabel"));

        gridLayout_5->addWidget(m_pRelErrorLabel, 1, 0, 1, 1);

        m_pAbsErrorLabel = new QLabel(m_groupBox_Results);
        m_pAbsErrorLabel->setObjectName(QString::fromUtf8("m_pAbsErrorLabel"));

        gridLayout_5->addWidget(m_pAbsErrorLabel, 2, 0, 1, 1);

        m_pAbsErrorEdit = new QSttLineEdit(m_groupBox_Results);
        m_pAbsErrorEdit->setObjectName(QString::fromUtf8("m_pAbsErrorEdit"));
        sizePolicy1.setHeightForWidth(m_pAbsErrorEdit->sizePolicy().hasHeightForWidth());
        m_pAbsErrorEdit->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_pAbsErrorEdit, 2, 1, 1, 1);

        m_pRelErrorEdit = new QSttLineEdit(m_groupBox_Results);
        m_pRelErrorEdit->setObjectName(QString::fromUtf8("m_pRelErrorEdit"));
        sizePolicy1.setHeightForWidth(m_pRelErrorEdit->sizePolicy().hasHeightForWidth());
        m_pRelErrorEdit->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_pRelErrorEdit, 1, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_5);


        gridLayout_8->addWidget(m_groupBox_Results, 1, 5, 1, 3);

        m_groupBox_FaultParas = new QSttGroupBox(QPowerDirAddMultDlg);
        m_groupBox_FaultParas->setObjectName(QString::fromUtf8("m_groupBox_FaultParas"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_groupBox_FaultParas->sizePolicy().hasHeightForWidth());
        m_groupBox_FaultParas->setSizePolicy(sizePolicy2);
        gridLayout_6 = new QGridLayout(m_groupBox_FaultParas);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_pFaultVLabel = new QLabel(m_groupBox_FaultParas);
        m_pFaultVLabel->setObjectName(QString::fromUtf8("m_pFaultVLabel"));

        gridLayout_4->addWidget(m_pFaultVLabel, 0, 0, 1, 1);

        m_pFaultVEdit = new QSttLineEdit(m_groupBox_FaultParas);
        m_pFaultVEdit->setObjectName(QString::fromUtf8("m_pFaultVEdit"));
        sizePolicy1.setHeightForWidth(m_pFaultVEdit->sizePolicy().hasHeightForWidth());
        m_pFaultVEdit->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pFaultVEdit, 0, 1, 1, 1);

        m_pFaultILabel = new QLabel(m_groupBox_FaultParas);
        m_pFaultILabel->setObjectName(QString::fromUtf8("m_pFaultILabel"));

        gridLayout_4->addWidget(m_pFaultILabel, 1, 0, 1, 1);

        m_pFaultIEdit = new QSttLineEdit(m_groupBox_FaultParas);
        m_pFaultIEdit->setObjectName(QString::fromUtf8("m_pFaultIEdit"));
        sizePolicy1.setHeightForWidth(m_pFaultIEdit->sizePolicy().hasHeightForWidth());
        m_pFaultIEdit->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pFaultIEdit, 1, 1, 1, 1);

        m_pFaultTimeLabel = new QLabel(m_groupBox_FaultParas);
        m_pFaultTimeLabel->setObjectName(QString::fromUtf8("m_pFaultTimeLabel"));

        gridLayout_4->addWidget(m_pFaultTimeLabel, 2, 0, 1, 1);

        m_pFaultTimeEdit = new QSttLineEdit(m_groupBox_FaultParas);
        m_pFaultTimeEdit->setObjectName(QString::fromUtf8("m_pFaultTimeEdit"));
        sizePolicy1.setHeightForWidth(m_pFaultTimeEdit->sizePolicy().hasHeightForWidth());
        m_pFaultTimeEdit->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pFaultTimeEdit, 2, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 0, 0, 1, 1);


        gridLayout_8->addWidget(m_groupBox_FaultParas, 1, 1, 1, 1);

        m_groupBox_AngleParas = new QSttGroupBox(QPowerDirAddMultDlg);
        m_groupBox_AngleParas->setObjectName(QString::fromUtf8("m_groupBox_AngleParas"));
        sizePolicy2.setHeightForWidth(m_groupBox_AngleParas->sizePolicy().hasHeightForWidth());
        m_groupBox_AngleParas->setSizePolicy(sizePolicy2);
        gridLayout_7 = new QGridLayout(m_groupBox_AngleParas);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_pMaxSensitAngleLabel = new QLabel(m_groupBox_AngleParas);
        m_pMaxSensitAngleLabel->setObjectName(QString::fromUtf8("m_pMaxSensitAngleLabel"));

        gridLayout_3->addWidget(m_pMaxSensitAngleLabel, 0, 0, 1, 1);

        m_pMaxSensitAngleEdit = new QSettingLineEdit(m_groupBox_AngleParas);
        m_pMaxSensitAngleEdit->setObjectName(QString::fromUtf8("m_pMaxSensitAngleEdit"));
        sizePolicy1.setHeightForWidth(m_pMaxSensitAngleEdit->sizePolicy().hasHeightForWidth());
        m_pMaxSensitAngleEdit->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_pMaxSensitAngleEdit, 0, 1, 1, 1);

        m_pActRangeEdit = new QSttLineEdit(m_groupBox_AngleParas);
        m_pActRangeEdit->setObjectName(QString::fromUtf8("m_pActRangeEdit"));
        sizePolicy1.setHeightForWidth(m_pActRangeEdit->sizePolicy().hasHeightForWidth());
        m_pActRangeEdit->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_pActRangeEdit, 1, 1, 1, 1);

        m_pActRangeLabel = new QLabel(m_groupBox_AngleParas);
        m_pActRangeLabel->setObjectName(QString::fromUtf8("m_pActRangeLabel"));

        gridLayout_3->addWidget(m_pActRangeLabel, 1, 0, 1, 1);

        m_pStepLabel = new QLabel(m_groupBox_AngleParas);
        m_pStepLabel->setObjectName(QString::fromUtf8("m_pStepLabel"));

        gridLayout_3->addWidget(m_pStepLabel, 2, 0, 1, 1);

        m_pStepEdit = new QSttLineEdit(m_groupBox_AngleParas);
        m_pStepEdit->setObjectName(QString::fromUtf8("m_pStepEdit"));
        sizePolicy1.setHeightForWidth(m_pStepEdit->sizePolicy().hasHeightForWidth());
        m_pStepEdit->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_pStepEdit, 2, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_3, 0, 1, 1, 1);


        gridLayout_8->addWidget(m_groupBox_AngleParas, 1, 2, 1, 3);


        retranslateUi(QPowerDirAddMultDlg);

        QMetaObject::connectSlotsByName(QPowerDirAddMultDlg);
    } // setupUi

    void retranslateUi(QDialog *QPowerDirAddMultDlg)
    {
        QPowerDirAddMultDlg->setWindowTitle(QApplication::translate("QPowerDirAddMultDlg", "\345\274\200\345\205\263\351\207\217", 0, QApplication::UnicodeUTF8));
        m_pCancel_PushButton->setText(QApplication::translate("QPowerDirAddMultDlg", "\345\217\226  \346\266\210", 0, QApplication::UnicodeUTF8));
        m_pOK_PushButton->setText(QApplication::translate("QPowerDirAddMultDlg", "\347\241\256  \350\256\244", 0, QApplication::UnicodeUTF8));
        m_groupBox->setTitle(QString());
        m_pBABC_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "ABC", 0, QApplication::UnicodeUTF8));
        m_pBBC_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "BC", 0, QApplication::UnicodeUTF8));
        m_pCCN_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "CN", 0, QApplication::UnicodeUTF8));
        m_pBBN_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "BN", 0, QApplication::UnicodeUTF8));
        m_pAAB_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "AB", 0, QApplication::UnicodeUTF8));
        m_pZeroSeq_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "\351\233\266\345\272\217", 0, QApplication::UnicodeUTF8));
        m_pACA_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "CA", 0, QApplication::UnicodeUTF8));
        m_pZeroAN_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "AN", 0, QApplication::UnicodeUTF8));
        m_pAABC_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "ABC", 0, QApplication::UnicodeUTF8));
        m_pNegativeSeq_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "\350\264\237\345\272\217", 0, QApplication::UnicodeUTF8));
        m_pZeroCN_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "CN", 0, QApplication::UnicodeUTF8));
        m_pNegativeAN_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "AN", 0, QApplication::UnicodeUTF8));
        m_pBAB_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "AB", 0, QApplication::UnicodeUTF8));
        m_pNegativeCN_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "CN", 0, QApplication::UnicodeUTF8));
        m_pNegativeAB_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "AB", 0, QApplication::UnicodeUTF8));
        m_pZeroBN_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "BN", 0, QApplication::UnicodeUTF8));
        m_pNegativeBN_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "BN", 0, QApplication::UnicodeUTF8));
        m_pNegativeBC_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "BC", 0, QApplication::UnicodeUTF8));
        m_pZeroSeqTest_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "\351\233\266\345\272\217\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pTestItemsLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\346\265\213\350\257\225\351\241\271", 0, QApplication::UnicodeUTF8));
        m_pABTest_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "AB\347\233\270\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pCTest_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "C\347\233\270\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pNegativeSeqTest_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "\350\264\237\345\272\217\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pBCTest_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "BC\347\233\270\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pAAN_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "AN", 0, QApplication::UnicodeUTF8));
        m_pATest_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "A\347\233\270\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pBTest_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "B\347\233\270\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pCATest_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "CA\347\233\270\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        m_pCCA_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "CA", 0, QApplication::UnicodeUTF8));
        m_pBCBC_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "BC", 0, QApplication::UnicodeUTF8));
        m_pCABC_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "ABC", 0, QApplication::UnicodeUTF8));
        m_pCBC_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "BC", 0, QApplication::UnicodeUTF8));
        m_pABAB_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "AB", 0, QApplication::UnicodeUTF8));
        m_pCACA_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "CA", 0, QApplication::UnicodeUTF8));
        m_pNegativeCA_CheckBox->setText(QApplication::translate("QPowerDirAddMultDlg", "CA", 0, QApplication::UnicodeUTF8));
        m_pFaultDiffLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\346\225\205\351\232\234\347\233\270\345\210\253", 0, QApplication::UnicodeUTF8));
        m_groupBox_Results->setTitle(QApplication::translate("QPowerDirAddMultDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_pErrorTypeLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\350\257\257\345\267\256\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        m_pRelErrorLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(%)", 0, QApplication::UnicodeUTF8));
        m_pAbsErrorLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(\302\260)", 0, QApplication::UnicodeUTF8));
        m_groupBox_FaultParas->setTitle(QApplication::translate("QPowerDirAddMultDlg", "\346\225\205\351\232\234\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_pFaultVLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\346\225\205\351\232\234\347\224\265\345\216\213(V)", 0, QApplication::UnicodeUTF8));
        m_pFaultILabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\346\225\205\351\232\234\347\224\265\346\265\201(A)", 0, QApplication::UnicodeUTF8));
        m_pFaultTimeLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\346\225\205\351\232\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_groupBox_AngleParas->setTitle(QApplication::translate("QPowerDirAddMultDlg", "\350\257\225\351\252\214\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_pMaxSensitAngleLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\346\234\200\345\244\247\347\201\265\346\225\217\350\247\222(\302\260)", 0, QApplication::UnicodeUTF8));
        m_pActRangeLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\345\212\250\344\275\234\345\214\272\350\214\203\345\233\264(\302\260)", 0, QApplication::UnicodeUTF8));
        m_pStepLabel->setText(QApplication::translate("QPowerDirAddMultDlg", "\345\217\230\345\214\226\346\255\245\351\225\277(\302\260)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QPowerDirAddMultDlg: public Ui_QPowerDirAddMultDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPOWERDIRADDMULTDLG_H
