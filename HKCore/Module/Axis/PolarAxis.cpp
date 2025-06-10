// PolarAxis.cpp : implementation file
//

#include "stdafx.h"
#include "PolarAxis.h"

#include "../../Module/API/GloblaDrawFunctions.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolarAxis

CPolarAxis::CPolarAxis()
{
	InitIt();	
}

CPolarAxis::~CPolarAxis()
{
	int i = 0;
}

// void CPolarAxis::LogicPointToDevicePoint(double x, double y, CPoint *pPoint, long nAxisIndex)
// {
// 
// }
// 
// void CPolarAxis::DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex)
// {
// 
// }
// 
// void CPolarAxis::GetAxisDrawArea(CRect &rcArea)
// {
// 
// }
// 
// void CPolarAxis::GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
// {
// 
// }

void CPolarAxis::LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex)
{
    //double f=fVal*m_dOneXGapValue;
    //nVal->x=FloatValToInt(f);
}

void CPolarAxis::DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex)
{
    //*fVal= nVal / m_dOneXGapValue;
}

void CPolarAxis::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{

}

CRect CPolarAxis::GetWorkArea()
{
	return m_rectWorkArea;
}

// void CPolarAxis::SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax)
// {
// 
// }


#ifdef USE_AXIS_CONFIG
void CPolarAxis::SetAxisConfig(CDataGroup *pAxisConfig)
{

}

void CPolarAxis::GetAxisConfig(CDataGroup *pAxisConfig)
{

}
#endif


void CPolarAxis::SetZoomCoefficient(long lVal)
{
	m_lZoomCoefficient = lVal;
}

long CPolarAxis::GetZoomCoefficient()
{
	return m_lZoomCoefficient;
}

//#########################################################
//定义极坐标的绘制区域信息
void CPolarAxis::SetPolarAxisBorder(CRect rectBorder)
{
	long lRulerHeight = 0;
	long lHeightGap = 0;
/*
	if (m_iAxisDrawType & POLARAXIS_RULER)
	{
		lRulerHeight = m_ruler.GetRulerHorHeight();
	}
*/
	lHeightGap = m_iVertMarginGapTop*2 + lRulerHeight;
	ASSERT (lHeightGap < rectBorder.Height());
	if (lHeightGap >= rectBorder.Height())
		return;
	
	m_rectBorder		=rectBorder;			//整个极坐标的坐标区域
	m_rectWorkArea		=rectBorder;			//极坐标的绘图区域
	m_rectWorkArea.left +=m_iHorzMarginGapLeft;
	m_rectWorkArea.right-=m_iHorzMarginGapRight;
	m_rectWorkArea.top	+=m_iVertMarginGapTop;
	m_rectWorkArea.bottom-=m_iVertMarginGapBottom;
/*
	if (m_iAxisDrawType & POLARAXIS_RULER)
	{
		m_rectWorkArea.bottom -= lRulerHeight;
	}
*/
	int iW=m_rectWorkArea.Width();
	int iH=m_rectWorkArea.Height();
	int iLen=iW;
	if(iW>iH)
		iLen=iH;
	iLen=iLen/2;
	CPoint ptC=m_rectWorkArea.CenterPoint();
	m_rectWorkArea=CRect(ptC.x-iLen,ptC.y-iLen,ptC.x+iLen,ptC.y+iLen);
	m_ptAxisCenter = m_rectWorkArea.CenterPoint();
#if 0	
	if (m_iAxisDrawType & POLARAXIS_RULER)
	{
		CRect rectTemp = m_rectWorkArea;
/*
		rectTemp.top = m_rectWorkArea.bottom + m_iVertMarginGap;
		rectTemp.bottom = rectTemp.top + lRulerHeight;
		m_ruler.ModifyRulerArea(rectTemp);
*/
		rectTemp = m_rectWorkArea;
		rectTemp.top = m_ptAxisCenter.y;
		rectTemp.bottom = rectTemp.top + lRulerHeight;
//		m_rulerCenter.ModifyRulerArea(rectTemp);
	}
#endif
}

CRect CPolarAxis::GetPolarAxisBorder()
{
	return m_rectBorder;
}

CRect CPolarAxis::GetPolarAxisWorkArea()
{
	return m_rectWorkArea;
}

CPoint CPolarAxis::GetPolarAxisCenterPoint()
{
	return m_ptAxisCenter;
}

void CPolarAxis::SetMarginGap(int iHorzGapLeft,int iVertGapTop,int iHorzGapRight,int iVertGapBottom)
{
	m_iHorzMarginGapLeft   = iHorzGapLeft;	 //坐标的水平空白区域
	m_iVertMarginGapTop    = iVertGapTop;		 //坐标的垂直空白区域	
	m_iHorzMarginGapRight  = iHorzGapRight;		
	m_iVertMarginGapBottom = iVertGapBottom;
}

long CPolarAxis::GetMarginGap(int iHorzGapLeft,int iVertGapTop,int iHorzGapRight,int iVertGapBottom)
{
	iHorzGapLeft   = m_iHorzMarginGapLeft;
	iVertGapTop    = m_iVertMarginGapTop;	
	iHorzGapRight  = m_iHorzMarginGapRight;
	iVertGapBottom = m_iVertMarginGapBottom;

	return 0;
}

void CPolarAxis::ResetPolarAxis()
{
	int iRadius=m_rectWorkArea.Height() / 2 ;
	for(int i=0;i<m_iCircleAxisCount;i++)
	{
		m_fCircleValOneGap[i] = m_fCircleUnitValue[i] / iRadius;
	}
}

void CPolarAxis::ResetPolarAxis(int iCircleUnitIndex)
{
	if(iCircleUnitIndex<0 || iCircleUnitIndex>=POLORAXIS_AXISCOUNT)return ;
	int iRadius=m_rectWorkArea.Height() / 2 ;
	m_fCircleValOneGap[iCircleUnitIndex] = m_fCircleUnitValue[iCircleUnitIndex] / iRadius;
}

long CPolarAxis::SetAxisTitleFont(LOGFONT lfFont)
{
	m_lfPolarAxisTitleFont = lfFont;
	return 0;
}

LOGFONT CPolarAxis::GetAxisTitleFont()
{
	return m_lfPolarAxisTitleFont;
}

long CPolarAxis::SetAngleUnitFont(LOGFONT lfFont)
{
	m_lfAngleUnitFont = lfFont;
	return 0;
}

LOGFONT CPolarAxis::GetAngleUnitFont()
{
	return m_lfAngleUnitFont;
}


void CPolarAxis::SetAxisBackColor(COLORREF color)
{
	m_crAxisBackColor = color;
}

COLORREF CPolarAxis::GetAxisBackColor()
{
	return m_crAxisBackColor;
}

void CPolarAxis::SetWorkAreaBkColor(COLORREF color)
{
	m_crAxisWorkAreaBk = color;
}

COLORREF CPolarAxis::GetWorkAreaBkColor()
{
	return m_crAxisWorkAreaBk;
}

void CPolarAxis::SetAngleUnitLineColor(COLORREF color)
{
	m_crAngleUnitLineColor = color;
}

COLORREF CPolarAxis::GetAngleUnitLineColor()
{
	return m_crAngleUnitLineColor;
}

void CPolarAxis::SetAxisCenterColor(COLORREF color)
{
	m_crAxisCenter = color;
}

COLORREF CPolarAxis::GetAxisCenterColor()
{
	return m_crAxisCenter;
}

void CPolarAxis::SetAxisFrameColor(COLORREF color)
{
	m_crAxisFrame = color;
}

COLORREF CPolarAxis::GetAxisFrameColor()
{
	return m_crAxisFrame;
}

void CPolarAxis::SetAngleUnitFontColor(COLORREF color)
{
	m_crAngleUnitFontColor = color;
}

COLORREF CPolarAxis::GetAngleUnitFontColor()
{
	return m_crAngleUnitFontColor;
}

void CPolarAxis::SetCenterLineType(long lVal)
{
	m_uiCenterLineType = lVal;
}

long CPolarAxis::GetCenterLineType()
{
	return m_uiCenterLineType;
}

void CPolarAxis::SetCenterLineWidth(long lVal)
{
	m_iCenterLineWidth = lVal;
}

long CPolarAxis::GetCenterLineWidth()
{
	return m_iCenterLineWidth;
}

void CPolarAxis::SetAngleUnitLineStyle(long lVal)
{
	m_lAngleUnitLineStyle = lVal;
}

long CPolarAxis::GetAngleUnitLineStyle()
{
	return m_lAngleUnitLineStyle;
}
void CPolarAxis::SetAxisDrawType(long lVal)
{
	m_iAxisDrawType = lVal;

	SetPolarAxisBorder(m_rectBorder);
}

long CPolarAxis::GetAxisDrawType()
{
	return m_iAxisDrawType;
}


//#########################################################
///////定义角度刻度相关的函数及控制变量
//0=5;1=10;2=15;3=30
void CPolarAxis::SetAngleUnit(int iAngleUnitIndex)
{
	int iUnit[4]={5,10,15,30};
	if(iAngleUnitIndex<0)iAngleUnitIndex=0;
	if(iAngleUnitIndex>3)iAngleUnitIndex=3;
	m_iAngleUnit=iUnit[iAngleUnitIndex];
}
int CPolarAxis::GetAngleUnit()
{
	return m_iAngleUnit;
}

//#########################################################
//定义幅值刻度相关的函数及其控制变量

//设置幅值刻度网格的个数
void CPolarAxis::SetCircleGridCounts(int iCircleGridCounts)
{
	m_iCircleGridCounts=iCircleGridCounts;
}
//获得幅值刻度网格的个数
int	CPolarAxis::GetCircleGridCounts()
{
	return m_iCircleGridCounts;
}
//设置坐标的种类个数
void CPolarAxis::SetCircleAxisCounts(int iCircleAxisCount)
{
	if(iCircleAxisCount<=0)iCircleAxisCount=1;
	if(iCircleAxisCount>=POLORAXIS_AXISCOUNT)iCircleAxisCount=POLORAXIS_AXISCOUNT;
	m_iCircleAxisCount=iCircleAxisCount;
}

long CPolarAxis::SetCircleAxisCounts(long nValue)
{
	if(nValue<=0)nValue=1;
	if(nValue>=POLORAXIS_AXISCOUNT)nValue=POLORAXIS_AXISCOUNT;
	m_iCircleAxisCount=nValue;
	return 0;
}

//获得坐标的种类个数
int	 CPolarAxis::GetCircleAxisCounts()
{
	return m_iCircleAxisCount;
}
//设置单个幅值坐标的幅值
void CPolarAxis::SetCircleUnitValue(int iUnitIndex,double fUnitVal)
{
	if(iUnitIndex<0 || iUnitIndex>=POLORAXIS_AXISCOUNT)return;
	m_fCircleUnitValue[iUnitIndex]=fUnitVal;
}
//获得单个幅值坐标的幅值
double CPolarAxis::GetCircleUnitValue(int iUnitIndex)
{
	if(iUnitIndex<0 || iUnitIndex>=POLORAXIS_AXISCOUNT)return -1;
	return m_fCircleUnitValue[iUnitIndex];
}
//设置幅值坐标的幅值
void CPolarAxis::SetCircleUnitValue(double fUnitVal[POLORAXIS_AXISCOUNT])
{
	int iIndex=0;
	for(iIndex=0;iIndex<m_iCircleAxisCount;iIndex++)
	{
		m_fCircleUnitValue[iIndex]=fUnitVal[iIndex];
	}

/*
	if(m_iAxisDrawType & POLARAXIS_RULER)
		ResetRuler();
*/
}
//获得幅值坐标的幅值，返回幅值坐标的个数
int CPolarAxis::GetCircleUnitValue(double fUnitVal[POLORAXIS_AXISCOUNT])
{
	int iIndex=0;

	for(iIndex=0;iIndex<m_iCircleAxisCount;iIndex++)
	{
		fUnitVal[iIndex]=m_fCircleUnitValue[iIndex];
	}

	return m_iCircleAxisCount;
}

//坐标区域
long CPolarAxis::GetBorder(long *left, long *top, long *right, long *bottom)
{
	return 0;
}

long CPolarAxis::SetMarginGap(long nLeftGap, long nTopGap, long nRightGap, long nBottomGap)
{
	return 0;
}

long CPolarAxis::GetMarginGap(long *nLeftGap, long *nTopGap, long *nRightGap, long *nBottomGap)
{
	return 0;
}

long CPolarAxis::GetXAxisType()
{
	return m_lAxisType;
}

void CPolarAxis::SetXAxisType(long lType)
{
	m_lAxisType=lType;
}


//#########################################################
//定义极坐标的总的对外接口函数
void CPolarAxis::InitIt()
{
	m_lAxisDrawStyle = POLARAXISDRAW_ALL;
	m_rectBorder		=CRect(0,0,260,230);			//整个极坐标的坐标区域
	m_rectWorkArea		=CRect(30,15,230,215);			//极坐标的绘图区域
	
	m_lCircleUnitLineWidth = 1;
	m_lZoomCoefficient = 1;
	m_crAngleUnitFontColor = RGB(0,0,0);

	//m_strPolarAxisTitle = "Polar Axis";
	m_crPolarAxisTitleFont = RGB(0,0,0);
    m_lfPolarAxisTitleFont = InitLogFont ((int)(12*m_lZoomCoefficient),0,0,0,400,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Arial"));
	
	m_iCircleGridCounts	=5;
	m_iCircleAxisCount	=2;
	
	//矢量的名称绘制字体
    m_lfAxisCenter = InitLogFont (12*m_lZoomCoefficient,0,0,0,400,'\0','\0','\0','\1','\x1','\x2','\x1','1',_T("Arial"));
	m_lfVectorName = m_lfAxisCenter;
	m_lfAngleUnitFont = m_lfAxisCenter;
#ifndef _PSX_IDE_QT_
    m_crAxisBackColor	= GetSysColor(COLOR_3DFACE);	//坐标轴的底色
    m_crAngleUnitLineColor		= GetSysColor(COLOR_3DDKSHADOW);	//坐标网格颜色
    m_crCircleUnitLineColor   =GetSysColor(COLOR_3DDKSHADOW);
#else
    m_crAxisBackColor	= RGB(240,240,240);//GetSysColor(COLOR_3DFACE);	//坐标轴的底色
    m_crAngleUnitLineColor		= RGB(192,192,192);//GetSysColor(COLOR_3DDKSHADOW);	//坐标网格颜色
    m_crCircleUnitLineColor   = RGB(128,128,128);//GetSysColor(COLOR_3DDKSHADOW);
#endif
	m_crAxisWorkAreaBk	=RGB(255,255,255);	//坐标轴的底色
	m_lAngleUnitLineWidth       = 1;//坐标网格宽度
	m_crAngleUnitFontColor      =RGB(0,0,0);
	m_crAxisCenter		=RGB(0,0,0);		//坐标中心轴颜色
	m_crAxisFrame		=RGB(0,0,0);		//坐标边框颜色
	m_crFrameLeftTopColor = RGB(128,128,128);
	m_crFrameRightBottomColor = RGB(240,240,240);
	m_iFrameShadow = (int)(2*m_lZoomCoefficient);
	m_uiCenterLineType	=PS_SOLID;
	m_iCenterLineWidth	=1;
    m_lAngleUnitLineStyle	= PS_DOT;

	m_iAxisDrawType		= POLARAXISDRAW_ALL;		//坐标绘制种类	角度刻度、幅值刻度、中心轴
	m_iAngleUnit		=30;
	m_lCircleUnitLineStyle    =PS_DOT; 
	m_lCircleUnitLineWidth   =1;
	m_iCircleGridCounts	=5;
	m_iCircleAxisCount	=1;

	m_lAxisType = 0;
	m_fOneYGapValue = 0;
	m_fOneXGapValue = 0;
	m_ptCenterLogInDv = CPoint(0,0);
	m_ptAxisCenter = CPoint(0,0);
	
/*
	m_ruler.InitIt();
	m_ruler.ContinueInit();
*/
//	m_rulerCenter.InitIt();
//	m_rulerCenter.ContinueInit();
	for(int i=0;i<POLORAXIS_AXISCOUNT;i++)
	{
		m_fCircleUnitValue[i]=10;
		m_fCircleValOneGap[i]=0;
		memset(m_ppszCircleUnitName[i] , 0, POLORAXIS_NAMEBUFFLEN*sizeof(char));
	}	

	SetAngleUnitID(30);
	SetCircleAxisCounts(5);

//	m_iHorzMarginGapLeft	=45*m_lZoomCoefficient;		//坐标的水平空白区域
//	m_iHorzMarginGapRight	=30*m_lZoomCoefficient;
//	m_iVertMarginGapTop	    =20*m_lZoomCoefficient;		//坐标的垂直空白区域
//	m_iVertMarginGapBottom  =15*m_lZoomCoefficient;	
	SetMarginGap(45,35,30,15);

    SetBorder(0,0,430,400);
	ResetPolarAxis();
}

void CPolarAxis::DrawWorkArea(CDC *pDC)	//绘制边框
{

	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,1,m_crAxisWorkAreaBk);
	pOldPen=pDC->SelectObject(&pen);
	CBrush brush,*pOldBrush;
	brush.CreateSolidBrush(m_crAxisWorkAreaBk);
	pOldBrush=pDC->SelectObject(&brush);

	pDC->Ellipse(m_rectWorkArea);


	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();

}

void CPolarAxis::DrawWorkAreaFrame(CDC *pDC)
{
	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,1,m_crAxisFrame);
	pOldPen=pDC->SelectObject(&pen);
	CGdiObject * pObj=pDC->SelectStockObject(NULL_BRUSH);
	
	pDC->Ellipse(m_rectWorkArea);
	
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	pDC->SelectObject(pObj);
}
//坐标轴的底色
void CPolarAxis::DrawAxisBackGround(CDC *pDC)
{
	//绘制背景
	CBrush brush;
	brush.CreateSolidBrush(m_crAxisBackColor);
	pDC->FillRect(m_rectBorder,&brush);
	brush.DeleteObject();	
}

void CPolarAxis::DrawAxisBoder(CDC *pDC)
{
	CRect rect = m_rectBorder;
//	rect.OffsetRect(ptOffset);
	Draw3dRectBorder(pDC,&rect,m_iFrameShadow,m_crFrameLeftTopColor,m_crFrameRightBottomColor);
}

/////////////Add at 05-9-9/////////////
void CPolarAxis::DrawAxisTitle(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	int iLen=m_strPolarAxisTitle.GetLength();
	CFont CF;
	LOGFONT lf = m_lfPolarAxisTitleFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	
	long lfWidth = GetCharWidthByLogfont2(pDC,lf);
	
	iLen = lfWidth * iLen;
	iLen = abs(iLen);
	int iWidth = 0;
	CRect rect;
	rect.left = m_rectBorder.left;
	rect.top = m_rectBorder.top + 2;
	rect.right = m_rectBorder.right;
	rect.bottom = m_rectBorder.top + m_iVertMarginGapTop;
	
	CPoint ptCenter = rect.CenterPoint();
	rect.left = ptCenter.x - iLen;
	rect.right = ptCenter.x + iLen;
	rect.OffsetRect(ptOffset);
	
	if (m_strPolarAxisTitle.GetLength() > 0)
	{
		CmDrawTextRect(pDC,m_strPolarAxisTitle,m_crPolarAxisTitleFont,&rect,RGB(0,0,0),
			lf,TRANSPARENT,DT_TOP|DT_LEFT,0);
	}
}

