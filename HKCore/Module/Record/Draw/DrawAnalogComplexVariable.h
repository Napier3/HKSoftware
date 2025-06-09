// DrawAnalogComplexVariable.h: interface for the CDrawAnalogComplexVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DrawAnalogComplexVariable_h__)
#define _DrawAnalogComplexVariable_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawVariable.h"
#include "../../Axis/RulerAxis.h"

class CDrawAnalogComplexVariable : public CDrawVariable  
{
public:
	double m_dCoefValue;
	CRulerAxis m_oRulerAxis;
	CString m_strUnit;
	
public:
	virtual void SetBorder(const CRect &rect);
	virtual void ExpandBorder(long &l, long &t, long &r, long &b);
	
	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) ;
	virtual void Move(long nHor = 0, long nVer = 0) ;
	virtual void Zoom(double dRate) ;
	virtual BOOL CanZoomY()		{	return TRUE;	}
	virtual BOOL CanZoomX()		{	return TRUE;	}
	virtual UINT GetClassID()	{	return  CMTRDCLASSID_COMPLEXVARIABLE;		}//CMTRDCLASSID_ATTRSPYVARIABLE
	virtual void GetVaraibleInterface(double& dCoef,long& nOffSetY);
	virtual void InitAxis(long nAxisRight);

	void SetRange(double dRange) ;
	double GetRange()			{	return m_dRange;	}
	void SetUnit(const CString& strUnit)   ;
	
public:
	CDrawAnalogComplexVariable();
	virtual ~CDrawAnalogComplexVariable();

private:
	double m_dRange;
};

#endif // !defined(_DrawAnalogComplexVariable_h__)
