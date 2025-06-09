#include "SttMacroParaEditViewImpedanceManu.h"
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
#include "ImpedanceManuEstimateDlg.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewImpedanceManu* g_pImpedanceManuTest = NULL;

QSttMacroParaEditViewImpedanceManu::QSttMacroParaEditViewImpedanceManu(QWidget *parent) 
{
	setWindowFlags(Qt::FramelessWindowHint);

	InitUI();
	InitLanuage();
	m_bTmtParaChanged = FALSE;
	m_bIsChanging = FALSE;
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;

	memset(m_uiVOL, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));
	memset(m_uiCUR, 0, MAX_VOLTAGE_COUNT * sizeof(tmt_channel));

	m_strParaFileTitle = "通用试验阻抗模板文件";
	m_strParaFileTitle = g_sLangTxt_componenttest;//"通用序分量试验模板文件";
	m_strParaFilePostfix = "project(*.mntxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("ImpedManualTest.mntxml");

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	stt_Frame_InitTestResource();
	m_pManualImpedParas = &m_oManualImpedTest.m_oManuImpedParas;

	OpenTestTestMngrFile(m_strDefaultParaFile);

	CopyBinaryConfig();
	stt_Frame_UpdateToolButtons();

	InitIVView();
	InitParasView();
	InitConnect();

	m_pImpedanceManuWidget->SetData(g_oSttTestResourceMngr.m_pTestResouce, m_pManualImpedParas, 0);
    g_pImpedanceManuTest = this;

	SetDatas(NULL);
	stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);	
	stt_Frame_InitPowerWidget(m_uiVOL,m_uiCUR);
	setFocusPolicy(Qt::StrongFocus);
}

void QSttMacroParaEditViewImpedanceManu::InitLanuage()
{
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pLock_PushButton, "Manual_Lock", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pFaultTypeLabel, "State_FaultType", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pCalModeLabel, "Impedance_CalMode", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pImpedlabel, "Impedance_Choose", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pDLLabel, "Impedance_ShortCurr", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pTrigDelayLabel, "Impedance_Delayed", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pVarSelecLabel, "Impedance_VarChoose", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pCacuTypeLabel, "Impedance_Mode", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pAmpLabel, "Native_Amplitude", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pAngleLabel, "Native_Angle", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pStartLabel, "Gradient_Init", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pEndLabel, "Gradient_Finish", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pTimeLabel, "Impedance_Time", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pStepLabel, "Gradient_Step", XLang_Ctrls_QLabel);
	//xlang_SetLangStrToWidget(m_pImpedanceManuWidget->m_PrepareTimeLabel, "Native_NormTime", XLang_Ctrls_QLabel);
	//xlang_SetLangStrToWidget(m_pImpedanceManuWidget->m_PreFaultTimeLabel, "Native_PreFautTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pChangeTypeLabel, "Impedance_ChangeType", XLang_Ctrls_QLabel);
	//xlang_SetLangStrToWidget(m_pImpedanceManuWidget->m_pActTimeLabel, "Gradient_ActionTime", XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pAuto_CheckBox, "Impedance_Auto", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pMutation_CheckBox, "Impedance_Mutation", XLang_Ctrls_QCheckBox);

	xlang_SetLangStrToWidget(m_pImpedanceManuWidget->ui->m_pBoutGroupBox, "Manual_OutSetting", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget_Txt(m_pImpedanceManuWidget->ui->m_pBinarySet_PushButton,g_sLangTxt_Native_Switch,XLang_Ctrls_QPushButton);

	xlang_SetLangStrToWidget_Txt(m_pImpedanceManuWidget->ui->m_pEstimate_PushButton,g_sLangTxt_State_Estimate,XLang_Ctrls_QPushButton);
}

QSttMacroParaEditViewImpedanceManu::~QSttMacroParaEditViewImpedanceManu()
{
}

void QSttMacroParaEditViewImpedanceManu::InitUI()
{
	m_pImpedanceManuWidget = new QImpedanceManuWidget(this);
	m_pImpedanceManuWidget->InitUI();
	setLayout(m_pImpedanceManuWidget->ui->gridLayout);
}

void QSttMacroParaEditViewImpedanceManu::SendUpdateParameter()
{
	stt_Frame_Ats_UpdateParameter();
}

void QSttMacroParaEditViewImpedanceManu::CopyBinaryConfig(BOOL b)
{
	if(b)
	{
		stt_GetBinaryConfig()->m_nBinLogic = m_pManualImpedParas->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			stt_GetBinaryConfig()->m_binIn[i].nSelect = m_pManualImpedParas->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			stt_GetBinaryConfig()->m_binOut[i].nState = m_pManualImpedParas->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			stt_GetBinaryConfig()->m_binInEx[i].nSelect = m_pManualImpedParas->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			stt_GetBinaryConfig()->m_binOutEx[i].nState = m_pManualImpedParas->m_binOutEx[i].nState;
		}
	}
	else
	{
		m_pManualImpedParas->m_nBinLogic = stt_GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			m_pManualImpedParas->m_binIn[i].nSelect = stt_GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_BINARYOUT_COUNT;i++){
			m_pManualImpedParas->m_binOut[i].nState = stt_GetBinaryConfig()->m_binOut[i].nState;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pManualImpedParas->m_binInEx[i].nSelect = stt_GetBinaryConfig()->m_binInEx[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			m_pManualImpedParas->m_binOutEx[i].nState = stt_GetBinaryConfig()->m_binOutEx[i].nState;
		}
	}
}

void QSttMacroParaEditViewImpedanceManu::InitConnect()
{
	m_pImpedanceManuWidget->InitConnect();
	connect(m_pImpedanceManuWidget->ui->m_pCmb_FaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbErrorTypeIndexChanged(int)));//故障类型
	connect(m_pImpedanceManuWidget->ui->m_pCmb_CalMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbCalModeIndexChanged(int)));//阻抗类型
	connect(m_pImpedanceManuWidget->ui->m_pCmb_CacuType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbCacuTypeIndexChanged(int)));//零系补偿模式ko
	connect(m_pImpedanceManuWidget->ui->m_pCmb_FirstMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbFirstModeIndexChanged(int)));
	connect(m_pImpedanceManuWidget->ui->m_pCmb_SecondMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSecondModeIndexChanged(int)));
	connect(m_pImpedanceManuWidget->ui->m_pCmb_ChangeType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbChangeTypeIndexChanged(int)));

	//阻抗输入选择
	connect(m_pImpedanceManuWidget->ui->m_pRad_Z, SIGNAL(toggled(bool )), this, SLOT(slot_RadioZPhiAndRX_StateChanged()));
	connect(m_pImpedanceManuWidget->ui->m_pRad_RX, SIGNAL(toggled(bool )), this, SLOT(slot_RadioZPhiAndRX_StateChanged()));

	connect(m_pImpedanceManuWidget->ui->m_pAuto_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_Chb_AutoStateChanged(int)));
	connect(m_pImpedanceManuWidget->ui->m_pMutation_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_Chb_MutationStateChanged(int)));

	connect(m_pImpedanceManuWidget->ui->m_pBout_CheckBox0, SIGNAL(clicked ()), this, SLOT(slot_ck_Out1StateChanged()));
	connect(m_pImpedanceManuWidget->ui->m_pBout_CheckBox1, SIGNAL(clicked ()), this, SLOT(slot_ck_Out2StateChanged()));
	connect(m_pImpedanceManuWidget->ui->m_pBout_CheckBox2, SIGNAL(clicked ()), this, SLOT(slot_ck_Out3StateChanged()));
	connect(m_pImpedanceManuWidget->ui->m_pBout_CheckBox3, SIGNAL(clicked ()), this, SLOT(slot_ck_Out4StateChanged()));

	connect(m_pImpedanceManuWidget->ui->m_pZEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pPhiEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pREdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pXEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pShortIOrZsAmpEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pShortIOrZsAngleEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_PrepareTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_PreFaultTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pStepEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pStartEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pEndEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pTrigDelayEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pAmpEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));
	connect(m_pImpedanceManuWidget->ui->m_pAngleEdit,SIGNAL(editingFinished()),this,SLOT(slot_Edit_Changed()));

	connect(m_pImpedanceManuWidget->ui->m_pbn_Down, SIGNAL(clicked()), this, SLOT(slot_PushButton_clicked()));
	connect(m_pImpedanceManuWidget->ui->m_pbn_Up, SIGNAL(clicked()), this, SLOT(slot_PushButton_clicked()));
	connect(m_pImpedanceManuWidget->ui->m_pLock_PushButton, SIGNAL(clicked()), this, SLOT(slot_Lock_PushButton_clicked()));
	connect(m_pImpedanceManuWidget->ui->m_pBinarySet_PushButton, SIGNAL(clicked()), this, SLOT(slot_BinarySetPushButton_clicked()));
	connect(m_pImpedanceManuWidget->ui->m_pEstimate_PushButton, SIGNAL(clicked()), this, SLOT(slot_EstimatePushButton_clicked()));
	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas()));
}

CSttTestResourceBase* QSttMacroParaEditViewImpedanceManu::CreateTestResource()
{
	m_pOriginalSttTestResource = stt_GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewImpedanceManu::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
									long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	//yzj 2022-2-21 开始测试前要保持该值为0
	if(!stt_Frame_IsTestStarted())
	{
		m_pManualImpedParas->m_bBinStop = FALSE;
	}

	tmt_ManualImpedTest *pTmtManualImpedTest = (tmt_ManualImpedTest *)pParas;

	stt_xml_serialize(&pTmtManualImpedTest->m_oManuImpedParas, pMacroParas);

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

void QSttMacroParaEditViewImpedanceManu::OnTestResults(CDataGroup *pResults)
{
	ASSERT(pResults != NULL);

	m_oManualImpedTest.m_nTestState = 1;	//测试完成
}

void QSttMacroParaEditViewImpedanceManu::InitBinaryInBinaryOutUI()
{
	GlobalSetQcheckState_BinaryOut(m_pImpedanceManuWidget->ui->m_pBout_CheckBox0,m_pManualImpedParas->m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_pImpedanceManuWidget->ui->m_pBout_CheckBox1,m_pManualImpedParas->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_pImpedanceManuWidget->ui->m_pBout_CheckBox2,m_pManualImpedParas->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_pImpedanceManuWidget->ui->m_pBout_CheckBox3,m_pManualImpedParas->m_binOut,3);
}

void QSttMacroParaEditViewImpedanceManu::SetManualOtherParasFont()
{
	m_pImpedanceManuWidget->ui->m_pBoutGroupBox->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pFaultTypeLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pCalModeLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pImpedlabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pZLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pRXLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pDLLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pVarSelecLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_PrepareTimeLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_PreFaultTimeLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pStepLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pStartLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pTimeLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pEndLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pTrigDelayLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pChangeTypeLabel->setFont(*g_pSttGlobalFont);
	//m_pImpedanceManuWidget->m_pActTimeLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pCacuTypeLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pAmpLabel->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pAngleLabel->setFont(*g_pSttGlobalFont);

	m_pImpedanceManuWidget->ui->m_pCmb_CalMode->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pCmb_FaultType->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pCmb_FirstMode->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pCmb_SecondMode->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pCmb_CacuType->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pCmb_ChangeType->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pRad_Z->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pRad_RX->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pAuto_CheckBox->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pMutation_CheckBox->setFont(*g_pSttGlobalFont);

	m_pImpedanceManuWidget->ui->m_pPhiEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pZEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pXEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pREdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pShortIOrZsAmpEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pShortIOrZsAngleEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_PrepareTimeEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_PreFaultTimeEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pStepEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pStartEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pTimeEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pEndEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pTrigDelayEdit->setFont(*g_pSttGlobalFont);
	//m_pImpedanceManuWidget->m_pActTimeEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pAmpEdit->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pAngleEdit->setFont(*g_pSttGlobalFont);

	m_pImpedanceManuWidget->ui->m_pBout_CheckBox0->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pBout_CheckBox1->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pBout_CheckBox2->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pBout_CheckBox3->setFont(*g_pSttGlobalFont);

	//m_pImpedanceManuWidget->m_pbn_Clear->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pbn_Up->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pbn_Down->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pLock_PushButton->setFont(*g_pSttGlobalFont);

	m_pImpedanceManuWidget->ui->m_pBinarySet_PushButton->setFont(*g_pSttGlobalFont);
	m_pImpedanceManuWidget->ui->m_pEstimate_PushButton->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewImpedanceManu::InitOtherParasUI()
{
	SetManualOtherParasFont();
}


void QSttMacroParaEditViewImpedanceManu::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();

	m_pImpedanceManuWidget->SetData(stt_GetSttTestResource(), m_pManualImpedParas, 0);
	InitBinaryInBinaryOutUI();
}


void QSttMacroParaEditViewImpedanceManu::UpdateGoutTab(BOOL bUpdateList)
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

void QSttMacroParaEditViewImpedanceManu::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
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

void QSttMacroParaEditViewImpedanceManu::UpdateFT3Tab(BOOL bUpdateList)
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

void QSttMacroParaEditViewImpedanceManu::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
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

void QSttMacroParaEditViewImpedanceManu::slot_GooseDataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_FT3DataChanged()
{
	if (stt_Frame_IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::UpdateBinBoutExTab()
{
	//当前页面无拓展开入开出
}

void QSttMacroParaEditViewImpedanceManu::UpdateManualParas()
{
	m_pImpedanceManuWidget->UpdateData();
	
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewImpedanceManu::ClearResult(PTMT_PARAS_HEAD pHead)
{
	m_oManualImpedTest.m_oManuImpedResult.init();
}

void QSttMacroParaEditViewImpedanceManu::InitStyle()
{
	((QSttCheckBox*)m_pImpedanceManuWidget->ui->m_pAuto_CheckBox)->InitStyleSheet();
	((QSttCheckBox*)m_pImpedanceManuWidget->ui->m_pMutation_CheckBox)->InitStyleSheet();
	((QSttCheckBox*)m_pImpedanceManuWidget->ui->m_pBout_CheckBox0)->InitStyleSheet();
	((QSttCheckBox*)m_pImpedanceManuWidget->ui->m_pBout_CheckBox1)->InitStyleSheet();
	((QSttCheckBox*)m_pImpedanceManuWidget->ui->m_pBout_CheckBox2)->InitStyleSheet();
	((QSttCheckBox*)m_pImpedanceManuWidget->ui->m_pBout_CheckBox3)->InitStyleSheet();
	((QSttTabWidget*)m_pImpedanceManuWidget->ui->m_pImpedanceManuTab)->InitStyleSheet();
}

void QSttMacroParaEditViewImpedanceManu::InitParasView()
{
	InitStyle();

	InitOtherParasUI();
	InitBinaryInBinaryOutUI();
}

void QSttMacroParaEditViewImpedanceManu::InitIVView()
{  
	setFont(*g_pSttGlobalFont);
 	m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewImpedanceManu::slot_SwitchStateChanged()
{
	m_pImpedanceManuWidget->UpdateData();//更新开出量状态

	if (stt_Frame_IsTestStarted() && !m_pManualImpedParas->m_bLockChanged)
	{
		SendUpdateParameter();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::OnViewTestLink(BOOL b)
{

}

void QSttMacroParaEditViewImpedanceManu::OnViewTestStart()
{
	BOOL bEnableState = TRUE;
	int nGooseParasUI_State = STT_UI_RUN_STATE_StateTested_Editable;

	if ((m_pManualImpedParas->m_bAuto))
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

	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	stt_Frame_ClearInfoWidget();
	m_pImpedanceManuWidget->StartInit();

	if(m_pImpedanceManuWidget->ui->m_pAuto_CheckBox->isChecked() && m_pGooseParaWidget)
	{
		m_pGooseParaWidget->setDisabled(true);
	}

	if(m_pImpedanceManuWidget->ui->m_pAuto_CheckBox->isChecked() && m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->setDisabled(true);
	}

	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();

	stt_Frame_EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewImpedanceManu::OnViewTestStop()
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
	
	m_pImpedanceManuWidget->StopInit();
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

	m_pImpedanceManuWidget->ui->m_pBoutGroupBox->setEnabled(true);
	m_pImpedanceManuWidget->ui->m_pBinarySet_PushButton->setEnabled(true);
	m_pImpedanceManuWidget->ui->m_pEstimate_PushButton->setEnabled(true);
}

void QSttMacroParaEditViewImpedanceManu::slot_Lock_PushButton_clicked()
{
	m_pImpedanceManuWidget->slot_pbn_LockClicked();

	if (stt_Frame_IsTestStarted() && (!m_pManualImpedParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_PushButton_clicked()
{
	if(m_bIsChanging)
	{
		return;
	}

	SetParaChanged();

	emit sig_updataParas();
}

void QSttMacroParaEditViewImpedanceManu::slot_Edit_Changed()
{
	SetParaChanged();
	emit sig_updataParas();
}

void QSttMacroParaEditViewImpedanceManu::slot_CmbErrorTypeIndexChanged(int index)
{
	if(m_pImpedanceManuWidget->ui->m_pCmb_FaultType->IsScrolling())
	{
		return;
	}	
	if (index == -1)
	{
		return;
	}


	m_pImpedanceManuWidget->slot_CmbErrorTypeIndexChanged(index);
	CalPhaseValues();
	slot_Edit_Changed();

	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_CmbCalModeIndexChanged(int index)
{
	if(m_pImpedanceManuWidget->ui->m_pCmb_CalMode->IsScrolling())
	{
		return;
	}	

	if (index == -1)
	{
		return;
	}

	m_pImpedanceManuWidget->slot_CmbCalModeIndexChanged(index);
	CalPhaseValues();
	slot_Edit_Changed();
	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_CmbCacuTypeIndexChanged(int index)
{
	if(m_pImpedanceManuWidget->ui->m_pCmb_CacuType->IsScrolling())
	{
		return;
	}	

	if (index == -1)
	{
		return;
	}

	m_pImpedanceManuWidget->slot_CmbCacuTypeIndexChanged(index);
	CalPhaseValues();
	slot_Edit_Changed();
	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_CmbFirstModeIndexChanged(int index)
{
	if(m_pImpedanceManuWidget->ui->m_pCmb_FirstMode->IsScrolling())
	{
		return;
	}	

	m_pImpedanceManuWidget->slot_CmbFirstModeIndexChanged(index);
	SetParaChanged();
}


void QSttMacroParaEditViewImpedanceManu::slot_CmbSecondModeIndexChanged(int index)
{
	if(m_pImpedanceManuWidget->ui->m_pCmb_SecondMode->IsScrolling())
	{
		return;
	}	

	m_pImpedanceManuWidget->slot_CmbSecondModeIndexChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_CmbChangeTypeIndexChanged(int index)
{
	if(m_pImpedanceManuWidget->ui->m_pCmb_ChangeType->IsScrolling())
	{
		return;
	}	

	m_pImpedanceManuWidget->slot_CmbChangeTypeIndexChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_RadioZPhiAndRX_StateChanged()
{
	m_pImpedanceManuWidget->slot_RadioZPhiAndRX_StateChanged();
	SetParaChanged();
}



void QSttMacroParaEditViewImpedanceManu::CalPhaseValues() 
{

	Complex p1,p2;
	float m_fImax = 5000;
	float m_fVmax = 5000000;
	float m_fVnom = g_oSystemParas.m_fVNom/SQRT3;
	int nPhaseRef[11]={1,2,0,2,0,1,2,0,1,0,0};
	if(m_pManualImpedParas->m_fSCVoltage<0.0)m_pManualImpedParas->m_fSCVoltage=0.0;
	if(m_pManualImpedParas->m_fSCVoltage>m_fVmax)m_pManualImpedParas->m_fSCVoltage=m_fVmax;

	if(m_pManualImpedParas->m_fSCCurrent<0.0)m_pManualImpedParas->m_fSCCurrent=0.0;
	if(m_pManualImpedParas->m_fSCCurrent>m_fImax)m_pManualImpedParas->m_fSCCurrent=m_fImax;
	m_pImpedanceManuWidget->OnRXValue();

	CFaultCalculat m_FaultCalculat;
	Complex m_fVa=p1.polar(m_fVnom,0.0);
	Complex m_fVb=p1.polar(m_fVnom,-120.0);
	Complex m_fVc=p1.polar(m_fVnom,120.0);
	Complex m_fIa=p1.polar(0,0.0);
	Complex m_fIb=p1.polar(0,-120.0);
	Complex m_fIc=p1.polar(0,120.0);

	float nAngle[11] = {p1.arg(m_fVb),p1.arg(m_fVc),p1.arg(m_fVa),p1.arg(m_fVc),p1.arg(m_fVa),p1.arg(m_fVb),p1.arg(m_fVc),p1.arg(m_fVa),p1.arg(m_fVb),p1.arg(m_fVa),p1.arg(m_fVa)};

	float m_fKr = m_pManualImpedParas->m_fAmplitudeOrKr;
	float m_fKx = m_pManualImpedParas->m_fPhaseOrKx;
	float m_fPhi = m_pManualImpedParas->m_fZAngle;
	float m_fZ = m_pManualImpedParas->m_fZAmp;
	float m_fZSZL = fabs(m_pManualImpedParas->m_fSZSAmp/m_pManualImpedParas->m_fSZSAngle);
	p1=m_FaultCalculat.GroundFactor(m_pManualImpedParas->m_nOffsetsMode,m_fKr,m_fKx,m_fPhi);
	float m_fK0l=p2.norm(p1);
	float m_fK0lPh=p2.arg(p1);
	Complex fV1,fV2,fV3,fI1,fI2,fI3;
	double fIt,fVt;
	float fValueFactor;

	fIt=m_pManualImpedParas->m_fSCCurrent;
	fVt=m_pManualImpedParas->m_fSCVoltage;
	m_FaultCalculat.Calculat(1.0, 1, 1, m_pManualImpedParas->m_nCalMode, m_pManualImpedParas->m_nFaultType,
		nPhaseRef[m_pManualImpedParas->m_nFaultType],nAngle[m_pManualImpedParas->m_nFaultType],
		m_fVmax,m_fVnom,m_fImax,
		&fIt,&fVt,
		p1.polar(0,0),
		p1.polar(m_fZ,m_fPhi),p1.polar(m_fK0l,m_fK0lPh),
		p1.polar(m_fZ*m_fZSZL,m_fPhi),
		p1.polar(m_fK0l,m_fK0lPh),
		&fV1,&fV2,&fV3,&fI1,&fI2,&fI3);
	m_fVa=fV1;
	m_fVb=fV2;
	m_fVc=fV3;
	m_fIa=fI1;
	m_fIb=fI2;
	m_fIc=fI3;
	m_pManualImpedParas->m_fSCCurrent=fIt;
	m_pManualImpedParas->m_fSCVoltage=fVt;

	QList<tmt_Channel> CHUList;
	QList<tmt_Channel> CHIList;
	tmt_Channel channelPara;

	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;

	Complex p11;

	m_pManualImpedParas->m_uiCUR[0].Harm[1].fAmp = (p11.norm(m_fIa) > fAcIMax)? fAcIMax:p11.norm(m_fIa);
	m_pManualImpedParas->m_uiCUR[1].Harm[1].fAmp = (p11.norm(m_fIb) > fAcIMax)? fAcIMax:p11.norm(m_fIb);
	m_pManualImpedParas->m_uiCUR[2].Harm[1].fAmp = (p11.norm(m_fIc) > fAcIMax)? fAcIMax:p11.norm(m_fIc);
	m_pManualImpedParas->m_uiCUR[0].Harm[1].fAngle = p11.arg(m_fIa);
	m_pManualImpedParas->m_uiCUR[1].Harm[1].fAngle = p11.arg(m_fIb);
	m_pManualImpedParas->m_uiCUR[2].Harm[1].fAngle = p11.arg(m_fIc);

	m_pManualImpedParas->m_uiVOL[0].Harm[1].fAmp  = (p11.norm(m_fVa) > fAcVMax)? fAcVMax:p11.norm(m_fVa);
	m_pManualImpedParas->m_uiVOL[1].Harm[1].fAmp  = (p11.norm(m_fVb) > fAcVMax)? fAcVMax:p11.norm(m_fVb);
	m_pManualImpedParas->m_uiVOL[2].Harm[1].fAmp  = (p11.norm(m_fVc) > fAcVMax)? fAcVMax:p11.norm(m_fVc);
	m_pManualImpedParas->m_uiVOL[0].Harm[1].fAngle = p11.arg(m_fVa);
	m_pManualImpedParas->m_uiVOL[1].Harm[1].fAngle = p11.arg(m_fVb);
	m_pManualImpedParas->m_uiVOL[2].Harm[1].fAngle = p11.arg(m_fVc);



	
}


void QSttMacroParaEditViewImpedanceManu::slot_Chb_AutoStateChanged(int index)
{
	m_pImpedanceManuWidget->slot_Chb_AutoStateChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_Chb_MutationStateChanged(int index)
{
	m_pImpedanceManuWidget->slot_Chb_MutationStateChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_ck_Out1StateChanged()
{
	m_pImpedanceManuWidget->slot_ck_Out1StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_ck_Out2StateChanged()
{
	m_pImpedanceManuWidget->slot_ck_Out2StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_ck_Out3StateChanged()
{
	m_pImpedanceManuWidget->slot_ck_Out3StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_ck_Out4StateChanged()
{
	m_pImpedanceManuWidget->slot_ck_Out4StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewImpedanceManu::slot_updateParas()
{
	if (stt_Frame_IsTestStarted() && (!m_pManualImpedParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}

	CalPhaseValues();
	stt_Frame_UpdateVectorData();
	stt_Frame_UpdatePowerData();
	
	SetParaChanged();
     
}                        

void QSttMacroParaEditViewImpedanceManu::ShowReport(CDvmValues *pValues)
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

CString QSttMacroParaEditViewImpedanceManu::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += STT_ORG_MACRO_ImpedManualTest;
	strFile += _T(".");
	strFile += "mntxml";

	return strFile;
}

bool QSttMacroParaEditViewImpedanceManu::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
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

void QSttMacroParaEditViewImpedanceManu::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

//判断使用的keyboard类型
//void QSttMacroParaEditViewImpedanceManu::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
//{

	////20240802 gongyiping 
	//if (pEditLine->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	//{
	//	if (((QSettingLineEdit*)pEditLine)->IsSetting())
	//	{
	//		return;
	//	}
	//}
//	if (pEditLine->text().isEmpty())
//	{
//		pEditLine->setText("0.0");
//	}
//
//	QString str = pEditLine->text();

	//if(bIsNor == FALSE)
	//{
	//	QString strVar = m_pSequenceManualWidget->m_pChSelect_ComboBox->currentText();
	//	int nIdx = m_pSequenceManualWidget->m_pChGradientType_ComboBox->currentIndex();
	//	switch(nIdx)
	//	{
	//	case 0: 
	//		if(strVar.contains("U"))
	//		{
	//			GetWidgetBoard_DigitData(0,str,pEditLine,this);
	//		}
	//		else
	//		{
	//			GetWidgetBoard_DigitData(1,str,pEditLine,this);
	//		}
	//		break;
	//	case 1: GetWidgetBoard_DigitData(2,str,pEditLine,this); break;
	//	case 2: GetWidgetBoard_DigitData(3,str,pEditLine,this); break;
	//	default:
	//		break;
	//	}

	//}
	//else
	//{
		//GetWidgetBoard_DigitData(4,str,pEditLine,this);
	//}
//}

void QSttMacroParaEditViewImpedanceManu::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,TRUE);
	int nInsertPos = 2;
    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewImpedanceManu::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,TRUE);
	int nInsertPos = 3;
	
	CString strTitle;
	strTitle=_T("FT3发布");
	m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewImpedanceManu::RemoveGooseParaWidget()
{
	if(m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->indexOf(m_pGooseParaWidget);
	m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QSttMacroParaEditViewImpedanceManu::RemoveFT3OutParaWidget()
{
	if(m_pFT3OutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->indexOf(m_pFT3OutParaWidget);
	m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->removeTab(nIndex);

	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

bool QSttMacroParaEditViewImpedanceManu::ExistGooseParaWidget()
{
	int nIndex = m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->indexOf(m_pGooseParaWidget);
	return (nIndex>=0);
}

bool QSttMacroParaEditViewImpedanceManu::ExistFT3OutParaWidget()
{
	int nIndex = m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewImpedanceManu::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->setTabEnabled(m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->indexOf(m_pGooseParaWidget),b);
	}
}

void QSttMacroParaEditViewImpedanceManu::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->setTabEnabled(m_pImpedanceManuWidget->ui->m_pImpedanceManuTab->indexOf(m_pFT3OutParaWidget),b);
	}
}

void QSttMacroParaEditViewImpedanceManu::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pManualImpedParas, &oRead);
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系
	}
	stt_Frame_InitVectorWidget(m_pManualImpedParas->m_uiVOL,m_pManualImpedParas->m_uiCUR);
	stt_Frame_InitPowerWidget(m_pManualImpedParas->m_uiVOL,m_pManualImpedParas->m_uiCUR);
    stt_Frame_InitStateMonitor();
    stt_Frame_ClearInfoWidget();

	CalPhaseValues();
    UpdateManualParas();
}

void QSttMacroParaEditViewImpedanceManu::slot_BinarySetPushButton_clicked()
{
	float fTrigDelay=0;
	QSttManualBinBoutDlg oManualBinBoutDlg(m_pManualImpedParas->m_binIn,m_pManualImpedParas->m_binOut,
		&m_pManualImpedParas->m_nBinLogic,&m_pManualImpedParas->m_manuImpedGradient.fTrigDelay,
		&m_pManualImpedParas->m_bAuto,this);// zhouhj 临时变量命名从sttManualBinBoutDlg改为oManualBinBoutDlg
	oManualBinBoutDlg.setWindowModality(Qt::WindowModal);//模态窗口
	oManualBinBoutDlg.DelayedSetVisible();
	//m_pImpedanceManuWidget->m_pTrigDelayEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fTrigDelay,'f',3)+"S");
	
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

void QSttMacroParaEditViewImpedanceManu::slot_EstimatePushButton_clicked()
{
	ImpedanceManuEstimateDlg dlg(m_pManualImpedParas, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}
