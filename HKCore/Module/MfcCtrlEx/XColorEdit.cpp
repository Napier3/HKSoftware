// XColorEdit.cpp : implementation file
//

#include "stdafx.h"
#include "XColorEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CXColorEdit
IMPLEMENT_DYNAMIC(CXColorEdit, CEdit)

CXColorEdit::CXColorEdit()
{
	m_crText = RGB(0, 0, 0);
	m_crBack = RGB(255, 255, 255);
	m_brBackGnd.CreateSolidBrush(m_crBack);
}

CXColorEdit::~CXColorEdit()
{
}


BEGIN_MESSAGE_MAP(CXColorEdit, CEdit)
	//ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

HBRUSH CXColorEdit::CtlColor(CDC* pDC, UINT nCtlColor) //OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CEdit::OnCtlColor(pDC, nCtlColor);

	pDC->SetTextColor(m_crText);
	pDC->SetBkColor(m_crBack);

	return m_brBackGnd;
}


void CXColorEdit::SetBackColor(COLORREF cr)
{
	m_crBack = cr;
	
	if (m_brBackGnd.GetSafeHandle())
       m_brBackGnd.DeleteObject();

	m_brBackGnd.CreateSolidBrush(cr);
	
	Invalidate(TRUE);
}


void CXColorEdit::SetTextColor(COLORREF cr)
{
	m_crText = cr;

	Invalidate(TRUE);
}

