/********************************************************************************
** Form generated from reading UI file 'qcommconfigcmsdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOMMCONFIGCMSDLG_H
#define UI_QCOMMCONFIGCMSDLG_H

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

class Ui_QCOmmConfigCmsDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QCheckBox *isClientIP;
    QLineEdit *m_editLocalIP;
    QLineEdit *m_editEncryptPsw;
    QLineEdit *m_editEncryptKey;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *m_editClientIP;
    QLabel *label_7;

    void setupUi(QDialog *QCOmmConfigCmsDlg)
    {
        if (QCOmmConfigCmsDlg->objectName().isEmpty())
            QCOmmConfigCmsDlg->setObjectName(QString::fromUtf8("QCOmmConfigCmsDlg"));
        QCOmmConfigCmsDlg->resize(408, 249);
        verticalLayout_2 = new QVBoxLayout(QCOmmConfigCmsDlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(QCOmmConfigCmsDlg);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        isClientIP = new QCheckBox(QCOmmConfigCmsDlg);
        isClientIP->setObjectName(QString::fromUtf8("isClientIP"));

        gridLayout->addWidget(isClientIP, 4, 1, 1, 1);

        m_editLocalIP = new QLineEdit(QCOmmConfigCmsDlg);
        m_editLocalIP->setObjectName(QString::fromUtf8("m_editLocalIP"));

        gridLayout->addWidget(m_editLocalIP, 0, 1, 1, 1);

        m_editEncryptPsw = new QLineEdit(QCOmmConfigCmsDlg);
        m_editEncryptPsw->setObjectName(QString::fromUtf8("m_editEncryptPsw"));

        gridLayout->addWidget(m_editEncryptPsw, 2, 1, 1, 1);

        m_editEncryptKey = new QLineEdit(QCOmmConfigCmsDlg);
        m_editEncryptKey->setObjectName(QString::fromUtf8("m_editEncryptKey"));

        gridLayout->addWidget(m_editEncryptKey, 1, 1, 1, 1);

        label_4 = new QLabel(QCOmmConfigCmsDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(QCOmmConfigCmsDlg);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_editClientIP = new QLineEdit(QCOmmConfigCmsDlg);
        m_editClientIP->setObjectName(QString::fromUtf8("m_editClientIP"));

        gridLayout->addWidget(m_editClientIP, 3, 1, 1, 1);

        label_7 = new QLabel(QCOmmConfigCmsDlg);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        retranslateUi(QCOmmConfigCmsDlg);

        QMetaObject::connectSlotsByName(QCOmmConfigCmsDlg);
    } // setupUi

    void retranslateUi(QDialog *QCOmmConfigCmsDlg)
    {
        QCOmmConfigCmsDlg->setWindowTitle(QApplication::translate("QCOmmConfigCmsDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QCOmmConfigCmsDlg", "\346\234\254\346\234\272IP\345\234\260\345\235\200   ", 0, QApplication::UnicodeUTF8));
        isClientIP->setText(QApplication::translate("QCOmmConfigCmsDlg", "\346\214\207\345\256\232\345\256\242\346\210\267\347\253\257", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QCOmmConfigCmsDlg", "  PSW       ", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QCOmmConfigCmsDlg", "  KEY       ", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QCOmmConfigCmsDlg", "\345\256\242\346\210\267\347\253\257IP\345\234\260\345\235\200 ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCOmmConfigCmsDlg: public Ui_QCOmmConfigCmsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOMMCONFIGCMSDLG_H
