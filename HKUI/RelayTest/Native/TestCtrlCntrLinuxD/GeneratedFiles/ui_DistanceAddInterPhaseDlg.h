/********************************************************************************
** Form generated from reading UI file 'DistanceAddInterPhaseDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCEADDINTERPHASEDLG_H
#define UI_DISTANCEADDINTERPHASEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDistanceAddInterPhaseDlg
{
public:
    QGridLayout *gridLayout;
    QLabel *m_labTSetting;
    QSettingLineEdit *m_txtTSetting;
    QSpacerItem *verticalSpacer;
    QSettingLineEdit *m_txtZAng;
    QLabel *m_labFaultCurrent;
    QSettingLineEdit *m_txtFaultCurrent;
    QLabel *m_labR;
    QLabel *m_labZAng;
    QSpacerItem *verticalSpacer_2;
    QLabel *m_labZSetting;
    QSettingLineEdit *m_txtZSetting;
    QCheckBox *m_checkRate_070;
    QLabel *m_labFaultType;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_btnSave;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnclose;
    QVBoxLayout *verticalLayout;
    QLabel *m_labTips;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *m_checkForward;
    QCheckBox *m_checkRate_105;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *horizontalSpacer_8;
    QLabel *m_labZSetting_3;
    QCheckBox *m_checkBC;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QLabel *m_labRate;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *m_checkRate_101;
    QSettingLineEdit *m_txtRate_101;
    QSpacerItem *verticalSpacer_9;
    QCheckBox *m_checkAB;
    QLabel *m_labFaultDirection;
    QSpacerItem *verticalSpacer_3;
    CExBaseListComboBox *m_cmbZoneType;
    QSettingLineEdit *m_txtX;
    QCheckBox *m_checkReverse;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_4;
    QCheckBox *m_checkCA;
    QLabel *m_labZoneType;
    QSettingLineEdit *m_txtR;
    QSpacerItem *verticalSpacer_5;
    QCheckBox *m_checkRate_095;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QSettingLineEdit *m_txtRel;
    QSpacerItem *verticalSpacer_8;
    QLabel *m_labPlus_3;
    QSettingLineEdit *m_txtPlus_3;
    QLabel *m_labMinus_3;
    QSettingLineEdit *m_txtMinus_3;
    QLabel *m_labRel_2;
    CExBaseListComboBox *m_cmb;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_11;
    QLabel *m_labType_2;

    void setupUi(QDialog *QDistanceAddInterPhaseDlg)
    {
        if (QDistanceAddInterPhaseDlg->objectName().isEmpty())
            QDistanceAddInterPhaseDlg->setObjectName(QString::fromUtf8("QDistanceAddInterPhaseDlg"));
        QDistanceAddInterPhaseDlg->resize(586, 500);
        QDistanceAddInterPhaseDlg->setMaximumSize(QSize(1000, 500));
        gridLayout = new QGridLayout(QDistanceAddInterPhaseDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labTSetting = new QLabel(QDistanceAddInterPhaseDlg);
        m_labTSetting->setObjectName(QString::fromUtf8("m_labTSetting"));

        gridLayout->addWidget(m_labTSetting, 0, 5, 1, 1);

        m_txtTSetting = new QSettingLineEdit(QDistanceAddInterPhaseDlg);
        m_txtTSetting->setObjectName(QString::fromUtf8("m_txtTSetting"));
        m_txtTSetting->setMinimumSize(QSize(130, 22));
        m_txtTSetting->setMaximumSize(QSize(130, 22));

        gridLayout->addWidget(m_txtTSetting, 0, 7, 1, 3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        m_txtZAng = new QSettingLineEdit(QDistanceAddInterPhaseDlg);
        m_txtZAng->setObjectName(QString::fromUtf8("m_txtZAng"));
        m_txtZAng->setMinimumSize(QSize(130, 22));
        m_txtZAng->setMaximumSize(QSize(130, 22));

        gridLayout->addWidget(m_txtZAng, 2, 3, 1, 1);

        m_labFaultCurrent = new QLabel(QDistanceAddInterPhaseDlg);
        m_labFaultCurrent->setObjectName(QString::fromUtf8("m_labFaultCurrent"));

        gridLayout->addWidget(m_labFaultCurrent, 2, 5, 1, 1);

        m_txtFaultCurrent = new QSettingLineEdit(QDistanceAddInterPhaseDlg);
        m_txtFaultCurrent->setObjectName(QString::fromUtf8("m_txtFaultCurrent"));
        m_txtFaultCurrent->setMinimumSize(QSize(0, 22));
        m_txtFaultCurrent->setMaximumSize(QSize(130, 22));

        gridLayout->addWidget(m_txtFaultCurrent, 2, 7, 1, 3);

        m_labR = new QLabel(QDistanceAddInterPhaseDlg);
        m_labR->setObjectName(QString::fromUtf8("m_labR"));

        gridLayout->addWidget(m_labR, 4, 1, 1, 1);

        m_labZAng = new QLabel(QDistanceAddInterPhaseDlg);
        m_labZAng->setObjectName(QString::fromUtf8("m_labZAng"));

        gridLayout->addWidget(m_labZAng, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        m_labZSetting = new QLabel(QDistanceAddInterPhaseDlg);
        m_labZSetting->setObjectName(QString::fromUtf8("m_labZSetting"));

        gridLayout->addWidget(m_labZSetting, 0, 1, 1, 1);

        m_txtZSetting = new QSettingLineEdit(QDistanceAddInterPhaseDlg);
        m_txtZSetting->setObjectName(QString::fromUtf8("m_txtZSetting"));
        m_txtZSetting->setMinimumSize(QSize(130, 22));
        m_txtZSetting->setMaximumSize(QSize(130, 22));

        gridLayout->addWidget(m_txtZSetting, 0, 3, 1, 1);

        m_checkRate_070 = new QCheckBox(QDistanceAddInterPhaseDlg);
        m_checkRate_070->setObjectName(QString::fromUtf8("m_checkRate_070"));

        gridLayout->addWidget(m_checkRate_070, 12, 7, 1, 1);

        m_labFaultType = new QLabel(QDistanceAddInterPhaseDlg);
        m_labFaultType->setObjectName(QString::fromUtf8("m_labFaultType"));

        gridLayout->addWidget(m_labFaultType, 8, 1, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_7, 13, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 10, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        m_btnSave = new QPushButton(QDistanceAddInterPhaseDlg);
        m_btnSave->setObjectName(QString::fromUtf8("m_btnSave"));

        horizontalLayout->addWidget(m_btnSave);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnclose = new QPushButton(QDistanceAddInterPhaseDlg);
        m_btnclose->setObjectName(QString::fromUtf8("m_btnclose"));

        horizontalLayout->addWidget(m_btnclose);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_labTips = new QLabel(QDistanceAddInterPhaseDlg);
        m_labTips->setObjectName(QString::fromUtf8("m_labTips"));
        m_labTips->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(9);
        m_labTips->setFont(font);
        m_labTips->setStyleSheet(QString::fromUtf8("QLabel{border:2px groove rgb(0,0,255);border-radius:10px;background-color: rgb(255,242,204)}"));
        m_labTips->setWordWrap(true);

        verticalLayout->addWidget(m_labTips);

        horizontalSpacer_3 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_3);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 16, 0, 1, 12);

        m_checkForward = new QCheckBox(QDistanceAddInterPhaseDlg);
        m_checkForward->setObjectName(QString::fromUtf8("m_checkForward"));

        gridLayout->addWidget(m_checkForward, 10, 3, 1, 1);

        m_checkRate_105 = new QCheckBox(QDistanceAddInterPhaseDlg);
        m_checkRate_105->setObjectName(QString::fromUtf8("m_checkRate_105"));

        gridLayout->addWidget(m_checkRate_105, 12, 3, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_12, 8, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 8, 6, 1, 1);

        m_labZSetting_3 = new QLabel(QDistanceAddInterPhaseDlg);
        m_labZSetting_3->setObjectName(QString::fromUtf8("m_labZSetting_3"));

        gridLayout->addWidget(m_labZSetting_3, 6, 1, 1, 1);

        m_checkBC = new QCheckBox(QDistanceAddInterPhaseDlg);
        m_checkBC->setObjectName(QString::fromUtf8("m_checkBC"));

        gridLayout->addWidget(m_checkBC, 8, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 8, 11, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 11, 1, 1, 1);

        m_labRate = new QLabel(QDistanceAddInterPhaseDlg);
        m_labRate->setObjectName(QString::fromUtf8("m_labRate"));

        gridLayout->addWidget(m_labRate, 12, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_checkRate_101 = new QCheckBox(QDistanceAddInterPhaseDlg);
        m_checkRate_101->setObjectName(QString::fromUtf8("m_checkRate_101"));
        m_checkRate_101->setMinimumSize(QSize(20, 0));
        m_checkRate_101->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_2->addWidget(m_checkRate_101);

        m_txtRate_101 = new QSettingLineEdit(QDistanceAddInterPhaseDlg);
        m_txtRate_101->setObjectName(QString::fromUtf8("m_txtRate_101"));
        m_txtRate_101->setMinimumSize(QSize(100, 22));
        m_txtRate_101->setMaximumSize(QSize(100, 22));

        horizontalLayout_2->addWidget(m_txtRate_101);


        gridLayout->addLayout(horizontalLayout_2, 12, 9, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_9, 14, 1, 1, 1);

        m_checkAB = new QCheckBox(QDistanceAddInterPhaseDlg);
        m_checkAB->setObjectName(QString::fromUtf8("m_checkAB"));

        gridLayout->addWidget(m_checkAB, 8, 3, 1, 1);

        m_labFaultDirection = new QLabel(QDistanceAddInterPhaseDlg);
        m_labFaultDirection->setObjectName(QString::fromUtf8("m_labFaultDirection"));

        gridLayout->addWidget(m_labFaultDirection, 10, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 5, 1, 1, 1);

        m_cmbZoneType = new CExBaseListComboBox(QDistanceAddInterPhaseDlg);
        m_cmbZoneType->setObjectName(QString::fromUtf8("m_cmbZoneType"));
        m_cmbZoneType->setMinimumSize(QSize(130, 22));
        m_cmbZoneType->setMaximumSize(QSize(130, 22));

        gridLayout->addWidget(m_cmbZoneType, 4, 7, 1, 3);

        m_txtX = new QSettingLineEdit(QDistanceAddInterPhaseDlg);
        m_txtX->setObjectName(QString::fromUtf8("m_txtX"));
        m_txtX->setMinimumSize(QSize(130, 22));
        m_txtX->setMaximumSize(QSize(130, 22));

        gridLayout->addWidget(m_txtX, 6, 3, 1, 1);

        m_checkReverse = new QCheckBox(QDistanceAddInterPhaseDlg);
        m_checkReverse->setObjectName(QString::fromUtf8("m_checkReverse"));

        gridLayout->addWidget(m_checkReverse, 10, 5, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 12, 8, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 7, 1, 1, 1);

        m_checkCA = new QCheckBox(QDistanceAddInterPhaseDlg);
        m_checkCA->setObjectName(QString::fromUtf8("m_checkCA"));

        gridLayout->addWidget(m_checkCA, 8, 7, 1, 1);

        m_labZoneType = new QLabel(QDistanceAddInterPhaseDlg);
        m_labZoneType->setObjectName(QString::fromUtf8("m_labZoneType"));

        gridLayout->addWidget(m_labZoneType, 4, 5, 1, 1);

        m_txtR = new QSettingLineEdit(QDistanceAddInterPhaseDlg);
        m_txtR->setObjectName(QString::fromUtf8("m_txtR"));
        m_txtR->setMinimumSize(QSize(130, 22));
        m_txtR->setMaximumSize(QSize(130, 22));

        gridLayout->addWidget(m_txtR, 4, 3, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 9, 1, 1, 1);

        m_checkRate_095 = new QCheckBox(QDistanceAddInterPhaseDlg);
        m_checkRate_095->setObjectName(QString::fromUtf8("m_checkRate_095"));

        gridLayout->addWidget(m_checkRate_095, 12, 5, 1, 1);

        groupBox = new QGroupBox(QDistanceAddInterPhaseDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_txtRel = new QSettingLineEdit(groupBox);
        m_txtRel->setObjectName(QString::fromUtf8("m_txtRel"));
        m_txtRel->setMinimumSize(QSize(170, 22));
        m_txtRel->setMaximumSize(QSize(16777215, 22));
        m_txtRel->setSizeIncrement(QSize(170, 0));

        gridLayout_2->addWidget(m_txtRel, 1, 7, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_8, 2, 0, 1, 1);

        m_labPlus_3 = new QLabel(groupBox);
        m_labPlus_3->setObjectName(QString::fromUtf8("m_labPlus_3"));

        gridLayout_2->addWidget(m_labPlus_3, 3, 0, 1, 1);

        m_txtPlus_3 = new QSettingLineEdit(groupBox);
        m_txtPlus_3->setObjectName(QString::fromUtf8("m_txtPlus_3"));
        m_txtPlus_3->setMinimumSize(QSize(0, 22));
        m_txtPlus_3->setMaximumSize(QSize(170, 22));

        gridLayout_2->addWidget(m_txtPlus_3, 3, 2, 1, 1);

        m_labMinus_3 = new QLabel(groupBox);
        m_labMinus_3->setObjectName(QString::fromUtf8("m_labMinus_3"));

        gridLayout_2->addWidget(m_labMinus_3, 3, 5, 1, 1);

        m_txtMinus_3 = new QSettingLineEdit(groupBox);
        m_txtMinus_3->setObjectName(QString::fromUtf8("m_txtMinus_3"));
        m_txtMinus_3->setMinimumSize(QSize(0, 22));
        m_txtMinus_3->setMaximumSize(QSize(16777215, 22));

        gridLayout_2->addWidget(m_txtMinus_3, 3, 7, 1, 1);

        m_labRel_2 = new QLabel(groupBox);
        m_labRel_2->setObjectName(QString::fromUtf8("m_labRel_2"));
        m_labRel_2->setMaximumSize(QSize(16777215, 30));
        m_labRel_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labRel_2, 1, 5, 1, 1);

        m_cmb = new CExBaseListComboBox(groupBox);
        m_cmb->setObjectName(QString::fromUtf8("m_cmb"));
        m_cmb->setMinimumSize(QSize(170, 22));
        m_cmb->setMaximumSize(QSize(170, 22));

        gridLayout_2->addWidget(m_cmb, 1, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 1, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 1, 3, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 1, 6, 1, 1);

        m_labType_2 = new QLabel(groupBox);
        m_labType_2->setObjectName(QString::fromUtf8("m_labType_2"));
        m_labType_2->setMaximumSize(QSize(16777215, 30));
        m_labType_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labType_2, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox, 15, 1, 1, 10);


        retranslateUi(QDistanceAddInterPhaseDlg);

        QMetaObject::connectSlotsByName(QDistanceAddInterPhaseDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceAddInterPhaseDlg)
    {
        QDistanceAddInterPhaseDlg->setWindowTitle(QApplication::translate("QDistanceAddInterPhaseDlg", "\346\267\273\345\212\240\347\233\270\351\227\264\346\216\245\345\234\260\346\225\205\351\232\234", 0, QApplication::UnicodeUTF8));
        m_labTSetting->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\346\225\264\345\256\232\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultCurrent->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\347\237\255\350\267\257\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labR->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "R(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labZAng->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labZSetting->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_checkRate_070->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "70.0", 0, QApplication::UnicodeUTF8));
        m_labFaultType->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\346\225\205\351\232\234\347\261\273\345\236\213\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_btnSave->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnclose->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        m_labTips->setText(QString());
        m_checkForward->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\346\255\243\345\220\221", 0, QApplication::UnicodeUTF8));
        m_checkRate_105->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "105.0", 0, QApplication::UnicodeUTF8));
        m_labZSetting_3->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "X(\316\251):", 0, QApplication::UnicodeUTF8));
        m_checkBC->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "BC", 0, QApplication::UnicodeUTF8));
        m_labRate->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\347\231\276\345\210\206\346\257\224%:", 0, QApplication::UnicodeUTF8));
        m_checkRate_101->setText(QString());
        m_checkAB->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "AB", 0, QApplication::UnicodeUTF8));
        m_labFaultDirection->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\346\225\205\351\232\234\346\226\271\345\220\221\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_checkReverse->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\345\217\215\345\220\221", 0, QApplication::UnicodeUTF8));
        m_checkCA->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "CA", 0, QApplication::UnicodeUTF8));
        m_labZoneType->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\345\214\272\346\256\265:", 0, QApplication::UnicodeUTF8));
        m_checkRate_095->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "95.0", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QDistanceAddInterPhaseDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_labPlus_3->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_labMinus_3->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
        m_labRel_2->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_labType_2->setText(QApplication::translate("QDistanceAddInterPhaseDlg", "\350\257\257\345\267\256\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceAddInterPhaseDlg: public Ui_QDistanceAddInterPhaseDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCEADDINTERPHASEDLG_H
