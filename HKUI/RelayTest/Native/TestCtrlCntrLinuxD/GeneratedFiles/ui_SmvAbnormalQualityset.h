/********************************************************************************
** Form generated from reading UI file 'SmvAbnormalQualityset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMVABNORMALQUALITYSET_H
#define UI_SMVABNORMALQUALITYSET_H

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
#include "../../Controls/SttCheckBox.h"
#include "../../Module/ScrollCtrl/ScrollComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_SmvAbnormalQualitySet
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QScrollComboBox *cmb_bit1;
    QLabel *label_2;
    QScrollComboBox *cmb_bit10;
    QLabel *label_3;
    QScrollComboBox *cmb_bit11;
    QSpacerItem *verticalSpacer;
    QLabel *label_4;
    QScrollComboBox *cmb_bit12;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QScrollComboBox *cmb_bit2;
    QLabel *label_6;
    QScrollComboBox *cmb_bit3;
    QLabel *label_7;
    QScrollComboBox *cmb_bit4;
    QLabel *label_8;
    QScrollComboBox *cmb_bit5;
    QLabel *label_9;
    QScrollComboBox *cmb_bit6;
    QLabel *label_10;
    QScrollComboBox *cmb_bit7;
    QLabel *label_11;
    QScrollComboBox *cmb_bit8;
    QLabel *label_12;
    QScrollComboBox *cmb_bit9;
    QHBoxLayout *horizontalLayout;
    QSttCheckBox *checkBox;
    QScrollComboBox *cmb_DispType;
    QSttLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbn_OK;
    QPushButton *pbn_Cancle;

    void setupUi(QDialog *SmvAbnormalQualitySet)
    {
        if (SmvAbnormalQualitySet->objectName().isEmpty())
            SmvAbnormalQualitySet->setObjectName(QString::fromUtf8("SmvAbnormalQualitySet"));
        SmvAbnormalQualitySet->resize(555, 317);
        gridLayout_4 = new QGridLayout(SmvAbnormalQualitySet);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(SmvAbnormalQualitySet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cmb_bit1 = new QScrollComboBox(groupBox);
        cmb_bit1->setObjectName(QString::fromUtf8("cmb_bit1"));

        gridLayout->addWidget(cmb_bit1, 0, 1, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        cmb_bit10 = new QScrollComboBox(groupBox);
        cmb_bit10->setObjectName(QString::fromUtf8("cmb_bit10"));

        gridLayout->addWidget(cmb_bit10, 1, 1, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        cmb_bit11 = new QScrollComboBox(groupBox);
        cmb_bit11->setObjectName(QString::fromUtf8("cmb_bit11"));

        gridLayout->addWidget(cmb_bit11, 2, 1, 1, 2);

        verticalSpacer = new QSpacerItem(20, 110, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        cmb_bit12 = new QScrollComboBox(groupBox);
        cmb_bit12->setObjectName(QString::fromUtf8("cmb_bit12"));

        gridLayout->addWidget(cmb_bit12, 3, 1, 1, 2);

        gridLayout->setColumnStretch(0, 2);
        gridLayout->setColumnStretch(1, 2);
        gridLayout->setColumnStretch(2, 1);

        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(SmvAbnormalQualitySet);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        cmb_bit2 = new QScrollComboBox(groupBox_2);
        cmb_bit2->setObjectName(QString::fromUtf8("cmb_bit2"));

        gridLayout_2->addWidget(cmb_bit2, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        cmb_bit3 = new QScrollComboBox(groupBox_2);
        cmb_bit3->setObjectName(QString::fromUtf8("cmb_bit3"));

        gridLayout_2->addWidget(cmb_bit3, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        cmb_bit4 = new QScrollComboBox(groupBox_2);
        cmb_bit4->setObjectName(QString::fromUtf8("cmb_bit4"));

        gridLayout_2->addWidget(cmb_bit4, 2, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        cmb_bit5 = new QScrollComboBox(groupBox_2);
        cmb_bit5->setObjectName(QString::fromUtf8("cmb_bit5"));

        gridLayout_2->addWidget(cmb_bit5, 3, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 4, 0, 1, 1);

        cmb_bit6 = new QScrollComboBox(groupBox_2);
        cmb_bit6->setObjectName(QString::fromUtf8("cmb_bit6"));

        gridLayout_2->addWidget(cmb_bit6, 4, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 5, 0, 1, 1);

        cmb_bit7 = new QScrollComboBox(groupBox_2);
        cmb_bit7->setObjectName(QString::fromUtf8("cmb_bit7"));

        gridLayout_2->addWidget(cmb_bit7, 5, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 6, 0, 1, 1);

        cmb_bit8 = new QScrollComboBox(groupBox_2);
        cmb_bit8->setObjectName(QString::fromUtf8("cmb_bit8"));

        gridLayout_2->addWidget(cmb_bit8, 6, 1, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 7, 0, 1, 1);

        cmb_bit9 = new QScrollComboBox(groupBox_2);
        cmb_bit9->setObjectName(QString::fromUtf8("cmb_bit9"));

        gridLayout_2->addWidget(cmb_bit9, 7, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 1, 1, 1);

        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);

        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox = new QSttCheckBox(SmvAbnormalQualitySet);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(false);

        horizontalLayout->addWidget(checkBox);

        cmb_DispType = new QScrollComboBox(SmvAbnormalQualitySet);
        cmb_DispType->setObjectName(QString::fromUtf8("cmb_DispType"));

        horizontalLayout->addWidget(cmb_DispType);

        lineEdit = new QSttLineEdit(SmvAbnormalQualitySet);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbn_OK = new QPushButton(SmvAbnormalQualitySet);
        pbn_OK->setObjectName(QString::fromUtf8("pbn_OK"));

        horizontalLayout->addWidget(pbn_OK);

        pbn_Cancle = new QPushButton(SmvAbnormalQualitySet);
        pbn_Cancle->setObjectName(QString::fromUtf8("pbn_Cancle"));

        horizontalLayout->addWidget(pbn_Cancle);


        gridLayout_4->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(SmvAbnormalQualitySet);

        QMetaObject::connectSlotsByName(SmvAbnormalQualitySet);
    } // setupUi

    void retranslateUi(QDialog *SmvAbnormalQualitySet)
    {
        SmvAbnormalQualitySet->setWindowTitle(QApplication::translate("SmvAbnormalQualitySet", "\345\223\201\350\264\250\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SmvAbnormalQualitySet", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SmvAbnormalQualitySet", "\346\234\211\346\225\210[bit0-1]", 0, QApplication::UnicodeUTF8));
        cmb_bit1->clear();
        cmb_bit1->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "00\357\274\232\345\245\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "01\357\274\232\346\227\240\346\225\210", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "10\357\274\232\344\277\235\347\225\231", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "11\357\274\232\345\217\257\347\226\221", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("SmvAbnormalQualitySet", "\346\272\220[bit10]", 0, QApplication::UnicodeUTF8));
        cmb_bit10->clear();
        cmb_bit10->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\350\277\207\347\250\213", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\350\242\253\345\217\226\344\273\243", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("SmvAbnormalQualitySet", "\346\265\213\350\257\225[bit11]", 0, QApplication::UnicodeUTF8));
        cmb_bit11->clear();
        cmb_bit11->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\350\277\220\350\241\214", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("SmvAbnormalQualitySet", "\346\223\215\344\275\234\345\221\230\351\227\255\351\224\201[bit12]", 0, QApplication::UnicodeUTF8));
        cmb_bit12->clear();
        cmb_bit12->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\344\270\215\351\227\255\351\224\201", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\351\227\255\351\224\201", 0, QApplication::UnicodeUTF8)
        );
        groupBox_2->setTitle(QApplication::translate("SmvAbnormalQualitySet", "\350\257\246\347\273\206\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SmvAbnormalQualitySet", "\346\272\242\345\207\272[bit2]", 0, QApplication::UnicodeUTF8));
        cmb_bit2->clear();
        cmb_bit2->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\346\227\240\346\272\242\345\207\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\346\272\242\345\207\272", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("SmvAbnormalQualitySet", "\350\266\205\345\200\274\345\237\237[bit3]", 0, QApplication::UnicodeUTF8));
        cmb_bit3->clear();
        cmb_bit3->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\346\255\243\345\270\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\350\266\205\345\200\274\345\237\237", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("SmvAbnormalQualitySet", "\345\235\217\345\237\272\345\207\206\345\200\274[bit4]", 0, QApplication::UnicodeUTF8));
        cmb_bit4->clear();
        cmb_bit4->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\346\255\243\345\270\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\345\235\217\345\237\272\345\207\206\345\200\274", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("SmvAbnormalQualitySet", "\346\212\226\345\212\250[bit5]", 0, QApplication::UnicodeUTF8));
        cmb_bit5->clear();
        cmb_bit5->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\346\227\240\346\212\226\345\212\250", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\346\234\211\346\212\226\345\212\250", 0, QApplication::UnicodeUTF8)
        );
        label_9->setText(QApplication::translate("SmvAbnormalQualitySet", "\346\225\205\351\232\234[bit6]", 0, QApplication::UnicodeUTF8));
        cmb_bit6->clear();
        cmb_bit6->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\346\227\240\346\225\205\351\232\234", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\346\234\211\346\225\205\351\232\234", 0, QApplication::UnicodeUTF8)
        );
        label_10->setText(QApplication::translate("SmvAbnormalQualitySet", "\346\227\247\346\225\260\346\215\256[bit7]", 0, QApplication::UnicodeUTF8));
        cmb_bit7->clear();
        cmb_bit7->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\346\227\240\350\266\205\346\227\266", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\346\225\260\346\215\256\350\266\205\346\227\266", 0, QApplication::UnicodeUTF8)
        );
        label_11->setText(QApplication::translate("SmvAbnormalQualitySet", "\344\270\215\344\270\200\350\207\264[bit8]", 0, QApplication::UnicodeUTF8));
        cmb_bit8->clear();
        cmb_bit8->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\344\270\200\350\207\264", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\344\270\215\344\270\200\350\207\264", 0, QApplication::UnicodeUTF8)
        );
        label_12->setText(QApplication::translate("SmvAbnormalQualitySet", "\344\270\215\347\262\276\347\241\256[bit9]", 0, QApplication::UnicodeUTF8));
        cmb_bit9->clear();
        cmb_bit9->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "0\357\274\232\347\262\276\347\241\256", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "1\357\274\232\344\270\215\347\262\276\347\241\256", 0, QApplication::UnicodeUTF8)
        );
        checkBox->setText(QApplication::translate("SmvAbnormalQualitySet", "\344\277\256\346\224\271\345\205\250\351\203\250\351\200\232\351\201\223\345\200\274", 0, QApplication::UnicodeUTF8));
        cmb_DispType->clear();
        cmb_DispType->insertItems(0, QStringList()
         << QApplication::translate("SmvAbnormalQualitySet", "\344\272\214\350\277\233\345\210\266", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "\345\215\201\350\277\233\345\210\266", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SmvAbnormalQualitySet", "\345\215\201\345\205\255\350\277\233\345\210\266", 0, QApplication::UnicodeUTF8)
        );
        pbn_OK->setText(QApplication::translate("SmvAbnormalQualitySet", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        pbn_Cancle->setText(QApplication::translate("SmvAbnormalQualitySet", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SmvAbnormalQualitySet: public Ui_SmvAbnormalQualitySet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMVABNORMALQUALITYSET_H
