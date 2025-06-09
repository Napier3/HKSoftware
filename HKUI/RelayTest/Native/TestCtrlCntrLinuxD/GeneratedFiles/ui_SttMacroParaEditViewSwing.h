/********************************************************************************
** Form generated from reading UI file 'SttMacroParaEditViewSwing.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTMACROPARAEDITVIEWSWING_H
#define UI_STTMACROPARAEDITVIEWSWING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSttMacroParaEditViewSwing
{
public:
    QHBoxLayout *horizontalLayout_13;
    QTabWidget *m_tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_labPAngleStart;
    QLineEdit *m_editPAngleStart;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_labSwingCount;
    QLineEdit *m_editSwingCount;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *m_cbRefault;
    QCheckBox *m_cbDzdt;
    QCheckBox *m_cbReciprocating;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnResultEval;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *m_btnTestParas;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_35;
    QLabel *m_labZ1;
    QLineEdit *m_editZ1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_labPAngleEnd;
    QLineEdit *m_editPAngleEnd;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_labSwingCycle;
    QLineEdit *m_editSwingCycle;
    QHBoxLayout *horizontalLayout_39;
    QLabel *m_labISet1;
    QLineEdit *m_editISet1;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QLineEdit *m_editEmEnRate;
    QHBoxLayout *horizontalLayout_38;
    QLabel *m_labFaultTime;
    QLineEdit *m_editFaultTime;
    QHBoxLayout *horizontalLayout_36;
    QLabel *m_labFaultType;
    QComboBox *m_cbbFaultType;
    QHBoxLayout *horizontalLayout_8;
    QLabel *m_labTripPoint;
    QComboBox *m_cbbTripPoint;
    QHBoxLayout *horizontalLayout_41;
    QLabel *m_labK0Mode;
    QComboBox *m_cbbK0Mode;
    QHBoxLayout *horizontalLayout_37;
    QLabel *m_labPhase;
    QLineEdit *m_editPhase;
    QHBoxLayout *horizontalLayout_34;
    QLabel *m_labTripSpeedDown;
    QComboBox *m_cbbTripSpeedDown;
    QHBoxLayout *horizontalLayout_40;
    QLabel *m_labAmplitude;
    QLineEdit *m_editAmplitude;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_labTripSpeedUp;
    QComboBox *m_cbbTripSpeedUp;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_16;
    QLineEdit *m_editDzdt;
    QRadioButton *m_rbSpeedUp;
    QRadioButton *m_rbSpeedDown;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QSttMacroParaEditViewSwing)
    {
        if (QSttMacroParaEditViewSwing->objectName().isEmpty())
            QSttMacroParaEditViewSwing->setObjectName(QString::fromUtf8("QSttMacroParaEditViewSwing"));
        QSttMacroParaEditViewSwing->resize(1009, 608);
        horizontalLayout_13 = new QHBoxLayout(QSttMacroParaEditViewSwing);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        m_tabWidget = new QTabWidget(QSttMacroParaEditViewSwing);
        m_tabWidget->setObjectName(QString::fromUtf8("m_tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_labPAngleStart = new QLabel(tab);
        m_labPAngleStart->setObjectName(QString::fromUtf8("m_labPAngleStart"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labPAngleStart->sizePolicy().hasHeightForWidth());
        m_labPAngleStart->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(m_labPAngleStart);

        m_editPAngleStart = new QLineEdit(tab);
        m_editPAngleStart->setObjectName(QString::fromUtf8("m_editPAngleStart"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_editPAngleStart->sizePolicy().hasHeightForWidth());
        m_editPAngleStart->setSizePolicy(sizePolicy1);
        m_editPAngleStart->setMinimumSize(QSize(300, 0));
        m_editPAngleStart->setMaximumSize(QSize(270, 16777215));

        horizontalLayout_2->addWidget(m_editPAngleStart);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_labSwingCount = new QLabel(tab);
        m_labSwingCount->setObjectName(QString::fromUtf8("m_labSwingCount"));
        sizePolicy.setHeightForWidth(m_labSwingCount->sizePolicy().hasHeightForWidth());
        m_labSwingCount->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(m_labSwingCount);

        m_editSwingCount = new QLineEdit(tab);
        m_editSwingCount->setObjectName(QString::fromUtf8("m_editSwingCount"));
        sizePolicy1.setHeightForWidth(m_editSwingCount->sizePolicy().hasHeightForWidth());
        m_editSwingCount->setSizePolicy(sizePolicy1);
        m_editSwingCount->setMinimumSize(QSize(300, 0));
        m_editSwingCount->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_6->addWidget(m_editSwingCount);


        gridLayout_2->addLayout(horizontalLayout_6, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, -1, -1, -1);
        m_cbRefault = new QCheckBox(tab);
        m_cbRefault->setObjectName(QString::fromUtf8("m_cbRefault"));
        sizePolicy1.setHeightForWidth(m_cbRefault->sizePolicy().hasHeightForWidth());
        m_cbRefault->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(m_cbRefault);

        m_cbDzdt = new QCheckBox(tab);
        m_cbDzdt->setObjectName(QString::fromUtf8("m_cbDzdt"));
        sizePolicy1.setHeightForWidth(m_cbDzdt->sizePolicy().hasHeightForWidth());
        m_cbDzdt->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(m_cbDzdt);

        m_cbReciprocating = new QCheckBox(tab);
        m_cbReciprocating->setObjectName(QString::fromUtf8("m_cbReciprocating"));
        sizePolicy1.setHeightForWidth(m_cbReciprocating->sizePolicy().hasHeightForWidth());
        m_cbReciprocating->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(m_cbReciprocating);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        m_btnResultEval = new QPushButton(tab);
        m_btnResultEval->setObjectName(QString::fromUtf8("m_btnResultEval"));

        horizontalLayout_3->addWidget(m_btnResultEval);

        horizontalSpacer_14 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_14);

        m_btnTestParas = new QPushButton(tab);
        m_btnTestParas->setObjectName(QString::fromUtf8("m_btnTestParas"));

        horizontalLayout_3->addWidget(m_btnTestParas);

        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout_3, 8, 0, 1, 3);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        m_labZ1 = new QLabel(tab);
        m_labZ1->setObjectName(QString::fromUtf8("m_labZ1"));
        sizePolicy.setHeightForWidth(m_labZ1->sizePolicy().hasHeightForWidth());
        m_labZ1->setSizePolicy(sizePolicy);
        m_labZ1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_35->addWidget(m_labZ1);

        m_editZ1 = new QLineEdit(tab);
        m_editZ1->setObjectName(QString::fromUtf8("m_editZ1"));
        sizePolicy1.setHeightForWidth(m_editZ1->sizePolicy().hasHeightForWidth());
        m_editZ1->setSizePolicy(sizePolicy1);
        m_editZ1->setMinimumSize(QSize(300, 0));
        m_editZ1->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_35->addWidget(m_editZ1);


        gridLayout_2->addLayout(horizontalLayout_35, 1, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_labPAngleEnd = new QLabel(tab);
        m_labPAngleEnd->setObjectName(QString::fromUtf8("m_labPAngleEnd"));
        sizePolicy.setHeightForWidth(m_labPAngleEnd->sizePolicy().hasHeightForWidth());
        m_labPAngleEnd->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(m_labPAngleEnd);

        m_editPAngleEnd = new QLineEdit(tab);
        m_editPAngleEnd->setObjectName(QString::fromUtf8("m_editPAngleEnd"));
        sizePolicy1.setHeightForWidth(m_editPAngleEnd->sizePolicy().hasHeightForWidth());
        m_editPAngleEnd->setSizePolicy(sizePolicy1);
        m_editPAngleEnd->setMinimumSize(QSize(300, 0));
        m_editPAngleEnd->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_4->addWidget(m_editPAngleEnd);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_labSwingCycle = new QLabel(tab);
        m_labSwingCycle->setObjectName(QString::fromUtf8("m_labSwingCycle"));
        sizePolicy.setHeightForWidth(m_labSwingCycle->sizePolicy().hasHeightForWidth());
        m_labSwingCycle->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(m_labSwingCycle);

        m_editSwingCycle = new QLineEdit(tab);
        m_editSwingCycle->setObjectName(QString::fromUtf8("m_editSwingCycle"));
        sizePolicy1.setHeightForWidth(m_editSwingCycle->sizePolicy().hasHeightForWidth());
        m_editSwingCycle->setSizePolicy(sizePolicy1);
        m_editSwingCycle->setMinimumSize(QSize(300, 0));
        m_editSwingCycle->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_5->addWidget(m_editSwingCycle);


        gridLayout_2->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        m_labISet1 = new QLabel(tab);
        m_labISet1->setObjectName(QString::fromUtf8("m_labISet1"));
        sizePolicy.setHeightForWidth(m_labISet1->sizePolicy().hasHeightForWidth());
        m_labISet1->setSizePolicy(sizePolicy);
        m_labISet1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_39->addWidget(m_labISet1);

        m_editISet1 = new QLineEdit(tab);
        m_editISet1->setObjectName(QString::fromUtf8("m_editISet1"));
        sizePolicy1.setHeightForWidth(m_editISet1->sizePolicy().hasHeightForWidth());
        m_editISet1->setSizePolicy(sizePolicy1);
        m_editISet1->setMinimumSize(QSize(300, 0));
        m_editISet1->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_39->addWidget(m_editISet1);


        gridLayout_2->addLayout(horizontalLayout_39, 2, 2, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(label_9);

        m_editEmEnRate = new QLineEdit(tab);
        m_editEmEnRate->setObjectName(QString::fromUtf8("m_editEmEnRate"));
        sizePolicy1.setHeightForWidth(m_editEmEnRate->sizePolicy().hasHeightForWidth());
        m_editEmEnRate->setSizePolicy(sizePolicy1);
        m_editEmEnRate->setMinimumSize(QSize(300, 0));
        m_editEmEnRate->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_7->addWidget(m_editEmEnRate);


        gridLayout_2->addLayout(horizontalLayout_7, 4, 0, 1, 1);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        m_labFaultTime = new QLabel(tab);
        m_labFaultTime->setObjectName(QString::fromUtf8("m_labFaultTime"));
        sizePolicy.setHeightForWidth(m_labFaultTime->sizePolicy().hasHeightForWidth());
        m_labFaultTime->setSizePolicy(sizePolicy);
        m_labFaultTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_38->addWidget(m_labFaultTime);

        m_editFaultTime = new QLineEdit(tab);
        m_editFaultTime->setObjectName(QString::fromUtf8("m_editFaultTime"));
        sizePolicy1.setHeightForWidth(m_editFaultTime->sizePolicy().hasHeightForWidth());
        m_editFaultTime->setSizePolicy(sizePolicy1);
        m_editFaultTime->setMinimumSize(QSize(300, 0));
        m_editFaultTime->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_38->addWidget(m_editFaultTime);


        gridLayout_2->addLayout(horizontalLayout_38, 3, 2, 1, 1);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        m_labFaultType = new QLabel(tab);
        m_labFaultType->setObjectName(QString::fromUtf8("m_labFaultType"));
        sizePolicy.setHeightForWidth(m_labFaultType->sizePolicy().hasHeightForWidth());
        m_labFaultType->setSizePolicy(sizePolicy);
        m_labFaultType->setLayoutDirection(Qt::LeftToRight);
        m_labFaultType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_36->addWidget(m_labFaultType);

        m_cbbFaultType = new QComboBox(tab);
        m_cbbFaultType->setObjectName(QString::fromUtf8("m_cbbFaultType"));
        sizePolicy1.setHeightForWidth(m_cbbFaultType->sizePolicy().hasHeightForWidth());
        m_cbbFaultType->setSizePolicy(sizePolicy1);
        m_cbbFaultType->setMinimumSize(QSize(300, 0));
        m_cbbFaultType->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_36->addWidget(m_cbbFaultType);


        gridLayout_2->addLayout(horizontalLayout_36, 0, 2, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        m_labTripPoint = new QLabel(tab);
        m_labTripPoint->setObjectName(QString::fromUtf8("m_labTripPoint"));
        sizePolicy.setHeightForWidth(m_labTripPoint->sizePolicy().hasHeightForWidth());
        m_labTripPoint->setSizePolicy(sizePolicy);
        m_labTripPoint->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_8->addWidget(m_labTripPoint);

        m_cbbTripPoint = new QComboBox(tab);
        m_cbbTripPoint->setObjectName(QString::fromUtf8("m_cbbTripPoint"));
        sizePolicy1.setHeightForWidth(m_cbbTripPoint->sizePolicy().hasHeightForWidth());
        m_cbbTripPoint->setSizePolicy(sizePolicy1);
        m_cbbTripPoint->setMinimumSize(QSize(300, 0));
        m_cbbTripPoint->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_8->addWidget(m_cbbTripPoint);


        gridLayout_2->addLayout(horizontalLayout_8, 5, 0, 1, 1);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        m_labK0Mode = new QLabel(tab);
        m_labK0Mode->setObjectName(QString::fromUtf8("m_labK0Mode"));
        sizePolicy.setHeightForWidth(m_labK0Mode->sizePolicy().hasHeightForWidth());
        m_labK0Mode->setSizePolicy(sizePolicy);
        m_labK0Mode->setLayoutDirection(Qt::RightToLeft);
        m_labK0Mode->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_41->addWidget(m_labK0Mode);

        m_cbbK0Mode = new QComboBox(tab);
        m_cbbK0Mode->setObjectName(QString::fromUtf8("m_cbbK0Mode"));
        sizePolicy1.setHeightForWidth(m_cbbK0Mode->sizePolicy().hasHeightForWidth());
        m_cbbK0Mode->setSizePolicy(sizePolicy1);
        m_cbbK0Mode->setMinimumSize(QSize(300, 0));
        m_cbbK0Mode->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_41->addWidget(m_cbbK0Mode);


        gridLayout_2->addLayout(horizontalLayout_41, 4, 2, 1, 1);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        m_labPhase = new QLabel(tab);
        m_labPhase->setObjectName(QString::fromUtf8("m_labPhase"));
        sizePolicy.setHeightForWidth(m_labPhase->sizePolicy().hasHeightForWidth());
        m_labPhase->setSizePolicy(sizePolicy);
        m_labPhase->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_37->addWidget(m_labPhase);

        m_editPhase = new QLineEdit(tab);
        m_editPhase->setObjectName(QString::fromUtf8("m_editPhase"));
        sizePolicy1.setHeightForWidth(m_editPhase->sizePolicy().hasHeightForWidth());
        m_editPhase->setSizePolicy(sizePolicy1);
        m_editPhase->setMinimumSize(QSize(300, 0));
        m_editPhase->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_37->addWidget(m_editPhase);


        gridLayout_2->addLayout(horizontalLayout_37, 6, 2, 1, 1);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        m_labTripSpeedDown = new QLabel(tab);
        m_labTripSpeedDown->setObjectName(QString::fromUtf8("m_labTripSpeedDown"));
        sizePolicy.setHeightForWidth(m_labTripSpeedDown->sizePolicy().hasHeightForWidth());
        m_labTripSpeedDown->setSizePolicy(sizePolicy);
        m_labTripSpeedDown->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_34->addWidget(m_labTripSpeedDown);

        m_cbbTripSpeedDown = new QComboBox(tab);
        m_cbbTripSpeedDown->setObjectName(QString::fromUtf8("m_cbbTripSpeedDown"));
        sizePolicy1.setHeightForWidth(m_cbbTripSpeedDown->sizePolicy().hasHeightForWidth());
        m_cbbTripSpeedDown->setSizePolicy(sizePolicy1);
        m_cbbTripSpeedDown->setMinimumSize(QSize(300, 0));
        m_cbbTripSpeedDown->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_34->addWidget(m_cbbTripSpeedDown);


        gridLayout_2->addLayout(horizontalLayout_34, 7, 0, 1, 1);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        m_labAmplitude = new QLabel(tab);
        m_labAmplitude->setObjectName(QString::fromUtf8("m_labAmplitude"));
        sizePolicy.setHeightForWidth(m_labAmplitude->sizePolicy().hasHeightForWidth());
        m_labAmplitude->setSizePolicy(sizePolicy);
        m_labAmplitude->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_40->addWidget(m_labAmplitude);

        m_editAmplitude = new QLineEdit(tab);
        m_editAmplitude->setObjectName(QString::fromUtf8("m_editAmplitude"));
        sizePolicy1.setHeightForWidth(m_editAmplitude->sizePolicy().hasHeightForWidth());
        m_editAmplitude->setSizePolicy(sizePolicy1);
        m_editAmplitude->setMinimumSize(QSize(300, 0));
        m_editAmplitude->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_40->addWidget(m_editAmplitude);


        gridLayout_2->addLayout(horizontalLayout_40, 5, 2, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        m_labTripSpeedUp = new QLabel(tab);
        m_labTripSpeedUp->setObjectName(QString::fromUtf8("m_labTripSpeedUp"));
        sizePolicy.setHeightForWidth(m_labTripSpeedUp->sizePolicy().hasHeightForWidth());
        m_labTripSpeedUp->setSizePolicy(sizePolicy);
        m_labTripSpeedUp->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_9->addWidget(m_labTripSpeedUp);

        m_cbbTripSpeedUp = new QComboBox(tab);
        m_cbbTripSpeedUp->setObjectName(QString::fromUtf8("m_cbbTripSpeedUp"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_cbbTripSpeedUp->sizePolicy().hasHeightForWidth());
        m_cbbTripSpeedUp->setSizePolicy(sizePolicy2);
        m_cbbTripSpeedUp->setMinimumSize(QSize(300, 0));
        m_cbbTripSpeedUp->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_9->addWidget(m_cbbTripSpeedUp);


        gridLayout_2->addLayout(horizontalLayout_9, 6, 0, 1, 1);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setObjectName(QString::fromUtf8("horizontalLayout_42"));
        label_16 = new QLabel(tab);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy3);
        label_16->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_42->addWidget(label_16);

        m_editDzdt = new QLineEdit(tab);
        m_editDzdt->setObjectName(QString::fromUtf8("m_editDzdt"));
        sizePolicy2.setHeightForWidth(m_editDzdt->sizePolicy().hasHeightForWidth());
        m_editDzdt->setSizePolicy(sizePolicy2);
        m_editDzdt->setMinimumSize(QSize(100, 0));
        m_editDzdt->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_42->addWidget(m_editDzdt);

        m_rbSpeedUp = new QRadioButton(tab);
        m_rbSpeedUp->setObjectName(QString::fromUtf8("m_rbSpeedUp"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(m_rbSpeedUp->sizePolicy().hasHeightForWidth());
        m_rbSpeedUp->setSizePolicy(sizePolicy4);
        m_rbSpeedUp->setMinimumSize(QSize(80, 0));
        m_rbSpeedUp->setMaximumSize(QSize(80, 16777215));
        m_rbSpeedUp->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_42->addWidget(m_rbSpeedUp);

        m_rbSpeedDown = new QRadioButton(tab);
        m_rbSpeedDown->setObjectName(QString::fromUtf8("m_rbSpeedDown"));
        sizePolicy1.setHeightForWidth(m_rbSpeedDown->sizePolicy().hasHeightForWidth());
        m_rbSpeedDown->setSizePolicy(sizePolicy1);
        m_rbSpeedDown->setMinimumSize(QSize(80, 0));
        m_rbSpeedDown->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_42->addWidget(m_rbSpeedDown);


        gridLayout_2->addLayout(horizontalLayout_42, 7, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        m_tabWidget->addTab(tab, QString());

        horizontalLayout_13->addWidget(m_tabWidget);


        retranslateUi(QSttMacroParaEditViewSwing);

        m_tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QSttMacroParaEditViewSwing);
    } // setupUi

    void retranslateUi(QWidget *QSttMacroParaEditViewSwing)
    {
        QSttMacroParaEditViewSwing->setWindowTitle(QApplication::translate("QSttMacroParaEditViewSwing", "Form", 0, QApplication::UnicodeUTF8));
        m_labPAngleStart->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\345\212\237\350\247\222\345\247\213\345\200\274(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labSwingCount->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\346\214\257\350\215\241\346\254\241\346\225\260:", 0, QApplication::UnicodeUTF8));
        m_cbRefault->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\346\214\257\350\215\241\344\270\255\345\206\215\346\225\205\351\232\234", 0, QApplication::UnicodeUTF8));
        m_cbDzdt->setText(QApplication::translate("QSttMacroParaEditViewSwing", "dz/dt", 0, QApplication::UnicodeUTF8));
        m_cbReciprocating->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\345\276\200\345\244\215\346\214\257\350\215\241", 0, QApplication::UnicodeUTF8));
        m_btnResultEval->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\347\273\223\346\236\234\350\257\204\344\274\260", 0, QApplication::UnicodeUTF8));
        m_btnTestParas->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labZ1->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\347\237\255\350\267\257\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labPAngleEnd->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\345\212\237\350\247\222\347\273\210\345\200\274(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labSwingCycle->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\346\214\257\350\215\241\345\221\250\346\234\237(s):", 0, QApplication::UnicodeUTF8));
        m_labISet1->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\346\225\205\351\232\234\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("QSttMacroParaEditViewSwing", "|EM|/|EN|:", 0, QApplication::UnicodeUTF8));
        m_labFaultTime->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\346\225\205\351\232\234\345\217\221\347\224\237\346\227\266\345\210\273(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultType->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\346\225\205\351\232\234\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_cbbFaultType->clear();
        m_cbbFaultType->insertItems(0, QStringList()
         << QApplication::translate("QSttMacroParaEditViewSwing", "A\347\233\270\346\216\245\345\234\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "B\347\233\270\346\216\245\345\234\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "C\347\233\270\346\216\245\345\234\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "AB\347\237\255\350\267\257", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "BC\347\237\255\350\267\257", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "CA\347\237\255\350\267\257", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "\344\270\211\347\233\270\347\237\255\350\267\257", 0, QApplication::UnicodeUTF8)
        );
        m_labTripPoint->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\350\267\263\351\227\270\346\216\245\347\202\271:", 0, QApplication::UnicodeUTF8));
        m_cbbTripPoint->clear();
        m_cbbTripPoint->insertItems(0, QStringList()
         << QApplication::translate("QSttMacroParaEditViewSwing", "A", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "B", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "C", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "D", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "E", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "F", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "G", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "H", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "I", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "J", 0, QApplication::UnicodeUTF8)
        );
        m_labK0Mode->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\350\241\250\350\276\276\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_cbbK0Mode->clear();
        m_cbbK0Mode->insertItems(0, QStringList()
         << QApplication::translate("QSttMacroParaEditViewSwing", "KL", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "Kr,Kx", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QSttMacroParaEditViewSwing", "Z0,Z1", 0, QApplication::UnicodeUTF8)
        );
        m_labPhase->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\347\233\270\344\275\215:", 0, QApplication::UnicodeUTF8));
        m_labTripSpeedDown->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\345\207\217\351\200\237\344\277\241\345\217\267\346\216\245\347\202\271:", 0, QApplication::UnicodeUTF8));
        m_cbbTripSpeedDown->clear();
        m_cbbTripSpeedDown->insertItems(0, QStringList()
         << QApplication::translate("QSttMacroParaEditViewSwing", "D", 0, QApplication::UnicodeUTF8)
        );
        m_labAmplitude->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\345\271\205\345\200\274:", 0, QApplication::UnicodeUTF8));
        m_labTripSpeedUp->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\345\212\240\351\200\237\344\277\241\345\217\267\346\216\245\347\202\271:", 0, QApplication::UnicodeUTF8));
        m_cbbTripSpeedUp->clear();
        m_cbbTripSpeedUp->insertItems(0, QStringList()
         << QApplication::translate("QSttMacroParaEditViewSwing", "C", 0, QApplication::UnicodeUTF8)
        );
        label_16->setText(QApplication::translate("QSttMacroParaEditViewSwing", "dz/dt(\316\251/s):", 0, QApplication::UnicodeUTF8));
        m_rbSpeedUp->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\345\242\236\351\200\237", 0, QApplication::UnicodeUTF8));
        m_rbSpeedDown->setText(QApplication::translate("QSttMacroParaEditViewSwing", "\345\207\217\351\200\237", 0, QApplication::UnicodeUTF8));
        m_tabWidget->setTabText(m_tabWidget->indexOf(tab), QApplication::translate("QSttMacroParaEditViewSwing", "\346\214\257\350\215\241\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttMacroParaEditViewSwing: public Ui_QSttMacroParaEditViewSwing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTMACROPARAEDITVIEWSWING_H
