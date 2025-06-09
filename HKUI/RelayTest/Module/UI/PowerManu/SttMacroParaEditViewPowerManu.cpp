#include "SttMacroParaEditViewPowerManu.h"
#include "ui_SttMacroParaEditViewManual.h"
#include "../../SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../SttTestCntrFrameAPI.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"
#include "../../Module/XLangResource_Native.h"

#include "../State/ShortCalcuDig.h"
#include "PowerManualEstimateDlg.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewPowerManu* g_pPowerManuTest = NULL;

QSttMacroParaEditViewPowerManu::QSttMacroParaEditViewPowerManu(QWidget *parent) 
{
	setWindowFlags(Qt::FramelessWindowHint);
	m_nManuHarmIndex = 1;
	InitUI();
	//InitLanuage();
	m_bTmtParaChanged = FALSE;
	m_bIsChanging = FALSE;
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;
	
	//memset(m_uiVOL, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));
	memset(m_uiCUR, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));
    //memset(m_uiPOW, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel_power));

	m_strParaFileTitle = g_sLangTxt_componenttest;//"通用序分量试验模板文件";
	m_strParaFilePostfix = "project(*.mntxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("PowerManuTest.mntxml");

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	stt_Frame_InitTestResource();
	m_pManualParas = &m_oManualTest.m_oPowerManuParas;

	OpenTestTestMngrFile(m_strDefaultParaFile);

	CopyBinaryConfig();
	stt_Frame_UpdateToolButtons();

	InitPVView();
	InitParasView();
	InitConnect();

	m_pPowerManualWidget->SetData(g_oSttTestResourceMngr.m_pTestResouce, m_pManualParas, 0);

	if (m_oPV.m_pPUParaWidget)
	{
		m_oPV.m_pPUParaWidget->setMacroType(MACROTYPE_ManualPower);
		m_oPV.m_pPUParaWidget->setHarmIndex(&m_nManuHarmIndex);
		m_oPV.m_pPUParaWidget->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_pManualParas->m_uiVOL,m_pManualParas->m_uiPOW,FALSE);
		m_oPV.m_pPUParaWidget->setMaxMinAndEDVal();
		connect(m_oPV.m_pPUParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	}

    g_pPowerManuTest = this;
 
	SetDatas(NULL);

	stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
	
	stt_Frame_InitPowerWidget(m_pManualParas->m_uiVOL,m_uiCUR);
	setFocusPolicy(Qt::StrongFocus);
}

void QSttMacroParaEditViewPowerManu::InitLanuage()
{
	xlang_SetLangStrToWidget(m_pPowerManualWidget->m_pLock_PushButton, "Manual_Lock", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pPowerManualWidget->m_pChSelect_Label, "Manual_Channel", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pPowerManualWidget->m_pEndValue_Label, "Manual_FinishVal", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pPowerManualWidget->m_pStartValue_Label, "Manual_InitVal", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pPowerManualWidget->m_pChangedType_Label, "Manual_ChangeType", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pPowerManualWidget->m_pStepValue_Label, "Manual_Step", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pPowerManualWidget->m_pStepTime_Label, "Manual_Timer", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pPowerManualWidget->m_pAuto_CheckBox, "Manual_Auto", XLang_Ctrls_QCheckBox);

	xlang_SetLangStrToWidget(m_pPowerManualWidget->m_pBoutGroupBox, "Manual_OutSetting", XLang_Ctrls_QGroupBox);
}

QSttMacroParaEditViewPowerManu::~QSttMacroParaEditViewPowerManu()
{
}

void QSttMacroParaEditViewPowerManu::InitUI()
{
	m_pPowerManualWidget = new QPowerManualWidget(this);
	m_pPowerManualWidget->InitUI();
	setLayout(m_pPowerManualWidget->m_pMainGridLayout);
}

void QSttMacroParaEditViewPowerManu::SendUpdateParameter()
{
	stt_Frame_Ats_UpdateParameter();
}

void QSttMacroParaEditViewPowerManu::CopyBinaryConfig(BOOL b)
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

void QSttMacroParaEditViewPowerManu::InitConnect()
{
	m_pPowerManualWidget->InitConnect();
	connect(m_pPowerManualWidget, SIGNAL(sig_ChannelTableItemValue(QString,float,int,int,bool)),this,SLOT(slot_ChannelTableItemValue(QString,float,int,int,bool)),Qt::UniqueConnection);
	connect(m_pPowerManualWidget->m_pStepTime_LineEdit, SIGNAL(clicked()), this, SLOT(slot_StepTime_LineEdit_Changed()));
	connect(m_pPowerManualWidget->m_pStepValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_StepValue_LineEdit_Changed()));
	//connect(m_pPowerManualWidget->m_pFreq_LineEdit, SIGNAL(clicked()), this, SLOT(slot_Freq_LineEdit_Changed()));
	connect(m_pPowerManualWidget->m_pStartValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_StartValue_LineEdit_Changed()));
	connect(m_pPowerManualWidget->m_pEndValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_EndValue_LineEdit_Changed()));

	connect(m_pPowerManualWidget->m_pStartValue_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StartValue_LineEdit_editingFinished()));
	connect(m_pPowerManualWidget->m_pEndValue_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_EndValue_LineEdit_editingFinished()));
	connect(m_pPowerManualWidget->m_pStepTime_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StepTime_LineEdit_editingFinished()));
	connect(m_pPowerManualWidget->m_pStepValue_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StepValue_LineEdit_editingFinished()));
	//connect(m_pPowerManualWidget->m_pFreq_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_Freq_LineEdit_editingFinished()));
//	connect(m_pPowerManualWidget->m_pChGradientType_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChGradientTypeComboBox_currentIndexChanged(int)));
	connect(m_pPowerManualWidget->m_pChSelect_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChSelectComboBox_currentIndexChanged(int)));
	connect(m_pPowerManualWidget->m_pChangedType_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChangedTypeComboBox_currentIndexChanged(int)));
	connect(m_pPowerManualWidget->m_pAuto_CheckBox, SIGNAL(clicked()), this, SLOT(slot_Auto_CheckBox_clicked()));
	connect(m_pPowerManualWidget->m_pBout_CheckBox[0], SIGNAL(clicked()), this, SLOT(slot_Bout_CheckBox1_clicked()));
	connect(m_pPowerManualWidget->m_pBout_CheckBox[1], SIGNAL(clicked()), this, SLOT(slot_Bout_CheckBox2_clicked()));
	connect(m_pPowerManualWidget->m_pBout_CheckBox[2], SIGNAL(clicked()), this, SLOT(slot_Bout_CheckBox3_clicked()));
	connect(m_pPowerManualWidget->m_pBout_CheckBox[3], SIGNAL(clicked()), this, SLOT(slot_Bout_CheckBox4_clicked()));

	connect(m_pPowerManualWidget->m_pLock_PushButton, SIGNAL(clicked()), this, SLOT(slot_Lock_PushButton_clicked()));
	connect(m_pPowerManualWidget->m_pAdd_PushButton, SIGNAL(clicked()), this, SLOT(slot_Add_PushButton_clicked()));
	connect(m_pPowerManualWidget->m_pMinus_PushButton, SIGNAL(clicked()), this, SLOT(slot_Minus_PushButton_clicked()));
	connect(m_pPowerManualWidget->m_pBinarySet_PushButton, SIGNAL(clicked()), this, SLOT(slot_BinarySetPushButton_clicked()));
	connect(m_pPowerManualWidget->m_pEstimate_PushButton, SIGNAL(clicked()), this, SLOT(slot_EstimatePushButton_clicked()));

	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas()));
}

CSttTestResourceBase* QSttMacroParaEditViewPowerManu::CreateTestResource()
{
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewPowerManu::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
									long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	//yzj 2022-2-21 开始测试前要保持该值为0
	if(!stt_Frame_IsTestStarted())
	{
		m_pManualParas->m_bBinStop = FALSE;
	}

	tmt_PowerManuTest *pTmtManualTest = (tmt_PowerManuTest *)pParas;

	stt_xml_serialize(&pTmtManualTest->m_oPowerManuParas, pMacroParas,nVolRsNum/3,nCurRsNum/3);

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

void QSttMacroParaEditViewPowerManu::OnTestResults(CDataGroup *pResults)
{
	ASSERT(pResults != NULL);

	m_oManualTest.m_nTestState = 1;	//测试完成
}

void QSttMacroParaEditViewPowerManu::InitBinaryInBinaryOutUI()
{
	GlobalSetQcheckState_BinaryOut(m_pPowerManualWidget->m_pBout_CheckBox[0],m_pManualParas->m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_pPowerManualWidget->m_pBout_CheckBox[1],m_pManualParas->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_pPowerManualWidget->m_pBout_CheckBox[2],m_pManualParas->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_pPowerManualWidget->m_pBout_CheckBox[3],m_pManualParas->m_binOut,3);
}

void QSttMacroParaEditViewPowerManu::SetManualOtherParasFont()
{
 	m_pPowerManualWidget->m_pBoutGroupBox->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pChSelect_Label->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pChSelect_ComboBox->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pStartValue_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pStartValue_Label->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pEndValue_Label->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pEndValue_LineEdit->setFont(*g_pSttGlobalFont);
 	//m_pPowerManualWidget->m_pChGradientType_ComboBox->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pStepValue_Label->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pStepTime_Label->setFont(*g_pSttGlobalFont);
	m_pPowerManualWidget->m_pStepValue_LineEdit->setFont(*g_pSttGlobalFont);
 	//m_pPowerManualWidget->m_pFreq_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pStepTime_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pAuto_CheckBox->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pChangedType_Label->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pChangedType_ComboBox->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pBout_CheckBox[0]->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pBout_CheckBox[1]->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pBout_CheckBox[2]->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pBout_CheckBox[3]->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pLock_PushButton->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pAdd_PushButton->setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pMinus_PushButton->setFont(*g_pSttGlobalFont);
 
 	m_pPowerManualWidget->m_pBinarySet_PushButton->setFont(*g_pSttGlobalFont);
	m_pPowerManualWidget->m_pEstimate_PushButton->setFont(*g_pSttGlobalFont);

}

void QSttMacroParaEditViewPowerManu::InitOtherParasUI()
{
	SetManualOtherParasFont();
}


void QSttMacroParaEditViewPowerManu::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();

	m_oPV.m_pPUParaWidget->initUI(stt_GetSttTestResource());
	m_oPV.m_pPUParaWidget->initData();
	m_oPV.m_pPUParaWidget->setMaxMinAndEDVal();

	m_pPowerManualWidget->SetData(stt_GetSttTestResource(), m_pManualParas, 0);
	InitBinaryInBinaryOutUI();
}


void QSttMacroParaEditViewPowerManu::UpdateGoutTab(BOOL bUpdateList)
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

void QSttMacroParaEditViewPowerManu::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
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

void QSttMacroParaEditViewPowerManu::UpdateFT3Tab(BOOL bUpdateList)
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

void QSttMacroParaEditViewPowerManu::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
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

void QSttMacroParaEditViewPowerManu::slot_GooseDataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::slot_FT3DataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::UpdateBinBoutExTab()
{
	//当前页面无拓展开入开出
}

void QSttMacroParaEditViewPowerManu::UpdateManualParas()
{
	m_oPV.m_pPUParaWidget->initData();
	m_pPowerManualWidget->UpdateData();
	
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewPowerManu::ClearResult(PTMT_PARAS_HEAD pHead)
{
	m_oManualTest.m_oPowerManuResult.init();
}

void QSttMacroParaEditViewPowerManu::InitStyle()
{
	((QSttCheckBox*)m_pPowerManualWidget->m_pAuto_CheckBox)->InitStyleSheet();
	((QSttCheckBox*)m_pPowerManualWidget->m_pBout_CheckBox[0])->InitStyleSheet();
	((QSttCheckBox*)m_pPowerManualWidget->m_pBout_CheckBox[1])->InitStyleSheet();
	((QSttCheckBox*)m_pPowerManualWidget->m_pBout_CheckBox[2])->InitStyleSheet();
	((QSttCheckBox*)m_pPowerManualWidget->m_pBout_CheckBox[3])->InitStyleSheet();
	((QSttTabWidget*)m_pPowerManualWidget->m_pPowerManuTab)->InitStyleSheet();
}

void QSttMacroParaEditViewPowerManu::InitParasView()
{
	InitStyle();
	//2023/10/9 wjs 取消对按钮“+”“-”的固定大小
	//m_pPowerManualWidget->m_pAdd_PushButton->setFixedWidth(100);
	//m_pPowerManualWidget->m_pMinus_PushButton->setFixedWidth(100);
	InitOtherParasUI();
	InitBinaryInBinaryOutUI();
}

void QSttMacroParaEditViewPowerManu::InitPVView()
{  
	setFont(*g_pSttGlobalFont);
 	m_pPowerManualWidget->m_pPowerManuTab->setFont(*g_pSttGlobalFont);
 	m_oPV.m_pTabWidget = m_pPowerManualWidget->m_pPowerManuTab;
    m_oPV.InitUI(TMT_MANU_FUNC_TYPE_Common);
}

void QSttMacroParaEditViewPowerManu::slot_SwitchStateChanged()
{
	m_pPowerManualWidget->UpdateData();//更新开出量状态

	if (stt_Frame_IsTestStarted() && !m_pManualParas->m_bLockChanged)
	{
		SendUpdateParameter();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::InitBinStateOnStarting()
{
}


void QSttMacroParaEditViewPowerManu::OnViewTestLink(BOOL b)
{

}


void QSttMacroParaEditViewPowerManu::OnViewTestStart()
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

	m_oPV.m_pPUParaWidget->startInit(bEnableState);
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	stt_Frame_ClearInfoWidget();
	m_pPowerManualWidget->StartInit();

	if(m_pPowerManualWidget->m_pAuto_CheckBox->isChecked() && m_pGooseParaWidget)
	{
		m_pGooseParaWidget->setDisabled(true);
	}

	if(m_pPowerManualWidget->m_pAuto_CheckBox->isChecked() && m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->setDisabled(true);
	}

	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();

	stt_Frame_EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewPowerManu::OnViewTestStop()
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
	
	m_oPV.m_pPUParaWidget->startInit();
	m_pPowerManualWidget->StopInit();
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
	m_oPV.m_pPUParaWidget->UpdateTables();

	m_pPowerManualWidget->m_pBoutGroupBox->setEnabled(true);
	m_pPowerManualWidget->m_pBinarySet_PushButton->setEnabled(true);
	m_pPowerManualWidget->m_pEstimate_PushButton->setEnabled(true);

}

void QSttMacroParaEditViewPowerManu::slot_Lock_PushButton_clicked()
{
	m_pPowerManualWidget->slot_btn_LockClicked();
	
	if (stt_Frame_IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}
	
	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::slot_Add_PushButton_clicked()
{
	if(m_bIsChanging)
	{
		return;
	}

	disconnect(m_oPV.m_pPUParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()));

	m_pPowerManualWidget->slot_btn_AddClicked();
	SetParaChanged();

	connect(m_oPV.m_pPUParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	emit sig_updataParas();
}

void QSttMacroParaEditViewPowerManu::slot_Minus_PushButton_clicked()
{
	if(m_bIsChanging)
	{
		return;
	}

	disconnect(m_oPV.m_pPUParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()));

	m_pPowerManualWidget->slot_btn_MinusClicked();
	SetParaChanged();

	connect(m_oPV.m_pPUParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	emit sig_updataParas();
}

void QSttMacroParaEditViewPowerManu::slot_StartValue_LineEdit_editingFinished()
{
	m_pPowerManualWidget->slot_lne_startChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::slot_EndValue_LineEdit_editingFinished()
{
	m_pPowerManualWidget->slot_lne_endChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::slot_StepTime_LineEdit_editingFinished()
{
	m_pPowerManualWidget->slot_lne_steptimeChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::slot_StepValue_LineEdit_editingFinished()
{
	m_pPowerManualWidget->slot_lne_stepChanged();
	SetParaChanged();
}

//void QSttMacroParaEditViewPowerManu::slot_Freq_LineEdit_editingFinished()
//{
//	m_pPowerManualWidget->slot_Freq_LineEdit_Changed();
//	SetParaChanged();
//	CalPhaseValues();
//}

void QSttMacroParaEditViewPowerManu::slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
{
	m_bIsChanging = TRUE;
	m_oPV.m_pPUParaWidget->setChannelTableItemValue_Sequence(str, fstep, valueFlag, AddOrMinus);
	m_bIsChanging = FALSE;
}

void QSttMacroParaEditViewPowerManu::slot_updateParas()
{
	if (stt_Frame_IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}
	m_oPV.m_pPUParaWidget->setMaxMinAndEDVal();//add wangtao 更新电压和功率的最大最小值
	//stt_Frame_UpdateVectorData();
	//stt_Frame_UpdatePowerData();
    CalPhaseValues();
	
	SetParaChanged();
}                        
void QSttMacroParaEditViewPowerManu::CalPhaseValues() //2023-2-28 chenling
{
	float dA_mag,dA_ang,dB_mag,dB_ang,dC_mag,dC_ang;
	
//	for (int j = 0;j < 3;j++ )
//	{
//		CalABCValues_ByPowerValues_Float(dA_mag,dA_ang,
//			m_pManualParas->m_uiPOW[j].m_fPpower, m_pManualParas->m_uiPOW[j].m_fQpower,m_pManualParas->m_uiVOL[j].Harm[1].fAmp,
//			m_pManualParas->m_uiVOL[j].Harm[1].fAngle);

//		 m_uiCUR[j].Harm[1].fAmp = dA_mag;
//		 m_uiCUR[j].Harm[1].fAngle = dA_ang;

//		//j=j+2;//GetVCurRsNum只有一组，+2没有意义
//	}

	stt_Frame_UpdatePowerData();
	stt_Frame_UpdateVectorData();
}


void QSttMacroParaEditViewPowerManu::slot_Auto_CheckBox_clicked()
{
	m_pPowerManualWidget->slot_cb_AutoClicked();
	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::slot_ChGradientTypeComboBox_currentIndexChanged(int index)
{
	m_pPowerManualWidget->slot_cbb_SelectChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::slot_ChSelectComboBox_currentIndexChanged(int index)
{
	if(m_pPowerManualWidget->m_pChSelect_ComboBox->IsScrolling())
	{
		return;
	}	

	m_pPowerManualWidget->slot_cbb_ChannelChanged(index);

	SetParaChanged();

	int	nGradientChSelect = m_pManualParas->m_nGradientChSelect;

	m_pManualParas->m_nVarIndexType = 0;

	//区分视在功率、有功功率、无功功率
	/*if (POWER_CHANNAL_TYPE_S(nGradientChSelect))
	{
		m_pManualParas->m_nVarIndexType = 0;
	}
	else if (POWER_CHANNAL_TYPE_P(nGradientChSelect))
	{
		m_pManualParas->m_nVarIndexType = 1;
	}
	else if (POWER_CHANNAL_TYPE_Q(nGradientChSelect))
	{
		m_pManualParas->m_nVarIndexType = 2;
	}*/
}

void QSttMacroParaEditViewPowerManu::slot_ChangedTypeComboBox_currentIndexChanged(int index)
{
	if(m_pPowerManualWidget->m_pChangedType_ComboBox->IsScrolling())
	{
		return;
	}	

	m_pPowerManualWidget->slot_cbb_ChangeTypeChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewPowerManu::slot_Bout_CheckBox1_clicked()
{
	m_pPowerManualWidget->slot_ck_Out1StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewPowerManu::slot_Bout_CheckBox2_clicked()
{
	m_pPowerManualWidget->slot_ck_Out2StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewPowerManu::slot_Bout_CheckBox3_clicked()
{
	m_pPowerManualWidget->slot_ck_Out3StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewPowerManu::slot_Bout_CheckBox4_clicked()
{
	m_pPowerManualWidget->slot_ck_Out4StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewPowerManu::ShowReport(CDvmValues *pValues)
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

CString QSttMacroParaEditViewPowerManu::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += STT_ORG_MACRO_PowerManuTest;
	strFile += _T(".");
	strFile += "mntxml";

	return strFile;
}

bool QSttMacroParaEditViewPowerManu::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
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

void QSttMacroParaEditViewPowerManu::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

//判断使用的keyboard类型
void QSttMacroParaEditViewPowerManu::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
{
	//20240801 gongyiping 
	if (pEditLine->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)pEditLine)->IsSetting())
		{
			return;
		}
	}

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();

	if(bIsNor == FALSE)
	{
		QString strVar = m_pPowerManualWidget->m_pChSelect_ComboBox->currentText();
		
		
			if(strVar.contains("U"))
			{
				GetWidgetBoard_DigitData(0,str,pEditLine,this);
			}
			else
			{
				GetWidgetBoard_DigitData(1,str,pEditLine,this);
			}

	}
	else
	{
		GetWidgetBoard_DigitData(4,str,pEditLine,this);
	}
}

void QSttMacroParaEditViewPowerManu::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,TRUE);
	int nInsertPos = 2;
    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	m_pPowerManualWidget->m_pPowerManuTab->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewPowerManu::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,TRUE);
	int nInsertPos = 3;
	
	CString strTitle;
	strTitle=_T("FT3发布");
	m_pPowerManualWidget->m_pPowerManuTab->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewPowerManu::RemoveGooseParaWidget()
{
	if(m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pPowerManualWidget->m_pPowerManuTab->indexOf(m_pGooseParaWidget);
	m_pPowerManualWidget->m_pPowerManuTab->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QSttMacroParaEditViewPowerManu::RemoveFT3OutParaWidget()
{
	if(m_pFT3OutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pPowerManualWidget->m_pPowerManuTab->indexOf(m_pFT3OutParaWidget);
	m_pPowerManualWidget->m_pPowerManuTab->removeTab(nIndex);

	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

bool QSttMacroParaEditViewPowerManu::ExistGooseParaWidget()
{
	int nIndex = m_pPowerManualWidget->m_pPowerManuTab->indexOf(m_pGooseParaWidget);
	return (nIndex>=0);
}

bool QSttMacroParaEditViewPowerManu::ExistFT3OutParaWidget()
{
	int nIndex = m_pPowerManualWidget->m_pPowerManuTab->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewPowerManu::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		m_pPowerManualWidget->m_pPowerManuTab->setTabEnabled(m_pPowerManualWidget->m_pPowerManuTab->indexOf(m_pGooseParaWidget),b);
	}
}

void QSttMacroParaEditViewPowerManu::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		m_pPowerManualWidget->m_pPowerManuTab->setTabEnabled(m_pPowerManualWidget->m_pPowerManuTab->indexOf(m_pFT3OutParaWidget),b);
	}
}

void QSttMacroParaEditViewPowerManu::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pManualParas, &oRead);
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系
	}
	stt_Frame_InitVectorWidget(m_pManualParas->m_uiVOL,m_uiCUR);
    stt_Frame_InitStateMonitor();
    stt_Frame_ClearInfoWidget();
	//stt_Frame_InitPowerWidget(m_pManualParas->m_uiVOL,m_uiCUR);//chenling

	CalPhaseValues();

    UpdateManualParas();
}

void QSttMacroParaEditViewPowerManu::slot_StepTime_LineEdit_Changed()
{
	slot_edit_changed(m_pPowerManualWidget->m_pStepTime_LineEdit, TRUE);
}

void QSttMacroParaEditViewPowerManu::slot_StepValue_LineEdit_Changed()
{
	slot_edit_changed(m_pPowerManualWidget->m_pStepValue_LineEdit, TRUE);
}

//void QSttMacroParaEditViewPowerManu::slot_Freq_LineEdit_Changed()
//{
//	//slot_edit_changed(m_pPowerManualWidget->m_pFreq_LineEdit, TRUE);
//}

void QSttMacroParaEditViewPowerManu::slot_StartValue_LineEdit_Changed()
{
	slot_edit_changed(m_pPowerManualWidget->m_pStartValue_LineEdit, TRUE);
}

void QSttMacroParaEditViewPowerManu::slot_EndValue_LineEdit_Changed()
{
	slot_edit_changed(m_pPowerManualWidget->m_pEndValue_LineEdit, TRUE);
}

void QSttMacroParaEditViewPowerManu::slot_BinarySetPushButton_clicked()
{
	QSttManualBinBoutDlg oManualBinBoutDlg(m_pManualParas->m_binIn,m_pManualParas->m_binOut,
		&m_pManualParas->m_nBinLogic,&m_pManualParas->m_fTrigDelay,
		&m_pManualParas->m_bAuto,this);// zhouhj 临时变量命名从sttManualBinBoutDlg改为oManualBinBoutDlg
	oManualBinBoutDlg.setWindowModality(Qt::WindowModal);//模态窗口

#ifdef _USE_SoftKeyBoard_
    QSoftKeyBoard::AttachObj(&oManualBinBoutDlg);
#endif
// 	oManualBinBoutDlg.exec();
	if (oManualBinBoutDlg.exec() == QDialog::Accepted)
	{
		emit sig_updataParas();	

		//2024-8-1 wuxinyi 新增更新开入量状态灯
		CopyBinaryConfig();
		stt_Frame_UpdateToolButtons();
	}


#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif
}

void QSttMacroParaEditViewPowerManu::slot_EstimatePushButton_clicked()
{
	PowerManualEstimateDlg dlg(m_pManualParas, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}
