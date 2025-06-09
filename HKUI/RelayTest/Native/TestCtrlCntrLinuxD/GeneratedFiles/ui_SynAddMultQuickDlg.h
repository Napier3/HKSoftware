/********************************************************************************
** Form generated from reading UI file 'SynAddMultQuickDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNADDMULTQUICKDLG_H
#define UI_SYNADDMULTQUICKDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "../../Module/UI/Controls/SttLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QSynAddMultQuickDlg
{
public:
    QGridLayout *gridLayout;
    QLabel *m_pUPlusLabel;
    QSttLineEdit *m_pUMinusEdit;
    QLabel *m_pUMinusLabel;
    QLabel *m_pFMinusLabel;
    QLabel *m_pFPlusLabel;
    QGridLayout *gridLayout_2;
    QPushButton *m_pOK_PushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_pCancel_PushButton;
    QSttLineEdit *m_pUPlusEdit;
    QSttLineEdit *m_pFPlusEdit;
    QSttLineEdit *m_pFMinusEdit;

    void setupUi(QDialog *QSynAddMultQuickDlg)
    {
        if (QSynAddMultQuickDlg->objectName().isEmpty())
            QSynAddMultQuickDlg->setObjectName(QString::fromUtf8("QSynAddMultQuickDlg"));
        QSynAddMultQuickDlg->resize(270, 198);
        gridLayout = new QGridLayout(QSynAddMultQuickDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pUPlusLabel = new QLabel(QSynAddMultQuickDlg);
        m_pUPlusLabel->setObjectName(QString::fromUtf8("m_pUPlusLabel"));

        gridLayout->addWidget(m_pUPlusLabel, 0, 0, 1, 1);

        m_pUMinusEdit = new QSttLineEdit(QSynAddMultQuickDlg);
        m_pUMinusEdit->setObjectName(QString::fromUtf8("m_pUMinusEdit"));

        gridLayout->addWidget(m_pUMinusEdit, 1, 1, 1, 1);

        m_pUMinusLabel = new QLabel(QSynAddMultQuickDlg);
        m_pUMinusLabel->setObjectName(QString::fromUtf8("m_pUMinusLabel"));

        gridLayout->addWidget(m_pUMinusLabel, 1, 0, 1, 1);

        m_pFMinusLabel = new QLabel(QSynAddMultQuickDlg);
        m_pFMinusLabel->setObjectName(QString::fromUtf8("m_pFMinusLabel"));

        gridLayout->addWidget(m_pFMinusLabel, 4, 0, 1, 1);

        m_pFPlusLabel = new QLabel(QSynAddMultQuickDlg);
        m_pFPlusLabel->setObjectName(QString::fromUtf8("m_pFPlusLabel"));

        gridLayout->addWidget(m_pFPlusLabel, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pOK_PushButton = new QPushButton(QSynAddMultQuickDlg);
        m_pOK_PushButton->setObjectName(QString::fromUtf8("m_pOK_PushButton"));
        m_pOK_PushButton->setAutoDefault(false);

        gridLayout_2->addWidget(m_pOK_PushButton, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        m_pCancel_PushButton = new QPushButton(QSynAddMultQuickDlg);
        m_pCancel_PushButton->setObjectName(QString::fromUtf8("m_pCancel_PushButton"));
        m_pCancel_PushButton->setAutoDefault(false);

        gridLayout_2->addWidget(m_pCancel_PushButton, 0, 2, 1, 1);


        gridLayout->addLayout(gridLayout_2, 5, 0, 1, 2);

        m_pUPlusEdit = new QSttLineEdit(QSynAddMultQuickDlg);
        m_pUPlusEdit->setObjectName(QString::fromUtf8("m_pUPlusEdit"));

        gridLayout->addWidget(m_pUPlusEdit, 0, 1, 1, 1);

        m_pFPlusEdit = new QSttLineEdit(QSynAddMultQuickDlg);
        m_pFPlusEdit->setObjectName(QString::fromUtf8("m_pFPlusEdit"));

        gridLayout->addWidget(m_pFPlusEdit, 3, 1, 1, 1);

        m_pFMinusEdit = new QSttLineEdit(QSynAddMultQuickDlg);
        m_pFMinusEdit->setObjectName(QString::fromUtf8("m_pFMinusEdit"));

        gridLayout->addWidget(m_pFMinusEdit, 4, 1, 1, 1);


        retranslateUi(QSynAddMultQuickDlg);

        QMetaObject::connectSlotsByName(QSynAddMultQuickDlg);
    } // setupUi

    void retranslateUi(QDialog *QSynAddMultQuickDlg)
    {
        QSynAddMultQuickDlg->setWindowTitle(QApplication::translate("QSynAddMultQuickDlg", "\345\274\200\345\205\263\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_pUPlusLabel->setText(QApplication::translate("QSynAddMultQuickDlg", "\342\226\263U+", 0, QApplication::UnicodeUTF8));
        m_pUMinusLabel->setText(QApplication::translate("QSynAddMultQuickDlg", "\342\226\263U-", 0, QApplication::UnicodeUTF8));
        m_pFMinusLabel->setText(QApplication::translate("QSynAddMultQuickDlg", "\342\226\263f-", 0, QApplication::UnicodeUTF8));
        m_pFPlusLabel->setText(QApplication::translate("QSynAddMultQuickDlg", "\342\226\263f+", 0, QApplication::UnicodeUTF8));
        m_pOK_PushButton->setText(QApplication::translate("QSynAddMultQuickDlg", "\347\241\256  \350\256\244", 0, QApplication::UnicodeUTF8));
        m_pCancel_PushButton->setText(QApplication::translate("QSynAddMultQuickDlg", "\345\217\226  \346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSynAddMultQuickDlg: public Ui_QSynAddMultQuickDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNADDMULTQUICKDLG_H
