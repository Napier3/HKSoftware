/********************************************************************************
** Form generated from reading UI file 'DiffCBOpCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFCBOPCOMMONPARASDLG_H
#define UI_DIFFCBOPCOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDiffCBOpCommonParasDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QComboBox *m_pCmbCoordinate;
    QLabel *m_pLabCTStarPoint;
    QLabel *m_pLabZeroSeqElimiType;
    QLabel *m_pLabBalanceTerms;
    QComboBox *m_pCmbCTStarPoint;
    QComboBox *m_pCmbIbiasCal;
    QLabel *m_pLabIbiasCal;
    QLineEdit *m_pEditFactor1;
    QLabel *m_pLabFactor2;
    QLineEdit *m_pEditFactor2;
    QLabel *m_pLabFactor1;
    QLabel *m_pLabComBineFeature;
    QLabel *m_pLabEarthing;
    QComboBox *m_pCmbComBineFeature;
    QComboBox *m_pCmbEarthing;
    QLineEdit *m_pEditCBTripTime;
    QLabel *m_pLabCoordinate;
    QLabel *m_pLabCBTripTime;
    QLabel *m_pLabCBCloseTime;
    QLineEdit *m_pEditCBCloseTime;
    QComboBox *m_pCmbBalanceTerms;
    QLineEdit *m_pEditStep;
    QLabel *m_pLabCBSimulation;
    QLabel *m_pLabStep;
    QLineEdit *m_pEditPreFaultTime;
    QLineEdit *m_pEditPrepareTime;
    QLabel *m_pLabPrepareTime;
    QLabel *m_pLabVg1;
    QLabel *m_pLabVg2;
    QLabel *m_pLabPreFaultTime;
    QLabel *m_pLabWindH;
    QLineEdit *m_pEditFaultTime;
    QLabel *m_pLabFaultTimeMargin;
    QLineEdit *m_pEditVg1;
    QComboBox *m_pCmbWindH;
    QLabel *m_pLabFaultTime;
    QSettingLineEdit *m_pEditActionHoldTime;
    QComboBox *m_pCmbCBSimulation;
    QLineEdit *m_pEditVg2;
    QLineEdit *m_pEditFaultTimeMargin;
    QLabel *m_pLabActionHoldTime;
    QComboBox *m_pCmbPhCorrectMode;
    QLabel *m_pLabPhCorrectMode;
    QComboBox *m_pCmbInsel;
    QLabel *m_pLabInsel;
    QComboBox *m_pCmbAdoptWind;
    QLabel *m_pLabInSet;
    QLabel *m_pLabAdoptWind;
    QLabel *m_pLabWindL;
    QComboBox *m_pCmbWindL;
    QLabel *m_pLabWindM;
    QComboBox *m_pCmbZeroSeqElimiType;
    QComboBox *m_pCmbWindM;
    QSettingLineEdit *m_pEditInSet;
    QLabel *m_pLabAroundClockNumHM;
    QComboBox *m_pCmbAroundClockNumHM;
    QLabel *m_pLabAroundClockNumHL;
    QComboBox *m_pCmbAroundClockNumHL;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pBtnOk;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_pBtnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QDiffCBOpCommonParasDlg)
    {
        if (QDiffCBOpCommonParasDlg->objectName().isEmpty())
            QDiffCBOpCommonParasDlg->setObjectName(QString::fromUtf8("QDiffCBOpCommonParasDlg"));
        QDiffCBOpCommonParasDlg->resize(860, 498);
        verticalLayout = new QVBoxLayout(QDiffCBOpCommonParasDlg);
        verticalLayout->setSpacing(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 11);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pCmbCoordinate = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbCoordinate->setObjectName(QString::fromUtf8("m_pCmbCoordinate"));
        QFont font;
        font.setPointSize(9);
        m_pCmbCoordinate->setFont(font);

        gridLayout->addWidget(m_pCmbCoordinate, 15, 3, 1, 1);

        m_pLabCTStarPoint = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabCTStarPoint->setObjectName(QString::fromUtf8("m_pLabCTStarPoint"));
        m_pLabCTStarPoint->setFont(font);

        gridLayout->addWidget(m_pLabCTStarPoint, 1, 2, 1, 1);

        m_pLabZeroSeqElimiType = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabZeroSeqElimiType->setObjectName(QString::fromUtf8("m_pLabZeroSeqElimiType"));
        m_pLabZeroSeqElimiType->setFont(font);

        gridLayout->addWidget(m_pLabZeroSeqElimiType, 6, 2, 1, 1);

        m_pLabBalanceTerms = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabBalanceTerms->setObjectName(QString::fromUtf8("m_pLabBalanceTerms"));
        m_pLabBalanceTerms->setFont(font);

        gridLayout->addWidget(m_pLabBalanceTerms, 0, 2, 1, 1);

        m_pCmbCTStarPoint = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbCTStarPoint->setObjectName(QString::fromUtf8("m_pCmbCTStarPoint"));
        m_pCmbCTStarPoint->setFont(font);

        gridLayout->addWidget(m_pCmbCTStarPoint, 1, 3, 1, 1);

        m_pCmbIbiasCal = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbIbiasCal->setObjectName(QString::fromUtf8("m_pCmbIbiasCal"));
        m_pCmbIbiasCal->setFont(font);

        gridLayout->addWidget(m_pCmbIbiasCal, 2, 3, 1, 1);

        m_pLabIbiasCal = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabIbiasCal->setObjectName(QString::fromUtf8("m_pLabIbiasCal"));
        m_pLabIbiasCal->setFont(font);

        gridLayout->addWidget(m_pLabIbiasCal, 2, 2, 1, 1);

        m_pEditFactor1 = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditFactor1->setObjectName(QString::fromUtf8("m_pEditFactor1"));
        m_pEditFactor1->setFont(font);

        gridLayout->addWidget(m_pEditFactor1, 3, 3, 1, 1);

        m_pLabFactor2 = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabFactor2->setObjectName(QString::fromUtf8("m_pLabFactor2"));
        m_pLabFactor2->setFont(font);

        gridLayout->addWidget(m_pLabFactor2, 4, 2, 1, 1);

        m_pEditFactor2 = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditFactor2->setObjectName(QString::fromUtf8("m_pEditFactor2"));
        m_pEditFactor2->setFont(font);

        gridLayout->addWidget(m_pEditFactor2, 4, 3, 1, 1);

        m_pLabFactor1 = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabFactor1->setObjectName(QString::fromUtf8("m_pLabFactor1"));
        m_pLabFactor1->setFont(font);

        gridLayout->addWidget(m_pLabFactor1, 3, 2, 1, 1);

        m_pLabComBineFeature = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabComBineFeature->setObjectName(QString::fromUtf8("m_pLabComBineFeature"));
        m_pLabComBineFeature->setFont(font);

        gridLayout->addWidget(m_pLabComBineFeature, 5, 2, 1, 1);

        m_pLabEarthing = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabEarthing->setObjectName(QString::fromUtf8("m_pLabEarthing"));
        m_pLabEarthing->setFont(font);

        gridLayout->addWidget(m_pLabEarthing, 7, 2, 1, 1);

        m_pCmbComBineFeature = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbComBineFeature->setObjectName(QString::fromUtf8("m_pCmbComBineFeature"));
        m_pCmbComBineFeature->setFont(font);

        gridLayout->addWidget(m_pCmbComBineFeature, 5, 3, 1, 1);

        m_pCmbEarthing = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbEarthing->setObjectName(QString::fromUtf8("m_pCmbEarthing"));
        m_pCmbEarthing->setFont(font);

        gridLayout->addWidget(m_pCmbEarthing, 7, 3, 1, 1);

        m_pEditCBTripTime = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditCBTripTime->setObjectName(QString::fromUtf8("m_pEditCBTripTime"));
        m_pEditCBTripTime->setFont(font);

        gridLayout->addWidget(m_pEditCBTripTime, 13, 3, 1, 1);

        m_pLabCoordinate = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabCoordinate->setObjectName(QString::fromUtf8("m_pLabCoordinate"));
        m_pLabCoordinate->setFont(font);

        gridLayout->addWidget(m_pLabCoordinate, 15, 2, 1, 1);

        m_pLabCBTripTime = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabCBTripTime->setObjectName(QString::fromUtf8("m_pLabCBTripTime"));
        m_pLabCBTripTime->setFont(font);

        gridLayout->addWidget(m_pLabCBTripTime, 13, 2, 1, 1);

        m_pLabCBCloseTime = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabCBCloseTime->setObjectName(QString::fromUtf8("m_pLabCBCloseTime"));
        m_pLabCBCloseTime->setFont(font);

        gridLayout->addWidget(m_pLabCBCloseTime, 14, 2, 1, 1);

        m_pEditCBCloseTime = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditCBCloseTime->setObjectName(QString::fromUtf8("m_pEditCBCloseTime"));
        m_pEditCBCloseTime->setFont(font);

        gridLayout->addWidget(m_pEditCBCloseTime, 14, 3, 1, 1);

        m_pCmbBalanceTerms = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbBalanceTerms->setObjectName(QString::fromUtf8("m_pCmbBalanceTerms"));
        m_pCmbBalanceTerms->setFont(font);

        gridLayout->addWidget(m_pCmbBalanceTerms, 0, 3, 1, 1);

        m_pEditStep = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditStep->setObjectName(QString::fromUtf8("m_pEditStep"));
        m_pEditStep->setFont(font);

        gridLayout->addWidget(m_pEditStep, 8, 3, 1, 1);

        m_pLabCBSimulation = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabCBSimulation->setObjectName(QString::fromUtf8("m_pLabCBSimulation"));
        m_pLabCBSimulation->setFont(font);

        gridLayout->addWidget(m_pLabCBSimulation, 11, 2, 1, 1);

        m_pLabStep = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabStep->setObjectName(QString::fromUtf8("m_pLabStep"));
        m_pLabStep->setFont(font);

        gridLayout->addWidget(m_pLabStep, 8, 2, 1, 1);

        m_pEditPreFaultTime = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditPreFaultTime->setObjectName(QString::fromUtf8("m_pEditPreFaultTime"));
        m_pEditPreFaultTime->setFont(font);

        gridLayout->addWidget(m_pEditPreFaultTime, 1, 1, 1, 1);

        m_pEditPrepareTime = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditPrepareTime->setObjectName(QString::fromUtf8("m_pEditPrepareTime"));
        m_pEditPrepareTime->setMaximumSize(QSize(16777215, 16777215));
        m_pEditPrepareTime->setFont(font);

        gridLayout->addWidget(m_pEditPrepareTime, 0, 1, 1, 1);

        m_pLabPrepareTime = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabPrepareTime->setObjectName(QString::fromUtf8("m_pLabPrepareTime"));
        m_pLabPrepareTime->setFont(font);

        gridLayout->addWidget(m_pLabPrepareTime, 0, 0, 1, 1);

        m_pLabVg1 = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabVg1->setObjectName(QString::fromUtf8("m_pLabVg1"));
        m_pLabVg1->setFont(font);

        gridLayout->addWidget(m_pLabVg1, 9, 2, 1, 1);

        m_pLabVg2 = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabVg2->setObjectName(QString::fromUtf8("m_pLabVg2"));
        m_pLabVg2->setFont(font);

        gridLayout->addWidget(m_pLabVg2, 10, 2, 1, 1);

        m_pLabPreFaultTime = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabPreFaultTime->setObjectName(QString::fromUtf8("m_pLabPreFaultTime"));
        m_pLabPreFaultTime->setFont(font);

        gridLayout->addWidget(m_pLabPreFaultTime, 1, 0, 1, 1);

        m_pLabWindH = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabWindH->setObjectName(QString::fromUtf8("m_pLabWindH"));
        m_pLabWindH->setFont(font);

        gridLayout->addWidget(m_pLabWindH, 5, 0, 1, 1);

        m_pEditFaultTime = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditFaultTime->setObjectName(QString::fromUtf8("m_pEditFaultTime"));
        m_pEditFaultTime->setFont(font);

        gridLayout->addWidget(m_pEditFaultTime, 2, 1, 1, 1);

        m_pLabFaultTimeMargin = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabFaultTimeMargin->setObjectName(QString::fromUtf8("m_pLabFaultTimeMargin"));
        m_pLabFaultTimeMargin->setFont(font);

        gridLayout->addWidget(m_pLabFaultTimeMargin, 3, 0, 1, 1);

        m_pEditVg1 = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditVg1->setObjectName(QString::fromUtf8("m_pEditVg1"));
        m_pEditVg1->setFont(font);

        gridLayout->addWidget(m_pEditVg1, 9, 3, 1, 1);

        m_pCmbWindH = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbWindH->setObjectName(QString::fromUtf8("m_pCmbWindH"));

        gridLayout->addWidget(m_pCmbWindH, 5, 1, 1, 1);

        m_pLabFaultTime = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabFaultTime->setObjectName(QString::fromUtf8("m_pLabFaultTime"));
        m_pLabFaultTime->setFont(font);

        gridLayout->addWidget(m_pLabFaultTime, 2, 0, 1, 1);

        m_pEditActionHoldTime = new QSettingLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditActionHoldTime->setObjectName(QString::fromUtf8("m_pEditActionHoldTime"));
        m_pEditActionHoldTime->setFont(font);

        gridLayout->addWidget(m_pEditActionHoldTime, 4, 1, 1, 1);

        m_pCmbCBSimulation = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbCBSimulation->setObjectName(QString::fromUtf8("m_pCmbCBSimulation"));
        m_pCmbCBSimulation->setFont(font);

        gridLayout->addWidget(m_pCmbCBSimulation, 11, 3, 1, 1);

        m_pEditVg2 = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditVg2->setObjectName(QString::fromUtf8("m_pEditVg2"));
        m_pEditVg2->setFont(font);

        gridLayout->addWidget(m_pEditVg2, 10, 3, 1, 1);

        m_pEditFaultTimeMargin = new QLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditFaultTimeMargin->setObjectName(QString::fromUtf8("m_pEditFaultTimeMargin"));
        m_pEditFaultTimeMargin->setFont(font);

        gridLayout->addWidget(m_pEditFaultTimeMargin, 3, 1, 1, 1);

        m_pLabActionHoldTime = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabActionHoldTime->setObjectName(QString::fromUtf8("m_pLabActionHoldTime"));
        m_pLabActionHoldTime->setFont(font);

        gridLayout->addWidget(m_pLabActionHoldTime, 4, 0, 1, 1);

        m_pCmbPhCorrectMode = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbPhCorrectMode->setObjectName(QString::fromUtf8("m_pCmbPhCorrectMode"));

        gridLayout->addWidget(m_pCmbPhCorrectMode, 8, 1, 1, 1);

        m_pLabPhCorrectMode = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabPhCorrectMode->setObjectName(QString::fromUtf8("m_pLabPhCorrectMode"));
        m_pLabPhCorrectMode->setFont(font);

        gridLayout->addWidget(m_pLabPhCorrectMode, 8, 0, 1, 1);

        m_pCmbInsel = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbInsel->setObjectName(QString::fromUtf8("m_pCmbInsel"));

        gridLayout->addWidget(m_pCmbInsel, 10, 1, 1, 1);

        m_pLabInsel = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabInsel->setObjectName(QString::fromUtf8("m_pLabInsel"));
        m_pLabInsel->setFont(font);

        gridLayout->addWidget(m_pLabInsel, 10, 0, 1, 1);

        m_pCmbAdoptWind = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbAdoptWind->setObjectName(QString::fromUtf8("m_pCmbAdoptWind"));

        gridLayout->addWidget(m_pCmbAdoptWind, 9, 1, 1, 1);

        m_pLabInSet = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabInSet->setObjectName(QString::fromUtf8("m_pLabInSet"));
        m_pLabInSet->setFont(font);

        gridLayout->addWidget(m_pLabInSet, 11, 0, 1, 1);

        m_pLabAdoptWind = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabAdoptWind->setObjectName(QString::fromUtf8("m_pLabAdoptWind"));
        m_pLabAdoptWind->setFont(font);

        gridLayout->addWidget(m_pLabAdoptWind, 9, 0, 1, 1);

        m_pLabWindL = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabWindL->setObjectName(QString::fromUtf8("m_pLabWindL"));
        m_pLabWindL->setFont(font);

        gridLayout->addWidget(m_pLabWindL, 7, 0, 1, 1);

        m_pCmbWindL = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbWindL->setObjectName(QString::fromUtf8("m_pCmbWindL"));

        gridLayout->addWidget(m_pCmbWindL, 7, 1, 1, 1);

        m_pLabWindM = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabWindM->setObjectName(QString::fromUtf8("m_pLabWindM"));
        m_pLabWindM->setFont(font);

        gridLayout->addWidget(m_pLabWindM, 6, 0, 1, 1);

        m_pCmbZeroSeqElimiType = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbZeroSeqElimiType->setObjectName(QString::fromUtf8("m_pCmbZeroSeqElimiType"));
        m_pCmbZeroSeqElimiType->setFont(font);

        gridLayout->addWidget(m_pCmbZeroSeqElimiType, 6, 3, 1, 1);

        m_pCmbWindM = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbWindM->setObjectName(QString::fromUtf8("m_pCmbWindM"));

        gridLayout->addWidget(m_pCmbWindM, 6, 1, 1, 1);

        m_pEditInSet = new QSettingLineEdit(QDiffCBOpCommonParasDlg);
        m_pEditInSet->setObjectName(QString::fromUtf8("m_pEditInSet"));
        m_pEditInSet->setFont(font);

        gridLayout->addWidget(m_pEditInSet, 11, 1, 1, 1);

        m_pLabAroundClockNumHM = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabAroundClockNumHM->setObjectName(QString::fromUtf8("m_pLabAroundClockNumHM"));
        m_pLabAroundClockNumHM->setFont(font);

        gridLayout->addWidget(m_pLabAroundClockNumHM, 13, 0, 1, 1);

        m_pCmbAroundClockNumHM = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbAroundClockNumHM->setObjectName(QString::fromUtf8("m_pCmbAroundClockNumHM"));
        m_pCmbAroundClockNumHM->setFont(font);

        gridLayout->addWidget(m_pCmbAroundClockNumHM, 13, 1, 1, 1);

        m_pLabAroundClockNumHL = new QLabel(QDiffCBOpCommonParasDlg);
        m_pLabAroundClockNumHL->setObjectName(QString::fromUtf8("m_pLabAroundClockNumHL"));
        m_pLabAroundClockNumHL->setFont(font);

        gridLayout->addWidget(m_pLabAroundClockNumHL, 14, 0, 1, 1);

        m_pCmbAroundClockNumHL = new QComboBox(QDiffCBOpCommonParasDlg);
        m_pCmbAroundClockNumHL->setObjectName(QString::fromUtf8("m_pCmbAroundClockNumHL"));
        m_pCmbAroundClockNumHL->setFont(font);

        gridLayout->addWidget(m_pCmbAroundClockNumHL, 14, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 10, -1, 10);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_pBtnOk = new QPushButton(QDiffCBOpCommonParasDlg);
        m_pBtnOk->setObjectName(QString::fromUtf8("m_pBtnOk"));

        horizontalLayout->addWidget(m_pBtnOk);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        m_pBtnCancel = new QPushButton(QDiffCBOpCommonParasDlg);
        m_pBtnCancel->setObjectName(QString::fromUtf8("m_pBtnCancel"));

        horizontalLayout->addWidget(m_pBtnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QDiffCBOpCommonParasDlg);

        QMetaObject::connectSlotsByName(QDiffCBOpCommonParasDlg);
    } // setupUi

    void retranslateUi(QWidget *QDiffCBOpCommonParasDlg)
    {
        QDiffCBOpCommonParasDlg->setWindowTitle(QApplication::translate("QDiffCBOpCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_pLabCTStarPoint->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "CT\346\236\201\346\200\247:", 0, QApplication::UnicodeUTF8));
        m_pLabZeroSeqElimiType->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\351\233\266\345\272\217\346\266\210\351\231\244\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        m_pLabBalanceTerms->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\271\263\350\241\241\347\263\273\346\225\260\350\256\241\347\256\227:", 0, QApplication::UnicodeUTF8));
        m_pLabIbiasCal->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\210\266\345\212\250\346\226\271\347\250\213:", 0, QApplication::UnicodeUTF8));
        m_pLabFactor2->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "K2:", 0, QApplication::UnicodeUTF8));
        m_pLabFactor1->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "K1:", 0, QApplication::UnicodeUTF8));
        m_pLabComBineFeature->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\244\215\345\220\210\347\211\271\346\200\247:", 0, QApplication::UnicodeUTF8));
        m_pLabEarthing->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\344\270\255\346\200\247\347\202\271\346\216\245\345\234\260:", 0, QApplication::UnicodeUTF8));
        m_pLabCoordinate->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\235\220\346\240\207:", 0, QApplication::UnicodeUTF8));
        m_pLabCBTripTime->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\210\206\351\227\270\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        m_pLabCBCloseTime->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\220\210\351\227\270\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        m_pLabCBSimulation->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\346\226\255\350\267\257\345\231\250\346\250\241\346\213\237:", 0, QApplication::UnicodeUTF8));
        m_pLabStep->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\346\265\213\350\257\225\347\262\276\345\272\246:", 0, QApplication::UnicodeUTF8));
        m_pLabPrepareTime->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\207\206\345\244\207\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_pLabVg1->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "Ua,Ub,Uc(V):", 0, QApplication::UnicodeUTF8));
        m_pLabVg2->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "Ua2,Ub2,Uc2(V):", 0, QApplication::UnicodeUTF8));
        m_pLabPreFaultTime->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_pLabWindH->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\351\253\230\345\216\213\344\276\247\347\273\225\347\273\204\346\216\245\347\272\277\345\236\213\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_pLabFaultTimeMargin->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\346\225\205\351\232\234\346\227\266\351\227\264\350\243\225\345\272\246(s):", 0, QApplication::UnicodeUTF8));
        m_pCmbWindH->clear();
        m_pCmbWindH->insertItems(0, QStringList()
         << QApplication::translate("QDiffCBOpCommonParasDlg", "Y", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffCBOpCommonParasDlg", "\342\226\263", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffCBOpCommonParasDlg", "Z", 0, QApplication::UnicodeUTF8)
        );
        m_pLabFaultTime->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_pLabActionHoldTime->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\212\250\344\275\234\345\220\216\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_pLabPhCorrectMode->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\346\240\241\346\255\243\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_pLabInsel->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\237\272\345\207\206\347\224\265\346\265\201:", 0, QApplication::UnicodeUTF8));
        m_pLabInSet->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\237\272\345\207\206\347\224\265\346\265\201\350\256\276\345\256\232\345\200\274:", 0, QApplication::UnicodeUTF8));
        m_pLabAdoptWind->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\346\265\213\350\257\225\347\273\225\347\273\204:", 0, QApplication::UnicodeUTF8));
        m_pLabWindL->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\344\275\216\345\216\213\344\276\247\347\273\225\347\273\204\346\216\245\347\272\277\345\236\213\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_pCmbWindL->clear();
        m_pCmbWindL->insertItems(0, QStringList()
         << QApplication::translate("QDiffCBOpCommonParasDlg", "Y", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffCBOpCommonParasDlg", "\342\226\263", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffCBOpCommonParasDlg", "Z", 0, QApplication::UnicodeUTF8)
        );
        m_pLabWindM->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\344\270\255\345\216\213\344\276\247\347\273\225\347\273\204\346\216\245\347\272\277\345\236\213\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_pCmbWindM->clear();
        m_pCmbWindM->insertItems(0, QStringList()
         << QApplication::translate("QDiffCBOpCommonParasDlg", "Y", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffCBOpCommonParasDlg", "\342\226\263", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffCBOpCommonParasDlg", "Z", 0, QApplication::UnicodeUTF8)
        );
        m_pLabAroundClockNumHM->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\351\253\230-\344\270\255\347\273\225\347\273\204\351\222\237\347\202\271\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_pLabAroundClockNumHL->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\351\253\230-\344\275\216\347\273\225\347\273\204\351\222\237\347\202\271\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_pBtnOk->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_pBtnCancel->setText(QApplication::translate("QDiffCBOpCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDiffCBOpCommonParasDlg: public Ui_QDiffCBOpCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFCBOPCOMMONPARASDLG_H
