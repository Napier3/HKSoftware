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

CDrawVariable::CDrawVariable(CRulerAxis *pAxis)
{
	if (pAxis != NULL)
	{
		m_pRulerAxis = pAxis;
		m_bRulerAxisRef = TRUE;
	}
	else
	{
		m_bRulerAxisRef = FALSE;
	}

	m_rcName			= CRect(0,0,0,0);	
	m_rcAxis			= CRect(0,0,0,0);
	m_rcDraw			= CRect(0,0,0,0);
	m_rcNameRectOrigin  = CRect(0,0,0,0);
	m_nYCenter			= 0;
	m_pnAttachBuffer	= NULL;
	m_pptAttachDrawBuffer	= NULL;
	m_pClipRect			= NULL;
	m_pfAttachBuffer    = NULL;
	m_nTextHeight		= 14;
	m_bNeedDrawCenter   = FALSE;
	m_oNameFont.CreateFontIndirect(&MrDraw::g_lfDrawVariableName);
	m_oSelectNameFont.CreateFontIndirect(&MrDraw::g_lfDrawVariableSelectName);
	m_nSelectedState = DRAW_NONE_OBJECT_SELECTED;
	InitAxis();
	m_pDrawStruct = NULL;
}

CDrawVariable::CDrawVariable()
{
	m_pRulerAxis = new CRulerAxis();
	m_bRulerAxisRef = FALSE;

	m_rcName			= CRect(0,0,0,0);	
	m_rcAxis			= CRect(0,0,0,0);
	m_rcDraw			= CRect(0,0,0,0);
	m_rcNameRectOrigin  = CRect(0,0,0,0);
	m_nYCenter			= 0;
	m_pnAttachBuffer	= NULL;
	m_pptAttachDrawBuffer	= NULL;
	m_pClipRect			= NULL;
	m_pfAttachBuffer    = NULL;
	m_nTextHeight		= 14;
	m_bNeedDrawCenter   = FALSE;
	m_oNameFont.CreateFontIndirect(&MrDraw::g_lfDrawVariableName);
	m_oSelectNameFont.CreateFontIndirect(&MrDraw::g_lfDrawVariableSelectName);
	m_nSelectedState = DRAW_NONE_OBJECT_SELECTED;
	InitAxis();
	m_pDrawStruct = NULL;
}

void CDrawVariable::AttachAxis(CRulerAxis *pAxis)
{
	ASSERT (pAxis != NULL);

	if (m_pRulerAxis != NULL)
	{
		delete m_pRulerAxis;
		m_pRulerAxis = NULL;
	}

	m_pRulerAxis = pAxis;
	m_bRulerAxisRef = TRUE;
}

CDrawVariable::~CDrawVariable()
{
	if (m_bRulerAxisRef)
	{
		m_pRulerAxis = NULL;
	}
	else
	{
		m_bRulerAxisRef = FALSE;
		delete m_pRulerAxis;
		m_pRulerAxis = NULL;
	}

	m_pnAttachBuffer	= NULL;
	m_pptAttachDrawBuffer	= NULL;

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
	CXDrawElement::SetParentWnd(pParentWnd);
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

void CDrawVariable::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, ULONG dwDrawFlag) 
{
	if ((VARIABLE_DRAW_STYLE_NAME & dwDrawFlag) == VARIABLE_DRAW_STYLE_NAME)
	{
		DrawChanName(pDC, ((VARIABLE_DRAW_STYLE_CARRY_GRID & dwDrawFlag) == VARIABLE_DRAW_STYLE_CARRY_GRID));
	}
	
	if ((VARIABLE_DRAW_STYLE_CENTER & dwDrawFlag) == VARIABLE_DRAW_STYLE_CENTER)
	{
		if (m_bNeedDrawCenter)
		{
			CPen pen(PS_SOLID, 1, MrDraw::g_crAxisGrid);
			CPen *pPen = pDC->SelectObject(&pen);
			
			pDC->MoveTo(m_rcAxis.right, m_nYCenter);
			pDC->LineTo(Right(), m_nYCenter);
			
			pDC->SelectObject(pPen);
			pen.DeleteObject();
		}
	}
}

void CDrawVariable::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
{
}

void CDrawVariable::DrawAttrs(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag, MrDraw::DRAWMEMBUFFERPOS &oBufPos)
{

}

void CDrawVariable::InitAxis()
{
	m_pRulerAxis->SetRulerHalfScaleShow(1);
	m_pRulerAxis->SetRulerTenthScaleShow(0);
	m_pRulerAxis->SetRulerBoderShow(0);
	m_pRulerAxis->SetFrameRightBottomColor(RGB(0,0,0));
	m_pRulerAxis->SetDrawBack(0);
	m_pRulerAxis->SetMinSawGapWidth(15);
	m_pRulerAxis->SetRulerTypeVert();
	m_pRulerAxis->SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);
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
		CRect rcBorder = GetBorder();
		rcBorder.OffsetRect(nHor, nVer);
		
		SetBorder(rcBorder);
		PostDrawObjectPosChangedMsg();
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
}

void CDrawVariable::SetClipRect(const CRect &rcClip)
{
	if (m_pClipRect == NULL)
	{
		m_pClipRect = new CRect();
	}
	
	*m_pClipRect = rcClip;
}

void CDrawVariable::DrawChanName(CDC* pDC, BOOL bDrawCarryGrid)
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

	if (g_bInWriteBmpFileState)
	{
		crOld = pDC->SetTextColor(RGB(0, 0, 0));	
	}
	else
	{
		crOld = pDC->SetTextColor(m_crForeColor);	
	}

#ifdef _DEBUG
	CString strName;
	BOOL bBufferIsNull = FALSE;
	if (m_pnAttachBuffer == NULL)
	{
		bBufferIsNull = TRUE;
	}
	else 
	{
		if (m_pnAttachBuffer->GetBuffer() == NULL)
		{
			bBufferIsNull = TRUE;
		}
	}

	if (bBufferIsNull)
	{
		strName.Format("%s null", m_strName);
	}
	else
	{
		strName = m_strName;
	}

	pDC->DrawText(strName,m_rcName,DT_CENTER | DT_VCENTER | DT_SINGLELINE);

#else
	pDC->DrawText(m_strName,m_rcName,DT_CENTER | DT_VCENTER | DT_SINGLELINE);

#endif

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

void CDrawVariable::SetBorderLeft(long nLeft)
{
	long nWidth = m_rcDraw.left -  m_ptTopLeft.x;

	m_ptTopLeft.x = nLeft;
	m_rcDraw.left   = nLeft + nWidth;
}

void CDrawVariable::SetBorderRight(long nRight)
{
	m_nWidth = nRight - m_ptTopLeft.x;
	m_rcDraw.right   = nRight;
}

void CDrawVariable::SetBorderTop(long nTop)
{
	m_ptTopLeft.x = nTop;
	m_rcDraw.top   = nTop;
}

void CDrawVariable::SetBorderBottom(long nBottom)
{
	m_nHeight = nBottom - m_ptTopLeft.y;
	m_rcDraw.bottom   = nBottom;
}

void CDrawVariable::SetShow(long nShow)
{
	CXDrawElement::SetShow(nShow);

	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->nShow = nShow;
	}
}

void CDrawVariable::SetAttachStruct(PRECORDDRAWOBJECTCONTROL pDrawStruct)
{	
	m_pDrawStruct = pDrawStruct;

	if (m_pDrawStruct != NULL)
	{
		m_nShow = m_pDrawStruct->nShow;
		SetUse(m_pDrawStruct->nUse);
	}
}

void CDrawVariable::SaveDrawControl()
{
	double dTop = m_ptTopLeft.y;
	double dBottom = Bottom();
	
	if (m_pDrawStruct != NULL && m_pClipRect != NULL)
	{
		long nHeight = m_pClipRect->Height();
		dTop -= m_pClipRect->top;
		dBottom -= m_pClipRect->top;
		m_pDrawStruct->dCenter = (dTop + dBottom) / 2 / nHeight;
	}
}

void CDrawVariable::SaveDrawControl(double dCenter)
{
	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->dCenter = dCenter;
	}
}

// void CDrawVariable::SetBorder(const CRect &rect, BOOL bSavePos)
// {
// 	SetBorder(rect);
// 
// 	if (bSavePos)
// 	{
// 		SetDrawRectRatio();
// 	}
// }


void CDrawVariable::SetBorder(const CRect &rect)
{
	CXDrawElement::SetBorder(rect);
//	SaveDrawControl();
}

void CDrawVariable::ExpandBorder(long &l, long &t, long &r, long &b)
{
	CXDrawElement::ExpandBorder(l, t, r, b);
//	SaveDrawControl();
}

void CDrawVariable::SetUse(long nUse)
{
	CXDrawElement::SetUse(nUse);

	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->nUse = nUse;
	}
}