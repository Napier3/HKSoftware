// GridMacEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "GridMacEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CGridMacEdit

CGridMacEdit::CGridMacEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
						   int nRow, int nColumn, CString sInitText, UINT nFirstChar,
						   CXGridCtrlBase_MsgFunc *pMsgFunc)
{
	m_pMsgFunc = pMsgFunc;
	EnableGetMaskedCharsOnly(FALSE);
	m_sInitText     = sInitText;
	m_nRow          = nRow;
	m_nColumn       = nColumn;
	m_nLastChar     = 0; 
	m_bExitOnArrows = (nFirstChar != VK_LBUTTON);    // If mouse click brought us here,
	// then no exit on arrows

	DWORD dwEditStyle = WS_BORDER|WS_CHILD|WS_VISIBLE| ES_AUTOHSCROLL //|ES_MULTILINE
		| dwStyle;
	if (!Create(dwEditStyle, rect, pParent, nID)) return;

	if (m_pMsgFunc != NULL)
	{
		SetFont(m_pMsgFunc->msg_OnGetFont());
	}
	else
	{
		SetFont(pParent->GetFont());
	}

	Init();
	SetWindowText(sInitText);
	SetFocus();

	switch (nFirstChar)
	{
	case VK_LBUTTON: 
	case VK_RETURN:   SetSel((int)_tcslen(m_sInitText), -1); return;
	case VK_BACK:     SetSel((int)_tcslen(m_sInitText), -1); break;
	case VK_DOWN: 
	case VK_UP:   
	case VK_RIGHT:
	case VK_LEFT:  
	case VK_NEXT:  
	case VK_PRIOR: 
	case VK_HOME:
	case VK_SPACE:
	case VK_END:      SetSel(0,-1); return;
	default:          SetSel(0,-1);
	}

	if (::IsWindow( GetSafeHwnd() ))
	{
		SendMessage(WM_CHAR, nFirstChar);
	}
}


CGridMacEdit::~CGridMacEdit()
{
}


BEGIN_MESSAGE_MAP(CGridMacEdit, CMFCMaskedEdit)
ON_WM_KILLFOCUS()
	ON_WM_CHAR()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_CREATE()
ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// CGridMacEdit 消息处理程序

void CGridMacEdit::Init()
{
	CString strMask=_T("  "), strInputTemplate = _T("0x"), strText2=_T("0x");
	long nIndex = 0;

	strMask = _T("AA AA AA AA AA AA");
	strInputTemplate = _T("__-__-__-__-__-__");
	strText2 = _T("FF-FF-FF-FF-FF-FF");

	EnableMask((LPCTSTR)strMask, // The mask string
		(LPCTSTR)strInputTemplate, // Literal, "_" char = character entry
		_T('0')); // Backspace replace char
	SetValidChars(_T("1234567890ABCDEFabcdef")); // Valid string characters
	SetWindowText(strText2);
}

void CGridMacEdit::GetMacAddr(CString &strMac)
{
	CString strText;
	GetWindowText(strText);
	char pszMac[40];
	char pszMacDest[40];
	CString_to_char(strText, pszMac);
	long nLen = strlen(pszMac);
	long nIndex = 0;
	long nIndexDest = 0;

	for (nIndex=0; nIndex<nLen; nIndex+=2)
	{
		if (pszMac[nIndex+2] == '-')
		{
			pszMacDest[nIndexDest++] = pszMac[nIndex];
			pszMacDest[nIndexDest++] = pszMac[nIndex+1];
			pszMacDest[nIndexDest++] = pszMac[nIndex+2];
		}
		else
		{
			pszMacDest[nIndexDest++] = pszMac[nIndex];
			pszMacDest[nIndexDest++] = pszMac[nIndex+1];
			pszMacDest[nIndexDest++] = '-';
		}
	}

	if (nIndexDest > 0)
	{
		nIndexDest--;
	}

	pszMacDest[nIndexDest] = '\0';
	strMac = pszMacDest;
}

void CGridMacEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if ('a' <= nChar && nChar <= 'z')
	{
		nChar += 'A' - 'a';
	}

	CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
}

CString CGridMacEdit::GetMacText()
{
	CString strText;
	GetWindowText(strText);
	CString strMac;
	long nLen = strText.GetLength();
	long nIndex = 0;

	for (nIndex=0; nIndex<nLen-2; nIndex+=2)
	{
		strMac += strText.Mid(nIndex, 2);
		strMac += _T("-");
	}

	strMac += strText.Mid(nIndex, 2);

	return strMac;
}

////////////////////////////////////////////////////////////////////////////
// CGridMacEdit overrides

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CGridMacEdit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->wParam == VK_RETURN)
	{
		TRACE("\nCGridHexEdit::PreTranslateMessage  VK_RETURN \n");
		//return CWnd::PreTranslateMessage(pMsg);
	}

	// Make sure that the keystrokes continue to the appropriate handlers
	if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP)
	{
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return TRUE;
	}	
	
	// Catch the Alt key so we don't choke if focus is going to an owner drawn button
	if (pMsg->message == WM_SYSCHAR)
		return TRUE;
	
    return CWnd::PreTranslateMessage(pMsg);
}

// Auto delete
void CGridMacEdit::PostNcDestroy() 
{
	CMFCMaskedEdit::PostNcDestroy();
	
    delete this;	
}

////////////////////////////////////////////////////////////////////////////
// CGridMacEdit implementation
// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CGridMacEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//     if ((nChar == VK_PRIOR || nChar == VK_NEXT ||
	//          nChar == VK_DOWN  || nChar == VK_UP   ||
	//          nChar == VK_RIGHT || nChar == VK_LEFT) &&
	//         (m_bExitOnArrows || GetKeyState(VK_CONTROL) < 0))
	if (nChar == VK_DOWN  || nChar == VK_UP)
	{
		//m_nLastChar = nChar;
        //GetParent()->SetFocus();
        return;
    }
	
    if (nChar == VK_ESCAPE) 
    {
        SetWindowText(m_sInitText);    // restore previous text
        m_nLastChar = nChar;
        GetParent()->SetFocus();
        return;
    }
	
    if (nChar == VK_RETURN) 
    {
        //SetWindowText(m_sInitText);    // restore previous text
        m_nLastChar = nChar;
        GetParent()->SetFocus();
        return;
    }
	
    CMFCMaskedEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Need to keep a lookout for Tabs, Esc and Returns. These send a 
// "KeyUp" message, but no "KeyDown". That's why I didn't put their
// code in OnKeyDown. (I will never understand windows...)
void CGridMacEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (   nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE
		|| nChar == VK_DOWN  || nChar == VK_UP
		|| nChar == VK_RIGHT || nChar == VK_LEFT)
		
	{
		m_nLastChar = nChar;
		GetParent()->SetFocus();    // This will destroy this window
		return;
	}
	
	CMFCMaskedEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

// As soon as this edit loses focus, kill it.
void CGridMacEdit::OnKillFocus(CWnd* pNewWnd)
{
    CMFCMaskedEdit::OnKillFocus(pNewWnd);
    EndEdit();
}

void CGridMacEdit::EndEdit()
{
    CString str;
    GetWindowText(str);

    // Send Notification to parent
    GV_DISPINFO dispinfo;
	
    dispinfo.hdr.hwndFrom = GetSafeHwnd();
    dispinfo.hdr.idFrom   = GetDlgCtrlID();
    dispinfo.hdr.code     = GVN_ENDLABELEDIT;
	
    dispinfo.item.mask    = LVIF_TEXT|LVIF_PARAM;
    dispinfo.item.row     = m_nRow;
    dispinfo.item.col     = m_nColumn;
    dispinfo.item.szText  = str;
    dispinfo.item.lParam  = (LPARAM) m_nLastChar; 
  
	if (m_pMsgFunc != NULL)
	{
		LRESULT nResullt = 0;
		m_pMsgFunc->msg_OnEndInPlaceEdit((NMHDR*)&dispinfo, &nResullt);
	}
	else
	{
		CWnd* pOwner = GetOwner();

		if (pOwner)
		{
			if (::IsWindow( pOwner->GetSafeHwnd() ))
			{
				pOwner->SendMessage(WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&dispinfo );
			}
		}
	}
	
    // Close this window (PostNcDestroy will delete this)
    if (::IsWindow( GetSafeHwnd() ))
	{
		PostMessage(WM_CLOSE, 0, 0);
    }
}

int CGridMacEdit::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return 1;//CMFCMaskedEdit::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
