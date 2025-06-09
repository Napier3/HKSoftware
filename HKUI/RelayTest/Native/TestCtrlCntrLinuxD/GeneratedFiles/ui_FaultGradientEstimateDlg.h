/********************************************************************************
** Form generated from reading UI file 'FaultGradientEstimateDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAULTGRADIENTESTIMATEDLG_H
#define UI_FAULTGRADIENTESTIMATEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "../FaultGradient/FaultGradientEstimateDlg.h"

QT_BEGIN_NAMESPACE

class Ui_CFaultGradientEstimateDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFaultGradientEstimateGrid *tableWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *CFaultGradientEstimateDlg)
    {
        if (CFaultGradientEstimateDlg->objectName().isEmpty())
            CFaultGradientEstimateDlg->setObjectName(QString::fromUtf8("CFaultGradientEstimateDlg"));
        CFaultGradientEstimateDlg->resize(666, 410);
        verticalLayout = new QVBoxLayout(CFaultGradientEstimateDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QFaultGradientEstimateGrid(CFaultGradientEstimateDlg);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        if (tableWidget->rowCount() < 7)
            tableWidget->setRowCount(7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
        tableWidget->setRowCount(7);
        tableWidget->setColumnCount(5);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(CFaultGradientEstimateDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));

        horizontalLayout->addWidget(btnOk);

        btnCancel = new QPushButton(CFaultGradientEstimateDlg);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CFaultGradientEstimateDlg);

        QMetaObject::connectSlotsByName(CFaultGradientEstimateDlg);
    } // setupUi

    void retranslateUi(QDialog *CFaultGradientEstimateDlg)
    {
        CFaultGradientEstimateDlg->setWindowTitle(QApplication::translate("CFaultGradientEstimateDlg", "CFaultGradientEstimateDlg", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("CFaultGradientEstimateDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("CFaultGradientEstimateDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CFaultGradientEstimateDlg: public Ui_CFaultGradientEstimateDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAULTGRADIENTESTIMATEDLG_H
