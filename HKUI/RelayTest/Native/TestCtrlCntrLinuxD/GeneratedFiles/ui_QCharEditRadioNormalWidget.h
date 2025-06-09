/********************************************************************************
** Form generated from reading UI file 'QCharEditRadioNormalWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCHAREDITRADIONORMALWIDGET_H
#define UI_QCHAREDITRADIONORMALWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../Controls/SttLineEdit.h"
#include "../../Module/CommonCtrl_QT/QDataTypeComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QCharEditRadioNormalWidget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *m_mainVerticalLayout;
    QGridLayout *gridLayout;
    QLabel *m_lbInSet;
    QSttLineEdit *m_editInSet;
    QDataTypeComboBox *m_cbSettingMinAxis;
    QLabel *m_lbSettingMinAxis;
    QDataTypeComboBox *m_cmb_TranSort;
    QLabel *m_lbTranSort;
    QLabel *m_label_Func;
    QGridLayout *gridLayout_2;
    QLabel *m_lblTitleLine2;
    QSttLineEdit *m_edtSet_Ip1;
    QLabel *m_lblTitleLineSd;
    QSttLineEdit *m_edtSet_K1;
    QCheckBox *m_chkStart;
    QCheckBox *m_chkLine2;
    QLabel *m_lblTitleCurr;
    QLabel *m_lbSetting;
    QSttLineEdit *m_edtSet_Istart;
    QLabel *m_lbName;
    QCheckBox *m_chkLine1;
    QLabel *m_lblTitleStart;
    QLabel *m_lblTitleK;
    QLabel *m_lblTitleLine1;
    QLabel *m_lblSet_K;
    QSttLineEdit *m_edtSet_K2;
    QSttLineEdit *m_edtSet_Kstart;
    QSttLineEdit *m_edtSet_Ip2;
    QSttLineEdit *m_edtSet_Isd;
    QCheckBox *m_chkLineSd;
    QHBoxLayout *horizontalLayout;
    QLabel *m_lbIdValue;
    QSttLineEdit *m_editSet_IdValue;
    QPushButton *m_btnUserAdd;
    QPushButton *m_btnUserClear;

    void setupUi(QWidget *QCharEditRadioNormalWidget)
    {
        if (QCharEditRadioNormalWidget->objectName().isEmpty())
            QCharEditRadioNormalWidget->setObjectName(QString::fromUtf8("QCharEditRadioNormalWidget"));
        QCharEditRadioNormalWidget->setEnabled(true);
        QCharEditRadioNormalWidget->resize(447, 519);
        layoutWidget = new QWidget(QCharEditRadioNormalWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 5, 441, 511));
        m_mainVerticalLayout = new QVBoxLayout(layoutWidget);
        m_mainVerticalLayout->setObjectName(QString::fromUtf8("m_mainVerticalLayout"));
        m_mainVerticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_lbInSet = new QLabel(layoutWidget);
        m_lbInSet->setObjectName(QString::fromUtf8("m_lbInSet"));
        QFont font;
        font.setFamily(QString::fromUtf8("HP Simplified Hans Light"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        m_lbInSet->setFont(font);
        m_lbInSet->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_lbInSet, 0, 2, 1, 1);

        m_editInSet = new QSttLineEdit(layoutWidget);
        m_editInSet->setObjectName(QString::fromUtf8("m_editInSet"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(16);
        m_editInSet->setFont(font1);

        gridLayout->addWidget(m_editInSet, 0, 3, 1, 1);

        m_cbSettingMinAxis = new QDataTypeComboBox(layoutWidget);
        m_cbSettingMinAxis->setObjectName(QString::fromUtf8("m_cbSettingMinAxis"));

        gridLayout->addWidget(m_cbSettingMinAxis, 0, 1, 1, 1, Qt::AlignLeft);

        m_lbSettingMinAxis = new QLabel(layoutWidget);
        m_lbSettingMinAxis->setObjectName(QString::fromUtf8("m_lbSettingMinAxis"));
        m_lbSettingMinAxis->setFont(font);
        m_lbSettingMinAxis->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_lbSettingMinAxis, 0, 0, 1, 1);

        m_cmb_TranSort = new QDataTypeComboBox(layoutWidget);
        m_cmb_TranSort->setObjectName(QString::fromUtf8("m_cmb_TranSort"));
        m_cmb_TranSort->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cmb_TranSort, 1, 2, 1, 2);

        m_lbTranSort = new QLabel(layoutWidget);
        m_lbTranSort->setObjectName(QString::fromUtf8("m_lbTranSort"));
        m_lbTranSort->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_lbTranSort, 1, 0, 1, 2);

        m_label_Func = new QLabel(layoutWidget);
        m_label_Func->setObjectName(QString::fromUtf8("m_label_Func"));
        m_label_Func->setFrameShape(QFrame::NoFrame);
        m_label_Func->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(m_label_Func, 2, 0, 1, 4);


        m_mainVerticalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_lblTitleLine2 = new QLabel(layoutWidget);
        m_lblTitleLine2->setObjectName(QString::fromUtf8("m_lblTitleLine2"));
        m_lblTitleLine2->setFont(font);
        m_lblTitleLine2->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_lblTitleLine2, 4, 2, 1, 1);

        m_edtSet_Ip1 = new QSttLineEdit(layoutWidget);
        m_edtSet_Ip1->setObjectName(QString::fromUtf8("m_edtSet_Ip1"));
        m_edtSet_Ip1->setFont(font1);

        gridLayout_2->addWidget(m_edtSet_Ip1, 3, 3, 1, 1);

        m_lblTitleLineSd = new QLabel(layoutWidget);
        m_lblTitleLineSd->setObjectName(QString::fromUtf8("m_lblTitleLineSd"));
        m_lblTitleLineSd->setFont(font);
        m_lblTitleLineSd->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_lblTitleLineSd, 5, 2, 1, 1);

        m_edtSet_K1 = new QSttLineEdit(layoutWidget);
        m_edtSet_K1->setObjectName(QString::fromUtf8("m_edtSet_K1"));
        m_edtSet_K1->setFont(font1);

        gridLayout_2->addWidget(m_edtSet_K1, 3, 4, 1, 1);

        m_chkStart = new QCheckBox(layoutWidget);
        m_chkStart->setObjectName(QString::fromUtf8("m_chkStart"));

        gridLayout_2->addWidget(m_chkStart, 2, 1, 1, 1);

        m_chkLine2 = new QCheckBox(layoutWidget);
        m_chkLine2->setObjectName(QString::fromUtf8("m_chkLine2"));

        gridLayout_2->addWidget(m_chkLine2, 4, 1, 1, 1);

        m_lblTitleCurr = new QLabel(layoutWidget);
        m_lblTitleCurr->setObjectName(QString::fromUtf8("m_lblTitleCurr"));
        m_lblTitleCurr->setFont(font);
        m_lblTitleCurr->setStyleSheet(QString::fromUtf8(""));
        m_lblTitleCurr->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_lblTitleCurr, 0, 3, 1, 1);

        m_lbSetting = new QLabel(layoutWidget);
        m_lbSetting->setObjectName(QString::fromUtf8("m_lbSetting"));
        m_lbSetting->setFont(font);
        m_lbSetting->setStyleSheet(QString::fromUtf8(""));
        m_lbSetting->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_lbSetting, 0, 2, 1, 1);

        m_edtSet_Istart = new QSttLineEdit(layoutWidget);
        m_edtSet_Istart->setObjectName(QString::fromUtf8("m_edtSet_Istart"));
        m_edtSet_Istart->setFont(font1);

        gridLayout_2->addWidget(m_edtSet_Istart, 2, 3, 1, 1);

        m_lbName = new QLabel(layoutWidget);
        m_lbName->setObjectName(QString::fromUtf8("m_lbName"));
        m_lbName->setFont(font);
        m_lbName->setStyleSheet(QString::fromUtf8(""));
        m_lbName->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_lbName, 0, 1, 1, 1);

        m_chkLine1 = new QCheckBox(layoutWidget);
        m_chkLine1->setObjectName(QString::fromUtf8("m_chkLine1"));

        gridLayout_2->addWidget(m_chkLine1, 3, 1, 1, 1);

        m_lblTitleStart = new QLabel(layoutWidget);
        m_lblTitleStart->setObjectName(QString::fromUtf8("m_lblTitleStart"));
        m_lblTitleStart->setFont(font);
        m_lblTitleStart->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_lblTitleStart, 2, 2, 1, 1);

        m_lblTitleK = new QLabel(layoutWidget);
        m_lblTitleK->setObjectName(QString::fromUtf8("m_lblTitleK"));
        m_lblTitleK->setFont(font);
        m_lblTitleK->setLayoutDirection(Qt::LeftToRight);
        m_lblTitleK->setStyleSheet(QString::fromUtf8(""));
        m_lblTitleK->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_lblTitleK, 0, 4, 1, 1);

        m_lblTitleLine1 = new QLabel(layoutWidget);
        m_lblTitleLine1->setObjectName(QString::fromUtf8("m_lblTitleLine1"));
        m_lblTitleLine1->setFont(font);
        m_lblTitleLine1->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(m_lblTitleLine1, 3, 2, 1, 1);

        m_lblSet_K = new QLabel(layoutWidget);
        m_lblSet_K->setObjectName(QString::fromUtf8("m_lblSet_K"));
        m_lblSet_K->setStyleSheet(QString::fromUtf8(""));
        m_lblSet_K->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_lblSet_K, 5, 4, 1, 1);

        m_edtSet_K2 = new QSttLineEdit(layoutWidget);
        m_edtSet_K2->setObjectName(QString::fromUtf8("m_edtSet_K2"));
        m_edtSet_K2->setFont(font1);

        gridLayout_2->addWidget(m_edtSet_K2, 4, 4, 1, 1);

        m_edtSet_Kstart = new QSttLineEdit(layoutWidget);
        m_edtSet_Kstart->setObjectName(QString::fromUtf8("m_edtSet_Kstart"));
        m_edtSet_Kstart->setFont(font1);

        gridLayout_2->addWidget(m_edtSet_Kstart, 2, 4, 1, 1);

        m_edtSet_Ip2 = new QSttLineEdit(layoutWidget);
        m_edtSet_Ip2->setObjectName(QString::fromUtf8("m_edtSet_Ip2"));
        m_edtSet_Ip2->setFont(font1);

        gridLayout_2->addWidget(m_edtSet_Ip2, 4, 3, 1, 1);

        m_edtSet_Isd = new QSttLineEdit(layoutWidget);
        m_edtSet_Isd->setObjectName(QString::fromUtf8("m_edtSet_Isd"));
        m_edtSet_Isd->setFont(font1);

        gridLayout_2->addWidget(m_edtSet_Isd, 5, 3, 1, 1);

        m_chkLineSd = new QCheckBox(layoutWidget);
        m_chkLineSd->setObjectName(QString::fromUtf8("m_chkLineSd"));

        gridLayout_2->addWidget(m_chkLineSd, 5, 1, 1, 1);


        m_mainVerticalLayout->addLayout(gridLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_lbIdValue = new QLabel(layoutWidget);
        m_lbIdValue->setObjectName(QString::fromUtf8("m_lbIdValue"));
        m_lbIdValue->setFont(font);
        m_lbIdValue->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_lbIdValue);

        m_editSet_IdValue = new QSttLineEdit(layoutWidget);
        m_editSet_IdValue->setObjectName(QString::fromUtf8("m_editSet_IdValue"));
        m_editSet_IdValue->setEnabled(true);
        m_editSet_IdValue->setFont(font1);
        m_editSet_IdValue->setMouseTracking(true);
        m_editSet_IdValue->setAcceptDrops(true);

        horizontalLayout->addWidget(m_editSet_IdValue);

        m_btnUserAdd = new QPushButton(layoutWidget);
        m_btnUserAdd->setObjectName(QString::fromUtf8("m_btnUserAdd"));
        m_btnUserAdd->setFont(font);
        m_btnUserAdd->setMouseTracking(true);
        m_btnUserAdd->setAcceptDrops(true);
        m_btnUserAdd->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_btnUserAdd);

        m_btnUserClear = new QPushButton(layoutWidget);
        m_btnUserClear->setObjectName(QString::fromUtf8("m_btnUserClear"));
        m_btnUserClear->setFont(font);
        m_btnUserClear->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_btnUserClear);


        m_mainVerticalLayout->addLayout(horizontalLayout);


        retranslateUi(QCharEditRadioNormalWidget);

        QMetaObject::connectSlotsByName(QCharEditRadioNormalWidget);
    } // setupUi

    void retranslateUi(QWidget *QCharEditRadioNormalWidget)
    {
        QCharEditRadioNormalWidget->setWindowTitle(QApplication::translate("QCharEditRadioNormalWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_lbInSet->setText(QApplication::translate("QCharEditRadioNormalWidget", "\345\237\272\345\207\206\347\224\265\346\265\201(A/Ie)", 0, QApplication::UnicodeUTF8));
        m_lbSettingMinAxis->setText(QApplication::translate("QCharEditRadioNormalWidget", "\345\256\232\345\200\274\346\225\264\345\256\232\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        m_lbTranSort->setText(QApplication::translate("QCharEditRadioNormalWidget", "\345\217\230\345\216\213\345\231\250\346\216\245\347\272\277\345\275\242\345\274\217", 0, QApplication::UnicodeUTF8));
        m_label_Func->setText(QString());
        m_lblTitleLine2->setText(QApplication::translate("QCharEditRadioNormalWidget", "\346\213\220\347\202\2712", 0, QApplication::UnicodeUTF8));
        m_lblTitleLineSd->setText(QApplication::translate("QCharEditRadioNormalWidget", "\345\267\256\345\212\250\351\200\237\346\226\255", 0, QApplication::UnicodeUTF8));
        m_chkStart->setText(QApplication::translate("QCharEditRadioNormalWidget", "\345\220\257\345\212\250\351\227\250\346\247\233", 0, QApplication::UnicodeUTF8));
        m_chkLine2->setText(QApplication::translate("QCharEditRadioNormalWidget", "\347\254\254\344\272\214\346\256\265", 0, QApplication::UnicodeUTF8));
        m_lblTitleCurr->setText(QApplication::translate("QCharEditRadioNormalWidget", "\347\224\265\346\265\201\357\274\210A/Ie\357\274\211", 0, QApplication::UnicodeUTF8));
        m_lbSetting->setText(QApplication::translate("QCharEditRadioNormalWidget", "\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_lbName->setText(QApplication::translate("QCharEditRadioNormalWidget", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_chkLine1->setText(QApplication::translate("QCharEditRadioNormalWidget", "\347\254\254\344\270\200\346\256\265", 0, QApplication::UnicodeUTF8));
        m_lblTitleStart->setText(QApplication::translate("QCharEditRadioNormalWidget", "\345\220\257\345\212\250\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_lblTitleK->setText(QApplication::translate("QCharEditRadioNormalWidget", "\346\257\224\347\216\207\345\210\266\345\212\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        m_lblTitleLine1->setText(QApplication::translate("QCharEditRadioNormalWidget", "\346\213\220\347\202\2711", 0, QApplication::UnicodeUTF8));
        m_lblSet_K->setText(QApplication::translate("QCharEditRadioNormalWidget", "0", 0, QApplication::UnicodeUTF8));
        m_chkLineSd->setText(QApplication::translate("QCharEditRadioNormalWidget", "\351\200\237\346\226\255\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_lbIdValue->setText(QApplication::translate("QCharEditRadioNormalWidget", "\345\210\266\345\212\250\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_btnUserAdd->setText(QApplication::translate("QCharEditRadioNormalWidget", "\346\267\273\345\212\240\350\207\252\345\256\232\344\271\211\347\202\271", 0, QApplication::UnicodeUTF8));
        m_btnUserClear->setText(QApplication::translate("QCharEditRadioNormalWidget", "\346\270\205\347\251\272\350\207\252\345\256\232\344\271\211\347\202\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCharEditRadioNormalWidget: public Ui_QCharEditRadioNormalWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCHAREDITRADIONORMALWIDGET_H
