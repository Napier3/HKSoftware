// DrawAttrSpy.h: interface for the CDrawAttrSpy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DrawAttrSpy_h__)
#define _DrawAttrSpy_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawVariable.h"
#include "../../Axis/RulerAxis.h"

class CDrawAttrSpy : public CDrawVariable  
{
public:
	CDrawAttrSpy(CRulerAxis *pAxis);
	CDrawAttrSpy();
	virtual ~CDrawAttrSpy();

public:
	double m_dCoefValue;
	long m_nAttrDataIndex;//表示在Info大文件存储过程中的位置，即在FileWrite中MR1200定义属性缓存的的顺序位置
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
	virtual UINT GetClassID()	{	return CMTRDCLASSID_ATTRSPYVARIABLE ;		}
	virtual void GetVaraibleInterface(double& dCoef,long& nOffSetY);
	virtual void InitAxis(long nAxisRight);
	void SetRange(double dMin,double dMax);
	void SetRange(double dRange,BOOL bModified = TRUE) ;
	double GetRange()			{	return m_dRange;	}

private:
	double m_dRange;
	BOOL m_bNeedModifyCenter;//TRUE时是+-Range
	double m_dRangeMax;
	double m_dRangeMin;
	UINT  m_nRangeMask;
};

#endif // !defined(_DrawAttrSpy_h__)





















