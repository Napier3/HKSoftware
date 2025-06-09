/********************************************************************************
** Form generated from reading UI file 'ppcommconfigdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PPCOMMCONFIGDLG_H
#define UI_PPCOMMCONFIGDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PpCommConfigDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *m_vlConfigMain;
    QGroupBox *m_grpCmmModel;
    QGridLayout *gridLayout;
    QRadioButton *m_btnNet;
    QRadioButton *m_btnMms;
    QRadioButton *m_btnSerial;
    QRadioButton *m_btnCms;
    QGroupBox *m_grpNetConfig;
    QGridLayout *gridLayout_2;
    QCheckBox *m_btnTcpServer;
    QCheckBox *m_btnTcpClient;
    QCheckBox *m_btnUdpServer;
    QCheckBox *m_btnUdpClient;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnSave;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *PpCommConfigDlg)
    {
        if (PpCommConfigDlg->objectName().isEmpty())
            PpCommConfigDlg->setObjectName(QString::fromUtf8("PpCommConfigDlg"));
        PpCommConfigDlg->resize(366, 281);
        verticalLayout_2 = new QVBoxLayout(PpCommConfigDlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_vlConfigMain = new QVBoxLayout();
        m_vlConfigMain->setObjectName(QString::fromUtf8("m_vlConfigMain"));
        m_grpCmmModel = new QGroupBox(PpCommConfigDlg);
        m_grpCmmModel->setObjectName(QString::fromUtf8("m_grpCmmModel"));
        gridLayout = new QGridLayout(m_grpCmmModel);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_btnNet = new QRadioButton(m_grpCmmModel);
        m_btnNet->setObjectName(QString::fromUtf8("m_btnNet"));

        gridLayout->addWidget(m_btnNet, 0, 1, 1, 1);

        m_btnMms = new QRadioButton(m_grpCmmModel);
        m_btnMms->setObjectName(QString::fromUtf8("m_btnMms"));

        gridLayout->addWidget(m_btnMms, 0, 2, 1, 1);

        m_btnSerial = new QRadioButton(m_grpCmmModel);
        m_btnSerial->setObjectName(QString::fromUtf8("m_btnSerial"));

        gridLayout->addWidget(m_btnSerial, 0, 0, 1, 1);

        m_btnCms = new QRadioButton(m_grpCmmModel);
        m_btnCms->setObjectName(QString::fromUtf8("m_btnCms"));

        gridLayout->addWidget(m_btnCms, 0, 3, 1, 1);


        m_vlConfigMain->addWidget(m_grpCmmModel);

        m_grpNetConfig = new QGroupBox(PpCommConfigDlg);
        m_grpNetConfig->setObjectName(QString::fromUtf8("m_grpNetConfig"));
        gridLayout_2 = new QGridLayout(m_grpNetConfig);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_btnTcpServer = new QCheckBox(m_grpNetConfig);
        m_btnTcpServer->setObjectName(QString::fromUtf8("m_btnTcpServer"));

        gridLayout_2->addWidget(m_btnTcpServer, 0, 0, 1, 1);

        m_btnTcpClient = new QCheckBox(m_grpNetConfig);
        m_btnTcpClient->setObjectName(QString::fromUtf8("m_btnTcpClient"));

        gridLayout_2->addWidget(m_btnTcpClient, 0, 1, 1, 1);

        m_btnUdpServer = new QCheckBox(m_grpNetConfig);
        m_btnUdpServer->setObjectName(QString::fromUtf8("m_btnUdpServer"));

        gridLayout_2->addWidget(m_btnUdpServer, 0, 2, 1, 1);

        m_btnUdpClient = new QCheckBox(m_grpNetConfig);
        m_btnUdpClient->setObjectName(QString::fromUtf8("m_btnUdpClient"));

        gridLayout_2->addWidget(m_btnUdpClient, 0, 3, 1, 1);


        m_vlConfigMain->addWidget(m_grpNetConfig);


        verticalLayout_2->addLayout(m_vlConfigMain);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        m_btnSave = new QPushButton(PpCommConfigDlg);
        m_btnSave->setObjectName(QString::fromUtf8("m_btnSave"));

        horizontalLayout_3->addWidget(m_btnSave);

        m_btnCancel = new QPushButton(PpCommConfigDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout_3->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(PpCommConfigDlg);

        QMetaObject::connectSlotsByName(PpCommConfigDlg);
    } // setupUi

    void retranslateUi(QDialog *PpCommConfigDlg)
    {
        PpCommConfigDlg->setWindowTitle(QApplication::translate("PpCommConfigDlg", "\351\200\232\344\277\241\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        m_btnNet->setText(QApplication::translate("PpCommConfigDlg", "\347\275\221\345\217\243\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        m_btnMms->setText(QApplication::translate("PpCommConfigDlg", "MMS\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        m_btnSerial->setText(QApplication::translate("PpCommConfigDlg", "\344\270\262\345\217\243\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        m_btnCms->setText(QApplication::translate("PpCommConfigDlg", "CMS\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        m_btnTcpServer->setText(QApplication::translate("PpCommConfigDlg", "TcpServer", 0, QApplication::UnicodeUTF8));
        m_btnTcpClient->setText(QApplication::translate("PpCommConfigDlg", "TcpClient", 0, QApplication::UnicodeUTF8));
        m_btnUdpServer->setText(QApplication::translate("PpCommConfigDlg", "UdpServer", 0, QApplication::UnicodeUTF8));
        m_btnUdpClient->setText(QApplication::translate("PpCommConfigDlg", "UdpClient", 0, QApplication::UnicodeUTF8));
        m_btnSave->setText(QApplication::translate("PpCommConfigDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("PpCommConfigDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PpCommConfigDlg: public Ui_PpCommConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PPCOMMCONFIGDLG_H
