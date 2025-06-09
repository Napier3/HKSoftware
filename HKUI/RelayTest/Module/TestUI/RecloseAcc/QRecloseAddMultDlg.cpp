#include "QRecloseAddMultDlg.h"
#include <QLabel>
#include "../../UI/SoftKeyboard/SoftKeyBoard.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../OSInterface/QT/XMessageBox.h"
#include "../../Module/SttTestCtrl/SttTestAppBase.h"
#include "../../XLangResource_Native.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "SttMultiMacroRecloseAccParasDefine.h"

QRecloseAddMultDlg::QRecloseAddMultDlg(QWidget *parent) : QDialog(parent),
ui(new Ui::QRecloseAddMultDlg)
{
	ui->setupUi(this);
    //installEventFilter(this);

    InitUI();
    initFont();
	initConnect();

}

QRecloseAddMultDlg::~QRecloseAddMultDlg()
{
	delete ui;
}

//20241024 wanmj
void QRecloseAddMultDlg::InitUI()
{
    CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
    strPngPath = _P_GetResourcePath();
    strPngPath = strPngPath + _T("images/Reclose.png");
#else
    strPngPath =  ":/ctrls/images/Reclose.png";
#endif
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setWindowTitle(g_sLangTxt_Button_AddMultDlg);

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_UXMODE);
    ui->m_pCmbDrawvoltage->ShowBaseList(pDataType);

    ui->m_LabTestItem->setText(g_sLangTxt_ActionTime_TestItem);
    ui->m_pNoPreCheck->setText(g_sLangTxt_RecloseAcc_NoPre);
    ui->m_pSamPerCheck->setText(g_sLangTxt_RecloseAcc_SamPer);
    ui->m_pFrequencyCheck->setText(g_sLangTxt_RecloseAcc_Frequency);
    ui->m_pRecCheck->setText(g_sLangTxt_RecloseAcc_AutoReclose);
    ui->m_pAftAccCheck->setText(g_sLangTxt_RecloseAcc_AftAcc);
    ui->m_LabSetValue->setText(g_sLangTxt_State_SettingValue);
    ui->m_pLabNoPreSet->setText(g_sLangTxt_RecloseAcc_NoPreSet);
    ui->m_pLabSynAngle->setText(g_sLangTxt_RecloseAcc_SynAngle);
    ui->m_pLabFrequency->setText(g_sLangTxt_RecloseAcc_Fre);
    ui->m_pLabFault->setText(g_sLangTxt_ActionTime_FaultPhase);
    ui->m_pMultiple->setText(g_sLangTxt_RecloseAcc_UxMode);

    ui->m_pFaultDiffGroupBox_3->setTitle(g_sLangTxt_Native_Fault);
    ui->m_pModeGroupBox_2->setTitle(g_sLangTxt_State_ZeroCoeff);
    ui->m_pLabZ1->setText(g_sLangTxt_RecloseAcc_Z);
    ui->m_pLabZ1Ph->setText(g_sLangTxt_Gradient_ImpAngle);
    ui->m_pLabISet1->setText(g_sLangTxt_State_ShortI);
    ui->m_pLabK0Mode->setText(g_sLangTxt_RecloseAcc_K0Mode);
    ui->m_pLabDrawvoltage->setText(g_sLangTxt_RecloseAcc_UxMode);
    ui->m_LabActionTime->setText(g_sLangTxt_Manual_ActionTime);
    ui->m_LabRecloseTime->setText(g_sLangTxt_RecloseAcc_RecloseTime);

    ui->m_pBtnResultAssess->setText(g_sLangTxt_StateEstimate_ResultEstimate);
    ui->m_pBtnOk->setText(g_sLangTxt_OK);
    ui->m_pBtnExit->setText(g_sLangTxt_Cancel);
}

void QRecloseAddMultDlg::initUI()
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

    ui->m_pCmbK0Mode->addItem("|K0|,Phi(K0)");
    ui->m_pCmbK0Mode->addItem("RERL,XEXL");
    ui->m_pCmbK0Mode->addItem("|Z0/Z1|,Phi(Z0/Z1)");

    Qt::CheckState NoPrestate = ui->m_pNoPreCheck->checkState();
    if(NoPrestate)
    {
        ui->m_pNoPreFaultTypeACheck->setEnabled(true);
        ui->m_pNoPreFaultTypeBCheck->setEnabled(true);
        ui->m_pNoPreFaultTypeCCheck->setEnabled(true);
        ui->m_pNoPreFaultTypeABCheck->setEnabled(true);
        ui->m_pNoPreFaultTypeBCCheck->setEnabled(true);
        ui->m_pNoPreFaultTypeCACheck->setEnabled(true);
        ui->m_pNoPreFaultTypeABCCheck->setEnabled(true);
        ui->m_pNoPreRate095Check->setEnabled(true);
        ui->m_pNoPreRate105Check->setEnabled(true);
        ui->m_pEditNoPreSet->setEnabled(true);
    }
    else
    {
        ui->m_pNoPreFaultTypeACheck->setEnabled(false);
        ui->m_pNoPreFaultTypeBCheck->setEnabled(false);
        ui->m_pNoPreFaultTypeCCheck->setEnabled(false);
        ui->m_pNoPreFaultTypeABCheck->setEnabled(false);
        ui->m_pNoPreFaultTypeBCCheck->setEnabled(false);
        ui->m_pNoPreFaultTypeCACheck->setEnabled(false);
        ui->m_pNoPreFaultTypeABCCheck->setEnabled(false);
        ui->m_pNoPreRate095Check->setEnabled(false);
        ui->m_pNoPreRate105Check->setEnabled(false);
        ui->m_pEditNoPreSet->setEnabled(false);
    }

    Qt::CheckState SamPerstate = ui->m_pSamPerCheck->checkState();
    if(SamPerstate)
    {
        ui->m_pSamPerFaultTypeACheck->setEnabled(true);
        ui->m_pSamPerFaultTypeBCheck->setEnabled(true);
        ui->m_pSamPerFaultTypeCCheck->setEnabled(true);
        ui->m_pSamPerFaultTypeABCheck->setEnabled(true);
        ui->m_pSamPerFaultTypeBCCheck->setEnabled(true);
        ui->m_pSamPerFaultTypeCACheck->setEnabled(true);
        ui->m_pSamPerFaultTypeABCCheck->setEnabled(true);
        ui->m_pSamPerRate095Check->setEnabled(true);
        ui->m_pSamPerRate105Check->setEnabled(true);
        ui->m_pEditSynAngleSetting->setEnabled(true);
    }
    else
    {
        ui->m_pSamPerFaultTypeACheck->setEnabled(false);
        ui->m_pSamPerFaultTypeBCheck->setEnabled(false);
        ui->m_pSamPerFaultTypeCCheck->setEnabled(false);
        ui->m_pSamPerFaultTypeABCheck->setEnabled(false);
        ui->m_pSamPerFaultTypeBCCheck->setEnabled(false);
        ui->m_pSamPerFaultTypeCACheck->setEnabled(false);
        ui->m_pSamPerFaultTypeABCCheck->setEnabled(false);
        ui->m_pSamPerRate095Check->setEnabled(false);
        ui->m_pSamPerRate105Check->setEnabled(false);
        ui->m_pEditSynAngleSetting->setEnabled(false);
    }

    Qt::CheckState AftAccstate = ui->m_pAftAccCheck->checkState();
    if(AftAccstate)
    {
        ui->m_pAftAccFaultTypeACheck->setEnabled(true);
        ui->m_pAftAccFaultTypeBCheck->setEnabled(true);
        ui->m_pAftAccFaultTypeCCheck->setEnabled(true);
        ui->m_pAftAccFaultTypeABCheck->setEnabled(true);
        ui->m_pAftAccFaultTypeBCCheck->setEnabled(true);
        ui->m_pAftAccFaultTypeCACheck->setEnabled(true);
        ui->m_pAftAccFaultTypeABCCheck->setEnabled(true);
    }
    else
    {
        ui->m_pAftAccFaultTypeACheck->setEnabled(false);
        ui->m_pAftAccFaultTypeBCheck->setEnabled(false);
        ui->m_pAftAccFaultTypeCCheck->setEnabled(false);
        ui->m_pAftAccFaultTypeABCheck->setEnabled(false);
        ui->m_pAftAccFaultTypeBCCheck->setEnabled(false);
        ui->m_pAftAccFaultTypeCACheck->setEnabled(false);
        ui->m_pAftAccFaultTypeABCCheck->setEnabled(false);
    }


    Qt::CheckState Frequencystate = ui->m_pFrequencyCheck->checkState();
    if(Frequencystate)
    {
        ui->m_pFrequencyACheck->setEnabled(true);
        ui->m_pFrequencyBCheck->setEnabled(true);
        ui->m_pFrequencyCCheck->setEnabled(true);
        ui->m_pFrequencyABCheck->setEnabled(true);
        ui->m_pFrequencyBCCheck->setEnabled(true);
        ui->m_pFrequencyCACheck->setEnabled(true);
        ui->m_pFrequencyABCCheck->setEnabled(true);
        ui->m_pFrequency095Check->setEnabled(true);
        ui->m_pFrequency105Check->setEnabled(true);
        ui->m_pEditFrequency->setEnabled(true);
    }
    else
    {
        ui->m_pFrequencyACheck->setEnabled(false);
        ui->m_pFrequencyBCheck->setEnabled(false);
        ui->m_pFrequencyCCheck->setEnabled(false);
        ui->m_pFrequencyABCheck->setEnabled(false);
        ui->m_pFrequencyBCCheck->setEnabled(false);
        ui->m_pFrequencyCACheck->setEnabled(false);
        ui->m_pFrequencyABCCheck->setEnabled(false);
        ui->m_pFrequency095Check->setEnabled(false);
        ui->m_pFrequency105Check->setEnabled(false);
        ui->m_pEditFrequency->setEnabled(false);
    }

    Qt::CheckState Recstate = ui->m_pRecCheck->checkState();
    if(Recstate)
    {
        ui->m_pRecFaultTypeACheck->setEnabled(true);
        ui->m_pRecFaultTypeBCheck->setEnabled(true);
        ui->m_pRecFaultTypeCCheck->setEnabled(true);
        ui->m_pRecFaultTypeABCheck->setEnabled(true);
        ui->m_pRecFaultTypeBCCheck->setEnabled(true);
        ui->m_pRecFaultTypeCACheck->setEnabled(true);
        ui->m_pRecFaultTypeABCCheck->setEnabled(true);
    }
    else
    {
        ui->m_pRecFaultTypeACheck->setEnabled(false);
        ui->m_pRecFaultTypeBCheck->setEnabled(false);
        ui->m_pRecFaultTypeCCheck->setEnabled(false);
        ui->m_pRecFaultTypeABCheck->setEnabled(false);
        ui->m_pRecFaultTypeBCCheck->setEnabled(false);
        ui->m_pRecFaultTypeCACheck->setEnabled(false);
        ui->m_pRecFaultTypeABCCheck->setEnabled(false);
    }



    ui->m_pEditZ1->setFixedWidth(120);
    ui->m_pEditZ1Ph->setFixedWidth(120);
    ui->m_pEditISet1->setFixedWidth(120);
    ui->m_pCmbK0Mode->setFixedWidth(180);
    ui->m_pEditKlKr->setFixedWidth(180);
    ui->m_pEditAngKx->setFixedWidth(180);
    ui->m_pCmbDrawvoltage->setFixedWidth(180);


    ui->m_pEditNoPreSet->setFixedWidth(120);
    ui->m_pEditSynAngleSetting->setFixedWidth(120);
    ui->m_pEditFrequency->setFixedWidth(120);
    ui->m_EditActionTime->setFixedWidth(180);
    ui->m_EditRecloseTime->setFixedWidth(180);


    ui->m_pBtnResultAssess->setFixedWidth(120);
	//ui->m_pBtnCommonParas->setFixedWidth(120);

	resize(900, 300);

    //initDatas();
}

void QRecloseAddMultDlg::initFont()
{
	ui->m_pLabNoPreSet->setFont(*g_pSttGlobalFont);   //无压定值
	ui->m_pLabSynAngle->setFont(*g_pSttGlobalFont);  //合闸角度
	ui->m_pLabZ1->setFont(*g_pSttGlobalFont);         //阻抗(故障)
	ui->m_pLabZ1Ph->setFont(*g_pSttGlobalFont);       //阻抗角
	ui->m_pLabISet1->setFont(*g_pSttGlobalFont);      //短路电流

	ui->m_pLabK0Mode->setFont(*g_pSttGlobalFont);     //零序补偿系数表达方式
	ui->m_pLabKlKr->setFont(*g_pSttGlobalFont);       //零序补偿系数RE
	ui->m_pLabAngKx->setFont(*g_pSttGlobalFont);     //零序补偿系数XE
	ui->m_pLabDrawvoltage->setFont(*g_pSttGlobalFont);//抽取电压选择


	ui->m_pNoPreCheck->setFont(*g_pSttGlobalFont);                 //检无压测试
	ui->m_pSamPerCheck->setFont(*g_pSttGlobalFont);                //检同期测试
	ui->m_pRecCheck->setFont(*g_pSttGlobalFont);                   //自动重合闸
	ui->m_pAftAccCheck->setFont(*g_pSttGlobalFont);                //后加速测试
	ui->m_pNoPreFaultTypeABCheck->setFont(*g_pSttGlobalFont);     //检无压测试故障相别-AB
	ui->m_pNoPreFaultTypeBCCheck->setFont(*g_pSttGlobalFont);      //检无压测试故障相别-BC
	ui->m_pNoPreFaultTypeCACheck->setFont(*g_pSttGlobalFont);      //检无压测试故障相别-CA
	ui->m_pNoPreFaultTypeABCCheck->setFont(*g_pSttGlobalFont);     //检无压测试故障相别-ABC
	ui->m_pSamPerFaultTypeABCheck->setFont(*g_pSttGlobalFont);     //检同期测试故障相别-AB
	ui->m_pSamPerFaultTypeBCCheck->setFont(*g_pSttGlobalFont);     //检同期测试故障相别-BC
	ui->m_pSamPerFaultTypeCACheck->setFont(*g_pSttGlobalFont);     //检同期测试故障相别-CA
	ui->m_pSamPerFaultTypeABCCheck->setFont(*g_pSttGlobalFont);    //检同期测试故障相别-ABC
	ui->m_pRecFaultTypeACheck->setFont(*g_pSttGlobalFont);        //自动重合闸故障相别-A
	ui->m_pRecFaultTypeBCheck->setFont(*g_pSttGlobalFont);        //自动重合闸故障相别-B
	ui->m_pRecFaultTypeCCheck->setFont(*g_pSttGlobalFont);        //自动重合闸故障相别-C
	ui->m_pRecFaultTypeABCheck->setFont(*g_pSttGlobalFont);        //自动重合闸故障相别-AB
	ui->m_pRecFaultTypeBCCheck->setFont(*g_pSttGlobalFont);        //自动重合闸故障相别-BC
	ui->m_pRecFaultTypeCACheck->setFont(*g_pSttGlobalFont);        //自动重合闸故障相别-CA
	ui->m_pRecFaultTypeABCCheck->setFont(*g_pSttGlobalFont);      //自动重合闸故障相别-ABC
	ui->m_pAftAccFaultTypeACheck->setFont(*g_pSttGlobalFont);     //后加速测试故障相别-A
	ui->m_pAftAccFaultTypeBCheck->setFont(*g_pSttGlobalFont);     //后加速测试故障相别-B
	ui->m_pAftAccFaultTypeCCheck->setFont(*g_pSttGlobalFont);     //后加速测试故障相别-C
	ui->m_pAftAccFaultTypeABCheck->setFont(*g_pSttGlobalFont);      //后加速测试故障相别-AB
	ui->m_pAftAccFaultTypeBCCheck->setFont(*g_pSttGlobalFont);     //后加速测试故障相别-BC
	ui->m_pAftAccFaultTypeCACheck->setFont(*g_pSttGlobalFont);     //后加速测试故障相别-CA
	ui->m_pAftAccFaultTypeABCCheck->setFont(*g_pSttGlobalFont);    //后加速测试故障相别-ABC
	ui->m_pNoPreRate095Check->setFont(*g_pSttGlobalFont);         //检无压测试倍数-0.95
	ui->m_pNoPreRate105Check->setFont(*g_pSttGlobalFont);          //检无压测试倍数-1.05
	ui->m_pSamPerRate095Check->setFont(*g_pSttGlobalFont);        //检同期测试倍数-0.95
	ui->m_pSamPerRate105Check->setFont(*g_pSttGlobalFont);         //检同期测试倍数-1.05
	ui->m_pFrequency095Check->setFont(*g_pSttGlobalFont);        
	ui->m_pFrequency105Check->setFont(*g_pSttGlobalFont);         

	ui->m_pNoPreFaultTypeACheck->setFont(*g_pSttGlobalFont);         //抽取电压选择
	ui->m_pNoPreFaultTypeBCheck->setFont(*g_pSttGlobalFont);         //抽取电压选择
	ui->m_pNoPreFaultTypeCCheck->setFont(*g_pSttGlobalFont);         //抽取电压选择
	ui->m_pSamPerFaultTypeACheck->setFont(*g_pSttGlobalFont);         //抽取电压选择
	ui->m_pSamPerFaultTypeBCheck->setFont(*g_pSttGlobalFont);         //抽取电压选择
	ui->m_pSamPerFaultTypeCCheck->setFont(*g_pSttGlobalFont);         //抽取电压选择
	ui->m_pFrequencyACheck->setFont(*g_pSttGlobalFont);         //抽取电压选择
	ui->m_pFrequencyBCheck->setFont(*g_pSttGlobalFont);         //抽取电压选择
	ui->m_pFrequencyCCheck->setFont(*g_pSttGlobalFont);         //抽取电压选择

	ui->m_pEditNoPreSet->setFont(*g_pSttGlobalFont);					 //检无压测试无压定值
	ui->m_pEditSynAngleSetting->setFont(*g_pSttGlobalFont);			 //检同期测试合闸角
	ui->m_pEditZ1->setFont(*g_pSttGlobalFont);						 //故障态阻抗
	ui->m_pEditZ1Ph->setFont(*g_pSttGlobalFont);						 //故障态阻抗角
	ui->m_pEditISet1->setFont(*g_pSttGlobalFont);					 //故障态短路电流

	ui->m_pEditKlKr->setFont(*g_pSttGlobalFont);						 //零序补偿系数RE
	ui->m_pEditAngKx->setFont(*g_pSttGlobalFont);					 //零序补偿系数XE
	ui->m_pBtnResultAssess->setFont(*g_pSttGlobalFont);      //结果评估
	//ui->m_pBtnCommonParas->setFont(*g_pSttGlobalFont);      //通用参数
	ui->m_pBtnExit->setFont(*g_pSttGlobalFont);

	ui->m_pCmbK0Mode->setFont(*g_pSttGlobalFont);			
	ui->m_pCmbDrawvoltage->setFont(*g_pSttGlobalFont);        

	ui->m_pFrequencyCheck->setFont(*g_pSttGlobalFont);			 
	ui->m_pLabFrequency->setFont(*g_pSttGlobalFont);      
	ui->m_pEditFrequency->setFont(*g_pSttGlobalFont);
	ui->m_pFrequencyACheck->setFont(*g_pSttGlobalFont);         
	ui->m_pFrequencyBCheck->setFont(*g_pSttGlobalFont);      
	ui->m_pFrequencyCCheck->setFont(*g_pSttGlobalFont);         
	ui->m_pFrequencyABCheck->setFont(*g_pSttGlobalFont);        
	ui->m_pFrequencyBCCheck->setFont(*g_pSttGlobalFont);        
	ui->m_pFrequencyCACheck->setFont(*g_pSttGlobalFont);         
	ui->m_pFrequencyABCCheck->setFont(*g_pSttGlobalFont);        
	ui->m_pFrequency095Check->setFont(*g_pSttGlobalFont);         
	ui->m_pFrequency105Check->setFont(*g_pSttGlobalFont);         

	ui->m_LabTestItem->setFont(*g_pSttGlobalFont);        
	ui->m_LabSetValue->setFont(*g_pSttGlobalFont);        
	ui->m_pLabFault->setFont(*g_pSttGlobalFont);         
	ui->m_pMultiple->setFont(*g_pSttGlobalFont);         

	ui->m_pFaultDiffGroupBox_3->setFont(*g_pSttGlobalFont);
	ui->m_pModeGroupBox_2->setFont(*g_pSttGlobalFont);
	ui->m_pBtnOk->setFont(*g_pSttGlobalFont);
	ui->m_LabActionTime->setFont(*g_pSttGlobalFont);
	ui->m_EditActionTime->setFont(*g_pSttGlobalFont);
	ui->m_LabRecloseTime->setFont(*g_pSttGlobalFont);
	ui->m_EditRecloseTime->setFont(*g_pSttGlobalFont);

}

void QRecloseAddMultDlg::initConnect()
{
	connect(ui->m_pNoPreCheck, SIGNAL(clicked()), this, SLOT(slot_NoPreCheck()));
	connect(ui->m_pSamPerCheck, SIGNAL(clicked(bool)), this, SLOT(slot_SamPerCheck(bool)));
	connect(ui->m_pRecCheck, SIGNAL(clicked(bool)), this, SLOT(slot_RecCheck(bool)));
	connect(ui->m_pAftAccCheck, SIGNAL(clicked(bool)), this, SLOT(slot_AftAccCheck(bool)));
	connect(ui->m_pFrequencyCheck, SIGNAL(clicked(bool)), this, SLOT(slot_FrequencyCheck(bool)));

	connect(ui->m_pCmbK0Mode, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbK0Mode(int)));

	connect(ui->m_pBtnResultAssess, SIGNAL(clicked()), this, SLOT(slot_ResultAssess()));
	//connect(ui->m_pBtnCommonParas, SIGNAL(clicked()), this, SLOT(slot_CommonParas()));

	connect(ui->m_pNoPreFaultTypeACheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));
	connect(ui->m_pNoPreFaultTypeBCheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));
	connect(ui->m_pNoPreFaultTypeCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));
	connect(ui->m_pNoPreFaultTypeABCheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));
	connect(ui->m_pNoPreFaultTypeBCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));
	connect(ui->m_pNoPreFaultTypeCACheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));
	connect(ui->m_pNoPreFaultTypeABCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));

	connect(ui->m_pSamPerFaultTypeACheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));
	connect(ui->m_pSamPerFaultTypeBCheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));
	connect(ui->m_pSamPerFaultTypeCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultNoPreCheck()));
	connect(ui->m_pSamPerFaultTypeABCheck, SIGNAL(clicked()), this, SLOT(slot_FaultSamPerCheck()));
	connect(ui->m_pSamPerFaultTypeBCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultSamPerCheck()));
	connect(ui->m_pSamPerFaultTypeCACheck, SIGNAL(clicked()), this, SLOT(slot_FaultSamPerCheck()));
	connect(ui->m_pSamPerFaultTypeABCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultSamPerCheck()));


	connect(ui->m_pRecFaultTypeACheck, SIGNAL(clicked()), this, SLOT(slot_FaultRecCheck()));
	connect(ui->m_pRecFaultTypeBCheck, SIGNAL(clicked()), this, SLOT(slot_FaultRecCheck()));
	connect(ui->m_pRecFaultTypeCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultRecCheck()));
	connect(ui->m_pRecFaultTypeABCheck, SIGNAL(clicked()), this, SLOT(slot_FaultRecCheck()));
	connect(ui->m_pRecFaultTypeBCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultRecCheck()));
	connect(ui->m_pRecFaultTypeCACheck, SIGNAL(clicked()), this, SLOT(slot_FaultRecCheck()));
	connect(ui->m_pRecFaultTypeABCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultRecCheck()));

	connect(ui->m_pAftAccFaultTypeACheck, SIGNAL(clicked()), this, SLOT(slot_FaultAftAccCheck()));
	connect(ui->m_pAftAccFaultTypeBCheck, SIGNAL(clicked()), this, SLOT(slot_FaultAftAccCheck()));
	connect(ui->m_pAftAccFaultTypeCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultAftAccCheck()));
	connect(ui->m_pAftAccFaultTypeABCheck, SIGNAL(clicked()), this, SLOT(slot_FaultAftAccCheck()));
	connect(ui->m_pAftAccFaultTypeBCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultAftAccCheck()));
	connect(ui->m_pAftAccFaultTypeCACheck, SIGNAL(clicked()), this, SLOT(slot_FaultAftAccCheck()));
	connect(ui->m_pAftAccFaultTypeABCCheck, SIGNAL(clicked()), this, SLOT(slot_FaultAftAccCheck()));

	connect(ui->m_pFrequencyACheck, SIGNAL(clicked()), this, SLOT(slot_frequencyCheck()));
	connect(ui->m_pFrequencyBCheck, SIGNAL(clicked()), this, SLOT(slot_frequencyCheck()));
	connect(ui->m_pFrequencyCCheck, SIGNAL(clicked()), this, SLOT(slot_frequencyCheck()));
	connect(ui->m_pFrequencyABCheck, SIGNAL(clicked()), this, SLOT(slot_frequencyCheck()));
	connect(ui->m_pFrequencyBCCheck, SIGNAL(clicked()), this, SLOT(slot_frequencyCheck()));
	connect(ui->m_pFrequencyCACheck, SIGNAL(clicked()), this, SLOT(slot_frequencyCheck()));
	connect(ui->m_pFrequencyABCCheck, SIGNAL(clicked()), this, SLOT(slot_frequencyCheck()));

	connect(ui->m_pNoPreRate095Check, SIGNAL(clicked()), this, SLOT(slot_MultipleNoPreCheck()));
	connect(ui->m_pNoPreRate105Check, SIGNAL(clicked()), this, SLOT(slot_MultipleNoPreCheck()));

	connect(ui->m_pSamPerRate095Check, SIGNAL(clicked()), this, SLOT(slot_MultipleSamPerCheck()));
	connect(ui->m_pSamPerRate105Check, SIGNAL(clicked()), this, SLOT(slot_MultipleSamPerCheck()));

	connect(ui->m_pFrequency095Check, SIGNAL(clicked()), this, SLOT(slot_MultipleFrequencyCheck()));
	connect(ui->m_pFrequency105Check, SIGNAL(clicked()), this, SLOT(slot_MultipleFrequencyCheck()));

	connect(ui->m_pEditNoPreSet, SIGNAL(editingFinished()), this, SLOT(slot_NoPreSet()));
	connect(ui->m_pEditSynAngleSetting, SIGNAL(editingFinished()), this, SLOT(slot_SynAngleSetting()));
	connect(ui->m_pEditZ1, SIGNAL(editingFinished()), this, SLOT(slot_Z1()));
	connect(ui->m_pEditZ1Ph, SIGNAL(editingFinished()), this, SLOT(slot_Z1Ph()));
	connect(ui->m_pEditISet1, SIGNAL(editingFinished()), this, SLOT(slot_ISet1()));

	connect(ui->m_pEditKlKr, SIGNAL(editingFinished()), this, SLOT(slot_KlKr()));
	connect(ui->m_pEditAngKx, SIGNAL(editingFinished()), this, SLOT(slot_AngKx()));

	connect(ui->m_pBtnExit, SIGNAL(clicked()), this, SLOT(slot_Exit()));
	connect(ui->m_pBtnOk, SIGNAL(clicked()), this, SLOT(slot_Ok()));
	connect(ui->m_EditActionTime, SIGNAL(editingFinished()), this, SLOT(slot_ActionTime()));
	connect(ui->m_EditRecloseTime, SIGNAL(editingFinished()), this, SLOT(slot_Reclose()));
	connect(ui->m_pEditFrequency, SIGNAL(editingFinished()), this, SLOT(slot_Frequency()));
	

	
}

void QRecloseAddMultDlg::slot_NoPreCheck() 
{
	bool state = ui->m_pNoPreCheck->isChecked();
	
	ui->m_pEditNoPreSet->setEnabled(state);
	ui->m_pNoPreFaultTypeACheck->setEnabled(state);
	ui->m_pNoPreFaultTypeBCheck->setEnabled(state);
	ui->m_pNoPreFaultTypeCCheck->setEnabled(state);
	ui->m_pNoPreFaultTypeABCheck->setEnabled(state);
	ui->m_pNoPreFaultTypeBCCheck->setEnabled(state);
	ui->m_pNoPreFaultTypeCACheck->setEnabled(state);
	ui->m_pNoPreFaultTypeABCCheck->setEnabled(state);
	ui->m_pNoPreRate095Check->setEnabled(state);
	ui->m_pNoPreRate105Check->setEnabled(state);
	ShowOneChecked(ui->m_pNoPreCheck, state);
}

void QRecloseAddMultDlg::slot_SamPerCheck(bool state) 
{
	ShowOneChecked(ui->m_pSamPerCheck, state);
	ui->m_pEditSynAngleSetting->setEnabled(state);
	ui->m_pSamPerFaultTypeACheck->setEnabled(state);
	ui->m_pSamPerFaultTypeBCheck->setEnabled(state);
	ui->m_pSamPerFaultTypeCCheck->setEnabled(state);
	ui->m_pSamPerFaultTypeABCheck->setEnabled(state);
	ui->m_pSamPerFaultTypeBCCheck->setEnabled(state);
	ui->m_pSamPerFaultTypeCACheck->setEnabled(state);
	ui->m_pSamPerFaultTypeABCCheck->setEnabled(state);
	ui->m_pSamPerRate095Check->setEnabled(state);
	ui->m_pSamPerRate105Check->setEnabled(state);
}

void QRecloseAddMultDlg::slot_RecCheck(bool state) 
{
	ShowOneChecked(ui->m_pRecCheck, state);
	ui->m_pRecFaultTypeACheck->setEnabled(state);
	ui->m_pRecFaultTypeBCheck->setEnabled(state);
	ui->m_pRecFaultTypeCCheck->setEnabled(state);
	ui->m_pRecFaultTypeABCheck->setEnabled(state);
	ui->m_pRecFaultTypeBCCheck->setEnabled(state);
	ui->m_pRecFaultTypeCACheck->setEnabled(state);
	ui->m_pRecFaultTypeABCCheck->setEnabled(state);
}

void QRecloseAddMultDlg::slot_AftAccCheck(bool state)
{
	ShowOneChecked(ui->m_pAftAccCheck, state);
	ui->m_pAftAccFaultTypeACheck->setEnabled(state);
	ui->m_pAftAccFaultTypeBCheck->setEnabled(state);
	ui->m_pAftAccFaultTypeCCheck->setEnabled(state);
	ui->m_pAftAccFaultTypeABCheck->setEnabled(state);
	ui->m_pAftAccFaultTypeBCCheck->setEnabled(state);
	ui->m_pAftAccFaultTypeCACheck->setEnabled(state);
	ui->m_pAftAccFaultTypeABCCheck->setEnabled(state);

}

void QRecloseAddMultDlg::slot_FrequencyCheck(bool state)
{
	ShowOneChecked(ui->m_pFrequencyCheck, state);
	ui->m_pEditFrequency->setEnabled(state);
	ui->m_pFrequencyACheck->setEnabled(state);
	ui->m_pFrequencyBCheck->setEnabled(state);
	ui->m_pFrequencyCCheck->setEnabled(state);
	ui->m_pFrequencyABCheck->setEnabled(state);
	ui->m_pFrequencyBCCheck->setEnabled(state);
	ui->m_pFrequencyCACheck->setEnabled(state);
	ui->m_pFrequencyABCCheck->setEnabled(state);
	ui->m_pFrequency095Check->setEnabled(state);
	ui->m_pFrequency105Check->setEnabled(state);
}

void QRecloseAddMultDlg::ShowOneChecked(QCheckBox* pCurrentCheckBox, bool state) 
{
	if (!state) 
	{
		int nCount = 0;
		if (ui->m_pNoPreCheck->isChecked()) 
		{
			nCount++;
		}
		if (ui->m_pSamPerCheck->isChecked()) 
		{
			nCount++;
		}
		if (ui->m_pRecCheck->isChecked()) 
		{
			nCount++;
		}
		if (ui->m_pAftAccCheck->isChecked())
		{
			 nCount++;
		}
		if (ui->m_pFrequencyCheck->isChecked())
		{
			nCount++;
		}
		if (nCount == 0) 
		{
			ui->m_pNoPreCheck->setChecked(true);
			ui->m_pEditNoPreSet->setEnabled(true);
			ui->m_pNoPreFaultTypeACheck->setEnabled(true);
			ui->m_pNoPreFaultTypeBCheck->setEnabled(true);
			ui->m_pNoPreFaultTypeCCheck->setEnabled(true);
			ui->m_pNoPreFaultTypeABCheck->setEnabled(true);
			ui->m_pNoPreFaultTypeBCCheck->setEnabled(true);
			ui->m_pNoPreFaultTypeCACheck->setEnabled(true);
			ui->m_pNoPreFaultTypeABCCheck->setEnabled(true);
			ui->m_pNoPreRate095Check->setEnabled(true);
			ui->m_pNoPreRate105Check->setEnabled(true);

			QMessageBox msgBox;
			msgBox.setWindowTitle(/*"提示"*/g_sLangTxt_Message);
			msgBox.setText(/*"请至少勾选一个测试项"*/g_sLangTxt_MaintainatLeastOneItem);
			QAbstractButton *okButton = msgBox.addButton(/*"确定"*/g_sLangTxt_OK, QMessageBox::AcceptRole);
			okButton->setText(/*"确定"*/g_sLangTxt_OK);
			msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);
			msgBox.exec();
			if (msgBox.clickedButton() == okButton)
			{
                return;
            }
        }
	}
}

void QRecloseAddMultDlg::GetDatas(CDataGroup *pParas)
{
	if(pParas == NULL)
	{
		return;
	}

	m_pRecloseAccDataGroup = pParas;
	GetValue();

}

void QRecloseAddMultDlg::SetDatas(CDataGroup *pDataset)
{
	if (pDataset == NULL)
	{
		return;
	}

	m_pRecloseAccDataGroup = pDataset;

	initDatas();
    initUI();
}

void QRecloseAddMultDlg::GetValue()
{
	CDvmData *pData;
	long nNoPre = ui->m_pNoPreCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPre_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nNoPre);
		ui->m_pNoPreCheck->setChecked(nNoPre);
	}
	
	long nSamPer = ui->m_pSamPerCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPer_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPer);
		ui->m_pSamPerCheck->setChecked(nSamPer);
	}

	long nFrequency = ui->m_pFrequencyCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Frequency_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequency);
		ui->m_pFrequencyCheck->setChecked(nFrequency);
	}

	long nRec = ui->m_pRecCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Rec_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nRec);
		ui->m_pRecCheck->setChecked(nRec);
	}

	long nAftAcc = ui->m_pAftAccCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAcc_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nAftAcc);
		ui->m_pAftAccCheck->setChecked(nAftAcc);
	}

	long nNoPreFaultTypeA = ui->m_pNoPreFaultTypeACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nNoPreFaultTypeA);
		ui->m_pNoPreFaultTypeACheck->setChecked(nNoPreFaultTypeA);
	}

	long nNoPreFaultTypeB = ui->m_pNoPreFaultTypeBCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nNoPreFaultTypeB);
		ui->m_pNoPreFaultTypeBCheck->setChecked(nNoPreFaultTypeB);
	}

	long nNoPreFaultTypeC = ui->m_pNoPreFaultTypeCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nNoPreFaultTypeC);
		ui->m_pNoPreFaultTypeCCheck->setChecked(nNoPreFaultTypeC);
	}

	long nNoPreFaultTypeAB = ui->m_pNoPreFaultTypeABCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeAB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nNoPreFaultTypeAB);
		ui->m_pNoPreFaultTypeABCheck->setChecked(nNoPreFaultTypeAB);
	}

	long nNoPreFaultTypeBC = ui->m_pNoPreFaultTypeBCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeBC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nNoPreFaultTypeBC);
		ui->m_pNoPreFaultTypeBCCheck->setChecked(nNoPreFaultTypeBC);
	}

	long NoPreFaultTypeCA = ui->m_pNoPreFaultTypeCACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeCA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(NoPreFaultTypeCA);
		ui->m_pNoPreFaultTypeCACheck->setChecked(NoPreFaultTypeCA);
	}

	long nNoPreFaultTypeABC = ui->m_pNoPreFaultTypeABCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeABC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nNoPreFaultTypeABC);
		ui->m_pNoPreFaultTypeABCCheck->setChecked(nNoPreFaultTypeABC);
	}

	long nSamPerFaultTypeA = ui->m_pSamPerFaultTypeACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPerFaultTypeA);
		ui->m_pSamPerFaultTypeACheck->setChecked(nSamPerFaultTypeA);
	}

	long nSamPerFaultTypeB = ui->m_pSamPerFaultTypeBCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPerFaultTypeB);
		ui->m_pSamPerFaultTypeBCheck->setChecked(nSamPerFaultTypeB);
	}

	long nSamPerFaultTypeC = ui->m_pSamPerFaultTypeCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPerFaultTypeC);
		ui->m_pSamPerFaultTypeCCheck->setChecked(nSamPerFaultTypeC);
	}

	long nSamPerFaultTypeAB = ui->m_pSamPerFaultTypeABCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeAB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPerFaultTypeAB);
		ui->m_pSamPerFaultTypeABCheck->setChecked(nSamPerFaultTypeAB);
	}

	long nSamPerFaultTypeBC = ui->m_pSamPerFaultTypeBCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeBC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPerFaultTypeBC);
		ui->m_pSamPerFaultTypeBCCheck->setChecked(nSamPerFaultTypeBC);
	}

	long nSamPerFaultTypeCA = ui->m_pSamPerFaultTypeCACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeCA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPerFaultTypeCA);
		ui->m_pSamPerFaultTypeCACheck->setChecked(nSamPerFaultTypeCA);
	}

	long nSamPerFaultTypeABC = ui->m_pSamPerFaultTypeABCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeABC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPerFaultTypeABC);
		ui->m_pSamPerFaultTypeABCCheck->setChecked(nSamPerFaultTypeABC);
	}

	long nFrequencyA = ui->m_pFrequencyACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequencyA);
		ui->m_pFrequencyACheck->setChecked(nFrequencyA);
	}

	long nFrequencyB = ui->m_pFrequencyBCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequencyB);
		ui->m_pFrequencyBCheck->setChecked(nFrequencyB);
	}

	long nFrequencyC = ui->m_pFrequencyCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequencyC);
		ui->m_pFrequencyCCheck->setChecked(nFrequencyC);
	}

	long nFrequencyAB = ui->m_pFrequencyABCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyAB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequencyAB);
		ui->m_pFrequencyABCheck->setChecked(nFrequencyAB);
	}

	long nFrequencyBC = ui->m_pFrequencyBCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyBC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequencyBC);
		ui->m_pFrequencyBCCheck->setChecked(nFrequencyBC);
	}

	long nFrequencyCA = ui->m_pFrequencyCACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyCA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequencyCA);
		ui->m_pFrequencyCACheck->setChecked(nFrequencyCA);
	}

	long nFrequencyABC = ui->m_pFrequencyABCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyABC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequencyABC);
		ui->m_pFrequencyABCCheck->setChecked(nFrequencyABC);
	}

	long nRecFaultTypeA = ui->m_pRecFaultTypeACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nRecFaultTypeA);
		ui->m_pRecFaultTypeACheck->setChecked(nRecFaultTypeA);
	}

	long nRecFaultTypeB = ui->m_pRecFaultTypeBCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nRecFaultTypeB);
		ui->m_pRecFaultTypeBCheck->setChecked(nRecFaultTypeB);
	}

	long nRecFaultTypeC = ui->m_pRecFaultTypeCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nRecFaultTypeC);
		ui->m_pRecFaultTypeCCheck->setChecked(nRecFaultTypeC);
	}

	long nRecFaultTypeAB = ui->m_pRecFaultTypeABCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeAB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nRecFaultTypeAB);
		ui->m_pRecFaultTypeABCheck->setChecked(nRecFaultTypeAB);
	}

	long nRecFaultTypeBC = ui->m_pRecFaultTypeBCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeBC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nRecFaultTypeBC);
		ui->m_pRecFaultTypeBCCheck->setChecked(nRecFaultTypeBC);
	}

	long nRecFaultTypeCA = ui->m_pRecFaultTypeCACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeCA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nRecFaultTypeCA);
		ui->m_pRecFaultTypeCACheck->setChecked(nRecFaultTypeCA);
	}

	long nRecFaultTypeABC = ui->m_pRecFaultTypeABCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeABC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nRecFaultTypeABC);
		ui->m_pRecFaultTypeABCCheck->setChecked(nRecFaultTypeABC);
	}

	long nAftAccFaultTypeA = ui->m_pAftAccFaultTypeACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nAftAccFaultTypeA);
		ui->m_pAftAccFaultTypeACheck->setChecked(nAftAccFaultTypeA);
	}

	long nAftAccFaultTypeB = ui->m_pAftAccFaultTypeBCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nAftAccFaultTypeB);
		ui->m_pAftAccFaultTypeBCheck->setChecked(nAftAccFaultTypeB);
	}

	long nAftAccFaultTypeC = ui->m_pAftAccFaultTypeCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nAftAccFaultTypeC);
		ui->m_pAftAccFaultTypeCCheck->setChecked(nAftAccFaultTypeC);
	}

	long nAftAccFaultTypeAB = ui->m_pAftAccFaultTypeABCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeAB_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nAftAccFaultTypeAB);
		ui->m_pAftAccFaultTypeABCheck->setChecked(nAftAccFaultTypeAB);
	}

	long nAftAccFaultTypeBC = ui->m_pAftAccFaultTypeBCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeBC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nAftAccFaultTypeBC);
		ui->m_pAftAccFaultTypeBCCheck->setChecked(nAftAccFaultTypeBC);
	}

	long nAftAccFaultTypeCA = ui->m_pAftAccFaultTypeCACheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeCA_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nAftAccFaultTypeCA);
		ui->m_pAftAccFaultTypeCACheck->setChecked(nAftAccFaultTypeCA);
	}

	long nAftAccFaultTypeABC = ui->m_pAftAccFaultTypeABCCheck->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeABC_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nAftAccFaultTypeABC);
		ui->m_pAftAccFaultTypeABCCheck->setChecked(nAftAccFaultTypeABC);
	}

	long nNoPreRate095 = ui->m_pNoPreRate095Check->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreRate095_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nNoPreRate095);
		ui->m_pNoPreRate095Check->setChecked(nNoPreRate095);
	}

	long nNoPreRate105 = ui->m_pNoPreRate105Check->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreRate105_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nNoPreRate105);
		ui->m_pNoPreRate105Check->setChecked(nNoPreRate105);
	}

	long nSamPerRate095 = ui->m_pSamPerRate095Check->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerRate095_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPerRate095);
		ui->m_pSamPerRate095Check->setChecked(nSamPerRate095);
	}

	long nSamPerRate105 = ui->m_pSamPerRate105Check->isChecked();
    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerRate110_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nSamPerRate105);
		ui->m_pSamPerRate105Check->setChecked(nSamPerRate105);
	}

	long nFrequency095 = ui->m_pFrequency095Check->isChecked();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Frequency095_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequency095);
		ui->m_pFrequency095Check->setChecked(nFrequency095);
	}

	long nFrequency105 = ui->m_pFrequency105Check->isChecked();
    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Frequency110_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFrequency105);
		ui->m_pFrequency105Check->setChecked(nFrequency105);
	}

	float fNoPreSet = ui->m_pEditNoPreSet->text().toDouble();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreSet");
	if (pData != NULL)
	{
//		pData->m_strValue = QString::number(fNoPreSet);
//		ui->m_pEditNoPreSet->setText(QString::number(fNoPreSet, 'f', 3));

        pData->m_strValue = ui->m_pEditNoPreSet->GetText();
	}

	float fSynAngleSetting = ui->m_pEditSynAngleSetting->text().toDouble();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SynAngleSetting");
	if (pData != NULL)
	{
//		pData->m_strValue = QString::number(fSynAngleSetting);
//		ui->m_pEditSynAngleSetting->setText(QString::number(fSynAngleSetting, 'f', 3));
        pData->m_strValue = ui->m_pEditSynAngleSetting->GetText();
	}

	float fFrequency_Edit = ui->m_pEditFrequency->text().toDouble();
    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("VZFreq");
	if (pData != NULL)
	{
//		pData->m_strValue = QString::number(fFrequency_Edit);
//		ui->m_pEditFrequency->setText(QString::number(fFrequency_Edit, 'f', 3));
        pData->m_strValue = ui->m_pEditFrequency->GetText();
	}

	float fZ1 = ui->m_pEditZ1->text().toDouble();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Z1");
	if (pData != NULL)
	{
//		pData->m_strValue = QString::number(fZ1);
//		ui->m_pEditZ1->setText(QString::number(fZ1, 'f', 3));
        pData->m_strValue = ui->m_pEditZ1->GetText();
	}

	float fZ1Ph = ui->m_pEditZ1Ph->text().toDouble();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Z1Ph");
	if (pData != NULL)
	{
//		pData->m_strValue = QString::number(fZ1Ph);
//		ui->m_pEditZ1Ph->setText(QString::number(fZ1Ph, 'f', 3));
        pData->m_strValue = ui->m_pEditZ1Ph->GetText();
	}

	float fISet1 = ui->m_pEditISet1->text().toDouble();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("ISet1");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fISet1);
		ui->m_pEditISet1->setText(QString::number(fISet1, 'f', 3));
	}

	long nK0Mode = ui->m_pCmbK0Mode->currentIndex();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("K0Mode");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nK0Mode);
		ui->m_pCmbK0Mode->setCurrentIndex(nK0Mode);
	}

	float fKlKr = ui->m_pEditKlKr->text().toDouble();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("KlKr");
	if (pData != NULL)
	{
//		pData->m_strValue = QString::number(fKlKr);
//		ui->m_pEditKlKr->setText(QString::number(fKlKr, 'f', 3));
        pData->m_strValue = ui->m_pEditKlKr->GetText();
	}

	float fAngKx = ui->m_pEditAngKx->text().toDouble();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AngKx");
	if (pData != NULL)
	{
//		pData->m_strValue = QString::number(fAngKx);
//		ui->m_pEditAngKx->setText(QString::number(fAngKx, 'f', 3));
        pData->m_strValue = ui->m_pEditAngKx->GetText();
	}

    //long nDrawvoltage = ui->m_pCmbDrawvoltage->currentIndex();
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Drawvoltage");
	if (pData != NULL)
	{
        CDataTypeValue *pValue = (CDataTypeValue*)ui->m_pCmbDrawvoltage->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}

	float fAction = ui->m_EditActionTime->text().toDouble();
    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("TripTime");
	if (pData != NULL)
	{
//		pData->m_strValue = QString::number(fAction);
//		ui->m_EditActionTime->setText(QString::number(fAction, 'f', 3));
        pData->m_strValue = ui->m_EditActionTime->GetText();
	}

	float fRecloseTime = ui->m_EditRecloseTime->text().toDouble();
    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecloseTime");
	if (pData != NULL)
	{
//		pData->m_strValue = QString::number(fRecloseTime);
//		ui->m_EditRecloseTime->setText(QString::number(fRecloseTime, 'f', 3));
        pData->m_strValue = ui->m_EditRecloseTime->GetText();
	}

}

void QRecloseAddMultDlg::slot_FaultNoPreCheck()
{
	if (!ui->m_pNoPreFaultTypeACheck->isChecked() &&
		!ui->m_pNoPreFaultTypeBCheck->isChecked() &&
		!ui->m_pNoPreFaultTypeCCheck->isChecked() &&
		!ui->m_pNoPreFaultTypeABCheck->isChecked() &&
		!ui->m_pNoPreFaultTypeBCCheck->isChecked() &&
		!ui->m_pNoPreFaultTypeCACheck->isChecked() &&
		!ui->m_pNoPreFaultTypeABCCheck->isChecked())
	{
		ui->m_pNoPreFaultTypeACheck->setChecked(true);
	}
}

void QRecloseAddMultDlg::slot_frequencyCheck()
{
	if (!ui->m_pFrequencyACheck->isChecked() &&
		!ui->m_pFrequencyBCheck->isChecked() &&
		!ui->m_pFrequencyCCheck->isChecked() &&
		!ui->m_pFrequencyABCheck->isChecked() &&
		!ui->m_pFrequencyBCCheck->isChecked() &&
		!ui->m_pFrequencyCACheck->isChecked() &&
		!ui->m_pFrequencyABCCheck->isChecked())
	{
		ui->m_pFrequencyACheck->setChecked(true);
	}
}


void QRecloseAddMultDlg::slot_FaultSamPerCheck()
{
	if (!ui->m_pSamPerFaultTypeACheck->isChecked() &&
		!ui->m_pSamPerFaultTypeBCheck->isChecked() &&
		!ui->m_pSamPerFaultTypeCCheck->isChecked() &&
		!ui->m_pSamPerFaultTypeABCheck->isChecked() &&
		!ui->m_pSamPerFaultTypeBCCheck->isChecked() &&
		!ui->m_pSamPerFaultTypeCACheck->isChecked() &&
		!ui->m_pSamPerFaultTypeABCCheck->isChecked())
	{
		ui->m_pSamPerFaultTypeACheck->setChecked(true);
	}
}

void QRecloseAddMultDlg::slot_FaultRecCheck()
{
	if (!ui->m_pRecFaultTypeACheck->isChecked() &&
		!ui->m_pRecFaultTypeBCheck->isChecked() &&
		!ui->m_pRecFaultTypeCCheck->isChecked() &&
		!ui->m_pRecFaultTypeABCheck->isChecked() &&
		!ui->m_pRecFaultTypeBCCheck->isChecked() &&
		!ui->m_pRecFaultTypeCACheck->isChecked() &&
		!ui->m_pRecFaultTypeABCCheck->isChecked())
	{
		ui->m_pRecFaultTypeACheck->setChecked(true);
	}
}

void QRecloseAddMultDlg::slot_FaultAftAccCheck()
{
	if (!ui->m_pAftAccFaultTypeACheck->isChecked() &&
		!ui->m_pAftAccFaultTypeBCheck->isChecked() &&
		!ui->m_pAftAccFaultTypeCCheck->isChecked() &&
		!ui->m_pAftAccFaultTypeABCheck->isChecked() &&
		!ui->m_pAftAccFaultTypeBCCheck->isChecked() &&
		!ui->m_pAftAccFaultTypeCACheck->isChecked() &&
		!ui->m_pAftAccFaultTypeABCCheck->isChecked())
	{
		ui->m_pAftAccFaultTypeACheck->setChecked(true);
	}
}

void QRecloseAddMultDlg::slot_MultipleNoPreCheck()
{
	if (!ui->m_pNoPreRate095Check->isChecked() &&
		!ui->m_pNoPreRate105Check->isChecked())
	{
		ui->m_pNoPreRate095Check->setChecked(true);
	}
}

void QRecloseAddMultDlg::slot_MultipleFrequencyCheck()
{
	if (!ui->m_pFrequency095Check->isChecked() &&
		!ui->m_pFrequency105Check->isChecked())
	{
		ui->m_pFrequency095Check->setChecked(true);
	}
}


void QRecloseAddMultDlg::slot_MultipleSamPerCheck()
{
	if (!ui->m_pSamPerRate095Check->isChecked() &&
		!ui->m_pSamPerRate105Check->isChecked())
	{
		ui->m_pSamPerRate095Check->setChecked(true);
	}
}

void QRecloseAddMultDlg::slot_CmbK0Mode(int nIndex)
{
	if (nIndex == 0)
	{
        ui->m_pLabKlKr->setText("|K0|:");
        ui->m_pLabAngKx->setText("Phi(K0):   ");
	}
	if(nIndex == 1)
	{
        ui->m_pLabKlKr->setText("RERL:");
        ui->m_pLabAngKx->setText("XEXL:      ");
	}
	if(nIndex == 2)
	{
        ui->m_pLabKlKr->setText("|Z0/Z1|:");
        ui->m_pLabAngKx->setText("Phi|Z0/Z1|:");
	}
}


void QRecloseAddMultDlg::slot_ResultAssess()
{
	QRecloseResultAssessDlg dlg(m_pRecloseAccDataGroup,this);
	dlg.setWindowTitle(/*"结果评估"*/g_sLangTxt_StateEstimate_ResultEstimate);
	dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif

}

//void QRecloseAddMultDlg::slot_CommonParas()
//{
//	QRecloseCommonParasDlg dlg(&m_pRecloseAccDataGroup,this);
//	dlg.setWindowTitle("通用参数");
//	dlg.setWindowModality(Qt::WindowModal);
//
//#ifdef _USE_SoftKeyBoard_
//	QSoftKeyBoard::AttachObj(&dlg);
//	dlg.exec();
//	QSoftKeyBoard::ReAttachObj();
//#else
//	dlg.exec();
//#endif
//}

