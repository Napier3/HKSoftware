/********************************************************************************
** Form generated from reading UI file 'DistanceSearchBinarySignalDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCESEARCHBINARYSIGNALDLG_H
#define UI_DISTANCESEARCHBINARYSIGNALDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QDistanceSearchBinarySignalDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *m_tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *m_cbBinSelectA;
    QCheckBox *m_cbBinSelectF;
    QCheckBox *m_cbBinSelectC;
    QCheckBox *m_cbBinSelectB;
    QCheckBox *m_cbBinSelectD;
    QCheckBox *m_cbBinSelectG;
    QCheckBox *m_cbBinSelectH;
    QCheckBox *m_cbBinSelectE;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_13;
    QRadioButton *m_rbAnd;
    QSpacerItem *horizontalSpacer_15;
    QRadioButton *m_rbOr;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_9;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *horizontalSpacer_17;
    QLabel *m_labBout4;
    QLabel *m_labBout2;
    QComboBox *m_cbbB01;
    QLabel *m_labBout3;
    QLabel *m_labBout1;
    QLabel *m_labBout6;
    QLabel *m_labOutputKeepTime;
    QLabel *m_labBout7;
    QLabel *m_labOutputSwitchMode;
    QLabel *m_labBout8;
    QLineEdit *m_editOutputKeepTime;
    QLineEdit *m_editOutputDelayTime;
    QComboBox *m_cbbOutputSwitchMode;
    QLabel *m_labBout5;
    QLabel *m_labOutputDelayTime;
    QComboBox *m_cbbB06;
    QComboBox *m_cbbB05;
    QComboBox *m_cbbB03;
    QComboBox *m_cbbB02;
    QComboBox *m_cbbB04;
    QComboBox *m_cbbB08;
    QComboBox *m_cbbB07;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_19;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *QDistanceSearchBinarySignalDlg)
    {
        if (QDistanceSearchBinarySignalDlg->objectName().isEmpty())
            QDistanceSearchBinarySignalDlg->setObjectName(QString::fromUtf8("QDistanceSearchBinarySignalDlg"));
        QDistanceSearchBinarySignalDlg->resize(343, 401);
        horizontalLayout = new QHBoxLayout(QDistanceSearchBinarySignalDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_tabWidget = new QTabWidget(QDistanceSearchBinarySignalDlg);
        m_tabWidget->setObjectName(QString::fromUtf8("m_tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_4 = new QHBoxLayout(tab);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 0, 1, 1);

        m_cbBinSelectA = new QCheckBox(frame);
        m_cbBinSelectA->setObjectName(QString::fromUtf8("m_cbBinSelectA"));

        gridLayout_2->addWidget(m_cbBinSelectA, 1, 0, 1, 1);

        m_cbBinSelectF = new QCheckBox(frame);
        m_cbBinSelectF->setObjectName(QString::fromUtf8("m_cbBinSelectF"));

        gridLayout_2->addWidget(m_cbBinSelectF, 3, 1, 1, 1);

        m_cbBinSelectC = new QCheckBox(frame);
        m_cbBinSelectC->setObjectName(QString::fromUtf8("m_cbBinSelectC"));

        gridLayout_2->addWidget(m_cbBinSelectC, 1, 2, 1, 1);

        m_cbBinSelectB = new QCheckBox(frame);
        m_cbBinSelectB->setObjectName(QString::fromUtf8("m_cbBinSelectB"));

        gridLayout_2->addWidget(m_cbBinSelectB, 1, 1, 1, 1);

        m_cbBinSelectD = new QCheckBox(frame);
        m_cbBinSelectD->setObjectName(QString::fromUtf8("m_cbBinSelectD"));

        gridLayout_2->addWidget(m_cbBinSelectD, 1, 3, 1, 1);

        m_cbBinSelectG = new QCheckBox(frame);
        m_cbBinSelectG->setObjectName(QString::fromUtf8("m_cbBinSelectG"));

        gridLayout_2->addWidget(m_cbBinSelectG, 3, 2, 1, 1);

        m_cbBinSelectH = new QCheckBox(frame);
        m_cbBinSelectH->setObjectName(QString::fromUtf8("m_cbBinSelectH"));

        gridLayout_2->addWidget(m_cbBinSelectH, 3, 3, 1, 1);

        m_cbBinSelectE = new QCheckBox(frame);
        m_cbBinSelectE->setObjectName(QString::fromUtf8("m_cbBinSelectE"));

        gridLayout_2->addWidget(m_cbBinSelectE, 3, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 4, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_13);

        m_rbAnd = new QRadioButton(frame);
        m_rbAnd->setObjectName(QString::fromUtf8("m_rbAnd"));

        horizontalLayout_7->addWidget(m_rbAnd);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_15);

        m_rbOr = new QRadioButton(frame);
        m_rbOr->setObjectName(QString::fromUtf8("m_rbOr"));

        horizontalLayout_7->addWidget(m_rbOr);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_14);


        verticalLayout_3->addLayout(horizontalLayout_7);


        horizontalLayout_8->addLayout(verticalLayout_3);


        verticalLayout_2->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_2);

        m_tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        frame_2 = new QFrame(tab_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame_2);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_16, 0, 0, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_17, 0, 2, 1, 1);

        m_labBout4 = new QLabel(frame_2);
        m_labBout4->setObjectName(QString::fromUtf8("m_labBout4"));

        gridLayout->addWidget(m_labBout4, 3, 1, 1, 1);

        m_labBout2 = new QLabel(frame_2);
        m_labBout2->setObjectName(QString::fromUtf8("m_labBout2"));

        gridLayout->addWidget(m_labBout2, 1, 1, 1, 1);

        m_cbbB01 = new QComboBox(frame_2);
        m_cbbB01->setObjectName(QString::fromUtf8("m_cbbB01"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_cbbB01->sizePolicy().hasHeightForWidth());
        m_cbbB01->setSizePolicy(sizePolicy);
        m_cbbB01->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbB01, 0, 3, 1, 1);

        m_labBout3 = new QLabel(frame_2);
        m_labBout3->setObjectName(QString::fromUtf8("m_labBout3"));

        gridLayout->addWidget(m_labBout3, 2, 1, 1, 1);

        m_labBout1 = new QLabel(frame_2);
        m_labBout1->setObjectName(QString::fromUtf8("m_labBout1"));

        gridLayout->addWidget(m_labBout1, 0, 1, 1, 1);

        m_labBout6 = new QLabel(frame_2);
        m_labBout6->setObjectName(QString::fromUtf8("m_labBout6"));

        gridLayout->addWidget(m_labBout6, 5, 1, 1, 1);

        m_labOutputKeepTime = new QLabel(frame_2);
        m_labOutputKeepTime->setObjectName(QString::fromUtf8("m_labOutputKeepTime"));

        gridLayout->addWidget(m_labOutputKeepTime, 9, 1, 1, 1);

        m_labBout7 = new QLabel(frame_2);
        m_labBout7->setObjectName(QString::fromUtf8("m_labBout7"));

        gridLayout->addWidget(m_labBout7, 6, 1, 1, 1);

        m_labOutputSwitchMode = new QLabel(frame_2);
        m_labOutputSwitchMode->setObjectName(QString::fromUtf8("m_labOutputSwitchMode"));

        gridLayout->addWidget(m_labOutputSwitchMode, 8, 1, 1, 1);

        m_labBout8 = new QLabel(frame_2);
        m_labBout8->setObjectName(QString::fromUtf8("m_labBout8"));

        gridLayout->addWidget(m_labBout8, 7, 1, 1, 1);

        m_editOutputKeepTime = new QLineEdit(frame_2);
        m_editOutputKeepTime->setObjectName(QString::fromUtf8("m_editOutputKeepTime"));
        sizePolicy.setHeightForWidth(m_editOutputKeepTime->sizePolicy().hasHeightForWidth());
        m_editOutputKeepTime->setSizePolicy(sizePolicy);
        m_editOutputKeepTime->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_editOutputKeepTime, 9, 3, 1, 1);

        m_editOutputDelayTime = new QLineEdit(frame_2);
        m_editOutputDelayTime->setObjectName(QString::fromUtf8("m_editOutputDelayTime"));
        sizePolicy.setHeightForWidth(m_editOutputDelayTime->sizePolicy().hasHeightForWidth());
        m_editOutputDelayTime->setSizePolicy(sizePolicy);
        m_editOutputDelayTime->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_editOutputDelayTime, 10, 3, 1, 1);

        m_cbbOutputSwitchMode = new QComboBox(frame_2);
        m_cbbOutputSwitchMode->setObjectName(QString::fromUtf8("m_cbbOutputSwitchMode"));
        sizePolicy.setHeightForWidth(m_cbbOutputSwitchMode->sizePolicy().hasHeightForWidth());
        m_cbbOutputSwitchMode->setSizePolicy(sizePolicy);
        m_cbbOutputSwitchMode->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbOutputSwitchMode, 8, 3, 1, 1);

        m_labBout5 = new QLabel(frame_2);
        m_labBout5->setObjectName(QString::fromUtf8("m_labBout5"));

        gridLayout->addWidget(m_labBout5, 4, 1, 1, 1);

        m_labOutputDelayTime = new QLabel(frame_2);
        m_labOutputDelayTime->setObjectName(QString::fromUtf8("m_labOutputDelayTime"));

        gridLayout->addWidget(m_labOutputDelayTime, 10, 1, 1, 1);

        m_cbbB06 = new QComboBox(frame_2);
        m_cbbB06->setObjectName(QString::fromUtf8("m_cbbB06"));
        sizePolicy.setHeightForWidth(m_cbbB06->sizePolicy().hasHeightForWidth());
        m_cbbB06->setSizePolicy(sizePolicy);
        m_cbbB06->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbB06, 5, 3, 1, 1);

        m_cbbB05 = new QComboBox(frame_2);
        m_cbbB05->setObjectName(QString::fromUtf8("m_cbbB05"));
        sizePolicy.setHeightForWidth(m_cbbB05->sizePolicy().hasHeightForWidth());
        m_cbbB05->setSizePolicy(sizePolicy);
        m_cbbB05->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbB05, 4, 3, 1, 1);

        m_cbbB03 = new QComboBox(frame_2);
        m_cbbB03->setObjectName(QString::fromUtf8("m_cbbB03"));
        sizePolicy.setHeightForWidth(m_cbbB03->sizePolicy().hasHeightForWidth());
        m_cbbB03->setSizePolicy(sizePolicy);
        m_cbbB03->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbB03, 2, 3, 1, 1);

        m_cbbB02 = new QComboBox(frame_2);
        m_cbbB02->setObjectName(QString::fromUtf8("m_cbbB02"));
        sizePolicy.setHeightForWidth(m_cbbB02->sizePolicy().hasHeightForWidth());
        m_cbbB02->setSizePolicy(sizePolicy);
        m_cbbB02->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbB02, 1, 3, 1, 1);

        m_cbbB04 = new QComboBox(frame_2);
        m_cbbB04->setObjectName(QString::fromUtf8("m_cbbB04"));
        sizePolicy.setHeightForWidth(m_cbbB04->sizePolicy().hasHeightForWidth());
        m_cbbB04->setSizePolicy(sizePolicy);
        m_cbbB04->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbB04, 3, 3, 1, 1);

        m_cbbB08 = new QComboBox(frame_2);
        m_cbbB08->setObjectName(QString::fromUtf8("m_cbbB08"));
        sizePolicy.setHeightForWidth(m_cbbB08->sizePolicy().hasHeightForWidth());
        m_cbbB08->setSizePolicy(sizePolicy);
        m_cbbB08->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbB08, 7, 3, 1, 1);

        m_cbbB07 = new QComboBox(frame_2);
        m_cbbB07->setObjectName(QString::fromUtf8("m_cbbB07"));
        sizePolicy.setHeightForWidth(m_cbbB07->sizePolicy().hasHeightForWidth());
        m_cbbB07->setSizePolicy(sizePolicy);
        m_cbbB07->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbB07, 6, 3, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_18, 0, 4, 1, 1);


        horizontalLayout_9->addLayout(gridLayout);


        verticalLayout_4->addWidget(frame_2);


        horizontalLayout_3->addLayout(verticalLayout_4);

        m_tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(m_tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_btnOk = new QPushButton(QDistanceSearchBinarySignalDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));

        horizontalLayout_2->addWidget(m_btnOk);

        horizontalSpacer_19 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_19);

        m_btnCancel = new QPushButton(QDistanceSearchBinarySignalDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout_2->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QDistanceSearchBinarySignalDlg);

        m_tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QDistanceSearchBinarySignalDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceSearchBinarySignalDlg)
    {
        QDistanceSearchBinarySignalDlg->setWindowTitle(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\263\351\207\217", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectA->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\245A", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectF->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\245F", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectC->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\245C", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectB->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\245B", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectD->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\245D", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectG->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\245G", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectH->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\245H", 0, QApplication::UnicodeUTF8));
        m_cbBinSelectE->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\245E", 0, QApplication::UnicodeUTF8));
        m_rbAnd->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_rbOr->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab), QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_labBout4->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\2724:", 0, QApplication::UnicodeUTF8));
        m_labBout2->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\2722:", 0, QApplication::UnicodeUTF8));
        m_labBout3->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\2723:", 0, QApplication::UnicodeUTF8));
        m_labBout1->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\2721:", 0, QApplication::UnicodeUTF8));
        m_labBout6->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\2726:", 0, QApplication::UnicodeUTF8));
        m_labOutputKeepTime->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\272\344\277\235\346\214\201\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        m_labBout7->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\2727:", 0, QApplication::UnicodeUTF8));
        m_labOutputSwitchMode->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\272\347\277\273\350\275\254\345\220\257\345\212\250\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labBout8->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\2728:", 0, QApplication::UnicodeUTF8));
        m_labBout5->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\2725:", 0, QApplication::UnicodeUTF8));
        m_labOutputDelayTime->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\272\347\277\273\350\275\254\346\227\266\345\210\273:", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab_2), QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\274\200\345\207\272\351\207\217", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDistanceSearchBinarySignalDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceSearchBinarySignalDlg: public Ui_QDistanceSearchBinarySignalDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCESEARCHBINARYSIGNALDLG_H
