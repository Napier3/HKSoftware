/********************************************************************************
** Form generated from reading UI file 'SttMacroParaEditViewGradient.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTMACROPARAEDITVIEWGRADIENT_H
#define UI_STTMACROPARAEDITVIEWGRADIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../../../Module/UI/Module/ScrollCtrl/ScrollComboBox.h"
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttGroupBox.h"
#include "../Controls/SttTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_QSttMacroParaEditViewGradient
{
public:
    QGridLayout *gridLayout_12;
    QSttTabWidget *m_tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSttGroupBox *m_gpChangeSet;
    QGridLayout *gridLayout_6;
    QLabel *m_labFinish;
    QSettingLineEdit *m_editInit;
    QLabel *m_labInit;
    QLabel *m_labVar;
    QScrollComboBox *m_cbbVarType;
    QLabel *m_labVarType;
    QScrollComboBox *m_cbbVar;
    QSettingLineEdit *m_editFinish;
    QSttGroupBox *m_gpVarSet;
    QGridLayout *gridLayout_3;
    QLabel *m_labFinish2;
    QLabel *m_labVarType2;
    QScrollComboBox *m_cbbVar2;
    QScrollComboBox *m_cbbVarType2;
    QLabel *m_labVar2;
    QSettingLineEdit *m_editInit2;
    QSettingLineEdit *m_editFinish2;
    QLabel *m_labInit2;
    QSttGroupBox *m_gpMannual;
    QGridLayout *gridLayout_2;
    QSttCheckBox *m_cbBefore;
    QSettingLineEdit *m_editTimeBeforeChange;
    QLabel *m_labTimeBeforeFail;
    QSpacerItem *verticalSpacer;
    QLabel *m_labTimeBeforeChange;
    QSettingLineEdit *m_editTimeBeforeFail;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout;
    QScrollComboBox *m_cbbType;
    QSettingLineEdit *m_editTime;
    QLabel *m_labType;
    QLabel *m_labTime;
    QSpacerItem *verticalSpacer_4;
    QFrame *frame_2;
    QGridLayout *gridLayout_7;
    QLabel *m_labStep;
    QLabel *m_labDirection;
    QSettingLineEdit *m_editStep;
    QScrollComboBox *m_cbbDirection;
    QSpacerItem *verticalSpacer_6;
    QFrame *frame_3;
    QGridLayout *gridLayout_8;
    QSettingLineEdit *m_editStep2;
    QLabel *m_labStep2;
    QSpacerItem *verticalSpacer_3;
    QSttGroupBox *m_gpBin;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout_4;
    QSttCheckBox *m_cbBinI;
    QSttCheckBox *m_cbBinD;
    QSttCheckBox *m_cbBinB;
    QSttCheckBox *m_cbBinJ;
    QSttCheckBox *m_cbBinF;
    QRadioButton *m_rbOr;
    QSttCheckBox *m_cbBinA;
    QRadioButton *m_rbAnd;
    QSttCheckBox *m_cbBinH;
    QSttCheckBox *m_cbBinG;
    QSttCheckBox *m_cbBinC;
    QSttCheckBox *m_cbBinE;
    QGridLayout *gridLayout_5;
    QCheckBox *ck_Out8_Fault;
    QCheckBox *ck_Out7_Fault;
    QCheckBox *ck_Out6_Fault;
    QCheckBox *ck_Out5_Fault;
    QCheckBox *ck_Out3_Fault;
    QCheckBox *ck_Out4_Fault;
    QCheckBox *ck_Out1;
    QCheckBox *ck_Out4;
    QCheckBox *ck_Out7;
    QCheckBox *ck_Out6;
    QCheckBox *ck_Out5;
    QCheckBox *ck_Out3;
    QCheckBox *ck_Out2;
    QCheckBox *ck_Out1_Fault;
    QCheckBox *ck_Out2_Fault;
    QLabel *label_Fault;
    QCheckBox *ck_Out8;
    QLabel *label_PreFault;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnSettingValue;
    QPushButton *m_btnEstimate;

    void setupUi(QWidget *QSttMacroParaEditViewGradient)
    {
        if (QSttMacroParaEditViewGradient->objectName().isEmpty())
            QSttMacroParaEditViewGradient->setObjectName(QString::fromUtf8("QSttMacroParaEditViewGradient"));
        QSttMacroParaEditViewGradient->resize(1699, 1149);
        QSttMacroParaEditViewGradient->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(18);
        QSttMacroParaEditViewGradient->setFont(font);
        gridLayout_12 = new QGridLayout(QSttMacroParaEditViewGradient);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        m_tabWidget = new QSttTabWidget(QSttMacroParaEditViewGradient);
        m_tabWidget->setObjectName(QString::fromUtf8("m_tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_tabWidget->sizePolicy().hasHeightForWidth());
        m_tabWidget->setSizePolicy(sizePolicy);
        m_tabWidget->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setPointSize(20);
        m_tabWidget->setFont(font1);
        m_tabWidget->setFocusPolicy(Qt::StrongFocus);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_gpChangeSet = new QSttGroupBox(tab);
        m_gpChangeSet->setObjectName(QString::fromUtf8("m_gpChangeSet"));
        sizePolicy.setHeightForWidth(m_gpChangeSet->sizePolicy().hasHeightForWidth());
        m_gpChangeSet->setSizePolicy(sizePolicy);
        m_gpChangeSet->setMinimumSize(QSize(0, 0));
        m_gpChangeSet->setMaximumSize(QSize(320, 230));
        gridLayout_6 = new QGridLayout(m_gpChangeSet);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(-1, -1, -1, 0);
        m_labFinish = new QLabel(m_gpChangeSet);
        m_labFinish->setObjectName(QString::fromUtf8("m_labFinish"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_labFinish->sizePolicy().hasHeightForWidth());
        m_labFinish->setSizePolicy(sizePolicy1);
        m_labFinish->setMaximumSize(QSize(16777215, 23));

        gridLayout_6->addWidget(m_labFinish, 7, 0, 1, 1);

        m_editInit = new QSettingLineEdit(m_gpChangeSet);
        m_editInit->setObjectName(QString::fromUtf8("m_editInit"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_editInit->sizePolicy().hasHeightForWidth());
        m_editInit->setSizePolicy(sizePolicy2);
        m_editInit->setMinimumSize(QSize(120, 0));
        m_editInit->setMaximumSize(QSize(120, 23));

        gridLayout_6->addWidget(m_editInit, 4, 1, 1, 1);

        m_labInit = new QLabel(m_gpChangeSet);
        m_labInit->setObjectName(QString::fromUtf8("m_labInit"));
        sizePolicy1.setHeightForWidth(m_labInit->sizePolicy().hasHeightForWidth());
        m_labInit->setSizePolicy(sizePolicy1);
        m_labInit->setMaximumSize(QSize(16777215, 23));

        gridLayout_6->addWidget(m_labInit, 4, 0, 1, 1);

        m_labVar = new QLabel(m_gpChangeSet);
        m_labVar->setObjectName(QString::fromUtf8("m_labVar"));
        sizePolicy1.setHeightForWidth(m_labVar->sizePolicy().hasHeightForWidth());
        m_labVar->setSizePolicy(sizePolicy1);
        m_labVar->setMaximumSize(QSize(16777215, 23));

        gridLayout_6->addWidget(m_labVar, 2, 0, 1, 1);

        m_cbbVarType = new QScrollComboBox(m_gpChangeSet);
        m_cbbVarType->setObjectName(QString::fromUtf8("m_cbbVarType"));
        sizePolicy2.setHeightForWidth(m_cbbVarType->sizePolicy().hasHeightForWidth());
        m_cbbVarType->setSizePolicy(sizePolicy2);
        m_cbbVarType->setMinimumSize(QSize(120, 0));
        m_cbbVarType->setMaximumSize(QSize(120, 23));
        m_cbbVarType->setFont(font1);

        gridLayout_6->addWidget(m_cbbVarType, 3, 1, 1, 1);

        m_labVarType = new QLabel(m_gpChangeSet);
        m_labVarType->setObjectName(QString::fromUtf8("m_labVarType"));
        sizePolicy1.setHeightForWidth(m_labVarType->sizePolicy().hasHeightForWidth());
        m_labVarType->setSizePolicy(sizePolicy1);
        m_labVarType->setMaximumSize(QSize(16777215, 23));

        gridLayout_6->addWidget(m_labVarType, 3, 0, 1, 1);

        m_cbbVar = new QScrollComboBox(m_gpChangeSet);
        m_cbbVar->setObjectName(QString::fromUtf8("m_cbbVar"));
        sizePolicy2.setHeightForWidth(m_cbbVar->sizePolicy().hasHeightForWidth());
        m_cbbVar->setSizePolicy(sizePolicy2);
        m_cbbVar->setMinimumSize(QSize(120, 0));
        m_cbbVar->setMaximumSize(QSize(120, 23));
        m_cbbVar->setMaxVisibleItems(5);

        gridLayout_6->addWidget(m_cbbVar, 2, 1, 1, 1);

        m_editFinish = new QSettingLineEdit(m_gpChangeSet);
        m_editFinish->setObjectName(QString::fromUtf8("m_editFinish"));
        sizePolicy2.setHeightForWidth(m_editFinish->sizePolicy().hasHeightForWidth());
        m_editFinish->setSizePolicy(sizePolicy2);
        m_editFinish->setMinimumSize(QSize(120, 0));
        m_editFinish->setMaximumSize(QSize(120, 23));

        gridLayout_6->addWidget(m_editFinish, 7, 1, 1, 1);


        horizontalLayout->addWidget(m_gpChangeSet);

        m_gpVarSet = new QSttGroupBox(tab);
        m_gpVarSet->setObjectName(QString::fromUtf8("m_gpVarSet"));
        sizePolicy.setHeightForWidth(m_gpVarSet->sizePolicy().hasHeightForWidth());
        m_gpVarSet->setSizePolicy(sizePolicy);
        m_gpVarSet->setMinimumSize(QSize(0, 0));
        m_gpVarSet->setMaximumSize(QSize(360, 230));
        gridLayout_3 = new QGridLayout(m_gpVarSet);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, -1, -1, 0);
        m_labFinish2 = new QLabel(m_gpVarSet);
        m_labFinish2->setObjectName(QString::fromUtf8("m_labFinish2"));
        sizePolicy1.setHeightForWidth(m_labFinish2->sizePolicy().hasHeightForWidth());
        m_labFinish2->setSizePolicy(sizePolicy1);
        m_labFinish2->setMaximumSize(QSize(16777215, 23));

        gridLayout_3->addWidget(m_labFinish2, 6, 1, 1, 1);

        m_labVarType2 = new QLabel(m_gpVarSet);
        m_labVarType2->setObjectName(QString::fromUtf8("m_labVarType2"));
        sizePolicy1.setHeightForWidth(m_labVarType2->sizePolicy().hasHeightForWidth());
        m_labVarType2->setSizePolicy(sizePolicy1);
        m_labVarType2->setMaximumSize(QSize(16777215, 23));

        gridLayout_3->addWidget(m_labVarType2, 1, 1, 1, 1);

        m_cbbVar2 = new QScrollComboBox(m_gpVarSet);
        m_cbbVar2->setObjectName(QString::fromUtf8("m_cbbVar2"));
        sizePolicy2.setHeightForWidth(m_cbbVar2->sizePolicy().hasHeightForWidth());
        m_cbbVar2->setSizePolicy(sizePolicy2);
        m_cbbVar2->setMinimumSize(QSize(120, 0));
        m_cbbVar2->setMaximumSize(QSize(120, 23));
        m_cbbVar2->setMaxVisibleItems(5);

        gridLayout_3->addWidget(m_cbbVar2, 0, 2, 1, 1);

        m_cbbVarType2 = new QScrollComboBox(m_gpVarSet);
        m_cbbVarType2->setObjectName(QString::fromUtf8("m_cbbVarType2"));
        sizePolicy2.setHeightForWidth(m_cbbVarType2->sizePolicy().hasHeightForWidth());
        m_cbbVarType2->setSizePolicy(sizePolicy2);
        m_cbbVarType2->setMinimumSize(QSize(120, 0));
        m_cbbVarType2->setMaximumSize(QSize(120, 23));
        m_cbbVarType2->setFont(font1);

        gridLayout_3->addWidget(m_cbbVarType2, 1, 2, 1, 1);

        m_labVar2 = new QLabel(m_gpVarSet);
        m_labVar2->setObjectName(QString::fromUtf8("m_labVar2"));
        sizePolicy1.setHeightForWidth(m_labVar2->sizePolicy().hasHeightForWidth());
        m_labVar2->setSizePolicy(sizePolicy1);
        m_labVar2->setMaximumSize(QSize(16777215, 23));

        gridLayout_3->addWidget(m_labVar2, 0, 1, 1, 1);

        m_editInit2 = new QSettingLineEdit(m_gpVarSet);
        m_editInit2->setObjectName(QString::fromUtf8("m_editInit2"));
        sizePolicy2.setHeightForWidth(m_editInit2->sizePolicy().hasHeightForWidth());
        m_editInit2->setSizePolicy(sizePolicy2);
        m_editInit2->setMinimumSize(QSize(120, 0));
        m_editInit2->setMaximumSize(QSize(120, 23));

        gridLayout_3->addWidget(m_editInit2, 3, 2, 1, 1);

        m_editFinish2 = new QSettingLineEdit(m_gpVarSet);
        m_editFinish2->setObjectName(QString::fromUtf8("m_editFinish2"));
        sizePolicy2.setHeightForWidth(m_editFinish2->sizePolicy().hasHeightForWidth());
        m_editFinish2->setSizePolicy(sizePolicy2);
        m_editFinish2->setMinimumSize(QSize(120, 0));
        m_editFinish2->setMaximumSize(QSize(120, 23));

        gridLayout_3->addWidget(m_editFinish2, 6, 2, 1, 1);

        m_labInit2 = new QLabel(m_gpVarSet);
        m_labInit2->setObjectName(QString::fromUtf8("m_labInit2"));
        sizePolicy1.setHeightForWidth(m_labInit2->sizePolicy().hasHeightForWidth());
        m_labInit2->setSizePolicy(sizePolicy1);
        m_labInit2->setMaximumSize(QSize(16777215, 23));

        gridLayout_3->addWidget(m_labInit2, 3, 1, 1, 1);


        horizontalLayout->addWidget(m_gpVarSet);

        m_gpMannual = new QSttGroupBox(tab);
        m_gpMannual->setObjectName(QString::fromUtf8("m_gpMannual"));
        m_gpMannual->setMinimumSize(QSize(0, 0));
        m_gpMannual->setMaximumSize(QSize(370, 230));
        gridLayout_2 = new QGridLayout(m_gpMannual);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_cbBefore = new QSttCheckBox(m_gpMannual);
        m_cbBefore->setObjectName(QString::fromUtf8("m_cbBefore"));

        gridLayout_2->addWidget(m_cbBefore, 2, 1, 1, 1);

        m_editTimeBeforeChange = new QSettingLineEdit(m_gpMannual);
        m_editTimeBeforeChange->setObjectName(QString::fromUtf8("m_editTimeBeforeChange"));
        sizePolicy2.setHeightForWidth(m_editTimeBeforeChange->sizePolicy().hasHeightForWidth());
        m_editTimeBeforeChange->setSizePolicy(sizePolicy2);
        m_editTimeBeforeChange->setMinimumSize(QSize(120, 0));
        m_editTimeBeforeChange->setMaximumSize(QSize(120, 23));

        gridLayout_2->addWidget(m_editTimeBeforeChange, 0, 1, 1, 1);

        m_labTimeBeforeFail = new QLabel(m_gpMannual);
        m_labTimeBeforeFail->setObjectName(QString::fromUtf8("m_labTimeBeforeFail"));
        m_labTimeBeforeFail->setMaximumSize(QSize(16777215, 23));

        gridLayout_2->addWidget(m_labTimeBeforeFail, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);

        m_labTimeBeforeChange = new QLabel(m_gpMannual);
        m_labTimeBeforeChange->setObjectName(QString::fromUtf8("m_labTimeBeforeChange"));
        m_labTimeBeforeChange->setMaximumSize(QSize(16777215, 23));

        gridLayout_2->addWidget(m_labTimeBeforeChange, 0, 0, 1, 1);

        m_editTimeBeforeFail = new QSettingLineEdit(m_gpMannual);
        m_editTimeBeforeFail->setObjectName(QString::fromUtf8("m_editTimeBeforeFail"));
        sizePolicy2.setHeightForWidth(m_editTimeBeforeFail->sizePolicy().hasHeightForWidth());
        m_editTimeBeforeFail->setSizePolicy(sizePolicy2);
        m_editTimeBeforeFail->setMinimumSize(QSize(120, 0));
        m_editTimeBeforeFail->setMaximumSize(QSize(120, 23));

        gridLayout_2->addWidget(m_editTimeBeforeFail, 1, 1, 1, 1);


        horizontalLayout->addWidget(m_gpMannual);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 3);
        horizontalLayout->setStretch(2, 4);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 0));
        frame->setMaximumSize(QSize(320, 100));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 0);
        m_cbbType = new QScrollComboBox(frame);
        m_cbbType->setObjectName(QString::fromUtf8("m_cbbType"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_cbbType->sizePolicy().hasHeightForWidth());
        m_cbbType->setSizePolicy(sizePolicy3);
        m_cbbType->setMinimumSize(QSize(120, 0));
        m_cbbType->setMaximumSize(QSize(120, 23));

        gridLayout->addWidget(m_cbbType, 1, 1, 1, 1);

        m_editTime = new QSettingLineEdit(frame);
        m_editTime->setObjectName(QString::fromUtf8("m_editTime"));
        sizePolicy3.setHeightForWidth(m_editTime->sizePolicy().hasHeightForWidth());
        m_editTime->setSizePolicy(sizePolicy3);
        m_editTime->setMinimumSize(QSize(120, 0));
        m_editTime->setMaximumSize(QSize(120, 23));

        gridLayout->addWidget(m_editTime, 0, 1, 1, 1);

        m_labType = new QLabel(frame);
        m_labType->setObjectName(QString::fromUtf8("m_labType"));
        sizePolicy1.setHeightForWidth(m_labType->sizePolicy().hasHeightForWidth());
        m_labType->setSizePolicy(sizePolicy1);
        m_labType->setMinimumSize(QSize(0, 0));
        m_labType->setMaximumSize(QSize(16777215, 23));

        gridLayout->addWidget(m_labType, 1, 0, 1, 1);

        m_labTime = new QLabel(frame);
        m_labTime->setObjectName(QString::fromUtf8("m_labTime"));
        sizePolicy1.setHeightForWidth(m_labTime->sizePolicy().hasHeightForWidth());
        m_labTime->setSizePolicy(sizePolicy1);
        m_labTime->setMinimumSize(QSize(0, 0));
        m_labTime->setMaximumSize(QSize(16777215, 23));

        gridLayout->addWidget(m_labTime, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 2, 0, 1, 1);


        horizontalLayout_3->addWidget(frame);

        frame_2 = new QFrame(tab);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setMaximumSize(QSize(360, 100));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_7 = new QGridLayout(frame_2);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(-1, -1, -1, 0);
        m_labStep = new QLabel(frame_2);
        m_labStep->setObjectName(QString::fromUtf8("m_labStep"));
        sizePolicy1.setHeightForWidth(m_labStep->sizePolicy().hasHeightForWidth());
        m_labStep->setSizePolicy(sizePolicy1);
        m_labStep->setMinimumSize(QSize(0, 0));
        m_labStep->setMaximumSize(QSize(16777215, 23));

        gridLayout_7->addWidget(m_labStep, 0, 0, 1, 1);

        m_labDirection = new QLabel(frame_2);
        m_labDirection->setObjectName(QString::fromUtf8("m_labDirection"));
        sizePolicy1.setHeightForWidth(m_labDirection->sizePolicy().hasHeightForWidth());
        m_labDirection->setSizePolicy(sizePolicy1);
        m_labDirection->setMinimumSize(QSize(0, 0));
        m_labDirection->setMaximumSize(QSize(16777215, 23));

        gridLayout_7->addWidget(m_labDirection, 1, 0, 1, 1);

        m_editStep = new QSettingLineEdit(frame_2);
        m_editStep->setObjectName(QString::fromUtf8("m_editStep"));
        sizePolicy3.setHeightForWidth(m_editStep->sizePolicy().hasHeightForWidth());
        m_editStep->setSizePolicy(sizePolicy3);
        m_editStep->setMinimumSize(QSize(120, 0));
        m_editStep->setMaximumSize(QSize(120, 23));

        gridLayout_7->addWidget(m_editStep, 0, 1, 1, 1);

        m_cbbDirection = new QScrollComboBox(frame_2);
        m_cbbDirection->setObjectName(QString::fromUtf8("m_cbbDirection"));
        sizePolicy3.setHeightForWidth(m_cbbDirection->sizePolicy().hasHeightForWidth());
        m_cbbDirection->setSizePolicy(sizePolicy3);
        m_cbbDirection->setMinimumSize(QSize(120, 0));
        m_cbbDirection->setMaximumSize(QSize(120, 23));

        gridLayout_7->addWidget(m_cbbDirection, 1, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_6, 2, 0, 1, 1);


        horizontalLayout_3->addWidget(frame_2);

        frame_3 = new QFrame(tab);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(0, 0));
        frame_3->setMaximumSize(QSize(370, 100));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_8 = new QGridLayout(frame_3);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(-1, -1, -1, 0);
        m_editStep2 = new QSettingLineEdit(frame_3);
        m_editStep2->setObjectName(QString::fromUtf8("m_editStep2"));
        m_editStep2->setEnabled(false);
        sizePolicy3.setHeightForWidth(m_editStep2->sizePolicy().hasHeightForWidth());
        m_editStep2->setSizePolicy(sizePolicy3);
        m_editStep2->setMinimumSize(QSize(120, 0));
        m_editStep2->setMaximumSize(QSize(120, 23));

        gridLayout_8->addWidget(m_editStep2, 0, 1, 1, 1);

        m_labStep2 = new QLabel(frame_3);
        m_labStep2->setObjectName(QString::fromUtf8("m_labStep2"));
        sizePolicy.setHeightForWidth(m_labStep2->sizePolicy().hasHeightForWidth());
        m_labStep2->setSizePolicy(sizePolicy);
        m_labStep2->setMinimumSize(QSize(0, 0));
        m_labStep2->setMaximumSize(QSize(16777215, 23));

        gridLayout_8->addWidget(m_labStep2, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer_3, 1, 0, 1, 1);

        gridLayout_8->setRowStretch(0, 1);

        horizontalLayout_3->addWidget(frame_3);

        horizontalLayout_3->setStretch(0, 3);
        horizontalLayout_3->setStretch(1, 3);
        horizontalLayout_3->setStretch(2, 4);

        verticalLayout->addLayout(horizontalLayout_3);

        m_gpBin = new QSttGroupBox(tab);
        m_gpBin->setObjectName(QString::fromUtf8("m_gpBin"));
        m_gpBin->setMinimumSize(QSize(0, 70));
        m_gpBin->setMaximumSize(QSize(16777215, 110));
        horizontalLayout_4 = new QHBoxLayout(m_gpBin);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(-1, -1, 9, 9);
        m_cbBinI = new QSttCheckBox(m_gpBin);
        m_cbBinI->setObjectName(QString::fromUtf8("m_cbBinI"));
        QFont font2;
        font2.setPointSize(16);
        m_cbBinI->setFont(font2);
        m_cbBinI->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinI, 0, 8, 1, 1);

        m_cbBinD = new QSttCheckBox(m_gpBin);
        m_cbBinD->setObjectName(QString::fromUtf8("m_cbBinD"));
        m_cbBinD->setFont(font2);
        m_cbBinD->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinD, 0, 3, 1, 1);

        m_cbBinB = new QSttCheckBox(m_gpBin);
        m_cbBinB->setObjectName(QString::fromUtf8("m_cbBinB"));
        m_cbBinB->setFont(font2);
        m_cbBinB->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinB, 0, 1, 1, 1);

        m_cbBinJ = new QSttCheckBox(m_gpBin);
        m_cbBinJ->setObjectName(QString::fromUtf8("m_cbBinJ"));
        m_cbBinJ->setFont(font2);
        m_cbBinJ->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinJ, 0, 9, 1, 1);

        m_cbBinF = new QSttCheckBox(m_gpBin);
        m_cbBinF->setObjectName(QString::fromUtf8("m_cbBinF"));
        m_cbBinF->setFont(font2);
        m_cbBinF->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinF, 0, 5, 1, 1);

        m_rbOr = new QRadioButton(m_gpBin);
        m_rbOr->setObjectName(QString::fromUtf8("m_rbOr"));

        gridLayout_4->addWidget(m_rbOr, 0, 10, 1, 1);

        m_cbBinA = new QSttCheckBox(m_gpBin);
        m_cbBinA->setObjectName(QString::fromUtf8("m_cbBinA"));
        m_cbBinA->setFont(font2);
        m_cbBinA->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinA, 0, 0, 1, 1);

        m_rbAnd = new QRadioButton(m_gpBin);
        m_rbAnd->setObjectName(QString::fromUtf8("m_rbAnd"));
        m_rbAnd->setChecked(true);

        gridLayout_4->addWidget(m_rbAnd, 0, 11, 1, 1);

        m_cbBinH = new QSttCheckBox(m_gpBin);
        m_cbBinH->setObjectName(QString::fromUtf8("m_cbBinH"));
        m_cbBinH->setFont(font2);
        m_cbBinH->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinH, 0, 7, 1, 1);

        m_cbBinG = new QSttCheckBox(m_gpBin);
        m_cbBinG->setObjectName(QString::fromUtf8("m_cbBinG"));
        m_cbBinG->setFont(font2);
        m_cbBinG->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinG, 0, 6, 1, 1);

        m_cbBinC = new QSttCheckBox(m_gpBin);
        m_cbBinC->setObjectName(QString::fromUtf8("m_cbBinC"));
        m_cbBinC->setFont(font2);
        m_cbBinC->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinC, 0, 2, 1, 1);

        m_cbBinE = new QSttCheckBox(m_gpBin);
        m_cbBinE->setObjectName(QString::fromUtf8("m_cbBinE"));
        m_cbBinE->setFont(font2);
        m_cbBinE->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(m_cbBinE, 0, 4, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_4);


        verticalLayout->addWidget(m_gpBin);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        ck_Out8_Fault = new QCheckBox(tab);
        ck_Out8_Fault->setObjectName(QString::fromUtf8("ck_Out8_Fault"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(ck_Out8_Fault->sizePolicy().hasHeightForWidth());
        ck_Out8_Fault->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out8_Fault, 2, 8, 1, 1);

        ck_Out7_Fault = new QCheckBox(tab);
        ck_Out7_Fault->setObjectName(QString::fromUtf8("ck_Out7_Fault"));
        sizePolicy4.setHeightForWidth(ck_Out7_Fault->sizePolicy().hasHeightForWidth());
        ck_Out7_Fault->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out7_Fault, 2, 7, 1, 1);

        ck_Out6_Fault = new QCheckBox(tab);
        ck_Out6_Fault->setObjectName(QString::fromUtf8("ck_Out6_Fault"));
        sizePolicy4.setHeightForWidth(ck_Out6_Fault->sizePolicy().hasHeightForWidth());
        ck_Out6_Fault->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out6_Fault, 2, 6, 1, 1);

        ck_Out5_Fault = new QCheckBox(tab);
        ck_Out5_Fault->setObjectName(QString::fromUtf8("ck_Out5_Fault"));
        sizePolicy4.setHeightForWidth(ck_Out5_Fault->sizePolicy().hasHeightForWidth());
        ck_Out5_Fault->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out5_Fault, 2, 5, 1, 1);

        ck_Out3_Fault = new QCheckBox(tab);
        ck_Out3_Fault->setObjectName(QString::fromUtf8("ck_Out3_Fault"));
        sizePolicy4.setHeightForWidth(ck_Out3_Fault->sizePolicy().hasHeightForWidth());
        ck_Out3_Fault->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out3_Fault, 2, 3, 1, 1);

        ck_Out4_Fault = new QCheckBox(tab);
        ck_Out4_Fault->setObjectName(QString::fromUtf8("ck_Out4_Fault"));
        sizePolicy4.setHeightForWidth(ck_Out4_Fault->sizePolicy().hasHeightForWidth());
        ck_Out4_Fault->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out4_Fault, 2, 4, 1, 1);

        ck_Out1 = new QCheckBox(tab);
        ck_Out1->setObjectName(QString::fromUtf8("ck_Out1"));
        sizePolicy4.setHeightForWidth(ck_Out1->sizePolicy().hasHeightForWidth());
        ck_Out1->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out1, 0, 1, 1, 1);

        ck_Out4 = new QCheckBox(tab);
        ck_Out4->setObjectName(QString::fromUtf8("ck_Out4"));
        sizePolicy4.setHeightForWidth(ck_Out4->sizePolicy().hasHeightForWidth());
        ck_Out4->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out4, 0, 4, 1, 1);

        ck_Out7 = new QCheckBox(tab);
        ck_Out7->setObjectName(QString::fromUtf8("ck_Out7"));
        sizePolicy4.setHeightForWidth(ck_Out7->sizePolicy().hasHeightForWidth());
        ck_Out7->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out7, 0, 7, 1, 1);

        ck_Out6 = new QCheckBox(tab);
        ck_Out6->setObjectName(QString::fromUtf8("ck_Out6"));
        sizePolicy4.setHeightForWidth(ck_Out6->sizePolicy().hasHeightForWidth());
        ck_Out6->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out6, 0, 6, 1, 1);

        ck_Out5 = new QCheckBox(tab);
        ck_Out5->setObjectName(QString::fromUtf8("ck_Out5"));
        sizePolicy4.setHeightForWidth(ck_Out5->sizePolicy().hasHeightForWidth());
        ck_Out5->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out5, 0, 5, 1, 1);

        ck_Out3 = new QCheckBox(tab);
        ck_Out3->setObjectName(QString::fromUtf8("ck_Out3"));
        sizePolicy4.setHeightForWidth(ck_Out3->sizePolicy().hasHeightForWidth());
        ck_Out3->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out3, 0, 3, 1, 1);

        ck_Out2 = new QCheckBox(tab);
        ck_Out2->setObjectName(QString::fromUtf8("ck_Out2"));
        sizePolicy4.setHeightForWidth(ck_Out2->sizePolicy().hasHeightForWidth());
        ck_Out2->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out2, 0, 2, 1, 1);

        ck_Out1_Fault = new QCheckBox(tab);
        ck_Out1_Fault->setObjectName(QString::fromUtf8("ck_Out1_Fault"));
        sizePolicy4.setHeightForWidth(ck_Out1_Fault->sizePolicy().hasHeightForWidth());
        ck_Out1_Fault->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out1_Fault, 2, 1, 1, 1);

        ck_Out2_Fault = new QCheckBox(tab);
        ck_Out2_Fault->setObjectName(QString::fromUtf8("ck_Out2_Fault"));
        sizePolicy4.setHeightForWidth(ck_Out2_Fault->sizePolicy().hasHeightForWidth());
        ck_Out2_Fault->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out2_Fault, 2, 2, 1, 1);

        label_Fault = new QLabel(tab);
        label_Fault->setObjectName(QString::fromUtf8("label_Fault"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_Fault->sizePolicy().hasHeightForWidth());
        label_Fault->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_Fault, 2, 0, 1, 1);

        ck_Out8 = new QCheckBox(tab);
        ck_Out8->setObjectName(QString::fromUtf8("ck_Out8"));
        sizePolicy4.setHeightForWidth(ck_Out8->sizePolicy().hasHeightForWidth());
        ck_Out8->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(ck_Out8, 0, 8, 1, 1);

        label_PreFault = new QLabel(tab);
        label_PreFault->setObjectName(QString::fromUtf8("label_PreFault"));
        sizePolicy5.setHeightForWidth(label_PreFault->sizePolicy().hasHeightForWidth());
        label_PreFault->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_PreFault, 0, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_5->addItem(verticalSpacer_5, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_btnSettingValue = new QPushButton(tab);
        m_btnSettingValue->setObjectName(QString::fromUtf8("m_btnSettingValue"));

        horizontalLayout_2->addWidget(m_btnSettingValue);

        m_btnEstimate = new QPushButton(tab);
        m_btnEstimate->setObjectName(QString::fromUtf8("m_btnEstimate"));

        horizontalLayout_2->addWidget(m_btnEstimate);


        verticalLayout->addLayout(horizontalLayout_2);

        m_tabWidget->addTab(tab, QString());
        m_gpBin->raise();

        gridLayout_12->addWidget(m_tabWidget, 0, 0, 1, 1);


        retranslateUi(QSttMacroParaEditViewGradient);

        m_tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QSttMacroParaEditViewGradient);
    } // setupUi

    void retranslateUi(QWidget *QSttMacroParaEditViewGradient)
    {
        QSttMacroParaEditViewGradient->setWindowTitle(QApplication::translate("QSttMacroParaEditViewGradient", "QSttMacroParaEditViewGradient", 0, QApplication::UnicodeUTF8));
        m_gpChangeSet->setTitle(QApplication::translate("QSttMacroParaEditViewGradient", "\347\254\254\344\270\200\345\217\230\351\207\217", 0, QApplication::UnicodeUTF8));
        m_labFinish->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\217\230\345\214\226\347\273\210\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labInit->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\217\230\345\214\226\345\247\213\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labVar->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\217\230\351\207\217\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_labVarType->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\217\230\351\207\217\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_gpVarSet->setTitle(QApplication::translate("QSttMacroParaEditViewGradient", "\347\254\254\344\272\214\345\217\230\351\207\217", 0, QApplication::UnicodeUTF8));
        m_labFinish2->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\217\230\345\214\226\347\273\210\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_labVarType2->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\217\230\351\207\217\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labVar2->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\217\230\351\207\217\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_labInit2->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\217\230\345\214\226\345\247\213\345\200\274(A):", 0, QApplication::UnicodeUTF8));
        m_gpMannual->setTitle(QApplication::translate("QSttMacroParaEditViewGradient", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_cbBefore->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\350\204\211\345\206\262", 0, QApplication::UnicodeUTF8));
        m_labTimeBeforeFail->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labTimeBeforeChange->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\217\230\345\214\226\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labType->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labTime->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\346\225\205\351\232\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labStep->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\347\254\254\344\270\200\345\217\230\351\207\217\346\255\245\351\225\277(A):", 0, QApplication::UnicodeUTF8));
        m_labDirection->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\351\200\222\345\217\230\346\226\271\345\220\221:", 0, QApplication::UnicodeUTF8));
        m_labStep2->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\347\254\254\344\272\214\345\217\230\351\207\217\346\255\245\351\225\277(A):", 0, QApplication::UnicodeUTF8));
        m_gpBin->setTitle(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_cbBinI->setText(QApplication::translate("QSttMacroParaEditViewGradient", "I", 0, QApplication::UnicodeUTF8));
        m_cbBinD->setText(QApplication::translate("QSttMacroParaEditViewGradient", "D", 0, QApplication::UnicodeUTF8));
        m_cbBinB->setText(QApplication::translate("QSttMacroParaEditViewGradient", "B", 0, QApplication::UnicodeUTF8));
        m_cbBinJ->setText(QApplication::translate("QSttMacroParaEditViewGradient", "J", 0, QApplication::UnicodeUTF8));
        m_cbBinF->setText(QApplication::translate("QSttMacroParaEditViewGradient", "F", 0, QApplication::UnicodeUTF8));
        m_rbOr->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\351\200\273\350\276\221\346\210\226", 0, QApplication::UnicodeUTF8));
        m_cbBinA->setText(QApplication::translate("QSttMacroParaEditViewGradient", "A", 0, QApplication::UnicodeUTF8));
        m_rbAnd->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\351\200\273\350\276\221\344\270\216", 0, QApplication::UnicodeUTF8));
        m_cbBinH->setText(QApplication::translate("QSttMacroParaEditViewGradient", "H", 0, QApplication::UnicodeUTF8));
        m_cbBinG->setText(QApplication::translate("QSttMacroParaEditViewGradient", "G", 0, QApplication::UnicodeUTF8));
        m_cbBinC->setText(QApplication::translate("QSttMacroParaEditViewGradient", "C", 0, QApplication::UnicodeUTF8));
        m_cbBinE->setText(QApplication::translate("QSttMacroParaEditViewGradient", "E", 0, QApplication::UnicodeUTF8));
        ck_Out8_Fault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2728", 0, QApplication::UnicodeUTF8));
        ck_Out7_Fault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2727", 0, QApplication::UnicodeUTF8));
        ck_Out6_Fault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2726", 0, QApplication::UnicodeUTF8));
        ck_Out5_Fault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2725", 0, QApplication::UnicodeUTF8));
        ck_Out3_Fault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2723", 0, QApplication::UnicodeUTF8));
        ck_Out4_Fault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2724", 0, QApplication::UnicodeUTF8));
        ck_Out1->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2721", 0, QApplication::UnicodeUTF8));
        ck_Out4->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2724", 0, QApplication::UnicodeUTF8));
        ck_Out7->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2727", 0, QApplication::UnicodeUTF8));
        ck_Out6->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2726", 0, QApplication::UnicodeUTF8));
        ck_Out5->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2725", 0, QApplication::UnicodeUTF8));
        ck_Out3->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2723", 0, QApplication::UnicodeUTF8));
        ck_Out2->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2722", 0, QApplication::UnicodeUTF8));
        ck_Out1_Fault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2721", 0, QApplication::UnicodeUTF8));
        ck_Out2_Fault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2722", 0, QApplication::UnicodeUTF8));
        label_Fault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\346\225\205\351\232\234\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        ck_Out8->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\274\200\345\207\2728", 0, QApplication::UnicodeUTF8));
        label_PreFault->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\345\270\270\346\200\201\357\274\232  ", 0, QApplication::UnicodeUTF8));
        m_btnSettingValue->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\346\225\264\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        m_btnEstimate->setText(QApplication::translate("QSttMacroParaEditViewGradient", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab), QApplication::translate("QSttMacroParaEditViewGradient", "\351\200\222\345\217\230\351\200\232\351\201\223\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttMacroParaEditViewGradient: public Ui_QSttMacroParaEditViewGradient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTMACROPARAEDITVIEWGRADIENT_H
