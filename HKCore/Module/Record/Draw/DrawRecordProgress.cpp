// DrawRecordProgress.cpp: implementation of the CDrawRecordProgress class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawRecordProgress.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawRecordProgress::CDrawRecordProgress()
{
	m_n64DataLength		 = 0;
	m_n64CurrDataPos	 = 0;
	m_nOldPos			 = 0;
	m_nProgressRectWidth = 400;
	m_crBackColor		 = RGB(255,255,255);
	m_crColor            = RGB(255,255,0);
}

CDrawRecordProgress::~CDrawRecordProgress()
{
}

void CDrawRecordProgress::Draw(CDC* pDC)
{
	pDC->FillSolidRect(m_rcBorder,m_crBackColor);
	StepIt(pDC);
}

//数据缓存可能很长，将其转成一个较短的值
void CDrawRecordProgress::SetLength(__int64 n64Length)
{
	m_n64DataLength = n64Length;
}

void CDrawRecordProgress::SetCurrPos(__int64 n64Pos)
{
	m_n64CurrDataPos = n64Pos;
	CDC* pDC = m_pParentWnd->GetDC();
	StepIt(pDC);
	m_pParentWnd->ReleaseDC(pDC);
}

void CDrawRecordProgress::StepIt(CDC* pDC)
{
	CPoint ptCenter = m_rcBorder.CenterPoint();
	double dRate = m_n64CurrDataPos * 1.0 / m_n64CurrDataPos;
	long nCurrentDraw = (long)(dRate * m_rcBorder.Width()) ;
	CPen MyPen(PS_SOLID,2,m_crColor);
	CPen* pOldPen = pDC->SelectObject(&MyPen);
	pDC->MoveTo(m_nOldPos ,ptCenter.y);
	pDC->LineTo(ptCenter.x + nCurrentDraw, ptCenter.y);
	pDC->SelectObject(pOldPen);
	MyPen.DeleteObject();
	pOldPen = NULL;
	m_nOldPos = ptCenter.x + nCurrentDraw;
}

void CDrawRecordProgress::SetBorder(const CRect &rect) 
{   
	m_rcBorder = rect; 
	m_rcBorder.top += SPACE_TO_BORDER;
	m_rcBorder.bottom -= SPACE_TO_BORDER;
	m_nOldPos  = rect.left;
}
