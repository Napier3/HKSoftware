/********************************************************************************
** Form generated from reading UI file 'ResultExprDlg_Data.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTEXPRDLG_DATA_H
#define UI_RESULTEXPRDLG_DATA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QResultExprDlg_Data
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *m_layoutTop;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *m_layoutGrid;
    QTabWidget *m_tabWidget;
    QWidget *tab_5;
    QGridLayout *gridLayout_5;
    QLineEdit *m_editValue;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *m_treeDataset;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QWidget *tab_3;
    QGridLayout *gridLayout_3;
    QWidget *tab_4;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_btnChangeReport;
    QLabel *m_txtPathLabel;
    QLabel *m_txtPath;
    QSpacerItem *m_spacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;

    void setupUi(QDialog *QResultExprDlg_Data)
    {
        if (QResultExprDlg_Data->objectName().isEmpty())
            QResultExprDlg_Data->setObjectName(QString::fromUtf8("QResultExprDlg_Data"));
        QResultExprDlg_Data->resize(800, 600);
        verticalLayout = new QVBoxLayout(QResultExprDlg_Data);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_layoutTop = new QHBoxLayout();
        m_layoutTop->setObjectName(QString::fromUtf8("m_layoutTop"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_layoutTop->addItem(horizontalSpacer);


        verticalLayout->addLayout(m_layoutTop);

        m_layoutGrid = new QVBoxLayout();
        m_layoutGrid->setObjectName(QString::fromUtf8("m_layoutGrid"));
        m_tabWidget = new QTabWidget(QResultExprDlg_Data);
        m_tabWidget->setObjectName(QString::fromUtf8("m_tabWidget"));
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_5 = new QGridLayout(tab_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_editValue = new QLineEdit(tab_5);
        m_editValue->setObjectName(QString::fromUtf8("m_editValue"));

        gridLayout_5->addWidget(m_editValue, 0, 0, 1, 1);

        m_tabWidget->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_treeDataset = new QTreeWidget(tab);
        m_treeDataset->setObjectName(QString::fromUtf8("m_treeDataset"));
        m_treeDataset->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_2->addWidget(m_treeDataset);

        m_tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_3 = new QGridLayout(tab_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_4 = new QGridLayout(tab_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_btnChangeReport = new QPushButton(tab_4);
        m_btnChangeReport->setObjectName(QString::fromUtf8("m_btnChangeReport"));

        horizontalLayout_3->addWidget(m_btnChangeReport);

        m_txtPathLabel = new QLabel(tab_4);
        m_txtPathLabel->setObjectName(QString::fromUtf8("m_txtPathLabel"));

        horizontalLayout_3->addWidget(m_txtPathLabel);

        m_txtPath = new QLabel(tab_4);
        m_txtPath->setObjectName(QString::fromUtf8("m_txtPath"));

        horizontalLayout_3->addWidget(m_txtPath);

        m_spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(m_spacer);


        gridLayout_4->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        m_tabWidget->addTab(tab_4, QString());

        m_layoutGrid->addWidget(m_tabWidget);


        verticalLayout->addLayout(m_layoutGrid);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btnOK = new QPushButton(QResultExprDlg_Data);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QResultExprDlg_Data);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QResultExprDlg_Data);

        m_tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(QResultExprDlg_Data);
    } // setupUi

    void retranslateUi(QDialog *QResultExprDlg_Data)
    {
        QResultExprDlg_Data->setWindowTitle(QApplication::translate("QResultExprDlg_Data", "Dialog", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab_5), QApplication::translate("QResultExprDlg_Data", "\346\225\260\345\200\274", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = m_treeDataset->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("QResultExprDlg_Data", "\346\225\260\346\215\256\351\233\206", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab), QApplication::translate("QResultExprDlg_Data", "\346\225\260\346\215\256\351\233\206", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab_2), QApplication::translate("QResultExprDlg_Data", "\347\263\273\347\273\237\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab_3), QApplication::translate("QResultExprDlg_Data", "\345\205\250\345\261\200\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_btnChangeReport->setText(QApplication::translate("QResultExprDlg_Data", "\345\210\207\346\215\242\346\212\245\345\221\212", 0, QApplication::UnicodeUTF8));
        m_txtPathLabel->setText(QApplication::translate("QResultExprDlg_Data", "\350\267\257\345\276\204:", 0, QApplication::UnicodeUTF8));
        m_txtPath->setText(QString());
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab_4), QApplication::translate("QResultExprDlg_Data", "\346\212\245\345\221\212\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QResultExprDlg_Data", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QResultExprDlg_Data", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QResultExprDlg_Data: public Ui_QResultExprDlg_Data {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTEXPRDLG_DATA_H
