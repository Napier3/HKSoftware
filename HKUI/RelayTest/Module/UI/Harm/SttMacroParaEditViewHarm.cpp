#include "SttMacroParaEditViewHarm.h"
#include "../../Module/SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../SttTestCntrFrameAPI.h"
#include "../../Module/XLangResource_Native.h"
QSttMacroParaEditViewHarm* g_pHarmTest = NULL;

extern float  g_fValueStep;
extern int g_nUpdateActTime;
extern QString g_strContent;

QSttMacroParaEditViewHarm::QSttMacroParaEditViewHarm(QWidget *parent)
    :CSttMacroParaEditViewOriginal(parent)
{
	////20240705 huangliang	切换到那个模块就需要更新地址
	//g_pCurrTestMacroUI_DataMaps = &m_oDvmDataMaps;//20240802 huangliang 在基类CSttMacroParaEditViewOriginal中以使用，删除此处代码

	g_pHarmTest = this;

	m_nCurHarmIndex = 0;
	//m_pHarmPara = NULL;
	m_nAutoStep = 0;
//	m_nUpdateDataFlag = 0;
	m_bTmtParaChanged = false;
//	m_strParaFileTitle = tr("谐波测试模板文件");
    m_strParaFileTitle = g_sLangTxt_State_HarmonicTestTemplatefile; //谐波测试模板文件 lcq 3.14
	m_strParaFilePostfix = tr("project(*.hrmxml)");
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("HarmTest.hrmxml");

	//这个定时器在6.3的版本里面就这么用的，我觉得这个定时器没有啥用，就等了5毫秒然后调了一个函数，
	//然后就把定时器关闭了，目测可以改成直接调用，等函模块写完再试 sf 20220224
	//connect(&m_oTimerWave,   SIGNAL(timeout()),   this,  SLOT(slot_Timer_Wave()));

	initUI();
	initConnections();

    m_pOriginalSttTestResource = stt_GetSttTestResource();
//	CreateTestResource();
	stt_Frame_InitTestResource();

// 	if (g_oSystemParas.m_nHasDigital)//zhouhj 在打开测试模板前先初始化当前GOOSE发布数据
// 	{
// 		InitGoosePubDataGroups();
// 	}

	initTestParas();
	InitArrUIValue();
	m_pHarmWidget->m_pParaWidget->UpdateBinaryInBinaryOutEnable();

//	m_oTimerDiBian.start(700);
//	connect(&m_oTimerDiBian,   SIGNAL(timeout()),    this,   SLOT(slot_DiBianTimer()));

	//SetWavePlotTestResource();
#ifdef _PSX_QT_WINDOWS_
	//2024-8-6 wuxinyi 手动调用更新波形图接口
    //m_pHarmWidget->m_pOscillogramGroupWidget->slot_updateOscillogramGroup();
#endif

}

QSttMacroParaEditViewHarm::~QSttMacroParaEditViewHarm()
{
	if (m_pHarmWidget != NULL)
	{
		delete m_pHarmWidget;
		m_pHarmWidget = NULL;
	}
}
// 
// CSttTestResourceBase* QSttMacroParaEditViewHarm::CreateTestResource()
// {
// // 	if (m_pOriginalSttTestResource == NULL)
// // 	{
// // 		m_pOriginalSttTestResource = new CSttTestResource_Sync();
// // 	}
// 
// // 	g_theTestCntrFrame->m_pSttTestResource = m_pOriginalSttTestResource;
// // 	g_oSttTestResourceMngr.m_pTestResouce = m_pOriginalSttTestResource;
// 	m_pOriginalSttTestResource = stt_GetSttTestResource();
// 	return m_pOriginalSttTestResource;
// }

void QSttMacroParaEditViewHarm::UpdateTestResource( BOOL bCreateChMaps )
{
// 	ASSERT(g_theTestCntrFrame->m_pSttTestResource);
// 	g_theTestCntrFrame->OnUpdateTestResource(bCreateChMaps);

	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();

	m_pHarmWidget->UpdateTestResource();
	m_pHarmWidget->m_pParaWidget->UpdateBinaryInBinaryOutEnable();

// 	if(g_nBoutCount == 8)
// 	{
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Output9->setChecked(false);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Output10->setChecked(false);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Output9->setEnabled(false);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Output10->setEnabled(false);
// 	}
// 	else
// 	{
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Output9->setChecked(m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOut[8].nState);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Output10->setChecked(m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOut[9].nState);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Output9->setEnabled(true);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Output10->setEnabled(true);
// 	}
// 
// 	if (g_nBinCount == 8)
// 	{
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Input9->setChecked(false);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Input10->setChecked(false);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Input9->setEnabled(false);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Input10->setEnabled(false);
// 	}
// 	else
// 	{
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Input9->setChecked(m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binIn[8].nSelect);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Input10->setChecked(m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binIn[9].nSelect);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Input9->setEnabled(true);
// 		m_pHarmWidget->m_pParaWidget->m_pCheck_Input10->setEnabled(true);
// 	}
}

void QSttMacroParaEditViewHarm::ShowReport( CDvmValues *pValues )
{
	CDvmValue* pActValueData = (CDvmValue*)pValues->FindByID("ActValue");
	CDvmValue* pActTimeData = (CDvmValue*)pValues->FindByID("TripTime");
	CDvmValue* pActReturnData = (CDvmValue*)pValues->FindByID("ReturnValue");
	CDvmValue* pActReturnTimeData = (CDvmValue*)pValues->FindByID("ReturnTime");

	float fActValue = 0, fActTime = 0, fReturnValue = 0, fReturnTime = 0;

	if (pActValueData != NULL)
	{
		fActValue = CString_To_double(pActValueData->m_strValue);
	}

	if (pActTimeData != NULL)
	{
		fActTime = CString_To_double(pActTimeData->m_strValue);
	}

	if (pActReturnData != NULL)
	{
		fReturnValue = CString_To_double(pActReturnData->m_strValue);
	}

	if (pActReturnTimeData != NULL)
	{
		fReturnTime = CString_To_double(pActReturnTimeData->m_strValue);
	}

	//m_pHarmWidget->UpdateResult(fActValue, fActTime, fReturnValue, fReturnTime);
}

void QSttMacroParaEditViewHarm::SetDatas(CDataGroup *pParas)
{
// 	if (m_pHarmWidget)
// 	{
// 		m_pHarmWidget->SetDatas(&m_oTmtHarmTest,g_theTestCntrFrame->m_pSttTestResource);
// 	}
	if (pParas != NULL)
	{
		CSttDataGroupSerializeRead oRead(pParas);
		stt_xml_serialize(&m_oTmtHarmTest.m_oHarmParas, &oRead);
		ReadModeDataSaveMaps(&oRead);	
	}

	stt_Frame_ClearInfoWidget();	

	UpdateHarmParas();
}

void QSttMacroParaEditViewHarm::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);

// 	SYSTEMTIME tm;
// 	::GetLocalTime(&tm);
// 	CString strTmpPath = _P_GetLibraryPath();
// 	strTmpPath.AppendFormat(_T("HarmTestParas%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
// 		, tm.wHour, tm.wMinute, tm.wSecond);
// 	pParas->SaveXmlFile(strTmpPath,CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewHarm::initUI()
{
	m_pMainLayout = new QHBoxLayout();
	this->setLayout(m_pMainLayout);

	m_pHarmWidget = new QHarmWidget(this);

    m_pHarmWidget->setPropertyOfParaSet(P_Common,  stt_GetSttTestResource(),  m_oTmtHarmTest.m_oHarmParas.m_uiVOL,  m_oTmtHarmTest.m_oHarmParas.m_uiCUR);
	m_pHarmWidget->setMaxMinAndEDVal();

	m_pMainLayout->addWidget(m_pHarmWidget);

	setFocusPolicy(Qt::StrongFocus);
}

void QSttMacroParaEditViewHarm::initConnections()
{
	connect(m_pHarmWidget->m_pParaWidget,SIGNAL(sig_InPutStateChanged()),this,SLOT(slot_SwitchStateChanged()));
	connect(m_pHarmWidget->m_pParaWidget,SIGNAL(sig_OutPutStateChanged()),this,SLOT(slot_SwitchStateChanged()));
	connect(this,	SIGNAL(sig_updataParas()),	this,	SLOT(slot_updateParas()));
	connect(m_pHarmWidget,  SIGNAL(sig_updataParas()),  this,  SLOT(slot_updateParas()), Qt::UniqueConnection);
	connect(m_pHarmWidget,	SIGNAL(sig_LockChanged()),   this,   SLOT(slot_LockChanged()),  Qt::UniqueConnection);

// 	connect(m_pHarmWidget->m_pbn_Add,   SIGNAL(clicked()),   this,  SLOT(slot_pbnAddClicked()),  Qt::UniqueConnection);
// 	connect(m_pHarmWidget->m_pbn_Del,   SIGNAL(clicked()),   this,  SLOT(slot_pbnMinusClicked()),  Qt::UniqueConnection);
	connect(m_pHarmWidget->m_pParaWidget,   SIGNAL(sig_AutoStateChanged(bool)),   this,  SLOT(slot_pbnAutoClicked(bool)),  Qt::UniqueConnection);
	connect(m_pHarmWidget,  SIGNAL(sig_SetToZero()),  this,  SLOT(slot_SetToZero()), Qt::UniqueConnection);
//	connect(m_pHarmWidget,   SIGNAL(sig_CheckStateChanged(/*int , bool*/ )),   this,  SLOT(slot_CheckStateChanged(/*int ,  bool */)));
	connect(m_pHarmWidget->m_pTabWidget,  SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
}


void QSttMacroParaEditViewHarm::UpdateHarmParas()
{
	if (m_pHarmWidget)
	{
        m_pHarmWidget->SetDatas(&m_oTmtHarmTest,stt_GetSttTestResource());
	}

	UpdateBinBoutExTab();
	if(m_pHarmWidget->ExistExBinParaWidget())
	{
		m_pHarmWidget->m_pExBinParaWidget->setData(m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binInEx,NULL);
	}

	if(m_pHarmWidget->ExistExBoutParaWidget())
	{
		m_pHarmWidget->m_pExBoutParaWidget->setData(NULL,m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOutEx);
	}

	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewHarm::OnViewTestLink( BOOL b/*=FALSE*/ )
{

}

void QSttMacroParaEditViewHarm::OnViewTestStart()
{
	m_pHarmWidget->StartInit();
	if (m_oTmtHarmTest.m_oHarmParas.m_bAuto)
	{
		if (m_pHarmWidget->m_pGooseParaWidget != NULL)
		{
			m_pHarmWidget->m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_NotEditable);
			m_pHarmWidget->m_pGooseParaWidget->setDisabled(true);
		}

		if (m_pHarmWidget->m_pFT3OutParaWidget != NULL)
		{
			m_pHarmWidget->m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_NotEditable);
			m_pHarmWidget->m_pFT3OutParaWidget->setDisabled(true);
		}

		m_pHarmWidget->SetEnableTable(false);
	}
	else
	{
		if (m_pHarmWidget->m_pGooseParaWidget)
			m_pHarmWidget->m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);

		if (m_pHarmWidget->m_pFT3OutParaWidget)
			m_pHarmWidget->m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);

		m_pHarmWidget->SetEnableTable(true);
		//m_pSyncParaSet->startInit();
	}

	stt_Frame_ClearInfoWidget();
	stt_Frame_EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewHarm::OnViewTestStop()
{
	m_oTmtHarmTest.m_oHarmParas.m_bBinStop = FALSE;
	m_pHarmWidget->SetEnableTable(true);

	if (m_pHarmWidget->m_pGooseParaWidget)
	{
		m_pHarmWidget->m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_Stoped);
		m_pHarmWidget->m_pGooseParaWidget->setDisabled(false);
	}

	if (m_pHarmWidget->m_pFT3OutParaWidget)
	{
		m_pHarmWidget->m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_Stoped);
		m_pHarmWidget->m_pFT3OutParaWidget->setDisabled(false);
	}
	m_pHarmWidget->slot_ResetChangeFlag(0);

	m_pHarmWidget->StopInit();
}

QWidget* QSttMacroParaEditViewHarm::GetWaveWidget()
{
    return 0;//m_pHarmWidget->m_pOscillogramGroupWidget;
}

void QSttMacroParaEditViewHarm::UpdateGoutTab_UI( CIecCfgGoutDatas* pCfgGoutDatas )
{
	if (m_pHarmWidget == NULL)
	{
		return;
	}
	if ((m_pHarmWidget->m_pGooseParaWidget == NULL)&&(g_oSystemParas.m_nHasDigital)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC> 0))//更新前无GOOSE界面,更新后需要GOOSE界面
	{
		m_pHarmWidget->AddGooseParaWidget(pCfgGoutDatas);

		connect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
		connect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
	}
	else if ((m_pHarmWidget->m_pGooseParaWidget != NULL)&&(!g_oSystemParas.m_nHasDigital))//更新前有GOOSE界面,更新后不需要
	{
		disconnect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		m_pHarmWidget->RemoveGooseParaWidget();
	}
	else if ((m_pHarmWidget->m_pGooseParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		disconnect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
		m_pHarmWidget->m_pGooseParaWidget->initGoosePubTable(pCfgGoutDatas);
		connect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
		connect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
	}
	else if ((m_pHarmWidget->m_pGooseParaWidget != NULL)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC == 0))//更新前有GOOSE界面,更新后LC口为0不需要
	{
		disconnect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pHarmWidget->m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		m_pHarmWidget->RemoveGooseParaWidget();
	}
}
void QSttMacroParaEditViewHarm::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	int nFT3Block = 0;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while(pos)
	{
		CIecCfgDataBase* pIecCfgDataBase = (CIecCfgDataBase *)pIecCfgDatasSMV->GetNext(pos);
		if (pIecCfgDataBase->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA && pIecCfgDataBase->m_nUseFlag)
		{
			nFT3Block ++;
		}
	}


	if (m_pHarmWidget == NULL)
	{
		return;
	}
	if ((m_pHarmWidget->m_pFT3OutParaWidget == NULL)&&(g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0) && (nFT3Block > 0))
	{
		m_pHarmWidget->AddFT3OutParaWidget(pIecCfgDatasSMV);

		connect(m_pHarmWidget->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
	else if ((m_pHarmWidget->m_pFT3OutParaWidget != NULL)&&(!g_oSystemParas.IsDigitalOutputFT3()))
	{
		disconnect(m_pHarmWidget->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		m_pHarmWidget->RemoveFT3OutParaWidget();
	}
	else if ((m_pHarmWidget->m_pFT3OutParaWidget != NULL)&&(g_oSystemParas.IsDigitalOutputFT3()))
	{
		if(nFT3Block > 0)
		{
		disconnect(m_pHarmWidget->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		m_pHarmWidget->m_pFT3OutParaWidget->InitFT3Table(pIecCfgDatasSMV);
		connect(m_pHarmWidget->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
		else
		{
			disconnect(m_pHarmWidget->m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
			m_pHarmWidget->RemoveFT3OutParaWidget();
		}
	}
}

void QSttMacroParaEditViewHarm::initTestParas()
{
	if (!OpenTestTestMngrFile(_T("")))
	{
		m_oTmtHarmTest.m_oHarmParas.init();
	}	

	CopyBinaryConfig();
	stt_Frame_UpdateToolButtons();
	SetDatas(NULL);
}

void QSttMacroParaEditViewHarm::UpdateGoutTab( BOOL bUpdateList /*= FALSE*/ )
{
	if (g_oSystemParas.m_nHasDigital)//zhouhj 在打开测试模板前先初始化当前GOOSE发布数据
	{
//		InitGoosePubDataGroups();
		UpdateGoutTab_UI(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr()/*m_listGoosePub.at(0)*/);
	}
	else if (m_pHarmWidget != NULL)
	{
		m_pHarmWidget->RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewHarm::UpdateFT3Tab( BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		UpdateFT3Tab_UI(g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr());
	}
	else if (m_pHarmWidget != NULL)
	{
		m_pHarmWidget->RemoveFT3OutParaWidget();
	}
}

void QSttMacroParaEditViewHarm::UpdateBinBoutExTab()
{
	if ((m_pHarmWidget->m_pExBinParaWidget == NULL)&&(g_oLocalSysPara.m_nCHBinInExNum > 0))
	{
		m_pHarmWidget->AddExBinParaWidget();
		m_pHarmWidget->m_pExBinParaWidget->setData(m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binInEx,NULL);
		connect(m_pHarmWidget->m_pExBinParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);
	}
	else if ((m_pHarmWidget->m_pExBinParaWidget != NULL)&&(g_oLocalSysPara.m_nCHBinInExNum == 0))
	{
		disconnect(m_pHarmWidget->m_pExBinParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pHarmWidget->RemoveExBinParaWidget();
	}
	else if ((m_pHarmWidget->m_pExBinParaWidget != NULL)&&(g_oLocalSysPara.m_nCHBinInExNum>0))
	{
		disconnect(m_pHarmWidget->m_pExBinParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pHarmWidget->m_pExBinParaWidget->setData(m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binInEx,NULL);
		connect(m_pHarmWidget->m_pExBinParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);

		m_pHarmWidget->EnableBinParaWidget(true);
	}

	if ((m_pHarmWidget->m_pExBoutParaWidget == NULL)&&(g_oLocalSysPara.m_nCHBinOutExNum>0))
	{
		m_pHarmWidget->AddExBoutParaWidget();
		m_pHarmWidget->m_pExBoutParaWidget->setData(NULL,m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOutEx);
		connect(m_pHarmWidget->m_pExBoutParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);
	}
	else if ((m_pHarmWidget->m_pExBoutParaWidget != NULL)&&(g_oLocalSysPara.m_nCHBinOutExNum == 0))
	{
		disconnect(m_pHarmWidget->m_pExBoutParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pHarmWidget->RemoveExBoutParaWidget();
	}
	else if ((m_pHarmWidget->m_pExBoutParaWidget != NULL)&&(g_oLocalSysPara.m_nCHBinOutExNum>0))
	{
		disconnect(m_pHarmWidget->m_pExBoutParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pHarmWidget->m_pExBoutParaWidget->setData(NULL,m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOutEx);
		connect(m_pHarmWidget->m_pExBoutParaWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);

		m_pHarmWidget->EnableBoutParaWidget(true);
	}
}
void QSttMacroParaEditViewHarm::CopyBinaryConfig( BOOL b/*=TRUE*/ )
{
	if(b)
	{
        stt_GetBinaryConfig()->m_nBinLogic = m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
            stt_GetBinaryConfig()->m_binIn[i] = m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binIn[i];
		}

// 		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
// 			stt_GetBinaryConfig()->m_binOut[i] = m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOut[i];
// 		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
            stt_GetBinaryConfig()->m_binInEx[i] = m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binInEx[i];
		}

// 		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
// 			stt_GetBinaryConfig()->m_binOutEx[i] = m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOutEx[i];
// 		}
	}
	else
	{
        m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_nBinLogic = stt_GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
            m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binIn[i] = stt_GetBinaryConfig()->m_binIn[i];
		}

// 		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
// 			m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOut[i] = stt_GetBinaryConfig()->m_binOut[i];
// 		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
            m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binInEx[i] = stt_GetBinaryConfig()->m_binInEx[i];
		}

// 		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
// 			m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOutEx[i] = stt_GetBinaryConfig()->m_binOutEx[i];
// 		}
	}
}

void QSttMacroParaEditViewHarm::SerializeTestParas( CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas, long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub )
{
	tmt_HarmTest *pHarmTest = (tmt_HarmTest*)pParas;
	stt_xml_serialize(&pHarmTest->m_oHarmParas, pMacroParas,nVolRsNum,nCurRsNum,g_oLocalSysPara.m_nMaxHarmCount);

//	CSttXmlSerializeBase *pXmlParas = stt_xml_serialize((tmt_HarmTest*)pParas,  pMacroParas, nVolRsNum,  nCurRsNum,g_oLocalSysPara.m_nMaxHarmCount);

	if (bHasGoosePub)
	{
		CIecCfgGoutDatas *pGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr()/*m_listGoosePub.at(0)*/;
		ASSERT(pGoutDatas);
//		CIecCfgGoutDatas *pGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
		SerializeGoosePubs(pMacroParas,pGoutDatas);
	}
	if (bHasGoosePub)
	{
		CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
		ASSERT(pIecCfgDatasSMV);
		SerializeFT3Pubs(pMacroParas,pIecCfgDatasSMV);
	}
}

void QSttMacroParaEditViewHarm::OnTestResults( CDataGroup *pResults )
{
	ASSERT(pResults != NULL);

	long nTripFlag;
	stt_GetDataValueByID(pResults, "TripFlag", nTripFlag);
	stt_GetDataValueByID(pResults, "TripTime", m_oTmtHarmTest.m_oHarmResult.m_fTripTime);
	stt_GetDataValueByID(pResults, "ActValue", m_oTmtHarmTest.m_oHarmResult.m_fActValue);

	m_oTmtHarmTest.m_oHarmResult.m_nTripFlag  =  nTripFlag;

	//m_pHarmWidget->UpdateResult(m_oTmtHarmTest.m_oHarmResult.m_fActValue,m_oTmtHarmTest.m_oHarmResult.m_fTripTime,   0,  0);
}

CString QSttMacroParaEditViewHarm::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += FILE_HARMTEST;
	strFile += _T(".");
	strFile += POSTFIX_HarmTEST;

	return strFile;
}

bool QSttMacroParaEditViewHarm::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
{
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != POSTFIX_HarmTEST)
	{
		return FALSE;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return FALSE;
	}

	return TRUE;
}

void QSttMacroParaEditViewHarm::slot_updateParas()
{
	//m_vectorWidget->updateData();
	if (stt_Frame_IsTestStarted() && (!m_oTmtHarmTest.m_oHarmParas.m_bLock))
	{
		//g_theTestCntrFrame->OnCmd_SaveTemplate();
		stt_Frame_Ats_UpdateParameter();
//		stt_Frame_UpdatePowerData();
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QSttMacroParaEditViewHarm::slot_updateParas[if]."));

// 		m_powerWidget->updateData();
// 		m_seqWidget->updateData();
// 		m_lineVoltWidget->updateData();
	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QSttMacroParaEditViewHarm::slot_updateParas[else]."));
// 	}
}

void QSttMacroParaEditViewHarm::slot_SwitchStateChanged()
{
	CopyBinaryConfig(TRUE);

//	g_theTestCntrFrame->SyncBinOutDatas();	

	stt_Frame_UpdateToolButtons();

	if (!stt_Frame_IsTestStarted()) 
	{
		return;
	}
	//开始测试后，非锁定刷新开关量曲线
	if (!m_oTmtHarmTest.m_oHarmParas.m_bLock)
	{
		emit sig_updataParas();
	}
}

void QSttMacroParaEditViewHarm::InitArrUIValue()
{
	for (int i  =  0;  i < MAX_VOLTAGE_COUNT;  i++)
	{
		for (int j  =  0;  j < MAX_HARM_COUNT_UI;  j++)
		{
			if (j<31)
			{
// 				m_oTmtHarmTest.m_oHarmParas.m_uiVOL[i].Harm[j].m_bSelect   =   true;//dingxy 20240412 根据模板值初始化
// 				m_oTmtHarmTest.m_oHarmParas.m_uiCUR[i].Harm[j].m_bSelect   =   true;
			}
			else
			{
				m_oTmtHarmTest.m_oHarmParas.m_uiVOL[i].Harm[j].m_bSelect   =   false;
				m_oTmtHarmTest.m_oHarmParas.m_uiCUR[i].Harm[j].m_bSelect   =   false;
			}

			m_oTmtHarmTest.m_oHarmParas.m_uiVOL[i].Harm[j].nIndex   =   j;
			m_oTmtHarmTest.m_oHarmParas.m_uiCUR[i].Harm[j].nIndex   =   j;

// 			if (j==0)
// 			{
// 				m_oTmtHarmTest.m_oHarmParas.m_uiVOL[i].Harm[j].fAmp   =   0;	
// 				m_oTmtHarmTest.m_oHarmParas.m_uiVOL[i].Harm[j].fContent   =   0;
// 
// 				m_oTmtHarmTest.m_oHarmParas.m_uiCUR[i].Harm[j].fAmp   =   0;	
// 				m_oTmtHarmTest.m_oHarmParas.m_uiCUR[i].Harm[j].fContent   =   0;
// 			}
// 			else if (j==1)
// 			{
// 				m_oTmtHarmTest.m_oHarmParas.m_uiVOL[i].Harm[j].fAmp   =   57.74;	
// 				m_oTmtHarmTest.m_oHarmParas.m_uiVOL[i].Harm[j].fContent   =   100.00;
// 
// 				m_oTmtHarmTest.m_oHarmParas.m_uiCUR[i].Harm[j].fAmp   =  5;	
// 				m_oTmtHarmTest.m_oHarmParas.m_uiCUR[i].Harm[j].fContent   =   100.00;
// 
// 			}
// 			else 
// 			{
// 				m_oTmtHarmTest.m_oHarmParas.m_uiVOL[i].Harm[j].fAmp   =  0;	
// 				m_oTmtHarmTest.m_oHarmParas.m_uiVOL[i].Harm[j].fContent   =   0;
// 
// 				m_oTmtHarmTest.m_oHarmParas.m_uiCUR[i].Harm[j].fAmp   =  0;	
// 				m_oTmtHarmTest.m_oHarmParas.m_uiCUR[i].Harm[j].fContent   =   0;
// 			}
		}
	}

}

void QSttMacroParaEditViewHarm::InitBinStateOnStarting()
{
// 	//初始化开出
// 	for (int i=0;i< g_oLocalSysPara.m_nCHBinOutNum;i++)
// 		m_oCurrEventResult.m_BinOut[i] = m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOut[i].nState;
// 
// 	for (int i=0;i< g_oLocalSysPara.m_nCHBinOutExNum;i++)
// 		m_oCurrEventResult.m_BinOutEx[i] = m_oTmtHarmTest.m_oHarmParas.m_oBinaryConfig.m_binOutEx[i].nState;

//	UpdateToolButtons();
}

void QSttMacroParaEditViewHarm::slot_LockChanged()
{
	if (!m_oTmtHarmTest.m_oHarmParas.m_bLock)  //解锁状态
	{
		m_oTmtHarmTest.m_oHarmParas.m_bBinStop = TRUE;
		slot_updateParas();
	}

}

void QSttMacroParaEditViewHarm::slot_FT3DataChanged()
{
	if (stt_Frame_IsTestStarted())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QSttMacroParaEditViewHarm::slot_FT3DataChanged[if]."));
		emit sig_updataParas();
	}
}
void QSttMacroParaEditViewHarm::slot_GooseDataChanged()
{
	if (stt_Frame_IsTestStarted())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QSttMacroParaEditViewHarm::slot_GooseDataChanged[if]."));
		emit sig_updataParas();
	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QSttMacroParaEditViewHarm::slot_GooseDataChanged[else]."));
// 		m_bIECParasChanged = TRUE;
// 	}
}

// void QSttMacroParaEditViewHarm::slot_RepairDataChanged()//20220815 zhouhj 可与GOOSE开出数值变化共用
// {
// 	if (stt_Frame_IsTestStarted())
// 	{
// 		emit sig_updataParas();
// 	}
// }

// void QSttMacroParaEditViewHarm::AddWavePlot()
// {
// 	m_pWaveGroupWidget   =  new  WaveGroupWidget(m_testParaView->getMonitor()->GetTabWidget());
// 
// 	//GetTemplateTab_UI()->insertTab(2,   m_pWaveGroupWidget,   tr("波形图"));
// 	(QTabWidget*)(m_testParaView->getMonitor()->GetTabWidget())->insertTab(2,   m_pWaveGroupWidget,   tr("波形图"));
// 	m_pWaveGroupWidget->show();
//}

// void QSttMacroParaEditViewHarm::SetWavePlotTestResource()
// {
// 	m_oTimerWave.start(5);
// }

// void QSttMacroParaEditViewHarm::SetWavePlot()
// {
// 	QHarmWidget  * pHarmWidget   =   (QHarmWidget *)m_testParaView->getMainPara()->m_templateWidget ;
// 
// 	//设置电压和电流结构体指针；
// 	m_pWaveGroupWidget->setArrUIVOL(m_oTmtHarmTest.m_oHarmParas.m_uiVOL);
// 	m_pWaveGroupWidget->setArrUICUR(m_oTmtHarmTest.m_oHarmParas.m_uiCUR);
// 
// 	//设置电压和电流结构体指针；
// 	//m_pWaveGroupWidget->setArrUIVOL(pHarmWidget->m_pSyncParaSet->m_pArrUIVOL);
// 	//m_pWaveGroupWidget->setArrUICUR(pHarmWidget->m_pSyncParaSet->m_pArrUICUR);
// 
// 	m_pWaveGroupWidget->Clear();
// 	m_pWaveGroupWidget->initUI(m_pSttTestResource);
// 
// 
// 	//###############/这里不能改，否则影响谐波刷新#####################//
// 	m_testParaView->getMonitor()->GetTabWidget()->setCurrentIndex(1);//3	m_testParaView->getMonitor()->GetTabWidget()->setCurrentIndex(3);
// 	if (m_pWaveGroupWidget)
// 		m_pWaveGroupWidget->setGeometry(0,  0, m_testParaView->getMonitor()->GetTabWidget()->width()  -  8, m_testParaView->getMonitor()->GetTabWidget()->height());
// 	m_testParaView->getMonitor()->GetTabWidget()->setCurrentIndex(0);//2
// 
// 	updateTabCnt();
// 
// 	//m_DockStaInfo->setFixedSize (this->width(),  80);
// 	int kkk = this->width();
// 	m_DockStaInfo->setMaximumSize(kkk,  90);
// 	//m_DockStaInfo->setGeometry(0,  0, this->width() , 40);
// }

// void QSttMacroParaEditViewHarm::slot_Timer_Wave()
// {
// 	m_oTimerWave.stop();	
// 	SetWavePlot();
// }

// void QSttMacroParaEditViewHarm::slot_DiBianTimer()
// {
// 	if (!stt_Frame_IsTestStarted())
// 		return;
// 
// 	if (m_nAutoStep==0)            // 没有点击自动的时候
// 	{
// 		if (m_nUpdateDataFlag==1)
// 		{
// 			m_nUpdateDataFlag = 0;
// 
// 			slot_updateParas();
// 			if (m_pHarmWidget)
// 			{
// 				m_pHarmWidget->slot_ResetChangeFlag(0);
// 			}
// 			//SendUpdateParameter();	
// 		}
// 	}
// }

// void QSttMacroParaEditViewHarm::slot_pbnAddClicked()
// {
// 	if(!m_nUpdateDataFlag)
// 	{
// 		m_oTimerDiBian.stop();
// 		if (m_pHarmWidget)
// 		{
// 			m_pHarmWidget->slot_ResetChangeFlag(1);
// 		}
// 		m_nUpdateDataFlag = 1;
// 		m_oTimerDiBian.start(700);
// 	}
// }
// 
// void QSttMacroParaEditViewHarm::slot_pbnMinusClicked()
// {
// 	if(!m_nUpdateDataFlag)
// 	{
// 		m_oTimerDiBian.stop();
// 		if (m_pHarmWidget)
// 		{
// 			m_pHarmWidget->slot_ResetChangeFlag(1);
// 		}
// 		m_nUpdateDataFlag = 1;
// 		m_oTimerDiBian.start(700);
// 	}
// }

void QSttMacroParaEditViewHarm::slot_pbnAutoClicked( bool bAuto)
{
	if (bAuto)
	{
		m_nAutoStep = 2;
	}
	else 
	{
		m_nAutoStep = 0;
	}

	if (m_pHarmWidget->ExistGooseParaWidget())
	{
		if (m_nAutoStep==2)
			m_pHarmWidget->m_pGooseParaWidget->setDisabled(true);
		else 
			m_pHarmWidget->m_pGooseParaWidget->setDisabled(false);
	}
	else if (m_pHarmWidget->ExistFT3OutParaWidget())
	{
		if (m_nAutoStep==2)
			m_pHarmWidget->m_pFT3OutParaWidget->setDisabled(true);
		else 
			m_pHarmWidget->m_pFT3OutParaWidget->setDisabled(false);
	}
	else if (m_pHarmWidget->ExistExBinParaWidget())
	{
		if (m_nAutoStep==2)
			m_pHarmWidget->m_pExBinParaWidget->setDisabled(true);
		else 
			m_pHarmWidget->m_pExBinParaWidget->setDisabled(false);
	}
	else if (m_pHarmWidget->ExistExBoutParaWidget())
	{
		if (m_nAutoStep==2)
			m_pHarmWidget->m_pExBoutParaWidget->setDisabled(true);
		else 
			m_pHarmWidget->m_pExBoutParaWidget->setDisabled(false);
	}
}

void QSttMacroParaEditViewHarm::slot_SetToZero()
{
	m_pHarmWidget->slot_ResetChangeFlag(0);
	emit sig_updataParas();
	//谐波清零自己不启动计时器，但slot_updataParas却在计时器中做处理，不正常
	//m_nUpdateDataFlag = 1;
}
// void QSttMacroParaEditViewHarm::slot_CheckStateChanged()
// {
// 	m_nUpdateDataFlag = 1;
// }

void QSttMacroParaEditViewHarm::slot_currentChangedTabWidget(int nCurrIndex)
{
	//判断当前页面
	BOOL bIsGooseCtrls = (m_pHarmWidget->m_pTabWidget->currentWidget() == m_pHarmWidget->m_pGooseParaWidget );
	BOOL bIsFt3Ctrls = (m_pHarmWidget->m_pTabWidget->currentWidget() == m_pHarmWidget->m_pFT3OutParaWidget );
    BOOL bIsWaveCtrls = false;//(m_pHarmWidget->m_pTabWidget->currentWidget() == m_pHarmWidget->m_pOscillogramGroupWidget );
	BOOL bVisibleParaCtrls = (m_pHarmWidget->m_pTabWidget->currentWidget() == m_pHarmWidget->m_pParaWidget );
	//判断页面大小
	BOOL bVisibleHeigthCtrls = ( stt_FrameTestCntrFrameHeight() <700 );
	//判断是否隐藏
	BOOL bVisibleBottomCtrls = !(( bVisibleParaCtrls && bVisibleHeigthCtrls ) || bIsGooseCtrls || bIsWaveCtrls || bIsFt3Ctrls);
	m_pHarmWidget->m_pbn_SetZero->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_pbn_Lock->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_pbn_Add->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_pbn_Del->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_pbnEstimate->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_lne_BasicHarmHz->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_pUChannel->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_pIChannel->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_Label_UChannel->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_Label_IChannel->setVisible(bVisibleBottomCtrls);
	m_pHarmWidget->m_Label_BasicHarmHz->setVisible(bVisibleBottomCtrls);
	

	//chenling 20240403 电压电流表需要全选/清空电压电流按钮
	BOOL bIsVolCurTable = (m_pHarmWidget->m_pTabWidget->currentWidget() == m_pHarmWidget->m_pParaTable );
	if(bIsVolCurTable) 
	{

// 		m_pHarmWidget->m_pVolSelBtn->show();
// 		m_pHarmWidget->m_pCurrSelBtn->show();
		m_pHarmWidget->UpdateVolCurTable(true);
	}
	else
	{
// 		m_pHarmWidget->m_pVolSelBtn->hide();
// 		m_pHarmWidget->m_pCurrSelBtn->hide();
		m_pHarmWidget->UpdateVolCurTable(false);
	}

	if (bIsWaveCtrls)
	{
        //m_pHarmWidget->m_pOscillogramGroupWidget->slot_updateOscillogramGroup();
	}

}
