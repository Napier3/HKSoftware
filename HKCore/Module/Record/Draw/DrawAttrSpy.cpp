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

CDrawAttrSpy::CDrawAttrSpy(CRulerAxis *pAxis)
	 : CDrawVariable(pAxis)
{
	m_bNeedModifyCenter = FALSE ;
	m_nRangeMask		= 0;
	m_dRangeMin			= 0;
	m_dRangeMax			= 0;
	m_dRange			= 0;	
	m_dCoefValue		= 1;
	m_nAttrDataIndex	= 0;
	m_strUnit			= "";
	m_nLineStyle = PS_SOLID;
}

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
	m_nLineStyle = PS_SOLID;
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
	m_pRulerAxis->SetRulerTypeVert();
	m_pRulerAxis->SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);
	m_pRulerAxis->SetBorder(m_rcAxis);
	m_pRulerAxis->SetMinSawGapWidth(15);
	m_pRulerAxis->SetRulerHalfScaleShow(1);
	m_pRulerAxis->SetRulerTenthScaleShow(0);
	m_pRulerAxis->SetRulerBoderShow(0);
	m_pRulerAxis->SetFrameRightBottomColor(RGB(0,0,0));
	m_pRulerAxis->SetDrawBack(0);

	m_rcAxis = GetBorder();//m_rcBorder;
	m_rcAxis.right = nAxisRight;	
	long nWidth = m_pRulerAxis->GetRulerHeight();//得到标尺的宽度
	m_rcAxis.left = nAxisRight - nWidth;
	m_pRulerAxis->SetBorder(m_rcAxis);	
	m_rcDraw = GetBorder();//m_rcBorder;
	m_rcDraw.left = nAxisRight;
	double dCoef ;
	m_pRulerAxis->GetAxisInterface(dCoef,m_nYCenter);
	
	if (!m_bNeedModifyCenter)
	{
		m_nYCenter = (m_rcAxis.top + m_rcAxis.bottom) / 2;
	}

	nWidth = 0;
	SetNameRect(/*m_rcBorder.left*/m_ptTopLeft.x
		,m_nYCenter - m_nTextHeight / 2
		, nAxisRight - nWidth
		, m_nYCenter + m_nTextHeight / 2);

	m_rcNameRectOrigin  = m_rcName;
}

void CDrawAttrSpy::ExpandBorder(long &l, long &t, long &r, long &b)
{
	l = 0;
	r = 0;
	CDrawBase::ExpandBorder(l, t, r, b);
	InitAxis(MrDraw::g_snNameandAxisRectWidth);

	PostDrawObjectPosChangedMsg();
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

void CDrawAttrSpy::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag) 
{
//	if ((VARIABLE_DRAW_STYLE_AXIS & dwDrawFlag) == VARIABLE_DRAW_STYLE_AXIS)
	double dCoef = m_dCoefValue ;// 需要一个从m_oRulerAxis获得的系数

	if (!m_bRulerAxisRef)
	{
		if (m_nSelectedState == DRAW_HAS_OBJECT_SELECTED || m_bSelect)
		{
			m_pRulerAxis->DrawIt(pDC);
		}

		CFont font;
		font.CreateFontIndirect(&MrDraw::g_lfDrawVariableName);
		CFont *pOldFont = pDC->SelectObject(&font);
		COLORREF crOld = pDC->SetTextColor(m_crForeColor);
		UINT nMode = pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(m_strName, m_rcName, DT_VCENTER | DT_LEFT);	
		pDC->SelectObject(pOldFont);
		pDC->SetTextColor(crOld);
		pDC->SetBkMode(nMode);
	}

	if (m_pptAttachDrawBuffer == NULL)
	{
		return;
	}
	
	long nWaveLength = m_pptAttachDrawBuffer->GetCurrUseLength();
	CPen MyPen(m_nLineStyle, 1, m_crForeColor);
	CPen* pOldPen = pDC->SelectObject(&MyPen);
	pDC->Polyline(m_pptAttachDrawBuffer->GetBuffer(), nWaveLength);
	pDC->SelectObject(pOldPen);
	MyPen.DeleteObject();
	pOldPen = NULL;
}

void CDrawAttrSpy::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
{
	if (m_pfAttachBuffer == NULL || m_pptAttachDrawBuffer ==NULL)
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
	m_pRulerAxis->GetAxisInterface(dDrawCoef, nOffSet);

	m_pptAttachDrawBuffer->CalValueY(-dDrawCoef,nOffSet,m_pfAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
		nBuf2BeginPos,nBuf2EndPos,nGap);
}

void CDrawAttrSpy::Move(long nHor, long nVer) 
{ 
	nHor = 0;
	
	if (nVer != 0 || nHor != 0)
	{
		CRect rcBorder = GetBorder();//m_rcBorder;
		rcBorder.OffsetRect(nHor, nVer);
		SetBorder(rcBorder);
		
		PostDrawObjectPosChangedMsg();
	}
}

void CDrawAttrSpy::Zoom(double dRate) 
{
}

void CDrawAttrSpy::GetVaraibleInterface(double& dCoef,long& nOffSetY)
{
	double dAxisCoef ;
	int nCenter;
	m_pRulerAxis->GetAxisInterface(dAxisCoef,nCenter);
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
	m_pRulerAxis->SetMinMaxVal(dMin , dMax , 0 );
}

void CDrawAttrSpy::SetRange(double dMin,double dMax)
{
	m_dRangeMin = dMin;
	m_dRangeMax = dMax;
	m_pRulerAxis->SetMinMaxVal(dMin , dMax , 0 );
}
