// ComtradeDigitalDraw.cpp: implementation of the CComtradeDigitalDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComtradeBinaryDraw.h"
#include "..\ComtradeBinaryData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComtradeBinaryDraw::CComtradeBinaryDraw()
{

}

CComtradeBinaryDraw::CComtradeBinaryDraw(CString chType):CComtradeDrawBaseClass(chType)
{

}

CComtradeBinaryDraw::~CComtradeBinaryDraw()
{

}


DWORD CComtradeBinaryDraw::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
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

CSize CComtradeBinaryDraw::CalLayout(CSize &szDraw)
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

CSize CComtradeBinaryDraw::Layout(CPoint &ptTopLeft)
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
	// 		//����ͨ��֮�������@@@
	// 	}
	// 	else
	// 	{
	// 		//�������ƿ�֮�������@@@
	// 	}

	// 	LayoutLines();
	// 	LayoutCtrlLine();

	CSize sz(m_nWidth, m_nHeight);
	return sz;
}

// 
// void CComtradeDigitalDraw::DrawIt(CComtradeDataBaseClass*pData,CPoint*pPoint,CAxisReference*axisRef,CDC*pDC)
// {
// 	CComtradeDigitalData*pDigital=(CComtradeDigitalData*)pData;
// }
// void CComtradeDigitalDraw::DrawIt(CDC*pDC,CComtradeDataBaseClass*pData,CMemBuffer_CPoint*pPointBuff,CAxisReference*axisRef,int iBeginIndex,int iEndIndex,int iMode)
// {
// 	CComtradeDigitalData*pDigital=(CComtradeDigitalData*)pData;
// 
// 	int iBMemBuff	=iBeginIndex / MEMBUFFER_MAX_ONEBUFFER;
// 	int iBMemIndex	=iBeginIndex - iBMemBuff * MEMBUFFER_MAX_ONEBUFFER;
// 	int iEMemBuff	=iEndIndex / MEMBUFFER_MAX_ONEBUFFER;
// 	int iEMemIndex	=iEndIndex - iEMemBuff * MEMBUFFER_MAX_ONEBUFFER;	
// 	//����һ����
// 	CPen pen,*pOldPen;
// 	pen.CreatePen(PS_SOLID,1,pDigital->m_crCHLine);
// 	pOldPen=pDC->SelectObject(&pen);
// 	int iy=pDigital->m_rectCHPosition.CenterPoint().y;
// 
// 	pDC->MoveTo(pPointBuff->m_pPointData[iBMemBuff][iBMemIndex].x,iy);
// 	pDC->LineTo(pPointBuff->m_pPointData[iEMemBuff][iEMemIndex].x,iy);
// 
// 	pDC->SelectObject(pOldPen);
// 	pen.DeleteObject();
// 
// 	//���ƶ�������
// 	//ѡ���ͼ�������ɫ
// 	CBrush brush,*pOldBrush;
// 	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
// 	pOldPen=pDC->SelectObject(&pen);
// 	brush.CreateSolidBrush(pDigital->m_crCHLine);
// 	pOldBrush=pDC->SelectObject(&brush);
// 
// 	char *pCharVal=NULL;
// 	CPoint	*pPoint=NULL;
// 
// 	int iIndex=0;
// 	int iFlag=0;
// 	CRect rectDigital;
// 	rectDigital.top=iy-4;
// 	rectDigital.bottom=iy+4;
// 	if(iBMemBuff==iEMemBuff)
// 	{
// 		pCharVal=pDigital->m_pDigitalMemBuff->m_pchData[iBMemBuff];
// 		pPoint=pPointBuff->m_pPointData[iBMemBuff];
// 		for(iIndex=iBMemIndex;iIndex<=iEMemIndex;iIndex++)
// 		{
// 			if(pCharVal[iIndex]>'0')
// 			{	if(iFlag==0)
// 				{	iFlag=1;
// 					rectDigital.left=pPoint[iIndex].x;
// 				}
// 			}
// 			else
// 			{	if(iFlag==1)
// 				{	iFlag=0;	rectDigital.right=pPoint[iIndex].x+1;
// 					pDC->Rectangle(rectDigital);
// 				}
// 			}
// 		}
// 		if(iFlag!=0)
// 		{
// 			rectDigital.right=pPoint[iIndex-1].x+1;
// 			pDC->Rectangle(rectDigital);
// 		}
// 	}
// 	else
// 	{
// 		//��һ�������������������ݴ�iBMemIndex��MEMBUFFER_MAX_ONEBUFFER-1;
// 		pCharVal=pDigital->m_pDigitalMemBuff->m_pchData[iBMemBuff];
// 		pPoint=pPointBuff->m_pPointData[iBMemBuff];
// 		for(iIndex=iBMemIndex;iIndex<=iEMemIndex;iIndex++)
// 		{
// 			if(pCharVal[iIndex]>'0')
// 			{	if(iFlag==0)
// 				{	iFlag=1;
// 					rectDigital.left=pPoint[iIndex].x;
// 				}
// 			}
// 			else
// 			{	if(iFlag==1)
// 				{	iFlag=0;	rectDigital.right=pPoint[iIndex].x+1;
// 					pDC->Rectangle(rectDigital);
// 				}
// 			}
// 		}
// 		//�м�Ļ����������������iBMemBuff+1��iEMemBuff��
// 		for(int iMemBuffIndex=iBMemBuff+1;iMemBuffIndex<iEMemBuff;iMemBuffIndex++)
// 		{
// 			pCharVal=pDigital->m_pDigitalMemBuff->m_pchData[iMemBuffIndex];
// 			pPoint=pPointBuff->m_pPointData[iMemBuffIndex];
// 			for(iIndex=0;iIndex<=MEMBUFFER_MAX_ONEBUFFER-1;iIndex++)
// 			{
// 				if(pCharVal[iIndex]>'0')
// 				{	if(iFlag==0)
// 					{	iFlag=1;rectDigital.left=pPoint[iIndex].x;
// 					}
// 				}
// 				else
// 				{	if(iFlag==1)
// 					{	iFlag=0;	rectDigital.right=pPoint[iIndex].x+1;
// 						pDC->Rectangle(rectDigital);
// 					}
// 				}
// 			}
// 		}
// 		//���һ�������������������iEMemBuff�����ݴ�0����iEMemIndex��
// 		pCharVal=pDigital->m_pDigitalMemBuff->m_pchData[iEMemBuff];
// 		pPoint=pPointBuff->m_pPointData[iEMemBuff];
// 		for(iIndex=0;iIndex<=iEMemIndex;iIndex++)
// 		{
// 			if(pCharVal[iIndex]>'0')
// 			{	if(iFlag==0)
// 				{	iFlag=1;	rectDigital.left=pPoint[iIndex].x;
// 				}
// 			}
// 			else
// 			{	if(iFlag==1)
// 				{	iFlag=0;	rectDigital.right=pPoint[iIndex].x+1;
// 					pDC->Rectangle(rectDigital);
// 				}
// 			}
// 		}
// 		//////////////////////////////////////////////////////////////////////
// 		if(iFlag!=0)
// 		{
// 			rectDigital.right=pPoint[iIndex-1].x+1;
// 			pDC->Rectangle(rectDigital);
// 		}
// 	}
// 	pDC->SelectObject(pOldPen);
// 	pen.DeleteObject();
// 	pDC->SelectObject(pOldBrush);
// 	brush.DeleteObject();	
// 	return;
// }
// 
// void CComtradeDigitalDraw::DrawCHTitle(CDC*pDC,CComtradeDataBaseClass*pData,int iMode,int iState,COLORREF crBack)
// {
// 	CComtradeDigitalData*pDigital=(CComtradeDigitalData*)pData;
// 	//ͨ������
// 	CPen pen,*pOldPen;
// 	if(iState==0)//normal
// 	{
// 		pen.CreatePen(PS_DOT,1,crBack);
// 	}
// 	else//active
// 	{
// 		pen.CreatePen(PS_DOT,1,RGB(0,0,0));
// 	}
// 	pOldPen=pDC->SelectObject(&pen);
// 	
// 	CPoint point[5];	
// 	point[0].x=pDigital->m_rectCHPosition.left-2;		point[0].y=pDigital->m_rectCHPosition.top;
// 	point[1].x=pDigital->m_rectCHPosition.right-10;		point[1].y=pDigital->m_rectCHPosition.top;
// 	point[2].x=pDigital->m_rectCHPosition.right-10;		point[2].y=pDigital->m_rectCHPosition.bottom+2;
// 	point[3].x=pDigital->m_rectCHPosition.left-2;		point[3].y=pDigital->m_rectCHPosition.bottom+2;
// 	point[4]=point[0];
// 	pDC->Polyline(point,5);
// 	pDC->SelectObject(pOldPen);
// 	pen.DeleteObject();
// 
// 	char chTitle[100];
// 	strcpy(chTitle,pDigital->m_strCHName);
// 	CmDrawTextRect(pDC,chTitle,RGB(0,0,0),&pDigital->m_rectCHPosition,RGB(0,0,0),m_lfDrawFont,TRANSPARENT,DT_VCENTER|DT_LEFT,0);
// }
// 
// 
