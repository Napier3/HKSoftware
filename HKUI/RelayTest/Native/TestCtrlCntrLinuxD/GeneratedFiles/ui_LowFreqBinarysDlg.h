/********************************************************************************
** Form generated from reading UI file 'LowFreqBinarysDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWFREQBINARYSDLG_H
#define UI_LOWFREQBINARYSDLG_H

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

QT_BEGIN_NAMESPACE

class Ui_QLowFreqBinarysDlg
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QCheckBox *m_check_A;
    QCheckBox *m_check_B;
    QCheckBox *m_check_C;
    QCheckBox *m_check_D;
    QCheckBox *m_check_E;
    QCheckBox *m_check_F;
    QCheckBox *m_check_G;
    QCheckBox *m_check_H;
    QSpacerItem *horizontalSpacer;
    QRadioButton *m_rbtn_LogicAnd;
    QRadioButton *m_rbtn_LogicOr;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QCheckBox *m_check_B01;
    QCheckBox *m_check_B02;
    QCheckBox *m_check_B03;
    QCheckBox *m_check_B04;
    QCheckBox *m_check_B05;
    QCheckBox *m_check_B06;
    QCheckBox *m_check_B07;
    QCheckBox *m_check_B08;

    void setupUi(QDialog *QLowFreqBinarysDlg)
    {
        if (QLowFreqBinarysDlg->objectName().isEmpty())
            QLowFreqBinarysDlg->setObjectName(QString::fromUtf8("QLowFreqBinarysDlg"));
        QLowFreqBinarysDlg->resize(399, 304);
        gridLayout = new QGridLayout(QLowFreqBinarysDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(QLowFreqBinarysDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_check_A = new QCheckBox(groupBox);
        m_check_A->setObjectName(QString::fromUtf8("m_check_A"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_check_A->sizePolicy().hasHeightForWidth());
        m_check_A->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_check_A, 0, 0, 1, 1);

        m_check_B = new QCheckBox(groupBox);
        m_check_B->setObjectName(QString::fromUtf8("m_check_B"));
        sizePolicy.setHeightForWidth(m_check_B->sizePolicy().hasHeightForWidth());
        m_check_B->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_check_B, 0, 1, 1, 1);

        m_check_C = new QCheckBox(groupBox);
        m_check_C->setObjectName(QString::fromUtf8("m_check_C"));
        sizePolicy.setHeightForWidth(m_check_C->sizePolicy().hasHeightForWidth());
        m_check_C->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_check_C, 0, 2, 1, 1);

        m_check_D = new QCheckBox(groupBox);
        m_check_D->setObjectName(QString::fromUtf8("m_check_D"));
        sizePolicy.setHeightForWidth(m_check_D->sizePolicy().hasHeightForWidth());
        m_check_D->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_check_D, 0, 3, 1, 1);

        m_check_E = new QCheckBox(groupBox);
        m_check_E->setObjectName(QString::fromUtf8("m_check_E"));
        sizePolicy.setHeightForWidth(m_check_E->sizePolicy().hasHeightForWidth());
        m_check_E->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_check_E, 0, 4, 1, 1);

        m_check_F = new QCheckBox(groupBox);
        m_check_F->setObjectName(QString::fromUtf8("m_check_F"));
        sizePolicy.setHeightForWidth(m_check_F->sizePolicy().hasHeightForWidth());
        m_check_F->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_check_F, 1, 0, 1, 1);

        m_check_G = new QCheckBox(groupBox);
        m_check_G->setObjectName(QString::fromUtf8("m_check_G"));
        sizePolicy.setHeightForWidth(m_check_G->sizePolicy().hasHeightForWidth());
        m_check_G->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_check_G, 1, 1, 1, 1);

        m_check_H = new QCheckBox(groupBox);
        m_check_H->setObjectName(QString::fromUtf8("m_check_H"));
        sizePolicy.setHeightForWidth(m_check_H->sizePolicy().hasHeightForWidth());
        m_check_H->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_check_H, 1, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 5);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        m_rbtn_LogicAnd = new QRadioButton(groupBox);
        m_rbtn_LogicAnd->setObjectName(QString::fromUtf8("m_rbtn_LogicAnd"));
        m_rbtn_LogicAnd->setChecked(true);

        gridLayout_3->addWidget(m_rbtn_LogicAnd, 1, 1, 1, 1);

        m_rbtn_LogicOr = new QRadioButton(groupBox);
        m_rbtn_LogicOr->setObjectName(QString::fromUtf8("m_rbtn_LogicOr"));

        gridLayout_3->addWidget(m_rbtn_LogicOr, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 1, 2, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        m_btnOK = new QPushButton(QLowFreqBinarysDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QLowFreqBinarysDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(QLowFreqBinarysDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_check_B01 = new QCheckBox(groupBox_2);
        m_check_B01->setObjectName(QString::fromUtf8("m_check_B01"));
        sizePolicy.setHeightForWidth(m_check_B01->sizePolicy().hasHeightForWidth());
        m_check_B01->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_check_B01, 0, 0, 1, 1);

        m_check_B02 = new QCheckBox(groupBox_2);
        m_check_B02->setObjectName(QString::fromUtf8("m_check_B02"));
        sizePolicy.setHeightForWidth(m_check_B02->sizePolicy().hasHeightForWidth());
        m_check_B02->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_check_B02, 0, 1, 1, 1);

        m_check_B03 = new QCheckBox(groupBox_2);
        m_check_B03->setObjectName(QString::fromUtf8("m_check_B03"));
        sizePolicy.setHeightForWidth(m_check_B03->sizePolicy().hasHeightForWidth());
        m_check_B03->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_check_B03, 0, 2, 1, 1);

        m_check_B04 = new QCheckBox(groupBox_2);
        m_check_B04->setObjectName(QString::fromUtf8("m_check_B04"));
        sizePolicy.setHeightForWidth(m_check_B04->sizePolicy().hasHeightForWidth());
        m_check_B04->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_check_B04, 0, 3, 1, 1);

        m_check_B05 = new QCheckBox(groupBox_2);
        m_check_B05->setObjectName(QString::fromUtf8("m_check_B05"));
        sizePolicy.setHeightForWidth(m_check_B05->sizePolicy().hasHeightForWidth());
        m_check_B05->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_check_B05, 0, 4, 1, 1);

        m_check_B06 = new QCheckBox(groupBox_2);
        m_check_B06->setObjectName(QString::fromUtf8("m_check_B06"));
        sizePolicy.setHeightForWidth(m_check_B06->sizePolicy().hasHeightForWidth());
        m_check_B06->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_check_B06, 1, 0, 1, 1);

        m_check_B07 = new QCheckBox(groupBox_2);
        m_check_B07->setObjectName(QString::fromUtf8("m_check_B07"));
        sizePolicy.setHeightForWidth(m_check_B07->sizePolicy().hasHeightForWidth());
        m_check_B07->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_check_B07, 1, 1, 1, 1);

        m_check_B08 = new QCheckBox(groupBox_2);
        m_check_B08->setObjectName(QString::fromUtf8("m_check_B08"));
        sizePolicy.setHeightForWidth(m_check_B08->sizePolicy().hasHeightForWidth());
        m_check_B08->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_check_B08, 1, 2, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(QLowFreqBinarysDlg);

        QMetaObject::connectSlotsByName(QLowFreqBinarysDlg);
    } // setupUi

    void retranslateUi(QDialog *QLowFreqBinarysDlg)
    {
        QLowFreqBinarysDlg->setWindowTitle(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\263\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\245\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_check_A->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\245A", 0, QApplication::UnicodeUTF8));
        m_check_B->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\245B", 0, QApplication::UnicodeUTF8));
        m_check_C->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\245C", 0, QApplication::UnicodeUTF8));
        m_check_D->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\245D", 0, QApplication::UnicodeUTF8));
        m_check_E->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\245E", 0, QApplication::UnicodeUTF8));
        m_check_F->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\245F", 0, QApplication::UnicodeUTF8));
        m_check_G->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\245G", 0, QApplication::UnicodeUTF8));
        m_check_H->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\205\245H", 0, QApplication::UnicodeUTF8));
        m_rbtn_LogicAnd->setText(QApplication::translate("QLowFreqBinarysDlg", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_rbtn_LogicOr->setText(QApplication::translate("QLowFreqBinarysDlg", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QLowFreqBinarysDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\207\272\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_check_B01->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\207\2721", 0, QApplication::UnicodeUTF8));
        m_check_B02->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\207\2722", 0, QApplication::UnicodeUTF8));
        m_check_B03->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\207\2723", 0, QApplication::UnicodeUTF8));
        m_check_B04->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\207\2724", 0, QApplication::UnicodeUTF8));
        m_check_B05->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\207\2725", 0, QApplication::UnicodeUTF8));
        m_check_B06->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\207\2726", 0, QApplication::UnicodeUTF8));
        m_check_B07->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\207\2727", 0, QApplication::UnicodeUTF8));
        m_check_B08->setText(QApplication::translate("QLowFreqBinarysDlg", "\345\274\200\345\207\2728", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLowFreqBinarysDlg: public Ui_QLowFreqBinarysDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWFREQBINARYSDLG_H
