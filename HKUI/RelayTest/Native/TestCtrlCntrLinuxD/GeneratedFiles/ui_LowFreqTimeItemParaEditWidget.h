/********************************************************************************
** Form generated from reading UI file 'LowFreqTimeItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWFREQTIMEITEMPARAEDITWIDGET_H
#define UI_LOWFREQTIMEITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_QLowFreqTimeItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_15;
    QLabel *m_labTSetting;
    QSettingLineEdit *m_txtActTime_TSetting;
    QHBoxLayout *horizontalLayout_17;
    QLabel *m_labFSetting;
    QSettingLineEdit *m_txtActTime_FSetting;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_18;
    QLabel *m_labRelErr;
    QLineEdit *m_txtActTime_RelErr;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labAbsErrPos;
    QLineEdit *m_txtActTime_AbsErrPos;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labAbsErrNeg;
    QLineEdit *m_txtActTime_AbsErrNeg;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_20;
    QLabel *m_labFreqEnd;
    QLineEdit *m_txtActTime_FreqEnd;
    QHBoxLayout *horizontalLayout_21;
    QLabel *m_labdfdt;
    QSettingLineEdit *m_txtActTime_dfdt;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_22;
    QLabel *m_labCur;
    QLineEdit *m_txtActTime_Cur;
    QHBoxLayout *horizontalLayout_23;
    QLabel *m_labHoldTime;
    QLineEdit *m_txtActTime_HoldTime;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QLowFreqTimeItemParaEditWidget)
    {
        if (QLowFreqTimeItemParaEditWidget->objectName().isEmpty())
            QLowFreqTimeItemParaEditWidget->setObjectName(QString::fromUtf8("QLowFreqTimeItemParaEditWidget"));
        QLowFreqTimeItemParaEditWidget->resize(1048, 419);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QLowFreqTimeItemParaEditWidget->sizePolicy().hasHeightForWidth());
        QLowFreqTimeItemParaEditWidget->setSizePolicy(sizePolicy);
        QLowFreqTimeItemParaEditWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(QLowFreqTimeItemParaEditWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_2 = new QFrame(QLowFreqTimeItemParaEditWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_9 = new QVBoxLayout(groupBox);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(9, -1, 9, -1);
        m_labTSetting = new QLabel(groupBox);
        m_labTSetting->setObjectName(QString::fromUtf8("m_labTSetting"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_labTSetting->sizePolicy().hasHeightForWidth());
        m_labTSetting->setSizePolicy(sizePolicy2);
        m_labTSetting->setMinimumSize(QSize(170, 0));
        m_labTSetting->setMaximumSize(QSize(170, 16777215));
        m_labTSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(m_labTSetting);

        m_txtActTime_TSetting = new QSettingLineEdit(groupBox);
        m_txtActTime_TSetting->setObjectName(QString::fromUtf8("m_txtActTime_TSetting"));
        sizePolicy2.setHeightForWidth(m_txtActTime_TSetting->sizePolicy().hasHeightForWidth());
        m_txtActTime_TSetting->setSizePolicy(sizePolicy2);
        m_txtActTime_TSetting->setMinimumSize(QSize(170, 0));
        m_txtActTime_TSetting->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_15->addWidget(m_txtActTime_TSetting);


        verticalLayout_9->addLayout(horizontalLayout_15);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(9, -1, 9, -1);
        m_labFSetting = new QLabel(groupBox);
        m_labFSetting->setObjectName(QString::fromUtf8("m_labFSetting"));
        sizePolicy2.setHeightForWidth(m_labFSetting->sizePolicy().hasHeightForWidth());
        m_labFSetting->setSizePolicy(sizePolicy2);
        m_labFSetting->setMinimumSize(QSize(170, 0));
        m_labFSetting->setMaximumSize(QSize(170, 16777215));
        m_labFSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_17->addWidget(m_labFSetting);

        m_txtActTime_FSetting = new QSettingLineEdit(groupBox);
        m_txtActTime_FSetting->setObjectName(QString::fromUtf8("m_txtActTime_FSetting"));
        sizePolicy2.setHeightForWidth(m_txtActTime_FSetting->sizePolicy().hasHeightForWidth());
        m_txtActTime_FSetting->setSizePolicy(sizePolicy2);
        m_txtActTime_FSetting->setMinimumSize(QSize(170, 0));
        m_txtActTime_FSetting->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_17->addWidget(m_txtActTime_FSetting);


        verticalLayout_9->addLayout(horizontalLayout_17);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addWidget(frame_2);

        frame = new QFrame(QLowFreqTimeItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(9, -1, 9, -1);
        m_labRelErr = new QLabel(frame);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy2.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy2);
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_18->addWidget(m_labRelErr);

        m_txtActTime_RelErr = new QLineEdit(frame);
        m_txtActTime_RelErr->setObjectName(QString::fromUtf8("m_txtActTime_RelErr"));
        sizePolicy2.setHeightForWidth(m_txtActTime_RelErr->sizePolicy().hasHeightForWidth());
        m_txtActTime_RelErr->setSizePolicy(sizePolicy2);
        m_txtActTime_RelErr->setMinimumSize(QSize(170, 0));
        m_txtActTime_RelErr->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_18->addWidget(m_txtActTime_RelErr);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, -1, 9, -1);
        m_labAbsErrPos = new QLabel(frame);
        m_labAbsErrPos->setObjectName(QString::fromUtf8("m_labAbsErrPos"));
        sizePolicy2.setHeightForWidth(m_labAbsErrPos->sizePolicy().hasHeightForWidth());
        m_labAbsErrPos->setSizePolicy(sizePolicy2);
        m_labAbsErrPos->setMinimumSize(QSize(170, 0));
        m_labAbsErrPos->setMaximumSize(QSize(170, 16777215));
        m_labAbsErrPos->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_labAbsErrPos);

        m_txtActTime_AbsErrPos = new QLineEdit(frame);
        m_txtActTime_AbsErrPos->setObjectName(QString::fromUtf8("m_txtActTime_AbsErrPos"));
        sizePolicy2.setHeightForWidth(m_txtActTime_AbsErrPos->sizePolicy().hasHeightForWidth());
        m_txtActTime_AbsErrPos->setSizePolicy(sizePolicy2);
        m_txtActTime_AbsErrPos->setMinimumSize(QSize(170, 0));
        m_txtActTime_AbsErrPos->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_txtActTime_AbsErrPos);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(9, -1, 9, -1);
        m_labAbsErrNeg = new QLabel(frame);
        m_labAbsErrNeg->setObjectName(QString::fromUtf8("m_labAbsErrNeg"));
        sizePolicy2.setHeightForWidth(m_labAbsErrNeg->sizePolicy().hasHeightForWidth());
        m_labAbsErrNeg->setSizePolicy(sizePolicy2);
        m_labAbsErrNeg->setMinimumSize(QSize(170, 0));
        m_labAbsErrNeg->setMaximumSize(QSize(170, 16777215));
        m_labAbsErrNeg->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_labAbsErrNeg);

        m_txtActTime_AbsErrNeg = new QLineEdit(frame);
        m_txtActTime_AbsErrNeg->setObjectName(QString::fromUtf8("m_txtActTime_AbsErrNeg"));
        sizePolicy2.setHeightForWidth(m_txtActTime_AbsErrNeg->sizePolicy().hasHeightForWidth());
        m_txtActTime_AbsErrNeg->setSizePolicy(sizePolicy2);
        m_txtActTime_AbsErrNeg->setMinimumSize(QSize(170, 0));
        m_txtActTime_AbsErrNeg->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_txtActTime_AbsErrNeg);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(frame);

        verticalLayout_3->setStretch(0, 2);
        verticalLayout_3->setStretch(1, 3);

        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(318, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        frame_4 = new QFrame(QLowFreqTimeItemParaEditWidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(frame_4);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_10 = new QVBoxLayout(groupBox_2);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(9, -1, 9, -1);
        m_labFreqEnd = new QLabel(groupBox_2);
        m_labFreqEnd->setObjectName(QString::fromUtf8("m_labFreqEnd"));
        sizePolicy2.setHeightForWidth(m_labFreqEnd->sizePolicy().hasHeightForWidth());
        m_labFreqEnd->setSizePolicy(sizePolicy2);
        m_labFreqEnd->setMinimumSize(QSize(170, 0));
        m_labFreqEnd->setMaximumSize(QSize(170, 16777215));
        m_labFreqEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_20->addWidget(m_labFreqEnd);

        m_txtActTime_FreqEnd = new QLineEdit(groupBox_2);
        m_txtActTime_FreqEnd->setObjectName(QString::fromUtf8("m_txtActTime_FreqEnd"));
        sizePolicy2.setHeightForWidth(m_txtActTime_FreqEnd->sizePolicy().hasHeightForWidth());
        m_txtActTime_FreqEnd->setSizePolicy(sizePolicy2);
        m_txtActTime_FreqEnd->setMinimumSize(QSize(170, 0));
        m_txtActTime_FreqEnd->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_20->addWidget(m_txtActTime_FreqEnd);


        verticalLayout_10->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_21->setContentsMargins(9, -1, 9, -1);
        m_labdfdt = new QLabel(groupBox_2);
        m_labdfdt->setObjectName(QString::fromUtf8("m_labdfdt"));
        sizePolicy2.setHeightForWidth(m_labdfdt->sizePolicy().hasHeightForWidth());
        m_labdfdt->setSizePolicy(sizePolicy2);
        m_labdfdt->setMinimumSize(QSize(170, 0));
        m_labdfdt->setMaximumSize(QSize(170, 16777215));
        m_labdfdt->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_21->addWidget(m_labdfdt);

        m_txtActTime_dfdt = new QSettingLineEdit(groupBox_2);
        m_txtActTime_dfdt->setObjectName(QString::fromUtf8("m_txtActTime_dfdt"));
        sizePolicy2.setHeightForWidth(m_txtActTime_dfdt->sizePolicy().hasHeightForWidth());
        m_txtActTime_dfdt->setSizePolicy(sizePolicy2);
        m_txtActTime_dfdt->setMinimumSize(QSize(170, 0));
        m_txtActTime_dfdt->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_21->addWidget(m_txtActTime_dfdt);


        verticalLayout_10->addLayout(horizontalLayout_21);


        verticalLayout_5->addWidget(groupBox_2);


        verticalLayout_6->addWidget(frame_4);

        frame_3 = new QFrame(QLowFreqTimeItemParaEditWidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalLayout_22->setContentsMargins(9, -1, 9, -1);
        m_labCur = new QLabel(frame_3);
        m_labCur->setObjectName(QString::fromUtf8("m_labCur"));
        sizePolicy2.setHeightForWidth(m_labCur->sizePolicy().hasHeightForWidth());
        m_labCur->setSizePolicy(sizePolicy2);
        m_labCur->setMinimumSize(QSize(170, 0));
        m_labCur->setMaximumSize(QSize(170, 16777215));
        m_labCur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_22->addWidget(m_labCur);

        m_txtActTime_Cur = new QLineEdit(frame_3);
        m_txtActTime_Cur->setObjectName(QString::fromUtf8("m_txtActTime_Cur"));
        sizePolicy2.setHeightForWidth(m_txtActTime_Cur->sizePolicy().hasHeightForWidth());
        m_txtActTime_Cur->setSizePolicy(sizePolicy2);
        m_txtActTime_Cur->setMinimumSize(QSize(170, 0));
        m_txtActTime_Cur->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_22->addWidget(m_txtActTime_Cur);


        verticalLayout_4->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(9, -1, 9, -1);
        m_labHoldTime = new QLabel(frame_3);
        m_labHoldTime->setObjectName(QString::fromUtf8("m_labHoldTime"));
        sizePolicy2.setHeightForWidth(m_labHoldTime->sizePolicy().hasHeightForWidth());
        m_labHoldTime->setSizePolicy(sizePolicy2);
        m_labHoldTime->setMinimumSize(QSize(170, 0));
        m_labHoldTime->setMaximumSize(QSize(170, 16777215));
        m_labHoldTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_23->addWidget(m_labHoldTime);

        m_txtActTime_HoldTime = new QLineEdit(frame_3);
        m_txtActTime_HoldTime->setObjectName(QString::fromUtf8("m_txtActTime_HoldTime"));
        sizePolicy2.setHeightForWidth(m_txtActTime_HoldTime->sizePolicy().hasHeightForWidth());
        m_txtActTime_HoldTime->setSizePolicy(sizePolicy2);
        m_txtActTime_HoldTime->setMinimumSize(QSize(170, 0));
        m_txtActTime_HoldTime->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_23->addWidget(m_txtActTime_HoldTime);


        verticalLayout_4->addLayout(horizontalLayout_23);


        verticalLayout_6->addWidget(frame_3);

        verticalLayout_6->setStretch(0, 1);
        verticalLayout_6->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_6);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 4);
        horizontalLayout->setStretch(4, 1);

        retranslateUi(QLowFreqTimeItemParaEditWidget);

        QMetaObject::connectSlotsByName(QLowFreqTimeItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QLowFreqTimeItemParaEditWidget)
    {
        QLowFreqTimeItemParaEditWidget->setWindowTitle(QApplication::translate("QLowFreqTimeItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labTSetting->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\345\212\250\344\275\234\346\227\266\351\227\264\345\256\232\345\200\274(s):", 0, QApplication::UnicodeUTF8));
        m_labFSetting->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\351\242\221\347\216\207\345\212\250\344\275\234\345\200\274(Hz):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_txtActTime_RelErr->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "2.0", 0, QApplication::UnicodeUTF8));
        m_labAbsErrPos->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_txtActTime_AbsErrPos->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        m_labAbsErrNeg->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
        m_txtActTime_AbsErrNeg->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\351\242\221\347\216\207\345\217\230\345\214\226\350\214\203\345\233\264\345\217\212\345\205\266\345\217\230\345\214\226\347\216\207", 0, QApplication::UnicodeUTF8));
        m_labFreqEnd->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\351\242\221\347\216\207\345\217\230\345\214\226\347\273\210\345\200\274(Hz):", 0, QApplication::UnicodeUTF8));
        m_labdfdt->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\351\242\221\347\216\207\346\273\221\345\267\256(Hz/s):", 0, QApplication::UnicodeUTF8));
        m_labCur->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labHoldTime->setText(QApplication::translate("QLowFreqTimeItemParaEditWidget", "\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLowFreqTimeItemParaEditWidget: public Ui_QLowFreqTimeItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWFREQTIMEITEMPARAEDITWIDGET_H
