// DrawAttrSpy.cpp: implementation of the CDrawAttrSpy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawAttrSpy.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawAttrSpy::CDrawAttrSpy()
{
	m_bNeedModifyCenter = FALSE ;
	m_nRangeMask		= 0;
	m_dRangeMin			= 0;
	m_dRangeMax			= 0;
	m_dRange			= 0;	
	m_dCoefValue		= 1;
	m_nAttrDataIndex	= 0;
	m_strUnit			= "";
}

CDrawAttrSpy::~CDrawAttrSpy()
{
}

void CDrawAttrSpy::SetBorder(const CRect &rect)
{
	CDrawBase::SetBorder(rect);
	InitAxis(MrDraw::g_snNameandAxisRectWidth);
}

void CDrawAttrSpy::InitAxis(long nAxisRight)
{
	m_oRulerAxis.SetRulerTypeVert();
	m_oRulerAxis.SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);
	m_oRulerAxis.SetBorder(m_rcAxis);
	m_oRulerAxis.SetMinSawGapWidth(15);
	m_oRulerAxis.SetRulerHalfScaleShow(1);
	m_oRulerAxis.SetRulerTenthScaleShow(0);
	m_oRulerAxis.SetRulerBoderShow(0);
	m_oRulerAxis.SetFrameRightBottomColor(RGB(0,0,0));
	m_oRulerAxis.SetDrawBack(0);

	m_rcAxis = m_rcBorder;
	m_rcAxis.right = nAxisRight;	
	long nWidth = m_oRulerAxis.GetRulerHeight();//得到标尺的宽度
	m_rcAxis.left = nAxisRight - nWidth;
	m_oRulerAxis.SetBorder(m_rcAxis);	
	m_rcDraw = m_rcBorder;
	m_rcDraw.left = nAxisRight;
	double dCoef ;
	m_oRulerAxis.GetAxisInterface(dCoef,m_nYCenter);
	
	if (!m_bNeedModifyCenter)
	{
		m_nYCenter = (m_rcAxis.top + m_rcAxis.bottom) / 2;
	}

	nWidth = 0;
	SetNameRect(m_rcBorder.left,m_nYCenter - m_nTextHeight / 2, nAxisRight - nWidth, m_nYCenter + m_nTextHeight / 2);
	m_rcNameRectOrigin  = m_rcName;
}

void CDrawAttrSpy::ExpandBorder(long &l, long &t, long &r, long &b)
{
	l = 0;
	r = 0;
	CDrawBase::ExpandBorder(l, t, r, b);
	InitAxis(MrDraw::g_snNameandAxisRectWidth);

	if (m_pParentWnd != NULL)
	{
		if (::IsWindow(m_pParentWnd->m_hWnd))
		{			
			m_pParentWnd->PostMessage(WM_VARIABLE_POS_CHANGED, 0, 0);
		}
	}
}

LONG CDrawAttrSpy::MouseMove(UINT nFlags, CPoint &point)
{
	return 0;
}

LONG CDrawAttrSpy::LButtonDown(UINT nFlags, CPoint &point)
{
	if (MrDraw::PointInRect(point, m_rcAxis))//m_rcAxis.PtInRect(point))
	{
		return DRAW_HAS_OBJECT_SELECTED;
	}
	else
	{
		return DRAW_NONE_OBJECT_SELECTED;
	}
}

LONG CDrawAttrSpy::LButtonUp(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawAttrSpy::RButtonDown(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawAttrSpy::RButtonUp(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

BOOL CDrawAttrSpy::PointInRgn(CPoint &pt) 
{
	return TRUE;
}

void CDrawAttrSpy::Draw(CDC *pDC, ULONG nDrawStyle) 
{
	m_oRulerAxis.DrawIt(pDC);
	
	//////////////////////////////
	double dCoef = m_dCoefValue ;// 需要一个从m_oRulerAxis获得的系数
	
	CFont font;
	font.CreateFontIndirect(&MrDraw::g_lfDrawVariableName);
	CFont *pOldFont = pDC->SelectObject(&font);
	COLORREF crOld = pDC->SetTextColor(m_crColor);
	UINT nMode = pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(m_strName, m_rcName, DT_VCENTER | DT_LEFT);	
	pDC->SelectObject(pOldFont);
	pDC->SetTextColor(crOld);
	pDC->SetBkMode(nMode);

	if (m_pptAttachBuffer == NULL)
	{
		return;
	}
	
	long nWaveLength = m_pptAttachBuffer->GetCurrUseLength() + 1;
	CPen MyPen(PS_SOLID,1,m_crColor);
	CPen* pOldPen = pDC->SelectObject(&MyPen);
	pDC->Polyline(m_pptAttachBuffer->GetBuffer(), nWaveLength);
	pDC->SelectObject(pOldPen);
	MyPen.DeleteObject();
	pOldPen = NULL;
}

void CDrawAttrSpy::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
{
	if (m_pfAttachBuffer == NULL || m_pptAttachBuffer ==NULL)
	{
		return;
	}
	
	long nBuf1BeginPos = oBufPos.nBuf1BeginPos;
	long nBuf1EndPos   = oBufPos.nBuf1EndPos;
	long nBuf2BeginPos = oBufPos.nBuf2BeginPos;
	long nBuf2EndPos   = oBufPos.nBuf2EndPos;
	long nGap = oBufPos.nGap;
	double dDrawCoef;
	int nOffSet;
	m_oRulerAxis.GetAxisInterface(dDrawCoef, nOffSet);

	m_pptAttachBuffer->CalValueY(-dDrawCoef,nOffSet,m_pfAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
		nBuf2BeginPos,nBuf2EndPos,nGap);
}

void CDrawAttrSpy::Move(long nHor, long nVer) 
{ 
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

void CDrawAttrSpy::Zoom(double dRate) 
{
}

void CDrawAttrSpy::GetVaraibleInterface(double& dCoef,long& nOffSetY)
{
	double dAxisCoef ;
	int nCenter;
	m_oRulerAxis.GetAxisInterface(dAxisCoef,nCenter);
	dCoef = dAxisCoef * m_dCoefValue;
	nOffSetY = nCenter;
}

void CDrawAttrSpy::SetRange(double dRange,BOOL bModified) 
{
	double dMax = dRange;
	double dMin = 0;

	if (bModified)
	{
		dMin = 0 - dRange; 
	}
	
	m_bNeedModifyCenter = bModified;
	m_oRulerAxis.SetMinMaxVal(dMin , dMax , 0 );
}

void CDrawAttrSpy::SetRange(double dMin,double dMax)
{
	m_dRangeMin = dMin;
	m_dRangeMax = dMax;
	m_oRulerAxis.SetMinMaxVal(dMin , dMax , 0 );
}
