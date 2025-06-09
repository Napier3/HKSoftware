// DrawAnalogComplexVariable.cpp: implementation of the CDrawAnalogComplexVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawAnalogComplexVariable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawAnalogComplexVariable::CDrawAnalogComplexVariable()
{
	m_dCoefValue = 1;;
	m_strUnit = "";
	m_dRange = 0;
}

CDrawAnalogComplexVariable::~CDrawAnalogComplexVariable()
{
}

void CDrawAnalogComplexVariable::SetBorder(const CRect &rect)
{
	CDrawBase::SetBorder(rect);

	InitAxis(MrDraw::g_snNameandAxisRectWidth);
}

void CDrawAnalogComplexVariable::InitAxis(long nAxisRight)
{
	SetNameRect(GetBorder());//m_rcBorder); 
	SetNameRectRight(m_rcName.left + MrDraw::g_nVariableNameLength);
	
	m_rcAxis = GetBorder();//m_rcBorder;
	m_rcAxis.left = m_rcName.right;
	m_pRulerAxis->SetRulerTypeVert();
	m_pRulerAxis->SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);
	m_pRulerAxis->SetBorder(m_rcAxis);
	m_pRulerAxis->SetMinSawGapWidth(15);
	m_pRulerAxis->SetRulerHalfScaleShow(1);
	m_pRulerAxis->SetRulerTenthScaleShow(0);
	m_pRulerAxis->SetRulerBoderShow(0);
	m_pRulerAxis->SetFrameRightBottomColor(RGB(0,0,0));
	m_pRulerAxis->SetDrawBack(0);
	m_rcAxis = m_pRulerAxis->GetBorder();
	
	m_rcDraw = GetBorder();//m_rcBorder;
	m_rcDraw.left = m_rcAxis.right;
	double dCoef ;
	m_pRulerAxis->GetAxisInterface(dCoef,m_nYCenter);
	
	long nWidth = m_rcAxis.Width();
	m_rcAxis.right = nAxisRight;
	m_rcAxis.left  = nAxisRight - nWidth;
	m_pRulerAxis->SetBorder(m_rcAxis);
	SetNameRectRight(m_rcAxis.left);
	m_rcNameRectOrigin  = m_rcName;	
}

void CDrawAnalogComplexVariable::ExpandBorder(long &l, long &t, long &r, long &b)
{
	l = 0;
	r = 0;
	CDrawBase::ExpandBorder(l, t, r, b);
	InitAxis(MrDraw::g_snNameandAxisRectWidth);

	PostDrawObjectPosChangedMsg();
}

LONG CDrawAnalogComplexVariable::MouseMove(UINT nFlags, CPoint &point)
{
	return 0;
}

LONG CDrawAnalogComplexVariable::LButtonDown(UINT nFlags, CPoint &point)
{
	if (MrDraw::PointInRect(point, m_rcAxis))
	{
		return DRAW_HAS_OBJECT_SELECTED;
	}
	else
	{
		return DRAW_NONE_OBJECT_SELECTED;
	}
}

LONG CDrawAnalogComplexVariable::LButtonUp(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawAnalogComplexVariable::RButtonDown(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawAnalogComplexVariable::RButtonUp(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

BOOL CDrawAnalogComplexVariable::PointInRgn(CPoint &pt) 
{
	return TRUE;
}

void CDrawAnalogComplexVariable::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag) 
{
	CDrawVariable::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);

//	if ((VARIABLE_DRAW_STYLE_AXIS & dwDrawFlag) == VARIABLE_DRAW_STYLE_AXIS)
	{
		if (m_nSelectedState == DRAW_HAS_OBJECT_SELECTED || m_bSelect)
		{
			m_pRulerAxis->DrawIt(pDC);
		}
	}

	double dCoef = m_dCoefValue ;// 需要一个从m_oRulerAxis获得的系数
	
	if (m_pptAttachDrawBuffer == NULL)
	{
		return;
	}
	
	long nWaveLength = m_pptAttachDrawBuffer->GetCurrUseLength();

	pDC->Polyline(m_pptAttachDrawBuffer->GetBuffer(), nWaveLength);

}

void CDrawAnalogComplexVariable::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
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
	dDrawCoef *= m_dCoefValue;
	m_pptAttachDrawBuffer->CalValueY(-dDrawCoef,nOffSet,m_pfAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
	nBuf2BeginPos,nBuf2EndPos,nGap);
}

void CDrawAnalogComplexVariable::Move(long nHor, long nVer) 
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

void CDrawAnalogComplexVariable::Zoom(double dRate) 
{
}

void CDrawAnalogComplexVariable::GetVaraibleInterface(double& dCoef,long& nOffSetY)
{
	double dAxisCoef ;
	int nCenter;
	m_pRulerAxis->GetAxisInterface(dAxisCoef,nCenter);
	dCoef = dAxisCoef * m_dCoefValue;
	nOffSetY = nCenter;
}

void CDrawAnalogComplexVariable::SetRange(double dRange) 
{
	double dMax = dRange;
	double dMin = -dRange;
	m_pRulerAxis->SetMinMaxVal(dMin , dMax , 0 );
}

void CDrawAnalogComplexVariable::SetUnit(const CString& strUnit)
{
	m_strUnit = strUnit;
	
#ifdef _SHOW_PARA
	m_oParas.SetUnit(strUnit);	
#endif	
}
