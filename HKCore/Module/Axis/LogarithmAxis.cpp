// LogarithmAxis.cpp : implementation file
//

#include "stdafx.h"
#include "LogarithmAxis.h"
#include "../API/GloblaDrawFunctions.h"
#include "../API/StringApi.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//############################对数坐标系统################################
//////////////////////////////////////////////////////////////////////////
#define LOGARITHMAXISDRAW_ALL				0x00FFFFFF
#define LOGARITHMAXISDRAW_WORKAREA			0x00000001
#define LOGARITHMAXISDRAW_AXISCENTER		0x00000002	
#define LOGARITHMAXISDRAW_AXISBODER			0x00000004	
#define LOGARITHMAXISDRAW_AXISTITLE			0x00000008	

#define LOGARITHMAXISDRAW_XAXIS_ALL			0x00000FF0	
#define LOGARITHMAXISDRAW_XAXIS_LINE		0x00000010	
#define LOGARITHMAXISDRAW_XAXIS_SCALETEXT	0x00000020	
#define LOGARITHMAXISDRAW_XAXIS_TENTHSCALE	0x00000040	
#define LOGARITHMAXISDRAW_XAXIS_HALFSCCALE	0x00000080	
#define LOGARITHMAXISDRAW_XAXIS_NAME		0x00000100	

#define LOGARITHMAXISDRAW_YAXIS_ALL			0x000FF000	
#define LOGARITHMAXISDRAW_YAXIS_LINE		0x00001000	
#define LOGARITHMAXISDRAW_YAXIS_SCALETEXT	0x00002000	
#define LOGARITHMAXISDRAW_YAXIS_TENTHSCALE	0x00004000	
#define LOGARITHMAXISDRAW_YAXIS_HALFSCCALE	0x00008000	
#define LOGARITHMAXISDRAW_YAXIS_NAME		0x00100000	
#define BOTTOMADD 2
/////////////////////////////////////////////////////////////////////////////
// CLogarithmAxis


CLogarithmAxis::CLogarithmAxis()
{
	m_iVertGapLineLen3=4*m_nZoomCoef;
	m_iHorzGapLineLen3=5*m_nZoomCoef;

	m_lAxisType = 0;
	m_bAxisXYUnitLock = TRUE;
	m_lXAxisMaxUnitCount = 10;
	m_lYAxisMaxUnitCount = 10;
	m_lAxisDrawStyle = LOGARITHM_ALL;
	m_dwDisplayType=LOGARITHM_ALL;
	m_lVertLineStyle=PS_DOT;
	m_lHorzLineStyle=PS_DOT;
	m_crVert_WorkAreaLine_Color=RGB(0,0,0);
	m_crHorz_WorkAreaLine_Color=RGB(0,0,0);
	m_crAxisCenter = RGB(240,240,240);
	ContinueInit();
	m_dwDisplayType&= (~LOGARITHM_YAXIS_LLINE);
	
	m_crCircleScale=RGB(240,240,240);
	m_crBiaslineScale=RGB(240,240,240);
	

	m_strAxisTitle = "";
	m_crAxisTitleFont = RGB(0,0,0);
	m_lfAxisTitleFont = InitLogFont (14,0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
	m_strXAxisName = "";
	m_strYAxisName = "";

	m_crFrameLeftTopColor = RGB(128,128,128);
	m_crFrameRightBottomColor = RGB(240,240,240);
	m_iFrameShadow = 2;

#ifndef _PSX_IDE_QT_
    m_crAxisBackColor = GetSysColor(COLOR_3DFACE);//RGB(240,240,240);
#else
    m_crAxisBackColor = RGB(240,240,240);
#endif

	m_dMaxZoomMultiple = 100.0f;
	m_dAxisWorkMarginRatio = 0.05;

	m_rcWorkArea=CRect(30,5,300,300);
	m_rcX_Axis=CRect(30,300,300,320);
	m_rcY_Axis=CRect(0,5,30,300);
	m_iBeginPalace=-0.20f;
	m_iEndPalace=3;
	m_iDisplayMinVal=-3;//0.01
	m_iDisplayMaxVal=2;
	m_iDataMinVal=0;
	m_iDataMaxVal=200;
	m_iMinValueXAxis=0;
	m_iMaxValueXAxis=100;
	m_iXMultipleCoeff=1;
	m_iYMultipleCoeff=1;
	m_iXMaxMultipleCoeff=100;
	m_iYMaxMultipleCoeff=100;		////图形放大的比例		逻辑值 / 设备值
	m_iXMinMultipleCoeff=100;
	m_iYMinMultipleCoeff=100;		////图形放大的比例		逻辑值 / 设备值
	
	m_fXCarryOneGap=1;
	m_fYCarryOneGap=1;

	m_nZoomCoef=1;
	InitIt();
}

CLogarithmAxis::~CLogarithmAxis()
{
	EndXAxisDef();
	EndYAxisDef();
}

//坐标转换
//将逻辑坐标转化为实际坐标
void CLogarithmAxis::LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint, long nAxisIndex)
{
	if(fx<0 || fy<0)return ;

	float fXVal=log10(fx);
	float fYVal=log10(fy);

	fXVal = m_rcX_Axis.left+(fXVal-m_iBeginPalace)*m_fXAxisOneGap;
	fYVal = m_rcY_Axis.bottom-(fYVal-m_iDisplayMinVal)*m_nYAxisOneGap;

	pPoint->x = FloatValToInt(fXVal);
	pPoint->y = FloatValToInt(fYVal);;
}


void CLogarithmAxis::LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex)
{
    //double f=fVal*m_dOneXGapValue;
    //nVal->x=FloatValToInt(f);
}

void CLogarithmAxis::DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex)
{
    //*fVal= nVal / m_dOneXGapValue;
}

//从实际坐标获取实际坐标所代表的值
void CLogarithmAxis::DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex)
{
	double fXVal =m_iBeginPalace + ((double)point.x-(double)m_rcX_Axis.left)/m_fXAxisOneGap;
	double fYVal =((double)m_rcY_Axis.bottom-(double)point.y)/m_nYAxisOneGap + m_iDisplayMinVal;
	*x=pow(10,fXVal);
	*y=pow(10,fYVal);
}

void CLogarithmAxis::GetAxisDrawArea(CRect &rcArea)
{

}

void CLogarithmAxis::GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
	GetMinMaxVal(&dXMin, &dYMin, &dXMax, &dYMax, 0);

}

void CLogarithmAxis::SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax)
{
	SetMinMaxVal(dXMin, dYMin, dXMax, dYMax, 0);
}

void CLogarithmAxis::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{
	SetXAxisName(strXAxisName);
	SetYAxisName(strYAxisName);
	SetAxisTitle(strAxisTitle);
}

#ifdef USE_AXIS_CONFIG//zhouhj 20211026 增加用于设置坐标轴
void CLogarithmAxis::SetAxisConfig(CDataGroup *pAxisConfig)
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
void CLogarithmAxis::SetAxisConfig(CDvmData *pAxisData)
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
		m_crVert_WorkAreaLine_Color = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_AxisCenterLineWidth)
	{
		m_lAxisCenterLineWidth = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_AxisCenterColor)
	{
		m_crAxisCenter = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_XAxisWorkAreaBackColorFrom)
	{
		m_crAxisBK = CString_To_long(pAxisData->m_strValue);
	}
	else if (pAxisData->m_strID == AXIS_CONFIG_ID_AxisScaleFont)
	{
		nValue = CString_To_long(pAxisData->m_strValue);
		m_lfAxisTitleFont= InitLogFont ((long)(-nValue*m_dMaxZoomMultiple),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
		m_lfAxisTitleFont = m_lfAxisTitleFont;
	}

}
void CLogarithmAxis::GetAxisConfig(CDataGroup *pAxisConfig)
{
}
#endif

void CLogarithmAxis::ContinueInit()
{
	m_cBkGroundBrush=InitLogBrush(BS_SOLID,1,m_crBkGroundColor);
	m_penVert_WorkAreaLine=InitLogPen(m_lVertLineStyle,1,m_crVert_WorkAreaLine_Color);
	m_penVert_WorkAreaShortLine=InitLogPen(PS_SOLID,1,m_crYTenthScaleColor);//crVert_WorkAreaLine_Color);
	m_penHorz_WorkAreaLine=InitLogPen(m_lHorzLineStyle,1,m_crHorz_WorkAreaLine_Color);
	m_penHorz_WorkAreaShortLine=InitLogPen(PS_SOLID,1,m_crXTenthScaleColor);//crHorz_WorkAreaLine_Color);
	m_penCircleScale		=InitLogPen(m_lCircleLineType,1,m_crCircleScale);
	m_penBiaslineScale	=InitLogPen(m_lBiasLineType,1,m_crBiaslineScale);
}

void CLogarithmAxis::InitIt()
{
	m_iLeftGap=15*m_nZoomCoef;m_iRightGap=5*m_nZoomCoef;
	m_iTopGap=20*m_nZoomCoef;m_iBottomGap=5*m_nZoomCoef;
	
	//WorkArea Bk
	m_crBkGroundColor=RGB(255,255,255);
	m_crBkLeftTopColor=RGB(128,128,128);
	m_crBkRightBottomColor=RGB(240,240,240);
	m_iShadow=2*m_nZoomCoef;
	
	m_crYUnitScaleColor=RGB(0,0,0);
	m_crYUnitScaleShadowColor=RGB(230,230,230);
	m_crXUnitScaleColor=RGB(0,0,0);
	m_crXUnitScaleShadowColor=RGB(230,230,230);
	
	//VertDef
	m_lfVertFont=InitLogFont (-9*m_nZoomCoef,0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
	m_lfVertTitleFont=InitLogFont (-9*m_nZoomCoef,0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
	m_crVertColor=RGB(0,0,0);
	m_crVertTitleColor=RGB(0,0,0);
	m_lVertLineStyle=PS_SOLID;
	m_crVert_WorkAreaLine_Color=RGB(240,240,240);//RGB(83,83,83);
	m_iVertAreaWidth=35*m_nZoomCoef;
	m_iVertGapLineLen1=10*m_nZoomCoef;
	m_iVertGapLineLen2=8*m_nZoomCoef;
	m_iVertGapLineLen3=3*m_nZoomCoef;
	//HorzDef
	m_lfHorzFont=InitLogFont (-9*m_nZoomCoef,0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
	m_lfHorzTitleFont=InitLogFont (-12*m_nZoomCoef,0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
	m_crHorzColor=RGB(0,0,0);
	m_crHorzTitleColor=RGB(0,0,0);
	m_lHorzLineStyle=PS_SOLID;
	m_crHorz_WorkAreaLine_Color=RGB(240,240,240);//RGB(83,83,83);  //////////grid hor_z
	m_iHorzAreaWidth=20*m_nZoomCoef;
	m_iHorzGapLineLen1=10*m_nZoomCoef;
	m_iHorzGapLineLen2=8*m_nZoomCoef;
	m_iHorzGapLineLen3=3*m_nZoomCoef;
	
	//Cursor and Choice Area
	m_penCursor=InitLogPen(PS_SOLID,1,RGB(255,255,255));
	m_penChoiceArea=InitLogPen(PS_SOLID,1,RGB(255,255,255));
	m_brushChoiceArea=InitLogBrush(BS_SOLID,1,RGB(255,255,255));
	
	m_crCircleScale	=RGB(240,240,240);
	m_crBiaslineScale=RGB(240,240,240);
	m_penCircleScale		=InitLogPen(m_lCircleLineType,1,m_crCircleScale);
	m_penBiaslineScale	=InitLogPen(m_lBiasLineType,1,m_crBiaslineScale);
	m_fCircleScaleOffset=1;
	m_fBiaslineScaleOffset=15;	//圆刻度的半径位移、斜线刻度的角度位移
	
	////////	坐标轴中心轴参数定义
	m_lAxisCenterLineWidth=1;
	m_lAxisCenterLineType = PS_SOLID;
	m_crAxisCenter = RGB(0,0,0);
	
	m_dwDrawXAxisTextType=1;
	m_dwDisplayType=LOGARITHM_ALL;

/////////////////////////////
/////////////////////////////
	m_rcWorkArea=CRect(30,5,300,300);
	m_rcX_Axis=CRect(30,300,300,320);
	m_rcY_Axis=CRect(0,5,30,300);

	m_iBeginPalace=-0.20f;
	m_iEndPalace=3;
	m_iDisplayMinVal=-3;//0.01
	m_iDisplayMaxVal=2;
	m_iOldBeginPalace=m_iBeginPalace;
	m_iOldEndPalace=m_iEndPalace;
	m_iOldDisplayMinVal=m_iDisplayMinVal;
	m_iOldDisplayMaxVal=m_iDisplayMaxVal;

	m_iDataMinVal=0;
	m_iDataMaxVal=200;
	m_iMinValueXAxis=0;
	m_iMaxValueXAxis=100;
	m_iXMultipleCoeff=1;
	m_iYMultipleCoeff=1;
	m_iXMaxMultipleCoeff=100;
	m_iYMaxMultipleCoeff=100;		////图形放大的比例		逻辑值 / 设备值
	m_iXMinMultipleCoeff=100;
	m_iYMinMultipleCoeff=100;		////图形放大的比例		逻辑值 / 设备值
	
	m_ptCenterLogInDv = CPoint(0,0);
	m_iDirection = 0;
	m_fXCarryOneGap=1;
	m_fYCarryOneGap=1;

	m_rectAxis.left = 0;
	m_rectAxis.right = 600;
	m_rectAxis.top = 0;
	m_rectAxis.bottom = 600;
}

const CLogarithmAxis & CLogarithmAxis::operator =(CLogarithmAxis &odTemp)
{
	if (&odTemp==this) 
		return *this;
		
	m_rcBorder=odTemp.m_rcBorder;
	m_rcWorkArea=odTemp.m_rcWorkArea;
	m_rcX_Axis=odTemp.m_rcX_Axis;
	m_rcY_Axis=odTemp.m_rcY_Axis;
	m_iBeginPalace=odTemp.m_iBeginPalace;
	m_iEndPalace=odTemp.m_iEndPalace;
	m_iDataMinVal=odTemp.m_iDataMinVal;
	m_iDataMaxVal=odTemp.m_iDataMaxVal;
	m_iDisplayMinVal=odTemp.m_iDisplayMinVal;
	m_iDisplayMaxVal=odTemp.m_iDisplayMaxVal;
	m_iDirection=odTemp.m_iDirection;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CLogarithmAxis message handlers
float CLogarithmAxis::GetBeginVal(float lNowVal,float lGapVal)
{
	float ff,ff1;
	int iMul=1;
	ff=lNowVal/lGapVal;
	ff1=(int)ff;
	if(ff-ff1<0.99)	iMul=(int)ff;
	else	iMul=(int)ff+1;

	float fb=0;
	fb=lNowVal-(lNowVal - iMul*lGapVal);
	return fb;
}

//#######################################################################
//*****************************关于Y轴的绘制*****************************
//#######################################################################
void CLogarithmAxis::InitYAxisDef()
{
	m_oYAxisDef.DeleteAll();
}
void CLogarithmAxis::EndYAxisDef()
{
	m_oYAxisDef.DeleteAll();
}
void CLogarithmAxis::ResetYAxisDef()
{
	EndYAxisDef();
	float fBeginVal=m_iDisplayMinVal;
	float fEndVal=m_iDisplayMaxVal;
	float iGapNum=0;
	fBeginVal=FloatValToInt(fBeginVal);
	fEndVal=FloatValToInt(fEndVal);
	iGapNum = fEndVal - fBeginVal;

	float iGapVal=1.0f;
	int iGapNumTemp=FloatValToInt(iGapNum);

#ifdef INVERSECHAPAGE_TEST_DEBUG
	CString strTemp = "";
	strTemp.Format("CLogarithmAxis::ResetYAxisDef():   %.3f,%.3f,%.3f,%d",fBeginVal,fEndVal,iGapNum,iGapNumTemp);
	AfxMessageBox(strTemp);
#endif

	float iBeginVal=GetBeginVal(m_iDisplayMinVal,iGapVal);
	GetOneYAxisHeight(iGapVal,1);

	int i=0;

	for (i=0;i<=iGapNumTemp;i++)
	{
		ResetOneYAxisDef(iBeginVal+i*iGapVal);
	}

	m_fYCarryOneGap=iGapVal;
}
void CLogarithmAxis::GetOneYAxisHeight(float iGap,BYTE bKind)
{
	int iHeight=m_rcY_Axis.Height();
	float iVal=m_iDisplayMaxVal-m_iDisplayMinVal;
	m_nYAxisOneGap=iGap*(float)iHeight/iVal;
}

void CLogarithmAxis::SetYAxisTenthScaleColor(COLORREF color)
{
	m_crYTenthScaleColor = color;
	ContinueInit();
}

COLORREF CLogarithmAxis::GetYAxisTenthScaleColor()
{
	return m_crYTenthScaleColor;
}

void CLogarithmAxis::SetXAxisTenthScaleColor(COLORREF color)
{
	m_crXTenthScaleColor = color;
	ContinueInit();
}
COLORREF CLogarithmAxis::GetXAxisTenthScaleColr()
{
	return m_crXTenthScaleColor;
}
void CLogarithmAxis::ResetOneYAxisDef(float m_dAxisScaleVal)
{
	int iHeight=m_rcY_Axis.Height();
	float iVal=m_iDisplayMaxVal-m_iDisplayMinVal;
	float f = m_rcY_Axis.bottom-(m_dAxisScaleVal-m_iDisplayMinVal)*((float)iHeight / iVal );
	int y=FloatValToInt(f);
	CAxisScaleData *odData=new CAxisScaleData();
	odData->FillIt(m_dAxisScaleVal,CPoint(m_rcY_Axis.right,y));
	m_oYAxisDef.AddTail(odData);
}

void CLogarithmAxis::DrawYAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio,CPoint ptOffset)
{
	CPoint pt;
	pt.x = m_rcWorkArea.left;
	pt.y = odData->m_ptAxisScale.y;
	pt.Offset(ptOffset);
	cDC->MoveTo(pt);

	pt.x = m_rcWorkArea.right;
	pt.y = odData->m_ptAxisScale.y;
	pt.Offset(ptOffset);
	cDC->LineTo(pt);
}
void CLogarithmAxis::DrawYAxisText(CDC *cDC,CAxisScaleData *odData,float fZoomRatio,CPoint ptOffset)
{
	char cStr[128];
	float fText=odData->m_dAxisScaleVal;
	fText=pow(10,fText);
	sprintf(cStr,"%f",fText);
	_ChopFloatString(cStr);
    long lHeight=(long)(m_lfVertFont.lfHeight * fZoomRatio);
    lHeight = abs(lHeight);
	CRect cR;
	cR.left=m_rcY_Axis.left;
	cR.top=odData->m_ptAxisScale.y-lHeight;
	cR.right=m_rcY_Axis.right-m_iVertGapLineLen1 * fZoomRatio;
	cR.bottom=odData->m_ptAxisScale.y+lHeight;
	cR.OffsetRect(ptOffset);
	CmDrawTextRect(cDC,CString(cStr),m_crVertColor,&cR,RGB(0,0,0),m_lfVertFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}
void CLogarithmAxis::DrawYAxisName(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{
	CRect cR;
	cR.left=m_rcBorder.left+2;
	cR.top=m_rcBorder.top;
	cR.right=m_rcY_Axis.right-3;
	cR.bottom=m_rcBorder.top+15*fZoomRatio;
	cR.OffsetRect(ptOffset);
	CmDrawTextRect(cDC,m_strYAxisName,m_crVertTitleColor,
				   &cR,RGB(0,0,0),m_lfVertTitleFont,
				   TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}
void CLogarithmAxis::DrawYAxis(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{
	int iNum=m_oYAxisDef.GetCount();
	if(iNum<=0)return;
	CPen cP;
	long lGap=(long)(abs(m_lfVertFont.lfHeight)*1.5 * fZoomRatio);
	cP.CreatePenIndirect(&m_penVert_WorkAreaLine);
	CPen *cOldP=cDC->SelectObject(&cP);
	int i=0;
	for (i=0;i<iNum;i++)
	{
		CAxisScaleData *odData=(CAxisScaleData*)m_oYAxisDef.GetAt(m_oYAxisDef.FindIndex(i));
		if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_SCALETEXT)
		{
			if( m_dwDisplayType & LOGARITHM_YAXIS_TEXT)
			{
				if(odData->m_ptAxisScale.y>=m_rcY_Axis.top)
					DrawYAxisText(cDC,odData,fZoomRatio,ptOffset);////标注
			}
		}
		if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_LINE)
		{
			if(m_dwDisplayType& LOGARITHM_YAXIS_LINE)
			{
				if ((odData->m_ptAxisScale.y>m_rcY_Axis.top)&&(odData->m_ptAxisScale.y<m_rcX_Axis.bottom))
				{
					DrawYAxisLine(cDC,odData,fZoomRatio,ptOffset);//网格
				}
			}
		}
	}
	cDC->SelectObject(cOldP);
	cP.DeleteObject();
	if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_TENTHSCALE)
		if(  m_dwDisplayType & LOGARITHM_YAXIS_SAWTOOTH1)
			DrawYSawtooth(cDC,0,fZoomRatio,ptOffset);
	if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_HALFSCCALE)
		if(  m_dwDisplayType & LOGARITHM_YAXIS_SAWTOOTH2)			
			DrawYSawtooth(cDC,1,fZoomRatio,ptOffset);
//	if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_NAME)
//		if(  lDisplayType & LOGARITHM_YAXIS_TEXT)						
//			DrawYAxisName(cDC,fZoomRatio,ptOffset);
}
///////////////靠工作区内的小锯齿
void CLogarithmAxis::DrawOneYSawtooth(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{
	CPen cP;
	cP.CreatePenIndirect(&m_penVert_WorkAreaShortLine);
	CPen *cOldP=cDC->SelectObject(&cP);
	int iDeltaY=0;
	float fVal=0;
	int i = 0;
	for (i=2;i<10;i++)
	{
		fVal=fCarryVal * i ;
		fVal=log10(fVal);
		float f = m_rcY_Axis.bottom-(fVal-m_iDisplayMinVal)*m_nYAxisOneGap;
		int y=FloatValToInt(f);

		CPoint cPt(cBegin.x,y);
		if((cPt.y<m_rcY_Axis.top)||(cPt.y>m_rcY_Axis.bottom))
			continue;
		cPt.Offset(ptOffset);
		cDC->MoveTo(cPt.x-1,cPt.y);
		cDC->LineTo(cPt.x-(long)(fZoomRatio*m_iVertGapLineLen3),cPt.y);
	}
	cDC->SelectObject(cOldP);
	cP.DeleteObject();

	if(m_dwDisplayType & LOGARITHMAXISDRAW_YAXIS_LINE)
	{
		cP.CreatePenIndirect(&m_penVert_WorkAreaLine);
		cOldP=cDC->SelectObject(&cP);
		for (i=2;i<10;i++)
		{
			fVal=fCarryVal * i ;
			fVal=log10(fVal);
			float f=m_rcY_Axis.bottom-(fVal-m_iDisplayMinVal)*m_nYAxisOneGap;
			int y=FloatValToInt(f);

			CPoint cPt(cBegin.x,y);
			if((cPt.y<m_rcY_Axis.top)||(cPt.y>m_rcY_Axis.bottom))continue;
			cPt.Offset(ptOffset);
			cDC->MoveTo(m_rcWorkArea.left+BOTTOMADD,cPt.y);
			cDC->LineTo((long)(fZoomRatio*m_rcWorkArea.right),cPt.y);
		}
		cDC->SelectObject(cOldP);
		cP.DeleteObject();
	}
}
///////////////大刻度
void CLogarithmAxis::DrawOneYSawtoothShadow(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{
	int iLen=(long)(fZoomRatio*m_iVertGapLineLen1);
	CPoint cPt(cBegin.x,cBegin.y);
	if((cPt.y>=(long)(fZoomRatio*m_rcY_Axis.top))&&(cPt.y<=(long)(fZoomRatio*m_rcY_Axis.bottom)))
	{
		cPt.Offset(ptOffset);
		DrawShadowHorzLine(cDC,cPt.x,cPt.y,iLen,m_crYUnitScaleColor,m_crYUnitScaleShadowColor);
	}
}
void CLogarithmAxis::DrawYSawtooth(CDC *cDC,BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;
	float fCarryVal=0;
	int i=0;
	for (i=0;i<m_oYAxisDef.GetCount();i++)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_oYAxisDef.GetAt(m_oYAxisDef.FindIndex(i));
		fCarryVal=pow(10,odData->m_dAxisScaleVal);
		if (i==0)
		{
			cBegin=CPoint(odData->m_ptAxisScale.x,odData->m_ptAxisScale.y+m_fXAxisOneGap);
			cEnd=odData->m_ptAxisScale;			
		}
		else
		{
			CAxisScaleData *odNewData=(CAxisScaleData *)m_oYAxisDef.GetAt(m_oYAxisDef.FindIndex(i-1));
			cBegin=odNewData->m_ptAxisScale;
			cEnd=odData->m_ptAxisScale;
		}
		if (bKind==0)
			DrawOneYSawtooth(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else
			DrawOneYSawtoothShadow(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		
	}
	if(m_oYAxisDef.GetCount()>=2)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_oYAxisDef.GetTail();
		cEnd=CPoint(odData->m_ptAxisScale.x,odData->m_ptAxisScale.y-m_nYAxisOneGap);
		cBegin=odData->m_ptAxisScale;
		fCarryVal=pow(10,odData->m_dAxisScaleVal);
		if (bKind==0)
			DrawOneYSawtooth(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else 
			DrawOneYSawtoothShadow(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
	}
}

//#######################################################################
//******************************关于X轴的绘制****************************
//#######################################################################

void CLogarithmAxis::InitXAxisDef(){m_oXAxisDef.DeleteAll();}
void CLogarithmAxis::EndXAxisDef(){m_oXAxisDef.DeleteAll();}


float CLogarithmAxis::GetXBeginVal(float lNowVal,float lGapVal)
{
	float ff,ff1;
	int iMul=1;
	ff=lNowVal/lGapVal;
	ff1=(int)ff;
	if(ff-ff1<0.99)	iMul=ff1;
	else	iMul=ff1+1;

	float fb=0;
	fb=lNowVal-(lNowVal - iMul*lGapVal);
	return fb;
}

void CLogarithmAxis::ResetXAxisDef()
{
	EndXAxisDef();

	float fBeginVal=m_iBeginPalace;
	float fEndVal=m_iEndPalace;
	float iGapNum=0;

	fBeginVal=FloatValToInt(fBeginVal);
	fEndVal=FloatValToInt(fEndVal);
	iGapNum = fEndVal - fBeginVal;

	int iGapNumTemp=FloatValToInt(iGapNum);
	float iGapVal=1.0f;
	float iBeginVal=GetXBeginVal(m_iBeginPalace,iGapVal);
	GetOneXAxisWidth(iGapVal,1);
	int i=0;
	for (i=0;i<=iGapNumTemp;i++)
		ResetOneXAxisDef(iBeginVal+i*iGapVal,0);
	m_fXCarryOneGap=iGapVal;
}
void CLogarithmAxis::GetOneXAxisWidth(float iGap,BYTE bKind)
{
	int iWidth=m_rcX_Axis.Width();
	float iVal=(m_iEndPalace-m_iBeginPalace);
	m_fXAxisOneGap=iGap*(float)iWidth/iVal;
}

void CLogarithmAxis::ResetOneXAxisDef(float m_dAxisScaleVal,BYTE bKind)
{
	int iWidth=m_rcX_Axis.Width();
	float iVal=(m_iEndPalace-m_iBeginPalace);//FloatValToInt
	float f=m_rcX_Axis.left+(m_dAxisScaleVal-m_iBeginPalace)*(float)iWidth/iVal;
	int x=FloatValToInt(f);
	CAxisScaleData *odData=new CAxisScaleData();
	int iIntegeralBeginPalace=0;//GetIntegeralBeginPalace();

	if(bKind==0) 
	{
		float f=(float)(m_dAxisScaleVal-iIntegeralBeginPalace);
		odData->FillIt(f,CPoint(x,m_rcX_Axis.top+BOTTOMADD));
	}
	else 
	{
		float f=(float)(m_dAxisScaleVal-iIntegeralBeginPalace);
		odData->FillIt(f, CPoint(x,m_rcX_Axis.top+BOTTOMADD));
	}
	m_oXAxisDef.AddTail(odData);
}
void CLogarithmAxis::DrawXAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio,CPoint ptOffset)
{
	CPoint pt;
	pt.x = odData->m_ptAxisScale.x;
	pt.y = (long)(fZoomRatio*m_rcWorkArea.top+m_iShadow);
	pt.Offset(ptOffset);
	cDC->MoveTo(pt);

	pt.x = odData->m_ptAxisScale.x;
	pt.y = (long)(fZoomRatio*m_rcWorkArea.bottom+BOTTOMADD);
	pt.Offset(ptOffset);
	cDC->LineTo(pt);
}

CRect  CLogarithmAxis::DrawXAxisText(CDC *cDC,CAxisScaleData *odData,BOOL bAddUint,BOOL bReallyDraw,float fZoomRatio,CPoint ptOffset)
{
	CRect cBack(-1,-1,-1,-1);
	char cStr[128];
	float fText=odData->m_dAxisScaleVal;
	fText=pow(10,fText);
	sprintf(cStr,"%.4f",fText);
	_ChopFloatString(cStr);
	CRect cR1=CRect(odData->m_ptAxisScale.x-(long)(fZoomRatio * 20),odData->m_ptAxisScale.y+(long)(fZoomRatio * 7),odData->m_ptAxisScale.x+(long)(fZoomRatio * 24),odData->m_ptAxisScale.y+(long)(fZoomRatio * 20));
	CRect cR;

	if(m_dwDrawXAxisTextType==1)
	{
		cR=CRect(odData->m_ptAxisScale.x-cR1.Width()/2-2,odData->m_ptAxisScale.y+(long)(fZoomRatio * m_iHorzGapLineLen1),
			 odData->m_ptAxisScale.x+cR1.Width()/2+2,odData->m_ptAxisScale.y+(long)(fZoomRatio * m_iHorzGapLineLen1)+cR1.Height());
		cR.OffsetRect(ptOffset);
		if(bReallyDraw)CmDrawTextRect(cDC,CString(cStr),m_crHorzColor,cR,RGB(0,0,0),m_lfHorzFont,TRANSPARENT,DT_VCENTER|DT_CENTER,0);
	}
	else
	{
		cR=CRect(odData->m_ptAxisScale.x+3,odData->m_ptAxisScale.y+(long)(fZoomRatio * m_iHorzGapLineLen3),
			 odData->m_ptAxisScale.x+cR1.Width()+2,odData->m_ptAxisScale.y+(long)(fZoomRatio * m_iHorzGapLineLen1)+cR1.Height());
		cR.OffsetRect(ptOffset);
		if(bReallyDraw)CmDrawTextRect(cDC,CString(cStr),m_crHorzColor,cR,RGB(0,0,0),m_lfHorzFont,TRANSPARENT,0,0);
	}
	return cR;
}
void CLogarithmAxis::DrawXAxisName(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	int iLen=m_strXAxisName.GetLength();
	CFont CF;
	CF.CreateFontIndirect(&m_lfHorzTitleFont);
	CFont *c=pDC->SelectObject(&CF);
	TEXTMETRIC textMetric;
	pDC->GetTextMetrics(&textMetric);
	pDC->SelectObject(c);
	iLen=textMetric.tmAveCharWidth *(iLen+1);
	
	//20230830 suyang L336D中获取不到字符串宽度，当小于1时重新赋值为1，否则会出现闪退
	if (iLen<1)
	{
		iLen = 1;
	}

	CRect cR;
	cR.left=m_rcX_Axis.right-iLen;
	cR.top=m_rcBorder.bottom-(long)(fZoomRatio * 10);
	cR.right= m_rcX_Axis.right;
	cR.bottom=m_rcBorder.bottom;
	cR.OffsetRect(ptOffset);
	CmDrawTextRect(pDC,m_strXAxisName,m_crHorzTitleColor,&cR,RGB(0,0,0),
				   m_lfHorzTitleFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}

void CLogarithmAxis::DrawXAxis(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{
	int iNum=m_oXAxisDef.GetCount();
	if(iNum<=0)return;
	CPen cP;
	cP.CreatePenIndirect(&m_penHorz_WorkAreaLine);
	CPen *cOldB=cDC->SelectObject(&cP);
	float iIntgerEndPalace=m_iEndPalace;//GetIntegeralEndPalace();
	if(iIntgerEndPalace<0)iIntgerEndPalace=0;

	int i=0;
	for (i=0;i<iNum;i++)
	{
		CAxisScaleData *odData=(CAxisScaleData*)m_oXAxisDef.GetAt(m_oXAxisDef.FindIndex(i));
		long m_dAxisScaleVal=m_dwDisplayType & LOGARITHM_XAXIS_LINE;
		if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_XAXIS_LINE)
		{
			if(m_dAxisScaleVal)
			{
				if ((odData->m_ptAxisScale.x>m_rcX_Axis.left)&&(odData->m_ptAxisScale.x<m_rcX_Axis.right))
				{
					DrawXAxisLine(cDC,odData,fZoomRatio,ptOffset);
				}
			}
		}
		
	}
	if(((m_lAxisDrawStyle & LOGARITHMAXISDRAW_XAXIS_SCALETEXT))&&((m_dwDisplayType & LOGARITHM_XAXIS_TEXT)))
	{
		int iStep=iNum;
		int i=0;
	for (i=0;i<iNum;i++)
		{
			CAxisScaleData *odData=(CAxisScaleData*)m_oXAxisDef.GetAt(m_oXAxisDef.FindIndex(i));
		}
		BOOL bDrawUint=FALSE;
		for (i=0;i<iStep-1;i++)
		{
			CAxisScaleData *odData=(CAxisScaleData*)m_oXAxisDef.GetAt(m_oXAxisDef.FindIndex(i));
			if(odData->m_ptAxisScale.x<m_rcX_Axis.left) 
				continue;
			DrawXAxisText(cDC,odData,bDrawUint,TRUE,fZoomRatio,ptOffset);
		}
		CAxisScaleData *odData=(CAxisScaleData*)m_oXAxisDef.GetAt(m_oXAxisDef.FindIndex(i));
		if(odData->m_ptAxisScale.x > m_rcX_Axis.left) 
		{
			char cStr[128];//lfHorzFont
			sprintf(cStr,"%.4f",(float)odData->m_dAxisScaleVal);
			int iLen=strlen(cStr);
			float f=0;
			if(cStr[iLen-1]>='5')
			{
				cStr[iLen-1]=0;				f=atof(cStr);
				if(f>=0.0001)f=f+0.001;
				else f=f-0.001;
				sprintf(cStr,"%.4f",f);
			}	
			////////////////////////////////获得坐标轴名称字体长度
			int iLenAxis=m_strXAxisName.GetLength();
			CFont CF;
			CF.CreateFontIndirect(&m_lfHorzTitleFont);
			CFont *c=cDC->SelectObject(&CF);
			TEXTMETRIC *textMetric=new TEXTMETRIC;
			cDC->GetTextMetrics(textMetric);
			cDC->SelectObject(c);
			iLenAxis=textMetric->tmMaxCharWidth *(iLenAxis+1);
			CF.DeleteObject();
			///////////////////////////////////////////////////////

			////////////////////////////////获得坐标轴标注]字体长度
			_ChopFloatString(cStr);
			iLen=strlen(cStr);
			CF.CreateFontIndirect(&m_lfHorzFont);
			c=cDC->SelectObject(&CF);
			cDC->GetTextMetrics(textMetric);
			cDC->SelectObject(c);
			iLen=textMetric->tmMaxCharWidth * iLen;
			CF.DeleteObject();
			delete textMetric;
			///////////////////////////////////////////////////////
			//if(odData->m_ptAxisScale.x+iLen < cX_Axis.right-iLenAxis)
				DrawXAxisText(cDC,odData,bDrawUint,TRUE,fZoomRatio,ptOffset);
		}
	}
	cDC->SelectObject(cOldB);
	cP.DeleteObject();
	if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_XAXIS_TENTHSCALE)
		if(m_dwDisplayType & LOGARITHM_XAXIS_SAWTOOTH1)
			DrawXSawtooth(cDC,0,fZoomRatio,ptOffset);
	if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_XAXIS_HALFSCCALE)
		if(m_dwDisplayType & LOGARITHM_XAXIS_SAWTOOTH2)
			DrawXSawtooth(cDC,1,fZoomRatio,ptOffset);
		
	//DrawXAxisName(cDC,fZoomRatio,ptOffset);
}

void CLogarithmAxis::DrawOneXSawtooth(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{                                     
	CPen cP;
	cP.CreatePenIndirect(&m_penHorz_WorkAreaShortLine);
	CPen *pOldPen=cDC->SelectObject(&cP);
	float fVal=0;
	int i=2;
	for (i=0;i<10;i++)
	{
		fVal=fCarryVal * i ;
		fVal=log10(fVal);
		float f=m_rcX_Axis.left+(fVal-m_iBeginPalace)*m_fXAxisOneGap;
		int x=FloatValToInt(f);

		CPoint cPt(x,cBegin.y);
		if((cPt.x<m_rcX_Axis.left)||(cPt.x>m_rcX_Axis.right)) continue;
		cPt.Offset(ptOffset);
		cDC->MoveTo(cPt.x,cPt.y+(long)(fZoomRatio*1));
		cDC->LineTo(cPt.x,cPt.y+(long)(fZoomRatio*m_iHorzGapLineLen3));
	}
	cDC->SelectObject(pOldPen);
	cP.DeleteObject();

	if(m_dwDisplayType & LOGARITHMAXISDRAW_XAXIS_LINE)
	{
		cP.CreatePenIndirect(&m_penHorz_WorkAreaLine);
		CPen *cOldB=cDC->SelectObject(&cP);
		for (i=2;i<10;i++)
		{
			fVal=fCarryVal * i ;
			fVal=log10(fVal);
			float f=m_rcX_Axis.left+(fVal-m_iBeginPalace)*m_fXAxisOneGap;
			int x=FloatValToInt(f);

			CPoint cPt(x,cBegin.y);
			if((cPt.x<m_rcX_Axis.left)||(cPt.x>m_rcX_Axis.right)) continue;
			cPt.Offset(ptOffset);			
			cDC->MoveTo(cPt.x,m_rcWorkArea.top+(long)(fZoomRatio*BOTTOMADD));
			cDC->LineTo(cPt.x,(long)(fZoomRatio*m_rcWorkArea.bottom));
		}
		cDC->SelectObject(pOldPen);
		cP.DeleteObject();
	}

}
void CLogarithmAxis::DrawOneXSawtoothShadow(CDC *cDC, CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{
	int iLen[2]={(long)(fZoomRatio*m_iHorzGapLineLen1),(long)(fZoomRatio*m_iHorzGapLineLen2)};
	int i=0;
	for (i=0;i<1;i++)
	{
		int iGapVal=FloatValToInt((float)((float)m_fXAxisOneGap/2.0*i));
		CPoint cPt(cBegin.x+iGapVal,cBegin.y);
		if((cPt.x<m_rcX_Axis.left)||(cPt.x>m_rcX_Axis.right)) continue;
		cPt.Offset(ptOffset);
		DrawShadowVertLine(cDC,cPt.x,cPt.y,iLen[i],m_crXUnitScaleColor,m_crXUnitScaleShadowColor);
	}
}
void CLogarithmAxis::DrawXSawtooth(CDC *cDC,BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;
	float fCarryVal=0;
	int i=0;
	for (i=0;i<m_oXAxisDef.GetCount();i++)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_oXAxisDef.GetAt(m_oXAxisDef.FindIndex(i));
		fCarryVal=pow(10,odData->m_dAxisScaleVal);
		if (i==0)
		{
			cBegin=CPoint(odData->m_ptAxisScale.x-m_fXAxisOneGap,odData->m_ptAxisScale.y);
			cEnd=odData->m_ptAxisScale;
		}
		else 
		{
				CAxisScaleData *odNewData=(CAxisScaleData *)m_oXAxisDef.GetAt(m_oXAxisDef.FindIndex(i-1));
				cBegin=odNewData->m_ptAxisScale;
				cEnd=odData->m_ptAxisScale;
		}	
		if (bKind==0)
			DrawOneXSawtooth(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else 
			DrawOneXSawtoothShadow(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
	}
	if(m_oXAxisDef.GetCount()>=2)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_oXAxisDef.GetTail();
		cEnd=CPoint(odData->m_ptAxisScale.x+m_fXAxisOneGap,odData->m_ptAxisScale.y);
		cBegin=odData->m_ptAxisScale;
		if (bKind==0)DrawOneXSawtooth(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else DrawOneXSawtoothShadow(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
	}
}

void CLogarithmAxis::DrawIt(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{

	if(m_lAxisDrawStyle &LOGARITHMAXISDRAW_WORKAREA)
//		if(lDisplayType&LOGARITHMAXISDRAW_WORKAREA)
		DrawArea(cDC,fZoomRatio,ptOffset);
	
//	if(m_lAxisDrawStyle &LOGARITHM_YAXIS)	////绘制Y轴
//		if(lDisplayType &LOGARITHM_YAXIS)
			DrawYAxis(cDC,fZoomRatio,ptOffset);
//	if(m_lAxisDrawStyle &LOGARITHM_XAXIS)	////绘制X轴	
//		if(lDisplayType &LOGARITHM_XAXIS)
			DrawXAxis(cDC,fZoomRatio,ptOffset);
	
	if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_XAXIS_NAME)
		DrawXAxisName(cDC,fZoomRatio,ptOffset);
			
	if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_NAME)
		DrawYAxisName(cDC,fZoomRatio,ptOffset);
			
	if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_AXISTITLE)
		DrawAxisTitle(cDC,fZoomRatio,ptOffset);

	if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_AXISBODER)
		DrawFrame(cDC,fZoomRatio,ptOffset);

}
void CLogarithmAxis::DrawAxisTitle(CDC *pDC,float fZoomRatio,CPoint ptOffset)
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
	rect.left = m_rcBorder.left;
	rect.top = m_rcBorder.top ;
	rect.right = m_rcBorder.right;
	rect.bottom = m_rcBorder.top+m_iTopGap;
	
	CPoint ptCenter = rect.CenterPoint();
	rect.left = ptCenter.x - iLen;
	rect.right = ptCenter.x + iLen;
	
	rect.OffsetRect(ptOffset);
	
	CmDrawTextRect(pDC,m_strAxisTitle,m_crAxisTitleFont,&rect,RGB(0,0,0),
		lf,TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}

void CLogarithmAxis::DrawFrame(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rect = m_rcBorder;
	rect.OffsetRect(ptOffset);
	Draw3dRectBorder(pDC,&rect,m_iFrameShadow,m_crFrameLeftTopColor,m_crFrameRightBottomColor);
}

void CLogarithmAxis::ModifyWorkArea(CRect* pRect,BOOL bInit,float fZoomRatio,CPoint ptOffset)
{
	CRect cNewRect =pRect[0];
	MakeWorkAreaLegal(cNewRect);
	m_rcBorder=cNewRect;

	m_rcX_Axis.bottom=cNewRect.bottom-(long)(fZoomRatio*m_iBottomGap);
	m_rcX_Axis.top=m_rcX_Axis.bottom-(long)(fZoomRatio*m_iHorzAreaWidth);
	
	m_rcWorkArea.bottom=m_rcX_Axis.top;
	m_rcWorkArea.top=cNewRect.top+(long)(fZoomRatio*m_iTopGap);
	
	m_rcY_Axis.left=cNewRect.left+(long)(fZoomRatio*m_iLeftGap);
	m_rcY_Axis.right=m_rcY_Axis.left+(long)(fZoomRatio*m_iVertAreaWidth);

	m_rcWorkArea.left=m_rcY_Axis.right;
	m_rcWorkArea.right=cNewRect.right-(long)(fZoomRatio*m_iRightGap);

	m_rcX_Axis.left=m_rcWorkArea.left;
	m_rcX_Axis.right=m_rcWorkArea.right;

	m_rcY_Axis.top=m_rcWorkArea.top;
	m_rcY_Axis.bottom=m_rcWorkArea.bottom;

}

BOOL CLogarithmAxis::MakeWorkAreaLegal(CRect &cNewRect)
{
	if(cNewRect.left<0)cNewRect.left=0;
	if(cNewRect.right<0)cNewRect.right=0;
	if(cNewRect.top<0)cNewRect.top=0;
	if(cNewRect.bottom<0)cNewRect.bottom=0;
	if (cNewRect.Height()<30)cNewRect.bottom=cNewRect.top+30;
	if (cNewRect.Width()<50)cNewRect.right=cNewRect.left+30;
	return TRUE;
}

void CLogarithmAxis::DrawWorkAreaBorder(CDC *pDC)//,cR,iGap,crLeftTop,crRightBottom);
{
	CRect cR=GetDrawWorkAreaRect();
	Draw3dRectBorder(pDC,&cR,m_iShadow,m_crBkLeftTopColor,m_crBkRightBottomColor);
}

void CLogarithmAxis::DrawArea(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect cR=GetDrawWorkAreaRect();
	cR.OffsetRect(ptOffset);
	Draw3dRectByMe(pDC,cR,(long)(fZoomRatio*m_iShadow),m_crBkLeftTopColor,
				   m_crBkRightBottomColor,m_crBkGroundColor);
}

void CLogarithmAxis::DrawAxisBack(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	//绘制背景
	CBrush brush;
	brush.CreateSolidBrush(m_crAxisBackColor);
	pDC->FillRect(m_rcBorder,&brush);
	brush.DeleteObject();
	
}

CRect CLogarithmAxis::GetDrawWorkAreaRect()
{
	CRect cR=m_rcWorkArea;
	cR.bottom+=3;cR.right+=2;
	return cR;
}

void CLogarithmAxis::SetAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY)
{
	//对数坐标系
	m_iOldBeginPalace=m_iBeginPalace;
	m_iOldEndPalace=m_iEndPalace;
	m_iOldDisplayMinVal=m_iDisplayMinVal;
	m_iOldDisplayMaxVal=m_iDisplayMaxVal;
	m_iBeginPalace=dMinX;	
	m_iEndPalace=dMaxX;		
	m_iDisplayMinVal=dMinY;	
	m_iDisplayMaxVal=dMaxY;	
	
	ModifyWorkArea(&m_rectAxis,1);
	ResetYAxisDef();
	ResetXAxisDef();
	
}

long CLogarithmAxis::GetAxisMinMaxVal(double *dMinX,double *dMinY,double *dMaxX,double *dMaxY)
{
	*dMinX=m_iBeginPalace;
	*dMaxX=m_iEndPalace;
	*dMinY=m_iDisplayMinVal;
	*dMaxY=m_iDisplayMaxVal;
	
	return 0;
}

void CLogarithmAxis::SetBorder(const CRect &rcBorder)
{
	m_rectAxis = rcBorder;

	int iH=0,iW=0;
	iH=m_rectAxis.Height();
	iW=m_rectAxis.Width();
	iH=iH-m_iBottomGap-m_iTopGap-m_iHorzAreaWidth;
	iW=iW-m_iLeftGap-m_iRightGap-m_iVertAreaWidth;
	if(iW<=0)
		iW=20;
	if(iH<=0)
		iH=20;

	m_rectAxis.bottom=m_rectAxis.top+iH + m_iBottomGap + m_iTopGap + m_iHorzAreaWidth;
	m_rectAxis.right=m_rectAxis.left+iW + m_iLeftGap + m_iRightGap + m_iVertAreaWidth;
	
	if (m_bAxisXYUnitLock)
	{
		iH=m_rectAxis.Height();
		iW=m_rectAxis.Width();
		iH=iH-m_iBottomGap-m_iTopGap-m_iHorzAreaWidth;
		iW=iW-m_iLeftGap-m_iRightGap-m_iVertAreaWidth;
		
		double fCoef=0;//(float)iW/iH;
		double fVer = (m_iOldDisplayMaxVal - m_iOldDisplayMinVal) / iH;
		double fHor = (m_iOldEndPalace - m_iOldBeginPalace) / iW;
		if(fVer>fHor)
		{
			fCoef=fVer / fHor;
			m_iBeginPalace   = m_iOldBeginPalace*fCoef;
			m_iEndPalace     = m_iOldEndPalace * fCoef;
			m_iDisplayMinVal = m_iOldDisplayMinVal;
			m_iDisplayMaxVal = m_iOldDisplayMaxVal;
		}
		else
		{
			fCoef=fHor / fVer;
			m_iDisplayMinVal = m_iOldDisplayMinVal*fCoef;
			m_iDisplayMaxVal = m_iOldDisplayMaxVal*fCoef;
			m_iBeginPalace   = m_iOldBeginPalace;
			m_iEndPalace     = m_iOldEndPalace;
		}
	}
	
	ModifyWorkArea(&m_rectAxis,1);
	ResetYAxisDef();
	ResetXAxisDef();
	InitAxisAttr();
}

void CLogarithmAxis::ResetAxis()
{
	//i-t
// 	m_iBeginPalace=0;
// 	m_iEndPalace=10;
// 	m_iDisplayMinVal=0;
// 	m_iDisplayMaxVal= 10;
	m_iOldBeginPalace=m_iBeginPalace;
	m_iOldEndPalace=m_iEndPalace;
	m_iOldDisplayMinVal=m_iDisplayMinVal;
	m_iOldDisplayMaxVal=m_iDisplayMaxVal;
	ResetXAxisDef();
	ResetYAxisDef();
	
}

void CLogarithmAxis::InitAxisAttr()
{
	CRect rectWork=m_rcWorkArea;
	float fYValue=0,fXValue=0;
	float fYMaxValue=0,fYMinValue=0,fXMaxValue=0,fXMinValue=0;
	CPoint pointCenter=CPoint(0,0);
	fYMaxValue=m_iDisplayMaxVal;
	fYMinValue=m_iDisplayMinVal;
	int iHeight=rectWork.Height();
	float fValYOneGap=iHeight/(fYMaxValue-fYMinValue);///Y轴实际坐标与实际值的比率
	///////////////////////////////////////////////
	fXMaxValue=m_iEndPalace;
	fXMinValue=m_iBeginPalace;
	int iWidth=rectWork.Width();
	float fValXOneGap=iWidth/(fXMaxValue-fXMinValue);//X轴实际坐标与实际值的比率
	/////坐标原点在屏幕上的位置
	float f=rectWork.left + (0-fXMinValue)*fValXOneGap;
	pointCenter.x=FloatValToInt(f);
	f=rectWork.bottom -(0-fYMinValue)*fValYOneGap;
	pointCenter.y=FloatValToInt(f);
	/////// 
	m_fOneYGapValue=fValYOneGap;
	m_fOneXGapValue=fValXOneGap;
	m_ptCenterLogInDv=pointCenter;

}
void CLogarithmAxis::ZoomIn(float fZoomIn)
{
	double fMinX=0,fMinY=0,fMaxX=0,fMaxY=0;
	fMinX = m_iBeginPalace / fZoomIn;
	fMaxX = m_iEndPalace /fZoomIn;
	fMinY = m_iDisplayMinVal / fZoomIn;
	fMaxY = m_iDisplayMaxVal / fZoomIn;
	
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
	
	fCoefX = (m_iOldEndPalace - m_iOldBeginPalace) / (fMaxX-fMinX);
	fCoefY = (m_iOldDisplayMaxVal - m_iOldDisplayMinVal) / (fMaxX-fMinX);
	
	fCoefX=fabs(fCoefX);
	fCoefY=fabs(fCoefY);
	if(fCoefX>m_dMaxZoomMultiple || fCoefY>m_dMaxZoomMultiple)
		return;
	
	SetAxisMinMaxVal(fMinX,fMinY,fMaxX,fMaxY);
}

void CLogarithmAxis::ZoomIn(double dMinX,double dMaxX,double dMinY,double dMaxY)
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
	SetAxisMinMaxVal(dMinX,dMinY,dMaxX,dMaxY);	
}

void CLogarithmAxis::ZoomIn(long lLeft,long lTop,long lRight,long lBottom)
{
	CPoint ptLeftTop = CPoint(lLeft,lTop);
	CPoint ptRightBottom = CPoint(lRight,lBottom);

	double dMinX,dMaxX,dMinY,dMaxY;
	double dx,dy;
	dMinX = dMaxX = dMinY = dMaxY = 0;
	dx = dy = 0;
	
	DevicePointToLogicPoint(ptLeftTop,&dMinX,&dMaxY, 0);
	DevicePointToLogicPoint(ptRightBottom,&dMaxX,&dMinY, 0);
	
	ZoomIn(dMinX,dMaxX,dMinY,dMaxY);
}

void CLogarithmAxis::ZoomOut(float fZoomOut)
{
	double fMinX=0,fMinY=0,fMaxX=0,fMaxY=0;
	fMinX = m_iBeginPalace * fZoomOut;
	fMaxX = m_iEndPalace * fZoomOut;
	fMinY = m_iDisplayMinVal * fZoomOut;
	fMaxY = m_iDisplayMaxVal * fZoomOut;
	
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
	
	fCoefX=(fMaxX-fMinX) / (m_iOldEndPalace - m_iOldBeginPalace)  ;
	fCoefY=(fMaxY-fMinY) / (m_iOldDisplayMaxVal - m_iOldDisplayMinVal) ;
	
	fCoefX=fabs(fCoefX);
	fCoefY=fabs(fCoefY);
	if(fCoefX>m_dMaxZoomMultiple || fCoefY>m_dMaxZoomMultiple)
		return;

	SetAxisMinMaxVal(fMinX,fMinY,fMaxX,fMaxY);	
}

void CLogarithmAxis::Move(float fXOffset,float fYOffset)
{
	m_iEndPalace     -= fXOffset * m_fXCarryOneGap;
	m_iBeginPalace   -= fXOffset * m_fXCarryOneGap;
	m_iDisplayMaxVal -= fYOffset * m_fYCarryOneGap;
	m_iDisplayMinVal -= fYOffset * m_fYCarryOneGap;
	
	ResetYAxisDef();
	ResetXAxisDef();
	InitAxisAttr();
}

////////////////////////////////////////////////////////////////////
// void CLogarithmAxis::LogicPointToDevicePoint(float fx,float fy,CPoint *pPoint)
// {
// 	//iYAxisOneGap		Y轴实际坐标与实际值的比率
// 	//iXAxisOneGap		X轴实际坐标与实际值的比率
// 	if(fx<0 || fy<0)return ;
// 	float fXVal=log10(fx);
// 	float fYVal=log10(fy);
// 	fXVal = m_rcX_Axis.left+(fXVal-m_iBeginPalace)*m_fXAxisOneGap;
// 	fYVal = m_rcY_Axis.bottom-(fYVal-m_iDisplayMinVal)*m_nYAxisOneGap;
// 	pPoint->x=FloatValToInt(fXVal);
// 	pPoint->y=FloatValToInt(fYVal);;
// }
// //从实际坐标获取实际坐标所代表的值
// void CLogarithmAxis::DevicePointToLogicPoint(CPoint point,double *fx,double *fy)
// {
// 	//iYAxisOneGap		Y轴实际坐标与实际值的比率
// 	//iXAxisOneGap		X轴实际坐标与实际值的比率
// 	double fXVal =m_iBeginPalace + ((double)point.x-(double)m_rcX_Axis.left)/m_fXAxisOneGap;
// 	double fYVal =((double)m_rcY_Axis.bottom-(double)point.y)/m_nYAxisOneGap + m_iDisplayMinVal;
// 	*fx=pow(10,fXVal);
// 	*fy=pow(10,fYVal);
// }

////////////////////////////////////////////////////////////////

long CLogarithmAxis::GetXAxisMinSawGapWidth(long *nValue)
{
	*nValue = m_fOneXGapValue;
	
	return 0;
}

long CLogarithmAxis::SetXAxisMinSawGapWidth(long nValue)
{
	m_fOneXGapValue = nValue;

	return 0;
}

long CLogarithmAxis::GetYAxisMinSawGapHeight(long *nValue)
{
	*nValue = m_fOneYGapValue;

	return 0;
}
long CLogarithmAxis::SetYAxisMinSawGapHeight(long nValue)
{
	m_fOneYGapValue = nValue;

	return 0;
}

long CLogarithmAxis::GetXAxisType(long *nValue)
{
	*nValue = m_lAxisType;

	return 0;
}

long CLogarithmAxis::SetXAxisType(long nValue)
{
	 m_lAxisType = nValue;

	 return 0;
}
long CLogarithmAxis::SetXAxisMaxUnitCount(long nValue)
{
	m_lXAxisMaxUnitCount = nValue;

	return 0;
}

long CLogarithmAxis::GetXAxisMaxUnitCount(long *nValue)
{
	*nValue = m_lXAxisMaxUnitCount;

	return 0;
}

long CLogarithmAxis::SetYAxisMaxUnitCount(long nValue)
{
	m_lYAxisMaxUnitCount = nValue;

	return 0;
}
long CLogarithmAxis::GetYAxisMaxUnitCount(long *nValue)
{
	*nValue = m_lYAxisMaxUnitCount;

	return 0;
}

long CLogarithmAxis::SetAxisXYUnitLock(long nValue)
{
	m_bAxisXYUnitLock = nValue;

	return 0;
}

long CLogarithmAxis::GetAxisXYUnitLock(long *nValue)
{
	*nValue = m_bAxisXYUnitLock;

    return 0;
}

//坐标系统的绘制类型,2005.08.12添加
long CLogarithmAxis::SetAxisDrawStyle(long nValue)
{
	
	m_lAxisDrawStyle = nValue;
	
	return 0;
}

long CLogarithmAxis::GetAxisDrawStyle(long *nValue)
{
	
	*nValue = m_lAxisDrawStyle;
	
    return 0;
}
long CLogarithmAxis::SetAxisDrawStyleBit(long nValue)
{

	m_lAxisDrawStyle |= nValue;
	
	return 0;
}
long CLogarithmAxis::ClearAxisDrawStyleBit(long nValue)
{

	m_lAxisDrawStyle &= (~nValue);
	
	return 0;
}


long CLogarithmAxis::SetXAxisTextDrawStyle(long nValue)
{
	m_dwDrawXAxisTextType = nValue;

	return 0;
}

long CLogarithmAxis::GetXAxisTextDrawStyle(long *nValue)
{
	*nValue = m_dwDrawXAxisTextType;

	return 0;
}

long CLogarithmAxis::SetAxisTitle(const CString & bstrValue)
{
/*
	char pszValue[MAX_PATH];
	memset(pszValue,0,MAX_PATH);
	CString_to_char(bstrValue,pszValue);*/

	m_strAxisTitle = bstrValue;

	return 0;
}
long CLogarithmAxis::GetAxisTitle(CString *pbstrValue)
{
	CString sAxisTitle;
	sAxisTitle = m_strAxisTitle;
	*pbstrValue = sAxisTitle.AllocSysString();
	
	return 0;
}

long CLogarithmAxis::SetAxisTitleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName)
{
	LOGFONT   lfAxisTitleFont;
	lfAxisTitleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet
		,(BYTE)lfOutPrecision,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,lfFaceName);
	m_lfAxisTitleFont = lfAxisTitleFont;

	return 0;
}

long CLogarithmAxis::GetAxisTitleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName)
{
	CString sFaceName;
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
long CLogarithmAxis::SetAxisTitleFontColor(long nValue)
{
	COLORREF m_crTitleColor;
	m_crTitleColor = (COLORREF)nValue;
	m_crAxisTitleFont = m_crTitleColor;

	return 0;
}

long CLogarithmAxis::GetAxisTitleFontColor(long *nValue)
{
	COLORREF m_crAxisTitleFontColor;
	m_crAxisTitleFontColor = m_crAxisTitleFont;
	*nValue = (long)m_crAxisTitleFontColor;

	return 0;
}

long CLogarithmAxis::SetAxisBackColor(long nValue)
{
	COLORREF m_crBackColor;
	m_crBackColor = (COLORREF)nValue;
	m_crAxisBackColor = m_crBackColor;

	return 0;
}
long CLogarithmAxis::GetAxisBackColor(long *nValue)
{
	COLORREF m_crBackColor;
	m_crBackColor = m_crAxisBackColor;
    *nValue = (long)m_crBackColor;

	return 0;
}

long CLogarithmAxis::SetWorkAreaBkColor(long nValue)
{
	COLORREF m_crBKColor;
	m_crBKColor = (COLORREF)nValue;
	m_crBkGroundColor = m_crBKColor;

	return 0;
}

long CLogarithmAxis::GetWorkAreaBkColor(long *nValue)
{
	COLORREF m_crBKColor;
	m_crBKColor = m_crBkGroundColor;
	*nValue = (long)m_crBKColor;

	return 0;
}
long CLogarithmAxis::SetWorkAreaBorderLeftTopColor(long nValue)
{
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = (COLORREF)nValue;
	m_crBkLeftTopColor = m_crLeftTopColor;

	return 0;
}

long CLogarithmAxis::GetWorkAreaBorderLeftTopColor(long *nValue)
{
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = m_crBkLeftTopColor;
	*nValue = (long)m_crLeftTopColor;

	return 0;
}

long CLogarithmAxis::SetWorkAreaBorderRightBottomColor(long nValue)
{
	COLORREF m_crRightBottomColor;
	m_crRightBottomColor = (COLORREF)nValue;
	m_crBkRightBottomColor = m_crRightBottomColor;

	return 0;
}
long CLogarithmAxis::GetWorkAreaBorderRightBottomColor(long *nValue)
{
	COLORREF m_crRightBottomColor;
	m_crRightBottomColor = m_crBkRightBottomColor;
	*nValue = (long)m_crRightBottomColor;

	return 0;
}

long CLogarithmAxis::SetWorkAreaBorderShadow(long nValue)
{
	m_iShadow = nValue;

	return 0;
}

long CLogarithmAxis::GetWorkAreaBorderShadow(long *nValue)
{

	*nValue = m_iShadow;

	return 0;
}

//坐标系统边框的颜色
long CLogarithmAxis::SetFrameLeftTopColor(long nValue)
{
	m_crFrameLeftTopColor = (COLORREF)nValue;
		
	return 0;
}

long CLogarithmAxis::GetFrameLeftTopColor(long *nValue)
{
	*nValue = (long)(m_crFrameLeftTopColor);

	return 0;
}

long CLogarithmAxis::SetFrameRightBottomColor(long nValue)
{
	m_crFrameRightBottomColor = (COLORREF)nValue;
		
	return 0;
}

long CLogarithmAxis::GetFrameRightBottomColor(long *nValue)
{
	*nValue = (long)(m_crFrameRightBottomColor);
	
	return 0;
}

//坐标系统边框边界阴影
long CLogarithmAxis::SetFrameShadow(long nValue)
{
	
	m_iFrameShadow = nValue;

	return 0;
}

long CLogarithmAxis::GetFrameShadow(long *nValue)
{
	
	*nValue = m_iFrameShadow;

	return 0;
}


long CLogarithmAxis::SetYUnitScaleColor(long nValue)
{
	COLORREF m_crYUnitScaleColor;
	m_crYUnitScaleColor = (COLORREF)nValue;
	m_crYUnitScaleColor = m_crYUnitScaleColor;

	return 0;
}

long CLogarithmAxis::GetYUnitScaleColor(long *nValue)
{
	*nValue = (long)m_crYUnitScaleColor;

	return 0;
}

long CLogarithmAxis::SetYUnitScaleShadowColor(long nValue)
{
	COLORREF m_crShadowColor;
	m_crShadowColor = (COLORREF)nValue;
	m_crYUnitScaleShadowColor = m_crShadowColor;

	return 0;
}
long CLogarithmAxis::GetYUnitScaleShadowColor(long *nValue)
{
	COLORREF m_crShadowColor;
	m_crShadowColor = m_crYUnitScaleShadowColor;
	*nValue = (long)m_crShadowColor;

	return 0;
}

long CLogarithmAxis::SetYAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName)
{
	LOGFONT   m_lfYAxisScaleFont;
	m_lfYAxisScaleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,lfFaceName);
	m_lfVertFont = m_lfYAxisScaleFont;

	return 0;
}

long CLogarithmAxis::GetYAxisScaleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName)
{
	LOGFONT m_lfYAxisScaleFont;
	CString sFaceName;
	m_lfYAxisScaleFont = m_lfVertFont;
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
long CLogarithmAxis::SetYAxisName(const CString & bstrName)
{
	char pszYAxisName[MAX_PATH];
	memset(pszYAxisName,0,MAX_PATH);
	CString_to_char(bstrName,pszYAxisName);
	m_strYAxisName = bstrName;

	return 0;
}

long CLogarithmAxis::GetYAxisName(CString *pbstrName)
{
	CString sYAxisName;
	sYAxisName = m_strYAxisName;
	*pbstrName = sYAxisName.AllocSysString();

	return 0;
}

long CLogarithmAxis::SetYAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName)
{
	LOGFONT   m_lfAxisNameFont;
	m_lfAxisNameFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,lfFaceName);
	m_lfVertTitleFont = m_lfAxisNameFont;

	return 0;
}
long CLogarithmAxis::GetYAxisNameFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName)
{
	LOGFONT m_lfYAxisNameFont;
	CString sFaceName;
	m_lfYAxisNameFont = m_lfVertTitleFont;
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

long CLogarithmAxis::SetYAxisNameFontColor(long nValue)
{
	COLORREF m_crYAxisNameFontColor;
	m_crYAxisNameFontColor = (COLORREF)nValue;
	m_crVertTitleColor = m_crYAxisNameFontColor;

	return 0;
}

long CLogarithmAxis::GetYAxisNameFontColor(long *nValue)
{
	COLORREF m_crYAxisNameFontColor;
	m_crYAxisNameFontColor = m_crVertTitleColor;
	*nValue = (long)m_crYAxisNameFontColor;

	return 0;
}
long CLogarithmAxis::SetYAxisScaleFontColor(long nValue)
{
	COLORREF m_crYAxisScaleFontColor;
	m_crYAxisScaleFontColor = (COLORREF)nValue;
	m_crVertColor = m_crYAxisScaleFontColor;

	return 0;
}

long CLogarithmAxis::GetYAxisScaleFontColor(long *nValue)
{
	COLORREF m_crYAxisScaleFontColor;
	m_crYAxisScaleFontColor = m_crVertColor;
	*nValue = (long)m_crYAxisScaleFontColor;

	return 0;
}

long CLogarithmAxis::SetYAxisGridLineStyle(long nValue)
{
	m_lAxisGridLineType = nValue;

	return 0;
}
long CLogarithmAxis::GetYAxisGridLineStyle(long *nValue)
{
	*nValue = m_lAxisGridLineType;

	return 0;
}

long CLogarithmAxis::SetYAxisGridLineColor(long nValue)
{
	COLORREF m_crYAxisGridLineColor;
	m_crYAxisGridLineColor = (COLORREF)nValue;
	m_crAxisGrid = m_crYAxisGridLineColor;

	return 0;
}

long CLogarithmAxis::GetYAxisGridLineColor(long *nValue)
{
	COLORREF m_crYAxisGridLineColor;
	m_crYAxisGridLineColor = m_crAxisGrid;
	*nValue = (long)m_crYAxisGridLineColor;

	return 0;
}

long CLogarithmAxis::SetYAxisTenthScaleColor(long nValue)
{
	COLORREF m_crYAxisTenthScaleColor;
	m_crYAxisTenthScaleColor = (COLORREF)nValue;
	SetYAxisTenthScaleColor(m_crYAxisTenthScaleColor);

	return 0;
}

long CLogarithmAxis::GetYAxisTenthScaleColor(long *nValue)
{
	COLORREF m_crYAxisTenthScaleColor;
	m_crYAxisTenthScaleColor = GetYAxisTenthScaleColor();
	*nValue = (long)m_crYAxisTenthScaleColor;

	return 0;
}

long CLogarithmAxis::SetYAxisAreaWidth(long nValue)
{
	m_iVertAreaWidth = nValue;

	return 0;
}

long CLogarithmAxis::GetYAxisAreaWidth(long *nValue)
{
	*nValue = m_iVertAreaWidth;

	return 0;
}

long CLogarithmAxis::SetYAxisUnitScaleLineLen(long nValue)
{
	m_iVertGapLineLen1 = nValue;

	return 0;
}

long CLogarithmAxis::GetYAxisUnitScaleLineLen(long *nValue)
{
	*nValue = m_iVertGapLineLen1;

	return 0;
}

long CLogarithmAxis::SetYAxisHalfScaleLineLen(long nValue)
{
	m_iVertGapLineLen2 = nValue;

	return 0;
}

long CLogarithmAxis::GetYAxisHalfScaleLineLen(long *nValue)
{
	*nValue = m_iVertGapLineLen2;
	return 0;
}

long CLogarithmAxis::SetYAxisTenthScaleLineLen(long nValue)
{
	m_iVertGapLineLen3 = nValue;

	return 0;
}

long CLogarithmAxis::GetYAxisTenthScaleLineLen(long *nValue)
{
	*nValue = m_iVertGapLineLen3;

	return 0;
}

long CLogarithmAxis::SetXUnitScaleColor(long nValue)
{
	COLORREF m_crXUnitScaleColor;
	m_crXUnitScaleColor = (COLORREF)nValue;
	m_crXUnitScaleColor = m_crXUnitScaleColor;

	return 0;
}

long CLogarithmAxis::GetXUnitScaleColor(long *nValue)
{
	*nValue = (long)m_crXUnitScaleColor;

	return 0;
}
long CLogarithmAxis::SetXUnitScaleShadowColor(long nValue)
{
	COLORREF m_crXUnitScaleShadowColor;
	m_crXUnitScaleShadowColor = (COLORREF)nValue;
	m_crXUnitScaleShadowColor = m_crXUnitScaleShadowColor;

	return 0;
}

long CLogarithmAxis::GetXUnitScaleShadowColor(long *nValue)
{
	*nValue = (long)m_crXUnitScaleShadowColor;

	return 0;
}

long CLogarithmAxis::SetXAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName)
{
	LOGFONT   m_lfXAxisScaleFont;
	m_lfXAxisScaleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,lfFaceName);
	m_lfHorzFont = m_lfXAxisScaleFont;

	return 0;
}
long CLogarithmAxis::GetXAxisScaleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName)
{
	LOGFONT m_lfXAxisScaleFont;
	CString sFaceName;
	m_lfXAxisScaleFont = m_lfHorzFont;
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

long CLogarithmAxis::SetXAxisName(const CString & bstrName)
{
	char pszName[MAX_PATH];
	memset(pszName,0,MAX_PATH);
	CString_to_char(bstrName,pszName);
	m_strXAxisName = pszName;

	return 0;
}

long CLogarithmAxis::GetXAxisName(CString *pbstrName)
{
	CString sXAxisName;
	sXAxisName = m_strXAxisName;
	*pbstrName = sXAxisName.AllocSysString();

	return 0;
}

long CLogarithmAxis::SetXAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName)
{
	LOGFONT   m_lfXAxisNameFont;
	m_lfXAxisNameFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,lfFaceName);
	m_lfHorzTitleFont = m_lfXAxisNameFont;

	return 0;
}

long CLogarithmAxis::GetXAxisNameFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName)
{
	LOGFONT m_lfXAxisNameFont;
	CString sFaceName;
	m_lfXAxisNameFont = m_lfHorzTitleFont;
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

long CLogarithmAxis::SetXAxisNameFontColor(long nValue)
{
	COLORREF m_crXAxisNameFontColor;
	m_crXAxisNameFontColor = (COLORREF)nValue;
	m_crHorzTitleColor = m_crXAxisNameFontColor;

	return 0;
}
long CLogarithmAxis::GetXAxisNameFontColor(long *nValue)
{
	COLORREF m_crXAxisNameFontColor;
	m_crXAxisNameFontColor = m_crHorzTitleColor;
	*nValue = (long)m_crXAxisNameFontColor;

	return 0;
}

long CLogarithmAxis::SetXAxisScaleFontColor(long nValue)
{
	COLORREF m_crXAxisScaleFontColor;
	m_crXAxisScaleFontColor = (COLORREF)nValue;
	m_crHorzColor = m_crXAxisScaleFontColor;

	return 0;
}

long CLogarithmAxis::GetXAxisScaleFontColor(long *nValue)
{
	COLORREF m_crXAxisScaleFontColor;
	m_crXAxisScaleFontColor = m_crHorzColor;
	*nValue = (long)m_crXAxisScaleFontColor;

	return 0;
}

long CLogarithmAxis::SetXAxisGridLineStyle(long nValue)
{
	m_lAxisGridLineType = nValue;

	return 0;
}

long CLogarithmAxis::GetXAxisGridLineStyle(long *nValue)
{
	*nValue = m_lAxisGridLineType;

	return 0;
}

long CLogarithmAxis::SetXAxisGridLineColor(long nValue)
{
	COLORREF m_crXAxisGrid;
	m_crXAxisGrid = (COLORREF)nValue;
	m_crAxisGrid = m_crXAxisGrid;;

	return 0;
}

long CLogarithmAxis::GetXAxisGridLineColor(long *nValue)
{
	COLORREF m_crXAxisGrid;
	m_crXAxisGrid = m_crAxisGrid;
	*nValue = (long)m_crXAxisGrid;

	return 0;
}

long CLogarithmAxis::SetXAxisTenthScaleColor(long nValue)
{
	COLORREF m_crXAxisTenthScaleColor;
	m_crXAxisTenthScaleColor = (COLORREF)nValue;
	SetXAxisTenthScaleColor(m_crXAxisTenthScaleColor);
	return 0;
}

long CLogarithmAxis::GetXAxisTenthScaleColor(long *nValue)
{
	COLORREF m_crXAxisTenthScaleColor;
	m_crXAxisTenthScaleColor = GetXAxisTenthScaleColr();
	*nValue = (long)m_crXAxisTenthScaleColor;

	return 0;
}

long CLogarithmAxis::SetXAxisAreaHeight(long nValue)
{
	m_iHorzAreaWidth = nValue;

	return 0;
}

long CLogarithmAxis::GetXAxisAreaHeight(long *nValue)
{
	*nValue = m_iHorzAreaWidth;

	return 0;
}

long CLogarithmAxis::SetXAxisUnitScaleLineLen(long nValue)
{
	m_iHorzGapLineLen1 = nValue;

	return 0;
}

long CLogarithmAxis::GetXAxisUnitScaleLineLen(long *nValue)
{
	*nValue = m_iHorzGapLineLen1;

	return 0;
}

long CLogarithmAxis::SetXAxisHalfScaleLineLen(long nValue)
{
	m_iHorzGapLineLen2 = nValue;

	return 0;
}

long CLogarithmAxis::GetXAxisHalfScaleLineLen(long *nValue)
{
	*nValue = m_iHorzGapLineLen2;

	return 0;
}

long CLogarithmAxis::SetXAxisTenthScaleLineLen(long nValue)
{
	m_iHorzGapLineLen3 = nValue;

	return 0;
}

long CLogarithmAxis::GetXAxisTenthScaleLineLen(long *nValue)
{
	*nValue = m_iHorzGapLineLen3;

	return 0;
}

long CLogarithmAxis::SetAxisCenterLineWidth(long nValue)
{
	m_lAxisCenterLineWidth = nValue;

	return 0;
}

long CLogarithmAxis::GetAxisCenterLineWidth(long *nValue)
{
	*nValue = m_lAxisCenterLineWidth;

	return 0;
}

long CLogarithmAxis::SetAxisCenterLineType(long nValue)
{
	m_lAxisCenterLineType = nValue;

	return 0;
}

long CLogarithmAxis::GetAxisCenterLineType(long *nValue)
{
	*nValue = m_lAxisCenterLineType;

	return 0;
}

long CLogarithmAxis::SetAxisCenterColor(long nValue)
{
	COLORREF m_crAxisCenterColor;
	m_crAxisCenterColor = (COLORREF)nValue;
	m_crAxisCenter = m_crAxisCenterColor;

	return 0;
}

long CLogarithmAxis::GetAxisCenterColor(long *nValue)
{
	COLORREF m_crAxisCenterColor;
	m_crAxisCenterColor = m_crAxisCenter;
	*nValue = (long)m_crAxisCenterColor;

	return 0;
}

long CLogarithmAxis::LogicPointToDevicePoint(double x,double y,long *ptx,long *pty)
{
	CPoint point(*ptx,*pty);
	LogicPointToDevicePoint(x,y, &point);

	return 0;
}

long CLogarithmAxis::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
{
	CPoint Point;
	Point = CPoint(ptx,pty);
	DevicePointToLogicPoint(Point,x,y, 0);

	return 0;
}

long CLogarithmAxis::SetMinMaxVal(double xMin,double yMin,double xMax,double yMax,long nReserved)
{
	SetAxisMinMaxVal(xMin,yMin,xMax,yMax);

	return 0;
}

long CLogarithmAxis::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
{
	GetAxisMinMaxVal(xMin,yMin,xMax,yMax);

	return 0;
}

long CLogarithmAxis::SetBoder(long left, long top, long right, long bottom)
{
	CRect rectW;
	rectW = CRect(left, top, right, bottom);
	SetBorder(rectW);

	return 0;
}

long CLogarithmAxis::GetBoder(long *left, long *top, long *right, long *bottom)
{
	CRect m_rectBoder;
	m_rectBoder = m_rcBorder;
	*left = m_rectBoder.left;
	*top = m_rectBoder.top;
	*right = m_rectBoder.right;
	*bottom = m_rectBoder.bottom;

	return 0;
}

long CLogarithmAxis::GetWorkArea(long *left, long *top, long *right, long *bottom)
{
	CRect rectWorkArea;
	rectWorkArea = m_rcWorkArea;
	*left = rectWorkArea.left;
	*top = rectWorkArea.top;
	*right = rectWorkArea.right;
	*bottom = rectWorkArea.bottom;

	return 0;
}

CRect CLogarithmAxis::GetWorkArea()
{
	return m_rcWorkArea;
}

long CLogarithmAxis::GetXAxisArea(long *left, long *top, long *right, long *bottom)
{
	CRect rectXAxisArea;
	rectXAxisArea = m_rcX_Axis;
	*left = rectXAxisArea.left;
	*top = rectXAxisArea.top;
	*right = rectXAxisArea.right;
	*bottom = rectXAxisArea.bottom;

	return 0;
}

long CLogarithmAxis::GetYAxisArea(long *left, long *top, long *right, long *bottom)
{
	CRect rectYAxisArea;
	rectYAxisArea = m_rcY_Axis;
	*left = rectYAxisArea.left;
	*top = rectYAxisArea.top;
	*right = rectYAxisArea.right;
	*bottom = rectYAxisArea.bottom;

	return 0;
}

long CLogarithmAxis::DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset)
{
	CPoint ptOffset;
	ptOffset = CPoint(xOffset,yOffset);
	DrawIt(pDC,fZoomRatio,ptOffset);

	return 0;
}

long CLogarithmAxis::ZoomIn1(float fRate)
{
	ZoomIn(fRate);

	return 0;
}

long CLogarithmAxis::ZoomIn2(double dMinX,double dMaxX,double dMinY,double dMaxY)
{
	ZoomIn(dMinX, dMaxX, dMinY, dMaxY);

	return 0;
}

long CLogarithmAxis::ZoomIn3(long left,long top,long right,long bottom)
{
	ZoomIn(left,top,right,bottom);

	return 0;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// 
// long CLogarithmAxis::GetBoder(long *left, long *top, long *right, long *bottom)
// {
// 	CRect rectBorder;
// 	rectBorder = cBorder;
// 	*left = rectBorder.left;
// 	*top = rectBorder.top;
// 	*right = rectBorder.right;
// 	*bottom = rectBorder.bottom;
// 	
// 	return 0;
// }
// 
// long CLogarithmAxis::GetWorkArea(long *left, long *top, long *right, long *bottom)
// {
// 	CRect rectWorkArea;
// 	rectWorkArea = cWorkArea;
// 	*left = rectWorkArea.left;
// 	*top = rectWorkArea.top;
// 	*right = rectWorkArea.right;
// 	*bottom = rectWorkArea.bottom;
// 	
// 	return 0;
// }
// 
// long CLogarithmAxis::LogicPointToDevicePoint(double x,double y,long *ptx,long *pty)
// {
// 	CPoint pPoint = CPoint(*ptx,*pty); 
// 	LogicPointToDevicePoint(x,y,&pPoint);
// 	
// 	return 0;
// }
// 
// long CLogarithmAxis::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
// {
// 	CPoint pPoint = CPoint(ptx,pty); 
// 	DevicePointToLogicPoint(pPoint,x,y);
// 	
// 	return 0;
// }
// 
// 
// long CLogarithmAxis::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
// {
// 	*xMin = iBeginPalace;
// 	*yMin = iDisplayMinVal;
// 	*xMax = iEndPalace;
// 	*yMax = iDisplayMaxVal;
// 	
// 	return 0;
// }
