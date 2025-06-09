/********************************************************************************
** Form generated from reading UI file 'SwingSysDiagramWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWINGSYSDIAGRAMWIDGET_H
#define UI_SWINGSYSDIAGRAMWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSwingSysDiagramWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *m_labDiagram;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QTableWidget *m_tableWidget;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *QSwingSysDiagramWidget)
    {
        if (QSwingSysDiagramWidget->objectName().isEmpty())
            QSwingSysDiagramWidget->setObjectName(QString::fromUtf8("QSwingSysDiagramWidget"));
        QSwingSysDiagramWidget->resize(684, 400);
        horizontalLayout = new QHBoxLayout(QSwingSysDiagramWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_labDiagram = new QLabel(QSwingSysDiagramWidget);
        m_labDiagram->setObjectName(QString::fromUtf8("m_labDiagram"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labDiagram->sizePolicy().hasHeightForWidth());
        m_labDiagram->setSizePolicy(sizePolicy);
        m_labDiagram->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(m_labDiagram);


        verticalLayout->addLayout(verticalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        m_tableWidget = new QTableWidget(QSwingSysDiagramWidget);
        if (m_tableWidget->columnCount() < 2)
            m_tableWidget->setColumnCount(2);
        if (m_tableWidget->rowCount() < 4)
            m_tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(1, 0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(2, 0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(3, 0, __qtablewidgetitem3);
        m_tableWidget->setObjectName(QString::fromUtf8("m_tableWidget"));
        m_tableWidget->setShowGrid(false);
        m_tableWidget->setRowCount(4);
        m_tableWidget->setColumnCount(2);
        m_tableWidget->horizontalHeader()->setVisible(false);
        m_tableWidget->verticalHeader()->setVisible(false);

        horizontalLayout_4->addWidget(m_tableWidget);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QSwingSysDiagramWidget);

        QMetaObject::connectSlotsByName(QSwingSysDiagramWidget);
    } // setupUi

    void retranslateUi(QWidget *QSwingSysDiagramWidget)
    {
        QSwingSysDiagramWidget->setWindowTitle(QApplication::translate("QSwingSysDiagramWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_labDiagram->setText(QString());

        const bool __sortingEnabled = m_tableWidget->isSortingEnabled();
        m_tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = m_tableWidget->item(0, 0);
        ___qtablewidgetitem->setText(QApplication::translate("QSwingSysDiagramWidget", "\346\234\200\345\260\217\346\214\257\350\215\241\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = m_tableWidget->item(1, 0);
        ___qtablewidgetitem1->setText(QApplication::translate("QSwingSysDiagramWidget", "\346\234\200\345\244\247\346\214\257\350\215\241\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = m_tableWidget->item(2, 0);
        ___qtablewidgetitem2->setText(QApplication::translate("QSwingSysDiagramWidget", "\346\214\257\350\215\241\344\270\255\345\277\203", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = m_tableWidget->item(3, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("QSwingSysDiagramWidget", "\345\212\237\350\247\222", 0, QApplication::UnicodeUTF8));
        m_tableWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class QSwingSysDiagramWidget: public Ui_QSwingSysDiagramWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWINGSYSDIAGRAMWIDGET_H
