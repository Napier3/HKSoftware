/********************************************************************************
** Form generated from reading UI file 'SynBinarysDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNBINARYSDLG_H
#define UI_SYNBINARYSDLG_H

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

QT_BEGIN_NAMESPACE

class Ui_QSynBinarysDlg
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *m_labKStart;
    QComboBox *m_cmbKStart;
    QLabel *m_labCloseTime;
    QLineEdit *m_lineCloseTime;
    QLabel *m_labBout1;
    QComboBox *m_cmbBout1;
    QLabel *m_labBout2;
    QComboBox *m_cmbBout2;
    QLabel *m_labBout3;
    QComboBox *m_cmbBout3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *m_labBinSyn;
    QComboBox *m_cmbBinSyn;
    QLabel *m_labBinIncV;
    QComboBox *m_cmbBinIncV;
    QLabel *m_labBinDecV;
    QComboBox *m_cmbBinDecV;
    QLabel *m_labBinIncF;
    QComboBox *m_cmbBinIncF;
    QLabel *m_labBinDecF;
    QComboBox *m_cmbBinDecF;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;

    void setupUi(QDialog *QSynBinarysDlg)
    {
        if (QSynBinarysDlg->objectName().isEmpty())
            QSynBinarysDlg->setObjectName(QString::fromUtf8("QSynBinarysDlg"));
        QSynBinarysDlg->resize(400, 439);
        gridLayout_3 = new QGridLayout(QSynBinarysDlg);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(QSynBinarysDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labKStart = new QLabel(groupBox);
        m_labKStart->setObjectName(QString::fromUtf8("m_labKStart"));

        gridLayout->addWidget(m_labKStart, 0, 0, 1, 1);

        m_cmbKStart = new QComboBox(groupBox);
        m_cmbKStart->setObjectName(QString::fromUtf8("m_cmbKStart"));

        gridLayout->addWidget(m_cmbKStart, 0, 1, 1, 1);

        m_labCloseTime = new QLabel(groupBox);
        m_labCloseTime->setObjectName(QString::fromUtf8("m_labCloseTime"));

        gridLayout->addWidget(m_labCloseTime, 1, 0, 1, 1);

        m_lineCloseTime = new QLineEdit(groupBox);
        m_lineCloseTime->setObjectName(QString::fromUtf8("m_lineCloseTime"));

        gridLayout->addWidget(m_lineCloseTime, 1, 1, 1, 1);

        m_labBout1 = new QLabel(groupBox);
        m_labBout1->setObjectName(QString::fromUtf8("m_labBout1"));

        gridLayout->addWidget(m_labBout1, 2, 0, 1, 1);

        m_cmbBout1 = new QComboBox(groupBox);
        m_cmbBout1->setObjectName(QString::fromUtf8("m_cmbBout1"));

        gridLayout->addWidget(m_cmbBout1, 2, 1, 1, 1);

        m_labBout2 = new QLabel(groupBox);
        m_labBout2->setObjectName(QString::fromUtf8("m_labBout2"));

        gridLayout->addWidget(m_labBout2, 3, 0, 1, 1);

        m_cmbBout2 = new QComboBox(groupBox);
        m_cmbBout2->setObjectName(QString::fromUtf8("m_cmbBout2"));

        gridLayout->addWidget(m_cmbBout2, 3, 1, 1, 1);

        m_labBout3 = new QLabel(groupBox);
        m_labBout3->setObjectName(QString::fromUtf8("m_labBout3"));

        gridLayout->addWidget(m_labBout3, 4, 0, 1, 1);

        m_cmbBout3 = new QComboBox(groupBox);
        m_cmbBout3->setObjectName(QString::fromUtf8("m_cmbBout3"));

        gridLayout->addWidget(m_cmbBout3, 4, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(QSynBinarysDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_labBinSyn = new QLabel(groupBox_2);
        m_labBinSyn->setObjectName(QString::fromUtf8("m_labBinSyn"));

        gridLayout_2->addWidget(m_labBinSyn, 0, 0, 1, 1);

        m_cmbBinSyn = new QComboBox(groupBox_2);
        m_cmbBinSyn->setObjectName(QString::fromUtf8("m_cmbBinSyn"));

        gridLayout_2->addWidget(m_cmbBinSyn, 0, 1, 1, 1);

        m_labBinIncV = new QLabel(groupBox_2);
        m_labBinIncV->setObjectName(QString::fromUtf8("m_labBinIncV"));

        gridLayout_2->addWidget(m_labBinIncV, 1, 0, 1, 1);

        m_cmbBinIncV = new QComboBox(groupBox_2);
        m_cmbBinIncV->setObjectName(QString::fromUtf8("m_cmbBinIncV"));

        gridLayout_2->addWidget(m_cmbBinIncV, 1, 1, 1, 1);

        m_labBinDecV = new QLabel(groupBox_2);
        m_labBinDecV->setObjectName(QString::fromUtf8("m_labBinDecV"));

        gridLayout_2->addWidget(m_labBinDecV, 2, 0, 1, 1);

        m_cmbBinDecV = new QComboBox(groupBox_2);
        m_cmbBinDecV->setObjectName(QString::fromUtf8("m_cmbBinDecV"));

        gridLayout_2->addWidget(m_cmbBinDecV, 2, 1, 1, 1);

        m_labBinIncF = new QLabel(groupBox_2);
        m_labBinIncF->setObjectName(QString::fromUtf8("m_labBinIncF"));

        gridLayout_2->addWidget(m_labBinIncF, 3, 0, 1, 1);

        m_cmbBinIncF = new QComboBox(groupBox_2);
        m_cmbBinIncF->setObjectName(QString::fromUtf8("m_cmbBinIncF"));

        gridLayout_2->addWidget(m_cmbBinIncF, 3, 1, 1, 1);

        m_labBinDecF = new QLabel(groupBox_2);
        m_labBinDecF->setObjectName(QString::fromUtf8("m_labBinDecF"));

        gridLayout_2->addWidget(m_labBinDecF, 4, 0, 1, 1);

        m_cmbBinDecF = new QComboBox(groupBox_2);
        m_cmbBinDecF->setObjectName(QString::fromUtf8("m_cmbBinDecF"));

        gridLayout_2->addWidget(m_cmbBinDecF, 4, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btnOK = new QPushButton(QSynBinarysDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));

        horizontalLayout->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QSynBinarysDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(QSynBinarysDlg);

        QMetaObject::connectSlotsByName(QSynBinarysDlg);
    } // setupUi

    void retranslateUi(QDialog *QSynBinarysDlg)
    {
        QSynBinarysDlg->setWindowTitle(QApplication::translate("QSynBinarysDlg", "\345\274\200\345\205\263\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QSynBinarysDlg", "\345\274\200\345\207\272\351\207\217", 0, QApplication::UnicodeUTF8));
        m_labKStart->setText(QApplication::translate("QSynBinarysDlg", "\345\274\200\345\207\2724\350\276\223\345\207\272\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        m_labCloseTime->setText(QApplication::translate("QSynBinarysDlg", "\345\274\200\345\207\2724\344\277\235\346\214\201\346\227\266\351\227\264(s)", 0, QApplication::UnicodeUTF8));
        m_labBout1->setText(QApplication::translate("QSynBinarysDlg", "\345\274\200\345\207\2721\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        m_labBout2->setText(QApplication::translate("QSynBinarysDlg", "\345\274\200\345\207\2722\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        m_labBout3->setText(QApplication::translate("QSynBinarysDlg", "\345\274\200\345\207\2723\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QSynBinarysDlg", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_labBinSyn->setText(QApplication::translate("QSynBinarysDlg", "\344\277\235\346\212\244\345\207\272\345\217\243\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        m_labBinIncV->setText(QApplication::translate("QSynBinarysDlg", "\345\242\236\345\216\213\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        m_labBinDecV->setText(QApplication::translate("QSynBinarysDlg", "\345\207\217\345\216\213\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        m_labBinIncF->setText(QApplication::translate("QSynBinarysDlg", "\345\242\236\351\200\237\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        m_labBinDecF->setText(QApplication::translate("QSynBinarysDlg", "\345\207\217\351\200\237\344\277\241\345\217\267", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QSynBinarysDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QSynBinarysDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSynBinarysDlg: public Ui_QSynBinarysDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNBINARYSDLG_H
