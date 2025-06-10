#include "SttMacroParaEditViewGradient.h"
#include "ui_SttMacroParaEditViewGradient.h"
// #include "../../../Native/TestCtrlCntrLinux/GeneratedFiles/ui_SttMacroParaEditViewGradient.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "GradientSettingDlg.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_6U6I.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../SttGlobalDef.h"
#include <QMessageBox>
#include "../Controls/SttTabWidget.h"
#include"../Module/XLangResource_Native.h"
#include "GradientEstimateDlg.h"
#include "GradientSettingValueDlg.h"
#include "../../Module/XLanguage/XLanguageResource.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewGradient* g_GradientMain = NULL;

QSttMacroParaEditViewGradient::QSttMacroParaEditViewGradient(QWidget *parent) :
	ui(new Ui::QSttMacroParaEditViewGradient)
{
	ui->setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint);
	InitLanuage();

	g_GradientMain = this;
	m_bTmtParaChanged = false;
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;
	m_pGroupWidget = NULL;
//	m_pUnGradientSettingWidget =NULL;
	//m_strParaFileTitle = "递变试验模板文件";
    m_strParaFileTitle = g_sLangTxt_State_IncreExperfile; //递变试验模板文件 lcq 3.14
	m_strParaFilePostfix = "project(*.grtxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("Gradient.grtxml");

	//CreateTestResource();

	SetData(CreateTestParas(GetMacroID()));

	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	g_theTestCntrFrame->InitTestResource();

	if (g_oSystemParas.m_nHasDigital)//zhouhj 在打开测试模板前先初始化当前GOOSE发布数据
	{
		InitGoosePubDataGroups();
		InitFT3PubDataGroups();
	}

	OpenTestTestMngrFile(m_strDefaultParaFile);
	
	m_pCurPara = &m_pCurTest->m_oGradientParasEx;
   
 	SetDatas(0);
    m_pCurPara->m_nSttTestMode = 0;

	InitUI();
	InitParas();
	InitMannualparas();
	InitConnections();
	InitStyle();

	g_theTestCntrFrame->UpdateButtonStateByID(STT_CMD_TYPE_ATS_ManuTriger,false,false);

	ui->m_btnSettingValue->hide();
}

QSttMacroParaEditViewGradient::~QSttMacroParaEditViewGradient()
{
	if(m_pCurTest != NULL)
	{
		delete m_pCurTest;
		m_pCurTest = NULL;
	}

	delete ui;
}

/*
void QSttMacroParaEditViewGradient::UpdateResult(float fTripValue, float fReturnValue, float fReturnCoef)
{
	if (fTripValue>0)
	{
		ui->m_editAction->setText(QString::number(fTripValue,'f',3));
	}
	else
	{
		ui->m_editAction->setText("");
	}

	if (fReturnValue>0)
	{
		ui->m_editReturn->setText(QString::number(fReturnValue,'f',3));
	}
	else
	{
		ui->m_editReturn->setText("");
	}

	if (fReturnCoef>0)
	{
		ui->m_editCoeff->setText(QString::number(fReturnCoef,'f',3));
	}
	else
	{
		ui->m_editCoeff->setText("");
	}
}
*/

void QSttMacroParaEditViewGradient::ShowReport(CDvmValues *pValues)
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
// 		fReturnValue = CString_To_double(pReturnData->m_strValue);
// 		pReturnData->m_strValue = QString::number(fReturnValue,'f',3);
	}

	if(pCoefData != NULL)
	{
		fReturnCoef = GlobalSetResultValue(pCoefData,3);
// 		fReturnCoef = CString_To_double(pCoefData->m_strValue);
// 		pCoefData->m_strValue = QString::number(fReturnCoef,'f',3);
	}
	//UpdateResult(fTripValue, fReturnValue, fReturnCoef);
}

void QSttMacroParaEditViewGradient::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewGradient::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_pCurPara, &oRead);
	}

	if (m_oGradientChs.GetCount() == 0)
	{
		if (g_oSttTestResourceMngr.m_pTestResouce != NULL)
		{
			g_oSttTestResourceMngr.m_pTestResouce->AddGradientChs_All(m_oGradientChs);
		}
	}

	g_theTestCntrFrame->InitVectorWidget(m_pCurPara->m_uiVOL[0],m_pCurPara->m_uiCUR[0]);
	g_theTestCntrFrame->InitPowerWidget(m_pCurPara->m_uiVOL[0],m_pCurPara->m_uiCUR[0]);
	g_theTestCntrFrame->InitStateMonitor(true, NULL);
	g_theTestCntrFrame->InitStateMonitor(m_pCurPara->m_nChannel, m_pCurPara->m_nType, g_theTestCntrFrame->IsTestStarted(), this);
	g_theTestCntrFrame->ClearInfoWidget();

// 	if (pDataset != NULL)
// 	{
// 		CDvmData *pTestMode = (CDvmData *)pDataset->FindByID(_T("SttTestMode"));
// 
// 		if (pTestMode != NULL)
// 		{
// 			m_pCurPara->m_nTestMode = CString_To_long(pTestMode->m_strValue);
// 		}
// 	}

	InitParas();

	UpdateGoutTab();
	UpdateFT3Tab();

	//切换界面时重新串行化出非递变通道界面
	if(m_pGroupWidget)
	{
		m_pGroupWidget->Update();
	}
}

void QSttMacroParaEditViewGradient::startInit()
{
	ui->m_gpMannual->setEnabled(false);
	ui->m_cbbVar->setDisabled(true);
	ui->m_cbbVarType->setDisabled(true);
	ui->m_cbbType->setDisabled(true);
	ui->m_cbbDirection->setDisabled(true);
//	ui->m_editVarA1->setDisabled(true);
//	ui->m_editVarA2->setDisabled(true);
//	ui->m_editVarV1->setDisabled(true);
//	ui->m_editVarV2->setDisabled(true);
	ui->m_editInit->setDisabled(true);
	ui->m_editFinish->setDisabled(true);
	ui->m_editStep->setDisabled(true);
	ui->m_editTime->setDisabled(true);
	ui->m_cbbType->setDisabled(true);
//  ui->m_btnManual->setDisabled(true);
//	ui->m_editfDiffIAngle->setDisabled(true);
	m_pGroupWidget->SetEnabledUI(false);

	if ((m_pGooseParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		m_pGooseParaWidget->SetGooseDisabled(TRUE);
	}

	if ((m_pFT3OutParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		m_pFT3OutParaWidget->SetGooseDisabled(TRUE);
	}

	ui->m_gpBin->setEnabled(false);
	ui->m_gpBoutNormal->setDisabled(true);

	ui->m_gpBoutError->setDisabled(true);

	ui->m_btnSettingValue->setDisabled(true);
	ui->m_btnEstimate->setDisabled(true);
	ui->m_btnMoreOut->setDisabled(true);
	
}

void QSttMacroParaEditViewGradient::stopInit()
{
	ui->m_gpMannual->setEnabled(true);
	ui->m_cbbVar->setDisabled(false);
	ui->m_cbbVarType->setDisabled(false);
	ui->m_cbbType->setDisabled(false);
	ui->m_cbbDirection->setDisabled(false);
//	ui->m_editVarA1->setDisabled(false);
//	ui->m_editVarA2->setDisabled(false);
//	ui->m_editVarV1->setDisabled(false);
//	ui->m_editVarV2->setDisabled(false);
	ui->m_editInit->setDisabled(false);
	ui->m_editFinish->setDisabled(false);
	ui->m_editStep->setDisabled(false);
	ui->m_editTime->setDisabled(false);
	ui->m_cbbType->setDisabled(false);
//	ui->m_btnManual->setDisabled(false);
//	ui->m_editfDiffIAngle->setDisabled(false);
	m_pGroupWidget->SetEnabledUI(true);

	ui->m_gpBin->setEnabled(true);
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
	EnableRadientType();
}

void QSttMacroParaEditViewGradient::InitEnableButtons()
{
  	long nGradientChannel = GetSttGradientChannelType(m_pCurPara->m_nChannel);
  	BOOL bCurentChannel = FALSE,bVoltageChannel = FALSE;
  
  	if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_CURR)
  	{
  		bCurentChannel = TRUE;
//   		ui->m_editVarA1->setDisabled(true);
//   		ui->m_editVarA2->setDisabled(false);
   
//   		ui->m_editVarV1->setDisabled(false);
//   		ui->m_editVarV2->setDisabled(false);
  
  	}
  	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_VOLT)
 	{
  		bVoltageChannel = TRUE;
//   		ui->m_editVarV1->setDisabled(true);
//   		ui->m_editVarV2->setDisabled(false);
   
//   		ui->m_editVarA1->setDisabled(false);
//   		ui->m_editVarA2->setDisabled(false);
  
 	}
  	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_CURR)
  	{
  		bCurentChannel = TRUE;
//   		ui->m_editVarA1->setDisabled(false);
//   		ui->m_editVarA2->setDisabled(true);
   
//   		ui->m_editVarV1->setDisabled(false);
//   		ui->m_editVarV2->setDisabled(false);
  
  	}
  	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_VOLT)
  	{
  		bVoltageChannel = TRUE;
//   		ui->m_editVarV1->setDisabled(false);
//   		ui->m_editVarV2->setDisabled(true);
   
//   		ui->m_editVarA1->setDisabled(false);
//   		ui->m_editVarA2->setDisabled(false);
 
 	}
  	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_ALL_CURR)
 	{
  		bCurentChannel = TRUE;
//   		ui->m_editVarV1->setDisabled(false);
//   		ui->m_editVarV2->setDisabled(false);
   
//   		ui->m_editVarA1->setDisabled(true);
//   		ui->m_editVarA2->setDisabled(true);
  
  	}
  	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_ALL_VOLT)
 	{
  		bVoltageChannel = TRUE;
//   		ui->m_editVarV1->setDisabled(true);
//   		ui->m_editVarV2->setDisabled(true);
  
//   		ui->m_editVarA1->setDisabled(false);
//   		ui->m_editVarA2->setDisabled(false);
 
  	}
  	else if (m_pCurPara->m_nChannel == freAll_type)
  	{
//   		ui->m_editVarV1->setDisabled(false);
//   		ui->m_editVarV2->setDisabled(false);
   
//   		ui->m_editVarA1->setDisabled(false);
//   		ui->m_editVarA2->setDisabled(false);
  	}


 	switch(m_pCurPara->m_nType)
 	{
 	case amplitude_type:
		{
// 			ui->m_editfDiffIAngle->setDisabled(false);
 		}
 		break;
 	case phasor_type:
 		{
//  			ui->m_editVarV1->setDisabled(false);
//  			ui->m_editVarV2->setDisabled(false);
//  			ui->m_editVarA2->setDisabled(false);
//  			ui->m_editVarA1->setDisabled(false);
//  			ui->m_editfDiffIAngle->setDisabled(true);
 		}
 		break;
 	case fre_type:
 		{
//  			ui->m_editVarV1->setDisabled(false);
//  			ui->m_editVarV2->setDisabled(false);
//  			ui->m_editVarA2->setDisabled(false);
//  			ui->m_editVarA1->setDisabled(false);
//  			ui->m_editfDiffIAngle->setDisabled(false);
		}
 		break;
 	}
}


void QSttMacroParaEditViewGradient::OnViewTestLink(BOOL b)
{

}
void QSttMacroParaEditViewGradient::OnViewTestStart()
{
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	startInit();
	//UpdateResult(0,0,0);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->InitStateMonitor(m_pCurPara->m_nChannel, m_pCurPara->m_nType, g_theTestCntrFrame->IsTestStarted());
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
	g_theTestCntrFrame->EnableManualTriggerButton(false);
}
void QSttMacroParaEditViewGradient::OnViewTestStop()
{
	stopInit();
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

CString QSttMacroParaEditViewGradient::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += FILE_GRADIENT;
	strFile += _T(".");
	strFile += POSTFIX_GRADIENT;

	return strFile;
}

bool QSttMacroParaEditViewGradient::IsValidTestParasFile( const CString& strParasFile,bool bOpen /*= true*/ )
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

//判断使用的keyboard类型
//bIsNor 是否是普通无快捷案件键盘
void QSttMacroParaEditViewGradient::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
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

// 	pEditLine->setText(str);
// 	pEditLine->SetEditFinished();
}

void QSttMacroParaEditViewGradient::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateGradientChs();
	InitParas();//zhouhj 20220419 重新初始化递变参数
//  	if (g_oSttSystemConfig.GetSelSysPata())
	{
		if (m_pGroupWidget)
	       {
		m_pGroupWidget->InitData(m_pCurPara);
			//m_pGroupWidget->Update();//20240606 suyang InitData函数中已经更新，不需要再次调用
		}
	}

	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();

	//g_theTestCntrFrame->InitStateMonitor(true, NULL);
	//g_theTestCntrFrame->InitStateMonitor(m_pCurPara->m_nChannel, m_pCurPara->m_nType, g_theTestCntrFrame->IsTestStarted(), this);
	updateLabName();
}

void QSttMacroParaEditViewGradient::UpdateGoutTab(BOOL bUpdateList)
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

void QSttMacroParaEditViewGradient::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
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
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		RemoveGooseParaWidget();
	}
}


void QSttMacroParaEditViewGradient::UpdateFT3Tab(BOOL bUpdateList)
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

void QSttMacroParaEditViewGradient::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
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
void QSttMacroParaEditViewGradient::UpdateBinBoutExTab()
{
	/*
	if ((m_pExSwitchInputSetWidget == NULL)&&(g_oLocalSysPara.m_nCHBinInExNum>0))
	{
		m_pExSwitchInputSetWidget = new ExSwitchSet(ExInput);
		GetCommonTab_UI()->addTab(m_pExSwitchInputSetWidget,tr("开入设置(扩展)"));
		m_pExSwitchInputSetWidget->setData(((tmt_GradientTestEx*)m_TestTable->GetCurrentItem())->m_oGradientParasEx.m_binInEx,NULL);
		connect(m_pExSwitchInputSetWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);
	}
	else if ((m_pExSwitchInputSetWidget != NULL)&&(g_oLocalSysPara.m_nCHBinInExNum == 0))
	{
		disconnect(m_pExSwitchInputSetWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		GetCommonTab_UI()->removeTab(GetCommonTab_UI()->indexOf(m_pExSwitchInputSetWidget));
		delete m_pExSwitchInputSetWidget;
		m_pExSwitchInputSetWidget = NULL;
	}
	else if ((m_pExSwitchInputSetWidget != NULL)&&(g_oLocalSysPara.m_nCHBinInExNum>0))
	{
		disconnect(m_pExSwitchInputSetWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pExSwitchInputSetWidget->setData(((tmt_GradientTestEx*)m_TestTable->GetCurrentItem())->m_oGradientParasEx.m_binInEx,NULL);
		connect(m_pExSwitchInputSetWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);

		GetCommonTab_UI()->setTabEnabled(GetCommonTab_UI()->indexOf(m_pExSwitchInputSetWidget),true);
	}

	if (m_pExSwitchOutputSetWidget == NULL && m_pExSwitchOutputSetWidgetFault == NULL && g_oLocalSysPara.m_nCHBinOutExNum>0)
	{
		m_pExSwitchOutputSetWidget = new ExSwitchSet(ExOutPut);
		GetCommonTab_UI()->addTab(m_pExSwitchOutputSetWidget,tr("常态开出设置(扩展)"));
		m_pExSwitchOutputSetWidget->setData(NULL,((tmt_GradientTestEx*)m_TestTable->GetCurrentItem())->m_oGradientParasEx.m_binOutEx[0]);
		connect(m_pExSwitchOutputSetWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);

		m_pExSwitchOutputSetWidgetFault = new ExSwitchSet(ExOutPut);
		GetCommonTab_UI()->addTab(m_pExSwitchOutputSetWidgetFault,tr("故障态开出设置(扩展)"));
		m_pExSwitchOutputSetWidgetFault->setData(NULL,((tmt_GradientTestEx*)m_TestTable->GetCurrentItem())->m_oGradientParasEx.m_binOutEx[1]);
		connect(m_pExSwitchOutputSetWidgetFault, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);
	}
	else if (m_pExSwitchOutputSetWidget != NULL && m_pExSwitchOutputSetWidgetFault != NULL && g_oLocalSysPara.m_nCHBinOutExNum == 0)
	{
		disconnect(m_pExSwitchOutputSetWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		GetCommonTab_UI()->removeTab(GetCommonTab_UI()->indexOf(m_pExSwitchOutputSetWidget));
		delete m_pExSwitchOutputSetWidget;
		m_pExSwitchOutputSetWidget = NULL;

		disconnect(m_pExSwitchOutputSetWidgetFault, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		GetCommonTab_UI()->removeTab(GetCommonTab_UI()->indexOf(m_pExSwitchOutputSetWidgetFault));
		delete m_pExSwitchOutputSetWidgetFault;
		m_pExSwitchOutputSetWidgetFault = NULL;
	}
	else if ((m_pExSwitchOutputSetWidget != NULL)&&(g_oLocalSysPara.m_nCHBinOutExNum>0))
	{
		disconnect(m_pExSwitchOutputSetWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pExSwitchOutputSetWidget->setData(NULL,((tmt_GradientTestEx*)m_TestTable->GetCurrentItem())->m_oGradientParasEx.m_binOutEx[0]);
		connect(m_pExSwitchOutputSetWidget, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);

		disconnect(m_pExSwitchOutputSetWidgetFault, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()));
		m_pExSwitchOutputSetWidgetFault->setData(NULL,((tmt_GradientTestEx*)m_TestTable->GetCurrentItem())->m_oGradientParasEx.m_binOutEx[1]);
		connect(m_pExSwitchOutputSetWidgetFault, SIGNAL(sig_ExSwitchChanged()), this, SLOT(slot_SwitchStateChanged()),Qt::UniqueConnection);

		GetCommonTab_UI()->setTabEnabled(GetCommonTab_UI()->indexOf(m_pExSwitchOutputSetWidget),true);
	}
	*/
}

void QSttMacroParaEditViewGradient::AddUnGradientSettingWidget()
{
	if (m_pGroupWidget)
	{
		return;
	}

	m_pGroupWidget=new QGradientGroupWidget(this);	
	m_pGroupWidget->Init(m_pCurPara);
	int nInsertPos = 1;
	CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Gradient_UnChangingSet");
	ui->m_tabWidget->insertTab(nInsertPos,m_pGroupWidget,strTitle);

	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
	m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);	

	m_pCurPara->m_nSttTestMode=3;
}

void QSttMacroParaEditViewGradient::RemoveUnGradientSettingWidget()
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

void QSttMacroParaEditViewGradient::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,FALSE);
	int nInsertPos = 2;

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
	ui->m_tabWidget->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewGradient::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,TRUE);
	int nInsertPos = 3;

	//CString strTitle= _T("FT3发布");
	CString strTitle= g_sLangTxt_Gradient_ReleasedFTT; //lcq
	
	ui->m_tabWidget->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewGradient::RemoveFT3OutParaWidget()
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

void QSttMacroParaEditViewGradient::RemoveGooseParaWidget()
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

bool QSttMacroParaEditViewGradient::ExistGooseParaWidget()
{
	int nIndex = ui->m_tabWidget->indexOf(m_pGooseParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewGradient::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		ui->m_tabWidget->setTabEnabled(ui->m_tabWidget->indexOf(m_pGooseParaWidget),b);
	}
}

bool QSttMacroParaEditViewGradient::ExistFT3OutParaWidget()
{
	int nIndex = ui->m_tabWidget->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

void QSttMacroParaEditViewGradient::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		ui->m_tabWidget->setTabEnabled(ui->m_tabWidget->indexOf(m_pFT3OutParaWidget),b);
	}
}

// void QSttMacroParaEditViewGradient::EnableSubParaWidget(bool bEnable)
// {
// if (bEnable)
// 	{
// 		if (m_pGooseParaWidget!= NULL)
// 		{
// 			m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
// 			m_pGooseParaWidget->SetGooseDisabled(FALSE);
// 		}
// 		/*
// 		if(m_pExSwitchInputSetWidget != NULL)
// 		{
// 			m_pExSwitchInputSetWidget->m_pTable->setDisabled(false);
// 			m_pExSwitchInputSetWidget->ck_SelectAll->setDisabled(false);
// 		}
// 
// 		if(m_pExSwitchOutputSetWidget != NULL)
// 		{
// 			m_pExSwitchOutputSetWidget->m_pTable->setDisabled(false);
// 			m_pExSwitchOutputSetWidget->ck_SelectAll->setDisabled(false);
// 		}
// 
// 		if(m_pExSwitchOutputSetWidgetFault != NULL)
// 		{
// 			m_pExSwitchOutputSetWidgetFault->m_pTable->setDisabled(false);
// 			m_pExSwitchOutputSetWidgetFault->ck_SelectAll->setDisabled(false);
// 		}
// 
// 		if (m_pRsltWidget != NULL)
// 		{
// 			m_pRsltWidget->stopInit();
// 		}
// 		*/
// 	}
// 	else
// 	{
// 		if (m_pGooseParaWidget != NULL)
// 		{
// 			m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_NotEditable);
// 			m_pGooseParaWidget->SetGooseDisabled(TRUE);
// 		}
// 		/*
// 		if(m_pExSwitchInputSetWidget != NULL)
// 		{
// 			m_pExSwitchInputSetWidget->m_pTable->setDisabled(true);
// 			m_pExSwitchInputSetWidget->ck_SelectAll->setDisabled(true);
// 		}
// 
// 		if(m_pExSwitchOutputSetWidget != NULL)
// 		{
// 			m_pExSwitchOutputSetWidget->m_pTable->setDisabled(true);
// 			m_pExSwitchOutputSetWidget->ck_SelectAll->setDisabled(true);
// 		}
// 
// 		if(m_pExSwitchOutputSetWidgetFault != NULL)
// 		{
// 			m_pExSwitchOutputSetWidgetFault->m_pTable->setDisabled(true);
// 			m_pExSwitchOutputSetWidgetFault->ck_SelectAll->setDisabled(true);
// 		}
// 
// 		if (m_pRsltWidget != NULL)
// 		{
// 			m_pRsltWidget->startInit();
// 		}
// 		*/
// 	}
// }

CString QSttMacroParaEditViewGradient::GetCurChannal(PTMT_PARAS_HEAD pParas)
{
	CDataTypeValue* pDataType =  (CDataTypeValue*)m_oGradientChs.FindByIndex(m_pCurTest->m_oGradientParasEx.m_nChannel);
	if(pDataType)
	{
		return pDataType->m_strID;
	}
	return "";
}

void QSttMacroParaEditViewGradient::InitLanuage()
{
	CString strText;
	xlang_GetLangStrByFile(strText, "Gradient_TimeBeforeChange");
	ui->m_labTimeBeforeChange->setText(strText + "(s):");
	xlang_GetLangStrByFile(strText, "Gradient_TimeBeforeFail");
	ui->m_labTimeBeforeFail->setText(strText/*.right(4)*/ + "(s):");
	ui->m_cbBefore->setText(strText.left(2));
// 	xlang_GetLangStrByFile(strText, "Gradient_CurBeforeChange");
// 	ui->m_labCurBeforeChange->setText(strText + "(A):");//Zhouyy 2023/01/10 新增语言识别
	xlang_GetLangStrByFile(strText, "sVariable");
	ui->m_labVar->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Gradient_VarType");
	ui->m_labVarType->setText(strText + ":");
	xlang_GetLangStrByFile(strText, "Native_Current");
	//ui->m_labVarA1->setText(strText + "(G1)(A):");
	xlang_GetLangStrByFile(strText, "Native_Current");
	//ui->m_labVarA2->setText(strText + "(G2)(A):");
	xlang_GetLangStrByFile(strText, "Native_Voltage");
	//ui->m_labVarV1->setText(strText + "(G1)(V):");
	xlang_GetLangStrByFile(strText, "Native_Voltage");
	//ui->m_labVarV2->setText(strText + "(G2)(V):");
	xlang_GetLangStrByFile(strText, "Gradient_Phase");
	//ui->m_labfDiffIAngle->setText(strText + "(G1,G2)(°):");
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
	//xlang_SetLangStrToWidget(ui->m_btnManual, "Native_CommonPara", XLang_Ctrls_QPushButton);

	xlang_GetLangStrByFile(m_strCurrent, "Native_Current");
	xlang_GetLangStrByFile(m_strVoltage, "Native_Voltage");
	xlang_GetLangStrByFile(m_strFreq, "Native_Freq");

	//xlang_SetLangStrToWidget(ui->m_labAction, "Native_Action", XLang_Ctrls_QLabel);
	//xlang_SetLangStrToWidget(ui->m_labReturn, "Native_ReturnVal", XLang_Ctrls_QLabel);

	//xlang_GetLangStrByFile(strText, "Native_ReturnCoeff");
	//ui->m_labCoeff->setText(strText + ":");

	xlang_GetLangStrByFile(strText, "Gradient_VarSet");
	ui->m_gpVarSet->setTitle(strText);
	xlang_GetLangStrByFile(strText, "Gradient_ChangingSet"); //递变参数设置
	ui->m_gpChangeSet->setTitle(strText);
	xlang_GetLangStrByFile(strText, "sGeneralParameter");//通用参数 lcq
	ui->m_gpMannual->setTitle(strText);


	xlang_GetLangStrByFile(strText, "Gradient_UnChangingSet");
//	ui->m_gpUnChangeSet->setTitle(strText);
	//xlang_GetLangStrByFile(strText, "Gradient_OtherSet");
	//ui->m_gpOtherSet->setTitle(strText);    其他参数被合并到变量设置，不再需要
	//xlang_GetLangStrByFile(strText, "Gradient_TestResult");
	//ui->m_gpTestResult->setTitle(strText);


	//xlang_GetLangStrByFile(strText, "Gradient_ParaSet");
	//strText = _T("递变通道设置");
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
// 	ui->m_cbBOut5->setText(/*strText +*/ "5");
// 	ui->m_cbBOut6->setText(/*strText +*/ "6");
// 	ui->m_cbBOut7->setText(/*strText +*/ "7");
// 	ui->m_cbBOut8->setText(/*strText +*/ "8");
// 	ui->m_cbBOut9->setText(/*strText +*/ "9");
// 	ui->m_cbBOut10->setText(/*strText +*/ "10");

	ui->m_cbBOut1_E->setText(/*strText +*/ "1");
	ui->m_cbBOut2_E->setText(/*strText +*/ "2");
	ui->m_cbBOut3_E->setText(/*strText +*/ "3");
	ui->m_cbBOut4_E->setText(/*strText +*/ "4");
// 	ui->m_cbBOut5_E->setText(/*strText +*/ "5");
// 	ui->m_cbBOut6_E->setText(/*strText +*/ "6");
// 	ui->m_cbBOut7_E->setText(/*strText +*/ "7");
// 	ui->m_cbBOut8_E->setText(/*strText +*/ "8");
// 	ui->m_cbBOut9_E->setText(/*strText +*/ "9");
// 	ui->m_cbBOut10_E->setText(/*strText +*/ "10");

	xlang_GetLangStrByFile(strText,"Native_Bout");
	//ui->m_gpBoutNormal->setTitle(strText+"正常态");	
	//ui->m_gpBoutError->setTitle(strText+"故障态");

	CString str;
	xlang_GetLangStrByFile(str,"Gradient_Normal");
	ui->m_gpBoutNormal->setTitle(strText+str);
	xlang_GetLangStrByFile(str,"Gradient_Failure");
	ui->m_gpBoutError->setTitle(strText+str);

	xlang_SetLangStrToWidget(ui->m_btnMoreOut, "Gradient_BoutSets", XLang_Ctrls_QPushButton);//更多开入量设置 lcq
	xlang_SetLangStrToWidget(ui->m_btnEstimate, "State_Estimate", XLang_Ctrls_QPushButton);//整定及结果评估 lcq
	
}

// CSttTestResourceBase* QSttMacroParaEditViewGradient::CreateTestResource()
// {
// // 	g_theTestCntrFrame->m_pSttTestResource = g_oSttTestResourceMngr.m_pTestResouce;
// // 	m_pOriginalSttTestResource = g_oSttTestResourceMngr.m_pTestResouce;
// 	return g_theTestCntrFrame->GetSttTestResource();
// }

PTMT_PARAS_HEAD QSttMacroParaEditViewGradient::CreateTestParas(const char * pszMacroID)
{
	PTMT_PARAS_HEAD pNewTest = new tmt_GradientTestEx;	
	strcpy(pNewTest->m_oRsltExprMngr.m_pszExprGroupID, STT_RSLTEXPR_MACROID_COMMON);  

	return pNewTest;
}

PTMT_PARAS_HEAD QSttMacroParaEditViewGradient::CreateTestParas(PTMT_PARAS_HEAD pCurr)
{
	ASSERT(pCurr != NULL);

	tmt_GradientTestEx* pCurrTest = (tmt_GradientTestEx*)pCurr;
	tmt_GradientTestEx* pNewTest = new tmt_GradientTestEx;

	memcpy(pNewTest,pCurrTest,sizeof(tmt_GradientTestEx));

	stt_clone_expr_mngr(pCurr, pNewTest);

	pNewTest->m_nTestState = 0;
	pNewTest->clear_result();

	return (PTMT_PARAS_HEAD)pNewTest;
}

void QSttMacroParaEditViewGradient::SetData(PTMT_PARAS_HEAD pCurr)
{
	ASSERT(m_pCur != NULL);
	m_pCurTest = (tmt_GradientTestEx*)pCurr;

	m_pCurPara = &m_pCurTest->m_oGradientParasEx;
	m_pCurResult = &m_pCurTest->m_oResultParas;
	
	//InitWidgetPara();

	//if (g_GradientMain->m_bViewTestStarted)
	//{
	//	startInit();
	//}
}

void QSttMacroParaEditViewGradient::InitStyle()
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
// 	((QSttCheckBox*)ui->m_cbBOut5)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut6)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut7)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut8)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut9)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut10)->InitStyleSheet();

	((QSttCheckBox*)ui->m_cbBOut1_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut2_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut3_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut4_E)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut5_E)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut6_E)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut7_E)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut8_E)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut9_E)->InitStyleSheet();
// 	((QSttCheckBox*)ui->m_cbBOut10_E)->InitStyleSheet();
}

void QSttMacroParaEditViewGradient::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
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

	tmt_gradient_test_ex *pGradientParas = (tmt_gradient_test_ex*)pParas;

	if(stt_xml_serialize_is_read(pMacroParas) || stt_xml_serialize_is_register(pMacroParas))
	{
		stt_xml_serialize_ex(&pGradientParas->m_oGradientParasEx, pMacroParas);	//文件的读写
	}
	else if (pParas->m_nSelected)
	{
		stt_xml_serialize_ex(&pGradientParas->m_oGradientParasEx, pMacroParas);	//测试参数下发
	}

//	CSttXmlSerializeBase *pChildParas = stt_xml_serialize((tmt_gradient_test_ex*)pParas, pMacroParas/*,nBinExNum,nBoutExNum*/);

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

// 	long nIndex = m_oTmtTestMngr.GetIndex(pParas);
// 
// 	if (stt_xml_serialize_is_read(pMacroParas)&&(nIndex == 0))
// 	{
// 		InitGoosePubDataGroups();	//从TestWin.ixml文件获取初始值，每个状态对应一个CDataGroup,需要克隆Gouts控制块,再打开模板,将模板中的数据值赋值到控制块中
// 	}
// 
// 	CIecCfgGoutDatas *pIecCfgGoutDatas = GetGoutDatas(nIndex);
// 
// 	if ((pIecCfgGoutDatas != NULL)&&bHasGoosePub)
// 	{
// 		SerializeGoosePubs(pChildParas,pIecCfgGoutDatas);
	// 	}
}

void QSttMacroParaEditViewGradient::on_m_btnManual_clicked()//点击调出子窗口
{
 	QGradientSettingDlg dlg(m_pCurPara, this);
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
 		g_theTestCntrFrame->UpdateToolButtons();

		tmt_GradientParasEx* pGradientPara = m_pCurPara;
		ui->m_cbBOut1->setChecked(pGradientPara->m_binOut[0][0].nState);
		ui->m_cbBOut2->setChecked(pGradientPara->m_binOut[0][1].nState);
		ui->m_cbBOut3->setChecked(pGradientPara->m_binOut[0][2].nState);
		ui->m_cbBOut4->setChecked(pGradientPara->m_binOut[0][3].nState);
		ui->m_cbBOut1_E->setChecked(pGradientPara->m_binOut[1][0].nState);
		ui->m_cbBOut2_E->setChecked(pGradientPara->m_binOut[1][1].nState);
		ui->m_cbBOut3_E->setChecked(pGradientPara->m_binOut[1][2].nState);
		ui->m_cbBOut4_E->setChecked(pGradientPara->m_binOut[1][3].nState);
 	}
}

void QSttMacroParaEditViewGradient::on_m_cbbVar_currentIndexChanged(int index)
{
	if(ui->m_cbbVar->IsScrolling())
	{
		return;
	}

	if(m_pCurPara == NULL)
	{
		return;
	}

	SetDefaultFaultValue(m_pCurPara->m_nChannel);

	long nOldChannel = m_pCurPara->m_nChannel;
	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(index);
	ASSERT(pCurDataTypeValue);
	m_pCurPara->m_nChannel = pCurDataTypeValue->GetIndex();

	disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	ui->m_cbbVarType->clear();
	if(m_pCurPara->m_nChannel == iabcAdd_type || m_pCurPara->m_nChannel == ia2b2c2Add_type)
	{
		ui->m_cbbVarType->addItems(m_ChangeTypeList2);
	}
	else
	{
		ui->m_cbbVarType->addItems(m_ChangeTypeList);
		ui->m_cbbVarType->setCurrentIndex(m_pCurPara->m_nType);
	}

	connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));

	if (m_pCurPara->m_nChannel == freAll_type)
	{
		m_pCurPara->m_nType = fre_type;
		disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
		ui->m_cbbVarType->setCurrentIndex(fre_type);
		connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	}
	else if (m_pCurPara->m_nType == fre_type)
	{
		m_pCurPara->m_nType = amplitude_type;
		disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
		ui->m_cbbVarType->setCurrentIndex(amplitude_type);
		connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	}

	if (nOldChannel != m_pCurPara->m_nChannel)
	{
		InitUI_AfterGridentSel();
	}

	g_GradientMain->m_bTmtParaChanged = TRUE;
	if(CHANNAL_TYPE_I(m_pCurPara->m_nChannel))
	{
		m_pCurPara->m_nVarIndexType = 0;
	}
	else if (CHANNAL_TYPE_U(m_pCurPara->m_nChannel))
	{
		m_pCurPara->m_nVarIndexType = 1;
	}
	else if(CHANNAL_TYPE_F(m_pCurPara->m_nChannel))
	{
		m_pCurPara->m_nVarIndexType = 2;
	}

	m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);
}

void QSttMacroParaEditViewGradient::on_m_cbbVarType_currentIndexChanged(int index)
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

	if ((m_pCurPara->m_nType == fre_type)&&(m_pCurPara->m_nChannel != freAll_type))
	{
		disconnect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
		m_pCurPara->m_nChannel = freAll_type;
		InitGradientChannel(freAll_type);
		connect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
	}
	else if ((m_pCurPara->m_nType != fre_type)&&(m_pCurPara->m_nChannel == freAll_type))
	{
		disconnect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
		m_pCurPara->m_nChannel = va1_type;
		InitGradientChannel(va1_type);
		connect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
	}

	//emit sig_Para_ChangeTypeIndexChanged(index);
	on_m_editInitChanged();
	on_m_editFinishChanged();
	on_m_editStepChanged();
	on_m_editTimeChanged();

	InitUI_AfterGridentSel();

	EnableRadientType();

	g_GradientMain->m_bTmtParaChanged = TRUE;

	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
	m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);

	if (index == 1)
	{
		//相位需要默认切换至最大灵敏角
		ui->m_cbbType->setCurrentIndex(2);
	}
}

void QSttMacroParaEditViewGradient::on_m_cbbType_currentIndexChanged(int index)
{
	if(ui->m_cbbType->IsScrolling())
	{
		return;
	}

	if (m_pCurPara->m_nTestMode != index)
	{
		m_pCurPara->m_nTestMode = index;
		emit sig_Para_ReturnTypeIndexChanged(index);

		g_GradientMain->m_bTmtParaChanged = TRUE;
	}

	EnableRadientType();
}

void QSttMacroParaEditViewGradient::on_m_cbbDirection_currentIndexChanged(int index)
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


//void QSttMacroParaEditViewGradient::on_m_cbGroup_clicked(int nState)
//{
//	if(nState)
//	{
//		//CString strTemp = "分组设置";
//		//ui->m_tabWidget->insertTab(1, m_pGroupWidget, strTemp);
//      ui->m_tabWidget->insertTab(1, m_pGroupWidget, g_sLangTxt_Gradient_Groupset);//分组设置-LCQ
//		ui->m_tabWidget->setCurrentIndex(1);
//		m_pGroupWidget->show();
//		CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
//		m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);	
//
//		ui->m_gpUnChangeSet->setEnabled(false);
//		ui->m_editCurBeforeChange->setEnabled(false);
//		ui->m_editfDiffUaIaAngle->setEnabled(false);
//
//		m_pCurPara->m_nSttTestMode = 3;
//	}
//	else
//	{
//		ui->m_tabWidget->removeTab(1);
//		m_pGroupWidget->hide();
//
//		ui->m_gpUnChangeSet->setEnabled(true);
//		ui->m_editCurBeforeChange->setEnabled(true);
//		ui->m_editfDiffUaIaAngle->setEnabled(true);
//
//		m_pCurPara->m_nSttTestMode = 0;
//	}
//}


void QSttMacroParaEditViewGradient::on_m_cbBefore_clicked(int nState)
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

//void QSttMacroParaEditViewGradient::on_m_editVarA1_clicked()
//{
//	slot_edit_changed(ui->m_editVarA1, TRUE);
//}
//
//void QSttMacroParaEditViewGradient::on_m_editVarA2_clicked()
//{
//	slot_edit_changed(ui->m_editVarA2, TRUE);
//}
//
//void QSttMacroParaEditViewGradient::on_m_editVarV1_clicked()
//{
// 	slot_edit_changed(ui->m_editVarV1, TRUE);
//}
//
//void QSttMacroParaEditViewGradient::on_m_editVarV2_clicked()
//{
//	slot_edit_changed(ui->m_editVarV2, TRUE);
//}
//
//void QSttMacroParaEditViewGradient::on_m_editfDiffIAngle_clicked()
//{
// 	slot_edit_changed(ui->m_editfDiffIAngle, TRUE);
//}
void QSttMacroParaEditViewGradient::on_m_editFreq_clicked()
{

}

void QSttMacroParaEditViewGradient::on_m_editInit_clicked()
{
	slot_edit_changed(ui->m_editInit, TRUE);
}

void QSttMacroParaEditViewGradient::on_m_editFinish_clicked()
{
	slot_edit_changed(ui->m_editFinish, TRUE);
}

void QSttMacroParaEditViewGradient::on_m_editStep_clicked()
{
	slot_edit_changed(ui->m_editStep, TRUE);
}

void QSttMacroParaEditViewGradient::on_m_editTime_clicked()
{
	slot_edit_changed(ui->m_editTime, TRUE);
}

// void QSttMacroParaEditViewGradient::on_m_editVarA1Changed()
// {
// 	QString str = ui->m_editVarA1->text();
// 
// 	if (str.right(1).contains("."))
// 	{
// 		str.append("000");
// 	}
// 
// 	float fv= str.toFloat();
// 
// 	if (fabs(fv - m_pCurPara->m_fG1Current)> EPSINON)
// 	{
// 		if (fabs(fv) > g_oLocalSysPara.m_fAC_CurMax)
// 		{
// 			if (fv > 0)
// 			{
// 				fv = g_oLocalSysPara.m_fAC_CurMax;
// 			}
// 			else
// 			{
// 				fv = -g_oLocalSysPara.m_fAC_CurMax;
// 			}
// 
// 		}
// 		ui->m_editVarA1->setText(QString::number(fv,'f',3));
// 		if(m_pCurPara->m_fG1Current != fv)
// 		{
// 			m_pCurPara->m_fG1Current = fv;
// 			emit sig_Para_G1CurrentChanged(fv);
// 
// 			m_bTmtParaChanged = TRUE;
// 		}
// 
// 		QString qName = GetCurChannal(m_pCurTest);
// 		if (m_pCurPara->m_nType == amplitude_type && qName.contains(tr("I")) && qName.contains(tr("2")))
// 		{
// 			float fdown=0;
// 			float fup=0;
// 			getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDI,m_pCurPara->m_fG1Current,m_pCurPara->m_fG2Current,
// 				m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
// 			emit sig_YRangeChanged(amplitude_type, m_strCurrent + "(A)",fdown/FRADIO,fup*FRADIO);
// 		}
// 	}
// 	else
// 	{
// 		ui->m_editVarA1->setText(QString::number(fv,'f',3));
// 	}
// }

//  void QSttMacroParaEditViewGradient::on_m_editVarA2Changed()
//  {
//  	QString str = ui->m_editVarA2->text();
// 
//  	if (str.right(1).contains("."))
//  	{
//  		str.append("000");
//  	}
//  
//  	float fv= str.toFloat();
//  	if (fabs(fv - m_pCurPara->m_fG2Current)> EPSINON)
//  	{
//  		if (fabs(fv) > g_oLocalSysPara.m_fAC_CurMax)
//  		{
//  			if (fv > 0)
//  			{
//  				fv = g_oLocalSysPara.m_fAC_CurMax;
//  			}
//  			else
//  			{
//  				fv = -g_oLocalSysPara.m_fAC_CurMax;
//  			}
//  		}
//   		ui->m_editVarA2->setText(QString::number(fv,'f',3));
//  		if (m_pCurPara->m_fG2Current != fv)
//  		{
//  			m_pCurPara->m_fG2Current = fv;
//  			emit sig_Para_G2CurrentChanged(fv);
//  
//  			m_bTmtParaChanged = TRUE;
//  		}
//  
//  		QString qName = GetCurChannal(m_pCurTest);
//  		if (m_pCurPara->m_nType == amplitude_type && qName.contains(tr("I")) && qName.contains(tr("2"))==false)
//  		{
//  			float fdown=0;
//  			float fup=0;
//  			getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDI,m_pCurPara->m_fG1Current,m_pCurPara->m_fG2Current,
//  				m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
//  			emit sig_YRangeChanged(amplitude_type, m_strCurrent + "(A)",fdown/FRADIO,fup*FRADIO);
//  		}
//  	}
//  	else
//  	{
//   		ui->m_editVarA2->setText(QString::number(fv,'f',3));
//  	}
//  }
//  
//  void QSttMacroParaEditViewGradient::on_m_editVarV1Changed()
//  {
//   	QString str = ui->m_editVarV1->text();
//  
//  	if (str.right(1).contains("."))
//  	{
//  		str.append("000");
//  	}
//  
//  	float fv= str.toFloat();
//  	if (fabs(fv - m_pCurPara->m_fG1Volt)> EPSINON)
//  	{
//  		if (fabs(fv) > g_oLocalSysPara.m_fAC_VolMax)
//  		{
//  			if (fv > 0)
//  			{
//  				fv = g_oLocalSysPara.m_fAC_VolMax;
//  			}
//  			else
//  			{
//  				fv = -g_oLocalSysPara.m_fAC_VolMax;
//  			}
//  
//  		}
//  		ui->m_editVarV1->setText(QString::number(fv,'f',3));
// 
//  		if (m_pCurPara->m_fG1Volt != fv)
//  		{
//  			m_pCurPara->m_fG1Volt = fv;
//  			emit sig_Para_G1VoltChanged(fv);
//  
//  			m_bTmtParaChanged = TRUE;
//  		}
//  
//  		QString qName = GetCurChannal(m_pCurTest);
//  		if (m_pCurPara->m_nType == amplitude_type && qName.contains(tr("U")) && qName.contains(tr("2")))
//  		{
//  			float fdown=0;
//  			float fup=0;
//  			getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDU,m_pCurPara->m_fG1Volt,m_pCurPara->m_fG2Volt,
//  				m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
//  			emit sig_YRangeChanged(amplitude_type, m_strVoltage + "(V)",fdown/FRADIO,fup*FRADIO);
//  		}
//  	}
//  	else
//  	{
//  		ui->m_editVarV1->setText(QString::number(fv,'f',3));
//  	}
//  }
//  
//  void QSttMacroParaEditViewGradient::on_m_editVarV2Changed()
//  {
//  	QString str = ui->m_editVarV2->text();
// 
//  	if (str.right(1).contains("."))
//  	{
//  		str.append("000");
//  	}
//  
//  	float fv= str.toFloat();
//  	if (fabs(fv - m_pCurPara->m_fG2Volt)> EPSINON)
//  	{
//  		if (fabs(fv) > g_oLocalSysPara.m_fAC_VolMax)
//  		{
//  			if (fv > 0)
//  			{
//  				fv = g_oLocalSysPara.m_fAC_VolMax;
//  			}
//  			else
//  			{
//  				fv = -g_oLocalSysPara.m_fAC_VolMax;
//  			}
//  		}
//  		ui->m_editVarV2->setText(QString::number(fv,'f',3));
// 
//  		if (m_pCurPara->m_fG2Volt != fv)
//  		{
//  			m_pCurPara->m_fG2Volt = fv;
//  			emit sig_Para_G2VoltChanged(fv);
//  
//  			m_bTmtParaChanged = TRUE;
//  		}
//  
//  		QString qName = GetCurChannal(m_pCurTest);
//  		if (m_pCurPara->m_nType == amplitude_type  && qName.contains(tr("U")) && qName.contains(tr("2"))==false)
//  		{
//  			float fdown=0;
//  			float fup=0;
//  			getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDU,m_pCurPara->m_fG1Volt,m_pCurPara->m_fG2Volt,
//  				m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
//  			emit sig_YRangeChanged(amplitude_type, m_strVoltage + "(V)",fdown/FRADIO,fup*FRADIO);
//  		}
//  	}
//  	else
//  	{
//  		ui->m_editVarV2->setText(QString::number(fv,'f',3));
//  	}
//  }
//  
//  void QSttMacroParaEditViewGradient::on_m_editfDiffIAngleChanged()
//  {
//  	QString str = ui->m_editfDiffIAngle->text();
// 
//  	if (str.right(1).contains("."))
//  	{
//  		str.append("000");
//  	}
//  
//  	float fXW= str.toFloat();
//  	if (fXW<0)
//  	{
//  		fXW = 0;
//  	}
//  	else if (fXW>360)
//  	{
//  		fXW = fXW-(int)(fXW/360)*360;
//  	}
//  
//  	ui->m_editfDiffIAngle->setText(QString::number(fXW,'f',1));
// 
//  	if (m_pCurPara->m_fDiffIAngle != fXW)
//  	{
//  		m_pCurPara->m_fDiffIAngle = fXW;
//  		emit sig_Para_DiffAngleChanged(fXW);
//  
//  		m_bTmtParaChanged = TRUE;
//  	}
//  }

void QSttMacroParaEditViewGradient::on_m_editFreqChanged()
{

}

void QSttMacroParaEditViewGradient::on_m_editInitChanged()
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

			connect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
		}
	}
	else if (m_pCurPara->m_nType == phasor_type)
	{
		if (fv<=9999 && fv>=-9999)
		{
		float f1 = fv - (int)fv;
		int f2 = ((int)fv)%360;
		fv = f1+f2;
		}
		else
		{
			fv=0;
		}

		disconnect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
		{
			if (m_pCurPara->m_fStart != fv)
			{
				m_pCurPara->m_fStart = fv;
				emit sig_Para_StartChanged(fv);
				m_bTmtParaChanged = TRUE;
			}

			ui->m_editInit->setText(QString::number(fv,'f',1));
		}

		connect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
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

		disconnect(ui->m_editInit, SIGNAL(editingFinished ()), this, SLOT(slot_Para_StartChanged()));
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

	CDataTypeValue *pCurDataTypeValue = (CDataTypeValue*)m_oGradientChs.GetAtIndex(ui->m_cbbVar->currentIndex());
	m_pGroupWidget->UpdateFaultEditState(pCurDataTypeValue);
}

void QSttMacroParaEditViewGradient::on_m_editFinishChanged()
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
		if (fv<=9999 && fv>=-9999)
		{
		float f1 = fv - (int)fv;
		int f2 = ((int)fv)%360;
		fv = f1+f2;
		}
		else
		{
			fv=0;
		}

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

void QSttMacroParaEditViewGradient::on_m_editStepChanged()
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
		if (fv<=9999 && fv>=-9999)
		{
		float f1 = fv - (int)fv;
		int f2 = ((int)fv)%360;
		fv = f1+f2;
		}
		else
		{
			fv=0;
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

void QSttMacroParaEditViewGradient::on_m_editTimeChanged()
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


void QSttMacroParaEditViewGradient::slot_Estimate()
{
	GradientEstimateDlg dlg(m_pCurPara, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewGradient::slot_SettingValue()
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

void QSttMacroParaEditViewGradient::SetGradientFont()
{
	g_pSttGlobalFont->resolve(QFont::AllPropertiesResolved);//20230801-wxy-修改设置字体无效问题
	ui->m_tabWidget->setFont(*g_pSttGlobalFont);
	ui->m_gpVarSet->setFont(*g_pSttGlobalFont);
	ui->m_labVar->setFont(*g_pSttGlobalFont);
	ui->m_cbbVar->setFont(*g_pSttGlobalFont);
	ui->m_labVarType->setFont(*g_pSttGlobalFont);
	ui->m_cbbVarType->setFont(*g_pSttGlobalFont);
//	ui->m_gpUnChangeSet->setFont(*g_pSttGlobalFont);
// 	ui->m_labVarA1->setFont(*g_pSttGlobalFont);
// 	ui->m_labVarA2->setFont(*g_pSttGlobalFont);
// 	ui->m_labVarV1->setFont(*g_pSttGlobalFont);
// 	ui->m_labVarV2->setFont(*g_pSttGlobalFont);
// 	ui->m_labfDiffIAngle->setFont(*g_pSttGlobalFont);
// 	ui->m_editVarA1->setFont(*g_pSttGlobalFont);
// 	ui->m_editVarA2->setFont(*g_pSttGlobalFont);
// 	ui->m_editVarV1->setFont(*g_pSttGlobalFont);
// 	ui->m_editVarV2->setFont(*g_pSttGlobalFont);	
// 	ui->m_editfDiffIAngle->setFont(*g_pSttGlobalFont);	
	ui->m_gpChangeSet->setFont(*g_pSttGlobalFont);
	ui->m_editFinish->setFont(*g_pSttGlobalFont);
	ui->m_labFinish->setFont(*g_pSttGlobalFont);
	ui->m_labInit->setFont(*g_pSttGlobalFont);
	ui->m_editInit->setFont(*g_pSttGlobalFont);	
	ui->m_labStep->setFont(*g_pSttGlobalFont);
	ui->m_editStep->setFont(*g_pSttGlobalFont);
	ui->m_labTime->setFont(*g_pSttGlobalFont);
	ui->m_editTime->setFont(*g_pSttGlobalFont);
	//ui->m_gpOtherSet->setFont(*g_pSttGlobalFont);	其他参数被合并到变量设置，不再需要
	ui->m_cbbType->setFont(*g_pSttGlobalFont);
	ui->m_labDirection->setFont(*g_pSttGlobalFont);
	ui->m_cbbDirection->setFont(*g_pSttGlobalFont);
	ui->m_labType->setFont(*g_pSttGlobalFont);
//	ui->m_btnManual->setFont(*g_pSttGlobalFont);
	//新增控件字体设置
	ui->m_gpMannual->setFont(*g_pSttGlobalFont);
	ui->m_labTimeBeforeChange->setFont(*g_pSttGlobalFont);
	ui->m_editTimeBeforeChange->setFont(*g_pSttGlobalFont);
	ui->m_labTimeBeforeFail->setFont(*g_pSttGlobalFont);
	ui->m_editTimeBeforeFail->setFont(*g_pSttGlobalFont);
// 	ui->m_labCurBeforeChange->setFont(*g_pSttGlobalFont);
// 	ui->m_labfDiffUaIaAngle->setFont(*g_pSttGlobalFont);
// 	ui->m_editfDiffUaIaAngle->setFont(*g_pSttGlobalFont);
// 	ui->m_editCurBeforeChange->setFont(*g_pSttGlobalFont);
//	ui->m_cbGroup->setFont(*g_pSttGlobalFont);
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
// 	ui->m_cbBOut5->setFont(*g_pSttGlobalFont);	
// 	ui->m_cbBOut6->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut7->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut8->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut9->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut10->setFont(*g_pSttGlobalFont);

	ui->m_gpBoutError->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut1_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut2_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut3_E->setFont(*g_pSttGlobalFont);	
	ui->m_cbBOut4_E->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut5_E->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut6_E->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut7_E->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut8_E->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut9_E->setFont(*g_pSttGlobalFont);
// 	ui->m_cbBOut10_E->setFont(*g_pSttGlobalFont);

	ui->m_btnSettingValue->setFont(*g_pSttGlobalFont);
	ui->m_btnEstimate->setFont(*g_pSttGlobalFont);
	ui->m_btnMoreOut->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewGradient::SetDefaultFaultValue(long nChIndex)
{
	//重置非递变通道的故障态值
	switch(nChIndex)
	{
	case 0:
		m_pGroupWidget->SetDefaultFaultValue(0);
		break;
	case 1:
		m_pGroupWidget->SetDefaultFaultValue(1);
		break;
	case 2:
		m_pGroupWidget->SetDefaultFaultValue(2);
		break;
	case 4:
		m_pGroupWidget->SetDefaultFaultValue(0);
		m_pGroupWidget->SetDefaultFaultValue(1);
		break;
	case 5:
		m_pGroupWidget->SetDefaultFaultValue(1);
		m_pGroupWidget->SetDefaultFaultValue(2);
		break;
	case 6:
		m_pGroupWidget->SetDefaultFaultValue(0);
		m_pGroupWidget->SetDefaultFaultValue(2);
		break;
	case 7:
		m_pGroupWidget->SetDefaultFaultValue(0);
		m_pGroupWidget->SetDefaultFaultValue(1);
		m_pGroupWidget->SetDefaultFaultValue(2);
		break;
	case 8:
		m_pGroupWidget->SetDefaultFaultValue(3);
		break;
	case 9:
		m_pGroupWidget->SetDefaultFaultValue(4);
		break;
	case 10:
		m_pGroupWidget->SetDefaultFaultValue(5);
		break;
	case 11:
		m_pGroupWidget->SetDefaultFaultValue(3);
		m_pGroupWidget->SetDefaultFaultValue(4);
		m_pGroupWidget->SetDefaultFaultValue(5);
		break;
	case 12:
		m_pGroupWidget->SetDefaultFaultValue(0, false);
		break;
	case 13:
		m_pGroupWidget->SetDefaultFaultValue(1, false);
		break;
	case 14:
		m_pGroupWidget->SetDefaultFaultValue(2, false);
		break;
	case 15:
		m_pGroupWidget->SetDefaultFaultValue(0, false);
		m_pGroupWidget->SetDefaultFaultValue(1, false);
		break;
	case 16:
		m_pGroupWidget->SetDefaultFaultValue(1, false);
		m_pGroupWidget->SetDefaultFaultValue(2, false);
		break;
	case 17:
		m_pGroupWidget->SetDefaultFaultValue(0, false);
		m_pGroupWidget->SetDefaultFaultValue(2, false);
		break;
	case 18:
		m_pGroupWidget->SetDefaultFaultValue(0, false);
		m_pGroupWidget->SetDefaultFaultValue(1, false);
		m_pGroupWidget->SetDefaultFaultValue(2, false);
		break;
	case 19:
		m_pGroupWidget->SetDefaultFaultValue(3, false);
		break;
	case 20:
		m_pGroupWidget->SetDefaultFaultValue(4, false);
		break;
	case 21:
		m_pGroupWidget->SetDefaultFaultValue(5, false);
		break;
	case 22:
		m_pGroupWidget->SetDefaultFaultValue(3, false);
		m_pGroupWidget->SetDefaultFaultValue(4, false);
		m_pGroupWidget->SetDefaultFaultValue(5, false);
		break;
	case 23:
		m_pGroupWidget->SetDefaultFaultValue(0);
		m_pGroupWidget->SetDefaultFaultValue(1);
		m_pGroupWidget->SetDefaultFaultValue(2);
		m_pGroupWidget->SetDefaultFaultValue(3);
		m_pGroupWidget->SetDefaultFaultValue(4);
		m_pGroupWidget->SetDefaultFaultValue(5);
		break;
	case 24:
		m_pGroupWidget->SetDefaultFaultValue(0, false);
		m_pGroupWidget->SetDefaultFaultValue(1, false);
		m_pGroupWidget->SetDefaultFaultValue(2, false);
		m_pGroupWidget->SetDefaultFaultValue(3, false);
		m_pGroupWidget->SetDefaultFaultValue(4, false);
		m_pGroupWidget->SetDefaultFaultValue(5, false);
		break;
	case 27:
		m_pGroupWidget->SetDefaultFaultValue(3);
		m_pGroupWidget->SetDefaultFaultValue(4);
		break;
	case 28:
		m_pGroupWidget->SetDefaultFaultValue(4);
		m_pGroupWidget->SetDefaultFaultValue(5);
		break;
	case 29:
		m_pGroupWidget->SetDefaultFaultValue(3);
		m_pGroupWidget->SetDefaultFaultValue(5);
		break;
	case 30:
		m_pGroupWidget->SetDefaultFaultValue(3, false);
		m_pGroupWidget->SetDefaultFaultValue(4, false);
		break;
	case 31:
		m_pGroupWidget->SetDefaultFaultValue(4, false);
		m_pGroupWidget->SetDefaultFaultValue(5, false);
		break;
	case 32:
		m_pGroupWidget->SetDefaultFaultValue(3, false);
		m_pGroupWidget->SetDefaultFaultValue(5, false);
		break;
	case 33:
		m_pGroupWidget->SetDefaultFaultValue(0, false);
		m_pGroupWidget->SetDefaultFaultValue(1, false);
		m_pGroupWidget->SetDefaultFaultValue(2, false);
		break;
	case 34:
		m_pGroupWidget->SetDefaultFaultValue(3, false);
		m_pGroupWidget->SetDefaultFaultValue(4, false);
		m_pGroupWidget->SetDefaultFaultValue(5, false);
		break;
	default:
		break;
	}

	m_pGroupWidget->Update();
}

void QSttMacroParaEditViewGradient::InitUI()
{
	SetGradientFont();
	((QSttTabWidget*)ui->m_tabWidget)->InitStyleSheet();

	disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	disconnect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));
	disconnect(ui->m_cbbDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbDirection_currentIndexChanged( int)));

	CString strText;
	xlang_GetLangStrByFile(strText, "Gradient_Anticlockwise");
	ui->m_cbbDirection->addItem(strText);
	xlang_GetLangStrByFile(strText, "Gradient_Clockwise");
	ui->m_cbbDirection->addItem(strText);
	ui->m_cbbDirection->setDisabled(true);
	
// 	initMaxPositiveEdit(ui->m_editVarA1);
// 	initMaxPositiveEdit(ui->m_editVarA2);
// 	initMaxPositiveEdit(ui->m_editVarV1);
// 	initMaxPositiveEdit(ui->m_editVarV2);
// 	initMaxEdit_one(ui->m_editfDiffIAngle);
	initMaxPositiveEdit(ui->m_editInit);
	initMaxPositiveEdit(ui->m_editFinish);
	initMaxPositiveEdit(ui->m_editStep);
	initMaxPositiveEdit(ui->m_editTime);

	initQList();

	UpdateGradientChs();

	ui->m_cbbVarType->clear();
	ui->m_cbbVarType->addItems(m_ChangeTypeList);
	ui->m_cbbType->clear();

	connect(ui->m_cbbDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbDirection_currentIndexChanged( int)));
	connect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));
	connect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));

// 	m_pGroupWidget = new QGradientGroupWidget(this);
// 	m_pGroupWidget->Init(m_pCurPara);
//	m_pGroupWidget->hide();

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
	
	// 20230825 suyang   适配L33D界面
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()==600)
	{
		ui->m_cbbVar->setStyleSheet("QComboBox { min-height: 20px; }");
		ui->m_cbbVarType->setStyleSheet("QComboBox { min-height: 20px; }");
		ui->m_cbbType->setStyleSheet("QComboBox { min-height: 20px; }");
		ui->m_cbbDirection->setStyleSheet("QComboBox { min-height: 20px; }");
		ui->m_gpChangeSet->setStyleSheet("QGroupBox { min-height: 150px; }");
		ui->m_gpVarSet->setStyleSheet("QGroupBox { min-height: 150px; }");
		ui->m_gpMannual->setStyleSheet("QGroupBox { min-height: 150px; }");
		ui->m_gpBin->setStyleSheet("QGroupBox { min-height: 80px; }");
	}
	


}

void QSttMacroParaEditViewGradient::InitGradientChannel(para_type vartype)
{
	CDataTypeValue *pCurSelData = m_oGradientChs.FindByIndex(vartype);

	if (pCurSelData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的递变通道(Index=%d)未查找到."),vartype);
		 CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurselinNotFound.GetString(),vartype); //当前选择的递变通道(Index=%d)未查找到. lcq 3.14
		return;
	} 
	else
	{
		long nIndex = m_oGradientChs.FindIndex(pCurSelData);
		ui->m_cbbVar->setCurrentIndex(nIndex);
	}
}

void QSttMacroParaEditViewGradient::updateLabName()
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

				//xlang_GetLangStrByFile(strTemp, "Native_Action");
				//ui->m_labAction->setText(strTemp.mid(0, ui->m_labAction->text().lastIndexOf("(") + 1) + "A):");
				//xlang_GetLangStrByFile(strTemp, "Native_ReturnVal");
				//ui->m_labReturn->setText(strTemp.mid(0, ui->m_labReturn->text().lastIndexOf("(") + 1) + "A):");

				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDI,m_pCurPara->m_fG1Current,m_pCurPara->m_fG2Current,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strCurrent + "(A)",fdown/FRADIO,fup*FRADIO);

//				if (str.contains(tr("2")))
//				{
// 					ui->m_editVarA2->setDisabled(true);
// 					ui->m_editVarA1->setDisabled(false);
// 					ui->m_labVarA1->setDisabled(false);
// 					ui->m_labVarA2->setDisabled(true);
//				}
//				else
//				{
// 					ui->m_editVarA2->setDisabled(false);
// 					ui->m_editVarA1->setDisabled(true);
// 					ui->m_labVarA1->setDisabled(true);
// 					ui->m_labVarA2->setDisabled(false);
//				}

// 				ui->m_editVarV1->setDisabled(false);
// 				ui->m_editVarV2->setDisabled(false);
// 				ui->m_labVarV1->setDisabled(false);
// 				ui->m_labVarV2->setDisabled(false);
	
			}
			else if (str.contains(tr("U")))
			{
				ui->m_labInit->setText(strInit + "(V):");
				ui->m_labFinish->setText(strFinish + "(V):");
				ui->m_labStep->setText(strStep + "(V):");

				//xlang_GetLangStrByFile(strTemp, "Native_Action");
				//ui->m_labAction->setText(strTemp.mid(0, ui->m_labAction->text().lastIndexOf("(") + 1) + "V):");
				//xlang_GetLangStrByFile(strTemp, "Native_ReturnVal");
				//ui->m_labReturn->setText(strTemp.mid(0, ui->m_labReturn->text().lastIndexOf("(") + 1) + "V):");

				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDU,m_pCurPara->m_fG1Volt,m_pCurPara->m_fG2Volt,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strVoltage + "(V)",fdown/FRADIO,fup*FRADIO);

//				if (str.contains(tr("2")))
//				{
// 					ui->m_editVarV1->setDisabled(false);
// 					ui->m_editVarV2->setDisabled(true);
// 					ui->m_labVarV1->setDisabled(false);
// 					ui->m_labVarV2->setDisabled(true);	
//				}
//				else
//				{
// 					ui->m_editVarV1->setDisabled(true);
// 					ui->m_editVarV2->setDisabled(false);
// 					ui->m_labVarV1->setDisabled(true);
// 					ui->m_labVarV2->setDisabled(false);
					
//				}

// 				ui->m_editVarA2->setDisabled(false);
// 				ui->m_editVarA1->setDisabled(false);
// 				ui->m_labVarA1->setDisabled(false);
// 				ui->m_labVarA2->setDisabled(false);
			}

// 			ui->m_editfDiffIAngle->setDisabled(false);
		}
		break;
	case phasor_type:
		{
// 			ui->m_editVarV1->setDisabled(false);
// 			ui->m_editVarV2->setDisabled(false);
// 			ui->m_labVarV1->setDisabled(false);
// 			ui->m_labVarV2->setDisabled(false);
// 			ui->m_editVarA2->setDisabled(false);
// 			ui->m_editVarA1->setDisabled(false);
// 			ui->m_labVarA1->setDisabled(false);
// 			ui->m_labVarA2->setDisabled(false);
// 			ui->m_editfDiffIAngle->setDisabled(true);
			
			ui->m_labInit->setText(strInit + strPhase);
			ui->m_labFinish->setText(strFinish + strPhase);
			ui->m_labStep->setText(strStep + strPhase);

			//xlang_GetLangStrByFile(strTemp, "Native_Action");
			//ui->m_labAction->setText(strTemp.mid(0, ui->m_labAction->text().lastIndexOf("(")) + strPhase);
			//xlang_GetLangStrByFile(strTemp, "Native_ReturnVal");
			//ui->m_labReturn->setText(strTemp.mid(0, ui->m_labReturn->text().lastIndexOf("(")) + strPhase);

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
	case fre_type:
		{
// 			ui->m_editVarV1->setDisabled(false);
// 			ui->m_editVarV2->setDisabled(false);
// 			ui->m_labVarV1->setDisabled(false);
// 			ui->m_labVarV2->setDisabled(false);
// 			ui->m_editVarA2->setDisabled(false);
// 			ui->m_editVarA1->setDisabled(false);
// 			ui->m_labVarA1->setDisabled(false);
// 			ui->m_labVarA2->setDisabled(false);
// 			ui->m_editfDiffIAngle->setDisabled(false);
		
			ui->m_labInit->setText(strInit + "(Hz):");
			ui->m_labFinish->setText(strFinish + "(Hz):");
			ui->m_labStep->setText(strStep + "(Hz):");

			//xlang_GetLangStrByFile(strTemp, "Native_Action");
			//ui->m_labAction->setText(strTemp.mid(0, ui->m_labAction->text().lastIndexOf("(") + 1) + "Hz):");
			//xlang_GetLangStrByFile(strTemp, "Native_ReturnVal");
			//ui->m_labReturn->setText(strTemp.mid(0, ui->m_labReturn->text().lastIndexOf("(") + 1) + "Hz):");

			emit sig_Para_ChangeIsAll();
			float fdown=0;
			float fup=0;
			getYRange(1,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
			emit sig_YRangeChanged(fre_type, m_strFreq + "(Hz)",fdown,fup*FRADIO);
		}
		break;
	default:
		break;
	}
}

void QSttMacroParaEditViewGradient::initQList()
{
	CString strPhase, strFreq, strAmp;
	CString strAction, strReturn, strAngle;
	
	xlang_GetLangStrByFile(strPhase, "Native_Angle");
	xlang_GetLangStrByFile(strFreq, "Native_Freq");
	xlang_GetLangStrByFile(strAmp, "Native_Amplitude");
	xlang_GetLangStrByFile(strAction, "Native_Action");
	strAction = strAction.Mid(0, strAction.ReverseFind('('));
	xlang_GetLangStrByFile(strReturn, "Native_ReturnCoeff");
	xlang_GetLangStrByFile(strAngle, "Gradient_MaxAngle");

	m_ChangeTypeList.clear();
	m_ChangeTypeList << strAmp << strPhase << strFreq;

	m_ChangeTypeList2.clear();
	m_ChangeTypeList2 << strAmp;

	m_listTestMode2.clear();;
	m_listTestMode2 << strAction << strReturn;
	m_listTestMode3.clear();
	m_listTestMode3<< strAction << strReturn << strAngle;
}

void QSttMacroParaEditViewGradient::InitParas()
{
	if(m_pCurPara == NULL)
		return;

	disconnect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
	disconnect(ui->m_cbbVarType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVarType_currentIndexChanged( int)));
	disconnect(ui->m_cbbType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbType_currentIndexChanged( int)));

	ui->m_cbbVarType->clear();
	if(m_pCurPara->m_nChannel == iabcAdd_type || m_pCurPara->m_nChannel == ia2b2c2Add_type)
	{
		ui->m_cbbVarType->addItems(m_ChangeTypeList2);
	}
	else
	{
		ui->m_cbbVarType->addItems(m_ChangeTypeList);
	}

	para_type var = getParaTypeByInt(m_pCurPara->m_nChannel);
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
//	initMaxPositiveEdit(ui->m_editCurBeforeChange);
//  initMaxEdit_one(ui->m_editfDiffIAngle);

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
// 	ui->m_editCurBeforeChange->setText(QString::number(m_pCurPara->m_fEDI,'f',3));
//	ui->m_editfDiffUaIaAngle->setText(QString::number(m_pCurPara->m_fEDUaIaAngle,'f',1));
	m_pCurPara->m_fEDFreq = g_oSystemParas.m_fFNom;//Zhouyy 2023/01/06

// 	ui->m_editVarA1->setText(QString::number(m_pCurPara->m_fG1Current, 'f',3));
// 	ui->m_editVarA2->setText(QString::number(m_pCurPara->m_fG2Current, 'f',3));
// 	ui->m_editVarV1->setText(QString::number(m_pCurPara->m_fG1Volt, 'f',3));
// 	ui->m_editVarV2->setText(QString::number(m_pCurPara->m_fG2Volt, 'f',3));
// 	ui->m_editfDiffIAngle->setText(QString::number(m_pCurPara->m_fDiffIAngle, 'f', 1));   	
	
	ui->m_editInit->setText(QString::number(m_pCurPara->m_fStart, 'f', 3));
	ui->m_editFinish->setText(QString::number(m_pCurPara->m_fStop, 'f', 3));
	ui->m_editStep->setText(QString::number(m_pCurPara->m_fStep, 'f', 3));
	ui->m_editTime->setText(QString::number(m_pCurPara->m_fStepTime, 'f', 3));	//步长时间=故障时间
	
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

	//常态开出量设置
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut1,m_pCurPara->m_binOut[0],0);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut2,m_pCurPara->m_binOut[0],1);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut3,m_pCurPara->m_binOut[0],2);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut4,m_pCurPara->m_binOut[0],3);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut5,m_pCurPara->m_binOut[0],4);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut6,m_pCurPara->m_binOut[0],5);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut7,m_pCurPara->m_binOut[0],6);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut8,m_pCurPara->m_binOut[0],7);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut9,m_pCurPara->m_binOut[0],8);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut10,m_pCurPara->m_binOut[0],9);

	//故障态开出量设置
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut1_E,m_pCurPara->m_binOut[1],0);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut2_E,m_pCurPara->m_binOut[1],1);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut3_E,m_pCurPara->m_binOut[1],2);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut4_E,m_pCurPara->m_binOut[1],3);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut5_E,m_pCurPara->m_binOut[1],4);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut6_E,m_pCurPara->m_binOut[1],5);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut7_E,m_pCurPara->m_binOut[1],6);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut8_E,m_pCurPara->m_binOut[1],7);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut9_E,m_pCurPara->m_binOut[1],8);
// 	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut10_E,m_pCurPara->m_binOut[1],9);

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
	EnableRadientType();

	//初始化时间特性曲线的标题
	emit sig_Para_ChangeIndexChanged(m_pCurPara->m_nChannel);

	CopyBinaryConfig();
	g_theTestCntrFrame->UpdateToolButtons();
}

void QSttMacroParaEditViewGradient::InitConnections()
{
	connect(ui->m_editTimeBeforeChange,SIGNAL(editingFinished()),this,SLOT(on_m_editTimeBeforeChangeChanged()));
	connect(ui->m_editTimeBeforeFail,SIGNAL(editingFinished()),this,SLOT(on_m_editTimeBeforeFailChanged()));
//	connect(ui->m_editCurBeforeChange,SIGNAL(editingFinished()),this,SLOT(on_m_editCurBeforeChangeChanged()));
//	connect(ui->m_editfDiffUaIaAngle,SIGNAL(editingFinished()),this,SLOT(on_m_editfDiffUaIaAngleChanged()));//响应部分（新界面需要）
// 	connect(ui->m_editVarA1, SIGNAL(editingFinished ()), this, SLOT(on_m_editVarA1Changed()));
// 	connect(ui->m_editVarA2, SIGNAL(editingFinished()), this, SLOT(on_m_editVarA2Changed()));
// 	connect(ui->m_editVarV1, SIGNAL(editingFinished ()), this, SLOT(on_m_editVarV1Changed()));
// 	connect(ui->m_editVarV2, SIGNAL(editingFinished()), this, SLOT(on_m_editVarV2Changed()));
// 	connect(ui->m_editfDiffIAngle, SIGNAL(editingFinished ()), this, SLOT(on_m_editfDiffIAngleChanged()));

	connect(ui->m_editInit, SIGNAL(editingFinished()), this, SLOT(on_m_editInitChanged()));
	connect(ui->m_editFinish, SIGNAL(editingFinished ()), this, SLOT(on_m_editFinishChanged()));
	connect(ui->m_editStep, SIGNAL(editingFinished ()), this, SLOT(on_m_editStepChanged()));
	connect(ui->m_editTime, SIGNAL(editingFinished ()), this, SLOT(on_m_editTimeChanged()));
	//connect(ui->m_cbGroup, SIGNAL(stateChanged(int)), this, SLOT(on_m_cbGroup_clicked(int)));
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
// 	connect(ui->m_cbBOut5, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut5StateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut6, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut6StateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut7, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut7StateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut8, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut8StateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut9, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut9StateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut10, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut10StateChanged(int)),Qt::UniqueConnection);

	connect(ui->m_cbBOut1_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut1_EStateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut2_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut2_EStateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut3_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut3_EStateChanged(int)),Qt::UniqueConnection);
	connect(ui->m_cbBOut4_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut4_EStateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut5_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut5_EStateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut6_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut6_EStateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut7_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut7_EStateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut8_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut8_EStateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut9_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut9_EStateChanged(int)),Qt::UniqueConnection);
// 	connect(ui->m_cbBOut10_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut10_EStateChanged(int)),Qt::UniqueConnection);
}

void QSttMacroParaEditViewGradient::CopyBinaryConfig(BOOL b)
{
	tmt_GradientParasEx* pGradientPara = m_pCurPara;
	if(pGradientPara == NULL)
	{
		return;
	}

	if(b)
	{
		g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic = pGradientPara->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect = pGradientPara->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i].nSelect = pGradientPara->m_binInEx[i].nSelect;
		}
	}
	else
	{
		pGradientPara->m_nBinLogic = g_theTestCntrFrame->GetBinaryConfig()->m_nBinLogic;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++){
			pGradientPara->m_binIn[i].nSelect = g_theTestCntrFrame->GetBinaryConfig()->m_binIn[i].nSelect;
		}

		for (int i=0;i<MAX_ExBINARY_COUNT;i++){
			pGradientPara->m_binInEx[i].nSelect = g_theTestCntrFrame->GetBinaryConfig()->m_binInEx[i].nSelect;
		}
	}
}

void QSttMacroParaEditViewGradient::EnableRadientType()
{
	if (m_pCurPara == NULL)
	{
		return;
	}

	if (m_pCurPara->m_nType == phasor_type && m_pCurPara->m_nTestMode != 2)
	{
		ui->m_cbbDirection->setDisabled(false);
	}
	else
	{
		ui->m_cbbDirection->setDisabled(true);
	}
}

void QSttMacroParaEditViewGradient::getYRange(float ftime,float fv, float v1,float v2,float fstart,float fend,float &down,float &up )
{
	float fNew=fv;
	if (ftime < EPSINON)
	{
		fNew=0;
	}

	up = getMaxFormThreeValue(getMaxFormThreeValue(fNew,v1,v2),fstart,fend);
	down = getMinFormThreeValue(getMinFormThreeValue(fNew,v1,v2),fstart,fend);
}

void QSttMacroParaEditViewGradient::UpdateGradientChs()
{
	if (g_oSttTestResourceMngr.m_pTestResouce != NULL)
	{
		g_oSttTestResourceMngr.m_pTestResouce->AddGradientChs_All(m_oGradientChs);
	}

	disconnect(ui->m_cbbVar, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cbbVar_currentIndexChanged( int)));
	ui->m_cbbVar->clear();

	CDataTypeValue *pCurTypeValue = NULL;
	POS pos = m_oGradientChs.GetHeadPosition();

	while(pos)
	{
		pCurTypeValue = (CDataTypeValue *)m_oGradientChs.GetNext(pos);
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

long QSttMacroParaEditViewGradient::GetSttGradientChannelType(long nChannel)
{
	if ((nChannel == ia1_type)||(nChannel == ib1_type)||(nChannel == ic1_type)||(nChannel == iabc1_type)
		||(nChannel == iab1_type)||(nChannel == ibc1_type)||(nChannel == ica1_type)||(nChannel == iabcAdd_type))
	{
		return STT_GRADIENT_CHANNEL_TYPE_G1_CURR;
	}
	else if ((nChannel == va1_type)||(nChannel == vb1_type)||(nChannel == vc1_type)||(nChannel == vabc1_type)
		||(nChannel == vab1_type)||(nChannel == vbc1_type)||(nChannel == vca1_type)||(nChannel == vabcAdd_type))
	{
		return STT_GRADIENT_CHANNEL_TYPE_G1_VOLT;
	}
	else if ((nChannel == ia2_type)||(nChannel == ib2_type)||(nChannel == ic2_type)||(nChannel == iabc2_type)
		||(nChannel == iab2_type)||(nChannel == ibc2_type)||(nChannel == ica2_type)||(nChannel == ia2b2c2Add_type))
	{
		return STT_GRADIENT_CHANNEL_TYPE_G2_CURR;
	}
	else if ((nChannel == va2_type)||(nChannel == vb2_type)||(nChannel == vc2_type)||(nChannel == vabc2_type)
		||(nChannel == vab2_type)||(nChannel == vbc2_type)||(nChannel == vca2_type)||(nChannel == va2b2c2Add_type))
	{
		return STT_GRADIENT_CHANNEL_TYPE_G2_VOLT;
	}
	else if (nChannel == iall_type)
	{
		return STT_GRADIENT_CHANNEL_TYPE_ALL_CURR;
	}
	else if (nChannel == vall_type)
	{
		return STT_GRADIENT_CHANNEL_TYPE_ALL_VOLT;
	}
	else if (nChannel == freAll_type)
	{
		return STT_GRADIENT_CHANNEL_TYPE_ALL_FREQ;
	}

	return null_type;
}

void QSttMacroParaEditViewGradient::InitUI_AfterGridentSel()
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
	
 	long nGradientChannel = GetSttGradientChannelType(m_pCurPara->m_nChannel);
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
//  		ui->m_labVarA1->setDisabled(true);
//  		ui->m_editVarA1->setDisabled(true);
//  		ui->m_labVarA2->setDisabled(false);
//  		ui->m_editVarA2->setDisabled(false);
 
//  		ui->m_editVarV1->setDisabled(false);
//  		ui->m_editVarV2->setDisabled(false);
//  		ui->m_labVarV1->setDisabled(false);
//  		ui->m_labVarV2->setDisabled(false);
 	}
 	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G1_VOLT)
 	{
 		if (m_pCurPara->m_nType == amplitude_type)
 		{
 			m_pCurPara->m_fG1Volt = m_pCurPara->m_fEDU;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
//  		ui->m_editVarV1->setText(QString::number(m_pCurPara->m_fG1Volt,'f',3));
 		}
 
 		bVoltageChannel = TRUE;
 // 		ui->m_labVarV1->setDisabled(true);
 // 		ui->m_editVarV1->setDisabled(true);
 // 		ui->m_labVarV2->setDisabled(false);
 // 		ui->m_editVarV2->setDisabled(false);
 // 
 // 		ui->m_labVarA1->setDisabled(false);
 // 		ui->m_editVarA1->setDisabled(false);
 // 		ui->m_labVarA2->setDisabled(false);
 // 		ui->m_editVarA2->setDisabled(false);

 	}
 	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_CURR)
 	{
 		if (m_pCurPara->m_nType == amplitude_type)
 		{
 			m_pCurPara->m_fG2Current = m_pCurPara->m_fEDI;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
//  		ui->m_editVarA2->setText(QString::number(m_pCurPara->m_fG2Current,'f',3));
		}
 
 		bCurentChannel = TRUE;
 // 		ui->m_labVarA1->setDisabled(false);
 // 		ui->m_editVarA1->setDisabled(false);
 // 		ui->m_labVarA2->setDisabled(true);
 // 		ui->m_editVarA2->setDisabled(true);
 // 
 // 		ui->m_editVarV1->setDisabled(false);
 // 		ui->m_editVarV2->setDisabled(false);
 // 		ui->m_labVarV1->setDisabled(false);
 // 		ui->m_labVarV2->setDisabled(false);
 
 	}
 	else if (nGradientChannel == STT_GRADIENT_CHANNEL_TYPE_G2_VOLT)
 	{
 		if (m_pCurPara->m_nType == amplitude_type)
 		{
 			m_pCurPara->m_fG2Volt = m_pCurPara->m_fEDU;//zhouhj 20210710 在切换通道选择时,当前变化通道组的非变化通道为故障前值
//  			ui->m_editVarV2->setText(QString::number(m_pCurPara->m_fG2Volt,'f',3));
 		}

 		bVoltageChannel = TRUE;
 // 		ui->m_labVarV1->setDisabled(false);
 // 		ui->m_editVarV1->setDisabled(false);
 // 		ui->m_labVarV2->setDisabled(true);
 // 		ui->m_editVarV2->setDisabled(true);
 // 
 // 		ui->m_labVarA1->setDisabled(false);
 // 		ui->m_editVarA1->setDisabled(false);
 // 		ui->m_labVarA2->setDisabled(false);
 // 		ui->m_editVarA2->setDisabled(false);
 
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
 // 		ui->m_labVarV1->setDisabled(false);
 // 		ui->m_editVarV1->setDisabled(false);
 // 		ui->m_labVarV2->setDisabled(false);
 // 		ui->m_editVarV2->setDisabled(false);
 // 
 // 		ui->m_labVarA1->setDisabled(true);
 // 		ui->m_editVarA1->setDisabled(true);
 // 		ui->m_labVarA2->setDisabled(true);
 // 		ui->m_editVarA2->setDisabled(true);
 
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
 // 		ui->m_labVarV1->setDisabled(true);
 // 		ui->m_editVarV1->setDisabled(true);
 // 		ui->m_labVarV2->setDisabled(true);
 // 		ui->m_editVarV2->setDisabled(true);
 // 
 // 		ui->m_labVarA1->setDisabled(false);
 // 		ui->m_editVarA1->setDisabled(false);
 // 		ui->m_labVarA2->setDisabled(false);
 // 		ui->m_editVarA2->setDisabled(false);
 	}
 	else if (m_pCurPara->m_nChannel == freAll_type)
 	{
 // 		ui->m_labVarV1->setDisabled(false);
 // 		ui->m_editVarV1->setDisabled(false);
 // 		ui->m_labVarV2->setDisabled(false);
 // 		ui->m_editVarV2->setDisabled(false);
 // 
 // 		ui->m_labVarA1->setDisabled(false);
 // 		ui->m_editVarA1->setDisabled(false);
 // 		ui->m_labVarA2->setDisabled(false);
 // 		ui->m_editVarA2->setDisabled(false);
 
 	}

	//递变通道为三相电流相加，自动更换递变类型
	if(m_pCurPara->m_nChannel == iabcAdd_type || m_pCurPara->m_nChannel == ia2b2c2Add_type)
	{
		m_pCurPara->m_nType = amplitude_type;
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
	case amplitude_type:
		{
			if (bCurentChannel)
			{
				ui->m_labInit->setText(strInit + "(A):");
				ui->m_labFinish->setText(strFinish + "(A):");
				ui->m_labStep->setText(strStep + "(A):");

				//xlang_GetLangStrByFile(strTemp, "Native_Action");
				//ui->m_labAction->setText(strTemp.mid(0, ui->m_labAction->text().lastIndexOf("(") + 1) + "A):");
				//xlang_GetLangStrByFile(strTemp, "Native_ReturnVal");
				//ui->m_labReturn->setText(strTemp.mid(0, ui->m_labReturn->text().lastIndexOf("(") + 1) + "A):");

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

				//xlang_GetLangStrByFile(strTemp, "Native_Action");
				//ui->m_labAction->setText(strTemp.mid(0, ui->m_labAction->text().lastIndexOf("(") + 1) + "V):");
				//xlang_GetLangStrByFile(strTemp, "Native_ReturnVal");
				//ui->m_labReturn->setText(strTemp.mid(0, ui->m_labReturn->text().lastIndexOf("(") + 1) + "V):");

				float fdown=0;
				float fup=0;
				getYRange(m_pCurPara->m_fPreFaultTime,m_pCurPara->m_fEDU,m_pCurPara->m_fG1Volt,m_pCurPara->m_fG2Volt,
					m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
				emit sig_YRangeChanged(amplitude_type, m_strVoltage + "(V)",fdown/FRADIO,fup*FRADIO);
			}

			//ui->m_editfDiffIAngle->setDisabled(false);
		}
		break;
	case phasor_type:
		{
			emit sig_Para_ChangeIndexChanged(m_pCurPara->m_nChannel);
// 			ui->m_editVarV1->setDisabled(false);
// 			ui->m_editVarV2->setDisabled(false);
// 			ui->m_labVarV1->setDisabled(false);
// 			ui->m_labVarV2->setDisabled(false);
// 			ui->m_editVarA2->setDisabled(false);
// 			ui->m_editVarA1->setDisabled(false);
// 			ui->m_labVarA1->setDisabled(false);
// 			ui->m_labVarA2->setDisabled(false);
// 			ui->m_editfDiffIAngle->setDisabled(true);

			ui->m_labInit->setText(strInit + strPhase);
			ui->m_labFinish->setText(strFinish + strPhase);
			ui->m_labStep->setText(strStep + strPhase);

			//xlang_GetLangStrByFile(strTemp, "Native_Action");
			//ui->m_labAction->setText(strTemp.mid(0, ui->m_labAction->text().lastIndexOf("(")) + strPhase);
			//xlang_GetLangStrByFile(strTemp, "Native_ReturnVal");
			//ui->m_labReturn->setText(strTemp.mid(0, ui->m_labReturn->text().lastIndexOf("(")) + strPhase);

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
	case fre_type:
		{
// 			ui->m_editVarV1->setDisabled(false);
// 			ui->m_editVarV2->setDisabled(false);
// 			ui->m_labVarV1->setDisabled(false);
// 			ui->m_labVarV2->setDisabled(false);
// 			ui->m_editVarA2->setDisabled(false);
// 			ui->m_editVarA1->setDisabled(false);
// 			ui->m_labVarA1->setDisabled(false);
// 			ui->m_labVarA2->setDisabled(false);
// 			ui->m_editfDiffIAngle->setDisabled(false);	
			ui->m_labInit->setText(strInit + "(Hz):");
			ui->m_labFinish->setText(strFinish + "(Hz):");
			ui->m_labStep->setText(strStep + "(Hz):");

			//xlang_GetLangStrByFile(strTemp, "Native_Action");
			//ui->m_labAction->setText(strTemp.mid(0, ui->m_labAction->text().lastIndexOf("(") + 1) + "Hz):");
			//xlang_GetLangStrByFile(strTemp, "Native_ReturnVal");
			//ui->m_labReturn->setText(strTemp.mid(0, ui->m_labReturn->text().lastIndexOf("(") + 1) + "Hz):");

			emit sig_Para_ChangeIsAll();
			float fdown=0;
			float fup=0;
			getYRange(1,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fEDFreq,m_pCurPara->m_fStart,m_pCurPara->m_fStop,fdown,fup);
			emit sig_YRangeChanged(fre_type, m_strFreq + "(Hz)",fdown,fup*FRADIO);
		}
		break;
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

	//slot_Para_StartChanged();
	//slot_Para_EndChanged();
	//slot_Para_StepChanged();
	//updataWidgetParaName();
}

void QSttMacroParaEditViewGradient::UpdateG1G2()
{
 	long nGradientChannel = GetSttGradientChannelType(m_pCurPara->m_nChannel);
 
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
void QSttMacroParaEditViewGradient::InitMannualparas()
{
	m_pCurPara->m_fPrepareTime = ui->m_editTimeBeforeChange->text().toFloat();	//准备时间
	m_pCurPara->m_fPreFaultTime = ui->m_editTimeBeforeFail->text().toFloat();	//故障前时间
//	m_pCurPara->m_fEDI = ui->m_editCurBeforeChange->text().toFloat();						//变化前电流I0
//	m_pCurPara->m_fEDUaIaAngle = ui->m_editfDiffUaIaAngle->text().toFloat();
}
void QSttMacroParaEditViewGradient::on_m_editTimeBeforeChange_clicked()//鼠标响应部分
{
	slot_edit_changed2(ui->m_editTimeBeforeChange, 0);
}

void QSttMacroParaEditViewGradient::on_m_editTimeBeforeFail_clicked()
{
	slot_edit_changed2(ui->m_editTimeBeforeFail, 0);
}

void QSttMacroParaEditViewGradient::on_m_editCurBeforeChange_clicked()
{
	//slot_edit_changed2(ui->m_editCurBeforeChange, 0);
}

void QSttMacroParaEditViewGradient::on_m_editfDiffUaIaAngle_clicked()
{
	//slot_edit_changed2(ui->m_editfDiffUaIaAngle, 0);
}
void QSttMacroParaEditViewGradient::on_m_editTimeBeforeChangeChanged()//Zhouyy 2023/01/06
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

void QSttMacroParaEditViewGradient::on_m_editTimeBeforeFailChanged()
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

void QSttMacroParaEditViewGradient::on_m_editCurBeforeChangeChanged()
{
// 	if (ui->m_editCurBeforeChange->text().isEmpty())
// 	{
// 		ui->m_editCurBeforeChange->setText("0");
// 	}
// 
// 	QString str = ui->m_editCurBeforeChange->text();
// 	if (str.right(1).contains("."))
// 	{
// 		str.append(000);
// 	}
// 
// 	float fv = str.toFloat();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 	else if (fv>g_oLocalSysPara.m_fAC_CurMax)
// 	{
// 		fv = g_oLocalSysPara.m_fAC_CurMax;
// 	}
// 
// 	ui->m_editCurBeforeChange->setText(QString::number(fv,'f',3));
// 	if(m_pCurPara->m_fEDI != ui->m_editCurBeforeChange->text().toFloat())
// 	{
// 		m_pCurPara->m_fEDI = ui->m_editCurBeforeChange->text().toFloat();
// 		m_bTmtParaChanged = TRUE;
// 	}
	
}

void QSttMacroParaEditViewGradient::on_m_editfDiffUaIaAngleChanged()
{
// 	if (ui->m_editfDiffUaIaAngle->text().isEmpty())
// 	{
// 		ui->m_editfDiffUaIaAngle->setText("0");
// 	}
// 
// 	QString str = ui->m_editfDiffUaIaAngle->text();
// 	if (str.right(1).contains("."))
// 	{
// 		str.append(000);
// 	}
// 
// 	float fv = str.toFloat();
// 	if (fv<0)
// 	{
// 		fv = 0;
// 	}
// 	else if (fv>360)
// 	{
// 		fv = fv-(int)(fv/360)*360;
// 	}
// 
// 	ui->m_editfDiffUaIaAngle->setText(QString::number(fv,'f',1));
// 	if(m_pCurPara->m_fEDUaIaAngle != ui->m_editfDiffUaIaAngle->text().toFloat())
// 	{
// 		m_pCurPara->m_fEDUaIaAngle = ui->m_editfDiffUaIaAngle->text().toFloat();
// 		m_bTmtParaChanged = TRUE;
// 	}
}

void QSttMacroParaEditViewGradient::slot_edit_changed2(QSttLineEdit* pEditLine, long nType)
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


void QSttMacroParaEditViewGradient::slot_chb_InPutA_StateChanged(int)
{
	if (ui->m_cbBinA->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[0].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[0].nSelect = 0;
	}

}

void QSttMacroParaEditViewGradient::slot_chb_InPutB_StateChanged(int)
{
 	if (ui->m_cbBinB->checkState() == Qt::Checked)
 	{
 		m_pCurPara->m_binIn[1].nSelect = 1;
 	}
 	else
 	{
 		m_pCurPara->m_binIn[1].nSelect = 0;
 	}
}

void QSttMacroParaEditViewGradient::slot_chb_InPutC_StateChanged(int)
{
	if (ui->m_cbBinC->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[2].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[2].nSelect = 0;
	}

}

void QSttMacroParaEditViewGradient::slot_chb_InPutD_StateChanged(int)
{
	if (ui->m_cbBinD->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[3].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[3].nSelect = 0;
	}
}

void QSttMacroParaEditViewGradient::slot_chb_InPutE_StateChanged(int)
{
	if (ui->m_cbBinE->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[4].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[4].nSelect = 0;
	}
}

void QSttMacroParaEditViewGradient::slot_chb_InPutF_StateChanged(int)
{
	if (ui->m_cbBinF->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[5].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[5].nSelect = 0;
	}
}

void QSttMacroParaEditViewGradient::slot_chb_InPutG_StateChanged(int)
{
	if (ui->m_cbBinG->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[6].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[6].nSelect = 0;
	}
}

void QSttMacroParaEditViewGradient::slot_chb_InPutH_StateChanged(int)
{
	if (ui->m_cbBinH->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[7].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[7].nSelect = 0;
	}
}

void QSttMacroParaEditViewGradient::slot_chb_InPutI_StateChanged(int)
{
	if (ui->m_cbBinI->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[8].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[8].nSelect = 0;
	}
}

void QSttMacroParaEditViewGradient::slot_chb_InPutJ_StateChanged(int)
{
	if (ui->m_cbBinJ->checkState() == Qt::Checked)
	{
		m_pCurPara->m_binIn[9].nSelect = 1;
	}
	else
	{
		m_pCurPara->m_binIn[9].nSelect = 0;
	}
}

void QSttMacroParaEditViewGradient::slot_radio_AndStateChanged(bool)
{
	if (ui->m_rbAnd->isChecked())
	{
		m_pCurPara->m_nBinLogic = 1;
	}	
}

void QSttMacroParaEditViewGradient::slot_radio_OrStateChanged(bool)
{
	if (ui->m_rbOr->isChecked())
	{
		m_pCurPara->m_nBinLogic = 0;
	}
}

void QSttMacroParaEditViewGradient::slot_chb_OutPut1StateChanged(int)
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

void QSttMacroParaEditViewGradient::slot_chb_OutPut2StateChanged(int)
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

void QSttMacroParaEditViewGradient::slot_chb_OutPut3StateChanged(int)
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

void QSttMacroParaEditViewGradient::slot_chb_OutPut4StateChanged(int)
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
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut5StateChanged(int)
// {
// 	if (ui->m_cbBOut5->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[0][4].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[0][4].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut6StateChanged(int)
// {
// 	if (ui->m_cbBOut6->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[0][5].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[0][5].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut7StateChanged(int)
// {
// 	if (ui->m_cbBOut7->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[0][6].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[0][6].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut8StateChanged(int)
// {
// 	if (ui->m_cbBOut8->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[0][7].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[0][7].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut9StateChanged(int)
// {
// 	if (ui->m_cbBOut9->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[0][8].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[0][8].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut10StateChanged(int)
// {
// 	if (ui->m_cbBOut10->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[0][9].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[0][9].nState = 0;
// 	}
// }

void QSttMacroParaEditViewGradient::slot_chb_OutPut1_EStateChanged(int)
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

void QSttMacroParaEditViewGradient::slot_chb_OutPut2_EStateChanged(int)
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

void QSttMacroParaEditViewGradient::slot_chb_OutPut3_EStateChanged(int)
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

void QSttMacroParaEditViewGradient::slot_chb_OutPut4_EStateChanged(int)
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
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut5_EStateChanged(int)
// {
// 	if (ui->m_cbBOut5_E->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[1][4].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[1][4].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut6_EStateChanged(int)
// {
// 	if (ui->m_cbBOut6_E->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[1][5].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[1][5].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut7_EStateChanged(int)
// {
// 	if (ui->m_cbBOut7_E->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[1][6].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[1][6].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut8_EStateChanged(int)
// {
// 	if (ui->m_cbBOut8_E->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[1][7].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[1][7].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut9_EStateChanged(int)
// {
// 	if (ui->m_cbBOut9_E->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[1][8].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[1][8].nState = 0;
// 	}
// }
// 
// void QSttMacroParaEditViewGradient::slot_chb_OutPut10_EStateChanged(int)
// {
// 	if (ui->m_cbBOut10_E->checkState() == Qt::Checked)
// 	{
// 		m_pCurPara->m_binOut[1][9].nState = 1;
// 	}
// 	else
// 	{
// 		m_pCurPara->m_binOut[1][9].nState = 0;
// 	}
// }
