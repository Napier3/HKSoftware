#include "stdafx.h"
#include "TestControlCommCmd.h"
#include "TestControl.h"

CTestControlCommCmd::CTestControlCommCmd()
{

}

CTestControlCommCmd::~CTestControlCommCmd()
{
	
}

//����ͨѶ��Լ�������
void CTestControlCommCmd::CreatePpEngineDevice()
{
	if (m_oPpDevice != NULL)
	{
		return;
	}

	CTCtrlCntrBaseApp *pApp = (CTCtrlCntrBaseApp*)AfxGetApp();
	PpEngine::IPpEnginePtr pEngine = pApp->GetPpEngine(m_pGuideBook->m_strPpEngineProgID);

	if (pEngine == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("û��ע���Լ�������"));
	}
	else
	{
// 		BSTR bstrPpTemplate = m_pGuideBook->m_strPpTemplateFile.AllocSysString();
// 		BSTR bstrDeviceModelFile = m_pGuideBook->m_strDeviceModelFile.AllocSysString();
	
		try
		{
			m_oPpDevice = pEngine.CreateDevice(m_pGuideBook->m_strPpTemplateFile, m_pGuideBook->m_strDeviceModelFile, _T(""));
		}
		catch (...)
		{
		}
	
		//::SysFreeString(bstrPpTemplate);
		//::SysFreeString(bstrDeviceModelFile);

		if (m_oPpDevice == NULL)
		{
			pApp->ReleasePpEngine();
			CLogPrint::LogString(LOGLEVEL_ERROR, _T("������ԼͨѶ�豸ʧ��"));
		}
		else
		{
			try
			{
				m_oPpDevice.AttachSystemWndMsg((ULONG)m_pTCtrlWnd->m_hWnd, WM_ENGINE_SYSTEM_MSG);
				m_oPpDevice.CommConfig(NULL);
				//Sleep (5000);
			}
			catch(...)
			{
			}
		}
	}
}

//��Լ�����Ϣ������
LRESULT CTestControlCommCmd::OnCommCommandMsg(WPARAM wParam, LPARAM lParam)
{
	//�ͷ�ע��Ĺ�����Ϣ
	UnRegisterProcedureMsg(wParam, lParam);

	CCommCmd *pCommCmd = NULL;

	if (m_pCurrSubTestItem != NULL)
	{
		if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			pCommCmd = (CCommCmd*)m_pCurrSubTestItem;
		}
	}
	else
	{
		if (m_pCurrTestItem != NULL)
		{
			if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
			{
				pCommCmd = (CCommCmd*)m_pCurrTestItem;
			}
		}
	}

	if (lParam == PpEngine::engineCommError)
	{
		CCmd *pCmd = pCommCmd->GetCmd();

		//if (m_nCommCmdReCommTimes >= pCmd->m_nMaxRetrytimes)
		if (m_nCommCmdReCommTimes >= GetCmmMaxRetryTimes())
		{
			m_nCommCmdReCommTimes = 0;
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("ͨѶ�����г��ִ��󣬲�����ֹ"));
			StopTestExtern();
		}
		else
		{
			m_nCommCmdReCommTimes++;
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("ͨѶ�����г��ִ�������ͨѶ��%d�Σ���%d��"), m_nCommCmdReCommTimes, GetCmmMaxRetryTimes());//pCmd->m_nMaxRetrytimes);
			m_pTCtrlWnd->SetTimer(TIMER_RETRY_CMM_CMD, pCmd->GetDelayBeforeRetry(), NULL);
		}

		return 0;
	}
	//�����쳣����??????????????????????????????????????????
	

	//��ͨѶ��ɺ����ʱ�ж�
	if (pCommCmd != NULL)
	{
		FinishTestItemCommCmd(pCommCmd);
	}

	return 0;
}

LRESULT CTestControlCommCmd::OnEngineSystemMessage(WPARAM wParam, LPARAM lParam)
{
	m_bPpDeviceConnectSucc = FALSE;

	if (m_pCurrTestItem == NULL)
	{
		//CLogPrint::LogString(LOGLEVEL_ERROR, L"OnEngineSystemMessage: m_pCurrTestItem == NULL");
		return 0;
	}

	BOOL bCommCmd = FALSE;

	if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		bCommCmd = TRUE;
	}
	else
	{
		if (m_pCurrSubTestItem != NULL)
		{
			if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
			{
				bCommCmd = TRUE;
			}
			else if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_SAFETY)
			{
				if (wParam == PpEngine::engineConnectDeviceSuccessful)
				{
					m_bPpDeviceConnectSucc = TRUE;
				}
			}
		}
	}

	if (m_pCurrTestItem != NULL)
	{
		if (m_pCurrTestItem->GetClassID() == GBCLASSID_SAFETY)
		{
			if (wParam == PpEngine::engineConnectDeviceSuccessful)
			{
				m_bPpDeviceConnectSucc = TRUE;
			}
		}
	}

	if (!bCommCmd)
	{
		//CLogPrint::LogString(LOGLEVEL_ERROR, L"OnEngineSystemMessage: not commcmd");
		return 0;
	}

	CCommCmd *pCmmCmd = (CCommCmd*)(m_pTCtrlWnd->m_pTestItem);
	CCmd *pCmd = pCmmCmd->GetCmd();

	switch (wParam)
	{
	case PpEngine::engineConnectDeviceFailed:
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("�����豸ʧ�ܣ�������ֹ"));
		StopTestExtern();
		break;

	case PpEngine::engineConnectDeviceSuccessful:
		m_bPpDeviceConnectSucc = TRUE;
		ExecuteTestItemCommCmd(pCmmCmd);
		break;

	case PpEngine::engineCommError:
		if (m_nCommCmdReCommTimes >= GetCmmMaxRetryTimes())
		//if (m_nCommCmdReCommTimes >= pCmd->m_nMaxRetrytimes)
		{
			m_nCommCmdReCommTimes = 0;
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("ͨѶ�����г��ִ��󣬲�����ֹ"));
			StopTestExtern();
		}
		else
		{
			m_nCommCmdReCommTimes++;
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("ͨѶ�����г��ִ�������ͨѶ��%d�Σ���%d��"), m_nCommCmdReCommTimes, GetCmmMaxRetryTimes());//pCmd->m_nMaxRetrytimes);
			m_pTCtrlWnd->SetTimer(TIMER_RETRY_CMM_CMD, pCmd->GetDelayBeforeRetry(), NULL);
		}

		break;

	default:
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("ͨѶ�����쳣��������ֹ"));
		StopTestExtern();
		break;
	}
	
	return 0;
}

PpEngine::IDevicePtr CTestControlCommCmd::GetDevicePtr(CCommCmd* pItem)
{
	if (pItem->IsUseDeviceEx())
	{
		//CLogPrint::LogString(LOGLEVEL_TRACE, _T("ʹ����չͨѶ�豸"));
		return m_oPpDeviceEx;
	}
	else
	{
		//CLogPrint::LogString(LOGLEVEL_TRACE, _T("ʹ�õ�ǰͨѶ�豸"));
		return m_oPpDevice;
	}
}

PpEngine::IDevicePtr CTestControlCommCmd::GetDevicePtr()
{
	if (m_pCurrTestItem== NULL)
	{
		return m_oPpDevice;
	}

	if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		return GetDevicePtr((CCommCmd*)m_pCurrTestItem);
	}

	if (m_pCurrSubTestItem== NULL)
	{
		return m_oPpDevice;
	}

	if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		return GetDevicePtr((CCommCmd*)m_pCurrSubTestItem);
	}

	return m_oPpDevice;
}

//ͨѶ�������
long CTestControlCommCmd::TestItemCommCmd(CCommCmd* pItem)
{
	//�����ֶ�¼��Ի���
	if(m_pUICommCmdViewDlg == NULL)
	{
		m_pUICommCmdViewDlg = new CUICommCmdViewDlg();
		m_pUICommCmdViewDlg->Create(UI_GetCommCmdAttrDialogID(),m_pParentWnd);
	}

	m_pUICommCmdViewDlg->InitTestItem(pItem);

	CCmd *pCmd = pItem->GetCmd();

	if (pCmd->m_nCommTimes > 1)
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("��Ŀ[%s]��%d�β��ԣ���%d��"), pItem->m_strName, m_nCommCmdTestTimes+1, GetMaxRepeatTimes(pCmd->m_nCommTimes)+1);
	}

	TestControlCommCmd_LogTime(9);
	m_pTCtrlWnd->m_pTestItem = pItem;

	//���ò���״̬
	if (m_pCurrTestItem != pItem)
	{
		pItem->SetState(TEST_STATE_TESTING);
	}
	
	PpEngine::IDevicePtr oPpDevice = GetDevicePtr(pItem);

	//������Լ�����豸���ӣ��������ʧ�ܣ�����ֹ����
	CreatePpEngineDevice();

	if (oPpDevice == NULL)
	{//ִ�е�һ��������Ŀ�Ĳ��ԣ������豸֮�󣬵ȴ��豸�����ɹ�����ִ�д���Ŀ�Ĳ���
		return 0;
	}

	oPpDevice = GetDevicePtr(pItem);

	if (oPpDevice == NULL)
	{
		return StopTestExtern();
	}

	try
	{
		//if (oPpDevice.IsConnectSuccessful() && m_bPpDeviceConnectSucc)
		{
			ExecuteTestItemCommCmd(pItem);
		}
	}
	catch(...)
	{
	}

	TestControlCommCmd_LogTime(10);

	if (m_pCurrTestItem != pItem)
	{
		m_pTCtrlMsgRcv->OnCurrItemStateChanged(pItem, FALSE);
	}

	return 0;
}

long CTestControlCommCmd::FinishTestItemCommCmd(CCommCmd* pItem)
{
	if (pItem == NULL)
	{
		return 0;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		return 0;
	}

	CCmd *pCmd = pItem->GetCmd();
	BOOL bFinish = FALSE;

	//����ͨѶ����ĺ�����Ŀ�����磺Ͷ��ѹ�壬ÿ��ֻ��Ͷ��һ��ѹ��
	ContinueTestCommCmd(pItem, bFinish);

	if (bFinish)
	{
		if (pCmd->GetDelayAfterCmd() > 0)
		{
			m_pUICommCmdViewDlg->ShowCommMessage(_T("ͨѶ����ʱ"), TRUE);
			m_pTCtrlWnd->SetTimer(TIMER_DELAY_AFTER_CMM_CMD, pCmd->GetDelayAfterCmd(), NULL);
		}
		else
		{
			m_pUICommCmdViewDlg->ShowCommMessage(_T(""), FALSE);
			//�������Ҫ��ʱ����ֱ�Ӵ������
			ExcuteCommCmdOnDelayAfterFinish(pItem);
		}
	}

	return 0;
}


//ͨѶ
BOOL CTestControlCommCmd::HasCommCmdEngine()
{
	if (m_oPpDevice != NULL)
	{
		return TRUE;
	}

	if (m_pGuideBook->m_strPpTemplateFile.GetLength() < 5)
	{

	}

// 	CString m_strPpTemplateFile;      //��Լģ���ļ�
// 	CString m_strCommCmdConfigFile;		//ͨѶ�����ļ�
// 	CString m_strDeviceModelFile;		//����ļ�

	if (g_strPpEngineProgIDMms == m_pGuideBook->m_strPpEngineProgID)
	{
		return TRUE;
	}
	else
	{
		if (m_pGuideBook->m_strPpTemplateFile.GetLength() < 5)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//ͨѶ�����

//ִ����Ŀ�Ĳ��ԣ�ͨѶ����ͨѶǰ��ʱ
void CTestControlCommCmd::ExcuteCommCmdOnDelayBefroeFinish(CCommCmd* pItem)
{
	if (m_pCurrTestItem == NULL)
	{
		//CLogPrint::LogString(LOGLEVEL_ERROR, L"ϵͳ���Դ���ExcuteCommCmdOnDelayBefroeFinish");
		return;
	}

	CCmd *pCmd = NULL;

	if (pItem == NULL)
	{
		if (m_pCurrSubTestItem != NULL)
		{
			pItem = (CCommCmd*)m_pCurrSubTestItem;
		}
		else 
		{
			if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
			{
				pItem = (CCommCmd*)m_pCurrTestItem;
			}
		}
	}

	if (pItem == NULL)
	{
		//CLogPrint::LogString(LOGLEVEL_ERROR, L"ϵͳ���Դ���ExcuteCommCmdOnDelayBefroeFinish");
		return;
	}

	pCmd = pItem->GetCmd();
	//CGbCommCmd *pGbCmdCfg = (CGbCommCmd*)m_pGuideBook->m_oGbCommCmdConfig.FindByID(pItem->m_strCommCmdID);  //���������
	//CCpu *pCpu = (CCpu*)pItem->GetCpu(pCmd->m_strDatasetPath);
	CDataSet *pDataset = pItem->GetDataset();
	BOOL bCanTest = TRUE;

// 	if (pGbCmdCfg == NULL)
// 	{
// 		bCanTest = FALSE;
// 		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("ͨѶ������Ŀ��%s������ġ�%s������"), pItem->m_strName, pItem->m_strType);
// 	}

	if (pDataset == NULL)
	{
		bCanTest = FALSE;
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("ͨѶ������Ŀ��%s������Ĳ�����%s������"), pItem->m_strName, pCmd->m_strDatasetPath);
	}


	if (pItem->IsWrite())
	{
		if (!bCanTest)
		{
			StopTestExtern();
			return;
		}

		WriteDatasToEngine(pItem);
	}
	else if (pItem->IsRead())
	{
		//SaveCmdDatasToLocal(pItem);
	}
	else
	{
		
	}
	
	RunProcedure(pItem->m_strCommCmdID, pCmd->m_strDatasetPath, 0, 0);

}

long CTestControlCommCmd::WriteDatasToEngine(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	CDvmDataset *pDvmDataset = pItem->GetWriteDvmDataset();
	PpEngine::IDevicePtr oPpDevice = GetDevicePtr(pItem);

	Update_dsSetting_TimeData_ms(pDvmDataset);

	if (oPpDevice == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("��Ŀ(%s)ͨѶ�����豸����ģ�Ͳ�����"), pItem->m_strName);
		return StopTestExtern();
	}

	PpEngine::IDataSetPtr oDataset = oPpDevice.FindDataSet(pCmd->m_strDatasetPath);

	if (oDataset == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("��Ŀ��%s��ͨѶ�����豸���ݼ���%s��������"), pItem->m_strName, pCmd->m_strDatasetPath);
		return StopTestExtern();
	}

	CString strXmlDatas;

	try
	{
		pDvmDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXmlDatas);
		
		//���ö�ֵ����
		//oPpDevice->SetXmlDataEx(pCmd->m_strDatasetPath, strXmlDatas);
		oDataset.SetXmlData(strXmlDatas);
	}
	catch(...)
	{
	}

	delete pDvmDataset;

	return 0;
}

long CTestControlCommCmd::SaveCmdDatasToLocal(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();

	//�ж������Ƿ���Ҫ���浽�����豸����ģ��
	if (!pCmd->IsCmdNeedWriteToLocal())
	{
		return 0;
	}

	CDataSet *pDataset = pItem->GetDataset();

	if (pDataset == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("��Ŀ��%s���豸����ģ�͡�%s��������"), pItem->m_strName, pCmd->m_strDatasetPath);
		//return StopTestExtern();
		return 0;
	}

	pDataset->SetDataSetValue(pCmd);
	Update_dsSetting_TimeData_s(pDataset);

	return 0;
}

