// ComtradeDrawBaseClass.cpp: implementation of the CComtradeDrawBaseClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComtradeDrawBaseClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComtradeDrawBaseClass::CComtradeDrawBaseClass()
{
	Init();
// 	m_strDrawType="A";
// 	m_lfDrawFont=InitLogFont (-14,0,0,0,400,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
}

CComtradeDrawBaseClass::CComtradeDrawBaseClass(CString strType)
{
	Init();
// 	m_strDrawType=strType;
// 	m_lfDrawFont=InitLogFont (-14,0,0,0,400,'\0','\0','\0','\0','\x1','\x2','\x1','1',"Arial");
}

CComtradeDrawBaseClass::~CComtradeDrawBaseClass()
{

}

void CComtradeDrawBaseClass::Init()
{
// 	m_pMemDC = NULL;				//内存绘制指针
// 	m_pBitmap = NULL;				//新位图
// 	m_pOldBMP = NULL;				//原位图
}

// void CComtradeDrawBaseClass::DrawIt(CComtradeDataBaseClass*pData,CPoint*pPoint,CAxisReference*axisRef,CDC*pDC)
// {
// 
// }
// 
// void CComtradeDrawBaseClass::DrawIt(CDC*pDC,CComtradeDataBaseClass*pData,CMemBuffer_CPoint*pPointBuff,CAxisReference*axisRef,int iBeginIndex,int iEndIndex,int iMode)
// {
// 
// }
// void CComtradeDrawBaseClass::DrawCHTitle(CDC*pDC,CComtradeDataBaseClass*pData,int iMode,int iState,COLORREF crBack)
// {
// 
// }


DWORD CComtradeDrawBaseClass::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
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

CSize CComtradeDrawBaseClass::CalLayout(CSize &szDraw)
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

CSize CComtradeDrawBaseClass::Layout(CPoint &ptTopLeft)
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


BOOL CComtradeDrawBaseClass::GetTimeByCursorPos(int iXL,int iXR,float &fTime1,float &fTime2)
{
// 	CPoint pt=CPoint(iXL,0);
// 	float fTemp=0;
// 	odDef.DevicePointToLogicPoint(pt,&fTime1,&fTemp);
// 	pt.x=iXR;
// 	odDef.DevicePointToLogicPoint(pt,&fTime2,&fTemp);
	return TRUE;
}
BOOL CComtradeDrawBaseClass::GetXPosByTimeVal(float fTime1,int &iXPos)
{
// 	CPoint pt=CPoint(0,0);
// 	float fTemp=0;
// 	odDef.LogicPointToDevicePoint(fTime1,fTemp,&pt);
// 	iXPos=pt.x;
	return TRUE;
}
