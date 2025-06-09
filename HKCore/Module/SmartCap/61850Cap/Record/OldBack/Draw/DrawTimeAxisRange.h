// DrawTimeAxisRange.h: interface for the CDrawTimeAxisRange class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAW_TIMEAXIS_RANGE_H__)
#define _DRAW_TIMEAXIS_RANGE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBase.h"
#include "DrawRangeStateAxis.h"

class CDrawTimeAxis;

#define TIMEAXIS_RANGESTATEAXIS_HEIGHT (RANGESTATEAXIS_BLOCK_WIDTH+4)

class CDrawTimeAxisRange : public CDrawBase  
{
public:
	double m_dTimeMin;
	double m_dTimeMax;

	CDrawRangeStateAxis m_oRangeState;
	CDrawTimeAxis  *m_pAttachTimeAxis;
	CRect m_rcRangeAxis;
	double m_dTimeRangeMin;
	double m_dTimeRangeMax;
	BOOL   m_bDrawTimeRange;

public:
	virtual void SetBorder(const CRect &rect, BOOL bUseClipRect=TRUE);
	virtual void ExpandBorder(long &l, long &t, long &r, long &b);
	virtual void SetParentWnd(CWnd* pParentWnd);
	
	//¼Ì³ÐµÄ·½·¨
	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Draw(CDC *pDC, ULONG nDrawStyle=0XFFFFFFFF);
	virtual BOOL CanZoomY() {	return FALSE;	}
	virtual BOOL CanZoomX() {	return TRUE;	}
	virtual void Move(long nHor = 0, long nVer = 0) ;
	virtual void Zoom(double dRate);

	void SetDrawTimeRange(BOOL bDrawTimeRange)  {    m_bDrawTimeRange = bDrawTimeRange;  }  
	BOOL GetDrawTimeRange()                     {    return m_bDrawTimeRange;            }  
	void SetTimeRange(double dMin, double dMax) {    m_dTimeRangeMax = dMax; m_dTimeRangeMin = dMin;	}

public:	
	CDrawTimeAxisRange();
	virtual ~CDrawTimeAxisRange();

	void AttachTimeAxis(CDrawTimeAxis *pAxis);
	void SetMinLength(long nLen)
	{
		if (nLen <= 0)
		{
			nLen = RANGESTATEAXIS_BLOCK_HEIGHT1*2;
		}
		m_oRangeState.SetMinLength(nLen);
	}
	
private:
	long m_nRangeStateAxisLeft;
	long m_nRangeStateAxisRight;
};

#endif // !defined(_DRAW_TIMEAXIS_RANGE_H__)
