// DrawTimeCursor.cpp: implementation of the CDrawTimeCursor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawTimeCursor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char* CDrawTimeCursor::g_pszKeyZoomBmp				= "Zoom.bmp";

CDrawTimeCursor::CDrawTimeCursor()
{
	m_nCurrCursorID	= 0;
	m_nXA			= 200;
	m_nXB			= 300;
	m_nXAOld		= 200;
	m_nXBOld		= 300;
	m_crATimeCursorColor = RGB(255,0,0);
	m_crBTimeCursorColor = RGB(0,0,255);
	m_ACursorPen.CreatePen(PS_SOLID,1,m_crATimeCursorColor);
	m_BCursorPen.CreatePen(PS_SOLID,1,m_crBTimeCursorColor);
	m_bCanMoveACursor	= FALSE;
	m_bCanMoveBCursor  = FALSE;
	CString str;
	str = _P_GetConfigPath();
	str += _T("Bitmaps\\Zoom.bmp");
	m_bUseZoomBmp = m_oDib.Load(str);
	m_nCurrCursorID = USETIMECURSORA;
	m_nZoomMode = -1;
	m_hMoveCursor = NULL;
}

CDrawTimeCursor::~CDrawTimeCursor()
{
	m_ACursorPen.DeleteObject();
	m_BCursorPen.DeleteObject();
}

