/********************************************************************************
** Form generated from reading UI file 'settingselectdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSELECTDLG_H
#define UI_SETTINGSELECTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingSelectDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_cannel;
    QPushButton *pushButton_AllCannel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Setting;
    QSpacerItem *horizontalSpacer;
    QLabel *label_Value;
    QLabel *label_Name;

    void setupUi(QWidget *SettingSelectDlg)
    {
        if (SettingSelectDlg->objectName().isEmpty())
            SettingSelectDlg->setObjectName(QString::fromUtf8("SettingSelectDlg"));
        SettingSelectDlg->resize(250, 53);
        SettingSelectDlg->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(SettingSelectDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(SettingSelectDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setAutoFillBackground(true);
        groupBox->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(181, 200, 200);"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(3);
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButton_cannel = new QPushButton(groupBox);
        pushButton_cannel->setObjectName(QString::fromUtf8("pushButton_cannel"));

        gridLayout_3->addWidget(pushButton_cannel, 1, 2, 1, 1);

        pushButton_AllCannel = new QPushButton(groupBox);
        pushButton_AllCannel->setObjectName(QString::fromUtf8("pushButton_AllCannel"));

        gridLayout_3->addWidget(pushButton_AllCannel, 1, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        pushButton_Setting = new QPushButton(groupBox);
        pushButton_Setting->setObjectName(QString::fromUtf8("pushButton_Setting"));

        gridLayout_3->addWidget(pushButton_Setting, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 3, 1, 1);

        label_Value = new QLabel(groupBox);
        label_Value->setObjectName(QString::fromUtf8("label_Value"));

        gridLayout_3->addWidget(label_Value, 0, 4, 1, 1);

        label_Name = new QLabel(groupBox);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));

        gridLayout_3->addWidget(label_Name, 0, 0, 1, 4);


        verticalLayout->addWidget(groupBox);

        QWidget::setTabOrder(pushButton_Setting, pushButton_cannel);
        QWidget::setTabOrder(pushButton_cannel, pushButton_AllCannel);

        retranslateUi(SettingSelectDlg);

        QMetaObject::connectSlotsByName(SettingSelectDlg);
    } // setupUi

    void retranslateUi(QWidget *SettingSelectDlg)
    {
        SettingSelectDlg->setWindowTitle(QApplication::translate("SettingSelectDlg", "\345\256\232\345\200\274\345\205\263\350\201\224", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        pushButton_cannel->setText(QApplication::translate("SettingSelectDlg", "\345\217\226\346\266\210\345\205\263\350\201\224", 0, QApplication::UnicodeUTF8));
        pushButton_AllCannel->setText(QApplication::translate("SettingSelectDlg", "\345\217\226\346\266\210\345\205\250\351\203\250", 0, QApplication::UnicodeUTF8));
        pushButton_Setting->setText(QApplication::translate("SettingSelectDlg", "\345\205\263\350\201\224\351\200\211\346\213\251\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        label_Value->setText(QApplication::translate("SettingSelectDlg", "0", 0, QApplication::UnicodeUTF8));
        label_Name->setText(QApplication::translate("SettingSelectDlg", "\345\260\232\346\234\252\345\205\263\350\201\224\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingSelectDlg: public Ui_SettingSelectDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSELECTDLG_H
