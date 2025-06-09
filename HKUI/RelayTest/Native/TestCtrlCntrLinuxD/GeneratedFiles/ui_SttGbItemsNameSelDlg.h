/********************************************************************************
** Form generated from reading UI file 'SttGbItemsNameSelDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTGBITEMSNAMESELDLG_H
#define UI_STTGBITEMSNAMESELDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttGbItemsNameSelDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QComboBox *m_cmbItemsName;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_Btn_OK;
    QPushButton *m_Btn_Cancel;

    void setupUi(QDialog *QSttGbItemsNameSelDlg)
    {
        if (QSttGbItemsNameSelDlg->objectName().isEmpty())
            QSttGbItemsNameSelDlg->setObjectName(QString::fromUtf8("QSttGbItemsNameSelDlg"));
        QSttGbItemsNameSelDlg->resize(486, 113);
        verticalLayout_2 = new QVBoxLayout(QSttGbItemsNameSelDlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_cmbItemsName = new QComboBox(QSttGbItemsNameSelDlg);
        m_cmbItemsName->setObjectName(QString::fromUtf8("m_cmbItemsName"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(16);
        m_cmbItemsName->setFont(font);

        gridLayout->addWidget(m_cmbItemsName, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_Btn_OK = new QPushButton(QSttGbItemsNameSelDlg);
        m_Btn_OK->setObjectName(QString::fromUtf8("m_Btn_OK"));
        QFont font1;
        font1.setPointSize(16);
        m_Btn_OK->setFont(font1);

        horizontalLayout->addWidget(m_Btn_OK);

        m_Btn_Cancel = new QPushButton(QSttGbItemsNameSelDlg);
        m_Btn_Cancel->setObjectName(QString::fromUtf8("m_Btn_Cancel"));
        m_Btn_Cancel->setFont(font1);

        horizontalLayout->addWidget(m_Btn_Cancel);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttGbItemsNameSelDlg);

        QMetaObject::connectSlotsByName(QSttGbItemsNameSelDlg);
    } // setupUi

    void retranslateUi(QDialog *QSttGbItemsNameSelDlg)
    {
        QSttGbItemsNameSelDlg->setWindowTitle(QApplication::translate("QSttGbItemsNameSelDlg", "Edit", 0, QApplication::UnicodeUTF8));
        m_Btn_OK->setText(QApplication::translate("QSttGbItemsNameSelDlg", "OK", 0, QApplication::UnicodeUTF8));
        m_Btn_Cancel->setText(QApplication::translate("QSttGbItemsNameSelDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttGbItemsNameSelDlg: public Ui_QSttGbItemsNameSelDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTGBITEMSNAMESELDLG_H
