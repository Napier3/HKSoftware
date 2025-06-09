/********************************************************************************
** Form generated from reading UI file 'qcommconfigudpserver.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOMMCONFIGUDPSERVER_H
#define UI_QCOMMCONFIGUDPSERVER_H

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

QT_BEGIN_NAMESPACE

class Ui_QCommConfigUdpServer
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLineEdit *m_editMulticastIP;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *m_editLocalIP;
    QLineEdit *m_editLocalPort;
    QCheckBox *isBroadcast;

    void setupUi(QDialog *QCommConfigUdpServer)
    {
        if (QCommConfigUdpServer->objectName().isEmpty())
            QCommConfigUdpServer->setObjectName(QString::fromUtf8("QCommConfigUdpServer"));
        QCommConfigUdpServer->resize(322, 206);
        gridLayout = new QGridLayout(QCommConfigUdpServer);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(QCommConfigUdpServer);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        m_editMulticastIP = new QLineEdit(QCommConfigUdpServer);
        m_editMulticastIP->setObjectName(QString::fromUtf8("m_editMulticastIP"));

        gridLayout_2->addWidget(m_editMulticastIP, 2, 1, 1, 1);

        label_4 = new QLabel(QCommConfigUdpServer);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        label_6 = new QLabel(QCommConfigUdpServer);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        m_editLocalIP = new QLineEdit(QCommConfigUdpServer);
        m_editLocalIP->setObjectName(QString::fromUtf8("m_editLocalIP"));

        gridLayout_2->addWidget(m_editLocalIP, 0, 1, 1, 1);

        m_editLocalPort = new QLineEdit(QCommConfigUdpServer);
        m_editLocalPort->setObjectName(QString::fromUtf8("m_editLocalPort"));

        gridLayout_2->addWidget(m_editLocalPort, 1, 1, 1, 1);

        isBroadcast = new QCheckBox(QCommConfigUdpServer);
        isBroadcast->setObjectName(QString::fromUtf8("isBroadcast"));

        gridLayout_2->addWidget(isBroadcast, 3, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(QCommConfigUdpServer);

        QMetaObject::connectSlotsByName(QCommConfigUdpServer);
    } // setupUi

    void retranslateUi(QDialog *QCommConfigUdpServer)
    {
        QCommConfigUdpServer->setWindowTitle(QApplication::translate("QCommConfigUdpServer", "Dialog", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QCommConfigUdpServer", "\347\273\204\346\222\255IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QCommConfigUdpServer", "\346\234\254\346\234\272\347\253\257\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QCommConfigUdpServer", "\346\234\254\346\234\272IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        isBroadcast->setText(QApplication::translate("QCommConfigUdpServer", "\346\230\257\345\220\246\344\275\277\347\224\250\345\271\277\346\222\255", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCommConfigUdpServer: public Ui_QCommConfigUdpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOMMCONFIGUDPSERVER_H
