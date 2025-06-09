#include "SttMacroParaEditViewRemoteCtrl.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Controls/SttTabWidget.h"
#include "../../Module/XLangResource_Native.h"
#include "../Module/CommConfigurationDlg/DevComm/QSttCommCfgDeviceWidget.h"

#include "../State/ShortCalcuDig.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewRemoteCtrl* g_pRemoteCtrl = NULL;

QSttMacroParaEditViewRemoteCtrl::QSttMacroParaEditViewRemoteCtrl(QWidget *parent) 
{
	setWindowFlags(Qt::FramelessWindowHint);
	g_pTheSttTestApp->IinitGbWzdAiTool();
	g_pRemoteCtrl = this;
	m_nReadCount = 0;

	InitUI();
	SetManualOtherParasFont();
	InitConnect();

	m_pBtnWidget->setData();
	InitGirdData();
	m_nRecordIndex = 0;

//	stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
}

QSttMacroParaEditViewRemoteCtrl::~QSttMacroParaEditViewRemoteCtrl()
{
}

//CSttMacroParaEditInterface
void QSttMacroParaEditViewRemoteCtrl::SysConfig(CDataGroup *pSysConfig)
{

}

void QSttMacroParaEditViewRemoteCtrl::SysConfig(CDvmDataset *pSysConfig)
{

}

void QSttMacroParaEditViewRemoteCtrl::SysConfig(const CString &strSysConfig )
{

}

void QSttMacroParaEditViewRemoteCtrl::SetDatas(CDvmDataset *pDataset)
{

}

void QSttMacroParaEditViewRemoteCtrl::SetDatas(CDataGroup *pParas)
{

}

void QSttMacroParaEditViewRemoteCtrl::SetDatas(const CString &strDataset)
{

}

void QSttMacroParaEditViewRemoteCtrl::GetDatas(CDvmDataset *pParas)
{

}

void QSttMacroParaEditViewRemoteCtrl::GetDatas(CDataGroup *pParas)
{

}

void QSttMacroParaEditViewRemoteCtrl::GetDatas(CString& strParas)
{

}


void QSttMacroParaEditViewRemoteCtrl::InitGirdData()
{

	m_pBtnWidget->m_pRemoteCtrlGridFirst->SetData();
	m_pBtnWidget->m_pRemoteCtrlGridSecond->SetData();

}

void QSttMacroParaEditViewRemoteCtrl::InitUI()
{
	m_pMainLayout = new QVBoxLayout;

	m_pBtnWidget = new QRemoteCtrlBtnWidget();
	m_pMainLayout->addWidget(m_pBtnWidget);
	setLayout(m_pMainLayout);
}

// void QSttMacroParaEditViewRemoteCtrl::SendUpdateParameter()
// {
// 	stt_Frame_Ats_UpdateParameter();
// }

void QSttMacroParaEditViewRemoteCtrl::InitConnect()
{
	connect(m_pBtnWidget->m_pInterSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_InterSelectIndexChanged(int)));
	connect(m_pBtnWidget->m_pChannelSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_ChannelSelect_cmb_Changed(int))/*,Qt::UniqueConnection*/);
	connect(m_pBtnWidget->m_pReadCondition, SIGNAL(clicked()), this, SLOT(slot_ReadCondition_PushButton_Clicked()));	
	connect(m_pBtnWidget->m_pRemoteCtrlPre_Button, SIGNAL(clicked()), this, SLOT(slot_RemoteCtrlPre_PushButton_Clicked()));	
	connect(m_pBtnWidget->m_pRemoteCtrlExe_Button, SIGNAL(clicked()), this, SLOT(slot_RemoteCtrlExe_PushButton_Clicked()));	
	connect(m_pBtnWidget->m_pRemoteCtrlCancel_Button, SIGNAL(clicked()), this, SLOT(slot_RemoteCtrlCancel_PushButton_Clicked()));	

	connect(this, SIGNAL(sig_updataParas()), this,SLOT(slot_updateParas()));
//	connect(this, SIGNAL(sig_UpdateExeResult(long)), this,SLOT(slot_UpdateExeResult(long)));
	m_nReadCount = 0;
	connect(&m_oRemoteCtrlTimer,   SIGNAL(timeout()),    this,   SLOT(slot_RemoteCtrlTimer()));
	m_oRemoteCtrlTimer.start(3000);
}

void QSttMacroParaEditViewRemoteCtrl::StartTest()
{
	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	if (! pNative->m_oSttAtsClient.ConnectAtsTestServer())
	{
		return ;
	}
}

void QSttMacroParaEditViewRemoteCtrl::SetManualOtherParasFont()
{
	m_pBtnWidget->m_pRemoteCtrlGridFirst->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pRemoteCtrlGridFirst->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pRemoteCtrlGridSecond->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pRemoteCtrlGridSecond->horizontalHeader()->setFont(*g_pSttGlobalFont);
	//m_pBtnWidget->m_pBtnTab->setFont(*g_pSttGlobalFont);

 	m_pBtnWidget->m_pInterSelect->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pInterSelect_ComboBox->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pChannelSelect->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pChannelSelect_ComboBox->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pDataType->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pDataType_LineEdit->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pOperationSelect->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pOperationSelect_ComboBox->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pRemoteCtrlPre_Button->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pRemoteCtrlExe_Button->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pRemoteCtrlCancel_Button->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pReadCondition->setFont(*g_pSttGlobalFont);
	m_pBtnWidget->m_pCondition_LineEdit->setFont(*g_pSttGlobalFont);

}

void QSttMacroParaEditViewRemoteCtrl::slot_updateParas()
{
// 	if (stt_Frame_IsTestStarted())  //解锁状态
// 	{
// 		SendUpdateParameter();
// 	}

	//stt_Frame_UpdateVectorData();
	//stt_Frame_UpdatePowerData();
	
	//SetParaChanged();
}                        

void QSttMacroParaEditViewRemoteCtrl::ShowReport(CDvmValues *pValues)
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

void QSttMacroParaEditViewRemoteCtrl::slot_InterSelectIndexChanged(int nIndex)
{
	m_pBtnWidget->initBaseData();
	InitGirdData();
	//UpdateRemoteCtrlParas();

	m_nReadCount = 0;//切换间隔需要重新启动报告命令，获得对应路径
}

void QSttMacroParaEditViewRemoteCtrl::slot_ChannelSelect_cmb_Changed(int index)
{
	m_pBtnWidget->slot_cmb_ChannelSelectChanged(index);
}

void QSttMacroParaEditViewRemoteCtrl::slot_ReadCondition_PushButton_Clicked()
{
	m_pBtnWidget->slot_PushButton_ReadConditionClicked();
}

void QSttMacroParaEditViewRemoteCtrl::slot_RemoteCtrlPre_PushButton_Clicked()
{
	if (g_theTestCntrFrame->m_pEngineClientWidget == NULL)
	{
		return;
	}

	CDvmData *pCurrSelData = (CDvmData*)m_pBtnWidget->m_pChannelSelect_ComboBox->GetCurrSelObject();

	if (pCurrSelData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的遥控通道为空"));
		return;
	}

	long nValue = m_pBtnWidget->m_pOperationSelect_ComboBox->currentIndex();
	pCurrSelData->m_strValue.Format("%ld",nValue);

	CDvmDataset *pDataset = (CDvmDataset*)pCurrSelData->GetParent();
	CString strDatasetPath;
	if (pDataset != NULL) //闪退问题
	{
			QSttCommCfgDeviceWidget *pSttCommCfgDeviceWidget = (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
			pSttCommCfgDeviceWidget->m_pRunProcedureReceiveDlg = this;
		strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);
		g_theTestCntrFrame->m_pEngineClientWidget->WiriteEna_Sel(pCurrSelData,strDatasetPath);
	}

	long nHasError = 0;
	if (g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient != NULL)
	{
		if (g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient->GetRunProcedureRltValue(ATTRID_ERRINFO,nHasError))
		{
			if (nHasError)
			{
				m_pBtnWidget->m_pRemoteCtrlExe_Button->setEnabled(false);
				m_pBtnWidget->m_pRemoteCtrlCancel_Button->setEnabled(false);
			}
			else
			{
				m_pBtnWidget->m_pRemoteCtrlExe_Button->setEnabled(true);
	                        m_pBtnWidget->m_pRemoteCtrlCancel_Button->setEnabled(true);
			}
		}
	}
// 	m_pBtnWidget->m_pRemoteCtrlExe_Button->setEnabled(true);
// 	m_pBtnWidget->m_pRemoteCtrlCancel_Button->setEnabled(true);

	m_nRecordIndex ++;

	UpdateEventGrid();
}

