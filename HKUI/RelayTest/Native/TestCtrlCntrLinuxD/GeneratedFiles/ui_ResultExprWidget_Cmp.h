/********************************************************************************
** Form generated from reading UI file 'ResultExprWidget_Cmp.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTEXPRWIDGET_CMP_H
#define UI_RESULTEXPRWIDGET_CMP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include "ResultExprWidgetItem.h"

QT_BEGIN_NAMESPACE

class Ui_QResultExprWidget_Cmp
{
public:
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_btnClose;
    QGridLayout *gridLayout;
    QResultExprWidgetButtonLine *m_editValue1;
    QPushButton *m_btnDel1;
    QResultExprWidgetButtonLine *m_editValue2;
    QResultExprWidgetExprComboBox *m_cbbExpr;
    QPushButton *m_btnDel2;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *QResultExprWidget_Cmp)
    {
        if (QResultExprWidget_Cmp->objectName().isEmpty())
            QResultExprWidget_Cmp->setObjectName(QString::fromUtf8("QResultExprWidget_Cmp"));
        QResultExprWidget_Cmp->resize(700, 80);
        QResultExprWidget_Cmp->setMinimumSize(QSize(700, 80));
        QResultExprWidget_Cmp->setMaximumSize(QSize(700, 80));
        horizontalLayout = new QHBoxLayout(QResultExprWidget_Cmp);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_btnClose = new QPushButton(QResultExprWidget_Cmp);
        m_btnClose->setObjectName(QString::fromUtf8("m_btnClose"));
        m_btnClose->setMinimumSize(QSize(20, 20));
        m_btnClose->setMaximumSize(QSize(20, 20));
        m_btnClose->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 0, 0);"));

        horizontalLayout_2->addWidget(m_btnClose);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_editValue1 = new QResultExprWidgetButtonLine(QResultExprWidget_Cmp);
        m_editValue1->setObjectName(QString::fromUtf8("m_editValue1"));
        m_editValue1->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(m_editValue1, 1, 1, 1, 1);

        m_btnDel1 = new QPushButton(QResultExprWidget_Cmp);
        m_btnDel1->setObjectName(QString::fromUtf8("m_btnDel1"));
        m_btnDel1->setMinimumSize(QSize(20, 20));
        m_btnDel1->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(m_btnDel1, 1, 2, 1, 1);

        m_editValue2 = new QResultExprWidgetButtonLine(QResultExprWidget_Cmp);
        m_editValue2->setObjectName(QString::fromUtf8("m_editValue2"));
        m_editValue2->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(m_editValue2, 1, 5, 1, 1);

        m_cbbExpr = new QResultExprWidgetExprComboBox(QResultExprWidget_Cmp);
        m_cbbExpr->setObjectName(QString::fromUtf8("m_cbbExpr"));
        m_cbbExpr->setMinimumSize(QSize(0, 30));
        m_cbbExpr->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_cbbExpr, 1, 3, 1, 1);

        m_btnDel2 = new QPushButton(QResultExprWidget_Cmp);
        m_btnDel2->setObjectName(QString::fromUtf8("m_btnDel2"));
        m_btnDel2->setMinimumSize(QSize(20, 20));
        m_btnDel2->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(m_btnDel2, 1, 6, 1, 1);

        label = new QLabel(QResultExprWidget_Cmp);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(QResultExprWidget_Cmp);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 4, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        horizontalLayout->addLayout(horizontalLayout_2);


        retranslateUi(QResultExprWidget_Cmp);

        QMetaObject::connectSlotsByName(QResultExprWidget_Cmp);
    } // setupUi

    void retranslateUi(QWidget *QResultExprWidget_Cmp)
    {
        QResultExprWidget_Cmp->setWindowTitle(QApplication::translate("QResultExprWidget_Cmp", "Form", 0, QApplication::UnicodeUTF8));
        m_btnClose->setText(QApplication::translate("QResultExprWidget_Cmp", "x", 0, QApplication::UnicodeUTF8));
        m_btnDel1->setText(QApplication::translate("QResultExprWidget_Cmp", "x", 0, QApplication::UnicodeUTF8));
        m_btnDel2->setText(QApplication::translate("QResultExprWidget_Cmp", "x", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QResultExprWidget_Cmp", "\345\217\202\346\225\260\344\270\200", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QResultExprWidget_Cmp", "\345\217\202\346\225\260\344\272\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QResultExprWidget_Cmp: public Ui_QResultExprWidget_Cmp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTEXPRWIDGET_CMP_H
