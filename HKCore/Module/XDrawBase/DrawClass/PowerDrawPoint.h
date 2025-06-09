// PowerDrawPoint.h: interface for the CPowerDrawPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWPOINT_H__E6522000_7546_11D5_A3F9_00E04CE17719__INCLUDED_)
#define AFX_POWERDRAWPOINT_H__E6522000_7546_11D5_A3F9_00E04CE17719__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PowerDrawBaseClass.h"

class CPowerDrawPoint : public CPowerDrawBaseClass  
{
public:
	CPowerPointValue m_ppv;
	CPoint m_pointValue;
	int   m_iDrawType;

	int iMMM;
	int m_iPixel;
public:
	CPowerDrawPoint();
	virtual ~CPowerDrawPoint();

	CPowerDrawPoint(CString strClass);
	virtual BOOL InitOwnDataByString(CString strOwnData);
	virtual BOOL ContinueInitIt(CAxisReference *axisReference);
	virtual CPowerDrawBaseClass* DirectGetNewObject();
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString  GetDisplayDataString(void);
	virtual CString GetExportTextString(void);

	virtual void  BeforePrinting(double fMMValue);
	virtual BOOL PickIt(CPoint point);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);
	virtual void OnColorChanged(COLORREF color);	//绘制图元的颜色改变
};

#endif // !defined(AFX_POWERDRAWPOINT_H__E6522000_7546_11D5_A3F9_00E04CE17719__INCLUDED_)
