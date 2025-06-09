﻿#if !defined(AFX_POLARAXIS_H__03FB2069_42F0_4D56_9193_5FB03F8BB502__INCLUDED_)
#define AFX_POLARAXIS_H__03FB2069_42F0_4D56_9193_5FB03F8BB502__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PolarAxis.h : header file
//


#define		POLORAXIS_NAMEBUFFLEN	80
#define		POLORAXIS_AXISCOUNT		10

#define AXISTYPE_DESCARTES	0
#define AXISTYPE_POLOR		1
#define AXISTYPE_LOGARITHM	2

#define PI_180_RADIANTOANGLE	0.01745329	// 3.141592654/180
#define PI_180_ANGLETORADIAN	57.29577951	// 180/3.141592654

#include "AxisInterface.h"

/////////////////////////////////////////////////////////////////////////////
// CPolarAxis command target

class CPolarAxis : public CCmdTarget
{
	DECLARE_DYNCREATE(CPolarAxis)

	CPolarAxis();           // protected constructor used by dynamic creation

// Attributes
public:
	long	m_lAxisType;
	double	m_fOneYGapValue;
	double	m_fOneXGapValue;
	CPoint	m_ptCenterLogInDv;
	
	//定义极坐标的绘制区域信息
	long	m_lZoomCoefficient;
	CRect	m_rectBorder;			//整个极坐标的坐标区域
	CRect	m_rectWorkArea;			//极坐标的绘图区域
	int		m_iHorzMarginGapLeft;		//坐标的水平空白区域
	int		m_iHorzMarginGapRight;
	int		m_iVertMarginGapTop;		//坐标的垂直空白区域
	int		m_iVertMarginGapBottom;
	LOGFONT	lfAxisCenter;			//坐标中心轴标注字体
	LOGFONT	lfVectorName;			//矢量的名称绘制字体
	
	LOGFONT   m_lfPolarAxisTitleFont;	////坐标轴标题的字体
	COLORREF  m_crPolarAxisTitleFont;	////坐标轴标题的字体颜色
	CString	  m_strPolarAxisTitle;		////坐标轴标题
	
	double     m_dXAxisMinVal,m_dXAxisMaxVal;	//用于X轴====>>开始的位置，结束的位置
	double    m_dYAxisMinVal,m_dYAxisMaxVal;
	
	long    m_lAxisDrawStyle;	//显示类型
	CPoint	m_ptAxisCenter;			//坐标轴中心轴
	
	//定义颜色信息
	COLORREF	m_crAxisBackColor;	//坐标轴的底色
	COLORREF	m_crAxisWorkAreaBk;	//工作区底色
	COLORREF	m_crAxisCenter;		//坐标中心轴颜色
	COLORREF	m_crAxisFrame;		//坐标边框颜色
	COLORREF    m_crFrameLeftTopColor;
	COLORREF    m_crFrameRightBottomColor;
	int		 m_iFrameShadow;	//工作区边界阴影
	unsigned int	m_uiCenterLineType;
	int				m_iCenterLineWidth;
	
	//坐标控制变量  
	int		m_iAxisDrawType;		//坐标绘制种类	角度刻度、幅值刻度、中心轴
	
	//定义角度刻度相关的函数及控制变量,角度刻度线的线型、颜色、线宽、字体、字体颜色
	int		  m_iAngleUnit;			      //角度刻度单位30，15，10，5
	long      m_lAngleUnitLineStyle;      //线形
	COLORREF  m_crAngleUnitLineColor;     //刻度线颜色
	long      m_lAngleUnitLineWidth;	  //宽度
	LOGFONT   m_lfAngleUnitFont;		  //字体
	COLORREF  m_crAngleUnitFontColor;	  //字体颜色
	
	//定义幅值刻度相关的函数及其控制变量
	long      m_lCircleUnitLineStyle;
	COLORREF  m_crCircleUnitLineColor;
	long    m_lCircleUnitLineWidth;
	int		m_iCircleGridCounts;	//幅值刻度网格的个数
	int		m_iCircleAxisCount;		//幅值刻度的种类个数 0~10 个
	double	m_fCircleUnitValue[POLORAXIS_AXISCOUNT];	//各种类幅值刻度的量程
	double	m_fCircleValOneGap[POLORAXIS_AXISCOUNT];	//单位逻辑坐标对应的实际幅值大小
	char	m_ppszCircleUnitName[POLORAXIS_AXISCOUNT][POLORAXIS_NAMEBUFFLEN];	//坐标的名称
	
// Operations
public:
	void	InitIt();
	
	void	SetZoomCoefficient(long lVal);
	long	GetZoomCoefficient();
	void	SetPolarAxisBorder(CRect rectBorder);
	CRect	GetPolarAxisBorder();
	CRect	GetPolarAxisWorkArea();
	CPoint	GetPolarAxisCenterPoint();
	void	SetMarginGap(int iHorzGapLeft=30,int iVertGapTop=10,int iHorzGapRight=30,int iVertGapBottom=10);
	long    GetMarginGap(int iHorzGapLeft,int iVertGapTop,int iHorzGapRight,int iVertGapBottom);
	void	ResetPolarAxis();
	void	ResetPolarAxis(int iCircleUnitIndex);
	long	GetXAxisType();
	void	SetXAxisType(long lType);
	
	void SetAxisBackColor(COLORREF color);
	COLORREF GetAxisBackColor();
	void SetWorkAreaBkColor(COLORREF color);
	COLORREF GetWorkAreaBkColor();
	void SetAngleUnitLineStyle(COLORREF color);
	COLORREF SetAngleUnitLineStyle();
	void SetAxisCenterColor(COLORREF color);
	COLORREF GetAxisCenterColor();
	void SetAxisFrameColor(COLORREF color);
	COLORREF GetAxisFrameColor();
	void SetAngleUnitFontColor(COLORREF color);
	COLORREF GetAngleUnitFontColor();
	void SetAxisDrawType(long lVal);
	long GetAxisDrawType();
	void SetCenterLineType(long lVal);
	long GetCenterLineType();
	void SetCenterLineWidth(long lVal);
	long GetCenterLineWidth();
	void SetAngleUnitLineStyle(long lVal);
	long GetAngleUnitLineStyle();
	void SetAngleUnitLineColor(COLORREF color);
	COLORREF GetAngleUnitLineColor();
	
	//定义角度刻度相关的函数及控制变量
	void	SetAngleUnit(int iAngleUnitIndex);	//0=5;1=10;2=15;3=30
	int		GetAngleUnit();
	
	//定义幅值刻度相关的函数及其控制变量
	void	SetCircleGridCounts(int iCircleGridCounts);	//设置幅值刻度网格的个数
	int		GetCircleGridCounts();	//获得幅值刻度网格的个数
	
	void	SetCircleAxisCounts(int iCircleAxisCount);	//设置坐标的种类个数
	int		GetCircleAxisCounts();	//获得坐标的种类个数
	void	SetCircleUnitValue(int iUnitIndex,double fUnitVal);	//设置单个幅值坐标的幅值
	double	GetCircleUnitValue(int iUnitIndex);		//获得单个幅值坐标的幅值
	void	SetCircleUnitValue(double fUnitVal[10]);	//设置幅值坐标的幅值
	int 	GetCircleUnitValue(double fUnitVal[10]);	//获得幅值坐标的幅值，返回幅值坐标的个数
	
	//#########################################################
	//定义极坐标的总的对外接口函数
	void	DrawWorkArea(CDC *pDC);	//绘制边框
	void	DrawWorkAreaFrame(CDC *pDC);	//绘制边框
	void	DrawAxisBackGround(CDC *pDC);	//坐标轴的底色
	void	DrawAxisBoder(CDC *pDC);	//坐标轴的底色
	void    DrawAxisTitle(CDC *pDC,float fZoomRatio,CPoint ptOffset);
	
	void	DrawIt(CDC*pDC);		//总的绘制接口
	
	void	DrawTheVector(CDC*pDC,int iCircleUnitIndex,double fRadius,double fAngle,CString strVectorName,COLORREF crVector=RGB(0,0,0),int iLineWidth=1,unsigned int uiLineStyle=PS_SOLID,int iArrowLen=10,COLORREF crVectorTitle=RGB(0,0,0));//绘制一矢量图
	void	DrawTheVector(CDC*pDC,int iCircleUnitIndex,double fRadius1,double fAngle1,double fRadius2,double fAngle2,CString strVectorName,COLORREF crVector=RGB(0,0,0),int iLineWidth=1,unsigned int uiLineStyle=PS_SOLID,int iArrowLen=10,COLORREF crVectorTitle=RGB(0,0,0));//绘制一矢量图
	void	DrawTheVector(CDC*pDC,int iCircleUnitIndex,double fRadius1,double fAngle1,double fRadius2,double fAngle2,double *fRadiusL,double *fAngleL,CString strVectorName,COLORREF crVector=RGB(0,0,0),int iLineWidth=1,unsigned int uiLineStyle=PS_SOLID,int iArrowLen=10,COLORREF crVectorTitle=RGB(0,0,0));//绘制一矢量图
	
	void    ZoomIn(float fRate);
	void    ZoomOut(float fRate);
	void	DrawCircle(CDC *pDC,int iCircleUnitIndex,double *pfRadius,long nCircles,COLORREF crCircle,long nLineStype=PS_SOLID,long lLineWidth=1);
	
	void	DrawAngleUnit(CDC*pDC);	//绘制角度刻度
	void	DrawCircleUnit(CDC*pDC);//绘制幅值刻度
	void	DrawAxisCenter(CDC*pDC);//绘制中心轴
	
	void	GetTheVector(double fRadius1,double fAngle1,double fRadius2,double fAngle2,double *fRadiusL,double *fAngleL);
	
	void	LogicPointToDevicePoint(double fRadius,double fAngle,CPoint *pPoint,int iCircleUnitIndex=0);	//将逻辑坐标转化为实际坐标
	void	DevicePointToLogicPoint(CPoint point,double *fRadius,double *fAngle,int iCircleUnitIndex=0);//从实际坐标获取实际坐标所代表的值
	
	void ResetRuler();
	
	//设置坐标系的绘图位置
	long GetAxisMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax);
	//获取坐标系的绘图位置
	long GetPosition(long *left, long *top, long *right, long *bottom);
	//获取坐标系统的工作区，即坐标系统坐标范围标示的有效区域
	long GetWorkArea(long *left, long *top, long *right, long *bottom);
	//将逻辑坐标转化为设备坐标:ptx,pty为设备坐标
	long LogicPointToDevicePoint(double x,double y,long *ptx,long *pty);
	//将设备坐标转化为逻辑坐标:ptx,pty为设备坐标
	long DevicePointToLogicPoint (long ptx,long pty ,double *x,double *y);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolarAxis)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPolarAxis();

	// Generated message map functions
	//{{AFX_MSG(CPolarAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CPolarAxis)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CPolarAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(PolarAxisInterface,IPolarAxisInterface)
		//坐标系统的绘制类型,2005.08.12添加
		STDMETHOD_(long,SetAxisDrawStyle)(long nValue);
		STDMETHOD_(long,GetAxisDrawStyle)(long *nValue);
		STDMETHOD_(long,SetAxisDrawStyleBit)(long nValue);
		STDMETHOD_(long,ClearAxisDrawStyleBit)(long nValue);
		
		//坐标轴标题及其字体、颜色
		STDMETHOD_(long,SetAxisTitle)(BSTR bstrValue);
		STDMETHOD_(long,GetAxisTitle)(BSTR *pbstrValue);
		STDMETHOD_(long,SetAxisTitleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetAxisTitleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		STDMETHOD_(long,SetAxisTitleFontColor)(long nValue);
		STDMETHOD_(long,GetAxisTitleFontColor)(long *nValue);
		
		//坐标系统的背景色
		STDMETHOD_(long,SetAxisBackColor)(long nValue);
		STDMETHOD_(long,GetAxisBackColor)(long *nValue);
		//坐标系统工作区颜色
		STDMETHOD_(long,SetWorkAreaBkColor)(long nValue);
		STDMETHOD_(long,GetWorkAreaBkColor)(long *nValue);
		//坐标系统边框的颜色
		STDMETHOD_(long,SetFrameLeftTopColor)(long nValue);
		STDMETHOD_(long,GetFrameLeftTopColor)(long *nValue);
		STDMETHOD_(long,SetFrameRightBottomColor)(long nValue);
		STDMETHOD_(long,GetFrameRightBottomColor)(long *nValue);
		//坐标系统边框边界阴影
		STDMETHOD_(long,SetFrameShadow)(long nValue);
		STDMETHOD_(long,GetFrameShadow)(long *nValue);
		
		//角度刻度线的线型、颜色、线宽、字体、字体颜色
		STDMETHOD_(long,SetAngleUnitLineStyle)(long nValue);
		STDMETHOD_(long,GetAngleUnitLineStyle)(long *nValue);
		STDMETHOD_(long,SetAngleUnitLineColor)(long nValue);
		STDMETHOD_(long,GetAngleUnitLineColor)(long *nValue);
		STDMETHOD_(long,SetAngleUnitLineWidth)(long nValue);
		STDMETHOD_(long,GetAngleUnitLineWidth)(long *nValue);
		STDMETHOD_(long,SetAngleUnitFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetAngleUnitFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		STDMETHOD_(long,SetAngleUnitFontColor)(long nValue);
		STDMETHOD_(long,GetAngleUnitFontColor)(long *nValue);
		
		//圆(幅值)刻度线的线型、颜色、线宽
		STDMETHOD_(long,SetCircleUnitLineStyle)(long nValue);
		STDMETHOD_(long,GetCircleUnitLineStyle)(long *nValue);
		STDMETHOD_(long,SetCircleUnitLineColor)(long nValue);
		STDMETHOD_(long,GetCircleUnitLineColor)(long *nValue);
		STDMETHOD_(long,SetCircleUnitLineWidth)(long nValue);
		STDMETHOD_(long,GetCircleUnitLineWidth)(long *nValue);
		
		//坐标轴中心轴参数定义
		STDMETHOD_(long,SetAxisCenterLineWidth)(long nValue);
		STDMETHOD_(long,GetAxisCenterLineWidth)(long *nValue);
		STDMETHOD_(long,SetAxisCenterLineType)(long nValue);
		STDMETHOD_(long,GetAxisCenterLineType)(long *nValue);
		STDMETHOD_(long,SetAxisCenterColor)(long nValue);
		STDMETHOD_(long,GetAxisCenterColor)(long *nValue);
		
		//逻辑坐标与设备坐标之间的转换
		STDMETHOD_(long,LogicPointToDevicePoint)(double x,double y,long *ptx,long *pty);
		STDMETHOD_(long,DevicePointToLogicPoint)(long ptx,long pty ,double *x,double *y);
		
		//坐标范围
		STDMETHOD_(long,SetAngleUnitID)(long nValue);
		STDMETHOD_(long,GetAngleUnitID)(long *nValue);
		STDMETHOD_(long,SetCircleAxisCounts)(long nValue);
		STDMETHOD_(long,GetCircleAxisCounts)(long *nValue);
		STDMETHOD_(long,SetCircleUnitValue)(double dValue,long nCircleAxisID);
		STDMETHOD_(long,GetCircleUnitValue)(double *dValue,long nCircleAxisID);
		
		//坐标区域
		STDMETHOD_(long,SetBoder)(long left, long top, long right, long bottom);
		STDMETHOD_(long,GetBoder)(long *left, long *top, long *right, long *bottom);
		STDMETHOD_(long,GetWorkArea)(long *left, long *top, long *right, long *bottom);
		STDMETHOD_(long,SetMarginGap)(long nLeftGap, long nTopGap, long nRightGap, long nBottomGap);
		STDMETHOD_(long,GetMarginGap)(long *nLeftGap, long *nTopGap, long *nRightGap, long *nBottomGap);
		
		//重新计算坐标系统的刻度
		STDMETHOD_(long,ResetAxis)();
		
		//绘图
		STDMETHOD_(long,DrawAxis)(long lDC);
		STDMETHOD_(long,DrawVector)(long lDC,long nUnitIndex,double fRadius,double fAngle,BSTR strVectorName,long crVector,long nLineWidth,long nLineStyle,long nArrowLen,long crVectorTitle,float fZoomRatio,long xOffset,long yOffset);
		STDMETHOD_(long,DrawVectorEx)(long lDC,long nUnitIndex,double dRadius1,double dAngle1,double dRadius2,double dAngle2,BSTR strVectorName,long crVector,long nLineWidth,long nLineStyle,long nArrowLen,long crVectorTitle,float fZoomRatio,long xOffset,long yOffset);
		STDMETHOD_(long,DrawVectorEx2)(long lDC,long nUnitIndex,double dRadius1,double dAngle1,double dRadius2,double dAngle2,double *dRadiusL,double *dAngleL,BSTR strVectorName,long crVector,long nLineWidth,long nLineStyle,long nArrowLen,long crVectorTitle,float fZoomRatio,long xOffset,long yOffset);
		STDMETHOD_(long,GetTheVector)(double fRadius1,double fAngle1,double fRadius2,double fAngle2,double *fRadiusL,double *fAngleL);			
		STDMETHOD_(long,DrawCircle)(long lDC,long nUnitIndex,double dRadius,long crCircle,long nLineStype,long nLineWidth,float fZoomRatio,long xOffset,long yOffset);
		
		//放大缩小
		STDMETHOD_(long,ZoomIn)(float fRate);
		STDMETHOD_(long,ZoomOut)(float fRate);
	END_INTERFACE_PART(PolarAxisInterface)

	BEGIN_INTERFACE_PART(AxisBaseInterface,IAxisBaseInterface)
		//坐标区域
		STDMETHOD_(long,GetBoder)(long *left, long *top, long *right, long *bottom);
		STDMETHOD_(long,GetWorkArea)(long *left, long *top, long *right, long *bottom);
		//逻辑坐标与设备坐标之间的转换
		STDMETHOD_(long,LogicPointToDevicePoint)(double x,double y,long *ptx,long *pty);
		STDMETHOD_(long,DevicePointToLogicPoint)(long ptx,long pty ,double *x,double *y);
		//坐标范围
		STDMETHOD_(long,GetMinMaxVal)(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved);
	END_INTERFACE_PART(AxisBaseInterface)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLARAXIS_H__03FB2069_42F0_4D56_9193_5FB03F8BB502__INCLUDED_)
