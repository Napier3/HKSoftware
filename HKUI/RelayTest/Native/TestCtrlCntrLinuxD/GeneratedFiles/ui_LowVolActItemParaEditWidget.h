/********************************************************************************
** Form generated from reading UI file 'LowVolActItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWVOLACTITEMPARAEDITWIDGET_H
#define UI_LOWVOLACTITEMPARAEDITWIDGET_H

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

class Ui_QLowVolActItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labActValue;
    QSettingLineEdit *m_txtActValue_ActValue;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_11;
    QLabel *m_labCur;
    QLineEdit *m_txtActValue_Cur;
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
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_33;
    QLabel *m_labVBegin;
    QSettingLineEdit *m_txtActValue_VStart;
    QHBoxLayout *horizontalLayout_34;
    QLabel *m_labVEnd;
    QSettingLineEdit *m_txtActValue_VEnd;
    QHBoxLayout *horizontalLayout_35;
    QLabel *m_labVStep;
    QSettingLineEdit *m_txtActValue_VStep;
    QHBoxLayout *horizontalLayout_36;
    QLabel *m_labdvdt;
    QSettingLineEdit *m_txtActValue_dVdt;
    QHBoxLayout *horizontalLayout_37;
    QLabel *m_labVar;
    QComboBox *m_cmbActValue_Var;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QLowVolActItemParaEditWidget)
    {
        if (QLowVolActItemParaEditWidget->objectName().isEmpty())
            QLowVolActItemParaEditWidget->setObjectName(QString::fromUtf8("QLowVolActItemParaEditWidget"));
        QLowVolActItemParaEditWidget->resize(1054, 409);
        horizontalLayout_5 = new QHBoxLayout(QLowVolActItemParaEditWidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame = new QFrame(QLowVolActItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        groupBox->setContextMenuPolicy(Qt::DefaultContextMenu);
        groupBox->setStyleSheet(QString::fromUtf8("groupBox->setStyleSheet(\n"
"          \"QGroupBox:title\"\n"
"          \"{\"\n"
"          \"color:white;\"\n"
"          \"subcontrol-origin: margin;\"\n"
"          \"left: 10px;\"\n"
"          \"}\"\n"
"          );"));
        groupBox->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, -1, 9, -1);
        m_labActValue = new QLabel(groupBox);
        m_labActValue->setObjectName(QString::fromUtf8("m_labActValue"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_labActValue->sizePolicy().hasHeightForWidth());
        m_labActValue->setSizePolicy(sizePolicy1);
        m_labActValue->setMinimumSize(QSize(170, 0));
        m_labActValue->setMaximumSize(QSize(170, 16777215));
        m_labActValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(m_labActValue);

        m_txtActValue_ActValue = new QSettingLineEdit(groupBox);
        m_txtActValue_ActValue->setObjectName(QString::fromUtf8("m_txtActValue_ActValue"));
        sizePolicy1.setHeightForWidth(m_txtActValue_ActValue->sizePolicy().hasHeightForWidth());
        m_txtActValue_ActValue->setSizePolicy(sizePolicy1);
        m_txtActValue_ActValue->setMinimumSize(QSize(170, 0));
        m_txtActValue_ActValue->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_txtActValue_ActValue);


        horizontalLayout_6->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addWidget(frame);

        frame_2 = new QFrame(QLowVolActItemParaEditWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(9, -1, 9, -1);
        m_labCur = new QLabel(frame_2);
        m_labCur->setObjectName(QString::fromUtf8("m_labCur"));
        sizePolicy1.setHeightForWidth(m_labCur->sizePolicy().hasHeightForWidth());
        m_labCur->setSizePolicy(sizePolicy1);
        m_labCur->setMinimumSize(QSize(170, 0));
        m_labCur->setMaximumSize(QSize(170, 16777215));
        m_labCur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(m_labCur);

        m_txtActValue_Cur = new QLineEdit(frame_2);
        m_txtActValue_Cur->setObjectName(QString::fromUtf8("m_txtActValue_Cur"));
        sizePolicy1.setHeightForWidth(m_txtActValue_Cur->sizePolicy().hasHeightForWidth());
        m_txtActValue_Cur->setSizePolicy(sizePolicy1);
        m_txtActValue_Cur->setMinimumSize(QSize(170, 0));
        m_txtActValue_Cur->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_11->addWidget(m_txtActValue_Cur);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, -1, 9, -1);
        m_labHoldTime = new QLabel(frame_2);
        m_labHoldTime->setObjectName(QString::fromUtf8("m_labHoldTime"));
        sizePolicy1.setHeightForWidth(m_labHoldTime->sizePolicy().hasHeightForWidth());
        m_labHoldTime->setSizePolicy(sizePolicy1);
        m_labHoldTime->setMinimumSize(QSize(170, 0));
        m_labHoldTime->setMaximumSize(QSize(170, 16777215));
        m_labHoldTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_labHoldTime);

        m_txtActValue_HoldTime = new QLineEdit(frame_2);
        m_txtActValue_HoldTime->setObjectName(QString::fromUtf8("m_txtActValue_HoldTime"));
        sizePolicy1.setHeightForWidth(m_txtActValue_HoldTime->sizePolicy().hasHeightForWidth());
        m_txtActValue_HoldTime->setSizePolicy(sizePolicy1);
        m_txtActValue_HoldTime->setMinimumSize(QSize(170, 0));
        m_txtActValue_HoldTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_txtActValue_HoldTime);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(9, -1, 9, -1);
        m_labRelErr = new QLabel(frame_2);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy1.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy1);
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_labRelErr);

        m_txtActValue_RelErr = new QLineEdit(frame_2);
        m_txtActValue_RelErr->setObjectName(QString::fromUtf8("m_txtActValue_RelErr"));
        sizePolicy1.setHeightForWidth(m_txtActValue_RelErr->sizePolicy().hasHeightForWidth());
        m_txtActValue_RelErr->setSizePolicy(sizePolicy1);
        m_txtActValue_RelErr->setMinimumSize(QSize(170, 0));
        m_txtActValue_RelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_txtActValue_RelErr);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_4->setContentsMargins(9, -1, 9, -1);
        m_labAbsErr = new QLabel(frame_2);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        sizePolicy1.setHeightForWidth(m_labAbsErr->sizePolicy().hasHeightForWidth());
        m_labAbsErr->setSizePolicy(sizePolicy1);
        m_labAbsErr->setMinimumSize(QSize(170, 0));
        m_labAbsErr->setMaximumSize(QSize(170, 16777215));
        m_labAbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(m_labAbsErr);

        m_txtActValue_AbsErr = new QLineEdit(frame_2);
        m_txtActValue_AbsErr->setObjectName(QString::fromUtf8("m_txtActValue_AbsErr"));
        sizePolicy1.setHeightForWidth(m_txtActValue_AbsErr->sizePolicy().hasHeightForWidth());
        m_txtActValue_AbsErr->setSizePolicy(sizePolicy1);
        m_txtActValue_AbsErr->setMinimumSize(QSize(170, 0));
        m_txtActValue_AbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_txtActValue_AbsErr);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(frame_2);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 4);

        horizontalLayout_5->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        groupBox_2 = new QGroupBox(QLowVolActItemParaEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_10 = new QVBoxLayout(groupBox_2);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        horizontalLayout_33->setContentsMargins(9, -1, 9, -1);
        m_labVBegin = new QLabel(groupBox_2);
        m_labVBegin->setObjectName(QString::fromUtf8("m_labVBegin"));
        sizePolicy1.setHeightForWidth(m_labVBegin->sizePolicy().hasHeightForWidth());
        m_labVBegin->setSizePolicy(sizePolicy1);
        m_labVBegin->setMinimumSize(QSize(170, 0));
        m_labVBegin->setMaximumSize(QSize(170, 16777215));
        m_labVBegin->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_33->addWidget(m_labVBegin);

        m_txtActValue_VStart = new QSettingLineEdit(groupBox_2);
        m_txtActValue_VStart->setObjectName(QString::fromUtf8("m_txtActValue_VStart"));
        sizePolicy1.setHeightForWidth(m_txtActValue_VStart->sizePolicy().hasHeightForWidth());
        m_txtActValue_VStart->setSizePolicy(sizePolicy1);
        m_txtActValue_VStart->setMinimumSize(QSize(170, 0));
        m_txtActValue_VStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_33->addWidget(m_txtActValue_VStart);


        verticalLayout_10->addLayout(horizontalLayout_33);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        horizontalLayout_34->setContentsMargins(9, -1, 9, -1);
        m_labVEnd = new QLabel(groupBox_2);
        m_labVEnd->setObjectName(QString::fromUtf8("m_labVEnd"));
        sizePolicy1.setHeightForWidth(m_labVEnd->sizePolicy().hasHeightForWidth());
        m_labVEnd->setSizePolicy(sizePolicy1);
        m_labVEnd->setMinimumSize(QSize(170, 0));
        m_labVEnd->setMaximumSize(QSize(170, 16777215));
        m_labVEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_34->addWidget(m_labVEnd);

        m_txtActValue_VEnd = new QSettingLineEdit(groupBox_2);
        m_txtActValue_VEnd->setObjectName(QString::fromUtf8("m_txtActValue_VEnd"));
        sizePolicy1.setHeightForWidth(m_txtActValue_VEnd->sizePolicy().hasHeightForWidth());
        m_txtActValue_VEnd->setSizePolicy(sizePolicy1);
        m_txtActValue_VEnd->setMinimumSize(QSize(170, 0));
        m_txtActValue_VEnd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_34->addWidget(m_txtActValue_VEnd);


        verticalLayout_10->addLayout(horizontalLayout_34);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        horizontalLayout_35->setContentsMargins(9, -1, 9, -1);
        m_labVStep = new QLabel(groupBox_2);
        m_labVStep->setObjectName(QString::fromUtf8("m_labVStep"));
        sizePolicy1.setHeightForWidth(m_labVStep->sizePolicy().hasHeightForWidth());
        m_labVStep->setSizePolicy(sizePolicy1);
        m_labVStep->setMinimumSize(QSize(170, 0));
        m_labVStep->setMaximumSize(QSize(170, 16777215));
        m_labVStep->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_35->addWidget(m_labVStep);

        m_txtActValue_VStep = new QSettingLineEdit(groupBox_2);
        m_txtActValue_VStep->setObjectName(QString::fromUtf8("m_txtActValue_VStep"));
        sizePolicy1.setHeightForWidth(m_txtActValue_VStep->sizePolicy().hasHeightForWidth());
        m_txtActValue_VStep->setSizePolicy(sizePolicy1);
        m_txtActValue_VStep->setMinimumSize(QSize(170, 0));
        m_txtActValue_VStep->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_35->addWidget(m_txtActValue_VStep);


        verticalLayout_10->addLayout(horizontalLayout_35);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        horizontalLayout_36->setContentsMargins(9, -1, 9, -1);
        m_labdvdt = new QLabel(groupBox_2);
        m_labdvdt->setObjectName(QString::fromUtf8("m_labdvdt"));
        sizePolicy1.setHeightForWidth(m_labdvdt->sizePolicy().hasHeightForWidth());
        m_labdvdt->setSizePolicy(sizePolicy1);
        m_labdvdt->setMinimumSize(QSize(170, 0));
        m_labdvdt->setMaximumSize(QSize(170, 16777215));
        m_labdvdt->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_36->addWidget(m_labdvdt);

        m_txtActValue_dVdt = new QSettingLineEdit(groupBox_2);
        m_txtActValue_dVdt->setObjectName(QString::fromUtf8("m_txtActValue_dVdt"));
        sizePolicy1.setHeightForWidth(m_txtActValue_dVdt->sizePolicy().hasHeightForWidth());
        m_txtActValue_dVdt->setSizePolicy(sizePolicy1);
        m_txtActValue_dVdt->setMinimumSize(QSize(170, 0));
        m_txtActValue_dVdt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_36->addWidget(m_txtActValue_dVdt);


        verticalLayout_10->addLayout(horizontalLayout_36);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        horizontalLayout_37->setContentsMargins(9, -1, 9, -1);
        m_labVar = new QLabel(groupBox_2);
        m_labVar->setObjectName(QString::fromUtf8("m_labVar"));
        sizePolicy1.setHeightForWidth(m_labVar->sizePolicy().hasHeightForWidth());
        m_labVar->setSizePolicy(sizePolicy1);
        m_labVar->setMinimumSize(QSize(170, 0));
        m_labVar->setMaximumSize(QSize(170, 16777215));
        m_labVar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_37->addWidget(m_labVar);

        m_cmbActValue_Var = new QComboBox(groupBox_2);
        m_cmbActValue_Var->setObjectName(QString::fromUtf8("m_cmbActValue_Var"));
        sizePolicy1.setHeightForWidth(m_cmbActValue_Var->sizePolicy().hasHeightForWidth());
        m_cmbActValue_Var->setSizePolicy(sizePolicy1);
        m_cmbActValue_Var->setMinimumSize(QSize(170, 0));
        m_cmbActValue_Var->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_37->addWidget(m_cmbActValue_Var);


        verticalLayout_10->addLayout(horizontalLayout_37);


        horizontalLayout_5->addWidget(groupBox_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 4);
        horizontalLayout_5->setStretch(2, 2);
        horizontalLayout_5->setStretch(3, 4);
        horizontalLayout_5->setStretch(4, 1);

        retranslateUi(QLowVolActItemParaEditWidget);

        QMetaObject::connectSlotsByName(QLowVolActItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QLowVolActItemParaEditWidget)
    {
        QLowVolActItemParaEditWidget->setWindowTitle(QApplication::translate("QLowVolActItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QLowVolActItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labActValue->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\345\212\250\344\275\234\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labCur->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labHoldTime->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_txtActValue_RelErr->setText(QApplication::translate("QLowVolActItemParaEditWidget", "2.0", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(V):", 0, QApplication::UnicodeUTF8));
        m_txtActValue_AbsErr->setText(QApplication::translate("QLowVolActItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QLowVolActItemParaEditWidget", "\347\224\265\345\216\213\345\217\230\345\214\226\350\214\203\345\233\264\345\217\212\345\205\266\345\217\230\345\214\226\347\216\207", 0, QApplication::UnicodeUTF8));
        m_labVBegin->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\345\217\230\345\214\226\350\265\267\345\247\213\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labVEnd->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\345\217\230\345\214\226\347\273\223\346\235\237\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labVStep->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\345\217\230\345\214\226\346\255\245\351\225\277(V):", 0, QApplication::UnicodeUTF8));
        m_labdvdt->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\347\224\265\345\216\213\346\273\221\345\267\256(V/s):", 0, QApplication::UnicodeUTF8));
        m_labVar->setText(QApplication::translate("QLowVolActItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\345\217\230\345\214\226\351\207\217:", 0, QApplication::UnicodeUTF8));
        m_cmbActValue_Var->clear();
        m_cmbActValue_Var->insertItems(0, QStringList()
         << QApplication::translate("QLowVolActItemParaEditWidget", "Uab", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QLowVolActItemParaEditWidget", "Ubc", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QLowVolActItemParaEditWidget", "Uca", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QLowVolActItemParaEditWidget", "Uabc", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class QLowVolActItemParaEditWidget: public Ui_QLowVolActItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWVOLACTITEMPARAEDITWIDGET_H
