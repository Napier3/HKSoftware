/********************************************************************************
** Form generated from reading UI file 'SttImportDvmFileWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTIMPORTDVMFILEWIDGET_H
#define UI_STTIMPORTDVMFILEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttImportDvmFileWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutWzd;
    QHBoxLayout *horizontalLayout_Btns;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Pre;
    QPushButton *pushButton_Next;
    QPushButton *pushButton_Cancel;

    void setupUi(QDialog *QSttImportDvmFileWidget)
    {
        if (QSttImportDvmFileWidget->objectName().isEmpty())
            QSttImportDvmFileWidget->setObjectName(QString::fromUtf8("QSttImportDvmFileWidget"));
        QSttImportDvmFileWidget->resize(1115, 653);
        verticalLayout_2 = new QVBoxLayout(QSttImportDvmFileWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayoutWzd = new QHBoxLayout();
        horizontalLayoutWzd->setObjectName(QString::fromUtf8("horizontalLayoutWzd"));
        horizontalLayoutWzd->setContentsMargins(18, -1, 18, -1);

        verticalLayout->addLayout(horizontalLayoutWzd);

        horizontalLayout_Btns = new QHBoxLayout();
        horizontalLayout_Btns->setSpacing(15);
        horizontalLayout_Btns->setObjectName(QString::fromUtf8("horizontalLayout_Btns"));
        horizontalLayout_Btns->setContentsMargins(-1, -1, 20, 15);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_Btns->addItem(horizontalSpacer);

        pushButton_Pre = new QPushButton(QSttImportDvmFileWidget);
        pushButton_Pre->setObjectName(QString::fromUtf8("pushButton_Pre"));

        horizontalLayout_Btns->addWidget(pushButton_Pre);

        pushButton_Next = new QPushButton(QSttImportDvmFileWidget);
        pushButton_Next->setObjectName(QString::fromUtf8("pushButton_Next"));

        horizontalLayout_Btns->addWidget(pushButton_Next);

        pushButton_Cancel = new QPushButton(QSttImportDvmFileWidget);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));

        horizontalLayout_Btns->addWidget(pushButton_Cancel);


        verticalLayout->addLayout(horizontalLayout_Btns);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttImportDvmFileWidget);

        QMetaObject::connectSlotsByName(QSttImportDvmFileWidget);
    } // setupUi

    void retranslateUi(QDialog *QSttImportDvmFileWidget)
    {
        QSttImportDvmFileWidget->setWindowTitle(QString());
        pushButton_Pre->setText(QApplication::translate("QSttImportDvmFileWidget", "\344\270\212\344\270\200\351\241\271", 0, QApplication::UnicodeUTF8));
        pushButton_Next->setText(QApplication::translate("QSttImportDvmFileWidget", "\344\270\213\344\270\200\351\241\271", 0, QApplication::UnicodeUTF8));
        pushButton_Cancel->setText(QApplication::translate("QSttImportDvmFileWidget", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttImportDvmFileWidget: public Ui_QSttImportDvmFileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTIMPORTDVMFILEWIDGET_H
