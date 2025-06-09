#if !defined(AFX_RULERLOGAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_)
#define AFX_RULERLOGAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RulerLogAxis.h : header file

#include "AxisInterface.h"

#define RULER_AXIS_LLINE			0x00000010

#define LOGARITHM_AREA				0x0001

//////////////////////////////////////////////////////////////////////////
//############################对数坐标系统################################
//////////////////////////////////////////////////////////////////////////
#define RULERLOGAXISDRAW_ALL				0x00FFFFFF
#define RULERLOGAXISDRAW_WORKAREA			0x00000001
#define RULERLOGAXISDRAW_AXISCENTER		0x00000002	
#define RULERLOGAXISDRAW_AXISBODER			0x00000004	
#define RULERLOGAXISDRAW_AXISTITLE			0x00000008	

#define RULERLOGAXISDRAW_XAXIS_ALL			0x00000FF0	
#define RULERLOGAXISDRAW_XAXIS_LINE		0x00000010	
#define RULERLOGAXISDRAW_XAXIS_SCALETEXT	0x00000020	
#define RULERLOGAXISDRAW_XAXIS_SAWTOOTH1	0x00000040	
#define RULERLOGAXISDRAW_XAXIS_SAWTOOTH2	0x00000080	
#define RULERLOGAXISDRAW_XAXIS_NAME		0x00000100	


#define  Ruler_Type_Horz        0
#define  Ruler_Type_Vert         1
#define RULER_DIRECTION_RIGHTDOWN    0
#define RULER_DIRECTION_LEFTUP       1

/////////////////////////////////////////////////////////////////////////////
// CRulerLogAxis command target

class CRulerLogAxis : public CAxisInterface
{
public:
	CRulerLogAxis();           // protected constructor used by dynamic creation
	virtual ~CRulerLogAxis();

// Operations
public:
	//坐标转换
	virtual void	LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint, long nAxisIndex=0);	//将逻辑坐标转化为实际坐标
	virtual void	DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0);//从实际坐标获取实际坐标所代表的值
    virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex=0);
    virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex=0);
    virtual void GetAxisDrawArea(CRect &rcArea);
	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
	virtual void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);//zhouhj 20210130 增加用于设置坐标轴名称等
	virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);
	//lijunqing 2024-6-20
	void LogicPointToDevicePoint(double *pfBuff, CPoint *pPointBuf, long nDatasCount, long nAxisIndex);


#ifdef USE_AXIS_CONFIG
	virtual void SetAxisConfig(CDataGroup *pAxisConfig);//zhouhj 20211026 增加用于设置坐标轴
	virtual void GetAxisConfig(CDataGroup *pAxisConfig);
	void SetAxisConfig(CDvmData *pAxisData);
#endif

public:
    void SetRulerType(long nValue)
    {
        m_nRulerType = nValue;
    }

    void SetRulerTypeHorz()
    {
        SetRulerType(Ruler_Type_Horz);
    }
    void SetRulerTypeVert()
    {
        SetRulerType(Ruler_Type_Vert);
    }

    void	InitHorzRulerAttr();
    void	SetRulerDirection(int iRulerType);//标尺的方向
    int		GetRulerDirection();
    void	SetRulerHeight(int iHeight);//高度
    int		GetRulerHeight();

public:
    long	m_nRulerType;	////标尺的种类 0：水平标尺；  1：垂直标尺
    int		m_nRulerHeight;
    int		m_nRulerDirection;		//标尺的方向，0：标尺标注在下/右；	1：标尺标注在上/左

	COLORREF	m_crAxisGrid;				//坐标的网格		
	COLORREF	m_crAxisCenter;				//坐标的中心轴颜色
	COLORREF	m_crAxisBK;					//坐标的背景
	COLORREF	m_crZoneLine;				//区段线颜色
	COLORREF	m_crViewBK;					//视图底色

	long		m_lAxisGridLineType;		//坐标网格线的种类
    CRect	m_rectRuler;			//坐标系的位置
// 	float	m_fAxisValue[4];		//各坐标轴的范围	0-3：笛卡尔坐标；4-7对数坐标
	long    m_lAxisDrawStyle;

	long m_lXAxisMaxUnitCount;

	LOGFONT   m_lfAxisTitleFont;	////坐标轴标题的字体
	COLORREF  m_crAxisTitleFont;	////坐标轴标题的字体颜色
	CString	  m_strAxisTitle;		////坐标轴标题

	COLORREF m_crAxisBackColor;

	COLORREF m_crFrameLeftTopColor;
	COLORREF m_crFrameRightBottomColor;
	int		 m_iFrameShadow;	//工作区边界阴影

	double m_dMaxZoomMultiple;	//最大放大倍数
	double	m_dAxisWorkMarginRatio;	//坐标工作区同其中的图形的边距
	
	void DrawYAxis(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisText(CDC *cDC,CAxisScaleData *odData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void ResetYSawtoothSmall();
	void GetOneYAxisHeight(float iGap,BYTE);		
	void DrawOneYSawtoothSmall(CDC *cDC,	CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void ResetOneYSawtoothSmall(CPoint cBegin,CPoint cEnd,float fCarryVal);
	void DrawOneYSawtoothBig(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisName(CDC*cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawAxisTitle(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
	///////////////////////////////////////*********************************************
	///////////////////下面定义 X 轴相关的数据及函数
	CAxisScaleDataList   m_listRulerScale;
	CAxisScaleDataList   m_listRulerSmallScale; // mym 2024-06-20 add 为存储小刻度值

    float				m_fXAxisOneGap;
	CString				m_strXAxisName;
	void InitXAxisDef();
	void EndXAxisDef();
	void ResetXAxisDef();
	void ResetOneXAxisDef(float lVal,BYTE);

    void ResetYAxisDef();
    void ResetOneYAxisDef(float lVal);


	void DrawXAxis(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	CRect DrawXAxisText(CDC *cDC,CAxisScaleData *odData,BOOL b=FALSE,BOOL bDraw=TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	float GetBeginVal(float lNowVal,float lGapVal); /////modify in 05-30;;
	float GetXBeginVal(float lNowVal,float lGapVal);
	void DrawXSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void ResetXSawtoothSmall();
	void GetOneXAxisWidth(float iGap,BYTE);
	void DrawOneXSawtoothSmall(CDC *cDC,	CPoint cBegin,CPoint cEnd,float fCarryVal=1.0,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void ResetOneXSawtoothSmall(CPoint cBegin,CPoint cEnd,float fCarryVal=1.0);
	void DrawOneXSawtoothBig(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal=1.0,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisName(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
// 	void LogicPointToDevicePoint(float fx,float fy,CPoint *pPoint);	//将逻辑坐标转化为实际坐标
// 	void DevicePointToLogicPoint(CPoint point,double *fx,double *fy);//从实际坐标获取实际坐标所代表的值
	
	void DrawIt(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawFrame(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));	
	void ModifyWorkArea(CRect* pRect, BOOL bInit,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	BOOL MakeWorkAreaLegal(CRect &cNewRect);
	void SetAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY);
	long GetAxisMinMaxVal(double *dMinX,double *dMinY,double *dMaxX,double *dMaxY);
	void SetBorder(const CRect &rectBorder);
	void ResetAxis();
	void InitAxisAttr();
	//////
	CRect GetDrawWorkAreaRect();
	void DrawArea(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawAxisBack(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawWorkAreaBorder(CDC *pDC);//,cR,iGap,crLeftTop,crRightBottom);

	void ZoomIn(float fZoomIn=2.0f);
	void ZoomIn(double dMinX,double dMaxX,double dMinY,double dMaxY);
	void ZoomIn(long lLeft,long lTop,long lRight,long lBottom);	
	void ZoomOut(float fZoomOut=2.0f);	
	void Move(float fXOffset=1,float fYOffset=1);

//////////////////////////ADD at 0908//////////////////////////////
//////////////////////////DrawPara/////////////////////////////////
public:
	DWORD    m_dwDisplayType;//显示类型
	DWORD    m_dwDrawXAxisTextType;
	int		m_nZoomCoef;
	
public:
	int m_iLeftGap,m_iRightGap,m_iTopGap,m_iBottomGap;
	//WorkArea Bk
	COLORREF m_crBkGroundColor,m_crBkLeftTopColor,m_crBkRightBottomColor;
	LOGBRUSH m_cBkGroundBrush;
	int		 m_iShadow;
	///////////////////////////////
	//VertDef
	LOGFONT   m_lfVertFont,m_lfVertTitleFont;////垂直刻度及Y轴名称的字体
	COLORREF  m_crVertColor,m_crVertTitleColor;//颜色
	long      m_lVertLineStyle;
	COLORREF  m_crVert_WorkAreaLine_Color;
	LOGPEN	  m_penVert_WorkAreaLine,m_penVert_WorkAreaShortLine;;
	int       m_iVertAreaWidth;
	int       m_iVertGapLineLen1,m_iVertGapLineLen2,m_iVertGapLineLen3;
	
	COLORREF  m_crYTenthScaleColor;
	COLORREF  m_crYUnitScaleColor,m_crYUnitScaleShadowColor;
	//HorzDef
	LOGFONT   m_lfHorzFont,m_lfHorzTitleFont;
	COLORREF  m_crHorzColor,m_crHorzTitleColor;
	long      m_lHorzLineStyle;
	COLORREF  m_crHorz_WorkAreaLine_Color;
	LOGPEN	  m_penHorz_WorkAreaLine,m_penHorz_WorkAreaShortLine;
	int       m_iHorzAreaWidth;
	int       m_iHorzGapLineLen1,m_iHorzGapLineLen2,m_iHorzGapLineLen3;
	
	COLORREF  m_crXTenthScaleColor;
	COLORREF  m_crXUnitScaleColor,m_crXUnitScaleShadowColor;
	//Cursor Area Def
	LOGPEN    m_penCursor;
	LOGPEN	  m_penChoiceArea;
	LOGBRUSH  m_brushChoiceArea;
	
	///斜线刻度、圆刻度的数据定义
	COLORREF	m_crCircleScale,m_crBiaslineScale;
	long	m_lCircleLineType,m_lBiasLineType;
	LOGPEN		m_penCircleScale,m_penBiaslineScale;
	float		m_fCircleScaleOffset,m_fBiaslineScaleOffset;	//圆刻度的半径位移、斜线刻度的角度位移
	
	////////	坐标轴中心轴参数定义
	long  m_lAxisCenterLineWidth;
	long  m_lAxisCenterLineType;
	//	LOGPEN   logpenAxisCenter;
public:	
	void InitIt();
	void ContinueInit();

///////////////////////////////RestoreData///////////////////////////
public:
	int		m_iXMultipleCoeff,m_iYMultipleCoeff;		////图形放大的比例		逻辑值 / 设备值
	int		m_iXMaxMultipleCoeff,m_iYMaxMultipleCoeff;		////图形放大的比例		逻辑值 / 设备值
	int		m_iXMinMultipleCoeff,m_iYMinMultipleCoeff;		////图形放大的比例		逻辑值 / 设备值
	CPoint	m_ptCenterLogInDv;	////逻辑坐标的原点在设备坐标上的坐标值
	float	m_fOneXGapValue;		///////X轴实际坐标与实际值的比率
	float	m_fXCarryOneGap;
    int		m_nCenterLogInDv;
	
public:	
	int     m_iDataMinVal,m_iDataMaxVal;//数据最大值，最小值
	float     m_iBeginPalace,m_iEndPalace;//用于X轴====>>开始的位置，结束的位置
	int		m_iDirection;//方向
	/////////////下面定义纪录X轴,Y轴原始显示区域的最大值，最小值,用于恢复原图用
	float     m_iOldBeginPalace,m_iOldEndPalace;//用于X轴====>>开始的位置，结束的位置
	//////////////////////////////////////////////
	int		m_iMinValueXAxis,m_iMaxValueXAxis;/////// X Axis max and min value.....
	long GetDataMaxVal();
	long GetDataMinVal();
	virtual const CRulerLogAxis & operator =(CRulerLogAxis &odTemp);

// Operations
public:

// Implementation
public:
		//X坐标轴的大刻度标注之间的间隔空间(宽度)最小值
		long GetXAxisMinSawGapWidth(long *nValue);
		long SetXAxisMinSawGapWidth(long nValue);
		//Y坐标轴的大刻度标注之间的间隔空间(高度)最小值
		long GetYAxisMinSawGapHeight(long *nValue);
		long SetYAxisMinSawGapHeight(long nValue);
		//坐标轴的种类 0：普通坐标轴；  1：时间坐标轴
		long GetXAxisType(long *nValue);
		long SetXAxisType(long nValue);
		//坐标轴的最大刻度数
		long SetXAxisMaxUnitCount(long nValue);
		long GetXAxisMaxUnitCount(long *nValue);
		long SetYAxisMaxUnitCount(long nValue);
		long GetYAxisMaxUnitCount(long *nValue);
		//X、Y轴坐标的显示比例锁定标志
		long SetAxisXYUnitLock(long nValue);
		long GetAxisXYUnitLock(long *nValue);
		//坐标系统的绘制类型,2005.08.12添加
		long SetAxisDrawStyle(long nValue);
		long GetAxisDrawStyle(long *nValue);
		long SetAxisDrawStyleBit(long nValue);
		long ClearAxisDrawStyleBit(long nValue);
		
		//X轴标注绘制模式：0=标注在刻度右边；1=标注在刻度下方居中
		long SetXAxisTextDrawStyle(long nValue);
		long GetXAxisTextDrawStyle(long *nValue);
		//坐标轴标题及其字体、颜色
		long SetAxisTitle(const CString & bstrValue);
		long GetAxisTitle(CString *pbstrValue);
		long SetAxisTitleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName);
		long GetAxisTitleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName);
		long SetAxisTitleFontColor(long nValue);
		long GetAxisTitleFontColor(long *nValue);
		
		//坐标系统的背景色
		long SetAxisBackColor(long nValue);
		long GetAxisBackColor(long *nValue);
		//坐标系统工作区颜色
		long SetWorkAreaBkColor(long nValue);
		long GetWorkAreaBkColor(long *nValue);
		long SetWorkAreaBorderLeftTopColor(long nValue);
		long GetWorkAreaBorderLeftTopColor(long *nValue);
		long SetWorkAreaBorderRightBottomColor(long nValue);
		long GetWorkAreaBorderRightBottomColor(long *nValue);
		//工作区边界阴影
		long SetWorkAreaBorderShadow(long nValue);
		long GetWorkAreaBorderShadow(long *nValue);
		//坐标系统边框的颜色
		long SetFrameLeftTopColor(long nValue);
		long GetFrameLeftTopColor(long *nValue);
		long SetFrameRightBottomColor(long nValue);
		long GetFrameRightBottomColor(long *nValue);
		//坐标系统边框边界阴影
		long SetFrameShadow(long nValue);
		long GetFrameShadow(long *nValue);

		//X Axis
		//单位刻度颜色
		long SetXUnitScaleColor(long nValue);
		long GetXUnitScaleColor(long *nValue);
		//单位刻度阴影颜色
		long SetXUnitScaleShadowColor(long nValue);
		long GetXUnitScaleShadowColor(long *nValue);
		//垂直刻度的字体
		long SetXAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName);
		long GetXAxisScaleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName);
		//X轴名称、字体、字体颜色
		long SetXAxisName(const CString & bstrName);
		long GetXAxisName(CString *pbstrName);
		//X轴名称的字体
		long SetXAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName);
		long GetXAxisNameFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName);
		//X轴名称字体颜色
		long SetXAxisNameFontColor(long nValue);
		long GetXAxisNameFontColor(long *nValue);
		//X轴刻度字体颜色
		long SetXAxisScaleFontColor(long nValue);
		long GetXAxisScaleFontColor(long *nValue);
		//X轴网格线型、颜色
		long SetXAxisGridLineStyle(long nValue);
		long GetXAxisGridLineStyle(long *nValue);
		long SetXAxisGridLineColor(long nValue);
		long GetXAxisGridLineColor(long *nValue);
		//1/10刻度画笔颜色
		long SetXAxisTenthScaleColor(long nValue);
		long GetXAxisTenthScaleColor(long *nValue);

		//X轴坐标区域的宽度
		long SetXAxisAreaHeight(long nValue);
		long GetXAxisAreaHeight(long *nValue);
		//X轴坐标单位刻度长度
		long SetXAxisUnitScaleLineLen(long nValue);
		long GetXAxisUnitScaleLineLen(long *nValue);
		//X轴坐标1/2刻度长度
		long SetXAxisHalfScaleLineLen(long nValue);
		long GetXAxisHalfScaleLineLen(long *nValue);
		////X轴坐标1/10刻度长度
		long SetXAxisTenthScaleLineLen(long nValue);
		long GetXAxisTenthScaleLineLen(long *nValue);
		
		//坐标轴中心轴参数定义
		long SetAxisCenterLineWidth(long nValue);
		long GetAxisCenterLineWidth(long *nValue);
		long SetAxisCenterLineType(long nValue);
		long GetAxisCenterLineType(long *nValue);
		long SetAxisCenterColor(long nValue);
		long GetAxisCenterColor(long *nValue);
		
		//逻辑坐标与设备坐标之间的转换
		long LogicPointToDevicePoint(double x,double y,long *ptx,long *pty);
		long DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y);
		
		//坐标范围
		long SetMinMaxVal(double xMin,double yMin,double xMax,double yMax,long nReserved);
		long GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved);
		
		//坐标区域
		long SetBoder(long left, long top, long right, long bottom);
		long GetBoder(long *left, long *top, long *right, long *bottom);
		long GetWorkArea(long *left, long *top, long *right, long *bottom);
		virtual CRect GetWorkArea();
		long GetXAxisArea(long *left, long *top, long *right, long *bottom);
		long GetYAxisArea(long *left, long *top, long *right, long *bottom);
		
		//绘图
		long DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset);

		//放大缩小
		long ZoomIn1(float fRate);
		long ZoomIn2(double dMinX,double dMaxX,double dMinY,double dMaxY);
		long ZoomIn3(long left,long top,long right,long bottom);

		//坐标区域
		//long GetBoder(long *left, long *top, long *right, long *bottom);
		//long GetWorkArea(long *left, long *top, long *right, long *bottom);
		//逻辑坐标与设备坐标之间的转换
		//long LogicPointToDevicePoint(double x,double y,long *ptx,long *pty);
		//long DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y);
		//坐标范围
		//long GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved);
};

#endif // !defined(AFX_RULERLOGAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_)
