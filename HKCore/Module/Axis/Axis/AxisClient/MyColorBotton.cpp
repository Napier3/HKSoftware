// MyColorBotton.cpp : implementation file
//

#include "stdafx.h"
#include "AxisClient.h"
#include "MyColorBotton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyColorBotton

CMyColorBotton::CMyColorBotton()
{
}

CMyColorBotton::~CMyColorBotton()
{
}


BEGIN_MESSAGE_MAP(CMyColorBotton, CButton)
	//{{AFX_MSG_MAP(CMyColorBotton)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyColorBotton message handlers

void CMyColorBotton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CAxisClientApp	*App=(CAxisClientApp*)AfxGetApp();
	CDC *cDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect cR(lpDrawItemStruct->rcItem);
	
	CPen cP(PS_SOLID,1,RGB(0,0,0));
	CBrush cB(crColor);
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

void CMyColorBotton::SetColor(COLORREF cr,char cInitSign)
{
	crColor=cr;
	if (cInitSign)
		Invalidate(TRUE);
}
COLORREF CMyColorBotton::GetColor()
{
	return crColor;
}