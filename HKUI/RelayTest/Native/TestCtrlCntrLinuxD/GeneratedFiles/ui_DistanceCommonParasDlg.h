/********************************************************************************
** Form generated from reading UI file 'DistanceCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCECOMMONPARASDLG_H
#define UI_DISTANCECOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDistanceCommonParasDlg
{
public:
    QGridLayout *gridLayout;
    QLabel *m_labCloseTime;
    QSettingLineEdit *m_txtBreakTime;
    QSpacerItem *verticalSpacer_8;
    QSettingLineEdit *m_txtTimeAfter;
    QLabel *m_labBreakTime;
    QLabel *m_labTimeAfter;
    QSettingLineEdit *m_txtCloseTime;
    QSettingLineEdit *m_txtLine;
    QLabel *m_labLine;
    QLabel *m_labVzDefine;
    QComboBox *m_cmbVzDefine;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QComboBox *m_cmbPTPos;
    QSpacerItem *verticalSpacer_6;
    QLabel *m_labPsuVzRef;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QLabel *m_labCTPos;
    QLabel *m_labVzPh;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer;
    QLabel *m_labPTPos;
    QComboBox *m_cmbPsuVzRef;
    QLabel *m_labILoadPh;
    QLabel *m_labILoad;
    QSettingLineEdit *m_txtILoadPh;
    QSettingLineEdit *m_txtVzPh;
    QComboBox *m_cmbCTPos;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOK;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;
    QSettingLineEdit *m_txtILoad;
    QLabel *m_labPreFaultTime;
    QSettingLineEdit *m_txtPreFaultTime;
    QComboBox *m_cmbFaultTrig;
    QLabel *m_labFaultTrig;
    QLabel *m_labFaultTime;
    QSettingLineEdit *m_txtMinTime;
    QLabel *m_labBreaker;
    QSettingLineEdit *m_txtFaultTime;
    QComboBox *m_cmbBreaker;
    QLabel *m_labMinTime;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *QDistanceCommonParasDlg)
    {
        if (QDistanceCommonParasDlg->objectName().isEmpty())
            QDistanceCommonParasDlg->setObjectName(QString::fromUtf8("QDistanceCommonParasDlg"));
        QDistanceCommonParasDlg->resize(848, 377);
        QDistanceCommonParasDlg->setMaximumSize(QSize(1059, 486));
        gridLayout = new QGridLayout(QDistanceCommonParasDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labCloseTime = new QLabel(QDistanceCommonParasDlg);
        m_labCloseTime->setObjectName(QString::fromUtf8("m_labCloseTime"));

        gridLayout->addWidget(m_labCloseTime, 6, 5, 1, 1);

        m_txtBreakTime = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtBreakTime->setObjectName(QString::fromUtf8("m_txtBreakTime"));
        m_txtBreakTime->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtBreakTime, 4, 7, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_8, 17, 1, 1, 1);

        m_txtTimeAfter = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtTimeAfter->setObjectName(QString::fromUtf8("m_txtTimeAfter"));
        m_txtTimeAfter->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtTimeAfter, 6, 3, 1, 1);

        m_labBreakTime = new QLabel(QDistanceCommonParasDlg);
        m_labBreakTime->setObjectName(QString::fromUtf8("m_labBreakTime"));

        gridLayout->addWidget(m_labBreakTime, 4, 5, 1, 1);

        m_labTimeAfter = new QLabel(QDistanceCommonParasDlg);
        m_labTimeAfter->setObjectName(QString::fromUtf8("m_labTimeAfter"));

        gridLayout->addWidget(m_labTimeAfter, 6, 1, 1, 1);

        m_txtCloseTime = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtCloseTime->setObjectName(QString::fromUtf8("m_txtCloseTime"));
        m_txtCloseTime->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtCloseTime, 6, 7, 1, 1);

        m_txtLine = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtLine->setObjectName(QString::fromUtf8("m_txtLine"));
        m_txtLine->setMinimumSize(QSize(200, 0));
        m_txtLine->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtLine, 10, 3, 1, 1);

        m_labLine = new QLabel(QDistanceCommonParasDlg);
        m_labLine->setObjectName(QString::fromUtf8("m_labLine"));
        m_labLine->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_labLine, 10, 1, 1, 1);

        m_labVzDefine = new QLabel(QDistanceCommonParasDlg);
        m_labVzDefine->setObjectName(QString::fromUtf8("m_labVzDefine"));

        gridLayout->addWidget(m_labVzDefine, 10, 5, 1, 1);

        m_cmbVzDefine = new QComboBox(QDistanceCommonParasDlg);
        m_cmbVzDefine->setObjectName(QString::fromUtf8("m_cmbVzDefine"));
        m_cmbVzDefine->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_cmbVzDefine, 10, 7, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 4, 4, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 6, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 16, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 7, 1, 1, 1);

        m_cmbPTPos = new QComboBox(QDistanceCommonParasDlg);
        m_cmbPTPos->setObjectName(QString::fromUtf8("m_cmbPTPos"));
        m_cmbPTPos->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_cmbPTPos, 12, 3, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 13, 1, 1, 1);

        m_labPsuVzRef = new QLabel(QDistanceCommonParasDlg);
        m_labPsuVzRef->setObjectName(QString::fromUtf8("m_labPsuVzRef"));

        gridLayout->addWidget(m_labPsuVzRef, 12, 5, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 5, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 11, 1, 1, 1);

        m_labCTPos = new QLabel(QDistanceCommonParasDlg);
        m_labCTPos->setObjectName(QString::fromUtf8("m_labCTPos"));

        gridLayout->addWidget(m_labCTPos, 14, 1, 1, 1);

        m_labVzPh = new QLabel(QDistanceCommonParasDlg);
        m_labVzPh->setObjectName(QString::fromUtf8("m_labVzPh"));
        m_labVzPh->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_labVzPh, 14, 5, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_7, 15, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        m_labPTPos = new QLabel(QDistanceCommonParasDlg);
        m_labPTPos->setObjectName(QString::fromUtf8("m_labPTPos"));

        gridLayout->addWidget(m_labPTPos, 12, 1, 1, 1);

        m_cmbPsuVzRef = new QComboBox(QDistanceCommonParasDlg);
        m_cmbPsuVzRef->setObjectName(QString::fromUtf8("m_cmbPsuVzRef"));
        m_cmbPsuVzRef->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_cmbPsuVzRef, 12, 7, 1, 1);

        m_labILoadPh = new QLabel(QDistanceCommonParasDlg);
        m_labILoadPh->setObjectName(QString::fromUtf8("m_labILoadPh"));

        gridLayout->addWidget(m_labILoadPh, 18, 1, 1, 1);

        m_labILoad = new QLabel(QDistanceCommonParasDlg);
        m_labILoad->setObjectName(QString::fromUtf8("m_labILoad"));

        gridLayout->addWidget(m_labILoad, 16, 1, 1, 1);

        m_txtILoadPh = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtILoadPh->setObjectName(QString::fromUtf8("m_txtILoadPh"));
        m_txtILoadPh->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtILoadPh, 18, 3, 1, 1);

        m_txtVzPh = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtVzPh->setObjectName(QString::fromUtf8("m_txtVzPh"));
        m_txtVzPh->setMinimumSize(QSize(200, 0));
        m_txtVzPh->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtVzPh, 14, 7, 1, 2);

        m_cmbCTPos = new QComboBox(QDistanceCommonParasDlg);
        m_cmbCTPos->setObjectName(QString::fromUtf8("m_cmbCTPos"));
        m_cmbCTPos->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_cmbCTPos, 14, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 12, 8, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnOK = new QPushButton(QDistanceCommonParasDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        horizontalSpacer_3 = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        m_btnCancel = new QPushButton(QDistanceCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 19, 0, 1, 9);

        m_txtILoad = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtILoad->setObjectName(QString::fromUtf8("m_txtILoad"));
        m_txtILoad->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtILoad, 16, 3, 1, 1);

        m_labPreFaultTime = new QLabel(QDistanceCommonParasDlg);
        m_labPreFaultTime->setObjectName(QString::fromUtf8("m_labPreFaultTime"));

        gridLayout->addWidget(m_labPreFaultTime, 0, 1, 1, 1);

        m_txtPreFaultTime = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtPreFaultTime->setObjectName(QString::fromUtf8("m_txtPreFaultTime"));
        m_txtPreFaultTime->setMinimumSize(QSize(200, 0));
        m_txtPreFaultTime->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtPreFaultTime, 0, 3, 1, 1);

        m_cmbFaultTrig = new QComboBox(QDistanceCommonParasDlg);
        m_cmbFaultTrig->setObjectName(QString::fromUtf8("m_cmbFaultTrig"));
        m_cmbFaultTrig->setMinimumSize(QSize(200, 0));
        m_cmbFaultTrig->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_cmbFaultTrig, 0, 7, 1, 1);

        m_labFaultTrig = new QLabel(QDistanceCommonParasDlg);
        m_labFaultTrig->setObjectName(QString::fromUtf8("m_labFaultTrig"));

        gridLayout->addWidget(m_labFaultTrig, 0, 5, 1, 1);

        m_labFaultTime = new QLabel(QDistanceCommonParasDlg);
        m_labFaultTime->setObjectName(QString::fromUtf8("m_labFaultTime"));

        gridLayout->addWidget(m_labFaultTime, 2, 1, 1, 1);

        m_txtMinTime = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtMinTime->setObjectName(QString::fromUtf8("m_txtMinTime"));
        m_txtMinTime->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtMinTime, 4, 3, 1, 1);

        m_labBreaker = new QLabel(QDistanceCommonParasDlg);
        m_labBreaker->setObjectName(QString::fromUtf8("m_labBreaker"));

        gridLayout->addWidget(m_labBreaker, 2, 5, 1, 1);

        m_txtFaultTime = new QSettingLineEdit(QDistanceCommonParasDlg);
        m_txtFaultTime->setObjectName(QString::fromUtf8("m_txtFaultTime"));
        m_txtFaultTime->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_txtFaultTime, 2, 3, 1, 1);

        m_cmbBreaker = new QComboBox(QDistanceCommonParasDlg);
        m_cmbBreaker->setObjectName(QString::fromUtf8("m_cmbBreaker"));
        m_cmbBreaker->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_cmbBreaker, 2, 7, 1, 1);

        m_labMinTime = new QLabel(QDistanceCommonParasDlg);
        m_labMinTime->setObjectName(QString::fromUtf8("m_labMinTime"));

        gridLayout->addWidget(m_labMinTime, 4, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 14, 6, 1, 1);


        retranslateUi(QDistanceCommonParasDlg);

        QMetaObject::connectSlotsByName(QDistanceCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceCommonParasDlg)
    {
        QDistanceCommonParasDlg->setWindowTitle(QApplication::translate("QDistanceCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_labCloseTime->setText(QApplication::translate("QDistanceCommonParasDlg", "\345\220\210\351\227\270\346\227\266\351\227\264(ms):", 0, QApplication::UnicodeUTF8));
        m_labBreakTime->setText(QApplication::translate("QDistanceCommonParasDlg", "\345\210\206\351\227\270\346\227\266\351\227\264(ms):", 0, QApplication::UnicodeUTF8));
        m_labTimeAfter->setText(QApplication::translate("QDistanceCommonParasDlg", "\344\277\235\346\212\244\345\212\250\344\275\234\345\220\216\346\214\201\347\273\255\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labLine->setText(QApplication::translate("QDistanceCommonParasDlg", "\347\272\277\350\267\257\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labVzDefine->setText(QApplication::translate("QDistanceCommonParasDlg", "\346\212\275\345\217\226\347\224\265\345\216\213\350\276\223\345\207\272\345\256\232\344\271\211:", 0, QApplication::UnicodeUTF8));
        m_labPsuVzRef->setText(QApplication::translate("QDistanceCommonParasDlg", "\346\212\275\345\217\226\347\224\265\345\216\213\345\217\202\350\200\203\347\233\270\345\256\232\344\271\211:", 0, QApplication::UnicodeUTF8));
        m_labCTPos->setText(QApplication::translate("QDistanceCommonParasDlg", "TA\346\255\243\346\236\201\346\200\247:", 0, QApplication::UnicodeUTF8));
        m_labVzPh->setText(QApplication::translate("QDistanceCommonParasDlg", "\346\212\275\345\217\226\347\224\265\345\216\213\347\233\270\350\247\222(\347\233\270\345\257\271\345\217\202\350\200\203\347\233\270):", 0, QApplication::UnicodeUTF8));
        m_labPTPos->setText(QApplication::translate("QDistanceCommonParasDlg", "TV\345\256\211\350\243\205\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        m_labILoadPh->setText(QApplication::translate("QDistanceCommonParasDlg", "\350\264\237\350\215\267\345\212\237\350\247\222:", 0, QApplication::UnicodeUTF8));
        m_labILoad->setText(QApplication::translate("QDistanceCommonParasDlg", "\350\264\237\350\215\267\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QDistanceCommonParasDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDistanceCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        m_labPreFaultTime->setText(QApplication::translate("QDistanceCommonParasDlg", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultTrig->setText(QApplication::translate("QDistanceCommonParasDlg", "\346\225\205\351\232\234\350\247\246\345\217\221\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labFaultTime->setText(QApplication::translate("QDistanceCommonParasDlg", "\346\225\205\351\232\234\346\227\266\351\227\264\350\243\225\345\272\246(s):", 0, QApplication::UnicodeUTF8));
        m_labBreaker->setText(QApplication::translate("QDistanceCommonParasDlg", "\346\226\255\350\267\257\345\231\250\346\250\241\346\213\237:", 0, QApplication::UnicodeUTF8));
        m_labMinTime->setText(QApplication::translate("QDistanceCommonParasDlg", "\346\234\200\345\260\217\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceCommonParasDlg: public Ui_QDistanceCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCECOMMONPARASDLG_H
