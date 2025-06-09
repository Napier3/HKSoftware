// DescartesAxis.cpp: implementation of the CDescartesAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DescartesAxis.h"

#include "../API/GloblaDrawFunctions.h"
#include "../API/GlobalApi.h"
#include "math.h"

#ifdef DESCARTES_AXIS_POLAR
#include "PowerDrawLine.h"
#include "PowerDrawGrpahList.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BOTTOMADD 2


CDescartesAxis::CDescartesAxis()
{
	m_dAxisWorkMarginRatio = 0.05;
	m_bAxisXYUnitLock = TRUE;
	m_lAxisType = 0;
	m_nMinOneGapWidth = 20;
	m_nMinOneGapHeight = 20;
	m_strAxisTitle = "";
	m_bLockXCarryOneGap = FALSE;
	InitAxis();
	ContinueInitAxis();
}

CDescartesAxis::~CDescartesAxis()
{
	EndXAxisDef();
	EndYAxisDef();
}

long CDescartesAxis::GetXAxisMinSawGapWidth()
{
	return m_nMinOneGapWidth;
}

void CDescartesAxis::SetXAxisMinSawGapWidth(long iXAxisMinSawGapWidth)
{
	m_nMinOneGapWidth=iXAxisMinSawGapWidth;
}
long CDescartesAxis::GetYAxisMinSawGapHeight()
{
	return m_nMinOneGapHeight;
}
void CDescartesAxis::SetYAxisMinSawGapHeight(long iYAxisMinSawGapHeight)
{
	m_nMinOneGapHeight=iYAxisMinSawGapHeight;
}
long CDescartesAxis::GetXAxisType()
{
	return m_lAxisType;
}
void CDescartesAxis::SetXAxisType(long lType)
{
	m_lAxisType=lType;
}


void CDescartesAxis::InitAxis()
{
    m_crAxisBackColor = RGB(240,240,240);//GetSysColor(COLOR_3DFACE);//RGB(240,240,240);
	m_rectWorkArea=CRect(30,5,300,300);
	m_rectXAxis=CRect(30,300,300,320);
	m_rectYAxis=CRect(0,5,30,300);
	m_rectY2Axis=CRect(0,5,30,300);
	m_dXAxisMinVal=0;
	m_dXAxisMaxVal=3269;
	
	m_dXCarryOneGap=1;
	m_dYCarryOneGap=1;
	m_dY2CarryOneGap=1;
	m_fCoefficient = 1.0f;
	
	m_nLeftGap = (long)(5*m_fCoefficient);
	m_nRightGap = (long)(5*m_fCoefficient);
	m_nTopGap = (long)(18*m_fCoefficient);
	m_nBottomGap = (long)(5*m_fCoefficient);
	
	//WorkArea Bk
	m_crWorkAreaBkColor = RGB(0,255,255);
	m_crWorkAreaBorderLeftTopColor = RGB(128,128,128);
	m_crWorkAreaBorderRightBottomColor = RGB(200,200,200);
	m_nWorkAreaBorderShadow = (long)(2*m_fCoefficient);
	m_crFrameLeftTopColor = RGB(128,128,128);
	m_crFrameRightBottomColor = RGB(200,200,200);
	m_nFrameShadow = (long)(2*m_fCoefficient);
	
	m_crXUnitScaleColor=RGB(0,0,0);
	m_crXUnitScaleShadowColor = RGB(255,255,255);
	m_crYUnitScaleColor=RGB(0,0,0);
	m_crYUnitScaleShadowColor=RGB(255,255,255);
	
	m_crAxisTitleFont = RGB(0,0,0);
	m_lfAxisTitleFont = InitLogFont ((long)(-14*m_fCoefficient),0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));

	//VertDef
	m_lfYAxisScaleFont= InitLogFont ((long)(-9*m_fCoefficient),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
	m_lfYAxisNameFont = InitLogFont ((long)(-9*m_fCoefficient),0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
	m_crYAxisScaleFontColor=RGB(0,0,0);
	m_crYAxisNameFontColor=RGB(0,0,0);
	m_lYAxisGridLineStyle=PS_DOT;
    m_crYAxisGridLineColor = RGB(128,128,128);//GetSysColor(COLOR_3DDKSHADOW);
	m_crYAxisTenthScale = RGB(0,0,0);
	m_crXAxisTenthScale = RGB(0,0,0);
	m_nYAxisAreaWidth = (long)(35*m_fCoefficient);
	m_nYAxisUnitScaleLineLen = (long)(15*m_fCoefficient);
	m_nYAxisHalfScaleLineLen = (long)(8*m_fCoefficient);
	m_nYAxisTenthScaleLineLen = (long)(3*m_fCoefficient);

	//HorzDef
	m_lfXAxisScaleFont = m_lfYAxisScaleFont;   //InitLogFont ((long)(-9*m_fCoefficient),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
	m_lfXAxisNameFont  = m_lfYAxisNameFont;    //InitLogFont ((long)(-12*m_fCoefficient),0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Tahoma");
	m_crXAxisScaleFontColor = RGB(0,0,0);
	m_crXAxisNameFontColor = RGB(0,0,0);
	m_lXAxisGridLineStyle = PS_DOT;

#ifndef _PSX_IDE_QT_
    m_crXAxisGridLineColor = GetSysColor(COLOR_3DDKSHADOW);
#else
    m_crXAxisGridLineColor		= RGB(192,192,192);//GetSysColor(COLOR_3DDKSHADOW);	//???????????
#endif

	m_nXAxisAreaHeight = (long)(30*m_fCoefficient);
	m_nXAxisUnitScaleLineLen = (long)(10*m_fCoefficient);
	m_nXAxisHalfScaleLineLen = (long)(8*m_fCoefficient);
	m_nXAxisTenthScaleLineLen = (long)(3*m_fCoefficient);
	
	////////	坐标轴中心轴参数定义
	m_lAxisCenterLineWidth=1;
	m_lAxisCenterLineType = PS_SOLID;
	m_crAxisCenterColor = RGB(0,0,0);
	
	m_lXAxisTextDrawStyle=1;
	m_lAxisDrawStyle=DESCARTESAXISDRAW_ALL;

	m_crYAxisWorkAreaBackColorFrom = m_crXAxisWorkAreaBackColorFrom = RGB( 20, 240, 240);
	m_crYAxisWorkAreaBackColorTo   = m_crXAxisWorkAreaBackColorTo   = RGB(240, 240, 240);

	m_rectBorder=CRect(30,5,300,300);
	m_dXAxisMinVal = 0;
	m_dXAxisMaxVal = 10;
	m_dYAxisMinVal = 0;
	m_dYAxisMaxVal = 10;
	m_dY2AxisMinVal = -5;
	m_dY2AxisMaxVal = 5;
	m_dXAxisOldMinVal = 0;
	m_dXAxisOldMaxVal = 10;
	m_dYAxisOldMinVal = 0;
	m_dYAxisOldMaxVal = 10;
	m_dY2AxisOldMinVal = -5;
	m_dY2AxisOldMaxVal = 5;
	m_bUseY2Axis = FALSE;
	m_dYAxisOneGap = 1;
	m_dXAxisOneGap = 1;
	m_dMaxZoomMultiple = 32;
	m_dOneXGapValue = 1;
	m_dOneYGapValue = 1;
	m_dOneY2GapValue = 1;
	m_ptCenterLogInDv.x = 0;
	m_ptCenterLogInDv.y = 0;
	m_dMaxZoomMultiple = 100.0f;
	m_lXAxisMaxUnitCount = 10;
	m_lYAxisMaxUnitCount = 10;
	m_bUseY2Axis = FALSE;
	
	SetBorder(m_rectBorder);
}

void CDescartesAxis::ContinueInitAxis()
{
	m_cBkGroundBrush=InitLogBrush(BS_SOLID,1,m_crWorkAreaBkColor);
	m_logpenYAxisGridLine=InitLogPen(m_lYAxisGridLineStyle,1,m_crYAxisGridLineColor);
	m_logpenYAxisTenthScale=InitLogPen(PS_SOLID,1,m_crYAxisTenthScale);//m_crYAxisGridLineColor);
	m_logpenXAxisGridLine=InitLogPen(m_lXAxisGridLineStyle,1,m_crXAxisGridLineColor);
	m_logpenXAxisTenthScale=InitLogPen(PS_SOLID,1,m_crXAxisTenthScale);//m_crXAxisGridLineColor);
}

//////////////////////////////////////////////////////////////////////////
//属性的Set、Get方法定义

long CDescartesAxis::ResetAxis()
{
	AdjustAxisDef(m_rectBorder,m_bAxisXYUnitLock);
	return 0;
}

void CDescartesAxis::SetXYAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY, double dMinY2, double dMaxY2)
{
	if (dMaxX - dMinX < 0.001)
	{
		dMaxX = dMinX + 0.1;
	}
	if (dMaxY - dMinY < 0.001)
	{
		dMaxY = dMinY + 0.1;
	}
	if (dMaxY2 - dMinY2 < 0.001)
	{
		dMaxY2 = dMinY2 + 0.1;
	}

	m_dXAxisMinVal = dMinX;
	m_dXAxisMaxVal = dMaxX;
	m_dYAxisMinVal = dMinY;
	m_dYAxisMaxVal = dMaxY;
	m_dY2AxisMinVal = dMinY2;
	m_dY2AxisMaxVal = dMaxY2;
	m_dXAxisOldMinVal = dMinX;
	m_dXAxisOldMaxVal = dMaxX;
	m_dYAxisOldMinVal = dMinY;
	m_dYAxisOldMaxVal = dMaxY;
	m_dY2AxisOldMinVal = dMinY2;
	m_dY2AxisOldMaxVal = dMaxY2;

	AdjustAxisDef(m_rectBorder,m_bAxisXYUnitLock);
}

void CDescartesAxis::GetXYAxisMinMaxVal(double &dMinX,double &dMinY,double &dMaxX,double &dMaxY, double &dMinY2,double &dMaxY2)
{
	dMinX = m_dXAxisMinVal;
	dMaxX = m_dXAxisMaxVal;
	dMinY = m_dYAxisMinVal;
	dMaxY = m_dYAxisMaxVal;
	dMinY2 = m_dY2AxisMinVal;
	dMaxY2 = m_dY2AxisMaxVal;
}
void CDescartesAxis::SetXAxisTextDrawStyle(long lXAxisTextDrawStyle)
{
	m_lXAxisTextDrawStyle = lXAxisTextDrawStyle;
}
long CDescartesAxis::GetXAxisTextDrawStyle()
{
	return m_lXAxisTextDrawStyle;
}
void CDescartesAxis::SetAxisTitleFont(LOGFONT lf)
{
	m_lfAxisTitleFont = lf;
}
LOGFONT CDescartesAxis::GetAxisTitleFont()
{
	return m_lfAxisTitleFont;
}
void CDescartesAxis::SetAxisTitleFontColor(COLORREF color)
{
	m_crAxisTitleFont = color;
}

COLORREF CDescartesAxis::GetAxisTitleFontColor()
{
	return m_crAxisTitleFont;
}
void CDescartesAxis::SetAxisTitle(CString strAxisTitle)
{
	m_strAxisTitle = strAxisTitle;
}
CString CDescartesAxis::GetAxisTitle()
{
	return m_strAxisTitle;
}
CRect CDescartesAxis::GetWorkArea()
{
	return m_rectWorkArea;
}
void CDescartesAxis::SetAxisBackColor(COLORREF color)
{
	m_crAxisBackColor = color;
}

COLORREF CDescartesAxis::GetAxisBackColor()
{
	return m_crAxisBackColor;
}

