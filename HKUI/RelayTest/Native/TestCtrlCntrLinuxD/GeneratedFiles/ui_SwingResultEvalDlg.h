/********************************************************************************
** Form generated from reading UI file 'SwingResultEvalDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWINGRESULTEVALDLG_H
#define UI_SWINGRESULTEVALDLG_H

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
#include "../../../Module/UI/Swing/SwingResultEvalGrid.h"

QT_BEGIN_NAMESPACE

class Ui_QSwingResultEvalDlg
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QSwingResultEvalGrid *m_tableWidget;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *QSwingResultEvalDlg)
    {
        if (QSwingResultEvalDlg->objectName().isEmpty())
            QSwingResultEvalDlg->setObjectName(QString::fromUtf8("QSwingResultEvalDlg"));
        QSwingResultEvalDlg->resize(802, 142);
        horizontalLayout_2 = new QHBoxLayout(QSwingResultEvalDlg);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        m_tableWidget = new QSwingResultEvalGrid(QSwingResultEvalDlg);
        if (m_tableWidget->columnCount() < 6)
            m_tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        m_tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (m_tableWidget->rowCount() < 1)
            m_tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 0, __qtablewidgetitem6);
        m_tableWidget->setObjectName(QString::fromUtf8("m_tableWidget"));
        m_tableWidget->setMinimumSize(QSize(440, 0));
        m_tableWidget->setRowCount(1);
        m_tableWidget->setColumnCount(6);
        m_tableWidget->horizontalHeader()->setStretchLastSection(true);
        m_tableWidget->verticalHeader()->setVisible(false);
        m_tableWidget->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(m_tableWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnOk = new QPushButton(QSwingResultEvalDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_btnOk);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        m_btnCancel = new QPushButton(QSwingResultEvalDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSwingResultEvalDlg);

        QMetaObject::connectSlotsByName(QSwingResultEvalDlg);
    } // setupUi

    void retranslateUi(QDialog *QSwingResultEvalDlg)
    {
        QSwingResultEvalDlg->setWindowTitle(QApplication::translate("QSwingResultEvalDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = m_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QSwingResultEvalDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = m_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QSwingResultEvalDlg", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = m_tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QSwingResultEvalDlg", "\350\257\257\345\267\256\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = m_tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QSwingResultEvalDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(\357\274\205)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = m_tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QSwingResultEvalDlg", "\347\273\235\345\257\271\350\257\257\345\267\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = m_tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("QSwingResultEvalDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(-)", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = m_tableWidget->isSortingEnabled();
        m_tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = m_tableWidget->item(0, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("QSwingResultEvalDlg", "\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_tableWidget->setSortingEnabled(__sortingEnabled);

        m_btnOk->setText(QApplication::translate("QSwingResultEvalDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QSwingResultEvalDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSwingResultEvalDlg: public Ui_QSwingResultEvalDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWINGRESULTEVALDLG_H
