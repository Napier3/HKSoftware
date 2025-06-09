/********************************************************************************
** Form generated from reading UI file 'ResultExprWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTEXPRWIDGET_H
#define UI_RESULTEXPRWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QResultExprWidget
{
public:

    void setupUi(QWidget *QResultExprWidget)
    {
        if (QResultExprWidget->objectName().isEmpty())
            QResultExprWidget->setObjectName(QString::fromUtf8("QResultExprWidget"));
        QResultExprWidget->resize(400, 300);

        retranslateUi(QResultExprWidget);

        QMetaObject::connectSlotsByName(QResultExprWidget);
    } // setupUi

    void retranslateUi(QWidget *QResultExprWidget)
    {
        QResultExprWidget->setWindowTitle(QApplication::translate("QResultExprWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QResultExprWidget: public Ui_QResultExprWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTEXPRWIDGET_H
