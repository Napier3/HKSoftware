/********************************************************************************
** Form generated from reading UI file 'SttGbSafetyEdit.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTGBSAFETYEDIT_H
#define UI_STTGBSAFETYEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttGbSafetyEdit
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_label_SelDefaultMsg;
    QComboBox *m_cmbMsgs;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *textEdit_Msgs;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Name;
    QLineEdit *lineEdit_Name;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_Btn_OK;
    QPushButton *m_Btn_Cancel;

    void setupUi(QDialog *QSttGbSafetyEdit)
    {
        if (QSttGbSafetyEdit->objectName().isEmpty())
            QSttGbSafetyEdit->setObjectName(QString::fromUtf8("QSttGbSafetyEdit"));
        QSttGbSafetyEdit->resize(769, 401);
        verticalLayout_2 = new QVBoxLayout(QSttGbSafetyEdit);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        m_label_SelDefaultMsg = new QLabel(QSttGbSafetyEdit);
        m_label_SelDefaultMsg->setObjectName(QString::fromUtf8("m_label_SelDefaultMsg"));
        QFont font;
        font.setPointSize(16);
        m_label_SelDefaultMsg->setFont(font);

        horizontalLayout_2->addWidget(m_label_SelDefaultMsg);

        m_cmbMsgs = new QComboBox(QSttGbSafetyEdit);
        m_cmbMsgs->setObjectName(QString::fromUtf8("m_cmbMsgs"));
        m_cmbMsgs->setFont(font);

        horizontalLayout_2->addWidget(m_cmbMsgs);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        textEdit_Msgs = new QTextEdit(QSttGbSafetyEdit);
        textEdit_Msgs->setObjectName(QString::fromUtf8("textEdit_Msgs"));
        textEdit_Msgs->setFont(font);

        verticalLayout->addWidget(textEdit_Msgs);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_Name = new QLabel(QSttGbSafetyEdit);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));
        label_Name->setFont(font);
        label_Name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_Name);

        lineEdit_Name = new QLineEdit(QSttGbSafetyEdit);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));
        lineEdit_Name->setFont(font);

        horizontalLayout->addWidget(lineEdit_Name);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_Btn_OK = new QPushButton(QSttGbSafetyEdit);
        m_Btn_OK->setObjectName(QString::fromUtf8("m_Btn_OK"));
        m_Btn_OK->setFont(font);

        horizontalLayout->addWidget(m_Btn_OK);

        m_Btn_Cancel = new QPushButton(QSttGbSafetyEdit);
        m_Btn_Cancel->setObjectName(QString::fromUtf8("m_Btn_Cancel"));
        m_Btn_Cancel->setFont(font);

        horizontalLayout->addWidget(m_Btn_Cancel);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttGbSafetyEdit);

        QMetaObject::connectSlotsByName(QSttGbSafetyEdit);
    } // setupUi

    void retranslateUi(QDialog *QSttGbSafetyEdit)
    {
        QSttGbSafetyEdit->setWindowTitle(QApplication::translate("QSttGbSafetyEdit", "Edit", 0, QApplication::UnicodeUTF8));
        m_label_SelDefaultMsg->setText(QApplication::translate("QSttGbSafetyEdit", "\351\200\211\346\213\251\351\234\200\350\246\201\347\232\204\346\216\245\347\272\277\346\217\220\347\244\272\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label_Name->setText(QApplication::translate("QSttGbSafetyEdit", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_Btn_OK->setText(QApplication::translate("QSttGbSafetyEdit", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_Btn_Cancel->setText(QApplication::translate("QSttGbSafetyEdit", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttGbSafetyEdit: public Ui_QSttGbSafetyEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTGBSAFETYEDIT_H
