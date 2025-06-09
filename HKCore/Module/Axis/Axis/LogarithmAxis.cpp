// LogarithmAxis.cpp : implementation file
//

#include "stdafx.h"
#include "Axis.h"
#include "LogarithmAxis.h"
#include "..\..\Module\Api\GloblaDrawFunctions.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BOTTOMADD 2
/////////////////////////////////////////////////////////////////////////////
// CLogarithmAxis

IMPLEMENT_DYNCREATE(CLogarithmAxis, CCmdTarget)

CLogarithmAxis::CLogarithmAxis()
{
	EnableAutomation();
	
	iVertGapLineLen3=4*iMM;
	iHorzGapLineLen3=5*iMM;

	m_lAxisType = 0;
	m_lCurrTestItem = 0;
	m_bAxisXYUnitLock = TRUE;
	m_lXAxisMaxUnitCount = 10;
	m_lYAxisMaxUnitCount = 10;
	m_lAxisDrawStyle = LOGARITHMAXISDRAW_ALL;
	lDisplayType=POWERADVANCE_ALL;
	lVertLineStyle=PS_DOT;
	lHorzLineStyle=PS_DOT;
	crVert_WorkAreaLine_Color=RGB(0,0,0);
	crHorz_WorkAreaLine_Color=RGB(0,0,0);
	crAxisCenter = RGB(240,240,240);
	ContinueInit();
	lDisplayType&= (~LOGARITHM_YAXIS_LLINE);
	
	crCircleScale=RGB(240,240,240);
	crBiaslineScale=RGB(240,240,240);
	

	m_strAxisTitle = "";
	m_crAxisTitleFont = RGB(0,0,0);
	m_lfAxisTitleFont = InitLogFont (-14,0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',"宋体");
	cXAxisName = "";
	cYAxisName = "";

	m_crFrameLeftTopColor = RGB(128,128,128);
	m_crFrameRightBottomColor = RGB(240,240,240);
	m_iFrameShadow = 2;

	m_crAxisBackColor = GetSysColor(COLOR_3DFACE);//RGB(240,240,240);

	m_dMaxZoomMultiple = 100.0f;
	m_dAxisWorkMarginRatio = 0.05;

	cWorkArea=CRect(30,5,300,300);
	cX_Axis=CRect(30,300,300,320);
	cY_Axis=CRect(0,5,30,300);
	iBeginPalace=0;
	iEndPalace=3269;
	//	iKeepMinVal=iDisplayMinVal=0;
	//	iKeepMaxVal=iDisplayMaxVal=2000000;
	iDataMinVal=0;
	iDataMaxVal=200;
	iMinValueXAxis=0;
	iMaxValueXAxis=100;
	m_iXMultipleCoeff=1;
	m_iYMultipleCoeff=1;
	m_iXMaxMultipleCoeff=100;
	m_iYMaxMultipleCoeff=100;		////图形放大的比例		逻辑值 / 设备值
	m_iXMinMultipleCoeff=100;
	m_iYMinMultipleCoeff=100;		////图形放大的比例		逻辑值 / 设备值
	
	m_fXCarryOneGap=1;
	m_fYCarryOneGap=1;

	iMM=1;
	InitIt();

	AfxOleLockApp();
}

CLogarithmAxis::~CLogarithmAxis()
{
	EndXAxisDef();
	EndYAxisDef();
	
	AfxOleUnlockApp();
}

void CLogarithmAxis::ContinueInit()
{
	cBkGroundBrush=InitLogBrush(BS_SOLID,1,crBkGroundColor);
	crVert_WorkAreaLine_Pen=InitLogPen(lVertLineStyle,1,crVert_WorkAreaLine_Color);
	crVert_WorkAreaShortLine_Pen=InitLogPen(PS_SOLID,1,m_crYTenthScaleColor);//crVert_WorkAreaLine_Color);
	crHorz_WorkAreaLine_Pen=InitLogPen(lHorzLineStyle,1,crHorz_WorkAreaLine_Color);
	crHorz_WorkAreaShortLine_Pen=InitLogPen(PS_SOLID,1,m_crXTenthScaleColor);//crHorz_WorkAreaLine_Color);
	cr_CircleScale_Pen		=InitLogPen(lCircleLineType,1,crCircleScale);
	cr_BiaslineScale_Pen	=InitLogPen(lBiasLineType,1,crBiaslineScale);
}
void CLogarithmAxis::InitIt()
{
	iLeftGap=15*iMM;iRightGap=5*iMM;
	iTopGap=20*iMM;iBottomGap=5*iMM;
	
	//WorkArea Bk
	crBkGroundColor=RGB(255,255,255);
	crBkLeftTopColor=RGB(128,128,128);
	crBkRightBottomColor=RGB(240,240,240);
	iShadow=2*iMM;
	
	m_crYUnitScaleColor=RGB(0,0,0);
	m_crYUnitScaleShadowColor=RGB(230,230,230);
	m_crXUnitScaleColor=RGB(0,0,0);
	m_crXUnitScaleShadowColor=RGB(230,230,230);
	
	//VertDef
	lfVertFont=InitLogFont (-9*iMM,0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
	lfVertTitleFont=InitLogFont (-9*iMM,0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
	crVertColor=RGB(0,0,0);
	crVertTitleColor=RGB(0,0,0);
	lVertLineStyle=PS_SOLID;
	crVert_WorkAreaLine_Color=RGB(240,240,240);//RGB(83,83,83);
	iVertAreaWidth=35*iMM;
	iVertGapLineLen1=10*iMM;
	iVertGapLineLen2=8*iMM;
	iVertGapLineLen3=3*iMM;
	//HorzDef
	lfHorzFont=InitLogFont (-9*iMM,0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
	lfHorzTitleFont=InitLogFont (-12*iMM,0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
	crHorzColor=RGB(0,0,0);
	crHorzTitleColor=RGB(0,0,0);
	lHorzLineStyle=PS_SOLID;
	crHorz_WorkAreaLine_Color=RGB(240,240,240);//RGB(83,83,83);  //////////grid hor_z
	iHorzAreaWidth=20*iMM;
	iHorzGapLineLen1=10*iMM;
	iHorzGapLineLen2=8*iMM;
	iHorzGapLineLen3=3*iMM;
	
	//Cursor and Choice Area
	lCursorPen=InitLogPen(PS_SOLID,1,RGB(255,255,255));
	lChoiceAreaPen=InitLogPen(PS_SOLID,1,RGB(255,255,255));
	lChoiceAreaBrush=InitLogBrush(BS_SOLID,1,RGB(255,255,255));
	
	crCircleScale	=RGB(240,240,240);
	crBiaslineScale=RGB(240,240,240);
	cr_CircleScale_Pen		=InitLogPen(lCircleLineType,1,crCircleScale);
	cr_BiaslineScale_Pen	=InitLogPen(lBiasLineType,1,crBiaslineScale);
	fCircleScaleOffset=1;
	fBiaslineScaleOffset=15;	//圆刻度的半径位移、斜线刻度的角度位移
	
	////////	坐标轴中心轴参数定义
	lAxisCenterLineWidth=1;
	lAxisCenterLineType = PS_SOLID;
	crAxisCenter = RGB(0,0,0);
	
	lDrawXAxisTextType=1;
	lDisplayType=POWERADVANCE_ALL;

/////////////////////////////
/////////////////////////////
	cWorkArea=CRect(30,5,300,300);
	cX_Axis=CRect(30,300,300,320);
	cY_Axis=CRect(0,5,30,300);
	iBeginPalace=0;
	iEndPalace=3269;
	//	iKeepMinVal=iDisplayMinVal=0;
	//	iKeepMaxVal=iDisplayMaxVal=2000000;
	iDataMinVal=0;
	iDataMaxVal=200;
	iMinValueXAxis=0;
	iMaxValueXAxis=100;
	m_iXMultipleCoeff=1;
	m_iYMultipleCoeff=1;
	m_iXMaxMultipleCoeff=100;
	m_iYMaxMultipleCoeff=100;		////图形放大的比例		逻辑值 / 设备值
	m_iXMinMultipleCoeff=100;
	m_iYMinMultipleCoeff=100;		////图形放大的比例		逻辑值 / 设备值
	
	m_ptCenterLogInDv = CPoint(0,0);
	iDirection = 0;
	m_fXCarryOneGap=1;
	m_fYCarryOneGap=1;
	
	//	bAutoComputeLimit=TRUE;
}

const CLogarithmAxis & CLogarithmAxis::operator =(CLogarithmAxis &odTemp)
{
	if (&odTemp==this) return *this;
	cBorder=odTemp.cBorder;
	cWorkArea=odTemp.cWorkArea;
	cX_Axis=odTemp.cX_Axis;
	cY_Axis=odTemp.cY_Axis;
	iBeginPalace=odTemp.iBeginPalace;
	iEndPalace=odTemp.iEndPalace;
	iDataMinVal=odTemp.iDataMinVal;
	iDataMaxVal=odTemp.iDataMaxVal;
	iDisplayMinVal=odTemp.iDisplayMinVal;
	iDisplayMaxVal=odTemp.iDisplayMaxVal;
	iDirection=odTemp.iDirection;
	return *this;
}


void CLogarithmAxis::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CLogarithmAxis, CCmdTarget)
	//{{AFX_MSG_MAP(CLogarithmAxis)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLogarithmAxis, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CLogarithmAxis)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ILogarithmAxis to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {91CE65B6-3E07-488B-B22D-1A41D4B83ADD}
static const IID IID_ILogarithmAxis =
{ 0x91ce65b6, 0x3e07, 0x488b, { 0xb2, 0x2d, 0x1a, 0x41, 0xd4, 0xb8, 0x3a, 0xdd } };

BEGIN_INTERFACE_MAP(CLogarithmAxis, CCmdTarget)
	INTERFACE_PART(CLogarithmAxis, IID_ILogarithmAxis, Dispatch)
	INTERFACE_PART(CLogarithmAxis, IID_ILogarithmAxisInterface, LogarithmAxisInterface)
	INTERFACE_PART(CLogarithmAxis, IID_IAxisBaseInterface,AxisBaseInterface)
END_INTERFACE_MAP()

// {CA9C9D73-51CF-4978-89E4-A56E57CD8C37}
IMPLEMENT_OLECREATE(CLogarithmAxis, PROGID_ILogarithmAxis, 0xca9c9d73, 0x51cf, 0x4978, 0x89, 0xe4, 0xa5, 0x6e, 0x57, 0xcd, 0x8c, 0x37)

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
	odYAxisDef.EndIt();
}
void CLogarithmAxis::EndYAxisDef()
{
	odYAxisDef.EndIt();
}
void CLogarithmAxis::ResetYAxisDef()
{
	EndYAxisDef();
	float fBeginVal=iDisplayMinVal;
	float fEndVal=iDisplayMaxVal;
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

	float iBeginVal=GetBeginVal(iDisplayMinVal,iGapVal);
	GetOneYAxisHeight(iGapVal,1);
	for (int i=0;i<=iGapNumTemp;i++)
	{
		ResetOneYAxisDef(iBeginVal+i*iGapVal);
	}
	m_fYCarryOneGap=iGapVal;
}
void CLogarithmAxis::GetOneYAxisHeight(float iGap,BYTE bKind)
{
	int iHeight=cY_Axis.Height();
	float iVal=iDisplayMaxVal-iDisplayMinVal;
	iYAxisOneGap=iGap*(float)iHeight/iVal;
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
void CLogarithmAxis::ResetOneYAxisDef(float lVal)
{
	int iHeight=cY_Axis.Height();
	float iVal=iDisplayMaxVal-iDisplayMinVal;
	float f = cY_Axis.bottom-(lVal-iDisplayMinVal)*((float)iHeight / iVal );
	int y=FloatValToInt(f);
	CAxisScaleData *odData=new CAxisScaleData();
	odData->FillIt2(lVal,0,0,CPoint(cY_Axis.right,y));
	odYAxisDef.AddTail(odData);
}

void CLogarithmAxis::DrawYAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio,CPoint ptOffset)
{
	CPoint pt;
	pt.x = cWorkArea.left;
	pt.y = odData->cPt.y;
	pt.Offset(ptOffset);
	cDC->MoveTo(pt);

	pt.x = cWorkArea.right;
	pt.y = odData->cPt.y;
	pt.Offset(ptOffset);
	cDC->LineTo(pt);
}
void CLogarithmAxis::DrawYAxisText(CDC *cDC,CAxisScaleData *odData,float fZoomRatio,CPoint ptOffset)
{
	char cStr[128];
	float fText=odData->lVal;
	fText=pow(10,fText);
	sprintf(cStr,"%.3f",fText);
	chop(cStr);
	long lHeight=(long)abs(lfVertFont.lfHeight * fZoomRatio);
	CRect cR;
	cR.left=cY_Axis.left;
	cR.top=odData->cPt.y-lHeight;
	cR.right=cY_Axis.right-iVertGapLineLen1 * fZoomRatio;
	cR.bottom=odData->cPt.y+lHeight;
	cR.OffsetRect(ptOffset);
	CmDrawTextRect(cDC,cStr,crVertColor,&cR,RGB(0,0,0),lfVertFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}
void CLogarithmAxis::DrawYAxisName(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{
	CRect cR;
	cR.left=cBorder.left+2;
	cR.top=cBorder.top;
	cR.right=cY_Axis.right-3;
	cR.bottom=cBorder.top+15*fZoomRatio;
	cR.OffsetRect(ptOffset);
	char cName[128];
	lstrcpy(cName,cYAxisName);
	CmDrawTextRect(cDC,(LPSTR)cName,crVertTitleColor,
				   &cR,RGB(0,0,0),lfVertTitleFont,
				   TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}
void CLogarithmAxis::DrawYAxis(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{
	int iNum=odYAxisDef.GetCount();
	if(iNum<=0)return;
	CPen cP;
	long lGap=(long)(abs(lfVertFont.lfHeight)*1.5 * fZoomRatio);
	cP.CreatePenIndirect(&crVert_WorkAreaLine_Pen);
	CPen *cOldP=cDC->SelectObject(&cP);
	for (int i=0;i<iNum;i++)
	{
		CAxisScaleData *odData=(CAxisScaleData*)odYAxisDef.GetAt(odYAxisDef.FindIndex(i));
		if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_SCALETEXT)
		{
			if( lDisplayType & POWERADVANCE_YAXIS_TEXT)
			{
				if(odData->cPt.y>=cY_Axis.top)
					DrawYAxisText(cDC,odData,fZoomRatio,ptOffset);////标注
			}
		}
		if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_LINE)
		{
			if(lDisplayType& POWERADVANCE_YAXIS_LINE)
			{
				if ((odData->cPt.y>cY_Axis.top)&&(odData->cPt.y<cX_Axis.bottom))
				{
					DrawYAxisLine(cDC,odData,fZoomRatio,ptOffset);//网格
				}
			}
		}
	}
	cDC->SelectObject(cOldP);
	cP.DeleteObject();
	if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_TENTHSCALE)
		if(  lDisplayType & POWERADVANCE_YAXIS_SAWTOOTH1)
			DrawYSawtooth(cDC,0,fZoomRatio,ptOffset);
	if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_HALFSCCALE)
		if(  lDisplayType & POWERADVANCE_YAXIS_SAWTOOTH2)			
			DrawYSawtooth(cDC,1,fZoomRatio,ptOffset);
//	if( m_lAxisDrawStyle & LOGARITHMAXISDRAW_YAXIS_NAME)
//		if(  lDisplayType & POWERADVANCE_YAXIS_TEXT)						
//			DrawYAxisName(cDC,fZoomRatio,ptOffset);
}
///////////////靠工作区内的小锯齿
void CLogarithmAxis::DrawOneYSawtooth(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{
	CPen cP;
	cP.CreatePenIndirect(&crVert_WorkAreaShortLine_Pen);
	CPen *cOldP=cDC->SelectObject(&cP);
	int iDeltaY=0;
	float fVal=0;
	for (int i=2;i<10;i++)
	{
		fVal=fCarryVal * i ;
		fVal=log10(fVal);
		float f = cY_Axis.bottom-(fVal-iDisplayMinVal)*iYAxisOneGap;
		int y=FloatValToInt(f);

		CPoint cPt(cBegin.x,y);
		if((cPt.y<cY_Axis.top)||(cPt.y>cY_Axis.bottom))
			continue;
		cPt.Offset(ptOffset);
		cDC->MoveTo(cPt.x-1,cPt.y);
		cDC->LineTo(cPt.x-(long)(fZoomRatio*iVertGapLineLen3),cPt.y);
	}
	cDC->SelectObject(cOldP);
	cP.DeleteObject();

	if(lDisplayType & LOGARITHMAXISDRAW_YAXIS_LINE)
	{
		cP.CreatePenIndirect(&crVert_WorkAreaLine_Pen);
		cOldP=cDC->SelectObject(&cP);
		for (i=2;i<10;i++)
		{
			fVal=fCarryVal * i ;
			fVal=log10(fVal);
			float f=cY_Axis.bottom-(fVal-iDisplayMinVal)*iYAxisOneGap;
			int y=FloatValToInt(f);

			CPoint cPt(cBegin.x,y);
			if((cPt.y<cY_Axis.top)||(cPt.y>cY_Axis.bottom))continue;
			cPt.Offset(ptOffset);
			cDC->MoveTo(cWorkArea.left+BOTTOMADD,cPt.y);
			cDC->LineTo((long)(fZoomRatio*cWorkArea.right),cPt.y);
		}
		cDC->SelectObject(cOldP);
		cP.DeleteObject();
	}
}
///////////////大刻度
void CLogarithmAxis::DrawOneYSawtoothShadow(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{
	int iLen=(long)(fZoomRatio*iVertGapLineLen1);
	CPoint cPt(cBegin.x,cBegin.y);
	if((cPt.y>=(long)(fZoomRatio*cY_Axis.top))&&(cPt.y<=(long)(fZoomRatio*cY_Axis.bottom)))
	{
		cPt.Offset(ptOffset);
		DrawShadowHorzLine(cDC,cPt.x,cPt.y,iLen,m_crYUnitScaleColor,m_crYUnitScaleShadowColor);
	}
}
void CLogarithmAxis::DrawYSawtooth(CDC *cDC,BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;
	float fCarryVal=0;
	for (int i=0;i<odYAxisDef.GetCount();i++)
	{
		CAxisScaleData *odData=(CAxisScaleData *)odYAxisDef.GetAt(odYAxisDef.FindIndex(i));
		fCarryVal=pow(10,odData->lVal);
		if (i==0)
		{
			cBegin=CPoint(odData->cPt.x,odData->cPt.y+iXAxisOneGap);
			cEnd=odData->cPt;			
		}
		else
		{
			CAxisScaleData *odNewData=(CAxisScaleData *)odYAxisDef.GetAt(odYAxisDef.FindIndex(i-1));
			cBegin=odNewData->cPt;
			cEnd=odData->cPt;
		}
		if (bKind==0)
			DrawOneYSawtooth(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else
			DrawOneYSawtoothShadow(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		
	}
	if(odYAxisDef.GetCount()>=2)
	{
		CAxisScaleData *odData=(CAxisScaleData *)odYAxisDef.GetTail();
		cEnd=CPoint(odData->cPt.x,odData->cPt.y-iYAxisOneGap);
		cBegin=odData->cPt;
		fCarryVal=pow(10,odData->lVal);
		if (bKind==0)
			DrawOneYSawtooth(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else 
			DrawOneYSawtoothShadow(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
	}
}

//#######################################################################
//******************************关于X轴的绘制****************************
//#######################################################################

void CLogarithmAxis::InitXAxisDef(){odXAxisDef.EndIt();}
void CLogarithmAxis::EndXAxisDef(){odXAxisDef.EndIt();}


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

	float fBeginVal=iBeginPalace;
	float fEndVal=iEndPalace;
	float iGapNum=0;

	fBeginVal=FloatValToInt(fBeginVal);
	fEndVal=FloatValToInt(fEndVal);
	iGapNum = fEndVal - fBeginVal;

	int iGapNumTemp=FloatValToInt(iGapNum);
	float iGapVal=1.0f;
	float iBeginVal=GetXBeginVal(iBeginPalace,iGapVal);
	GetOneXAxisWidth(iGapVal,1);
	for (int i=0;i<=iGapNumTemp;i++)
		ResetOneXAxisDef(iBeginVal+i*iGapVal,0);
	m_fXCarryOneGap=iGapVal;
}
void CLogarithmAxis::GetOneXAxisWidth(float iGap,BYTE bKind)
{
	int iWidth=cX_Axis.Width();
	float iVal=(iEndPalace-iBeginPalace);
	iXAxisOneGap=iGap*(float)iWidth/iVal;
}
void CLogarithmAxis::ResetOneXAxisDef(float lVal,BYTE bKind)
{
	int iWidth=cX_Axis.Width();
	float iVal=(iEndPalace-iBeginPalace);//FloatValToInt
	float f=cX_Axis.left+(lVal-iBeginPalace)*(float)iWidth/iVal;
	int x=FloatValToInt(f);
	CAxisScaleData *odData=new CAxisScaleData();
	int iIntegeralBeginPalace=0;//GetIntegeralBeginPalace();
	if(bKind==0) 
	{
		float f=(float)(lVal-iIntegeralBeginPalace);
		odData->FillIt2(lVal,f,1,CPoint(x,cX_Axis.top+BOTTOMADD));
	}
	else 
	{
		float f=(float)(lVal-iIntegeralBeginPalace);
		odData->FillIt2(lVal,f,1,CPoint(x,cX_Axis.top+BOTTOMADD));
	}
	odXAxisDef.AddTail(odData);
}
void CLogarithmAxis::DrawXAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio,CPoint ptOffset)
{
	CPoint pt;
	pt.x = odData->cPt.x;
	pt.y = (long)(fZoomRatio*cWorkArea.top+iShadow);
	pt.Offset(ptOffset);
	cDC->MoveTo(pt);

	pt.x = odData->cPt.x;
	pt.y = (long)(fZoomRatio*cWorkArea.bottom+BOTTOMADD);
	pt.Offset(ptOffset);
	cDC->LineTo(pt);
}

CRect  CLogarithmAxis::DrawXAxisText(CDC *cDC,CAxisScaleData *odData,BOOL bAddUint,BOOL bReallyDraw,float fZoomRatio,CPoint ptOffset)
{
	CRect cBack(-1,-1,-1,-1);
	char cStr[128];
	float fText=odData->lVal;
	fText=pow(10,fText);
	sprintf(cStr,"%.4f",fText);
	chop(cStr);
	CRect cR1=CRect(odData->cPt.x-(long)(fZoomRatio * 20),odData->cPt.y+(long)(fZoomRatio * 7),odData->cPt.x+(long)(fZoomRatio * 24),odData->cPt.y+(long)(fZoomRatio * 20));
	CRect cR;

	if(lDrawXAxisTextType==1)
	{
		cR=CRect(odData->cPt.x-cR1.Width()/2-2,odData->cPt.y+(long)(fZoomRatio * iHorzGapLineLen1),
			 odData->cPt.x+cR1.Width()/2+2,odData->cPt.y+(long)(fZoomRatio * iHorzGapLineLen1)+cR1.Height());
		cR.OffsetRect(ptOffset);
		if(bReallyDraw)CmDrawTextRect(cDC,cStr,crHorzColor,cR,RGB(0,0,0),lfHorzFont,TRANSPARENT,DT_VCENTER|DT_CENTER,0);
	}
	else
	{
		cR=CRect(odData->cPt.x+3,odData->cPt.y+(long)(fZoomRatio * iHorzGapLineLen3),
			 odData->cPt.x+cR1.Width()+2,odData->cPt.y+(long)(fZoomRatio * iHorzGapLineLen1)+cR1.Height());
		cR.OffsetRect(ptOffset);
		if(bReallyDraw)CmDrawTextRect(cDC,cStr,crHorzColor,cR,RGB(0,0,0),lfHorzFont,TRANSPARENT,0,0);
	}
	return cR;
}
void CLogarithmAxis::DrawXAxisName(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	int iLen=cXAxisName.GetLength();
	CFont CF;
	CF.CreateFontIndirect(&lfHorzTitleFont);
	CFont *c=pDC->SelectObject(&CF);
	TEXTMETRIC textMetric;
	pDC->GetTextMetrics(&textMetric);
	pDC->SelectObject(c);
	iLen=textMetric.tmAveCharWidth *(iLen+1);

	CRect cR;
	cR.left=cX_Axis.right-iLen;
	cR.top=cBorder.bottom-(long)(fZoomRatio * 10);
	cR.right= cX_Axis.right;
	cR.bottom=cBorder.bottom;
	cR.OffsetRect(ptOffset);
	char cName[128];
	lstrcpy(cName,cXAxisName);
	CmDrawTextRect(pDC,(LPSTR)cName,crHorzTitleColor,&cR,RGB(0,0,0),
				   lfHorzTitleFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}

void CLogarithmAxis::DrawXAxis(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{
	int iNum=odXAxisDef.GetCount();
	if(iNum<=0)return;
	CPen cP;
	cP.CreatePenIndirect(&crHorz_WorkAreaLine_Pen);
	CPen *cOldB=cDC->SelectObject(&cP);
	float iIntgerEndPalace=iEndPalace;//GetIntegeralEndPalace();
	if(iIntgerEndPalace<0)iIntgerEndPalace=0;

	for (int i=0;i<iNum;i++)
	{
		CAxisScaleData *odData=(CAxisScaleData*)odXAxisDef.GetAt(odXAxisDef.FindIndex(i));
		long lVal=lDisplayType & POWERADVANCE_XAXIS_LINE;
		if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_XAXIS_LINE)
		{
			if(lVal)
			{
				if ((odData->cPt.x>cX_Axis.left)&&(odData->cPt.x<cX_Axis.right))
				{
					DrawXAxisLine(cDC,odData,fZoomRatio,ptOffset);
				}
			}
		}
		
	}
	if(((m_lAxisDrawStyle & LOGARITHMAXISDRAW_XAXIS_SCALETEXT))&&((lDisplayType & POWERADVANCE_XAXIS_TEXT)))
	{
		int iStep=iNum;
		for (int i=0;i<iNum;i++)
		{
			CAxisScaleData *odData=(CAxisScaleData*)odXAxisDef.GetAt(odXAxisDef.FindIndex(i));
		}
		BOOL bDrawUint=FALSE;
		for (i=0;i<iStep-1;i++)
		{
			CAxisScaleData *odData=(CAxisScaleData*)odXAxisDef.GetAt(odXAxisDef.FindIndex(i));
			if(odData->cPt.x<cX_Axis.left) 
				continue;
			DrawXAxisText(cDC,odData,bDrawUint,TRUE,fZoomRatio,ptOffset);
		}
		CAxisScaleData *odData=(CAxisScaleData*)odXAxisDef.GetAt(odXAxisDef.FindIndex(i));
		if(odData->cPt.x > cX_Axis.left) 
		{
			char cStr[128];//lfHorzFont
			sprintf(cStr,"%.4f",(float)odData->fVal);
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
			int iLenAxis=cXAxisName.GetLength();
			CFont CF;
			CF.CreateFontIndirect(&lfHorzTitleFont);
			CFont *c=cDC->SelectObject(&CF);
			TEXTMETRIC *textMetric=new TEXTMETRIC;
			cDC->GetTextMetrics(textMetric);
			cDC->SelectObject(c);
			iLenAxis=textMetric->tmMaxCharWidth *(iLenAxis+1);
			CF.DeleteObject();
			///////////////////////////////////////////////////////

			////////////////////////////////获得坐标轴标注]字体长度
			chop(cStr);
			iLen=strlen(cStr);
			CF.CreateFontIndirect(&lfHorzFont);
			c=cDC->SelectObject(&CF);
			cDC->GetTextMetrics(textMetric);
			cDC->SelectObject(c);
			iLen=textMetric->tmMaxCharWidth * iLen;
			CF.DeleteObject();
			delete textMetric;
			///////////////////////////////////////////////////////
			//if(odData->cPt.x+iLen < cX_Axis.right-iLenAxis)
				DrawXAxisText(cDC,odData,bDrawUint,TRUE,fZoomRatio,ptOffset);
		}
	}
	cDC->SelectObject(cOldB);
	cP.DeleteObject();
	if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_XAXIS_TENTHSCALE)
		if(lDisplayType & POWERADVANCE_XAXIS_SAWTOOTH1)
			DrawXSawtooth(cDC,0,fZoomRatio,ptOffset);
	if(m_lAxisDrawStyle & LOGARITHMAXISDRAW_XAXIS_HALFSCCALE)
		if(lDisplayType & POWERADVANCE_XAXIS_SAWTOOTH2)
			DrawXSawtooth(cDC,1,fZoomRatio,ptOffset);
		
	//DrawXAxisName(cDC,fZoomRatio,ptOffset);
}

void CLogarithmAxis::DrawOneXSawtooth(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{                                     
	CPen cP;
	cP.CreatePenIndirect(&crHorz_WorkAreaShortLine_Pen);
	CPen *pOldPen=cDC->SelectObject(&cP);
	float fVal=0;
	for (int i=2;i<10;i++)
	{
		fVal=fCarryVal * i ;
		fVal=log10(fVal);
		float f=cX_Axis.left+(fVal-iBeginPalace)*iXAxisOneGap;
		int x=FloatValToInt(f);

		CPoint cPt(x,cBegin.y);
		if((cPt.x<cX_Axis.left)||(cPt.x>cX_Axis.right)) continue;
		cPt.Offset(ptOffset);
		cDC->MoveTo(cPt.x,cPt.y+(long)(fZoomRatio*1));
		cDC->LineTo(cPt.x,cPt.y+(long)(fZoomRatio*iHorzGapLineLen3));
	}
	cDC->SelectObject(pOldPen);
	cP.DeleteObject();

	if(lDisplayType & LOGARITHMAXISDRAW_XAXIS_LINE)
	{
		cP.CreatePenIndirect(&crHorz_WorkAreaLine_Pen);
		CPen *cOldB=cDC->SelectObject(&cP);
		for (i=2;i<10;i++)
		{
			fVal=fCarryVal * i ;
			fVal=log10(fVal);
			float f=cX_Axis.left+(fVal-iBeginPalace)*iXAxisOneGap;
			int x=FloatValToInt(f);

			CPoint cPt(x,cBegin.y);
			if((cPt.x<cX_Axis.left)||(cPt.x>cX_Axis.right)) continue;
			cPt.Offset(ptOffset);			
			cDC->MoveTo(cPt.x,cWorkArea.top+(long)(fZoomRatio*BOTTOMADD));
			cDC->LineTo(cPt.x,(long)(fZoomRatio*cWorkArea.bottom));
		}
		cDC->SelectObject(pOldPen);
		cP.DeleteObject();
	}

}
void CLogarithmAxis::DrawOneXSawtoothShadow(CDC *cDC, CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio,CPoint ptOffset)
{
	int iLen[2]={(long)(fZoomRatio*iHorzGapLineLen1),(long)(fZoomRatio*iHorzGapLineLen2)};
	for (int i=0;i<1;i++)
	{
		int iGapVal=GetIntVal((float)((float)iXAxisOneGap/2.0*i));
		CPoint cPt(cBegin.x+iGapVal,cBegin.y);
		if((cPt.x<cX_Axis.left)||(cPt.x>cX_Axis.right)) continue;
		cPt.Offset(ptOffset);
		DrawShadowVertLine(cDC,cPt.x,cPt.y,iLen[i],m_crXUnitScaleColor,m_crXUnitScaleShadowColor);
	}
}
void CLogarithmAxis::DrawXSawtooth(CDC *cDC,BYTE bKind,float fZoomRatio,CPoint ptOffset)
{
	CPoint cBegin,cEnd;
	float fCarryVal=0;
	for (int i=0;i<odXAxisDef.GetCount();i++)
	{
		CAxisScaleData *odData=(CAxisScaleData *)odXAxisDef.GetAt(odXAxisDef.FindIndex(i));
		fCarryVal=pow(10,odData->lVal);
		if (i==0)
		{
			cBegin=CPoint(odData->cPt.x-iXAxisOneGap,odData->cPt.y);
			cEnd=odData->cPt;
		}
		else 
		{
				CAxisScaleData *odNewData=(CAxisScaleData *)odXAxisDef.GetAt(odXAxisDef.FindIndex(i-1));
				cBegin=odNewData->cPt;
				cEnd=odData->cPt;
		}	
		if (bKind==0)
			DrawOneXSawtooth(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else 
			DrawOneXSawtoothShadow(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
	}
	if(odXAxisDef.GetCount()>=2)
	{
		CAxisScaleData *odData=(CAxisScaleData *)odXAxisDef.GetTail();
		cEnd=CPoint(odData->cPt.x+iXAxisOneGap,odData->cPt.y);
		cBegin=odData->cPt;
		if (bKind==0)DrawOneXSawtooth(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
		else DrawOneXSawtoothShadow(cDC,cBegin,cEnd,fCarryVal,fZoomRatio,ptOffset);
	}
}

void CLogarithmAxis::DrawIt(CDC *cDC,float fZoomRatio,CPoint ptOffset)
{

	if(m_lAxisDrawStyle &LOGARITHMAXISDRAW_WORKAREA)
//		if(lDisplayType&LOGARITHMAXISDRAW_WORKAREA)
		DrawArea(cDC,fZoomRatio,ptOffset);
	
//	if(m_lAxisDrawStyle &POWERADVANCE_YAXIS)	////绘制Y轴
//		if(lDisplayType &POWERADVANCE_YAXIS)
			DrawYAxis(cDC,fZoomRatio,ptOffset);
//	if(m_lAxisDrawStyle &POWERADVANCE_XAXIS)	////绘制X轴	
//		if(lDisplayType &POWERADVANCE_XAXIS)
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
	rect.left = cBorder.left;
	rect.top = cBorder.top ;
	rect.right = cBorder.right;
	rect.bottom = cBorder.top+iTopGap;
	
	CPoint ptCenter = rect.CenterPoint();
	rect.left = ptCenter.x - iLen;
	rect.right = ptCenter.x + iLen;
	
	rect.OffsetRect(ptOffset);
	
	char cName[128];
	lstrcpy(cName,m_strAxisTitle);
	CmDrawTextRect(pDC,(LPSTR)cName,m_crAxisTitleFont,&rect,RGB(0,0,0),
		lf,TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}

void CLogarithmAxis::DrawFrame(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect rect = cBorder;
	rect.OffsetRect(ptOffset);
	Draw3dRectBorder(pDC,&rect,m_iFrameShadow,m_crFrameLeftTopColor,m_crFrameRightBottomColor);
}
void CLogarithmAxis::ModifyWorkArea(CRect* cRect,BOOL bInit,float fZoomRatio,CPoint ptOffset)
{
	CRect cNewRect=cRect[0];
	MakeWorkAreaLegal(cNewRect);
	cBorder=cNewRect;

	cX_Axis.bottom=cNewRect.bottom-(long)(fZoomRatio*iBottomGap);
	cX_Axis.top=cX_Axis.bottom-(long)(fZoomRatio*iHorzAreaWidth);
	
	cWorkArea.bottom=cX_Axis.top;
	cWorkArea.top=cNewRect.top+(long)(fZoomRatio*iTopGap);
	
	cY_Axis.left=cNewRect.left+(long)(fZoomRatio*iLeftGap);
	cY_Axis.right=cY_Axis.left+(long)(fZoomRatio*iVertAreaWidth);

	cWorkArea.left=cY_Axis.right;
	cWorkArea.right=cNewRect.right-(long)(fZoomRatio*iRightGap);

	cX_Axis.left=cWorkArea.left;
	cX_Axis.right=cWorkArea.right;

	cY_Axis.top=cWorkArea.top;
	cY_Axis.bottom=cWorkArea.bottom;

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
	Draw3dRectBorder(pDC,&cR,iShadow,crBkLeftTopColor,crBkRightBottomColor);
}
void CLogarithmAxis::DrawArea(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CRect cR=GetDrawWorkAreaRect();
	cR.OffsetRect(ptOffset);
	Draw3dRectByMe(pDC,&cR,(long)(fZoomRatio*iShadow),crBkLeftTopColor,
				   crBkRightBottomColor,crBkGroundColor);
}
void CLogarithmAxis::DrawAxisBack(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	//绘制背景
	CBrush brush;
	brush.CreateSolidBrush(m_crAxisBackColor);
	pDC->FillRect(cBorder,&brush);
	brush.DeleteObject();
	
}
CRect CLogarithmAxis::GetDrawWorkAreaRect()
{
	CRect cR=cWorkArea;
	cR.bottom+=3;cR.right+=2;
	return cR;
}

void CLogarithmAxis::SetAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY)
{
	//对数坐标系
	m_iOldBeginPalace=iBeginPalace;
	m_iOldEndPalace=iEndPalace;
	m_iOldDisplayMinVal=iDisplayMinVal;
	m_iOldDisplayMaxVal=iDisplayMaxVal;
	iBeginPalace=dMinX;	
	iEndPalace=dMaxX;		
	iDisplayMinVal=dMinY;	
	iDisplayMaxVal=dMaxY;	
	
	ModifyWorkArea(&m_rectAxis,1);
	ResetYAxisDef();
	ResetXAxisDef();
	
}
long CLogarithmAxis::GetAxisMinMaxVal(double *dMinX,double *dMinY,double *dMaxX,double *dMaxY)
{
	*dMinX=iBeginPalace;
	*dMaxX=iEndPalace;
	*dMinY=iDisplayMinVal;
	*dMaxY=iDisplayMaxVal;
	
	return 0;
}
void CLogarithmAxis::SetBorder(CRect rectBorder)
{
	int iH=0,iW=0;
	iH=rectBorder.Height();
	iW=rectBorder.Width();
	iH=iH-iBottomGap-iTopGap-iHorzAreaWidth;
	iW=iW-iLeftGap-iRightGap-iVertAreaWidth;
	if(iW<=0)
		iW=20;
	if(iH<=0)
		iH=20;
	rectBorder.bottom=rectBorder.top+iH + iBottomGap + iTopGap + iHorzAreaWidth;
	rectBorder.right=rectBorder.left+iW + iLeftGap + iRightGap + iVertAreaWidth;
	
	if (m_bAxisXYUnitLock)
	{
		iH=rectBorder.Height();
		iW=rectBorder.Width();
		iH=iH-iBottomGap-iTopGap-iHorzAreaWidth;
		iW=iW-iLeftGap-iRightGap-iVertAreaWidth;
		
		double fCoef=0;//(float)iW/iH;
		double fVer = (m_iOldDisplayMaxVal - m_iOldDisplayMinVal) / iH;
		double fHor = (m_iOldEndPalace - m_iOldBeginPalace) / iW;
		if(fVer>fHor)
		{
			fCoef=fVer / fHor;
			iBeginPalace   = m_iOldBeginPalace*fCoef;
			iEndPalace     = m_iOldEndPalace * fCoef;
			iDisplayMinVal = m_iOldDisplayMinVal;
			iDisplayMaxVal = m_iOldDisplayMaxVal;
		}
		else
		{
			fCoef=fHor / fVer;
			iDisplayMinVal = m_iOldDisplayMinVal*fCoef;
			iDisplayMaxVal = m_iOldDisplayMaxVal*fCoef;
			iBeginPalace   = m_iOldBeginPalace;
			iEndPalace     = m_iOldEndPalace;
		}
	}
	
	ModifyWorkArea(&rectBorder,1);
	ResetYAxisDef();
	ResetXAxisDef();
	InitAxisAttr();
}
void CLogarithmAxis::ResetAxis()
{
	//i-t
/*
	m_fAxisValue[0]	= -0.2f;
	m_fAxisValue[1]	= 1.62f;
	m_fAxisValue[2] = -3.0f;
	m_fAxisValue[3] = 3.0f;
*/

	iBeginPalace=m_fAxisValue[0];
	iEndPalace=m_fAxisValue[1];
	iDisplayMinVal=m_fAxisValue[2];
	iDisplayMaxVal= m_fAxisValue[3];
	m_iOldBeginPalace=iBeginPalace;
	m_iOldEndPalace=iEndPalace;
	m_iOldDisplayMinVal=iDisplayMinVal;
	m_iOldDisplayMaxVal=iDisplayMaxVal;
	ResetXAxisDef();
	ResetYAxisDef();
	
}

void CLogarithmAxis::InitAxisAttr()
{
	CRect rectWork=cWorkArea;
	float fYValue=0,fXValue=0;
	float fYMaxValue=0,fYMinValue=0,fXMaxValue=0,fXMinValue=0;
	CPoint pointCenter=CPoint(0,0);
	fYMaxValue=iDisplayMaxVal;
	fYMinValue=iDisplayMinVal;
	int iHeight=rectWork.Height();
	float fValYOneGap=iHeight/(fYMaxValue-fYMinValue);///Y轴实际坐标与实际值的比率
	///////////////////////////////////////////////
	fXMaxValue=iEndPalace;
	fXMinValue=iBeginPalace;
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
	fMinX = iBeginPalace / fZoomIn;
	fMaxX = iEndPalace /fZoomIn;
	fMinY = iDisplayMinVal / fZoomIn;
	fMaxY = iDisplayMaxVal / fZoomIn;
	
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
	
	DevicePointToLogicPoint(ptLeftTop,&dMinX,&dMaxY);
	DevicePointToLogicPoint(ptRightBottom,&dMaxX,&dMinY);
	
	ZoomIn(dMinX,dMaxX,dMinY,dMaxY);
}

void CLogarithmAxis::ZoomOut(float fZoomOut)
{
	double fMinX=0,fMinY=0,fMaxX=0,fMaxY=0;
	fMinX = iBeginPalace * fZoomOut;
	fMaxX = iEndPalace * fZoomOut;
	fMinY = iDisplayMinVal * fZoomOut;
	fMaxY = iDisplayMaxVal * fZoomOut;
	
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
	iEndPalace     -= fXOffset * m_fXCarryOneGap;
	iBeginPalace   -= fXOffset * m_fXCarryOneGap;
	iDisplayMaxVal -= fYOffset * m_fYCarryOneGap;
	iDisplayMinVal -= fYOffset * m_fYCarryOneGap;
	
	ResetYAxisDef();
	ResetXAxisDef();
	InitAxisAttr();
}

////////////////////////////////////////////////////////////////////
void CLogarithmAxis::LogicPointToDevicePoint(float fx,float fy,CPoint *pPoint)
{
	//iYAxisOneGap		Y轴实际坐标与实际值的比率
	//iXAxisOneGap		X轴实际坐标与实际值的比率
	if(fx<0 || fy<0)return ;
	float fXVal=log10(fx);
	float fYVal=log10(fy);
	fXVal = cX_Axis.left+(fXVal-iBeginPalace)*iXAxisOneGap;
	fYVal = cY_Axis.bottom-(fYVal-iDisplayMinVal)*iYAxisOneGap;
	pPoint->x=FloatValToInt(fXVal);
	pPoint->y=FloatValToInt(fYVal);;
}
//从实际坐标获取实际坐标所代表的值
void CLogarithmAxis::DevicePointToLogicPoint(CPoint point,double *fx,double *fy)
{
	//iYAxisOneGap		Y轴实际坐标与实际值的比率
	//iXAxisOneGap		X轴实际坐标与实际值的比率
	double fXVal =iBeginPalace + ((double)point.x-(double)cX_Axis.left)/iXAxisOneGap;
	double fYVal =((double)cY_Axis.bottom-(double)point.y)/iYAxisOneGap + iDisplayMinVal;
	*fx=pow(10,fXVal);
	*fy=pow(10,fYVal);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) CLogarithmAxis::XLogarithmAxisInterface::AddRef()
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CLogarithmAxis::XLogarithmAxisInterface::Release()
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	return pThis->ExternalRelease();
}

STDMETHODIMP CLogarithmAxis::XLogarithmAxisInterface::QueryInterface(REFIID iid,LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisMinSawGapWidth(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->m_fOneXGapValue;
	
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisMinSawGapWidth(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->m_fOneXGapValue = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisMinSawGapHeight(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->m_fOneYGapValue;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisMinSawGapHeight(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->m_fOneYGapValue = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisType(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->m_lAxisType;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisType(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	 pThis->m_lAxisType = nValue;

	 return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisMaxUnitCount(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->m_lXAxisMaxUnitCount = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisMaxUnitCount(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->m_lXAxisMaxUnitCount;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisMaxUnitCount(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->m_lYAxisMaxUnitCount = nValue;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisMaxUnitCount(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->m_lYAxisMaxUnitCount;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisXYUnitLock(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->m_bAxisXYUnitLock = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetAxisXYUnitLock(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->m_bAxisXYUnitLock;

    return 0;
}

//坐标系统的绘制类型,2005.08.12添加
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisDrawStyle(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	
	pThis->m_lAxisDrawStyle = nValue;
	
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetAxisDrawStyle(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	
	*nValue = pThis->m_lAxisDrawStyle;
	
    return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisDrawStyleBit(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);

	pThis->m_lAxisDrawStyle |= nValue;
	
	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::ClearAxisDrawStyleBit(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);

	pThis->m_lAxisDrawStyle &= (~nValue);
	
	return 0;
}


STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisTextDrawStyle(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->lDrawXAxisTextType = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisTextDrawStyle(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->lDrawXAxisTextType;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisTitle(BSTR bstrValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
/*
	char pszValue[MAX_PATH];
	memset(pszValue,0,MAX_PATH);
	BSTRToAnsiStr(bstrValue,pszValue);*/

	pThis->m_strAxisTitle = bstrValue;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetAxisTitle(BSTR *pbstrValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CString sAxisTitle;
	sAxisTitle = pThis->m_strAxisTitle;
	*pbstrValue = sAxisTitle.AllocSysString();
	
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisTitleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT   m_lfAxisTitleFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfAxisTitleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet
		,(BYTE)lfOutPrecision,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->m_lfAxisTitleFont = m_lfAxisTitleFont;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetAxisTitleFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT m_lfAxisTitleFont;
	CString sFaceName;
	m_lfAxisTitleFont = pThis->m_lfAxisTitleFont;
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
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisTitleFontColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crTitleColor;
	m_crTitleColor = (COLORREF)nValue;
	pThis->m_crAxisTitleFont = m_crTitleColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetAxisTitleFontColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crAxisTitleFontColor;
	m_crAxisTitleFontColor = pThis->m_crAxisTitleFont;
	*nValue = (long)m_crAxisTitleFontColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisBackColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crBackColor;
	m_crBackColor = (COLORREF)nValue;
	pThis->m_crAxisBackColor = m_crBackColor;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetAxisBackColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crBackColor;
	m_crBackColor = pThis->m_crAxisBackColor;
    *nValue = (long)m_crBackColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetWorkAreaBkColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crBKColor;
	m_crBKColor = (COLORREF)nValue;
	pThis->crBkGroundColor = m_crBKColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetWorkAreaBkColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crBKColor;
	m_crBKColor = pThis->crBkGroundColor;
	*nValue = (long)m_crBKColor;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetWorkAreaBorderLeftTopColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = (COLORREF)nValue;
	pThis->crBkLeftTopColor = m_crLeftTopColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetWorkAreaBorderLeftTopColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crLeftTopColor;
	m_crLeftTopColor = pThis->crBkLeftTopColor;
	*nValue = (long)m_crLeftTopColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetWorkAreaBorderRightBottomColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crRightBottomColor;
	m_crRightBottomColor = (COLORREF)nValue;
	pThis->crBkRightBottomColor = m_crRightBottomColor;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetWorkAreaBorderRightBottomColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crRightBottomColor;
	m_crRightBottomColor = pThis->crBkRightBottomColor;
	*nValue = (long)m_crRightBottomColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetWorkAreaBorderShadow(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->iShadow = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetWorkAreaBorderShadow(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);

	*nValue = pThis->iShadow;

	return 0;
}

//坐标系统边框的颜色
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetFrameLeftTopColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->m_crFrameLeftTopColor = (COLORREF)nValue;
		
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetFrameLeftTopColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = (long)(pThis->m_crFrameLeftTopColor);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetFrameRightBottomColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->m_crFrameRightBottomColor = (COLORREF)nValue;
		
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetFrameRightBottomColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = (long)(pThis->m_crFrameRightBottomColor);
	
	return 0;
}

//坐标系统边框边界阴影
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetFrameShadow(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	
	pThis->m_iFrameShadow = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetFrameShadow(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	
	*nValue = pThis->m_iFrameShadow;

	return 0;
}


STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYUnitScaleColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYUnitScaleColor;
	m_crYUnitScaleColor = (COLORREF)nValue;
	pThis->m_crYUnitScaleColor = m_crYUnitScaleColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYUnitScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYUnitScaleColor;
	m_crYUnitScaleColor = pThis->m_crYUnitScaleColor;
	*nValue = (long)m_crYUnitScaleColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYUnitScaleShadowColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crShadowColor;
	m_crShadowColor = (COLORREF)nValue;
	pThis->m_crYUnitScaleShadowColor = m_crShadowColor;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYUnitScaleShadowColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crShadowColor;
	m_crShadowColor = pThis->m_crYUnitScaleShadowColor;
	*nValue = (long)m_crShadowColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT   m_lfYAxisScaleFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfYAxisScaleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->lfVertFont = m_lfYAxisScaleFont;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisScaleFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT m_lfYAxisScaleFont;
	CString sFaceName;
	m_lfYAxisScaleFont = pThis->lfVertFont;
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
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisName(BSTR bstrName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	char pszYAxisName[MAX_PATH];
	memset(pszYAxisName,0,MAX_PATH);
	BSTRToAnsiStr(bstrName,pszYAxisName);
	pThis->cYAxisName = bstrName;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisName(BSTR *pbstrName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CString sYAxisName;
	sYAxisName = pThis->cYAxisName;
	*pbstrName = sYAxisName.AllocSysString();

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT   m_lfAxisNameFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfAxisNameFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->lfVertTitleFont = m_lfAxisNameFont;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisNameFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT m_lfYAxisNameFont;
	CString sFaceName;
	m_lfYAxisNameFont = pThis->lfVertTitleFont;
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

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisNameFontColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYAxisNameFontColor;
	m_crYAxisNameFontColor = (COLORREF)nValue;
	pThis->crVertTitleColor = m_crYAxisNameFontColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisNameFontColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYAxisNameFontColor;
	m_crYAxisNameFontColor = pThis->crVertTitleColor;
	*nValue = (long)m_crYAxisNameFontColor;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisScaleFontColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYAxisScaleFontColor;
	m_crYAxisScaleFontColor = (COLORREF)nValue;
	pThis->crVertColor = m_crYAxisScaleFontColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisScaleFontColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYAxisScaleFontColor;
	m_crYAxisScaleFontColor = pThis->crVertColor;
	*nValue = (long)m_crYAxisScaleFontColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisGridLineStyle(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->m_lAxisGridLineType = nValue;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisGridLineStyle(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->m_lAxisGridLineType;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisGridLineColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYAxisGridLineColor;
	m_crYAxisGridLineColor = (COLORREF)nValue;
	pThis->m_crAxisGrid = m_crYAxisGridLineColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisGridLineColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYAxisGridLineColor;
	m_crYAxisGridLineColor = pThis->m_crAxisGrid;
	*nValue = (long)m_crYAxisGridLineColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisTenthScaleColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYAxisTenthScaleColor;
	m_crYAxisTenthScaleColor = (COLORREF)nValue;
	pThis->SetYAxisTenthScaleColor(m_crYAxisTenthScaleColor);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisTenthScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crYAxisTenthScaleColor;
	m_crYAxisTenthScaleColor = pThis->GetYAxisTenthScaleColor();
	*nValue = (long)m_crYAxisTenthScaleColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisAreaWidth(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->iVertAreaWidth = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisAreaWidth(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->iVertAreaWidth;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisUnitScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->iVertGapLineLen1 = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisUnitScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->iVertGapLineLen1;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisHalfScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->iVertGapLineLen2 = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisHalfScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->iVertGapLineLen2;
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetYAxisTenthScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->iVertGapLineLen3 = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisTenthScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->iVertGapLineLen3;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXUnitScaleColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXUnitScaleColor;
	m_crXUnitScaleColor = (COLORREF)nValue;
	pThis->m_crXUnitScaleColor = m_crXUnitScaleColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXUnitScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXUnitScaleColor;
	m_crXUnitScaleColor = pThis->m_crXUnitScaleColor;
	*nValue = (long)m_crXUnitScaleColor;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXUnitScaleShadowColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXUnitScaleShadowColor;
	m_crXUnitScaleShadowColor = (COLORREF)nValue;
	pThis->m_crXUnitScaleShadowColor = m_crXUnitScaleShadowColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXUnitScaleShadowColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXUnitScaleShadowColor;
	m_crXUnitScaleShadowColor = pThis->m_crXUnitScaleShadowColor;
	*nValue = (long)m_crXUnitScaleShadowColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT   m_lfXAxisScaleFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfXAxisScaleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->lfHorzFont = m_lfXAxisScaleFont;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisScaleFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT m_lfXAxisScaleFont;
	CString sFaceName;
	m_lfXAxisScaleFont = pThis->lfHorzFont;
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

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisName(BSTR bstrName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	char pszName[MAX_PATH];
	memset(pszName,0,MAX_PATH);
	BSTRToAnsiStr(bstrName,pszName);
	pThis->cXAxisName = pszName;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisName(BSTR *pbstrName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CString sXAxisName;
	sXAxisName = pThis->cXAxisName;
	*pbstrName = sXAxisName.AllocSysString();

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT   m_lfXAxisNameFont;
    char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfXAxisNameFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet,(BYTE)lfOutPrecision
		,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->lfHorzTitleFont = m_lfXAxisNameFont;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisNameFont(long FAR*lfHeight,long FAR*lfWidth,long FAR*lfEscapement,long FAR*lfOrientation,long FAR*lfWeight,long FAR*lfItalic,long FAR*lfUnderline,long FAR*lfStrikeOut,long FAR*lfCharSet,long FAR*lfOutPrecision,long FAR*lfClipPrecision,long FAR*lfQuality,long FAR*lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	LOGFONT m_lfXAxisNameFont;
	CString sFaceName;
	m_lfXAxisNameFont = pThis->lfHorzTitleFont;
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

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisNameFontColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXAxisNameFontColor;
	m_crXAxisNameFontColor = (COLORREF)nValue;
	pThis->crHorzTitleColor = m_crXAxisNameFontColor;

	return 0;
}
STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisNameFontColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface)
	COLORREF m_crXAxisNameFontColor;
	m_crXAxisNameFontColor = pThis->crHorzTitleColor;
	*nValue = (long)m_crXAxisNameFontColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisScaleFontColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXAxisScaleFontColor;
	m_crXAxisScaleFontColor = (COLORREF)nValue;
	pThis->crHorzColor = m_crXAxisScaleFontColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisScaleFontColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXAxisScaleFontColor;
	m_crXAxisScaleFontColor = pThis->crHorzColor;
	*nValue = (long)m_crXAxisScaleFontColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisGridLineStyle(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->m_lAxisGridLineType = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisGridLineStyle(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->m_lAxisGridLineType;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisGridLineColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXAxisGrid;
	m_crXAxisGrid = (COLORREF)nValue;
	pThis->m_crAxisGrid = m_crXAxisGrid;;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisGridLineColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXAxisGrid;
	m_crXAxisGrid = pThis->m_crAxisGrid;
	*nValue = (long)m_crXAxisGrid;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisTenthScaleColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXAxisTenthScaleColor;
	m_crXAxisTenthScaleColor = (COLORREF)nValue;
	pThis->SetXAxisTenthScaleColor(m_crXAxisTenthScaleColor);
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisTenthScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crXAxisTenthScaleColor;
	m_crXAxisTenthScaleColor = pThis->GetXAxisTenthScaleColr();
	*nValue = (long)m_crXAxisTenthScaleColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisAreaHeight(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->iHorzAreaWidth = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisAreaHeight(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->iHorzAreaWidth;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisUnitScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->iHorzGapLineLen1 = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisUnitScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->iHorzGapLineLen1;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisHalfScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->iHorzGapLineLen2 = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisHalfScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->iHorzGapLineLen2;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetXAxisTenthScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->iHorzGapLineLen3 = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisTenthScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->iHorzGapLineLen3;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisCenterLineWidth(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->lAxisCenterLineWidth = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetAxisCenterLineWidth(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->lAxisCenterLineWidth;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisCenterLineType(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->lAxisCenterLineType = nValue;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetAxisCenterLineType(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	*nValue = pThis->lAxisCenterLineType;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetAxisCenterColor(long nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crAxisCenterColor;
	m_crAxisCenterColor = (COLORREF)nValue;
	pThis->crAxisCenter = m_crAxisCenterColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetAxisCenterColor(long *nValue)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	COLORREF m_crAxisCenterColor;
	m_crAxisCenterColor = pThis->crAxisCenter;
	*nValue = (long)m_crAxisCenterColor;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::LogicPointToDevicePoint(double x,double y,long FAR*ptx,long FAR*pty)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CPoint *pPoint;
	*pPoint = CPoint(*ptx,*pty);
	pThis->LogicPointToDevicePoint(x,y,pPoint);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CPoint Point;
	Point = CPoint(ptx,pty);
	pThis->DevicePointToLogicPoint(Point,x,y);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetMinMaxVal(double xMin,double yMin,double xMax,double yMax,long nReserved)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->SetAxisMinMaxVal(xMin,yMin,xMax,yMax);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->GetAxisMinMaxVal(xMin,yMin,xMax,yMax);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::SetBoder(long left, long top, long right, long bottom)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CRect rectW;
	rectW = CRect(left, top, right, bottom);
	pThis->SetBorder(rectW);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetBoder(long FAR*left, long FAR*top, long FAR*right, long FAR*bottom)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CRect m_rectBoder;
	m_rectBoder = pThis->cBorder;
	*left = m_rectBoder.left;
	*top = m_rectBoder.top;
	*right = m_rectBoder.right;
	*bottom = m_rectBoder.bottom;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetWorkArea(long FAR*left, long FAR*top, long FAR*right, long FAR*bottom)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CRect rectWorkArea;
	rectWorkArea = pThis->cWorkArea;
	*left = rectWorkArea.left;
	*top = rectWorkArea.top;
	*right = rectWorkArea.right;
	*bottom = rectWorkArea.bottom;

	return 0;

}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetXAxisArea(long FAR*left, long FAR*top, long FAR*right, long FAR*bottom)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CRect rectXAxisArea;
	rectXAxisArea = pThis->cX_Axis;
	*left = rectXAxisArea.left;
	*top = rectXAxisArea.top;
	*right = rectXAxisArea.right;
	*bottom = rectXAxisArea.bottom;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::GetYAxisArea(long FAR*left, long FAR*top, long FAR*right, long FAR*bottom)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CRect rectYAxisArea;
	rectYAxisArea = pThis->cY_Axis;
	*left = rectYAxisArea.left;
	*top = rectYAxisArea.top;
	*right = rectYAxisArea.right;
	*bottom = rectYAxisArea.bottom;

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::ResetAxis()
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->ResetAxis();

	return 0;
}


STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::DrawAxis(long lDC,float fZoomRatio,long xOffset,long yOffset)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	CDC *pDC;
	pDC = (CDC*)lDC;
	CPoint ptOffset;
	ptOffset = CPoint(xOffset,yOffset);
	pThis->DrawIt(pDC,fZoomRatio,ptOffset);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::ZoomIn1(float fRate)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->ZoomIn(fRate);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::ZoomIn2(double dMinX,double dMaxX,double dMinY,double dMaxY)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->ZoomIn(dMinX, dMaxX, dMinY, dMaxY);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::ZoomIn3(long left,long top,long right,long bottom)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->ZoomIn(left,top,right,bottom);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::ZoomOut(float fRate)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->ZoomOut(fRate);

	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XLogarithmAxisInterface::Move(float fXOffset,float fYOffset)
{
	METHOD_PROLOGUE(CLogarithmAxis, LogarithmAxisInterface);
	pThis->Move(fXOffset,fYOffset);

	return 0;
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) CLogarithmAxis::XAxisBaseInterface::AddRef()
{
	METHOD_PROLOGUE(CLogarithmAxis, AxisBaseInterface);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CLogarithmAxis::XAxisBaseInterface::Release()
{
	METHOD_PROLOGUE(CLogarithmAxis, AxisBaseInterface);
	return pThis->ExternalRelease();
}

STDMETHODIMP CLogarithmAxis::XAxisBaseInterface::QueryInterface(REFIID iid,LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CLogarithmAxis, AxisBaseInterface);
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(long) CLogarithmAxis::XAxisBaseInterface::GetBoder(long *left, long *top, long *right, long *bottom)
{
	METHOD_PROLOGUE(CLogarithmAxis, AxisBaseInterface);
	CRect rectBorder;
	rectBorder = pThis->cBorder;
	*left = rectBorder.left;
	*top = rectBorder.top;
	*right = rectBorder.right;
	*bottom = rectBorder.bottom;
	
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XAxisBaseInterface::GetWorkArea(long *left, long *top, long *right, long *bottom)
{
	METHOD_PROLOGUE(CLogarithmAxis, AxisBaseInterface);
	CRect rectWorkArea;
	rectWorkArea = pThis->cWorkArea;
	*left = rectWorkArea.left;
	*top = rectWorkArea.top;
	*right = rectWorkArea.right;
	*bottom = rectWorkArea.bottom;
	
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XAxisBaseInterface::LogicPointToDevicePoint(double x,double y,long FAR*ptx,long FAR*pty)
{
	METHOD_PROLOGUE(CLogarithmAxis, AxisBaseInterface);
	CPoint pPoint = CPoint(*ptx,*pty); 
	pThis->LogicPointToDevicePoint(x,y,&pPoint);
	
	return 0;
}

STDMETHODIMP_(long) CLogarithmAxis::XAxisBaseInterface::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
{
	METHOD_PROLOGUE(CLogarithmAxis, AxisBaseInterface);
	CPoint pPoint = CPoint(ptx,pty); 
	pThis->DevicePointToLogicPoint(pPoint,x,y);
	
	return 0;
}


STDMETHODIMP_(long) CLogarithmAxis::XAxisBaseInterface::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
{
	METHOD_PROLOGUE(CLogarithmAxis, AxisBaseInterface);
	*xMin = pThis->iBeginPalace;
	*yMin = pThis->iDisplayMinVal;
	*xMax = pThis->iEndPalace;
	*yMax = pThis->iDisplayMaxVal;
	
	return 0;
}
