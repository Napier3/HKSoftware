#include "SttMacroParaEditViewRemoteMeas.h"
#include "ui_SttMacroParaEditViewManual.h"
#include "../../SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../SttTestCntrFrameAPI.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"
#include "../../Module/XLangResource_Native.h"

#include "../State/ShortCalcuDig.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewRemoteMeas* g_pRemoteMeas = NULL;

QSttMacroParaEditViewRemoteMeas::QSttMacroParaEditViewRemoteMeas(QWidget *parent) 
{
	setWindowFlags(Qt::FramelessWindowHint);
	g_pTheSttTestApp->IinitGbWzdAiTool();
	g_pRemoteMeas = this;

	InitUI();
	InitLanuage();
	m_bTmtParaChanged = FALSE;
	m_bIsChanging = FALSE;
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;
	
	memset(m_uiVOL, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));
	memset(m_uiCUR, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));

	m_strParaFileTitle = "遥测模板文件";
	m_strParaFilePostfix = "project(*.mntxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("RemoteMeasTest.mntxml");

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	stt_Frame_InitTestResource();
	m_pManualParas = &m_oManualTest.m_oManuParas;

	OpenTestTestMngrFile(m_strDefaultParaFile);

	//CopyBinaryConfig();
	stt_Frame_UpdateToolButtons();

	InitParasView();
	InitConnect();

	m_pRemoteMeasWidget->SetData(g_oSttTestResourceMngr.m_pTestResouce, m_pManualParas, 0);
	m_pBtnWidget->setData(m_pManualParas);
	InitIVView();

	SetDatas(NULL);

	stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
	
	stt_Frame_InitPowerWidget(m_uiVOL,m_uiCUR);
	m_nReadCount = 0;
	connect(&m_oRemoteMeasTimer,   SIGNAL(timeout()),    this,   SLOT(slot_Timer()));
	m_oRemoteMeasTimer.start(1000);
}

void QSttMacroParaEditViewRemoteMeas::InitLanuage()
{
	xlang_SetLangStrToWidget(m_pRemoteMeasWidget->m_pLock_PushButton, "Manual_Lock", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pRemoteMeasWidget->m_pChSelect_Label, "Manual_Channel", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pRemoteMeasWidget->m_pEndValue_Label, "Manual_FinishVal", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pRemoteMeasWidget->m_pStartValue_Label, "Manual_InitVal", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pRemoteMeasWidget->m_pChangedType_Label, "Manual_ChangeType", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pRemoteMeasWidget->m_pStepValue_Label, "Manual_Step", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pRemoteMeasWidget->m_pStepTime_Label, "Manual_Timer", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pRemoteMeasWidget->m_pAuto_CheckBox, "Manual_Auto", XLang_Ctrls_QCheckBox);
}

QSttMacroParaEditViewRemoteMeas::~QSttMacroParaEditViewRemoteMeas()
{
}

void QSttMacroParaEditViewRemoteMeas::InitUI()
{
	m_pMainLayout = new QVBoxLayout;

	m_pBtnWidget = new QRemoteMeasRatWidget(this);
	m_pRemoteMeasWidget = new QRemoteMeasWidget(this);
	m_pRemoteMeasWidget->InitUI();

	m_pMainLayout->addWidget(m_pBtnWidget);
	m_pMainLayout->addWidget(m_pRemoteMeasWidget);	
	m_pMainLayout->setSpacing(0);
	setLayout(m_pMainLayout);
}

void QSttMacroParaEditViewRemoteMeas::SendUpdateParameter()
{
	stt_Frame_Ats_UpdateParameter();
}

void QSttMacroParaEditViewRemoteMeas::CopyBinaryConfig(BOOL b)
{
	if(b)
	{
		stt_GetBinaryConfig()->m_nBinLogic = m_pManualParas->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			stt_GetBinaryConfig()->m_binIn[i].nSelect = m_pManualParas->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			stt_GetBinaryConfig()->m_binOut[i].nState = m_pManualParas->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			stt_GetBinaryConfig()->m_binInEx[i].nSelect = m_pManualParas->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			stt_GetBinaryConfig()->m_binOutEx[i].nState = m_pManualParas->m_binOutEx[i].nState;
		}
	}
	else
	{
		m_pManualParas->m_nBinLogic = stt_GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			m_pManualParas->m_binIn[i].nSelect = stt_GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			m_pManualParas->m_binOut[i].nState = stt_GetBinaryConfig()->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pManualParas->m_binInEx[i].nSelect = stt_GetBinaryConfig()->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pManualParas->m_binOutEx[i].nState = stt_GetBinaryConfig()->m_binOutEx[i].nState;
		}
	}
}

void QSttMacroParaEditViewRemoteMeas::InitConnect()
{
	m_pRemoteMeasWidget->InitConnect();
	connect(m_pRemoteMeasWidget, SIGNAL(sig_ChannelTableItemValue(QString,float,int,int,bool)),this,SLOT(slot_ChannelTableItemValue(QString,float,int,int,bool)),Qt::UniqueConnection);
	connect(m_pRemoteMeasWidget->m_pStepTime_LineEdit, SIGNAL(clicked()), this, SLOT(slot_StepTime_LineEdit_Changed()));
	connect(m_pRemoteMeasWidget->m_pStepValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_StepValue_LineEdit_Changed()));
	connect(m_pRemoteMeasWidget->m_pStartValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_StartValue_LineEdit_Changed()));
	connect(m_pRemoteMeasWidget->m_pEndValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_EndValue_LineEdit_Changed()));

	connect(m_pBtnWidget->m_pSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_SelectIndexChanged(int)),Qt::UniqueConnection);
	connect(m_pBtnWidget->m_pVolt1_LineEdit, SIGNAL(clicked()), this, SLOT(slot_Volt1Value_LineEdit_Changed()));
	connect(m_pBtnWidget->m_pVolt2_LineEdit, SIGNAL(clicked()), this, SLOT(slot_Volt2Value_LineEdit_Changed()));
	connect(m_pBtnWidget->m_pCurr1_LineEdit, SIGNAL(clicked()), this, SLOT(slot_Curr1Value_LineEdit_Changed()));
	connect(m_pBtnWidget->m_pCurr2_LineEdit, SIGNAL(clicked()), this, SLOT(slot_Curr2Value_LineEdit_Changed()));
	connect(m_pBtnWidget->m_pZeroVolt1_LineEdit, SIGNAL(clicked()), this, SLOT(slot_ZeroVolt1Value_LineEdit_Changed()));
	connect(m_pBtnWidget->m_pZeroVolt2_LineEdit, SIGNAL(clicked()), this, SLOT(slot_ZeroVolt2Value_LineEdit_Changed()));
	connect(m_pBtnWidget->m_pZeroCurr1_LineEdit, SIGNAL(clicked()), this, SLOT(slot_ZeroCurr1Value_LineEdit_Changed()));
	connect(m_pBtnWidget->m_pZeroCurr2_LineEdit, SIGNAL(clicked()), this, SLOT(slot_ZeroCurr2Value_LineEdit_Changed()));

	connect(m_pRemoteMeasWidget->m_pStartValue_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StartValue_LineEdit_editingFinished()));
	connect(m_pRemoteMeasWidget->m_pEndValue_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_EndValue_LineEdit_editingFinished()));
	connect(m_pRemoteMeasWidget->m_pStepTime_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StepTime_LineEdit_editingFinished()));
	connect(m_pRemoteMeasWidget->m_pStepValue_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StepValue_LineEdit_editingFinished()));
	connect(m_pRemoteMeasWidget->m_pChGradientType_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChGradientTypeComboBox_currentIndexChanged(int)));
	connect(m_pRemoteMeasWidget->m_pChSelect_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChSelectComboBox_currentIndexChanged(int)));
	connect(m_pRemoteMeasWidget->m_pChangedType_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChangedTypeComboBox_currentIndexChanged(int)));
	connect(m_pRemoteMeasWidget->m_pAuto_CheckBox, SIGNAL(clicked()), this, SLOT(slot_Auto_CheckBox_clicked()));

	connect(m_pBtnWidget->m_pVolt1_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_Volt1Value_LineEdit_editingFinished()));
	connect(m_pBtnWidget->m_pVolt2_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_Volt2Value_LineEdit_editingFinished()));
	connect(m_pBtnWidget->m_pCurr1_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_Curr1Value_LineEdit_editingFinished()));
	connect(m_pBtnWidget->m_pCurr2_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_Curr2Value_LineEdit_editingFinished()));
	connect(m_pBtnWidget->m_pZeroVolt1_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_ZeroVolt1Value_LineEdit_editingFinished()));
	connect(m_pBtnWidget->m_pZeroVolt2_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_ZeroVolt2Value_LineEdit_editingFinished()));
	connect(m_pBtnWidget->m_pZeroCurr1_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_ZeroCurr1Value_LineEdit_editingFinished()));
	connect(m_pBtnWidget->m_pZeroCurr2_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_ZeroCurr2Value_LineEdit_editingFinished()));

	connect(m_pRemoteMeasWidget->m_pLock_PushButton, SIGNAL(clicked()), this, SLOT(slot_Lock_PushButton_clicked()));
	connect(m_pRemoteMeasWidget->m_pAdd_PushButton, SIGNAL(clicked()), this, SLOT(slot_Add_PushButton_clicked()));
	connect(m_pRemoteMeasWidget->m_pMinus_PushButton, SIGNAL(clicked()), this, SLOT(slot_Minus_PushButton_clicked()));

	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas()));
}

CSttTestResourceBase* QSttMacroParaEditViewRemoteMeas::CreateTestResource()
{
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewRemoteMeas::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
									long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	//yzj 2022-2-21 开始测试前要保持该值为0
	if(!stt_Frame_IsTestStarted())
	{
		m_pManualParas->m_bBinStop = FALSE;
	}

	tmt_ManualTest *pTmtManualTest = (tmt_ManualTest *)pParas;

	stt_xml_serialize(&pTmtManualTest->m_oManuParas, pMacroParas,nVolRsNum,nCurRsNum);

	if (bHasGoosePub)
	{
		CIecCfgGoutDatas *pGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr()/*m_listGoosePub.at(0)*/;
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

void QSttMacroParaEditViewRemoteMeas::OnTestResults(CDataGroup *pResults)
{
	ASSERT(pResults != NULL);

	m_oManualTest.m_nTestState = 1;	//测试完成
}

void QSttMacroParaEditViewRemoteMeas::SetManualOtherParasFont()
{
 	m_pRemoteMeasWidget->m_pChSelect_Label->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pChSelect_ComboBox->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pStartValue_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pStartValue_Label->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pEndValue_Label->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pEndValue_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pChGradientType_ComboBox->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pStepValue_Label->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pStepTime_Label->setFont(*g_pSttGlobalFont);
	m_pRemoteMeasWidget->m_pStepValue_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pStepTime_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pAuto_CheckBox->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pChangedType_Label->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pChangedType_ComboBox->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pLock_PushButton->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pAdd_PushButton->setFont(*g_pSttGlobalFont);
 	m_pRemoteMeasWidget->m_pMinus_PushButton->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewRemoteMeas::InitOtherParasUI()
{
	SetManualOtherParasFont();
}


void QSttMacroParaEditViewRemoteMeas::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();

	m_pBtnWidget->m_pUIParaWidget->initUI(stt_GetSttTestResource());	
	m_pBtnWidget->m_pUIParaWidget->setMaxMinAndEDVal();//系统参数输出类型修改后再初始化,顺序调整
	m_pBtnWidget->m_pUIParaWidget->initData();
	m_pRemoteMeasWidget->SetData(stt_GetSttTestResource(), m_pManualParas, 0);
}

void QSttMacroParaEditViewRemoteMeas::slot_GooseDataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_FT3DataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::UpdateBinBoutExTab()
{
	//当前页面无拓展开入开出
}

void QSttMacroParaEditViewRemoteMeas::UpdateManualParas()
{
	m_pBtnWidget->m_pUIParaWidget->initData();
	m_pRemoteMeasWidget->UpdateData();
	
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewRemoteMeas::ClearResult(PTMT_PARAS_HEAD pHead)
{
	m_oManualTest.m_oManuResult.init();
}

void QSttMacroParaEditViewRemoteMeas::InitStyle()
{
	((QSttCheckBox*)m_pRemoteMeasWidget->m_pAuto_CheckBox)->InitStyleSheet();
	//((QSttTabWidget*)m_pRemoteMeasWidget->m_pTelemeterTab)->InitStyleSheet();
}

void QSttMacroParaEditViewRemoteMeas::InitParasView()
{
	InitStyle();
	//2023/10/9 wjs 取消对按钮“+”“-”的固定大小
	//m_pSequenceManualWidget->m_pAdd_PushButton->setFixedWidth(100);
	//m_pSequenceManualWidget->m_pMinus_PushButton->setFixedWidth(100);
	InitOtherParasUI();
}

void QSttMacroParaEditViewRemoteMeas::InitIVView()
{  
	//setFont(*g_pSttGlobalFont);
 	//m_pRemoteMeasWidget->m_pTelemeterTab->setFont(*g_pSttGlobalFont);
 	//m_oIV.m_pTabWidget = m_pRemoteMeasWidget->m_pTelemeterTab;
     //m_oIV.InitUI();
	m_pBtnWidget->m_pUIParaWidget->setMacroType(MACROTYPE_RemoteMeas);
	m_pBtnWidget->m_pUIParaWidget->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
	m_pBtnWidget->m_pUIParaWidget->setMaxMinAndEDVal();
	connect(m_pBtnWidget->m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);

}

void QSttMacroParaEditViewRemoteMeas::slot_SwitchStateChanged()
{
	m_pRemoteMeasWidget->UpdateData();//更新开出量状态

	if (stt_Frame_IsTestStarted() && !m_pManualParas->m_bLockChanged)
	{
		SendUpdateParameter();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::InitBinStateOnStarting()
{
}

void QSttMacroParaEditViewRemoteMeas::OnViewTestLink(BOOL b)
{

}

void QSttMacroParaEditViewRemoteMeas::OnViewTestStart()
{
	InitBinStateOnStarting();
	BOOL bEnableState = TRUE;
	int nGooseParasUI_State = STT_UI_RUN_STATE_StateTested_Editable;

	if ((m_pManualParas->m_bAuto))
	{
		nGooseParasUI_State = STT_UI_RUN_STATE_StateTested_NotEditable;
		bEnableState = FALSE;
	}

	if (m_pGooseParaWidget != NULL)
	{
		m_pGooseParaWidget->SetRunState(nGooseParasUI_State);
		m_pGooseParaWidget->SetGooseDisabled(!bEnableState);
	}
	if (m_pFT3OutParaWidget != NULL)
	{
		m_pFT3OutParaWidget->SetRunState(nGooseParasUI_State);
		m_pFT3OutParaWidget->SetGooseDisabled(!bEnableState);
	}

	m_pBtnWidget->m_pUIParaWidget->startInit(bEnableState);
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	stt_Frame_ClearInfoWidget();
	m_pRemoteMeasWidget->StartInit();

	if(m_pRemoteMeasWidget->m_pAuto_CheckBox->isChecked() && m_pGooseParaWidget)
	{
		m_pGooseParaWidget->setDisabled(true);
	}

	if(m_pRemoteMeasWidget->m_pAuto_CheckBox->isChecked() && m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->setDisabled(true);
	}

	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();

	stt_Frame_EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewRemoteMeas::OnViewTestStop()
{
	if (m_pGooseParaWidget)
	{
		m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_Stoped);
		m_pGooseParaWidget->SetGooseDisabled(FALSE);
	}
	if (m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_Stoped);
		m_pFT3OutParaWidget->SetGooseDisabled(FALSE);
	}
	
	m_pBtnWidget->m_pUIParaWidget->startInit();
	m_pRemoteMeasWidget->StopInit();
	if(m_pGooseParaWidget)
	{
		m_pGooseParaWidget->setDisabled(false);
	}

	if(m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->setDisabled(false);
	}
	stt_Frame_StopStateMonitor();
	stt_Frame_StopVectorWidget(false);//20220628 zhouhj 暂时改为不更新界面参数,防止界面参数被修改为0
	stt_Frame_StopPowerWidget(false);
	m_pBtnWidget->m_pUIParaWidget->UpdateTables();
}

void QSttMacroParaEditViewRemoteMeas::slot_Lock_PushButton_clicked()
{
	m_pRemoteMeasWidget->slot_btn_LockClicked();
	
	if (stt_Frame_IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}
	
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_Add_PushButton_clicked()
{
	if(m_bIsChanging)
	{
		return;
	}

	disconnect(m_pBtnWidget->m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()));

	m_pRemoteMeasWidget->slot_btn_AddClicked();
	SetParaChanged();

	connect(m_pBtnWidget->m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	emit sig_updataParas();
}

void QSttMacroParaEditViewRemoteMeas::slot_Minus_PushButton_clicked()
{
	if(m_bIsChanging)
	{
		return;
	}

	disconnect(m_pBtnWidget->m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()));

	m_pRemoteMeasWidget->slot_btn_MinusClicked();
	SetParaChanged();

	connect(m_pBtnWidget->m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	emit sig_updataParas();
}

void QSttMacroParaEditViewRemoteMeas::slot_StartValue_LineEdit_editingFinished()
{
	m_pRemoteMeasWidget->slot_lne_startChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_EndValue_LineEdit_editingFinished()
{
	m_pRemoteMeasWidget->slot_lne_endChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_StepTime_LineEdit_editingFinished()
{
	m_pRemoteMeasWidget->slot_lne_steptimeChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_StepValue_LineEdit_editingFinished()
{
	m_pRemoteMeasWidget->slot_lne_stepChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_Volt1Value_LineEdit_editingFinished()
{
	m_pBtnWidget->slot_lne_Volt1Changed();
	m_pBtnWidget->m_pUIParaWidget->initData();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_Volt2Value_LineEdit_editingFinished()
{
	m_pBtnWidget->slot_lne_Volt2Changed();
	m_pBtnWidget->m_pUIParaWidget->initData();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_Curr1Value_LineEdit_editingFinished()
{
	m_pBtnWidget->slot_lne_Curr1Changed();
	m_pBtnWidget->m_pUIParaWidget->initData();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_Curr2Value_LineEdit_editingFinished()
{
	m_pBtnWidget->slot_lne_Curr2Changed();
	m_pBtnWidget->m_pUIParaWidget->initData();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_ZeroVolt1Value_LineEdit_editingFinished()
{
	m_pBtnWidget->slot_lne_ZeroVolt1Changed();
	m_pBtnWidget->m_pUIParaWidget->initData();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_ZeroVolt2Value_LineEdit_editingFinished()
{
	m_pBtnWidget->slot_lne_ZeroVolt2Changed();
	m_pBtnWidget->m_pUIParaWidget->initData();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_ZeroCurr1Value_LineEdit_editingFinished()
{
	m_pBtnWidget->slot_lne_ZeroCurr1Changed();
	m_pBtnWidget->m_pUIParaWidget->initData();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_ZeroCurr2Value_LineEdit_editingFinished()
{
	m_pBtnWidget->slot_lne_ZeroCurr2Changed();
	m_pBtnWidget->m_pUIParaWidget->initData();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
{
	m_bIsChanging = TRUE;
	m_pBtnWidget->m_pUIParaWidget->setChannelTableItemValue(str, fstep, valueFlag, AddOrMinus);
	m_pBtnWidget->m_pUIParaWidget->initData();
	m_bIsChanging = FALSE;
}

void QSttMacroParaEditViewRemoteMeas::slot_updateParas()
{
	if (stt_Frame_IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}

	stt_Frame_UpdateVectorData();
	stt_Frame_UpdatePowerData();
	
	SetParaChanged();
}                        

void QSttMacroParaEditViewRemoteMeas::slot_Auto_CheckBox_clicked()
{
	m_pRemoteMeasWidget->slot_cb_AutoClicked();
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_ChGradientTypeComboBox_currentIndexChanged(int index)
{
	if(m_pRemoteMeasWidget->m_pChGradientType_ComboBox->IsScrolling())
	{
		return;
	}	

	m_pRemoteMeasWidget->slot_cbb_SelectChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::slot_ChSelectComboBox_currentIndexChanged(int index)
{
	if(m_pRemoteMeasWidget->m_pChSelect_ComboBox->IsScrolling())
	{
		return;
	}	

	m_pRemoteMeasWidget->slot_cbb_ChannelChanged(index);

	SetParaChanged();

	int	nGradientChSelect = m_pManualParas->m_nGradientChSelect;

	if(CHANNAL_TYPE_I(nGradientChSelect))
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

void QSttMacroParaEditViewRemoteMeas::slot_ChangedTypeComboBox_currentIndexChanged(int index)
{
	if(m_pRemoteMeasWidget->m_pChangedType_ComboBox->IsScrolling())
	{
		return;
	}	

	m_pRemoteMeasWidget->slot_cbb_ChangeTypeChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewRemoteMeas::ShowReport(CDvmValues *pValues)
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

CString QSttMacroParaEditViewRemoteMeas::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += STT_ORG_MACRO_RemoteMeasTest;
	strFile += _T(".");
	strFile += "mntxml";

	return strFile;
}

bool QSttMacroParaEditViewRemoteMeas::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
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

void QSttMacroParaEditViewRemoteMeas::UpdateDeviceModelRef()
{
	disconnect(m_pBtnWidget->m_pSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_SelectIndexChanged(int)));
	m_pBtnWidget->initInterSelectData();
	connect(m_pBtnWidget->m_pSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_SelectIndexChanged(int)),Qt::UniqueConnection);

}

void QSttMacroParaEditViewRemoteMeas::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

//判断使用的keyboard类型
void QSttMacroParaEditViewRemoteMeas::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
{
	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();

	if(bIsNor == FALSE)
	{
		QString strVar = m_pRemoteMeasWidget->m_pChSelect_ComboBox->currentText();
		int nIdx = m_pRemoteMeasWidget->m_pChGradientType_ComboBox->currentIndex();
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
}

void QSttMacroParaEditViewRemoteMeas::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pManualParas, &oRead);
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系
	}
	stt_Frame_InitVectorWidget(m_uiVOL,m_uiCUR);
    stt_Frame_InitStateMonitor();
    stt_Frame_ClearInfoWidget();
	stt_Frame_InitPowerWidget(m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);//chenling


    UpdateManualParas();
}

void QSttMacroParaEditViewRemoteMeas::slot_StepTime_LineEdit_Changed()
{
	slot_edit_changed(m_pRemoteMeasWidget->m_pStepTime_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_StepValue_LineEdit_Changed()
{
	slot_edit_changed(m_pRemoteMeasWidget->m_pStepValue_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_StartValue_LineEdit_Changed()
{
	slot_edit_changed(m_pRemoteMeasWidget->m_pStartValue_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_EndValue_LineEdit_Changed()
{
	slot_edit_changed(m_pRemoteMeasWidget->m_pEndValue_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_Volt1Value_LineEdit_Changed()
{
	slot_edit_changed(m_pBtnWidget->m_pVolt1_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_Volt2Value_LineEdit_Changed()
{
	slot_edit_changed(m_pBtnWidget->m_pVolt2_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_Curr1Value_LineEdit_Changed()
{
	slot_edit_changed(m_pBtnWidget->m_pCurr1_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_Curr2Value_LineEdit_Changed()
{
	slot_edit_changed(m_pBtnWidget->m_pCurr2_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_ZeroVolt1Value_LineEdit_Changed()
{
	slot_edit_changed(m_pBtnWidget->m_pZeroVolt1_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_ZeroVolt2Value_LineEdit_Changed()
{
	slot_edit_changed(m_pBtnWidget->m_pZeroVolt2_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_ZeroCurr1Value_LineEdit_Changed()
{
	slot_edit_changed(m_pBtnWidget->m_pZeroCurr1_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_ZeroCurr2Value_LineEdit_Changed()
{
	slot_edit_changed(m_pBtnWidget->m_pZeroCurr2_LineEdit, TRUE);
}

void QSttMacroParaEditViewRemoteMeas::slot_SelectIndexChanged(int nIndex)
{
	//if(m_pBtnWidget->m_pSelect_ComboBox->IsScrolling())
	//{
	//	return;
	//}

	UpdateManualParas();

// 	CExBaseList *pDataset = (CExBaseList*)m_pBtnWidget->m_pSelect_ComboBox->GetCurrSelObject();
// 
// 	if (pDataset == NULL)
// 	{
// 		m_strAinDatasetPath = "";
// 		return;
// 	}
// 
// 	CDvmLogicDevice *pLogDev = (CDvmLogicDevice*)pDataset;
}

void QSttMacroParaEditViewRemoteMeas::slot_Timer()
{
	CExBaseList *pDataset = (CExBaseList*)m_pBtnWidget->m_pSelect_ComboBox->GetCurrSelObject();

	if (pDataset == NULL)
	{
		return;
	}

	if (g_theTestCntrFrame->m_pEngineClientWidget == NULL)
	{
		return;
	}

	if (!g_theTestCntrFrame->m_pEngineClientWidget->IsConnectSuccessful())
	{
		return;
	}

	if (!g_theTestCntrFrame->m_pEngineClientWidget->IsRunProcedureFinished())
	{
		return;
	}

	if (g_theTestCntrFrame->m_pActiveWidget != this)
	{
		return;
	}

	m_nReadCount++;

	if (m_nReadCount%5 == 0)//每5秒读取一次遥测数据
	{
		g_theTestCntrFrame->m_pEngineClientWidget->ReadAin(pDataset->m_strID);//20240307读数据刷新紊乱
	}

	if ((m_pBtnWidget->m_pUIParaWidget != NULL) && (m_pBtnWidget != NULL))
	{
		m_pBtnWidget->m_pUIParaWidget->initData();
	}

	if (m_nReadCount >= 1000000)//超过一定次数清零
	{
		m_nReadCount = 0;
	}
}
