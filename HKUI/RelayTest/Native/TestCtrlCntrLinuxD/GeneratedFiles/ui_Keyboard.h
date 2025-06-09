/********************************************************************************
** Form generated from reading UI file 'Keyboard.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Keyboard
{
public:
    QGridLayout *gridLayout_3;
    QWidget *widgetTop;
    QHBoxLayout *lay2;
    QPushButton *btnPre;
    QLabel *labPY;
    QLabel *labCh1;
    QLabel *labCh2;
    QLabel *labCh3;
    QLabel *labCh4;
    QLabel *labCh5;
    QPushButton *btnNext;
    QPushButton *btnCancel;
    QWidget *widgetMain;
    QGridLayout *gridLayout;
    QPushButton *btnFun3;
    QPushButton *btnN;
    QPushButton *btnB;
    QPushButton *btnV;
    QPushButton *btnJ;
    QPushButton *btn5;
    QPushButton *btnP;
    QPushButton *btnG;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btnR;
    QPushButton *btnM;
    QPushButton *btn1;
    QPushButton *btnT;
    QPushButton *btnU;
    QPushButton *btn2;
    QPushButton *btnF;
    QPushButton *btnY;
    QPushButton *btnO;
    QPushButton *btnI;
    QPushButton *btnH;
    QPushButton *btnFun2;
    QPushButton *btn4;
    QPushButton *btnL;
    QPushButton *btn9;
    QPushButton *btnK;
    QPushButton *btnFun4;
    QPushButton *btnFun1;
    QPushButton *btn3;
    QPushButton *btnEnter;
    QPushButton *btn6;
    QPushButton *btnDelete;
    QPushButton *btn0;
    QPushButton *btnSpace;
    QPushButton *btnMinus;
    QPushButton *btnDot;

    void setupUi(QWidget *Keyboard)
    {
        if (Keyboard->objectName().isEmpty())
            Keyboard->setObjectName(QString::fromUtf8("Keyboard"));
        Keyboard->resize(819, 358);
        Keyboard->setMaximumSize(QSize(1024, 768));
        Keyboard->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(Keyboard);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widgetTop = new QWidget(Keyboard);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetTop->sizePolicy().hasHeightForWidth());
        widgetTop->setSizePolicy(sizePolicy);
        widgetTop->setMaximumSize(QSize(1024, 16777215));
        lay2 = new QHBoxLayout(widgetTop);
        lay2->setSpacing(0);
        lay2->setObjectName(QString::fromUtf8("lay2"));
        lay2->setContentsMargins(9, 9, 9, 0);
        btnPre = new QPushButton(widgetTop);
        btnPre->setObjectName(QString::fromUtf8("btnPre"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnPre->sizePolicy().hasHeightForWidth());
        btnPre->setSizePolicy(sizePolicy1);
        btnPre->setMinimumSize(QSize(60, 60));
        btnPre->setFocusPolicy(Qt::NoFocus);

        lay2->addWidget(btnPre);

        labPY = new QLabel(widgetTop);
        labPY->setObjectName(QString::fromUtf8("labPY"));
        labPY->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labPY);

        labCh1 = new QLabel(widgetTop);
        labCh1->setObjectName(QString::fromUtf8("labCh1"));
        labCh1->setScaledContents(true);
        labCh1->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh1);

        labCh2 = new QLabel(widgetTop);
        labCh2->setObjectName(QString::fromUtf8("labCh2"));
        labCh2->setScaledContents(true);
        labCh2->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh2);

        labCh3 = new QLabel(widgetTop);
        labCh3->setObjectName(QString::fromUtf8("labCh3"));
        labCh3->setScaledContents(true);
        labCh3->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh3);

        labCh4 = new QLabel(widgetTop);
        labCh4->setObjectName(QString::fromUtf8("labCh4"));
        labCh4->setScaledContents(true);
        labCh4->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh4);

        labCh5 = new QLabel(widgetTop);
        labCh5->setObjectName(QString::fromUtf8("labCh5"));
        labCh5->setScaledContents(true);
        labCh5->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh5);

        btnNext = new QPushButton(widgetTop);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        sizePolicy1.setHeightForWidth(btnNext->sizePolicy().hasHeightForWidth());
        btnNext->setSizePolicy(sizePolicy1);
        btnNext->setMinimumSize(QSize(60, 60));
        btnNext->setFocusPolicy(Qt::NoFocus);

        lay2->addWidget(btnNext);

        btnCancel = new QPushButton(widgetTop);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        sizePolicy1.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy1);
        btnCancel->setMinimumSize(QSize(60, 60));
        btnCancel->setFocusPolicy(Qt::NoFocus);

        lay2->addWidget(btnCancel);


        gridLayout_3->addWidget(widgetTop, 0, 0, 1, 2);

        widgetMain = new QWidget(Keyboard);
        widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetMain->sizePolicy().hasHeightForWidth());
        widgetMain->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(widgetMain);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnFun3 = new QPushButton(widgetMain);
        btnFun3->setObjectName(QString::fromUtf8("btnFun3"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnFun3->sizePolicy().hasHeightForWidth());
        btnFun3->setSizePolicy(sizePolicy3);
        btnFun3->setMinimumSize(QSize(60, 60));
        btnFun3->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnFun3, 2, 0, 1, 1);

        btnN = new QPushButton(widgetMain);
        btnN->setObjectName(QString::fromUtf8("btnN"));
        sizePolicy3.setHeightForWidth(btnN->sizePolicy().hasHeightForWidth());
        btnN->setSizePolicy(sizePolicy3);
        btnN->setMinimumSize(QSize(60, 60));
        btnN->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnN, 2, 6, 1, 1);

        btnB = new QPushButton(widgetMain);
        btnB->setObjectName(QString::fromUtf8("btnB"));
        sizePolicy3.setHeightForWidth(btnB->sizePolicy().hasHeightForWidth());
        btnB->setSizePolicy(sizePolicy3);
        btnB->setMinimumSize(QSize(60, 60));
        btnB->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnB, 2, 5, 1, 1);

        btnV = new QPushButton(widgetMain);
        btnV->setObjectName(QString::fromUtf8("btnV"));
        sizePolicy3.setHeightForWidth(btnV->sizePolicy().hasHeightForWidth());
        btnV->setSizePolicy(sizePolicy3);
        btnV->setMinimumSize(QSize(60, 60));
        btnV->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnV, 2, 4, 1, 1);

        btnJ = new QPushButton(widgetMain);
        btnJ->setObjectName(QString::fromUtf8("btnJ"));
        sizePolicy3.setHeightForWidth(btnJ->sizePolicy().hasHeightForWidth());
        btnJ->setSizePolicy(sizePolicy3);
        btnJ->setMinimumSize(QSize(60, 60));
        btnJ->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnJ, 1, 7, 1, 1);

        btn5 = new QPushButton(widgetMain);
        btn5->setObjectName(QString::fromUtf8("btn5"));
        sizePolicy3.setHeightForWidth(btn5->sizePolicy().hasHeightForWidth());
        btn5->setSizePolicy(sizePolicy3);
        btn5->setMinimumSize(QSize(60, 60));
        btn5->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn5, 1, 2, 1, 1);

        btnP = new QPushButton(widgetMain);
        btnP->setObjectName(QString::fromUtf8("btnP"));
        sizePolicy3.setHeightForWidth(btnP->sizePolicy().hasHeightForWidth());
        btnP->setSizePolicy(sizePolicy3);
        btnP->setMinimumSize(QSize(60, 60));
        btnP->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnP, 0, 11, 1, 1);

        btnG = new QPushButton(widgetMain);
        btnG->setObjectName(QString::fromUtf8("btnG"));
        sizePolicy3.setHeightForWidth(btnG->sizePolicy().hasHeightForWidth());
        btnG->setSizePolicy(sizePolicy3);
        btnG->setMinimumSize(QSize(60, 60));
        btnG->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnG, 1, 5, 1, 1);

        btn7 = new QPushButton(widgetMain);
        btn7->setObjectName(QString::fromUtf8("btn7"));
        sizePolicy3.setHeightForWidth(btn7->sizePolicy().hasHeightForWidth());
        btn7->setSizePolicy(sizePolicy3);
        btn7->setMinimumSize(QSize(60, 60));
        btn7->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn7, 2, 1, 1, 1);

        btn8 = new QPushButton(widgetMain);
        btn8->setObjectName(QString::fromUtf8("btn8"));
        sizePolicy3.setHeightForWidth(btn8->sizePolicy().hasHeightForWidth());
        btn8->setSizePolicy(sizePolicy3);
        btn8->setMinimumSize(QSize(60, 60));
        btn8->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn8, 2, 2, 1, 1);

        btnR = new QPushButton(widgetMain);
        btnR->setObjectName(QString::fromUtf8("btnR"));
        sizePolicy3.setHeightForWidth(btnR->sizePolicy().hasHeightForWidth());
        btnR->setSizePolicy(sizePolicy3);
        btnR->setMinimumSize(QSize(60, 60));
        btnR->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnR, 0, 4, 1, 1);

        btnM = new QPushButton(widgetMain);
        btnM->setObjectName(QString::fromUtf8("btnM"));
        sizePolicy3.setHeightForWidth(btnM->sizePolicy().hasHeightForWidth());
        btnM->setSizePolicy(sizePolicy3);
        btnM->setMinimumSize(QSize(60, 60));
        btnM->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnM, 2, 7, 1, 1);

        btn1 = new QPushButton(widgetMain);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        sizePolicy3.setHeightForWidth(btn1->sizePolicy().hasHeightForWidth());
        btn1->setSizePolicy(sizePolicy3);
        btn1->setMinimumSize(QSize(60, 60));
        btn1->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn1, 0, 1, 1, 1);

        btnT = new QPushButton(widgetMain);
        btnT->setObjectName(QString::fromUtf8("btnT"));
        sizePolicy3.setHeightForWidth(btnT->sizePolicy().hasHeightForWidth());
        btnT->setSizePolicy(sizePolicy3);
        btnT->setMinimumSize(QSize(60, 60));
        btnT->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnT, 0, 5, 1, 1);

        btnU = new QPushButton(widgetMain);
        btnU->setObjectName(QString::fromUtf8("btnU"));
        sizePolicy3.setHeightForWidth(btnU->sizePolicy().hasHeightForWidth());
        btnU->setSizePolicy(sizePolicy3);
        btnU->setMinimumSize(QSize(60, 60));
        btnU->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnU, 0, 7, 1, 1);

        btn2 = new QPushButton(widgetMain);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        sizePolicy3.setHeightForWidth(btn2->sizePolicy().hasHeightForWidth());
        btn2->setSizePolicy(sizePolicy3);
        btn2->setMinimumSize(QSize(60, 60));
        btn2->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn2, 0, 2, 1, 1);

        btnF = new QPushButton(widgetMain);
        btnF->setObjectName(QString::fromUtf8("btnF"));
        sizePolicy3.setHeightForWidth(btnF->sizePolicy().hasHeightForWidth());
        btnF->setSizePolicy(sizePolicy3);
        btnF->setMinimumSize(QSize(60, 60));
        btnF->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnF, 1, 4, 1, 1);

        btnY = new QPushButton(widgetMain);
        btnY->setObjectName(QString::fromUtf8("btnY"));
        sizePolicy3.setHeightForWidth(btnY->sizePolicy().hasHeightForWidth());
        btnY->setSizePolicy(sizePolicy3);
        btnY->setMinimumSize(QSize(60, 60));
        btnY->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnY, 0, 6, 1, 1);

        btnO = new QPushButton(widgetMain);
        btnO->setObjectName(QString::fromUtf8("btnO"));
        sizePolicy3.setHeightForWidth(btnO->sizePolicy().hasHeightForWidth());
        btnO->setSizePolicy(sizePolicy3);
        btnO->setMinimumSize(QSize(60, 60));
        btnO->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnO, 0, 9, 1, 1);

        btnI = new QPushButton(widgetMain);
        btnI->setObjectName(QString::fromUtf8("btnI"));
        sizePolicy3.setHeightForWidth(btnI->sizePolicy().hasHeightForWidth());
        btnI->setSizePolicy(sizePolicy3);
        btnI->setMinimumSize(QSize(60, 60));
        btnI->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnI, 0, 8, 1, 1);

        btnH = new QPushButton(widgetMain);
        btnH->setObjectName(QString::fromUtf8("btnH"));
        sizePolicy3.setHeightForWidth(btnH->sizePolicy().hasHeightForWidth());
        btnH->setSizePolicy(sizePolicy3);
        btnH->setMinimumSize(QSize(60, 60));
        btnH->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnH, 1, 6, 1, 1);

        btnFun2 = new QPushButton(widgetMain);
        btnFun2->setObjectName(QString::fromUtf8("btnFun2"));
        sizePolicy3.setHeightForWidth(btnFun2->sizePolicy().hasHeightForWidth());
        btnFun2->setSizePolicy(sizePolicy3);
        btnFun2->setMinimumSize(QSize(60, 60));
        btnFun2->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnFun2, 1, 0, 1, 1);

        btn4 = new QPushButton(widgetMain);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        sizePolicy3.setHeightForWidth(btn4->sizePolicy().hasHeightForWidth());
        btn4->setSizePolicy(sizePolicy3);
        btn4->setMinimumSize(QSize(60, 60));
        btn4->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn4, 1, 1, 1, 1);

        btnL = new QPushButton(widgetMain);
        btnL->setObjectName(QString::fromUtf8("btnL"));
        sizePolicy3.setHeightForWidth(btnL->sizePolicy().hasHeightForWidth());
        btnL->setSizePolicy(sizePolicy3);
        btnL->setMinimumSize(QSize(60, 60));
        btnL->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnL, 1, 9, 1, 1);

        btn9 = new QPushButton(widgetMain);
        btn9->setObjectName(QString::fromUtf8("btn9"));
        sizePolicy3.setHeightForWidth(btn9->sizePolicy().hasHeightForWidth());
        btn9->setSizePolicy(sizePolicy3);
        btn9->setMinimumSize(QSize(60, 60));
        btn9->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn9, 2, 3, 1, 1);

        btnK = new QPushButton(widgetMain);
        btnK->setObjectName(QString::fromUtf8("btnK"));
        sizePolicy3.setHeightForWidth(btnK->sizePolicy().hasHeightForWidth());
        btnK->setSizePolicy(sizePolicy3);
        btnK->setMinimumSize(QSize(60, 60));
        btnK->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnK, 1, 8, 1, 1);

        btnFun4 = new QPushButton(widgetMain);
        btnFun4->setObjectName(QString::fromUtf8("btnFun4"));
        sizePolicy3.setHeightForWidth(btnFun4->sizePolicy().hasHeightForWidth());
        btnFun4->setSizePolicy(sizePolicy3);
        btnFun4->setMinimumSize(QSize(60, 60));
        btnFun4->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnFun4, 3, 0, 1, 1);

        btnFun1 = new QPushButton(widgetMain);
        btnFun1->setObjectName(QString::fromUtf8("btnFun1"));
        sizePolicy3.setHeightForWidth(btnFun1->sizePolicy().hasHeightForWidth());
        btnFun1->setSizePolicy(sizePolicy3);
        btnFun1->setMinimumSize(QSize(60, 60));
        btnFun1->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnFun1, 0, 0, 1, 1);

        btn3 = new QPushButton(widgetMain);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        sizePolicy3.setHeightForWidth(btn3->sizePolicy().hasHeightForWidth());
        btn3->setSizePolicy(sizePolicy3);
        btn3->setMinimumSize(QSize(60, 60));
        btn3->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn3, 0, 3, 1, 1);

        btnEnter = new QPushButton(widgetMain);
        btnEnter->setObjectName(QString::fromUtf8("btnEnter"));
        sizePolicy3.setHeightForWidth(btnEnter->sizePolicy().hasHeightForWidth());
        btnEnter->setSizePolicy(sizePolicy3);
        btnEnter->setMinimumSize(QSize(60, 130));
        btnEnter->setMaximumSize(QSize(16777215, 16777215));
        btnEnter->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnEnter, 2, 12, 2, 1);

        btn6 = new QPushButton(widgetMain);
        btn6->setObjectName(QString::fromUtf8("btn6"));
        sizePolicy3.setHeightForWidth(btn6->sizePolicy().hasHeightForWidth());
        btn6->setSizePolicy(sizePolicy3);
        btn6->setMinimumSize(QSize(60, 60));
        btn6->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn6, 1, 3, 1, 1);

        btnDelete = new QPushButton(widgetMain);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
        sizePolicy3.setHeightForWidth(btnDelete->sizePolicy().hasHeightForWidth());
        btnDelete->setSizePolicy(sizePolicy3);
        btnDelete->setMinimumSize(QSize(60, 130));
        btnDelete->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnDelete, 0, 12, 2, 1);

        btn0 = new QPushButton(widgetMain);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        sizePolicy3.setHeightForWidth(btn0->sizePolicy().hasHeightForWidth());
        btn0->setSizePolicy(sizePolicy3);
        btn0->setMinimumSize(QSize(60, 60));
        btn0->setSizeIncrement(QSize(0, 0));
        btn0->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn0, 3, 2, 1, 1);

        btnSpace = new QPushButton(widgetMain);
        btnSpace->setObjectName(QString::fromUtf8("btnSpace"));
        sizePolicy3.setHeightForWidth(btnSpace->sizePolicy().hasHeightForWidth());
        btnSpace->setSizePolicy(sizePolicy3);
        btnSpace->setMinimumSize(QSize(60, 60));
        btnSpace->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnSpace, 3, 4, 1, 1);

        btnMinus = new QPushButton(widgetMain);
        btnMinus->setObjectName(QString::fromUtf8("btnMinus"));
        sizePolicy3.setHeightForWidth(btnMinus->sizePolicy().hasHeightForWidth());
        btnMinus->setSizePolicy(sizePolicy3);
        btnMinus->setMinimumSize(QSize(60, 60));
        btnMinus->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnMinus, 3, 1, 1, 1);

        btnDot = new QPushButton(widgetMain);
        btnDot->setObjectName(QString::fromUtf8("btnDot"));
        sizePolicy3.setHeightForWidth(btnDot->sizePolicy().hasHeightForWidth());
        btnDot->setSizePolicy(sizePolicy3);
        btnDot->setMinimumSize(QSize(60, 60));
        btnDot->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnDot, 3, 3, 1, 1);


        gridLayout_3->addWidget(widgetMain, 1, 1, 1, 1);


        retranslateUi(Keyboard);

        QMetaObject::connectSlotsByName(Keyboard);
    } // setupUi

    void retranslateUi(QWidget *Keyboard)
    {
        btnPre->setText(QApplication::translate("Keyboard", "<", 0, QApplication::UnicodeUTF8));
        labPY->setText(QString());
        labCh1->setText(QString());
        labCh2->setText(QString());
        labCh3->setText(QString());
        labCh4->setText(QString());
        labCh5->setText(QString());
        btnNext->setText(QApplication::translate("Keyboard", ">", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("Keyboard", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        btnFun3->setText(QString());
        btnN->setText(QApplication::translate("Keyboard", "N", 0, QApplication::UnicodeUTF8));
        btnB->setText(QApplication::translate("Keyboard", "B", 0, QApplication::UnicodeUTF8));
        btnV->setText(QApplication::translate("Keyboard", "V", 0, QApplication::UnicodeUTF8));
        btnJ->setText(QApplication::translate("Keyboard", "J", 0, QApplication::UnicodeUTF8));
        btn5->setText(QApplication::translate("Keyboard", "5", 0, QApplication::UnicodeUTF8));
        btnP->setText(QApplication::translate("Keyboard", "P", 0, QApplication::UnicodeUTF8));
        btnG->setText(QApplication::translate("Keyboard", "G", 0, QApplication::UnicodeUTF8));
        btn7->setText(QApplication::translate("Keyboard", "7", 0, QApplication::UnicodeUTF8));
        btn8->setText(QApplication::translate("Keyboard", "8", 0, QApplication::UnicodeUTF8));
        btnR->setText(QApplication::translate("Keyboard", "R", 0, QApplication::UnicodeUTF8));
        btnM->setText(QApplication::translate("Keyboard", "M", 0, QApplication::UnicodeUTF8));
        btn1->setText(QApplication::translate("Keyboard", "1", 0, QApplication::UnicodeUTF8));
        btnT->setText(QApplication::translate("Keyboard", "T", 0, QApplication::UnicodeUTF8));
        btnU->setText(QApplication::translate("Keyboard", "U", 0, QApplication::UnicodeUTF8));
        btn2->setText(QApplication::translate("Keyboard", "2", 0, QApplication::UnicodeUTF8));
        btnF->setText(QApplication::translate("Keyboard", "F", 0, QApplication::UnicodeUTF8));
        btnY->setText(QApplication::translate("Keyboard", "Y", 0, QApplication::UnicodeUTF8));
        btnO->setText(QApplication::translate("Keyboard", "O", 0, QApplication::UnicodeUTF8));
        btnI->setText(QApplication::translate("Keyboard", "I", 0, QApplication::UnicodeUTF8));
        btnH->setText(QApplication::translate("Keyboard", "H", 0, QApplication::UnicodeUTF8));
        btnFun2->setText(QString());
        btn4->setText(QApplication::translate("Keyboard", "4", 0, QApplication::UnicodeUTF8));
        btnL->setText(QApplication::translate("Keyboard", "L", 0, QApplication::UnicodeUTF8));
        btn9->setText(QApplication::translate("Keyboard", "9", 0, QApplication::UnicodeUTF8));
        btnK->setText(QApplication::translate("Keyboard", "K", 0, QApplication::UnicodeUTF8));
        btnFun4->setText(QString());
        btnFun1->setText(QString());
        btn3->setText(QApplication::translate("Keyboard", "3", 0, QApplication::UnicodeUTF8));
        btnEnter->setText(QApplication::translate("Keyboard", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        btn6->setText(QApplication::translate("Keyboard", "6", 0, QApplication::UnicodeUTF8));
        btnDelete->setText(QApplication::translate("Keyboard", "\345\233\236\351\200\200", 0, QApplication::UnicodeUTF8));
        btn0->setText(QApplication::translate("Keyboard", "0", 0, QApplication::UnicodeUTF8));
        btnSpace->setText(QApplication::translate("Keyboard", "\347\251\272\346\240\274", 0, QApplication::UnicodeUTF8));
        btnMinus->setText(QApplication::translate("Keyboard", "-", 0, QApplication::UnicodeUTF8));
        btnDot->setText(QApplication::translate("Keyboard", ".", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Keyboard);
    } // retranslateUi

};

namespace Ui {
    class Keyboard: public Ui_Keyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
