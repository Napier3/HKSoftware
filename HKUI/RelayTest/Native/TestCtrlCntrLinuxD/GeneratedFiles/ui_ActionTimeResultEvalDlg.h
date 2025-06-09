/********************************************************************************
** Form generated from reading UI file 'ActionTimeResultEvalDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIONTIMERESULTEVALDLG_H
#define UI_ACTIONTIMERESULTEVALDLG_H

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

class Ui_QActionTimeResultEvalDlg
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QTableWidget *m_tableWidget;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *QActionTimeResultEvalDlg)
    {
        if (QActionTimeResultEvalDlg->objectName().isEmpty())
            QActionTimeResultEvalDlg->setObjectName(QString::fromUtf8("QActionTimeResultEvalDlg"));
        QActionTimeResultEvalDlg->resize(540, 200);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QActionTimeResultEvalDlg->sizePolicy().hasHeightForWidth());
        QActionTimeResultEvalDlg->setSizePolicy(sizePolicy);
        QActionTimeResultEvalDlg->setMinimumSize(QSize(540, 200));
        QActionTimeResultEvalDlg->setMaximumSize(QSize(540, 200));
        verticalLayout = new QVBoxLayout(QActionTimeResultEvalDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        m_tableWidget = new QTableWidget(QActionTimeResultEvalDlg);
        if (m_tableWidget->columnCount() < 4)
            m_tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (m_tableWidget->rowCount() < 1)
            m_tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        m_tableWidget->setItem(0, 0, __qtablewidgetitem4);
        m_tableWidget->setObjectName(QString::fromUtf8("m_tableWidget"));
        m_tableWidget->setRowCount(1);
        m_tableWidget->horizontalHeader()->setStretchLastSection(true);
        m_tableWidget->verticalHeader()->setVisible(false);
        m_tableWidget->verticalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(m_tableWidget);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnOk = new QPushButton(QActionTimeResultEvalDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        sizePolicy.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_btnOk);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        m_btnCancel = new QPushButton(QActionTimeResultEvalDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(QActionTimeResultEvalDlg);

        QMetaObject::connectSlotsByName(QActionTimeResultEvalDlg);
    } // setupUi

    void retranslateUi(QDialog *QActionTimeResultEvalDlg)
    {
        QActionTimeResultEvalDlg->setWindowTitle(QApplication::translate("QActionTimeResultEvalDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = m_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QActionTimeResultEvalDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = m_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QActionTimeResultEvalDlg", "\350\257\257\345\267\256\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = m_tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QActionTimeResultEvalDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(\357\274\205)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = m_tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QActionTimeResultEvalDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = m_tableWidget->isSortingEnabled();
        m_tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem4 = m_tableWidget->item(0, 0);
        ___qtablewidgetitem4->setText(QApplication::translate("QActionTimeResultEvalDlg", "\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_tableWidget->setSortingEnabled(__sortingEnabled);

        m_btnOk->setText(QApplication::translate("QActionTimeResultEvalDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QActionTimeResultEvalDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QActionTimeResultEvalDlg: public Ui_QActionTimeResultEvalDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIONTIMERESULTEVALDLG_H
