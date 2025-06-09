// PowerDrawCircle.h: interface for the CPowerDrawCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWCIRCLE_H__77921201_29A2_11D5_B09F_0050BA40BBF3__INCLUDED_)
#define AFX_POWERDRAWCIRCLE_H__77921201_29A2_11D5_B09F_0050BA40BBF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PowerDrawBaseClass.h"
#include "PowerDrawArc.h"

//#include "PowerDrawLine.h"

class CPowerDrawCircleValue
{
public:
	double	dOffset;
	double	dAngle;
	double	dDiameter;
	//CPowerPointValue	m_ppvCenter;
	double dA,dB;

public:
	BOOL IsThisATrueCircle();
	CPowerDrawCircleValue();
	~CPowerDrawCircleValue();
};

class CPowerDrawCircle : public CPowerDrawBaseClass  
{
public:
	DECLARE_DYNCREATE(CPowerDrawCircle)

public:
	CPoint	m_ptCenter;	///实际的圆心坐标
	int     m_iRadiusX,m_iRadiusY;
	double	m_dRadius;

	CPowerDrawArc pArcL,pArcR;
	CPowerDrawCircleValue m_pdcv;

	void	Draw(CDC *pDC);
	void	Draw(CDC *pDC,CRect rectBox);
public:	/////圆的选取
	BOOL	PickCircle(CPoint curPoint);
	CRect	GetMinRectBOX();
	void	SetPicked(BOOL bPicked=FALSE);

	////选中的标志

public:
//	void	OnLButtonDown(CDC *pDC,UINT nFlags, CPoint point);

public:
	BOOL InitCircleByOnePoint(double fx,double fy);
	CPowerDrawCircle();
	CPowerDrawCircle(CString strClass);
	virtual ~CPowerDrawCircle();

	void EndIt();
	void InitIt();
	virtual BOOL InitOwnDataByString(CString strOwnData);
	virtual BOOL ContinueInitIt(CAxisReference *axisReference);
	virtual CPowerDrawBaseClass* DirectGetNewObject();
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString GetExportTextString(void);
	virtual CString  GetDisplayDataString(void);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

	virtual BOOL PickIt(CPoint point);

	/////////////求取直线与图形的交点
	//入口参数：直线方程
	//返回参数：直线与图形的交点指针、交点的个数
	double GetPVAngle(double fx,double fy);	//获得圆上一点的角度
	virtual void GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	void GetCircleIntersetPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	void GetArcIntersetPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	BOOL IsPointTheJustPoint(CLineFunction*pLF,double fx,double fy);
	virtual void OnColorChanged(COLORREF color);	//绘制图元的颜色改变

	//定义误差线的求取函数
	CString	GetErrorString(double fOffVal);
};

#endif // !defined(AFX_POWERDRAWCIRCLE_H__77921201_29A2_11D5_B09F_0050BA40BBF3__INCLUDED_)