long CTestControlCommCmd::ReadEngineDatas(CCommCmd* pItem, CDvmDataset *pShortDatas)
{
	ASSERT (pShortDatas != NULL);
	PpEngine::IDevicePtr oPpDevice = GetDevicePtr(pItem);
	CCmd *pCmd = pItem->GetCmd();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("��Ŀ��%s��ͨѶ�����豸����ģ�Ͳ�����"), pItem->m_strName);
		return StopTestExtern();
	}

	PpEngine::IDataSetPtr oDataset = oPpDevice.FindDataSet(pCmd->m_strDatasetPath);

	if (oDataset == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("��Ŀ��%s��ͨѶ�����豸���ݼ���%s��������"), pItem->m_strName, pCmd->m_strDatasetPath);
		return StopTestExtern();
	}


	try
	{
		_bstr_t strXmlDatas;
		strXmlDatas = oDataset.GetXmlData();
		pShortDatas->SetXml(strXmlDatas,CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
	}
	catch(...)
	{
	}

	return 0;
}

long CTestControlCommCmd::SaveEngineDatasToLocal(CCommCmd* pItem, CDvmDataset *pShortDatas)
{
	ASSERT (pShortDatas != NULL);
	CCmd *pCmd = pItem->GetCmd();
	
	//�ж������Ƿ���Ҫ���浽�����豸����ģ��
	if (!pCmd->IsCmdNeedWriteToLocal())
	{
		return 0;
	}

	CDataSet *pDataset = pItem->GetDataset();

	if (pDataset == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("��Ŀ��%s���豸����ģ�͡�%s��������"), pItem->m_strName, pCmd->m_strDatasetPath);
		//return StopTestExtern();
		return 0;
	}

	pDataset->InitValueByDvmDataset(pShortDatas);
	
	return 0;
}

const BSTR CTestControlCommCmd::g_strDataInterfaceID_CPU = L"pnCpuIndex";
const BSTR CTestControlCommCmd::g_strDataInterfaceID_Group = L"pnGroupIndex";
const BSTR CTestControlCommCmd::g_strDataInterfaceID_Index = L"pnItemIndex";
const BSTR CTestControlCommCmd::g_strDataInterfaceID_Value = L"pnValue";


long CTestControlCommCmd::ProcessFinishCommCmd(CCommCmd* pItem)
{
	//CGbCommCmd *pGbCmdCfg = (CGbCommCmd*)m_pGuideBook->m_oGbCommCmdConfig.FindByID(pItem->m_strCommCmdID);  //���������

// 	if (pGbCmdCfg == NULL)
// 	{
// 		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("ͨѶ������Ŀ��%s������ġ�%s������"), pItem->m_strName, pItem->m_strType);
// 		return 0;
// 	}

	CReport *pReport = NULL;
	CCmd *pCmd = pItem->GetCmd();

	if (pItem->IsWrite())
	{//д����
		SaveCmdDatasToLocal(pItem);
		pReport = AddReport(pItem, pCmd->m_nCommTimes, m_nCommCmdTestTimes);
		pReport->AddReportValues(pItem->GetCmd());
	}
	else if (pItem->IsRead())
	{
		//�ӹ�Լ�����ȡ����
		//CShortDatas oDatas;
		CDvmDataset oDataset;
		ReadEngineDatas(pItem, &oDataset);

		if (pItem->IsCmdRptDataset() )
		{
			pReport = AddCommCmdReportDataEx(pItem, &oDataset);
		}
		else
		{
			//�������ݵ�����
			SaveEngineDatasToLocal(pItem, &oDataset);

			//������ݵ�����
			pReport = AddCommCmdReportData(pItem, &oDataset);
		}
	}
	else
	{
		pReport = AddReport(pItem, pCmd->m_nCommTimes, m_nCommCmdTestTimes);
	}

	FillCommCmdItemReport(pItem, pReport);

	pItem->InitStateByReport();
	m_pTCtrlMsgRcv->OnCurrItemStateChanged(pItem, FALSE);

	return 0;
}

void CTestControlCommCmd::AddAnalogErrorDatas(CCommCmd* pItem, CValues * pValues)
{
	CCmd *pCmd = pItem->GetCmd();

	if (!pCmd->IsCmdDataset(DSID_dsAin))
	{
		return;
	}

	CDataSet *pDataset = pItem->GetDataset();

	if (pDataset == NULL)
	{
		return;
	}
	
	POS pos = pDataset->GetHeadPosition();
	CDataObj *pAnalog = NULL;
	CValue * pValue = NULL;

	while (pos != NULL)
	{
		pAnalog = (CDataObj*)pDataset->GetNext(pos);

		if (pAnalog->m_strDataTypeID == g_strAnalogType_Error)
		{
			pValue = pValues->AddNew(pAnalog->m_strID, L"0");
		}
	}
}

CReport* CTestControlCommCmd::AddCommCmdReportData(CCommCmd* pItem, CDvmDataset *pDatas)
{
	CCmd *pCmd = pItem->GetCmd();
	CReport *pReport = AddReport(pItem, pCmd->m_nCommTimes, m_nCommCmdTestTimes);
	CValues * pValues = pReport->m_pValues;
	long nIndex = 0;

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("����ͨѶ���%s�����"), pItem->m_strName);

	if (pValues == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, L"�����������ʧ��");
		return pReport;
	}

	//���CommCmd����ı������� 
	pItem->AddCommCmdRptTags(pValues);

	//CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("����ͨѶ���%s�����������%d��"), pItem->m_strName, pValues->GetCount());

	//����豸����ģ�͵�����
	POS pos = pDatas->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)pDatas->GetNext(pos);
		CValue * pValue = pValues->AddNew(pData->m_strID, pData->m_strValue);
	}
	
	//�����ң�⣬���������
	AddAnalogErrorDatas(pItem, pValues);

	return pReport;
}

CReport* CTestControlCommCmd::AddCommCmdReportDataEx(CCommCmd* pItem, CDvmDataset *pDatas)
{
	CCmd *pCmd = pItem->GetCmd();
	CReport *pReport = AddReport(pItem, pCmd->m_nCommTimes, m_nCommCmdTestTimes);
	CValues *pValues = pReport->m_pValues;
	long nIndex = 0;

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("����ͨѶ���%s�����"), pItem->m_strName);

	if (pValues == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, L"�����������ʧ��");
		return pReport;
	}

	//���CommCmd����ı������� 
	pItem->AddCommCmdRptTags(pValues);

	pReport->m_pRptDvmDataset->AppendCloneEx(*pDatas);

	return pReport;
}

#define _use_xmatch



//��дͨѶ������Ŀ�ı�������
void CTestControlCommCmd::FillCommCmdItemReport(CCommCmd* pItem, CReport *pReport)
{
	CCmd *pCmd = pItem->GetCmd();

	if (pCmd->m_nCommTimes > 1)
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("��Ŀ��%s��������д��%d�Σ���%d��"), pItem->m_strName, m_nCommCmdTestTimes+1, GetMaxRepeatTimes(pCmd->m_nCommTimes)+1);
	}
	else
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("��Ŀ��%s��������д"), pItem->m_strName);
	}

	//ִ�н���жϽű�
	CString strSyntax;
	if (!pItem->RunResultScript(strSyntax))
	{
		//CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("ִ�н���жϽű���%s��"), strSyntax);
	}
	else
	{
		////CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("RunResultScript��%s���ɹ�"), pItem->m_strName);
	}

	long nCommCmdTestTimes = m_nCommCmdTestTimes;

	if (pCmd != NULL)
	{
		if (pCmd->m_nCommTimes > 1)
		{//�ظ�ͨѶ�Ĵ�������1
			//if (pCmd->HasRepeatTestFinish(m_nCommCmdTestTimes))
			if (m_nCommCmdTestTimes >= GetMaxRepeatTimes(pCmd->m_nCommTimes))
			{//�ﵽͨѶ����������µı������ݶ���
				pReport = CreateCmmFinalReport(pItem);
				nCommCmdTestTimes = pCmd->m_nCommTimes;
			}
			else
			{//û�дﵽͨѶ����������
#ifdef TCTRLCNTR_USE_WORD
				nCommCmdTestTimes = pCmd->m_nCommTimes;
				FillReport(pReport, nCommCmdTestTimes);
#endif			
				return;
			}
		}
	}

	//��д����
#ifdef TCTRLCNTR_USE_WORD
	FillReport(pReport, nCommCmdTestTimes);
#endif

	if (m_pCurrSubTestItem == pItem)
	{//��ǰ��Ŀ����Ŀ
		//����ִ���жϽű��ķ���ֵ������Ŀ״̬
		pItem->InitStateByReport();
	}
}

long CTestControlCommCmd::GbDeleteAllNodeData(const CString &strID)
{
	PpEngine::IDevicePtr oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, L"ͨѶ�豸������");
		return StopTestExtern();
	}

	PpEngine::IDataSetPtr oDataset = NULL;

	try
	{
		oDataset = oPpDevice.FindDataSet(strID);

		if(oDataset != NULL)
		{
			oDataset.DeleteAllDatas();
		}
	}
	catch(...){}

	return 0;
}

//ִ�й���
void CTestControlCommCmd::RunProcedure(const CString &bstrProcedureID, const CString & bstrDatasetPath, WPARAM wParam, LPARAM lParam)
{
	PpEngine::IDevicePtr oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, L"RunProcedure:ͨѶ�������");
		return;
	}

	//CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("TestControlCommCmd::RunProcedure:%s"), (CString(bstrProcedureID)));
	oPpDevice.RegisterProcedureWndMsg(bstrProcedureID, (ULONG)m_pTCtrlWnd->m_hWnd, WM_COMM_COMMAND);
	m_strProcedureID = bstrProcedureID;
	m_strDatasetPath = bstrDatasetPath;
	oPpDevice.RunProcedure(bstrProcedureID, bstrDatasetPath);
}

void CTestControlCommCmd::UnRegisterProcedureMsg(WPARAM wParam, LPARAM lParam)
{
	PpEngine::IDevicePtr oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, L"ִ��ͨѶ����:ͨѶ�������");
		return;
	}

	oPpDevice.UnRegisterProcedureWndMsg(_bstr_t(m_strProcedureID), (ULONG)m_pTCtrlWnd->m_hWnd, WM_COMM_COMMAND);
}

//���ձ���ı�ʶ��������������𣺱����ʾ��"CAL_"��ͷ
//��ȡ���һ���������ݵ�ǰһ��"CAL_"������֮�������
//֮���ն���ļ��㷽ʽ�������ݵĴ���
CReport* CTestControlCommCmd::CreateCmmFinalReport(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	long nCalMode = pCmd->GetCalMode();
	CReport *pReportFinal = NULL;

	if (nCalMode == TEST_CALMODE_NONE)
	{
		pReportFinal = pItem->GetCurrReport();
		return pReportFinal;
	}

	CExBaseList oReports;

	//��ȡ��Ҫ����ı������ݶ���
	GetCmmReportsForCal(pItem, oReports);

	if (oReports.GetCount() < 2)
	{
		return pReportFinal;
	}

	//���㱨������
	pReportFinal = AddReport(pItem, pCmd->m_nCommTimes, pCmd->m_nCommTimes);
	pReportFinal->SetCalReport();

	switch (nCalMode)
	{
	case TEST_CALMODE_AVERAGE:
		CmmCalReports_Average(pReportFinal, oReports);
		break;

	case TEST_CALMODE_MAX:
		CmmCalReports_Max(pReportFinal, oReports);
		break;

	case TEST_CALMODE_MIN:
		CmmCalReports_Min(pReportFinal, oReports);
		break;

	default:
		break;
	}

	oReports.RemoveAll();

	return pReportFinal;
}
