/********************************************************************************
** Form generated from reading UI file 'SttReplayParaSetWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTREPLAYPARASETWIDGET_H
#define UI_STTREPLAYPARASETWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>
#include "../Controls/SttTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SttReplayParaSetWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSttTabWidget *tabWidget;
    QWidget *tab_5;
    QGridLayout *gridLayout_10;
    QTableWidget *tableWidgetIns;
    QTableWidget *tableWidget;

    void setupUi(QWidget *SttReplayParaSetWidget)
    {
        if (SttReplayParaSetWidget->objectName().isEmpty())
            SttReplayParaSetWidget->setObjectName(QString::fromUtf8("SttReplayParaSetWidget"));
        SttReplayParaSetWidget->resize(721, 409);
        SttReplayParaSetWidget->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(SttReplayParaSetWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QSttTabWidget(SttReplayParaSetWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_10 = new QGridLayout(tab_5);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        tableWidgetIns = new QTableWidget(tab_5);
        if (tableWidgetIns->columnCount() < 2)
            tableWidgetIns->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetIns->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetIns->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetIns->setObjectName(QString::fromUtf8("tableWidgetIns"));
        tableWidgetIns->setEnabled(true);

        gridLayout_10->addWidget(tableWidgetIns, 0, 1, 1, 1);

        tableWidget = new QTableWidget(tab_5);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(true);

        gridLayout_10->addWidget(tableWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(SttReplayParaSetWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SttReplayParaSetWidget);
    } // setupUi

    void retranslateUi(QWidget *SttReplayParaSetWidget)
    {
        SttReplayParaSetWidget->setWindowTitle(QApplication::translate("SttReplayParaSetWidget", "Form", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetIns->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SttReplayParaSetWidget", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetIns->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SttReplayParaSetWidget", "\347\236\254\346\227\266\345\200\274", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("SttReplayParaSetWidget", "\351\207\207\346\240\267\347\216\207", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("SttReplayParaSetWidget", "\351\207\207\346\240\267\346\225\260", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("SttReplayParaSetWidget", "\351\207\207\346\240\267\347\216\207", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SttReplayParaSetWidget: public Ui_SttReplayParaSetWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTREPLAYPARASETWIDGET_H
