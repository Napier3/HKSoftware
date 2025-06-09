#if !defined(AFX_DESCARTESAXIS_H__8710398B_FF86_4B12_AE1B_6C53534255FD__INCLUDED_)
#define AFX_DESCARTESAXIS_H__8710398B_FF86_4B12_AE1B_6C53534255FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DescartesAxis.h : header file
//

#include "..\..\Module\BaseObject\BaseObject.h"
#include "..\..\Module\Interface\AxisInterface.h"

#define pi  3.141592653579798

/////////////////////////////////////////////////////////////////////////////
// CDescartesAxis command target

class CDescartesAxis : public CCmdTarget
{
	DECLARE_DYNCREATE(CDescartesAxis)

	CDescartesAxis();           // protected constructor used by dynamic creation

// Attributes
public:
	int		m_iMinOneGapWidth;		//X坐标轴的大刻度标注之间的间隔空间(宽度)最小值
	int		m_iMinOneGapHeight;		//Y坐标轴的大刻度标注之间的间隔空间(高度)最小值
	long	m_lAxisType;			//坐标轴的种类 0：普通坐标轴；  1：时间坐标轴
	BOOL	m_bAxisXYUnitLock;		//X、Y轴坐标的显示比例锁定标志
	double	m_dAxisWorkMarginRatio;	//坐标工作区同其中的图形的边距

	//坐标轴的最大刻度数
	long	m_lXAxisMaxUnitCount;
	long	m_lYAxisMaxUnitCount;
	
	double	m_fOneXGapValue;	///////X轴实际坐标与实际值的比率
	double	m_fOneYGapValue;	///////Y轴实际坐标与实际值的比率

	//////////////////////////////////////////////////////////////////////////
	//坐标轴的相关数据
	//////////////////////////////////////////////////////////////////////////

	//坐标轴的范围：最大值，最小值
	double     m_dXAxisMinVal,m_dXAxisMaxVal;	//用于X轴====>>开始的位置，结束的位置
	double    m_dYAxisMinVal,m_dYAxisMaxVal;	//用于Y轴====>>显示区域的最大值，最小值,
	
	CRect   m_rectBorder;	//坐标轴区域
	CRect   m_rectWorkArea;	//坐标轴工作区域

	CPoint	m_ptCenterLogInDv;	////逻辑坐标的原点在设备坐标上的坐标值
	double	m_dOneYGapValue;		///////Y轴实际坐标与实际值的比率
	double	m_dOneXGapValue;		///////X轴实际坐标与实际值的比率
	
	//坐标轴的进位：按进位单位1、2、5、10
	double	m_dXCarryOneGap;	//X轴进位
	double	m_dYCarryOneGap;	//Y轴进位
	float	m_fCoefficient;		//图形计算的放大系数，用于屏幕尺寸与大因此村的控制
	
	//坐标轴的相关区域
	
	CRect   m_rectXAxis,m_rectYAxis;	//X轴,Y轴区域
	int		m_iLeftGap,m_iRightGap,m_iTopGap,m_iBottomGap;	//

	//X轴,Y轴原始显示区域的最大值，最小值,用于恢复原图用
	double     m_dXAxisOldMinVal,m_dXAxisOldMaxVal;	//用于X轴====>>开始的位置，结束的位置
	double     m_dYAxisOldMinVal,m_dYAxisOldMaxVal;	//用于Y轴====>>显示区域的最大值，最小值,

	//////////////////////////////////////////////
	long    m_lAxisDrawStyle;	//显示类型
	long    m_lXAxisTextDrawStyle;	//X轴标注绘制模式：0=标注在刻度右边；1=标注在刻度下方居中
	
	LOGFONT   m_lfAxisTitleFont;	////坐标轴标题的字体
	COLORREF  m_crAxisTitleFont;	////坐标轴标题的字体颜色
	CString	  m_strAxisTitle;		////坐标轴标题

	COLORREF m_crAxisBackColor;
	//工作区相关底色参数
	COLORREF m_crWorkAreaBkColor;
	COLORREF m_crWorkAreaBorderLeftTopColor;
	COLORREF m_crWorkAreaBorderRightBottomColor;
	int		 m_iWorkAreaBorderShadow;	//工作区边界阴影
	LOGBRUSH m_cBkGroundBrush;
	COLORREF m_crFrameLeftTopColor;
	COLORREF m_crFrameRightBottomColor;
	int		 m_iFrameShadow;	//工作区边界阴影
	int      ColorR;
	int      ColorG;
	void     DrawXYAxisRect(CDC *pDC,float fZoomRatio,CPoint ptOffset);
	
	
	///////////////////////////////
	//Y坐标轴相关属性
	COLORREF m_crYUnitScaleColor;	//单位刻度颜色
	COLORREF m_crYUnitScaleShadowColor;//单位刻度阴影颜色
	LOGFONT   m_lfYAxisScaleFont;	////垂直刻度的字体
	LOGFONT   m_lfYAxisNameFont;		////Y轴名称的字体
	COLORREF  m_crYAxisScaleFontColor;
	COLORREF  m_crYAxisNameFontColor;//颜色
	long      m_lYAxisGridLineStyle;	//Y网格颜色
	COLORREF  m_crYAxisGridLineColor;
	LOGPEN	  m_logpenYAxisGridLine;
	COLORREF  m_crYAxisTenthScale;	//1/10刻度画笔颜色
	LOGPEN	  m_logpenYAxisTenthScale;	//1/10刻度画笔
	int       m_iYAxisAreaWidth;	//Y轴坐标区域的宽度
	int       m_iYAxisUnitScaleLineLen;	//Y轴坐标单位刻度长度
	int       m_iYAxisHalfScaleLineLen;	//Y轴坐标1/2刻度长度
	int       m_iYAxisTenthScaleLineLen;	//Y轴坐标1/10刻度长度
	
	//X坐标轴相关属性
	COLORREF m_crXUnitScaleColor;	//单位刻度颜色
	COLORREF m_crXUnitScaleShadowColor;//单位刻度阴影颜色
	LOGFONT   m_lfXAxisScaleFont;	////垂直刻度的字体
	LOGFONT   m_lfXAxisNameFont;		////Y轴名称的字体
	COLORREF  m_crXAxisScaleFontColor;
	COLORREF  m_crXAxisNameFontColor;//颜色
	long      m_lXAxisGridLineStyle;
	COLORREF  m_crXAxisGridLineColor;
	LOGPEN	  m_logpenXAxisGridLine;
	COLORREF  m_crXAxisTenthScale;	//1/10刻度画笔颜色
	LOGPEN	  m_logpenXAxisTenthScale;	//1/10刻度画笔
	int       m_iXAxisAreaHeight;	//X轴坐标区域的高度
	int       m_iXAxisUnitScaleLineLen;	//X轴坐标单位刻度长度
	int       m_iXAxisHalfScaleLineLen;	//X轴坐标1/2刻度长度
	int       m_iXAxisTenthScaleLineLen;	//X轴坐标1/10刻度长度

	////////	坐标轴中心轴参数定义
	long  m_lAxisCenterLineWidth;
	long  m_lAxisCenterLineType;
	COLORREF m_crAxisCenterColor;

	double m_dMaxZoomMultiple;	//最大放大倍数

	//X坐标轴相关
	double		m_dXAxisOneGap;	//X轴的单位刻度的高度
	CString		m_strXAxisName;	//
	CBaseObjectList       m_listXAxisScale;
	//Y坐标轴相关
	double		m_dYAxisOneGap;	//Y轴的单位刻度的高度
	CString		m_strYAxisName;	//
	CBaseObjectList       m_listYAxisScale;
	
	
// Operations
public:
	void InitAxis();
	void ContinueInitAxis();
	
	//////////////////////////////////////////////////////////////////////////
	//属性的Set、Get方法定义
	
	int		GetXAxisMinSawGapWidth();
	void	SetXAxisMinSawGapWidth(int iXAxisMinSawGapWidth);
	int		GetYAxisMinSawGapHeight();
	void	SetYAxisMinSawGapHeight(int iYAxisMinSawGapHeight);
	long	GetXAxisType();
	void	SetXAxisType(long lType);
	void SetXAxisMaxUnitCount(long lVal);
	long GetXAxisMaxUnitCount( );
	void SetYAxisMaxUnitCount(long lVal);
	long GetYAxisMaxUnitCount( );
	
	///////Add in 2005/7/28//////////
	void SetBorder(CRect rectBorder);
	CRect GetBorder();
	void SetAxisXYUnitLock(BOOL bXYUnitLock);
	BOOL GetAxisXYUnitLock();
	CRect GetXAxisArea();
	CRect GetYAxisArea();
	
	//////////////////////////////////////////////////////////////////////////
	//X Axis 
	void SetXYAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY);
	void GetXYAxisMinMaxVal(double &dMinX,double &dMinY,double &dMaxX,double &dMaxY);
	void SetXAxisTextDrawStyle(long lXAxisTextDrawStyle = 1);
	long GetXAxisTextDrawStyle();
	void SetAxisTitleFont(LOGFONT lf);
	LOGFONT GetAxisTitleFont();
	void SetAxisTitleFontColor(COLORREF color);
	COLORREF GetAxisTitleFontColor();
	void SetAxisTitle(CString strAxisTitle);
	CString GetAxisTitle();
	CRect GetWorkArea();
	void SetAxisBackColor(COLORREF color);
	COLORREF GetAxisBackColor();
	void SetWorkAreaBkColor(COLORREF color);
	COLORREF GetWorkAreaBkColor();
	void SetWorkAreaBorderLeftTopColor(COLORREF color);
	COLORREF GetWorkAreaBorderLeftTopColor();
	void SetWorkAreaBorderRightBottomColor(COLORREF color);
	COLORREF GetWorkAreaBorderRightBottomColor();
	void SetWorkAreaBorderShadow(long lWorkAreaBorderShadow);
	long GetWorkAreaBorderShadow();
	void SetFrameLeftTopColor(COLORREF color);
	COLORREF GetFrameLeftTopColor();
	void SetFrameRightBottomColor(COLORREF color);
	COLORREF GetFrameRightBottomColor();
	void SetFrameShadow(long lWorkAreaBorderShadow);
	long GetFrameShadow();
	
	//////////////////////////////////////////////////////////////////////////
	//Y Axis
	void SetYUnitScaleColor(COLORREF color);
	COLORREF GetYUnitScaleColor();
	void SetYUnitScaleShadowColor(COLORREF color);
	COLORREF GetYUnitScaleShadowColor();
	void SetYAxisScaleFont(LOGFONT lf);
	LOGFONT GetYAxisScaleFont();
	void SetYAxisNameFont(LOGFONT lf);
	LOGFONT GetYAxisNameFont();
	void SetYAxisScaleFontColor(COLORREF color);
	COLORREF GetYAxisScaleFontColor();
	void SetYAxisNameFontColor(COLORREF color);
	COLORREF GetYAxisNameFontColor();
	void SetYAxisGridLineStyle(long l);
	long GetYAxisGridLineStyle();
	void SetYAxisGridLineColor(COLORREF color);
	COLORREF GetYAxisGridLineColor();
	void SetYAxisTenthScaleColor(COLORREF color);
	COLORREF GetYAxisTenthScaleColor();
	void SetYAxisAreaWidth(long l);
	long GetYAxisAreaWidth();
	void SetYAxisUnitScaleLineLen(long l);
	long GetYAxisUnitScaleLineLen();
	void SetYAxisHalfScaleLineLen(long l);
	long GetYAxisHalfScaleLineLen();
	void SetYAxisTenthScaleLineLen(long l);
	long GetYAxisTenthScaleLineLen();

	//X Axis
	void SetXUnitScaleColor(COLORREF color);
	COLORREF GetXUnitScaleColor();
	void SetXUnitScaleShadowColor(COLORREF color);
	COLORREF GetXUnitScaleShadowColor();
	void SetXAxisScaleFont(LOGFONT lf);
	LOGFONT GetXAxisScaleFont();
	void SetXAxisNameFont(LOGFONT lf);
	LOGFONT GetXAxisNameFont();
	void SetXAxisScaleFontColor(COLORREF color);
	COLORREF GetXAxisScaleFontColor();
	void SetXAxisNameFontColor(COLORREF color);
	COLORREF GetXAxisNameFontColor();
	void SetXAxisGridLineStyle(long l);
	long GetXAxisGridLineStyle();
	void SetXAxisGridLineColor(COLORREF color);
	COLORREF GetXAxisGridLineColor();
	void SetXAxisTenthScaleColor(COLORREF color);
	COLORREF GetXAxisTenthScaleColr();
	void SetXAxisAreaHeight(long l);
	long GetXAxisAreaHeight();
	void SetXAxisUnitScaleLineLen(long l);
	long GetXAxisUnitScaleLineLen();
	void SetXAxisHalfScaleLineLen(long l);
	long GetXAxisHalfScaleLineLen();
	void SetXAxisTenthScaleLineLen(long l);
	long GetXAxisTenthScaleLineLen();

	//坐标轴中心轴参数定义
	void SetAxisCenterLineWidth(long l);
	long GetAxisCenterLineWidth();
	void SetAxisCenterLineType(long l);
	long GetAxisCenterLineType();
	void SetAxisCenterColor(COLORREF color);
	COLORREF GetAxisCenterColor();
	
	//坐标转换
	void	LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint);	//将逻辑坐标转化为实际坐标
	void	DevicePointToLogicPoint(CPoint point,double *fx,double *fy);//从实际坐标获取实际坐标所代表的值

	//坐标相关数据计算
	double GetFloatCarryVal(double fVal);
	double MakeFloatGapValLegal(double fVal,double &lVal);//float fVal,int &lVal
	
	long GetCarryVal(int iVal);
	int MakeGapValLegal(float fVal,int &lVal);

	///////////////////////////////////////*********************************************
	///////////////////下面定义 Y 轴相关的数据及函数
	void SetYAxisName(CString strYAxisName);
	CString GetYAxisName();

	void	InitAxisAttr();
	void InitYAxisDef();
	void ResetYAxisDef();
	
	void EndYAxisDef();
	void ResetOneYAxisDef(double lVal);
	void DrawYAxis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisText(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	long GetBaseOneGapHeight();
	long GetMinOneGapHeight();
	void DrawYSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void GetOneYAxisHeight(double iGap,BYTE);		////////modify in 05-30;;
	void DrawOneYSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneYSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisName(CDC*,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawAxisTitle(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
	///////////////////////////////////////*********************************************
	///////////////////下面定义 X 轴相关的数据及函数
	//++++++++++++++X 轴对外接口数据
	void InitXAxisDef();
	void ResetXAxisDef();
	void SetXAxisName(CString strXAxisName);
	CString GetXAxisName();

	void EndXAxisDef();
	void ResetOneXAxisDef(double lVal);
	void DrawXAxis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	CString GetTimeVal(float fTimeVal);
	CRect DrawXAxisText(CDC *pDC,CAxisScaleData *pScaleData,BOOL b=FALSE,BOOL bDraw=TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	long GetBaseOneGapWidth();
	long GetMinOneGapWidth();
	long Get60CarryVal(int iVal);
	double GetBeginVal(double lNowVal,double lGapVal); /////modify in 05-30;;
	double GetXBeginVal(double lNowVal,double lGapVal);
	void DrawXSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void GetOneXAxisWidth(double iGap,BYTE);
	void DrawOneXSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneXSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisName(CDC*,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));

	//坐标系统条整功能
	BOOL MakeWorkAreaLegal(CRect &cNewRect);
	CRect GetDrawWorkAreaRect(float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawArea(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawWorkAreaBorder(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));//,cR,iGap,crLeftTop,crRightBottom);
	void DrawAxisBack(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void AdjustAxisDef(CRect rectArea,BOOL bAdjust = TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	BOOL AdjustAxisDef(double fMinX,double fMinY,double fMaxX,double fMaxY,BOOL bAdjust = TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));

	//绘图功能
	void	DrawIt(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void	DrawFrame(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void	DrawAxisCenter(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void ModifyWorkArea(CRect* cRect,BOOL bInit,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));


public:
	//////////////////////////////////////////////////////////////////////////
	//定义放大、缩小、移动接口
	void ZoomIn(float fZoomIn=2.0f);
	void ZoomIn(double dMinX,double dMaxX,double dMinY,double dMaxY);
	void ZoomIn(CRect rectZoomIn);
	void ZoomIn(long lLeft,long lTop,long lRight,long lBottom);
	void ZoomIn(CPoint ptLeftTop,CPoint ptRightBottom);
	void ZoomOut(float fZoomOut=2.0f);

	void Move(float fXOffset=1,float fYOffset=1);

public:
	//设置坐标系的绘图位置
	virtual long GetAxisMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax);
	//获取坐标系的绘图位置
	virtual long GetPosition(long *left, long *top, long *right, long *bottom);
	//获取坐标系统的工作区，即坐标系统坐标范围标示的有效区域
	virtual long GetWorkArea(long *left, long *top, long *right, long *bottom);
	//将逻辑坐标转化为设备坐标:ptx,pty为设备坐标
	virtual long LogicPointToDevicePoint(double x,double y,long *ptx,long *pty);
	//将设备坐标转化为逻辑坐标:ptx,pty为设备坐标
	virtual long DevicePointToLogicPoint (long ptx,long pty ,double *x,double *y);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDescartesAxis)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDescartesAxis();

	// Generated message map functions
	//{{AFX_MSG(CDescartesAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CDescartesAxis)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDescartesAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(DescartesAxisInterface,IDescartesAxisInterface)
		//X坐标轴的大刻度标注之间的间隔空间(宽度)最小值
		STDMETHOD_(long,GetXAxisMinSawGapWidth)(long *nValue);
		STDMETHOD_(long,SetXAxisMinSawGapWidth)(long nValue);
		//Y坐标轴的大刻度标注之间的间隔空间(高度)最小值
		STDMETHOD_(long,GetYAxisMinSawGapHeight)(long *nValue);
		STDMETHOD_(long,SetYAxisMinSawGapHeight)(long nValue);
		//坐标轴的种类 0：普通坐标轴；  1：时间坐标轴
		STDMETHOD_(long,GetXAxisType)(long *nValue);
		STDMETHOD_(long,SetXAxisType)(long nValue);
		//坐标轴的最大刻度数
		STDMETHOD_(long,SetXAxisMaxUnitCount)(long nValue);
		STDMETHOD_(long,GetXAxisMaxUnitCount)(long *nValue);
		STDMETHOD_(long,SetYAxisMaxUnitCount)(long nValue);
		STDMETHOD_(long,GetYAxisMaxUnitCount)(long *nValue);
		//X、Y轴坐标的显示比例锁定标志
		STDMETHOD_(long,SetAxisXYUnitLock)(long nValue);
		STDMETHOD_(long,GetAxisXYUnitLock)(long *nValue);
		//坐标系统的绘制类型,2005.08.12添加
		STDMETHOD_(long,SetAxisDrawStyle)(long nValue);
		STDMETHOD_(long,GetAxisDrawStyle)(long *nValue);
		STDMETHOD_(long,SetAxisDrawStyleBit)(long nValue);
		STDMETHOD_(long,ClearAxisDrawStyleBit)(long nValue);
		
		//X轴标注绘制模式：0=标注在刻度右边；1=标注在刻度下方居中
		STDMETHOD_(long,SetXAxisTextDrawStyle)(long nValue);
		STDMETHOD_(long,GetXAxisTextDrawStyle)(long *nValue);
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
		STDMETHOD_(long,SetWorkAreaBorderLeftTopColor)(long nValue);
		STDMETHOD_(long,GetWorkAreaBorderLeftTopColor)(long *nValue);
		STDMETHOD_(long,SetWorkAreaBorderRightBottomColor)(long nValue);
		STDMETHOD_(long,GetWorkAreaBorderRightBottomColor)(long *nValue);
		//工作区边界阴影
		STDMETHOD_(long,SetWorkAreaBorderShadow)(long nValue);
		STDMETHOD_(long,GetWorkAreaBorderShadow)(long *nValue);
		//坐标系统边框的颜色
		STDMETHOD_(long,SetFrameLeftTopColor)(long nValue);
		STDMETHOD_(long,GetFrameLeftTopColor)(long *nValue);
		STDMETHOD_(long,SetFrameRightBottomColor)(long nValue);
		STDMETHOD_(long,GetFrameRightBottomColor)(long *nValue);
		//坐标系统边框边界阴影
		STDMETHOD_(long,SetFrameShadow)(long nValue);
		STDMETHOD_(long,GetFrameShadow)(long *nValue);
		
		//Y Axis
		//单位刻度颜色
		STDMETHOD_(long,SetYUnitScaleColor)(long nValue);
		STDMETHOD_(long,GetYUnitScaleColor)(long *nValue);
		//单位刻度阴影颜色
		STDMETHOD_(long,SetYUnitScaleShadowColor)(long nValue);
		STDMETHOD_(long,GetYUnitScaleShadowColor)(long *nValue);
		//垂直刻度的字体
		STDMETHOD_(long,SetYAxisScaleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetYAxisScaleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		//Y轴名称、字体、字体颜色
		STDMETHOD_(long,SetYAxisName)(BSTR bstrName);
		STDMETHOD_(long,GetYAxisName)(BSTR *pbstrName);
		//Y轴名称的字体
		STDMETHOD_(long,SetYAxisNameFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetYAxisNameFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		//Y轴名称字体颜色
		STDMETHOD_(long,SetYAxisNameFontColor)(long nValue);
		STDMETHOD_(long,GetYAxisNameFontColor)(long *nValue);
		//Y轴刻度字体颜色
		STDMETHOD_(long,SetYAxisScaleFontColor)(long nValue);
		STDMETHOD_(long,GetYAxisScaleFontColor)(long *nValue);
		//Y轴网格线型、颜色
		STDMETHOD_(long,SetYAxisGridLineStyle)(long nValue);
		STDMETHOD_(long,GetYAxisGridLineStyle)(long *nValue);
		STDMETHOD_(long,SetYAxisGridLineColor)(long nValue);
		STDMETHOD_(long,GetYAxisGridLineColor)(long *nValue);
		//1/10刻度画笔颜色
		STDMETHOD_(long,SetYAxisTenthScaleColor)(long nValue);
		STDMETHOD_(long,GetYAxisTenthScaleColor)(long *nValue);
		//Y轴坐标区域的宽度
		STDMETHOD_(long,SetYAxisAreaWidth)(long nValue);
		STDMETHOD_(long,GetYAxisAreaWidth)(long *nValue);
		//Y轴坐标单位刻度长度
		STDMETHOD_(long,SetYAxisUnitScaleLineLen)(long nValue);
		STDMETHOD_(long,GetYAxisUnitScaleLineLen)(long *nValue);
		//Y轴坐标1/2刻度长度
		STDMETHOD_(long,SetYAxisHalfScaleLineLen)(long nValue);
		STDMETHOD_(long,GetYAxisHalfScaleLineLen)(long *nValue);
		////Y轴坐标1/10刻度长度
		STDMETHOD_(long,SetYAxisTenthScaleLineLen)(long nValue);
		STDMETHOD_(long,GetYAxisTenthScaleLineLen)(long *nValue);

		//X Axis
		//单位刻度颜色
		STDMETHOD_(long,SetXUnitScaleColor)(long nValue);
		STDMETHOD_(long,GetXUnitScaleColor)(long *nValue);
		//单位刻度阴影颜色
		STDMETHOD_(long,SetXUnitScaleShadowColor)(long nValue);
		STDMETHOD_(long,GetXUnitScaleShadowColor)(long *nValue);
		//垂直刻度的字体
		STDMETHOD_(long,SetXAxisScaleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetXAxisScaleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		//X轴名称、字体、字体颜色
		STDMETHOD_(long,SetXAxisName)(BSTR bstrName);
		STDMETHOD_(long,GetXAxisName)(BSTR *pbstrName);
		//X轴名称的字体
		STDMETHOD_(long,SetXAxisNameFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetXAxisNameFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		//X轴名称字体颜色
		STDMETHOD_(long,SetXAxisNameFontColor)(long nValue);
		STDMETHOD_(long,GetXAxisNameFontColor)(long *nValue);
		//X轴刻度字体颜色
		STDMETHOD_(long,SetXAxisScaleFontColor)(long nValue);
		STDMETHOD_(long,GetXAxisScaleFontColor)(long *nValue);
		//X轴网格线型、颜色
		STDMETHOD_(long,SetXAxisGridLineStyle)(long nValue);
		STDMETHOD_(long,GetXAxisGridLineStyle)(long *nValue);
		STDMETHOD_(long,SetXAxisGridLineColor)(long nValue);
		STDMETHOD_(long,GetXAxisGridLineColor)(long *nValue);
		//1/10刻度画笔颜色
		STDMETHOD_(long,SetXAxisTenthScaleColor)(long nValue);
		STDMETHOD_(long,GetXAxisTenthScaleColor)(long *nValue);
		//X轴坐标区域的宽度
		STDMETHOD_(long,SetXAxisAreaHeight)(long nValue);
		STDMETHOD_(long,GetXAxisAreaHeight)(long *nValue);
		//X轴坐标单位刻度长度
		STDMETHOD_(long,SetXAxisUnitScaleLineLen)(long nValue);
		STDMETHOD_(long,GetXAxisUnitScaleLineLen)(long *nValue);
		//X轴坐标1/2刻度长度
		STDMETHOD_(long,SetXAxisHalfScaleLineLen)(long nValue);
		STDMETHOD_(long,GetXAxisHalfScaleLineLen)(long *nValue);
		////X轴坐标1/10刻度长度
		STDMETHOD_(long,SetXAxisTenthScaleLineLen)(long nValue);
		STDMETHOD_(long,GetXAxisTenthScaleLineLen)(long *nValue);
		
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
		STDMETHOD_(long,SetMinMaxVal)(double xMin,double yMin,double xMax,double yMax,long nReserved);
		STDMETHOD_(long,GetMinMaxVal)(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved);
		
		//坐标区域
		STDMETHOD_(long,SetBoder)(long left, long top, long right, long bottom);
		STDMETHOD_(long,GetBoder)(long *left, long *top, long *right, long *bottom);
		STDMETHOD_(long,GetWorkArea)(long *left, long *top, long *right, long *bottom);
		STDMETHOD_(long,GetXAxisArea)(long *left, long *top, long *right, long *bottom);
		STDMETHOD_(long,GetYAxisArea)(long *left, long *top, long *right, long *bottom);
		
		//重新计算坐标系统的刻度
		STDMETHOD_(long,ResetAxis)();

		//绘图
		STDMETHOD_(long,DrawAxis)(long lDC,float fZoomRatio,long xOffset,long yOffset);

		//放大缩小
		STDMETHOD_(long,ZoomIn1)(float fRate);
		STDMETHOD_(long,ZoomIn2)(double dMinX,double dMaxX,double dMinY,double dMaxY);
		STDMETHOD_(long,ZoomIn3)(long left,long top,long right,long bottom);
		STDMETHOD_(long,ZoomOut)(float fRate);
		STDMETHOD_(long,Move)(float fXOffset,float fYOffset);

	
	END_INTERFACE_PART(DescartesAxisInterface)

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

#endif // !defined(AFX_DESCARTESAXIS_H__8710398B_FF86_4B12_AE1B_6C53534255FD__INCLUDED_)
