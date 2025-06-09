// DvmDeviceTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "DvmDeviceTreeCtrl.h"

IMPLEMENT_DYNAMIC(CDvmDeviceTreeCtrl, CTreeCtrl)

CDvmDeviceTreeCtrl::CDvmDeviceTreeCtrl()
{
	m_pDvmDevice = NULL;
	m_pFrameWnd = NULL;
	m_bChangeChild = TRUE;
	m_pTreeSelNode = NULL;
	m_pTreeSelNodePrev = NULL;
	m_dwRcvMsg = 0;
}

CDvmDeviceTreeCtrl::~CDvmDeviceTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CDvmDeviceTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CDvmDeviceTreeCtrl::OnNMDblclk)
END_MESSAGE_MAP()


void CDvmDeviceTreeCtrl::InitShowDvmDevice(CDvmDevice* pDvmDevice)
{
	m_pDvmDevice = pDvmDevice;
	DeleteAllItems();

	if(m_pDvmDevice == NULL)
	{
		return;
	}

	InsertToTreeCtrl(m_pDvmDevice, NULL);
	m_pTreeSelNode = m_pDvmDevice;
	Expand((HTREEITEM)m_pTreeSelNode->m_dwItemData,TVE_EXPAND);
	SelChanged((HTREEITEM)m_pDvmDevice->m_dwItemData);
}

UINT CDvmDeviceTreeCtrl::GetImgIndex(CExBaseObject* pDvmNode)
{
	UINT nClassID = pDvmNode->GetClassID();

	switch (nClassID)
	{
	case DVMCLASSID_CDVMDEVICE:
		nClassID = 0;
		break;
	case DVMCLASSID_CDVMLOGICDEVICE:
		nClassID = 1;
		break;
	case DVMCLASSID_CDVMDATASET:
		nClassID = 2;
		break;
	}

	return nClassID;
}
void CDvmDeviceTreeCtrl::UpdateToTreeCtrl(CExBaseObject*pItem)
{
	HTREEITEM hCurr = (HTREEITEM)pItem->m_dwItemData;
	
	if (hCurr != NULL)
	{
		if (ItemHasChildren(hCurr))
		{
			HTREEITEM hNextItem;
			HTREEITEM hChildItem = GetChildItem(hCurr);

			while (hChildItem != NULL)
			{
				hNextItem = GetNextItem(hChildItem, TVGN_NEXT);
				DeleteItem(hChildItem);
				hChildItem = hNextItem;
			}
		}
	}
	else
	{
		CExBaseList *pParent = (CExBaseList*)pItem->GetParent();
		HTREEITEM hParent = NULL;
		ASSERT (pParent != NULL);
		hParent = (HTREEITEM)pParent->m_dwItemData;
		ASSERT (hParent != NULL);
		InsertToTreeCtrl(pItem, hParent, NULL, FALSE);
	}

	if (IsObjVisible(pItem->GetClassID()))
	{
		InsertChildrenToTreeCtrl((CExBaseList*)pItem, hCurr);
	}
}

BOOL CDvmDeviceTreeCtrl::IsObjVisible(UINT nClassID)
{
	return (nClassID == DVMCLASSID_CDVMDEVICE) ||
		(nClassID == DVMCLASSID_CDVMLOGICDEVICE) ||
		(nClassID == DVMCLASSID_CDVMDATASET);
}

void CDvmDeviceTreeCtrl::InsertToTreeCtrl(CExBaseObject*pItem,HTREEITEM htiParent,HTREEITEM hAfter, BOOL bSelect)
{
	HTREEITEM hTreeItem = NULL;

	if (pItem == NULL)
	{
		return;
	}

	//显示可显示的项；显示子元素
	if (IsObjVisible(pItem->GetClassID()))
	{
		UINT nImg = GetImgIndex(pItem);
		hTreeItem = InsertItem(pItem->m_strName, nImg, nImg, htiParent,hAfter);
		pItem->m_dwItemData = (DWORD)hTreeItem;
		SetItemData(hTreeItem, (DWORD)pItem);
		
		//判断其是否为可扩展项
		if (IsObjVisible(pItem->GetClassID()))
		{
			InsertChildrenToTreeCtrl((CExBaseList*)pItem, hTreeItem);
		}

		if (bSelect)
		{
			HTREEITEM hCurrItem = (HTREEITEM)pItem->m_dwItemData;
			CExBaseObject* pParent = (CExBaseObject*)pItem->GetParent();
		
			if(pParent != NULL)
			{
				Expand((HTREEITEM)pParent->m_dwItemData,TVE_EXPAND);
			}
		}
	}

}

void CDvmDeviceTreeCtrl::InsertChildrenToTreeCtrl(CExBaseList* pItem,HTREEITEM htiParent)
{
	if (pItem->GetClassID() == DVMCLASSID_CDVMDATASET)
	{
		return;
	}

	ASSERT(pItem != NULL);
	CExBaseObject* pObj = NULL;
	POS pos = pItem->GetHeadPosition();

	while(pos != NULL)
	{
		pObj = (CExBaseObject*)pItem->GetNext(pos);
		InsertToTreeCtrl(pObj,htiParent);
	}
}

CExBaseObject* CDvmDeviceTreeCtrl::GetDvmObjByTreeItem(long hTreeItem)
{
	if (m_pDvmDevice != NULL)
	{
		return (CExBaseObject*)GetItemData((HTREEITEM)hTreeItem);
	}

	return NULL;
}


CExBaseObject* CDvmDeviceTreeCtrl::SelChanged(HTREEITEM hItem)
{
// 	CExBaseObject* pDvmNode  = (CExBaseObject*)GetItemData(hItem);
// 	ASSERT(pDvmNode != NULL);
// 
// 	SelectItem(hItem);
// 	m_pTreeSelNode = pDvmNode;
// 
// 	if (m_pFrameWnd != NULL)
// 	{
// 		if(m_pTreeSelNodePrev != m_pTreeSelNode)
// 		{
// 			if (m_dwRcvMsg != 0)
// 			{
// 				m_pFrameWnd->SendMessage(m_dwRcvMsg, (WPARAM)this, (LPARAM)m_pTreeSelNode);
// 			}
// 		}
// 	}
// 
// 	m_pTreeSelNodePrev = pDvmNode;
// 	return pDvmNode;
	return NULL;
}

BOOL CDvmDeviceTreeCtrl::ChangeTreePosition(CExBaseObject* p1,CExBaseObject* p2)
{
	if(p1 != NULL && p2 != NULL)
	{
		if( IsObjVisible(p1->GetClassID()) && IsObjVisible(p2->GetClassID()) )
		{
			CExBaseList* pParent = (CExBaseList*)p1->GetParent();
			if(pParent == (CExBaseList*)p2->GetParent() && IsObjVisible(pParent->GetClassID()))
			{
				HTREEITEM hItem = NULL;
				
				POS pos1 = pParent->Find(p1);
				POS pos2 = pParent->Find(p2);
				int nIndex1 = -1;
				int nIndex2 = -1;
				if(pos1 != NULL && pos2 != NULL)
				{
					nIndex1 = pParent->FindIndex(pos1);
					nIndex2 = pParent->FindIndex(pos2);
				}
				else
				{
					return FALSE;
				}
				
				if(nIndex1 != -1 && nIndex2 != -1)
				{
					if(nIndex2 > nIndex1)
					{
						this->DeleteItem((HTREEITEM)p2->m_dwItemData);
						UINT nImg = GetImgIndex(p2);
						hItem = this->InsertItem(p2->m_strName,nImg , nImg,(HTREEITEM)pParent->m_dwItemData,(HTREEITEM)p1->m_dwItemData);
						if(p2->IsBaseList())
						{
							InsertChildrenToTreeCtrl((CExBaseList*)p2,hItem);
						}
						p2->m_dwItemData = (DWORD)hItem;
						SetItemData(hItem,(DWORD_PTR)p2);
					}
				}

			}
		}
	}

	return FALSE;
}

void CDvmDeviceTreeCtrl::DeleteDvmNode(CExBaseObject *pDvmNode)
{
	if( !IsObjVisible(pDvmNode->GetClassID()) )
	{
		return;
	}

	HTREEITEM hItem = (HTREEITEM)pDvmNode->m_dwItemData;
	HTREEITEM hPrev = GetPrevSiblingItem(hItem);
	HTREEITEM hNext = GetNextSiblingItem(hItem);
	HTREEITEM hParent = GetParentItem(hItem);
	DeleteItem(hItem);

	HTREEITEM hNewItem = GetSelectedItem();

	if (hNewItem != NULL)
	{
		SelChanged(hNewItem);
	}
	else
	{
		if (hNext != NULL)
		{
			SelChanged(hNext);
		}
		else if (hPrev != NULL)
		{
			SelChanged(hPrev);
		}
		else if (hParent != NULL)
		{
			SelChanged(hParent);
		}
	}
}

CDvmDataset* CDvmDeviceTreeCtrl::GetCurrSelDataset()
{
	HTREEITEM hItem = GetSelectedItem();

	if (hItem == NULL)
	{
		return NULL;
	}

	CExBaseObject *pSel = (CExBaseObject*)GetItemData(hItem);

	if (pSel == NULL)
	{
		return NULL;
	}

	if (pSel->GetClassID() == DVMCLASSID_CDVMDATASET)
	{
		return (CDvmDataset*)pSel;
	}
	else
	{
		return NULL;
	}
}


void CDvmDeviceTreeCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	HTREEITEM hItem = GetSelectedItem();

	if (hItem == NULL)
	{
		return;
	}

	CExBaseObject *pSel = (CExBaseObject*)GetItemData(hItem);

	if(pSel == NULL)
	{
		return;
	}

	if (m_pDataViewOptrInterface != NULL)
	{
		//传给父窗口处理
		m_pDataViewOptrInterface->OnNMDblclk(this, pNMHDR, pResult);
		return;
	}

	if (m_pFrameWnd == NULL || m_dwRcvMsg == 0)
	{
		return;
	}

	if (m_pFrameWnd != NULL)
	{
		m_pFrameWnd->PostMessage(m_dwRcvMsg, (WPARAM)this, (LPARAM)pSel);
	}
}