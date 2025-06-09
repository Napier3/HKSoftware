#include "stdafx.h"
#include "TestControlCommCmd.h"
#include "TestControl.h"

CTestControlCommCmd::CTestControlCommCmd()
{

}

CTestControlCommCmd::~CTestControlCommCmd()
{
	
}

//创建通讯规约引擎对象
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
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("没有注册规约引擎组件"));
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
			CLogPrint::LogString(LOGLEVEL_ERROR, _T("创建规约通讯设备失败"));
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

//规约组件消息处理函数
LRESULT CTestControlCommCmd::OnCommCommandMsg(WPARAM wParam, LPARAM lParam)
{
	//释放注册的过程消息
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
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("通讯过程中出现错误，测试终止"));
			StopTestExtern();
		}
		else
		{
			m_nCommCmdReCommTimes++;
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("通讯过程中出现错误，重新通讯第%d次，共%d次"), m_nCommCmdReCommTimes, GetCmmMaxRetryTimes());//pCmd->m_nMaxRetrytimes);
			m_pTCtrlWnd->SetTimer(TIMER_RETRY_CMM_CMD, pCmd->GetDelayBeforeRetry(), NULL);
		}

		return 0;
	}
	//加入异常处理??????????????????????????????????????????
	

	//做通讯完成后的延时判断
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
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("连接设备失败，测试终止"));
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
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("通讯过程中出现错误，测试终止"));
			StopTestExtern();
		}
		else
		{
			m_nCommCmdReCommTimes++;
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("通讯过程中出现错误，重新通讯第%d次，共%d次"), m_nCommCmdReCommTimes, GetCmmMaxRetryTimes());//pCmd->m_nMaxRetrytimes);
			m_pTCtrlWnd->SetTimer(TIMER_RETRY_CMM_CMD, pCmd->GetDelayBeforeRetry(), NULL);
		}

		break;

	default:
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("通讯引擎异常，测试终止"));
		StopTestExtern();
		break;
	}
	
	return 0;
}

PpEngine::IDevicePtr CTestControlCommCmd::GetDevicePtr(CCommCmd* pItem)
{
	if (pItem->IsUseDeviceEx())
	{
		//CLogPrint::LogString(LOGLEVEL_TRACE, _T("使用扩展通讯设备"));
		return m_oPpDeviceEx;
	}
	else
	{
		//CLogPrint::LogString(LOGLEVEL_TRACE, _T("使用当前通讯设备"));
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

//通讯命令测试
long CTestControlCommCmd::TestItemCommCmd(CCommCmd* pItem)
{
	//创建手动录入对话框
	if(m_pUICommCmdViewDlg == NULL)
	{
		m_pUICommCmdViewDlg = new CUICommCmdViewDlg();
		m_pUICommCmdViewDlg->Create(UI_GetCommCmdAttrDialogID(),m_pParentWnd);
	}

	m_pUICommCmdViewDlg->InitTestItem(pItem);

	CCmd *pCmd = pItem->GetCmd();

	if (pCmd->m_nCommTimes > 1)
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("项目[%s]第%d次测试，共%d次"), pItem->m_strName, m_nCommCmdTestTimes+1, GetMaxRepeatTimes(pCmd->m_nCommTimes)+1);
	}

	TestControlCommCmd_LogTime(9);
	m_pTCtrlWnd->m_pTestItem = pItem;

	//设置测试状态
	if (m_pCurrTestItem != pItem)
	{
		pItem->SetState(TEST_STATE_TESTING);
	}
	
	PpEngine::IDevicePtr oPpDevice = GetDevicePtr(pItem);

	//创建规约引擎设备连接，如果创建失败，则终止测试
	CreatePpEngineDevice();

	if (oPpDevice == NULL)
	{//执行第一个测试项目的测试，创建设备之后，等待设备联机成功，再执行此项目的测试
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

	//处理通讯命令的后续项目，例如：投退压板，每次只能投退一个压板
	ContinueTestCommCmd(pItem, bFinish);

	if (bFinish)
	{
		if (pCmd->GetDelayAfterCmd() > 0)
		{
			m_pUICommCmdViewDlg->ShowCommMessage(_T("通讯后延时"), TRUE);
			m_pTCtrlWnd->SetTimer(TIMER_DELAY_AFTER_CMM_CMD, pCmd->GetDelayAfterCmd(), NULL);
		}
		else
		{
			m_pUICommCmdViewDlg->ShowCommMessage(_T(""), FALSE);
			//如果不需要延时，则直接处理结束
			ExcuteCommCmdOnDelayAfterFinish(pItem);
		}
	}

	return 0;
}


//通讯
BOOL CTestControlCommCmd::HasCommCmdEngine()
{
	if (m_oPpDevice != NULL)
	{
		return TRUE;
	}

	if (m_pGuideBook->m_strPpTemplateFile.GetLength() < 5)
	{

	}

// 	CString m_strPpTemplateFile;      //规约模板文件
// 	CString m_strCommCmdConfigFile;		//通讯配置文件
// 	CString m_strDeviceModelFile;		//点表文件

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
//通讯命令处理

//执行项目的测试：通讯命令通讯前延时
void CTestControlCommCmd::ExcuteCommCmdOnDelayBefroeFinish(CCommCmd* pItem)
{
	if (m_pCurrTestItem == NULL)
	{
		//CLogPrint::LogString(LOGLEVEL_ERROR, L"系统测试错误：ExcuteCommCmdOnDelayBefroeFinish");
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
		//CLogPrint::LogString(LOGLEVEL_ERROR, L"系统测试错误：ExcuteCommCmdOnDelayBefroeFinish");
		return;
	}

	pCmd = pItem->GetCmd();
	//CGbCommCmd *pGbCmdCfg = (CGbCommCmd*)m_pGuideBook->m_oGbCommCmdConfig.FindByID(pItem->m_strCommCmdID);  //命令的类型
	//CCpu *pCpu = (CCpu*)pItem->GetCpu(pCmd->m_strDatasetPath);
	CDataSet *pDataset = pItem->GetDataset();
	BOOL bCanTest = TRUE;

// 	if (pGbCmdCfg == NULL)
// 	{
// 		bCanTest = FALSE;
// 		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("通讯命令项目【%s】定义的【%s】错误"), pItem->m_strName, pItem->m_strType);
// 	}

	if (pDataset == NULL)
	{
		bCanTest = FALSE;
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("通讯命令项目【%s】定义的参数【%s】错误"), pItem->m_strName, pCmd->m_strDatasetPath);
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
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("项目(%s)通讯引擎设备数据模型不存在"), pItem->m_strName);
		return StopTestExtern();
	}

	PpEngine::IDataSetPtr oDataset = oPpDevice.FindDataSet(pCmd->m_strDatasetPath);

	if (oDataset == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("项目【%s】通讯引擎设备数据集【%s】不存在"), pItem->m_strName, pCmd->m_strDatasetPath);
		return StopTestExtern();
	}

	CString strXmlDatas;

	try
	{
		pDvmDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXmlDatas);
		
		//设置定值数据
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

	//判断数据是否需要保存到本地设备数据模型
	if (!pCmd->IsCmdNeedWriteToLocal())
	{
		return 0;
	}

	CDataSet *pDataset = pItem->GetDataset();

	if (pDataset == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("项目【%s】设备数据模型【%s】不存在"), pItem->m_strName, pCmd->m_strDatasetPath);
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
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("项目【%s】通讯引擎设备数据模型不存在"), pItem->m_strName);
		return StopTestExtern();
	}

	PpEngine::IDataSetPtr oDataset = oPpDevice.FindDataSet(pCmd->m_strDatasetPath);

	if (oDataset == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("项目【%s】通讯引擎设备数据集【%s】不存在"), pItem->m_strName, pCmd->m_strDatasetPath);
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
	
	//判断数据是否需要保存到本地设备数据模型
	if (!pCmd->IsCmdNeedWriteToLocal())
	{
		return 0;
	}

	CDataSet *pDataset = pItem->GetDataset();

	if (pDataset == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("项目【%s】设备数据模型【%s】不存在"), pItem->m_strName, pCmd->m_strDatasetPath);
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
	//CGbCommCmd *pGbCmdCfg = (CGbCommCmd*)m_pGuideBook->m_oGbCommCmdConfig.FindByID(pItem->m_strCommCmdID);  //命令的类型

// 	if (pGbCmdCfg == NULL)
// 	{
// 		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("通讯命令项目【%s】定义的【%s】错误"), pItem->m_strName, pItem->m_strType);
// 		return 0;
// 	}

	CReport *pReport = NULL;
	CCmd *pCmd = pItem->GetCmd();

	if (pItem->IsWrite())
	{//写命令
		SaveCmdDatasToLocal(pItem);
		pReport = AddReport(pItem, pCmd->m_nCommTimes, m_nCommCmdTestTimes);
		pReport->AddReportValues(pItem->GetCmd());
	}
	else if (pItem->IsRead())
	{
		//从规约引擎读取数据
		//CShortDatas oDatas;
		CDvmDataset oDataset;
		ReadEngineDatas(pItem, &oDataset);

		if (pItem->IsCmdRptDataset() )
		{
			pReport = AddCommCmdReportDataEx(pItem, &oDataset);
		}
		else
		{
			//保存数据到本地
			SaveEngineDatasToLocal(pItem, &oDataset);

			//添加数据到报告
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

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("处理通讯命令【%s】结果"), pItem->m_strName);

	if (pValues == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, L"创建报告对象失败");
		return pReport;
	}

	//添加CommCmd定义的报告数据 
	pItem->AddCommCmdRptTags(pValues);

	//CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("处理通讯命令【%s】结果个数【%d】"), pItem->m_strName, pValues->GetCount());

	//添加设备数据模型的数据
	POS pos = pDatas->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)pDatas->GetNext(pos);
		CValue * pValue = pValues->AddNew(pData->m_strID, pData->m_strValue);
	}
	
	//如果是遥测，处理误差量
	AddAnalogErrorDatas(pItem, pValues);

	return pReport;
}

CReport* CTestControlCommCmd::AddCommCmdReportDataEx(CCommCmd* pItem, CDvmDataset *pDatas)
{
	CCmd *pCmd = pItem->GetCmd();
	CReport *pReport = AddReport(pItem, pCmd->m_nCommTimes, m_nCommCmdTestTimes);
	CValues *pValues = pReport->m_pValues;
	long nIndex = 0;

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("处理通讯命令【%s】结果"), pItem->m_strName);

	if (pValues == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, L"创建报告对象失败");
		return pReport;
	}

	//添加CommCmd定义的报告数据 
	pItem->AddCommCmdRptTags(pValues);

	pReport->m_pRptDvmDataset->AppendCloneEx(*pDatas);

	return pReport;
}

#define _use_xmatch



//填写通讯命令项目的报告数据
void CTestControlCommCmd::FillCommCmdItemReport(CCommCmd* pItem, CReport *pReport)
{
	CCmd *pCmd = pItem->GetCmd();

	if (pCmd->m_nCommTimes > 1)
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("项目【%s】报告填写第%d次，共%d次"), pItem->m_strName, m_nCommCmdTestTimes+1, GetMaxRepeatTimes(pCmd->m_nCommTimes)+1);
	}
	else
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("项目【%s】报告填写"), pItem->m_strName);
	}

	//执行结果判断脚本
	CString strSyntax;
	if (!pItem->RunResultScript(strSyntax))
	{
		//CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("执行结果判断脚本【%s】"), strSyntax);
	}
	else
	{
		////CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("RunResultScript【%s】成功"), pItem->m_strName);
	}

	long nCommCmdTestTimes = m_nCommCmdTestTimes;

	if (pCmd != NULL)
	{
		if (pCmd->m_nCommTimes > 1)
		{//重复通讯的次数大于1
			//if (pCmd->HasRepeatTestFinish(m_nCommCmdTestTimes))
			if (m_nCommCmdTestTimes >= GetMaxRepeatTimes(pCmd->m_nCommTimes))
			{//达到通讯次数，添加新的报告数据对象
				pReport = CreateCmmFinalReport(pItem);
				nCommCmdTestTimes = pCmd->m_nCommTimes;
			}
			else
			{//没有达到通讯次数，返回
#ifdef TCTRLCNTR_USE_WORD
				nCommCmdTestTimes = pCmd->m_nCommTimes;
				FillReport(pReport, nCommCmdTestTimes);
#endif			
				return;
			}
		}
	}

	//填写报告
#ifdef TCTRLCNTR_USE_WORD
	FillReport(pReport, nCommCmdTestTimes);
#endif

	if (m_pCurrSubTestItem == pItem)
	{//当前项目是项目
		//根据执行判断脚本的返回值设置项目状态
		pItem->InitStateByReport();
	}
}

long CTestControlCommCmd::GbDeleteAllNodeData(const CString &strID)
{
	PpEngine::IDevicePtr oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, L"通讯设备不存在");
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

//执行过程
void CTestControlCommCmd::RunProcedure(const CString &bstrProcedureID, const CString & bstrDatasetPath, WPARAM wParam, LPARAM lParam)
{
	PpEngine::IDevicePtr oPpDevice = GetDevicePtr();

	if (oPpDevice == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, L"RunProcedure:通讯引擎错误");
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
		CLogPrint::LogString(LOGLEVEL_ERROR, L"执行通讯过程:通讯引擎错误");
		return;
	}

	oPpDevice.UnRegisterProcedureWndMsg(_bstr_t(m_strProcedureID), (ULONG)m_pTCtrlWnd->m_hWnd, WM_COMM_COMMAND);
}

//最终报告的标识与其他报告的区别：报告表示以"CAL_"开头
//获取最后一个报告数据到前一个"CAL_"的数据之后的数据
//之后按照定义的计算方式进行数据的处理
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

	//获取需要计算的报告数据对象
	GetCmmReportsForCal(pItem, oReports);

	if (oReports.GetCount() < 2)
	{
		return pReportFinal;
	}

	//计算报告数据
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
