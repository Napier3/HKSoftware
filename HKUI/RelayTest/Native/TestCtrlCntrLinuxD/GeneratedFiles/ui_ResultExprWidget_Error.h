/********************************************************************************
** Form generated from reading UI file 'ResultExprWidget_Error.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTEXPRWIDGET_ERROR_H
#define UI_RESULTEXPRWIDGET_ERROR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include "ResultExprWidgetItem.h"

QT_BEGIN_NAMESPACE

class Ui_QResultExprWidget_Error
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnClose;
    QGridLayout *gridLayout_2;
    QResultExprWidgetButtonLine *m_editErrorResult;
    QResultExprWidgetExprComboBox *m_cbbExpr;
    QLabel *label_5;
    QResultExprWidgetButtonLine *m_editErrorValue;
    QLabel *label_3;
    QResultExprWidgetButtonLine *m_editResultParas;
    QLabel *label;
    QPushButton *m_btnResultParasDel;
    QPushButton *m_btnErrorResultDel;
    QComboBox *m_cbbExprType;
    QPushButton *m_btnErrorValueDel;
    QResultExprWidgetButtonLine *m_editStdParas;
    QPushButton *m_btnStdParasDel;
    QLabel *label_2;

    void setupUi(QWidget *QResultExprWidget_Error)
    {
        if (QResultExprWidget_Error->objectName().isEmpty())
            QResultExprWidget_Error->setObjectName(QString::fromUtf8("QResultExprWidget_Error"));
        QResultExprWidget_Error->resize(800, 95);
        QResultExprWidget_Error->setMinimumSize(QSize(800, 95));
        QResultExprWidget_Error->setMaximumSize(QSize(800, 95));
        gridLayout = new QGridLayout(QResultExprWidget_Error);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btnClose = new QPushButton(QResultExprWidget_Error);
        m_btnClose->setObjectName(QString::fromUtf8("m_btnClose"));
        m_btnClose->setMinimumSize(QSize(20, 20));
        m_btnClose->setMaximumSize(QSize(20, 20));
        m_btnClose->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 0, 0);"));

        horizontalLayout->addWidget(m_btnClose);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_editErrorResult = new QResultExprWidgetButtonLine(QResultExprWidget_Error);
        m_editErrorResult->setObjectName(QString::fromUtf8("m_editErrorResult"));
        m_editErrorResult->setMinimumSize(QSize(0, 30));
        m_editErrorResult->setMaximumSize(QSize(16777215, 30));

        gridLayout_2->addWidget(m_editErrorResult, 1, 1, 1, 1);

        m_cbbExpr = new QResultExprWidgetExprComboBox(QResultExprWidget_Error);
        m_cbbExpr->setObjectName(QString::fromUtf8("m_cbbExpr"));
        m_cbbExpr->setMinimumSize(QSize(0, 30));
        m_cbbExpr->setMaximumSize(QSize(120, 30));

        gridLayout_2->addWidget(m_cbbExpr, 1, 3, 1, 1);

        label_5 = new QLabel(QResultExprWidget_Error);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 5, 1, 1);

        m_editErrorValue = new QResultExprWidgetButtonLine(QResultExprWidget_Error);
        m_editErrorValue->setObjectName(QString::fromUtf8("m_editErrorValue"));
        m_editErrorValue->setMinimumSize(QSize(0, 30));
        m_editErrorValue->setMaximumSize(QSize(16777215, 30));

        gridLayout_2->addWidget(m_editErrorValue, 1, 6, 1, 1);

        label_3 = new QLabel(QResultExprWidget_Error);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        m_editResultParas = new QResultExprWidgetButtonLine(QResultExprWidget_Error);
        m_editResultParas->setObjectName(QString::fromUtf8("m_editResultParas"));
        m_editResultParas->setMinimumSize(QSize(0, 30));
        m_editResultParas->setMaximumSize(QSize(16777215, 30));

        gridLayout_2->addWidget(m_editResultParas, 0, 1, 1, 1);

        label = new QLabel(QResultExprWidget_Error);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        m_btnResultParasDel = new QPushButton(QResultExprWidget_Error);
        m_btnResultParasDel->setObjectName(QString::fromUtf8("m_btnResultParasDel"));
        m_btnResultParasDel->setMinimumSize(QSize(20, 20));
        m_btnResultParasDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnResultParasDel, 0, 2, 1, 1);

        m_btnErrorResultDel = new QPushButton(QResultExprWidget_Error);
        m_btnErrorResultDel->setObjectName(QString::fromUtf8("m_btnErrorResultDel"));
        m_btnErrorResultDel->setMinimumSize(QSize(20, 20));
        m_btnErrorResultDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnErrorResultDel, 1, 2, 1, 1);

        m_cbbExprType = new QComboBox(QResultExprWidget_Error);
        m_cbbExprType->setObjectName(QString::fromUtf8("m_cbbExprType"));
        m_cbbExprType->setMinimumSize(QSize(0, 30));
        m_cbbExprType->setMaximumSize(QSize(120, 30));

        gridLayout_2->addWidget(m_cbbExprType, 1, 4, 1, 1);

        m_btnErrorValueDel = new QPushButton(QResultExprWidget_Error);
        m_btnErrorValueDel->setObjectName(QString::fromUtf8("m_btnErrorValueDel"));
        m_btnErrorValueDel->setMinimumSize(QSize(20, 20));
        m_btnErrorValueDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnErrorValueDel, 1, 7, 1, 1);

        m_editStdParas = new QResultExprWidgetButtonLine(QResultExprWidget_Error);
        m_editStdParas->setObjectName(QString::fromUtf8("m_editStdParas"));
        m_editStdParas->setMinimumSize(QSize(0, 30));
        m_editStdParas->setMaximumSize(QSize(16777215, 30));

        gridLayout_2->addWidget(m_editStdParas, 0, 6, 1, 1);

        m_btnStdParasDel = new QPushButton(QResultExprWidget_Error);
        m_btnStdParasDel->setObjectName(QString::fromUtf8("m_btnStdParasDel"));
        m_btnStdParasDel->setMinimumSize(QSize(20, 20));
        m_btnStdParasDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnStdParasDel, 0, 7, 1, 1);

        label_2 = new QLabel(QResultExprWidget_Error);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 5, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);


        retranslateUi(QResultExprWidget_Error);

        QMetaObject::connectSlotsByName(QResultExprWidget_Error);
    } // setupUi

    void retranslateUi(QWidget *QResultExprWidget_Error)
    {
        QResultExprWidget_Error->setWindowTitle(QApplication::translate("QResultExprWidget_Error", "Form", 0, QApplication::UnicodeUTF8));
        m_btnClose->setText(QApplication::translate("QResultExprWidget_Error", "x", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QResultExprWidget_Error", "\350\257\257\345\267\256\351\231\220", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QResultExprWidget_Error", "\350\257\257\345\267\256\347\273\223\346\236\234", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QResultExprWidget_Error", "\347\273\223\346\236\234\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_btnResultParasDel->setText(QApplication::translate("QResultExprWidget_Error", "x", 0, QApplication::UnicodeUTF8));
        m_btnErrorResultDel->setText(QApplication::translate("QResultExprWidget_Error", "x", 0, QApplication::UnicodeUTF8));
        m_cbbExprType->clear();
        m_cbbExprType->insertItems(0, QStringList()
         << QApplication::translate("QResultExprWidget_Error", "\347\273\235\345\257\271\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QResultExprWidget_Error", "\347\233\270\345\257\271\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8)
        );
        m_btnErrorValueDel->setText(QApplication::translate("QResultExprWidget_Error", "x", 0, QApplication::UnicodeUTF8));
        m_btnStdParasDel->setText(QApplication::translate("QResultExprWidget_Error", "x", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QResultExprWidget_Error", "\345\237\272\345\207\206\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QResultExprWidget_Error: public Ui_QResultExprWidget_Error {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTEXPRWIDGET_ERROR_H
