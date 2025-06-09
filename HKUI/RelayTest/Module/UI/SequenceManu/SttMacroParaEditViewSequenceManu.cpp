#include "SttMacroParaEditViewSequenceManu.h"
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
#include "SequenceManualEstimateDlg.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewSequenceManu* g_pSequenceManuTest = NULL;

QSttMacroParaEditViewSequenceManu::QSttMacroParaEditViewSequenceManu(QWidget *parent) 
{
	setWindowFlags(Qt::FramelessWindowHint);
	m_nManuHarmIndex = 1;
	InitUI();
	InitLanuage();
	m_bTmtParaChanged = FALSE;
	m_bIsChanging = FALSE;
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;
	
	memset(m_uiVOL, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));
	memset(m_uiCUR, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));

	m_strParaFileTitle = g_sLangTxt_componenttest;//"通用序分量试验模板文件";
	m_strParaFilePostfix = "project(*.mntxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("SequenceManuTest.mntxml");

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	stt_Frame_InitTestResource();
	m_pManualParas = &m_oManualTest.m_oSequenceManuParas;

	OpenTestTestMngrFile(m_strDefaultParaFile);

	CopyBinaryConfig();
	stt_Frame_UpdateToolButtons();

	InitIVView();
	InitParasView();
	InitConnect();

	m_pSequenceManualWidget->SetData(g_oSttTestResourceMngr.m_pTestResouce, m_pManualParas, 0);

	if (m_oIV.m_pUIParaWidget)
	{
		m_oIV.m_pUIParaWidget->setMacroType(MACROTYPE_ManualSequence);
		m_oIV.m_pUIParaWidget->setHarmIndex(&m_nManuHarmIndex);
		m_oIV.m_pUIParaWidget->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR,FALSE);
		m_oIV.m_pUIParaWidget->setMaxMinAndEDVal();
		connect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	}

     g_pSequenceManuTest = this;
 
	SetDatas(NULL);

	stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
	
	stt_Frame_InitPowerWidget(m_uiVOL,m_uiCUR);
	setFocusPolicy(Qt::StrongFocus);
}

void QSttMacroParaEditViewSequenceManu::InitLanuage()
{
	xlang_SetLangStrToWidget(m_pSequenceManualWidget->m_pLock_PushButton, "Manual_Lock", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pSequenceManualWidget->m_pChSelect_Label, "Manual_Channel", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pSequenceManualWidget->m_pEndValue_Label, "Manual_FinishVal", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pSequenceManualWidget->m_pStartValue_Label, "Manual_InitVal", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pSequenceManualWidget->m_pChangedType_Label, "Manual_ChangeType", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pSequenceManualWidget->m_pStepValue_Label, "Manual_Step", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pSequenceManualWidget->m_pStepTime_Label, "Manual_Timer", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pSequenceManualWidget->m_pAuto_CheckBox, "Manual_Auto", XLang_Ctrls_QCheckBox);

	xlang_SetLangStrToWidget(m_pSequenceManualWidget->m_pBoutGroupBox, "Manual_OutSetting", XLang_Ctrls_QGroupBox);
}

QSttMacroParaEditViewSequenceManu::~QSttMacroParaEditViewSequenceManu()
{
}

void QSttMacroParaEditViewSequenceManu::InitUI()
{
	m_pSequenceManualWidget = new QSequenceManualWidget(this);
	m_pSequenceManualWidget->InitUI();
	setLayout(m_pSequenceManualWidget->m_pMainGridLayout);
}

void QSttMacroParaEditViewSequenceManu::SendUpdateParameter()
{
	stt_Frame_Ats_UpdateParameter();
}

void QSttMacroParaEditViewSequenceManu::CopyBinaryConfig(BOOL b)
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

void QSttMacroParaEditViewSequenceManu::InitConnect()
{
	m_pSequenceManualWidget->InitConnect();
	connect(m_pSequenceManualWidget, SIGNAL(sig_ChannelTableItemValue(QString,float,int,int,bool)),this,SLOT(slot_ChannelTableItemValue(QString,float,int,int,bool)),Qt::UniqueConnection);
	connect(m_pSequenceManualWidget->m_pStepTime_LineEdit, SIGNAL(clicked()), this, SLOT(slot_StepTime_LineEdit_Changed()));
	connect(m_pSequenceManualWidget->m_pStepValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_StepValue_LineEdit_Changed()));
	connect(m_pSequenceManualWidget->m_pFreq_LineEdit, SIGNAL(clicked()), this, SLOT(slot_Freq_LineEdit_Changed()));
	connect(m_pSequenceManualWidget->m_pStartValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_StartValue_LineEdit_Changed()));
	connect(m_pSequenceManualWidget->m_pEndValue_LineEdit, SIGNAL(clicked()), this, SLOT(slot_EndValue_LineEdit_Changed()));

	connect(m_pSequenceManualWidget->m_pStartValue_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StartValue_LineEdit_editingFinished()));
	connect(m_pSequenceManualWidget->m_pEndValue_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_EndValue_LineEdit_editingFinished()));
	connect(m_pSequenceManualWidget->m_pStepTime_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StepTime_LineEdit_editingFinished()));
	connect(m_pSequenceManualWidget->m_pStepValue_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StepValue_LineEdit_editingFinished()));
	connect(m_pSequenceManualWidget->m_pFreq_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_Freq_LineEdit_editingFinished()));
	connect(m_pSequenceManualWidget->m_pChGradientType_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChGradientTypeComboBox_currentIndexChanged(int)));
	connect(m_pSequenceManualWidget->m_pChSelect_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChSelectComboBox_currentIndexChanged(int)));
	connect(m_pSequenceManualWidget->m_pChangedType_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChangedTypeComboBox_currentIndexChanged(int)));
	connect(m_pSequenceManualWidget->m_pAuto_CheckBox, SIGNAL(clicked()), this, SLOT(slot_Auto_CheckBox_clicked()));
	connect(m_pSequenceManualWidget->m_pBout_CheckBox[0], SIGNAL(clicked()), this, SLOT(slot_Bout_CheckBox1_clicked()));
	connect(m_pSequenceManualWidget->m_pBout_CheckBox[1], SIGNAL(clicked()), this, SLOT(slot_Bout_CheckBox2_clicked()));
	connect(m_pSequenceManualWidget->m_pBout_CheckBox[2], SIGNAL(clicked()), this, SLOT(slot_Bout_CheckBox3_clicked()));
	connect(m_pSequenceManualWidget->m_pBout_CheckBox[3], SIGNAL(clicked()), this, SLOT(slot_Bout_CheckBox4_clicked()));

	connect(m_pSequenceManualWidget->m_pLock_PushButton, SIGNAL(clicked()), this, SLOT(slot_Lock_PushButton_clicked()));
	connect(m_pSequenceManualWidget->m_pAdd_PushButton, SIGNAL(clicked()), this, SLOT(slot_Add_PushButton_clicked()));
	connect(m_pSequenceManualWidget->m_pMinus_PushButton, SIGNAL(clicked()), this, SLOT(slot_Minus_PushButton_clicked()));
	connect(m_pSequenceManualWidget->m_pBinarySet_PushButton, SIGNAL(clicked()), this, SLOT(slot_BinarySetPushButton_clicked()));
	connect(m_pSequenceManualWidget->m_pEstimate_PushButton, SIGNAL(clicked()), this, SLOT(slot_EstimatePushButton_clicked()));

	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas()));
}

CSttTestResourceBase* QSttMacroParaEditViewSequenceManu::CreateTestResource()
{
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewSequenceManu::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
									long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	//yzj 2022-2-21 开始测试前要保持该值为0
	if(!stt_Frame_IsTestStarted())
	{
		m_pManualParas->m_bBinStop = FALSE;
	}

	tmt_SequenceManuTest *pTmtManualTest = (tmt_SequenceManuTest *)pParas;

	stt_xml_serialize(&pTmtManualTest->m_oSequenceManuParas, pMacroParas,nVolRsNum/3,nCurRsNum/3);

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

void QSttMacroParaEditViewSequenceManu::OnTestResults(CDataGroup *pResults)
{
	ASSERT(pResults != NULL);

	m_oManualTest.m_nTestState = 1;	//测试完成
}

void QSttMacroParaEditViewSequenceManu::InitBinaryInBinaryOutUI()
{
	GlobalSetQcheckState_BinaryOut(m_pSequenceManualWidget->m_pBout_CheckBox[0],m_pManualParas->m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_pSequenceManualWidget->m_pBout_CheckBox[1],m_pManualParas->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_pSequenceManualWidget->m_pBout_CheckBox[2],m_pManualParas->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_pSequenceManualWidget->m_pBout_CheckBox[3],m_pManualParas->m_binOut,3);
}

void QSttMacroParaEditViewSequenceManu::SetManualOtherParasFont()
{
 	m_pSequenceManualWidget->m_pBoutGroupBox->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pChSelect_Label->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pChSelect_ComboBox->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pStartValue_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pStartValue_Label->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pEndValue_Label->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pEndValue_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pChGradientType_ComboBox->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pStepValue_Label->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pStepTime_Label->setFont(*g_pSttGlobalFont);
	m_pSequenceManualWidget->m_pStepValue_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pFreq_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pStepTime_LineEdit->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pAuto_CheckBox->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pChangedType_Label->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pChangedType_ComboBox->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pBout_CheckBox[0]->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pBout_CheckBox[1]->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pBout_CheckBox[2]->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pBout_CheckBox[3]->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pLock_PushButton->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pAdd_PushButton->setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pMinus_PushButton->setFont(*g_pSttGlobalFont);
 
 	m_pSequenceManualWidget->m_pBinarySet_PushButton->setFont(*g_pSttGlobalFont);
	m_pSequenceManualWidget->m_pEstimate_PushButton->setFont(*g_pSttGlobalFont);

}

void QSttMacroParaEditViewSequenceManu::InitOtherParasUI()
{
	SetManualOtherParasFont();
}


void QSttMacroParaEditViewSequenceManu::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();

	m_oIV.m_pUIParaWidget->initUI(stt_GetSttTestResource());
	m_oIV.m_pUIParaWidget->initData();
	m_oIV.m_pUIParaWidget->setMaxMinAndEDVal();

	m_pSequenceManualWidget->SetData(stt_GetSttTestResource(), m_pManualParas, 0);
	InitBinaryInBinaryOutUI();
}


void QSttMacroParaEditViewSequenceManu::UpdateGoutTab(BOOL bUpdateList)
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

void QSttMacroParaEditViewSequenceManu::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
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

void QSttMacroParaEditViewSequenceManu::UpdateFT3Tab(BOOL bUpdateList)
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

void QSttMacroParaEditViewSequenceManu::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
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

void QSttMacroParaEditViewSequenceManu::slot_GooseDataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_FT3DataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::UpdateBinBoutExTab()
{
	//当前页面无拓展开入开出
}

void QSttMacroParaEditViewSequenceManu::UpdateManualParas()
{
	m_oIV.m_pUIParaWidget->initData();
	m_pSequenceManualWidget->UpdateData();
	
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewSequenceManu::ClearResult(PTMT_PARAS_HEAD pHead)
{
	m_oManualTest.m_oSequenceManuResult.init();
}

void QSttMacroParaEditViewSequenceManu::InitStyle()
{
	((QSttCheckBox*)m_pSequenceManualWidget->m_pAuto_CheckBox)->InitStyleSheet();
	((QSttCheckBox*)m_pSequenceManualWidget->m_pBout_CheckBox[0])->InitStyleSheet();
	((QSttCheckBox*)m_pSequenceManualWidget->m_pBout_CheckBox[1])->InitStyleSheet();
	((QSttCheckBox*)m_pSequenceManualWidget->m_pBout_CheckBox[2])->InitStyleSheet();
	((QSttCheckBox*)m_pSequenceManualWidget->m_pBout_CheckBox[3])->InitStyleSheet();
	((QSttTabWidget*)m_pSequenceManualWidget->m_pSequenceManuTab)->InitStyleSheet();
}

void QSttMacroParaEditViewSequenceManu::InitParasView()
{
	InitStyle();
	//2023/10/9 wjs 取消对按钮“+”“-”的固定大小
	//m_pSequenceManualWidget->m_pAdd_PushButton->setFixedWidth(100);
	//m_pSequenceManualWidget->m_pMinus_PushButton->setFixedWidth(100);
	InitOtherParasUI();
	InitBinaryInBinaryOutUI();
}

void QSttMacroParaEditViewSequenceManu::InitIVView()
{  
	setFont(*g_pSttGlobalFont);
 	m_pSequenceManualWidget->m_pSequenceManuTab->setFont(*g_pSttGlobalFont);
 	m_oIV.m_pTabWidget = m_pSequenceManualWidget->m_pSequenceManuTab;
     m_oIV.InitUI(TMT_MANU_FUNC_TYPE_Common);
}

void QSttMacroParaEditViewSequenceManu::slot_SwitchStateChanged()
{
	m_pSequenceManualWidget->UpdateData();//更新开出量状态

	if (stt_Frame_IsTestStarted() && !m_pManualParas->m_bLockChanged)
	{
		SendUpdateParameter();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::InitBinStateOnStarting()
{
}


void QSttMacroParaEditViewSequenceManu::OnViewTestLink(BOOL b)
{

}


void QSttMacroParaEditViewSequenceManu::OnViewTestStart()
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

	m_oIV.m_pUIParaWidget->startInit(bEnableState);
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	stt_Frame_ClearInfoWidget();
	m_pSequenceManualWidget->StartInit();

	if(m_pSequenceManualWidget->m_pAuto_CheckBox->isChecked() && m_pGooseParaWidget)
	{
		m_pGooseParaWidget->setDisabled(true);
	}

	if(m_pSequenceManualWidget->m_pAuto_CheckBox->isChecked() && m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->setDisabled(true);
	}

	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();

	stt_Frame_EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewSequenceManu::OnViewTestStop()
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
	
	m_oIV.m_pUIParaWidget->startInit();
	m_pSequenceManualWidget->StopInit();
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
	m_oIV.m_pUIParaWidget->UpdateTables();

	m_pSequenceManualWidget->m_pBoutGroupBox->setEnabled(true);
	m_pSequenceManualWidget->m_pBinarySet_PushButton->setEnabled(true);
	m_pSequenceManualWidget->m_pEstimate_PushButton->setEnabled(true);

}

void QSttMacroParaEditViewSequenceManu::slot_Lock_PushButton_clicked()
{
	m_pSequenceManualWidget->slot_btn_LockClicked();
	
	if (stt_Frame_IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}
	
	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_Add_PushButton_clicked()
{
	if(m_bIsChanging)
	{
		return;
	}

	disconnect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()));

	m_pSequenceManualWidget->slot_btn_AddClicked();
	SetParaChanged();

	connect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	emit sig_updataParas();
}

void QSttMacroParaEditViewSequenceManu::slot_Minus_PushButton_clicked()
{
	if(m_bIsChanging)
	{
		return;
	}

	disconnect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()));

	m_pSequenceManualWidget->slot_btn_MinusClicked();
	SetParaChanged();

	connect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	emit sig_updataParas();
}

void QSttMacroParaEditViewSequenceManu::slot_StartValue_LineEdit_editingFinished()
{
	m_pSequenceManualWidget->slot_lne_startChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_EndValue_LineEdit_editingFinished()
{
	m_pSequenceManualWidget->slot_lne_endChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_StepTime_LineEdit_editingFinished()
{
	m_pSequenceManualWidget->slot_lne_steptimeChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_StepValue_LineEdit_editingFinished()
{
	m_pSequenceManualWidget->slot_lne_stepChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_Freq_LineEdit_editingFinished()
{
	m_pSequenceManualWidget->slot_Freq_LineEdit_Changed();
	SetParaChanged();
	CalPhaseValues();
}

void QSttMacroParaEditViewSequenceManu::slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
{
	m_bIsChanging = TRUE;
	m_oIV.m_pUIParaWidget->setChannelTableItemValue_Sequence(str, fstep, valueFlag, AddOrMinus);
	m_bIsChanging = FALSE;
}

void QSttMacroParaEditViewSequenceManu::slot_updateParas()
{
	if (stt_Frame_IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}

	//stt_Frame_UpdateVectorData();
	//stt_Frame_UpdatePowerData();
    CalPhaseValues();
	
	SetParaChanged();
}                        
void QSttMacroParaEditViewSequenceManu::CalPhaseValues() //2023-2-28 chenling
{
	float dA_mag,dA_ang,dB_mag,dB_ang,dC_mag,dC_ang;

	for (int i = 0;i < m_pSequenceManualWidget->m_pTestResource->GetVolRsNum();i++ )
	{
		CalABCValues_BySequenceValues_Float(dA_mag,dA_ang,dB_mag,dB_ang,dC_mag,dC_ang
			,m_pManualParas->m_uiVOL[i].Harm[1].fAmp,m_pManualParas->m_uiVOL[i].Harm[1].fAngle
			,m_pManualParas->m_uiVOL[i+1].Harm[1].fAmp,m_pManualParas->m_uiVOL[i+1].Harm[1].fAngle
			,m_pManualParas->m_uiVOL[i+2].Harm[1].fAmp,m_pManualParas->m_uiVOL[i+2].Harm[1].fAngle);
			
		m_uiVOL[i].Harm[1].fAmp = dA_mag;
		m_uiVOL[i].Harm[1].fAngle = dA_ang;
		m_uiVOL[i+1].Harm[1].fAmp = dB_mag;
		m_uiVOL[i+1].Harm[1].fAngle = dB_ang;
		m_uiVOL[i+2].Harm[1].fAmp = dC_mag;
		m_uiVOL[i+2].Harm[1].fAngle = dC_ang;
		
		m_uiVOL[i].Harm[1].fFreq=m_pSequenceManualWidget->m_pFreq_LineEdit->text().toFloat();
		m_uiVOL[i+1].Harm[1].fFreq=m_pSequenceManualWidget->m_pFreq_LineEdit->text().toFloat();
		m_uiVOL[i+2].Harm[1].fFreq=m_pSequenceManualWidget->m_pFreq_LineEdit->text().toFloat();
		
		i=i+2;
	}     
	
	for (int j = 0;j < m_pSequenceManualWidget->m_pTestResource->GetVCurRsNum();j++ )
	{
		CalABCValues_BySequenceValues_Float(dA_mag,dA_ang,dB_mag,dB_ang,dC_mag,dC_ang
			,m_pManualParas->m_uiCUR[j].Harm[1].fAmp,m_pManualParas->m_uiCUR[j].Harm[1].fAngle
			,m_pManualParas->m_uiCUR[j+1].Harm[1].fAmp,m_pManualParas->m_uiCUR[j+1].Harm[1].fAngle
			,m_pManualParas->m_uiCUR[j+2].Harm[1].fAmp,m_pManualParas->m_uiCUR[j+2].Harm[1].fAngle);

		m_uiCUR[j].Harm[1].fAmp = dA_mag;
		m_uiCUR[j].Harm[1].fAngle = dA_ang;
		m_uiCUR[j+1].Harm[1].fAmp = dB_mag;
		m_uiCUR[j+1].Harm[1].fAngle = dB_ang;
		m_uiCUR[j+2].Harm[1].fAmp = dC_mag;
		m_uiCUR[j+2].Harm[1].fAngle = dC_ang;

		m_uiCUR[j].Harm[1].fFreq=m_pSequenceManualWidget->m_pFreq_LineEdit->text().toFloat();
		m_uiCUR[j+1].Harm[1].fFreq=m_pSequenceManualWidget->m_pFreq_LineEdit->text().toFloat();
		m_uiCUR[j+2].Harm[1].fFreq=m_pSequenceManualWidget->m_pFreq_LineEdit->text().toFloat();
		
		j=j+2;
	}

	stt_Frame_UpdatePowerData();
	stt_Frame_UpdateVectorData();
}


void QSttMacroParaEditViewSequenceManu::slot_Auto_CheckBox_clicked()
{
	m_pSequenceManualWidget->slot_cb_AutoClicked();
	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_ChGradientTypeComboBox_currentIndexChanged(int index)
{
	if(m_pSequenceManualWidget->m_pChGradientType_ComboBox->IsScrolling())
	{
		return;
	}	

	m_pSequenceManualWidget->slot_cbb_SelectChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_ChSelectComboBox_currentIndexChanged(int index)
{
	if(m_pSequenceManualWidget->m_pChSelect_ComboBox->IsScrolling())
	{
		return;
	}	

	m_pSequenceManualWidget->slot_cbb_ChannelChanged(index);

	SetParaChanged();

	int	nGradientChSelect = m_pManualParas->m_nGradientChSelect;

	if(SEQUENCE_CHANNAL_TYPE_I(nGradientChSelect))
	{
		m_pManualParas->m_nVarIndexType = 0;
	}
	else if(SEQUENCE_CHANNAL_TYPE_U(nGradientChSelect))
	{
		m_pManualParas->m_nVarIndexType = 1;
	}
}

void QSttMacroParaEditViewSequenceManu::slot_ChangedTypeComboBox_currentIndexChanged(int index)
{
	if(m_pSequenceManualWidget->m_pChangedType_ComboBox->IsScrolling())
	{
		return;
	}	

	m_pSequenceManualWidget->slot_cbb_ChangeTypeChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_Bout_CheckBox1_clicked()
{
	m_pSequenceManualWidget->slot_ck_Out1StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_Bout_CheckBox2_clicked()
{
	m_pSequenceManualWidget->slot_ck_Out2StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_Bout_CheckBox3_clicked()
{
	m_pSequenceManualWidget->slot_ck_Out3StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewSequenceManu::slot_Bout_CheckBox4_clicked()
{
	m_pSequenceManualWidget->slot_ck_Out4StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewSequenceManu::ShowReport(CDvmValues *pValues)
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

CString QSttMacroParaEditViewSequenceManu::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += STT_ORG_MACRO_SequenceManuTest;
	strFile += _T(".");
	strFile += "mntxml";

	return strFile;
}

bool QSttMacroParaEditViewSequenceManu::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
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

void QSttMacroParaEditViewSequenceManu::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

//判断使用的keyboard类型
void QSttMacroParaEditViewSequenceManu::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
{
	//20240731 gongyping 
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
		QString strVar = m_pSequenceManualWidget->m_pChSelect_ComboBox->currentText();
		int nIdx = m_pSequenceManualWidget->m_pChGradientType_ComboBox->currentIndex();
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

void QSttMacroParaEditViewSequenceManu::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,TRUE);
	int nInsertPos = 2;
    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	m_pSequenceManualWidget->m_pSequenceManuTab->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewSequenceManu::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,TRUE);
	int nInsertPos = 3;
	
	CString strTitle;
	strTitle=_T("FT3发布");
	m_pSequenceManualWidget->m_pSequenceManuTab->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewSequenceManu::RemoveGooseParaWidget()
{
	if(m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pSequenceManualWidget->m_pSequenceManuTab->indexOf(m_pGooseParaWidget);
	m_pSequenceManualWidget->m_pSequenceManuTab->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QSttMacroParaEditViewSequenceManu::RemoveFT3OutParaWidget()
{
	if(m_pFT3OutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pSequenceManualWidget->m_pSequenceManuTab->indexOf(m_pFT3OutParaWidget);
	m_pSequenceManualWidget->m_pSequenceManuTab->removeTab(nIndex);

	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

bool QSttMacroParaEditViewSequenceManu::ExistGooseParaWidget()
{
	int nIndex = m_pSequenceManualWidget->m_pSequenceManuTab->indexOf(m_pGooseParaWidget);
	return (nIndex>=0);
}

bool QSttMacroParaEditViewSequenceManu::ExistFT3OutParaWidget()
{
	int nIndex = m_pSequenceManualWidget->m_pSequenceManuTab->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewSequenceManu::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		m_pSequenceManualWidget->m_pSequenceManuTab->setTabEnabled(m_pSequenceManualWidget->m_pSequenceManuTab->indexOf(m_pGooseParaWidget),b);
	}
}

void QSttMacroParaEditViewSequenceManu::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		m_pSequenceManualWidget->m_pSequenceManuTab->setTabEnabled(m_pSequenceManualWidget->m_pSequenceManuTab->indexOf(m_pFT3OutParaWidget),b);
	}
}

void QSttMacroParaEditViewSequenceManu::SetDatas(CDataGroup *pDataset)
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

	CalPhaseValues();

    UpdateManualParas();
}

void QSttMacroParaEditViewSequenceManu::slot_StepTime_LineEdit_Changed()
{
	slot_edit_changed(m_pSequenceManualWidget->m_pStepTime_LineEdit, TRUE);
}

void QSttMacroParaEditViewSequenceManu::slot_StepValue_LineEdit_Changed()
{
	slot_edit_changed(m_pSequenceManualWidget->m_pStepValue_LineEdit, TRUE);
}

void QSttMacroParaEditViewSequenceManu::slot_Freq_LineEdit_Changed()
{
	slot_edit_changed(m_pSequenceManualWidget->m_pFreq_LineEdit, TRUE);
}

void QSttMacroParaEditViewSequenceManu::slot_StartValue_LineEdit_Changed()
{
	slot_edit_changed(m_pSequenceManualWidget->m_pStartValue_LineEdit, TRUE);
}

void QSttMacroParaEditViewSequenceManu::slot_EndValue_LineEdit_Changed()
{
	slot_edit_changed(m_pSequenceManualWidget->m_pEndValue_LineEdit, TRUE);
}

void QSttMacroParaEditViewSequenceManu::slot_BinarySetPushButton_clicked()
{
	QSttManualBinBoutDlg oManualBinBoutDlg(m_pManualParas->m_binIn,m_pManualParas->m_binOut,
		&m_pManualParas->m_nBinLogic,&m_pManualParas->m_oSequenceGradient.fTrigDelay,
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

void QSttMacroParaEditViewSequenceManu::slot_EstimatePushButton_clicked()
{
	SequenceManualEstimateDlg dlg(m_pManualParas, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}
