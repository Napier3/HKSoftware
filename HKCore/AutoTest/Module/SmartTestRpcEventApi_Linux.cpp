
#include "../../SttStudio/Module/SttAtsSvr/SttSmartTest.h"
//////////////////////////////////////////////////////////////////////////
//
void atsrpc_OnGbrptOpened()
{
//#ifndef _PSX_QT_LINUX_
//	//这个函数暂时没用到，实际调用的是TestCreated
//	if (g_theSmartTestRpcMngr)
//	{
//		g_theSmartTestRpcMngr->OnGbrptOpened();
//	}
//#endif
}

void atsrpc_OnGbrptFileFailed(CTestControlBase* pTestControl)
{
//#ifndef _PSX_QT_LINUX_
//	if (g_theSmartTestRpcMngr)
//	{
//		g_theSmartTestRpcMngr->OnOpenGbrptFailed();
//	}

//	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
//	{
//		return;
//	}

//	CString strTestID;
//	long nDeviceIndex = 0, nReportIndex = 0;
//	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);

//	CTestEventSinkMngr::XOnOpenGbrptFileFailed(strTestID);
//#endif
}

void atsrpc_GetAllTestItems(CTestControlBase* pTestControl, CDvmDataset *pDvmDataset)
{
//#ifndef _PSX_QT_LINUX_
//	RPC_API_GetAllTestItems(pTestControl, *pDvmDataset);
//#endif
}

void atsrpc_OnSmartTestCreated(CDvmDataset *pDvmTasks)
{
//#ifndef _PSX_QT_LINUX_
//	if (g_theSmartTestRpcMngr)
//	{
//		g_theSmartTestRpcMngr->OnSmartTestCreated(pDvmTasks);
//	}

//	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
//	{
//		return;
//	}

//	CTestEventSinkMngr::XOnTestCreated(pDvmTasks->m_strID);
//#endif
}

void atsrpc_OnTestItemStateChanged(CGbItemBase *pTestItem)
{
//#ifndef _PSX_QT_LINUX_
//	if (g_theSmartTestRpcMngr != NULL)
//	{
//		g_theSmartTestRpcMngr->OnTestItemStateChanged(pTestItem);
//	}

//	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
//	{
//		return;
//	}

//	CString strTestID, strItemID, strState;
//	long nDeviceIndex = 0, nReportIndex = 0,  nItemIndex = 0;
//	RPC_API_GetItemState(pTestItem, strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);

//	CTestEventSinkMngr::XOnItemStateChanged(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);
//#endif
}

void atsrpc_OnTestFinished(CTestControlBase *pTestControl, long nType)
{
//#ifndef _PSX_QT_LINUX_
//	if (g_theSmartTestRpcMngr != NULL)
//	{
//		g_theSmartTestRpcMngr->OnTestFinished(pTestControl, nType);
//	}

//	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
//	{
//		return;
//	}

//	CString strTestID;
//	long nDeviceIndex = 0, nReportIndex = 0;
//	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);

//	if (nType == 1)
//	{//_T("测试结束");
//		CTestEventSinkMngr::XOnTestFinished(strTestID, nDeviceIndex, nReportIndex);
//	}
//	else
//	{//_T("测试停止");
//		CTestEventSinkMngr::XOnTestStoped(strTestID, nDeviceIndex, nReportIndex);
//	}
//#endif
}

void atsrpc_OnTestError(CTestControlBase *pTestControl)
{

}

void atsrpc_OnTestAppEvent(CTestControlBase *pTestControl, const CString &strEvent)
{
    stt_Return_Ats_Event_Ex(pTestControl, SYS_STATE_EVENT_OnTestAppEvent, strEvent);
}

void atsrpc_OnEngineEvent(CTestControlBase *pTestControl, const CString &strEvent)
{
    stt_Return_Ats_Event_Ex(pTestControl, SYS_STATE_EVENT_OnEngineEvent, strEvent);
}

void atsrpc_OnTestStoped(CTestControlBase *pTestControl, const CString &strMsg)
{
//#ifndef _PSX_QT_LINUX_
//	if (g_theSmartTestRpcMngr != NULL)
//	{
//	}

//	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
//	{
//		return;
//	}

//	CString strTestID;
//	long nDeviceIndex = 0, nReportIndex = 0;
//	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);
//	CTestEventSinkMngr::XOnTestStoped(strTestID, nDeviceIndex, nReportIndex);
//#endif
}

BOOL atsrpc_OnExportRptFinished(CTestControlBase *pTestControl)
{
//#ifndef _PSX_QT_LINUX_
//	if (g_theSmartTestRpcMngr != NULL)
//	{
//		g_theSmartTestRpcMngr->OnExportRptFinished();
//	}

//	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
//	{
//		return FALSE;
//	}

//	CString strTestID;
//	long nDeviceIndex = 0, nReportIndex = 0;
//	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);
//	CTestEventSinkMngr::XOnExportRptFinished(strTestID, nDeviceIndex, nReportIndex);
//#endif

	return TRUE;
}

BOOL atsrpc_IsSmartTestRpc()
{
//#ifndef _PSX_QT_LINUX_
//	if (g_theSmartTestRpcMngr != NULL)
//	{
//		return TRUE;
//	}
	
//	if (CTestEventSinkMngr::HasTestEventSinkMngr())
//	{
//		return TRUE;
//	}
//#endif

	//Linux下，是通过19815起自动测试服务，默认为RPC模式
	return TRUE;
}