//绘制中心轴
void CPolarAxis::DrawAxisCenter(CDC*pDC)
{
	CPen pen,*pOldPen;
	pen.CreatePen(m_uiCenterLineType,m_iCenterLineWidth,m_crAxisCenter);
	pOldPen=pDC->SelectObject(&pen);

	//绘制坐标中心轴轴线
    m_ptAxisCenter = m_rectWorkArea.CenterPoint();
	pDC->MoveTo(m_rectWorkArea.left+1,m_ptAxisCenter.y);
	pDC->LineTo(m_rectWorkArea.right-1,m_ptAxisCenter.y);
	pDC->MoveTo(m_ptAxisCenter.x,m_rectWorkArea.top+1);
	pDC->LineTo(m_ptAxisCenter.x,m_rectWorkArea.bottom-1);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	//绘制坐标的标注
	CRect rect;
	char cStr[40];
	m_lZoomCoefficient = 1;
	int iGap=4*m_lZoomCoefficient;
	int iLen=40*m_lZoomCoefficient;

	//		0
	strcpy(cStr,"0");
	rect.left=m_rectWorkArea.right+iGap;
	rect.top=m_ptAxisCenter.y-10*m_lZoomCoefficient;
	rect.right=rect.left+iLen;
	rect.bottom=m_ptAxisCenter.y+10*m_lZoomCoefficient;
	CmDrawTextRect(pDC,CString(cStr),m_crAngleUnitFontColor,rect,RGB(0,0,0),m_lfAngleUnitFont,TRANSPARENT,DT_VCENTER|DT_LEFT,0);

	//±180
#ifndef _PSX_IDE_QT_
    strcpy(cStr,"±180");
#else
    strcpy(cStr,"180");
#endif
	rect.right=m_rectWorkArea.left-iGap;
	rect.left=rect.right-iLen;
	CmDrawTextRect(pDC,CString(cStr),m_crAngleUnitFontColor,rect,RGB(0,0,0),m_lfAngleUnitFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);

	//+90
	strcpy(cStr,"+90");
	rect.right=m_ptAxisCenter.x+iLen/2;
	rect.left=rect.right-iLen;
	rect.bottom=m_rectWorkArea.top;
	rect.top=rect.bottom-15*m_lZoomCoefficient;
	CmDrawTextRect(pDC,CString(cStr),m_crAngleUnitFontColor,rect,RGB(0,0,0),m_lfAngleUnitFont,TRANSPARENT,DT_BOTTOM|DT_CENTER,0);
	
	//-90
	strcpy(cStr,"-90");
	rect.top=m_rectWorkArea.bottom;
	rect.bottom=rect.top+15*m_lZoomCoefficient;
	CmDrawTextRect(pDC,CString(cStr),m_crAngleUnitFontColor,rect,RGB(0,0,0),m_lfAngleUnitFont,TRANSPARENT,DT_TOP|DT_CENTER,0);
}	
void CPolarAxis::DrawIt(CDC *pDC)
{
	DrawAxisBackGround(pDC);
	
	if(m_lAxisDrawStyle & POLARAXISDRAW_AXISBODER)
	{
		DrawAxisBoder(pDC);
	}
	
	//工作区
	if(m_lAxisDrawStyle & POLARAXISDRAW_WORKAREA)
	{
		DrawWorkArea(pDC);		
	}

	if(m_lAxisDrawStyle & POLARAXISDRAW_AXISTITLE)
	{
        DrawAxisTitle(pDC,1,CPoint(0,0));
	}
	
	//绘制角度斜线刻度
	if(m_lAxisDrawStyle & POLARAXISDRAW_ANGLEUNIT_LINE)
	{
		DrawAngleUnit(pDC);	
	}
	
	//绘制幅值刻度
	if(m_lAxisDrawStyle & POLARAXISDRAW_CIRCLEUNIT)
	{
		DrawCircleUnit(pDC);	
	}

	//绘制中心轴和刻度
	if(m_lAxisDrawStyle & POLARAXISDRAW_AXISCENTER)
	{
		DrawAxisCenter(pDC);	
	}

	if(m_lAxisDrawStyle & POLARAXISDRAW_WORKAREAFRAME)
	{
		DrawWorkAreaFrame(pDC);	
	}
}
//将逻辑坐标转化为实际坐标
void CPolarAxis::LogicPointToDevicePoint(double fRadius,double fAngle,CPoint *pPoint,long iCircleUnitIndex)
{
	double fUnit=fRadius / m_fCircleValOneGap[iCircleUnitIndex];		//幅值转换
	double dx,dy;

	//转化成增量
	double da = PI_180_RADIANTOANGLE * fAngle;	//PI_180 = 3.1415926 / 180
	dx=fUnit*cos(da);
	dy=fUnit*sin(da);

	//获得屏幕坐标值
	pPoint->x=m_ptAxisCenter.x+(int)dx;
	pPoint->y=m_ptAxisCenter.y-(int)dy;
}

//从实际坐标获取实际坐标所代表的值
void CPolarAxis::DevicePointToLogicPoint(const CPoint &point,double *fRadius,double *fAngle,long iCircleUnitIndex)
{
	double dx,dy;

	//获得增量
	dx=(double)(point.x-m_ptAxisCenter.x)*m_fCircleValOneGap[iCircleUnitIndex];
	dy=(double)(m_ptAxisCenter.y-point.y)*m_fCircleValOneGap[iCircleUnitIndex];
    double dLen=hypot(dx,dy);
	if(dLen<=0.0001)
	{
		*fRadius=0;
		*fAngle=0;
		return;
	}

	double da=acos(dx / dLen);
	da= da * PI_180_ANGLETORADIAN;
	if(point.y>m_ptAxisCenter.y)
		da=-da;
	dLen=dLen;
	*fRadius=(double)dLen;
	*fAngle=(double)(da);
}

void CPolarAxis::GetAxisDrawArea(CRect &rcArea)
{
    rcArea = m_rectBorder;
}

void CPolarAxis::GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
    dXMin = 0;
    dXMax = 360;
    dYMin = 0;
    dYMax = m_fCircleUnitValue[0];
}

//绘制一矢量图
void CPolarAxis::DrawTheVector(CDC*pDC,int iCircleUnitIndex,double fRadius,double fAngle,
		CString strVectorName,COLORREF crVector,int iLineWidth,
		unsigned int uiLineStyle,int iArrowLen,COLORREF crVectorTitle)
{
	CPoint ptv;
	if(iCircleUnitIndex>=m_iCircleAxisCount)return;
	CPen pen,*pOldPen;
	int	iArowLen2=15*m_lZoomCoefficient;
	m_ptAxisCenter = m_rectWorkArea.CenterPoint();
	
	if(fRadius>m_fCircleUnitValue[iCircleUnitIndex])
	{
		fRadius=m_fCircleUnitValue[iCircleUnitIndex];
		LogicPointToDevicePoint(fRadius,fAngle,&ptv,iCircleUnitIndex);
		pen.CreatePen(uiLineStyle,iLineWidth,crVector);
		pOldPen=pDC->SelectObject(&pen);
		pDC->MoveTo(m_ptAxisCenter);	
		pDC->LineTo(ptv);
		pDC->SelectObject(pOldPen);
		pen.DeleteObject();
		return;
	}

	LogicPointToDevicePoint(fRadius,fAngle,&ptv,iCircleUnitIndex);
    double d1=ptv.x-m_ptAxisCenter.x;
    double d2=ptv.y-m_ptAxisCenter.y;
    double fArowLen2=hypot(d1,d2);
	CPoint ptArrow1,ptArrow2;
	//////////////计算矢量图的箭头
	iArowLen2=(int)fArowLen2;

	if(iArowLen2<iArrowLen)
		iArrowLen=iArowLen2;

	double	fAss=(double)iArrowLen;
	double	fAg=(double)(3.141592654 / 180.0);
	ptArrow1.x=-(int)(fAss*sin((fAngle+75.0f)*fAg));
	ptArrow1.y=-(int)(fAss*cos((fAngle+75.0f)*fAg));
	ptArrow2.x=-(int)(fAss*sin((75.0f-fAngle)*fAg));
	ptArrow2.y=(int)(fAss*cos((75.0f-fAngle)*fAg));
	ptArrow1 = ptv+ptArrow1;
	ptArrow2 = ptv+ptArrow2;

	//////////绘制矢量直线
	pen.CreatePen(uiLineStyle,iLineWidth,crVector);
	pOldPen=pDC->SelectObject(&pen);
	pDC->MoveTo(m_ptAxisCenter);	
	pDC->LineTo(ptv);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	//////////绘制矢量箭头
	pen.CreatePen(PS_SOLID,iLineWidth,crVector);
	pOldPen=pDC->SelectObject(&pen);
	CBrush brush,*pOldBrush;
	brush.CreateSolidBrush(crVector);
	pOldBrush=pDC->SelectObject(&brush);

	if(iLineWidth==1)
	{
		CPoint ptArrow[3];
		ptArrow[0]=ptv;ptArrow[1]=ptArrow1;ptArrow[2]=ptArrow2;
		pDC->Polygon(ptArrow,3);
	}
	else
	{
		pDC->MoveTo(ptArrow1);pDC->LineTo(ptv);
		pDC->MoveTo(ptArrow2);pDC->LineTo(ptv);
	}

	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	///////////////下面绘制矢量图的名称
	//获取矢量图名称的位置
	CRect rectVector;
	int iLen=strVectorName.GetLength() ;
	double fAT=fAngle;
	if(fAT<0)fAT=360+fAT;
	unsigned int ulType=0;
	int iLenChar=10*m_lZoomCoefficient;

	if (fAT>=45 && fAT <= 135 ) 
	{
		rectVector.bottom=ptv.y-2*m_lZoomCoefficient;rectVector.top=rectVector.bottom-10*m_lZoomCoefficient;
		rectVector.left=ptv.x-iLen*iLenChar;rectVector.right=rectVector.left+iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_CENTER;
	}
	else if ( fAT>135 && fAT < 225)
	{
		rectVector.bottom=ptv.y-8*m_lZoomCoefficient;rectVector.top=ptv.y+8*m_lZoomCoefficient;
		rectVector.right=ptv.x;rectVector.left=rectVector.right-iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_RIGHT;
	}
	else if(fAT>=225 && fAT <= 315)
	{
		rectVector.top=ptv.y+2*m_lZoomCoefficient;rectVector.bottom=rectVector.top+10*m_lZoomCoefficient;
		rectVector.left=ptv.x-iLen*iLenChar;rectVector.right=rectVector.left+iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_CENTER;
	}
	else
	{
		rectVector.bottom=ptv.y+8*m_lZoomCoefficient;rectVector.top=ptv.y-8*m_lZoomCoefficient;
		rectVector.left=ptv.x;rectVector.right=rectVector.left+iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_LEFT;
	}
	
	if (strVectorName.GetLength() > 0)
	{
		CmDrawTextRect(pDC,strVectorName,crVectorTitle,rectVector,RGB(0,0,0),m_lfVectorName,TRANSPARENT,ulType,0);
	}
}
void CPolarAxis::DrawTheVector(CDC*pDC,int iCircleUnitIndex,double fRadius1,double fAngle1,double fRadius2,double fAngle2,
							   CString strVectorName,COLORREF crVector,int iLineWidth,unsigned int uiLineStyle,
							   int iArrowLen,COLORREF crVectorTitle)
{
	double	fAngle3,fRadius3;		//2矢量之间的矢量数据
	CPoint	ptDelta;				//2矢量之间在设备坐标上的象素之差
	CPoint	ptVector1,ptVector2;
	CPoint	ptTemp;
	m_ptAxisCenter = m_rectWorkArea.CenterPoint();

	if(iCircleUnitIndex>=m_iCircleAxisCount)return;

	CPen pen,*pOldPen;
	int	iArowLen2=15*m_lZoomCoefficient;
	
	LogicPointToDevicePoint(fRadius1,fAngle1,&ptVector1,iCircleUnitIndex);
	LogicPointToDevicePoint(fRadius2,fAngle2,&ptVector2,iCircleUnitIndex);
	ptDelta	=ptVector2-ptVector1;		//
	ptTemp  =ptDelta + m_ptAxisCenter;
	DevicePointToLogicPoint(ptTemp,&fRadius3,&fAngle3,iCircleUnitIndex);

//	LogicPointToDevicePoint(fRadius,fAngle,&ptv,iCircleUnitIndex);
	double d1=ptDelta.x;
	double d2=ptDelta.y;
    double fArowLen2=hypot(d1,d2);
	CPoint ptArrow1,ptArrow2;
	//////////////计算矢量图的箭头
	iArowLen2=(int)fArowLen2;
	if(iArowLen2<iArrowLen)
		iArrowLen=iArowLen2;
	double	fAss=(double)iArrowLen;
	double	fAg=(double)(3.141592654 / 180.0);
	ptArrow1.x=-(int)(fAss*sin((fAngle3+75.0f)*fAg));
	ptArrow1.y=-(int)(fAss*cos((fAngle3+75.0f)*fAg));
	ptArrow2.x=-(int)(fAss*sin((75.0f-fAngle3)*fAg));
	ptArrow2.y=(int)(fAss*cos((75.0f-fAngle3)*fAg));
	
	ptArrow1 = ptVector2+ptArrow1;
	ptArrow2 = ptVector2+ptArrow2;
	//////////绘制矢量直线
	pen.CreatePen(uiLineStyle,iLineWidth,crVector);
	pOldPen=pDC->SelectObject(&pen);
	pDC->MoveTo(ptVector1);		pDC->LineTo(ptVector2);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	//////////绘制矢量箭头
	pen.CreatePen(PS_SOLID,iLineWidth,crVector);
	pOldPen=pDC->SelectObject(&pen);
	CBrush brush,*pOldBrush;
	brush.CreateSolidBrush(crVector);
	pOldBrush=pDC->SelectObject(&brush);
	if(iLineWidth==1)
	{
		CPoint ptArrow[3];
		ptArrow[0]=ptVector2;ptArrow[1]=ptArrow1;ptArrow[2]=ptArrow2;
		pDC->Polygon(ptArrow,3);
	}
	else
	{
		pDC->MoveTo(ptArrow1);pDC->LineTo(ptVector2);
		pDC->MoveTo(ptArrow2);pDC->LineTo(ptVector2);
	}
	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	///////////////下面绘制矢量图的名称
	//获取矢量图名称的位置
	CRect rectVector;
	int iLen=strVectorName.GetLength() ;
	double fAT=fAngle1;
	if(fAT<0)fAT=360+fAT;
	unsigned int ulType=0;
	int iLenChar=8*m_lZoomCoefficient;
	if (fAT>=45 && fAT <= 135 ) 
	{
		rectVector.bottom=ptVector1.y-2*m_lZoomCoefficient;rectVector.top=rectVector.bottom-10*m_lZoomCoefficient;
		rectVector.left=ptVector1.x-iLen*iLenChar;rectVector.right=rectVector.left+iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_CENTER;
	}
	else if ( fAT>135 && fAT < 225)
	{
		rectVector.bottom=ptVector1.y-8*m_lZoomCoefficient;rectVector.top=ptVector1.y+8*m_lZoomCoefficient;
		rectVector.right=ptVector1.x;rectVector.left=rectVector.right-iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_RIGHT;
	}
	else if(fAT>=225 && fAT <= 315)
	{
		rectVector.top=ptVector1.y+2*m_lZoomCoefficient;rectVector.bottom=rectVector.top+10*m_lZoomCoefficient;
		rectVector.left=ptVector1.x-iLen*iLenChar;rectVector.right=rectVector.left+iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_CENTER;
	}
	else
	{
		rectVector.bottom=ptVector1.y+8*m_lZoomCoefficient;rectVector.top=ptVector1.y-8*m_lZoomCoefficient;
		rectVector.left=ptVector1.x;rectVector.right=rectVector.left+iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_LEFT;
	}

	if (strVectorName.GetLength() > 0)
	{
		CmDrawTextRect(pDC,strVectorName,crVectorTitle,rectVector,RGB(0,0,0),m_lfVectorName,TRANSPARENT,ulType,0);
	}
}


void CPolarAxis::DrawTheVector(CDC*pDC,int iCircleUnitIndex,
		double fRadius1,double fAngle1,double fRadius2,double fAngle2,
		double *fRadiusL,double *fAngleL,	//返回线性矢量
		CString strVectorName,COLORREF crVector,int iLineWidth,unsigned int uiLineStyle,
		int iArrowLen,COLORREF crVectorTitle)
{
	double	fAngle3,fRadius3;		//2矢量之间的矢量数据
	CPoint	ptDelta;				//2矢量之间在设备坐标上的象素之差
	CPoint	ptVector1,ptVector2;
	CPoint	ptTemp;
	m_ptAxisCenter = m_rectWorkArea.CenterPoint();

	if(iCircleUnitIndex>=m_iCircleAxisCount || iCircleUnitIndex < 0)
	{
		return;
	}

	CPen pen,*pOldPen;
	int	iArowLen2=15*m_lZoomCoefficient;
	
	LogicPointToDevicePoint(fRadius1,fAngle1,&ptVector1,iCircleUnitIndex);
	LogicPointToDevicePoint(fRadius2,fAngle2,&ptVector2,iCircleUnitIndex);
	ptDelta	=ptVector2-ptVector1;		//
	ptTemp  =ptDelta + m_ptAxisCenter;
	DevicePointToLogicPoint(ptTemp,&fRadius3,&fAngle3,iCircleUnitIndex);
	*fRadiusL=fRadius3;*fAngleL=fAngle3;
//	LogicPointToDevicePoint(fRadius,fAngle,&ptv,iCircleUnitIndex);
	double d1=ptDelta.x;
	double d2=ptDelta.y;
    double fArowLen2=hypot(d1,d2);
	CPoint ptArrow1,ptArrow2;
	//////////////计算矢量图的箭头
	iArowLen2=(int)fArowLen2;
	if(iArowLen2<iArrowLen)
		iArrowLen=iArowLen2;
	double	fAss=(double)iArrowLen;
	double	fAg=(double)(3.141592654 / 180.0);
	ptArrow1.x=-(int)(fAss*sin((fAngle3+75.0f)*fAg));
	ptArrow1.y=-(int)(fAss*cos((fAngle3+75.0f)*fAg));
	ptArrow2.x=-(int)(fAss*sin((75.0f-fAngle3)*fAg));
	ptArrow2.y=(int)(fAss*cos((75.0f-fAngle3)*fAg));
	
	ptArrow1 = ptVector2+ptArrow1;
	ptArrow2 = ptVector2+ptArrow2;
	//////////绘制矢量直线
	pen.CreatePen(uiLineStyle,iLineWidth,crVector);
	pOldPen=pDC->SelectObject(&pen); 
	pDC->MoveTo(ptVector1);		pDC->LineTo(ptVector2);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	//////////绘制矢量箭头
	pen.CreatePen(PS_SOLID,iLineWidth,crVector);
	pOldPen=pDC->SelectObject(&pen);
	CBrush brush,*pOldBrush;
	brush.CreateSolidBrush(crVector);
	pOldBrush=pDC->SelectObject(&brush);
	if(iLineWidth==1)
	{
		CPoint ptArrow[3];
		ptArrow[0]=ptVector2;ptArrow[1]=ptArrow1;ptArrow[2]=ptArrow2;
		pDC->Polygon(ptArrow,3);
	}
	else
	{
		pDC->MoveTo(ptArrow1);pDC->LineTo(ptVector2);
		pDC->MoveTo(ptArrow2);pDC->LineTo(ptVector2);
	}
	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	///////////////下面绘制矢量图的名称
	//获取矢量图名称的位置
	CRect rectVector;
	int iLen=strVectorName.GetLength() ;
	double fAT=fAngle1;
	if(fAT<0)fAT=360+fAT;
	unsigned int ulType=0;
	int iLenChar=8*m_lZoomCoefficient;
	if (fAT>=45 && fAT <= 135 ) 
	{
		rectVector.bottom=ptVector1.y-2*m_lZoomCoefficient;rectVector.top=rectVector.bottom-10*m_lZoomCoefficient;
		rectVector.left=ptVector1.x-iLen*iLenChar;rectVector.right=rectVector.left+iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_CENTER;
	}
	else if ( fAT>135 && fAT < 225)
	{
		rectVector.bottom=ptVector1.y-8*m_lZoomCoefficient;rectVector.top=ptVector1.y+8*m_lZoomCoefficient;
		rectVector.right=ptVector1.x;rectVector.left=rectVector.right-iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_RIGHT;
	}
	else if(fAT>=225 && fAT <= 315)
	{
		rectVector.top=ptVector1.y+2*m_lZoomCoefficient;rectVector.bottom=rectVector.top+10*m_lZoomCoefficient;
		rectVector.left=ptVector1.x-iLen*iLenChar;rectVector.right=rectVector.left+iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_CENTER;
	}
	else
	{
		rectVector.bottom=ptVector1.y+8*m_lZoomCoefficient;rectVector.top=ptVector1.y-8*m_lZoomCoefficient;
		rectVector.left=ptVector1.x;rectVector.right=rectVector.left+iLen*iLenChar*2;
		ulType=DT_VCENTER|DT_LEFT;
	}

	if (strVectorName.GetLength() > 0)
	{
		CmDrawTextRect(pDC,strVectorName,crVectorTitle,rectVector,RGB(0,0,0),m_lfVectorName,TRANSPARENT,ulType,0);
	}
}

void CPolarAxis::DrawTheVector(CDC *pDC, int iCircleUnitIndex, POLAR_VECTOR *pVector)
{
	//	void	DrawTheVector(CDC*pDC,int iCircleUnitIndex,double fRadius,double fAngle,CString strVectorName,COLORREF crVector=RGB(0,0,0),int iLineWidth=1
	//,unsigned int uiLineStyle=PS_SOLID,int iArrowLen=10,COLORREF crVectorTitle=RGB(0,0,0));//绘制一矢量图
#ifdef UNICODE
	DrawTheVector(pDC, iCircleUnitIndex, pVector->dMag, pVector->dAng, CString(pVector->pszName), pVector->crVector, pVector->nLineWidth
		, pVector->uiLineStyle, pVector->nArrowLen, pVector->crVectorTitle);
#else
	DrawTheVector(pDC, iCircleUnitIndex, pVector->dMag, pVector->dAng, pVector->pszName, pVector->crVector, pVector->nLineWidth
		, pVector->uiLineStyle, pVector->nArrowLen, pVector->crVectorTitle);
#endif
}

void CPolarAxis::DrawTheVector(CDC *pDC, POLAR_VECTORS *pVectors)
{
	if (pVectors->nEnable == 0)
	{
		return;
	}

	int k = 0;
	double dMax = pVectors->get_max();

	if (dMax <= 0.001)
	{
		dMax = 0.001;
	}

	dMax *= 1.1;

	SetCircleUnitValue(pVectors->nAxis, dMax);
	ResetPolarAxis(pVectors->nAxis);

	for (k=0; k<pVectors->nCount; k++)
	{
		DrawTheVector(pDC, pVectors->nAxis, pVectors->pArrVector+k);
	}
}

void CPolarAxis::DrawTheVector(CDC *pDC, POLAR_VECTORS_MNGR *pVectorsMngr)
{
	int k = 0;

	for (k=0; k<pVectorsMngr->nCount; k++)
	{
		DrawTheVector(pDC, pVectorsMngr->pArrVectors+k);
	}
}




//绘制角度刻度
void CPolarAxis::DrawAngleUnit(CDC*pDC)
{
	double dAngleUnit=(double)m_iAngleUnit;
	int iTotal=360 / m_iAngleUnit;
	int iRadius=m_rectWorkArea.Width() / 2;
	double dx,dy;
	double dPI=3.141592654 ;
	double dAngle=0;
	int iX,iY;
	CPen pen,*pOldPen;
	pen.CreatePen(m_lAngleUnitLineStyle,m_lAngleUnitLineWidth,m_crAngleUnitLineColor);
	pOldPen=pDC->SelectObject(&pen);
    m_ptAxisCenter = m_rectWorkArea.CenterPoint();

	for(int i=0;i<iTotal;i++)
	{
		dAngle = dPI * m_iAngleUnit * i / 180;
		dx = cos(dAngle)*iRadius;
		dy = sin(dAngle)*iRadius;
		iX=m_ptAxisCenter.x + (int)dx;
		iY=m_ptAxisCenter.y - (int)dy;
		pDC->MoveTo(m_ptAxisCenter);
		pDC->LineTo(iX,iY);
	}
	pDC->SelectObject(pOldPen);
}

//绘制幅值刻度
void CPolarAxis::DrawCircleUnit(CDC *pDC)
{
	CRect rect;
	int iLen=0;
	CPen cp,*pOldPen;
	CGdiObject * pObj=pDC->SelectStockObject(NULL_BRUSH);
	COLORREF crBackColor = pDC->SetBkColor(m_crAxisWorkAreaBk);
	cp.CreatePen(m_lCircleUnitLineStyle,m_lCircleUnitLineWidth,m_crCircleUnitLineColor);
	pOldPen=pDC->SelectObject(&cp);

	long nBkMode = pDC->SetBkMode(TRANSPARENT);
	
/*	if(m_iAxisDrawType & POLARAXIS_RULER)
	{
		CAxisScaleData *pAxisData = NULL;
		CPoint ptCircle(0,0);
		pAxisData = m_rulerCenter.GetFirstAxisData();
		while (pAxisData != NULL)
		{
			if (pAxisData->m_ptAxisScale.x >=m_rectWorkArea.left && pAxisData->m_ptAxisScale.x <=m_rectWorkArea.right)
			{
				LogicPointToDevicePoint(pAxisData->m_dAxisScaleVal,0,&ptCircle,0);
				iLen = abs(ptCircle.x - m_ptAxisCenter.x);
				rect.left = m_ptAxisCenter.x-iLen;
				rect.right = m_ptAxisCenter.x+iLen;
				rect.top = m_ptAxisCenter.y-iLen;
				rect.bottom = m_ptAxisCenter.y+iLen;
				pDC->Ellipse(rect);
			}
			pAxisData = m_rulerCenter.GetNextAxisData();
		}
	}
	else
*/	{
		int iRadius=m_rectWorkArea.Width() / 2;
		double	fUnit=(double)iRadius / m_iCircleGridCounts;
		
		for(int i=1;i<m_iCircleGridCounts;i++)
		{
			iLen=(int)(fUnit*i);
			rect.left=m_ptAxisCenter.x-iLen;
			rect.right=m_ptAxisCenter.x+iLen;
			rect.top=m_ptAxisCenter.y-iLen;
			rect.bottom=m_ptAxisCenter.y+iLen;
			pDC->Ellipse(rect);
		}	

	}

	pDC->SetBkMode(nBkMode);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pObj);
	pDC->SetBkColor(crBackColor);
	cp.DeleteObject();
}

void CPolarAxis::DrawCircle(CDC *pDC,int iCircleUnitIndex,double *pfRadius,long nCircles
							,COLORREF crCircle,long nLineStype,long lLineWidth)
{
	if (nCircles <= 0)
	{
		return;
	}

	CPoint ptRadius(0,0);

	int iIndex = 0;
	int iRadius=m_rectWorkArea.Width() / 2;
	double	fUnit=(double)iRadius / m_iCircleGridCounts;
	CRect rect;
	int iLen=0;
	
	CPen cp,*pOldPen;
	CGdiObject * pObj=pDC->SelectStockObject(NULL_BRUSH);
	COLORREF crBackColor = pDC->SetBkColor(m_crAxisWorkAreaBk);
	cp.CreatePen(nLineStype,lLineWidth,crCircle);
	pOldPen=pDC->SelectObject(&cp);
	for(iIndex = 0; iIndex < nCircles; iIndex++)
	{
		LogicPointToDevicePoint(pfRadius[iIndex],0,&ptRadius,iCircleUnitIndex);
		iLen = abs(ptRadius.x - m_ptAxisCenter.x);
		rect.left = m_ptAxisCenter.x-iLen;
		rect.right = m_ptAxisCenter.x+iLen;
		rect.top = m_ptAxisCenter.y-iLen;
		rect.bottom = m_ptAxisCenter.y+iLen;
		pDC->Ellipse(rect);
	}	
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pObj);
	pDC->SetBkColor(crBackColor);
	cp.DeleteObject();	
}

void CPolarAxis::GetTheVector(double fRadius1,double fAngle1,double fRadius2,double fAngle2,double *fRadiusL,double *fAngleL)
{
	double fx1,fy1,fx2,fy2;
	double ftx,fty;
	double fTemp=3.1415926/180;
	fAngle1=fAngle1*fTemp;
	fAngle2=fAngle2*fTemp;
	fx1=fRadius1*cos(fAngle1);	fy1=fRadius1*sin(fAngle1);
	fx2=fRadius2*cos(fAngle2);	fy2=fRadius2*sin(fAngle2);
	ftx=fx2-fx1;fty=fy2-fy1;
    *fRadiusL=hypot(ftx,fty);
	if(*fRadiusL==0)
	{
		*fAngleL=0;
		return;
	}
	*fAngleL=acos(ftx/(*fRadiusL)) / fTemp;
	if(fty<0)*fAngleL=-*fAngleL;
}

void CPolarAxis::ZoomIn(float fRate)
{
	float fAngleUnit = (float)GetAngleUnit();
	fAngleUnit *= fRate;
	m_iAngleUnit = (int)fAngleUnit;
	if(m_iAngleUnit<=5) m_iAngleUnit = 0;
	if(m_iAngleUnit>=90) m_iAngleUnit = 90;
	
	m_iCircleGridCounts++;
	AssertCircleGridCounts();
}

void CPolarAxis::ZoomOut(float fRate)
{
	int iAngleUnit = GetAngleUnit();
	iAngleUnit = (int)( fRate * iAngleUnit );
	m_iAngleUnit = iAngleUnit;
	if(m_iAngleUnit<=5) m_iAngleUnit = 0;
	if(m_iAngleUnit>=90) m_iAngleUnit = 90;
	
	m_iCircleGridCounts--;
	AssertCircleGridCounts();
}

void CPolarAxis::ResetRuler()
{
}


//获取坐标系的绘图位置
long CPolarAxis::GetPosition(long *left, long *top, long *right, long *bottom)
{
	*left = m_rectBorder.left;
	*top = m_rectBorder.top;
	*right = m_rectBorder.right;
	*bottom = m_rectBorder.bottom;
	
	return 0;
}

//获取坐标系统的工作区，即坐标系统坐标范围标示的有效区域
long CPolarAxis::GetWorkArea(long *left, long *top, long *right, long *bottom)
{
	*left = m_rectWorkArea.left;
	*top = m_rectWorkArea.top;
	*right = m_rectWorkArea.right;
	*bottom = m_rectWorkArea.bottom;

	return 0;
}

//将逻辑坐标转化为设备坐标:ptx,pty为设备坐标
long CPolarAxis::LogicPointToDevicePoint(double x,double y,long *ptx,long *pty)
{
	CPoint pt;
	LogicPointToDevicePoint(x,y,&pt);
	*ptx = pt.x;
	*pty = pt.y;
	
	return 0;
}

//将设备坐标转化为逻辑坐标:ptx,pty为设备坐标
long CPolarAxis::DevicePointToLogicPoint (long ptx,long pty ,double *x,double *y)
{
	CPoint pt;
	pt.x = ptx;
	pt.y = pty;
	DevicePointToLogicPoint(pt,x,y);

	return 0;
}
