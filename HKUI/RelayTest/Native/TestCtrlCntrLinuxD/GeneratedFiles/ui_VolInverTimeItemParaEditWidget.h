/********************************************************************************
** Form generated from reading UI file 'VolInverTimeItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLINVERTIMEITEMPARAEDITWIDGET_H
#define UI_VOLINVERTIMEITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QVolInverTimeItemParaEditWidget
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *m_labHz;
    QSettingLineEdit *m_txtHz;
    QSettingLineEdit *m_txtAng;
    QLabel *m_labErrType;
    QComboBox *m_cmb_ErrorType;
    QLabel *m_labVolt;
    QSettingLineEdit *m_txtVolt;
    QLabel *m_labAng;
    QLabel *m_labFaultCurr;
    QSettingLineEdit *m_txtFaultCurr;
    QLabel *m_labAbsErr;
    QSpacerItem *horizontalSpacer_3;
    QLabel *m_labMinus;
    QSettingLineEdit *m_txtMinus;
    QLabel *m_labRelErr;
    QSettingLineEdit *m_txtRelErr;
    QSpacerItem *horizontalSpacer_2;
    QSettingLineEdit *m_txtTSetting;
    QLabel *m_lablne_TSetting;
    QSpacerItem *horizontalSpacer;
    QSettingLineEdit *m_txtPlus;

    void setupUi(QWidget *QVolInverTimeItemParaEditWidget)
    {
        if (QVolInverTimeItemParaEditWidget->objectName().isEmpty())
            QVolInverTimeItemParaEditWidget->setObjectName(QString::fromUtf8("QVolInverTimeItemParaEditWidget"));
        QVolInverTimeItemParaEditWidget->resize(513, 218);
        gridLayout_2 = new QGridLayout(QVolInverTimeItemParaEditWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(QVolInverTimeItemParaEditWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        m_labHz = new QLabel(groupBox);
        m_labHz->setObjectName(QString::fromUtf8("m_labHz"));
        sizePolicy.setHeightForWidth(m_labHz->sizePolicy().hasHeightForWidth());
        m_labHz->setSizePolicy(sizePolicy);
        m_labHz->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labHz, 5, 1, 1, 1);

        m_txtHz = new QSettingLineEdit(groupBox);
        m_txtHz->setObjectName(QString::fromUtf8("m_txtHz"));

        gridLayout->addWidget(m_txtHz, 5, 2, 1, 1);

        m_txtAng = new QSettingLineEdit(groupBox);
        m_txtAng->setObjectName(QString::fromUtf8("m_txtAng"));

        gridLayout->addWidget(m_txtAng, 3, 2, 1, 1);

        m_labErrType = new QLabel(groupBox);
        m_labErrType->setObjectName(QString::fromUtf8("m_labErrType"));
        sizePolicy.setHeightForWidth(m_labErrType->sizePolicy().hasHeightForWidth());
        m_labErrType->setSizePolicy(sizePolicy);
        m_labErrType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labErrType, 0, 1, 1, 1);

        m_cmb_ErrorType = new QComboBox(groupBox);
        m_cmb_ErrorType->setObjectName(QString::fromUtf8("m_cmb_ErrorType"));

        gridLayout->addWidget(m_cmb_ErrorType, 0, 2, 1, 1);

        m_labVolt = new QLabel(groupBox);
        m_labVolt->setObjectName(QString::fromUtf8("m_labVolt"));
        sizePolicy.setHeightForWidth(m_labVolt->sizePolicy().hasHeightForWidth());
        m_labVolt->setSizePolicy(sizePolicy);
        m_labVolt->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labVolt, 1, 1, 1, 1);

        m_txtVolt = new QSettingLineEdit(groupBox);
        m_txtVolt->setObjectName(QString::fromUtf8("m_txtVolt"));

        gridLayout->addWidget(m_txtVolt, 1, 2, 1, 1);

        m_labAng = new QLabel(groupBox);
        m_labAng->setObjectName(QString::fromUtf8("m_labAng"));
        sizePolicy.setHeightForWidth(m_labAng->sizePolicy().hasHeightForWidth());
        m_labAng->setSizePolicy(sizePolicy);
        m_labAng->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labAng, 3, 1, 1, 1);

        m_labFaultCurr = new QLabel(groupBox);
        m_labFaultCurr->setObjectName(QString::fromUtf8("m_labFaultCurr"));
        sizePolicy.setHeightForWidth(m_labFaultCurr->sizePolicy().hasHeightForWidth());
        m_labFaultCurr->setSizePolicy(sizePolicy);
        m_labFaultCurr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labFaultCurr, 2, 1, 1, 1);

        m_txtFaultCurr = new QSettingLineEdit(groupBox);
        m_txtFaultCurr->setObjectName(QString::fromUtf8("m_txtFaultCurr"));

        gridLayout->addWidget(m_txtFaultCurr, 2, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 1, 5, 1);

        m_labAbsErr = new QLabel(QVolInverTimeItemParaEditWidget);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        sizePolicy.setHeightForWidth(m_labAbsErr->sizePolicy().hasHeightForWidth());
        m_labAbsErr->setSizePolicy(sizePolicy);
        m_labAbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labAbsErr, 2, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 5, 1, 1);

        m_labMinus = new QLabel(QVolInverTimeItemParaEditWidget);
        m_labMinus->setObjectName(QString::fromUtf8("m_labMinus"));
        sizePolicy.setHeightForWidth(m_labMinus->sizePolicy().hasHeightForWidth());
        m_labMinus->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_labMinus, 3, 3, 1, 1);

        m_txtMinus = new QSettingLineEdit(QVolInverTimeItemParaEditWidget);
        m_txtMinus->setObjectName(QString::fromUtf8("m_txtMinus"));

        gridLayout_2->addWidget(m_txtMinus, 3, 4, 1, 1);

        m_labRelErr = new QLabel(QVolInverTimeItemParaEditWidget);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        sizePolicy.setHeightForWidth(m_labRelErr->sizePolicy().hasHeightForWidth());
        m_labRelErr->setSizePolicy(sizePolicy);
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labRelErr, 4, 3, 1, 1);

        m_txtRelErr = new QSettingLineEdit(QVolInverTimeItemParaEditWidget);
        m_txtRelErr->setObjectName(QString::fromUtf8("m_txtRelErr"));

        gridLayout_2->addWidget(m_txtRelErr, 4, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        m_txtTSetting = new QSettingLineEdit(QVolInverTimeItemParaEditWidget);
        m_txtTSetting->setObjectName(QString::fromUtf8("m_txtTSetting"));

        gridLayout_2->addWidget(m_txtTSetting, 0, 4, 1, 1);

        m_lablne_TSetting = new QLabel(QVolInverTimeItemParaEditWidget);
        m_lablne_TSetting->setObjectName(QString::fromUtf8("m_lablne_TSetting"));
        sizePolicy.setHeightForWidth(m_lablne_TSetting->sizePolicy().hasHeightForWidth());
        m_lablne_TSetting->setSizePolicy(sizePolicy);
        m_lablne_TSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_lablne_TSetting, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 2, 1, 1);

        m_txtPlus = new QSettingLineEdit(QVolInverTimeItemParaEditWidget);
        m_txtPlus->setObjectName(QString::fromUtf8("m_txtPlus"));

        gridLayout_2->addWidget(m_txtPlus, 2, 4, 1, 1);


        retranslateUi(QVolInverTimeItemParaEditWidget);

        QMetaObject::connectSlotsByName(QVolInverTimeItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QVolInverTimeItemParaEditWidget)
    {
        QVolInverTimeItemParaEditWidget->setWindowTitle(QApplication::translate("QVolInverTimeItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QVolInverTimeItemParaEditWidget", "\346\225\205\351\232\234\346\200\201\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        m_labHz->setText(QApplication::translate("QVolInverTimeItemParaEditWidget", "\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labErrType->setText(QApplication::translate("QVolInverTimeItemParaEditWidget", "\346\225\205\351\232\234\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labVolt->setText(QApplication::translate("QVolInverTimeItemParaEditWidget", "\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labAng->setText(QApplication::translate("QVolInverTimeItemParaEditWidget", "\347\233\270\344\275\215\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labFaultCurr->setText(QApplication::translate("QVolInverTimeItemParaEditWidget", "\347\237\255\350\267\257\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QVolInverTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_labMinus->setText(QApplication::translate("QVolInverTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QVolInverTimeItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_lablne_TSetting->setText(QApplication::translate("QVolInverTimeItemParaEditWidget", "\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QVolInverTimeItemParaEditWidget: public Ui_QVolInverTimeItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLINVERTIMEITEMPARAEDITWIDGET_H
