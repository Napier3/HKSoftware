#include "SttMacroParaEditViewRemoteCtrl.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../SttGlobalDef.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../Controls/SttTabWidget.h"
#include "../Module/XLangResource_Native.h"
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

//	g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
}

QSttMacroParaEditViewRemoteCtrl::~QSttMacroParaEditViewRemoteCtrl()
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
// 	g_theTestCntrFrame->Ats_UpdateParameter();
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
// 	if (g_theTestCntrFrame->IsTestStarted())  //����״̬
// 	{
// 		SendUpdateParameter();
// 	}

	//g_theTestCntrFrame->UpdateVectorData();
	//g_theTestCntrFrame->UpdatePowerData();
	
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

	m_nReadCount = 0;//�л������Ҫ�����������������ö�Ӧ·��
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰѡ���ң��ͨ��Ϊ��"));
		return;
	}

	long nValue = m_pBtnWidget->m_pOperationSelect_ComboBox->currentIndex();
	pCurrSelData->m_strValue.Format("%ld",nValue);

	CDvmDataset *pDataset = (CDvmDataset*)pCurrSelData->GetParent();
	CString strDatasetPath;
	if (pDataset != NULL) //��������
	{
			QSttCommCfgDeviceWidget *pSttCommCfgDeviceWidget = (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
			pSttCommCfgDeviceWidget->m_pRunProcedureReceiveDlg = this;
		strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);
		g_theTestCntrFrame->m_pEngineClientWidget->WiriteEna_Sel(pCurrSelData,strDatasetPath);
	}

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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰѡ���ң��ͨ��Ϊ��"));
		return;
	}

	long nValue = m_pBtnWidget->m_pOperationSelect_ComboBox->currentIndex();
	pCurrSelData->m_strValue.Format("%ld",nValue);

	CDvmDataset *pDataset = (CDvmDataset*)pCurrSelData->GetParent();
	CString strDatasetPath;
	if (pDataset != NULL)//��������
	{
		QSttCommCfgDeviceWidget *pSttCommCfgDeviceWidget = (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
		pSttCommCfgDeviceWidget->m_pRunProcedureReceiveDlg = this;
		strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);
		g_theTestCntrFrame->m_pEngineClientWidget->WiriteEna_Oper(pCurrSelData,strDatasetPath);
	}
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰѡ���ң��ͨ��Ϊ��"));
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
	m_nRecordIndex ++;
	UpdateEventGrid();
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

	if (m_nReadCount >= 1000000)//����һ����������
	{
		m_nReadCount = 0;
	}
}

void QSttMacroParaEditViewRemoteCtrl::UpdateExeResult(QString strID,long nErrorInfor)
{
	QSttCommCfgDeviceWidget *pSttCommCfgDeviceWidget = (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
	pSttCommCfgDeviceWidget->m_pRunProcedureReceiveDlg = NULL;
	m_pBtnWidget->m_pRemoteCtrlGridFirst->UpdateExcRlt(nErrorInfor);


	if(strID == CMDID_writeenasel)
	{
		if (nErrorInfor)
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
	else if (strID == CMDID_writeenaoper || strID == CMDID_writeenarevk)
	{
		if (nErrorInfor)
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
		pEventStruct->strActionName = _T("ң��Ԥ��");
	}
	else if(g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient->m_strProcedureID == CMDID_writeenaoper)
	{
		pEventStruct->strActionName = _T("ң��ִ��");
	}
	else if(g_theTestCntrFrame->m_pEngineClientWidget->m_pPpDeviceClient->m_strProcedureID == CMDID_writeenarevk)
	{
		pEventStruct->strActionName = _T("ң�س���");
	}

	if (g_theTestCntrFrame->m_pEngineClientWidget->/*ConnectDevice()*/IsConnectSuccessful())
	{
		pEventStruct->strRecord = _T("---");//�����ǰ���ӳɹ�,��Ҫ�ȴ��������
	}
	else
	{
		pEventStruct->strRecord = _T("ʧ��");
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
	g_pTheSttTestApp->m_pDvmDevice = g_theTestCntrFrame->m_pEngineClientWidget->m_pDvmDevice;//ң���л�������ݸ��£����ѡ��������ֵˢ��
	m_pBtnWidget->initInterSelectData();
	connect(m_pBtnWidget->m_pInterSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_InterSelectIndexChanged(int)));
}