/********************************************************************************
** Form generated from reading UI file 'qsttzoneindexsetdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSTTZONEINDEXSETDLG_H
#define UI_QSTTZONEINDEXSETDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttZoneIndexSetDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *m_wndFrameZone;
    QLabel *m_lblZone;
    QComboBox *m_cmbZone;
    QHBoxLayout *m_wndFrameBtns;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;

    void setupUi(QDialog *QSttZoneIndexSetDlg)
    {
        if (QSttZoneIndexSetDlg->objectName().isEmpty())
            QSttZoneIndexSetDlg->setObjectName(QString::fromUtf8("QSttZoneIndexSetDlg"));
        QSttZoneIndexSetDlg->resize(193, 89);
        verticalLayout_2 = new QVBoxLayout(QSttZoneIndexSetDlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_wndFrameZone = new QHBoxLayout();
        m_wndFrameZone->setObjectName(QString::fromUtf8("m_wndFrameZone"));
        m_lblZone = new QLabel(QSttZoneIndexSetDlg);
        m_lblZone->setObjectName(QString::fromUtf8("m_lblZone"));

        m_wndFrameZone->addWidget(m_lblZone);

        m_cmbZone = new QComboBox(QSttZoneIndexSetDlg);
        m_cmbZone->setObjectName(QString::fromUtf8("m_cmbZone"));

        m_wndFrameZone->addWidget(m_cmbZone);


        verticalLayout_2->addLayout(m_wndFrameZone);

        m_wndFrameBtns = new QHBoxLayout();
        m_wndFrameBtns->setObjectName(QString::fromUtf8("m_wndFrameBtns"));
        m_btnOK = new QPushButton(QSttZoneIndexSetDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        m_wndFrameBtns->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QSttZoneIndexSetDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        m_wndFrameBtns->addWidget(m_btnCancel);


        verticalLayout_2->addLayout(m_wndFrameBtns);


        retranslateUi(QSttZoneIndexSetDlg);

        QMetaObject::connectSlotsByName(QSttZoneIndexSetDlg);
    } // setupUi

    void retranslateUi(QDialog *QSttZoneIndexSetDlg)
    {
        QSttZoneIndexSetDlg->setWindowTitle(QApplication::translate("QSttZoneIndexSetDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        m_lblZone->setText(QApplication::translate("QSttZoneIndexSetDlg", "\351\200\211\346\213\251\345\256\232\345\200\274\345\214\272\345\217\267", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QSttZoneIndexSetDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QSttZoneIndexSetDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttZoneIndexSetDlg: public Ui_QSttZoneIndexSetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSTTZONEINDEXSETDLG_H
