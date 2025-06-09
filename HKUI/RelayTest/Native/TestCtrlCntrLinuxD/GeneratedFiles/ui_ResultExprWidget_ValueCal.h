/********************************************************************************
** Form generated from reading UI file 'ResultExprWidget_ValueCal.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTEXPRWIDGET_VALUECAL_H
#define UI_RESULTEXPRWIDGET_VALUECAL_H

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

class Ui_QResultExprWidget_ValueCal
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnClose;
    QGridLayout *gridLayout_2;
    QPushButton *m_btnErrorResultDel;
    QPushButton *m_btnStdValueDel;
    QResultExprWidgetButtonLine *m_editValue1;
    QResultExprWidgetButtonLine *m_editStdValue;
    QResultExprWidgetButtonLine *m_editValue2;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label;
    QComboBox *m_cbbExprType;
    QResultExprWidgetExprComboBox *m_cbbExpr;
    QResultExprWidgetButtonLine *m_editCalResult;
    QLabel *label_3;
    QResultExprWidgetExprComboBox *m_cbbCalType;
    QPushButton *m_btnValue2Del;
    QPushButton *m_btnCalResultDel;
    QPushButton *m_btnErrorValueDel;
    QPushButton *m_btnValue1Del;
    QLabel *label_6;
    QLabel *label_5;
    QResultExprWidgetButtonLine *m_editErrorResult;
    QResultExprWidgetButtonLine *m_editErrorValue;

    void setupUi(QWidget *QResultExprWidget_ValueCal)
    {
        if (QResultExprWidget_ValueCal->objectName().isEmpty())
            QResultExprWidget_ValueCal->setObjectName(QString::fromUtf8("QResultExprWidget_ValueCal"));
        QResultExprWidget_ValueCal->resize(750, 130);
        QResultExprWidget_ValueCal->setMinimumSize(QSize(750, 130));
        QResultExprWidget_ValueCal->setMaximumSize(QSize(750, 130));
        gridLayout = new QGridLayout(QResultExprWidget_ValueCal);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btnClose = new QPushButton(QResultExprWidget_ValueCal);
        m_btnClose->setObjectName(QString::fromUtf8("m_btnClose"));
        m_btnClose->setMinimumSize(QSize(20, 20));
        m_btnClose->setMaximumSize(QSize(20, 20));
        m_btnClose->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 0, 0);"));

        horizontalLayout->addWidget(m_btnClose);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_btnErrorResultDel = new QPushButton(QResultExprWidget_ValueCal);
        m_btnErrorResultDel->setObjectName(QString::fromUtf8("m_btnErrorResultDel"));
        m_btnErrorResultDel->setMinimumSize(QSize(20, 2));
        m_btnErrorResultDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnErrorResultDel, 2, 8, 1, 1);

        m_btnStdValueDel = new QPushButton(QResultExprWidget_ValueCal);
        m_btnStdValueDel->setObjectName(QString::fromUtf8("m_btnStdValueDel"));
        m_btnStdValueDel->setMinimumSize(QSize(20, 2));
        m_btnStdValueDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnStdValueDel, 1, 8, 1, 1);

        m_editValue1 = new QResultExprWidgetButtonLine(QResultExprWidget_ValueCal);
        m_editValue1->setObjectName(QString::fromUtf8("m_editValue1"));
        m_editValue1->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(m_editValue1, 0, 1, 1, 1);

        m_editStdValue = new QResultExprWidgetButtonLine(QResultExprWidget_ValueCal);
        m_editStdValue->setObjectName(QString::fromUtf8("m_editStdValue"));
        m_editStdValue->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(m_editStdValue, 1, 7, 1, 1);

        m_editValue2 = new QResultExprWidgetButtonLine(QResultExprWidget_ValueCal);
        m_editValue2->setObjectName(QString::fromUtf8("m_editValue2"));
        m_editValue2->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(m_editValue2, 0, 7, 1, 1);

        label_4 = new QLabel(QResultExprWidget_ValueCal);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 5, 1, 1);

        label_2 = new QLabel(QResultExprWidget_ValueCal);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 5, 1, 1);

        label = new QLabel(QResultExprWidget_ValueCal);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        m_cbbExprType = new QComboBox(QResultExprWidget_ValueCal);
        m_cbbExprType->setObjectName(QString::fromUtf8("m_cbbExprType"));
        m_cbbExprType->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(m_cbbExprType, 2, 4, 1, 1);

        m_cbbExpr = new QResultExprWidgetExprComboBox(QResultExprWidget_ValueCal);
        m_cbbExpr->setObjectName(QString::fromUtf8("m_cbbExpr"));
        m_cbbExpr->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(m_cbbExpr, 2, 3, 1, 1);

        m_editCalResult = new QResultExprWidgetButtonLine(QResultExprWidget_ValueCal);
        m_editCalResult->setObjectName(QString::fromUtf8("m_editCalResult"));
        m_editCalResult->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(m_editCalResult, 1, 1, 1, 1);

        label_3 = new QLabel(QResultExprWidget_ValueCal);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        m_cbbCalType = new QResultExprWidgetExprComboBox(QResultExprWidget_ValueCal);
        m_cbbCalType->setObjectName(QString::fromUtf8("m_cbbCalType"));
        m_cbbCalType->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(m_cbbCalType, 0, 3, 1, 1);

        m_btnValue2Del = new QPushButton(QResultExprWidget_ValueCal);
        m_btnValue2Del->setObjectName(QString::fromUtf8("m_btnValue2Del"));
        m_btnValue2Del->setMinimumSize(QSize(20, 2));
        m_btnValue2Del->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnValue2Del, 0, 8, 1, 1);

        m_btnCalResultDel = new QPushButton(QResultExprWidget_ValueCal);
        m_btnCalResultDel->setObjectName(QString::fromUtf8("m_btnCalResultDel"));
        m_btnCalResultDel->setMinimumSize(QSize(20, 2));
        m_btnCalResultDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnCalResultDel, 1, 2, 1, 1);

        m_btnErrorValueDel = new QPushButton(QResultExprWidget_ValueCal);
        m_btnErrorValueDel->setObjectName(QString::fromUtf8("m_btnErrorValueDel"));
        m_btnErrorValueDel->setMinimumSize(QSize(20, 2));
        m_btnErrorValueDel->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnErrorValueDel, 2, 2, 1, 1);

        m_btnValue1Del = new QPushButton(QResultExprWidget_ValueCal);
        m_btnValue1Del->setObjectName(QString::fromUtf8("m_btnValue1Del"));
        m_btnValue1Del->setMinimumSize(QSize(20, 2));
        m_btnValue1Del->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(m_btnValue1Del, 0, 2, 1, 1);

        label_6 = new QLabel(QResultExprWidget_ValueCal);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        label_5 = new QLabel(QResultExprWidget_ValueCal);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 5, 1, 1);

        m_editErrorResult = new QResultExprWidgetButtonLine(QResultExprWidget_ValueCal);
        m_editErrorResult->setObjectName(QString::fromUtf8("m_editErrorResult"));
        m_editErrorResult->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(m_editErrorResult, 2, 1, 1, 1);

        m_editErrorValue = new QResultExprWidgetButtonLine(QResultExprWidget_ValueCal);
        m_editErrorValue->setObjectName(QString::fromUtf8("m_editErrorValue"));
        m_editErrorValue->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(m_editErrorValue, 2, 7, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(QResultExprWidget_ValueCal);

        QMetaObject::connectSlotsByName(QResultExprWidget_ValueCal);
    } // setupUi

    void retranslateUi(QWidget *QResultExprWidget_ValueCal)
    {
        QResultExprWidget_ValueCal->setWindowTitle(QApplication::translate("QResultExprWidget_ValueCal", "Form", 0, QApplication::UnicodeUTF8));
        m_btnClose->setText(QApplication::translate("QResultExprWidget_ValueCal", "x", 0, QApplication::UnicodeUTF8));
        m_btnErrorResultDel->setText(QApplication::translate("QResultExprWidget_ValueCal", "x", 0, QApplication::UnicodeUTF8));
        m_btnStdValueDel->setText(QApplication::translate("QResultExprWidget_ValueCal", "x", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QResultExprWidget_ValueCal", "\345\237\272\345\207\206\345\200\274", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QResultExprWidget_ValueCal", "\345\217\202\346\225\260\344\272\214", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QResultExprWidget_ValueCal", "\345\217\202\346\225\260\344\270\200", 0, QApplication::UnicodeUTF8));
        m_cbbExprType->clear();
        m_cbbExprType->insertItems(0, QStringList()
         << QApplication::translate("QResultExprWidget_ValueCal", "\347\233\270\345\257\271\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QResultExprWidget_ValueCal", "\347\273\235\345\257\271\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("QResultExprWidget_ValueCal", "\350\277\220\347\256\227\347\273\223\346\236\234", 0, QApplication::UnicodeUTF8));
        m_btnValue2Del->setText(QApplication::translate("QResultExprWidget_ValueCal", "x", 0, QApplication::UnicodeUTF8));
        m_btnCalResultDel->setText(QApplication::translate("QResultExprWidget_ValueCal", "x", 0, QApplication::UnicodeUTF8));
        m_btnErrorValueDel->setText(QApplication::translate("QResultExprWidget_ValueCal", "x", 0, QApplication::UnicodeUTF8));
        m_btnValue1Del->setText(QApplication::translate("QResultExprWidget_ValueCal", "x", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QResultExprWidget_ValueCal", "\350\257\257\345\267\256\347\273\223\346\236\234", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QResultExprWidget_ValueCal", "\350\257\257\345\267\256\351\231\220", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QResultExprWidget_ValueCal: public Ui_QResultExprWidget_ValueCal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTEXPRWIDGET_VALUECAL_H
