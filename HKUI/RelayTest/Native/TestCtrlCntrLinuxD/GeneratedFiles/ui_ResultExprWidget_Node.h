/********************************************************************************
** Form generated from reading UI file 'ResultExprWidget_Node.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTEXPRWIDGET_NODE_H
#define UI_RESULTEXPRWIDGET_NODE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "ResultExprWidgetItem.h"

QT_BEGIN_NAMESPACE

class Ui_QResultExprWidget_Node
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnClose;
    QHBoxLayout *horizontalLayout;
    QLineEdit *m_editTrue;
    QComboBox *m_cbbExpr;
    QPushButton *m_btnAdd;
    QPushButton *m_btnExpand;
    QHBoxLayout *horizontalLayout_2;
    QResultExprWidgetButtonLine *m_editExpr;
    QPushButton *m_btnDel;

    void setupUi(QWidget *QResultExprWidget_Node)
    {
        if (QResultExprWidget_Node->objectName().isEmpty())
            QResultExprWidget_Node->setObjectName(QString::fromUtf8("QResultExprWidget_Node"));
        QResultExprWidget_Node->resize(260, 120);
        QResultExprWidget_Node->setMinimumSize(QSize(260, 120));
        QResultExprWidget_Node->setMaximumSize(QSize(260, 120));
        verticalLayout = new QVBoxLayout(QResultExprWidget_Node);
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        m_btnClose = new QPushButton(QResultExprWidget_Node);
        m_btnClose->setObjectName(QString::fromUtf8("m_btnClose"));
        m_btnClose->setMinimumSize(QSize(20, 20));
        m_btnClose->setMaximumSize(QSize(20, 20));
        m_btnClose->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 0, 0);"));

        horizontalLayout_3->addWidget(m_btnClose);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_editTrue = new QLineEdit(QResultExprWidget_Node);
        m_editTrue->setObjectName(QString::fromUtf8("m_editTrue"));
        m_editTrue->setMinimumSize(QSize(0, 30));
        m_editTrue->setMaximumSize(QSize(50, 30));
        m_editTrue->setReadOnly(true);

        horizontalLayout->addWidget(m_editTrue);

        m_cbbExpr = new QComboBox(QResultExprWidget_Node);
        m_cbbExpr->setObjectName(QString::fromUtf8("m_cbbExpr"));
        m_cbbExpr->setMinimumSize(QSize(0, 30));
        m_cbbExpr->setMaximumSize(QSize(60, 30));

        horizontalLayout->addWidget(m_cbbExpr);

        m_btnAdd = new QPushButton(QResultExprWidget_Node);
        m_btnAdd->setObjectName(QString::fromUtf8("m_btnAdd"));
        m_btnAdd->setMinimumSize(QSize(0, 30));
        m_btnAdd->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(m_btnAdd);

        m_btnExpand = new QPushButton(QResultExprWidget_Node);
        m_btnExpand->setObjectName(QString::fromUtf8("m_btnExpand"));
        m_btnExpand->setMinimumSize(QSize(20, 20));
        m_btnExpand->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(m_btnExpand);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_editExpr = new QResultExprWidgetButtonLine(QResultExprWidget_Node);
        m_editExpr->setObjectName(QString::fromUtf8("m_editExpr"));
        m_editExpr->setMinimumSize(QSize(0, 30));
        m_editExpr->setMaximumSize(QSize(16777215, 30));
        m_editExpr->setReadOnly(true);

        horizontalLayout_2->addWidget(m_editExpr);

        m_btnDel = new QPushButton(QResultExprWidget_Node);
        m_btnDel->setObjectName(QString::fromUtf8("m_btnDel"));
        m_btnDel->setMinimumSize(QSize(20, 20));
        m_btnDel->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(m_btnDel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(QResultExprWidget_Node);

        QMetaObject::connectSlotsByName(QResultExprWidget_Node);
    } // setupUi

    void retranslateUi(QWidget *QResultExprWidget_Node)
    {
        QResultExprWidget_Node->setWindowTitle(QApplication::translate("QResultExprWidget_Node", "Form", 0, QApplication::UnicodeUTF8));
        m_btnClose->setText(QApplication::translate("QResultExprWidget_Node", "x", 0, QApplication::UnicodeUTF8));
        m_editTrue->setText(QApplication::translate("QResultExprWidget_Node", "\346\234\252\350\256\241\347\256\227", 0, QApplication::UnicodeUTF8));
        m_cbbExpr->clear();
        m_cbbExpr->insertItems(0, QStringList()
         << QApplication::translate("QResultExprWidget_Node", "\344\270\216", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QResultExprWidget_Node", "\346\210\226", 0, QApplication::UnicodeUTF8)
        );
        m_btnAdd->setText(QApplication::translate("QResultExprWidget_Node", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        m_btnExpand->setText(QApplication::translate("QResultExprWidget_Node", "-", 0, QApplication::UnicodeUTF8));
        m_btnDel->setText(QApplication::translate("QResultExprWidget_Node", "x", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QResultExprWidget_Node: public Ui_QResultExprWidget_Node {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTEXPRWIDGET_NODE_H
