// GridEdit.cpp : implementation file

#include "stdafx.h"
#include "TCHAR.h"
#include "GridEdit.h"
#include "GridDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridEdit

CGridEdit::CGridEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
					 int nRow, int nColumn, CString sInitText, 
					 UINT nFirstChar, GRIDEDIT_FORMAT nFormat,
					 CXGridCtrlBase_MsgFunc *pMsgFunc)
{
	m_pMsgFunc = pMsgFunc;
	m_nFormat       = nFormat;
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

CGridEdit::~CGridEdit()
{

}

BEGIN_MESSAGE_MAP(CGridEdit, CEdit)
//{{AFX_MSG_MAP(CGridEdit)
ON_WM_KILLFOCUS()
ON_WM_CHAR()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_CREATE()
//}}AFX_MSG_MAP
ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////
// CGridEdit message handlers

// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CGridEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
	
    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Need to keep a lookout for Tabs, Esc and Returns. These send a 
// "KeyUp" message, but no "KeyDown". That's why I didn't put their
// code in OnKeyDown. (I will never understand windows...)
void CGridEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//    if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
	if (nChar == VK_TAB || nChar == VK_ESCAPE)
		
	{
		m_nLastChar = nChar;
		GetParent()->SetFocus();    // This will destroy this window
		return;
	}
	
	if (nChar == VK_DOWN  || nChar == VK_UP   ||
		nChar == VK_RIGHT || nChar == VK_LEFT)
	{
		if (nChar == VK_DOWN)
		{
			ArrowDown();
		}
		
		if (nChar == VK_UP)
		{
			ArrowUp();
		}
		
		if (nChar == VK_RIGHT)
		{
			//ArrowRight();
		}
		
		if (nChar == VK_LEFT)
		{
			//ArrowLeft();
		}
		//m_nLastChar = nChar;
		//GetParent()->SetFocus();
		return;
	}
	
	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

// As soon as this edit loses focus, kill it.
void CGridEdit::OnKillFocus(CWnd* pNewWnd)
{
    CEdit::OnKillFocus(pNewWnd);
    EndEdit();
}

void CGridEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//CEdit::OnChar(nChar, nRepCnt, nFlags);
	if(nChar == VK_DOWN||nChar == VK_UP)
	{
	}
	else if ((nChar >= '0' && nChar <= '9') || nChar == '.')
	{
		if (m_nFormat == GEFM_Integer)
		{
			if (nChar != '.')
			{
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
		}
		else
		{
			if (m_nFormat == GEFM_Float)
			{
				CString strText;
				GetWindowText(strText);
				int nIndex = strText.FindOneOf(_T("."));
				
				if (nIndex > -1 &&  nChar == '.')
				{				
				}
				else
				{
					CEdit::OnChar(nChar, nRepCnt, nFlags);
				}
			}
			else
			{
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
			
		}
	}
	else if(nChar == VK_LEFT || nChar == VK_RIGHT)
	{
	}
	else
	{	
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		CString str;
		GetWindowText( str );
		
		CWindowDC dc(this);
		CFont *pFontDC = dc.SelectObject(GetFont());
		CSize size = dc.GetTextExtent( str );
		dc.SelectObject( pFontDC );
		
		size.cx += 5;                   // add some extra buffer
		
		// Get client rect
		CRect rect, parentrect;
		GetClientRect( &rect );
		GetParent()->GetClientRect( &parentrect );
		
		// Transform rect to parent coordinates
		ClientToScreen( &rect );
		GetParent()->ScreenToClient( &rect );
		
		// Check whether control needs to be resized
		// and whether there is space to grow
		if (size.cx > rect.Width())
		{
			if( size.cx + rect.left < parentrect.right )
				rect.right = rect.left + size.cx;
			else
				rect.right = parentrect.right;
			MoveWindow( &rect );
		}
	}
	
}

////////////////////////////////////////////////////////////////////////////
// CGridEdit overrides

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CGridEdit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->wParam == VK_RETURN)
	{
		//TRACE("\nCGridEdit::PreTranslateMessage  VK_RETURN \n");
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
void CGridEdit::PostNcDestroy() 
{
	CEdit::PostNcDestroy();
	
    delete this;	
}

////////////////////////////////////////////////////////////////////////////
// CGridEdit implementation

void CGridEdit::EndEdit()
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



//////////////////////////////////////////////////////////////////////////

void CGridEdit::ArrowUp()
{
	int nStart, nEnd;
	GetSel(nStart,nEnd);
	CString strText;
	GetWindowText(strText);
	int nLength = strText.GetLength();
	TCHAR chCurr = 0;
	
	switch(m_nFormat)
	{
	case GEFM_Float:
		{	
			if (nStart>=nLength)
			{
				chCurr = '0';
			}
			else
			{
				chCurr = strText.GetAt(nStart);
				
				if (chCurr == '.')
				{
					chCurr = '0';
				}
				else
				{
					chCurr++;
				}
				
				if (chCurr > '9')
				{
					chCurr = '.';
				}
			}
			
			strText.Format(_T("%c"),chCurr);
			UpdateText(strText , nStart ,nStart);
		}
		break;
	case GEFM_Integer:
		{									
			if (nStart>=nLength) 
			{
				chCurr = '0';
			}
			else
			{
				chCurr = strText.GetAt(nStart);
				chCurr++;
				
				if (chCurr>'9')
				{
					chCurr = '0';
				}
			}
			
			strText.Format(_T("%c"),chCurr);
			UpdateText(strText , nStart ,nStart);
		}
		break;
	}
}

void CGridEdit::ArrowDown()
{
	int nStart, nEnd;
	GetSel(nStart,nEnd);
	CString strText;
	GetWindowText(strText);
	int nLength = strText.GetLength();	
	TCHAR chCurr = 0;
	
	switch(m_nFormat)
	{
	case GEFM_Float:
		{
			int nIndex = strText.FindOneOf(_T("."));	
			int nTempValue = 0;	
			
			if (nStart>=nLength) 
			{
			}
			else
			{
				chCurr = strText.GetAt(nStart);
				
				if (chCurr == '.')
				{
					chCurr = '9';
				}
				else
				{
					chCurr--;
				}
				
				if (chCurr < '0')
				{
					chCurr = '.';
				}		
			}
			
			strText.Format(_T("%c"),chCurr);
			UpdateText(strText , nStart ,nStart);
		}
		break;
	case GEFM_Integer:
		{		
			if (nStart>=nLength) 
			{
				chCurr = '0';
			}
			else
			{
				chCurr = strText.GetAt(nStart);
				chCurr--;
				
				if (chCurr<'0')
				{
					chCurr = '9';
				}
			}
			
			strText.Format(_T("%c"),chCurr);
			UpdateText(strText , nStart ,nStart);
		}
		break;
	}
}


void CGridEdit::ArrowLeft()
{
	int nStart, nEnd;
	GetSel(nStart,nEnd);
	
	if (nStart>0)
	{
		nStart--;
	}
	
//	SetFocus();
	SetSel(nStart, nStart);
}

void CGridEdit::ArrowRight()
{
	int nStart, nEnd;
	GetSel(nStart,nEnd);
	CString strText;
	GetWindowText(strText);
	int nLength = strText.GetLength();
	
	if (nStart<nLength)
	{
		nStart++;
	}
	
//	SetFocus();
	SetSel(nStart, nStart);
}

void CGridEdit::UpdateText(CString &strText, int nStart, int nEnd)
{
	SetSel(nStart, nEnd+1);
	ReplaceSel(strText);
//	SetFocus();
	SetSel(nStart, nEnd);
}

int CGridEdit::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return 1;//CEdit::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
