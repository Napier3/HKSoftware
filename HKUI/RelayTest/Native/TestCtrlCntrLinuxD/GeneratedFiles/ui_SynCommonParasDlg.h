/********************************************************************************
** Form generated from reading UI file 'SynCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNCOMMONPARASDLG_H
#define UI_SYNCOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QSynCommonParasDlg
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QSettingLineEdit *m_lineUs;
    QLabel *m_labUs;
    QLabel *m_labUg;
    QSettingLineEdit *m_lineUg;
    QLabel *m_labFs;
    QSettingLineEdit *m_lineFs;
    QLabel *m_labPointNum;
    QLabel *m_labUgConnectDef;
    QLineEdit *m_lineAng;
    QLabel *m_labAng;
    QLineEdit *m_lineTmax;
    QComboBox *m_cmbVref;
    QComboBox *m_cmbPointNum;
    QComboBox *m_cmbUgConnectDef;
    QLabel *m_labTmax;
    QLabel *m_labVref;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *m_btnOK;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *QSynCommonParasDlg)
    {
        if (QSynCommonParasDlg->objectName().isEmpty())
            QSynCommonParasDlg->setObjectName(QString::fromUtf8("QSynCommonParasDlg"));
        QSynCommonParasDlg->resize(411, 375);
        gridLayout_3 = new QGridLayout(QSynCommonParasDlg);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        frame = new QFrame(QSynCommonParasDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_lineUs = new QSettingLineEdit(frame);
        m_lineUs->setObjectName(QString::fromUtf8("m_lineUs"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_lineUs->sizePolicy().hasHeightForWidth());
        m_lineUs->setSizePolicy(sizePolicy);
        m_lineUs->setMinimumSize(QSize(200, 0));
        m_lineUs->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_lineUs, 0, 3, 1, 1);

        m_labUs = new QLabel(frame);
        m_labUs->setObjectName(QString::fromUtf8("m_labUs"));

        gridLayout->addWidget(m_labUs, 0, 1, 1, 1);

        m_labUg = new QLabel(frame);
        m_labUg->setObjectName(QString::fromUtf8("m_labUg"));

        gridLayout->addWidget(m_labUg, 2, 1, 1, 1);

        m_lineUg = new QSettingLineEdit(frame);
        m_lineUg->setObjectName(QString::fromUtf8("m_lineUg"));
        sizePolicy.setHeightForWidth(m_lineUg->sizePolicy().hasHeightForWidth());
        m_lineUg->setSizePolicy(sizePolicy);
        m_lineUg->setMinimumSize(QSize(200, 0));
        m_lineUg->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_lineUg, 2, 3, 1, 1);

        m_labFs = new QLabel(frame);
        m_labFs->setObjectName(QString::fromUtf8("m_labFs"));

        gridLayout->addWidget(m_labFs, 1, 1, 1, 1);

        m_lineFs = new QSettingLineEdit(frame);
        m_lineFs->setObjectName(QString::fromUtf8("m_lineFs"));
        sizePolicy.setHeightForWidth(m_lineFs->sizePolicy().hasHeightForWidth());
        m_lineFs->setSizePolicy(sizePolicy);
        m_lineFs->setMinimumSize(QSize(200, 0));
        m_lineFs->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_lineFs, 1, 3, 1, 1);

        m_labPointNum = new QLabel(frame);
        m_labPointNum->setObjectName(QString::fromUtf8("m_labPointNum"));

        gridLayout->addWidget(m_labPointNum, 5, 1, 1, 1);

        m_labUgConnectDef = new QLabel(frame);
        m_labUgConnectDef->setObjectName(QString::fromUtf8("m_labUgConnectDef"));

        gridLayout->addWidget(m_labUgConnectDef, 3, 1, 1, 1);

        m_lineAng = new QLineEdit(frame);
        m_lineAng->setObjectName(QString::fromUtf8("m_lineAng"));
        sizePolicy.setHeightForWidth(m_lineAng->sizePolicy().hasHeightForWidth());
        m_lineAng->setSizePolicy(sizePolicy);
        m_lineAng->setMinimumSize(QSize(200, 0));
        m_lineAng->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_lineAng, 6, 3, 1, 1);

        m_labAng = new QLabel(frame);
        m_labAng->setObjectName(QString::fromUtf8("m_labAng"));

        gridLayout->addWidget(m_labAng, 6, 1, 1, 1);

        m_lineTmax = new QLineEdit(frame);
        m_lineTmax->setObjectName(QString::fromUtf8("m_lineTmax"));
        sizePolicy.setHeightForWidth(m_lineTmax->sizePolicy().hasHeightForWidth());
        m_lineTmax->setSizePolicy(sizePolicy);
        m_lineTmax->setMinimumSize(QSize(200, 0));
        m_lineTmax->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_lineTmax, 7, 3, 1, 1);

        m_cmbVref = new QComboBox(frame);
        m_cmbVref->setObjectName(QString::fromUtf8("m_cmbVref"));
        sizePolicy.setHeightForWidth(m_cmbVref->sizePolicy().hasHeightForWidth());
        m_cmbVref->setSizePolicy(sizePolicy);
        m_cmbVref->setMinimumSize(QSize(200, 0));
        m_cmbVref->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_cmbVref, 4, 3, 1, 1);

        m_cmbPointNum = new QComboBox(frame);
        m_cmbPointNum->setObjectName(QString::fromUtf8("m_cmbPointNum"));
        sizePolicy.setHeightForWidth(m_cmbPointNum->sizePolicy().hasHeightForWidth());
        m_cmbPointNum->setSizePolicy(sizePolicy);
        m_cmbPointNum->setMinimumSize(QSize(200, 0));
        m_cmbPointNum->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_cmbPointNum, 5, 3, 1, 1);

        m_cmbUgConnectDef = new QComboBox(frame);
        m_cmbUgConnectDef->setObjectName(QString::fromUtf8("m_cmbUgConnectDef"));
        sizePolicy.setHeightForWidth(m_cmbUgConnectDef->sizePolicy().hasHeightForWidth());
        m_cmbUgConnectDef->setSizePolicy(sizePolicy);
        m_cmbUgConnectDef->setMinimumSize(QSize(200, 0));
        m_cmbUgConnectDef->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(m_cmbUgConnectDef, 3, 3, 1, 1);

        m_labTmax = new QLabel(frame);
        m_labTmax->setObjectName(QString::fromUtf8("m_labTmax"));

        gridLayout->addWidget(m_labTmax, 7, 1, 1, 1);

        m_labVref = new QLabel(frame);
        m_labVref->setObjectName(QString::fromUtf8("m_labVref"));

        gridLayout->addWidget(m_labVref, 4, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 2, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        m_btnOK = new QPushButton(QSynCommonParasDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnCancel = new QPushButton(QSynCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(QSynCommonParasDlg);

        QMetaObject::connectSlotsByName(QSynCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QSynCommonParasDlg)
    {
        QSynCommonParasDlg->setWindowTitle(QApplication::translate("QSynCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labUs->setText(QApplication::translate("QSynCommonParasDlg", "\347\263\273\347\273\237\344\276\247\351\242\235\345\256\232\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labUg->setText(QApplication::translate("QSynCommonParasDlg", "\345\276\205\345\271\266\346\265\213\351\242\235\345\256\232\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFs->setText(QApplication::translate("QSynCommonParasDlg", "\347\263\273\347\273\237\344\276\247\351\242\235\345\256\232\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labPointNum->setText(QApplication::translate("QSynCommonParasDlg", "\351\222\237\347\202\271\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labUgConnectDef->setText(QApplication::translate("QSynCommonParasDlg", "\347\224\265\345\216\213\345\256\232\344\271\211:", 0, QApplication::UnicodeUTF8));
        m_labAng->setText(QApplication::translate("QSynCommonParasDlg", "\344\270\244\344\276\247\347\233\270\344\275\215\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labTmax->setText(QApplication::translate("QSynCommonParasDlg", "\346\234\200\345\244\247\345\220\214\346\255\245\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labVref->setText(QApplication::translate("QSynCommonParasDlg", "\345\217\202\350\200\203\351\241\271:", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QSynCommonParasDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QSynCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSynCommonParasDlg: public Ui_QSynCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCOMMONPARASDLG_H
