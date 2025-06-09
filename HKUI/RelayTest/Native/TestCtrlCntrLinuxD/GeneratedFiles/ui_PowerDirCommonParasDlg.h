/********************************************************************************
** Form generated from reading UI file 'PowerDirCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POWERDIRCOMMONPARASDLG_H
#define UI_POWERDIRCOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QPowerDirCommonParasDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *m_editPrepareTime;
    QLineEdit *m_editPreAngle;
    QLineEdit *m_editIPre;
    QLabel *m_labPrepareTime;
    QLineEdit *m_editAngleMargin;
    QLabel *m_labAngleMode;
    QLineEdit *m_editPreFaultTime;
    QLineEdit *m_editUPre;
    QLabel *m_labConnectMode;
    QLabel *m_labAngleMargin;
    QLabel *m_labIPre;
    CExBaseListComboBox *m_cbbConnectMode;
    QLabel *m_labPreFaultTime;
    QLabel *m_labUPhSet;
    QLabel *m_labIPhSet;
    QLabel *m_labPreAngle;
    QLabel *m_labUPre;
    CExBaseListComboBox *m_cbbUPhSet;
    CExBaseListComboBox *m_cbbIPhSet;
    CExBaseListComboBox *m_cbbAngleMode;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QDialog *QPowerDirCommonParasDlg)
    {
        if (QPowerDirCommonParasDlg->objectName().isEmpty())
            QPowerDirCommonParasDlg->setObjectName(QString::fromUtf8("QPowerDirCommonParasDlg"));
        QPowerDirCommonParasDlg->resize(321, 363);
        horizontalLayout = new QHBoxLayout(QPowerDirCommonParasDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(10, -1, 10, -1);
        m_editPrepareTime = new QLineEdit(QPowerDirCommonParasDlg);
        m_editPrepareTime->setObjectName(QString::fromUtf8("m_editPrepareTime"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_editPrepareTime->sizePolicy().hasHeightForWidth());
        m_editPrepareTime->setSizePolicy(sizePolicy);
        m_editPrepareTime->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_editPrepareTime, 0, 3, 1, 1);

        m_editPreAngle = new QLineEdit(QPowerDirCommonParasDlg);
        m_editPreAngle->setObjectName(QString::fromUtf8("m_editPreAngle"));
        sizePolicy.setHeightForWidth(m_editPreAngle->sizePolicy().hasHeightForWidth());
        m_editPreAngle->setSizePolicy(sizePolicy);
        m_editPreAngle->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_editPreAngle, 6, 3, 1, 1);

        m_editIPre = new QLineEdit(QPowerDirCommonParasDlg);
        m_editIPre->setObjectName(QString::fromUtf8("m_editIPre"));
        sizePolicy.setHeightForWidth(m_editIPre->sizePolicy().hasHeightForWidth());
        m_editIPre->setSizePolicy(sizePolicy);
        m_editIPre->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_editIPre, 4, 3, 1, 1);

        m_labPrepareTime = new QLabel(QPowerDirCommonParasDlg);
        m_labPrepareTime->setObjectName(QString::fromUtf8("m_labPrepareTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_labPrepareTime->sizePolicy().hasHeightForWidth());
        m_labPrepareTime->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labPrepareTime, 0, 1, 1, 1);

        m_editAngleMargin = new QLineEdit(QPowerDirCommonParasDlg);
        m_editAngleMargin->setObjectName(QString::fromUtf8("m_editAngleMargin"));
        sizePolicy.setHeightForWidth(m_editAngleMargin->sizePolicy().hasHeightForWidth());
        m_editAngleMargin->setSizePolicy(sizePolicy);
        m_editAngleMargin->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_editAngleMargin, 9, 3, 1, 1);

        m_labAngleMode = new QLabel(QPowerDirCommonParasDlg);
        m_labAngleMode->setObjectName(QString::fromUtf8("m_labAngleMode"));
        sizePolicy1.setHeightForWidth(m_labAngleMode->sizePolicy().hasHeightForWidth());
        m_labAngleMode->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labAngleMode, 7, 1, 1, 1);

        m_editPreFaultTime = new QLineEdit(QPowerDirCommonParasDlg);
        m_editPreFaultTime->setObjectName(QString::fromUtf8("m_editPreFaultTime"));
        sizePolicy.setHeightForWidth(m_editPreFaultTime->sizePolicy().hasHeightForWidth());
        m_editPreFaultTime->setSizePolicy(sizePolicy);
        m_editPreFaultTime->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_editPreFaultTime, 1, 3, 1, 1);

        m_editUPre = new QLineEdit(QPowerDirCommonParasDlg);
        m_editUPre->setObjectName(QString::fromUtf8("m_editUPre"));
        sizePolicy.setHeightForWidth(m_editUPre->sizePolicy().hasHeightForWidth());
        m_editUPre->setSizePolicy(sizePolicy);
        m_editUPre->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_editUPre, 2, 3, 1, 1);

        m_labConnectMode = new QLabel(QPowerDirCommonParasDlg);
        m_labConnectMode->setObjectName(QString::fromUtf8("m_labConnectMode"));
        sizePolicy1.setHeightForWidth(m_labConnectMode->sizePolicy().hasHeightForWidth());
        m_labConnectMode->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labConnectMode, 8, 1, 1, 1);

        m_labAngleMargin = new QLabel(QPowerDirCommonParasDlg);
        m_labAngleMargin->setObjectName(QString::fromUtf8("m_labAngleMargin"));
        sizePolicy1.setHeightForWidth(m_labAngleMargin->sizePolicy().hasHeightForWidth());
        m_labAngleMargin->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labAngleMargin, 9, 1, 1, 1);

        m_labIPre = new QLabel(QPowerDirCommonParasDlg);
        m_labIPre->setObjectName(QString::fromUtf8("m_labIPre"));
        sizePolicy1.setHeightForWidth(m_labIPre->sizePolicy().hasHeightForWidth());
        m_labIPre->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labIPre, 4, 1, 1, 1);

        m_cbbConnectMode = new CExBaseListComboBox(QPowerDirCommonParasDlg);
        m_cbbConnectMode->setObjectName(QString::fromUtf8("m_cbbConnectMode"));
        sizePolicy.setHeightForWidth(m_cbbConnectMode->sizePolicy().hasHeightForWidth());
        m_cbbConnectMode->setSizePolicy(sizePolicy);
        m_cbbConnectMode->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbConnectMode, 8, 3, 1, 1);

        m_labPreFaultTime = new QLabel(QPowerDirCommonParasDlg);
        m_labPreFaultTime->setObjectName(QString::fromUtf8("m_labPreFaultTime"));
        sizePolicy1.setHeightForWidth(m_labPreFaultTime->sizePolicy().hasHeightForWidth());
        m_labPreFaultTime->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labPreFaultTime, 1, 1, 1, 1);

        m_labUPhSet = new QLabel(QPowerDirCommonParasDlg);
        m_labUPhSet->setObjectName(QString::fromUtf8("m_labUPhSet"));
        sizePolicy1.setHeightForWidth(m_labUPhSet->sizePolicy().hasHeightForWidth());
        m_labUPhSet->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labUPhSet, 3, 1, 1, 1);

        m_labIPhSet = new QLabel(QPowerDirCommonParasDlg);
        m_labIPhSet->setObjectName(QString::fromUtf8("m_labIPhSet"));
        sizePolicy1.setHeightForWidth(m_labIPhSet->sizePolicy().hasHeightForWidth());
        m_labIPhSet->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labIPhSet, 5, 1, 1, 1);

        m_labPreAngle = new QLabel(QPowerDirCommonParasDlg);
        m_labPreAngle->setObjectName(QString::fromUtf8("m_labPreAngle"));
        sizePolicy1.setHeightForWidth(m_labPreAngle->sizePolicy().hasHeightForWidth());
        m_labPreAngle->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labPreAngle, 6, 1, 1, 1);

        m_labUPre = new QLabel(QPowerDirCommonParasDlg);
        m_labUPre->setObjectName(QString::fromUtf8("m_labUPre"));
        sizePolicy1.setHeightForWidth(m_labUPre->sizePolicy().hasHeightForWidth());
        m_labUPre->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labUPre, 2, 1, 1, 1);

        m_cbbUPhSet = new CExBaseListComboBox(QPowerDirCommonParasDlg);
        m_cbbUPhSet->setObjectName(QString::fromUtf8("m_cbbUPhSet"));
        sizePolicy.setHeightForWidth(m_cbbUPhSet->sizePolicy().hasHeightForWidth());
        m_cbbUPhSet->setSizePolicy(sizePolicy);
        m_cbbUPhSet->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbUPhSet, 3, 3, 1, 1);

        m_cbbIPhSet = new CExBaseListComboBox(QPowerDirCommonParasDlg);
        m_cbbIPhSet->setObjectName(QString::fromUtf8("m_cbbIPhSet"));
        sizePolicy.setHeightForWidth(m_cbbIPhSet->sizePolicy().hasHeightForWidth());
        m_cbbIPhSet->setSizePolicy(sizePolicy);
        m_cbbIPhSet->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbIPhSet, 5, 3, 1, 1);

        m_cbbAngleMode = new CExBaseListComboBox(QPowerDirCommonParasDlg);
        m_cbbAngleMode->setObjectName(QString::fromUtf8("m_cbbAngleMode"));
        sizePolicy.setHeightForWidth(m_cbbAngleMode->sizePolicy().hasHeightForWidth());
        m_cbbAngleMode->setSizePolicy(sizePolicy);
        m_cbbAngleMode->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_cbbAngleMode, 7, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        m_btnOk = new QPushButton(QPowerDirCommonParasDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        sizePolicy.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(m_btnOk);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        m_btnCancel = new QPushButton(QPowerDirCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(m_btnCancel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QPowerDirCommonParasDlg);

        QMetaObject::connectSlotsByName(QPowerDirCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QPowerDirCommonParasDlg)
    {
        QPowerDirCommonParasDlg->setWindowTitle(QApplication::translate("QPowerDirCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labPrepareTime->setText(QApplication::translate("QPowerDirCommonParasDlg", "\345\217\230\345\214\226\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labAngleMode->setText(QApplication::translate("QPowerDirCommonParasDlg", "\350\247\222\345\272\246\345\256\232\344\271\211:", 0, QApplication::UnicodeUTF8));
        m_labConnectMode->setText(QApplication::translate("QPowerDirCommonParasDlg", "\346\216\245\347\272\277\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labAngleMargin->setText(QApplication::translate("QPowerDirCommonParasDlg", "\350\247\222\345\272\246\350\243\225\345\272\246(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labIPre->setText(QApplication::translate("QPowerDirCommonParasDlg", "\345\270\270\346\200\201\347\224\265\346\265\201\345\271\205\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labPreFaultTime->setText(QApplication::translate("QPowerDirCommonParasDlg", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labUPhSet->setText(QApplication::translate("QPowerDirCommonParasDlg", "\345\270\270\346\200\201\347\224\265\345\216\213\347\233\270\345\272\217:", 0, QApplication::UnicodeUTF8));
        m_labIPhSet->setText(QApplication::translate("QPowerDirCommonParasDlg", "\345\270\270\346\200\201\347\224\265\346\265\201\347\233\270\345\272\217:", 0, QApplication::UnicodeUTF8));
        m_labPreAngle->setText(QApplication::translate("QPowerDirCommonParasDlg", "\345\270\270\346\200\201\347\233\270\350\247\222(U-I):", 0, QApplication::UnicodeUTF8));
        m_labUPre->setText(QApplication::translate("QPowerDirCommonParasDlg", "\345\270\270\346\200\201\347\224\265\345\216\213\345\271\205\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QPowerDirCommonParasDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QPowerDirCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QPowerDirCommonParasDlg: public Ui_QPowerDirCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POWERDIRCOMMONPARASDLG_H
