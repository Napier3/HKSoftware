/********************************************************************************
** Form generated from reading UI file 'LowFreqDfdtItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWFREQDFDTITEMPARAEDITWIDGET_H
#define UI_LOWFREQDFDTITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
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

class Ui_QLowFreqDfdtItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout_26;
    QLabel *m_labdfdtSetting;
    QSettingLineEdit *m_txtSlipTrip_dfdtSetting;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_30;
    QLabel *m_labCur;
    QLineEdit *m_txtSlipTrip_Cur;
    QHBoxLayout *horizontalLayout_27;
    QLabel *m_labHoldTime;
    QLineEdit *m_txtSlipTrip_HoldTime;
    QHBoxLayout *horizontalLayout_28;
    QLabel *m_labRelErr;
    QLineEdit *m_txtSlipTrip_RelErr;
    QHBoxLayout *horizontalLayout_29;
    QLabel *m_labAbsErr;
    QLineEdit *m_txtSlipTrip_AbsErr;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_13;
    QLabel *m_labFreqEnd;
    QSettingLineEdit *m_txtSlipTrip_FreqEnd;
    QHBoxLayout *horizontalLayout_14;
    QLabel *m_labdfdtStart;
    QSettingLineEdit *m_txtSlipTrip_dfdtStart;
    QHBoxLayout *horizontalLayout_16;
    QLabel *m_labdfdtEnd;
    QSettingLineEdit *m_txtSlipTrip_dfdtEnd;
    QHBoxLayout *horizontalLayout_24;
    QLabel *m_labdfdtStep;
    QSettingLineEdit *m_txtSlipTrip_dfdtStep;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QLowFreqDfdtItemParaEditWidget)
    {
        if (QLowFreqDfdtItemParaEditWidget->objectName().isEmpty())
            QLowFreqDfdtItemParaEditWidget->setObjectName(QString::fromUtf8("QLowFreqDfdtItemParaEditWidget"));
        QLowFreqDfdtItemParaEditWidget->resize(930, 342);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QLowFreqDfdtItemParaEditWidget->sizePolicy().hasHeightForWidth());
        QLowFreqDfdtItemParaEditWidget->setSizePolicy(sizePolicy);
        QLowFreqDfdtItemParaEditWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(QLowFreqDfdtItemParaEditWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_2 = new QFrame(QLowFreqDfdtItemParaEditWidget);
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
        gridLayout_9 = new QGridLayout(groupBox);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(9, -1, 9, -1);
        m_labdfdtSetting = new QLabel(groupBox);
        m_labdfdtSetting->setObjectName(QString::fromUtf8("m_labdfdtSetting"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_labdfdtSetting->sizePolicy().hasHeightForWidth());
        m_labdfdtSetting->setSizePolicy(sizePolicy2);
        m_labdfdtSetting->setMinimumSize(QSize(170, 0));
        m_labdfdtSetting->setMaximumSize(QSize(170, 16777215));
        m_labdfdtSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_26->addWidget(m_labdfdtSetting);

        m_txtSlipTrip_dfdtSetting = new QSettingLineEdit(groupBox);
        m_txtSlipTrip_dfdtSetting->setObjectName(QString::fromUtf8("m_txtSlipTrip_dfdtSetting"));
        sizePolicy2.setHeightForWidth(m_txtSlipTrip_dfdtSetting->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_dfdtSetting->setSizePolicy(sizePolicy2);
        m_txtSlipTrip_dfdtSetting->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_dfdtSetting->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_26->addWidget(m_txtSlipTrip_dfdtSetting);


        gridLayout_9->addLayout(horizontalLayout_26, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addWidget(frame_2);

        frame = new QFrame(QLowFreqDfdtItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        horizontalLayout_30->setContentsMargins(9, -1, 9, -1);
        m_labCur = new QLabel(frame);
        m_labCur->setObjectName(QString::fromUtf8("m_labCur"));
        sizePolicy2.setHeightForWidth(m_labCur->sizePolicy().hasHeightForWidth());
        m_labCur->setSizePolicy(sizePolicy2);
        m_labCur->setMinimumSize(QSize(170, 0));
        m_labCur->setMaximumSize(QSize(170, 16777215));
        m_labCur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_30->addWidget(m_labCur);

        m_txtSlipTrip_Cur = new QLineEdit(frame);
        m_txtSlipTrip_Cur->setObjectName(QString::fromUtf8("m_txtSlipTrip_Cur"));
        sizePolicy2.setHeightForWidth(m_txtSlipTrip_Cur->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_Cur->setSizePolicy(sizePolicy2);
        m_txtSlipTrip_Cur->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_Cur->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_30->addWidget(m_txtSlipTrip_Cur);


        verticalLayout->addLayout(horizontalLayout_30);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(9, -1, 9, -1);
        m_labHoldTime = new QLabel(frame);
        m_labHoldTime->setObjectName(QString::fromUtf8("m_labHoldTime"));
        sizePolicy2.setHeightForWidth(m_labHoldTime->sizePolicy().hasHeightForWidth());
        m_labHoldTime->setSizePolicy(sizePolicy2);
        m_labHoldTime->setMinimumSize(QSize(170, 0));
        m_labHoldTime->setMaximumSize(QSize(170, 16777215));
        m_labHoldTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_27->addWidget(m_labHoldTime);

        m_txtSlipTrip_HoldTime = new QLineEdit(frame);
        m_txtSlipTrip_HoldTime->setObjectName(QString::fromUtf8("m_txtSlipTrip_HoldTime"));
        sizePolicy2.setHeightForWidth(m_txtSlipTrip_HoldTime->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_HoldTime->setSizePolicy(sizePolicy2);
        m_txtSlipTrip_HoldTime->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_HoldTime->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_27->addWidget(m_txtSlipTrip_HoldTime);


        verticalLayout->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(9, -1, 9, -1);
        m_labRelErr = new QLabel(frame);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy2.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy2);
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_28->addWidget(m_labRelErr);

        m_txtSlipTrip_RelErr = new QLineEdit(frame);
        m_txtSlipTrip_RelErr->setObjectName(QString::fromUtf8("m_txtSlipTrip_RelErr"));
        sizePolicy2.setHeightForWidth(m_txtSlipTrip_RelErr->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_RelErr->setSizePolicy(sizePolicy2);
        m_txtSlipTrip_RelErr->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_RelErr->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_28->addWidget(m_txtSlipTrip_RelErr);


        verticalLayout->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(9, -1, 9, -1);
        m_labAbsErr = new QLabel(frame);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        sizePolicy2.setHeightForWidth(m_labAbsErr->sizePolicy().hasHeightForWidth());
        m_labAbsErr->setSizePolicy(sizePolicy2);
        m_labAbsErr->setMinimumSize(QSize(170, 0));
        m_labAbsErr->setMaximumSize(QSize(170, 16777215));
        m_labAbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_29->addWidget(m_labAbsErr);

        m_txtSlipTrip_AbsErr = new QLineEdit(frame);
        m_txtSlipTrip_AbsErr->setObjectName(QString::fromUtf8("m_txtSlipTrip_AbsErr"));
        sizePolicy2.setHeightForWidth(m_txtSlipTrip_AbsErr->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_AbsErr->setSizePolicy(sizePolicy2);
        m_txtSlipTrip_AbsErr->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_AbsErr->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_29->addWidget(m_txtSlipTrip_AbsErr);


        verticalLayout->addLayout(horizontalLayout_29);


        verticalLayout_3->addWidget(frame);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 4);

        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(297, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupBox_2 = new QGroupBox(QLowFreqDfdtItemParaEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_12 = new QVBoxLayout(groupBox_2);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(9, -1, 9, -1);
        m_labFreqEnd = new QLabel(groupBox_2);
        m_labFreqEnd->setObjectName(QString::fromUtf8("m_labFreqEnd"));
        sizePolicy2.setHeightForWidth(m_labFreqEnd->sizePolicy().hasHeightForWidth());
        m_labFreqEnd->setSizePolicy(sizePolicy2);
        m_labFreqEnd->setMinimumSize(QSize(170, 0));
        m_labFreqEnd->setMaximumSize(QSize(170, 16777215));
        m_labFreqEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(m_labFreqEnd);

        m_txtSlipTrip_FreqEnd = new QSettingLineEdit(groupBox_2);
        m_txtSlipTrip_FreqEnd->setObjectName(QString::fromUtf8("m_txtSlipTrip_FreqEnd"));
        sizePolicy2.setHeightForWidth(m_txtSlipTrip_FreqEnd->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_FreqEnd->setSizePolicy(sizePolicy2);
        m_txtSlipTrip_FreqEnd->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_FreqEnd->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_13->addWidget(m_txtSlipTrip_FreqEnd);


        verticalLayout_12->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(9, -1, 9, -1);
        m_labdfdtStart = new QLabel(groupBox_2);
        m_labdfdtStart->setObjectName(QString::fromUtf8("m_labdfdtStart"));
        sizePolicy2.setHeightForWidth(m_labdfdtStart->sizePolicy().hasHeightForWidth());
        m_labdfdtStart->setSizePolicy(sizePolicy2);
        m_labdfdtStart->setMinimumSize(QSize(170, 0));
        m_labdfdtStart->setMaximumSize(QSize(170, 16777215));
        m_labdfdtStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(m_labdfdtStart);

        m_txtSlipTrip_dfdtStart = new QSettingLineEdit(groupBox_2);
        m_txtSlipTrip_dfdtStart->setObjectName(QString::fromUtf8("m_txtSlipTrip_dfdtStart"));
        sizePolicy2.setHeightForWidth(m_txtSlipTrip_dfdtStart->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_dfdtStart->setSizePolicy(sizePolicy2);
        m_txtSlipTrip_dfdtStart->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_dfdtStart->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_14->addWidget(m_txtSlipTrip_dfdtStart);


        verticalLayout_12->addLayout(horizontalLayout_14);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(9, -1, 9, -1);
        m_labdfdtEnd = new QLabel(groupBox_2);
        m_labdfdtEnd->setObjectName(QString::fromUtf8("m_labdfdtEnd"));
        sizePolicy2.setHeightForWidth(m_labdfdtEnd->sizePolicy().hasHeightForWidth());
        m_labdfdtEnd->setSizePolicy(sizePolicy2);
        m_labdfdtEnd->setMinimumSize(QSize(170, 0));
        m_labdfdtEnd->setMaximumSize(QSize(170, 16777215));
        m_labdfdtEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(m_labdfdtEnd);

        m_txtSlipTrip_dfdtEnd = new QSettingLineEdit(groupBox_2);
        m_txtSlipTrip_dfdtEnd->setObjectName(QString::fromUtf8("m_txtSlipTrip_dfdtEnd"));
        sizePolicy2.setHeightForWidth(m_txtSlipTrip_dfdtEnd->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_dfdtEnd->setSizePolicy(sizePolicy2);
        m_txtSlipTrip_dfdtEnd->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_dfdtEnd->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_16->addWidget(m_txtSlipTrip_dfdtEnd);


        verticalLayout_12->addLayout(horizontalLayout_16);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_24->setContentsMargins(9, -1, 9, -1);
        m_labdfdtStep = new QLabel(groupBox_2);
        m_labdfdtStep->setObjectName(QString::fromUtf8("m_labdfdtStep"));
        sizePolicy2.setHeightForWidth(m_labdfdtStep->sizePolicy().hasHeightForWidth());
        m_labdfdtStep->setSizePolicy(sizePolicy2);
        m_labdfdtStep->setMinimumSize(QSize(170, 0));
        m_labdfdtStep->setMaximumSize(QSize(170, 16777215));
        m_labdfdtStep->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_24->addWidget(m_labdfdtStep);

        m_txtSlipTrip_dfdtStep = new QSettingLineEdit(groupBox_2);
        m_txtSlipTrip_dfdtStep->setObjectName(QString::fromUtf8("m_txtSlipTrip_dfdtStep"));
        sizePolicy2.setHeightForWidth(m_txtSlipTrip_dfdtStep->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_dfdtStep->setSizePolicy(sizePolicy2);
        m_txtSlipTrip_dfdtStep->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_dfdtStep->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_24->addWidget(m_txtSlipTrip_dfdtStep);


        verticalLayout_12->addLayout(horizontalLayout_24);


        horizontalLayout->addWidget(groupBox_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 4);
        horizontalLayout->setStretch(4, 1);
        groupBox_2->raise();

        retranslateUi(QLowFreqDfdtItemParaEditWidget);

        QMetaObject::connectSlotsByName(QLowFreqDfdtItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QLowFreqDfdtItemParaEditWidget)
    {
        QLowFreqDfdtItemParaEditWidget->setWindowTitle(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labdfdtSetting->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\346\273\221\345\267\256\345\256\232\345\200\274(Hz/s):", 0, QApplication::UnicodeUTF8));
        m_labCur->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labHoldTime->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_txtSlipTrip_RelErr->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "2.0", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(Hz/s):", 0, QApplication::UnicodeUTF8));
        m_txtSlipTrip_AbsErr->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\351\200\222\345\217\230\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labFreqEnd->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\351\242\221\347\216\207\345\217\230\345\214\226\347\273\210\345\200\274(Hz):", 0, QApplication::UnicodeUTF8));
        m_labdfdtStart->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\346\273\221\345\267\256\345\217\230\345\214\226\345\247\213\345\200\274(Hz/s):", 0, QApplication::UnicodeUTF8));
        m_labdfdtEnd->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\346\273\221\345\267\256\345\217\230\345\214\226\347\273\210\345\200\274(Hz/s):", 0, QApplication::UnicodeUTF8));
        m_labdfdtStep->setText(QApplication::translate("QLowFreqDfdtItemParaEditWidget", "\346\273\221\345\267\256\345\217\230\345\214\226\346\255\245\351\225\277(Hz/s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLowFreqDfdtItemParaEditWidget: public Ui_QLowFreqDfdtItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWFREQDFDTITEMPARAEDITWIDGET_H
