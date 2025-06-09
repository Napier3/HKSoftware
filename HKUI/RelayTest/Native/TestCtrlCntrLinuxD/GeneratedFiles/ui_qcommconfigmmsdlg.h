/********************************************************************************
** Form generated from reading UI file 'qcommconfigmmsdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOMMCONFIGMMSDLG_H
#define UI_QCOMMCONFIGMMSDLG_H

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

class Ui_QCommConfigMmsDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLineEdit *m_editEncryptKey;
    QLabel *label_5;
    QLineEdit *m_editRemoteIP;
    QLabel *label_4;
    QLineEdit *m_editEncryptPsw;

    void setupUi(QDialog *QCommConfigMmsDlg)
    {
        if (QCommConfigMmsDlg->objectName().isEmpty())
            QCommConfigMmsDlg->setObjectName(QString::fromUtf8("QCommConfigMmsDlg"));
        QCommConfigMmsDlg->resize(273, 195);
        verticalLayout = new QVBoxLayout(QCommConfigMmsDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(QCommConfigMmsDlg);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        m_editEncryptKey = new QLineEdit(QCommConfigMmsDlg);
        m_editEncryptKey->setObjectName(QString::fromUtf8("m_editEncryptKey"));

        gridLayout->addWidget(m_editEncryptKey, 1, 1, 1, 1);

        label_5 = new QLabel(QCommConfigMmsDlg);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_editRemoteIP = new QLineEdit(QCommConfigMmsDlg);
        m_editRemoteIP->setObjectName(QString::fromUtf8("m_editRemoteIP"));

        gridLayout->addWidget(m_editRemoteIP, 0, 1, 1, 1);

        label_4 = new QLabel(QCommConfigMmsDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        m_editEncryptPsw = new QLineEdit(QCommConfigMmsDlg);
        m_editEncryptPsw->setObjectName(QString::fromUtf8("m_editEncryptPsw"));

        gridLayout->addWidget(m_editEncryptPsw, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(QCommConfigMmsDlg);

        QMetaObject::connectSlotsByName(QCommConfigMmsDlg);
    } // setupUi

    void retranslateUi(QDialog *QCommConfigMmsDlg)
    {
        QCommConfigMmsDlg->setWindowTitle(QApplication::translate("QCommConfigMmsDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QCommConfigMmsDlg", "IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QCommConfigMmsDlg", "  KEY    ", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QCommConfigMmsDlg", "  PSW    ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCommConfigMmsDlg: public Ui_QCommConfigMmsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOMMCONFIGMMSDLG_H
