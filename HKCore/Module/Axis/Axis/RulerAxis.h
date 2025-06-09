#if !defined(AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_)
#define AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RulerAxis.h : header file
#include "..\..\Module\BaseObject\BaseObject.h"
#include "..\..\Module\Interface\AxisInterface.h"

#define RULERDRAW_ALL				0x000FFFFF
#define RULERDRAW_BODER				0x00000001	//标尺边框
#define RULERDRAW_WORKAREA			0x00000002	//标尺工作区
#define RULERDRAW_SCALETEXT			0x00000004	//标尺标注
#define RULERDRAW_TENTHSCALE		0x00000008	//标尺1/10刻度绘制控制
#define RULERDRAW_HALFSCCALE		0x00000010	//标尺1/2刻度绘制控制


/////////////////////////////////////////////////////////////////////////////
// CRulerAxis command target

class CRulerAxis : public CCmdTarget
{
	DECLARE_DYNCREATE(CRulerAxis)

	CRulerAxis();           // protected constructor used by dynamic creation

// Attributes
public:
	long	m_nRulerType;	////标尺的种类 0：水平标尺；  1：垂直标尺
	double	m_dVectorCoef;				//矢量图的比例参数
	long	m_lDrawRulerTextType;	//标尺刻度标注的种类
	int		m_iBigSawMinWidth;		//标尺的大刻度标注之间的间隔空间(宽度)最小值
	int		m_iRulerHeight;
	long    m_lMaxRulerGapCount;
	double  m_dMaxZoomMultiple;
	long    m_lDrawStyle;
	
	int		m_iRulerDirection;		//标尺的方向，0：标尺标注在下；	1：标尺标注在上

	void	SetVectorCoef(double dCoef);////矢量图的比例参数
	double	GetVectorCoef();
	void	SetRulerSawTextType(int iType);////标尺刻度标注的种类
	int		GetRulerSawTextType();
	void	SetBigSawMinWidth(int iSawWidth);//标尺的大刻度标注之间的间隔空间(宽度)最小值
	int		GetBigSawMinWidth();
	void	SetRulerDirection(int iRulerType);//标尺的方向
	int		GetRulerDirection();
	void	SetRulerHeight(int iHeight);//高度
	int		GetRulerHeight();
	
	COLORREF m_crSmallSaw;
	COLORREF crShadowColor1,crShadowColor2;//单位刻度颜色及单位刻度阴影颜色
	COLORREF m_crFrameLeftTop,m_crFrameRightBottom;
	COLORREF m_crRulerBackColor;
	long     m_lFrameShadow;
	//HorzDef
	LOGFONT   lfHorzFont,lfHorzTitleFont;
	COLORREF  m_crHorzSawText,m_crHorzTitleColor;
	LOGPEN	  m_logpenSmallSaw;
	int       m_iHorBigSawLenLen,m_iHorHalfSawLen,m_iHorSmallSawLen;
// Operations
public:
	void InitIt();
	void ContinueInit();
	
	//##################################################3
	//逻辑坐标与实际坐标的转化
private:
	double	m_dOneHorGapValue;
	int		m_iCenterLogInDv;
public:
	void	InitHorzRulerAttr();
	void	LogicPointToDevicePoint(double fx,long *iX);	//将逻辑坐标转化为实际坐标
	void	DevicePointToLogicPoint(long iX,double *dX);//从实际坐标获取实际坐标所代表的值
	
private:
	double GetFloatCarryVal(double fVal);
	double MakeFloatGapValLegal(double fVal,double &lVal);//float fVal,int &lVal
	
	
public:	//++++++++++++++X 轴对外接口数据
	double		m_dRulerHorOneGap;
	CString		m_strRulerName;
	void InitRulerDef();
	void ResetRulerDef();
	
	//##########################################################################
	//定义水平标尺的区域、做标值范围相关成员及函数
public:
	CRect	m_rectRuler;
	double	m_dHorMinValue;
	double	m_dHorMaxValue;
	double  m_dHorOldMinValue;
	double  m_dHorOldMaxValue;
	double	m_dHorCarryOneGap;
	int	m_iBOTTOMADD;
	
	void	ModifyRulerArea(CRect rectRuler);
	CRect	GetRulerArea();
	void	GetRulerMaxMinValue(double *dMinValue,double *dMaxValue);
	void	SetRulerMaxMinValue(double dMinValue,double dMaxValue);
	double	GetHorCarryOenGap();
	
	
	//////标尺的绘制、计算
	CBaseObjectList       m_listRulerDef;
	void EndRulerDef();
	void ResetOneRulerHorDef(double lVal);
	
	CString GetTimeVal(float fTimeVal);
	CRect DrawRulerHorText(CDC *pDC,CAxisScaleData *pScaleData,BOOL b=FALSE,BOOL bDraw=TRUE);
	long GetBaseOneGapWidth();
	long GetMinOneGapWidth();
	long GetMaxRulerGapNum();
	long Get60CarryVal(int iVal);
	double GetRulerBeginVal(double lNowVal,double lGapVal);
	void DrawRulerHorSawtooth(CDC*,BYTE);
	void GetOneRulerHorWidth(double iGap,BYTE);
	void SetBorder(long left,long top,long right,long bottom);
	CRect GetBorder();
	void ZoomIn(float fRate);
	void ZoomOut(float fRate);
	void Move(float fOffset);
	
	POSITION m_posAxisData;

	CAxisScaleData* GetFirstAxisData();
	CAxisScaleData* GetNextAxisData();
	

	void	DrawIt(CDC *pDC);
	
	void DrawOneRulerHorSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd);
	void DrawOneRulerHorSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd);
	void DrawLine(CDC *pDC,int left,int top,int right,int bottom,CPen *cP,BOOL bDel);
	void DrawRulerShadowVertLine(CDC *pDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2);
	void DrawRulerHor(CDC *pDC);
	void DrawRulerHorFrame(CDC*pDC);
	void DrawRulerHorLine(CDC *pDC,CAxisScaleData *pScaleData);
	void DrawRulerHorName(CDC*);
	void DrawRulerBack(CDC *pDC);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulerAxis)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRulerAxis();

	// Generated message map functions
	//{{AFX_MSG(CRulerAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CRulerAxis)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CRulerAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

BEGIN_INTERFACE_PART(RulerAxisInterface,IRulerAxisInterface)
	//X坐标轴的大刻度标注之间的间隔空间(宽度)最小值
	STDMETHOD_(long,GetMinSawGapWidth)(long *nValue);
	STDMETHOD_(long,SetMinSawGapWidth)(long nValue);
	//标尺的种类 0：水平标尺；  1：垂直标尺
	STDMETHOD_(long,GetRulerType)(long *nValue);
	STDMETHOD_(long,SetRulerType)(long nValue);
	//标尺的最大刻度数
	STDMETHOD_(long,SetMaxUnitCount)(long nValue);
	STDMETHOD_(long,GetMaxUnitCount)(long *nValue);
	//坐标系统的绘制类型,2005.08.12添加
	STDMETHOD_(long,SetDrawStyle)(long nValue);
	STDMETHOD_(long,GetDrawStyle)(long *nValue);
	STDMETHOD_(long,SetDrawStyleBit)(long nValue);
	STDMETHOD_(long,ClearDrawStyleBit)(long nValue);
	
	//标尺标注绘制模式：0=标注在刻度右边；1=标注在刻度下方居中
	STDMETHOD_(long,SetScaleTextDrawStyle)(long nValue);
	STDMETHOD_(long,GetScaleTextDrawStyle)(long *nValue);
	//坐标轴标题及其字体、颜色
	STDMETHOD_(long,SetRulerTitle)(BSTR bstrValue);
	STDMETHOD_(long,GetRulerTitle)(BSTR *pbstrValue);
	STDMETHOD_(long,SetRulerTitleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	STDMETHOD_(long,GetRulerTitleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	STDMETHOD_(long,SetRulerTitleFontColor)(long nValue);
	STDMETHOD_(long,GetRulerTitleFontColor)(long *nValue);
	
	//标尺背景色
	STDMETHOD_(long,SetRulerBackColor)(long nValue);
	STDMETHOD_(long,GetRulerBackColor)(long *nValue);
	//标尺边框的颜色
	STDMETHOD_(long,SetFrameLeftTopColor)(long nValue);
	STDMETHOD_(long,GetFrameLeftTopColor)(long *nValue);
	STDMETHOD_(long,SetFrameRightBottomColor)(long nValue);
	STDMETHOD_(long,GetFrameRightBottomColor)(long *nValue);
	//标尺边框边界阴影
	STDMETHOD_(long,SetFrameShadow)(long nValue);
	STDMETHOD_(long,GetFrameShadow)(long *nValue);
	
	//标尺单位刻度颜色
	STDMETHOD_(long,SetUnitScaleColor)(long nValue);
	STDMETHOD_(long,GetUnitScaleColor)(long *nValue);
	//标尺单位刻度阴影颜色
	STDMETHOD_(long,SetUnitScaleShadowColor)(long nValue);
	STDMETHOD_(long,GetUnitScaleShadowColor)(long *nValue);
	//标尺刻度的字体
	STDMETHOD_(long,SetRulerScaleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	STDMETHOD_(long,GetRulerScaleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//标尺刻度字体颜色
	STDMETHOD_(long,SetRulerScaleFontColor)(long nValue);
	STDMETHOD_(long,GetRulerScaleFontColor)(long *nValue);
	//标尺1/10刻度画笔颜色
	STDMETHOD_(long,SetRulerTenthScaleColor)(long nValue);
	STDMETHOD_(long,GetRulerTenthScaleColor)(long *nValue);
	//标尺坐标区域的宽度/高度
	STDMETHOD_(long,SetRulerAreaWidth)(long nValue);
	STDMETHOD_(long,GetRulerAreaWidth)(long *nValue);
	//标尺单位刻度长度
	STDMETHOD_(long,SetRulerUnitScaleLineLen)(long nValue);
	STDMETHOD_(long,GetRulerUnitScaleLineLen)(long *nValue);
	//标尺1/2刻度长度
	STDMETHOD_(long,SetRulerHalfScaleLineLen)(long nValue);
	STDMETHOD_(long,GetRulerHalfScaleLineLen)(long *nValue);
	//标尺1/10刻度长度
	STDMETHOD_(long,SetRulerTenthScaleLineLen)(long nValue);
	STDMETHOD_(long,GetRulerTenthScaleLineLen)(long *nValue);
	
	//逻辑坐标与设备坐标之间的转换
	STDMETHOD_(long,LogicPointToDevicePoint)(double dValue,long *nValue);
	STDMETHOD_(long,DevicePointToLogicPoint)(long nValue,double *dValue);
	
	//坐标范围
	STDMETHOD_(long,SetMinMaxVal)(double Min,double Max,long nReserved);
	STDMETHOD_(long,GetMinMaxVal)(double *Min,double *Max,long nReserved);
	
	//坐标区域
	STDMETHOD_(long,SetBoder)(long left, long top, long right, long bottom);
	STDMETHOD_(long,GetBoder)(long *left, long *top, long *right, long *bottom);
	
	//重新计算坐标系统的刻度
	STDMETHOD_(long,ResetAxis)();
	
	//绘图
	STDMETHOD_(long,DrawAxis)(long lDC,float fZoomRatio,long xOffset,long yOffset);
	
	//放大缩小
	STDMETHOD_(long,ZoomIn)(float fRate);
	STDMETHOD_(long,ZoomOut)(float fRate);
	STDMETHOD_(long,Move)(float fOffset);
	
END_INTERFACE_PART(RulerAxisInterface)

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

#endif // !defined(AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_)
