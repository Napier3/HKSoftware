/********************************************************************************
** Form generated from reading UI file 'TestMacroToolDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTMACROTOOLDLG_H
#define UI_TESTMACROTOOLDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTestMacroToolDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *m_layoutTest;
    QVBoxLayout *m_layoutLeft;
    QScrollArea *scrollArea;
    QWidget *m_tableTest;
    QGridLayout *gridLayout;
    QVBoxLayout *m_layoutRight;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidget;
    QGridLayout *gridLayout_2;
    QTreeWidget *m_treeTest;
    QHBoxLayout *m_layoutAdd;
    QPushButton *m_btnAddChild;
    QPushButton *m_btnAddBefore;
    QPushButton *m_btnAddAfter;
    QLabel *m_txtTimes;
    QLineEdit *m_editTimes;
    QLineEdit *m_editName;
    QCheckBox *m_chkRptTitle;
    QLabel *m_txtTitleLevel;
    QComboBox *m_cmbTitleLevel;
    QPushButton *m_btnClose;

    void setupUi(QDialog *QTestMacroToolDlg)
    {
        if (QTestMacroToolDlg->objectName().isEmpty())
            QTestMacroToolDlg->setObjectName(QString::fromUtf8("QTestMacroToolDlg"));
        QTestMacroToolDlg->resize(915, 668);
        verticalLayout = new QVBoxLayout(QTestMacroToolDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_layoutTest = new QHBoxLayout();
        m_layoutTest->setObjectName(QString::fromUtf8("m_layoutTest"));
        m_layoutLeft = new QVBoxLayout();
        m_layoutLeft->setObjectName(QString::fromUtf8("m_layoutLeft"));
        scrollArea = new QScrollArea(QTestMacroToolDlg);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        m_tableTest = new QWidget();
        m_tableTest->setObjectName(QString::fromUtf8("m_tableTest"));
        m_tableTest->setGeometry(QRect(0, 0, 659, 603));
        m_tableTest->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(m_tableTest);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea->setWidget(m_tableTest);

        m_layoutLeft->addWidget(scrollArea);


        m_layoutTest->addLayout(m_layoutLeft);

        m_layoutRight = new QVBoxLayout();
        m_layoutRight->setObjectName(QString::fromUtf8("m_layoutRight"));
        scrollArea_2 = new QScrollArea(QTestMacroToolDlg);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidget = new QWidget();
        scrollAreaWidget->setObjectName(QString::fromUtf8("scrollAreaWidget"));
        scrollAreaWidget->setGeometry(QRect(0, 0, 217, 603));
        gridLayout_2 = new QGridLayout(scrollAreaWidget);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_treeTest = new QTreeWidget(scrollAreaWidget);
        m_treeTest->setObjectName(QString::fromUtf8("m_treeTest"));
        m_treeTest->setSelectionMode(QAbstractItemView::NoSelection);
        m_treeTest->setSelectionBehavior(QAbstractItemView::SelectItems);
        m_treeTest->setColumnCount(1);
        m_treeTest->header()->setVisible(false);

        gridLayout_2->addWidget(m_treeTest, 0, 1, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidget);

        m_layoutRight->addWidget(scrollArea_2);


        m_layoutTest->addLayout(m_layoutRight);

        m_layoutTest->setStretch(0, 3);
        m_layoutTest->setStretch(1, 1);

        verticalLayout->addLayout(m_layoutTest);

        m_layoutAdd = new QHBoxLayout();
        m_layoutAdd->setObjectName(QString::fromUtf8("m_layoutAdd"));
        m_btnAddChild = new QPushButton(QTestMacroToolDlg);
        m_btnAddChild->setObjectName(QString::fromUtf8("m_btnAddChild"));
        m_btnAddChild->setAutoDefault(false);

        m_layoutAdd->addWidget(m_btnAddChild);

        m_btnAddBefore = new QPushButton(QTestMacroToolDlg);
        m_btnAddBefore->setObjectName(QString::fromUtf8("m_btnAddBefore"));
        m_btnAddBefore->setEnabled(false);
        m_btnAddBefore->setAutoDefault(false);

        m_layoutAdd->addWidget(m_btnAddBefore);

        m_btnAddAfter = new QPushButton(QTestMacroToolDlg);
        m_btnAddAfter->setObjectName(QString::fromUtf8("m_btnAddAfter"));
        m_btnAddAfter->setEnabled(false);
        m_btnAddAfter->setAutoDefault(false);

        m_layoutAdd->addWidget(m_btnAddAfter);

        m_txtTimes = new QLabel(QTestMacroToolDlg);
        m_txtTimes->setObjectName(QString::fromUtf8("m_txtTimes"));
        m_txtTimes->setMaximumSize(QSize(70, 16777215));

        m_layoutAdd->addWidget(m_txtTimes);

        m_editTimes = new QLineEdit(QTestMacroToolDlg);
        m_editTimes->setObjectName(QString::fromUtf8("m_editTimes"));
        m_editTimes->setMaximumSize(QSize(70, 16777215));
        m_editTimes->setEchoMode(QLineEdit::Normal);

        m_layoutAdd->addWidget(m_editTimes);

        m_editName = new QLineEdit(QTestMacroToolDlg);
        m_editName->setObjectName(QString::fromUtf8("m_editName"));
        m_editName->setMaximumSize(QSize(150, 16777215));

        m_layoutAdd->addWidget(m_editName);

        m_chkRptTitle = new QCheckBox(QTestMacroToolDlg);
        m_chkRptTitle->setObjectName(QString::fromUtf8("m_chkRptTitle"));

        m_layoutAdd->addWidget(m_chkRptTitle);

        m_txtTitleLevel = new QLabel(QTestMacroToolDlg);
        m_txtTitleLevel->setObjectName(QString::fromUtf8("m_txtTitleLevel"));

        m_layoutAdd->addWidget(m_txtTitleLevel);

        m_cmbTitleLevel = new QComboBox(QTestMacroToolDlg);
        m_cmbTitleLevel->setObjectName(QString::fromUtf8("m_cmbTitleLevel"));

        m_layoutAdd->addWidget(m_cmbTitleLevel);

        m_btnClose = new QPushButton(QTestMacroToolDlg);
        m_btnClose->setObjectName(QString::fromUtf8("m_btnClose"));
        m_btnClose->setMaximumSize(QSize(100, 16777215));

        m_layoutAdd->addWidget(m_btnClose);


        verticalLayout->addLayout(m_layoutAdd);


        retranslateUi(QTestMacroToolDlg);

        QMetaObject::connectSlotsByName(QTestMacroToolDlg);
    } // setupUi

    void retranslateUi(QDialog *QTestMacroToolDlg)
    {
        QTestMacroToolDlg->setWindowTitle(QApplication::translate("QTestMacroToolDlg", "\351\200\211\346\213\251\346\265\213\350\257\225\345\212\237\350\203\275", 0, QApplication::UnicodeUTF8));
        m_btnAddChild->setText(QApplication::translate("QTestMacroToolDlg", "\346\267\273\345\212\240\350\207\263:\345\255\220\351\241\271", 0, QApplication::UnicodeUTF8));
        m_btnAddBefore->setText(QApplication::translate("QTestMacroToolDlg", "\346\267\273\345\212\240\350\207\263:\351\241\271\344\271\213\345\211\215", 0, QApplication::UnicodeUTF8));
        m_btnAddAfter->setText(QApplication::translate("QTestMacroToolDlg", "\346\267\273\345\212\240\350\207\263:\351\241\271\344\271\213\345\220\216", 0, QApplication::UnicodeUTF8));
        m_txtTimes->setText(QApplication::translate("QTestMacroToolDlg", "\346\265\213\350\257\225\346\254\241\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        m_editTimes->setText(QApplication::translate("QTestMacroToolDlg", "1", 0, QApplication::UnicodeUTF8));
        m_chkRptTitle->setText(QApplication::translate("QTestMacroToolDlg", "\344\275\234\344\270\272Word\346\240\207\351\242\230", 0, QApplication::UnicodeUTF8));
        m_txtTitleLevel->setText(QApplication::translate("QTestMacroToolDlg", "\346\240\207\351\242\230\347\255\211\347\272\247", 0, QApplication::UnicodeUTF8));
        m_btnClose->setText(QApplication::translate("QTestMacroToolDlg", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QTestMacroToolDlg: public Ui_QTestMacroToolDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTMACROTOOLDLG_H
