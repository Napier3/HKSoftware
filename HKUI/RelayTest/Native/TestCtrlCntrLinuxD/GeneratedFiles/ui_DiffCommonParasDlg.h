/********************************************************************************
** Form generated from reading UI file 'DiffCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFCOMMONPARASDLG_H
#define UI_DIFFCOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"
#include "../../UI/Module/CommonCtrl_QT/QDataTypeComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QDiffCommonParasDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *m_labIrEquation;
    QLabel *m_labK;
    QLabel *m_labTransGroupMode2;
    QLabel *m_labTransGroupMode1;
    QLabel *m_labCTPoint;
    QLabel *m_labEarthing;
    QLabel *m_labK2;
    QLabel *m_labSearchMode;
    QLabel *m_labAdoptWind;
    QLabel *m_labJXFactor;
    QLabel *m_labWindH;
    QLabel *m_labVg1;
    QLabel *m_labVg2;
    QLabel *m_labStep;
    QLabel *m_labPhCorrectMode;
    QLabel *m_labWindL;
    QLabel *m_labWindM;
    QLabel *m_labPrepareTime;
    QLabel *m_labHUn;
    QSettingLineEdit *m_txtLUn;
    QLabel *m_labTimeAfter;
    QLineEdit *m_txtPrepareTime;
    QLabel *m_labLUn;
    QSettingLineEdit *m_txtCTSl;
    QLabel *m_labKphSet;
    QLabel *m_labKpmSet;
    QLabel *m_labFaultTime;
    QSettingLineEdit *m_txtTimeAfter;
    QComboBox *m_cmbKPSetMode;
    QLabel *m_labCTPh;
    QLineEdit *m_txtFaultTime;
    QLabel *m_labCTSh;
    QLabel *m_labMUn;
    QSettingLineEdit *m_txtCTSh;
    QSettingLineEdit *m_txtCTSm;
    QLabel *m_labCTSl;
    QSettingLineEdit *m_txtKphSet;
    QSettingLineEdit *m_txtCTPm;
    QSettingLineEdit *m_txtCTPl;
    QSettingLineEdit *m_txtSn;
    QLabel *m_labPreFaultTime;
    QLineEdit *m_txtPreFaultTime;
    QSettingLineEdit *m_txtMUn;
    QLabel *m_labSn;
    QSettingLineEdit *m_txtCTPh;
    QLabel *m_labCTPm;
    QLabel *m_labKPSetMode;
    QSettingLineEdit *m_txtHUn;
    QLabel *m_labCTPl;
    QLabel *m_labCTSm;
    QSettingLineEdit *m_txtKplSet;
    QLabel *m_labKplSet;
    QSettingLineEdit *m_txtKpmSet;
    QComboBox *m_cmbWindH;
    QComboBox *m_cmbWindM;
    QComboBox *m_cmbWindL;
    QDataTypeComboBox *m_cmbPhCorrectMode;
    QComboBox *m_cmbAdoptWind;
    QComboBox *m_cmbTransGroupMode1;
    QComboBox *m_cmbTransGroupMode2;
    QComboBox *m_cmbJXFactor;
    QComboBox *m_cmbSearchMode;
    QComboBox *m_cmbCTPoint;
    QComboBox *m_cmbIrEquation;
    QLineEdit *m_txtK;
    QLineEdit *m_txtK2;
    QComboBox *m_cmbEarthing;
    QLineEdit *m_txtStep;
    QLineEdit *m_txtVg1;
    QLineEdit *m_txtVg2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOK;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *QDiffCommonParasDlg)
    {
        if (QDiffCommonParasDlg->objectName().isEmpty())
            QDiffCommonParasDlg->setObjectName(QString::fromUtf8("QDiffCommonParasDlg"));
        QDiffCommonParasDlg->resize(838, 623);
        verticalLayout = new QVBoxLayout(QDiffCommonParasDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labIrEquation = new QLabel(QDiffCommonParasDlg);
        m_labIrEquation->setObjectName(QString::fromUtf8("m_labIrEquation"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labIrEquation->sizePolicy().hasHeightForWidth());
        m_labIrEquation->setSizePolicy(sizePolicy);
        m_labIrEquation->setMinimumSize(QSize(180, 0));
        m_labIrEquation->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labIrEquation, 10, 2, 1, 1);

        m_labK = new QLabel(QDiffCommonParasDlg);
        m_labK->setObjectName(QString::fromUtf8("m_labK"));
        sizePolicy.setHeightForWidth(m_labK->sizePolicy().hasHeightForWidth());
        m_labK->setSizePolicy(sizePolicy);
        m_labK->setMinimumSize(QSize(180, 0));
        m_labK->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labK, 11, 2, 1, 1);

        m_labTransGroupMode2 = new QLabel(QDiffCommonParasDlg);
        m_labTransGroupMode2->setObjectName(QString::fromUtf8("m_labTransGroupMode2"));
        sizePolicy.setHeightForWidth(m_labTransGroupMode2->sizePolicy().hasHeightForWidth());
        m_labTransGroupMode2->setSizePolicy(sizePolicy);
        m_labTransGroupMode2->setMinimumSize(QSize(180, 0));
        m_labTransGroupMode2->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labTransGroupMode2, 6, 2, 1, 1);

        m_labTransGroupMode1 = new QLabel(QDiffCommonParasDlg);
        m_labTransGroupMode1->setObjectName(QString::fromUtf8("m_labTransGroupMode1"));
        sizePolicy.setHeightForWidth(m_labTransGroupMode1->sizePolicy().hasHeightForWidth());
        m_labTransGroupMode1->setSizePolicy(sizePolicy);
        m_labTransGroupMode1->setMinimumSize(QSize(180, 0));
        m_labTransGroupMode1->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labTransGroupMode1, 5, 2, 1, 1);

        m_labCTPoint = new QLabel(QDiffCommonParasDlg);
        m_labCTPoint->setObjectName(QString::fromUtf8("m_labCTPoint"));
        sizePolicy.setHeightForWidth(m_labCTPoint->sizePolicy().hasHeightForWidth());
        m_labCTPoint->setSizePolicy(sizePolicy);
        m_labCTPoint->setMinimumSize(QSize(180, 0));
        m_labCTPoint->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labCTPoint, 9, 2, 1, 1);

        m_labEarthing = new QLabel(QDiffCommonParasDlg);
        m_labEarthing->setObjectName(QString::fromUtf8("m_labEarthing"));
        sizePolicy.setHeightForWidth(m_labEarthing->sizePolicy().hasHeightForWidth());
        m_labEarthing->setSizePolicy(sizePolicy);
        m_labEarthing->setMinimumSize(QSize(180, 0));
        m_labEarthing->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labEarthing, 13, 2, 1, 1);

        m_labK2 = new QLabel(QDiffCommonParasDlg);
        m_labK2->setObjectName(QString::fromUtf8("m_labK2"));
        sizePolicy.setHeightForWidth(m_labK2->sizePolicy().hasHeightForWidth());
        m_labK2->setSizePolicy(sizePolicy);
        m_labK2->setMinimumSize(QSize(180, 0));
        m_labK2->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labK2, 12, 2, 1, 1);

        m_labSearchMode = new QLabel(QDiffCommonParasDlg);
        m_labSearchMode->setObjectName(QString::fromUtf8("m_labSearchMode"));
        sizePolicy.setHeightForWidth(m_labSearchMode->sizePolicy().hasHeightForWidth());
        m_labSearchMode->setSizePolicy(sizePolicy);
        m_labSearchMode->setMinimumSize(QSize(180, 0));
        m_labSearchMode->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labSearchMode, 8, 2, 1, 1);

        m_labAdoptWind = new QLabel(QDiffCommonParasDlg);
        m_labAdoptWind->setObjectName(QString::fromUtf8("m_labAdoptWind"));
        sizePolicy.setHeightForWidth(m_labAdoptWind->sizePolicy().hasHeightForWidth());
        m_labAdoptWind->setSizePolicy(sizePolicy);
        m_labAdoptWind->setMinimumSize(QSize(180, 0));
        m_labAdoptWind->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labAdoptWind, 4, 2, 1, 1);

        m_labJXFactor = new QLabel(QDiffCommonParasDlg);
        m_labJXFactor->setObjectName(QString::fromUtf8("m_labJXFactor"));
        sizePolicy.setHeightForWidth(m_labJXFactor->sizePolicy().hasHeightForWidth());
        m_labJXFactor->setSizePolicy(sizePolicy);
        m_labJXFactor->setMinimumSize(QSize(180, 0));
        m_labJXFactor->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labJXFactor, 7, 2, 1, 1);

        m_labWindH = new QLabel(QDiffCommonParasDlg);
        m_labWindH->setObjectName(QString::fromUtf8("m_labWindH"));
        sizePolicy.setHeightForWidth(m_labWindH->sizePolicy().hasHeightForWidth());
        m_labWindH->setSizePolicy(sizePolicy);
        m_labWindH->setMinimumSize(QSize(180, 0));
        m_labWindH->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labWindH, 0, 2, 1, 1);

        m_labVg1 = new QLabel(QDiffCommonParasDlg);
        m_labVg1->setObjectName(QString::fromUtf8("m_labVg1"));
        sizePolicy.setHeightForWidth(m_labVg1->sizePolicy().hasHeightForWidth());
        m_labVg1->setSizePolicy(sizePolicy);
        m_labVg1->setMinimumSize(QSize(180, 0));
        m_labVg1->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labVg1, 15, 2, 1, 1);

        m_labVg2 = new QLabel(QDiffCommonParasDlg);
        m_labVg2->setObjectName(QString::fromUtf8("m_labVg2"));
        sizePolicy.setHeightForWidth(m_labVg2->sizePolicy().hasHeightForWidth());
        m_labVg2->setSizePolicy(sizePolicy);
        m_labVg2->setMinimumSize(QSize(180, 0));
        m_labVg2->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labVg2, 16, 2, 1, 1);

        m_labStep = new QLabel(QDiffCommonParasDlg);
        m_labStep->setObjectName(QString::fromUtf8("m_labStep"));
        sizePolicy.setHeightForWidth(m_labStep->sizePolicy().hasHeightForWidth());
        m_labStep->setSizePolicy(sizePolicy);
        m_labStep->setMinimumSize(QSize(180, 0));
        m_labStep->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labStep, 14, 2, 1, 1);

        m_labPhCorrectMode = new QLabel(QDiffCommonParasDlg);
        m_labPhCorrectMode->setObjectName(QString::fromUtf8("m_labPhCorrectMode"));
        sizePolicy.setHeightForWidth(m_labPhCorrectMode->sizePolicy().hasHeightForWidth());
        m_labPhCorrectMode->setSizePolicy(sizePolicy);
        m_labPhCorrectMode->setMinimumSize(QSize(180, 0));
        m_labPhCorrectMode->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labPhCorrectMode, 3, 2, 1, 1);

        m_labWindL = new QLabel(QDiffCommonParasDlg);
        m_labWindL->setObjectName(QString::fromUtf8("m_labWindL"));
        sizePolicy.setHeightForWidth(m_labWindL->sizePolicy().hasHeightForWidth());
        m_labWindL->setSizePolicy(sizePolicy);
        m_labWindL->setMinimumSize(QSize(180, 0));
        m_labWindL->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labWindL, 2, 2, 1, 1);

        m_labWindM = new QLabel(QDiffCommonParasDlg);
        m_labWindM->setObjectName(QString::fromUtf8("m_labWindM"));
        sizePolicy.setHeightForWidth(m_labWindM->sizePolicy().hasHeightForWidth());
        m_labWindM->setSizePolicy(sizePolicy);
        m_labWindM->setMinimumSize(QSize(180, 0));
        m_labWindM->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labWindM, 1, 2, 1, 1);

        m_labPrepareTime = new QLabel(QDiffCommonParasDlg);
        m_labPrepareTime->setObjectName(QString::fromUtf8("m_labPrepareTime"));
        sizePolicy.setHeightForWidth(m_labPrepareTime->sizePolicy().hasHeightForWidth());
        m_labPrepareTime->setSizePolicy(sizePolicy);
        m_labPrepareTime->setMinimumSize(QSize(180, 0));
        m_labPrepareTime->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labPrepareTime, 0, 0, 1, 1);

        m_labHUn = new QLabel(QDiffCommonParasDlg);
        m_labHUn->setObjectName(QString::fromUtf8("m_labHUn"));
        sizePolicy.setHeightForWidth(m_labHUn->sizePolicy().hasHeightForWidth());
        m_labHUn->setSizePolicy(sizePolicy);
        m_labHUn->setMinimumSize(QSize(180, 0));
        m_labHUn->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labHUn, 6, 0, 1, 1);

        m_txtLUn = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtLUn->setObjectName(QString::fromUtf8("m_txtLUn"));
        sizePolicy.setHeightForWidth(m_txtLUn->sizePolicy().hasHeightForWidth());
        m_txtLUn->setSizePolicy(sizePolicy);
        m_txtLUn->setMinimumSize(QSize(220, 25));
        m_txtLUn->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtLUn, 8, 1, 1, 1);

        m_labTimeAfter = new QLabel(QDiffCommonParasDlg);
        m_labTimeAfter->setObjectName(QString::fromUtf8("m_labTimeAfter"));
        sizePolicy.setHeightForWidth(m_labTimeAfter->sizePolicy().hasHeightForWidth());
        m_labTimeAfter->setSizePolicy(sizePolicy);
        m_labTimeAfter->setMinimumSize(QSize(180, 0));
        m_labTimeAfter->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labTimeAfter, 3, 0, 1, 1);

        m_txtPrepareTime = new QLineEdit(QDiffCommonParasDlg);
        m_txtPrepareTime->setObjectName(QString::fromUtf8("m_txtPrepareTime"));
        sizePolicy.setHeightForWidth(m_txtPrepareTime->sizePolicy().hasHeightForWidth());
        m_txtPrepareTime->setSizePolicy(sizePolicy);
        m_txtPrepareTime->setMinimumSize(QSize(220, 25));
        m_txtPrepareTime->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtPrepareTime, 0, 1, 1, 1);

        m_labLUn = new QLabel(QDiffCommonParasDlg);
        m_labLUn->setObjectName(QString::fromUtf8("m_labLUn"));
        sizePolicy.setHeightForWidth(m_labLUn->sizePolicy().hasHeightForWidth());
        m_labLUn->setSizePolicy(sizePolicy);
        m_labLUn->setMinimumSize(QSize(180, 0));
        m_labLUn->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labLUn, 8, 0, 1, 1);

        m_txtCTSl = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtCTSl->setObjectName(QString::fromUtf8("m_txtCTSl"));
        sizePolicy.setHeightForWidth(m_txtCTSl->sizePolicy().hasHeightForWidth());
        m_txtCTSl->setSizePolicy(sizePolicy);
        m_txtCTSl->setMinimumSize(QSize(220, 25));
        m_txtCTSl->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtCTSl, 14, 1, 1, 1);

        m_labKphSet = new QLabel(QDiffCommonParasDlg);
        m_labKphSet->setObjectName(QString::fromUtf8("m_labKphSet"));
        sizePolicy.setHeightForWidth(m_labKphSet->sizePolicy().hasHeightForWidth());
        m_labKphSet->setSizePolicy(sizePolicy);
        m_labKphSet->setMinimumSize(QSize(180, 0));
        m_labKphSet->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labKphSet, 15, 0, 1, 1);

        m_labKpmSet = new QLabel(QDiffCommonParasDlg);
        m_labKpmSet->setObjectName(QString::fromUtf8("m_labKpmSet"));
        sizePolicy.setHeightForWidth(m_labKpmSet->sizePolicy().hasHeightForWidth());
        m_labKpmSet->setSizePolicy(sizePolicy);
        m_labKpmSet->setMinimumSize(QSize(180, 0));
        m_labKpmSet->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labKpmSet, 16, 0, 1, 1);

        m_labFaultTime = new QLabel(QDiffCommonParasDlg);
        m_labFaultTime->setObjectName(QString::fromUtf8("m_labFaultTime"));
        sizePolicy.setHeightForWidth(m_labFaultTime->sizePolicy().hasHeightForWidth());
        m_labFaultTime->setSizePolicy(sizePolicy);
        m_labFaultTime->setMinimumSize(QSize(180, 0));
        m_labFaultTime->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labFaultTime, 2, 0, 1, 1);

        m_txtTimeAfter = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtTimeAfter->setObjectName(QString::fromUtf8("m_txtTimeAfter"));
        sizePolicy.setHeightForWidth(m_txtTimeAfter->sizePolicy().hasHeightForWidth());
        m_txtTimeAfter->setSizePolicy(sizePolicy);
        m_txtTimeAfter->setMinimumSize(QSize(220, 25));
        m_txtTimeAfter->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtTimeAfter, 3, 1, 1, 1);

        m_cmbKPSetMode = new QComboBox(QDiffCommonParasDlg);
        m_cmbKPSetMode->setObjectName(QString::fromUtf8("m_cmbKPSetMode"));
        sizePolicy.setHeightForWidth(m_cmbKPSetMode->sizePolicy().hasHeightForWidth());
        m_cmbKPSetMode->setSizePolicy(sizePolicy);
        m_cmbKPSetMode->setMinimumSize(QSize(220, 25));
        m_cmbKPSetMode->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbKPSetMode, 4, 1, 1, 1);

        m_labCTPh = new QLabel(QDiffCommonParasDlg);
        m_labCTPh->setObjectName(QString::fromUtf8("m_labCTPh"));
        sizePolicy.setHeightForWidth(m_labCTPh->sizePolicy().hasHeightForWidth());
        m_labCTPh->setSizePolicy(sizePolicy);
        m_labCTPh->setMinimumSize(QSize(180, 0));
        m_labCTPh->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labCTPh, 9, 0, 1, 1);

        m_txtFaultTime = new QLineEdit(QDiffCommonParasDlg);
        m_txtFaultTime->setObjectName(QString::fromUtf8("m_txtFaultTime"));
        sizePolicy.setHeightForWidth(m_txtFaultTime->sizePolicy().hasHeightForWidth());
        m_txtFaultTime->setSizePolicy(sizePolicy);
        m_txtFaultTime->setMinimumSize(QSize(220, 25));
        m_txtFaultTime->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtFaultTime, 2, 1, 1, 1);

        m_labCTSh = new QLabel(QDiffCommonParasDlg);
        m_labCTSh->setObjectName(QString::fromUtf8("m_labCTSh"));
        sizePolicy.setHeightForWidth(m_labCTSh->sizePolicy().hasHeightForWidth());
        m_labCTSh->setSizePolicy(sizePolicy);
        m_labCTSh->setMinimumSize(QSize(180, 0));
        m_labCTSh->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labCTSh, 12, 0, 1, 1);

        m_labMUn = new QLabel(QDiffCommonParasDlg);
        m_labMUn->setObjectName(QString::fromUtf8("m_labMUn"));
        sizePolicy.setHeightForWidth(m_labMUn->sizePolicy().hasHeightForWidth());
        m_labMUn->setSizePolicy(sizePolicy);
        m_labMUn->setMinimumSize(QSize(180, 0));
        m_labMUn->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labMUn, 7, 0, 1, 1);

        m_txtCTSh = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtCTSh->setObjectName(QString::fromUtf8("m_txtCTSh"));
        sizePolicy.setHeightForWidth(m_txtCTSh->sizePolicy().hasHeightForWidth());
        m_txtCTSh->setSizePolicy(sizePolicy);
        m_txtCTSh->setMinimumSize(QSize(220, 25));
        m_txtCTSh->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtCTSh, 12, 1, 1, 1);

        m_txtCTSm = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtCTSm->setObjectName(QString::fromUtf8("m_txtCTSm"));
        sizePolicy.setHeightForWidth(m_txtCTSm->sizePolicy().hasHeightForWidth());
        m_txtCTSm->setSizePolicy(sizePolicy);
        m_txtCTSm->setMinimumSize(QSize(220, 25));
        m_txtCTSm->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtCTSm, 13, 1, 1, 1);

        m_labCTSl = new QLabel(QDiffCommonParasDlg);
        m_labCTSl->setObjectName(QString::fromUtf8("m_labCTSl"));
        sizePolicy.setHeightForWidth(m_labCTSl->sizePolicy().hasHeightForWidth());
        m_labCTSl->setSizePolicy(sizePolicy);
        m_labCTSl->setMinimumSize(QSize(180, 0));
        m_labCTSl->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labCTSl, 14, 0, 1, 1);

        m_txtKphSet = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtKphSet->setObjectName(QString::fromUtf8("m_txtKphSet"));
        sizePolicy.setHeightForWidth(m_txtKphSet->sizePolicy().hasHeightForWidth());
        m_txtKphSet->setSizePolicy(sizePolicy);
        m_txtKphSet->setMinimumSize(QSize(220, 25));
        m_txtKphSet->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtKphSet, 15, 1, 1, 1);

        m_txtCTPm = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtCTPm->setObjectName(QString::fromUtf8("m_txtCTPm"));
        sizePolicy.setHeightForWidth(m_txtCTPm->sizePolicy().hasHeightForWidth());
        m_txtCTPm->setSizePolicy(sizePolicy);
        m_txtCTPm->setMinimumSize(QSize(220, 25));
        m_txtCTPm->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtCTPm, 10, 1, 1, 1);

        m_txtCTPl = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtCTPl->setObjectName(QString::fromUtf8("m_txtCTPl"));
        sizePolicy.setHeightForWidth(m_txtCTPl->sizePolicy().hasHeightForWidth());
        m_txtCTPl->setSizePolicy(sizePolicy);
        m_txtCTPl->setMinimumSize(QSize(220, 25));
        m_txtCTPl->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtCTPl, 11, 1, 1, 1);

        m_txtSn = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtSn->setObjectName(QString::fromUtf8("m_txtSn"));
        sizePolicy.setHeightForWidth(m_txtSn->sizePolicy().hasHeightForWidth());
        m_txtSn->setSizePolicy(sizePolicy);
        m_txtSn->setMinimumSize(QSize(220, 25));
        m_txtSn->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtSn, 5, 1, 1, 1);

        m_labPreFaultTime = new QLabel(QDiffCommonParasDlg);
        m_labPreFaultTime->setObjectName(QString::fromUtf8("m_labPreFaultTime"));
        sizePolicy.setHeightForWidth(m_labPreFaultTime->sizePolicy().hasHeightForWidth());
        m_labPreFaultTime->setSizePolicy(sizePolicy);
        m_labPreFaultTime->setMinimumSize(QSize(180, 0));
        m_labPreFaultTime->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labPreFaultTime, 1, 0, 1, 1);

        m_txtPreFaultTime = new QLineEdit(QDiffCommonParasDlg);
        m_txtPreFaultTime->setObjectName(QString::fromUtf8("m_txtPreFaultTime"));
        sizePolicy.setHeightForWidth(m_txtPreFaultTime->sizePolicy().hasHeightForWidth());
        m_txtPreFaultTime->setSizePolicy(sizePolicy);
        m_txtPreFaultTime->setMinimumSize(QSize(220, 25));
        m_txtPreFaultTime->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtPreFaultTime, 1, 1, 1, 1);

        m_txtMUn = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtMUn->setObjectName(QString::fromUtf8("m_txtMUn"));
        sizePolicy.setHeightForWidth(m_txtMUn->sizePolicy().hasHeightForWidth());
        m_txtMUn->setSizePolicy(sizePolicy);
        m_txtMUn->setMinimumSize(QSize(220, 25));
        m_txtMUn->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtMUn, 7, 1, 1, 1);

        m_labSn = new QLabel(QDiffCommonParasDlg);
        m_labSn->setObjectName(QString::fromUtf8("m_labSn"));
        sizePolicy.setHeightForWidth(m_labSn->sizePolicy().hasHeightForWidth());
        m_labSn->setSizePolicy(sizePolicy);
        m_labSn->setMinimumSize(QSize(180, 0));
        m_labSn->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labSn, 5, 0, 1, 1);

        m_txtCTPh = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtCTPh->setObjectName(QString::fromUtf8("m_txtCTPh"));
        sizePolicy.setHeightForWidth(m_txtCTPh->sizePolicy().hasHeightForWidth());
        m_txtCTPh->setSizePolicy(sizePolicy);
        m_txtCTPh->setMinimumSize(QSize(220, 25));
        m_txtCTPh->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtCTPh, 9, 1, 1, 1);

        m_labCTPm = new QLabel(QDiffCommonParasDlg);
        m_labCTPm->setObjectName(QString::fromUtf8("m_labCTPm"));
        sizePolicy.setHeightForWidth(m_labCTPm->sizePolicy().hasHeightForWidth());
        m_labCTPm->setSizePolicy(sizePolicy);
        m_labCTPm->setMinimumSize(QSize(180, 0));
        m_labCTPm->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labCTPm, 10, 0, 1, 1);

        m_labKPSetMode = new QLabel(QDiffCommonParasDlg);
        m_labKPSetMode->setObjectName(QString::fromUtf8("m_labKPSetMode"));
        sizePolicy.setHeightForWidth(m_labKPSetMode->sizePolicy().hasHeightForWidth());
        m_labKPSetMode->setSizePolicy(sizePolicy);
        m_labKPSetMode->setMinimumSize(QSize(180, 0));
        m_labKPSetMode->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labKPSetMode, 4, 0, 1, 1);

        m_txtHUn = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtHUn->setObjectName(QString::fromUtf8("m_txtHUn"));
        sizePolicy.setHeightForWidth(m_txtHUn->sizePolicy().hasHeightForWidth());
        m_txtHUn->setSizePolicy(sizePolicy);
        m_txtHUn->setMinimumSize(QSize(220, 25));
        m_txtHUn->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtHUn, 6, 1, 1, 1);

        m_labCTPl = new QLabel(QDiffCommonParasDlg);
        m_labCTPl->setObjectName(QString::fromUtf8("m_labCTPl"));
        sizePolicy.setHeightForWidth(m_labCTPl->sizePolicy().hasHeightForWidth());
        m_labCTPl->setSizePolicy(sizePolicy);
        m_labCTPl->setMinimumSize(QSize(180, 0));
        m_labCTPl->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labCTPl, 11, 0, 1, 1);

        m_labCTSm = new QLabel(QDiffCommonParasDlg);
        m_labCTSm->setObjectName(QString::fromUtf8("m_labCTSm"));
        sizePolicy.setHeightForWidth(m_labCTSm->sizePolicy().hasHeightForWidth());
        m_labCTSm->setSizePolicy(sizePolicy);
        m_labCTSm->setMinimumSize(QSize(180, 0));
        m_labCTSm->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labCTSm, 13, 0, 1, 1);

        m_txtKplSet = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtKplSet->setObjectName(QString::fromUtf8("m_txtKplSet"));
        sizePolicy.setHeightForWidth(m_txtKplSet->sizePolicy().hasHeightForWidth());
        m_txtKplSet->setSizePolicy(sizePolicy);
        m_txtKplSet->setMinimumSize(QSize(220, 25));
        m_txtKplSet->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtKplSet, 17, 1, 1, 1);

        m_labKplSet = new QLabel(QDiffCommonParasDlg);
        m_labKplSet->setObjectName(QString::fromUtf8("m_labKplSet"));
        sizePolicy.setHeightForWidth(m_labKplSet->sizePolicy().hasHeightForWidth());
        m_labKplSet->setSizePolicy(sizePolicy);
        m_labKplSet->setMinimumSize(QSize(180, 0));
        m_labKplSet->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(m_labKplSet, 17, 0, 1, 1);

        m_txtKpmSet = new QSettingLineEdit(QDiffCommonParasDlg);
        m_txtKpmSet->setObjectName(QString::fromUtf8("m_txtKpmSet"));
        sizePolicy.setHeightForWidth(m_txtKpmSet->sizePolicy().hasHeightForWidth());
        m_txtKpmSet->setSizePolicy(sizePolicy);
        m_txtKpmSet->setMinimumSize(QSize(220, 25));
        m_txtKpmSet->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtKpmSet, 16, 1, 1, 1);

        m_cmbWindH = new QComboBox(QDiffCommonParasDlg);
        m_cmbWindH->setObjectName(QString::fromUtf8("m_cmbWindH"));
        sizePolicy.setHeightForWidth(m_cmbWindH->sizePolicy().hasHeightForWidth());
        m_cmbWindH->setSizePolicy(sizePolicy);
        m_cmbWindH->setMinimumSize(QSize(220, 25));
        m_cmbWindH->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbWindH, 0, 3, 1, 1);

        m_cmbWindM = new QComboBox(QDiffCommonParasDlg);
        m_cmbWindM->setObjectName(QString::fromUtf8("m_cmbWindM"));
        sizePolicy.setHeightForWidth(m_cmbWindM->sizePolicy().hasHeightForWidth());
        m_cmbWindM->setSizePolicy(sizePolicy);
        m_cmbWindM->setMinimumSize(QSize(220, 25));
        m_cmbWindM->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbWindM, 1, 3, 1, 1);

        m_cmbWindL = new QComboBox(QDiffCommonParasDlg);
        m_cmbWindL->setObjectName(QString::fromUtf8("m_cmbWindL"));
        sizePolicy.setHeightForWidth(m_cmbWindL->sizePolicy().hasHeightForWidth());
        m_cmbWindL->setSizePolicy(sizePolicy);
        m_cmbWindL->setMinimumSize(QSize(220, 25));
        m_cmbWindL->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbWindL, 2, 3, 1, 1);

        m_cmbPhCorrectMode = new QDataTypeComboBox(QDiffCommonParasDlg);
        m_cmbPhCorrectMode->setObjectName(QString::fromUtf8("m_cmbPhCorrectMode"));
        sizePolicy.setHeightForWidth(m_cmbPhCorrectMode->sizePolicy().hasHeightForWidth());
        m_cmbPhCorrectMode->setSizePolicy(sizePolicy);
        m_cmbPhCorrectMode->setMinimumSize(QSize(220, 25));
        m_cmbPhCorrectMode->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbPhCorrectMode, 3, 3, 1, 1);

        m_cmbAdoptWind = new QComboBox(QDiffCommonParasDlg);
        m_cmbAdoptWind->setObjectName(QString::fromUtf8("m_cmbAdoptWind"));
        sizePolicy.setHeightForWidth(m_cmbAdoptWind->sizePolicy().hasHeightForWidth());
        m_cmbAdoptWind->setSizePolicy(sizePolicy);
        m_cmbAdoptWind->setMinimumSize(QSize(220, 25));
        m_cmbAdoptWind->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbAdoptWind, 4, 3, 1, 1);

        m_cmbTransGroupMode1 = new QComboBox(QDiffCommonParasDlg);
        m_cmbTransGroupMode1->setObjectName(QString::fromUtf8("m_cmbTransGroupMode1"));
        sizePolicy.setHeightForWidth(m_cmbTransGroupMode1->sizePolicy().hasHeightForWidth());
        m_cmbTransGroupMode1->setSizePolicy(sizePolicy);
        m_cmbTransGroupMode1->setMinimumSize(QSize(220, 25));
        m_cmbTransGroupMode1->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbTransGroupMode1, 5, 3, 1, 1);

        m_cmbTransGroupMode2 = new QComboBox(QDiffCommonParasDlg);
        m_cmbTransGroupMode2->setObjectName(QString::fromUtf8("m_cmbTransGroupMode2"));
        sizePolicy.setHeightForWidth(m_cmbTransGroupMode2->sizePolicy().hasHeightForWidth());
        m_cmbTransGroupMode2->setSizePolicy(sizePolicy);
        m_cmbTransGroupMode2->setMinimumSize(QSize(220, 25));
        m_cmbTransGroupMode2->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbTransGroupMode2, 6, 3, 1, 1);

        m_cmbJXFactor = new QComboBox(QDiffCommonParasDlg);
        m_cmbJXFactor->setObjectName(QString::fromUtf8("m_cmbJXFactor"));
        sizePolicy.setHeightForWidth(m_cmbJXFactor->sizePolicy().hasHeightForWidth());
        m_cmbJXFactor->setSizePolicy(sizePolicy);
        m_cmbJXFactor->setMinimumSize(QSize(220, 25));
        m_cmbJXFactor->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbJXFactor, 7, 3, 1, 1);

        m_cmbSearchMode = new QComboBox(QDiffCommonParasDlg);
        m_cmbSearchMode->setObjectName(QString::fromUtf8("m_cmbSearchMode"));
        sizePolicy.setHeightForWidth(m_cmbSearchMode->sizePolicy().hasHeightForWidth());
        m_cmbSearchMode->setSizePolicy(sizePolicy);
        m_cmbSearchMode->setMinimumSize(QSize(220, 25));
        m_cmbSearchMode->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbSearchMode, 8, 3, 1, 1);

        m_cmbCTPoint = new QComboBox(QDiffCommonParasDlg);
        m_cmbCTPoint->setObjectName(QString::fromUtf8("m_cmbCTPoint"));
        sizePolicy.setHeightForWidth(m_cmbCTPoint->sizePolicy().hasHeightForWidth());
        m_cmbCTPoint->setSizePolicy(sizePolicy);
        m_cmbCTPoint->setMinimumSize(QSize(220, 25));
        m_cmbCTPoint->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbCTPoint, 9, 3, 1, 1);

        m_cmbIrEquation = new QComboBox(QDiffCommonParasDlg);
        m_cmbIrEquation->setObjectName(QString::fromUtf8("m_cmbIrEquation"));
        sizePolicy.setHeightForWidth(m_cmbIrEquation->sizePolicy().hasHeightForWidth());
        m_cmbIrEquation->setSizePolicy(sizePolicy);
        m_cmbIrEquation->setMinimumSize(QSize(220, 25));
        m_cmbIrEquation->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbIrEquation, 10, 3, 1, 1);

        m_txtK = new QLineEdit(QDiffCommonParasDlg);
        m_txtK->setObjectName(QString::fromUtf8("m_txtK"));
        sizePolicy.setHeightForWidth(m_txtK->sizePolicy().hasHeightForWidth());
        m_txtK->setSizePolicy(sizePolicy);
        m_txtK->setMinimumSize(QSize(220, 25));
        m_txtK->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtK, 11, 3, 1, 1);

        m_txtK2 = new QLineEdit(QDiffCommonParasDlg);
        m_txtK2->setObjectName(QString::fromUtf8("m_txtK2"));
        sizePolicy.setHeightForWidth(m_txtK2->sizePolicy().hasHeightForWidth());
        m_txtK2->setSizePolicy(sizePolicy);
        m_txtK2->setMinimumSize(QSize(220, 25));
        m_txtK2->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtK2, 12, 3, 1, 1);

        m_cmbEarthing = new QComboBox(QDiffCommonParasDlg);
        m_cmbEarthing->setObjectName(QString::fromUtf8("m_cmbEarthing"));
        sizePolicy.setHeightForWidth(m_cmbEarthing->sizePolicy().hasHeightForWidth());
        m_cmbEarthing->setSizePolicy(sizePolicy);
        m_cmbEarthing->setMinimumSize(QSize(220, 25));
        m_cmbEarthing->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_cmbEarthing, 13, 3, 1, 1);

        m_txtStep = new QLineEdit(QDiffCommonParasDlg);
        m_txtStep->setObjectName(QString::fromUtf8("m_txtStep"));
        sizePolicy.setHeightForWidth(m_txtStep->sizePolicy().hasHeightForWidth());
        m_txtStep->setSizePolicy(sizePolicy);
        m_txtStep->setMinimumSize(QSize(220, 25));
        m_txtStep->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtStep, 14, 3, 1, 1);

        m_txtVg1 = new QLineEdit(QDiffCommonParasDlg);
        m_txtVg1->setObjectName(QString::fromUtf8("m_txtVg1"));
        sizePolicy.setHeightForWidth(m_txtVg1->sizePolicy().hasHeightForWidth());
        m_txtVg1->setSizePolicy(sizePolicy);
        m_txtVg1->setMinimumSize(QSize(220, 25));
        m_txtVg1->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtVg1, 15, 3, 1, 1);

        m_txtVg2 = new QLineEdit(QDiffCommonParasDlg);
        m_txtVg2->setObjectName(QString::fromUtf8("m_txtVg2"));
        sizePolicy.setHeightForWidth(m_txtVg2->sizePolicy().hasHeightForWidth());
        m_txtVg2->setSizePolicy(sizePolicy);
        m_txtVg2->setMinimumSize(QSize(220, 25));
        m_txtVg2->setMaximumSize(QSize(220, 16777215));

        gridLayout->addWidget(m_txtVg2, 16, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_btnOK = new QPushButton(QDiffCommonParasDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));
        m_btnOK->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(m_btnOK);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        m_btnCancel = new QPushButton(QDiffCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        m_btnCancel->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(m_btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(QDiffCommonParasDlg);

        QMetaObject::connectSlotsByName(QDiffCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QDiffCommonParasDlg)
    {
        QDiffCommonParasDlg->setWindowTitle(QApplication::translate("QDiffCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labIrEquation->setText(QApplication::translate("QDiffCommonParasDlg", "\345\210\266\345\212\250\346\226\271\347\250\213:", 0, QApplication::UnicodeUTF8));
        m_labK->setText(QApplication::translate("QDiffCommonParasDlg", "K1:", 0, QApplication::UnicodeUTF8));
        m_labTransGroupMode2->setText(QApplication::translate("QDiffCommonParasDlg", "\351\253\230-\344\275\216\347\273\225\347\273\204\351\222\237\347\202\271\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labTransGroupMode1->setText(QApplication::translate("QDiffCommonParasDlg", "\351\253\230-\344\270\255\347\273\225\347\273\204\351\222\237\347\202\271\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labCTPoint->setText(QApplication::translate("QDiffCommonParasDlg", "CT\346\236\201\346\200\247:", 0, QApplication::UnicodeUTF8));
        m_labEarthing->setText(QApplication::translate("QDiffCommonParasDlg", "\346\216\245\345\234\260:", 0, QApplication::UnicodeUTF8));
        m_labK2->setText(QApplication::translate("QDiffCommonParasDlg", "K2:", 0, QApplication::UnicodeUTF8));
        m_labSearchMode->setText(QApplication::translate("QDiffCommonParasDlg", "\346\220\234\347\264\242\346\226\271\346\263\225:", 0, QApplication::UnicodeUTF8));
        m_labAdoptWind->setText(QApplication::translate("QDiffCommonParasDlg", "\346\265\213\350\257\225\347\273\225\347\273\204:", 0, QApplication::UnicodeUTF8));
        m_labJXFactor->setText(QApplication::translate("QDiffCommonParasDlg", "\345\271\263\350\241\241\347\263\273\346\225\260\350\256\241\347\256\227:", 0, QApplication::UnicodeUTF8));
        m_labWindH->setText(QApplication::translate("QDiffCommonParasDlg", "\351\253\230\345\216\213\344\276\247\347\273\225\347\273\204\346\216\245\347\272\277\345\236\213\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labVg1->setText(QApplication::translate("QDiffCommonParasDlg", "Ua\343\200\201Ub\343\200\201Uc(V):", 0, QApplication::UnicodeUTF8));
        m_labVg2->setText(QApplication::translate("QDiffCommonParasDlg", "Ua2\343\200\201Ub2\343\200\201Uc2(V):", 0, QApplication::UnicodeUTF8));
        m_labStep->setText(QApplication::translate("QDiffCommonParasDlg", "\346\265\213\350\257\225\347\262\276\345\272\246:", 0, QApplication::UnicodeUTF8));
        m_labPhCorrectMode->setText(QApplication::translate("QDiffCommonParasDlg", "\346\240\241\346\255\243\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_labWindL->setText(QApplication::translate("QDiffCommonParasDlg", "\344\275\216\345\216\213\344\276\247\347\273\225\347\273\204\346\216\245\347\272\277\345\236\213\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labWindM->setText(QApplication::translate("QDiffCommonParasDlg", "\344\270\255\345\216\213\344\276\247\347\273\225\347\273\204\346\216\245\347\272\277\345\236\213\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labPrepareTime->setText(QApplication::translate("QDiffCommonParasDlg", "\345\207\206\345\244\207\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labHUn->setText(QApplication::translate("QDiffCommonParasDlg", "\351\253\230\345\216\213\344\276\247\351\242\235\345\256\232\347\224\265\345\216\213(kV):", 0, QApplication::UnicodeUTF8));
        m_labTimeAfter->setText(QApplication::translate("QDiffCommonParasDlg", "\345\212\250\344\275\234\345\220\216\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labLUn->setText(QApplication::translate("QDiffCommonParasDlg", "\344\275\216\345\216\213\344\276\247\351\242\235\345\256\232\347\224\265\345\216\213(kV):", 0, QApplication::UnicodeUTF8));
        m_labKphSet->setText(QApplication::translate("QDiffCommonParasDlg", "\351\253\230\345\216\213\344\276\247\345\267\256\345\212\250\345\271\263\350\241\241\347\263\273\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labKpmSet->setText(QApplication::translate("QDiffCommonParasDlg", "\344\270\255\345\216\213\344\276\247\345\267\256\345\212\250\345\271\263\350\241\241\347\263\273\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labFaultTime->setText(QApplication::translate("QDiffCommonParasDlg", "\346\225\264\345\256\232\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labCTPh->setText(QApplication::translate("QDiffCommonParasDlg", "\351\253\230\345\216\213\344\276\247CT\344\270\200\346\254\241\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labCTSh->setText(QApplication::translate("QDiffCommonParasDlg", "\351\253\230\345\216\213\344\276\247CT\344\272\214\346\254\241\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labMUn->setText(QApplication::translate("QDiffCommonParasDlg", "\344\270\255\345\216\213\344\276\247\351\242\235\345\256\232\347\224\265\345\216\213(kV):", 0, QApplication::UnicodeUTF8));
        m_labCTSl->setText(QApplication::translate("QDiffCommonParasDlg", "\344\275\216\345\216\213\344\276\247CT\344\272\214\346\254\241\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labPreFaultTime->setText(QApplication::translate("QDiffCommonParasDlg", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labSn->setText(QApplication::translate("QDiffCommonParasDlg", "\345\217\230\345\216\213\345\231\250\351\242\235\345\256\232\345\256\271\351\207\217(MVA):", 0, QApplication::UnicodeUTF8));
        m_labCTPm->setText(QApplication::translate("QDiffCommonParasDlg", "\344\270\255\345\216\213\344\276\247CT\344\270\200\346\254\241\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labKPSetMode->setText(QApplication::translate("QDiffCommonParasDlg", "\345\220\204\344\276\247\345\271\263\350\241\241\347\263\273\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labCTPl->setText(QApplication::translate("QDiffCommonParasDlg", "\344\275\216\345\216\213\344\276\247CT\344\270\200\346\254\241\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labCTSm->setText(QApplication::translate("QDiffCommonParasDlg", "\344\270\255\345\216\213\344\276\247CT\344\272\214\346\254\241\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labKplSet->setText(QApplication::translate("QDiffCommonParasDlg", "\344\275\216\345\216\213\344\276\247\345\267\256\345\212\250\345\271\263\350\241\241\347\263\273\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QDiffCommonParasDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDiffCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDiffCommonParasDlg: public Ui_QDiffCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFCOMMONPARASDLG_H
