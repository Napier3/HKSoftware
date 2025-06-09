/********************************************************************************
** Form generated from reading UI file 'DistanceSearchQuickAddMultDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCESEARCHQUICKADDMULTDLG_H
#define UI_DISTANCESEARCHQUICKADDMULTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QDistanceSearchQuickAddMultDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QCheckBox *m_cbAN;
    QCheckBox *m_cbCN;
    QCheckBox *m_cbAB;
    QCheckBox *m_cbBN;
    QCheckBox *m_cbBC;
    QCheckBox *m_cbABC;
    QCheckBox *m_cbCA;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *QDistanceSearchQuickAddMultDlg)
    {
        if (QDistanceSearchQuickAddMultDlg->objectName().isEmpty())
            QDistanceSearchQuickAddMultDlg->setObjectName(QString::fromUtf8("QDistanceSearchQuickAddMultDlg"));
        QDistanceSearchQuickAddMultDlg->resize(270, 300);
        horizontalLayout = new QHBoxLayout(QDistanceSearchQuickAddMultDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(20, -1, -1, -1);
        m_cbAN = new QCheckBox(QDistanceSearchQuickAddMultDlg);
        m_cbAN->setObjectName(QString::fromUtf8("m_cbAN"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_cbAN->sizePolicy().hasHeightForWidth());
        m_cbAN->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_cbAN, 0, 0, 1, 1);

        m_cbCN = new QCheckBox(QDistanceSearchQuickAddMultDlg);
        m_cbCN->setObjectName(QString::fromUtf8("m_cbCN"));
        sizePolicy.setHeightForWidth(m_cbCN->sizePolicy().hasHeightForWidth());
        m_cbCN->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_cbCN, 2, 0, 1, 1);

        m_cbAB = new QCheckBox(QDistanceSearchQuickAddMultDlg);
        m_cbAB->setObjectName(QString::fromUtf8("m_cbAB"));
        sizePolicy.setHeightForWidth(m_cbAB->sizePolicy().hasHeightForWidth());
        m_cbAB->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_cbAB, 3, 0, 1, 1);

        m_cbBN = new QCheckBox(QDistanceSearchQuickAddMultDlg);
        m_cbBN->setObjectName(QString::fromUtf8("m_cbBN"));
        sizePolicy.setHeightForWidth(m_cbBN->sizePolicy().hasHeightForWidth());
        m_cbBN->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_cbBN, 1, 0, 1, 1);

        m_cbBC = new QCheckBox(QDistanceSearchQuickAddMultDlg);
        m_cbBC->setObjectName(QString::fromUtf8("m_cbBC"));
        sizePolicy.setHeightForWidth(m_cbBC->sizePolicy().hasHeightForWidth());
        m_cbBC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_cbBC, 4, 0, 1, 1);

        m_cbABC = new QCheckBox(QDistanceSearchQuickAddMultDlg);
        m_cbABC->setObjectName(QString::fromUtf8("m_cbABC"));
        sizePolicy.setHeightForWidth(m_cbABC->sizePolicy().hasHeightForWidth());
        m_cbABC->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_cbABC, 6, 0, 1, 1);

        m_cbCA = new QCheckBox(QDistanceSearchQuickAddMultDlg);
        m_cbCA->setObjectName(QString::fromUtf8("m_cbCA"));
        sizePolicy.setHeightForWidth(m_cbCA->sizePolicy().hasHeightForWidth());
        m_cbCA->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_cbCA, 5, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 7, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        m_btnOk = new QPushButton(QDistanceSearchQuickAddMultDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(m_btnOk);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        m_btnCancel = new QPushButton(QDistanceSearchQuickAddMultDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy1.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(m_btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QDistanceSearchQuickAddMultDlg);

        QMetaObject::connectSlotsByName(QDistanceSearchQuickAddMultDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceSearchQuickAddMultDlg)
    {
        QDistanceSearchQuickAddMultDlg->setWindowTitle(QApplication::translate("QDistanceSearchQuickAddMultDlg", "\345\277\253\351\200\237\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        m_cbAN->setText(QApplication::translate("QDistanceSearchQuickAddMultDlg", "AN", 0, QApplication::UnicodeUTF8));
        m_cbCN->setText(QApplication::translate("QDistanceSearchQuickAddMultDlg", "CN", 0, QApplication::UnicodeUTF8));
        m_cbAB->setText(QApplication::translate("QDistanceSearchQuickAddMultDlg", "AB", 0, QApplication::UnicodeUTF8));
        m_cbBN->setText(QApplication::translate("QDistanceSearchQuickAddMultDlg", "BN", 0, QApplication::UnicodeUTF8));
        m_cbBC->setText(QApplication::translate("QDistanceSearchQuickAddMultDlg", "BC", 0, QApplication::UnicodeUTF8));
        m_cbABC->setText(QApplication::translate("QDistanceSearchQuickAddMultDlg", "ABC", 0, QApplication::UnicodeUTF8));
        m_cbCA->setText(QApplication::translate("QDistanceSearchQuickAddMultDlg", "CA", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QDistanceSearchQuickAddMultDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDistanceSearchQuickAddMultDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceSearchQuickAddMultDlg: public Ui_QDistanceSearchQuickAddMultDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCESEARCHQUICKADDMULTDLG_H
