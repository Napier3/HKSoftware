/********************************************************************************
** Form generated from reading UI file 'DiffHarmItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFHARMITEMPARAEDITWIDGET_H
#define UI_DIFFHARMITEMPARAEDITWIDGET_H

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

class Ui_QDiffHarmItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labHarm_FaultType;
    QComboBox *m_cmbHarm_FaultType;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labHarm_HarmIndex;
    QComboBox *m_cmbHarm_HarmIndex;
    QHBoxLayout *horizontalLayout_13;
    QLabel *m_labHarm_HarmIndex_2;
    QLineEdit *m_txtHarm_CustomHarmIndex;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labHarm_Id;
    QLineEdit *m_txtHarm_Id;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labHarm_BeginVal;
    QLineEdit *m_txtHarm_BeginVal;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labHarm_EndVal;
    QLineEdit *m_txtHarm_EndVal;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_labHarm_Step;
    QLineEdit *m_txtHarm_Step;
    QHBoxLayout *horizontalLayout_12;
    QLabel *m_labHarm_OutSide;
    QComboBox *m_cmbHarm_OutSide;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_labHarm_FaultTime;
    QLineEdit *m_txtHarm_FaultTime;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labHarm_AbsErr;
    QSettingLineEdit *m_txtHarm_AbsErrPos;
    QHBoxLayout *horizontalLayout_8;
    QLabel *m_labHarm_AbsErrNeg;
    QSettingLineEdit *m_txtHarm_AbsErrNeg;
    QHBoxLayout *horizontalLayout_11;
    QLabel *m_labHarm_RelErr;
    QSettingLineEdit *m_txtHarm_RelErr;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QDiffHarmItemParaEditWidget)
    {
        if (QDiffHarmItemParaEditWidget->objectName().isEmpty())
            QDiffHarmItemParaEditWidget->setObjectName(QString::fromUtf8("QDiffHarmItemParaEditWidget"));
        QDiffHarmItemParaEditWidget->resize(930, 342);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QDiffHarmItemParaEditWidget->sizePolicy().hasHeightForWidth());
        QDiffHarmItemParaEditWidget->setSizePolicy(sizePolicy);
        QDiffHarmItemParaEditWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout_10 = new QHBoxLayout(QDiffHarmItemParaEditWidget);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labHarm_FaultType = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_FaultType->setObjectName(QString::fromUtf8("m_labHarm_FaultType"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_labHarm_FaultType->sizePolicy().hasHeightForWidth());
        m_labHarm_FaultType->setSizePolicy(sizePolicy1);
        m_labHarm_FaultType->setMinimumSize(QSize(170, 0));
        m_labHarm_FaultType->setMaximumSize(QSize(170, 16777215));
        m_labHarm_FaultType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(m_labHarm_FaultType);

        m_cmbHarm_FaultType = new QComboBox(QDiffHarmItemParaEditWidget);
        m_cmbHarm_FaultType->setObjectName(QString::fromUtf8("m_cmbHarm_FaultType"));
        sizePolicy1.setHeightForWidth(m_cmbHarm_FaultType->sizePolicy().hasHeightForWidth());
        m_cmbHarm_FaultType->setSizePolicy(sizePolicy1);
        m_cmbHarm_FaultType->setMinimumSize(QSize(170, 0));
        m_cmbHarm_FaultType->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_cmbHarm_FaultType);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labHarm_HarmIndex = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_HarmIndex->setObjectName(QString::fromUtf8("m_labHarm_HarmIndex"));
        sizePolicy1.setHeightForWidth(m_labHarm_HarmIndex->sizePolicy().hasHeightForWidth());
        m_labHarm_HarmIndex->setSizePolicy(sizePolicy1);
        m_labHarm_HarmIndex->setMinimumSize(QSize(170, 0));
        m_labHarm_HarmIndex->setMaximumSize(QSize(170, 16777215));
        m_labHarm_HarmIndex->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_labHarm_HarmIndex);

        m_cmbHarm_HarmIndex = new QComboBox(QDiffHarmItemParaEditWidget);
        m_cmbHarm_HarmIndex->setObjectName(QString::fromUtf8("m_cmbHarm_HarmIndex"));
        sizePolicy1.setHeightForWidth(m_cmbHarm_HarmIndex->sizePolicy().hasHeightForWidth());
        m_cmbHarm_HarmIndex->setSizePolicy(sizePolicy1);
        m_cmbHarm_HarmIndex->setMinimumSize(QSize(170, 0));
        m_cmbHarm_HarmIndex->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_cmbHarm_HarmIndex);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        m_labHarm_HarmIndex_2 = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_HarmIndex_2->setObjectName(QString::fromUtf8("m_labHarm_HarmIndex_2"));
        sizePolicy1.setHeightForWidth(m_labHarm_HarmIndex_2->sizePolicy().hasHeightForWidth());
        m_labHarm_HarmIndex_2->setSizePolicy(sizePolicy1);
        m_labHarm_HarmIndex_2->setMinimumSize(QSize(170, 0));
        m_labHarm_HarmIndex_2->setMaximumSize(QSize(170, 16777215));
        m_labHarm_HarmIndex_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(m_labHarm_HarmIndex_2);

        m_txtHarm_CustomHarmIndex = new QLineEdit(QDiffHarmItemParaEditWidget);
        m_txtHarm_CustomHarmIndex->setObjectName(QString::fromUtf8("m_txtHarm_CustomHarmIndex"));
        m_txtHarm_CustomHarmIndex->setEnabled(false);
        sizePolicy1.setHeightForWidth(m_txtHarm_CustomHarmIndex->sizePolicy().hasHeightForWidth());
        m_txtHarm_CustomHarmIndex->setSizePolicy(sizePolicy1);
        m_txtHarm_CustomHarmIndex->setMinimumSize(QSize(170, 0));
        m_txtHarm_CustomHarmIndex->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_13->addWidget(m_txtHarm_CustomHarmIndex);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_labHarm_Id = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_Id->setObjectName(QString::fromUtf8("m_labHarm_Id"));
        sizePolicy1.setHeightForWidth(m_labHarm_Id->sizePolicy().hasHeightForWidth());
        m_labHarm_Id->setSizePolicy(sizePolicy1);
        m_labHarm_Id->setMinimumSize(QSize(170, 0));
        m_labHarm_Id->setMaximumSize(QSize(170, 16777215));
        m_labHarm_Id->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_labHarm_Id);

        m_txtHarm_Id = new QLineEdit(QDiffHarmItemParaEditWidget);
        m_txtHarm_Id->setObjectName(QString::fromUtf8("m_txtHarm_Id"));
        sizePolicy1.setHeightForWidth(m_txtHarm_Id->sizePolicy().hasHeightForWidth());
        m_txtHarm_Id->setSizePolicy(sizePolicy1);
        m_txtHarm_Id->setMinimumSize(QSize(170, 0));
        m_txtHarm_Id->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_txtHarm_Id);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_labHarm_BeginVal = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_BeginVal->setObjectName(QString::fromUtf8("m_labHarm_BeginVal"));
        sizePolicy1.setHeightForWidth(m_labHarm_BeginVal->sizePolicy().hasHeightForWidth());
        m_labHarm_BeginVal->setSizePolicy(sizePolicy1);
        m_labHarm_BeginVal->setMinimumSize(QSize(170, 0));
        m_labHarm_BeginVal->setMaximumSize(QSize(170, 16777215));
        m_labHarm_BeginVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(m_labHarm_BeginVal);

        m_txtHarm_BeginVal = new QLineEdit(QDiffHarmItemParaEditWidget);
        m_txtHarm_BeginVal->setObjectName(QString::fromUtf8("m_txtHarm_BeginVal"));
        sizePolicy1.setHeightForWidth(m_txtHarm_BeginVal->sizePolicy().hasHeightForWidth());
        m_txtHarm_BeginVal->setSizePolicy(sizePolicy1);
        m_txtHarm_BeginVal->setMinimumSize(QSize(170, 0));
        m_txtHarm_BeginVal->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_txtHarm_BeginVal);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_labHarm_EndVal = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_EndVal->setObjectName(QString::fromUtf8("m_labHarm_EndVal"));
        sizePolicy1.setHeightForWidth(m_labHarm_EndVal->sizePolicy().hasHeightForWidth());
        m_labHarm_EndVal->setSizePolicy(sizePolicy1);
        m_labHarm_EndVal->setMinimumSize(QSize(170, 0));
        m_labHarm_EndVal->setMaximumSize(QSize(170, 16777215));
        m_labHarm_EndVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(m_labHarm_EndVal);

        m_txtHarm_EndVal = new QLineEdit(QDiffHarmItemParaEditWidget);
        m_txtHarm_EndVal->setObjectName(QString::fromUtf8("m_txtHarm_EndVal"));
        sizePolicy1.setHeightForWidth(m_txtHarm_EndVal->sizePolicy().hasHeightForWidth());
        m_txtHarm_EndVal->setSizePolicy(sizePolicy1);
        m_txtHarm_EndVal->setMinimumSize(QSize(170, 0));
        m_txtHarm_EndVal->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_txtHarm_EndVal);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_10->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_labHarm_Step = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_Step->setObjectName(QString::fromUtf8("m_labHarm_Step"));
        sizePolicy1.setHeightForWidth(m_labHarm_Step->sizePolicy().hasHeightForWidth());
        m_labHarm_Step->setSizePolicy(sizePolicy1);
        m_labHarm_Step->setMinimumSize(QSize(170, 0));
        m_labHarm_Step->setMaximumSize(QSize(170, 16777215));
        m_labHarm_Step->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(m_labHarm_Step);

        m_txtHarm_Step = new QLineEdit(QDiffHarmItemParaEditWidget);
        m_txtHarm_Step->setObjectName(QString::fromUtf8("m_txtHarm_Step"));
        sizePolicy1.setHeightForWidth(m_txtHarm_Step->sizePolicy().hasHeightForWidth());
        m_txtHarm_Step->setSizePolicy(sizePolicy1);
        m_txtHarm_Step->setMinimumSize(QSize(170, 0));
        m_txtHarm_Step->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_7->addWidget(m_txtHarm_Step);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        m_labHarm_OutSide = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_OutSide->setObjectName(QString::fromUtf8("m_labHarm_OutSide"));
        sizePolicy1.setHeightForWidth(m_labHarm_OutSide->sizePolicy().hasHeightForWidth());
        m_labHarm_OutSide->setSizePolicy(sizePolicy1);
        m_labHarm_OutSide->setMinimumSize(QSize(170, 0));
        m_labHarm_OutSide->setMaximumSize(QSize(170, 16777215));
        m_labHarm_OutSide->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(m_labHarm_OutSide);

        m_cmbHarm_OutSide = new QComboBox(QDiffHarmItemParaEditWidget);
        m_cmbHarm_OutSide->setObjectName(QString::fromUtf8("m_cmbHarm_OutSide"));
        sizePolicy1.setHeightForWidth(m_cmbHarm_OutSide->sizePolicy().hasHeightForWidth());
        m_cmbHarm_OutSide->setSizePolicy(sizePolicy1);
        m_cmbHarm_OutSide->setMinimumSize(QSize(170, 0));
        m_cmbHarm_OutSide->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_12->addWidget(m_cmbHarm_OutSide);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        m_labHarm_FaultTime = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_FaultTime->setObjectName(QString::fromUtf8("m_labHarm_FaultTime"));
        sizePolicy1.setHeightForWidth(m_labHarm_FaultTime->sizePolicy().hasHeightForWidth());
        m_labHarm_FaultTime->setSizePolicy(sizePolicy1);
        m_labHarm_FaultTime->setMinimumSize(QSize(170, 0));
        m_labHarm_FaultTime->setMaximumSize(QSize(170, 16777215));
        m_labHarm_FaultTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(m_labHarm_FaultTime);

        m_txtHarm_FaultTime = new QLineEdit(QDiffHarmItemParaEditWidget);
        m_txtHarm_FaultTime->setObjectName(QString::fromUtf8("m_txtHarm_FaultTime"));
        sizePolicy1.setHeightForWidth(m_txtHarm_FaultTime->sizePolicy().hasHeightForWidth());
        m_txtHarm_FaultTime->setSizePolicy(sizePolicy1);
        m_txtHarm_FaultTime->setMinimumSize(QSize(170, 0));
        m_txtHarm_FaultTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_9->addWidget(m_txtHarm_FaultTime);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labHarm_AbsErr = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_AbsErr->setObjectName(QString::fromUtf8("m_labHarm_AbsErr"));
        sizePolicy1.setHeightForWidth(m_labHarm_AbsErr->sizePolicy().hasHeightForWidth());
        m_labHarm_AbsErr->setSizePolicy(sizePolicy1);
        m_labHarm_AbsErr->setMinimumSize(QSize(170, 0));
        m_labHarm_AbsErr->setMaximumSize(QSize(170, 16777215));
        m_labHarm_AbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(m_labHarm_AbsErr);

        m_txtHarm_AbsErrPos = new QSettingLineEdit(QDiffHarmItemParaEditWidget);
        m_txtHarm_AbsErrPos->setObjectName(QString::fromUtf8("m_txtHarm_AbsErrPos"));
        sizePolicy1.setHeightForWidth(m_txtHarm_AbsErrPos->sizePolicy().hasHeightForWidth());
        m_txtHarm_AbsErrPos->setSizePolicy(sizePolicy1);
        m_txtHarm_AbsErrPos->setMinimumSize(QSize(170, 0));
        m_txtHarm_AbsErrPos->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_txtHarm_AbsErrPos);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        m_labHarm_AbsErrNeg = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_AbsErrNeg->setObjectName(QString::fromUtf8("m_labHarm_AbsErrNeg"));
        sizePolicy1.setHeightForWidth(m_labHarm_AbsErrNeg->sizePolicy().hasHeightForWidth());
        m_labHarm_AbsErrNeg->setSizePolicy(sizePolicy1);
        m_labHarm_AbsErrNeg->setMinimumSize(QSize(170, 0));
        m_labHarm_AbsErrNeg->setMaximumSize(QSize(170, 16777215));
        m_labHarm_AbsErrNeg->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(m_labHarm_AbsErrNeg);

        m_txtHarm_AbsErrNeg = new QSettingLineEdit(QDiffHarmItemParaEditWidget);
        m_txtHarm_AbsErrNeg->setObjectName(QString::fromUtf8("m_txtHarm_AbsErrNeg"));
        sizePolicy1.setHeightForWidth(m_txtHarm_AbsErrNeg->sizePolicy().hasHeightForWidth());
        m_txtHarm_AbsErrNeg->setSizePolicy(sizePolicy1);
        m_txtHarm_AbsErrNeg->setMinimumSize(QSize(170, 0));
        m_txtHarm_AbsErrNeg->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_8->addWidget(m_txtHarm_AbsErrNeg);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        m_labHarm_RelErr = new QLabel(QDiffHarmItemParaEditWidget);
        m_labHarm_RelErr->setObjectName(QString::fromUtf8("m_labHarm_RelErr"));
        sizePolicy1.setHeightForWidth(m_labHarm_RelErr->sizePolicy().hasHeightForWidth());
        m_labHarm_RelErr->setSizePolicy(sizePolicy1);
        m_labHarm_RelErr->setMinimumSize(QSize(170, 0));
        m_labHarm_RelErr->setMaximumSize(QSize(170, 16777215));
        m_labHarm_RelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(m_labHarm_RelErr);

        m_txtHarm_RelErr = new QSettingLineEdit(QDiffHarmItemParaEditWidget);
        m_txtHarm_RelErr->setObjectName(QString::fromUtf8("m_txtHarm_RelErr"));
        sizePolicy1.setHeightForWidth(m_txtHarm_RelErr->sizePolicy().hasHeightForWidth());
        m_txtHarm_RelErr->setSizePolicy(sizePolicy1);
        m_txtHarm_RelErr->setMinimumSize(QSize(170, 0));
        m_txtHarm_RelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_11->addWidget(m_txtHarm_RelErr);


        verticalLayout_2->addLayout(horizontalLayout_11);


        horizontalLayout_10->addLayout(verticalLayout_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 4);
        horizontalLayout_10->setStretch(2, 2);
        horizontalLayout_10->setStretch(3, 4);
        horizontalLayout_10->setStretch(4, 1);

        retranslateUi(QDiffHarmItemParaEditWidget);

        QMetaObject::connectSlotsByName(QDiffHarmItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QDiffHarmItemParaEditWidget)
    {
        QDiffHarmItemParaEditWidget->setWindowTitle(QApplication::translate("QDiffHarmItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_labHarm_FaultType->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\346\225\205\351\232\234\347\233\270\345\210\253:", 0, QApplication::UnicodeUTF8));
        m_cmbHarm_FaultType->clear();
        m_cmbHarm_FaultType->insertItems(0, QStringList()
         << QApplication::translate("QDiffHarmItemParaEditWidget", "A", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "B", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "C", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "ABC", 0, QApplication::UnicodeUTF8)
        );
        m_labHarm_HarmIndex->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\350\260\220\346\263\242\346\254\241\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labHarm_HarmIndex_2->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\350\207\252\345\256\232\344\271\211\350\260\220\346\263\242\346\254\241\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labHarm_Id->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\345\267\256\345\212\250\347\224\265\346\265\201():", 0, QApplication::UnicodeUTF8));
        m_labHarm_BeginVal->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\346\220\234\347\264\242\345\247\213\345\200\274(%):", 0, QApplication::UnicodeUTF8));
        m_labHarm_EndVal->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\346\220\234\347\264\242\347\273\210\345\200\274(%):", 0, QApplication::UnicodeUTF8));
        m_labHarm_Step->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\346\265\213\350\257\225\347\262\276\345\272\246(Ixf/Id):", 0, QApplication::UnicodeUTF8));
        m_labHarm_OutSide->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\350\260\220\346\263\242\350\276\223\345\207\272\344\276\247:", 0, QApplication::UnicodeUTF8));
        m_cmbHarm_OutSide->clear();
        m_cmbHarm_OutSide->insertItems(0, QStringList()
         << QApplication::translate("QDiffHarmItemParaEditWidget", "IA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "IB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "IC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "IA\\IB\\IC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "IA2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "IB2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "IC2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDiffHarmItemParaEditWidget", "IA2\\IB2\\IC2", 0, QApplication::UnicodeUTF8)
        );
        m_labHarm_FaultTime->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\346\234\200\345\244\247\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labHarm_AbsErr->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_labHarm_AbsErrNeg->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
        m_labHarm_RelErr->setText(QApplication::translate("QDiffHarmItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDiffHarmItemParaEditWidget: public Ui_QDiffHarmItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFHARMITEMPARAEDITWIDGET_H
