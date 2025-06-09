/********************************************************************************
** Form generated from reading UI file 'DistanceResultEstimateDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCERESULTESTIMATEDLG_H
#define UI_DISTANCERESULTESTIMATEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDistanceResultEstimateDlg
{
public:
    QGridLayout *gridLayout;
    QLabel *m_labName;
    QLabel *m_labType_2;
    QLabel *m_labRel;
    QLabel *m_labAbs;
    QLabel *m_labAbs_2;
    QLabel *m_lab1;
    CExBaseListComboBox *m_cmb1;
    QSettingLineEdit *m_txtRel1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labPlus_1;
    QSettingLineEdit *m_txtPlus_1;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_labMinus_1;
    QSettingLineEdit *m_txtMinus_1;
    QLabel *m_lab2;
    CExBaseListComboBox *m_cmb2;
    QSettingLineEdit *m_txtRel2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labPlus_2;
    QSettingLineEdit *m_txtPlus_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *m_labMinus_2;
    QSettingLineEdit *m_txtMinus_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *m_lab3;
    CExBaseListComboBox *m_cmb3;
    QSettingLineEdit *m_txtRel3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labPlus_3;
    QSettingLineEdit *m_txtPlus_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_labMinus_3;
    QSettingLineEdit *m_txtMinus_3;
    QLabel *m_lab4;
    CExBaseListComboBox *m_cmb4;
    QSettingLineEdit *m_txtRel4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labPlus_4;
    QSettingLineEdit *m_txtPlus_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *m_labMinus_4;
    QSettingLineEdit *m_txtMinus_4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *m_lab5;
    CExBaseListComboBox *m_cmb5;
    QSettingLineEdit *m_txtRel5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labPlus_5;
    QSettingLineEdit *m_txtPlus_5;
    QHBoxLayout *horizontalLayout_11;
    QLabel *m_labMinus_5;
    QSettingLineEdit *m_txtMinus_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_btnOK;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *QDistanceResultEstimateDlg)
    {
        if (QDistanceResultEstimateDlg->objectName().isEmpty())
            QDistanceResultEstimateDlg->setObjectName(QString::fromUtf8("QDistanceResultEstimateDlg"));
        QDistanceResultEstimateDlg->resize(876, 208);
        gridLayout = new QGridLayout(QDistanceResultEstimateDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labName = new QLabel(QDistanceResultEstimateDlg);
        m_labName->setObjectName(QString::fromUtf8("m_labName"));
        m_labName->setMaximumSize(QSize(16777215, 30));
        m_labName->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_labName, 0, 1, 1, 1);

        m_labType_2 = new QLabel(QDistanceResultEstimateDlg);
        m_labType_2->setObjectName(QString::fromUtf8("m_labType_2"));
        m_labType_2->setMaximumSize(QSize(16777215, 30));
        m_labType_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_labType_2, 0, 2, 1, 1);

        m_labRel = new QLabel(QDistanceResultEstimateDlg);
        m_labRel->setObjectName(QString::fromUtf8("m_labRel"));
        m_labRel->setMaximumSize(QSize(16777215, 30));
        m_labRel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_labRel, 0, 3, 1, 1);

        m_labAbs = new QLabel(QDistanceResultEstimateDlg);
        m_labAbs->setObjectName(QString::fromUtf8("m_labAbs"));
        m_labAbs->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_labAbs, 0, 4, 1, 1);

        m_labAbs_2 = new QLabel(QDistanceResultEstimateDlg);
        m_labAbs_2->setObjectName(QString::fromUtf8("m_labAbs_2"));
        m_labAbs_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_labAbs_2, 0, 5, 1, 1);

        m_lab1 = new QLabel(QDistanceResultEstimateDlg);
        m_lab1->setObjectName(QString::fromUtf8("m_lab1"));
        m_lab1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lab1, 1, 1, 1, 1);

        m_cmb1 = new CExBaseListComboBox(QDistanceResultEstimateDlg);
        m_cmb1->setObjectName(QString::fromUtf8("m_cmb1"));
        m_cmb1->setMinimumSize(QSize(170, 0));
        m_cmb1->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_cmb1, 1, 2, 1, 1);

        m_txtRel1 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtRel1->setObjectName(QString::fromUtf8("m_txtRel1"));
        m_txtRel1->setMinimumSize(QSize(170, 0));
        m_txtRel1->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_txtRel1, 1, 3, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_labPlus_1 = new QLabel(QDistanceResultEstimateDlg);
        m_labPlus_1->setObjectName(QString::fromUtf8("m_labPlus_1"));

        horizontalLayout_3->addWidget(m_labPlus_1);

        m_txtPlus_1 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtPlus_1->setObjectName(QString::fromUtf8("m_txtPlus_1"));
        m_txtPlus_1->setMinimumSize(QSize(170, 0));
        m_txtPlus_1->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_txtPlus_1);


        gridLayout->addLayout(horizontalLayout_3, 1, 4, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_labMinus_1 = new QLabel(QDistanceResultEstimateDlg);
        m_labMinus_1->setObjectName(QString::fromUtf8("m_labMinus_1"));

        horizontalLayout_7->addWidget(m_labMinus_1);

        m_txtMinus_1 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtMinus_1->setObjectName(QString::fromUtf8("m_txtMinus_1"));
        m_txtMinus_1->setMinimumSize(QSize(170, 0));
        m_txtMinus_1->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_7->addWidget(m_txtMinus_1);


        gridLayout->addLayout(horizontalLayout_7, 1, 5, 1, 1);

        m_lab2 = new QLabel(QDistanceResultEstimateDlg);
        m_lab2->setObjectName(QString::fromUtf8("m_lab2"));
        m_lab2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lab2, 2, 1, 1, 1);

        m_cmb2 = new CExBaseListComboBox(QDistanceResultEstimateDlg);
        m_cmb2->setObjectName(QString::fromUtf8("m_cmb2"));
        m_cmb2->setMinimumSize(QSize(170, 0));
        m_cmb2->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_cmb2, 2, 2, 1, 1);

        m_txtRel2 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtRel2->setObjectName(QString::fromUtf8("m_txtRel2"));
        m_txtRel2->setMinimumSize(QSize(170, 0));
        m_txtRel2->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_txtRel2, 2, 3, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labPlus_2 = new QLabel(QDistanceResultEstimateDlg);
        m_labPlus_2->setObjectName(QString::fromUtf8("m_labPlus_2"));

        horizontalLayout_2->addWidget(m_labPlus_2);

        m_txtPlus_2 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtPlus_2->setObjectName(QString::fromUtf8("m_txtPlus_2"));
        m_txtPlus_2->setMinimumSize(QSize(170, 0));
        m_txtPlus_2->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_txtPlus_2);


        gridLayout->addLayout(horizontalLayout_2, 2, 4, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        m_labMinus_2 = new QLabel(QDistanceResultEstimateDlg);
        m_labMinus_2->setObjectName(QString::fromUtf8("m_labMinus_2"));

        horizontalLayout_8->addWidget(m_labMinus_2);

        m_txtMinus_2 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtMinus_2->setObjectName(QString::fromUtf8("m_txtMinus_2"));
        m_txtMinus_2->setMinimumSize(QSize(170, 0));
        m_txtMinus_2->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_8->addWidget(m_txtMinus_2);


        gridLayout->addLayout(horizontalLayout_8, 2, 5, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 0, 1, 1);

        m_lab3 = new QLabel(QDistanceResultEstimateDlg);
        m_lab3->setObjectName(QString::fromUtf8("m_lab3"));
        m_lab3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lab3, 3, 1, 1, 1);

        m_cmb3 = new CExBaseListComboBox(QDistanceResultEstimateDlg);
        m_cmb3->setObjectName(QString::fromUtf8("m_cmb3"));
        m_cmb3->setMinimumSize(QSize(170, 0));
        m_cmb3->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_cmb3, 3, 2, 1, 1);

        m_txtRel3 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtRel3->setObjectName(QString::fromUtf8("m_txtRel3"));
        m_txtRel3->setMinimumSize(QSize(170, 0));
        m_txtRel3->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_txtRel3, 3, 3, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_labPlus_3 = new QLabel(QDistanceResultEstimateDlg);
        m_labPlus_3->setObjectName(QString::fromUtf8("m_labPlus_3"));

        horizontalLayout_5->addWidget(m_labPlus_3);

        m_txtPlus_3 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtPlus_3->setObjectName(QString::fromUtf8("m_txtPlus_3"));
        m_txtPlus_3->setMinimumSize(QSize(170, 0));
        m_txtPlus_3->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_txtPlus_3);


        gridLayout->addLayout(horizontalLayout_5, 3, 4, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        m_labMinus_3 = new QLabel(QDistanceResultEstimateDlg);
        m_labMinus_3->setObjectName(QString::fromUtf8("m_labMinus_3"));

        horizontalLayout_9->addWidget(m_labMinus_3);

        m_txtMinus_3 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtMinus_3->setObjectName(QString::fromUtf8("m_txtMinus_3"));
        m_txtMinus_3->setMinimumSize(QSize(170, 0));
        m_txtMinus_3->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_9->addWidget(m_txtMinus_3);


        gridLayout->addLayout(horizontalLayout_9, 3, 5, 1, 1);

        m_lab4 = new QLabel(QDistanceResultEstimateDlg);
        m_lab4->setObjectName(QString::fromUtf8("m_lab4"));
        m_lab4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lab4, 4, 1, 1, 1);

        m_cmb4 = new CExBaseListComboBox(QDistanceResultEstimateDlg);
        m_cmb4->setObjectName(QString::fromUtf8("m_cmb4"));
        m_cmb4->setMinimumSize(QSize(170, 0));
        m_cmb4->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_cmb4, 4, 2, 1, 1);

        m_txtRel4 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtRel4->setObjectName(QString::fromUtf8("m_txtRel4"));
        m_txtRel4->setMinimumSize(QSize(170, 0));
        m_txtRel4->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_txtRel4, 4, 3, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_labPlus_4 = new QLabel(QDistanceResultEstimateDlg);
        m_labPlus_4->setObjectName(QString::fromUtf8("m_labPlus_4"));

        horizontalLayout_4->addWidget(m_labPlus_4);

        m_txtPlus_4 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtPlus_4->setObjectName(QString::fromUtf8("m_txtPlus_4"));
        m_txtPlus_4->setMinimumSize(QSize(170, 0));
        m_txtPlus_4->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_txtPlus_4);


        gridLayout->addLayout(horizontalLayout_4, 4, 4, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        m_labMinus_4 = new QLabel(QDistanceResultEstimateDlg);
        m_labMinus_4->setObjectName(QString::fromUtf8("m_labMinus_4"));

        horizontalLayout_10->addWidget(m_labMinus_4);

        m_txtMinus_4 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtMinus_4->setObjectName(QString::fromUtf8("m_txtMinus_4"));
        m_txtMinus_4->setMinimumSize(QSize(170, 0));
        m_txtMinus_4->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_10->addWidget(m_txtMinus_4);


        gridLayout->addLayout(horizontalLayout_10, 4, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 4, 6, 1, 1);

        m_lab5 = new QLabel(QDistanceResultEstimateDlg);
        m_lab5->setObjectName(QString::fromUtf8("m_lab5"));
        m_lab5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lab5, 5, 1, 1, 1);

        m_cmb5 = new CExBaseListComboBox(QDistanceResultEstimateDlg);
        m_cmb5->setObjectName(QString::fromUtf8("m_cmb5"));
        m_cmb5->setMinimumSize(QSize(170, 0));
        m_cmb5->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_cmb5, 5, 2, 1, 1);

        m_txtRel5 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtRel5->setObjectName(QString::fromUtf8("m_txtRel5"));
        m_txtRel5->setMinimumSize(QSize(170, 0));
        m_txtRel5->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(m_txtRel5, 5, 3, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labPlus_5 = new QLabel(QDistanceResultEstimateDlg);
        m_labPlus_5->setObjectName(QString::fromUtf8("m_labPlus_5"));

        horizontalLayout_6->addWidget(m_labPlus_5);

        m_txtPlus_5 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtPlus_5->setObjectName(QString::fromUtf8("m_txtPlus_5"));
        m_txtPlus_5->setMinimumSize(QSize(170, 0));
        m_txtPlus_5->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_txtPlus_5);


        gridLayout->addLayout(horizontalLayout_6, 5, 4, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        m_labMinus_5 = new QLabel(QDistanceResultEstimateDlg);
        m_labMinus_5->setObjectName(QString::fromUtf8("m_labMinus_5"));

        horizontalLayout_11->addWidget(m_labMinus_5);

        m_txtMinus_5 = new QSettingLineEdit(QDistanceResultEstimateDlg);
        m_txtMinus_5->setObjectName(QString::fromUtf8("m_txtMinus_5"));
        m_txtMinus_5->setMinimumSize(QSize(170, 0));
        m_txtMinus_5->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_11->addWidget(m_txtMinus_5);


        gridLayout->addLayout(horizontalLayout_11, 5, 5, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        m_btnOK = new QPushButton(QDistanceResultEstimateDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnCancel = new QPushButton(QDistanceResultEstimateDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 6, 1, 1, 5);


        retranslateUi(QDistanceResultEstimateDlg);

        QMetaObject::connectSlotsByName(QDistanceResultEstimateDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceResultEstimateDlg)
    {
        QDistanceResultEstimateDlg->setWindowTitle(QApplication::translate("QDistanceResultEstimateDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        m_labName->setText(QApplication::translate("QDistanceResultEstimateDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_labType_2->setText(QApplication::translate("QDistanceResultEstimateDlg", "\350\257\257\345\267\256\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        m_labRel->setText(QApplication::translate("QDistanceResultEstimateDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(%)", 0, QApplication::UnicodeUTF8));
        m_labAbs->setText(QApplication::translate("QDistanceResultEstimateDlg", "\347\273\235\345\257\271\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        m_labAbs_2->setText(QApplication::translate("QDistanceResultEstimateDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(-)", 0, QApplication::UnicodeUTF8));
        m_lab1->setText(QApplication::translate("QDistanceResultEstimateDlg", "\350\267\235\347\246\273I\346\256\265\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_labPlus_1->setText(QApplication::translate("QDistanceResultEstimateDlg", "+", 0, QApplication::UnicodeUTF8));
        m_labMinus_1->setText(QApplication::translate("QDistanceResultEstimateDlg", "-", 0, QApplication::UnicodeUTF8));
        m_lab2->setText(QApplication::translate("QDistanceResultEstimateDlg", "\350\267\235\347\246\273\342\205\241\346\256\265\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_labPlus_2->setText(QApplication::translate("QDistanceResultEstimateDlg", "+", 0, QApplication::UnicodeUTF8));
        m_labMinus_2->setText(QApplication::translate("QDistanceResultEstimateDlg", "-", 0, QApplication::UnicodeUTF8));
        m_lab3->setText(QApplication::translate("QDistanceResultEstimateDlg", "\350\267\235\347\246\273\342\205\242\346\256\265\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_labPlus_3->setText(QApplication::translate("QDistanceResultEstimateDlg", "+", 0, QApplication::UnicodeUTF8));
        m_labMinus_3->setText(QApplication::translate("QDistanceResultEstimateDlg", "-", 0, QApplication::UnicodeUTF8));
        m_lab4->setText(QApplication::translate("QDistanceResultEstimateDlg", "\350\267\235\347\246\273IV\346\256\265\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_labPlus_4->setText(QApplication::translate("QDistanceResultEstimateDlg", "+", 0, QApplication::UnicodeUTF8));
        m_labMinus_4->setText(QApplication::translate("QDistanceResultEstimateDlg", "-", 0, QApplication::UnicodeUTF8));
        m_lab5->setText(QApplication::translate("QDistanceResultEstimateDlg", "\350\267\235\347\246\273V\346\256\265\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_labPlus_5->setText(QApplication::translate("QDistanceResultEstimateDlg", "+", 0, QApplication::UnicodeUTF8));
        m_labMinus_5->setText(QApplication::translate("QDistanceResultEstimateDlg", "-", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QDistanceResultEstimateDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDistanceResultEstimateDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceResultEstimateDlg: public Ui_QDistanceResultEstimateDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCERESULTESTIMATEDLG_H
