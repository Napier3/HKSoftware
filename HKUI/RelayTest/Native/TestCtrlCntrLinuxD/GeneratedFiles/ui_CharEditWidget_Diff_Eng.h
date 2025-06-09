/********************************************************************************
** Form generated from reading UI file 'CharEditWidget_Diff_Eng.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAREDITWIDGET_DIFF_ENG_H
#define UI_CHAREDITWIDGET_DIFF_ENG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../../Controls/SttCheckBox.h"
#include "../../../Controls/SttLineEdit.h"
#include "../../CommonCtrl_QT/QDataTypeComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QCharEditWidget_Diff_Eng
{
public:
    QVBoxLayout *verticalLayout_4;
    QTabWidget *m_DiffTypeTab;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QSttLineEdit *m_editInSet;
    QDataTypeComboBox *m_cbInSel;
    QRadioButton *m_radioSetting;
    QLabel *m_lbSettingMinAxis;
    QRadioButton *m_radioUser;
    QLabel *m_lbInSel;
    QLabel *m_lbTypeSel;
    QDataTypeComboBox *m_cbTypeSel;
    QDataTypeComboBox *m_cbSettingMinAxis;
    QLabel *m_lbInSet;
    QLabel *m_labCombinedFeature;
    QComboBox *m_cmbCombinedFeature;
    QLabel *m_labZeroSeqElimiType;
    QComboBox *m_cmbZeroSeqElimiType;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QSttLineEdit *m_editIQuick;
    QLabel *m_lbIQuick;
    QSttLineEdit *m_editCustomHarmIndex;
    QSttLineEdit *m_editIDoor;
    QSttLineEdit *m_editHarmCoef;
    QLabel *m_lbInSel2;
    QLabel *m_lbSettingMinAxis2;
    QLabel *m_lbHarmIndex_2;
    QLabel *m_lbInSet2;
    QLabel *m_lbIDoor;
    QLabel *m_lbHarmCoef;
    QSttLineEdit *m_editInSet2;
    QDataTypeComboBox *m_cbInSel2;
    QLabel *m_lbHarmIndex;
    QComboBox *m_cbHarmIndex;
    QLabel *m_labCombinedFeature2;
    QComboBox *m_cmbCombinedFeature2;
    QDataTypeComboBox *m_cbSettingMinAxis2;
    QLabel *m_labZeroSeqElimiType2;
    QComboBox *m_cmbZeroSeqElimiType2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *m_layoutVert;
    QGridLayout *m_layGridParas;
    QLabel *m_lblTitleStart;
    QSttLineEdit *m_edtSet_Istart;
    QSttLineEdit *m_edtSet_Kstart;
    QSttCheckBox *m_chkLine1;
    QSttLineEdit *m_edtSet_Ip1;
    QLabel *m_lblTitleCurr;
    QLabel *m_lblTitleK;
    QSttCheckBox *m_chkLine2;
    QSttCheckBox *m_chkLine3;
    QSttCheckBox *m_chkStart;
    QSttLineEdit *m_edtSet_K1;
    QLabel *m_lblTitleLine1;
    QSttCheckBox *m_chkLineSd;
    QLabel *m_lblTitleLineSd;
    QLabel *m_lblTitleLine3;
    QSttLineEdit *m_edtSet_Ip3;
    QSttLineEdit *m_edtSet_Ip2;
    QSttLineEdit *m_edtSet_Isd;
    QSttLineEdit *m_edtSet_K2;
    QSttLineEdit *m_edtSet_K3;
    QLabel *m_lbSetting;
    QLabel *m_lbName;
    QLabel *m_lblTitleLine2;

    void setupUi(QWidget *QCharEditWidget_Diff_Eng)
    {
        if (QCharEditWidget_Diff_Eng->objectName().isEmpty())
            QCharEditWidget_Diff_Eng->setObjectName(QString::fromUtf8("QCharEditWidget_Diff_Eng"));
        QCharEditWidget_Diff_Eng->resize(492, 458);
        verticalLayout_4 = new QVBoxLayout(QCharEditWidget_Diff_Eng);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        m_DiffTypeTab = new QTabWidget(QCharEditWidget_Diff_Eng);
        m_DiffTypeTab->setObjectName(QString::fromUtf8("m_DiffTypeTab"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_DiffTypeTab->sizePolicy().hasHeightForWidth());
        m_DiffTypeTab->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(9);
        m_DiffTypeTab->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_editInSet = new QSttLineEdit(tab);
        m_editInSet->setObjectName(QString::fromUtf8("m_editInSet"));
        m_editInSet->setMinimumSize(QSize(0, 20));
        m_editInSet->setMaximumSize(QSize(250, 25));
        m_editInSet->setFont(font);

        gridLayout->addWidget(m_editInSet, 1, 3, 1, 1);

        m_cbInSel = new QDataTypeComboBox(tab);
        m_cbInSel->setObjectName(QString::fromUtf8("m_cbInSel"));
        m_cbInSel->setMinimumSize(QSize(0, 20));
        m_cbInSel->setMaximumSize(QSize(250, 25));
        m_cbInSel->setFont(font);

        gridLayout->addWidget(m_cbInSel, 0, 3, 1, 1);

        m_radioSetting = new QRadioButton(tab);
        m_radioSetting->setObjectName(QString::fromUtf8("m_radioSetting"));
        m_radioSetting->setMinimumSize(QSize(0, 20));
        m_radioSetting->setMaximumSize(QSize(140, 25));
        m_radioSetting->setFont(font);
        m_radioSetting->setChecked(true);

        gridLayout->addWidget(m_radioSetting, 3, 0, 1, 1);

        m_lbSettingMinAxis = new QLabel(tab);
        m_lbSettingMinAxis->setObjectName(QString::fromUtf8("m_lbSettingMinAxis"));
        m_lbSettingMinAxis->setMinimumSize(QSize(0, 20));
        m_lbSettingMinAxis->setMaximumSize(QSize(140, 25));
        m_lbSettingMinAxis->setFont(font);

        gridLayout->addWidget(m_lbSettingMinAxis, 0, 0, 1, 1);

        m_radioUser = new QRadioButton(tab);
        m_radioUser->setObjectName(QString::fromUtf8("m_radioUser"));
        m_radioUser->setMinimumSize(QSize(0, 20));
        m_radioUser->setMaximumSize(QSize(250, 25));
        m_radioUser->setFont(font);

        gridLayout->addWidget(m_radioUser, 3, 1, 1, 1);

        m_lbInSel = new QLabel(tab);
        m_lbInSel->setObjectName(QString::fromUtf8("m_lbInSel"));
        m_lbInSel->setMinimumSize(QSize(0, 20));
        m_lbInSel->setMaximumSize(QSize(140, 25));
        m_lbInSel->setFont(font);

        gridLayout->addWidget(m_lbInSel, 0, 2, 1, 1);

        m_lbTypeSel = new QLabel(tab);
        m_lbTypeSel->setObjectName(QString::fromUtf8("m_lbTypeSel"));
        m_lbTypeSel->setMinimumSize(QSize(0, 20));
        m_lbTypeSel->setMaximumSize(QSize(140, 25));
        m_lbTypeSel->setFont(font);

        gridLayout->addWidget(m_lbTypeSel, 3, 2, 1, 1);

        m_cbTypeSel = new QDataTypeComboBox(tab);
        m_cbTypeSel->setObjectName(QString::fromUtf8("m_cbTypeSel"));
        m_cbTypeSel->setEnabled(false);
        m_cbTypeSel->setMinimumSize(QSize(0, 20));
        m_cbTypeSel->setMaximumSize(QSize(250, 25));
        m_cbTypeSel->setFont(font);

        gridLayout->addWidget(m_cbTypeSel, 3, 3, 1, 1);

        m_cbSettingMinAxis = new QDataTypeComboBox(tab);
        m_cbSettingMinAxis->setObjectName(QString::fromUtf8("m_cbSettingMinAxis"));
        m_cbSettingMinAxis->setMinimumSize(QSize(0, 20));
        m_cbSettingMinAxis->setMaximumSize(QSize(250, 25));
        m_cbSettingMinAxis->setFont(font);

        gridLayout->addWidget(m_cbSettingMinAxis, 0, 1, 1, 1);

        m_lbInSet = new QLabel(tab);
        m_lbInSet->setObjectName(QString::fromUtf8("m_lbInSet"));
        m_lbInSet->setMinimumSize(QSize(0, 20));
        m_lbInSet->setMaximumSize(QSize(140, 25));
        m_lbInSet->setFont(font);

        gridLayout->addWidget(m_lbInSet, 1, 2, 1, 1);

        m_labCombinedFeature = new QLabel(tab);
        m_labCombinedFeature->setObjectName(QString::fromUtf8("m_labCombinedFeature"));
        m_labCombinedFeature->setMinimumSize(QSize(0, 20));
        m_labCombinedFeature->setMaximumSize(QSize(140, 25));
        m_labCombinedFeature->setFont(font);

        gridLayout->addWidget(m_labCombinedFeature, 2, 0, 1, 1);

        m_cmbCombinedFeature = new QComboBox(tab);
        m_cmbCombinedFeature->setObjectName(QString::fromUtf8("m_cmbCombinedFeature"));
        m_cmbCombinedFeature->setMinimumSize(QSize(0, 20));
        m_cmbCombinedFeature->setMaximumSize(QSize(250, 25));
        m_cmbCombinedFeature->setFont(font);

        gridLayout->addWidget(m_cmbCombinedFeature, 2, 1, 1, 1);

        m_labZeroSeqElimiType = new QLabel(tab);
        m_labZeroSeqElimiType->setObjectName(QString::fromUtf8("m_labZeroSeqElimiType"));
        m_labZeroSeqElimiType->setMinimumSize(QSize(0, 20));
        m_labZeroSeqElimiType->setMaximumSize(QSize(140, 25));
        m_labZeroSeqElimiType->setFont(font);

        gridLayout->addWidget(m_labZeroSeqElimiType, 2, 2, 1, 1);

        m_cmbZeroSeqElimiType = new QComboBox(tab);
        m_cmbZeroSeqElimiType->setObjectName(QString::fromUtf8("m_cmbZeroSeqElimiType"));
        m_cmbZeroSeqElimiType->setMinimumSize(QSize(0, 20));
        m_cmbZeroSeqElimiType->setMaximumSize(QSize(250, 25));
        m_cmbZeroSeqElimiType->setFont(font);

        gridLayout->addWidget(m_cmbZeroSeqElimiType, 2, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        m_DiffTypeTab->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_editIQuick = new QSttLineEdit(tab_2);
        m_editIQuick->setObjectName(QString::fromUtf8("m_editIQuick"));
        m_editIQuick->setMinimumSize(QSize(0, 20));
        m_editIQuick->setMaximumSize(QSize(250, 25));
        m_editIQuick->setFont(font);

        gridLayout_2->addWidget(m_editIQuick, 4, 3, 1, 1);

        m_lbIQuick = new QLabel(tab_2);
        m_lbIQuick->setObjectName(QString::fromUtf8("m_lbIQuick"));
        m_lbIQuick->setMinimumSize(QSize(0, 20));
        m_lbIQuick->setMaximumSize(QSize(140, 25));
        m_lbIQuick->setFont(font);

        gridLayout_2->addWidget(m_lbIQuick, 4, 2, 1, 1);

        m_editCustomHarmIndex = new QSttLineEdit(tab_2);
        m_editCustomHarmIndex->setObjectName(QString::fromUtf8("m_editCustomHarmIndex"));
        m_editCustomHarmIndex->setMinimumSize(QSize(0, 20));
        m_editCustomHarmIndex->setMaximumSize(QSize(250, 25));
        m_editCustomHarmIndex->setFont(font);

        gridLayout_2->addWidget(m_editCustomHarmIndex, 2, 3, 1, 1);

        m_editIDoor = new QSttLineEdit(tab_2);
        m_editIDoor->setObjectName(QString::fromUtf8("m_editIDoor"));
        m_editIDoor->setMinimumSize(QSize(0, 20));
        m_editIDoor->setMaximumSize(QSize(250, 25));
        m_editIDoor->setFont(font);

        gridLayout_2->addWidget(m_editIDoor, 3, 3, 1, 1);

        m_editHarmCoef = new QSttLineEdit(tab_2);
        m_editHarmCoef->setObjectName(QString::fromUtf8("m_editHarmCoef"));
        m_editHarmCoef->setMinimumSize(QSize(0, 20));
        m_editHarmCoef->setMaximumSize(QSize(250, 25));
        m_editHarmCoef->setFont(font);

        gridLayout_2->addWidget(m_editHarmCoef, 3, 1, 1, 1);

        m_lbInSel2 = new QLabel(tab_2);
        m_lbInSel2->setObjectName(QString::fromUtf8("m_lbInSel2"));
        m_lbInSel2->setMinimumSize(QSize(0, 20));
        m_lbInSel2->setMaximumSize(QSize(140, 25));
        m_lbInSel2->setFont(font);

        gridLayout_2->addWidget(m_lbInSel2, 0, 2, 1, 1);

        m_lbSettingMinAxis2 = new QLabel(tab_2);
        m_lbSettingMinAxis2->setObjectName(QString::fromUtf8("m_lbSettingMinAxis2"));
        m_lbSettingMinAxis2->setMinimumSize(QSize(0, 20));
        m_lbSettingMinAxis2->setMaximumSize(QSize(140, 25));
        m_lbSettingMinAxis2->setFont(font);

        gridLayout_2->addWidget(m_lbSettingMinAxis2, 0, 0, 1, 1);

        m_lbHarmIndex_2 = new QLabel(tab_2);
        m_lbHarmIndex_2->setObjectName(QString::fromUtf8("m_lbHarmIndex_2"));
        m_lbHarmIndex_2->setMinimumSize(QSize(0, 20));
        m_lbHarmIndex_2->setMaximumSize(QSize(140, 25));
        m_lbHarmIndex_2->setFont(font);
        m_lbHarmIndex_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_lbHarmIndex_2, 2, 2, 1, 1);

        m_lbInSet2 = new QLabel(tab_2);
        m_lbInSet2->setObjectName(QString::fromUtf8("m_lbInSet2"));
        m_lbInSet2->setMinimumSize(QSize(0, 20));
        m_lbInSet2->setMaximumSize(QSize(140, 25));
        m_lbInSet2->setFont(font);

        gridLayout_2->addWidget(m_lbInSet2, 1, 2, 1, 1);

        m_lbIDoor = new QLabel(tab_2);
        m_lbIDoor->setObjectName(QString::fromUtf8("m_lbIDoor"));
        m_lbIDoor->setMinimumSize(QSize(0, 20));
        m_lbIDoor->setMaximumSize(QSize(140, 25));
        m_lbIDoor->setFont(font);

        gridLayout_2->addWidget(m_lbIDoor, 3, 2, 1, 1);

        m_lbHarmCoef = new QLabel(tab_2);
        m_lbHarmCoef->setObjectName(QString::fromUtf8("m_lbHarmCoef"));
        m_lbHarmCoef->setMinimumSize(QSize(0, 20));
        m_lbHarmCoef->setMaximumSize(QSize(140, 25));
        m_lbHarmCoef->setFont(font);
        m_lbHarmCoef->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_lbHarmCoef, 3, 0, 1, 1);

        m_editInSet2 = new QSttLineEdit(tab_2);
        m_editInSet2->setObjectName(QString::fromUtf8("m_editInSet2"));
        m_editInSet2->setMinimumSize(QSize(0, 20));
        m_editInSet2->setMaximumSize(QSize(250, 25));
        m_editInSet2->setFont(font);

        gridLayout_2->addWidget(m_editInSet2, 1, 3, 1, 1);

        m_cbInSel2 = new QDataTypeComboBox(tab_2);
        m_cbInSel2->setObjectName(QString::fromUtf8("m_cbInSel2"));
        m_cbInSel2->setMinimumSize(QSize(0, 20));
        m_cbInSel2->setMaximumSize(QSize(250, 25));
        m_cbInSel2->setFont(font);

        gridLayout_2->addWidget(m_cbInSel2, 0, 3, 1, 1);

        m_lbHarmIndex = new QLabel(tab_2);
        m_lbHarmIndex->setObjectName(QString::fromUtf8("m_lbHarmIndex"));
        m_lbHarmIndex->setMinimumSize(QSize(0, 20));
        m_lbHarmIndex->setMaximumSize(QSize(140, 25));
        m_lbHarmIndex->setFont(font);
        m_lbHarmIndex->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(m_lbHarmIndex, 2, 0, 1, 1);

        m_cbHarmIndex = new QComboBox(tab_2);
        m_cbHarmIndex->setObjectName(QString::fromUtf8("m_cbHarmIndex"));
        m_cbHarmIndex->setMinimumSize(QSize(0, 20));
        m_cbHarmIndex->setMaximumSize(QSize(250, 25));
        m_cbHarmIndex->setFont(font);

        gridLayout_2->addWidget(m_cbHarmIndex, 2, 1, 1, 1);

        m_labCombinedFeature2 = new QLabel(tab_2);
        m_labCombinedFeature2->setObjectName(QString::fromUtf8("m_labCombinedFeature2"));
        m_labCombinedFeature2->setMinimumSize(QSize(0, 20));
        m_labCombinedFeature2->setMaximumSize(QSize(140, 25));
        m_labCombinedFeature2->setFont(font);

        gridLayout_2->addWidget(m_labCombinedFeature2, 5, 0, 1, 1);

        m_cmbCombinedFeature2 = new QComboBox(tab_2);
        m_cmbCombinedFeature2->setObjectName(QString::fromUtf8("m_cmbCombinedFeature2"));
        m_cmbCombinedFeature2->setMinimumSize(QSize(0, 20));
        m_cmbCombinedFeature2->setMaximumSize(QSize(250, 25));
        m_cmbCombinedFeature2->setFont(font);

        gridLayout_2->addWidget(m_cmbCombinedFeature2, 5, 1, 1, 1);

        m_cbSettingMinAxis2 = new QDataTypeComboBox(tab_2);
        m_cbSettingMinAxis2->setObjectName(QString::fromUtf8("m_cbSettingMinAxis2"));
        m_cbSettingMinAxis2->setMinimumSize(QSize(0, 20));
        m_cbSettingMinAxis2->setMaximumSize(QSize(250, 25));
        m_cbSettingMinAxis2->setFont(font);

        gridLayout_2->addWidget(m_cbSettingMinAxis2, 0, 1, 1, 1);

        m_labZeroSeqElimiType2 = new QLabel(tab_2);
        m_labZeroSeqElimiType2->setObjectName(QString::fromUtf8("m_labZeroSeqElimiType2"));
        m_labZeroSeqElimiType2->setMinimumSize(QSize(0, 20));
        m_labZeroSeqElimiType2->setMaximumSize(QSize(140, 25));
        m_labZeroSeqElimiType2->setFont(font);

        gridLayout_2->addWidget(m_labZeroSeqElimiType2, 5, 2, 1, 1);

        m_cmbZeroSeqElimiType2 = new QComboBox(tab_2);
        m_cmbZeroSeqElimiType2->setObjectName(QString::fromUtf8("m_cmbZeroSeqElimiType2"));
        m_cmbZeroSeqElimiType2->setMinimumSize(QSize(0, 20));
        m_cmbZeroSeqElimiType2->setMaximumSize(QSize(250, 25));
        m_cmbZeroSeqElimiType2->setFont(font);

        gridLayout_2->addWidget(m_cmbZeroSeqElimiType2, 5, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        m_DiffTypeTab->addTab(tab_2, QString());

        verticalLayout_4->addWidget(m_DiffTypeTab);

        frame = new QFrame(QCharEditWidget_Diff_Eng);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_layoutVert = new QVBoxLayout();
        m_layoutVert->setSpacing(6);
        m_layoutVert->setObjectName(QString::fromUtf8("m_layoutVert"));
        m_layGridParas = new QGridLayout();
        m_layGridParas->setSpacing(6);
        m_layGridParas->setObjectName(QString::fromUtf8("m_layGridParas"));
        m_lblTitleStart = new QLabel(frame);
        m_lblTitleStart->setObjectName(QString::fromUtf8("m_lblTitleStart"));
        m_lblTitleStart->setMinimumSize(QSize(0, 20));
        m_lblTitleStart->setMaximumSize(QSize(130, 25));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(9);
        m_lblTitleStart->setFont(font1);
        m_lblTitleStart->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lblTitleStart, 1, 1, 1, 1);

        m_edtSet_Istart = new QSttLineEdit(frame);
        m_edtSet_Istart->setObjectName(QString::fromUtf8("m_edtSet_Istart"));
        m_edtSet_Istart->setMinimumSize(QSize(0, 20));
        m_edtSet_Istart->setMaximumSize(QSize(130, 25));
        m_edtSet_Istart->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Istart, 1, 2, 1, 1);

        m_edtSet_Kstart = new QSttLineEdit(frame);
        m_edtSet_Kstart->setObjectName(QString::fromUtf8("m_edtSet_Kstart"));
        m_edtSet_Kstart->setMinimumSize(QSize(0, 20));
        m_edtSet_Kstart->setMaximumSize(QSize(130, 25));
        m_edtSet_Kstart->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Kstart, 1, 3, 1, 1);

        m_chkLine1 = new QSttCheckBox(frame);
        m_chkLine1->setObjectName(QString::fromUtf8("m_chkLine1"));
        m_chkLine1->setMinimumSize(QSize(0, 20));
        m_chkLine1->setMaximumSize(QSize(130, 25));
        m_chkLine1->setFont(font1);

        m_layGridParas->addWidget(m_chkLine1, 2, 0, 1, 1);

        m_edtSet_Ip1 = new QSttLineEdit(frame);
        m_edtSet_Ip1->setObjectName(QString::fromUtf8("m_edtSet_Ip1"));
        m_edtSet_Ip1->setMinimumSize(QSize(0, 20));
        m_edtSet_Ip1->setMaximumSize(QSize(130, 25));
        m_edtSet_Ip1->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Ip1, 2, 2, 1, 1);

        m_lblTitleCurr = new QLabel(frame);
        m_lblTitleCurr->setObjectName(QString::fromUtf8("m_lblTitleCurr"));
        m_lblTitleCurr->setMinimumSize(QSize(0, 20));
        m_lblTitleCurr->setMaximumSize(QSize(130, 25));
        m_lblTitleCurr->setFont(font1);
        m_lblTitleCurr->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lblTitleCurr, 0, 2, 1, 1);

        m_lblTitleK = new QLabel(frame);
        m_lblTitleK->setObjectName(QString::fromUtf8("m_lblTitleK"));
        m_lblTitleK->setMinimumSize(QSize(0, 20));
        m_lblTitleK->setMaximumSize(QSize(130, 25));
        m_lblTitleK->setFont(font1);
        m_lblTitleK->setLayoutDirection(Qt::LeftToRight);
        m_lblTitleK->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lblTitleK, 0, 3, 1, 1);

        m_chkLine2 = new QSttCheckBox(frame);
        m_chkLine2->setObjectName(QString::fromUtf8("m_chkLine2"));
        m_chkLine2->setMinimumSize(QSize(0, 20));
        m_chkLine2->setMaximumSize(QSize(130, 25));
        m_chkLine2->setFont(font1);

        m_layGridParas->addWidget(m_chkLine2, 3, 0, 1, 1);

        m_chkLine3 = new QSttCheckBox(frame);
        m_chkLine3->setObjectName(QString::fromUtf8("m_chkLine3"));
        m_chkLine3->setMinimumSize(QSize(0, 20));
        m_chkLine3->setMaximumSize(QSize(130, 25));
        m_chkLine3->setFont(font1);

        m_layGridParas->addWidget(m_chkLine3, 4, 0, 1, 1);

        m_chkStart = new QSttCheckBox(frame);
        m_chkStart->setObjectName(QString::fromUtf8("m_chkStart"));
        m_chkStart->setMinimumSize(QSize(0, 20));
        m_chkStart->setMaximumSize(QSize(130, 25));
        m_chkStart->setFont(font1);

        m_layGridParas->addWidget(m_chkStart, 1, 0, 1, 1);

        m_edtSet_K1 = new QSttLineEdit(frame);
        m_edtSet_K1->setObjectName(QString::fromUtf8("m_edtSet_K1"));
        m_edtSet_K1->setMinimumSize(QSize(0, 20));
        m_edtSet_K1->setMaximumSize(QSize(130, 25));
        m_edtSet_K1->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_K1, 2, 3, 1, 1);

        m_lblTitleLine1 = new QLabel(frame);
        m_lblTitleLine1->setObjectName(QString::fromUtf8("m_lblTitleLine1"));
        m_lblTitleLine1->setMinimumSize(QSize(0, 20));
        m_lblTitleLine1->setMaximumSize(QSize(130, 25));
        m_lblTitleLine1->setFont(font1);
        m_lblTitleLine1->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lblTitleLine1, 2, 1, 1, 1);

        m_chkLineSd = new QSttCheckBox(frame);
        m_chkLineSd->setObjectName(QString::fromUtf8("m_chkLineSd"));
        m_chkLineSd->setMinimumSize(QSize(0, 20));
        m_chkLineSd->setMaximumSize(QSize(130, 25));
        m_chkLineSd->setFont(font1);

        m_layGridParas->addWidget(m_chkLineSd, 5, 0, 1, 1);

        m_lblTitleLineSd = new QLabel(frame);
        m_lblTitleLineSd->setObjectName(QString::fromUtf8("m_lblTitleLineSd"));
        m_lblTitleLineSd->setMinimumSize(QSize(0, 20));
        m_lblTitleLineSd->setMaximumSize(QSize(130, 25));
        m_lblTitleLineSd->setFont(font1);
        m_lblTitleLineSd->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lblTitleLineSd, 5, 1, 1, 1);

        m_lblTitleLine3 = new QLabel(frame);
        m_lblTitleLine3->setObjectName(QString::fromUtf8("m_lblTitleLine3"));
        m_lblTitleLine3->setMinimumSize(QSize(0, 20));
        m_lblTitleLine3->setMaximumSize(QSize(130, 25));
        m_lblTitleLine3->setFont(font1);
        m_lblTitleLine3->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lblTitleLine3, 4, 1, 1, 1);

        m_edtSet_Ip3 = new QSttLineEdit(frame);
        m_edtSet_Ip3->setObjectName(QString::fromUtf8("m_edtSet_Ip3"));
        m_edtSet_Ip3->setMinimumSize(QSize(0, 20));
        m_edtSet_Ip3->setMaximumSize(QSize(130, 25));
        m_edtSet_Ip3->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Ip3, 4, 2, 1, 1);

        m_edtSet_Ip2 = new QSttLineEdit(frame);
        m_edtSet_Ip2->setObjectName(QString::fromUtf8("m_edtSet_Ip2"));
        m_edtSet_Ip2->setMinimumSize(QSize(0, 20));
        m_edtSet_Ip2->setMaximumSize(QSize(130, 25));
        m_edtSet_Ip2->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Ip2, 3, 2, 1, 1);

        m_edtSet_Isd = new QSttLineEdit(frame);
        m_edtSet_Isd->setObjectName(QString::fromUtf8("m_edtSet_Isd"));
        m_edtSet_Isd->setMinimumSize(QSize(0, 20));
        m_edtSet_Isd->setMaximumSize(QSize(130, 25));
        m_edtSet_Isd->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_Isd, 5, 2, 1, 1);

        m_edtSet_K2 = new QSttLineEdit(frame);
        m_edtSet_K2->setObjectName(QString::fromUtf8("m_edtSet_K2"));
        m_edtSet_K2->setMinimumSize(QSize(0, 20));
        m_edtSet_K2->setMaximumSize(QSize(130, 25));
        m_edtSet_K2->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_K2, 3, 3, 1, 1);

        m_edtSet_K3 = new QSttLineEdit(frame);
        m_edtSet_K3->setObjectName(QString::fromUtf8("m_edtSet_K3"));
        m_edtSet_K3->setMinimumSize(QSize(0, 20));
        m_edtSet_K3->setMaximumSize(QSize(130, 25));
        m_edtSet_K3->setFont(font1);

        m_layGridParas->addWidget(m_edtSet_K3, 4, 3, 1, 1);

        m_lbSetting = new QLabel(frame);
        m_lbSetting->setObjectName(QString::fromUtf8("m_lbSetting"));
        m_lbSetting->setMinimumSize(QSize(0, 20));
        m_lbSetting->setMaximumSize(QSize(130, 25));
        m_lbSetting->setFont(font);
        m_lbSetting->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lbSetting, 0, 1, 1, 1);

        m_lbName = new QLabel(frame);
        m_lbName->setObjectName(QString::fromUtf8("m_lbName"));
        m_lbName->setMinimumSize(QSize(0, 20));
        m_lbName->setMaximumSize(QSize(130, 25));
        m_lbName->setFont(font);
        m_lbName->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lbName, 0, 0, 1, 1);

        m_lblTitleLine2 = new QLabel(frame);
        m_lblTitleLine2->setObjectName(QString::fromUtf8("m_lblTitleLine2"));
        m_lblTitleLine2->setMinimumSize(QSize(0, 20));
        m_lblTitleLine2->setMaximumSize(QSize(130, 25));
        m_lblTitleLine2->setFont(font1);
        m_lblTitleLine2->setAlignment(Qt::AlignCenter);

        m_layGridParas->addWidget(m_lblTitleLine2, 3, 1, 1, 1);


        m_layoutVert->addLayout(m_layGridParas);


        verticalLayout_3->addLayout(m_layoutVert);


        verticalLayout_4->addWidget(frame);


        retranslateUi(QCharEditWidget_Diff_Eng);

        m_DiffTypeTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QCharEditWidget_Diff_Eng);
    } // setupUi

    void retranslateUi(QWidget *QCharEditWidget_Diff_Eng)
    {
        QCharEditWidget_Diff_Eng->setWindowTitle(QApplication::translate("QCharEditWidget_Diff_Eng", "QCharEditWidget_Diff_Eng", 0, QApplication::UnicodeUTF8));
        m_editInSet->setText(QString());
        m_radioSetting->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\346\225\264\345\256\232\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_lbSettingMinAxis->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\256\232\345\200\274\346\225\264\345\256\232\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_radioUser->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\350\207\252\345\256\232\344\271\211", 0, QApplication::UnicodeUTF8));
        m_lbInSel->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\237\272\345\207\206\347\224\265\346\265\201\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_lbTypeSel->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\351\200\211\346\213\251\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_cbTypeSel->clear();
        m_cbTypeSel->insertItems(0, QStringList()
         << QApplication::translate("QCharEditWidget_Diff_Eng", "GE Multilin T60", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCharEditWidget_Diff_Eng", "GE Multilin L90", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCharEditWidget_Diff_Eng", "GE Multilin 489", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCharEditWidget_Diff_Eng", "GE Multilin 745", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QCharEditWidget_Diff_Eng", "Siements 7SL86", 0, QApplication::UnicodeUTF8)
        );
        m_lbInSet->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\237\272\345\207\206\347\224\265\346\265\201(\345\205\266\345\256\203):", 0, QApplication::UnicodeUTF8));
        m_labCombinedFeature->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\244\215\345\220\210\347\211\271\346\200\247:", 0, QApplication::UnicodeUTF8));
        m_labZeroSeqElimiType->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\351\233\266\345\272\217\346\266\210\351\231\244\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_DiffTypeTab->setTabText(m_DiffTypeTab->indexOf(tab), QApplication::translate("QCharEditWidget_Diff_Eng", "\346\257\224\347\216\207\345\267\256\345\212\250", 0, QApplication::UnicodeUTF8));
        m_lbIQuick->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\351\200\237\346\226\255\345\200\274():", 0, QApplication::UnicodeUTF8));
        m_lbInSel2->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\237\272\345\207\206\347\224\265\346\265\201\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_lbSettingMinAxis2->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\256\232\345\200\274\346\225\264\345\256\232\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_lbHarmIndex_2->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\350\207\252\345\256\232\344\271\211\350\260\220\346\263\242\346\254\241\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_lbInSet2->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\237\272\345\207\206\347\224\265\346\265\201(\345\205\266\345\256\203):", 0, QApplication::UnicodeUTF8));
        m_lbIDoor->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\351\227\250\346\247\233\345\200\274():", 0, QApplication::UnicodeUTF8));
        m_lbHarmCoef->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\350\260\220\346\263\242\345\210\266\345\212\250\347\263\273\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_lbHarmIndex->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\350\260\220\346\263\242\346\254\241\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_labCombinedFeature2->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\244\215\345\220\210\347\211\271\346\200\247:", 0, QApplication::UnicodeUTF8));
        m_labZeroSeqElimiType2->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\351\233\266\345\272\217\346\266\210\351\231\244\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_DiffTypeTab->setTabText(m_DiffTypeTab->indexOf(tab_2), QApplication::translate("QCharEditWidget_Diff_Eng", "\350\260\220\346\263\242\345\210\266\345\212\250", 0, QApplication::UnicodeUTF8));
        m_lblTitleStart->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\351\227\250\346\247\233\345\200\274", 0, QApplication::UnicodeUTF8));
        m_edtSet_Istart->setText(QString());
        m_chkLine1->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\347\254\254\344\270\200\346\256\265", 0, QApplication::UnicodeUTF8));
        m_lblTitleCurr->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\347\224\265\346\265\201\357\274\210Ie\357\274\211", 0, QApplication::UnicodeUTF8));
        m_lblTitleK->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\346\226\234\347\216\207", 0, QApplication::UnicodeUTF8));
        m_chkLine2->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\347\254\254\344\272\214\346\256\265", 0, QApplication::UnicodeUTF8));
        m_chkLine3->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\347\254\254\344\270\211\346\256\265", 0, QApplication::UnicodeUTF8));
        m_chkStart->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\220\257\345\212\250\347\224\265\346\265\201", 0, QApplication::UnicodeUTF8));
        m_lblTitleLine1->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\346\213\220\347\202\2711", 0, QApplication::UnicodeUTF8));
        m_chkLineSd->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\351\200\237\346\226\255", 0, QApplication::UnicodeUTF8));
        m_lblTitleLineSd->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\351\200\237\346\226\255\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_lblTitleLine3->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\346\213\220\347\202\2713", 0, QApplication::UnicodeUTF8));
        m_lbSetting->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_lbName->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_lblTitleLine2->setText(QApplication::translate("QCharEditWidget_Diff_Eng", "\346\213\220\347\202\2712", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCharEditWidget_Diff_Eng: public Ui_QCharEditWidget_Diff_Eng {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAREDITWIDGET_DIFF_ENG_H
