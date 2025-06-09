/********************************************************************************
** Form generated from reading UI file 'SttFileSaveAsDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTFILESAVEASDLG_H
#define UI_STTFILESAVEASDLG_H

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
#include "sttlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QSttFileSaveAsDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *m_lblFileFolder;
    QSttLineEdit *m_wndFolderName;
    QSttLineEdit *m_wndFileName;
    QLabel *m_lblFileName;
    QLineEdit *m_wndInfor;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_Btn_OK;
    QPushButton *m_Btn_Cancel;

    void setupUi(QDialog *QSttFileSaveAsDlg)
    {
        if (QSttFileSaveAsDlg->objectName().isEmpty())
            QSttFileSaveAsDlg->setObjectName(QString::fromUtf8("QSttFileSaveAsDlg"));
        QSttFileSaveAsDlg->resize(562, 159);
        verticalLayout_2 = new QVBoxLayout(QSttFileSaveAsDlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_lblFileFolder = new QLabel(QSttFileSaveAsDlg);
        m_lblFileFolder->setObjectName(QString::fromUtf8("m_lblFileFolder"));
        QFont font;
        font.setPointSize(16);
        m_lblFileFolder->setFont(font);
        m_lblFileFolder->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(m_lblFileFolder, 0, 1, 1, 1);

        m_wndFolderName = new QSttLineEdit(QSttFileSaveAsDlg);
        m_wndFolderName->setObjectName(QString::fromUtf8("m_wndFolderName"));
        m_wndFolderName->setFont(font);
        m_wndFolderName->setReadOnly(false);

        gridLayout->addWidget(m_wndFolderName, 0, 3, 1, 1);

        m_wndFileName = new QSttLineEdit(QSttFileSaveAsDlg);
        m_wndFileName->setObjectName(QString::fromUtf8("m_wndFileName"));
        m_wndFileName->setFont(font);

        gridLayout->addWidget(m_wndFileName, 2, 3, 1, 1);

        m_lblFileName = new QLabel(QSttFileSaveAsDlg);
        m_lblFileName->setObjectName(QString::fromUtf8("m_lblFileName"));
        m_lblFileName->setFont(font);
        m_lblFileName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(m_lblFileName, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        m_wndInfor = new QLineEdit(QSttFileSaveAsDlg);
        m_wndInfor->setObjectName(QString::fromUtf8("m_wndInfor"));
        m_wndInfor->setEnabled(false);
        m_wndInfor->setFont(font);
        m_wndInfor->setReadOnly(true);

        verticalLayout->addWidget(m_wndInfor);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_Btn_OK = new QPushButton(QSttFileSaveAsDlg);
        m_Btn_OK->setObjectName(QString::fromUtf8("m_Btn_OK"));
        m_Btn_OK->setFont(font);

        horizontalLayout->addWidget(m_Btn_OK);

        m_Btn_Cancel = new QPushButton(QSttFileSaveAsDlg);
        m_Btn_Cancel->setObjectName(QString::fromUtf8("m_Btn_Cancel"));
        m_Btn_Cancel->setFont(font);

        horizontalLayout->addWidget(m_Btn_Cancel);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttFileSaveAsDlg);

        QMetaObject::connectSlotsByName(QSttFileSaveAsDlg);
    } // setupUi

    void retranslateUi(QDialog *QSttFileSaveAsDlg)
    {
        QSttFileSaveAsDlg->setWindowTitle(QApplication::translate("QSttFileSaveAsDlg", "Edit", 0, QApplication::UnicodeUTF8));
        m_lblFileFolder->setText(QApplication::translate("QSttFileSaveAsDlg", "\346\226\207\344\273\266\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        m_lblFileName->setText(QApplication::translate("QSttFileSaveAsDlg", "\346\226\207\344\273\266\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_Btn_OK->setText(QApplication::translate("QSttFileSaveAsDlg", "OK", 0, QApplication::UnicodeUTF8));
        m_Btn_Cancel->setText(QApplication::translate("QSttFileSaveAsDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttFileSaveAsDlg: public Ui_QSttFileSaveAsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTFILESAVEASDLG_H
