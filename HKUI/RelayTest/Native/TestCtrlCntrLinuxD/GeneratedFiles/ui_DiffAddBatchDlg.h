/********************************************************************************
** Form generated from reading UI file 'DiffAddBatchDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFADDBATCHDLG_H
#define UI_DIFFADDBATCHDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
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
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QDiffAddBatchDlg
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QLabel *m_labTime_lr;
    QLabel *m_labTime_ld;
    QLabel *m_labTime_ld_2;
    QLineEdit *m_txtTime_lr;
    QLineEdit *m_txtTime_ld;
    QLineEdit *m_txtMaxFaultTime;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *m_check_AN;
    QCheckBox *m_check_BC;
    QCheckBox *m_check_AB;
    QCheckBox *m_check_CA;
    QCheckBox *m_check_BN;
    QCheckBox *m_check_CN;
    QCheckBox *m_check_ABC;
    QCheckBox *m_check_Harm;
    QCheckBox *m_check_Time;
    QCheckBox *m_check_Rate;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *VLayout_Rate;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *VLayout_Harm;
    QPushButton *m_btnResEvaluat;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labTips;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *m_btnSave;
    QPushButton *m_btnClose;

    void setupUi(QDialog *QDiffAddBatchDlg)
    {
        if (QDiffAddBatchDlg->objectName().isEmpty())
            QDiffAddBatchDlg->setObjectName(QString::fromUtf8("QDiffAddBatchDlg"));
        QDiffAddBatchDlg->resize(471, 552);
        QFont font;
        font.setPointSize(9);
        QDiffAddBatchDlg->setFont(font);
        gridLayout_3 = new QGridLayout(QDiffAddBatchDlg);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_2 = new QFrame(QDiffAddBatchDlg);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_labTime_lr = new QLabel(frame_2);
        m_labTime_lr->setObjectName(QString::fromUtf8("m_labTime_lr"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labTime_lr->sizePolicy().hasHeightForWidth());
        m_labTime_lr->setSizePolicy(sizePolicy);
        m_labTime_lr->setMinimumSize(QSize(0, 0));
        m_labTime_lr->setMaximumSize(QSize(16777215, 16777215));
        m_labTime_lr->setFont(font);
        m_labTime_lr->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_labTime_lr, 3, 0, 1, 1);

        m_labTime_ld = new QLabel(frame_2);
        m_labTime_ld->setObjectName(QString::fromUtf8("m_labTime_ld"));
        sizePolicy.setHeightForWidth(m_labTime_ld->sizePolicy().hasHeightForWidth());
        m_labTime_ld->setSizePolicy(sizePolicy);
        m_labTime_ld->setMinimumSize(QSize(0, 0));
        m_labTime_ld->setMaximumSize(QSize(16777215, 16777215));
        m_labTime_ld->setFont(font);
        m_labTime_ld->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_labTime_ld, 4, 0, 1, 1);

        m_labTime_ld_2 = new QLabel(frame_2);
        m_labTime_ld_2->setObjectName(QString::fromUtf8("m_labTime_ld_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_labTime_ld_2->sizePolicy().hasHeightForWidth());
        m_labTime_ld_2->setSizePolicy(sizePolicy1);
        m_labTime_ld_2->setMinimumSize(QSize(0, 0));
        m_labTime_ld_2->setMaximumSize(QSize(16777215, 16777215));
        m_labTime_ld_2->setFont(font);
        m_labTime_ld_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_labTime_ld_2, 5, 0, 1, 1);

        m_txtTime_lr = new QLineEdit(frame_2);
        m_txtTime_lr->setObjectName(QString::fromUtf8("m_txtTime_lr"));
        sizePolicy.setHeightForWidth(m_txtTime_lr->sizePolicy().hasHeightForWidth());
        m_txtTime_lr->setSizePolicy(sizePolicy);
        m_txtTime_lr->setMinimumSize(QSize(0, 0));
        m_txtTime_lr->setMaximumSize(QSize(16777215, 16777215));
        m_txtTime_lr->setFont(font);

        gridLayout_2->addWidget(m_txtTime_lr, 3, 1, 1, 1);

        m_txtTime_ld = new QLineEdit(frame_2);
        m_txtTime_ld->setObjectName(QString::fromUtf8("m_txtTime_ld"));
        sizePolicy.setHeightForWidth(m_txtTime_ld->sizePolicy().hasHeightForWidth());
        m_txtTime_ld->setSizePolicy(sizePolicy);
        m_txtTime_ld->setMinimumSize(QSize(0, 0));
        m_txtTime_ld->setMaximumSize(QSize(16777215, 16777215));
        m_txtTime_ld->setFont(font);

        gridLayout_2->addWidget(m_txtTime_ld, 4, 1, 1, 1);

        m_txtMaxFaultTime = new QLineEdit(frame_2);
        m_txtMaxFaultTime->setObjectName(QString::fromUtf8("m_txtMaxFaultTime"));
        sizePolicy.setHeightForWidth(m_txtMaxFaultTime->sizePolicy().hasHeightForWidth());
        m_txtMaxFaultTime->setSizePolicy(sizePolicy);
        m_txtMaxFaultTime->setMinimumSize(QSize(0, 0));
        m_txtMaxFaultTime->setMaximumSize(QSize(16777215, 16777215));
        m_txtMaxFaultTime->setFont(font);

        gridLayout_2->addWidget(m_txtMaxFaultTime, 5, 1, 1, 1);

        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(15, -1, -1, -1);
        m_check_AN = new QCheckBox(groupBox);
        m_check_AN->setObjectName(QString::fromUtf8("m_check_AN"));
        sizePolicy.setHeightForWidth(m_check_AN->sizePolicy().hasHeightForWidth());
        m_check_AN->setSizePolicy(sizePolicy);
        m_check_AN->setMinimumSize(QSize(0, 0));
        m_check_AN->setMaximumSize(QSize(80, 16777215));
        m_check_AN->setChecked(true);

        gridLayout->addWidget(m_check_AN, 0, 1, 1, 1);

        m_check_BC = new QCheckBox(groupBox);
        m_check_BC->setObjectName(QString::fromUtf8("m_check_BC"));
        sizePolicy.setHeightForWidth(m_check_BC->sizePolicy().hasHeightForWidth());
        m_check_BC->setSizePolicy(sizePolicy);
        m_check_BC->setMinimumSize(QSize(0, 0));
        m_check_BC->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_check_BC, 1, 2, 1, 1);

        m_check_AB = new QCheckBox(groupBox);
        m_check_AB->setObjectName(QString::fromUtf8("m_check_AB"));
        sizePolicy.setHeightForWidth(m_check_AB->sizePolicy().hasHeightForWidth());
        m_check_AB->setSizePolicy(sizePolicy);
        m_check_AB->setMinimumSize(QSize(0, 0));
        m_check_AB->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_check_AB, 1, 1, 1, 1);

        m_check_CA = new QCheckBox(groupBox);
        m_check_CA->setObjectName(QString::fromUtf8("m_check_CA"));
        sizePolicy.setHeightForWidth(m_check_CA->sizePolicy().hasHeightForWidth());
        m_check_CA->setSizePolicy(sizePolicy);
        m_check_CA->setMinimumSize(QSize(0, 0));
        m_check_CA->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_check_CA, 1, 3, 1, 1);

        m_check_BN = new QCheckBox(groupBox);
        m_check_BN->setObjectName(QString::fromUtf8("m_check_BN"));
        sizePolicy.setHeightForWidth(m_check_BN->sizePolicy().hasHeightForWidth());
        m_check_BN->setSizePolicy(sizePolicy);
        m_check_BN->setMinimumSize(QSize(0, 0));
        m_check_BN->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_check_BN, 0, 2, 1, 1);

        m_check_CN = new QCheckBox(groupBox);
        m_check_CN->setObjectName(QString::fromUtf8("m_check_CN"));
        sizePolicy.setHeightForWidth(m_check_CN->sizePolicy().hasHeightForWidth());
        m_check_CN->setSizePolicy(sizePolicy);
        m_check_CN->setMinimumSize(QSize(0, 0));
        m_check_CN->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_check_CN, 0, 3, 1, 1);

        m_check_ABC = new QCheckBox(groupBox);
        m_check_ABC->setObjectName(QString::fromUtf8("m_check_ABC"));
        sizePolicy.setHeightForWidth(m_check_ABC->sizePolicy().hasHeightForWidth());
        m_check_ABC->setSizePolicy(sizePolicy);
        m_check_ABC->setMinimumSize(QSize(0, 0));
        m_check_ABC->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(m_check_ABC, 1, 4, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 2, 6, 1);

        m_check_Harm = new QCheckBox(frame_2);
        m_check_Harm->setObjectName(QString::fromUtf8("m_check_Harm"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_check_Harm->sizePolicy().hasHeightForWidth());
        m_check_Harm->setSizePolicy(sizePolicy2);
        m_check_Harm->setMinimumSize(QSize(0, 0));
        m_check_Harm->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(m_check_Harm, 1, 0, 1, 2);

        m_check_Time = new QCheckBox(frame_2);
        m_check_Time->setObjectName(QString::fromUtf8("m_check_Time"));
        sizePolicy2.setHeightForWidth(m_check_Time->sizePolicy().hasHeightForWidth());
        m_check_Time->setSizePolicy(sizePolicy2);
        m_check_Time->setMinimumSize(QSize(0, 0));
        m_check_Time->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(m_check_Time, 2, 0, 1, 2);

        m_check_Rate = new QCheckBox(frame_2);
        m_check_Rate->setObjectName(QString::fromUtf8("m_check_Rate"));
        sizePolicy2.setHeightForWidth(m_check_Rate->sizePolicy().hasHeightForWidth());
        m_check_Rate->setSizePolicy(sizePolicy2);
        m_check_Rate->setMinimumSize(QSize(0, 0));
        m_check_Rate->setMaximumSize(QSize(16777215, 16777215));
        m_check_Rate->setChecked(true);

        gridLayout_2->addWidget(m_check_Rate, 0, 0, 1, 2);


        verticalLayout->addWidget(frame_2);

        verticalLayout->setStretch(0, 5);

        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 3);

        tabWidget = new QTabWidget(QDiffAddBatchDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        VLayout_Rate = new QVBoxLayout();
        VLayout_Rate->setObjectName(QString::fromUtf8("VLayout_Rate"));

        horizontalLayout->addLayout(VLayout_Rate);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        VLayout_Harm = new QVBoxLayout();
        VLayout_Harm->setObjectName(QString::fromUtf8("VLayout_Harm"));

        verticalLayout_4->addLayout(VLayout_Harm);

        tabWidget->addTab(tab_2, QString());

        gridLayout_3->addWidget(tabWidget, 1, 0, 1, 3);

        m_btnResEvaluat = new QPushButton(QDiffAddBatchDlg);
        m_btnResEvaluat->setObjectName(QString::fromUtf8("m_btnResEvaluat"));
        m_btnResEvaluat->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(m_btnResEvaluat, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(150, 27, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 3, 0, 1, 1);

        m_labTips = new QLabel(QDiffAddBatchDlg);
        m_labTips->setObjectName(QString::fromUtf8("m_labTips"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_labTips->sizePolicy().hasHeightForWidth());
        m_labTips->setSizePolicy(sizePolicy3);
        m_labTips->setMinimumSize(QSize(0, 0));
        m_labTips->setMaximumSize(QSize(16777215, 16777215));
        m_labTips->setFont(font);
        m_labTips->setStyleSheet(QString::fromUtf8("QLabel{border:2px groove rgb(0,0,255);border-radius:10px;background-color: rgb(255,242,204)}"));
        m_labTips->setWordWrap(true);

        gridLayout_3->addWidget(m_labTips, 3, 2, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(15);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_btnSave = new QPushButton(QDiffAddBatchDlg);
        m_btnSave->setObjectName(QString::fromUtf8("m_btnSave"));
        sizePolicy.setHeightForWidth(m_btnSave->sizePolicy().hasHeightForWidth());
        m_btnSave->setSizePolicy(sizePolicy);
        m_btnSave->setMinimumSize(QSize(100, 23));
        m_btnSave->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_7->addWidget(m_btnSave);

        m_btnClose = new QPushButton(QDiffAddBatchDlg);
        m_btnClose->setObjectName(QString::fromUtf8("m_btnClose"));
        sizePolicy.setHeightForWidth(m_btnClose->sizePolicy().hasHeightForWidth());
        m_btnClose->setSizePolicy(sizePolicy);
        m_btnClose->setMinimumSize(QSize(100, 0));
        m_btnClose->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_7->addWidget(m_btnClose);


        gridLayout_3->addLayout(horizontalLayout_7, 3, 1, 1, 1);

        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnStretch(2, 1);

        retranslateUi(QDiffAddBatchDlg);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QDiffAddBatchDlg);
    } // setupUi

    void retranslateUi(QDialog *QDiffAddBatchDlg)
    {
        QDiffAddBatchDlg->setWindowTitle(QApplication::translate("QDiffAddBatchDlg", "\346\211\271\351\207\217\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        m_labTime_lr->setText(QApplication::translate("QDiffAddBatchDlg", "Ir():", 0, QApplication::UnicodeUTF8));
        m_labTime_ld->setText(QApplication::translate("QDiffAddBatchDlg", "Id():", 0, QApplication::UnicodeUTF8));
        m_labTime_ld_2->setText(QApplication::translate("QDiffAddBatchDlg", "\346\234\200\345\244\247\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QDiffAddBatchDlg", "\346\225\205\351\232\234\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        m_check_AN->setText(QApplication::translate("QDiffAddBatchDlg", "AN", 0, QApplication::UnicodeUTF8));
        m_check_BC->setText(QApplication::translate("QDiffAddBatchDlg", "BC", 0, QApplication::UnicodeUTF8));
        m_check_AB->setText(QApplication::translate("QDiffAddBatchDlg", "AB", 0, QApplication::UnicodeUTF8));
        m_check_CA->setText(QApplication::translate("QDiffAddBatchDlg", "CA", 0, QApplication::UnicodeUTF8));
        m_check_BN->setText(QApplication::translate("QDiffAddBatchDlg", "BN", 0, QApplication::UnicodeUTF8));
        m_check_CN->setText(QApplication::translate("QDiffAddBatchDlg", "CN", 0, QApplication::UnicodeUTF8));
        m_check_ABC->setText(QApplication::translate("QDiffAddBatchDlg", "ABC", 0, QApplication::UnicodeUTF8));
        m_check_Harm->setText(QApplication::translate("QDiffAddBatchDlg", "\350\260\220\346\263\242\345\210\266\345\212\250\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
        m_check_Time->setText(QApplication::translate("QDiffAddBatchDlg", "\345\212\250\344\275\234\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        m_check_Rate->setText(QApplication::translate("QDiffAddBatchDlg", "\345\267\256\345\212\250\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QDiffAddBatchDlg", "\345\267\256\345\212\250\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QDiffAddBatchDlg", "\350\260\220\346\263\242\345\210\266\345\212\250\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
        m_btnResEvaluat->setText(QApplication::translate("QDiffAddBatchDlg", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_labTips->setText(QString());
        m_btnSave->setText(QApplication::translate("QDiffAddBatchDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnClose->setText(QApplication::translate("QDiffAddBatchDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDiffAddBatchDlg: public Ui_QDiffAddBatchDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFADDBATCHDLG_H
