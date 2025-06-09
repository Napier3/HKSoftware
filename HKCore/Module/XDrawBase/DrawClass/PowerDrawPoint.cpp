// PowerDrawPoint.cpp: implementation of the CPowerDrawPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerDrawPoint.h"
/////////////////////////注册表头文件
#include "PowerRegisterKey.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPowerDrawPoint::CPowerDrawPoint()
{
	m_iDrawType=10;
	m_pointValue=CPoint (0,0);
	m_ppv.dX=m_ppv.dY=0;
	iMMM=1;
	m_iPixel=4;

	CPowerRegisterKey regKey1;
	regKey1.RegRegOpen(HKEY_CURRENT_USER,_T("Software\\PowerAdvance\\"));
	CString strPiexl="";
	regKey1.RegRead(_T("PTPIXEL"),strPiexl);
	strPiexl.TrimLeft();
	if(strPiexl.GetLength()>=1)
	{
		m_iPixel=atoi(strPiexl);
	}
	if(m_iPixel>4)m_iPixel=4;
	if(m_iPixel<2)m_iPixel=2;
}
CPowerDrawPoint::CPowerDrawPoint(CString strClass):CPowerDrawBaseClass(strClass)
{

}

CPowerDrawPoint::~CPowerDrawPoint()
{

}
CString CPowerDrawPoint::GetExportTextString(void)
{
	return "";
}
CString  CPowerDrawPoint::GetDisplayDataString(void)
{
	CString strData="";
	CString strTemp="";
	
	char chTemp[80];chTemp[0]=0;
	strData="(POINT=";
	strTemp.Format("%f",m_ppv.dX);strcpy(chTemp,strTemp);chop(chTemp);		strTemp.Format("%s,",chTemp);strData+=strTemp;
	strTemp.Format("%f",m_ppv.dY);strcpy(chTemp,strTemp);chop(chTemp);		strTemp.Format("%s,",chTemp);strData+=strTemp;
	strTemp.Format("%d)",m_iDrawType);strData+=strTemp;

	return strData;
}
BOOL CPowerDrawPoint::InitOwnDataByString(CString strOwnData)
{
	int iBegin=0;
	int iEnd=0;
	CString strData="";
	CString strsp="=";
	CString strsp2=",";
	iBegin=strOwnData.Find(strsp);
	if(iBegin==-1)return FALSE;
	iBegin++;
	double x=0,y=0;
	
	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	x=atof(strData);
	iBegin=iEnd+1;

	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	y=atof(strData);
	iBegin=iEnd+1;

	//strData=strOwnData.Mid(iBegin,strOwnData.GetLength()-iBegin-1);
	strData=strOwnData.Right(strOwnData.GetLength()-iBegin);
	m_iDrawType=atoi(strData);
	iBegin=iEnd+1;

	m_ppv.dX=x;m_ppv.dY=y;

	return TRUE;
}

BOOL CPowerDrawPoint::ContinueInitIt(CAxisReference *axisReference)
{
	LogicPointToDevicePoint(&m_pointValue,m_ppv.dX,m_ppv.dY,axisReference);
	return TRUE;
}


CPowerDrawBaseClass* CPowerDrawPoint::DirectGetNewObject()
{

	return new CPowerDrawPoint;
}

void CPowerDrawPoint::DrawIt(CDC *pDC,BOOL bSel,double fZoomRatio,CPoint ptOffset)
{
	CPoint ptValue = m_pointValue;
	ptValue.Offset(ptOffset);
	CPen cp,*pOldPen;
	cp.CreatePen(m_uiLineStyle,m_iLineWidth,m_ulColor);
	pOldPen=pDC->SelectObject(&cp);

	CRect rectC;
	CBrush brush,*pOldBrush;
	CGdiObject *pObj1;
	int iLen = (int)(m_iPixel * iMMM * fZoomRatio);
	int iMMMTemp = (int)(iMMM * fZoomRatio);

	switch(m_iDrawType)
	{
	case 0:	////	+ 
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen+iMMMTemp,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen+iMMMTemp);
		break;
	case 1:	////	x
		pDC->MoveTo(ptValue.x-iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x+iLen+iMMMTemp,ptValue.y+iLen+iMMMTemp);
		pDC->MoveTo(ptValue.x+iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x-iLen-iMMMTemp,ptValue.y+iLen+iMMMTemp);
		break;
	case 2:	////	+o	
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen+iMMMTemp,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen+iMMMTemp);
		rectC=CRect(ptValue.x-2*iMMMTemp,ptValue.y-2*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pObj1);
		break;
	case 3:	////	xo
		pDC->MoveTo(ptValue.x-iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x+iLen+iMMMTemp,ptValue.y+iLen+iMMMTemp);
		pDC->MoveTo(ptValue.x+iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x-iLen-iMMMTemp,ptValue.y+iLen+iMMMTemp);
		rectC=CRect(ptValue.x-2*iMMMTemp,ptValue.y-2*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pObj1);
		break;
	case 4: ////	+.	
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen+iMMMTemp,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen+iMMMTemp);
		rectC=CRect(ptValue.x-2*iMMMTemp,ptValue.y-2*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
//		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
//		pDC->SelectObject(pObj1);
		break;
	case 5: ////	x.
		pDC->MoveTo(ptValue.x-iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x+iLen+iMMMTemp,ptValue.y+iLen+iMMMTemp);
		pDC->MoveTo(ptValue.x+iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x-iLen-iMMMTemp,ptValue.y+iLen+iMMMTemp);
		rectC=CRect(ptValue.x-2*iMMMTemp,ptValue.y-2*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
//		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
//		pDC->SelectObject(pObj1);
		break;
	case 6: ////	.
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen+iMMMTemp,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen+iMMMTemp);
		rectC=CRect(ptValue.x-2*iMMMTemp,ptValue.y-2*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
		brush.CreateSolidBrush(m_ulColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 7:	////	x.
		pDC->MoveTo(ptValue.x-iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x+iLen+iMMMTemp,ptValue.y+iLen+iMMMTemp);
		pDC->MoveTo(ptValue.x+iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x-iLen-iMMMTemp,ptValue.y+iLen+1);
		rectC=CRect(ptValue.x-2*iMMMTemp,ptValue.y-2*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
		brush.CreateSolidBrush(m_ulColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 8://.
		rectC=CRect(ptValue.x-2*iMMMTemp,ptValue.y-2*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
		brush.CreateSolidBrush(m_ulColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 9:
		rectC=CRect(ptValue.x-3*iMMMTemp,ptValue.y-3*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
		brush.CreateSolidBrush(m_ulColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 10:
		rectC=CRect(ptValue.x-2*iMMMTemp,ptValue.y-2*iMMMTemp,ptValue.x+4*iMMMTemp,ptValue.y+4*iMMMTemp);
		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pObj1);
		rectC=CRect(ptValue.x-1*iMMMTemp,ptValue.y-1*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
		brush.CreateSolidBrush(m_ulColor);//(m_ulColor);
		pOldBrush=pDC->SelectObject(&brush);
		//pDC->Ellipse(rectC);
		{
		pDC->SetPixel(ptValue,m_ulColor);
		CPoint pt=ptValue+CPoint(1,0);
		pDC->SetPixel(pt,m_ulColor);
		pt=ptValue+CPoint(1,1);
		pDC->SetPixel(pt,m_ulColor);
		pt=ptValue+CPoint(0,1);
		pDC->SetPixel(pt,m_ulColor);
		}
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 11:
		rectC=CRect(ptValue.x-2*iMMMTemp,ptValue.y-2*iMMMTemp,ptValue.x+3*iMMMTemp,ptValue.y+3*iMMMTemp);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(PS_SOLID,1,RGB(0,0,0));
		pOldPen=pDC->SelectObject(&cp);
		brush.CreateSolidBrush(m_ulColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(m_uiLineStyle,m_iLineWidth,m_ulColor);
		break;
	case 12:
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(m_uiLineStyle,2,m_ulColor);
		pOldPen=pDC->SelectObject(&cp);
		pDC->MoveTo(ptValue.x-4-2*iMMMTemp,ptValue.y);
		pDC->LineTo(ptValue.x+4+2*iMMMTemp,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-4-2*iMMMTemp);
		pDC->LineTo(ptValue.x,ptValue.y+4+2*iMMMTemp);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(m_uiLineStyle,m_iLineWidth,m_ulColor);
		pOldPen=pDC->SelectObject(&cp);
		break;
	case 13:
		rectC=CRect(ptValue.x-4*iMMMTemp,ptValue.y-4*iMMMTemp,ptValue.x+(4+1)*iMMMTemp,ptValue.y+(4+1)*iMMMTemp);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(PS_SOLID,1,m_ulColor);
		pOldPen=pDC->SelectObject(&cp);
		pObj1=pDC->SelectStockObject(NULL_BRUSH);

		pDC->Ellipse(rectC);

		pDC->SelectObject(pObj1);

		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(m_uiLineStyle,m_iLineWidth,m_ulColor);
		break;
	default:
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen+iMMMTemp,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen+iMMMTemp);
		break;
	}
	pDC->SelectObject(pOldPen);
	cp.DeleteObject();			
}

void  CPowerDrawPoint::BeforePrinting(double fMMValue)
{
	iMMM=(int)fMMValue;
}

BOOL CPowerDrawPoint::PickIt(CPoint point)
{
	return TRUE;
}
void CPowerDrawPoint::GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	double fx=(double)m_ppv.dX;
	double fy=(double)m_ppv.dY;
	if(fx<fMinX) fMinX=fx;
	if(fx>fMaxX) fMaxX=fx;
	if(fy<fMinY) fMinY=fy;
	if(fy>fMaxY) fMaxY=fy;
}

void CPowerDrawPoint::OnColorChanged(COLORREF color)
{
	m_ulColor=color;
}
