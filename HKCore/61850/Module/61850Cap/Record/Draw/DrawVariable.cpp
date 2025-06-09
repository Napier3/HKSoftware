// DrawVariable.cpp: implementation of the CDrawVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawVariable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawVariable::CDrawVariable()
{
	m_rcName			= CRect(0,0,0,0);	
	m_rcAxis			= CRect(0,0,0,0);
	m_rcDraw			= CRect(0,0,0,0);
	m_rcNameRectOrigin  = CRect(0,0,0,0);
	m_nYCenter			= 0;
	m_pnAttachBuffer	= NULL;
	m_pptAttachBuffer	= NULL;
	m_pClipRect			= NULL;
	m_pfAttachBuffer    = NULL;
	m_nTextHeight		= 16;
	m_bNeedDrawCenter   = FALSE;
	m_oNameFont.CreateFontIndirect(&MrDraw::g_lfDrawVariableName);
	m_oSelectNameFont.CreateFontIndirect(&MrDraw::g_lfDrawVariableSelectName);
	m_nSelectedState = DRAW_NONE_OBJECT_SELECTED;

	m_pDrawStruct = NULL;
}

CDrawVariable::~CDrawVariable()
{
	m_pnAttachBuffer	= NULL;
	m_pptAttachBuffer	= NULL;

	if(m_pClipRect != NULL)
	{
		delete m_pClipRect;
		m_pClipRect = NULL;
	}

	m_oNameFont.DeleteObject();
	m_oSelectNameFont.DeleteObject();

	m_pDrawStruct = NULL;
}

void CDrawVariable::SetParentWnd(CWnd* pParentWnd)
{
	CDrawBase::SetParentWnd(pParentWnd);
}

LONG CDrawVariable::MouseMove(UINT nFlags, CPoint &point)
{	
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawVariable::LButtonDown(UINT nFlags, CPoint &point)
{
	if (m_rcName.PtInRect(point)) 
	{
		g_ptOrigin = point;
		g_ptCurrent = point;
		m_nSelectedState = DRAW_HAS_OBJECT_SELECTED;
	}
	else
	{
		if (MrDraw::PointInRect(point, m_rcAxis))//m_rcAxis.PtInRect(point))
		{
			g_ptOrigin = point;
			g_ptCurrent = point;
			m_nSelectedState = DRAW_HAS_OBJECT_SELECTED;
		}
		else
		{
			m_nSelectedState = DRAW_NONE_OBJECT_SELECTED;
		}

	}

	return m_nSelectedState;
}

void CDrawVariable::SetSelect(BOOL bSelect) 
{   
	m_bSelect = bSelect;     
    ClearSelectState();
}

LONG CDrawVariable::LButtonUp(UINT nFlags, CPoint &point)
{
	return m_nSelectedState;
}

LONG CDrawVariable::RButtonDown(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawVariable::RButtonUp(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

BOOL CDrawVariable::PointInRgn(CPoint &pt) 
{
	if (m_rcName.PtInRect(pt))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

void CDrawVariable::Draw(CDC *pDC, ULONG nDrawStyle) 
{
	if ((VARIABLE_DRAW_STYLE_NAME & nDrawStyle) == VARIABLE_DRAW_STYLE_NAME)
	{
		DrawChanName(pDC);
	}
	
	if ((VARIABLE_DRAW_STYLE_CENTER & nDrawStyle) == VARIABLE_DRAW_STYLE_CENTER)
	{
		if (m_bNeedDrawCenter)
		{
			CPen pen(PS_SOLID, 1, MrDraw::g_crAxisGrid);
			CPen *pPen = pDC->SelectObject(&pen);
			
			pDC->MoveTo(m_rcAxis.right,m_nYCenter);
			pDC->LineTo(m_rcBorder.right,m_nYCenter);
			
			pDC->SelectObject(pPen);
			pen.DeleteObject();
		}
	}
}

void CDrawVariable::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
{
}

void CDrawVariable::InitAxisSet()
{
	m_oRulerAxis.SetRulerHalfScaleShow(1);
	m_oRulerAxis.SetRulerTenthScaleShow(0);
	m_oRulerAxis.SetRulerBoderShow(0);
	m_oRulerAxis.SetFrameRightBottomColor(RGB(0,0,0));
	m_oRulerAxis.SetDrawBack(0);
	m_oRulerAxis.SetMinSawGapWidth(15);
	m_oRulerAxis.SetRulerTypeVert();
	m_oRulerAxis.SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);
}

void CDrawVariable::CalTextHeight(CDC *pDC)
{
	CFont *pOldFont = pDC->SelectObject(&m_oNameFont);
	CSize szName = pDC->GetTextExtent(m_strName); 
	pDC->SelectObject(pOldFont);
	m_nTextHeight = szName.cy;
	m_pParentWnd->ReleaseDC(pDC);
	pOldFont = NULL;	
}

void CDrawVariable::Move(long nHor, long nVer, BOOL bUseAcc) 
{
#ifdef USE_OPTR_ACC
	if (bUseAcc)
	{
		Rt_OptrAcc("DrawVariable::Move", nHor, nVer);
	}
#endif

	nHor = 0;
	
	if (nVer != 0 || nHor != 0) 
	{
		CRect rcBorder = m_rcBorder;
		rcBorder.OffsetRect(nHor, nVer);
		
		SetBorder(rcBorder);
		
		if (m_pParentWnd != NULL)
		{
			if (::IsWindow(m_pParentWnd->m_hWnd)) 
			{
				m_pParentWnd->PostMessage(WM_VARIABLE_POS_CHANGED, 0, 0);
			}
		}
	}
}

void CDrawVariable::Zoom(double dRate) 
{
}

void CDrawVariable::SetAxisHeight(long nHeight) 
{
}

void CDrawVariable::MoveAxis(long nVertOffset)	 
{
}

void CDrawVariable::InitAxis(long nAxisRight)
{
	m_nYCenter = m_rcBorder.CenterPoint().y;
}

void CDrawVariable::SetClipRect(const CRect &rcClip)
{
	if (m_pClipRect == NULL)
	{
		m_pClipRect = new CRect();
	}
	
	*m_pClipRect = rcClip;
}

void CDrawVariable::DrawChanName(CDC* pDC)
{
	int nMode = pDC->SetBkMode(TRANSPARENT);
	long nSrcBegin = 0;
	long nSrcLen = 0;
	CFont *pOldFont = NULL;
	

	if (GetSelect())
	{
		pOldFont = pDC->SelectObject(&m_oSelectNameFont);
	}
	else
	{
		pOldFont = pDC->SelectObject(&m_oNameFont);//
	}
	
	COLORREF crOld ;
	crOld = pDC->SetTextColor(m_crColor);	
	pDC->DrawText(m_strName,m_rcName,DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	pDC->SelectObject(pOldFont);
	pDC->SetTextColor(crOld);
	pDC->SetBkMode(nMode);
	pOldFont = NULL;
}

void CDrawVariable::SetNameRect(long nLeft, long nTop, long nRight, long nBottom)
{
	m_rcName.left = nLeft;
	m_rcName.right = nRight;
	m_rcName.top = nTop;
	m_rcName.bottom =  nBottom;
	//TRACE("m_rcName=%d %d %d %d\n", m_rcName.left, m_rcName.top, m_rcName.right, m_rcName.bottom);
}

void CDrawVariable::SetNameRect(const CRect &rc)
{
	m_rcName = rc;
	//TRACE("m_rcName=%d %d %d %d\n", m_rcName.left, m_rcName.top, m_rcName.right, m_rcName.bottom);
}

void CDrawVariable::SetNameRectTop(long nVal)
{
	m_rcName.top = nVal;
	//TRACE("m_rcName=%d %d %d %d\n", m_rcName.left, m_rcName.top, m_rcName.right, m_rcName.bottom);
}

void CDrawVariable::SetNameRectBottom(long nVal)
{
	m_rcName.bottom = nVal;
	TRACE("m_rcName=%d %d %d %d\n", m_rcName.left, m_rcName.top, m_rcName.right, m_rcName.bottom);
}

void CDrawVariable::SetNameRectLeft(long nVal)
{
	m_rcName.left = nVal;
	//TRACE("m_rcName=%d %d %d %d\n", m_rcName.left, m_rcName.top, m_rcName.right, m_rcName.bottom);
}

void CDrawVariable::SetNameRectRight(long nVal)
{
	m_rcName.right = nVal;
	//TRACE("m_rcName=%d %d %d %d\n", m_rcName.left, m_rcName.top, m_rcName.right, m_rcName.bottom);
}


void CDrawVariable::SetParaRectTop(long nVal)
{
	m_rcName.top = nVal;
	//TRACE("m_rcName=%d %d %d %d\n", m_rcName.left, m_rcName.top, m_rcName.right, m_rcName.bottom);
}

void CDrawVariable::SetParaRectBottom(long nVal)
{
	m_rcName.bottom = nVal;
	TRACE("m_rcName=%d %d %d %d\n", m_rcName.left, m_rcName.top, m_rcName.right, m_rcName.bottom);
}

void CDrawVariable::SetBorderLeft(long nLeft)
{
	long nWidth = m_rcDraw.left -  m_rcBorder.left;

	m_rcBorder.left = nLeft;
	m_rcDraw.left   = nLeft + nWidth;
}

void CDrawVariable::SetBorderRight(long nRight)
{
	m_rcBorder.right = nRight;
	m_rcDraw.right   = nRight;
}

void CDrawVariable::SetBorderTop(long nTop)
{
	m_rcBorder.top = nTop;
	m_rcDraw.top   = nTop;
}

void CDrawVariable::SetBorderBottom(long nBottom)
{
	m_rcBorder.bottom = nBottom;
	m_rcDraw.bottom   = nBottom;
}

void CDrawVariable::SetShow(long nShow)
{
	CDrawBase::SetShow(nShow);

	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->nShow = nShow;
	}
}

void CDrawVariable::SetAttachStruct(PDRAWVAR pDrawStruct)
{	
	m_pDrawStruct = pDrawStruct;

	if (m_pDrawStruct != NULL)
	{
		m_nShow = m_pDrawStruct->nShow;
		SetUse(m_pDrawStruct->nUse);
	}
}

void CDrawVariable::SetDrawRectRatio()
{
	double dTop = m_rcBorder.top;
	double dBottom = m_rcBorder.bottom;
	
	if (m_pDrawStruct != NULL && m_pClipRect != NULL)
	{
		long nHeight = m_pClipRect->Height();
		dTop -= m_pClipRect->top;
		dBottom -= m_pClipRect->top;

		m_pDrawStruct->dTopRatio = dTop / nHeight;
		m_pDrawStruct->dBottomRatio = dBottom / nHeight;
	}
}

void CDrawVariable::SetBorder(const CRect &rect, BOOL bSavePos)
{
	SetBorder(rect);

	if (bSavePos)
	{
		SetDrawRectRatio();
	}
}


void CDrawVariable::SetBorder(const CRect &rect)
{
	CDrawBase::SetBorder(rect);
	m_nYCenter = m_rcBorder.CenterPoint().y;
	SetDrawRectRatio();
}

void CDrawVariable::ExpandBorder(long &l, long &t, long &r, long &b)
{
	CDrawBase::ExpandBorder(l, t, r, b);
	SetDrawRectRatio();
}

void CDrawVariable::SetUse(long nUse)
{
	CDrawBase::SetUse(nUse);

	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->nUse = nUse;
	}
}