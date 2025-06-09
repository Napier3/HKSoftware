/********************************************************************************
** Form generated from reading UI file 'DiffTimeItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFTIMEITEMPARAEDITWIDGET_H
#define UI_DIFFTIMEITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDiffTimeItemParaEditWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labTime_FaultType;
    QComboBox *m_cmbTime_FaultType;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labTime_Ir;
    QLineEdit *m_txtTime_Ir;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labTime_Id;
    QLineEdit *m_txtTime_Id;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_labTime_Freq;
    QLineEdit *m_txtTime_Freq;
    QHBoxLayout *horizontalLayout_8;
    QLabel *m_labTime_FaultTime;
    QLineEdit *m_txtTime_FaultTime;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labTime_AbsErr;
    QSettingLineEdit *m_txtTime_AbsErrPos;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labTime_AbsErr_2;
    QSettingLineEdit *m_txtTime_AbsErrNeg;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labTime_RelErr;
    QSettingLineEdit *m_txtTime_RelErr;

    void setupUi(QWidget *QDiffTimeItemParaEditWidget)
    {
        if (QDiffTimeItemParaEditWidget->objectName().isEmpty())
            QDiffTimeItemParaEditWidget->setObjectName(QString::fromUtf8("QDiffTimeItemParaEditWidget"));
        QDiffTimeItemParaEditWidget->resize(837, 374);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QDiffTimeItemParaEditWidget->sizePolicy().hasHeightForWidth());
        QDiffTimeItemParaEditWidget->setSizePolicy(sizePolicy);
        QDiffTimeItemParaEditWidget->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(QDiffTimeItemParaEditWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labTime_FaultType = new QLabel(QDiffTimeItemParaEditWidget);
        m_labTime_FaultType->setObjectName(QString::fromUtf8("m_labTime_FaultType"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_labTime_FaultType->sizePolicy().hasHeightForWidth());
        m_labTime_FaultType->setSizePolicy(sizePolicy1);
        m_labTime_FaultType->setMinimumSize(QSize(170, 0));
        m_labTime_FaultType->setMaximumSize(QSize(170, 16777215));
        m_labTime_FaultType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(m_labTime_FaultType);

        m_cmbTime_FaultType = new QComboBox(QDiffTimeItemParaEditWidget);
        m_cmbTime_FaultType->setObjectName(QString::fromUtf8("m_cmbTime_FaultType"));
        sizePolicy1.setHeightForWidth(m_cmbTime_FaultType->sizePolicy().hasHeightForWidth());
        m_cmbTime_FaultType->setSizePolicy(sizePolicy1);
        m_cmbTime_FaultType->setMinimumSize(QSize(170, 0));
        m_cmbTime_FaultType->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_cmbTime_FaultType);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_labTime_Ir = new QLabel(QDiffTimeItemParaEditWidget);
        m_labTime_Ir->setObjectName(QString::fromUtf8("m_labTime_Ir"));
        sizePolicy1.setHeightForWidth(m_labTime_Ir->sizePolicy().hasHeightForWidth());
        m_labTime_Ir->setSizePolicy(sizePolicy1);
        m_labTime_Ir->setMinimumSize(QSize(170, 0));
        m_labTime_Ir->setMaximumSize(QSize(170, 16777215));
        m_labTime_Ir->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_labTime_Ir);

        m_txtTime_Ir = new QLineEdit(QDiffTimeItemParaEditWidget);
        m_txtTime_Ir->setObjectName(QString::fromUtf8("m_txtTime_Ir"));
        sizePolicy1.setHeightForWidth(m_txtTime_Ir->sizePolicy().hasHeightForWidth());
        m_txtTime_Ir->setSizePolicy(sizePolicy1);
        m_txtTime_Ir->setMinimumSize(QSize(170, 0));
        m_txtTime_Ir->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_txtTime_Ir);


        gridLayout->addLayout(horizontalLayout_3, 3, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_labTime_Id = new QLabel(QDiffTimeItemParaEditWidget);
        m_labTime_Id->setObjectName(QString::fromUtf8("m_labTime_Id"));
        sizePolicy1.setHeightForWidth(m_labTime_Id->sizePolicy().hasHeightForWidth());
        m_labTime_Id->setSizePolicy(sizePolicy1);
        m_labTime_Id->setMinimumSize(QSize(170, 0));
        m_labTime_Id->setMaximumSize(QSize(170, 16777215));
        m_labTime_Id->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(m_labTime_Id);

        m_txtTime_Id = new QLineEdit(QDiffTimeItemParaEditWidget);
        m_txtTime_Id->setObjectName(QString::fromUtf8("m_txtTime_Id"));
        m_txtTime_Id->setEnabled(false);
        sizePolicy1.setHeightForWidth(m_txtTime_Id->sizePolicy().hasHeightForWidth());
        m_txtTime_Id->setSizePolicy(sizePolicy1);
        m_txtTime_Id->setMinimumSize(QSize(170, 0));
        m_txtTime_Id->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_txtTime_Id);


        gridLayout->addLayout(horizontalLayout_4, 4, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 6, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 2, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_labTime_Freq = new QLabel(QDiffTimeItemParaEditWidget);
        m_labTime_Freq->setObjectName(QString::fromUtf8("m_labTime_Freq"));
        sizePolicy1.setHeightForWidth(m_labTime_Freq->sizePolicy().hasHeightForWidth());
        m_labTime_Freq->setSizePolicy(sizePolicy1);
        m_labTime_Freq->setMinimumSize(QSize(170, 0));
        m_labTime_Freq->setMaximumSize(QSize(170, 16777215));
        m_labTime_Freq->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(m_labTime_Freq);

        m_txtTime_Freq = new QLineEdit(QDiffTimeItemParaEditWidget);
        m_txtTime_Freq->setObjectName(QString::fromUtf8("m_txtTime_Freq"));
        sizePolicy1.setHeightForWidth(m_txtTime_Freq->sizePolicy().hasHeightForWidth());
        m_txtTime_Freq->setSizePolicy(sizePolicy1);
        m_txtTime_Freq->setMinimumSize(QSize(170, 0));
        m_txtTime_Freq->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_7->addWidget(m_txtTime_Freq);


        gridLayout->addLayout(horizontalLayout_7, 5, 1, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        m_labTime_FaultTime = new QLabel(QDiffTimeItemParaEditWidget);
        m_labTime_FaultTime->setObjectName(QString::fromUtf8("m_labTime_FaultTime"));
        sizePolicy1.setHeightForWidth(m_labTime_FaultTime->sizePolicy().hasHeightForWidth());
        m_labTime_FaultTime->setSizePolicy(sizePolicy1);
        m_labTime_FaultTime->setMinimumSize(QSize(170, 0));
        m_labTime_FaultTime->setMaximumSize(QSize(170, 16777215));
        m_labTime_FaultTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(m_labTime_FaultTime);

        m_txtTime_FaultTime = new QLineEdit(QDiffTimeItemParaEditWidget);
        m_txtTime_FaultTime->setObjectName(QString::fromUtf8("m_txtTime_FaultTime"));
        sizePolicy1.setHeightForWidth(m_txtTime_FaultTime->sizePolicy().hasHeightForWidth());
        m_txtTime_FaultTime->setSizePolicy(sizePolicy1);
        m_txtTime_FaultTime->setMinimumSize(QSize(170, 0));
        m_txtTime_FaultTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_8->addWidget(m_txtTime_FaultTime);


        gridLayout->addLayout(horizontalLayout_8, 6, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labTime_AbsErr = new QLabel(QDiffTimeItemParaEditWidget);
        m_labTime_AbsErr->setObjectName(QString::fromUtf8("m_labTime_AbsErr"));
        sizePolicy1.setHeightForWidth(m_labTime_AbsErr->sizePolicy().hasHeightForWidth());
        m_labTime_AbsErr->setSizePolicy(sizePolicy1);
        m_labTime_AbsErr->setMinimumSize(QSize(170, 0));
        m_labTime_AbsErr->setMaximumSize(QSize(170, 16777215));
        m_labTime_AbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_labTime_AbsErr);

        m_txtTime_AbsErrPos = new QSettingLineEdit(QDiffTimeItemParaEditWidget);
        m_txtTime_AbsErrPos->setObjectName(QString::fromUtf8("m_txtTime_AbsErrPos"));
        sizePolicy1.setHeightForWidth(m_txtTime_AbsErrPos->sizePolicy().hasHeightForWidth());
        m_txtTime_AbsErrPos->setSizePolicy(sizePolicy1);
        m_txtTime_AbsErrPos->setMinimumSize(QSize(170, 0));
        m_txtTime_AbsErrPos->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_txtTime_AbsErrPos);


        gridLayout->addLayout(horizontalLayout_2, 2, 3, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_labTime_AbsErr_2 = new QLabel(QDiffTimeItemParaEditWidget);
        m_labTime_AbsErr_2->setObjectName(QString::fromUtf8("m_labTime_AbsErr_2"));
        sizePolicy1.setHeightForWidth(m_labTime_AbsErr_2->sizePolicy().hasHeightForWidth());
        m_labTime_AbsErr_2->setSizePolicy(sizePolicy1);
        m_labTime_AbsErr_2->setMinimumSize(QSize(170, 0));
        m_labTime_AbsErr_2->setMaximumSize(QSize(170, 16777215));
        m_labTime_AbsErr_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(m_labTime_AbsErr_2);

        m_txtTime_AbsErrNeg = new QSettingLineEdit(QDiffTimeItemParaEditWidget);
        m_txtTime_AbsErrNeg->setObjectName(QString::fromUtf8("m_txtTime_AbsErrNeg"));
        sizePolicy1.setHeightForWidth(m_txtTime_AbsErrNeg->sizePolicy().hasHeightForWidth());
        m_txtTime_AbsErrNeg->setSizePolicy(sizePolicy1);
        m_txtTime_AbsErrNeg->setMinimumSize(QSize(170, 0));
        m_txtTime_AbsErrNeg->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_txtTime_AbsErrNeg);


        gridLayout->addLayout(horizontalLayout_5, 3, 3, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labTime_RelErr = new QLabel(QDiffTimeItemParaEditWidget);
        m_labTime_RelErr->setObjectName(QString::fromUtf8("m_labTime_RelErr"));
        sizePolicy1.setHeightForWidth(m_labTime_RelErr->sizePolicy().hasHeightForWidth());
        m_labTime_RelErr->setSizePolicy(sizePolicy1);
        m_labTime_RelErr->setMinimumSize(QSize(170, 0));
        m_labTime_RelErr->setMaximumSize(QSize(170, 16777215));
        m_labTime_RelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(m_labTime_RelErr);

        m_txtTime_RelErr = new QSettingLineEdit(QDiffTimeItemParaEditWidget);
        m_txtTime_RelErr->setObjectName(QString::fromUtf8("m_txtTime_RelErr"));
        sizePolicy1.setHeightForWidth(m_txtTime_RelErr->sizePolicy().hasHeightForWidth());
        m_txtTime_RelErr->setSizePolicy(sizePolicy1);
        m_txtTime_RelErr->setMinimumSize(QSize(170, 0));
        m_txtTime_RelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_txtTime_RelErr);


        gridLayout->addLayout(horizontalLayout_6, 4, 3, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 4);
        gridLayout->setColumnStretch(2, 2);
        gridLayout->setColumnStretch(3, 4);
        gridLayout->setColumnStretch(4, 1);

        retranslateUi(QDiffTimeItemParaEditWidget);

        QMetaObject::connectSlotsByName(QDiffTimeItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QDiffTimeItemParaEditWidget)
    {
        QDiffTimeItemParaEditWidget->setWindowTitle(QApplication::translate("QDiffTimeItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_labTime_FaultType->setText(QApplication::translate("QDiffTimeItemParaEditWidget", "\346\225\205\351\232\234\347\233\270\345\210\253", 0, QApplication::UnicodeUTF8));
        m_cmbTime_FaultType->clear();
        m_cmbTime_FaultType->insertItems(0, QStringList()
         << QApplication::translate("QDiffTimeItemParaEditWidget", "A", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffTimeItemParaEditWidget", "B", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffTimeItemParaEditWidget", "C", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffTimeItemParaEditWidget", "ABC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffTimeItemParaEditWidget", "AB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffTimeItemParaEditWidget", "BC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffTimeItemParaEditWidget", "CA", 0, QApplication::UnicodeUTF8)
        );
        m_labTime_Ir->setText(QApplication::translate("QDiffTimeItemParaEditWidget", "\345\210\266\345\212\250\347\224\265\346\265\201Ir():", 0, QApplication::UnicodeUTF8));
        m_labTime_Id->setText(QApplication::translate("QDiffTimeItemParaEditWidget", "\345\267\256\345\212\250\347\224\265\346\265\201Id():", 0, QApplication::UnicodeUTF8));
        m_labTime_Freq->setText(QApplication::translate("QDiffTimeItemParaEditWidget", "\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labTime_FaultTime->setText(QApplication::translate("QDiffTimeItemParaEditWidget", "\346\234\200\345\244\247\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labTime_AbsErr->setText(QApplication::translate("QDiffTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_labTime_AbsErr_2->setText(QApplication::translate("QDiffTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
        m_labTime_RelErr->setText(QApplication::translate("QDiffTimeItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDiffTimeItemParaEditWidget: public Ui_QDiffTimeItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFTIMEITEMPARAEDITWIDGET_H
