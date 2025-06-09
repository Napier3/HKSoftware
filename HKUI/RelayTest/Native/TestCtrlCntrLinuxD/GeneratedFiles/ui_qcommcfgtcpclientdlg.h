/********************************************************************************
** Form generated from reading UI file 'qcommcfgtcpclientdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOMMCFGTCPCLIENTDLG_H
#define UI_QCOMMCFGTCPCLIENTDLG_H

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

class Ui_QCommCfgTcpClientDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *m_editRemoteIP;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *m_editLocalIP;
    QLineEdit *m_editLocalPort;
    QLabel *label_4;
    QLabel *label_7;
    QLineEdit *m_editRemotePort;

    void setupUi(QDialog *QCommCfgTcpClientDlg)
    {
        if (QCommCfgTcpClientDlg->objectName().isEmpty())
            QCommCfgTcpClientDlg->setObjectName(QString::fromUtf8("QCommCfgTcpClientDlg"));
        QCommCfgTcpClientDlg->resize(416, 241);
        verticalLayout = new QVBoxLayout(QCommCfgTcpClientDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_editRemoteIP = new QLineEdit(QCommCfgTcpClientDlg);
        m_editRemoteIP->setObjectName(QString::fromUtf8("m_editRemoteIP"));

        gridLayout->addWidget(m_editRemoteIP, 2, 1, 1, 1);

        label_5 = new QLabel(QCommCfgTcpClientDlg);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        label_6 = new QLabel(QCommCfgTcpClientDlg);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        m_editLocalIP = new QLineEdit(QCommCfgTcpClientDlg);
        m_editLocalIP->setObjectName(QString::fromUtf8("m_editLocalIP"));

        gridLayout->addWidget(m_editLocalIP, 0, 1, 1, 1);

        m_editLocalPort = new QLineEdit(QCommCfgTcpClientDlg);
        m_editLocalPort->setObjectName(QString::fromUtf8("m_editLocalPort"));

        gridLayout->addWidget(m_editLocalPort, 1, 1, 1, 1);

        label_4 = new QLabel(QCommCfgTcpClientDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_7 = new QLabel(QCommCfgTcpClientDlg);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        m_editRemotePort = new QLineEdit(QCommCfgTcpClientDlg);
        m_editRemotePort->setObjectName(QString::fromUtf8("m_editRemotePort"));

        gridLayout->addWidget(m_editRemotePort, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(QCommCfgTcpClientDlg);

        QMetaObject::connectSlotsByName(QCommCfgTcpClientDlg);
    } // setupUi

    void retranslateUi(QDialog *QCommCfgTcpClientDlg)
    {
        QCommCfgTcpClientDlg->setWindowTitle(QApplication::translate("QCommCfgTcpClientDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QCommCfgTcpClientDlg", "\350\277\234\347\250\213IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QCommCfgTcpClientDlg", "\346\234\254\346\234\272IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QCommCfgTcpClientDlg", "\346\234\254\346\234\272\347\253\257\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QCommCfgTcpClientDlg", "\350\277\234\347\250\213\347\253\257\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCommCfgTcpClientDlg: public Ui_QCommCfgTcpClientDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOMMCFGTCPCLIENTDLG_H
