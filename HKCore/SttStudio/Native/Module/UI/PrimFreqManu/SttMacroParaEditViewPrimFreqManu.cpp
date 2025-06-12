#include "SttMacroParaEditViewPrimFreqManu.h"
#include "../../SmartCap/XSmartCapMngr.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"
#include"../Module/XLangResource_Native.h"
#include "QDcSignalMapDialog.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewPrimFreqManual* g_pPrimFreqManualTest = NULL;

QSttMacroParaEditViewPrimFreqManual::QSttMacroParaEditViewPrimFreqManual(QWidget *parent) 
		: QSttMacroParaEditViewManualBase(parent)
{
	g_pPrimFreqManualTest = this;

	debug_time_long_log("MacroParaEditViewPrimFreqManual setupUi", true);

	m_pMainLayout = new QVBoxLayout(this);
	m_pManualTest_UI = new QPrimFreqManualWidget(this);
	m_pMainLayout->addWidget(m_pManualTest_UI);
	setLayout(m_pMainLayout);	

#ifdef _PSX_QT_WINDOWS_
	setMaximumSize(QSize(5000, 5000));
#endif

	InitLanuage();
	debug_time_long_log("MacroParaEditViewManualInitLanuage ", true);

	m_bTmtParaChanged = FALSE;
	m_bIsChanging = FALSE;

	m_strParaFileTitle = g_sLangTxt_State_Genexperfile;//通用试验模板文件 lcq 3.14
	m_strParaFilePostfix = "project(*.pfmntxml)";

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
//	CreateTestResource();
	g_theTestCntrFrame->InitTestResource();
	debug_time_long_log("MacroParaEditViewPrimFreqManual InitTestResource", true);

	m_pManualParas =(tmt_PrimFreqManualParas *)&m_oManualTest.m_oManuParas;

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

	OpenTestTestMngrFile(m_strDefaultParaFile);
	debug_time_long_log("MacroParaEditViewPrimFreqManual OpenTestTestMngrFile", true);

	CopyBinaryConfig();
	debug_time_long_log("MacroParaEditViewPrimFreqManual CopyBinaryConfig", true);
	//g_theTestCntrFrame->UpdateToolButtons();//QSttTestCntrFrameBase::OpenMacroTestUI_Test会再次重复刷新

	this->InitIVView();
	debug_time_long_log("MacroParaEditViewPrimFreqManual InitIVView", true);
	
	this->InitParasView();
	debug_time_long_log("MacroParaEditViewPrimFreqManual InitParasView", true);

	InitConnect();

	m_oParas.SetData(g_oSttTestResourceMngr.m_pTestResouce, m_pManualParas, 0);
	debug_time_long_log("MacroParaEditViewPrimFreqManual UpdateHarmCheckComboxUI", true);

	if (m_oIV.m_pUIParaWidget)
	{
		m_oIV.m_pUIParaWidget->setMacroType(MACROTYPE_Manual);
		m_oIV.m_pUIParaWidget->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
		m_oIV.m_pUIParaWidget->setMaxMinAndEDVal();
		connect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	}

	debug_time_long_log("MacroParaEditViewPrimFreqManual m_pUIParaWidget", true);

	if (m_oIV.m_pHarmUIParaWidget)
	{
		m_oIV.m_pHarmUIParaWidget->setMacroType(MACROTYPE_ManualHarm);
		m_oIV.m_pHarmUIParaWidget->setHarmIndex(&m_pManualParas->m_nHarmIndex);
		m_oIV.m_pHarmUIParaWidget->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
		m_oIV.m_pHarmUIParaWidget->setMaxMinAndEDVal();
		connect(m_oIV.m_pHarmUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	}

	debug_time_long_log("MacroParaEditViewPrimFreqManual m_pHarmUIParaWidget", true);


	SetDatas(NULL);
	debug_time_long_log("MacroParaEditViewPrimFreqManual SetDatas", true);

	debug_time_long_log("MacroParaEditViewPrimFreqManual m_pTabWidget->setCurrentIndex", true);
}

void QSttMacroParaEditViewPrimFreqManual::InitLanuage()
{

}

QSttMacroParaEditViewPrimFreqManual::~QSttMacroParaEditViewPrimFreqManual()
{
// 	if(m_pManualParas->m_nFuncType)
// 	{
// 		CXSmartCapMngr::Release();
// 	}
    delete m_pManualTest_UI;
}

void QSttMacroParaEditViewPrimFreqManual::SendUpdateParameter()
{
	g_theTestCntrFrame->Ats_UpdateParameter();
}

void QSttMacroParaEditViewPrimFreqManual::CopyBinaryConfig(BOOL b)
{
	if(b)
	{
		g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic = m_pManualParas->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect = m_pManualParas->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binOut[i].nState = m_pManualParas->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i].nSelect = m_pManualParas->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binOutEx[i].nState = m_pManualParas->m_binOutEx[i].nState;
		}
	}
	else
	{
		m_pManualParas->m_nBinLogic = g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			m_pManualParas->m_binIn[i].nSelect = g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			m_pManualParas->m_binOut[i].nState = g_theTestCntrFrame->GetBinaryConfig()->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pManualParas->m_binInEx[i].nSelect = g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pManualParas->m_binOutEx[i].nState = g_theTestCntrFrame->GetBinaryConfig()->m_binOutEx[i].nState;
		}
	}
}

void QSttMacroParaEditViewPrimFreqManual::InitConnect()
{
	connect(&m_oParas, SIGNAL(sig_ChannelTableItemValue(QString,float,int,int,bool)),this,SLOT(slot_ChannelTableItemValue(QString,float,int,int,bool)),Qt::UniqueConnection);
	connect(m_pManualTest_UI->m_pEditTime, SIGNAL(clicked()), this, SLOT(on_m_editTimeChanged()));
	connect(m_pManualTest_UI->m_pEditStep, SIGNAL(clicked()), this, SLOT(on_m_editStepChanged()));
	connect(m_pManualTest_UI->m_pEditInitVal, SIGNAL(clicked()), this, SLOT(on_m_editInitValueChanged()));
	connect(m_pManualTest_UI->m_pEditFinishVal, SIGNAL(clicked()), this, SLOT(on_m_editFinishValueChanged()));

	connect(m_pManualTest_UI->m_pEditTime, SIGNAL(editingFinished()), this, SLOT(on_m_editTime_editingFinished()));
	connect(m_pManualTest_UI->m_pEditStep, SIGNAL(editingFinished()), this, SLOT(on_m_editStep_editingFinished()));
	connect(m_pManualTest_UI->m_pEditInitVal, SIGNAL(editingFinished()), this, SLOT(on_m_editIintVal_editingFinished()));
	connect(m_pManualTest_UI->m_pEditFinishVal, SIGNAL(editingFinished()), this, SLOT(on_m_editFinishVal_editingFinished()));

	connect(m_pManualTest_UI->m_pTabWidget, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
	connect(m_pManualTest_UI->m_pBtnAdd, SIGNAL(clicked()), this, SLOT(on_m_btnAdd_clicked()));
	connect(m_pManualTest_UI->m_pBtnMinus, SIGNAL(clicked()), this, SLOT(on_m_btnMinus_clicked()));
	connect(m_pManualTest_UI->m_pCbAuto, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbAuto_clicked(int)));
	connect(m_pManualTest_UI->m_pCbbSelect, SIGNAL(currentIndexChanged(int )), this, SLOT(on_m_cbbSelect_currentIndexChanged(int)));
	connect(m_pManualTest_UI->m_pCbbChannel, SIGNAL(currentIndexChanged(int )), this, SLOT(on_m_cbbChannel_currentIndexChanged(int)));
	connect(m_pManualTest_UI->m_pCbbDcChangeType, SIGNAL(currentIndexChanged(int )), this, SLOT(on_m_cbbChangeType_currentIndexChanged(int)));

	connect(m_pManualTest_UI->m_pCbOut1, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbOut1_clicked(int)));
	connect(m_pManualTest_UI->m_pCbOut2, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbOut2_clicked(int)));
	connect(m_pManualTest_UI->m_pCbOut3, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbOut3_clicked(int)));
	connect(m_pManualTest_UI->m_pCbOut4, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbOut4_clicked(int)));
	connect(m_pManualTest_UI->m_pInBinaryOutSet, SIGNAL(clicked()), this, SLOT(on_m_btnInBinaryOutSet_clicked()));

	connect(m_pManualTest_UI->m_pGrpPulseSignal, SIGNAL(clicked(bool)), this,SLOT(slot_GrpPulse_cliked()));
	connect(m_pManualTest_UI->m_pGrpDcSignal, SIGNAL(clicked(bool)), this,SLOT(slot_GrpDc_cliked()));
	connect(m_pManualTest_UI->m_pCbbPulseType, SIGNAL(currentIndexChanged(int )), this, SLOT(slot_cbb_PulseType(int)));
	connect(m_pManualTest_UI->m_pCbbPeakValue, SIGNAL(currentIndexChanged(int )), this, SLOT(slot_cbb_PeakValue(int)));
	connect(m_pManualTest_UI->m_pCbbDcChangeType, SIGNAL(currentIndexChanged(int )), this, SLOT(slot_cbb_DcChangeType(int)));

	connect(m_pManualTest_UI->m_pEditPulseWidth, SIGNAL(editingFinished()), this, SLOT(slot_edt_PulseWidth()));
	connect(m_pManualTest_UI->m_pEditPulseFreq, SIGNAL(editingFinished()), this, SLOT(slot_edt_PulseFreq()));
	connect(m_pManualTest_UI->m_pEditDcChangeValue, SIGNAL(editingFinished()), this, SLOT(slot_edt_DcChangeValue()));
	connect(m_pManualTest_UI->m_pEditDc1, SIGNAL(editingFinished()), this, SLOT(slot_edt_Dc1()));
	connect(m_pManualTest_UI->m_pEditDc2, SIGNAL(editingFinished()), this, SLOT(slot_edt_Dc2()));
	connect(m_pManualTest_UI->m_pBtnMapping, SIGNAL(clicked()), this, SLOT(slot_btn_Mapping()));

	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas()));
 
}

void QSttMacroParaEditViewPrimFreqManual::UinitConnect()
{
// 	connect(&m_oParas, SIGNAL(sig_ChannelTableItemValue(QString,float,int,int,bool)),this,SLOT(slot_ChannelTableItemValue(QString,float,int,int,bool)),Qt::UniqueConnection);
// 	connect(m_pManualTest_UI->m_pEditTime, SIGNAL(clicked()), this, SLOT(on_m_editTimeChanged()));
// 	connect(m_pManualTest_UI->m_pEditStep, SIGNAL(clicked()), this, SLOT(on_m_editStepChanged()));
// 	connect(m_pManualTest_UI->m_pEditInitVal, SIGNAL(clicked()), this, SLOT(on_m_editInitValueChanged()));
// 	connect(m_pManualTest_UI->m_pEditFinishVal, SIGNAL(clicked()), this, SLOT(on_m_editFinishValueChanged()));
// 	connect(m_pManualTest_UI->m_pTabWidget, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
// 	connect(m_pManualTest_UI->m_pBtnAdd, SIGNAL(clicked()), this, SLOT(on_m_btnAdd_clicked()));
// 	connect(m_pManualTest_UI->m_pBtnMinus, SIGNAL(clicked()), this, SLOT(on_m_btnMinus_clicked()));
// 	connect(m_pManualTest_UI->m_pCbAuto, SIGNAL(stateChanged()), this, SLOT(on_m_cbAuto_clicked()));
// 	connect(m_pManualTest_UI->m_pCbbSelect, SIGNAL(currentIndexChanged(int )), this, SLOT(on_m_cbbSelect_currentIndexChanged(int)));
// 	connect(m_pManualTest_UI->m_pCbbChannel, SIGNAL(currentIndexChanged(int )), this, SLOT(on_m_cbbChannel_currentIndexChanged(int)));
// 	connect(m_pManualTest_UI->m_pCbbDcChangeType, SIGNAL(currentIndexChanged(int )), this, SLOT(on_m_cbbChangeType_currentIndexChanged(int)));
// 
// 	connect(m_pManualTest_UI->m_pCbOut1, SIGNAL(stateChanged()), this, SLOT(on_m_cbOut1_clicked()));
// 	connect(m_pManualTest_UI->m_pCbOut2, SIGNAL(stateChanged()), this, SLOT(on_m_cbOut2_clicked()));
// 	connect(m_pManualTest_UI->m_pCbOut3, SIGNAL(stateChanged()), this, SLOT(on_m_cbOut3_clicked()));
// 	connect(m_pManualTest_UI->m_pCbOut4, SIGNAL(stateChanged()), this, SLOT(on_m_cbOut4_clicked()));
// 	connect(m_pManualTest_UI->m_pInBinaryOutSet, SIGNAL(clicked()), this, SLOT(on_m_btnInBinaryOutSet_clicked()));

}

void QSttMacroParaEditViewPrimFreqManual::UpdateAuxDCEdit()
{
	m_oParas.slot_UpdateUdcEditEnabled();
}

void QSttMacroParaEditViewPrimFreqManual::slot_currentChangedTabWidget(int nCurrIndex)
{
	if (m_pManualParas == NULL)
	{
		return;
	}

}

CSttTestResourceBase* QSttMacroParaEditViewPrimFreqManual::CreateTestResource()
{
// 	if (m_pOriginalSttTestResource == NULL)
// 	{
// 		m_pOriginalSttTestResource = new CSttTestResource_Sync();
// 	}

// 	g_theTestCntrFrame->m_pSttTestResource = m_pOriginalSttTestResource;
// 	g_oSttTestResourceMngr.m_pTestResouce = m_pOriginalSttTestResource;
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewPrimFreqManual::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
									long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	//yzj 2022-2-21 开始测试前要保持该值为0
	if(!g_theTestCntrFrame->IsTestStarted())
	{
		m_pManualParas->m_bBinStop = FALSE;
	}

	tmt_PrimFreqManualTest *pTmtManualTest = (tmt_PrimFreqManualTest *)pParas;

	/*CSttXmlSerializeBase *pXmlParas = */stt_xml_serialize(&pTmtManualTest->m_oManuParas, pMacroParas,nVolRsNum,nCurRsNum);

	if (bHasGoosePub)
	{
		//2023/11/27 wangjunsheng

		CIecCfgGoutDatas *pGoutDatas = NULL;
		pGoutDatas = m_listGoosePub.at(0);

		ASSERT(pGoutDatas);
		SerializeGoosePubs(pMacroParas,pGoutDatas);
	}

	if (bHasGoosePub)
	{
		CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
		ASSERT(pIecCfgDatasSMV);
		SerializeFT3Pubs(pMacroParas,pIecCfgDatasSMV);
	}
}

void QSttMacroParaEditViewPrimFreqManual::OnTestResults(CDataGroup *pResults)
{
	ASSERT(pResults != NULL);

	m_oManualTest.m_nTestState = 1;	//测试完成
}

void QSttMacroParaEditViewPrimFreqManual::InitBinaryInBinaryOutUI()
{
	//开入量设置
	/*Global_CheckBinSelect(m_pManualParas->m_binIn,g_nBinCount);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInA,m_pManualParas->m_binIn,0);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInB,m_pManualParas->m_binIn,1);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInC,m_pManualParas->m_binIn,2);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInD,m_pManualParas->m_binIn,3);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInE,m_pManualParas->m_binIn,4);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInF,m_pManualParas->m_binIn,5);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInG,m_pManualParas->m_binIn,6);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInH,m_pManualParas->m_binIn,7);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInI,m_pManualParas->m_binIn,8);
	GlobalSetQcheckState_BinaryIn(m_oParas.m_pCbInJ,m_pManualParas->m_binIn,9);*/

	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut1,m_pManualParas->m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut2,m_pManualParas->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut3,m_pManualParas->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut4,m_pManualParas->m_binOut,3);
	/*GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut5,m_pManualParas->m_binOut,4);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut6,m_pManualParas->m_binOut,5);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut7,m_pManualParas->m_binOut,6);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut8,m_pManualParas->m_binOut,7);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut9,m_pManualParas->m_binOut,8);
	GlobalSetQcheckState_BinaryOut(m_oParas.m_pCbOut10,m_pManualParas->m_binOut,9);*/
}

void QSttMacroParaEditViewPrimFreqManual::SetManualOtherParasFont()
{
	m_pManualTest_UI->m_pGrpCbOut->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbbChannel->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditInitVal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pLabInitVal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pLabFinishVal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditFinishVal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbbSelect->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pLabStep->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_plabTime->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditStep->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditTime->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbAuto->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_plabChangeType->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbbChangeType->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbOut1->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbOut2->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbOut3->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbOut4->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pBtnLock->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pBtnAdd->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pBtnMinus->setFont(*g_pSttGlobalFont);

	m_pManualTest_UI->m_pGrpPulseSignal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pLblPulseType->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbbPulseType->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pLblPulseWidth->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditPulseWidth->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pLblPeakValue->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pCbbPeakValue->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pLblPulseFreq->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditPulseFreq->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pGrpDcSignal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pLblDc1->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditDc1->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditDcChangeValue->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditDcChangeValue->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pLblDc2->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pEditDc2->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pBtnMapping->setFont(*g_pSttGlobalFont);

	m_pManualTest_UI->m_pInBinaryOutSet->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewPrimFreqManual::InitOtherParasUI()
{
	SetManualOtherParasFont();

}

void QSttMacroParaEditViewPrimFreqManual::UpdateTestResource(BOOL bCreateChMaps)
{

	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();

	CString strModel;
	strModel = g_oSttSystemConfig.GetDevModel();
	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	if (!pCurDevice->m_strModel.IsEmpty())
	{
		strModel = pCurDevice->m_strModel;
	}

	m_oIV.m_pUIParaWidget->initUI(g_theTestCntrFrame->GetSttTestResource());
	m_oIV.m_pUIParaWidget->initData(true);
	m_oIV.m_pUIParaWidget->setMaxMinAndEDVal();

	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_oIV.m_pHarmUIParaWidget->initUI(g_theTestCntrFrame->GetSttTestResource());
		m_oIV.m_pHarmUIParaWidget->initData(true);
		m_oIV.m_pHarmUIParaWidget->setMaxMinAndEDVal();
	}

	m_oParas.SetData(g_theTestCntrFrame->GetSttTestResource(), m_pManualParas, 0);
	InitBinaryInBinaryOutUI();

}

void QSttMacroParaEditViewPrimFreqManual::UpdateManualParas(bool bUpdateParasData)
{
	m_oIV.m_pUIParaWidget->initData(true);

	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_oIV.m_pHarmUIParaWidget->initData(true);
	}
	
	if (bUpdateParasData)
	{
	m_oParas.UpdateData();
	}
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewPrimFreqManual::ClearResult(PTMT_PARAS_HEAD pHead)
{
	m_oManualTest.m_oManuResult.init();
}

void QSttMacroParaEditViewPrimFreqManual::InitStyle()
{
	((QSttCheckBox*)m_pManualTest_UI->m_pCbAuto)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_pCbOut1)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_pCbOut2)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_pCbOut3)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_pCbOut4)->InitStyleSheet();

	((QSttTabWidget*)m_pManualTest_UI->m_pTabWidget)->InitStyleSheet();

}

void QSttMacroParaEditViewPrimFreqManual::InitParasView()
{
	InitStyle();
    m_oParas.m_pEditStep = m_pManualTest_UI->m_pEditStep;
    m_oParas.m_pEditInitVal = m_pManualTest_UI->m_pEditInitVal;
	m_oParas.m_pEditFinishVal = m_pManualTest_UI->m_pEditFinishVal;
    m_oParas.m_pEditTime = m_pManualTest_UI->m_pEditTime;
    m_oParas.m_pCbbChannel = m_pManualTest_UI->m_pCbbChannel;
    m_oParas.m_pCbbSelect = m_pManualTest_UI->m_pCbbSelect;
    m_oParas.m_pCbbChangeType = m_pManualTest_UI->m_pCbbChangeType;
    m_oParas.m_pCbOut1 = m_pManualTest_UI->m_pCbOut1;
    m_oParas.m_pCbOut2 = m_pManualTest_UI->m_pCbOut2;
    m_oParas.m_pCbOut3 = m_pManualTest_UI->m_pCbOut3;
    m_oParas.m_pCbOut4 = m_pManualTest_UI->m_pCbOut4;

	m_oParas.m_pBtnAdd = m_pManualTest_UI->m_pBtnAdd;
	m_oParas.m_pBtnMinus = m_pManualTest_UI->m_pBtnMinus;
	m_oParas.m_pBtnLock = m_pManualTest_UI->m_pBtnLock;
	m_oParas.m_pLabInitVal = m_pManualTest_UI->m_pLabInitVal;
	m_oParas.m_pLabFinishVal = m_pManualTest_UI->m_pLabFinishVal;
	m_oParas.m_pLabStep = m_pManualTest_UI->m_pLabStep;
	m_oParas.m_pCbAuto =  m_pManualTest_UI->m_pCbAuto;

	// 转速脉冲信号部分
	m_oParas.m_pGrpPulseSignal = m_pManualTest_UI->m_pGrpPulseSignal;
	m_oParas.m_pLblPulseType = m_pManualTest_UI->m_pLblPulseType;
	m_oParas.m_pCbbPulseType = m_pManualTest_UI->m_pCbbPulseType;
	m_oParas.m_pLblPulseWidth = m_pManualTest_UI->m_pLblPulseWidth;
	m_oParas.m_pEditPulseWidth = m_pManualTest_UI->m_pEditPulseWidth;
	m_oParas.m_pLblPeakValue = m_pManualTest_UI->m_pLblPeakValue;
	m_oParas.m_pCbbPeakValue = m_pManualTest_UI->m_pCbbPeakValue;
	m_oParas.m_pLblPulseFreq = m_pManualTest_UI->m_pLblPulseFreq;
	m_oParas.m_pEditPulseFreq = m_pManualTest_UI->m_pEditPulseFreq;

	// 直流信号源部分
	m_oParas.m_pDcLayout  = m_pManualTest_UI->m_pDcLayout;
	m_oParas.m_pGrpDcSignal = m_pManualTest_UI->m_pGrpDcSignal;
	m_oParas.m_pLblDc1 = m_pManualTest_UI->m_pLblDc1;
	m_oParas.m_pEditDc1 = m_pManualTest_UI->m_pEditDc1;
	m_oParas.m_pCbbDcChangeType = m_pManualTest_UI->m_pCbbDcChangeType;
	m_oParas.m_pEditDcChangeValue = m_pManualTest_UI->m_pEditDcChangeValue;
	m_oParas.m_pLblDc2 = m_pManualTest_UI->m_pLblDc2;
	m_oParas.m_pEditDc2 = m_pManualTest_UI->m_pEditDc2;
	m_oParas.m_pBtnMapping = m_pManualTest_UI->m_pBtnMapping;


	m_pManualTest_UI->m_pGrpCbOut->setFixedWidth(110);

	m_oParas.Init();
	InitOtherParasUI();

	m_oParas.m_pBtnAdd->setVisible(true);
	m_oParas.m_pBtnMinus->setVisible(true);
	m_oParas.m_pBtnLock->setVisible(true);



	InitBinaryInBinaryOutUI();

}

void QSttMacroParaEditViewPrimFreqManual::InitIVView()
{  
	setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_pTabWidget->setFont(*g_pSttGlobalFont);
	m_oIV.m_pTabWidget = m_pManualTest_UI->m_pTabWidget;
    m_oIV.InitUI(m_pManualParas->m_nFuncType);
}

void QSttMacroParaEditViewPrimFreqManual::slot_SwitchStateChanged()
{
	//UpdateToolButtons();将开出量传给框架
	m_oParas.UpdateData();//更新开出量状态

	if (g_theTestCntrFrame->IsTestStarted() && !m_pManualParas->m_bLockChanged)
	{
		SendUpdateParameter();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::InitBinStateOnStarting()
{
	/*初始化开出
	for (int i=0;i<g_oLocalSysPara.m_nCHBinOutNum;i++)
		m_oCurrEventResult.m_BinOut[i] = m_pManualParas->m_binOut[i].nState;

	for (int i=0;i<g_nBoutExCount;i++)
		m_oCurrEventResult.m_BinOutEx[i] = m_pManualParas->m_binOutEx[i].nState;

	UpdateToolButtons();
	*/
}


void QSttMacroParaEditViewPrimFreqManual::OnViewTestLink(BOOL b)
{

}

bool QSttMacroParaEditViewPrimFreqManual::PrepStartTest()
{
	m_bSystemParasChanged = FALSE;

	return true;
}

void QSttMacroParaEditViewPrimFreqManual::OnViewTestStart()
{

	InitBinStateOnStarting();
	BOOL bEnableState = TRUE;
	int nGooseParasUI_State = STT_UI_RUN_STATE_StateTested_Editable;

	if ((m_pManualParas->m_bAuto)/*||(m_pManualParas->m_nFuncType != TMT_MANU_FUNC_TYPE_Common)*/)
	{
		nGooseParasUI_State = STT_UI_RUN_STATE_StateTested_NotEditable;
		bEnableState = FALSE;
	}

	m_oIV.m_pUIParaWidget->startInit(bEnableState);
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	g_theTestCntrFrame->ClearInfoWidget();
	m_oParas.StartInit();


// 	m_pManualTest_UI->m_checkBoxHarm->setEnabled(false);
// 	m_pManualTest_UI->m_comboBoxHarm->setEnabled(m_pManualParas->m_nSelHarm);
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();

	m_pManualTest_UI->m_pInBinaryOutSet->setEnabled(bEnableState);

	if (m_pManualTest_UI->m_pCbAuto->checkState() == Qt::Checked)
	{
		m_pManualTest_UI->m_pGrpCbOut->setEnabled(false);
	}

	g_theTestCntrFrame->EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewPrimFreqManual::OnViewTestStop()
{
	m_oIV.m_pUIParaWidget->startInit();
// 	m_pManualTest_UI->m_checkBoxHarm->setEnabled(true);
// 	m_pManualTest_UI->m_comboBoxHarm->setEnabled(true);
	m_oParas.StopInit();

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget(false);//20220628 zhouhj 暂时改为不更新界面参数,防止界面参数被修改为0
	g_theTestCntrFrame->StopPowerWidget();
	m_oIV.m_pUIParaWidget->UpdateTables();

	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_oIV.m_pHarmUIParaWidget->startInit();
		m_oIV.m_pHarmUIParaWidget->UpdateTables();
	}


	m_pManualTest_UI->m_pInBinaryOutSet->setEnabled(true);

}

void QSttMacroParaEditViewPrimFreqManual::on_m_btnLock_clicked()
{
	m_oParas.slot_btn_LockClicked();
	
	if (g_theTestCntrFrame->IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}
	
	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_btnAdd_clicked()
{
	if(m_bIsChanging)
	{
		return;
	}

	disconnect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()));

	m_oParas.slot_btn_AddClicked();
	SetParaChanged();

	connect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	emit sig_updataParas();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_btnMinus_clicked()
{
	if(m_bIsChanging)
	{
		return;
	}

	disconnect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()));

	m_oParas.slot_btn_MinusClicked();
	SetParaChanged();

	connect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	emit sig_updataParas();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_editIintVal_editingFinished()
{
	m_oParas.slot_lne_startChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_editFinishVal_editingFinished()
{
	m_oParas.slot_lne_endChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_editTime_editingFinished()
{
	m_oParas.slot_lne_steptimeChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_editUdc_editingFinished()
{
	m_oParas.slot_lne_UdcChanged();
	SetParaChanged();
	
}
//void QSttMacroParaEditViewPrimFreqManual::on_m_editDelayed_editingFinished()
//{
//	m_oParas.slot_lne_delayedChanged();
//	SetParaChanged();
//}

void QSttMacroParaEditViewPrimFreqManual::on_m_editStep_editingFinished()
{
	m_oParas.slot_lne_stepChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
{
	m_bIsChanging = TRUE;

	//20240919 suyang 幅值  电压时，步长需要进行转换 一次值
	if (!IsUseSecondParaSet() &&  (valueFlag == amplitude_type))
	{
		if (str.contains("U"))
		{
			fstep = fstep/1000;
		}
	}
	
	m_oIV.m_pUIParaWidget->setChannelTableItemValue(str, fstep, valueFlag, AddOrMinus, bDC);
	m_bIsChanging = FALSE;
}

void QSttMacroParaEditViewPrimFreqManual::slot_updateParas()
{
	if (g_theTestCntrFrame == NULL)
	{
		return;
	}

	if (g_theTestCntrFrame->IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}

	g_theTestCntrFrame->UpdateVectorData();
	g_theTestCntrFrame->UpdatePowerData();


	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_cbAuto_clicked(int nIndex)
{
	m_oParas.slot_cb_AutoClicked();
	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_cbbSelect_currentIndexChanged(int index)
{
	if(m_oParas.m_pCbbSelect->IsScrolling())
	{
		return;
	}	

	m_oParas.slot_cbb_SelectChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_cbbChannel_currentIndexChanged(int index)
{
	if(m_oParas.m_pCbbChannel->IsScrolling())
	{
		return;
	}	

	m_oParas.slot_cbb_ChannelChanged(index);

	SetParaChanged();

	m_strCbbChannel=m_pManualTest_UI->m_pCbbChannel->currentText();
	
	if(CHANNAL_TYPE_I(m_pManualParas->m_nGradientChSelect))
	{
		m_pManualParas->m_nVarIndexType = 0;
	}
	else if (CHANNAL_TYPE_U(m_pManualParas->m_nGradientChSelect))
	{
		m_pManualParas->m_nVarIndexType = 1;
	}
	else if(CHANNAL_TYPE_F(m_pManualParas->m_nGradientChSelect))
	{
		m_pManualParas->m_nVarIndexType = 2;
	}
}

void QSttMacroParaEditViewPrimFreqManual::on_m_cbbChangeType_currentIndexChanged(int index)
{
	if(m_oParas.m_pCbbChangeType->IsScrolling())
	{
		return;
	}	

	m_oParas.slot_cbb_ChangeTypeChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_cbOut1_clicked(int nIndex)
{
	m_oParas.slot_ck_Out1StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_cbOut2_clicked(int nIndex)
{
	m_oParas.slot_ck_Out2StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_cbOut3_clicked(int nIndex)
{
	m_oParas.slot_ck_Out3StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewPrimFreqManual::on_m_cbOut4_clicked(int nIndex)
{
	m_oParas.slot_ck_Out4StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewPrimFreqManual::ShowReport(CDvmValues *pValues)
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

// 	if (pActTimeData != NULL)// zhouhj 2024.1.19 不能在此处修约,后续还要用到该数据
// 	{
// 		fActTime = GlobalSetResultValue(pActTimeData,4);
// 		//		pActTimeData->m_strValue = QString::number(fActTime,'f',4);
// 	}

	if (pActReturnData != NULL)
	{
		fReturnValue = GlobalSetResultValue(pActReturnData,3);
		//		pActReturnData->m_strValue = QString::number(fReturnValue,'f',3);
	}

}

CString QSttMacroParaEditViewPrimFreqManual::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += FILE_PRIMFREQMANUALTEST;
	strFile += _T(".");
	strFile += POSTFIX_PRIMFREQMANUALTEST;

	return strFile;
}

bool QSttMacroParaEditViewPrimFreqManual::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
{
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != POSTFIX_PRIMFREQMANUALTEST)
	{
		return false;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return false;
	}

	return true;
}

void QSttMacroParaEditViewPrimFreqManual::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

//判断使用的keyboard类型
void QSttMacroParaEditViewPrimFreqManual::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
{
	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();

	if(bIsNor == FALSE)
	{
		QString strVar = m_pManualTest_UI->m_pCbbChannel->currentText();
		int nIdx = m_pManualTest_UI->m_pCbbSelect->currentIndex();
		switch(nIdx)
		{
		case 0: 
			if(strVar.contains("U"))
			{
				GetWidgetBoard_DigitData(0,str,pEditLine,this);
			}
			else
			{
				GetWidgetBoard_DigitData(1,str,pEditLine,this);
			}
			break;
		case 1: GetWidgetBoard_DigitData(2,str,pEditLine,this); break;
		case 2: GetWidgetBoard_DigitData(3,str,pEditLine,this); break;
		default:
			break;
		}

	}
	else
	{
		GetWidgetBoard_DigitData(4,str,pEditLine,this);
	}

// 	if (str.right(1).contains("."))
// 	{
// 		str.append("000");
// 	}
// 
// 	pEditLine->setText(str);
// 	pEditLine->SetEditFinished();
}

void QSttMacroParaEditViewPrimFreqManual::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pManualParas, &oRead);
		debug_time_long_log("SetDatas stt_xml_serialize", true);
	}

	g_theTestCntrFrame->InitVectorWidget(m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
	debug_time_long_log("SetDatas InitVectorWidget", true);

	g_theTestCntrFrame->InitPowerWidget(m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
	debug_time_long_log("SetDatas InitPowerWidget", true);


    g_theTestCntrFrame->InitStateMonitor();
	debug_time_long_log("SetDatas InitStateMonitor", true);

    g_theTestCntrFrame->ClearInfoWidget();
	debug_time_long_log("SetDatas ClearInfoWidget", true);

    UpdateManualParas(FALSE);//dingxy 20240603 构造函数中setdata调用m_oParas.UpdateData();重复调用注释
	debug_time_long_log("SetDatas UpdateManualParas", true);

	SetPlotAcDcMaxMinValue();//20241101 suyang 初始化时也需要通过当前电压电流通道值更新状态图坐标轴

}

BOOL QSttMacroParaEditViewPrimFreqManual::SetValues_dsRcdStep6U6I(CDvmDataset *pDsRcdStep6U6I)
{
	if ((m_pManualParas == NULL)||(pDsRcdStep6U6I == NULL))
	{
		return FALSE;
	}

	CDvmData *pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID("Freq");

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[0].Harm[1].fFreq);
	}

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_IsZeroDriftTest);

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_ZeroDrift_Un);

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_oMuParas.fUn);
	}

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_ZeroDrift_In);

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_oMuParas.fIn);
	}

//  	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_DelayCompens_NoPPS);
//  
//  	if (pCurrData != NULL)
//  	{
//  		pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_oMuParas.fDelayCompens_NoPPS);
//  	}

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID("IsSuperHarm");

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%d"),m_pManualParas->m_nSelHarm);
	}

	pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID("HarmCount");

	if (pCurrData != NULL)
	{
		pCurrData->m_strValue.Format(_T("%d"),m_pManualParas->m_nHarmIndex);
	}

	for (int nIndex = 0;nIndex<6;nIndex++)
	{
/////////////////////////////////////////////////电压幅值、相位赋值//////////////////////////////////////////////////////////////////////////////////
		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelName[nIndex]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[nIndex].Harm[1].fAmp);
		}

		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelPh[nIndex]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[nIndex].Harm[1].fAngle);
		}

/////////////////////////////////////////////////电流幅值、相位赋值//////////////////////////////////////////////////////////////////////////////////
		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelName[nIndex+6]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiCUR[nIndex].Harm[1].fAmp);
		}

		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelPh[nIndex+6]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiCUR[nIndex].Harm[1].fAngle);
		}

/////////////////////////////////////////////////电压谐波幅值、相位赋值//////////////////////////////////////////////////////////////////////////////////
		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelHarm[nIndex]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[nIndex].Harm[m_pManualParas->m_nHarmIndex].fAmp);
		}

		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelHarmPh[nIndex]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiVOL[nIndex].Harm[m_pManualParas->m_nHarmIndex].fAngle);
		}

/////////////////////////////////////////////////电流谐波幅值、相位赋值//////////////////////////////////////////////////////////////////////////////////
		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelHarm[nIndex+6]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiCUR[nIndex].Harm[m_pManualParas->m_nHarmIndex].fAmp);
		}

		pCurrData = (CDvmData*)pDsRcdStep6U6I->FindByID(g_strListChannelHarmPh[nIndex+6]);

		if (pCurrData != NULL)
		{
			pCurrData->m_strValue.Format(_T("%f"),m_pManualParas->m_uiCUR[nIndex].Harm[m_pManualParas->m_nHarmIndex].fAngle);
		}
	}

	return TRUE;
}

void QSttMacroParaEditViewPrimFreqManual::on_m_editTimeChanged()
{
	slot_edit_changed(m_pManualTest_UI->m_pEditTime, TRUE);
}

void QSttMacroParaEditViewPrimFreqManual::on_m_editStepChanged()
{
	slot_edit_changed(m_pManualTest_UI->m_pEditStep, TRUE);
}

void QSttMacroParaEditViewPrimFreqManual::on_m_editInitValueChanged()
{
	slot_edit_changed(m_pManualTest_UI->m_pEditInitVal, TRUE);
}

void QSttMacroParaEditViewPrimFreqManual::on_m_editFinishValueChanged()
{
	slot_edit_changed(m_pManualTest_UI->m_pEditFinishVal, TRUE);
}

void QSttMacroParaEditViewPrimFreqManual::on_m_btnInBinaryOutSet_clicked()
{
	QSttManualBinBoutDlg oManualBinBoutDlg(m_pManualParas->m_binIn,m_pManualParas->m_binOut,
		&m_pManualParas->m_nBinLogic,&m_pManualParas->m_manuGradient.fTrigDelay,
		&m_pManualParas->m_bAuto,this);// zhouhj 临时变量命名从sttManualBinBoutDlg改为oManualBinBoutDlg
	oManualBinBoutDlg.setWindowModality(Qt::WindowModal);//模态窗口

#ifdef _USE_SoftKeyBoard_
    QSoftKeyBoard::AttachObj(&oManualBinBoutDlg);
#endif

	if (oManualBinBoutDlg.exec() == QDialog::Accepted)
	{
		emit sig_updataParas();
	}
	
#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif
}

void QSttMacroParaEditViewPrimFreqManual::slot_GrpPulse_cliked()
{
	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;
	if(m_pManualTest_UI->m_pGrpPulseSignal->isChecked())
	{
		pParas->m_nOutputType = 1;
		m_pManualTest_UI->m_pGrpDcSignal->setChecked(false);
	}
	else
	{
		if(!m_pManualTest_UI->m_pGrpDcSignal->isChecked())
		{
			pParas->m_nOutputType = 0;
		}
	}
	

}

void QSttMacroParaEditViewPrimFreqManual::slot_GrpDc_cliked()
{
	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;
	if(m_pManualTest_UI->m_pGrpDcSignal->isChecked())
	{
		pParas->m_nOutputType = 2;
		m_pManualTest_UI->m_pGrpPulseSignal->setChecked(false);
	}
	else if(!m_pManualTest_UI->m_pGrpPulseSignal->isChecked())
	{
		pParas->m_nOutputType = 0;
	}

}

void QSttMacroParaEditViewPrimFreqManual::slot_cbb_PulseType( int nIndex )
{
	if(nIndex < 0)
	{
		return;
	}
	CString strText = m_pManualTest_UI->m_pCbbPulseType->currentText();
	bool bEnble = (strText == _T("正弦波"))? FALSE: TRUE;
	
	m_pManualTest_UI->m_pLblPulseWidth->setEnabled(bEnble);
	m_pManualTest_UI->m_pEditPulseWidth->setEnabled(bEnble);

	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;
	pParas->m_nSpeedPulseType = nIndex;

}

void QSttMacroParaEditViewPrimFreqManual::slot_cbb_PeakValue( int nIndex )
{
	if(nIndex < 0)
	{
		return;
	}
	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;

	pParas->m_nPeakToPeakTypeIndex = nIndex;

}

void QSttMacroParaEditViewPrimFreqManual::slot_cbb_DcChangeType( int nIndex )
{
	if(nIndex < 0)
	{
		return;
	}
	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;
	pParas->m_nDcOutputMode = nIndex;
}

void QSttMacroParaEditViewPrimFreqManual::slot_edt_PulseWidth()
{
	float fv = m_pManualTest_UI->m_pEditPulseWidth->text().toFloat();
	if( fv < 0.0f || fv > 20.0f)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("脉冲宽度支持2～20ms,请重新输入！"));
	}
	fv = setLimit(0.0f, 20.0f, fv);

	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;
	pParas->m_nPulseWidth = fv;
	m_pManualTest_UI->m_pEditPulseWidth->setText(QString::number(fv,'f',0));

}

void QSttMacroParaEditViewPrimFreqManual::slot_edt_PulseFreq()
{
	float fv = m_pManualTest_UI->m_pEditPulseWidth->text().toFloat();
	if( fv < 40.0f || fv > 8000.0f)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("频率支持40～8000Hz,请重新输入！"));
	}
	fv = setLimit(40.0f, 8000.0f, fv);

	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;
	pParas->m_fPulseFreqHz = fv;
	m_pManualTest_UI->m_pEditPulseFreq->setText(QString::number(fv,'f',4));

}

void QSttMacroParaEditViewPrimFreqManual::slot_edt_DcChangeValue()
{
	float fv = m_pManualTest_UI->m_pEditDcChangeValue->text().toFloat();
	if(fabs(fv -0.0f) <= 0.000001)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("请先设置对应关系！"));
		return;
	
	}
	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;

	CString strType = m_pManualTest_UI->m_pCbbDcChangeType->currentText();
	float fMin = 0.0f, fMax = 0.0f;
	if(strType == _T("电网频率"))
	{
		fMin = pParas->m_fGridFrequencyMinHz;
		fMax = pParas->m_fGridFrequencyMaxHz;
	}
	else if(strType == _T("发电机转速"))
	{
		fMin = pParas->m_fGenSpeedMinRpm;
		fMax = pParas->m_fGenSpeedMaxRpm;
	}
	
	if((fabs(fv - fMax) > 0.00001) || (fabs(fMin - fv)> 0.00001))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("当前模式输入范围应为%.3f~%.3f之间！"),fMin,fMax);
	}
	
	pParas->m_fDcOutputValue = fv;
	m_pManualTest_UI->m_pEditDcChangeValue->setText(QString::number(fv,'f',4));

}

void QSttMacroParaEditViewPrimFreqManual::slot_edt_Dc1()
{
	float fv = m_pManualTest_UI->m_pEditDc1->text().toFloat();
	if( fv < 4.0f || fv > 12.0f)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("两路直流信号源输出支持4～12mA,请重新输入！"));
	}
	fv = setLimit(4.0f, 12.0f, fv);

	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;
	pParas->m_frCurrentDc[0] = fv;
	m_pManualTest_UI->m_pEditDc1->setText(QString::number(fv,'f',4));

}

void QSttMacroParaEditViewPrimFreqManual::slot_edt_Dc2()
{
	float fv = m_pManualTest_UI->m_pEditDc2->text().toFloat();
	if( fv < 4.0f || fv > 12.0f)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("两路直流信号源输出支持4～12mA,请重新输入！"));
	}
	fv = setLimit(4.0f, 12.0f, fv);

	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;
	pParas->m_frCurrentDc[1] = fv;
	m_pManualTest_UI->m_pEditDc2->setText(QString::number(fv,'f',4));

}

void QSttMacroParaEditViewPrimFreqManual::slot_btn_Mapping()
{
	tmt_PrimFreqManualParas *pParas = (tmt_PrimFreqManualParas *)m_pManualParas;
	
	QDcSignalMapDialog dialog(pParas,this);
	dialog.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::AttachObj(&dialog);
		dialog.exec();
		QSoftKeyBoard::ReAttachObj();
#else
		dialog.exec();
#endif
}

CString QSttMacroParaEditViewPrimFreqManual::GetMacroTestResultUnit()
{
	long nChType = m_oParas.GetChanneType();
	long nUnitType = m_oParas.GetCbbSelect();

	CString strUnit;

	switch (nUnitType)
	{
	case amplitude_type:
		switch (nChType)
		{
		case 0:
			if (!IsUseSecondParaSet())
			{
				strUnit = _T("kV");

			}
			else
			{
			strUnit = _T("V");

			}
			break;
		case 1:
			strUnit = _T("A");
			break;
		default:
			break;
		}
		break;
	case phasor_type:
		strUnit = _T("°");
		break;
	case fre_type:
		strUnit = _T("Hz");
		break;
	default:
		strUnit = _T("");
		break;
	}
	return strUnit;
}

