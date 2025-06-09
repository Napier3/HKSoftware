/********************************************************************************
** Form generated from reading UI file 'CurrInverCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CURRINVERCOMMONPARASDLG_H
#define UI_CURRINVERCOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QCurrInverseCommonParasDlg
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *m_labPreFaultTime;
    QSpacerItem *horizontalSpacer;
    QSettingLineEdit *m_txtPreFaultTime;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labFaultVolt;
    QSettingLineEdit *m_txtFaultVolt;
    QLabel *m_labFaultCurr;
    QSettingLineEdit *m_txtFaultCurr;
    QLabel *m_labAng;
    QSettingLineEdit *m_txtAng;
    QLabel *m_labHz;
    QSettingLineEdit *m_txtHz;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *m_cmbValue;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_2;
    QSettingLineEdit *m_txtIn;
    QLabel *label_3;
    QComboBox *m_cmbCTPos;
    QLabel *label_4;
    QSettingLineEdit *m_txtIp;
    QLabel *label_5;
    QSettingLineEdit *m_txtFaultTime;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *m_btnOK;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QDialog *QCurrInverseCommonParasDlg)
    {
        if (QCurrInverseCommonParasDlg->objectName().isEmpty())
            QCurrInverseCommonParasDlg->setObjectName(QString::fromUtf8("QCurrInverseCommonParasDlg"));
        QCurrInverseCommonParasDlg->resize(354, 505);
        gridLayout_4 = new QGridLayout(QCurrInverseCommonParasDlg);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(QCurrInverseCommonParasDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        m_labPreFaultTime = new QLabel(groupBox);
        m_labPreFaultTime->setObjectName(QString::fromUtf8("m_labPreFaultTime"));

        gridLayout->addWidget(m_labPreFaultTime, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        m_txtPreFaultTime = new QSettingLineEdit(groupBox);
        m_txtPreFaultTime->setObjectName(QString::fromUtf8("m_txtPreFaultTime"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_txtPreFaultTime->sizePolicy().hasHeightForWidth());
        m_txtPreFaultTime->setSizePolicy(sizePolicy);
        m_txtPreFaultTime->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(m_txtPreFaultTime, 0, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 4, 1, 1);

        m_labFaultVolt = new QLabel(groupBox);
        m_labFaultVolt->setObjectName(QString::fromUtf8("m_labFaultVolt"));

        gridLayout->addWidget(m_labFaultVolt, 1, 1, 1, 1);

        m_txtFaultVolt = new QSettingLineEdit(groupBox);
        m_txtFaultVolt->setObjectName(QString::fromUtf8("m_txtFaultVolt"));
        sizePolicy.setHeightForWidth(m_txtFaultVolt->sizePolicy().hasHeightForWidth());
        m_txtFaultVolt->setSizePolicy(sizePolicy);
        m_txtFaultVolt->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(m_txtFaultVolt, 1, 3, 1, 1);

        m_labFaultCurr = new QLabel(groupBox);
        m_labFaultCurr->setObjectName(QString::fromUtf8("m_labFaultCurr"));

        gridLayout->addWidget(m_labFaultCurr, 2, 1, 1, 1);

        m_txtFaultCurr = new QSettingLineEdit(groupBox);
        m_txtFaultCurr->setObjectName(QString::fromUtf8("m_txtFaultCurr"));
        sizePolicy.setHeightForWidth(m_txtFaultCurr->sizePolicy().hasHeightForWidth());
        m_txtFaultCurr->setSizePolicy(sizePolicy);
        m_txtFaultCurr->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(m_txtFaultCurr, 2, 3, 1, 1);

        m_labAng = new QLabel(groupBox);
        m_labAng->setObjectName(QString::fromUtf8("m_labAng"));

        gridLayout->addWidget(m_labAng, 3, 1, 1, 1);

        m_txtAng = new QSettingLineEdit(groupBox);
        m_txtAng->setObjectName(QString::fromUtf8("m_txtAng"));
        sizePolicy.setHeightForWidth(m_txtAng->sizePolicy().hasHeightForWidth());
        m_txtAng->setSizePolicy(sizePolicy);
        m_txtAng->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(m_txtAng, 3, 3, 1, 1);

        m_labHz = new QLabel(groupBox);
        m_labHz->setObjectName(QString::fromUtf8("m_labHz"));

        gridLayout->addWidget(m_labHz, 4, 1, 1, 1);

        m_txtHz = new QSettingLineEdit(groupBox);
        m_txtHz->setObjectName(QString::fromUtf8("m_txtHz"));
        sizePolicy.setHeightForWidth(m_txtHz->sizePolicy().hasHeightForWidth());
        m_txtHz->setSizePolicy(sizePolicy);
        m_txtHz->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(m_txtHz, 4, 3, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        frame = new QFrame(QCurrInverseCommonParasDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        m_cmbValue = new QComboBox(frame);
        m_cmbValue->setObjectName(QString::fromUtf8("m_cmbValue"));
        sizePolicy.setHeightForWidth(m_cmbValue->sizePolicy().hasHeightForWidth());
        m_cmbValue->setSizePolicy(sizePolicy);
        m_cmbValue->setMinimumSize(QSize(118, 0));

        gridLayout_2->addWidget(m_cmbValue, 0, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 4, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 1, 1, 1);

        m_txtIn = new QSettingLineEdit(frame);
        m_txtIn->setObjectName(QString::fromUtf8("m_txtIn"));
        sizePolicy.setHeightForWidth(m_txtIn->sizePolicy().hasHeightForWidth());
        m_txtIn->setSizePolicy(sizePolicy);
        m_txtIn->setMinimumSize(QSize(118, 0));

        gridLayout_2->addWidget(m_txtIn, 1, 3, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 1, 1, 1);

        m_cmbCTPos = new QComboBox(frame);
        m_cmbCTPos->setObjectName(QString::fromUtf8("m_cmbCTPos"));
        sizePolicy.setHeightForWidth(m_cmbCTPos->sizePolicy().hasHeightForWidth());
        m_cmbCTPos->setSizePolicy(sizePolicy);
        m_cmbCTPos->setMinimumSize(QSize(118, 0));

        gridLayout_2->addWidget(m_cmbCTPos, 2, 3, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 1, 1, 1);

        m_txtIp = new QSettingLineEdit(frame);
        m_txtIp->setObjectName(QString::fromUtf8("m_txtIp"));
        sizePolicy.setHeightForWidth(m_txtIp->sizePolicy().hasHeightForWidth());
        m_txtIp->setSizePolicy(sizePolicy);
        m_txtIp->setMinimumSize(QSize(118, 0));

        gridLayout_2->addWidget(m_txtIp, 3, 3, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 1, 1, 1);

        m_txtFaultTime = new QSettingLineEdit(frame);
        m_txtFaultTime->setObjectName(QString::fromUtf8("m_txtFaultTime"));
        sizePolicy.setHeightForWidth(m_txtFaultTime->sizePolicy().hasHeightForWidth());
        m_txtFaultTime->setSizePolicy(sizePolicy);
        m_txtFaultTime->setMinimumSize(QSize(118, 0));

        gridLayout_2->addWidget(m_txtFaultTime, 4, 3, 1, 1);


        gridLayout_3->addWidget(frame, 1, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        m_btnOK = new QPushButton(QCurrInverseCommonParasDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);

        m_btnCancel = new QPushButton(QCurrInverseCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);


        gridLayout_3->addLayout(horizontalLayout, 3, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        retranslateUi(QCurrInverseCommonParasDlg);

        QMetaObject::connectSlotsByName(QCurrInverseCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QCurrInverseCommonParasDlg)
    {
        QCurrInverseCommonParasDlg->setWindowTitle(QApplication::translate("QCurrInverseCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QCurrInverseCommonParasDlg", "\346\225\205\351\232\234\345\211\215\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        m_labPreFaultTime->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultVolt->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\346\225\205\351\232\234\345\211\215\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFaultCurr->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\346\225\205\351\232\234\345\211\215\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labAng->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\347\233\270\344\275\215\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labHz->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\345\237\272\345\207\206\345\200\274:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\351\242\235\345\256\232\347\224\265\346\265\201(In):", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QCurrInverseCommonParasDlg", "CT\346\255\243\346\236\201\346\200\247:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\345\220\257\345\212\250\347\224\265\346\265\201(Ip):", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\346\225\205\351\232\234\346\227\266\351\227\264\350\243\225\345\272\246(s):", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QCurrInverseCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCurrInverseCommonParasDlg: public Ui_QCurrInverseCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CURRINVERCOMMONPARASDLG_H
