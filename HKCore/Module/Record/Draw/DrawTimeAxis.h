// DrawTimeAxis.h: interface for the CDrawTimeAxis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAW_TIME_AXIS_H__)
#define _DRAW_TIME_AXIS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBase.h"
#include "../../AXIS/RulerAxis.h"	// Added by ClassView
#include "DrawTimeAxisRange.h"
#include "../RecordGlobalDefine.h"

extern long TIMEAXIS_RANGESTATEAXIS_HEIGHT;  

class CDrawTimeAxis : public CDrawBase  
{
public:
	CRulerAxis m_oTimeAxis;

	//坐标系当前使用的时间刻度
	double m_dTimeMin;
	double m_dTimeMax;

	//坐标系初始时间刻度
	double m_dOldTimeMin;
	double m_dOldTimeMax;

	BOOL m_bUseRangeAxis;
	CDrawTimeAxisRange m_oRangeAxis;

public:
	virtual void SetBorder(const CRect &rect, BOOL bUseClipRect=TRUE);
	virtual void ExpandBorder(long l, long t, long r, long b);
	virtual void SetParentWnd(CWnd* pParentWnd);
	
	//继承的方法
	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void DrawSubject(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF) ;
	virtual BOOL CanZoomY() {	return FALSE;	}
	virtual BOOL CanZoomX() {	return TRUE;	}
	virtual void Move(long nHor = 0, long nVer = 0) ;
	virtual void Zoom(double dRate);
	
	void SetUseRangeAxis(BOOL bUseRangeAxis)    {    m_bUseRangeAxis = bUseRangeAxis;    };
	BOOL GetUseRangeAxis()                      {    return m_bUseRangeAxis;             }
	CDrawRangeStateAxis* GetDrawRangeStateAxis();
	void SetAxisRange(double dCoefLeft, double dCoefRight);
	void SetMaxMinTime(double dMax,double dMin);
	void GetMaxMinTime(double &dMax,double& dMin); 
	void SetOldMaxMinTime(double dMax,double dMin);
	void GetOldMaxMinTime(double &dMax,double& dMin); 
	void LogicPointToDevicePoint(double dValue , long* pnXPosition);
	void DevicePointToLogicPoint(long nXPosition , double* pdValue);
	void AttachDrawStruct(PMR1200SYSANALYSEMNGR pDrawVars)	{	m_pDrawStruct = pDrawVars;	}

	void TimeGetAxisRange(double &dCoefLeft, double &dCoefRight);
	void TimeSetAxisRange(double dCoefLeft, double dCoefRight);
	void SetAxisCurrTime(double dMax,double dMin);

public:	
	CDrawTimeAxis();
	virtual ~CDrawTimeAxis();

private:
	//关联绘图结构体
	PMR1200SYSANALYSEMNGR m_pDrawStruct;
};

#endif // !defined(_DRAW_TIME_AXIS_H__)
