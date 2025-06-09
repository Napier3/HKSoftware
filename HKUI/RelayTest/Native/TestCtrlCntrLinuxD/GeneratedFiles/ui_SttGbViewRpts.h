/********************************************************************************
** Form generated from reading UI file 'SttGbViewRpts.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTGBVIEWRPTS_H
#define UI_STTGBVIEWRPTS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttGbViewRpts
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_TestCount;
    QComboBox *m_cmbTestCount;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;

    void setupUi(QDialog *QSttGbViewRpts)
    {
        if (QSttGbViewRpts->objectName().isEmpty())
            QSttGbViewRpts->setObjectName(QString::fromUtf8("QSttGbViewRpts"));
        QSttGbViewRpts->resize(804, 465);
        verticalLayout_2 = new QVBoxLayout(QSttGbViewRpts);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_TestCount = new QHBoxLayout();
        horizontalLayout_TestCount->setObjectName(QString::fromUtf8("horizontalLayout_TestCount"));
        m_cmbTestCount = new QComboBox(QSttGbViewRpts);
        m_cmbTestCount->setObjectName(QString::fromUtf8("m_cmbTestCount"));

        horizontalLayout_TestCount->addWidget(m_cmbTestCount);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_TestCount->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_TestCount);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 10, -1, -1);

        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttGbViewRpts);

        QMetaObject::connectSlotsByName(QSttGbViewRpts);
    } // setupUi

    void retranslateUi(QDialog *QSttGbViewRpts)
    {
        QSttGbViewRpts->setWindowTitle(QApplication::translate("QSttGbViewRpts", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttGbViewRpts: public Ui_QSttGbViewRpts {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTGBVIEWRPTS_H
