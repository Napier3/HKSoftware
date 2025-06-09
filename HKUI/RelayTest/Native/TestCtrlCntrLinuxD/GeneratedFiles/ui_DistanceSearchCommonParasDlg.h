/********************************************************************************
** Form generated from reading UI file 'DistanceSearchCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCESEARCHCOMMONPARASDLG_H
#define UI_DISTANCESEARCHCOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
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

class Ui_QDistanceSearchCommonParasDlg
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_5;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *m_editFaultTime;
    QLabel *m_labFaultTime;
    QLineEdit *m_editAngKx;
    QLabel *m_labILoadPh;
    QLineEdit *m_editILoadPh;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *m_labAngKx_2;
    QLabel *m_labAngKx;
    QLabel *m_labActionTime;
    QLineEdit *m_editActionTime;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labPreTime;
    QLabel *m_labTimeAfterTrigger;
    QLabel *m_labSearchMode;
    CExBaseListComboBox *m_cbbSearchMode;
    QLineEdit *m_editILoad;
    QLabel *m_labILoad;
    QLineEdit *m_editPreFaultTime;
    QLineEdit *m_editTimeAfterTrigger;
    QLineEdit *m_editKlKr;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labKlKr_2;
    QLabel *m_labKlKr;
    QLabel *m_labZl;
    QLabel *m_labK0Mode;
    QComboBox *m_cbbK0Mode;
    QLineEdit *m_editZl;
    QLabel *m_labZAng;
    QLineEdit *m_editZAng;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_7;
    QGridLayout *gridLayout_3;
    QLabel *m_labZsAng;
    QComboBox *m_cbbCalcuMode;
    CExBaseListComboBox *m_cbbSimulateBreakerDelay;
    QLineEdit *m_editBrkCloseTime;
    CExBaseListComboBox *m_cbbFaultAngMode;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *m_cbbFaultId;
    QLabel *m_labCalMode;
    QLabel *m_labPTPos;
    QLabel *m_labSimulateBreakerDelay;
    QLabel *m_labFaultAng;
    CExBaseListComboBox *m_cbbPTPos;
    QLabel *m_labFaultAngMode;
    QLabel *m_labBrkCloseTime;
    QLabel *m_labCTPos;
    CExBaseListComboBox *m_cbbCTPos;
    QLineEdit *m_editFaultAng;
    QLabel *m_labBrkBreakTime;
    QLabel *m_labFaultId;
    QLineEdit *m_editBrkBreakTime;
    QLabel *m_labZsMag;
    QLineEdit *m_editZsAng;
    QLineEdit *m_editZsMag;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QDialog *QDistanceSearchCommonParasDlg)
    {
        if (QDistanceSearchCommonParasDlg->objectName().isEmpty())
            QDistanceSearchCommonParasDlg->setObjectName(QString::fromUtf8("QDistanceSearchCommonParasDlg"));
        QDistanceSearchCommonParasDlg->resize(910, 546);
        horizontalLayout_2 = new QHBoxLayout(QDistanceSearchCommonParasDlg);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(QDistanceSearchCommonParasDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        m_editFaultTime = new QLineEdit(frame);
        m_editFaultTime->setObjectName(QString::fromUtf8("m_editFaultTime"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_editFaultTime->sizePolicy().hasHeightForWidth());
        m_editFaultTime->setSizePolicy(sizePolicy);
        m_editFaultTime->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editFaultTime, 2, 3, 1, 1);

        m_labFaultTime = new QLabel(frame);
        m_labFaultTime->setObjectName(QString::fromUtf8("m_labFaultTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_labFaultTime->sizePolicy().hasHeightForWidth());
        m_labFaultTime->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labFaultTime, 2, 1, 1, 1);

        m_editAngKx = new QLineEdit(frame);
        m_editAngKx->setObjectName(QString::fromUtf8("m_editAngKx"));
        sizePolicy.setHeightForWidth(m_editAngKx->sizePolicy().hasHeightForWidth());
        m_editAngKx->setSizePolicy(sizePolicy);
        m_editAngKx->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editAngKx, 8, 3, 1, 1);

        m_labILoadPh = new QLabel(frame);
        m_labILoadPh->setObjectName(QString::fromUtf8("m_labILoadPh"));
        sizePolicy1.setHeightForWidth(m_labILoadPh->sizePolicy().hasHeightForWidth());
        m_labILoadPh->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labILoadPh, 12, 1, 1, 1);

        m_editILoadPh = new QLineEdit(frame);
        m_editILoadPh->setObjectName(QString::fromUtf8("m_editILoadPh"));
        sizePolicy.setHeightForWidth(m_editILoadPh->sizePolicy().hasHeightForWidth());
        m_editILoadPh->setSizePolicy(sizePolicy);
        m_editILoadPh->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editILoadPh, 12, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 4, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        m_labAngKx_2 = new QLabel(frame);
        m_labAngKx_2->setObjectName(QString::fromUtf8("m_labAngKx_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_labAngKx_2->sizePolicy().hasHeightForWidth());
        m_labAngKx_2->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(m_labAngKx_2);

        m_labAngKx = new QLabel(frame);
        m_labAngKx->setObjectName(QString::fromUtf8("m_labAngKx"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_labAngKx->sizePolicy().hasHeightForWidth());
        m_labAngKx->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(m_labAngKx);


        gridLayout->addLayout(horizontalLayout_8, 8, 1, 1, 1);

        m_labActionTime = new QLabel(frame);
        m_labActionTime->setObjectName(QString::fromUtf8("m_labActionTime"));
        sizePolicy1.setHeightForWidth(m_labActionTime->sizePolicy().hasHeightForWidth());
        m_labActionTime->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labActionTime, 3, 1, 1, 1);

        m_editActionTime = new QLineEdit(frame);
        m_editActionTime->setObjectName(QString::fromUtf8("m_editActionTime"));
        sizePolicy.setHeightForWidth(m_editActionTime->sizePolicy().hasHeightForWidth());
        m_editActionTime->setSizePolicy(sizePolicy);
        m_editActionTime->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editActionTime, 3, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        m_labPreTime = new QLabel(frame);
        m_labPreTime->setObjectName(QString::fromUtf8("m_labPreTime"));
        sizePolicy1.setHeightForWidth(m_labPreTime->sizePolicy().hasHeightForWidth());
        m_labPreTime->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labPreTime, 0, 1, 1, 1);

        m_labTimeAfterTrigger = new QLabel(frame);
        m_labTimeAfterTrigger->setObjectName(QString::fromUtf8("m_labTimeAfterTrigger"));
        sizePolicy1.setHeightForWidth(m_labTimeAfterTrigger->sizePolicy().hasHeightForWidth());
        m_labTimeAfterTrigger->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labTimeAfterTrigger, 1, 1, 1, 1);

        m_labSearchMode = new QLabel(frame);
        m_labSearchMode->setObjectName(QString::fromUtf8("m_labSearchMode"));
        sizePolicy1.setHeightForWidth(m_labSearchMode->sizePolicy().hasHeightForWidth());
        m_labSearchMode->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labSearchMode, 10, 1, 1, 1);

        m_cbbSearchMode = new CExBaseListComboBox(frame);
        m_cbbSearchMode->setObjectName(QString::fromUtf8("m_cbbSearchMode"));
        sizePolicy.setHeightForWidth(m_cbbSearchMode->sizePolicy().hasHeightForWidth());
        m_cbbSearchMode->setSizePolicy(sizePolicy);
        m_cbbSearchMode->setMinimumSize(QSize(0, 0));
        m_cbbSearchMode->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_cbbSearchMode, 10, 3, 1, 1);

        m_editILoad = new QLineEdit(frame);
        m_editILoad->setObjectName(QString::fromUtf8("m_editILoad"));
        sizePolicy.setHeightForWidth(m_editILoad->sizePolicy().hasHeightForWidth());
        m_editILoad->setSizePolicy(sizePolicy);
        m_editILoad->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editILoad, 11, 3, 1, 1);

        m_labILoad = new QLabel(frame);
        m_labILoad->setObjectName(QString::fromUtf8("m_labILoad"));
        sizePolicy1.setHeightForWidth(m_labILoad->sizePolicy().hasHeightForWidth());
        m_labILoad->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labILoad, 11, 1, 1, 1);

        m_editPreFaultTime = new QLineEdit(frame);
        m_editPreFaultTime->setObjectName(QString::fromUtf8("m_editPreFaultTime"));
        sizePolicy.setHeightForWidth(m_editPreFaultTime->sizePolicy().hasHeightForWidth());
        m_editPreFaultTime->setSizePolicy(sizePolicy);
        m_editPreFaultTime->setMinimumSize(QSize(120, 0));
        m_editPreFaultTime->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editPreFaultTime, 0, 3, 1, 1);

        m_editTimeAfterTrigger = new QLineEdit(frame);
        m_editTimeAfterTrigger->setObjectName(QString::fromUtf8("m_editTimeAfterTrigger"));
        sizePolicy.setHeightForWidth(m_editTimeAfterTrigger->sizePolicy().hasHeightForWidth());
        m_editTimeAfterTrigger->setSizePolicy(sizePolicy);
        m_editTimeAfterTrigger->setMinimumSize(QSize(120, 0));
        m_editTimeAfterTrigger->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editTimeAfterTrigger, 1, 3, 1, 1);

        m_editKlKr = new QLineEdit(frame);
        m_editKlKr->setObjectName(QString::fromUtf8("m_editKlKr"));
        sizePolicy.setHeightForWidth(m_editKlKr->sizePolicy().hasHeightForWidth());
        m_editKlKr->setSizePolicy(sizePolicy);
        m_editKlKr->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editKlKr, 7, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labKlKr_2 = new QLabel(frame);
        m_labKlKr_2->setObjectName(QString::fromUtf8("m_labKlKr_2"));
        sizePolicy2.setHeightForWidth(m_labKlKr_2->sizePolicy().hasHeightForWidth());
        m_labKlKr_2->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(m_labKlKr_2);

        m_labKlKr = new QLabel(frame);
        m_labKlKr->setObjectName(QString::fromUtf8("m_labKlKr"));
        sizePolicy3.setHeightForWidth(m_labKlKr->sizePolicy().hasHeightForWidth());
        m_labKlKr->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(m_labKlKr);


        gridLayout->addLayout(horizontalLayout, 7, 1, 1, 1);

        m_labZl = new QLabel(frame);
        m_labZl->setObjectName(QString::fromUtf8("m_labZl"));
        sizePolicy1.setHeightForWidth(m_labZl->sizePolicy().hasHeightForWidth());
        m_labZl->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labZl, 4, 1, 1, 1);

        m_labK0Mode = new QLabel(frame);
        m_labK0Mode->setObjectName(QString::fromUtf8("m_labK0Mode"));
        sizePolicy1.setHeightForWidth(m_labK0Mode->sizePolicy().hasHeightForWidth());
        m_labK0Mode->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labK0Mode, 6, 1, 1, 1);

        m_cbbK0Mode = new QComboBox(frame);
        m_cbbK0Mode->setObjectName(QString::fromUtf8("m_cbbK0Mode"));
        sizePolicy.setHeightForWidth(m_cbbK0Mode->sizePolicy().hasHeightForWidth());
        m_cbbK0Mode->setSizePolicy(sizePolicy);
        m_cbbK0Mode->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_cbbK0Mode, 6, 3, 1, 1);

        m_editZl = new QLineEdit(frame);
        m_editZl->setObjectName(QString::fromUtf8("m_editZl"));
        sizePolicy.setHeightForWidth(m_editZl->sizePolicy().hasHeightForWidth());
        m_editZl->setSizePolicy(sizePolicy);
        m_editZl->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editZl, 4, 3, 1, 1);

        m_labZAng = new QLabel(frame);
        m_labZAng->setObjectName(QString::fromUtf8("m_labZAng"));
        sizePolicy1.setHeightForWidth(m_labZAng->sizePolicy().hasHeightForWidth());
        m_labZAng->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_labZAng, 5, 1, 1, 1);

        m_editZAng = new QLineEdit(frame);
        m_editZAng->setObjectName(QString::fromUtf8("m_editZAng"));
        sizePolicy.setHeightForWidth(m_editZAng->sizePolicy().hasHeightForWidth());
        m_editZAng->setSizePolicy(sizePolicy);
        m_editZAng->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(m_editZAng, 5, 3, 1, 1);


        horizontalLayout_5->addLayout(gridLayout);


        verticalLayout_2->addWidget(frame);


        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_3 = new QFrame(QDistanceSearchCommonParasDlg);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::Box);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_3);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_labZsAng = new QLabel(frame_3);
        m_labZsAng->setObjectName(QString::fromUtf8("m_labZsAng"));
        sizePolicy1.setHeightForWidth(m_labZsAng->sizePolicy().hasHeightForWidth());
        m_labZsAng->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labZsAng, 2, 1, 1, 1);

        m_cbbCalcuMode = new QComboBox(frame_3);
        m_cbbCalcuMode->setObjectName(QString::fromUtf8("m_cbbCalcuMode"));
        sizePolicy.setHeightForWidth(m_cbbCalcuMode->sizePolicy().hasHeightForWidth());
        m_cbbCalcuMode->setSizePolicy(sizePolicy);
        m_cbbCalcuMode->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_cbbCalcuMode, 0, 3, 1, 1);

        m_cbbSimulateBreakerDelay = new CExBaseListComboBox(frame_3);
        m_cbbSimulateBreakerDelay->setObjectName(QString::fromUtf8("m_cbbSimulateBreakerDelay"));
        sizePolicy.setHeightForWidth(m_cbbSimulateBreakerDelay->sizePolicy().hasHeightForWidth());
        m_cbbSimulateBreakerDelay->setSizePolicy(sizePolicy);
        m_cbbSimulateBreakerDelay->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_cbbSimulateBreakerDelay, 5, 3, 1, 1);

        m_editBrkCloseTime = new QLineEdit(frame_3);
        m_editBrkCloseTime->setObjectName(QString::fromUtf8("m_editBrkCloseTime"));
        sizePolicy.setHeightForWidth(m_editBrkCloseTime->sizePolicy().hasHeightForWidth());
        m_editBrkCloseTime->setSizePolicy(sizePolicy);
        m_editBrkCloseTime->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_editBrkCloseTime, 7, 3, 1, 1);

        m_cbbFaultAngMode = new CExBaseListComboBox(frame_3);
        m_cbbFaultAngMode->setObjectName(QString::fromUtf8("m_cbbFaultAngMode"));
        sizePolicy.setHeightForWidth(m_cbbFaultAngMode->sizePolicy().hasHeightForWidth());
        m_cbbFaultAngMode->setSizePolicy(sizePolicy);
        m_cbbFaultAngMode->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_cbbFaultAngMode, 9, 3, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 3, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 3, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        m_cbbFaultId = new QComboBox(frame_3);
        m_cbbFaultId->setObjectName(QString::fromUtf8("m_cbbFaultId"));
        sizePolicy.setHeightForWidth(m_cbbFaultId->sizePolicy().hasHeightForWidth());
        m_cbbFaultId->setSizePolicy(sizePolicy);
        m_cbbFaultId->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_cbbFaultId, 8, 3, 1, 1);

        m_labCalMode = new QLabel(frame_3);
        m_labCalMode->setObjectName(QString::fromUtf8("m_labCalMode"));
        sizePolicy1.setHeightForWidth(m_labCalMode->sizePolicy().hasHeightForWidth());
        m_labCalMode->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labCalMode, 0, 1, 1, 1);

        m_labPTPos = new QLabel(frame_3);
        m_labPTPos->setObjectName(QString::fromUtf8("m_labPTPos"));
        sizePolicy1.setHeightForWidth(m_labPTPos->sizePolicy().hasHeightForWidth());
        m_labPTPos->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labPTPos, 3, 1, 1, 1);

        m_labSimulateBreakerDelay = new QLabel(frame_3);
        m_labSimulateBreakerDelay->setObjectName(QString::fromUtf8("m_labSimulateBreakerDelay"));
        sizePolicy1.setHeightForWidth(m_labSimulateBreakerDelay->sizePolicy().hasHeightForWidth());
        m_labSimulateBreakerDelay->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labSimulateBreakerDelay, 5, 1, 1, 1);

        m_labFaultAng = new QLabel(frame_3);
        m_labFaultAng->setObjectName(QString::fromUtf8("m_labFaultAng"));
        sizePolicy1.setHeightForWidth(m_labFaultAng->sizePolicy().hasHeightForWidth());
        m_labFaultAng->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labFaultAng, 10, 1, 1, 1);

        m_cbbPTPos = new CExBaseListComboBox(frame_3);
        m_cbbPTPos->setObjectName(QString::fromUtf8("m_cbbPTPos"));
        sizePolicy.setHeightForWidth(m_cbbPTPos->sizePolicy().hasHeightForWidth());
        m_cbbPTPos->setSizePolicy(sizePolicy);
        m_cbbPTPos->setMinimumSize(QSize(120, 0));

        gridLayout_3->addWidget(m_cbbPTPos, 3, 3, 1, 1);

        m_labFaultAngMode = new QLabel(frame_3);
        m_labFaultAngMode->setObjectName(QString::fromUtf8("m_labFaultAngMode"));
        sizePolicy1.setHeightForWidth(m_labFaultAngMode->sizePolicy().hasHeightForWidth());
        m_labFaultAngMode->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labFaultAngMode, 9, 1, 1, 1);

        m_labBrkCloseTime = new QLabel(frame_3);
        m_labBrkCloseTime->setObjectName(QString::fromUtf8("m_labBrkCloseTime"));
        sizePolicy1.setHeightForWidth(m_labBrkCloseTime->sizePolicy().hasHeightForWidth());
        m_labBrkCloseTime->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labBrkCloseTime, 7, 1, 1, 1);

        m_labCTPos = new QLabel(frame_3);
        m_labCTPos->setObjectName(QString::fromUtf8("m_labCTPos"));
        sizePolicy1.setHeightForWidth(m_labCTPos->sizePolicy().hasHeightForWidth());
        m_labCTPos->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labCTPos, 4, 1, 1, 1);

        m_cbbCTPos = new CExBaseListComboBox(frame_3);
        m_cbbCTPos->setObjectName(QString::fromUtf8("m_cbbCTPos"));
        sizePolicy.setHeightForWidth(m_cbbCTPos->sizePolicy().hasHeightForWidth());
        m_cbbCTPos->setSizePolicy(sizePolicy);
        m_cbbCTPos->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_cbbCTPos, 4, 3, 1, 1);

        m_editFaultAng = new QLineEdit(frame_3);
        m_editFaultAng->setObjectName(QString::fromUtf8("m_editFaultAng"));
        sizePolicy.setHeightForWidth(m_editFaultAng->sizePolicy().hasHeightForWidth());
        m_editFaultAng->setSizePolicy(sizePolicy);
        m_editFaultAng->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_editFaultAng, 10, 3, 1, 1);

        m_labBrkBreakTime = new QLabel(frame_3);
        m_labBrkBreakTime->setObjectName(QString::fromUtf8("m_labBrkBreakTime"));
        sizePolicy1.setHeightForWidth(m_labBrkBreakTime->sizePolicy().hasHeightForWidth());
        m_labBrkBreakTime->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labBrkBreakTime, 6, 1, 1, 1);

        m_labFaultId = new QLabel(frame_3);
        m_labFaultId->setObjectName(QString::fromUtf8("m_labFaultId"));
        sizePolicy1.setHeightForWidth(m_labFaultId->sizePolicy().hasHeightForWidth());
        m_labFaultId->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labFaultId, 8, 1, 1, 1);

        m_editBrkBreakTime = new QLineEdit(frame_3);
        m_editBrkBreakTime->setObjectName(QString::fromUtf8("m_editBrkBreakTime"));
        sizePolicy.setHeightForWidth(m_editBrkBreakTime->sizePolicy().hasHeightForWidth());
        m_editBrkBreakTime->setSizePolicy(sizePolicy);
        m_editBrkBreakTime->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_editBrkBreakTime, 6, 3, 1, 1);

        m_labZsMag = new QLabel(frame_3);
        m_labZsMag->setObjectName(QString::fromUtf8("m_labZsMag"));
        sizePolicy1.setHeightForWidth(m_labZsMag->sizePolicy().hasHeightForWidth());
        m_labZsMag->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_labZsMag, 1, 1, 1, 1);

        m_editZsAng = new QLineEdit(frame_3);
        m_editZsAng->setObjectName(QString::fromUtf8("m_editZsAng"));
        sizePolicy.setHeightForWidth(m_editZsAng->sizePolicy().hasHeightForWidth());
        m_editZsAng->setSizePolicy(sizePolicy);
        m_editZsAng->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_editZsAng, 2, 3, 1, 1);

        m_editZsMag = new QLineEdit(frame_3);
        m_editZsMag->setObjectName(QString::fromUtf8("m_editZsMag"));
        sizePolicy.setHeightForWidth(m_editZsMag->sizePolicy().hasHeightForWidth());
        m_editZsMag->setSizePolicy(sizePolicy);
        m_editZsMag->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(m_editZsMag, 1, 3, 1, 1);


        horizontalLayout_7->addLayout(gridLayout_3);


        verticalLayout_3->addWidget(frame_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        m_btnOk = new QPushButton(QDistanceSearchCommonParasDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        sizePolicy.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(m_btnOk);

        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        m_btnCancel = new QPushButton(QDistanceSearchCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(m_btnCancel);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(QDistanceSearchCommonParasDlg);

        QMetaObject::connectSlotsByName(QDistanceSearchCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QDistanceSearchCommonParasDlg)
    {
        QDistanceSearchCommonParasDlg->setWindowTitle(QApplication::translate("QDistanceSearchCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labFaultTime->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\346\225\205\351\232\234\346\227\266\351\227\264\350\243\225\345\272\246(s):", 0, QApplication::UnicodeUTF8));
        m_labILoadPh->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\350\264\237\350\215\267\345\212\237\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labAngKx_2->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\351\233\266\345\272\217\350\241\245\345\201\277\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labAngKx->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "XE/XL:", 0, QApplication::UnicodeUTF8));
        m_labActionTime->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\346\234\200\345\260\217\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labPreTime->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\346\225\205\351\232\234\345\211\215\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labTimeAfterTrigger->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\344\277\235\346\212\244\345\212\250\344\275\234\345\220\216\346\214\201\347\273\255\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labSearchMode->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\346\220\234\347\264\242\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labILoad->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\350\264\237\350\215\267\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labKlKr_2->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\351\233\266\345\272\217\350\241\245\345\201\277\347\263\273\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labKlKr->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "RE/RL:", 0, QApplication::UnicodeUTF8));
        m_labZl->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\347\272\277\350\267\257\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labK0Mode->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\351\233\266\345\272\217\350\241\245\345\201\277\347\263\273\346\225\260\350\256\241\347\256\227\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_cbbK0Mode->clear();
        m_cbbK0Mode->insertItems(0, QStringList()
         << QApplication::translate("QDistanceSearchCommonParasDlg", "|K0|,Phi(K0)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDistanceSearchCommonParasDlg", "RERL,XEXL", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QDistanceSearchCommonParasDlg", "|Z0/Z1|,Phi(Z0/Z1)", 0, QApplication::UnicodeUTF8)
        );
        m_labZAng->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labZsAng->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\347\263\273\347\273\237\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labCalMode->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\350\256\241\347\256\227\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labPTPos->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "TV\345\256\211\350\243\205\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        m_labSimulateBreakerDelay->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\346\226\255\350\267\257\345\231\250\346\250\241\346\213\237:", 0, QApplication::UnicodeUTF8));
        m_labFaultAng->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\345\220\210\351\227\270\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labFaultAngMode->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\345\220\210\351\227\270\350\247\222\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labBrkCloseTime->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\345\220\210\351\227\270\346\227\266\351\227\264(ms):", 0, QApplication::UnicodeUTF8));
        m_labCTPos->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "TA\346\255\243\346\236\201\346\200\247:", 0, QApplication::UnicodeUTF8));
        m_labBrkBreakTime->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\345\210\206\351\227\270\346\227\266\351\227\264(ms):", 0, QApplication::UnicodeUTF8));
        m_labFaultId->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\346\230\257\345\220\246\345\217\240\345\212\240\351\235\236\345\221\250\346\234\237\345\210\206\351\207\217:", 0, QApplication::UnicodeUTF8));
        m_labZsMag->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\347\263\273\347\273\237\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QDistanceSearchCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDistanceSearchCommonParasDlg: public Ui_QDistanceSearchCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCESEARCHCOMMONPARASDLG_H
