/********************************************************************************
** Form generated from reading UI file 'SynAutoAdjItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNAUTOADJITEMPARAEDITWIDGET_H
#define UI_SYNAUTOADJITEMPARAEDITWIDGET_H

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

class Ui_QSynAutoAdjItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
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
    QHBoxLayout *horizontalLayout_12;
    QLabel *m_labUt;
    QSettingLineEdit *m_lineUt;
    QHBoxLayout *horizontalLayout_11;
    QLabel *m_labFt;
    QSettingLineEdit *m_lineFt;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labAbsErr;
    QLineEdit *m_lineAbsErr;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_8;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labUgStart;
    QSettingLineEdit *m_lineUgStart;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labFgStart;
    QSettingLineEdit *m_lineFgStart;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_labDfDt;
    QSettingLineEdit *m_lineDfDt;
    QHBoxLayout *horizontalLayout_10;
    QLabel *m_labDvDt;
    QSettingLineEdit *m_lineDvDt;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labRelErr;
    QLineEdit *m_lineRelErr;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QSynAutoAdjItemParaEditWidget)
    {
        if (QSynAutoAdjItemParaEditWidget->objectName().isEmpty())
            QSynAutoAdjItemParaEditWidget->setObjectName(QString::fromUtf8("QSynAutoAdjItemParaEditWidget"));
        QSynAutoAdjItemParaEditWidget->resize(930, 342);
        horizontalLayout_7 = new QHBoxLayout(QSynAutoAdjItemParaEditWidget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        frame = new QFrame(QSynAutoAdjItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
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


        verticalLayout_2->addWidget(groupBox_2);


        verticalLayout_4->addWidget(frame);

        frame_2 = new QFrame(QSynAutoAdjItemParaEditWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        m_labUt = new QLabel(frame_2);
        m_labUt->setObjectName(QString::fromUtf8("m_labUt"));
        m_labUt->setMinimumSize(QSize(170, 0));
        m_labUt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_12->addWidget(m_labUt);

        m_lineUt = new QSettingLineEdit(frame_2);
        m_lineUt->setObjectName(QString::fromUtf8("m_lineUt"));
        sizePolicy1.setHeightForWidth(m_lineUt->sizePolicy().hasHeightForWidth());
        m_lineUt->setSizePolicy(sizePolicy1);
        m_lineUt->setMinimumSize(QSize(170, 0));
        m_lineUt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_12->addWidget(m_lineUt);


        verticalLayout_3->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        m_labFt = new QLabel(frame_2);
        m_labFt->setObjectName(QString::fromUtf8("m_labFt"));
        m_labFt->setMinimumSize(QSize(170, 0));
        m_labFt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_11->addWidget(m_labFt);

        m_lineFt = new QSettingLineEdit(frame_2);
        m_lineFt->setObjectName(QString::fromUtf8("m_lineFt"));
        sizePolicy1.setHeightForWidth(m_lineFt->sizePolicy().hasHeightForWidth());
        m_lineFt->setSizePolicy(sizePolicy1);
        m_lineFt->setMinimumSize(QSize(170, 0));
        m_lineFt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_11->addWidget(m_lineFt);


        verticalLayout_3->addLayout(horizontalLayout_11);

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


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_4->addWidget(frame_2);


        horizontalLayout_7->addLayout(verticalLayout_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        frame_3 = new QFrame(QSynAutoAdjItemParaEditWidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_3);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(frame_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 200));
        groupBox_3->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_labUgStart = new QLabel(groupBox_3);
        m_labUgStart->setObjectName(QString::fromUtf8("m_labUgStart"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_labUgStart->sizePolicy().hasHeightForWidth());
        m_labUgStart->setSizePolicy(sizePolicy2);
        m_labUgStart->setMinimumSize(QSize(170, 0));
        m_labUgStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_labUgStart);

        m_lineUgStart = new QSettingLineEdit(groupBox_3);
        m_lineUgStart->setObjectName(QString::fromUtf8("m_lineUgStart"));
        sizePolicy2.setHeightForWidth(m_lineUgStart->sizePolicy().hasHeightForWidth());
        m_lineUgStart->setSizePolicy(sizePolicy2);
        m_lineUgStart->setMinimumSize(QSize(170, 0));
        m_lineUgStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_5->addWidget(m_lineUgStart);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labFgStart = new QLabel(groupBox_3);
        m_labFgStart->setObjectName(QString::fromUtf8("m_labFgStart"));
        sizePolicy2.setHeightForWidth(m_labFgStart->sizePolicy().hasHeightForWidth());
        m_labFgStart->setSizePolicy(sizePolicy2);
        m_labFgStart->setMinimumSize(QSize(170, 0));
        m_labFgStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_labFgStart);

        m_lineFgStart = new QSettingLineEdit(groupBox_3);
        m_lineFgStart->setObjectName(QString::fromUtf8("m_lineFgStart"));
        sizePolicy2.setHeightForWidth(m_lineFgStart->sizePolicy().hasHeightForWidth());
        m_lineFgStart->setSizePolicy(sizePolicy2);
        m_lineFgStart->setMinimumSize(QSize(170, 0));
        m_lineFgStart->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_lineFgStart);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        m_labDfDt = new QLabel(groupBox_3);
        m_labDfDt->setObjectName(QString::fromUtf8("m_labDfDt"));
        sizePolicy2.setHeightForWidth(m_labDfDt->sizePolicy().hasHeightForWidth());
        m_labDfDt->setSizePolicy(sizePolicy2);
        m_labDfDt->setMinimumSize(QSize(170, 0));
        m_labDfDt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_9->addWidget(m_labDfDt);

        m_lineDfDt = new QSettingLineEdit(groupBox_3);
        m_lineDfDt->setObjectName(QString::fromUtf8("m_lineDfDt"));
        sizePolicy2.setHeightForWidth(m_lineDfDt->sizePolicy().hasHeightForWidth());
        m_lineDfDt->setSizePolicy(sizePolicy2);
        m_lineDfDt->setMinimumSize(QSize(170, 0));
        m_lineDfDt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_9->addWidget(m_lineDfDt);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        m_labDvDt = new QLabel(groupBox_3);
        m_labDvDt->setObjectName(QString::fromUtf8("m_labDvDt"));
        sizePolicy2.setHeightForWidth(m_labDvDt->sizePolicy().hasHeightForWidth());
        m_labDvDt->setSizePolicy(sizePolicy2);
        m_labDvDt->setMinimumSize(QSize(170, 0));
        m_labDvDt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_10->addWidget(m_labDvDt);

        m_lineDvDt = new QSettingLineEdit(groupBox_3);
        m_lineDvDt->setObjectName(QString::fromUtf8("m_lineDvDt"));
        sizePolicy2.setHeightForWidth(m_lineDvDt->sizePolicy().hasHeightForWidth());
        m_lineDvDt->setSizePolicy(sizePolicy2);
        m_lineDvDt->setMinimumSize(QSize(170, 0));
        m_lineDvDt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_10->addWidget(m_lineDvDt);


        verticalLayout_5->addLayout(horizontalLayout_10);


        verticalLayout_6->addWidget(groupBox_3);


        verticalLayout_8->addWidget(frame_3);

        frame_4 = new QFrame(QSynAutoAdjItemParaEditWidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_4);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labRelErr = new QLabel(frame_4);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy2.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy2);
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_labRelErr);

        m_lineRelErr = new QLineEdit(frame_4);
        m_lineRelErr->setObjectName(QString::fromUtf8("m_lineRelErr"));
        sizePolicy2.setHeightForWidth(m_lineRelErr->sizePolicy().hasHeightForWidth());
        m_lineRelErr->setSizePolicy(sizePolicy2);
        m_lineRelErr->setMinimumSize(QSize(170, 0));
        m_lineRelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_lineRelErr);


        verticalLayout_7->addLayout(horizontalLayout_2);


        verticalLayout_8->addWidget(frame_4);


        horizontalLayout_7->addLayout(verticalLayout_8);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        retranslateUi(QSynAutoAdjItemParaEditWidget);

        QMetaObject::connectSlotsByName(QSynAutoAdjItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QSynAutoAdjItemParaEditWidget)
    {
        QSynAutoAdjItemParaEditWidget->setWindowTitle(QApplication::translate("QSynAutoAdjItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labLAngle->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\345\257\274\345\211\215\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labLTime->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\345\257\274\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labUt->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\350\260\203\345\216\213\345\221\250\346\234\237(s):", 0, QApplication::UnicodeUTF8));
        m_labFt->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\350\260\203\351\242\221\345\221\250\346\234\237(s):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\350\257\225\351\252\214\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labUgStart->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFgStart->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labDfDt->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "df/dt(Hz/s):", 0, QApplication::UnicodeUTF8));
        m_labDvDt->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "dv/dt(V/s):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QSynAutoAdjItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSynAutoAdjItemParaEditWidget: public Ui_QSynAutoAdjItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNAUTOADJITEMPARAEDITWIDGET_H
