/********************************************************************************
** Form generated from reading UI file 'CurrInverTimeItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CURRINVERTIMEITEMPARAEDITWIDGET_H
#define UI_CURRINVERTIMEITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QCurrInverTimeItemParaEditWidget
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *m_labAng;
    QLabel *m_labHz;
    QLabel *m_labErrType;
    QComboBox *m_cmbFaultVolt;
    QLabel *m_labCurrent;
    QLabel *m_labFaultVolt;
    QSettingLineEdit *m_txtAng;
    QComboBox *m_cmb_ErrorType;
    QSettingLineEdit *m_txtHz;
    QSettingLineEdit *m_txtFaultVolt;
    QSettingLineEdit *m_txtCurrent;
    QLabel *m_lablne_TSetting;
    QSpacerItem *horizontalSpacer;
    QSettingLineEdit *m_txtTSetting;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *m_labAbsErr;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labPlus;
    QSettingLineEdit *m_txtPlus;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labRelErr;
    QSettingLineEdit *m_txtRelErr;
    QLabel *m_labAbsErr_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labMinus;
    QSettingLineEdit *m_txtMinus;

    void setupUi(QWidget *QCurrInverTimeItemParaEditWidget)
    {
        if (QCurrInverTimeItemParaEditWidget->objectName().isEmpty())
            QCurrInverTimeItemParaEditWidget->setObjectName(QString::fromUtf8("QCurrInverTimeItemParaEditWidget"));
        QCurrInverTimeItemParaEditWidget->resize(797, 358);
        gridLayout_4 = new QGridLayout(QCurrInverTimeItemParaEditWidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(QCurrInverTimeItemParaEditWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labAng = new QLabel(groupBox);
        m_labAng->setObjectName(QString::fromUtf8("m_labAng"));
        m_labAng->setMinimumSize(QSize(80, 0));
        m_labAng->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labAng, 1, 4, 1, 1);

        m_labHz = new QLabel(groupBox);
        m_labHz->setObjectName(QString::fromUtf8("m_labHz"));
        m_labHz->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labHz, 4, 0, 1, 1);

        m_labErrType = new QLabel(groupBox);
        m_labErrType->setObjectName(QString::fromUtf8("m_labErrType"));
        m_labErrType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labErrType, 0, 0, 1, 1);

        m_cmbFaultVolt = new QComboBox(groupBox);
        m_cmbFaultVolt->setObjectName(QString::fromUtf8("m_cmbFaultVolt"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_cmbFaultVolt->sizePolicy().hasHeightForWidth());
        m_cmbFaultVolt->setSizePolicy(sizePolicy);
        m_cmbFaultVolt->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(m_cmbFaultVolt, 1, 2, 1, 1);

        m_labCurrent = new QLabel(groupBox);
        m_labCurrent->setObjectName(QString::fromUtf8("m_labCurrent"));
        m_labCurrent->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labCurrent, 0, 4, 1, 1);

        m_labFaultVolt = new QLabel(groupBox);
        m_labFaultVolt->setObjectName(QString::fromUtf8("m_labFaultVolt"));
        m_labFaultVolt->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labFaultVolt, 1, 0, 1, 1);

        m_txtAng = new QSettingLineEdit(groupBox);
        m_txtAng->setObjectName(QString::fromUtf8("m_txtAng"));
        sizePolicy.setHeightForWidth(m_txtAng->sizePolicy().hasHeightForWidth());
        m_txtAng->setSizePolicy(sizePolicy);
        m_txtAng->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_txtAng, 1, 5, 1, 1);

        m_cmb_ErrorType = new QComboBox(groupBox);
        m_cmb_ErrorType->setObjectName(QString::fromUtf8("m_cmb_ErrorType"));
        sizePolicy.setHeightForWidth(m_cmb_ErrorType->sizePolicy().hasHeightForWidth());
        m_cmb_ErrorType->setSizePolicy(sizePolicy);
        m_cmb_ErrorType->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_cmb_ErrorType, 0, 1, 1, 1);

        m_txtHz = new QSettingLineEdit(groupBox);
        m_txtHz->setObjectName(QString::fromUtf8("m_txtHz"));
        sizePolicy.setHeightForWidth(m_txtHz->sizePolicy().hasHeightForWidth());
        m_txtHz->setSizePolicy(sizePolicy);
        m_txtHz->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_txtHz, 4, 1, 1, 1);

        m_txtFaultVolt = new QSettingLineEdit(groupBox);
        m_txtFaultVolt->setObjectName(QString::fromUtf8("m_txtFaultVolt"));
        sizePolicy.setHeightForWidth(m_txtFaultVolt->sizePolicy().hasHeightForWidth());
        m_txtFaultVolt->setSizePolicy(sizePolicy);
        m_txtFaultVolt->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_txtFaultVolt, 1, 1, 1, 1);

        m_txtCurrent = new QSettingLineEdit(groupBox);
        m_txtCurrent->setObjectName(QString::fromUtf8("m_txtCurrent"));
        sizePolicy.setHeightForWidth(m_txtCurrent->sizePolicy().hasHeightForWidth());
        m_txtCurrent->setSizePolicy(sizePolicy);
        m_txtCurrent->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_txtCurrent, 0, 5, 1, 1);

        m_lablne_TSetting = new QLabel(groupBox);
        m_lablne_TSetting->setObjectName(QString::fromUtf8("m_lablne_TSetting"));
        m_lablne_TSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_lablne_TSetting, 4, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);

        m_txtTSetting = new QSettingLineEdit(groupBox);
        m_txtTSetting->setObjectName(QString::fromUtf8("m_txtTSetting"));
        sizePolicy.setHeightForWidth(m_txtTSetting->sizePolicy().hasHeightForWidth());
        m_txtTSetting->setSizePolicy(sizePolicy);
        m_txtTSetting->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_txtTSetting, 4, 5, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        frame = new QFrame(QCurrInverTimeItemParaEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(16777215, 100));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_labAbsErr = new QLabel(frame);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));
        m_labAbsErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labAbsErr, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labPlus = new QLabel(frame);
        m_labPlus->setObjectName(QString::fromUtf8("m_labPlus"));

        horizontalLayout->addWidget(m_labPlus);

        m_txtPlus = new QSettingLineEdit(frame);
        m_txtPlus->setObjectName(QString::fromUtf8("m_txtPlus"));
        sizePolicy.setHeightForWidth(m_txtPlus->sizePolicy().hasHeightForWidth());
        m_txtPlus->setSizePolicy(sizePolicy);
        m_txtPlus->setMinimumSize(QSize(180, 0));

        horizontalLayout->addWidget(m_txtPlus);


        gridLayout_2->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        m_labRelErr = new QLabel(frame);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));
        m_labRelErr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labRelErr, 0, 3, 1, 1);

        m_txtRelErr = new QSettingLineEdit(frame);
        m_txtRelErr->setObjectName(QString::fromUtf8("m_txtRelErr"));
        sizePolicy.setHeightForWidth(m_txtRelErr->sizePolicy().hasHeightForWidth());
        m_txtRelErr->setSizePolicy(sizePolicy);
        m_txtRelErr->setMinimumSize(QSize(185, 0));

        gridLayout_2->addWidget(m_txtRelErr, 0, 4, 1, 1);

        m_labAbsErr_2 = new QLabel(frame);
        m_labAbsErr_2->setObjectName(QString::fromUtf8("m_labAbsErr_2"));
        m_labAbsErr_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labAbsErr_2, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labMinus = new QLabel(frame);
        m_labMinus->setObjectName(QString::fromUtf8("m_labMinus"));

        horizontalLayout_2->addWidget(m_labMinus);

        m_txtMinus = new QSettingLineEdit(frame);
        m_txtMinus->setObjectName(QString::fromUtf8("m_txtMinus"));
        sizePolicy.setHeightForWidth(m_txtMinus->sizePolicy().hasHeightForWidth());
        m_txtMinus->setSizePolicy(sizePolicy);
        m_txtMinus->setMinimumSize(QSize(180, 0));

        horizontalLayout_2->addWidget(m_txtMinus);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 1, 1, 1);


        gridLayout_3->addWidget(frame, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        retranslateUi(QCurrInverTimeItemParaEditWidget);

        QMetaObject::connectSlotsByName(QCurrInverTimeItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QCurrInverTimeItemParaEditWidget)
    {
        QCurrInverTimeItemParaEditWidget->setWindowTitle(QApplication::translate("QCurrInverTimeItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\346\225\205\351\232\234\346\200\201\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        m_labAng->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\347\233\270\344\275\215\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labHz->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labErrType->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\346\225\205\351\232\234\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labCurrent->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\347\224\265\346\265\201(I*):", 0, QApplication::UnicodeUTF8));
        m_labFaultVolt->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\347\237\255\350\267\257\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_lablne_TSetting->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s):", 0, QApplication::UnicodeUTF8));
        m_labPlus->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "+", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr_2->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s):", 0, QApplication::UnicodeUTF8));
        m_labMinus->setText(QApplication::translate("QCurrInverTimeItemParaEditWidget", "-", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCurrInverTimeItemParaEditWidget: public Ui_QCurrInverTimeItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CURRINVERTIMEITEMPARAEDITWIDGET_H
