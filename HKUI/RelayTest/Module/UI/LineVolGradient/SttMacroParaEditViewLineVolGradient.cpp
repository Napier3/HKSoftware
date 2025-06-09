#include "SttMacroParaEditViewLineVolGradient.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../Gradient/GradientSettingDlg.h"
#include "../SttTestCntrFrameAPI.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_6U6I.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../SttGlobalDef.h"
#include <QMessageBox>
#include "../Controls/SttTabWidget.h"
#include"../../Module/XLangResource_Native.h"
#include "../Gradient/GradientSettingValueDlg.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "ui_SttMacroParaEditViewSequenceGradient.h"
#include "LineVolGradientEstimateDlg.h"
#include "../../XLangResource_Native.h"
QSttMacroParaEditViewLineVolGradient* g_LineVolGradientMain = NULL;
QSttMacroParaEditViewLineVolGradient::QSttMacroParaEditViewLineVolGradient(QWidget *parent) :
ui(new Ui::QSttMacroParaEditViewSequenceGradient)
{
	ui->setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint);
	InitLanuage();

	g_LineVolGradientMain = this;
	m_bTmtParaChanged = false;
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;
	m_pGroupWidget = NULL;

	m_strParaFileTitle = g_sLangTxt_State_IncreExperfile; 
	m_strParaFilePostfix = "project(*.grtxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("LineVolGradient.grtxml");

	//CreateTestResource();

	SetData(CreateTestParas(GetMacroID()));

    m_pOriginalSttTestResource = stt_GetSttTestResource();
	stt_Frame_InitTestResource();

	if (g_oSystemParas.m_nHasDigital)//zhouhj 在打开测试模板前先初始化当前GOOSE发布数据
	{
		InitGoosePubDataGroups();
		InitFT3PubDataGroups();
	}

	OpenTestTestMngrFile(m_strDefaultParaFile);

	m_pCurPara = (tmt_LineVolGradientParasEx*)(&m_pCurTest->m_oLineVolGradientParasEx);

	SetDatas(0);
	m_pCurPara->m_nSttTestMode = 0;

	InitUI();
	InitParas();
	InitMannualparas();
	InitConnections();
	InitStyle();

	stt_Frame_Ats_UpdateButtonStateByID(STT_CMD_TYPE_ATS_ManuTriger,false,false);

	ui->m_btnSettingValue->hide();
}

QSttMacroParaEditViewLineVolGradient::~QSttMacroParaEditViewLineVolGradient()
{
	if(m_pCurTest != NULL)
	{
		delete m_pCurTest;
		m_pCurTest = NULL;
	}

	delete ui;
}

void QSttMacroParaEditViewLineVolGradient::ShowReport(CDvmValues *pValues)
{
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

void QSttMacroParaEditViewLineVolGradient::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewLineVolGradient::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize_LineVol(m_pCurPara, &oRead);
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系
	}

	if (m_oLineVolGradientChs.GetCount() == 0)
	{
		if (g_oSttTestResourceMngr.m_pTestResouce != NULL)
		{
			g_oSttTestResourceMngr.m_pTestResouce->AddGradientChs_All(m_oLineVolGradientChs);
		}
	}

	stt_Frame_InitVectorWidget(m_pCurPara->m_uiVOL[0],m_pCurPara->m_uiCUR[0]);
	stt_Frame_InitPowerWidget(m_pCurPara->m_uiVOL[0],m_pCurPara->m_uiCUR[0]);
	stt_Frame_InitStateMonitor(true, NULL);
	stt_Frame_InitStateMonitor(m_pCurPara->m_nChannel, m_pCurPara->m_nType, stt_Frame_IsTestStarted(), this);
	stt_Frame_ClearInfoWidget();

	InitParas();

	UpdateGoutTab();
	UpdateFT3Tab();

	//切换界面时重新串行化出非递变通道界面
	if(m_pGroupWidget)
	{
		m_pGroupWidget->Update();

		CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oLineVolGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
		m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);
	}
}

void QSttMacroParaEditViewLineVolGradient::startInit()
{
	ui->m_cbbDirection->setEnabled(false);
	ui->m_gpMannual->setEnabled(false);
	ui->m_cbbVar->setDisabled(true);
	ui->m_cbbVar->setEnabled(false);
	ui->m_cbbVarType->setDisabled(true);
	ui->m_cbbVarType->setEnabled(false);
	ui->m_cbbType->setDisabled(true);
	ui->m_cbbDirection->setDisabled(true);
	ui->m_editInit->setDisabled(true);
	ui->m_editFinish->setDisabled(true);
	ui->m_editStep->setDisabled(true);
	ui->m_editTime->setDisabled(true);
	ui->m_cbbType->setDisabled(true);
	m_pGroupWidget->SetEnabledUI(false);

	if ((m_pGooseParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		m_pGooseParaWidget->SetGooseDisabled(TRUE);
	}

	if ((m_pFT3OutParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
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

void QSttMacroParaEditViewLineVolGradient::stopInit()
{
	ui->m_gpMannual->setEnabled(true);
	ui->m_cbbVar->setDisabled(false);

	//2024-10-23 wuxinyi 修改停止测试以下控件依旧不使能
// 	ui->m_cbbVarType->setDisabled(false);
// 	ui->m_cbbType->setDisabled(false);
// 	ui->m_cbbDirection->setDisabled(false);

	ui->m_editInit->setDisabled(false);
	ui->m_editFinish->setDisabled(false);
	ui->m_editStep->setDisabled(false);
	ui->m_editTime->setDisabled(false);
	m_pGroupWidget->SetEnabledUI(true);
	ui->m_gpBin->setDisabled(false);
	ui->m_gpBoutNormal->setDisabled(false);
	ui->m_gpBoutError->setDisabled(false);
	ui->m_btnSettingValue->setDisabled(false);
	ui->m_btnEstimate->setDisabled(false);
	ui->m_btnMoreOut->setDisabled(false);

	if ((m_pGooseParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		m_pGooseParaWidget->SetGooseDisabled(FALSE);
	}

	if ((m_pFT3OutParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		m_pFT3OutParaWidget->SetGooseDisabled(FALSE);
	}

	InitEnableButtons();
//	EnableRadientType();
}

void QSttMacroParaEditViewLineVolGradient::InitEnableButtons()
{
	long nGradientChannel = GetSttLineVolGradientChannelType(m_pCurPara->m_nChannel);
	BOOL bCurentChannel = FALSE,bVoltageChannel = FALSE;

	if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_CURR)
	{
		bCurentChannel = TRUE;

	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_VOLT)
	{
		bVoltageChannel = TRUE;


	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_CURR)
	{
		bCurentChannel = TRUE;


	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_VOLT)
	{
		bVoltageChannel = TRUE;


	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_ALL_CURR)
	{
		bCurentChannel = TRUE;


	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_ALL_VOLT)
	{
		bVoltageChannel = TRUE;
	}
// 	else if (m_pCurPara->m_nChannel == freAll_type)
// 	{
// 	}

}

void QSttMacroParaEditViewLineVolGradient::OnViewTestLink(BOOL b)
{

}

void QSttMacroParaEditViewLineVolGradient::OnViewTestStart()
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
	stt_Frame_InitStateMonitor(m_pCurPara->m_nChannel, m_pCurPara->m_nType, stt_Frame_IsTestStarted());
	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();
	stt_Frame_EnableManualTriggerButton(false);
}

void QSttMacroParaEditViewLineVolGradient::OnViewTestStop()
{
	stopInit();
	stt_Frame_StopStateMonitor();
	stt_Frame_StopVectorWidget();
	stt_Frame_StopPowerWidget();
}

CString QSttMacroParaEditViewLineVolGradient::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += FILE_GRADIENT;
	strFile += _T(".");
	strFile += POSTFIX_GRADIENT;

	return strFile;
}

bool QSttMacroParaEditViewLineVolGradient::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
{
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != POSTFIX_GRADIENT)
	{
		return false;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return false;
	}

	return true;
}

void QSttMacroParaEditViewLineVolGradient::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
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

void QSttMacroParaEditViewLineVolGradient::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateLineVolGradientChs();
	InitParas();

	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();

	updateLabName();

	if (m_pGroupWidget)
	{
		m_pGroupWidget->InitLineVolGridData(m_pCurPara);

	}
}

void QSttMacroParaEditViewLineVolGradient::UpdateGoutTab(BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)//zhouhj 在打开测试模板前先初始化当前GOOSE发布数据
	{
		InitGoosePubDataGroups();
		UpdateGoutTab_UI(m_listGoosePub.at(0));
	}
	else
	{
		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewLineVolGradient::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if ((m_pGooseParaWidget == NULL)&&(g_oSystemParas.m_nHasDigital)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC> 0))//更新前无GOOSE界面,更新后需要GOOSE界面
	{
		AddGooseParaWidget(pCfgGoutDatas);

		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
	}
	else if ((m_pGooseParaWidget != NULL)&&(!g_oSystemParas.m_nHasDigital))//更新前有GOOSE界面,更新后不需要
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));

		RemoveGooseParaWidget();
	}
	else if ((m_pGooseParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
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

		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewLineVolGradient::UpdateFT3Tab(BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)//zhouhj 在打开测试模板前先初始化当前GOOSE发布数据
	{
		InitFT3PubDataGroups();
		UpdateFT3Tab_UI(m_listFT3Pub.at(0));
	}
	else
	{
		RemoveFT3OutParaWidget();
	}
}

void QSttMacroParaEditViewLineVolGradient::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
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

void QSttMacroParaEditViewLineVolGradient::UpdateBinBoutExTab()
{

}

void QSttMacroParaEditViewLineVolGradient::AddUnGradientSettingWidget()
{
	if (m_pGroupWidget)
	{
		return;
	}

	m_pGroupWidget=new QLineVolGradientGroupWidget(this);	
	m_pGroupWidget->InitLineVolGrid(m_pCurPara);
	int nInsertPos = 1;
	CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Gradient_UnChangingSet");
	ui->m_tabWidget->insertTab(nInsertPos,m_pGroupWidget,strTitle);

	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oLineVolGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
	m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);	

	m_pCurPara->m_nSttTestMode=3;
}

void QSttMacroParaEditViewLineVolGradient::RemoveUnGradientSettingWidget()
{
	if(m_pGroupWidget == NULL)
	{
		return;
	}

	int nIndex = ui->m_tabWidget->indexOf(m_pGroupWidget);
	ui->m_tabWidget->removeTab(nIndex);

	delete m_pGroupWidget;
	m_pGroupWidget = NULL;
	m_pCurPara->m_nSttTestMode = 0;
}
void QSttMacroParaEditViewLineVolGradient::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,FALSE);
	int nInsertPos = 2;
	CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	ui->m_tabWidget->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewLineVolGradient::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,TRUE);
	int nInsertPos = 3;

	CString strTitle=/*_T("FT3发布")*/g_sLangTxt_Gradient_ReleasedFTT;

	ui->m_tabWidget->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewLineVolGradient::RemoveFT3OutParaWidget()
{
	if(m_pFT3OutParaWidget == NULL)
	{
		return;
	}

	int nIndex = ui->m_tabWidget->indexOf(m_pFT3OutParaWidget);
	ui->m_tabWidget->removeTab(nIndex);

	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

void QSttMacroParaEditViewLineVolGradient::RemoveGooseParaWidget()
{
	if(m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = ui->m_tabWidget->indexOf(m_pGooseParaWidget);
	ui->m_tabWidget->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

bool QSttMacroParaEditViewLineVolGradient::ExistGooseParaWidget()
{
	int nIndex = ui->m_tabWidget->indexOf(m_pGooseParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewLineVolGradient::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		ui->m_tabWidget->setTabEnabled(ui->m_tabWidget->indexOf(m_pGooseParaWidget),b);
	}
}

bool QSttMacroParaEditViewLineVolGradient::ExistFT3OutParaWidget()
{
	int nIndex = ui->m_tabWidget->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewLineVolGradient::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		ui->m_tabWidget->setTabEnabled(ui->m_tabWidget->indexOf(m_pFT3OutParaWidget),b);
	}
}
CString QSttMacroParaEditViewLineVolGradient::GetCurChannal(PTMT_PARAS_HEAD pParas)
{
	CDataTypeValue* pDataType =  (CDataTypeValue*)m_oLineVolGradientChs.FindByIndex(m_pCurTest->m_oLineVolGradientParasEx.m_nChannel);
	if(pDataType)
	{
		return pDataType->m_strID;
	}
	return "";
}

void QSttMacroParaEditViewLineVolGradient::InitLanuage()
{
	CString strText;
	xlang_GetLangStrByFile(strText, "Gradient_TimeBeforeChange");
	ui->m_labTimeBeforeChange->setText(strText + "(s):");
	xlang_GetLangStrByFile(strText, "Gradient_TimeBeforeFail");
	ui->m_labTimeBeforeFail->setText(strText/*.right(4)*/ + "(s):");
	ui->m_cbBefore->setText(strText.left(2));
	xlang_GetLangStrByFile(strText, "sVariable");
	ui->m_labVar->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Gradient_VarType");
	ui->m_labVarType->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Native_Current");
	xlang_GetLangStrByFile(strText, "Native_Current");
	xlang_GetLangStrByFile(strText, "Native_Voltage");
	xlang_GetLangStrByFile(strText, "Native_Voltage");
	xlang_GetLangStrByFile(strText, "Gradient_Phase");
#ifndef _PSX_QT_LINUX_ 
	//ui->m_labfDiffIAngle->setText(strText + QString::fromLocal8Bit("(G1,G2)(°):"));
#endif
	xlang_GetLangStrByFile(strText, "Gradient_Init");
	ui->m_labInit->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Gradient_Finish");
	ui->m_labFinish->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Gradient_Step");
	ui->m_labStep->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Gradient_Time");
	ui->m_labTime->setText(strText + "(s):");
	xlang_GetLangStrByFile(strText, "Gradient_Direction");
	ui->m_labDirection->setText(strText + ":");
	xlang_SetLangStrToWidget(ui->m_labType, "Native_Type", XLang_Ctrls_QLabel);
	xlang_GetLangStrByFile(m_strCurrent, "Native_Current");
	xlang_GetLangStrByFile(m_strVoltage, "Native_Voltage");
	xlang_GetLangStrByFile(m_strFreq, "Native_Freq");

	xlang_GetLangStrByFile(strText, "Gradient_VarSet");
	ui->m_gpVarSet->setTitle(strText);
	xlang_GetLangStrByFile(strText, "Gradient_ChangingSet");
	xlang_GetLangStrByFile(strText, "Gradient_UnChangingSet");
	ui->m_tabWidget->setTabText(0, g_sLangTxt_Gradient_ChangingSet);

	xlang_GetLangStrByFile(strText, "Native_LogicAnd");
	ui->m_rbAnd->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_LogicOr");
	ui->m_rbOr->setText(strText);
	xlang_SetLangStrToWidget(ui->m_gpBin, "Native_Bin", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(ui->m_gpBoutNormal, "Gradient_Normal", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(ui->m_gpBoutError, "Gradient_Failure", XLang_Ctrls_QGroupBox);

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
	xlang_GetLangStrByFile(strText,"Native_Bout");

	CString str;
	xlang_GetLangStrByFile(str,"Gradient_Normal");
	ui->m_gpBoutNormal->setTitle(strText+str);
	xlang_GetLangStrByFile(str,"Gradient_Failure");
	ui->m_gpBoutError->setTitle(strText+str);

	xlang_SetLangStrToWidget(ui->m_btnMoreOut, "Gradient_BoutSets", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnEstimate, "State_Estimate", XLang_Ctrls_QPushButton);

}

PTMT_PARAS_HEAD QSttMacroParaEditViewLineVolGradient::CreateTestParas(const char * pszMacroID)
{
	PTMT_PARAS_HEAD pNewTest = new tmt_LineVolGradientTestEx;	
	strcpy(pNewTest->m_oRsltExprMngr.m_pszExprGroupID, STT_RSLTEXPR_MACROID_COMMON);  

	return pNewTest;
}

PTMT_PARAS_HEAD QSttMacroParaEditViewLineVolGradient::CreateTestParas(PTMT_PARAS_HEAD pCurr)
{
	ASSERT(pCurr != NULL);

	tmt_LineVolGradientTestEx* pCurrTest = (tmt_LineVolGradientTestEx*)pCurr;
	tmt_LineVolGradientTestEx* pNewTest = new tmt_LineVolGradientTestEx;

	memcpy(pNewTest,pCurrTest,sizeof(tmt_LineVolGradientTestEx));

	stt_clone_expr_mngr(pCurr, pNewTest);

	pNewTest->m_nTestState = 0;
	pNewTest->clear_result();

	return (PTMT_PARAS_HEAD)pNewTest;
}

void QSttMacroParaEditViewLineVolGradient::SetData(PTMT_PARAS_HEAD pCurr)
{
	ASSERT(m_pCur != NULL);
	m_pCurTest = (tmt_LineVolGradientTestEx*)pCurr;

	m_pCurPara = (tmt_LineVolGradientParasEx*)&m_pCurTest->m_oLineVolGradientParasEx;
	m_pCurResult = (tmt_LineVolGradientResult*)&m_pCurTest->m_oLineVolGradientResultParas;
}

void QSttMacroParaEditViewLineVolGradient::InitStyle()
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

void QSttMacroParaEditViewLineVolGradient::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
													   long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	for (int i = 0; i < 6; i++)
	{
		m_pCurPara->m_uiCUR[1][i].Harm[1].fAmp = m_pCurPara->m_uiCUR[0][i].Harm[1].fAmp;
		m_pCurPara->m_uiCUR[1][i].Harm[1].fAngle = m_pCurPara->m_uiCUR[0][i].Harm[1].fAngle;
		m_pCurPara->m_uiCUR[1][i].Harm[1].fFreq = m_pCurPara->m_uiCUR[0][i].Harm[1].fFreq;
		m_pCurPara->m_uiVOL[1][i].Harm[1].fAmp = m_pCurPara->m_uiVOL[0][i].Harm[1].fAmp;
		m_pCurPara->m_uiVOL[1][i].Harm[1].fAngle = m_pCurPara->m_uiVOL[0][i].Harm[1].fAngle;
		m_pCurPara->m_uiVOL[1][i].Harm[1].fFreq = m_pCurPara->m_uiVOL[0][i].Harm[1].fFreq;
	}

	tmt_linevolgradient_test_ex *pGradientParas = (tmt_linevolgradient_test_ex*)pParas;

	if(stt_xml_serialize_is_read(pMacroParas) || stt_xml_serialize_is_register(pMacroParas))
	{
		stt_xml_serialize_LineVol_ex(&pGradientParas->m_oLineVolGradientParasEx, pMacroParas);	//文件的读写
	}
	else if (pParas->m_nSelected)
	{
		stt_xml_serialize_LineVol_ex(&pGradientParas->m_oLineVolGradientParasEx, pMacroParas);	//测试参数下发
	}


	if (bHasGoosePub)
	{
		CIecCfgGoutDatas *pGoutDatas = m_listGoosePub.at(0);
		ASSERT(pGoutDatas);
		SerializeGoosePubs(pMacroParas,pGoutDatas);

		CIecCfgDatasSMV *pDatasSMV = m_listFT3Pub.at(0);
		ASSERT(pDatasSMV);
		SerializeFT3Pubs(pMacroParas,pDatasSMV);
	}

}

void QSttMacroParaEditViewLineVolGradient::on_m_btnManual_clicked()//点击调出子窗口
{
	QGradientSettingDlg dlg((tmt_GradientParasEx*)m_pCurPara, this);
	dlg.setWindowModality(Qt::WindowModal);//模态窗口
	CString strText;
	strText = /*"开出量设置"*/g_sLangTxt_Gradient_BoutSet;
	//xlang_GetLangStrByFile(strText, "Native_CommonPara");
	dlg.setWindowTitle(strText);

	dlg.exec();

	//更新主窗口的值
	if (dlg.m_nIsOK == 1)
	{
		CopyBinaryConfig();
		stt_Frame_UpdateToolButtons();

		tmt_LineVolGradientParasEx* pLineVolGradientPara = m_pCurPara;
		ui->m_cbBOut1->setChecked(pLineVolGradientPara->m_binOut[0][0].nState);
		ui->m_cbBOut2->setChecked(pLineVolGradientPara->m_binOut[0][1].nState);
		ui->m_cbBOut3->setChecked(pLineVolGradientPara->m_binOut[0][2].nState);
		ui->m_cbBOut4->setChecked(pLineVolGradientPara->m_binOut[0][3].nState);
		ui->m_cbBOut1_E->setChecked(pLineVolGradientPara->m_binOut[1][0].nState);
		ui->m_cbBOut2_E->setChecked(pLineVolGradientPara->m_binOut[1][1].nState);
		ui->m_cbBOut3_E->setChecked(pLineVolGradientPara->m_binOut[1][2].nState);
		ui->m_cbBOut4_E->setChecked(pLineVolGradientPara->m_binOut[1][3].nState);
	}
//	stt_xml_serialize_write_LineVolGradientTest();


}

void QSttMacroParaEditViewLineVolGradient::on_m_cbbVar_currentIndexChanged(int index)
{
	if(ui->m_cbbVar->IsScrolling())
	{
		return;
	}

	if(m_pCurPara == NULL)
	{
		return;
	}


	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oLineVolGradientChs.GetAtIndex(index);
	ASSERT(pCurDataTypeValue);
	long nOldChannel = m_pCurPara->m_nChannel;
	m_pCurPara->m_nChannel = pCurDataTypeValue->GetIndex();
// 
// 	disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
// 	ui->m_cbbVarType->clear();
// 	if(m_pCurPara->m_nChannel == iabcAdd_type || m_pCurPara->m_nChannel == ia2b2c2Add_type)
// 	{
// 		ui->m_cbbVarType->addItems(m_ChangeTypeList2);
// 	}
// 	else
// 	{
// 		ui->m_cbbVarType->addItems(m_ChangeTypeList);
// 		ui->m_cbbVarType->setCurrentIndex(m_pCurPara->m_nType);
// 	}
// 
// 	connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
// 
// 	if (m_pCurPara->m_nChannel == freAll_type)
// 	{
// 		m_pCurPara->m_nType = fre_type;
// 		disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
// 		ui->m_cbbVarType->setCurrentIndex(fre_type);
// 		connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
// 	}
// 	else if (m_pCurPara->m_nType == fre_type)
// 	{
// 		m_pCurPara->m_nType = amplitude_type;
// 		disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
// 		ui->m_cbbVarType->setCurrentIndex(amplitude_type);
// 		connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
// 	}
// 
	if (nOldChannel != m_pCurPara->m_nChannel)
	{
		InitUI_AfterGridentSel();
	}

	g_LineVolGradientMain->m_bTmtParaChanged = TRUE;
	if(LINEVOL_CHANNAL_TYPE_I(m_pCurPara->m_nChannel))
	{
		m_pCurPara->m_nVarIndexType = 0;
	}
	else if (LINEVOL_CHANNAL_TYPE_U(m_pCurPara->m_nChannel))
	{
		m_pCurPara->m_nVarIndexType = 1;
	}

	m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);
}

void QSttMacroParaEditViewLineVolGradient::on_m_cbbVarType_currentIndexChanged(int index)
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

// 	if ((m_pCurPara->m_nType != fre_type)&&(m_pCurPara->m_nChannel == freAll_type))
// 	{
// 		disconnect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
// 		m_pCurPara->m_nChannel = LineVolt_vab1_type;
// 		InitGradientChannel(LineVolt_vab1_type);
// 		connect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
// 	}

	on_m_editInitChanged();
	on_m_editFinishChanged();
	on_m_editStepChanged();
	on_m_editTimeChanged();

	InitUI_AfterGridentSel();

//	EnableRadientType();

	g_LineVolGradientMain->m_bTmtParaChanged = TRUE;

	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oLineVolGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
	m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);
}

void QSttMacroParaEditViewLineVolGradient::on_m_cbbType_currentIndexChanged(int index)
{
	if(ui->m_cbbType->IsScrolling())
	{
		return;
	}

	if (m_pCurPara->m_nTestMode != index)
	{
		m_pCurPara->m_nTestMode = index;
		emit sig_Para_ReturnTypeIndexChanged(index);

		g_LineVolGradientMain->m_bTmtParaChanged = TRUE;
	}

//	EnableRadientType();
}

// void QSttMacroParaEditViewLineVolGradient::on_m_cbbDirection_currentIndexChanged(int index)
// {
// 	if(ui->m_cbbDirection->IsScrolling())
// 	{
// 		return;
// 	}
// 
// 	if (m_pCurPara->m_nPhaseGradDir != index)
// 	{
// 		m_pCurPara->m_nPhaseGradDir = index;
// 		m_bTmtParaChanged = TRUE;
// 	}
// }

void QSttMacroParaEditViewLineVolGradient::on_m_cbBefore_clicked(int nState)
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

void QSttMacroParaEditViewLineVolGradient::on_m_editInit_clicked()
{
	slot_edit_changed(ui->m_editInit, TRUE);
}

void QSttMacroParaEditViewLineVolGradient::on_m_editFinish_clicked()
{
	slot_edit_changed(ui->m_editFinish, TRUE);
}

void QSttMacroParaEditViewLineVolGradient::on_m_editStep_clicked()
{
	slot_edit_changed(ui->m_editStep, TRUE);
}

void QSttMacroParaEditViewLineVolGradient::on_m_editTime_clicked()
{
	slot_edit_changed(ui->m_editTime, TRUE);
}

void QSttMacroParaEditViewLineVolGradient::on_m_editInitChanged()
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
					fv = g_oLocalSysPara.m_fAC_VolMax*1.73205;
				}
				else
				{
					fv = -g_oLocalSysPara.m_fAC_VolMax*1.73205;
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

			connect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
		}
	}
// 	else if (m_pCurPara->m_nType == phasor_type)
// 	{
// 		float f1 = fv - (int)fv;
// 		int f2 = ((int)fv)%360;
// 		fv = f1+f2;
// 
// 		disconnect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
// 		{
// 			if (m_pCurPara->m_fStart != fv)
// 			{
// 				m_pCurPara->m_fStart = fv;
// 				emit sig_Para_StartChanged(fv);
// 				m_bTmtParaChanged = TRUE;
// 			}
// 
// 			ui->m_editInit->setText(QString::number(fv,'f',1));
// 		}
// 
// 		connect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
// 	}
// 	else
// 	{
// 		if (fabs(fv) > nMaxFreq)
// 		{
// 			if (fv > 0)
// 			{
// 				fv = nMaxFreq;
// 			}
// 			else
// 			{
// 				fv = -nMaxFreq;
// 			}
// 		}
// 		else if(fv < 10)
// 		{
// 			fv = 10;
// 		}
// 
// 		disconnect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
// 		{
// 			if (m_pCurPara->m_fStart != fv)
// 			{
// 				m_pCurPara->m_fStart = fv;
// 				emit sig_Para_StartChanged(fv);
// 				m_bTmtParaChanged = TRUE;
// 			}
// 
// 			ui->m_editInit->setText(QString::number(fv,'f',3));
// 
// 			float fdown=0;
// 			float fup=0;
// 			getYRange(1,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
// 			emit sig_YRangeChanged(fre_type, m_strFreq + "(Hz)",fdown,fup*FRADIO);
// 		}
// 
// 		connect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
// 	}

	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oLineVolGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
	m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);
}

void QSttMacroParaEditViewLineVolGradient::on_m_editFinishChanged()
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

			connect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
		}
		else if (str.contains(tr("U")))
		{
			if (fabs(fv) > g_oLocalSysPara.m_fAC_VolMax)
			{
				if (fv > 0)
				{
					fv = g_oLocalSysPara.m_fAC_VolMax*1.73205;
				}
				else
				{
					fv = -g_oLocalSysPara.m_fAC_VolMax*1.73205;
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
// 	else if (m_pCurPara->m_nType == phasor_type)
// 	{
// 		float f1 = fv - (int)fv;
// 		int f2 = ((int)fv)%360;
// 		fv = f1+f2;
// 
// 		disconnect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
// 		{
// 			if (m_pCurPara->m_fStop != fv)
// 			{
// 				m_pCurPara->m_fStop = fv;
// 				emit sig_Para_EndChanged(fv);
// 				m_bTmtParaChanged = TRUE;
// 			}
// 
// 			ui->m_editFinish->setText(QString::number(fv,'f',1));
// 		}
// 
// 		connect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
// 	}
// 	else
// 	{
// 		if (fabs(fv) > nMaxFreq)
// 		{
// 			if (fv > 0)
// 			{
// 				fv = nMaxFreq;
// 			}
// 			else
// 			{
// 				fv = -nMaxFreq;
// 			}
// 		}
// 		else if(fv < 10)
// 		{
// 			fv = 10;
// 		}
// 
// 		disconnect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
// 		{
// 			if (m_pCurPara->m_fStop != fv)
// 			{
// 				m_pCurPara->m_fStop = fv;
// 				emit sig_Para_EndChanged(fv);
// 				m_bTmtParaChanged = TRUE;
// 			}
// 
// 			ui->m_editFinish->setText(QString::number(fv,'f',3));
// 
// 			float fdown=0;
// 			float fup=0;
// 			getYRange(1,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
// 			emit sig_YRangeChanged(fre_type, m_strFreq + "(Hz)",fdown,fup*FRADIO);
// 		}
// 
// 		connect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(slot_Para_EndChanged()));
// 	}
}

void QSttMacroParaEditViewLineVolGradient::on_m_editStepChanged()
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
// 	else if (m_pCurPara->m_nType == phasor_type)
// 	{
// 		float f1 = fv - (int)fv;
// 		int f2 = ((int)fv)%360;
// 		fv = f1+f2;
// 		if (fv == 0)
// 		{
// 			fv = 0.001;
// 		}
// 
// 		disconnect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
// 		{
// 			if(m_pCurPara->m_fStep != fv)
// 			{
// 				m_pCurPara->m_fStep = fv;
// 				emit sig_Para_StepChanged(fv);
// 				m_bTmtParaChanged = TRUE;
// 			}
// 
// 			ui->m_editStep->setText(QString::number(fv,'f',3));
// 		}
// 
// 		connect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
// 	}
// 	else
// 	{
// 		if (fabs(fv) > nMaxFreq)
// 		{
// 			if (fv > 0)
// 			{
// 				fv = nMaxFreq;
// 			}
// 			else
// 			{
// 				fv = -nMaxFreq;
// 			}
// 		}
//
// 		if (fv == 0)
// 		{
// 			fv = 0.001;
// 		}
// 
// 		disconnect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
// 		{
// 			if(m_pCurPara->m_fStep != fv)
// 			{
// 				m_pCurPara->m_fStep = fv;
// 				emit sig_Para_StepChanged(fv);
// 				m_bTmtParaChanged = TRUE;
// 			}
// 
// 			ui->m_editStep->setText(QString::number(fv,'f',3));
// 		}
// 
// 		connect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StepChanged()));
// 	}
}

void QSttMacroParaEditViewLineVolGradient::on_m_editTimeChanged()
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

void QSttMacroParaEditViewLineVolGradient::slot_Estimate()
{
	LineVolGradientEstimateDlg dlg((tmt_LineVolGradientParasEx*)m_pCurPara, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewLineVolGradient::slot_SettingValue()
{
	GradientSettingValueDlg dlg((tmt_GradientParasEx*)m_pCurPara, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewLineVolGradient::SetLineVoltGradientFont()
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

void QSttMacroParaEditViewLineVolGradient::InitUI()
{
	SetLineVoltGradientFont();
	((QSttTabWidget*)ui->m_tabWidget)->InitStyleSheet();

	disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	disconnect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));
//	disconnect(ui->m_cbbDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbDirection_currentIndexChanged( int)));

	CString strText;
	xlang_GetLangStrByFile(strText, "Gradient_Anticlockwise");
	ui->m_cbbDirection->addItem(strText);
	xlang_GetLangStrByFile(strText, "Gradient_Clockwise");
	ui->m_cbbDirection->addItem(strText);
	ui->m_cbbDirection->setEnabled(false);

	initMaxPositiveEdit(ui->m_editInit);
	initMaxPositiveEdit(ui->m_editFinish);
	initMaxPositiveEdit(ui->m_editStep);
	initMaxPositiveEdit(ui->m_editTime);

	initQList();

	UpdateLineVolGradientChs();

	ui->m_cbbVarType->clear();
	ui->m_cbbVarType->addItems(m_ChangeTypeList);
	ui->m_cbbType->clear();

//	connect(ui->m_cbbDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbDirection_currentIndexChanged( int)));
	connect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));
	connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));

	ui->m_cbBefore->InitStyleSheet();
	ui->m_cbBefore->setChecked(true);


	if (m_pGroupWidget ==NULL)
	{
		AddUnGradientSettingWidget();
	}
	else
	{
		RemoveUnGradientSettingWidget();
	}
}

void QSttMacroParaEditViewLineVolGradient::InitGradientChannel(LineVolt_type vartype)
{
	CDataTypeValue *pCurSelData = m_oLineVolGradientChs.FindByIndex(vartype);

	if (pCurSelData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的递变通道(Index=%d)未查找到."),vartype);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurselinNotFound.GetString(),vartype); //当前选择的递变通道(Index=%d)未查找到. lcq 3.14
		return;
	} 
	else
	{
		long nIndex = m_oLineVolGradientChs.FindIndex(pCurSelData);
		ui->m_cbbVar->setCurrentIndex(nIndex);
	}
}

void QSttMacroParaEditViewLineVolGradient::updateLabName()
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
// 	case phasor_type:
// 		{
// 	
// 
// 			ui->m_labInit->setText(strInit + strPhase);
// 			ui->m_labFinish->setText(strFinish + strPhase);
// 			ui->m_labStep->setText(strStep + strPhase);
// 
// 
// 			float fdown=0;
// 			float fup=0;
// 			if(m_pCurPara->m_fStart > m_pCurPara->m_fStop)
// 			{
// 				fdown = m_pCurPara->m_fStop;
// 				fup = m_pCurPara->m_fStart;
// 			}
// 			else
// 			{
// 				fup = m_pCurPara->m_fStop;
// 				fdown = m_pCurPara->m_fStart;
// 			}
// 
// 			CString strType;
// 			xlang_GetLangStrByFile(strType, "Native_Angle");
// 			emit sig_YRangeChanged(phasor_type, strType + strPhase.Left(strPhase.length() - 1),fdown/FRADIO,fup*1.3);	//φ
// 		}
// 		break;
// 	case fre_type:
// 		{
// 
// 			ui->m_labInit->setText(strInit + "(Hz):");
// 			ui->m_labFinish->setText(strFinish + "(Hz):");
// 			ui->m_labStep->setText(strStep + "(Hz):");
// 
// 
// 			emit sig_Para_ChangeIsAll();
// 			float fdown=0;
// 			float fup=0;
// 			getYRange(1,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
// 			emit sig_YRangeChanged(fre_type, m_strFreq + "(Hz)",fdown,fup*FRADIO);
// 		}
// 		break;
	default:
		break;
	}
}

void QSttMacroParaEditViewLineVolGradient::initQList()
{
	CString strPhase, strFreq, strAmp;
	CString strAction, strReturn, strAngle;

// 	xlang_GetLangStrByFile(strPhase, "Native_Angle");
// 	xlang_GetLangStrByFile(strFreq, "Native_Freq");
	xlang_GetLangStrByFile(strAmp, "Native_Amplitude");
	xlang_GetLangStrByFile(strAction, "Native_Action");
	strAction = strAction.Mid(0, strAction.ReverseFind('('));
// 	xlang_GetLangStrByFile(strReturn, "Native_ReturnCoeff");
// 	xlang_GetLangStrByFile(strAngle, "Gradient_MaxAngle");

	m_ChangeTypeList.clear();
	m_ChangeTypeList << strAmp;

	m_ChangeTypeList2.clear();
	m_ChangeTypeList2 << strAmp;

	m_listTestMode2.clear();
	m_listTestMode2 << strAction;
	m_listTestMode3.clear();
	m_listTestMode3<< strAction;
}

void QSttMacroParaEditViewLineVolGradient::InitParas()
{
	if(m_pCurPara == NULL)
		return;

	disconnect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
	disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	disconnect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));

	ui->m_cbbVarType->clear();
		ui->m_cbbVarType->addItems(m_ChangeTypeList);
// 	if(m_pCurPara->m_nChannel == iabcAdd_type || m_pCurPara->m_nChannel == ia2b2c2Add_type)
// 	{
// 		ui->m_cbbVarType->addItems(m_ChangeTypeList2);
// 	}
// 	else
// 	{
// 		ui->m_cbbVarType->addItems(m_ChangeTypeList);
// 	}

	LineVolt_type var = getLineVoltParaTypeByInt(m_pCurPara->m_nChannel);
	InitGradientChannel(var);
	ui->m_cbbVarType->setCurrentIndex(m_pCurPara->m_nType);

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
	m_pCurPara->m_fEDFreq = g_oSystemParas.m_fFNom;//Zhouyy 2023/01/06
  	
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

	if (m_pCurPara->m_nSttTestMode == 3)
	{
		//ui->m_cbGroup->setChecked(true);
	}
	else
	{
		//ui->m_cbGroup->setChecked(false);
	}

	//初始化递变方向
	ui->m_cbbDirection->setCurrentIndex(m_pCurPara->m_nPhaseGradDir);
//	EnableRadientType();
	//递变方向灰掉
	ui->m_cbbDirection->setEnabled(false);
	ui->m_cbbVarType->setEnabled(false);
	ui->m_cbbType->setEnabled(false);

	//初始化时间特性曲线的标题
	emit sig_Para_ChangeIndexChanged(m_pCurPara->m_nChannel);

	if(LINEVOL_CHANNAL_TYPE_I(m_pCurPara->m_nChannel))
	{
		m_pCurPara->m_nVarIndexType = 0;
	}
	else if (LINEVOL_CHANNAL_TYPE_U(m_pCurPara->m_nChannel))
	{
		m_pCurPara->m_nVarIndexType = 1;
	}

//	m_pCurPara->m_nVarIndexType = 1;
	CopyBinaryConfig();
	stt_Frame_UpdateToolButtons();
}

void QSttMacroParaEditViewLineVolGradient::InitConnections()
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
	connect(ui->m_btnSettingValue,SIGNAL(clicked()),this,SLOT(slot_SettingValue()));
	connect(ui->m_btnEstimate,SIGNAL(clicked()),this,SLOT(slot_Estimate()));
	connect(ui->m_btnMoreOut,SIGNAL(clicked()),this,SLOT(on_m_btnManual_clicked()));
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
}

void QSttMacroParaEditViewLineVolGradient::CopyBinaryConfig(BOOL b)
{
	tmt_LineVolGradientParasEx* pGradientPara = m_pCurPara;
	if(pGradientPara == NULL)
	{
		return;
	}

	if(b)
	{
		stt_GetBinaryConfig()->m_nBinLogic = pGradientPara->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			stt_GetBinaryConfig()->m_binIn[i].nSelect = pGradientPara->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			stt_GetBinaryConfig()->m_binInEx[i].nSelect = pGradientPara->m_binInEx[i].nSelect;
		}
	}
	else
	{
		pGradientPara->m_nBinLogic = stt_GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			pGradientPara->m_binIn[i].nSelect = stt_GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			pGradientPara->m_binInEx[i].nSelect = stt_GetBinaryConfig()->m_binInEx[i].nSelect;
		}
	}
}


void QSttMacroParaEditViewLineVolGradient::getYRange(float ftime,float fv, float v1,float v2,float fstart,float fend,float &down,float &up )
{
	float fNew=fv;
	if (ftime < EPSINON)
	{
		fNew=0;
	}

	up = getMaxFormThreeValue(getMaxFormThreeValue(fNew,v1,v2),fstart,fend);
	down = getMinFormThreeValue(getMinFormThreeValue(fNew,v1,v2),fstart,fend);
}

void QSttMacroParaEditViewLineVolGradient::UpdateLineVolGradientChs()
{
	if (g_oSttTestResourceMngr.m_pTestResouce != NULL)
	{
		g_oSttTestResourceMngr.m_pTestResouce->AddGradientLineVolt(m_oLineVolGradientChs);
	}
	disconnect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
	ui->m_cbbVar->clear();

	CDataTypeValue *pCurTypeValue = NULL;
	POS pos = m_oLineVolGradientChs.GetHeadPosition();

	while(pos)
	{
		pCurTypeValue = (CDataTypeValue *)m_oLineVolGradientChs.GetNext(pos);
		CString strAllFreq;
		xlang_GetLangStrByFile(strAllFreq, "Gradient_AllFreq");
		if (pCurTypeValue->m_strName == strAllFreq)
		{
			ui->m_cbbVar->addItem(pCurTypeValue->m_strID);
		}
		else
		{
			ui->m_cbbVar->addItem(pCurTypeValue->m_strID.GetString());
		}
	}

	connect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
}

long QSttMacroParaEditViewLineVolGradient::GetSttLineVolGradientChannelType(long nChannel)
{
	if ((nChannel == LineVolt_vab1_type)||(nChannel == LineVolt_v1_0_type))
	{
		return STT_GRADIENT_CHANNEL_TYPE_G1_VOLT;
	}
	else if ((nChannel == LineVolt_vab2_type)||(nChannel == LineVolt_v2_0_type))
	{
		return STT_GRADIENT_CHANNEL_TYPE_G2_VOLT;
	}
	else if ((nChannel == LineVolt_ia1_type)||(nChannel == LineVolt_ib1_type)||(nChannel == LineVolt_ic1_type))
	{
		return STT_GRADIENT_CHANNEL_TYPE_G1_CURR;
	}
	else if ((nChannel == LineVolt_ia2_type)||(nChannel == LineVolt_ib2_type)||(nChannel == LineVolt_ic2_type))
	{
		return STT_GRADIENT_CHANNEL_TYPE_G2_CURR;
	}

	return null_type;
}

void QSttMacroParaEditViewLineVolGradient::InitUI_AfterGridentSel()
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

	disconnect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int))); 

	long nGradientChannel = GetSttLineVolGradientChannelType(m_pCurPara->m_nChannel);
	BOOL bCurentChannel = FALSE,bVoltageChannel = FALSE;

	if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_CURR)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Current = m_pCurPara->m_fEDI;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
			// 			ui->m_editVarA1->setText(QString::number(m_pCurPara->m_fG1Current,'f',3));
		}
		// 
		bCurentChannel = TRUE;

	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_VOLT)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Volt = m_pCurPara->m_fEDU;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
			//  		ui->m_editVarV1->setText(QString::number(m_pCurPara->m_fG1Volt,'f',3));
		}

		bVoltageChannel = TRUE;


	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_CURR)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG2Current = m_pCurPara->m_fEDI;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
			//  		ui->m_editVarA2->setText(QString::number(m_pCurPara->m_fG2Current,'f',3));
		}

		bCurentChannel = TRUE;


	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_VOLT)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG2Volt = m_pCurPara->m_fEDU;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
			//  			ui->m_editVarV2->setText(QString::number(m_pCurPara->m_fG2Volt,'f',3));
		}

		bVoltageChannel = TRUE;

	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_ALL_CURR)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Current = m_pCurPara->m_fEDI;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
			// 			ui->m_editVarA1->setText(QString::number(m_pCurPara->m_fG1Current,'f',3));
			m_pCurPara->m_fG2Current = m_pCurPara->m_fEDI;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
			//  			ui->m_editVarA2->setText(QString::number(m_pCurPara->m_fG2Current,'f',3));
		}

		bCurentChannel = TRUE;


	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_ALL_VOLT)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Volt = m_pCurPara->m_fEDU;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
			// 			ui->m_editVarV1->setText(QString::number(m_pCurPara->m_fG1Volt,'f',3));
			m_pCurPara->m_fG2Volt = m_pCurPara->m_fEDU;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
			// 			ui->m_editVarV2->setText(QString::number(m_pCurPara->m_fG2Volt,'f',3));
		}

		bVoltageChannel = TRUE;

	}
// 	else if (m_pCurPara->m_nChannel == freAll_type)
// 	{
// 
// 	}


// 	if(m_pCurPara->m_nChannel == iabcAdd_type || m_pCurPara->m_nChannel == ia2b2c2Add_type)
// 	{
// 		m_pCurPara->m_nType = amplitude_type;
// 	}

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
	case amplitude_type:
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
// 	case phasor_type:
// 		{
// 			emit sig_Para_ChangeIndexChanged(m_pCurPara->m_nChannel);
// 			ui->m_labInit->setText(strInit + strPhase);
// 			ui->m_labFinish->setText(strFinish + strPhase);
// 			ui->m_labStep->setText(strStep + strPhase);
// 
// 
// 			float fdown=0;
// 			float fup=0;
// 			if(m_pCurPara->m_fStart > m_pCurPara->m_fStop)
// 			{
// 				fdown = m_pCurPara->m_fStop;
// 				fup = m_pCurPara->m_fStart;
// 			}
// 			else
// 			{
// 				fup = m_pCurPara->m_fStop;
// 				fdown = m_pCurPara->m_fStart;
// 			}
// 
// 			CString strType;
// 			xlang_GetLangStrByFile(strType, "Native_Angle");
// 			emit sig_YRangeChanged(phasor_type, strType + strPhase.left(strPhase.length() - 1),fdown/FRADIO,fup*1.3);
// 		}
// 		break;
// 	case fre_type:
// 		{
// 
// 			ui->m_labInit->setText(strInit + "(Hz):");
// 			ui->m_labFinish->setText(strFinish + "(Hz):");
// 			ui->m_labStep->setText(strStep + "(Hz):");
// 			emit sig_Para_ChangeIsAll();
// 			float fdown=0;
// 			float fup=0;
// 			getYRange(1,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
// 			emit sig_YRangeChanged(fre_type, m_strFreq + "(Hz)",fdown,fup*FRADIO);
// 		}
// 		break;
	}

	connect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));

	if (m_pCurPara->m_nTestMode >= ui->m_cbbType->count())
	{
		m_pCurPara->m_nTestMode = 0;
	}

	ui->m_cbbType->setCurrentIndex(m_pCurPara->m_nTestMode);
	on_m_cbbType_currentIndexChanged(m_pCurPara->m_nTestMode);

	ui->m_editInit->SetEditFinished();
	ui->m_editFinish->SetEditFinished();

}

void QSttMacroParaEditViewLineVolGradient::UpdateG1G2()
{
	long nGradientChannel = GetSttLineVolGradientChannelType(m_pCurPara->m_nChannel);

	if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_CURR)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Current = m_pCurPara->m_fEDI;
			//  			ui->m_editVarA1->setText(QString::number(m_pCurPara->m_fG1Current,'f',3));
		}
	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_VOLT)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Volt = m_pCurPara->m_fEDU;
			//  			ui->m_editVarV1->setText(QString::number(m_pCurPara->m_fG1Volt,'f',3));
		}
	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_CURR)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG2Current = m_pCurPara->m_fEDI;
			//  			ui->m_editVarA2->setText(QString::number(m_pCurPara->m_fG2Current,'f',3));
		}
	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_VOLT)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG2Volt = m_pCurPara->m_fEDU;
			//  			ui->m_editVarV2->setText(QString::number(m_pCurPara->m_fG2Volt,'f',3));
		}
	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_ALL_CURR)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Current = m_pCurPara->m_fEDI;
			//  			ui->m_editVarA1->setText(QString::number(m_pCurPara->m_fG1Current,'f',3));
			m_pCurPara->m_fG2Current = m_pCurPara->m_fEDI;
			//  			ui->m_editVarA2->setText(QString::number(m_pCurPara->m_fG2Current,'f',3));
		}
	}
	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_ALL_VOLT)
	{
		if (m_pCurPara->m_nType == amplitude_type)
		{
			m_pCurPara->m_fG1Volt = m_pCurPara->m_fEDU;
			//  			ui->m_editVarV1->setText(QString::number(m_pCurPara->m_fG1Volt,'f',3));
			m_pCurPara->m_fG2Volt = m_pCurPara->m_fEDU;
			//  			ui->m_editVarV2->setText(QString::number(m_pCurPara->m_fG2Volt,'f',3));
		}
	}
}

void QSttMacroParaEditViewLineVolGradient::InitMannualparas()
{
	m_pCurPara->m_fPrepareTime = ui->m_editTimeBeforeChange->text().toFloat();	//准备时间
	m_pCurPara->m_fPreFaultTime = ui->m_editTimeBeforeFail->text().toFloat();	//故障前时间
}

void QSttMacroParaEditViewLineVolGradient::on_m_editTimeBeforeChange_clicked()//鼠标响应部分
{
	slot_edit_changed2(ui->m_editTimeBeforeChange, 0);
}

void QSttMacroParaEditViewLineVolGradient::on_m_editTimeBeforeFail_clicked()
{
	slot_edit_changed2(ui->m_editTimeBeforeFail, 0);
}

void QSttMacroParaEditViewLineVolGradient::on_m_editCurBeforeChange_clicked()
{
	//slot_edit_changed2(ui->m_editCurBeforeChange, 0);
}

void QSttMacroParaEditViewLineVolGradient::on_m_editfDiffUaIaAngle_clicked()
{
	//slot_edit_changed2(ui->m_editfDiffUaIaAngle, 0);
}
void QSttMacroParaEditViewLineVolGradient::on_m_editTimeBeforeChangeChanged()//Zhouyy 2023/01/06
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

void QSttMacroParaEditViewLineVolGradient::on_m_editTimeBeforeFailChanged()
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
		ui->m_editTimeBeforeFail->setText("0");
		ui->m_editTimeBeforeFail->setEnabled(false);
		ui->m_cbBefore->setChecked(false);
	}
	ui->m_editTimeBeforeFail->setCursorPosition(0);

}

void QSttMacroParaEditViewLineVolGradient::slot_edit_changed2(QSttLineEdit* pEditLine, long nType)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutA_StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutB_StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutC_StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutD_StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutE_StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutF_StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutG_StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutH_StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutI_StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_InPutJ_StateChanged(int)
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
void QSttMacroParaEditViewLineVolGradient::slot_radio_AndStateChanged(bool)
{
	if (ui->m_rbAnd->isChecked())
	{
		m_pCurPara->m_nBinLogic = 1;
	}	
}

void QSttMacroParaEditViewLineVolGradient::slot_radio_OrStateChanged(bool)
{
	if (ui->m_rbOr->isChecked())
	{
		m_pCurPara->m_nBinLogic = 0;
	}
}

void QSttMacroParaEditViewLineVolGradient::slot_chb_OutPut1StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_OutPut2StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_OutPut3StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_OutPut4StateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_OutPut1_EStateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_OutPut2_EStateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_OutPut3_EStateChanged(int)
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

void QSttMacroParaEditViewLineVolGradient::slot_chb_OutPut4_EStateChanged(int)
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

LineVolt_type QSttMacroParaEditViewLineVolGradient::getLineVoltParaTypeByInt(int iVar)
{
	LineVolt_type type = LineVolt_vab1_type;
	switch(iVar)
	{
	case 0:
		type = LineVolt_vab1_type;
		break;
	case 1:
		type = LineVolt_v1_0_type;
		break;
	case 2:
		type = LineVolt_vab2_type;
		break;
	case 3:
		type = LineVolt_v2_0_type;
		break;
	case 4:
		type = LineVolt_ia1_type;
		break;
	case 5:
		type = LineVolt_ib1_type;
		break;
	case 6:
		type = LineVolt_ic1_type;
		break;
	case 7:
		type = LineVolt_ia2_type;
		break;
	case 8:
		type = LineVolt_ib2_type;
		break;
	case 9:
		type = LineVolt_ic2_type;
		break;
	}
	return type;
}
