// DescartesAxis.h: interface for the CDescartesAxis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined DESCARTESAXIS_H_
#define DESCARTESAXIS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxisInterface.h"

//////////////////////////////////////////////////////////////////////////
//############################笛卡尔坐标系统##############################
//////////////////////////////////////////////////////////////////////////
#define DESCARTESAXISDRAW_ALL				0x00FFFFFF
#define DESCARTESAXISDRAW_WORKAREA			0x00000001	//
#define DESCARTESAXISDRAW_AXISCENTER		0x00000002	//
#define DESCARTESAXISDRAW_AXISBODER			0x00000004	//
#define DESCARTESAXISDRAW_AXISTITLE			0x00000008	//

#define DESCARTESAXISDRAW_XAXIS_ALL			0x00000FF0	//
#define DESCARTESAXISDRAW_XAXIS_LINE		0x00000010	//
#define DESCARTESAXISDRAW_XAXIS_SCALETEXT	0x00000020	//
#define DESCARTESAXISDRAW_XAXIS_TENTHSCALE	0x00000040	//
#define DESCARTESAXISDRAW_XAXIS_HALFSCCALE	0x00000080	//
#define DESCARTESAXISDRAW_XAXIS_NAME		0x00000100	//

#define DESCARTESAXISDRAW_YAXIS_ALL			0x000FF000	//
#define DESCARTESAXISDRAW_YAXIS_LINE		0x00001000	//
#define DESCARTESAXISDRAW_YAXIS_SCALETEXT	0x00002000	//
#define DESCARTESAXISDRAW_YAXIS_TENTHSCALE	0x00004000	//
#define DESCARTESAXISDRAW_YAXIS_HALFSCCALE	0x00008000	//
#define DESCARTESAXISDRAW_YAXIS_NAME		0x00100000	//



class CDescartesAxis : public CAxisInterface
{
public:
	CDescartesAxis();
	virtual ~CDescartesAxis();

private:
	long    m_nMinOneGapWidth;		//X坐标轴的大刻度标注之间的间隔空间(宽度)最小值
	long    m_nMinOneGapHeight;		//Y坐标轴的大刻度标注之间的间隔空间(高度)最小值
	long	m_lAxisType;			//坐标轴的种类 0：普通坐标轴；  1：时间坐标轴
	BOOL    m_bAxisXYUnitLock;		//X、Y轴坐标的显示比例锁定标志
	double  m_dAxisWorkMarginRatio;	//坐标工作区同其中的图形的边距

	//坐标轴的最大刻度数
	long	m_lXAxisMaxUnitCount;
	long	m_lYAxisMaxUnitCount;
	

	//////////////////////////////////////////////////////////////////////////
	//坐标轴的相关数据
	//////////////////////////////////////////////////////////////////////////

	//坐标轴的范围：最大值，最小值
	double    m_dXAxisMinVal, m_dXAxisMaxVal;	//用于X轴====>>开始的位置，结束的位置
	double    m_dYAxisMinVal, m_dYAxisMaxVal;	//用于Y轴====>>显示区域的最大值，最小值,
	double    m_dY2AxisMinVal, m_dY2AxisMaxVal;	//用于Y轴====>>显示区域的最大值，最小值,
	
	CRect     m_rectBorder;	//坐标轴区域
	CRect     m_rectWorkArea;	//坐标轴工作区域

	CPoint	m_ptCenterLogInDv;	    ////逻辑坐标的原点在设备坐标上的坐标值
	double	m_dOneYGapValue;		///////Y轴实际坐标与实际值的比率
	double	m_dOneXGapValue;		///////X轴实际坐标与实际值的比率
	double	m_dOneY2GapValue;		///////Y轴实际坐标与实际值的比率
	
	//坐标轴的进位：按进位单位1、2、5、10
	double	m_dXCarryOneGap;	//X轴进位
	double	m_dYCarryOneGap;	//Y轴进位
	double	m_dY2CarryOneGap;	//Y轴进位
	float	m_fCoefficient;		//图形计算的放大系数，用于屏幕尺寸与打印的控制

	BOOL m_bLockXCarryOneGap;
	
	//坐标轴的相关区域
	CRect   m_rectXAxis, m_rectYAxis, m_rectY2Axis;	//X轴,Y轴区域
	long	m_nLeftGap,m_nRightGap,m_nTopGap,m_nBottomGap;	//
	
	//X轴,Y轴原始显示区域的最大值，最小值,用于恢复原图用
	double     m_dXAxisOldMinVal,m_dXAxisOldMaxVal;	//用于X轴====>>开始的位置，结束的位置
	double     m_dYAxisOldMinVal,m_dYAxisOldMaxVal;	//用于Y轴====>>显示区域的最大值，最小值,
	double     m_dY2AxisOldMinVal,m_dY2AxisOldMaxVal;	//用于Y轴====>>显示区域的最大值，最小值,

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
	long		 m_nWorkAreaBorderShadow;	//工作区边界阴影
	LOGBRUSH m_cBkGroundBrush;
	COLORREF m_crFrameLeftTopColor;
	COLORREF m_crFrameRightBottomColor;
	long	m_nFrameShadow;	//工作区边界阴影
	void     DrawXYAxisRect(CDC *pDC,float fZoomRatio,CPoint ptOffset);
	
	
	///////////////////////////////
	//Y坐标轴相关属性
	COLORREF m_crYAxisWorkAreaBackColorFrom, m_crYAxisWorkAreaBackColorTo;    //Y轴坐标区域颜色
	COLORREF m_crYUnitScaleColor;	//单位刻度颜色
	COLORREF m_crYUnitScaleShadowColor;//单位刻度阴影颜色
	LOGFONT   m_lfYAxisScaleFont;	////垂直刻度的字体
	LOGFONT   m_lfYAxisNameFont;		////Y轴名称的字体
	COLORREF  m_crYAxisScaleFontColor;//Y轴坐标标尺数字颜色
	COLORREF  m_crYAxisNameFontColor;//颜色
	long      m_lYAxisGridLineStyle;	//Y网格颜色
	COLORREF  m_crYAxisGridLineColor;
	LOGPEN	  m_logpenYAxisGridLine;
	COLORREF  m_crYAxisTenthScale;	//1/10刻度画笔颜色
	LOGPEN	  m_logpenYAxisTenthScale;	//1/10刻度画笔
	long       m_nYAxisAreaWidth;	//Y轴坐标区域的宽度
	long       m_nYAxisUnitScaleLineLen;	//Y轴坐标单位刻度长度
	long       m_nYAxisHalfScaleLineLen;	//Y轴坐标1/2刻度长度
	long       m_nYAxisTenthScaleLineLen;	//Y轴坐标1/10刻度长度
	
	//X坐标轴相关属性
	COLORREF m_crXAxisWorkAreaBackColorFrom, m_crXAxisWorkAreaBackColorTo;    //X轴坐标区域颜色
	COLORREF m_crXUnitScaleColor;	//单位刻度颜色
	COLORREF m_crXUnitScaleShadowColor;//单位刻度阴影颜色
	LOGFONT   m_lfXAxisScaleFont;	////垂直刻度的字体
	LOGFONT   m_lfXAxisNameFont;		////X轴名称的字体
	COLORREF  m_crXAxisScaleFontColor;
	COLORREF  m_crXAxisNameFontColor;//颜色
	long      m_lXAxisGridLineStyle;
	COLORREF  m_crXAxisGridLineColor;
	LOGPEN	  m_logpenXAxisGridLine;
	COLORREF  m_crXAxisTenthScale;	//1/10刻度画笔颜色
	LOGPEN	  m_logpenXAxisTenthScale;	//1/10刻度画笔
	long       m_nXAxisAreaHeight;	//X轴坐标区域的高度
	long       m_nXAxisUnitScaleLineLen;	//X轴坐标单位刻度长度
	long       m_nXAxisHalfScaleLineLen;	//X轴坐标1/2刻度长度
	long       m_nXAxisTenthScaleLineLen;	//X轴坐标1/10刻度长度
	
	////////	坐标轴中心轴参数定义
	long  m_lAxisCenterLineWidth;
	long  m_lAxisCenterLineType;
	COLORREF m_crAxisCenterColor;//坐标轴颜色

	double m_dMaxZoomMultiple;	//最大放大倍数

	//X坐标轴相关
	double		m_dXAxisOneGap;	//X轴的单位刻度的高度
	CString		m_strXAxisName;	//
	CAxisScaleDataList       m_listXAxisScale;
	//Y坐标轴相关
	double		m_dYAxisOneGap;	//Y轴的单位刻度的高度
	CString		m_strYAxisName;	//
	CAxisScaleDataList       m_listYAxisScale;


	BOOL      m_bUseY2Axis;
	CString		m_strY2AxisName;	//
	CAxisScaleDataList       m_listY2AxisScale;
	
	
// Operations
public:
	//坐标转换
	virtual void	LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint, long nAxisIndex=0);	//将逻辑坐标转化为实际坐标
	virtual void	DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0);//从实际坐标获取实际坐标所代表的值
    virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex);
    virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex);
    virtual void GetAxisDrawArea(CRect &rcArea);
	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
	virtual void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);//zhouhj 20210130 增加用于设置坐标轴名称等
	virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);

#ifdef USE_AXIS_CONFIG
	virtual void SetAxisConfig(CDataGroup *pAxisConfig);//zhouhj 20211026 增加用于设置坐标轴
	virtual void GetAxisConfig(CDataGroup *pAxisConfig);
	void SetAxisConfig(CDvmData *pAxisData);
#endif
	
private:
	void InitAxis();
	void ContinueInitAxis();
	
	CRect GetXAxisArea();
	CRect GetYAxisArea();
	CRect GetY2AxisArea();
	
	//////////////////////////////////////////////////////////////////////////
	//X Axis 
	COLORREF GetXAxisTenthScaleColr();


	//坐标相关数据计算
	double GetFloatCarryVal(double fVal);
	double MakeFloatGapValLegal(double fVal,double &lVal);//float fVal,long &lVal

	long GetCarryVal(long iVal);
	long MakeGapValLegal(float fVal,long &lVal);

	///////////////////////////////////////*********************************************
	///////////////////下面定义 Y 轴相关的数据及函数
	void	InitAxisAttr();
	void InitYAxisDef();
	void ResetYAxisDef();
	void ResetY2AxisDef();
	
	void EndYAxisDef();
	void ResetOneYAxisDef(double lVal);
	void ResetOneY2AxisDef(double lVal);
	void DrawYAxis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawY2Axis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisText(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawY2AxisText(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	long GetBaseOneGapHeight();
	long GetMinOneGapHeight();
	void DrawYSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawY2Sawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void GetOneYAxisHeight(double iGap,BYTE);		////////modify in 05-30;;
	void DrawOneYSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneY2Sawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneYSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneY2SawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisName(CDC*,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawY2AxisName(CDC*,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawAxisTitle(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
	///////////////////////////////////////*********************************************
	///////////////////下面定义 X 轴相关的数据及函数
	//++++++++++++++X 轴对外接口数据
	void InitXAxisDef();
	void ResetXAxisDef();

	void EndXAxisDef();
	void ResetOneXAxisDef(double lVal);
	void DrawXAxis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	CString GetTimeVal(float fTimeVal);
	CRect DrawXAxisText(CDC *pDC,CAxisScaleData *pScaleData,BOOL b=FALSE,BOOL bDraw=TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	long GetBaseOneGapWidth();
	long GetMinOneGapWidth();
	long Get60CarryVal(long iVal);
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


	//#############################################################################################//
	//################################接口定义#####################################################//
	//#############################################################################################//
public:
	void   SetUseY2Axis(BOOL bUseY2Axis)     {      m_bUseY2Axis = bUseY2Axis;  }
	BOOL   GetUseY2Axis()                    {      return m_bUseY2Axis;        }
	void   SetLeftGap(long nGap)             {      m_nLeftGap = nGap;          }
	void   SetTopGap(long nGap)              {      m_nTopGap = nGap;           }
	void   SetRightGap(long nGap)            {      m_nRightGap = nGap;         }
	void   SetBottomGap(long nGap)           {      m_nBottomGap = nGap;        }

	//////////////////////////////////////////////////////////////////////////
	//定义放大、缩小、移动接口
	virtual void ZoomIn(float fZoomIn=2.0f);
	void ZoomIn(double dMinX,double dMaxX,double dMinY,double dMaxY);
	void ZoomIn(CRect rectZoomIn);
	void ZoomIn(long lLeft,long lTop,long lRight,long lBottom);
	void ZoomIn(CPoint ptLeftTop,CPoint ptRightBottom);
	virtual void ZoomOut(float fZoomOut=2.0f);

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
	virtual void GetAxisInterface(long &nXCenterLog,long &nYCenterLog,double &dXCoef,double &dYCoef);
	
	//坐标系的绘图位置
	void SetMinMaxVal(double xMin,double yMin,double xMax,double yMax,long nReserved)
	{
#ifdef _PSX_IDE_QT_
            (void)nReserved;
#endif
                SetXYAxisMinMaxVal(xMin, yMin, xMax, yMax);
	}
	
	//////////////////////////////////////////////////////////////////////////
	//坐标系
public:
	//坐标范围
	void SetXYAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY, double dMinY2=0,double dMaxY2=10);
	void GetXYAxisMinMaxVal(double &dMinX,double &dMinY,double &dMaxX,double &dMaxY, double &dMinY2,double &dMaxY2);
	
	//坐标系名称
	void SetAxisTitle(CString strAxisTitle);
	CString GetAxisTitle();
	
	//坐标系工作区
	virtual CRect GetWorkArea();
	
	//坐标区域
	void SetBorder(CRect rectBorder);
	CRect GetBorder();

	void SetXAxisWorkAreaBackColor(COLORREF crAxisWorkAreaBackColorFrom, COLORREF crAxisWorkAreaBackColorTo)
	{
		m_crXAxisWorkAreaBackColorFrom = crAxisWorkAreaBackColorFrom;
		m_crXAxisWorkAreaBackColorTo = crAxisWorkAreaBackColorTo;
	}
	void SetYAxisWorkAreaBackColor(COLORREF crAxisWorkAreaBackColorFrom, COLORREF crAxisWorkAreaBackColorTo)
	{
		m_crYAxisWorkAreaBackColorFrom = crAxisWorkAreaBackColorFrom;
		m_crYAxisWorkAreaBackColorTo = crAxisWorkAreaBackColorTo;
	}
	void GetXAxisWorkAreaBackColor(COLORREF &crAxisWorkAreaBackColorFrom, COLORREF &crAxisWorkAreaBackColorTo)
	{
		crAxisWorkAreaBackColorFrom = m_crXAxisWorkAreaBackColorFrom;
		crAxisWorkAreaBackColorTo   = m_crXAxisWorkAreaBackColorTo;
	}
	void GetYAxisWorkAreaBackColor(COLORREF &crAxisWorkAreaBackColorFrom, COLORREF &crAxisWorkAreaBackColorTo)
	{
		crAxisWorkAreaBackColorFrom = m_crYAxisWorkAreaBackColorFrom;
		crAxisWorkAreaBackColorTo   = m_crYAxisWorkAreaBackColorTo;
	}
	//////////////////////////////////////////////////////////////////////////
	//X坐标轴
public:
	void SetXAxisName(CString strXAxisName);
	CString GetXAxisName();

	//X坐标轴的大刻度标注之间的间隔空间(宽度)最小值
	long GetXAxisMinSawGapWidth();
	void SetXAxisMinSawGapWidth(long nValue);

	//Y坐标轴的大刻度标注之间的间隔空间(高度)最小值
	long GetYAxisMinSawGapHeight();
	void SetYAxisMinSawGapHeight(long nValue);

	//坐标轴的种类 0：普通坐标轴；  1：时间坐标轴
	long GetXAxisType();
	void SetXAxisType(long nValue);

	//坐标轴的最大刻度数
	void SetXAxisMaxUnitCount(long nValue);
	long GetXAxisMaxUnitCount();
	void SetYAxisMaxUnitCount(long nValue);
	long GetYAxisMaxUnitCount();
	void LockXCarryOneGap(BOOL bLock, double dXCarryOneGap);

	//X、Y轴坐标的显示比例锁定标志
	void SetAxisXYUnitLock(long nValue);
	long GetAxisXYUnitLock();

	//坐标系统的绘制类型,2005.08.12添加
	void SetAxisDrawStyle(long nValue)      {        m_lAxisDrawStyle = nValue;    };
	void SetAxisDrawStyleEx(DWORD dwValue)      {        m_lAxisDrawStyle |= dwValue;    };
	void ClearAxisDrawStyleEx(DWORD dwValue)      {        m_lAxisDrawStyle &= (~dwValue);    };
	long GetAxisDrawStyle()                 {        return m_lAxisDrawStyle;      } ;
	void SetAxisDrawStyleBit(long nValue);
	long ClearAxisDrawStyleBit(long nValue);
	
	//X轴标注绘制模式：0=标注在刻度右边；1=标注在刻度下方居中
	void SetXAxisTextDrawStyle(long nValue = 1);
	long GetXAxisTextDrawStyle();

	//坐标轴标题及其字体、颜色
    //void SetAxisTitle(BSTR bstrValue);
    //long GetAxisTitle(BSTR *pbstrValue);
	void SetAxisTitleFont(LOGFONT lfFont);//long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetAxisTitleFont();//long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	void SetAxisTitleFontColor(COLORREF nValue);
	COLORREF GetAxisTitleFontColor();
	
	//坐标系统的背景色
	void SetAxisBackColor(COLORREF nValue);
	COLORREF GetAxisBackColor();

	//坐标系统工作区颜色
	void SetWorkAreaBkColor(COLORREF nValue);
	COLORREF GetWorkAreaBkColor();
	void SetWorkAreaBorderLeftTopColor(COLORREF nValue);
	COLORREF GetWorkAreaBorderLeftTopColor();
	void SetWorkAreaBorderRightBottomColor(COLORREF nValue);
	COLORREF GetWorkAreaBorderRightBottomColor();

	//工作区边界阴影
	void SetWorkAreaBorderShadow(long nValue);
	long GetWorkAreaBorderShadow();

	//坐标系统边框的颜色
	void SetFrameLeftTopColor(COLORREF nValue);
	COLORREF GetFrameLeftTopColor();
	void SetFrameRightBottomColor(COLORREF nValue);
	COLORREF GetFrameRightBottomColor();

	//坐标系统边框边界阴影
	void SetFrameShadow(long nValue);
	long GetFrameShadow();
	
	//////////////////////////////////////////////////////////////////////////
	//Y Axis
public:
	//轴名称
	void SetYAxisName(CString strYAxisName);
	CString GetYAxisName();
	void SetY2AxisName(CString strYAxisName);
	CString GetY2AxisName();

	//单位刻度颜色
	void SetYUnitScaleColor(COLORREF nValue);
	COLORREF GetYUnitScaleColor();
	//单位刻度阴影颜色
	void SetYUnitScaleShadowColor(COLORREF nValue);
	COLORREF GetYUnitScaleShadowColor();
	//垂直刻度的字体
	void SetYAxisScaleFont(LOGFONT lf);  //long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetYAxisScaleFont();  //long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//Y轴名称、字体、字体颜色
    //void SetYAxisName(BSTR bstrName);
    //long GetYAxisName(BSTR *pbstrName);
	//Y轴名称的字体
	void SetYAxisNameFont(LOGFONT lfFont);//(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetYAxisNameFont();//long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//Y轴名称字体颜色
	void SetYAxisNameFontColor(COLORREF nValue);
	COLORREF GetYAxisNameFontColor();
	//Y轴刻度字体颜色
	void SetYAxisScaleFontColor(COLORREF nValue);
	COLORREF GetYAxisScaleFontColor();
	//Y轴网格线型、颜色
	void SetYAxisGridLineStyle(long nValue);
	long GetYAxisGridLineStyle();
	void SetYAxisGridLineColor(COLORREF nValue);
	COLORREF GetYAxisGridLineColor();
	//1/10刻度画笔颜色
	void SetYAxisTenthScaleColor(COLORREF nValue);
	COLORREF GetYAxisTenthScaleColor();
	//Y轴坐标区域的宽度
	void SetYAxisAreaWidth(long nValue);
	long GetYAxisAreaWidth();
	//Y轴坐标单位刻度长度
	void SetYAxisUnitScaleLineLen(long nValue);
	long GetYAxisUnitScaleLineLen();
	//Y轴坐标1/2刻度长度
	void SetYAxisHalfScaleLineLen(long nValue);
	long GetYAxisHalfScaleLineLen();
	////Y轴坐标1/10刻度长度
	void SetYAxisTenthScaleLineLen(long nValue);
	long GetYAxisTenthScaleLineLen();
	
	//X Axis
	//单位刻度颜色
	void SetXUnitScaleColor(COLORREF nValue);
	COLORREF GetXUnitScaleColor();
	//单位刻度阴影颜色
	void SetXUnitScaleShadowColor(COLORREF nValue);
	COLORREF GetXUnitScaleShadowColor();
	//垂直刻度的字体
	void SetXAxisScaleFont(LOGFONT lfFont);//(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetXAxisScaleFont();//long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//X轴名称、字体、字体颜色
    //void SetXAxisName(BSTR bstrName);
    //long GetXAxisName(BSTR *pbstrName);
	//X轴名称的字体
	void SetXAxisNameFont(LOGFONT lfFont);//(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetXAxisNameFont();//long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//X轴名称字体颜色
	void SetXAxisNameFontColor(COLORREF nValue);
	COLORREF GetXAxisNameFontColor();
	//X轴刻度字体颜色
	void SetXAxisScaleFontColor(COLORREF nValue);
	COLORREF GetXAxisScaleFontColor();
	//X轴网格线型、颜色
	void SetXAxisGridLineStyle(long nValue);
	long GetXAxisGridLineStyle();
	void SetXAxisGridLineColor(COLORREF nValue);
	COLORREF GetXAxisGridLineColor();
	//1/10刻度画笔颜色
	void SetXAxisTenthScaleColor(COLORREF nValue);
	COLORREF GetXAxisTenthScaleColor();
	//X轴坐标区域的宽度
	void SetXAxisAreaHeight(long nValue);
	long GetXAxisAreaHeight();
	//X轴坐标单位刻度长度
	void SetXAxisUnitScaleLineLen(long nValue);
	long GetXAxisUnitScaleLineLen();
	//X轴坐标1/2刻度长度
	void SetXAxisHalfScaleLineLen(long nValue);
	long GetXAxisHalfScaleLineLen();
	////X轴坐标1/10刻度长度
	void SetXAxisTenthScaleLineLen(long nValue);
	long GetXAxisTenthScaleLineLen();
	
	//坐标轴中心轴参数定义
	void SetAxisCenterLineWidth(long nValue);
	long GetAxisCenterLineWidth();
	void SetAxisCenterLineType(long nValue);
	long GetAxisCenterLineType();
	void SetAxisCenterColor(COLORREF nValue);
	COLORREF GetAxisCenterColor();
	
	//重新计算坐标系统的刻度
	long ResetAxis();
	
	//绘图
	long DrawAxis(CDC *pDC, float fZoomRatio,long xOffset,long yOffset)
	{
		CPoint pt;
		pt = CPoint(xOffset,yOffset);
		DrawIt(pDC,fZoomRatio,pt);	
		return 0;
	}
	long DrawAxis(CDC *pDC,float fZoomRatio, CPoint &ptOffset)
	{
		DrawIt(pDC,fZoomRatio,ptOffset);	
		return 0;
	}
	
};


#endif // !defined(DESCARTESAXIS_H_
