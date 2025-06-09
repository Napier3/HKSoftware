// PowerDrawBaseClass.h: interface for the CPowerDrawBaseClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWBASECLASS_H__95DE7D16_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_)
#define AFX_POWERDRAWBASECLASS_H__95DE7D16_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define POWERADVANCE_PICK_RADIUS	2
#include "math.h"
#include "PDBaseObject.h"
#include "PDApi.h"

#define POWERADVANCE_UNIT_DRAW_MODE_NORMAL	0X001
#define POWERADVANCE_UNIT_DRAW_MODE_PICKED	0X002


class CPowerPointValue 
{
public:
	double dX,dY;
	CPowerPointValue();
	~CPowerPointValue();
};
class CPointValueObject : public CObject
{
public:
	double dX,dY;
	int	iIndex;
	CPointValueObject();
	~CPointValueObject();
};
class CAxisReference
{
public:
	CPoint	m_ptCenterLogInDv;	////逻辑坐标的原点在设备坐标上的坐标值
	double	m_fOneYGapValue;		///////Y轴实际坐标与实际值的比率
	double	m_fOneXGapValue;		///////X轴实际坐标与实际值的比率
	CAxisReference();
	~CAxisReference();
};

////////////////////定义直线函数方程数据类
/*
	直线的种类	
		iType=0			正常直线	y=k*x+b
		iType=1			k->∞		x=b
*/
class CLineFunction : public CPDBaseObject
{
public:
	int		iType;		//直线的种类
	double	fCoefK;		//直线的斜率 k
	double	fSlantAngle;//直线的倾斜角
	double	fConstB;	//直线的常数 b
	double	fbx,fby;	//直线的起始点
	double	fex,fey;	//直线的终止点
	void   InitIt();
	CLineFunction();
	~CLineFunction();
	void	SetCoefKByAngle(double fAngle,double fx,double fy);
};
class CPowerDrawBaseClass : public CPDBaseObject  
{
public:
	DECLARE_DYNCREATE(CPowerDrawBaseClass)

	CString strClassName;

//	CAxisReference axisReference;
public:
	unsigned long	m_ulColor;
	UINT		m_uiLineStyle;
	int			m_iLineWidth;

	unsigned long	m_ulPickColor;
	UINT		m_uiPickLineStyle;
	int			m_iPickLineWidth;
	void Init();

	int		m_iDrawModal;        ////0,normal  ; 1=>picked  ...
	////选中的标志
	int		m_iOldDrawModal;

public:
	CPowerDrawBaseClass();
	CPowerDrawBaseClass(CString strClass);
	CPowerDrawBaseClass(unsigned long color,UINT lineStyle,int iWidth);
	virtual ~CPowerDrawBaseClass();

	void    LogicPointToDevicePoint(CPoint *ptDevice,double fx,double fy,CAxisReference *axisReference);
	virtual BOOL InitOwnDataByString(CString strOwnData);
	virtual BOOL ContinueInitIt(CAxisReference *axisReference);
	virtual CPowerDrawBaseClass* DirectGetNewObject();
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString GetExportTextString(void);
	virtual CString  GetDisplayDataString(void);

	virtual BOOL PickIt(CPoint point);
	virtual void  BeforePrinting(double fMMValue);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

	/////////////求取直线与图形的交点
	//入口参数：直线方程	//返回参数：直线与图形的交点指针、交点的个数
	virtual void GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);

	virtual void OnColorChanged(COLORREF color);	//绘制图元的颜色改变
};

#endif // !defined(AFX_POWERDRAWBASECLASS_H__95DE7D16_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_)