void CDescartesAxis::SetWorkAreaBkColor(COLORREF color)
{
	m_crWorkAreaBkColor = color;
	m_cBkGroundBrush = InitLogBrush(BS_SOLID,1,m_crWorkAreaBkColor);
}
COLORREF CDescartesAxis::GetWorkAreaBkColor()
{
	return m_crWorkAreaBkColor;
}
void CDescartesAxis::SetWorkAreaBorderLeftTopColor(COLORREF color)
{
	m_crWorkAreaBorderLeftTopColor = color;
}
COLORREF CDescartesAxis::GetWorkAreaBorderLeftTopColor()
{
	return m_crWorkAreaBorderLeftTopColor;
}
void CDescartesAxis::SetWorkAreaBorderRightBottomColor(COLORREF color)
{
	m_crWorkAreaBorderRightBottomColor = color;
}
COLORREF CDescartesAxis::GetWorkAreaBorderRightBottomColor()
{
	return m_crWorkAreaBorderRightBottomColor;
}
void CDescartesAxis::SetWorkAreaBorderShadow(long lWorkAreaBorderShadow)
{
	m_nWorkAreaBorderShadow = lWorkAreaBorderShadow;
}
long CDescartesAxis::GetWorkAreaBorderShadow()
{
	return m_nWorkAreaBorderShadow;
}

void CDescartesAxis::SetFrameLeftTopColor(COLORREF color)
{
	m_crFrameLeftTopColor = color;
}

COLORREF CDescartesAxis::GetFrameLeftTopColor()
{
	return m_crFrameLeftTopColor;
}

void CDescartesAxis::SetFrameRightBottomColor(COLORREF color)
{
	m_crFrameRightBottomColor = color;
}

COLORREF CDescartesAxis::GetFrameRightBottomColor()
{
	return m_crFrameRightBottomColor;
}

void CDescartesAxis::SetFrameShadow(long lWorkAreaBorderShadow)
{
	m_nFrameShadow = lWorkAreaBorderShadow;
}

long CDescartesAxis::GetFrameShadow()
{
	return m_nFrameShadow;
}

void CDescartesAxis::SetBorder(CRect rectBorder)
{
	m_rectBorder = rectBorder;
	AdjustAxisDef(m_rectBorder,m_bAxisXYUnitLock);
}

CRect CDescartesAxis::GetBorder()
{
	return m_rectBorder;
}
void CDescartesAxis::SetAxisXYUnitLock(long bXYUnitLock)
{
	m_bAxisXYUnitLock = bXYUnitLock;
}
long CDescartesAxis::GetAxisXYUnitLock()
{
	return m_bAxisXYUnitLock;
}
CRect CDescartesAxis::GetXAxisArea()
{
	return m_rectXAxis;
}
CRect CDescartesAxis::GetYAxisArea()
{
	return m_rectYAxis;
}

//Y Axis
void CDescartesAxis::SetYUnitScaleColor(COLORREF color)
{
	m_crYUnitScaleColor = color;
}	
COLORREF CDescartesAxis::GetYUnitScaleColor()
{
	return m_crYUnitScaleColor;
}	
void CDescartesAxis::SetYUnitScaleShadowColor(COLORREF color)
{
	m_crYUnitScaleShadowColor = color;
}	
COLORREF CDescartesAxis::GetYUnitScaleShadowColor()
{
	return m_crYUnitScaleShadowColor;
}
void CDescartesAxis::SetYAxisScaleFont(LOGFONT lf)
{
	m_lfYAxisScaleFont = lf;
}
LOGFONT CDescartesAxis::GetYAxisScaleFont()
{
	return m_lfYAxisScaleFont;
}
void CDescartesAxis::SetYAxisNameFont(LOGFONT lf)
{
	m_lfYAxisNameFont = lf;
}
LOGFONT CDescartesAxis::GetYAxisNameFont()
{
	return m_lfYAxisNameFont;
}
void CDescartesAxis::SetYAxisScaleFontColor(COLORREF color)
{
	m_crYAxisScaleFontColor = color;
}
COLORREF CDescartesAxis::GetYAxisScaleFontColor()
{
	return m_crYAxisScaleFontColor;
}
void CDescartesAxis::SetYAxisNameFontColor(COLORREF color)
{
	m_crYAxisNameFontColor = color;
}
COLORREF CDescartesAxis::GetYAxisNameFontColor()
{
	return m_crYAxisNameFontColor;
}
void CDescartesAxis::SetYAxisGridLineStyle(long l)
{
	m_lYAxisGridLineStyle = l;
}
long CDescartesAxis::GetYAxisGridLineStyle()
{
	return m_lYAxisGridLineStyle;
}
void CDescartesAxis::SetYAxisGridLineColor(COLORREF color)
{
	m_crYAxisGridLineColor = color;
	m_logpenYAxisGridLine=InitLogPen(m_lYAxisGridLineStyle,1,m_crYAxisGridLineColor);
}
COLORREF CDescartesAxis::GetYAxisGridLineColor()
{
	return m_crYAxisGridLineColor;
}
void CDescartesAxis::SetYAxisTenthScaleColor(COLORREF color)
{
	m_crYAxisTenthScale = color;
	m_logpenYAxisTenthScale=InitLogPen(PS_SOLID,1,m_crYAxisTenthScale);//m_crYAxisGridLineColor);
}
COLORREF CDescartesAxis::GetYAxisTenthScaleColor()
{
	return m_crYAxisTenthScale;
}
void CDescartesAxis::SetYAxisAreaWidth(long l)
{
	m_nYAxisAreaWidth = l;
}
long CDescartesAxis::GetYAxisAreaWidth()
{
	return m_nYAxisAreaWidth;
}
void CDescartesAxis::SetYAxisUnitScaleLineLen(long l)
{
	m_nYAxisUnitScaleLineLen = l;
}
long CDescartesAxis::GetYAxisUnitScaleLineLen()
{
	return m_nYAxisUnitScaleLineLen;
}
void CDescartesAxis::SetYAxisHalfScaleLineLen(long l)
{
	m_nYAxisHalfScaleLineLen = l;
}
long CDescartesAxis::GetYAxisHalfScaleLineLen()
{
	return m_nYAxisHalfScaleLineLen;
}
void CDescartesAxis::SetYAxisTenthScaleLineLen(long l)
{
	m_nYAxisTenthScaleLineLen = l;
}
long CDescartesAxis::GetYAxisTenthScaleLineLen()
{
	return m_nYAxisTenthScaleLineLen;
}

//X Axis
void CDescartesAxis::SetXUnitScaleColor(COLORREF color)
{
	m_crXUnitScaleColor = color;
}	
COLORREF CDescartesAxis::GetXUnitScaleColor()
{
	return m_crXUnitScaleColor;
}	
void CDescartesAxis::SetXUnitScaleShadowColor(COLORREF color)
{
	m_crXUnitScaleShadowColor = color;
}	
COLORREF CDescartesAxis::GetXUnitScaleShadowColor()
{
	return m_crXUnitScaleShadowColor;
}	

void CDescartesAxis::SetXAxisScaleFont(LOGFONT lf)
{
	m_lfXAxisScaleFont = lf;
}
LOGFONT CDescartesAxis::GetXAxisScaleFont()
{
	return m_lfXAxisScaleFont;
}
void CDescartesAxis::SetXAxisNameFont(LOGFONT lf)
{
	m_lfXAxisNameFont = lf;
}
LOGFONT CDescartesAxis::GetXAxisNameFont()
{
	return m_lfXAxisNameFont;
}
void CDescartesAxis::SetXAxisScaleFontColor(COLORREF color)
{
	m_crXAxisScaleFontColor = color;
}
COLORREF CDescartesAxis::GetXAxisScaleFontColor()
{
	return m_crXAxisScaleFontColor;
}
void CDescartesAxis::SetXAxisNameFontColor(COLORREF color)
{
	m_crXAxisNameFontColor = color;
}
COLORREF CDescartesAxis::GetXAxisNameFontColor()
{
	return m_crXAxisNameFontColor;
}
void CDescartesAxis::SetXAxisGridLineStyle(long l)
{
	m_lXAxisGridLineStyle = l;
}
long CDescartesAxis::GetXAxisGridLineStyle()
{
	return m_lXAxisGridLineStyle;
}
void CDescartesAxis::SetXAxisGridLineColor(COLORREF color)
{
	m_crXAxisGridLineColor = color;
	m_logpenXAxisGridLine=InitLogPen(m_lXAxisGridLineStyle,1,m_crXAxisGridLineColor);
}
COLORREF CDescartesAxis::GetXAxisGridLineColor()
{
	return m_crXAxisGridLineColor;
}
void CDescartesAxis::SetXAxisTenthScaleColor(COLORREF color)
{
	m_crXAxisTenthScale = color;
	m_logpenXAxisTenthScale=InitLogPen(PS_SOLID,1,m_crXAxisTenthScale);//m_crXAxisGridLineColor);
}
COLORREF CDescartesAxis::GetXAxisTenthScaleColr()
{
	return m_crXAxisTenthScale;
}
void CDescartesAxis::SetXAxisAreaHeight(long l)
{
	m_nXAxisAreaHeight = l;
}
long CDescartesAxis::GetXAxisAreaHeight()
{
	return m_nXAxisAreaHeight;
}
void CDescartesAxis::SetXAxisUnitScaleLineLen(long l)
{
	m_nXAxisUnitScaleLineLen = l;
}
long CDescartesAxis::GetXAxisUnitScaleLineLen()
{
	return m_nXAxisUnitScaleLineLen;
}
void CDescartesAxis::SetXAxisHalfScaleLineLen(long l)
{
	m_nXAxisHalfScaleLineLen = l;
}
long CDescartesAxis::GetXAxisHalfScaleLineLen()
{
	return m_nXAxisHalfScaleLineLen;
}
void CDescartesAxis::SetXAxisTenthScaleLineLen(long l)
{
	m_nXAxisTenthScaleLineLen = l;
}
long CDescartesAxis::GetXAxisTenthScaleLineLen()
{
	return m_nXAxisTenthScaleLineLen;
}

//坐标轴中心轴参数定义
void CDescartesAxis::SetAxisCenterLineWidth(long l)
{
	m_lAxisCenterLineWidth = l;
}
long CDescartesAxis::GetAxisCenterLineWidth()
{
	return m_lAxisCenterLineWidth;
}
void CDescartesAxis::SetAxisCenterLineType(long l)
{
	m_lAxisCenterLineType = l;
}
long CDescartesAxis::GetAxisCenterLineType()
{
	return m_lAxisCenterLineType;
}
void CDescartesAxis::SetAxisCenterColor(COLORREF color)
{
	m_crAxisCenterColor = color;
}
COLORREF CDescartesAxis::GetAxisCenterColor()
{
	return m_crAxisCenterColor;
}

long CDescartesAxis::GetCarryVal(long iVal)
{
	long iStep=1;
	long iStep1=10;
	for (long i=1;;i++)
	{
		if( (iVal >= iStep) && (iVal < iStep1) ) 
			break;
		iStep=iStep1;
		iStep1*=10;
	}
	return iStep;
}

long CDescartesAxis::MakeGapValLegal(float fVal,long &lVal)
{

	long iTmp=(long)fVal;
	if(iTmp==0)
	{
		lVal=1;
		return 1;
	}
	long iMulti=GetCarryVal(iTmp);///进位数值
	long iSet[4]={1,2,5,10};/////////
	long i = 0;

	for (i=0;i<3;i++)
	{
		if ((iTmp>=iMulti*iSet[i])&&(iTmp<iSet[i+1]*iMulti))
		{
			lVal=iMulti*iSet[i];
			return iSet[i+1]*iMulti;
		}
	}
	return iSet[i+1]*iMulti;
}

///////////////////
double CDescartesAxis::GetBeginVal(double lNowVal, double lGapVal)//得到整数倍一个Gap的lNowVal值
{
	double ff,ff1;
	long iMul=1;
	ff = lNowVal / lGapVal;
	ff1=(double)((long)ff);

	if(ff-ff1<0.99)	
		iMul=(long)ff;
	else
		iMul=(long)ff+1;

	double fb=0;
	fb = lNowVal - (lNowVal - iMul*lGapVal);

	return fb;
}
/***********************************************************************
关于Y轴的绘制
***********************************************************************/
long CDescartesAxis::GetBaseOneGapHeight()
{
	return m_nMinOneGapHeight;
}
long CDescartesAxis::GetMinOneGapHeight()
{
	return m_nMinOneGapHeight;
}

void CDescartesAxis::InitYAxisDef()
{
	m_listYAxisScale.DeleteAll();
	m_listY2AxisScale.DeleteAll();
}
void CDescartesAxis::EndYAxisDef()
{
	m_listYAxisScale.DeleteAll();
	m_listY2AxisScale.DeleteAll();
}

void CDescartesAxis::SetYAxisName(CString strYAxisName)
{
	m_strYAxisName = strYAxisName;
}
CString CDescartesAxis::GetYAxisName()
{	
	return m_strYAxisName;
}
void CDescartesAxis::SetY2AxisName(CString strYAxisName)
{
	m_strY2AxisName = strYAxisName;
}
CString CDescartesAxis::GetY2AxisName()
{	
	return m_strY2AxisName;
}

void CDescartesAxis::ResetYAxisDef()
{
	EndYAxisDef();
	long iOneGapPt = GetBaseOneGapHeight();//得到基本的一个Gap的间距
	long iHeight = m_rectYAxis.Height();//得到整个工作区域的高度

	//得到需要计算数据的间隔
	double dYAxisRangeVal = m_dYAxisMaxVal-m_dYAxisMinVal;
	double dGapNum = iHeight/iOneGapPt;

	if (iHeight<10) 
		return;

	if (dGapNum<=0.0001)
		return ;

	if (dGapNum > GetYAxisMaxUnitCount())
		dGapNum = GetYAxisMaxUnitCount();////获得最大间隔数(最大刻度数)

	double dAxisUnitGapVal = dYAxisRangeVal/dGapNum;//得到每个间隔的数值

	double dLegalGapVal=0;
	double dGapVal=0;
	long iGapNumTemp=0;
	long iCircleCounts=0;
	
	for(;iCircleCounts<50;iCircleCounts++)
	{
		dLegalGapVal=MakeFloatGapValLegal(dAxisUnitGapVal,dGapVal);//得到最可能的Mv数
		dGapNum=dYAxisRangeVal/dGapVal;		////最大可能的间隔数
		iGapNumTemp=FloatValToInt(dGapNum);
		dGapNum=FloatValToInt(dGapNum);//iGapNumTemp < dGapNum ? iGapNumTemp+1 : dGapNum;
		long iNowGapPt=(long)(iHeight/dGapNum);	////最小可能的每个间隔值
		////最小可能的每个间隔值 < 允许的最小可能的间隔值

		if(iNowGapPt<GetMinOneGapHeight())
			dGapVal=dLegalGapVal;//得到最后的Mv数

		dGapNum=dYAxisRangeVal/dGapVal;
		iGapNumTemp=FloatValToInt(dGapNum);
		dGapNum=iGapNumTemp ;
		
		if(iGapNumTemp>GetYAxisMaxUnitCount())/////间隔数大于最大允许的间隔数
		{
			dGapVal=dLegalGapVal;
			if(iGapNumTemp>GetYAxisMaxUnitCount())
			{
				dGapNum=(float)GetYAxisMaxUnitCount();
				dAxisUnitGapVal=(float)dLegalGapVal;
				continue;
			}
		}
		break;
	}	

	if (iGapNumTemp==0)iGapNumTemp=1;
	long iNowGapPt=iHeight/iGapNumTemp;

	if (iNowGapPt==0)
		iNowGapPt=1;

	if(iNowGapPt<GetMinOneGapHeight())dGapVal=dLegalGapVal;//得到最后的Mv数
	dGapNum=dYAxisRangeVal/dGapVal;
	iGapNumTemp=FloatValToInt(dGapNum);
	
	if(iGapNumTemp>GetYAxisMaxUnitCount())
	{
		dGapVal=dLegalGapVal;
		dGapNum=dYAxisRangeVal/dGapVal;
		iGapNumTemp=FloatValToInt(dGapNum);
	}
	
	double iBeginVal=GetBeginVal(m_dYAxisMinVal,dGapVal);

	GetOneYAxisHeight(dGapVal,1);

	for (long i=0;i<=iGapNumTemp;i++)
	{
		ResetOneYAxisDef(iBeginVal+i*dGapVal);
	}

	m_dYCarryOneGap=dGapVal;

	if (m_bUseY2Axis)
	{
		ResetY2AxisDef();
	}
}

void CDescartesAxis::ResetY2AxisDef()
{
	long nYScaleCount = m_listYAxisScale.GetCount();

	if (nYScaleCount == 0)
	{
		return ;
	}

	double dY2ValRange = m_dY2AxisMaxVal - m_dY2AxisMinVal;
	dY2ValRange = dY2ValRange * (nYScaleCount+2) / nYScaleCount;
	double dY2SacleVal = dY2ValRange / nYScaleCount;
	double dY2SacleUnit = dY2ValRange / nYScaleCount;
	double dY2SacleHigh = MakeFloatGapValLegal(dY2SacleVal, dY2SacleUnit);
	
	POS pos = m_listYAxisScale.GetHeadPosition();
	CAxisScaleData *pData = NULL;
	CAxisScaleData *pNew = NULL;
	double dBeginVal = GetBeginVal(m_dY2AxisMinVal, dY2SacleUnit);
	double dValue = dBeginVal;
	
	while (pos != NULL)
	{
		pData = m_listYAxisScale.GetNext(pos);
		pNew  = pData->Clone();
		pNew->m_dAxisScaleVal = dValue;
		pNew->m_ptAxisScale.x = m_rectY2Axis.left;
		dValue += dY2SacleUnit;
		m_listY2AxisScale.AddNode(pNew);

		//TRACE("Scale: %.3f\t\t%.3f\n", pData->m_dAxisScaleVal, pNew->m_dAxisScaleVal);
	}

	m_dY2CarryOneGap = dY2SacleUnit;
}

void CDescartesAxis::GetOneYAxisHeight(double iGap,BYTE bKind)
{
	long iHeight=m_rectYAxis.Height();
	double iVal=m_dYAxisMaxVal-m_dYAxisMinVal;
	m_dYAxisOneGap=(long)(iGap*(double)iHeight/iVal);
}

void CDescartesAxis::ResetOneYAxisDef(double lVal)
{
	long iHeight = m_rectYAxis.Height();
	double iVal = m_dYAxisMaxVal - m_dYAxisMinVal;
	double f = m_rectYAxis.bottom - (lVal - m_dYAxisMinVal ) * m_dOneYGapValue;
	long y = FloatValToInt(f);
	CAxisScaleData *pScaleData=new CAxisScaleData();
    pScaleData->FillIt(lVal,m_rectYAxis.right,y);
	m_listYAxisScale.AddNode(pScaleData);
}

void CDescartesAxis::DrawYAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio,CPoint ptOffset)
{
	CPoint pt;
	pt.x = m_rectWorkArea.left ;
	pt.y = pScaleData->m_ptAxisScale.y ;
	pt.Offset(ptOffset);
	pDC->MoveTo(pt);

	pt.x = m_rectWorkArea.right ;
	pt.y = pScaleData->m_ptAxisScale.y ;
	pt.Offset(ptOffset);
	pDC->LineTo(pt);
}

void CDescartesAxis::DrawYAxisText(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio,CPoint ptOffset)
{
	char pszString[128];
	_ChopFloatString(pScaleData->m_dAxisScaleVal, pszString);

	LOGFONT lf = m_lfYAxisScaleFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lHeight = abs(lf.lfHeight);

	CRect rect;
	rect.left = m_rectYAxis.left;
	rect.top = pScaleData->m_ptAxisScale.y-lHeight;
	rect.right = m_rectYAxis.right-(long)(fZoomRatio*m_nYAxisUnitScaleLineLen);
	rect.bottom = pScaleData->m_ptAxisScale.y+lHeight;
	rect.OffsetRect(ptOffset);

	CmDrawTextRect(pDC,CString(pszString),m_crYAxisScaleFontColor,
			&rect,RGB(0,0,0),lf,
			TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}

void CDescartesAxis::DrawY2AxisText(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio,CPoint ptOffset)
{
	char pszString[128];
	_ChopFloatString(pScaleData->m_dAxisScaleVal, pszString);
	
	LOGFONT lf = m_lfYAxisScaleFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lHeight = abs(lf.lfHeight);
	
	CRect rect;
	rect.right = m_rectY2Axis.right;
	rect.top = pScaleData->m_ptAxisScale.y-lHeight;
	rect.left = m_rectY2Axis.left+(long)(fZoomRatio*m_nYAxisUnitScaleLineLen);
	rect.bottom = pScaleData->m_ptAxisScale.y+lHeight;
	rect.OffsetRect(ptOffset);
	
	CmDrawTextRect(pDC,CString(pszString),m_crYAxisScaleFontColor,
		&rect,RGB(0,0,0),lf,
		TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}

void CDescartesAxis::DrawYAxisName(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rect;
	LOGFONT lf = m_lfYAxisNameFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lfWidth = GetCharWidthByLogfont2(pDC,lf);

	rect.left=m_rectYAxis.left;
	rect.top=m_rectBorder.top/*+m_nTopGap*/;//2023.6.3 yzj 顶部显示不添加m_nTopGap
	rect.right=rect.left + lfWidth * m_strYAxisName.GetLength();
	rect.bottom=m_rectBorder.top + (long)(fZoomRatio * m_nTopGap);
	rect.OffsetRect(ptOffset);

	CmDrawTextRect(pDC,m_strYAxisName,m_crYAxisNameFontColor,
				   &rect,RGB(0,0,0),lf,
				   TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}

void CDescartesAxis::DrawY2AxisName(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rect;
	LOGFONT lf = m_lfYAxisNameFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lfWidth = GetCharWidthByLogfont2(pDC,lf);
	
/*
	rect.left=m_rectY2Axis.left;
	rect.top=m_rectBorder.top+m_nTopGap;
	rect.right=rect.left + lfWidth * m_strY2AxisName.GetLength();
	rect.bottom=m_rectBorder.top + (long)(fZoomRatio * m_nTopGap);
*/
	rect.right=m_rectY2Axis.right;
	rect.top=m_rectBorder.top+m_nTopGap;
	rect.left=m_rectY2Axis.right - lfWidth * m_strY2AxisName.GetLength();
	rect.bottom = m_rectBorder.top + (long)(fZoomRatio * m_nTopGap);
	rect.OffsetRect(ptOffset);
	
	CmDrawTextRect(pDC,m_strY2AxisName,m_crYAxisNameFontColor,
		&rect,RGB(0,0,0),lf,
		TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}

void CDescartesAxis::DrawYAxis(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	long iNum=m_listYAxisScale.GetCount();
	if(iNum<=0)
		return;
	CPen pen;
	m_logpenYAxisGridLine=InitLogPen(m_lYAxisGridLineStyle,1,m_crYAxisGridLineColor);
	long lGap=(long)(abs(m_lfYAxisScaleFont.lfHeight)*1.5 * fZoomRatio);
	pen.CreatePenIndirect(&m_logpenYAxisGridLine);
	CPen *cOldP=pDC->SelectObject(&pen);
	for (long i=0;i<iNum;i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData*)m_listYAxisScale.GetAt(i);

		if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_LINE)
		{
			if ((pScaleData->m_ptAxisScale.y>m_rectWorkArea.top)&&
				(pScaleData->m_ptAxisScale.y<m_rectWorkArea.bottom))
			{
				DrawYAxisLine(pDC,pScaleData,fZoomRatio,ptOffset);//网格
			}
		}
	}

	pDC->SelectObject(cOldP);
	pen.DeleteObject();

	for (long i=0;i<iNum;i++)//zhouhj 20210203 将标注和网格分开，不然会影响正常绘图
	{
		CAxisScaleData *pScaleData=(CAxisScaleData*)m_listYAxisScale.GetAt(i);
		if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_SCALETEXT)
		{
			if(pScaleData->m_ptAxisScale.y>=m_rectYAxis.top && pScaleData->m_ptAxisScale.y<=m_rectYAxis.bottom)
			{	
				DrawYAxisText(pDC,pScaleData,fZoomRatio,ptOffset);////标注
			}
		}
	}

	if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_HALFSCCALE)
	{
		DrawYSawtooth(pDC,0,fZoomRatio,ptOffset);
	}
	if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_TENTHSCALE)
	{
		DrawYSawtooth(pDC,1,fZoomRatio,ptOffset);
	}
}

void CDescartesAxis::DrawY2Axis(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	long iNum=m_listY2AxisScale.GetCount();
	if(iNum<=0)
		return;

	CPen pen;
	m_logpenYAxisGridLine = InitLogPen(m_lYAxisGridLineStyle,1,m_crYAxisGridLineColor);
	long lGap=(long)(abs(m_lfYAxisScaleFont.lfHeight)*1.5 * fZoomRatio);
	pen.CreatePenIndirect(&m_logpenYAxisGridLine);
	CPen *cOldP=pDC->SelectObject(&pen);

	for (long i=0;i<iNum;i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData*)m_listY2AxisScale.GetAt(i);
		if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_SCALETEXT)
		{
			if(pScaleData->m_ptAxisScale.y>=m_rectY2Axis.top && pScaleData->m_ptAxisScale.y<=m_rectY2Axis.bottom)
			{	
				DrawY2AxisText(pDC,pScaleData,fZoomRatio,ptOffset);////标注
			}
		}
//		if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_LINE)
//		{
//			if ((pScaleData->m_ptAxisScale.y>m_rectWorkArea.top)&&
//				(pScaleData->m_ptAxisScale.y<m_rectWorkArea.bottom))
//			{
//				DrawYAxisLine(pDC,pScaleData,fZoomRatio,ptOffset);//网格
//			}
//		}
	}

	pDC->SelectObject(cOldP);
	pen.DeleteObject();
	
	if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_HALFSCCALE)
	{
		DrawY2Sawtooth(pDC,0,fZoomRatio,ptOffset);
	}

	if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_TENTHSCALE)
	{
		DrawY2Sawtooth(pDC,1,fZoomRatio,ptOffset);
	}
}

///////////////靠工作区内的小锯齿
void CDescartesAxis::DrawOneYSawtooth(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{
	CPen pen;
	pen.CreatePenIndirect(&m_logpenYAxisTenthScale);
	CPen *cOldP=pDC->SelectObject(&pen);
	for (long i=0;i<10;i++)
	{
		long iGapVal=FloatValToInt((float)((float)m_dYAxisOneGap/10.0*i));
		CPoint cPt(cBegin.x,cBegin.y - iGapVal);
		if ( (cPt.y < m_rectYAxis.top) || (cPt.y>m_rectYAxis.bottom) )
			continue;
		cPt.Offset(ptOffset);
		pDC->MoveTo(cPt.x-1,cPt.y);
		pDC->LineTo(cPt.x-(long)(fZoomRatio*m_nYAxisTenthScaleLineLen),cPt.y);
	}
	pDC->SelectObject(cOldP);
	pen.DeleteObject();
}

void CDescartesAxis::DrawOneY2Sawtooth(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{
	CPen pen;
	pen.CreatePenIndirect(&m_logpenYAxisTenthScale);
	CPen *cOldP=pDC->SelectObject(&pen);

	for (long i=0;i<10;i++)
	{
		long iGapVal=FloatValToInt((float)((float)m_dYAxisOneGap/10.0*i));
		CPoint cPt(cBegin.x, cBegin.y - iGapVal);

		if ( (cPt.y < m_rectY2Axis.top) || (cPt.y>m_rectY2Axis.bottom) )
			continue;

		cPt.Offset(ptOffset);
		pDC->MoveTo(cPt.x+1,cPt.y);
		pDC->LineTo(cPt.x+(long)(fZoomRatio*m_nYAxisTenthScaleLineLen),cPt.y);
	}

	pDC->SelectObject(cOldP);
	pen.DeleteObject();
}
///////////////大刻度
void CDescartesAxis::DrawOneYSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{
	long iLen[2]={0,0};
	iLen[0] = (long)(fZoomRatio * m_nYAxisUnitScaleLineLen);
	iLen[1] = (long)(fZoomRatio *m_nYAxisHalfScaleLineLen);

	for (long i=0; i<2;i++)
	{
		long iGapVal=FloatValToInt((float)((float)m_dYAxisOneGap/2.0*i));
		CPoint cPt(cBegin.x,cBegin.y-iGapVal);

		if( (cPt.y < (long)(fZoomRatio*m_rectYAxis.top)) || (cPt.y>(long)(fZoomRatio*m_rectYAxis.bottom)) )
			continue;
		
		cPt.Offset(ptOffset);
		DrawShadowHorzLine(pDC,cPt.x,cPt.y,iLen[i],m_crYUnitScaleColor,m_crYUnitScaleShadowColor);
	}
}

void CDescartesAxis::DrawOneY2SawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{
	long iLen[2]={0,0};
	iLen[0] = -(long)(fZoomRatio * m_nYAxisUnitScaleLineLen);
	iLen[1] = -(long)(fZoomRatio *m_nYAxisHalfScaleLineLen);

	for (long i=0; i<2;i++)
	{
		long iGapVal=FloatValToInt((float)((float)m_dYAxisOneGap/2.0*i));
		CPoint cPt(cBegin.x,cBegin.y-iGapVal);

		if( (cPt.y < (long)(fZoomRatio*m_rectY2Axis.top)) || (cPt.y>(long)(fZoomRatio*m_rectY2Axis.bottom)) )
			continue;
		
		cPt.Offset(ptOffset);
		DrawShadowHorzLine(pDC,cPt.x,cPt.y,iLen[i],m_crYUnitScaleColor,m_crYUnitScaleShadowColor, 1);
	}
}

void CDescartesAxis::DrawYSawtooth(CDC *pDC,BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;
	for (long i=0;i<m_listYAxisScale.GetCount();i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listYAxisScale.GetAt(i);
		if (i==0)
		{
			cBegin=CPoint(pScaleData->m_ptAxisScale.x,(long)(pScaleData->m_ptAxisScale.y+m_dYAxisOneGap));
			cEnd=pScaleData->m_ptAxisScale;

			//最小值到第一个刻度间的小刻度
			CPen pen;
			pen.CreatePenIndirect(&m_logpenYAxisTenthScale);
			CPen *cOldP=pDC->SelectObject(&pen);

			for (long i=0;i<10;i++)
			{
				long iGapVal=FloatValToInt((float)((float)m_dYAxisOneGap/10.0*i));
				CPoint cPt(cBegin.x,cEnd.y+iGapVal);
				
				if((cPt.y < m_rectYAxis.top)||(cPt.y > m_rectYAxis.bottom))
					continue;
				
				cPt.Offset(ptOffset);
				pDC->MoveTo(cPt.x-1,cPt.y);
				pDC->LineTo(cPt.x - (long)(fZoomRatio * m_nYAxisTenthScaleLineLen),cPt.y);
			}
			
			pDC->SelectObject(cOldP);
			pen.DeleteObject();
			continue;
		}
		else
		{
			CAxisScaleData *odNewData=(CAxisScaleData *)m_listYAxisScale.GetAt(i-1);
			cBegin=odNewData->m_ptAxisScale;
			cEnd=pScaleData->m_ptAxisScale;
		}
		
		if (bKind==0)
		{	
			DrawOneYSawtooth(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		}
		else
		{	
			DrawOneYSawtoothShadow(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		}
	}
	
	if(m_listYAxisScale.GetCount()>=2)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listYAxisScale.GetTail();
		cEnd=CPoint(pScaleData->m_ptAxisScale.x,(long)(pScaleData->m_ptAxisScale.y-m_dYAxisOneGap));
		cBegin=pScaleData->m_ptAxisScale;

		if (bKind==0)
		{
			DrawOneYSawtooth(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		}
		else 
		{
			DrawOneYSawtoothShadow(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		}
	}
	
}

void CDescartesAxis::DrawY2Sawtooth(CDC *pDC, BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;

	for (long i=0;i<m_listY2AxisScale.GetCount();i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listY2AxisScale.GetAt(i);

		if (i==0)
		{
			cBegin = CPoint(pScaleData->m_ptAxisScale.x,(long)(pScaleData->m_ptAxisScale.y+m_dXAxisOneGap));

			cEnd=pScaleData->m_ptAxisScale;
			{
				CPen pen;
				pen.CreatePenIndirect(&m_logpenYAxisTenthScale);
				CPen *cOldP=pDC->SelectObject(&pen);
				
				for (long i=0;i<10;i++)
				{
					long iGapVal=FloatValToInt((float)((float)m_dYAxisOneGap/10.0*i));
					CPoint cPt(cBegin.x,cEnd.y+iGapVal);

					if((cPt.y < m_rectY2Axis.top)||(cPt.y > m_rectY2Axis.bottom))
						continue;

					cPt.Offset(ptOffset);
					pDC->MoveTo(cPt.x+1,cPt.y);
					pDC->LineTo(cPt.x + (long)(fZoomRatio * m_nYAxisTenthScaleLineLen),cPt.y);
				}

				pDC->SelectObject(cOldP);
				pen.DeleteObject();
				continue;
			}
		}
		else
		{
			CAxisScaleData *odNewData=(CAxisScaleData *)m_listY2AxisScale.GetAt(i-1);
			cBegin=odNewData->m_ptAxisScale;
			cEnd=pScaleData->m_ptAxisScale;
		}

		if (bKind==0)
		{	
			DrawOneY2Sawtooth(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		}
		else
		{	
			DrawOneY2SawtoothShadow(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		}
	}
	
	if(m_listY2AxisScale.GetCount()>=2)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listY2AxisScale.GetTail();
		cEnd=CPoint(pScaleData->m_ptAxisScale.x,(long)(pScaleData->m_ptAxisScale.y-m_dYAxisOneGap));
		cBegin=pScaleData->m_ptAxisScale;
		
		if (bKind==0)
		{
			DrawOneY2Sawtooth(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		}
		else 
		{
			DrawOneY2SawtoothShadow(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		}
	}
}

/***********************************************************************
关于X轴的绘制
***********************************************************************/
long CDescartesAxis::GetBaseOneGapWidth()
{
	return m_nMinOneGapWidth;
}

long CDescartesAxis::GetMinOneGapWidth()
{
	return m_nMinOneGapWidth;
}

void CDescartesAxis::InitXAxisDef()
{
	m_listXAxisScale.DeleteAll();
}

void CDescartesAxis::EndXAxisDef()
{
	m_listXAxisScale.DeleteAll();
}


long CDescartesAxis::Get60CarryVal(long iVal)
{
	long iStep=6;
	long iStep1=60;
	if (iVal < iStep)
	{
		return iStep;
	}
	for (long i=1;;i++)
	{
		if( (iVal >= iStep) && (iVal < iStep1) ) 
			break;
		iStep=iStep1;
		iStep1*=10;
	}
	return iStep;
}
double CDescartesAxis::GetXBeginVal(double lNowVal,double lGapVal)
{
	double ff,ff1;
	long iMul=1;
	ff=lNowVal/lGapVal;
	ff1=(float)((long)ff);
	if(ff-ff1<0.99)
		iMul=(long)ff1;
	else
		iMul=(long)ff1+1;
	double fb=0;
	fb=lNowVal-(lNowVal - iMul*lGapVal);
	return fb;
}

void CDescartesAxis::LockXCarryOneGap(BOOL bLock, double dXCarryOneGap)
{
	m_bLockXCarryOneGap = bLock;
	m_dXCarryOneGap = dXCarryOneGap;
}

void CDescartesAxis::ResetXAxisDef()
{
	EndXAxisDef();

	if (m_bLockXCarryOneGap)
	{
		double dGapVal = m_dXCarryOneGap;
		double dGapNum = (m_dXAxisMaxVal - m_dXAxisMinVal) / dGapVal;
		int iGapNumTemp = FloatValToInt(dGapNum);;

		double iBeginVal=GetXBeginVal(m_dXAxisMinVal,dGapVal);
		GetOneXAxisWidth(dGapVal,1);
		for (long i=0;i<=iGapNumTemp;i++)
			ResetOneXAxisDef(iBeginVal+i*dGapVal);

		return;
	}

	long iOneGapPt=GetBaseOneGapWidth();//得到基本的一个Gap的间距
	long iHeight=m_rectXAxis.Width();//得到整个工作区域的高度
	//得到需要计算数据的间隔
	double dXAxisRangeVal=m_dXAxisMaxVal-m_dXAxisMinVal;
	
	double dGapNum=iHeight/iOneGapPt;
	long iGapNumTemp=0;
	iGapNumTemp=FloatValToInt(dGapNum);
	if(iGapNumTemp>GetXAxisMaxUnitCount())
		dGapNum=(float)GetXAxisMaxUnitCount();////获得最大间隔数
	double dAxisUnitGapVal=dXAxisRangeVal/dGapNum;//得到每个间隔的数值
	if(dGapNum<=0.0001)
		return ;

	double dLegalGapVal=0;
	double dGapVal=0;
	long iCircleCounts=0;
	for(;iCircleCounts<50;iCircleCounts++)
	{
		dLegalGapVal=MakeFloatGapValLegal(dAxisUnitGapVal,dGapVal);//得到最可能的Mv数
		//if(dLegalGapVal>1) break;
		dGapNum=dXAxisRangeVal/dGapVal;		////最大可能的间隔数
		iGapNumTemp=FloatValToInt(dGapNum);
		dGapNum=(float)iGapNumTemp ;
		long iNowGapPt=(long)(iHeight/dGapNum);	////最小可能的每个间隔值
		////最小可能的每个间隔值 < 允许的最小可能的间隔值
		if(iNowGapPt<GetMinOneGapWidth())
			dGapVal=dLegalGapVal;//得到最后的Mv数
		dGapNum=dXAxisRangeVal/dGapVal;
		iGapNumTemp=FloatValToInt(dGapNum);
		dGapNum = (double)iGapNumTemp ;
		if(iGapNumTemp>GetXAxisMaxUnitCount())/////间隔数大于最大允许的间隔数
		{
			dGapVal=dLegalGapVal;
			if(iGapNumTemp>GetXAxisMaxUnitCount())
			{
				dGapNum=(float)GetXAxisMaxUnitCount();
				dAxisUnitGapVal=dLegalGapVal;
				continue;
			}
		}
		break;
	}	

	//	if (dAxisUnitGapVal>=1)
	{
		dLegalGapVal=MakeFloatGapValLegal(dAxisUnitGapVal,dGapVal);//得到最可能的Mv数
		dGapNum=dXAxisRangeVal/dGapVal;
		if (dGapNum==0)dGapNum=1;
		long iNowGapPt=(long)(iHeight/dGapNum);
		if (iNowGapPt==0)iNowGapPt=1;
		if(iNowGapPt<GetMinOneGapWidth())dGapVal=dLegalGapVal;//得到最后的Mv数
		dGapNum=dXAxisRangeVal/dGapVal;
		iGapNumTemp=FloatValToInt(dGapNum);
		if(iGapNumTemp>GetXAxisMaxUnitCount())
		{
			dGapVal=dLegalGapVal;
			dGapNum=dXAxisRangeVal/dGapVal;
			iGapNumTemp=FloatValToInt(dGapNum);
		}
		double iBeginVal=GetXBeginVal(m_dXAxisMinVal,dGapVal);
		GetOneXAxisWidth(dGapVal,1);
		for (long i=0;i<=iGapNumTemp;i++)
			ResetOneXAxisDef(iBeginVal+i*dGapVal);
	}

	m_dXCarryOneGap=dGapVal;
}

void CDescartesAxis::SetXAxisName(CString strXAxisName)
{
	m_strXAxisName = strXAxisName;
}
CString CDescartesAxis::GetXAxisName()
{
	return m_strXAxisName;
}

void CDescartesAxis::GetOneXAxisWidth(double iGap,BYTE bKind)
{
	long iWidth=m_rectXAxis.Width();
	double iVal=(m_dXAxisMaxVal-m_dXAxisMinVal);
	m_dXAxisOneGap=iGap*(float)iWidth/iVal;
}

void CDescartesAxis::ResetOneXAxisDef(double lVal)
{
	long iWidth=m_rectXAxis.Width();
	double iVal=(m_dXAxisMaxVal-m_dXAxisMinVal);//FloatValToInt
	double f=m_rectXAxis.left+(lVal-m_dXAxisMinVal)*(float)iWidth/iVal;
	long x=FloatValToInt(f);
	CAxisScaleData *pScaleData=new CAxisScaleData();
	long iIntegeralBeginPalace=0;//GetIntegeralBeginPalace();
	f=lVal-iIntegeralBeginPalace;
    pScaleData->FillIt(f,x,m_rectXAxis.top+BOTTOMADD);
	m_listXAxisScale.AddNode(pScaleData);
}

void CDescartesAxis::DrawXAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio,CPoint ptOffset)
{
	CPoint pt;
//	pt.x = (long)(fZoomRatio * pScaleData->m_ptAxisScale.x);
//	pt.y = (long)(fZoomRatio * (m_rectWorkArea.top+m_nWorkAreaBorderShadow) );
	pt.x = pScaleData->m_ptAxisScale.x;
	pt.y = m_rectWorkArea.top + (long)(fZoomRatio * m_nWorkAreaBorderShadow) ;
	pt.Offset(ptOffset);
	pDC->MoveTo(pt);

//	pt.x = (long)(fZoomRatio * pScaleData->m_ptAxisScale.x);
//	pt.y = (long)(fZoomRatio * (m_rectWorkArea.bottom+BOTTOMADD) );
	pt.x = pScaleData->m_ptAxisScale.x;
	pt.y = m_rectWorkArea.bottom + (long)(fZoomRatio * BOTTOMADD);
	pt.Offset(ptOffset);
	pDC->LineTo(pt);
}

CRect  CDescartesAxis::DrawXAxisText(CDC *pDC,CAxisScaleData *pScaleData,BOOL bAddUint,BOOL bReallyDraw,float fZoomRatio,CPoint ptOffset)
{
	//char pszString[128];
	CString strText;
	strText.Format(_T("%f"), pScaleData->m_dAxisScaleVal);
	//_ChopFloatString(pScaleData->m_dAxisScaleVal, pszString, 4);
	ChopFloatString(strText, -1);
	
	if(m_lAxisType==1)
	{
		strText += GetTimeVal((float)pScaleData->m_dAxisScaleVal);
	}
	
	if(bAddUint==TRUE)
	{
		strText += m_strXAxisName;
	}

	CRect rect1;
	rect1.left = pScaleData->m_ptAxisScale.x-(long)(fZoomRatio * 20*m_fCoefficient );
	rect1.top = pScaleData->m_ptAxisScale.y + (long)(fZoomRatio * 7*m_fCoefficient );
	rect1.right = pScaleData->m_ptAxisScale.x + (long)(fZoomRatio * 24*m_fCoefficient);
	rect1.bottom = pScaleData->m_ptAxisScale.y + (long)(fZoomRatio * 20*m_fCoefficient);

	CRect rect;
	LOGFONT lf = m_lfXAxisScaleFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lIMM_2 = (long)(2*m_fCoefficient * fZoomRatio);
	if(m_lXAxisTextDrawStyle==1)
	{
		rect.left = pScaleData->m_ptAxisScale.x-lIMM_2-rect1.Width()/2;
		rect.top = pScaleData->m_ptAxisScale.y+(long)(fZoomRatio*m_nXAxisUnitScaleLineLen);
		rect.right = pScaleData->m_ptAxisScale.x+rect1.Width()/2+lIMM_2;
		rect.bottom = pScaleData->m_ptAxisScale.y + (long)(fZoomRatio*m_nXAxisUnitScaleLineLen) + rect1.Height();
		rect.OffsetRect(ptOffset);
		if(bReallyDraw)
			CmDrawTextRect(pDC,strText,m_crXAxisScaleFontColor,rect,RGB(0,0,0),lf,TRANSPARENT,DT_VCENTER|DT_CENTER,0);
	}
	else
	{
		rect.left = pScaleData->m_ptAxisScale.x+lIMM_2*3/2;
		rect.top = pScaleData->m_ptAxisScale.y + (long)(fZoomRatio*m_nXAxisTenthScaleLineLen);
		rect.right = pScaleData->m_ptAxisScale.x+rect1.Width()+lIMM_2;
		rect.bottom = pScaleData->m_ptAxisScale.y + (long)(fZoomRatio*m_nXAxisUnitScaleLineLen) + rect1.Height();
		rect.OffsetRect(ptOffset);
		if(bReallyDraw)
			CmDrawTextRect(pDC,strText,m_crXAxisScaleFontColor,rect,RGB(0,0,0),lf,TRANSPARENT,0,0);
	}
	return rect;
}
void CDescartesAxis::DrawXAxisName(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	long iLen=m_strXAxisName.GetLength();
	CFont CF;
	LOGFONT lf = m_lfXAxisNameFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lfWidth = GetCharWidthByLogfont2(pDC,lf);
	CRect rect;
	rect.top = m_rectXAxis.top ;
	rect.right = m_rectXAxis.right;
	rect.left = rect.right - lfWidth * m_strXAxisName.GetLength();
	rect.bottom = m_rectXAxis.bottom;
	rect.top = rect.bottom - abs(lf.lfHeight);

	rect.OffsetRect(ptOffset);
	CmDrawTextRect(pDC,m_strXAxisName,m_crXAxisNameFontColor,&rect,RGB(255,0,0),
				   lf,TRANSPARENT,DT_BOTTOM|DT_RIGHT,0);
}

void CDescartesAxis::DrawXAxis(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	long iNum=m_listXAxisScale.GetCount();

	if(iNum<=0)
		return;
	
	CPen pen;
	m_logpenXAxisGridLine=InitLogPen(m_lXAxisGridLineStyle,1,m_crXAxisGridLineColor);	
	pen.CreatePenIndirect(&m_logpenXAxisGridLine);
	CPen *cOldB=pDC->SelectObject(&pen);
	double iIntgerEndPalace=m_dXAxisMaxVal;//GetIntegeralEndPalace();
	if(iIntgerEndPalace<0)iIntgerEndPalace=0;

	long i = 0;
	for (i=0;i<iNum;i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData*)m_listXAxisScale.GetAt(i);
		if(m_lAxisDrawStyle & DESCARTESAXISDRAW_XAXIS_LINE)
		{
			if ((pScaleData->m_ptAxisScale.x>m_rectWorkArea.left)&&(pScaleData->m_ptAxisScale.x<=m_rectWorkArea.right))
			{
				DrawXAxisLine(pDC,pScaleData,fZoomRatio,ptOffset);
			}
		}
	}

	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_XAXIS_SCALETEXT)
	{
		long iStep=iNum;

		for (i=0;i<iNum;i++)
		{
			CAxisScaleData *pScaleData=(CAxisScaleData*)m_listXAxisScale.GetAt(i);
		}

		BOOL bDrawUint=FALSE;

		for (i=0;i<iStep;i++)
		{
			CAxisScaleData *pScaleData=(CAxisScaleData*)m_listXAxisScale.GetAt(i);
		
			if(i==iStep-1)
			{
			//	if(cEndIntegerRect.left==-1) 
					//bDrawUint=TRUE;
			}
			if(pScaleData->m_ptAxisScale.x<m_rectXAxis.left || pScaleData->m_ptAxisScale.x>m_rectXAxis.right) 
				continue;
			if (pScaleData->m_ptAxisScale.x + m_nMinOneGapWidth > m_rectXAxis.right)
				continue;
			
			DrawXAxisText(pDC,pScaleData,bDrawUint,TRUE,fZoomRatio,ptOffset);
		}
	}

	pDC->SelectObject(cOldB);
	pen.DeleteObject();

	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_XAXIS_HALFSCCALE)
		DrawXSawtooth(pDC,0,fZoomRatio,ptOffset);

	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_XAXIS_TENTHSCALE)
		DrawXSawtooth(pDC,1,fZoomRatio,ptOffset);
}

void CDescartesAxis::DrawOneXSawtooth(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{
	CPen pen;
	pen.CreatePenIndirect(&m_logpenXAxisTenthScale);
	CPen *pOldPen=pDC->SelectObject(&pen);
	for (long i=0;i<10;i++)
	{
		long iGapVal=FloatValToInt((float)((float)m_dXAxisOneGap/10.0*i));
	//	iGapVal = (long)(fZoomRatio * iGapVal);
		CPoint cPt(cBegin.x+iGapVal,cBegin.y);
		if( (cPt.x < m_rectXAxis.left) || (cPt.x > m_rectXAxis.right) ) 
			continue;
		cPt.Offset(ptOffset);
		pDC->MoveTo(cPt.x,cPt.y+(long)fZoomRatio);
		pDC->LineTo(cPt.x,cPt.y + (long)(fZoomRatio * m_nXAxisTenthScaleLineLen) );
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}
void CDescartesAxis::DrawOneXSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{
	long iLen[2]={0,0};
	iLen[0] = (long)(fZoomRatio * m_nXAxisUnitScaleLineLen);
	iLen[1] = (long)(fZoomRatio * m_nXAxisHalfScaleLineLen);
	for (long i=0;i<2;i++)
	{
		long iGapVal=FloatValToInt((float)((float)m_dXAxisOneGap/2.0*i));
		CPoint cPt(cBegin.x+iGapVal,cBegin.y);
		if( (cPt.x < m_rectXAxis.left) || (cPt.x > m_rectXAxis.right) ) 
			continue;
		cPt.Offset(ptOffset);
		DrawShadowVertLine(pDC,cPt.x,cPt.y,iLen[i],m_crXUnitScaleColor,m_crXUnitScaleShadowColor);
	}
}
void CDescartesAxis::DrawXSawtooth(CDC *pDC,BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;
	for (long i=0;i<m_listXAxisScale.GetCount();i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listXAxisScale.GetAt(i);
		if (i==0)
		{
			cBegin=CPoint((long)(pScaleData->m_ptAxisScale.x-m_dXAxisOneGap),pScaleData->m_ptAxisScale.y);
			cEnd=pScaleData->m_ptAxisScale;
		}
		else 
		{
			CAxisScaleData *odNewData=(CAxisScaleData *)m_listXAxisScale.GetAt(i-1);
			cBegin=odNewData->m_ptAxisScale;
			cEnd=pScaleData->m_ptAxisScale;
		}	
		if (bKind==0)
			DrawOneXSawtooth(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		else 
			DrawOneXSawtoothShadow(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
	}
	if(m_listXAxisScale.GetCount()>=2)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listXAxisScale.GetTail();
		cEnd=CPoint((long)(pScaleData->m_ptAxisScale.x+m_dXAxisOneGap),pScaleData->m_ptAxisScale.y);
		cBegin=pScaleData->m_ptAxisScale;
		if (bKind==0)
			DrawOneXSawtooth(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		else 
			DrawOneXSawtoothShadow(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
	}
}


void CDescartesAxis::DrawIt(CDC *pDC,float fZoomRatio, CPoint ptOffset)
{
	DrawAxisBack(pDC,fZoomRatio,ptOffset);
	
	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_WORKAREA)
	{
		DrawArea(pDC,fZoomRatio,ptOffset);
	}
	
	long nBkMode = pDC->SetBkMode(TRANSPARENT);
	
	DrawXYAxisRect(pDC,fZoomRatio,ptOffset);	
	DrawYAxis(pDC, fZoomRatio, ptOffset);

	if (m_bUseY2Axis)
	{
		DrawY2Axis(pDC, fZoomRatio, ptOffset);
	}

	DrawXAxis(pDC, fZoomRatio, ptOffset);
	
	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_AXISCENTER)
	{
		DrawAxisCenter(pDC,fZoomRatio,ptOffset);
	}
	
	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_XAXIS_NAME)
	{
		DrawXAxisName(pDC,fZoomRatio,ptOffset);
	}
	
	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_NAME)
	{
		DrawYAxisName(pDC,fZoomRatio,ptOffset);

		if (m_bUseY2Axis)
		{
			DrawY2AxisName(pDC,fZoomRatio,ptOffset);
		}
	}
	
	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_AXISTITLE)
	{
		DrawAxisTitle(pDC,fZoomRatio,ptOffset);
	}
	
	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_AXISBODER)
	{
		DrawFrame(pDC,fZoomRatio,ptOffset);
	}

	pDC->SetBkMode(nBkMode);
}

void CDescartesAxis::DrawAxisTitle(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	long iLen=m_strAxisTitle.GetLength();
	CFont CF;
	LOGFONT lf = m_lfAxisTitleFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);

	long lfWidth = GetCharWidthByLogfont2(pDC,lf);
	
	iLen = lfWidth * iLen /*/ 2*/;//zhouhj 20211026 删除除以2,会导致长度不够,标题换行,导致显示不全
	iLen = abs(iLen);
	long iWidth = 0;
	CRect rect;
	rect.left = m_rectBorder.left;
	rect.top = m_rectBorder.top ;
	rect.right = m_rectBorder.right;
	rect.bottom = m_rectWorkArea.top;

	CPoint ptCenter = rect.CenterPoint();
	rect.left = ptCenter.x - iLen;
	rect.right = ptCenter.x + iLen;

	rect.OffsetRect(ptOffset);

	CmDrawTextRect(pDC,m_strAxisTitle,m_crAxisTitleFont,&rect,RGB(0,0,0),
				   lf,TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}

void CDescartesAxis::DrawFrame(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rect = m_rectBorder;
	rect.OffsetRect(ptOffset);
	Draw3dRectBorder(pDC,&rect,m_nFrameShadow,m_crFrameLeftTopColor,m_crFrameRightBottomColor);
}
//修改工作区域
void CDescartesAxis::ModifyWorkArea(CRect* cRect,BOOL bInit,float fZoomRatio,CPoint ptOffset)
{
	CRect cNewRect=cRect[0];
	m_rectBorder=cNewRect;

	m_rectXAxis.bottom=cNewRect.bottom - (long)(fZoomRatio*m_nBottomGap);
	m_rectXAxis.top=m_rectXAxis.bottom - (long)(fZoomRatio * m_nXAxisAreaHeight);
	
	m_rectWorkArea.bottom=m_rectXAxis.top;
	m_rectWorkArea.top = cNewRect.top + (long)(fZoomRatio*m_nTopGap);
	
	m_rectYAxis.left = cNewRect.left + (long)(fZoomRatio*m_nLeftGap);
	m_rectYAxis.right = m_rectYAxis.left + (long)(fZoomRatio*m_nYAxisAreaWidth);

	if (m_bUseY2Axis)
	{
		m_rectY2Axis.right = cNewRect.right - (long)(fZoomRatio*m_nLeftGap);
		m_rectY2Axis.left = m_rectY2Axis.right - (long)(fZoomRatio*m_nYAxisAreaWidth);
	}

	m_rectWorkArea.left=m_rectYAxis.right;

	if (m_bUseY2Axis)
	{
		m_rectWorkArea.right=m_rectY2Axis.left;
	}
	else
	{
		m_rectWorkArea.right=cNewRect.right - (long)(fZoomRatio*m_nRightGap);
	}

	m_rectXAxis.left=m_rectWorkArea.left;
	m_rectXAxis.right=m_rectWorkArea.right;

	m_rectYAxis.top=m_rectWorkArea.top;
	m_rectYAxis.bottom=m_rectWorkArea.bottom;

	if (m_bUseY2Axis)
	{
		m_rectY2Axis.top=m_rectWorkArea.top;
		m_rectY2Axis.bottom=m_rectWorkArea.bottom;
	}

	InitAxisAttr();
}

BOOL CDescartesAxis::MakeWorkAreaLegal(CRect &cNewRect)//检验工作区合法性
{
	if(cNewRect.left<0)
		cNewRect.left=0;
	if(cNewRect.right<0)
		cNewRect.right=0;
	if(cNewRect.top<0)
		cNewRect.top=0;
	if(cNewRect.bottom<0)
		cNewRect.bottom=0;
	if (cNewRect.Height()<30)
		cNewRect.bottom=cNewRect.top+30;
	if (cNewRect.Width()<50)
		cNewRect.right=cNewRect.left+30;
	
	return TRUE;
}
//绘制边界
void CDescartesAxis::DrawWorkAreaBorder(CDC *pDC,float fZoomRatio,CPoint ptOffset)//,rect,iGap,crLeftTop,crRightBottom);
{
	CRect rect=GetDrawWorkAreaRect();
	rect.OffsetRect(ptOffset);
	Draw3dRectBorder(pDC,&rect,m_nWorkAreaBorderShadow,m_crWorkAreaBorderLeftTopColor,m_crWorkAreaBorderRightBottomColor);
}

void CDescartesAxis::DrawAxisBack(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	//绘制背景
	CBrush brush;
	brush.CreateSolidBrush(m_crAxisBackColor);
	pDC->FillRect(m_rectBorder,&brush);
	brush.DeleteObject();
	
}

void CDescartesAxis::DrawArea(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rect=GetDrawWorkAreaRect();
	rect.OffsetRect(ptOffset);

//	Draw3dRectBorder(pDC,&rect,(long)(fZoomRatio*m_nWorkAreaBorderShadow),m_crWorkAreaBorderLeftTopColor,m_crWorkAreaBorderRightBottomColor);
    Draw3dRectByMe(pDC,rect,(long)(fZoomRatio*m_nWorkAreaBorderShadow),m_crWorkAreaBorderLeftTopColor,m_crWorkAreaBorderRightBottomColor,m_crWorkAreaBkColor);

}
CRect CDescartesAxis::GetDrawWorkAreaRect(float fZoomRatio,CPoint ptOffset)
{
	CRect rect=m_rectWorkArea;
	rect.bottom += (long)(fZoomRatio*3);
	rect.right += (long)(fZoomRatio*2);
	return rect;
}

void CDescartesAxis::DrawAxisCenter(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rectWork=m_rectWorkArea;

	double fYValue=0,fXValue=0;
	double fYMaxValue=0,fYMinValue=0,fXMaxValue=0,fXMinValue=0;
	CPoint pointCenter=CPoint(0,0);
	///////////////
	fYMaxValue=m_dYAxisMaxVal;
	fYMinValue=m_dYAxisMinVal;
	double fValYOneGap=m_dOneYGapValue;//iHeight/(fYMaxValue-fYMinValue);
	///////////////////////////////////////////////
	fXMaxValue=m_dXAxisMaxVal;
	fXMinValue=(float)m_dXAxisMinVal;
	double fValXOneGap=m_dOneXGapValue;//iWidth/(fXMaxValue-fXMinValue);
	double f=0;
	f=rectWork.left  + (0-fXMinValue)*fValXOneGap;
	pointCenter.x=FloatValToInt(f);
	f=rectWork.bottom - (0-fYMinValue)*fValYOneGap;
	//FloatValToInt
	pointCenter.y=FloatValToInt(f);//(long)();

	pointCenter.Offset(ptOffset);
	rectWork.OffsetRect(ptOffset);

	CPen pen,*pOldPen;
	pen.CreatePen(m_lAxisCenterLineType,m_lAxisCenterLineWidth,m_crAxisCenterColor);
	pOldPen=pDC->SelectObject(&pen);
	if(pointCenter.x>rectWork.left && pointCenter.x<rectWork.right)
	{
		pDC->MoveTo(pointCenter.x,rectWork.top);
		pDC->LineTo(pointCenter.x,rectWork.bottom);
	}
	if(pointCenter.y>rectWork.top && pointCenter.y<rectWork.bottom)
	{
		pDC->MoveTo(rectWork.left,pointCenter.y);
		pDC->LineTo(rectWork.right,pointCenter.y);
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

void CDescartesAxis::SetXAxisMaxUnitCount(long lVal)
{
	m_lXAxisMaxUnitCount = lVal;
}
long CDescartesAxis::GetXAxisMaxUnitCount( )
{
	return m_lXAxisMaxUnitCount;
}
void CDescartesAxis::SetYAxisMaxUnitCount(long lVal)
{
	m_lYAxisMaxUnitCount = lVal;
}
long CDescartesAxis::GetYAxisMaxUnitCount( )
{
	return m_lYAxisMaxUnitCount;
}

void CDescartesAxis::InitAxisAttr()
{
	CRect rectWork=m_rectWorkArea;
	double fYValue=0,fXValue=0;
	double fYMaxValue=0,fYMinValue=0,fXMaxValue=0,fXMinValue=0;
	CPoint pointCenter=CPoint(0,0);
	fYMaxValue=m_dYAxisMaxVal;
	fYMinValue=m_dYAxisMinVal;
	long iHeight=rectWork.Height();
	double fValYOneGap=iHeight/(fYMaxValue-fYMinValue);///Y轴实际坐标与实际值的比率
	///////////////////////////////////////////////
	fXMaxValue=m_dXAxisMaxVal;
	fXMinValue=m_dXAxisMinVal;
	long iWidth=rectWork.Width();
	double fValXOneGap=iWidth/(fXMaxValue-fXMinValue);//X轴实际坐标与实际值的比率
	/////坐标原点在屏幕上的位置
	double f=rectWork.left + (0-fXMinValue)*fValXOneGap;
	pointCenter.x=FloatValToInt(f);
	f=rectWork.bottom -(0-fYMinValue)*fValYOneGap;
	pointCenter.y=FloatValToInt(f);
	/////// 
	m_dOneYGapValue=fValYOneGap;
	m_dOneXGapValue=fValXOneGap;
	m_ptCenterLogInDv=pointCenter;
}

void CDescartesAxis::LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint, long nAxisIndex)
{
	double f=fx*m_dOneXGapValue+m_ptCenterLogInDv.x;
	pPoint->x=FloatValToInt(f);
	f=-fy*m_dOneYGapValue+m_ptCenterLogInDv.y;
	pPoint->y=FloatValToInt(f);;
}
//从实际坐标获取实际坐标所代表的值
void CDescartesAxis::DevicePointToLogicPoint(const CPoint &point, double *fx,double *fy, long nAxisIndex)
{
	*fy=-(point.y-m_ptCenterLogInDv.y) / m_dOneYGapValue;
	*fx=(point.x-m_ptCenterLogInDv.x) / m_dOneXGapValue;
}

void CDescartesAxis::LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex)
{
    double f=fVal*m_dOneXGapValue;
    *nVal = FloatValToInt(f);
}

void CDescartesAxis::DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex)
{
    *fVal= nVal / m_dOneXGapValue;
}

void CDescartesAxis::GetAxisDrawArea(CRect &rcArea)
{
	rcArea = m_rectWorkArea;
}

void CDescartesAxis::GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
	dXMin = m_dXAxisMinVal;
	dYMin = m_dYAxisMinVal;
	dXMax = m_dXAxisMaxVal;
	dYMax = m_dYAxisMaxVal;
}

void CDescartesAxis::SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax)
{
	SetMinMaxVal(dXMin, dYMin, dXMax, dYMax, 0);
}

void CDescartesAxis::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{
	SetXAxisName(strXAxisName);
	SetYAxisName(strYAxisName);
	SetAxisTitle(strAxisTitle);
}

#ifdef USE_AXIS_CONFIG//zhouhj 20211026 增加用于设置坐标轴
void CDescartesAxis::SetAxisConfig(CDataGroup *pAxisConfig)
{
	if (pAxisConfig == NULL)
	{
		return;
	}

	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_WorkAreaBkColor));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_XAxisGridLineColor));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_YAxisGridLineColor));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_AxisCenterLineWidth));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_AxisCenterColor));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_XAxisWorkAreaBackColorFrom));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_YAxisWorkAreaBackColorFrom));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_XAxisWorkAreaBackColorTo));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_YAxisWorkAreaBackColorTo));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_AxisScaleFont));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_AxisNameFont));
	SetAxisConfig((CDvmData*)pAxisConfig->FindByID(AXIS_CONFIG_ID_AxisTopGap));

}

void CDescartesAxis::SetAxisConfig(CDvmData *pAxisData)
{
	if (pAxisData == NULL)
	{
		return;
	}

	COLORREF crValue = 0;
	long nValue = 0;

	if (pAxisData->m_strID == AXIS_CONFIG_ID_WorkAreaBkColor)
	{
		crValue = CString_To_long(pAxisData->m_strValue);
		SetWorkAreaBkColor(crValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_XAxisGridLineColor)
	{
		m_crXAxisGridLineColor = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_YAxisGridLineColor)
	{
		m_crYAxisGridLineColor = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_AxisCenterLineWidth)
	{
		m_lAxisCenterLineWidth = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_AxisCenterColor)
	{
		m_crAxisCenterColor = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_XAxisWorkAreaBackColorFrom)
	{
		m_crXAxisWorkAreaBackColorFrom = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_YAxisWorkAreaBackColorFrom)
	{
		m_crYAxisWorkAreaBackColorFrom = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_XAxisWorkAreaBackColorTo)
	{
		m_crXAxisWorkAreaBackColorTo = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_YAxisWorkAreaBackColorTo)
	{
		m_crYAxisWorkAreaBackColorTo = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_AxisScaleFont)
	{
		nValue = CString_To_long(pAxisData->m_strValue);
		m_lfYAxisScaleFont= InitLogFont ((long)(-nValue*m_fCoefficient),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
		m_lfXAxisScaleFont = m_lfYAxisScaleFont;
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_AxisNameFont)
	{
		nValue = CString_To_long(pAxisData->m_strValue);
		m_lfYAxisNameFont = InitLogFont ((long)(-nValue*m_fCoefficient),0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
		m_lfXAxisNameFont = m_lfYAxisNameFont;
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_AxisTopGap)
	{
		nValue = CString_To_long(pAxisData->m_strValue);
		m_nTopGap = (long)(nValue*m_fCoefficient);
	}
}

void CDescartesAxis::GetAxisConfig(CDataGroup *pAxisConfig)
{
}
#endif

/*///////////////////////////////////////////////////////////////
		下面定义图形的相关操作
*////////////////////////////////////////////////////////

double CDescartesAxis::GetFloatCarryVal(double fVal)
{
	double fStep = 0.0001;
	double fStep1 = fStep*10;
	for (long i=1;;i++)
	{
		if( (fVal >= fStep) && (fVal < fStep1) ) 
			break;
		fStep = fStep1;
		fStep1 *= 10;
	}
	return fStep;
}
double CDescartesAxis::MakeFloatGapValLegal(double fVal,double &lVal)
{
	double fTmp = fVal;
	if (fTmp <= 0.0001)
	{
		fVal=fTmp;
		return fTmp;
	}

	double fMulti = GetFloatCarryVal(fTmp);///进位数值
	long iSet[4]={1,2,5,10};/////////
	long i = 0;

	for (i=0;i<3;i++)
	{
		double fMin = fMulti*iSet[i];
		double fMax = iSet[i+1]*fMulti;

		if ((fTmp>=fMin)&&(fTmp<fMax))
		{
			lVal = fMulti*iSet[i];
			return fMulti*iSet[i+1];
		}
	}
	
	return iSet[i+1]*fMulti;
}

void CDescartesAxis::AdjustAxisDef(CRect rectArea,BOOL bAdjust,float fZoomRatio,CPoint ptOffset)
{
	long iH=0,iW=0;
	iH=rectArea.Height();
	iW=rectArea.Width();
	iH=iH-m_nBottomGap-m_nTopGap-m_nXAxisAreaHeight;
	iW=iW-m_nLeftGap-m_nRightGap-m_nYAxisAreaWidth;
	if(iW<=0)
		iW=20;
	if(iH<=0)
		iH=20;
	rectArea.bottom=rectArea.top+iH + m_nBottomGap + m_nTopGap+m_nXAxisAreaHeight;
	rectArea.right =rectArea.left+iW +m_nLeftGap+ m_nRightGap+m_nYAxisAreaWidth;

	if (m_bAxisXYUnitLock)
	{
		iH=rectArea.Height();
		iW=rectArea.Width();
		iH=iH-m_nBottomGap-m_nTopGap-m_nXAxisAreaHeight;
		iW=iW-m_nLeftGap-m_nRightGap-m_nYAxisAreaWidth;

		double fCoef=0;//(float)iW/iH;
		double fVer = (m_dYAxisOldMaxVal - m_dYAxisOldMinVal) / iH;
		double fHor = (m_dXAxisOldMaxVal - m_dXAxisOldMinVal) / iW;
		if(fVer>fHor)
		{
			fCoef=fVer / fHor;
			m_dXAxisMinVal = m_dXAxisOldMinVal*fCoef;
			m_dXAxisMaxVal = m_dXAxisOldMaxVal * fCoef;
			m_dYAxisMinVal = m_dYAxisOldMinVal;
			m_dYAxisMaxVal = m_dYAxisOldMaxVal;
		}
		else
		{
			fCoef=fHor / fVer;
			m_dYAxisMinVal=m_dYAxisOldMinVal*fCoef;
			m_dYAxisMaxVal=m_dYAxisOldMaxVal*fCoef;
			m_dXAxisMinVal=m_dXAxisOldMinVal;
			m_dXAxisMaxVal  =m_dXAxisOldMaxVal;
		}
	}

	ModifyWorkArea(&rectArea,1,fZoomRatio,ptOffset);
	ResetYAxisDef();
	ResetXAxisDef();
	InitAxisAttr();
}

BOOL CDescartesAxis::AdjustAxisDef(double fMinX,double fMinY,double fMaxX,double fMaxY,BOOL bAdjust,float fZoomRatio,CPoint ptOffset)
{
	if(bAdjust)
	{
        double fMax=max(fMaxY,fMaxX);
        double fMin=min(fMinX,fMinY);
		if(fMin>fMax)
			return FALSE;
		CRect rectArea=m_rectBorder;
		m_dXAxisOldMinVal = fMinX ;
		m_dXAxisOldMaxVal =fMaxX ;
		m_dYAxisOldMinVal = fMinY;
		m_dYAxisOldMaxVal =fMaxY;
		AdjustAxisDef(rectArea,TRUE,fZoomRatio,ptOffset);
	}
	else
	{
		CRect rectArea=m_rectBorder;
		m_dXAxisMinVal = fMinX ;
		m_dXAxisMaxVal =fMaxX ;
		m_dYAxisMinVal = fMinY;
		m_dYAxisMaxVal =fMaxY;
		ModifyWorkArea(&rectArea,1,fZoomRatio,ptOffset);
		ResetYAxisDef();
		ResetXAxisDef();
		InitAxisAttr();
	}
	return TRUE;
}

CString CDescartesAxis::GetTimeVal(float fTimeVal)
{
	if(fTimeVal<=0.001)
		return _T("0");

	float fMinute = fTimeVal / 60;
	long   iMinute = FloatValToInt(fMinute,0);
	float fHour   = fMinute  / 60;
	long   iHour   = FloatValToInt(fHour,0);
	iMinute = iMinute - iHour * 60 ;
	CString strTime=_T("");
	CString strTemp=_T("");
	BOOL bTrue=FALSE;
	if(iHour>0)
	{
		strTemp.Format(_T("%d:"),iHour);
		bTrue=TRUE;
	}
	strTime += strTemp;
	if(iMinute>0)
	{
		strTemp.Format(_T("%d:"),iMinute);
		bTrue=TRUE;
	}
	else
	{
		if(iHour)	
		{
			bTrue=TRUE;
            strTemp=_T("0:");
		}
		else  
		{
            strTemp=_T("");
			bTrue=FALSE;
		}
	}
	strTime += strTemp;
	iMinute = FloatValToInt(fMinute,0);
	long iSecond = FloatValToInt(fTimeVal,0);
	float fMS=fTimeVal - iSecond;
	iSecond = iSecond - iMinute * 60 ;
	if(iSecond>0)
	{
		bTrue=TRUE;
		strTemp.Format(_T("%d\'"),iSecond);
	}
	else
	{
        strTemp=_T("0\'");
		bTrue=TRUE;
	}
	strTime += strTemp;
	strTemp=_T("");
	if(fMS>=0.001)
	{
		strTemp.Format(_T("%.3f"),fMS);
		strTemp=strTemp.Right(3);
		strTemp+=_T("\'\'");
	}
	strTime += strTemp;
	return strTime;
}

//////////////////////////////////////////////////////////////////////////
//定义放大、缩小、移动接口
void CDescartesAxis::ZoomIn(float fZoomIn)
{
	double fMinX=0,fMinY=0,fMaxX=0,fMaxY=0;
	fMinX = m_dXAxisMinVal / fZoomIn;
	fMaxX = m_dXAxisMaxVal / fZoomIn;
	fMinY = m_dYAxisMinVal / fZoomIn;
	fMaxY = m_dYAxisMaxVal / fZoomIn;
	
	double fLenX=fabs(fMinX-fMaxX);
	double fLenY=fabs(fMaxY-fMinY);
	double fLenXY=fabs(fLenX-fLenY) / 2;
	if(fLenX>fLenY)
	{
		fMinY -= fLenXY;
		fMaxY += fLenXY;
	}
	else
	{
		fMinX -= fLenXY;
		fMaxX += fLenXY;
	}
	double fCoefX=0, fCoefY=0;
	
	fCoefX= (m_dXAxisOldMaxVal - m_dXAxisOldMinVal) / (fMaxX-fMinX);
	fCoefY= (m_dYAxisOldMaxVal - m_dYAxisOldMinVal) / (fMaxY-fMinY);
	
	fCoefX=fabs(fCoefX);
	fCoefY=fabs(fCoefY);
	if(fCoefX>m_dMaxZoomMultiple || fCoefY>m_dMaxZoomMultiple)
		return;
	
	AdjustAxisDef(fMinX,fMinY,fMaxX,fMaxY);	
}

void CDescartesAxis::ZoomIn(double dMinX,double dMaxX,double dMinY,double dMaxY)
{
	//X、Y轴的数值一样，保证绘图的比列一致
	if (m_bAxisXYUnitLock)
	{
		double dLenX = 0, dLenY = 0, dLenXY = 0;
		double dLMaxLen = 0;
		dLenX = fabs(dMinX-dMaxX);
		dLenY = fabs(dMaxY-dMinY);
		dLenXY = fabs(dLenX-dLenY) / 2;
		if(dLenX > dLenY)
		{
			dMinY -= dLenXY;
			dMaxY += dLenXY;
		}
		else
		{
			dMinX -= dLenXY;
			dMaxX += dLenXY;
		}
		//使整个图形能够看到坐标轴的中心轴的处理部分
		dLMaxLen = dMaxY-dMinY;
		if (dMinY >= 0)
			dMinY = -dLMaxLen * m_dAxisWorkMarginRatio;//坐标工作区同其中的图形的边距
		if (dMinX >= 0)
			dMinX=-dLMaxLen * m_dAxisWorkMarginRatio;
		if (dMaxX <= 0)
			dMaxX = dLMaxLen *m_dAxisWorkMarginRatio;
		if (dMaxY <= 0)
			dMaxY = dLMaxLen * m_dAxisWorkMarginRatio;
		dLenX = fabs(dMinX-dMaxX);
		dLenY = fabs(dMaxY-dMinY);
		dLMaxLen = max(dLenX,dLenY);
		dLenXY = fabs(dLenX-dLenY) / 2 ;
		if(dLenX > dLenY)
		{	
			dMinY -= dLenXY;
			dMaxY += dLenXY;
		}
		else
		{	
			dMinX -= dLenXY;
			dMaxX += dLenXY;
		}
		//将X、Y轴各增大m_dAxisWorkMarginRatio倍
		dLenXY = fabs(dLMaxLen) * m_dAxisWorkMarginRatio;
		dMinX -= dLenXY;
		dMaxX += dLenXY;
		dMinY -= dLenXY;
		dMaxY += dLenXY;
	}

	//重新设置当前测试项目的坐标系
	AdjustAxisDef(dMinX,dMinY,dMaxX,dMaxY);	
}

void CDescartesAxis::ZoomIn(CRect rectZoomIn)
{
	ZoomIn(rectZoomIn.TopLeft(),rectZoomIn.BottomRight());
}

void CDescartesAxis::ZoomIn(long lLeft,long lTop,long lRight,long lBottom)
{
	ZoomIn(CPoint(lLeft,lTop),CPoint(lRight,lBottom));
}

void CDescartesAxis::ZoomIn(CPoint ptLeftTop,CPoint ptRightBottom)
{
	double dMinX,dMaxX,dMinY,dMaxY;
	double dx,dy;
	dMinX = dMaxX = dMinY = dMaxY = 0;
	dx = dy = 0;

	DevicePointToLogicPoint(ptLeftTop,&dMinX,&dMaxY);
	DevicePointToLogicPoint(ptRightBottom,&dMaxX,&dMinY);
	
	ZoomIn(dMinX,dMaxX,dMinY,dMaxY);
}

void CDescartesAxis::ZoomOut(float fZoomOut)
{
	double fMinX=0,fMinY=0,fMaxX=0,fMaxY=0;
	fMinX = m_dXAxisMinVal * fZoomOut;
	fMaxX = m_dXAxisMaxVal * fZoomOut;
	fMinY = m_dYAxisMinVal * fZoomOut;
	fMaxY = m_dYAxisMaxVal * fZoomOut;
	
	double fLenX=fabs(fMinX-fMaxX);
	double fLenY=fabs(fMaxY-fMinY);
	double fLenXY=fabs(fLenX-fLenY) / 2;
	if(fLenX>fLenY)
	{
		fMinY-=fLenXY;fMaxY+=fLenXY;
	}
	else
	{
		fMinX-=fLenXY;fMaxX+=fLenXY;
	}
	double fCoefX=0, fCoefY=0;
	
	fCoefX=(fMaxX-fMinX) / (m_dXAxisOldMaxVal - m_dXAxisOldMinVal)  ;
	fCoefY=(fMaxY-fMinY) / (m_dYAxisOldMaxVal - m_dYAxisOldMinVal) ;
	
	fCoefX=fabs(fCoefX);
	fCoefY=fabs(fCoefY);
	if(fCoefX>m_dMaxZoomMultiple || fCoefY>m_dMaxZoomMultiple)
		return;
	
	AdjustAxisDef(fMinX,fMinY,fMaxX,fMaxY);	
}

void CDescartesAxis::Move(float fXOffset,float fYOffset)
{
	m_dXAxisMaxVal -= fXOffset * m_dXCarryOneGap;
	m_dXAxisMinVal -= fXOffset * m_dXCarryOneGap;
	m_dYAxisMaxVal -= fYOffset * m_dYCarryOneGap;
	m_dYAxisMinVal -= fYOffset * m_dYCarryOneGap;
	
	ResetYAxisDef();
	ResetXAxisDef();
	InitAxisAttr();
}

//设置坐标系的绘图位置
long CDescartesAxis::GetAxisMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax)
{
	*xMin = m_dXAxisMinVal;
	*xMax = m_dXAxisMaxVal;	
	*yMin = m_dYAxisMinVal;
	*yMax = m_dYAxisMaxVal;	
	
	return 0;
}

//获取坐标系的绘图位置
long CDescartesAxis::GetPosition(long *left, long *top, long *right, long *bottom)
{
	*left = m_rectBorder.left;
	*top = m_rectBorder.top;
	*right = m_rectBorder.right;
	*bottom = m_rectBorder.bottom;
	
	return 0;
}

//获取坐标系统的工作区，即坐标系统坐标范围标示的有效区域
long CDescartesAxis::GetWorkArea(long *left, long *top, long *right, long *bottom)
{
	*left = m_rectWorkArea.left;
	*top = m_rectWorkArea.top;
	*right = m_rectWorkArea.right;
	*bottom = m_rectWorkArea.bottom;

	return 0;
}

//将逻辑坐标转化为设备坐标:ptx,pty为设备坐标
long CDescartesAxis::LogicPointToDevicePoint(double x,double y,long *ptx,long *pty)
{
	CPoint pt;
	LogicPointToDevicePoint(x,y,&pt);
	*ptx = pt.x;
	*pty = pt.y;
	
	return 0;
}

//将设备坐标转化为逻辑坐标:ptx,pty为设备坐标
long CDescartesAxis::DevicePointToLogicPoint (long ptx,long pty ,double *x,double *y)
{
	CPoint pt;
	pt.x = ptx;
	pt.y = pty;
	DevicePointToLogicPoint(pt,x,y);

	return 0;
}

void CDescartesAxis::DrawXYAxisRect(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rect1=m_rectYAxis;
	CRect rect2=m_rectXAxis;
	CRect rect3=m_rectY2Axis;
	long nWidth = rect1.Width();
	long nHeight = rect2.Height();
	CRect rectangle1,rectangle2,rectangle3,rectangle4;
	long lR1,lG1,lB1,lR2,lG2,lB2;
	COLORREF color1,color2;

	//Y axis work area
	lR1 = GetRValue(m_crYAxisWorkAreaBackColorFrom);
	lG1 = GetGValue(m_crYAxisWorkAreaBackColorFrom);
	lB1 = GetBValue(m_crYAxisWorkAreaBackColorFrom);
	lR2 = GetRValue(m_crYAxisWorkAreaBackColorTo);
	lG2 = GetGValue(m_crYAxisWorkAreaBackColorTo);
	lB2 = GetBValue(m_crYAxisWorkAreaBackColorTo);

	long i = 0;
	for(i=0;i<nWidth;i++)
	{
		rectangle1.SetRect(rect1.left+i,rect1.top,rect1.left+i+1,rect1.bottom);
		rectangle3.SetRect(rect1.left+i,rect1.bottom,rect1.left+i+1,rect2.bottom);
		lR1 = lR1+MulDiv(i,(lR2 - lR1)*1/7,nWidth);
		lB1 = lB1+MulDiv(i,(lG2 - lB1)*1/7,nWidth);
		lG1 = lG1+MulDiv(i,(lB2 - lG1)*1/7,nWidth);
		
		color1 = RGB(lR1,lG1,lB1);
		pDC->FillSolidRect(&rectangle3,color1);
		pDC->FillSolidRect(&rectangle1,color1);
		
	}

	//Y axis work area
	if (m_bUseY2Axis)
	{
		lR1 = GetRValue(m_crYAxisWorkAreaBackColorFrom);
		lG1 = GetGValue(m_crYAxisWorkAreaBackColorFrom);
		lB1 = GetBValue(m_crYAxisWorkAreaBackColorFrom);
		lR2 = GetRValue(m_crYAxisWorkAreaBackColorTo);
		lG2 = GetGValue(m_crYAxisWorkAreaBackColorTo);
		lB2 = GetBValue(m_crYAxisWorkAreaBackColorTo);
		
		for( i=0;i<nWidth;i++)
		{
			rectangle1.SetRect(rect3.right-i,rect3.top,rect3.right-i-1,rect3.bottom);
			rectangle3.SetRect(rect3.right-i,rect3.bottom,rect3.right-i-1,rect2.bottom);
			lR1 = lR1+MulDiv(i,(lR2 - lR1)*1/7,nWidth);
			lB1 = lB1+MulDiv(i,(lG2 - lB1)*1/7,nWidth);
			lG1 = lG1+MulDiv(i,(lB2 - lG1)*1/7,nWidth);
			
			color1 = RGB(lR1,lG1,lB1);
			pDC->FillSolidRect(&rectangle3,color1);
			pDC->FillSolidRect(&rectangle1,color1);
			
		}
	}
	
	//draw X Axis work area back
	lR2 = GetRValue(m_crXAxisWorkAreaBackColorFrom);
	lG2 = GetGValue(m_crXAxisWorkAreaBackColorFrom);
	lB2 = GetBValue(m_crXAxisWorkAreaBackColorFrom);
	lR1 = GetRValue(m_crXAxisWorkAreaBackColorTo);
	lG1 = GetGValue(m_crXAxisWorkAreaBackColorTo);
	lB1 = GetBValue(m_crXAxisWorkAreaBackColorTo);

	for(long j=0;j<nHeight;j++)
	{
		rectangle2.SetRect(rect2.left,rect2.bottom-j-1,rect2.right+1,rect2.bottom-j);
		rectangle4.SetRect(rect1.left+j,rect2.bottom-j-1,rect2.left,rect2.bottom-j);

		lR2 = lR2 + MulDiv(j,(lR1 - lR2 )*1/7,nHeight);
		lB2 = lB2 + MulDiv(j,(lG1 - lB2 )*1/7,nHeight);
		lG2 = lG2 + MulDiv(j,(lB1 - lG2 )*1/7,nHeight);
		color2 = RGB(lR2,lG2,lB2);
		pDC->FillSolidRect(&rectangle2,color2);
		pDC->FillSolidRect(&rectangle4,color2);

		if (m_bUseY2Axis)
		{
			//rectangle4.SetRect(rect1.left+j,rect2.bottom-j-1,rect2.left,rect2.bottom-j);
			rectangle4.SetRect(rect3.left,rect2.bottom-j-1,rect3.right-j,rect2.bottom-j);
			pDC->FillSolidRect(&rectangle4,color2);
		}
	}
}

void CDescartesAxis::GetAxisInterface(long &nXCenterLog,long &nYCenterLog,double &dXCoef,double &dYCoef)
{
	nXCenterLog = m_ptCenterLogInDv.x;
	nYCenterLog = m_ptCenterLogInDv.y;
	dXCoef      = m_dOneXGapValue;
	dYCoef      = m_dOneYGapValue;
}
