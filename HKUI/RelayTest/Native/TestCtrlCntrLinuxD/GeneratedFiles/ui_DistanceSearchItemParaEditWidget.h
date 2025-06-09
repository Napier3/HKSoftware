/********************************************************************************
** Form generated from reading UI file 'DistanceSearchItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCESEARCHITEMPARAEDITWIDGET_H
#define UI_DISTANCESEARCHITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QDistanceSearchItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *m_gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labEndZAng;
    QLabel *m_labEndZ;
    QLineEdit *m_editAbsErr;
    QLabel *m_labRelErr;
    QLineEdit *m_editFaultVf;
    QLineEdit *m_editTSetting;
    QLineEdit *m_editEndVal;
    QLabel *m_labAbsErr;
    QLineEdit *m_editEndValAng;
    QLabel *m_labFaultType;
    QLineEdit *m_editRelErr;
    CExBaseListComboBox *m_cbbFaultType;
    QLineEdit *m_editFaultIf;
    QLabel *m_labFaultCur;
    QLabel *m_labFaultVol;
    QLabel *m_labTSetting;
    QSpacerItem *horizontalSpacer;
    QLabel *m_labStep;
    QLineEdit *m_editBeginVal;
    QLabel *m_labBegZ;
    QLabel *m_labBegZAng;
    QLineEdit *m_editStep;
    QLabel *m_labZoneType;
    CExBaseListComboBox *m_cbbZoneType;
    QLineEdit *m_editBeginValAng;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QDistanceSearchItemParaEditWidget)
    {
        if (QDistanceSearchItemParaEditWidget->objectName().isEmpty())
            QDistanceSearchItemParaEditWidget->setObjectName(QString::fromUtf8("QDistanceSearchItemParaEditWidget"));
        QDistanceSearchItemParaEditWidget->resize(670, 407);
        horizontalLayout = new QHBoxLayout(QDistanceSearchItemParaEditWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_gridLayout = new QGridLayout();
        m_gridLayout->setSpacing(6);
        m_gridLayout->setObjectName(QString::fromUtf8("m_gridLayout"));
        m_gridLayout->setContentsMargins(-1, -1, 10, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        m_labEndZAng = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labEndZAng->setObjectName(QString::fromUtf8("m_labEndZAng"));
        m_labEndZAng->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labEndZAng, 7, 1, 1, 1);

        m_labEndZ = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labEndZ->setObjectName(QString::fromUtf8("m_labEndZ"));
        m_labEndZ->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labEndZ, 6, 1, 1, 1);

        m_editAbsErr = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editAbsErr->setObjectName(QString::fromUtf8("m_editAbsErr"));

        m_gridLayout->addWidget(m_editAbsErr, 6, 5, 1, 1);

        m_labRelErr = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labRelErr, 7, 4, 1, 1);

        m_editFaultVf = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editFaultVf->setObjectName(QString::fromUtf8("m_editFaultVf"));

        m_gridLayout->addWidget(m_editFaultVf, 3, 5, 1, 1);

        m_editTSetting = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editTSetting->setObjectName(QString::fromUtf8("m_editTSetting"));

        m_gridLayout->addWidget(m_editTSetting, 4, 5, 1, 1);

        m_editEndVal = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editEndVal->setObjectName(QString::fromUtf8("m_editEndVal"));

        m_gridLayout->addWidget(m_editEndVal, 6, 2, 1, 1);

        m_labAbsErr = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        m_labAbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labAbsErr, 6, 4, 1, 1);

        m_editEndValAng = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editEndValAng->setObjectName(QString::fromUtf8("m_editEndValAng"));

        m_gridLayout->addWidget(m_editEndValAng, 7, 2, 1, 1);

        m_labFaultType = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labFaultType->setObjectName(QString::fromUtf8("m_labFaultType"));
        m_labFaultType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labFaultType, 0, 1, 1, 1);

        m_editRelErr = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editRelErr->setObjectName(QString::fromUtf8("m_editRelErr"));

        m_gridLayout->addWidget(m_editRelErr, 7, 5, 1, 1);

        m_cbbFaultType = new CExBaseListComboBox(QDistanceSearchItemParaEditWidget);
        m_cbbFaultType->setObjectName(QString::fromUtf8("m_cbbFaultType"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_cbbFaultType->sizePolicy().hasHeightForWidth());
        m_cbbFaultType->setSizePolicy(sizePolicy);

        m_gridLayout->addWidget(m_cbbFaultType, 0, 2, 1, 1);

        m_editFaultIf = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editFaultIf->setObjectName(QString::fromUtf8("m_editFaultIf"));

        m_gridLayout->addWidget(m_editFaultIf, 1, 5, 1, 1);

        m_labFaultCur = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labFaultCur->setObjectName(QString::fromUtf8("m_labFaultCur"));
        m_labFaultCur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labFaultCur, 1, 4, 1, 1);

        m_labFaultVol = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labFaultVol->setObjectName(QString::fromUtf8("m_labFaultVol"));
        m_labFaultVol->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labFaultVol, 3, 4, 1, 1);

        m_labTSetting = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labTSetting->setObjectName(QString::fromUtf8("m_labTSetting"));
        m_labTSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labTSetting, 4, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        m_labStep = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labStep->setObjectName(QString::fromUtf8("m_labStep"));
        m_labStep->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labStep, 0, 4, 1, 1);

        m_editBeginVal = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editBeginVal->setObjectName(QString::fromUtf8("m_editBeginVal"));

        m_gridLayout->addWidget(m_editBeginVal, 3, 2, 1, 1);

        m_labBegZ = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labBegZ->setObjectName(QString::fromUtf8("m_labBegZ"));
        m_labBegZ->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labBegZ, 3, 1, 1, 1);

        m_labBegZAng = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labBegZAng->setObjectName(QString::fromUtf8("m_labBegZAng"));
        m_labBegZAng->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labBegZAng, 4, 1, 1, 1);

        m_editStep = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editStep->setObjectName(QString::fromUtf8("m_editStep"));

        m_gridLayout->addWidget(m_editStep, 0, 5, 1, 1);

        m_labZoneType = new QLabel(QDistanceSearchItemParaEditWidget);
        m_labZoneType->setObjectName(QString::fromUtf8("m_labZoneType"));
        m_labZoneType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        m_gridLayout->addWidget(m_labZoneType, 1, 1, 1, 1);

        m_cbbZoneType = new CExBaseListComboBox(QDistanceSearchItemParaEditWidget);
        m_cbbZoneType->setObjectName(QString::fromUtf8("m_cbbZoneType"));

        m_gridLayout->addWidget(m_cbbZoneType, 1, 2, 1, 1);

        m_editBeginValAng = new QLineEdit(QDistanceSearchItemParaEditWidget);
        m_editBeginValAng->setObjectName(QString::fromUtf8("m_editBeginValAng"));

        m_gridLayout->addWidget(m_editBeginValAng, 4, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_gridLayout->addItem(horizontalSpacer_3, 0, 6, 1, 1);


        horizontalLayout->addLayout(m_gridLayout);


        retranslateUi(QDistanceSearchItemParaEditWidget);

        QMetaObject::connectSlotsByName(QDistanceSearchItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QDistanceSearchItemParaEditWidget)
    {
        QDistanceSearchItemParaEditWidget->setWindowTitle(QApplication::translate("QDistanceSearchItemParaEditWidget", "QRecloseAccItemParaEditWidget", 0, QApplication::UnicodeUTF8));
        m_labEndZAng->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\346\234\253\347\253\257\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labEndZ->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\346\234\253\347\253\257\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(\357\274\205):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labFaultType->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\346\225\205\351\232\234\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labFaultCur->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\347\237\255\350\267\257\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labFaultVol->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\347\237\255\350\267\257\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labTSetting->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\346\227\266\351\227\264\345\256\232\345\200\274(s):", 0, QApplication::UnicodeUTF8));
        m_labStep->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\351\230\273\346\212\227\346\255\245\351\225\277(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labBegZ->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\351\246\226\347\253\257\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labBegZAng->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\351\246\226\347\253\257\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labZoneType->setText(QApplication::translate("QDistanceSearchItemParaEditWidget", "\345\214\272\346\256\265:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceSearchItemParaEditWidget: public Ui_QDistanceSearchItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCESEARCHITEMPARAEDITWIDGET_H
