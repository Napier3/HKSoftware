/********************************************************************************
** Form generated from reading UI file 'CharEditWidget_Diff.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAREDITWIDGET_DIFF_H
#define UI_CHAREDITWIDGET_DIFF_H

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
#include "../../Controls/SttCheckbox.h"
#include "../../Controls/SttLineEdit.h"
#include "../../Module/CommonCtrl_QT/QDataTypeComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QCharEditWidget_Diff
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *m_radioNormal;
    QRadioButton *m_radioHarm;
    QGridLayout *gridLayout;
    QDataTypeComboBox *m_cbSettingMinAxis;
    QLabel *m_lbSettingMinAxis;
    QLabel *m_lbInSel;
    QDataTypeComboBox *m_cbInSel;
    QLabel *m_lbInSet;
    QSttLineEdit *m_editInSet;
    QDataTypeComboBox *m_cbHarmIndex;
    QLabel *m_lbHarmIndex;
    QLabel *m_lbHarmCoef;
    QSttLineEdit *m_editHarmCoef;
    QVBoxLayout *m_layoutVert;
    QGridLayout *m_layGridParas;
    QSttLineEdit *m_edtSet_Istart;
    QSttLineEdit *m_edtSet_Kstart;
    QLabel *m_lblTitleStart;
    QLabel *m_lblTitleCurr;
    QLabel *m_lblTitleK;
    QSttCheckBox *m_chkLine1;
    QSttLineEdit *m_edtSet_Ip1;
    QLabel *m_lblTitleLine1;
    QSttLineEdit *m_edtSet_K1;
    QSttCheckBox *m_chkStart;
    QSttCheckBox *m_chkLine3;
    QSttCheckBox *m_chkLine2;
    QSttCheckBox *m_chkLineSd;
    QLabel *m_lblTitleLine2;
    QLabel *m_lblTitleLine3;
    QLabel *m_lblTitleLineSd;
    QSttLineEdit *m_edtSet_Ip2;
    QSttLineEdit *m_edtSet_Ip3;
    QSttLineEdit *m_edtSet_Isd;
    QSttLineEdit *m_edtSet_K2;
    QSttLineEdit *m_edtSet_K3;
    QLabel *m_lbName;
    QLabel *m_lbSetting;
    QHBoxLayout *m_layUser;
    QLabel *m_lbIdValue;
    QSttLineEdit *m_editSet_IdValue;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnUserAdd;
    QPushButton *m_btnUserClear;

    void setupUi(QWidget *QCharEditWidget_Diff)
    {
        if (QCharEditWidget_Diff->objectName().isEmpty())
            QCharEditWidget_Diff->setObjectName(QString::fromUtf8("QCharEditWidget_Diff"));
        QCharEditWidget_Diff->resize(553, 420);
        verticalLayout = new QVBoxLayout(QCharEditWidget_Diff);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_radioNormal = new QRadioButton(QCharEditWidget_Diff);
        m_radioNormal->setObjectName(QString::fromUtf8("m_radioNormal"));
        QFont font;
        font.setPointSize(16);
        m_radioNormal->setFont(font);
        m_radioNormal->setChecked(true);

        horizontalLayout->addWidget(m_radioNormal);

        m_radioHarm = new QRadioButton(QCharEditWidget_Diff);
        m_radioHarm->setObjectName(QString::fromUtf8("m_radioHarm"));
        m_radioHarm->setFont(font);

        horizontalLayout->addWidget(m_radioHarm);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_cbSettingMinAxis = new QDataTypeComboBox(QCharEditWidget_Diff);
        m_cbSettingMinAxis->setObjectName(QString::fromUtf8("m_cbSettingMinAxis"));

        gridLayout->addWidget(m_cbSettingMinAxis, 0, 1, 1, 1);

        m_lbSettingMinAxis = new QLabel(QCharEditWidget_Diff);
        m_lbSettingMinAxis->setObjectName(QString::fromUtf8("m_lbSettingMinAxis"));
        m_lbSettingMinAxis->setFont(font);

        gridLayout->addWidget(m_lbSettingMinAxis, 0, 0, 1, 1);

        m_lbInSel = new QLabel(QCharEditWidget_Diff);
        m_lbInSel->setObjectName(QString::fromUtf8("m_lbInSel"));
        m_lbInSel->setFont(font);

        gridLayout->addWidget(m_lbInSel, 0, 2, 1, 1);

        m_cbInSel = new QDataTypeComboBox(QCharEditWidget_Diff);
        m_cbInSel->setObjectName(QString::fromUtf8("m_cbInSel"));

        gridLayout->addWidget(m_cbInSel, 0, 3, 1, 1);

        m_lbInSet = new QLabel(QCharEditWidget_Diff);
        m_lbInSet->setObjectName(QString::fromUtf8("m_lbInSet"));
        m_lbInSet->setFont(font);

        gridLayout->addWidget(m_lbInSet, 1, 2, 1, 1);

        m_editInSet = new QSttLineEdit(QCharEditWidget_Diff);
        m_editInSet->setObjectName(QString::fromUtf8("m_editInSet"));

        gridLayout->addWidget(m_editInSet, 1, 3, 1, 1);

        m_cbHarmIndex = new QDataTypeComboBox(QCharEditWidget_Diff);
        m_cbHarmIndex->setObjectName(QString::fromUtf8("m_cbHarmIndex"));
        m_cbHarmIndex->setFont(font);

        gridLayout->addWidget(m_cbHarmIndex, 2, 1, 1, 1);

        m_lbHarmIndex = new QLabel(QCharEditWidget_Diff);
        m_lbHarmIndex->setObjectName(QString::fromUtf8("m_lbHarmIndex"));
        m_lbHarmIndex->setFont(font);
        m_lbHarmIndex->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lbHarmIndex, 2, 0, 1, 1);

        m_lbHarmCoef = new QLabel(QCharEditWidget_Diff);
        m_lbHarmCoef->setObjectName(QString::fromUtf8("m_lbHarmCoef"));
        m_lbHarmCoef->setFont(font);
        m_lbHarmCoef->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_lbHarmCoef, 2, 2, 1, 1);

        m_editHarmCoef = new QSttLineEdit(QCharEditWidget_Diff);
        m_editHarmCoef->setObjectName(QString::fromUtf8("m_editHarmCoef"));
        m_editHarmCoef->setFont(font);

        gridLayout->addWidget(m_editHarmCoef, 2, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        m_layoutVert = new QVBoxLayout();
        m_layoutVert->setSpacing(6);
        m_layoutVert->setObjectName(QString::fromUtf8("m_layoutVert"));
        m_layGridParas = new QGridLayout();
        m_layGridParas->setSpacing(6);
        m_layGridParas->setObjectName(QString::fromUtf8("m_layGridParas"));
        m_edtSet_Istart = new QSttLineEdit(QCharEditWidget_Diff);
        m_edtSet_Istart->setObjectName(QString::fromUtf8("m_edtSet_Istart"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(16);
        m_edtSet_Istart->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Istart, 1, 2, 1, 1);

        m_edtSet_Kstart = new QSttLineEdit(QCharEditWidget_Diff);
        m_edtSet_Kstart->setObjectName(QString::fromUtf8("m_edtSet_Kstart"));
        m_edtSet_Kstart->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Kstart, 1, 3, 1, 1);

        m_lblTitleStart = new QLabel(QCharEditWidget_Diff);
        m_lblTitleStart->setObjectName(QString::fromUtf8("m_lblTitleStart"));
        m_lblTitleStart->setFont(font1);

        m_layGridParas->addWidget(m_lblTitleStart, 1, 1, 1, 1);

        m_lblTitleCurr = new QLabel(QCharEditWidget_Diff);
        m_lblTitleCurr->setObjectName(QString::fromUtf8("m_lblTitleCurr"));
        m_lblTitleCurr->setFont(font1);
        m_lblTitleCurr->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lblTitleCurr, 0, 2, 1, 1);

        m_lblTitleK = new QLabel(QCharEditWidget_Diff);
        m_lblTitleK->setObjectName(QString::fromUtf8("m_lblTitleK"));
        m_lblTitleK->setFont(font1);
        m_lblTitleK->setLayoutDirection(Qt::LeftToRight);
        m_lblTitleK->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lblTitleK, 0, 3, 1, 1);

        m_chkLine1 = new QSttCheckBox(QCharEditWidget_Diff);
        m_chkLine1->setObjectName(QString::fromUtf8("m_chkLine1"));
        m_chkLine1->setFont(font1);

        m_layGridParas->addWidget(m_chkLine1, 2, 0, 1, 1);

        m_edtSet_Ip1 = new QSttLineEdit(QCharEditWidget_Diff);
        m_edtSet_Ip1->setObjectName(QString::fromUtf8("m_edtSet_Ip1"));
        m_edtSet_Ip1->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Ip1, 2, 2, 1, 1);

        m_lblTitleLine1 = new QLabel(QCharEditWidget_Diff);
        m_lblTitleLine1->setObjectName(QString::fromUtf8("m_lblTitleLine1"));
        m_lblTitleLine1->setFont(font1);

        m_layGridParas->addWidget(m_lblTitleLine1, 2, 1, 1, 1);

        m_edtSet_K1 = new QSttLineEdit(QCharEditWidget_Diff);
        m_edtSet_K1->setObjectName(QString::fromUtf8("m_edtSet_K1"));
        m_edtSet_K1->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_K1, 2, 3, 1, 1);

        m_chkStart = new QSttCheckBox(QCharEditWidget_Diff);
        m_chkStart->setObjectName(QString::fromUtf8("m_chkStart"));
        m_chkStart->setFont(font1);

        m_layGridParas->addWidget(m_chkStart, 1, 0, 1, 1);

        m_chkLine3 = new QSttCheckBox(QCharEditWidget_Diff);
        m_chkLine3->setObjectName(QString::fromUtf8("m_chkLine3"));
        m_chkLine3->setFont(font1);

        m_layGridParas->addWidget(m_chkLine3, 4, 0, 1, 1);

        m_chkLine2 = new QSttCheckBox(QCharEditWidget_Diff);
        m_chkLine2->setObjectName(QString::fromUtf8("m_chkLine2"));
        m_chkLine2->setFont(font1);

        m_layGridParas->addWidget(m_chkLine2, 3, 0, 1, 1);

        m_chkLineSd = new QSttCheckBox(QCharEditWidget_Diff);
        m_chkLineSd->setObjectName(QString::fromUtf8("m_chkLineSd"));
        m_chkLineSd->setFont(font1);

        m_layGridParas->addWidget(m_chkLineSd, 5, 0, 1, 1);

        m_lblTitleLine2 = new QLabel(QCharEditWidget_Diff);
        m_lblTitleLine2->setObjectName(QString::fromUtf8("m_lblTitleLine2"));
        m_lblTitleLine2->setFont(font1);

        m_layGridParas->addWidget(m_lblTitleLine2, 3, 1, 1, 1);

        m_lblTitleLine3 = new QLabel(QCharEditWidget_Diff);
        m_lblTitleLine3->setObjectName(QString::fromUtf8("m_lblTitleLine3"));
        m_lblTitleLine3->setFont(font1);

        m_layGridParas->addWidget(m_lblTitleLine3, 4, 1, 1, 1);

        m_lblTitleLineSd = new QLabel(QCharEditWidget_Diff);
        m_lblTitleLineSd->setObjectName(QString::fromUtf8("m_lblTitleLineSd"));
        m_lblTitleLineSd->setFont(font1);

        m_layGridParas->addWidget(m_lblTitleLineSd, 5, 1, 1, 1);

        m_edtSet_Ip2 = new QSttLineEdit(QCharEditWidget_Diff);
        m_edtSet_Ip2->setObjectName(QString::fromUtf8("m_edtSet_Ip2"));
        m_edtSet_Ip2->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Ip2, 3, 2, 1, 1);

        m_edtSet_Ip3 = new QSttLineEdit(QCharEditWidget_Diff);
        m_edtSet_Ip3->setObjectName(QString::fromUtf8("m_edtSet_Ip3"));
        m_edtSet_Ip3->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Ip3, 4, 2, 1, 1);

        m_edtSet_Isd = new QSttLineEdit(QCharEditWidget_Diff);
        m_edtSet_Isd->setObjectName(QString::fromUtf8("m_edtSet_Isd"));
        m_edtSet_Isd->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Isd, 5, 2, 1, 1);

        m_edtSet_K2 = new QSttLineEdit(QCharEditWidget_Diff);
        m_edtSet_K2->setObjectName(QString::fromUtf8("m_edtSet_K2"));
        m_edtSet_K2->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_K2, 3, 3, 1, 1);

        m_edtSet_K3 = new QSttLineEdit(QCharEditWidget_Diff);
        m_edtSet_K3->setObjectName(QString::fromUtf8("m_edtSet_K3"));
        m_edtSet_K3->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_K3, 4, 3, 1, 1);

        m_lbName = new QLabel(QCharEditWidget_Diff);
        m_lbName->setObjectName(QString::fromUtf8("m_lbName"));
        m_lbName->setFont(font);
        m_lbName->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lbName, 0, 0, 1, 1);

        m_lbSetting = new QLabel(QCharEditWidget_Diff);
        m_lbSetting->setObjectName(QString::fromUtf8("m_lbSetting"));
        m_lbSetting->setFont(font);
        m_lbSetting->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lbSetting, 0, 1, 1, 1);


        m_layoutVert->addLayout(m_layGridParas);

        m_layUser = new QHBoxLayout();
        m_layUser->setSpacing(6);
        m_layUser->setObjectName(QString::fromUtf8("m_layUser"));
        m_lbIdValue = new QLabel(QCharEditWidget_Diff);
        m_lbIdValue->setObjectName(QString::fromUtf8("m_lbIdValue"));
        m_lbIdValue->setFont(font1);

        m_layUser->addWidget(m_lbIdValue);

        m_editSet_IdValue = new QSttLineEdit(QCharEditWidget_Diff);
        m_editSet_IdValue->setObjectName(QString::fromUtf8("m_editSet_IdValue"));
        m_editSet_IdValue->setFont(font1);

        m_layUser->addWidget(m_editSet_IdValue);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_layUser->addItem(horizontalSpacer);

        m_btnUserAdd = new QPushButton(QCharEditWidget_Diff);
        m_btnUserAdd->setObjectName(QString::fromUtf8("m_btnUserAdd"));
        m_btnUserAdd->setFont(font);

        m_layUser->addWidget(m_btnUserAdd);

        m_btnUserClear = new QPushButton(QCharEditWidget_Diff);
        m_btnUserClear->setObjectName(QString::fromUtf8("m_btnUserClear"));
        m_btnUserClear->setFont(font);

        m_layUser->addWidget(m_btnUserClear);


        m_layoutVert->addLayout(m_layUser);


        verticalLayout->addLayout(m_layoutVert);


        retranslateUi(QCharEditWidget_Diff);

        QMetaObject::connectSlotsByName(QCharEditWidget_Diff);
    } // setupUi

    void retranslateUi(QWidget *QCharEditWidget_Diff)
    {
        QCharEditWidget_Diff->setWindowTitle(QApplication::translate("QCharEditWidget_Diff", "QCharEditWidget_Diff", 0, QApplication::UnicodeUTF8));
        m_radioNormal->setText(QApplication::translate("QCharEditWidget_Diff", "\346\257\224\347\216\207\345\267\256\345\212\250", 0, QApplication::UnicodeUTF8));
        m_radioHarm->setText(QApplication::translate("QCharEditWidget_Diff", "\350\260\220\346\263\242\345\210\266\345\212\250", 0, QApplication::UnicodeUTF8));
        m_lbSettingMinAxis->setText(QApplication::translate("QCharEditWidget_Diff", "\345\256\232\345\200\274\346\225\264\345\256\232\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        m_lbInSel->setText(QApplication::translate("QCharEditWidget_Diff", "\345\237\272\345\207\206\347\224\265\346\265\201\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        m_lbInSet->setText(QApplication::translate("QCharEditWidget_Diff", "\345\237\272\345\207\206\347\224\265\346\265\201(\345\205\266\345\256\203)", 0, QApplication::UnicodeUTF8));
        m_lbHarmIndex->setText(QApplication::translate("QCharEditWidget_Diff", "\350\260\220\346\263\242\346\254\241\346\225\260", 0, QApplication::UnicodeUTF8));
        m_lbHarmCoef->setText(QApplication::translate("QCharEditWidget_Diff", "\350\260\220\346\263\242\345\210\266\345\212\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        m_lblTitleStart->setText(QApplication::translate("QCharEditWidget_Diff", "\351\227\250\346\247\233\345\200\274", 0, QApplication::UnicodeUTF8));
        m_lblTitleCurr->setText(QApplication::translate("QCharEditWidget_Diff", "\347\224\265\346\265\201\357\274\210Ie\357\274\211", 0, QApplication::UnicodeUTF8));
        m_lblTitleK->setText(QApplication::translate("QCharEditWidget_Diff", "\346\226\234\347\216\207", 0, QApplication::UnicodeUTF8));
        m_chkLine1->setText(QApplication::translate("QCharEditWidget_Diff", "\347\254\254\344\270\200\346\256\265", 0, QApplication::UnicodeUTF8));
        m_lblTitleLine1->setText(QApplication::translate("QCharEditWidget_Diff", "\346\213\220\347\202\2711", 0, QApplication::UnicodeUTF8));
        m_chkStart->setText(QApplication::translate("QCharEditWidget_Diff", "\345\220\257\345\212\250\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_chkLine3->setText(QApplication::translate("QCharEditWidget_Diff", "\347\254\254\344\270\211\346\256\265", 0, QApplication::UnicodeUTF8));
        m_chkLine2->setText(QApplication::translate("QCharEditWidget_Diff", "\347\254\254\344\272\214\346\256\265", 0, QApplication::UnicodeUTF8));
        m_chkLineSd->setText(QApplication::translate("QCharEditWidget_Diff", "\351\200\237\346\226\255", 0, QApplication::UnicodeUTF8));
        m_lblTitleLine2->setText(QApplication::translate("QCharEditWidget_Diff", "\346\213\220\347\202\2712", 0, QApplication::UnicodeUTF8));
        m_lblTitleLine3->setText(QApplication::translate("QCharEditWidget_Diff", "\346\213\220\347\202\2713", 0, QApplication::UnicodeUTF8));
        m_lblTitleLineSd->setText(QApplication::translate("QCharEditWidget_Diff", "\351\200\237\346\226\255\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_lbName->setText(QApplication::translate("QCharEditWidget_Diff", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_lbSetting->setText(QApplication::translate("QCharEditWidget_Diff", "\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_lbIdValue->setText(QApplication::translate("QCharEditWidget_Diff", "\345\210\266\345\212\250\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_btnUserAdd->setText(QApplication::translate("QCharEditWidget_Diff", "\346\267\273\345\212\240\350\207\252\345\256\232\344\271\211\347\202\271", 0, QApplication::UnicodeUTF8));
        m_btnUserClear->setText(QApplication::translate("QCharEditWidget_Diff", "\346\270\205\347\251\272\350\207\252\345\256\232\344\271\211\347\202\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCharEditWidget_Diff: public Ui_QCharEditWidget_Diff {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAREDITWIDGET_DIFF_H
