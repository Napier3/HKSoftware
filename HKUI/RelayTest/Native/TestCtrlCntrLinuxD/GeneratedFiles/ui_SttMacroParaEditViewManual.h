/********************************************************************************
** Form generated from reading UI file 'SttMacroParaEditViewManual.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTMACROPARAEDITVIEWMANUAL_H
#define UI_STTMACROPARAEDITVIEWMANUAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../Controls/SettingCtrls/QSettingLineEdit.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QSttMacroParaEditViewManual
{
public:
    QVBoxLayout *verticalLayout_2;
    QSttTabWidget *m_tabWidget;
    QWidget *m_layoutIV;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labChannel;
    QScrollComboBox *m_cbbChannel;
    QScrollComboBox *m_cbbSelect;
    QLabel *m_labTime;
    QSettingLineEdit *m_editTime;
    QLabel *m_labUdc;
    QSettingLineEdit *m_editUdc;
    QSttCheckBox *m_cbAuto;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_labInitVal;
    QSettingLineEdit *m_editIintVal;
    QLabel *m_labFinishVal;
    QSettingLineEdit *m_editFinishVal;
    QLabel *m_labStep;
    QSettingLineEdit *m_editStep;
    QLabel *m_labChangeType;
    QScrollComboBox *m_cbbChangeType;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *m_boxOutSetting;
    QGridLayout *gridLayout;
    QSttCheckBox *m_cbOut2;
    QSttCheckBox *m_cbOut3;
    QSttCheckBox *m_cbOut4;
    QSttCheckBox *m_cbOut1;
    QSpacerItem *horizontalSpacer_5;
    QWidget *m_frmOtherPara;
    QHBoxLayout *horizontalLayout_4;
    QWidget *m_frmParas;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout;
    QCheckBox *m_cbOld;
    QCheckBox *m_cbDC;
    QCheckBox *m_checkBoxHarm;
    QScrollComboBox *m_comboBoxHarm;
    QPushButton *m_btnLock;
    QPushButton *m_btnAdd;
    QPushButton *m_btnMinus;
    QPushButton *m_btnShortCalcu;
    QPushButton *m_btnDiffCalc;
    QPushButton *m_btnInBinaryOutSet;
    QPushButton *m_btnEstimate;

    void setupUi(QWidget *QSttMacroParaEditViewManual)
    {
        if (QSttMacroParaEditViewManual->objectName().isEmpty())
            QSttMacroParaEditViewManual->setObjectName(QString::fromUtf8("QSttMacroParaEditViewManual"));
        QSttMacroParaEditViewManual->setWindowModality(Qt::NonModal);
        QSttMacroParaEditViewManual->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QSttMacroParaEditViewManual->sizePolicy().hasHeightForWidth());
        QSttMacroParaEditViewManual->setSizePolicy(sizePolicy);
        QSttMacroParaEditViewManual->setMinimumSize(QSize(0, 0));
        QSttMacroParaEditViewManual->setMaximumSize(QSize(1024, 768));
        QFont font;
        font.setPointSize(16);
        QSttMacroParaEditViewManual->setFont(font);
        QSttMacroParaEditViewManual->setFocusPolicy(Qt::StrongFocus);
        QSttMacroParaEditViewManual->setContextMenuPolicy(Qt::NoContextMenu);
        QSttMacroParaEditViewManual->setWindowOpacity(1);
        verticalLayout_2 = new QVBoxLayout(QSttMacroParaEditViewManual);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_tabWidget = new QSttTabWidget(QSttMacroParaEditViewManual);
        m_tabWidget->setObjectName(QString::fromUtf8("m_tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(m_tabWidget->sizePolicy().hasHeightForWidth());
        m_tabWidget->setSizePolicy(sizePolicy1);
        m_tabWidget->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(20);
        m_tabWidget->setFont(font1);
        m_tabWidget->setTabShape(QTabWidget::Rounded);
        m_layoutIV = new QWidget();
        m_layoutIV->setObjectName(QString::fromUtf8("m_layoutIV"));
        m_tabWidget->addTab(m_layoutIV, QString());

        verticalLayout_2->addWidget(m_tabWidget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labChannel = new QLabel(QSttMacroParaEditViewManual);
        m_labChannel->setObjectName(QString::fromUtf8("m_labChannel"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_labChannel->sizePolicy().hasHeightForWidth());
        m_labChannel->setSizePolicy(sizePolicy2);
        m_labChannel->setFont(font1);

        horizontalLayout_2->addWidget(m_labChannel);

        m_cbbChannel = new QScrollComboBox(QSttMacroParaEditViewManual);
        m_cbbChannel->setObjectName(QString::fromUtf8("m_cbbChannel"));
        m_cbbChannel->setMinimumSize(QSize(0, 0));
        m_cbbChannel->setMaximumSize(QSize(16777215, 16777215));
        m_cbbChannel->setFont(font1);

        horizontalLayout_2->addWidget(m_cbbChannel);

        m_cbbSelect = new QScrollComboBox(QSttMacroParaEditViewManual);
        m_cbbSelect->setObjectName(QString::fromUtf8("m_cbbSelect"));
        m_cbbSelect->setMinimumSize(QSize(0, 0));
        m_cbbSelect->setMaximumSize(QSize(16777215, 16777215));
        m_cbbSelect->setFont(font1);

        horizontalLayout_2->addWidget(m_cbbSelect);

        m_labTime = new QLabel(QSttMacroParaEditViewManual);
        m_labTime->setObjectName(QString::fromUtf8("m_labTime"));
        m_labTime->setFont(font1);

        horizontalLayout_2->addWidget(m_labTime);

        m_editTime = new QSettingLineEdit(QSttMacroParaEditViewManual);
        m_editTime->setObjectName(QString::fromUtf8("m_editTime"));
        m_editTime->setFont(font1);
        m_editTime->setFrame(true);

        horizontalLayout_2->addWidget(m_editTime);

        m_labUdc = new QLabel(QSttMacroParaEditViewManual);
        m_labUdc->setObjectName(QString::fromUtf8("m_labUdc"));

        horizontalLayout_2->addWidget(m_labUdc);

        m_editUdc = new QSettingLineEdit(QSttMacroParaEditViewManual);
        m_editUdc->setObjectName(QString::fromUtf8("m_editUdc"));

        horizontalLayout_2->addWidget(m_editUdc);

        m_cbAuto = new QSttCheckBox(QSttMacroParaEditViewManual);
        m_cbAuto->setObjectName(QString::fromUtf8("m_cbAuto"));
        sizePolicy.setHeightForWidth(m_cbAuto->sizePolicy().hasHeightForWidth());
        m_cbAuto->setSizePolicy(sizePolicy);
        m_cbAuto->setFont(font1);
        m_cbAuto->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(m_cbAuto);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_labInitVal = new QLabel(QSttMacroParaEditViewManual);
        m_labInitVal->setObjectName(QString::fromUtf8("m_labInitVal"));
        m_labInitVal->setFont(font1);

        horizontalLayout_3->addWidget(m_labInitVal);

        m_editIintVal = new QSettingLineEdit(QSttMacroParaEditViewManual);
        m_editIintVal->setObjectName(QString::fromUtf8("m_editIintVal"));
        m_editIintVal->setFont(font1);

        horizontalLayout_3->addWidget(m_editIintVal);

        m_labFinishVal = new QLabel(QSttMacroParaEditViewManual);
        m_labFinishVal->setObjectName(QString::fromUtf8("m_labFinishVal"));
        m_labFinishVal->setFont(font1);

        horizontalLayout_3->addWidget(m_labFinishVal);

        m_editFinishVal = new QSettingLineEdit(QSttMacroParaEditViewManual);
        m_editFinishVal->setObjectName(QString::fromUtf8("m_editFinishVal"));
        m_editFinishVal->setFont(font1);
        m_editFinishVal->setFrame(true);
        m_editFinishVal->setEchoMode(QLineEdit::Normal);
        m_editFinishVal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_editFinishVal);

        m_labStep = new QLabel(QSttMacroParaEditViewManual);
        m_labStep->setObjectName(QString::fromUtf8("m_labStep"));
        m_labStep->setFont(font1);

        horizontalLayout_3->addWidget(m_labStep);

        m_editStep = new QSettingLineEdit(QSttMacroParaEditViewManual);
        m_editStep->setObjectName(QString::fromUtf8("m_editStep"));
        m_editStep->setFont(font1);

        horizontalLayout_3->addWidget(m_editStep);

        m_labChangeType = new QLabel(QSttMacroParaEditViewManual);
        m_labChangeType->setObjectName(QString::fromUtf8("m_labChangeType"));
        m_labChangeType->setFont(font1);

        horizontalLayout_3->addWidget(m_labChangeType);

        m_cbbChangeType = new QScrollComboBox(QSttMacroParaEditViewManual);
        m_cbbChangeType->setObjectName(QString::fromUtf8("m_cbbChangeType"));
        m_cbbChangeType->setFont(font1);

        horizontalLayout_3->addWidget(m_cbbChangeType);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_6->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(37, 39, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        m_boxOutSetting = new QGroupBox(QSttMacroParaEditViewManual);
        m_boxOutSetting->setObjectName(QString::fromUtf8("m_boxOutSetting"));
        sizePolicy.setHeightForWidth(m_boxOutSetting->sizePolicy().hasHeightForWidth());
        m_boxOutSetting->setSizePolicy(sizePolicy);
        m_boxOutSetting->setMinimumSize(QSize(0, 0));
        m_boxOutSetting->setMaximumSize(QSize(16777215, 16777215));
        m_boxOutSetting->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        m_boxOutSetting->setFlat(false);
        m_boxOutSetting->setCheckable(false);
        gridLayout = new QGridLayout(m_boxOutSetting);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_cbOut2 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut2->setObjectName(QString::fromUtf8("m_cbOut2"));
        m_cbOut2->setFont(font1);
        m_cbOut2->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbOut2, 0, 1, 1, 1);

        m_cbOut3 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut3->setObjectName(QString::fromUtf8("m_cbOut3"));
        m_cbOut3->setFont(font1);
        m_cbOut3->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbOut3, 1, 0, 1, 1);

        m_cbOut4 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut4->setObjectName(QString::fromUtf8("m_cbOut4"));
        m_cbOut4->setFont(font1);
        m_cbOut4->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(m_cbOut4, 1, 1, 1, 1);

        m_cbOut1 = new QSttCheckBox(m_boxOutSetting);
        m_cbOut1->setObjectName(QString::fromUtf8("m_cbOut1"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_cbOut1->sizePolicy().hasHeightForWidth());
        m_cbOut1->setSizePolicy(sizePolicy3);
        m_cbOut1->setFont(font1);
        m_cbOut1->setAutoFillBackground(false);
        m_cbOut1->setStyleSheet(QString::fromUtf8(""));
        m_cbOut1->setCheckable(true);
        m_cbOut1->setChecked(false);
        m_cbOut1->setAutoRepeat(false);
        m_cbOut1->setAutoExclusive(false);

        gridLayout->addWidget(m_cbOut1, 0, 0, 1, 1);


        horizontalLayout_6->addWidget(m_boxOutSetting);

        horizontalSpacer_5 = new QSpacerItem(37, 38, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_6);

        m_frmOtherPara = new QWidget(QSttMacroParaEditViewManual);
        m_frmOtherPara->setObjectName(QString::fromUtf8("m_frmOtherPara"));
        horizontalLayout_4 = new QHBoxLayout(m_frmOtherPara);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(m_frmOtherPara);

        m_frmParas = new QWidget(QSttMacroParaEditViewManual);
        m_frmParas->setObjectName(QString::fromUtf8("m_frmParas"));
        horizontalLayout_5 = new QHBoxLayout(m_frmParas);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_cbOld = new QCheckBox(m_frmParas);
        m_cbOld->setObjectName(QString::fromUtf8("m_cbOld"));

        horizontalLayout->addWidget(m_cbOld);

        m_cbDC = new QCheckBox(m_frmParas);
        m_cbDC->setObjectName(QString::fromUtf8("m_cbDC"));

        horizontalLayout->addWidget(m_cbDC);

        m_checkBoxHarm = new QCheckBox(m_frmParas);
        m_checkBoxHarm->setObjectName(QString::fromUtf8("m_checkBoxHarm"));

        horizontalLayout->addWidget(m_checkBoxHarm);

        m_comboBoxHarm = new QScrollComboBox(m_frmParas);
        m_comboBoxHarm->setObjectName(QString::fromUtf8("m_comboBoxHarm"));

        horizontalLayout->addWidget(m_comboBoxHarm);

        m_btnLock = new QPushButton(m_frmParas);
        m_btnLock->setObjectName(QString::fromUtf8("m_btnLock"));
        sizePolicy3.setHeightForWidth(m_btnLock->sizePolicy().hasHeightForWidth());
        m_btnLock->setSizePolicy(sizePolicy3);
        m_btnLock->setMinimumSize(QSize(0, 0));
        m_btnLock->setMaximumSize(QSize(16777215, 16777215));
        m_btnLock->setFont(font1);

        horizontalLayout->addWidget(m_btnLock);

        m_btnAdd = new QPushButton(m_frmParas);
        m_btnAdd->setObjectName(QString::fromUtf8("m_btnAdd"));
        m_btnAdd->setFont(font1);

        horizontalLayout->addWidget(m_btnAdd);

        m_btnMinus = new QPushButton(m_frmParas);
        m_btnMinus->setObjectName(QString::fromUtf8("m_btnMinus"));
        m_btnMinus->setFont(font1);

        horizontalLayout->addWidget(m_btnMinus);

        m_btnShortCalcu = new QPushButton(m_frmParas);
        m_btnShortCalcu->setObjectName(QString::fromUtf8("m_btnShortCalcu"));
        m_btnShortCalcu->setFont(font1);

        horizontalLayout->addWidget(m_btnShortCalcu);

        m_btnDiffCalc = new QPushButton(m_frmParas);
        m_btnDiffCalc->setObjectName(QString::fromUtf8("m_btnDiffCalc"));
        m_btnDiffCalc->setFont(font1);

        horizontalLayout->addWidget(m_btnDiffCalc);

        m_btnInBinaryOutSet = new QPushButton(m_frmParas);
        m_btnInBinaryOutSet->setObjectName(QString::fromUtf8("m_btnInBinaryOutSet"));
        m_btnInBinaryOutSet->setFont(font1);

        horizontalLayout->addWidget(m_btnInBinaryOutSet);

        m_btnEstimate = new QPushButton(m_frmParas);
        m_btnEstimate->setObjectName(QString::fromUtf8("m_btnEstimate"));
        m_btnEstimate->setFont(font1);

        horizontalLayout->addWidget(m_btnEstimate);


        horizontalLayout_5->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(m_frmParas);


        retranslateUi(QSttMacroParaEditViewManual);

        m_tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QSttMacroParaEditViewManual);
    } // setupUi

    void retranslateUi(QWidget *QSttMacroParaEditViewManual)
    {
        QSttMacroParaEditViewManual->setWindowTitle(QApplication::translate("QSttMacroParaEditViewManual", "QSttMacroParaEditManualTestView", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(m_layoutIV), QApplication::translate("QSttMacroParaEditViewManual", "\347\224\265\345\216\213\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_labChannel->setText(QApplication::translate("QSttMacroParaEditViewManual", "\351\200\232\351\201\223\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_cbbSelect->clear();
        m_cbbSelect->insertItems(0, QStringList()
         << QApplication::translate("QSttMacroParaEditViewManual", "\345\271\205\345\200\274", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewManual", "\347\233\270\344\275\215", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewManual", "\351\242\221\347\216\207", 0, QApplication::UnicodeUTF8)
        );
        m_labTime->setText(QApplication::translate("QSttMacroParaEditViewManual", "\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labUdc->setText(QApplication::translate("QSttMacroParaEditViewManual", "Udc(V):", 0, QApplication::UnicodeUTF8));
        m_cbAuto->setText(QApplication::translate("QSttMacroParaEditViewManual", "\350\207\252\345\212\250", 0, QApplication::UnicodeUTF8));
        m_labInitVal->setText(QApplication::translate("QSttMacroParaEditViewManual", "\345\247\213\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_labFinishVal->setText(QApplication::translate("QSttMacroParaEditViewManual", "\347\273\210\345\200\274(V):", 0, QApplication::UnicodeUTF8));
        m_editFinishVal->setText(QString());
        m_labStep->setText(QApplication::translate("QSttMacroParaEditViewManual", "\346\255\245\351\225\277(V):", 0, QApplication::UnicodeUTF8));
        m_labChangeType->setText(QApplication::translate("QSttMacroParaEditViewManual", "\345\217\230\345\214\226\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_cbbChangeType->clear();
        m_cbbChangeType->insertItems(0, QStringList()
         << QApplication::translate("QSttMacroParaEditViewManual", "\345\247\213\342\200\224\347\273\210", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewManual", "\345\247\213\342\200\224\347\273\210\342\200\224\345\247\213", 0, QApplication::UnicodeUTF8)
        );
        m_boxOutSetting->setTitle(QApplication::translate("QSttMacroParaEditViewManual", "\345\274\200\345\207\272\351\207\217", 0, QApplication::UnicodeUTF8));
        m_cbOut2->setText(QApplication::translate("QSttMacroParaEditViewManual", "2", 0, QApplication::UnicodeUTF8));
        m_cbOut3->setText(QApplication::translate("QSttMacroParaEditViewManual", "3", 0, QApplication::UnicodeUTF8));
        m_cbOut4->setText(QApplication::translate("QSttMacroParaEditViewManual", "4", 0, QApplication::UnicodeUTF8));
        m_cbOut1->setText(QApplication::translate("QSttMacroParaEditViewManual", "1", 0, QApplication::UnicodeUTF8));
        m_cbOld->setText(QApplication::translate("QSttMacroParaEditViewManual", "\350\200\201\345\214\226", 0, QApplication::UnicodeUTF8));
        m_cbDC->setText(QApplication::translate("QSttMacroParaEditViewManual", "\347\233\264\346\265\201", 0, QApplication::UnicodeUTF8));
        m_checkBoxHarm->setText(QApplication::translate("QSttMacroParaEditViewManual", "\345\217\240\345\212\240\350\260\220\346\263\242", 0, QApplication::UnicodeUTF8));
        m_btnLock->setText(QApplication::translate("QSttMacroParaEditViewManual", "\351\224\201", 0, QApplication::UnicodeUTF8));
        m_btnAdd->setText(QApplication::translate("QSttMacroParaEditViewManual", "+", 0, QApplication::UnicodeUTF8));
        m_btnMinus->setText(QApplication::translate("QSttMacroParaEditViewManual", "-", 0, QApplication::UnicodeUTF8));
        m_btnShortCalcu->setText(QApplication::translate("QSttMacroParaEditViewManual", "\347\237\255\350\267\257\350\256\241\347\256\227", 0, QApplication::UnicodeUTF8));
        m_btnDiffCalc->setText(QApplication::translate("QSttMacroParaEditViewManual", "\345\267\256\346\265\201\350\256\241\347\256\227", 0, QApplication::UnicodeUTF8));
        m_btnInBinaryOutSet->setText(QApplication::translate("QSttMacroParaEditViewManual", "\345\274\200\345\205\263\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_btnEstimate->setText(QApplication::translate("QSttMacroParaEditViewManual", "\346\225\264\345\256\232\345\217\212\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttMacroParaEditViewManual: public Ui_QSttMacroParaEditViewManual {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTMACROPARAEDITVIEWMANUAL_H
