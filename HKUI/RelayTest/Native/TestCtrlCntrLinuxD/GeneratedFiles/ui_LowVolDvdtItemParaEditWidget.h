/********************************************************************************
** Form generated from reading UI file 'LowVolDvdtItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWVOLDVDTITEMPARAEDITWIDGET_H
#define UI_LOWVOLDVDTITEMPARAEDITWIDGET_H

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

class Ui_QLowVolDvdtItemParaEditWidget
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
    QLabel *m_labActValue;
    QSettingLineEdit *m_txtSlipTrip_dfdtSetting;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_30;
    QLabel *m_labCur;
    QSettingLineEdit *m_txtSlipTrip_Cur;
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
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_13;
    QLabel *m_labVEnd;
    QSettingLineEdit *m_txtSlipTrip_VEnd;
    QHBoxLayout *horizontalLayout_14;
    QLabel *m_labVStep;
    QSettingLineEdit *m_txtSlipTrip_VStep;
    QHBoxLayout *horizontalLayout_24;
    QLabel *m_labdfdtEnd;
    QSettingLineEdit *m_txtSlipTrip_dfdtEnd;
    QHBoxLayout *horizontalLayout_16;
    QLabel *m_labdfdtStart;
    QSettingLineEdit *m_txtSlipTrip_dfdtStart;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QLowVolDvdtItemParaEditWidget)
    {
        if (QLowVolDvdtItemParaEditWidget->objectName().isEmpty())
            QLowVolDvdtItemParaEditWidget->setObjectName(QString::fromUtf8("QLowVolDvdtItemParaEditWidget"));
        QLowVolDvdtItemParaEditWidget->resize(1087, 380);
        horizontalLayout = new QHBoxLayout(QLowVolDvdtItemParaEditWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_2 = new QFrame(QLowVolDvdtItemParaEditWidget);
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
        gridLayout_9 = new QGridLayout(groupBox);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(9, -1, 9, -1);
        m_labActValue = new QLabel(groupBox);
        m_labActValue->setObjectName(QString::fromUtf8("m_labActValue"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labActValue->sizePolicy().hasHeightForWidth());
        m_labActValue->setSizePolicy(sizePolicy);
        m_labActValue->setMinimumSize(QSize(170, 0));
        m_labActValue->setMaximumSize(QSize(170, 16777215));
        m_labActValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_26->addWidget(m_labActValue);

        m_txtSlipTrip_dfdtSetting = new QSettingLineEdit(groupBox);
        m_txtSlipTrip_dfdtSetting->setObjectName(QString::fromUtf8("m_txtSlipTrip_dfdtSetting"));
        sizePolicy.setHeightForWidth(m_txtSlipTrip_dfdtSetting->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_dfdtSetting->setSizePolicy(sizePolicy);
        m_txtSlipTrip_dfdtSetting->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_dfdtSetting->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_26->addWidget(m_txtSlipTrip_dfdtSetting);


        gridLayout_9->addLayout(horizontalLayout_26, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addWidget(frame_2);

        frame = new QFrame(QLowVolDvdtItemParaEditWidget);
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
        sizePolicy.setHeightForWidth(m_labCur->sizePolicy().hasHeightForWidth());
        m_labCur->setSizePolicy(sizePolicy);
        m_labCur->setMinimumSize(QSize(170, 0));
        m_labCur->setMaximumSize(QSize(170, 16777215));
        m_labCur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_30->addWidget(m_labCur);

        m_txtSlipTrip_Cur = new QSettingLineEdit(frame);
        m_txtSlipTrip_Cur->setObjectName(QString::fromUtf8("m_txtSlipTrip_Cur"));
        sizePolicy.setHeightForWidth(m_txtSlipTrip_Cur->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_Cur->setSizePolicy(sizePolicy);
        m_txtSlipTrip_Cur->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_Cur->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_30->addWidget(m_txtSlipTrip_Cur);


        verticalLayout->addLayout(horizontalLayout_30);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(9, -1, 9, -1);
        m_labHoldTime = new QLabel(frame);
        m_labHoldTime->setObjectName(QString::fromUtf8("m_labHoldTime"));
        sizePolicy.setHeightForWidth(m_labHoldTime->sizePolicy().hasHeightForWidth());
        m_labHoldTime->setSizePolicy(sizePolicy);
        m_labHoldTime->setMinimumSize(QSize(170, 0));
        m_labHoldTime->setMaximumSize(QSize(170, 16777215));
        m_labHoldTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_27->addWidget(m_labHoldTime);

        m_txtSlipTrip_HoldTime = new QLineEdit(frame);
        m_txtSlipTrip_HoldTime->setObjectName(QString::fromUtf8("m_txtSlipTrip_HoldTime"));
        sizePolicy.setHeightForWidth(m_txtSlipTrip_HoldTime->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_HoldTime->setSizePolicy(sizePolicy);
        m_txtSlipTrip_HoldTime->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_HoldTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_27->addWidget(m_txtSlipTrip_HoldTime);


        verticalLayout->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(9, -1, 9, -1);
        m_labRelErr = new QLabel(frame);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy);
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_28->addWidget(m_labRelErr);

        m_txtSlipTrip_RelErr = new QLineEdit(frame);
        m_txtSlipTrip_RelErr->setObjectName(QString::fromUtf8("m_txtSlipTrip_RelErr"));
        sizePolicy.setHeightForWidth(m_txtSlipTrip_RelErr->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_RelErr->setSizePolicy(sizePolicy);
        m_txtSlipTrip_RelErr->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_RelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_28->addWidget(m_txtSlipTrip_RelErr);


        verticalLayout->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(9, -1, 9, -1);
        m_labAbsErr = new QLabel(frame);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        sizePolicy.setHeightForWidth(m_labAbsErr->sizePolicy().hasHeightForWidth());
        m_labAbsErr->setSizePolicy(sizePolicy);
        m_labAbsErr->setMinimumSize(QSize(170, 0));
        m_labAbsErr->setMaximumSize(QSize(170, 16777215));
        m_labAbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_29->addWidget(m_labAbsErr);

        m_txtSlipTrip_AbsErr = new QLineEdit(frame);
        m_txtSlipTrip_AbsErr->setObjectName(QString::fromUtf8("m_txtSlipTrip_AbsErr"));
        sizePolicy.setHeightForWidth(m_txtSlipTrip_AbsErr->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_AbsErr->setSizePolicy(sizePolicy);
        m_txtSlipTrip_AbsErr->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_AbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_29->addWidget(m_txtSlipTrip_AbsErr);


        verticalLayout->addLayout(horizontalLayout_29);


        verticalLayout_3->addWidget(frame);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 4);

        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupBox_2 = new QGroupBox(QLowVolDvdtItemParaEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_8 = new QGridLayout(groupBox_2);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(9, -1, 9, -1);
        m_labVEnd = new QLabel(groupBox_2);
        m_labVEnd->setObjectName(QString::fromUtf8("m_labVEnd"));
        sizePolicy.setHeightForWidth(m_labVEnd->sizePolicy().hasHeightForWidth());
        m_labVEnd->setSizePolicy(sizePolicy);
        m_labVEnd->setMinimumSize(QSize(170, 0));
        m_labVEnd->setMaximumSize(QSize(170, 16777215));
        m_labVEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(m_labVEnd);

        m_txtSlipTrip_VEnd = new QSettingLineEdit(groupBox_2);
        m_txtSlipTrip_VEnd->setObjectName(QString::fromUtf8("m_txtSlipTrip_VEnd"));
        sizePolicy.setHeightForWidth(m_txtSlipTrip_VEnd->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_VEnd->setSizePolicy(sizePolicy);
        m_txtSlipTrip_VEnd->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_VEnd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_13->addWidget(m_txtSlipTrip_VEnd);


        gridLayout_8->addLayout(horizontalLayout_13, 0, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(9, -1, 9, -1);
        m_labVStep = new QLabel(groupBox_2);
        m_labVStep->setObjectName(QString::fromUtf8("m_labVStep"));
        sizePolicy.setHeightForWidth(m_labVStep->sizePolicy().hasHeightForWidth());
        m_labVStep->setSizePolicy(sizePolicy);
        m_labVStep->setMinimumSize(QSize(170, 0));
        m_labVStep->setMaximumSize(QSize(170, 16777215));
        m_labVStep->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(m_labVStep);

        m_txtSlipTrip_VStep = new QSettingLineEdit(groupBox_2);
        m_txtSlipTrip_VStep->setObjectName(QString::fromUtf8("m_txtSlipTrip_VStep"));
        sizePolicy.setHeightForWidth(m_txtSlipTrip_VStep->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_VStep->setSizePolicy(sizePolicy);
        m_txtSlipTrip_VStep->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_VStep->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_14->addWidget(m_txtSlipTrip_VStep);


        gridLayout_8->addLayout(horizontalLayout_14, 1, 0, 1, 1);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_24->setContentsMargins(9, -1, 9, -1);
        m_labdfdtEnd = new QLabel(groupBox_2);
        m_labdfdtEnd->setObjectName(QString::fromUtf8("m_labdfdtEnd"));
        sizePolicy.setHeightForWidth(m_labdfdtEnd->sizePolicy().hasHeightForWidth());
        m_labdfdtEnd->setSizePolicy(sizePolicy);
        m_labdfdtEnd->setMinimumSize(QSize(170, 0));
        m_labdfdtEnd->setMaximumSize(QSize(170, 16777215));
        m_labdfdtEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_24->addWidget(m_labdfdtEnd);

        m_txtSlipTrip_dfdtEnd = new QSettingLineEdit(groupBox_2);
        m_txtSlipTrip_dfdtEnd->setObjectName(QString::fromUtf8("m_txtSlipTrip_dfdtEnd"));
        sizePolicy.setHeightForWidth(m_txtSlipTrip_dfdtEnd->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_dfdtEnd->setSizePolicy(sizePolicy);
        m_txtSlipTrip_dfdtEnd->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_dfdtEnd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_24->addWidget(m_txtSlipTrip_dfdtEnd);


        gridLayout_8->addLayout(horizontalLayout_24, 3, 0, 1, 1);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(9, -1, 9, -1);
        m_labdfdtStart = new QLabel(groupBox_2);
        m_labdfdtStart->setObjectName(QString::fromUtf8("m_labdfdtStart"));
        sizePolicy.setHeightForWidth(m_labdfdtStart->sizePolicy().hasHeightForWidth());
        m_labdfdtStart->setSizePolicy(sizePolicy);
        m_labdfdtStart->setMinimumSize(QSize(170, 0));
        m_labdfdtStart->setMaximumSize(QSize(170, 16777215));
        m_labdfdtStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(m_labdfdtStart);

        m_txtSlipTrip_dfdtStart = new QSettingLineEdit(groupBox_2);
        m_txtSlipTrip_dfdtStart->setObjectName(QString::fromUtf8("m_txtSlipTrip_dfdtStart"));
        sizePolicy.setHeightForWidth(m_txtSlipTrip_dfdtStart->sizePolicy().hasHeightForWidth());
        m_txtSlipTrip_dfdtStart->setSizePolicy(sizePolicy);
        m_txtSlipTrip_dfdtStart->setMinimumSize(QSize(170, 0));
        m_txtSlipTrip_dfdtStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_16->addWidget(m_txtSlipTrip_dfdtStart);


        gridLayout_8->addLayout(horizontalLayout_16, 2, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 4);
        horizontalLayout->setStretch(4, 1);

        retranslateUi(QLowVolDvdtItemParaEditWidget);

        QMetaObject::connectSlotsByName(QLowVolDvdtItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QLowVolDvdtItemParaEditWidget)
    {
        QLowVolDvdtItemParaEditWidget->setWindowTitle(QApplication::translate("QLowVolDvdtItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labActValue->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\346\273\221\345\267\256\345\256\232\345\200\274df/dt(V/s):", 0, QApplication::UnicodeUTF8));
        m_labCur->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labHoldTime->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_txtSlipTrip_RelErr->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "2.0", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(V/s):", 0, QApplication::UnicodeUTF8));
        m_txtSlipTrip_AbsErr->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\351\200\222\345\217\230\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labVEnd->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\345\217\230\345\214\226\347\273\210\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labVStep->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\346\273\221\345\267\256\345\217\230\345\214\226\346\255\245\351\225\277(V/s):", 0, QApplication::UnicodeUTF8));
        m_labdfdtEnd->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\346\273\221\345\267\256\345\217\230\345\214\226\347\273\210\345\200\274(V/s):", 0, QApplication::UnicodeUTF8));
        m_labdfdtStart->setText(QApplication::translate("QLowVolDvdtItemParaEditWidget", "\346\273\221\345\267\256\345\217\230\345\214\226\345\247\213\345\200\274(V/s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLowVolDvdtItemParaEditWidget: public Ui_QLowVolDvdtItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWVOLDVDTITEMPARAEDITWIDGET_H
