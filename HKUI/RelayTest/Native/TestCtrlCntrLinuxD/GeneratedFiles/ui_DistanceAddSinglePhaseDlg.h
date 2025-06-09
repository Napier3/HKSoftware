/********************************************************************************
** Form generated from reading UI file 'DistanceAddSinglePhaseDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCEADDSINGLEPHASEDLG_H
#define UI_DISTANCEADDSINGLEPHASEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
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

class Ui_QDistanceAddSinglePhaseDlg
{
public:
    QGridLayout *gridLayout_2;
    QLabel *m_labZoneType;
    QLabel *m_labX;
    QSettingLineEdit *m_txtR;
    QLabel *m_labZSetting;
    QSettingLineEdit *m_txtTSetting;
    QLabel *m_labZAng;
    QSettingLineEdit *m_txtZSetting;
    QLabel *m_labTSetting;
    QSettingLineEdit *m_txtZAng;
    QLabel *m_labFaultCurrent;
    CExBaseListComboBox *m_cmbZoneType;
    QCheckBox *m_checkAN;
    QLabel *m_labR;
    QSettingLineEdit *m_txtFaultCurrent;
    QCheckBox *m_checkBN;
    QCheckBox *m_checkCN;
    QSpacerItem *horizontalSpacer_4;
    QSettingLineEdit *m_txtX;
    QLabel *m_labFaultType;
    QLabel *m_labFaultDirection;
    QLabel *m_labRate;
    QCheckBox *m_checkReverse;
    QCheckBox *m_checkRate_095;
    QCheckBox *m_checkForward;
    QCheckBox *m_checkRate_105;
    QCheckBox *m_checkRate_070;
    QHBoxLayout *horizontalLayout;
    QCheckBox *m_checkRate_100;
    QSettingLineEdit *m_txtRate_100;
    QLabel *m_labK0Mode;
    QLabel *m_labKlKr;
    QComboBox *m_cmbK0Mode;
    QLabel *m_labAngKx;
    QSettingLineEdit *m_txtKlKr;
    QSettingLineEdit *m_txtAngKx;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnSave;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnclose;
    QVBoxLayout *verticalLayout;
    QLabel *m_labTips;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *m_labType;
    CExBaseListComboBox *m_cmb1;
    QSettingLineEdit *m_txtRel1;
    QLabel *m_labPlus;
    QSettingLineEdit *m_txtPlus;
    QLabel *m_labRel;
    QLabel *m_labMinus;
    QSettingLineEdit *m_txtMinus;
    QSpacerItem *horizontalSpacer_10;

    void setupUi(QDialog *QDistanceAddSinglePhaseDlg)
    {
        if (QDistanceAddSinglePhaseDlg->objectName().isEmpty())
            QDistanceAddSinglePhaseDlg->setObjectName(QString::fromUtf8("QDistanceAddSinglePhaseDlg"));
        QDistanceAddSinglePhaseDlg->resize(802, 429);
        QDistanceAddSinglePhaseDlg->setMaximumSize(QSize(1000, 500));
        QDistanceAddSinglePhaseDlg->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(QDistanceAddSinglePhaseDlg);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_labZoneType = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labZoneType->setObjectName(QString::fromUtf8("m_labZoneType"));

        gridLayout_2->addWidget(m_labZoneType, 4, 7, 1, 1);

        m_labX = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labX->setObjectName(QString::fromUtf8("m_labX"));

        gridLayout_2->addWidget(m_labX, 6, 1, 1, 1);

        m_txtR = new QSettingLineEdit(QDistanceAddSinglePhaseDlg);
        m_txtR->setObjectName(QString::fromUtf8("m_txtR"));
        m_txtR->setMinimumSize(QSize(0, 22));
        m_txtR->setMaximumSize(QSize(130, 22));

        gridLayout_2->addWidget(m_txtR, 4, 3, 1, 1);

        m_labZSetting = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labZSetting->setObjectName(QString::fromUtf8("m_labZSetting"));

        gridLayout_2->addWidget(m_labZSetting, 0, 1, 1, 1);

        m_txtTSetting = new QSettingLineEdit(QDistanceAddSinglePhaseDlg);
        m_txtTSetting->setObjectName(QString::fromUtf8("m_txtTSetting"));
        m_txtTSetting->setMinimumSize(QSize(130, 22));
        m_txtTSetting->setMaximumSize(QSize(130, 22));

        gridLayout_2->addWidget(m_txtTSetting, 0, 9, 1, 1);

        m_labZAng = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labZAng->setObjectName(QString::fromUtf8("m_labZAng"));

        gridLayout_2->addWidget(m_labZAng, 2, 1, 1, 1);

        m_txtZSetting = new QSettingLineEdit(QDistanceAddSinglePhaseDlg);
        m_txtZSetting->setObjectName(QString::fromUtf8("m_txtZSetting"));
        m_txtZSetting->setMinimumSize(QSize(130, 22));
        m_txtZSetting->setMaximumSize(QSize(130, 22));

        gridLayout_2->addWidget(m_txtZSetting, 0, 3, 1, 1);

        m_labTSetting = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labTSetting->setObjectName(QString::fromUtf8("m_labTSetting"));

        gridLayout_2->addWidget(m_labTSetting, 0, 7, 1, 1);

        m_txtZAng = new QSettingLineEdit(QDistanceAddSinglePhaseDlg);
        m_txtZAng->setObjectName(QString::fromUtf8("m_txtZAng"));
        m_txtZAng->setMinimumSize(QSize(0, 22));
        m_txtZAng->setMaximumSize(QSize(130, 22));

        gridLayout_2->addWidget(m_txtZAng, 2, 3, 1, 1);

        m_labFaultCurrent = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labFaultCurrent->setObjectName(QString::fromUtf8("m_labFaultCurrent"));

        gridLayout_2->addWidget(m_labFaultCurrent, 2, 7, 1, 1);

        m_cmbZoneType = new CExBaseListComboBox(QDistanceAddSinglePhaseDlg);
        m_cmbZoneType->setObjectName(QString::fromUtf8("m_cmbZoneType"));
        m_cmbZoneType->setMinimumSize(QSize(0, 22));
        m_cmbZoneType->setMaximumSize(QSize(130, 22));

        gridLayout_2->addWidget(m_cmbZoneType, 4, 9, 1, 1);

        m_checkAN = new QCheckBox(QDistanceAddSinglePhaseDlg);
        m_checkAN->setObjectName(QString::fromUtf8("m_checkAN"));

        gridLayout_2->addWidget(m_checkAN, 8, 3, 1, 1);

        m_labR = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labR->setObjectName(QString::fromUtf8("m_labR"));

        gridLayout_2->addWidget(m_labR, 4, 1, 1, 1);

        m_txtFaultCurrent = new QSettingLineEdit(QDistanceAddSinglePhaseDlg);
        m_txtFaultCurrent->setObjectName(QString::fromUtf8("m_txtFaultCurrent"));
        m_txtFaultCurrent->setMinimumSize(QSize(0, 22));
        m_txtFaultCurrent->setMaximumSize(QSize(130, 22));

        gridLayout_2->addWidget(m_txtFaultCurrent, 2, 9, 1, 1);

        m_checkBN = new QCheckBox(QDistanceAddSinglePhaseDlg);
        m_checkBN->setObjectName(QString::fromUtf8("m_checkBN"));

        gridLayout_2->addWidget(m_checkBN, 8, 5, 1, 1);

        m_checkCN = new QCheckBox(QDistanceAddSinglePhaseDlg);
        m_checkCN->setObjectName(QString::fromUtf8("m_checkCN"));

        gridLayout_2->addWidget(m_checkCN, 8, 7, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 12, 0, 1, 1);

        m_txtX = new QSettingLineEdit(QDistanceAddSinglePhaseDlg);
        m_txtX->setObjectName(QString::fromUtf8("m_txtX"));
        m_txtX->setMinimumSize(QSize(0, 22));
        m_txtX->setMaximumSize(QSize(130, 22));

        gridLayout_2->addWidget(m_txtX, 6, 3, 1, 1);

        m_labFaultType = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labFaultType->setObjectName(QString::fromUtf8("m_labFaultType"));

        gridLayout_2->addWidget(m_labFaultType, 8, 1, 1, 1);

        m_labFaultDirection = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labFaultDirection->setObjectName(QString::fromUtf8("m_labFaultDirection"));

        gridLayout_2->addWidget(m_labFaultDirection, 10, 1, 1, 1);

        m_labRate = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labRate->setObjectName(QString::fromUtf8("m_labRate"));

        gridLayout_2->addWidget(m_labRate, 12, 1, 1, 1);

        m_checkReverse = new QCheckBox(QDistanceAddSinglePhaseDlg);
        m_checkReverse->setObjectName(QString::fromUtf8("m_checkReverse"));

        gridLayout_2->addWidget(m_checkReverse, 10, 5, 1, 1);

        m_checkRate_095 = new QCheckBox(QDistanceAddSinglePhaseDlg);
        m_checkRate_095->setObjectName(QString::fromUtf8("m_checkRate_095"));

        gridLayout_2->addWidget(m_checkRate_095, 12, 5, 1, 1);

        m_checkForward = new QCheckBox(QDistanceAddSinglePhaseDlg);
        m_checkForward->setObjectName(QString::fromUtf8("m_checkForward"));

        gridLayout_2->addWidget(m_checkForward, 10, 3, 1, 1);

        m_checkRate_105 = new QCheckBox(QDistanceAddSinglePhaseDlg);
        m_checkRate_105->setObjectName(QString::fromUtf8("m_checkRate_105"));

        gridLayout_2->addWidget(m_checkRate_105, 12, 3, 1, 1);

        m_checkRate_070 = new QCheckBox(QDistanceAddSinglePhaseDlg);
        m_checkRate_070->setObjectName(QString::fromUtf8("m_checkRate_070"));

        gridLayout_2->addWidget(m_checkRate_070, 12, 7, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_checkRate_100 = new QCheckBox(QDistanceAddSinglePhaseDlg);
        m_checkRate_100->setObjectName(QString::fromUtf8("m_checkRate_100"));
        m_checkRate_100->setMinimumSize(QSize(20, 0));
        m_checkRate_100->setMaximumSize(QSize(20, 16777215));

        horizontalLayout->addWidget(m_checkRate_100);

        m_txtRate_100 = new QSettingLineEdit(QDistanceAddSinglePhaseDlg);
        m_txtRate_100->setObjectName(QString::fromUtf8("m_txtRate_100"));
        m_txtRate_100->setMinimumSize(QSize(100, 22));
        m_txtRate_100->setMaximumSize(QSize(100, 22));

        horizontalLayout->addWidget(m_txtRate_100);


        gridLayout_2->addLayout(horizontalLayout, 12, 9, 1, 1);

        m_labK0Mode = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labK0Mode->setObjectName(QString::fromUtf8("m_labK0Mode"));

        gridLayout_2->addWidget(m_labK0Mode, 14, 1, 1, 1);

        m_labKlKr = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labKlKr->setObjectName(QString::fromUtf8("m_labKlKr"));
        m_labKlKr->setMinimumSize(QSize(80, 0));

        gridLayout_2->addWidget(m_labKlKr, 14, 5, 1, 1);

        m_cmbK0Mode = new QComboBox(QDistanceAddSinglePhaseDlg);
        m_cmbK0Mode->setObjectName(QString::fromUtf8("m_cmbK0Mode"));
        m_cmbK0Mode->setMinimumSize(QSize(170, 22));
        m_cmbK0Mode->setMaximumSize(QSize(170, 22));

        gridLayout_2->addWidget(m_cmbK0Mode, 14, 3, 1, 1);

        m_labAngKx = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labAngKx->setObjectName(QString::fromUtf8("m_labAngKx"));
        m_labAngKx->setMinimumSize(QSize(80, 0));

        gridLayout_2->addWidget(m_labAngKx, 14, 9, 1, 1);

        m_txtKlKr = new QSettingLineEdit(QDistanceAddSinglePhaseDlg);
        m_txtKlKr->setObjectName(QString::fromUtf8("m_txtKlKr"));
        m_txtKlKr->setMinimumSize(QSize(130, 22));
        m_txtKlKr->setMaximumSize(QSize(130, 22));

        gridLayout_2->addWidget(m_txtKlKr, 14, 7, 1, 1);

        m_txtAngKx = new QSettingLineEdit(QDistanceAddSinglePhaseDlg);
        m_txtAngKx->setObjectName(QString::fromUtf8("m_txtAngKx"));
        m_txtAngKx->setMinimumSize(QSize(130, 22));
        m_txtAngKx->setMaximumSize(QSize(130, 22));

        gridLayout_2->addWidget(m_txtAngKx, 14, 10, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 14, 11, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_btnSave = new QPushButton(QDistanceAddSinglePhaseDlg);
        m_btnSave->setObjectName(QString::fromUtf8("m_btnSave"));

        horizontalLayout_2->addWidget(m_btnSave);

        horizontalSpacer_3 = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        m_btnclose = new QPushButton(QDistanceAddSinglePhaseDlg);
        m_btnclose->setObjectName(QString::fromUtf8("m_btnclose"));

        horizontalLayout_2->addWidget(m_btnclose);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_labTips = new QLabel(QDistanceAddSinglePhaseDlg);
        m_labTips->setObjectName(QString::fromUtf8("m_labTips"));
        m_labTips->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(9);
        m_labTips->setFont(font);
        m_labTips->setStyleSheet(QString::fromUtf8("QLabel{border:2px groove rgb(0,0,255);border-radius:10px;background-color: rgb(255,242,204)}"));
        m_labTips->setWordWrap(true);

        verticalLayout->addWidget(m_labTips);

        horizontalSpacer_2 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout_2->addLayout(horizontalLayout_2, 17, 1, 1, 10);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 11, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 13, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 9, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 5, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 7, 1, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_8, 15, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 12, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 12, 4, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 12, 6, 1, 1);

        groupBox = new QGroupBox(QDistanceAddSinglePhaseDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labType = new QLabel(groupBox);
        m_labType->setObjectName(QString::fromUtf8("m_labType"));
        m_labType->setMaximumSize(QSize(16777215, 30));
        m_labType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labType, 0, 0, 1, 1);

        m_cmb1 = new CExBaseListComboBox(groupBox);
        m_cmb1->setObjectName(QString::fromUtf8("m_cmb1"));
        m_cmb1->setMinimumSize(QSize(170, 22));
        m_cmb1->setMaximumSize(QSize(170, 22));

        gridLayout->addWidget(m_cmb1, 0, 1, 1, 2);

        m_txtRel1 = new QSettingLineEdit(groupBox);
        m_txtRel1->setObjectName(QString::fromUtf8("m_txtRel1"));
        m_txtRel1->setMinimumSize(QSize(170, 22));
        m_txtRel1->setMaximumSize(QSize(170, 22));

        gridLayout->addWidget(m_txtRel1, 0, 6, 1, 2);

        m_labPlus = new QLabel(groupBox);
        m_labPlus->setObjectName(QString::fromUtf8("m_labPlus"));

        gridLayout->addWidget(m_labPlus, 2, 0, 1, 1);

        m_txtPlus = new QSettingLineEdit(groupBox);
        m_txtPlus->setObjectName(QString::fromUtf8("m_txtPlus"));
        m_txtPlus->setMinimumSize(QSize(170, 22));
        m_txtPlus->setMaximumSize(QSize(170, 22));

        gridLayout->addWidget(m_txtPlus, 2, 1, 1, 1);

        m_labRel = new QLabel(groupBox);
        m_labRel->setObjectName(QString::fromUtf8("m_labRel"));
        m_labRel->setMaximumSize(QSize(16777215, 30));
        m_labRel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_labRel, 0, 3, 1, 1);

        m_labMinus = new QLabel(groupBox);
        m_labMinus->setObjectName(QString::fromUtf8("m_labMinus"));

        gridLayout->addWidget(m_labMinus, 2, 3, 1, 1);

        m_txtMinus = new QSettingLineEdit(groupBox);
        m_txtMinus->setObjectName(QString::fromUtf8("m_txtMinus"));
        m_txtMinus->setMinimumSize(QSize(170, 22));
        m_txtMinus->setMaximumSize(QSize(170, 22));

        gridLayout->addWidget(m_txtMinus, 2, 6, 1, 1);


        gridLayout_2->addWidget(groupBox, 16, 1, 1, 10);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 12, 8, 1, 1);

        m_labZSetting->raise();
        m_txtZSetting->raise();
        m_labTSetting->raise();
        m_txtTSetting->raise();
        m_labZAng->raise();
        m_txtZAng->raise();
        m_labFaultCurrent->raise();
        m_txtFaultCurrent->raise();
        m_labR->raise();
        m_txtR->raise();
        m_labZoneType->raise();
        m_cmbZoneType->raise();
        m_labX->raise();
        m_txtX->raise();
        m_labFaultType->raise();
        m_checkAN->raise();
        m_checkBN->raise();
        m_checkCN->raise();
        m_labFaultDirection->raise();
        m_checkForward->raise();
        m_checkReverse->raise();
        m_labRate->raise();
        m_checkRate_105->raise();
        m_checkRate_095->raise();
        m_checkRate_070->raise();
        m_labK0Mode->raise();
        m_cmbK0Mode->raise();
        m_labKlKr->raise();
        m_txtKlKr->raise();
        m_labAngKx->raise();
        m_txtAngKx->raise();
        groupBox->raise();

        retranslateUi(QDistanceAddSinglePhaseDlg);

        QMetaObject::connectSlotsByName(QDistanceAddSinglePhaseDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceAddSinglePhaseDlg)
    {
        QDistanceAddSinglePhaseDlg->setWindowTitle(QApplication::translate("QDistanceAddSinglePhaseDlg", "\346\267\273\345\212\240\345\215\225\347\233\270\346\216\245\345\234\260\346\225\205\351\232\234", 0, QApplication::UnicodeUTF8));
        m_labZoneType->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\345\214\272\346\256\265:", 0, QApplication::UnicodeUTF8));
        m_labX->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "X(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labZSetting->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labZAng->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labTSetting->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\346\225\264\345\256\232\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultCurrent->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\347\237\255\350\267\257\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_checkAN->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "AN", 0, QApplication::UnicodeUTF8));
        m_labR->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "R(\316\251):", 0, QApplication::UnicodeUTF8));
        m_checkBN->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "BN", 0, QApplication::UnicodeUTF8));
        m_checkCN->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "CN", 0, QApplication::UnicodeUTF8));
        m_labFaultType->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\346\225\205\351\232\234\347\261\273\345\236\213\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_labFaultDirection->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\346\225\205\351\232\234\346\226\271\345\220\221\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_labRate->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\347\231\276\345\210\206\346\257\224%:", 0, QApplication::UnicodeUTF8));
        m_checkReverse->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\345\217\215\345\220\221", 0, QApplication::UnicodeUTF8));
        m_checkRate_095->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "95.0", 0, QApplication::UnicodeUTF8));
        m_checkForward->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\346\255\243\345\220\221", 0, QApplication::UnicodeUTF8));
        m_checkRate_105->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "105.0", 0, QApplication::UnicodeUTF8));
        m_checkRate_070->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "70.0", 0, QApplication::UnicodeUTF8));
        m_checkRate_100->setText(QString());
        m_labK0Mode->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\351\233\266\345\272\217\350\241\245\345\201\277\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labKlKr->setText(QString());
        m_labAngKx->setText(QString());
        m_btnSave->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnclose->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        m_labTips->setText(QString());
        groupBox->setTitle(QApplication::translate("QDistanceAddSinglePhaseDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_labType->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\350\257\257\345\267\256\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labPlus->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_labRel->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_labMinus->setText(QApplication::translate("QDistanceAddSinglePhaseDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceAddSinglePhaseDlg: public Ui_QDistanceAddSinglePhaseDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCEADDSINGLEPHASEDLG_H
