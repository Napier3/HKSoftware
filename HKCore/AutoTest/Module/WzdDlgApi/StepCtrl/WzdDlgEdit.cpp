#include "stdafx.h"
#include "WzdDlgEdit.h"

IMPLEMENT_DYNAMIC(CWzdDlgEdit, CEdit)

CWzdDlgEdit::CWzdDlgEdit()
{
	m_crBorder = RGB(0, 0, 0);
}

CWzdDlgEdit::~CWzdDlgEdit()
{

}

BEGIN_MESSAGE_MAP(CWzdDlgEdit, CEdit)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

BOOL CWzdDlgEdit::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

HBRUSH CWzdDlgEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	CRect rc;
	GetClientRect(rc);
	CBrush brush(m_crBorder);
	pDC->FrameRect(rc, &brush);
	rc.InflateRect(1, 1, 1, 1);
	pDC->FrameRect(rc, &brush);
	rc.InflateRect(1, 1, 1, 1);
	pDC->FrameRect(rc, &brush);
	return NULL;
}