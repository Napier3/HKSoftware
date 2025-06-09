#include "stdafx.h"

#include "SmartTestRpcApi.h"

#ifndef _PSX_QT_LINUX_
#include "TestControl/TestControlMdvMgrp.h"
#endif


void RPC_API_GetTestItemState(CDvmData *pDataItem, CGbItemBase *pTestItem)
{
	if (pTestItem->GetClassID() == GBCLASSID_ITEMS)
	{
		return;   //分类节点，不返回测试结论信息  shaolei 2019.06.28
	}

	CDvmValue *pState = new CDvmValue();
	CString strState = Gb_GetTestStateByID(pTestItem->GetState());
	pState->m_strValue = strState;
	pDataItem->AddNewChild(pState);
}

void RPC_API_GetTestItemState(CTestControlBase *pTestControl, CDvmData *pDataItem, CGbItemBase *pTestItem)
{
	CGbItemBase *pFind = (CGbItemBase*)Gb_GetItem(pTestControl->m_pGuideBook, pTestItem);
	RPC_API_GetTestItemState(pDataItem, pFind);
}

void RPC_API_GetTestItemState_All(CTestControlBase *pTestControl, CDvmData *pDataItem, CGbItemBase *pTestItem)
{
	//主装置项目的状态
	RPC_API_GetTestItemState(pDataItem, pTestItem);

#ifndef _PSX_QT_LINUX_
	if (pTestControl->GetTestControlMode() != TESTCONTROLMODE_MDVMGRP)
	{//测单台
		return;
	}

	CMdvMgrpSpoDeviceMngrTestControl *pMngr = (CMdvMgrpSpoDeviceMngrTestControl*)pTestControl;
	POS pos = pMngr->m_listMdvMgrpTestControl.GetHeadPosition();
	CTestControlBase *pSub = NULL;

	while (pos != NULL)
	{
		pSub = (CTestControlBase *)pMngr->m_listMdvMgrpTestControl.GetNext(pos);
		RPC_API_GetTestItemState(pSub, pDataItem, pTestItem);
	}
#endif
}

void RPC_API_GetAllTestItems(CTestControlBase *pTestControl, CDvmDataset &oDvmDataset)
{
	pTestControl->CTestControlBase::InitGuideBook();
	pTestControl->QueryFrom(-1);

	CExBaseList listAllItems;

	pTestControl->m_pItemContainer->GetAllTestItems(listAllItems);

	POS pos = listAllItems.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	//CDvmData *pData = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = (CGbItemBase *)listAllItems.GetNext(pos);

		if (pItem->m_nSelect == 0 || pItem->m_nShow == 0 || pItem->m_nEnable == 0)
		{
			continue;
		}

		RPC_API_GetItem(pTestControl, &oDvmDataset, pItem);
	}

	listAllItems.RemoveAll();
}

void RPC_API_GetItem(CTestControlBase *pTestControl, CDvmDataset *pDvmDataset, CGbItemBase *pItem)
{
	CDvmData *pData = NULL;

	pData = new CDvmData();
	pData->m_strName = pItem->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
	pData->m_nIndex = pItem->m_nIndex;
	pData->m_strID = pItem->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
	pData->m_strDataType = pItem->GetXmlElementKey();
	pDvmDataset->AddNewChild(pData);
	RPC_API_GetTestItemState_All(pTestControl, pData, pItem);

	UINT nClassID = pItem->GetClassID();

	if (nClassID == GBCLASSID_MACROTEST)
	{
		POS pos = pItem->GetHeadPosition();
		CGbItemBase *pSubItem = NULL;

		while (pos != NULL)
		{
			pSubItem = (CGbItemBase *)pItem->GetNext(pos);
			UINT nSubClassID = pSubItem->GetClassID();

			if (nSubClassID != GBCLASSID_COMMCMD)
			{
				continue;
			}
			
			RPC_API_GetItem(pTestControl, pDvmDataset, pSubItem);
		}
	}
}

long RPC_API_GetTestControlIndex(CGbItemBase *pTestItem)
{
	CExBaseObject *pGuideBook = (CExBaseObject*)pTestItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CExBaseObject *pTestControl = (CExBaseObject*)pGuideBook->GetParent();

	return RPC_API_GetTestControlIndex((CTestControlBase *)pTestControl);
}

long RPC_API_GetTestControlIndex(CTestControlBase *pTestControl)
{
	return tctrl_GetTestControlIndex(pTestControl);
// 	CTestControlBase *pParent = (CTestControlBase*)pTestControl->GetParent();
// 	long nDeviceIndex = 0;
// 
// 	if (pParent == NULL)
// 	{
// 		nDeviceIndex = 0;
// 	}
// 	else
// 	{
// 		nDeviceIndex = pParent->FindTestControlIndex(pTestControl) + 1;
// 	}
// 
// 	return nDeviceIndex;
}

void RPC_API_GetItemState(CGbItemBase *pTestItem, CString &strTestID, long &nDeviceIndex, long &nReportIndex, long &nItemIndex, CString &strItemID, CString &strState)
{
	//2021-8-5  lijunqing
	CGuideBook *pGuideBook = (CGuideBook*)pTestItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	strTestID = pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);
	nDeviceIndex = RPC_API_GetTestControlIndex(pTestItem);
	nItemIndex = pTestItem->m_nIndex;

#ifdef ITEM_PATH_USE_NAME
	strItemID = pTestItem->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
#else
	strItemID = pTestItem->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
#endif
	strState = Gb_GetTestStateByID(pTestItem->GetState());
}

void RPC_API_GetTestCtrlAttr(CTestControlBase *pTestControl, CString &strTestID, long &nDeviceIndex, long &nReportIndex)
{
	//2021-8-5  lijunqing
	strTestID = pTestControl->m_pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);

	nDeviceIndex = RPC_API_GetTestControlIndex(pTestControl);
}

