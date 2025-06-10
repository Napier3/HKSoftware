// RulerAxis.cpp : implementation file
//

#include "stdafx.h"
#include "RulerAxis.h"
#include "../../Module/API/GloblaDrawFunctions.h"
#include <math.h>
#include "../API/StringApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulerAxis
void CRulerAxis::LogicPointToDevicePoint(double x, double y, CPoint *pPoint, long nAxisIndex)
{
	if(m_nRulerType == g_nRulerType_Horz)
	{
		LogicPointToDevicePoint(x, &pPoint->x);

		if (m_pRefAxis != NULL)
		{
			m_pRefAxis->LogicPointToDevicePoint(y, &pPoint->y);
		}
	}
	else
	{
		LogicPointToDevicePoint(y, &pPoint->y);

		if (m_pRefAxis != NULL)
		{
			m_pRefAxis->LogicPointToDevicePoint(x, &pPoint->x);
		}
	}
}

void CRulerAxis::DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex)
{
	if(m_nRulerType == g_nRulerType_Horz)
	{
		DevicePointToLogicPoint(point.x, x);

		if (m_pRefAxis != NULL)
		{
			m_pRefAxis->DevicePointToLogicPoint(point.y, y);
		}
	}
	else
	{
		DevicePointToLogicPoint(point.y, y);

		if (m_pRefAxis != NULL)
		{
			m_pRefAxis->DevicePointToLogicPoint(point.x, x);
		}
	}
}

void CRulerAxis::LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex)
{

}

void CRulerAxis::DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex)
{

}

void CRulerAxis::GetAxisDrawArea(CRect &rcArea)
{

}

void CRulerAxis::GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{

}

void CRulerAxis::SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax)
{

}

#ifdef USE_AXIS_CONFIG
void CRulerAxis::SetAxisConfig(CDataGroup *pAxisConfig)
{

}

void CRulerAxis::GetAxisConfig(CDataGroup *pAxisConfig)
{

}

#endif

void	CRulerAxis::LogicPointToDevicePoint(double fVal, long *pnPoint)
{
	double f=0;

	if(m_nRulerType == g_nRulerType_Horz)
	{
		f=fVal * m_dOneHorGapValue + m_nCenterLogInDv;
	}
	else
	{
		f=-fVal * m_dOneHorGapValue + m_nCenterLogInDv;
	}

	*pnPoint =FloatValToInt(f);
}

void	CRulerAxis::LogicPointToDevicePoint(double fVal, int *pnPoint)
{
    double f=0;

    if(m_nRulerType == g_nRulerType_Horz)
    {
        f=fVal * m_dOneHorGapValue + m_nCenterLogInDv;
    }
    else
    {
        f=-fVal * m_dOneHorGapValue + m_nCenterLogInDv;
    }

    *pnPoint =FloatValToInt(f);
}

void	CRulerAxis::DevicePointToLogicPoint(long nPoint, double *dVal)
{
	if(m_nRulerType == g_nRulerType_Horz)
	{
		*dVal=(nPoint - m_nCenterLogInDv) / m_dOneHorGapValue;
	}
	else
	{
		*dVal=-(nPoint - m_nCenterLogInDv) / m_dOneHorGapValue;
	}
}

const long CRulerAxis::g_nRulerType_Horz = 0;
const long CRulerAxis::g_nRulerType_Vert = 1;

CRulerAxis::CRulerAxis()
{
	m_pSmallSawPen = new CPen(PS_SOLID, 1, RGB(0,0,0));
	m_rectRuler = CRect(0,0,0,0);
	m_nDrawRulerTextType	=AXIS_TYPE_NORMAL;
	m_nBOTTOMADD	=2;
	m_nBigSawMinWidth	=30;
	m_nRulerHeight	=25;
	m_nRulerDirection		=RULER_DIRECTION_RIGHTDOWN;
	m_nMaxRulerGapCount = 1000;
	m_nDrawStyle = RULERDRAW_ALL;
	
	m_dOneHorGapValue	=1;
	m_dHorCarryOneGap = 1;
	m_nCenterLogInDv	=0;
	InitIt();
	
	m_nRulerType = g_nRulerType_Horz;

	m_crFrameLeftTop = RGB(128,128,128);
	m_crFrameRightBottom = RGB(240,240,240);
	m_dScaleOffset = 0;

	//如果m_pRefAxisX不为空，则自身为Y轴；如果m_pRefAxisY不为空，则自身为X轴
	m_pRefAxis = NULL;
	m_dAxisScaleRate = 1;
}

CRulerAxis::~CRulerAxis()
{
	m_listRulerScale.DeleteAll();
	
	if (m_pSmallSawPen != NULL)
	{
		delete m_pSmallSawPen;
		m_pSmallSawPen = NULL;
	}
}

void CRulerAxis::AdjustAxisName_Time()
{
	if (m_strOldRulerName.GetLength() == 0)
	{
		m_strOldRulerName = m_strRulerName;
	}

	if (m_strOldRulerName.GetLength() == 0)
	{
		return;
	}

	if (m_strOldRulerName == _T("S"))
	{
		long nIndex = 0;
		CString strUnit[4] = {_T("S"), _T("ms"),  _T("us"),  _T("ns") };
		double dMax = m_dHorMaxValue;
		
		while (dMax * m_dAxisScaleRate < 0.999)
		{
			m_dAxisScaleRate *= 1000;
			nIndex++;
		}

		m_strRulerName = strUnit[nIndex];
	}
}


void CRulerAxis::InitIt()
{
	m_dRulerHorOneGap = 1;
	m_dVectorCoef=1;
	m_crSmallSaw = RGB(0,0,0);
	crShadowColor1=RGB(0,0,0);
	crShadowColor2=RGB(230,230,230);

#ifndef _PSX_QT_LINUX_
	m_crRulerBackColor = GetSysColor(COLOR_3DFACE);//RGB(240,240,240);
#else
    m_crRulerBackColor = RGB(240,240,240);
#endif

	m_lfRulerScaleFont=InitLogFont (-(int)(9*m_dVectorCoef),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Arial"));
	m_lfRulerTitleFont=InitLogFont (-(int)(10*m_dVectorCoef),0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Arial"));
	m_crHorzSawText=RGB(0,0,0);
	m_crHorzTitleColor=RGB(0,0,0);
	m_nFrameShadow=2;
	m_nHorBigSawLenLen	=(int)(6*m_dVectorCoef);
	m_nHorHalfSawLen	=(int)(4*m_dVectorCoef);
	m_nHorSmallSawLen	=(int)(3*m_dVectorCoef);
	m_dMaxZoomMultiple = 20000.0;
	m_strRulerName = "";
	ContinueInit();

	SetMinMaxVal(0, 10, 0);
}

void CRulerAxis::ContinueInit()
{
	if (m_pSmallSawPen != NULL)
	{
		m_pSmallSawPen->DeleteObject();
		delete m_pSmallSawPen;
	}

	m_pSmallSawPen = new CPen(PS_SOLID, 1, m_crSmallSaw);
}

long CRulerAxis::GetBaseOneGapWidth()
{
	return m_nBigSawMinWidth;
}

long CRulerAxis::GetMinOneGapWidth()
{
	return m_nBigSawMinWidth;
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
	m_nDrawRulerTextType=iType;
}
int CRulerAxis::GetRulerSawTextType()
{
	return m_nDrawRulerTextType;
}
//标尺的大刻度标注之间的间隔空间(宽度)最小值
void CRulerAxis::SetBigSawMinWidth(int iSawWidth)
{
	m_nBigSawMinWidth=iSawWidth;
}
int CRulerAxis::GetBigSawMinWidth()
{
	return m_nBigSawMinWidth;
}

//标尺的方向，0：标尺标注在下；	1：标尺标注在上
int CRulerAxis::GetRulerDirection()
{
	return m_nRulerDirection;
}

void CRulerAxis::SetRulerDirection(int iDirection)
{
	if (m_nRulerType == g_nRulerType_Horz)
	{
		m_nRulerDirection = iDirection;
	}
	else
	{
		m_nRulerDirection = iDirection;
	}
}

//高度
void CRulerAxis::SetRulerHeight(int iXAxisMinSawGapWidth)
{
	m_nRulerHeight = iXAxisMinSawGapWidth;
}

int CRulerAxis::GetRulerHeight()
{
	return m_nRulerHeight;
}

long CRulerAxis::GetMaxRulerGapNum()
{
	return m_nMaxRulerGapCount;
}

void CRulerAxis::InitRulerDef()
{
	m_listRulerScale.DeleteAll();
}

void CRulerAxis::EndRulerDef()
{
	m_listRulerScale.DeleteAll();
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
	if(m_nRulerType == g_nRulerType_Horz)
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
	if (m_nRulerType == g_nRulerType_Horz)
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
	if(m_nRulerType == g_nRulerType_Horz)
	{
		iWidth=m_rectRuler.Width();
	}
	else
	{
		iWidth=m_rectRuler.Height();
	}
	double iVal=(m_dHorMaxValue-m_dHorMinValue);//FloatValToInt
	if(m_nRulerType == g_nRulerType_Horz)
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

	if(m_nRulerType == g_nRulerType_Horz)
	{
		f=lVal-iIntegeralBeginPalace;
		if(m_nRulerDirection == RULER_DIRECTION_RIGHTDOWN)
			pScaleData->FillIt(f,CPoint(x,m_rectRuler.top+m_nBOTTOMADD));
		else
			pScaleData->FillIt(f,CPoint(x,m_rectRuler.bottom-m_nBOTTOMADD));
	}
	else
	{
			double f=lVal-iIntegeralBeginPalace;
			if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
				pScaleData->FillIt(f,CPoint(m_rectRuler.right-m_nBOTTOMADD,x));
			else
				pScaleData->FillIt(f,CPoint(m_rectRuler.left+m_nBOTTOMADD,x));
	}
	m_listRulerScale.AddNode(pScaleData);
}

CAxisScaleData* CRulerAxis::GetFirstAxisData(POS &pos)
{
	pos = m_listRulerScale.GetHeadPosition();

	CAxisScaleData *pAxisData = NULL;

	if (pos != NULL)
	{
		pAxisData = (CAxisScaleData*)m_listRulerScale.GetAt(pos);
	}

	return pAxisData;
}

CAxisScaleData* CRulerAxis::GetNextAxisData(POS &pos)
{
	CAxisScaleData *pAxisData = NULL;

	if (pos != NULL)
	{
		m_listRulerScale.GetNext(pos);
		if (pos != NULL)
			pAxisData = (CAxisScaleData*)m_listRulerScale.GetAt(pos);
	}

	return pAxisData;
}

void CRulerAxis::DrawRulerHorLine(CDC *pDC,CAxisScaleData *pScaleData)
{
	pDC->MoveTo(CPoint(pScaleData->m_ptAxisScale.x,m_rectRuler.top+m_nFrameShadow));
	pDC->LineTo(CPoint(pScaleData->m_ptAxisScale.x,m_rectRuler.bottom+m_nBOTTOMADD));
}

CRect  CRulerAxis::DrawRulerHorText(CDC *pDC,CAxisScaleData *pScaleData,BOOL bAddUint,BOOL bReallyDraw)
{
	char szTemp[50];
	char cStr[128];
	double dValue = (pScaleData->m_dAxisScaleVal + m_dScaleOffset)  * m_dAxisScaleRate;
	sprintf(cStr,"%.7f", dValue);
	int iLen=strlen(cStr);
	double f=0;
	
	if(cStr[iLen-1]>='5')
	{
		cStr[iLen-1]=0;
		f=atof(cStr);
		if(f>=AXIS_CAL_MIN_VALUE)f=f+AXIS_CAL_MIN_VALUE;
		else f=f-AXIS_CAL_MIN_VALUE;
		sprintf(cStr,"%.7f",f);
	}
	
	_ChopFloatString(cStr);

	if(m_nRulerType == g_nRulerType_Horz)
	{
		if(bAddUint==TRUE)
		{
			CString_to_char(m_strRulerName, szTemp);
			strcat(cStr,szTemp);
		}

		CRect cR1;
		CRect crCal = cR1;
		pDC->DrawText(cStr, &crCal, DT_CALCRECT);
		long nWidth = crCal.Width() / 2 + 1;
		cR1.left	=pScaleData->m_ptAxisScale.x-(int)(nWidth*m_dVectorCoef);
		cR1.right	=pScaleData->m_ptAxisScale.x+(int)(nWidth*m_dVectorCoef);

		if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
		{
			cR1.top		=pScaleData->m_ptAxisScale.y+(int)(7*m_dVectorCoef);
			cR1.bottom	=pScaleData->m_ptAxisScale.y+(int)(20*m_dVectorCoef);
		}
		else
		{
			cR1.bottom	=pScaleData->m_ptAxisScale.y-(int)(7*m_dVectorCoef);
			cR1.top		=pScaleData->m_ptAxisScale.y-(int)(20*m_dVectorCoef);
		}

		if (cR1.right > m_rectRuler.right)
		{
			long nOffset = cR1.right - m_rectRuler.right;
			cR1.right -= nOffset;
			cR1.left -= nOffset;
		}

		pDC->DrawText(CString(cStr), &cR1, DT_VCENTER|DT_CENTER);
		//CmDrawTextRect(pDC,cStr,m_crHorzSawText,cR1,RGB(0,0,0),m_lfRulerScaleFont,TRANSPARENT,DT_VCENTER|DT_CENTER,0);
		return cR1;
	}
	else
	{
		long lHeight=(long)fabs(m_lfRulerScaleFont.lfHeight*m_dVectorCoef) / 2;
		CRect rect;
		int iStrLen=strlen(cStr) ;
		float fStrLen=(float)iStrLen/* / 2*/;
		
		CRect rcPos(0,0,0,0);
		long nFornat = DT_CALCRECT | DT_SINGLELINE;
		nFornat = nFornat & DT_CALCRECT;

		pDC->DrawText(cStr, rcPos, DT_CALCRECT | DT_SINGLELINE);
		lHeight = rcPos.Height() / 2 + 1;
		long nWidth = rcPos.Width() + 4;
		
		if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
		{
			rect.left	=pScaleData->m_ptAxisScale.x-nWidth;//(int)(iCharWidth*fStrLen*m_dVectorCoef);//(int)(20*m_dVectorCoef);
			rect.right	=pScaleData->m_ptAxisScale.x;//-(int)(7*m_dVectorCoef);
			rect.bottom	=pScaleData->m_ptAxisScale.y+lHeight;//(int)(iCharWidth*fStrLen*m_dVectorCoef);
			rect.top	=pScaleData->m_ptAxisScale.y-lHeight + (int)(m_dVectorCoef);//(int)(iCharWidth*fStrLen*m_dVectorCoef);
			rect.OffsetRect(-m_nHorBigSawLenLen, 0);
			pDC->DrawText(CString(cStr), &rect, DT_VCENTER|DT_RIGHT);
			//CmDrawTextRect(pDC,cStr,m_crHorzSawText,rect,RGB(0,0,0),m_lfRulerScaleFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
		}
		else
		{
			rect.left	=pScaleData->m_ptAxisScale.x+(int)(2*m_dVectorCoef);
			rect.right	=pScaleData->m_ptAxisScale.x+nWidth;//(int)(iCharWidth*fStrLen*m_dVectorCoef);//(int)(7*m_dVectorCoef);
			rect.top	=pScaleData->m_ptAxisScale.y-lHeight + (int)(m_dVectorCoef);
			rect.bottom	=pScaleData->m_ptAxisScale.y+lHeight;//(int)(iCharWidth*fStrLen*m_dVectorCoef);
			rect.OffsetRect(m_nHorBigSawLenLen, 0);
			pDC->DrawText(CString(cStr), &rect, DT_VCENTER|DT_LEFT);
		}
		
		return rect;
	}
}

void CRulerAxis::DrawRulerHorName(CDC *pDC)
{
	int iLen=m_strRulerName.GetLength();

	if (iLen == 0)
	{
		return;
	}

	CFont CF;
	CF.CreateFontIndirect(&m_lfRulerTitleFont);
	CFont *c=pDC->SelectObject(&CF);
	TEXTMETRIC textMetric;
	pDC->GetTextMetrics(&textMetric);
	pDC->SelectObject(c);
	iLen=textMetric.tmAveCharWidth *(iLen+1);

	CRect cR;
	cR.left=m_rectRuler.right-iLen;
	cR.top=m_rectRuler.bottom- (long)(m_dVectorCoef*5);
	cR.right= m_rectRuler.right;
	cR.bottom=m_rectRuler.bottom+5;
	char cName[128];
// 	lstrcpy(cName,m_strRulerName);
	CString_to_char(m_strRulerName, cName);
	CmDrawTextRect(pDC,(CString)cName,m_crHorzTitleColor,&cR,RGB(0,0,0),
				   m_lfRulerTitleFont,TRANSPARENT,DT_VCENTER|DT_RIGHT,0);
}

void CRulerAxis::DrawRulerHorFrame(CDC*pDC)
{
	CPoint ptTopLeft=m_rectRuler.TopLeft();
	CPoint ptRightBottom=m_rectRuler.BottomRight();
	CPen pen1(PS_SOLID,1,m_crFrameLeftTop);
	CPen pen2(PS_SOLID,1,m_crFrameRightBottom);

	if(RULERDRAW_BODER & m_nDrawStyle)
	{
		if(m_nRulerType == g_nRulerType_Horz)
		{
			for(int i=0;i<m_nFrameShadow;i++)
			{
				DrawLine(pDC,ptTopLeft.x+i,ptTopLeft.y+i,ptRightBottom.x-i,ptTopLeft.y+i,&pen1);
				DrawLine(pDC,ptTopLeft.x+i,ptRightBottom.y-i,ptRightBottom.x-i,ptRightBottom.y-i,&pen2);		
				//	pDC->MoveTo(ptTopLeft);	pDC->LineTo(ptRightBottom.x,ptTopLeft.y);
				//	pDC->MoveTo(ptTopLeft.x,ptRightBottom.y);	pDC->LineTo(ptRightBottom);
			}
		}
		else
		{
			for(int i=0;i<m_nFrameShadow;i++)
			{
				DrawLine(pDC,ptTopLeft.x+i,ptTopLeft.y+i,ptTopLeft.x+i,ptRightBottom.y-i,&pen1);
				DrawLine(pDC,ptRightBottom.x-i,ptTopLeft.y+i,ptRightBottom.x-i,ptRightBottom.y-i,&pen2);
				//	pDC->MoveTo(ptTopLeft);	pDC->LineTo(ptTopLeft.x,ptRightBottom.y);
				//	pDC->MoveTo(ptRightBottom.x,ptTopLeft.y);	pDC->LineTo(ptRightBottom);
			}
		}
	}
	else
	{
		if(m_nRulerType == g_nRulerType_Horz)
		{
			if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
			{
				DrawLine(pDC,ptTopLeft.x,ptTopLeft.y+1,ptRightBottom.x+1,ptTopLeft.y+1,&pen2);		
			}
			else
			{
				DrawLine(pDC,ptTopLeft.x,ptRightBottom.y-1,ptRightBottom.x,ptRightBottom.y,&pen2);		
			}
		}
		else
		{
			if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
			{
				DrawLine(pDC,ptRightBottom.x-1,ptTopLeft.y,ptRightBottom.x-1,ptRightBottom.y+1,&pen2);
			}
			else
			{
				DrawLine(pDC,ptTopLeft.x+1,ptRightBottom.y,ptTopLeft.x+1,ptTopLeft.y-1,&pen2);
			}
		}
	}

	pen1.DeleteObject();
	pen2.DeleteObject();
}

void CRulerAxis::DrawRulerBack(CDC *pDC)
{
	//绘制背景
	if(m_nDrawStyle & RULERDRAW_WORKAREA)
	{
		CBrush brush;
		brush.CreateSolidBrush(m_crRulerBackColor);
		pDC->FillRect(m_rectRuler,&brush);
		brush.DeleteObject();
	}
}

void CRulerAxis::DrawRulerHor(CDC *pDC)
{
	int iNum=m_listRulerScale.GetCount();
	if(iNum<=0)return;
	
	CFont font;
	font.CreateFontIndirect(&m_lfRulerScaleFont);
	CFont *pOldFont = pDC->SelectObject(&font);
	COLORREF crOld = pDC->SetTextColor(m_crHorzSawText);
	UINT nMode = pDC->SetBkMode(TRANSPARENT);

	if(m_nRulerType == g_nRulerType_Horz)
	{
		if(m_nDrawStyle & RULERDRAW_SCALETEXT)
		{
			for (int i=0;i<iNum;i++)
			{
				CAxisScaleData *pScaleData=(CAxisScaleData*)m_listRulerScale.GetAt(i);
				if(pScaleData->m_ptAxisScale.x<m_rectRuler.left || pScaleData->m_ptAxisScale.x>m_rectRuler.right) 
					continue;
				
				DrawRulerHorText(pDC,pScaleData,FALSE,TRUE);
			}
		}
	}
	else
	{
		for (int i=0;i<iNum;i++)
		{
			CAxisScaleData *pScaleData=(CAxisScaleData*)m_listRulerScale.GetAt(i);

			if( m_nDrawStyle & RULERDRAW_SCALETEXT)
			{
				if(pScaleData->m_ptAxisScale.y>=m_rectRuler.top && pScaleData->m_ptAxisScale.y<=m_rectRuler.bottom)
				{
					DrawRulerHorText(pDC,pScaleData,FALSE,FALSE);////标注
				}
			}
		}
	}
	
	pDC->SetBkMode(nMode);
	pDC->SetTextColor(crOld);
	pDC->SelectObject(pOldFont);
	font.DeleteObject();

	if(m_nDrawStyle & RULERDRAW_HALFSCCALE)
		DrawRulerHorSawtooth(pDC,SCCALE_TYPE_HALF);

	if(m_nDrawStyle & RULERDRAW_TENTHSCALE)
		DrawRulerHorSawtooth(pDC,SCCALE_TYPE_TENTH);
		
	DrawRulerHorName(pDC);
}

void CRulerAxis::DrawOneRulerHorSawtooth(CDC *pDC,CPoint cBegin,CPoint cEnd)
{
	CPen *pOldPen=pDC->SelectObject(m_pSmallSawPen);

	for (int i=0;i<10;i++)
	{
		int iGapVal=FloatValToInt((float)((float)m_dRulerHorOneGap/10.0*i));
		
		if(m_nRulerType == g_nRulerType_Horz)
		{
			CPoint cPt(cBegin.x+iGapVal,cBegin.y);
			if((cPt.x<m_rectRuler.left)||(cPt.x>m_rectRuler.right))
				continue;

			pDC->MoveTo(cPt.x,cPt.y+1);
			if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
			{
				pDC->MoveTo(cPt.x,cPt.y+1);
				pDC->LineTo(cPt.x,cPt.y+m_nHorSmallSawLen);
			}
			else
			{
				pDC->MoveTo(cPt.x,cPt.y-1);
				pDC->LineTo(cPt.x,cPt.y-m_nHorSmallSawLen);
			}
		}
		else
		{
			CPoint cPt(cBegin.x,cBegin.y-iGapVal);
			if((cPt.y<m_rectRuler.top)||(cPt.y>m_rectRuler.bottom))
				continue;
			if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
			{
				pDC->MoveTo(cPt.x-1,cPt.y);
				pDC->LineTo(cPt.x-m_nHorSmallSawLen,cPt.y);
			}
			else
			{
				pDC->MoveTo(cPt.x+1,cPt.y);
				pDC->LineTo(cPt.x+m_nHorSmallSawLen,cPt.y);
			}
		}
	}

	pDC->SelectObject(pOldPen);
}

void CRulerAxis::DrawOneRulerHorSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd)
{
	int iLen[2]={m_nHorBigSawLenLen,m_nHorHalfSawLen};

	if(m_nRulerType == g_nRulerType_Horz)
	{
		for (int i=0;i<2;i++)
		{
			int iGapVal=FloatValToInt((float)((float)m_dRulerHorOneGap/2.0*i));
			CPoint cPt(cBegin.x+iGapVal,cBegin.y);
			if((cPt.x<m_rectRuler.left)||(cPt.x>m_rectRuler.right)) continue;
			if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
				DrawRulerShadowVertLine(pDC,cPt.x,cPt.y,iLen[i],crShadowColor1,crShadowColor2);
			else
				DrawRulerShadowVertLine(pDC,cPt.x,cPt.y,-iLen[i],crShadowColor1,crShadowColor2);
		}
	}
	else
	{
		for (int i=0;i<2;i++)
		{
			int iGapVal=FloatValToInt((float)((float)m_dRulerHorOneGap/2.0*i));
			CPoint cPt(cBegin.x,cBegin.y-iGapVal);
			if((cPt.y<m_rectRuler.top)||(cPt.y>m_rectRuler.bottom))	continue;
			DrawRulerShadowVertLine(pDC,cPt.x,cPt.y,iLen[i],crShadowColor1,crShadowColor2);
		}
	}
}
void CRulerAxis::DrawLine(CDC *pDC,int left,int top,int right,int bottom,CPen *pen)
{
	CPen *cOldB=pDC->SelectObject(pen);

	pDC->MoveTo(left,top);
	pDC->LineTo(right,bottom);

	pDC->SelectObject(cOldB);
}

void CRulerAxis::DrawRulerShadowVertLine(CDC *pDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2)
{
	CPen pen(PS_SOLID,1,crColor1);
	CPen pen1(PS_SOLID,1,crColor2);
	
	if(m_nRulerType == g_nRulerType_Horz)
	{
		DrawLine(pDC,iLeft,iTop,iLeft,iTop+iLen,&pen);

		if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
			DrawLine(pDC,iLeft+1,iTop+2,iLeft+1,iTop+iLen,&pen1);
		else
			DrawLine(pDC,iLeft+1,iTop-2,iLeft+1,iTop+iLen,&pen1);
	}
	else
	{
		if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
		{
			DrawLine(pDC,iLeft,iTop,iLeft-iLen,iTop,&pen);
			DrawLine(pDC,iLeft,iTop+1,iLeft-iLen+2,iTop+1,&pen1);
		}
		else
		{
			DrawLine(pDC,iLeft,iTop,iLeft+iLen,iTop,&pen);
			DrawLine(pDC,iLeft,iTop+1,iLeft+iLen-2,iTop+1,&pen1);
		}
	}

	pen.DeleteObject();
	pen1.DeleteObject();
}

void CRulerAxis::DrawRulerHorSawtooth(CDC *pDC,BYTE bKind)
{
	CPoint cBegin,cEnd;
	
	for (int i=0;i<m_listRulerScale.GetCount();i++)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listRulerScale.GetAt(i);
	
		if (i==0)
		{
			if(m_nRulerType == g_nRulerType_Horz)
			{
				cBegin=CPoint((int)(pScaleData->m_ptAxisScale.x-m_dRulerHorOneGap),pScaleData->m_ptAxisScale.y);
				cEnd=pScaleData->m_ptAxisScale;

				if (m_nDrawStyle & RULERDRAW_TENTHSCALE)
				{
					CPen *cOldP=pDC->SelectObject(m_pSmallSawPen);
					
					for (int i=0;i<10;i++)
					{
						int iGapVal=FloatValToInt((float)((float)m_dRulerHorOneGap/10.0*i));
						CPoint cPt(cBegin.x+iGapVal,cEnd.y);
						if((cPt.x<m_rectRuler.left)||(cPt.x>m_rectRuler.right))
							continue;
						
						if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
						{
							pDC->MoveTo(cPt.x,cPt.y+1);
							pDC->LineTo(cPt.x,cPt.y+m_nHorSmallSawLen);
						}
						else
						{
							pDC->MoveTo(cPt.x,cPt.y-1);
							pDC->LineTo(cPt.x,cPt.y-m_nHorSmallSawLen);
						}
					}
					
					pDC->SelectObject(cOldP);
					continue;
				}
			}
			else
			{
				cBegin=CPoint(pScaleData->m_ptAxisScale.x,(int)(pScaleData->m_ptAxisScale.y+m_dRulerHorOneGap));
				cEnd=pScaleData->m_ptAxisScale;

				if (m_nDrawStyle & RULERDRAW_TENTHSCALE)
				{
					CPen *cOldP=pDC->SelectObject(m_pSmallSawPen);
					
					for (int i=0;i<10;i++)
					{
						int iGapVal=FloatValToInt((float)((float)m_dRulerHorOneGap/10.0*i));
						CPoint cPt(cBegin.x,cEnd.y+iGapVal);
						if((cPt.y<m_rectRuler.top)||(cPt.y>m_rectRuler.bottom))
							continue;
						
						if(m_nRulerDirection==RULER_DIRECTION_RIGHTDOWN)
						{
							pDC->MoveTo(cPt.x-1,cPt.y);
							pDC->LineTo(cPt.x-m_nHorSmallSawLen,cPt.y);
						}
						else
						{
							pDC->MoveTo(cPt.x+1,cPt.y);
							pDC->LineTo(cPt.x+m_nHorSmallSawLen,cPt.y);
						}
					}
					
					pDC->SelectObject(cOldP);
					continue;
				}
			}
		}
		else 
		{
				CAxisScaleData *odNewData=(CAxisScaleData *)m_listRulerScale.GetAt(i-1);
				cBegin=odNewData->m_ptAxisScale;
				cEnd=pScaleData->m_ptAxisScale;
		}	

		if (bKind == SCCALE_TYPE_TENTH)
			DrawOneRulerHorSawtooth(pDC,cBegin,cEnd);
		else 
			DrawOneRulerHorSawtoothShadow(pDC,cBegin,cEnd);
	}

	if(m_listRulerScale.GetCount()>=2)
	{
		CAxisScaleData *pScaleData=(CAxisScaleData *)m_listRulerScale.GetTail();

		if(m_nRulerType == g_nRulerType_Horz)
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
//	pDC->Rectangle(m_rectRuler);
	DrawRulerBack(pDC);
	DrawRulerHorFrame(pDC);
	DrawRulerHor(pDC);
}


double CRulerAxis::MakeFloatGapValLegal(double fVal,double &lVal)
{
	int i = 0;
	double fTmp=fVal;

	if(fTmp<=AXIS_CAL_MIN_VALUE)
	{
		fVal=fTmp;
		return fTmp;
	}

	double fMulti=GetFloatCarryVal(fTmp);///进位数值
	int iSet[4]={1,2,5,10};/////////

	for ( i=0;i<3;i++)
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
	double fStep = AXIS_CAL_MIN_VALUE;
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

	if(m_nRulerType == g_nRulerType_Horz)
	{
		m_rectRuler.bottom = m_rectRuler.top+m_nRulerHeight;
	}
	else
	{
		m_rectRuler.right = m_rectRuler.left + m_nRulerHeight;
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
	SetOldRulerMaxMinValue(dMinValue, dMaxValue);
	ResetRulerDef();

	AdjustAxisName_Time();
}
void CRulerAxis::GetOldRulerMaxMinValue(double *dMinValue,double *dMaxValue)
{
	*dMinValue	=m_dHorOldMinValue;
	*dMaxValue	=m_dHorOldMaxValue;
}

void CRulerAxis::SetOldRulerMaxMinValue(double dMinValue,double dMaxValue)
{
	m_dHorOldMinValue	=dMinValue;
	m_dHorOldMaxValue	=dMaxValue;
//	ResetRulerDef();
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
	if(m_nRulerType == g_nRulerType_Horz)
	{
		iWidth=rectWork.Width();
	}
	else
	{
		iWidth=rectWork.Height();
	}
	double fValXOneGap=iWidth/(fXMaxValue-fXMinValue);//X轴实际坐标与实际值的比率
	/////坐标原点在屏幕上的位置
	if(m_nRulerType == g_nRulerType_Horz)
	{
		f=rectWork.left + (0-fXMinValue)*fValXOneGap;
	}
	else
	{
		f=rectWork.bottom - (0-fXMinValue)*fValXOneGap;
	}

	m_nCenterLogInDv	=FloatValToInt(f);
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
//	fMinValue = m_dHorMinValue / fRate;
//	fMaxValue = m_dHorMaxValue / fRate;
//	m_dHorOldMinValue = m_dHorMinValue;
//	m_dHorOldMaxValue = m_dHorMaxValue;
	
	double fLen=fabs(m_dHorMaxValue-m_dHorMinValue);
	fMinValue = m_dHorMinValue;
	fMaxValue = m_dHorMinValue + fLen / fRate;

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
//	m_dHorOldMinValue = m_dHorMinValue;
//	m_dHorOldMaxValue = m_dHorMaxValue;
	
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

// 
// //将逻辑坐标转化为实际坐标
// void CRulerAxis::LogicPointToDevicePoint(double fx,long *iX)
// {
// 	double f=0;
// 	
// 	if (g_nRulerType_Vert == m_nRulerType)
// 	{
// 		f = -fx * m_dOneHorGapValue + m_nCenterLogInDv;
// 	}
// 	else
// 	{
// 		f = fx * m_dOneHorGapValue + m_nCenterLogInDv;
// 	}
// 
// 	*iX=FloatValToInt(f);
// }
// //从实际坐标获取实际坐标所代表的值
// void CRulerAxis::DevicePointToLogicPoint(long iX,double *dX)
// {
// 	*dX=(iX-m_nCenterLogInDv) / m_dOneHorGapValue;
// }

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


long CRulerAxis::GetMinSawGapWidth(long *nValue)
{
	*nValue	= GetMinOneGapWidth();

	return 0;
}

long CRulerAxis::SetMinSawGapWidth(long nValue)
{

	m_nBigSawMinWidth = nValue;

	return 0;
}

long CRulerAxis::GetRulerType(long *nValue)
{

	*nValue = m_nRulerType;

	return 0;
}
long CRulerAxis::SetRulerType(long nValue)
{

	m_nRulerType = nValue;

	return 0;
}

long CRulerAxis::SetMaxUnitCount(long nValue)
{

	m_nMaxRulerGapCount = nValue;
	
	return 0;
}

long CRulerAxis::GetMaxUnitCount(long *nValue)
{

	*nValue = m_nMaxRulerGapCount;

	 return 0;
}
long CRulerAxis::SetDrawStyle(long nValue)
{

	m_nDrawStyle = nValue;

	return 0;
}

long CRulerAxis::GetDrawStyle(long *nValue)
{

	*nValue = m_nDrawStyle;

	return 0;
}

long CRulerAxis::SetDrawStyleBit(long nValue)
{

	m_nDrawStyle |= nValue;

	return 0;
}
long CRulerAxis::ClearDrawStyleBit(long nValue)
{

	m_nDrawStyle &= (~nValue);

	return 0;
}

long CRulerAxis::SetScaleTextDrawStyle(long nValue)
{

	SetRulerSawTextType(nValue);

	return 0;
}

long CRulerAxis::GetScaleTextDrawStyle(long *nValue)
{

	*nValue = GetRulerSawTextType();

    return 0;
}

//坐标系统的绘制类型,2005.08.12添加
long CRulerAxis::SetRulerTitle(BSTR bstrValue)
{

/*
	char pszRulerTitle[MAX_PATH];
	memset(pszRulerTitle,0,MAX_PATH);
	BSTRToAnsiStr(bstrValue,pszRulerTitle);*/

	m_strRulerName = bstrValue;
	
	return 0;
}

long CRulerAxis::GetRulerTitle(BSTR *pbstrValue)
{

	CString strRulerTitle;
	strRulerTitle = m_strRulerName;
	*pbstrValue = strRulerTitle.AllocSysString();	
	
    return 0;
}
long CRulerAxis::SetRulerTitleFont(LOGFONT lfFont)
{
	m_lfRulerTitleFont = lfFont;
	return 0;
}

LOGFONT CRulerAxis::GetRulerTitleFont()
{
	return m_lfRulerTitleFont;
}


long CRulerAxis::SetRulerTitleFontColor(long nValue)
{

	m_crHorzTitleColor = (COLORREF)nValue;

	return 0;
}

long CRulerAxis::GetRulerTitleFontColor(long *nValue)
{

	*nValue = (long)m_crHorzTitleColor;

	return 0;
}

long CRulerAxis::SetRulerBackColor(long nValue)
{

	m_crRulerBackColor = (COLORREF)nValue;

	return 0;
}
long CRulerAxis::GetRulerBackColor(long *nValue)
{

	*nValue = (long)m_crRulerBackColor;

	return 0;
}

long CRulerAxis::SetFrameLeftTopColor(long nValue)
{

	m_crFrameLeftTop = (COLORREF)nValue;

	return 0;
}

long CRulerAxis::GetFrameLeftTopColor(long *nValue)
{

	*nValue = (long)m_crFrameLeftTop;

	return 0;
}
long CRulerAxis::SetFrameRightBottomColor(long nValue)
{

	m_crFrameRightBottom = (COLORREF)nValue;

	return 0;
}

long CRulerAxis::GetFrameRightBottomColor(long *nValue)
{

	*nValue = (long)m_crFrameRightBottom;

	return 0;
}

long CRulerAxis::SetFrameShadow(long nValue)
{
	m_nFrameShadow = nValue;

	return 0;
}
long CRulerAxis::GetFrameShadow(long *nValue)
{

	*nValue = m_nFrameShadow;

	return 0;
}

long CRulerAxis::SetUnitScaleColor(long nValue)
{

	crShadowColor1 = (COLORREF)nValue;

	return 0;
}

long CRulerAxis::GetUnitScaleColor(long *nValue)
{

	*nValue = (long)crShadowColor1;

	return 0;
}
long CRulerAxis::SetUnitScaleShadowColor(long nValue)
{

	crShadowColor2 = (COLORREF)nValue;

	return 0;
}

long CRulerAxis::GetUnitScaleShadowColor(long *nValue)
{

	*nValue = (long)crShadowColor2;

	return 0;
}

long CRulerAxis::SetRulerScaleFont(LOGFONT lfFont)
{
	m_lfRulerScaleFont = lfFont;
	return 0;
}
LOGFONT CRulerAxis::GetRulerScaleFont()
{
	return m_lfRulerScaleFont;
}

long CRulerAxis::SetRulerScaleFontColor(long nValue)
{

	m_crHorzSawText = (COLORREF)nValue;

	return 0;
}

long CRulerAxis::GetRulerScaleFontColor(long *nValue)
{

	*nValue = (long)m_crHorzSawText;

	return 0;
}

long CRulerAxis::SetRulerTenthScaleColor(long nValue)
{

	m_crSmallSaw = (COLORREF)nValue;
	ContinueInit();

	return 0;
}

long CRulerAxis::GetRulerTenthScaleColor(long *nValue)
{

	*nValue = (COLORREF)m_crSmallSaw;

	return 0;
}

long CRulerAxis::SetRulerAreaWidth(long nValue)
{

	long lWidth;
	long lLen;
	lWidth = m_rectRuler.Width();
	if(lWidth == nValue)
		return 0;
	else
	{
		lLen = (nValue - lWidth) / 2;
		m_rectRuler.left += lLen;
		m_rectRuler.right += lLen;
		SetBorder(m_rectRuler.left,m_rectRuler.top,m_rectRuler.right,m_rectRuler.bottom);
	
		return 0;
	}
}

long CRulerAxis::GetRulerAreaWidth(long *nValue)
{

	*nValue = m_rectRuler.Width();
	
	return 0;
}

long CRulerAxis::SetRulerUnitScaleLineLen(long nValue)
{

	m_nHorBigSawLenLen = nValue;

	return 0;
}

long CRulerAxis::SetRulerBoderShow(long nValue)
{
	if (nValue == 0)
	{
		m_nDrawStyle &= ~ RULERDRAW_BODER;
	}
	else
	{
		m_nDrawStyle |= RULERDRAW_BODER;
	}
	
	return m_nDrawStyle;
}

long CRulerAxis::SetDrawBack(long nValue)
{
	if (nValue == 0)
	{
		m_nDrawStyle &= ~ RULERDRAW_WORKAREA;
	}
	else
	{
		m_nDrawStyle |= RULERDRAW_WORKAREA;
	}
	
	return m_nDrawStyle;
}

long CRulerAxis::SetRulerHalfScaleShow(long nValue)
{
	if (nValue == 0)
	{
		m_nDrawStyle &= ~ RULERDRAW_TENTHSCALE;
		m_nDrawStyle &= ~ RULERDRAW_HALFSCCALE;
	}
	else
	{
		m_nDrawStyle |= RULERDRAW_HALFSCCALE;
	}

	return m_nDrawStyle;
}

long CRulerAxis::GetRulerUnitScaleLineLen(long *nValue)
{

	*nValue = m_nHorBigSawLenLen;

	return 0;
}


long CRulerAxis::SetRulerHalfScaleLineLen(long nValue)
{

	m_nHorHalfSawLen = nValue;

	return 0;
}

long CRulerAxis::GetRulerHalfScaleLineLen(long *nValue)
{

	*nValue = m_nHorHalfSawLen;

	return 0;
}

long CRulerAxis::SetRulerTenthScaleLineLen(long nValue)
{

	m_nHorSmallSawLen = nValue;

	return 0;
}

long CRulerAxis::GetRulerTenthScaleLineLen(long *nValue)
{

	*nValue = m_nHorSmallSawLen;

	return 0;
}


long CRulerAxis::SetRulerTenthScaleShow(long nValue)
{
	if (nValue == 0)
	{
		m_nDrawStyle &= ~ RULERDRAW_TENTHSCALE;
	}
	else
	{
		if ((m_nDrawStyle & RULERDRAW_HALFSCCALE) == RULERDRAW_HALFSCCALE)
		{
			m_nDrawStyle |= RULERDRAW_TENTHSCALE;
		}
		else
		{
		}
	}
	
	return m_nDrawStyle;
}

long CRulerAxis::SetMinMaxVal(double Min,double Max,long nReserved)
{

	SetRulerMaxMinValue(Min,Max);

	return 0;
}

long CRulerAxis::GetMinMaxVal(double *Min,double *Max,long nReserved)
{

	GetRulerMaxMinValue(Min,Max);

	return 0;
}

long CRulerAxis::ResetAxis()
{

	return 0;
}

//
//long CRulerAxis::ZoomIn(float fRate)
//{
//
//	ZoomIn(fRate);
//
//	return 0;
//}
//
//long CRulerAxis::ZoomOut(float fRate)
//{
//
//	ZoomOut(fRate);
//
//	return 0;
//}
//
//long CRulerAxis::Move(float fOffset)
//{
//
//	Move(fOffset);
//
//	return 0;
//}

/*
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) CRulerAxis::XAxisBaseInterface::AddRef()
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	return ExternalAddRef();
}

STDMETHODIMP_(ULONG) CRulerAxis::XAxisBaseInterface::Release()
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	return ExternalRelease();
}

STDMETHODIMP CRulerAxis::XAxisBaseInterface::QueryInterface(REFIID iid,LPVOID* ppvObj)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	return ExternalQueryInterface(&iid, ppvObj);
}

long CRulerAxis::XAxisBaseInterface::GetBoder(long *left, long *top, long *right, long *bottom)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	CRect rectBorder;
	rectBorder = m_rectRuler;
	*left = rectBorder.left;
	*top = rectBorder.top;
	*right = rectBorder.right;
	*bottom = rectBorder.bottom;
	
	return 0;
}

long CRulerAxis::XAxisBaseInterface::GetWorkArea(long *left, long *top, long *right, long *bottom)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	CRect rectWorkArea;
	rectWorkArea = m_rectRuler;
	*left = rectWorkArea.left;
	*top = rectWorkArea.top;
	*right = rectWorkArea.right;
	*bottom = rectWorkArea.bottom;
	
	return 0;
}

long CRulerAxis::XAxisBaseInterface::LogicPointToDevicePoint(double x,double y,long FAR*ptx,long FAR*pty)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	LogicPointToDevicePoint(x,ptx);
	
	return 0;
}

long CRulerAxis::XAxisBaseInterface::DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	DevicePointToLogicPoint(ptx,x);
	
	return 0;
}


long CRulerAxis::XAxisBaseInterface::GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved)
{
	METHOD_PROLOGUE(CRulerAxis, AxisBaseInterface);
	GetRulerMaxMinValue(xMin,xMax);

	return 0;
}
*/
