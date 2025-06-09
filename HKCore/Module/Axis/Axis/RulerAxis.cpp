// RulerAxis.cpp : implementation file
//

#include "stdafx.h"
#include "Axis.h"
#include "RulerAxis.h"
#include "..\..\Module\Api\GloblaDrawFunctions.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulerAxis

IMPLEMENT_DYNCREATE(CRulerAxis, CCmdTarget)

CRulerAxis::CRulerAxis()
{
	EnableAutomation();
	
	m_lDrawRulerTextType	=1;
	m_iBOTTOMADD	=2;
	m_iBigSawMinWidth	=30;
	m_iRulerHeight	=25;
	m_iRulerDirection		=0;
	m_lMaxRulerGapCount = 100;
	m_lDrawStyle = RULERDRAW_ALL;
	
	m_dOneHorGapValue	=1;
	m_iCenterLogInDv	=0;
	InitIt();
	
	m_posAxisData = NULL;
	m_nRulerType = 0;

	m_crFrameLeftTop = RGB(128,128,128);
	m_crFrameRightBottom = RGB(240,240,240);
	AfxOleLockApp();

}

CRulerAxis::~CRulerAxis()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CRulerAxis::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CRulerAxis, CCmdTarget)
	//{{AFX_MSG_MAP(CRulerAxis)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CRulerAxis, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CRulerAxis)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IRulerAxis to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {ABDD3E52-C6B2-4956-91A1-8DBFA846ECB3}
static const IID IID_IRulerAxis =
{ 0xabdd3e52, 0xc6b2, 0x4956, { 0x91, 0xa1, 0x8d, 0xbf, 0xa8, 0x46, 0xec, 0xb3 } };

BEGIN_INTERFACE_MAP(CRulerAxis, CCmdTarget)
	INTERFACE_PART(CRulerAxis, IID_IRulerAxis, Dispatch)
	INTERFACE_PART(CRulerAxis, IID_IRulerAxisInterface, RulerAxisInterface)
	INTERFACE_PART(CRulerAxis, IID_IAxisBaseInterface,AxisBaseInterface)
END_INTERFACE_MAP()

// {355D7CF1-ABC6-4743-833C-E0897B261020}
IMPLEMENT_OLECREATE(CRulerAxis, PROGID_IRulerAxis, 0x355d7cf1, 0xabc6, 0x4743, 0x83, 0x3c, 0xe0, 0x89, 0x7b, 0x26, 0x10, 0x20)

/////////////////////////////////////////////////////////////////////////////
// CRulerAxis message handlers
void CRulerAxis::InitIt()
{
	m_dVectorCoef=1;
	m_crSmallSaw = RGB(0,0,0);
	crShadowColor1=RGB(0,0,0);
	crShadowColor2=RGB(230,230,230);
	m_crRulerBackColor = GetSysColor(COLOR_3DFACE);//RGB(240,240,240);

	lfHorzFont=InitLogFont (-(int)(9*m_dVectorCoef),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
	lfHorzTitleFont=InitLogFont (-(int)(12*m_dVectorCoef),0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
	m_crHorzSawText=RGB(0,0,0);
	m_crHorzTitleColor=RGB(0,0,0);
	m_lFrameShadow=2;
	m_iHorBigSawLenLen	=(int)(10*m_dVectorCoef);
	m_iHorHalfSawLen	=(int)(8*m_dVectorCoef);
	m_iHorSmallSawLen	=(int)(5*m_dVectorCoef);
	m_dMaxZoomMultiple = 100.0;
	m_strRulerName = "";
	ContinueInit();
}

void CRulerAxis::ContinueInit()
{
	m_logpenSmallSaw=InitLogPen(PS_SOLID,1,m_crSmallSaw);
}

long CRulerAxis::GetBaseOneGapWidth()
{
	return m_iBigSawMinWidth;
}

long CRulerAxis::GetMinOneGapWidth()
{
	return m_iBigSawMinWidth;
}

////矢量图的比例参数
void CRulerAxis::SetVectorCoef(double dCoef)
{
	m_dVectorCoef=dCoef;
}
double CRulerAxis::GetVectorCoef()
{
	return m_dVectorCoef;
}

//标尺刻度标注的种类
void CRulerAxis::SetRulerSawTextType(int iType)
{
	m_lDrawRulerTextType=iType;
}
int CRulerAxis::GetRulerSawTextType()
{
	return m_lDrawRulerTextType;
}
//标尺的大刻度标注之间的间隔空间(宽度)最小值
void CRulerAxis::SetBigSawMinWidth(int iSawWidth)
{
	m_iBigSawMinWidth=iSawWidth;
}
int CRulerAxis::GetBigSawMinWidth()
{
	return m_iBigSawMinWidth;
}

//标尺的方向，0：标尺标注在下；	1：标尺标注在上
int CRulerAxis::GetRulerDirection()
{
	return m_iRulerDirection;
}
void CRulerAxis::SetRulerDirection(int iXAxisMinSawGapWidth)
{
	if (m_nRulerType == 0)
	{
		m_iRulerDirection=iXAxisMinSawGapWidth;
	}
	else
	{
		m_iRulerDirection=iXAxisMinSawGapWidth;
		if(m_iRulerDirection==1)
			lfHorzFont.lfEscapement=2700;
		else
			lfHorzFont.lfEscapement=900;
	}
}

//高度
void CRulerAxis::SetRulerHeight(int iXAxisMinSawGapWidth)
{
	m_iRulerHeight = iXAxisMinSawGapWidth;
}

int CRulerAxis::GetRulerHeight()
{
	return m_iRulerHeight;
}

long CRulerAxis::GetMaxRulerGapNum()
{
	return m_lMaxRulerGapCount;
}

void CRulerAxis::InitRulerDef()
{
	m_listRulerDef.EndIt();
}

void CRulerAxis::EndRulerDef()
{
	m_listRulerDef.EndIt();
}

long CRulerAxis::Get60CarryVal(int iVal)
{
	int iStep=6;
	int iStep1=60;
	if(iVal<iStep)return iStep;
	for (int i=1;;i++)
	{
		if((iVal>=iStep)&&(iVal<iStep1)) 
			return iStep;
		iStep=iStep1;iStep1*=10;
	}
}
double CRulerAxis::GetRulerBeginVal(double lNowVal,double lGapVal)
{
	double ff,ff1;
	int iMul=1;
	ff=lNowVal/lGapVal;
	ff1=(float)((int)ff);
	if(ff-ff1<0.99)	iMul=(int)ff1;
	else	iMul=(int)ff1+1;

	double fb=0;
	fb=lNowVal-(lNowVal - iMul*lGapVal);
	return fb;
}

void CRulerAxis::ResetRulerDef()
{
	EndRulerDef();
	int iOneGapPt=GetBaseOneGapWidth();//得到基本的一个Gap的间距
	int iWidth;
	if(m_nRulerType == 0)
	{
		iWidth=m_rectRuler.Width();//得到整个工作区域的高度
	}
	else
	{
		iWidth=m_rectRuler.Height();
		if(iWidth<10) return;
	}
	//得到需要计算数据的间隔
	double iVal=m_dHorMaxValue-m_dHorMinValue;
	
	double iGapNum=iWidth/iOneGapPt;
	int iGapNumTemp=0;
	iGapNumTemp=FloatValToInt(iGapNum);
	if(iGapNumTemp>GetMaxRulerGapNum())iGapNum=(float)GetMaxRulerGapNum();////获得最大间隔数
	double fVal=iVal/iGapNum;//得到每个间隔的数值
	if(iGapNum<=0.0001)return ;

	double iLegalGapVal=0;
	double iGapVal=0;
	int iCircleCounts=0;
	for(;iCircleCounts<50;iCircleCounts++)
	{
		iLegalGapVal=MakeFloatGapValLegal(fVal,iGapVal);//得到最可能的Mv数
		//if(iLegalGapVal>1) break;
		iGapNum=iVal/iGapVal;		////最大可能的间隔数
		iGapNumTemp=FloatValToInt(iGapNum);
		iGapNum=(float)iGapNumTemp ;
		int iNowGapPt=(int)(iWidth/iGapNum);	////最小可能的每个间隔值
		////最小可能的每个间隔值 < 允许的最小可能的间隔值
		if(iNowGapPt<GetMinOneGapWidth())
			iGapVal=iLegalGapVal;//得到最后的Mv数
		iGapNum=iVal/iGapVal;
		iGapNumTemp=FloatValToInt(iGapNum);
		iGapNum=(float)iGapNumTemp ;
		if(iGapNumTemp>GetMaxRulerGapNum())/////间隔数大于最大允许的间隔数
		{
			iGapVal=iLegalGapVal;
			if(iGapNumTemp>GetMaxRulerGapNum())
			{
				iGapNum=(float)GetMaxRulerGapNum();
				fVal=iLegalGapVal;
				continue;
			}
		}
		break;
	}	
//////////////////********************************************************************
//////////////////********************************************************************
//	if (fVal>=1)
	{
		iLegalGapVal=MakeFloatGapValLegal(fVal,iGapVal);//得到最可能的Mv数
		iGapNum=iVal/iGapVal;
		if (iGapNum==0)iGapNum=1;
		int iNowGapPt=(int)(iWidth/iGapNum);
		if (iNowGapPt==0)iNowGapPt=1;
		if(iNowGapPt<GetMinOneGapWidth())iGapVal=iLegalGapVal;//得到最后的Mv数
		iGapNum=iVal/iGapVal;
		iGapNumTemp=FloatValToInt(iGapNum);
		if(iGapNumTemp>GetMaxRulerGapNum())
		{
			iGapVal=iLegalGapVal;
			iGapNum=iVal/iGapVal;
			iGapNumTemp=FloatValToInt(iGapNum);
		}
		double iBeginVal=GetRulerBeginVal(m_dHorMinValue,iGapVal);
		GetOneRulerHorWidth(iGapVal,1);
		for (int i=0;i<=iGapNumTemp;i++)
			ResetOneRulerHorDef(iBeginVal+i*iGapVal);
	}
	m_dHorCarryOneGap=iGapVal;
	InitHorzRulerAttr();
}
void CRulerAxis::GetOneRulerHorWidth(double iGap,BYTE bKind)
{
	int iWidth = 0;
	if (m_nRulerType == 0)
	{
		iWidth = m_rectRuler.Width();
	}
	else
	{
		iWidth = m_rectRuler.Height();
	}
	double iVal=(m_dHorMaxValue-m_dHorMinValue);
	m_dRulerHorOneGap=iGap*(float)iWidth/iVal;
}

void CRulerAxis::ResetOneRulerHorDef(double lVal)
{
	int iWidth;
	double f;
	if(m_nRulerType == 0)
	{
		iWidth=m_rectRuler.Width();
	}
	else
	{
		iWidth=m_rectRuler.Height();
	}
	double iVal=(m_dHorMaxValue-m_dHorMinValue);//FloatValToInt
	if(m_nRulerType == 0)
	{
		f=m_rectRuler.left+(lVal-m_dHorMinValue)*(float)iWidth/iVal;
	}
	else
	{
		f=m_rectRuler.bottom-(lVal-m_dHorMinValue)*(float)iWidth/iVal;
	}
	int x=FloatValToInt(f);
	CAxisScaleData *pScaleData=new CAxisScaleData();
	int iIntegeralBeginPalace=0;//GetIntegeralBeginPalace();

	if(m_nRulerType == 0)
	{
		f=lVal-iIntegeralBeginPalace;
		if(m_iRulerDirection == 0)
			pScaleData->FillIt(f,CPoint(x,m_rectRuler.top+m_iBOTTOMADD));
		else
			pScaleData->FillIt(f,CPoint(x,m_rectRuler.bottom-m_iBOTTOMADD));
	}
	else
	{
			double f=lVal-iIntegeralBeginPalace;
			if(m_iRulerDirection==0)
				pScaleData->FillIt(f,CPoint(m_rectRuler.right-m_iBOTTOMADD,x));
			else
				pScaleData->FillIt(f,CPoint(m_rectRuler.left+m_iBOTTOMADD,x));
	}
	m_listRulerDef.AddTail(pScaleData);
}

CAxisScaleData* CRulerAxis::GetFirstAxisData()
{
	m_posAxisData = m_listRulerDef.GetHeadPosition();
	CAxisScaleData *pAxisData = NULL;
	if (m_posAxisData != NULL)
	{
		pAxisData = (CAxisScaleData*)m_listRulerDef.GetAt(m_posAxisData);
	}
	return pAxisData;
}

CAxisScaleData* CRulerAxis::GetNextAxisData()
{
	CAxisScaleData *pAxisData = NULL;
	if (m_posAxisData != NULL)
	{
		m_listRulerDef.GetNext(m_posAxisData);
		if (m_posAxisData != NULL)
			pAxisData = (CAxisScaleData*)m_listRulerDef.GetAt(m_posAxisData);
	}
	return pAxisData;
}

void CRulerAxis::DrawRulerHorLine(CDC *pDC,CAxisScaleData *pScaleData)
{
	pDC->MoveTo(CPoint(pScaleData->m_ptAxisScale.x,m_rectRuler.top+m_lFrameShadow));
	pDC->LineTo(CPoint(pScaleData->m_ptAxisScale.x,m_rectRuler.bottom+m_iBOTTOMADD));
}

CRect  CRulerAxis::DrawRulerHorText(CDC *pDC,CAxisScaleData *pScaleData,BOOL bAddUint,BOOL bReallyDraw)
{
	char cStr[128];
	sprintf(cStr,"%.4f",pScaleData->m_dAxisScaleVal);
	int iLen=strlen(cStr);
	double f=0;
	if(cStr[iLen-1]>='5')
	{
		cStr[iLen-1]=0;
		f=atof(cStr);
		if(f>=0.0001)f=f+0.001;
		else f=f-0.001;
		sprintf(cStr,"%.4f",f);
	}		
	chop(cStr);

	if(m_nRulerType == 0)
	{
		if(bAddUint==TRUE)
			lstrcat(cStr,m_strRulerName);
		CRect cR1;
		cR1.left	=pScaleData->m_ptAxisScale.x-(int)(20*m_dVectorCoef);
		cR1.right	=pScaleData->m_ptAxisScale.x+(int)(24*m_dVectorCoef);
		if(m_iRulerDirection==0)
		{
			cR1.top		=pScaleData->m_ptAxisScale.y+(int)(7*m_dVectorCoef);
			cR1.bottom	=pScaleData->m_ptAxisScale.y+(int)(20*m_dVectorCoef);
		}
		else
		{
			cR1.bottom	=pScaleData->m_ptAxisScale.y-(int)(7*m_dVectorCoef);
			cR1.top		=pScaleData->m_ptAxisScale.y-(int)(20*m_dVectorCoef);
		}
		CRect cR;

		if(m_lDrawRulerTextType==1)
		{
			cR.left		=pScaleData->m_ptAxisScale.x-cR1.Width()/2-(int)(2*m_dVectorCoef);
			cR.right	=pScaleData->m_ptAxisScale.x+cR1.Width()/2+(int)(2*m_dVectorCoef);
			if(m_iRulerDirection==0)
			{
				cR.top		=pScaleData->m_ptAxisScale.y+m_iHorBigSawLenLen;
				cR.bottom	=pScaleData->m_ptAxisScale.y+m_iHorBigSawLenLen+cR1.Height();;
			}
			else
			{
				cR.bottom	=pScaleData->m_ptAxisScale.y-m_iHorBigSawLenLen;
				cR.top		=pScaleData->m_ptAxisScale.y-m_iHorBigSawLenLen-cR1.Height();;
			}
			if(bReallyDraw)
				CmDrawTextRect(pDC,cStr,m_crHorzSawText,cR,RGB(0,0,0),lfHorzFont,TRANSPARENT,DT_VCENTER|DT_CENTER,0);
		}
		else
		{
			cR.left		=pScaleData->m_ptAxisScale.x+(int)(3*m_dVectorCoef);
			cR.right	=pScaleData->m_ptAxisScale.x+cR1.Width()+(int)(2*m_dVectorCoef);
			if(m_iRulerDirection==0)
			{
				cR.top		=pScaleData->m_ptAxisScale.y+m_iHorSmallSawLen;
				cR.bottom	=pScaleData->m_ptAxisScale.y+m_iHorBigSawLenLen+cR1.Height();
			}
			else
			{
				cR.bottom	=pScaleData->m_ptAxisScale.y-m_iHorSmallSawLen;
				cR.top		=cR.bottom-cR1.Height();
			}
			if(bReallyDraw)
				CmDrawTextRect(pDC,cStr,m_crHorzSawText,cR,RGB(0,0,0),lfHorzFont,TRANSPARENT,0,0);
		}
		return cR;
	}
	else
	{
		long lHeight=(long)fabs(lfHorzFont.lfHeight*m_dVectorCoef);
		CRect rect;
		int iStrLen=strlen(cStr) ;
		float fStrLen=(float)iStrLen / 2;
		
		int iCharWidth=5;
		
		if(m_iRulerDirection==0)
		{
			rect.left	=pScaleData->m_ptAxisScale.x-(int)(20*m_dVectorCoef);
			rect.right	=pScaleData->m_ptAxisScale.x-(int)(7*m_dVectorCoef);
			rect.bottom	=pScaleData->m_ptAxisScale.y-(int)(iCharWidth*fStrLen*m_dVectorCoef);
			rect.top	=pScaleData->m_ptAxisScale.y+(int)(iCharWidth*fStrLen*m_dVectorCoef);
		}
		else
		{
			rect.left	=pScaleData->m_ptAxisScale.x+(int)(20*m_dVectorCoef);
			rect.right	=pScaleData->m_ptAxisScale.x+(int)(7*m_dVectorCoef);
			rect.top	=pScaleData->m_ptAxisScale.y-(int)(iCharWidth*fStrLen*m_dVectorCoef);
			rect.bottom	=pScaleData->m_ptAxisScale.y+(int)(iCharWidth*fStrLen*m_dVectorCoef);
		}
		
		
		CmDrawTextRect(pDC,cStr,m_crHorzSawText,&rect,RGB(0,0,0),
			lfHorzFont,TRANSPARENT,DT_NOCLIP,0);
		return rect;
	}
}
void CRulerAxis::DrawRulerHorName(CDC *pDC)
{
	int iLen=m_strRulerName.GetLength();
	CFont CF;
	CF.CreateFontIndirect(&lfHorzTitleFont);
	CFont *c=pDC->SelectObject(&CF);
	TEXTMETRIC textMetric;
	pDC->GetTextMetrics(&textMetric);
	pDC->SelectObject(c);
	iLen=textMetric.tmAveCharWidth *(iLen+1);

	CRect cR;
	cR.left=m_rectRuler.right-iLen;
	cR.top=m_rectRuler.bottom-5*m_dVectorCoef;
	cR.right= m_rectRuler.right;
	cR.bottom=m_rectRuler.bottom+5;
	char cName[128];
	lstrcpy(cName,m_strRulerName);
	CmDrawTextRect(pDC,(LPSTR)cName,m_crHorzTitleColor,&cR,RGB(0,0,0),
				   lfHorzTitleFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);

}
void CRulerAxis::DrawRulerHorFrame(CDC*pDC)
{
	CPoint ptTopLeft=m_rectRuler.TopLeft();
	CPoint ptRightBottom=m_rectRuler.BottomRight();
	CPen cP1(PS_SOLID,1,m_crFrameLeftTop);
	CPen cP2(PS_SOLID,1,m_crFrameRightBottom);
	if(m_nRulerType == 0)
	{
		for(int i=0;i<m_lFrameShadow;i++)
		{
			DrawLine(pDC,ptTopLeft.x+i,ptTopLeft.y+i,ptRightBottom.x-i,ptTopLeft.y+i,&cP1,FALSE);
	 		DrawLine(pDC,ptTopLeft.x+i,ptRightBottom.y-i,ptRightBottom.x-i,ptRightBottom.y-i,&cP2,FALSE);		
			//	pDC->MoveTo(ptTopLeft);	pDC->LineTo(ptRightBottom.x,ptTopLeft.y);
			//	pDC->MoveTo(ptTopLeft.x,ptRightBottom.y);	pDC->LineTo(ptRightBottom);
		}
	}
	else
	{
		for(int i=0;i<m_lFrameShadow;i++)
		{
			DrawLine(pDC,ptTopLeft.x+i,ptTopLeft.y+i,ptTopLeft.x+i,ptRightBottom.y-i,&cP1,FALSE);
			DrawLine(pDC,ptRightBottom.x-i,ptTopLeft.y+i,ptRightBottom.x-i,ptRightBottom.y-i,&cP2,FALSE);
			//	pDC->MoveTo(ptTopLeft);	pDC->LineTo(ptTopLeft.x,ptRightBottom.y);
			//	pDC->MoveTo(ptRightBottom.x,ptTopLeft.y);	pDC->LineTo(ptRightBottom);
		}
	}
	cP1.DeleteObject();
	cP2.DeleteObject();
}

void CRulerAxis::DrawRulerBack(CDC *pDC)
{
	//绘制背景
	CBrush brush;
	brush.CreateSolidBrush(m_crRulerBackColor);
	pDC->FillRect(m_rectRuler,&brush);
	brush.DeleteObject();
}

void CRulerAxis::DrawRulerHor(CDC *pDC)
{
	int iNum=m_listRulerDef.GetCount();
	if(iNum<=0)return;
	if(m_nRulerType == 0)
	{
		if(m_lDrawStyle & RULERDRAW_SCALETEXT)
		{
			int iStep=iNum;
			for (int i=0;i<iNum;i++)
			{
				CAxisScaleData *pScaleData=(CAxisScaleData*)m_listRulerDef.GetAt(m_listRulerDef.FindIndex(i));
			//	CRect cR=DrawRulerHorText(pDC,pScaleData,FALSE,FALSE);
			}
			BOOL bDrawUint=FALSE;
			for (i=0;i<iStep;i++)
			{
				CAxisScaleData *pScaleData=(CAxisScaleData*)m_listRulerDef.GetAt(m_listRulerDef.FindIndex(i));
				if(i==iStep-1)
				{
				//	if(cEndIntegerRect.left==-1) 
						//bDrawUint=TRUE;
				}
				if(pScaleData->m_ptAxisScale.x<m_rectRuler.left || pScaleData->m_ptAxisScale.x>m_rectRuler.right) 
					continue;
				DrawRulerHorText(pDC,pScaleData,bDrawUint,TRUE);
			}
		}
	}
	else
	{
		CPen cP;
		long lGap=(long)fabs(lfHorzFont.lfHeight*m_dVectorCoef);
		cP.CreatePenIndirect(&m_logpenSmallSaw);
		CPen *cOldP=pDC->SelectObject(&cP);
		for (int i=0;i<iNum;i++)
		{
			CAxisScaleData *pScaleData=(CAxisScaleData*)m_listRulerDef.GetAt(m_listRulerDef.FindIndex(i));
			if( m_lDrawStyle & RULERDRAW_SCALETEXT)
			{
				if(pScaleData->m_ptAxisScale.y>=m_rectRuler.top && pScaleData->m_ptAxisScale.y<=m_rectRuler.bottom)
					DrawRulerHorText(pDC,pScaleData,FALSE,FALSE);////标注
			}
		}
		pDC->SelectObject(cOldP);
		cP.DeleteObject();
	}
		
	if(m_lDrawStyle & RULERDRAW_HALFSCCALE)
		DrawRulerHorSawtooth(pDC,0);
	if(m_lDrawStyle & RULERDRAW_TENTHSCALE)
		DrawRulerHorSawtooth(pDC,1);
		
		DrawRulerHorName(pDC);
	
}

void CRulerAxis::DrawOneRulerHorSawtooth(CDC *pDC,CPoint cBegin,CPoint cEnd)
{
	CPen cP;
	cP.CreatePenIndirect(&m_logpenSmallSaw);
	CPen *pOldPen=pDC->SelectObject(&cP);
	for (int i=0;i<10;i++)
	{
		int iGapVal=GetIntVal((float)((float)m_dRulerHorOneGap/10.0*i));
		if(m_nRulerType == 0)
		{
			CPoint cPt(cBegin.x+iGapVal,cBegin.y);
			if((cPt.x<m_rectRuler.left)||(cPt.x>m_rectRuler.right)) continue;
			pDC->MoveTo(cPt.x,cPt.y+1);
			if(m_iRulerDirection==0)
			{
				pDC->MoveTo(cPt.x,cPt.y+1);
				pDC->LineTo(cPt.x,cPt.y+m_iHorSmallSawLen);
			}
			else
			{
				pDC->MoveTo(cPt.x,cPt.y-1);
				pDC->LineTo(cPt.x,cPt.y-m_iHorSmallSawLen);
			}
		}
		else
		{
			CPoint cPt(cBegin.x,cBegin.y-iGapVal);
			if((cPt.y<m_rectRuler.top)||(cPt.y>m_rectRuler.bottom))
				continue;
			if(m_iRulerDirection==0)
			{
				pDC->MoveTo(cPt.x-1,cPt.y);
				pDC->LineTo(cPt.x-m_iHorSmallSawLen,cPt.y);
			}
			else
			{
				pDC->MoveTo(cPt.x+1,cPt.y);
				pDC->LineTo(cPt.x+m_iHorSmallSawLen,cPt.y);
			}
		}
	}
		pDC->SelectObject(pOldPen);
		cP.DeleteObject();
}
void CRulerAxis::DrawOneRulerHorSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd)
{
	int iLen[2]={m_iHorBigSawLenLen,m_iHorHalfSawLen};
	if(m_nRulerType == 0)
	{
		for (int i=0;i<2;i++)
		{
			int iGapVal=GetIntVal((float)((float)m_dRulerHorOneGap/2.0*i));
			CPoint cPt(cBegin.x+iGapVal,cBegin.y);
			if((cPt.x<m_rectRuler.left)||(cPt.x>m_rectRuler.right)) continue;
			if(m_iRulerDirection==0)
				DrawRulerShadowVertLine(pDC,cPt.x,cPt.y,iLen[i],crShadowColor1,crShadowColor2);
			else
				DrawRulerShadowVertLine(pDC,cPt.x,cPt.y,-iLen[i],crShadowColor1,crShadowColor2);
		}
	}
	else
	{
		for (int i=0;i<2;i++)
		{
			int iGapVal=GetIntVal((float)((float)m_dRulerHorOneGap/2.0*i));
			CPoint cPt(cBegin.x,cBegin.y-iGapVal);
			if((cPt.y<m_rectRuler.top)||(cPt.y>m_rectRuler.bottom))	continue;
			DrawRulerShadowVertLine(pDC,cPt.x,cPt.y,iLen[i],crShadowColor1,crShadowColor2);
		}
	}
}
void CRulerAxis::DrawLine(CDC *pDC,int left,int top,int right,int bottom,CPen *cP,BOOL bDel)
{
	CPen *cOldB=pDC->SelectObject(cP);
	pDC->MoveTo(left,top);
	pDC->LineTo(right,bottom);
	pDC->SelectObject(cOldB);
	if(bDel)cP->DeleteObject();
}
void CRulerAxis::DrawRulerShadowVertLine(CDC *pDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2)
{
	CPen cP(PS_SOLID,1,crColor1);
	CPen cP1(PS_SOLID,1,crColor2);
	if(m_nRulerType == 0)
	{
		DrawLine(pDC,iLeft,iTop,iLeft,iTop+iLen,&cP,TRUE);
		if(m_iRulerDirection==0)
			DrawLine(pDC,iLeft+1,iTop+2,iLeft+1,iTop+iLen,&cP1,TRUE);
		else
			DrawLine(pDC,iLeft+1,iTop-2,iLeft+1,iTop+iLen,&cP1,TRUE);
	}
	else
	{
		if(m_iRulerDirection==0)
		{
			DrawLine(pDC,iLeft,iTop,iLeft-iLen,iTop,&cP,TRUE);
			DrawLine(pDC,iLeft,iTop+1,iLeft-iLen+2,iTop+1,&cP1,TRUE);
		}
		else
		{
			DrawLine(pDC,iLeft,iTop,iLeft+iLen,iTop,&cP,TRUE);
			DrawLine(pDC,iLeft,iTop+1,iLeft+iLen-2,iTop+1,&cP1,TRUE);
		}
	}
}

void CRulerAxis::DrawRulerHorSawtooth(CDC *pDC,BYTE bKind)
{
	CPoint cBegin,cEnd;
	for (int i=0;i<m_listRulerDef.GetCount();i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listRulerDef.GetAt(m_listRulerDef.FindIndex(i));
		if (i==0)
		{
			if(m_nRulerType == 0)
			{
				cBegin=CPoint((int)(pScaleData->m_ptAxisScale.x-m_dRulerHorOneGap),pScaleData->m_ptAxisScale.y);
				cEnd=pScaleData->m_ptAxisScale;
			}
			else
			{
				cBegin=CPoint(pScaleData->m_ptAxisScale.x,(int)(pScaleData->m_ptAxisScale.y+m_dRulerHorOneGap));
				cEnd=pScaleData->m_ptAxisScale;
				{
					CPen cP;
					cP.CreatePenIndirect(&m_logpenSmallSaw);
					CPen *cOldP=pDC->SelectObject(&cP);
					for (int i=0;i<10;i++)
					{
						int iGapVal=GetIntVal((float)((float)m_dRulerHorOneGap/10.0*i));
						CPoint cPt(cBegin.x,cEnd.y+iGapVal);
						if((cPt.y<m_rectRuler.top)||(cPt.y>m_rectRuler.bottom))
							continue;
						if(m_iRulerDirection==0)
						{
							pDC->MoveTo(cPt.x-1,cPt.y);
							pDC->LineTo(cPt.x-m_iHorSmallSawLen,cPt.y);
						}
						else
						{
							pDC->MoveTo(cPt.x+1,cPt.y);
							pDC->LineTo(cPt.x+m_iHorSmallSawLen,cPt.y);
						}
					}
					pDC->SelectObject(cOldP);
					cP.DeleteObject();
					continue;
				}
			}
		}
		else 
		{
				CAxisScaleData *odNewData=(CAxisScaleData *)m_listRulerDef.GetAt(m_listRulerDef.FindIndex(i-1));
				cBegin=odNewData->m_ptAxisScale;
				cEnd=pScaleData->m_ptAxisScale;
		}	
		if (bKind==0)
			DrawOneRulerHorSawtooth(pDC,cBegin,cEnd);
		else 
			DrawOneRulerHorSawtoothShadow(pDC,cBegin,cEnd);
	}
	if(m_listRulerDef.GetCount()>=2)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listRulerDef.GetTail();
		if(m_nRulerType == 0)
		{
			cEnd=CPoint((int)(pScaleData->m_ptAxisScale.x+m_dRulerHorOneGap),pScaleData->m_ptAxisScale.y);
		}
		else
		{
			cEnd=CPoint(pScaleData->m_ptAxisScale.x,(int)(pScaleData->m_ptAxisScale.y-m_dRulerHorOneGap));
		}
		cBegin=pScaleData->m_ptAxisScale;
		if (bKind==0)
			DrawOneRulerHorSawtooth(pDC,cBegin,cEnd);
		else 
			DrawOneRulerHorSawtoothShadow(pDC,cBegin,cEnd);
	}
}

void CRulerAxis::DrawIt(CDC *pDC)
{
	DrawRulerBack(pDC);
	if(RULERDRAW_BODER & m_lDrawStyle)
		DrawRulerHorFrame(pDC);

	DrawRulerHor(pDC);
}
double CRulerAxis::MakeFloatGapValLegal(double fVal,double &lVal)
{
	double fTmp=fVal;
	if(fTmp<=0.0001)
	{
		fVal=fTmp;
		return fTmp;
	}
	double fMulti=GetFloatCarryVal(fTmp);///进位数值
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
double CRulerAxis::GetFloatCarryVal(double fVal)
{
	double fStep=0.0001;
	double fStep1=fStep*10;
	for (int i=1;;i++)
	{
		if((fVal>=fStep)&&(fVal<fStep1)) 
			return fStep;
		fStep=fStep1;
		fStep1*=10;
	}
}

//##########################################################################
//定义水平标尺的区域、做标值范围相关成员及函数
void CRulerAxis::ModifyRulerArea(CRect rectRuler)
{
	m_rectRuler=rectRuler;
	if(m_nRulerType == 0)
	{
		m_rectRuler.bottom=m_rectRuler.top+m_iRulerHeight;
	}
	else
	{
		m_rectRuler.right=m_rectRuler.left+m_iRulerHeight;
	}
	ResetRulerDef();
}

CRect CRulerAxis::GetRulerArea()
{
	return m_rectRuler;
}

void CRulerAxis::GetRulerMaxMinValue(double *dMinValue,double *dMaxValue)
{
	*dMinValue	=m_dHorMinValue;
	*dMaxValue	=m_dHorMaxValue;
}

void CRulerAxis::SetRulerMaxMinValue(double dMinValue,double dMaxValue)
{
	m_dHorMinValue	=dMinValue;
	m_dHorMaxValue	=dMaxValue;
	ResetRulerDef();
}

double CRulerAxis::GetHorCarryOenGap()
{
	return m_dHorCarryOneGap;
}

//##################################################3
//逻辑坐标与实际坐标的转化
void CRulerAxis::InitHorzRulerAttr()
{
	CRect rectWork=m_rectRuler;
	double fXValue=0;
	double fXMaxValue=0,fXMinValue=0;

	CPoint pointCenter=CPoint(0,0);
	fXMaxValue=m_dHorMaxValue;
	fXMinValue=m_dHorMinValue;

	int iWidth;
	double f;
	if(m_nRulerType == 0)
	{
		iWidth=rectWork.Width();
	}
	else
	{
		iWidth=rectWork.Height();
	}
	double fValXOneGap=iWidth/(fXMaxValue-fXMinValue);//X轴实际坐标与实际值的比率
	/////坐标原点在屏幕上的位置
	if(m_nRulerType == 0)
	{
		f=rectWork.left + (0-fXMinValue)*fValXOneGap;
	}
	else
	{
		f=rectWork.top + (0-fXMinValue)*fValXOneGap;
	}

	m_iCenterLogInDv	=FloatValToInt(f);
	m_dOneHorGapValue	=fValXOneGap;
}

void CRulerAxis::SetBorder(long left,long top,long right,long bottom)
{
	CRect rectBorder;
	rectBorder = CRect(left,top,right,bottom);
	ModifyRulerArea(rectBorder);
}

void CRulerAxis::ZoomIn(float fRate)
{
	double fMinValue=0,fMaxValue=0;
	fMinValue = m_dHorMinValue / fRate;
	fMaxValue = m_dHorMaxValue / fRate;
	m_dHorOldMinValue = m_dHorMinValue;
	m_dHorOldMaxValue = m_dHorMaxValue;
	
	double fLen=fabs(fMinValue-fMaxValue);

	double fCoef=0;
	
	fCoef= (m_dHorOldMinValue - m_dHorOldMaxValue) / (fMaxValue-fMinValue);
	
	fCoef=fabs(fCoef);
	if(fCoef>m_dMaxZoomMultiple)
		return;
	
	m_dHorMinValue = fMinValue;
	m_dHorMaxValue = fMaxValue;
	ResetRulerDef();	
}

void CRulerAxis::ZoomOut(float fRate)
{
	double fMinValue=0,fMaxValue=0;
	fMinValue = m_dHorMinValue * fRate;
	fMaxValue = m_dHorMaxValue * fRate;
	m_dHorOldMinValue = m_dHorMinValue;
	m_dHorOldMaxValue = m_dHorMaxValue;
	
	double fLen=fabs(fMinValue-fMaxValue);
	
	double fCoef=0;
	
	fCoef=(fMaxValue-fMinValue) / (m_dHorOldMaxValue - m_dHorOldMinValue);
	
	fCoef=fabs(fCoef);
	if(fCoef>m_dMaxZoomMultiple)
		return;
	
	m_dHorMinValue = fMinValue;
	m_dHorMaxValue = fMaxValue;
	ResetRulerDef();
}

void CRulerAxis::Move(float fOffset)
{
	m_dHorMaxValue -= fOffset * m_dHorCarryOneGap;
	m_dHorMinValue -= fOffset * m_dHorCarryOneGap;
	
	ResetRulerDef();
	InitHorzRulerAttr();
}

CRect CRulerAxis::GetBorder()
{
	return m_rectRuler;
}

//将逻辑坐标转化为实际坐标
void CRulerAxis::LogicPointToDevicePoint(double fx,long *iX)
{
	double f=fx*m_dOneHorGapValue+m_iCenterLogInDv;
	*iX=FloatValToInt(f);
}
//从实际坐标获取实际坐标所代表的值
void CRulerAxis::DevicePointToLogicPoint(long iX,double *dX)
{
	*dX=(iX-m_iCenterLogInDv) / m_dOneHorGapValue;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


STDMETHODIMP_(ULONG) CRulerAxis::XRulerAxisInterface::AddRef()
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CRulerAxis::XRulerAxisInterface::Release()
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	return pThis->ExternalRelease();
}

STDMETHODIMP CRulerAxis::XRulerAxisInterface::QueryInterface(REFIID iid,LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetMinSawGapWidth(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue	= pThis->GetMinOneGapWidth();

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetMinSawGapWidth(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_iBigSawMinWidth = nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerType(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = pThis->m_nRulerType;

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerType(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_nRulerType = nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetMaxUnitCount(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_lMaxRulerGapCount = nValue;
	
	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetMaxUnitCount(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = pThis->m_lMaxRulerGapCount;

	 return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetDrawStyle(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_lDrawStyle = nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetDrawStyle(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = pThis->m_lDrawStyle;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetDrawStyleBit(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_lDrawStyle |= nValue;

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::ClearDrawStyleBit(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_lDrawStyle &= (~nValue);

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetScaleTextDrawStyle(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->SetRulerSawTextType(nValue);

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetScaleTextDrawStyle(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = pThis->GetRulerSawTextType();

    return 0;
}

//坐标系统的绘制类型,2005.08.12添加
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerTitle(BSTR bstrValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
/*
	char pszRulerTitle[MAX_PATH];
	memset(pszRulerTitle,0,MAX_PATH);
	BSTRToAnsiStr(bstrValue,pszRulerTitle);*/

	pThis->m_strRulerName = bstrValue;
	
	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerTitle(BSTR *pbstrValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	CString strRulerTitle;
	strRulerTitle = pThis->m_strRulerName;
	*pbstrValue = strRulerTitle.AllocSysString();	
	
    return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerTitleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	LOGFONT   m_lfRulerTitleFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	m_lfRulerTitleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet
		,(BYTE)lfOutPrecision,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->lfHorzTitleFont = m_lfRulerTitleFont;
	
	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerTitleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	LOGFONT m_lfRulerTitleFont;
	CString sFaceName;
	m_lfRulerTitleFont = pThis->lfHorzTitleFont;
	*lfHeight = m_lfRulerTitleFont.lfHeight;
	*lfWidth = m_lfRulerTitleFont.lfWidth;
	*lfOrientation = m_lfRulerTitleFont.lfOrientation;
	*lfWeight = m_lfRulerTitleFont.lfWeight;
	*lfItalic = (long)m_lfRulerTitleFont.lfItalic;
	*lfUnderline = (long)m_lfRulerTitleFont.lfUnderline;
	*lfStrikeOut = (long)m_lfRulerTitleFont.lfStrikeOut;
	*lfCharSet = (long)m_lfRulerTitleFont.lfCharSet;
	*lfOutPrecision = (long)m_lfRulerTitleFont.lfOutPrecision;
	*lfClipPrecision = (long)m_lfRulerTitleFont.lfClipPrecision;
	*lfQuality = (long)m_lfRulerTitleFont.lfQuality;
	*lfPitchAndFamily = (long)m_lfRulerTitleFont.lfPitchAndFamily;
	sFaceName = m_lfRulerTitleFont.lfFaceName;
	*lfFaceName = sFaceName.AllocSysString();
	
	return 0;
}


STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerTitleFontColor(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_crHorzTitleColor = (COLORREF)nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerTitleFontColor(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = (long)pThis->m_crHorzTitleColor;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerBackColor(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_crRulerBackColor = (COLORREF)nValue;

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerBackColor(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = (long)pThis->m_crRulerBackColor;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetFrameLeftTopColor(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_crFrameLeftTop = (COLORREF)nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetFrameLeftTopColor(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = (long)pThis->m_crFrameLeftTop;

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetFrameRightBottomColor(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_crFrameRightBottom = (COLORREF)nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetFrameRightBottomColor(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = (long)pThis->m_crFrameRightBottom;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetFrameShadow(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_lFrameShadow = nValue;

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetFrameShadow(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = pThis->m_lFrameShadow;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetUnitScaleColor(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->crShadowColor1 = (COLORREF)nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetUnitScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = (long)pThis->crShadowColor1;

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetUnitScaleShadowColor(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->crShadowColor2 = (COLORREF)nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetUnitScaleShadowColor(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = (long)pThis->crShadowColor2;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	LOGFONT lfRulerScaleFont;
	char pszFaceName[MAX_PATH];
	memset(pszFaceName,0,MAX_PATH);
	BSTRToAnsiStr(lfFaceName,pszFaceName);
	lfRulerScaleFont = InitLogFont (lfHeight,lfWidth,lfEscapement,lfOrientation
		,lfWeight,(BYTE)lfItalic,(BYTE)lfUnderline,(BYTE)lfStrikeOut,(BYTE)lfCharSet
		,(BYTE)lfOutPrecision,(BYTE)lfClipPrecision,(BYTE)lfQuality,(BYTE)lfPitchAndFamily,pszFaceName);
	pThis->lfHorzFont = lfRulerScaleFont;

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerScaleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	LOGFONT lfRulerScaleFont;
	CString sFaceName;
	lfRulerScaleFont = pThis->lfHorzFont;
	*lfHeight = lfRulerScaleFont.lfHeight;
	*lfWidth = lfRulerScaleFont.lfWidth;
	*lfOrientation = lfRulerScaleFont.lfOrientation;
	*lfWeight = lfRulerScaleFont.lfWeight;
	*lfItalic = (long)lfRulerScaleFont.lfItalic;
	*lfUnderline = (long)lfRulerScaleFont.lfUnderline;
	*lfStrikeOut = (long)lfRulerScaleFont.lfStrikeOut;
	*lfCharSet = (long)lfRulerScaleFont.lfCharSet;
	*lfOutPrecision = (long)lfRulerScaleFont.lfOutPrecision;
	*lfClipPrecision = (long)lfRulerScaleFont.lfClipPrecision;
	*lfQuality = (long)lfRulerScaleFont.lfQuality;
	*lfPitchAndFamily = (long)lfRulerScaleFont.lfPitchAndFamily;
	sFaceName = lfRulerScaleFont.lfFaceName;
	*lfFaceName = sFaceName.AllocSysString();

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerScaleFontColor(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_crHorzSawText = (COLORREF)nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerScaleFontColor(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = (long)pThis->m_crHorzSawText;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerTenthScaleColor(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_crSmallSaw = (COLORREF)nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerTenthScaleColor(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = (COLORREF)pThis->m_crSmallSaw;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerAreaWidth(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	long lWidth;
	long lLen;
	lWidth = pThis->m_rectRuler.Width();
	if(lWidth == nValue)
		return 0;
	else
	{
		lLen = (nValue - lWidth) / 2;
		pThis->m_rectRuler.left += lLen;
		pThis->m_rectRuler.right += lLen;
		pThis->SetBorder(pThis->m_rectRuler.left,pThis->m_rectRuler.top,pThis->m_rectRuler.right,pThis->m_rectRuler.bottom);
	
		return 0;
	}
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerAreaWidth(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = pThis->m_rectRuler.Width();
	
	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerUnitScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_iHorBigSawLenLen = nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerUnitScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = pThis->m_iHorBigSawLenLen;

	return 0;
}


STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerHalfScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_iHorHalfSawLen = nValue;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerHalfScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = pThis->m_iHorHalfSawLen;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetRulerTenthScaleLineLen(long nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->m_iHorSmallSawLen = nValue;

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetRulerTenthScaleLineLen(long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	*nValue = pThis->m_iHorSmallSawLen;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::LogicPointToDevicePoint(double dValue,long *nValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->LogicPointToDevicePoint(dValue,nValue);

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::DevicePointToLogicPoint(long nValue,double *dValue)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->DevicePointToLogicPoint(nValue,dValue);

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetMinMaxVal(double Min,double Max,long nReserved)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->SetRulerMaxMinValue(Min,Max);

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetMinMaxVal(double *Min,double *Max,long nReserved)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->GetRulerMaxMinValue(Min,Max);

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::SetBoder(long left, long top, long right, long bottom)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->SetBorder(left,top,right,bottom);

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::GetBoder(long *left, long *top, long *right, long *bottom)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	CRect rectBorder;
	rectBorder = pThis->GetBorder();
	*left = rectBorder.left;
	*top = rectBorder.top;
	*right = rectBorder.right;
	*bottom = rectBorder.bottom;

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::ResetAxis()
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::DrawAxis(long lDC,float fZoomRatio,long xOffset,long yOffset)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	CDC *pDC;
	pDC = (CDC*)lDC;
	pThis->DrawIt(pDC);

	return 0;
}
STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::ZoomIn(float fRate)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->ZoomIn(fRate);

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::ZoomOut(float fRate)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->ZoomOut(fRate);

	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XRulerAxisInterface::Move(float fOffset)
{
	METHOD_PROLOGUE(CRulerAxis, RulerAxisInterface);
	pThis->Move(fOffset);

	return 0;
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) CRulerAxis::XAxisBaseInterface::AddRef()
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CRulerAxis::XAxisBaseInterface::Release()
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	return pThis->ExternalRelease();
}

STDMETHODIMP CRulerAxis::XAxisBaseInterface::QueryInterface(REFIID iid,LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(long) CRulerAxis::XAxisBaseInterface::GetBoder(long *left, long *top, long *right, long *bottom)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	CRect rectBorder;
	rectBorder = pThis->m_rectRuler;
	*left = rectBorder.left;
	*top = rectBorder.top;
	*right = rectBorder.right;
	*bottom = rectBorder.bottom;
	
	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XAxisBaseInterface::GetWorkArea(long *left, long *top, long *right, long *bottom)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	CRect rectWorkArea;
	rectWorkArea = pThis->m_rectRuler;
	*left = rectWorkArea.left;
	*top = rectWorkArea.top;
	*right = rectWorkArea.right;
	*bottom = rectWorkArea.bottom;
	
	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XAxisBaseInterface::LogicPointToDevicePoint(double x,double y,long FAR*ptx,long FAR*pty)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	pThis->LogicPointToDevicePoint(x,ptx);
	
	return 0;
}

STDMETHODIMP_(long) CRulerAxis::XAxisBaseInterface::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	pThis->DevicePointToLogicPoint(ptx,x);
	
	return 0;
}


STDMETHODIMP_(long) CRulerAxis::XAxisBaseInterface::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	pThis->GetRulerMaxMinValue(xMin,xMax);

	return 0;
}
