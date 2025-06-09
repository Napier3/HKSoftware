/********************************************************************************
** Form generated from reading UI file 'ResultExprDlg_Reports.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTEXPRDLG_REPORTS_H
#define UI_RESULTEXPRDLG_REPORTS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QResultExprDlg_Reports
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *m_layoutGrid;
    QTreeWidget *m_treeReport;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;

    void setupUi(QDialog *QResultExprDlg_Reports)
    {
        if (QResultExprDlg_Reports->objectName().isEmpty())
            QResultExprDlg_Reports->setObjectName(QString::fromUtf8("QResultExprDlg_Reports"));
        QResultExprDlg_Reports->resize(400, 300);
        verticalLayout = new QVBoxLayout(QResultExprDlg_Reports);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_layoutGrid = new QGridLayout();
        m_layoutGrid->setObjectName(QString::fromUtf8("m_layoutGrid"));
        m_treeReport = new QTreeWidget(QResultExprDlg_Reports);
        m_treeReport->setObjectName(QString::fromUtf8("m_treeReport"));

        m_layoutGrid->addWidget(m_treeReport, 0, 0, 1, 1);


        verticalLayout->addLayout(m_layoutGrid);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btnOK = new QPushButton(QResultExprDlg_Reports);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QResultExprDlg_Reports);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QResultExprDlg_Reports);

        QMetaObject::connectSlotsByName(QResultExprDlg_Reports);
    } // setupUi

    void retranslateUi(QDialog *QResultExprDlg_Reports)
    {
        QResultExprDlg_Reports->setWindowTitle(QApplication::translate("QResultExprDlg_Reports", "Dialog", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = m_treeReport->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("QResultExprDlg_Reports", "\346\212\245\345\221\212", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QResultExprDlg_Reports", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QResultExprDlg_Reports", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QResultExprDlg_Reports: public Ui_QResultExprDlg_Reports {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTEXPRDLG_REPORTS_H
