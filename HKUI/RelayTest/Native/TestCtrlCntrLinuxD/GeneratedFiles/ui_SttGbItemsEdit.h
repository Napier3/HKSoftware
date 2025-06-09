/********************************************************************************
** Form generated from reading UI file 'SttGbItemsEdit.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTGBITEMSEDIT_H
#define UI_STTGBITEMSEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttGbItemsEdit
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_Name;
    QLineEdit *lineEdit_Name;
    QLineEdit *lineEdit_ID;
    QLabel *label_ID;
    QLineEdit *m_editTimes;
    QPushButton *m_Btn_SelName;
    QLabel *m_txtTimes;
    QCheckBox *m_chk_AutoUpdateItemName;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *m_chkRptTitle;
    QLabel *m_txtTitleLevel;
    QComboBox *m_cmbTitleLevel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_Btn_OK;
    QPushButton *m_Btn_Cancel;

    void setupUi(QDialog *QSttGbItemsEdit)
    {
        if (QSttGbItemsEdit->objectName().isEmpty())
            QSttGbItemsEdit->setObjectName(QString::fromUtf8("QSttGbItemsEdit"));
        QSttGbItemsEdit->resize(486, 222);
        verticalLayout_2 = new QVBoxLayout(QSttGbItemsEdit);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_Name = new QLabel(QSttGbItemsEdit);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));
        QFont font;
        font.setPointSize(16);
        label_Name->setFont(font);
        label_Name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_Name, 0, 1, 1, 1);

        lineEdit_Name = new QLineEdit(QSttGbItemsEdit);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));
        lineEdit_Name->setFont(font);

        gridLayout->addWidget(lineEdit_Name, 0, 3, 1, 1);

        lineEdit_ID = new QLineEdit(QSttGbItemsEdit);
        lineEdit_ID->setObjectName(QString::fromUtf8("lineEdit_ID"));
        lineEdit_ID->setFont(font);

        gridLayout->addWidget(lineEdit_ID, 2, 3, 1, 1);

        label_ID = new QLabel(QSttGbItemsEdit);
        label_ID->setObjectName(QString::fromUtf8("label_ID"));
        label_ID->setFont(font);
        label_ID->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_ID, 2, 1, 1, 1);

        m_editTimes = new QLineEdit(QSttGbItemsEdit);
        m_editTimes->setObjectName(QString::fromUtf8("m_editTimes"));
        m_editTimes->setFont(font);

        gridLayout->addWidget(m_editTimes, 3, 3, 1, 1);

        m_Btn_SelName = new QPushButton(QSttGbItemsEdit);
        m_Btn_SelName->setObjectName(QString::fromUtf8("m_Btn_SelName"));
        m_Btn_SelName->setFont(font);

        gridLayout->addWidget(m_Btn_SelName, 0, 4, 1, 1);

        m_txtTimes = new QLabel(QSttGbItemsEdit);
        m_txtTimes->setObjectName(QString::fromUtf8("m_txtTimes"));
        m_txtTimes->setFont(font);

        gridLayout->addWidget(m_txtTimes, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        m_chk_AutoUpdateItemName = new QCheckBox(QSttGbItemsEdit);
        m_chk_AutoUpdateItemName->setObjectName(QString::fromUtf8("m_chk_AutoUpdateItemName"));
        m_chk_AutoUpdateItemName->setFont(font);

        verticalLayout->addWidget(m_chk_AutoUpdateItemName);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_chkRptTitle = new QCheckBox(QSttGbItemsEdit);
        m_chkRptTitle->setObjectName(QString::fromUtf8("m_chkRptTitle"));
        m_chkRptTitle->setFont(font);

        horizontalLayout_2->addWidget(m_chkRptTitle);

        m_txtTitleLevel = new QLabel(QSttGbItemsEdit);
        m_txtTitleLevel->setObjectName(QString::fromUtf8("m_txtTitleLevel"));
        m_txtTitleLevel->setFont(font);

        horizontalLayout_2->addWidget(m_txtTitleLevel);

        m_cmbTitleLevel = new QComboBox(QSttGbItemsEdit);
        m_cmbTitleLevel->setObjectName(QString::fromUtf8("m_cmbTitleLevel"));
        m_cmbTitleLevel->setFont(font);

        horizontalLayout_2->addWidget(m_cmbTitleLevel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_Btn_OK = new QPushButton(QSttGbItemsEdit);
        m_Btn_OK->setObjectName(QString::fromUtf8("m_Btn_OK"));
        m_Btn_OK->setFont(font);

        horizontalLayout->addWidget(m_Btn_OK);

        m_Btn_Cancel = new QPushButton(QSttGbItemsEdit);
        m_Btn_Cancel->setObjectName(QString::fromUtf8("m_Btn_Cancel"));
        m_Btn_Cancel->setFont(font);

        horizontalLayout->addWidget(m_Btn_Cancel);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttGbItemsEdit);

        QMetaObject::connectSlotsByName(QSttGbItemsEdit);
    } // setupUi

    void retranslateUi(QDialog *QSttGbItemsEdit)
    {
        QSttGbItemsEdit->setWindowTitle(QApplication::translate("QSttGbItemsEdit", "Edit", 0, QApplication::UnicodeUTF8));
        label_Name->setText(QApplication::translate("QSttGbItemsEdit", "\351\241\271\347\233\256\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_ID->setText(QApplication::translate("QSttGbItemsEdit", "ID", 0, QApplication::UnicodeUTF8));
        m_Btn_SelName->setText(QApplication::translate("QSttGbItemsEdit", "\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        m_txtTimes->setText(QApplication::translate("QSttGbItemsEdit", "\346\265\213\350\257\225\346\254\241\346\225\260", 0, QApplication::UnicodeUTF8));
        m_chk_AutoUpdateItemName->setText(QApplication::translate("QSttGbItemsEdit", "\346\265\213\350\257\225\346\254\241\346\225\260 >1\346\227\266\357\274\214\350\207\252\345\212\250\346\233\264\346\226\260\345\210\260\351\241\271\347\233\256\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_chkRptTitle->setText(QApplication::translate("QSttGbItemsEdit", "\345\220\215\347\247\260\344\275\234\344\270\272word\346\240\207\351\242\230", 0, QApplication::UnicodeUTF8));
        m_txtTitleLevel->setText(QApplication::translate("QSttGbItemsEdit", "\346\240\207\351\242\230\347\255\211\347\272\247", 0, QApplication::UnicodeUTF8));
        m_Btn_OK->setText(QApplication::translate("QSttGbItemsEdit", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_Btn_Cancel->setText(QApplication::translate("QSttGbItemsEdit", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttGbItemsEdit: public Ui_QSttGbItemsEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTGBITEMSEDIT_H
