
#include "SmartTestRpcApi.h"
#include "AtsRpc/SmartTestRpcMngr.h"
#include "XTestEventSink.h"
#include "TCtrlCntrConfig.h"
#include "../../Module/DataMngr/DataMngrTrans.h"
#include "../../SttStudio/Module/SttCmd/GuideBook/SttCmdGuideBookTransTool.h"
#include "TestControl/TCtrlCntrBaseApp.h"
// #include "../../SttStudio/Module/Engine/SttNativeTestEngine.h"

//////////////////////////////////////////////////////////////////////////
//
void atsrpc_OnGbrptOpened()
{
	//这个函数暂时没用到，实际调用的是TestCreated
	if (g_theSmartTestRpcMngr)
	{
		g_theSmartTestRpcMngr->OnGbrptOpened();
	}
}

void atsrpc_OnGbrptFileFailed(CTestControlBase* pTestControl)
{
	if (g_theSmartTestRpcMngr)
	{
		g_theSmartTestRpcMngr->OnOpenGbrptFailed();
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);

	CTestEventSinkMngr::XOnOpenGbrptFileFailed(strTestID);
}

void atsrpc_GetAllTestItems(CTestControlBase* pTestControl, CDvmDataset *pDvmDataset)
{
	RPC_API_GetAllTestItems(pTestControl, *pDvmDataset);
}

//2021-8-4  lijunqing  
void atsrpc_OnSmartTestCreated(const CString &strDeviceSN)
{
	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CTestEventSinkMngr::XOnTestCreated(strDeviceSN);
}


void atsrpc_OnSmartTestCreated(CDvmDataset *pDvmTasks)
{
	if (g_theSmartTestRpcMngr)
	{
		g_theSmartTestRpcMngr->OnSmartTestCreated(pDvmTasks);
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CTestEventSinkMngr::XOnTestCreated(pDvmTasks->m_strID);
}

void atsrpc_OnTestItemStateChanged(CGbItemBase *pTestItem)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("atsrpc_OnTestItemStateChanged>>>>%s>>>>%d"), pTestItem->m_strName, pTestItem->GetState());

	if (g_theSmartTestRpcMngr != NULL)
	{
		g_theSmartTestRpcMngr->OnTestItemStateChanged(pTestItem);
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CString strTestID, strItemID, strState;
	long nDeviceIndex = 0, nReportIndex = 0,  nItemIndex = 0;
	RPC_API_GetItemState(pTestItem, strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);

	CTestEventSinkMngr::XOnItemStateChanged(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);
}

void atsrpc_OnTestFinished(CTestControlBase *pTestControl, long nType)
{
	if (g_theSmartTestRpcMngr != NULL)
	{
		g_theSmartTestRpcMngr->OnTestFinished(pTestControl, nType);
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);

	if (nType == 1)
	{//_T("测试结束");
		CTestEventSinkMngr::XOnTestFinished(strTestID, nDeviceIndex, nReportIndex);
	}
	else
	{//_T("测试停止");
		CTestEventSinkMngr::XOnTestStoped(strTestID, nDeviceIndex, nReportIndex);
	}
}

void atsrpc_OnTestError(CTestControlBase *pTestControl)
{
	if (g_theSmartTestRpcMngr != NULL)
	{
		g_theSmartTestRpcMngr->OnTestError(pTestControl);
	}
}

void atsrpc_OnTestAppEvent(CTestControlBase *pTestControl, const CString &strEvent)
{
	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);

	CTestEventSinkMngr::XOnTestAppEvent(strTestID, strEvent);
}

void atsrpc_OnEngineEvent(CTestControlBase *pTestControl, const CString &strEvent)
{
	if (g_theSmartTestRpcMngr != NULL)
	{
		//如果连接设备失败，通过Rpc通知AtsBench，ShaoL 2019.04.26
		if (strEvent == EngineEvent_ConnectDeviceFailed)
		{
			g_theSmartTestRpcMngr->OnConnectDeviceFailed();
		}

		//shaolei 2019.06.24
		else if (strEvent == TEST_STATE_DESC_STOPED || strEvent == TEST_STATE_TEST_ERROR)
		{
			g_theSmartTestRpcMngr->OnTestStoped(pTestControl, strEvent);
		}
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);

	CTestEventSinkMngr::XOnEngineEvent(strTestID, nDeviceIndex, strEvent);
}

void atsrpc_OnTestStoped(CTestControlBase *pTestControl, const CString &strMsg)
{
	if (g_theSmartTestRpcMngr != NULL)
	{
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);
	CTestEventSinkMngr::XOnTestStoped(strTestID, nDeviceIndex, nReportIndex);
}

BOOL atsrpc_OnExportRptFinished(CTestControlBase *pTestControl)
{
	if (g_theSmartTestRpcMngr != NULL)
	{
		g_theSmartTestRpcMngr->OnExportRptFinished();
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return FALSE;
	}

	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);
	CTestEventSinkMngr::XOnExportRptFinished(strTestID, nDeviceIndex, nReportIndex);

	return TRUE;
}

BOOL atsrpc_IsSmartTestRpc()
{
	if (g_theTCtrlCntrApp->IsSmartTestRpc())
	{
		return TRUE;
	}

	if (g_theSmartTestRpcMngr != NULL)
	{
		return TRUE;
	}
	
	if (CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return TRUE;
	}

	//shaolei 20220419  自动测试服务模式下，也认为是RPC模式  需要给外部发送消息
	if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_nUseSttAtsSvr == 1/* && CSttNativeTestEngine::g_pNativeTestEngine != NULL*/)
	{
		return TRUE;
	}

	return FALSE;
}

void atsrpc_OnTestStarted(CTestControlBase *pTestControl, const CString &strMsg)
{
	if (g_theSmartTestRpcMngr != NULL)
	{
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);
	CTestEventSinkMngr::XOnTestStarted(strTestID, nDeviceIndex, nReportIndex);
}

void atsrpc_OnUploadRptFile(CTestControlBase *pTestControl)
{
	if (g_theSmartTestRpcMngr != NULL)
	{
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CString strTestID, strFiles;
	strTestID = pTestControl->m_pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);
	pTestControl->UploadRptFiles(strFiles);

	CTestEventSinkMngr::XOnUploadRptFile(strTestID, strFiles);
}

//2021-8-5  lijunqing
void atsrpc_OnTestProcess(CTestControlBase *pTestControl)
{
	CString strDeviceID, strTestID, strDeviceState;
	long nTotalItems = 0, nCurrItem = 0, nTotalTime = 0, nRemainTime = 0;
	long nEligibleItems = 0;
	long nInlegibleItems = 0;
	strDeviceID = pTestControl->m_pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);
	strDeviceState = pTestControl->m_pGuideBook->GetSummaryRslt();

	if (pTestControl->GetParent() != NULL)
	{
		//表示是从TestControl对象
		CTestControlBase *pMainTestControl = (CTestControlBase *)pTestControl->GetParent();
		pMainTestControl->m_pItemContainer->GetTestProcess(nTotalItems, nCurrItem, nTotalTime, nRemainTime);
		pMainTestControl->GetItemsCount(nTotalItems, nEligibleItems, nInlegibleItems);

		pMainTestControl->m_pItemContainer->m_nCurrFinishItem--;  //从TestControl对象的进度会累加到主TestControl。故此处还原
		nCurrItem--;
	}
	else
	{
		pTestControl->m_pItemContainer->GetTestProcess(nTotalItems, nCurrItem, nTotalTime, nRemainTime);
		pTestControl->GetItemsCount(nTotalItems, nEligibleItems, nInlegibleItems);
	}

	CTestEventSinkMngr::XOnTestProcess(strDeviceID, strTestID, nTotalItems, nCurrItem, nTotalTime, nRemainTime, strDeviceState);
}

//2021-8-6  shaolei
void atsrpc_OnExportRptEvent(CTestControlBase *pTestControl, const CString &strEvent)
{
	if (g_theSmartTestRpcMngr != NULL)
	{
	}

	if (!CTestEventSinkMngr::HasTestEventSinkMngr())
	{
		return;
	}

	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);
	CTestEventSinkMngr::XOnExportRptEvent(strTestID, strEvent, nDeviceIndex, nReportIndex);
}

void atsrpc_OnInputData(CGbItemBase *pItemBase)
{
	if (CTestEventSinkMngr::GetSinkMngr() == NULL)
	{
		return;
	}

	if (pItemBase->GetClassID() == GBCLASSID_SAFETY)
	{
		CSafety *pSafety = (CSafety *)pItemBase;
		CDataGroup oDataGroup;
		Append_Datas(&oDataGroup, pSafety->GetDatas(), FALSE);
		CExBaseList *pMsgs = pSafety->GetMsgs();//安全措施中，没有CMsgs类，这边返回的是一个CExBaseList链表，不能直接GetXml
		CSttMsgs oMsgs;
		MsgLists_to_SttMsgs(pMsgs, &oMsgs);

		CString strDatas, strMsgs;
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		oDataGroup.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strDatas);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		oMsgs.GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strMsgs);

		CTestEventSinkMngr::XOnInputData(strDatas, strMsgs);
	}
}