/********************************************************************************
** Form generated from reading UI file 'SynLeadAngItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNLEADANGITEMPARAEDITWIDGET_H
#define UI_SYNLEADANGITEMPARAEDITWIDGET_H

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

class Ui_QSynLeadAngItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labLAngle;
    QSettingLineEdit *m_lineLAngle;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labLTime;
    QSettingLineEdit *m_lineLTime;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labAbsErr;
    QLineEdit *m_lineAbsErr;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labRelErr;
    QLineEdit *m_lineRelErr;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_7;
    QFrame *frame;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labUgStart;
    QSettingLineEdit *m_lineUgStart;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labFgStart;
    QSettingLineEdit *m_lineFgStart;
    QFrame *frame_4;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QSynLeadAngItemParaEditWidget)
    {
        if (QSynLeadAngItemParaEditWidget->objectName().isEmpty())
            QSynLeadAngItemParaEditWidget->setObjectName(QString::fromUtf8("QSynLeadAngItemParaEditWidget"));
        QSynLeadAngItemParaEditWidget->resize(930, 342);
        horizontalLayout_7 = new QHBoxLayout(QSynLeadAngItemParaEditWidget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame_3 = new QFrame(QSynLeadAngItemParaEditWidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_3);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(frame_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(5000, 150));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labLAngle = new QLabel(groupBox_2);
        m_labLAngle->setObjectName(QString::fromUtf8("m_labLAngle"));
        m_labLAngle->setMinimumSize(QSize(170, 0));
        m_labLAngle->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_labLAngle);

        m_lineLAngle = new QSettingLineEdit(groupBox_2);
        m_lineLAngle->setObjectName(QString::fromUtf8("m_lineLAngle"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_lineLAngle->sizePolicy().hasHeightForWidth());
        m_lineLAngle->setSizePolicy(sizePolicy1);
        m_lineLAngle->setMinimumSize(QSize(170, 0));
        m_lineLAngle->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_lineLAngle);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_labLTime = new QLabel(groupBox_2);
        m_labLTime->setObjectName(QString::fromUtf8("m_labLTime"));
        m_labLTime->setMinimumSize(QSize(170, 0));
        m_labLTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_labLTime);

        m_lineLTime = new QSettingLineEdit(groupBox_2);
        m_lineLTime->setObjectName(QString::fromUtf8("m_lineLTime"));
        sizePolicy1.setHeightForWidth(m_lineLTime->sizePolicy().hasHeightForWidth());
        m_lineLTime->setSizePolicy(sizePolicy1);
        m_lineLTime->setMinimumSize(QSize(170, 0));
        m_lineLTime->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_4->addWidget(m_lineLTime);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_4->addWidget(groupBox_2);


        verticalLayout_5->addWidget(frame_3);

        frame_2 = new QFrame(QSynLeadAngItemParaEditWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labAbsErr = new QLabel(frame_2);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        m_labAbsErr->setMinimumSize(QSize(170, 0));
        m_labAbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_labAbsErr);

        m_lineAbsErr = new QLineEdit(frame_2);
        m_lineAbsErr->setObjectName(QString::fromUtf8("m_lineAbsErr"));
        sizePolicy1.setHeightForWidth(m_lineAbsErr->sizePolicy().hasHeightForWidth());
        m_lineAbsErr->setSizePolicy(sizePolicy1);
        m_lineAbsErr->setMinimumSize(QSize(170, 0));
        m_lineAbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_lineAbsErr);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_labRelErr = new QLabel(frame_2);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_labRelErr);

        m_lineRelErr = new QLineEdit(frame_2);
        m_lineRelErr->setObjectName(QString::fromUtf8("m_lineRelErr"));
        sizePolicy1.setHeightForWidth(m_lineRelErr->sizePolicy().hasHeightForWidth());
        m_lineRelErr->setSizePolicy(sizePolicy1);
        m_lineRelErr->setMinimumSize(QSize(170, 0));
        m_lineRelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_lineRelErr);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_5->addWidget(frame_2);


        horizontalLayout_7->addLayout(verticalLayout_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        frame = new QFrame(QSynLeadAngItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMaximumSize(QSize(16777215, 150));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_labUgStart = new QLabel(groupBox_3);
        m_labUgStart->setObjectName(QString::fromUtf8("m_labUgStart"));
        m_labUgStart->setMinimumSize(QSize(205, 0));
        m_labUgStart->setMaximumSize(QSize(205, 16777215));

        horizontalLayout_5->addWidget(m_labUgStart);

        m_lineUgStart = new QSettingLineEdit(groupBox_3);
        m_lineUgStart->setObjectName(QString::fromUtf8("m_lineUgStart"));
        sizePolicy1.setHeightForWidth(m_lineUgStart->sizePolicy().hasHeightForWidth());
        m_lineUgStart->setSizePolicy(sizePolicy1);
        m_lineUgStart->setMinimumSize(QSize(170, 0));
        m_lineUgStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_lineUgStart);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labFgStart = new QLabel(groupBox_3);
        m_labFgStart->setObjectName(QString::fromUtf8("m_labFgStart"));
        m_labFgStart->setMinimumSize(QSize(205, 0));
        m_labFgStart->setMaximumSize(QSize(205, 16777215));

        horizontalLayout_6->addWidget(m_labFgStart);

        m_lineFgStart = new QSettingLineEdit(groupBox_3);
        m_lineFgStart->setObjectName(QString::fromUtf8("m_lineFgStart"));
        sizePolicy1.setHeightForWidth(m_lineFgStart->sizePolicy().hasHeightForWidth());
        m_lineFgStart->setSizePolicy(sizePolicy1);
        m_lineFgStart->setMinimumSize(QSize(170, 0));
        m_lineFgStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_lineFgStart);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout_6->addWidget(groupBox_3);


        verticalLayout_7->addWidget(frame);

        frame_4 = new QFrame(QSynLeadAngItemParaEditWidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);

        verticalLayout_7->addWidget(frame_4);


        horizontalLayout_7->addLayout(verticalLayout_7);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        retranslateUi(QSynLeadAngItemParaEditWidget);

        QMetaObject::connectSlotsByName(QSynLeadAngItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QSynLeadAngItemParaEditWidget)
    {
        QSynLeadAngItemParaEditWidget->setWindowTitle(QApplication::translate("QSynLeadAngItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QSynLeadAngItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labLAngle->setText(QApplication::translate("QSynLeadAngItemParaEditWidget", "\345\257\274\345\211\215\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labLTime->setText(QApplication::translate("QSynLeadAngItemParaEditWidget", "\345\257\274\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QSynLeadAngItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QSynLeadAngItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("QSynLeadAngItemParaEditWidget", "\350\257\225\351\252\214\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labUgStart->setText(QApplication::translate("QSynLeadAngItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFgStart->setText(QApplication::translate("QSynLeadAngItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSynLeadAngItemParaEditWidget: public Ui_QSynLeadAngItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNLEADANGITEMPARAEDITWIDGET_H
