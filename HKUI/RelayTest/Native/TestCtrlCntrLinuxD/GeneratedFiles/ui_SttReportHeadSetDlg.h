/********************************************************************************
** Form generated from reading UI file 'SttReportHeadSetDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTREPORTHEADSETDLG_H
#define UI_STTREPORTHEADSETDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttReportHeadSetDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *m_pVBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *QSttReportHeadSetDlg)
    {
        if (QSttReportHeadSetDlg->objectName().isEmpty())
            QSttReportHeadSetDlg->setObjectName(QString::fromUtf8("QSttReportHeadSetDlg"));
        QSttReportHeadSetDlg->resize(528, 269);
        horizontalLayout = new QHBoxLayout(QSttReportHeadSetDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeWidget = new QTreeWidget(QSttReportHeadSetDlg);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QFont font;
        font.setPointSize(14);
        treeWidget->setFont(font);
        treeWidget->setHeaderHidden(false);

        horizontalLayout->addWidget(treeWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pVBox = new QGridLayout();
        m_pVBox->setObjectName(QString::fromUtf8("m_pVBox"));

        verticalLayout->addLayout(m_pVBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnOK = new QPushButton(QSttReportHeadSetDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setFont(font);

        horizontalLayout_2->addWidget(btnOK);

        btnCancel = new QPushButton(QSttReportHeadSetDlg);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setFont(font);

        horizontalLayout_2->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QSttReportHeadSetDlg);

        QMetaObject::connectSlotsByName(QSttReportHeadSetDlg);
    } // setupUi

    void retranslateUi(QDialog *QSttReportHeadSetDlg)
    {
        QSttReportHeadSetDlg->setWindowTitle(QApplication::translate("QSttReportHeadSetDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("QSttReportHeadSetDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("QSttReportHeadSetDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttReportHeadSetDlg: public Ui_QSttReportHeadSetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTREPORTHEADSETDLG_H
