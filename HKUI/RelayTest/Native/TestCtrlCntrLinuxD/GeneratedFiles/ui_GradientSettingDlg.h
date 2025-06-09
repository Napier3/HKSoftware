/********************************************************************************
** Form generated from reading UI file 'GradientSettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRADIENTSETTINGDLG_H
#define UI_GRADIENTSETTINGDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttGroupBox.h"
#include "../Controls/SttTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_QGradientSettingDlg
{
public:
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
    QSttGroupBox *m_gbNormal;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_3;
    QSttCheckBox *m_cbBOut3;
    QSttCheckBox *m_cbBOut4;
    QSttCheckBox *m_cbBOut6;
    QSttCheckBox *m_cbBOut7;
    QSttCheckBox *m_cbBOut2;
    QSttCheckBox *m_cbBOut10;
    QSttCheckBox *m_cbBOut8;
    QSttCheckBox *m_cbBOut5;
    QSttCheckBox *m_cbBOut9;
    QSttCheckBox *m_cbBOut1;
    QSttGroupBox *m_gbError;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_4;
    QSttCheckBox *m_cbBOut10_E;
    QSttCheckBox *m_cbBOut4_E;
    QSttCheckBox *m_cbBOut2_E;
    QSttCheckBox *m_cbBOut7_E;
    QSttCheckBox *m_cbBOut5_E;
    QSttCheckBox *m_cbBOut6_E;
    QSttCheckBox *m_cbBOut9_E;
    QSttCheckBox *m_cbBOut1_E;
    QSttCheckBox *m_cbBOut8_E;
    QSttCheckBox *m_cbBOut3_E;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *QGradientSettingDlg)
    {
        if (QGradientSettingDlg->objectName().isEmpty())
            QGradientSettingDlg->setObjectName(QString::fromUtf8("QGradientSettingDlg"));
        QGradientSettingDlg->resize(600, 400);
        QFont font;
        font.setPointSize(18);
        QGradientSettingDlg->setFont(font);
        QGradientSettingDlg->setWindowOpacity(1);
        verticalLayout = new QVBoxLayout(QGradientSettingDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QSttTabWidget(QGradientSettingDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font1;
        font1.setPointSize(20);
        tabWidget->setFont(font1);
        m_tabBIn = new QWidget();
        m_tabBIn->setObjectName(QString::fromUtf8("m_tabBIn"));
        verticalLayout_2 = new QVBoxLayout(m_tabBIn);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_cbBinC = new QSttCheckBox(m_tabBIn);
        m_cbBinC->setObjectName(QString::fromUtf8("m_cbBinC"));
        QFont font2;
        font2.setPointSize(16);
        m_cbBinC->setFont(font2);
        m_cbBinC->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinC, 0, 2, 1, 1);

        m_cbBinA = new QSttCheckBox(m_tabBIn);
        m_cbBinA->setObjectName(QString::fromUtf8("m_cbBinA"));
        m_cbBinA->setFont(font2);
        m_cbBinA->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinA, 0, 0, 1, 1);

        m_cbBinB = new QSttCheckBox(m_tabBIn);
        m_cbBinB->setObjectName(QString::fromUtf8("m_cbBinB"));
        m_cbBinB->setFont(font2);
        m_cbBinB->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinB, 0, 1, 1, 1);

        m_cbBinD = new QSttCheckBox(m_tabBIn);
        m_cbBinD->setObjectName(QString::fromUtf8("m_cbBinD"));
        m_cbBinD->setFont(font2);
        m_cbBinD->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinD, 0, 3, 1, 1);

        m_cbBinE = new QSttCheckBox(m_tabBIn);
        m_cbBinE->setObjectName(QString::fromUtf8("m_cbBinE"));
        m_cbBinE->setFont(font2);
        m_cbBinE->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbBinE, 0, 4, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_cbBinF = new QSttCheckBox(m_tabBIn);
        m_cbBinF->setObjectName(QString::fromUtf8("m_cbBinF"));
        m_cbBinF->setFont(font2);
        m_cbBinF->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinF, 0, 1, 1, 1);

        m_cbBinG = new QSttCheckBox(m_tabBIn);
        m_cbBinG->setObjectName(QString::fromUtf8("m_cbBinG"));
        m_cbBinG->setFont(font2);
        m_cbBinG->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinG, 0, 2, 1, 1);

        m_cbBinI = new QSttCheckBox(m_tabBIn);
        m_cbBinI->setObjectName(QString::fromUtf8("m_cbBinI"));
        m_cbBinI->setFont(font2);
        m_cbBinI->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinI, 0, 4, 1, 1);

        m_cbBinH = new QSttCheckBox(m_tabBIn);
        m_cbBinH->setObjectName(QString::fromUtf8("m_cbBinH"));
        m_cbBinH->setFont(font2);
        m_cbBinH->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinH, 0, 3, 1, 1);

        m_cbBinJ = new QSttCheckBox(m_tabBIn);
        m_cbBinJ->setObjectName(QString::fromUtf8("m_cbBinJ"));
        m_cbBinJ->setFont(font2);
        m_cbBinJ->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_cbBinJ, 0, 5, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
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
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_gbNormal = new QSttGroupBox(m_tabBOut);
        m_gbNormal->setObjectName(QString::fromUtf8("m_gbNormal"));
        verticalLayout_4 = new QVBoxLayout(m_gbNormal);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_cbBOut3 = new QSttCheckBox(m_gbNormal);
        m_cbBOut3->setObjectName(QString::fromUtf8("m_cbBOut3"));
        m_cbBOut3->setFont(font2);
        m_cbBOut3->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut3, 0, 2, 1, 1);

        m_cbBOut4 = new QSttCheckBox(m_gbNormal);
        m_cbBOut4->setObjectName(QString::fromUtf8("m_cbBOut4"));
        m_cbBOut4->setFont(font2);
        m_cbBOut4->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut4, 0, 3, 1, 1);

        m_cbBOut6 = new QSttCheckBox(m_gbNormal);
        m_cbBOut6->setObjectName(QString::fromUtf8("m_cbBOut6"));
        m_cbBOut6->setFont(font2);
        m_cbBOut6->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut6, 1, 0, 1, 1);

        m_cbBOut7 = new QSttCheckBox(m_gbNormal);
        m_cbBOut7->setObjectName(QString::fromUtf8("m_cbBOut7"));
        m_cbBOut7->setFont(font2);
        m_cbBOut7->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut7, 1, 1, 1, 1);

        m_cbBOut2 = new QSttCheckBox(m_gbNormal);
        m_cbBOut2->setObjectName(QString::fromUtf8("m_cbBOut2"));
        m_cbBOut2->setFont(font2);
        m_cbBOut2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut2, 0, 1, 1, 1);

        m_cbBOut10 = new QSttCheckBox(m_gbNormal);
        m_cbBOut10->setObjectName(QString::fromUtf8("m_cbBOut10"));
        m_cbBOut10->setFont(font2);
        m_cbBOut10->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut10, 1, 4, 1, 1);

        m_cbBOut8 = new QSttCheckBox(m_gbNormal);
        m_cbBOut8->setObjectName(QString::fromUtf8("m_cbBOut8"));
        m_cbBOut8->setFont(font2);
        m_cbBOut8->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut8, 1, 2, 1, 1);

        m_cbBOut5 = new QSttCheckBox(m_gbNormal);
        m_cbBOut5->setObjectName(QString::fromUtf8("m_cbBOut5"));
        m_cbBOut5->setFont(font2);
        m_cbBOut5->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut5, 0, 4, 1, 1);

        m_cbBOut9 = new QSttCheckBox(m_gbNormal);
        m_cbBOut9->setObjectName(QString::fromUtf8("m_cbBOut9"));
        m_cbBOut9->setFont(font2);
        m_cbBOut9->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut9, 1, 3, 1, 1);

        m_cbBOut1 = new QSttCheckBox(m_gbNormal);
        m_cbBOut1->setObjectName(QString::fromUtf8("m_cbBOut1"));
        m_cbBOut1->setFont(font2);
        m_cbBOut1->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(m_cbBOut1, 0, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);


        verticalLayout_3->addWidget(m_gbNormal);

        m_gbError = new QSttGroupBox(m_tabBOut);
        m_gbError->setObjectName(QString::fromUtf8("m_gbError"));
        verticalLayout_5 = new QVBoxLayout(m_gbError);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_cbBOut10_E = new QSttCheckBox(m_gbError);
        m_cbBOut10_E->setObjectName(QString::fromUtf8("m_cbBOut10_E"));
        m_cbBOut10_E->setFont(font2);
        m_cbBOut10_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut10_E, 1, 4, 1, 1);

        m_cbBOut4_E = new QSttCheckBox(m_gbError);
        m_cbBOut4_E->setObjectName(QString::fromUtf8("m_cbBOut4_E"));
        m_cbBOut4_E->setFont(font2);
        m_cbBOut4_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut4_E, 0, 3, 1, 1);

        m_cbBOut2_E = new QSttCheckBox(m_gbError);
        m_cbBOut2_E->setObjectName(QString::fromUtf8("m_cbBOut2_E"));
        m_cbBOut2_E->setFont(font2);
        m_cbBOut2_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut2_E, 0, 1, 1, 1);

        m_cbBOut7_E = new QSttCheckBox(m_gbError);
        m_cbBOut7_E->setObjectName(QString::fromUtf8("m_cbBOut7_E"));
        m_cbBOut7_E->setFont(font2);
        m_cbBOut7_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut7_E, 1, 1, 1, 1);

        m_cbBOut5_E = new QSttCheckBox(m_gbError);
        m_cbBOut5_E->setObjectName(QString::fromUtf8("m_cbBOut5_E"));
        m_cbBOut5_E->setFont(font2);
        m_cbBOut5_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut5_E, 0, 4, 1, 1);

        m_cbBOut6_E = new QSttCheckBox(m_gbError);
        m_cbBOut6_E->setObjectName(QString::fromUtf8("m_cbBOut6_E"));
        m_cbBOut6_E->setFont(font2);
        m_cbBOut6_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut6_E, 1, 0, 1, 1);

        m_cbBOut9_E = new QSttCheckBox(m_gbError);
        m_cbBOut9_E->setObjectName(QString::fromUtf8("m_cbBOut9_E"));
        m_cbBOut9_E->setFont(font2);
        m_cbBOut9_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut9_E, 1, 3, 1, 1);

        m_cbBOut1_E = new QSttCheckBox(m_gbError);
        m_cbBOut1_E->setObjectName(QString::fromUtf8("m_cbBOut1_E"));
        m_cbBOut1_E->setFont(font2);
        m_cbBOut1_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut1_E, 0, 0, 1, 1);

        m_cbBOut8_E = new QSttCheckBox(m_gbError);
        m_cbBOut8_E->setObjectName(QString::fromUtf8("m_cbBOut8_E"));
        m_cbBOut8_E->setFont(font2);
        m_cbBOut8_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut8_E, 1, 2, 1, 1);

        m_cbBOut3_E = new QSttCheckBox(m_gbError);
        m_cbBOut3_E->setObjectName(QString::fromUtf8("m_cbBOut3_E"));
        m_cbBOut3_E->setFont(font2);
        m_cbBOut3_E->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBOut3_E, 0, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout_4);


        verticalLayout_3->addWidget(m_gbError);

        tabWidget->addTab(m_tabBOut, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnOK = new QPushButton(QGradientSettingDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));
        m_btnOK->setFont(font1);

        horizontalLayout->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QGradientSettingDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        m_btnCancel->setFont(font1);

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QGradientSettingDlg);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QGradientSettingDlg);
    } // setupUi

    void retranslateUi(QDialog *QGradientSettingDlg)
    {
        QGradientSettingDlg->setWindowTitle(QString());
        m_cbBinC->setText(QApplication::translate("QGradientSettingDlg", "C", 0, QApplication::UnicodeUTF8));
        m_cbBinA->setText(QApplication::translate("QGradientSettingDlg", "A", 0, QApplication::UnicodeUTF8));
        m_cbBinB->setText(QApplication::translate("QGradientSettingDlg", "B", 0, QApplication::UnicodeUTF8));
        m_cbBinD->setText(QApplication::translate("QGradientSettingDlg", "D", 0, QApplication::UnicodeUTF8));
        m_cbBinE->setText(QApplication::translate("QGradientSettingDlg", "E", 0, QApplication::UnicodeUTF8));
        m_cbBinF->setText(QApplication::translate("QGradientSettingDlg", "F", 0, QApplication::UnicodeUTF8));
        m_cbBinG->setText(QApplication::translate("QGradientSettingDlg", "G", 0, QApplication::UnicodeUTF8));
        m_cbBinI->setText(QApplication::translate("QGradientSettingDlg", "I", 0, QApplication::UnicodeUTF8));
        m_cbBinH->setText(QApplication::translate("QGradientSettingDlg", "H", 0, QApplication::UnicodeUTF8));
        m_cbBinJ->setText(QApplication::translate("QGradientSettingDlg", "J", 0, QApplication::UnicodeUTF8));
        m_rbAnd->setText(QApplication::translate("QGradientSettingDlg", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_rbOr->setText(QApplication::translate("QGradientSettingDlg", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(m_tabBIn), QApplication::translate("QGradientSettingDlg", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_gbNormal->setTitle(QApplication::translate("QGradientSettingDlg", "\345\270\270\346\200\201", 0, QApplication::UnicodeUTF8));
        m_cbBOut3->setText(QApplication::translate("QGradientSettingDlg", "3", 0, QApplication::UnicodeUTF8));
        m_cbBOut4->setText(QApplication::translate("QGradientSettingDlg", "4", 0, QApplication::UnicodeUTF8));
        m_cbBOut6->setText(QApplication::translate("QGradientSettingDlg", "6", 0, QApplication::UnicodeUTF8));
        m_cbBOut7->setText(QApplication::translate("QGradientSettingDlg", "7", 0, QApplication::UnicodeUTF8));
        m_cbBOut2->setText(QApplication::translate("QGradientSettingDlg", "2", 0, QApplication::UnicodeUTF8));
        m_cbBOut10->setText(QApplication::translate("QGradientSettingDlg", "10", 0, QApplication::UnicodeUTF8));
        m_cbBOut8->setText(QApplication::translate("QGradientSettingDlg", "8", 0, QApplication::UnicodeUTF8));
        m_cbBOut5->setText(QApplication::translate("QGradientSettingDlg", "5", 0, QApplication::UnicodeUTF8));
        m_cbBOut9->setText(QApplication::translate("QGradientSettingDlg", "9", 0, QApplication::UnicodeUTF8));
        m_cbBOut1->setText(QApplication::translate("QGradientSettingDlg", "1", 0, QApplication::UnicodeUTF8));
        m_gbError->setTitle(QApplication::translate("QGradientSettingDlg", "\346\225\205\351\232\234\346\200\201", 0, QApplication::UnicodeUTF8));
        m_cbBOut10_E->setText(QApplication::translate("QGradientSettingDlg", "10", 0, QApplication::UnicodeUTF8));
        m_cbBOut4_E->setText(QApplication::translate("QGradientSettingDlg", "4", 0, QApplication::UnicodeUTF8));
        m_cbBOut2_E->setText(QApplication::translate("QGradientSettingDlg", "2", 0, QApplication::UnicodeUTF8));
        m_cbBOut7_E->setText(QApplication::translate("QGradientSettingDlg", "7", 0, QApplication::UnicodeUTF8));
        m_cbBOut5_E->setText(QApplication::translate("QGradientSettingDlg", "5", 0, QApplication::UnicodeUTF8));
        m_cbBOut6_E->setText(QApplication::translate("QGradientSettingDlg", "6", 0, QApplication::UnicodeUTF8));
        m_cbBOut9_E->setText(QApplication::translate("QGradientSettingDlg", "9", 0, QApplication::UnicodeUTF8));
        m_cbBOut1_E->setText(QApplication::translate("QGradientSettingDlg", "1", 0, QApplication::UnicodeUTF8));
        m_cbBOut8_E->setText(QApplication::translate("QGradientSettingDlg", "8", 0, QApplication::UnicodeUTF8));
        m_cbBOut3_E->setText(QApplication::translate("QGradientSettingDlg", "3", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(m_tabBOut), QApplication::translate("QGradientSettingDlg", "\345\274\200\345\207\272\351\207\217", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QGradientSettingDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QGradientSettingDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QGradientSettingDlg: public Ui_QGradientSettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRADIENTSETTINGDLG_H
