// DrawMultiPara.cpp: implementation of the CDrawMultiPara class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawMultiPara.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawMultiPara::CDrawMultiPara()
{
	m_strUnit2 = "";
}

CDrawMultiPara::~CDrawMultiPara()
{
	m_pfPara		= NULL;
}

void CDrawMultiPara::Draw(CDC* pDC)
{
	CFont* pOldFont = pDC->SelectObject(m_pfPara);
// 	CPen Pen(PS_SOLID,1,m_crColor);
// 	CPen* pOldPen = pDC->SelectObject(&Pen);
	CString strPara,strPara2;
	
	//第一个参数
	strPara.Format(_T("%.3f%s"),m_fValue,m_strUnit);
	CSize szPara = pDC->GetTextExtent(strPara);	
	long nTop = m_rcBorder.top ;
	long nLeft = m_rcBorder.left;
	long nBom = nTop + szPara.cy;

	pDC->TextOut(nLeft, nTop, strPara);
	nLeft += szPara.cx;
	pDC->MoveTo(nLeft, nBom);
	pDC->LineTo(nLeft + szPara.cy , nTop );

	//第二个参数
	strPara2.Format(_T("%.3f%s"), m_fAngle,m_strUnit2);
	CSize szPara2 = pDC->GetTextExtent(strPara2);
	pDC->TextOut(nLeft + szPara.cy , nTop, strPara2);
	pDC->MoveTo(nLeft, nBom);
	pDC->LineTo(nLeft + szPara.cy + szPara2.cx , nBom);

	pDC->SelectObject(pOldFont);
// 	pDC->SelectObject(pOldPen);
// 	pOldPen  = NULL;
	pOldFont = NULL;
//	Pen.DeleteObject();
}

void CDrawMultiPara::GetDrawRectSize(long& cx,long& cy)
{
	CDC* pDC = m_pParentWnd->GetDC();
	CFont* pOldFont = pDC->SelectObject(m_pfPara);
	CString strPara,strPara2;

	//第一个参数
	strPara.Format(_T("%.3f%s"),m_fValue,m_strUnit);
	CSize szPara = pDC->GetTextExtent(strPara);	
	cy = szPara.cy + 2;
	cx = szPara.cx;
	
	//第二个参数
	strPara2.Format(_T("%.3f%s"), m_fAngle,m_strUnit2);
	CSize szPara2 = pDC->GetTextExtent(strPara2);
	cx += szPara2.cx;
	cx += cy;
	pDC->SelectObject(pOldFont);
	pOldFont = NULL;
	m_pParentWnd->ReleaseDC(pDC);
}

void CDrawMultiPara::Init(UINT nParaID,const CString& strUnit,PRTATTRIBUTECALFUNCPARA pCalFuncPara,CFont* pFont)
{
	if(pCalFuncPara == NULL)
		return;
	
	if(pCalFuncPara->pRtChAttrVal == NULL)
		return;
	
	m_pfPara = pFont;
	m_nParaID = nParaID;
}
