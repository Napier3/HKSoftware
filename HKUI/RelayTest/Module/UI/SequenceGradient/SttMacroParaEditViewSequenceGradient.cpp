#include "SttMacroParaEditViewSequenceGradient.h"
#include "ui_SttMacroParaEditViewSequenceGradient.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SequenceGradientSettingDlg.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_4U3I.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../SttGlobalDef.h"
#include "SequenceGradientWidget.h"
#include <QMessageBox>
#include "../Controls/SttTabWidget.h"
#include"../../Module/XLangResource_Native.h"
//#include "GradientEstimateDlg.h"
//#include "GradientSettingValueDlg.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewSequenceGradient* g_SequenceGradientMain = NULL;

QSttMacroParaEditViewSequenceGradient::QSttMacroParaEditViewSequenceGradient(QWidget *parent) :
	ui(new Ui::QSttMacroParaEditViewSequenceGradient)
{
	ui->setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint);
	InitLanuage();
	g_SequenceGradientMain = this;
	m_bTmtParaChanged = false;
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;
	m_pSequenceGradientWidget = NULL;
	m_strParaFileTitle = g_sLangTxt_State_IncreExperfile; //递变试验模板文件 lcq 3.14
	m_strParaFilePostfix = "project(*.grtxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("SequenceGradient.grtxml");
	SetData(CreateTestParas(GetMacroID())); //初始化创建测试项

	m_pOriginalSttTestResource = stt_GetSttTestResource();//创建软件资源类对象
	stt_Frame_InitTestResource();//软件资源初始化

	if (g_oSystemParas.m_nHasDigital)
	{
		InitFT3PubDataGroups();
		InitGoosePubDataGroups();
	}
	OpenTestTestMngrFile(m_strDefaultParaFile);
	m_pCurPara = &m_pCurTest->m_oSequenceGradientParasEx;

	SetDatas(0);
	m_pCurPara->m_nSttTestMode = 0;

	InitUI();
	InitParas();
	InitConnections();
	InitMannualparas();//初始化故障前时间以及变化前时间
	InitStyle();
	stt_Frame_Ats_UpdateButtonStateByID(STT_CMD_TYPE_ATS_ManuTriger, false, false);
	ui->m_btnSettingValue->hide();
}

QSttMacroParaEditViewSequenceGradient::~QSttMacroParaEditViewSequenceGradient()
{
	if (m_pCurTest != NULL)
	{
		delete m_pCurTest;
		m_pCurTest = NULL;
	}

	delete ui;
}

void QSttMacroParaEditViewSequenceGradient::InitLanuage()
{
	CString strText;
	xlang_GetLangStrByFile(strText, "Gradient_TimeBeforeChange");//变化前时间
	ui->m_labTimeBeforeChange->setText(strText + "(s):");
	xlang_GetLangStrByFile(strText, "Gradient_TimeBeforeFail");
	ui->m_labTimeBeforeFail->setText(strText/*.right(4)*/ + "(s):");//脉冲递变复归时间
	ui->m_cbBefore->setText(strText.left(2));
	xlang_GetLangStrByFile(strText, "sVariable");//变量
	ui->m_labVar->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Gradient_VarType");//变量类型
	ui->m_labVarType->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Native_Current");//电流
	xlang_GetLangStrByFile(strText, "Native_Current");
	xlang_GetLangStrByFile(strText, "Native_Voltage");
	xlang_GetLangStrByFile(strText, "Native_Voltage");//电压
	xlang_GetLangStrByFile(strText, "Gradient_Phase");//相位差
	xlang_GetLangStrByFile(strText, "Gradient_Init");//变化始值
	ui->m_labInit->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Gradient_Finish");//变化终值
	ui->m_labFinish->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Gradient_Step");//变化步长
	ui->m_labStep->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Gradient_Time");//故障时间
	ui->m_labTime->setText(strText + "(s):");
	xlang_GetLangStrByFile(strText, "Gradient_Direction");//递变方向
	ui->m_labDirection->setText(strText + ":");
	xlang_SetLangStrToWidget(ui->m_labType, "Native_Type", XLang_Ctrls_QLabel);//类型
	xlang_GetLangStrByFile(m_strCurrent, "Native_Current");
	xlang_GetLangStrByFile(m_strVoltage, "Native_Voltage");
	xlang_GetLangStrByFile(m_strFreq, "Native_Freq");
	xlang_GetLangStrByFile(strText, "Gradient_VarSet");//变量设置
	ui->m_gpVarSet->setTitle(strText);
	xlang_GetLangStrByFile(strText, "Gradient_ChangingSet"); //递变参数设置
	ui->m_gpChangeSet->setTitle(strText);
	xlang_GetLangStrByFile(strText, "sGeneralParameter");//通用参数 lcq
	ui->m_gpMannual->setTitle(strText);
	xlang_GetLangStrByFile(strText, "Gradient_UnChangingSet");//非递变通道设置
	ui->m_tabWidget->setTabText(0, g_sLangTxt_Gradient_ChangingSet);//递变通道设置
	xlang_GetLangStrByFile(strText, "Native_LogicAnd");//逻辑与
	ui->m_rbAnd->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_LogicOr");//逻辑或
	ui->m_rbOr->setText(strText);
	xlang_SetLangStrToWidget(ui->m_gpBin, "Native_Bin", XLang_Ctrls_QGroupBox);//开入量
	xlang_SetLangStrToWidget(ui->m_gpBoutNormal, "Gradient_Normal", XLang_Ctrls_QGroupBox);//开出量正常态
	xlang_SetLangStrToWidget(ui->m_gpBoutError, "Gradient_Failure", XLang_Ctrls_QGroupBox);//开出量故障态
	xlang_GetLangStrByFile(strText, "Native_BinX");
	ui->m_cbBinA->setText(/*strText +*/ "A");
	ui->m_cbBinB->setText(/*strText +*/ "B");
	ui->m_cbBinC->setText(/*strText +*/ "C");
	ui->m_cbBinD->setText(/*strText +*/ "D");
	ui->m_cbBinE->setText(/*strText +*/ "E");
	ui->m_cbBinF->setText(/*strText +*/ "F");
	ui->m_cbBinG->setText(/*strText +*/ "G");
	ui->m_cbBinH->setText(/*strText +*/ "H");
	ui->m_cbBinI->setText(/*strText +*/"I");
	ui->m_cbBinJ->setText(/*strText +*/ "J");

	xlang_GetLangStrByFile(strText, "Native_BoutX");
	ui->m_cbBOut1->setText(/*strText +*/ "1");
	ui->m_cbBOut2->setText(/*strText +*/ "2");
	ui->m_cbBOut3->setText(/*strText +*/ "3");
	ui->m_cbBOut4->setText(/*strText +*/ "4");

	ui->m_cbBOut1_E->setText(/*strText +*/ "1");
	ui->m_cbBOut2_E->setText(/*strText +*/ "2");
	ui->m_cbBOut3_E->setText(/*strText +*/ "3");
	ui->m_cbBOut4_E->setText(/*strText +*/ "4");
	xlang_GetLangStrByFile(strText,"Native_Bout");//开出量
	CString str;
	xlang_GetLangStrByFile(str,"Gradient_Normal");
	ui->m_gpBoutNormal->setTitle(strText+str);
	xlang_GetLangStrByFile(str,"Gradient_Failure");
	ui->m_gpBoutError->setTitle(strText+str);

	xlang_SetLangStrToWidget(ui->m_btnMoreOut, "Gradient_BoutSets", XLang_Ctrls_QPushButton);//更多开入量设置 lcq
	xlang_SetLangStrToWidget(ui->m_btnEstimate, "State_Estimate", XLang_Ctrls_QPushButton);//整定及结果评估 lcq

}

void QSttMacroParaEditViewSequenceGradient::SetSequenceGradientFont()
{

#ifdef _PSX_QT_LINUX_//解决Windows下字体不一致问题
	g_pSttGlobalFont->resolve(QFont::AllPropertiesResolved);
#endif
	setFont(*g_pSttGlobalFont);
	ui->m_tabWidget->setFont(*g_pSttGlobalFont);
	ui->m_gpVarSet->setFont(*g_pSttGlobalFont);
	ui->m_labVar->setFont(*g_pSttGlobalFont);
	ui->m_cbbVar->setFont(*g_pSttGlobalFont);
	ui->m_labVarType->setFont(*g_pSttGlobalFont);
	ui->m_cbbVarType->setFont(*g_pSttGlobalFont);
	ui->m_gpChangeSet->setFont(*g_pSttGlobalFont);
	ui->m_editFinish->setFont(*g_pSttGlobalFont);
	ui->m_labFinish->setFont(*g_pSttGlobalFont);
	ui->m_labInit->setFont(*g_pSttGlobalFont);
	ui->m_editInit->setFont(*g_pSttGlobalFont);	
	ui->m_labStep->setFont(*g_pSttGlobalFont);
	ui->m_editStep->setFont(*g_pSttGlobalFont);
	ui->m_labTime->setFont(*g_pSttGlobalFont);
	ui->m_editTime->setFont(*g_pSttGlobalFont);
	ui->m_cbbType->setFont(*g_pSttGlobalFont);
	ui->m_labDirection->setFont(*g_pSttGlobalFont);
	ui->m_cbbDirection->setFont(*g_pSttGlobalFont);
	ui->m_labType->setFont(*g_pSttGlobalFont);
	ui->m_gpMannual->setFont(*g_pSttGlobalFont);
	ui->m_labTimeBeforeChange->setFont(*g_pSttGlobalFont);
	ui->m_editTimeBeforeChange->setFont(*g_pSttGlobalFont);
	ui->m_labTimeBeforeFail->setFont(*g_pSttGlobalFont);
	ui->m_editTimeBeforeFail->setFont(*g_pSttGlobalFont);
	ui->m_cbBefore->setFont(*g_pSttGlobalFont);
	ui->m_cbBinA->setFont(*g_pSttGlobalFont);
	ui->m_cbBinB->setFont(*g_pSttGlobalFont);
	ui->m_cbBinC->setFont(*g_pSttGlobalFont);
	ui->m_cbBinD->setFont(*g_pSttGlobalFont);
	ui->m_cbBinE->setFont(*g_pSttGlobalFont);
	ui->m_cbBinF->setFont(*g_pSttGlobalFont);
	ui->m_cbBinG->setFont(*g_pSttGlobalFont);
	ui->m_cbBinH->setFont(*g_pSttGlobalFont);
	ui->m_cbBinJ->setFont(*g_pSttGlobalFont);
	ui->m_cbBinI->setFont(*g_pSttGlobalFont);
	ui->m_rbAnd->setFont(*g_pSttGlobalFont);
	ui->m_rbOr->setFont(*g_pSttGlobalFont);
	ui->m_gpBin->setFont(*g_pSttGlobalFont);
	ui->m_gpBoutNormal->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut1->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut2->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut3->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut4->setFont(*g_pSttGlobalFont);
	ui->m_gpBoutError->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut1_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut2_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut3_E->setFont(*g_pSttGlobalFont);	
	ui->m_cbBOut4_E->setFont(*g_pSttGlobalFont);

	ui->m_btnEstimate->setFont(*g_pSttGlobalFont);
	ui->m_btnMoreOut->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewSequenceGradient::InitUI()
{
	SetSequenceGradientFont();
	((QSttTabWidget*)ui->m_tabWidget)->InitStyleSheet();
	disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	disconnect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));
	disconnect(ui->m_cbbDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbDirection_currentIndexChanged( int)));

	CString strText;
	xlang_GetLangStrByFile(strText, "Gradient_Anticlockwise");//逆时针
	ui->m_cbbDirection->addItem(strText);
	xlang_GetLangStrByFile(strText, "Gradient_Clockwise");//顺时针
	ui->m_cbbDirection->addItem(strText);
	ui->m_cbbDirection->setDisabled(true);
	initMaxPositiveEdit(ui->m_editInit);//变化始长
	initMaxPositiveEdit(ui->m_editFinish);
	initMaxPositiveEdit(ui->m_editStep);
	initMaxPositiveEdit(ui->m_editTime);//故障时间

	InitQList();//初始化变量类型以及类型下拉框的值
	UpdateSequenceGradientChs();

	ui->m_cbbVarType->clear();
	ui->m_cbbVarType->addItems(m_ChangeTypeList);
	ui->m_cbbType->clear();
	connect(ui->m_cbbDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbDirection_currentIndexChanged(int)));
	connect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged(int)));
	connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged(int)));
	ui->m_cbBefore->InitStyleSheet();
	ui->m_cbBefore->setChecked(true);

	if (m_pSequenceGradientWidget == NULL)
	{
		AddUnSequenceGradientSettingWidget();
	}
	else
	{
		RemoveUnSequenceGradientSettingWidget();
	}

	this->setLayout(ui->m_MainLayout);

}

void QSttMacroParaEditViewSequenceGradient::InitParas()
{
	if (m_pCurPara == NULL)
	{
		return;
	}

	disconnect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
	disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	disconnect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));
	ui->m_cbbVarType->clear();
	ui->m_cbbVarType->addItems(m_ChangeTypeList);
	Sequence_type var = getParaTypeByIndex(m_pCurPara->m_nChannel);
	InitSequenceGradientChannel(var);//设置当前的变量
	ui->m_cbbVarType->setCurrentIndex(m_pCurPara->m_nType);//设置当前变量类型为幅值
	ui->m_cbbType->clear();

	if (m_pCurPara->m_nType == phasor_type)
	{
		ui->m_cbbType->addItems(m_listTestMode3);
	}
	else
	{
		ui->m_cbbType->addItems(m_listTestMode2);
	}

	ui->m_cbbType->setCurrentIndex(m_pCurPara->m_nTestMode);
	connect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));
	connect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
	connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	initMaxPositiveEdit(ui->m_editTimeBeforeChange);
	initMaxPositiveEdit(ui->m_editTimeBeforeFail);
	
	ui->m_editTimeBeforeChange->setText(QString::number(m_pCurPara->m_fPrepareTime,'f',3));
	if(m_pCurPara->m_fPreFaultTime < 0.0001)
	{
		m_pCurPara->m_fPreFaultTime = 0;
		ui->m_editTimeBeforeFail->setText("0");
		ui->m_editTimeBeforeFail->setEnabled(false);
		ui->m_cbBefore->setChecked(false);
	}
	else
	{
	ui->m_editTimeBeforeFail->setText(QString::number(m_pCurPara->m_fPreFaultTime,'f',3));
	}
	m_pCurPara->m_fEDU = g_oSystemParas.m_fVNom / G3;
	m_pCurPara->m_fEDFreq = g_oSystemParas.m_fFNom;

// 	ui->m_editInit->setText(QString::number(m_pCurPara->m_fStart, 'f', 3));
// 	ui->m_editFinish->setText(QString::number(m_pCurPara->m_fStop, 'f', 3));
// 	ui->m_editStep->setText(QString::number(m_pCurPara->m_fStep, 'f', 3));
// 	ui->m_editTime->setText(QString::number(m_pCurPara->m_fStepTime, 'f', 3));	//步长时间=故障时间
	((QSettingLineEdit*)ui->m_editInit)->UpdateStructText(CVariantDataAddress(&m_pCurPara->m_fStart), 3);
	((QSettingLineEdit*)ui->m_editFinish)->UpdateStructText(CVariantDataAddress(&m_pCurPara->m_fStop), 3);
	((QSettingLineEdit*)ui->m_editStep)->UpdateStructText(CVariantDataAddress(&m_pCurPara->m_fStep), 3);
	((QSettingLineEdit*)ui->m_editTime)->UpdateStructText(CVariantDataAddress(&m_pCurPara->m_fStepTime), 3);


	
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinA,m_pCurPara->m_binIn,0);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinB,m_pCurPara->m_binIn,1);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinC,m_pCurPara->m_binIn,2);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinD,m_pCurPara->m_binIn,3);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinE,m_pCurPara->m_binIn,4);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinF,m_pCurPara->m_binIn,5);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinG,m_pCurPara->m_binIn,6);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinH,m_pCurPara->m_binIn,7);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinI,m_pCurPara->m_binIn,8);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinJ,m_pCurPara->m_binIn,9);
	
	//2024-8-27 wuxinyi 从j往后的开入量选择置为0
	for (int nIndex = 10; nIndex < MAX_BINARYIN_COUNT; nIndex++)
	{
		m_pCurPara->m_binIn[nIndex].nSelect = 0;
	}

	//常态开出量设置
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut1,m_pCurPara->m_binOut[0],0);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut2,m_pCurPara->m_binOut[0],1);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut3,m_pCurPara->m_binOut[0],2);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut4,m_pCurPara->m_binOut[0],3);
	//故障态开出量设置
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut1_E,m_pCurPara->m_binOut[1],0);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut2_E,m_pCurPara->m_binOut[1],1);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut3_E,m_pCurPara->m_binOut[1],2);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut4_E,m_pCurPara->m_binOut[1],3);
	
	if(m_pCurPara->m_nBinLogic)
	{
		ui->m_rbAnd->setChecked(true);
	}
	else
	{
		ui->m_rbOr->setChecked(true);
	}

	updateLabName();
	ui->m_cbbDirection->setCurrentIndex(m_pCurPara->m_nPhaseGradDir);
	EnableRadientType();
	//初始化时间特性曲线的标题
	emit sig_Para_ChangeIndexChanged(m_pCurPara->m_nChannel);
	CopyBinaryConfig();
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewSequenceGradient::InitEnableButtons()
{
	long nSequenceGradientChannel = GetSttSequenceGradientChannelType(m_pCurPara->m_nChannel);
	BOOL bCurentChannel = FALSE,bVoltageChannel = FALSE;

	if (nSequenceGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_CURR)
	{
		bCurentChannel = TRUE;
	}
	else if (nSequenceGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_VOLT)
	{
		bVoltageChannel = TRUE;
	}
}

void QSttMacroParaEditViewSequenceGradient::InitConnections()
{
	connect(ui->m_editTimeBeforeChange,SIGNAL(editingFinished()),this,SLOT(on_m_editTimeBeforeChangeChanged()));
	connect(ui->m_editTimeBeforeFail,SIGNAL(editingFinished()),this,SLOT(on_m_editTimeBeforeFailChanged()));
	connect(ui->m_editInit, SIGNAL(editingFinished()), this, SLOT(on_m_editInitChanged()));
	connect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(on_m_editFinishChanged()));
	connect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(on_m_editStepChanged()));
	connect(ui->m_editTime, SIGNAL(editingFinished ()), this, SLOT(on_m_editTimeChanged()));
	connect(ui->m_cbBefore, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbBefore_clicked(int)));
	connect(ui->m_cbBinA, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutA_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBinB, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutB_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBinC, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutC_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBinD, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutD_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBinE, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutE_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBinF, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutF_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBinG, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutG_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBinH, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutH_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBinI, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutI_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBinJ, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutJ_StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_rbAnd, SIGNAL(toggled(bool )), this, SLOT(slot_radio_AndStateChanged(bool)),Qt::UniqueConnection);
	connect(ui->m_rbOr, SIGNAL(toggled(bool )), this, SLOT(slot_radio_OrStateChanged(bool)),Qt::UniqueConnection);
	connect(ui->m_cbBOut1, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut1StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut2, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut2StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut3, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut3StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut4, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut4StateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut1_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut1_EStateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut2_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut2_EStateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut3_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut3_EStateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut4_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut4_EStateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_btnMoreOut,SIGNAL(clicked()),this,SLOT(on_m_btnManual_clicked()));
	connect(ui->m_btnEstimate,SIGNAL(clicked()),this,SLOT(slot_Estimate()));
	connect(ui->m_btnSettingValue,SIGNAL(clicked()),this,SLOT(slot_SettingValue()));
}

void QSttMacroParaEditViewSequenceGradient::InitStyle()
{
	((QSttCheckBox*)ui->m_cbBinA)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinB)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinC)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinD)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinE)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinF)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinG)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinH)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinI)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinJ)->InitStyleSheet();

	((QSttCheckBox*)ui->m_cbBOut1)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut2)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut3)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut4)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut1_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut2_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut3_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut4_E)->InitStyleSheet();
}

void QSttMacroParaEditViewSequenceGradient::CopyBinaryConfig(BOOL b)
{
	//开关量
	tmt_GradientParasEx* pSequenceGradientPara = m_pCurPara;
	if (pSequenceGradientPara == NULL)
	{
		return;
	}

	if (b)
	{
		stt_GetBinaryConfig()->m_nBinLogic = pSequenceGradientPara->m_nBinLogic;
		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			stt_GetBinaryConfig()->m_binIn[i].nSelect = pSequenceGradientPara->m_binIn[i].nSelect;
		}

		for (int i = 0; i < MAX_ExBINARY_COUNT; i++)
		{
			stt_GetBinaryConfig()->m_binInEx[i].nSelect = pSequenceGradientPara->m_binInEx[i].nSelect;
		}
	}
	else
	{
		pSequenceGradientPara->m_nBinLogic = stt_GetBinaryConfig()->m_nBinLogic;
		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			pSequenceGradientPara->m_binIn[i].nSelect = stt_GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i = 0; i < MAX_ExBINARY_COUNT; i++)
		{
			pSequenceGradientPara->m_binInEx[i].nSelect = stt_GetBinaryConfig()->m_binInEx[i].nSelect;
		}
	}
}

void QSttMacroParaEditViewSequenceGradient::InitMannualparas()
{
	m_pCurPara->m_fPrepareTime = ui->m_editTimeBeforeChange->text().toFloat();	//准备时间
	m_pCurPara->m_fPreFaultTime = ui->m_editTimeBeforeFail->text().toFloat();	//故障前时间
}

void QSttMacroParaEditViewSequenceGradient::InitQList()
{
	CString strPhase, strFreq, strAmp;
	CString strAction, strReturn, strAngle;

	xlang_GetLangStrByFile(strPhase, "Native_Angle");//相位
	xlang_GetLangStrByFile(strFreq, "Native_Freq");//频率
	xlang_GetLangStrByFile(strAmp, "Native_Amplitude");//幅值
	xlang_GetLangStrByFile(strAction, "Native_Action");//动作值
	strAction = strAction.Mid(0, strAction.ReverseFind('('));
	xlang_GetLangStrByFile(strReturn, "Native_ReturnCoeff");//返回系数
	xlang_GetLangStrByFile(strAngle, "Gradient_MaxAngle");//最大灵敏角

	m_ChangeTypeList.clear();
	//m_ChangeTypeList << strAmp << strPhase;
	m_ChangeTypeList << strAmp;


	m_listTestMode2.clear();
	//m_listTestMode2 << strAction << strReturn;
	m_listTestMode2 << strAction;

	m_listTestMode3.clear();
	m_listTestMode3 << strAction << strReturn << strAngle;
}

void QSttMacroParaEditViewSequenceGradient::UpdateSequenceGradientChs()
{
	if (g_oSttTestResourceMngr.m_pTestResouce != NULL)
	{
		g_oSttTestResourceMngr.m_pTestResouce->AddGradientSequence(m_oSequenceGradientChs);
	}

	disconnect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
	ui->m_cbbVar->clear();

	CDataTypeValue *pCurTypeValue = NULL;
	POS pos = m_oSequenceGradientChs.GetHeadPosition();

	while(pos)
	{
		pCurTypeValue = (CDataTypeValue *)m_oSequenceGradientChs.GetNext(pos);
		if ((pCurTypeValue->m_strID == "U1-1") || (pCurTypeValue->m_strID == "U1-2") || (pCurTypeValue->m_strID == "U1-0"))
		{
			ui->m_cbbVar->addItem(pCurTypeValue->m_strID.GetString());
		}
		if ((pCurTypeValue->m_strID == "I1-1") || (pCurTypeValue->m_strID == "I1-2") || (pCurTypeValue->m_strID == "I1-0"))
		{
			ui->m_cbbVar->addItem(pCurTypeValue->m_strID.GetString());
		}
		
	}
	connect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged(int)));
}

void QSttMacroParaEditViewSequenceGradient::InitSequenceGradientChannel(Sequence_type vartype)
{
	CDataTypeValue *pCurSelData = m_oSequenceGradientChs.FindByIndex(vartype);

	if (pCurSelData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的递变通道(Index=%d)未查找到."),vartype);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurselinNotFound.GetString(),vartype); //当前选择的递变通道(Index=%d)未查找到. lcq 3.14
		return;
	} 
	else
	{
		long nIndex = m_oSequenceGradientChs.FindIndex(pCurSelData);
		ui->m_cbbVar->setCurrentIndex(nIndex);
	}
}

void QSttMacroParaEditViewSequenceGradient::getYRange(float ftime,float fv,float v1,float v2,float fstart,float fend,float &down,float &up)
{
	float fNew=fv;
	if (ftime < EPSINON)
	{
		fNew=0;
	}

	up = getMaxFormThreeValue(getMaxFormThreeValue(fNew,v1,v2),fstart,fend);
	down = getMinFormThreeValue(getMinFormThreeValue(fNew,v1,v2),fstart,fend);
}

void QSttMacroParaEditViewSequenceGradient::InitUI_AfterSequenceGridentSel()
{
	CString strInit, strFinish, strStep;
	xlang_GetLangStrByFile(strInit, "Gradient_Init");
	xlang_GetLangStrByFile(strFinish, "Gradient_Finish");
	xlang_GetLangStrByFile(strStep, "Gradient_Step");

	CString strPhase;

#ifndef _PSX_QT_LINUX_
	strPhase += QString::fromLocal8Bit("(°):");
#else
	strPhase += "(°):";
#endif

	disconnect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged(int)));
	long nGradientChannel = GetSttSequenceGradientChannelType(m_pCurPara->m_nChannel);
	BOOL bCurentChannel = FALSE,bVoltageChannel = FALSE;

	if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_CURR)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Current = m_pCurPara->m_fEDI;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
		}
		bCurentChannel = TRUE;
	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_VOLT)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Volt = m_pCurPara->m_fEDU;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
		}
		bVoltageChannel = TRUE;
	}

	ui->m_cbbType->clear();
	if (m_pCurPara->m_nType == phasor_type)
	{
		ui->m_cbbType->addItems(m_listTestMode3);
	}
	else
	{
		ui->m_cbbType->addItems(m_listTestMode2);
	}
	CString strTemp;
	switch(m_pCurPara->m_nType)
	{
	case  amplitude_type://幅值
		{
			if (bCurentChannel)
			{
				ui->m_labInit->setText(strInit + "(A):");
				ui->m_labFinish->setText(strFinish + "(A):");
				ui->m_labStep->setText(strStep + "(A):");
				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDI,m_pCurPara->m_fG1Current,m_pCurPara->m_fG2Current,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strCurrent + "(A)",fdown/FRADIO,fup*FRADIO);
			}
			else if (bVoltageChannel)
			{
				ui->m_labInit->setText(strInit + "(V):");
				ui->m_labFinish->setText(strFinish + "(V):");
				ui->m_labStep->setText(strStep + "(V):");
				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDU,m_pCurPara->m_fG1Volt,m_pCurPara->m_fG2Volt,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strVoltage + "(V)",fdown/FRADIO,fup*FRADIO);
			}
		}
		break;
	case phasor_type://相位
		{
			emit sig_Para_ChangeIndexChanged(m_pCurPara->m_nChannel);
			ui->m_labInit->setText(strInit + strPhase);
			ui->m_labFinish->setText(strFinish + strPhase);
			ui->m_labStep->setText(strStep + strPhase);

			float fdown=0;
			float fup=0;
			if(m_pCurPara->m_fStart > m_pCurPara->m_fStop)
			{
				fdown = m_pCurPara->m_fStop;
				fup = m_pCurPara->m_fStart;
			}
			else
			{
				fup = m_pCurPara->m_fStop;
				fdown = m_pCurPara->m_fStart;
			}
			CString strType;
			xlang_GetLangStrByFile(strType, "Native_Angle");
			emit sig_YRangeChanged(phasor_type, strType + strPhase.left(strPhase.length() - 1),fdown/FRADIO,fup*1.3);
		}
		break;
	}

	connect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged(int)));
	if (m_pCurPara->m_nTestMode >= ui->m_cbbType->count())
	{
		m_pCurPara->m_nTestMode = 0;
	}
	
	ui->m_cbbType->setCurrentIndex(m_pCurPara->m_nTestMode);
	on_m_cbbType_currentIndexChanged(m_pCurPara->m_nTestMode);
	ui->m_editInit->SetEditFinished();
	ui->m_editFinish->SetEditFinished();


}

void QSttMacroParaEditViewSequenceGradient::EnableRadientType()
{
	if (m_pCurPara == NULL)
	{
		return;
	}

	if (m_pCurPara->m_nType == phasor_type && m_pCurPara->m_nTestMode != 2)
	{
		//变量类型为相位且类型不为最大灵敏角
		ui->m_cbbDirection->setDisabled(false);
	}
	else
	{
		ui->m_cbbDirection->setDisabled(true);
	}

}

long QSttMacroParaEditViewSequenceGradient::GetSttSequenceGradientChannelType(long nChannel)
{
	if ((nChannel == 0) || (nChannel == 1) || (nChannel == 2))//U1-1\2\0
	{
		return STT_GRADIENT_CHANNEL_TYPE_G1_VOLT;
	}
	if ((nChannel == 6) || (nChannel == 7) || (nChannel == 8))//I1-1\2\0
	{
		return STT_GRADIENT_CHANNEL_TYPE_G1_CURR;
	}
	return null_type;
}

void QSttMacroParaEditViewSequenceGradient::updateLabName()
{
	CString strInit, strFinish, strStep;
	xlang_GetLangStrByFile(strInit, "Gradient_Init");
	xlang_GetLangStrByFile(strFinish, "Gradient_Finish");
	xlang_GetLangStrByFile(strStep, "Gradient_Step");

	CString strPhase;

#ifndef _PSX_QT_LINUX_
	strPhase += QString::fromLocal8Bit("(°):");
#else
	strPhase += "(°):";
#endif

	CString strTemp;
	int index = m_pCurPara->m_nType;
	switch(index)
	{
	case amplitude_type:
		{
			QString str = ui->m_cbbVar->currentText();
			if (str.contains(tr("I")))
			{
				ui->m_labInit->setText(strInit + "(A):");
				ui->m_labFinish->setText(strFinish + "(A):");
				ui->m_labStep->setText(strStep + "(A):");
				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDI,m_pCurPara->m_fG1Current,m_pCurPara->m_fG2Current,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strCurrent + "(A)",fdown/FRADIO,fup*FRADIO);
			}
			else if (str.contains(tr("U")))
			{
				ui->m_labInit->setText(strInit + "(V):");
				ui->m_labFinish->setText(strFinish + "(V):");
				ui->m_labStep->setText(strStep + "(V):");
				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDU,m_pCurPara->m_fG1Volt,m_pCurPara->m_fG2Volt,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strVoltage + "(V)",fdown/FRADIO,fup*FRADIO);
			}
		}
	break;
	case phasor_type:
		{
			ui->m_labInit->setText(strInit + strPhase);
			ui->m_labFinish->setText(strFinish + strPhase);
			ui->m_labStep->setText(strStep + strPhase);
			float fdown=0;
			float fup=0;
			if(m_pCurPara->m_fStart > m_pCurPara->m_fStop)
			{
				fdown = m_pCurPara->m_fStop;
				fup = m_pCurPara->m_fStart;
			}
			else
			{
				fup = m_pCurPara->m_fStop;
				fdown = m_pCurPara->m_fStart;
			}

			CString strType;
			xlang_GetLangStrByFile(strType, "Native_Angle");
			emit sig_YRangeChanged(phasor_type, strType + strPhase.Left(strPhase.length() - 1),fdown/FRADIO,fup*1.3);	//φ
		}
		break;
	default:
		break;
    }
}

void QSttMacroParaEditViewSequenceGradient::AddUnSequenceGradientSettingWidget()
{
	if (m_pSequenceGradientWidget)
	{
		return;
	}

	m_pSequenceGradientWidget = new QSequenceGradientWidget(this);	
	m_pSequenceGradientWidget->Init(m_pCurPara);
	int nInsertPos = 1;
	CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Gradient_UnChangingSet");
	ui->m_tabWidget->insertTab(nInsertPos,m_pSequenceGradientWidget,strTitle);

    int nIndex = ui->m_cbbVar->currentIndex();
 	
//  	if (nIndex >= 3)
//  	{
//  		nIndex += 3 ;
//  	}
 	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oSequenceGradientChs.GetAtIndex(nIndex);
 	//CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oSequenceGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
 	m_pSequenceGradientWidget->UpdateFaultEditState(pCurDataTypeValue);	

	m_pCurPara->m_nSttTestMode=3;
}

void QSttMacroParaEditViewSequenceGradient::RemoveUnSequenceGradientSettingWidget()
{
	if(m_pSequenceGradientWidget == NULL)
	{
		return;
	}

	int nIndex = ui->m_tabWidget->indexOf(m_pSequenceGradientWidget);
	ui->m_tabWidget->removeTab(nIndex);

	delete m_pSequenceGradientWidget;
	m_pSequenceGradientWidget = NULL;
	m_pCurPara->m_nSttTestMode = 0;
}

void QSttMacroParaEditViewSequenceGradient::SetData(PTMT_PARAS_HEAD pCurr)
{
	ASSERT(m_pCur != NULL);
	m_pCurTest = (tmt_SequenceGradientTestEx*)pCurr;//该处结构体需要换成对应的结构体以及变量名

	m_pCurPara = &m_pCurTest->m_oSequenceGradientParasEx;
	m_pCurResult = &m_pCurTest->m_oSequenceResultParas;
}

void QSttMacroParaEditViewSequenceGradient::startInit()
{
	ui->m_gpMannual->setEnabled(false);
	ui->m_cbbVar->setDisabled(true);
	ui->m_cbbVarType->setDisabled(true);
	ui->m_cbbType->setDisabled(true);
	ui->m_cbbDirection->setDisabled(true);
	ui->m_editInit->setDisabled(true);
	ui->m_editFinish->setDisabled(true);
	ui->m_editStep->setDisabled(true);
	ui->m_editTime->setDisabled(true);
	ui->m_cbbType->setDisabled(true);
	m_pSequenceGradientWidget->SetEnabledUI(false);
	//设置控件的使能状态
	if ((m_pGooseParaWidget != NULL) && (g_oSystemParas.m_nHasDigital))
	{
		m_pGooseParaWidget->SetGooseDisabled(TRUE);
	}
	if ((m_pFT3OutParaWidget != NULL) && (g_oSystemParas.m_nHasDigital))
	{
		m_pFT3OutParaWidget->SetGooseDisabled(TRUE);
	}

	ui->m_gpBin->setDisabled(true);
	ui->m_gpBoutNormal->setDisabled(true);
	ui->m_gpBoutError->setDisabled(true);
	ui->m_btnSettingValue->setDisabled(true);
	ui->m_btnEstimate->setDisabled(true);
	ui->m_btnMoreOut->setDisabled(true);
}

void QSttMacroParaEditViewSequenceGradient::stopInit()
{
	ui->m_gpMannual->setEnabled(true);
	ui->m_cbbVar->setDisabled(false);
	ui->m_cbbVarType->setDisabled(false);
	ui->m_cbbType->setDisabled(false);
	ui->m_cbbDirection->setDisabled(false);
	ui->m_editInit->setDisabled(false);
	ui->m_editFinish->setDisabled(false);
	ui->m_editStep->setDisabled(false);
	ui->m_editTime->setDisabled(false);
	ui->m_cbbType->setDisabled(false);
	m_pSequenceGradientWidget->SetEnabledUI(true);
	ui->m_gpBin->setDisabled(false);
	ui->m_gpBoutNormal->setDisabled(false);
	ui->m_gpBoutError->setDisabled(false);
	ui->m_btnSettingValue->setDisabled(false);
	ui->m_btnEstimate->setDisabled(false);
	ui->m_btnMoreOut->setDisabled(false);
	//设置界面控件的失能状态
	if ((m_pGooseParaWidget != NULL) && (g_oSystemParas.m_nHasDigital))
	{
		m_pGooseParaWidget->SetGooseDisabled(FALSE);
	}
	
	if ((m_pFT3OutParaWidget != NULL) && (g_oSystemParas.m_nHasDigital))
	{
		m_pFT3OutParaWidget->SetGooseDisabled(FALSE);
	}
	EnableRadientType();
    InitEnableButtons();
}

PTMT_PARAS_HEAD QSttMacroParaEditViewSequenceGradient::CreateTestParas(const char * pszMacroID)
{
	PTMT_PARAS_HEAD pNewTest = new tmt_SequenceGradientTestEx;
	strcpy(pNewTest->m_oRsltExprMngr.m_pszExprGroupID, STT_RSLTEXPR_MACROID_COMMON);
	return pNewTest;
}

PTMT_PARAS_HEAD QSttMacroParaEditViewSequenceGradient::CreateTestParas(PTMT_PARAS_HEAD pCurr)
{
	ASSERT(pCurr != NULL);

	tmt_SequenceGradientTestEx* pCurrTest = (tmt_SequenceGradientTestEx*)pCurr;
	tmt_SequenceGradientTestEx* pNewTest = new tmt_SequenceGradientTestEx;

	memcpy(pNewTest,pCurrTest,sizeof(tmt_SequenceGradientTestEx));

	stt_clone_expr_mngr(pCurr, pNewTest);

 	pNewTest->m_nTestState = 0;
 	pNewTest->clear_result();

	return (PTMT_PARAS_HEAD)pNewTest;
}

void QSttMacroParaEditViewSequenceGradient::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
						long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	for (int i = 0; i < 3; i++)
	{
 		m_pCurPara->m_uiCUR[1][i].Harm[1].fAmp = m_pCurPara->m_uiCUR[0][i].Harm[1].fAmp;
		m_pCurPara->m_uiCUR[1][i].Harm[1].fAngle = m_pCurPara->m_uiCUR[0][i].Harm[1].fAngle;
 		m_pCurPara->m_uiCUR[1][i].Harm[1].fFreq = m_pCurPara->m_uiCUR[0][i].Harm[1].fFreq;
 		m_pCurPara->m_uiVOL[1][i].Harm[1].fAmp = m_pCurPara->m_uiVOL[0][i].Harm[1].fAmp;
 		m_pCurPara->m_uiVOL[1][i].Harm[1].fAngle = m_pCurPara->m_uiVOL[0][i].Harm[1].fAngle;
 		m_pCurPara->m_uiVOL[1][i].Harm[1].fFreq = m_pCurPara->m_uiVOL[0][i].Harm[1].fFreq;
	}

	tmt_sequence_gradient_test_ex *pGradientParas = (tmt_sequence_gradient_test_ex*)pParas;

	if(stt_xml_serialize_is_read(pMacroParas) || stt_xml_serialize_is_register(pMacroParas))
	{
		stt_xml_serialize_sequence_ex(&pGradientParas->m_oSequenceGradientParasEx, pMacroParas);	//文件的读写
	}
	else if (pParas->m_nSelected)
	{
		stt_xml_serialize_sequence_ex(&pGradientParas->m_oSequenceGradientParasEx, pMacroParas);	//测试参数下发
	}
	
// 	stt_xml_serialize_Sequence(&pGradientParas->m_oSequenceGradientParasEx, pMacroParas,
// 								&m_pCurPara->m_uiVOL[1][0], &m_pCurPara->m_uiVOL[1][1], &m_pCurPara->m_uiVOL[1][2],
// 								&m_pCurPara->m_uiCUR[1][0], &m_pCurPara->m_uiCUR[1][1], &m_pCurPara->m_uiCUR[1][2]);
	if (bHasGoosePub)
	{
		CIecCfgGoutDatas *pGoutDatas = m_listGoosePub.at(0);
		ASSERT(pGoutDatas);
		SerializeGoosePubs(pMacroParas,pGoutDatas);

		//chenling
		CIecCfgDatasSMV *pDatasSMV = m_listFT3Pub.at(0);
		ASSERT(pDatasSMV);
		SerializeFT3Pubs(pMacroParas,pDatasSMV);
	}
}

void QSttMacroParaEditViewSequenceGradient::OnViewTestLink(BOOL b)
{

}

void QSttMacroParaEditViewSequenceGradient::OnViewTestStart()
{
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	startInit();
	stt_Frame_ClearInfoWidget();

	//2024-8-27 wuxinyi 递变通道与状态图里递变通道序号不统一，故在此修改
	int nChIndex = 0;
	if (m_pCurPara->m_nChannel == v11_type)
	{
		nChIndex = va1_type;
	}
	else if (m_pCurPara->m_nChannel == v12_type)
	{
		nChIndex = vb1_type;
	}
	else if (m_pCurPara->m_nChannel == v10_type)
	{
		nChIndex = va2_type;
	}
	else if (m_pCurPara->m_nChannel == i11_type)
	{
		nChIndex = ia1_type;
	}
	else if (m_pCurPara->m_nChannel == i12_type)
	{
		nChIndex = ib1_type;
	}
	else if (m_pCurPara->m_nChannel == i10_type)
	{
		nChIndex = ic1_type;
	}

	stt_Frame_InitStateMonitor(nChIndex/*m_pCurPara->m_nChannel*/, m_pCurPara->m_nType, stt_Frame_IsTestStarted());
	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();
	stt_Frame_EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewSequenceGradient::OnViewTestStop()
{
	stopInit();
	stt_Frame_StopStateMonitor();
	stt_Frame_StopVectorWidget();
	stt_Frame_StopPowerWidget();
}


void QSttMacroParaEditViewSequenceGradient::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
{
	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();

	if(bIsNor == FALSE)
	{
 		QString strVar = ui->m_cbbVar->currentText();
 		int nIdx = ui->m_cbbVarType->currentIndex();
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

	if (str.right(1).contains("."))
	{
		str.append("000");
	}
}

void QSttMacroParaEditViewSequenceGradient::ShowReport(CDvmValues *pValues)
{
	//根据id获取值
	CDvmValue* pTripData = (CDvmValue*)pValues->FindByID("TripValue");
	CDvmValue* pReturnData = (CDvmValue*)pValues->FindByID("ReturnValue");
	CDvmValue* pCoefData = (CDvmValue*)pValues->FindByID("ReturnCoef");

	float fTripValue = 0, fReturnValue = 0, fReturnCoef = 0;

	if(pTripData != NULL)
	{
		fTripValue = GlobalSetResultValue(pTripData,3);
	}

	if(pReturnData != NULL)
	{
		fReturnValue = GlobalSetResultValue(pReturnData,3);
	}

	if(pCoefData != NULL)
	{
		fReturnCoef = GlobalSetResultValue(pCoefData,3);
	}

}

void QSttMacroParaEditViewSequenceGradient::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewSequenceGradient::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pCurPara, &oRead);//修改
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系
	}

	if (m_oSequenceGradientChs.GetCount() == 0)
	{
		if (g_oSttTestResourceMngr.m_pTestResouce != NULL)
		{
			g_oSttTestResourceMngr.m_pTestResouce->AddGradientChs_All(m_oSequenceGradientChs);
		}
	}

	stt_Frame_InitVectorWidget(m_pCurPara->m_uiVOL[0],m_pCurPara->m_uiCUR[0]);
	stt_Frame_InitPowerWidget(m_pCurPara->m_uiVOL[0],m_pCurPara->m_uiCUR[0]);
	stt_Frame_InitStateMonitor(true, NULL);
	stt_Frame_InitStateMonitor(m_pCurPara->m_nChannel, m_pCurPara->m_nType, stt_Frame_IsTestStarted(), this);
	stt_Frame_ClearInfoWidget();

	//初始化监视器等
	InitParas();

	UpdateGoutTab();
	UpdateFT3Tab();

	//切换界面时重新串行化出非递变通道界面
	if(m_pSequenceGradientWidget)
	{
		m_pSequenceGradientWidget->Update();//非递变通道中故障态和正常态更新链表数据

		CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oSequenceGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
		m_pSequenceGradientWidget->UpdateFaultEditState(pCurDataTypeValue);	
		
	}
}

CString QSttMacroParaEditViewSequenceGradient::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += FILE_GRADIENT; //文件名
	strFile += _T(".");
	strFile += POSTFIX_GRADIENT; //文件后缀

	return strFile;
}

bool QSttMacroParaEditViewSequenceGradient::IsValidTestParasFile(const CString& strParasFile,bool bOpen)
{
 	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != POSTFIX_GRADIENT)
 	{
 		return false;
 	} //文件后缀名判断是否正确

	if(bOpen && !IsFileExist(strParasFile))
	{
		return false;
	}

	return true;
}

void QSttMacroParaEditViewSequenceGradient::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateSequenceGradientChs();
	InitParas(); //重新初始化递变参数
	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();
	updateLabName();
	if (m_pSequenceGradientWidget)
	{
		m_pSequenceGradientWidget->InitData(m_pCurPara);
	}
}

void QSttMacroParaEditViewSequenceGradient::UpdateGoutTab(BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		InitGoosePubDataGroups();
		UpdateGoutTab_UI(m_listGoosePub.at(0));
	}
	else
	{
		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewSequenceGradient::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if ((m_pGooseParaWidget == NULL) && (g_oSystemParas.m_nHasDigital)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC> 0))//数字输出且无goose界面
	{
		AddGooseParaWidget(pCfgGoutDatas);
		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
	}
	else if ((m_pGooseParaWidget != NULL) && (!g_oSystemParas.m_nHasDigital))
	{
		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		RemoveGooseParaWidget();//更新后不需要goose界面
	}
	else if ((m_pGooseParaWidget != NULL) && (g_oSystemParas.m_nHasDigital))
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		m_pGooseParaWidget->initGoosePubTable(pCfgGoutDatas);
		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
	}
	else if ((m_pGooseParaWidget != NULL)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC == 0))//更新前有GOOSE界面,更新后LC口为0不需要
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewSequenceGradient::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
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
	//判断数字量输出类型以及FT3的界面
	if ((m_pFT3OutParaWidget == NULL) && (g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0) && (nFT3Block > 0))
	{
		AddFT3OutParaWidget(pIecCfgDatasSMV);
		connect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
	else if ((m_pFT3OutParaWidget != NULL) && (!g_oSystemParas.IsDigitalOutputFT3()))
	{
		disconnect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		RemoveFT3OutParaWidget();
	}
	else if ((m_pFT3OutParaWidget != NULL) && (g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0))
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

void QSttMacroParaEditViewSequenceGradient::UpdateFT3Tab(BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		InitFT3PubDataGroups();
		UpdateFT3Tab_UI(m_listFT3Pub.at(0));
	}
	else
	{
		RemoveFT3OutParaWidget();
	}
}

void QSttMacroParaEditViewSequenceGradient::UpdateBinBoutExTab()
{
	//暂无拓展开入开出
}

void QSttMacroParaEditViewSequenceGradient::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas, FALSE);
	int nInsertPos = 2;
	CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	ui->m_tabWidget->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewSequenceGradient::RemoveGooseParaWidget()
{
	if (m_pGooseParaWidget == NULL)
	{
		return;
	}
	int nIndex = ui->m_tabWidget->indexOf(m_pGooseParaWidget);
	ui->m_tabWidget->removeTab(nIndex);
	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QSttMacroParaEditViewSequenceGradient::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		ui->m_tabWidget->setTabEnabled(ui->m_tabWidget->indexOf(m_pGooseParaWidget),b);
	}

}

bool QSttMacroParaEditViewSequenceGradient::ExistGooseParaWidget()
{
	//获取ui界面中的goose界面，判断是否有该界面
	int nIndex = ui->m_tabWidget->indexOf(m_pGooseParaWidget);
	return (nIndex >= 0);

}

void QSttMacroParaEditViewSequenceGradient::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}
	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV, TRUE);
	
	int nInsertPos = 3;
	CString strTitle = _T("FT3发布");
	//在界面中插入FT3界面
	ui->m_tabWidget->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewSequenceGradient::RemoveFT3OutParaWidget()
{
	if (m_pFT3OutParaWidget == NULL)
	{
		return;
	}
	int nIndex = ui->m_tabWidget->indexOf(m_pFT3OutParaWidget);
	ui->m_tabWidget->removeTab(nIndex);//根据ui界面的tab获取
	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;

}
void QSttMacroParaEditViewSequenceGradient::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		ui->m_tabWidget->setTabEnabled(ui->m_tabWidget->indexOf(m_pGooseParaWidget),b);
	}

}
bool QSttMacroParaEditViewSequenceGradient::ExistFT3OutParaWidget()
{
	int nIndex = ui->m_tabWidget->indexOf(m_pFT3OutParaWidget);
	return (nIndex >= 0);

}

void QSttMacroParaEditViewSequenceGradient::on_m_cbbVar_currentIndexChanged(int index)
{
	if (ui->m_cbbVar->IsScrolling())
	{
		return;
	}

	if (m_pCurPara == NULL)
	{
		return;
	}

	disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	ui->m_cbbVarType->clear();
	ui->m_cbbVarType->addItems(m_ChangeTypeList);
	ui->m_cbbVarType->setCurrentIndex(m_pCurPara->m_nType);
	connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));

 	long nOldChannel = m_pCurPara->m_nChannel;//变量值

// 	if (index >= 3)
// 	{
// 		index += 3;
// 	}
 	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oSequenceGradientChs.GetAtIndex(index);
	if (!pCurDataTypeValue)
	{
		return;
	}
	g_SequenceGradientMain->m_bTmtParaChanged = TRUE;
	m_pCurPara->m_nChannel = pCurDataTypeValue->GetIndex();
	if (nOldChannel != m_pCurPara->m_nChannel)
	{
		InitUI_AfterSequenceGridentSel();
	}
// 	if (m_pCurPara->m_nChannel >= 0 && m_pCurPara->m_nChannel <= 5)
// 	{//电压
// 		m_pCurPara->m_nVarIndexType = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_nVarIndexType = 0;
// 	}

	if(SEQUENCE_CHANNAL_TYPE_I(m_pCurPara->m_nChannel))
	{
		m_pCurPara->m_nVarIndexType = 0;
	}
	else if(SEQUENCE_CHANNAL_TYPE_U(m_pCurPara->m_nChannel))
	{
		m_pCurPara->m_nVarIndexType = 1;
	}
 	m_pSequenceGradientWidget->UpdateFaultEditState(pCurDataTypeValue);

 	
	updateLabName();
}

void QSttMacroParaEditViewSequenceGradient::on_m_cbbVarType_currentIndexChanged(int index)
{
	if(ui->m_cbbVarType->IsScrolling())
	{
		return;
	}

	if (index == 1)//相位
	{
		initMaxEdit_one(ui->m_editInit);
		initMaxEdit_one(ui->m_editFinish);
		initMaxEdit_one(ui->m_editStep);
	}
	else
	{
		initMaxPositiveEdit(ui->m_editInit);
		initMaxPositiveEdit(ui->m_editFinish);
		initMaxPositiveEdit(ui->m_editStep);
	}

	m_pCurPara->m_nType = getChangeTypeByIndex(index);
	on_m_editInitChanged();
	on_m_editFinishChanged();
	on_m_editStepChanged();
	on_m_editTimeChanged();

	InitUI_AfterSequenceGridentSel();
	EnableRadientType();

	g_SequenceGradientMain->m_bTmtParaChanged = TRUE;

	int nIndex = ui->m_cbbVar->currentIndex();

// 	if (nIndex >= 3)
// 	{
// 		nIndex += 3 ;
// 	}
 	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oSequenceGradientChs.GetAtIndex(nIndex);
 	//CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oSequenceGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
 	//更新表格
 	m_pSequenceGradientWidget->UpdateFaultEditState(pCurDataTypeValue);
}

void QSttMacroParaEditViewSequenceGradient::on_m_cbbType_currentIndexChanged(int index)
{
	if(ui->m_cbbType->IsScrolling())
	{
		return;
	}

	if (m_pCurPara->m_nTestMode != index)
	{
		m_pCurPara->m_nTestMode = index;
		emit sig_Para_ReturnTypeIndexChanged(index);

		g_SequenceGradientMain->m_bTmtParaChanged = TRUE;
	}

	EnableRadientType();//失能递变方向
}
void QSttMacroParaEditViewSequenceGradient::on_m_cbbDirection_currentIndexChanged(int index)
{
	if(ui->m_cbbDirection->IsScrolling())
	{
		return;
	}

	if (m_pCurPara->m_nPhaseGradDir != index)
	{
		m_pCurPara->m_nPhaseGradDir = index;
		m_bTmtParaChanged = TRUE;
	}
}

void QSttMacroParaEditViewSequenceGradient::on_m_editTimeBeforeChangeChanged()//Zhouyy 2023/01/06
{
	if (ui->m_editTimeBeforeChange->text().isEmpty())
	{
		ui->m_editTimeBeforeChange->setText("0");
	}

	QString str = ui->m_editTimeBeforeChange->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}
	else if (fv>999.999)
	{
		fv = 999.999;
	}

	ui->m_editTimeBeforeChange->setText(QString::number(fv,'f',3));
	if(m_pCurPara->m_fPrepareTime!= ui->m_editTimeBeforeChange->text().toFloat())
	{
		m_pCurPara->m_fPrepareTime = ui->m_editTimeBeforeChange->text().toFloat();
		m_bTmtParaChanged = TRUE;
	}
}

void QSttMacroParaEditViewSequenceGradient::on_m_editTimeBeforeFailChanged()
{
	if (ui->m_editTimeBeforeFail->text().isEmpty())
	{
		ui->m_editTimeBeforeFail->setText("0");
	}

	QString str = ui->m_editTimeBeforeFail->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}
	else if (fv>999.999)
	{
		fv = 999.999;
	}

	ui->m_editTimeBeforeFail->setText(QString::number(fv,'f',3));
	if(m_pCurPara->m_fPreFaultTime != ui->m_editTimeBeforeFail->text().toFloat())
	{
		m_pCurPara->m_fPreFaultTime = ui->m_editTimeBeforeFail->text().toFloat();
		m_bTmtParaChanged = TRUE;
	}
	if(ui->m_editTimeBeforeFail->text().toFloat() < 0.0001)
	{
		m_pCurPara->m_fPreFaultTime = 0;
        ui->m_editTimeBeforeFail->setText(QString::number(0,'f',3));
        //chenling 2024.8.15 脉冲勾选，复归编辑框不应灰掉
        //ui->m_editTimeBeforeFail->setEnabled(false);
        //ui->m_cbBefore->setChecked(false);
	}
	ui->m_editTimeBeforeFail->setCursorPosition(0);
}

void QSttMacroParaEditViewSequenceGradient::slot_edit_changed2(QSttLineEdit* pEditLine, long nType)
{
	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();

	switch(nType)
	{
	case 0: GetWidgetBoard_DigitData(4,str,pEditLine, parentWidget()); break;
	case 1: GetWidgetBoard_DigitData(1,str,pEditLine,parentWidget()); break;
	case 2: GetWidgetBoard_DigitData(2,str,pEditLine,parentWidget()); break;
	default:
		break;
	}

	if (str.right(1).contains("."))
	{
		str.append("000");
	}
}


void QSttMacroParaEditViewSequenceGradient::on_m_cbBefore_clicked(int nState)
{
	if(nState)
	{
		ui->m_editTimeBeforeFail->setEnabled(true);
	}
	else
	{
		ui->m_editTimeBeforeFail->setText("0");
		ui->m_editTimeBeforeFail->setEnabled(false);
		m_pCurPara->m_fPreFaultTime = 0;
	}
}


void QSttMacroParaEditViewSequenceGradient::slot_Estimate()
{
	SequenceGradientEstimateDlg dlg(m_pCurPara, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewSequenceGradient::slot_SettingValue()
{
	GradientSettingValueDlg dlg(m_pCurPara, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewSequenceGradient::on_m_editInitChanged()
{
	QString str2 = ui->m_editInit->text();

	if (str2.right(1).contains("."))
	{
		str2.append("000");
	}

	long nMaxFreq = Global_GetMaxFreq();
	float fv= str2.toFloat();
	if (m_pCurPara->m_nType == amplitude_type)
	{
		QString str = ui->m_cbbVar->currentText();
		if (str.contains(tr("I")))
		{
			if (fabs(fv) > g_oLocalSysPara.m_fAC_CurMax)
			{
				if (fv > 0)
				{
					fv = g_oLocalSysPara.m_fAC_CurMax;
				}
				else
				{
					fv = -g_oLocalSysPara.m_fAC_CurMax;
				}
			}

			disconnect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
			{
				if (m_pCurPara->m_fStart != fv)
				{
					m_pCurPara->m_fStart = fv;
					emit sig_Para_StartChanged(fv);
					m_bTmtParaChanged = TRUE;
				}

				ui->m_editInit->setText(QString::number(fv,'f',3));

				//更新实时图Y坐标轴范围
				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDI,m_pCurPara->m_fG1Current,m_pCurPara->m_fG2Current,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strCurrent + "(A)",fdown/FRADIO,fup*FRADIO);
			}

			connect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
		}
		else if (str.contains(tr("U")))
		{
			if (fabs(fv) > g_oLocalSysPara.m_fAC_VolMax)
			{
				if (fv > 0)
				{
					fv = g_oLocalSysPara.m_fAC_VolMax;
				}
				else
				{
					fv = -g_oLocalSysPara.m_fAC_VolMax;
				}
			}

			disconnect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
			{
				if (m_pCurPara->m_fStart != fv)
				{
					m_pCurPara->m_fStart = fv;
					emit sig_Para_StartChanged(fv);
					m_bTmtParaChanged = TRUE;
				}

				ui->m_editInit->setText(QString::number(fv,'f',3));

				//更新实时图Y坐标轴范围
				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDU,m_pCurPara->m_fG1Volt,m_pCurPara->m_fG2Volt,m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strVoltage + "(V)",fdown/FRADIO,fup*FRADIO);
			}

			connect(ui->m_editInit, SIGNAL(editingFinished()), this, SLOT(slot_Para_StartChanged()));
		}
	}
	else if (m_pCurPara->m_nType == phasor_type)
	{
		float f1 = fv - (int)fv;
		int f2 = ((int)fv)%360;
		fv = f1+f2;

		disconnect(ui->m_editInit, SIGNAL(editingFinished()), this, SLOT(slot_Para_StartChanged()));
		{
			if (m_pCurPara->m_fStart != fv)
			{
				m_pCurPara->m_fStart = fv;
				emit sig_Para_StartChanged(fv);
				m_bTmtParaChanged = TRUE;
			}

			ui->m_editInit->setText(QString::number(fv,'f',1));
		}

		connect(ui->m_editInit, SIGNAL(editingFinished()), this, SLOT(slot_Para_StartChanged()));
	}
	else
	{
		if (fabs(fv) > nMaxFreq)
		{
			if (fv > 0)
			{
				fv = nMaxFreq;
			}
			else
			{
				fv = -nMaxFreq;
			}
		}
		else if(fv < 10)
		{
			fv = 10;
		}

		disconnect(ui->m_editInit, SIGNAL(editingFinished()), this, SLOT(slot_Para_StartChanged()));
		{
			if (m_pCurPara->m_fStart != fv)
			{
				m_pCurPara->m_fStart = fv;
				emit sig_Para_StartChanged(fv);
				m_bTmtParaChanged = TRUE;
			}

			ui->m_editInit->setText(QString::number(fv,'f',3));

			float fdown=0;
			float fup=0;
			getYRange(1,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
			emit sig_YRangeChanged(fre_type, m_strFreq + "(Hz)",fdown,fup*FRADIO);
		}

		connect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
	}
	int nIndex = ui->m_cbbVar->currentIndex();

// 	if (nIndex >= 3)
// 	{
// 		nIndex += 3 ;
// 	}
 	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oSequenceGradientChs.GetAtIndex(nIndex);
  	
 	//CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oSequenceGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
 	m_pSequenceGradientWidget->UpdateFaultEditState(pCurDataTypeValue);

}

void QSttMacroParaEditViewSequenceGradient::on_m_editFinishChanged()
{
	QString str2 = ui->m_editFinish->text();

	if (str2.right(1).contains("."))
	{
		str2.append("000");
	}

	float fv= str2.toFloat();
	long nMaxFreq = Global_GetMaxFreq();

	if (m_pCurPara->m_nType == amplitude_type)
	{
		QString str = ui->m_cbbVar->currentText();
		if (str.contains(tr("I")))
		{
			if (fabs(fv) > g_oLocalSysPara.m_fAC_CurMax)
			{
				if (fv > 0)
				{
					fv = g_oLocalSysPara.m_fAC_CurMax;
				}
				else
				{
					fv = -g_oLocalSysPara.m_fAC_CurMax;
				}
			}

			disconnect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
			{
				if (m_pCurPara->m_fStop != fv)
				{
					m_pCurPara->m_fStop = fv;
					emit sig_Para_EndChanged(fv);
					m_bTmtParaChanged = TRUE;
				}

				ui->m_editFinish->setText(QString::number(fv,'f',3));

				//更新实时图Y坐标轴范围
				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDI,m_pCurPara->m_fG1Current,m_pCurPara->m_fG2Current,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strCurrent + "(A)",fdown/FRADIO,fup*FRADIO);
			}

			//connect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
		}
		else if (str.contains(tr("U")))
		{
			if (fabs(fv) > g_oLocalSysPara.m_fAC_VolMax)
			{
				if (fv > 0)
				{
					fv = g_oLocalSysPara.m_fAC_VolMax;
				}
				else
				{
					fv = -g_oLocalSysPara.m_fAC_VolMax;
				}
			}

			disconnect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
			{
				if (m_pCurPara->m_fStop != fv)
				{
					m_pCurPara->m_fStop = fv;
					emit sig_Para_EndChanged(fv);
					m_bTmtParaChanged = TRUE;
				}

				ui->m_editFinish->setText(QString::number(fv,'f',3));

				//更新实时图Y坐标轴范围
				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDU,m_pCurPara->m_fG1Volt,m_pCurPara->m_fG2Volt,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strVoltage + "(V)",fdown/FRADIO,fup*FRADIO);
			}

			connect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
		}
	}
	else if (m_pCurPara->m_nType == phasor_type)
	{
		float f1 = fv - (int)fv;
		int f2 = ((int)fv)%360;
		fv = f1+f2;

		disconnect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
		{
			if (m_pCurPara->m_fStop != fv)
			{
				m_pCurPara->m_fStop = fv;
				emit sig_Para_EndChanged(fv);
				m_bTmtParaChanged = TRUE;
			}

			ui->m_editFinish->setText(QString::number(fv,'f',1));
		}

		connect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
	}
	else
	{
		if (fabs(fv) > nMaxFreq)
		{
			if (fv > 0)
			{
				fv = nMaxFreq;
			}
			else
			{
				fv = -nMaxFreq;
			}
		}
		else if(fv < 10)
		{
			fv = 10;
		}

		disconnect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
		{
			if (m_pCurPara->m_fStop != fv)
			{
				m_pCurPara->m_fStop = fv;
				emit sig_Para_EndChanged(fv);
				m_bTmtParaChanged = TRUE;
			}

			ui->m_editFinish->setText(QString::number(fv,'f',3));

			float fdown=0;
			float fup=0;
			getYRange(1,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
			emit sig_YRangeChanged(fre_type, m_strFreq + "(Hz)",fdown,fup*FRADIO);
		}

		connect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
	}
}

void QSttMacroParaEditViewSequenceGradient::on_m_editStepChanged()
{
	QString str = ui->m_editStep->text();

	if (str.right(1).contains("."))
	{
		str.append("000");
	}

	float fv= str.toFloat();
	long nMaxFreq = Global_GetMaxFreq();

	if (m_pCurPara->m_nType == amplitude_type)
	{
		QString str = ui->m_cbbVar->currentText();
		if (str.contains(tr("I")))
		{
			if (fabs(fv) > g_oLocalSysPara.m_fAC_CurMax)
			{
				if (fv > 0)
				{
					fv = g_oLocalSysPara.m_fAC_CurMax;
				}
				else
				{
					fv = -g_oLocalSysPara.m_fAC_CurMax;
				}
			}

			if (fv == 0)
			{
				fv = 0.001;
			}
			disconnect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
			{
				if(m_pCurPara->m_fStep != fv)
				{
					m_pCurPara->m_fStep = fv;
					emit sig_Para_StepChanged(fv);
					m_bTmtParaChanged = TRUE;
				}

				ui->m_editStep->setText(QString::number(fv,'f',3));
			}

			connect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
		}
		else if (str.contains(tr("U")))
		{
			if (fabs(fv) > g_oLocalSysPara.m_fAC_VolMax)
			{
				if (fv > 0)
				{
					fv = g_oLocalSysPara.m_fAC_VolMax;
				}
				else
				{
					fv = -g_oLocalSysPara.m_fAC_VolMax;
				}
			}

			if (fv == 0)
			{
				fv = 0.001;
			}
			disconnect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
			{
				if(m_pCurPara->m_fStep != fv)
				{
					m_pCurPara->m_fStep = fv;
					emit sig_Para_StepChanged(fv);
					m_bTmtParaChanged = TRUE;
				}

				ui->m_editStep->setText(QString::number(fv,'f',3));
			}

			connect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
		}
	}
	else if (m_pCurPara->m_nType == phasor_type)
	{
		float f1 = fv - (int)fv;
		int f2 = ((int)fv)%360;
		fv = f1+f2;
		if (fv == 0)
		{
			fv = 0.001;
		}

		disconnect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
		{
			if(m_pCurPara->m_fStep != fv)
			{
				m_pCurPara->m_fStep = fv;
				emit sig_Para_StepChanged(fv);
				m_bTmtParaChanged = TRUE;
			}

			ui->m_editStep->setText(QString::number(fv,'f',3));
		}

		connect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
	}
	else
	{
		if (fabs(fv) > nMaxFreq)
		{
			if (fv > 0)
			{
				fv = nMaxFreq;
			}
			else
			{
				fv = -nMaxFreq;
			}
		}

		if (fv == 0)
		{
			fv = 0.001;
		}

		disconnect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
		{
			if(m_pCurPara->m_fStep != fv)
			{
				m_pCurPara->m_fStep = fv;
				emit sig_Para_StepChanged(fv);
				m_bTmtParaChanged = TRUE;
			}

			ui->m_editStep->setText(QString::number(fv,'f',3));
		}

		connect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
	}
}

void QSttMacroParaEditViewSequenceGradient::on_m_editTimeChanged()
{
	QString str = ui->m_editTime->text();

	if (str.right(1).contains("."))
	{
		str.append("000");
	}

	float fv= str.toFloat();

	if (fv <= EPSINON)
	{
		ui->m_editTime->setText(QString::number(m_pCurPara->m_fStepTime, 'f', 3));
		return;
	}
	else if (fv > EPSINON && fv < 0.02)
	{
		fv = 0.02;
		m_pCurPara->m_fStepTime = fv;
		emit sig_Para_ErrorTimeChanged(fv);
		ui->m_editTime->setText(QString::number(m_pCurPara->m_fStepTime, 'f', 3));
	}
	else if (fv>999.999)
	{
		fv = 999.999;
		if (m_pCurPara->m_fStepTime != fv)
		{
			m_pCurPara->m_fStepTime = fv;
		    emit sig_Para_ErrorTimeChanged(fv);
			m_bTmtParaChanged = TRUE;
		}

		ui->m_editTime->setText(QString::number(m_pCurPara->m_fStepTime, 'f', 3));
	}
	else
	{
		if (m_pCurPara->m_fStepTime != fv)
		{
			m_pCurPara->m_fStepTime = fv;
			emit sig_Para_ErrorTimeChanged(fv);
			m_bTmtParaChanged = TRUE;
		}

		ui->m_editTime->setText(QString::number(m_pCurPara->m_fStepTime, 'f', 3));
	}
}

void QSttMacroParaEditViewSequenceGradient::on_m_editInit_clicked()
{
	slot_edit_changed(ui->m_editInit, TRUE);
}

void QSttMacroParaEditViewSequenceGradient::on_m_editFinish_clicked()
{
	slot_edit_changed(ui->m_editFinish, TRUE);
}

void QSttMacroParaEditViewSequenceGradient::on_m_editStep_clicked()
{
	slot_edit_changed(ui->m_editStep, TRUE);
}

void QSttMacroParaEditViewSequenceGradient::on_m_editTime_clicked()
{
	slot_edit_changed(ui->m_editTime, TRUE);
}

void QSttMacroParaEditViewSequenceGradient::on_m_editTimeBeforeChange_clicked()//鼠标响应部分
{
	slot_edit_changed2(ui->m_editTimeBeforeChange, 0);
}

void QSttMacroParaEditViewSequenceGradient::on_m_editTimeBeforeFail_clicked()
{
	slot_edit_changed2(ui->m_editTimeBeforeFail, 0);
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutA_StateChanged(int)
{
	if (ui->m_cbBinA->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[0].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[0].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();

}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutB_StateChanged(int)
{
	if (ui->m_cbBinB->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[1].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[1].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutC_StateChanged(int)
{
	if (ui->m_cbBinC->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[2].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[2].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();

}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutD_StateChanged(int)
{
	if (ui->m_cbBinD->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[3].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[3].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutE_StateChanged(int)
{
	if (ui->m_cbBinE->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[4].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[4].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutF_StateChanged(int)
{
	if (ui->m_cbBinF->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[5].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[5].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutG_StateChanged(int)
{
	if (ui->m_cbBinG->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[6].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[6].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutH_StateChanged(int)
{
	if (ui->m_cbBinH->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[7].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[7].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutI_StateChanged(int)
{
	if (ui->m_cbBinI->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[8].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[8].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_InPutJ_StateChanged(int)
{
	if (ui->m_cbBinJ->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[9].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[9].nSelect = 0;
	}

	CopyBinaryConfig(TRUE);
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewSequenceGradient::slot_radio_AndStateChanged(bool)
{
	if (ui->m_rbAnd->isChecked())
	{
		m_pCurPara->m_nBinLogic = 1;
	}	
}

void QSttMacroParaEditViewSequenceGradient::slot_radio_OrStateChanged(bool)
{
	if (ui->m_rbOr->isChecked())
	{
		m_pCurPara->m_nBinLogic = 0;
	}
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_OutPut1StateChanged(int)
{
	if (ui->m_cbBOut1->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binOut[0][0].nState = 1;
	}
	else
	{
		m_pCurPara->m_binOut[0][0].nState = 0;
	}
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_OutPut2StateChanged(int)
{
	if (ui->m_cbBOut2->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binOut[0][1].nState = 1;
	}
	else
	{
		m_pCurPara->m_binOut[0][1].nState = 0;
	}
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_OutPut3StateChanged(int)
{
	if (ui->m_cbBOut3->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binOut[0][2].nState = 1;
	}
	else
	{
		m_pCurPara->m_binOut[0][2].nState = 0;
	}
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_OutPut4StateChanged(int)
{
	if (ui->m_cbBOut4->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binOut[0][3].nState = 1;
	}
	else
	{
		m_pCurPara->m_binOut[0][3].nState = 0;
	}
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_OutPut1_EStateChanged(int)
{
	if (ui->m_cbBOut1_E->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binOut[1][0].nState = 1;
	}
	else
	{
		m_pCurPara->m_binOut[1][0].nState = 0;
	}
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_OutPut2_EStateChanged(int)
{
	if (ui->m_cbBOut2_E->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binOut[1][1].nState = 1;
	}
	else
	{
		m_pCurPara->m_binOut[1][1].nState = 0;
	}
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_OutPut3_EStateChanged(int)
{
	if (ui->m_cbBOut3_E->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binOut[1][2].nState = 1;
	}
	else
	{
		m_pCurPara->m_binOut[1][2].nState = 0;
	}
}

void QSttMacroParaEditViewSequenceGradient::slot_chb_OutPut4_EStateChanged(int)
{
	if (ui->m_cbBOut4_E->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binOut[1][3].nState = 1;
	}
	else
	{
		m_pCurPara->m_binOut[1][3].nState = 0;
	}
}

void QSttMacroParaEditViewSequenceGradient::on_m_btnManual_clicked()
{
	QSequenceGradientSettingDlg dlg(m_pCurPara, this);
	dlg.setWindowModality(Qt::WindowModal);//模态窗口
	CString strText;
	strText = /*"开出量设置"*/g_sLangTxt_Gradient_BoutSet;
    dlg.setWindowTitle(strText);
	dlg.exec();
	if (dlg.m_nIsOK == 1)
	{
		CopyBinaryConfig();
		stt_Frame_UpdateToolButtons();
		tmt_GradientParasEx* pSequenceGradientPara = m_pCurPara;
		ui->m_cbBOut1->setChecked(pSequenceGradientPara->m_binOut[0][0].nState);
		ui->m_cbBOut2->setChecked(pSequenceGradientPara->m_binOut[0][1].nState);
		ui->m_cbBOut3->setChecked(pSequenceGradientPara->m_binOut[0][2].nState);
		ui->m_cbBOut4->setChecked(pSequenceGradientPara->m_binOut[0][3].nState);
		ui->m_cbBOut1_E->setChecked(pSequenceGradientPara->m_binOut[1][0].nState);
		ui->m_cbBOut2_E->setChecked(pSequenceGradientPara->m_binOut[1][1].nState);
		ui->m_cbBOut3_E->setChecked(pSequenceGradientPara->m_binOut[1][2].nState);
		ui->m_cbBOut4_E->setChecked(pSequenceGradientPara->m_binOut[1][3].nState);
	}
}