void QSttMacroParaEditViewRemoteCtrl::slot_RemoteCtrlExe_PushButton_Clicked()
{
	if (g_theTestCntrFrame->m_pEngineClientWidget == NULL)
	{
		return;
	}

	CDvmData *pCurrSelData = (CDvmData*)m_pBtnWidget->m_pChannelSelect_ComboBox->GetCurrSelObject();

	if (pCurrSelData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的遥控通道为空"));
		return;
	}

	long nValue = m_pBtnWidget->m_pOperationSelect_ComboBox->currentIndex();
	pCurrSelData->m_strValue.Format("%ld",nValue);

	CDvmDataset *pDataset = (CDvmDataset*)pCurrSelData->GetParent();
	CString strDatasetPath;
	if (pDataset != NULL)//闪退问题
	{
		QSttCommCfgDeviceWidget *pSttCommCfgDeviceWidget = (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
		pSttCommCfgDeviceWidget->m_pRunProcedureReceiveDlg = this;
		strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);
		g_theTestCntrFrame->m_pEngineClientWidget->WiriteEna_Oper(pCurrSelData,strDatasetPath);
	}

	long nHasError = 0;
	if (g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient != NULL)
	{
		if (g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient->GetRunProcedureRltValue(ATTRID_ERRINFO,nHasError))
		{
			if (nHasError)
			{
				m_pBtnWidget->m_pRemoteCtrlExe_Button->setEnabled(true);
				m_pBtnWidget->m_pRemoteCtrlCancel_Button->setEnabled(true);
			}
			else
			{
				m_pBtnWidget->m_pRemoteCtrlExe_Button->setEnabled(false);
				m_pBtnWidget->m_pRemoteCtrlCancel_Button->setEnabled(false);
			}
		}
	}


 	//m_pBtnWidget->m_pRemoteCtrlExe_Button->setEnabled(false);
 	//m_pBtnWidget->m_pRemoteCtrlCancel_Button->setEnabled(false);
	m_nRecordIndex ++;
	UpdateEventGrid();
}

void QSttMacroParaEditViewRemoteCtrl::slot_RemoteCtrlCancel_PushButton_Clicked()
{
	if (g_theTestCntrFrame->m_pEngineClientWidget == NULL)
	{
		return;
	}

	CDvmData *pCurrSelData = (CDvmData*)m_pBtnWidget->m_pChannelSelect_ComboBox->GetCurrSelObject();

	if (pCurrSelData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前选择的遥控通道为空"));
		return;
	}

	long nValue = m_pBtnWidget->m_pOperationSelect_ComboBox->currentIndex();
	pCurrSelData->m_strValue.Format("%ld",nValue);

	CDvmDataset *pDataset = (CDvmDataset*)pCurrSelData->GetParent();
	CString strDatasetPath;
	if (pDataset != NULL) 
	{
		QSttCommCfgDeviceWidget *pSttCommCfgDeviceWidget = (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
		pSttCommCfgDeviceWidget->m_pRunProcedureReceiveDlg = this;
		strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);
		g_theTestCntrFrame->m_pEngineClientWidget->WiriteEna_Revoke(pCurrSelData,strDatasetPath);
	}

	long nHasError = 0;
	if (g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient != NULL)
	{
		if (g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient->GetRunProcedureRltValue(ATTRID_ERRINFO,nHasError))
		{
			if (nHasError)
			{
				m_pBtnWidget->m_pRemoteCtrlExe_Button->setEnabled(true);
				m_pBtnWidget->m_pRemoteCtrlCancel_Button->setEnabled(true);
			}
			else
			{
				m_pBtnWidget->m_pRemoteCtrlExe_Button->setEnabled(false);
				m_pBtnWidget->m_pRemoteCtrlCancel_Button->setEnabled(false);
			}
		}
	}
 	//m_pBtnWidget->m_pRemoteCtrlExe_Button->setEnabled(false);
 	//m_pBtnWidget->m_pRemoteCtrlCancel_Button->setEnabled(false);
}

void QSttMacroParaEditViewRemoteCtrl::slot_RemoteCtrlTimer()
{
	CExBaseList *pDataset = (CExBaseList*)m_pBtnWidget->m_pChannelSelect_ComboBox->GetCurrSelObject();

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

	if (m_nReadCount == 0)
	{
		CDvmDataset *pCurrDataset = (CDvmDataset*)m_pBtnWidget->m_pInterSelect_ComboBox->GetCurrSelObject();

		if (pCurrDataset)
		{
			g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient->RegisterReport_Cmd(pCurrDataset->m_strDataType);
		}
	}
	else
	{	
		CExBaseList oList;

		if (g_theTestCntrFrame->m_pEngineClientWidget->GetSoeReprt(&oList))
		{
			m_pBtnWidget->m_pRemoteCtrlGridSecond->AddShowSoeReports(&oList);
		}

		oList.RemoveAll();
//		CDvmDataset *pCurrDataset = (CDvmDataset*)m_pBtnWidget->m_pInterSelect_ComboBox->GetCurrSelObject();
		g_theTestCntrFrame->m_pEngineClientWidget->ReadSoe(/*pCurrDataset->m_strID*/"report$soe");
	}

	m_nReadCount++;

	if (m_nReadCount >= 1000000)//超过一定次数清零
	{
		m_nReadCount = 0;
	}
}

void QSttMacroParaEditViewRemoteCtrl::UpdateExeResult(long nErrorInfor)
{
	QSttCommCfgDeviceWidget *pSttCommCfgDeviceWidget = (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
	pSttCommCfgDeviceWidget->m_pRunProcedureReceiveDlg = NULL;
	m_pBtnWidget->m_pRemoteCtrlGridFirst->UpdateExcRlt(nErrorInfor);
}

void QSttMacroParaEditViewRemoteCtrl::UpdateEventGrid()
{
	if (m_pBtnWidget == NULL)
	{
		return;
	}
	CExBaseList *pDatasetInterSelect = (CExBaseList*)(m_pBtnWidget->m_pInterSelect_ComboBox->GetCurrSelObject());
	if (pDatasetInterSelect == NULL)
	{
		return;
	}
	CString strInterSelectName = pDatasetInterSelect->m_strName;
	CExBaseList *pChannelDataset = (CExBaseList*)(m_pBtnWidget->m_pChannelSelect_ComboBox->GetCurrSelObject());
	if (pChannelDataset == NULL)
	{
		return;
	}
	CString strChannelSelectName = pChannelDataset->m_strName;
	CString strOperationSelectName = m_pBtnWidget->m_pOperationSelect_ComboBox->currentText();
	EventStruct *pEventStruct = new EventStruct;
	pEventStruct->nIndex = m_nRecordIndex;
	pEventStruct->strInterSelectName = strInterSelectName;
	pEventStruct->strChannelSelectName = strChannelSelectName;
	pEventStruct->strOperationSelectName = strOperationSelectName;

	if(g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient->m_strProcedureID == CMDID_writeenasel)
	{
		pEventStruct->strActionName = _T("遥控预置");
	}
	else if(g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient->m_strProcedureID == CMDID_writeenaoper)
	{
		pEventStruct->strActionName = _T("遥控执行");
	}
	else if(g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient->m_strProcedureID == CMDID_writeenarevk)
	{
		pEventStruct->strActionName = _T("遥控撤销");
	}

	if (g_theTestCntrFrame->m_pEngineClientWidget->/*ConnectDevice()*/IsConnectSuccessful())
	{
		pEventStruct->strRecord = _T("---");//如果当前连接成功,需要等待操作结果
	}
	else
	{
		pEventStruct->strRecord = _T("失败");
	}

	CString strCurrTime;
#ifdef USE_Custom_CDateTime
	CDateTime::GetDateTime_YYYYMMDD_HHMMSSZZZ(strCurrTime);
#else
	QDateTime current_date_time = QDateTime::currentDateTime();
	strCurrTime = current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz");
#endif

	pEventStruct->strRecordtime = /*QDateTime::currentDateTime()*/strCurrTime;
	m_pBtnWidget->m_pRemoteCtrlGridFirst->UpdateTableData(pEventStruct,m_nRecordIndex);
}

void QSttMacroParaEditViewRemoteCtrl::UpdateDeviceModelRef()
{
	disconnect(m_pBtnWidget->m_pInterSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_InterSelectIndexChanged(int)));
	g_pTheSttTestApp->m_pDvmDevice = g_theTestCntrFrame->m_pEngineClientWidget->m_pDvmDevice;//遥控切换点表数据更新，间隔选择下拉框值刷新
	m_pBtnWidget->initInterSelectData();
	connect(m_pBtnWidget->m_pInterSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_InterSelectIndexChanged(int)));
}
