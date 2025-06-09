/********************************************************************************
** Form generated from reading UI file 'DistanceBinarysDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCEBINARYSDLG_H
#define UI_DISTANCEBINARYSDLG_H

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
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDistanceBinarysDlg
{
public:
    QGridLayout *gridLayout;
    QTabWidget *m_tabIn_Out;
    QWidget *m_tabInput;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *m_radio_or;
    QRadioButton *m_radio_and;
    QCheckBox *m_checkD;
    QCheckBox *m_checkB;
    QSpacerItem *verticalSpacer;
    QCheckBox *m_checkC;
    QCheckBox *m_checkA;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *m_checkE;
    QCheckBox *m_checkH;
    QCheckBox *m_checkG;
    QCheckBox *m_checkF;
    QWidget *m_tabOutput;
    QGridLayout *gridLayout_3;
    QLabel *m_lab_B04;
    QLabel *m_lab_B01;
    QComboBox *m_cmb_B01;
    QLabel *m_labDelayTime;
    QLabel *m_lab_B05;
    QLabel *m_lab_B03;
    QComboBox *m_cmb_B05;
    QComboBox *m_cmb_B04;
    QLabel *m_lab_B02;
    QComboBox *m_cmb_B02;
    QLabel *m_lab_B06;
    QComboBox *m_cmb_B07;
    QComboBox *m_cmb_B08;
    QLabel *m_lab_B08;
    QComboBox *m_cmb_B03;
    QLabel *m_lab_SwitchMode;
    QComboBox *m_cmb_B06;
    QSettingLineEdit *m_txtDelayTime;
    QComboBox *m_cmb_SwitchMode;
    QLabel *m_lab_B07;
    QLabel *m_labKeepTime;
    QSettingLineEdit *m_txtKeepTime;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnOK;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QDialog *QDistanceBinarysDlg)
    {
        if (QDistanceBinarysDlg->objectName().isEmpty())
            QDistanceBinarysDlg->setObjectName(QString::fromUtf8("QDistanceBinarysDlg"));
        QDistanceBinarysDlg->resize(400, 400);
        QDistanceBinarysDlg->setMaximumSize(QSize(526, 600));
        gridLayout = new QGridLayout(QDistanceBinarysDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_tabIn_Out = new QTabWidget(QDistanceBinarysDlg);
        m_tabIn_Out->setObjectName(QString::fromUtf8("m_tabIn_Out"));
        m_tabInput = new QWidget();
        m_tabInput->setObjectName(QString::fromUtf8("m_tabInput"));
        gridLayout_2 = new QGridLayout(m_tabInput);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_2 = new QGroupBox(m_tabInput);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("border:0px;\n"
"\n"
""));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_radio_or = new QRadioButton(groupBox_2);
        m_radio_or->setObjectName(QString::fromUtf8("m_radio_or"));

        horizontalLayout_2->addWidget(m_radio_or);

        m_radio_and = new QRadioButton(groupBox_2);
        m_radio_and->setObjectName(QString::fromUtf8("m_radio_and"));

        horizontalLayout_2->addWidget(m_radio_and);


        gridLayout_2->addWidget(groupBox_2, 2, 2, 1, 3);

        m_checkD = new QCheckBox(m_tabInput);
        m_checkD->setObjectName(QString::fromUtf8("m_checkD"));

        gridLayout_2->addWidget(m_checkD, 0, 6, 1, 1);

        m_checkB = new QCheckBox(m_tabInput);
        m_checkB->setObjectName(QString::fromUtf8("m_checkB"));

        gridLayout_2->addWidget(m_checkB, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 2, 1, 1);

        m_checkC = new QCheckBox(m_tabInput);
        m_checkC->setObjectName(QString::fromUtf8("m_checkC"));

        gridLayout_2->addWidget(m_checkC, 0, 4, 1, 1);

        m_checkA = new QCheckBox(m_tabInput);
        m_checkA->setObjectName(QString::fromUtf8("m_checkA"));

        gridLayout_2->addWidget(m_checkA, 0, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 0, 5, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 0, 3, 1, 1);

        m_checkE = new QCheckBox(m_tabInput);
        m_checkE->setObjectName(QString::fromUtf8("m_checkE"));

        gridLayout_2->addWidget(m_checkE, 1, 0, 1, 1);

        m_checkH = new QCheckBox(m_tabInput);
        m_checkH->setObjectName(QString::fromUtf8("m_checkH"));

        gridLayout_2->addWidget(m_checkH, 1, 6, 1, 1);

        m_checkG = new QCheckBox(m_tabInput);
        m_checkG->setObjectName(QString::fromUtf8("m_checkG"));

        gridLayout_2->addWidget(m_checkG, 1, 4, 1, 1);

        m_checkF = new QCheckBox(m_tabInput);
        m_checkF->setObjectName(QString::fromUtf8("m_checkF"));

        gridLayout_2->addWidget(m_checkF, 1, 2, 1, 1);

        m_tabIn_Out->addTab(m_tabInput, QString());
        m_tabOutput = new QWidget();
        m_tabOutput->setObjectName(QString::fromUtf8("m_tabOutput"));
        gridLayout_3 = new QGridLayout(m_tabOutput);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_lab_B04 = new QLabel(m_tabOutput);
        m_lab_B04->setObjectName(QString::fromUtf8("m_lab_B04"));

        gridLayout_3->addWidget(m_lab_B04, 3, 0, 1, 1);

        m_lab_B01 = new QLabel(m_tabOutput);
        m_lab_B01->setObjectName(QString::fromUtf8("m_lab_B01"));

        gridLayout_3->addWidget(m_lab_B01, 0, 0, 1, 1);

        m_cmb_B01 = new QComboBox(m_tabOutput);
        m_cmb_B01->setObjectName(QString::fromUtf8("m_cmb_B01"));
        m_cmb_B01->setMinimumSize(QSize(200, 0));

        gridLayout_3->addWidget(m_cmb_B01, 0, 2, 1, 1);

        m_labDelayTime = new QLabel(m_tabOutput);
        m_labDelayTime->setObjectName(QString::fromUtf8("m_labDelayTime"));

        gridLayout_3->addWidget(m_labDelayTime, 9, 0, 1, 1);

        m_lab_B05 = new QLabel(m_tabOutput);
        m_lab_B05->setObjectName(QString::fromUtf8("m_lab_B05"));

        gridLayout_3->addWidget(m_lab_B05, 4, 0, 1, 1);

        m_lab_B03 = new QLabel(m_tabOutput);
        m_lab_B03->setObjectName(QString::fromUtf8("m_lab_B03"));

        gridLayout_3->addWidget(m_lab_B03, 2, 0, 1, 1);

        m_cmb_B05 = new QComboBox(m_tabOutput);
        m_cmb_B05->setObjectName(QString::fromUtf8("m_cmb_B05"));

        gridLayout_3->addWidget(m_cmb_B05, 4, 2, 1, 1);

        m_cmb_B04 = new QComboBox(m_tabOutput);
        m_cmb_B04->setObjectName(QString::fromUtf8("m_cmb_B04"));

        gridLayout_3->addWidget(m_cmb_B04, 3, 2, 1, 1);

        m_lab_B02 = new QLabel(m_tabOutput);
        m_lab_B02->setObjectName(QString::fromUtf8("m_lab_B02"));

        gridLayout_3->addWidget(m_lab_B02, 1, 0, 1, 1);

        m_cmb_B02 = new QComboBox(m_tabOutput);
        m_cmb_B02->setObjectName(QString::fromUtf8("m_cmb_B02"));

        gridLayout_3->addWidget(m_cmb_B02, 1, 2, 1, 1);

        m_lab_B06 = new QLabel(m_tabOutput);
        m_lab_B06->setObjectName(QString::fromUtf8("m_lab_B06"));

        gridLayout_3->addWidget(m_lab_B06, 5, 0, 1, 1);

        m_cmb_B07 = new QComboBox(m_tabOutput);
        m_cmb_B07->setObjectName(QString::fromUtf8("m_cmb_B07"));

        gridLayout_3->addWidget(m_cmb_B07, 6, 2, 1, 1);

        m_cmb_B08 = new QComboBox(m_tabOutput);
        m_cmb_B08->setObjectName(QString::fromUtf8("m_cmb_B08"));

        gridLayout_3->addWidget(m_cmb_B08, 7, 2, 1, 1);

        m_lab_B08 = new QLabel(m_tabOutput);
        m_lab_B08->setObjectName(QString::fromUtf8("m_lab_B08"));

        gridLayout_3->addWidget(m_lab_B08, 7, 0, 1, 1);

        m_cmb_B03 = new QComboBox(m_tabOutput);
        m_cmb_B03->setObjectName(QString::fromUtf8("m_cmb_B03"));

        gridLayout_3->addWidget(m_cmb_B03, 2, 2, 1, 1);

        m_lab_SwitchMode = new QLabel(m_tabOutput);
        m_lab_SwitchMode->setObjectName(QString::fromUtf8("m_lab_SwitchMode"));
        m_lab_SwitchMode->setMinimumSize(QSize(0, 0));
        m_lab_SwitchMode->setMaximumSize(QSize(110, 16777215));

        gridLayout_3->addWidget(m_lab_SwitchMode, 8, 0, 1, 1);

        m_cmb_B06 = new QComboBox(m_tabOutput);
        m_cmb_B06->setObjectName(QString::fromUtf8("m_cmb_B06"));

        gridLayout_3->addWidget(m_cmb_B06, 5, 2, 1, 1);

        m_txtDelayTime = new QSettingLineEdit(m_tabOutput);
        m_txtDelayTime->setObjectName(QString::fromUtf8("m_txtDelayTime"));

        gridLayout_3->addWidget(m_txtDelayTime, 9, 2, 1, 1);

        m_cmb_SwitchMode = new QComboBox(m_tabOutput);
        m_cmb_SwitchMode->setObjectName(QString::fromUtf8("m_cmb_SwitchMode"));

        gridLayout_3->addWidget(m_cmb_SwitchMode, 8, 2, 1, 1);

        m_lab_B07 = new QLabel(m_tabOutput);
        m_lab_B07->setObjectName(QString::fromUtf8("m_lab_B07"));

        gridLayout_3->addWidget(m_lab_B07, 6, 0, 1, 1);

        m_labKeepTime = new QLabel(m_tabOutput);
        m_labKeepTime->setObjectName(QString::fromUtf8("m_labKeepTime"));

        gridLayout_3->addWidget(m_labKeepTime, 10, 0, 1, 1);

        m_txtKeepTime = new QSettingLineEdit(m_tabOutput);
        m_txtKeepTime->setObjectName(QString::fromUtf8("m_txtKeepTime"));
        m_txtKeepTime->setMinimumSize(QSize(200, 0));
        m_txtKeepTime->setMaximumSize(QSize(200, 16777215));

        gridLayout_3->addWidget(m_txtKeepTime, 10, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        m_tabIn_Out->addTab(m_tabOutput, QString());

        gridLayout->addWidget(m_tabIn_Out, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        m_btnOK = new QPushButton(QDistanceBinarysDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnCancel = new QPushButton(QDistanceBinarysDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 1, 1, 1);


        retranslateUi(QDistanceBinarysDlg);

        m_tabIn_Out->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QDistanceBinarysDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceBinarysDlg)
    {
        QDistanceBinarysDlg->setWindowTitle(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245\343\200\201\345\274\200\345\207\272\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        m_radio_or->setText(QApplication::translate("QDistanceBinarysDlg", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        m_radio_and->setText(QApplication::translate("QDistanceBinarysDlg", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_checkD->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245D", 0, QApplication::UnicodeUTF8));
        m_checkB->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245B", 0, QApplication::UnicodeUTF8));
        m_checkC->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245C", 0, QApplication::UnicodeUTF8));
        m_checkA->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245A", 0, QApplication::UnicodeUTF8));
        m_checkE->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245E", 0, QApplication::UnicodeUTF8));
        m_checkH->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245H", 0, QApplication::UnicodeUTF8));
        m_checkG->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245G", 0, QApplication::UnicodeUTF8));
        m_checkF->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245F", 0, QApplication::UnicodeUTF8));
        m_tabIn_Out->setTabText(m_tabIn_Out->indexOf(m_tabInput), QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_lab_B04->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\2724", 0, QApplication::UnicodeUTF8));
        m_lab_B01->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\2721", 0, QApplication::UnicodeUTF8));
        m_labDelayTime->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\272\344\277\235\346\214\201\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_lab_B05->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\2725", 0, QApplication::UnicodeUTF8));
        m_lab_B03->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\2723", 0, QApplication::UnicodeUTF8));
        m_lab_B02->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\2722", 0, QApplication::UnicodeUTF8));
        m_lab_B06->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\2726", 0, QApplication::UnicodeUTF8));
        m_lab_B08->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\2728", 0, QApplication::UnicodeUTF8));
        m_lab_SwitchMode->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\272\347\277\273\350\275\254\345\220\257\345\212\250\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        m_lab_B07->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\2727", 0, QApplication::UnicodeUTF8));
        m_labKeepTime->setText(QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\272\347\277\273\350\275\254\346\227\266\345\210\273(s)", 0, QApplication::UnicodeUTF8));
        m_tabIn_Out->setTabText(m_tabIn_Out->indexOf(m_tabOutput), QApplication::translate("QDistanceBinarysDlg", "\345\274\200\345\207\272\351\207\217", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QDistanceBinarysDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDistanceBinarysDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceBinarysDlg: public Ui_QDistanceBinarysDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCEBINARYSDLG_H