void QRecloseAddMultDlg::initDatas()
{
	CDvmData *pData = NULL;
	long nValue;
	float fValue;

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPre_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPer_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerCheck->setChecked(nValue);
	}

    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAcc_Check");
    if (pData != NULL)
    {
        nValue = CString_To_long(pData->m_strValue);
        ui->m_pAftAccCheck->setChecked(nValue);
    }

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Rec_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pRecCheck->setChecked(nValue);
	}

    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Frequency_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
        ui->m_pFrequencyCheck->setChecked(nValue);
	}
	
	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreSet");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
        ui->m_pEditNoPreSet->UpdateObjectText(pData, QString::number(fValue, 'f', 3), 3);
        //ui->m_pEditNoPreSet->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SynAngleSetting");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
        ui->m_pEditSynAngleSetting->UpdateObjectText(pData, QString::number(fValue, 'f', 3), 3);
        //ui->m_pEditSynAngleSetting->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeAB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreFaultTypeABCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeBC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreFaultTypeBCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeCA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreFaultTypeCACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeABC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreFaultTypeABCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeAB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerFaultTypeABCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeBC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerFaultTypeBCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeCA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerFaultTypeCACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeABC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerFaultTypeABCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pRecFaultTypeACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pRecFaultTypeBCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pRecFaultTypeCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeAB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pRecFaultTypeABCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeBC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pRecFaultTypeBCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeCA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pRecFaultTypeCACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecFaultTypeABC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pRecFaultTypeABCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pAftAccFaultTypeACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pAftAccFaultTypeBCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pAftAccFaultTypeCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeAB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pAftAccFaultTypeABCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeBC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pAftAccFaultTypeBCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeCA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pAftAccFaultTypeCACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AftAccFaultTypeABC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pAftAccFaultTypeABCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreRate095_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreRate095Check->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreRate105_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreRate105Check->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerRate120_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerRate095Check->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerRate110_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerRate105Check->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Z1");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
        ui->m_pEditZ1->UpdateObjectText(pData, QString::number(fValue, 'f', 3), 3);
        //ui->m_pEditZ1->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Z1Ph");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
        ui->m_pEditZ1Ph->UpdateObjectText(pData, QString::number(fValue, 'f', 2), 2);
        //ui->m_pEditZ1Ph->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("ISet1");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_pEditISet1->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("K0Mode");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pCmbK0Mode->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("KlKr");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
        ui->m_pEditKlKr->UpdateObjectText(pData, QString::number(fValue, 'f', 3), 3);
        //ui->m_pEditKlKr->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("AngKx");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
        ui->m_pEditAngKx->UpdateObjectText(pData, QString::number(fValue, 'f', 2), 2);
        //ui->m_pEditAngKx->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Drawvoltage");
	if (pData != NULL)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_UXMODE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            ui->m_pCmbDrawvoltage->SetCurrSelByName(pValue->m_strName);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreFaultTypeACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreFaultTypeBCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("NoPreFaultTypeC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pNoPreFaultTypeCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerFaultTypeACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerFaultTypeBCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("SamPerFaultTypeC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pSamPerFaultTypeCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pFrequencyACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pFrequencyBCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pFrequencyCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyAB_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pFrequencyABCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyBC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pFrequencyBCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyCA_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pFrequencyCACheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("FrequencyABC_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pFrequencyABCCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Frequency095_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pFrequency095Check->setChecked(nValue);
	}

	pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("Frequency110_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_pFrequency105Check->setChecked(nValue);
	}

    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("TripTime");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
        ui->m_EditActionTime->UpdateObjectText(pData, QString::number(fValue, 'f', 3), 3);
        //ui->m_EditActionTime->setText(QString::number(fValue, 'f', 3));
	}

    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("RecloseTime");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
        ui->m_EditRecloseTime->UpdateObjectText(pData, QString::number(fValue, 'f', 3), 3);
        //ui->m_EditRecloseTime->setText(QString::number(fValue, 'f', 3));
	}

    pData = (CDvmData *)m_pRecloseAccDataGroup->FindByID("VZFreq");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
        ui->m_pEditFrequency->UpdateObjectText(pData, QString::number(fValue, 'f', 3), 3);
        //ui->m_pEditFrequency->setText(QString::number(fValue, 'f', 3));
	}
}

void QRecloseAddMultDlg::slot_NoPreSet()
{
    if(ui->m_pEditNoPreSet->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_pEditNoPreSet)->IsSetting())
        {
            return;
        }
    }

	float fv = ui->m_pEditNoPreSet->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_pEditNoPreSet->setText(QString::number(fv, 'f', 3));
}

void QRecloseAddMultDlg::slot_SynAngleSetting()
{
    if(ui->m_pEditSynAngleSetting->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_pEditSynAngleSetting)->IsSetting())
        {
            return;
        }
    }

	float fv = ui->m_pEditSynAngleSetting->text().toFloat();
	fv = setLimit(-360.0,360.00,fv);
	ui->m_pEditSynAngleSetting->setText(QString::number(fv, 'f', 2));
}

void QRecloseAddMultDlg::slot_Z1()
{
    if(ui->m_pEditZ1->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_pEditZ1)->IsSetting())
        {
            return;
        }
    }

	float fv = ui->m_pEditZ1->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_pEditZ1->setText(QString::number(fv, 'f', 3));
}

void QRecloseAddMultDlg::slot_Z1Ph()
{
    if(ui->m_pEditZ1Ph->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_pEditZ1Ph)->IsSetting())
        {
            return;
        }
    }

	float fv = ui->m_pEditZ1Ph->text().toFloat();
	fv = setLimit(-360.0,360.00,fv);
	ui->m_pEditZ1Ph->setText(QString::number(fv, 'f', 2));
}

void QRecloseAddMultDlg::slot_ISet1()
{
	float fv = ui->m_pEditISet1->text().toFloat();
	fv = setLimit(0,20.000,fv);
	ui->m_pEditISet1->setText(QString::number(fv, 'f', 3));
}

void QRecloseAddMultDlg::slot_KlKr()
{
    if(ui->m_pEditKlKr->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_pEditKlKr)->IsSetting())
        {
            return;
        }
    }

	float fv = ui->m_pEditKlKr->text().toFloat();
	fv = setLimit(0,999.99,fv);
	ui->m_pEditKlKr->setText(QString::number(fv, 'f', 2));
}

void QRecloseAddMultDlg::slot_AngKx()
{
    if(ui->m_pEditAngKx->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_pEditAngKx)->IsSetting())
        {
            return;
        }
    }

	float fv = ui->m_pEditAngKx->text().toFloat();
	fv = setLimit(0,360.00,fv);
	ui->m_pEditAngKx->setText(QString::number(fv, 'f', 2));
}

void QRecloseAddMultDlg::slot_ActionTime()
{
    if(ui->m_EditActionTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_EditActionTime)->IsSetting())
        {
            return;
        }
    }

	float fv = ui->m_EditActionTime->text().toFloat();
	fv = setLimit(0,999.99,fv);
    ui->m_EditActionTime->setText(QString::number(fv, 'f', 3));
}

void QRecloseAddMultDlg::slot_Reclose()
{
    if(ui->m_EditRecloseTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_EditRecloseTime)->IsSetting())
        {
            return;
        }
    }

	float fv = ui->m_EditRecloseTime->text().toFloat();
	fv = setLimit(0,999.99,fv);
    ui->m_EditRecloseTime->setText(QString::number(fv, 'f', 3));
}

void QRecloseAddMultDlg::slot_Frequency()
{
    if(ui->m_pEditFrequency->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingLineEdit"*/))
    {
        if (((QSettingLineEdit*)ui->m_pEditFrequency)->IsSetting())
        {
            return;
        }
    }

	float fv = ui->m_pEditFrequency->text().toFloat();
	fv = setLimit(0,999.99,fv);
    ui->m_pEditFrequency->setText(QString::number(fv, 'f', 3));
}

void QRecloseAddMultDlg::slot_Ok()
{
//    GetValue();
//	accept();
    GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
    this->done(Accepted);
}

void QRecloseAddMultDlg::slot_Exit()
{
	this->close();
}
