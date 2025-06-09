/********************************************************************************
** Form generated from reading UI file 'QZKFeatureAddDig.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QZKFEATUREADDDIG_H
#define UI_QZKFEATUREADDDIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QZKFeatureAddDig
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QGridLayout *gridLayout_7;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pbn_Ok;
    QPushButton *pbn_Cancel;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *QZKFeatureAddDig)
    {
        if (QZKFeatureAddDig->objectName().isEmpty())
            QZKFeatureAddDig->setObjectName(QString::fromUtf8("QZKFeatureAddDig"));
        QZKFeatureAddDig->resize(351, 300);
        verticalLayout = new QVBoxLayout(QZKFeatureAddDig);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget = new QTreeWidget(QZKFeatureAddDig);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setRootIsDecorated(true);
        treeWidget->setAllColumnsShowFocus(true);
        treeWidget->setColumnCount(1);
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalSpacer_4 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        pbn_Ok = new QPushButton(QZKFeatureAddDig);
        pbn_Ok->setObjectName(QString::fromUtf8("pbn_Ok"));
        pbn_Ok->setAutoDefault(false);

        gridLayout_7->addWidget(pbn_Ok, 0, 1, 1, 1);

        pbn_Cancel = new QPushButton(QZKFeatureAddDig);
        pbn_Cancel->setObjectName(QString::fromUtf8("pbn_Cancel"));
        pbn_Cancel->setAutoDefault(false);

        gridLayout_7->addWidget(pbn_Cancel, 0, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_5, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_7);


        retranslateUi(QZKFeatureAddDig);

        QMetaObject::connectSlotsByName(QZKFeatureAddDig);
    } // setupUi

    void retranslateUi(QWidget *QZKFeatureAddDig)
    {
        QZKFeatureAddDig->setWindowTitle(QApplication::translate("QZKFeatureAddDig", "QZKFeatureAddDig", 0, QApplication::UnicodeUTF8));
        pbn_Ok->setText(QApplication::translate("QZKFeatureAddDig", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pbn_Cancel->setText(QApplication::translate("QZKFeatureAddDig", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QZKFeatureAddDig: public Ui_QZKFeatureAddDig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QZKFEATUREADDDIG_H
