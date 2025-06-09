#include "stdafx.h"
#include "WzdDlgTabCtrl.h"
#include "../WzdDlgDef.h"

IMPLEMENT_DYNAMIC(CWzdDlgTabCtrl, CTabCtrl)

CWzdDlgTabCtrl::CWzdDlgTabCtrl()
{

}

CWzdDlgTabCtrl::~CWzdDlgTabCtrl()
{
}

void CWzdDlgTabCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0, TCS_OWNERDRAWFIXED);
	CTabCtrl::PreSubclassWindow();
}

void CWzdDlgTabCtrl::SetItemColor(long nIndex, COLORREF rgbBk, COLORREF rgbTxt)
{
	tagTabColor tg;
	tg.m_clrBk = rgbBk;
	tg.m_clrTxt = rgbTxt;

	m_color.insert(std::pair<int, tagTabColor>(nIndex, tg));
}

BEGIN_MESSAGE_MAP(CWzdDlgTabCtrl, CTabCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()

BOOL CWzdDlgTabCtrl::OnEraseBkgnd(CDC* pDC) 
{
	CBrush br(RGB(255, 255, 255));
	CRect rc;
	GetClientRect(rc);
	pDC->FillRect(rc, &br);
	return TRUE;
}

void CWzdDlgTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rc = lpDIS->rcItem;

	char szTabText[100];
	TC_ITEM  tci;
	memset(szTabText, '\0', sizeof(szTabText));
	tci.mask = TCIF_TEXT;
	tci.pszText = szTabText;
	tci.cchTextMax = sizeof(szTabText) - 1;
	GetItem(lpDIS->itemID, &tci);
	CString strText = tci.pszText;

	if (lpDIS->itemID != GetCurSel())
	{
		pDC->FillSolidRect(rc, RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		rc.top += 1;
		pDC->DrawText(strText, strText.GetLength(), &rc, DT_CENTER);
	}
	else
	{
		pDC->FillSolidRect(rc, g_crBlue);
		pDC->SetTextColor(RGB(0, 0, 0));
		rc.top += 5;
		pDC->DrawText(strText, strText.GetLength(), &rc, DT_CENTER);
	}
}