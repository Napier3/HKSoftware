// GridHexEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "TCHAR.h"
#include "GridHexEdit.h"
#include "GridDefine.h"
#include "..\API\HexTransApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridHexEdit

CGridHexEdit::CGridHexEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
						   int nRow, int nColumn, CString sInitText, UINT nFirstChar, int nMaxLen,
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

	Init(nMaxLen);
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


CGridHexEdit::~CGridHexEdit()
{
}


BEGIN_MESSAGE_MAP(CGridHexEdit, CMFCMaskedEdit)
ON_WM_KILLFOCUS()
	ON_WM_CHAR()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_CREATE()
ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// CGridHexEdit 消息处理程序

void CGridHexEdit::Init(long nLength)
{
	CString strMask=_T("  "), strInputTemplate = _T("0X"), strText2=_T("0X");
	long nIndex = 0;

	for (nIndex=0; nIndex<nLength; nIndex++)
	{
		strMask = strMask + _T("AA");
		strInputTemplate = strInputTemplate + _T("__");
		strText2 = strText2 + _T("00");
	}

	EnableMask((LPCTSTR)strMask, // The mask string
		(LPCTSTR)strInputTemplate, // Literal, "_" char = character entry
		_T('0')); // Backspace replace char
	SetValidChars(_T("1234567890ABCDEFabcdef")); // Valid string characters


	SetWindowText(strText2);
	m_nLength *= 2;
}

void CGridHexEdit::InitEx(long nLength)
{
	CString strMask=_T("  "), strInputTemplate = _T("0X"), strText2=_T("0X");
	long nIndex = 0;

	for (nIndex=0; nIndex<nLength; nIndex++)
	{
		strMask = strMask + _T("A");
		strInputTemplate = strInputTemplate + _T("_");
		strText2 = strText2 + _T("0");
	}

	EnableMask((LPCTSTR)strMask, // The mask string
		(LPCTSTR)strInputTemplate, // Literal, "_" char = character entry
		_T('0')); // Backspace replace char
	SetValidChars(_T("1234567890ABCDEFabcdef")); // Valid string characters


	SetWindowText(strText2);
	m_nLength = nLength;
}

// 
// void CGridHexEdit::SetValue(DWORD dwValue)
// {
// 	CString strText;
// 	CString strFormat(_T("0x%0%dX"), m_nLength);
// 	strText.Format(strFormat, dwValue);
// 	SetWindowText(strText);
// }

void CGridHexEdit::SetValue(DWORD dwValue)
{
	char pszHex[20];
	ValueToHex(dwValue, pszHex);
	SetWindowText(CString(pszHex));
}

void CGridHexEdit::GetValue(DWORD &dwValue)
{
	BYTE byteValue[10];
	char *pszHex = NULL;
	CString strHex;
	GetWindowText(strHex);
	long nLen = strHex.GetLength();

	if (nLen % 2 == 1)
	{
		strHex = _T("0") + strHex;
	}

	CString_to_char(strHex, &pszHex);
	
	nLen = HexToValue(pszHex, byteValue);

	if (nLen > 4)
	{
		nLen = 4;
	}

	long nIndex = 0;
	dwValue = 0;

	for (nIndex=0; nIndex<nLen; nIndex++)
	{
		dwValue = dwValue * 256 + byteValue[nIndex];
	}

	delete pszHex;
}

void CGridHexEdit::SetValue(WORD wValue)
{
	char pszHex[20];
	ValueToHex(wValue, pszHex);
	SetWindowText(CString(pszHex));
}

void CGridHexEdit::GetValue(WORD &wValue)
{
	DWORD dwValue = 0;
	GetValue(dwValue);
	wValue = (WORD)dwValue;
}

void CGridHexEdit::SetValue(BYTE byteValue)
{
	char pszHex[20];
	ValueToHex(byteValue, pszHex);
	SetWindowText(CString(pszHex));
}

void CGridHexEdit::GetValue(BYTE &byteValue)
{
	DWORD dwValue = 0;
	GetValue(dwValue);
	byteValue = (BYTE)dwValue;
}
// 
// void CGridHexEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
// {
// 	if ('a' <= nChar && nChar <= 'z')
// 	{
// 		nChar += 'A' - 'a';
// 	}
// 
// 	CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
// }


// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CGridHexEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
void CGridHexEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
void CGridHexEdit::OnKillFocus(CWnd* pNewWnd)
{
    CMFCMaskedEdit::OnKillFocus(pNewWnd);
    EndEdit();
}

void CGridHexEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
	if(nChar == VK_DOWN||nChar == VK_UP)
	{
	}
	else if ((nChar >= '0' && nChar <= '9') || ('a' <= nChar && nChar <= 'z') || ('A' <= nChar && nChar <= 'Z'))
	{
		if ('a' <= nChar && nChar <= 'z')
		{
			nChar += 'A' - 'a';
		}

		CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if(nChar == VK_LEFT || nChar == VK_RIGHT)
	{
	}
	else
	{	
// 		CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
// 		CString str;
// 		GetWindowText( str );
// 		
// 		CWindowDC dc(this);
// 		CFont *pFontDC = dc.SelectObject(GetFont());
// 		CSize size = dc.GetTextExtent( str );
// 		dc.SelectObject( pFontDC );
// 		
// 		size.cx += 5;                   // add some extra buffer
// 		
// 		// Get client rect
// 		CRect rect, parentrect;
// 		GetClientRect( &rect );
// 		GetParent()->GetClientRect( &parentrect );
// 		
// 		// Transform rect to parent coordinates
// 		ClientToScreen( &rect );
// 		GetParent()->ScreenToClient( &rect );
// 		
// 		// Check whether control needs to be resized
// 		// and whether there is space to grow
// 		if (size.cx > rect.Width())
// 		{
// 			if( size.cx + rect.left < parentrect.right )
// 				rect.right = rect.left + size.cx;
// 			else
// 				rect.right = parentrect.right;
// 			MoveWindow( &rect );
// 		}
	}
	
}

////////////////////////////////////////////////////////////////////////////
// CGridHexEdit overrides

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CGridHexEdit::PreTranslateMessage(MSG* pMsg) 
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
void CGridHexEdit::PostNcDestroy() 
{
	CMFCMaskedEdit::PostNcDestroy();
	
    delete this;	
}

////////////////////////////////////////////////////////////////////////////
// CGridHexEdit implementation

void CGridHexEdit::EndEdit()
{
    CString str;
    GetWindowText(str);

	CString str2 = str.Left(2);
	str2.MakeLower();
	if (str2 != _T("0x"))
	{
		str = _T("0X") + str;
	}
	
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


int CGridHexEdit::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return 1;//CMFCMaskedEdit::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CGridBinaryEdit::CGridBinaryEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
								 int nRow, int nColumn, CString sInitText, UINT nFirstChar, int nMaxLen,
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

	Init(nMaxLen);
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


CGridBinaryEdit::~CGridBinaryEdit()
{
}


BEGIN_MESSAGE_MAP(CGridBinaryEdit, CMFCMaskedEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// CGridBinaryEdit 消息处理程序

void CGridBinaryEdit::Init(long nLength)
{
	CString strMask=_T(""), strInputTemplate = _T(""), strText2=_T("");
	long nIndex = 0;

	for (nIndex=0; nIndex<nLength; nIndex++)
	{
		strMask = strMask + _T("A");
		strInputTemplate = strInputTemplate + _T("_");
		strText2 = strText2 + _T("0");
	}

	EnableMask((LPCTSTR)strMask, // The mask string
		(LPCTSTR)strInputTemplate, // Literal, "_" char = character entry
		_T('0')); // Backspace replace char
	SetValidChars(_T("10")); // Valid string characters


	SetWindowText(strText2);
}

// 
// void CGridBinaryEdit::SetValue(DWORD dwValue)
// {
// 	CString strText;
// 	CString strFormat(_T("0x%0%dX"), m_nLength);
// 	strText.Format(strFormat, dwValue);
// 	SetWindowText(strText);
// }

// void CGridBinaryEdit::SetValue(DWORD dwValue)
// {
// 	char pszHex[20];
// 	ValueToHex(dwValue, pszHex);
// 	SetWindowText(CString(pszHex));
// }
// 
// void CGridBinaryEdit::GetValue(DWORD &dwValue)
// {
// 	BYTE byteValue[10];
// 	char *pszHex = NULL;
// 	CString strHex;
// 	GetWindowText(strHex);
// 	long nLen = strHex.GetLength();
// 
// 	if (nLen % 2 == 1)
// 	{
// 		strHex = _T("0") + strHex;
// 	}
// 
// 	CString_to_char(strHex, &pszHex);
// 	
// 	nLen = HexToValue(pszHex, byteValue);
// 
// 	if (nLen > 4)
// 	{
// 		nLen = 4;
// 	}
// 
// 	long nIndex = 0;
// 	dwValue = 0;
// 
// 	for (nIndex=0; nIndex<nLen; nIndex++)
// 	{
// 		dwValue = dwValue * 256 + byteValue[nIndex];
// 	}
// 
// 	delete pszHex;
// }

// void CGridBinaryEdit::SetValue(WORD wValue)
// {
// 	char pszHex[20];
// 	ValueToHex(wValue, pszHex);
// 	SetWindowText(CString(pszHex));
// }
// 
// void CGridBinaryEdit::GetValue(WORD &wValue)
// {
// 	DWORD dwValue = 0;
// 	GetValue(dwValue);
// 	wValue = (WORD)dwValue;
// }
// 
// void CGridBinaryEdit::SetValue(BYTE byteValue)
// {
// 	char pszHex[20];
// 	ValueToHex(byteValue, pszHex);
// 	SetWindowText(CString(pszHex));
// }
// 
// void CGridBinaryEdit::GetValue(BYTE &byteValue)
// {
// 	DWORD dwValue = 0;
// 	GetValue(dwValue);
// 	byteValue = (BYTE)dwValue;
// }
// 
// void CGridBinaryEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
// {
// 	if ('a' <= nChar && nChar <= 'z')
// 	{
// 		nChar += 'A' - 'a';
// 	}
// 
// 	CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
// }


// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CGridBinaryEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
void CGridBinaryEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
void CGridBinaryEdit::OnKillFocus(CWnd* pNewWnd)
{
	CMFCMaskedEdit::OnKillFocus(pNewWnd);
	EndEdit();
}

void CGridBinaryEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
	if(nChar == VK_DOWN||nChar == VK_UP)
	{
	}
	else if (nChar == '0' || nChar == '1')
	{
		CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if(nChar == VK_LEFT || nChar == VK_RIGHT)
	{
	}
	else
	{	
		// 		CMFCMaskedEdit::OnChar(nChar, nRepCnt, nFlags);
		// 		CString str;
		// 		GetWindowText( str );
		// 		
		// 		CWindowDC dc(this);
		// 		CFont *pFontDC = dc.SelectObject(GetFont());
		// 		CSize size = dc.GetTextExtent( str );
		// 		dc.SelectObject( pFontDC );
		// 		
		// 		size.cx += 5;                   // add some extra buffer
		// 		
		// 		// Get client rect
		// 		CRect rect, parentrect;
		// 		GetClientRect( &rect );
		// 		GetParent()->GetClientRect( &parentrect );
		// 		
		// 		// Transform rect to parent coordinates
		// 		ClientToScreen( &rect );
		// 		GetParent()->ScreenToClient( &rect );
		// 		
		// 		// Check whether control needs to be resized
		// 		// and whether there is space to grow
		// 		if (size.cx > rect.Width())
		// 		{
		// 			if( size.cx + rect.left < parentrect.right )
		// 				rect.right = rect.left + size.cx;
		// 			else
		// 				rect.right = parentrect.right;
		// 			MoveWindow( &rect );
		// 		}
	}

}

////////////////////////////////////////////////////////////////////////////
// CGridBinaryEdit overrides

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CGridBinaryEdit::PreTranslateMessage(MSG* pMsg) 
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
void CGridBinaryEdit::PostNcDestroy() 
{
	CMFCMaskedEdit::PostNcDestroy();

	delete this;	
}

////////////////////////////////////////////////////////////////////////////
// CGridBinaryEdit implementation

void CGridBinaryEdit::EndEdit()
{
	CString str;
	GetWindowText(str);

	// 	CString str2 = str.Left(2);
	// 	str2.MakeLower();
	// 	if (str2 != _T("0x"))
	// 	{
	// 		str = _T("0X") + str;
	// 	}

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


int CGridBinaryEdit::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return 1;//CMFCMaskedEdit::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
