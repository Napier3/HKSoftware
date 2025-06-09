/********************************************************************************
** Form generated from reading UI file 'DistanceSearchAddMultDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCESEARCHADDMULTDLG_H
#define UI_DISTANCESEARCHADDMULTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QDistanceSearchAddMultDlg
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QTableWidget *m_tableWidget;
    QSpacerItem *horizontalSpacer;
    QGroupBox *m_gbOtherParas;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_5;
    QGridLayout *gridLayout_2;
    QLineEdit *m_editSearchAngBeg;
    QLabel *m_labSearchLen;
    QLineEdit *m_editSearchLen;
    QLabel *m_labZoneType;
    QComboBox *m_cbbZoneType;
    QLabel *m_labFaultCur;
    QLineEdit *m_editFaultCur;
    QLabel *m_labFaultVol;
    QLabel *m_labOrigAng;
    QLineEdit *m_editFaultVol;
    QLabel *m_labSearchAngEnd;
    QLabel *m_labAngStep;
    QLabel *m_labSearchAngBeg;
    QLabel *m_labOrigImp;
    QLineEdit *m_editOrigAng;
    QLineEdit *m_editOrigImp;
    QLineEdit *m_editAngStep;
    QLineEdit *m_editSearchAngEnd;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QGroupBox *m_gbResultEval;
    QHBoxLayout *horizontalLayout_6;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_7;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *m_editAbsErr;
    QSpacerItem *horizontalSpacer_4;
    QLabel *m_labErrType;
    QLabel *m_labAbsErr;
    CExBaseListComboBox *m_cbbErrType;
    QLabel *m_labRelErr;
    QLineEdit *m_editRelErr;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *QDistanceSearchAddMultDlg)
    {
        if (QDistanceSearchAddMultDlg->objectName().isEmpty())
            QDistanceSearchAddMultDlg->setObjectName(QString::fromUtf8("QDistanceSearchAddMultDlg"));
        QDistanceSearchAddMultDlg->resize(782, 615);
        horizontalLayout_3 = new QHBoxLayout(QDistanceSearchAddMultDlg);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_tableWidget = new QTableWidget(QDistanceSearchAddMultDlg);
        if (m_tableWidget->columnCount() < 2)
            m_tableWidget->setColumnCount(2);
        if (m_tableWidget->rowCount() < 4)
            m_tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 1, __qtablewidgetitem1);
        m_tableWidget->setObjectName(QString::fromUtf8("m_tableWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_tableWidget->sizePolicy().hasHeightForWidth());
        m_tableWidget->setSizePolicy(sizePolicy);
        m_tableWidget->setMinimumSize(QSize(0, 240));
        m_tableWidget->setRowCount(4);
        m_tableWidget->setColumnCount(2);
        m_tableWidget->horizontalHeader()->setVisible(false);
        m_tableWidget->horizontalHeader()->setMinimumSectionSize(40);
        m_tableWidget->horizontalHeader()->setStretchLastSection(true);
        m_tableWidget->verticalHeader()->setVisible(false);
        m_tableWidget->verticalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(m_tableWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        m_gbOtherParas = new QGroupBox(QDistanceSearchAddMultDlg);
        m_gbOtherParas->setObjectName(QString::fromUtf8("m_gbOtherParas"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_gbOtherParas->sizePolicy().hasHeightForWidth());
        m_gbOtherParas->setSizePolicy(sizePolicy1);
        horizontalLayout_4 = new QHBoxLayout(m_gbOtherParas);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        frame = new QFrame(m_gbOtherParas);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_editSearchAngBeg = new QLineEdit(frame);
        m_editSearchAngBeg->setObjectName(QString::fromUtf8("m_editSearchAngBeg"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_editSearchAngBeg->sizePolicy().hasHeightForWidth());
        m_editSearchAngBeg->setSizePolicy(sizePolicy2);
        m_editSearchAngBeg->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editSearchAngBeg, 0, 4, 1, 1);

        m_labSearchLen = new QLabel(frame);
        m_labSearchLen->setObjectName(QString::fromUtf8("m_labSearchLen"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_labSearchLen->sizePolicy().hasHeightForWidth());
        m_labSearchLen->setSizePolicy(sizePolicy3);
        m_labSearchLen->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labSearchLen, 1, 6, 1, 1);

        m_editSearchLen = new QLineEdit(frame);
        m_editSearchLen->setObjectName(QString::fromUtf8("m_editSearchLen"));
        sizePolicy2.setHeightForWidth(m_editSearchLen->sizePolicy().hasHeightForWidth());
        m_editSearchLen->setSizePolicy(sizePolicy2);
        m_editSearchLen->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editSearchLen, 1, 7, 1, 1);

        m_labZoneType = new QLabel(frame);
        m_labZoneType->setObjectName(QString::fromUtf8("m_labZoneType"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(m_labZoneType->sizePolicy().hasHeightForWidth());
        m_labZoneType->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(m_labZoneType, 0, 6, 1, 1);

        m_cbbZoneType = new QComboBox(frame);
        m_cbbZoneType->setObjectName(QString::fromUtf8("m_cbbZoneType"));
        sizePolicy2.setHeightForWidth(m_cbbZoneType->sizePolicy().hasHeightForWidth());
        m_cbbZoneType->setSizePolicy(sizePolicy2);
        m_cbbZoneType->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_cbbZoneType, 0, 7, 1, 1);

        m_labFaultCur = new QLabel(frame);
        m_labFaultCur->setObjectName(QString::fromUtf8("m_labFaultCur"));
        m_labFaultCur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labFaultCur, 2, 0, 1, 1);

        m_editFaultCur = new QLineEdit(frame);
        m_editFaultCur->setObjectName(QString::fromUtf8("m_editFaultCur"));
        sizePolicy2.setHeightForWidth(m_editFaultCur->sizePolicy().hasHeightForWidth());
        m_editFaultCur->setSizePolicy(sizePolicy2);
        m_editFaultCur->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editFaultCur, 2, 1, 1, 1);

        m_labFaultVol = new QLabel(frame);
        m_labFaultVol->setObjectName(QString::fromUtf8("m_labFaultVol"));
        sizePolicy4.setHeightForWidth(m_labFaultVol->sizePolicy().hasHeightForWidth());
        m_labFaultVol->setSizePolicy(sizePolicy4);
        m_labFaultVol->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labFaultVol, 3, 0, 1, 1);

        m_labOrigAng = new QLabel(frame);
        m_labOrigAng->setObjectName(QString::fromUtf8("m_labOrigAng"));
        sizePolicy3.setHeightForWidth(m_labOrigAng->sizePolicy().hasHeightForWidth());
        m_labOrigAng->setSizePolicy(sizePolicy3);
        m_labOrigAng->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labOrigAng, 1, 0, 1, 1);

        m_editFaultVol = new QLineEdit(frame);
        m_editFaultVol->setObjectName(QString::fromUtf8("m_editFaultVol"));
        sizePolicy2.setHeightForWidth(m_editFaultVol->sizePolicy().hasHeightForWidth());
        m_editFaultVol->setSizePolicy(sizePolicy2);
        m_editFaultVol->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editFaultVol, 3, 1, 1, 1);

        m_labSearchAngEnd = new QLabel(frame);
        m_labSearchAngEnd->setObjectName(QString::fromUtf8("m_labSearchAngEnd"));
        m_labSearchAngEnd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labSearchAngEnd, 1, 3, 1, 1);

        m_labAngStep = new QLabel(frame);
        m_labAngStep->setObjectName(QString::fromUtf8("m_labAngStep"));
        m_labAngStep->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labAngStep, 2, 3, 1, 1);

        m_labSearchAngBeg = new QLabel(frame);
        m_labSearchAngBeg->setObjectName(QString::fromUtf8("m_labSearchAngBeg"));
        sizePolicy3.setHeightForWidth(m_labSearchAngBeg->sizePolicy().hasHeightForWidth());
        m_labSearchAngBeg->setSizePolicy(sizePolicy3);
        m_labSearchAngBeg->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labSearchAngBeg, 0, 3, 1, 1);

        m_labOrigImp = new QLabel(frame);
        m_labOrigImp->setObjectName(QString::fromUtf8("m_labOrigImp"));
        sizePolicy3.setHeightForWidth(m_labOrigImp->sizePolicy().hasHeightForWidth());
        m_labOrigImp->setSizePolicy(sizePolicy3);
        m_labOrigImp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_labOrigImp, 0, 0, 1, 1);

        m_editOrigAng = new QLineEdit(frame);
        m_editOrigAng->setObjectName(QString::fromUtf8("m_editOrigAng"));
        sizePolicy2.setHeightForWidth(m_editOrigAng->sizePolicy().hasHeightForWidth());
        m_editOrigAng->setSizePolicy(sizePolicy2);
        m_editOrigAng->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editOrigAng, 1, 1, 1, 1);

        m_editOrigImp = new QLineEdit(frame);
        m_editOrigImp->setObjectName(QString::fromUtf8("m_editOrigImp"));
        sizePolicy2.setHeightForWidth(m_editOrigImp->sizePolicy().hasHeightForWidth());
        m_editOrigImp->setSizePolicy(sizePolicy2);
        m_editOrigImp->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editOrigImp, 0, 1, 1, 1);

        m_editAngStep = new QLineEdit(frame);
        m_editAngStep->setObjectName(QString::fromUtf8("m_editAngStep"));
        sizePolicy2.setHeightForWidth(m_editAngStep->sizePolicy().hasHeightForWidth());
        m_editAngStep->setSizePolicy(sizePolicy2);
        m_editAngStep->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editAngStep, 2, 4, 1, 1);

        m_editSearchAngEnd = new QLineEdit(frame);
        m_editSearchAngEnd->setObjectName(QString::fromUtf8("m_editSearchAngEnd"));
        sizePolicy2.setHeightForWidth(m_editSearchAngEnd->sizePolicy().hasHeightForWidth());
        m_editSearchAngEnd->setSizePolicy(sizePolicy2);
        m_editSearchAngEnd->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(m_editSearchAngEnd, 1, 4, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 5, 1, 1);


        horizontalLayout_5->addLayout(gridLayout_2);


        horizontalLayout_4->addWidget(frame);


        verticalLayout->addWidget(m_gbOtherParas);

        m_gbResultEval = new QGroupBox(QDistanceSearchAddMultDlg);
        m_gbResultEval->setObjectName(QString::fromUtf8("m_gbResultEval"));
        horizontalLayout_6 = new QHBoxLayout(m_gbResultEval);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        frame_2 = new QFrame(m_gbResultEval);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy4.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy4);
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_2);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 1, 6, 1, 1);

        m_editAbsErr = new QLineEdit(frame_2);
        m_editAbsErr->setObjectName(QString::fromUtf8("m_editAbsErr"));

        gridLayout_3->addWidget(m_editAbsErr, 1, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        m_labErrType = new QLabel(frame_2);
        m_labErrType->setObjectName(QString::fromUtf8("m_labErrType"));

        gridLayout_3->addWidget(m_labErrType, 0, 0, 1, 1);

        m_labAbsErr = new QLabel(frame_2);
        m_labAbsErr->setObjectName(QString::fromUtf8("m_labAbsErr"));

        gridLayout_3->addWidget(m_labAbsErr, 1, 3, 1, 1);

        m_cbbErrType = new CExBaseListComboBox(frame_2);
        m_cbbErrType->setObjectName(QString::fromUtf8("m_cbbErrType"));

        gridLayout_3->addWidget(m_cbbErrType, 0, 1, 1, 1);

        m_labRelErr = new QLabel(frame_2);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));

        gridLayout_3->addWidget(m_labRelErr, 1, 0, 1, 1);

        m_editRelErr = new QLineEdit(frame_2);
        m_editRelErr->setObjectName(QString::fromUtf8("m_editRelErr"));

        gridLayout_3->addWidget(m_editRelErr, 1, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 1, 5, 1, 1);


        horizontalLayout_7->addLayout(gridLayout_3);


        horizontalLayout_6->addWidget(frame_2);


        verticalLayout->addWidget(m_gbResultEval);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, 10, -1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 10, -1);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        m_btnOk = new QPushButton(QDistanceSearchAddMultDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));

        horizontalLayout_2->addWidget(m_btnOk);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        m_btnCancel = new QPushButton(QDistanceSearchAddMultDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout_2->addWidget(m_btnCancel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(QDistanceSearchAddMultDlg);

        QMetaObject::connectSlotsByName(QDistanceSearchAddMultDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceSearchAddMultDlg)
    {
        QDistanceSearchAddMultDlg->setWindowTitle(QApplication::translate("QDistanceSearchAddMultDlg", "\346\267\273\345\212\240\347\263\273\345\210\227", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = m_tableWidget->isSortingEnabled();
        m_tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = m_tableWidget->item(0, 0);
        ___qtablewidgetitem->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\346\225\205\351\232\234\347\233\270\345\210\253", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = m_tableWidget->item(0, 1);
        ___qtablewidgetitem1->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\345\212\250\344\275\234\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_tableWidget->setSortingEnabled(__sortingEnabled);

        m_gbOtherParas->setTitle(QApplication::translate("QDistanceSearchAddMultDlg", "\345\205\266\344\273\226\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labSearchLen->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\346\220\234\347\264\242\345\215\212\345\276\204(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labZoneType->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\345\214\272\346\256\265\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_cbbZoneType->clear();
        m_cbbZoneType->insertItems(0, QStringList()
         << QApplication::translate("QDistanceSearchAddMultDlg", "\342\205\240\346\256\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDistanceSearchAddMultDlg", "\342\205\241\346\256\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDistanceSearchAddMultDlg", "\342\205\242\346\256\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDistanceSearchAddMultDlg", "\342\205\243\346\256\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDistanceSearchAddMultDlg", "\342\205\244\346\256\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDistanceSearchAddMultDlg", "\347\272\277\350\267\257\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDistanceSearchAddMultDlg", "\346\211\200\346\234\211\345\214\272\345\237\237", 0, QApplication::UnicodeUTF8)
        );
        m_labFaultCur->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\347\237\255\350\267\257\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labFaultVol->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\347\237\255\350\267\257\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labOrigAng->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\344\270\255\345\277\203\347\202\271\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labSearchAngEnd->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\346\220\234\347\264\242\350\247\222\345\272\246\347\273\210\345\200\274(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labAngStep->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\350\247\222\345\272\246\346\224\271\345\217\230\346\255\245\351\225\277(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labSearchAngBeg->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\346\220\234\347\264\242\350\247\222\345\272\246\345\247\213\345\200\274(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labOrigImp->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\344\270\255\345\277\203\347\202\271\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_gbResultEval->setTitle(QApplication::translate("QDistanceSearchAddMultDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_labErrType->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\350\257\257\345\267\256\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labAbsErr->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(\357\274\205):", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDistanceSearchAddMultDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceSearchAddMultDlg: public Ui_QDistanceSearchAddMultDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCESEARCHADDMULTDLG_H
