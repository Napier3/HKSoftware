/********************************************************************************
** Form generated from reading UI file 'SttMacroParaEditViewSequenceGradient.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTMACROPARAEDITVIEWSEQUENCEGRADIENT_H
#define UI_STTMACROPARAEDITVIEWSEQUENCEGRADIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../Controls/SettingCtrls/QSettingLineEdit.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttGroupBox.h"
#include "../Controls/SttLineEdit.h"
#include "../Controls/SttTabWidget.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QSttMacroParaEditViewSequenceGradient
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *m_MainLayout;
    QSttTabWidget *m_tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSttGroupBox *m_gpChangeSet;
    QGridLayout *gridLayout_6;
    QLabel *m_labInit;
    QLabel *m_labStep;
    QSettingLineEdit *m_editStep;
    QLabel *m_labTime;
    QSettingLineEdit *m_editTime;
    QSettingLineEdit *m_editInit;
    QLabel *m_labFinish;
    QSettingLineEdit *m_editFinish;
    QSttGroupBox *m_gpVarSet;
    QGridLayout *gridLayout_3;
    QScrollComboBox *m_cbbVarType;
    QLabel *m_labDirection;
    QLabel *m_labType;
    QScrollComboBox *m_cbbDirection;
    QLabel *m_labVarType;
    QScrollComboBox *m_cbbType;
    QScrollComboBox *m_cbbVar;
    QLabel *m_labVar;
    QSttGroupBox *m_gpMannual;
    QGridLayout *gridLayout;
    QLabel *m_labTimeBeforeFail;
    QHBoxLayout *horizontalLayout_3;
    QSttLineEdit *m_editTimeBeforeFail;
    QSttCheckBox *m_cbBefore;
    QSttLineEdit *m_editTimeBeforeChange;
    QLabel *m_labTimeBeforeChange;
    QSpacerItem *verticalSpacer_2;
    QSttGroupBox *m_gpBin;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout_4;
    QSttCheckBox *m_cbBinD;
    QSttCheckBox *m_cbBinI;
    QSttCheckBox *m_cbBinJ;
    QRadioButton *m_rbOr;
    QSttCheckBox *m_cbBinB;
    QSttCheckBox *m_cbBinF;
    QSttCheckBox *m_cbBinA;
    QSttCheckBox *m_cbBinC;
    QSttCheckBox *m_cbBinG;
    QSttCheckBox *m_cbBinH;
    QSttCheckBox *m_cbBinE;
    QRadioButton *m_rbAnd;
    QHBoxLayout *horizontalLayout_5;
    QSttGroupBox *m_gpBoutNormal;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_5;
    QSttCheckBox *m_cbBOut1;
    QSttCheckBox *m_cbBOut4;
    QSttCheckBox *m_cbBOut3;
    QSttCheckBox *m_cbBOut2;
    QSttGroupBox *m_gpBoutError;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout_7;
    QSttCheckBox *m_cbBOut2_E;
    QSttCheckBox *m_cbBOut4_E;
    QSttCheckBox *m_cbBOut1_E;
    QSttCheckBox *m_cbBOut3_E;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnSettingValue;
    QPushButton *m_btnEstimate;
    QPushButton *m_btnMoreOut;

    void setupUi(QWidget *QSttMacroParaEditViewSequenceGradient)
    {
        if (QSttMacroParaEditViewSequenceGradient->objectName().isEmpty())
            QSttMacroParaEditViewSequenceGradient->setObjectName(QString::fromUtf8("QSttMacroParaEditViewSequenceGradient"));
        QSttMacroParaEditViewSequenceGradient->resize(1068, 626);
        QFont font;
        font.setPointSize(18);
        QSttMacroParaEditViewSequenceGradient->setFont(font);
        gridLayout_2 = new QGridLayout(QSttMacroParaEditViewSequenceGradient);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_MainLayout = new QVBoxLayout();
        m_MainLayout->setSpacing(6);
        m_MainLayout->setObjectName(QString::fromUtf8("m_MainLayout"));
        m_tabWidget = new QSttTabWidget(QSttMacroParaEditViewSequenceGradient);
        m_tabWidget->setObjectName(QString::fromUtf8("m_tabWidget"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(11);
        m_tabWidget->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_gpChangeSet = new QSttGroupBox(tab);
        m_gpChangeSet->setObjectName(QString::fromUtf8("m_gpChangeSet"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_gpChangeSet->sizePolicy().hasHeightForWidth());
        m_gpChangeSet->setSizePolicy(sizePolicy);
        m_gpChangeSet->setMinimumSize(QSize(0, 220));
        m_gpChangeSet->setMaximumSize(QSize(290, 250));
        m_gpChangeSet->setFont(font1);
        gridLayout_6 = new QGridLayout(m_gpChangeSet);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        m_labInit = new QLabel(m_gpChangeSet);
        m_labInit->setObjectName(QString::fromUtf8("m_labInit"));

        gridLayout_6->addWidget(m_labInit, 0, 0, 1, 1);

        m_labStep = new QLabel(m_gpChangeSet);
        m_labStep->setObjectName(QString::fromUtf8("m_labStep"));

        gridLayout_6->addWidget(m_labStep, 2, 0, 1, 1);

        m_editStep = new QSettingLineEdit(m_gpChangeSet);
        m_editStep->setObjectName(QString::fromUtf8("m_editStep"));
        m_editStep->setMinimumSize(QSize(120, 0));

        gridLayout_6->addWidget(m_editStep, 2, 1, 1, 1);

        m_labTime = new QLabel(m_gpChangeSet);
        m_labTime->setObjectName(QString::fromUtf8("m_labTime"));

        gridLayout_6->addWidget(m_labTime, 3, 0, 1, 1);

        m_editTime = new QSettingLineEdit(m_gpChangeSet);
        m_editTime->setObjectName(QString::fromUtf8("m_editTime"));
        m_editTime->setMinimumSize(QSize(120, 0));

        gridLayout_6->addWidget(m_editTime, 3, 1, 1, 1);

        m_editInit = new QSettingLineEdit(m_gpChangeSet);
        m_editInit->setObjectName(QString::fromUtf8("m_editInit"));
        m_editInit->setMinimumSize(QSize(120, 0));

        gridLayout_6->addWidget(m_editInit, 0, 1, 1, 1);

        m_labFinish = new QLabel(m_gpChangeSet);
        m_labFinish->setObjectName(QString::fromUtf8("m_labFinish"));

        gridLayout_6->addWidget(m_labFinish, 1, 0, 1, 1);

        m_editFinish = new QSettingLineEdit(m_gpChangeSet);
        m_editFinish->setObjectName(QString::fromUtf8("m_editFinish"));
        m_editFinish->setMinimumSize(QSize(120, 0));

        gridLayout_6->addWidget(m_editFinish, 1, 1, 1, 1);

        m_labInit->raise();
        m_editInit->raise();
        m_editFinish->raise();
        m_labFinish->raise();
        m_labStep->raise();
        m_editStep->raise();
        m_labTime->raise();
        m_editTime->raise();

        horizontalLayout->addWidget(m_gpChangeSet);

        m_gpVarSet = new QSttGroupBox(tab);
        m_gpVarSet->setObjectName(QString::fromUtf8("m_gpVarSet"));
        sizePolicy.setHeightForWidth(m_gpVarSet->sizePolicy().hasHeightForWidth());
        m_gpVarSet->setSizePolicy(sizePolicy);
        m_gpVarSet->setMinimumSize(QSize(0, 220));
        m_gpVarSet->setMaximumSize(QSize(340, 250));
        m_gpVarSet->setFont(font1);
        gridLayout_3 = new QGridLayout(m_gpVarSet);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_cbbVarType = new QScrollComboBox(m_gpVarSet);
        m_cbbVarType->setObjectName(QString::fromUtf8("m_cbbVarType"));
        m_cbbVarType->setMinimumSize(QSize(150, 0));
        m_cbbVarType->setMaximumSize(QSize(16777215, 16777215));
        QFont font2;
        font2.setPointSize(20);
        m_cbbVarType->setFont(font2);

        gridLayout_3->addWidget(m_cbbVarType, 3, 2, 1, 1);

        m_labDirection = new QLabel(m_gpVarSet);
        m_labDirection->setObjectName(QString::fromUtf8("m_labDirection"));

        gridLayout_3->addWidget(m_labDirection, 5, 0, 1, 2);

        m_labType = new QLabel(m_gpVarSet);
        m_labType->setObjectName(QString::fromUtf8("m_labType"));

        gridLayout_3->addWidget(m_labType, 4, 0, 1, 1);

        m_cbbDirection = new QScrollComboBox(m_gpVarSet);
        m_cbbDirection->setObjectName(QString::fromUtf8("m_cbbDirection"));
        m_cbbDirection->setMinimumSize(QSize(150, 0));
        m_cbbDirection->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(m_cbbDirection, 5, 2, 1, 1);

        m_labVarType = new QLabel(m_gpVarSet);
        m_labVarType->setObjectName(QString::fromUtf8("m_labVarType"));

        gridLayout_3->addWidget(m_labVarType, 3, 0, 1, 2);

        m_cbbType = new QScrollComboBox(m_gpVarSet);
        m_cbbType->setObjectName(QString::fromUtf8("m_cbbType"));
        m_cbbType->setMinimumSize(QSize(150, 0));
        m_cbbType->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(m_cbbType, 4, 2, 1, 1);

        m_cbbVar = new QScrollComboBox(m_gpVarSet);
        m_cbbVar->setObjectName(QString::fromUtf8("m_cbbVar"));
        m_cbbVar->setMinimumSize(QSize(150, 0));
        m_cbbVar->setMaximumSize(QSize(16777215, 16777215));
        m_cbbVar->setMaxVisibleItems(5);

        gridLayout_3->addWidget(m_cbbVar, 1, 2, 1, 1);

        m_labVar = new QLabel(m_gpVarSet);
        m_labVar->setObjectName(QString::fromUtf8("m_labVar"));

        gridLayout_3->addWidget(m_labVar, 1, 0, 1, 1);


        horizontalLayout->addWidget(m_gpVarSet);

        m_gpMannual = new QSttGroupBox(tab);
        m_gpMannual->setObjectName(QString::fromUtf8("m_gpMannual"));
        m_gpMannual->setMinimumSize(QSize(0, 220));
        m_gpMannual->setMaximumSize(QSize(350, 250));
        m_gpMannual->setFont(font1);
        gridLayout = new QGridLayout(m_gpMannual);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labTimeBeforeFail = new QLabel(m_gpMannual);
        m_labTimeBeforeFail->setObjectName(QString::fromUtf8("m_labTimeBeforeFail"));

        gridLayout->addWidget(m_labTimeBeforeFail, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_editTimeBeforeFail = new QSttLineEdit(m_gpMannual);
        m_editTimeBeforeFail->setObjectName(QString::fromUtf8("m_editTimeBeforeFail"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_editTimeBeforeFail->sizePolicy().hasHeightForWidth());
        m_editTimeBeforeFail->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(m_editTimeBeforeFail);

        m_cbBefore = new QSttCheckBox(m_gpMannual);
        m_cbBefore->setObjectName(QString::fromUtf8("m_cbBefore"));

        horizontalLayout_3->addWidget(m_cbBefore);


        gridLayout->addLayout(horizontalLayout_3, 2, 2, 1, 1);

        m_editTimeBeforeChange = new QSttLineEdit(m_gpMannual);
        m_editTimeBeforeChange->setObjectName(QString::fromUtf8("m_editTimeBeforeChange"));
        sizePolicy1.setHeightForWidth(m_editTimeBeforeChange->sizePolicy().hasHeightForWidth());
        m_editTimeBeforeChange->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_editTimeBeforeChange, 1, 2, 1, 1);

        m_labTimeBeforeChange = new QLabel(m_gpMannual);
        m_labTimeBeforeChange->setObjectName(QString::fromUtf8("m_labTimeBeforeChange"));

        gridLayout->addWidget(m_labTimeBeforeChange, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);


        horizontalLayout->addWidget(m_gpMannual);


        verticalLayout->addLayout(horizontalLayout);

        m_gpBin = new QSttGroupBox(tab);
        m_gpBin->setObjectName(QString::fromUtf8("m_gpBin"));
        m_gpBin->setMinimumSize(QSize(0, 80));
        m_gpBin->setMaximumSize(QSize(16777215, 110));
        m_gpBin->setFont(font1);
        horizontalLayout_6 = new QHBoxLayout(m_gpBin);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setVerticalSpacing(0);
        gridLayout_4->setContentsMargins(-1, -1, 0, 0);
        m_cbBinD = new QSttCheckBox(m_gpBin);
        m_cbBinD->setObjectName(QString::fromUtf8("m_cbBinD"));
        QFont font3;
        font3.setPointSize(11);
        m_cbBinD->setFont(font3);
        m_cbBinD->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinD, 0, 3, 1, 1);

        m_cbBinI = new QSttCheckBox(m_gpBin);
        m_cbBinI->setObjectName(QString::fromUtf8("m_cbBinI"));
        m_cbBinI->setFont(font3);
        m_cbBinI->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinI, 0, 8, 1, 1);

        m_cbBinJ = new QSttCheckBox(m_gpBin);
        m_cbBinJ->setObjectName(QString::fromUtf8("m_cbBinJ"));
        m_cbBinJ->setFont(font3);
        m_cbBinJ->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinJ, 0, 9, 1, 1);

        m_rbOr = new QRadioButton(m_gpBin);
        m_rbOr->setObjectName(QString::fromUtf8("m_rbOr"));

        gridLayout_4->addWidget(m_rbOr, 0, 10, 1, 1);

        m_cbBinB = new QSttCheckBox(m_gpBin);
        m_cbBinB->setObjectName(QString::fromUtf8("m_cbBinB"));
        m_cbBinB->setFont(font3);
        m_cbBinB->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinB, 0, 1, 1, 1);

        m_cbBinF = new QSttCheckBox(m_gpBin);
        m_cbBinF->setObjectName(QString::fromUtf8("m_cbBinF"));
        m_cbBinF->setFont(font3);
        m_cbBinF->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinF, 0, 5, 1, 1);

        m_cbBinA = new QSttCheckBox(m_gpBin);
        m_cbBinA->setObjectName(QString::fromUtf8("m_cbBinA"));
        m_cbBinA->setFont(font3);
        m_cbBinA->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinA, 0, 0, 1, 1);

        m_cbBinC = new QSttCheckBox(m_gpBin);
        m_cbBinC->setObjectName(QString::fromUtf8("m_cbBinC"));
        m_cbBinC->setFont(font3);
        m_cbBinC->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinC, 0, 2, 1, 1);

        m_cbBinG = new QSttCheckBox(m_gpBin);
        m_cbBinG->setObjectName(QString::fromUtf8("m_cbBinG"));
        m_cbBinG->setFont(font3);
        m_cbBinG->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinG, 0, 6, 1, 1);

        m_cbBinH = new QSttCheckBox(m_gpBin);
        m_cbBinH->setObjectName(QString::fromUtf8("m_cbBinH"));
        m_cbBinH->setFont(font3);
        m_cbBinH->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinH, 0, 7, 1, 1);

        m_cbBinE = new QSttCheckBox(m_gpBin);
        m_cbBinE->setObjectName(QString::fromUtf8("m_cbBinE"));
        m_cbBinE->setFont(font3);
        m_cbBinE->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinE, 0, 4, 1, 1);

        m_rbAnd = new QRadioButton(m_gpBin);
        m_rbAnd->setObjectName(QString::fromUtf8("m_rbAnd"));
        m_rbAnd->setChecked(true);

        gridLayout_4->addWidget(m_rbAnd, 0, 11, 1, 1);


        horizontalLayout_6->addLayout(gridLayout_4);


        verticalLayout->addWidget(m_gpBin);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_gpBoutNormal = new QSttGroupBox(tab);
        m_gpBoutNormal->setObjectName(QString::fromUtf8("m_gpBoutNormal"));
        m_gpBoutNormal->setFont(font1);
        gridLayout_10 = new QGridLayout(m_gpBoutNormal);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_cbBOut1 = new QSttCheckBox(m_gpBoutNormal);
        m_cbBOut1->setObjectName(QString::fromUtf8("m_cbBOut1"));
        m_cbBOut1->setFont(font3);
        m_cbBOut1->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(m_cbBOut1, 0, 0, 1, 1);

        m_cbBOut4 = new QSttCheckBox(m_gpBoutNormal);
        m_cbBOut4->setObjectName(QString::fromUtf8("m_cbBOut4"));
        m_cbBOut4->setFont(font3);
        m_cbBOut4->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(m_cbBOut4, 0, 3, 1, 1);

        m_cbBOut3 = new QSttCheckBox(m_gpBoutNormal);
        m_cbBOut3->setObjectName(QString::fromUtf8("m_cbBOut3"));
        m_cbBOut3->setFont(font3);
        m_cbBOut3->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(m_cbBOut3, 0, 2, 1, 1);

        m_cbBOut2 = new QSttCheckBox(m_gpBoutNormal);
        m_cbBOut2->setObjectName(QString::fromUtf8("m_cbBOut2"));
        m_cbBOut2->setFont(font3);
        m_cbBOut2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(m_cbBOut2, 0, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_5, 0, 0, 1, 1);


        horizontalLayout_5->addWidget(m_gpBoutNormal);

        m_gpBoutError = new QSttGroupBox(tab);
        m_gpBoutError->setObjectName(QString::fromUtf8("m_gpBoutError"));
        m_gpBoutError->setFont(font1);
        horizontalLayout_4 = new QHBoxLayout(m_gpBoutError);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        m_cbBOut2_E = new QSttCheckBox(m_gpBoutError);
        m_cbBOut2_E->setObjectName(QString::fromUtf8("m_cbBOut2_E"));
        m_cbBOut2_E->setFont(font3);
        m_cbBOut2_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(m_cbBOut2_E, 0, 1, 1, 1);

        m_cbBOut4_E = new QSttCheckBox(m_gpBoutError);
        m_cbBOut4_E->setObjectName(QString::fromUtf8("m_cbBOut4_E"));
        m_cbBOut4_E->setFont(font3);
        m_cbBOut4_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(m_cbBOut4_E, 0, 3, 1, 1);

        m_cbBOut1_E = new QSttCheckBox(m_gpBoutError);
        m_cbBOut1_E->setObjectName(QString::fromUtf8("m_cbBOut1_E"));
        m_cbBOut1_E->setFont(font3);
        m_cbBOut1_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(m_cbBOut1_E, 0, 0, 1, 1);

        m_cbBOut3_E = new QSttCheckBox(m_gpBoutError);
        m_cbBOut3_E->setObjectName(QString::fromUtf8("m_cbBOut3_E"));
        m_cbBOut3_E->setFont(font3);
        m_cbBOut3_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(m_cbBOut3_E, 0, 2, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_7);


        horizontalLayout_5->addWidget(m_gpBoutError);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_btnSettingValue = new QPushButton(tab);
        m_btnSettingValue->setObjectName(QString::fromUtf8("m_btnSettingValue"));
        m_btnSettingValue->setFont(font1);

        horizontalLayout_2->addWidget(m_btnSettingValue);

        m_btnEstimate = new QPushButton(tab);
        m_btnEstimate->setObjectName(QString::fromUtf8("m_btnEstimate"));
        m_btnEstimate->setFont(font1);

        horizontalLayout_2->addWidget(m_btnEstimate);

        m_btnMoreOut = new QPushButton(tab);
        m_btnMoreOut->setObjectName(QString::fromUtf8("m_btnMoreOut"));
        m_btnMoreOut->setFont(font1);

        horizontalLayout_2->addWidget(m_btnMoreOut);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);

        verticalLayout_2->addLayout(verticalLayout);

        m_tabWidget->addTab(tab, QString());

        m_MainLayout->addWidget(m_tabWidget);


        gridLayout_2->addLayout(m_MainLayout, 0, 0, 1, 1);


        retranslateUi(QSttMacroParaEditViewSequenceGradient);

        m_tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QSttMacroParaEditViewSequenceGradient);
    } // setupUi

    void retranslateUi(QWidget *QSttMacroParaEditViewSequenceGradient)
    {
        QSttMacroParaEditViewSequenceGradient->setWindowTitle(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "QSttMacroParaEditViewGradient", 0, QApplication::UnicodeUTF8));
        m_gpChangeSet->setTitle(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\351\200\222\345\217\230\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_labInit->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\217\230\345\214\226\345\247\213\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labStep->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\217\230\345\214\226\346\255\245\351\225\277(A):", 0, QApplication::UnicodeUTF8));
        m_labTime->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labFinish->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\217\230\345\214\226\347\273\210\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_gpVarSet->setTitle(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\217\230\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_labDirection->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\351\200\222\345\217\230\346\226\271\345\220\221:", 0, QApplication::UnicodeUTF8));
        m_labType->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labVarType->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\217\230\351\207\217\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labVar->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\217\230\351\207\217:", 0, QApplication::UnicodeUTF8));
        m_gpMannual->setTitle(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labTimeBeforeFail->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_cbBefore->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\350\204\211\345\206\262", 0, QApplication::UnicodeUTF8));
        m_labTimeBeforeChange->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\217\230\345\214\226\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_gpBin->setTitle(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_cbBinD->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "D", 0, QApplication::UnicodeUTF8));
        m_cbBinI->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "I", 0, QApplication::UnicodeUTF8));
        m_cbBinJ->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "J", 0, QApplication::UnicodeUTF8));
        m_rbOr->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        m_cbBinB->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "B", 0, QApplication::UnicodeUTF8));
        m_cbBinF->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "F", 0, QApplication::UnicodeUTF8));
        m_cbBinA->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "A", 0, QApplication::UnicodeUTF8));
        m_cbBinC->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "C", 0, QApplication::UnicodeUTF8));
        m_cbBinG->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "G", 0, QApplication::UnicodeUTF8));
        m_cbBinH->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "H", 0, QApplication::UnicodeUTF8));
        m_cbBinE->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "E", 0, QApplication::UnicodeUTF8));
        m_rbAnd->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_gpBoutNormal->setTitle(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\274\200\345\207\272\351\207\217\346\255\243\345\270\270\346\200\201", 0, QApplication::UnicodeUTF8));
        m_cbBOut1->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "1", 0, QApplication::UnicodeUTF8));
        m_cbBOut4->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "4", 0, QApplication::UnicodeUTF8));
        m_cbBOut3->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "3", 0, QApplication::UnicodeUTF8));
        m_cbBOut2->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "2", 0, QApplication::UnicodeUTF8));
        m_gpBoutError->setTitle(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\345\274\200\345\207\272\351\207\217\346\225\205\351\232\234\346\200\201", 0, QApplication::UnicodeUTF8));
        m_cbBOut2_E->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "2", 0, QApplication::UnicodeUTF8));
        m_cbBOut4_E->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "4", 0, QApplication::UnicodeUTF8));
        m_cbBOut1_E->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "1", 0, QApplication::UnicodeUTF8));
        m_cbBOut3_E->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "3", 0, QApplication::UnicodeUTF8));
        m_btnSettingValue->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_btnEstimate->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\346\225\264\345\256\232\345\217\212\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_btnMoreOut->setText(QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\346\233\264\345\244\232\345\274\200\345\207\272\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab), QApplication::translate("QSttMacroParaEditViewSequenceGradient", "\351\200\222\345\217\230\351\200\232\351\201\223\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttMacroParaEditViewSequenceGradient: public Ui_QSttMacroParaEditViewSequenceGradient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTMACROPARAEDITVIEWSEQUENCEGRADIENT_H
