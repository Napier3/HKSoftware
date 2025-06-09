#ifndef _SmartTestRpcApi_h__
#define _SmartTestRpcApi_h__

#include "../../Module/DataMngr/DvmDataset.h"
#include "../../Module/CriticalSection/SynCriticalSection.h"

#include "TestControl/TestControlBase.h"

#ifndef _PSX_QT_LINUX_
#include "GbWzdAuto\GbWzdAutoConfig.h"
#endif

void RPC_API_GetAllTestItems(CTestControlBase *pTestControl, CDvmDataset &oDvmDataset);
void RPC_API_GetItem(CTestControlBase *pTestControl, CDvmDataset *pDvmDataset, CGbItemBase *pItem);
long RPC_API_GetTestControlIndex(CGbItemBase *pTestItem);
long RPC_API_GetTestControlIndex(CTestControlBase *pTestControl);
void RPC_API_GetItemState(CGbItemBase *pTestItem, CString &strTestID, long &nDeviceIndex, long &nReportIndex, long &nItemIndex, CString &strItemID, CString &strState);
void RPC_API_GetTestCtrlAttr(CTestControlBase *pTestControl, CString &strTestID, long &nDeviceIndex, long &nReportIndex);

#endif // _SmartTestRpcApi_h__

