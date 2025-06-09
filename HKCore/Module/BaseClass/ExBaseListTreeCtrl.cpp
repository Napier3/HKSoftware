// \Module\BaseClass\ExBaseListTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ExBaseListTreeCtrl.h"


// CExBaseListTreeCtrl

IMPLEMENT_DYNAMIC(CExBaseListTreeCtrl, CTreeCtrl)

BOOL CExBaseListTreeCtrl::Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	AddObj(pData);

	return TRUE;
}

BOOL CExBaseListTreeCtrl::Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate)
{
	UpdateObject(pData);

	return TRUE;
}

BOOL CExBaseListTreeCtrl::Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther, BOOL bInvalidate)
{
	return DeleteObject(pData, bSelectOther);
}

BOOL CExBaseListTreeCtrl::Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate)
{
	SetCurrSelObj(pData);
	return TRUE;
}

CExBaseListTreeCtrl::CExBaseListTreeCtrl()
{
	m_pOptrInterface = NULL;
	m_pList = NULL;
}

CExBaseListTreeCtrl::~CExBaseListTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CExBaseListTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CExBaseListTreeCtrl::OnNMDblclk)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CExBaseListTreeCtrl::OnTvnSelchanged)
END_MESSAGE_MAP()



// CExBaseListTreeCtrl 消息处理程序


void CExBaseListTreeCtrl::ShowBaseList(CExBaseList *pList, BOOL bAddRoot)
{
	HTREEITEM hItem = NULL;
	m_pList = pList;

	if (bAddRoot)
	{
		hItem = AddObj(pList, TVI_ROOT);
		Expand(hItem, TVE_EXPAND);
	}
	else
	{
		POS pos = pList->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pList->GetNext(pos);
			AddObj(p, TVI_ROOT);
		}
	}
}

void CExBaseListTreeCtrl::SetCurrSelObj(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return;
	}

	HTREEITEM hItem = (HTREEITEM)pObj->m_dwItemData;
	
	if (hItem != NULL)
	{
		Select(hItem,TVGN_CARET);
	}
}

CExBaseObject* CExBaseListTreeCtrl::GetSelectObject()
{
	HTREEITEM hItem = GetSelectedItem();

	if (hItem == NULL)
	{
		return NULL;
	}

	return (CExBaseObject*)GetItemData(hItem);
}

CString CExBaseListTreeCtrl::GetSelectID()
{
	return _T("");
}

CString CExBaseListTreeCtrl::GetSelectName()
{
	return _T("");
}

BOOL CExBaseListTreeCtrl::GetSelectID(CString &strID)
{
	return FALSE;
}

BOOL CExBaseListTreeCtrl::GetSelectName(CString &strName)
{
	return FALSE;
}


BOOL CExBaseListTreeCtrl::DeleteObject(CExBaseObject *pObj, BOOL bSelOther)
{
	HTREEITEM hItem = (HTREEITEM)pObj->m_dwItemData;

	if (hItem == NULL)
	{
		return FALSE;
	}

	HTREEITEM hSelItem = GetSelectedItem();
	HTREEITEM hPrev = GetPrevSiblingItem(hItem);
	HTREEITEM hNext = GetNextSiblingItem(hItem);
	HTREEITEM hParent = GetParentItem(hItem);
	DeleteItem(hItem);

	if (hSelItem != hItem)
	{
		return FALSE;
	}

	if (!bSelOther)
	{
		return FALSE;
	}

	HTREEITEM hNewItem = GetSelectedItem();

	if (hNewItem != NULL)
	{
		SelectItem(hNewItem);
	}
	else
	{
		if (hNext != NULL)
		{
			SelectItem(hNext);
		}
		else if (hPrev != NULL)
		{
			SelectItem(hPrev);
		}
		else if (hParent != NULL)
		{
			SelectItem(hParent);
		}
	}

	return TRUE;
}

HTREEITEM CExBaseListTreeCtrl::AddObj(CExBaseObject *pObj, BOOL bExpand)
{
	CExBaseObject *pParent = (CExBaseObject*)pObj->GetParent();
	HTREEITEM hItem = NULL;

	if (pParent == NULL)
	{
		hItem = AddObj(pObj, TVI_ROOT);
	}
	else
	{
		hItem = AddObj(pObj, (HTREEITEM)pParent->m_dwItemData);
	}

	if (bExpand)
	{
		Expand(hItem, TVE_EXPAND);
	}

	RedrawWindow();

	return hItem;
}

void CExBaseListTreeCtrl::UpdateObject(CExBaseObject *pObj)
{
	if (!CanAdd(pObj))
	{
		return;
	}

	SetItemText((HTREEITEM)pObj->m_dwItemData, pObj->m_strName);
}

BOOL CExBaseListTreeCtrl::CanAdd(CExBaseObject *pObj)
{
	return CanAdd(pObj->GetClassID());
}

BOOL CExBaseListTreeCtrl::CanAdd(UINT nClassID)
{
	//2021-8-21  lijunqing  如果没有定义，则显示所有
	if (m_arrdwClassID.GetCount() == 0)
	{
		return TRUE;
	}

	return GetIndexOfClassID(nClassID) >= 0;
}

HTREEITEM CExBaseListTreeCtrl::AddObj(CExBaseObject *pObj, HTREEITEM hParent)
{
	UINT nClassID = pObj->GetClassID();
	HTREEITEM hItem = NULL;

	if (!CanAdd(nClassID))
	{
		return NULL;
	}

	hItem = InsertItem(pObj->m_strName, 0, 0, hParent);
	pObj->m_dwItemData = (DWORD)hItem;
	SetItemData(hItem, (DWORD)pObj);

	if (!CBaseObject::IsBaseList(nClassID))
	{
		return hItem;
	}

	CExBaseList *pList = (CExBaseList*)pObj;
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		AddObj(p, hItem);
	}

	return hItem;
}

HTREEITEM CExBaseListTreeCtrl::InsertObj(UINT nClassID, const  CString &strName, HTREEITEM hParent)
{
	return InsertItem(strName, 0, 0, hParent);
}

void CExBaseListTreeCtrl::ClearArrClassID()
{
	m_arrdwClassID.RemoveAll();
}

void CExBaseListTreeCtrl::AddClassID(UINT nClassID)
{
	m_arrdwClassID.Add(nClassID);
}

void CExBaseListTreeCtrl::RemoveClassID(UINT nClassID)
{
	long nIndex = GetIndexOfClassID(nClassID);

	if (nIndex >= 0)
	{
		m_arrdwClassID.RemoveAt(nIndex);
	}
}

long CExBaseListTreeCtrl::GetIndexOfClassID(UINT nClassID)
{
	long nIndex = 0;
	long nIndexFind = -1;
	long nCount = m_arrdwClassID.GetSize();

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (nClassID == m_arrdwClassID.GetAt(nIndex))
		{
			nIndexFind = nIndex;
			break;
		}
	}

	return nIndexFind;
}

//////////////////////////////////////////////////////////////////////////
void CExBaseListTreeCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	if (m_pOptrInterface == NULL)
	{
		return;
	}

	CExBaseObject *pSel = GetSelectObject();
	m_pOptrInterface->OnItemBDblClk(this, pSel);
}

void CExBaseListTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if (m_pOptrInterface == NULL)
	{
		return;
	}

	CExBaseObject *pSel = GetSelectObject();
	m_pOptrInterface->OnItemSelChanged(this, pSel);
}
