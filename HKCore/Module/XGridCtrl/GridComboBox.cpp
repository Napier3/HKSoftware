
#include "stdafx.h"
#include "GridComboBox.h"
#include "GridDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGridComboEdit

CGridComboEdit::CGridComboEdit()
{
}

CGridComboEdit::~CGridComboEdit()
{	
}

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CGridComboEdit::PreTranslateMessage(MSG* pMsg) 
{
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

	return CEdit::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CGridComboEdit, CEdit)
	//{{AFX_MSG_MAP(CGridComboEdit)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridComboEdit message handlers

void CGridComboEdit::OnKillFocus(CWnd* pNewWnd) 
{
    CGridComboBox* pOwner = (CGridComboBox*) GetOwner();  // This MUST be a CGridComboBox
	if (pOwner)
        pOwner->EndEdit();	
	//CEdit::OnKillFocus(pNewWnd);
}

void CGridComboEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((nChar == VK_PRIOR || nChar == VK_NEXT ||
		 nChar == VK_DOWN  || nChar == VK_UP   ||
		 nChar == VK_RIGHT || nChar == VK_LEFT) &&
		(GetKeyState(VK_CONTROL) < 0 && GetDlgCtrlID() == IDC_COMBOEDIT))
    {
        CWnd* pOwner = GetOwner();

        if (pOwner)
		{
			if (::IsWindow(pOwner->GetSafeHwnd()))
			{
				pOwner->SendMessage(WM_KEYDOWN, nChar, nRepCnt+ (((DWORD)nFlags)<<16));
			}		
		}

        return;
    }

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGridComboEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
/*
	if (nChar == VK_ESCAPE) 
	{
        CWnd* pOwner = GetOwner();
        if (pOwner)
            pOwner->SendMessage(WM_KEYUP, nChar, nRepCnt + (((DWORD)nFlags)<<16));
        return;
    }

	if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
    {
        CWnd* pOwner = GetOwner();
        if (pOwner)
            pOwner->SendMessage(WM_KEYUP, nChar, nRepCnt + (((DWORD)nFlags)<<16));
        return;
    }*/

	if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
    {
        CWnd* pOwner = GetOwner();

        if (pOwner)
		{
			if (::IsWindow(pOwner->GetSafeHwnd()))
			{
				pOwner->SendMessage(WM_KEYUP, nChar, nRepCnt + (((DWORD)nFlags)<<16));
			}
		}

        return;
    }

	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CGridComboBox
void CGridComboBox::SetDeflateVal(int iVal)
{
	m_iDeflateVal = iVal;
}

CGridComboBox::CGridComboBox(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                           int nRow, int nColumn, 
						   /*CStringArray& Items, */CString sInitText, 
						   UINT nFirstChar, LOGFONT lfFont)
{
	m_pFont = NULL;
	m_bDisableAC   = FALSE;
    m_bFlatLook    = TRUE;
    m_bLBtnDown    = FALSE;
    m_bPainted     = FALSE;
    m_bHasFocus    = FALSE;
    m_bAutoComp    = FALSE;
    m_clr3DHilight = ::GetSysColor(COLOR_3DHILIGHT);
    m_clr3DShadow  = ::GetSysColor(COLOR_3DSHADOW);
    m_clr3DFace    = ::GetSysColor(COLOR_3DFACE);
    m_cxHThumb     = ::GetSystemMetrics(SM_CXHTHUMB);
	
	SetDeflateVal(1);

	m_nNumLines = 4;
	m_sInitText = sInitText;
 	m_nRow		= nRow;
 	m_nCol      = nColumn;
 	m_nLastChar = 0; 
	m_bExitOnArrows = FALSE; //(nFirstChar != VK_LBUTTON);	// If mouse click brought us here,

	// Create the combobox
 	DWORD dwComboStyle = WS_CHILD|/*WS_VISIBLE|*/WS_VSCROLL|
 					     CBS_AUTOHSCROLL | dwStyle;
	int nHeight = rect.Height();
	rect.bottom = rect.bottom + m_nNumLines*nHeight + ::GetSystemMetrics(SM_CYHSCROLL);
	if (rect.Height() < 200)
	{
		rect.bottom = rect.top + 200;
	}

	if (!Create(dwComboStyle, rect, pParent, nID)) 
		return;

	// Add the strings
	ASSERT (nRow < 65536 || nColumn < 65536);
	
	WPARAM wPara = (nRow << 16) + nColumn;
	if (pParent != NULL)
	{
		if (::IsWindow( pParent->GetSafeHwnd()) ) 
		{
			pParent->SendMessage( IPCMBM_FILL, wPara, (LPARAM)this );
		}	
	}

	int i = 0;
	// Get the maximum width of the text strings
	CStringArray Items;
	int iCount = GetCount();
	int iIndex=0;
	for(iIndex=0;iIndex<iCount;iIndex++)
	{
		CString rString=_T("");
		GetLBText( iIndex, rString ) ;
		Items.Add(rString);
	}
	int nMaxLength = 0;
	CClientDC dc(GetParent());

	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&lfFont);
	CFont* pOldFont = dc.SelectObject(m_pFont);

	for (i = 0; i < Items.GetSize(); i++) 
		nMaxLength = max(nMaxLength, dc.GetTextExtent(Items[i]).cx);

	nMaxLength += (::GetSystemMetrics(SM_CXVSCROLL) + dc.GetTextExtent(_T(" ")).cx*2);
	dc.SelectObject(pOldFont);

  //  if (nMaxLength > rect.Width())
//	    rect.right = rect.left + nMaxLength;

	// Resize the edit window and the drop down window
	MoveWindow(rect);
	ShowWindow(SW_SHOW);
	
	SetFont(m_pFont);
	SetItemHeight(-1, nHeight);

	if (nMaxLength < 80)
	{
		nMaxLength = 80;
	}

	SetDroppedWidth(nMaxLength);//下拉时的最小宽度
	SetHorizontalExtent(0); // no horz scrolling

	// Set the initial text to m_sInitText
	if (SelectString(-1, m_sInitText) == CB_ERR) 
		SetWindowText(m_sInitText);		// No text selected, so restore what was there before

    // Subclass the combobox edit control if style includes CBS_DROPDOWN
    if ((dwStyle & CBS_DROPDOWNLIST) != CBS_DROPDOWNLIST)
    {
        m_edit.SubclassDlgItem(IDC_COMBOEDIT, this);
 	    SetFocus();
        switch (nFirstChar)
        {
            case VK_LBUTTON: 
            case VK_RETURN:   
            case VK_SPACE:   
				m_edit.SetSel((int)_tcslen(m_sInitText), -1); 
				return;
            case VK_BACK:     
				m_edit.SetSel((int)_tcslen(m_sInitText), -1); 
				break;
            case VK_DOWN: 
            case VK_UP:   
            case VK_RIGHT:
            case VK_LEFT:  
            case VK_NEXT:  
            case VK_PRIOR: 
            case VK_HOME:  
            case VK_END:      
				//m_edit.SetSel(0,-1);
				//return;
            default:          
				//m_edit.SetSel(0,-1);
				break;
        }

        if (::IsWindow( GetSafeHwnd() ))
		{
			SendMessage(WM_CHAR, nFirstChar);
        }
    }
    else
 	    SetFocus();


	Invalidate();
}

CGridComboBox::~CGridComboBox()
{
	if (m_pFont != NULL)
	{
		delete m_pFont;
		m_pFont = NULL;
	}
}


void CGridComboBox::EndEdit()
{
    CString str;
    GetWindowText(str);
 
    // Send Notification to parent
    GV_DISPINFO dispinfo;

    dispinfo.hdr.hwndFrom = GetSafeHwnd();
    dispinfo.hdr.idFrom   = GetDlgCtrlID();
    dispinfo.hdr.code     = GVN_ENDCOMBOBOXEDIT;
    dispinfo.item.mask    = LVIF_TEXT|LVIF_PARAM;
    dispinfo.item.row     = m_nRow;
    dispinfo.item.col     = m_nCol;
    dispinfo.item.szText  = str;
	dispinfo.item.dwValue = GetCurSel();
    dispinfo.item.lParam  = (LPARAM) m_nLastChar; 
	dispinfo.dwItemData   = GetItemData(dispinfo.item.dwValue);
 
    CWnd* pOwner = GetOwner();
	
	if (pOwner != NULL)
	{
		if (::IsWindow(pOwner->GetSafeHwnd()))
		{
			pOwner->SendMessage(WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&dispinfo );
		}		
	}
	
	// Close this window (PostNcDestroy will delete this)
    if (::IsWindow(GetSafeHwnd()))
	{
		PostMessage(WM_CLOSE, 0, 0);
    }
}

void CGridComboBox::PostNcDestroy() 
{
	CComboBox::PostNcDestroy();

	delete this;
}

BEGIN_MESSAGE_MAP(CGridComboBox, CComboBox)
	//{{AFX_MSG_MAP(CGridComboBox)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_PAINT()
    ON_CONTROL_REFLECT(CBN_SETFOCUS, OnCbnSetFocus)
   //ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillFocus)
   ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnCbnKillfocus)
	ON_WM_SYSCOLORCHANGE()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEACTIVATE()
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CGridComboBox::OnCbnSelchange)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGridComboBox message handlers

void CGridComboBox::OnCbnKillfocus() 
{
	if (m_bFlatLook)
	{
        m_bHasFocus = FALSE;
		
		Invalidate(); 
    }
    if ((GetStyle() & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST)
	{
		EndEdit();
	}

	ShowWindow(SW_HIDE);
	
//	CComboBox::OnKillFocus(pNewWnd);

// 	if (pNewWnd != NULL)
// 	{
// 		if (GetSafeHwnd() == pNewWnd->GetSafeHwnd())
// 			return;
//	}

    // Only end editing on change of focus if we're using the CBS_DROPDOWNLIST style
}

// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CGridComboBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((nChar == VK_PRIOR || nChar == VK_NEXT ||
		 nChar == VK_DOWN  || nChar == VK_UP   ||
		 nChar == VK_RIGHT || nChar == VK_LEFT) &&
		(m_bExitOnArrows || GetKeyState(VK_CONTROL) < 0))
	{
		m_nLastChar = nChar;
		GetParent()->SetFocus();
		return;
	}

	CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Need to keep a lookout for Tabs, Esc and Returns.
void CGridComboBox::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_ESCAPE) 
		SetWindowText(m_sInitText);	// restore previous text

	if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
	{
		m_nLastChar = nChar;
		GetParent()->SetFocus();	// This will destroy this window
		return;
	}

	CComboBox::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL CGridComboBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	return CComboBox::OnSetCursor(pWnd, nHitTest, message);
}

void CGridComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
    CComboBox::OnLButtonDown(nFlags, point);
}

void CGridComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CComboBox::OnLButtonUp(nFlags, point);
}

BOOL CGridComboBox::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

BOOL CGridComboBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_VSCROLL;
	cs.style |= CBS_AUTOHSCROLL;

	if (!CComboBox::PreCreateWindow(cs))
		return FALSE;
	return TRUE;
}

void CGridComboBox::OnPaint() 
{
	CPaintDC dc(this); 
	OnNoFlickerPaint(&dc);
}

void CGridComboBox::OnNoFlickerPaint(CDC* pDC)
{
	ASSERT(pDC != NULL);
	
	//获得客户区
	CRect rcClient;
	GetClientRect(&rcClient);

	CDC memDC; 

    //创建内存DC
	memDC.CreateCompatibleDC(pDC);
	memDC.SetMapMode(pDC->GetMapMode());

    //创建位图，用于绘制组合框控件
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());

    //将位图选入内存DC
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	//绘制背景
//	memDC.FillSolidRect(rcClient, m_clr3DFace);
	memDC.FillSolidRect(rcClient, RGB(255,255,255));

	//缺省绘制
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );

	DrawCombo(&memDC,m_clr3DFace, m_clr3DFace);

	pDC->BitBlt(rcClient.left, 
		rcClient.top,
		rcClient.Width()-2*m_iDeflateVal,
		rcClient.Height()-2*m_iDeflateVal,
		&memDC, 
		rcClient.left+m_iDeflateVal,
		rcClient.top+m_iDeflateVal, 
		SRCCOPY);  
	
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
}

void CGridComboBox::DrawCombo(CDC* pDC,COLORREF clrTopLeft,COLORREF clrBottomRight)
{
    CRect rcItem;
    GetClientRect(&rcItem);

	//控件的最外围的边框
	pDC->Draw3dRect(rcItem, RGB(255,255,255), RGB(255,255,255));//%%%
    rcItem.DeflateRect(1,1);//比第一个遍框小一个单位
    //控件的第二个边框
    if (!IsWindowEnabled())
	{
		pDC->Draw3dRect(rcItem, m_clr3DShadow, m_clr3DHilight);//%%%
    }
    else
	{
		pDC->Draw3dRect(rcItem, RGB(255,255,255), RGB(255,255,255));//%%%
    }

    //下拉箭头按钮的最外围边框
    rcItem.DeflateRect(1,1);
    rcItem.left = rcItem.right-m_cxHThumb;
	pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DDKSHADOW));//下拉箭头按钮的最外围边框
}

void CGridComboBox::OnCbnSetFocus()
{
    if (m_bFlatLook)
	{
        m_bHasFocus = TRUE;

		Invalidate();
    }

	ShowDropDown(TRUE);

}

BOOL CGridComboBox::PreTranslateMessage(MSG* pMsg) 
{
	if (m_bAutoComp)
	{
        // Make sure that the keystrokes continue to the edit control.
        if (pMsg->message == WM_KEYDOWN || pMsg->message==WM_KEYUP)
        {
			if (pMsg->message == WM_KEYDOWN)
			{
				if (pMsg->wParam == VK_DELETE ||
					pMsg->wParam == VK_BACK)
				{
					m_bDisableAC = TRUE;
				}
			}
			
			if (pMsg->message == WM_KEYUP)
			{
				if (pMsg->wParam == VK_DELETE ||
					pMsg->wParam == VK_BACK)
				{
					m_bDisableAC = FALSE;
				}
			}
			
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
			
            return TRUE;
		}
	}
	
    return CComboBox::PreTranslateMessage(pMsg);
}

void CGridComboBox::OnSysColorChange() 
{
	CComboBox::OnSysColorChange();
	
	// reset color member variables.
    m_clr3DHilight = ::GetSysColor(COLOR_3DHILIGHT);
    m_clr3DShadow  = ::GetSysColor(COLOR_3DSHADOW);
    m_clr3DFace    = ::GetSysColor(COLOR_3DFACE);
}

int CGridComboEdit::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return 1;//CEdit::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

int CGridComboBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return 1;//CComboBox::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CGridComboBox::OnCbnSelchange()
{
	EndEdit();
}
