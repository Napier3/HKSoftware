/********************************************************************************
** Form generated from reading UI file 'DistanceSearchBatchAddMultDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCESEARCHBATCHADDMULTDLG_H
#define UI_DISTANCESEARCHBATCHADDMULTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QDistanceSearchBatchAddMultDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *m_tableWidget;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *QDistanceSearchBatchAddMultDlg)
    {
        if (QDistanceSearchBatchAddMultDlg->objectName().isEmpty())
            QDistanceSearchBatchAddMultDlg->setObjectName(QString::fromUtf8("QDistanceSearchBatchAddMultDlg"));
        QDistanceSearchBatchAddMultDlg->resize(850, 418);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QDistanceSearchBatchAddMultDlg->sizePolicy().hasHeightForWidth());
        QDistanceSearchBatchAddMultDlg->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(QDistanceSearchBatchAddMultDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_tableWidget = new QTableWidget(QDistanceSearchBatchAddMultDlg);
        if (m_tableWidget->columnCount() < 4)
            m_tableWidget->setColumnCount(4);
        if (m_tableWidget->rowCount() < 11)
            m_tableWidget->setRowCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 1, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 2, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 3, __qtablewidgetitem2);
        m_tableWidget->setObjectName(QString::fromUtf8("m_tableWidget"));
        m_tableWidget->setRowCount(11);
        m_tableWidget->setColumnCount(4);
        m_tableWidget->horizontalHeader()->setVisible(false);
        m_tableWidget->horizontalHeader()->setStretchLastSection(true);
        m_tableWidget->verticalHeader()->setVisible(false);
        m_tableWidget->verticalHeader()->setStretchLastSection(true);

        verticalLayout_2->addWidget(m_tableWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 10);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        m_btnOk = new QPushButton(QDistanceSearchBatchAddMultDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(m_btnOk);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        m_btnCancel = new QPushButton(QDistanceSearchBatchAddMultDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy1.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(m_btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(QDistanceSearchBatchAddMultDlg);

        QMetaObject::connectSlotsByName(QDistanceSearchBatchAddMultDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceSearchBatchAddMultDlg)
    {
        QDistanceSearchBatchAddMultDlg->setWindowTitle(QApplication::translate("QDistanceSearchBatchAddMultDlg", "\346\211\271\351\207\217\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = m_tableWidget->isSortingEnabled();
        m_tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = m_tableWidget->item(0, 1);
        ___qtablewidgetitem->setText(QApplication::translate("QDistanceSearchBatchAddMultDlg", "\345\214\272\346\256\265", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = m_tableWidget->item(0, 2);
        ___qtablewidgetitem1->setText(QApplication::translate("QDistanceSearchBatchAddMultDlg", "\345\212\250\344\275\234\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = m_tableWidget->item(0, 3);
        ___qtablewidgetitem2->setText(QApplication::translate("QDistanceSearchBatchAddMultDlg", "\346\225\205\351\232\234\347\233\270\345\210\253", 0, QApplication::UnicodeUTF8));
        m_tableWidget->setSortingEnabled(__sortingEnabled);

        m_btnOk->setText(QApplication::translate("QDistanceSearchBatchAddMultDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDistanceSearchBatchAddMultDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceSearchBatchAddMultDlg: public Ui_QDistanceSearchBatchAddMultDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCESEARCHBATCHADDMULTDLG_H
