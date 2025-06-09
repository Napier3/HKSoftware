/********************************************************************************
** Form generated from reading UI file 'ActionTimeItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIONTIMEITEMPARAEDITWIDGET_H
#define UI_ACTIONTIMEITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../UI/Controls/SettingCtrls/QSettingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QActionTimeItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QLabel *m_labAbsErrPos;
    QLineEdit *m_editPreFre;
    QLabel *m_labFaultAngle;
    QLineEdit *m_editPreAngle;
    QLineEdit *m_editFaultVolt;
    QLabel *m_labFaultVol;
    QLabel *m_labFaultFre;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_3;
    QSettingLineEdit *m_editSettingTime;
    QSpacerItem *horizontalSpacer;
    QLabel *m_labSettingTime;
    QLineEdit *m_editFaultCurrent;
    QLineEdit *m_editRelErr;
    QLabel *m_labFaultCur;
    QLabel *m_labFaultType;
    QLabel *m_labFaultVolType;
    CExBaseListComboBox *m_cbbFaultType;
    QComboBox *m_cbbFaultVolType;
    QLabel *m_labRelErr;
    QLabel *m_labAbsErrNeg;
    QLineEdit *m_editAbsErr1;
    QLineEdit *m_editAbsErr2;

    void setupUi(QWidget *QActionTimeItemParaEditWidget)
    {
        if (QActionTimeItemParaEditWidget->objectName().isEmpty())
            QActionTimeItemParaEditWidget->setObjectName(QString::fromUtf8("QActionTimeItemParaEditWidget"));
        QActionTimeItemParaEditWidget->resize(739, 371);
        horizontalLayout_2 = new QHBoxLayout(QActionTimeItemParaEditWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labAbsErrPos = new QLabel(QActionTimeItemParaEditWidget);
        m_labAbsErrPos->setObjectName(QString::fromUtf8("m_labAbsErrPos"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labAbsErrPos->sizePolicy().hasHeightForWidth());
        m_labAbsErrPos->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_labAbsErrPos, 4, 1, 1, 1);

        m_editPreFre = new QLineEdit(QActionTimeItemParaEditWidget);
        m_editPreFre->setObjectName(QString::fromUtf8("m_editPreFre"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_editPreFre->sizePolicy().hasHeightForWidth());
        m_editPreFre->setSizePolicy(sizePolicy1);
        m_editPreFre->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_editPreFre, 3, 5, 1, 1);

        m_labFaultAngle = new QLabel(QActionTimeItemParaEditWidget);
        m_labFaultAngle->setObjectName(QString::fromUtf8("m_labFaultAngle"));

        gridLayout->addWidget(m_labFaultAngle, 2, 4, 1, 1);

        m_editPreAngle = new QLineEdit(QActionTimeItemParaEditWidget);
        m_editPreAngle->setObjectName(QString::fromUtf8("m_editPreAngle"));
        sizePolicy1.setHeightForWidth(m_editPreAngle->sizePolicy().hasHeightForWidth());
        m_editPreAngle->setSizePolicy(sizePolicy1);
        m_editPreAngle->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_editPreAngle, 2, 5, 1, 1);

        m_editFaultVolt = new QLineEdit(QActionTimeItemParaEditWidget);
        m_editFaultVolt->setObjectName(QString::fromUtf8("m_editFaultVolt"));

        gridLayout->addWidget(m_editFaultVolt, 1, 5, 1, 1);

        m_labFaultVol = new QLabel(QActionTimeItemParaEditWidget);
        m_labFaultVol->setObjectName(QString::fromUtf8("m_labFaultVol"));

        gridLayout->addWidget(m_labFaultVol, 1, 4, 1, 1);

        m_labFaultFre = new QLabel(QActionTimeItemParaEditWidget);
        m_labFaultFre->setObjectName(QString::fromUtf8("m_labFaultFre"));

        gridLayout->addWidget(m_labFaultFre, 3, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        label_11 = new QLabel(QActionTimeItemParaEditWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_11, 4, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 6, 1, 1);

        m_editSettingTime = new QSettingLineEdit(QActionTimeItemParaEditWidget);
        m_editSettingTime->setObjectName(QString::fromUtf8("m_editSettingTime"));
        sizePolicy1.setHeightForWidth(m_editSettingTime->sizePolicy().hasHeightForWidth());
        m_editSettingTime->setSizePolicy(sizePolicy1);
        m_editSettingTime->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_editSettingTime, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        m_labSettingTime = new QLabel(QActionTimeItemParaEditWidget);
        m_labSettingTime->setObjectName(QString::fromUtf8("m_labSettingTime"));

        gridLayout->addWidget(m_labSettingTime, 1, 1, 1, 1);

        m_editFaultCurrent = new QLineEdit(QActionTimeItemParaEditWidget);
        m_editFaultCurrent->setObjectName(QString::fromUtf8("m_editFaultCurrent"));
        sizePolicy1.setHeightForWidth(m_editFaultCurrent->sizePolicy().hasHeightForWidth());
        m_editFaultCurrent->setSizePolicy(sizePolicy1);
        m_editFaultCurrent->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_editFaultCurrent, 2, 2, 1, 1);

        m_editRelErr = new QLineEdit(QActionTimeItemParaEditWidget);
        m_editRelErr->setObjectName(QString::fromUtf8("m_editRelErr"));
        sizePolicy1.setHeightForWidth(m_editRelErr->sizePolicy().hasHeightForWidth());
        m_editRelErr->setSizePolicy(sizePolicy1);
        m_editRelErr->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_editRelErr, 3, 2, 1, 1);

        m_labFaultCur = new QLabel(QActionTimeItemParaEditWidget);
        m_labFaultCur->setObjectName(QString::fromUtf8("m_labFaultCur"));

        gridLayout->addWidget(m_labFaultCur, 2, 1, 1, 1);

        m_labFaultType = new QLabel(QActionTimeItemParaEditWidget);
        m_labFaultType->setObjectName(QString::fromUtf8("m_labFaultType"));
        m_labFaultType->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(m_labFaultType, 0, 1, 1, 1);

        m_labFaultVolType = new QLabel(QActionTimeItemParaEditWidget);
        m_labFaultVolType->setObjectName(QString::fromUtf8("m_labFaultVolType"));

        gridLayout->addWidget(m_labFaultVolType, 0, 4, 1, 1);

        m_cbbFaultType = new CExBaseListComboBox(QActionTimeItemParaEditWidget);
        m_cbbFaultType->setObjectName(QString::fromUtf8("m_cbbFaultType"));
        sizePolicy1.setHeightForWidth(m_cbbFaultType->sizePolicy().hasHeightForWidth());
        m_cbbFaultType->setSizePolicy(sizePolicy1);
        m_cbbFaultType->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_cbbFaultType, 0, 2, 1, 1);

        m_cbbFaultVolType = new QComboBox(QActionTimeItemParaEditWidget);
        m_cbbFaultVolType->setObjectName(QString::fromUtf8("m_cbbFaultVolType"));
        sizePolicy1.setHeightForWidth(m_cbbFaultVolType->sizePolicy().hasHeightForWidth());
        m_cbbFaultVolType->setSizePolicy(sizePolicy1);
        m_cbbFaultVolType->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_cbbFaultVolType, 0, 5, 1, 1);

        m_labRelErr = new QLabel(QActionTimeItemParaEditWidget);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));

        gridLayout->addWidget(m_labRelErr, 3, 1, 1, 1);

        m_labAbsErrNeg = new QLabel(QActionTimeItemParaEditWidget);
        m_labAbsErrNeg->setObjectName(QString::fromUtf8("m_labAbsErrNeg"));
        sizePolicy.setHeightForWidth(m_labAbsErrNeg->sizePolicy().hasHeightForWidth());
        m_labAbsErrNeg->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_labAbsErrNeg, 5, 1, 1, 1);

        m_editAbsErr1 = new QLineEdit(QActionTimeItemParaEditWidget);
        m_editAbsErr1->setObjectName(QString::fromUtf8("m_editAbsErr1"));
        sizePolicy1.setHeightForWidth(m_editAbsErr1->sizePolicy().hasHeightForWidth());
        m_editAbsErr1->setSizePolicy(sizePolicy1);
        m_editAbsErr1->setMinimumSize(QSize(180, 0));
        m_editAbsErr1->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(m_editAbsErr1, 4, 2, 1, 1);

        m_editAbsErr2 = new QLineEdit(QActionTimeItemParaEditWidget);
        m_editAbsErr2->setObjectName(QString::fromUtf8("m_editAbsErr2"));
        sizePolicy1.setHeightForWidth(m_editAbsErr2->sizePolicy().hasHeightForWidth());
        m_editAbsErr2->setSizePolicy(sizePolicy1);
        m_editAbsErr2->setMinimumSize(QSize(180, 0));
        m_editAbsErr2->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(m_editAbsErr2, 5, 2, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        retranslateUi(QActionTimeItemParaEditWidget);

        QMetaObject::connectSlotsByName(QActionTimeItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QActionTimeItemParaEditWidget)
    {
        QActionTimeItemParaEditWidget->setWindowTitle(QApplication::translate("QActionTimeItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_labAbsErrPos->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_labFaultAngle->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\346\225\205\351\232\234\346\200\201\347\233\270\344\275\215\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labFaultVol->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\346\225\205\351\232\234\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFaultFre->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\346\225\205\351\232\234\346\200\201\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        label_11->setText(QString());
        m_labSettingTime->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\345\212\250\344\275\234\346\227\266\351\227\264\345\256\232\345\200\274(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultCur->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\346\225\205\351\232\234\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labFaultType->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\346\225\205\351\232\234\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labFaultVolType->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\346\225\205\351\232\234\347\224\265\345\216\213:", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(\357\274\205):", 0, QApplication::UnicodeUTF8));
        m_labAbsErrNeg->setText(QApplication::translate("QActionTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QActionTimeItemParaEditWidget: public Ui_QActionTimeItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIONTIMEITEMPARAEDITWIDGET_H
