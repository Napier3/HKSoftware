// DrawTrigCursor.cpp: implementation of the CDrawTrigCursor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawTrigCursor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawTrigCursor::CDrawTrigCursor()
{
	m_ptTrig[0] = CPoint(10,20);
	m_ptTrig[1] = CPoint(20,20);
	m_ptTrig[2] = CPoint(20,10);
	m_ptTrig[3] = CPoint(30,10);
	m_bCanbeMove = FALSE;
	m_rcClipRect = CRect(0,0,0,0);
	m_pDrawStruct = NULL;
	m_crColor = RGB(255, 255, 0);
}

CDrawTrigCursor::~CDrawTrigCursor()
{
	m_pDrawStruct = NULL;
}

void CDrawTrigCursor::Move(long nHor, long nVer , BOOL bUseAcc)
{
#ifdef USE_OPTR_ACC
	if (bUseAcc)
	{
		Rt_OptrAcc("DrawTrigCursor::Move", nHor, nVer);
	}
#endif
	
	if (nHor != 0 || nVer != 0) 
	{
		int nTop , nBottom , nLeft , nRight;
		nTop	 = m_ptTrig[3].y + nVer;
		nBottom  = m_ptTrig[0].y + nVer;
		nLeft    = m_ptTrig[0].x + nHor;
		nRight   = m_ptTrig[3].x + nHor;	
		CPoint ptOffSet(nHor , nVer);
		EraseTrigCursor();
		SetTrigCursorPosition(nLeft , nTop , nRight , nBottom , ptOffSet);
		EraseTrigCursor();
	}
}

void CDrawTrigCursor::Draw(CDC *pDC, ULONG nDrawStyle) 
{
	if (m_nShow == 1)
	{
		CPen TrigPen(PS_SOLID,1,m_crColor);
		CPen* pOldPen = pDC->SelectObject(&TrigPen);
		pDC->Polyline(m_ptTrig,4);
		pDC->SelectObject(pOldPen);
		TrigPen.DeleteObject();
		pOldPen = NULL;
	}
}

LONG CDrawTrigCursor::MouseMove(UINT nFlags, CPoint &point)
{
	if (m_bSelect && m_bCanbeMove)
	{
		CPoint ptOffSet =   point - g_ptCurrent;
		int nTop , nBottom , nLeft , nRight;
		nTop	 = m_ptTrig[3].y + ptOffSet.y;
		nBottom  = m_ptTrig[0].y + ptOffSet.y;
		nLeft    = m_ptTrig[0].x + ptOffSet.x;
		nRight   = m_ptTrig[3].x + ptOffSet.x;		
		
		EraseTrigCursor();
		SetTrigCursorPosition(nLeft , nTop , nRight , nBottom , ptOffSet);
		g_ptCurrent = point;
		EraseTrigCursor();
	}

	return 0;
}

LONG CDrawTrigCursor::LButtonDown(UINT nFlags, CPoint &point)
{
	if (PointInRgn(point))
	{
		g_ptCurrent  = point;
		SetSelect(TRUE);
		m_bCanbeMove = TRUE;
		g_ptOrigin   = point;
		
		return DRAW_HAS_OBJECT_SELECTED;
	}
	
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawTrigCursor::LButtonUp(UINT nFlags, CPoint &point)
{
	m_bCanbeMove = FALSE;

	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawTrigCursor::RButtonDown(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawTrigCursor::RButtonUp(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

BOOL CDrawTrigCursor::PointInRgn(CPoint &pt)
{
	if (m_nShow == 0)
	{
		return FALSE;
	}
	
	CRect rect1,rect2,rect3;//×óÖÐÓÒ
	rect1 = CRect(m_ptTrig[0].x , m_ptTrig[0].y - 3 , m_ptTrig[1].x - 3 , m_ptTrig[0].y + 3);
	rect2 = CRect(m_ptTrig[1].x - 3 , m_ptTrig[2].y - 3 , m_ptTrig[1].x + 3 , m_ptTrig[1].y + 3);
	rect3 = CRect(m_ptTrig[2].x + 3 , m_ptTrig[2].y - 3 , m_ptTrig[3].x  , m_ptTrig[2].y + 3);

	if (rect1.PtInRect(pt) || rect2.PtInRect(pt) || rect3.PtInRect(pt))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

void CDrawTrigCursor::SetCursorPosition(const CPoint &point) 
{
}

void CDrawTrigCursor::EraseTrigCursor()
{
	CRect rect = CRect(m_ptTrig[0].x - 1 , m_ptTrig[0].y + 1 , m_ptTrig[3].x + 1 , m_ptTrig[3].y - 1);
	m_pParentWnd->InvalidateRect(rect,FALSE);
}

void CDrawTrigCursor::SetClipRect(const CRect &rect)     
{    
	m_rcClipRect = rect;    
	int nTop , nBottom , nLeft , nRight;
	nTop	 = m_ptTrig[3].y ;
	nBottom  = m_ptTrig[0].y ;
	nLeft    = m_ptTrig[0].x ;
	nRight   = m_ptTrig[3].x ;	
	SetTrigCursorPosition(nLeft , nTop , nRight , nBottom );
}

void CDrawTrigCursor::SetTrigCursorPosition(long nLeft, long nTop, long nRight ,long nBottom , CPoint ptOffSet)
{
	if (nTop >= m_rcClipRect.top && nBottom <= m_rcClipRect.bottom && nRight <= m_rcClipRect.right && nLeft >=m_rcClipRect.left)
	{
		m_ptTrig[0] = m_ptTrig[0] + ptOffSet;
		m_ptTrig[1] = m_ptTrig[1] + ptOffSet;
		m_ptTrig[2] = m_ptTrig[2] + ptOffSet;
		m_ptTrig[3] = m_ptTrig[3] + ptOffSet;
	}
	else
	{
		if (nTop < m_rcClipRect.top)
		{
			m_ptTrig[3].y = m_rcClipRect.top;
			m_ptTrig[2].y = m_rcClipRect.top;
			m_ptTrig[1].y = m_rcClipRect.top + 10;
			m_ptTrig[0].y = m_rcClipRect.top + 10;
		}
		
		if (nBottom > m_rcClipRect.bottom)
		{
			m_ptTrig[0].y = m_rcClipRect.bottom;
			m_ptTrig[1].y = m_rcClipRect.bottom;
			m_ptTrig[2].y = m_rcClipRect.bottom - 10;
			m_ptTrig[3].y = m_rcClipRect.bottom - 10;
		}
		
		if (nLeft < m_rcClipRect.left)
		{
			m_ptTrig[0].x = m_rcClipRect.left;
			m_ptTrig[1].x = m_rcClipRect.left + 10;
			m_ptTrig[2].x = m_rcClipRect.left + 10;
			m_ptTrig[3].x = m_rcClipRect.left + 20;
		}
		
		if (nRight > m_rcClipRect.right)
		{
			m_ptTrig[3].x = m_rcClipRect.right;
			m_ptTrig[2].x = m_rcClipRect.right - 10;
			m_ptTrig[1].x = m_rcClipRect.right - 10;
			m_ptTrig[0].x = m_rcClipRect.right - 20;
		}
	}

	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->ptTrigCursor = m_ptTrig[2];
	}
}

void CDrawTrigCursor::ShowSet(long nShow)
{
	m_nShow = nShow;

	if (nShow == 0)
	{
		m_bCanbeMove = FALSE;
		SetSelect(FALSE);
	}
}

BOOL CDrawTrigCursor::SetTrigCursorPos(long nXPos,long nYPos)
{
	long nLeft  = nXPos - 10;
	long nRight = nXPos + 10;
	long nTop   = nYPos;
	long nBom   = nYPos + 10;
	BOOL bSet = FALSE;
	
	if (nTop >= m_rcClipRect.top && nBom <= m_rcClipRect.bottom && nRight <= m_rcClipRect.right && nLeft >=m_rcClipRect.left)
	{
		m_ptTrig[0].x = nXPos - 10;
		m_ptTrig[0].y = nYPos + 10;
		
		m_ptTrig[1].x = nXPos;
		m_ptTrig[1].y = nYPos + 10;
		
		m_ptTrig[2].x = nXPos;
		m_ptTrig[2].y = nYPos;
		
		m_ptTrig[3].x = nXPos + 10;
		m_ptTrig[3].y = nYPos;

		bSet = TRUE;
	}
	else
	{
	}

	return bSet;
}