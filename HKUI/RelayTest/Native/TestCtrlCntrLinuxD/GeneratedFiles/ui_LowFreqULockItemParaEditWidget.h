/********************************************************************************
** Form generated from reading UI file 'LowFreqULockItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWFREQULOCKITEMPARAEDITWIDGET_H
#define UI_LOWFREQULOCKITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QLowFreqULockItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_37;
    QLabel *m_labVBlockSetting;
    QSettingLineEdit *m_txtVBlock_VBlockSetting;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_32;
    QLabel *m_labCur;
    QLineEdit *m_txtVBlock_Cur;
    QHBoxLayout *horizontalLayout_33;
    QLabel *m_labHoldTime;
    QLineEdit *m_txtVBlock_HoldTime;
    QHBoxLayout *horizontalLayout_34;
    QLabel *m_labVBlock_Var;
    QComboBox *m_cmbVBlock_Var;
    QHBoxLayout *horizontalLayout_35;
    QLabel *m_labRelErr;
    QLineEdit *m_txtVBlock_RelErr;
    QHBoxLayout *horizontalLayout_36;
    QLabel *m_labAbsErr;
    QLineEdit *m_txtVBlock_AbsErr;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labVBegin;
    QSettingLineEdit *m_txtVBlock_VStart;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labVEnd;
    QSettingLineEdit *m_txtVBlock_VEnd;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labVStep;
    QSettingLineEdit *m_txtVBlock_VStep;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labdfdt;
    QSettingLineEdit *m_txtVBlock_dfdt;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labFreqEnd;
    QLineEdit *m_txtVBlock_FreqEnd;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QLowFreqULockItemParaEditWidget)
    {
        if (QLowFreqULockItemParaEditWidget->objectName().isEmpty())
            QLowFreqULockItemParaEditWidget->setObjectName(QString::fromUtf8("QLowFreqULockItemParaEditWidget"));
        QLowFreqULockItemParaEditWidget->resize(1034, 477);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QLowFreqULockItemParaEditWidget->sizePolicy().hasHeightForWidth());
        QLowFreqULockItemParaEditWidget->setSizePolicy(sizePolicy);
        QLowFreqULockItemParaEditWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(QLowFreqULockItemParaEditWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_2 = new QFrame(QLowFreqULockItemParaEditWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_13 = new QVBoxLayout(groupBox);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        horizontalLayout_37->setContentsMargins(9, -1, 9, -1);
        m_labVBlockSetting = new QLabel(groupBox);
        m_labVBlockSetting->setObjectName(QString::fromUtf8("m_labVBlockSetting"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_labVBlockSetting->sizePolicy().hasHeightForWidth());
        m_labVBlockSetting->setSizePolicy(sizePolicy1);
        m_labVBlockSetting->setMinimumSize(QSize(170, 0));
        m_labVBlockSetting->setMaximumSize(QSize(170, 16777215));
        m_labVBlockSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_37->addWidget(m_labVBlockSetting);

        m_txtVBlock_VBlockSetting = new QSettingLineEdit(groupBox);
        m_txtVBlock_VBlockSetting->setObjectName(QString::fromUtf8("m_txtVBlock_VBlockSetting"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_VBlockSetting->sizePolicy().hasHeightForWidth());
        m_txtVBlock_VBlockSetting->setSizePolicy(sizePolicy1);
        m_txtVBlock_VBlockSetting->setMinimumSize(QSize(170, 0));
        m_txtVBlock_VBlockSetting->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_37->addWidget(m_txtVBlock_VBlockSetting);


        verticalLayout_13->addLayout(horizontalLayout_37);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addWidget(frame_2);

        frame = new QFrame(QLowFreqULockItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        horizontalLayout_32->setContentsMargins(9, -1, 9, -1);
        m_labCur = new QLabel(frame);
        m_labCur->setObjectName(QString::fromUtf8("m_labCur"));
        sizePolicy1.setHeightForWidth(m_labCur->sizePolicy().hasHeightForWidth());
        m_labCur->setSizePolicy(sizePolicy1);
        m_labCur->setMinimumSize(QSize(170, 0));
        m_labCur->setMaximumSize(QSize(170, 16777215));
        m_labCur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_32->addWidget(m_labCur);

        m_txtVBlock_Cur = new QLineEdit(frame);
        m_txtVBlock_Cur->setObjectName(QString::fromUtf8("m_txtVBlock_Cur"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_Cur->sizePolicy().hasHeightForWidth());
        m_txtVBlock_Cur->setSizePolicy(sizePolicy1);
        m_txtVBlock_Cur->setMinimumSize(QSize(170, 0));
        m_txtVBlock_Cur->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_32->addWidget(m_txtVBlock_Cur);


        verticalLayout->addLayout(horizontalLayout_32);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        horizontalLayout_33->setContentsMargins(9, -1, 9, -1);
        m_labHoldTime = new QLabel(frame);
        m_labHoldTime->setObjectName(QString::fromUtf8("m_labHoldTime"));
        sizePolicy1.setHeightForWidth(m_labHoldTime->sizePolicy().hasHeightForWidth());
        m_labHoldTime->setSizePolicy(sizePolicy1);
        m_labHoldTime->setMinimumSize(QSize(170, 0));
        m_labHoldTime->setMaximumSize(QSize(170, 16777215));
        m_labHoldTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_33->addWidget(m_labHoldTime);

        m_txtVBlock_HoldTime = new QLineEdit(frame);
        m_txtVBlock_HoldTime->setObjectName(QString::fromUtf8("m_txtVBlock_HoldTime"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_HoldTime->sizePolicy().hasHeightForWidth());
        m_txtVBlock_HoldTime->setSizePolicy(sizePolicy1);
        m_txtVBlock_HoldTime->setMinimumSize(QSize(170, 0));
        m_txtVBlock_HoldTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_33->addWidget(m_txtVBlock_HoldTime);


        verticalLayout->addLayout(horizontalLayout_33);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        horizontalLayout_34->setContentsMargins(9, -1, 9, -1);
        m_labVBlock_Var = new QLabel(frame);
        m_labVBlock_Var->setObjectName(QString::fromUtf8("m_labVBlock_Var"));
        sizePolicy1.setHeightForWidth(m_labVBlock_Var->sizePolicy().hasHeightForWidth());
        m_labVBlock_Var->setSizePolicy(sizePolicy1);
        m_labVBlock_Var->setMinimumSize(QSize(170, 0));
        m_labVBlock_Var->setMaximumSize(QSize(170, 16777215));
        m_labVBlock_Var->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_34->addWidget(m_labVBlock_Var);

        m_cmbVBlock_Var = new QComboBox(frame);
        m_cmbVBlock_Var->setObjectName(QString::fromUtf8("m_cmbVBlock_Var"));
        sizePolicy1.setHeightForWidth(m_cmbVBlock_Var->sizePolicy().hasHeightForWidth());
        m_cmbVBlock_Var->setSizePolicy(sizePolicy1);
        m_cmbVBlock_Var->setMinimumSize(QSize(170, 0));
        m_cmbVBlock_Var->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_34->addWidget(m_cmbVBlock_Var);


        verticalLayout->addLayout(horizontalLayout_34);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        horizontalLayout_35->setContentsMargins(9, -1, 9, -1);
        m_labRelErr = new QLabel(frame);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy1.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy1);
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_35->addWidget(m_labRelErr);

        m_txtVBlock_RelErr = new QLineEdit(frame);
        m_txtVBlock_RelErr->setObjectName(QString::fromUtf8("m_txtVBlock_RelErr"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_RelErr->sizePolicy().hasHeightForWidth());
        m_txtVBlock_RelErr->setSizePolicy(sizePolicy1);
        m_txtVBlock_RelErr->setMinimumSize(QSize(170, 0));
        m_txtVBlock_RelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_35->addWidget(m_txtVBlock_RelErr);


        verticalLayout->addLayout(horizontalLayout_35);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        horizontalLayout_36->setContentsMargins(9, -1, 9, -1);
        m_labAbsErr = new QLabel(frame);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        sizePolicy1.setHeightForWidth(m_labAbsErr->sizePolicy().hasHeightForWidth());
        m_labAbsErr->setSizePolicy(sizePolicy1);
        m_labAbsErr->setMinimumSize(QSize(170, 0));
        m_labAbsErr->setMaximumSize(QSize(170, 16777215));
        m_labAbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_36->addWidget(m_labAbsErr);

        m_txtVBlock_AbsErr = new QLineEdit(frame);
        m_txtVBlock_AbsErr->setObjectName(QString::fromUtf8("m_txtVBlock_AbsErr"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_AbsErr->sizePolicy().hasHeightForWidth());
        m_txtVBlock_AbsErr->setSizePolicy(sizePolicy1);
        m_txtVBlock_AbsErr->setMinimumSize(QSize(170, 0));
        m_txtVBlock_AbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_36->addWidget(m_txtVBlock_AbsErr);


        verticalLayout->addLayout(horizontalLayout_36);


        verticalLayout_3->addWidget(frame);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 5);

        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(331, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupBox_2 = new QGroupBox(QLowFreqULockItemParaEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, -1, 9, -1);
        m_labVBegin = new QLabel(groupBox_2);
        m_labVBegin->setObjectName(QString::fromUtf8("m_labVBegin"));
        sizePolicy1.setHeightForWidth(m_labVBegin->sizePolicy().hasHeightForWidth());
        m_labVBegin->setSizePolicy(sizePolicy1);
        m_labVBegin->setMinimumSize(QSize(170, 0));
        m_labVBegin->setMaximumSize(QSize(170, 16777215));
        m_labVBegin->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_labVBegin);

        m_txtVBlock_VStart = new QSettingLineEdit(groupBox_2);
        m_txtVBlock_VStart->setObjectName(QString::fromUtf8("m_txtVBlock_VStart"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_VStart->sizePolicy().hasHeightForWidth());
        m_txtVBlock_VStart->setSizePolicy(sizePolicy1);
        m_txtVBlock_VStart->setMinimumSize(QSize(170, 0));
        m_txtVBlock_VStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_txtVBlock_VStart);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(9, -1, 9, -1);
        m_labVEnd = new QLabel(groupBox_2);
        m_labVEnd->setObjectName(QString::fromUtf8("m_labVEnd"));
        sizePolicy1.setHeightForWidth(m_labVEnd->sizePolicy().hasHeightForWidth());
        m_labVEnd->setSizePolicy(sizePolicy1);
        m_labVEnd->setMinimumSize(QSize(170, 0));
        m_labVEnd->setMaximumSize(QSize(170, 16777215));
        m_labVEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_labVEnd);

        m_txtVBlock_VEnd = new QSettingLineEdit(groupBox_2);
        m_txtVBlock_VEnd->setObjectName(QString::fromUtf8("m_txtVBlock_VEnd"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_VEnd->sizePolicy().hasHeightForWidth());
        m_txtVBlock_VEnd->setSizePolicy(sizePolicy1);
        m_txtVBlock_VEnd->setMinimumSize(QSize(170, 0));
        m_txtVBlock_VEnd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_txtVBlock_VEnd);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(9, -1, 9, -1);
        m_labVStep = new QLabel(groupBox_2);
        m_labVStep->setObjectName(QString::fromUtf8("m_labVStep"));
        sizePolicy1.setHeightForWidth(m_labVStep->sizePolicy().hasHeightForWidth());
        m_labVStep->setSizePolicy(sizePolicy1);
        m_labVStep->setMinimumSize(QSize(170, 0));
        m_labVStep->setMaximumSize(QSize(170, 16777215));
        m_labVStep->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(m_labVStep);

        m_txtVBlock_VStep = new QSettingLineEdit(groupBox_2);
        m_txtVBlock_VStep->setObjectName(QString::fromUtf8("m_txtVBlock_VStep"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_VStep->sizePolicy().hasHeightForWidth());
        m_txtVBlock_VStep->setSizePolicy(sizePolicy1);
        m_txtVBlock_VStep->setMinimumSize(QSize(170, 0));
        m_txtVBlock_VStep->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_txtVBlock_VStep);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(9, -1, 9, -1);
        m_labdfdt = new QLabel(groupBox_2);
        m_labdfdt->setObjectName(QString::fromUtf8("m_labdfdt"));
        sizePolicy1.setHeightForWidth(m_labdfdt->sizePolicy().hasHeightForWidth());
        m_labdfdt->setSizePolicy(sizePolicy1);
        m_labdfdt->setMinimumSize(QSize(170, 0));
        m_labdfdt->setMaximumSize(QSize(170, 16777215));
        m_labdfdt->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(m_labdfdt);

        m_txtVBlock_dfdt = new QSettingLineEdit(groupBox_2);
        m_txtVBlock_dfdt->setObjectName(QString::fromUtf8("m_txtVBlock_dfdt"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_dfdt->sizePolicy().hasHeightForWidth());
        m_txtVBlock_dfdt->setSizePolicy(sizePolicy1);
        m_txtVBlock_dfdt->setMinimumSize(QSize(170, 0));
        m_txtVBlock_dfdt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_txtVBlock_dfdt);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(9, -1, 9, -1);
        m_labFreqEnd = new QLabel(groupBox_2);
        m_labFreqEnd->setObjectName(QString::fromUtf8("m_labFreqEnd"));
        sizePolicy1.setHeightForWidth(m_labFreqEnd->sizePolicy().hasHeightForWidth());
        m_labFreqEnd->setSizePolicy(sizePolicy1);
        m_labFreqEnd->setMinimumSize(QSize(170, 0));
        m_labFreqEnd->setMaximumSize(QSize(170, 16777215));
        m_labFreqEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(m_labFreqEnd);

        m_txtVBlock_FreqEnd = new QLineEdit(groupBox_2);
        m_txtVBlock_FreqEnd->setObjectName(QString::fromUtf8("m_txtVBlock_FreqEnd"));
        sizePolicy1.setHeightForWidth(m_txtVBlock_FreqEnd->sizePolicy().hasHeightForWidth());
        m_txtVBlock_FreqEnd->setSizePolicy(sizePolicy1);
        m_txtVBlock_FreqEnd->setMinimumSize(QSize(170, 0));
        m_txtVBlock_FreqEnd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_txtVBlock_FreqEnd);


        verticalLayout_4->addLayout(horizontalLayout_6);


        horizontalLayout->addWidget(groupBox_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 4);
        horizontalLayout->setStretch(4, 1);

        retranslateUi(QLowFreqULockItemParaEditWidget);

        QMetaObject::connectSlotsByName(QLowFreqULockItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QLowFreqULockItemParaEditWidget)
    {
        QLowFreqULockItemParaEditWidget->setWindowTitle(QApplication::translate("QLowFreqULockItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QLowFreqULockItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labVBlockSetting->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\344\275\216\347\224\265\345\216\213\351\227\255\351\224\201\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labCur->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labHoldTime->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labVBlock_Var->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\347\224\265\345\216\213\345\217\230\345\214\226\351\207\217:", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_txtVBlock_RelErr->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "2.0", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(V):", 0, QApplication::UnicodeUTF8));
        m_txtVBlock_AbsErr->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QLowFreqULockItemParaEditWidget", "\351\200\222\345\217\230\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labVBegin->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\345\217\230\345\214\226\345\247\213\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labVEnd->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\345\217\230\345\214\226\347\273\210\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labVStep->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\345\217\230\345\214\226\346\255\245\351\225\277(V):", 0, QApplication::UnicodeUTF8));
        m_labdfdt->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\351\242\221\347\216\207\346\273\221\345\267\256(Hz/s):", 0, QApplication::UnicodeUTF8));
        m_labFreqEnd->setText(QApplication::translate("QLowFreqULockItemParaEditWidget", "\351\242\221\347\216\207\345\217\230\345\214\226\347\273\210\345\200\274(Hz):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLowFreqULockItemParaEditWidget: public Ui_QLowFreqULockItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWFREQULOCKITEMPARAEDITWIDGET_H
