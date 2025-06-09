#ifndef _SmartTestRpcEventApi_h__
#define _SmartTestRpcEventApi_h__


#include "TestControl/TestControlBase.h"

//2021-8-4  lijunqing  
void atsrpc_OnSmartTestCreated(const CString &strDeviceSN);

void atsrpc_OnSmartTestCreated(CDvmDataset *pDvmTasks);
void atsrpc_OnTestItemStateChanged(CGbItemBase *pTestItem);
void atsrpc_OnTestFinished(CTestControlBase *pTestControl, long nType);
void atsrpc_OnTestError(CTestControlBase *pTestControl);
void atsrpc_OnTestAppEvent(CTestControlBase *pTestControl, const CString &strEvent);
void atsrpc_OnEngineEvent(CTestControlBase *pTestControl, const CString &strEvent);
void atsrpc_OnTestStoped(CTestControlBase *pTestControl, const CString &strMsg);
BOOL atsrpc_OnExportRptFinished(CTestControlBase *pTestControl);
BOOL atsrpc_IsSmartTestRpc();
void atsrpc_OnGbrptOpened();
void atsrpc_OnGbrptFileFailed(CTestControlBase* pTestControl);
void atsrpc_GetAllTestItems(CTestControlBase* pTestControl, CDvmDataset *pDvmDataset);
void atsrpc_OnTestStarted(CTestControlBase *pTestControl, const CString &strMsg);
void atsrpc_OnUploadRptFile(CTestControlBase *pTestControl);

//2021-8-5  lijunqing
void atsrpc_OnTestProcess(CTestControlBase *pTestControl);

//2021-8-6 shaolei
void atsrpc_OnExportRptEvent(CTestControlBase *pTestControl, const CString &strEvent);

//shaolei 20220611
void atsrpc_OnInputData(CGbItemBase *pItemBase);

#endif // _SmartTestRpcApi_h__

