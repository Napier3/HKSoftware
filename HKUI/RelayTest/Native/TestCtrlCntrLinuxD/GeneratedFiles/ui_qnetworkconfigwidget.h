/********************************************************************************
** Form generated from reading UI file 'qnetworkconfigwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QNETWORKCONFIGWIDGET_H
#define UI_QNETWORKCONFIGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QNetworkConfigWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_pNetCardSel_Label;
    QComboBox *m_pNetCardSel_ComboBox;
    QLabel *m_pLocalIP_Label;
    QComboBox *m_pLocalIP_ComboBox;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *m_wndVertLayout;
    QHBoxLayout *m_wndBtnsLayout;
    QPushButton *m_pScan_PushButton;
    QLabel *m_pServerIP_Label;
    QLineEdit *m_pServerIP_LineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnModify;
    QPushButton *m_btnAdd;
    QPushButton *m_btnDelete;
    QPushButton *m_pCancel_PushButton;

    void setupUi(QWidget *QNetworkConfigWidget)
    {
        if (QNetworkConfigWidget->objectName().isEmpty())
            QNetworkConfigWidget->setObjectName(QString::fromUtf8("QNetworkConfigWidget"));
        QNetworkConfigWidget->resize(647, 313);
        verticalLayout_2 = new QVBoxLayout(QNetworkConfigWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_pNetCardSel_Label = new QLabel(QNetworkConfigWidget);
        m_pNetCardSel_Label->setObjectName(QString::fromUtf8("m_pNetCardSel_Label"));

        horizontalLayout_3->addWidget(m_pNetCardSel_Label);

        m_pNetCardSel_ComboBox = new QComboBox(QNetworkConfigWidget);
        m_pNetCardSel_ComboBox->setObjectName(QString::fromUtf8("m_pNetCardSel_ComboBox"));

        horizontalLayout_3->addWidget(m_pNetCardSel_ComboBox);

        m_pLocalIP_Label = new QLabel(QNetworkConfigWidget);
        m_pLocalIP_Label->setObjectName(QString::fromUtf8("m_pLocalIP_Label"));

        horizontalLayout_3->addWidget(m_pLocalIP_Label);

        m_pLocalIP_ComboBox = new QComboBox(QNetworkConfigWidget);
        m_pLocalIP_ComboBox->setObjectName(QString::fromUtf8("m_pLocalIP_ComboBox"));

        horizontalLayout_3->addWidget(m_pLocalIP_ComboBox);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_3);

        m_wndVertLayout = new QVBoxLayout();
        m_wndVertLayout->setObjectName(QString::fromUtf8("m_wndVertLayout"));
        m_wndBtnsLayout = new QHBoxLayout();
        m_wndBtnsLayout->setObjectName(QString::fromUtf8("m_wndBtnsLayout"));
        m_pScan_PushButton = new QPushButton(QNetworkConfigWidget);
        m_pScan_PushButton->setObjectName(QString::fromUtf8("m_pScan_PushButton"));

        m_wndBtnsLayout->addWidget(m_pScan_PushButton);

        m_pServerIP_Label = new QLabel(QNetworkConfigWidget);
        m_pServerIP_Label->setObjectName(QString::fromUtf8("m_pServerIP_Label"));

        m_wndBtnsLayout->addWidget(m_pServerIP_Label);

        m_pServerIP_LineEdit = new QLineEdit(QNetworkConfigWidget);
        m_pServerIP_LineEdit->setObjectName(QString::fromUtf8("m_pServerIP_LineEdit"));

        m_wndBtnsLayout->addWidget(m_pServerIP_LineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_wndBtnsLayout->addItem(horizontalSpacer);

        m_btnModify = new QPushButton(QNetworkConfigWidget);
        m_btnModify->setObjectName(QString::fromUtf8("m_btnModify"));

        m_wndBtnsLayout->addWidget(m_btnModify);

        m_btnAdd = new QPushButton(QNetworkConfigWidget);
        m_btnAdd->setObjectName(QString::fromUtf8("m_btnAdd"));

        m_wndBtnsLayout->addWidget(m_btnAdd);

        m_btnDelete = new QPushButton(QNetworkConfigWidget);
        m_btnDelete->setObjectName(QString::fromUtf8("m_btnDelete"));

        m_wndBtnsLayout->addWidget(m_btnDelete);

        m_pCancel_PushButton = new QPushButton(QNetworkConfigWidget);
        m_pCancel_PushButton->setObjectName(QString::fromUtf8("m_pCancel_PushButton"));

        m_wndBtnsLayout->addWidget(m_pCancel_PushButton);


        m_wndVertLayout->addLayout(m_wndBtnsLayout);


        verticalLayout_2->addLayout(m_wndVertLayout);


        retranslateUi(QNetworkConfigWidget);

        QMetaObject::connectSlotsByName(QNetworkConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *QNetworkConfigWidget)
    {
        QNetworkConfigWidget->setWindowTitle(QApplication::translate("QNetworkConfigWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_pNetCardSel_Label->setText(QApplication::translate("QNetworkConfigWidget", "\347\275\221\345\215\241\351\200\211\346\213\251\357\274\232", 0, QApplication::UnicodeUTF8));
        m_pLocalIP_Label->setText(QApplication::translate("QNetworkConfigWidget", "\346\234\254\345\234\260\347\275\221\345\215\241IP:", 0, QApplication::UnicodeUTF8));
        m_pScan_PushButton->setText(QApplication::translate("QNetworkConfigWidget", "\346\211\253\346\217\217", 0, QApplication::UnicodeUTF8));
        m_pServerIP_Label->setText(QApplication::translate("QNetworkConfigWidget", "\344\270\273IP\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        m_btnModify->setText(QApplication::translate("QNetworkConfigWidget", "\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
        m_btnAdd->setText(QApplication::translate("QNetworkConfigWidget", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        m_btnDelete->setText(QApplication::translate("QNetworkConfigWidget", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        m_pCancel_PushButton->setText(QApplication::translate("QNetworkConfigWidget", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QNetworkConfigWidget: public Ui_QNetworkConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QNETWORKCONFIGWIDGET_H
