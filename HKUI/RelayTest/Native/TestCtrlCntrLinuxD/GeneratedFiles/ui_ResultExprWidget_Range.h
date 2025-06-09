/********************************************************************************
** Form generated from reading UI file 'ResultExprWidget_Range.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTEXPRWIDGET_RANGE_H
#define UI_RESULTEXPRWIDGET_RANGE_H

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

class Ui_QResultExprWidget_Range
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnClose;
    QLabel *label;
    QResultExprWidgetButtonLine *m_editResultParas;
    QPushButton *m_btnResultParasDel;
    QGridLayout *gridLayout_2;
    QResultExprWidgetExprComboBox *m_cbbMinExpr;
    QPushButton *m_btnMinValueDel;
    QPushButton *m_btnMaxValueDel;
    QResultExprWidgetButtonLine *m_editMaxValue;
    QResultExprWidgetExprComboBox *m_cbbMaxExpr;
    QLabel *label_3;
    QResultExprWidgetButtonLine *m_editMinValue;
    QLabel *label_2;

    void setupUi(QWidget *QResultExprWidget_Range)
    {
        if (QResultExprWidget_Range->objectName().isEmpty())
            QResultExprWidget_Range->setObjectName(QString::fromUtf8("QResultExprWidget_Range"));
        QResultExprWidget_Range->resize(700, 100);
        QResultExprWidget_Range->setMinimumSize(QSize(700, 100));
        QResultExprWidget_Range->setMaximumSize(QSize(700, 100));
        gridLayout = new QGridLayout(QResultExprWidget_Range);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btnClose = new QPushButton(QResultExprWidget_Range);
        m_btnClose->setObjectName(QString::fromUtf8("m_btnClose"));
        m_btnClose->setMinimumSize(QSize(20, 20));
        m_btnClose->setMaximumSize(QSize(20, 20));
        m_btnClose->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 0, 0);"));

        horizontalLayout->addWidget(m_btnClose);

        label = new QLabel(QResultExprWidget_Range);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_editResultParas = new QResultExprWidgetButtonLine(QResultExprWidget_Range);
        m_editResultParas->setObjectName(QString::fromUtf8("m_editResultParas"));
        m_editResultParas->setMinimumSize(QSize(0, 30));
        m_editResultParas->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(m_editResultParas);

        m_btnResultParasDel = new QPushButton(QResultExprWidget_Range);
        m_btnResultParasDel->setObjectName(QString::fromUtf8("m_btnResultParasDel"));
        m_btnResultParasDel->setMinimumSize(QSize(20, 20));
        m_btnResultParasDel->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(m_btnResultParasDel);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_cbbMinExpr = new QResultExprWidgetExprComboBox(QResultExprWidget_Range);
        m_cbbMinExpr->setObjectName(QString::fromUtf8("m_cbbMinExpr"));
        m_cbbMinExpr->setMinimumSize(QSize(0, 30));
        m_cbbMinExpr->setMaximumSize(QSize(16777215, 30));

        gridLayout_2->addWidget(m_cbbMinExpr, 0, 0, 1, 1);

        m_btnMinValueDel = new QPushButton(QResultExprWidget_Range);
        m_btnMinValueDel->setObjectName(QString::fromUtf8("m_btnMinValueDel"));
        m_btnMinValueDel->setMinimumSize(QSize(20, 20));
        m_btnMinValueDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnMinValueDel, 0, 3, 1, 1);

        m_btnMaxValueDel = new QPushButton(QResultExprWidget_Range);
        m_btnMaxValueDel->setObjectName(QString::fromUtf8("m_btnMaxValueDel"));
        m_btnMaxValueDel->setEnabled(true);
        m_btnMaxValueDel->setMinimumSize(QSize(20, 20));
        m_btnMaxValueDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnMaxValueDel, 1, 3, 1, 1);

        m_editMaxValue = new QResultExprWidgetButtonLine(QResultExprWidget_Range);
        m_editMaxValue->setObjectName(QString::fromUtf8("m_editMaxValue"));
        m_editMaxValue->setMinimumSize(QSize(0, 30));
        m_editMaxValue->setMaximumSize(QSize(16777215, 30));

        gridLayout_2->addWidget(m_editMaxValue, 1, 2, 1, 1);

        m_cbbMaxExpr = new QResultExprWidgetExprComboBox(QResultExprWidget_Range);
        m_cbbMaxExpr->setObjectName(QString::fromUtf8("m_cbbMaxExpr"));
        m_cbbMaxExpr->setMinimumSize(QSize(0, 30));
        m_cbbMaxExpr->setMaximumSize(QSize(16777215, 30));

        gridLayout_2->addWidget(m_cbbMaxExpr, 1, 0, 1, 1);

        label_3 = new QLabel(QResultExprWidget_Range);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 1, 1, 1);

        m_editMinValue = new QResultExprWidgetButtonLine(QResultExprWidget_Range);
        m_editMinValue->setObjectName(QString::fromUtf8("m_editMinValue"));
        m_editMinValue->setMinimumSize(QSize(0, 30));
        m_editMinValue->setMaximumSize(QSize(16777215, 30));

        gridLayout_2->addWidget(m_editMinValue, 0, 2, 1, 1);

        label_2 = new QLabel(QResultExprWidget_Range);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(QResultExprWidget_Range);

        QMetaObject::connectSlotsByName(QResultExprWidget_Range);
    } // setupUi

    void retranslateUi(QWidget *QResultExprWidget_Range)
    {
        QResultExprWidget_Range->setWindowTitle(QApplication::translate("QResultExprWidget_Range", "Form", 0, QApplication::UnicodeUTF8));
        m_btnClose->setText(QApplication::translate("QResultExprWidget_Range", "x", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QResultExprWidget_Range", "\347\273\223\346\236\234\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_btnResultParasDel->setText(QApplication::translate("QResultExprWidget_Range", "x", 0, QApplication::UnicodeUTF8));
        m_btnMinValueDel->setText(QApplication::translate("QResultExprWidget_Range", "x", 0, QApplication::UnicodeUTF8));
        m_btnMaxValueDel->setText(QApplication::translate("QResultExprWidget_Range", "x", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QResultExprWidget_Range", "\345\237\272\345\207\206-\346\234\200\345\244\247\345\200\274", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QResultExprWidget_Range", "\345\237\272\345\207\206-\346\234\200\345\260\217\345\200\274", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QResultExprWidget_Range: public Ui_QResultExprWidget_Range {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTEXPRWIDGET_RANGE_H
