/********************************************************************************
** Form generated from reading UI file 'CharLibWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARLIBWIDGET_H
#define UI_CHARLIBWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCharLibWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *m_layoutLeft;
    QTableWidget *tableWidget_ZK;
    QTableWidget *tableWidget_Info;
    QTableWidget *tableWidget_Info2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_btnAdd;
    QPushButton *m_btnDel;
    QGridLayout *m_layoutRight;
    QTabWidget *m_wgtCharLib;

    void setupUi(QWidget *QCharLibWidget)
    {
        if (QCharLibWidget->objectName().isEmpty())
            QCharLibWidget->setObjectName(QString::fromUtf8("QCharLibWidget"));
        QCharLibWidget->resize(998, 792);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        QCharLibWidget->setFont(font);
        QCharLibWidget->setFocusPolicy(Qt::TabFocus);
        horizontalLayout = new QHBoxLayout(QCharLibWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_layoutLeft = new QVBoxLayout();
        m_layoutLeft->setSpacing(6);
        m_layoutLeft->setObjectName(QString::fromUtf8("m_layoutLeft"));
        tableWidget_ZK = new QTableWidget(QCharLibWidget);
        tableWidget_ZK->setObjectName(QString::fromUtf8("tableWidget_ZK"));

        m_layoutLeft->addWidget(tableWidget_ZK);

        tableWidget_Info = new QTableWidget(QCharLibWidget);
        tableWidget_Info->setObjectName(QString::fromUtf8("tableWidget_Info"));

        m_layoutLeft->addWidget(tableWidget_Info);

        tableWidget_Info2 = new QTableWidget(QCharLibWidget);
        tableWidget_Info2->setObjectName(QString::fromUtf8("tableWidget_Info2"));

        m_layoutLeft->addWidget(tableWidget_Info2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_btnAdd = new QPushButton(QCharLibWidget);
        m_btnAdd->setObjectName(QString::fromUtf8("m_btnAdd"));

        horizontalLayout_2->addWidget(m_btnAdd);

        m_btnDel = new QPushButton(QCharLibWidget);
        m_btnDel->setObjectName(QString::fromUtf8("m_btnDel"));

        horizontalLayout_2->addWidget(m_btnDel);


        m_layoutLeft->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(m_layoutLeft);

        m_layoutRight = new QGridLayout();
        m_layoutRight->setSpacing(6);
        m_layoutRight->setObjectName(QString::fromUtf8("m_layoutRight"));
        m_wgtCharLib = new QTabWidget(QCharLibWidget);
        m_wgtCharLib->setObjectName(QString::fromUtf8("m_wgtCharLib"));

        m_layoutRight->addWidget(m_wgtCharLib, 0, 0, 1, 1);


        horizontalLayout->addLayout(m_layoutRight);

        horizontalLayout->setStretch(0, 6);
        horizontalLayout->setStretch(1, 7);

        retranslateUi(QCharLibWidget);

        m_wgtCharLib->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(QCharLibWidget);
    } // setupUi

    void retranslateUi(QWidget *QCharLibWidget)
    {
        QCharLibWidget->setWindowTitle(QApplication::translate("QCharLibWidget", "ParaSetWidget", 0, QApplication::UnicodeUTF8));
        m_btnAdd->setText(QApplication::translate("QCharLibWidget", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        m_btnDel->setText(QApplication::translate("QCharLibWidget", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCharLibWidget: public Ui_QCharLibWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARLIBWIDGET_H
