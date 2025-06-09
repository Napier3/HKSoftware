/********************************************************************************
** Form generated from reading UI file 'DiffRateItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFRATEITEMPARAEDITWIDGET_H
#define UI_DIFFRATEITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDiffRateItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labRate_FaultType;
    QComboBox *m_cmbRate_FaultType;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labRate_BeginVal;
    QLineEdit *m_txtRate_BeginVal;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labRate_EndVal;
    QLineEdit *m_txtRate_EndVal;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labRate_Step;
    QLineEdit *m_txtRate_Step;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labRate_Freq;
    QLineEdit *m_txtRate_Freq;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_labRate_Ir;
    QLineEdit *m_txtRate_Ir;
    QHBoxLayout *horizontalLayout_8;
    QLabel *m_labRate_IdSetting;
    QLineEdit *m_txtRate_IdSetting;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_labRate_FaultTime;
    QLineEdit *m_txtRate_FaultTime;
    QHBoxLayout *horizontalLayout_10;
    QLabel *m_labRate_AbsErr;
    QSettingLineEdit *m_txtRate_AbsErr;
    QHBoxLayout *horizontalLayout_11;
    QLabel *m_labRate_RelErr;
    QSettingLineEdit *m_txtRate_RelErr;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QDiffRateItemParaEditWidget)
    {
        if (QDiffRateItemParaEditWidget->objectName().isEmpty())
            QDiffRateItemParaEditWidget->setObjectName(QString::fromUtf8("QDiffRateItemParaEditWidget"));
        QDiffRateItemParaEditWidget->resize(895, 355);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QDiffRateItemParaEditWidget->sizePolicy().hasHeightForWidth());
        QDiffRateItemParaEditWidget->setSizePolicy(sizePolicy);
        QDiffRateItemParaEditWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout_2 = new QHBoxLayout(QDiffRateItemParaEditWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labRate_FaultType = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_FaultType->setObjectName(QString::fromUtf8("m_labRate_FaultType"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_labRate_FaultType->sizePolicy().hasHeightForWidth());
        m_labRate_FaultType->setSizePolicy(sizePolicy1);
        m_labRate_FaultType->setMinimumSize(QSize(170, 0));
        m_labRate_FaultType->setMaximumSize(QSize(170, 16777215));
        m_labRate_FaultType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(m_labRate_FaultType);

        m_cmbRate_FaultType = new QComboBox(QDiffRateItemParaEditWidget);
        m_cmbRate_FaultType->setObjectName(QString::fromUtf8("m_cmbRate_FaultType"));
        sizePolicy1.setHeightForWidth(m_cmbRate_FaultType->sizePolicy().hasHeightForWidth());
        m_cmbRate_FaultType->setSizePolicy(sizePolicy1);
        m_cmbRate_FaultType->setMinimumSize(QSize(170, 0));
        m_cmbRate_FaultType->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_cmbRate_FaultType);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_labRate_BeginVal = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_BeginVal->setObjectName(QString::fromUtf8("m_labRate_BeginVal"));
        sizePolicy1.setHeightForWidth(m_labRate_BeginVal->sizePolicy().hasHeightForWidth());
        m_labRate_BeginVal->setSizePolicy(sizePolicy1);
        m_labRate_BeginVal->setMinimumSize(QSize(170, 0));
        m_labRate_BeginVal->setMaximumSize(QSize(170, 16777215));
        m_labRate_BeginVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_labRate_BeginVal);

        m_txtRate_BeginVal = new QLineEdit(QDiffRateItemParaEditWidget);
        m_txtRate_BeginVal->setObjectName(QString::fromUtf8("m_txtRate_BeginVal"));
        sizePolicy1.setHeightForWidth(m_txtRate_BeginVal->sizePolicy().hasHeightForWidth());
        m_txtRate_BeginVal->setSizePolicy(sizePolicy1);
        m_txtRate_BeginVal->setMinimumSize(QSize(170, 0));
        m_txtRate_BeginVal->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_txtRate_BeginVal);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_labRate_EndVal = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_EndVal->setObjectName(QString::fromUtf8("m_labRate_EndVal"));
        sizePolicy1.setHeightForWidth(m_labRate_EndVal->sizePolicy().hasHeightForWidth());
        m_labRate_EndVal->setSizePolicy(sizePolicy1);
        m_labRate_EndVal->setMinimumSize(QSize(170, 0));
        m_labRate_EndVal->setMaximumSize(QSize(170, 16777215));
        m_labRate_EndVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(m_labRate_EndVal);

        m_txtRate_EndVal = new QLineEdit(QDiffRateItemParaEditWidget);
        m_txtRate_EndVal->setObjectName(QString::fromUtf8("m_txtRate_EndVal"));
        sizePolicy1.setHeightForWidth(m_txtRate_EndVal->sizePolicy().hasHeightForWidth());
        m_txtRate_EndVal->setSizePolicy(sizePolicy1);
        m_txtRate_EndVal->setMinimumSize(QSize(170, 0));
        m_txtRate_EndVal->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_txtRate_EndVal);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_labRate_Step = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_Step->setObjectName(QString::fromUtf8("m_labRate_Step"));
        sizePolicy1.setHeightForWidth(m_labRate_Step->sizePolicy().hasHeightForWidth());
        m_labRate_Step->setSizePolicy(sizePolicy1);
        m_labRate_Step->setMinimumSize(QSize(170, 0));
        m_labRate_Step->setMaximumSize(QSize(170, 16777215));
        m_labRate_Step->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(m_labRate_Step);

        m_txtRate_Step = new QLineEdit(QDiffRateItemParaEditWidget);
        m_txtRate_Step->setObjectName(QString::fromUtf8("m_txtRate_Step"));
        sizePolicy1.setHeightForWidth(m_txtRate_Step->sizePolicy().hasHeightForWidth());
        m_txtRate_Step->setSizePolicy(sizePolicy1);
        m_txtRate_Step->setMinimumSize(QSize(170, 0));
        m_txtRate_Step->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_txtRate_Step);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labRate_Freq = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_Freq->setObjectName(QString::fromUtf8("m_labRate_Freq"));
        sizePolicy1.setHeightForWidth(m_labRate_Freq->sizePolicy().hasHeightForWidth());
        m_labRate_Freq->setSizePolicy(sizePolicy1);
        m_labRate_Freq->setMinimumSize(QSize(170, 0));
        m_labRate_Freq->setMaximumSize(QSize(170, 16777215));
        m_labRate_Freq->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(m_labRate_Freq);

        m_txtRate_Freq = new QLineEdit(QDiffRateItemParaEditWidget);
        m_txtRate_Freq->setObjectName(QString::fromUtf8("m_txtRate_Freq"));
        sizePolicy1.setHeightForWidth(m_txtRate_Freq->sizePolicy().hasHeightForWidth());
        m_txtRate_Freq->setSizePolicy(sizePolicy1);
        m_txtRate_Freq->setMinimumSize(QSize(170, 0));
        m_txtRate_Freq->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_txtRate_Freq);


        verticalLayout->addLayout(horizontalLayout_6);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_labRate_Ir = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_Ir->setObjectName(QString::fromUtf8("m_labRate_Ir"));
        sizePolicy1.setHeightForWidth(m_labRate_Ir->sizePolicy().hasHeightForWidth());
        m_labRate_Ir->setSizePolicy(sizePolicy1);
        m_labRate_Ir->setMinimumSize(QSize(170, 0));
        m_labRate_Ir->setMaximumSize(QSize(170, 16777215));
        m_labRate_Ir->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(m_labRate_Ir);

        m_txtRate_Ir = new QLineEdit(QDiffRateItemParaEditWidget);
        m_txtRate_Ir->setObjectName(QString::fromUtf8("m_txtRate_Ir"));
        sizePolicy1.setHeightForWidth(m_txtRate_Ir->sizePolicy().hasHeightForWidth());
        m_txtRate_Ir->setSizePolicy(sizePolicy1);
        m_txtRate_Ir->setMinimumSize(QSize(170, 0));
        m_txtRate_Ir->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_7->addWidget(m_txtRate_Ir);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        m_labRate_IdSetting = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_IdSetting->setObjectName(QString::fromUtf8("m_labRate_IdSetting"));
        sizePolicy1.setHeightForWidth(m_labRate_IdSetting->sizePolicy().hasHeightForWidth());
        m_labRate_IdSetting->setSizePolicy(sizePolicy1);
        m_labRate_IdSetting->setMinimumSize(QSize(170, 0));
        m_labRate_IdSetting->setMaximumSize(QSize(170, 16777215));
        m_labRate_IdSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(m_labRate_IdSetting);

        m_txtRate_IdSetting = new QLineEdit(QDiffRateItemParaEditWidget);
        m_txtRate_IdSetting->setObjectName(QString::fromUtf8("m_txtRate_IdSetting"));
        m_txtRate_IdSetting->setEnabled(false);
        sizePolicy1.setHeightForWidth(m_txtRate_IdSetting->sizePolicy().hasHeightForWidth());
        m_txtRate_IdSetting->setSizePolicy(sizePolicy1);
        m_txtRate_IdSetting->setMinimumSize(QSize(170, 0));
        m_txtRate_IdSetting->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_8->addWidget(m_txtRate_IdSetting);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        m_labRate_FaultTime = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_FaultTime->setObjectName(QString::fromUtf8("m_labRate_FaultTime"));
        sizePolicy1.setHeightForWidth(m_labRate_FaultTime->sizePolicy().hasHeightForWidth());
        m_labRate_FaultTime->setSizePolicy(sizePolicy1);
        m_labRate_FaultTime->setMinimumSize(QSize(170, 0));
        m_labRate_FaultTime->setMaximumSize(QSize(170, 16777215));
        m_labRate_FaultTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(m_labRate_FaultTime);

        m_txtRate_FaultTime = new QLineEdit(QDiffRateItemParaEditWidget);
        m_txtRate_FaultTime->setObjectName(QString::fromUtf8("m_txtRate_FaultTime"));
        sizePolicy1.setHeightForWidth(m_txtRate_FaultTime->sizePolicy().hasHeightForWidth());
        m_txtRate_FaultTime->setSizePolicy(sizePolicy1);
        m_txtRate_FaultTime->setMinimumSize(QSize(170, 0));
        m_txtRate_FaultTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_9->addWidget(m_txtRate_FaultTime);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        m_labRate_AbsErr = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_AbsErr->setObjectName(QString::fromUtf8("m_labRate_AbsErr"));
        sizePolicy1.setHeightForWidth(m_labRate_AbsErr->sizePolicy().hasHeightForWidth());
        m_labRate_AbsErr->setSizePolicy(sizePolicy1);
        m_labRate_AbsErr->setMinimumSize(QSize(170, 0));
        m_labRate_AbsErr->setMaximumSize(QSize(170, 16777215));
        m_labRate_AbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(m_labRate_AbsErr);

        m_txtRate_AbsErr = new QSettingLineEdit(QDiffRateItemParaEditWidget);
        m_txtRate_AbsErr->setObjectName(QString::fromUtf8("m_txtRate_AbsErr"));
        sizePolicy1.setHeightForWidth(m_txtRate_AbsErr->sizePolicy().hasHeightForWidth());
        m_txtRate_AbsErr->setSizePolicy(sizePolicy1);
        m_txtRate_AbsErr->setMinimumSize(QSize(170, 0));
        m_txtRate_AbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_10->addWidget(m_txtRate_AbsErr);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        m_labRate_RelErr = new QLabel(QDiffRateItemParaEditWidget);
        m_labRate_RelErr->setObjectName(QString::fromUtf8("m_labRate_RelErr"));
        sizePolicy1.setHeightForWidth(m_labRate_RelErr->sizePolicy().hasHeightForWidth());
        m_labRate_RelErr->setSizePolicy(sizePolicy1);
        m_labRate_RelErr->setMinimumSize(QSize(170, 0));
        m_labRate_RelErr->setMaximumSize(QSize(170, 16777215));
        m_labRate_RelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(m_labRate_RelErr);

        m_txtRate_RelErr = new QSettingLineEdit(QDiffRateItemParaEditWidget);
        m_txtRate_RelErr->setObjectName(QString::fromUtf8("m_txtRate_RelErr"));
        sizePolicy1.setHeightForWidth(m_txtRate_RelErr->sizePolicy().hasHeightForWidth());
        m_txtRate_RelErr->setSizePolicy(sizePolicy1);
        m_txtRate_RelErr->setMinimumSize(QSize(170, 0));
        m_txtRate_RelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_11->addWidget(m_txtRate_RelErr);


        verticalLayout_2->addLayout(horizontalLayout_11);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 4);
        horizontalLayout_2->setStretch(2, 2);
        horizontalLayout_2->setStretch(3, 4);
        horizontalLayout_2->setStretch(4, 1);

        retranslateUi(QDiffRateItemParaEditWidget);

        QMetaObject::connectSlotsByName(QDiffRateItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QDiffRateItemParaEditWidget)
    {
        QDiffRateItemParaEditWidget->setWindowTitle(QApplication::translate("QDiffRateItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_labRate_FaultType->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\346\225\205\351\232\234\347\233\270\345\210\253:", 0, QApplication::UnicodeUTF8));
        m_cmbRate_FaultType->clear();
        m_cmbRate_FaultType->insertItems(0, QStringList()
         << QApplication::translate("QDiffRateItemParaEditWidget", "A", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffRateItemParaEditWidget", "B", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffRateItemParaEditWidget", "C", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffRateItemParaEditWidget", "ABC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffRateItemParaEditWidget", "AB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffRateItemParaEditWidget", "BC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffRateItemParaEditWidget", "CA", 0, QApplication::UnicodeUTF8)
        );
        m_labRate_BeginVal->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\346\220\234\347\264\242\344\270\212\351\231\220(%):", 0, QApplication::UnicodeUTF8));
        m_labRate_EndVal->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\346\220\234\347\264\242\344\270\213\351\231\220(%):", 0, QApplication::UnicodeUTF8));
        m_labRate_Step->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\346\265\213\350\257\225\347\262\276\345\272\246():", 0, QApplication::UnicodeUTF8));
        m_labRate_Freq->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labRate_Ir->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\345\210\266\345\212\250\347\224\265\346\265\201Ir():", 0, QApplication::UnicodeUTF8));
        m_labRate_IdSetting->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\345\267\256\345\212\250\347\220\206\350\256\272\345\200\274Id():", 0, QApplication::UnicodeUTF8));
        m_labRate_FaultTime->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\346\234\200\345\244\247\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labRate_AbsErr->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256():", 0, QApplication::UnicodeUTF8));
        m_labRate_RelErr->setText(QApplication::translate("QDiffRateItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDiffRateItemParaEditWidget: public Ui_QDiffRateItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFRATEITEMPARAEDITWIDGET_H
