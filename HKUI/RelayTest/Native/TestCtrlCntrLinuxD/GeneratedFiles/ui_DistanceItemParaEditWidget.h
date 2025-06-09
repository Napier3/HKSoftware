/********************************************************************************
** Form generated from reading UI file 'DistanceItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCEITEMPARAEDITWIDGET_H
#define UI_DISTANCEITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDistanceItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QFormLayout *formLayout;
    QLabel *m_labErrType;
    CExBaseListComboBox *m_cmb_ErrorType;
    QLabel *m_labZSetting;
    QSettingLineEdit *m_txtZSetting;
    QLabel *m_labZAng;
    QSettingLineEdit *m_txtZAng;
    QLabel *m_labR;
    QSettingLineEdit *m_txtR;
    QLabel *m_labX;
    QSettingLineEdit *m_txtX;
    QLabel *m_labRate;
    QSettingLineEdit *m_txtRate;
    QLabel *m_labZoneType;
    CExBaseListComboBox *m_cmb_ZoneType;
    QLabel *m_labPlus;
    QSettingLineEdit *m_txtPlus;
    QLabel *m_labRelErr;
    QSettingLineEdit *m_txtRelErr;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout_2;
    QLabel *m_labFaultCurrent;
    QSettingLineEdit *m_txtFaultCurrent;
    QLabel *m_lab_ErrorDirc;
    QComboBox *m_cmb_ErrorDirc;
    QLabel *m_lab_ErrorNature;
    QComboBox *m_cmb_ErrorNature;
    QLabel *m_lablne_TSetting;
    QSettingLineEdit *m_txtTSetting;
    QLabel *m_labK0Mode;
    QComboBox *m_cmbK0Mode;
    QLabel *m_labKlKr;
    QSettingLineEdit *m_txtKlKr;
    QLabel *m_labAngKx;
    QSettingLineEdit *m_txtAngKx;
    QLabel *m_labMinus;
    QSettingLineEdit *m_txtMinus;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QDistanceItemParaEditWidget)
    {
        if (QDistanceItemParaEditWidget->objectName().isEmpty())
            QDistanceItemParaEditWidget->setObjectName(QString::fromUtf8("QDistanceItemParaEditWidget"));
        QDistanceItemParaEditWidget->resize(760, 323);
        horizontalLayout = new QHBoxLayout(QDistanceItemParaEditWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        m_labErrType = new QLabel(QDistanceItemParaEditWidget);
        m_labErrType->setObjectName(QString::fromUtf8("m_labErrType"));
        m_labErrType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, m_labErrType);

        m_cmb_ErrorType = new CExBaseListComboBox(QDistanceItemParaEditWidget);
        m_cmb_ErrorType->setObjectName(QString::fromUtf8("m_cmb_ErrorType"));
        m_cmb_ErrorType->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(0, QFormLayout::FieldRole, m_cmb_ErrorType);

        m_labZSetting = new QLabel(QDistanceItemParaEditWidget);
        m_labZSetting->setObjectName(QString::fromUtf8("m_labZSetting"));
        m_labZSetting->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, m_labZSetting);

        m_txtZSetting = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtZSetting->setObjectName(QString::fromUtf8("m_txtZSetting"));
        m_txtZSetting->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(1, QFormLayout::FieldRole, m_txtZSetting);

        m_labZAng = new QLabel(QDistanceItemParaEditWidget);
        m_labZAng->setObjectName(QString::fromUtf8("m_labZAng"));
        m_labZAng->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, m_labZAng);

        m_txtZAng = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtZAng->setObjectName(QString::fromUtf8("m_txtZAng"));
        m_txtZAng->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(2, QFormLayout::FieldRole, m_txtZAng);

        m_labR = new QLabel(QDistanceItemParaEditWidget);
        m_labR->setObjectName(QString::fromUtf8("m_labR"));
        m_labR->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, m_labR);

        m_txtR = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtR->setObjectName(QString::fromUtf8("m_txtR"));
        m_txtR->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(3, QFormLayout::FieldRole, m_txtR);

        m_labX = new QLabel(QDistanceItemParaEditWidget);
        m_labX->setObjectName(QString::fromUtf8("m_labX"));
        m_labX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(4, QFormLayout::LabelRole, m_labX);

        m_txtX = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtX->setObjectName(QString::fromUtf8("m_txtX"));
        m_txtX->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(4, QFormLayout::FieldRole, m_txtX);

        m_labRate = new QLabel(QDistanceItemParaEditWidget);
        m_labRate->setObjectName(QString::fromUtf8("m_labRate"));
        m_labRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(5, QFormLayout::LabelRole, m_labRate);

        m_txtRate = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtRate->setObjectName(QString::fromUtf8("m_txtRate"));
        m_txtRate->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(5, QFormLayout::FieldRole, m_txtRate);

        m_labZoneType = new QLabel(QDistanceItemParaEditWidget);
        m_labZoneType->setObjectName(QString::fromUtf8("m_labZoneType"));
        m_labZoneType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(6, QFormLayout::LabelRole, m_labZoneType);

        m_cmb_ZoneType = new CExBaseListComboBox(QDistanceItemParaEditWidget);
        m_cmb_ZoneType->setObjectName(QString::fromUtf8("m_cmb_ZoneType"));
        m_cmb_ZoneType->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(6, QFormLayout::FieldRole, m_cmb_ZoneType);

        m_labPlus = new QLabel(QDistanceItemParaEditWidget);
        m_labPlus->setObjectName(QString::fromUtf8("m_labPlus"));

        formLayout->setWidget(7, QFormLayout::LabelRole, m_labPlus);

        m_txtPlus = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtPlus->setObjectName(QString::fromUtf8("m_txtPlus"));
        m_txtPlus->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(7, QFormLayout::FieldRole, m_txtPlus);

        m_labRelErr = new QLabel(QDistanceItemParaEditWidget);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        m_labRelErr->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(8, QFormLayout::LabelRole, m_labRelErr);

        m_txtRelErr = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtRelErr->setObjectName(QString::fromUtf8("m_txtRelErr"));
        m_txtRelErr->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(8, QFormLayout::FieldRole, m_txtRelErr);


        horizontalLayout->addLayout(formLayout);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        m_labFaultCurrent = new QLabel(QDistanceItemParaEditWidget);
        m_labFaultCurrent->setObjectName(QString::fromUtf8("m_labFaultCurrent"));
        m_labFaultCurrent->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, m_labFaultCurrent);

        m_txtFaultCurrent = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtFaultCurrent->setObjectName(QString::fromUtf8("m_txtFaultCurrent"));
        m_txtFaultCurrent->setMinimumSize(QSize(200, 0));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, m_txtFaultCurrent);

        m_lab_ErrorDirc = new QLabel(QDistanceItemParaEditWidget);
        m_lab_ErrorDirc->setObjectName(QString::fromUtf8("m_lab_ErrorDirc"));
        m_lab_ErrorDirc->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, m_lab_ErrorDirc);

        m_cmb_ErrorDirc = new QComboBox(QDistanceItemParaEditWidget);
        m_cmb_ErrorDirc->setObjectName(QString::fromUtf8("m_cmb_ErrorDirc"));
        m_cmb_ErrorDirc->setMinimumSize(QSize(200, 0));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, m_cmb_ErrorDirc);

        m_lab_ErrorNature = new QLabel(QDistanceItemParaEditWidget);
        m_lab_ErrorNature->setObjectName(QString::fromUtf8("m_lab_ErrorNature"));
        m_lab_ErrorNature->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, m_lab_ErrorNature);

        m_cmb_ErrorNature = new QComboBox(QDistanceItemParaEditWidget);
        m_cmb_ErrorNature->setObjectName(QString::fromUtf8("m_cmb_ErrorNature"));
        m_cmb_ErrorNature->setMinimumSize(QSize(200, 0));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, m_cmb_ErrorNature);

        m_lablne_TSetting = new QLabel(QDistanceItemParaEditWidget);
        m_lablne_TSetting->setObjectName(QString::fromUtf8("m_lablne_TSetting"));
        m_lablne_TSetting->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, m_lablne_TSetting);

        m_txtTSetting = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtTSetting->setObjectName(QString::fromUtf8("m_txtTSetting"));
        m_txtTSetting->setMinimumSize(QSize(200, 0));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, m_txtTSetting);

        m_labK0Mode = new QLabel(QDistanceItemParaEditWidget);
        m_labK0Mode->setObjectName(QString::fromUtf8("m_labK0Mode"));
        m_labK0Mode->setMinimumSize(QSize(80, 0));
        m_labK0Mode->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, m_labK0Mode);

        m_cmbK0Mode = new QComboBox(QDistanceItemParaEditWidget);
        m_cmbK0Mode->setObjectName(QString::fromUtf8("m_cmbK0Mode"));
        m_cmbK0Mode->setMinimumSize(QSize(200, 0));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, m_cmbK0Mode);

        m_labKlKr = new QLabel(QDistanceItemParaEditWidget);
        m_labKlKr->setObjectName(QString::fromUtf8("m_labKlKr"));
        m_labKlKr->setMinimumSize(QSize(80, 0));
        m_labKlKr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout_2->setWidget(5, QFormLayout::LabelRole, m_labKlKr);

        m_txtKlKr = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtKlKr->setObjectName(QString::fromUtf8("m_txtKlKr"));
        m_txtKlKr->setMinimumSize(QSize(200, 0));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, m_txtKlKr);

        m_labAngKx = new QLabel(QDistanceItemParaEditWidget);
        m_labAngKx->setObjectName(QString::fromUtf8("m_labAngKx"));
        m_labAngKx->setMinimumSize(QSize(80, 0));
        m_labAngKx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout_2->setWidget(6, QFormLayout::LabelRole, m_labAngKx);

        m_txtAngKx = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtAngKx->setObjectName(QString::fromUtf8("m_txtAngKx"));
        m_txtAngKx->setMinimumSize(QSize(200, 0));

        formLayout_2->setWidget(6, QFormLayout::FieldRole, m_txtAngKx);

        m_labMinus = new QLabel(QDistanceItemParaEditWidget);
        m_labMinus->setObjectName(QString::fromUtf8("m_labMinus"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, m_labMinus);

        m_txtMinus = new QSettingLineEdit(QDistanceItemParaEditWidget);
        m_txtMinus->setObjectName(QString::fromUtf8("m_txtMinus"));
        m_txtMinus->setMinimumSize(QSize(200, 0));

        formLayout_2->setWidget(7, QFormLayout::FieldRole, m_txtMinus);


        horizontalLayout->addLayout(formLayout_2);

        horizontalSpacer_3 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        retranslateUi(QDistanceItemParaEditWidget);

        QMetaObject::connectSlotsByName(QDistanceItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QDistanceItemParaEditWidget)
    {
        QDistanceItemParaEditWidget->setWindowTitle(QApplication::translate("QDistanceItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_labErrType->setText(QApplication::translate("QDistanceItemParaEditWidget", "\346\225\205\351\232\234\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labZSetting->setText(QApplication::translate("QDistanceItemParaEditWidget", "\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labZAng->setText(QApplication::translate("QDistanceItemParaEditWidget", "\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labR->setText(QApplication::translate("QDistanceItemParaEditWidget", "R(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labX->setText(QApplication::translate("QDistanceItemParaEditWidget", "X(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labRate->setText(QApplication::translate("QDistanceItemParaEditWidget", "\347\231\276\345\210\206\346\257\224(%):", 0, QApplication::UnicodeUTF8));
        m_labZoneType->setText(QApplication::translate("QDistanceItemParaEditWidget", "\345\214\272\346\256\265\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_labPlus->setText(QApplication::translate("QDistanceItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QDistanceItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_labFaultCurrent->setText(QApplication::translate("QDistanceItemParaEditWidget", "\347\237\255\350\267\257\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_lab_ErrorDirc->setText(QApplication::translate("QDistanceItemParaEditWidget", "\346\225\205\351\232\234\346\226\271\345\220\221:", 0, QApplication::UnicodeUTF8));
        m_lab_ErrorNature->setText(QApplication::translate("QDistanceItemParaEditWidget", "\346\225\205\351\232\234\346\200\247\350\264\250:", 0, QApplication::UnicodeUTF8));
        m_lablne_TSetting->setText(QApplication::translate("QDistanceItemParaEditWidget", "\346\227\266\351\227\264\345\256\232\345\200\274(s):", 0, QApplication::UnicodeUTF8));
        m_labK0Mode->setText(QApplication::translate("QDistanceItemParaEditWidget", "\351\233\266\345\272\217\350\241\245\345\201\277\347\263\273\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labKlKr->setText(QString());
        m_labAngKx->setText(QString());
        m_labMinus->setText(QApplication::translate("QDistanceItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceItemParaEditWidget: public Ui_QDistanceItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCEITEMPARAEDITWIDGET_H
