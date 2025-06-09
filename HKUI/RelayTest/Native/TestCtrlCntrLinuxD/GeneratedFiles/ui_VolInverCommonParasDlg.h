/********************************************************************************
** Form generated from reading UI file 'VolInverCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLINVERCOMMONPARASDLG_H
#define UI_VOLINVERCOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_QVolInverseCommonParasDlg
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QComboBox *m_cmbCTPos;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *m_labHz;
    QLineEdit *m_txtFaultCurr;
    QLabel *m_labPreFaultTime;
    QLabel *m_labFaultVolt;
    QLineEdit *m_txtAng;
    QLineEdit *m_txtPreFaultTime;
    QLabel *label_5;
    QLabel *m_labAng;
    QLineEdit *m_txtFaultTime;
    QLineEdit *m_txtFaultVolt;
    QLabel *m_labFaultCurr;
    QLineEdit *m_txtHz;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnOK;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *QVolInverseCommonParasDlg)
    {
        if (QVolInverseCommonParasDlg->objectName().isEmpty())
            QVolInverseCommonParasDlg->setObjectName(QString::fromUtf8("QVolInverseCommonParasDlg"));
        QVolInverseCommonParasDlg->resize(341, 310);
        gridLayout_3 = new QGridLayout(QVolInverseCommonParasDlg);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_cmbCTPos = new QComboBox(QVolInverseCommonParasDlg);
        m_cmbCTPos->setObjectName(QString::fromUtf8("m_cmbCTPos"));

        gridLayout_2->addWidget(m_cmbCTPos, 1, 1, 1, 1);

        groupBox = new QGroupBox(QVolInverseCommonParasDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labHz = new QLabel(groupBox);
        m_labHz->setObjectName(QString::fromUtf8("m_labHz"));

        gridLayout->addWidget(m_labHz, 5, 0, 1, 1);

        m_txtFaultCurr = new QLineEdit(groupBox);
        m_txtFaultCurr->setObjectName(QString::fromUtf8("m_txtFaultCurr"));

        gridLayout->addWidget(m_txtFaultCurr, 3, 1, 1, 1);

        m_labPreFaultTime = new QLabel(groupBox);
        m_labPreFaultTime->setObjectName(QString::fromUtf8("m_labPreFaultTime"));

        gridLayout->addWidget(m_labPreFaultTime, 0, 0, 1, 1);

        m_labFaultVolt = new QLabel(groupBox);
        m_labFaultVolt->setObjectName(QString::fromUtf8("m_labFaultVolt"));

        gridLayout->addWidget(m_labFaultVolt, 2, 0, 1, 1);

        m_txtAng = new QLineEdit(groupBox);
        m_txtAng->setObjectName(QString::fromUtf8("m_txtAng"));

        gridLayout->addWidget(m_txtAng, 4, 1, 1, 1);

        m_txtPreFaultTime = new QLineEdit(groupBox);
        m_txtPreFaultTime->setObjectName(QString::fromUtf8("m_txtPreFaultTime"));

        gridLayout->addWidget(m_txtPreFaultTime, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_labAng = new QLabel(groupBox);
        m_labAng->setObjectName(QString::fromUtf8("m_labAng"));

        gridLayout->addWidget(m_labAng, 4, 0, 1, 1);

        m_txtFaultTime = new QLineEdit(groupBox);
        m_txtFaultTime->setObjectName(QString::fromUtf8("m_txtFaultTime"));

        gridLayout->addWidget(m_txtFaultTime, 1, 1, 1, 1);

        m_txtFaultVolt = new QLineEdit(groupBox);
        m_txtFaultVolt->setObjectName(QString::fromUtf8("m_txtFaultVolt"));

        gridLayout->addWidget(m_txtFaultVolt, 2, 1, 1, 1);

        m_labFaultCurr = new QLabel(groupBox);
        m_labFaultCurr->setObjectName(QString::fromUtf8("m_labFaultCurr"));

        gridLayout->addWidget(m_labFaultCurr, 3, 0, 1, 1);

        m_txtHz = new QLineEdit(groupBox);
        m_txtHz->setObjectName(QString::fromUtf8("m_txtHz"));

        gridLayout->addWidget(m_txtHz, 5, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 2);

        label_3 = new QLabel(QVolInverseCommonParasDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        m_btnOK = new QPushButton(QVolInverseCommonParasDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnCancel = new QPushButton(QVolInverseCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 2);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(QVolInverseCommonParasDlg);

        QMetaObject::connectSlotsByName(QVolInverseCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QVolInverseCommonParasDlg)
    {
        QVolInverseCommonParasDlg->setWindowTitle(QApplication::translate("QVolInverseCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QVolInverseCommonParasDlg", "\346\225\205\351\232\234\345\211\215\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        m_labHz->setText(QApplication::translate("QVolInverseCommonParasDlg", "\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labPreFaultTime->setText(QApplication::translate("QVolInverseCommonParasDlg", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultVolt->setText(QApplication::translate("QVolInverseCommonParasDlg", "\346\225\205\351\232\234\345\211\215\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QVolInverseCommonParasDlg", "\346\225\205\351\232\234\346\227\266\351\227\264\350\243\225\345\272\246(s)", 0, QApplication::UnicodeUTF8));
        m_labAng->setText(QApplication::translate("QVolInverseCommonParasDlg", "\347\233\270\344\275\215\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labFaultCurr->setText(QApplication::translate("QVolInverseCommonParasDlg", "\346\225\205\351\232\234\345\211\215\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QVolInverseCommonParasDlg", "CT\346\255\243\346\236\201\346\200\247", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QVolInverseCommonParasDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QVolInverseCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QVolInverseCommonParasDlg: public Ui_QVolInverseCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLINVERCOMMONPARASDLG_H
