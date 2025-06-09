/********************************************************************************
** Form generated from reading UI file 'DiffAddSearchLineDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFADDSEARCHLINEDLG_H
#define UI_DIFFADDSEARCHLINEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
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
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QDiffAddSearchLineDlg
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *m_lbActAbsErr;
    QLabel *m_lbErrorLogic;
    QLineEdit *m_editActAbsErr;
    QComboBox *m_cmbErrorLogic;
    QLabel *m_lbActRelErr;
    QLineEdit *m_editActRelErr;
    QLabel *m_labTips;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *m_check_AB;
    QCheckBox *m_check_BC;
    QCheckBox *m_check_CA;
    QCheckBox *m_check_ABC;
    QCheckBox *m_check_AN;
    QCheckBox *m_check_BN;
    QCheckBox *m_check_CN;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *m_btnSave;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *m_btnClose;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labSL_BeginVal;
    QLineEdit *m_txtSL_BeginVal;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labSL_EndVal;
    QLineEdit *m_txtSL_EndVal;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labSL_Step;
    QLineEdit *m_txtSL_Step;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labSL_Time;
    QLineEdit *m_txtSL_Time;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labSL_Points;
    QLineEdit *m_txtSL_Points;

    void setupUi(QDialog *QDiffAddSearchLineDlg)
    {
        if (QDiffAddSearchLineDlg->objectName().isEmpty())
            QDiffAddSearchLineDlg->setObjectName(QString::fromUtf8("QDiffAddSearchLineDlg"));
        QDiffAddSearchLineDlg->resize(592, 499);
        QFont font;
        font.setPointSize(9);
        QDiffAddSearchLineDlg->setFont(font);
        gridLayout_2 = new QGridLayout(QDiffAddSearchLineDlg);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_2 = new QGroupBox(QDiffAddSearchLineDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_lbActAbsErr = new QLabel(groupBox_2);
        m_lbActAbsErr->setObjectName(QString::fromUtf8("m_lbActAbsErr"));
        m_lbActAbsErr->setMinimumSize(QSize(0, 0));
        m_lbActAbsErr->setMaximumSize(QSize(130, 20));
        m_lbActAbsErr->setFont(font);

        gridLayout_3->addWidget(m_lbActAbsErr, 1, 0, 1, 1);

        m_lbErrorLogic = new QLabel(groupBox_2);
        m_lbErrorLogic->setObjectName(QString::fromUtf8("m_lbErrorLogic"));
        m_lbErrorLogic->setMinimumSize(QSize(0, 0));
        m_lbErrorLogic->setMaximumSize(QSize(130, 20));
        m_lbErrorLogic->setFont(font);

        gridLayout_3->addWidget(m_lbErrorLogic, 0, 0, 1, 1);

        m_editActAbsErr = new QLineEdit(groupBox_2);
        m_editActAbsErr->setObjectName(QString::fromUtf8("m_editActAbsErr"));
        m_editActAbsErr->setMinimumSize(QSize(0, 0));
        m_editActAbsErr->setMaximumSize(QSize(130, 20));
        m_editActAbsErr->setFont(font);

        gridLayout_3->addWidget(m_editActAbsErr, 1, 1, 1, 1);

        m_cmbErrorLogic = new QComboBox(groupBox_2);
        m_cmbErrorLogic->setObjectName(QString::fromUtf8("m_cmbErrorLogic"));

        gridLayout_3->addWidget(m_cmbErrorLogic, 0, 1, 1, 1);

        m_lbActRelErr = new QLabel(groupBox_2);
        m_lbActRelErr->setObjectName(QString::fromUtf8("m_lbActRelErr"));
        m_lbActRelErr->setMinimumSize(QSize(0, 0));
        m_lbActRelErr->setMaximumSize(QSize(130, 20));
        m_lbActRelErr->setFont(font);

        gridLayout_3->addWidget(m_lbActRelErr, 1, 2, 1, 1);

        m_editActRelErr = new QLineEdit(groupBox_2);
        m_editActRelErr->setObjectName(QString::fromUtf8("m_editActRelErr"));
        m_editActRelErr->setMinimumSize(QSize(0, 0));
        m_editActRelErr->setMaximumSize(QSize(130, 20));
        m_editActRelErr->setFont(font);

        gridLayout_3->addWidget(m_editActRelErr, 1, 3, 1, 1);

        gridLayout_3->setRowStretch(0, 1);

        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 4);

        m_labTips = new QLabel(QDiffAddSearchLineDlg);
        m_labTips->setObjectName(QString::fromUtf8("m_labTips"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labTips->sizePolicy().hasHeightForWidth());
        m_labTips->setSizePolicy(sizePolicy);
        m_labTips->setMinimumSize(QSize(0, 0));
        m_labTips->setFont(font);
        m_labTips->setStyleSheet(QString::fromUtf8("QLabel{border:2px groove rgb(0,0,255);border-radius:10px;background-color: rgb(255,242,204)}"));
        m_labTips->setWordWrap(true);

        gridLayout_2->addWidget(m_labTips, 2, 3, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(QDiffAddSearchLineDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(20, -1, 9, -1);
        m_check_AB = new QCheckBox(groupBox);
        m_check_AB->setObjectName(QString::fromUtf8("m_check_AB"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_check_AB->sizePolicy().hasHeightForWidth());
        m_check_AB->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_check_AB, 1, 1, 1, 1);

        m_check_BC = new QCheckBox(groupBox);
        m_check_BC->setObjectName(QString::fromUtf8("m_check_BC"));
        sizePolicy1.setHeightForWidth(m_check_BC->sizePolicy().hasHeightForWidth());
        m_check_BC->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_check_BC, 1, 2, 1, 1);

        m_check_CA = new QCheckBox(groupBox);
        m_check_CA->setObjectName(QString::fromUtf8("m_check_CA"));
        sizePolicy1.setHeightForWidth(m_check_CA->sizePolicy().hasHeightForWidth());
        m_check_CA->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_check_CA, 1, 3, 1, 1);

        m_check_ABC = new QCheckBox(groupBox);
        m_check_ABC->setObjectName(QString::fromUtf8("m_check_ABC"));
        sizePolicy1.setHeightForWidth(m_check_ABC->sizePolicy().hasHeightForWidth());
        m_check_ABC->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_check_ABC, 2, 1, 1, 1);

        m_check_AN = new QCheckBox(groupBox);
        m_check_AN->setObjectName(QString::fromUtf8("m_check_AN"));
        sizePolicy1.setHeightForWidth(m_check_AN->sizePolicy().hasHeightForWidth());
        m_check_AN->setSizePolicy(sizePolicy1);
        m_check_AN->setChecked(true);
        m_check_AN->setTristate(false);

        gridLayout->addWidget(m_check_AN, 0, 1, 1, 1);

        m_check_BN = new QCheckBox(groupBox);
        m_check_BN->setObjectName(QString::fromUtf8("m_check_BN"));
        sizePolicy1.setHeightForWidth(m_check_BN->sizePolicy().hasHeightForWidth());
        m_check_BN->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_check_BN, 0, 2, 1, 1);

        m_check_CN = new QCheckBox(groupBox);
        m_check_CN->setObjectName(QString::fromUtf8("m_check_CN"));
        sizePolicy1.setHeightForWidth(m_check_CN->sizePolicy().hasHeightForWidth());
        m_check_CN->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_check_CN, 0, 3, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        verticalLayout_2->setStretch(0, 3);

        gridLayout_2->addLayout(verticalLayout_2, 0, 2, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(191, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_btnSave = new QPushButton(QDiffAddSearchLineDlg);
        m_btnSave->setObjectName(QString::fromUtf8("m_btnSave"));

        horizontalLayout_7->addWidget(m_btnSave);

        horizontalSpacer_4 = new QSpacerItem(113, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        m_btnClose = new QPushButton(QDiffAddSearchLineDlg);
        m_btnClose->setObjectName(QString::fromUtf8("m_btnClose"));

        horizontalLayout_7->addWidget(m_btnClose);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(2, 1);

        gridLayout_2->addLayout(horizontalLayout_7, 2, 1, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 6, -1);
        m_labSL_BeginVal = new QLabel(QDiffAddSearchLineDlg);
        m_labSL_BeginVal->setObjectName(QString::fromUtf8("m_labSL_BeginVal"));
        m_labSL_BeginVal->setMinimumSize(QSize(170, 0));
        m_labSL_BeginVal->setMaximumSize(QSize(170, 16777215));
        m_labSL_BeginVal->setFont(font);
        m_labSL_BeginVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_labSL_BeginVal);

        m_txtSL_BeginVal = new QLineEdit(QDiffAddSearchLineDlg);
        m_txtSL_BeginVal->setObjectName(QString::fromUtf8("m_txtSL_BeginVal"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_txtSL_BeginVal->sizePolicy().hasHeightForWidth());
        m_txtSL_BeginVal->setSizePolicy(sizePolicy2);
        m_txtSL_BeginVal->setMinimumSize(QSize(100, 0));
        m_txtSL_BeginVal->setMaximumSize(QSize(16777215, 16777215));
        m_txtSL_BeginVal->setFont(font);

        horizontalLayout_2->addWidget(m_txtSL_BeginVal);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, 6, -1);
        m_labSL_EndVal = new QLabel(QDiffAddSearchLineDlg);
        m_labSL_EndVal->setObjectName(QString::fromUtf8("m_labSL_EndVal"));
        m_labSL_EndVal->setMinimumSize(QSize(170, 0));
        m_labSL_EndVal->setMaximumSize(QSize(170, 16777215));
        m_labSL_EndVal->setFont(font);
        m_labSL_EndVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_labSL_EndVal);

        m_txtSL_EndVal = new QLineEdit(QDiffAddSearchLineDlg);
        m_txtSL_EndVal->setObjectName(QString::fromUtf8("m_txtSL_EndVal"));
        sizePolicy2.setHeightForWidth(m_txtSL_EndVal->sizePolicy().hasHeightForWidth());
        m_txtSL_EndVal->setSizePolicy(sizePolicy2);
        m_txtSL_EndVal->setMinimumSize(QSize(100, 0));
        m_txtSL_EndVal->setMaximumSize(QSize(16777215, 16777215));
        m_txtSL_EndVal->setFont(font);

        horizontalLayout_3->addWidget(m_txtSL_EndVal);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 6, -1);
        m_labSL_Step = new QLabel(QDiffAddSearchLineDlg);
        m_labSL_Step->setObjectName(QString::fromUtf8("m_labSL_Step"));
        m_labSL_Step->setMinimumSize(QSize(170, 0));
        m_labSL_Step->setMaximumSize(QSize(170, 16777215));
        m_labSL_Step->setFont(font);
        m_labSL_Step->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(m_labSL_Step);

        m_txtSL_Step = new QLineEdit(QDiffAddSearchLineDlg);
        m_txtSL_Step->setObjectName(QString::fromUtf8("m_txtSL_Step"));
        sizePolicy2.setHeightForWidth(m_txtSL_Step->sizePolicy().hasHeightForWidth());
        m_txtSL_Step->setSizePolicy(sizePolicy2);
        m_txtSL_Step->setMinimumSize(QSize(100, 0));
        m_txtSL_Step->setMaximumSize(QSize(16777215, 16777215));
        m_txtSL_Step->setFont(font);

        horizontalLayout_4->addWidget(m_txtSL_Step);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, 6, -1);
        m_labSL_Time = new QLabel(QDiffAddSearchLineDlg);
        m_labSL_Time->setObjectName(QString::fromUtf8("m_labSL_Time"));
        m_labSL_Time->setMinimumSize(QSize(170, 0));
        m_labSL_Time->setMaximumSize(QSize(170, 16777215));
        m_labSL_Time->setFont(font);
        m_labSL_Time->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(m_labSL_Time);

        m_txtSL_Time = new QLineEdit(QDiffAddSearchLineDlg);
        m_txtSL_Time->setObjectName(QString::fromUtf8("m_txtSL_Time"));
        sizePolicy2.setHeightForWidth(m_txtSL_Time->sizePolicy().hasHeightForWidth());
        m_txtSL_Time->setSizePolicy(sizePolicy2);
        m_txtSL_Time->setMinimumSize(QSize(100, 0));
        m_txtSL_Time->setMaximumSize(QSize(16777215, 16777215));
        m_txtSL_Time->setFont(font);

        horizontalLayout_5->addWidget(m_txtSL_Time);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, -1, 6, -1);
        m_labSL_Points = new QLabel(QDiffAddSearchLineDlg);
        m_labSL_Points->setObjectName(QString::fromUtf8("m_labSL_Points"));
        m_labSL_Points->setMinimumSize(QSize(170, 0));
        m_labSL_Points->setMaximumSize(QSize(170, 16777215));
        m_labSL_Points->setFont(font);
        m_labSL_Points->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(m_labSL_Points);

        m_txtSL_Points = new QLineEdit(QDiffAddSearchLineDlg);
        m_txtSL_Points->setObjectName(QString::fromUtf8("m_txtSL_Points"));
        m_txtSL_Points->setEnabled(false);
        sizePolicy2.setHeightForWidth(m_txtSL_Points->sizePolicy().hasHeightForWidth());
        m_txtSL_Points->setSizePolicy(sizePolicy2);
        m_txtSL_Points->setMinimumSize(QSize(100, 0));
        m_txtSL_Points->setMaximumSize(QSize(16777215, 16777215));
        m_txtSL_Points->setFont(font);

        horizontalLayout_6->addWidget(m_txtSL_Points);


        verticalLayout->addLayout(horizontalLayout_6);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 2);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 1);
        gridLayout_2->setColumnStretch(2, 1);
        gridLayout_2->setColumnStretch(3, 1);
        m_labTips->raise();
        groupBox_2->raise();

        retranslateUi(QDiffAddSearchLineDlg);

        QMetaObject::connectSlotsByName(QDiffAddSearchLineDlg);
    } // setupUi

    void retranslateUi(QDialog *QDiffAddSearchLineDlg)
    {
        QDiffAddSearchLineDlg->setWindowTitle(QApplication::translate("QDiffAddSearchLineDlg", "\346\267\273\345\212\240\346\220\234\347\264\242\347\272\277", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("QDiffAddSearchLineDlg", "\347\273\223\346\236\234\345\210\244\346\226\255", 0, QApplication::UnicodeUTF8));
        m_lbActAbsErr->setText(QApplication::translate("QDiffAddSearchLineDlg", "\345\212\250\344\275\234\345\200\274\347\273\235\345\257\271\350\257\257\345\267\256():", 0, QApplication::UnicodeUTF8));
        m_lbErrorLogic->setText(QApplication::translate("QDiffAddSearchLineDlg", "\350\257\257\345\267\256\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_editActAbsErr->setText(QApplication::translate("QDiffAddSearchLineDlg", "2.000", 0, QApplication::UnicodeUTF8));
        m_lbActRelErr->setText(QApplication::translate("QDiffAddSearchLineDlg", "\345\212\250\344\275\234\345\200\274\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
        m_editActRelErr->setText(QApplication::translate("QDiffAddSearchLineDlg", "0.020", 0, QApplication::UnicodeUTF8));
        m_labTips->setText(QString());
        groupBox->setTitle(QApplication::translate("QDiffAddSearchLineDlg", "\346\225\205\351\232\234\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        m_check_AB->setText(QApplication::translate("QDiffAddSearchLineDlg", "AB", 0, QApplication::UnicodeUTF8));
        m_check_BC->setText(QApplication::translate("QDiffAddSearchLineDlg", "BC", 0, QApplication::UnicodeUTF8));
        m_check_CA->setText(QApplication::translate("QDiffAddSearchLineDlg", "CA", 0, QApplication::UnicodeUTF8));
        m_check_ABC->setText(QApplication::translate("QDiffAddSearchLineDlg", "ABC", 0, QApplication::UnicodeUTF8));
        m_check_AN->setText(QApplication::translate("QDiffAddSearchLineDlg", "AN", 0, QApplication::UnicodeUTF8));
        m_check_BN->setText(QApplication::translate("QDiffAddSearchLineDlg", "BN", 0, QApplication::UnicodeUTF8));
        m_check_CN->setText(QApplication::translate("QDiffAddSearchLineDlg", "CN", 0, QApplication::UnicodeUTF8));
        m_btnSave->setText(QApplication::translate("QDiffAddSearchLineDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnClose->setText(QApplication::translate("QDiffAddSearchLineDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        m_labSL_BeginVal->setText(QApplication::translate("QDiffAddSearchLineDlg", "\345\210\266\345\212\250\347\224\265\346\265\201\345\247\213\345\200\274():", 0, QApplication::UnicodeUTF8));
        m_txtSL_BeginVal->setText(QApplication::translate("QDiffAddSearchLineDlg", "0.100", 0, QApplication::UnicodeUTF8));
        m_labSL_EndVal->setText(QApplication::translate("QDiffAddSearchLineDlg", "\345\210\266\345\212\250\347\224\265\346\265\201\347\273\210\345\200\274():", 0, QApplication::UnicodeUTF8));
        m_txtSL_EndVal->setText(QApplication::translate("QDiffAddSearchLineDlg", "5.000", 0, QApplication::UnicodeUTF8));
        m_labSL_Step->setText(QApplication::translate("QDiffAddSearchLineDlg", "\345\217\230\345\214\226\346\255\245\351\225\277():", 0, QApplication::UnicodeUTF8));
        m_txtSL_Step->setText(QApplication::translate("QDiffAddSearchLineDlg", "0.100", 0, QApplication::UnicodeUTF8));
        m_labSL_Time->setText(QApplication::translate("QDiffAddSearchLineDlg", "\346\234\200\345\244\247\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_txtSL_Time->setText(QApplication::translate("QDiffAddSearchLineDlg", "0.200", 0, QApplication::UnicodeUTF8));
        m_labSL_Points->setText(QApplication::translate("QDiffAddSearchLineDlg", "\346\265\213\350\257\225\347\202\271\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_txtSL_Points->setText(QApplication::translate("QDiffAddSearchLineDlg", "50", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDiffAddSearchLineDlg: public Ui_QDiffAddSearchLineDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFADDSEARCHLINEDLG_H
