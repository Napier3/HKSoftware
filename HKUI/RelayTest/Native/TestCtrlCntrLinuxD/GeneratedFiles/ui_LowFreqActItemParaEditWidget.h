/********************************************************************************
** Form generated from reading UI file 'LowFreqActItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWFREQACTITEMPARAEDITWIDGET_H
#define UI_LOWFREQACTITEMPARAEDITWIDGET_H

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

class Ui_QLowFreqActItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labActValue;
    QSettingLineEdit *m_txtActValue_ActValue;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *m_labCur;
    QSettingLineEdit *m_txtActValue_Cur;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labHoldTime;
    QLineEdit *m_txtActValue_HoldTime;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labRelErr;
    QLineEdit *m_txtActValue_RelErr;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labAbsErr;
    QLineEdit *m_txtActValue_AbsErr;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_labFreqStart;
    QSettingLineEdit *m_txtActValue_FreqStart;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labFreqEnd;
    QSettingLineEdit *m_txtActValue_FreqEnd;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_labFreqStep;
    QSettingLineEdit *m_txtActValue_FreqStep;
    QHBoxLayout *horizontalLayout_8;
    QLabel *m_labdvdt;
    QSettingLineEdit *m_txtActValue_dvdt;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QLowFreqActItemParaEditWidget)
    {
        if (QLowFreqActItemParaEditWidget->objectName().isEmpty())
            QLowFreqActItemParaEditWidget->setObjectName(QString::fromUtf8("QLowFreqActItemParaEditWidget"));
        QLowFreqActItemParaEditWidget->resize(1038, 446);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QLowFreqActItemParaEditWidget->sizePolicy().hasHeightForWidth());
        QLowFreqActItemParaEditWidget->setSizePolicy(sizePolicy);
        QLowFreqActItemParaEditWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout_5 = new QHBoxLayout(QLowFreqActItemParaEditWidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame = new QFrame(QLowFreqActItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, -1, 9, -1);
        m_labActValue = new QLabel(groupBox);
        m_labActValue->setObjectName(QString::fromUtf8("m_labActValue"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_labActValue->sizePolicy().hasHeightForWidth());
        m_labActValue->setSizePolicy(sizePolicy2);
        m_labActValue->setMinimumSize(QSize(170, 0));
        m_labActValue->setMaximumSize(QSize(170, 16777215));
        m_labActValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(m_labActValue);

        m_txtActValue_ActValue = new QSettingLineEdit(groupBox);
        m_txtActValue_ActValue->setObjectName(QString::fromUtf8("m_txtActValue_ActValue"));
        sizePolicy2.setHeightForWidth(m_txtActValue_ActValue->sizePolicy().hasHeightForWidth());
        m_txtActValue_ActValue->setSizePolicy(sizePolicy2);
        m_txtActValue_ActValue->setMinimumSize(QSize(170, 0));
        m_txtActValue_ActValue->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_txtActValue_ActValue);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);


        verticalLayout_3->addWidget(frame);

        frame_2 = new QFrame(QLowFreqActItemParaEditWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(9, -1, 9, -1);
        m_labCur = new QLabel(frame_2);
        m_labCur->setObjectName(QString::fromUtf8("m_labCur"));
        sizePolicy2.setHeightForWidth(m_labCur->sizePolicy().hasHeightForWidth());
        m_labCur->setSizePolicy(sizePolicy2);
        m_labCur->setMinimumSize(QSize(170, 0));
        m_labCur->setMaximumSize(QSize(170, 16777215));
        m_labCur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(m_labCur);

        m_txtActValue_Cur = new QSettingLineEdit(frame_2);
        m_txtActValue_Cur->setObjectName(QString::fromUtf8("m_txtActValue_Cur"));
        sizePolicy2.setHeightForWidth(m_txtActValue_Cur->sizePolicy().hasHeightForWidth());
        m_txtActValue_Cur->setSizePolicy(sizePolicy2);
        m_txtActValue_Cur->setMinimumSize(QSize(170, 0));
        m_txtActValue_Cur->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_11->addWidget(m_txtActValue_Cur);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, -1, 9, -1);
        m_labHoldTime = new QLabel(frame_2);
        m_labHoldTime->setObjectName(QString::fromUtf8("m_labHoldTime"));
        sizePolicy2.setHeightForWidth(m_labHoldTime->sizePolicy().hasHeightForWidth());
        m_labHoldTime->setSizePolicy(sizePolicy2);
        m_labHoldTime->setMinimumSize(QSize(170, 0));
        m_labHoldTime->setMaximumSize(QSize(170, 16777215));
        m_labHoldTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_labHoldTime);

        m_txtActValue_HoldTime = new QLineEdit(frame_2);
        m_txtActValue_HoldTime->setObjectName(QString::fromUtf8("m_txtActValue_HoldTime"));
        sizePolicy2.setHeightForWidth(m_txtActValue_HoldTime->sizePolicy().hasHeightForWidth());
        m_txtActValue_HoldTime->setSizePolicy(sizePolicy2);
        m_txtActValue_HoldTime->setMinimumSize(QSize(170, 0));
        m_txtActValue_HoldTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_txtActValue_HoldTime);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(9, -1, 9, -1);
        m_labRelErr = new QLabel(frame_2);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy2.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy2);
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_labRelErr);

        m_txtActValue_RelErr = new QLineEdit(frame_2);
        m_txtActValue_RelErr->setObjectName(QString::fromUtf8("m_txtActValue_RelErr"));
        sizePolicy2.setHeightForWidth(m_txtActValue_RelErr->sizePolicy().hasHeightForWidth());
        m_txtActValue_RelErr->setSizePolicy(sizePolicy2);
        m_txtActValue_RelErr->setMinimumSize(QSize(170, 0));
        m_txtActValue_RelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_txtActValue_RelErr);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(9, -1, 9, -1);
        m_labAbsErr = new QLabel(frame_2);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        sizePolicy2.setHeightForWidth(m_labAbsErr->sizePolicy().hasHeightForWidth());
        m_labAbsErr->setSizePolicy(sizePolicy2);
        m_labAbsErr->setMinimumSize(QSize(170, 0));
        m_labAbsErr->setMaximumSize(QSize(170, 16777215));
        m_labAbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(m_labAbsErr);

        m_txtActValue_AbsErr = new QLineEdit(frame_2);
        m_txtActValue_AbsErr->setObjectName(QString::fromUtf8("m_txtActValue_AbsErr"));
        sizePolicy2.setHeightForWidth(m_txtActValue_AbsErr->sizePolicy().hasHeightForWidth());
        m_txtActValue_AbsErr->setSizePolicy(sizePolicy2);
        m_txtActValue_AbsErr->setMinimumSize(QSize(170, 0));
        m_txtActValue_AbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_txtActValue_AbsErr);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(frame_2);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 4);

        horizontalLayout_5->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        groupBox_2 = new QGroupBox(QLowFreqActItemParaEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        verticalLayout_8 = new QVBoxLayout(groupBox_2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(9, -1, 9, -1);
        m_labFreqStart = new QLabel(groupBox_2);
        m_labFreqStart->setObjectName(QString::fromUtf8("m_labFreqStart"));
        sizePolicy2.setHeightForWidth(m_labFreqStart->sizePolicy().hasHeightForWidth());
        m_labFreqStart->setSizePolicy(sizePolicy2);
        m_labFreqStart->setMinimumSize(QSize(170, 0));
        m_labFreqStart->setMaximumSize(QSize(170, 16777215));
        m_labFreqStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(m_labFreqStart);

        m_txtActValue_FreqStart = new QSettingLineEdit(groupBox_2);
        m_txtActValue_FreqStart->setObjectName(QString::fromUtf8("m_txtActValue_FreqStart"));
        sizePolicy2.setHeightForWidth(m_txtActValue_FreqStart->sizePolicy().hasHeightForWidth());
        m_txtActValue_FreqStart->setSizePolicy(sizePolicy2);
        m_txtActValue_FreqStart->setMinimumSize(QSize(170, 0));
        m_txtActValue_FreqStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_9->addWidget(m_txtActValue_FreqStart);


        verticalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(9, -1, 9, -1);
        m_labFreqEnd = new QLabel(groupBox_2);
        m_labFreqEnd->setObjectName(QString::fromUtf8("m_labFreqEnd"));
        sizePolicy2.setHeightForWidth(m_labFreqEnd->sizePolicy().hasHeightForWidth());
        m_labFreqEnd->setSizePolicy(sizePolicy2);
        m_labFreqEnd->setMinimumSize(QSize(170, 0));
        m_labFreqEnd->setMaximumSize(QSize(170, 16777215));
        m_labFreqEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(m_labFreqEnd);

        m_txtActValue_FreqEnd = new QSettingLineEdit(groupBox_2);
        m_txtActValue_FreqEnd->setObjectName(QString::fromUtf8("m_txtActValue_FreqEnd"));
        sizePolicy2.setHeightForWidth(m_txtActValue_FreqEnd->sizePolicy().hasHeightForWidth());
        m_txtActValue_FreqEnd->setSizePolicy(sizePolicy2);
        m_txtActValue_FreqEnd->setMinimumSize(QSize(170, 0));
        m_txtActValue_FreqEnd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_txtActValue_FreqEnd);


        verticalLayout_8->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(9, -1, 9, -1);
        m_labFreqStep = new QLabel(groupBox_2);
        m_labFreqStep->setObjectName(QString::fromUtf8("m_labFreqStep"));
        sizePolicy2.setHeightForWidth(m_labFreqStep->sizePolicy().hasHeightForWidth());
        m_labFreqStep->setSizePolicy(sizePolicy2);
        m_labFreqStep->setMinimumSize(QSize(170, 0));
        m_labFreqStep->setMaximumSize(QSize(170, 16777215));
        m_labFreqStep->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(m_labFreqStep);

        m_txtActValue_FreqStep = new QSettingLineEdit(groupBox_2);
        m_txtActValue_FreqStep->setObjectName(QString::fromUtf8("m_txtActValue_FreqStep"));
        sizePolicy2.setHeightForWidth(m_txtActValue_FreqStep->sizePolicy().hasHeightForWidth());
        m_txtActValue_FreqStep->setSizePolicy(sizePolicy2);
        m_txtActValue_FreqStep->setMinimumSize(QSize(170, 0));
        m_txtActValue_FreqStep->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_7->addWidget(m_txtActValue_FreqStep);


        verticalLayout_8->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(9, -1, 9, -1);
        m_labdvdt = new QLabel(groupBox_2);
        m_labdvdt->setObjectName(QString::fromUtf8("m_labdvdt"));
        sizePolicy2.setHeightForWidth(m_labdvdt->sizePolicy().hasHeightForWidth());
        m_labdvdt->setSizePolicy(sizePolicy2);
        m_labdvdt->setMinimumSize(QSize(170, 0));
        m_labdvdt->setMaximumSize(QSize(170, 16777215));
        m_labdvdt->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(m_labdvdt);

        m_txtActValue_dvdt = new QSettingLineEdit(groupBox_2);
        m_txtActValue_dvdt->setObjectName(QString::fromUtf8("m_txtActValue_dvdt"));
        sizePolicy2.setHeightForWidth(m_txtActValue_dvdt->sizePolicy().hasHeightForWidth());
        m_txtActValue_dvdt->setSizePolicy(sizePolicy2);
        m_txtActValue_dvdt->setMinimumSize(QSize(170, 0));
        m_txtActValue_dvdt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_8->addWidget(m_txtActValue_dvdt);


        verticalLayout_8->addLayout(horizontalLayout_8);


        horizontalLayout_5->addWidget(groupBox_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 4);
        horizontalLayout_5->setStretch(2, 2);
        horizontalLayout_5->setStretch(3, 4);
        horizontalLayout_5->setStretch(4, 1);

        retranslateUi(QLowFreqActItemParaEditWidget);

        QMetaObject::connectSlotsByName(QLowFreqActItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QLowFreqActItemParaEditWidget)
    {
        QLowFreqActItemParaEditWidget->setWindowTitle(QApplication::translate("QLowFreqActItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QLowFreqActItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labActValue->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "\345\212\250\344\275\234\345\200\274(Hz):", 0, QApplication::UnicodeUTF8));
        m_labCur->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labHoldTime->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_txtActValue_RelErr->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "2.0", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(Hz):", 0, QApplication::UnicodeUTF8));
        m_txtActValue_AbsErr->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QLowFreqActItemParaEditWidget", "\351\242\221\347\216\207\345\217\230\345\214\226\350\214\203\345\233\264\345\217\212\345\205\266\345\217\230\345\214\226\347\216\207", 0, QApplication::UnicodeUTF8));
        m_labFreqStart->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "\351\242\221\347\216\207\350\265\267\345\247\213\345\200\274(Hz):", 0, QApplication::UnicodeUTF8));
        m_labFreqEnd->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "\351\242\221\347\216\207\347\273\223\346\235\237\345\200\274(Hz):", 0, QApplication::UnicodeUTF8));
        m_labFreqStep->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "\351\242\221\347\216\207\345\217\230\345\214\226\346\255\245\351\225\277(Hz):", 0, QApplication::UnicodeUTF8));
        m_labdvdt->setText(QApplication::translate("QLowFreqActItemParaEditWidget", "\351\242\221\347\216\207\346\273\221\345\267\256(Hz/s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLowFreqActItemParaEditWidget: public Ui_QLowFreqActItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWFREQACTITEMPARAEDITWIDGET_H
