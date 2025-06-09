// ComtradeAnalogDraw.cpp: implementation of the CComtradeAnalogDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComtradeAnalogDraw.h"
#include "..\ComtradeAnalogData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CComtradeAnalogDraw::CComtradeAnalogDraw()
{

}
CComtradeAnalogDraw::CComtradeAnalogDraw(CString chType):CComtradeDrawBaseClass(chType)
{

}

CComtradeAnalogDraw::~CComtradeAnalogDraw()
{

}


DWORD CComtradeAnalogDraw::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	m_pXDrawDataRef = pData;
	// 
	// 	XCreateElement_Title(pData, pParentWnd);
	// 	XCreateElement_Chs(pData, pParentWnd);
	// 
	// 	m_pGridCtrlTitle->m_pCtrlChsGrid = m_pGridCtrlChs;
	// 	m_pGridCtrlChs->m_pCtrlTitleGrid = m_pGridCtrlTitle;
	// 
	// 	ReSetTiTleChsWidth();

	CSize sz;
	CalLayout(sz);

	return XCREATE_SUCC;
}

CSize CComtradeAnalogDraw::CalLayout(CSize &szDraw)
{
	// 	if (m_bShowChs)
	// 	{
	// 		m_nWidth = max(m_pGridCtrlTitle->GetVirtualWidth(), m_pGridCtrlChs->GetVirtualWidth());
	// 		m_nHeight = m_pGridCtrlTitle->GetVirtualHeight() + m_pGridCtrlChs->GetVirtualHeight();
	// 	}
	// 	else
	// 	{
	// 		m_nWidth = m_pGridCtrlTitle->GetVirtualWidth();
	// 		m_nHeight = m_pGridCtrlTitle->GetVirtualHeight();
	// 	}

	CSize sz(m_nWidth, m_nHeight);

	return sz;
}

CSize CComtradeAnalogDraw::Layout(CPoint &ptTopLeft)
{
	CPoint pt = ptTopLeft;
	m_ptTopLeft = ptTopLeft;
	// 	m_pGridCtrlTitle->SetPosTopLeft(pt);
	// 
	// 	if (m_bShowChs)
	// 	{
	// 		pt.y += m_pGridCtrlTitle->GetVirtualHeight();
	// 		m_pGridCtrlChs->SetPosTopLeft(pt);
	// 
	// 		//调整通道之间的连线@@@
	// 	}
	// 	else
	// 	{
	// 		//调整控制块之间的连线@@@
	// 	}

	// 	LayoutLines();
	// 	LayoutCtrlLine();

	CSize sz(m_nWidth, m_nHeight);
	return sz;
}


#if 0
void CComtradeAnalogDraw::DrawIt(CComtradeDataBaseClass*pData,CPoint*pPoint,CAxisReference*axisRef,CDC*pDC)
{
	CComtradeAnalogData*pAnalog=(CComtradeAnalogData*)pData;
}

void CComtradeAnalogDraw::DrawIt(CDC*pDC,CComtradeDataBaseClass*pData,CMemBuffer_CPoint*pPointBuff,CAxisReference*axisRef,int iBeginIndex,int iEndIndex,int iMode)
{
	CComtradeAnalogData*pAnalog=(CComtradeAnalogData*)pData;
	int iIndex=0;
	float fVal=0;
	CPoint	*pPoint=NULL;
	float	*pFloatVal=NULL;
	int iBMemBuff	=iBeginIndex / MEMBUFFER_MAX_ONEBUFFER;
	int iBMemIndex	=iBeginIndex - iBMemBuff * MEMBUFFER_MAX_ONEBUFFER;
	int iEMemBuff	=iEndIndex / MEMBUFFER_MAX_ONEBUFFER;
	int iEMemIndex	=iEndIndex - iEMemBuff * MEMBUFFER_MAX_ONEBUFFER;

	CPen*pOldPen,pen;
	pen.CreatePen(pAnalog->m_ulCHLineType,1,pAnalog->m_crCHLine);
	pOldPen=pDC->SelectObject(&pen);

	if(iBMemBuff==iEMemBuff)
	{
		pPoint=pPointBuff->m_pPointData[iBMemBuff];
		pFloatVal=pAnalog->m_pAnalogMemBuf->m_pfData[iBMemBuff];
		for(iIndex=iBMemIndex;iIndex<=iEMemIndex;iIndex++)
		{
			fVal=-pFloatVal[iIndex] * axisRef->m_fOneYGapValue+axisRef->m_ptCenterLogInDv.y;
			pPoint[iIndex].y=(int)fVal;
		}
		pDC->Polyline(&pPoint[iBMemIndex],iEMemIndex-iBMemIndex+1);
	}
	else
	{
		//第一个缓冲区，缓冲区数据从iBMemIndex到MEMBUFFER_MAX_ONEBUFFER-1;
		pPoint=pPointBuff->m_pPointData[iBMemBuff];
		pFloatVal=pAnalog->m_pAnalogMemBuf->m_pfData[iBMemBuff];
		for (int iIndex=iBMemIndex;iIndex<=MEMBUFFER_MAX_ONEBUFFER-1;iIndex++)
		{
			fVal=-pFloatVal[iIndex] * axisRef->m_fOneYGapValue+axisRef->m_ptCenterLogInDv.y;
			pPoint[iIndex].y=(int)(fVal);
		}
		pDC->Polyline(&pPoint[iBMemIndex],MEMBUFFER_MAX_ONEBUFFER-iBMemIndex);
		//中间的缓冲区，缓冲区编号iBMemBuff+1到iEMemBuff；
		for(int iMemBuffIndex=iBMemBuff+1;iMemBuffIndex<iEMemBuff;iMemBuffIndex++)
		{
			pPoint=pPointBuff->m_pPointData[iMemBuffIndex];
			pFloatVal=pAnalog->m_pAnalogMemBuf->m_pfData[iMemBuffIndex];
			for (int iIndex=0;iIndex<=MEMBUFFER_MAX_ONEBUFFER-1;iIndex++)
			{
				fVal=-pFloatVal[iIndex] * axisRef->m_fOneYGapValue+axisRef->m_ptCenterLogInDv.y;
				pPoint[iIndex].y=(int)(fVal);
			}
			pDC->Polyline(pPoint,MEMBUFFER_MAX_ONEBUFFER);
		}
		//最后一个缓冲区，缓冲区编号iEMemBuff，数据从0导到iEMemIndex；
		pPoint=pPointBuff->m_pPointData[iEMemBuff];
		pFloatVal=pAnalog->m_pAnalogMemBuf->m_pfData[iEMemBuff];
		for (iIndex=0;iIndex<=iEMemIndex;iIndex++)
		{
			fVal=-pFloatVal[iIndex] * axisRef->m_fOneYGapValue+axisRef->m_ptCenterLogInDv.y;
			pPoint[iIndex].y=(int)(fVal);
		}
		pDC->Polyline(pPoint,iEMemIndex+1);
	}

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

}

void CComtradeAnalogDraw::DrawCHTitle(CDC*pDC,CComtradeDataBaseClass*pData,int iMode,int iState,COLORREF crBack)
{
	CComtradeAnalogData*pAnalog=(CComtradeAnalogData*)pData;

	CPoint pt;

	CPen*pOldPen,pen;
	pen.CreatePen(pAnalog->m_ulCHLineType,1,pAnalog->m_crCHLine);
	pOldPen=pDC->SelectObject(&pen);

	if(iMode==0)
	{
		//绘制曲线的线型
		pt.x=pAnalog->m_rectCHPosition.right-80;pt.y=pAnalog->m_rectCHPosition.CenterPoint().y;
		pDC->MoveTo(pt);
		pt.x=pAnalog->m_rectCHPosition.right-10;
		pDC->LineTo(pt);
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	//通道名称
	if(iState==0)//normal
	{
		pen.CreatePen(PS_DOT,1,crBack);
	}
	else//active
	{
		pen.CreatePen(PS_DOT,1,RGB(0,0,0));
	}
	pOldPen=pDC->SelectObject(&pen);
	
	CPoint point[5];	
	point[0].x=pAnalog->m_rectCHPosition.left-2;		point[0].y=pAnalog->m_rectCHPosition.top-1;
	point[1].x=pAnalog->m_rectCHPosition.right-10;		point[1].y=pAnalog->m_rectCHPosition.top-1;
	point[2].x=pAnalog->m_rectCHPosition.right-10;		point[2].y=pAnalog->m_rectCHPosition.bottom-2;
	point[3].x=pAnalog->m_rectCHPosition.left-2;		point[3].y=pAnalog->m_rectCHPosition.bottom-2;
	point[4]=point[0];
	pDC->Polyline(point,5);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	
	char chTitle[100];
	strcpy(chTitle,pAnalog->m_strCHName);
	if(iMode==1)
	{
		strcat(chTitle,"/");
		strcat(chTitle,pAnalog->m_strCHUnit);
	}
	CRect rect=pAnalog->m_rectCHPosition;rect.top-=2;rect.bottom-=2;
	CmDrawTextRect(pDC,chTitle,RGB(0,0,0),&rect,RGB(0,0,0),m_lfDrawFont,TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}

#endif