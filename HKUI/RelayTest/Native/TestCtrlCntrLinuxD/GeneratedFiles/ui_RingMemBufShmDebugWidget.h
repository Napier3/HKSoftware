/********************************************************************************
** Form generated from reading UI file 'RingMemBufShmDebugWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RINGMEMBUFSHMDEBUGWIDGET_H
#define UI_RINGMEMBUFSHMDEBUGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QRingMemBufShmDebugWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayoutNameID;
    QGridLayout *gridLayout;
    QLabel *m_lblSendLength_2;
    QLabel *m_lblFileName;
    QLineEdit *m_edtFileName;
    QLineEdit *m_edtSendLength;
    QLabel *m_lblSendLength;
    QLineEdit *m_edtSendLengthTotal;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_Btn_WriteDetectPkg;
    QPushButton *m_Btn_WriteRcvPkg;
    QPushButton *m_btnAutoWrite;

    void setupUi(QDialog *QRingMemBufShmDebugWidget)
    {
        if (QRingMemBufShmDebugWidget->objectName().isEmpty())
            QRingMemBufShmDebugWidget->setObjectName(QString::fromUtf8("QRingMemBufShmDebugWidget"));
        QRingMemBufShmDebugWidget->resize(382, 125);
        verticalLayout_2 = new QVBoxLayout(QRingMemBufShmDebugWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayoutNameID = new QGridLayout();
        gridLayoutNameID->setObjectName(QString::fromUtf8("gridLayoutNameID"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_lblSendLength_2 = new QLabel(QRingMemBufShmDebugWidget);
        m_lblSendLength_2->setObjectName(QString::fromUtf8("m_lblSendLength_2"));

        gridLayout->addWidget(m_lblSendLength_2, 0, 0, 1, 1);


        gridLayoutNameID->addLayout(gridLayout, 2, 0, 1, 1);

        m_lblFileName = new QLabel(QRingMemBufShmDebugWidget);
        m_lblFileName->setObjectName(QString::fromUtf8("m_lblFileName"));

        gridLayoutNameID->addWidget(m_lblFileName, 0, 0, 1, 1);

        m_edtFileName = new QLineEdit(QRingMemBufShmDebugWidget);
        m_edtFileName->setObjectName(QString::fromUtf8("m_edtFileName"));

        gridLayoutNameID->addWidget(m_edtFileName, 0, 2, 1, 1);

        m_edtSendLength = new QLineEdit(QRingMemBufShmDebugWidget);
        m_edtSendLength->setObjectName(QString::fromUtf8("m_edtSendLength"));

        gridLayoutNameID->addWidget(m_edtSendLength, 1, 2, 1, 1);

        m_lblSendLength = new QLabel(QRingMemBufShmDebugWidget);
        m_lblSendLength->setObjectName(QString::fromUtf8("m_lblSendLength"));

        gridLayoutNameID->addWidget(m_lblSendLength, 1, 0, 1, 1);

        m_edtSendLengthTotal = new QLineEdit(QRingMemBufShmDebugWidget);
        m_edtSendLengthTotal->setObjectName(QString::fromUtf8("m_edtSendLengthTotal"));
        m_edtSendLengthTotal->setReadOnly(true);

        gridLayoutNameID->addWidget(m_edtSendLengthTotal, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayoutNameID);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_Btn_WriteDetectPkg = new QPushButton(QRingMemBufShmDebugWidget);
        m_Btn_WriteDetectPkg->setObjectName(QString::fromUtf8("m_Btn_WriteDetectPkg"));

        horizontalLayout->addWidget(m_Btn_WriteDetectPkg);

        m_Btn_WriteRcvPkg = new QPushButton(QRingMemBufShmDebugWidget);
        m_Btn_WriteRcvPkg->setObjectName(QString::fromUtf8("m_Btn_WriteRcvPkg"));

        horizontalLayout->addWidget(m_Btn_WriteRcvPkg);

        m_btnAutoWrite = new QPushButton(QRingMemBufShmDebugWidget);
        m_btnAutoWrite->setObjectName(QString::fromUtf8("m_btnAutoWrite"));

        horizontalLayout->addWidget(m_btnAutoWrite);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QRingMemBufShmDebugWidget);

        QMetaObject::connectSlotsByName(QRingMemBufShmDebugWidget);
    } // setupUi

    void retranslateUi(QDialog *QRingMemBufShmDebugWidget)
    {
        QRingMemBufShmDebugWidget->setWindowTitle(QApplication::translate("QRingMemBufShmDebugWidget", "\346\250\241\346\213\237\345\217\221\347\224\237\345\231\250", 0, QApplication::UnicodeUTF8));
        m_lblSendLength_2->setText(QApplication::translate("QRingMemBufShmDebugWidget", "\346\200\273\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        m_lblFileName->setText(QApplication::translate("QRingMemBufShmDebugWidget", "\346\226\207\344\273\266\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_lblSendLength->setText(QApplication::translate("QRingMemBufShmDebugWidget", "\345\217\221\351\200\201\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        m_Btn_WriteDetectPkg->setText(QApplication::translate("QRingMemBufShmDebugWidget", "\346\250\241\346\213\237\346\216\242\346\265\213", 0, QApplication::UnicodeUTF8));
        m_Btn_WriteRcvPkg->setText(QApplication::translate("QRingMemBufShmDebugWidget", "\346\250\241\346\213\237\346\216\245\345\217\227\346\212\245\346\226\207", 0, QApplication::UnicodeUTF8));
        m_btnAutoWrite->setText(QApplication::translate("QRingMemBufShmDebugWidget", "\350\207\252\345\212\250\346\250\241\346\213\237", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QRingMemBufShmDebugWidget: public Ui_QRingMemBufShmDebugWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RINGMEMBUFSHMDEBUGWIDGET_H
