// ExBaseListComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "ExBaseListComboBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//对于不同逻辑设备下的数据集，可能存在数据集名称ID一致，因此显示时需要加上逻辑设备的信息
void ex_InsertChildreComboBox(CExBaseList *pDatas, QComboBox *pComboBox, BOOL bAddParentNameID, long nSel)
{
	pComboBox->clear();

	if (pDatas == NULL)
	{
		return;
	}

	CExBaseObject *pObj = NULL;
	POS pos = pDatas->GetHeadPosition();
	CString strText;

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);

		//2022-9-28  lijunqing 设置Item关联的对象
		if (bAddParentNameID)
		{
			CExBaseObject *pParent = (CExBaseObject *)pObj->GetParent();
			
			if (pParent->m_strName.GetLength() > 0)
			{
				strText = pParent->m_strName + _T("$") + pObj->m_strName;
			}
			else
			{
				strText = pParent->m_strID + _T("$") + pObj->m_strName;
			}
		}
		else
		{
			strText = pObj->m_strName;
		}

		pComboBox->addItem(strText, QVariant::fromValue((void*)pObj) );
	}

	if (nSel >= 0)
	{
		pComboBox->setCurrentIndex(0);
	}
}

CExBaseObject* ex_ComboBox_GetSelObj(QComboBox *pComboBox, long nIndex)
{
	QVariant v = pComboBox->itemData(nIndex);
	return (CExBaseObject*)v.value<void*>();
}

CExBaseObject* ex_ComboBox_GetSelObj(QComboBox *pComboBox)
{
	long nIndex = pComboBox->currentIndex();
	return ex_ComboBox_GetSelObj(pComboBox, nIndex);
}

#include <QAbstractItemView>
//2022-11-3  lijunqing
void ex_ComboBox_adjustItemWidth(QComboBox *pComboBox)
{
	int max_len=0;

	for(int idx=0;idx < pComboBox->count();idx++)
	{
		if(max_len < pComboBox->itemText(idx).length())
			max_len = pComboBox->itemText(idx).length();
	}

	int pt_val = pComboBox->font().pointSize();//获取字体的磅值

	if (pt_val <= 0)
	{
		pt_val = 7;
	}

	pComboBox->view()->setFixedWidth(max_len*pt_val*1.67);//（字符数*每个字符的宽度(磅)*1.67）个像素
}

//////////////////////////////////////////////////////////////////////////
// CExBaseListComboBoxList
/*
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
*/

//////////////////////////////////////////////////////////////////////////
// CExBaseListComboBox

BOOL CExBaseListComboBox::Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	AddObj(pData);

	return TRUE;
}

BOOL CExBaseListComboBox::Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate)
{
// 	long nIndex = FindIndex(pData);
// 	long nSelIndex = GetCurSel();
// 	DeleteString(nIndex);
// 	InsertObj(nIndex, pData);
// 
// 	if (nSelIndex == nIndex)
// 	{
// 		SetCurSel(nIndex);
// 	}

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

CExBaseListComboBox::CExBaseListComboBox(QWidget *parent)
#ifdef _PSX_QT_LINUX_
: QScrollComboBox(parent)
#else
: QComboBox(parent)
#endif
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
// 	if ( m_Edit.GetSafeHwnd() != NULL )
// 	{
// 		m_Edit.UnsubclassWindow();
// 	}
// 
// 	if ( m_ListBox.GetSafeHwnd() != NULL )
// 	{
// 		m_ListBox.UnsubclassWindow();
// 	}
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
	clear();

	if (m_pList == NULL)
	{
		return;
	}

	if (m_bAddEmptyString)
	{
		addItem(_T(""),QVariant::fromValue((void*)NULL));	
		//		SetItemDataPtr(nIndex, NULL);
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
	long nCount = count();
	long nIndex = 0;
	long nFindIndex = -1;

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

	int nCount = GetCount();
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

	if (nSel <0)
	{
		return NULL;
	}

	return (CExBaseObject*)GetItemData(nSel);
}

int CExBaseListComboBox::GetCurSel()
{
	return currentIndex();
}

int CExBaseListComboBox::DeleteString(UINT nIndex)
{
	removeItem(nIndex);
	return count()-1;
}

int CExBaseListComboBox::AddString(CString &lpszString)
{
	addItem(lpszString);
	return count()-1;
}

int CExBaseListComboBox::InsertString(int nIndex, CString &lpszString)
{
	insertItem(nIndex, lpszString);
	return count()-1;
}

void CExBaseListComboBox::SetItemData(int nIndex, long nData)
{
	QVariant var;
	var = (int)nData;
	setItemData(nIndex, var);
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
		CExBaseObject *p = (CExBaseObject*)GetItemData(nIndex);

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

void CExBaseListComboBox::OnFilterText()
{
// 	if (!m_bUseFilter)
// 	{
// 		return;
// 	}
// 
// 	if (!::IsWindow(m_Edit.m_hWnd))
// 	{
// 		return;
// 	}
// 
// 	if (!GetDroppedState())
// 	{
// 		ShowDropDown(TRUE);
// 	}
// 
// 	CString strText = m_Edit.m_strText;
// 
// 	if (strText.GetLength() == 0)
// 	{
// 		m_pList->Filter(strText, FILTERMODE_CLEAR);
// 	}
// 	else
// 	{
// 		m_pList->Filter(strText);
// 	}
// 
// 	ShowBaseList();
// 	m_Edit.ShowText();
// 
// 	HCURSOR  hCursor = ::GetCursor();
// 
// 	if (hCursor != NULL)
// 	{
// 		SetCursor(hCursor);
// 	}
// 	else
// 	{
// 		SetCursor(::LoadCursor(NULL, IDC_HAND));
// 	}
}

void CExBaseListComboBox::OnRbtnDelete()
{

}


DWORD CExBaseListComboBox::GetItemData(long nIndex)
{
	QVariant v = itemData(nIndex);
	return v.value<DWORD>();
}

void CExBaseListComboBox::SetCurSel(int index)
{
	setCurrentIndex(index);
}

