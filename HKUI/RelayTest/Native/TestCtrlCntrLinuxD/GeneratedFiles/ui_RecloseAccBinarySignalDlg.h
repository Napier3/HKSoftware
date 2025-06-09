/********************************************************************************
** Form generated from reading UI file 'RecloseAccBinarySignalDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECLOSEACCBINARYSIGNALDLG_H
#define UI_RECLOSEACCBINARYSIGNALDLG_H

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
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QRecloseAccBinarySignalDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *m_tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout;
    QLabel *m_labBinB;
    QLabel *m_labBinA;
    QLabel *m_labBinSelect;
    QLabel *m_labBinC;
    QComboBox *m_cbbBinSelect;
    QLabel *m_labBinE;
    QLabel *m_labBinG;
    CExBaseListComboBox *m_cbbInputA;
    QLabel *m_labBinH;
    QLabel *m_labBinD;
    CExBaseListComboBox *m_cbbInputB;
    CExBaseListComboBox *m_cbbInputE;
    QLabel *m_labBinF;
    CExBaseListComboBox *m_cbbInputD;
    CExBaseListComboBox *m_cbbInputC;
    QSpacerItem *horizontalSpacer;
    CExBaseListComboBox *m_cbbInputG;
    CExBaseListComboBox *m_cbbInputF;
    CExBaseListComboBox *m_cbbInputH;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_5;
    QGridLayout *gridLayout_2;
    QLabel *m_labOutputKeepTime;
    QLabel *m_labBout5;
    QLabel *m_labBout7;
    QLabel *m_labBout6;
    QLabel *m_labBout8;
    QLabel *m_labOutputSwitchMode;
    QLabel *m_labBout3;
    QLabel *m_labOutputDelayTime;
    QLabel *m_labBout1;
    QLabel *m_labBout4;
    CExBaseListComboBox *m_cbbB01;
    CExBaseListComboBox *m_cbbB02;
    CExBaseListComboBox *m_cbbB03;
    QLabel *m_labBout2;
    CExBaseListComboBox *m_cbbB05;
    CExBaseListComboBox *m_cbbB08;
    QLineEdit *m_editOutputDelayTime;
    CExBaseListComboBox *m_cbbB06;
    CExBaseListComboBox *m_cbbOutputSwitchMode;
    CExBaseListComboBox *m_cbbB04;
    QLineEdit *m_editOutputKeepTime;
    CExBaseListComboBox *m_cbbB07;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *QRecloseAccBinarySignalDlg)
    {
        if (QRecloseAccBinarySignalDlg->objectName().isEmpty())
            QRecloseAccBinarySignalDlg->setObjectName(QString::fromUtf8("QRecloseAccBinarySignalDlg"));
        QRecloseAccBinarySignalDlg->resize(350, 422);
        horizontalLayout = new QHBoxLayout(QRecloseAccBinarySignalDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_tabWidget = new QTabWidget(QRecloseAccBinarySignalDlg);
        m_tabWidget->setObjectName(QString::fromUtf8("m_tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, -1, -1, -1);
        m_labBinB = new QLabel(frame);
        m_labBinB->setObjectName(QString::fromUtf8("m_labBinB"));

        gridLayout->addWidget(m_labBinB, 2, 1, 1, 1);

        m_labBinA = new QLabel(frame);
        m_labBinA->setObjectName(QString::fromUtf8("m_labBinA"));

        gridLayout->addWidget(m_labBinA, 1, 1, 1, 1);

        m_labBinSelect = new QLabel(frame);
        m_labBinSelect->setObjectName(QString::fromUtf8("m_labBinSelect"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labBinSelect->sizePolicy().hasHeightForWidth());
        m_labBinSelect->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_labBinSelect, 0, 1, 1, 1);

        m_labBinC = new QLabel(frame);
        m_labBinC->setObjectName(QString::fromUtf8("m_labBinC"));

        gridLayout->addWidget(m_labBinC, 3, 1, 1, 1);

        m_cbbBinSelect = new QComboBox(frame);
        m_cbbBinSelect->setObjectName(QString::fromUtf8("m_cbbBinSelect"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_cbbBinSelect->sizePolicy().hasHeightForWidth());
        m_cbbBinSelect->setSizePolicy(sizePolicy1);
        m_cbbBinSelect->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_cbbBinSelect, 0, 3, 1, 1);

        m_labBinE = new QLabel(frame);
        m_labBinE->setObjectName(QString::fromUtf8("m_labBinE"));

        gridLayout->addWidget(m_labBinE, 5, 1, 1, 1);

        m_labBinG = new QLabel(frame);
        m_labBinG->setObjectName(QString::fromUtf8("m_labBinG"));

        gridLayout->addWidget(m_labBinG, 7, 1, 1, 1);

        m_cbbInputA = new CExBaseListComboBox(frame);
        m_cbbInputA->setObjectName(QString::fromUtf8("m_cbbInputA"));
        sizePolicy1.setHeightForWidth(m_cbbInputA->sizePolicy().hasHeightForWidth());
        m_cbbInputA->setSizePolicy(sizePolicy1);
        m_cbbInputA->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_cbbInputA, 1, 3, 1, 1);

        m_labBinH = new QLabel(frame);
        m_labBinH->setObjectName(QString::fromUtf8("m_labBinH"));

        gridLayout->addWidget(m_labBinH, 8, 1, 1, 1);

        m_labBinD = new QLabel(frame);
        m_labBinD->setObjectName(QString::fromUtf8("m_labBinD"));

        gridLayout->addWidget(m_labBinD, 4, 1, 1, 1);

        m_cbbInputB = new CExBaseListComboBox(frame);
        m_cbbInputB->setObjectName(QString::fromUtf8("m_cbbInputB"));
        sizePolicy1.setHeightForWidth(m_cbbInputB->sizePolicy().hasHeightForWidth());
        m_cbbInputB->setSizePolicy(sizePolicy1);
        m_cbbInputB->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_cbbInputB, 2, 3, 1, 1);

        m_cbbInputE = new CExBaseListComboBox(frame);
        m_cbbInputE->setObjectName(QString::fromUtf8("m_cbbInputE"));
        sizePolicy1.setHeightForWidth(m_cbbInputE->sizePolicy().hasHeightForWidth());
        m_cbbInputE->setSizePolicy(sizePolicy1);
        m_cbbInputE->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_cbbInputE, 5, 3, 1, 1);

        m_labBinF = new QLabel(frame);
        m_labBinF->setObjectName(QString::fromUtf8("m_labBinF"));

        gridLayout->addWidget(m_labBinF, 6, 1, 1, 1);

        m_cbbInputD = new CExBaseListComboBox(frame);
        m_cbbInputD->setObjectName(QString::fromUtf8("m_cbbInputD"));
        sizePolicy1.setHeightForWidth(m_cbbInputD->sizePolicy().hasHeightForWidth());
        m_cbbInputD->setSizePolicy(sizePolicy1);
        m_cbbInputD->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_cbbInputD, 4, 3, 1, 1);

        m_cbbInputC = new CExBaseListComboBox(frame);
        m_cbbInputC->setObjectName(QString::fromUtf8("m_cbbInputC"));
        sizePolicy1.setHeightForWidth(m_cbbInputC->sizePolicy().hasHeightForWidth());
        m_cbbInputC->setSizePolicy(sizePolicy1);
        m_cbbInputC->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_cbbInputC, 3, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        m_cbbInputG = new CExBaseListComboBox(frame);
        m_cbbInputG->setObjectName(QString::fromUtf8("m_cbbInputG"));
        sizePolicy1.setHeightForWidth(m_cbbInputG->sizePolicy().hasHeightForWidth());
        m_cbbInputG->setSizePolicy(sizePolicy1);
        m_cbbInputG->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_cbbInputG, 7, 3, 1, 1);

        m_cbbInputF = new CExBaseListComboBox(frame);
        m_cbbInputF->setObjectName(QString::fromUtf8("m_cbbInputF"));
        sizePolicy1.setHeightForWidth(m_cbbInputF->sizePolicy().hasHeightForWidth());
        m_cbbInputF->setSizePolicy(sizePolicy1);
        m_cbbInputF->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_cbbInputF, 6, 3, 1, 1);

        m_cbbInputH = new CExBaseListComboBox(frame);
        m_cbbInputH->setObjectName(QString::fromUtf8("m_cbbInputH"));
        sizePolicy1.setHeightForWidth(m_cbbInputH->sizePolicy().hasHeightForWidth());
        m_cbbInputH->setSizePolicy(sizePolicy1);
        m_cbbInputH->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_cbbInputH, 8, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 4, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);


        horizontalLayout_2->addWidget(frame);

        m_tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_4 = new QHBoxLayout(tab_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        frame_2 = new QFrame(tab_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_labOutputKeepTime = new QLabel(frame_2);
        m_labOutputKeepTime->setObjectName(QString::fromUtf8("m_labOutputKeepTime"));

        gridLayout_2->addWidget(m_labOutputKeepTime, 9, 1, 1, 1);

        m_labBout5 = new QLabel(frame_2);
        m_labBout5->setObjectName(QString::fromUtf8("m_labBout5"));

        gridLayout_2->addWidget(m_labBout5, 4, 1, 1, 1);

        m_labBout7 = new QLabel(frame_2);
        m_labBout7->setObjectName(QString::fromUtf8("m_labBout7"));

        gridLayout_2->addWidget(m_labBout7, 6, 1, 1, 1);

        m_labBout6 = new QLabel(frame_2);
        m_labBout6->setObjectName(QString::fromUtf8("m_labBout6"));

        gridLayout_2->addWidget(m_labBout6, 5, 1, 1, 1);

        m_labBout8 = new QLabel(frame_2);
        m_labBout8->setObjectName(QString::fromUtf8("m_labBout8"));

        gridLayout_2->addWidget(m_labBout8, 7, 1, 1, 1);

        m_labOutputSwitchMode = new QLabel(frame_2);
        m_labOutputSwitchMode->setObjectName(QString::fromUtf8("m_labOutputSwitchMode"));

        gridLayout_2->addWidget(m_labOutputSwitchMode, 8, 1, 1, 1);

        m_labBout3 = new QLabel(frame_2);
        m_labBout3->setObjectName(QString::fromUtf8("m_labBout3"));

        gridLayout_2->addWidget(m_labBout3, 2, 1, 1, 1);

        m_labOutputDelayTime = new QLabel(frame_2);
        m_labOutputDelayTime->setObjectName(QString::fromUtf8("m_labOutputDelayTime"));

        gridLayout_2->addWidget(m_labOutputDelayTime, 10, 1, 1, 1);

        m_labBout1 = new QLabel(frame_2);
        m_labBout1->setObjectName(QString::fromUtf8("m_labBout1"));

        gridLayout_2->addWidget(m_labBout1, 0, 1, 1, 1);

        m_labBout4 = new QLabel(frame_2);
        m_labBout4->setObjectName(QString::fromUtf8("m_labBout4"));

        gridLayout_2->addWidget(m_labBout4, 3, 1, 1, 1);

        m_cbbB01 = new CExBaseListComboBox(frame_2);
        m_cbbB01->setObjectName(QString::fromUtf8("m_cbbB01"));
        sizePolicy1.setHeightForWidth(m_cbbB01->sizePolicy().hasHeightForWidth());
        m_cbbB01->setSizePolicy(sizePolicy1);
        m_cbbB01->setMinimumSize(QSize(0, 0));
        m_cbbB01->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbB01, 0, 3, 1, 1);

        m_cbbB02 = new CExBaseListComboBox(frame_2);
        m_cbbB02->setObjectName(QString::fromUtf8("m_cbbB02"));
        sizePolicy1.setHeightForWidth(m_cbbB02->sizePolicy().hasHeightForWidth());
        m_cbbB02->setSizePolicy(sizePolicy1);
        m_cbbB02->setMinimumSize(QSize(0, 0));
        m_cbbB02->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbB02, 1, 3, 1, 1);

        m_cbbB03 = new CExBaseListComboBox(frame_2);
        m_cbbB03->setObjectName(QString::fromUtf8("m_cbbB03"));
        sizePolicy1.setHeightForWidth(m_cbbB03->sizePolicy().hasHeightForWidth());
        m_cbbB03->setSizePolicy(sizePolicy1);
        m_cbbB03->setMinimumSize(QSize(0, 0));
        m_cbbB03->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbB03, 2, 3, 1, 1);

        m_labBout2 = new QLabel(frame_2);
        m_labBout2->setObjectName(QString::fromUtf8("m_labBout2"));

        gridLayout_2->addWidget(m_labBout2, 1, 1, 1, 1);

        m_cbbB05 = new CExBaseListComboBox(frame_2);
        m_cbbB05->setObjectName(QString::fromUtf8("m_cbbB05"));
        sizePolicy1.setHeightForWidth(m_cbbB05->sizePolicy().hasHeightForWidth());
        m_cbbB05->setSizePolicy(sizePolicy1);
        m_cbbB05->setMinimumSize(QSize(0, 0));
        m_cbbB05->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbB05, 4, 3, 1, 1);

        m_cbbB08 = new CExBaseListComboBox(frame_2);
        m_cbbB08->setObjectName(QString::fromUtf8("m_cbbB08"));
        sizePolicy1.setHeightForWidth(m_cbbB08->sizePolicy().hasHeightForWidth());
        m_cbbB08->setSizePolicy(sizePolicy1);
        m_cbbB08->setMinimumSize(QSize(0, 0));
        m_cbbB08->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbB08, 7, 3, 1, 1);

        m_editOutputDelayTime = new QLineEdit(frame_2);
        m_editOutputDelayTime->setObjectName(QString::fromUtf8("m_editOutputDelayTime"));
        sizePolicy1.setHeightForWidth(m_editOutputDelayTime->sizePolicy().hasHeightForWidth());
        m_editOutputDelayTime->setSizePolicy(sizePolicy1);
        m_editOutputDelayTime->setMinimumSize(QSize(0, 0));
        m_editOutputDelayTime->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editOutputDelayTime, 10, 3, 1, 1);

        m_cbbB06 = new CExBaseListComboBox(frame_2);
        m_cbbB06->setObjectName(QString::fromUtf8("m_cbbB06"));
        sizePolicy1.setHeightForWidth(m_cbbB06->sizePolicy().hasHeightForWidth());
        m_cbbB06->setSizePolicy(sizePolicy1);
        m_cbbB06->setMinimumSize(QSize(0, 0));
        m_cbbB06->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbB06, 5, 3, 1, 1);

        m_cbbOutputSwitchMode = new CExBaseListComboBox(frame_2);
        m_cbbOutputSwitchMode->setObjectName(QString::fromUtf8("m_cbbOutputSwitchMode"));
        sizePolicy1.setHeightForWidth(m_cbbOutputSwitchMode->sizePolicy().hasHeightForWidth());
        m_cbbOutputSwitchMode->setSizePolicy(sizePolicy1);
        m_cbbOutputSwitchMode->setMinimumSize(QSize(0, 0));
        m_cbbOutputSwitchMode->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbOutputSwitchMode, 8, 3, 1, 1);

        m_cbbB04 = new CExBaseListComboBox(frame_2);
        m_cbbB04->setObjectName(QString::fromUtf8("m_cbbB04"));
        sizePolicy1.setHeightForWidth(m_cbbB04->sizePolicy().hasHeightForWidth());
        m_cbbB04->setSizePolicy(sizePolicy1);
        m_cbbB04->setMinimumSize(QSize(0, 0));
        m_cbbB04->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbB04, 3, 3, 1, 1);

        m_editOutputKeepTime = new QLineEdit(frame_2);
        m_editOutputKeepTime->setObjectName(QString::fromUtf8("m_editOutputKeepTime"));
        sizePolicy1.setHeightForWidth(m_editOutputKeepTime->sizePolicy().hasHeightForWidth());
        m_editOutputKeepTime->setSizePolicy(sizePolicy1);
        m_editOutputKeepTime->setMinimumSize(QSize(0, 0));
        m_editOutputKeepTime->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editOutputKeepTime, 9, 3, 1, 1);

        m_cbbB07 = new CExBaseListComboBox(frame_2);
        m_cbbB07->setObjectName(QString::fromUtf8("m_cbbB07"));
        sizePolicy1.setHeightForWidth(m_cbbB07->sizePolicy().hasHeightForWidth());
        m_cbbB07->setSizePolicy(sizePolicy1);
        m_cbbB07->setMinimumSize(QSize(0, 0));
        m_cbbB07->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbB07, 6, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 4, 1, 1);


        horizontalLayout_5->addLayout(gridLayout_2);


        horizontalLayout_4->addWidget(frame_2);

        m_tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(m_tabWidget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        m_btnOk = new QPushButton(QRecloseAccBinarySignalDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        sizePolicy1.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(m_btnOk);

        horizontalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        m_btnCancel = new QPushButton(QRecloseAccBinarySignalDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy1.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(m_btnCancel);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_6);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QRecloseAccBinarySignalDlg);

        m_tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QRecloseAccBinarySignalDlg);
    } // setupUi

    void retranslateUi(QDialog *QRecloseAccBinarySignalDlg)
    {
        QRecloseAccBinarySignalDlg->setWindowTitle(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\263\351\207\217", 0, QApplication::UnicodeUTF8));
        m_labBinB->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245B:", 0, QApplication::UnicodeUTF8));
        m_labBinA->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245A:", 0, QApplication::UnicodeUTF8));
        m_labBinSelect->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_labBinC->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245C:", 0, QApplication::UnicodeUTF8));
        m_labBinE->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245E:", 0, QApplication::UnicodeUTF8));
        m_labBinG->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245G:", 0, QApplication::UnicodeUTF8));
        m_labBinH->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245H:", 0, QApplication::UnicodeUTF8));
        m_labBinD->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245D:", 0, QApplication::UnicodeUTF8));
        m_labBinF->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245F:", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab), QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\205\245\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        m_labOutputKeepTime->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\272\344\277\235\346\214\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labBout5->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\2725:", 0, QApplication::UnicodeUTF8));
        m_labBout7->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\2727:", 0, QApplication::UnicodeUTF8));
        m_labBout6->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\2726:", 0, QApplication::UnicodeUTF8));
        m_labBout8->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\2728:", 0, QApplication::UnicodeUTF8));
        m_labOutputSwitchMode->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\272\347\277\273\350\275\254\345\220\257\345\212\250\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labBout3->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\2723:", 0, QApplication::UnicodeUTF8));
        m_labOutputDelayTime->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\272\347\277\273\350\275\254\346\227\266\345\210\273(s):", 0, QApplication::UnicodeUTF8));
        m_labBout1->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\2721:", 0, QApplication::UnicodeUTF8));
        m_labBout4->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\2724:", 0, QApplication::UnicodeUTF8));
        m_labBout2->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\2722:", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab_2), QApplication::translate("QRecloseAccBinarySignalDlg", "\345\274\200\345\207\272\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QRecloseAccBinarySignalDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QRecloseAccBinarySignalDlg: public Ui_QRecloseAccBinarySignalDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECLOSEACCBINARYSIGNALDLG_H
