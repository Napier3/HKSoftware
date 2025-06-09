/********************************************************************************
** Form generated from reading UI file 'PowerDirItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POWERDIRITEMPARAEDITWIDGET_H
#define UI_POWERDIRITEMPARAEDITWIDGET_H

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
#include "../../UI/Controls/SettingCtrls/QSettingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QPowerDirItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QComboBox *m_cbbTestPhase;
    QLineEdit *m_editStepValue;
    QLabel *m_labFaultVol;
    QLabel *m_labFaultCur;
    QLabel *m_labFaultPhase;
    QLineEdit *m_editActionAreaRange;
    QSettingLineEdit *m_editMTA;
    QLineEdit *m_editFaultCur;
    QLineEdit *m_editFaultTime;
    QLabel *m_labMaxSenAng;
    QLineEdit *m_editFaultVol;
    QLabel *m_labTestPhase;
    QLineEdit *m_editAbsErr;
    QLabel *m_labAbsErr;
    QLabel *m_labActionAreaRange;
    QLineEdit *m_editRelErr;
    QLabel *m_labStepValue;
    QLabel *m_labRelErr;
    QComboBox *m_cbbFaultPhase;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labFaultTime;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QPowerDirItemParaEditWidget)
    {
        if (QPowerDirItemParaEditWidget->objectName().isEmpty())
            QPowerDirItemParaEditWidget->setObjectName(QString::fromUtf8("QPowerDirItemParaEditWidget"));
        QPowerDirItemParaEditWidget->resize(600, 391);
        horizontalLayout = new QHBoxLayout(QPowerDirItemParaEditWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(10, -1, 10, -1);
        m_cbbTestPhase = new QComboBox(QPowerDirItemParaEditWidget);
        m_cbbTestPhase->setObjectName(QString::fromUtf8("m_cbbTestPhase"));

        gridLayout->addWidget(m_cbbTestPhase, 0, 2, 1, 1);

        m_editStepValue = new QLineEdit(QPowerDirItemParaEditWidget);
        m_editStepValue->setObjectName(QString::fromUtf8("m_editStepValue"));

        gridLayout->addWidget(m_editStepValue, 2, 5, 1, 1);

        m_labFaultVol = new QLabel(QPowerDirItemParaEditWidget);
        m_labFaultVol->setObjectName(QString::fromUtf8("m_labFaultVol"));

        gridLayout->addWidget(m_labFaultVol, 2, 1, 1, 1);

        m_labFaultCur = new QLabel(QPowerDirItemParaEditWidget);
        m_labFaultCur->setObjectName(QString::fromUtf8("m_labFaultCur"));

        gridLayout->addWidget(m_labFaultCur, 3, 1, 1, 1);

        m_labFaultPhase = new QLabel(QPowerDirItemParaEditWidget);
        m_labFaultPhase->setObjectName(QString::fromUtf8("m_labFaultPhase"));

        gridLayout->addWidget(m_labFaultPhase, 1, 1, 1, 1);

        m_editActionAreaRange = new QLineEdit(QPowerDirItemParaEditWidget);
        m_editActionAreaRange->setObjectName(QString::fromUtf8("m_editActionAreaRange"));

        gridLayout->addWidget(m_editActionAreaRange, 1, 5, 1, 1);

        m_editMTA = new QSettingLineEdit(QPowerDirItemParaEditWidget);
        m_editMTA->setObjectName(QString::fromUtf8("m_editMTA"));

        gridLayout->addWidget(m_editMTA, 0, 5, 1, 1);

        m_editFaultCur = new QLineEdit(QPowerDirItemParaEditWidget);
        m_editFaultCur->setObjectName(QString::fromUtf8("m_editFaultCur"));

        gridLayout->addWidget(m_editFaultCur, 3, 2, 1, 1);

        m_editFaultTime = new QLineEdit(QPowerDirItemParaEditWidget);
        m_editFaultTime->setObjectName(QString::fromUtf8("m_editFaultTime"));

        gridLayout->addWidget(m_editFaultTime, 4, 2, 1, 1);

        m_labMaxSenAng = new QLabel(QPowerDirItemParaEditWidget);
        m_labMaxSenAng->setObjectName(QString::fromUtf8("m_labMaxSenAng"));

        gridLayout->addWidget(m_labMaxSenAng, 0, 4, 1, 1);

        m_editFaultVol = new QLineEdit(QPowerDirItemParaEditWidget);
        m_editFaultVol->setObjectName(QString::fromUtf8("m_editFaultVol"));

        gridLayout->addWidget(m_editFaultVol, 2, 2, 1, 1);

        m_labTestPhase = new QLabel(QPowerDirItemParaEditWidget);
        m_labTestPhase->setObjectName(QString::fromUtf8("m_labTestPhase"));

        gridLayout->addWidget(m_labTestPhase, 0, 1, 1, 1);

        m_editAbsErr = new QLineEdit(QPowerDirItemParaEditWidget);
        m_editAbsErr->setObjectName(QString::fromUtf8("m_editAbsErr"));

        gridLayout->addWidget(m_editAbsErr, 3, 5, 1, 1);

        m_labAbsErr = new QLabel(QPowerDirItemParaEditWidget);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));

        gridLayout->addWidget(m_labAbsErr, 3, 4, 1, 1);

        m_labActionAreaRange = new QLabel(QPowerDirItemParaEditWidget);
        m_labActionAreaRange->setObjectName(QString::fromUtf8("m_labActionAreaRange"));

        gridLayout->addWidget(m_labActionAreaRange, 1, 4, 1, 1);

        m_editRelErr = new QLineEdit(QPowerDirItemParaEditWidget);
        m_editRelErr->setObjectName(QString::fromUtf8("m_editRelErr"));

        gridLayout->addWidget(m_editRelErr, 4, 5, 1, 1);

        m_labStepValue = new QLabel(QPowerDirItemParaEditWidget);
        m_labStepValue->setObjectName(QString::fromUtf8("m_labStepValue"));

        gridLayout->addWidget(m_labStepValue, 2, 4, 1, 1);

        m_labRelErr = new QLabel(QPowerDirItemParaEditWidget);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));

        gridLayout->addWidget(m_labRelErr, 4, 4, 1, 1);

        m_cbbFaultPhase = new QComboBox(QPowerDirItemParaEditWidget);
        m_cbbFaultPhase->setObjectName(QString::fromUtf8("m_cbbFaultPhase"));

        gridLayout->addWidget(m_cbbFaultPhase, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        m_labFaultTime = new QLabel(QPowerDirItemParaEditWidget);
        m_labFaultTime->setObjectName(QString::fromUtf8("m_labFaultTime"));

        gridLayout->addWidget(m_labFaultTime, 4, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 6, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(QPowerDirItemParaEditWidget);

        QMetaObject::connectSlotsByName(QPowerDirItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QPowerDirItemParaEditWidget)
    {
        QPowerDirItemParaEditWidget->setWindowTitle(QApplication::translate("QPowerDirItemParaEditWidget", "QPowerDirItemParaEditWidget", 0, QApplication::UnicodeUTF8));
        m_cbbTestPhase->clear();
        m_cbbTestPhase->insertItems(0, QStringList()
         << QApplication::translate("QPowerDirItemParaEditWidget", "AN", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QPowerDirItemParaEditWidget", "BN", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QPowerDirItemParaEditWidget", "CN", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QPowerDirItemParaEditWidget", "AB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QPowerDirItemParaEditWidget", "BC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QPowerDirItemParaEditWidget", "CA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QPowerDirItemParaEditWidget", "ABC", 0, QApplication::UnicodeUTF8)
        );
        m_labFaultVol->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\346\225\205\351\232\234\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFaultCur->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\346\225\205\351\232\234\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labFaultPhase->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\346\225\205\351\232\234\347\233\270:", 0, QApplication::UnicodeUTF8));
        m_labMaxSenAng->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\346\234\200\345\244\247\347\201\265\346\225\217\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labTestPhase->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\346\265\213\350\257\225\347\233\270:", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labActionAreaRange->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\345\212\250\344\275\234\345\214\272\350\214\203\345\233\264(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labStepValue->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\345\217\230\345\214\226\346\255\245\351\225\277(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(\357\274\205):", 0, QApplication::UnicodeUTF8));
        m_labFaultTime->setText(QApplication::translate("QPowerDirItemParaEditWidget", "\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QPowerDirItemParaEditWidget: public Ui_QPowerDirItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POWERDIRITEMPARAEDITWIDGET_H
