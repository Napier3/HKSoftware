#include "SttMacroParaEditViewIntelligentTerminal.h"
#include "ui_SttMacroParaEditViewManual.h"
#include "../../SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"
#include "../../Module/XLangResource_Native.h"
#include "../../Engine/SttPowerTestEngineBase.h"
#include "../State/ShortCalcuDig.h"


#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewIntelligentTerminal* g_pIntelligentTest = NULL;

QSttMacroParaEditViewIntelligentTerminal::QSttMacroParaEditViewIntelligentTerminal(QWidget *parent) 
{
	setWindowFlags(Qt::FramelessWindowHint);
	InitUI();
	m_bTmtParaChanged = FALSE;
	m_pSttIntelGoutToBinParaWidget = NULL;
	m_pSttIntelBoutToGinParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;

	m_strParaFileTitle = g_sLangTxt_State_Genexperfile;
	m_strParaFilePostfix = "project(*.Intxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("IntelligentTest.Intxml");

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	g_theTestCntrFrame->InitTestResource();
	m_pIntellTerminalParas = &m_oIntellTerminalTest.m_oManuParas;

	OpenTestTestMngrFile(m_strDefaultParaFile);

	CopyBinaryConfig();
	g_theTestCntrFrame->UpdateToolButtons();

	InitIVView();
	InitParasView();
	InitConnect();

     g_pIntelligentTest = this;
 
	SetDatas(NULL);
	g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);	
	g_theTestCntrFrame->InitPowerWidget(m_uiVOL,m_uiCUR);
	UpdateGoutTab();
}



QSttMacroParaEditViewIntelligentTerminal::~QSttMacroParaEditViewIntelligentTerminal()
{
}

void QSttMacroParaEditViewIntelligentTerminal::InitUI()
{
	m_pIntellTerminalWidget = new QIntellTerminalWidget(this);
	m_pIntellTerminalWidget->InitUI();
	setLayout(m_pIntellTerminalWidget->m_pMainGridLayout);
}

void QSttMacroParaEditViewIntelligentTerminal::SendUpdateParameter()
{
	g_theTestCntrFrame->Ats_UpdateParameter();
	
	//20231222 gongyiping 确保在非数字模拟测试中GOOSE发布根据取反重新获取测试开入量变化的时间
	if (!g_oSystemParas.m_nHasDigital&&m_pIntellTerminalParas->m_nFuncType==0)
	{
		CString strItemPath = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
		CString strMacroID = _T("");
		strItemPath += "$" + strItemPath;
		long nIndex = strItemPath.Find(_T("Test"));
		if (nIndex>=0)
		{
			CString strItemPathNodes=g_pTheSttTestApp->m_pTestMacroUI->m_strID.Left(nIndex);
		strItemPath+= "$" + strItemPathNodes;
		}
		
		strMacroID=STT_ORG_MACRO_BinaryManuTest;//开关量手动测试MarcoID
		g_theTestCntrFrame->GetTestCtrlCntrBase()->Ats_SetItemPara(strItemPath, strMacroID);
	}
}

void QSttMacroParaEditViewIntelligentTerminal::CopyBinaryConfig(BOOL b)
{
	if(b)
	{
		g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic = m_pIntellTerminalParas->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect = m_pIntellTerminalParas->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binOut[i].nState = m_pIntellTerminalParas->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i].nSelect = m_pIntellTerminalParas->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binOutEx[i].nState = m_pIntellTerminalParas->m_binOutEx[i].nState;
		}
	}
	else
	{
		m_pIntellTerminalParas->m_nBinLogic = g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			m_pIntellTerminalParas->m_binIn[i].nSelect = g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			m_pIntellTerminalParas->m_binOut[i].nState = g_theTestCntrFrame->GetBinaryConfig()->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pIntellTerminalParas->m_binInEx[i].nSelect = g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pIntellTerminalParas->m_binOutEx[i].nState = g_theTestCntrFrame->GetBinaryConfig()->m_binOutEx[i].nState;
		}
	}
}

void QSttMacroParaEditViewIntelligentTerminal::InitConnect()
{
	connect(m_pIntellTerminalWidget->m_pBinarySet_PushButton, SIGNAL(clicked()), this, SLOT(slot_BinarySetPushButton_clicked()));
	connect(m_pIntellTerminalWidget->m_pIntellTerminalTab,SIGNAL(currentChanged(int)),this,SLOT(slot_TabPageChanged(int)));
	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas()));
//	connect(g_theTestCntrFrame,SIGNAL(sig_UpdateEventMsgTime(CEventResult*)),this,SLOT(slot_UpdateEventMsgTime(CEventResult*)));
}

CSttTestResourceBase* QSttMacroParaEditViewIntelligentTerminal::CreateTestResource()
{
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewIntelligentTerminal::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
									long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	tmt_manual_test *pTmtManualTest = (tmt_manual_test *)pParas;
	stt_xml_serialize(&pTmtManualTest->m_oManuParas, pMacroParas,nVolRsNum,nCurRsNum);

	if (stt_xml_serialize_is_read(pMacroParas))
	{
		InitGoosePubDataGroups();	
		InitGooseGinPubDataGroups();
	}
	CIecCfgGoutDatas *pGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr()/*m_listGoosePub.at(0)*/;
	CIecCfgGinDatas *pGinDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGinMngr();

	if (bHasGoosePub)
	{
		ASSERT(pGoutDatas);
		SerializeGoosePubs(pMacroParas,pGoutDatas);
		ASSERT(pGinDatas);
		SerializeGooseGinPubs(pMacroParas,pGinDatas);
	}


	if (bHasGoosePub)
	{
		CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
		ASSERT(pIecCfgDatasSMV);
		SerializeFT3Pubs(pMacroParas,pIecCfgDatasSMV);
	}
}

void QSttMacroParaEditViewIntelligentTerminal::OnTestResults(CDataGroup *pResults)
{
	ASSERT(pResults != NULL);

	m_oIntellTerminalTest.m_nTestState = 1;	//测试完成
}

void QSttMacroParaEditViewIntelligentTerminal::InitBinaryInBinaryOutUI()
{
}

void QSttMacroParaEditViewIntelligentTerminal::SetManualOtherParasFont()
{
 	m_pIntellTerminalWidget->m_pBinarySet_PushButton->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewIntelligentTerminal::InitOtherParasUI()
{
	SetManualOtherParasFont();
}

void QSttMacroParaEditViewIntelligentTerminal::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateFT3Tab();
	UpdateBinBoutExTab();

	m_pIntellTerminalWidget->SetData(g_theTestCntrFrame->GetSttTestResource(), m_pIntellTerminalParas, 0);
	InitBinaryInBinaryOutUI();
}

void QSttMacroParaEditViewIntelligentTerminal::UpdateGoutTab(BOOL bUpdateList)
{
	UpdateGoutTab_UI(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr(),g_oSttTestResourceMngr.m_oIecDatasMngr.GetGinMngr()/*m_listGoosePub.at(0)*/);
}

void QSttMacroParaEditViewIntelligentTerminal::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas,CIecCfgGinDatas* pCfgGinDatas)
{
	if ((m_pSttIntelGoutToBinParaWidget == NULL)&&(m_pSttIntelBoutToGinParaWidget == NULL))//更新前无GOOSE界面,更新后需要GOOSE界面
	{
		AddGooseParaWidget(pCfgGoutDatas,pCfgGinDatas);

		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_RevertData()), this, SLOT(slot_RevertData()));
		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_GoutRowIndex(int)),this,SLOT(slot_GoutRowIndex(int)));
		connect(m_pSttIntelGoutToBinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));
		
		connect(m_pSttIntelBoutToGinParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
		connect(m_pSttIntelBoutToGinParaWidget, SIGNAL(sig_setBinOut(int,bool)), this, SLOT(slot_setBinOut(int,bool)));
		connect(m_pSttIntelBoutToGinParaWidget, SIGNAL(sig_GinRowIndex(int,float)),this,SLOT(slot_GinRowIndex(int,float)));
		connect(m_pSttIntelBoutToGinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));

	}
	else if ((m_pSttIntelGoutToBinParaWidget != NULL)||(m_pSttIntelBoutToGinParaWidget != NULL))//更新前有GOOSE界面,更新GOOSE界面
	{
		disconnect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
		disconnect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_RevertData()), this, SLOT(slot_RevertData()));
		disconnect(m_pSttIntelGoutToBinParaWidget,SIGNAL(sig_GoutRowIndex(int)),this,SLOT(slot_GoutRowIndex(int)));
		disconnect(m_pSttIntelGoutToBinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));
		m_pSttIntelGoutToBinParaWidget->initGoosePubTable(pCfgGoutDatas);
		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_RevertData()), this, SLOT(slot_RevertData()));
		connect(m_pSttIntelGoutToBinParaWidget, SIGNAL(sig_GoutRowIndex(int)),this,SLOT(slot_GoutRowIndex(int)));
		connect(m_pSttIntelGoutToBinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));

		disconnect(m_pSttIntelBoutToGinParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pSttIntelBoutToGinParaWidget, SIGNAL(sig_setBinOut(int,bool)), this, SLOT(slot_setBinOut(int,bool)));
		disconnect(m_pSttIntelBoutToGinParaWidget, SIGNAL(sig_GinRowIndex(int,float)),this,SLOT(slot_GinRowIndex(int,float)));
		disconnect(m_pSttIntelBoutToGinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));
		m_pSttIntelBoutToGinParaWidget->initGoosePubTable(pCfgGinDatas);
		connect(m_pSttIntelBoutToGinParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()),Qt::DirectConnection);
		connect(m_pSttIntelBoutToGinParaWidget, SIGNAL(sig_setBinOut(int,bool)), this, SLOT(slot_setBinOut(int,bool)));
		connect(m_pSttIntelBoutToGinParaWidget, SIGNAL(sig_GinRowIndex(int,float)),this,SLOT(slot_GinRowIndex(int,float)));
		connect(m_pSttIntelBoutToGinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));
	}
	m_nTestIndex=0;
	init();
	
}

void QSttMacroParaEditViewIntelligentTerminal::UpdateFT3Tab(BOOL bUpdateList)
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

void QSttMacroParaEditViewIntelligentTerminal::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if ((m_pFT3OutParaWidget == NULL)&&(g_oSystemParas.IsDigitalOutputFT3()))
	{
		AddFT3OutParaWidget(pIecCfgDatasSMV);

		connect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
	else if ((m_pFT3OutParaWidget != NULL)&&(!g_oSystemParas.IsDigitalOutputFT3()))
	{
		disconnect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));

		RemoveFT3OutParaWidget();
	}
	else if ((m_pFT3OutParaWidget != NULL)&&(g_oSystemParas.IsDigitalOutputFT3()))
	{
		disconnect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		m_pFT3OutParaWidget->InitFT3Table(pIecCfgDatasSMV);
		connect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
}

void QSttMacroParaEditViewIntelligentTerminal::slot_GooseDataChanged()
{
	if (g_theTestCntrFrame->IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewIntelligentTerminal::slot_FT3DataChanged()
{
	if (g_theTestCntrFrame->IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewIntelligentTerminal::UpdateBinBoutExTab()
{
	//当前页面无拓展开入开出
}

void QSttMacroParaEditViewIntelligentTerminal::UpdateManualParas()
{
	m_pIntellTerminalWidget->UpdateData();
	
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewIntelligentTerminal::UpdateEventMsg(CEventResult *pCurrEventResult)
{
	slot_UpdateEventMsgTime(pCurrEventResult);
}

void QSttMacroParaEditViewIntelligentTerminal::ClearResult(PTMT_PARAS_HEAD pHead)
{
	m_oIntellTerminalTest.m_oManuResult.init();
}

void QSttMacroParaEditViewIntelligentTerminal::InitStyle()
{
	((QSttTabWidget*)m_pIntellTerminalWidget->m_pIntellTerminalTab)->InitStyleSheet();
}

void QSttMacroParaEditViewIntelligentTerminal::InitParasView()
{
	InitStyle();
	InitOtherParasUI();
	InitBinaryInBinaryOutUI();
}

void QSttMacroParaEditViewIntelligentTerminal::InitIVView()
{  
	setFont(*g_pSttGlobalFont);
 	m_pIntellTerminalWidget->m_pIntellTerminalTab->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewIntelligentTerminal::slot_SwitchStateChanged()
{
	m_pIntellTerminalWidget->UpdateData();//更新开出量状态

	if (g_theTestCntrFrame->IsTestStarted())
	{
		SendUpdateParameter();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewIntelligentTerminal::slot_setBinOut(int nbout ,bool bStateChanged)
{
	if (bStateChanged)
	{
		m_pIntellTerminalParas->m_binOut[nbout].nState=1;
	} 
	else
	{
		m_pIntellTerminalParas->m_binOut[nbout].nState=0;
	}
	CopyBinaryConfig();
	g_theTestCntrFrame->SyncBinOutDatas();	
	g_theTestCntrFrame->UpdateToolButtons();
	slot_GooseDataChanged();
}

void QSttMacroParaEditViewIntelligentTerminal::InitBinStateOnStarting()
{

	
}

void QSttMacroParaEditViewIntelligentTerminal::OnViewTestLink(BOOL b)
{

}


void QSttMacroParaEditViewIntelligentTerminal::OnViewTestStart()
{
	InitBinStateOnStarting();

	BOOL bEnableState = TRUE;
	startInit(bEnableState,STT_UI_RUN_STATE_StateTested_NotEditable);

	if (m_pFT3OutParaWidget != NULL)
	{
		m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_NotEditable);
		m_pFT3OutParaWidget->SetGooseDisabled(bEnableState);
	}

	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	g_theTestCntrFrame->ClearInfoWidget();
	m_pIntellTerminalWidget->StartInit();

	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();

	g_theTestCntrFrame->EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewIntelligentTerminal::OnViewTestStop()
{
	disconnect(m_pSttIntelGoutToBinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));
	disconnect(m_pSttIntelBoutToGinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));

	BOOL bEnableState = FALSE;
	stopInit(bEnableState,STT_UI_RUN_STATE_Stoped);
	m_pIntellTerminalWidget->m_pIntellTerminalTab->setTabEnabled(0,true);
	m_pIntellTerminalWidget->m_pIntellTerminalTab->setTabEnabled(1,true);

	if (m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_Stoped);
		m_pFT3OutParaWidget->SetGooseDisabled(bEnableState);
	}
	
	m_pIntellTerminalWidget->StopInit();
	

	if(m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->setDisabled(false);
	}
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget(false);//20220628 zhouhj 暂时改为不更新界面参数,防止界面参数被修改为0
	g_theTestCntrFrame->StopPowerWidget(false);
	g_theTestCntrFrame->UpdateRptHtml();
	m_pIntellTerminalWidget->m_pBinarySet_PushButton->setEnabled(true);
	connect(m_pSttIntelGoutToBinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));
	connect(m_pSttIntelBoutToGinParaWidget->getGoosePub(), SIGNAL(currentChanged ( int  )), this, SLOT(slot_Tab_cellClicked ( int )));

}
void QSttMacroParaEditViewIntelligentTerminal::startInit(BOOL bEnableState,int nGooseParasUI_State)
{
	m_nRowIndex=-1;
	slot_RevertData();//确保测试开始后改测试项的数据为初始化状态
	if (m_pIntellTerminalParas->m_nFuncType==0)
	{	
		m_nTestIndex=m_pSttIntelGoutToBinParaWidget->GetCurrentRow();
		m_pSttIntelGoutToBinParaWidget->startInit();
		m_pIntellTerminalWidget->m_pIntellTerminalTab->setTabEnabled(1,!bEnableState);
		m_pSttIntelGoutToBinParaWidget->SetRunState(nGooseParasUI_State);
		m_pSttIntelGoutToBinParaWidget->SetGooseDisabled(bEnableState);
	} 
	else
	{	
		m_nTestIndex=m_pSttIntelBoutToGinParaWidget->GetCurrentRow();
		m_pSttIntelBoutToGinParaWidget->startInit();
		m_pIntellTerminalWidget->m_pIntellTerminalTab->setTabEnabled(0,!bEnableState);	
		m_pSttIntelBoutToGinParaWidget->SetRunState(nGooseParasUI_State);
		m_pSttIntelBoutToGinParaWidget->SetGooseDisabled(bEnableState);
		
	}
}
void QSttMacroParaEditViewIntelligentTerminal::stopInit(BOOL bEnableState,int nGooseParasUI_State)
{
	if (m_pIntellTerminalParas->m_nFuncType==0)
	{
		m_nTestIndex=m_pSttIntelGoutToBinParaWidget->GetCurrentRow();
		m_pSttIntelGoutToBinParaWidget->SetGooseDisabled(bEnableState);
		m_pSttIntelGoutToBinParaWidget->SetRunState(nGooseParasUI_State);
		m_pSttIntelGoutToBinParaWidget->getGoosePub()->setCurrentIndex(m_nTestIndex);
		m_pSttIntelGoutToBinParaWidget->setGooseTabEnable(!bEnableState);
	}
	else
	{
		m_nTestIndex=m_pSttIntelBoutToGinParaWidget->GetCurrentRow();
		m_pSttIntelBoutToGinParaWidget->SetGooseDisabled(bEnableState);
		m_pSttIntelBoutToGinParaWidget->SetRunState(nGooseParasUI_State);
		m_pSttIntelBoutToGinParaWidget->getGoosePub()->setCurrentIndex(m_nTestIndex);
		m_pSttIntelBoutToGinParaWidget->setGooseTabEnable(!bEnableState);
	}
}

void QSttMacroParaEditViewIntelligentTerminal::slot_updateParas()
{
	if (g_theTestCntrFrame->IsTestStarted())  
	{
		SendUpdateParameter();
	}
	SetParaChanged();
}                        


void QSttMacroParaEditViewIntelligentTerminal::slot_TabPageChanged( int index )
{
	m_pIntellTerminalParas->m_nFuncType=index;

	if (index==0)
	{
		m_pIntellTerminalWidget->m_pBinarySet_PushButton->setVisible(true);
	}
	else
	{
		m_pIntellTerminalWidget->m_pBinarySet_PushButton->setVisible(false);
	}
}
void QSttMacroParaEditViewIntelligentTerminal::slot_Tab_cellClicked(int index)
{
	m_nTestIndex=index;
}

void QSttMacroParaEditViewIntelligentTerminal::slot_RevertData()
{
	m_oIntellTerminalTest.m_oManuResult.init();
	for(int j = 0; j < PARAS_RSLT_EXPR_LEN; j++)
	{
		if (m_pIntellTerminalParas->m_nFuncType==0)
		{
			m_nGooseOutType[m_nTestIndex][j] =0;
			m_fGooseOutTime[m_nTestIndex][j] = 0.f;
		}
		else
		{
			m_nGooseInType[m_nTestIndex][j] =0;
			m_fGooseInTime[m_nTestIndex][j] = 0.f;
		}
	}
}
//根据tab页面获取对应的Group值
CIecCfgGoutData* QSttMacroParaEditViewIntelligentTerminal::GetGoutData(int nindex)
{
	CIecCfgGoutData* pGoutData = NULL;
	CIecCfgGoutDatas *pGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
	POS pos = pGoutDatas->GetHeadPosition();
	CIecCfgGoutCh *pGoutCh = NULL;
	int nGroup=0;
	while(pos)
	{
		pGoutData = (CIecCfgGoutData*)pGoutDatas->GetNext(pos);	
		if(pGoutData->m_nUseFlag == 1)
		{
			if( nindex == nGroup)
			{
				return pGoutData;
			}
			nGroup++;
		}
	}
	return pGoutData;
}

CIecCfgGinData* QSttMacroParaEditViewIntelligentTerminal::GetGinData( int nindex )
{
	CIecCfgGinData* pGinData = NULL;
	CIecCfgGinDatas *pGinDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGinMngr(); 
	POS pos = pGinDatas->GetHeadPosition();
	CIecCfgGinCh *pGinCh = NULL;
	int nGroup=0;
	while(pos)
	{
		pGinData = (CIecCfgGinData*)pGinDatas->GetNext(pos);	
		if(pGinData->m_nUseFlag == 1)
		{
			if( nindex == nGroup)
			{
				return pGinData;
			}
			nGroup++;
		}
	}
	return pGinData;
}

//处理测试结果和信号
void QSttMacroParaEditViewIntelligentTerminal::UpGoutData(int nTestIndex,int nindex)
{
	CIecCfgGoutData* pGoutData=GetGoutData(nTestIndex);
	CIecCfgGoutChs *pGoutChs = (CIecCfgGoutChs*)pGoutData->m_pCfgChs;

	POS pos = pGoutChs->GetHeadPosition();
	int nGoutChindex=0;
	while(pos)
	{			
		CIecCfgGoutCh* pGoutCh = (CIecCfgGoutCh*)pGoutData->GetNext(pos);	
		if (nGoutChindex==nindex)//根据行号获取发布信号的代表值
		{
			m_nGooseOutType[m_nTestIndex][nindex]=GetGooseSignal(pGoutCh->m_strDefaultValue);
		}
		nGoutChindex++;
	}		
}

void QSttMacroParaEditViewIntelligentTerminal::UpGinData(int nTestIndex,int nindex )
{
	CIecCfgGinData* pGinData=GetGinData(nTestIndex);
	CIecCfgGinChs *pGinChs = (CIecCfgGinChs*)pGinData->m_pCfgChs;

	POS pos = pGinChs->GetHeadPosition();
	int nGinChindex=0;
	while(pos)
	{			
		CIecCfgGinCh* pGinCh = (CIecCfgGinCh*)pGinData->GetNext(pos);	
		if (nGinChindex==nindex)//根据行号获取接收信号的代表值
		{
			m_nGooseInType[m_nTestIndex][nindex]=GetGooseSignal(pGinCh->m_strDefaultValue);	
		}
		nGinChindex++;
	}	
}
int QSttMacroParaEditViewIntelligentTerminal::GetGooseSignal(CString strID)
{
	int nGooseSignal;
	if (strID == _T("TRUE"))
	{
		nGooseSignal=1;//数值1代表信号为"0->1"
	}
	else if (strID == _T("FALSE"))
	{
		nGooseSignal=2;//数值2代表信号为"1->0"
	}				
	else if (strID == _T("[00]"))
	{	
		nGooseSignal=3;//数值3代表信号为"11->00"
	}	
	else  if (strID == _T("[01]"))
	{
		nGooseSignal=4;//数值4代表信号为"10->01"
	}
	else  if (strID == _T("[10]"))
	{
		nGooseSignal=5;//数值5代表信号为"01->10"
	}
	else  if (strID == _T("[11]"))
	{
		nGooseSignal=6;//数值6代表信号为"00->11"
	}
	return nGooseSignal;
}

void QSttMacroParaEditViewIntelligentTerminal::slot_GoutRowIndex(int nRowIndex)
{
	m_nRowIndex=nRowIndex;
}
void QSttMacroParaEditViewIntelligentTerminal::slot_GinRowIndex(int nRowIndex,float fActTime)
{
	m_nRowIndex=nRowIndex;
	int num=m_pSttIntelGoutToBinParaWidget->getGoosePubList().size();
	m_fGooseInTime[m_nTestIndex][m_nRowIndex]=fActTime;
	UpGinData(num,m_nRowIndex);
}

void QSttMacroParaEditViewIntelligentTerminal::slot_UpdateEventMsgTime(CEventResult* pEventInfo)
{
	if(pEventInfo==NULL)
	{
		return;
	}
	char flag='A';
	int num =m_pSttIntelGoutToBinParaWidget->getGoosePubList().size();
	if(pEventInfo->m_strEventID==SYS_STATE_REPORT_OnSwichInChanged)
	{
		if (m_strEndBinIn.GetLength()>g_nBinCount)
		{
			m_strEndBinIn=_T("");
		}
		for (int i=0; i< g_nBinCount; i++)
		{
			m_strEndBinIn.AppendFormat("%d",pEventInfo->m_BinIn[i]);
			if (m_strInitBinIn[i]!=m_strEndBinIn[i])
			{
				if (m_pIntellTerminalParas->m_nFuncType==0)
				{
					if (m_nRowIndex==-1)//GOOSE发布未选择取反
					{
						return;
					}
					if(m_fGooseOutTime[m_nTestIndex][m_nRowIndex]==0)
					{
						m_pSttIntelGoutToBinParaWidget->setGooseResultVlaues();//删除上一次记录的测试结果ResultVlaues
					}
					m_fGooseOutTime[m_nTestIndex][m_nRowIndex]=pEventInfo->m_fActTime;//GOOSE发布的结果显示到表格中
					UpGoutData(m_nTestIndex,m_nRowIndex);
					m_pSttIntelGoutToBinParaWidget->getGoosePubList().at(m_nTestIndex)->GridCellResultVlaues(pEventInfo->m_fActTime,flag);
				}
				else
				{			
					m_pSttIntelBoutToGinParaWidget->getGoosePubList().at(m_nTestIndex)->GridCellResultVlaues(pEventInfo->m_fActTime,flag);
				}
			}	
			flag++;
			m_strInitBinIn.AppendFormat(_T("%d"),pEventInfo->m_BinIn[i]);//二次记录开入变量的动作值作为参照量	
			if (m_strInitBinIn.GetLength()>=g_nBinCount*2)
			{
				m_strInitBinIn=m_strInitBinIn.Right(g_nBinCount);
			}
		/*	if(m_fGooseOutTime[m_nTestIndex][m_nRowIndex]!=0)
			{*/
				//m_pSttIntelGoutToBinParaWidget->setGooseResultVlaues();//删除上一次记录的测试结果ResultVlaues
			//}
			
		}			
	}
	if (pEventInfo->m_strEventID==SYS_STATE_EVENT_OnTestStarted)
	{
		if (m_strInitBinIn.GetLength()>=g_nBinCount)
		{
			m_strInitBinIn=_T("");
		}
		for (int i=0; i< g_nBinCount; i++)
		{
			m_strInitBinIn.AppendFormat(_T("%d"),pEventInfo->m_BinIn[i]);
		}
	}
}
void QSttMacroParaEditViewIntelligentTerminal::ShowReport(CDvmValues *pValues)
{
	g_theTestCntrFrame->UpdateRptHtml();
}

CString QSttMacroParaEditViewIntelligentTerminal::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += STT_ORG_MACRO_IntelligentTest;
	strFile += _T(".");
	strFile += "Intxml";

	return strFile;
}

bool QSttMacroParaEditViewIntelligentTerminal::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
{
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != "Intxml")
	{
		return false;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return false;
	}

	return true;
}

void QSttMacroParaEditViewIntelligentTerminal::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}


void QSttMacroParaEditViewIntelligentTerminal::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas,CIecCfgGinDatas* pCfgGinDatas )
{
	if (m_pSttIntelGoutToBinParaWidget||m_pSttIntelBoutToGinParaWidget)
	{
		return;
	}

	m_pSttIntelGoutToBinParaWidget = new QSttIntelGoutToBinParaWidget(pCfgGoutDatas);
	m_pSttIntelBoutToGinParaWidget = new QSttIntelBoutToGinParaWidget(pCfgGinDatas);
	int nInsertPos = 2;
    CString strGoutTitle,strGinTitle;
	xlang_GetLangStrByFile(strGoutTitle,"Native_GooseOutSet");
	xlang_GetLangStrByFile(strGinTitle,"Native_GooseInSet");
	m_pIntellTerminalWidget->m_pIntellTerminalTab->insertTab(nInsertPos,m_pSttIntelGoutToBinParaWidget,strGoutTitle);
	m_pIntellTerminalWidget->m_pIntellTerminalTab->insertTab(nInsertPos+1,m_pSttIntelBoutToGinParaWidget,strGinTitle);
}

void QSttMacroParaEditViewIntelligentTerminal::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,TRUE);
	int nInsertPos = 3;
	
	CString strTitle;
	strTitle=_T("FT3发布");
	m_pIntellTerminalWidget->m_pIntellTerminalTab->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewIntelligentTerminal::RemoveGooseParaWidget()
{
	if(m_pSttIntelGoutToBinParaWidget == NULL||m_pSttIntelBoutToGinParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pIntellTerminalWidget->m_pIntellTerminalTab->indexOf(m_pSttIntelGoutToBinParaWidget);
	m_pIntellTerminalWidget->m_pIntellTerminalTab->removeTab(nIndex+1);
	m_pIntellTerminalWidget->m_pIntellTerminalTab->removeTab(nIndex);

	delete m_pSttIntelGoutToBinParaWidget;
	delete m_pSttIntelBoutToGinParaWidget;
	m_pSttIntelGoutToBinParaWidget = NULL;
	m_pSttIntelBoutToGinParaWidget=NULL;
}

void QSttMacroParaEditViewIntelligentTerminal::RemoveFT3OutParaWidget()
{
	if(m_pFT3OutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pIntellTerminalWidget->m_pIntellTerminalTab->indexOf(m_pFT3OutParaWidget);
	m_pIntellTerminalWidget->m_pIntellTerminalTab->removeTab(nIndex);

	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

bool QSttMacroParaEditViewIntelligentTerminal::ExistGooseParaWidget()
{
	int nIndex = m_pIntellTerminalWidget->m_pIntellTerminalTab->indexOf(m_pSttIntelGoutToBinParaWidget);
	return (nIndex>=0);
}

bool QSttMacroParaEditViewIntelligentTerminal::ExistFT3OutParaWidget()
{
	int nIndex = m_pIntellTerminalWidget->m_pIntellTerminalTab->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewIntelligentTerminal::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		m_pIntellTerminalWidget->m_pIntellTerminalTab->setTabEnabled(m_pIntellTerminalWidget->m_pIntellTerminalTab->indexOf(m_pSttIntelGoutToBinParaWidget),b);
	}
}

void QSttMacroParaEditViewIntelligentTerminal::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		m_pIntellTerminalWidget->m_pIntellTerminalTab->setTabEnabled(m_pIntellTerminalWidget->m_pIntellTerminalTab->indexOf(m_pFT3OutParaWidget),b);
	}
}

void QSttMacroParaEditViewIntelligentTerminal::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pIntellTerminalParas, &oRead);
		stt_xml_serialize(&m_oIntellTerminalTest, &oRead);
	}

    g_theTestCntrFrame->InitStateMonitor();
    g_theTestCntrFrame->ClearInfoWidget();

    UpdateManualParas();
}
void QSttMacroParaEditViewIntelligentTerminal::init()
{
	m_strInitBinIn= _T("");
	m_strEndBinIn= _T("");

	for(int i = 0; i < PARAS_RSLT_COUNT; i++)
	{
		for(int j = 0; j < PARAS_RSLT_EXPR_LEN; j++)
		{
			m_nGooseInType[i][j] =0;
			m_nGooseOutType[i][j] =0;
			m_fGooseInTime[i][j]= 0.f;
			m_fGooseOutTime[i][j] = 0.f;
		}
	}	 
}

void QSttMacroParaEditViewIntelligentTerminal::slot_BinarySetPushButton_clicked()
{
	float fTrigDelay=0;
	QSttManualBinBoutDlg oManualBinBoutDlg(m_pIntellTerminalParas->m_binIn,m_pIntellTerminalParas->m_binOut,
		&m_pIntellTerminalParas->m_nBinLogic,&m_pIntellTerminalParas->m_manuGradient.fTrigDelay,
		&m_pIntellTerminalParas->m_bAuto,this);// zhouhj 临时变量命名从sttManualBinBoutDlg改为oManualBinBoutDlg
	oManualBinBoutDlg.setWindowModality(Qt::WindowModal);//模态窗口
	//SyncSwitchParas(m_pIntellTerminalParas);

#ifdef _USE_SoftKeyBoard_
    QSoftKeyBoard::AttachObj(&oManualBinBoutDlg);
#endif
	oManualBinBoutDlg.exec();
#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif
}