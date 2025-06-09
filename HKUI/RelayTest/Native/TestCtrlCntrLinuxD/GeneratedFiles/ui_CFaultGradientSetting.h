/********************************************************************************
** Form generated from reading UI file 'CFaultGradientSetting.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CFAULTGRADIENTSETTING_H
#define UI_CFAULTGRADIENTSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CFaultGradientSetting
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QSttTabWidget *tabWidget;
    QWidget *m_tabBIn;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QSttCheckBox *m_cbBinC;
    QSttCheckBox *m_cbBinA;
    QSttCheckBox *m_cbBinB;
    QSttCheckBox *m_cbBinD;
    QSttCheckBox *m_cbBinE;
    QGridLayout *gridLayout_2;
    QSttCheckBox *m_cbBinF;
    QSttCheckBox *m_cbBinG;
    QSttCheckBox *m_cbBinI;
    QSttCheckBox *m_cbBinH;
    QSttCheckBox *m_cbBinJ;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *m_rbAnd;
    QSpacerItem *horizontalSpacer_5;
    QRadioButton *m_rbOr;
    QSpacerItem *horizontalSpacer_4;
    QWidget *m_tabBOut;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *m_gbNormal;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_3;
    QSttCheckBox *m_cbBOut2;
    QSttCheckBox *m_cbBOut3;
    QSttCheckBox *m_cbBOut5;
    QSttCheckBox *m_cbBOut6;
    QSttCheckBox *m_cbBOut1;
    QSttCheckBox *m_cbBOut9;
    QSttCheckBox *m_cbBOut7;
    QSttCheckBox *m_cbBOut4;
    QSttCheckBox *m_cbBOut8;
    QSttCheckBox *m_cbBOut0;
    QGroupBox *m_gbError;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_4;
    QSttCheckBox *m_cbBOut10_E19;
    QSttCheckBox *m_cbBOut4_E13;
    QSttCheckBox *m_cbBOut2_E11;
    QSttCheckBox *m_cbBOut7_E16;
    QSttCheckBox *m_cbBOut5_E14;
    QSttCheckBox *m_cbBOut6_E15;
    QSttCheckBox *m_cbBOut9_E18;
    QSttCheckBox *m_cbBOut1_E10;
    QSttCheckBox *m_cbBOut8_E17;
    QSttCheckBox *m_cbBOut3_E12;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;
    QButtonGroup *btnGrpNormal;
    QButtonGroup *btnGrpError;

    void setupUi(QDialog *CFaultGradientSetting)
    {
        if (CFaultGradientSetting->objectName().isEmpty())
            CFaultGradientSetting->setObjectName(QString::fromUtf8("CFaultGradientSetting"));
        CFaultGradientSetting->resize(610, 475);
        verticalLayout_6 = new QVBoxLayout(CFaultGradientSetting);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QSttTabWidget(CFaultGradientSetting);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font;
        font.setPointSize(20);
        tabWidget->setFont(font);
        m_tabBIn = new QWidget();
        m_tabBIn->setObjectName(QString::fromUtf8("m_tabBIn"));
        verticalLayout_2 = new QVBoxLayout(m_tabBIn);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_cbBinC = new QSttCheckBox(m_tabBIn);
        m_cbBinC->setObjectName(QString::fromUtf8("m_cbBinC"));
        QFont font1;
        font1.setPointSize(16);
        m_cbBinC->setFont(font1);
        m_cbBinC->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinC, 0, 2, 1, 1);

        m_cbBinA = new QSttCheckBox(m_tabBIn);
        m_cbBinA->setObjectName(QString::fromUtf8("m_cbBinA"));
        m_cbBinA->setFont(font1);
        m_cbBinA->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinA, 0, 0, 1, 1);

        m_cbBinB = new QSttCheckBox(m_tabBIn);
        m_cbBinB->setObjectName(QString::fromUtf8("m_cbBinB"));
        m_cbBinB->setFont(font1);
        m_cbBinB->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinB, 0, 1, 1, 1);

        m_cbBinD = new QSttCheckBox(m_tabBIn);
        m_cbBinD->setObjectName(QString::fromUtf8("m_cbBinD"));
        m_cbBinD->setFont(font1);
        m_cbBinD->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinD, 0, 3, 1, 1);

        m_cbBinE = new QSttCheckBox(m_tabBIn);
        m_cbBinE->setObjectName(QString::fromUtf8("m_cbBinE"));
        m_cbBinE->setFont(font1);
        m_cbBinE->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinE, 0, 4, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_cbBinF = new QSttCheckBox(m_tabBIn);
        m_cbBinF->setObjectName(QString::fromUtf8("m_cbBinF"));
        m_cbBinF->setFont(font1);
        m_cbBinF->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinF, 0, 1, 1, 1);

        m_cbBinG = new QSttCheckBox(m_tabBIn);
        m_cbBinG->setObjectName(QString::fromUtf8("m_cbBinG"));
        m_cbBinG->setFont(font1);
        m_cbBinG->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinG, 0, 2, 1, 1);

        m_cbBinI = new QSttCheckBox(m_tabBIn);
        m_cbBinI->setObjectName(QString::fromUtf8("m_cbBinI"));
        m_cbBinI->setFont(font1);
        m_cbBinI->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinI, 0, 4, 1, 1);

        m_cbBinH = new QSttCheckBox(m_tabBIn);
        m_cbBinH->setObjectName(QString::fromUtf8("m_cbBinH"));
        m_cbBinH->setFont(font1);
        m_cbBinH->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinH, 0, 3, 1, 1);

        m_cbBinJ = new QSttCheckBox(m_tabBIn);
        m_cbBinJ->setObjectName(QString::fromUtf8("m_cbBinJ"));
        m_cbBinJ->setFont(font1);
        m_cbBinJ->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinJ, 0, 5, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        m_rbAnd = new QRadioButton(m_tabBIn);
        m_rbAnd->setObjectName(QString::fromUtf8("m_rbAnd"));
        m_rbAnd->setChecked(true);

        horizontalLayout_4->addWidget(m_rbAnd);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        m_rbOr = new QRadioButton(m_tabBIn);
        m_rbOr->setObjectName(QString::fromUtf8("m_rbOr"));

        horizontalLayout_4->addWidget(m_rbOr);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tabWidget->addTab(m_tabBIn, QString());
        m_tabBOut = new QWidget();
        m_tabBOut->setObjectName(QString::fromUtf8("m_tabBOut"));
        verticalLayout_3 = new QVBoxLayout(m_tabBOut);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_gbNormal = new QGroupBox(m_tabBOut);
        m_gbNormal->setObjectName(QString::fromUtf8("m_gbNormal"));
        verticalLayout_4 = new QVBoxLayout(m_gbNormal);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_cbBOut2 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal = new QButtonGroup(CFaultGradientSetting);
        btnGrpNormal->setObjectName(QString::fromUtf8("btnGrpNormal"));
        btnGrpNormal->setExclusive(false);
        btnGrpNormal->addButton(m_cbBOut2);
        m_cbBOut2->setObjectName(QString::fromUtf8("m_cbBOut2"));
        m_cbBOut2->setFont(font1);
        m_cbBOut2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut2, 0, 2, 1, 1);

        m_cbBOut3 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal->addButton(m_cbBOut3);
        m_cbBOut3->setObjectName(QString::fromUtf8("m_cbBOut3"));
        m_cbBOut3->setFont(font1);
        m_cbBOut3->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut3, 0, 3, 1, 1);

        m_cbBOut5 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal->addButton(m_cbBOut5);
        m_cbBOut5->setObjectName(QString::fromUtf8("m_cbBOut5"));
        m_cbBOut5->setFont(font1);
        m_cbBOut5->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut5, 1, 0, 1, 1);

        m_cbBOut6 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal->addButton(m_cbBOut6);
        m_cbBOut6->setObjectName(QString::fromUtf8("m_cbBOut6"));
        m_cbBOut6->setFont(font1);
        m_cbBOut6->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut6, 1, 1, 1, 1);

        m_cbBOut1 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal->addButton(m_cbBOut1);
        m_cbBOut1->setObjectName(QString::fromUtf8("m_cbBOut1"));
        m_cbBOut1->setFont(font1);
        m_cbBOut1->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut1, 0, 1, 1, 1);

        m_cbBOut9 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal->addButton(m_cbBOut9);
        m_cbBOut9->setObjectName(QString::fromUtf8("m_cbBOut9"));
        m_cbBOut9->setFont(font1);
        m_cbBOut9->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut9, 1, 4, 1, 1);

        m_cbBOut7 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal->addButton(m_cbBOut7);
        m_cbBOut7->setObjectName(QString::fromUtf8("m_cbBOut7"));
        m_cbBOut7->setFont(font1);
        m_cbBOut7->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut7, 1, 2, 1, 1);

        m_cbBOut4 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal->addButton(m_cbBOut4);
        m_cbBOut4->setObjectName(QString::fromUtf8("m_cbBOut4"));
        m_cbBOut4->setFont(font1);
        m_cbBOut4->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut4, 0, 4, 1, 1);

        m_cbBOut8 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal->addButton(m_cbBOut8);
        m_cbBOut8->setObjectName(QString::fromUtf8("m_cbBOut8"));
        m_cbBOut8->setFont(font1);
        m_cbBOut8->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut8, 1, 3, 1, 1);

        m_cbBOut0 = new QSttCheckBox(m_gbNormal);
        btnGrpNormal->addButton(m_cbBOut0);
        m_cbBOut0->setObjectName(QString::fromUtf8("m_cbBOut0"));
        m_cbBOut0->setFont(font1);
        m_cbBOut0->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut0, 0, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);


        verticalLayout_3->addWidget(m_gbNormal);

        m_gbError = new QGroupBox(m_tabBOut);
        m_gbError->setObjectName(QString::fromUtf8("m_gbError"));
        verticalLayout_5 = new QVBoxLayout(m_gbError);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_cbBOut10_E19 = new QSttCheckBox(m_gbError);
        btnGrpError = new QButtonGroup(CFaultGradientSetting);
        btnGrpError->setObjectName(QString::fromUtf8("btnGrpError"));
        btnGrpError->setExclusive(false);
        btnGrpError->addButton(m_cbBOut10_E19);
        m_cbBOut10_E19->setObjectName(QString::fromUtf8("m_cbBOut10_E19"));
        m_cbBOut10_E19->setFont(font1);
        m_cbBOut10_E19->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut10_E19, 1, 4, 1, 1);

        m_cbBOut4_E13 = new QSttCheckBox(m_gbError);
        btnGrpError->addButton(m_cbBOut4_E13);
        m_cbBOut4_E13->setObjectName(QString::fromUtf8("m_cbBOut4_E13"));
        m_cbBOut4_E13->setFont(font1);
        m_cbBOut4_E13->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut4_E13, 0, 3, 1, 1);

        m_cbBOut2_E11 = new QSttCheckBox(m_gbError);
        btnGrpError->addButton(m_cbBOut2_E11);
        m_cbBOut2_E11->setObjectName(QString::fromUtf8("m_cbBOut2_E11"));
        m_cbBOut2_E11->setFont(font1);
        m_cbBOut2_E11->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut2_E11, 0, 1, 1, 1);

        m_cbBOut7_E16 = new QSttCheckBox(m_gbError);
        btnGrpError->addButton(m_cbBOut7_E16);
        m_cbBOut7_E16->setObjectName(QString::fromUtf8("m_cbBOut7_E16"));
        m_cbBOut7_E16->setFont(font1);
        m_cbBOut7_E16->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut7_E16, 1, 1, 1, 1);

        m_cbBOut5_E14 = new QSttCheckBox(m_gbError);
        btnGrpError->addButton(m_cbBOut5_E14);
        m_cbBOut5_E14->setObjectName(QString::fromUtf8("m_cbBOut5_E14"));
        m_cbBOut5_E14->setFont(font1);
        m_cbBOut5_E14->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut5_E14, 0, 4, 1, 1);

        m_cbBOut6_E15 = new QSttCheckBox(m_gbError);
        btnGrpError->addButton(m_cbBOut6_E15);
        m_cbBOut6_E15->setObjectName(QString::fromUtf8("m_cbBOut6_E15"));
        m_cbBOut6_E15->setFont(font1);
        m_cbBOut6_E15->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut6_E15, 1, 0, 1, 1);

        m_cbBOut9_E18 = new QSttCheckBox(m_gbError);
        btnGrpError->addButton(m_cbBOut9_E18);
        m_cbBOut9_E18->setObjectName(QString::fromUtf8("m_cbBOut9_E18"));
        m_cbBOut9_E18->setFont(font1);
        m_cbBOut9_E18->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut9_E18, 1, 3, 1, 1);

        m_cbBOut1_E10 = new QSttCheckBox(m_gbError);
        btnGrpError->addButton(m_cbBOut1_E10);
        m_cbBOut1_E10->setObjectName(QString::fromUtf8("m_cbBOut1_E10"));
        m_cbBOut1_E10->setFont(font1);
        m_cbBOut1_E10->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut1_E10, 0, 0, 1, 1);

        m_cbBOut8_E17 = new QSttCheckBox(m_gbError);
        btnGrpError->addButton(m_cbBOut8_E17);
        m_cbBOut8_E17->setObjectName(QString::fromUtf8("m_cbBOut8_E17"));
        m_cbBOut8_E17->setFont(font1);
        m_cbBOut8_E17->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut8_E17, 1, 2, 1, 1);

        m_cbBOut3_E12 = new QSttCheckBox(m_gbError);
        btnGrpError->addButton(m_cbBOut3_E12);
        m_cbBOut3_E12->setObjectName(QString::fromUtf8("m_cbBOut3_E12"));
        m_cbBOut3_E12->setFont(font1);
        m_cbBOut3_E12->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut3_E12, 0, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout_4);


        verticalLayout_3->addWidget(m_gbError);

        tabWidget->addTab(m_tabBOut, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnOK = new QPushButton(CFaultGradientSetting);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));
        m_btnOK->setFont(font);

        horizontalLayout->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(CFaultGradientSetting);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        m_btnCancel->setFont(font);

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_6->addLayout(verticalLayout);


        retranslateUi(CFaultGradientSetting);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CFaultGradientSetting);
    } // setupUi

    void retranslateUi(QDialog *CFaultGradientSetting)
    {
        CFaultGradientSetting->setWindowTitle(QApplication::translate("CFaultGradientSetting", "\345\274\200\345\207\272\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_cbBinC->setText(QApplication::translate("CFaultGradientSetting", "C", 0, QApplication::UnicodeUTF8));
        m_cbBinA->setText(QApplication::translate("CFaultGradientSetting", "A", 0, QApplication::UnicodeUTF8));
        m_cbBinB->setText(QApplication::translate("CFaultGradientSetting", "B", 0, QApplication::UnicodeUTF8));
        m_cbBinD->setText(QApplication::translate("CFaultGradientSetting", "D", 0, QApplication::UnicodeUTF8));
        m_cbBinE->setText(QApplication::translate("CFaultGradientSetting", "E", 0, QApplication::UnicodeUTF8));
        m_cbBinF->setText(QApplication::translate("CFaultGradientSetting", "F", 0, QApplication::UnicodeUTF8));
        m_cbBinG->setText(QApplication::translate("CFaultGradientSetting", "G", 0, QApplication::UnicodeUTF8));
        m_cbBinI->setText(QApplication::translate("CFaultGradientSetting", "I", 0, QApplication::UnicodeUTF8));
        m_cbBinH->setText(QApplication::translate("CFaultGradientSetting", "H", 0, QApplication::UnicodeUTF8));
        m_cbBinJ->setText(QApplication::translate("CFaultGradientSetting", "J", 0, QApplication::UnicodeUTF8));
        m_rbAnd->setText(QApplication::translate("CFaultGradientSetting", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_rbOr->setText(QApplication::translate("CFaultGradientSetting", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(m_tabBIn), QApplication::translate("CFaultGradientSetting", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_gbNormal->setTitle(QApplication::translate("CFaultGradientSetting", "\345\270\270\346\200\201", 0, QApplication::UnicodeUTF8));
        m_cbBOut2->setText(QApplication::translate("CFaultGradientSetting", "3", 0, QApplication::UnicodeUTF8));
        m_cbBOut3->setText(QApplication::translate("CFaultGradientSetting", "4", 0, QApplication::UnicodeUTF8));
        m_cbBOut5->setText(QApplication::translate("CFaultGradientSetting", "6", 0, QApplication::UnicodeUTF8));
        m_cbBOut6->setText(QApplication::translate("CFaultGradientSetting", "7", 0, QApplication::UnicodeUTF8));
        m_cbBOut1->setText(QApplication::translate("CFaultGradientSetting", "2", 0, QApplication::UnicodeUTF8));
        m_cbBOut9->setText(QApplication::translate("CFaultGradientSetting", "10", 0, QApplication::UnicodeUTF8));
        m_cbBOut7->setText(QApplication::translate("CFaultGradientSetting", "8", 0, QApplication::UnicodeUTF8));
        m_cbBOut4->setText(QApplication::translate("CFaultGradientSetting", "5", 0, QApplication::UnicodeUTF8));
        m_cbBOut8->setText(QApplication::translate("CFaultGradientSetting", "9", 0, QApplication::UnicodeUTF8));
        m_cbBOut0->setText(QApplication::translate("CFaultGradientSetting", "1", 0, QApplication::UnicodeUTF8));
        m_gbError->setTitle(QApplication::translate("CFaultGradientSetting", "\346\225\205\351\232\234\346\200\201", 0, QApplication::UnicodeUTF8));
        m_cbBOut10_E19->setText(QApplication::translate("CFaultGradientSetting", "10", 0, QApplication::UnicodeUTF8));
        m_cbBOut4_E13->setText(QApplication::translate("CFaultGradientSetting", "4", 0, QApplication::UnicodeUTF8));
        m_cbBOut2_E11->setText(QApplication::translate("CFaultGradientSetting", "2", 0, QApplication::UnicodeUTF8));
        m_cbBOut7_E16->setText(QApplication::translate("CFaultGradientSetting", "7", 0, QApplication::UnicodeUTF8));
        m_cbBOut5_E14->setText(QApplication::translate("CFaultGradientSetting", "5", 0, QApplication::UnicodeUTF8));
        m_cbBOut6_E15->setText(QApplication::translate("CFaultGradientSetting", "6", 0, QApplication::UnicodeUTF8));
        m_cbBOut9_E18->setText(QApplication::translate("CFaultGradientSetting", "9", 0, QApplication::UnicodeUTF8));
        m_cbBOut1_E10->setText(QApplication::translate("CFaultGradientSetting", "1", 0, QApplication::UnicodeUTF8));
        m_cbBOut8_E17->setText(QApplication::translate("CFaultGradientSetting", "8", 0, QApplication::UnicodeUTF8));
        m_cbBOut3_E12->setText(QApplication::translate("CFaultGradientSetting", "3", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(m_tabBOut), QApplication::translate("CFaultGradientSetting", "\345\274\200\345\207\272\351\207\217", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("CFaultGradientSetting", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("CFaultGradientSetting", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CFaultGradientSetting: public Ui_CFaultGradientSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CFAULTGRADIENTSETTING_H
