/********************************************************************************
** Form generated from reading UI file 'WidgetKeyboard.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETKEYBOARD_H
#define UI_WIDGETKEYBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetKeyboard
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;

    void setupUi(QWidget *WidgetKeyboard)
    {
        if (WidgetKeyboard->objectName().isEmpty())
            WidgetKeyboard->setObjectName(QString::fromUtf8("WidgetKeyboard"));
        WidgetKeyboard->resize(1024, 350);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(30);
        font.setBold(false);
        font.setWeight(50);
        WidgetKeyboard->setFont(font);
        stackedWidget = new QStackedWidget(WidgetKeyboard);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1024, 350));
        stackedWidget->setFrameShape(QFrame::StyledPanel);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        retranslateUi(WidgetKeyboard);

        QMetaObject::connectSlotsByName(WidgetKeyboard);
    } // setupUi

    void retranslateUi(QWidget *WidgetKeyboard)
    {
        WidgetKeyboard->setWindowTitle(QApplication::translate("WidgetKeyboard", "Virtual Keyboard", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidgetKeyboard: public Ui_WidgetKeyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETKEYBOARD_H
