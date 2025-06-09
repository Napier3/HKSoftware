// ColorSelBotton.cpp : implementation file
//

#include "stdafx.h"
#include "ColorSelBotton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorSelBotton

CColorSelBotton::CColorSelBotton()
{
}

CColorSelBotton::~CColorSelBotton()
{
}


BEGIN_MESSAGE_MAP(CColorSelBotton, CButton)
	//{{AFX_MSG_MAP(CColorSelBotton)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorSelBotton message handlers

void CColorSelBotton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC *cDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect cR(lpDrawItemStruct->rcItem);
	
	CPen cP(PS_SOLID,1,RGB(0,0,0));
	CBrush cB(m_crColor);
	CPen *cOldP=cDC->SelectObject(&cP);
	CBrush*cOldB=cDC->SelectObject(&cB);
	cDC->Rectangle(cR);
	cDC->SelectObject(cOldP);
	cDC->SelectObject(cOldB);
	cP.DeleteObject();
	cB.DeleteObject();
	if (lpDrawItemStruct->itemState&ODS_SELECTED)
		cDC->DrawEdge(&cR,EDGE_SUNKEN,BF_RECT);
	
}

void CColorSelBotton::SetColor(COLORREF cr,BOOL bInvalid)
{
	m_crColor=cr;
	if (bInvalid)
	{
		Invalidate(TRUE);
	}
}
COLORREF CColorSelBotton::GetColor()
{
	return m_crColor;
}

BOOL CColorSelBotton::SelColor(CWnd *pParent)
{
	CColorDialog od(m_crColor,0,pParent);	
	
	if (od.DoModal()==IDOK)
	{
		m_crColor = od.GetColor();
		SetColor(m_crColor, TRUE);
		return TRUE;
	}
	
	return FALSE;
}

