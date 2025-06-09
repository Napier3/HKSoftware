// BaseListComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "FilterTextComboBox.h"
#include "..\API\FileApi.h"
#include "..\DataMngr\DataMngrGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// 
// //////////////////////////////////////////////////////////////////////////
// // CFilterTextListBox
// 
// IMPLEMENT_DYNAMIC(CFilterTextListBox, CListBox)
// 
// CFilterTextListBox::CFilterTextListBox()
// {
// 	m_pCmoboBox = NULL;
// }
// 
// CFilterTextListBox::~CFilterTextListBox()
// {
// }
// 
// 
// BEGIN_MESSAGE_MAP(CFilterTextListBox, CListBox)
// 	ON_WM_RBUTTONUP()
// END_MESSAGE_MAP()
// 
// 
// void CFilterTextListBox::OnRButtonUp(UINT nFlags, CPoint point)
// {
// 	// TODO: 在此添加消息处理程序代码和/或调用默认值
// 
// 	CListBox::OnRButtonUp(nFlags, point);
// 
// 	if (m_pCmoboBox != NULL)
// 	{
// 		m_pCmoboBox->PostMessage(WM_DELETE_FILTER_TEXT, 0, 0);
// 	}
// }
// 
// //////////////////////////////////////////////////////////////////////////
// //
// 
// IMPLEMENT_DYNAMIC(CFilterTexEdit, CEdit)
// 
// CFilterTexEdit::CFilterTexEdit()
// {
// 	m_nCurrPosBegin = 0;
// 	m_nCurrPosEnd = 0;
// }
// 
// CFilterTexEdit::~CFilterTexEdit()
// {
// }
// 
// BEGIN_MESSAGE_MAP(CFilterTexEdit, CEdit)
// 	ON_WM_CHAR()
// 	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CFilterTexEdit::OnEnKillfocus)
// END_MESSAGE_MAP()
// 
// 
// void CFilterTexEdit::OnEnKillfocus()
// {
// 	GetSel(m_nCurrPosBegin, m_nCurrPosEnd);
// }
// 
// void  CFilterTexEdit::SetSelText(const CString &strText)
// {
// 	SetSel(m_nCurrPosBegin, m_nCurrPosEnd,  TRUE);
// 	ReplaceSel(strText);
// }

//////////////////////////////////////////////////////////////////////////
// CFilterTextComboBox
CFilterTextComboBox::CFilterTextComboBox()
{

}

CFilterTextComboBox::~CFilterTextComboBox()
{
}

void CFilterTextComboBox::InitFilterText(CFilterTextMngr *pFilterTextMngr)
{
	ShowBaseList(pFilterTextMngr);
}

void CFilterTextComboBox::AddFilterText(CFilterText *pText)
{
	CString strText = pText->m_strName;
	GetAddString(strText);
	
	long nIndex = AddString(strText);
	SetItemDataPtr(nIndex, pText);
}

void CFilterTextComboBox::GetAddString(CString &strText)
{
	if (m_strPrevfixText.GetLength() > 0)
	{
		CString strRet = strText;
		strRet.MakeLower();

		if (strRet.Find(m_strPrevfixText) == 0)
		{
			strText = strText.Mid(m_strPrevfixText.GetLength());
		}
	}
}

CString CFilterTextComboBox::GetAddString2(const CString &strText)
{
	if (m_strPrevfixText.GetLength() > 0)
	{
		CString strRet = strText;
		strRet.MakeLower();
		
		if (strRet.Find(m_strPrevfixText) == 0)
		{
			strRet = strText.Mid(m_strPrevfixText.GetLength());
		}

		return strRet;
	}
	else
	{
		return strText;
	}
}

long CFilterTextComboBox::AddObj(CExBaseObject *pObj)
{
	if (!CanAdd(pObj))
	{
		return -1;
	}

	long nIndex = 0;

	if (m_bAddName)
	{
		nIndex = AddString(GetAddString2(pObj->m_strName));
	}
	else
	{
		nIndex = AddString(GetAddString2(pObj->m_strID));
	}

	SetItemData(nIndex, (DWORD)pObj);

	return nIndex;
}


long CFilterTextComboBox::InsertObj(long nIndex, CExBaseObject *pObj)
{
	if (!CanAdd(pObj))
	{
		return -1;
	}

	long nCurrIndex = 0;

	if (m_bAddName)
	{
		nCurrIndex = InsertString(nIndex, GetAddString2(pObj->m_strName));
	}
	else
	{
		nCurrIndex = InsertString(nIndex, GetAddString2(pObj->m_strID));
	}

	SetItemData(nCurrIndex, (DWORD)pObj);

	return nCurrIndex;
}


void CFilterTextComboBox::SelectFilterText(CFilterText *pText)
{
	long nIndex = 0, nFind = -1;
	long nCount = GetCount();

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if ((CFilterText*)GetItemDataPtr(nIndex) == pText)
		{
			nFind = nIndex;
			break;
		}
	}

	if (nFind != -1)
	{
		SetCurSel(nFind);
	}
}


void CFilterTextComboBox::SaveFilterText()
{
	CFilterTextMngr *pFilterTextMngr = (CFilterTextMngr*)m_pList;
	pFilterTextMngr->SaveXmlFile();
}

CFilterText* CFilterTextComboBox::AddFilterText(const CString &strFilterText)
{
	CFilterText *pNew = NULL;
	pNew = (CFilterText*)m_pList->FindByID(strFilterText);

	if (pNew == NULL)
	{
		CFilterTextMngr *pFilterTextMngr = (CFilterTextMngr*)m_pList;
		pNew = pFilterTextMngr->AddText(strFilterText);
		AddFilterText(pNew);
		SaveFilterText();
	}

	return pNew;
}

BOOL CFilterTextComboBox::GetFilterText(CString &strFilterText)
{
	ASSERT (m_pList != NULL);

	if (m_pList == NULL)
	{
		return FALSE;
	}

	GetWindowText(strFilterText);
	strFilterText.Trim();

	if (strFilterText.GetLength() > 0)
	{
		AddFilterText(strFilterText);
// 		if (m_pList->FindByID(strFilterText) == NULL)
// 		{
// 			CFilterTextMngr *pFilterTextMngr = (CFilterTextMngr*)m_pList;
// 			CExBaseObject *pNew = pFilterTextMngr->AddText(strFilterText);
// 			AddObj(pNew);
// 			SaveFilterText();
// 		}
	}

	if (m_strPrevFilterText == strFilterText)
	{
		return FALSE;
	}
	else
	{
		m_strPrevFilterText = strFilterText;
		return TRUE;
	}
}

CFilterText* CFilterTextComboBox::GetFilterText(BOOL bBringToTop)
{
	long nIndex = GetCurSel();

	if (nIndex == CB_ERR)
	{
		return NULL;
	}

	CFilterText *pFind = ((CFilterText*)GetItemDataPtr(nIndex));

	if (pFind != NULL)
	{
		((CFilterTextMngr*)m_pList)->BringToHead(pFind);
		((CFilterTextMngr*)m_pList)->SaveXmlFile();

	}

	return pFind;
}

// BEGIN_MESSAGE_MAP(CFilterTextComboBox, CExBaseListComboBox)
// 	ON_MESSAGE(WM_DELETE_FILTER_TEXT, &CFilterTextComboBox::OnFilterTextDelete)
// 	ON_WM_CTLCOLOR()
// END_MESSAGE_MAP()


void CFilterTextComboBox::OnRbtnDelete()
{
	long nIndex = GetCurSel();

	//ShowDropDown(FALSE);

	if (nIndex == CB_ERR)
	{
		return ;
	}

	CFilterText *pSel = (CFilterText *)GetItemDataPtr(nIndex);

	if (pSel == NULL)
	{
		return ;
	}

	DeleteString(nIndex);
	m_pList->Delete(pSel);
	SaveFilterText();
}

BOOL CFilterTextComboBox::GetCurrSelFilterText(CString &strFilterText)
{
	if (GetCount() == 0)
	{
		return FALSE;
	}

	long nIndex = GetCurSel();

	if (nIndex == CB_ERR)
	{
		return FALSE;
	}

	CFilterText *pSel = (CFilterText *)GetItemDataPtr(nIndex);

	if (pSel == NULL || ((DWORD)pSel == 0XFFFFFFFF))
	{
		return FALSE;
	}

	strFilterText = pSel->m_strName;
	return TRUE;
}
