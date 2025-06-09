/********************************************************************************
** Form generated from reading UI file 'WidgetKeyboardV_Digit.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETKEYBOARDV_DIGIT_H
#define UI_WIDGETKEYBOARDV_DIGIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetKeyboardV_Digit
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QToolButton *btn_enter;
    QWidget *widget;
    QGridLayout *gridLayout;
    QToolButton *btn_2;
    QToolButton *btn_1;
    QToolButton *btn_6;
    QToolButton *btn_3;
    QToolButton *btn_5;
    QToolButton *btn_7;
    QToolButton *btn_8;
    QToolButton *btn_9;
    QToolButton *btn_4;
    QToolButton *btn_dol;
    QToolButton *btn_dele;
    QToolButton *btn_0;
    QToolButton *btn_abc;
    QToolButton *btn_amp;
    QToolButton *btn_10V;
    QToolButton *btn_100V;
    QToolButton *btn_57V;
    QToolButton *btn_50V;
    QToolButton *btn_20V;
    QToolButton *btn_30V;

    void setupUi(QDialog *WidgetKeyboardV_Digit)
    {
        if (WidgetKeyboardV_Digit->objectName().isEmpty())
            WidgetKeyboardV_Digit->setObjectName(QString::fromUtf8("WidgetKeyboardV_Digit"));
        WidgetKeyboardV_Digit->resize(713, 350);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WidgetKeyboardV_Digit->sizePolicy().hasHeightForWidth());
        WidgetKeyboardV_Digit->setSizePolicy(sizePolicy);
        WidgetKeyboardV_Digit->setMinimumSize(QSize(700, 350));
        WidgetKeyboardV_Digit->setMaximumSize(QSize(1024, 350));
        WidgetKeyboardV_Digit->setStyleSheet(QString::fromUtf8("background-color: #979797;"));
        verticalLayout = new QVBoxLayout(WidgetKeyboardV_Digit);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit = new QLineEdit(WidgetKeyboardV_Digit);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMinimumSize(QSize(0, 36));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));

        horizontalLayout_2->addWidget(lineEdit);

        btn_enter = new QToolButton(WidgetKeyboardV_Digit);
        btn_enter->setObjectName(QString::fromUtf8("btn_enter"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_enter->sizePolicy().hasHeightForWidth());
        btn_enter->setSizePolicy(sizePolicy2);
        btn_enter->setMinimumSize(QSize(120, 36));
        btn_enter->setMaximumSize(QSize(180, 36));
        QFont font;
        font.setPointSize(8);
        btn_enter->setFont(font);
        btn_enter->setAutoRepeat(true);

        horizontalLayout_2->addWidget(btn_enter);


        verticalLayout->addLayout(horizontalLayout_2);

        widget = new QWidget(WidgetKeyboardV_Digit);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn_2 = new QToolButton(widget);
        btn_2->setObjectName(QString::fromUtf8("btn_2"));
        sizePolicy.setHeightForWidth(btn_2->sizePolicy().hasHeightForWidth());
        btn_2->setSizePolicy(sizePolicy);
        btn_2->setMinimumSize(QSize(120, 50));
        btn_2->setMaximumSize(QSize(16777215, 50));
        btn_2->setFont(font);
        btn_2->setAutoRepeat(true);

        gridLayout->addWidget(btn_2, 0, 1, 1, 1);

        btn_1 = new QToolButton(widget);
        btn_1->setObjectName(QString::fromUtf8("btn_1"));
        sizePolicy.setHeightForWidth(btn_1->sizePolicy().hasHeightForWidth());
        btn_1->setSizePolicy(sizePolicy);
        btn_1->setMinimumSize(QSize(120, 50));
        btn_1->setMaximumSize(QSize(16777215, 50));
        btn_1->setFont(font);
        btn_1->setAutoRepeat(true);

        gridLayout->addWidget(btn_1, 0, 0, 1, 1);

        btn_6 = new QToolButton(widget);
        btn_6->setObjectName(QString::fromUtf8("btn_6"));
        sizePolicy.setHeightForWidth(btn_6->sizePolicy().hasHeightForWidth());
        btn_6->setSizePolicy(sizePolicy);
        btn_6->setMinimumSize(QSize(120, 50));
        btn_6->setMaximumSize(QSize(16777215, 50));
        btn_6->setFont(font);
        btn_6->setAutoRepeat(true);

        gridLayout->addWidget(btn_6, 2, 2, 1, 1);

        btn_3 = new QToolButton(widget);
        btn_3->setObjectName(QString::fromUtf8("btn_3"));
        sizePolicy.setHeightForWidth(btn_3->sizePolicy().hasHeightForWidth());
        btn_3->setSizePolicy(sizePolicy);
        btn_3->setMinimumSize(QSize(120, 50));
        btn_3->setMaximumSize(QSize(16777215, 50));
        btn_3->setFont(font);
        btn_3->setAutoRepeat(true);

        gridLayout->addWidget(btn_3, 0, 2, 1, 1);

        btn_5 = new QToolButton(widget);
        btn_5->setObjectName(QString::fromUtf8("btn_5"));
        sizePolicy.setHeightForWidth(btn_5->sizePolicy().hasHeightForWidth());
        btn_5->setSizePolicy(sizePolicy);
        btn_5->setMinimumSize(QSize(120, 50));
        btn_5->setMaximumSize(QSize(16777215, 50));
        btn_5->setFont(font);
        btn_5->setAutoRepeat(true);

        gridLayout->addWidget(btn_5, 2, 1, 1, 1);

        btn_7 = new QToolButton(widget);
        btn_7->setObjectName(QString::fromUtf8("btn_7"));
        sizePolicy.setHeightForWidth(btn_7->sizePolicy().hasHeightForWidth());
        btn_7->setSizePolicy(sizePolicy);
        btn_7->setMinimumSize(QSize(120, 50));
        btn_7->setMaximumSize(QSize(16777215, 50));
        btn_7->setFont(font);
        btn_7->setAutoRepeat(true);

        gridLayout->addWidget(btn_7, 3, 0, 1, 1);

        btn_8 = new QToolButton(widget);
        btn_8->setObjectName(QString::fromUtf8("btn_8"));
        sizePolicy.setHeightForWidth(btn_8->sizePolicy().hasHeightForWidth());
        btn_8->setSizePolicy(sizePolicy);
        btn_8->setMinimumSize(QSize(120, 50));
        btn_8->setMaximumSize(QSize(16777215, 50));
        btn_8->setFont(font);
        btn_8->setAutoRepeat(true);

        gridLayout->addWidget(btn_8, 3, 1, 1, 1);

        btn_9 = new QToolButton(widget);
        btn_9->setObjectName(QString::fromUtf8("btn_9"));
        sizePolicy.setHeightForWidth(btn_9->sizePolicy().hasHeightForWidth());
        btn_9->setSizePolicy(sizePolicy);
        btn_9->setMinimumSize(QSize(120, 50));
        btn_9->setMaximumSize(QSize(16777215, 50));
        btn_9->setFont(font);
        btn_9->setAutoRepeat(true);

        gridLayout->addWidget(btn_9, 3, 2, 1, 1);

        btn_4 = new QToolButton(widget);
        btn_4->setObjectName(QString::fromUtf8("btn_4"));
        sizePolicy.setHeightForWidth(btn_4->sizePolicy().hasHeightForWidth());
        btn_4->setSizePolicy(sizePolicy);
        btn_4->setMinimumSize(QSize(120, 50));
        btn_4->setMaximumSize(QSize(16777215, 50));
        btn_4->setFont(font);
        btn_4->setAutoRepeat(true);

        gridLayout->addWidget(btn_4, 2, 0, 1, 1);

        btn_dol = new QToolButton(widget);
        btn_dol->setObjectName(QString::fromUtf8("btn_dol"));
        sizePolicy.setHeightForWidth(btn_dol->sizePolicy().hasHeightForWidth());
        btn_dol->setSizePolicy(sizePolicy);
        btn_dol->setMinimumSize(QSize(120, 50));
        btn_dol->setMaximumSize(QSize(16777215, 50));
        btn_dol->setFont(font);
        btn_dol->setAutoRepeat(true);

        gridLayout->addWidget(btn_dol, 5, 0, 1, 1);

        btn_dele = new QToolButton(widget);
        btn_dele->setObjectName(QString::fromUtf8("btn_dele"));
        sizePolicy.setHeightForWidth(btn_dele->sizePolicy().hasHeightForWidth());
        btn_dele->setSizePolicy(sizePolicy);
        btn_dele->setMinimumSize(QSize(120, 50));
        btn_dele->setMaximumSize(QSize(16777215, 50));
        btn_dele->setFont(font);
        btn_dele->setAutoRepeat(true);

        gridLayout->addWidget(btn_dele, 5, 2, 1, 1);

        btn_0 = new QToolButton(widget);
        btn_0->setObjectName(QString::fromUtf8("btn_0"));
        sizePolicy.setHeightForWidth(btn_0->sizePolicy().hasHeightForWidth());
        btn_0->setSizePolicy(sizePolicy);
        btn_0->setMinimumSize(QSize(120, 50));
        btn_0->setMaximumSize(QSize(16777215, 50));
        btn_0->setFont(font);
        btn_0->setAutoRepeat(true);

        gridLayout->addWidget(btn_0, 5, 1, 1, 1);

        btn_abc = new QToolButton(widget);
        btn_abc->setObjectName(QString::fromUtf8("btn_abc"));
        btn_abc->setEnabled(false);
        sizePolicy.setHeightForWidth(btn_abc->sizePolicy().hasHeightForWidth());
        btn_abc->setSizePolicy(sizePolicy);
        btn_abc->setMinimumSize(QSize(120, 50));
        btn_abc->setMaximumSize(QSize(16777215, 50));
        btn_abc->setFont(font);
        btn_abc->setAutoRepeat(true);

        gridLayout->addWidget(btn_abc, 5, 3, 1, 1);

        btn_amp = new QToolButton(widget);
        btn_amp->setObjectName(QString::fromUtf8("btn_amp"));
        sizePolicy.setHeightForWidth(btn_amp->sizePolicy().hasHeightForWidth());
        btn_amp->setSizePolicy(sizePolicy);
        btn_amp->setMinimumSize(QSize(120, 50));
        btn_amp->setMaximumSize(QSize(16777215, 50));
        btn_amp->setFont(font);
        btn_amp->setAutoRepeat(true);

        gridLayout->addWidget(btn_amp, 3, 3, 1, 1);

        btn_10V = new QToolButton(widget);
        btn_10V->setObjectName(QString::fromUtf8("btn_10V"));
        sizePolicy.setHeightForWidth(btn_10V->sizePolicy().hasHeightForWidth());
        btn_10V->setSizePolicy(sizePolicy);
        btn_10V->setMinimumSize(QSize(120, 50));
        btn_10V->setMaximumSize(QSize(16777215, 50));
        btn_10V->setFont(font);
        btn_10V->setAutoRepeat(true);

        gridLayout->addWidget(btn_10V, 0, 3, 1, 1);

        btn_100V = new QToolButton(widget);
        btn_100V->setObjectName(QString::fromUtf8("btn_100V"));
        sizePolicy.setHeightForWidth(btn_100V->sizePolicy().hasHeightForWidth());
        btn_100V->setSizePolicy(sizePolicy);
        btn_100V->setMinimumSize(QSize(120, 50));
        btn_100V->setMaximumSize(QSize(16777215, 50));
        btn_100V->setFont(font);
        btn_100V->setAutoRepeat(true);

        gridLayout->addWidget(btn_100V, 5, 4, 1, 1);

        btn_57V = new QToolButton(widget);
        btn_57V->setObjectName(QString::fromUtf8("btn_57V"));
        sizePolicy.setHeightForWidth(btn_57V->sizePolicy().hasHeightForWidth());
        btn_57V->setSizePolicy(sizePolicy);
        btn_57V->setMinimumSize(QSize(120, 50));
        btn_57V->setMaximumSize(QSize(16777215, 50));
        btn_57V->setFont(font);
        btn_57V->setAutoRepeat(true);

        gridLayout->addWidget(btn_57V, 3, 4, 1, 1);

        btn_50V = new QToolButton(widget);
        btn_50V->setObjectName(QString::fromUtf8("btn_50V"));
        sizePolicy.setHeightForWidth(btn_50V->sizePolicy().hasHeightForWidth());
        btn_50V->setSizePolicy(sizePolicy);
        btn_50V->setMinimumSize(QSize(120, 50));
        btn_50V->setMaximumSize(QSize(16777215, 50));
        btn_50V->setFont(font);
        btn_50V->setAutoRepeat(true);

        gridLayout->addWidget(btn_50V, 2, 4, 1, 1);

        btn_20V = new QToolButton(widget);
        btn_20V->setObjectName(QString::fromUtf8("btn_20V"));
        sizePolicy.setHeightForWidth(btn_20V->sizePolicy().hasHeightForWidth());
        btn_20V->setSizePolicy(sizePolicy);
        btn_20V->setMinimumSize(QSize(120, 50));
        btn_20V->setMaximumSize(QSize(16777215, 50));
        btn_20V->setFont(font);
        btn_20V->setFocusPolicy(Qt::TabFocus);

        gridLayout->addWidget(btn_20V, 2, 3, 1, 1);

        btn_30V = new QToolButton(widget);
        btn_30V->setObjectName(QString::fromUtf8("btn_30V"));
        sizePolicy.setHeightForWidth(btn_30V->sizePolicy().hasHeightForWidth());
        btn_30V->setSizePolicy(sizePolicy);
        btn_30V->setMinimumSize(QSize(120, 50));
        btn_30V->setMaximumSize(QSize(16777215, 50));
        btn_30V->setFont(font);
        btn_30V->setFocusPolicy(Qt::TabFocus);

        gridLayout->addWidget(btn_30V, 0, 4, 1, 1);


        verticalLayout->addWidget(widget);


        retranslateUi(WidgetKeyboardV_Digit);

        QMetaObject::connectSlotsByName(WidgetKeyboardV_Digit);
    } // setupUi

    void retranslateUi(QDialog *WidgetKeyboardV_Digit)
    {
        WidgetKeyboardV_Digit->setWindowTitle(QApplication::translate("WidgetKeyboardV_Digit", "WidgetKeyboardV_Digit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_enter->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x01000004", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_enter->setText(QApplication::translate("WidgetKeyboardV_Digit", "Enter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_2->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_2->setText(QApplication::translate("WidgetKeyboardV_Digit", "2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_1->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_1->setText(QApplication::translate("WidgetKeyboardV_Digit", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_6->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_6->setText(QApplication::translate("WidgetKeyboardV_Digit", "6", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_3->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_3->setText(QApplication::translate("WidgetKeyboardV_Digit", "3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_5->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_5->setText(QApplication::translate("WidgetKeyboardV_Digit", "5", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_7->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_7->setText(QApplication::translate("WidgetKeyboardV_Digit", "7", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_8->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_8->setText(QApplication::translate("WidgetKeyboardV_Digit", "8", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_9->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_9->setText(QApplication::translate("WidgetKeyboardV_Digit", "9", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_4->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_4->setText(QApplication::translate("WidgetKeyboardV_Digit", "4", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_dol->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_dol->setText(QApplication::translate("WidgetKeyboardV_Digit", ".", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_dele->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x4d", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_dele->setText(QApplication::translate("WidgetKeyboardV_Digit", "Delete", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_0->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_0->setText(QApplication::translate("WidgetKeyboardV_Digit", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_abc->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_abc->setText(QApplication::translate("WidgetKeyboardV_Digit", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_amp->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_amp->setText(QApplication::translate("WidgetKeyboardV_Digit", "equal amp", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_10V->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_10V->setText(QApplication::translate("WidgetKeyboardV_Digit", "10V", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_100V->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_100V->setText(QApplication::translate("WidgetKeyboardV_Digit", "100V", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_57V->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_57V->setText(QApplication::translate("WidgetKeyboardV_Digit", "57.74V", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_50V->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_50V->setText(QApplication::translate("WidgetKeyboardV_Digit", "50V", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_20V->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_20V->setText(QApplication::translate("WidgetKeyboardV_Digit", "20V", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_30V->setAccessibleName(QApplication::translate("WidgetKeyboardV_Digit", "0x51", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_30V->setText(QApplication::translate("WidgetKeyboardV_Digit", "30V", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidgetKeyboardV_Digit: public Ui_WidgetKeyboardV_Digit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETKEYBOARDV_DIGIT_H
