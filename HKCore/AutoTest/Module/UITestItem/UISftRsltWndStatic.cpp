#include "stdafx.h"
#include "UISftRsltWndStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUISftRsltWndStatic::CUISftRsltWndStatic()
{
	m_nWidth = 0;
	m_nHeight = 0;
}

CUISftRsltWndStatic::~CUISftRsltWndStatic()
{

}

long CUISftRsltWndStatic::CalWndSize(long &nWidth,long &nHeight)
{
	nHeight = 0;
	nWidth = 0;
	long nLineHeight = 0;
	CDC *pDC = GetDC();

	CString strText;
	GetWindowText(strText);
	CRect rc(0, 0, 0, 0);
	CFont *pFont = NULL;

	if (m_pFont != NULL)
	{
		pDC->SelectObject(m_pFont);
	}

	GetWindowRect(rc);
	pDC->DrawText(strText, rc, DT_CALCRECT|/*DT_WORDBREAK|*/DT_LEFT | DT_EXTERNALLEADING);
	nHeight = rc.Height();
	nWidth = rc.Width()+30;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	if (m_nWidth == 0)
	{
		pDC->DrawText(_T("  "), rc, DT_CALCRECT|/*DT_WORDBREAK|*/DT_LEFT);
		m_nHeight = rc.Height();
	}
// 	else
// 	{
// 		m_nWidth += rc.Width();
// 	}

	if (m_pFont != NULL)
	{
		pDC->SelectObject(pFont);
	}

	ReleaseDC(pDC);

	return nHeight;
}

void CUISftRsltWndStatic::CreateUIStatic(const CString &strText, CRect rcWnd, CWnd *pParent, UINT nID)
{
	CreateEx(WS_EX_CLIENTEDGE, _T("Edit"),_T("")
		, WS_CHILD |ES_MULTILINE |ES_LEFT|WS_TABSTOP 
		| ES_AUTOVSCROLL /*| WS_VSCROLL*/ | ES_READONLY
		, rcWnd,pParent,nID);
	SetWindowText(strText);
}

