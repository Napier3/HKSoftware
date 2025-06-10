#include "SttMacroParaEditViewManual.h"
#include "ui_SttMacroParaEditViewManual.h"
#include "../../SmartCap/XSmartCapMngr.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
//#include "../../Module/SmartCap/X61850CapBase.h"
// #include "../../Engine/PpMeas/PpSttIotMeasServer.h"  //2022-10-5  lijunqing
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"
#include"../Module/XLangResource_Native.h"
#include "../State/ShortCalcuDig.h"
#include "../../RecordTest/UI/MUTest/SttMUTestIecCbSelWidget.h"
#include "../../RecordTest/UI/MUTest/SttIecRecordCbInterface.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewManual* g_pManualTest = NULL;
#define  STT_MODULE_L336D          "L336D"

QSttMacroParaEditViewManual::QSttMacroParaEditViewManual(QWidget *parent) :
    m_pManualTest_UI(new Ui::QSttMacroParaEditViewManual)
{
	m_pSetMUTestRpt_CheckBox = NULL;
	m_nIecFormatMeas = g_oSystemParas.m_nIecFormatMeas;
	m_nBCodeMode = g_oSystemParas.m_nBCodeMode;
	m_pRefresh_Button = NULL;
// 	m_pSttMUParasWidget = NULL;
	m_pSttMUTimeTestWidget = NULL;

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin QSttMacroParaEditViewManual -  >>");	}

    m_pManualTest_UI->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

#ifdef _PSX_QT_WINDOWS_
	setMaximumSize(QSize(5000, 5000));
#endif

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> ---------- QSttMacroParaEditViewManual -  1 >>");	}

	InitLanuage();

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> ---------- QSttMacroParaEditViewManual -  2 >>");	}

	m_bTmtParaChanged = FALSE;
	m_bIsChanging = FALSE;
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;
	//m_strParaFileTitle = "通用试验模板文件";
	m_strParaFileTitle = g_sLangTxt_State_Genexperfile;//通用试验模板文件 lcq 3.14
	m_strParaFilePostfix = "project(*.mntxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("ManualTest.mntxml");

	//先初始化Resource才能设置最大最小值
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
//	CreateTestResource();
	g_theTestCntrFrame->InitTestResource();

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> ---------- QSttMacroParaEditViewManual -  3 >>");	}

	m_pManualParas = &m_oManualTest.m_oManuParas;

	if (g_oSystemParas.m_nHasDigital)//zhouhj 在打开测试模板前先初始化当前GOOSE发布数据
	{
		InitGoosePubDataGroups();
		InitFT3PubDataGroups();
	}

	OpenTestTestMngrFile(m_strDefaultParaFile);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> ---------- QSttMacroParaEditViewManual -  4 >>");	}

	CopyBinaryConfig();
	//g_theTestCntrFrame->UpdateToolButtons();//QSttTestCntrFrameBase::OpenMacroTestUI_Test会再次重复刷新

	this->InitIVView();
	this->InitParasView();
	InitConnect();

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> ---------- QSttMacroParaEditViewManual -  5 >>");	}

	m_oParas.SetData(g_oSttTestResourceMngr.m_pTestResouce, m_pManualParas, 0);
	UpdateHarmCheckComboxUI(TRUE);

	if (m_oIV.m_pUIParaWidget)
	{
		m_oIV.m_pUIParaWidget->setMacroType(MACROTYPE_Manual);
		m_oIV.m_pUIParaWidget->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
		m_oIV.m_pUIParaWidget->setMaxMinAndEDVal();
		connect(m_oIV.m_pUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	}

	if (m_oIV.m_pHarmUIParaWidget)
	{
		m_oIV.m_pHarmUIParaWidget->setMacroType(MACROTYPE_ManualHarm);
		m_oIV.m_pHarmUIParaWidget->setHarmIndex(&m_pManualParas->m_nHarmIndex);
		m_oIV.m_pHarmUIParaWidget->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
		m_oIV.m_pHarmUIParaWidget->setMaxMinAndEDVal();
		connect(m_oIV.m_pHarmUIParaWidget,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);
	}

    g_pManualTest = this;

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> ---------- QSttMacroParaEditViewManual -  6 >>");	}

	SetDatas(NULL);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> ---------- QSttMacroParaEditViewManual -  7 >>");	}

	//QSttTestCntrFrameLinux::UpdateButtonsStateByID()刷新,重复调用
	//g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end QSttMacroParaEditViewManual -  >>");	}

	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		m_pManualTest_UI->m_tabWidget->setCurrentIndex(0);
	}
	else if ((m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUTimingAccur)||(m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUPunctAccur))
	{
		m_pManualTest_UI->m_tabWidget->setCurrentIndex(1);
	}
	
}

void QSttMacroParaEditViewManual::InitLanuage()
{
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_btnLock, "Manual_Lock", XLang_Ctrls_QPushButton);
	//xlang_SetLangStrToWidget(m_pManualTest_UI->m_labAction, "Native_Action", XLang_Ctrls_QLabel);
	//xlang_SetLangStrToWidget(m_pManualTest_UI->m_labReturn, "Native_ReturnVal", XLang_Ctrls_QLabel);
	//xlang_SetLangStrToWidget(m_pManualTest_UI->m_labActionTime, "Manual_ActionTime", XLang_Ctrls_QLabel);
	//xlang_SetLangStrToWidget(m_pManualTest_UI->m_labReturnTime, "Manual_ReturnTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_labChannel, "Manual_Channel", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_labFinishVal, "Manual_FinishVal", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_labInitVal, "Manual_InitVal", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_labChangeType, "Manual_ChangeType", XLang_Ctrls_QLabel);
//	xlang_SetLangStrToWidget(m_pManualTest_UI->m_labDelayed, "Manual_Delayed", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_labStep, "Manual_Step", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_labTime, "Manual_Timer", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbOld, "Manual_Old", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbAuto, "Manual_Auto", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbDC, "Native_DC", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_btnShortCalcu, "State_ShortCalc", XLang_Ctrls_QPushButton);
//	m_pManualTest_UI->m_btnShortCalcu->setText("短路\n计算");
	/*xlang_SetLangStrToWidget(m_pManualTest_UI->m_btnInBinaryOutSet, "Manual_OutSetting", XLang_Ctrls_QPushButton);*/
	xlang_SetLangStrToWidget_Txt(m_pManualTest_UI->m_btnDiffCalc,g_sLangTxt_State_Difflowcalculation,XLang_Ctrls_QPushButton);//差流计算-LCQ
    xlang_SetLangStrToWidget_Txt(m_pManualTest_UI->m_btnInBinaryOutSet,g_sLangTxt_Native_Switch,XLang_Ctrls_QPushButton);//开关量设置-LCQ
	
	xlang_SetLangStrToWidget_Txt(m_pManualTest_UI->m_btnEstimate,g_sLangTxt_State_Estimate,XLang_Ctrls_QPushButton);//整定及结果评估cl20230724

	/*xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbOut1, "Manual_Out1", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbOut2, "Manual_Out2", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbOut3, "Manual_Out3", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbOut4, "Manual_Out4", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbOut5, "Manual_Out5", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbOut6, "Manual_Out6", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbOut7, "Manual_Out7", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbOut8, "Manual_Out8", XLang_Ctrls_QCheckBox);*/

#ifdef _PSX_QT_LINUX_
	m_pManualTest_UI->m_cbOld->setDisabled(true);//zhouhj 在脱机模式下,固定将老化不可编辑
#endif

	/*CString strText;
	xlang_GetLangStrByFile(strText, "Native_BoutX");
	m_pManualTest_UI->m_cbOut9->setText(strText + "9");
	m_pManualTest_UI->m_cbOut10->setText(strText + "10");*/

	xlang_SetLangStrToWidget(m_pManualTest_UI->m_layoutIV, "Manual_IV", XLang_Ctrls_QTabWidget);
//	xlang_SetLangStrToWidget(m_pManualTest_UI->m_layoutOther, "Manual_OtherParam", XLang_Ctrls_QTabWidget);
//	xlang_SetLangStrToWidget(m_pManualTest_UI->m_boxChanging, "Manual_Changing", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_boxOutSetting, "Manual_OutSetting", XLang_Ctrls_QGroupBox);

	/*xlang_SetLangStrToWidget(m_pManualTest_UI->m_rdAnd, "Native_LogicAnd", XLang_Ctrls_QRadioButton);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_rdOr, "Native_LogicOr", XLang_Ctrls_QRadioButton);

	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbInA, "Manual_InA", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbInB, "Manual_InB", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbInC, "Manual_InC", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbInD, "Manual_InD", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbInE, "Manual_InE", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbInF, "Manual_InF", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbInG, "Manual_InG", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(m_pManualTest_UI->m_cbInH, "Manual_InH", XLang_Ctrls_QCheckBox);
	//xlang_SetLangStrToWidget(m_pManualTest_UI->m_layoutButtom, "Manual_layoutButtom", XLang_Ctrls_QTabWidget);

	xlang_GetLangStrByFile(strText, "Native_BinX");
	m_pManualTest_UI->m_cbInI->setText(strText + "I");
	m_pManualTest_UI->m_cbInJ->setText(strText + "J");

	xlang_SetLangStrToWidget(m_pManualTest_UI->m_boxInSetting, "Manual_InSetting", XLang_Ctrls_QGroupBox);*/
}

QSttMacroParaEditViewManual::~QSttMacroParaEditViewManual()
{
// 	if(m_pManualParas->m_nFuncType)
// 	{
// 		CXSmartCapMngr::Release();
// 	}
    delete m_pManualTest_UI;
}

void QSttMacroParaEditViewManual::SendUpdateParameter()
{
	g_theTestCntrFrame->Ats_UpdateParameter();
}

void QSttMacroParaEditViewManual::CopyBinaryConfig(BOOL b)
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

void QSttMacroParaEditViewManual::InitConnect()
{
	connect(&m_oParas, SIGNAL(sig_ChannelTableItemValue(QString,float,int,int,bool)),this,SLOT(slot_ChannelTableItemValue(QString,float,int,int,bool)),Qt::UniqueConnection);
	connect(m_pManualTest_UI->m_editTime, SIGNAL(clicked()), this, SLOT(on_m_editTimeChanged()));
	connect(m_pManualTest_UI->m_editStep, SIGNAL(clicked()), this, SLOT(on_m_editStepChanged()));
	connect(m_pManualTest_UI->m_editIintVal, SIGNAL(clicked()), this, SLOT(on_m_editInitValueChanged()));
	connect(m_pManualTest_UI->m_editFinishVal, SIGNAL(clicked()), this, SLOT(on_m_editFinishValueChanged()));
	connect(m_pManualTest_UI->m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
//	connect(m_pManualTest_UI->m_editDelayed, SIGNAL(clicked()), this, SLOT(on_m_editDelayChanged()));

	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		connect(m_pHarm_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_HarmCheck_stateChanged(int)));
		connect(m_pHarm_ComboBox, SIGNAL(currentIndexChanged (int)), this, SLOT(slot_cmbHarm_SelChanged(int)));
		
		connect(m_pTestMethod_ComboBox, SIGNAL(currentIndexChanged (int)), this, SLOT(slot_cbbTestMethod_currentIndexChanged(int)));
		connect(m_pMeasType_ComboBox, SIGNAL(currentIndexChanged (int)), this, SLOT(slot_cbbMeasType_currentIndexChanged(int)));
		connect(m_pBCode_ComboBox, SIGNAL(currentIndexChanged (int)), this, SLOT(slot_cbbBCode_currentIndexChanged(int)));

#ifdef _PSX_QT_LINUX_
		connect(m_pMUAccuracyTestNum_Edit, SIGNAL(clicked()), this, SLOT(slot_editTestNumChanged()));
		connect(m_pMUTestTime_Edit, SIGNAL(clicked()), this, SLOT(slot_editTestTimeChanged()));

#endif
		connect(m_pMUAccuracyTestNum_Edit, SIGNAL(editingFinished()), this, SLOT(slot_editTestNumFinished()));
		connect(m_pMUTestTime_Edit, SIGNAL(editingFinished()), this, SLOT(slot_editTestTimeFinished()));

		connect(m_pSetMUTestRpt_CheckBox, SIGNAL(clicked()), this, SLOT(slot_OnTestCheckChanged()));
		connect(m_pRefresh_Button, SIGNAL(clicked()), this, SLOT(slot_RefreshClicked()));
		
		for (int nIndex = 0;nIndex<10;nIndex++)
		{
			connect(m_pOutCheckBox[nIndex], SIGNAL(clicked()), this, SLOT(slot_OnOutCheckChanged()));
		}

	}
// 
// 	if (m_pSttMUParasWidget != NULL)
// 	{
// 		connect(m_pSttMUParasWidget, SIGNAL(sig_updataParas()), this, SLOT(slot_updateParas()));
// 	}

	if (m_pSttMUTimeTestWidget != NULL)
	{
		connect(m_pSttMUTimeTestWidget, SIGNAL(sig_updataParas()), this, SLOT(slot_updateParas()));
	}

	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas()));
//	connect(this, SIGNAL(sig_UpdateMUTimeAccurRlt_PPS()), this,SLOT(slot_UpdateMUTimeAccurRlt_PPS()));

	connect(m_pManualTest_UI->m_btnEstimate,SIGNAL(clicked()),this,SLOT(slot_Estimate()));

// 	connect(g_theTestCntrFrame, SIGNAL(sig_UpdateAuxDCEdit()), this,SLOT(slot_UpdateUdcEditEnabled()));
 
}
void QSttMacroParaEditViewManual::UpdateAuxDCEdit()
{
	m_oParas.slot_UpdateUdcEditEnabled();
}

void QSttMacroParaEditViewManual::slot_HarmCheck_stateChanged(int nState)
{
	m_pManualParas->m_nSelHarm = nState;
	m_oParas.m_pComboBoxHarm->setEnabled(nState);

	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_oIV.m_pHarmUIParaWidget->setEnabled(nState);
	}

	emit sig_updataParas();
}

void QSttMacroParaEditViewManual::slot_cmbHarm_SelChanged(int nCurrIndex)
{
	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_pManualParas->m_nHarmIndex = nCurrIndex+2;
		m_oIV.m_pHarmUIParaWidget->initData();
		emit sig_updataParas();
	}
}

void QSttMacroParaEditViewManual::slot_currentChangedTabWidget(int nCurrIndex)
{
	if (m_pManualParas == NULL)
	{
		return;
	}

	if (m_pManualParas->m_nFuncType != TMT_MANU_FUNC_TYPE_Common)
	{
		return;
	}

	//判断当前页面
	BOOL bVisibleBottomCtrlsGoose = (m_pGooseParaWidget == m_pManualTest_UI->m_tabWidget->currentWidget());
	BOOL bVisibleBottomCtrlsFT3 = (m_pFT3OutParaWidget == m_pManualTest_UI->m_tabWidget->currentWidget());

    BOOL bVisibleBottomCtrls=!(bVisibleBottomCtrlsGoose || bVisibleBottomCtrlsFT3);

	m_pManualTest_UI->m_frmOtherPara->setVisible(bVisibleBottomCtrls);
	m_pManualTest_UI->m_boxOutSetting->setVisible(bVisibleBottomCtrls);
	m_pManualTest_UI->m_cbOld->setVisible(bVisibleBottomCtrls);
	m_pManualTest_UI->m_cbDC->setVisible(bVisibleBottomCtrls);
	m_pManualTest_UI->m_btnLock->setVisible(bVisibleBottomCtrls);
	m_pManualTest_UI->m_btnAdd->setVisible(bVisibleBottomCtrls);
	m_pManualTest_UI->m_btnMinus->setVisible(bVisibleBottomCtrls);
	m_pManualTest_UI->m_btnInBinaryOutSet->setVisible(bVisibleBottomCtrls);
	m_pManualTest_UI->m_btnShortCalcu->setVisible(bVisibleBottomCtrls); 
	m_pManualTest_UI->m_btnDiffCalc->setVisible(bVisibleBottomCtrls);
	m_pManualTest_UI->m_btnEstimate->setVisible(bVisibleBottomCtrls);


	if (bVisibleBottomCtrls)
	{
		m_pManualTest_UI->horizontalSpacer_4->changeSize(37, 39, QSizePolicy::Minimum, QSizePolicy::Minimum);
		m_pManualTest_UI->horizontalSpacer_5->changeSize(37, 38, QSizePolicy::Minimum, QSizePolicy::Minimum);
		m_pManualTest_UI->gridLayout_2->update();

		//m_pManualTest_UI->horizontalSpacer_3->changeSize(50, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
		m_pManualTest_UI->horizontalLayout->update();
		m_pManualTest_UI->horizontalLayout_4->update();
	} 
	else
	{
		m_pManualTest_UI->horizontalSpacer_4->changeSize(0,0);
		m_pManualTest_UI->horizontalSpacer_5->changeSize(0,0);
		m_pManualTest_UI->gridLayout_2->update();

		//m_pManualTest_UI->horizontalSpacer_3->changeSize(0,0);
		m_pManualTest_UI->horizontalLayout_4->update();
	}
}

CSttTestResourceBase* QSttMacroParaEditViewManual::CreateTestResource()
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

void QSttMacroParaEditViewManual::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
									long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	//yzj 2022-2-21 开始测试前要保持该值为0
	if(!g_theTestCntrFrame->IsTestStarted())
	{
		m_pManualParas->m_bBinStop = FALSE;
	}

	tmt_manual_test *pTmtManualTest = (tmt_manual_test *)pParas;

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

void QSttMacroParaEditViewManual::OnTestResults(CDataGroup *pResults)
{
	ASSERT(pResults != NULL);

	m_oManualTest.m_nTestState = 1;	//测试完成

	/*此处替换成新的报文结构解析,需要解析出指定的返回值
	CSttDataGroupSerializeRead oRead(pResults);
	stt_xml_serialize(&m_oManualTest.m_oManuResult, &oRead);
	*/

	//刷新返回结果
	//m_oParas.UpdateResult(m_oManualTest.m_oManuResult.m_fActValue,m_oManualTest.m_oManuResult.m_fTripTime
	//	,m_oManualTest.m_oManuResult.m_fReturnValue,m_oManualTest.m_oManuResult.m_fReturnTime);
}

void QSttMacroParaEditViewManual::InitBinaryInBinaryOutUI()
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

void QSttMacroParaEditViewManual::SetManualOtherParasFont()
{
//	m_pManualTest_UI->groupBox->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_boxOutSetting->setFont(*g_pSttGlobalFont);
//	m_pManualTest_UI->m_boxChanging->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_labChannel->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbbChannel->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_editIintVal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_labInitVal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_labFinishVal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_editFinishVal->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbbSelect->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_labStep->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_labTime->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_editStep->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_editTime->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbAuto->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_labChangeType->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbbChangeType->setFont(*g_pSttGlobalFont);
	/*m_pManualTest_UI->m_boxInSetting->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInD->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInC->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInA->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInB->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_rdOr->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_rdAnd->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInE->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInF->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInG->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInH->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInI->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbInJ->setFont(*g_pSttGlobalFont);*/
	m_pManualTest_UI->m_cbOut3->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbOut4->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbOut2->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbOut1->setFont(*g_pSttGlobalFont);
	/*m_pManualTest_UI-> m_cbOut5->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbOut6->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbOut7->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbOut8->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbOut9->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbOut10->setFont(*g_pSttGlobalFont);*/
//	m_pManualTest_UI->m_editDelayed->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbDC->setFont(*g_pSttGlobalFont);
//	m_pManualTest_UI->m_labDelayed->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_cbOld->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_btnLock->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_btnAdd->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_btnMinus->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_comboBoxHarm->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_checkBoxHarm->setFont(*g_pSttGlobalFont);

	m_pManualTest_UI->m_btnShortCalcu->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_btnDiffCalc->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_btnInBinaryOutSet->setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_btnEstimate->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewManual::VisibleCtrlsByFuncType()
{
	if (m_pManualParas == NULL)
	{
		return;
	}

	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{

		m_pManualTest_UI->m_frmOtherPara->setVisible(false);
		m_pManualTest_UI->m_boxOutSetting->setVisible(false);
		m_pManualTest_UI->horizontalSpacer_4->changeSize(0,0);
		m_pManualTest_UI->horizontalSpacer_5->changeSize(0,0);
		m_pManualTest_UI->gridLayout_2->update();
	
		m_pManualTest_UI->m_btnShortCalcu->setVisible(false);
		m_pManualTest_UI->m_btnDiffCalc->setVisible(false);
		m_pManualTest_UI->m_btnInBinaryOutSet->setVisible(false);

		m_pManualTest_UI->m_cbOld->setVisible(false);
		m_pManualTest_UI->m_cbDC->setVisible(false);
		m_pManualTest_UI->m_btnLock->setVisible(false);
		m_pManualTest_UI->m_btnAdd->setVisible(false);
		m_pManualTest_UI->m_btnMinus->setVisible(false);
		m_pManualTest_UI->m_btnInBinaryOutSet->setVisible(false);
		m_pManualTest_UI->m_btnEstimate->setVisible(false);

//		m_pManualTest_UI->horizontalSpacer_3->changeSize(0,0);
		m_pManualTest_UI->horizontalLayout->update();

		m_pManualTest_UI->m_tabWidget->raise();


	}
	else if (m_pManualParas->m_nFuncType >= TMT_MANU_FUNC_TYPE_MUTimingAccur)
	{
		m_pManualTest_UI->m_frmOtherPara->setVisible(false);
		m_pManualTest_UI->m_boxOutSetting->setVisible(false);
		m_pManualTest_UI->m_cbOld->setVisible(false);
		m_pManualTest_UI->m_cbDC->setVisible(false);
		m_pManualTest_UI->m_btnLock->setVisible(false);
		m_pManualTest_UI->m_btnAdd->setVisible(false);
		m_pManualTest_UI->m_btnMinus->setVisible(false);
		m_pManualTest_UI->m_btnInBinaryOutSet->setVisible(false);
		m_pManualTest_UI->m_btnShortCalcu->setVisible(false);
		m_pManualTest_UI->m_btnDiffCalc->setVisible(false);
		m_pManualTest_UI->m_btnEstimate->setVisible(false);

		m_pManualTest_UI->horizontalSpacer_4->changeSize(0,0);
		m_pManualTest_UI->horizontalSpacer_5->changeSize(0,0);
		m_pManualTest_UI->gridLayout_2->update();

// 		m_pManualTest_UI->horizontalSpacer_3->changeSize(0,0);
		m_pManualTest_UI->horizontalLayout->update();
 		//m_pManualTest_UI->horizontalLayout_4->update();
		m_pManualTest_UI->m_tabWidget->raise();
	}

	CString strModel,strL336DName;
	strModel = g_oSttSystemConfig.GetDevModel();
	strL336DName = strModel.Left(5);

	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;

	if (strL336DName == STT_MODULE_L336D  || pCurDevice->m_strModel.Find(_T("PTU200L")) >= 0)
	{
		g_theTestCntrFrame->UpDateUdcVal();
	}
	else
	{
		m_pManualTest_UI->m_editUdc->hide();
		m_pManualTest_UI->m_labUdc->hide();
	}
}

void QSttMacroParaEditViewManual::InitOtherParasUI()
{
	SetManualOtherParasFont();
//	m_pManualTest_UI->m_tabWidget->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");

	/*if (m_pManualParas->m_nFuncType != TMT_MANU_FUNC_TYPE_Common)
	{
		m_pManualTest_UI->m_tabWidget->removeTab(m_pManualTest_UI->m_tabWidget->indexOf(m_pManualTest_UI->m_layoutOther));
	} */

//	m_pManualTest_UI->m_tabWidget->setTabEnabled(m_pManualTest_UI->m_tabWidget->indexOf(m_pManualTest_UI->m_layoutOther),m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_Common);

	// 2023=05=29 suyang 根据提供的新界面需求，不需要 其它参数设置
// 	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
// 	{
// 		if (m_pSttMUParasWidget == NULL)
// 		{
// 			m_pSttMUParasWidget = new QSttMUParasWidget(&m_bTmtParaChanged,this);
// 			m_pSttMUParasWidget->setFont(*g_pSttGlobalFont);
// 			CString strTmp;
// 			xlang_GetLangStrByFile(strTmp,"Manual_OtherParam");
// 			m_pManualTest_UI->m_tabWidget->insertTab(2,m_pSttMUParasWidget,strTmp);
// 		}
// 	}

	 if (m_pManualParas->m_nFuncType >= TMT_MANU_FUNC_TYPE_MUTimingAccur)
	{
		if (m_pSttMUTimeTestWidget == NULL)
		{
			m_pSttMUTimeTestWidget = new QSttMUTimeTestWidget(&m_bTmtParaChanged,this);
			CString strTmp;
			xlang_GetLangStrByFile(strTmp,"Manual_OtherParam");
			m_pManualTest_UI->m_tabWidget->insertTab(1,m_pSttMUTimeTestWidget,strTmp);
		}
	}

	VisibleCtrlsByFuncType();
}


void QSttMacroParaEditViewManual::UpdateTestResource(BOOL bCreateChMaps)
{
	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		m_nIecFormatMeas = g_oSystemParas.m_nIecFormatMeas;
		m_nBCodeMode = g_oSystemParas.m_nBCodeMode;

		if (m_pSetMUTestRpt_CheckBox != NULL)
		{
			m_pMeasType_ComboBox->setCurrentIndex(m_nIecFormatMeas);
			m_pBCode_ComboBox->setCurrentIndex(m_nBCodeMode);
		}
	}

	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();

// 	if (m_pSttMUParasWidget != NULL)
// 	{
// 		m_pSttMUParasWidget->UpdateUI();
// 	}

	if (m_pSttMUTimeTestWidget != NULL)
	{
		m_pSttMUTimeTestWidget->UpdateUI();
	}

	m_oIV.m_pUIParaWidget->initUI(g_theTestCntrFrame->GetSttTestResource());
	m_oIV.m_pUIParaWidget->initData();
	m_oIV.m_pUIParaWidget->setMaxMinAndEDVal();

	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_oIV.m_pHarmUIParaWidget->initUI(g_theTestCntrFrame->GetSttTestResource());
		m_oIV.m_pHarmUIParaWidget->initData();
		m_oIV.m_pHarmUIParaWidget->setMaxMinAndEDVal();
	}

	m_oParas.SetData(g_theTestCntrFrame->GetSttTestResource(), m_pManualParas, 0);
	UpdateHarmCheckComboxUI(TRUE);
	InitBinaryInBinaryOutUI();

// 	if(g_nBinCount == 8)
// 	{
// 		m_oParas.m_pCbInI->setChecked(false);
// 		m_oParas.m_pCbInJ->setChecked(false);
// 		m_oParas.m_pCbInI->setEnabled(false);
// 		m_oParas.m_pCbInJ->setEnabled(false);
// 	}
// 	else
// 	{
// 		m_oParas.m_pCbInI->setChecked(m_pManualParas->m_binIn[8].nSelect);
// 		m_oParas.m_pCbInJ->setChecked(m_pManualParas->m_binIn[9].nSelect);
// 		m_oParas.m_pCbInI->setEnabled(true);
// 		m_oParas.m_pCbInJ->setEnabled(true);
// 	}
// 
// 	if(g_nBoutCount == 8)
// 	{
// 		m_oParas.m_pCbOut9->setChecked(false);
// 		m_oParas.m_pCbOut10->setChecked(false);
// 		m_oParas.m_pCbOut9->setEnabled(false);
// 		m_oParas.m_pCbOut10->setEnabled(false);
// 	}
// 	else
// 	{
// 		m_oParas.m_pCbOut9->setChecked(m_pManualParas->m_binOut[8].nState);
// 		m_oParas.m_pCbOut10->setChecked(m_pManualParas->m_binOut[9].nState);
// 		m_oParas.m_pCbOut9->setEnabled(true);
// 		m_oParas.m_pCbOut10->setEnabled(true);
// 	}
}

// void QSttMacroParaEditViewManual::UpdateRtSyncTime(CDataGroup *pRtSycTime)
// {
// 	if (m_pSttMUTimeTestWidget == NULL)
// 	{
// 		return;
// 	}
// 
// 	if ((m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUTimingAccur)||(m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUPunctAccur))
// 	{
// 		m_pSttMUTimeTestWidget->UpdateMUTimeAccurRlt(pRtSycTime);
// 	}
// }

void QSttMacroParaEditViewManual::UpdateFT3Tab(BOOL bUpdateList)
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

void QSttMacroParaEditViewManual::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
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
// 		disconnect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
// 		m_pFT3OutParaWidget->InitFT3Table(pIecCfgDatasSMV);
// 		connect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));

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
void QSttMacroParaEditViewManual::UpdateGoutTab(BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)//zhouhj 在打开测试模板前先初始化当前GOOSE发布数据
	{
		//2023/11/27 wangjs 修改传出的pCfgGoutDatas值
		InitGoosePubDataGroups();
		UpdateGoutTab_UI(m_listGoosePub.at(0));
	}
	else
	{
		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewManual::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
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

void QSttMacroParaEditViewManual::slot_FT3DataChanged()
{
	if (g_theTestCntrFrame->IsTestStarted())
	{		
		slot_updateParas();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewManual::slot_GooseDataChanged()
{
	if (g_theTestCntrFrame->IsTestStarted())
	{		
		slot_updateParas();
//		emit sig_updataParas();
	}
// 	else
// 	{
// 		m_bIECParasChanged = TRUE;
// 	}

	SetParaChanged();
}

void QSttMacroParaEditViewManual::UpdateBinBoutExTab()
{
	//当前页面无拓展开入开出
}

void QSttMacroParaEditViewManual::UpdateManualParas(bool bUpdateParasData)
{
	m_oIV.m_pUIParaWidget->initData();

	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_oIV.m_pHarmUIParaWidget->initData();
	}

	if (m_pManualParas->m_bDC)
	{
		m_oIV.m_pUIParaWidget->DCStateChanged(P_Common, true);
	}

	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		UpdateMUAccurData();
	}
	
	if (bUpdateParasData)
	{
	m_oParas.UpdateData();
	}
	UpdateHarmCheckComboxUI(FALSE);
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewManual::ClearResult(PTMT_PARAS_HEAD pHead)
{
	m_oManualTest.m_oManuResult.init();
}

void QSttMacroParaEditViewManual::InitStyle()
{
	/*((QSttCheckBox*)m_pManualTest_UI->m_cbInA)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbInB)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbInC)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbInD)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbInE)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbInF)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbInG)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbInH)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbInI)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbInJ)->InitStyleSheet();*/
	((QSttCheckBox*)m_pManualTest_UI->m_cbOld)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbAuto)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbDC)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbOut1)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbOut2)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbOut3)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbOut4)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_checkBoxHarm)->InitStyleSheet();
	/*((QSttCheckBox*)m_pManualTest_UI->m_cbOut5)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbOut6)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbOut7)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbOut8)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbOut9)->InitStyleSheet();
	((QSttCheckBox*)m_pManualTest_UI->m_cbOut10)->InitStyleSheet();*/

	((QSttTabWidget*)m_pManualTest_UI->m_tabWidget)->InitStyleSheet();

}

void QSttMacroParaEditViewManual::InitParasView()
{
	InitStyle();
//    m_oParas.m_pEditDelayed = m_pManualTest_UI->m_editDelayed;
    m_oParas.m_pEditStep = m_pManualTest_UI->m_editStep;
    m_oParas.m_pEditInitVal = m_pManualTest_UI->m_editIintVal;
	m_oParas.m_pEditFinishVal = m_pManualTest_UI->m_editFinishVal;
    m_oParas.m_pEditTime = m_pManualTest_UI->m_editTime;
	m_oParas.m_pEditUdc = m_pManualTest_UI->m_editUdc;
    m_oParas.m_pCbbChannel = m_pManualTest_UI->m_cbbChannel;
    m_oParas.m_pCbbSelect = m_pManualTest_UI->m_cbbSelect;
    m_oParas.m_pCbbChangeType = m_pManualTest_UI->m_cbbChangeType;
    m_oParas.m_pCbOut1 = m_pManualTest_UI->m_cbOut1;
    m_oParas.m_pCbOut2 = m_pManualTest_UI->m_cbOut2;
    m_oParas.m_pCbOut3 = m_pManualTest_UI->m_cbOut3;
    m_oParas.m_pCbOut4 = m_pManualTest_UI->m_cbOut4;
    /*m_oParas.m_pCbOut5 = m_pManualTest_UI->m_cbOut5;
    m_oParas.m_pCbOut6 = m_pManualTest_UI->m_cbOut6;
    m_oParas.m_pCbOut7 = m_pManualTest_UI->m_cbOut7;
    m_oParas.m_pCbOut8 = m_pManualTest_UI->m_cbOut8;
	m_oParas.m_pCbOut9 = m_pManualTest_UI->m_cbOut9;
	m_oParas.m_pCbOut10 = m_pManualTest_UI->m_cbOut10;
	m_oParas.m_pCbInA = m_pManualTest_UI->m_cbInA;
	m_oParas.m_pCbInB = m_pManualTest_UI->m_cbInB;
	m_oParas.m_pCbInC = m_pManualTest_UI->m_cbInC;
	m_oParas.m_pCbInD = m_pManualTest_UI->m_cbInD;
	m_oParas.m_pCbInE = m_pManualTest_UI->m_cbInE;
	m_oParas.m_pCbInF = m_pManualTest_UI->m_cbInF;
	m_oParas.m_pCbInG = m_pManualTest_UI->m_cbInG;
	m_oParas.m_pCbInH = m_pManualTest_UI->m_cbInH;
	m_oParas.m_pCbInI = m_pManualTest_UI->m_cbInI;
	m_oParas.m_pCbInJ = m_pManualTest_UI->m_cbInJ;
	m_oParas.m_pBtnAnd = m_pManualTest_UI->m_rdAnd;
	m_oParas.m_pBtnOr = m_pManualTest_UI->m_rdOr;*/
    m_oParas.m_pCbOld = m_pManualTest_UI->m_cbOld;
    m_oParas.m_pCbAuto = m_pManualTest_UI->m_cbAuto;
    m_oParas.m_pCbDC = m_pManualTest_UI->m_cbDC;
	m_oParas.m_pBtnAdd = m_pManualTest_UI->m_btnAdd;
	m_oParas.m_pBtnMinus = m_pManualTest_UI->m_btnMinus;
	m_oParas.m_pBtnLock = m_pManualTest_UI->m_btnLock;
//	m_oParas.m_pCheckBoxHarm = m_pManualTest_UI->m_checkBoxHarm;
	m_oParas.m_pComboBoxHarm = m_pManualTest_UI->m_comboBoxHarm;
	//m_oParas.m_pEditAction = m_pManualTest_UI->m_editAction;
	//m_oParas.m_pEditActionTime = m_pManualTest_UI->m_editActionTime;
	//m_oParas.m_pEditReturn = m_pManualTest_UI->m_editReturn;
	//m_oParas.m_pEditReturnTime = m_pManualTest_UI->m_editReturnTime;
	m_oParas.m_pLabInitVal = m_pManualTest_UI->m_labInitVal;
	m_oParas.m_pLabFinishVal = m_pManualTest_UI->m_labFinishVal;
	m_oParas.m_pLabStep = m_pManualTest_UI->m_labStep;
	//m_oParas.m_pLabAction = m_pManualTest_UI->m_labAction;
	//m_oParas.m_pLabReturn = m_pManualTest_UI->m_labReturn;

	//2023/10/8 wjs 取消“+”“-”按钮为固定大小,"锁"设置为动态调整的
	//m_pManualTest_UI->m_btnLock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//m_pManualTest_UI->m_btnLock->setFixedWidth(500);
	//m_pManualTest_UI->m_btnAdd->setFixedWidth(100);
	//m_pManualTest_UI->m_btnMinus->setFixedWidth(100);
	//2023/10/8 wjs 开出量Widget宽度改变
	m_pManualTest_UI->m_boxOutSetting->setFixedWidth(110);

	m_oParas.Init();
	InitOtherParasUI();

	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		m_oParas.m_pBtnAdd->setVisible(false);
		m_oParas.m_pBtnMinus->setVisible(false);
		m_oParas.m_pBtnLock->setVisible(false);
		m_pManualTest_UI->m_checkBoxHarm->setVisible(false);//20230807 suyang 隐藏ui的叠加谐波

//		m_oParas.m_pCheckBoxHarm->setVisible(false);
		m_oParas.m_pComboBoxHarm->setVisible(false);


	//	m_pManualTest_UI->m_frmParas->hide();


		InitMuUI();
//		m_oParas.m_pCheckBoxHarm = m_pHarm_CheckBox;
		m_oParas.m_pComboBoxHarm = m_pHarm_ComboBox;
		//m_pManualTest_UI->m_comboBoxHarm = m_pHarm_ComboBox;


	}
	else if ((m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUTimingAccur)||(m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUPunctAccur))
	{
		m_oParas.m_pBtnAdd->setVisible(false);
		m_oParas.m_pBtnMinus->setVisible(false);
		m_oParas.m_pBtnLock->setVisible(false);
		m_pManualTest_UI->m_checkBoxHarm->setVisible(false);
//		m_oParas.m_pCheckBoxHarm->setVisible(false);
		m_oParas.m_pComboBoxHarm->setVisible(false);
	}
	else
	{
		m_oParas.m_pBtnAdd->setVisible(true);
		m_oParas.m_pBtnMinus->setVisible(true);
		m_oParas.m_pBtnLock->setVisible(true);
		m_pManualTest_UI->m_checkBoxHarm->setVisible(false);
//		m_oParas.m_pCheckBoxHarm->setVisible(false);
		m_oParas.m_pComboBoxHarm->setVisible(false);
	}

// 	if (m_pSttMUParasWidget != NULL)
// 	{
// 		m_pSttMUParasWidget->InitData(m_pManualParas);
// 	}

	if (m_pSttMUTimeTestWidget != NULL)
	{
		m_pSttMUTimeTestWidget->InitData(&m_oManualTest);
	}

	InitBinaryInBinaryOutUI();

// 	if(g_nBinCount == 8)
// 	{
// 		m_oParas.m_pCbInI->setChecked(false);
// 		m_oParas.m_pCbInJ->setChecked(false);
// 		m_oParas.m_pCbInI->setEnabled(false);
// 		m_oParas.m_pCbInJ->setEnabled(false);
// 	}
// 
// 	if(g_nBoutCount == 8)
// 	{
// 		m_oParas.m_pCbOut9->setChecked(false);
// 		m_oParas.m_pCbOut10->setChecked(false);
// 		m_oParas.m_pCbOut9->setEnabled(false);
// 		m_oParas.m_pCbOut10->setEnabled(false);
// 	}
}

void QSttMacroParaEditViewManual::InitIVView()
{  
	setFont(*g_pSttGlobalFont);
	m_pManualTest_UI->m_tabWidget->setFont(*g_pSttGlobalFont);
	m_oIV.m_pTabWidget = m_pManualTest_UI->m_tabWidget;
    m_oIV.InitUI(m_pManualParas->m_nFuncType);
}

void QSttMacroParaEditViewManual::InitMuUI()
{
	m_pHarm_CheckBox = new QSttCheckBox(g_sLangTxt_Manual_Harm);
	m_pHarm_ComboBox = new QScrollComboBox();
	m_pTestMethod_Label = new QLabel(g_sLangTxt_Manual_TestMethod);
	m_pTestMethod_ComboBox = new QScrollComboBox();
	
	m_pMeasType_Label = new QLabel(g_sLangTxt_Manual_MeasType);
	m_pMeasType_ComboBox = new QScrollComboBox();

	m_pBCode_Label = new QLabel(g_sLangTxt_Manual_BCode);
	m_pBCode_ComboBox = new QScrollComboBox();
	
	QVBoxLayout *m_pManual_VBoxLayout = new QVBoxLayout();
	m_pManualGroupBox = new QSttGroupBox(g_sLangTxt_GeneralParameter);

	m_pGridLayoutLeft = new QGridLayout();
	m_pGridLayoutLeft->addWidget(m_pHarm_CheckBox,0,0);
	m_pGridLayoutLeft->addWidget(m_pHarm_ComboBox,0,1);
	m_pGridLayoutLeft->addWidget(m_pMeasType_Label,0,2);
	m_pGridLayoutLeft->addWidget(m_pMeasType_ComboBox,0,3);
	m_pGridLayoutLeft->addWidget(m_pTestMethod_Label,1,0);
	m_pGridLayoutLeft->addWidget(m_pTestMethod_ComboBox,1,1);
	m_pGridLayoutLeft->addWidget(m_pBCode_Label,1,2);
	m_pGridLayoutLeft->addWidget(m_pBCode_ComboBox,1,3);

 	m_pManualGroupBox->setLayout(m_pGridLayoutLeft);


	QGridLayout *m_pTestReport_GridLayout = new QGridLayout();

	m_pSetMUTestRpt_CheckBox = new QSttCheckBox(g_sLangTxt_Manual_TestReport);

	m_pMUAccuracyTestNum_Edit = new QSttLineEdit();
	m_pMUTestNumUnit_Label = new QLabel(g_sLangTxt_Harm_Times);
	m_pMUTestTime_Edit = new QSttLineEdit();
	m_pMUTestTimeUnit_Label = new QLabel(g_sLangTxt_Manual_TestTime);

	m_pTestReport_GridLayout->addWidget(m_pSetMUTestRpt_CheckBox,0,0);

	m_pTestReport_GridLayout->addWidget(m_pMUAccuracyTestNum_Edit,1,0);
	m_pTestReport_GridLayout->addWidget(m_pMUTestNumUnit_Label,1,1);
	m_pTestReport_GridLayout->addWidget(m_pMUTestTime_Edit,1,2);
	m_pTestReport_GridLayout->addWidget(m_pMUTestTimeUnit_Label,1,3);

	m_pTestGroupBox = new QSttGroupBox(g_sLangTxt_Manual_TestReport);
	m_pTestGroupBox->setLayout(m_pTestReport_GridLayout);


	m_pOutSetGridLayout = new QGridLayout;
	CString strOutDesc,strTemp;;
	xlang_GetLangStrByFile(strOutDesc, "Native_BoutX");

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		strTemp = strOutDesc;
		strTemp.AppendFormat("%d",nIndex+1);
		m_pOutCheckBox[nIndex] = new QSttCheckBox(strTemp);
		if (nIndex < 4)
		{
			m_pOutSetGridLayout->addWidget(m_pOutCheckBox[nIndex],0,nIndex);
		}
		else
		{

			m_pOutSetGridLayout->addWidget(m_pOutCheckBox[nIndex],1,nIndex-4);
		}
	}

	m_pOutSetGroupBox = new QSttGroupBox(g_sLangTxt_Manual_OutSetting );
	m_pOutSetGroupBox->setLayout(m_pOutSetGridLayout);
	m_pOutSetGroupBox->setFont(*g_pSttGlobalFont);
	
	m_pRefresh_Button = new QPushButton(g_sLangTxt_Manual_Refresh);
 	m_pRefresh_Button->setMaximumWidth(100);

// #ifdef _PSX_QT_LINUX_
// 	m_pRefresh_Button->setVisible(false);
// #endif
	QHBoxLayout *m_pHBoxLayout = new QHBoxLayout();
	m_pHBoxLayout->addWidget(m_pRefresh_Button);
	m_pHBoxLayout->setAlignment(Qt::AlignCenter);
	

	QWidget *m_pWidget = new QWidget();
	m_pMainVBoxLayout = new QGridLayout(m_pWidget);
	m_pMainVBoxLayout->addWidget(m_pManualGroupBox,0,0);
	m_pMainVBoxLayout->addWidget(m_pTestGroupBox,0,1);
	m_pMainVBoxLayout->addWidget(m_pOutSetGroupBox,1,0);
	m_pMainVBoxLayout->addLayout(m_pHBoxLayout,1,1);
	m_pMainVBoxLayout->setContentsMargins(0, 0, 0, 0); 
	m_pMainVBoxLayout->setSpacing(2);

// 	m_pMainVBoxLayout->setHorizontalSpacing(30);
	m_pMainVBoxLayout -> setColumnStretch(0, 2);  
	m_pMainVBoxLayout -> setColumnStretch(1, 1);  

	m_pManualTest_UI->gridLayout_2->addWidget(m_pWidget,1, 0, 1, 1);
	m_pManualTest_UI->gridLayout_2->setContentsMargins(0, 0, 0, 0); 


	m_pBCode_ComboBox->setFont(*g_pSttGlobalFont);
	m_pHarm_ComboBox->setFont(*g_pSttGlobalFont);
	m_pTestMethod_ComboBox->setFont(*g_pSttGlobalFont);
	m_pMeasType_ComboBox->setFont(*g_pSttGlobalFont);
	m_pRefresh_Button->setFont(*g_pSttGlobalFont);

#ifdef _PSX_QT_WINDOWS_
	//20230712 suyang 适配6.4合并单元分辨率 1024X768
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("当前屏幕宽度(%ld),高度(%ld)."),
// 		rect.width(),rect.height());

	if (rect.width() <= 1024)
	{
		SetWinMuTestFont_1024_768();
	}
#else
	SetWinMuTestFont_1024_768();  //xueyangfan  2024-04-10  字体大小修改
#endif


 	InitMuComboBoxItem();

}

void QSttMacroParaEditViewManual::SetWinMuTestFont_1024_768()
{
// 	QFont oFont;
// 	oFont.setPixelSize(12);
	g_pSttGlobalFont->resolve(QFont::AllPropertiesResolved);
	m_pHarm_CheckBox->setFont(*g_pSttGlobalFont);
	m_pBCode_ComboBox->setFont(*g_pSttGlobalFont);
	m_pHarm_ComboBox->setFont(*g_pSttGlobalFont);
	m_pTestMethod_ComboBox->setFont(*g_pSttGlobalFont);
	m_pMeasType_ComboBox->setFont(*g_pSttGlobalFont);
	m_pRefresh_Button->setFont(*g_pSttGlobalFont);
	m_pOutSetGroupBox->setFont(*g_pSttGlobalFont);
	m_pTestMethod_Label->setFont(*g_pSttGlobalFont);
	m_pMeasType_Label->setFont(*g_pSttGlobalFont);
	m_pBCode_Label->setFont(*g_pSttGlobalFont);
	m_pSetMUTestRpt_CheckBox->setFont(*g_pSttGlobalFont);
	m_pMUAccuracyTestNum_Edit->setFont(*g_pSttGlobalFont);
	m_pMUTestNumUnit_Label->setFont(*g_pSttGlobalFont);
	m_pMUTestTime_Edit->setFont(*g_pSttGlobalFont);
	m_pMUTestTimeUnit_Label->setFont(*g_pSttGlobalFont);

	m_pManualGroupBox->setFont(*g_pSttGlobalFont);
	m_pTestGroupBox->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewManual::InitMuComboBoxItem()
{

	if (m_pTestMethod_ComboBox != NULL)
	{
		m_pTestMethod_ComboBox->addItem(g_sLangTxt_State_Synchronousmethod);
		m_pTestMethod_ComboBox->addItem(g_sLangTxt_State_Interpolation);
	}

	if (m_pMeasType_ComboBox != NULL)
	{
		CString strText;
		strText = _T("IEC61850-9-2");
		m_pMeasType_ComboBox->addItem(strText);
		strText = _T("IEC60044-8(FT3)");
		m_pMeasType_ComboBox->addItem(strText);
	}

	if (m_pBCode_ComboBox != NULL)
	{
		m_pBCode_ComboBox->addItem(g_sLangTxt_Manual_PositiveLogic);
		m_pBCode_ComboBox->addItem(g_sLangTxt_Manual_NegativeLogic);
	}


}

void QSttMacroParaEditViewManual::UpdateMUAccurData()
{
	g_nUseCustomMUTestRpt = m_pManualParas->m_oMuParas.m_nUseSetRpt;
	g_nMURptTestCount = m_pManualParas->m_oMuParas.m_nMaxTestCount;
	g_fMUTestTimeEach = m_pManualParas->m_oMuParas.m_fTimeOneCount;
	m_pSetMUTestRpt_CheckBox->setChecked(m_pManualParas->m_oMuParas.m_nUseSetRpt);
	m_pMUAccuracyTestNum_Edit->setText(QString::number(m_pManualParas->m_oMuParas.m_nMaxTestCount));
	m_pMUTestTime_Edit->setText(QString::number(m_pManualParas->m_oMuParas.m_fTimeOneCount,'f',3));
	UpdateMURptUI();

	m_pTestMethod_ComboBox->setCurrentIndex(m_pManualParas->m_oMuParas.nAlgorithmType);

	if (m_nIecFormatMeas == 0)
	{
		m_pMeasType_ComboBox->setCurrentIndex(0);
	}
	else
	{
		m_pMeasType_ComboBox->setCurrentIndex(1);
	}

	if (m_nBCodeMode == 0)
	{
		m_pBCode_ComboBox->setCurrentIndex(0);
	}
	else
	{
		m_pBCode_ComboBox->setCurrentIndex(1);
	}

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		m_pOutCheckBox[nIndex]->setChecked(m_pManualParas->m_binOut[nIndex].nState);
		m_pOutCheckBox[nIndex]->setVisible(g_nBoutCount>nIndex);
	}
}

void QSttMacroParaEditViewManual::UpdateHarmCheckComboxUI(BOOL bClearItems)
{
	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		disconnect(m_pHarm_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_HarmCheck_stateChanged(int)));
		disconnect(m_pHarm_ComboBox, SIGNAL(currentIndexChanged (int)), this, SLOT(slot_cmbHarm_SelChanged(int)));

		if (bClearItems)
		{
			m_oParas.InitHarmCombox();
		}

		m_pHarm_ComboBox->setEnabled(m_pManualParas->m_nSelHarm);
		m_pHarm_CheckBox->setChecked(m_pManualParas->m_nSelHarm);
		m_pHarm_ComboBox->setCurrentIndex(m_pManualParas->m_nHarmIndex-2);

		if (m_oIV.m_pHarmUIParaWidget != NULL)
		{
			m_oIV.m_pHarmUIParaWidget->setEnabled(m_pManualParas->m_nSelHarm);
		}

		connect(m_pHarm_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_HarmCheck_stateChanged(int)));
		connect(m_pHarm_ComboBox, SIGNAL(currentIndexChanged (int)), this, SLOT(slot_cmbHarm_SelChanged(int)));
	}
}

// void QSttMacroParaEditViewManual::UpdateMUTimeAccurRlt_NOPPS(CDvmData *pSVDelayData)
// {
// 	if (m_pSttMUTimeTestWidget == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (m_pManualParas == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (m_pManualParas->m_oMuParas.nPPS_SetType == 2)//只在无PPS时更新结果
// 	{
// 		m_pSttMUTimeTestWidget->UpdateMUTimeAccurRlt_NOPPS(pSVDelayData);
// 	}
// }

void QSttMacroParaEditViewManual::slot_SwitchStateChanged()
{
	//UpdateToolButtons();将开出量传给框架
	m_oParas.UpdateData();//更新开出量状态

	if (g_theTestCntrFrame->IsTestStarted() && !m_pManualParas->m_bLockChanged)
	{
		SendUpdateParameter();
	}

	SetParaChanged();
}

void QSttMacroParaEditViewManual::InitBinStateOnStarting()
{
	/*初始化开出
	for (int i=0;i<g_oLocalSysPara.m_nCHBinOutNum;i++)
		m_oCurrEventResult.m_BinOut[i] = m_pManualParas->m_binOut[i].nState;

	for (int i=0;i<g_nBoutExCount;i++)
		m_oCurrEventResult.m_BinOutEx[i] = m_pManualParas->m_binOutEx[i].nState;

	UpdateToolButtons();
	*/
}


void QSttMacroParaEditViewManual::OnViewTestLink(BOOL b)
{

}

bool QSttMacroParaEditViewManual::PrepStartTest()
{
	m_bSystemParasChanged = FALSE;

	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		if (m_pRefresh_Button != NULL)
		{
			m_pRefresh_Button->setEnabled(false);
		}
		if (g_oSystemParas.m_nIecFormatMeas != m_nIecFormatMeas)
		{
			g_oSystemParas.m_nIecFormatMeas = m_nIecFormatMeas;
			m_bSystemParasChanged = TRUE;
		}

		if (g_oSystemParas.m_nBCodeMode != m_nBCodeMode)
		{
			g_oSystemParas.m_nBCodeMode = m_nBCodeMode;
			m_bSystemParasChanged = TRUE;
		}

		g_nMURptTestCount = m_pManualParas->m_oMuParas.m_nMaxTestCount;
		g_fMUTestTimeEach = m_pManualParas->m_oMuParas.m_fTimeOneCount;
		g_nUseCustomMUTestRpt = m_pManualParas->m_oMuParas.m_nUseSetRpt;
	}

	return true;
}

void QSttMacroParaEditViewManual::OnViewTestStart()
{
	//合并单元测试需要判断输出B码和接收报文类型与系统参数是否一致  suyang 2023-6-1

	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		if (m_pRefresh_Button != NULL)
		{
			m_pRefresh_Button->setEnabled(false);
		}

		if (m_pSetMUTestRpt_CheckBox != NULL)
		{
			m_pSetMUTestRpt_CheckBox->setEnabled(false);
			m_pMUAccuracyTestNum_Edit->setEnabled(false);
			m_pMUTestTime_Edit->setEnabled(false);

			m_pTestMethod_ComboBox->setEnabled(false);
			m_pMeasType_ComboBox->setEnabled(false);
			m_pBCode_ComboBox->setEnabled(false);
		}
	}

	InitBinStateOnStarting();
	BOOL bEnableState = TRUE;
	int nGooseParasUI_State = STT_UI_RUN_STATE_StateTested_Editable;

	if ((m_pManualParas->m_bAuto)/*||(m_pManualParas->m_nFuncType != TMT_MANU_FUNC_TYPE_Common)*/)
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

	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_oIV.m_pHarmUIParaWidget->startInit(bEnableState);
	}

	if (m_pSttMUTimeTestWidget != NULL)
	{
		m_pSttMUTimeTestWidget->TestStartInit();
	}

// 	if (m_pSttMUParasWidget != NULL)
// 	{
// 		m_pSttMUParasWidget->setEnabled(false);
// 	}

	m_oIV.m_pUIParaWidget->startInit(bEnableState);
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	g_theTestCntrFrame->ClearInfoWidget();
	m_oParas.StartInit();
	//m_oParas.UpdateResult(0,0,0,0);
	if(m_pManualTest_UI->m_cbAuto->isChecked() && m_pGooseParaWidget)
	{
		m_pGooseParaWidget->setDisabled(true);
	}

	if(m_pManualTest_UI->m_cbAuto->isChecked() && m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->setDisabled(true);
	}

// 	m_pManualTest_UI->m_checkBoxHarm->setEnabled(false);
// 	m_pManualTest_UI->m_comboBoxHarm->setEnabled(m_pManualParas->m_nSelHarm);
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();

	m_pManualTest_UI->m_btnShortCalcu->setEnabled(bEnableState);
	m_pManualTest_UI->m_btnDiffCalc->setEnabled(bEnableState);
	m_pManualTest_UI->m_btnInBinaryOutSet->setEnabled(bEnableState);
	m_pManualTest_UI->m_btnEstimate->setEnabled(bEnableState);

	if (m_pManualTest_UI->m_cbAuto->checkState() == Qt::Checked)
	{
		m_pManualTest_UI->m_frmOtherPara->setEnabled(false);
		m_pManualTest_UI->m_boxOutSetting->setEnabled(false);
		m_pManualTest_UI->m_frmParas->setEnabled(false);
	}

	g_theTestCntrFrame->EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewManual::OnViewTestStop()
{
	UpdateMURptUI();

	if (m_pSetMUTestRpt_CheckBox != NULL)
	{
		m_pSetMUTestRpt_CheckBox->setEnabled(TRUE);
		m_pTestMethod_ComboBox->setEnabled(TRUE);
		m_pMeasType_ComboBox->setEnabled(TRUE);
		m_pBCode_ComboBox->setEnabled(TRUE);
	}

	/*初始化开入
	for (int i=0;i<g_oLocalSysPara.m_nCHBinInNum;i++)
		m_oCurrEventResult.m_BinIn[i] = 0;

	//初始化扩展开出
	for (int i=0;i<g_nBinExCount;i++)
		m_oCurrEventResult.m_BinInEx[i] = 0;

	//初始化开出
	for (int i=0;i<g_oLocalSysPara.m_nCHBinOutNum;i++)
		m_oCurrEventResult.m_BinOut[i] = 0;

	//初始化扩展开出
	for (int i=0;i<g_nBoutExCount;i++)
		m_oCurrEventResult.m_BinOutEx[i] = 0;

	m_bViewTestStarted = false;

	m_oIV.m_pUIParaWidget->stopInit();
	m_oIV.m_pUIParaWidget->setFocus();
*/
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

	if (m_pRefresh_Button != NULL)
	{
		m_pRefresh_Button->setEnabled(true);
	}
	
	m_oIV.m_pUIParaWidget->startInit();
// 	m_pManualTest_UI->m_checkBoxHarm->setEnabled(true);
// 	m_pManualTest_UI->m_comboBoxHarm->setEnabled(true);
	m_oParas.StopInit();
	if(m_pGooseParaWidget)
	{
		m_pGooseParaWidget->setDisabled(false);
	}
	if(m_pFT3OutParaWidget)
	{
		m_pFT3OutParaWidget->setDisabled(false);
	}
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget(false);//20220628 zhouhj 暂时改为不更新界面参数,防止界面参数被修改为0
	g_theTestCntrFrame->StopPowerWidget();
	m_oIV.m_pUIParaWidget->UpdateTables();

	if (m_oIV.m_pHarmUIParaWidget != NULL)
	{
		m_oIV.m_pHarmUIParaWidget->startInit();
		m_oIV.m_pHarmUIParaWidget->UpdateTables();
	}

	if (m_pSttMUTimeTestWidget != NULL)
	{
		m_pSttMUTimeTestWidget->TestStopInit();
	}

// 	if (m_pSttMUParasWidget != NULL)
// 	{
// 		m_pSttMUParasWidget->setEnabled(true);
// 	}

	m_pManualTest_UI->m_frmOtherPara->setEnabled(true);
	m_pManualTest_UI->m_boxOutSetting->setEnabled(true);
	m_pManualTest_UI->m_frmParas->setEnabled(true);
	m_pManualTest_UI->m_btnShortCalcu->setEnabled(true);
	m_pManualTest_UI->m_btnDiffCalc->setEnabled(true);
	m_pManualTest_UI->m_btnInBinaryOutSet->setEnabled(true);
	m_pManualTest_UI->m_btnEstimate->setEnabled(true);

}

void QSttMacroParaEditViewManual::on_m_btnLock_clicked()
{
	m_oParas.slot_btn_LockClicked();
	
	if (g_theTestCntrFrame->IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}
	
	SetParaChanged();
}

void QSttMacroParaEditViewManual::on_m_btnAdd_clicked()
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

void QSttMacroParaEditViewManual::on_m_btnMinus_clicked()
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

void QSttMacroParaEditViewManual::on_m_editIintVal_editingFinished()
{
	m_oParas.slot_lne_startChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewManual::on_m_editFinishVal_editingFinished()
{
	m_oParas.slot_lne_endChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewManual::on_m_editTime_editingFinished()
{
	m_oParas.slot_lne_steptimeChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewManual::on_m_editUdc_editingFinished()
{
	m_oParas.slot_lne_UdcChanged();
	SetParaChanged();
	
}
//void QSttMacroParaEditViewManual::on_m_editDelayed_editingFinished()
//{
//	m_oParas.slot_lne_delayedChanged();
//	SetParaChanged();
//}

void QSttMacroParaEditViewManual::on_m_editStep_editingFinished()
{
	m_oParas.slot_lne_stepChanged();
	SetParaChanged();
}

void QSttMacroParaEditViewManual::slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC)
{
	m_bIsChanging = TRUE;
	m_oIV.m_pUIParaWidget->setChannelTableItemValue(str, fstep, valueFlag, AddOrMinus, bDC);
	m_bIsChanging = FALSE;
}

void QSttMacroParaEditViewManual::slot_updateParas()
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

void QSttMacroParaEditViewManual::on_m_cbOld_clicked()
{
	m_oParas.slot_cb_OldClicked();
	if (g_theTestCntrFrame->IsTestStarted() && (!m_pManualParas->m_bLockChanged))  //解锁状态
	{
		SendUpdateParameter();
	}
	SetParaChanged();
}

void QSttMacroParaEditViewManual::on_m_cbAuto_clicked()
{
	m_oParas.slot_cb_AutoClicked();
	SetParaChanged();
}

void QSttMacroParaEditViewManual::on_m_cbDC_clicked()
{
	m_oParas.slot_cb_DCClicked();
	m_oIV.slot_cb_DCClicked(m_pManualTest_UI->m_cbDC->isChecked());
	SetParaChanged();
}

void QSttMacroParaEditViewManual::on_m_cbbSelect_currentIndexChanged(int index)
{
	if(m_oParas.m_pCbbSelect->IsScrolling())
	{
		return;
	}	

	m_oParas.slot_cbb_SelectChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewManual::on_m_cbbChannel_currentIndexChanged(int index)
{
	if(m_oParas.m_pCbbChannel->IsScrolling())
	{
		return;
	}	

	m_oParas.slot_cbb_ChannelChanged(index);

	SetParaChanged();

	m_strCbbChannel=m_pManualTest_UI->m_cbbChannel->currentText();
	
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

void QSttMacroParaEditViewManual::on_m_cbbChangeType_currentIndexChanged(int index)
{
	if(m_oParas.m_pCbbChangeType->IsScrolling())
	{
		return;
	}	

	m_oParas.slot_cbb_ChangeTypeChanged(index);
	SetParaChanged();
}

void QSttMacroParaEditViewManual::on_m_cbOut1_clicked()
{
	m_oParas.slot_ck_Out1StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewManual::on_m_cbOut2_clicked()
{
	m_oParas.slot_ck_Out2StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewManual::on_m_cbOut3_clicked()
{
	m_oParas.slot_ck_Out3StateChanged();
	slot_SwitchStateChanged();
}

void QSttMacroParaEditViewManual::on_m_cbOut4_clicked()
{
	m_oParas.slot_ck_Out4StateChanged();
	slot_SwitchStateChanged();
}

//void QSttMacroParaEditViewManual::on_m_cbOut5_clicked()
//{
//	m_oParas.slot_ck_Out5StateChanged();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_cbOut6_clicked()
//{
//	m_oParas.slot_ck_Out6StateChanged();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_cbOut7_clicked()
//{
//	m_oParas.slot_ck_Out7StateChanged();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_cbOut8_clicked()
//{
//	m_oParas.slot_ck_Out8StateChanged();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_cbOut9_clicked()
//{
//	m_oParas.slot_ck_Out9StateChanged();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_cbOut10_clicked()
//{
//	m_oParas.slot_ck_Out10StateChanged();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_cbInA_clicked()
//{
//	m_oParas.slot_ck_InAStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//void QSttMacroParaEditViewManual::on_m_cbInB_clicked()
//{
//	m_oParas.slot_ck_InBStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//void QSttMacroParaEditViewManual::on_m_cbInC_clicked()
//{
//	m_oParas.slot_ck_InCStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//void QSttMacroParaEditViewManual::on_m_cbInD_clicked()
//{
//	m_oParas.slot_ck_InDStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//void QSttMacroParaEditViewManual::on_m_cbInE_clicked()
//{
//	m_oParas.slot_ck_InEStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//void QSttMacroParaEditViewManual::on_m_cbInF_clicked()
//{
//	m_oParas.slot_ck_InFStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//void QSttMacroParaEditViewManual::on_m_cbInG_clicked()
//{
//	m_oParas.slot_ck_InGStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//void QSttMacroParaEditViewManual::on_m_cbInH_clicked()
//{
//	m_oParas.slot_ck_InHStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_cbInI_clicked()
//{
//	m_oParas.slot_ck_InIStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_cbInJ_clicked()
//{
//	m_oParas.slot_ck_InJStateChanged();
//	g_theTestCntrFrame->UpdateToolButtons();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_rdAnd_clicked()
//{
//	m_oParas.slot_rb_RdAndStateChanged();
//	slot_SwitchStateChanged();
//}
//
//void QSttMacroParaEditViewManual::on_m_rdOr_clicked()
//{
//	m_oParas.slot_rb_RdOrStateChanged();
//	slot_SwitchStateChanged();
//}


void QSttMacroParaEditViewManual::ShowReport(CDvmValues *pValues)
{
	CDvmValue* pActValueData = (CDvmValue*)pValues->FindByID("ActValue");
	CDvmValue* pActTimeData = (CDvmValue*)pValues->FindByID("TripTime");
	CDvmValue* pActReturnData = (CDvmValue*)pValues->FindByID("ReturnValue");
	CDvmValue* pActReturnTimeData = (CDvmValue*)pValues->FindByID("ReturnTime");

	float fActValue = 0, fActTime = 0, fReturnValue = 0, fReturnTime = 0;

	if (pActValueData != NULL)
	{
		fActValue = GlobalSetResultValue(pActValueData,3);
		//		pActValueData->m_strValue = QString::number(fActValue,'f',3);
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

// 	if (pActReturnTimeData != NULL)// zhouhj 2024.1.19 不能在此处修约,后续还要用到该数据
// 	{
// 		fReturnTime = GlobalSetResultValue(pActReturnTimeData,4);
// 		//		pActReturnTimeData->m_strValue = QString::number(fReturnTime,'f',4);
// 	}

	if (m_pSttMUTimeTestWidget != NULL)
	{
		m_pSttMUTimeTestWidget->ShowReport(pValues);
	}

	//m_oParas.UpdateResult(fActValue, fActTime, fReturnValue, fReturnTime);
}

CString QSttMacroParaEditViewManual::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += FILE_MANUTEST;
	strFile += _T(".");
	strFile += POSTFIX_MANUTEST;

	return strFile;
}

bool QSttMacroParaEditViewManual::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
{
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != POSTFIX_MANUTEST)
	{
		return false;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return false;
	}

	return true;
}

void QSttMacroParaEditViewManual::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

//判断使用的keyboard类型
void QSttMacroParaEditViewManual::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
{
	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();

	if(bIsNor == FALSE)
	{
		QString strVar = m_pManualTest_UI->m_cbbChannel->currentText();
		int nIdx = m_pManualTest_UI->m_cbbSelect->currentIndex();
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

void QSttMacroParaEditViewManual::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,TRUE);
	int nInsertPos = 2;

	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		nInsertPos++;
	}

	//if (ExistHarmParaset())
	//{
	//	nInsertPos++;
	//}

	//if (ExistExBinParaWidget())
	//{
	//	nInsertPos++;
	//}

	//if (ExistExBoutParaWidget())
	//{
	//	nInsertPos++;
	//}

	//	m_tabWidget->insertTab(nInsertPos,m_pExBoutParaWidget,tr("开出设置(扩展)"));

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	m_pManualTest_UI->m_tabWidget->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewManual::RemoveGooseParaWidget()
{
	if(m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pManualTest_UI->m_tabWidget->indexOf(m_pGooseParaWidget);
	m_pManualTest_UI->m_tabWidget->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QSttMacroParaEditViewManual::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,TRUE);
	int nInsertPos = 3;

	if ((m_pManualParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)&&(m_pManualParas->m_nFuncType < TMT_MANU_FUNC_TYPE_MUTimingAccur))
	{
		nInsertPos++;
	}

	CString strTitle;
	strTitle = /*_T("FT3发布")*/g_sLangTxt_Gradient_ReleasedFTT; //lcq
	m_pManualTest_UI->m_tabWidget->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewManual::RemoveFT3OutParaWidget()
{
	if(m_pFT3OutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pManualTest_UI->m_tabWidget->indexOf(m_pFT3OutParaWidget);
	m_pManualTest_UI->m_tabWidget->removeTab(nIndex);

	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

bool QSttMacroParaEditViewManual::ExistFT3OutParaWidget()
{
	int nIndex = m_pManualTest_UI->m_tabWidget->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

bool QSttMacroParaEditViewManual::ExistGooseParaWidget()
{
	int nIndex = m_pManualTest_UI->m_tabWidget->indexOf(m_pGooseParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewManual::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		m_pManualTest_UI->m_tabWidget->setTabEnabled(m_pManualTest_UI->m_tabWidget->indexOf(m_pFT3OutParaWidget),b);
	}
}

// void QSttMacroParaEditViewManual::UpdateMUTimeAccurRlt_PPS()
// {
// 	emit sig_UpdateMUTimeAccurRlt_PPS();
// }

//2023.10.17 zhouhj 删除
// void QSttMacroParaEditViewManual::slot_UpdateMUTimeAccurRlt_PPS()
// {
// 	CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();
// 
// 	if ((pXSttCap_61850 == NULL)||(m_pSttMUTimeTestWidget == NULL)
// 		||(m_pManualParas == NULL))
// 	{
// 		return;
// 	}
// 
// 	if (pXSttCap_61850->m_pDataset_MUTimeRlt == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (m_pManualParas->m_oMuParas.nPPS_SetType < 2)//只在无PPS时更新结果
// 	{
// 		m_pSttMUTimeTestWidget->UpdateMUTimeAccurRlt_PPS(pXSttCap_61850->m_pDataset_MUTimeRlt);
// 	}
// }

void QSttMacroParaEditViewManual::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		m_pManualTest_UI->m_tabWidget->setTabEnabled(m_pManualTest_UI->m_tabWidget->indexOf(m_pGooseParaWidget),b);
	}
}

// void QSttMacroParaEditViewManual::EnableSubParaWidget(bool bEnable)
// {
// 	/*
// 	if (m_pHarmParaWidget != NULL)
// 	{
// 		m_pHarmParaWidget->startInit(bEnable);
// 	}
// 
// 	if(m_pExBinParaWidget != NULL)
// 	{
// 		m_pExBinParaWidget->m_pTable->setDisabled(!bEnable);
// 		m_pExBinParaWidget->ck_SelectAll->setDisabled(!bEnable);
// 	}
// 
// 	if(m_pExBoutParaWidget != NULL)
// 	{
// 		m_pExBoutParaWidget->m_pTable->setDisabled(!bEnable);
// 		m_pExBoutParaWidget->ck_SelectAll->setDisabled(!bEnable);
// 	}
// 	*/
// 	if (m_pGooseParaWidget!= NULL)
// 	{
// 		if(bEnable)
// 		{
// 			m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
// 			m_pGooseParaWidget->SetGooseDisabled(FALSE);
// 		}
// 		else
// 		{
// 			m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_NotEditable);
// 			m_pGooseParaWidget->SetGooseDisabled(TRUE);
// 		}
// 	}
// }

void QSttMacroParaEditViewManual::SetDatas(CDataGroup *pDataset)
{
	m_nBCodeMode = g_oSystemParas.m_nBCodeMode;
	m_nIecFormatMeas = g_oSystemParas.m_nIecFormatMeas;

	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pManualParas, &oRead);

	}

    if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin QSttMacroParaEditViewManual::SetDatas -  >>");	}

	g_theTestCntrFrame->InitVectorWidget(m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);
 
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin QSttMacroParaEditViewManual::SetDatas -  >>");	}
	g_theTestCntrFrame->InitPowerWidget(m_pManualParas->m_uiVOL,m_pManualParas->m_uiCUR);

    if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin QSttMacroParaEditViewManual::SetDatas 1-  >>");	}

    g_theTestCntrFrame->InitStateMonitor();

    if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin QSttMacroParaEditViewManual::SetDatas 2-  >>");	}
    g_theTestCntrFrame->ClearInfoWidget();

    if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin QSttMacroParaEditViewManual::SetDatas 3-  >>");	}
    UpdateManualParas(FALSE);//dingxy 20240603 构造函数中setdata调用m_oParas.UpdateData();重复调用注释
    if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end QSttMacroParaEditViewManual::SetDatas -  >>");	}
}

BOOL QSttMacroParaEditViewManual::SetValues_dsRcdStep6U6I(CDvmDataset *pDsRcdStep6U6I)
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

	if (pCurrData != NULL)
	{
		if (m_pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUFirstCycleWave)
		{
			pCurrData->m_strValue = _T("1");
		} 
		else
		{
			pCurrData->m_strValue = _T("0");
		}
	}

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

void QSttMacroParaEditViewManual::on_m_editTimeChanged()
{
	slot_edit_changed(m_pManualTest_UI->m_editTime, TRUE);
}

void QSttMacroParaEditViewManual::on_m_editStepChanged()
{
	slot_edit_changed(m_pManualTest_UI->m_editStep, TRUE);
}

void QSttMacroParaEditViewManual::on_m_editInitValueChanged()
{
	slot_edit_changed(m_pManualTest_UI->m_editIintVal, TRUE);
}

void QSttMacroParaEditViewManual::on_m_editFinishValueChanged()
{
	slot_edit_changed(m_pManualTest_UI->m_editFinishVal, TRUE);
}

//void QSttMacroParaEditViewManual::on_m_editDelayChanged()
//{
//	slot_edit_changed(m_pManualTest_UI->m_editDelayed, TRUE);
//}


void QSttMacroParaEditViewManual::on_m_btnShortCalcu_clicked()
{
	ShortCalcuDig dlg(g_oSttTestResourceMngr.m_pTestResouce
		,m_pManualParas->m_uiVOL, m_pManualParas->m_uiCUR
		,m_ShortCalcuPara,this);
	dlg.setFont(*g_pSttGlobalFont);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
    QSoftKeyBoard::AttachObj(&dlg);
#endif
	connect(&dlg,SIGNAL(sig_ShortCalcuOk(ShortCalcuPara &)),this,SLOT(slot_ShortCalcuOk(ShortCalcuPara &)));
	dlg.exec();
#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif
}

void QSttMacroParaEditViewManual::slot_ShortCalcuOk(ShortCalcuPara &para)
{
	if (!m_ShortCalcuPara.isSame(para))
	{
		m_ShortCalcuPara = para;
		g_pManualTest->m_bTmtParaChanged = TRUE;
		UpdateManualParas();
		emit sig_updataParas();
	}

}

//void QSttMacroParaEditViewManual::slot_ShortClac()
//{
///*
//	ShortCalcuDig dig(g_oSttTestResourceMngr.m_pTestResouce,m_pStatePara,m_ShortCalcuPara,this);
//	dig.setWindowModality(Qt::WindowModal);
//	connect(&dig,SIGNAL(sig_ShortCalcuOk(ShortCalcuPara &)),this,SLOT(slot_ShortCalcuOk(ShortCalcuPara &)));
//#ifdef _PSX_QT_LINUX_
//	QSoftKeyBoard::AttachObj(&dig);
//	dig.exec();
//	QSoftKeyBoard::AttachObj(this);
//#else
//	dig.exec();
//#endif
//	dig.exec();
//*/
//}


void QSttMacroParaEditViewManual::on_m_btnInBinaryOutSet_clicked()
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

void QSttMacroParaEditViewManual::on_m_btnDiffCalc_clicked()
{
	
	SttDiffCurrCalDlg dig(this);
	dig.setFont(*g_pSttGlobalFont);
	dig.setWindowModality(Qt::WindowModal);
	dig.InitUI(&m_oDiffCurrCalParas);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dig);
#endif

	if (dig.exec() == QDialog::Accepted)
	{
		long nHeightBeginIndex = dig.m_nHeightUsedIndex*3;
		long nLowerBeginIndex = dig.m_nLowerUsedIndex*3;
		ChannelUI_Diff* pChannelUI_Diff = dig.m_oDiffCalTool.GetChannelCurrents();
		m_pManualParas->m_uiCUR[nHeightBeginIndex].Harm[1].fAmp = pChannelUI_Diff[0].famptitude;
		m_pManualParas->m_uiCUR[nHeightBeginIndex].Harm[1].fAngle = pChannelUI_Diff[0].fphase;
		m_pManualParas->m_uiCUR[nHeightBeginIndex+1].Harm[1].fAmp = pChannelUI_Diff[1].famptitude;
		m_pManualParas->m_uiCUR[nHeightBeginIndex+1].Harm[1].fAngle = pChannelUI_Diff[1].fphase;
		m_pManualParas->m_uiCUR[nHeightBeginIndex+2].Harm[1].fAmp = pChannelUI_Diff[2].famptitude;
		m_pManualParas->m_uiCUR[nHeightBeginIndex+2].Harm[1].fAngle = pChannelUI_Diff[2].fphase;
		m_pManualParas->m_uiCUR[nLowerBeginIndex].Harm[1].fAmp = pChannelUI_Diff[3].famptitude;
		m_pManualParas->m_uiCUR[nLowerBeginIndex].Harm[1].fAngle = pChannelUI_Diff[3].fphase;
		m_pManualParas->m_uiCUR[nLowerBeginIndex+1].Harm[1].fAmp = pChannelUI_Diff[4].famptitude;
		m_pManualParas->m_uiCUR[nLowerBeginIndex+1].Harm[1].fAngle = pChannelUI_Diff[4].fphase;
		m_pManualParas->m_uiCUR[nLowerBeginIndex+2].Harm[1].fAmp = pChannelUI_Diff[5].famptitude;
		m_pManualParas->m_uiCUR[nLowerBeginIndex+2].Harm[1].fAngle = pChannelUI_Diff[5].fphase;
		UpdateManualParas();
		emit sig_updataParas();
	}
#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif

}

//cl20230l724
void QSttMacroParaEditViewManual::slot_Estimate()
{
	ManualEstimateDlg dlg(m_pManualParas, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewManual::slot_cbbTestMethod_currentIndexChanged(int index)
{
	m_pManualParas->m_oMuParas.nAlgorithmType = index;
	SetParaChanged();
}

void QSttMacroParaEditViewManual::slot_cbbMeasType_currentIndexChanged(int index)
{
// 	if (g_oSystemParas.m_nIecFormatMeas != index)
// 	{
// 		g_oSystemParas.m_nIecFormatMeas = index;
// 	}

	m_nIecFormatMeas = index;

}

void QSttMacroParaEditViewManual::slot_cbbBCode_currentIndexChanged(int index)
{

// 	if (g_oSystemParas.m_nBCodeMode != index)
// 	{
// 		g_oSystemParas.m_nBCodeMode = index;
// 	}

	m_nBCodeMode = index;

}

void QSttMacroParaEditViewManual::slot_editTestNumChanged()
{

// #ifdef _USE_SoftKeyBoard_
// 	QSoftKeyBoard::ShowSmoothKeyboard();
// #endif

	QString strValue = m_pMUAccuracyTestNum_Edit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pMUAccuracyTestNum_Edit,this);
	
// 	int nCnt = strValue.toInt();
// 
// 	if (nCnt >20 )
// 	{
// 		nCnt = 20;
// 	}
// 
// 	if (nCnt < 2)
// 	{
// 		nCnt = 2;
// 	}
}


void QSttMacroParaEditViewManual::slot_editTestTimeChanged()
{
	QString strValue = m_pMUTestTime_Edit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pMUTestTime_Edit,this);

// 	int nCnt = strValue.toInt();
// 
// 	if (nCnt >10 )
// 	{
// 		nCnt = 10;
// 	}
// 
// 	if (nCnt < 1)
// 	{
// 		nCnt = 1;
// 	}
}


void QSttMacroParaEditViewManual::slot_editTestNumFinished()
{
	QString strValue = m_pMUAccuracyTestNum_Edit->text();

	int nCnt = strValue.toInt();

	if (nCnt >20 )
	{
		nCnt = 20;
	}

	if (nCnt < 2)
	{
		nCnt = 2;
	}

	m_pManualParas->m_oMuParas.m_nMaxTestCount = nCnt;
	g_nMURptTestCount = m_pManualParas->m_oMuParas.m_nMaxTestCount;
	m_pMUAccuracyTestNum_Edit->setText(QString::number(nCnt));
	SetParaChanged();
}

void QSttMacroParaEditViewManual::slot_editTestTimeFinished()
{
	QString strValue = m_pMUTestTime_Edit->text();

	float fTime = strValue.toFloat();

	if (fTime >10.0f )
	{
		fTime = 10.0f;
	}

	if (fTime < 0.5f)
	{
		fTime = 0.5f;
	}

	m_pManualParas->m_oMuParas.m_fTimeOneCount = fTime;
	g_fMUTestTimeEach = m_pManualParas->m_oMuParas.m_fTimeOneCount;
	m_pMUTestTime_Edit->setText(QString::number(fTime,'f',3));

	if (g_pSttIecRecordCbWidget != NULL)
	{
		g_pSttIecRecordCbWidget->Update_IecRcdTimer();
	} 
}

void QSttMacroParaEditViewManual::slot_OnTestCheckChanged()
{
	m_pManualParas->m_oMuParas.m_nUseSetRpt = m_pSetMUTestRpt_CheckBox->isChecked();
	UpdateMURptUI();

	if (g_pSttIecRecordCbWidget != NULL)
	{
		g_nUseCustomMUTestRpt = m_pManualParas->m_oMuParas.m_nUseSetRpt;
		g_pSttIecRecordCbWidget->Update_IecRcdTimer();
	} 
}

void QSttMacroParaEditViewManual::slot_RefreshClicked()
{
	if (g_pSttMUTestIecCbSelWidget != NULL)
	{
		g_pSttMUTestIecCbSelWidget->Refresh_MUTest();
	}
}


void QSttMacroParaEditViewManual::UpdateMURptUI()
{
	if (m_pSetMUTestRpt_CheckBox == NULL)
	{
		return;
	}

	if (m_pSetMUTestRpt_CheckBox->checkState() ==  Qt::Checked)
	{
		m_pMUAccuracyTestNum_Edit->setEnabled(TRUE);
		m_pMUTestTime_Edit->setEnabled(TRUE);
	}
	else
	{
		m_pMUAccuracyTestNum_Edit->setEnabled(FALSE);
		m_pMUTestTime_Edit->setEnabled(FALSE);
	}
}

void QSttMacroParaEditViewManual::slot_OnOutCheckChanged()
{
	QCheckBox* pCheckBox = qobject_cast<QCheckBox*>(sender());

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		if (pCheckBox == m_pOutCheckBox[nIndex])
		{
			m_pManualParas->m_binOut[nIndex].nState = pCheckBox->isChecked();
			emit sig_updataParas();
			break;
		}
	}
}

// void QSttMacroParaEditViewManual::slot_UpdateUdcEditEnabled()
// {
// 	m_oParas.slot_UpdateUdcEditEnabled();
// }
