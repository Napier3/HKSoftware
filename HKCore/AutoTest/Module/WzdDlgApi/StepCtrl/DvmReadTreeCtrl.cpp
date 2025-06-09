#include "stdafx.h"
#include "DvmReadTreeCtrl.h"
#include "../WzdDlgDef.h"
#include "../MmsApi/MmsGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CDvmReadTreeCtrl::CDvmReadTreeCtrl()
{
	m_pStartAddr_ACSI_CTRL = NULL;
	m_pStartAddrDEVICE_NODE = NULL;
	m_pStartAddrACSI_NODE = NULL;
	m_pStartAddr_SOERPT = NULL;
	m_pStartAddr_RLYSOERPT = NULL;

}

CDvmReadTreeCtrl::~CDvmReadTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CDvmReadTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDvmReadTreeCtrl::OnTvnSelchanged)
	ON_NOTIFY_REFLECT(NM_CLICK, &CDvmReadTreeCtrl::OnNMClick)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CDvmReadTreeCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CDvmReadTreeCtrl::OnMmsSelchanged(HTREEITEM hItem)
{
	DWORD dwItemData = 0;
	dwItemData = GetItemData(hItem);
	GetParent()->PostMessage(WM_MMS_NODE_SELCHANGED, dwItemData, dwItemData);
}

void CDvmReadTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
	HTREEITEM hSel = GetSelectedItem();

	if (hSel != NULL )
	{
		OnMmsSelchanged(hSel);
	}

	*pResult = 0;
}

void CDvmReadTreeCtrl::UpdateDeviceIP_Desc(long nDeviceIndex)
{
	ASSERT (m_pStartAddrDEVICE_NODE != NULL);
	struct in_addr	addr;
	CString strText = "";
	CString strIP1 = "";
	CString strIP2 = "";
	DWORD dwNum = -1;
	LD_NODE * pLD = NULL;
	HTREEITEM hItem = NULL;

	DEVICE_NODE *pDEVICE_NODE = (DEVICE_NODE*)(m_pStartAddrDEVICE_NODE + nDeviceIndex*sizeof(DEVICE_NODE));

	addr.S_un.S_addr = pDEVICE_NODE->IP1;
	strIP1 = inet_ntoa(addr);
	addr.S_un.S_addr = pDEVICE_NODE->IP2;
	strIP2 = inet_ntoa(addr);

	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	CString strName(pDevice->devName);

	if (strName.IsEmpty())
	{
		strName = pDEVICE_NODE->DeviceModel;
	}

	if (strName.IsEmpty())
	{
		strName = _T("device:");
	}

	strText.Format(_T("%s(%s)"), strName, strIP1);
	hItem = (HTREEITEM)pDevice->dwTreeItemData;
	ASSERT(hItem);
	SetItemText(hItem,strText);
}

long CDvmReadTreeCtrl::FindDevIndexByIP(const CString &strIP)
{
	long nDevIndex = -1;

	if (strIP.IsEmpty())
	{
		return nDevIndex;
	}

	ASSERT (m_pStartAddrDEVICE_NODE != NULL);
	DEVICE_NODE * pDEVICE_NODE = NULL;
	int nSize = *((int*)pmemOBJTree);
	struct in_addr	addr;
	CString strIP1 = "";

	if (nSize>MAX_DEVICE)
	{
		nSize = MAX_DEVICE;
	} 

	for (int i=0; i<nSize; i++)
	{
		pDEVICE_NODE = (DEVICE_NODE*)(m_pStartAddrDEVICE_NODE + i*sizeof(DEVICE_NODE));

		if (!pDEVICE_NODE)
			continue;

		addr.S_un.S_addr = pDEVICE_NODE->IP1;
		strIP1 = inet_ntoa(addr);

		if (strIP1 == strIP)
		{
			nDevIndex = i;
			break;
		}

	}

	return nDevIndex;
}

void CDvmReadTreeCtrl::InsertDevice(long nDeviceIndex, HTREEITEM hParent)
{
	ASSERT (m_pStartAddrDEVICE_NODE != NULL);
	struct in_addr	addr;
	CString strText = "";
	CString strIP1 = "";
	CString strIP2 = "";
	DWORD dwNum = -1;
	LD_NODE * pLD = NULL;
	HTREEITEM hItem = NULL;

	DEVICE_NODE *pDEVICE_NODE = (DEVICE_NODE*)(m_pStartAddrDEVICE_NODE + nDeviceIndex*sizeof(DEVICE_NODE));

	addr.S_un.S_addr = pDEVICE_NODE->IP1;
	strIP1 = inet_ntoa(addr);
	addr.S_un.S_addr = pDEVICE_NODE->IP2;
	strIP2 = inet_ntoa(addr);

	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	CString strName(pDevice->devName);

	if (strName.IsEmpty())
	{
		strName = pDEVICE_NODE->DeviceModel;
	}

	if (strName.IsEmpty())
	{
		strName = _T("device:");
	}

	//strText.Format(_T("%s(%s)"), strName, strIP1);
	strText.Format(_T("%s"), strName);

	if (pDevice->dwTreeItemData != 0)
	{
		UpdateDeviceState(pDevice);
		hItem = (HTREEITEM)pDevice->dwTreeItemData;
		HTREEITEM hChild = GetChildItem(hItem);
		HTREEITEM hNext = NULL;

		while (hChild != NULL)
		{
			hNext = GetNextSiblingItem(hChild);
			DeleteItem(hChild);
			hChild = hNext;
		}
	}
	else
	{
		if (pDevice->bConnect)
		{
			hItem = InsertItem(strText, 1, 1, hParent, NULL);
		}
		else
		{
			hItem = InsertItem(strText, 0, 0, hParent, NULL);
		}

		dwNum = mms_MakeDWORD(TREEITEM_TYPE_DEVICE, nDeviceIndex);
		SetItemData(hItem, dwNum);
		pDevice->dwTreeItemData = (DWORD)hItem;
	}


	for (int nLDIndex=0;nLDIndex<pDevice->numLD;nLDIndex++)
	{
		pLD = &pDevice->LD[nLDIndex];
		InsertLDevice(nDeviceIndex, nLDIndex, hItem);
	}

	if (pDevice->numLD == 0)
	{
		return;
	}

	//录波文件
	dwNum = mms_MakeDWORD(TREEITEM_TYPE_FILEDIR, nDeviceIndex);
	HTREEITEM hCurr = InsertItem(_T("录波文件"), 5, 5, hItem, NULL);
	SetItemData(hCurr, dwNum);

	Expand(hItem, TVE_EXPAND);
}

void CDvmReadTreeCtrl::InsertLDevice(long nDeviceIndex, long nLDIndex, HTREEITEM hParent)
{
	HTREEITEM hLdItem = NULL;
	HTREEITEM hData = NULL;
	CString strText = "";
	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
	strText.Format(_T("%s[%s]"),pLD->LDName,pLD->LDDesc);
	DWORD dwNum = -1;

	hLdItem = InsertItem(strText, 2, 2, hParent);
	pLD->dwTreeItemData = (DWORD)hLdItem;

	dwNum = mms_MakeDWORD(TREEITEM_TYPE_LDEVICE, nDeviceIndex, nLDIndex);
	SetItemData(hLdItem,dwNum);

	for (long nDsIndex=0; nDsIndex < pLD->numDaSet; nDsIndex++)
	{
		LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
		strText.Format(_T("%s[%s]"),pLD_INFO->DaSetDesc,pLD_INFO->DataSetID);

		if (pLD_INFO->curRcbIndex > 0)
		{
			hData = InsertItem(strText, 4, 4, hLdItem);
		}
		else
		{
			hData = InsertItem(strText, 3, 3, hLdItem);
		}

		dwNum = mms_MakeDWORD(TREEITEM_TYPE_TAGDA, nDeviceIndex, nLDIndex, nDsIndex);
		SetItemData(hData, dwNum);
		pLD_INFO->dwTreeItemData = (DWORD)hData;
	}

	//日志列表
	dwNum = mms_MakeDWORD(TREEITEM_TYPE_LOGLIST, nDeviceIndex, nLDIndex);
	hData = InsertItem(_T("日志记录"), 6, 6, hLdItem, NULL);
	SetItemData(hData, dwNum);

	//建模模型
	dwNum = mms_MakeDWORD(TREEITEM_TYPE_NODES, nDeviceIndex, nLDIndex);
	HTREEITEM hCurr = InsertItem(_T("建模模型"), 7, 7, hLdItem, NULL);
	SetItemData(hCurr, dwNum);
}

void CDvmReadTreeCtrl::InitRootObject()
{
	m_pStartAddr_ACSI_CTRL = pmemOBJTree + sizeof(int);
	m_pStartAddrDEVICE_NODE = m_pStartAddr_ACSI_CTRL + MAX_DEVICE * sizeof(ACSI_CTRL);
	m_pStartAddrACSI_NODE = m_pStartAddrDEVICE_NODE + MAX_DEVICE * sizeof(DEVICE_NODE);
	m_pStartAddr_SOERPT = m_pStartAddrACSI_NODE + MAX_DEVICE * sizeof(ACSI_NODE);
	m_pStartAddr_RLYSOERPT = m_pStartAddr_SOERPT + sizeof(tagSOEFIFO);

}

void CDvmReadTreeCtrl::InitDeviceNodeList(long nDeviceIndex)
{
	if (nDeviceIndex >= 0)
	{
		InsertDevice(nDeviceIndex, TVI_ROOT );
		return;
	}

	ClearLDNodeTree();

	if (!pACSINode)
		return;

	HTREEITEM hItem = NULL;
	HTREEITEM hSubItem = NULL;

	InitRootObject();

	DEVICE_NODE * pDEVICE_NODE = NULL;

	int nSize = *((int*)pmemOBJTree);
	if (nSize>MAX_DEVICE)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("实际装置数大于假设最大装置数!"));
		return;
	} 

	//配置文件中读取到7个,但本项目中只使用一个
	nSize = 1;
	for (int i=0; i<nSize; i++)
	{
		pDEVICE_NODE = (DEVICE_NODE*)(m_pStartAddrDEVICE_NODE + i*sizeof(DEVICE_NODE));
		if (!pDEVICE_NODE)
			continue;

		InsertDevice(i, TVI_ROOT );
	}

	hItem = GetRootItem();
	SelectItem(hItem);
	Expand(hItem,TVE_EXPAND);
}


void CDvmReadTreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CDvmReadTreeCtrl::UpdateDeviceState(long nDeviceIndex)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	UpdateDeviceState(pDevice);
}

void CDvmReadTreeCtrl::UpdateDeviceState(ACSI_NODE *pDevice)
{
	HTREEITEM hItem = (HTREEITEM)pDevice->dwTreeItemData;

	if (pDevice->bConnect)
	{
		SetItemImage(hItem, 1, 1);
	}
	else
	{
		SetItemImage(hItem, 0, 0);
	}
}

void CDvmReadTreeCtrl::UpdateDatasetState(long nDeviceIndex, long nLDIndex, long nDsIndex)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];

	UpdateDatasetState(&pDevice->LD[nLDIndex].DataInfo[nDsIndex]);
}

void CDvmReadTreeCtrl::UpdateDatasetState(LD_DATASET_INFO *pLD_INFO)
{
	HTREEITEM hItem = (HTREEITEM)pLD_INFO->dwTreeItemData;

	if (pLD_INFO->curRcbIndex > 0)
	{
		SetItemImage(hItem, 4, 4);
	}
	else
	{
		SetItemImage(hItem, 3, 3);
	}
}


void CDvmReadTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CTreeCtrl::OnRButtonDown(nFlags, point);
}

BOOL CDvmReadTreeCtrl::SelDeviceNode(long nNodeType,long nDevIndex,long nLogicDevIndex,long nDatasetIndex)
{
	if ((nDevIndex<0))
	{
		return FALSE;
	}

	HTREEITEM hRootItem;  
	hRootItem= GetRootItem();

	if (ItemHasChildren(hRootItem))
	{
		HTREEITEM hCurItemDev=GetChildItem(hRootItem); //找到设备节点
		long nCurDevIndex = 0;

		while(hCurItemDev)  
		{  
			if (nCurDevIndex == nDevIndex)
			{
				if (nNodeType == TREEITEM_TYPE_DEVICE)
				{
					OnMmsSelchanged(hCurItemDev);//选择设备
					return TRUE;
				}

				break;
			}

			nCurDevIndex++;
			hCurItemDev= GetNextItem(hCurItemDev,TVGN_NEXT);  
		} 

		if (hCurItemDev&&ItemHasChildren(hCurItemDev))
		{
			ACSI_NODE *pDevice = &pACSINode[nDevIndex];
			HTREEITEM hCurItemLogDev=GetChildItem(hCurItemDev); //找到逻辑设备节点
			long nCurLogDevIndex = 0;

			if (nNodeType == TREEITEM_TYPE_FILEDIR)
			{
				nCurLogDevIndex = pDevice->numLD;
			}

			while(hCurItemLogDev)  
			{  
				if (nCurLogDevIndex == nLogicDevIndex)
				{
					if ((nNodeType == TREEITEM_TYPE_LDEVICE)||(nNodeType == TREEITEM_TYPE_FILEDIR))
					{
						OnMmsSelchanged(hCurItemLogDev);//选择逻辑设备、文件
						return TRUE;
					}

					break;
				}

				nCurLogDevIndex++;
				hCurItemLogDev= GetNextItem(hCurItemLogDev,TVGN_NEXT);  
			}  

			if (hCurItemLogDev&&ItemHasChildren(hCurItemLogDev))
			{
				LD_NODE *pLdNode = &pDevice->LD[nLogicDevIndex];
				HTREEITEM hCurItemDataset=GetChildItem(hCurItemLogDev); //找到数据集节点
				long nCurDatasetIndex = 0;

				if (nNodeType == TREEITEM_TYPE_LOGLIST)
				{
					nDatasetIndex = pLdNode->numDaSet;
				}

				while(hCurItemDataset)  
				{  
					if (nCurDatasetIndex == nDatasetIndex)
					{
						OnMmsSelchanged(hCurItemDataset);//选择数据集
						return TRUE;
					}

					nCurDatasetIndex++;
					hCurItemDataset= GetNextItem(hCurItemDataset,TVGN_NEXT);  
				}  
			}
		}
	}

	return FALSE;
}
