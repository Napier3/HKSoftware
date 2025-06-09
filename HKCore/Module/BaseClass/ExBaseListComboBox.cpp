// ExBaseListComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "ExBaseListComboBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// CExBaseListComboBoxList

IMPLEMENT_DYNAMIC(CExBaseListComboBoxList, CListBox)

CExBaseListComboBoxList::CExBaseListComboBoxList()
{
	m_pCmoboBox = NULL;
}

CExBaseListComboBoxList::~CExBaseListComboBoxList()
{
}


BEGIN_MESSAGE_MAP(CExBaseListComboBoxList, CListBox)
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


void CExBaseListComboBoxList::OnRButtonUp(UINT nFlags, CPoint point)
{
	CListBox::OnRButtonUp(nFlags, point);

	if (m_pCmoboBox != NULL)
	{
		m_pCmoboBox->PostMessage(WM_RBUTTON_UP_LIST, 0, 0);
	}
}

//////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DYNAMIC(CExBaseListComboBoxEdit, CEdit)

CExBaseListComboBoxEdit::CExBaseListComboBoxEdit()
{
	m_pCmoboBox = NULL;
	m_nCurrPosBegin = 0;
	m_nCurrPosEnd = 0;
}

CExBaseListComboBoxEdit::~CExBaseListComboBoxEdit()
{
}

BEGIN_MESSAGE_MAP(CExBaseListComboBoxEdit, CEdit)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CExBaseListComboBoxEdit::OnEnKillfocus)
	ON_CONTROL_REFLECT(EN_CHANGE, &CExBaseListComboBoxEdit::OnEnChange)
END_MESSAGE_MAP()

void CExBaseListComboBoxEdit::OnEnKillfocus()
{
	
}

void CExBaseListComboBoxEdit::ShowText()
{
	if (m_strText.GetLength() == 0)
	{
		return;
	}

	SetWindowText(m_strText);
	SetSel(m_nCurrPosBegin, m_nCurrPosEnd);
}

void CExBaseListComboBoxEdit::OnEnChange()
{
	GetWindowText(m_strText);
	GetSel(m_nCurrPosBegin, m_nCurrPosEnd);

	if (m_pCmoboBox != NULL)
	{
		m_pCmoboBox->SendMessage(WM_FILTER_EXBASELIST, 0, 0);
	}
}

//////////////////////////////////////////////////////////////////////////
// CExBaseListComboBox

BOOL CExBaseListComboBox::Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	AddObj(pData);

	return TRUE;
}

BOOL CExBaseListComboBox::Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate)
{
	long nIndex = FindIndex(pData);
	long nSelIndex = GetCurSel();
	DeleteString(nIndex);
	InsertObj(nIndex, pData);

	if (nSelIndex == nIndex)
	{
		SetCurSel(nIndex);
	}

	return TRUE;
}

BOOL CExBaseListComboBox::Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther, BOOL bInvalidate)
{
	DeleteObject(pData);

	return TRUE;
}

BOOL CExBaseListComboBox::Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate)
{
	SetCurrSelObj(pData);
	return TRUE;
}

CExBaseListComboBox::CExBaseListComboBox()
{
	m_bAddEmptyString = FALSE;
	m_bAddName = TRUE;
	m_nInsertClassID = 0;
	m_pList = NULL;
	m_bUseFilter = FALSE;
	m_bUseComboBoxList = TRUE;
}

void CExBaseListComboBox::UnsubclassChildWindow()
{
	if ( m_Edit.GetSafeHwnd() != NULL )
	{
		m_Edit.UnsubclassWindow();
	}

	if ( m_ListBox.GetSafeHwnd() != NULL )
	{
		m_ListBox.UnsubclassWindow();
	}
}

CExBaseListComboBox::~CExBaseListComboBox()
{
	UnsubclassChildWindow();
}

void CExBaseListComboBox::ShowBaseList(CExBaseList *pList, UINT nClassID, BOOL bAddEmptyString,BOOL bAddName)
{
	m_nInsertClassID = nClassID;
	m_bAddEmptyString = bAddEmptyString;
	m_bAddName = bAddName;

	ShowBaseList(pList);
}

void CExBaseListComboBox::Init(CExBaseList *pList, BOOL bAddEmptyString,BOOL bAddName)
{
	m_bAddEmptyString = bAddEmptyString;
	m_bAddName = bAddName;
	ShowBaseList(pList);
}

#ifndef NO_XDbBaseLib
void CExBaseListComboBox::InitEx(CExBaseList *pList, long nPkValue, BOOL bAddEmptyString, BOOL bAddName)
{
	Init(pList, bAddEmptyString, bAddName);
	SetCurrSelObj(nPkValue);
}
#endif

void CExBaseListComboBox::ShowBaseList(CExBaseList *pList)
{
	m_pList = pList;

	ShowBaseList();
}

void CExBaseListComboBox::ShowBaseList()
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

#ifndef exbase_not_use_m_dwReserved
		if (pObj->m_dwReserved != 0)
#endif
		{
			AddObj(pObj);
		}
	}
}

long CExBaseListComboBox::FindIndex(CExBaseObject *pObj)
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

CExBaseObject* CExBaseListComboBox::SetCurrSelByName(const CString &strName)
{
	if (strName == _T("") && m_bAddEmptyString)
	{
		SetCurSel(0);
		return NULL;
	}

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

CExBaseObject* CExBaseListComboBox::SetCurrSelByID(const CString &strID)
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

CExBaseObject* CExBaseListComboBox::SetCurrSelObj(CExBaseObject *pObj)
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

#ifndef NO_XDbBaseLib
CExBaseObject* CExBaseListComboBox::SetCurrSelObj(long nPkValue)
{
	CExBaseObject *pFind = NULL;
	
	if (nPkValue > 0)
	{
		pFind = m_pList->FindByPkValue(nPkValue);
		ASSERT (pFind != NULL);
	}
	else
	{
		ASSERT (m_bAddEmptyString);
		SetCurSel(0);
		return NULL;
	}

	SetCurrSelObj(pFind);

	return pFind;
}
#endif

CExBaseObject* CExBaseListComboBox::GetSelectObject()
{
	long nSel = GetCurSel();

	if (nSel == CB_ERR)
	{
		return NULL;
	}

	return (CExBaseObject*)GetItemData(nSel);
}

CString CExBaseListComboBox::GetSelectID()
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

CString CExBaseListComboBox::GetSelectName()
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

BOOL CExBaseListComboBox::GetSelectID(CString &strID)
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

BOOL CExBaseListComboBox::GetSelectName(CString &strName)
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

#ifndef NO_XDbBaseLib
long CExBaseListComboBox::GetSelectPKValue()
{
	CExBaseObject *pSel = GetSelectObject();

	if (pSel == NULL)
	{
		return 0;
	}
	else
	{
		CXDb_PKeyValue oPKeyValue;
		pSel->Db_GetPkeyValue(oPKeyValue);
		return *oPKeyValue.oKeyValRef.pnValue;
	}
}
#endif

BOOL CExBaseListComboBox::DeleteObject(CExBaseObject *pObj)
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

//2021-1-8  lijunqing
BOOL CExBaseListComboBox::DeleteCurrSelObject()
{
	long nIndex = GetCurSel();

	if (nIndex != CB_ERR)
	{
		DeleteString(nIndex);
		return TRUE;
	}

	return FALSE;
}

void CExBaseListComboBox::RemoveByID(const CString &strID)
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

BOOL CExBaseListComboBox::CanAdd(CExBaseObject *pObj)
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

long CExBaseListComboBox::AddObj(CExBaseObject *pObj)
{
	if (!CanAdd(pObj))
	{
		return -1;
	}

	long nIndex = 0;

	if (m_bAddName)
	{
		nIndex = AddString(pObj->m_strName);
	}
	else
	{
		nIndex = AddString(pObj->m_strID);
	}

	SetItemData(nIndex, (DWORD)pObj);

	return nIndex;
}


long CExBaseListComboBox::InsertObj(long nIndex, CExBaseObject *pObj)
{
	if (!CanAdd(pObj))
	{
		return -1;
	}

	long nCurrIndex = 0;
	
	if (m_bAddName)
	{
		nCurrIndex = InsertString(nIndex, pObj->m_strName);
	}
	else
	{
		nCurrIndex = InsertString(nIndex, pObj->m_strID);
	}

	SetItemData(nCurrIndex, (DWORD)pObj);

	return nCurrIndex;
}

BEGIN_MESSAGE_MAP(CExBaseListComboBox, CComboBox)
	ON_MESSAGE(WM_FILTER_EXBASELIST, &CExBaseListComboBox::OnFilterText)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_RBUTTON_UP_LIST, &CExBaseListComboBox::OnRbtnDelete)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


HRESULT CExBaseListComboBox::OnFilterText(WPARAM wParam, LPARAM lParam)
{
	OnFilterText();

	return 0;
}


HRESULT CExBaseListComboBox::OnRbtnDelete(WPARAM wParam, LPARAM lParam)
{
	OnRbtnDelete();

	return 0;
}


HBRUSH CExBaseListComboBox::OnCtlColor(CDC* pDC,CWnd *pWnd, UINT nCtlColor)
{
	if ( nCtlColor == CTLCOLOR_EDIT )
	{
		if ( m_Edit.GetSafeHwnd() == NULL )
		{
			m_Edit.SubclassWindow( pWnd->GetSafeHwnd() );
			m_Edit.m_pCmoboBox = this;
		}
	}
	else if (nCtlColor == CTLCOLOR_LISTBOX)
	{
		if (m_ListBox.GetSafeHwnd() == NULL && m_bUseComboBoxList)
		{
			m_ListBox.SubclassWindow(pWnd->GetSafeHwnd());
			m_ListBox.m_pCmoboBox = this;
		}
	}

	return CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	return NULL;
}

void CExBaseListComboBox::OnFilterText()
{
	if (!m_bUseFilter)
	{
		return;
	}

	if (!::IsWindow(m_Edit.m_hWnd))
	{
		return;
	}

	if (!GetDroppedState())
	{
		ShowDropDown(TRUE);
	}

	CString strText = m_Edit.m_strText;

	if (strText.GetLength() == 0)
	{
		m_pList->Filter(strText, FILTERMODE_CLEAR);
	}
	else
	{
		m_pList->Filter(strText);
	}

	ShowBaseList();
	m_Edit.ShowText();

	HCURSOR  hCursor = ::GetCursor();

	if (hCursor != NULL)
	{
		SetCursor(hCursor);
	}
	else
	{
		SetCursor(::LoadCursor(NULL, IDC_HAND));
	}

// 	if (m_ListBox.IsWindowVisible())
// 	{
// 		CRect rc;
// 		m_ListBox.GetWindowRect(&rc);
// 		::SetWindowPos(m_ListBox.m_hWnd, HWND_BOTTOM, rc.left, rc.right, rc.Width(), rc.Height(), SWP_NOMOVE);
// 	}
}

void CExBaseListComboBox::OnRbtnDelete()
{

}

void CExBaseListComboBox::OnDestroy()
{
	CComboBox::OnDestroy();

	UnsubclassChildWindow();
}
