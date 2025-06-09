/********************************************************************************
** Form generated from reading UI file 'QSttManualBinBoutDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSTTMANUALBINBOUTDLG_H
#define UI_QSTTMANUALBINBOUTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttGroupBox.h"
#include "../Controls/SttLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QSttManualBinBoutDlg
{
public:
    QVBoxLayout *verticalLayout;
    QSttGroupBox *m_boxInSetting;
    QGridLayout *gridLayout;
    QSttCheckBox *m_cbInA;
    QSttCheckBox *m_cbInB;
    QSttCheckBox *m_cbInC;
    QSttCheckBox *m_cbInD;
    QSttCheckBox *m_cbInE;
    QRadioButton *m_rdOr;
    QSttCheckBox *m_cbInF;
    QSttCheckBox *m_cbInG;
    QSttCheckBox *m_cbInH;
    QSttCheckBox *m_cbInI;
    QSttCheckBox *m_cbInJ;
    QRadioButton *m_rdAnd;
    QSttGroupBox *m_boxOutSetting;
    QHBoxLayout *horizontalLayout;
    QSttCheckBox *m_cbOut5;
    QSttCheckBox *m_cbOut6;
    QSttCheckBox *m_cbOut7;
    QSttCheckBox *m_cbOut8;
    QSttCheckBox *m_cbOut9;
    QSttCheckBox *m_cbOut10;
    QGroupBox *m_GroupDelayed;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labDelayed;
    QSttLineEdit *m_editDelayed;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *_2;
    QSpacerItem *spacerItem;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *QSttManualBinBoutDlg)
    {
        if (QSttManualBinBoutDlg->objectName().isEmpty())
            QSttManualBinBoutDlg->setObjectName(QString::fromUtf8("QSttManualBinBoutDlg"));
        QSttManualBinBoutDlg->resize(498, 396);
        verticalLayout = new QVBoxLayout(QSttManualBinBoutDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_boxInSetting = new QSttGroupBox(QSttManualBinBoutDlg);
        m_boxInSetting->setObjectName(QString::fromUtf8("m_boxInSetting"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_boxInSetting->sizePolicy().hasHeightForWidth());
        m_boxInSetting->setSizePolicy(sizePolicy);
        m_boxInSetting->setMinimumSize(QSize(0, 120));
        m_boxInSetting->setMaximumSize(QSize(16777215, 120));
        QFont font;
        font.setPointSize(20);
        m_boxInSetting->setFont(font);
        gridLayout = new QGridLayout(m_boxInSetting);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_cbInA = new QSttCheckBox(m_boxInSetting);
        m_cbInA->setObjectName(QString::fromUtf8("m_cbInA"));
        m_cbInA->setFont(font);
        m_cbInA->setStyleSheet(QString::fromUtf8(""));
        m_cbInA->setChecked(true);

        gridLayout->addWidget(m_cbInA, 0, 0, 1, 1);

        m_cbInB = new QSttCheckBox(m_boxInSetting);
        m_cbInB->setObjectName(QString::fromUtf8("m_cbInB"));
        m_cbInB->setFont(font);
        m_cbInB->setStyleSheet(QString::fromUtf8(""));
        m_cbInB->setChecked(true);

        gridLayout->addWidget(m_cbInB, 0, 1, 1, 1);

        m_cbInC = new QSttCheckBox(m_boxInSetting);
        m_cbInC->setObjectName(QString::fromUtf8("m_cbInC"));
        m_cbInC->setFont(font);
        m_cbInC->setStyleSheet(QString::fromUtf8(""));
        m_cbInC->setChecked(true);

        gridLayout->addWidget(m_cbInC, 0, 2, 1, 1);

        m_cbInD = new QSttCheckBox(m_boxInSetting);
        m_cbInD->setObjectName(QString::fromUtf8("m_cbInD"));
        m_cbInD->setFont(font);
        m_cbInD->setStyleSheet(QString::fromUtf8(""));
        m_cbInD->setChecked(true);

        gridLayout->addWidget(m_cbInD, 0, 3, 1, 1);

        m_cbInE = new QSttCheckBox(m_boxInSetting);
        m_cbInE->setObjectName(QString::fromUtf8("m_cbInE"));
        m_cbInE->setFont(font);
        m_cbInE->setStyleSheet(QString::fromUtf8(""));
        m_cbInE->setChecked(true);

        gridLayout->addWidget(m_cbInE, 0, 4, 1, 1);

        m_rdOr = new QRadioButton(m_boxInSetting);
        m_rdOr->setObjectName(QString::fromUtf8("m_rdOr"));
        m_rdOr->setFont(font);
        m_rdOr->setChecked(true);

        gridLayout->addWidget(m_rdOr, 0, 5, 1, 1);

        m_cbInF = new QSttCheckBox(m_boxInSetting);
        m_cbInF->setObjectName(QString::fromUtf8("m_cbInF"));
        m_cbInF->setFont(font);
        m_cbInF->setStyleSheet(QString::fromUtf8(""));
        m_cbInF->setChecked(true);

        gridLayout->addWidget(m_cbInF, 1, 0, 1, 1);

        m_cbInG = new QSttCheckBox(m_boxInSetting);
        m_cbInG->setObjectName(QString::fromUtf8("m_cbInG"));
        m_cbInG->setFont(font);
        m_cbInG->setStyleSheet(QString::fromUtf8(""));
        m_cbInG->setChecked(true);

        gridLayout->addWidget(m_cbInG, 1, 1, 1, 1);

        m_cbInH = new QSttCheckBox(m_boxInSetting);
        m_cbInH->setObjectName(QString::fromUtf8("m_cbInH"));
        m_cbInH->setFont(font);
        m_cbInH->setStyleSheet(QString::fromUtf8(""));
        m_cbInH->setChecked(true);

        gridLayout->addWidget(m_cbInH, 1, 2, 1, 1);

        m_cbInI = new QSttCheckBox(m_boxInSetting);
        m_cbInI->setObjectName(QString::fromUtf8("m_cbInI"));
        m_cbInI->setFont(font);
        m_cbInI->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbInI, 1, 3, 1, 1);

        m_cbInJ = new QSttCheckBox(m_boxInSetting);
        m_cbInJ->setObjectName(QString::fromUtf8("m_cbInJ"));
        m_cbInJ->setFont(font);
        m_cbInJ->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbInJ, 1, 4, 1, 1);

        m_rdAnd = new QRadioButton(m_boxInSetting);
        m_rdAnd->setObjectName(QString::fromUtf8("m_rdAnd"));
        m_rdAnd->setFont(font);

        gridLayout->addWidget(m_rdAnd, 1, 5, 1, 1);


        verticalLayout->addWidget(m_boxInSetting);

        m_boxOutSetting = new QSttGroupBox(QSttManualBinBoutDlg);
        m_boxOutSetting->setObjectName(QString::fromUtf8("m_boxOutSetting"));
        sizePolicy.setHeightForWidth(m_boxOutSetting->sizePolicy().hasHeightForWidth());
        m_boxOutSetting->setSizePolicy(sizePolicy);
        m_boxOutSetting->setMinimumSize(QSize(0, 80));
        m_boxOutSetting->setMaximumSize(QSize(16777215, 80));
        m_boxOutSetting->setFont(font);
        horizontalLayout = new QHBoxLayout(m_boxOutSetting);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_cbOut5 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut5->setObjectName(QString::fromUtf8("m_cbOut5"));
        m_cbOut5->setFont(font);
        m_cbOut5->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_cbOut5);

        m_cbOut6 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut6->setObjectName(QString::fromUtf8("m_cbOut6"));
        m_cbOut6->setFont(font);
        m_cbOut6->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_cbOut6);

        m_cbOut7 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut7->setObjectName(QString::fromUtf8("m_cbOut7"));
        m_cbOut7->setFont(font);
        m_cbOut7->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_cbOut7);

        m_cbOut8 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut8->setObjectName(QString::fromUtf8("m_cbOut8"));
        m_cbOut8->setFont(font);
        m_cbOut8->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_cbOut8);

        m_cbOut9 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut9->setObjectName(QString::fromUtf8("m_cbOut9"));
        m_cbOut9->setFont(font);
        m_cbOut9->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_cbOut9);

        m_cbOut10 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut10->setObjectName(QString::fromUtf8("m_cbOut10"));
        m_cbOut10->setFont(font);
        m_cbOut10->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_cbOut10);


        verticalLayout->addWidget(m_boxOutSetting);

        m_GroupDelayed = new QGroupBox(QSttManualBinBoutDlg);
        m_GroupDelayed->setObjectName(QString::fromUtf8("m_GroupDelayed"));
        m_GroupDelayed->setMinimumSize(QSize(0, 60));
        m_GroupDelayed->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_2 = new QHBoxLayout(m_GroupDelayed);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labDelayed = new QLabel(m_GroupDelayed);
        m_labDelayed->setObjectName(QString::fromUtf8("m_labDelayed"));
        m_labDelayed->setMaximumSize(QSize(300, 16777215));
        m_labDelayed->setFont(font);

        horizontalLayout_2->addWidget(m_labDelayed);

        m_editDelayed = new QSttLineEdit(m_GroupDelayed);
        m_editDelayed->setObjectName(QString::fromUtf8("m_editDelayed"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_editDelayed->sizePolicy().hasHeightForWidth());
        m_editDelayed->setSizePolicy(sizePolicy1);
        m_editDelayed->setMaximumSize(QSize(100, 16777215));
        m_editDelayed->setFont(font);

        horizontalLayout_2->addWidget(m_editDelayed);

        horizontalSpacer_2 = new QSpacerItem(197, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(m_GroupDelayed);

        _2 = new QHBoxLayout();
        _2->setSpacing(6);
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _2->addItem(spacerItem);

        m_btnOK = new QPushButton(QSttManualBinBoutDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        _2->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QSttManualBinBoutDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        _2->addWidget(m_btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(_2);


        retranslateUi(QSttManualBinBoutDlg);

        QMetaObject::connectSlotsByName(QSttManualBinBoutDlg);
    } // setupUi

    void retranslateUi(QDialog *QSttManualBinBoutDlg)
    {
        QSttManualBinBoutDlg->setWindowTitle(QApplication::translate("QSttManualBinBoutDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        m_boxInSetting->setTitle(QApplication::translate("QSttManualBinBoutDlg", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_cbInA->setText(QApplication::translate("QSttManualBinBoutDlg", "A", 0, QApplication::UnicodeUTF8));
        m_cbInB->setText(QApplication::translate("QSttManualBinBoutDlg", "B", 0, QApplication::UnicodeUTF8));
        m_cbInC->setText(QApplication::translate("QSttManualBinBoutDlg", "C", 0, QApplication::UnicodeUTF8));
        m_cbInD->setText(QApplication::translate("QSttManualBinBoutDlg", "D", 0, QApplication::UnicodeUTF8));
        m_cbInE->setText(QApplication::translate("QSttManualBinBoutDlg", "E", 0, QApplication::UnicodeUTF8));
        m_rdOr->setText(QApplication::translate("QSttManualBinBoutDlg", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        m_cbInF->setText(QApplication::translate("QSttManualBinBoutDlg", "F", 0, QApplication::UnicodeUTF8));
        m_cbInG->setText(QApplication::translate("QSttManualBinBoutDlg", "G", 0, QApplication::UnicodeUTF8));
        m_cbInH->setText(QApplication::translate("QSttManualBinBoutDlg", "H", 0, QApplication::UnicodeUTF8));
        m_cbInI->setText(QApplication::translate("QSttManualBinBoutDlg", "I", 0, QApplication::UnicodeUTF8));
        m_cbInJ->setText(QApplication::translate("QSttManualBinBoutDlg", "J", 0, QApplication::UnicodeUTF8));
        m_rdAnd->setText(QApplication::translate("QSttManualBinBoutDlg", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_boxOutSetting->setTitle(QApplication::translate("QSttManualBinBoutDlg", "\345\274\200\345\207\272\351\207\217", 0, QApplication::UnicodeUTF8));
        m_cbOut5->setText(QApplication::translate("QSttManualBinBoutDlg", "5", 0, QApplication::UnicodeUTF8));
        m_cbOut6->setText(QApplication::translate("QSttManualBinBoutDlg", "6", 0, QApplication::UnicodeUTF8));
        m_cbOut7->setText(QApplication::translate("QSttManualBinBoutDlg", "7", 0, QApplication::UnicodeUTF8));
        m_cbOut8->setText(QApplication::translate("QSttManualBinBoutDlg", "8", 0, QApplication::UnicodeUTF8));
        m_cbOut9->setText(QApplication::translate("QSttManualBinBoutDlg", "9", 0, QApplication::UnicodeUTF8));
        m_cbOut10->setText(QApplication::translate("QSttManualBinBoutDlg", "10", 0, QApplication::UnicodeUTF8));
        m_GroupDelayed->setTitle(QString());
        m_labDelayed->setText(QApplication::translate("QSttManualBinBoutDlg", "\350\247\246\345\217\221\345\220\216\345\273\266\346\227\266(s):", 0, QApplication::UnicodeUTF8));
        m_editDelayed->setText(QString());
        m_btnOK->setText(QApplication::translate("QSttManualBinBoutDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QSttManualBinBoutDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttManualBinBoutDlg: public Ui_QSttManualBinBoutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSTTMANUALBINBOUTDLG_H
