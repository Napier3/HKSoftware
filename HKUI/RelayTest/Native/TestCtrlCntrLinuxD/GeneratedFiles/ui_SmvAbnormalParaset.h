/********************************************************************************
** Form generated from reading UI file 'SmvAbnormalParaset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMVABNORMALPARASET_H
#define UI_SMVABNORMALPARASET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "../../../Module/UI/Controls/SttLineEdit.h"
#include "../../Controls/SttCheckBox.h"
#include "../../Module/ScrollCtrl/ScrollComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QSmvAbnormalParaset
{
public:
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QSttLineEdit *lne_flypointvolt;
    QLabel *label_18;
    QSttLineEdit *lne_indexerr;
    QSttLineEdit *lne_errcmpt;
    QRadioButton *radio_delayoffset;
    QRadioButton *radio_no;
    QRadioButton *radio_lost;
    QSttCheckBox *ck_Ua;
    QSttCheckBox *ck_Uc;
    QLabel *label_7;
    QSttCheckBox *ck_Ub;
    QSttLineEdit *lne_flypoitcurrent;
    QLabel *label_8;
    QSttCheckBox *ck_Ic;
    QRadioButton *radio_jitter;
    QSttCheckBox *ck_Ib;
    QLabel *label_9;
    QSttLineEdit *lne_jitter;
    QRadioButton *radio_errcmpt;
    QSttCheckBox *ck_Ia;
    QSttLineEdit *lne_offsettime;
    QLabel *label_12;
    QRadioButton *radio_delaymodify;
    QSttLineEdit *lne_modifytime;
    QLabel *label_11;
    QRadioButton *radio_indexerr;
    QPushButton *pbn_ChannelSelect;
    QPushButton *pbn_qualitySet;
    QRadioButton *radio_flypoint;
    QRadioButton *radio_qualityinvalid;
    QLabel *label_17;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_19;
    QGroupBox *left_group;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbn_set;
    QPushButton *pbn_MessageSet;
    QGridLayout *gridLayout;
    QScrollComboBox *cmb_APPID;
    QLabel *label_1;
    QScrollComboBox *cmb_sendtype;
    QSttLineEdit *lne_circlepersecond;
    QLabel *label_4;
    QSttLineEdit *lne_sendcircle;
    QSttLineEdit *lne_sendtime;
    QLabel *label_16;
    QLabel *label_2;
    QLabel *label_3;
    QSttCheckBox *checkBox_SelOrgPkgSet;

    void setupUi(QWidget *QSmvAbnormalParaset)
    {
        if (QSmvAbnormalParaset->objectName().isEmpty())
            QSmvAbnormalParaset->setObjectName(QString::fromUtf8("QSmvAbnormalParaset"));
        QSmvAbnormalParaset->resize(717, 300);
        QSmvAbnormalParaset->setMaximumSize(QSize(1024, 768));
        gridLayout_5 = new QGridLayout(QSmvAbnormalParaset);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(QSmvAbnormalParaset);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(label_6, 2, 1, 1, 1);

        lne_flypointvolt = new QSttLineEdit(QSmvAbnormalParaset);
        lne_flypointvolt->setObjectName(QString::fromUtf8("lne_flypointvolt"));

        gridLayout_2->addWidget(lne_flypointvolt, 2, 2, 1, 1);

        label_18 = new QLabel(QSmvAbnormalParaset);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(label_18, 8, 1, 1, 1);

        lne_indexerr = new QSttLineEdit(QSmvAbnormalParaset);
        lne_indexerr->setObjectName(QString::fromUtf8("lne_indexerr"));

        gridLayout_2->addWidget(lne_indexerr, 8, 2, 1, 1);

        lne_errcmpt = new QSttLineEdit(QSmvAbnormalParaset);
        lne_errcmpt->setObjectName(QString::fromUtf8("lne_errcmpt"));

        gridLayout_2->addWidget(lne_errcmpt, 5, 2, 1, 1);

        radio_delayoffset = new QRadioButton(QSmvAbnormalParaset);
        radio_delayoffset->setObjectName(QString::fromUtf8("radio_delayoffset"));

        gridLayout_2->addWidget(radio_delayoffset, 6, 0, 1, 1);

        radio_no = new QRadioButton(QSmvAbnormalParaset);
        radio_no->setObjectName(QString::fromUtf8("radio_no"));

        gridLayout_2->addWidget(radio_no, 0, 0, 1, 1);

        radio_lost = new QRadioButton(QSmvAbnormalParaset);
        radio_lost->setObjectName(QString::fromUtf8("radio_lost"));
        radio_lost->setChecked(true);

        gridLayout_2->addWidget(radio_lost, 1, 0, 1, 1);

        ck_Ua = new QSttCheckBox(QSmvAbnormalParaset);
        ck_Ua->setObjectName(QString::fromUtf8("ck_Ua"));

        gridLayout_2->addWidget(ck_Ua, 2, 4, 1, 1);

        ck_Uc = new QSttCheckBox(QSmvAbnormalParaset);
        ck_Uc->setObjectName(QString::fromUtf8("ck_Uc"));

        gridLayout_2->addWidget(ck_Uc, 2, 6, 1, 1);

        label_7 = new QLabel(QSmvAbnormalParaset);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(label_7, 3, 1, 1, 1);

        ck_Ub = new QSttCheckBox(QSmvAbnormalParaset);
        ck_Ub->setObjectName(QString::fromUtf8("ck_Ub"));

        gridLayout_2->addWidget(ck_Ub, 2, 5, 1, 1);

        lne_flypoitcurrent = new QSttLineEdit(QSmvAbnormalParaset);
        lne_flypoitcurrent->setObjectName(QString::fromUtf8("lne_flypoitcurrent"));

        gridLayout_2->addWidget(lne_flypoitcurrent, 3, 2, 1, 1);

        label_8 = new QLabel(QSmvAbnormalParaset);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(label_8, 4, 1, 1, 1);

        ck_Ic = new QSttCheckBox(QSmvAbnormalParaset);
        ck_Ic->setObjectName(QString::fromUtf8("ck_Ic"));

        gridLayout_2->addWidget(ck_Ic, 3, 6, 1, 1);

        radio_jitter = new QRadioButton(QSmvAbnormalParaset);
        radio_jitter->setObjectName(QString::fromUtf8("radio_jitter"));

        gridLayout_2->addWidget(radio_jitter, 4, 0, 1, 1);

        ck_Ib = new QSttCheckBox(QSmvAbnormalParaset);
        ck_Ib->setObjectName(QString::fromUtf8("ck_Ib"));

        gridLayout_2->addWidget(ck_Ib, 3, 5, 1, 1);

        label_9 = new QLabel(QSmvAbnormalParaset);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(label_9, 5, 1, 1, 1);

        lne_jitter = new QSttLineEdit(QSmvAbnormalParaset);
        lne_jitter->setObjectName(QString::fromUtf8("lne_jitter"));

        gridLayout_2->addWidget(lne_jitter, 4, 2, 1, 1);

        radio_errcmpt = new QRadioButton(QSmvAbnormalParaset);
        radio_errcmpt->setObjectName(QString::fromUtf8("radio_errcmpt"));

        gridLayout_2->addWidget(radio_errcmpt, 5, 0, 1, 1);

        ck_Ia = new QSttCheckBox(QSmvAbnormalParaset);
        ck_Ia->setObjectName(QString::fromUtf8("ck_Ia"));

        gridLayout_2->addWidget(ck_Ia, 3, 4, 1, 1);

        lne_offsettime = new QSttLineEdit(QSmvAbnormalParaset);
        lne_offsettime->setObjectName(QString::fromUtf8("lne_offsettime"));

        gridLayout_2->addWidget(lne_offsettime, 6, 2, 1, 1);

        label_12 = new QLabel(QSmvAbnormalParaset);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(label_12, 7, 1, 1, 1);

        radio_delaymodify = new QRadioButton(QSmvAbnormalParaset);
        radio_delaymodify->setObjectName(QString::fromUtf8("radio_delaymodify"));

        gridLayout_2->addWidget(radio_delaymodify, 7, 0, 1, 1);

        lne_modifytime = new QSttLineEdit(QSmvAbnormalParaset);
        lne_modifytime->setObjectName(QString::fromUtf8("lne_modifytime"));

        gridLayout_2->addWidget(lne_modifytime, 7, 2, 1, 1);

        label_11 = new QLabel(QSmvAbnormalParaset);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(label_11, 6, 1, 1, 1);

        radio_indexerr = new QRadioButton(QSmvAbnormalParaset);
        radio_indexerr->setObjectName(QString::fromUtf8("radio_indexerr"));

        gridLayout_2->addWidget(radio_indexerr, 8, 0, 1, 1);

        pbn_ChannelSelect = new QPushButton(QSmvAbnormalParaset);
        pbn_ChannelSelect->setObjectName(QString::fromUtf8("pbn_ChannelSelect"));

        gridLayout_2->addWidget(pbn_ChannelSelect, 9, 1, 1, 1);

        pbn_qualitySet = new QPushButton(QSmvAbnormalParaset);
        pbn_qualitySet->setObjectName(QString::fromUtf8("pbn_qualitySet"));

        gridLayout_2->addWidget(pbn_qualitySet, 9, 2, 1, 1);

        radio_flypoint = new QRadioButton(QSmvAbnormalParaset);
        radio_flypoint->setObjectName(QString::fromUtf8("radio_flypoint"));

        gridLayout_2->addWidget(radio_flypoint, 2, 0, 1, 1);

        radio_qualityinvalid = new QRadioButton(QSmvAbnormalParaset);
        radio_qualityinvalid->setObjectName(QString::fromUtf8("radio_qualityinvalid"));

        gridLayout_2->addWidget(radio_qualityinvalid, 9, 0, 1, 1);

        label_17 = new QLabel(QSmvAbnormalParaset);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 2, 3, 1, 1);

        label_13 = new QLabel(QSmvAbnormalParaset);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 4, 3, 1, 1);

        label_14 = new QLabel(QSmvAbnormalParaset);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 6, 3, 1, 1);

        label_15 = new QLabel(QSmvAbnormalParaset);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 7, 3, 1, 1);

        label_19 = new QLabel(QSmvAbnormalParaset);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_2->addWidget(label_19, 3, 3, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 0, 0, 2, 2);

        left_group = new QGroupBox(QSmvAbnormalParaset);
        left_group->setObjectName(QString::fromUtf8("left_group"));
        gridLayout_3 = new QGridLayout(left_group);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(121, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        pbn_set = new QPushButton(left_group);
        pbn_set->setObjectName(QString::fromUtf8("pbn_set"));
        pbn_set->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(pbn_set, 0, 1, 1, 1);

        pbn_MessageSet = new QPushButton(left_group);
        pbn_MessageSet->setObjectName(QString::fromUtf8("pbn_MessageSet"));
        pbn_MessageSet->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(pbn_MessageSet, 1, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cmb_APPID = new QScrollComboBox(left_group);
        cmb_APPID->setObjectName(QString::fromUtf8("cmb_APPID"));

        gridLayout->addWidget(cmb_APPID, 0, 1, 1, 1);

        label_1 = new QLabel(left_group);
        label_1->setObjectName(QString::fromUtf8("label_1"));

        gridLayout->addWidget(label_1, 1, 0, 1, 1);

        cmb_sendtype = new QScrollComboBox(left_group);
        cmb_sendtype->setObjectName(QString::fromUtf8("cmb_sendtype"));

        gridLayout->addWidget(cmb_sendtype, 1, 1, 1, 1);

        lne_circlepersecond = new QSttLineEdit(left_group);
        lne_circlepersecond->setObjectName(QString::fromUtf8("lne_circlepersecond"));

        gridLayout->addWidget(lne_circlepersecond, 3, 1, 1, 1);

        label_4 = new QLabel(left_group);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        lne_sendcircle = new QSttLineEdit(left_group);
        lne_sendcircle->setObjectName(QString::fromUtf8("lne_sendcircle"));

        gridLayout->addWidget(lne_sendcircle, 2, 1, 1, 1);

        lne_sendtime = new QSttLineEdit(left_group);
        lne_sendtime->setObjectName(QString::fromUtf8("lne_sendtime"));

        gridLayout->addWidget(lne_sendtime, 4, 1, 1, 1);

        label_16 = new QLabel(left_group);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 0, 0, 1, 1);

        label_2 = new QLabel(left_group);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_3 = new QLabel(left_group);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout, 2, 0, 1, 2);

        checkBox_SelOrgPkgSet = new QSttCheckBox(left_group);
        checkBox_SelOrgPkgSet->setObjectName(QString::fromUtf8("checkBox_SelOrgPkgSet"));

        gridLayout_3->addWidget(checkBox_SelOrgPkgSet, 1, 0, 1, 1);


        gridLayout_5->addWidget(left_group, 0, 2, 2, 1);


        retranslateUi(QSmvAbnormalParaset);

        QMetaObject::connectSlotsByName(QSmvAbnormalParaset);
    } // setupUi

    void retranslateUi(QWidget *QSmvAbnormalParaset)
    {
        QSmvAbnormalParaset->setWindowTitle(QApplication::translate("QSmvAbnormalParaset", "QSmvAbnormalParaset", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("QSmvAbnormalParaset", "\345\274\202\345\270\270\347\224\265\345\216\213", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("QSmvAbnormalParaset", "\345\201\217\345\267\256\345\200\274", 0, QApplication::UnicodeUTF8));
        radio_delayoffset->setText(QApplication::translate("QSmvAbnormalParaset", "\345\273\266\346\227\266\345\201\217\345\267\256", 0, QApplication::UnicodeUTF8));
        radio_no->setText(QApplication::translate("QSmvAbnormalParaset", "\345\220\246", 0, QApplication::UnicodeUTF8));
        radio_lost->setText(QApplication::translate("QSmvAbnormalParaset", "\344\270\242\345\270\247\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        ck_Ua->setText(QApplication::translate("QSmvAbnormalParaset", "Ua", 0, QApplication::UnicodeUTF8));
        ck_Uc->setText(QApplication::translate("QSmvAbnormalParaset", "Uc", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("QSmvAbnormalParaset", "\345\274\202\345\270\270\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        ck_Ub->setText(QApplication::translate("QSmvAbnormalParaset", "Ub", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("QSmvAbnormalParaset", "\346\212\226\345\212\250\345\200\274  ", 0, QApplication::UnicodeUTF8));
        ck_Ic->setText(QApplication::translate("QSmvAbnormalParaset", "Ic", 0, QApplication::UnicodeUTF8));
        radio_jitter->setText(QApplication::translate("QSmvAbnormalParaset", "\346\212\226\345\212\250\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        ck_Ib->setText(QApplication::translate("QSmvAbnormalParaset", "Ib", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("QSmvAbnormalParaset", "\350\267\263\345\217\230\345\200\274", 0, QApplication::UnicodeUTF8));
        radio_errcmpt->setText(QApplication::translate("QSmvAbnormalParaset", "\351\224\231\345\272\217\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        ck_Ia->setText(QApplication::translate("QSmvAbnormalParaset", "Ia", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("QSmvAbnormalParaset", "\345\273\266\346\227\266\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        radio_delaymodify->setText(QApplication::translate("QSmvAbnormalParaset", "\345\273\266\346\227\266\345\217\230\345\214\226", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("QSmvAbnormalParaset", "\345\201\217\345\267\256\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        radio_indexerr->setText(QApplication::translate("QSmvAbnormalParaset", "\345\272\217\345\217\267\345\201\217\345\267\256", 0, QApplication::UnicodeUTF8));
        pbn_ChannelSelect->setText(QApplication::translate("QSmvAbnormalParaset", "\351\200\232\351\201\223\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        pbn_qualitySet->setText(QApplication::translate("QSmvAbnormalParaset", "\345\223\201\350\264\250\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        radio_flypoint->setText(QApplication::translate("QSmvAbnormalParaset", "\351\243\236\347\202\271\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        radio_qualityinvalid->setText(QApplication::translate("QSmvAbnormalParaset", "\345\223\201\350\264\250\345\274\202\345\270\270", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("QSmvAbnormalParaset", "V", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("QSmvAbnormalParaset", "ns", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("QSmvAbnormalParaset", "us", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("QSmvAbnormalParaset", "us", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("QSmvAbnormalParaset", "A", 0, QApplication::UnicodeUTF8));
        left_group->setTitle(QString());
        pbn_set->setText(QApplication::translate("QSmvAbnormalParaset", "\345\274\202\345\270\270\347\202\271\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pbn_MessageSet->setText(QApplication::translate("QSmvAbnormalParaset", "\346\212\245\346\226\207\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("QSmvAbnormalParaset", "\345\274\202\345\270\270\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QSmvAbnormalParaset", "\345\217\221\351\200\201\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("QSmvAbnormalParaset", "\346\212\245\346\226\207\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QSmvAbnormalParaset", "\346\257\217\347\247\222\345\217\221\351\200\201\345\221\250\346\263\242\346\225\260", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QSmvAbnormalParaset", "\345\217\221\351\200\201\345\221\250\346\263\242\346\225\260", 0, QApplication::UnicodeUTF8));
        checkBox_SelOrgPkgSet->setText(QApplication::translate("QSmvAbnormalParaset", "\345\216\237\345\247\213\346\212\245\346\226\207\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSmvAbnormalParaset: public Ui_QSmvAbnormalParaset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMVABNORMALPARASET_H
