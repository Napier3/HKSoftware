/********************************************************************************
** Form generated from reading UI file 'PowerDirBinarySignalDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POWERDIRBINARYSIGNALDLG_H
#define UI_POWERDIRBINARYSIGNALDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QPowerDirBinarySignalDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *m_gbBIn;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QCheckBox *m_cbBinSelectB;
    QCheckBox *m_cbBinSelectA;
    QCheckBox *m_cbBinSelectC;
    QCheckBox *m_cbBinSelectD;
    QCheckBox *m_cbBinSelectE;
    QCheckBox *m_cbBinSelectF;
    QCheckBox *m_cbBinSelectG;
    QCheckBox *m_cbBinSelectH;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *m_rbAnd;
    QRadioButton *m_rbOr;
    QGroupBox *m_gbNormalBOut;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_3;
    QCheckBox *m_cbBout01;
    QCheckBox *m_cbBout03;
    QCheckBox *m_cbBout04;
    QCheckBox *m_cbBout02;
    QCheckBox *m_cbBout05;
    QCheckBox *m_cbBout06;
    QCheckBox *m_cbBout07;
    QCheckBox *m_cbBout08;
    QGroupBox *m_gbFaultBOut;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_5;
    QCheckBox *m_cbBout1;
    QCheckBox *m_cbBout4;
    QCheckBox *m_cbBout2;
    QCheckBox *m_cbBout3;
    QCheckBox *m_cbBout5;
    QCheckBox *m_cbBout6;
    QCheckBox *m_cbBout7;
    QCheckBox *m_cbBout8;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *QPowerDirBinarySignalDlg)
    {
        if (QPowerDirBinarySignalDlg->objectName().isEmpty())
            QPowerDirBinarySignalDlg->setObjectName(QString::fromUtf8("QPowerDirBinarySignalDlg"));
        QPowerDirBinarySignalDlg->resize(432, 405);
        horizontalLayout = new QHBoxLayout(QPowerDirBinarySignalDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_gbBIn = new QGroupBox(QPowerDirBinarySignalDlg);
        m_gbBIn->setObjectName(QString::fromUtf8("m_gbBIn"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_gbBIn->sizePolicy().hasHeightForWidth());
        m_gbBIn->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(m_gbBIn);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_cbBinSelectB = new QCheckBox(m_gbBIn);
        m_cbBinSelectB->setObjectName(QString::fromUtf8("m_cbBinSelectB"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_cbBinSelectB->sizePolicy().hasHeightForWidth());
        m_cbBinSelectB->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_cbBinSelectB, 0, 1, 1, 1);

        m_cbBinSelectA = new QCheckBox(m_gbBIn);
        m_cbBinSelectA->setObjectName(QString::fromUtf8("m_cbBinSelectA"));
        sizePolicy1.setHeightForWidth(m_cbBinSelectA->sizePolicy().hasHeightForWidth());
        m_cbBinSelectA->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_cbBinSelectA, 0, 0, 1, 1);

        m_cbBinSelectC = new QCheckBox(m_gbBIn);
        m_cbBinSelectC->setObjectName(QString::fromUtf8("m_cbBinSelectC"));
        sizePolicy1.setHeightForWidth(m_cbBinSelectC->sizePolicy().hasHeightForWidth());
        m_cbBinSelectC->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_cbBinSelectC, 0, 2, 1, 1);

        m_cbBinSelectD = new QCheckBox(m_gbBIn);
        m_cbBinSelectD->setObjectName(QString::fromUtf8("m_cbBinSelectD"));
        sizePolicy1.setHeightForWidth(m_cbBinSelectD->sizePolicy().hasHeightForWidth());
        m_cbBinSelectD->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_cbBinSelectD, 0, 3, 1, 1);

        m_cbBinSelectE = new QCheckBox(m_gbBIn);
        m_cbBinSelectE->setObjectName(QString::fromUtf8("m_cbBinSelectE"));
        sizePolicy1.setHeightForWidth(m_cbBinSelectE->sizePolicy().hasHeightForWidth());
        m_cbBinSelectE->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_cbBinSelectE, 1, 0, 1, 1);

        m_cbBinSelectF = new QCheckBox(m_gbBIn);
        m_cbBinSelectF->setObjectName(QString::fromUtf8("m_cbBinSelectF"));
        sizePolicy1.setHeightForWidth(m_cbBinSelectF->sizePolicy().hasHeightForWidth());
        m_cbBinSelectF->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_cbBinSelectF, 1, 1, 1, 1);

        m_cbBinSelectG = new QCheckBox(m_gbBIn);
        m_cbBinSelectG->setObjectName(QString::fromUtf8("m_cbBinSelectG"));
        sizePolicy1.setHeightForWidth(m_cbBinSelectG->sizePolicy().hasHeightForWidth());
        m_cbBinSelectG->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_cbBinSelectG, 1, 2, 1, 1);

        m_cbBinSelectH = new QCheckBox(m_gbBIn);
        m_cbBinSelectH->setObjectName(QString::fromUtf8("m_cbBinSelectH"));
        sizePolicy1.setHeightForWidth(m_cbBinSelectH->sizePolicy().hasHeightForWidth());
        m_cbBinSelectH->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_cbBinSelectH, 1, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_rbAnd = new QRadioButton(m_gbBIn);
        m_rbAnd->setObjectName(QString::fromUtf8("m_rbAnd"));
        sizePolicy1.setHeightForWidth(m_rbAnd->sizePolicy().hasHeightForWidth());
        m_rbAnd->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(m_rbAnd);

        m_rbOr = new QRadioButton(m_gbBIn);
        m_rbOr->setObjectName(QString::fromUtf8("m_rbOr"));
        sizePolicy1.setHeightForWidth(m_rbOr->sizePolicy().hasHeightForWidth());
        m_rbOr->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(m_rbOr);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout_4->addLayout(verticalLayout_2);


        verticalLayout->addWidget(m_gbBIn);

        m_gbNormalBOut = new QGroupBox(QPowerDirBinarySignalDlg);
        m_gbNormalBOut->setObjectName(QString::fromUtf8("m_gbNormalBOut"));
        sizePolicy.setHeightForWidth(m_gbNormalBOut->sizePolicy().hasHeightForWidth());
        m_gbNormalBOut->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(m_gbNormalBOut);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_cbBout01 = new QCheckBox(m_gbNormalBOut);
        m_cbBout01->setObjectName(QString::fromUtf8("m_cbBout01"));
        sizePolicy1.setHeightForWidth(m_cbBout01->sizePolicy().hasHeightForWidth());
        m_cbBout01->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_cbBout01, 0, 0, 1, 1);

        m_cbBout03 = new QCheckBox(m_gbNormalBOut);
        m_cbBout03->setObjectName(QString::fromUtf8("m_cbBout03"));
        sizePolicy1.setHeightForWidth(m_cbBout03->sizePolicy().hasHeightForWidth());
        m_cbBout03->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_cbBout03, 0, 2, 1, 1);

        m_cbBout04 = new QCheckBox(m_gbNormalBOut);
        m_cbBout04->setObjectName(QString::fromUtf8("m_cbBout04"));
        sizePolicy1.setHeightForWidth(m_cbBout04->sizePolicy().hasHeightForWidth());
        m_cbBout04->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_cbBout04, 0, 3, 1, 1);

        m_cbBout02 = new QCheckBox(m_gbNormalBOut);
        m_cbBout02->setObjectName(QString::fromUtf8("m_cbBout02"));
        sizePolicy1.setHeightForWidth(m_cbBout02->sizePolicy().hasHeightForWidth());
        m_cbBout02->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_cbBout02, 0, 1, 1, 1);

        m_cbBout05 = new QCheckBox(m_gbNormalBOut);
        m_cbBout05->setObjectName(QString::fromUtf8("m_cbBout05"));
        sizePolicy1.setHeightForWidth(m_cbBout05->sizePolicy().hasHeightForWidth());
        m_cbBout05->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_cbBout05, 1, 0, 1, 1);

        m_cbBout06 = new QCheckBox(m_gbNormalBOut);
        m_cbBout06->setObjectName(QString::fromUtf8("m_cbBout06"));
        sizePolicy1.setHeightForWidth(m_cbBout06->sizePolicy().hasHeightForWidth());
        m_cbBout06->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_cbBout06, 1, 1, 1, 1);

        m_cbBout07 = new QCheckBox(m_gbNormalBOut);
        m_cbBout07->setObjectName(QString::fromUtf8("m_cbBout07"));
        sizePolicy1.setHeightForWidth(m_cbBout07->sizePolicy().hasHeightForWidth());
        m_cbBout07->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_cbBout07, 1, 2, 1, 1);

        m_cbBout08 = new QCheckBox(m_gbNormalBOut);
        m_cbBout08->setObjectName(QString::fromUtf8("m_cbBout08"));
        sizePolicy1.setHeightForWidth(m_cbBout08->sizePolicy().hasHeightForWidth());
        m_cbBout08->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_cbBout08, 1, 3, 1, 1);


        verticalLayout_3->addLayout(gridLayout_3);


        verticalLayout->addWidget(m_gbNormalBOut);

        m_gbFaultBOut = new QGroupBox(QPowerDirBinarySignalDlg);
        m_gbFaultBOut->setObjectName(QString::fromUtf8("m_gbFaultBOut"));
        sizePolicy.setHeightForWidth(m_gbFaultBOut->sizePolicy().hasHeightForWidth());
        m_gbFaultBOut->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(m_gbFaultBOut);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_cbBout1 = new QCheckBox(m_gbFaultBOut);
        m_cbBout1->setObjectName(QString::fromUtf8("m_cbBout1"));
        sizePolicy1.setHeightForWidth(m_cbBout1->sizePolicy().hasHeightForWidth());
        m_cbBout1->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_cbBout1, 0, 0, 1, 1);

        m_cbBout4 = new QCheckBox(m_gbFaultBOut);
        m_cbBout4->setObjectName(QString::fromUtf8("m_cbBout4"));
        sizePolicy1.setHeightForWidth(m_cbBout4->sizePolicy().hasHeightForWidth());
        m_cbBout4->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_cbBout4, 0, 3, 1, 1);

        m_cbBout2 = new QCheckBox(m_gbFaultBOut);
        m_cbBout2->setObjectName(QString::fromUtf8("m_cbBout2"));
        sizePolicy1.setHeightForWidth(m_cbBout2->sizePolicy().hasHeightForWidth());
        m_cbBout2->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_cbBout2, 0, 1, 1, 1);

        m_cbBout3 = new QCheckBox(m_gbFaultBOut);
        m_cbBout3->setObjectName(QString::fromUtf8("m_cbBout3"));
        sizePolicy1.setHeightForWidth(m_cbBout3->sizePolicy().hasHeightForWidth());
        m_cbBout3->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_cbBout3, 0, 2, 1, 1);

        m_cbBout5 = new QCheckBox(m_gbFaultBOut);
        m_cbBout5->setObjectName(QString::fromUtf8("m_cbBout5"));
        sizePolicy1.setHeightForWidth(m_cbBout5->sizePolicy().hasHeightForWidth());
        m_cbBout5->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_cbBout5, 1, 0, 1, 1);

        m_cbBout6 = new QCheckBox(m_gbFaultBOut);
        m_cbBout6->setObjectName(QString::fromUtf8("m_cbBout6"));
        sizePolicy1.setHeightForWidth(m_cbBout6->sizePolicy().hasHeightForWidth());
        m_cbBout6->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_cbBout6, 1, 1, 1, 1);

        m_cbBout7 = new QCheckBox(m_gbFaultBOut);
        m_cbBout7->setObjectName(QString::fromUtf8("m_cbBout7"));
        sizePolicy1.setHeightForWidth(m_cbBout7->sizePolicy().hasHeightForWidth());
        m_cbBout7->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_cbBout7, 1, 2, 1, 1);

        m_cbBout8 = new QCheckBox(m_gbFaultBOut);
        m_cbBout8->setObjectName(QString::fromUtf8("m_cbBout8"));
        sizePolicy1.setHeightForWidth(m_cbBout8->sizePolicy().hasHeightForWidth());
        m_cbBout8->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(m_cbBout8, 1, 3, 1, 1);


        verticalLayout_5->addLayout(gridLayout_5);


        verticalLayout->addWidget(m_gbFaultBOut);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer);

        m_btnOk = new QPushButton(QPowerDirBinarySignalDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        sizePolicy1.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(m_btnOk);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_3);

        m_btnCancel = new QPushButton(QPowerDirBinarySignalDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy1.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_13);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QPowerDirBinarySignalDlg);

        QMetaObject::connectSlotsByName(QPowerDirBinarySignalDlg);
    } // setupUi

    void retranslateUi(QDialog *QPowerDirBinarySignalDlg)
    {
        QPowerDirBinarySignalDlg->setWindowTitle(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\263\351\207\217", 0, QApplication::UnicodeUTF8));
        m_gbBIn->setTitle(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\245\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectB->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\245B", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectA->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\245A", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectC->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\245C", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectD->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\245D", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectE->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\245E", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectF->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\245F", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectG->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\245G", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectH->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\205\245H", 0, QApplication::UnicodeUTF8));
        m_rbAnd->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_rbOr->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        m_gbNormalBOut->setTitle(QApplication::translate("QPowerDirBinarySignalDlg", "\345\270\270\346\200\201\345\274\200\345\207\272\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_cbBout01->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2721", 0, QApplication::UnicodeUTF8));
        m_cbBout03->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2723", 0, QApplication::UnicodeUTF8));
        m_cbBout04->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2724", 0, QApplication::UnicodeUTF8));
        m_cbBout02->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2722", 0, QApplication::UnicodeUTF8));
        m_cbBout05->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2725", 0, QApplication::UnicodeUTF8));
        m_cbBout06->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2726", 0, QApplication::UnicodeUTF8));
        m_cbBout07->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2727", 0, QApplication::UnicodeUTF8));
        m_cbBout08->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2728", 0, QApplication::UnicodeUTF8));
        m_gbFaultBOut->setTitle(QApplication::translate("QPowerDirBinarySignalDlg", "\346\225\205\351\232\234\346\200\201\345\274\200\345\207\272\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_cbBout1->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2721", 0, QApplication::UnicodeUTF8));
        m_cbBout4->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2724", 0, QApplication::UnicodeUTF8));
        m_cbBout2->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2722", 0, QApplication::UnicodeUTF8));
        m_cbBout3->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2723", 0, QApplication::UnicodeUTF8));
        m_cbBout5->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2725", 0, QApplication::UnicodeUTF8));
        m_cbBout6->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2726", 0, QApplication::UnicodeUTF8));
        m_cbBout7->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2727", 0, QApplication::UnicodeUTF8));
        m_cbBout8->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\274\200\345\207\2728", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QPowerDirBinarySignalDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QPowerDirBinarySignalDlg: public Ui_QPowerDirBinarySignalDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POWERDIRBINARYSIGNALDLG_H
