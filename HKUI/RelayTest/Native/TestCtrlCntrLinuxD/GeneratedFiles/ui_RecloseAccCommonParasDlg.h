/********************************************************************************
** Form generated from reading UI file 'RecloseAccCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECLOSEACCCOMMONPARASDLG_H
#define UI_RECLOSEACCCOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../UI/Controls/SettingCtrls/QSettingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QRecloseAccCommonParasDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QLabel *m_labILoadPh;
    QLineEdit *m_editILoad;
    CExBaseListComboBox *m_cbbFaultTrigMode;
    QLabel *m_labILoad;
    QLineEdit *m_editFaultTime;
    QLabel *m_labPreFaultTime;
    QLineEdit *m_editPreFaultTime;
    QLineEdit *m_editILoadPh;
    QLabel *m_labFaultTime;
    QLabel *m_labBrkCloseTime;
    QLabel *m_labFaultTrigMode;
    QLabel *m_labSimulateBreakerDelay;
    QLabel *m_labBrkBreakTime;
    QLabel *m_labPTPos;
    QLabel *m_labCTPos;
    QLineEdit *m_editBrkBreakTime;
    CExBaseListComboBox *m_cbbPTPos;
    CExBaseListComboBox *m_cbbSimulateBreakerDelay;
    QLineEdit *m_editBrkCloseTime;
    QSettingLineEdit *m_editActionTime;
    CExBaseListComboBox *m_cbbCTPos;
    QLabel *m_labActionTime;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *QRecloseAccCommonParasDlg)
    {
        if (QRecloseAccCommonParasDlg->objectName().isEmpty())
            QRecloseAccCommonParasDlg->setObjectName(QString::fromUtf8("QRecloseAccCommonParasDlg"));
        QRecloseAccCommonParasDlg->resize(328, 359);
        horizontalLayout = new QHBoxLayout(QRecloseAccCommonParasDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_labILoadPh = new QLabel(QRecloseAccCommonParasDlg);
        m_labILoadPh->setObjectName(QString::fromUtf8("m_labILoadPh"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labILoadPh->sizePolicy().hasHeightForWidth());
        m_labILoadPh->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labILoadPh, 7, 1, 1, 1);

        m_editILoad = new QLineEdit(QRecloseAccCommonParasDlg);
        m_editILoad->setObjectName(QString::fromUtf8("m_editILoad"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_editILoad->sizePolicy().hasHeightForWidth());
        m_editILoad->setSizePolicy(sizePolicy1);
        m_editILoad->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_editILoad, 6, 3, 1, 1);

        m_cbbFaultTrigMode = new CExBaseListComboBox(QRecloseAccCommonParasDlg);
        m_cbbFaultTrigMode->setObjectName(QString::fromUtf8("m_cbbFaultTrigMode"));
        sizePolicy1.setHeightForWidth(m_cbbFaultTrigMode->sizePolicy().hasHeightForWidth());
        m_cbbFaultTrigMode->setSizePolicy(sizePolicy1);
        m_cbbFaultTrigMode->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_cbbFaultTrigMode, 3, 3, 1, 1);

        m_labILoad = new QLabel(QRecloseAccCommonParasDlg);
        m_labILoad->setObjectName(QString::fromUtf8("m_labILoad"));
        sizePolicy.setHeightForWidth(m_labILoad->sizePolicy().hasHeightForWidth());
        m_labILoad->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labILoad, 6, 1, 1, 1);

        m_editFaultTime = new QLineEdit(QRecloseAccCommonParasDlg);
        m_editFaultTime->setObjectName(QString::fromUtf8("m_editFaultTime"));
        sizePolicy1.setHeightForWidth(m_editFaultTime->sizePolicy().hasHeightForWidth());
        m_editFaultTime->setSizePolicy(sizePolicy1);
        m_editFaultTime->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_editFaultTime, 1, 3, 1, 1);

        m_labPreFaultTime = new QLabel(QRecloseAccCommonParasDlg);
        m_labPreFaultTime->setObjectName(QString::fromUtf8("m_labPreFaultTime"));
        sizePolicy.setHeightForWidth(m_labPreFaultTime->sizePolicy().hasHeightForWidth());
        m_labPreFaultTime->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labPreFaultTime, 0, 1, 1, 1);

        m_editPreFaultTime = new QLineEdit(QRecloseAccCommonParasDlg);
        m_editPreFaultTime->setObjectName(QString::fromUtf8("m_editPreFaultTime"));
        sizePolicy1.setHeightForWidth(m_editPreFaultTime->sizePolicy().hasHeightForWidth());
        m_editPreFaultTime->setSizePolicy(sizePolicy1);
        m_editPreFaultTime->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_editPreFaultTime, 0, 3, 1, 1);

        m_editILoadPh = new QLineEdit(QRecloseAccCommonParasDlg);
        m_editILoadPh->setObjectName(QString::fromUtf8("m_editILoadPh"));
        sizePolicy1.setHeightForWidth(m_editILoadPh->sizePolicy().hasHeightForWidth());
        m_editILoadPh->setSizePolicy(sizePolicy1);
        m_editILoadPh->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_editILoadPh, 7, 3, 1, 1);

        m_labFaultTime = new QLabel(QRecloseAccCommonParasDlg);
        m_labFaultTime->setObjectName(QString::fromUtf8("m_labFaultTime"));
        sizePolicy.setHeightForWidth(m_labFaultTime->sizePolicy().hasHeightForWidth());
        m_labFaultTime->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labFaultTime, 1, 1, 1, 1);

        m_labBrkCloseTime = new QLabel(QRecloseAccCommonParasDlg);
        m_labBrkCloseTime->setObjectName(QString::fromUtf8("m_labBrkCloseTime"));
        sizePolicy.setHeightForWidth(m_labBrkCloseTime->sizePolicy().hasHeightForWidth());
        m_labBrkCloseTime->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labBrkCloseTime, 11, 1, 1, 1);

        m_labFaultTrigMode = new QLabel(QRecloseAccCommonParasDlg);
        m_labFaultTrigMode->setObjectName(QString::fromUtf8("m_labFaultTrigMode"));
        sizePolicy.setHeightForWidth(m_labFaultTrigMode->sizePolicy().hasHeightForWidth());
        m_labFaultTrigMode->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labFaultTrigMode, 3, 1, 1, 1);

        m_labSimulateBreakerDelay = new QLabel(QRecloseAccCommonParasDlg);
        m_labSimulateBreakerDelay->setObjectName(QString::fromUtf8("m_labSimulateBreakerDelay"));
        sizePolicy.setHeightForWidth(m_labSimulateBreakerDelay->sizePolicy().hasHeightForWidth());
        m_labSimulateBreakerDelay->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labSimulateBreakerDelay, 9, 1, 1, 1);

        m_labBrkBreakTime = new QLabel(QRecloseAccCommonParasDlg);
        m_labBrkBreakTime->setObjectName(QString::fromUtf8("m_labBrkBreakTime"));
        sizePolicy.setHeightForWidth(m_labBrkBreakTime->sizePolicy().hasHeightForWidth());
        m_labBrkBreakTime->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labBrkBreakTime, 10, 1, 1, 1);

        m_labPTPos = new QLabel(QRecloseAccCommonParasDlg);
        m_labPTPos->setObjectName(QString::fromUtf8("m_labPTPos"));
        sizePolicy.setHeightForWidth(m_labPTPos->sizePolicy().hasHeightForWidth());
        m_labPTPos->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labPTPos, 4, 1, 1, 1);

        m_labCTPos = new QLabel(QRecloseAccCommonParasDlg);
        m_labCTPos->setObjectName(QString::fromUtf8("m_labCTPos"));
        sizePolicy.setHeightForWidth(m_labCTPos->sizePolicy().hasHeightForWidth());
        m_labCTPos->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_labCTPos, 5, 1, 1, 1);

        m_editBrkBreakTime = new QLineEdit(QRecloseAccCommonParasDlg);
        m_editBrkBreakTime->setObjectName(QString::fromUtf8("m_editBrkBreakTime"));
        sizePolicy1.setHeightForWidth(m_editBrkBreakTime->sizePolicy().hasHeightForWidth());
        m_editBrkBreakTime->setSizePolicy(sizePolicy1);
        m_editBrkBreakTime->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_editBrkBreakTime, 10, 3, 1, 1);

        m_cbbPTPos = new CExBaseListComboBox(QRecloseAccCommonParasDlg);
        m_cbbPTPos->setObjectName(QString::fromUtf8("m_cbbPTPos"));
        sizePolicy1.setHeightForWidth(m_cbbPTPos->sizePolicy().hasHeightForWidth());
        m_cbbPTPos->setSizePolicy(sizePolicy1);
        m_cbbPTPos->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_cbbPTPos, 4, 3, 1, 1);

        m_cbbSimulateBreakerDelay = new CExBaseListComboBox(QRecloseAccCommonParasDlg);
        m_cbbSimulateBreakerDelay->setObjectName(QString::fromUtf8("m_cbbSimulateBreakerDelay"));
        sizePolicy1.setHeightForWidth(m_cbbSimulateBreakerDelay->sizePolicy().hasHeightForWidth());
        m_cbbSimulateBreakerDelay->setSizePolicy(sizePolicy1);
        m_cbbSimulateBreakerDelay->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_cbbSimulateBreakerDelay, 9, 3, 1, 1);

        m_editBrkCloseTime = new QLineEdit(QRecloseAccCommonParasDlg);
        m_editBrkCloseTime->setObjectName(QString::fromUtf8("m_editBrkCloseTime"));
        sizePolicy1.setHeightForWidth(m_editBrkCloseTime->sizePolicy().hasHeightForWidth());
        m_editBrkCloseTime->setSizePolicy(sizePolicy1);
        m_editBrkCloseTime->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_editBrkCloseTime, 11, 3, 1, 1);

        m_editActionTime = new QSettingLineEdit(QRecloseAccCommonParasDlg);
        m_editActionTime->setObjectName(QString::fromUtf8("m_editActionTime"));
        sizePolicy1.setHeightForWidth(m_editActionTime->sizePolicy().hasHeightForWidth());
        m_editActionTime->setSizePolicy(sizePolicy1);
        m_editActionTime->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_editActionTime, 2, 3, 1, 1);

        m_cbbCTPos = new CExBaseListComboBox(QRecloseAccCommonParasDlg);
        m_cbbCTPos->setObjectName(QString::fromUtf8("m_cbbCTPos"));
        sizePolicy1.setHeightForWidth(m_cbbCTPos->sizePolicy().hasHeightForWidth());
        m_cbbCTPos->setSizePolicy(sizePolicy1);
        m_cbbCTPos->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(m_cbbCTPos, 5, 3, 1, 1);

        m_labActionTime = new QLabel(QRecloseAccCommonParasDlg);
        m_labActionTime->setObjectName(QString::fromUtf8("m_labActionTime"));

        gridLayout_3->addWidget(m_labActionTime, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 4, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        m_btnOk = new QPushButton(QRecloseAccCommonParasDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        sizePolicy1.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(m_btnOk);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        m_btnCancel = new QPushButton(QRecloseAccCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy1.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(m_btnCancel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QRecloseAccCommonParasDlg);

        QMetaObject::connectSlotsByName(QRecloseAccCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QRecloseAccCommonParasDlg)
    {
        QRecloseAccCommonParasDlg->setWindowTitle(QApplication::translate("QRecloseAccCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labILoadPh->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\350\264\237\350\215\267\345\212\237\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labILoad->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\350\264\237\350\215\267\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labPreFaultTime->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultTime->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\346\225\205\351\232\234\346\227\266\351\227\264\350\243\225\345\272\246(s):", 0, QApplication::UnicodeUTF8));
        m_labBrkCloseTime->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\345\220\210\351\227\270\346\227\266\351\227\264(ms):", 0, QApplication::UnicodeUTF8));
        m_labFaultTrigMode->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\346\225\205\351\232\234\350\247\246\345\217\221\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labSimulateBreakerDelay->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\346\226\255\350\267\257\345\231\250\346\250\241\346\213\237:", 0, QApplication::UnicodeUTF8));
        m_labBrkBreakTime->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\345\210\206\351\227\270\346\227\266\351\227\264(ms):", 0, QApplication::UnicodeUTF8));
        m_labPTPos->setText(QApplication::translate("QRecloseAccCommonParasDlg", "TV\345\256\211\350\243\205\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        m_labCTPos->setText(QApplication::translate("QRecloseAccCommonParasDlg", "TA\346\255\243\346\236\201\346\200\247:", 0, QApplication::UnicodeUTF8));
        m_labActionTime->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\346\234\200\345\260\217\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QRecloseAccCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QRecloseAccCommonParasDlg: public Ui_QRecloseAccCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECLOSEACCCOMMONPARASDLG_H
