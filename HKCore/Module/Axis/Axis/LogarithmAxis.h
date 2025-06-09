#if !defined(AFX_LOGARITHMAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_)
#define AFX_LOGARITHMAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogarithmAxis.h : header file
//
//#include "PowerAdvanceDrawPara.h"
//#include "PowerAdvanceRestoreData.h"
#include "..\..\Module\Interface\AxisInterface.h"
#include "..\..\Module\BaseObject\BaseObject.h"
#include "AxisScaleData.h"

#define LOGARITHM_XAXIS_LLINE			0x00000010
#define LOGARITHM_YAXIS_LLINE			0x00000020

#define POWERADVANCE_AREA				0x0001

#define POWERADVANCE_ALL				0x07fffffff
#define POWERADVANCE_XAXIS				0x0002
#define POWERADVANCE_XAXIS_LINE			0x00010000
#define POWERADVANCE_XAXIS_TEXT			0x00020000
#define POWERADVANCE_XAXIS_SAWTOOTH1	0x00040000
#define POWERADVANCE_XAXIS_SAWTOOTH2	0x00080000
#define POWERADVANCE_XAXIS_ALL			0x000F0002

#define POWERADVANCE_YAXIS				0x0004
#define POWERADVANCE_YAXIS_LINE			0x00100000
#define POWERADVANCE_YAXIS_TEXT			0x00200000
#define POWERADVANCE_YAXIS_SAWTOOTH1	0x00400000
#define POWERADVANCE_YAXIS_SAWTOOTH2	0x00800000
#define POWERADVANCE_YAXIS_ALL			0x00F00004

#define POWERADVANCE_AXISCENTER			0X00000100

#define POWERADVANCE_CIRCLE				0X00001000	//是否绘制圆刻度
#define POWERADVANCE_BIASlINE			0X00002000	//是否绘制斜线刻度

#define POWERADVANE_PI		3.14159265

/////////////////////////////////////////////////////////////////////////////
// CLogarithmAxis command target

class CLogarithmAxis : public CCmdTarget
{
	DECLARE_DYNCREATE(CLogarithmAxis)

	CLogarithmAxis();           // protected constructor used by dynamic creation

public:
	COLORREF	m_crAxisGrid;				//坐标的网格		
	COLORREF	m_crAxisCenter;				//坐标的中心轴颜色
	COLORREF	m_crAxisBK;					//坐标的背景
	COLORREF	m_crZoneLine;				//区段线颜色
	COLORREF	m_crTestTitle;				//测试项目的标题颜色
	COLORREF	m_crViewBK;					//视图底色
	long		m_lAxisGridLineType;		//坐标网格线的种类
	CRect	m_rectAxis;			//坐标系的位置
	float	m_fAxisValue[4];		//各坐标轴的范围	0-3：笛卡尔坐标；4-7对数坐标
	long    m_lAxisDrawStyle;
	long    m_lCurrTestItem;        //当前测试项目

	long m_lAxisType;			//坐标轴的种类
	BOOL m_bAxisXYUnitLock;
	long m_lXAxisMaxUnitCount;
	long m_lYAxisMaxUnitCount;

	LOGFONT   m_lfAxisTitleFont;	////坐标轴标题的字体
	COLORREF  m_crAxisTitleFont;	////坐标轴标题的字体颜色
	CString	  m_strAxisTitle;		////坐标轴标题

	COLORREF m_crAxisBackColor;

	COLORREF m_crFrameLeftTopColor;
	COLORREF m_crFrameRightBottomColor;
	int		 m_iFrameShadow;	//工作区边界阴影

	double m_dMaxZoomMultiple;	//最大放大倍数
	double	m_dAxisWorkMarginRatio;	//坐标工作区同其中的图形的边距
	
	//////////下面定义 Y 轴相关的数据及函数
	CBaseObjectList       odYAxisDef;
	float					iYAxisOneGap;
	CString				cYAxisName;
	void InitYAxisDef();
	void EndYAxisDef();
	void ResetYAxisDef();
	void ResetOneYAxisDef(float lVal);
	void DrawYAxis(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisText(CDC *cDC,CAxisScaleData *odData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void SetYAxisTenthScaleColor(COLORREF color);
	COLORREF GetYAxisTenthScaleColor();
	void SetXAxisTenthScaleColor(COLORREF color);
	COLORREF GetXAxisTenthScaleColr();
	void GetOneYAxisHeight(float iGap,BYTE);		
	void DrawOneYSawtooth(CDC *cDC,	CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneYSawtoothShadow(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisName(CDC*cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawAxisTitle(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
	///////////////////////////////////////*********************************************
	///////////////////下面定义 X 轴相关的数据及函数
	CBaseObjectList   odXAxisDef;
	float				iXAxisOneGap;
	CString				cXAxisName;
	void InitXAxisDef();
	void EndXAxisDef();
	void ResetXAxisDef();
	void ResetOneXAxisDef(float lVal,BYTE);
	void DrawXAxis(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	CRect DrawXAxisText(CDC *cDC,CAxisScaleData *odData,BOOL b=FALSE,BOOL bDraw=TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	float GetBeginVal(float lNowVal,float lGapVal); /////modify in 05-30;;
	float GetXBeginVal(float lNowVal,float lGapVal);
	void DrawXSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void GetOneXAxisWidth(float iGap,BYTE);
	void DrawOneXSawtooth(CDC *cDC,	CPoint cBegin,CPoint cEnd,float fCarryVal=1.0,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneXSawtoothShadow(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal=1.0,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisName(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
	void LogicPointToDevicePoint(float fx,float fy,CPoint *pPoint);	//将逻辑坐标转化为实际坐标
	void DevicePointToLogicPoint(CPoint point,double *fx,double *fy);//从实际坐标获取实际坐标所代表的值
	
	void DrawIt(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawFrame(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));	
	void ModifyWorkArea(CRect* cRect,BOOL bInit,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	BOOL MakeWorkAreaLegal(CRect &cNewRect);
	void SetAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY);
	long GetAxisMinMaxVal(double *dMinX,double *dMinY,double *dMaxX,double *dMaxY);
	void SetBorder(CRect rectBorder);
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
	long    lDisplayType;//显示类型
	long    lDrawXAxisTextType;
	int		iMM;
public:
	int iLeftGap,iRightGap,iTopGap,iBottomGap;
	//WorkArea Bk
	COLORREF crBkGroundColor,crBkLeftTopColor,crBkRightBottomColor;
	LOGBRUSH cBkGroundBrush;
	int		 iShadow;
	///////////////////////////////
	//VertDef
	LOGFONT   lfVertFont,lfVertTitleFont;////垂直刻度及Y轴名称的字体
	COLORREF  crVertColor,crVertTitleColor;//颜色
	long      lVertLineStyle;
	COLORREF  crVert_WorkAreaLine_Color;
	LOGPEN	  crVert_WorkAreaLine_Pen,crVert_WorkAreaShortLine_Pen;;
	int       iVertAreaWidth;
	int       iVertGapLineLen1,iVertGapLineLen2,iVertGapLineLen3;
	
	COLORREF  m_crYTenthScaleColor;
	COLORREF  m_crYUnitScaleColor,m_crYUnitScaleShadowColor;
	//HorzDef
	LOGFONT   lfHorzFont,lfHorzTitleFont;
	COLORREF  crHorzColor,crHorzTitleColor;
	long      lHorzLineStyle;
	COLORREF  crHorz_WorkAreaLine_Color;
	LOGPEN	  crHorz_WorkAreaLine_Pen,crHorz_WorkAreaShortLine_Pen;
	int       iHorzAreaWidth;
	int       iHorzGapLineLen1,iHorzGapLineLen2,iHorzGapLineLen3;
	
	COLORREF  m_crXTenthScaleColor;
	COLORREF  m_crXUnitScaleColor,m_crXUnitScaleShadowColor;
	//Cursor Area Def
	LOGPEN    lCursorPen;
	LOGPEN	  lChoiceAreaPen;
	LOGBRUSH  lChoiceAreaBrush;
	
	///斜线刻度、圆刻度的数据定义
	COLORREF	crCircleScale,crBiaslineScale;
	long	lCircleLineType,lBiasLineType;
	LOGPEN		cr_CircleScale_Pen,cr_BiaslineScale_Pen;
	float		fCircleScaleOffset,fBiaslineScaleOffset;	//圆刻度的半径位移、斜线刻度的角度位移
	
	////////	坐标轴中心轴参数定义
	long  lAxisCenterLineWidth;
	long  lAxisCenterLineType;
	COLORREF crAxisCenter;
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
	float	m_fOneYGapValue;		///////Y轴实际坐标与实际值的比率
	float	m_fOneXGapValue;		///////X轴实际坐标与实际值的比率
	
	float	m_fXCarryOneGap;
	float	m_fYCarryOneGap;
public:
	//	BYTE	bOnlyDisplayIntegeralArea;
	CRect   cBorder;
	CRect   cWorkArea;//工作区域
	CRect   cX_Axis,cY_Axis;//X轴,Y轴标注区域
	
	int     iDataMinVal,iDataMaxVal;//数据最大值，最小值
	float     iDisplayMinVal,iDisplayMaxVal;//用于Y轴====>>显示区域的最大值，最小值,
	float     iBeginPalace,iEndPalace;//用于X轴====>>开始的位置，结束的位置
	int		iDirection;//方向
	/////////////下面定义纪录X轴,Y轴原始显示区域的最大值，最小值,用于恢复原图用
	float     m_iOldBeginPalace,m_iOldEndPalace;//用于X轴====>>开始的位置，结束的位置
	float     m_iOldDisplayMinVal,m_iOldDisplayMaxVal;//用于Y轴====>>显示区域的最大值，最小值,
	//////////////////////////////////////////////
	int		iMinValueXAxis,iMaxValueXAxis;/////// X Axis max and min value.....
	long GetDataMaxVal();
	long GetDataMinVal();
	virtual const CLogarithmAxis & operator =(CLogarithmAxis &odTemp);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogarithmAxis)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLogarithmAxis();

	// Generated message map functions
	//{{AFX_MSG(CLogarithmAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLogarithmAxis)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CLogarithmAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
						 
	BEGIN_INTERFACE_PART(LogarithmAxisInterface,ILogarithmAxisInterface)
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
	END_INTERFACE_PART(LogarithmAxisInterface)

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

#endif // !defined(AFX_LOGARITHMAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_)
