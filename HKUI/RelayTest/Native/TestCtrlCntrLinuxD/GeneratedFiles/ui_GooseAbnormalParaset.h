/********************************************************************************
** Form generated from reading UI file 'GooseAbnormalParaset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOOSEABNORMALPARASET_H
#define UI_GOOSEABNORMALPARASET_H

#include <../../../Module/UI/Controls/SttLineEdit.h>
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
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../Module/ScrollCtrl/ScrollComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QGooseAbnormalParaSet
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QScrollComboBox *comboBox_GroupIndex;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *ck_YMAC;
    QSttLineEdit *lne_YMAC;
    QCheckBox *ck_TTL;
    QSttLineEdit *lne_TTL;
    QCheckBox *ck_MMAC;
    QSttLineEdit *lne_MMAC;
    QCheckBox *ck_APPID;
    QLabel *label_6;
    QSttLineEdit *lne_APPID;
    QCheckBox *ck_GcRef;
    QSttLineEdit *lne_GcRef;
    QCheckBox *ck_WT;
    QScrollComboBox *cb_WT;
    QCheckBox *ck_GoID;
    QSttLineEdit *lne_GoID;
    QCheckBox *ck_Test;
    QScrollComboBox *cb_Test;
    QCheckBox *ck_DataSet;
    QSttLineEdit *lne_DataSet;
    QCheckBox *ck_Vlan;
    QLabel *label_7;
    QSttLineEdit *lne_Vlan;
    QCheckBox *ck_SetVerion;
    QSttLineEdit *lne_SetVerion;
    QCheckBox *ck_Net;
    QLabel *label_8;
    QSttLineEdit *lne_Net;
    QCheckBox *ck_St;
    QSttLineEdit *lne_St;
    QLabel *label_3;
    QSttLineEdit *lne_VlanPriority;
    QCheckBox *ck_Sq;
    QSttLineEdit *lne_Sq;
    QLabel *label_4;
    QLabel *label_9;
    QSttLineEdit *lne_TimeQuality;

    void setupUi(QWidget *QGooseAbnormalParaSet)
    {
        if (QGooseAbnormalParaSet->objectName().isEmpty())
            QGooseAbnormalParaSet->setObjectName(QString::fromUtf8("QGooseAbnormalParaSet"));
        QGooseAbnormalParaSet->resize(568, 313);
        gridLayout_2 = new QGridLayout(QGooseAbnormalParaSet);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_5 = new QLabel(QGooseAbnormalParaSet);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        comboBox_GroupIndex = new QScrollComboBox(QGooseAbnormalParaSet);
        comboBox_GroupIndex->setObjectName(QString::fromUtf8("comboBox_GroupIndex"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_GroupIndex->sizePolicy().hasHeightForWidth());
        comboBox_GroupIndex->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBox_GroupIndex);

        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBox = new QGroupBox(QGooseAbnormalParaSet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(3);
        ck_YMAC = new QCheckBox(groupBox);
        ck_YMAC->setObjectName(QString::fromUtf8("ck_YMAC"));

        gridLayout->addWidget(ck_YMAC, 0, 0, 1, 1);

        lne_YMAC = new QSttLineEdit(groupBox);
        lne_YMAC->setObjectName(QString::fromUtf8("lne_YMAC"));
        lne_YMAC->setEnabled(true);

        gridLayout->addWidget(lne_YMAC, 0, 1, 1, 1);

        ck_TTL = new QCheckBox(groupBox);
        ck_TTL->setObjectName(QString::fromUtf8("ck_TTL"));

        gridLayout->addWidget(ck_TTL, 0, 2, 1, 1);

        lne_TTL = new QSttLineEdit(groupBox);
        lne_TTL->setObjectName(QString::fromUtf8("lne_TTL"));

        gridLayout->addWidget(lne_TTL, 0, 4, 1, 1);

        ck_MMAC = new QCheckBox(groupBox);
        ck_MMAC->setObjectName(QString::fromUtf8("ck_MMAC"));

        gridLayout->addWidget(ck_MMAC, 1, 0, 1, 1);

        lne_MMAC = new QSttLineEdit(groupBox);
        lne_MMAC->setObjectName(QString::fromUtf8("lne_MMAC"));

        gridLayout->addWidget(lne_MMAC, 1, 1, 1, 1);

        ck_APPID = new QCheckBox(groupBox);
        ck_APPID->setObjectName(QString::fromUtf8("ck_APPID"));

        gridLayout->addWidget(ck_APPID, 1, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 3, 1, 1);

        lne_APPID = new QSttLineEdit(groupBox);
        lne_APPID->setObjectName(QString::fromUtf8("lne_APPID"));

        gridLayout->addWidget(lne_APPID, 1, 4, 1, 1);

        ck_GcRef = new QCheckBox(groupBox);
        ck_GcRef->setObjectName(QString::fromUtf8("ck_GcRef"));

        gridLayout->addWidget(ck_GcRef, 2, 0, 1, 1);

        lne_GcRef = new QSttLineEdit(groupBox);
        lne_GcRef->setObjectName(QString::fromUtf8("lne_GcRef"));

        gridLayout->addWidget(lne_GcRef, 2, 1, 1, 1);

        ck_WT = new QCheckBox(groupBox);
        ck_WT->setObjectName(QString::fromUtf8("ck_WT"));

        gridLayout->addWidget(ck_WT, 2, 2, 1, 1);

        cb_WT = new QScrollComboBox(groupBox);
        cb_WT->setObjectName(QString::fromUtf8("cb_WT"));

        gridLayout->addWidget(cb_WT, 2, 4, 1, 1);

        ck_GoID = new QCheckBox(groupBox);
        ck_GoID->setObjectName(QString::fromUtf8("ck_GoID"));

        gridLayout->addWidget(ck_GoID, 3, 0, 1, 1);

        lne_GoID = new QSttLineEdit(groupBox);
        lne_GoID->setObjectName(QString::fromUtf8("lne_GoID"));

        gridLayout->addWidget(lne_GoID, 3, 1, 1, 1);

        ck_Test = new QCheckBox(groupBox);
        ck_Test->setObjectName(QString::fromUtf8("ck_Test"));

        gridLayout->addWidget(ck_Test, 3, 2, 1, 1);

        cb_Test = new QScrollComboBox(groupBox);
        cb_Test->setObjectName(QString::fromUtf8("cb_Test"));

        gridLayout->addWidget(cb_Test, 3, 4, 1, 1);

        ck_DataSet = new QCheckBox(groupBox);
        ck_DataSet->setObjectName(QString::fromUtf8("ck_DataSet"));

        gridLayout->addWidget(ck_DataSet, 4, 0, 1, 1);

        lne_DataSet = new QSttLineEdit(groupBox);
        lne_DataSet->setObjectName(QString::fromUtf8("lne_DataSet"));

        gridLayout->addWidget(lne_DataSet, 4, 1, 1, 1);

        ck_Vlan = new QCheckBox(groupBox);
        ck_Vlan->setObjectName(QString::fromUtf8("ck_Vlan"));

        gridLayout->addWidget(ck_Vlan, 4, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 3, 1, 1);

        lne_Vlan = new QSttLineEdit(groupBox);
        lne_Vlan->setObjectName(QString::fromUtf8("lne_Vlan"));

        gridLayout->addWidget(lne_Vlan, 4, 4, 1, 1);

        ck_SetVerion = new QCheckBox(groupBox);
        ck_SetVerion->setObjectName(QString::fromUtf8("ck_SetVerion"));

        gridLayout->addWidget(ck_SetVerion, 5, 0, 1, 1);

        lne_SetVerion = new QSttLineEdit(groupBox);
        lne_SetVerion->setObjectName(QString::fromUtf8("lne_SetVerion"));

        gridLayout->addWidget(lne_SetVerion, 5, 1, 1, 1);

        ck_Net = new QCheckBox(groupBox);
        ck_Net->setObjectName(QString::fromUtf8("ck_Net"));

        gridLayout->addWidget(ck_Net, 5, 2, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 5, 3, 1, 1);

        lne_Net = new QSttLineEdit(groupBox);
        lne_Net->setObjectName(QString::fromUtf8("lne_Net"));

        gridLayout->addWidget(lne_Net, 5, 4, 1, 1);

        ck_St = new QCheckBox(groupBox);
        ck_St->setObjectName(QString::fromUtf8("ck_St"));

        gridLayout->addWidget(ck_St, 6, 0, 1, 1);

        lne_St = new QSttLineEdit(groupBox);
        lne_St->setObjectName(QString::fromUtf8("lne_St"));

        gridLayout->addWidget(lne_St, 6, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 6, 2, 1, 1);

        lne_VlanPriority = new QSttLineEdit(groupBox);
        lne_VlanPriority->setObjectName(QString::fromUtf8("lne_VlanPriority"));

        gridLayout->addWidget(lne_VlanPriority, 6, 4, 1, 1);

        ck_Sq = new QCheckBox(groupBox);
        ck_Sq->setObjectName(QString::fromUtf8("ck_Sq"));

        gridLayout->addWidget(ck_Sq, 7, 0, 1, 1);

        lne_Sq = new QSttLineEdit(groupBox);
        lne_Sq->setObjectName(QString::fromUtf8("lne_Sq"));

        gridLayout->addWidget(lne_Sq, 7, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 7, 2, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 7, 3, 1, 1);

        lne_TimeQuality = new QSttLineEdit(groupBox);
        lne_TimeQuality->setObjectName(QString::fromUtf8("lne_TimeQuality"));

        gridLayout->addWidget(lne_TimeQuality, 7, 4, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 10);

        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(QGooseAbnormalParaSet);

        QMetaObject::connectSlotsByName(QGooseAbnormalParaSet);
    } // setupUi

    void retranslateUi(QWidget *QGooseAbnormalParaSet)
    {
        QGooseAbnormalParaSet->setWindowTitle(QApplication::translate("QGooseAbnormalParaSet", "GooseParaSet", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QGooseAbnormalParaSet", "\347\273\204\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QGooseAbnormalParaSet", "GOOSE\345\216\237\345\247\213\346\212\245\346\226\207", 0, QApplication::UnicodeUTF8));
        ck_YMAC->setText(QApplication::translate("QGooseAbnormalParaSet", "\346\272\220MAC", 0, QApplication::UnicodeUTF8));
        ck_TTL->setText(QApplication::translate("QGooseAbnormalParaSet", "TTL(ms)", 0, QApplication::UnicodeUTF8));
        ck_MMAC->setText(QApplication::translate("QGooseAbnormalParaSet", "\347\233\256\347\232\204MAC", 0, QApplication::UnicodeUTF8));
        ck_APPID->setText(QApplication::translate("QGooseAbnormalParaSet", "APPID", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QGooseAbnormalParaSet", "0x", 0, QApplication::UnicodeUTF8));
        ck_GcRef->setText(QApplication::translate("QGooseAbnormalParaSet", "GcRef", 0, QApplication::UnicodeUTF8));
        ck_WT->setText(QApplication::translate("QGooseAbnormalParaSet", "\345\247\224\346\211\230", 0, QApplication::UnicodeUTF8));
        ck_GoID->setText(QApplication::translate("QGooseAbnormalParaSet", "GoID", 0, QApplication::UnicodeUTF8));
        ck_Test->setText(QApplication::translate("QGooseAbnormalParaSet", "Test", 0, QApplication::UnicodeUTF8));
        ck_DataSet->setText(QApplication::translate("QGooseAbnormalParaSet", "DataSet", 0, QApplication::UnicodeUTF8));
        ck_Vlan->setText(QApplication::translate("QGooseAbnormalParaSet", "Vlan", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QGooseAbnormalParaSet", "0x", 0, QApplication::UnicodeUTF8));
        ck_SetVerion->setText(QApplication::translate("QGooseAbnormalParaSet", "\351\205\215\347\275\256\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        ck_Net->setText(QApplication::translate("QGooseAbnormalParaSet", "\347\275\221\347\273\234\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("QGooseAbnormalParaSet", "0x", 0, QApplication::UnicodeUTF8));
        ck_St->setText(QApplication::translate("QGooseAbnormalParaSet", "St", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QGooseAbnormalParaSet", "Vlan\344\274\230\345\205\210\347\272\247", 0, QApplication::UnicodeUTF8));
        ck_Sq->setText(QApplication::translate("QGooseAbnormalParaSet", "Sq", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QGooseAbnormalParaSet", "\346\227\266\351\227\264\345\223\201\350\264\250", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("QGooseAbnormalParaSet", "0x", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QGooseAbnormalParaSet: public Ui_QGooseAbnormalParaSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOOSEABNORMALPARASET_H
