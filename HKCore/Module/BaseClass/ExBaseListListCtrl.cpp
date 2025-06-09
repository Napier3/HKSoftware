// ExBaseListListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ExBaseListListCtrl.h"
#include "..\XLanguage\XLanguageMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CExBaseListListCtrl

IMPLEMENT_DYNAMIC(CExBaseListListCtrl, CListCtrl)

BOOL CExBaseListListCtrl::Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	AddObj(pData);
	return TRUE;
}

BOOL CExBaseListListCtrl::Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate)
{
	UpdateListCtrl(pData);
	return TRUE;
}

BOOL CExBaseListListCtrl::Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther, BOOL bInvalidate)
{
	DeleteObject(pData);

	return TRUE;
}

BOOL CExBaseListListCtrl::Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate)
{
	SetCurrSelObj(pData);
	return TRUE;
}

void CExBaseListListCtrl::Optr_UpdateDataIndex()
{
	UpdateIndex(0);
}

CExBaseListListCtrl::CExBaseListListCtrl()
{
	m_nInsertClassID = 0;
	m_pList = NULL;
}

void CExBaseListListCtrl::SetCurrSelection(long nIndex)
{
	POSITION pos = GetFirstSelectedItemPosition();
	while (pos != NULL)
	{
		long nPrevIndex = GetNextSelectedItem(pos);
		SetItemState(nPrevIndex, 0 , -1);
	}

	//Select
	SetItemState(nIndex,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);//|LVIS_DROPHILITED);//选择
	//SetItemState(nIndex,~LVIS_SELECTED,LVIS_DROPHILITED);
	SetSelectionMark(nIndex);
	EnsureVisible(nIndex,TRUE);
	SetFocus();
}

void CExBaseListListCtrl::ModifyListCtrlStyle()
{
	ModifyStyle(LVS_SORTASCENDING | LVS_SORTDESCENDING, LVS_SHOWSELALWAYS);
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
}

void CExBaseListListCtrl::CreateListCtrl(CWnd *pParent, CRect rcWnd, UINT nID, BOOL bInitCols)
{
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS;
	BOOL bTrue = Create(dwStyle, rcWnd, pParent, nID);
	ModifyListCtrlStyle();

	if (bInitCols)
	{
		InitCollumns();
	}
}

CExBaseListListCtrl::~CExBaseListListCtrl()
{
}

void CExBaseListListCtrl::InitCollumns()
{
#ifdef NOT_USE_XLANGUAGE
	InsertColumn(LIST_COL_INDEX,_T("编号"),LVCFMT_LEFT,50);
	InsertColumn(LIST_COL_NAME,_T("名称"),LVCFMT_LEFT,100);
#else
	InsertColumn(LIST_COL_INDEX,g_sLangTxt_Index/*_T("编号")*/,LVCFMT_LEFT,50);
	InsertColumn(LIST_COL_NAME,g_sLangTxt_Name/*_T("名称")*/,LVCFMT_LEFT,100);
#endif


	InsertColumn(LIST_COL_ID,_T("ID"),LVCFMT_LEFT,80);
}

void CExBaseListListCtrl::UpdateListCtrl()
{
	long nCount = GetItemCount();
	long nIndex = 0;
	CExBaseObject *pObj = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pObj = (CExBaseObject *)GetItemData(nIndex);
		UpdateListCtrl(pObj, nIndex);
	}
}

void CExBaseListListCtrl::UpdateListCtrl(CExBaseObject *pObj)
{
	long nCount = GetItemCount();
	long nIndex = 0;
	CExBaseObject *pObjFind = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pObjFind = (CExBaseObject *)GetItemData(nIndex);
		
		if (pObjFind == pObj)
		{
			UpdateListCtrl(pObj, nIndex);
			break;
		}
	}
}

void CExBaseListListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	if (pObj->UpdateListCtrl(this, nIndex))
	{
		return;
	}

	CString strText;
	strText.Format(_T("%d"), nIndex+1);
	SetItemText(nIndex, LIST_COL_INDEX, strText);
	SetItemText(nIndex, LIST_COL_NAME, pObj->m_strName);
	SetItemText(nIndex, LIST_COL_ID, pObj->m_strID);
}	

void CExBaseListListCtrl::ShowBaseList(CExBaseList *pList, UINT nClassID)
{
	m_nInsertClassID = nClassID;

	ShowBaseList(pList);
}

void CExBaseListListCtrl::Init(CExBaseList *pList)
{
	ShowBaseList(pList);
}

void CExBaseListListCtrl::ShowBaseList(CExBaseList *pList)
{
	m_pList = pList;

	ShowBaseList();
}

void CExBaseListListCtrl::InsertBaseList(CExBaseList *pList)
{
	m_pList = pList;

	ShowBaseList(FALSE);
}

void CExBaseListListCtrl::ShowBaseList(BOOL bDeletaAllItems)
{
	if (bDeletaAllItems)
	{
		DeleteAllItems();
	}

	if (m_pList == NULL)
	{
		return;
	}

	CExBaseObject *pObj = NULL;
	POS pos = m_pList->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = m_pList->GetNext(pos);
		AddObj(pObj);
	}
}

long CExBaseListListCtrl::FindIndex(CExBaseObject *pObj)
{
	long nCount = GetItemCount();
	long nIndex = 0;
	long nFindIndex = CB_ERR;

	for (nIndex=0; nIndex < nCount; nIndex++)
	{
		if (GetItemData(nIndex) == (DWORD)pObj)
		{
			nFindIndex = nIndex;
			break;
		}
	}

	return nFindIndex;
}

CExBaseObject* CExBaseListListCtrl::SetCurrSelByName(const CString &strName)
{
	int nCount = GetItemCount();
	CExBaseObject* pObj = NULL;
	CExBaseObject* pFind = NULL;
	long nFind = CB_ERR;

	for (int i=0;i<nCount;i++)
	{
		pObj = (CExBaseObject*)GetItemData(i);

		if (pObj != NULL)
		{
			if (strName == pObj->m_strName)
			{
				nFind = i;
				pFind = pObj;
				break;
			}
		}
	}

	SetHotItem(nFind);

	return pFind;//(nFind != CB_ERR);
}

CExBaseObject* CExBaseListListCtrl::SetCurrSelByID(const CString &strID)
{
	int nCount = GetItemCount();
	CExBaseObject* pObj = NULL;
	CExBaseObject* pFind = NULL;
	long nFind = CB_ERR;

	for (int i=0;i<nCount;i++)
	{
		pObj = (CExBaseObject*)GetItemData(i);

		if (pObj != NULL)
		{
			if (strID == pObj->m_strID)
			{
				nFind = i;
				pFind = pObj;
				break;
			}
		}
	}

	SetHotItem(nFind);

	return pFind;//(nFind != CB_ERR);
}

CExBaseObject* CExBaseListListCtrl::SetCurrSelObj(CExBaseObject *pObj)
{
	CExBaseObject *pFind = pObj;

	if (pObj == NULL)
	{
		SetHotItem(-1);
		return NULL;
	}

	long nFindIndex = FindIndex(pObj);

	if (nFindIndex == -1)
	{
		pFind = NULL;
	}

	SetHotItem(nFindIndex);
	SetItemState(nFindIndex, LVIS_SELECTED, LVIS_SELECTED);

	return pFind;
}

long CExBaseListListCtrl::GetAllSelect(CExBaseList &listSel)
{
	POSITION pos = GetFirstSelectedItemPosition();
	long nSel = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		nSel = GetNextSelectedItem(pos);
		pObj = GetObject(nSel);
		listSel.AddTail(pObj);
	}

	return listSel.GetCount();
}

long CExBaseListListCtrl::GetSelectIndex()
{
	POSITION pos = GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		return -1;
	}

	long nSel = GetNextSelectedItem(pos);

	return nSel;
}

CExBaseObject* CExBaseListListCtrl::GetSelectObject()
{
	POSITION pos = GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		return NULL;
	}

	long nSel = GetNextSelectedItem(pos);

	if (nSel < 0)
	{
		return NULL;
	}

	return (CExBaseObject*)GetItemData(nSel);
}

CExBaseObject* CExBaseListListCtrl::GetObject(long nIndex)
{
	if (nIndex < 0)
	{
		return NULL;
	}

	return (CExBaseObject*)GetItemData(nIndex);
}

CString CExBaseListListCtrl::GetSelectID()
{
	CExBaseObject *pSel = GetSelectObject();

	if (pSel == NULL)
	{
		return _T("");
	}
	else
	{
		return pSel->m_strID;
	}
}

CString CExBaseListListCtrl::GetSelectName()
{
	CExBaseObject *pSel = GetSelectObject();

	if (pSel == NULL)
	{
		return _T("");
	}
	else
	{
		return pSel->m_strName;
	}
}

BOOL CExBaseListListCtrl::GetSelectID(CString &strID)
{
	CExBaseObject *pSel = GetSelectObject();

	if (pSel == NULL)
	{
		return FALSE;
	}
	else
	{
		strID = pSel->m_strID;
		return TRUE;
	}
}

BOOL CExBaseListListCtrl::GetSelectName(CString &strName)
{
	CExBaseObject *pSel = GetSelectObject();

	if (pSel == NULL)
	{
		return FALSE;
	}
	else
	{
		strName = pSel->m_strName;
		return TRUE;
	}
}

BOOL CExBaseListListCtrl::DeleteObject(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return NULL;
	}

	long nFindIndex = FindIndex(pObj);

	if (nFindIndex== CB_ERR)
	{
		return FALSE;
	}
	else
	{
		DeleteItem(nFindIndex);
		UpdateIndex(nFindIndex);
		return TRUE;
	}
}

void CExBaseListListCtrl::RemoveByID(const CString &strID)
{
	long nCount = GetItemCount();
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		CExBaseObject *p = (CExBaseObject*)GetItemData(nIndex);

		if (p->m_strID == strID)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	if (nIndexFind != -1)
	{
		DeleteItem(nIndexFind);
		UpdateIndex(nIndexFind);
	}
}

BOOL CExBaseListListCtrl::CanAdd(CExBaseObject *pObj)
{
	BOOL bCanAdd = FALSE;

	if (m_nInsertClassID == 0)
	{
		bCanAdd = TRUE;
	}
	else 
	{
		if (m_nInsertClassID == pObj->GetClassID())
		{
			bCanAdd = TRUE;
		}
	}

	return bCanAdd;
}

long CExBaseListListCtrl::AddObj(CExBaseObject *pObj)
{
	if (!CanAdd(pObj))
	{
		return -1;
	}

	long nCount = GetItemCount();

	if (nCount >= 65530)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("ExBaseListListCtrl:数据太多"));
	}

	CString strText;
	strText.Format(_T("%d"), nCount+1);
	InsertItem(nCount, strText);
	UpdateListCtrl(pObj, nCount);
	SetItemData(nCount, (DWORD)pObj);

	return nCount;
}


long CExBaseListListCtrl::InsertObj(long nIndex, CExBaseObject *pObj)
{
	if (!CanAdd(pObj))
	{
		return -1;
	}

	InsertItem(nIndex, _T(""));
	UpdateListCtrl(pObj, nIndex);
	SetItemData(nIndex, (DWORD)pObj);
	UpdateIndex(nIndex);

	return nIndex;
}

void CExBaseListListCtrl::UpdateIndex(long nIndexFrom)
{
	long nIndex = nIndexFrom;
	long nCount = GetItemCount();
	CString strText;

	for (nIndex=nIndexFrom; nIndex < nCount; nIndex++)
	{
		strText.Format(_T("%d"), nIndex+1);
		SetItemText(nIndex, LIST_COL_INDEX, strText);
	}
}

BEGIN_MESSAGE_MAP(CExBaseListListCtrl, CListCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// CExBaseListListCtrl 消息处理程序



void CExBaseListListCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	PopupMenu(pWnd, point);
}
