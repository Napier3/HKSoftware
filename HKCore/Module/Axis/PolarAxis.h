#if !defined(_POLARAXIS_H__)
#define _POLARAXIS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PolarAxis.h : header file
//
#include "AxisInterface.h"


#define		POLORAXIS_NAMEBUFFLEN	80
#define		POLORAXIS_AXISCOUNT		10

#define AXISTYPE_DESCARTES	0
#define AXISTYPE_POLOR		1
#define AXISTYPE_LOGARITHM	2

#define PI_180_RADIANTOANGLE	0.01745329	// 3.141592654/180
#define PI_180_ANGLETORADIAN	57.29577951	// 180/3.141592654


#define POLARAXISDRAW_ALL				0x000FFFFF
#define POLARAXISDRAW_WORKAREA			0x00000001	
#define POLARAXISDRAW_WORKAREAFRAME		0x00000002	
#define POLARAXISDRAW_AXISCENTER		0x00000004	
#define POLARAXISDRAW_AXISBODER			0x00000008	
#define POLARAXISDRAW_AXISTITLE			0x00000010	
#define POLARAXISDRAW_ANGLEUNIT_LINE	0x00000020	
#define POLARAXISDRAW_ANGLEUNIT_TEXT	0x00000040	
#define POLARAXISDRAW_CIRCLEUNIT		0x00000080	
#define POLARAXISDRAW_CIRCLEUNITTEXT	0x00001000	

//2022-5-14 lijunqing 
typedef struct _polar_vector_
{
public:
	char pszName[32];
	double dMag;
	double dAng;
	COLORREF crVector;//=RGB(0,0,0),
	int nLineWidth;//=1,
	unsigned int uiLineStyle;//=PS_SOLID,
	int nArrowLen;//=10,
	COLORREF crVectorTitle;//=RGB(0,0,0)
	
	void Init(char *p, long nWidth=3)
	{
		strcpy(pszName, p);

		if (pszName[1] == 'a')
		{
			crVector =RGB(255, 255, 0);
		}
		else if (pszName[1] == 'b')
		{
			crVector =RGB(0, 0, 255);
		}
		else if (pszName[1] == 'c')
		{
			crVector =RGB(255, 0, 0);
		}
		else
		{
			crVector =RGB(0, 0, 0);
		}

		nLineWidth = nWidth;
		uiLineStyle =PS_SOLID;
		nArrowLen=10;
		crVectorTitle=RGB(0,0,0);
	}

	void Init2(long nCh, long nWidth=3)
	{
		if (nCh == 0)
		{
			crVector =RGB(255, 255, 0);
		}
		else if (nCh == 1)
		{
			crVector =RGB(0, 0, 255);
		}
		else if (nCh == 2)
		{
			crVector =RGB(255, 0, 0);
		}
		else
		{
			crVector =RGB(0, 0, 0);
		}

		nLineWidth = nWidth;
		uiLineStyle =PS_SOLID;
		nArrowLen=10;
		crVectorTitle=RGB(0,0,0);
	}

}POLAR_VECTOR;

typedef struct _polar_vectors_
{
public:
	long nAxis;
	long nCount;
	long nEnable;
	POLAR_VECTOR *pArrVector;

	_polar_vectors_()
	{
		nAxis = 0;
		nCount = 0;
		nEnable = 1;
		pArrVector = NULL;
	}

	~_polar_vectors_()
	{
		Free();
	}

	void Free()
	{
		if (pArrVector != NULL)
		{
			free(pArrVector);
			pArrVector = NULL;
		}
	}

	void SetVectors(long n)
	{
		Free();

		if (n > 0)
		{
			pArrVector = (POLAR_VECTOR*)malloc(n * sizeof(POLAR_VECTOR));
			memset(pArrVector, 0, n * sizeof(POLAR_VECTOR));
		}

		nCount = n;
	}

	POLAR_VECTOR* GetAt(long nIndex)
	{
		if (nIndex < 0 || nIndex >= nCount)
		{
			return NULL;
		}

		return pArrVector + nIndex;
	}

	double get_max()
	{
		long k = 0;
		double dMax = 0;

		for (k=0; k<nCount; k++)
		{
			POLAR_VECTOR *p = pArrVector + k;
			dMax = dMax > p->dMag ? dMax : p->dMag;
		}

		return dMax;
	}

}POLAR_VECTORS;


typedef struct _polar_vectors_mngr_
{
public:
	long nCount;
	POLAR_VECTORS *pArrVectors;

	_polar_vectors_mngr_()
	{
		nCount = 0;
		pArrVectors = NULL;
	}

	~_polar_vectors_mngr_()
	{
		Free();
	}

	void Free()
	{
		if (pArrVectors != NULL)
		{
			free(pArrVectors);
			pArrVectors = NULL;
		}
	}

	void SetVectors(long nVal)
	{
		Free();

		if (nVal > 0)
		{
			pArrVectors = (POLAR_VECTORS*)malloc(nVal * sizeof(POLAR_VECTORS));
			memset(pArrVectors, 0, nVal * sizeof(POLAR_VECTORS));
		}

		nCount = nVal;
	}
	void SetVectors(long nIndex, long nVal)
	{
		POLAR_VECTORS *p = GetAt(nIndex);

		if (p != NULL)
		{
			p->SetVectors(nVal);
		}
	}
	POLAR_VECTORS* GetAt(long n)
	{
		if (n < 0 || n >= nCount)
		{
			return NULL;
		}

		return pArrVectors + n;
	}

}POLAR_VECTORS_MNGR;

/////////////////////////////////////////////////////////////////////////////
// CPolarAxis command target

class CPolarAxis : public CAxisInterface
{
public:
	CPolarAxis();
	virtual ~CPolarAxis();

public://CAxisInterface
// 	virtual void LogicPointToDevicePoint(double x, double y, CPoint *pPoint, long nAxisIndex=0) = 0;
// 	virtual void DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0) = 0;
//	virtual void GetAxisDrawArea(CRect &rcArea) = 0;
//	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax) =  0;
	virtual void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);//zhouhj 20210130 增加用于设置坐标轴名称等
	virtual CRect GetWorkArea();
//	virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);

#ifdef USE_AXIS_CONFIG
	virtual void SetAxisConfig(CDataGroup *pAxisConfig);
	virtual void GetAxisConfig(CDataGroup *pAxisConfig);
#endif

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
	LOGFONT	m_lfAxisCenter;			//坐标中心轴标注字体
	LOGFONT	m_lfVectorName;			//矢量的名称绘制字体
	
	LOGFONT   m_lfPolarAxisTitleFont;	////坐标轴标题的字体
	COLORREF  m_crPolarAxisTitleFont;	////坐标轴标题的字体颜色
	CString	  m_strPolarAxisTitle;		////坐标轴标题
	
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
	void    AssertCircleGridCounts()
	{
		if (m_iCircleGridCounts<=0)
		{
			m_iCircleGridCounts = 1;
		}

		if (m_iCircleGridCounts > POLORAXIS_AXISCOUNT) 
		{
			m_iCircleGridCounts = POLORAXIS_AXISCOUNT;	
		}
	}
	
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
	void	SetCircleUnitValue(double fUnitVal[POLORAXIS_AXISCOUNT]);	//设置幅值坐标的幅值
	int 	GetCircleUnitValue(double fUnitVal[POLORAXIS_AXISCOUNT]);	//获得幅值坐标的幅值，返回幅值坐标的个数
	
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

	//2022-5-14  lijunqing
	void   DrawTheVector(CDC *pDC, int iCircleUnitIndex, POLAR_VECTOR *pVector);
	void   DrawTheVector(CDC *pDC, POLAR_VECTORS *pVectors);
	void   DrawTheVector(CDC *pDC, POLAR_VECTORS_MNGR *pVectorsMngr);
	
	void	DrawCircle(CDC *pDC,int iCircleUnitIndex,double *pfRadius,long nCircles,COLORREF crCircle,long nLineStype=PS_SOLID,long lLineWidth=1);
	
	void	DrawAngleUnit(CDC*pDC);	//绘制角度刻度
	void	DrawCircleUnit(CDC*pDC);//绘制幅值刻度
	void	DrawAxisCenter(CDC*pDC);//绘制中心轴
	
	virtual void	LogicPointToDevicePoint(double fRadius,double fAngle,CPoint *pPoint,long iCircleUnitIndex=0);	//将逻辑坐标转化为实际坐标
	virtual void	DevicePointToLogicPoint(const CPoint &point,double *fRadius,double *fAngle,long iCircleUnitIndex=0);//从实际坐标获取实际坐标所代表的值
    virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex=0);
    virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex=0);
    virtual void GetAxisDrawArea(CRect &rcArea);
    virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);

	void ResetRuler();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	//##############################接口定义#####################################################
public:
	//获取坐标系的绘图位置
	long GetPosition(long *left, long *top, long *right, long *bottom);
//	//获取坐标系统的工作区，即坐标系统坐标范围标示的有效区域
//	long GetWorkArea(long *left, long *top, long *right, long *bottom);
//	//将逻辑坐标转化为设备坐标:ptx,pty为设备坐标
//	long LogicPointToDevicePoint(double x,double y,long *ptx,long *pty);
//	//将设备坐标转化为逻辑坐标:ptx,pty为设备坐标
//	long DevicePointToLogicPoint (long ptx,long pty ,double *x,double *y);

	//坐标系统的绘制类型,2005.08.12添加
	long SetAxisDrawStyle(long nValue)		{		m_lAxisDrawStyle = nValue;	return m_lAxisDrawStyle;	}
	long GetAxisDrawStyle(long *nValue)		{		return m_lAxisDrawStyle;			}
	long SetAxisDrawStyleBit(long nValue);
	long ClearAxisDrawStyleBit(long nValue);
	
	//坐标轴标题及其字体、颜色
    long SetAxisTitle(const CString &bstrValue)  {   m_strPolarAxisTitle = bstrValue;  return 0;   }
	CString GetAxisTitle()                       {   return m_strPolarAxisTitle;     }
	long SetAxisTitleFont(LOGFONT lfFont);
	LOGFONT GetAxisTitleFont();
	long SetAxisTitleFontColor(long nValue);
	long GetAxisTitleFontColor(long *nValue);
	
	//坐标系统的背景色
	long SetAxisBackColor(long nValue);
	long GetAxisBackColor(long *nValue);
	//坐标系统工作区颜色
	long SetWorkAreaBkColor(long nValue);
	long GetWorkAreaBkColor(long *nValue);
	//坐标系统边框的颜色
	long SetFrameLeftTopColor(long nValue);
	long GetFrameLeftTopColor(long *nValue);
	long SetFrameRightBottomColor(long nValue);
	long GetFrameRightBottomColor(long *nValue);
	//坐标系统边框边界阴影
	long SetFrameShadow(long nValue);
	long GetFrameShadow(long *nValue);
	
	//角度刻度线的线型、颜色、线宽、字体、字体颜色
	void SetAngleUnitLineStyle(long nValue);
	long GetAngleUnitLineStyle();
	long SetAngleUnitLineColor(long nValue);
	long GetAngleUnitLineColor(long *nValue);
	long SetAngleUnitLineWidth(long nValue);
	long GetAngleUnitLineWidth(long *nValue);
	long SetAngleUnitFont(LOGFONT lfFont);
	LOGFONT GetAngleUnitFont();
	long SetAngleUnitFontColor(long nValue);
	long GetAngleUnitFontColor(long *nValue);
	
	//圆(幅值)刻度线的线型、颜色、线宽
	long SetCircleUnitLineStyle(long nValue);
	long GetCircleUnitLineStyle(long *nValue);
	long SetCircleUnitLineColor(long nValue);
	long GetCircleUnitLineColor(long *nValue);
	long SetCircleUnitLineWidth(long nValue);
	long GetCircleUnitLineWidth(long *nValue);
	
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
	long SetAngleUnitID(long nValue)         {    SetAngleUnit(nValue);  return 0;  };
	long GetAngleUnitID(long *nValue);
	long SetCircleAxisCounts(long nValue);
	long GetCircleAxisCounts(long *nValue);
	long SetCircleUnitValue(double dValue,long nCircleAxisID);
	long GetCircleUnitValue(double *dValue,long nCircleAxisID);
	
	//坐标区域
    inline long SetBorder(long left, long top, long right, long bottom)
	{
		SetPolarAxisBorder(CRect(left, top, right, bottom));
		return 0;
	}
    inline long SetBorder(CRect rcBoder)
	{
		SetPolarAxisBorder(rcBoder);
		return 0;
	}
    long GetBorder(long *left, long *top, long *right, long *bottom);
	long GetWorkArea(long *left, long *top, long *right, long *bottom);
	long SetMarginGap(long nLeftGap, long nTopGap, long nRightGap, long nBottomGap);
	long GetMarginGap(long *nLeftGap, long *nTopGap, long *nRightGap, long *nBottomGap);
	
	//重新计算坐标系统的刻度
	long ResetAxis()       {        ResetPolarAxis();    return 0;   }
	
	//绘图
	void DrawAxis(CDC *pDC)
	{
		DrawIt(pDC);
	}
	long DrawVector(CDC *pDC,long nUnitIndex,double fRadius,double fAngle,const CString &strVectorName,long crVector,long nLineWidth,long nLineStyle,long nArrowLen,long crVectorTitle,float fZoomRatio,long xOffset,long yOffset)
	{
		DrawTheVector(pDC,nUnitIndex, fRadius, fAngle,strVectorName,crVector,nLineWidth,nLineStyle,nArrowLen,crVectorTitle);
		return 0;
	}
	long DrawVectorEx(CDC *pDC,long nUnitIndex,double dRadius1,double dAngle1,double dRadius2,double dAngle2,const CString &strVectorName,long crVector,long nLineWidth,long nLineStyle,long nArrowLen,long crVectorTitle,float fZoomRatio,long xOffset,long yOffset)
	{
		DrawTheVector(pDC, nUnitIndex, dRadius1, dAngle1, dRadius2, dAngle2,strVectorName
			,crVector,nLineWidth,nLineStyle,nArrowLen,crVectorTitle);
		return 0;
	}
	long DrawVectorEx2(CDC *pDC,long nUnitIndex,double dRadius1,double dAngle1,double dRadius2,double dAngle2,double *dRadiusL,double *dAngleL,const CString &strVectorName,long crVector,long nLineWidth,long nLineStyle,long nArrowLen,long crVectorTitle,float fZoomRatio,long xOffset,long yOffset)
	{
		DrawTheVector(pDC, nUnitIndex, dRadius1, dAngle1, dRadius2, dAngle2, dRadiusL, dAngleL
			,strVectorName, crVector, nLineWidth, nLineStyle, nArrowLen, crVectorTitle);
		return 0;
	}
	void GetTheVector(double fRadius1,double fAngle1,double fRadius2,double fAngle2,double *fRadiusL,double *fAngleL);
	long DrawCircle(CDC *pDC,long nUnitIndex,double dRadius,long crCircle,long nLineStype,long nLineWidth,float fZoomRatio,long xOffset,long yOffset)
	{
		CPoint pt(xOffset,yOffset);
		DrawCircle(pDC, nUnitIndex, &dRadius, m_iCircleAxisCount, crCircle, nLineStype, nLineWidth);
	}
	
	//放大缩小
	void ZoomIn(float fRate);
	void ZoomOut(float fRate);
};

#endif // !defined(_POLARAXIS_H__)
