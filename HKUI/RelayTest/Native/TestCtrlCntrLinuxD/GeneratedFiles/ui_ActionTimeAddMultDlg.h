/********************************************************************************
** Form generated from reading UI file 'ActionTimeAddMultDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIONTIMEADDMULTDLG_H
#define UI_ACTIONTIMEADDMULTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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
#include <QtGui/QWidget>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../UI/Controls/SettingCtrls/QSettingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QActionTimeAddMultDlg
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_1;
    QTableWidget *m_tableWidget;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *m_gbFault;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_10;
    QLabel *m_labSettingTime;
    QSettingLineEdit *m_editSettingTime;
    QSpacerItem *horizontalSpacer_5;
    QLabel *m_labFaultCur;
    QLineEdit *m_editFaultCurrent;
    QSpacerItem *horizontalSpacer_6;
    QLabel *m_labFaultAngle;
    QLineEdit *m_editFaultAngle;
    QSpacerItem *horizontalSpacer_11;
    QGroupBox *m_gbResultEval;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout;
    QLabel *m_labErrType;
    CExBaseListComboBox *m_cbbErrType;
    QSpacerItem *horizontalSpacer_8;
    QLabel *m_labRelErr;
    QLabel *m_labAbsErrPos;
    QLineEdit *m_editRelErr;
    QLabel *m_labAbsErrNeg;
    QLineEdit *m_editAbsErrPos;
    QLineEdit *m_editAbsErrNeg;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QWidget *QActionTimeAddMultDlg)
    {
        if (QActionTimeAddMultDlg->objectName().isEmpty())
            QActionTimeAddMultDlg->setObjectName(QString::fromUtf8("QActionTimeAddMultDlg"));
        QActionTimeAddMultDlg->resize(911, 608);
        QActionTimeAddMultDlg->setMaximumSize(QSize(1024, 800));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        QActionTimeAddMultDlg->setFont(font);
        gridLayout_2 = new QGridLayout(QActionTimeAddMultDlg);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        m_btnOk = new QPushButton(QActionTimeAddMultDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_btnOk);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        m_btnCancel = new QPushButton(QActionTimeAddMultDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setSpacing(6);
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        m_tableWidget = new QTableWidget(QActionTimeAddMultDlg);
        if (m_tableWidget->columnCount() < 3)
            m_tableWidget->setColumnCount(3);
        if (m_tableWidget->rowCount() < 7)
            m_tableWidget->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(0, 2, __qtablewidgetitem2);
        m_tableWidget->setObjectName(QString::fromUtf8("m_tableWidget"));
        m_tableWidget->setRowCount(7);
        m_tableWidget->setColumnCount(3);
        m_tableWidget->horizontalHeader()->setVisible(false);
        m_tableWidget->horizontalHeader()->setStretchLastSection(true);
        m_tableWidget->verticalHeader()->setVisible(false);
        m_tableWidget->verticalHeader()->setHighlightSections(false);
        m_tableWidget->verticalHeader()->setStretchLastSection(true);

        horizontalLayout_1->addWidget(m_tableWidget);


        gridLayout_2->addLayout(horizontalLayout_1, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_gbFault = new QGroupBox(QActionTimeAddMultDlg);
        m_gbFault->setObjectName(QString::fromUtf8("m_gbFault"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_gbFault->sizePolicy().hasHeightForWidth());
        m_gbFault->setSizePolicy(sizePolicy1);
        horizontalLayout_3 = new QHBoxLayout(m_gbFault);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        frame = new QFrame(m_gbFault);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_10);

        m_labSettingTime = new QLabel(frame);
        m_labSettingTime->setObjectName(QString::fromUtf8("m_labSettingTime"));
        sizePolicy.setHeightForWidth(m_labSettingTime->sizePolicy().hasHeightForWidth());
        m_labSettingTime->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(m_labSettingTime);

        m_editSettingTime = new QSettingLineEdit(frame);
        m_editSettingTime->setObjectName(QString::fromUtf8("m_editSettingTime"));
        sizePolicy.setHeightForWidth(m_editSettingTime->sizePolicy().hasHeightForWidth());
        m_editSettingTime->setSizePolicy(sizePolicy);
        m_editSettingTime->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(m_editSettingTime);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        m_labFaultCur = new QLabel(frame);
        m_labFaultCur->setObjectName(QString::fromUtf8("m_labFaultCur"));

        horizontalLayout_2->addWidget(m_labFaultCur);

        m_editFaultCurrent = new QLineEdit(frame);
        m_editFaultCurrent->setObjectName(QString::fromUtf8("m_editFaultCurrent"));
        sizePolicy.setHeightForWidth(m_editFaultCurrent->sizePolicy().hasHeightForWidth());
        m_editFaultCurrent->setSizePolicy(sizePolicy);
        m_editFaultCurrent->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(m_editFaultCurrent);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        m_labFaultAngle = new QLabel(frame);
        m_labFaultAngle->setObjectName(QString::fromUtf8("m_labFaultAngle"));

        horizontalLayout_2->addWidget(m_labFaultAngle);

        m_editFaultAngle = new QLineEdit(frame);
        m_editFaultAngle->setObjectName(QString::fromUtf8("m_editFaultAngle"));
        sizePolicy.setHeightForWidth(m_editFaultAngle->sizePolicy().hasHeightForWidth());
        m_editFaultAngle->setSizePolicy(sizePolicy);
        m_editFaultAngle->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(m_editFaultAngle);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_11);


        horizontalLayout_4->addLayout(horizontalLayout_2);


        horizontalLayout_3->addWidget(frame);


        verticalLayout_2->addWidget(m_gbFault);

        m_gbResultEval = new QGroupBox(QActionTimeAddMultDlg);
        m_gbResultEval->setObjectName(QString::fromUtf8("m_gbResultEval"));
        sizePolicy2.setHeightForWidth(m_gbResultEval->sizePolicy().hasHeightForWidth());
        m_gbResultEval->setSizePolicy(sizePolicy2);
        horizontalLayout_5 = new QHBoxLayout(m_gbResultEval);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        frame_2 = new QFrame(m_gbResultEval);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Sunken);
        horizontalLayout_6 = new QHBoxLayout(frame_2);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labErrType = new QLabel(frame_2);
        m_labErrType->setObjectName(QString::fromUtf8("m_labErrType"));

        gridLayout->addWidget(m_labErrType, 1, 1, 1, 1);

        m_cbbErrType = new CExBaseListComboBox(frame_2);
        m_cbbErrType->setObjectName(QString::fromUtf8("m_cbbErrType"));
        sizePolicy.setHeightForWidth(m_cbbErrType->sizePolicy().hasHeightForWidth());
        m_cbbErrType->setSizePolicy(sizePolicy);
        m_cbbErrType->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(m_cbbErrType, 1, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 1, 0, 1, 1);

        m_labRelErr = new QLabel(frame_2);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));

        gridLayout->addWidget(m_labRelErr, 1, 4, 1, 1);

        m_labAbsErrPos = new QLabel(frame_2);
        m_labAbsErrPos->setObjectName(QString::fromUtf8("m_labAbsErrPos"));

        gridLayout->addWidget(m_labAbsErrPos, 2, 1, 1, 1);

        m_editRelErr = new QLineEdit(frame_2);
        m_editRelErr->setObjectName(QString::fromUtf8("m_editRelErr"));
        sizePolicy.setHeightForWidth(m_editRelErr->sizePolicy().hasHeightForWidth());
        m_editRelErr->setSizePolicy(sizePolicy);
        m_editRelErr->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(m_editRelErr, 1, 5, 1, 1);

        m_labAbsErrNeg = new QLabel(frame_2);
        m_labAbsErrNeg->setObjectName(QString::fromUtf8("m_labAbsErrNeg"));

        gridLayout->addWidget(m_labAbsErrNeg, 2, 4, 1, 1);

        m_editAbsErrPos = new QLineEdit(frame_2);
        m_editAbsErrPos->setObjectName(QString::fromUtf8("m_editAbsErrPos"));
        sizePolicy.setHeightForWidth(m_editAbsErrPos->sizePolicy().hasHeightForWidth());
        m_editAbsErrPos->setSizePolicy(sizePolicy);
        m_editAbsErrPos->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(m_editAbsErrPos, 2, 2, 1, 1);

        m_editAbsErrNeg = new QLineEdit(frame_2);
        m_editAbsErrNeg->setObjectName(QString::fromUtf8("m_editAbsErrNeg"));
        sizePolicy.setHeightForWidth(m_editAbsErrNeg->sizePolicy().hasHeightForWidth());
        m_editAbsErrNeg->setSizePolicy(sizePolicy);
        m_editAbsErrNeg->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(m_editAbsErrNeg, 2, 5, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 1, 3, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 1, 6, 1, 1);


        horizontalLayout_6->addLayout(gridLayout);


        horizontalLayout_5->addWidget(frame_2);


        verticalLayout_2->addWidget(m_gbResultEval);


        gridLayout_2->addLayout(verticalLayout_2, 1, 0, 1, 1);


        retranslateUi(QActionTimeAddMultDlg);

        QMetaObject::connectSlotsByName(QActionTimeAddMultDlg);
    } // setupUi

    void retranslateUi(QWidget *QActionTimeAddMultDlg)
    {
        QActionTimeAddMultDlg->setWindowTitle(QApplication::translate("QActionTimeAddMultDlg", "\346\267\273\345\212\240\347\263\273\345\210\227", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QActionTimeAddMultDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QActionTimeAddMultDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = m_tableWidget->isSortingEnabled();
        m_tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = m_tableWidget->item(0, 0);
        ___qtablewidgetitem->setText(QApplication::translate("QActionTimeAddMultDlg", "\346\265\213\350\257\225\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = m_tableWidget->item(0, 1);
        ___qtablewidgetitem1->setText(QApplication::translate("QActionTimeAddMultDlg", "\346\225\205\351\232\234\347\224\265\345\216\213(V)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = m_tableWidget->item(0, 2);
        ___qtablewidgetitem2->setText(QApplication::translate("QActionTimeAddMultDlg", "\346\225\205\351\232\234\347\233\270\345\210\253", 0, QApplication::UnicodeUTF8));
        m_tableWidget->setSortingEnabled(__sortingEnabled);

        m_gbFault->setTitle(QApplication::translate("QActionTimeAddMultDlg", "\346\225\205\351\232\234\346\200\201", 0, QApplication::UnicodeUTF8));
        m_labSettingTime->setText(QApplication::translate("QActionTimeAddMultDlg", "\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultCur->setText(QApplication::translate("QActionTimeAddMultDlg", "\346\225\205\351\232\234\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labFaultAngle->setText(QApplication::translate("QActionTimeAddMultDlg", "\346\225\205\351\232\234\346\200\201\347\233\270\344\275\215\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_gbResultEval->setTitle(QApplication::translate("QActionTimeAddMultDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_labErrType->setText(QApplication::translate("QActionTimeAddMultDlg", "\350\257\257\345\267\256\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QActionTimeAddMultDlg", "\347\233\270\345\257\271\350\257\257\345\267\256(\357\274\205):", 0, QApplication::UnicodeUTF8));
        m_labAbsErrPos->setText(QApplication::translate("QActionTimeAddMultDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s) +:", 0, QApplication::UnicodeUTF8));
        m_labAbsErrNeg->setText(QApplication::translate("QActionTimeAddMultDlg", "\347\273\235\345\257\271\350\257\257\345\267\256(s) -:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QActionTimeAddMultDlg: public Ui_QActionTimeAddMultDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIONTIMEADDMULTDLG_H
