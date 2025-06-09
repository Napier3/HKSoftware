#include "stdafx.h"
#include "IotSmartTestCtrlMngr.h"


CIotSmartTestCtrlMngr::CIotSmartTestCtrlMngr()
{
	
}

CIotSmartTestCtrlMngr::~CIotSmartTestCtrlMngr()
{
	
}

/************************
自动测试主题：
"测试台SN/XML/AtsCmd/+";
"测试台SN/被测装置SN/XML/AtsCmd/FinishInputData";
"测试台SN/被测装置SN/XML/AtsState/InputData/Reply"
**************************/
void CIotSmartTestCtrlMngr::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{
	//根据主题
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	long nPathCnt = oToken.GetStringsCount();
	CString strTestID = oToken.GetToken(0);
	CString strCmd = oToken.GetToken(nPathCnt-1);

	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);

	if (strCmd == STT_CMD_TYPE_ATS_CreateTest)
	{//创建测试
		if (pSmartTestCtrl != NULL)
		{
			delete pSmartTestCtrl;
		}

		pSmartTestCtrl = new CIotSmartTestCtrl;
		pSmartTestCtrl->m_strID = strTestID;
		AddNewChild(pSmartTestCtrl);
	}
	else if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnMqttMsgRecieve:主题[%s]，pSmartTestCtrl == NULL。"),strTopic);
		return;
	}

	pSmartTestCtrl->OnMqttMsgRecieve(oToken,pBuf,nLen);
}

//启动后需要订阅自动测试主题
/***************************
订阅：
	测试台SN/XML/AtsCmd/CreateTest
发布：
	测试台SN/XML/AtsState/CreateTest/Reply
	测试台SN/XML/AtsState/EVENT/TestCreated

订阅：
	测试台SN/XML/AtsCmd/StartTest
发布：
	测试台SN/XML/AtsState/StartTest/Reply
	测试台SN/XML/AtsState/EVENT/TestStarted

订阅：
	测试台SN/XML/AtsCmd/StopTest
发布：
	测试台SN/XML/AtsState/StopTest/Reply
	测试台SN/XML/AtsState/EVENT/TestStoped

订阅：
	测试台SN/XML/AtsCmd/TestItem
发布：
	测试台SN/XML/AtsState/TestItem/Reply

订阅：
	测试台SN/XML/AtsCmd/TestFrom
发布：
	测试台SN/XML/AtsState/TestFrom/Reply

订阅：
	测试台SN/XML/AtsCmd/TestAllFailedItems
发布：
	测试台SN/XML/AtsState/TestAllFailedItems/Reply

订阅：
	测试台SN/XML/AtsCmd/SetItemState
发布：
	测试台SN/XML/AtsState/SetItemState/Reply

订阅：
	测试台SN/XML/AtsCmd/CreateDevice
发布：
	测试台SN/XML/AtsState/CreateDevice/Reply

订阅：
	测试台SN/XML/AtsCmd/ConfigDevice
发布：
	测试台SN/XML/AtsState/ConfigDevice/Reply

订阅：
	测试台SN/XML/AtsCmd/ConnectDevice
发布：
	测试台SN/XML/AtsState/ConnectDevice/Reply
	测试台SN/XML/AtsState/EVENT/EngineEvent/事件ID

订阅：
	测试台SN/XML/AtsCmd/CloseDevice
发布：
	测试台SN/XML/AtsState/CloseDevice/Reply
	测试台SN/XML/AtsState/EVENT/EngineEvent/DeviceClosed

订阅：
	测试台SN/XML/AtsCmd/ConfigEngine
发布：
	测试台SN/XML/AtsState/ConfigEngine/Reply

订阅：
	测试台SN/XML/AtsCmd/GetDataset
发布：
	测试台SN/XML/AtsState/GetDataset/Reply

订阅：
	测试台SN/XML/AtsCmd/SetDataset
发布：
	测试台SN/XML/AtsState/SetDataset/Reply

订阅：
	测试台SN/XML/AtsCmd/RunProcedure
发布：
	测试台SN/XML/AtsState/RunProcedure/Reply
	测试台SN/XML/AtsState/EVENT/EngineEvent/事件ID

订阅：
	测试台SN/XML/AtsCmd/QueryAtsFile
发布：
	测试台SN/XML/AtsState/QueryAtsFile/Reply

发布：
	测试台SN/被测装置SN/XML/AtsCmd/InputData
订阅：
	测试台SN/被测装置SN/XML/AtsState/InputData/Reply

订阅：
	测试台SN/被测装置SN/XML/AtsCmd/FinishInputData
发布：
	测试台SN/被测装置SN/XML/AtsState/FinishInputData/Reply

订阅：
	测试台SN/XML/AtsCmd/ExportReport
发布：
	测试台SN/XML/AtsState/ExportReport/Reply
	测试台SN/XML/AtsState/EVENT/ExportBegin|ExportFinish

订阅：
	测试台SN/XML/AtsCmd/QueryItems
发布：
	测试台SN/XML/AtsState/QueryItems/Reply

订阅：
	测试台SN/XML/AtsCmd/SetItemsReport
发布：
	测试台SN/XML/AtsState/SetItemsReport/Reply

订阅：
	测试台SN/XML/AtsCmd/ConfigTest
发布：
	测试台SN/XML/AtsState/ConfigTest/Reply

发布事件：
	测试台SN/被测装置SN/XML/AtsState/EVENT/ItemStateChanged
	测试台SN/被测装置SN/XML/AtsState/EVENT/Report
	测试台SN/XML/AtsState/EVENT/TestFinished
	测试台SN/XML/AtsState/EVENT/TestProcess
	测试台SN/XML/AtsState/EVENT/EngineEvent/事件ID
	测试台SN/XML/AtsState/EVENT/TestAppEvent/事件ID
***************************/
BOOL CIotSmartTestCtrlMngr::SubcribeMqttAtsTopic(int nQos)
{
	/*************************************
	需订阅自动测试主题：
	测试台SN/XML/AtsCmd/CreateTest
	测试台SN/XML/AtsCmd/StartTest
	测试台SN/XML/AtsCmd/StopTest
	测试台SN/XML/AtsCmd/TestItem
	测试台SN/XML/AtsCmd/TestFrom
	测试台SN/XML/AtsCmd/TestAllFailedItems
	测试台SN/XML/AtsCmd/SetItemState
	测试台SN/XML/AtsCmd/CreateDevice
	测试台SN/XML/AtsCmd/ConfigDevice
	测试台SN/XML/AtsCmd/ConnectDevice
	测试台SN/XML/AtsCmd/CloseDevice
	测试台SN/XML/AtsCmd/ConfigEngine
	测试台SN/XML/AtsCmd/GetDataset
	测试台SN/XML/AtsCmd/SetDataset
	测试台SN/XML/AtsCmd/RunProcedure
	测试台SN/XML/AtsCmd/QueryAtsFile
	测试台SN/XML/AtsCmd/ExportReport
	测试台SN/XML/AtsCmd/QueryItems
	测试台SN/XML/AtsCmd/SetItemsReport
	测试台SN/XML/AtsCmd/ConfigTest

	测试台SN/被测装置SN/XML/AtsCmd/FinishInputData
	测试台SN/被测装置SN/XML/AtsState/InputData/Reply
	*********************************/

	CSttMqttClientTool::SubscribeTopic(_T("+/+/AtsCmd/+"),nQos);
	CSttMqttClientTool::SubscribeTopic(_T("+/+/+/AtsCmd/FinishInputData"),nQos);
	CSttMqttClientTool::SubscribeTopic(_T("+/+/+/AtsState/InputData/Reply"),nQos);

	return TRUE;
}

//事件处理接口
long CIotSmartTestCtrlMngr::TES_OnItemStateChanged(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex
												, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnItemStateChanged:[%s]，pSmartTestCtrl == NULL。"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnItemStateChanged(nDeviceIndex, nReportIndex
													, nItemIndex,strItemID, strState);
}

long CIotSmartTestCtrlMngr::TES_OnTestFinished(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnTestFinished:[%s]，pSmartTestCtrl == NULL。"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnTestFinished(nDeviceIndex, nReportIndex);
}

long CIotSmartTestCtrlMngr::TES_OnTestStoped(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnTestStoped:[%s]，pSmartTestCtrl == NULL。"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnTestStoped(nDeviceIndex, nReportIndex);
}

long CIotSmartTestCtrlMngr::TES_OnExportRptFinished(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnExportRptFinished:[%s]，pSmartTestCtrl == NULL。"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnExportRptFinished(nDeviceIndex, nReportIndex);
}

long CIotSmartTestCtrlMngr::TES_OnTestAppEvent(LPCTSTR strTestID, LPCTSTR strEvent)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnTestAppEvent:[%s]，pSmartTestCtrl == NULL。"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnTestAppEvent(strEvent);
}

long CIotSmartTestCtrlMngr::TES_OnEngineEvent(LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnEngineEvent:[%s]，pSmartTestCtrl == NULL。"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnEngineEvent(nDeviceIndex,strEvent);
}

long CIotSmartTestCtrlMngr::TES_OnTestCreated(LPCTSTR strTestID)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnTestCreated:[%s]，pSmartTestCtrl == NULL。"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnTestCreated();
}

long CIotSmartTestCtrlMngr::TES_OnOpenGbrptFileFailed(LPCTSTR strTestID)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnOpenGbrptFileFailed:[%s]，pSmartTestCtrl == NULL。"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnOpenGbrptFileFailed();
}
