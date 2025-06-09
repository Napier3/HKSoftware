/********************************************************************************
** Form generated from reading UI file 'QAinDataMapDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QAINDATAMAPDLG_H
#define UI_QAINDATAMAPDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QAinDataMapDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *m_LeftLayout;
    QLabel *m_labTip;
    QVBoxLayout *m_RightLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labDataSet;
    QComboBox *m_cmbDataSet;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_btnAdd;
    QPushButton *m_btnDelete;
    QPushButton *m_btnClearAllMap;
    QPushButton *m_btnClearClickedMap;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_stcDevMeas;
    QComboBox *m_cmbDevMeas;
    QSpacerItem *horizontalSpacer_5;
    QLabel *m_stcPt;
    QLineEdit *m_edtPtPrimary;
    QLabel *m_stcPtPirmary;
    QLineEdit *m_edtPtSecondary;
    QLabel *m_stcPtSecondary;
    QSpacerItem *horizontalSpacer_4;
    QLabel *m_stcCt;
    QLineEdit *m_edtCtPrimary;
    QLabel *m_stcCtPirmary;
    QLineEdit *m_edtCtSecondary;
    QLabel *m_stcCtSecondary;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;

    void setupUi(QDialog *QAinDataMapDlg)
    {
        if (QAinDataMapDlg->objectName().isEmpty())
            QAinDataMapDlg->setObjectName(QString::fromUtf8("QAinDataMapDlg"));
        QAinDataMapDlg->resize(1104, 614);
        verticalLayout_2 = new QVBoxLayout(QAinDataMapDlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_LeftLayout = new QVBoxLayout();
        m_LeftLayout->setObjectName(QString::fromUtf8("m_LeftLayout"));
        m_labTip = new QLabel(QAinDataMapDlg);
        m_labTip->setObjectName(QString::fromUtf8("m_labTip"));

        m_LeftLayout->addWidget(m_labTip);


        horizontalLayout_2->addLayout(m_LeftLayout);

        m_RightLayout = new QVBoxLayout();
        m_RightLayout->setObjectName(QString::fromUtf8("m_RightLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labDataSet = new QLabel(QAinDataMapDlg);
        m_labDataSet->setObjectName(QString::fromUtf8("m_labDataSet"));

        horizontalLayout->addWidget(m_labDataSet);

        m_cmbDataSet = new QComboBox(QAinDataMapDlg);
        m_cmbDataSet->setObjectName(QString::fromUtf8("m_cmbDataSet"));

        horizontalLayout->addWidget(m_cmbDataSet);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        m_RightLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(m_RightLayout);

        horizontalLayout_2->setStretch(0, 4);
        horizontalLayout_2->setStretch(1, 3);

        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_btnAdd = new QPushButton(QAinDataMapDlg);
        m_btnAdd->setObjectName(QString::fromUtf8("m_btnAdd"));

        horizontalLayout_3->addWidget(m_btnAdd);

        m_btnDelete = new QPushButton(QAinDataMapDlg);
        m_btnDelete->setObjectName(QString::fromUtf8("m_btnDelete"));

        horizontalLayout_3->addWidget(m_btnDelete);

        m_btnClearAllMap = new QPushButton(QAinDataMapDlg);
        m_btnClearAllMap->setObjectName(QString::fromUtf8("m_btnClearAllMap"));

        horizontalLayout_3->addWidget(m_btnClearAllMap);

        m_btnClearClickedMap = new QPushButton(QAinDataMapDlg);
        m_btnClearClickedMap->setObjectName(QString::fromUtf8("m_btnClearClickedMap"));

        horizontalLayout_3->addWidget(m_btnClearClickedMap);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_stcDevMeas = new QLabel(QAinDataMapDlg);
        m_stcDevMeas->setObjectName(QString::fromUtf8("m_stcDevMeas"));

        horizontalLayout_4->addWidget(m_stcDevMeas);

        m_cmbDevMeas = new QComboBox(QAinDataMapDlg);
        m_cmbDevMeas->setObjectName(QString::fromUtf8("m_cmbDevMeas"));

        horizontalLayout_4->addWidget(m_cmbDevMeas);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        m_stcPt = new QLabel(QAinDataMapDlg);
        m_stcPt->setObjectName(QString::fromUtf8("m_stcPt"));

        horizontalLayout_4->addWidget(m_stcPt);

        m_edtPtPrimary = new QLineEdit(QAinDataMapDlg);
        m_edtPtPrimary->setObjectName(QString::fromUtf8("m_edtPtPrimary"));

        horizontalLayout_4->addWidget(m_edtPtPrimary);

        m_stcPtPirmary = new QLabel(QAinDataMapDlg);
        m_stcPtPirmary->setObjectName(QString::fromUtf8("m_stcPtPirmary"));

        horizontalLayout_4->addWidget(m_stcPtPirmary);

        m_edtPtSecondary = new QLineEdit(QAinDataMapDlg);
        m_edtPtSecondary->setObjectName(QString::fromUtf8("m_edtPtSecondary"));

        horizontalLayout_4->addWidget(m_edtPtSecondary);

        m_stcPtSecondary = new QLabel(QAinDataMapDlg);
        m_stcPtSecondary->setObjectName(QString::fromUtf8("m_stcPtSecondary"));

        horizontalLayout_4->addWidget(m_stcPtSecondary);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        m_stcCt = new QLabel(QAinDataMapDlg);
        m_stcCt->setObjectName(QString::fromUtf8("m_stcCt"));

        horizontalLayout_4->addWidget(m_stcCt);

        m_edtCtPrimary = new QLineEdit(QAinDataMapDlg);
        m_edtCtPrimary->setObjectName(QString::fromUtf8("m_edtCtPrimary"));

        horizontalLayout_4->addWidget(m_edtCtPrimary);

        m_stcCtPirmary = new QLabel(QAinDataMapDlg);
        m_stcCtPirmary->setObjectName(QString::fromUtf8("m_stcCtPirmary"));

        horizontalLayout_4->addWidget(m_stcCtPirmary);

        m_edtCtSecondary = new QLineEdit(QAinDataMapDlg);
        m_edtCtSecondary->setObjectName(QString::fromUtf8("m_edtCtSecondary"));

        horizontalLayout_4->addWidget(m_edtCtSecondary);

        m_stcCtSecondary = new QLabel(QAinDataMapDlg);
        m_stcCtSecondary->setObjectName(QString::fromUtf8("m_stcCtSecondary"));

        horizontalLayout_4->addWidget(m_stcCtSecondary);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        m_btnOK = new QPushButton(QAinDataMapDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout_4->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QAinDataMapDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout_4->addWidget(m_btnCancel);


        verticalLayout_2->addLayout(horizontalLayout_4);


        retranslateUi(QAinDataMapDlg);

        QMetaObject::connectSlotsByName(QAinDataMapDlg);
    } // setupUi

    void retranslateUi(QDialog *QAinDataMapDlg)
    {
        QAinDataMapDlg->setWindowTitle(QApplication::translate("QAinDataMapDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        m_labTip->setText(QApplication::translate("QAinDataMapDlg", "\345\234\250\345\267\246\344\276\247\350\241\250\346\240\274\351\200\211\344\270\255\351\234\200\350\246\201\346\230\240\345\260\204\347\232\204\345\217\202\346\225\260\345\220\216\357\274\214\345\234\250\345\217\263\344\276\247\350\241\250\346\240\274\345\217\214\345\207\273\351\234\200\350\246\201\346\230\240\345\260\204\347\232\204\346\250\241\345\236\213\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        m_labDataSet->setText(QApplication::translate("QAinDataMapDlg", "\346\225\260\346\215\256\351\233\206\357\274\232", 0, QApplication::UnicodeUTF8));
        m_btnAdd->setText(QApplication::translate("QAinDataMapDlg", "\346\226\260\345\242\236", 0, QApplication::UnicodeUTF8));
        m_btnDelete->setText(QApplication::translate("QAinDataMapDlg", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        m_btnClearAllMap->setText(QApplication::translate("QAinDataMapDlg", "\346\270\205\347\251\272\346\211\200\346\234\211\346\230\240\345\260\204", 0, QApplication::UnicodeUTF8));
        m_btnClearClickedMap->setText(QApplication::translate("QAinDataMapDlg", "\346\270\205\351\231\244\351\200\211\344\270\255\346\230\240\345\260\204", 0, QApplication::UnicodeUTF8));
        m_stcDevMeas->setText(QApplication::translate("QAinDataMapDlg", "\350\243\205\347\275\256\351\207\207\346\240\267\357\274\232", 0, QApplication::UnicodeUTF8));
        m_stcPt->setText(QApplication::translate("QAinDataMapDlg", "PT\345\217\230\346\257\224\357\274\232", 0, QApplication::UnicodeUTF8));
        m_stcPtPirmary->setText(QApplication::translate("QAinDataMapDlg", "kV /", 0, QApplication::UnicodeUTF8));
        m_stcPtSecondary->setText(QApplication::translate("QAinDataMapDlg", "V", 0, QApplication::UnicodeUTF8));
        m_stcCt->setText(QApplication::translate("QAinDataMapDlg", "CT\345\217\230\346\257\224\357\274\232", 0, QApplication::UnicodeUTF8));
        m_stcCtPirmary->setText(QApplication::translate("QAinDataMapDlg", "A /", 0, QApplication::UnicodeUTF8));
        m_stcCtSecondary->setText(QApplication::translate("QAinDataMapDlg", "A", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QAinDataMapDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QAinDataMapDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QAinDataMapDlg: public Ui_QAinDataMapDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QAINDATAMAPDLG_H
