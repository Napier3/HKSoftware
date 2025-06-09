/********************************************************************************
** Form generated from reading UI file 'DiffCBOpResultEstimateDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFCBOPRESULTESTIMATEDLG_H
#define UI_DIFFCBOPRESULTESTIMATEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_DiffCBOpResultEstimateDlg
{
public:
    QVBoxLayout *verticalLayout_13;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_7;
    QLabel *m_labName;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout;
    QLabel *m_labSetting;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_10;
    QLabel *m_labType;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_12;
    QLabel *m_labRel;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *m_labAbs;
    QGroupBox *groupBox_11;
    QVBoxLayout *verticalLayout_5;
    QLabel *m_labAbs_2;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_8;
    QLabel *m_labActionTime;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_2;
    QSettingLineEdit *m_EditSetting;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_9;
    QComboBox *m_cmbFluatType;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_11;
    QSettingLineEdit *m_txtRel3;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_4;
    QSettingLineEdit *m_txtPlus_3;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_6;
    QSettingLineEdit *m_txtMinus_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOK;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *DiffCBOpResultEstimateDlg)
    {
        if (DiffCBOpResultEstimateDlg->objectName().isEmpty())
            DiffCBOpResultEstimateDlg->setObjectName(QString::fromUtf8("DiffCBOpResultEstimateDlg"));
        DiffCBOpResultEstimateDlg->resize(906, 152);
        verticalLayout_13 = new QVBoxLayout(DiffCBOpResultEstimateDlg);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_7 = new QVBoxLayout(groupBox);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        m_labName = new QLabel(groupBox);
        m_labName->setObjectName(QString::fromUtf8("m_labName"));
        m_labName->setMinimumSize(QSize(0, 0));
        m_labName->setMaximumSize(QSize(16777215, 30));
        m_labName->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(m_labName);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_10 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        verticalLayout = new QVBoxLayout(groupBox_10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_labSetting = new QLabel(groupBox_10);
        m_labSetting->setObjectName(QString::fromUtf8("m_labSetting"));
        m_labSetting->setMaximumSize(QSize(16777215, 30));
        m_labSetting->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_labSetting);


        gridLayout->addWidget(groupBox_10, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_10 = new QVBoxLayout(groupBox_2);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        m_labType = new QLabel(groupBox_2);
        m_labType->setObjectName(QString::fromUtf8("m_labType"));
        m_labType->setMaximumSize(QSize(16777215, 30));
        m_labType->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(m_labType);


        gridLayout->addWidget(groupBox_2, 0, 2, 1, 1);

        groupBox_3 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_12 = new QVBoxLayout(groupBox_3);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        m_labRel = new QLabel(groupBox_3);
        m_labRel->setObjectName(QString::fromUtf8("m_labRel"));
        m_labRel->setMaximumSize(QSize(16777215, 30));
        m_labRel->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(m_labRel);


        gridLayout->addWidget(groupBox_3, 0, 3, 1, 1);

        groupBox_4 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_labAbs = new QLabel(groupBox_4);
        m_labAbs->setObjectName(QString::fromUtf8("m_labAbs"));
        m_labAbs->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(m_labAbs);


        gridLayout->addWidget(groupBox_4, 0, 4, 1, 1);

        groupBox_11 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        verticalLayout_5 = new QVBoxLayout(groupBox_11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        m_labAbs_2 = new QLabel(groupBox_11);
        m_labAbs_2->setObjectName(QString::fromUtf8("m_labAbs_2"));
        m_labAbs_2->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(m_labAbs_2);


        gridLayout->addWidget(groupBox_11, 0, 5, 1, 1);

        groupBox_5 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setAlignment(Qt::AlignCenter);
        verticalLayout_8 = new QVBoxLayout(groupBox_5);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        m_labActionTime = new QLabel(groupBox_5);
        m_labActionTime->setObjectName(QString::fromUtf8("m_labActionTime"));
        m_labActionTime->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(m_labActionTime);


        gridLayout->addWidget(groupBox_5, 1, 0, 1, 1);

        groupBox_9 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox_9);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_EditSetting = new QSettingLineEdit(groupBox_9);
        m_EditSetting->setObjectName(QString::fromUtf8("m_EditSetting"));
        m_EditSetting->setEnabled(true);
        m_EditSetting->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(m_EditSetting);


        gridLayout->addWidget(groupBox_9, 1, 1, 1, 1);

        groupBox_7 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setAlignment(Qt::AlignCenter);
        verticalLayout_9 = new QVBoxLayout(groupBox_7);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        m_cmbFluatType = new QComboBox(groupBox_7);
        m_cmbFluatType->setObjectName(QString::fromUtf8("m_cmbFluatType"));
        m_cmbFluatType->setEnabled(true);
        m_cmbFluatType->setMinimumSize(QSize(140, 0));
        m_cmbFluatType->setEditable(false);

        verticalLayout_9->addWidget(m_cmbFluatType);


        gridLayout->addWidget(groupBox_7, 1, 2, 1, 1);

        groupBox_8 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setAlignment(Qt::AlignCenter);
        verticalLayout_11 = new QVBoxLayout(groupBox_8);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        m_txtRel3 = new QSettingLineEdit(groupBox_8);
        m_txtRel3->setObjectName(QString::fromUtf8("m_txtRel3"));
        m_txtRel3->setEnabled(true);
        m_txtRel3->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(m_txtRel3);


        gridLayout->addWidget(groupBox_8, 1, 3, 1, 1);

        groupBox_6 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setAlignment(Qt::AlignCenter);
        verticalLayout_4 = new QVBoxLayout(groupBox_6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        m_txtPlus_3 = new QSettingLineEdit(groupBox_6);
        m_txtPlus_3->setObjectName(QString::fromUtf8("m_txtPlus_3"));
        m_txtPlus_3->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(m_txtPlus_3);


        gridLayout->addWidget(groupBox_6, 1, 4, 1, 1);

        groupBox_12 = new QGroupBox(DiffCBOpResultEstimateDlg);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        groupBox_12->setAlignment(Qt::AlignCenter);
        verticalLayout_6 = new QVBoxLayout(groupBox_12);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        m_txtMinus_3 = new QSettingLineEdit(groupBox_12);
        m_txtMinus_3->setObjectName(QString::fromUtf8("m_txtMinus_3"));
        m_txtMinus_3->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(m_txtMinus_3);


        gridLayout->addWidget(groupBox_12, 1, 5, 1, 1);


        verticalLayout_13->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnOK = new QPushButton(DiffCBOpResultEstimateDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        m_btnCancel = new QPushButton(DiffCBOpResultEstimateDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_13->addLayout(horizontalLayout);


        retranslateUi(DiffCBOpResultEstimateDlg);

        QMetaObject::connectSlotsByName(DiffCBOpResultEstimateDlg);
    } // setupUi

    void retranslateUi(QDialog *DiffCBOpResultEstimateDlg)
    {
        DiffCBOpResultEstimateDlg->setWindowTitle(QApplication::translate("DiffCBOpResultEstimateDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        m_labName->setText(QApplication::translate("DiffCBOpResultEstimateDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QString());
        m_labSetting->setText(QApplication::translate("DiffCBOpResultEstimateDlg", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        m_labType->setText(QApplication::translate("DiffCBOpResultEstimateDlg", "\350\257\257\345\267\256\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        m_labRel->setText(QApplication::translate("DiffCBOpResultEstimateDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(%)", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QString());
        m_labAbs->setText(QApplication::translate("DiffCBOpResultEstimateDlg", "\347\273\235\345\257\271\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QString());
        m_labAbs_2->setText(QApplication::translate("DiffCBOpResultEstimateDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(-)", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QString());
        m_labActionTime->setText(QApplication::translate("DiffCBOpResultEstimateDlg", "\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QString());
        m_EditSetting->setText(QString());
        groupBox_7->setTitle(QString());
        groupBox_8->setTitle(QString());
        m_txtRel3->setText(QString());
        groupBox_6->setTitle(QString());
        m_txtPlus_3->setText(QString());
        groupBox_12->setTitle(QString());
        m_txtMinus_3->setText(QString());
        m_btnOK->setText(QApplication::translate("DiffCBOpResultEstimateDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("DiffCBOpResultEstimateDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DiffCBOpResultEstimateDlg: public Ui_DiffCBOpResultEstimateDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFCBOPRESULTESTIMATEDLG_H
