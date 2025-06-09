/********************************************************************************
** Form generated from reading UI file 'SttAddMacroWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTADDMACROWIDGET_H
#define UI_STTADDMACROWIDGET_H

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

class Ui_QSttAddMacroWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayoutNameID;
    QLabel *m_lblItemsName;
    QLineEdit *m_edtItemsID;
    QLineEdit *m_edtItemsName;
    QLabel *m_lblItemsID;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_Btn_OK;
    QPushButton *m_Btn_Cancel;

    void setupUi(QDialog *QSttAddMacroWidget)
    {
        if (QSttAddMacroWidget->objectName().isEmpty())
            QSttAddMacroWidget->setObjectName(QString::fromUtf8("QSttAddMacroWidget"));
        QSttAddMacroWidget->resize(382, 366);
        verticalLayout_2 = new QVBoxLayout(QSttAddMacroWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayoutNameID = new QGridLayout();
        gridLayoutNameID->setObjectName(QString::fromUtf8("gridLayoutNameID"));
        m_lblItemsName = new QLabel(QSttAddMacroWidget);
        m_lblItemsName->setObjectName(QString::fromUtf8("m_lblItemsName"));

        gridLayoutNameID->addWidget(m_lblItemsName, 0, 0, 1, 1);

        m_edtItemsID = new QLineEdit(QSttAddMacroWidget);
        m_edtItemsID->setObjectName(QString::fromUtf8("m_edtItemsID"));

        gridLayoutNameID->addWidget(m_edtItemsID, 1, 1, 1, 1);

        m_edtItemsName = new QLineEdit(QSttAddMacroWidget);
        m_edtItemsName->setObjectName(QString::fromUtf8("m_edtItemsName"));

        gridLayoutNameID->addWidget(m_edtItemsName, 0, 1, 1, 1);

        m_lblItemsID = new QLabel(QSttAddMacroWidget);
        m_lblItemsID->setObjectName(QString::fromUtf8("m_lblItemsID"));

        gridLayoutNameID->addWidget(m_lblItemsID, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayoutNameID);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_Btn_OK = new QPushButton(QSttAddMacroWidget);
        m_Btn_OK->setObjectName(QString::fromUtf8("m_Btn_OK"));

        horizontalLayout->addWidget(m_Btn_OK);

        m_Btn_Cancel = new QPushButton(QSttAddMacroWidget);
        m_Btn_Cancel->setObjectName(QString::fromUtf8("m_Btn_Cancel"));

        horizontalLayout->addWidget(m_Btn_Cancel);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttAddMacroWidget);

        QMetaObject::connectSlotsByName(QSttAddMacroWidget);
    } // setupUi

    void retranslateUi(QDialog *QSttAddMacroWidget)
    {
        QSttAddMacroWidget->setWindowTitle(QApplication::translate("QSttAddMacroWidget", "\351\200\211\346\213\251\346\265\213\350\257\225\345\212\237\350\203\275", 0, QApplication::UnicodeUTF8));
        m_lblItemsName->setText(QApplication::translate("QSttAddMacroWidget", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_lblItemsID->setText(QApplication::translate("QSttAddMacroWidget", "\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        m_Btn_OK->setText(QApplication::translate("QSttAddMacroWidget", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_Btn_Cancel->setText(QApplication::translate("QSttAddMacroWidget", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttAddMacroWidget: public Ui_QSttAddMacroWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTADDMACROWIDGET_H
