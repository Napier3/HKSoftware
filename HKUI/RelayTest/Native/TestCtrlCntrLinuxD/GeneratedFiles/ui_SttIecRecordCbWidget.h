/********************************************************************************
** Form generated from reading UI file 'SttIecRecordCbWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTIECRECORDCBWIDGET_H
#define UI_STTIECRECORDCBWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttIecRecordCbWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayoutNameID;
    QHBoxLayout *m_layButtons;
    QLabel *m_lblSelCb;
    QLabel *m_lblSelFunc;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnPrevPage;
    QPushButton *m_btnNextPage;
    QLabel *m_lblHarmDisplay;
    QPushButton *m_btnAddToSub;
    QPushButton *m_btnAddToPub;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_btnSysSet;
    QPushButton *m_btnBack;

    void setupUi(QDialog *QSttIecRecordCbWidget)
    {
        if (QSttIecRecordCbWidget->objectName().isEmpty())
            QSttIecRecordCbWidget->setObjectName(QString::fromUtf8("QSttIecRecordCbWidget"));
        QSttIecRecordCbWidget->resize(1061, 366);
        verticalLayout_2 = new QVBoxLayout(QSttIecRecordCbWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayoutNameID = new QGridLayout();
        gridLayoutNameID->setObjectName(QString::fromUtf8("gridLayoutNameID"));

        verticalLayout->addLayout(gridLayoutNameID);

        m_layButtons = new QHBoxLayout();
        m_layButtons->setSpacing(6);
        m_layButtons->setObjectName(QString::fromUtf8("m_layButtons"));
        m_layButtons->setSizeConstraint(QLayout::SetDefaultConstraint);
        m_lblSelCb = new QLabel(QSttIecRecordCbWidget);
        m_lblSelCb->setObjectName(QString::fromUtf8("m_lblSelCb"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(20);
        m_lblSelCb->setFont(font);

        m_layButtons->addWidget(m_lblSelCb);

        m_lblSelFunc = new QLabel(QSttIecRecordCbWidget);
        m_lblSelFunc->setObjectName(QString::fromUtf8("m_lblSelFunc"));
        m_lblSelFunc->setFont(font);

        m_layButtons->addWidget(m_lblSelFunc);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_layButtons->addItem(horizontalSpacer);

        m_btnPrevPage = new QPushButton(QSttIecRecordCbWidget);
        m_btnPrevPage->setObjectName(QString::fromUtf8("m_btnPrevPage"));
        m_btnPrevPage->setFont(font);

        m_layButtons->addWidget(m_btnPrevPage);

        m_btnNextPage = new QPushButton(QSttIecRecordCbWidget);
        m_btnNextPage->setObjectName(QString::fromUtf8("m_btnNextPage"));
        m_btnNextPage->setFont(font);

        m_layButtons->addWidget(m_btnNextPage);

        m_lblHarmDisplay = new QLabel(QSttIecRecordCbWidget);
        m_lblHarmDisplay->setObjectName(QString::fromUtf8("m_lblHarmDisplay"));
        m_lblHarmDisplay->setFont(font);

        m_layButtons->addWidget(m_lblHarmDisplay);

        m_btnAddToSub = new QPushButton(QSttIecRecordCbWidget);
        m_btnAddToSub->setObjectName(QString::fromUtf8("m_btnAddToSub"));
        m_btnAddToSub->setFont(font);

        m_layButtons->addWidget(m_btnAddToSub);

        m_btnAddToPub = new QPushButton(QSttIecRecordCbWidget);
        m_btnAddToPub->setObjectName(QString::fromUtf8("m_btnAddToPub"));
        m_btnAddToPub->setFont(font);

        m_layButtons->addWidget(m_btnAddToPub);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_layButtons->addItem(horizontalSpacer_2);

        m_btnSysSet = new QPushButton(QSttIecRecordCbWidget);
        m_btnSysSet->setObjectName(QString::fromUtf8("m_btnSysSet"));
        m_btnSysSet->setFont(font);

        m_layButtons->addWidget(m_btnSysSet);

        m_btnBack = new QPushButton(QSttIecRecordCbWidget);
        m_btnBack->setObjectName(QString::fromUtf8("m_btnBack"));
        m_btnBack->setFont(font);

        m_layButtons->addWidget(m_btnBack);


        verticalLayout->addLayout(m_layButtons);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttIecRecordCbWidget);

        QMetaObject::connectSlotsByName(QSttIecRecordCbWidget);
    } // setupUi

    void retranslateUi(QDialog *QSttIecRecordCbWidget)
    {
        QSttIecRecordCbWidget->setWindowTitle(QString());
        m_lblSelCb->setText(QApplication::translate("QSttIecRecordCbWidget", "\351\200\211\346\213\251\346\216\247\345\210\266\345\235\227", 0, QApplication::UnicodeUTF8));
        m_lblSelFunc->setText(QApplication::translate("QSttIecRecordCbWidget", "\351\200\211\346\213\251\345\212\237\350\203\275", 0, QApplication::UnicodeUTF8));
        m_btnPrevPage->setText(QApplication::translate("QSttIecRecordCbWidget", "\344\270\212\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
        m_btnNextPage->setText(QApplication::translate("QSttIecRecordCbWidget", "\344\270\213\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
        m_lblHarmDisplay->setText(QApplication::translate("QSttIecRecordCbWidget", "\350\260\220\346\263\242\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        m_btnAddToSub->setText(QApplication::translate("QSttIecRecordCbWidget", "\350\207\263\350\256\242\351\230\205", 0, QApplication::UnicodeUTF8));
        m_btnAddToPub->setText(QApplication::translate("QSttIecRecordCbWidget", "\350\207\263\345\217\221\345\270\203", 0, QApplication::UnicodeUTF8));
        m_btnSysSet->setText(QApplication::translate("QSttIecRecordCbWidget", "\347\263\273\347\273\237\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_btnBack->setText(QApplication::translate("QSttIecRecordCbWidget", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttIecRecordCbWidget: public Ui_QSttIecRecordCbWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTIECRECORDCBWIDGET_H
