// SplashWndBase.cpp
//

#include "stdafx.h"
#include "XSplashWndBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
BOOL CXSplashWndBase::g_bShowSplashWnd = TRUE;  
CXSplashWndBase* CXSplashWndBase::g_pSplashWnd = NULL;  

CXSplashWndBase::CXSplashWndBase()  
{  

}  

CXSplashWndBase::~CXSplashWndBase()  
{  
	// Clear the static window pointer.  
	ASSERT(g_pSplashWnd == this);  
	g_pSplashWnd = NULL;  
}  


BEGIN_MESSAGE_MAP(CXSplashWndBase, CWnd)  
	ON_WM_CREATE()  
	ON_WM_PAINT()  
	ON_WM_TIMER()  
END_MESSAGE_MAP()  


void CXSplashWndBase::EnableSplashScreen(BOOL bEnable )  
{  
	g_bShowSplashWnd = bEnable;  
}  

void CXSplashWndBase::ShowSplashScreen(const CString &strFile, CWnd* pParentWnd )  
{  
	if (!g_bShowSplashWnd || (g_pSplashWnd != NULL))  
		return;  

	g_pSplashWnd = new CXSplashWndBase;  
	CString strBmpFile;
	strBmpFile = _P_GetCommonResourcePath();
	strBmpFile += strFile;
	g_pSplashWnd->m_oDib.Load(strBmpFile);

	if (!g_pSplashWnd->Create(pParentWnd))  
		delete g_pSplashWnd;  
	else  
		g_pSplashWnd->UpdateWindow();  
}  

BOOL CXSplashWndBase::PreTranslateAppMessage(MSG* pMsg)  
{  
	if (g_pSplashWnd == NULL)  
		return FALSE;  

	// If we get a keyboard or mouse message, hide the splash screen.  
	if (pMsg->message == WM_KEYDOWN ||  
		pMsg->message == WM_SYSKEYDOWN ||  
		pMsg->message == WM_LBUTTONDOWN ||  
		pMsg->message == WM_RBUTTONDOWN ||  
		pMsg->message == WM_MBUTTONDOWN ||  
		pMsg->message == WM_NCLBUTTONDOWN ||  
		pMsg->message == WM_NCRBUTTONDOWN ||  
		pMsg->message == WM_NCMBUTTONDOWN)  
	{  
		g_pSplashWnd->HideSplashScreen();  
		return TRUE; // message handled here  
	}  

	return FALSE; // message not handled  
}  

BOOL CXSplashWndBase::Create(CWnd* pParentWnd )  
{  
	CRect rcBmp = m_oDib.GetDibRect();

	if (rcBmp.Width() < 10)  
		return FALSE;  

	return CreateEx(0,  
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),  
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, rcBmp.Width(), rcBmp.Height(), pParentWnd->GetSafeHwnd(), NULL);  
}  


void CXSplashWndBase::HideSplashScreen()  
{  
	// Destroy the window, and update the mainframe.  
	DestroyWindow();  
	AfxGetMainWnd()->UpdateWindow();  
}  

void CXSplashWndBase::PostNcDestroy()  
{  
	// Free the C++ class.  
	delete this;  
}  

int CXSplashWndBase::OnCreate(LPCREATESTRUCT lpCreateStruct)  
{  
	if (CWnd::OnCreate(lpCreateStruct) == -1)  
		return -1;  

	// Center the window.  
	CenterWindow();  

	// Set a timer to destroy the splash screen.  
	SetTimer(1, 3000, NULL);  

	return 0;  
}  

void CXSplashWndBase::OnPaint()  
{  
	CPaintDC dc(this);  

	CRect rcBmp = m_oDib.GetDibRect();
	m_oDib.Draw(&dc, 0, 0, rcBmp.Width(), rcBmp.Height());
// 	CDC dcImage;  
// 	if (!dcImage.CreateCompatibleDC(&dc))  
// 		return;  
// 
// 	BITMAP bm;  
// 	m_bitmap.GetBitmap(&bm);  
// 
// 	// Paint the image.  
// 	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);  
// 	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);  
// 	dcImage.SelectObject(pOldBitmap);  
}  

void CXSplashWndBase::OnTimer(UINT nIDEvent)  
{  
	// Destroy the splash screen window.  
	HideSplashScreen();  
}   
