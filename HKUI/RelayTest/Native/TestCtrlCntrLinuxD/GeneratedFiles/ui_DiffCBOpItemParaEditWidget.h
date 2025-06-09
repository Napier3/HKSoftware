/********************************************************************************
** Form generated from reading UI file 'DiffCBOpItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFCBOPITEMPARAEDITWIDGET_H
#define UI_DIFFCBOPITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"

QT_BEGIN_NAMESPACE

class Ui_QDiffCBOpItemParaEditWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *m_pLabCurrent;
    QLabel *m_pLabFrep;
    QLineEdit *m_pEditFrep;
    QComboBox *m_pCmbFaultLocation;
    QLabel *m_pLabFaultLocation;
    QLabel *m_pLabFaultType;
    QComboBox *m_pCmbFaultType;
    QLineEdit *m_pEditCurent;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *m_pGroupSystemParas;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *m_pLabTransfHvKph;
    QLabel *m_pLabTransfHvKpl;
    QLabel *m_pLabBalCoeff;
    QSettingLineEdit *m_pEditTransfHvKph;
    QSettingLineEdit *m_pEditTransfMvKpm;
    QSettingLineEdit *m_pEditTransfLvKpl;
    QLabel *m_pLabVnom;
    QSettingLineEdit *m_pEditTransfHvVol;
    QSettingLineEdit *m_pEditTransfMvVol;
    QSettingLineEdit *m_pEditTransfLvVol;
    QLabel *m_pLabEDCurrent;
    QSettingLineEdit *m_pEditTransfHvCur;
    QSettingLineEdit *m_pEditTransfMvCur;
    QSettingLineEdit *m_pEditTransfLvCur;
    QLabel *m_pLabCT;
    QSettingLineEdit *m_pEditTransfHvCT;
    QSettingLineEdit *m_pEditTransfMvCT;
    QSettingLineEdit *m_pEditTransfLvCT;
    QLabel *m_pLabTransfRatedCapacity;
    QSettingLineEdit *m_pEditTransfHvKVA;
    QCheckBox *m_pChkKph;
    QLabel *m_pLabTransfHvKpm;
    QGridLayout *gridLayout_3;
    QLabel *m_pLabAbsErr;
    QLabel *m_pLabAbsErrMinus;
    QSettingLineEdit *m_pEditRelErr;
    QSettingLineEdit *m_pEditAbsErrReduce;
    QLabel *m_pLabRelErr;
    QSettingLineEdit *m_pEditAbsErrSum;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *QDiffCBOpItemParaEditWidget)
    {
        if (QDiffCBOpItemParaEditWidget->objectName().isEmpty())
            QDiffCBOpItemParaEditWidget->setObjectName(QString::fromUtf8("QDiffCBOpItemParaEditWidget"));
        QDiffCBOpItemParaEditWidget->resize(753, 400);
        QDiffCBOpItemParaEditWidget->setMaximumSize(QSize(16777215, 400));
        verticalLayout_3 = new QVBoxLayout(QDiffCBOpItemParaEditWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(15, -1, 15, -1);
        m_pLabCurrent = new QLabel(QDiffCBOpItemParaEditWidget);
        m_pLabCurrent->setObjectName(QString::fromUtf8("m_pLabCurrent"));
        QFont font;
        font.setPointSize(9);
        m_pLabCurrent->setFont(font);

        gridLayout_2->addWidget(m_pLabCurrent, 1, 0, 1, 1);

        m_pLabFrep = new QLabel(QDiffCBOpItemParaEditWidget);
        m_pLabFrep->setObjectName(QString::fromUtf8("m_pLabFrep"));
        m_pLabFrep->setFont(font);

        gridLayout_2->addWidget(m_pLabFrep, 1, 4, 1, 1);

        m_pEditFrep = new QLineEdit(QDiffCBOpItemParaEditWidget);
        m_pEditFrep->setObjectName(QString::fromUtf8("m_pEditFrep"));
        m_pEditFrep->setFont(font);

        gridLayout_2->addWidget(m_pEditFrep, 1, 5, 1, 1);

        m_pCmbFaultLocation = new QComboBox(QDiffCBOpItemParaEditWidget);
        m_pCmbFaultLocation->setObjectName(QString::fromUtf8("m_pCmbFaultLocation"));
        m_pCmbFaultLocation->setFont(font);

        gridLayout_2->addWidget(m_pCmbFaultLocation, 0, 5, 1, 1);

        m_pLabFaultLocation = new QLabel(QDiffCBOpItemParaEditWidget);
        m_pLabFaultLocation->setObjectName(QString::fromUtf8("m_pLabFaultLocation"));
        m_pLabFaultLocation->setFont(font);

        gridLayout_2->addWidget(m_pLabFaultLocation, 0, 4, 1, 1);

        m_pLabFaultType = new QLabel(QDiffCBOpItemParaEditWidget);
        m_pLabFaultType->setObjectName(QString::fromUtf8("m_pLabFaultType"));
        m_pLabFaultType->setFont(font);

        gridLayout_2->addWidget(m_pLabFaultType, 0, 0, 1, 1);

        m_pCmbFaultType = new QComboBox(QDiffCBOpItemParaEditWidget);
        m_pCmbFaultType->setObjectName(QString::fromUtf8("m_pCmbFaultType"));
        m_pCmbFaultType->setFont(font);

        gridLayout_2->addWidget(m_pCmbFaultType, 0, 1, 1, 1);

        m_pEditCurent = new QLineEdit(QDiffCBOpItemParaEditWidget);
        m_pEditCurent->setObjectName(QString::fromUtf8("m_pEditCurent"));
        m_pEditCurent->setFont(font);

        gridLayout_2->addWidget(m_pEditCurent, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 2, 1, 2);


        verticalLayout_2->addLayout(gridLayout_2);

        m_pGroupSystemParas = new QGroupBox(QDiffCBOpItemParaEditWidget);
        m_pGroupSystemParas->setObjectName(QString::fromUtf8("m_pGroupSystemParas"));
        m_pGroupSystemParas->setMaximumSize(QSize(16777215, 16777215));
        m_pGroupSystemParas->setFont(font);
        verticalLayout = new QVBoxLayout(m_pGroupSystemParas);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        m_pLabTransfHvKph = new QLabel(m_pGroupSystemParas);
        m_pLabTransfHvKph->setObjectName(QString::fromUtf8("m_pLabTransfHvKph"));
        m_pLabTransfHvKph->setMaximumSize(QSize(300, 20));
        m_pLabTransfHvKph->setFont(font);
        m_pLabTransfHvKph->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_pLabTransfHvKph, 0, 1, 1, 1);

        m_pLabTransfHvKpl = new QLabel(m_pGroupSystemParas);
        m_pLabTransfHvKpl->setObjectName(QString::fromUtf8("m_pLabTransfHvKpl"));
        m_pLabTransfHvKpl->setMaximumSize(QSize(300, 20));
        m_pLabTransfHvKpl->setFont(font);
        m_pLabTransfHvKpl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_pLabTransfHvKpl, 0, 3, 1, 1);

        m_pLabBalCoeff = new QLabel(m_pGroupSystemParas);
        m_pLabBalCoeff->setObjectName(QString::fromUtf8("m_pLabBalCoeff"));
        m_pLabBalCoeff->setFont(font);

        gridLayout->addWidget(m_pLabBalCoeff, 1, 0, 1, 1);

        m_pEditTransfHvKph = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfHvKph->setObjectName(QString::fromUtf8("m_pEditTransfHvKph"));
        m_pEditTransfHvKph->setFont(font);

        gridLayout->addWidget(m_pEditTransfHvKph, 1, 1, 1, 1);

        m_pEditTransfMvKpm = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfMvKpm->setObjectName(QString::fromUtf8("m_pEditTransfMvKpm"));
        m_pEditTransfMvKpm->setFont(font);

        gridLayout->addWidget(m_pEditTransfMvKpm, 1, 2, 1, 1);

        m_pEditTransfLvKpl = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfLvKpl->setObjectName(QString::fromUtf8("m_pEditTransfLvKpl"));
        m_pEditTransfLvKpl->setFont(font);

        gridLayout->addWidget(m_pEditTransfLvKpl, 1, 3, 1, 1);

        m_pLabVnom = new QLabel(m_pGroupSystemParas);
        m_pLabVnom->setObjectName(QString::fromUtf8("m_pLabVnom"));
        m_pLabVnom->setFont(font);

        gridLayout->addWidget(m_pLabVnom, 2, 0, 1, 1);

        m_pEditTransfHvVol = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfHvVol->setObjectName(QString::fromUtf8("m_pEditTransfHvVol"));
        m_pEditTransfHvVol->setFont(font);

        gridLayout->addWidget(m_pEditTransfHvVol, 2, 1, 1, 1);

        m_pEditTransfMvVol = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfMvVol->setObjectName(QString::fromUtf8("m_pEditTransfMvVol"));
        m_pEditTransfMvVol->setFont(font);

        gridLayout->addWidget(m_pEditTransfMvVol, 2, 2, 1, 1);

        m_pEditTransfLvVol = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfLvVol->setObjectName(QString::fromUtf8("m_pEditTransfLvVol"));
        m_pEditTransfLvVol->setFont(font);

        gridLayout->addWidget(m_pEditTransfLvVol, 2, 3, 1, 1);

        m_pLabEDCurrent = new QLabel(m_pGroupSystemParas);
        m_pLabEDCurrent->setObjectName(QString::fromUtf8("m_pLabEDCurrent"));
        m_pLabEDCurrent->setFont(font);

        gridLayout->addWidget(m_pLabEDCurrent, 3, 0, 1, 1);

        m_pEditTransfHvCur = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfHvCur->setObjectName(QString::fromUtf8("m_pEditTransfHvCur"));
        m_pEditTransfHvCur->setFont(font);

        gridLayout->addWidget(m_pEditTransfHvCur, 3, 1, 1, 1);

        m_pEditTransfMvCur = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfMvCur->setObjectName(QString::fromUtf8("m_pEditTransfMvCur"));
        m_pEditTransfMvCur->setFont(font);

        gridLayout->addWidget(m_pEditTransfMvCur, 3, 2, 1, 1);

        m_pEditTransfLvCur = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfLvCur->setObjectName(QString::fromUtf8("m_pEditTransfLvCur"));
        m_pEditTransfLvCur->setFont(font);

        gridLayout->addWidget(m_pEditTransfLvCur, 3, 3, 1, 1);

        m_pLabCT = new QLabel(m_pGroupSystemParas);
        m_pLabCT->setObjectName(QString::fromUtf8("m_pLabCT"));
        m_pLabCT->setFont(font);

        gridLayout->addWidget(m_pLabCT, 4, 0, 1, 1);

        m_pEditTransfHvCT = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfHvCT->setObjectName(QString::fromUtf8("m_pEditTransfHvCT"));
        m_pEditTransfHvCT->setFont(font);

        gridLayout->addWidget(m_pEditTransfHvCT, 4, 1, 1, 1);

        m_pEditTransfMvCT = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfMvCT->setObjectName(QString::fromUtf8("m_pEditTransfMvCT"));
        m_pEditTransfMvCT->setFont(font);

        gridLayout->addWidget(m_pEditTransfMvCT, 4, 2, 1, 1);

        m_pEditTransfLvCT = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfLvCT->setObjectName(QString::fromUtf8("m_pEditTransfLvCT"));
        m_pEditTransfLvCT->setFont(font);

        gridLayout->addWidget(m_pEditTransfLvCT, 4, 3, 1, 1);

        m_pLabTransfRatedCapacity = new QLabel(m_pGroupSystemParas);
        m_pLabTransfRatedCapacity->setObjectName(QString::fromUtf8("m_pLabTransfRatedCapacity"));
        m_pLabTransfRatedCapacity->setFont(font);

        gridLayout->addWidget(m_pLabTransfRatedCapacity, 5, 0, 1, 1);

        m_pEditTransfHvKVA = new QSettingLineEdit(m_pGroupSystemParas);
        m_pEditTransfHvKVA->setObjectName(QString::fromUtf8("m_pEditTransfHvKVA"));
        m_pEditTransfHvKVA->setFont(font);

        gridLayout->addWidget(m_pEditTransfHvKVA, 5, 1, 1, 1);

        m_pChkKph = new QCheckBox(m_pGroupSystemParas);
        m_pChkKph->setObjectName(QString::fromUtf8("m_pChkKph"));
        m_pChkKph->setFont(font);

        gridLayout->addWidget(m_pChkKph, 5, 3, 1, 1);

        m_pLabTransfHvKpm = new QLabel(m_pGroupSystemParas);
        m_pLabTransfHvKpm->setObjectName(QString::fromUtf8("m_pLabTransfHvKpm"));
        m_pLabTransfHvKpm->setMaximumSize(QSize(300, 20));
        m_pLabTransfHvKpm->setFont(font);
        m_pLabTransfHvKpm->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_pLabTransfHvKpm, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addWidget(m_pGroupSystemParas);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(17, -1, 17, -1);
        m_pLabAbsErr = new QLabel(QDiffCBOpItemParaEditWidget);
        m_pLabAbsErr->setObjectName(QString::fromUtf8("m_pLabAbsErr"));
        m_pLabAbsErr->setFont(font);

        gridLayout_3->addWidget(m_pLabAbsErr, 0, 0, 1, 1);

        m_pLabAbsErrMinus = new QLabel(QDiffCBOpItemParaEditWidget);
        m_pLabAbsErrMinus->setObjectName(QString::fromUtf8("m_pLabAbsErrMinus"));
        m_pLabAbsErrMinus->setFont(font);

        gridLayout_3->addWidget(m_pLabAbsErrMinus, 1, 0, 1, 1);

        m_pEditRelErr = new QSettingLineEdit(QDiffCBOpItemParaEditWidget);
        m_pEditRelErr->setObjectName(QString::fromUtf8("m_pEditRelErr"));
        m_pEditRelErr->setFont(font);

        gridLayout_3->addWidget(m_pEditRelErr, 0, 4, 1, 1);

        m_pEditAbsErrReduce = new QSettingLineEdit(QDiffCBOpItemParaEditWidget);
        m_pEditAbsErrReduce->setObjectName(QString::fromUtf8("m_pEditAbsErrReduce"));
        m_pEditAbsErrReduce->setFont(font);

        gridLayout_3->addWidget(m_pEditAbsErrReduce, 1, 1, 1, 1);

        m_pLabRelErr = new QLabel(QDiffCBOpItemParaEditWidget);
        m_pLabRelErr->setObjectName(QString::fromUtf8("m_pLabRelErr"));
        m_pLabRelErr->setFont(font);

        gridLayout_3->addWidget(m_pLabRelErr, 0, 3, 1, 1);

        m_pEditAbsErrSum = new QSettingLineEdit(QDiffCBOpItemParaEditWidget);
        m_pEditAbsErrSum->setObjectName(QString::fromUtf8("m_pEditAbsErrSum"));
        m_pEditAbsErrSum->setFont(font);

        gridLayout_3->addWidget(m_pEditAbsErrSum, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(QDiffCBOpItemParaEditWidget);

        QMetaObject::connectSlotsByName(QDiffCBOpItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QDiffCBOpItemParaEditWidget)
    {
        QDiffCBOpItemParaEditWidget->setWindowTitle(QApplication::translate("QDiffCBOpItemParaEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_pLabCurrent->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\347\224\265\346\265\201(In)", 0, QApplication::UnicodeUTF8));
        m_pLabFrep->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\351\242\221\347\216\207(Hz)", 0, QApplication::UnicodeUTF8));
        m_pLabFaultLocation->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\346\225\205\351\232\234\347\202\271\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        m_pLabFaultType->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\346\225\205\351\232\234\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        m_pGroupSystemParas->setTitle(QApplication::translate("QDiffCBOpItemParaEditWidget", "\347\263\273\347\273\237\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_pLabTransfHvKph->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\345\217\230\345\216\213\345\231\250\351\253\230\345\216\213\344\276\247", 0, QApplication::UnicodeUTF8));
        m_pLabTransfHvKpl->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\345\217\230\345\216\213\345\231\250\344\275\216\345\216\213\344\276\247", 0, QApplication::UnicodeUTF8));
        m_pLabBalCoeff->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\345\271\263\350\241\241\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        m_pLabVnom->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\351\242\235\345\256\232\347\224\265\345\216\213(kV)", 0, QApplication::UnicodeUTF8));
        m_pLabEDCurrent->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\351\242\235\345\256\232\347\224\265\346\265\201(A)", 0, QApplication::UnicodeUTF8));
        m_pLabCT->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "CT\345\217\230\346\257\224", 0, QApplication::UnicodeUTF8));
        m_pLabTransfRatedCapacity->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\351\242\235\345\256\232\345\256\271\351\207\217(MVA)", 0, QApplication::UnicodeUTF8));
        m_pChkKph->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\350\256\276\347\275\256\345\271\263\350\241\241\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        m_pLabTransfHvKpm->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\345\217\230\345\216\213\345\231\250\344\270\255\345\216\213\344\276\247", 0, QApplication::UnicodeUTF8));
        m_pLabAbsErr->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_pLabAbsErrMinus->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
        m_pLabRelErr->setText(QApplication::translate("QDiffCBOpItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(%):", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDiffCBOpItemParaEditWidget: public Ui_QDiffCBOpItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFCBOPITEMPARAEDITWIDGET_H
