/********************************************************************************
** Form generated from reading UI file 'SttCustomSetDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTCUSTOMSETDLG_H
#define UI_STTCUSTOMSETDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include "SttCustomSetTree.h"

QT_BEGIN_NAMESPACE

class Ui_QSttCustomSetDlg
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSttCustomSetTree *m_pMenuTreeCtrl;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QToolButton *BtnRemove;
    QSpacerItem *verticalSpacer_5;
    QToolButton *BtnInsertBefore;
    QSpacerItem *verticalSpacer_4;
    QToolButton *BtnInsertAfter;
    QSpacerItem *verticalSpacer_2;
    QToolButton *BtnAddBar;
    QSpacerItem *verticalSpacer;
    QSttCustomSetTree *m_pFloatBarTreeCtrl;
    QHBoxLayout *_2;
    QSpacerItem *spacerItem;
    QPushButton *BtnCancel;

    void setupUi(QDialog *QSttCustomSetDlg)
    {
        if (QSttCustomSetDlg->objectName().isEmpty())
            QSttCustomSetDlg->setObjectName(QString::fromUtf8("QSttCustomSetDlg"));
        QSttCustomSetDlg->setWindowModality(Qt::WindowModal);
        QSttCustomSetDlg->resize(645, 391);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QSttCustomSetDlg->sizePolicy().hasHeightForWidth());
        QSttCustomSetDlg->setSizePolicy(sizePolicy);
        QSttCustomSetDlg->setMinimumSize(QSize(0, 30));
        QSttCustomSetDlg->setMaximumSize(QSize(645, 16777215));
        QSttCustomSetDlg->setSizeGripEnabled(false);
        QSttCustomSetDlg->setModal(false);
        horizontalLayout_2 = new QHBoxLayout(QSttCustomSetDlg);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pMenuTreeCtrl = new QSttCustomSetTree(QSttCustomSetDlg);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        m_pMenuTreeCtrl->setHeaderItem(__qtreewidgetitem);
        m_pMenuTreeCtrl->setObjectName(QString::fromUtf8("m_pMenuTreeCtrl"));

        horizontalLayout->addWidget(m_pMenuTreeCtrl);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        BtnRemove = new QToolButton(QSttCustomSetDlg);
        BtnRemove->setObjectName(QString::fromUtf8("BtnRemove"));
        BtnRemove->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        BtnRemove->setFont(font);

        verticalLayout->addWidget(BtnRemove);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        BtnInsertBefore = new QToolButton(QSttCustomSetDlg);
        BtnInsertBefore->setObjectName(QString::fromUtf8("BtnInsertBefore"));
        BtnInsertBefore->setMinimumSize(QSize(0, 30));
        BtnInsertBefore->setFont(font);
        BtnInsertBefore->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(BtnInsertBefore);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        BtnInsertAfter = new QToolButton(QSttCustomSetDlg);
        BtnInsertAfter->setObjectName(QString::fromUtf8("BtnInsertAfter"));
        BtnInsertAfter->setMinimumSize(QSize(0, 30));
        BtnInsertAfter->setFont(font);

        verticalLayout->addWidget(BtnInsertAfter);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        BtnAddBar = new QToolButton(QSttCustomSetDlg);
        BtnAddBar->setObjectName(QString::fromUtf8("BtnAddBar"));
        sizePolicy.setHeightForWidth(BtnAddBar->sizePolicy().hasHeightForWidth());
        BtnAddBar->setSizePolicy(sizePolicy);
        BtnAddBar->setMinimumSize(QSize(0, 30));
        BtnAddBar->setFont(font);
        BtnAddBar->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(BtnAddBar);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        m_pFloatBarTreeCtrl = new QSttCustomSetTree(QSttCustomSetDlg);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        m_pFloatBarTreeCtrl->setHeaderItem(__qtreewidgetitem1);
        m_pFloatBarTreeCtrl->setObjectName(QString::fromUtf8("m_pFloatBarTreeCtrl"));

        horizontalLayout->addWidget(m_pFloatBarTreeCtrl);


        verticalLayout_2->addLayout(horizontalLayout);

        _2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        _2->setSpacing(6);
#endif
        _2->setContentsMargins(0, 0, 0, 0);
        _2->setObjectName(QString::fromUtf8("_2"));
        spacerItem = new QSpacerItem(111, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _2->addItem(spacerItem);

        BtnCancel = new QPushButton(QSttCustomSetDlg);
        BtnCancel->setObjectName(QString::fromUtf8("BtnCancel"));

        _2->addWidget(BtnCancel);


        verticalLayout_2->addLayout(_2);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(QSttCustomSetDlg);
        QObject::connect(BtnCancel, SIGNAL(clicked()), QSttCustomSetDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(QSttCustomSetDlg);
    } // setupUi

    void retranslateUi(QDialog *QSttCustomSetDlg)
    {
        QSttCustomSetDlg->setWindowTitle(QApplication::translate("QSttCustomSetDlg", "\350\207\252\345\256\232\344\271\211\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        BtnRemove->setText(QApplication::translate("QSttCustomSetDlg", " \347\247\273    \351\231\244 ", 0, QApplication::UnicodeUTF8));
        BtnInsertBefore->setText(QApplication::translate("QSttCustomSetDlg", "\345\211\215\351\235\242\346\217\222\345\205\245", 0, QApplication::UnicodeUTF8));
        BtnInsertAfter->setText(QApplication::translate("QSttCustomSetDlg", "\345\220\216\351\235\242\346\217\222\345\205\245", 0, QApplication::UnicodeUTF8));
        BtnAddBar->setText(QApplication::translate("QSttCustomSetDlg", "\346\234\253\345\260\276\346\217\222\345\205\245", 0, QApplication::UnicodeUTF8));
        BtnCancel->setText(QApplication::translate("QSttCustomSetDlg", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        BtnCancel->setShortcut(QApplication::translate("QSttCustomSetDlg", "Ctrl+S", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttCustomSetDlg: public Ui_QSttCustomSetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTCUSTOMSETDLG_H
