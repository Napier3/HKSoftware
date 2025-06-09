/********************************************************************************
** Form generated from reading UI file 'SttIecRecordMainWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTIECRECORDMAINWIDGET_H
#define UI_STTIECRECORDMAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttIecRecordMainWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *QSttIecRecordMainWidget)
    {
        if (QSttIecRecordMainWidget->objectName().isEmpty())
            QSttIecRecordMainWidget->setObjectName(QString::fromUtf8("QSttIecRecordMainWidget"));
        QSttIecRecordMainWidget->resize(705, 366);
        verticalLayout_2 = new QVBoxLayout(QSttIecRecordMainWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttIecRecordMainWidget);

        QMetaObject::connectSlotsByName(QSttIecRecordMainWidget);
    } // setupUi

    void retranslateUi(QDialog *QSttIecRecordMainWidget)
    {
        QSttIecRecordMainWidget->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class QSttIecRecordMainWidget: public Ui_QSttIecRecordMainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTIECRECORDMAINWIDGET_H
