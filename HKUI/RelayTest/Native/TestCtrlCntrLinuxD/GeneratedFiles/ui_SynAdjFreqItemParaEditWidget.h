/********************************************************************************
** Form generated from reading UI file 'SynAdjFreqItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNADJFREQITEMPARAEDITWIDGET_H
#define UI_SYNADJFREQITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_QSynAdjFreqItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labFt;
    QSettingLineEdit *m_lineFt;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labUgStart;
    QSettingLineEdit *m_lineUgStart;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labFgStart;
    QSettingLineEdit *m_lineFgStart;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labAbsErr;
    QLineEdit *m_linePlus;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labAbsErr_2;
    QLineEdit *m_lineMinus;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labRelErr;
    QLineEdit *m_lineRelErr;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QSynAdjFreqItemParaEditWidget)
    {
        if (QSynAdjFreqItemParaEditWidget->objectName().isEmpty())
            QSynAdjFreqItemParaEditWidget->setObjectName(QString::fromUtf8("QSynAdjFreqItemParaEditWidget"));
        QSynAdjFreqItemParaEditWidget->resize(930, 342);
        horizontalLayout_7 = new QHBoxLayout(QSynAdjFreqItemParaEditWidget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_2 = new QGroupBox(QSynAdjFreqItemParaEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(5000, 100));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labFt = new QLabel(groupBox_2);
        m_labFt->setObjectName(QString::fromUtf8("m_labFt"));
        m_labFt->setMinimumSize(QSize(170, 0));
        m_labFt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_labFt);

        m_lineFt = new QSettingLineEdit(groupBox_2);
        m_lineFt->setObjectName(QString::fromUtf8("m_lineFt"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_lineFt->sizePolicy().hasHeightForWidth());
        m_lineFt->setSizePolicy(sizePolicy1);
        m_lineFt->setMinimumSize(QSize(170, 0));
        m_lineFt->setMaximumSize(QSize(170, 16777215));

        horizontalLayout->addWidget(m_lineFt);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(QSynAdjFreqItemParaEditWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
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


        verticalLayout->addLayout(horizontalLayout_4);

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


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addWidget(groupBox_3);


        horizontalLayout_7->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_labAbsErr = new QLabel(QSynAdjFreqItemParaEditWidget);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        m_labAbsErr->setMinimumSize(QSize(170, 0));
        m_labAbsErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_labAbsErr);

        m_linePlus = new QLineEdit(QSynAdjFreqItemParaEditWidget);
        m_linePlus->setObjectName(QString::fromUtf8("m_linePlus"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_linePlus->sizePolicy().hasHeightForWidth());
        m_linePlus->setSizePolicy(sizePolicy2);
        m_linePlus->setMinimumSize(QSize(170, 0));
        m_linePlus->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_3->addWidget(m_linePlus);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labAbsErr_2 = new QLabel(QSynAdjFreqItemParaEditWidget);
        m_labAbsErr_2->setObjectName(QString::fromUtf8("m_labAbsErr_2"));
        m_labAbsErr_2->setMinimumSize(QSize(170, 0));
        m_labAbsErr_2->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_labAbsErr_2);

        m_lineMinus = new QLineEdit(QSynAdjFreqItemParaEditWidget);
        m_lineMinus->setObjectName(QString::fromUtf8("m_lineMinus"));
        sizePolicy2.setHeightForWidth(m_lineMinus->sizePolicy().hasHeightForWidth());
        m_lineMinus->setSizePolicy(sizePolicy2);
        m_lineMinus->setMinimumSize(QSize(170, 0));
        m_lineMinus->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_6->addWidget(m_lineMinus);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labRelErr = new QLabel(QSynAdjFreqItemParaEditWidget);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        m_labRelErr->setMinimumSize(QSize(170, 0));
        m_labRelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_labRelErr);

        m_lineRelErr = new QLineEdit(QSynAdjFreqItemParaEditWidget);
        m_lineRelErr->setObjectName(QString::fromUtf8("m_lineRelErr"));
        sizePolicy1.setHeightForWidth(m_lineRelErr->sizePolicy().hasHeightForWidth());
        m_lineRelErr->setSizePolicy(sizePolicy1);
        m_lineRelErr->setMinimumSize(QSize(170, 0));
        m_lineRelErr->setMaximumSize(QSize(170, 16777215));

        horizontalLayout_2->addWidget(m_lineRelErr);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_7->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        retranslateUi(QSynAdjFreqItemParaEditWidget);

        QMetaObject::connectSlotsByName(QSynAdjFreqItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QSynAdjFreqItemParaEditWidget)
    {
        QSynAdjFreqItemParaEditWidget->setWindowTitle(QApplication::translate("QSynAdjFreqItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QSynAdjFreqItemParaEditWidget", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_labFt->setText(QApplication::translate("QSynAdjFreqItemParaEditWidget", "\350\260\203\351\242\221\345\221\250\346\234\237(s):", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("QSynAdjFreqItemParaEditWidget", "\350\257\225\351\252\214\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labUgStart->setText(QApplication::translate("QSynAdjFreqItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFgStart->setText(QApplication::translate("QSynAdjFreqItemParaEditWidget", "\345\276\205\345\271\266\344\276\247\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QSynAdjFreqItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_labAbsErr_2->setText(QApplication::translate("QSynAdjFreqItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QSynAdjFreqItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSynAdjFreqItemParaEditWidget: public Ui_QSynAdjFreqItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNADJFREQITEMPARAEDITWIDGET_H
