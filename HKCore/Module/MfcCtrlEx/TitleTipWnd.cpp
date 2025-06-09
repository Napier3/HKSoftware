// TitleTipWnd.cpp : implementation file
//

#include "stdafx.h"
#include "TitleTipWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitleTipWnd

CTitleTipWnd::CTitleTipWnd()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();
	if(!(::GetClassInfo(hInst, TITLETIPWND_CLASSNAME, &wndcls)))
	{
		// otherwise we need to register a new class
		wndcls.style			= CS_SAVEBITS ;
		wndcls.lpfnWndProc		= ::DefWindowProc;
		wndcls.cbClsExtra		= wndcls.cbWndExtra = 0;
		wndcls.hInstance		= hInst;
		wndcls.hIcon			= NULL;
		wndcls.hCursor			= LoadCursor( hInst, IDC_ARROW );
		wndcls.hbrBackground	= (HBRUSH)(COLOR_INFOBK + 1); 
		wndcls.lpszMenuName		= NULL;
		wndcls.lpszClassName	= TITLETIPWND_CLASSNAME;
		
		if (!AfxRegisterClass(&wndcls))
			AfxThrowResourceException();
	}

	m_logFont = InitLogFont();
	m_logFont.lfHeight = -12;
	strcpy(m_logFont.lfFaceName,"Tahoma");

	m_bUseParentFont = TRUE;
}

CTitleTipWnd::~CTitleTipWnd()
{
}


BEGIN_MESSAGE_MAP(CTitleTipWnd, CWnd)
	//{{AFX_MSG_MAP(CTitleTipWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTitleTipWnd message handlers


BOOL CTitleTipWnd::Create(CWnd * pParentWnd)
{
	//ASSERT_VALID(pParentWnd);
	if (pParentWnd == NULL)
	{
		return FALSE;
	}
	
	DWORD dwStyle = WS_BORDER | WS_POPUP; 
	DWORD dwExStyle = WS_EX_TOOLWINDOW | WS_EX_TOPMOST;
	m_pParentWnd = pParentWnd;
	
	BOOL b = CreateEx(dwExStyle, TITLETIPWND_CLASSNAME, NULL, dwStyle, 0, 0, 1000, 1000, 
		NULL, NULL, NULL );
	SetTimer(124,500,NULL);
	return b;
}

// Show 		 - Show the titletip if needed
// rectTitle	 - The rectangle within which the original 
//				    title is constrained - in client coordinates
// lpszTitleText - The text to be displayed
// xoffset		 - Number of pixel that the text is offset from
//				   left border of the cell
void CTitleTipWnd::Show(CRect rectTitle, LPCTSTR lpszTitleText, int xoffset /*=0*/)
{
	HWND hWnd = GetSafeHwnd();
	if (!::IsWindow(hWnd))
	{
		return;
	}
	if( rectTitle.IsRectEmpty() )
	{
		return;
	}
	
	// If titletip is already displayed, don't do anything.
	if( IsWindowVisible() ) 
		return;
	
	// Do not display the titletip is app does not have focus
	if( GetFocus() == NULL )
		return;
	
	// Define the rectangle outside which the titletip will be hidden.
	// We add a buffer of one pixel around the rectangle
	m_rectTitle.top    = -1;
	m_rectTitle.left   = -xoffset-1;
	m_rectTitle.right  = rectTitle.Width()-xoffset;
	m_rectTitle.bottom = rectTitle.Height()+1;
	
	// Determine the width of the text
	m_pParentWnd->ClientToScreen( rectTitle );
	
	CClientDC dc(this);
	CString strTitle = _T(" ");	strTitle += lpszTitleText; strTitle += _T(" ");
	
	CFont *pFont = NULL;
	if (m_bUseParentFont)
	{
		pFont = m_pParentWnd->GetFont();
	}
	else
	{
		pFont = new CFont;
		pFont->CreateFontIndirect(&m_logFont);
	}
	CFont *pFontDC = dc.SelectObject( pFont );
	CSize size = dc.GetTextExtent( strTitle );
	
	CRect rectDisplay = rectTitle;
	rectDisplay.left += xoffset;
	rectDisplay.right = rectDisplay.left + size.cx + xoffset;
	if (rectDisplay.Height() < size.cy + 4)
	{
		rectDisplay.bottom = rectDisplay.top + size.cy + 4 ;
	}
	
	// Do not display if the text fits within available space
	if( rectDisplay.right <= rectTitle.right-xoffset )
		return;
	
	CWnd *pWnd = GetDesktopWindow();
	CRect rectDesktop;
	pWnd->GetWindowRect(&rectDesktop);

	if (rectDisplay.right > rectDesktop.right)
	{
		long nOffset = rectDesktop.right - rectDisplay.right;
		rectDisplay.OffsetRect(nOffset,0);
		m_rectTitle.OffsetRect(-nOffset,0);
	}
	// Show the titletip
	SetWindowPos( &wndTop, rectDisplay.left, rectDisplay.top, 
		rectDisplay.Width(), rectDisplay.Height(), 
		SWP_SHOWWINDOW|SWP_NOACTIVATE );
	
	dc.SetBkMode( TRANSPARENT );
	dc.TextOut( 0, 0, strTitle );
	dc.SelectObject( pFontDC );
	if (!m_bUseParentFont)
	{
		pFont->DeleteObject();
		delete pFont;
	}
	
	SetCapture();
}

void CTitleTipWnd::Hide()
{
	if (!::IsWindow(GetSafeHwnd()))
        return;
	
    if (GetCapture()->GetSafeHwnd() == GetSafeHwnd())
        ReleaseCapture();
	
	ShowWindow( SW_HIDE );
}

void CTitleTipWnd::SetLogFont(LOGFONT logFont)
{
	m_bUseParentFont = FALSE;
	m_logFont = logFont;
}

void CTitleTipWnd::CalTipRectAngle(LPCTSTR lpszTitleText,long nMaxWidth,CSize &sizeTip)
{
	HWND hWnd = GetSafeHwnd();
	if (!::IsWindow(hWnd))
	{
		return;
	}
	CRect rectTitle(0,0,nMaxWidth,0);
	
	// If titletip is already displayed, don't do anything.
	if( IsWindowVisible() ) 
		return;
		
	CClientDC dc(this);
	CString strTitle = _T(" ");	
	strTitle += lpszTitleText; 
	strTitle += _T(" ");
	
	CFont *pFont = NULL;
	if (m_bUseParentFont)
	{
		pFont = m_pParentWnd->GetFont();
	}
	else
	{
		pFont = new CFont;
		pFont->CreateFontIndirect(&m_logFont);
	}
	CFont *pFontDC = dc.SelectObject( pFont );
	sizeTip = dc.GetTextExtent( strTitle );
	if (sizeTip.cx > nMaxWidth)
	{
		long nRows = sizeTip.cx / nMaxWidth;
		if (nRows*nMaxWidth < sizeTip.cx)
		{
			nRows++;
		}
		sizeTip.cx = nMaxWidth;
		sizeTip.cy = sizeTip.cy * nRows;
	}
	
	dc.SelectObject( pFontDC );
	if (!m_bUseParentFont)
	{
		pFont->DeleteObject();
		delete pFont;
	}
	
}

BOOL CTitleTipWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	SetTimer(124,500,NULL);
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CTitleTipWnd::PreTranslateMessage(MSG* pMsg) 
{
	CWnd *pWnd;
	int hittest;
	switch (pMsg->message)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		POINTS pts = MAKEPOINTS( pMsg->lParam );
		POINT  point;
		point.x = pts.x;
		point.y = pts.y;
		ClientToScreen( &point );
		pWnd = WindowFromPoint( point );
		if( pWnd == this ) 
			pWnd = m_pParentWnd;
		
		hittest = (int)pWnd->SendMessage(WM_NCHITTEST,0,MAKELONG(point.x,point.y));
		
		if (hittest == HTCLIENT) 
		{
			pWnd->ScreenToClient( &point );
			pMsg->lParam = MAKELONG(point.x,point.y);
		} 
		else 
		{
			switch (pMsg->message)
			{
			case WM_LBUTTONDOWN: 
				pMsg->message = WM_NCLBUTTONDOWN;
				break;
			case WM_RBUTTONDOWN: 
				pMsg->message = WM_NCRBUTTONDOWN;
				break;
			case WM_MBUTTONDOWN: 
				pMsg->message = WM_NCMBUTTONDOWN;
				break;
			}
			pMsg->wParam = hittest;
			pMsg->lParam = MAKELONG(point.x,point.y);
		}
		
        Hide();
		pWnd->PostMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		return TRUE;	
		
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
        Hide();
		m_pParentWnd->PostMessage( pMsg->message, pMsg->wParam, pMsg->lParam );
		return TRUE;
	}
	
	if( GetFocus() == NULL )
	{
        Hide();
		return TRUE;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}

void CTitleTipWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (!m_rectTitle.PtInRect(point)) 
    {
        Hide();

        ClientToScreen( &point );
        CWnd *pWnd = WindowFromPoint( point );
        if ( pWnd == this ) 
            pWnd = m_pParentWnd;
        
        int hittest = (int)pWnd->SendMessage(WM_NCHITTEST,0,MAKELONG(point.x,point.y));
        
        if (hittest == HTCLIENT) 
		{
            pWnd->ScreenToClient( &point );
            pWnd->PostMessage( WM_MOUSEMOVE, nFlags, MAKELONG(point.x,point.y) );
		} 
		else
		{
            pWnd->PostMessage( WM_NCMOUSEMOVE, hittest, MAKELONG(point.x,point.y) );
        }
    }
	else
	{
	}
}


void CTitleTipWnd::OnKillFocus(CWnd* pNewWnd) 
{
	Hide();
	CWnd::OnKillFocus(pNewWnd);

	TRACE("CTitleTipWnd::OnKillFocus");
}


void CTitleTipWnd::OnTimer(UINT nIDEvent) 
{
	if (! ::IsWindow(m_hWnd))
	{
		return;
	}

	CPoint point;
	GetCursorPos(&point); 
	CRect rectWin;
	GetWindowRect(&rectWin);
	if (!rectWin.PtInRect(point))
	{
		if(IsWindowVisible())
		{
			Hide();
		}
	}

	CWnd::OnTimer(nIDEvent);
}
