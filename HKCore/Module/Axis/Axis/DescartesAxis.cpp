// DescartesAxis.cpp : implementation file
//

#include "stdafx.h"
#include "Axis.h"
#include "DescartesAxis.h"
#include <math.h>
#include "..\..\Module\Api\GloblaDrawFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDescartesAxis
#define BOTTOMADD 2

IMPLEMENT_DYNCREATE(CDescartesAxis, CCmdTarget)

CDescartesAxis::CDescartesAxis()
{
	EnableAutomation();
	
	m_dAxisWorkMarginRatio = 0.05;
	m_bAxisXYUnitLock = TRUE;
	m_lAxisType = 0;
	m_iMinOneGapWidth = 20;
	m_iMinOneGapHeight = 20;

	ColorR = 255;
	ColorG = 255;
	
	m_strAxisTitle = "";
	
	InitAxis();
	ContinueInitAxis();
	
	m_dMaxZoomMultiple = 100.0f;
	
	m_lXAxisMaxUnitCount = 10;
	m_lYAxisMaxUnitCount = 10;
	
	AfxOleLockApp();
}

CDescartesAxis::~CDescartesAxis()
{
	EndXAxisDef();
	EndYAxisDef();
	
	AfxOleUnlockApp();
}


void CDescartesAxis::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CDescartesAxis, CCmdTarget)
	//{{AFX_MSG_MAP(CDescartesAxis)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDescartesAxis, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CDescartesAxis)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDescartesAxis to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {9045AF09-D6CF-4413-A251-703E2D0C4BCB}
static const IID IID_IDescartesAxis =
{ 0x9045af09, 0xd6cf, 0x4413, { 0xa2, 0x51, 0x70, 0x3e, 0x2d, 0xc, 0x4b, 0xcb } };

BEGIN_INTERFACE_MAP(CDescartesAxis, CCmdTarget)
	INTERFACE_PART(CDescartesAxis, IID_IDescartesAxis, Dispatch)
	INTERFACE_PART(CDescartesAxis, IID_IDescartesAxisInterface, DescartesAxisInterface)
	INTERFACE_PART(CDescartesAxis, IID_IAxisBaseInterface,AxisBaseInterface)
END_INTERFACE_MAP()

// {8A2C36AE-3BC2-4902-8CB8-7ECDAB1843C7}
IMPLEMENT_OLECREATE(CDescartesAxis, PROGID_IDescartesAxis, 0x8a2c36ae, 0x3bc2, 0x4902, 0x8c, 0xb8, 0x7e, 0xcd, 0xab, 0x18, 0x43, 0xc7)

/////////////////////////////////////////////////////////////////////////////
// CDescartesAxis message handlers


int CDescartesAxis::GetXAxisMinSawGapWidth()
{
	return m_iMinOneGapWidth;
}

void CDescartesAxis::SetXAxisMinSawGapWidth(int iXAxisMinSawGapWidth)
{
	m_iMinOneGapWidth=iXAxisMinSawGapWidth;
}
int CDescartesAxis::GetYAxisMinSawGapHeight()
{
	return m_iMinOneGapHeight;
}
void CDescartesAxis::SetYAxisMinSawGapHeight(int iYAxisMinSawGapHeight)
{
	m_iMinOneGapHeight=iYAxisMinSawGapHeight;
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
	m_crAxisBackColor = GetSysColor(COLOR_3DFACE);//RGB(240,240,240);
	m_rectWorkArea=CRect(30,5,300,300);
	m_rectXAxis=CRect(30,300,300,320);
	m_rectYAxis=CRect(0,5,30,300);
	m_dXAxisMinVal=0;
	m_dXAxisMaxVal=3269;
	
	m_dXCarryOneGap=1;
	m_dYCarryOneGap=1;
	m_fCoefficient = 1.0f;
	
	m_iLeftGap = (int)(5*m_fCoefficient);
	m_iRightGap = (int)(5*m_fCoefficient);
	m_iTopGap = (int)(18*m_fCoefficient);
	m_iBottomGap = (int)(5*m_fCoefficient);
	
	//WorkArea Bk
	m_crWorkAreaBkColor = RGB(255,255,255);
	m_crWorkAreaBorderLeftTopColor = RGB(128,128,128);
	m_crWorkAreaBorderRightBottomColor = RGB(240,240,240);
	m_iWorkAreaBorderShadow = (int)(2*m_fCoefficient);
	m_crFrameLeftTopColor = RGB(128,128,128);
	m_crFrameRightBottomColor = RGB(240,240,240);
	m_iFrameShadow = (int)(2*m_fCoefficient);

	m_crXUnitScaleColor=RGB(0,0,0);
	m_crXUnitScaleShadowColor = RGB(255,255,255);
	m_crYUnitScaleColor=RGB(0,0,0);
	m_crYUnitScaleShadowColor=RGB(255,255,255);
	
	m_crAxisTitleFont = RGB(0,0,0);
	m_lfAxisTitleFont = InitLogFont ((int)(-14*m_fCoefficient),0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',"宋体");
	//VertDef
	m_lfYAxisScaleFont=InitLogFont ((int)(-9*m_fCoefficient),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
	m_lfYAxisNameFont=InitLogFont ((int)(-12*m_fCoefficient),0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',"宋体");
	m_crYAxisScaleFontColor=RGB(0,0,0);
	m_crYAxisNameFontColor=RGB(0,0,0);
	m_lYAxisGridLineStyle=PS_DOT;
	m_crYAxisGridLineColor = GetSysColor(COLOR_3DDKSHADOW);
	m_crYAxisTenthScale = RGB(0,0,0);
	m_crXAxisTenthScale = RGB(0,0,0);
	m_iYAxisAreaWidth = (int)(35*m_fCoefficient);
	m_iYAxisUnitScaleLineLen = (int)(15*m_fCoefficient);
	m_iYAxisHalfScaleLineLen = (int)(8*m_fCoefficient);
	m_iYAxisTenthScaleLineLen = (int)(3*m_fCoefficient);
	//HorzDef
	m_lfXAxisScaleFont=InitLogFont ((int)(-9*m_fCoefficient),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
	m_lfXAxisNameFont=InitLogFont ((int)(-12*m_fCoefficient),0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',"宋体");
	m_crXAxisScaleFontColor = RGB(0,0,0);
	m_crXAxisNameFontColor = RGB(0,0,0);
	m_lXAxisGridLineStyle = PS_DOT;
	m_crXAxisGridLineColor = GetSysColor(COLOR_3DDKSHADOW);
	m_iXAxisAreaHeight = (int)(30*m_fCoefficient);
	m_iXAxisUnitScaleLineLen = (int)(10*m_fCoefficient);
	m_iXAxisHalfScaleLineLen = (int)(8*m_fCoefficient);
	m_iXAxisTenthScaleLineLen = (int)(3*m_fCoefficient);
	
	////////	坐标轴中心轴参数定义
	m_lAxisCenterLineWidth=1;
	m_lAxisCenterLineType = PS_SOLID;
	m_crAxisCenterColor = RGB(0,0,0);
	
	m_lXAxisTextDrawStyle=1;
	m_lAxisDrawStyle = DESCARTESAXISDRAW_ALL;
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

void CDescartesAxis::SetXYAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY)
{
	m_dXAxisMinVal = dMinX;
	m_dXAxisMaxVal = dMaxX;
	m_dYAxisMinVal = dMinY;
	m_dYAxisMaxVal = dMaxY;
	m_dXAxisOldMinVal = dMinX;
	m_dXAxisOldMaxVal = dMaxX;
	m_dYAxisOldMinVal = dMinY;
	m_dYAxisOldMaxVal = dMaxY;

	AdjustAxisDef(m_rectBorder,m_bAxisXYUnitLock);
}
void CDescartesAxis::GetXYAxisMinMaxVal(double &dMinX,double &dMinY,double &dMaxX,double &dMaxY)
{
	dMinX = m_dXAxisMinVal;
	dMaxX = m_dXAxisMaxVal;
	dMinY = m_dYAxisMinVal;
	dMaxY = m_dYAxisMaxVal;
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
	m_iWorkAreaBorderShadow = lWorkAreaBorderShadow;
}
long CDescartesAxis::GetWorkAreaBorderShadow()
{
	return m_iWorkAreaBorderShadow;
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
	m_iFrameShadow = lWorkAreaBorderShadow;
}

long CDescartesAxis::GetFrameShadow()
{
	return m_iFrameShadow;
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
void CDescartesAxis::SetAxisXYUnitLock(BOOL bXYUnitLock)
{
	m_bAxisXYUnitLock = bXYUnitLock;
}
BOOL CDescartesAxis::GetAxisXYUnitLock()
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
	m_iYAxisAreaWidth = l;
}
long CDescartesAxis::GetYAxisAreaWidth()
{
	return m_iYAxisAreaWidth;
}
void CDescartesAxis::SetYAxisUnitScaleLineLen(long l)
{
	m_iYAxisUnitScaleLineLen = l;
}
long CDescartesAxis::GetYAxisUnitScaleLineLen()
{
	return m_iYAxisUnitScaleLineLen;
}
void CDescartesAxis::SetYAxisHalfScaleLineLen(long l)
{
	m_iYAxisHalfScaleLineLen = l;
}
long CDescartesAxis::GetYAxisHalfScaleLineLen()
{
	return m_iYAxisHalfScaleLineLen;
}
void CDescartesAxis::SetYAxisTenthScaleLineLen(long l)
{
	m_iYAxisTenthScaleLineLen = l;
}
long CDescartesAxis::GetYAxisTenthScaleLineLen()
{
	return m_iYAxisTenthScaleLineLen;
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
	m_iXAxisAreaHeight = l;
}
long CDescartesAxis::GetXAxisAreaHeight()
{
	return m_iXAxisAreaHeight;
}
void CDescartesAxis::SetXAxisUnitScaleLineLen(long l)
{
	m_iXAxisUnitScaleLineLen = l;
}
long CDescartesAxis::GetXAxisUnitScaleLineLen()
{
	return m_iXAxisUnitScaleLineLen;
}
void CDescartesAxis::SetXAxisHalfScaleLineLen(long l)
{
	m_iXAxisHalfScaleLineLen = l;
}
long CDescartesAxis::GetXAxisHalfScaleLineLen()
{
	return m_iXAxisHalfScaleLineLen;
}
void CDescartesAxis::SetXAxisTenthScaleLineLen(long l)
{
	m_iXAxisTenthScaleLineLen = l;
}
long CDescartesAxis::GetXAxisTenthScaleLineLen()
{
	return m_iXAxisTenthScaleLineLen;
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

long CDescartesAxis::GetCarryVal(int iVal)
{
	int iStep=1;
	int iStep1=10;
	for (int i=1;;i++)
	{
		if( (iVal >= iStep) && (iVal < iStep1) ) 
			break;
		iStep=iStep1;
		iStep1*=10;
	}
	return iStep;
}

int CDescartesAxis::MakeGapValLegal(float fVal,int &lVal)
{

	int iTmp=(int)fVal;
	if(iTmp==0)
	{
		lVal=1;
		return 1;
	}
	int iMulti=GetCarryVal(iTmp);///进位数值
	int iSet[4]={1,2,5,10};/////////
	for (int i=0;i<3;i++)
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
double CDescartesAxis::GetBeginVal(double lNowVal,double lGapVal)//得到整数倍一个Gap的lNowVal值
{
	double ff,ff1;
	int iMul=1;
	ff=lNowVal/lGapVal;
	ff1=(double)((int)ff);
	if(ff-ff1<0.99)	
		iMul=(int)ff;
	else
		iMul=(int)ff+1;

	double fb=0;
	fb=lNowVal-(lNowVal - iMul*lGapVal);
	return fb;
}
/***********************************************************************
关于Y轴的绘制
***********************************************************************/
long CDescartesAxis::GetBaseOneGapHeight()
{
	return m_iMinOneGapHeight;
}
long CDescartesAxis::GetMinOneGapHeight()
{
	return m_iMinOneGapHeight;
}

void CDescartesAxis::InitYAxisDef()
{
	m_listYAxisScale.EndIt();
}
void CDescartesAxis::EndYAxisDef()
{
	m_listYAxisScale.EndIt();
}

void CDescartesAxis::SetYAxisName(CString strYAxisName)
{
	m_strYAxisName = strYAxisName;
}
CString CDescartesAxis::GetYAxisName()
{	
	return m_strYAxisName;
}

void CDescartesAxis::ResetYAxisDef()
{
	EndYAxisDef();
	int iOneGapPt = GetBaseOneGapHeight();//得到基本的一个Gap的间距
	int iHeight = m_rectYAxis.Height();//得到整个工作区域的高度
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

	int iGapNumTemp=0;
	int iCircleCounts=0;
	for(;iCircleCounts<50;iCircleCounts++)
	{
		dLegalGapVal=MakeFloatGapValLegal(dAxisUnitGapVal,dGapVal);//得到最可能的Mv数
		dGapNum=dYAxisRangeVal/dGapVal;		////最大可能的间隔数
		iGapNumTemp = FloatValToInt(dGapNum);
		dGapNum=FloatValToInt(dGapNum);//iGapNumTemp < dGapNum ? iGapNumTemp+1 : dGapNum;
		int iNowGapPt=(int)(iHeight/dGapNum);	////最小可能的每个间隔值
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
	int iNowGapPt=iHeight/iGapNumTemp;
	if (iNowGapPt==0)iNowGapPt=1;
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
	for (int i=0;i<=iGapNumTemp;i++)
	{
		ResetOneYAxisDef(iBeginVal+i*dGapVal);
	}

	m_dYCarryOneGap=dGapVal;
}
void CDescartesAxis::GetOneYAxisHeight(double iGap,BYTE bKind)
{
	int iHeight=m_rectYAxis.Height();
	double iVal=m_dYAxisMaxVal-m_dYAxisMinVal;
	m_dYAxisOneGap=(int)(iGap*(double)iHeight/iVal);
}
void CDescartesAxis::ResetOneYAxisDef(double lVal)
{
	int iHeight=m_rectYAxis.Height();
	double iVal=m_dYAxisMaxVal-m_dYAxisMinVal;
	//int y=int(m_rectYAxis.bottom-(lVal-m_dYAxisMinVal)*m_dOneYGapValue);
	double f = m_rectYAxis.bottom-(lVal-m_dYAxisMinVal)*m_dOneYGapValue;
	int y=FloatValToInt(f);
	CAxisScaleData *pScaleData=new CAxisScaleData();
	pScaleData->FillIt(lVal,CPoint(m_rectYAxis.right,y));
	m_listYAxisScale.AddTail(pScaleData);
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
	sprintf(pszString,"%.3f",pScaleData->m_dAxisScaleVal);
	chop(pszString);
	LOGFONT lf = m_lfYAxisScaleFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lHeight = abs(lf.lfHeight);

	CRect rect;
	rect.left = m_rectYAxis.left;
	rect.top = pScaleData->m_ptAxisScale.y-lHeight;
	rect.right = m_rectYAxis.right-(long)(fZoomRatio*m_iYAxisUnitScaleLineLen);
	rect.bottom = pScaleData->m_ptAxisScale.y+lHeight;
	rect.OffsetRect(ptOffset);

	CmDrawTextRect(pDC,pszString,m_crYAxisScaleFontColor,
			&rect,RGB(0,0,0),lf,
			TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}
void CDescartesAxis::DrawYAxisName(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rect;
	LOGFONT lf = m_lfYAxisNameFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lfWidth = GetCharWidthByLogfont2(pDC,lf);

	rect.left=m_rectYAxis.left;
	rect.top=m_rectBorder.top+m_iTopGap;
	rect.right=rect.left + lfWidth * m_strYAxisName.GetLength();
	rect.bottom=m_rectBorder.top + (long)(fZoomRatio * m_iTopGap);
	rect.OffsetRect(ptOffset);

	char cName[128];
	lstrcpy(cName,m_strYAxisName);
	CmDrawTextRect(pDC,(LPSTR)cName,m_crYAxisNameFontColor,
				   &rect,RGB(0,0,0),lf,
				   TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}
void CDescartesAxis::DrawYAxis(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	int iNum=m_listYAxisScale.GetCount();
	if(iNum<=0)
		return;
	CPen pen;
	m_logpenYAxisGridLine=InitLogPen(m_lYAxisGridLineStyle,1,m_crYAxisGridLineColor);
	long lGap=(long)(abs(m_lfYAxisScaleFont.lfHeight)*1.5 * fZoomRatio);
	pen.CreatePenIndirect(&m_logpenYAxisGridLine);
	CPen *cOldP=pDC->SelectObject(&pen);
	for (int i=0;i<iNum;i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData*)m_listYAxisScale.GetAt(m_listYAxisScale.FindIndex(i));
		if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_SCALETEXT)
		{
			//if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_TEXT)
			{
				if(pScaleData->m_ptAxisScale.y>=m_rectYAxis.top && pScaleData->m_ptAxisScale.y<=m_rectYAxis.bottom)
				{	
					DrawYAxisText(pDC,pScaleData,fZoomRatio,ptOffset);////标注
				}
			}
		}
		if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_LINE)
		{
			//if(m_lAxisDrawStyle& DESCARTESAXISDRAW_YAXIS_LINE)
			{
				if ((pScaleData->m_ptAxisScale.y>m_rectWorkArea.top)&&
					(pScaleData->m_ptAxisScale.y<m_rectWorkArea.bottom))
				{
					DrawYAxisLine(pDC,pScaleData,fZoomRatio,ptOffset);//网格
				}
			}
		}
	}
	pDC->SelectObject(cOldP);
	pen.DeleteObject();
	if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_HALFSCCALE)
	{
		DrawYSawtooth(pDC,0,fZoomRatio,ptOffset);
	}
	if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_TENTHSCALE)
	{
		DrawYSawtooth(pDC,1,fZoomRatio,ptOffset);
	}
/*
	if( m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_NAME)
	{
		DrawYAxisName(pDC,fZoomRatio,ptOffset);
	}
*/
	
}
///////////////靠工作区内的小锯齿
void CDescartesAxis::DrawOneYSawtooth(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{									  
	CPen pen;
	pen.CreatePenIndirect(&m_logpenYAxisTenthScale);
	CPen *cOldP=pDC->SelectObject(&pen);
	for (int i=0;i<10;i++)
	{
		int iGapVal=GetIntVal((float)((float)m_dYAxisOneGap/10.0*i));
		CPoint cPt(cBegin.x,cBegin.y - iGapVal);
		if ( (cPt.y < m_rectYAxis.top) || (cPt.y>m_rectYAxis.bottom) )
			continue;
		cPt.Offset(ptOffset);
		pDC->MoveTo(cPt.x-1,cPt.y);
		pDC->LineTo(cPt.x-(long)(fZoomRatio*m_iYAxisTenthScaleLineLen),cPt.y);
	}
	pDC->SelectObject(cOldP);
	pen.DeleteObject();
}
///////////////大刻度
void CDescartesAxis::DrawOneYSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{
	int iLen[2]={0,0};
	iLen[0] = (long)(fZoomRatio * m_iYAxisUnitScaleLineLen);
	iLen[1] = (long)(fZoomRatio *m_iYAxisHalfScaleLineLen);
	for (int i=0; i<2;i++)
	{
		int iGapVal=GetIntVal((float)((float)m_dYAxisOneGap/2.0*i));
		CPoint cPt(cBegin.x,cBegin.y-iGapVal);
		if( (cPt.y < (long)(fZoomRatio*m_rectYAxis.top)) || (cPt.y>(long)(fZoomRatio*m_rectYAxis.bottom)) )
			continue;
		cPt.Offset(ptOffset);
		DrawShadowHorzLine(pDC,cPt.x,cPt.y,iLen[i],m_crYUnitScaleColor,m_crYUnitScaleShadowColor);
	}
}
void CDescartesAxis::DrawYSawtooth(CDC *pDC,BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;
	for (int i=0;i<m_listYAxisScale.GetCount();i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listYAxisScale.GetAt(m_listYAxisScale.FindIndex(i));
		if (i==0)
		{
			cBegin=CPoint(pScaleData->m_ptAxisScale.x,(int)(pScaleData->m_ptAxisScale.y+m_dXAxisOneGap));
			cEnd=pScaleData->m_ptAxisScale;
			{
				CPen pen;
				pen.CreatePenIndirect(&m_logpenYAxisTenthScale);
				CPen *cOldP=pDC->SelectObject(&pen);
				for (int i=0;i<10;i++)
				{
					int iGapVal=GetIntVal((float)((float)m_dYAxisOneGap/10.0*i));
					CPoint cPt(cBegin.x,cEnd.y+iGapVal);
					if((cPt.y < m_rectYAxis.top)||(cPt.y > m_rectYAxis.bottom))
						continue;
					cPt.Offset(ptOffset);
					pDC->MoveTo(cPt.x-1,cPt.y);
					pDC->LineTo(cPt.x - (long)(fZoomRatio * m_iYAxisTenthScaleLineLen),cPt.y);
				}
				pDC->SelectObject(cOldP);
				pen.DeleteObject();
				continue;
			}
		}
		else
		{
			CAxisScaleData *odNewData=(CAxisScaleData *)m_listYAxisScale.GetAt(m_listYAxisScale.FindIndex(i-1));
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
		cEnd=CPoint(pScaleData->m_ptAxisScale.x,(int)(pScaleData->m_ptAxisScale.y-m_dYAxisOneGap));
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

/***********************************************************************
关于X轴的绘制
***********************************************************************/
long CDescartesAxis::GetBaseOneGapWidth()
{
	return m_iMinOneGapWidth;
}

long CDescartesAxis::GetMinOneGapWidth()
{
	return m_iMinOneGapWidth;
}

void CDescartesAxis::InitXAxisDef()
{
	m_listXAxisScale.EndIt();
}

void CDescartesAxis::EndXAxisDef()
{
	m_listXAxisScale.EndIt();
}


long CDescartesAxis::Get60CarryVal(int iVal)
{
	int iStep=6;
	int iStep1=60;
	if (iVal < iStep)
	{
		return iStep;
	}
	for (int i=1;;i++)
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
	int iMul=1;
	ff=lNowVal/lGapVal;
	ff1=(float)((int)ff);
	if(ff-ff1<0.99)
		iMul=(int)ff1;
	else
		iMul=(int)ff1+1;
	double fb=0;
	fb=lNowVal-(lNowVal - iMul*lGapVal);
	return fb;
}

void CDescartesAxis::ResetXAxisDef()
{
	EndXAxisDef();
	int iOneGapPt=GetBaseOneGapWidth();//得到基本的一个Gap的间距
	int iHeight=m_rectXAxis.Width();//得到整个工作区域的高度
	//得到需要计算数据的间隔
	double dXAxisRangeVal=m_dXAxisMaxVal-m_dXAxisMinVal;
	
	double dGapNum=iHeight/iOneGapPt;
	int iGapNumTemp=0;
	iGapNumTemp=FloatValToInt(dGapNum);
	if(iGapNumTemp>GetXAxisMaxUnitCount())
		dGapNum=(float)GetXAxisMaxUnitCount();////获得最大间隔数
	double dAxisUnitGapVal=dXAxisRangeVal/dGapNum;//得到每个间隔的数值
	if(dGapNum<=0.0001)
		return ;

	double dLegalGapVal=0;
	double dGapVal=0;
	int iCircleCounts=0;
	for(;iCircleCounts<50;iCircleCounts++)
	{
		dLegalGapVal=MakeFloatGapValLegal(dAxisUnitGapVal,dGapVal);//得到最可能的Mv数
		//if(dLegalGapVal>1) break;
		dGapNum=dXAxisRangeVal/dGapVal;		////最大可能的间隔数
		iGapNumTemp=FloatValToInt(dGapNum);
		dGapNum=(float)iGapNumTemp ;
		int iNowGapPt=(int)(iHeight/dGapNum);	////最小可能的每个间隔值
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
		int iNowGapPt=(int)(iHeight/dGapNum);
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
		for (int i=0;i<=iGapNumTemp;i++)
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
	int iWidth=m_rectXAxis.Width();
	double iVal=(m_dXAxisMaxVal-m_dXAxisMinVal);
	m_dXAxisOneGap=iGap*(float)iWidth/iVal;
}

void CDescartesAxis::ResetOneXAxisDef(double lVal)
{
	int iWidth=m_rectXAxis.Width();
	double iVal=(m_dXAxisMaxVal-m_dXAxisMinVal);//FloatValToInt
	double f=m_rectXAxis.left+(lVal-m_dXAxisMinVal)*(float)iWidth/iVal;
	int x=FloatValToInt(f);
	CAxisScaleData *pScaleData=new CAxisScaleData();
	int iIntegeralBeginPalace=0;//GetIntegeralBeginPalace();
	f=lVal-iIntegeralBeginPalace;
	pScaleData->FillIt(f,CPoint(x,m_rectXAxis.top+BOTTOMADD));//BOTTOMADD = 2
	m_listXAxisScale.AddTail(pScaleData);
}
void CDescartesAxis::DrawXAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio,CPoint ptOffset)
{
	CPoint pt;
//	pt.x = (long)(fZoomRatio * pScaleData->m_ptAxisScale.x);
//	pt.y = (long)(fZoomRatio * (m_rectWorkArea.top+m_iWorkAreaBorderShadow) );
	pt.x = pScaleData->m_ptAxisScale.x;
	pt.y = m_rectWorkArea.top + (long)(fZoomRatio * m_iWorkAreaBorderShadow) ;
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
	char pszString[128];
	sprintf(pszString,"%.4f",pScaleData->m_dAxisScaleVal);
	int iLen=strlen(pszString);
	double f=0;
	if(pszString[iLen-1]>='5')
	{
		pszString[iLen-1]=0;
		f=atof(pszString);
		if(f>=0.0001)
			f=f+0.001;
		else 
			f=f-0.001;
		sprintf(pszString,"%.4f",f);
	}		
	chop(pszString);
	if(m_lAxisType==1)
	{
		CString strTT=GetTimeVal((float)pScaleData->m_dAxisScaleVal);
		strcpy(pszString,strTT);
	}
	if(bAddUint==TRUE)
		lstrcat(pszString,m_strXAxisName);
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
		rect.top = pScaleData->m_ptAxisScale.y+(long)(fZoomRatio*m_iXAxisUnitScaleLineLen);
		rect.right = pScaleData->m_ptAxisScale.x+rect1.Width()/2+lIMM_2;
		rect.bottom = pScaleData->m_ptAxisScale.y + (long)(fZoomRatio*m_iXAxisUnitScaleLineLen) + rect1.Height();
		rect.OffsetRect(ptOffset);
		if(bReallyDraw)
			CmDrawTextRect(pDC,pszString,m_crXAxisScaleFontColor,rect,RGB(0,0,0),lf,TRANSPARENT,DT_VCENTER|DT_CENTER,0);
	}
	else
	{
		rect.left = pScaleData->m_ptAxisScale.x+lIMM_2*3/2;
		rect.top = pScaleData->m_ptAxisScale.y + (long)(fZoomRatio*m_iXAxisTenthScaleLineLen);
		rect.right = pScaleData->m_ptAxisScale.x+rect1.Width()+lIMM_2;
		rect.bottom = pScaleData->m_ptAxisScale.y + (long)(fZoomRatio*m_iXAxisUnitScaleLineLen) + rect1.Height();
		rect.OffsetRect(ptOffset);
		if(bReallyDraw)
			CmDrawTextRect(pDC,pszString,m_crXAxisScaleFontColor,rect,RGB(0,0,0),lf,TRANSPARENT,0,0);
	}
	return rect;
}
void CDescartesAxis::DrawXAxisName(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	int iLen=m_strXAxisName.GetLength();
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
	char cName[128];
	lstrcpy(cName,m_strXAxisName);
	CmDrawTextRect(pDC,(LPSTR)cName,m_crXAxisNameFontColor,&rect,RGB(255,0,0),
				   lf,TRANSPARENT,DT_BOTTOM|DT_RIGHT,0);
}

void CDescartesAxis::DrawXAxis(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	int iNum=m_listXAxisScale.GetCount();
	if(iNum<=0)
		return;
	CPen pen;
	m_logpenXAxisGridLine=InitLogPen(m_lXAxisGridLineStyle,1,m_crXAxisGridLineColor);	
	pen.CreatePenIndirect(&m_logpenXAxisGridLine);
	CPen *cOldB=pDC->SelectObject(&pen);
	double iIntgerEndPalace=m_dXAxisMaxVal;//GetIntegeralEndPalace();
	if(iIntgerEndPalace<0)iIntgerEndPalace=0;

	for (int i=0;i<iNum;i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData*)m_listXAxisScale.GetAt(m_listXAxisScale.FindIndex(i));
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
		int iStep=iNum;
		for (int i=0;i<iNum;i++)
		{
			CAxisScaleData *pScaleData=(CAxisScaleData*)m_listXAxisScale.GetAt(m_listXAxisScale.FindIndex(i));
		}
		BOOL bDrawUint=FALSE;
		for (i=0;i<iStep;i++)
		{
			CAxisScaleData *pScaleData=(CAxisScaleData*)m_listXAxisScale.GetAt(m_listXAxisScale.FindIndex(i));
			if(i==iStep-1)
			{
			//	if(cEndIntegerRect.left==-1) 
					//bDrawUint=TRUE;
			}
			if(pScaleData->m_ptAxisScale.x<m_rectXAxis.left || pScaleData->m_ptAxisScale.x>m_rectXAxis.right) 
				continue;
			if (pScaleData->m_ptAxisScale.x + m_iMinOneGapWidth > m_rectXAxis.right)
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
		
/*
	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_XAXIS_NAME)
		DrawXAxisName(pDC,fZoomRatio,ptOffset);
*/
}

void CDescartesAxis::DrawOneXSawtooth(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{
	CPen pen;
	pen.CreatePenIndirect(&m_logpenXAxisTenthScale);
	CPen *pOldPen=pDC->SelectObject(&pen);
	for (int i=0;i<10;i++)
	{
		int iGapVal=GetIntVal((float)((float)m_dXAxisOneGap/10.0*i));
	//	iGapVal = (long)(fZoomRatio * iGapVal);
		CPoint cPt(cBegin.x+iGapVal,cBegin.y);
		if( (cPt.x < m_rectXAxis.left) || (cPt.x > m_rectXAxis.right) ) 
			continue;
		cPt.Offset(ptOffset);
		pDC->MoveTo(cPt.x,cPt.y+(long)fZoomRatio);
		pDC->LineTo(cPt.x,cPt.y + (long)(fZoomRatio * m_iXAxisTenthScaleLineLen) );
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}
void CDescartesAxis::DrawOneXSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio,CPoint ptOffset)
{
	int iLen[2]={0,0};
	iLen[0] = (long)(fZoomRatio * m_iXAxisUnitScaleLineLen);
	iLen[1] = (long)(fZoomRatio * m_iXAxisHalfScaleLineLen);
	for (int i=0;i<2;i++)
	{
		int iGapVal=GetIntVal((float)((float)m_dXAxisOneGap/2.0*i));
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
	for (int i=0;i<m_listXAxisScale.GetCount();i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listXAxisScale.GetAt(m_listXAxisScale.FindIndex(i));
		if (i==0)
		{
			cBegin=CPoint((int)(pScaleData->m_ptAxisScale.x-m_dXAxisOneGap),pScaleData->m_ptAxisScale.y);
			cEnd=pScaleData->m_ptAxisScale;
		}
		else 
		{
			CAxisScaleData *odNewData=(CAxisScaleData *)m_listXAxisScale.GetAt(m_listXAxisScale.FindIndex(i-1));
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
		cEnd=CPoint((int)(pScaleData->m_ptAxisScale.x+m_dXAxisOneGap),pScaleData->m_ptAxisScale.y);
		cBegin=pScaleData->m_ptAxisScale;
		if (bKind==0)
			DrawOneXSawtooth(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
		else 
			DrawOneXSawtoothShadow(pDC,cBegin,cEnd,fZoomRatio,ptOffset);
	}
}

void CDescartesAxis::DrawIt(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	DrawAxisBack(pDC,fZoomRatio,ptOffset);
	
	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_WORKAREA)
		DrawArea(pDC,fZoomRatio,ptOffset);
	
	DrawXYAxisRect(pDC,fZoomRatio,ptOffset);	
	DrawYAxis(pDC,fZoomRatio,ptOffset);
	DrawXAxis(pDC,fZoomRatio,ptOffset);

	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_AXISCENTER)
		DrawAxisCenter(pDC,fZoomRatio,ptOffset);

	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_XAXIS_NAME)
		DrawXAxisName(pDC,fZoomRatio,ptOffset);

	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_YAXIS_NAME)
		DrawYAxisName(pDC,fZoomRatio,ptOffset);

	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_AXISTITLE)
		DrawAxisTitle(pDC,fZoomRatio,ptOffset);

	if(m_lAxisDrawStyle & DESCARTESAXISDRAW_AXISBODER)
		DrawFrame(pDC,fZoomRatio,ptOffset);
	
}

void CDescartesAxis::DrawAxisTitle(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	int iLen=m_strAxisTitle.GetLength();
	CFont CF;
	LOGFONT lf = m_lfAxisTitleFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);

	long lfWidth = GetCharWidthByLogfont2(pDC,lf);
	
	iLen = lfWidth * iLen / 2;
	iLen = abs(iLen);
	int iWidth = 0;
	CRect rect;
	rect.left = m_rectBorder.left;
	rect.top = m_rectBorder.top ;
	rect.right = m_rectBorder.right;
	rect.bottom = m_rectWorkArea.top;

	CPoint ptCenter = rect.CenterPoint();
	rect.left = ptCenter.x - iLen;
	rect.right = ptCenter.x + iLen;

	rect.OffsetRect(ptOffset);

	char cName[128];
	lstrcpy(cName,m_strAxisTitle);
	CmDrawTextRect(pDC,(LPSTR)cName,m_crAxisTitleFont,&rect,RGB(0,0,0),
				   lf,TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}

void CDescartesAxis::DrawFrame(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rect = m_rectBorder;
	rect.OffsetRect(ptOffset);
	Draw3dRectBorder(pDC,&rect,m_iFrameShadow,m_crFrameLeftTopColor,m_crFrameRightBottomColor);
}
//修改工作区域
void CDescartesAxis::ModifyWorkArea(CRect* cRect,BOOL bInit,float fZoomRatio,CPoint ptOffset)
{
	CRect cNewRect=cRect[0];
	m_rectBorder=cNewRect;

	m_rectXAxis.bottom=cNewRect.bottom - (long)(fZoomRatio*m_iBottomGap);
	m_rectXAxis.top=m_rectXAxis.bottom - (long)(fZoomRatio * m_iXAxisAreaHeight);
	
	m_rectWorkArea.bottom=m_rectXAxis.top;
	m_rectWorkArea.top = cNewRect.top + (long)(fZoomRatio*m_iTopGap);
	
	m_rectYAxis.left = cNewRect.left + (long)(fZoomRatio*m_iLeftGap);
	m_rectYAxis.right = m_rectYAxis.left + (long)(fZoomRatio*m_iYAxisAreaWidth);

	m_rectWorkArea.left=m_rectYAxis.right;
	m_rectWorkArea.right=cNewRect.right - (long)(fZoomRatio*m_iRightGap);

	m_rectXAxis.left=m_rectWorkArea.left;
	m_rectXAxis.right=m_rectWorkArea.right;

	m_rectYAxis.top=m_rectWorkArea.top;
	m_rectYAxis.bottom=m_rectWorkArea.bottom;

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
	Draw3dRectBorder(pDC,&rect,m_iWorkAreaBorderShadow,m_crWorkAreaBorderLeftTopColor,m_crWorkAreaBorderRightBottomColor);
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

//	Draw3dRectBorder(pDC,&rect,(long)(fZoomRatio*m_iWorkAreaBorderShadow),m_crWorkAreaBorderLeftTopColor,m_crWorkAreaBorderRightBottomColor);
	Draw3dRectByMe(pDC,&rect,(long)(fZoomRatio*m_iWorkAreaBorderShadow),m_crWorkAreaBorderLeftTopColor,m_crWorkAreaBorderRightBottomColor,m_crWorkAreaBkColor);

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
	pointCenter.y=FloatValToInt(f);//(int)();

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
	int iHeight=rectWork.Height();
	double fValYOneGap=iHeight/(fYMaxValue-fYMinValue);///Y轴实际坐标与实际值的比率
	///////////////////////////////////////////////
	fXMaxValue=m_dXAxisMaxVal;
	fXMinValue=m_dXAxisMinVal;
	int iWidth=rectWork.Width();
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

void CDescartesAxis::LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint)
{
	double f=fx*m_dOneXGapValue+m_ptCenterLogInDv.x;
	pPoint->x=FloatValToInt(f);
	f=-fy*m_dOneYGapValue+m_ptCenterLogInDv.y;
	pPoint->y=FloatValToInt(f);;
}
//从实际坐标获取实际坐标所代表的值
void CDescartesAxis::DevicePointToLogicPoint(CPoint point,double *fx,double *fy)
{
	*fy=-(point.y-m_ptCenterLogInDv.y) / m_dOneYGapValue;
	*fx=(point.x-m_ptCenterLogInDv.x) / m_dOneXGapValue;
}


/*///////////////////////////////////////////////////////////////
		下面定义图形的相关操作
*////////////////////////////////////////////////////////

double CDescartesAxis::GetFloatCarryVal(double fVal)
{
	double fStep = 0.0001;
	double fStep1 = fStep*10;
	for (int i=1;;i++)
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
	int iSet[4]={1,2,5,10};/////////
	for (int i=0;i<3;i++)
	{
		double fMin=fMulti*iSet[i];
		double fMax=iSet[i+1]*fMulti;
		if ((fTmp>=fMin)&&(fTmp<fMax))
		{
			lVal=fMulti*iSet[i];
			return fMulti*iSet[i+1];
		}
	}
	return iSet[i+1]*fMulti;
}

void CDescartesAxis::AdjustAxisDef(CRect rectArea,BOOL bAdjust,float fZoomRatio,CPoint ptOffset)
{
	int iH=0,iW=0;
	iH=rectArea.Height();
	iW=rectArea.Width();
	iH=iH-m_iBottomGap-m_iTopGap-m_iXAxisAreaHeight;
	iW=iW-m_iLeftGap-m_iRightGap-m_iYAxisAreaWidth;
	if(iW<=0)
		iW=20;
	if(iH<=0)
		iH=20;
	rectArea.bottom=rectArea.top+iH + m_iBottomGap + m_iTopGap+m_iXAxisAreaHeight;
	rectArea.right =rectArea.left+iW +m_iLeftGap+ m_iRightGap+m_iYAxisAreaWidth;

	if (m_bAxisXYUnitLock)
	{
		iH=rectArea.Height();
		iW=rectArea.Width();
		iH=iH-m_iBottomGap-m_iTopGap-m_iXAxisAreaHeight;
		iW=iW-m_iLeftGap-m_iRightGap-m_iYAxisAreaWidth;

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
		return "0";

	float fMinute = fTimeVal / 60;
	int   iMinute = FloatValToInt(fMinute,0);
	float fHour   = fMinute  / 60;
	int   iHour   = FloatValToInt(fHour,0);
	iMinute = iMinute - iHour * 60 ;
	CString strTime="";
	CString strTemp="";
	BOOL bTrue=FALSE;
	if(iHour>0)
	{
		strTemp.Format("%d:",iHour);
		bTrue=TRUE;
	}
	strTime += strTemp;
	if(iMinute>0)
	{
		strTemp.Format("%d:",iMinute);
		bTrue=TRUE;
	}
	else
	{
		if(iHour)	
		{
			bTrue=TRUE;
			strTemp="0:";
		}
		else  
		{
			strTemp="";
			bTrue=FALSE;
		}
	}
	strTime += strTemp;
	iMinute = FloatValToInt(fMinute,0);
	int iSecond = FloatValToInt(fTimeVal,0);
	float fMS=fTimeVal - iSecond;
	iSecond = iSecond - iMinute * 60 ;
	if(iSecond>0)
	{
		bTrue=TRUE;
		strTemp.Format("%d\'",iSecond);
	}
	else
	{
		strTemp="0\'";
		bTrue=TRUE;
	}
	strTime += strTemp;
	strTemp="";
	if(fMS>=0.001)
	{
		strTemp.Format("%.3f",fMS);
		strTemp=strTemp.Right(3);
		strTemp+="\'\'";
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
	int nWidth = rect1.Width();
	int nHeight = rect2.Height();
	CRect rectangle1,rectangle2,rectangle3,rectangle4;
	int lR1,lG1,lB1,lR2,lG2,lB2;
	COLORREF color1,color2;
	lR1 = lR2 = GetRValue(m_crWorkAreaBkColor);
	lG1 = lG2 = GetGValue(m_crWorkAreaBkColor);
	lB1 = lB2 = GetBValue(m_crWorkAreaBkColor);
	for(int i=0;i<nWidth;i++)
	{
		rectangle1.SetRect(rect1.left+i,rect1.top,rect1.left+i+1,rect1.bottom);
		rectangle3.SetRect(rect1.left+i,rect1.bottom,rect1.left+i+1,rect2.bottom);
//		rectangle3.SetRect(rect1.left+i,rect1.bottom,rect1.left+i+1,rect2.bottom-tan(pi / 4.5)*i);
		lR1 = lR1+MulDiv(i,(255-lR1)*1/7,nWidth);
		lB1 = lB1+MulDiv(i,(255-lB1)*1/7,nWidth);
		lG1 = lG1+MulDiv(i,(255-lG1)*1/7,nWidth);
		
		//		ColorB = 255-MulDiv(i,255,nWidth);
		//		color = RGB(ColorR,ColorG,ColorB);
		color1 = RGB(lR1,lG1,lB1);
		pDC->FillSolidRect(&rectangle3,color1);
		pDC->FillSolidRect(&rectangle1,color1);
		
	}
	for(int j=0;j<nHeight;j++)
	{
		rectangle2.SetRect(rect2.left,rect2.bottom-j-1,rect2.right+1,rect2.bottom-j);
		rectangle4.SetRect(rect1.left+tan(pi / 3.5)*j,rect2.bottom-j-1,rect2.left,rect2.bottom-j);
		lR2 = lR2+MulDiv(j,(255-lR2)*1/7,nHeight);
		lB2 = lB2+MulDiv(j,(255-lB2)*1/7,nHeight);
		lG2 = lG2+MulDiv(j,(255-lG2)*1/7,nHeight);
		color2 = RGB(lR2,lG2,lB2);
		pDC->FillSolidRect(&rectangle2,color2);
		pDC->FillSolidRect(&rectangle4,color2);
	}

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


STDMETHODIMP_(ULONG) CDescartesAxis::XDescartesAxisInterface::AddRef()
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDescartesAxis::XDescartesAxisInterface::Release()
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	return pThis->ExternalRelease();
}

STDMETHODIMP CDescartesAxis::XDescartesAxisInterface::QueryInterface(REFIID iid,LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisMinSawGapWidth(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetXAxisMinSawGapWidth();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisMinSawGapWidth(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetXAxisMinSawGapWidth(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisMinSawGapHeight(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetYAxisMinSawGapHeight();

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisMinSawGapHeight(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetYAxisMinSawGapHeight(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisType(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetXAxisType();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisType(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	 pThis->SetXAxisType(nValue);

	 return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisMaxUnitCount(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetXAxisMaxUnitCount(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisMaxUnitCount(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetXAxisMaxUnitCount();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisMaxUnitCount(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetYAxisMaxUnitCount(nValue);

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisMaxUnitCount(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetYAxisMaxUnitCount();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisXYUnitLock(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetAxisXYUnitLock(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetAxisXYUnitLock(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetAxisXYUnitLock();

    return 0;
}

//坐标系统的绘制类型,2005.08.12添加
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisDrawStyle(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	
	pThis->m_lAxisDrawStyle = nValue;
	
	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetAxisDrawStyle(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	
	*nValue = pThis->m_lAxisDrawStyle;
	
    return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisDrawStyleBit(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);

	pThis->m_lAxisDrawStyle |= nValue;
	
	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::ClearAxisDrawStyleBit(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);

	pThis->m_lAxisDrawStyle &= (~nValue);
	
	return 0;
}


STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisTextDrawStyle(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetXAxisTextDrawStyle(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisTextDrawStyle(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetXAxisTextDrawStyle();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisTitle(BSTR bstrValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);

	pThis->SetAxisTitle(bstrValue);

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetAxisTitle(BSTR *pbstrValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CString sAxisTitle;
	sAxisTitle = pThis->GetAxisTitle();
	*pbstrValue = sAxisTitle.AllocSysString();
	
	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisTitleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT   m_lfAxisTitleFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfAxisTitleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet
		,(BYTE)lfOutPrecision,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->SetAxisTitleFont(m_lfAxisTitleFont);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetAxisTitleFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT m_lfAxisTitleFont;
	CString sFaceName;
	m_lfAxisTitleFont = pThis->GetAxisTitleFont();
	*lfHeight = m_lfAxisTitleFont.lfHeight;
	*lfWidth = m_lfAxisTitleFont.lfWidth;
	*lfOrientation = m_lfAxisTitleFont.lfOrientation;
	*lfWeight = m_lfAxisTitleFont.lfWeight;
	*lfItalic = (long)m_lfAxisTitleFont.lfItalic;
	*lfUnderline = (long)m_lfAxisTitleFont.lfUnderline;
	*lfStrikeOut = (long)m_lfAxisTitleFont.lfStrikeOut;
	*lfCharSet = (long)m_lfAxisTitleFont.lfCharSet;
	*lfOutPrecision = (long)m_lfAxisTitleFont.lfOutPrecision;
	*lfClipPrecision = (long)m_lfAxisTitleFont.lfClipPrecision;
	*lfQuality = (long)m_lfAxisTitleFont.lfQuality;
	*lfPitchAndFamily = (long)m_lfAxisTitleFont.lfPitchAndFamily;
	sFaceName = m_lfAxisTitleFont.lfFaceName;
	*lfFaceName = sFaceName.AllocSysString();

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisTitleFontColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crTitleColor;
	m_crTitleColor = (COLORREF)nValue;
	pThis->SetAxisTitleFontColor(m_crTitleColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetAxisTitleFontColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crAxisTitleFontColor;
	m_crAxisTitleFontColor = pThis->GetAxisTitleFontColor();
	*nValue = (long)m_crAxisTitleFontColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisBackColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crBackColor;
	m_crBackColor = (COLORREF)nValue;
	pThis->SetAxisBackColor(m_crBackColor);

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetAxisBackColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crBackColor;
	m_crBackColor = pThis->GetAxisBackColor();
    *nValue = (long)m_crBackColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetWorkAreaBkColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crBKColor;
	m_crBKColor = (COLORREF)nValue;
	pThis->SetWorkAreaBkColor(m_crBKColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetWorkAreaBkColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crBKColor;
	m_crBKColor = pThis->GetWorkAreaBkColor();
	*nValue = (long)m_crBKColor;

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetWorkAreaBorderLeftTopColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = (COLORREF)nValue;
	pThis->SetWorkAreaBorderLeftTopColor(m_crLeftTopColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetWorkAreaBorderLeftTopColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = pThis->GetWorkAreaBorderLeftTopColor();
	*nValue = (long)m_crLeftTopColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetWorkAreaBorderRightBottomColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crRightBottomColor;
	m_crRightBottomColor = (COLORREF)nValue;
	pThis->SetWorkAreaBorderRightBottomColor(m_crRightBottomColor);

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetWorkAreaBorderRightBottomColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crRightBottomColor;
	m_crRightBottomColor = pThis->GetWorkAreaBorderRightBottomColor();
	*nValue = (long)m_crRightBottomColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetWorkAreaBorderShadow(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetWorkAreaBorderShadow(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetWorkAreaBorderShadow(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);

	*nValue = pThis->GetWorkAreaBorderShadow();

	return 0;
}

//坐标系统边框的颜色
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetFrameLeftTopColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	
	pThis->SetFrameLeftTopColor(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetFrameLeftTopColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	
	*nValue = pThis->GetFrameLeftTopColor();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetFrameRightBottomColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	
	pThis->SetFrameRightBottomColor(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetFrameRightBottomColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	
	*nValue = pThis->GetFrameRightBottomColor();
	
	return 0;
}

//坐标系统边框边界阴影
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetFrameShadow(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	
	pThis->SetFrameShadow(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetFrameShadow(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	
	*nValue = pThis->GetFrameShadow();

	return 0;
}


STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYUnitScaleColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYUnitScaleColor;
	m_crYUnitScaleColor = (COLORREF)nValue;
	pThis->SetYUnitScaleColor(m_crYUnitScaleColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYUnitScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYUnitScaleColor;
	m_crYUnitScaleColor = pThis->GetYUnitScaleColor();
	*nValue = (long)m_crYUnitScaleColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYUnitScaleShadowColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crShadowColor;
	m_crShadowColor = (COLORREF)nValue;
	pThis->SetYUnitScaleShadowColor(m_crShadowColor);

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYUnitScaleShadowColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crShadowColor;
	m_crShadowColor = pThis->GetYUnitScaleShadowColor();
	*nValue = (long)m_crShadowColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT   m_lfYAxisScaleFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfYAxisScaleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->SetYAxisScaleFont(m_lfYAxisScaleFont);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisScaleFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT m_lfYAxisScaleFont;
	CString sFaceName;
	m_lfYAxisScaleFont = pThis->GetYAxisScaleFont();
	*lfHeight = m_lfYAxisScaleFont.lfHeight;
	*lfWidth = m_lfYAxisScaleFont.lfWidth;
	*lfOrientation = m_lfYAxisScaleFont.lfOrientation;
	*lfWeight = m_lfYAxisScaleFont.lfWeight;
	*lfItalic = (long)m_lfYAxisScaleFont.lfItalic;
	*lfUnderline = (long)m_lfYAxisScaleFont.lfUnderline;
	*lfStrikeOut = (long)m_lfYAxisScaleFont.lfStrikeOut;
	*lfCharSet = (long)m_lfYAxisScaleFont.lfCharSet;
	*lfOutPrecision = (long)m_lfYAxisScaleFont.lfOutPrecision;
	*lfClipPrecision = (long)m_lfYAxisScaleFont.lfClipPrecision;
	*lfQuality = (long)m_lfYAxisScaleFont.lfQuality;
	*lfPitchAndFamily = (long)m_lfYAxisScaleFont.lfPitchAndFamily;
	sFaceName = m_lfYAxisScaleFont.lfFaceName;
	*lfFaceName = sFaceName.AllocSysString();

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisName(BSTR bstrName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	char pszYAxisName[MAX_PATH];
	memset(pszYAxisName,0,MAX_PATH);
	BSTRToAnsiStr(bstrName,pszYAxisName);
	pThis->SetYAxisName(pszYAxisName);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisName(BSTR *pbstrName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CString sYAxisName;
	sYAxisName = pThis->GetYAxisName();
	*pbstrName = sYAxisName.AllocSysString();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT   m_lfAxisNameFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfAxisNameFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->SetYAxisNameFont(m_lfAxisNameFont);

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisNameFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT m_lfYAxisNameFont;
	CString sFaceName;
	m_lfYAxisNameFont = pThis->GetYAxisNameFont();
	*lfHeight = m_lfYAxisNameFont.lfHeight;
	*lfWidth = m_lfYAxisNameFont.lfWidth;
	*lfOrientation = m_lfYAxisNameFont.lfOrientation;
	*lfWeight = m_lfYAxisNameFont.lfWeight;
	*lfItalic = (long)m_lfYAxisNameFont.lfItalic;
	*lfUnderline = (long)m_lfYAxisNameFont.lfUnderline;
	*lfStrikeOut = (long)m_lfYAxisNameFont.lfStrikeOut;
	*lfCharSet = (long)m_lfYAxisNameFont.lfCharSet;
	*lfOutPrecision = (long)m_lfYAxisNameFont.lfOutPrecision;
	*lfClipPrecision = (long)m_lfYAxisNameFont.lfClipPrecision;
	*lfQuality = (long)m_lfYAxisNameFont.lfQuality;
	*lfPitchAndFamily = (long)m_lfYAxisNameFont.lfPitchAndFamily;
	sFaceName = m_lfYAxisNameFont.lfFaceName;
	*lfFaceName = sFaceName.AllocSysString();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisNameFontColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYAxisNameFontColor;
	m_crYAxisNameFontColor = (COLORREF)nValue;
	pThis->SetYAxisNameFontColor(m_crYAxisNameFontColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisNameFontColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYAxisNameFontColor;
	m_crYAxisNameFontColor = pThis->GetYAxisNameFontColor();
	*nValue = (long)m_crYAxisNameFontColor;

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisScaleFontColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYAxisScaleFontColor;
	m_crYAxisScaleFontColor = (COLORREF)nValue;
	pThis->SetYAxisScaleFontColor(m_crYAxisScaleFontColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisScaleFontColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYAxisScaleFontColor;
	m_crYAxisScaleFontColor = pThis->GetYAxisScaleFontColor();
	*nValue = (long)m_crYAxisScaleFontColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisGridLineStyle(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetYAxisGridLineStyle(nValue);

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisGridLineStyle(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetYAxisGridLineStyle();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisGridLineColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYAxisGridLineColor;
	m_crYAxisGridLineColor = (COLORREF)nValue;
	pThis->SetYAxisGridLineColor(m_crYAxisGridLineColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisGridLineColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYAxisGridLineColor;
	m_crYAxisGridLineColor = pThis->GetYAxisGridLineColor();
	*nValue = (long)m_crYAxisGridLineColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisTenthScaleColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYAxisTenthScaleColor;
	m_crYAxisTenthScaleColor = (COLORREF)nValue;
	pThis->SetYAxisTenthScaleColor(m_crYAxisTenthScaleColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisTenthScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crYAxisTenthScaleColor;
	m_crYAxisTenthScaleColor = pThis->GetYAxisTenthScaleColor();
	*nValue = (long)m_crYAxisTenthScaleColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisAreaWidth(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetYAxisAreaWidth(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisAreaWidth(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetYAxisAreaWidth();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisUnitScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetYAxisUnitScaleLineLen(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisUnitScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetYAxisUnitScaleLineLen();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisHalfScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetYAxisHalfScaleLineLen(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisHalfScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetYAxisHalfScaleLineLen();
	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetYAxisTenthScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetYAxisTenthScaleLineLen(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisTenthScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetYAxisTenthScaleLineLen();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXUnitScaleColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crXUnitScaleColor;
	m_crXUnitScaleColor = (COLORREF)nValue;
	pThis->SetXUnitScaleColor(m_crXUnitScaleColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXUnitScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crXUnitScaleColor;
	m_crXUnitScaleColor = pThis->GetXUnitScaleColor();
	*nValue = (long)m_crXUnitScaleColor;

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXUnitScaleShadowColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crXUnitScaleShadowColor;
	m_crXUnitScaleShadowColor = (COLORREF)nValue;
	pThis->SetXUnitScaleShadowColor(m_crXUnitScaleShadowColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXUnitScaleShadowColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crXUnitScaleShadowColor;
	m_crXUnitScaleShadowColor = pThis->GetXUnitScaleShadowColor();
	*nValue = (long)m_crXUnitScaleShadowColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT   m_lfXAxisScaleFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfXAxisScaleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->SetXAxisScaleFont(m_lfXAxisScaleFont);

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisScaleFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT m_lfXAxisScaleFont;
	CString sFaceName;
	m_lfXAxisScaleFont = pThis->GetXAxisScaleFont();
	*lfHeight = m_lfXAxisScaleFont.lfHeight;
	*lfWidth = m_lfXAxisScaleFont.lfWidth;
	*lfOrientation = m_lfXAxisScaleFont.lfOrientation;
	*lfWeight = m_lfXAxisScaleFont.lfWeight;
	*lfItalic = (long)m_lfXAxisScaleFont.lfItalic;
	*lfUnderline = (long)m_lfXAxisScaleFont.lfUnderline;
	*lfStrikeOut = (long)m_lfXAxisScaleFont.lfStrikeOut;
	*lfCharSet = (long)m_lfXAxisScaleFont.lfCharSet;
	*lfOutPrecision = (long)m_lfXAxisScaleFont.lfOutPrecision;
	*lfClipPrecision = (long)m_lfXAxisScaleFont.lfClipPrecision;
	*lfQuality = (long)m_lfXAxisScaleFont.lfQuality;
	*lfPitchAndFamily = (long)m_lfXAxisScaleFont.lfPitchAndFamily;
	sFaceName = m_lfXAxisScaleFont.lfFaceName;
	*lfFaceName = sFaceName.AllocSysString();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisName(BSTR bstrName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	char pszName[MAX_PATH];
	memset(pszName,0,MAX_PATH);
	BSTRToAnsiStr(bstrName,pszName);

//	CString strTemp = bstrName;

	pThis->SetXAxisName(pszName);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisName(BSTR *pbstrName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CString sXAxisName;
	sXAxisName = pThis->GetXAxisName();
	*pbstrName = sXAxisName.AllocSysString();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT   m_lfXAxisNameFont;
    char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfXAxisNameFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->SetXAxisNameFont(m_lfXAxisNameFont);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisNameFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	LOGFONT m_lfXAxisNameFont;
	CString sFaceName;
	m_lfXAxisNameFont = pThis->GetXAxisNameFont();
	*lfHeight = m_lfXAxisNameFont.lfHeight;
	*lfWidth = m_lfXAxisNameFont.lfWidth;
	*lfOrientation = m_lfXAxisNameFont.lfOrientation;
	*lfWeight = m_lfXAxisNameFont.lfWeight;
	*lfItalic = (long)m_lfXAxisNameFont.lfItalic;
	*lfUnderline = (long)m_lfXAxisNameFont.lfUnderline;
	*lfStrikeOut = (long)m_lfXAxisNameFont.lfStrikeOut;
	*lfCharSet = (long)m_lfXAxisNameFont.lfCharSet;
	*lfOutPrecision = (long)m_lfXAxisNameFont.lfOutPrecision;
	*lfClipPrecision = (long)m_lfXAxisNameFont.lfClipPrecision;
	*lfQuality = (long)m_lfXAxisNameFont.lfQuality;
	*lfPitchAndFamily = (long)m_lfXAxisNameFont.lfPitchAndFamily;
	sFaceName = m_lfXAxisNameFont.lfFaceName;
	*lfFaceName = sFaceName.AllocSysString();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisNameFontColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crXAxisNameFontColor;
	m_crXAxisNameFontColor = (COLORREF)nValue;
	pThis->SetXAxisNameFontColor(m_crXAxisNameFontColor);

	return 0;
}
STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisNameFontColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface)
	COLORREF m_crXAxisNameFontColor;
	m_crXAxisNameFontColor = pThis->GetXAxisNameFontColor();
	*nValue = (long)m_crXAxisNameFontColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisScaleFontColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crXAxisScaleFontColor;
	m_crXAxisScaleFontColor = (COLORREF)nValue;
	pThis->SetXAxisScaleFontColor(m_crXAxisScaleFontColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisScaleFontColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crXAxisScaleFontColor;
	m_crXAxisScaleFontColor = pThis->GetXAxisScaleFontColor();
	*nValue = (long)m_crXAxisScaleFontColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisGridLineStyle(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetXAxisGridLineStyle(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisGridLineStyle(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetXAxisGridLineStyle();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisGridLineColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = (COLORREF)nValue;
	pThis->SetXAxisGridLineColor(m_crLeftTopColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisGridLineColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = pThis->GetXAxisGridLineColor();
	*nValue = (long)m_crLeftTopColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisTenthScaleColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crXAxisTenthScaleColor;
	m_crXAxisTenthScaleColor = (COLORREF)nValue;
	pThis->SetXAxisTenthScaleColor(m_crXAxisTenthScaleColor);
	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisTenthScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crXAxisTenthScaleColor;
	m_crXAxisTenthScaleColor = pThis->GetXAxisTenthScaleColr();
	*nValue = (long)m_crXAxisTenthScaleColor;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisAreaHeight(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetXAxisAreaHeight(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisAreaHeight(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetXAxisAreaHeight();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisUnitScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetXAxisUnitScaleLineLen(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisUnitScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetXAxisUnitScaleLineLen();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisHalfScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetXAxisHalfScaleLineLen(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisHalfScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetXAxisHalfScaleLineLen();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetXAxisTenthScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetXAxisTenthScaleLineLen(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisTenthScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetXAxisTenthScaleLineLen();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisCenterLineWidth(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetAxisCenterLineWidth(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetAxisCenterLineWidth(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetAxisCenterLineWidth();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisCenterLineType(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetAxisCenterLineType(nValue);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetAxisCenterLineType(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	*nValue = pThis->GetAxisCenterLineType();

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetAxisCenterColor(long nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crAxisCenterColor;
	m_crAxisCenterColor = (COLORREF)nValue;
	pThis->SetAxisCenterColor(m_crAxisCenterColor);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetAxisCenterColor(long *nValue)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	COLORREF m_crAxisCenterColor;
	m_crAxisCenterColor = pThis->GetAxisCenterColor();
	*nValue = (long)m_crAxisCenterColor;

	return 0;
}


STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetMinMaxVal(double xMin,double yMin,double xMax,double yMax,long nReserved)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->SetXYAxisMinMaxVal(xMin,yMin,xMax,yMax);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->GetAxisMinMaxVal(xMin,yMin,xMax,yMax);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::SetBoder(long left, long top, long right, long bottom)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CRect rectW;
	rectW = CRect(left, top, right, bottom);
	pThis->SetBorder(rectW);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetBoder(long FAR*left, long FAR*top, long FAR*right, long FAR*bottom)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CRect m_rectBoder;
	m_rectBoder = pThis->GetBorder();
	*left = m_rectBoder.left;
	*top = m_rectBoder.top;
	*right = m_rectBoder.right;
	*bottom = m_rectBoder.bottom;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetWorkArea(long FAR*left, long FAR*top, long FAR*right, long FAR*bottom)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CRect rectWorkArea;
	rectWorkArea = pThis->GetWorkArea();
	*left = rectWorkArea.left;
	*top = rectWorkArea.top;
	*right = rectWorkArea.right;
	*bottom = rectWorkArea.bottom;

	return 0;

}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetXAxisArea(long FAR*left, long FAR*top, long FAR*right, long FAR*bottom)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CRect rectXAxisArea;
	rectXAxisArea = pThis->GetXAxisArea();
	*left = rectXAxisArea.left;
	*top = rectXAxisArea.top;
	*right = rectXAxisArea.right;
	*bottom = rectXAxisArea.bottom;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::GetYAxisArea(long FAR*left, long FAR*top, long FAR*right, long FAR*bottom)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CRect rectYAxisArea;
	rectYAxisArea = pThis->GetYAxisArea();
	*left = rectYAxisArea.left;
	*top = rectYAxisArea.top;
	*right = rectYAxisArea.right;
	*bottom = rectYAxisArea.bottom;

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::ResetAxis()
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);

	double m_fAxisValue[4];
	m_fAxisValue[0]=9999;
	m_fAxisValue[1]=9999;
	m_fAxisValue[2]=-9999;
	m_fAxisValue[3]=-9999;
	
	if(fabs(m_fAxisValue[0]-9999)<0.001) 
		m_fAxisValue[0]=-5;
	if(fabs(m_fAxisValue[1]-9999)<0.001)
		m_fAxisValue[1]=5;
	if(fabs(m_fAxisValue[2]+9999)<0.001)
		m_fAxisValue[2]=-5;
	if(fabs(m_fAxisValue[3]+9999)<0.001)
		m_fAxisValue[3]=5;
	
	float fTemp = (float)((m_fAxisValue[2]-m_fAxisValue[0])*0.1f);
	m_fAxisValue[0]-=fTemp;
	m_fAxisValue[2]+=fTemp;
	
	fTemp = (float)((m_fAxisValue[3]-m_fAxisValue[1])*0.1f);
	m_fAxisValue[1] -=fTemp;
	m_fAxisValue[3] +=fTemp;	
	
	pThis->SetXYAxisMinMaxVal(m_fAxisValue[0],m_fAxisValue[1],m_fAxisValue[2],m_fAxisValue[3]);
//	pThis->ModifyWorkArea(&(pThis->m_rectAxis),1);
//	pThis->AdjustAxisDef(m_fAxisValue[0],m_fAxisValue[1],m_fAxisValue[2],m_fAxisValue[3],FALSE);	

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->DevicePointToLogicPoint(ptx,pty,x,y);
	
	return 0;
}


STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::LogicPointToDevicePoint(double x,double y,long FAR*ptx,long FAR*pty)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->LogicPointToDevicePoint(x,y,ptx,pty);
	
	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::DrawAxis(long lDC,float fZoomRatio,long xOffset,long yOffset)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CDC *pDC;
	pDC = (CDC*)lDC;
	CPoint pt;
	pt = CPoint(xOffset,yOffset);
	pThis->DrawIt(pDC,fZoomRatio,pt);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::ZoomIn1(float fRate)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->ZoomIn(fRate);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::ZoomIn2(double dMinX,double dMaxX,double dMinY,double dMaxY)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->ZoomIn(dMinX, dMaxX, dMinY, dMaxY);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::ZoomIn3(long left,long top,long right,long bottom)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	CRect rectW;
	rectW = CRect(left,top,right,bottom);
	pThis->ZoomIn(rectW);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::ZoomOut(float fRate)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->ZoomOut(fRate);

	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XDescartesAxisInterface::Move(float fXOffset,float fYOffset)
{
	METHOD_PROLOGUE(CDescartesAxis, DescartesAxisInterface);
	pThis->Move(fXOffset,fYOffset);

	return 0;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) CDescartesAxis::XAxisBaseInterface::AddRef()
{
	METHOD_PROLOGUE(CDescartesAxis, AxisBaseInterface);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDescartesAxis::XAxisBaseInterface::Release()
{
	METHOD_PROLOGUE(CDescartesAxis, AxisBaseInterface);
	return pThis->ExternalRelease();
}

STDMETHODIMP CDescartesAxis::XAxisBaseInterface::QueryInterface(REFIID iid,LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CDescartesAxis, AxisBaseInterface);
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(long) CDescartesAxis::XAxisBaseInterface::GetBoder(long *left, long *top, long *right, long *bottom)
{
	METHOD_PROLOGUE(CDescartesAxis, AxisBaseInterface);
	CRect rectBorder;
	rectBorder = pThis->m_rectBorder;
	*left = rectBorder.left;
	*top = rectBorder.top;
	*right = rectBorder.right;
	*bottom = rectBorder.bottom;
	
	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XAxisBaseInterface::GetWorkArea(long *left, long *top, long *right, long *bottom)
{
	METHOD_PROLOGUE(CDescartesAxis, AxisBaseInterface);
	CRect rectWorkArea;
	rectWorkArea = pThis->m_rectWorkArea;
	*left = rectWorkArea.left;
	*top = rectWorkArea.top;
	*right = rectWorkArea.right;
	*bottom = rectWorkArea.bottom;
	
	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XAxisBaseInterface::LogicPointToDevicePoint(double x,double y,long FAR*ptx,long FAR*pty)
{
	METHOD_PROLOGUE(CDescartesAxis, AxisBaseInterface);
	
	pThis->LogicPointToDevicePoint(x,y,ptx,pty);
	
	return 0;
}

STDMETHODIMP_(long) CDescartesAxis::XAxisBaseInterface::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
{
	METHOD_PROLOGUE(CDescartesAxis, AxisBaseInterface);
	pThis->DevicePointToLogicPoint(ptx,pty,x,y);
	
	return 0;
}


STDMETHODIMP_(long) CDescartesAxis::XAxisBaseInterface::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
{
	METHOD_PROLOGUE(CDescartesAxis, AxisBaseInterface);
	pThis->GetAxisMinMaxVal(xMin,yMin,xMax,yMax);
	
	return 0;
}
