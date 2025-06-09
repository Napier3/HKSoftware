// DrawPara.cpp: implementation of the CDrawPara class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawPara.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawPara::CDrawPara()
{
	m_nParaID		= 0;
	m_fFrequency		= 0;
	m_fValue	= 0;
	m_fAngle		= 0;
	m_pfPara		= NULL;
	m_strUnit	    = "";
}

CDrawPara::~CDrawPara()
{
	m_nParaID		= 0;
	m_pfPara		= NULL;
}

void CDrawPara::CalValue()
{
	
}

void CDrawPara::GetDrawRectSize(long& cx,long& cy)
{
	CDC* pDC = m_pParentWnd->GetDC();
	CFont* pOldFont = pDC->SelectObject(m_pfPara);
	CString str ;
	str.Format(_T("%.3f%s"), m_fValue,m_strUnit);
	CSize szPara = pDC->GetTextExtent(str);
	pDC->SelectObject(pOldFont);
	pOldFont = NULL;
	m_pParentWnd->ReleaseDC(pDC);
	cy = szPara.cy;
	cx = szPara.cx;
}

void CDrawPara::Draw(CDC* pDC)
{
	CFont* pOldFont = pDC->SelectObject(m_pfPara);
	int nMode = pDC->SetBkMode(TRANSPARENT);
	CString str ;
	CRect rect = m_rcBorder;
	str.Format(_T("%.1f%s"),m_fValue,m_strUnit);
	pDC->DrawText(str,rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	pDC->SelectObject(pOldFont);
	pDC->SetBkMode(nMode);
	pOldFont = NULL;
}

void CDrawPara::Init(UINT nParaID,const CString& strUnit,PRTATTRIBUTECALFUNCPARA pCalFuncPara,CFont* pFont)
{
	if(pCalFuncPara == NULL)
		return;

	if(pCalFuncPara->pRtChAttrVal == NULL)
		return;

	m_pfPara = pFont;
}
