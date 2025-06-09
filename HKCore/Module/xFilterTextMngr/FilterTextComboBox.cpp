// ExBaseListComboBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FilterTextComboBox.h"


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

void CFilterTextComboBox::SaveFilterText()
{
	CFilterTextMngr *pFilterTextMngr = (CFilterTextMngr*)m_pList;
	pFilterTextMngr->SaveXmlFile();
}

BOOL CFilterTextComboBox::GetFilterText(CString &strFilterText)
{
	ASSERT (m_pList != NULL);

	if (m_pList == NULL)
	{
		return FALSE;
	}

	GetWindowText(strFilterText);

	if (strFilterText.GetLength() > 0)
	{
		if (m_pList->FindByID(strFilterText) == NULL)
		{
			CFilterTextMngr *pFilterTextMngr = (CFilterTextMngr*)m_pList;
			CExBaseObject *pNew = pFilterTextMngr->AddText(strFilterText);
			AddObj(pNew);
			SaveFilterText();
		}
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

BEGIN_MESSAGE_MAP(CFilterTextComboBox, CExBaseListComboBox)
	ON_CONTROL_REFLECT(CBN_SELENDOK, &CFilterTextComboBox::OnCbnSelendok)
	ON_WM_KEYUP()
	ON_WM_GETDLGCODE()
END_MESSAGE_MAP()

void CFilterTextComboBox::OnCbnSelendok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CFilterTextComboBox::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN)
	{
		GetParent()->PostMessage(WM_FILTERTEXT_END_EDIT, 0, 0);
	}

	CExBaseListComboBox::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CFilterTextComboBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_GETDLGCODE)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			GetParent()->PostMessage(WM_FILTERTEXT_END_EDIT, 0, 0);
		}
	}

	return CExBaseListComboBox::PreTranslateMessage(pMsg);
}

UINT CFilterTextComboBox::OnGetDlgCode()
{
	//CLogPrint::LogString(LOGLEVEL_TRACE, _T("OnGetDlgCode"));
	return DLGC_WANTALLKEYS;
// 	UINT nKey = CExBaseListComboBox::OnGetDlgCode();
// 
// 	if (nKey == DLGC_WANTALLKEYS)
// 	{
// 		GetParent()->PostMessage(WM_FILTERTEXT_END_EDIT, 0, 0);
// 	}
// 
// 	return nKey;
}
