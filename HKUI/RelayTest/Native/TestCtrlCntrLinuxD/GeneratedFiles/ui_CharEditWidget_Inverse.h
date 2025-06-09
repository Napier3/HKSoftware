/********************************************************************************
** Form generated from reading UI file 'CharEditWidget_Inverse.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAREDITWIDGET_INVERSE_H
#define UI_CHAREDITWIDGET_INVERSE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../Controls/SttLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QCharEditWidget_Inverse
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *layoutTop;
    QLabel *txtName;
    QLabel *txtID;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSelect;
    QLabel *m_txtImg;
    QGroupBox *groupBox_1;
    QGridLayout *_2;
    QLabel *label_26;
    QSttLineEdit *lineEdit_VSet1;
    QLabel *label_34;
    QLabel *label_35;
    QSttLineEdit *lineEdit_TSet2;
    QLabel *label_30;
    QCheckBox *checkBox_Set3;
    QSttLineEdit *lineEdit_TSet3;
    QCheckBox *checkBox_Set2;
    QLabel *label_27;
    QLabel *label_31;
    QSttLineEdit *lineEdit_VSet3;
    QSttLineEdit *lineEdit_VSet2;
    QLabel *label_38;
    QLabel *label_39;
    QSttLineEdit *lineEdit_TSet1;
    QCheckBox *checkBox_Set1;
    QGridLayout *GroupGrid;
    QHBoxLayout *horizontalLayout;
    QLabel *label_CurrValue;
    QSttLineEdit *lineEdit_CurrValue;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Btn_AddUserPoint;
    QPushButton *Btn_ClearUserPoints;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *QCharEditWidget_Inverse)
    {
        if (QCharEditWidget_Inverse->objectName().isEmpty())
            QCharEditWidget_Inverse->setObjectName(QString::fromUtf8("QCharEditWidget_Inverse"));
        QCharEditWidget_Inverse->resize(504, 399);
        verticalLayout = new QVBoxLayout(QCharEditWidget_Inverse);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        layoutTop = new QHBoxLayout();
        layoutTop->setSpacing(6);
        layoutTop->setObjectName(QString::fromUtf8("layoutTop"));
        txtName = new QLabel(QCharEditWidget_Inverse);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setPointSize(10);
        txtName->setFont(font);

        layoutTop->addWidget(txtName);

        txtID = new QLabel(QCharEditWidget_Inverse);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setFont(font);

        layoutTop->addWidget(txtID);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutTop->addItem(horizontalSpacer);

        btnSelect = new QPushButton(QCharEditWidget_Inverse);
        btnSelect->setObjectName(QString::fromUtf8("btnSelect"));
        btnSelect->setFont(font);

        layoutTop->addWidget(btnSelect);


        verticalLayout->addLayout(layoutTop);

        m_txtImg = new QLabel(QCharEditWidget_Inverse);
        m_txtImg->setObjectName(QString::fromUtf8("m_txtImg"));

        verticalLayout->addWidget(m_txtImg);

        groupBox_1 = new QGroupBox(QCharEditWidget_Inverse);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        _2 = new QGridLayout(groupBox_1);
        _2->setSpacing(6);
        _2->setContentsMargins(11, 11, 11, 11);
        _2->setObjectName(QString::fromUtf8("_2"));
        label_26 = new QLabel(groupBox_1);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy);
        label_26->setFont(font);
        label_26->setAlignment(Qt::AlignCenter);

        _2->addWidget(label_26, 0, 1, 1, 1);

        lineEdit_VSet1 = new QSttLineEdit(groupBox_1);
        lineEdit_VSet1->setObjectName(QString::fromUtf8("lineEdit_VSet1"));
        lineEdit_VSet1->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        lineEdit_VSet1->setFont(font1);

        _2->addWidget(lineEdit_VSet1, 2, 1, 1, 1);

        label_34 = new QLabel(groupBox_1);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy1);
        label_34->setFont(font);

        _2->addWidget(label_34, 3, 2, 1, 1);

        label_35 = new QLabel(groupBox_1);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        sizePolicy1.setHeightForWidth(label_35->sizePolicy().hasHeightForWidth());
        label_35->setSizePolicy(sizePolicy1);
        label_35->setFont(font);

        _2->addWidget(label_35, 3, 4, 1, 1);

        lineEdit_TSet2 = new QSttLineEdit(groupBox_1);
        lineEdit_TSet2->setObjectName(QString::fromUtf8("lineEdit_TSet2"));
        lineEdit_TSet2->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_TSet2->setFont(font1);

        _2->addWidget(lineEdit_TSet2, 3, 3, 1, 1);

        label_30 = new QLabel(groupBox_1);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font);

        _2->addWidget(label_30, 2, 2, 1, 1);

        checkBox_Set3 = new QCheckBox(groupBox_1);
        checkBox_Set3->setObjectName(QString::fromUtf8("checkBox_Set3"));
        checkBox_Set3->setFont(font);

        _2->addWidget(checkBox_Set3, 4, 0, 1, 1);

        lineEdit_TSet3 = new QSttLineEdit(groupBox_1);
        lineEdit_TSet3->setObjectName(QString::fromUtf8("lineEdit_TSet3"));
        lineEdit_TSet3->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_TSet3->setFont(font1);

        _2->addWidget(lineEdit_TSet3, 4, 3, 1, 1);

        checkBox_Set2 = new QCheckBox(groupBox_1);
        checkBox_Set2->setObjectName(QString::fromUtf8("checkBox_Set2"));
        checkBox_Set2->setFont(font);

        _2->addWidget(checkBox_Set2, 3, 0, 1, 1);

        label_27 = new QLabel(groupBox_1);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font);
        label_27->setAlignment(Qt::AlignCenter);

        _2->addWidget(label_27, 0, 3, 1, 1);

        label_31 = new QLabel(groupBox_1);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setFont(font);

        _2->addWidget(label_31, 2, 4, 1, 1);

        lineEdit_VSet3 = new QSttLineEdit(groupBox_1);
        lineEdit_VSet3->setObjectName(QString::fromUtf8("lineEdit_VSet3"));
        lineEdit_VSet3->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_VSet3->setFont(font1);

        _2->addWidget(lineEdit_VSet3, 4, 1, 1, 1);

        lineEdit_VSet2 = new QSttLineEdit(groupBox_1);
        lineEdit_VSet2->setObjectName(QString::fromUtf8("lineEdit_VSet2"));
        lineEdit_VSet2->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_VSet2->setFont(font1);

        _2->addWidget(lineEdit_VSet2, 3, 1, 1, 1);

        label_38 = new QLabel(groupBox_1);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        sizePolicy1.setHeightForWidth(label_38->sizePolicy().hasHeightForWidth());
        label_38->setSizePolicy(sizePolicy1);
        label_38->setFont(font);

        _2->addWidget(label_38, 4, 2, 1, 1);

        label_39 = new QLabel(groupBox_1);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        sizePolicy1.setHeightForWidth(label_39->sizePolicy().hasHeightForWidth());
        label_39->setSizePolicy(sizePolicy1);
        label_39->setFont(font);

        _2->addWidget(label_39, 4, 4, 1, 1);

        lineEdit_TSet1 = new QSttLineEdit(groupBox_1);
        lineEdit_TSet1->setObjectName(QString::fromUtf8("lineEdit_TSet1"));
        lineEdit_TSet1->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_TSet1->setFont(font1);

        _2->addWidget(lineEdit_TSet1, 2, 3, 1, 1);

        checkBox_Set1 = new QCheckBox(groupBox_1);
        checkBox_Set1->setObjectName(QString::fromUtf8("checkBox_Set1"));
        checkBox_Set1->setFont(font);

        _2->addWidget(checkBox_Set1, 2, 0, 1, 1);

        label_27->raise();
        label_30->raise();
        checkBox_Set1->raise();
        label_31->raise();
        lineEdit_VSet1->raise();
        lineEdit_TSet1->raise();
        lineEdit_TSet2->raise();
        label_34->raise();
        checkBox_Set2->raise();
        lineEdit_VSet2->raise();
        lineEdit_VSet3->raise();
        checkBox_Set3->raise();
        label_38->raise();
        lineEdit_TSet3->raise();
        label_35->raise();
        label_39->raise();
        label_26->raise();

        verticalLayout->addWidget(groupBox_1);

        GroupGrid = new QGridLayout();
        GroupGrid->setSpacing(6);
        GroupGrid->setObjectName(QString::fromUtf8("GroupGrid"));

        verticalLayout->addLayout(GroupGrid);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_CurrValue = new QLabel(QCharEditWidget_Inverse);
        label_CurrValue->setObjectName(QString::fromUtf8("label_CurrValue"));

        horizontalLayout->addWidget(label_CurrValue);

        lineEdit_CurrValue = new QSttLineEdit(QCharEditWidget_Inverse);
        lineEdit_CurrValue->setObjectName(QString::fromUtf8("lineEdit_CurrValue"));
        lineEdit_CurrValue->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_CurrValue->setFont(font1);

        horizontalLayout->addWidget(lineEdit_CurrValue);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        Btn_AddUserPoint = new QPushButton(QCharEditWidget_Inverse);
        Btn_AddUserPoint->setObjectName(QString::fromUtf8("Btn_AddUserPoint"));

        horizontalLayout->addWidget(Btn_AddUserPoint);

        Btn_ClearUserPoints = new QPushButton(QCharEditWidget_Inverse);
        Btn_ClearUserPoints->setObjectName(QString::fromUtf8("Btn_ClearUserPoints"));

        horizontalLayout->addWidget(Btn_ClearUserPoints);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(QCharEditWidget_Inverse);

        QMetaObject::connectSlotsByName(QCharEditWidget_Inverse);
    } // setupUi

    void retranslateUi(QWidget *QCharEditWidget_Inverse)
    {
        QCharEditWidget_Inverse->setWindowTitle(QApplication::translate("QCharEditWidget_Inverse", "QCharEditWidget_Inverse", 0, QApplication::UnicodeUTF8));
        txtName->setText(QApplication::translate("QCharEditWidget_Inverse", "\346\233\262\347\272\277\345\220\215\347\247\260:", 0, QApplication::UnicodeUTF8));
        txtID->setText(QString());
        btnSelect->setText(QApplication::translate("QCharEditWidget_Inverse", "\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        m_txtImg->setText(QString());
        groupBox_1->setTitle(QString());
        label_26->setText(QApplication::translate("QCharEditWidget_Inverse", "\345\212\250\344\275\234\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("QCharEditWidget_Inverse", "A", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("QCharEditWidget_Inverse", "s", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("QCharEditWidget_Inverse", "A", 0, QApplication::UnicodeUTF8));
        checkBox_Set3->setText(QApplication::translate("QCharEditWidget_Inverse", "3\346\256\265\345\256\232\346\227\266\351\231\220", 0, QApplication::UnicodeUTF8));
        checkBox_Set2->setText(QApplication::translate("QCharEditWidget_Inverse", "2\346\256\265\345\256\232\346\227\266\351\231\220", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("QCharEditWidget_Inverse", "\345\212\250\344\275\234\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("QCharEditWidget_Inverse", "s", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("QCharEditWidget_Inverse", "A", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("QCharEditWidget_Inverse", "s", 0, QApplication::UnicodeUTF8));
        checkBox_Set1->setText(QApplication::translate("QCharEditWidget_Inverse", "1\346\256\265\345\256\232\346\227\266\351\231\220", 0, QApplication::UnicodeUTF8));
        label_CurrValue->setText(QApplication::translate("QCharEditWidget_Inverse", "\347\224\265\346\265\201\345\200\274", 0, QApplication::UnicodeUTF8));
        Btn_AddUserPoint->setText(QApplication::translate("QCharEditWidget_Inverse", "\346\267\273\345\212\240\350\207\252\345\256\232\344\271\211\347\202\271", 0, QApplication::UnicodeUTF8));
        Btn_ClearUserPoints->setText(QApplication::translate("QCharEditWidget_Inverse", "\346\270\205\347\251\272\350\207\252\345\256\232\344\271\211\347\202\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCharEditWidget_Inverse: public Ui_QCharEditWidget_Inverse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAREDITWIDGET_INVERSE_H
