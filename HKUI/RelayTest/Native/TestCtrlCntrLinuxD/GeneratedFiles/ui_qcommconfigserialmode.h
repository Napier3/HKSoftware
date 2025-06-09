/********************************************************************************
** Form generated from reading UI file 'qcommconfigserialmode.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOMMCONFIGSERIALMODE_H
#define UI_QCOMMCONFIGSERIALMODE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_QCommConfigSerialMode
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *m_lab_SerialNumber;
    QLabel *m_lab_StopBit_2;
    QComboBox *m_cmbParity;
    QComboBox *m_cmbPortNum;
    QComboBox *m_cmbStopBits;
    QComboBox *m_cmbByteSize;
    QLabel *m_lab_BaudRate;
    QComboBox *m_cmbBaudRate;
    QLabel *m_lab_ParityBit;
    QLabel *m_lab_DataBit;

    void setupUi(QDialog *QCommConfigSerialMode)
    {
        if (QCommConfigSerialMode->objectName().isEmpty())
            QCommConfigSerialMode->setObjectName(QString::fromUtf8("QCommConfigSerialMode"));
        QCommConfigSerialMode->resize(283, 263);
        gridLayout = new QGridLayout(QCommConfigSerialMode);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_lab_SerialNumber = new QLabel(QCommConfigSerialMode);
        m_lab_SerialNumber->setObjectName(QString::fromUtf8("m_lab_SerialNumber"));

        gridLayout_2->addWidget(m_lab_SerialNumber, 0, 0, 1, 1);

        m_lab_StopBit_2 = new QLabel(QCommConfigSerialMode);
        m_lab_StopBit_2->setObjectName(QString::fromUtf8("m_lab_StopBit_2"));

        gridLayout_2->addWidget(m_lab_StopBit_2, 1, 0, 1, 1);

        m_cmbParity = new QComboBox(QCommConfigSerialMode);
        m_cmbParity->setObjectName(QString::fromUtf8("m_cmbParity"));

        gridLayout_2->addWidget(m_cmbParity, 3, 1, 1, 1);

        m_cmbPortNum = new QComboBox(QCommConfigSerialMode);
        m_cmbPortNum->setObjectName(QString::fromUtf8("m_cmbPortNum"));

        gridLayout_2->addWidget(m_cmbPortNum, 0, 1, 1, 1);

        m_cmbStopBits = new QComboBox(QCommConfigSerialMode);
        m_cmbStopBits->setObjectName(QString::fromUtf8("m_cmbStopBits"));

        gridLayout_2->addWidget(m_cmbStopBits, 1, 1, 1, 1);

        m_cmbByteSize = new QComboBox(QCommConfigSerialMode);
        m_cmbByteSize->setObjectName(QString::fromUtf8("m_cmbByteSize"));

        gridLayout_2->addWidget(m_cmbByteSize, 4, 1, 1, 1);

        m_lab_BaudRate = new QLabel(QCommConfigSerialMode);
        m_lab_BaudRate->setObjectName(QString::fromUtf8("m_lab_BaudRate"));

        gridLayout_2->addWidget(m_lab_BaudRate, 2, 0, 1, 1);

        m_cmbBaudRate = new QComboBox(QCommConfigSerialMode);
        m_cmbBaudRate->setObjectName(QString::fromUtf8("m_cmbBaudRate"));

        gridLayout_2->addWidget(m_cmbBaudRate, 2, 1, 1, 1);

        m_lab_ParityBit = new QLabel(QCommConfigSerialMode);
        m_lab_ParityBit->setObjectName(QString::fromUtf8("m_lab_ParityBit"));

        gridLayout_2->addWidget(m_lab_ParityBit, 3, 0, 1, 1);

        m_lab_DataBit = new QLabel(QCommConfigSerialMode);
        m_lab_DataBit->setObjectName(QString::fromUtf8("m_lab_DataBit"));

        gridLayout_2->addWidget(m_lab_DataBit, 4, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(QCommConfigSerialMode);

        QMetaObject::connectSlotsByName(QCommConfigSerialMode);
    } // setupUi

    void retranslateUi(QDialog *QCommConfigSerialMode)
    {
        QCommConfigSerialMode->setWindowTitle(QApplication::translate("QCommConfigSerialMode", "Dialog", 0, QApplication::UnicodeUTF8));
        m_lab_SerialNumber->setText(QApplication::translate("QCommConfigSerialMode", "\344\270\262\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
        m_lab_StopBit_2->setText(QApplication::translate("QCommConfigSerialMode", "\345\201\234\346\255\242\344\275\215", 0, QApplication::UnicodeUTF8));
        m_cmbParity->clear();
        m_cmbParity->insertItems(0, QStringList()
         << QApplication::translate("QCommConfigSerialMode", "\346\227\240\346\240\241\351\252\214", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "\345\245\207\346\240\241\351\252\214", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "\345\201\266\346\240\241\351\252\214", 0, QApplication::UnicodeUTF8)
        );
        m_cmbPortNum->clear();
        m_cmbPortNum->insertItems(0, QStringList()
         << QApplication::translate("QCommConfigSerialMode", "COM1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "COM12", 0, QApplication::UnicodeUTF8)
        );
        m_cmbStopBits->clear();
        m_cmbStopBits->insertItems(0, QStringList()
         << QApplication::translate("QCommConfigSerialMode", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "1.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "2", 0, QApplication::UnicodeUTF8)
        );
        m_cmbByteSize->clear();
        m_cmbByteSize->insertItems(0, QStringList()
         << QApplication::translate("QCommConfigSerialMode", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "8", 0, QApplication::UnicodeUTF8)
        );
        m_lab_BaudRate->setText(QApplication::translate("QCommConfigSerialMode", "\346\263\242\347\211\271\347\216\207", 0, QApplication::UnicodeUTF8));
        m_cmbBaudRate->clear();
        m_cmbBaudRate->insertItems(0, QStringList()
         << QApplication::translate("QCommConfigSerialMode", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCommConfigSerialMode", "19200", 0, QApplication::UnicodeUTF8)
        );
        m_lab_ParityBit->setText(QApplication::translate("QCommConfigSerialMode", "\346\240\241\351\252\214\344\275\215", 0, QApplication::UnicodeUTF8));
        m_lab_DataBit->setText(QApplication::translate("QCommConfigSerialMode", "\346\225\260\346\215\256\344\275\215", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCommConfigSerialMode: public Ui_QCommConfigSerialMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOMMCONFIGSERIALMODE_H
