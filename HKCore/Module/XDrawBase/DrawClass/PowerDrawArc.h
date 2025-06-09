// PowerDrawArc.h: interface for the CPowerDrawArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWARC_H__781122E0_2C5C_11D5_B0A0_0050BA40BBF3__INCLUDED_)
#define AFX_POWERDRAWARC_H__781122E0_2C5C_11D5_B0A0_0050BA40BBF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PowerDrawBaseClass.h"

class CPowerDrawArc : public CPowerDrawBaseClass  
{
public:
	DECLARE_DYNCREATE(CPowerDrawArc)

public:
	CPoint pt1,pt2,pt3;       ///pt2  圆弧的中间点

	CPowerPointValue	m_ppv1,m_ppv2,m_ppv3;

	CPowerPointValue m_ppvBegin,m_ppvEnd;

	double	fCenterX,fCenterY;
	double	fRadius;

	double	fBeginAngle,fEndAngle;

	int  m_iRadiusX,m_iRadiusY;
	CPoint m_ptCenter;
	CPoint m_ptBegin,m_ptEnd;

	////////圆弧的拾取
	CRect	GetBox();
	BOOL	PickArc(CPoint point);
	double	GetPickPointAngle(CPoint pt);
	void	SetPicked(BOOL bPicked=FALSE);
public:
	BOOL	SetArcPoints(CPoint p1,CPoint p2,CPoint p3);
	BOOL	SetArcValues(CPowerPointValue	ppv1,CPowerPointValue	ppv2,CPowerPointValue	ppv3);
	void	Draw(CDC *pDC,int m_DrawMode,int m_DrawMode1,unsigned long ululBKColor);
public:
	CPowerDrawArc();
	CPowerDrawArc(CString strClass);
	virtual ~CPowerDrawArc();

	virtual BOOL InitOwnDataByString(CString strOwnData);
	virtual BOOL ContinueInitIt(CAxisReference *axisReference);
	virtual CPowerDrawBaseClass* DirectGetNewObject();
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString GetExportTextString(void);
	virtual CString  GetDisplayDataString(void);
	virtual BOOL PickIt(CPoint point);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);
	int GetQuadrant(double fx,double fy);

	double GetTheAngle(double f1,double f2,double fr);
	double GetIntPVAngle(double fx,double fy);
	/////////////求取直线与图形的交点
	//入口参数：直线方程
	//返回参数：直线与图形的交点指针、交点的个数
	virtual void GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	BOOL IsPointTheJustPoint(CLineFunction*pLF,double fx,double fy);
	BOOL IsIntersectPTOnArc(double fx,double fy);
	virtual void OnColorChanged(COLORREF color);	//绘制图元的颜色改变

	//定义误差计算函数
	CPowerDrawArc*GetErrorArc(double fErrorVal);		//获得偏移后的误差曲线
	CString GetErrorArcString(CPointValueObject*ppvo1,CPointValueObject*ppvo2,BOOL bIner=FALSE);
	virtual void GetIntersectPV2(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,BOOL bIner=FALSE,int iEndOrBegin=0);
};

#endif // !defined(AFX_POWERDRAWARC_H__781122E0_2C5C_11D5_B0A0_0050BA40BBF3__INCLUDED_)
