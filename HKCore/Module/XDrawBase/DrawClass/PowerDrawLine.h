// PowerDrawLine.h: interface for the CPowerDrawLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWLINE_H__95DE7D17_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_)
#define AFX_POWERDRAWLINE_H__95DE7D17_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PowerDrawBaseClass.h"



class CPowerDrawLine : public CPowerDrawBaseClass  
{
public:
	DECLARE_DYNCREATE(CPowerDrawLine)
public:
	/////////作图中对应的点坐标
	CPoint	m_pointBegin;
	CPoint	m_pointEnd;
	/////////作图中对应的点坐标代表的数值
	CPowerPointValue	m_pvBegin;
	CPowerPointValue	m_pvEnd;
public:
	BOOL PickLine(CPoint curPoint);
	double GetLineAngle();
	CRect	GetMinRectBOX();
public:
	void Draw(CDC *pDC);

public:
	void Init();
	void InitPowerLine(CPoint pointBegin,CPoint pointEnd);
	CPowerDrawLine(CPoint pointBegin,CPoint pointEnd);
	CPowerDrawLine();
	void	SetPicked(BOOL bPicked=FALSE);
	virtual ~CPowerDrawLine();
	CPowerDrawLine(CString strClass);

	virtual BOOL InitOwnDataByString(CString strOwnData);
	virtual BOOL ContinueInitIt(CAxisReference *axisReference);
	virtual CPowerDrawBaseClass* DirectGetNewObject();
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString GetExportTextString(void);
	virtual CString  GetDisplayDataString(void);
	virtual BOOL PickIt(CPoint point);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);
	/////////////求取直线与图形的交点
	//入口参数：直线方程
	//返回参数：直线与图形的交点指针、交点的个数
	BOOL IsPointTheJustPoint(CLineFunction*pLF,double fx,double fy);
	virtual void GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	virtual void GetIntersectPV2(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect);
	virtual void OnColorChanged(COLORREF color);	//绘制图元的颜色改变

	//////////////定义误差线函数
	double GetLineAngleVal();	//获得直线的倾角		2001年11月11日
	double GetLineLength();		//获得直线的长度		2001年11月11日
	CString GetErrorLineString(CPointValueObject*ppvo1,CPointValueObject*ppvo2);
	CPowerDrawLine*GetErrorLine(double fErrorVal);	//获得此直线的偏移直线
	CLineFunction*GetLineFunction();				//获得此直线的方程
};

#endif // !defined(AFX_POWERDRAWLINE_H__95DE7D17_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_)
