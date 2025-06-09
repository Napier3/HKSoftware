#include "SttMacroParaEditViewSoe.h"

#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameBase.h"
#include "../SttTestCntrFrameAPI.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Controls/SttTabWidget.h"
#include "../../Module/XLangResource_Native.h"
#include "../State/ShortCalcuDig.h"
#include "../../XLangResource_Native.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewSoe* g_pSoeTest = NULL;

QSttMacroParaEditViewSoe::QSttMacroParaEditViewSoe(QWidget *parent) 
{
	setWindowFlags(Qt::FramelessWindowHint);

	InitUI();
	m_bTmtParaChanged = FALSE;

	m_bIsChanging = FALSE;
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;

	m_strParaFileTitle = g_sLangTxt_SOE_TemplateFile;
	m_strParaFilePostfix = "project(*.mntxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("SoeTest.mntxml");

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	stt_Frame_InitTestResource();

	m_pSoeParas = &m_oSoeTest.m_oSoeParas;
	

	OpenTestTestMngrFile(m_strDefaultParaFile);

	stt_Frame_UpdateToolButtons();

	InitGirdData();
	InitParasView();
	InitConnect();
	
	SetDatas(NULL);
	m_pSoeWidget->SetData(m_pSoeParas);
	m_pSoeParas->m_nSelect = 0;//初始化为主板开出端子
	
	g_pSoeTest = this;
		
	stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
}

QSttMacroParaEditViewSoe::~QSttMacroParaEditViewSoe()
{
}


void QSttMacroParaEditViewSoe::InitGirdData()
{
	
	m_pSoeWidget->m_pSoeGrid->SetData(&m_oSoeTest);
}


void QSttMacroParaEditViewSoe::InitUI()
{
	m_pSoeWidget = new QSttMacroParaEditViewSoeWidget();
	m_pSoeWidget->InitUI();
	setLayout(m_pSoeWidget->m_pMain_VLayout);
}


void QSttMacroParaEditViewSoe::InitConnect()
{
	m_pSoeWidget->initConnections();

	connect(m_pSoeWidget->m_pSelectAll_PushButton, SIGNAL(clicked()), this, SLOT(slot_SelectAll_PushButton_Clicked()));	
	connect(m_pSoeWidget->m_pCancelAll_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelAll_PushButton_Clicked()));

	connect(m_pSoeWidget->m_pInitialAll_PushButton, SIGNAL(clicked()), this, SLOT(slot_InitialAl_PushButton_Clicked()));
	connect(m_pSoeWidget->m_pInitialDivideAll_PushButton, SIGNAL(clicked()), this, SLOT(slot_InitialDivideAll_PushButton_Clicked()));	

	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas()));

#ifdef _PSX_QT_LINUX_


	connect(m_pSoeWidget->m_pHourEdit, SIGNAL(clicked()), this, SLOT(slot_lneH_GPSTimeChanged()),Qt::UniqueConnection);
	connect(m_pSoeWidget->m_pMinuteEdit, SIGNAL(clicked()), this, SLOT(slot_lneM_GPSTimeChanged()),Qt::UniqueConnection);
	connect(m_pSoeWidget->m_pSecondEdit, SIGNAL(clicked()), this, SLOT(slot_lneS_GPSTimeChanged()),Qt::UniqueConnection);
	
	connect(m_pSoeWidget->m_pDeflectio_Edit, SIGNAL(clicked()), this, SLOT(slot_lne_DeflectioChanged()),Qt::UniqueConnection);
	connect(m_pSoeWidget->m_pPulseWidth_Edit, SIGNAL(clicked()), this, SLOT(slot_lne_PulseWidthChanged()),Qt::UniqueConnection);
	connect(m_pSoeWidget->m_pSOE_Edit, SIGNAL(clicked()), this, SLOT(slot_lne_SOEChanged()),Qt::UniqueConnection);

#endif

	connect(m_pSoeWidget->m_pHourEdit, SIGNAL(editingFinished()), this, SLOT(slot_lneH_GPSTimeChangedKeyBoard()));
	connect(m_pSoeWidget->m_pMinuteEdit, SIGNAL(editingFinished()), this, SLOT(slot_lneM_GPSTimeChangedKeyBoard()));
	connect(m_pSoeWidget->m_pSecondEdit, SIGNAL(editingFinished()), this, SLOT(slot_lneS_GPSTimeChangedKeyBoard()));
	connect(m_pSoeWidget->m_pTrigerConditionCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_TrigerCondition_cmb_Changed(int)),Qt::UniqueConnection);

	connect(m_pSoeWidget->m_pDeflectio_Edit, SIGNAL(editingFinished()), this, SLOT(slot_lne_DeflectioChangedKeyBoard()));
	connect(m_pSoeWidget->m_pPulseWidth_Edit, SIGNAL(editingFinished()), this, SLOT(slot_lne_PulseWidthChangedKeyBoard()));
	connect(m_pSoeWidget->m_pSOE_Edit, SIGNAL(editingFinished()), this, SLOT(slot_lne_SOEChangedKeyBoard()));

}

CSttTestResourceBase* QSttMacroParaEditViewSoe::CreateTestResource()
{
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewSoe::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
									long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	//yzj 2022-2-21 开始测试前要保持该值为0
// 	if(!stt_Frame_IsTestStarted())
// 	{
// 		//m_pManualParas->m_bBinStop = FALSE;
// 	}
// 
	tmt_SoeTest *pSoeTest = (tmt_SoeTest *)pParas;

	stt_xml_serialize(&pSoeTest->m_oSoeParas, pMacroParas);

	if (bHasGoosePub)
	{
		CIecCfgGoutDatas *pGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr()/*m_listGoosePub.at(0)*/;
		ASSERT(pGoutDatas);
		SerializeGoosePubs(pMacroParas,pGoutDatas);

		CIecCfgDatasSMV *pDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
		ASSERT(pDatasSMV);
		SerializeFT3Pubs(pMacroParas,pDatasSMV);
	}
}



void QSttMacroParaEditViewSoe::SetManualOtherParasFont()
{
 	m_pSoeWidget->m_pSoeGrid->setFont(*g_pSttGlobalFont);
 	m_pSoeWidget->m_pSoeGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		
	m_pSoeWidget->m_pSoeTab->setFont(*g_pSttGlobalFont);
	
	m_pSoeWidget->m_pPulseWidth_Label->setFont(*g_pSttGlobalFont);

	m_pSoeWidget->m_pPulseWidth_Edit->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pSOE_Edit->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pSOE_Label->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pDeflectio_Edit->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pDeflection_Label->setFont(*g_pSttGlobalFont);

	m_pSoeWidget->m_pSelectAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pCancelAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pInitialAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pInitialDivideAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pTrigger_Label->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pTrigerConditionCombox->setFont(*g_pSttGlobalFont);

	m_pSoeWidget->m_pGPSTime_Label->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pHourEdit->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pHourEdit->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pHourEdit->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pMinuteEdit->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pSecondEdit->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pHourLabel->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pMinuteLabel->setFont(*g_pSttGlobalFont);
	m_pSoeWidget->m_pSecondLabel->setFont(*g_pSttGlobalFont);

}

void QSttMacroParaEditViewSoe::InitOtherParasUI()
{
	SetManualOtherParasFont();
}


void QSttMacroParaEditViewSoe::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateGoutTab();
	UpdateBinBoutExTab();
	UpdateFT3Tab();
}


void QSttMacroParaEditViewSoe::UpdateGoutTab(BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)//zhouhj 在打开测试模板前先初始化当前GOOSE发布数据
	{
		UpdateGoutTab_UI(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr()/*m_listGoosePub.at(0)*/);
	}
	else
	{
		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewSoe::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if ((m_pGooseParaWidget == NULL)&&(g_oSystemParas.m_nHasDigital)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC> 0))//更新前无GOOSE界面,更新后需要GOOSE界面
	{
		AddGooseParaWidget(pCfgGoutDatas);

		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
	}
	else if ((m_pGooseParaWidget != NULL)&&(!g_oSystemParas.m_nHasDigital))//更新前有GOOSE界面,更新后不需要
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		RemoveGooseParaWidget();
	}
	else if ((m_pGooseParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
		m_pGooseParaWidget->initGoosePubTable(pCfgGoutDatas);
		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
	}
	else if ((m_pGooseParaWidget != NULL)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC == 0))//更新前有GOOSE界面,更新后LC口为0不需要
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewSoe::UpdateFT3Tab(BOOL bUpdateList /* = FALSE */)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		UpdateFT3Tab_UI(g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr());
	}
	else
	{
		RemoveFT3OutParaWidget();
	}
}

void QSttMacroParaEditViewSoe::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
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

	if ((m_pFT3OutParaWidget == NULL)&&(g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0) && (nFT3Block > 0))
	{
		AddFT3OutParaWidget(pIecCfgDatasSMV);
		connect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
	else if ((m_pFT3OutParaWidget != NULL)&&(!g_oSystemParas.IsDigitalOutputFT3()))
	{
		disconnect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		RemoveFT3OutParaWidget();
	}
	else if ((m_pFT3OutParaWidget != NULL)&&(g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0))
	{
		if(nFT3Block > 0)
	{
		disconnect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		m_pFT3OutParaWidget->InitFT3Table(pIecCfgDatasSMV);
		connect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
		else
		{
			disconnect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
			RemoveFT3OutParaWidget();
		}
	}
}

void QSttMacroParaEditViewSoe::slot_GooseDataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}
// 
// 	SetParaChanged();
}

void QSttMacroParaEditViewSoe::slot_FT3DataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}
}

void QSttMacroParaEditViewSoe::slot_updateParas()
{
	if (stt_Frame_IsTestStarted() )  
	{
		SendUpdateParameter();
	}

// 	stt_Frame_UpdateVectorData();
// 	stt_Frame_UpdatePowerData();
	

	SetParaChanged();
} 

void QSttMacroParaEditViewSoe::UpdateBinBoutExTab()
{
	//当前页面无拓展开入开出
}


void QSttMacroParaEditViewSoe::UpdateSoeParas()
{
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewSoe::SendUpdateParameter()
{
	stt_Frame_Ats_UpdateParameter();
}


void QSttMacroParaEditViewSoe::ClearResult(PTMT_PARAS_HEAD pHead)
{
	m_oSoeTest.m_oSoeResult.init();
}

void QSttMacroParaEditViewSoe::OnTestResults(CDataGroup *pResults)
{
	ASSERT(pResults != NULL);

	m_oSoeTest.m_nTestState = 1;	//测试完成
}

void QSttMacroParaEditViewSoe::InitStyle()
{
	m_pSoeWidget->m_pSoeTab->InitStyleSheet();
}

void QSttMacroParaEditViewSoe::InitParasView()
{
	InitStyle();
	InitOtherParasUI();
}

void QSttMacroParaEditViewSoe::InitBinStateOnStarting()
{
}


void QSttMacroParaEditViewSoe::OnViewTestLink(BOOL b)
{

}


void QSttMacroParaEditViewSoe::OnViewTestStart()
{
	InitBinStateOnStarting();
	BOOL bEnableState = TRUE;
	int nGooseParasUI_State = STT_UI_RUN_STATE_StateTested_Editable;

	if (m_pGooseParaWidget != NULL)
	{
		m_pGooseParaWidget->SetRunState(nGooseParasUI_State);
		m_pGooseParaWidget->SetGooseDisabled(!bEnableState);
	}

	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	stt_Frame_ClearInfoWidget();
	m_pSoeWidget->StartInit();


	if( m_pGooseParaWidget)
	{
		m_pGooseParaWidget->setDisabled(true);
	}

	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();

	stt_Frame_EnableManualTriggerButton(false);

	if (m_pFT3OutParaWidget != NULL)
	{
		m_pFT3OutParaWidget->SetRunState(nGooseParasUI_State);
		m_pFT3OutParaWidget->SetGooseDisabled(!bEnableState);
		m_pFT3OutParaWidget->setDisabled(true);
	}
}

void QSttMacroParaEditViewSoe::OnViewTestStop()
{
	if (m_pGooseParaWidget)
	{
		m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_Stoped);
		m_pGooseParaWidget->SetGooseDisabled(FALSE);
	}

	m_pSoeWidget->StopInit();
	if(m_pGooseParaWidget)
	{
		m_pGooseParaWidget->setDisabled(false);
	}
	stt_Frame_StopStateMonitor();
	stt_Frame_StopVectorWidget(false);//20220628 zhouhj 暂时改为不更新界面参数,防止界面参数被修改为0
	stt_Frame_StopPowerWidget(false);

	if (m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_Stoped);
		m_pFT3OutParaWidget->SetGooseDisabled(FALSE);
		m_pFT3OutParaWidget->setDisabled(false);
	}
}



void QSttMacroParaEditViewSoe::ShowReport(CDvmValues *pValues)
{
	CDvmValue* pActValueData = (CDvmValue*)pValues->FindByID("ActValue");
	CDvmValue* pActTimeData = (CDvmValue*)pValues->FindByID("TripTime");
	CDvmValue* pActReturnData = (CDvmValue*)pValues->FindByID("ReturnValue");
	CDvmValue* pActReturnTimeData = (CDvmValue*)pValues->FindByID("ReturnTime");

	float fActValue = 0, fActTime = 0, fReturnValue = 0, fReturnTime = 0;

	if (pActValueData != NULL)
	{
		fActValue = GlobalSetResultValue(pActValueData,3);
	}

	if (pActTimeData != NULL)
	{
		fActTime = GlobalSetResultValue(pActTimeData,4);
	}

	if (pActReturnData != NULL)
	{
		fReturnValue = GlobalSetResultValue(pActReturnData,3);
	}

	if (pActReturnTimeData != NULL)
	{
		fReturnTime = GlobalSetResultValue(pActReturnTimeData,4);
	}
}

CString QSttMacroParaEditViewSoe::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += STT_ORG_MACRO_SoeTest;
	strFile += _T(".");
	strFile += "mntxml";

	return strFile;
}

bool QSttMacroParaEditViewSoe::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
{
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != "mntxml")
	{
		return false;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return false;
	}

	return true;
}

void QSttMacroParaEditViewSoe::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}


void QSttMacroParaEditViewSoe::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,TRUE);
	int nInsertPos = 2;
    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	m_pSoeWidget->m_pSoeTab->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewSoe::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,TRUE);
	int nInsertPos = 3;
	CString strTitle;
	strTitle=/*_T("FT3发布")*/g_sLangTxt_Gradient_ReleasedFTT;
	m_pSoeWidget->m_pSoeTab->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewSoe::RemoveGooseParaWidget()
{
	if(m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pSoeWidget->m_pSoeTab->indexOf(m_pGooseParaWidget);
	m_pSoeWidget->m_pSoeTab->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QSttMacroParaEditViewSoe::RemoveFT3OutParaWidget()
{
	if(m_pFT3OutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pSoeWidget->m_pSoeTab->indexOf(m_pFT3OutParaWidget);
	m_pSoeWidget->m_pSoeTab->removeTab(nIndex);

	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

bool QSttMacroParaEditViewSoe::ExistGooseParaWidget()
{
	int nIndex = m_pSoeWidget->m_pSoeTab->indexOf(m_pGooseParaWidget);
	return (nIndex>=0);
}

bool QSttMacroParaEditViewSoe::ExistFT3OutParaWidget()
{
	int nIndex = m_pSoeWidget->m_pSoeTab->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewSoe::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		m_pSoeWidget->m_pSoeTab->setTabEnabled(m_pSoeWidget->m_pSoeTab->indexOf(m_pGooseParaWidget),b);
	}
}

void QSttMacroParaEditViewSoe::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		m_pSoeWidget->m_pSoeTab->setTabEnabled(m_pSoeWidget->m_pSoeTab->indexOf(m_pFT3OutParaWidget),b);
	}
}

void QSttMacroParaEditViewSoe::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pSoeParas, &oRead);
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系
	}

    stt_Frame_InitStateMonitor();
    stt_Frame_ClearInfoWidget();

    UpdateSoeParas();
}


void QSttMacroParaEditViewSoe::slot_SelectAll_PushButton_Clicked()
{
	m_pSoeWidget->m_pSoeGrid->SetSelState_SelectAll();
	SetParaChanged();

}

void QSttMacroParaEditViewSoe::slot_CancelAll_PushButton_Clicked()
{
	m_pSoeWidget->m_pSoeGrid->SetSelState_UnSelectAll();
	SetParaChanged();
}

void QSttMacroParaEditViewSoe::slot_InitialAl_PushButton_Clicked()
{
	m_pSoeWidget->m_pSoeGrid->SetSelState_InitialAll();
	SetParaChanged();
	

}

void QSttMacroParaEditViewSoe::slot_InitialDivideAll_PushButton_Clicked()
{
	m_pSoeWidget->m_pSoeGrid->SetSelState_UnInitialAll();
	SetParaChanged();
	

}



void QSttMacroParaEditViewSoe::slot_lneH_GPSTimeChanged()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ShowSmoothKeyboard();
#endif

	QString strValue =m_pSoeWidget->m_pHourEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pSoeWidget->m_pHourEdit,this);


}

void QSttMacroParaEditViewSoe::slot_lneH_GPSTimeChangedKeyBoard()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

	QString strValue = m_pSoeWidget->m_pHourEdit->text();

	float h = strValue.toFloat();
	if (h>23)
	{
		h = m_pSoeParas->m_tGps.nHour;
	}

	if (m_pSoeParas->m_tGps.nHour != h)
	{
		m_pSoeParas->m_tGps.nHour = h;
		m_bTmtParaChanged = TRUE;
	}

	if (m_pSoeParas->m_tGps.nHour<10)
	{
		m_pSoeWidget->m_pHourEdit->setText("0"+QString::number(m_pSoeParas->m_tGps.nHour,10));
	}
	else
	{
		m_pSoeWidget->m_pHourEdit->setText(QString::number(m_pSoeParas->m_tGps.nHour,10));
	}
}

void QSttMacroParaEditViewSoe::slot_lneM_GPSTimeChanged()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ShowSmoothKeyboard();
#endif

	QString strValue = m_pSoeWidget->m_pMinuteEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pSoeWidget->m_pMinuteEdit,this);

}

void QSttMacroParaEditViewSoe::slot_lneM_GPSTimeChangedKeyBoard()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

	QString strValue = m_pSoeWidget->m_pMinuteEdit->text();

	float m = strValue.toFloat();

	if (m>59)
	{
		m = m_pSoeParas->m_tGps.nMinutes;
	}

	if (m_pSoeParas->m_tGps.nMinutes != m)
	{
		m_pSoeParas->m_tGps.nMinutes = m;
		m_bTmtParaChanged = TRUE;
	}

	if (m_pSoeParas->m_tGps.nMinutes<10)
	{
		m_pSoeWidget->m_pMinuteEdit->setText("0"+QString::number(m_pSoeParas->m_tGps.nMinutes,10));
	}
	else
	{
		m_pSoeWidget->m_pMinuteEdit->setText(QString::number(m_pSoeParas->m_tGps.nMinutes,10));
	}
}


void QSttMacroParaEditViewSoe::slot_lneS_GPSTimeChanged()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ShowSmoothKeyboard();
#endif

	QString strValue = m_pSoeWidget->m_pSecondEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pSoeWidget->m_pSecondEdit,this);


}

void QSttMacroParaEditViewSoe::slot_lneS_GPSTimeChangedKeyBoard()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

	QString strValue = m_pSoeWidget->m_pSecondEdit->text();

	float s = strValue.toFloat();

	if (s>59)
	{
		s = m_pSoeParas->m_tGps.nSeconds;
	}

	if (m_pSoeParas->m_tGps.nSeconds != s)
	{
		m_pSoeParas->m_tGps.nSeconds = s;
		m_bTmtParaChanged = TRUE;
	}

	if (m_pSoeParas->m_tGps.nSeconds<10)
	{
		m_pSoeWidget->m_pSecondEdit->setText("0"+QString::number(m_pSoeParas->m_tGps.nSeconds,10));
	}
	else
	{
		m_pSoeWidget->m_pSecondEdit->setText(QString::number(m_pSoeParas->m_tGps.nSeconds,10));
	}
}

void QSttMacroParaEditViewSoe::slot_TrigerCondition_cmb_Changed(int index)
{
	if (m_pSoeWidget->m_pTrigerConditionCombox->IsScrolling())
	{
		return;
	}

	m_pSoeWidget->slot_cmb_TrigerConditionChanged(index);


}

void QSttMacroParaEditViewSoe::slot_lne_PulseWidthChanged()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ShowSmoothKeyboard();
#endif

	QString strValue = m_pSoeWidget->m_pPulseWidth_Edit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pSoeWidget->m_pPulseWidth_Edit,this);


	float nTime = strValue.toFloat();

	if ((nTime > m_pSoeWidget->m_pSoeGrid->m_nTime) )
	{
		nTime =  m_pSoeWidget->m_pSoeGrid->m_nTime;
	}

	if (nTime < 20)
	{
		nTime = 20;
	}

	int nRows = m_pSoeWidget->m_pSoeGrid->rowCount();

	for(int i = 0 ; i <nRows; i++)
	{
		QTableWidgetItem *pItem = m_pSoeWidget->m_pSoeGrid->item(i,1);

		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pSoeParas->m_binOut[i].otmt_SoeState[1].time = nTime;
			m_pSoeParas->m_binOut[i].otmt_SoeState[2].time = nTime;

			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,5);
			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,6);
		}
	}


}

void QSttMacroParaEditViewSoe::slot_lne_PulseWidthChangedKeyBoard()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

	QString strValue = m_pSoeWidget->m_pPulseWidth_Edit->text();

	float nTime = strValue.toFloat();

	if ((nTime > m_pSoeWidget->m_pSoeGrid->m_nTime) )
	{
		nTime =  m_pSoeWidget->m_pSoeGrid->m_nTime;
	}

	if (nTime < 20)
	{
		nTime = 20;
	}

	int nRows = m_pSoeWidget->m_pSoeGrid->rowCount();

	for(int i = 0 ; i <nRows; i++)
	{
		QTableWidgetItem *pItem = m_pSoeWidget->m_pSoeGrid->item(i,1);

		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pSoeParas->m_binOut[i].otmt_SoeState[1].time = nTime;
			m_pSoeParas->m_binOut[i].otmt_SoeState[2].time = nTime;

			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,5);
			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,6);
		}
	}

	m_pSoeWidget->m_pPulseWidth_Edit->setText(QString::number(nTime));

}

void QSttMacroParaEditViewSoe::slot_lne_SOEChanged()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ShowSmoothKeyboard();
#endif

	QString strValue = m_pSoeWidget->m_pSOE_Edit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pSoeWidget->m_pSOE_Edit,this);

	float fTime = strValue.toFloat();


	if (fTime <= 0)
	{
		fTime = 0.1;
	}

	int nRows = m_pSoeWidget->m_pSoeGrid->rowCount();
	int nIndex = 0;
	float fPulseWidth,fSum,fCount,fBreakTime,fNumber;

	for(int i = 0 ; i <nRows; i++)
	{
		QTableWidgetItem *pItem = m_pSoeWidget->m_pSoeGrid->item(i,1);

		if (pItem->checkState() !=  Qt::Unchecked)
		{
			

			fPulseWidth =  m_pSoeParas->m_binOut[i].otmt_SoeState[1].time;
			fBreakTime = m_pSoeParas->m_binOut[i].otmt_SoeState[2].time;

			fSum = fPulseWidth + fBreakTime;

			fNumber = fSum +fTime;
			fCount = fSum - fTime;



			if (nIndex == 0)
			{
				m_pSoeParas->m_binOut[i].otmt_SoeState[1].time = fPulseWidth;
				m_pSoeParas->m_binOut[i].otmt_SoeState[2].time = fBreakTime;
			}
			else
			{
				if (fSum >= fPulseWidth*2)
				{
					fSum = fPulseWidth*2 - 1;
				}

				if (fCount < 1)
				{
					fCount = 1;
				}

				m_pSoeParas->m_binOut[i].otmt_SoeState[1].time = fNumber;
				m_pSoeParas->m_binOut[i].otmt_SoeState[2].time = fCount;

				fNumber = fNumber + fTime;

				fCount = fCount - fTime;


			}

			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,5);
			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,6);

			nIndex ++;
		}
	}

}

void QSttMacroParaEditViewSoe::slot_lne_SOEChangedKeyBoard()
{

	if (m_pSoeParas == NULL)
	{
		return;
	}

	QString strValue = m_pSoeWidget->m_pSOE_Edit->text();

	float fTime = strValue.toFloat();

// 	if ((nTime > m_pSoeWidget->m_pSoeGrid->m_nTime) )
// 	{
// 		nTime =  m_pSoeWidget->m_pSoeGrid->m_nTime;
// 	}
// 
	if (fTime <= 0)
	{
		fTime = 0.1;
	}

	int nRows = m_pSoeWidget->m_pSoeGrid->rowCount();
	int nIndex = 0;

	float fPulseWidth,fSum,fCount,fBreakTime,fNumber;

	for(int i = 0 ; i <nRows; i++)
	{
		QTableWidgetItem *pItem = m_pSoeWidget->m_pSoeGrid->item(i,1);

		if (pItem->checkState() !=  Qt::Unchecked)
		{			
			if (nIndex == 0)
			{
				fPulseWidth =  m_pSoeParas->m_binOut[i].otmt_SoeState[1].time;
				fBreakTime = m_pSoeParas->m_binOut[i].otmt_SoeState[2].time;
			
				fSum = fPulseWidth + fBreakTime;//获取到第一个数据断开时长和闭合时长总和

				fNumber = fPulseWidth +fTime;
				fCount = fBreakTime - fTime;

			}
			else
			{

				if (fNumber >= fSum)
				{
					fNumber = fSum - 1;
				}

				if (fCount < 1)
				{
					fCount = 1;
				}

				m_pSoeParas->m_binOut[i].otmt_SoeState[1].time = fNumber;
				m_pSoeParas->m_binOut[i].otmt_SoeState[2].time = fCount;


				fNumber = fNumber +fTime;
				fCount = fCount - fTime;

			}

			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,5);
			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,6);

			nIndex ++;
		}
	}


	m_pSoeWidget->m_pSOE_Edit->setText(QString::number(fTime));
}

void QSttMacroParaEditViewSoe::slot_lne_DeflectioChanged()
{	
	if (m_pSoeParas == NULL)
	{
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ShowSmoothKeyboard();
#endif

	QString strValue = m_pSoeWidget->m_pDeflectio_Edit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pSoeWidget->m_pDeflectio_Edit,this);

	int nCnt = strValue.toInt();

	if (nCnt > m_pSoeWidget->m_pSoeGrid->m_nCnt )
	{
		nCnt =  m_pSoeWidget->m_pSoeGrid->m_nCnt;
	}

	if (nCnt < 1)
	{
		nCnt = 1;
	}

	if (nCnt > 1000) //SOE变位次数限制1000
	{
		nCnt = 1000;
	}

	int nRows = m_pSoeWidget->m_pSoeGrid->rowCount();

	for(int i = 0 ; i <nRows; i++)
	{
		QTableWidgetItem *pItem = m_pSoeWidget->m_pSoeGrid->item(i,1);

		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pSoeParas->m_binOut[i].cnt = nCnt;

			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,7);
		}
	}

}

void QSttMacroParaEditViewSoe::slot_lne_DeflectioChangedKeyBoard()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}

	QString strValue = m_pSoeWidget->m_pDeflectio_Edit->text();

	int nCnt = strValue.toInt();

	if (nCnt > 1000) //SOE变位次数限制1000
	{
		nCnt = 1000;
	}

	int nRows = m_pSoeWidget->m_pSoeGrid->rowCount();

	for(int i = 0 ; i <nRows; i++)
	{
		QTableWidgetItem *pItem = m_pSoeWidget->m_pSoeGrid->item(i,1);

		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pSoeParas->m_binOut[i].cnt = nCnt;

			m_pSoeWidget->m_pSoeGrid->UpdateTable(i,7);
		}
	}

	m_pSoeWidget->m_pDeflectio_Edit->setText(QString::number(nCnt));

}


