// GridDateTimeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "GridDateTimeCtrl.h"


// CGridDateTimeCtrl

CGridDateTimeCtrl::CGridDateTimeCtrl(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
						   int nRow, int nColumn, CString sInitText, UINT nFirstChar,
						   CXGridCtrlBase_MsgFunc *pMsgFunc)
{
	m_pMsgFunc = pMsgFunc;
	m_sInitText     = sInitText;
	m_nRow          = nRow;
	m_nColumn       = nColumn;
	m_nLastChar     = 0; 
	m_bExitOnArrows = (nFirstChar != VK_LBUTTON);    // If mouse click brought us here,
	// then no exit on arrows
	WPARAM wPara = (nRow << 16) + nColumn;

	DWORD dwEditStyle = WS_BORDER|WS_CHILD|WS_VISIBLE
		| dwStyle;
	if (!Create(dwEditStyle, rect, pParent, nID)) return;

	if (m_pMsgFunc != NULL)
	{
		SetFont(m_pMsgFunc->msg_OnGetFont());
		m_pMsgFunc->msg_OnFillComboBox(wPara, (LPARAM)this);
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
	case VK_RETURN: 
	case VK_BACK: 
	case VK_DOWN: 
	case VK_UP:   
	case VK_RIGHT:
	case VK_LEFT:  
	case VK_NEXT:  
	case VK_PRIOR: 
	case VK_HOME:
	case VK_SPACE:
	case VK_END:
		break;
	default:
		break;
	}

// 	if (::IsWindow( GetSafeHwnd() ))
// 	{
// 		SendMessage(WM_CHAR, nFirstChar);
// 	}
}


CGridDateTimeCtrl::~CGridDateTimeCtrl()
{
}


BEGIN_MESSAGE_MAP(CGridDateTimeCtrl, CDateTimeCtrl)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
	ON_NOTIFY_REFLECT(DTN_DATETIMECHANGE, &CGridDateTimeCtrl::OnDtnDatetimechange)
END_MESSAGE_MAP()



// CGridDateTimeCtrl 消息处理程序

void CGridDateTimeCtrl::Init()
{
	m_strDateTimeFormat = _T("yyyy-MM-dd HH:mm:ss");//strFormart;
	SetFormat(m_strDateTimeFormat);
}


CString CGridDateTimeCtrl::GeTimeText()
{
	COleDateTime timeDest;
	GetTime(timeDest);
	
	CString strData;

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("chs"));
#endif

	strData = timeDest.Format(m_strDateTimeFormat);
	ASSERT(strData != _T(""));

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("eng"));
#endif

	return strData;
}

////////////////////////////////////////////////////////////////////////////
// CGridDateTimeCtrl overrides

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CGridDateTimeCtrl::PreTranslateMessage(MSG* pMsg) 
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
void CGridDateTimeCtrl::PostNcDestroy() 
{
		CDateTimeCtrl::PostNcDestroy();
	
    delete this;	
}

////////////////////////////////////////////////////////////////////////////
// CGridDateTimeCtrl implementation
// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CGridDateTimeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_DOWN  || nChar == VK_UP)
	{
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
	
    CDateTimeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Need to keep a lookout for Tabs, Esc and Returns. These send a 
// "KeyUp" message, but no "KeyDown". That's why I didn't put their
// code in OnKeyDown. (I will never understand windows...)
void CGridDateTimeCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (   nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE
		|| nChar == VK_DOWN  || nChar == VK_UP
		|| nChar == VK_RIGHT || nChar == VK_LEFT)
		
	{
		m_nLastChar = nChar;
		GetParent()->SetFocus();    // This will destroy this window
		return;
	}
	
	CDateTimeCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

// As soon as this edit loses focus, kill it.
void CGridDateTimeCtrl::OnKillFocus(CWnd* pNewWnd)
{
    CDateTimeCtrl::OnKillFocus(pNewWnd);
    EndEdit();
}

void CGridDateTimeCtrl::EndEdit()
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


void CGridDateTimeCtrl::OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult)
{
// 	COleDateTime timeDest;
// 	GetTime(timeDest);
// 	
// 	CString strData;
// 
// #ifdef UNICODE
// 	_wsetlocale(LC_ALL,_T("chs"));
// #endif
// 
// 	strData = timeDest.Format(m_strDateTimeFormat);
// 	ASSERT(strData != _T(""));
// 
// 	if (m_pResultWndInterface != NULL)
// 	{
// 		m_pResultWndInterface->OnResultDataChanged(strData);
// 	}
// 
// #ifdef UNICODE
// 	_wsetlocale(LC_ALL,_T("eng"));
// #endif
	
	*pResult = 0;
}
