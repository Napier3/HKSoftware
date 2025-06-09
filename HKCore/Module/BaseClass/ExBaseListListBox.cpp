// ExBaseListListBox.cpp : 实现文件
//

#include "stdafx.h"
#include "ExBaseListListBox.h"


// CExBaseListListBox

IMPLEMENT_DYNAMIC(CExBaseListListBox, CListBox)

CExBaseListListBox::CExBaseListListBox()
{
	m_bAddEmptyString = FALSE;
	m_dwAddName_ID_Mode = TRUE;
	m_nInsertClassID = 0;
	m_pList = NULL;
}

CExBaseListListBox::~CExBaseListListBox()
{
}

void CExBaseListListBox::ShowBaseList(CExBaseList *pList, UINT nClassID, BOOL bAddEmptyString,BOOL bAddName)
{
	m_nInsertClassID = nClassID;
	m_bAddEmptyString = bAddEmptyString;
	m_dwAddName_ID_Mode = bAddName;

	ShowBaseList(pList);
}

void CExBaseListListBox::Init(CExBaseList *pList, BOOL bAddEmptyString,BOOL bAddName)
{
	m_bAddEmptyString = bAddEmptyString;
	m_dwAddName_ID_Mode = bAddName;
	ShowBaseList(pList);
}

void CExBaseListListBox::ShowBaseList(CExBaseList *pList)
{
	m_pList = pList;

	ShowBaseList();
}

void CExBaseListListBox::ShowBaseList()
{
	ResetContent();

	if (m_pList == NULL)
	{
		return;
	}

	if (m_bAddEmptyString)
	{
		long nIndex = AddString(_T(""));
		SetItemDataPtr(nIndex, NULL);
	}

	CExBaseObject *pObj = NULL;
	POS pos = m_pList->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = m_pList->GetNext(pos);
		AddObj(pObj);
	}
}

long CExBaseListListBox::FindIndex(CExBaseObject *pObj)
{
	long nCount = GetCount();
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

CExBaseObject* CExBaseListListBox::SetCurrSelByName(const CString &strName)
{
// 	ASSERT (m_pList == NULL);
// 
// 	if (m_pList == NULL)
// 	{
// 		SetCurSel(-1);
// 		return NULL;
// 	}
//
	if (strName == _T("") && m_bAddEmptyString)
	{
		SetCurSel(0);
		return NULL;
	}

// 	CExBaseObject *pFind = NULL;
// 	pFind = m_pList->FindByName(strName);
// 
// 	return SetCurrSelObj(pFind);

	int nCount = GetCount();
	CExBaseObject* pObj = NULL;
	CExBaseObject* pFind = NULL;
	long nFind = CB_ERR;

	for (int i=0;i<nCount;i++)
	{
		pObj = (CExBaseObject*)GetItemDataPtr(i);

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

	SetCurSel(nFind);

	return pFind;//(nFind != CB_ERR);
}

CExBaseObject* CExBaseListListBox::SetCurrSelByID(const CString &strID)
{
	if (strID == _T("") && m_bAddEmptyString)
	{
		SetCurSel(0);
		return NULL;
	}

// 	ASSERT (m_pList != NULL);
// 
// 	if (m_pList == NULL)
// 	{
// 		SetCurSel(-1);
// 		return NULL;
// 	}
// 
// 	CExBaseObject *pFind = NULL;
// 	pFind = m_pList->FindByID(strID);
// 
// 	return SetCurrSelObj(pFind);

	int nCount = GetCount();
	CExBaseObject* pObj = NULL;
	CExBaseObject* pFind = NULL;
	long nFind = CB_ERR;

	for (int i=0;i<nCount;i++)
	{
		pObj = (CExBaseObject*)GetItemDataPtr(i);

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

	SetCurSel(nFind);

	return pFind;//(nFind != CB_ERR);
}

CExBaseObject* CExBaseListListBox::SetCurrSelObj(CExBaseObject *pObj)
{
	CExBaseObject *pFind = pObj;

	if (pObj == NULL)
	{
		SetCurSel(-1);
		return NULL;
	}

	long nFindIndex = FindIndex(pObj);

	if (nFindIndex == -1)
	{
		pFind = NULL;
	}

	SetCurSel(nFindIndex);

	return pFind;
}


CExBaseObject* CExBaseListListBox::GetSelectObject()
{
	long nSel = GetCurSel();

	if (nSel == CB_ERR)
	{
		return NULL;
	}

	return (CExBaseObject*)GetItemData(nSel);
}

CString CExBaseListListBox::GetSelectID()
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

CString CExBaseListListBox::GetSelectName()
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

BOOL CExBaseListListBox::GetSelectID(CString &strID)
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

BOOL CExBaseListListBox::GetSelectName(CString &strName)
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

BOOL CExBaseListListBox::DeleteObject(CExBaseObject *pObj)
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
		DeleteString(nFindIndex);
		return TRUE;
	}
}

void CExBaseListListBox::RemoveByID(const CString &strID)
{
	long nCount = GetCount();
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		CExBaseObject *p = (CExBaseObject*)GetItemDataPtr(nIndex);

		if (p->m_strID == strID)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	if (nIndexFind != -1)
	{
		DeleteString(nIndexFind);
	}
}

BOOL CExBaseListListBox::CanAdd(CExBaseObject *pObj)
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

	if (pObj->m_dwReserved == 0)
	{
		bCanAdd = FALSE;
	}

	return bCanAdd;
}

long CExBaseListListBox::AddObj(CExBaseObject *pObj)
{
	if (!CanAdd(pObj))
	{
		return -1;
	}

	long nIndex = 0;

	if (m_dwAddName_ID_Mode == 0)
	{
		nIndex = AddString(pObj->m_strName);
	}
	else if (m_dwAddName_ID_Mode == 1)
	{
		nIndex = AddString(pObj->m_strID);
	}
	else
	{
		if (pObj->m_strID.GetLength() == 0)
		{
			nIndex = AddString(pObj->m_strName);
		}
		else
		{
			CString strText;
			strText.Format(_T("%s   (%s)"), pObj->m_strName, pObj->m_strID);
			nIndex = AddString(strText);
		}
	}

	SetItemData(nIndex, (DWORD)pObj);

	return -1;
}


long CExBaseListListBox::InsertObj(long nIndex, CExBaseObject *pObj)
{
	if (!CanAdd(pObj))
	{
		return -1;
	}

	long nCurrIndex = 0;
	
	if (m_dwAddName_ID_Mode == 0)
	{
		nCurrIndex = InsertString(nIndex, pObj->m_strName);
	}
	else if (m_dwAddName_ID_Mode == 1)
	{
		nCurrIndex = InsertString(nIndex, pObj->m_strID);
	}
	else
	{
		if (pObj->m_strID.GetLength() == 0)
		{
			nCurrIndex = InsertString(nIndex, pObj->m_strName);
		}
		else
		{
			CString strText;
			strText.Format(_T("%s  (%s)"), pObj->m_strName, pObj->m_strID);
			nCurrIndex = InsertString(nIndex, strText);
		}
	}

	SetItemData(nCurrIndex, (DWORD)pObj);

	return nCurrIndex;
}

BEGIN_MESSAGE_MAP(CExBaseListListBox, CListBox)
END_MESSAGE_MAP()



// CExBaseListListBox 消息处理程序


void CExBaseListListBox::SetAddName(BOOL bAddName)	
{
	if (bAddName)
		m_dwAddName_ID_Mode = 0;
	else
		m_dwAddName_ID_Mode = 1;
}