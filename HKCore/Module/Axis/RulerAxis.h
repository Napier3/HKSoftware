#if !defined(AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_)
#define AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RulerAxis.h : header file

#define RULERDRAW_ALL				0x000FFFFF
#define RULERDRAW_BODER				0x00000001	//标尺边框
#define RULERDRAW_WORKAREA			0x00000002	//标尺工作区
#define RULERDRAW_SCALETEXT			0x00000004	//标尺标注
#define RULERDRAW_TENTHSCALE		0x00000008	//标尺1/10刻度绘制控制
#define RULERDRAW_HALFSCCALE		0x00000010	//标尺1/2刻度绘制控制

#include "AxisInterface.h"

#define RULER_DIRECTION_RIGHTDOWN    0
#define RULER_DIRECTION_LEFTUP       1

/////////////////////////////////////////////////////////////////////////////
// CRulerAxis command target

class CRulerAxis : public CAxisInterface
{
//2021-1-16  lijunqing
public:
	virtual void LogicPointToDevicePoint(double x, double y, CPoint *pPoint, long nAxisIndex=0);
	virtual void DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0);
	virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex);
	virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex);
	virtual void GetAxisDrawArea(CRect &rcArea);
	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
	virtual CRect GetWorkArea()	{	return m_rectRuler;	}
	virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);
#ifdef USE_AXIS_CONFIG
	virtual void SetAxisConfig(CDataGroup *pAxisConfig) ;
	virtual void GetAxisConfig(CDataGroup *pAxisConfig) ;
#endif
	void AttatchRefAxis(CRulerAxis *pAxis)	{	m_pRefAxis = pAxis;	}
protected:
	//如果m_pRefAxisX不为空，则自身为Y轴；如果m_pRefAxisY不为空，则自身为X轴
	CRulerAxis *m_pRefAxis;

public:
	CRulerAxis(); 
	virtual ~CRulerAxis();
	static const long g_nRulerType_Horz;
	static const long g_nRulerType_Vert;

// Attributes
public:
	long	m_nRulerType;	////标尺的种类 0：水平标尺；  1：垂直标尺
	double	m_dVectorCoef;				//矢量图的比例参数
	long	m_nDrawRulerTextType;	//标尺刻度标注的种类
	int		m_nBigSawMinWidth;		//标尺的大刻度标注之间的间隔空间(宽度)最小值
	int		m_nRulerHeight;
	long    m_nMaxRulerGapCount;
	double  m_dMaxZoomMultiple;
	long    m_nDrawStyle;
	
	int		m_nRulerDirection;		//标尺的方向，0：标尺标注在下/右；	1：标尺标注在上/左

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
	long     m_nFrameShadow;
	//HorzDef
	LOGFONT   m_lfRulerScaleFont, m_lfRulerTitleFont;
	COLORREF  m_crHorzSawText,m_crHorzTitleColor;
	CPen	  *m_pSmallSawPen;
	int       m_nHorBigSawLenLen,m_nHorHalfSawLen,m_nHorSmallSawLen;

// Operations
public:
	void InitIt();
	void ContinueInit();
	void SetScaleOffset(double dVal)	{	m_dScaleOffset = dVal;		}
	double GetScaleOffset()				{	return m_dScaleOffset;		}
	
	//##################################################3
	//逻辑坐标与实际坐标的转化
private:
	double    m_dScaleOffset;    //刻度标示的偏移
	double	m_dOneHorGapValue;
	int		m_nCenterLogInDv;

protected:
	double m_dAxisScaleRate;  //坐标刻度的比例，针对时间进行调整
	CString m_strOldRulerName;
	void AdjustAxisName_Time();

public:
	void	InitHorzRulerAttr();
	void	GetAxisInterface(double& dCoef , int& nCenterLog) { dCoef = m_dOneHorGapValue;  nCenterLog = m_nCenterLogInDv;	}

private:
	double GetFloatCarryVal(double fVal);
	double MakeFloatGapValLegal(double fVal,double &lVal);//float fVal,int &lVal
	
	
public:	//++++++++++++++X 轴对外接口数据
	double		m_dRulerHorOneGap;
	CString		m_strRulerName;
	void InitRulerDef();
	void ResetRulerDef();

	void SetRulerName(const CString &strName)
	{
		m_strRulerName = strName;
		m_strOldRulerName = strName;
		m_dAxisScaleRate = 1;
	}
	
	//##########################################################################
	//定义水平标尺的区域、做标值范围相关成员及函数
public:
	CRect	m_rectRuler;
	double	m_dHorMinValue;
	double	m_dHorMaxValue;
	double  m_dHorOldMinValue;
	double  m_dHorOldMaxValue;
	double	m_dHorCarryOneGap;
	int	m_nBOTTOMADD;
	
	void	ModifyRulerArea(CRect rectRuler);
	CRect	GetRulerArea();
	void	GetRulerMaxMinValue(double *dMinValue,double *dMaxValue);
	void	SetRulerMaxMinValue(double dMinValue,double dMaxValue);
	void	GetOldRulerMaxMinValue(double *dMinValue,double *dMaxValue);
	void	SetOldRulerMaxMinValue(double dMinValue,double dMaxValue);
	double	GetHorCarryOenGap();
	
	
	//////标尺的绘制、计算
	CAxisScaleDataList       m_listRulerScale;
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

	//坐标区域
	void SetBorder(long left,long top,long right,long bottom);
	void SetBorder(CRect rcBorder)    {    ModifyRulerArea(rcBorder);    }
	CRect GetBorder()                 {    return m_rectRuler;           }
//	void ZoomIn(float fRate);
//	void ZoomOut(float fRate);
//	void Move(float fOffset);
	
	CAxisScaleData* GetFirstAxisData(POS &pos);
	CAxisScaleData* GetNextAxisData(POS &pos);
	

	void	DrawIt(CDC *pDC);
	
	void DrawOneRulerHorSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd);
	void DrawOneRulerHorSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd);
	void DrawLine(CDC *pDC,int left,int top,int right,int bottom,CPen *pPen);
	void DrawRulerShadowVertLine(CDC *pDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2);
	void DrawRulerHor(CDC *pDC);
	void DrawRulerHorFrame(CDC*pDC);
	void DrawRulerHorLine(CDC *pDC,CAxisScaleData *pScaleData);
	void DrawRulerHorName(CDC*);
	void DrawRulerBack(CDC *pDC);

	//X坐标轴的大刻度标注之间的间隔空间(宽度)最小值
	long GetMinSawGapWidth(long *nValue);
	long SetMinSawGapWidth(long nValue);
	//标尺的种类 0：水平标尺；  1：垂直标尺
	long GetRulerType(long *nValue);
	long SetRulerType(long nValue);
	void SetRulerTypeHorz()
	{
		SetRulerType(g_nRulerType_Horz);
	}
	void SetRulerTypeVert()
	{
		SetRulerType(g_nRulerType_Vert);
	}
	//标尺的最大刻度数
	long SetMaxUnitCount(long nValue);
	long GetMaxUnitCount(long *nValue);
	//坐标系统的绘制类型,2005.08.12添加
	long SetDrawStyle(long nValue);
	long GetDrawStyle(long *nValue);
	long SetDrawStyleBit(long nValue);
	long ClearDrawStyleBit(long nValue);
	
	//标尺标注绘制模式：0=标注在刻度右边；1=标注在刻度下方居中
	long SetScaleTextDrawStyle(long nValue);
	long GetScaleTextDrawStyle(long *nValue);
	//坐标轴标题及其字体、颜色
	long SetRulerTitle(BSTR bstrValue);
	long GetRulerTitle(BSTR *pbstrValue);
	long SetRulerTitleFont(LOGFONT lfFont);
	LOGFONT GetRulerTitleFont();
	long SetRulerTitleFontColor(long nValue);
	long GetRulerTitleFontColor(long *nValue);
	
	//标尺背景色
	long SetRulerBackColor(long nValue);
	long GetRulerBackColor(long *nValue);
	//标尺边框的颜色
	long SetFrameLeftTopColor(long nValue);
	long GetFrameLeftTopColor(long *nValue);
	long SetFrameRightBottomColor(long nValue);
	long GetFrameRightBottomColor(long *nValue);
	//标尺边框边界阴影
	long SetFrameShadow(long nValue);
	long GetFrameShadow(long *nValue);
	
	//标尺单位刻度颜色
	long SetUnitScaleColor(long nValue);
	long GetUnitScaleColor(long *nValue);
	//标尺单位刻度阴影颜色
	long SetUnitScaleShadowColor(long nValue);
	long GetUnitScaleShadowColor(long *nValue);
	//标尺刻度的字体
	long SetRulerScaleFont(LOGFONT lfFont);
	LOGFONT GetRulerScaleFont();
	//标尺刻度字体颜色
	long SetRulerScaleFontColor(long nValue);
	long GetRulerScaleFontColor(long *nValue);
	//标尺1/10刻度画笔颜色
	long SetRulerTenthScaleColor(long nValue);
	long GetRulerTenthScaleColor(long *nValue);
	//标尺坐标区域的宽度/高度
	long SetRulerAreaWidth(long nValue);
	long GetRulerAreaWidth(long *nValue);
	//标尺单位刻度长度
	long SetRulerUnitScaleLineLen(long nValue);
	long GetRulerUnitScaleLineLen(long *nValue);
	//标尺1/2刻度长度
	long SetRulerHalfScaleLineLen(long nValue);
	long GetRulerHalfScaleLineLen(long *nValue);
	long SetRulerHalfScaleShow(long nValue);
	//标尺1/10刻度长度
	long SetRulerTenthScaleLineLen(long nValue);
	long GetRulerTenthScaleLineLen(long *nValue);
	long SetRulerTenthScaleShow(long nValue);
	//边界
	long SetRulerBoderShow(long nValue);
	//底色
	long SetDrawBack(long nValue);
	
	//逻辑坐标与设备坐标之间的转换
	void LogicPointToDevicePoint(double dValue,long *nValue);
    void LogicPointToDevicePoint(double dValue,int *nValue);
    void DevicePointToLogicPoint(long nValue,double *dValue);
	
	//坐标范围
	long SetMinMaxVal(double Min,double Max,long nReserved);
	long GetMinMaxVal(double *Min,double *Max,long nReserved);
	
	//重新计算坐标系统的刻度
	long ResetAxis();
	
	//绘图
	void DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset)
	{
		DrawIt(pDC);
	}
	
	//放大缩小
	void ZoomIn(float fRate);
	void ZoomOut(float fRate);
	void Move(float fOffset);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_)