LONG CDrawTimeCursor::MouseMove(UINT nFlags, CPoint &point)
{
	if (m_bSelect)
	{
		long nCurrentX = point.x;

		if (m_nCurrCursorID == USETIMECURSORA)
		{
			if (m_bCanMoveACursor)
			{	
				::SetCursor(m_hMoveCursor);				
				m_nXAOld = m_nXA;
				ChangeCursorPosition(m_nXA , nCurrentX);
				SetZoomRect();

				if (m_pParentWnd != NULL)
				{
					if (::IsWindow(m_pParentWnd->m_hWnd))
					{						
						m_pParentWnd->PostMessage(WM_TIMECURSOR_POS_CHANGE,(WPARAM)this, 0);
					}
				}

				return DRAW_HAS_OBJECT_SELECTED;
			}
		}
		else
		{
			if (m_bCanMoveBCursor)
			{
				::SetCursor(m_hMoveCursor);
				m_nXBOld = m_nXB;

				ChangeCursorPosition(m_nXB , nCurrentX);
				SetZoomRect();

				if (m_pParentWnd != NULL)
				{
					m_pParentWnd->PostMessage(WM_TIMECURSOR_POS_CHANGE, (WPARAM)this, 0);
				}

				return DRAW_HAS_OBJECT_SELECTED;
			}	
		}

		
	}

	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawTimeCursor::LButtonDown(UINT nFlags, CPoint &point)
{
	if (PointInRgn(point))
	{
		SetSelect(TRUE);
		
		return DRAW_HAS_OBJECT_SELECTED;
	}

	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawTimeCursor::LButtonUp(UINT nFlags, CPoint &point)
{
	m_bCanMoveACursor  = FALSE;
	m_bCanMoveBCursor  = FALSE;

	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawTimeCursor::RButtonDown(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawTimeCursor::RButtonUp(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

BOOL CDrawTimeCursor::PointInRgn(CPoint &pt) 
{
	if (m_nShow == 0)
	{
		SetSelect(FALSE);
		return FALSE;
	}

	CRect rectA = CRect(m_nXA - 4, m_rcBorder.top , m_nXA + 5 , m_rcBorder.bottom);
	CRect rectB = CRect(m_nXB - 4, m_rcBorder.top , m_nXB + 5 , m_rcBorder.bottom);
	
	if (m_rcZoomBmp.PtInRect(pt)) 
	{
		SetZoomMode(pt);

		if (m_pParentWnd != NULL)
		{
			if (::IsWindow(m_pParentWnd->m_hWnd))
			{				
				m_pParentWnd->PostMessage(WM_TIME_CHANGED, (WPARAM)this ,(LPARAM)m_nZoomMode);
			}
		}
	}
	else
	{
		if (rectA.PtInRect(pt))
		{
			g_ptOrigin  = pt;
			m_nCurrCursorID = USETIMECURSORA;
			SetSelect(TRUE);
			m_bCanMoveACursor  = TRUE;
			m_bCanMoveBCursor  = FALSE;
		}
		else if (rectB.PtInRect(pt))
		{
			m_nCurrCursorID = USETIMECURSORB;
			g_ptOrigin  = pt;
			SetSelect(TRUE);
			m_bCanMoveACursor  = FALSE;
			m_bCanMoveBCursor  = TRUE;
		}
		else
		{
			SetSelect(FALSE);
			return FALSE;
		}

		if (m_pParentWnd != NULL)
		{
			if (::IsWindow(m_pParentWnd->m_hWnd))
			{				
				m_pParentWnd->PostMessage(WM_TIMECURSOR_SELECT_CHANGE, (WPARAM)this , 0);
			}
		}
	}
	
	return TRUE;
}

void CDrawTimeCursor::Draw(CDC *pDC, ULONG nDrawStyle) 
{	
	if (m_nShow == 1)
	{
		DrawACursor(pDC);
		DrawBCursor(pDC);

		if (m_bUseZoomBmp) 
		{
			m_oDib.Draw(pDC,m_rcZoomBmp);
		}
	}
}

void CDrawTimeCursor::Move(long nHor, long nVer,BOOL bUseAcc) 
{
#ifdef USE_OPTR_ACC
	if (bUseAcc)
	{
		Rt_OptrAcc("CDrawTimeCursor::Move", nHor, nVer);
	}
#endif

	switch(m_nCurrCursorID) 
	{
	case USETIMECURSORA:
		{
			m_nXAOld = m_nXA;
			long nCurrentX = m_nXA + nHor;
			ChangeCursorPosition(m_nXA , nCurrentX);
			SetZoomRect();
		}
		break;
	case USETIMECURSORB:
		{
			m_nXBOld = m_nXB;
			long nCurrentX = m_nXB + nHor;
			ChangeCursorPosition(m_nXB , nCurrentX);
			SetZoomRect();
		}
		break;
	default:
		break;
	}

	if (m_pParentWnd != NULL)
	{
		if (::IsWindow(m_pParentWnd->m_hWnd))
		{			
			m_pParentWnd->PostMessage(WM_TIMECURSOR_POS_CHANGE, (WPARAM)this , 0);
		}
	}
}

void CDrawTimeCursor::SetCurrentCursor(long nCursorID)
{
	m_nCurrCursorID = nCursorID;
	SetZoomRect();
	
	if (m_pParentWnd != NULL)
	{
		if (::IsWindow(m_pParentWnd->m_hWnd))
		{
			m_pParentWnd->PostMessage(WM_TIMECURSOR_SELECT_CHANGE, (WPARAM)this ,0);
		}
	}
}

long CDrawTimeCursor::GetCurrCursorID()
{
	return m_nCurrCursorID;
}

long CDrawTimeCursor::GetCurrentCursorPosition()
{
	long nPos = m_nXA;

	if (m_nCurrCursorID == USETIMECURSORB) 
	{
		nPos = m_nXB;
	}

	return nPos;
}

long CDrawTimeCursor::SetCursorPosition(long nPos, long nCursorID)
{
	m_nCurrCursorID = nCursorID;

	switch(nCursorID) 
	{
	case USETIMECURSORA:
		m_nXA = nPos;
		break;
	case USETIMECURSORB:
		m_nXB = nPos;
		break;
	default:
		m_nXA = nPos;
		break;
	}

	return m_nCurrCursorID;
}

long CDrawTimeCursor::GetCursorPosition(long nCursorID)
{
	long nPos = m_nXA;

	if (nCursorID == USETIMECURSORB)
	{
		nPos = m_nXB;
	}

	return nPos;
}

void CDrawTimeCursor::EraseATimeLine()
{	
	CRect rectA = CRect(m_nXA - 5, m_rcBorder.top , m_nXA + 6 , m_rcBorder.bottom);
	m_pParentWnd->InvalidateRect(rectA,FALSE);
}

void CDrawTimeCursor::EraseBTimeLine()
{
	CRect rectB = CRect(m_nXB - 5, m_rcBorder.top , m_nXB + 6 , m_rcBorder.bottom);
	m_pParentWnd->InvalidateRect(rectB,FALSE);
}

//暂时把绘制区域视为整个波形区域
void CDrawTimeCursor::SetBorder(const CRect &rect)
{
	CDrawBase::SetBorder(rect);
	m_nXB      = rect.left + rect.Width() / 3 * 2;
	m_nXA	   = rect.left + rect.Width() / 3;

	m_nXA = min(80, m_nXA);

	m_nXAOld   = m_nXA;
	m_nXBOld   = m_nXB;

	SetZoomRect();
}

void CDrawTimeCursor::DrawACursor(CDC *pDC)
{
	CPen* pOldPen = NULL;
	pOldPen = pDC->SelectObject(&m_ACursorPen);
	pDC->MoveTo(m_nXA,m_rcBorder.top);
	pDC->LineTo(m_nXA,m_rcBorder.bottom);
	pDC->SelectObject(pOldPen);
	pOldPen = NULL;
}

void CDrawTimeCursor::DrawBCursor(CDC *pDC)
{
	CPen* pOldPen = pDC->SelectObject(&m_BCursorPen);
	pDC->MoveTo(m_nXB,m_rcBorder.top);
	pDC->LineTo(m_nXB,m_rcBorder.bottom);
	pDC->SelectObject(pOldPen);
	pOldPen = NULL;
}

void CDrawTimeCursor::ChangeCursorPosition(long& nPosition,long nCurrentX)
{
	if (nCurrentX < m_rcBorder.left)
	{
		nPosition = m_rcBorder.left;
	}
	else if (nCurrentX > m_rcBorder.right)
	{
		nPosition = m_rcBorder.right;
	}
	else
	{
		nPosition = nCurrentX;
	}
}

void CDrawTimeCursor::ShowSet(long nShow)
{
	m_nShow = nShow;

	if (nShow ==0)
	{
		m_bCanMoveACursor  = FALSE;
		m_bCanMoveBCursor  = FALSE;
		SetSelect(FALSE);
	}
}

void CDrawTimeCursor::GetCurrCursorInvalidateRect(CRect &rcOld, CRect &rcNew)
{
	switch(m_nCurrCursorID)
	{
	case USETIMECURSORA:
		{
			rcOld.left = m_nXAOld - WIDTHTOCENTER - 1 ;
			rcOld.top = m_rcBorder.top;
			rcOld.right = m_nXAOld + WIDTHTOCENTER + 2 ;
			rcOld.bottom = m_rcBorder.bottom;

			rcNew.left = m_nXA - WIDTHTOCENTER - 1 ;
			rcNew.top = m_rcBorder.top;
			rcNew.right = m_nXA + WIDTHTOCENTER + 2 ;
			rcNew.bottom = m_rcBorder.bottom;
		}
		break;
	case USETIMECURSORB:
		{
			rcOld.left = m_nXBOld - WIDTHTOCENTER - 1 ;
			rcOld.top = m_rcBorder.top;
			rcOld.right = m_nXBOld + WIDTHTOCENTER + 2 ;
			rcOld.bottom = m_rcBorder.bottom;
			
			rcNew.left = m_nXB - WIDTHTOCENTER - 1 ;
			rcNew.top = m_rcBorder.top;
			rcNew.right = m_nXB + WIDTHTOCENTER + 1 ;
			rcNew.bottom = m_rcBorder.bottom;
		}
		break;
	default:
		break;
	}
}


void CDrawTimeCursor::GetInvalidateRect(CRect &rcOld, CRect &rcNew)
{
	rcOld.left = m_nXA - WIDTHTOCENTER - 1 ;
	rcOld.top = m_rcBorder.top;
	rcOld.right = m_nXA + WIDTHTOCENTER + 2 ;
	rcOld.bottom = m_rcBorder.bottom;
	
	rcNew.left = m_nXB - WIDTHTOCENTER - 2 ;
	rcNew.top = m_rcBorder.top;
	rcNew.right = m_nXB + WIDTHTOCENTER + 2  ;
	rcNew.bottom = m_rcBorder.bottom;
}

void CDrawTimeCursor::SetZoomRect()
{
	if (m_bUseZoomBmp == TRUE)
	{
		m_rcZoomBmpOld = m_rcZoomBmp;
		long nPos	 = GetCurrentCursorPosition();
		CRect rc	 = m_oDib.GetDibRect(); 
		long nWidth  = rc.Width();
		long nHeight = rc.Height();
		
		m_rcZoomBmp.left  = nPos - nWidth / 2;
		m_rcZoomBmp.right = m_rcZoomBmp.left + nWidth;
		
		if (m_rcZoomBmp.left < m_rcBorder.left)
		{
			m_rcZoomBmp.left  = m_rcBorder.left;
			m_rcZoomBmp.right = m_rcZoomBmp.left + nWidth;
		}
		
		if (m_rcZoomBmp.right > m_rcBorder.right)
		{
			m_rcZoomBmp.right = m_rcBorder.right;
			m_rcZoomBmp.left  = m_rcZoomBmp.right - nWidth;
		}
		m_rcZoomBmp.top    = m_rcBorder.top;
		m_rcZoomBmp.bottom   = m_rcZoomBmp.top + nHeight;
		
	}

}

void CDrawTimeCursor::SetZoomMode(CPoint point)
{
	CRect rcZoomIn, rcZoomOut,rcRevert;
	rcRevert  = m_rcZoomBmp;
	rcZoomIn  = m_rcZoomBmp;
	rcZoomOut = m_rcZoomBmp;
	long nWidth = m_rcZoomBmp.Width() / 3;
	long nLeft  = m_rcZoomBmp.left;
	rcZoomOut.left = nLeft;
	rcZoomOut.right = nWidth + rcZoomIn.left - 1;
	rcZoomIn.left = nLeft + nWidth;
	rcZoomIn.right = nWidth + rcZoomIn.left - 1;
	rcRevert.left  = rcZoomIn.right + 1;
	rcRevert.right = m_rcZoomBmp.right;
			
	if (rcZoomIn.PtInRect(point))
	{
		m_nZoomMode = 0;
	}
	else if (rcZoomOut.PtInRect(point))
	{
		m_nZoomMode = 1;
	}
	else if (rcRevert.PtInRect(point))
	{
		m_nZoomMode = 2;
	}
	else
	{
		m_nZoomMode = -1;
	}
}
