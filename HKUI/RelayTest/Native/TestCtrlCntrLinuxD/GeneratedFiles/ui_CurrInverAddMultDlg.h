/********************************************************************************
** Form generated from reading UI file 'CurrInverAddMultDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CURRINVERADDMULTDLG_H
#define UI_CURRINVERADDMULTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QCurrInverAddMultDlg
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *m_labSelect;
    QComboBox *m_cmbSelect;
    QLabel *m_labFaultVolt;
    QSettingLineEdit *m_lineFaultVolt;
    QLabel *m_labFaultAngle;
    QSettingLineEdit *m_lineFaultAngle;
    QLabel *m_labHz;
    QSettingLineEdit *m_lineHz;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *m_labChangeStart;
    QSettingLineEdit *m_lineChangeStart;
    QLabel *m_labChangeFinal;
    QSettingLineEdit *m_lineChangeFinal;
    QLabel *m_labChangeStep;
    QSettingLineEdit *m_lineChangeStep;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QCheckBox *chb_AN;
    QCheckBox *chb_BN;
    QCheckBox *chb_CN;
    QCheckBox *chb_AB;
    QCheckBox *chb_BC;
    QCheckBox *chb_CA;
    QCheckBox *chb_ABC;
    QCheckBox *chb_IaIbIc;
    QCheckBox *chb_3I0;
    QCheckBox *chb_I2;
    QCheckBox *chb_A;
    QCheckBox *chb_B;
    QCheckBox *chb_C;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QLabel *m_labRelErr;
    QSettingLineEdit *m_lineRelErr;
    QLabel *m_labErrorLogic;
    QSettingLineEdit *m_linePlus;
    QSettingLineEdit *m_lineMinus;
    QComboBox *m_cmbErrorLogic;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labAbsErr_2;
    QLabel *m_labMinus;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labAbsErr;
    QLabel *m_labPlus;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pbn_Ok;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pbn_Cancel;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QDialog *QCurrInverAddMultDlg)
    {
        if (QCurrInverAddMultDlg->objectName().isEmpty())
            QCurrInverAddMultDlg->setObjectName(QString::fromUtf8("QCurrInverAddMultDlg"));
        QCurrInverAddMultDlg->resize(502, 496);
        gridLayout_5 = new QGridLayout(QCurrInverAddMultDlg);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(QCurrInverAddMultDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labSelect = new QLabel(groupBox);
        m_labSelect->setObjectName(QString::fromUtf8("m_labSelect"));

        gridLayout->addWidget(m_labSelect, 0, 0, 1, 1);

        m_cmbSelect = new QComboBox(groupBox);
        m_cmbSelect->setObjectName(QString::fromUtf8("m_cmbSelect"));

        gridLayout->addWidget(m_cmbSelect, 0, 1, 1, 1);

        m_labFaultVolt = new QLabel(groupBox);
        m_labFaultVolt->setObjectName(QString::fromUtf8("m_labFaultVolt"));

        gridLayout->addWidget(m_labFaultVolt, 1, 0, 1, 1);

        m_lineFaultVolt = new QSettingLineEdit(groupBox);
        m_lineFaultVolt->setObjectName(QString::fromUtf8("m_lineFaultVolt"));

        gridLayout->addWidget(m_lineFaultVolt, 1, 1, 1, 1);

        m_labFaultAngle = new QLabel(groupBox);
        m_labFaultAngle->setObjectName(QString::fromUtf8("m_labFaultAngle"));

        gridLayout->addWidget(m_labFaultAngle, 2, 0, 1, 1);

        m_lineFaultAngle = new QSettingLineEdit(groupBox);
        m_lineFaultAngle->setObjectName(QString::fromUtf8("m_lineFaultAngle"));

        gridLayout->addWidget(m_lineFaultAngle, 2, 1, 1, 1);

        m_labHz = new QLabel(groupBox);
        m_labHz->setObjectName(QString::fromUtf8("m_labHz"));

        gridLayout->addWidget(m_labHz, 3, 0, 1, 1);

        m_lineHz = new QSettingLineEdit(groupBox);
        m_lineHz->setObjectName(QString::fromUtf8("m_lineHz"));

        gridLayout->addWidget(m_lineHz, 3, 1, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(QCurrInverAddMultDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_labChangeStart = new QLabel(groupBox_2);
        m_labChangeStart->setObjectName(QString::fromUtf8("m_labChangeStart"));

        gridLayout_2->addWidget(m_labChangeStart, 0, 0, 1, 1);

        m_lineChangeStart = new QSettingLineEdit(groupBox_2);
        m_lineChangeStart->setObjectName(QString::fromUtf8("m_lineChangeStart"));

        gridLayout_2->addWidget(m_lineChangeStart, 0, 1, 1, 1);

        m_labChangeFinal = new QLabel(groupBox_2);
        m_labChangeFinal->setObjectName(QString::fromUtf8("m_labChangeFinal"));

        gridLayout_2->addWidget(m_labChangeFinal, 1, 0, 1, 1);

        m_lineChangeFinal = new QSettingLineEdit(groupBox_2);
        m_lineChangeFinal->setObjectName(QString::fromUtf8("m_lineChangeFinal"));

        gridLayout_2->addWidget(m_lineChangeFinal, 1, 1, 1, 1);

        m_labChangeStep = new QLabel(groupBox_2);
        m_labChangeStep->setObjectName(QString::fromUtf8("m_labChangeStep"));

        gridLayout_2->addWidget(m_labChangeStep, 2, 0, 1, 1);

        m_lineChangeStep = new QSettingLineEdit(groupBox_2);
        m_lineChangeStep->setObjectName(QString::fromUtf8("m_lineChangeStep"));

        gridLayout_2->addWidget(m_lineChangeStep, 2, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(QCurrInverAddMultDlg);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        chb_AN = new QCheckBox(groupBox_3);
        chb_AN->setObjectName(QString::fromUtf8("chb_AN"));

        gridLayout_3->addWidget(chb_AN, 0, 0, 1, 1);

        chb_BN = new QCheckBox(groupBox_3);
        chb_BN->setObjectName(QString::fromUtf8("chb_BN"));

        gridLayout_3->addWidget(chb_BN, 0, 1, 1, 1);

        chb_CN = new QCheckBox(groupBox_3);
        chb_CN->setObjectName(QString::fromUtf8("chb_CN"));

        gridLayout_3->addWidget(chb_CN, 0, 2, 1, 2);

        chb_AB = new QCheckBox(groupBox_3);
        chb_AB->setObjectName(QString::fromUtf8("chb_AB"));

        gridLayout_3->addWidget(chb_AB, 1, 0, 1, 1);

        chb_BC = new QCheckBox(groupBox_3);
        chb_BC->setObjectName(QString::fromUtf8("chb_BC"));

        gridLayout_3->addWidget(chb_BC, 1, 1, 1, 1);

        chb_CA = new QCheckBox(groupBox_3);
        chb_CA->setObjectName(QString::fromUtf8("chb_CA"));

        gridLayout_3->addWidget(chb_CA, 1, 2, 1, 1);

        chb_ABC = new QCheckBox(groupBox_3);
        chb_ABC->setObjectName(QString::fromUtf8("chb_ABC"));

        gridLayout_3->addWidget(chb_ABC, 1, 3, 1, 2);

        chb_IaIbIc = new QCheckBox(groupBox_3);
        chb_IaIbIc->setObjectName(QString::fromUtf8("chb_IaIbIc"));

        gridLayout_3->addWidget(chb_IaIbIc, 2, 0, 1, 1);

        chb_3I0 = new QCheckBox(groupBox_3);
        chb_3I0->setObjectName(QString::fromUtf8("chb_3I0"));

        gridLayout_3->addWidget(chb_3I0, 2, 1, 1, 1);

        chb_I2 = new QCheckBox(groupBox_3);
        chb_I2->setObjectName(QString::fromUtf8("chb_I2"));

        gridLayout_3->addWidget(chb_I2, 2, 2, 1, 1);

        chb_A = new QCheckBox(groupBox_3);
        chb_A->setObjectName(QString::fromUtf8("chb_A"));

        gridLayout_3->addWidget(chb_A, 2, 3, 1, 1);

        chb_B = new QCheckBox(groupBox_3);
        chb_B->setObjectName(QString::fromUtf8("chb_B"));

        gridLayout_3->addWidget(chb_B, 2, 4, 1, 1);

        chb_C = new QCheckBox(groupBox_3);
        chb_C->setObjectName(QString::fromUtf8("chb_C"));

        gridLayout_3->addWidget(chb_C, 2, 5, 1, 1);


        gridLayout_5->addWidget(groupBox_3, 1, 0, 1, 2);

        groupBox_4 = new QGroupBox(QCurrInverAddMultDlg);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_labRelErr = new QLabel(groupBox_4);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));

        gridLayout_4->addWidget(m_labRelErr, 0, 2, 1, 1);

        m_lineRelErr = new QSettingLineEdit(groupBox_4);
        m_lineRelErr->setObjectName(QString::fromUtf8("m_lineRelErr"));

        gridLayout_4->addWidget(m_lineRelErr, 0, 3, 1, 1);

        m_labErrorLogic = new QLabel(groupBox_4);
        m_labErrorLogic->setObjectName(QString::fromUtf8("m_labErrorLogic"));

        gridLayout_4->addWidget(m_labErrorLogic, 0, 0, 1, 1);

        m_linePlus = new QSettingLineEdit(groupBox_4);
        m_linePlus->setObjectName(QString::fromUtf8("m_linePlus"));

        gridLayout_4->addWidget(m_linePlus, 1, 1, 1, 1);

        m_lineMinus = new QSettingLineEdit(groupBox_4);
        m_lineMinus->setObjectName(QString::fromUtf8("m_lineMinus"));

        gridLayout_4->addWidget(m_lineMinus, 1, 3, 1, 1);

        m_cmbErrorLogic = new QComboBox(groupBox_4);
        m_cmbErrorLogic->setObjectName(QString::fromUtf8("m_cmbErrorLogic"));

        gridLayout_4->addWidget(m_cmbErrorLogic, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labAbsErr_2 = new QLabel(groupBox_4);
        m_labAbsErr_2->setObjectName(QString::fromUtf8("m_labAbsErr_2"));

        horizontalLayout_2->addWidget(m_labAbsErr_2);

        m_labMinus = new QLabel(groupBox_4);
        m_labMinus->setObjectName(QString::fromUtf8("m_labMinus"));

        horizontalLayout_2->addWidget(m_labMinus);


        gridLayout_4->addLayout(horizontalLayout_2, 1, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labAbsErr = new QLabel(groupBox_4);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));

        horizontalLayout->addWidget(m_labAbsErr);

        m_labPlus = new QLabel(groupBox_4);
        m_labPlus->setObjectName(QString::fromUtf8("m_labPlus"));

        horizontalLayout->addWidget(m_labPlus);


        gridLayout_4->addLayout(horizontalLayout, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 2, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);

        pbn_Ok = new QPushButton(QCurrInverAddMultDlg);
        pbn_Ok->setObjectName(QString::fromUtf8("pbn_Ok"));

        horizontalLayout_3->addWidget(pbn_Ok);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_11);

        pbn_Cancel = new QPushButton(QCurrInverAddMultDlg);
        pbn_Cancel->setObjectName(QString::fromUtf8("pbn_Cancel"));

        horizontalLayout_3->addWidget(pbn_Cancel);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);


        gridLayout_5->addLayout(horizontalLayout_3, 3, 0, 1, 2);


        retranslateUi(QCurrInverAddMultDlg);

        QMetaObject::connectSlotsByName(QCurrInverAddMultDlg);
    } // setupUi

    void retranslateUi(QDialog *QCurrInverAddMultDlg)
    {
        QCurrInverAddMultDlg->setWindowTitle(QApplication::translate("QCurrInverAddMultDlg", "\346\267\273\345\212\240\347\263\273\345\210\227", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QCurrInverAddMultDlg", "\346\225\205\351\232\234\346\200\201", 0, QApplication::UnicodeUTF8));
        m_labSelect->setText(QApplication::translate("QCurrInverAddMultDlg", "\345\217\230\351\207\217\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_labFaultVolt->setText(QApplication::translate("QCurrInverAddMultDlg", "\347\237\255\350\267\257\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFaultAngle->setText(QApplication::translate("QCurrInverAddMultDlg", "\347\233\270\344\275\215(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labHz->setText(QApplication::translate("QCurrInverAddMultDlg", "\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QCurrInverAddMultDlg", "\346\267\273\345\212\240\346\265\213\350\257\225\347\202\271", 0, QApplication::UnicodeUTF8));
        m_labChangeStart->setText(QApplication::translate("QCurrInverAddMultDlg", "\345\217\230\345\214\226\345\247\213\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labChangeFinal->setText(QApplication::translate("QCurrInverAddMultDlg", "\345\217\230\345\214\226\347\273\210\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labChangeStep->setText(QApplication::translate("QCurrInverAddMultDlg", "\345\217\230\345\214\226\346\255\245\351\225\277(A):", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("QCurrInverAddMultDlg", "\346\225\205\351\232\234\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        chb_AN->setText(QApplication::translate("QCurrInverAddMultDlg", "AN", 0, QApplication::UnicodeUTF8));
        chb_BN->setText(QApplication::translate("QCurrInverAddMultDlg", "BN", 0, QApplication::UnicodeUTF8));
        chb_CN->setText(QApplication::translate("QCurrInverAddMultDlg", "CN", 0, QApplication::UnicodeUTF8));
        chb_AB->setText(QApplication::translate("QCurrInverAddMultDlg", "AB", 0, QApplication::UnicodeUTF8));
        chb_BC->setText(QApplication::translate("QCurrInverAddMultDlg", "BC", 0, QApplication::UnicodeUTF8));
        chb_CA->setText(QApplication::translate("QCurrInverAddMultDlg", "CA", 0, QApplication::UnicodeUTF8));
        chb_ABC->setText(QApplication::translate("QCurrInverAddMultDlg", "ABC", 0, QApplication::UnicodeUTF8));
        chb_IaIbIc->setText(QApplication::translate("QCurrInverAddMultDlg", "Ia+Ib+Ic", 0, QApplication::UnicodeUTF8));
        chb_3I0->setText(QApplication::translate("QCurrInverAddMultDlg", "3I0", 0, QApplication::UnicodeUTF8));
        chb_I2->setText(QApplication::translate("QCurrInverAddMultDlg", "I2", 0, QApplication::UnicodeUTF8));
        chb_A->setText(QApplication::translate("QCurrInverAddMultDlg", "A", 0, QApplication::UnicodeUTF8));
        chb_B->setText(QApplication::translate("QCurrInverAddMultDlg", "B", 0, QApplication::UnicodeUTF8));
        chb_C->setText(QApplication::translate("QCurrInverAddMultDlg", "C", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("QCurrInverAddMultDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QCurrInverAddMultDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_labErrorLogic->setText(QApplication::translate("QCurrInverAddMultDlg", "\350\257\257\345\267\256\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labAbsErr_2->setText(QApplication::translate("QCurrInverAddMultDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s):", 0, QApplication::UnicodeUTF8));
        m_labMinus->setText(QApplication::translate("QCurrInverAddMultDlg", "-", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QCurrInverAddMultDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s):", 0, QApplication::UnicodeUTF8));
        m_labPlus->setText(QApplication::translate("QCurrInverAddMultDlg", "+", 0, QApplication::UnicodeUTF8));
        pbn_Ok->setText(QApplication::translate("QCurrInverAddMultDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pbn_Cancel->setText(QApplication::translate("QCurrInverAddMultDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCurrInverAddMultDlg: public Ui_QCurrInverAddMultDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CURRINVERADDMULTDLG_H
