/********************************************************************************
** Form generated from reading UI file 'QCharEditRadioHarmWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCHAREDITRADIOHARMWIDGET_H
#define UI_QCHAREDITRADIOHARMWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../Controls/SttLineEdit.h"
#include "../../Module/CommonCtrl_QT/QDataTypeComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QCharEditRadioHarmWidget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *m_mainVerticalLayout;
    QGridLayout *gridLayout_4;
    QDataTypeComboBox *m_cbSettingMinAxis;
    QSttLineEdit *m_editHarmCoef;
    QLabel *m_lbInSet;
    QSttLineEdit *m_editInSet;
    QLabel *m_lbHarmIndex;
    QDataTypeComboBox *m_cbHarmIndex;
    QLabel *m_lbHarmCoef;
    QLabel *m_lbSettingMinAxis;
    QDataTypeComboBox *m_cmb_TranSort;
    QLabel *m_lbTranSort;
    QLabel *m_label_Func;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_lblTitleStart;
    QSttLineEdit *m_edtSet_Istart;
    QLabel *m_lblTitleLineSd;
    QSttLineEdit *m_edtSet_Isd;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *m_lbIdValue;
    QSttLineEdit *m_editSet_IdValue;
    QPushButton *m_btnUserAdd;
    QPushButton *m_btnUserClear;

    void setupUi(QWidget *QCharEditRadioHarmWidget)
    {
        if (QCharEditRadioHarmWidget->objectName().isEmpty())
            QCharEditRadioHarmWidget->setObjectName(QString::fromUtf8("QCharEditRadioHarmWidget"));
        QCharEditRadioHarmWidget->resize(447, 519);
        layoutWidget = new QWidget(QCharEditRadioHarmWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 441, 511));
        m_mainVerticalLayout = new QVBoxLayout(layoutWidget);
        m_mainVerticalLayout->setObjectName(QString::fromUtf8("m_mainVerticalLayout"));
        m_mainVerticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_cbSettingMinAxis = new QDataTypeComboBox(layoutWidget);
        m_cbSettingMinAxis->setObjectName(QString::fromUtf8("m_cbSettingMinAxis"));

        gridLayout_4->addWidget(m_cbSettingMinAxis, 0, 1, 1, 1);

        m_editHarmCoef = new QSttLineEdit(layoutWidget);
        m_editHarmCoef->setObjectName(QString::fromUtf8("m_editHarmCoef"));
        QFont font;
        font.setPointSize(16);
        m_editHarmCoef->setFont(font);

        gridLayout_4->addWidget(m_editHarmCoef, 2, 3, 1, 1);

        m_lbInSet = new QLabel(layoutWidget);
        m_lbInSet->setObjectName(QString::fromUtf8("m_lbInSet"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        m_lbInSet->setFont(font1);
        m_lbInSet->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_lbInSet, 0, 2, 1, 1);

        m_editInSet = new QSttLineEdit(layoutWidget);
        m_editInSet->setObjectName(QString::fromUtf8("m_editInSet"));

        gridLayout_4->addWidget(m_editInSet, 0, 3, 1, 1);

        m_lbHarmIndex = new QLabel(layoutWidget);
        m_lbHarmIndex->setObjectName(QString::fromUtf8("m_lbHarmIndex"));
        m_lbHarmIndex->setFont(font1);
        m_lbHarmIndex->setStyleSheet(QString::fromUtf8(""));
        m_lbHarmIndex->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(m_lbHarmIndex, 2, 0, 1, 1);

        m_cbHarmIndex = new QDataTypeComboBox(layoutWidget);
        m_cbHarmIndex->setObjectName(QString::fromUtf8("m_cbHarmIndex"));
        m_cbHarmIndex->setFont(font);

        gridLayout_4->addWidget(m_cbHarmIndex, 2, 1, 1, 1);

        m_lbHarmCoef = new QLabel(layoutWidget);
        m_lbHarmCoef->setObjectName(QString::fromUtf8("m_lbHarmCoef"));
        m_lbHarmCoef->setFont(font1);
        m_lbHarmCoef->setStyleSheet(QString::fromUtf8(""));
        m_lbHarmCoef->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(m_lbHarmCoef, 2, 2, 1, 1);

        m_lbSettingMinAxis = new QLabel(layoutWidget);
        m_lbSettingMinAxis->setObjectName(QString::fromUtf8("m_lbSettingMinAxis"));
        m_lbSettingMinAxis->setFont(font1);
        m_lbSettingMinAxis->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_lbSettingMinAxis, 0, 0, 1, 1);

        m_cmb_TranSort = new QDataTypeComboBox(layoutWidget);
        m_cmb_TranSort->setObjectName(QString::fromUtf8("m_cmb_TranSort"));
        m_cmb_TranSort->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cmb_TranSort, 3, 2, 1, 2);

        m_lbTranSort = new QLabel(layoutWidget);
        m_lbTranSort->setObjectName(QString::fromUtf8("m_lbTranSort"));
        m_lbTranSort->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_lbTranSort, 3, 0, 1, 2);

        m_label_Func = new QLabel(layoutWidget);
        m_label_Func->setObjectName(QString::fromUtf8("m_label_Func"));
        m_label_Func->setFrameShape(QFrame::NoFrame);
        m_label_Func->setFrameShadow(QFrame::Plain);

        gridLayout_4->addWidget(m_label_Func, 4, 0, 1, 4);


        m_mainVerticalLayout->addLayout(gridLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_lblTitleStart = new QLabel(layoutWidget);
        m_lblTitleStart->setObjectName(QString::fromUtf8("m_lblTitleStart"));
        m_lblTitleStart->setFont(font1);
        m_lblTitleStart->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(m_lblTitleStart);

        m_edtSet_Istart = new QSttLineEdit(layoutWidget);
        m_edtSet_Istart->setObjectName(QString::fromUtf8("m_edtSet_Istart"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Agency FB"));
        font2.setPointSize(16);
        m_edtSet_Istart->setFont(font2);

        horizontalLayout_2->addWidget(m_edtSet_Istart);

        m_lblTitleLineSd = new QLabel(layoutWidget);
        m_lblTitleLineSd->setObjectName(QString::fromUtf8("m_lblTitleLineSd"));
        m_lblTitleLineSd->setFont(font1);
        m_lblTitleLineSd->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(m_lblTitleLineSd);

        m_edtSet_Isd = new QSttLineEdit(layoutWidget);
        m_edtSet_Isd->setObjectName(QString::fromUtf8("m_edtSet_Isd"));
        m_edtSet_Isd->setFont(font2);

        horizontalLayout_2->addWidget(m_edtSet_Isd);


        m_mainVerticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_mainVerticalLayout->addItem(verticalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        m_mainVerticalLayout->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_mainVerticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_lbIdValue = new QLabel(layoutWidget);
        m_lbIdValue->setObjectName(QString::fromUtf8("m_lbIdValue"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("HP Simplified Hans Light"));
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        m_lbIdValue->setFont(font3);
        m_lbIdValue->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_lbIdValue);

        m_editSet_IdValue = new QSttLineEdit(layoutWidget);
        m_editSet_IdValue->setObjectName(QString::fromUtf8("m_editSet_IdValue"));
        m_editSet_IdValue->setEnabled(true);
        m_editSet_IdValue->setFont(font2);
        m_editSet_IdValue->setMouseTracking(true);
        m_editSet_IdValue->setAcceptDrops(true);

        horizontalLayout->addWidget(m_editSet_IdValue);

        m_btnUserAdd = new QPushButton(layoutWidget);
        m_btnUserAdd->setObjectName(QString::fromUtf8("m_btnUserAdd"));
        m_btnUserAdd->setFont(font3);
        m_btnUserAdd->setMouseTracking(true);
        m_btnUserAdd->setAcceptDrops(true);
        m_btnUserAdd->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_btnUserAdd);

        m_btnUserClear = new QPushButton(layoutWidget);
        m_btnUserClear->setObjectName(QString::fromUtf8("m_btnUserClear"));
        m_btnUserClear->setFont(font3);
        m_btnUserClear->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(m_btnUserClear);


        m_mainVerticalLayout->addLayout(horizontalLayout);


        retranslateUi(QCharEditRadioHarmWidget);

        QMetaObject::connectSlotsByName(QCharEditRadioHarmWidget);
    } // setupUi

    void retranslateUi(QWidget *QCharEditRadioHarmWidget)
    {
        QCharEditRadioHarmWidget->setWindowTitle(QApplication::translate("QCharEditRadioHarmWidget", "QCharEditRadioHarmWidget", 0, QApplication::UnicodeUTF8));
        m_lbInSet->setText(QApplication::translate("QCharEditRadioHarmWidget", "\345\237\272\345\207\206\347\224\265\346\265\201\357\274\210A/Ie\357\274\211", 0, QApplication::UnicodeUTF8));
        m_lbHarmIndex->setText(QApplication::translate("QCharEditRadioHarmWidget", "\350\260\220\346\263\242\346\254\241\346\225\260", 0, QApplication::UnicodeUTF8));
        m_lbHarmCoef->setText(QApplication::translate("QCharEditRadioHarmWidget", "\350\260\220\346\263\242\345\210\266\345\212\250\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        m_lbSettingMinAxis->setText(QApplication::translate("QCharEditRadioHarmWidget", "\345\256\232\345\200\274\346\225\264\345\256\232\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        m_lbTranSort->setText(QApplication::translate("QCharEditRadioHarmWidget", "\345\217\230\345\216\213\345\231\250\346\216\245\347\272\277\345\275\242\345\274\217", 0, QApplication::UnicodeUTF8));
        m_label_Func->setText(QString());
        m_lblTitleStart->setText(QApplication::translate("QCharEditRadioHarmWidget", "\351\227\250\346\247\233\345\200\274", 0, QApplication::UnicodeUTF8));
        m_lblTitleLineSd->setText(QApplication::translate("QCharEditRadioHarmWidget", "\351\200\237\346\226\255\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_lbIdValue->setText(QApplication::translate("QCharEditRadioHarmWidget", "\345\210\266\345\212\250\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_btnUserAdd->setText(QApplication::translate("QCharEditRadioHarmWidget", "\346\267\273\345\212\240\350\207\252\345\256\232\344\271\211\347\202\271", 0, QApplication::UnicodeUTF8));
        m_btnUserClear->setText(QApplication::translate("QCharEditRadioHarmWidget", "\346\270\205\347\251\272\350\207\252\345\256\232\344\271\211\347\202\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCharEditRadioHarmWidget: public Ui_QCharEditRadioHarmWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCHAREDITRADIOHARMWIDGET_H
