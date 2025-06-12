#include "SttMacroParaEditViewPrimFreqState.h"
#include "../Module/XLangResource_Native.h"
#include "../Module/SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttGlobalDef.h"
#include "../Controls/SttCheckBox.h"

//2022-12-02 修改功能ID，导致所有的都要编译，效率低下，所以从头文件中去掉，在任何需要包含的地方进行包含
#include "../SttTestCntrCmdDefine.h" 
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../State/CommonValueDialogState.h"
#include "../State/StateBinarySetDlg.h"

QSttMacroParaEditViewPrimFreqState* g_pPrimFreqStateTest = NULL;

QSttMacroParaEditViewPrimFreqState::QSttMacroParaEditViewPrimFreqState(bool bHorizontal,QWidget *parent, Qt::WindowFlags flags)
	:QSttMacroParaEditViewState(bHorizontal,parent,flags)
{
	g_pPrimFreqStateTest = this;
	m_pPrimStateTest = 0;
	m_nCurStateIndex = 0;

	//纯模拟量
	if (!g_oSystemParas.m_nHasAnalog)
	{
		g_oSystemParas.m_nHasAnalog = 1;
		m_bSystemParasChanged = TRUE;
	}

	if(g_oSystemParas.m_nHasWeek)
	{
		g_oSystemParas.m_nHasWeek = 0;
		m_bSystemParasChanged = TRUE;
	}
	if (g_oSystemParas.m_nHasDigital)
	{
		g_oSystemParas.m_nHasDigital = 0;
		m_bSystemParasChanged = TRUE;
	}

	m_pDcLayout = NULL ;
	m_pGrpDcSignal = NULL;
	m_pLblDc1 = NULL;
	m_pLblDc2 = NULL;
	m_pEditDc1 = NULL;
	m_pEditDc2 = NULL;

	InitStateTest();
	m_pStateParas = (tmt_PrimFreqStateParas *)&m_pPrimStateTest->m_oStateParas;
}

QSttMacroParaEditViewPrimFreqState::~QSttMacroParaEditViewPrimFreqState()
{

}

void QSttMacroParaEditViewPrimFreqState::ResetStateSerialize()
{
	for (int i = 0; i < m_pStateParas->m_nStateNumbers; i++)
	{
		tmt_PrimFreqStateParas *pPara = (tmt_PrimFreqStateParas *)m_pStateParas;
		pPara->m_paraPrimFreqState[i].m_bSelected = 1;
	}

	SaveTestMngrFile("");

}

CSttTestResourceBase* QSttMacroParaEditViewPrimFreqState::CreateTestResource()
{
// 	if (m_pOriginalSttTestResource == NULL)
// 	{
// 		m_pOriginalSttTestResource = new CSttTestResource_Sync();
// 	}

// 	g_theTestCntrFrame->m_pSttTestResource = m_pOriginalSttTestResource;
// 	g_oSttTestResourceMngr.m_pTestResouce = m_pOriginalSttTestResource;
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	return g_theTestCntrFrame->GetSttTestResource();
}

void QSttMacroParaEditViewPrimFreqState::initUI_Paras(bool bSmvAbnormal)
{
	(void)bSmvAbnormal;

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin initUI_Paras -  >>");	}

	//m_strParaFileTitle = tr("状态序列模板文件");
	m_strParaFileTitle = g_sLangTxt_State_StateSequencefile ; //状态序列模板文件 lcq 3.14
	m_strParaFilePostfix = tr("project(*.pfsttxml)");
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("PrimFreqStateTest.pfsttxml");
	debug_time_long_log("ViewState initUI_Paras 1", true);

	initUI();
	initConnections();
	debug_time_long_log("ViewState initUI_Paras initUI", true);

	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();

	//	CreateTestResource();
	g_theTestCntrFrame->InitTestResource();
	g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);
	debug_time_long_log("ViewState initUI_Paras InitTestResource", true);

	initTestParas();
	debug_time_long_log("ViewState initUI_Paras initTestParas", true);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end initUI_Paras -  >>");	}

}

void QSttMacroParaEditViewPrimFreqState::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
/*
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	CString strTmpPath = _P_GetLibraryPath();
	strTmpPath.AppendFormat(_T("StateTestParas%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
		, tm.wHour, tm.wMinute, tm.wSecond);
	pParas->SaveXmlFile(strTmpPath,CDataMngrXmlRWKeys::g_pXmlKeys);*/
}

//#include "../SttTestCntrThread.h"

void QSttMacroParaEditViewPrimFreqState::SetDatas(CDataGroup *pDataset)
{
	if (m_pParaTab == NULL)
	{
		return;
	}

	if (pDataset != NULL)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin State::SetDatas-1");	}
		CSttDataGroupSerializeRead oRead(pDataset);

		tmt_PrimFreqStateParas *pParas = (tmt_PrimFreqStateParas *)m_pStateParas;

		stt_xml_serialize(pParas, &oRead);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end State::SetDatas-1");	}
	}

	//初始化按钮栏
	if (m_pBtnWidget)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin State::SetDatas-2");	}
		m_pBtnWidget->m_pnCurStateIndex = &m_nCurStateIndex; //状态指针关联
		m_pBtnWidget->setData(&m_pPrimStateTest->m_oStateParas,TRUE);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end State::SetDatas-2");	}
	}

	if (m_pTrigerWidget)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin State::SetDatas-3");	}
		m_pTrigerWidget->SetData(m_pStatePara);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end State::SetDatas-3");	}
	}


	m_pStatePara = &(m_pPrimStateTest->m_oStateParas.m_paraPrimFreqState[0]);
	
	tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)m_pStatePara;
	if(pPara)
	{
		m_pEditDc1->setText(QString::number(pPara->m_frCurrentDc[0],'f',4));
		m_pEditDc2->setText(QString::number(pPara->m_frCurrentDc[1],'f',4));
	}

	if (m_pParaTab->m_pUIParaWidget)
	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-4  UIParaWidget");	}
		disconnect(m_pParaTab->m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()));
		m_pParaTab->m_pUIParaWidget->setMacroType(MACROTYPE_State);
		m_pParaTab->m_pUIParaWidget->setPropertyOfParaSet(P_Common,g_theTestCntrFrame->GetSttTestResource(),m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
		m_pParaTab->m_pUIParaWidget->setMaxMinAndEDVal();
		connect(m_pParaTab->m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_UpdateVecterViews()),Qt::UniqueConnection);
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-4  UIParaWidget");	}
	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "benin State::SetDatas-6   InitVectorWidget");	}
	g_theTestCntrFrame->InitVectorWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "benin State::SetDatas-6   InitPowerWidget");	}
	g_theTestCntrFrame->InitPowerWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "end State::SetDatas-6   InitVectorWidget");	}

#ifndef SttTestCntrThread_H
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-7  InitStateMonitor");	}
	g_theTestCntrFrame->InitStateMonitor();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-7   InitStateMonitor");	}

	g_theTestCntrFrame->ClearInfoWidget();	
#else
	//不能使用这种模式，因为需要new widget，在线程中 new 会崩溃
	CSttMacroParaEditInterface *pMacroParaEditInterface = (CSttMacroParaEditInterface*)this;
	g_theSttTestCntrThread->PostThreadMessage(11, (unsigned long)pMacroParaEditInterface, (unsigned long)pMacroParaEditInterface);
#endif

	UpdateStateParas();
}

//2023-2-4  lijunqing 提高程序界面初始化打开的速度，将矢量图、状态图等的初始化放到线程
void QSttMacroParaEditViewPrimFreqState::InitSpyToolWidget()	
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-6   InitVectorWidget");	}
	g_theTestCntrFrame->InitVectorWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-6   InitPowerWidget");	}
	g_theTestCntrFrame->InitPowerWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-6   InitVectorWidget");	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** benin State::SetDatas-7  InitStateMonitor");	}
	g_theTestCntrFrame->InitStateMonitor();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end State::SetDatas-7   InitStateMonitor");	}

	g_theTestCntrFrame->ClearInfoWidget();	
}


void QSttMacroParaEditViewPrimFreqState::slot_UpdateVecterViews()
{
	g_theTestCntrFrame->UpdateVectorData();
	g_theTestCntrFrame->UpdatePowerData();
}

void QSttMacroParaEditViewPrimFreqState::slot_updateParas()
{
	if (m_pParaTab->m_pUIParaWidget)
	{
		((QBasicTestParaSet*)m_pParaTab->m_pUIParaWidget)->UpdateTables();
	}
	
	slot_UpdateVecterViews();
	m_bTmtParaChanged = TRUE;
}

void QSttMacroParaEditViewPrimFreqState::initUI_TabBase()
{
	CString strText;

	//strText = _T("开关量设置");
	//xlang_SetLangStrToWidget_Txt(m_pBinarySet, g_sLangTxt_State_SwitchSet,XLang_Ctrls_QPushButton);//开关量设置-LCQ
	AddPushButton(&m_pBinarySet,g_sLangTxt_Native_Switch,18);

	//strText = _T("通用参数");
	//xlang_SetLangStrToWidget_Txt(m_pCommonPara, g_sLangTxt_GeneralParameter, XLang_Ctrls_QPushButton);//通用参数-LCQ
	AddPushButton(&m_pCommonPara,g_sLangTxt_GeneralParameter,18);


	m_pGrpDcSignal = new QGroupBox(_T("直流信号源") );
	AddLabel(&m_pLblDc1, _T("Idc1 (mA)"), 18);
	AddLabel(&m_pLblDc2, _T("Idc2 (mA)"), 18);

	AddLineEdit(&m_pEditDc1, 18);
	AddLineEdit(&m_pEditDc2, 18);

}

void QSttMacroParaEditViewPrimFreqState::initUI_LayoutBase(bool bGradientSet)
{
	m_pMainLayout = new QVBoxLayout;

	QVBoxLayout *pVDownTab = new QVBoxLayout;
	pVDownTab->addWidget(m_pParaTab);
	QVBoxLayout *pVDown = new QVBoxLayout;
	QHBoxLayout* pVDownBottom = new QHBoxLayout;
	//pVDownBottom->addWidget(m_pFreLabel);
	//pVDownBottom->addWidget(m_pFreEdit);
	pVDownBottom->addSpacerItem(new QSpacerItem(600,20,QSizePolicy::Expanding));
	pVDownBottom->addWidget(m_pBinarySet);
	pVDownBottom->addWidget(m_pCommonPara);
	pVDownBottom->setSpacing(4);

	m_pGrpDcSignal = new QGroupBox;
	m_pDcLayout = new QHBoxLayout;
	m_pDcLayout->addWidget(m_pLblDc1);
	m_pDcLayout->addWidget(m_pEditDc1);
	m_pDcLayout->addWidget(m_pLblDc2);
	m_pDcLayout->addWidget(m_pEditDc2);
	m_pGrpDcSignal->setLayout(m_pDcLayout);

	pVDown->addLayout(pVDownBottom);
	m_pMainLayout->addWidget(m_pBtnWidget );
	m_pMainLayout->addLayout(pVDownTab);
	m_pMainLayout->addWidget(m_pGrpDcSignal);
	m_pMainLayout->addWidget(m_pTrigerWidget);
	m_pMainLayout->addLayout(pVDown);	

	setLayout(m_pMainLayout);
}


void QSttMacroParaEditViewPrimFreqState::initUI()
{
	//创建各部件
	//QFont font;
	m_pParaTab = new QStateParaTab(&m_bTmtParaChanged,this, true);
	CString strText;

	m_pParaTab->m_tabWidget->setCurrentIndex(0);

	m_pBtnWidget = new QStateButtonWidget(true,this, true);
    m_pTrigerWidget = new QStateTrigerWidget(&m_bTmtParaChanged,this);
	m_pBtnWidget->m_pnCurStateIndex = &m_nCurStateIndex; //状态指针关联

	initUI_TabBase();

	initUI_LayoutBase(true);
	SetStateFont();
	m_pBtnWidget->EnableButtons();

	setFocusPolicy(Qt::StrongFocus);
}

void QSttMacroParaEditViewPrimFreqState::SetStateFont()
{
	m_pBinarySet->setFont(*g_pSttGlobalFont);
	m_pCommonPara->setFont(*g_pSttGlobalFont);
	m_pGrpDcSignal->setFont(*g_pSttGlobalFont);
	m_pLblDc1->setFont(*g_pSttGlobalFont);
	m_pLblDc2->setFont(*g_pSttGlobalFont);
	m_pEditDc1->setFont(*g_pSttGlobalFont);
	m_pEditDc2->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewPrimFreqState::initConnection_Base()
{
	connect(m_pBtnWidget->m_pPreviosState,SIGNAL(clicked()),this,SLOT(slot_PreviosState()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pNextState,SIGNAL(clicked()),this,SLOT(slot_NextState()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pInsertStateBF,SIGNAL(clicked()),this,SLOT(slot_InsertStateBF()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pInsertStateAF,SIGNAL(clicked()),this,SLOT(slot_InsertStateAF()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pDeleteState,SIGNAL(clicked()),this,SLOT(slot_DeleteState()),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)),Qt::UniqueConnection);
	connect(m_pParaTab->m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
// 	connect(m_pBtnWidget->m_pBtnEditState, SIGNAL(clicked()), this, SLOT(slot_EditState()));

    connect(m_pBinarySet,SIGNAL(clicked()),this,SLOT(slot_BinarySet()),Qt::UniqueConnection);
	connect(m_pCommonPara,SIGNAL(clicked()),this,SLOT(slot_CommonPara()),Qt::UniqueConnection);

//  	connect(g_theTestCntrFrame, SIGNAL(sig_UpdateAuxDCEdit()), this, SLOT(slot_UpdateAuxDcEnabled()));

//#ifdef _PSX_QT_LINUX_
//	connect(m_pFreEdit, SIGNAL(clicked()), this, SLOT(slot_lne_FreChanged()));
//#endif
}

void QSttMacroParaEditViewPrimFreqState::initConnections()
{
	connect(m_pEditDc1, SIGNAL(editingFinished()), this, SLOT(slot_edt_Dc1()));
	connect(m_pEditDc2, SIGNAL(editingFinished()), this, SLOT(slot_edt_Dc2()));

	initConnection_Base();
}

// void QSttMacroParaEditViewPrimFreqState::slot_UpdateAuxDcEnabled()
// {
// 	if (m_pTrigerWidget == NULL)
// 	{
// 		return;
// 	}
// 
// 	m_pTrigerWidget->UpdateAuxDcEnabled();
// 
// }

void QSttMacroParaEditViewPrimFreqState::InitGoosePubDataGroups()
{

}

void QSttMacroParaEditViewPrimFreqState::InitFT3PubDataGroups()
{

}
void QSttMacroParaEditViewPrimFreqState::UpdateTestResource(BOOL bCreateChMaps)
{
// 	ASSERT(g_theTestCntrFrame->m_pSttTestResource);
// 	g_theTestCntrFrame->OnUpdateTestResource(bCreateChMaps);

	if (m_pParaTab->m_pUIParaWidget)
	{
		m_pParaTab->m_pUIParaWidget->initUI(g_theTestCntrFrame->GetSttTestResource());
		m_pParaTab->m_pUIParaWidget->initData(true);
		m_pParaTab->m_pUIParaWidget->setMaxMinAndEDVal();
	}
	
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();

	CString strModel;
	strModel = g_oSttSystemConfig.GetDevModel();
	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	if (!pCurDevice->m_strModel.IsEmpty())
	{
		strModel = pCurDevice->m_strModel;
	}
	

}

void QSttMacroParaEditViewPrimFreqState::UpdatePrimParaSetUI()
{
}

void QSttMacroParaEditViewPrimFreqState::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
													long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	tmt_prim_freq_state_test *pTmtStateTest = (tmt_prim_freq_state_test *)pParas;
	stt_xml_serialize_ex2(&pTmtStateTest->m_oStateParas, pMacroParas,nVolRsNum,nCurRsNum,FALSE);
}

CString QSttMacroParaEditViewPrimFreqState::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();

	strFile += STT_MACRO_ID_PrimFreqStateTest;

	strFile += _T(".");
	strFile += POSTFIX_PRIMFREQSTATETEST;

	return strFile;
}

bool QSttMacroParaEditViewPrimFreqState::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
{
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != POSTFIX_PRIMFREQSTATETEST)
	{
		return false;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return false;
	}

	return true;
}

//2024-9-11 lijunqing 优化
void QSttMacroParaEditViewPrimFreqState::InitStateTest()
{
	if (m_pPrimStateTest == NULL)
	{
#ifdef TMT_STATECOUNT_USE_DEF
		m_pPrimStateTest = (tmt_prim_freq_state_test*)malloc(sizeof(tmt_prim_freq_state_test));
		m_pPrimStateTest->init(0);
#else
		m_pPrimStateTest = new tmt_prim_freq_state_test;
#endif
	}
}

void QSttMacroParaEditViewPrimFreqState::initTestParas()
{
	BOOL bRet = OpenTestTestMngrFile(_T(""));
	debug_time_long_log("ViewState initUI_Paras initTestParas OpenTestTestMngrFile", true);

	if (!bRet)
	{
		m_pStateParas->init(2);
		debug_time_long_log("ViewState initUI_Paras initTestParas InitState", true);
	}

	CopyBinaryConfig();
	g_theTestCntrFrame->UpdateToolButtons();
	SetDatas(NULL);

	debug_time_long_log("ViewState initUI_Paras initTestParas SetDatas", true);

	m_pBtnWidget->EnableButtons();
}

void QSttMacroParaEditViewPrimFreqState::InitUI_OpenParas()
{
	if (m_pParaTab == NULL)
	{
		return;
	}

	//初始化按钮栏
	tmt_PrimFreqStateParas *pParas = (tmt_PrimFreqStateParas *)m_pStateParas;
	if (m_pBtnWidget)
	{
		m_pBtnWidget->setData(pParas);
	}
	if (m_pTrigerWidget)
	{
		tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)m_pStatePara;
		m_pTrigerWidget->SetData(m_pStatePara);
	}

	m_pStatePara = &(pParas->m_paraPrimFreqState[0]);
	if (m_pParaTab->m_pUIParaWidget)
	{
		m_pParaTab->m_pUIParaWidget->setMacroType(MACROTYPE_State);
		m_pParaTab->m_pUIParaWidget->setPropertyOfParaSet(P_Common,g_theTestCntrFrame->GetSttTestResource(),m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
		m_pParaTab->m_pUIParaWidget->setMaxMinAndEDVal();
	}

	UpdateStateParas();
}

void QSttMacroParaEditViewPrimFreqState::UpdateStateParas_Base()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	if (m_pParaTab->m_pUIParaWidget)
	{
		m_pParaTab->m_pUIParaWidget->setData(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR);
		m_pParaTab->m_pUIParaWidget->initData(true);
	}

}

void QSttMacroParaEditViewPrimFreqState::UpdateStateParas()
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateStateParas");	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateStateParas_Base");	}
	UpdateStateParas_Base();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateStateParas_Base");	}

	tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)m_pStatePara;
      m_pTrigerWidget->SetData(m_pStatePara);

// 	  if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateGoutTab");	}
// 	UpdateGoutTab();
// 	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateGoutTab");	}
// 
// 	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateFT3Tab");	}
// 	UpdateFT3Tab();
// 	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateFT3Tab");	}


	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> benin UpdateVectorObject");	}
	UpdateVectorObject();
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateVectorObject");	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end UpdateStateParas");	}
}

void QSttMacroParaEditViewPrimFreqState::CopyBinaryConfig(BOOL b)
{
	tmt_PrimFreqStateParas *pParas = (tmt_PrimFreqStateParas *)m_pStateParas;
	tmt_PrimFreqStatePara* pStatePara = (tmt_PrimFreqStatePara *)&pParas->m_paraPrimFreqState[m_nCurStateIndex];
	
	if(!pStatePara)
	{
		return;
	}

	if(b)
	{
		g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic = pStatePara->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect = pStatePara->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binOut[i].nState = pStatePara->m_binOut[i].nState;
		}
	}
	else
	{
		pStatePara->m_nBinLogic = g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			pStatePara->m_binIn[i].nSelect = g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			pStatePara->m_binOut[i].nState = g_theTestCntrFrame->GetBinaryConfig()->m_binOut[i].nState;
		}
	}
}

void QSttMacroParaEditViewPrimFreqState::UpdateBinBoutExTab()
{

}

void QSttMacroParaEditViewPrimFreqState::UpdateGoutTab(BOOL bUpdateList)
{

}
void QSttMacroParaEditViewPrimFreqState::UpdateFT3Tab(BOOL bUpdateList)
{

}
void QSttMacroParaEditViewPrimFreqState::UpdateFT3Tab_UI(CIecCfgDatasSMV *pIecCfgDatasSMV)
{
}

void QSttMacroParaEditViewPrimFreqState::ClearResult(PTMT_PARAS_HEAD pHead)
{
	((tmt_StateTest*)pHead)->m_oStateResults.init(g_nStateCount);	
}

void QSttMacroParaEditViewPrimFreqState::EnableButtons()
{

	if(m_nCurStateIndex < 0 || m_nCurStateIndex >= m_pStateParas->m_nStateNumbers)
	{
		m_pBtnWidget->m_pDeleteState->setDisabled(true);
	}
	else
	{
		m_pBtnWidget->m_pDeleteState->setDisabled(false);
	}
}

void QSttMacroParaEditViewPrimFreqState::UpdateActValue(CEventResult *pEventInfo)
{
	m_aStrActValue.clear();
	int nCurrStateIndex = pEventInfo->m_nCurrStateIndex;
	GetActValue(pEventInfo->m_nCurrStepIndex, nCurrStateIndex);
	CString strStateActMsg;
	for (size_t i = 0; i < m_aStrActValue.size(); i++)
	{
		if (i > 0)
		{
			strStateActMsg += " ";
		}
		strStateActMsg += m_aStrActValue[i];
	}

	if (!strStateActMsg.IsEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,strStateActMsg);
	}
}

void QSttMacroParaEditViewPrimFreqState::GetActValue( int nCurStepIndex, int nIndex)
{
	tmt_PrimFreqStateParas *pParas = (tmt_PrimFreqStateParas *)m_pStateParas;
 	tmt_PrimFreqStatePara* pStatePara = &pParas->m_paraPrimFreqState[nIndex];
	tmt_channel* pChVData = pStatePara->m_uiVOL;
	tmt_channel* pChCData = pStatePara->m_uiCUR;
	CExBaseList* pListChVData =&g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef;
	CExBaseList *pListChCData = &g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef;
	long nChIndex = 0;
	int nGradientType = GRADIENT_TYPE_None;

	POS pos = pListChVData->GetHeadPosition();
	CExBaseObject *pCh = NULL;
	CString strChName;
	float nActValue = 0.00f;
	CString strMsgDesc;
	while(pos)
	{
		pCh = pListChVData->GetNext(pos);
		strChName = pCh->m_strName;
		if (nGradientType == GRADIENT_TYPE_Linear )
		{
			if(pChVData[nChIndex].Ramp[0].nIndex == 1)
			{
				if (pChVData[nChIndex].Harm[1].fAmp > pChVData[nChIndex].Ramp[0].fEnd)
				{
					nActValue = pChVData[nChIndex].Harm[1].fAmp - nCurStepIndex*(pChVData[nChIndex].Ramp[0].fStep);
					if (nActValue < pChVData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();

					if (IsUseSecondParaSet())
					{
					strMsgDesc.AppendFormat(_T("(%.3f V)."),nActValue);
					}
					else
					{
						strMsgDesc.AppendFormat(_T("(%.3f kV)."),nActValue);
					}
					
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue = pChVData[nChIndex].Harm[1].fAmp + nCurStepIndex*(pChVData[nChIndex].Ramp[0].fStep);
					if (nActValue > pChVData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					if (IsUseSecondParaSet())
					{
					strMsgDesc.AppendFormat(_T("(%.3f V)."),nActValue);
					}
					else
					{
						strMsgDesc.AppendFormat(_T("(%.3f kV)."),nActValue);
					}
					
					m_aStrActValue.append(strMsgDesc);
				}
			}

			if(pChVData[nChIndex].Ramp[2].nIndex == 1)
			{
				if (pChVData[nChIndex].Harm[1].fFreq > pChVData[nChIndex].Ramp[2].fEnd)
				{
					nActValue = pChVData[nChIndex].Harm[1].fFreq - nCurStepIndex*(pChVData[nChIndex].Ramp[2].fStep);
					if (nActValue < pChVData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue =  pChVData[nChIndex].Harm[1].fFreq+nCurStepIndex*(pChVData[nChIndex].Ramp[2].fStep);

					if (nActValue > pChVData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}
		}
		else if (nGradientType == GRADIENT_TYPE_Step)
		{
			if(pChVData[nChIndex].Ramp[0].nIndex == 1)
			{
				if (pChVData[nChIndex].Harm[1].fAmp > pChVData[nChIndex].Ramp[0].fEnd)
				{
					nActValue = pChVData[nChIndex].Harm[1].fAmp -nCurStepIndex*(pChVData[nChIndex].Ramp[0].fStep);
					if (nActValue <pChVData[nChIndex].Ramp[0].fEnd )
					{
						nActValue = pChVData[nChIndex].Ramp[0].fEnd; 
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					if (IsUseSecondParaSet())
					{
					strMsgDesc.AppendFormat(_T("(%.3f V)."),nActValue);
					}
					else
					{
						strMsgDesc.AppendFormat(_T("(%.3f kV)."),nActValue);

					}
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue = pChVData[nChIndex].Harm[1].fAmp + nCurStepIndex*(pChVData[nChIndex].Ramp[0].fStep);
					if (nActValue > pChVData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					if (IsUseSecondParaSet())
					{
					strMsgDesc.AppendFormat(_T("(%.3f V)."),nActValue);

					}
					else
					{
						strMsgDesc.AppendFormat(_T("(%.3f kV)."),nActValue);

					}
					m_aStrActValue.append(strMsgDesc);
				}
			}

			if(pChVData[nChIndex].Ramp[2].nIndex == 1)
			{
				if (pChVData[nChIndex].Harm[1].fFreq > pChVData[nChIndex].Ramp[2].fEnd)
				{
					nActValue = pChVData[nChIndex].Harm[1].fFreq - nCurStepIndex*(pChVData[nChIndex].Ramp[2].fStep);
					if ( pChVData[nChIndex].Ramp[2].fEnd > nActValue)
					{
						nActValue = pChVData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue =  pChVData[nChIndex].Harm[1].fFreq+nCurStepIndex*(pChVData[nChIndex].Ramp[2].fStep);
					if (nActValue > pChVData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChVData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}
		}
		nChIndex++;
	}


	POS pos2 = pListChCData->GetHeadPosition();
	nChIndex = 0;
	while(pos2)
	{
		pCh = pListChCData->GetNext(pos2);
		strChName = pCh->m_strName;
		if (nGradientType == GRADIENT_TYPE_Linear)
		{
			if(pChCData[nChIndex].Ramp[0].nIndex == 1)
			{
				if (pChCData[nChIndex].Harm[1].fAmp > pChCData[nChIndex].Ramp[0].fEnd)
				{
					nActValue = pChCData[nChIndex].Harm[1].fAmp - nCurStepIndex*(pChCData[nChIndex].Ramp[0].fStep);
					if (nActValue < pChCData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f A)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue = pChCData[nChIndex].Harm[1].fAmp + nCurStepIndex*(pChCData[nChIndex].Ramp[0].fStep);
					if (nActValue > pChCData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f A)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}

			if (pChCData[nChIndex].Ramp[2].nIndex == 1)
			{
				if (pChCData[nChIndex].Harm[1].fFreq > pChCData[nChIndex].Ramp[2].fEnd)
				{
					nActValue = pChCData[nChIndex].Harm[1].fFreq - nCurStepIndex*(pChCData[nChIndex].Ramp[2].fStep);
					if (nActValue < pChCData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue =  pChCData[nChIndex].Harm[1].fFreq+nCurStepIndex*(pChCData[nChIndex].Ramp[2].fStep);
					if (nActValue > pChCData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}
		}
		else if (nGradientType == GRADIENT_TYPE_Step)
		{
			if(pChCData[nChIndex].Ramp[0].nIndex == 1)
			{
				if (pChCData[nChIndex].Harm[1].fAmp > pChCData[nChIndex].Ramp[0].fEnd)
				{
					nActValue = pChCData[nChIndex].Harm[1].fAmp - nCurStepIndex*(pChCData[nChIndex].Ramp[0].fStep);
					if (nActValue < pChCData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f A)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue = pChCData[nChIndex].Harm[1].fAmp + nCurStepIndex*(pChCData[nChIndex].Ramp[0].fStep);
					if (nActValue > pChCData[nChIndex].Ramp[0].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[0].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f A)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}

			if(pChCData[nChIndex].Ramp[2].nIndex == 1)
			{
				if (pChCData[nChIndex].Harm[1].fFreq > pChCData[nChIndex].Ramp[2].fEnd)
				{
					nActValue = pChCData[nChIndex].Harm[1].fFreq - nCurStepIndex*(pChCData[nChIndex].Ramp[2].fStep);
					if (nActValue < pChCData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f  HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
				else
				{
					nActValue =  pChCData[nChIndex].Harm[1].fFreq+nCurStepIndex*(pChCData[nChIndex].Ramp[2].fStep);
					if (nActValue > pChCData[nChIndex].Ramp[2].fEnd)
					{
						nActValue = pChCData[nChIndex].Ramp[2].fEnd;
					}

					strMsgDesc = strChName;
					strMsgDesc += /*_T("动作值")*/g_sLangTxt_State_ActionValue.GetString();
					strMsgDesc.AppendFormat(_T("(%.3f HZ)."),nActValue);
					m_aStrActValue.append(strMsgDesc);
				}
			}
		}
		nChIndex++;
	}

}

void QSttMacroParaEditViewPrimFreqState::UpdateVectorObject()
{
	ASSERT(m_pStatePara != NULL);
	CSttMacroChannels *pMacroChs = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
	g_theTestCntrFrame->UpdateVectorWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR, &pMacroChs->m_oVolChListRef, &pMacroChs->m_oCurChListRef);
	g_theTestCntrFrame->UpdatePowerWidget(m_pStatePara->m_uiVOL,m_pStatePara->m_uiCUR, &pMacroChs->m_oVolChListRef, &pMacroChs->m_oCurChListRef);
	
}

void QSttMacroParaEditViewPrimFreqState::slot_PreviosState()//切换上一状态
{

	long  nCurrStateIndex = m_pBtnWidget->m_pStatesComBox->currentIndex();

	if (nCurrStateIndex >0)
	{
		nCurrStateIndex--;
		m_pBtnWidget->m_pStatesComBox->setCurrentIndex(nCurrStateIndex);
	}	
	
	m_pBtnWidget->EnableButtons();
}

void QSttMacroParaEditViewPrimFreqState::slot_NextState()//切换下一状态
{
	long  nCurrStateIndex = m_pBtnWidget->m_pStatesComBox->currentIndex();
	long  nMaxState = m_pBtnWidget->m_pStatesComBox->count();

	if (nCurrStateIndex + 1 < nMaxState)
	{
		nCurrStateIndex++;
		m_pBtnWidget->m_pStatesComBox->setCurrentIndex(nCurrStateIndex);
	}
	
	m_pBtnWidget->EnableButtons();
}

void QSttMacroParaEditViewPrimFreqState::slot_InsertStateBF()
{
	if (m_pCopyStatePara == NULL)
	{
		m_pCopyStatePara = new tmt_PrimFreqStatePara;
	}
	if(m_pStatePara == NULL)
	{
		return;
	}

	tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)m_pStatePara;
	memcpy(m_pCopyStatePara,pPara,sizeof(tmt_PrimFreqStatePara));

	if(m_pBtnWidget->m_pStatesComBox->count() == g_nStateCount)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("状态数目不能超过%d"), g_nStateCount);
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_State_NumnotExceed.GetString(), g_nStateCount);
		return;
	}	
	
// 	stt_state_paras_insert_before(&m_oStateTest->m_oStateParas, NULL, m_nCurStateIndex);
// 	InsertGoutDatas(GetGoutDatas(m_nCurStateIndex),m_nCurStateIndex);
	tmt_PrimFreqStateParas *pParas = (tmt_PrimFreqStateParas *)&m_pPrimStateTest->m_oStateParas;
	tmt_PrimFreqStatePara *pCopyParas = (tmt_PrimFreqStatePara *)m_pCopyStatePara;

	stt_prim_freq_state_paras_insert_before(/*&m_oStateTest->m_oStateParas*/pParas, pCopyParas, m_nCurStateIndex);

	disconnect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));
	m_pBtnWidget->UpdateStateCombox(TRUE);
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));

	slot_StatesIndexChanged(m_nCurStateIndex);

	g_pPrimFreqStateTest->m_bTmtParaChanged = TRUE;
	//EnableButtons();
}

void QSttMacroParaEditViewPrimFreqState::CopyDatasSMV()
{

}

void QSttMacroParaEditViewPrimFreqState::slot_InsertStateAF()
{
	if (m_pCopyStatePara == NULL)
	{
		m_pCopyStatePara = new tmt_PrimFreqStatePara;
	}
	if(m_pStatePara == NULL)
	{
		return;
	}
	
	tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)m_pStatePara;
	memcpy(m_pCopyStatePara,pPara,sizeof(tmt_PrimFreqStatePara));

	if(m_pBtnWidget->m_pStatesComBox->count() == g_nStateCount)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("状态数目不能超过%d"), g_nStateCount);
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_State_NumnotExceed.GetString(), g_nStateCount);//lcq 3.14
		return;
	}	
	
	tmt_PrimFreqStateParas *pParas = (tmt_PrimFreqStateParas *)&m_pPrimStateTest->m_oStateParas;
	tmt_PrimFreqStatePara *pCopyParas = (tmt_PrimFreqStatePara *)m_pCopyStatePara;

 	stt_prim_freq_state_paras_insert_after(pParas, pCopyParas, m_nCurStateIndex);

	m_nCurStateIndex++;
	//m_pBtnWidget->m_nCurStateIndex = m_nCurStateIndex;

	disconnect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));
	m_pBtnWidget->UpdateStateCombox(true);
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));

	slot_StatesIndexChanged(m_nCurStateIndex);

	g_pPrimFreqStateTest->m_bTmtParaChanged = TRUE;
	EnableButtons();
}
	
void QSttMacroParaEditViewPrimFreqState::slot_DeleteState()
{
	if(m_pStateParas->m_nStateNumbers <= 1)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("至少保留一个状态."));
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_Gradient_MaintainatLeastOneState.GetString()); //至少保留一个状态 lcq 3.14
		return;	//必须至少一个状态
	}
	tmt_PrimFreqStateParas *pParas = (tmt_PrimFreqStateParas *)&m_pPrimStateTest->m_oStateParas;

	stt_prim_freq_state_paras_delete(/*&m_oStateTest->m_oStateParas*/pParas,m_nCurStateIndex);

	m_nCurStateIndex--;

	if(m_nCurStateIndex < 0)
	{
		m_nCurStateIndex = 0;
	}
	//m_pBtnWidget->m_nCurStateIndex = m_nCurStateIndex;

	disconnect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));
	m_pBtnWidget->UpdateStateCombox(TRUE);
	connect(m_pBtnWidget->m_pStatesComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_StatesIndexChanged(int)));

	slot_StatesIndexChanged(m_nCurStateIndex);

	g_pPrimFreqStateTest->m_bTmtParaChanged = TRUE;
	EnableButtons();
}
	
void QSttMacroParaEditViewPrimFreqState::slot_StatesIndexChanged(int nIndex)
{
	if (! m_pBtnWidget->m_bEnable_slot_StatesIndexChanged)
	{
		return;
	}

	if(m_pBtnWidget->m_pStatesComBox->IsScrolling())
	{
		return;
	}

	tmt_PrimFreqStateParas *pParas = (tmt_PrimFreqStateParas *)m_pStateParas;

	if (nIndex < 0 || nIndex >= pParas->m_nStateNumbers)
	{
		return;
	}

	m_nCurStateIndex = nIndex;
	//m_pBtnWidget->m_nCurStateIndex = nIndex;
	m_pStatePara = &pParas->m_paraPrimFreqState[m_nCurStateIndex];
	m_pBtnWidget->EnableButtons();

	tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)m_pStatePara;
	if(pPara)
	{
		m_pEditDc1->setText(QString::number(pPara->m_frCurrentDc[0],'f',4));
		m_pEditDc2->setText(QString::number(pPara->m_frCurrentDc[1],'f',4));
	}

	
	UpdateStateParas();
}

void QSttMacroParaEditViewPrimFreqState::slot_BinarySet()
{
	QStateBinarySetDlg dlg(this);

	tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)m_pStatePara;
	dlg.setData(pPara);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}
void QSttMacroParaEditViewPrimFreqState::slot_CommonPara()
{
	tmt_PrimFreqStateParas *pParas = (tmt_PrimFreqStateParas *)&m_pPrimStateTest->m_oStateParas;
	CommonValueDialogState dlg(pParas, this, true);
	dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif

	if (dlg.m_nIsOK==1)
	{
		g_pPrimFreqStateTest->m_bTmtParaChanged = TRUE;
	}
}

void QSttMacroParaEditViewPrimFreqState::slot_edt_Dc1()
{
	float fv = m_pEditDc1->text().toFloat();
	if( fv < 4.0f || fv > 12.0f)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("两路直流信号源输出支持4～12mA,请重新输入！"));
	}
	fv = setLimit(4.0f, 12.0f, fv);

	tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)m_pStatePara;
	pPara->m_frCurrentDc[0] = fv;
	m_pEditDc1->setText(QString::number(fv,'f',4));

}

void QSttMacroParaEditViewPrimFreqState::slot_edt_Dc2()
{
	float fv = m_pEditDc2->text().toFloat();
	if( fv < 4.0f || fv > 12.0f)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("两路直流信号源输出支持4～12mA,请重新输入！"));
	}
	fv = setLimit(4.0f, 12.0f, fv);

	tmt_PrimFreqStatePara *pPara = (tmt_PrimFreqStatePara *)m_pStatePara;
	pPara->m_frCurrentDc[0] = fv;
	m_pEditDc2->setText(QString::number(fv,'f',4));
}

void QSttMacroParaEditViewPrimFreqState::slot_currentChangedTabWidget(int nCurrIndex)
{
	if (m_pStatePara == NULL)
	{
		return;
	}

}

void QSttMacroParaEditViewPrimFreqState::slot_SwitchStateChanged()
{
	if(g_theTestCntrFrame->IsTestStarted())
	{
		g_theTestCntrFrame->UpdateToolButtons();
	}
}

void QSttMacroParaEditViewPrimFreqState::OnViewTestLink(BOOL b)
{
	if(!b)
	{
		OnViewTestStop();
	}
}

void QSttMacroParaEditViewPrimFreqState::OnViewTestStart()
{
	//20250213 suyang 状态图偶发刷新不对，分析可能是清除慢，将底层上送的数据清除了，故移到此处；（最好放在base点击开始的槽函数，待讨论）
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	g_theTestCntrFrame->ClearInfoWidget();

//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[问题查找]OnViewTestStart_StateTest."));
	//切换到状态1, 并初始化循环计数器
	m_nCircle = 0;
	m_pBtnWidget->m_pStatesComBox->setCurrentIndex(0);

	//m_pFreEdit->setDisabled(true);
    m_pBinarySet->setDisabled(true);
	m_pCommonPara->setDisabled(true);

	m_pBtnWidget->startInit();
	m_pBtnWidget->EnableButtons(); //2023-1-13

	m_pTrigerWidget->startInit();//2023-1-12

	InitManuTrigerButton();

	m_pParaTab->startInit();

	if(m_pParaTab->m_pGooseParaWidget)
	{
		m_pParaTab->m_pGooseParaWidget->setDisabled(true);
	}

	if(m_pParaTab->m_pFT3OutParaWidget)
	{
		m_pParaTab->m_pFT3OutParaWidget->setDisabled(true);
	}
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();

	m_mapState.clear();
	CString strStateName;

	tmt_PrimFreqStateParas *pPara = (tmt_PrimFreqStateParas *)m_pStateParas;

	for(int i = 0; i < pPara->m_nStateNumbers; i++)
	{
		if(pPara->m_paraPrimFreqState[i].m_bSelected)
		{
			strStateName = pPara->m_paraPrimFreqState[i].m_strName;

			if (strStateName.IsEmpty())
			{
				strStateName = g_sLangTxt_State;
				strStateName.AppendFormat(_T("%ld"),i+1);
			}
			m_mapState.insert(m_mapState.size(),strStateName );
		}
	}
}

void QSttMacroParaEditViewPrimFreqState::OnViewTestStop()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[问题查找]OnViewTestStop_StateTest."));
	m_pTrigerWidget->stopInit();//2023-1-12
	m_pBinarySet->setDisabled(false);
	//m_pSettingValue->setVisible(false);
	m_pCommonPara->setDisabled(false);

	m_pBtnWidget->stopInit(m_pCopyStatePara != NULL);

	m_pParaTab->stopInit();

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
	setDcoffsetEnable();
}

void QSttMacroParaEditViewPrimFreqState::InitManuTrigerButton()
{
	tmt_PrimFreqStateParas *pPara = (tmt_PrimFreqStateParas *)m_pStateParas;
	if (pPara->m_paraPrimFreqState[0].m_nTriggerCondition == TMT_MDSTATE_MEARSURETRIGGER)
	{
		g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,true);
	}
	else
	{
		g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false);
	}
}

void QSttMacroParaEditViewPrimFreqState::SysStateReport_OnStateChanged(CEventResult *pEventInfo)
{	
//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[问题查找]SysStateReport_OnStateChanged(%ld)."),pEventInfo->m_nCurrStateIndex);
	ASSERT(pEventInfo != NULL);
	if (pEventInfo->m_nCurrStateIndex>=0)
	{
		if(pEventInfo->m_nCurrStateIndex == 0)
		{
			m_nCircle++;
		}

		CString strStateMsg, strLoopNum, strInState, strStateNum;
		//strStateMsg.Format(_T("当前循环%d, 进入状态%ld."), m_nCircle, pEventInfo->m_nCurrStateIndex+1);

		//strStateMsg = _T("当前循环");
		strStateMsg = g_sLangTxt_State_TheCurrentLoop; //当前循环 lcq 3.14
		strLoopNum.Format("%d", m_nCircle);
#ifndef _PSX_QT_LINUX_
		//strInState = _T("进入");
		strInState = g_sLangTxt_State_Enter; //进入 lcq 3.14
		strInState += m_mapState[pEventInfo->m_nCurrStateIndex];
#else
		strInState = /*_T("进入状态")*/g_sLangTxt_State_InState;
		strStateNum.Format("%ld", pEventInfo->m_nCurrStateIndex+1);
#endif
		strStateMsg = strStateMsg + strLoopNum + strInState + strStateNum;
		CLogPrint::LogString(XLOGLEVEL_RESULT,strStateMsg);
		m_pBtnWidget->m_pStatesComBox->setCurrentIndex(pEventInfo->m_nCurrStateIndex);

		tmt_PrimFreqStateParas* pParas = (tmt_PrimFreqStateParas*)m_pStateParas;
		tmt_StatePara* pStatePara = &(pParas->m_paraPrimFreqState[pEventInfo->m_nCurrStateIndex]);

		if (pStatePara->m_nTriggerCondition == TMT_MDSTATE_MEARSURETRIGGER)
		{
			//手动触发按钮变亮
			g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,true);
		}
		else
		{
			//手动触发按钮变暗
			g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false);
		}
	}
}

void QSttMacroParaEditViewPrimFreqState::UpdateEventMsg( CEventResult *pCurrEventResult )
{
	if (pCurrEventResult == NULL)
	{
		return;
	}

	if (pCurrEventResult->m_fActTime > 0.00001)
	{
		CString strResultMsg;
		strResultMsg.Format(g_sLangTxt_Native_StatusLDActTime.GetString()/*_T("状态%ld动作时间%.4lfs.")*/,
			pCurrEventResult->m_nCurrStateIndex + 1, pCurrEventResult->m_fActTime);
		CLogPrint::LogString(XLOGLEVEL_RESULT, strResultMsg);
		if (strcmp(m_oStateTest->m_pszMacroID, STT_ORG_MACRO_PrimFreqStateTest) == 0)
		{
			UpdateActValue(pCurrEventResult);
		}
	}
}

//void QSttMacroParaEditViewPrimFreqState::GetSMVDataAppIDs(QList<int> &olistAppIDs)
//{
//	olistAppIDs.clear();
//	CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
//	CIecCfgSmvDataBase *pIecCfgSmvData = NULL;
//	POS pos = pIecCfgDatasSMV->GetHeadPosition();
////	long nFindIndex = 0;
//
//	while(pos)
//	{
//		pIecCfgSmvData = (CIecCfgSmvDataBase *)pIecCfgDatasSMV->GetNext(pos);
//
//		if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
//		{
//			continue;
//		}
//		olistAppIDs.append(((CIecCfg92Data*)pIecCfgSmvData)->m_dwAppID);
//	}
//
//// 	for (int i=0;i<pIecCfgDatasSMV->GetCount();i++)
//// 	{
//// 		pIecCfgSmvData = (CIecCfgSmvDataBase*)pIecCfgDatasSMV->GetAtIndex(i);
//// 		if (pIecCfgSmvData->GetClassID() != CFGCLASSID_CIECCFG92DATA)
//// 		{
//// 			continue;
//// 		}
//// 
//// 		m_olistAppIDs.append(((CIecCfg92Data*)pIecCfgSmvData)->m_dwAppID);
//// 	}
//}

//void QSttMacroParaEditViewPrimFreqState::GetSMVDataAppID(int nIndex)
//{
//	long nFindIndex = 0;
//
//	GetSMVDataAppIDs(nIndex);
//
//	if (nFindIndex == nIndex)
//	{
//		return;
//	}
//	else
//	{
//		nFindIndex++;
//	}
//}

long QSttMacroParaEditViewPrimFreqState::GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml)
{
	return CSttMacroParaEditViewOriginal::GetMacroItemsXml(strMacroItemsID,ppszItemsXml);
}

void QSttMacroParaEditViewPrimFreqState::GetMacroItemsXml(CSttItems &oRootItems)
{
	CSttItems* pRoot = new CSttItems;
	pRoot->m_strID = GetMacroID();
	pRoot->m_nTkID = 65535;
	oRootItems.AddNewChild(pRoot);

	CSttItems* pItems = new CSttItems;
	pItems->m_strID = GetMacroID();
	pItems->m_nTkID = 65535;
	pRoot->AddNewChild(pItems);

	for (int i = 0; i < m_pStateParas->m_nStateNumbers; i++)
	{
		CSttItems* pStateItems = new CSttItems;
		pStateItems->m_strID = "state" + QString::number(i);
		pStateItems->m_nTkID = 65535;
		pItems->AddNewChild(pStateItems);

		GetMacroItemsXml_Chs(pStateItems);
	}
}

void QSttMacroParaEditViewPrimFreqState::ProcessGbAfterGenTemplate(CSttGuideBook *pSttGuideBook)
{
	CString strMacroID;
	strMacroID = GetMacroID();
	CSttDevice *pDevice = pSttGuideBook->GetDevice();
	if(pDevice == NULL) //chenling 20250117 修改输出类型闪退问题
	{
		return; 
	}
	CSttItems* pRootItems=( CSttItems*)pDevice->FindByID (strMacroID/*_T("StateTest")*/);

	if (pRootItems ==NULL)
	{
		return;
	}

	CSttItemBase *pMacroTestState = (CSttItemBase *)pRootItems-> FindByID(strMacroID/*_T("StateTest")*/);
	CSttItems *pNewRootItems = NULL;
	int nRepeatNumbers = m_pStateParas->m_nRepeatNumbers;  
#ifdef USE_STT_STATE_EX_REPORT
	if ((nRepeatNumbers > STT_STATE_REPORT_MAX_REPEAT_COUNT)
		&& g_theTestCntrFrame->IsTestStarted())
	{
		nRepeatNumbers = STT_STATE_REPORT_MAX_REPEAT_COUNT; //dingxy 20240606 循环次数过多时生成模板速度慢导致界面卡，循环次数多时暂时不更新报告
	}
#endif
	for (long k = 1; k <= nRepeatNumbers; k++)
	{
		pNewRootItems = (CSttItems*)pRootItems->CloneEx();
		pNewRootItems->m_strID.AppendFormat(_T("%d"), k+1);  
		pNewRootItems->m_strName.AppendFormat(_T("%d"), k+1);  
		pDevice->AddNewChild(pNewRootItems);

		CSttItemBase *pCurrItem = (CSttItemBase *) pMacroTestState ->Clone();  //克隆Item
		pNewRootItems->AddNewChild(pCurrItem);
	}
}

void QSttMacroParaEditViewPrimFreqState::UpdateReportFile()
{
#ifdef USE_STT_STATE_EX_REPORT
	CString strFileName,strExFileName,strPath;
	strFileName = g_pTheSttTestApp->m_pTestMacroUI->m_strReportFile;
	
	if (strFileName.Find("Ex_Report.html")>0)
	{
		strExFileName = strFileName;
		strFileName.Replace("Ex_Report.html","_Report.html");
	}
	else
	{
		strExFileName = strFileName;
		strExFileName.Replace("_Report.html","Ex_Report.html");
	}

	strPath = _P_GetDBPath();
	strPath += "ui/";
#ifdef NOT_USE_XLANGUAGE  //zhouhj 20220401 如果未使用多语言,固定用中文
	strPath += _T("chinese");
#else
	strPath += xlang_GetCurrLanguageID();
#endif
	strPath += "/";
	strPath += strExFileName;

	if (!IsFileExist(strPath))
	{
		g_pTheSttTestApp->m_pTestMacroUI->m_strReportFile = strFileName;
		return;
	}

	int nRepeatNumbers = m_pStateParas->m_nRepeatNumbers;  //循环次数参数
	int nStateCount = m_pStateParas->m_nStateNumbers;

	if (((nStateCount > STT_SINGLE_STATE_MAX_REPORT_COUNT)
		|| (nStateCount * nRepeatNumbers > STT_STATE_REPORT_TOTAL_STATE_NUM))
		&& g_theTestCntrFrame->IsTestStarted())
	{
		g_pTheSttTestApp->m_pTestMacroUI->m_strReportFile = strExFileName;
	}
	else
	{
		g_pTheSttTestApp->m_pTestMacroUI->m_strReportFile = strFileName;
	}

#endif
}

//void QSttMacroParaEditViewPrimFreqState::ProcessRptAfterGenTemplate(QSttReportViewHtml *pSttReportViewHtml)
//{
//	//获得项目的报告数据strReport【初始化的时候，每个数据都是一样的】
//	char *strReport = NULL,*strNewReport = NULL;
//	long nLen = 0;
//	CString strMacroID = g_pTheSttTestApp->m_pTestMacroUI->m_strID;
//	nLen = GetMacroItemsXml(strMacroID, &strReport);
//	///*g_theTestCntrFrame->*/GetMacroItemsXml(&strReport, nLen);
//
//	CString strItemID;
//	int nRepeatNumbers = m_pStateParas->m_nRepeatNumbers;  //循环次数参数
//	long nRepeatIndex = 0;
//
//	UpdateReportFile();
//
//#ifdef USE_STT_STATE_EX_REPORT
//	if ((nRepeatNumbers > STT_STATE_REPORT_MAX_REPEAT_COUNT)
//		&& g_theTestCntrFrame->IsTestStarted())
//	{
//		nRepeatNumbers = STT_STATE_REPORT_MAX_REPEAT_COUNT;
//	}
//#endif
//
//	for (nRepeatIndex = 0; nRepeatIndex< nRepeatNumbers;nRepeatIndex++)
//	{
//		strItemID.Format("StateTest%d", nRepeatIndex+2);
//		//pSttReportViewHtml->OpenRptFileData(g_pTheSttTestApp->m_pTestMacroUI->m_strReportFile,"",strItemID);
//		strNewReport = new char[nLen+20];
//		memset(strNewReport,0,nLen+20);
//		memcpy(strNewReport,strReport,nLen);
//		pSttReportViewHtml->AddInsertCmd(g_pTheSttTestApp->m_pTestMacroUI,"", strItemID, strNewReport, FALSE);
//		//pSttReportViewHtml->InsertRptHtml("", strItemID, strNewReport);
//
//		strNewReport = new char[nLen+20];
//		memset(strNewReport,0,nLen+20);
//		memcpy(strNewReport,strReport,nLen);
//		//根据报告数据更新每个状态序列的状态数【报告模板，默认状态数是20个，需要根据设置的状态数删除多余的状态报告】
//		pSttReportViewHtml->AddUpdateCmd(g_pTheSttTestApp->m_pTestMacroUI, "", strItemID, strNewReport, FALSE);
//		//pSttReportViewHtml->UpdateMacroTestReport("", strItemID,strNewReport);
//	}
//
//	for (;nRepeatIndex < m_nRepeatNum_GenerateRpt;nRepeatIndex++)
//	{
//		strItemID.Format("StateTest%d", nRepeatIndex+2);
//		pSttReportViewHtml->DeleteRptHtml("",strItemID);
//	}
//
//	m_nRepeatNum_GenerateRpt = nRepeatNumbers;
//
//	delete strReport;
//
//	//pSttReportViewHtml->ExcuteNextCmd();
//}

CString QSttMacroParaEditViewPrimFreqState::ProcessItemID(const CString & strItemID,long nLoopIndex)
{
	//strItemID：根据当前重复的次数，动态更新ID，与模板调整的ID一致的
	CString strNewID;

	if(nLoopIndex <= 0)
	{
		if (strItemID.IsEmpty())
		{
			strNewID = _T("StateTest$StateTest");
		} 
		else
		{
		strNewID = strItemID;
	}
	}
	else
	{
		strNewID.Format(_T("StateTest%d$StateTest"), nLoopIndex+1);
	}

	return strNewID;
}
