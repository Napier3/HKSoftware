/********************************************************************************
** Form generated from reading UI file 'SttReportView.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTREPORTVIEW_H
#define UI_STTREPORTVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSttReportView
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTextEdit *btnTextEdit;
    QHBoxLayout *horizontalLayout_2;

    void setupUi(QWidget *QSttReportView)
    {
        if (QSttReportView->objectName().isEmpty())
            QSttReportView->setObjectName(QString::fromUtf8("QSttReportView"));
        QSttReportView->resize(411, 326);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QSttReportView->sizePolicy().hasHeightForWidth());
        QSttReportView->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(QSttReportView);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnTextEdit = new QTextEdit(QSttReportView);
        btnTextEdit->setObjectName(QString::fromUtf8("btnTextEdit"));
        btnTextEdit->setLineWrapMode(QTextEdit::FixedPixelWidth);
        btnTextEdit->setLineWrapColumnOrWidth(1050);
        btnTextEdit->setReadOnly(true);

        verticalLayout->addWidget(btnTextEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttReportView);

        QMetaObject::connectSlotsByName(QSttReportView);
    } // setupUi

    void retranslateUi(QWidget *QSttReportView)
    {
        QSttReportView->setWindowTitle(QApplication::translate("QSttReportView", "\351\242\204\350\247\210\346\212\245\345\221\212", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttReportView: public Ui_QSttReportView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTREPORTVIEW_H
