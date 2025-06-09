#include "DistanceSearchBatchAddMultDlg.h"
#include "ui_DistanceSearchBatchAddMultDlg.h"
#include "QMessageBox"
#include "../../XLangResource_Native.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/SttTestCtrl/SttTestAppBase.h"
#include "DistanceSearchCommon.h"
#include "SttMultiMacroDistanceSearchParasDefine.h"
#include "../../Module/UI/SttTestCntrFrameApi.h"
#include "../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include "../../../../AutoTest/Module/Characteristic/Characteristics.h"

extern CFont *g_pSttGlobalFont;

QDistanceSearchBatchAddMultDlg::QDistanceSearchBatchAddMultDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDistanceSearchBatchAddMultDlg)
{
    ui->setupUi(this);
    InitUI();
    InitConnect();

    return;
}

QDistanceSearchBatchAddMultDlg::~QDistanceSearchBatchAddMultDlg()
{
    delete ui;
}

void QDistanceSearchBatchAddMultDlg::InitUI()
{
    CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
    strPngPath = _P_GetResourcePath();
    strPngPath = strPngPath + _T("images/DistanceSearchTest.png");
#else
    strPngPath =  ":/ctrls/images/DistanceSearchTest.png";
#endif
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setWindowTitle(g_sLangTxt_Button_AddMultBatch);
    QColor backgrdColor = this->palette().color(QPalette::Background);
    ui->m_tableWidget->setStyleSheet(QString("QTableWidget { background-color: %1; }").arg(backgrdColor.name()));
    ui->m_tableWidget->setFont(*g_pSttGlobalFont);
    for(int i = 0; i < 11; i++)
    {
        ui->m_tableWidget->setRowHeight(i, 40);
    }
    ui->m_tableWidget->setFixedHeight(452);
    ui->m_tableWidget->setColumnWidth(0, 0.05*this->width());
    ui->m_tableWidget->setColumnWidth(1, 0.15*this->width());
    ui->m_tableWidget->setColumnWidth(2, 0.25*this->width());
    ui->m_tableWidget->setSpan(1, 0, 5, 1);
    ui->m_tableWidget->setSpan(6, 0, 5, 1);

    ui->m_tableWidget->item(0, 1)->setText(g_sLangTxt_DistanceSearch_Header_ZoneType);
    ui->m_tableWidget->item(0, 2)->setText(g_sLangTxt_Gradient_ActionTime);
    ui->m_tableWidget->item(0, 3)->setText(g_sLangTxt_ActionTime_FaultPhase);

    QTableWidgetItem *tableWidgetItemLN = new QTableWidgetItem(/*接地故障*/g_sLangTxt_DistanceSearch_LNFault);
    tableWidgetItemLN->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QTableWidgetItem *tableWidgetItemLL = new QTableWidgetItem(/*相间故障*/g_sLangTxt_DistanceSearch_LLFault);
    tableWidgetItemLL->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->m_tableWidget->setItem(1, 0, tableWidgetItemLN);
    ui->m_tableWidget->setItem(6, 0, tableWidgetItemLL);

    m_cbLNZoneOne = new QCheckBox(g_sLangTxt_DistanceSearch_SectionOne, ui->m_tableWidget);
    m_cbLNOneAN = new QCheckBox("AN", ui->m_tableWidget);
    m_cbLNOneBN = new QCheckBox("BN", ui->m_tableWidget);
    m_cbLNOneCN = new QCheckBox("CN", ui->m_tableWidget);

    QWidget *containerWidget_1 = new QWidget(this);
    QHBoxLayout *horizontalLayout_1 = new QHBoxLayout(containerWidget_1);
    horizontalLayout_1->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_1->addStretch();
    horizontalLayout_1->addWidget(m_cbLNZoneOne);
    horizontalLayout_1->addStretch();
    ui->m_tableWidget->setCellWidget(1, 1, containerWidget_1);

    QWidget *containerWidget_2 = new QWidget(this);
    QHBoxLayout *horizontalLayout_2 = new QHBoxLayout(containerWidget_2);
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_2->addStretch();
    horizontalLayout_2->addWidget(m_cbLNOneAN);
    horizontalLayout_2->addStretch();
    horizontalLayout_2->addWidget(m_cbLNOneBN);
    horizontalLayout_2->addStretch();
    horizontalLayout_2->addWidget(m_cbLNOneCN);
    horizontalLayout_2->addStretch();
    ui->m_tableWidget->setCellWidget(1, 3, containerWidget_2);

    m_cbLNZoneTwo = new QCheckBox(g_sLangTxt_DistanceSearch_SectionTwo, ui->m_tableWidget);
    m_cbLNTwoAN = new QCheckBox("AN", ui->m_tableWidget);
    m_cbLNTwoBN = new QCheckBox("BN", ui->m_tableWidget);
    m_cbLNTwoCN = new QCheckBox("CN", ui->m_tableWidget);

    QWidget *containerWidget_3 = new QWidget(this);
    QHBoxLayout *horizontalLayout_3 = new QHBoxLayout(containerWidget_3);
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_3->addStretch();
    horizontalLayout_3->addWidget(m_cbLNZoneTwo);
    horizontalLayout_3->addStretch();
    ui->m_tableWidget->setCellWidget(2, 1, containerWidget_3);

    QWidget *containerWidget_4 = new QWidget(this);
    QHBoxLayout *horizontalLayout_4 = new QHBoxLayout(containerWidget_4);
    horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_4->addStretch();
    horizontalLayout_4->addWidget(m_cbLNTwoAN);
    horizontalLayout_4->addStretch();
    horizontalLayout_4->addWidget(m_cbLNTwoBN);
    horizontalLayout_4->addStretch();
    horizontalLayout_4->addWidget(m_cbLNTwoCN);
    horizontalLayout_4->addStretch();
    ui->m_tableWidget->setCellWidget(2, 3, containerWidget_4);

    m_cbLNZoneThree = new QCheckBox(g_sLangTxt_DistanceSearch_SectionThree, ui->m_tableWidget);
    m_cbLNThreeAN = new QCheckBox("AN", ui->m_tableWidget);
    m_cbLNThreeBN = new QCheckBox("BN", ui->m_tableWidget);
    m_cbLNThreeCN = new QCheckBox("CN", ui->m_tableWidget);

    QWidget *containerWidget_5 = new QWidget(this);
    QHBoxLayout *horizontalLayout_5 = new QHBoxLayout(containerWidget_5);
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_5->addStretch();
    horizontalLayout_5->addWidget(m_cbLNZoneThree);
    horizontalLayout_5->addStretch();
    ui->m_tableWidget->setCellWidget(3, 1, containerWidget_5);

    QWidget *containerWidget_6 = new QWidget(this);
    QHBoxLayout *horizontalLayout_6 = new QHBoxLayout(containerWidget_6);
    horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_6->addStretch();
    horizontalLayout_6->addWidget(m_cbLNThreeAN);
    horizontalLayout_6->addStretch();
    horizontalLayout_6->addWidget(m_cbLNThreeBN);
    horizontalLayout_6->addStretch();
    horizontalLayout_6->addWidget(m_cbLNThreeCN);
    horizontalLayout_6->addStretch();
    ui->m_tableWidget->setCellWidget(3, 3, containerWidget_6);

    m_cbLNZoneFour = new QCheckBox(g_sLangTxt_DistanceSearch_SectionFour, ui->m_tableWidget);
    m_cbLNFourAN = new QCheckBox("AN", ui->m_tableWidget);
    m_cbLNFourBN = new QCheckBox("BN", ui->m_tableWidget);
    m_cbLNFourCN = new QCheckBox("CN", ui->m_tableWidget);

    QWidget *containerWidget_7 = new QWidget(this);
    QHBoxLayout *horizontalLayout_7 = new QHBoxLayout(containerWidget_7);
    horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_7->addStretch();
    horizontalLayout_7->addWidget(m_cbLNZoneFour);
    horizontalLayout_7->addStretch();
    ui->m_tableWidget->setCellWidget(4, 1, containerWidget_7);

    QWidget *containerWidget_8 = new QWidget(this);
    QHBoxLayout *horizontalLayout_8 = new QHBoxLayout(containerWidget_8);
    horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_8->addStretch();
    horizontalLayout_8->addWidget(m_cbLNFourAN);
    horizontalLayout_8->addStretch();
    horizontalLayout_8->addWidget(m_cbLNFourBN);
    horizontalLayout_8->addStretch();
    horizontalLayout_8->addWidget(m_cbLNFourCN);
    horizontalLayout_8->addStretch();
    ui->m_tableWidget->setCellWidget(4, 3, containerWidget_8);

    m_cbLNZoneFive = new QCheckBox(g_sLangTxt_DistanceSearch_SectionFive, ui->m_tableWidget);
    m_cbLNFiveAN = new QCheckBox("AN", ui->m_tableWidget);
    m_cbLNFiveBN = new QCheckBox("BN", ui->m_tableWidget);
    m_cbLNFiveCN = new QCheckBox("CN", ui->m_tableWidget);

    QWidget *containerWidget_9 = new QWidget(this);
    QHBoxLayout *horizontalLayout_9 = new QHBoxLayout(containerWidget_9);
    horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_9->addStretch();
    horizontalLayout_9->addWidget(m_cbLNZoneFive);
    horizontalLayout_9->addStretch();
    ui->m_tableWidget->setCellWidget(5, 1, containerWidget_9);

    QWidget *containerWidget_10 = new QWidget(this);
    QHBoxLayout *horizontalLayout_10 = new QHBoxLayout(containerWidget_10);
    horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_10->addStretch();
    horizontalLayout_10->addWidget(m_cbLNFiveAN);
    horizontalLayout_10->addStretch();
    horizontalLayout_10->addWidget(m_cbLNFiveBN);
    horizontalLayout_10->addStretch();
    horizontalLayout_10->addWidget(m_cbLNFiveCN);
    horizontalLayout_10->addStretch();
    ui->m_tableWidget->setCellWidget(5, 3, containerWidget_10);

    m_cbLLZoneOne = new QCheckBox(g_sLangTxt_DistanceSearch_SectionOne, ui->m_tableWidget);
    m_cbLLOneAB = new QCheckBox("AB", ui->m_tableWidget);
    m_cbLLOneBC = new QCheckBox("BC", ui->m_tableWidget);
    m_cbLLOneCA = new QCheckBox("CA", ui->m_tableWidget);
    m_cbLLOneABC = new QCheckBox("ABC", ui->m_tableWidget);

    QWidget *containerWidget_11 = new QWidget(this);
    QHBoxLayout *horizontalLayout_11 = new QHBoxLayout(containerWidget_11);
    horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_11->addStretch();
    horizontalLayout_11->addWidget(m_cbLLZoneOne);
    horizontalLayout_11->addStretch();
    ui->m_tableWidget->setCellWidget(6, 1, containerWidget_11);

    QWidget *containerWidget_12 = new QWidget(this);
    QHBoxLayout *horizontalLayout_12 = new QHBoxLayout(containerWidget_12);
    horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_12->addStretch();
    horizontalLayout_12->addWidget(m_cbLLOneAB);
    horizontalLayout_12->addStretch();
    horizontalLayout_12->addWidget(m_cbLLOneBC);
    horizontalLayout_12->addStretch();
    horizontalLayout_12->addWidget(m_cbLLOneCA);
    horizontalLayout_12->addStretch();
    horizontalLayout_12->addWidget(m_cbLLOneABC);
    horizontalLayout_12->addStretch();
    ui->m_tableWidget->setCellWidget(6, 3, containerWidget_12);

    m_cbLLZoneTwo = new QCheckBox(g_sLangTxt_DistanceSearch_SectionTwo, ui->m_tableWidget);
    m_cbLLTwoAB = new QCheckBox("AB", ui->m_tableWidget);
    m_cbLLTwoBC = new QCheckBox("BC", ui->m_tableWidget);
    m_cbLLTwoCA = new QCheckBox("CA", ui->m_tableWidget);
    m_cbLLTwoABC = new QCheckBox("ABC", ui->m_tableWidget);

    QWidget *containerWidget_13 = new QWidget(this);
    QHBoxLayout *horizontalLayout_13 = new QHBoxLayout(containerWidget_13);
    horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_13->addStretch();
    horizontalLayout_13->addWidget(m_cbLLZoneTwo);
    horizontalLayout_13->addStretch();
    ui->m_tableWidget->setCellWidget(7, 1, containerWidget_13);

    QWidget *containerWidget_14 = new QWidget(this);
    QHBoxLayout *horizontalLayout_14 = new QHBoxLayout(containerWidget_14);
    horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_14->addStretch();
    horizontalLayout_14->addWidget(m_cbLLTwoAB);
    horizontalLayout_14->addStretch();
    horizontalLayout_14->addWidget(m_cbLLTwoBC);
    horizontalLayout_14->addStretch();
    horizontalLayout_14->addWidget(m_cbLLTwoCA);
    horizontalLayout_14->addStretch();
    horizontalLayout_14->addWidget(m_cbLLTwoABC);
    horizontalLayout_14->addStretch();
    ui->m_tableWidget->setCellWidget(7, 3, containerWidget_14);

    m_cbLLZoneThree = new QCheckBox(g_sLangTxt_DistanceSearch_SectionThree, ui->m_tableWidget);
    m_cbLLThreeAB = new QCheckBox("AB", ui->m_tableWidget);
    m_cbLLThreeBC = new QCheckBox("BC", ui->m_tableWidget);
    m_cbLLThreeCA = new QCheckBox("CA", ui->m_tableWidget);
    m_cbLLThreeABC = new QCheckBox("ABC", ui->m_tableWidget);

    QWidget *containerWidget_15 = new QWidget(this);
    QHBoxLayout *horizontalLayout_15 = new QHBoxLayout(containerWidget_15);
    horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_15->addStretch();
    horizontalLayout_15->addWidget(m_cbLLZoneThree);
    horizontalLayout_15->addStretch();
    ui->m_tableWidget->setCellWidget(8, 1, containerWidget_15);

    QWidget *containerWidget_16 = new QWidget(this);
    QHBoxLayout *horizontalLayout_16 = new QHBoxLayout(containerWidget_16);
    horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_16->addStretch();
    horizontalLayout_16->addWidget(m_cbLLThreeAB);
    horizontalLayout_16->addStretch();
    horizontalLayout_16->addWidget(m_cbLLThreeBC);
    horizontalLayout_16->addStretch();
    horizontalLayout_16->addWidget(m_cbLLThreeCA);
    horizontalLayout_16->addStretch();
    horizontalLayout_16->addWidget(m_cbLLThreeABC);
    horizontalLayout_16->addStretch();
    ui->m_tableWidget->setCellWidget(8, 3, containerWidget_16);

    m_cbLLZoneFour = new QCheckBox(g_sLangTxt_DistanceSearch_SectionFour, ui->m_tableWidget);
    m_cbLLFourAB = new QCheckBox("AB", ui->m_tableWidget);
    m_cbLLFourBC = new QCheckBox("BC", ui->m_tableWidget);
    m_cbLLFourCA = new QCheckBox("CA", ui->m_tableWidget);
    m_cbLLFourABC = new QCheckBox("ABC", ui->m_tableWidget);

    QWidget *containerWidget_17 = new QWidget(this);
    QHBoxLayout *horizontalLayout_17 = new QHBoxLayout(containerWidget_17);
    horizontalLayout_17->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_17->addStretch();
    horizontalLayout_17->addWidget(m_cbLLZoneFour);
    horizontalLayout_17->addStretch();
    ui->m_tableWidget->setCellWidget(9, 1, containerWidget_17);

    QWidget *containerWidget_18 = new QWidget(this);
    QHBoxLayout *horizontalLayout_18 = new QHBoxLayout(containerWidget_18);
    horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_18->addStretch();
    horizontalLayout_18->addWidget(m_cbLLFourAB);
    horizontalLayout_18->addStretch();
    horizontalLayout_18->addWidget(m_cbLLFourBC);
    horizontalLayout_18->addStretch();
    horizontalLayout_18->addWidget(m_cbLLFourCA);
    horizontalLayout_18->addStretch();
    horizontalLayout_18->addWidget(m_cbLLFourABC);
    horizontalLayout_18->addStretch();
    ui->m_tableWidget->setCellWidget(9, 3, containerWidget_18);

    m_cbLLZoneFive = new QCheckBox(g_sLangTxt_DistanceSearch_SectionFive, ui->m_tableWidget);
    m_cbLLFiveAB = new QCheckBox("AB", ui->m_tableWidget);
    m_cbLLFiveBC = new QCheckBox("BC", ui->m_tableWidget);
    m_cbLLFiveCA = new QCheckBox("CA", ui->m_tableWidget);
    m_cbLLFiveABC = new QCheckBox("ABC", ui->m_tableWidget);

    QWidget *containerWidget_19 = new QWidget(this);
    QHBoxLayout *horizontalLayout_19 = new QHBoxLayout(containerWidget_19);
    horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_19->addStretch();
    horizontalLayout_19->addWidget(m_cbLLZoneFive);
    horizontalLayout_19->addStretch();
    ui->m_tableWidget->setCellWidget(10, 1, containerWidget_19);

    QWidget *containerWidget_20 = new QWidget(this);
    QHBoxLayout *horizontalLayout_20 = new QHBoxLayout(containerWidget_20);
    horizontalLayout_20->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_20->addStretch();
    horizontalLayout_20->addWidget(m_cbLLFiveAB);
    horizontalLayout_20->addStretch();
    horizontalLayout_20->addWidget(m_cbLLFiveBC);
    horizontalLayout_20->addStretch();
    horizontalLayout_20->addWidget(m_cbLLFiveCA);
    horizontalLayout_20->addStretch();
    horizontalLayout_20->addWidget(m_cbLLFiveABC);
    horizontalLayout_20->addStretch();
    ui->m_tableWidget->setCellWidget(10, 3, containerWidget_20);

    m_editActTimeLNOne = new QLineEdit(ui->m_tableWidget);
    m_editActTimeLNTwo = new QLineEdit(ui->m_tableWidget);
    m_editActTimeLNThree = new QLineEdit(ui->m_tableWidget);
    m_editActTimeLNFour = new QLineEdit(ui->m_tableWidget);
    m_editActTimeLNFive = new QLineEdit(ui->m_tableWidget);

    m_editActTimeLLOne = new QLineEdit(ui->m_tableWidget);
    m_editActTimeLLTwo = new QLineEdit(ui->m_tableWidget);
    m_editActTimeLLThree = new QLineEdit(ui->m_tableWidget);
    m_editActTimeLLFour = new QLineEdit(ui->m_tableWidget);
    m_editActTimeLLFive = new QLineEdit(ui->m_tableWidget);

    QWidget *editWidget_1 = new QWidget(this);
    QHBoxLayout *editLayout_1 = new QHBoxLayout(editWidget_1);
    editLayout_1->setContentsMargins(0, 0, 0, 0);
    editLayout_1->addStretch();
    editLayout_1->addWidget(m_editActTimeLNOne);
    editLayout_1->addStretch();
    ui->m_tableWidget->setCellWidget(1, 2, editWidget_1);

    QWidget *editWidget_2 = new QWidget(this);
    QHBoxLayout *editLayout_2 = new QHBoxLayout(editWidget_2);
    editLayout_2->setContentsMargins(0, 0, 0, 0);
    editLayout_2->addStretch();
    editLayout_2->addWidget(m_editActTimeLNTwo);
    editLayout_2->addStretch();
    ui->m_tableWidget->setCellWidget(2, 2, editWidget_2);

    QWidget *editWidget_3 = new QWidget(this);
    QHBoxLayout *editLayout_3 = new QHBoxLayout(editWidget_3);
    editLayout_3->setContentsMargins(0, 0, 0, 0);
    editLayout_3->addStretch();
    editLayout_3->addWidget(m_editActTimeLNThree);
    editLayout_3->addStretch();
    ui->m_tableWidget->setCellWidget(3, 2, editWidget_3);

    QWidget *editWidget_4 = new QWidget(this);
    QHBoxLayout *editLayout_4 = new QHBoxLayout(editWidget_4);
    editLayout_4->setContentsMargins(0, 0, 0, 0);
    editLayout_4->addStretch();
    editLayout_4->addWidget(m_editActTimeLNFour);
    editLayout_4->addStretch();
    ui->m_tableWidget->setCellWidget(4, 2, editWidget_4);

    QWidget *editWidget_5 = new QWidget(this);
    QHBoxLayout *editLayout_5 = new QHBoxLayout(editWidget_5);
    editLayout_5->setContentsMargins(0, 0, 0, 0);
    editLayout_5->addStretch();
    editLayout_5->addWidget(m_editActTimeLNFive);
    editLayout_5->addStretch();
    ui->m_tableWidget->setCellWidget(5, 2, editWidget_5);

    QWidget *editWidget_6 = new QWidget(this);
    QHBoxLayout *editLayout_6 = new QHBoxLayout(editWidget_6);
    editLayout_6->setContentsMargins(0, 0, 0, 0);
    editLayout_6->addStretch();
    editLayout_6->addWidget(m_editActTimeLLOne);
    editLayout_6->addStretch();
    ui->m_tableWidget->setCellWidget(6, 2, editWidget_6);

    QWidget *editWidget_7 = new QWidget(this);
    QHBoxLayout *editLayout_7 = new QHBoxLayout(editWidget_7);
    editLayout_7->setContentsMargins(0, 0, 0, 0);
    editLayout_7->addStretch();
    editLayout_7->addWidget(m_editActTimeLLTwo);
    editLayout_7->addStretch();
    ui->m_tableWidget->setCellWidget(7, 2, editWidget_7);

    QWidget *editWidget_8 = new QWidget(this);
    QHBoxLayout *editLayout_8 = new QHBoxLayout(editWidget_8);
    editLayout_8->setContentsMargins(0, 0, 0, 0);
    editLayout_8->addStretch();
    editLayout_8->addWidget(m_editActTimeLLThree);
    editLayout_8->addStretch();
    ui->m_tableWidget->setCellWidget(8, 2, editWidget_8);

    QWidget *editWidget_9 = new QWidget(this);
    QHBoxLayout *editLayout_9 = new QHBoxLayout(editWidget_9);
    editLayout_9->setContentsMargins(0, 0, 0, 0);
    editLayout_9->addStretch();
    editLayout_9->addWidget(m_editActTimeLLFour);
    editLayout_9->addStretch();
    ui->m_tableWidget->setCellWidget(9, 2, editWidget_9);

    QWidget *editWidget_10 = new QWidget(this);
    QHBoxLayout *editLayout_10 = new QHBoxLayout(editWidget_10);
    editLayout_10->setContentsMargins(0, 0, 0, 0);
    editLayout_10->addStretch();
    editLayout_10->addWidget(m_editActTimeLLFive);
    editLayout_10->addStretch();
    ui->m_tableWidget->setCellWidget(10, 2, editWidget_10);

    //时间定值不可编辑
    m_editActTimeLNOne->setEnabled(false);
    m_editActTimeLNTwo->setEnabled(false);
    m_editActTimeLNThree->setEnabled(false);
    m_editActTimeLNFour->setEnabled(false);
    m_editActTimeLNFive->setEnabled(false);
    m_editActTimeLLOne->setEnabled(false);
    m_editActTimeLLTwo->setEnabled(false);
    m_editActTimeLLThree->setEnabled(false);
    m_editActTimeLLFour->setEnabled(false);
    m_editActTimeLLFive->setEnabled(false);

    m_cbLNZoneOne->setEnabled(false);
    m_cbLNZoneTwo->setEnabled(false);
    m_cbLNZoneThree->setEnabled(false);
    m_cbLNZoneFour->setEnabled(false);
    m_cbLNZoneFive->setEnabled(false);
    m_cbLLZoneOne->setEnabled(false);
    m_cbLLZoneTwo->setEnabled(false);
    m_cbLLZoneThree->setEnabled(false);
    m_cbLLZoneFour->setEnabled(false);
    m_cbLLZoneFive->setEnabled(false);

    ui->m_btnOk->setText(g_sLangTxt_OK);
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);

    return;
}

void QDistanceSearchBatchAddMultDlg::InitConnect()
{
    connect(m_cbLNZoneOne, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLNZoneOne_StateChanged(int)));
    connect(m_cbLNZoneTwo, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLNZoneTwo_StateChanged(int)));
    connect(m_cbLNZoneThree, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLNZoneThree_StateChanged(int)));
    connect(m_cbLNZoneFour, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLNZoneFour_StateChanged(int)));
    connect(m_cbLNZoneFive, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLNZoneFive_StateChanged(int)));

    connect(m_cbLLZoneOne, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLLZoneOne_StateChanged(int)));
    connect(m_cbLLZoneTwo, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLLZoneTwo_StateChanged(int)));
    connect(m_cbLLZoneThree, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLLZoneThree_StateChanged(int)));
    connect(m_cbLLZoneFour, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLLZoneFour_StateChanged(int)));
    connect(m_cbLLZoneFive, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbLLZoneFive_StateChanged(int)));

    connect(m_editActTimeLNOne,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLNOne_editingFinished()));
    connect(m_editActTimeLNTwo,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLNTwo_editingFinished()));
    connect(m_editActTimeLNThree,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLNThree_editingFinished()));
    connect(m_editActTimeLNFour,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLNFour_editingFinished()));
    connect(m_editActTimeLNFive,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLNFive_editingFinished()));

    connect(m_editActTimeLLOne,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLLOne_editingFinished()));
    connect(m_editActTimeLLTwo,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLLTwo_editingFinished()));
    connect(m_editActTimeLLThree,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLLThree_editingFinished()));
    connect(m_editActTimeLLFour,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLLFour_editingFinished()));
    connect(m_editActTimeLLFive,SIGNAL(editingFinished()),this,SLOT(on_m_editActTimeLLFive_editingFinished()));

}

void QDistanceSearchBatchAddMultDlg::SetValueToPage(CDvmData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone1_Check)
    {
        m_cbLNZoneOne->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone2_Check)
    {
        m_cbLNZoneTwo->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone3_Check)
    {
        m_cbLNZoneThree->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone4_Check)
    {
        m_cbLNZoneFour->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone5_Check)
    {
        m_cbLNZoneFive->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone1_Check)
    {
        m_cbLLZoneOne->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone2_Check)
    {
        m_cbLLZoneTwo->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone3_Check)
    {
        m_cbLLZoneThree->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone4_Check)
    {
        m_cbLLZoneFour->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone5_Check)
    {
        m_cbLLZoneFive->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone1)
    {
        m_editActTimeLNOne->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone2)
    {
        m_editActTimeLNTwo->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone3)
    {
        m_editActTimeLNThree->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone4)
    {
        m_editActTimeLNFour->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone5)
    {
        m_editActTimeLNFive->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone1)
    {
        m_editActTimeLLOne->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone2)
    {
        m_editActTimeLLTwo->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone3)
    {
        m_editActTimeLLThree->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone4)
    {
        m_editActTimeLLFour->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone5)
    {
        m_editActTimeLLFive->setText(DistanceSearchValueCheck(pData->m_strValue, SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN1FaultTypeAE_Check)
    {
        m_cbLNOneAN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN1FaultTypeBE_Check)
    {
        m_cbLNOneBN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN1FaultTypeCE_Check)
    {
        m_cbLNOneCN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN2FaultTypeAE_Check)
    {
        m_cbLNTwoAN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN2FaultTypeBE_Check)
    {
        m_cbLNTwoBN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN2FaultTypeCE_Check)
    {
        m_cbLNTwoCN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN3FaultTypeAE_Check)
    {
        m_cbLNThreeAN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN3FaultTypeBE_Check)
    {
        m_cbLNThreeBN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN3FaultTypeCE_Check)
    {
        m_cbLNThreeCN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN4FaultTypeAE_Check)
    {
        m_cbLNFourAN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN4FaultTypeBE_Check)
    {
        m_cbLNFourBN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN4FaultTypeCE_Check)
    {
        m_cbLNFourCN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN5FaultTypeAE_Check)
    {
        m_cbLNFiveAN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN5FaultTypeBE_Check)
    {
        m_cbLNFiveBN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN5FaultTypeCE_Check)
    {
        m_cbLNFiveCN->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeAB_Check)
    {
        m_cbLLOneAB->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeBC_Check)
    {
        m_cbLLOneBC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeCA_Check)
    {
        m_cbLLOneCA->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeABC_Check)
    {
        m_cbLLOneABC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeAB_Check)
    {
        m_cbLLTwoAB->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeBC_Check)
    {
        m_cbLLTwoBC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeCA_Check)
    {
        m_cbLLTwoCA->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeABC_Check)
    {
        m_cbLLTwoABC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeAB_Check)
    {
        m_cbLLThreeAB->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeBC_Check)
    {
        m_cbLLThreeBC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeCA_Check)
    {
        m_cbLLThreeCA->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeABC_Check)
    {
        m_cbLLThreeABC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeAB_Check)
    {
        m_cbLLFourAB->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeBC_Check)
    {
        m_cbLLFourBC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeCA_Check)
    {
        m_cbLLFourCA->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeABC_Check)
    {
        m_cbLLFourABC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeAB_Check)
    {
        m_cbLLFiveAB->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeBC_Check)
    {
        m_cbLLFiveBC->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeCA_Check)
    {
        m_cbLLFiveCA->setChecked(pData->m_strValue == "1");
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeABC_Check)
    {
        m_cbLLFiveABC->setChecked(pData->m_strValue == "1");
    }

    return;
}

void QDistanceSearchBatchAddMultDlg::SetDatas(CDataGroup *pParas)
{
    if(pParas == NULL)
        return;

    m_pCurrDataGroup = pParas;
    POS pos = pParas->GetHeadPosition();
    while(pos != NULL)
    {
        CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
        SetValueToPage(pData);
    }

    //根据特性曲线图获取使能状态和动作时间
    UpdateFromCharact();

    on_m_cbLNZoneOne_StateChanged(m_cbLNZoneOne->checkState());
    on_m_cbLNZoneTwo_StateChanged(m_cbLNZoneTwo->checkState());
    on_m_cbLNZoneThree_StateChanged(m_cbLNZoneThree->checkState());
    on_m_cbLNZoneFour_StateChanged(m_cbLNZoneFour->checkState());
    on_m_cbLNZoneFive_StateChanged(m_cbLNZoneFive->checkState());
    on_m_cbLLZoneOne_StateChanged(m_cbLLZoneOne->checkState());
    on_m_cbLLZoneTwo_StateChanged(m_cbLLZoneTwo->checkState());
    on_m_cbLLZoneThree_StateChanged(m_cbLLZoneThree->checkState());
    on_m_cbLLZoneFour_StateChanged(m_cbLLZoneFour->checkState());
    on_m_cbLLZoneFive_StateChanged(m_cbLLZoneFive->checkState());

    return;
}

void QDistanceSearchBatchAddMultDlg::UpdateFromCharact()
{
    //根据故障类型和区段值查找对应曲线 并将曲线参数设置到MacroTest
    CCharacteristic *pChar = NULL;
    CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
    POS pos = pCharacteristics->GetHeadPosition();
    while (pos != NULL)
    {
        CExBaseObject *pObj = pCharacteristics->GetNext(pos);
        if (pObj->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
            continue;

        CCharacteristic *pCharTemp = (CCharacteristic *)pObj;
        //获取勾选使用的曲线
        if (pCharTemp->m_nUse != 1)
        {
            continue;
        }

        CExBaseList* pParas = (CExBaseList*)pCharTemp->GetCharInterface();
        CCharInterfaceVariable *pPara = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING);
        CString strTSetting;
        if(pPara != NULL)
            strTSetting = pPara->m_strValue;

        if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
        {
            if(pCharTemp->m_strIndex == "2")    //1段
            {
                m_cbLNZoneOne->setEnabled(true);
                m_cbLLZoneOne->setEnabled(true);
                m_editActTimeLNOne->setText(strTSetting);
                m_editActTimeLLOne->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "3")    //2段
            {
                m_cbLNZoneTwo->setEnabled(true);
                m_cbLLZoneTwo->setEnabled(true);
                m_editActTimeLNTwo->setText(strTSetting);
                m_editActTimeLLTwo->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "4")    //3段
            {
                m_cbLNZoneThree->setEnabled(true);
                m_cbLLZoneThree->setEnabled(true);
                m_editActTimeLNThree->setText(strTSetting);
                m_editActTimeLLThree->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "5")    //4段
            {
                m_cbLNZoneFour->setEnabled(true);
                m_cbLLZoneFour->setEnabled(true);
                m_editActTimeLNFour->setText(strTSetting);
                m_editActTimeLLFour->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "6")    //5段
            {
                m_cbLNZoneFive->setEnabled(true);
                m_cbLLZoneFive->setEnabled(true);
                m_editActTimeLNFive->setText(strTSetting);
                m_editActTimeLLFive->setText(strTSetting);
            }
        }
        else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LN)
        {
            if(pCharTemp->m_strIndex == "2")    //1段
            {
                m_cbLNZoneOne->setEnabled(true);
                m_editActTimeLNOne->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "3")    //2段
            {
                m_cbLNZoneTwo->setEnabled(true);
                m_editActTimeLNTwo->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "4")    //3段
            {
                m_cbLNZoneThree->setEnabled(true);
                m_editActTimeLNThree->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "5")    //4段
            {
                m_cbLNZoneFour->setEnabled(true);
                m_editActTimeLNFour->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "6")    //5段
            {
                m_cbLNZoneFive->setEnabled(true);
                m_editActTimeLNFive->setText(strTSetting);
            }
        }
        else if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_LL)
        {
            if(pCharTemp->m_strIndex == "2")    //1段
            {
                m_cbLLZoneOne->setEnabled(true);
                m_editActTimeLLOne->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "3")    //2段
            {
                m_cbLLZoneTwo->setEnabled(true);
                m_editActTimeLLTwo->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "4")    //3段
            {
                m_cbLLZoneThree->setEnabled(true);
                m_editActTimeLLThree->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "5")    //4段
            {
                m_cbLLZoneFour->setEnabled(true);
                m_editActTimeLLFour->setText(strTSetting);
            }
            else if(pCharTemp->m_strIndex == "6")    //5段
            {
                m_cbLLZoneFive->setEnabled(true);
                m_editActTimeLLFive->setText(strTSetting);
            }
        }
    }
}

void QDistanceSearchBatchAddMultDlg::GetPageToValue(CDvmData *pData)
{
    if(pData == NULL)
        return;

    if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone1_Check)
    {
        pData->m_strValue.setNum(m_cbLNZoneOne->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone2_Check)
    {
        pData->m_strValue.setNum(m_cbLNZoneTwo->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone3_Check)
    {
        pData->m_strValue.setNum(m_cbLNZoneThree->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone4_Check)
    {
        pData->m_strValue.setNum(m_cbLNZoneFour->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone5_Check)
    {
        pData->m_strValue.setNum(m_cbLNZoneFive->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone1_Check)
    {
        pData->m_strValue.setNum(m_cbLLZoneOne->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone2_Check)
    {
        pData->m_strValue.setNum(m_cbLLZoneTwo->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone3_Check)
    {
        pData->m_strValue.setNum(m_cbLLZoneThree->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone4_Check)
    {
        pData->m_strValue.setNum(m_cbLLZoneFour->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone5_Check)
    {
        pData->m_strValue.setNum(m_cbLLZoneFive->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone1)
    {
        pData->m_strValue = m_editActTimeLNOne->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone2)
    {
        pData->m_strValue = m_editActTimeLNTwo->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone3)
    {
        pData->m_strValue = m_editActTimeLNThree->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone4)
    {
        pData->m_strValue = m_editActTimeLNFour->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone5)
    {
        pData->m_strValue = m_editActTimeLNFive->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone1)
    {
        pData->m_strValue = m_editActTimeLLOne->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone2)
    {
        pData->m_strValue = m_editActTimeLLTwo->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone3)
    {
        pData->m_strValue = m_editActTimeLLThree->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone4)
    {
        pData->m_strValue = m_editActTimeLLFour->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone5)
    {
        pData->m_strValue = m_editActTimeLLFive->text();
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN1FaultTypeAE_Check)
    {
        pData->m_strValue.setNum(m_cbLNOneAN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN1FaultTypeBE_Check)
    {
        pData->m_strValue.setNum(m_cbLNOneBN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN1FaultTypeCE_Check)
    {
        pData->m_strValue.setNum(m_cbLNOneCN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN2FaultTypeAE_Check)
    {
        pData->m_strValue.setNum(m_cbLNTwoAN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN2FaultTypeBE_Check)
    {
        pData->m_strValue.setNum(m_cbLNTwoBN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN2FaultTypeCE_Check)
    {
        pData->m_strValue.setNum(m_cbLNTwoCN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN3FaultTypeAE_Check)
    {
        pData->m_strValue.setNum(m_cbLNThreeAN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN3FaultTypeBE_Check)
    {
        pData->m_strValue.setNum(m_cbLNThreeBN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN3FaultTypeCE_Check)
    {
        pData->m_strValue.setNum(m_cbLNThreeCN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN4FaultTypeAE_Check)
    {
        pData->m_strValue.setNum(m_cbLNFourAN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN4FaultTypeBE_Check)
    {
        pData->m_strValue.setNum(m_cbLNFourBN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN4FaultTypeCE_Check)
    {
        pData->m_strValue.setNum(m_cbLNFourCN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN5FaultTypeAE_Check)
    {
        pData->m_strValue.setNum(m_cbLNFiveAN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN5FaultTypeBE_Check)
    {
        pData->m_strValue.setNum(m_cbLNFiveBN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN5FaultTypeCE_Check)
    {
        pData->m_strValue.setNum(m_cbLNFiveCN->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeAB_Check)
    {
        pData->m_strValue.setNum(m_cbLLOneAB->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeBC_Check)
    {
        pData->m_strValue.setNum(m_cbLLOneBC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeCA_Check)
    {
        pData->m_strValue.setNum(m_cbLLOneCA->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeABC_Check)
    {
        pData->m_strValue.setNum(m_cbLLOneABC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeAB_Check)
    {
        pData->m_strValue.setNum(m_cbLLTwoAB->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeBC_Check)
    {
        pData->m_strValue.setNum(m_cbLLTwoBC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeCA_Check)
    {
        pData->m_strValue.setNum(m_cbLLTwoCA->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeABC_Check)
    {
        pData->m_strValue.setNum(m_cbLLTwoABC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeAB_Check)
    {
        pData->m_strValue.setNum(m_cbLLThreeAB->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeBC_Check)
    {
        pData->m_strValue.setNum(m_cbLLThreeBC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeCA_Check)
    {
        pData->m_strValue.setNum(m_cbLLThreeCA->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeABC_Check)
    {
        pData->m_strValue.setNum(m_cbLLThreeABC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeAB_Check)
    {
        pData->m_strValue.setNum(m_cbLLFourAB->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeBC_Check)
    {
        pData->m_strValue.setNum(m_cbLLFourBC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeCA_Check)
    {
        pData->m_strValue.setNum(m_cbLLFourCA->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeABC_Check)
    {
        pData->m_strValue.setNum(m_cbLLFourABC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeAB_Check)
    {
        pData->m_strValue.setNum(m_cbLLFiveAB->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeBC_Check)
    {
        pData->m_strValue.setNum(m_cbLLFiveBC->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeCA_Check)
    {
        pData->m_strValue.setNum(m_cbLLFiveCA->isChecked());
    }
    else if(pData->m_strID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeABC_Check)
    {
        pData->m_strValue.setNum(m_cbLLFiveABC->isChecked());
    }
}

void QDistanceSearchBatchAddMultDlg::CheckAllPresence()
{
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone1_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone2_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone3_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone4_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LNZone5_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone1_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone2_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone3_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone4_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LLZone5_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone1);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone2);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone3);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone4);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLN_Zone5);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone1);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone2);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone3);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone4);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_TSetingLL_Zone5);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN1FaultTypeAE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN1FaultTypeBE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN1FaultTypeCE_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN2FaultTypeAE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN2FaultTypeBE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN2FaultTypeCE_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN3FaultTypeAE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN3FaultTypeBE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN3FaultTypeCE_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN4FaultTypeAE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN4FaultTypeBE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN4FaultTypeCE_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN5FaultTypeAE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN5FaultTypeBE_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LN5FaultTypeCE_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeAB_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeBC_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeCA_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL1FaultTypeABC_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeAB_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeBC_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeCA_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL2FaultTypeABC_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeAB_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeBC_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeCA_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL3FaultTypeABC_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeAB_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeBC_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeCA_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL4FaultTypeABC_Check);

    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeAB_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeBC_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeCA_Check);
    DistanceSearchCheckParaExist(m_pCurrDataGroup, STT_MULTI_MACRO_DISTANCESEARCH_PARAS_BATCH_MULT_ID_LL5FaultTypeABC_Check);

    return;
}

void QDistanceSearchBatchAddMultDlg::GetDatas(CDataGroup *pParas)
{
    if(pParas == NULL)
        return;

    m_pCurrDataGroup = pParas;
    CheckAllPresence();

    POS pos = pParas->GetHeadPosition();
    while(pos!=NULL)
    {
        CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
        GetPageToValue(pData);
    }

    return;
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLNZoneOne_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLNZoneOne->isEnabled())
    {
        m_cbLNOneAN->setEnabled(true);
        m_cbLNOneBN->setEnabled(true);
        m_cbLNOneCN->setEnabled(true);
    }
    else
    {
        m_cbLNOneAN->setEnabled(false);
        m_cbLNOneBN->setEnabled(false);
        m_cbLNOneCN->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLNZoneTwo_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLNZoneTwo->isEnabled())
    {
        m_cbLNTwoAN->setEnabled(true);
        m_cbLNTwoBN->setEnabled(true);
        m_cbLNTwoCN->setEnabled(true);
    }
    else
    {
        m_cbLNTwoAN->setEnabled(false);
        m_cbLNTwoBN->setEnabled(false);
        m_cbLNTwoCN->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLNZoneThree_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLNZoneThree->isEnabled())
    {
        m_cbLNThreeAN->setEnabled(true);
        m_cbLNThreeBN->setEnabled(true);
        m_cbLNThreeCN->setEnabled(true);
    }
    else
    {
        m_cbLNThreeAN->setEnabled(false);
        m_cbLNThreeBN->setEnabled(false);
        m_cbLNThreeCN->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLNZoneFour_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLNZoneFour->isEnabled())
    {
        m_cbLNFourAN->setEnabled(true);
        m_cbLNFourBN->setEnabled(true);
        m_cbLNFourCN->setEnabled(true);
    }
    else
    {
        m_cbLNFourAN->setEnabled(false);
        m_cbLNFourBN->setEnabled(false);
        m_cbLNFourCN->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLNZoneFive_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLNZoneFive->isEnabled())
    {
        m_cbLNFiveAN->setEnabled(true);
        m_cbLNFiveBN->setEnabled(true);
        m_cbLNFiveCN->setEnabled(true);
    }
    else
    {
        m_cbLNFiveAN->setEnabled(false);
        m_cbLNFiveBN->setEnabled(false);
        m_cbLNFiveCN->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLLZoneOne_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLLZoneOne->isEnabled())
    {
        m_editActTimeLLOne->setEnabled(true);
        m_cbLLOneAB->setEnabled(true);
        m_cbLLOneBC->setEnabled(true);
        m_cbLLOneCA->setEnabled(true);
        m_cbLLOneABC->setEnabled(true);
    }
    else
    {
        m_editActTimeLLOne->setEnabled(false);
        m_cbLLOneAB->setEnabled(false);
        m_cbLLOneBC->setEnabled(false);
        m_cbLLOneCA->setEnabled(false);
        m_cbLLOneABC->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLLZoneTwo_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLLZoneTwo->isEnabled())
    {
        m_editActTimeLLTwo->setEnabled(true);
        m_cbLLTwoAB->setEnabled(true);
        m_cbLLTwoBC->setEnabled(true);
        m_cbLLTwoCA->setEnabled(true);
        m_cbLLTwoABC->setEnabled(true);
    }
    else
    {
        m_editActTimeLLTwo->setEnabled(false);
        m_cbLLTwoAB->setEnabled(false);
        m_cbLLTwoBC->setEnabled(false);
        m_cbLLTwoCA->setEnabled(false);
        m_cbLLTwoABC->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLLZoneThree_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLLZoneThree->isEnabled())
    {
        m_editActTimeLLThree->setEnabled(true);
        m_cbLLThreeAB->setEnabled(true);
        m_cbLLThreeBC->setEnabled(true);
        m_cbLLThreeCA->setEnabled(true);
        m_cbLLThreeABC->setEnabled(true);
    }
    else
    {
        m_editActTimeLLThree->setEnabled(false);
        m_cbLLThreeAB->setEnabled(false);
        m_cbLLThreeBC->setEnabled(false);
        m_cbLLThreeCA->setEnabled(false);
        m_cbLLThreeABC->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLLZoneFour_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLLZoneFour->isEnabled())
    {
        m_editActTimeLLFour->setEnabled(true);
        m_cbLLFourAB->setEnabled(true);
        m_cbLLFourBC->setEnabled(true);
        m_cbLLFourCA->setEnabled(true);
        m_cbLLFourABC->setEnabled(true);
    }
    else
    {
        m_editActTimeLLFour->setEnabled(false);
        m_cbLLFourAB->setEnabled(false);
        m_cbLLFourBC->setEnabled(false);
        m_cbLLFourCA->setEnabled(false);
        m_cbLLFourABC->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_cbLLZoneFive_StateChanged(int state)
{
    if(Qt::Checked == state && m_cbLLZoneFive->isEnabled())
    {
        m_editActTimeLLFive->setEnabled(true);
        m_cbLLFiveAB->setEnabled(true);
        m_cbLLFiveBC->setEnabled(true);
        m_cbLLFiveCA->setEnabled(true);
        m_cbLLFiveABC->setEnabled(true);
    }
    else
    {
        m_editActTimeLLFive->setEnabled(false);
        m_cbLLFiveAB->setEnabled(false);
        m_cbLLFiveBC->setEnabled(false);
        m_cbLLFiveCA->setEnabled(false);
        m_cbLLFiveABC->setEnabled(false);
    }
}

void QDistanceSearchBatchAddMultDlg::on_m_btnOk_clicked()
{
    GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
    this->done(Accepted);
}

void QDistanceSearchBatchAddMultDlg::on_m_btnCancel_clicked()
{
    this->close();
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLNOne_editingFinished()
{
    m_editActTimeLNOne->setText(DistanceSearchValueCheck(m_editActTimeLNOne->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLNTwo_editingFinished()
{
    m_editActTimeLNTwo->setText(DistanceSearchValueCheck(m_editActTimeLNTwo->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLNThree_editingFinished()
{
    m_editActTimeLNThree->setText(DistanceSearchValueCheck(m_editActTimeLNThree->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLNFour_editingFinished()
{
    m_editActTimeLNFour->setText(DistanceSearchValueCheck(m_editActTimeLNFour->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLNFive_editingFinished()
{
    m_editActTimeLNFive->setText(DistanceSearchValueCheck(m_editActTimeLNFive->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLLOne_editingFinished()
{
    m_editActTimeLLOne->setText(DistanceSearchValueCheck(m_editActTimeLLOne->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLLTwo_editingFinished()
{
    m_editActTimeLLTwo->setText(DistanceSearchValueCheck(m_editActTimeLLTwo->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLLThree_editingFinished()
{
    m_editActTimeLLThree->setText(DistanceSearchValueCheck(m_editActTimeLLThree->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLLFour_editingFinished()
{
    m_editActTimeLLFour->setText(DistanceSearchValueCheck(m_editActTimeLLFour->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}

void QDistanceSearchBatchAddMultDlg::on_m_editActTimeLLFive_editingFinished()
{
    m_editActTimeLLFive->setText(DistanceSearchValueCheck(m_editActTimeLLFive->text(), SETTINGTIME_MAX, SETTINGTIME_MIN, 3));
}
