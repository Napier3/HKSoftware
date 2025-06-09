/********************************************************************************
** Form generated from reading UI file 'DiffResultEstimateDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFRESULTESTIMATEDLG_H
#define UI_DIFFRESULTESTIMATEDLG_H

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
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDiffResultEstimateDlg
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labPlus_2;
    QSettingLineEdit *m_txtPlus_2;
    QLabel *m_labMinus_2;
    QSettingLineEdit *m_txtMinus_2;
    QHBoxLayout *horizontalLayout_1;
    QSettingLineEdit *m_txtPlus_1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labPlus_3;
    QSettingLineEdit *m_txtPlus_3;
    QLabel *m_labMinus_3;
    QSettingLineEdit *m_txtMinus_3;
    QSettingLineEdit *m_txtRel1;
    QLabel *m_labAbs;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;
    QLabel *m_labRel;
    QSettingLineEdit *m_txtRel2;
    QLabel *m_labType;
    QLineEdit *m_txtRel3;
    QComboBox *m_cmb1;
    QLabel *m_lab2;
    QComboBox *m_cmb2;
    QComboBox *m_cmb3;
    QLabel *m_lab3;
    QLabel *m_lab1;
    QLabel *m_labName;

    void setupUi(QDialog *QDiffResultEstimateDlg)
    {
        if (QDiffResultEstimateDlg->objectName().isEmpty())
            QDiffResultEstimateDlg->setObjectName(QString::fromUtf8("QDiffResultEstimateDlg"));
        QDiffResultEstimateDlg->resize(733, 209);
        gridLayout = new QGridLayout(QDiffResultEstimateDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labPlus_2 = new QLabel(QDiffResultEstimateDlg);
        m_labPlus_2->setObjectName(QString::fromUtf8("m_labPlus_2"));

        horizontalLayout_2->addWidget(m_labPlus_2);

        m_txtPlus_2 = new QSettingLineEdit(QDiffResultEstimateDlg);
        m_txtPlus_2->setObjectName(QString::fromUtf8("m_txtPlus_2"));
        m_txtPlus_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(m_txtPlus_2);

        m_labMinus_2 = new QLabel(QDiffResultEstimateDlg);
        m_labMinus_2->setObjectName(QString::fromUtf8("m_labMinus_2"));

        horizontalLayout_2->addWidget(m_labMinus_2);

        m_txtMinus_2 = new QSettingLineEdit(QDiffResultEstimateDlg);
        m_txtMinus_2->setObjectName(QString::fromUtf8("m_txtMinus_2"));
        m_txtMinus_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(m_txtMinus_2);


        gridLayout->addLayout(horizontalLayout_2, 4, 3, 1, 1);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        m_txtPlus_1 = new QSettingLineEdit(QDiffResultEstimateDlg);
        m_txtPlus_1->setObjectName(QString::fromUtf8("m_txtPlus_1"));
        m_txtPlus_1->setAlignment(Qt::AlignCenter);

        horizontalLayout_1->addWidget(m_txtPlus_1);


        gridLayout->addLayout(horizontalLayout_1, 3, 3, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_labPlus_3 = new QLabel(QDiffResultEstimateDlg);
        m_labPlus_3->setObjectName(QString::fromUtf8("m_labPlus_3"));

        horizontalLayout_5->addWidget(m_labPlus_3);

        m_txtPlus_3 = new QSettingLineEdit(QDiffResultEstimateDlg);
        m_txtPlus_3->setObjectName(QString::fromUtf8("m_txtPlus_3"));
        m_txtPlus_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(m_txtPlus_3);

        m_labMinus_3 = new QLabel(QDiffResultEstimateDlg);
        m_labMinus_3->setObjectName(QString::fromUtf8("m_labMinus_3"));

        horizontalLayout_5->addWidget(m_labMinus_3);

        m_txtMinus_3 = new QSettingLineEdit(QDiffResultEstimateDlg);
        m_txtMinus_3->setObjectName(QString::fromUtf8("m_txtMinus_3"));
        m_txtMinus_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(m_txtMinus_3);


        gridLayout->addLayout(horizontalLayout_5, 5, 3, 1, 1);

        m_txtRel1 = new QSettingLineEdit(QDiffResultEstimateDlg);
        m_txtRel1->setObjectName(QString::fromUtf8("m_txtRel1"));
        m_txtRel1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_txtRel1, 3, 2, 1, 1);

        m_labAbs = new QLabel(QDiffResultEstimateDlg);
        m_labAbs->setObjectName(QString::fromUtf8("m_labAbs"));
        m_labAbs->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_labAbs, 1, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btnOK = new QPushButton(QDiffResultEstimateDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QDiffResultEstimateDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);


        gridLayout->addLayout(horizontalLayout, 6, 2, 1, 1);

        m_labRel = new QLabel(QDiffResultEstimateDlg);
        m_labRel->setObjectName(QString::fromUtf8("m_labRel"));
        m_labRel->setMaximumSize(QSize(16777215, 30));
        m_labRel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_labRel, 1, 2, 1, 1);

        m_txtRel2 = new QSettingLineEdit(QDiffResultEstimateDlg);
        m_txtRel2->setObjectName(QString::fromUtf8("m_txtRel2"));
        m_txtRel2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_txtRel2, 4, 2, 1, 1);

        m_labType = new QLabel(QDiffResultEstimateDlg);
        m_labType->setObjectName(QString::fromUtf8("m_labType"));
        m_labType->setMaximumSize(QSize(16777215, 30));
        m_labType->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_labType, 1, 1, 1, 1);

        m_txtRel3 = new QLineEdit(QDiffResultEstimateDlg);
        m_txtRel3->setObjectName(QString::fromUtf8("m_txtRel3"));
        m_txtRel3->setEnabled(false);
        m_txtRel3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_txtRel3, 5, 2, 1, 1);

        m_cmb1 = new QComboBox(QDiffResultEstimateDlg);
        m_cmb1->setObjectName(QString::fromUtf8("m_cmb1"));
        m_cmb1->setMinimumSize(QSize(140, 0));

        gridLayout->addWidget(m_cmb1, 3, 1, 1, 1);

        m_lab2 = new QLabel(QDiffResultEstimateDlg);
        m_lab2->setObjectName(QString::fromUtf8("m_lab2"));
        m_lab2->setMinimumSize(QSize(150, 0));
        m_lab2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lab2, 4, 0, 1, 1);

        m_cmb2 = new QComboBox(QDiffResultEstimateDlg);
        m_cmb2->setObjectName(QString::fromUtf8("m_cmb2"));
        m_cmb2->setMinimumSize(QSize(140, 0));

        gridLayout->addWidget(m_cmb2, 4, 1, 1, 1);

        m_cmb3 = new QComboBox(QDiffResultEstimateDlg);
        m_cmb3->setObjectName(QString::fromUtf8("m_cmb3"));
        m_cmb3->setEnabled(false);
        m_cmb3->setMinimumSize(QSize(140, 0));
        m_cmb3->setEditable(false);

        gridLayout->addWidget(m_cmb3, 5, 1, 1, 1);

        m_lab3 = new QLabel(QDiffResultEstimateDlg);
        m_lab3->setObjectName(QString::fromUtf8("m_lab3"));
        m_lab3->setMinimumSize(QSize(150, 0));
        m_lab3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lab3, 5, 0, 1, 1);

        m_lab1 = new QLabel(QDiffResultEstimateDlg);
        m_lab1->setObjectName(QString::fromUtf8("m_lab1"));
        m_lab1->setMinimumSize(QSize(150, 0));
        m_lab1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lab1, 3, 0, 1, 1);

        m_labName = new QLabel(QDiffResultEstimateDlg);
        m_labName->setObjectName(QString::fromUtf8("m_labName"));
        m_labName->setMinimumSize(QSize(0, 30));
        m_labName->setMaximumSize(QSize(16777215, 30));
        m_labName->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_labName, 1, 0, 1, 1);


        retranslateUi(QDiffResultEstimateDlg);

        QMetaObject::connectSlotsByName(QDiffResultEstimateDlg);
    } // setupUi

    void retranslateUi(QDialog *QDiffResultEstimateDlg)
    {
        QDiffResultEstimateDlg->setWindowTitle(QApplication::translate("QDiffResultEstimateDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_labPlus_2->setText(QApplication::translate("QDiffResultEstimateDlg", "+", 0, QApplication::UnicodeUTF8));
        m_labMinus_2->setText(QApplication::translate("QDiffResultEstimateDlg", "-", 0, QApplication::UnicodeUTF8));
        m_labPlus_3->setText(QApplication::translate("QDiffResultEstimateDlg", "+", 0, QApplication::UnicodeUTF8));
        m_labMinus_3->setText(QApplication::translate("QDiffResultEstimateDlg", "-", 0, QApplication::UnicodeUTF8));
        m_labAbs->setText(QApplication::translate("QDiffResultEstimateDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s)", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QDiffResultEstimateDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDiffResultEstimateDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        m_labRel->setText(QApplication::translate("QDiffResultEstimateDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(%)", 0, QApplication::UnicodeUTF8));
        m_labType->setText(QApplication::translate("QDiffResultEstimateDlg", "\350\257\257\345\267\256\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        m_lab2->setText(QApplication::translate("QDiffResultEstimateDlg", "\350\260\220\346\263\242\345\210\266\345\212\250\346\220\234\347\264\242\345\200\274(%)", 0, QApplication::UnicodeUTF8));
        m_lab3->setText(QApplication::translate("QDiffResultEstimateDlg", "\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_lab1->setText(QApplication::translate("QDiffResultEstimateDlg", "\345\267\256\345\212\250\346\220\234\347\264\242\345\200\274(A/le)", 0, QApplication::UnicodeUTF8));
        m_labName->setText(QApplication::translate("QDiffResultEstimateDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDiffResultEstimateDlg: public Ui_QDiffResultEstimateDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFRESULTESTIMATEDLG_H
