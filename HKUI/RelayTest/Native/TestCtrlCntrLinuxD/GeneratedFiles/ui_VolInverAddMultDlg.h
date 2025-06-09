/********************************************************************************
** Form generated from reading UI file 'VolInverAddMultDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLINVERADDMULTDLG_H
#define UI_VOLINVERADDMULTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "../../Module/UI/Controls/SttCheckbox.h"
#include "../../Module/UI/Controls/SttGroupBox.h"
#include "../../Module/UI/Module/ScrollCtrl/ScrollComboBox.h"
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QVolInverAddMultDlg
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_FaultTypeChoose;
    QGridLayout *gridLayout_4;
    QSttCheckBox *m_pAN_CheckBox;
    QSttCheckBox *m_pBN_CheckBox;
    QSttCheckBox *m_pCN_CheckBox;
    QSttCheckBox *m_pCA_CheckBox;
    QSttCheckBox *m_pAB_CheckBox;
    QSttCheckBox *m_p3U0_CheckBox;
    QSttCheckBox *m_pBC_CheckBox;
    QSttCheckBox *m_pU2_CheckBox;
    QSttCheckBox *m_pABC_CheckBox;
    QSttGroupBox *groupBox_AddTestPoint;
    QGridLayout *gridLayout_3;
    QLabel *m_pVChangeStartLabel;
    QSettingLineEdit *m_pVChangeStartEdit;
    QLabel *m_pVChangeEndLabel;
    QSettingLineEdit *m_pVChangeEndEdit;
    QLabel *m_pVChangeStepLabel;
    QSettingLineEdit *m_pVChangeStepEdit;
    QLabel *m_pDLCurrentLabel;
    QSettingLineEdit *m_pDLCurrentEdit;
    QSettingLineEdit *m_pFPhaseDiffEdit;
    QLabel *m_pFreLabel;
    QLabel *m_pFPhaseDiffLabel;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_pOK_PushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pCancel_PushButton;
    QSpacerItem *horizontalSpacer_3;
    QSettingLineEdit *m_pFreEdit;
    QSttGroupBox *gridGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *m_pErrorTypeLabel;
    QScrollComboBox *m_pCmb_ErrorType;
    QLabel *m_pRelativeLabel;
    QSettingLineEdit *m_pRelativeEdit;
    QLabel *m_pAbsAddLabel;
    QSettingLineEdit *m_pAbsAddEdit;
    QLabel *m_pAbsDownLabel;
    QSettingLineEdit *m_pAbsDownEdit;

    void setupUi(QDialog *QVolInverAddMultDlg)
    {
        if (QVolInverAddMultDlg->objectName().isEmpty())
            QVolInverAddMultDlg->setObjectName(QString::fromUtf8("QVolInverAddMultDlg"));
        QVolInverAddMultDlg->resize(533, 237);
        gridLayout = new QGridLayout(QVolInverAddMultDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_FaultTypeChoose = new QGroupBox(QVolInverAddMultDlg);
        groupBox_FaultTypeChoose->setObjectName(QString::fromUtf8("groupBox_FaultTypeChoose"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_FaultTypeChoose->sizePolicy().hasHeightForWidth());
        groupBox_FaultTypeChoose->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(groupBox_FaultTypeChoose);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_pAN_CheckBox = new QSttCheckBox(groupBox_FaultTypeChoose);
        m_pAN_CheckBox->setObjectName(QString::fromUtf8("m_pAN_CheckBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pAN_CheckBox->sizePolicy().hasHeightForWidth());
        m_pAN_CheckBox->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pAN_CheckBox, 0, 0, 1, 1);

        m_pBN_CheckBox = new QSttCheckBox(groupBox_FaultTypeChoose);
        m_pBN_CheckBox->setObjectName(QString::fromUtf8("m_pBN_CheckBox"));
        sizePolicy1.setHeightForWidth(m_pBN_CheckBox->sizePolicy().hasHeightForWidth());
        m_pBN_CheckBox->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pBN_CheckBox, 0, 1, 1, 1);

        m_pCN_CheckBox = new QSttCheckBox(groupBox_FaultTypeChoose);
        m_pCN_CheckBox->setObjectName(QString::fromUtf8("m_pCN_CheckBox"));
        sizePolicy1.setHeightForWidth(m_pCN_CheckBox->sizePolicy().hasHeightForWidth());
        m_pCN_CheckBox->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pCN_CheckBox, 0, 3, 1, 1);

        m_pCA_CheckBox = new QSttCheckBox(groupBox_FaultTypeChoose);
        m_pCA_CheckBox->setObjectName(QString::fromUtf8("m_pCA_CheckBox"));
        sizePolicy1.setHeightForWidth(m_pCA_CheckBox->sizePolicy().hasHeightForWidth());
        m_pCA_CheckBox->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pCA_CheckBox, 1, 3, 1, 1);

        m_pAB_CheckBox = new QSttCheckBox(groupBox_FaultTypeChoose);
        m_pAB_CheckBox->setObjectName(QString::fromUtf8("m_pAB_CheckBox"));
        sizePolicy1.setHeightForWidth(m_pAB_CheckBox->sizePolicy().hasHeightForWidth());
        m_pAB_CheckBox->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pAB_CheckBox, 1, 0, 1, 1);

        m_p3U0_CheckBox = new QSttCheckBox(groupBox_FaultTypeChoose);
        m_p3U0_CheckBox->setObjectName(QString::fromUtf8("m_p3U0_CheckBox"));
        sizePolicy1.setHeightForWidth(m_p3U0_CheckBox->sizePolicy().hasHeightForWidth());
        m_p3U0_CheckBox->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_p3U0_CheckBox, 2, 0, 1, 1);

        m_pBC_CheckBox = new QSttCheckBox(groupBox_FaultTypeChoose);
        m_pBC_CheckBox->setObjectName(QString::fromUtf8("m_pBC_CheckBox"));
        sizePolicy1.setHeightForWidth(m_pBC_CheckBox->sizePolicy().hasHeightForWidth());
        m_pBC_CheckBox->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pBC_CheckBox, 1, 1, 1, 2);

        m_pU2_CheckBox = new QSttCheckBox(groupBox_FaultTypeChoose);
        m_pU2_CheckBox->setObjectName(QString::fromUtf8("m_pU2_CheckBox"));
        sizePolicy1.setHeightForWidth(m_pU2_CheckBox->sizePolicy().hasHeightForWidth());
        m_pU2_CheckBox->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pU2_CheckBox, 2, 1, 1, 1);

        m_pABC_CheckBox = new QSttCheckBox(groupBox_FaultTypeChoose);
        m_pABC_CheckBox->setObjectName(QString::fromUtf8("m_pABC_CheckBox"));
        sizePolicy1.setHeightForWidth(m_pABC_CheckBox->sizePolicy().hasHeightForWidth());
        m_pABC_CheckBox->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pABC_CheckBox, 1, 4, 1, 1);

        m_pCN_CheckBox->raise();
        m_pBN_CheckBox->raise();
        m_pAN_CheckBox->raise();
        m_pCA_CheckBox->raise();
        m_pAB_CheckBox->raise();
        m_pU2_CheckBox->raise();
        m_pBN_CheckBox->raise();
        m_pCN_CheckBox->raise();
        m_p3U0_CheckBox->raise();
        m_pAN_CheckBox->raise();
        m_pBC_CheckBox->raise();
        m_pABC_CheckBox->raise();

        gridLayout->addWidget(groupBox_FaultTypeChoose, 0, 3, 1, 1);

        groupBox_AddTestPoint = new QSttGroupBox(QVolInverAddMultDlg);
        groupBox_AddTestPoint->setObjectName(QString::fromUtf8("groupBox_AddTestPoint"));
        sizePolicy.setHeightForWidth(groupBox_AddTestPoint->sizePolicy().hasHeightForWidth());
        groupBox_AddTestPoint->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(groupBox_AddTestPoint);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_pVChangeStartLabel = new QLabel(groupBox_AddTestPoint);
        m_pVChangeStartLabel->setObjectName(QString::fromUtf8("m_pVChangeStartLabel"));

        gridLayout_3->addWidget(m_pVChangeStartLabel, 0, 0, 1, 1);

        m_pVChangeStartEdit = new QSettingLineEdit(groupBox_AddTestPoint);
        m_pVChangeStartEdit->setObjectName(QString::fromUtf8("m_pVChangeStartEdit"));

        gridLayout_3->addWidget(m_pVChangeStartEdit, 0, 1, 1, 1);

        m_pVChangeEndLabel = new QLabel(groupBox_AddTestPoint);
        m_pVChangeEndLabel->setObjectName(QString::fromUtf8("m_pVChangeEndLabel"));

        gridLayout_3->addWidget(m_pVChangeEndLabel, 1, 0, 1, 1);

        m_pVChangeEndEdit = new QSettingLineEdit(groupBox_AddTestPoint);
        m_pVChangeEndEdit->setObjectName(QString::fromUtf8("m_pVChangeEndEdit"));

        gridLayout_3->addWidget(m_pVChangeEndEdit, 1, 1, 1, 1);

        m_pVChangeStepLabel = new QLabel(groupBox_AddTestPoint);
        m_pVChangeStepLabel->setObjectName(QString::fromUtf8("m_pVChangeStepLabel"));

        gridLayout_3->addWidget(m_pVChangeStepLabel, 2, 0, 1, 1);

        m_pVChangeStepEdit = new QSettingLineEdit(groupBox_AddTestPoint);
        m_pVChangeStepEdit->setObjectName(QString::fromUtf8("m_pVChangeStepEdit"));

        gridLayout_3->addWidget(m_pVChangeStepEdit, 2, 1, 1, 1);


        gridLayout->addWidget(groupBox_AddTestPoint, 0, 0, 1, 3);

        m_pDLCurrentLabel = new QLabel(QVolInverAddMultDlg);
        m_pDLCurrentLabel->setObjectName(QString::fromUtf8("m_pDLCurrentLabel"));

        gridLayout->addWidget(m_pDLCurrentLabel, 1, 0, 1, 1);

        m_pDLCurrentEdit = new QSettingLineEdit(QVolInverAddMultDlg);
        m_pDLCurrentEdit->setObjectName(QString::fromUtf8("m_pDLCurrentEdit"));

        gridLayout->addWidget(m_pDLCurrentEdit, 1, 1, 1, 1);

        m_pFPhaseDiffEdit = new QSettingLineEdit(QVolInverAddMultDlg);
        m_pFPhaseDiffEdit->setObjectName(QString::fromUtf8("m_pFPhaseDiffEdit"));

        gridLayout->addWidget(m_pFPhaseDiffEdit, 2, 1, 1, 1);

        m_pFreLabel = new QLabel(QVolInverAddMultDlg);
        m_pFreLabel->setObjectName(QString::fromUtf8("m_pFreLabel"));

        gridLayout->addWidget(m_pFreLabel, 3, 0, 1, 1);

        m_pFPhaseDiffLabel = new QLabel(QVolInverAddMultDlg);
        m_pFPhaseDiffLabel->setObjectName(QString::fromUtf8("m_pFPhaseDiffLabel"));

        gridLayout->addWidget(m_pFPhaseDiffLabel, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        m_pOK_PushButton = new QPushButton(QVolInverAddMultDlg);
        m_pOK_PushButton->setObjectName(QString::fromUtf8("m_pOK_PushButton"));
        m_pOK_PushButton->setAutoDefault(false);

        horizontalLayout_3->addWidget(m_pOK_PushButton);

        horizontalSpacer = new QSpacerItem(128, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        m_pCancel_PushButton = new QPushButton(QVolInverAddMultDlg);
        m_pCancel_PushButton->setObjectName(QString::fromUtf8("m_pCancel_PushButton"));
        m_pCancel_PushButton->setAutoDefault(false);

        horizontalLayout_3->addWidget(m_pCancel_PushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 4);

        m_pFreEdit = new QSettingLineEdit(QVolInverAddMultDlg);
        m_pFreEdit->setObjectName(QString::fromUtf8("m_pFreEdit"));

        gridLayout->addWidget(m_pFreEdit, 3, 1, 1, 1);

        gridGroupBox = new QSttGroupBox(QVolInverAddMultDlg);
        gridGroupBox->setObjectName(QString::fromUtf8("gridGroupBox"));
        gridLayout_2 = new QGridLayout(gridGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pErrorTypeLabel = new QLabel(gridGroupBox);
        m_pErrorTypeLabel->setObjectName(QString::fromUtf8("m_pErrorTypeLabel"));

        gridLayout_2->addWidget(m_pErrorTypeLabel, 0, 0, 1, 1);

        m_pCmb_ErrorType = new QScrollComboBox(gridGroupBox);
        m_pCmb_ErrorType->setObjectName(QString::fromUtf8("m_pCmb_ErrorType"));

        gridLayout_2->addWidget(m_pCmb_ErrorType, 0, 1, 1, 1);

        m_pRelativeLabel = new QLabel(gridGroupBox);
        m_pRelativeLabel->setObjectName(QString::fromUtf8("m_pRelativeLabel"));

        gridLayout_2->addWidget(m_pRelativeLabel, 0, 2, 1, 1);

        m_pRelativeEdit = new QSettingLineEdit(gridGroupBox);
        m_pRelativeEdit->setObjectName(QString::fromUtf8("m_pRelativeEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pRelativeEdit->sizePolicy().hasHeightForWidth());
        m_pRelativeEdit->setSizePolicy(sizePolicy2);
        m_pRelativeEdit->setMinimumSize(QSize(80, 0));

        gridLayout_2->addWidget(m_pRelativeEdit, 0, 3, 1, 1);

        m_pAbsAddLabel = new QLabel(gridGroupBox);
        m_pAbsAddLabel->setObjectName(QString::fromUtf8("m_pAbsAddLabel"));

        gridLayout_2->addWidget(m_pAbsAddLabel, 1, 0, 1, 1);

        m_pAbsAddEdit = new QSettingLineEdit(gridGroupBox);
        m_pAbsAddEdit->setObjectName(QString::fromUtf8("m_pAbsAddEdit"));
        sizePolicy2.setHeightForWidth(m_pAbsAddEdit->sizePolicy().hasHeightForWidth());
        m_pAbsAddEdit->setSizePolicy(sizePolicy2);
        m_pAbsAddEdit->setMinimumSize(QSize(80, 0));

        gridLayout_2->addWidget(m_pAbsAddEdit, 1, 1, 1, 1);

        m_pAbsDownLabel = new QLabel(gridGroupBox);
        m_pAbsDownLabel->setObjectName(QString::fromUtf8("m_pAbsDownLabel"));

        gridLayout_2->addWidget(m_pAbsDownLabel, 1, 2, 1, 1);

        m_pAbsDownEdit = new QSettingLineEdit(gridGroupBox);
        m_pAbsDownEdit->setObjectName(QString::fromUtf8("m_pAbsDownEdit"));
        sizePolicy2.setHeightForWidth(m_pAbsDownEdit->sizePolicy().hasHeightForWidth());
        m_pAbsDownEdit->setSizePolicy(sizePolicy2);
        m_pAbsDownEdit->setMinimumSize(QSize(80, 0));

        gridLayout_2->addWidget(m_pAbsDownEdit, 1, 3, 1, 1);


        gridLayout->addWidget(gridGroupBox, 1, 2, 3, 2);


        retranslateUi(QVolInverAddMultDlg);

        QMetaObject::connectSlotsByName(QVolInverAddMultDlg);
    } // setupUi

    void retranslateUi(QDialog *QVolInverAddMultDlg)
    {
        QVolInverAddMultDlg->setWindowTitle(QApplication::translate("QVolInverAddMultDlg", "\346\267\273\345\212\240\347\263\273\345\210\227", 0, QApplication::UnicodeUTF8));
        groupBox_FaultTypeChoose->setTitle(QApplication::translate("QVolInverAddMultDlg", "\346\225\205\351\232\234\347\261\273\345\210\253\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        m_pAN_CheckBox->setText(QApplication::translate("QVolInverAddMultDlg", "AN", 0, QApplication::UnicodeUTF8));
        m_pBN_CheckBox->setText(QApplication::translate("QVolInverAddMultDlg", "BN", 0, QApplication::UnicodeUTF8));
        m_pCN_CheckBox->setText(QApplication::translate("QVolInverAddMultDlg", "CN", 0, QApplication::UnicodeUTF8));
        m_pCA_CheckBox->setText(QApplication::translate("QVolInverAddMultDlg", "CA\347\237\255\350\267\257", 0, QApplication::UnicodeUTF8));
        m_pAB_CheckBox->setText(QApplication::translate("QVolInverAddMultDlg", "AB\347\237\255\350\267\257", 0, QApplication::UnicodeUTF8));
        m_p3U0_CheckBox->setText(QApplication::translate("QVolInverAddMultDlg", "3U0", 0, QApplication::UnicodeUTF8));
        m_pBC_CheckBox->setText(QApplication::translate("QVolInverAddMultDlg", "BC\347\237\255\350\267\257", 0, QApplication::UnicodeUTF8));
        m_pU2_CheckBox->setText(QApplication::translate("QVolInverAddMultDlg", "U2", 0, QApplication::UnicodeUTF8));
        m_pABC_CheckBox->setText(QApplication::translate("QVolInverAddMultDlg", "\344\270\211\347\233\270\347\237\255\350\267\257", 0, QApplication::UnicodeUTF8));
        groupBox_AddTestPoint->setTitle(QApplication::translate("QVolInverAddMultDlg", "\346\265\213\350\257\225\347\202\271\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        m_pVChangeStartLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\347\224\265\345\216\213\345\217\230\345\214\226\345\247\213\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_pVChangeEndLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\347\224\265\345\216\213\345\217\230\345\214\226\347\273\210\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_pVChangeStepLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\347\224\265\345\216\213\345\217\230\345\214\226\346\255\245\351\225\277(V):", 0, QApplication::UnicodeUTF8));
        m_pDLCurrentLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\347\237\255\350\267\257\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_pFreLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_pFPhaseDiffLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\347\233\270\344\275\215\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_pOK_PushButton->setText(QApplication::translate("QVolInverAddMultDlg", "\347\241\256  \350\256\244", 0, QApplication::UnicodeUTF8));
        m_pCancel_PushButton->setText(QApplication::translate("QVolInverAddMultDlg", "\345\217\226  \346\266\210", 0, QApplication::UnicodeUTF8));
        gridGroupBox->setTitle(QApplication::translate("QVolInverAddMultDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_pErrorTypeLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\350\257\257\345\267\256\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_pRelativeLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_pAbsAddLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_pAbsDownLabel->setText(QApplication::translate("QVolInverAddMultDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QVolInverAddMultDlg: public Ui_QVolInverAddMultDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLINVERADDMULTDLG_H
