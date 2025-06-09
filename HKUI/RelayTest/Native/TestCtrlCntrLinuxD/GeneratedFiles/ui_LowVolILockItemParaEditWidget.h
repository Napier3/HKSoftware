/********************************************************************************
** Form generated from reading UI file 'LowVolILockItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWVOLILOCKITEMPARAEDITWIDGET_H
#define UI_LOWVOLILOCKITEMPARAEDITWIDGET_H

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

class Ui_QLowVolILockItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_31;
    QHBoxLayout *horizontalLayout_48;
    QLabel *m_labIBlockSetting;
    QSettingLineEdit *m_txtIBlock_IBlockSetting;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labHoldTime;
    QLineEdit *m_txtIBlock_HoldTime;
    QHBoxLayout *horizontalLayout_21;
    QLabel *m_labIBlock_Var;
    QComboBox *m_cmbIBlock_Var;
    QHBoxLayout *horizontalLayout_22;
    QLabel *m_labRelErr;
    QLineEdit *m_txtIBlock_RelErr;
    QHBoxLayout *horizontalLayout_25;
    QLabel *m_labAbsErr;
    QLineEdit *m_txtIBlock_AbsErr;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_43;
    QLabel *m_labIStart;
    QSettingLineEdit *m_txtIBlock_IStart;
    QHBoxLayout *horizontalLayout_44;
    QLabel *m_labIEnd;
    QSettingLineEdit *m_txtIBlock_IEnd;
    QHBoxLayout *horizontalLayout_45;
    QLabel *m_labIStep;
    QSettingLineEdit *m_txtIBlock_IStep;
    QHBoxLayout *horizontalLayout_46;
    QLabel *m_labFreqEnd;
    QSettingLineEdit *m_txtIBlock_VEnd;
    QHBoxLayout *horizontalLayout_47;
    QLabel *m_labDvdt;
    QSettingLineEdit *m_txtIBlock_dVdt;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QLowVolILockItemParaEditWidget)
    {
        if (QLowVolILockItemParaEditWidget->objectName().isEmpty())
            QLowVolILockItemParaEditWidget->setObjectName(QString::fromUtf8("QLowVolILockItemParaEditWidget"));
        QLowVolILockItemParaEditWidget->resize(1065, 400);
        horizontalLayout = new QHBoxLayout(QLowVolILockItemParaEditWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_2 = new QFrame(QLowVolILockItemParaEditWidget);
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
        horizontalLayout_31 = new QHBoxLayout(groupBox);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        horizontalLayout_31->setContentsMargins(9, -1, -1, -1);
        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setObjectName(QString::fromUtf8("horizontalLayout_48"));
        horizontalLayout_48->setContentsMargins(9, -1, 9, -1);
        m_labIBlockSetting = new QLabel(groupBox);
        m_labIBlockSetting->setObjectName(QString::fromUtf8("m_labIBlockSetting"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labIBlockSetting->sizePolicy().hasHeightForWidth());
        m_labIBlockSetting->setSizePolicy(sizePolicy);
        m_labIBlockSetting->setMinimumSize(QSize(170, 0));
        m_labIBlockSetting->setMaximumSize(QSize(170, 16777215));
        m_labIBlockSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_48->addWidget(m_labIBlockSetting);

        m_txtIBlock_IBlockSetting = new QSettingLineEdit(groupBox);
        m_txtIBlock_IBlockSetting->setObjectName(QString::fromUtf8("m_txtIBlock_IBlockSetting"));
        sizePolicy.setHeightForWidth(m_txtIBlock_IBlockSetting->sizePolicy().hasHeightForWidth());
        m_txtIBlock_IBlockSetting->setSizePolicy(sizePolicy);
        m_txtIBlock_IBlockSetting->setMinimumSize(QSize(170, 0));
        m_txtIBlock_IBlockSetting->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_48->addWidget(m_txtIBlock_IBlockSetting);


        horizontalLayout_31->addLayout(horizontalLayout_48);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addWidget(frame_2);

        frame = new QFrame(QLowVolILockItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(9, -1, 9, -1);
        m_labHoldTime = new QLabel(frame);
        m_labHoldTime->setObjectName(QString::fromUtf8("m_labHoldTime"));
        sizePolicy.setHeightForWidth(m_labHoldTime->sizePolicy().hasHeightForWidth());
        m_labHoldTime->setSizePolicy(sizePolicy);
        m_labHoldTime->setMinimumSize(QSize(170, 0));
        m_labHoldTime->setMaximumSize(QSize(170, 16777215));
        m_labHoldTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(m_labHoldTime);

        m_txtIBlock_HoldTime = new QLineEdit(frame);
        m_txtIBlock_HoldTime->setObjectName(QString::fromUtf8("m_txtIBlock_HoldTime"));
        sizePolicy.setHeightForWidth(m_txtIBlock_HoldTime->sizePolicy().hasHeightForWidth());
        m_txtIBlock_HoldTime->setSizePolicy(sizePolicy);
        m_txtIBlock_HoldTime->setMinimumSize(QSize(170, 0));
        m_txtIBlock_HoldTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_txtIBlock_HoldTime);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_21->setContentsMargins(9, -1, 9, -1);
        m_labIBlock_Var = new QLabel(frame);
        m_labIBlock_Var->setObjectName(QString::fromUtf8("m_labIBlock_Var"));
        sizePolicy.setHeightForWidth(m_labIBlock_Var->sizePolicy().hasHeightForWidth());
        m_labIBlock_Var->setSizePolicy(sizePolicy);
        m_labIBlock_Var->setMinimumSize(QSize(170, 0));
        m_labIBlock_Var->setMaximumSize(QSize(170, 16777215));
        m_labIBlock_Var->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_21->addWidget(m_labIBlock_Var);

        m_cmbIBlock_Var = new QComboBox(frame);
        m_cmbIBlock_Var->setObjectName(QString::fromUtf8("m_cmbIBlock_Var"));
        sizePolicy.setHeightForWidth(m_cmbIBlock_Var->sizePolicy().hasHeightForWidth());
        m_cmbIBlock_Var->setSizePolicy(sizePolicy);
        m_cmbIBlock_Var->setMinimumSize(QSize(170, 0));
        m_cmbIBlock_Var->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_21->addWidget(m_cmbIBlock_Var);


        verticalLayout->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalLayout_22->setContentsMargins(9, -1, 9, -1);
        m_labRelErr = new QLabel(frame);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy);
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_22->addWidget(m_labRelErr);

        m_txtIBlock_RelErr = new QLineEdit(frame);
        m_txtIBlock_RelErr->setObjectName(QString::fromUtf8("m_txtIBlock_RelErr"));
        sizePolicy.setHeightForWidth(m_txtIBlock_RelErr->sizePolicy().hasHeightForWidth());
        m_txtIBlock_RelErr->setSizePolicy(sizePolicy);
        m_txtIBlock_RelErr->setMinimumSize(QSize(170, 0));
        m_txtIBlock_RelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_22->addWidget(m_txtIBlock_RelErr);


        verticalLayout->addLayout(horizontalLayout_22);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        horizontalLayout_25->setContentsMargins(9, -1, 9, -1);
        m_labAbsErr = new QLabel(frame);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        sizePolicy.setHeightForWidth(m_labAbsErr->sizePolicy().hasHeightForWidth());
        m_labAbsErr->setSizePolicy(sizePolicy);
        m_labAbsErr->setMinimumSize(QSize(170, 0));
        m_labAbsErr->setMaximumSize(QSize(170, 16777215));
        m_labAbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_25->addWidget(m_labAbsErr);

        m_txtIBlock_AbsErr = new QLineEdit(frame);
        m_txtIBlock_AbsErr->setObjectName(QString::fromUtf8("m_txtIBlock_AbsErr"));
        sizePolicy.setHeightForWidth(m_txtIBlock_AbsErr->sizePolicy().hasHeightForWidth());
        m_txtIBlock_AbsErr->setSizePolicy(sizePolicy);
        m_txtIBlock_AbsErr->setMinimumSize(QSize(170, 0));
        m_txtIBlock_AbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_25->addWidget(m_txtIBlock_AbsErr);


        verticalLayout->addLayout(horizontalLayout_25);


        verticalLayout_3->addWidget(frame);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 4);

        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupBox_2 = new QGroupBox(QLowVolILockItemParaEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_9 = new QVBoxLayout(groupBox_2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        horizontalLayout_43->setContentsMargins(9, -1, 9, -1);
        m_labIStart = new QLabel(groupBox_2);
        m_labIStart->setObjectName(QString::fromUtf8("m_labIStart"));
        sizePolicy.setHeightForWidth(m_labIStart->sizePolicy().hasHeightForWidth());
        m_labIStart->setSizePolicy(sizePolicy);
        m_labIStart->setMinimumSize(QSize(170, 0));
        m_labIStart->setMaximumSize(QSize(170, 16777215));
        m_labIStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_43->addWidget(m_labIStart);

        m_txtIBlock_IStart = new QSettingLineEdit(groupBox_2);
        m_txtIBlock_IStart->setObjectName(QString::fromUtf8("m_txtIBlock_IStart"));
        sizePolicy.setHeightForWidth(m_txtIBlock_IStart->sizePolicy().hasHeightForWidth());
        m_txtIBlock_IStart->setSizePolicy(sizePolicy);
        m_txtIBlock_IStart->setMinimumSize(QSize(170, 0));
        m_txtIBlock_IStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_43->addWidget(m_txtIBlock_IStart);


        verticalLayout_9->addLayout(horizontalLayout_43);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        horizontalLayout_44->setContentsMargins(9, -1, 9, -1);
        m_labIEnd = new QLabel(groupBox_2);
        m_labIEnd->setObjectName(QString::fromUtf8("m_labIEnd"));
        sizePolicy.setHeightForWidth(m_labIEnd->sizePolicy().hasHeightForWidth());
        m_labIEnd->setSizePolicy(sizePolicy);
        m_labIEnd->setMinimumSize(QSize(170, 0));
        m_labIEnd->setMaximumSize(QSize(170, 16777215));
        m_labIEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_44->addWidget(m_labIEnd);

        m_txtIBlock_IEnd = new QSettingLineEdit(groupBox_2);
        m_txtIBlock_IEnd->setObjectName(QString::fromUtf8("m_txtIBlock_IEnd"));
        sizePolicy.setHeightForWidth(m_txtIBlock_IEnd->sizePolicy().hasHeightForWidth());
        m_txtIBlock_IEnd->setSizePolicy(sizePolicy);
        m_txtIBlock_IEnd->setMinimumSize(QSize(170, 0));
        m_txtIBlock_IEnd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_44->addWidget(m_txtIBlock_IEnd);


        verticalLayout_9->addLayout(horizontalLayout_44);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        horizontalLayout_45->setContentsMargins(9, -1, 9, -1);
        m_labIStep = new QLabel(groupBox_2);
        m_labIStep->setObjectName(QString::fromUtf8("m_labIStep"));
        sizePolicy.setHeightForWidth(m_labIStep->sizePolicy().hasHeightForWidth());
        m_labIStep->setSizePolicy(sizePolicy);
        m_labIStep->setMinimumSize(QSize(170, 0));
        m_labIStep->setMaximumSize(QSize(170, 16777215));
        m_labIStep->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_45->addWidget(m_labIStep);

        m_txtIBlock_IStep = new QSettingLineEdit(groupBox_2);
        m_txtIBlock_IStep->setObjectName(QString::fromUtf8("m_txtIBlock_IStep"));
        sizePolicy.setHeightForWidth(m_txtIBlock_IStep->sizePolicy().hasHeightForWidth());
        m_txtIBlock_IStep->setSizePolicy(sizePolicy);
        m_txtIBlock_IStep->setMinimumSize(QSize(170, 0));
        m_txtIBlock_IStep->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_45->addWidget(m_txtIBlock_IStep);


        verticalLayout_9->addLayout(horizontalLayout_45);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setObjectName(QString::fromUtf8("horizontalLayout_46"));
        horizontalLayout_46->setContentsMargins(9, -1, 9, -1);
        m_labFreqEnd = new QLabel(groupBox_2);
        m_labFreqEnd->setObjectName(QString::fromUtf8("m_labFreqEnd"));
        sizePolicy.setHeightForWidth(m_labFreqEnd->sizePolicy().hasHeightForWidth());
        m_labFreqEnd->setSizePolicy(sizePolicy);
        m_labFreqEnd->setMinimumSize(QSize(170, 0));
        m_labFreqEnd->setMaximumSize(QSize(170, 16777215));
        m_labFreqEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_46->addWidget(m_labFreqEnd);

        m_txtIBlock_VEnd = new QSettingLineEdit(groupBox_2);
        m_txtIBlock_VEnd->setObjectName(QString::fromUtf8("m_txtIBlock_VEnd"));
        sizePolicy.setHeightForWidth(m_txtIBlock_VEnd->sizePolicy().hasHeightForWidth());
        m_txtIBlock_VEnd->setSizePolicy(sizePolicy);
        m_txtIBlock_VEnd->setMinimumSize(QSize(170, 0));
        m_txtIBlock_VEnd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_46->addWidget(m_txtIBlock_VEnd);


        verticalLayout_9->addLayout(horizontalLayout_46);

        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setObjectName(QString::fromUtf8("horizontalLayout_47"));
        horizontalLayout_47->setContentsMargins(9, -1, 9, -1);
        m_labDvdt = new QLabel(groupBox_2);
        m_labDvdt->setObjectName(QString::fromUtf8("m_labDvdt"));
        sizePolicy.setHeightForWidth(m_labDvdt->sizePolicy().hasHeightForWidth());
        m_labDvdt->setSizePolicy(sizePolicy);
        m_labDvdt->setMinimumSize(QSize(170, 0));
        m_labDvdt->setMaximumSize(QSize(170, 16777215));
        m_labDvdt->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_47->addWidget(m_labDvdt);

        m_txtIBlock_dVdt = new QSettingLineEdit(groupBox_2);
        m_txtIBlock_dVdt->setObjectName(QString::fromUtf8("m_txtIBlock_dVdt"));
        sizePolicy.setHeightForWidth(m_txtIBlock_dVdt->sizePolicy().hasHeightForWidth());
        m_txtIBlock_dVdt->setSizePolicy(sizePolicy);
        m_txtIBlock_dVdt->setMinimumSize(QSize(170, 0));
        m_txtIBlock_dVdt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_47->addWidget(m_txtIBlock_dVdt);


        verticalLayout_9->addLayout(horizontalLayout_47);


        horizontalLayout->addWidget(groupBox_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 4);
        horizontalLayout->setStretch(4, 1);

        retranslateUi(QLowVolILockItemParaEditWidget);

        QMetaObject::connectSlotsByName(QLowVolILockItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QLowVolILockItemParaEditWidget)
    {
        QLowVolILockItemParaEditWidget->setWindowTitle(QApplication::translate("QLowVolILockItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QLowVolILockItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labIBlockSetting->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\344\275\216\347\224\265\346\265\201\351\227\255\351\224\201\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labHoldTime->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labIBlock_Var->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\347\224\265\346\265\201\350\276\223\345\207\272\347\233\270:", 0, QApplication::UnicodeUTF8));
        m_cmbIBlock_Var->clear();
        m_cmbIBlock_Var->insertItems(0, QStringList()
         << QApplication::translate("QLowVolILockItemParaEditWidget", "Ia", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QLowVolILockItemParaEditWidget", "Ib", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QLowVolILockItemParaEditWidget", "Ic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QLowVolILockItemParaEditWidget", "Iabc", 0, QApplication::UnicodeUTF8)
        );
        m_labRelErr->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_txtIBlock_RelErr->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "2.0", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(A):", 0, QApplication::UnicodeUTF8));
        m_txtIBlock_AbsErr->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "0.020", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QLowVolILockItemParaEditWidget", "\351\200\222\345\217\230\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labIStart->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\347\224\265\346\265\201\345\217\230\345\214\226\345\247\213\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labIEnd->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\347\224\265\346\265\201\345\217\230\345\214\226\347\273\210\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labIStep->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\347\224\265\346\265\201\345\217\230\345\214\226\346\255\245\351\225\277(A):", 0, QApplication::UnicodeUTF8));
        m_labFreqEnd->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\347\224\265\345\216\213\345\217\230\345\214\226\347\273\210\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labDvdt->setText(QApplication::translate("QLowVolILockItemParaEditWidget", "\347\272\277\347\224\265\345\216\213\346\273\221\345\267\256(V/s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLowVolILockItemParaEditWidget: public Ui_QLowVolILockItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWVOLILOCKITEMPARAEDITWIDGET_H
