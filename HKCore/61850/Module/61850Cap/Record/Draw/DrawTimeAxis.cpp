// DrawTimeAxis.cpp: implementation of the CDrawTimeAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawTimeAxis.h"
#include "..\..\..\..\..\Module\API\GloblaDrawFunctions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawTimeAxis::CDrawTimeAxis()
{
	//坐标系当前使用的时间刻度
	m_dTimeMin = 0;
	m_dTimeMax = 100;
	
	//坐标系初始时间刻度
	m_dOldTimeMin = 0;
	m_dOldTimeMax = 100;

	m_oTimeAxis.SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);
	m_oTimeAxis.SetBorder(40, 400 , 400, 460);	
	m_oTimeAxis.SetRulerBoderShow(0);
	m_oTimeAxis.SetMinMaxVal(m_dTimeMin, m_dTimeMax, 0);
	m_oTimeAxis.SetRulerHalfScaleShow(1);
	m_oTimeAxis.SetRulerTenthScaleShow(1);
	m_oTimeAxis.SetFrameLeftTopColor(RGB(0,0,0));
	m_oTimeAxis.SetFrameRightBottomColor(RGB(0,0,0));
	m_oTimeAxis.SetDrawBack(0);

	m_oRangeAxis.AttachTimeAxis(this);
	m_bUseRangeAxis = TRUE;
	m_pDrawStruct = NULL;
}

CDrawTimeAxis::~CDrawTimeAxis()
{	
	m_pDrawStruct = NULL;
}

void CDrawTimeAxis::SetParentWnd(CWnd* pParentWnd)
{
	CDrawBase::SetParentWnd(pParentWnd);
	m_oRangeAxis.SetParentWnd(pParentWnd);
}

void CDrawTimeAxis::SetBorder(const CRect &rect, BOOL bUseClipRect)
{
	CDrawBase::SetBorder(rect);

	if ( (m_rcBorder.right - m_rcBorder.left) % 2 != 0)
	{
		m_rcBorder.right += 1;
	}

	m_oTimeAxis.SetBorder(m_rcBorder);

	if (m_bUseRangeAxis)
	{
		CRect rcRular = m_oTimeAxis.GetBorder();
		CRect rcRangeAxisBorder = m_rcBorder;
		rcRangeAxisBorder.top = rcRular.bottom - 4;
		rcRangeAxisBorder.bottom = rcRangeAxisBorder.top + TIMEAXIS_RANGESTATEAXIS_HEIGHT;
		m_oRangeAxis.SetBorder(rcRangeAxisBorder, bUseClipRect);
	}
}

void CDrawTimeAxis::ExpandBorder(long l, long t, long r, long b)
{	
}

void CDrawTimeAxis::Move(long nHor, long nVer )
{
}
//这 个函数需要一个变量，改变的中心位置
void CDrawTimeAxis::Zoom(double dRate) 
{
}

void CDrawTimeAxis::Draw(CDC *pDC, ULONG nDrawStyle) 
{
	m_oTimeAxis.DrawIt(pDC);
}

void CDrawTimeAxis::DrawSubject(CDC *pDC) 
{	
	if (m_bUseRangeAxis)
	{
		m_oRangeAxis.Draw(pDC);
	}
}

LONG CDrawTimeAxis::MouseMove(UINT nFlags, CPoint &point)
{
	if (m_bUseRangeAxis)
	{
		return m_oRangeAxis.MouseMove(nFlags, point);
	}
	else
	{
		return DRAW_NONE_OBJECT_SELECTED;
	}
}

LONG CDrawTimeAxis::LButtonDown(UINT nFlags, CPoint &point)
{
	if (m_bUseRangeAxis)
	{
		return m_oRangeAxis.LButtonDown(nFlags, point);
	}
	else
	{
		return DRAW_NONE_OBJECT_SELECTED;
	}
}

LONG CDrawTimeAxis::LButtonUp(UINT nFlags, CPoint &point)
{
	if (m_bUseRangeAxis)
	{
		return m_oRangeAxis.LButtonUp(nFlags, point);
	}
	else
	{
		return DRAW_NONE_OBJECT_SELECTED;
	}
}

LONG CDrawTimeAxis::RButtonDown(UINT nFlags, CPoint &point)
{
	return 0;
}

LONG CDrawTimeAxis::RButtonUp(UINT nFlags, CPoint &point)
{
	return 0;
}

BOOL CDrawTimeAxis::PointInRgn(CPoint &pt)
{
	return TRUE;
}

CDrawRangeStateAxis* CDrawTimeAxis::GetDrawRangeStateAxis()
{
	if (m_bUseRangeAxis)
	{
		return &(m_oRangeAxis.m_oRangeState);
	}
	else
	{
		return NULL;
	}
}

void CDrawTimeAxis::SetAxisRange(double dCoefLeft, double dCoefRight)
{
	double dLen = m_dOldTimeMax - m_dOldTimeMin;
	m_dTimeMin = m_dOldTimeMin + dCoefLeft * dLen;
	m_dTimeMax = m_dOldTimeMin + dCoefRight * dLen;
	m_oTimeAxis.SetMinMaxVal(m_dTimeMin, m_dTimeMax, 0);	

	if (m_pParentWnd != NULL)
	{
		if (::IsWindow(m_pParentWnd->m_hWnd))
		{			
			m_pParentWnd->PostMessage(WM_TIMEAXIS_CHANGED, 0, 0);
		}
	}	
}

void CDrawTimeAxis::SetMaxMinTime(double dMax,double dMin)
{
	m_dTimeMin = dMin;
	m_dTimeMax = dMax;

	m_oTimeAxis.SetMinMaxVal(m_dTimeMin, m_dTimeMax, 0);
	
	double dTimeLen = m_dOldTimeMax - m_dOldTimeMin;
	double dCoefLeft = (dMin - m_dOldTimeMin) / dTimeLen;
	double dCoefRight =(dMax - m_dOldTimeMin) / dTimeLen;
	m_oRangeAxis.m_oRangeState.AdjustRangeStateAxisByCoef(dCoefLeft,dCoefRight);

	if (m_pDrawStruct != NULL)//之所以只适用一个参数，是因为示波时时间最小值是0
	{
		m_pDrawStruct->dLastTimeLen = dMax - dMin;
	}
}

void CDrawTimeAxis::GetMaxMinTime(double &dMax,double& dMin)
{ 
	dMax = m_dTimeMax; 
	dMin = m_dTimeMin;	
}

void CDrawTimeAxis::SetOldMaxMinTime(double dMax,double dMin)
{
	m_dOldTimeMin = dMin;
	m_dOldTimeMax = dMax;
	m_oTimeAxis.SetOldRulerMaxMinValue(dMin, dMax);	
}

void CDrawTimeAxis::GetOldMaxMinTime(double &dMax,double& dMin)
{ 
	dMin = m_dOldTimeMin;
	dMax = m_dOldTimeMax;
}

void CDrawTimeAxis::LogicPointToDevicePoint(double dValue , long* pnXPosition)
{
	m_oTimeAxis.LogicPointToDevicePoint(dValue , pnXPosition);
}

void CDrawTimeAxis::DevicePointToLogicPoint(long nXPosition , double* pdValue)
{
	m_oTimeAxis.DevicePointToLogicPoint(nXPosition , pdValue);
}
