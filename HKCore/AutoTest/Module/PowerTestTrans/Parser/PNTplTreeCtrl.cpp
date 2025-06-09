// DvmDeviceTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "PNTplTreeCtrl.h"

IMPLEMENT_DYNAMIC(CPNTplTreeCtrl, CTreeCtrl)

CPNTplTreeCtrl::CPNTplTreeCtrl()
{
	m_pPNTpl = NULL;
	m_pFrameWnd = NULL;
	m_bChangeChild = TRUE;
	m_pTreeSelNode = NULL;
	m_pTreeSelNodePrev = NULL;
	m_dwRcvMsg = 0;
}

CPNTplTreeCtrl::~CPNTplTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CPNTplTreeCtrl, CTreeCtrl)

END_MESSAGE_MAP()


void CPNTplTreeCtrl::InitShowPNTpl(CPNTplRoot* pPNTpl)
{
	m_pPNTpl = pPNTpl;
	DeleteAllItems();

	if(m_pPNTpl == NULL)
	{
		return;
	}

	InsertToTreeCtrl(m_pPNTpl, NULL);
	m_pTreeSelNode = m_pPNTpl;
	Expand((HTREEITEM)m_pTreeSelNode->m_dwItemData,TVE_EXPAND);
	/*SelChanged((HTREEITEM)m_pPNTpl->m_dwItemData);*/
}

UINT CPNTplTreeCtrl::GetImgIndex(CExBaseObject* pDvmNode)
{
	UINT nClassID = pDvmNode->GetClassID();

	switch (nClassID)
	{
	case MNGRCLASSID_CPNTPLROOT:
		nClassID = 0;
		break;
	case MNGRCLASSID_CPNTPLELEMENT:
		nClassID = 1;
		break;
	case MNGRCLASSID_CPNTPLGROUP:
		nClassID = 2;
	case MNGRCLASSID_CPNTPLEQUATION:
		nClassID = 3;
		break;
	case MNGRCLASSID_CPNTPLTEXT:
		nClassID = 4;
		break;
	}

	return nClassID;
}
void CPNTplTreeCtrl::UpdateToTreeCtrl(CExBaseObject*pItem)
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

BOOL CPNTplTreeCtrl::IsObjVisible(UINT nClassID)
{
	return (nClassID == MNGRCLASSID_CPNTPLROOT) ||
		(nClassID == MNGRCLASSID_CPNTPLELEMENT) ||
		(nClassID == MNGRCLASSID_CPNTPLEQUATION)||
		(nClassID == MNGRCLASSID_CPNTPLTEXT)||
		(nClassID == MNGRCLASSID_CPNTPLGROUP);
}

void CPNTplTreeCtrl::InsertToTreeCtrl(CExBaseObject*pItem,HTREEITEM htiParent,HTREEITEM hAfter, BOOL bSelect)
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

void CPNTplTreeCtrl::InsertChildrenToTreeCtrl(CExBaseList* pItem,HTREEITEM htiParent)
{
	if ((pItem->GetClassID() == MNGRCLASSID_CPNTPLEQUATION) ||
		(pItem->GetClassID() == MNGRCLASSID_CPNTPLTEXT))
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

CExBaseObject* CPNTplTreeCtrl::GetDvmObjByTreeItem(long hTreeItem)
{
	if (m_pPNTpl != NULL)
	{
		return (CExBaseObject*)GetItemData((HTREEITEM)hTreeItem);
	}

	return NULL;
}


CExBaseObject* CPNTplTreeCtrl::SelChanged(HTREEITEM hItem)
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

BOOL CPNTplTreeCtrl::ChangeTreePosition(CExBaseObject* p1,CExBaseObject* p2)
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

void CPNTplTreeCtrl::DeleteTplNode(CExBaseObject *pDvmNode)
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