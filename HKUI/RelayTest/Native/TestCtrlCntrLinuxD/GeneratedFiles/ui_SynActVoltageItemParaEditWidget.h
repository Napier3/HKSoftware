/********************************************************************************
** Form generated from reading UI file 'SynActVoltageItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNACTVOLTAGEITEMPARAEDITWIDGET_H
#define UI_SYNACTVOLTAGEITEMPARAEDITWIDGET_H

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

class Ui_QSynActVoltageItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labVzd;
    QSettingLineEdit *m_lineVzd;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labAbsErr;
    QLineEdit *m_lineAbsErr;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labRelErr;
    QLineEdit *m_lineRelErr;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labUgStart;
    QSettingLineEdit *m_lineUgStart;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labFgStart;
    QSettingLineEdit *m_lineFgStart;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labUgMagStep;
    QSettingLineEdit *m_lineUgMagStep;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_labUt;
    QSettingLineEdit *m_lineUt;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QSynActVoltageItemParaEditWidget)
    {
        if (QSynActVoltageItemParaEditWidget->objectName().isEmpty())
            QSynActVoltageItemParaEditWidget->setObjectName(QString::fromUtf8("QSynActVoltageItemParaEditWidget"));
        QSynActVoltageItemParaEditWidget->resize(1046, 370);
        horizontalLayout_8 = new QHBoxLayout(QSynActVoltageItemParaEditWidget);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame = new QFrame(QSynActVoltageItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labVzd = new QLabel(groupBox_2);
        m_labVzd->setObjectName(QString::fromUtf8("m_labVzd"));
        m_labVzd->setMinimumSize(QSize(170, 0));
        m_labVzd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_labVzd);

        m_lineVzd = new QSettingLineEdit(groupBox_2);
        m_lineVzd->setObjectName(QString::fromUtf8("m_lineVzd"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_lineVzd->sizePolicy().hasHeightForWidth());
        m_lineVzd->setSizePolicy(sizePolicy1);
        m_lineVzd->setMinimumSize(QSize(170, 0));
        m_lineVzd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_lineVzd);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(groupBox_2);


        verticalLayout_5->addWidget(frame);

        frame_2 = new QFrame(QSynActVoltageItemParaEditWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_labAbsErr = new QLabel(frame_2);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        m_labAbsErr->setMinimumSize(QSize(170, 0));
        m_labAbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_labAbsErr);

        m_lineAbsErr = new QLineEdit(frame_2);
        m_lineAbsErr->setObjectName(QString::fromUtf8("m_lineAbsErr"));
        sizePolicy1.setHeightForWidth(m_lineAbsErr->sizePolicy().hasHeightForWidth());
        m_lineAbsErr->setSizePolicy(sizePolicy1);
        m_lineAbsErr->setMinimumSize(QSize(170, 0));
        m_lineAbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_lineAbsErr);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labRelErr = new QLabel(frame_2);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_labRelErr);

        m_lineRelErr = new QLineEdit(frame_2);
        m_lineRelErr->setObjectName(QString::fromUtf8("m_lineRelErr"));
        sizePolicy1.setHeightForWidth(m_lineRelErr->sizePolicy().hasHeightForWidth());
        m_lineRelErr->setSizePolicy(sizePolicy1);
        m_lineRelErr->setMinimumSize(QSize(170, 0));
        m_lineRelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_lineRelErr);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_5->addWidget(frame_2);


        horizontalLayout_8->addLayout(verticalLayout_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        groupBox_3 = new QGroupBox(QSynActVoltageItemParaEditWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_labUgStart = new QLabel(groupBox_3);
        m_labUgStart->setObjectName(QString::fromUtf8("m_labUgStart"));
        m_labUgStart->setMinimumSize(QSize(195, 0));
        m_labUgStart->setMaximumSize(QSize(195, 16777215));

        horizontalLayout_4->addWidget(m_labUgStart);

        m_lineUgStart = new QSettingLineEdit(groupBox_3);
        m_lineUgStart->setObjectName(QString::fromUtf8("m_lineUgStart"));
        sizePolicy1.setHeightForWidth(m_lineUgStart->sizePolicy().hasHeightForWidth());
        m_lineUgStart->setSizePolicy(sizePolicy1);
        m_lineUgStart->setMinimumSize(QSize(170, 0));
        m_lineUgStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_lineUgStart);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_labFgStart = new QLabel(groupBox_3);
        m_labFgStart->setObjectName(QString::fromUtf8("m_labFgStart"));
        m_labFgStart->setMinimumSize(QSize(195, 0));
        m_labFgStart->setMaximumSize(QSize(195, 16777215));

        horizontalLayout_5->addWidget(m_labFgStart);

        m_lineFgStart = new QSettingLineEdit(groupBox_3);
        m_lineFgStart->setObjectName(QString::fromUtf8("m_lineFgStart"));
        sizePolicy1.setHeightForWidth(m_lineFgStart->sizePolicy().hasHeightForWidth());
        m_lineFgStart->setSizePolicy(sizePolicy1);
        m_lineFgStart->setMinimumSize(QSize(170, 0));
        m_lineFgStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_lineFgStart);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labUgMagStep = new QLabel(groupBox_3);
        m_labUgMagStep->setObjectName(QString::fromUtf8("m_labUgMagStep"));
        m_labUgMagStep->setMinimumSize(QSize(195, 0));
        m_labUgMagStep->setMaximumSize(QSize(195, 16777215));

        horizontalLayout_6->addWidget(m_labUgMagStep);

        m_lineUgMagStep = new QSettingLineEdit(groupBox_3);
        m_lineUgMagStep->setObjectName(QString::fromUtf8("m_lineUgMagStep"));
        sizePolicy1.setHeightForWidth(m_lineUgMagStep->sizePolicy().hasHeightForWidth());
        m_lineUgMagStep->setSizePolicy(sizePolicy1);
        m_lineUgMagStep->setMinimumSize(QSize(170, 0));
        m_lineUgMagStep->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_lineUgMagStep);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_labUt = new QLabel(groupBox_3);
        m_labUt->setObjectName(QString::fromUtf8("m_labUt"));
        m_labUt->setMinimumSize(QSize(195, 0));
        m_labUt->setMaximumSize(QSize(195, 16777215));

        horizontalLayout_7->addWidget(m_labUt);

        m_lineUt = new QSettingLineEdit(groupBox_3);
        m_lineUt->setObjectName(QString::fromUtf8("m_lineUt"));
        sizePolicy1.setHeightForWidth(m_lineUt->sizePolicy().hasHeightForWidth());
        m_lineUt->setSizePolicy(sizePolicy1);
        m_lineUt->setMinimumSize(QSize(170, 0));
        m_lineUt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_7->addWidget(m_lineUt);


        verticalLayout_2->addLayout(horizontalLayout_7);


        horizontalLayout_8->addWidget(groupBox_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);


        retranslateUi(QSynActVoltageItemParaEditWidget);

        QMetaObject::connectSlotsByName(QSynActVoltageItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QSynActVoltageItemParaEditWidget)
    {
        QSynActVoltageItemParaEditWidget->setWindowTitle(QApplication::translate("QSynActVoltageItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QSynActVoltageItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labVzd->setText(QApplication::translate("QSynActVoltageItemParaEditWidget", "\345\205\201\350\256\270\345\216\213\345\267\256(V):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QSynActVoltageItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(V):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QSynActVoltageItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("QSynActVoltageItemParaEditWidget", "\350\257\225\351\252\214\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labUgStart->setText(QApplication::translate("QSynActVoltageItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFgStart->setText(QApplication::translate("QSynActVoltageItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labUgMagStep->setText(QApplication::translate("QSynActVoltageItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\347\224\265\345\216\213\345\217\230\345\214\226\346\255\245\351\225\277(V):", 0, QApplication::UnicodeUTF8));
        m_labUt->setText(QApplication::translate("QSynActVoltageItemParaEditWidget", "\350\260\203\345\216\213\345\221\250\346\234\237(s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSynActVoltageItemParaEditWidget: public Ui_QSynActVoltageItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNACTVOLTAGEITEMPARAEDITWIDGET_H
