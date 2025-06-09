/********************************************************************************
** Form generated from reading UI file 'SmvAbnormalMessageset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMVABNORMALMESSAGESET_H
#define UI_SMVABNORMALMESSAGESET_H

#include <../../../Module/UI/Controls/SttLineEdit.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "../../Module/ScrollCtrl/ScrollComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_SmvAbnormalMessageSet
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QSttLineEdit *lne_sourceMac;
    QLabel *label_8;
    QScrollComboBox *cmb_synchro;
    QLabel *label_2;
    QSttLineEdit *lne_destMAC;
    QLabel *label_9;
    QSttLineEdit *lne_version;
    QLabel *label_3;
    QSttLineEdit *lne_VIanID;
    QLabel *label_10;
    QSttLineEdit *lne_sampledelay;
    QLabel *label_4;
    QSttLineEdit *lne_VIanPriority;
    QLabel *label_11;
    QSttLineEdit *lne_datset;
    QLabel *label_5;
    QSttLineEdit *lne_nettype;
    QLabel *label_12;
    QSttLineEdit *lne_RefrTm;
    QLabel *label_6;
    QSttLineEdit *lne_APPID;
    QLabel *label_7;
    QSttLineEdit *lne_SVID;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbn_Ok;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pbn_Cancle;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *SmvAbnormalMessageSet)
    {
        if (SmvAbnormalMessageSet->objectName().isEmpty())
            SmvAbnormalMessageSet->setObjectName(QString::fromUtf8("SmvAbnormalMessageSet"));
        SmvAbnormalMessageSet->resize(693, 328);
        gridLayout_2 = new QGridLayout(SmvAbnormalMessageSet);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(SmvAbnormalMessageSet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lne_sourceMac = new QSttLineEdit(groupBox);
        lne_sourceMac->setObjectName(QString::fromUtf8("lne_sourceMac"));

        gridLayout->addWidget(lne_sourceMac, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 2, 1, 1);

        cmb_synchro = new QScrollComboBox(groupBox);
        cmb_synchro->setObjectName(QString::fromUtf8("cmb_synchro"));

        gridLayout->addWidget(cmb_synchro, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lne_destMAC = new QSttLineEdit(groupBox);
        lne_destMAC->setObjectName(QString::fromUtf8("lne_destMAC"));

        gridLayout->addWidget(lne_destMAC, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 2, 1, 1);

        lne_version = new QSttLineEdit(groupBox);
        lne_version->setObjectName(QString::fromUtf8("lne_version"));

        gridLayout->addWidget(lne_version, 1, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lne_VIanID = new QSttLineEdit(groupBox);
        lne_VIanID->setObjectName(QString::fromUtf8("lne_VIanID"));

        gridLayout->addWidget(lne_VIanID, 2, 1, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setEnabled(false);

        gridLayout->addWidget(label_10, 2, 2, 1, 1);

        lne_sampledelay = new QSttLineEdit(groupBox);
        lne_sampledelay->setObjectName(QString::fromUtf8("lne_sampledelay"));
        lne_sampledelay->setEnabled(false);

        gridLayout->addWidget(lne_sampledelay, 2, 3, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lne_VIanPriority = new QSttLineEdit(groupBox);
        lne_VIanPriority->setObjectName(QString::fromUtf8("lne_VIanPriority"));

        gridLayout->addWidget(lne_VIanPriority, 3, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 3, 2, 1, 1);

        lne_datset = new QSttLineEdit(groupBox);
        lne_datset->setObjectName(QString::fromUtf8("lne_datset"));

        gridLayout->addWidget(lne_datset, 3, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        lne_nettype = new QSttLineEdit(groupBox);
        lne_nettype->setObjectName(QString::fromUtf8("lne_nettype"));

        gridLayout->addWidget(lne_nettype, 4, 1, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setEnabled(false);

        gridLayout->addWidget(label_12, 4, 2, 1, 1);

        lne_RefrTm = new QSttLineEdit(groupBox);
        lne_RefrTm->setObjectName(QString::fromUtf8("lne_RefrTm"));
        lne_RefrTm->setEnabled(false);

        gridLayout->addWidget(lne_RefrTm, 4, 3, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        lne_APPID = new QSttLineEdit(groupBox);
        lne_APPID->setObjectName(QString::fromUtf8("lne_APPID"));

        gridLayout->addWidget(lne_APPID, 5, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 5, 2, 1, 1);

        lne_SVID = new QSttLineEdit(groupBox);
        lne_SVID->setObjectName(QString::fromUtf8("lne_SVID"));

        gridLayout->addWidget(lne_SVID, 5, 3, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pbn_Ok = new QPushButton(SmvAbnormalMessageSet);
        pbn_Ok->setObjectName(QString::fromUtf8("pbn_Ok"));

        horizontalLayout->addWidget(pbn_Ok);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pbn_Cancle = new QPushButton(SmvAbnormalMessageSet);
        pbn_Cancle->setObjectName(QString::fromUtf8("pbn_Cancle"));

        horizontalLayout->addWidget(pbn_Cancle);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 7);
        gridLayout_2->setRowStretch(1, 1);

        retranslateUi(SmvAbnormalMessageSet);

        QMetaObject::connectSlotsByName(SmvAbnormalMessageSet);
    } // setupUi

    void retranslateUi(QDialog *SmvAbnormalMessageSet)
    {
        SmvAbnormalMessageSet->setWindowTitle(QApplication::translate("SmvAbnormalMessageSet", "\345\274\202\345\270\270\346\212\245\346\226\207\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SmvAbnormalMessageSet", "SV\345\216\237\345\247\213\346\212\245\346\226\207", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SmvAbnormalMessageSet", "\346\272\220MAC", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SmvAbnormalMessageSet", "\345\220\214\346\255\245\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        cmb_synchro->clear();
        cmb_synchro->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalMessageSet", "\344\270\215\345\220\214\346\255\245", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalMessageSet", "\346\234\254\345\234\260\345\220\214\346\255\245", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalMessageSet", "\345\205\250\345\261\200\345\220\214\346\255\245", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("SmvAbnormalMessageSet", "\347\233\256\347\232\204MAC", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("SmvAbnormalMessageSet", "\347\211\210\346\234\254\345\217\267", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SmvAbnormalMessageSet", "Vlan ID    0x", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("SmvAbnormalMessageSet", "\351\207\207\346\240\267\345\273\266\346\227\266", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SmvAbnormalMessageSet", "Vlan Priority", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("SmvAbnormalMessageSet", "DatSet", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SmvAbnormalMessageSet", "\347\275\221\347\273\234\346\240\207\350\257\206   0x", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("SmvAbnormalMessageSet", "RefrTm", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SmvAbnormalMessageSet", "APPID      0x", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SmvAbnormalMessageSet", "SVID", 0, QApplication::UnicodeUTF8));
        pbn_Ok->setText(QApplication::translate("SmvAbnormalMessageSet", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pbn_Cancle->setText(QApplication::translate("SmvAbnormalMessageSet", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SmvAbnormalMessageSet: public Ui_SmvAbnormalMessageSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMVABNORMALMESSAGESET_H
