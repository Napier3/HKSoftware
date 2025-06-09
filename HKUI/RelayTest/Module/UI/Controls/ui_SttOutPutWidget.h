/********************************************************************************
** Form generated from reading UI file 'SttOutPutWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTOUTPUTWIDGET_H
#define UI_STTOUTPUTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../Module/ScrollCtrl/ScrollTextEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QSttOutputWidget
{
public:
    QVBoxLayout *verticalLayout;
    QScrollTextEdit *textEdit;

    void setupUi(QWidget *QSttOutputWidget)
    {
        if (QSttOutputWidget->objectName().isEmpty())
            QSttOutputWidget->setObjectName(QString::fromUtf8("QSttOutputWidget"));
        QSttOutputWidget->setWindowModality(Qt::WindowModal);
        QSttOutputWidget->resize(416, 312);
        verticalLayout = new QVBoxLayout(QSttOutputWidget);
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QScrollTextEdit(QSttOutputWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(QSttOutputWidget);

        QMetaObject::connectSlotsByName(QSttOutputWidget);
    } // setupUi

    void retranslateUi(QWidget *QSttOutputWidget)
    {
        QSttOutputWidget->setWindowTitle(QApplication::translate("QSttOutputWidget", "\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttOutputWidget: public Ui_QSttOutputWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTOUTPUTWIDGET_H
