// RulerLogAxis.cpp : implementation file
//

#include "stdafx.h"
#include "RulerLogAxis.h"
#include "../Api/GloblaDrawFunctions.h"
#include "../Api/StringApi.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define BOTTOMADD 2
/////////////////////////////////////////////////////////////////////////////
// CRulerLogAxis


CRulerLogAxis::CRulerLogAxis()
{
    m_nRulerHeight	=25;
    m_nRulerDirection		=RULER_DIRECTION_RIGHTDOWN;
    m_nCenterLogInDv = 0;

	m_iVertGapLineLen3=4*m_nZoomCoef;
	m_iHorzGapLineLen3=5*m_nZoomCoef;

	m_lXAxisMaxUnitCount = 10;
	m_lAxisDrawStyle = RULERLOGAXISDRAW_ALL;
    m_lVertLineStyle=PS_DOT;
    m_lHorzLineStyle=PS_DOT;
	m_crVert_WorkAreaLine_Color=RGB(0,0,0);
	m_crHorz_WorkAreaLine_Color=RGB(0,0,0);
	m_crAxisCenter = RGB(240,240,240);
	ContinueInit();
	
	m_crCircleScale=RGB(240,240,240);
	m_crBiaslineScale=RGB(240,240,240);
	

	m_strAxisTitle = "";
	m_crAxisTitleFont = RGB(0,0,0);
	m_lfAxisTitleFont = InitLogFont (14,0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
	m_strXAxisName = "";

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

	m_iBeginPalace=-0.20f;
	m_iEndPalace=3;
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

	m_nZoomCoef=1;
    SetRulerTypeHorz();
	InitIt();
}

CRulerLogAxis::~CRulerLogAxis()
{
	EndXAxisDef();
}

//坐标转换
//将逻辑坐标转化为实际坐标
void CRulerLogAxis::LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint, long nAxisIndex)
{
	if(fx<0 || fy<0)return ;

	float fXVal=log10(fx);
	float fYVal=log10(fy);

    fXVal = m_rectRuler.left+(fXVal-m_iBeginPalace)*m_fXAxisOneGap;
    fYVal = m_rectRuler.bottom-(fYVal-m_iBeginPalace)*m_fXAxisOneGap;

	pPoint->x = FloatValToInt(fXVal);
	pPoint->y = FloatValToInt(fYVal);;
}


void CRulerLogAxis::LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex)
{
    //double f=fVal*m_dOneXGapValue;
    //nVal->x=FloatValToInt(f);
}

void CRulerLogAxis::DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex)
{
    //*fVal= nVal / m_dOneXGapValue;
}

//从实际坐标获取实际坐标所代表的值
void CRulerLogAxis::DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex)
{
    double fXVal =m_iBeginPalace + ((double)point.x-(double)m_rectRuler.left)/m_fXAxisOneGap;
    double fYVal =((double)m_rectRuler.bottom-(double)point.y)/m_fXAxisOneGap + m_iBeginPalace;
	*x=pow(10,fXVal);
	*y=pow(10,fYVal);
}


//标尺的方向，0：标尺标注在下；	1：标尺标注在上
int CRulerLogAxis::GetRulerDirection()
{
    return m_nRulerDirection;
}

void CRulerLogAxis::SetRulerDirection(int iDirection)
{
    if (m_nRulerType == Ruler_Type_Horz)
    {
        m_nRulerDirection = iDirection;
    }
    else
    {
        m_nRulerDirection = iDirection;
    }
}

//高度
void CRulerLogAxis::SetRulerHeight(int iXAxisMinSawGapWidth)
{
    m_nRulerHeight = iXAxisMinSawGapWidth;
}

int CRulerLogAxis::GetRulerHeight()
{
    return m_nRulerHeight;
}

void CRulerLogAxis::InitHorzRulerAttr()
{

}

void CRulerLogAxis::GetAxisDrawArea(CRect &rcArea)
{

}

void CRulerLogAxis::GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
	GetMinMaxVal(&dXMin, &dYMin, &dXMax, &dYMax, 0);

}

void CRulerLogAxis::SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax)
{
	SetMinMaxVal(dXMin, dYMin, dXMax, dYMax, 0);
}


//lijunqing 2024-6-20
void CRulerLogAxis::LogicPointToDevicePoint(double *pfBuff, CPoint *pPointBuf, long nDatasCount, long nAxisIndex)
{
	int k=0;
	double dVal = 0;

	if(m_nRulerType == Ruler_Type_Horz)
	{
		for (k=0; k<nDatasCount; k++)
		{
			if (pfBuff[k] > 0)
			{
				dVal = log10(pfBuff[k]);
			}
			else
			{
				dVal = m_iBeginPalace;
			}
			
			dVal = m_rectRuler.left+(dVal-m_iBeginPalace)*m_fXAxisOneGap;
			pPointBuf[k].x = FloatValToInt(dVal);
		}

	}
	else
	{
		for (k=0; k<nDatasCount; k++)
		{
			if (pfBuff[k] > 0)
			{
				dVal = log10(pfBuff[k]);
			}
			else
			{
				dVal = m_iBeginPalace;
			}

			dVal = m_rectRuler.bottom-(dVal-m_iBeginPalace)*m_fXAxisOneGap;
			pPointBuf[k].x = FloatValToInt(dVal);
		}
	}
}


void CRulerLogAxis::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{
	SetXAxisName(strXAxisName);
	SetAxisTitle(strAxisTitle);
}

#ifdef USE_AXIS_CONFIG//zhouhj 20211026 增加用于设置坐标轴
void CRulerLogAxis::SetAxisConfig(CDataGroup *pAxisConfig)
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
void CRulerLogAxis::SetAxisConfig(CDvmData *pAxisData)
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
void CRulerLogAxis::GetAxisConfig(CDataGroup *pAxisConfig)
{
}
#endif

void CRulerLogAxis::ContinueInit()
{
	m_cBkGroundBrush=InitLogBrush(BS_SOLID,1,m_crBkGroundColor);
	m_penVert_WorkAreaLine=InitLogPen(m_lVertLineStyle,1,m_crVert_WorkAreaLine_Color);
	m_penVert_WorkAreaShortLine=InitLogPen(PS_SOLID,1,m_crYTenthScaleColor);//crVert_WorkAreaLine_Color);
	m_penHorz_WorkAreaLine=InitLogPen(m_lHorzLineStyle,1,m_crHorz_WorkAreaLine_Color);
	m_penHorz_WorkAreaShortLine=InitLogPen(PS_SOLID,1,m_crXTenthScaleColor);//crHorz_WorkAreaLine_Color);
	m_penCircleScale		=InitLogPen(m_lCircleLineType,1,m_crCircleScale);
	m_penBiaslineScale	=InitLogPen(m_lBiasLineType,1,m_crBiaslineScale);
}

void CRulerLogAxis::InitIt()
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

/////////////////////////////
/////////////////////////////

	m_iBeginPalace=-0.20f;
	m_iEndPalace=3;
	m_iOldBeginPalace=m_iBeginPalace;
	m_iOldEndPalace=m_iEndPalace;

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

    m_rectRuler.left = 0;
    m_rectRuler.right = 600;
    m_rectRuler.top = 0;
    m_rectRuler.bottom = 600;
}

const CRulerLogAxis & CRulerLogAxis::operator =(CRulerLogAxis &odTemp)
{
	if (&odTemp==this) 
		return *this;
		
	m_iBeginPalace=odTemp.m_iBeginPalace;
	m_iEndPalace=odTemp.m_iEndPalace;
	m_iDataMinVal=odTemp.m_iDataMinVal;
	m_iDataMaxVal=odTemp.m_iDataMaxVal;
	m_iDirection=odTemp.m_iDirection;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CRulerLogAxis message handlers
float CRulerLogAxis::GetBeginVal(float lNowVal,float lGapVal)
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
void CRulerLogAxis::ResetYAxisDef()
{
    EndXAxisDef();
    float fBeginVal=m_iBeginPalace;
    float fEndVal=m_iEndPalace;
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

    float iBeginVal=GetBeginVal(m_iBeginPalace, iGapVal);
    GetOneYAxisHeight(iGapVal,1);

    int i=0;

    for (i=0;i<=iGapNumTemp;i++)
    {
        ResetOneYAxisDef(iBeginVal+i*iGapVal);
    }

    m_fXCarryOneGap=iGapVal;
}

void CRulerLogAxis::GetOneYAxisHeight(float iGap,BYTE bKind)
{
    int iHeight=m_rectRuler.Height();
    float iVal=m_iEndPalace-m_iBeginPalace;

    m_fXAxisOneGap=iGap*(float)iHeight/iVal;
}


void CRulerLogAxis::ResetOneYAxisDef(float dAxisScaleVal)
{
    int iHeight=m_rectRuler.Height();
    float iVal=m_iEndPalace-m_iBeginPalace;
    float f = m_rectRuler.bottom-(dAxisScaleVal-m_iBeginPalace)*((float)iHeight / iVal );
    int y=FloatValToInt(f);
    CAxisScaleData *odData=new CAxisScaleData();
    odData->FillIt(dAxisScaleVal,CPoint(m_rectRuler.right,y));
    m_listRulerScale.AddTail(odData);
}

void CRulerLogAxis::DrawYAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio,CPoint ptOffset)
{
    return;
	CPoint pt;
    pt.x = m_rectRuler.left;
	pt.y = odData->m_ptAxisScale.y;
	pt.Offset(ptOffset);
	cDC->MoveTo(pt);

    pt.x = m_rectRuler.right;
	pt.y = odData->m_ptAxisScale.y;
	pt.Offset(ptOffset);
	cDC->LineTo(pt);
}

void CRulerLogAxis::DrawYAxisText(CDC *cDC,CAxisScaleData *odData,float fZoomRatio,CPoint ptOffset)
{
	char cStr[128];
	float fText=odData->m_dAxisScaleVal;
	fText=pow(10,fText);
	sprintf(cStr,"%f",fText);
	_ChopFloatString(cStr);
    long lHeight=(long)(m_lfVertFont.lfHeight * fZoomRatio);
    lHeight = abs(lHeight);
	CRect cR;
    cR.left=m_rectRuler.left;
	cR.top=odData->m_ptAxisScale.y-lHeight;
    cR.right=m_rectRuler.right-m_iVertGapLineLen1 * fZoomRatio;
	cR.bottom=odData->m_ptAxisScale.y+lHeight;
	cR.OffsetRect(ptOffset);
	CmDrawTextRect(cDC,CString(cStr),m_crVertColor,&cR,RGB(0,0,0),m_lfVertFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}
void CRulerLogAxis::DrawYAxisName(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{
	CRect cR;
    cR.left=m_rectRuler.left+2;
    cR.top=m_rectRuler.top;
    cR.right=m_rectRuler.right-3;
    cR.bottom=m_rectRuler.top+15*fZoomRatio;
	cR.OffsetRect(ptOffset);
    CmDrawTextRect(cDC,m_strXAxisName,m_crVertTitleColor,
				   &cR,RGB(0,0,0),m_lfVertTitleFont,
				   TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}

void CRulerLogAxis::DrawYAxis(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{
    int iNum=m_listRulerScale.GetCount();
	if(iNum<=0)return;
	CPen cP;
	long lGap=(long)(abs(m_lfVertFont.lfHeight)*1.5 * fZoomRatio);
	cP.CreatePenIndirect(&m_penVert_WorkAreaLine);
	CPen *cOldP=cDC->SelectObject(&cP);
	int i=0;
	for (i=0;i<iNum;i++)
	{
        CAxisScaleData *odData=(CAxisScaleData*)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i));

        if( m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_SCALETEXT)
		{
                if(odData->m_ptAxisScale.y>=m_rectRuler.top)
					DrawYAxisText(cDC,odData,fZoomRatio,ptOffset);////标注
		}

        if( m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_LINE)
		{
                if ((odData->m_ptAxisScale.y>m_rectRuler.top)&&(odData->m_ptAxisScale.y<m_rectRuler.bottom))
				{
					DrawYAxisLine(cDC,odData,fZoomRatio,ptOffset);//网格
				}
		}
	}

	cDC->SelectObject(cOldP);
	cP.DeleteObject();

    if( m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_SAWTOOTH1)
		DrawYSawtooth(cDC,0,fZoomRatio,ptOffset);

    if( m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_SAWTOOTH2)
		DrawYSawtooth(cDC,1,fZoomRatio,ptOffset);
}

///////////////靠工作区内的小锯齿
void CRulerLogAxis::DrawOneYSawtoothSmall(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
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
        float f = m_rectRuler.bottom-(fVal-m_iBeginPalace)*m_fXAxisOneGap;
		int y=FloatValToInt(f);

		CPoint cPt(cBegin.x,y);
        if((cPt.y<m_rectRuler.top)||(cPt.y>m_rectRuler.bottom))
			continue;
		cPt.Offset(ptOffset);
		cDC->MoveTo(cPt.x-1,cPt.y);
		cDC->LineTo(cPt.x-(long)(fZoomRatio*m_iVertGapLineLen3),cPt.y);
	}

	cDC->SelectObject(cOldP);
	cP.DeleteObject();
}

void CRulerLogAxis::ResetOneYSawtoothSmall(CPoint cBegin,CPoint cEnd,float fCarryVal)
{
	int iDeltaY=0;
	float fVal=0;
	int i = 0;
	CAxisScaleData *p = NULL;

	for (i=2;i<10;i++)
	{
		fVal=fCarryVal * i ;
		fVal=log10(fVal);
		float f = m_rectRuler.bottom-(fVal-m_iBeginPalace)*m_fXAxisOneGap;
		int y=FloatValToInt(f);

		CPoint cPt(cBegin.x,y);
		if((cPt.y<m_rectRuler.top)||(cPt.y>m_rectRuler.bottom))
			continue;

		p = new CAxisScaleData();
		p->m_dAxisScaleVal = fVal;
		p->m_ptAxisScale = cPt;
		m_listRulerSmallScale.AddTail(p);
	}
}

///////////////大刻度
void CRulerLogAxis::DrawOneYSawtoothBig(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{
	int iLen=(long)(fZoomRatio*m_iVertGapLineLen1);
	CPoint cPt(cBegin.x,cBegin.y);
    if((cPt.y>=(long)(fZoomRatio*m_rectRuler.top))&&(cPt.y<=(long)(fZoomRatio*m_rectRuler.bottom)))
	{
		cPt.Offset(ptOffset);
		DrawShadowHorzLine(cDC,cPt.x,cPt.y,iLen,m_crYUnitScaleColor,m_crYUnitScaleShadowColor);
	}
}

void CRulerLogAxis::DrawYSawtooth(CDC *cDC,BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;
	float fCarryVal=0;
	int i=0;

    for (i=0;i<m_listRulerScale.GetCount();i++)
	{
        CAxisScaleData *odData=(CAxisScaleData *)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i));
		fCarryVal=pow(10,odData->m_dAxisScaleVal);

        if (i==0)
		{
            cBegin=CPoint(odData->m_ptAxisScale.x,odData->m_ptAxisScale.y+m_fXAxisOneGap);
			cEnd=odData->m_ptAxisScale;			
		}
		else
		{
            CAxisScaleData *odNewData=(CAxisScaleData *)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i-1));
			cBegin=odNewData->m_ptAxisScale;
			cEnd=odData->m_ptAxisScale;
		}

		if (bKind==0)
			DrawOneYSawtoothSmall(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else
			DrawOneYSawtoothBig(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		
	}

    if(m_listRulerScale.GetCount()>=2)
	{
        CAxisScaleData *odData=(CAxisScaleData *)m_listRulerScale.GetTail();
        cEnd=CPoint(odData->m_ptAxisScale.x,odData->m_ptAxisScale.y-m_fXAxisOneGap);
		cBegin=odData->m_ptAxisScale;
		fCarryVal=pow(10,odData->m_dAxisScaleVal);

        if (bKind==0)
			DrawOneYSawtoothSmall(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else 
			DrawOneYSawtoothBig(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
	}
}

void CRulerLogAxis::ResetYSawtoothSmall()
{
	m_listRulerSmallScale.DeleteAll();

	CPoint cBegin,cEnd;
	float fCarryVal=0;
	int i=0;

	for (i=0;i<m_listRulerScale.GetCount();i++)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i));
		fCarryVal=pow(10,odData->m_dAxisScaleVal);

		cBegin=CPoint(odData->m_ptAxisScale.x,odData->m_ptAxisScale.y+m_fXAxisOneGap);
		cEnd=odData->m_ptAxisScale;			
		ResetOneYSawtoothSmall(cBegin,cEnd,fCarryVal);
	}

	if(m_listRulerScale.GetCount()>=2)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_listRulerScale.GetTail();
		cEnd=CPoint(odData->m_ptAxisScale.x,odData->m_ptAxisScale.y-m_fXAxisOneGap);
		cBegin=odData->m_ptAxisScale;
		fCarryVal=pow(10,odData->m_dAxisScaleVal);
		ResetOneYSawtoothSmall(cBegin,cEnd,fCarryVal);
	}
}
//#######################################################################
//******************************关于X轴的绘制****************************
//#######################################################################

void CRulerLogAxis::InitXAxisDef(){m_listRulerScale.DeleteAll();}
void CRulerLogAxis::EndXAxisDef(){m_listRulerScale.DeleteAll();}


float CRulerLogAxis::GetXBeginVal(float lNowVal,float lGapVal)
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

void CRulerLogAxis::ResetXAxisDef()
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
void CRulerLogAxis::GetOneXAxisWidth(float iGap,BYTE bKind)
{
    int iWidth=m_rectRuler.Width();
	float iVal=(m_iEndPalace-m_iBeginPalace);
    m_fXAxisOneGap=iGap*(float)iWidth/iVal;
}

void CRulerLogAxis::ResetOneXAxisDef(float dAxisScaleVal,BYTE bKind)
{
    int iWidth=m_rectRuler.Width();
	float iVal=(m_iEndPalace-m_iBeginPalace);//FloatValToInt
    float f=m_rectRuler.left+(dAxisScaleVal-m_iBeginPalace)*(float)iWidth/iVal;
	int x=FloatValToInt(f);
	CAxisScaleData *odData=new CAxisScaleData();
	int iIntegeralBeginPalace=0;//GetIntegeralBeginPalace();

	if(bKind==0) 
	{
		float f=(float)(dAxisScaleVal-iIntegeralBeginPalace);
        odData->FillIt(f,CPoint(x,m_rectRuler.top+BOTTOMADD));
	}
	else 
	{
		float f=(float)(dAxisScaleVal-iIntegeralBeginPalace);
        odData->FillIt(f, CPoint(x,m_rectRuler.top+BOTTOMADD));
	}

	m_listRulerScale.AddTail(odData);
}


void CRulerLogAxis::DrawXAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio,CPoint ptOffset)
{
    return;
	CPoint pt;
	pt.x = odData->m_ptAxisScale.x;
    pt.y = (long)(fZoomRatio*m_rectRuler.top+m_iShadow);
	pt.Offset(ptOffset);
	cDC->MoveTo(pt);

	pt.x = odData->m_ptAxisScale.x;
    pt.y = (long)(fZoomRatio*m_rectRuler.bottom+BOTTOMADD);
	pt.Offset(ptOffset);
	cDC->LineTo(pt);
}

CRect  CRulerLogAxis::DrawXAxisText(CDC *cDC,CAxisScaleData *odData,BOOL bAddUint,BOOL bReallyDraw,float fZoomRatio,CPoint ptOffset)
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
void CRulerLogAxis::DrawXAxisName(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	int iLen=m_strXAxisName.GetLength();
	CFont CF;
	CF.CreateFontIndirect(&m_lfHorzTitleFont);
	CFont *c=pDC->SelectObject(&CF);
	TEXTMETRIC textMetric;
	pDC->GetTextMetrics(&textMetric);
	pDC->SelectObject(c);
	iLen=textMetric.tmAveCharWidth *(iLen+1);

	CRect cR;
    cR.left=m_rectRuler.right-iLen;
    cR.top=m_rectRuler.bottom-(long)(fZoomRatio * 10);
    cR.right= m_rectRuler.right;
    cR.bottom=m_rectRuler.bottom;
	cR.OffsetRect(ptOffset);
	CmDrawTextRect(pDC,m_strXAxisName,m_crHorzTitleColor,&cR,RGB(0,0,0),
				   m_lfHorzTitleFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}

void CRulerLogAxis::DrawXAxis(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{
	int iNum=m_listRulerScale.GetCount();
	if(iNum<=0)return;
	CPen cP;
	cP.CreatePenIndirect(&m_penHorz_WorkAreaLine);
	CPen *cOldB=cDC->SelectObject(&cP);
	float iIntgerEndPalace=m_iEndPalace;//GetIntegeralEndPalace();
	if(iIntgerEndPalace<0)iIntgerEndPalace=0;

	int i=0;
	for (i=0;i<iNum;i++)
	{
		CAxisScaleData *odData=(CAxisScaleData*)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i));
		if(m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_LINE)
		{
                if ((odData->m_ptAxisScale.x>m_rectRuler.left)&&(odData->m_ptAxisScale.x<m_rectRuler.right))
				{
					DrawXAxisLine(cDC,odData,fZoomRatio,ptOffset);
				}
		}
		
	}

	if(m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_SCALETEXT)
	{
		int iStep=iNum;
		int i=0;
	for (i=0;i<iNum;i++)
		{
			CAxisScaleData *odData=(CAxisScaleData*)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i));
		}
		BOOL bDrawUint=FALSE;
		for (i=0;i<iStep-1;i++)
		{
			CAxisScaleData *odData=(CAxisScaleData*)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i));
            if(odData->m_ptAxisScale.x<m_rectRuler.left)
				continue;
			DrawXAxisText(cDC,odData,bDrawUint,TRUE,fZoomRatio,ptOffset);
		}
		CAxisScaleData *odData=(CAxisScaleData*)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i));
        if(odData->m_ptAxisScale.x > m_rectRuler.left)
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
	if(m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_SAWTOOTH1)
			DrawXSawtooth(cDC,0,fZoomRatio,ptOffset);

	if(m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_SAWTOOTH2)
			DrawXSawtooth(cDC,1,fZoomRatio,ptOffset);
		
	//DrawXAxisName(cDC,fZoomRatio,ptOffset);
}

void CRulerLogAxis::DrawOneXSawtoothSmall(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{                                     
	CPen cP;
	cP.CreatePenIndirect(&m_penHorz_WorkAreaShortLine);
	CPen *pOldPen=cDC->SelectObject(&cP);
	float fVal=0;
	int i=2;

	for (i=2;i<10;i++)
	{
		fVal=fCarryVal * i ;
		fVal=log10(fVal);
        float f=m_rectRuler.left+(fVal-m_iBeginPalace)*m_fXAxisOneGap;
		int x=FloatValToInt(f);

		CPoint cPt(x,cBegin.y);

        if((cPt.x<m_rectRuler.left)||(cPt.x>m_rectRuler.right)) 
			continue;

		cPt.Offset(ptOffset);
		cDC->MoveTo(cPt.x,cPt.y+(long)(fZoomRatio*1));
		cDC->LineTo(cPt.x,cPt.y+(long)(fZoomRatio*m_iHorzGapLineLen3));
	}

	cDC->SelectObject(pOldPen);
	cP.DeleteObject();
}

void CRulerLogAxis::ResetOneXSawtoothSmall(CPoint cBegin,CPoint cEnd,float fCarryVal)
{                                     
	float fVal=0;
	int i=2;
	CAxisScaleData *p = NULL;

	for (i=2;i<10;i++)
	{
		fVal=fCarryVal * i ;
		fVal=log10(fVal);
		float f=m_rectRuler.left+(fVal-m_iBeginPalace)*m_fXAxisOneGap;
		int x=FloatValToInt(f);

		CPoint cPt(x,cBegin.y);

		if((cPt.x<m_rectRuler.left)||(cPt.x>m_rectRuler.right)) 
			continue;

		p = new CAxisScaleData();
		p->m_dAxisScaleVal = fVal;
		p->m_ptAxisScale = cPt;
		m_listRulerSmallScale.AddTail(p);
	}
}

void CRulerLogAxis::DrawOneXSawtoothBig(CDC *cDC, CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{
	int iLen[2]={(long)(fZoomRatio*m_iHorzGapLineLen1),(long)(fZoomRatio*m_iHorzGapLineLen2)};
	int i=0;
	for (i=0;i<1;i++)
	{
        int iGapVal=FloatValToInt((float)((float)m_fXAxisOneGap/2.0*i));
		CPoint cPt(cBegin.x+iGapVal,cBegin.y);
        if((cPt.x<m_rectRuler.left)||(cPt.x>m_rectRuler.right)) continue;
		cPt.Offset(ptOffset);
		DrawShadowVertLine(cDC,cPt.x,cPt.y,iLen[i],m_crXUnitScaleColor,m_crXUnitScaleShadowColor);
	}
}

void CRulerLogAxis::DrawXSawtooth(CDC *cDC,BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;
	float fCarryVal=0;
	int i=0;

	for (i=0;i<m_listRulerScale.GetCount();i++)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i));
		fCarryVal=pow(10,odData->m_dAxisScaleVal);

        if (i==0)
		{
            cBegin=CPoint(odData->m_ptAxisScale.x-m_fXAxisOneGap,odData->m_ptAxisScale.y);
			cEnd=odData->m_ptAxisScale;
		}
		else 
		{
				CAxisScaleData *odNewData=(CAxisScaleData *)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i-1));
				cBegin=odNewData->m_ptAxisScale;
				cEnd=odData->m_ptAxisScale;
		}	

		if (bKind==0)
		{
			DrawOneXSawtoothSmall(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		}
		else 
		{
			DrawOneXSawtoothBig(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		}
	}

	if(m_listRulerScale.GetCount()>=2)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_listRulerScale.GetTail();
        cEnd=CPoint(odData->m_ptAxisScale.x+m_fXAxisOneGap,odData->m_ptAxisScale.y);
		cBegin=odData->m_ptAxisScale;
		if (bKind==0)DrawOneXSawtoothSmall(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else DrawOneXSawtoothBig(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
	}
}

void CRulerLogAxis::ResetXSawtoothSmall()
{
/*	CPoint cBegin,cEnd;
	float fCarryVal=0;
	int i=0;

	for (i=0;i<m_listRulerScale.GetCount();i++)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i));
		fCarryVal=pow(10,odData->m_dAxisScaleVal);

		if (i==0)
		{
			cBegin=CPoint(odData->m_ptAxisScale.x-m_fXAxisOneGap,odData->m_ptAxisScale.y);
			cEnd=odData->m_ptAxisScale;
		}
		else 
		{
			CAxisScaleData *odNewData=(CAxisScaleData *)m_listRulerScale.GetAt(m_listRulerScale.FindIndex(i-1));
			cBegin=odNewData->m_ptAxisScale;
			cEnd=odData->m_ptAxisScale;
		}	

		if (bKind==0)
		{
			DrawOneXSawtoothSmall(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		}
		else 
		{
			DrawOneXSawtoothBig(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		}
	}

	if(m_listRulerScale.GetCount()>=2)
	{
		CAxisScaleData *odData=(CAxisScaleData *)m_listRulerScale.GetTail();
		cEnd=CPoint(odData->m_ptAxisScale.x+m_fXAxisOneGap,odData->m_ptAxisScale.y);
		cBegin=odData->m_ptAxisScale;
		if (bKind==0)DrawOneXSawtoothSmall(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else DrawOneXSawtoothBig(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
	}
    */
}
void CRulerLogAxis::DrawIt(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{

	if(m_lAxisDrawStyle &RULERLOGAXISDRAW_WORKAREA)
		DrawArea(cDC,fZoomRatio,ptOffset);

    if (m_nRulerType == Ruler_Type_Horz)
    {
        DrawXAxis(cDC,fZoomRatio,ptOffset);

        if(m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_NAME)
            DrawXAxisName(cDC,fZoomRatio,ptOffset);
     }
     else
    {
        DrawYAxis(cDC,fZoomRatio,ptOffset);

        if(m_lAxisDrawStyle & RULERLOGAXISDRAW_XAXIS_NAME)
            DrawYAxisName(cDC,fZoomRatio,ptOffset);
    }

	if(m_lAxisDrawStyle & RULERLOGAXISDRAW_AXISTITLE)
		DrawAxisTitle(cDC,fZoomRatio,ptOffset);

	if(m_lAxisDrawStyle & RULERLOGAXISDRAW_AXISBODER)
		DrawFrame(cDC,fZoomRatio,ptOffset);
}

void CRulerLogAxis::DrawAxisTitle(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
}

void CRulerLogAxis::DrawFrame(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
/*
    CRect rect = m_rectRuler;
	rect.OffsetRect(ptOffset);
	Draw3dRectBorder(pDC,&rect,m_iFrameShadow,m_crFrameLeftTopColor,m_crFrameRightBottomColor);
*/
}

void CRulerLogAxis::ModifyWorkArea(CRect* pRect,BOOL bInit,float fZoomRatio,CPoint ptOffset)
{
    m_rectRuler=*pRect;

    if(m_nRulerType == Ruler_Type_Horz)
    {
        m_rectRuler.bottom = m_rectRuler.top+m_nRulerHeight;
    }
    else
    {
        m_rectRuler.right = m_rectRuler.left + m_nRulerHeight;
    }

}

BOOL CRulerLogAxis::MakeWorkAreaLegal(CRect &cNewRect)
{
	if(cNewRect.left<0)cNewRect.left=0;
	if(cNewRect.right<0)cNewRect.right=0;
	if(cNewRect.top<0)cNewRect.top=0;
	if(cNewRect.bottom<0)cNewRect.bottom=0;
	if (cNewRect.Height()<30)cNewRect.bottom=cNewRect.top+30;
	if (cNewRect.Width()<50)cNewRect.right=cNewRect.left+30;
	return TRUE;
}

void CRulerLogAxis::DrawWorkAreaBorder(CDC *pDC)//,cR,iGap,crLeftTop,crRightBottom);
{
    /*
	CRect cR=GetDrawWorkAreaRect();
	Draw3dRectBorder(pDC,&cR,m_iShadow,m_crBkLeftTopColor,m_crBkRightBottomColor);
*/
}

void CRulerLogAxis::DrawArea(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
    CRect cR=GetDrawWorkAreaRect();
	cR.OffsetRect(ptOffset);
	Draw3dRectByMe(pDC,cR,(long)(fZoomRatio*m_iShadow),m_crBkLeftTopColor,
				   m_crBkRightBottomColor,m_crBkGroundColor);
}

void CRulerLogAxis::DrawAxisBack(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	//绘制背景
	CBrush brush;
	brush.CreateSolidBrush(m_crAxisBackColor);
    pDC->FillRect(m_rectRuler,&brush);
	brush.DeleteObject();
	
}

CRect CRulerLogAxis::GetDrawWorkAreaRect()
{
    CRect cR=m_rectRuler;
	cR.bottom+=3;cR.right+=2;
	return cR;
}

void CRulerLogAxis::SetAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY)
{
	//对数坐标系
	m_iOldBeginPalace=m_iBeginPalace;
	m_iOldEndPalace=m_iEndPalace;
	m_iBeginPalace=dMinX;	
	m_iEndPalace=dMaxX;		
	
    ModifyWorkArea(&m_rectRuler,1);
	ResetAxis();
}

long CRulerLogAxis::GetAxisMinMaxVal(double *dMinX,double *dMinY,double *dMaxX,double *dMaxY)
{
	*dMinX=m_iBeginPalace;
	*dMaxX=m_iEndPalace;
	
	return 0;
}

void CRulerLogAxis::SetBorder(const CRect &rcBorder)
{
    m_rectRuler=rcBorder;

    if(m_nRulerType == Ruler_Type_Horz)
    {
        m_rectRuler.bottom = m_rectRuler.top+m_nRulerHeight;
    }
    else
    {
        m_rectRuler.right = m_rectRuler.left + m_nRulerHeight;
    }

	ResetAxis();
	InitAxisAttr();
}

void CRulerLogAxis::ResetAxis()
{
	//i-t
// 	m_iBeginPalace=0;
// 	m_iEndPalace=10;
// 	m_iBeginPalace=0;
// 	m_iDisplayMaxVal= 10;
	m_iOldBeginPalace=m_iBeginPalace;
	m_iOldEndPalace=m_iEndPalace;

    if (m_nRulerType == Ruler_Type_Horz)
    {
        ResetXAxisDef();
    }
    else
    {
		ResetYAxisDef();
    }
}

void CRulerLogAxis::InitAxisAttr()
{
//     CRect rectWork=m_rectRuler;
// 	float fYValue=0,fXValue=0;
// 	float fYMaxValue=0,fYMinValue=0,fXMaxValue=0,fXMinValue=0;
// 	CPoint pointCenter=CPoint(0,0);
// 	int iHeight=rectWork.Height();
// 	float fValYOneGap=iHeight/(fYMaxValue-fYMinValue);///Y轴实际坐标与实际值的比率
// 	///////////////////////////////////////////////
// 	fXMaxValue=m_iEndPalace;
// 	fXMinValue=m_iBeginPalace;
// 	int iWidth=rectWork.Width();
// 	float fValXOneGap=iWidth/(fXMaxValue-fXMinValue);//X轴实际坐标与实际值的比率
// 	/////坐标原点在屏幕上的位置
// 	float f=rectWork.left + (0-fXMinValue)*fValXOneGap;
// 	pointCenter.x=FloatValToInt(f);
// 	f=rectWork.bottom -(0-fYMinValue)*fValYOneGap;
// 	pointCenter.y=FloatValToInt(f);
// 
//     m_fOneXGapValue=fValXOneGap;
// 	m_ptCenterLogInDv=pointCenter;

}
void CRulerLogAxis::ZoomIn(float fZoomIn)
{
	double fMinX=0,fMinY=0,fMaxX=0,fMaxY=0;
	fMinX = m_iBeginPalace / fZoomIn;
	fMaxX = m_iEndPalace /fZoomIn;
	
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
	fCoefX=fabs(fCoefX);

    if(fCoefX>m_dMaxZoomMultiple || fCoefY>m_dMaxZoomMultiple)
		return;
	
	SetAxisMinMaxVal(fMinX,fMinY,fMaxX,fMaxY);
}

void CRulerLogAxis::ZoomIn(double dMinX,double dMaxX,double dMinY,double dMaxY)
{
	//重新设置当前测试项目的坐标系
	SetAxisMinMaxVal(dMinX,dMinY,dMaxX,dMaxY);	
}

void CRulerLogAxis::ZoomIn(long lLeft,long lTop,long lRight,long lBottom)
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

void CRulerLogAxis::ZoomOut(float fZoomOut)
{
	double fMinX=0,fMinY=0,fMaxX=0,fMaxY=0;
	fMinX = m_iBeginPalace * fZoomOut;
	fMaxX = m_iEndPalace * fZoomOut;
	
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
    double fCoefX=0;
	
	fCoefX=(fMaxX-fMinX) / (m_iOldEndPalace - m_iOldBeginPalace)  ;
	fCoefX=fabs(fCoefX);

    if(fCoefX>m_dMaxZoomMultiple)
		return;

	SetAxisMinMaxVal(fMinX,fMinY,fMaxX,fMaxY);	
}

void CRulerLogAxis::Move(float fXOffset,float fYOffset)
{
	m_iEndPalace     -= fXOffset * m_fXCarryOneGap;
	m_iBeginPalace   -= fXOffset * m_fXCarryOneGap;
	
	ResetAxis();
	InitAxisAttr();
}

////////////////////////////////////////////////////////////////

long CRulerLogAxis::GetXAxisMinSawGapWidth(long *nValue)
{
	*nValue = m_fOneXGapValue;
	
	return 0;
}

long CRulerLogAxis::SetXAxisMinSawGapWidth(long nValue)
{
	m_fOneXGapValue = nValue;

	return 0;
}

long CRulerLogAxis::SetXAxisMaxUnitCount(long nValue)
{
	m_lXAxisMaxUnitCount = nValue;

	return 0;
}

long CRulerLogAxis::GetXAxisMaxUnitCount(long *nValue)
{
	*nValue = m_lXAxisMaxUnitCount;

	return 0;
}

//坐标系统的绘制类型,2005.08.12添加
long CRulerLogAxis::SetAxisDrawStyle(long nValue)
{
	
	m_lAxisDrawStyle = nValue;
	
	return 0;
}

long CRulerLogAxis::GetAxisDrawStyle(long *nValue)
{
	
	*nValue = m_lAxisDrawStyle;
	
    return 0;
}
long CRulerLogAxis::SetAxisDrawStyleBit(long nValue)
{

	m_lAxisDrawStyle |= nValue;
	
	return 0;
}
long CRulerLogAxis::ClearAxisDrawStyleBit(long nValue)
{

	m_lAxisDrawStyle &= (~nValue);
	
	return 0;
}


long CRulerLogAxis::SetXAxisTextDrawStyle(long nValue)
{
	m_dwDrawXAxisTextType = nValue;

	return 0;
}

long CRulerLogAxis::GetXAxisTextDrawStyle(long *nValue)
{
	*nValue = m_dwDrawXAxisTextType;

	return 0;
}

long CRulerLogAxis::SetAxisTitle(const CString & bstrValue)
{
/*
	char pszValue[MAX_PATH];
	memset(pszValue,0,MAX_PATH);
	CString_to_char(bstrValue,pszValue);*/

	m_strAxisTitle = bstrValue;

	return 0;
}
long CRulerLogAxis::GetAxisTitle(CString *pbstrValue)
{
	CString sAxisTitle;
	sAxisTitle = m_strAxisTitle;
	*pbstrValue = sAxisTitle.AllocSysString();
	
	return 0;
}

long CRulerLogAxis::SetAxisTitleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName)
{
	LOGFONT   lfAxisTitleFont;
	lfAxisTitleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet
		,(BYTE)lfOutPrecision,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,lfFaceName);
	m_lfAxisTitleFont = lfAxisTitleFont;

	return 0;
}

long CRulerLogAxis::GetAxisTitleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName)
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
long CRulerLogAxis::SetAxisTitleFontColor(long nValue)
{
	COLORREF m_crTitleColor;
	m_crTitleColor = (COLORREF)nValue;
	m_crAxisTitleFont = m_crTitleColor;

	return 0;
}

long CRulerLogAxis::GetAxisTitleFontColor(long *nValue)
{
	COLORREF m_crAxisTitleFontColor;
	m_crAxisTitleFontColor = m_crAxisTitleFont;
	*nValue = (long)m_crAxisTitleFontColor;

	return 0;
}

long CRulerLogAxis::SetAxisBackColor(long nValue)
{
	COLORREF m_crBackColor;
	m_crBackColor = (COLORREF)nValue;
	m_crAxisBackColor = m_crBackColor;

	return 0;
}
long CRulerLogAxis::GetAxisBackColor(long *nValue)
{
	COLORREF m_crBackColor;
	m_crBackColor = m_crAxisBackColor;
    *nValue = (long)m_crBackColor;

	return 0;
}

long CRulerLogAxis::SetWorkAreaBkColor(long nValue)
{
	COLORREF m_crBKColor;
	m_crBKColor = (COLORREF)nValue;
	m_crBkGroundColor = m_crBKColor;

	return 0;
}

long CRulerLogAxis::GetWorkAreaBkColor(long *nValue)
{
	COLORREF m_crBKColor;
	m_crBKColor = m_crBkGroundColor;
	*nValue = (long)m_crBKColor;

	return 0;
}
long CRulerLogAxis::SetWorkAreaBorderLeftTopColor(long nValue)
{
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = (COLORREF)nValue;
	m_crBkLeftTopColor = m_crLeftTopColor;

	return 0;
}

long CRulerLogAxis::GetWorkAreaBorderLeftTopColor(long *nValue)
{
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = m_crBkLeftTopColor;
	*nValue = (long)m_crLeftTopColor;

	return 0;
}

long CRulerLogAxis::SetWorkAreaBorderRightBottomColor(long nValue)
{
	COLORREF m_crRightBottomColor;
	m_crRightBottomColor = (COLORREF)nValue;
	m_crBkRightBottomColor = m_crRightBottomColor;

	return 0;
}
long CRulerLogAxis::GetWorkAreaBorderRightBottomColor(long *nValue)
{
	COLORREF m_crRightBottomColor;
	m_crRightBottomColor = m_crBkRightBottomColor;
	*nValue = (long)m_crRightBottomColor;

	return 0;
}

long CRulerLogAxis::SetWorkAreaBorderShadow(long nValue)
{
	m_iShadow = nValue;

	return 0;
}

long CRulerLogAxis::GetWorkAreaBorderShadow(long *nValue)
{

	*nValue = m_iShadow;

	return 0;
}

//坐标系统边框的颜色
long CRulerLogAxis::SetFrameLeftTopColor(long nValue)
{
	m_crFrameLeftTopColor = (COLORREF)nValue;
		
	return 0;
}

long CRulerLogAxis::GetFrameLeftTopColor(long *nValue)
{
	*nValue = (long)(m_crFrameLeftTopColor);

	return 0;
}

long CRulerLogAxis::SetFrameRightBottomColor(long nValue)
{
	m_crFrameRightBottomColor = (COLORREF)nValue;
		
	return 0;
}

long CRulerLogAxis::GetFrameRightBottomColor(long *nValue)
{
	*nValue = (long)(m_crFrameRightBottomColor);
	
	return 0;
}

//坐标系统边框边界阴影
long CRulerLogAxis::SetFrameShadow(long nValue)
{
	
	m_iFrameShadow = nValue;

	return 0;
}

long CRulerLogAxis::GetFrameShadow(long *nValue)
{
	
	*nValue = m_iFrameShadow;

	return 0;
}


long CRulerLogAxis::SetXUnitScaleColor(long nValue)
{
	COLORREF m_crXUnitScaleColor;
	m_crXUnitScaleColor = (COLORREF)nValue;
	m_crXUnitScaleColor = m_crXUnitScaleColor;

	return 0;
}

long CRulerLogAxis::GetXUnitScaleColor(long *nValue)
{
	*nValue = (long)m_crXUnitScaleColor;

	return 0;
}
long CRulerLogAxis::SetXUnitScaleShadowColor(long nValue)
{
	COLORREF m_crXUnitScaleShadowColor;
	m_crXUnitScaleShadowColor = (COLORREF)nValue;
	m_crXUnitScaleShadowColor = m_crXUnitScaleShadowColor;

	return 0;
}

long CRulerLogAxis::GetXUnitScaleShadowColor(long *nValue)
{
	*nValue = (long)m_crXUnitScaleShadowColor;

	return 0;
}

long CRulerLogAxis::SetXAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName)
{
	LOGFONT   m_lfXAxisScaleFont;
	m_lfXAxisScaleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,lfFaceName);
	m_lfHorzFont = m_lfXAxisScaleFont;

	return 0;
}
long CRulerLogAxis::GetXAxisScaleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName)
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

long CRulerLogAxis::SetXAxisName(const CString & bstrName)
{
	char pszName[MAX_PATH];
	memset(pszName,0,MAX_PATH);
	CString_to_char(bstrName,pszName);
	m_strXAxisName = pszName;

	return 0;
}

long CRulerLogAxis::GetXAxisName(CString *pbstrName)
{
	CString sXAxisName;
	sXAxisName = m_strXAxisName;
	*pbstrName = sXAxisName.AllocSysString();

	return 0;
}

long CRulerLogAxis::SetXAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName)
{
	LOGFONT   m_lfXAxisNameFont;
	m_lfXAxisNameFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,lfFaceName);
	m_lfHorzTitleFont = m_lfXAxisNameFont;

	return 0;
}

long CRulerLogAxis::GetXAxisNameFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName)
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

long CRulerLogAxis::SetXAxisNameFontColor(long nValue)
{
	COLORREF m_crXAxisNameFontColor;
	m_crXAxisNameFontColor = (COLORREF)nValue;
	m_crHorzTitleColor = m_crXAxisNameFontColor;

	return 0;
}
long CRulerLogAxis::GetXAxisNameFontColor(long *nValue)
{
	COLORREF m_crXAxisNameFontColor;
	m_crXAxisNameFontColor = m_crHorzTitleColor;
	*nValue = (long)m_crXAxisNameFontColor;

	return 0;
}

long CRulerLogAxis::SetXAxisScaleFontColor(long nValue)
{
	COLORREF m_crXAxisScaleFontColor;
	m_crXAxisScaleFontColor = (COLORREF)nValue;
	m_crHorzColor = m_crXAxisScaleFontColor;

	return 0;
}

long CRulerLogAxis::GetXAxisScaleFontColor(long *nValue)
{
	COLORREF m_crXAxisScaleFontColor;
	m_crXAxisScaleFontColor = m_crHorzColor;
	*nValue = (long)m_crXAxisScaleFontColor;

	return 0;
}

long CRulerLogAxis::SetXAxisGridLineStyle(long nValue)
{
	m_lAxisGridLineType = nValue;

	return 0;
}

long CRulerLogAxis::GetXAxisGridLineStyle(long *nValue)
{
	*nValue = m_lAxisGridLineType;

	return 0;
}

long CRulerLogAxis::SetXAxisGridLineColor(long nValue)
{
	COLORREF m_crXAxisGrid;
	m_crXAxisGrid = (COLORREF)nValue;
	m_crAxisGrid = m_crXAxisGrid;;

	return 0;
}

long CRulerLogAxis::GetXAxisGridLineColor(long *nValue)
{
	COLORREF m_crXAxisGrid;
	m_crXAxisGrid = m_crAxisGrid;
	*nValue = (long)m_crXAxisGrid;

	return 0;
}

long CRulerLogAxis::SetXAxisTenthScaleColor(long nValue)
{
	COLORREF m_crXAxisTenthScaleColor;
	m_crXAxisTenthScaleColor = (COLORREF)nValue;
	//SetXAxisTenthScaleColor(m_crXAxisTenthScaleColor);
	return 0;
}

long CRulerLogAxis::GetXAxisTenthScaleColor(long *nValue)
{
	COLORREF m_crXAxisTenthScaleColor;
    m_crXAxisTenthScaleColor = m_crXTenthScaleColor;
	*nValue = (long)m_crXAxisTenthScaleColor;

	return 0;
}

long CRulerLogAxis::SetXAxisAreaHeight(long nValue)
{
	m_iHorzAreaWidth = nValue;

	return 0;
}

long CRulerLogAxis::GetXAxisAreaHeight(long *nValue)
{
	*nValue = m_iHorzAreaWidth;

	return 0;
}

long CRulerLogAxis::SetXAxisUnitScaleLineLen(long nValue)
{
	m_iHorzGapLineLen1 = nValue;

	return 0;
}

long CRulerLogAxis::GetXAxisUnitScaleLineLen(long *nValue)
{
	*nValue = m_iHorzGapLineLen1;

	return 0;
}

long CRulerLogAxis::SetXAxisHalfScaleLineLen(long nValue)
{
	m_iHorzGapLineLen2 = nValue;

	return 0;
}

long CRulerLogAxis::GetXAxisHalfScaleLineLen(long *nValue)
{
	*nValue = m_iHorzGapLineLen2;

	return 0;
}

long CRulerLogAxis::SetXAxisTenthScaleLineLen(long nValue)
{
	m_iHorzGapLineLen3 = nValue;

	return 0;
}

long CRulerLogAxis::GetXAxisTenthScaleLineLen(long *nValue)
{
	*nValue = m_iHorzGapLineLen3;

	return 0;
}

long CRulerLogAxis::SetAxisCenterLineWidth(long nValue)
{
	m_lAxisCenterLineWidth = nValue;

	return 0;
}

long CRulerLogAxis::GetAxisCenterLineWidth(long *nValue)
{
	*nValue = m_lAxisCenterLineWidth;

	return 0;
}

long CRulerLogAxis::SetAxisCenterLineType(long nValue)
{
	m_lAxisCenterLineType = nValue;

	return 0;
}

long CRulerLogAxis::GetAxisCenterLineType(long *nValue)
{
	*nValue = m_lAxisCenterLineType;

	return 0;
}

long CRulerLogAxis::SetAxisCenterColor(long nValue)
{
	COLORREF m_crAxisCenterColor;
	m_crAxisCenterColor = (COLORREF)nValue;
	m_crAxisCenter = m_crAxisCenterColor;

	return 0;
}

long CRulerLogAxis::GetAxisCenterColor(long *nValue)
{
	COLORREF m_crAxisCenterColor;
	m_crAxisCenterColor = m_crAxisCenter;
	*nValue = (long)m_crAxisCenterColor;

	return 0;
}

long CRulerLogAxis::LogicPointToDevicePoint(double x,double y,long *ptx,long *pty)
{
	CPoint point(*ptx,*pty);
	LogicPointToDevicePoint(x,y, &point);

	return 0;
}

long CRulerLogAxis::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
{
	CPoint Point;
	Point = CPoint(ptx,pty);
	DevicePointToLogicPoint(Point,x,y, 0);

	return 0;
}

long CRulerLogAxis::SetMinMaxVal(double xMin,double yMin,double xMax,double yMax,long nReserved)
{
	SetAxisMinMaxVal(xMin,yMin,xMax,yMax);

	return 0;
}

long CRulerLogAxis::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
{
	GetAxisMinMaxVal(xMin,yMin,xMax,yMax);

	return 0;
}

long CRulerLogAxis::SetBoder(long left, long top, long right, long bottom)
{
	CRect rectW;
	rectW = CRect(left, top, right, bottom);
	SetBorder(rectW);

	return 0;
}

long CRulerLogAxis::GetBoder(long *left, long *top, long *right, long *bottom)
{
	CRect m_rectBoder;
    m_rectBoder = m_rectRuler;
	*left = m_rectBoder.left;
	*top = m_rectBoder.top;
	*right = m_rectBoder.right;
	*bottom = m_rectBoder.bottom;

	return 0;
}

long CRulerLogAxis::GetWorkArea(long *left, long *top, long *right, long *bottom)
{
	CRect rectWorkArea;
    rectWorkArea = m_rectRuler;
	*left = rectWorkArea.left;
	*top = rectWorkArea.top;
	*right = rectWorkArea.right;
	*bottom = rectWorkArea.bottom;

	return 0;
}

CRect CRulerLogAxis::GetWorkArea()
{
    return m_rectRuler;
}

long CRulerLogAxis::GetXAxisArea(long *left, long *top, long *right, long *bottom)
{
	CRect rectXAxisArea;
    rectXAxisArea = m_rectRuler;
	*left = rectXAxisArea.left;
	*top = rectXAxisArea.top;
	*right = rectXAxisArea.right;
	*bottom = rectXAxisArea.bottom;

	return 0;
}

long CRulerLogAxis::GetYAxisArea(long *left, long *top, long *right, long *bottom)
{
	CRect rectYAxisArea;
    rectYAxisArea = m_rectRuler;
	*left = rectYAxisArea.left;
	*top = rectYAxisArea.top;
	*right = rectYAxisArea.right;
	*bottom = rectYAxisArea.bottom;

	return 0;
}

long CRulerLogAxis::DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset)
{
	CPoint ptOffset;
	ptOffset = CPoint(xOffset,yOffset);
	DrawIt(pDC,fZoomRatio,ptOffset);

	return 0;
}

long CRulerLogAxis::ZoomIn1(float fRate)
{
	ZoomIn(fRate);

	return 0;
}

long CRulerLogAxis::ZoomIn2(double dMinX,double dMaxX,double dMinY,double dMaxY)
{
	ZoomIn(dMinX, dMaxX, dMinY, dMaxY);

	return 0;
}

long CRulerLogAxis::ZoomIn3(long left,long top,long right,long bottom)
{
	ZoomIn(left,top,right,bottom);

	return 0;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// 
// long CRulerLogAxis::GetBoder(long *left, long *top, long *right, long *bottom)
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
// long CRulerLogAxis::GetWorkArea(long *left, long *top, long *right, long *bottom)
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
// long CRulerLogAxis::LogicPointToDevicePoint(double x,double y,long *ptx,long *pty)
// {
// 	CPoint pPoint = CPoint(*ptx,*pty); 
// 	LogicPointToDevicePoint(x,y,&pPoint);
// 	
// 	return 0;
// }
// 
// long CRulerLogAxis::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
// {
// 	CPoint pPoint = CPoint(ptx,pty); 
// 	DevicePointToLogicPoint(pPoint,x,y);
// 	
// 	return 0;
// }
// 
// 
// long CRulerLogAxis::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
// {
// 	*xMin = iBeginPalace;
// 	*yMin = iDisplayMinVal;
// 	*xMax = iEndPalace;
// 	*yMax = iDisplayMaxVal;
// 	
// 	return 0;
// }
