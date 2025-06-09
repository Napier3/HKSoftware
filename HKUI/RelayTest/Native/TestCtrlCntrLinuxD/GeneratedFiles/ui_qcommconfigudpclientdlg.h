/********************************************************************************
** Form generated from reading UI file 'qcommconfigudpclientdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOMMCONFIGUDPCLIENTDLG_H
#define UI_QCOMMCONFIGUDPCLIENTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QCommConfigUdpClientDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLineEdit *m_editRemotePort;
    QLabel *label_5;
    QLineEdit *m_editMulticastIP;
    QLineEdit *m_editLocalPort;
    QLineEdit *m_editLocalIP;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_7;
    QLineEdit *m_editRemoteIP;
    QCheckBox *m_chkIsBroadcast;

    void setupUi(QDialog *QCommConfigUdpClientDlg)
    {
        if (QCommConfigUdpClientDlg->objectName().isEmpty())
            QCommConfigUdpClientDlg->setObjectName(QString::fromUtf8("QCommConfigUdpClientDlg"));
        QCommConfigUdpClientDlg->resize(348, 286);
        verticalLayout = new QVBoxLayout(QCommConfigUdpClientDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(QCommConfigUdpClientDlg);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        m_editRemotePort = new QLineEdit(QCommConfigUdpClientDlg);
        m_editRemotePort->setObjectName(QString::fromUtf8("m_editRemotePort"));

        gridLayout->addWidget(m_editRemotePort, 3, 1, 1, 1);

        label_5 = new QLabel(QCommConfigUdpClientDlg);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        m_editMulticastIP = new QLineEdit(QCommConfigUdpClientDlg);
        m_editMulticastIP->setObjectName(QString::fromUtf8("m_editMulticastIP"));

        gridLayout->addWidget(m_editMulticastIP, 4, 1, 1, 1);

        m_editLocalPort = new QLineEdit(QCommConfigUdpClientDlg);
        m_editLocalPort->setObjectName(QString::fromUtf8("m_editLocalPort"));

        gridLayout->addWidget(m_editLocalPort, 1, 1, 1, 1);

        m_editLocalIP = new QLineEdit(QCommConfigUdpClientDlg);
        m_editLocalIP->setObjectName(QString::fromUtf8("m_editLocalIP"));

        gridLayout->addWidget(m_editLocalIP, 0, 1, 1, 1);

        label_4 = new QLabel(QCommConfigUdpClientDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_8 = new QLabel(QCommConfigUdpClientDlg);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 3, 0, 1, 1);

        label_7 = new QLabel(QCommConfigUdpClientDlg);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        m_editRemoteIP = new QLineEdit(QCommConfigUdpClientDlg);
        m_editRemoteIP->setObjectName(QString::fromUtf8("m_editRemoteIP"));

        gridLayout->addWidget(m_editRemoteIP, 2, 1, 1, 1);

        m_chkIsBroadcast = new QCheckBox(QCommConfigUdpClientDlg);
        m_chkIsBroadcast->setObjectName(QString::fromUtf8("m_chkIsBroadcast"));

        gridLayout->addWidget(m_chkIsBroadcast, 5, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(QCommConfigUdpClientDlg);

        QMetaObject::connectSlotsByName(QCommConfigUdpClientDlg);
    } // setupUi

    void retranslateUi(QDialog *QCommConfigUdpClientDlg)
    {
        QCommConfigUdpClientDlg->setWindowTitle(QApplication::translate("QCommConfigUdpClientDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QCommConfigUdpClientDlg", "\346\234\254\346\234\272IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QCommConfigUdpClientDlg", "\347\273\204\346\222\255IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QCommConfigUdpClientDlg", "\346\234\254\346\234\272\347\253\257\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("QCommConfigUdpClientDlg", "\350\277\234\347\250\213\347\253\257\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QCommConfigUdpClientDlg", "\350\277\234\347\250\213IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        m_chkIsBroadcast->setText(QApplication::translate("QCommConfigUdpClientDlg", "\346\230\257\345\220\246\344\275\277\347\224\250\345\271\277\346\222\255", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCommConfigUdpClientDlg: public Ui_QCommConfigUdpClientDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOMMCONFIGUDPCLIENTDLG_H
