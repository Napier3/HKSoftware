/********************************************************************************
** Form generated from reading UI file 'SynActFreqItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNACTFREQITEMPARAEDITWIDGET_H
#define UI_SYNACTFREQITEMPARAEDITWIDGET_H

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

class Ui_QSynActFreqItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labFzd;
    QSettingLineEdit *m_lineFzd;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labRelErr;
    QLineEdit *m_lineRelErr;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labAbsErr;
    QLineEdit *m_lineAbsErr;
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
    QLabel *m_labUgFreqStep;
    QSettingLineEdit *m_lineUgFreqStep;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_labFt;
    QSettingLineEdit *m_lineFt;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QSynActFreqItemParaEditWidget)
    {
        if (QSynActFreqItemParaEditWidget->objectName().isEmpty())
            QSynActFreqItemParaEditWidget->setObjectName(QString::fromUtf8("QSynActFreqItemParaEditWidget"));
        QSynActFreqItemParaEditWidget->resize(1031, 370);
        horizontalLayout_8 = new QHBoxLayout(QSynActFreqItemParaEditWidget);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame = new QFrame(QSynActFreqItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
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
        m_labFzd = new QLabel(groupBox_2);
        m_labFzd->setObjectName(QString::fromUtf8("m_labFzd"));
        m_labFzd->setMinimumSize(QSize(170, 0));
        m_labFzd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_labFzd);

        m_lineFzd = new QSettingLineEdit(groupBox_2);
        m_lineFzd->setObjectName(QString::fromUtf8("m_lineFzd"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_lineFzd->sizePolicy().hasHeightForWidth());
        m_lineFzd->setSizePolicy(sizePolicy1);
        m_lineFzd->setMinimumSize(QSize(170, 0));
        m_lineFzd->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_lineFzd);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupBox_2);


        verticalLayout_5->addWidget(frame);

        frame_2 = new QFrame(QSynActFreqItemParaEditWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
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


        verticalLayout_3->addLayout(horizontalLayout_2);

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


        verticalLayout_5->addWidget(frame_2);


        horizontalLayout_8->addLayout(verticalLayout_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        groupBox_3 = new QGroupBox(QSynActFreqItemParaEditWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_labUgStart = new QLabel(groupBox_3);
        m_labUgStart->setObjectName(QString::fromUtf8("m_labUgStart"));
        m_labUgStart->setMinimumSize(QSize(205, 0));
        m_labUgStart->setMaximumSize(QSize(205, 16777215));

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
        m_labFgStart->setMinimumSize(QSize(205, 0));
        m_labFgStart->setMaximumSize(QSize(205, 16777215));

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
        m_labUgFreqStep = new QLabel(groupBox_3);
        m_labUgFreqStep->setObjectName(QString::fromUtf8("m_labUgFreqStep"));
        m_labUgFreqStep->setMinimumSize(QSize(205, 0));
        m_labUgFreqStep->setMaximumSize(QSize(205, 16777215));

        horizontalLayout_6->addWidget(m_labUgFreqStep);

        m_lineUgFreqStep = new QSettingLineEdit(groupBox_3);
        m_lineUgFreqStep->setObjectName(QString::fromUtf8("m_lineUgFreqStep"));
        sizePolicy1.setHeightForWidth(m_lineUgFreqStep->sizePolicy().hasHeightForWidth());
        m_lineUgFreqStep->setSizePolicy(sizePolicy1);
        m_lineUgFreqStep->setMinimumSize(QSize(170, 0));
        m_lineUgFreqStep->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_lineUgFreqStep);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_labFt = new QLabel(groupBox_3);
        m_labFt->setObjectName(QString::fromUtf8("m_labFt"));
        m_labFt->setMinimumSize(QSize(205, 0));
        m_labFt->setMaximumSize(QSize(205, 16777215));

        horizontalLayout_7->addWidget(m_labFt);

        m_lineFt = new QSettingLineEdit(groupBox_3);
        m_lineFt->setObjectName(QString::fromUtf8("m_lineFt"));
        sizePolicy1.setHeightForWidth(m_lineFt->sizePolicy().hasHeightForWidth());
        m_lineFt->setSizePolicy(sizePolicy1);
        m_lineFt->setMinimumSize(QSize(170, 0));
        m_lineFt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_7->addWidget(m_lineFt);


        verticalLayout_2->addLayout(horizontalLayout_7);


        horizontalLayout_8->addWidget(groupBox_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);


        retranslateUi(QSynActFreqItemParaEditWidget);

        QMetaObject::connectSlotsByName(QSynActFreqItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QSynActFreqItemParaEditWidget)
    {
        QSynActFreqItemParaEditWidget->setWindowTitle(QApplication::translate("QSynActFreqItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QSynActFreqItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labFzd->setText(QApplication::translate("QSynActFreqItemParaEditWidget", "\345\205\201\350\256\270\351\242\221\345\267\256(Hz):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QSynActFreqItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QSynActFreqItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(Hz):", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("QSynActFreqItemParaEditWidget", "\350\257\225\351\252\214\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labUgStart->setText(QApplication::translate("QSynActFreqItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFgStart->setText(QApplication::translate("QSynActFreqItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labUgFreqStep->setText(QApplication::translate("QSynActFreqItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\351\242\221\347\216\207\345\217\230\345\214\226\346\255\245\351\225\277(Hz):", 0, QApplication::UnicodeUTF8));
        m_labFt->setText(QApplication::translate("QSynActFreqItemParaEditWidget", "\350\260\203\351\242\221\345\221\250\346\234\237(s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSynActFreqItemParaEditWidget: public Ui_QSynActFreqItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNACTFREQITEMPARAEDITWIDGET_H
