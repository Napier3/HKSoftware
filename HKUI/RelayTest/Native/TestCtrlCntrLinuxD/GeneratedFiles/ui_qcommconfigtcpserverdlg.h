/********************************************************************************
** Form generated from reading UI file 'qcommconfigtcpserverdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOMMCONFIGTCPSERVERDLG_H
#define UI_QCOMMCONFIGTCPSERVERDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QCommConfigServerDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *m_editLocalIP;
    QLabel *label_6;
    QLabel *label_4;
    QLineEdit *m_editLocalPort;

    void setupUi(QDialog *QCommConfigServerDlg)
    {
        if (QCommConfigServerDlg->objectName().isEmpty())
            QCommConfigServerDlg->setObjectName(QString::fromUtf8("QCommConfigServerDlg"));
        QCommConfigServerDlg->resize(327, 161);
        verticalLayout = new QVBoxLayout(QCommConfigServerDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_editLocalIP = new QLineEdit(QCommConfigServerDlg);
        m_editLocalIP->setObjectName(QString::fromUtf8("m_editLocalIP"));

        gridLayout->addWidget(m_editLocalIP, 0, 1, 1, 1);

        label_6 = new QLabel(QCommConfigServerDlg);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        label_4 = new QLabel(QCommConfigServerDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        m_editLocalPort = new QLineEdit(QCommConfigServerDlg);
        m_editLocalPort->setObjectName(QString::fromUtf8("m_editLocalPort"));

        gridLayout->addWidget(m_editLocalPort, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(QCommConfigServerDlg);

        QMetaObject::connectSlotsByName(QCommConfigServerDlg);
    } // setupUi

    void retranslateUi(QDialog *QCommConfigServerDlg)
    {
        QCommConfigServerDlg->setWindowTitle(QApplication::translate("QCommConfigServerDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QCommConfigServerDlg", "\346\234\254\346\234\272IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QCommConfigServerDlg", "\346\234\254\346\234\272\347\253\257\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCommConfigServerDlg: public Ui_QCommConfigServerDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOMMCONFIGTCPSERVERDLG_H
