// DrawAnalogVariable.h: interface for the CDrawAnalogVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAWANALOGVARIABLE_H__)
#define _DRAWANALOGVARIABLE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawVariable.h"

class CDrawAnalogVariable : public CDrawVariable  
{
public:
	double* m_dCoefValue;//short到实际值
	double* m_dZeroValue;//实际零值 **V/A
	CString m_strUnit;
	CString m_strPhaseID;

public:
	virtual void SetBorder(const CRect &rect, BOOL bSavePos);
	virtual void SetBorder(const CRect &rect);
	virtual void ExpandBorder(long &l, long &t, long &r, long &b);
	virtual void SetParentWnd(CWnd* pParentWnd)	 ;
// 	virtual LONG MouseMove(UINT nFlags, CPoint &point);
// 	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
// 	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
// 	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
// 	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Draw(CDC *pDC, ULONG nDrawStyle=0XFFFFFFFF);
	virtual void LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) ;
	virtual void Move(long nHor = 0, long nVer = 0) ;
	virtual void Zoom(double dRate) ;
	virtual BOOL CanZoomY()		{	return TRUE;	}
	virtual BOOL CanZoomX()		{	return TRUE;	}
	virtual UINT GetClassID()	{	return DRAWCLASSID_ANALOGVARIABLE ;		}
	virtual void GetVaraibleInterface(double& dCoef,long& nOffSetY);
	virtual void InitAxis(long nAxisRight);
	virtual void SetClipRect(const CRect &rcClip);
	virtual void SetAttachStruct(PDRAWVAR pDrawStruct);
	void SetRange(double dRange) ;
	double GetRange()			{	return m_dRange;	}
	void SetUnit(const CString& strUnit);
	void SetAdjustValue(double *dZero,double *dCoef);
	void GetTimeCursorPos(long nCursorPos);
	void SetParaRect(CRect rcPara);

	//参数
	void AddPara(UINT nID);
	void DeletePara(UINT nID);
	void DeleteAllPara();

public:
	CDrawAnalogVariable();
	virtual ~CDrawAnalogVariable();

private:
	double m_dRange;
};

#endif // !defined(_DRAWANALOGVARIABLE_H__)
