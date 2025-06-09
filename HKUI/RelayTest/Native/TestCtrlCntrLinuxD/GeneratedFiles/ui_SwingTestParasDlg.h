/********************************************************************************
** Form generated from reading UI file 'SwingTestParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWINGTESTPARASDLG_H
#define UI_SWINGTESTPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
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

class Ui_QSwingTestParasDlg
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labSwingTime;
    QSpacerItem *horizontalSpacer_15;
    QLineEdit *m_editPreFaultTime;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *m_labCTPos;
    QSpacerItem *horizontalSpacer_16;
    QComboBox *m_cbbCTPos;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *m_labSysZs;
    QSpacerItem *horizontalSpacer_17;
    QLineEdit *m_editImpSys;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_7;
    QLabel *m_labSysZsPhi;
    QSpacerItem *horizontalSpacer_18;
    QLineEdit *m_editImpSysPh;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_9;
    QLabel *m_labTransZt;
    QSpacerItem *horizontalSpacer_19;
    QLineEdit *m_editImpTf;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_11;
    QLabel *m_labTransZtPhi;
    QSpacerItem *horizontalSpacer_20;
    QLineEdit *m_editImpTfPh;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_13;
    QLabel *m_labImpTs;
    QSpacerItem *horizontalSpacer_21;
    QLineEdit *m_editImpTs;
    QSpacerItem *horizontalSpacer_14;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *m_cbBout1;
    QCheckBox *m_cbBout2;
    QCheckBox *m_cbBout3;
    QCheckBox *m_cbBout4;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *m_cbBout5;
    QCheckBox *m_cbBout6;
    QCheckBox *m_cbBout7;
    QCheckBox *m_cbBout8;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_22;
    QPushButton *m_btnOk;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_23;

    void setupUi(QDialog *QSwingTestParasDlg)
    {
        if (QSwingTestParasDlg->objectName().isEmpty())
            QSwingTestParasDlg->setObjectName(QString::fromUtf8("QSwingTestParasDlg"));
        QSwingTestParasDlg->resize(600, 400);
        QSwingTestParasDlg->setMinimumSize(QSize(600, 400));
        QSwingTestParasDlg->setMaximumSize(QSize(600, 400));
        tabWidget = new QTabWidget(QSwingTestParasDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(6, 9, 581, 321));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 0, 564, 291));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 10, 0, 10);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        m_labSwingTime = new QLabel(verticalLayoutWidget);
        m_labSwingTime->setObjectName(QString::fromUtf8("m_labSwingTime"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labSwingTime->sizePolicy().hasHeightForWidth());
        m_labSwingTime->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(m_labSwingTime);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_15);

        m_editPreFaultTime = new QLineEdit(verticalLayoutWidget);
        m_editPreFaultTime->setObjectName(QString::fromUtf8("m_editPreFaultTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_editPreFaultTime->sizePolicy().hasHeightForWidth());
        m_editPreFaultTime->setSizePolicy(sizePolicy1);
        m_editPreFaultTime->setMinimumSize(QSize(250, 0));
        m_editPreFaultTime->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_2->addWidget(m_editPreFaultTime);

        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        m_labCTPos = new QLabel(verticalLayoutWidget);
        m_labCTPos->setObjectName(QString::fromUtf8("m_labCTPos"));
        sizePolicy.setHeightForWidth(m_labCTPos->sizePolicy().hasHeightForWidth());
        m_labCTPos->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(m_labCTPos);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_16);

        m_cbbCTPos = new QComboBox(verticalLayoutWidget);
        m_cbbCTPos->setObjectName(QString::fromUtf8("m_cbbCTPos"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_cbbCTPos->sizePolicy().hasHeightForWidth());
        m_cbbCTPos->setSizePolicy(sizePolicy2);
        m_cbbCTPos->setMinimumSize(QSize(250, 0));
        m_cbbCTPos->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_3->addWidget(m_cbbCTPos);

        horizontalSpacer_4 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        m_labSysZs = new QLabel(verticalLayoutWidget);
        m_labSysZs->setObjectName(QString::fromUtf8("m_labSysZs"));
        sizePolicy.setHeightForWidth(m_labSysZs->sizePolicy().hasHeightForWidth());
        m_labSysZs->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(m_labSysZs);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_17);

        m_editImpSys = new QLineEdit(verticalLayoutWidget);
        m_editImpSys->setObjectName(QString::fromUtf8("m_editImpSys"));
        sizePolicy2.setHeightForWidth(m_editImpSys->sizePolicy().hasHeightForWidth());
        m_editImpSys->setSizePolicy(sizePolicy2);
        m_editImpSys->setMinimumSize(QSize(250, 0));
        m_editImpSys->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_4->addWidget(m_editImpSys);

        horizontalSpacer_6 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_7 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        m_labSysZsPhi = new QLabel(verticalLayoutWidget);
        m_labSysZsPhi->setObjectName(QString::fromUtf8("m_labSysZsPhi"));
        sizePolicy.setHeightForWidth(m_labSysZsPhi->sizePolicy().hasHeightForWidth());
        m_labSysZsPhi->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(m_labSysZsPhi);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_18);

        m_editImpSysPh = new QLineEdit(verticalLayoutWidget);
        m_editImpSysPh->setObjectName(QString::fromUtf8("m_editImpSysPh"));
        sizePolicy2.setHeightForWidth(m_editImpSysPh->sizePolicy().hasHeightForWidth());
        m_editImpSysPh->setSizePolicy(sizePolicy2);
        m_editImpSysPh->setMinimumSize(QSize(250, 0));
        m_editImpSysPh->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_5->addWidget(m_editImpSysPh);

        horizontalSpacer_8 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_9 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        m_labTransZt = new QLabel(verticalLayoutWidget);
        m_labTransZt->setObjectName(QString::fromUtf8("m_labTransZt"));
        sizePolicy.setHeightForWidth(m_labTransZt->sizePolicy().hasHeightForWidth());
        m_labTransZt->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(m_labTransZt);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_19);

        m_editImpTf = new QLineEdit(verticalLayoutWidget);
        m_editImpTf->setObjectName(QString::fromUtf8("m_editImpTf"));
        sizePolicy2.setHeightForWidth(m_editImpTf->sizePolicy().hasHeightForWidth());
        m_editImpTf->setSizePolicy(sizePolicy2);
        m_editImpTf->setMinimumSize(QSize(250, 0));
        m_editImpTf->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_6->addWidget(m_editImpTf);

        horizontalSpacer_10 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_11 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        m_labTransZtPhi = new QLabel(verticalLayoutWidget);
        m_labTransZtPhi->setObjectName(QString::fromUtf8("m_labTransZtPhi"));
        sizePolicy.setHeightForWidth(m_labTransZtPhi->sizePolicy().hasHeightForWidth());
        m_labTransZtPhi->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(m_labTransZtPhi);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_20);

        m_editImpTfPh = new QLineEdit(verticalLayoutWidget);
        m_editImpTfPh->setObjectName(QString::fromUtf8("m_editImpTfPh"));
        sizePolicy2.setHeightForWidth(m_editImpTfPh->sizePolicy().hasHeightForWidth());
        m_editImpTfPh->setSizePolicy(sizePolicy2);
        m_editImpTfPh->setMinimumSize(QSize(250, 0));
        m_editImpTfPh->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_7->addWidget(m_editImpTfPh);

        horizontalSpacer_12 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_13 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        m_labImpTs = new QLabel(verticalLayoutWidget);
        m_labImpTs->setObjectName(QString::fromUtf8("m_labImpTs"));
        sizePolicy.setHeightForWidth(m_labImpTs->sizePolicy().hasHeightForWidth());
        m_labImpTs->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(m_labImpTs);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_21);

        m_editImpTs = new QLineEdit(verticalLayoutWidget);
        m_editImpTs->setObjectName(QString::fromUtf8("m_editImpTs"));
        sizePolicy2.setHeightForWidth(m_editImpTs->sizePolicy().hasHeightForWidth());
        m_editImpTs->setSizePolicy(sizePolicy2);
        m_editImpTs->setMinimumSize(QSize(250, 0));
        m_editImpTs->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_8->addWidget(m_editImpTs);

        horizontalSpacer_14 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);


        verticalLayout->addLayout(horizontalLayout_8);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayoutWidget_2 = new QWidget(tab_2);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(59, 19, 451, 241));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        m_cbBout1 = new QCheckBox(verticalLayoutWidget_2);
        m_cbBout1->setObjectName(QString::fromUtf8("m_cbBout1"));

        horizontalLayout_9->addWidget(m_cbBout1);

        m_cbBout2 = new QCheckBox(verticalLayoutWidget_2);
        m_cbBout2->setObjectName(QString::fromUtf8("m_cbBout2"));

        horizontalLayout_9->addWidget(m_cbBout2);

        m_cbBout3 = new QCheckBox(verticalLayoutWidget_2);
        m_cbBout3->setObjectName(QString::fromUtf8("m_cbBout3"));

        horizontalLayout_9->addWidget(m_cbBout3);

        m_cbBout4 = new QCheckBox(verticalLayoutWidget_2);
        m_cbBout4->setObjectName(QString::fromUtf8("m_cbBout4"));

        horizontalLayout_9->addWidget(m_cbBout4);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        m_cbBout5 = new QCheckBox(verticalLayoutWidget_2);
        m_cbBout5->setObjectName(QString::fromUtf8("m_cbBout5"));

        horizontalLayout_10->addWidget(m_cbBout5);

        m_cbBout6 = new QCheckBox(verticalLayoutWidget_2);
        m_cbBout6->setObjectName(QString::fromUtf8("m_cbBout6"));

        horizontalLayout_10->addWidget(m_cbBout6);

        m_cbBout7 = new QCheckBox(verticalLayoutWidget_2);
        m_cbBout7->setObjectName(QString::fromUtf8("m_cbBout7"));

        horizontalLayout_10->addWidget(m_cbBout7);

        m_cbBout8 = new QCheckBox(verticalLayoutWidget_2);
        m_cbBout8->setObjectName(QString::fromUtf8("m_cbBout8"));

        horizontalLayout_10->addWidget(m_cbBout8);


        verticalLayout_2->addLayout(horizontalLayout_10);

        tabWidget->addTab(tab_2, QString());
        horizontalLayoutWidget = new QWidget(QSwingTestParasDlg);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 330, 581, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_22);

        m_btnOk = new QPushButton(horizontalLayoutWidget);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        sizePolicy2.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(m_btnOk);

        m_btnCancel = new QPushButton(horizontalLayoutWidget);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy2.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_23);


        retranslateUi(QSwingTestParasDlg);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QSwingTestParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QSwingTestParasDlg)
    {
        QSwingTestParasDlg->setWindowTitle(QApplication::translate("QSwingTestParasDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        m_labSwingTime->setText(QApplication::translate("QSwingTestParasDlg", "\346\214\257\350\215\241\345\211\215\346\227\266\351\227\264(s)\357\274\232", 0, QApplication::UnicodeUTF8));
        m_labCTPos->setText(QApplication::translate("QSwingTestParasDlg", "TA\346\255\243\346\236\201\346\200\247\357\274\232", 0, QApplication::UnicodeUTF8));
        m_cbbCTPos->clear();
        m_cbbCTPos->insertItems(0, QStringList()
         << QApplication::translate("QSwingTestParasDlg", "\346\214\207\345\220\221\346\257\215\347\272\277", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSwingTestParasDlg", "\346\214\207\345\220\221\347\272\277\350\267\257", 0, QApplication::UnicodeUTF8)
        );
        m_labSysZs->setText(QApplication::translate("QSwingTestParasDlg", "\347\263\273\347\273\237\344\276\247\351\230\273\346\212\227|Zs|(\316\251)\357\274\232", 0, QApplication::UnicodeUTF8));
        m_labSysZsPhi->setText(QApplication::translate("QSwingTestParasDlg", "PhI(Zs)(\302\260)\357\274\232", 0, QApplication::UnicodeUTF8));
        m_labTransZt->setText(QApplication::translate("QSwingTestParasDlg", "\345\217\230\345\216\213\345\231\250\351\230\273\346\212\227|Zt|(\316\251)\357\274\232", 0, QApplication::UnicodeUTF8));
        m_labTransZtPhi->setText(QApplication::translate("QSwingTestParasDlg", "Phi(Zt)(\302\260)\357\274\232", 0, QApplication::UnicodeUTF8));
        m_labImpTs->setText(QApplication::translate("QSwingTestParasDlg", "\345\217\221\347\224\265\346\234\272\346\232\202\346\200\201\347\224\265\346\212\227(\316\251)\357\274\232", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QSwingTestParasDlg", "Tab 1", 0, QApplication::UnicodeUTF8));
        m_cbBout1->setText(QApplication::translate("QSwingTestParasDlg", "\345\274\200\345\207\2721", 0, QApplication::UnicodeUTF8));
        m_cbBout2->setText(QApplication::translate("QSwingTestParasDlg", "\345\274\200\345\207\2722", 0, QApplication::UnicodeUTF8));
        m_cbBout3->setText(QApplication::translate("QSwingTestParasDlg", "\345\274\200\345\207\2723", 0, QApplication::UnicodeUTF8));
        m_cbBout4->setText(QApplication::translate("QSwingTestParasDlg", "\345\274\200\345\207\2724", 0, QApplication::UnicodeUTF8));
        m_cbBout5->setText(QApplication::translate("QSwingTestParasDlg", "\345\274\200\345\207\2725", 0, QApplication::UnicodeUTF8));
        m_cbBout6->setText(QApplication::translate("QSwingTestParasDlg", "\345\274\200\345\207\2726", 0, QApplication::UnicodeUTF8));
        m_cbBout7->setText(QApplication::translate("QSwingTestParasDlg", "\345\274\200\345\207\2727", 0, QApplication::UnicodeUTF8));
        m_cbBout8->setText(QApplication::translate("QSwingTestParasDlg", "\345\274\200\345\207\2728", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QSwingTestParasDlg", "Tab 2", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QSwingTestParasDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QSwingTestParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSwingTestParasDlg: public Ui_QSwingTestParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWINGTESTPARASDLG_H
