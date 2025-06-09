/********************************************************************************
** Form generated from reading UI file 'LowVolTimeItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWVOLTIMEITEMPARAEDITWIDGET_H
#define UI_LOWVOLTIMEITEMPARAEDITWIDGET_H

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

class Ui_QLowVolTimeItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_18;
    QLabel *m_labTSetting;
    QSettingLineEdit *m_txtActTime_TSetting;
    QHBoxLayout *horizontalLayout_23;
    QLabel *m_labVSetting;
    QSettingLineEdit *m_txtActTime_FSetting;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_labRelErr;
    QLineEdit *m_txtActTime_RelErr;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labAbsErrPos;
    QLineEdit *m_txtActTime_AbsErrPos;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labAbsErrNeg;
    QLineEdit *m_txtActTime_AbsErrNeg;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_8;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_labVEnd;
    QSettingLineEdit *m_txtActTime_VEnd;
    QHBoxLayout *horizontalLayout_12;
    QLabel *m_labDvdt;
    QSettingLineEdit *m_txtActTime_dVdt;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_15;
    QLabel *m_labCur;
    QLineEdit *m_txtActTime_Cur;
    QHBoxLayout *horizontalLayout_17;
    QLabel *m_labHoldTime;
    QLineEdit *m_txtActTime_HoldTime;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QLowVolTimeItemParaEditWidget)
    {
        if (QLowVolTimeItemParaEditWidget->objectName().isEmpty())
            QLowVolTimeItemParaEditWidget->setObjectName(QString::fromUtf8("QLowVolTimeItemParaEditWidget"));
        QLowVolTimeItemParaEditWidget->resize(1071, 314);
        horizontalLayout = new QHBoxLayout(QLowVolTimeItemParaEditWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_2 = new QFrame(QLowVolTimeItemParaEditWidget);
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
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(9, -1, 9, -1);
        m_labTSetting = new QLabel(groupBox);
        m_labTSetting->setObjectName(QString::fromUtf8("m_labTSetting"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labTSetting->sizePolicy().hasHeightForWidth());
        m_labTSetting->setSizePolicy(sizePolicy);
        m_labTSetting->setMinimumSize(QSize(170, 0));
        m_labTSetting->setMaximumSize(QSize(170, 16777215));
        m_labTSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_18->addWidget(m_labTSetting);

        m_txtActTime_TSetting = new QSettingLineEdit(groupBox);
        m_txtActTime_TSetting->setObjectName(QString::fromUtf8("m_txtActTime_TSetting"));
        sizePolicy.setHeightForWidth(m_txtActTime_TSetting->sizePolicy().hasHeightForWidth());
        m_txtActTime_TSetting->setSizePolicy(sizePolicy);
        m_txtActTime_TSetting->setMinimumSize(QSize(170, 0));
        m_txtActTime_TSetting->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_18->addWidget(m_txtActTime_TSetting);


        verticalLayout_4->addLayout(horizontalLayout_18);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(9, -1, 9, -1);
        m_labVSetting = new QLabel(groupBox);
        m_labVSetting->setObjectName(QString::fromUtf8("m_labVSetting"));
        sizePolicy.setHeightForWidth(m_labVSetting->sizePolicy().hasHeightForWidth());
        m_labVSetting->setSizePolicy(sizePolicy);
        m_labVSetting->setMinimumSize(QSize(170, 0));
        m_labVSetting->setMaximumSize(QSize(170, 16777215));
        m_labVSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_23->addWidget(m_labVSetting);

        m_txtActTime_FSetting = new QSettingLineEdit(groupBox);
        m_txtActTime_FSetting->setObjectName(QString::fromUtf8("m_txtActTime_FSetting"));
        sizePolicy.setHeightForWidth(m_txtActTime_FSetting->sizePolicy().hasHeightForWidth());
        m_txtActTime_FSetting->setSizePolicy(sizePolicy);
        m_txtActTime_FSetting->setMinimumSize(QSize(170, 0));
        m_txtActTime_FSetting->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_23->addWidget(m_txtActTime_FSetting);


        verticalLayout_4->addLayout(horizontalLayout_23);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addWidget(frame_2);

        frame = new QFrame(QLowVolTimeItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(9, -1, 9, -1);
        m_labRelErr = new QLabel(frame);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy);
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(m_labRelErr);

        m_txtActTime_RelErr = new QLineEdit(frame);
        m_txtActTime_RelErr->setObjectName(QString::fromUtf8("m_txtActTime_RelErr"));
        sizePolicy.setHeightForWidth(m_txtActTime_RelErr->sizePolicy().hasHeightForWidth());
        m_txtActTime_RelErr->setSizePolicy(sizePolicy);
        m_txtActTime_RelErr->setMinimumSize(QSize(170, 0));
        m_txtActTime_RelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_7->addWidget(m_txtActTime_RelErr);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, -1, 9, -1);
        m_labAbsErrPos = new QLabel(frame);
        m_labAbsErrPos->setObjectName(QString::fromUtf8("m_labAbsErrPos"));
        sizePolicy.setHeightForWidth(m_labAbsErrPos->sizePolicy().hasHeightForWidth());
        m_labAbsErrPos->setSizePolicy(sizePolicy);
        m_labAbsErrPos->setMinimumSize(QSize(170, 0));
        m_labAbsErrPos->setMaximumSize(QSize(170, 16777215));
        m_labAbsErrPos->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_labAbsErrPos);

        m_txtActTime_AbsErrPos = new QLineEdit(frame);
        m_txtActTime_AbsErrPos->setObjectName(QString::fromUtf8("m_txtActTime_AbsErrPos"));
        sizePolicy.setHeightForWidth(m_txtActTime_AbsErrPos->sizePolicy().hasHeightForWidth());
        m_txtActTime_AbsErrPos->setSizePolicy(sizePolicy);
        m_txtActTime_AbsErrPos->setMinimumSize(QSize(170, 0));
        m_txtActTime_AbsErrPos->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_txtActTime_AbsErrPos);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(9, -1, 9, -1);
        m_labAbsErrNeg = new QLabel(frame);
        m_labAbsErrNeg->setObjectName(QString::fromUtf8("m_labAbsErrNeg"));
        sizePolicy.setHeightForWidth(m_labAbsErrNeg->sizePolicy().hasHeightForWidth());
        m_labAbsErrNeg->setSizePolicy(sizePolicy);
        m_labAbsErrNeg->setMinimumSize(QSize(170, 0));
        m_labAbsErrNeg->setMaximumSize(QSize(170, 16777215));
        m_labAbsErrNeg->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_labAbsErrNeg);

        m_txtActTime_AbsErrNeg = new QLineEdit(frame);
        m_txtActTime_AbsErrNeg->setObjectName(QString::fromUtf8("m_txtActTime_AbsErrNeg"));
        sizePolicy.setHeightForWidth(m_txtActTime_AbsErrNeg->sizePolicy().hasHeightForWidth());
        m_txtActTime_AbsErrNeg->setSizePolicy(sizePolicy);
        m_txtActTime_AbsErrNeg->setMinimumSize(QSize(170, 0));
        m_txtActTime_AbsErrNeg->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_txtActTime_AbsErrNeg);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(frame);

        verticalLayout_3->setStretch(0, 2);
        verticalLayout_3->setStretch(1, 3);

        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(QLowVolTimeItemParaEditWidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_3);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(frame_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(9, -1, -1, -1);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(9, -1, 9, -1);
        m_labVEnd = new QLabel(groupBox_2);
        m_labVEnd->setObjectName(QString::fromUtf8("m_labVEnd"));
        sizePolicy.setHeightForWidth(m_labVEnd->sizePolicy().hasHeightForWidth());
        m_labVEnd->setSizePolicy(sizePolicy);
        m_labVEnd->setMinimumSize(QSize(170, 0));
        m_labVEnd->setMaximumSize(QSize(170, 16777215));
        m_labVEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(m_labVEnd);

        m_txtActTime_VEnd = new QSettingLineEdit(groupBox_2);
        m_txtActTime_VEnd->setObjectName(QString::fromUtf8("m_txtActTime_VEnd"));
        sizePolicy.setHeightForWidth(m_txtActTime_VEnd->sizePolicy().hasHeightForWidth());
        m_txtActTime_VEnd->setSizePolicy(sizePolicy);
        m_txtActTime_VEnd->setMinimumSize(QSize(170, 0));
        m_txtActTime_VEnd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_9->addWidget(m_txtActTime_VEnd);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(9, -1, 9, -1);
        m_labDvdt = new QLabel(groupBox_2);
        m_labDvdt->setObjectName(QString::fromUtf8("m_labDvdt"));
        sizePolicy.setHeightForWidth(m_labDvdt->sizePolicy().hasHeightForWidth());
        m_labDvdt->setSizePolicy(sizePolicy);
        m_labDvdt->setMinimumSize(QSize(170, 0));
        m_labDvdt->setMaximumSize(QSize(170, 16777215));
        m_labDvdt->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(m_labDvdt);

        m_txtActTime_dVdt = new QSettingLineEdit(groupBox_2);
        m_txtActTime_dVdt->setObjectName(QString::fromUtf8("m_txtActTime_dVdt"));
        sizePolicy.setHeightForWidth(m_txtActTime_dVdt->sizePolicy().hasHeightForWidth());
        m_txtActTime_dVdt->setSizePolicy(sizePolicy);
        m_txtActTime_dVdt->setMinimumSize(QSize(170, 0));
        m_txtActTime_dVdt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_12->addWidget(m_txtActTime_dVdt);


        verticalLayout_5->addLayout(horizontalLayout_12);


        verticalLayout_6->addWidget(groupBox_2);


        verticalLayout_8->addWidget(frame_3);

        frame_4 = new QFrame(QLowVolTimeItemParaEditWidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_4);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(9, -1, 9, -1);
        m_labCur = new QLabel(frame_4);
        m_labCur->setObjectName(QString::fromUtf8("m_labCur"));
        sizePolicy.setHeightForWidth(m_labCur->sizePolicy().hasHeightForWidth());
        m_labCur->setSizePolicy(sizePolicy);
        m_labCur->setMinimumSize(QSize(170, 0));
        m_labCur->setMaximumSize(QSize(170, 16777215));
        m_labCur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(m_labCur);

        m_txtActTime_Cur = new QLineEdit(frame_4);
        m_txtActTime_Cur->setObjectName(QString::fromUtf8("m_txtActTime_Cur"));
        sizePolicy.setHeightForWidth(m_txtActTime_Cur->sizePolicy().hasHeightForWidth());
        m_txtActTime_Cur->setSizePolicy(sizePolicy);
        m_txtActTime_Cur->setMinimumSize(QSize(170, 0));
        m_txtActTime_Cur->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_15->addWidget(m_txtActTime_Cur);


        verticalLayout_7->addLayout(horizontalLayout_15);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(9, -1, 9, -1);
        m_labHoldTime = new QLabel(frame_4);
        m_labHoldTime->setObjectName(QString::fromUtf8("m_labHoldTime"));
        sizePolicy.setHeightForWidth(m_labHoldTime->sizePolicy().hasHeightForWidth());
        m_labHoldTime->setSizePolicy(sizePolicy);
        m_labHoldTime->setMinimumSize(QSize(170, 0));
        m_labHoldTime->setMaximumSize(QSize(170, 16777215));
        m_labHoldTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_17->addWidget(m_labHoldTime);

        m_txtActTime_HoldTime = new QLineEdit(frame_4);
        m_txtActTime_HoldTime->setObjectName(QString::fromUtf8("m_txtActTime_HoldTime"));
        sizePolicy.setHeightForWidth(m_txtActTime_HoldTime->sizePolicy().hasHeightForWidth());
        m_txtActTime_HoldTime->setSizePolicy(sizePolicy);
        m_txtActTime_HoldTime->setMinimumSize(QSize(170, 0));
        m_txtActTime_HoldTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_17->addWidget(m_txtActTime_HoldTime);


        verticalLayout_7->addLayout(horizontalLayout_17);


        verticalLayout_8->addWidget(frame_4);

        verticalLayout_8->setStretch(0, 2);
        verticalLayout_8->setStretch(1, 3);

        horizontalLayout->addLayout(verticalLayout_8);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 4);
        horizontalLayout->setStretch(4, 1);

        retranslateUi(QLowVolTimeItemParaEditWidget);

        QMetaObject::connectSlotsByName(QLowVolTimeItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QLowVolTimeItemParaEditWidget)
    {
        QLowVolTimeItemParaEditWidget->setWindowTitle(QApplication::translate("QLowVolTimeItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QLowVolTimeItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labTSetting->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "\345\212\250\344\275\234\346\227\266\351\227\264\345\256\232\345\200\274(s):", 0, QApplication::UnicodeUTF8));
        m_labVSetting->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "\347\224\265\345\216\213\345\212\250\344\275\234\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_txtActTime_RelErr->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "2.0", 0, QApplication::UnicodeUTF8));
        m_labAbsErrPos->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_txtActTime_AbsErrPos->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        m_labAbsErrNeg->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
        m_txtActTime_AbsErrNeg->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QLowVolTimeItemParaEditWidget", "\347\224\265\345\216\213\345\217\230\345\214\226\350\214\203\345\233\264\345\217\212\345\205\266\345\217\230\345\214\226\347\216\207", 0, QApplication::UnicodeUTF8));
        m_labVEnd->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\345\217\230\345\214\226\347\273\210\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labDvdt->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\346\273\221\345\267\256(V/s):", 0, QApplication::UnicodeUTF8));
        m_labCur->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labHoldTime->setText(QApplication::translate("QLowVolTimeItemParaEditWidget", "\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLowVolTimeItemParaEditWidget: public Ui_QLowVolTimeItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWVOLTIMEITEMPARAEDITWIDGET_H
