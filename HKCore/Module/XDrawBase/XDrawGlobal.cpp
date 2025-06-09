//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawGlobal.cpp

#include "stdafx.h"
#include "XDrawGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXDrawXmlRWKeys

CXDrawXmlRWKeys* CXDrawXmlRWKeys::g_pXmlKeys = NULL;
long CXDrawXmlRWKeys::g_nDWRef = 0;


CXDrawXmlRWKeys::CXDrawXmlRWKeys()
{
	m_strCXDrawMngrKey = L"draw-mngr";
	m_strCXDrawListKey = L"draw-list";
	m_strCXDrawArcKey = L"arc";
	m_strCXDrawCircleKey = L"circle";
	m_strCXDrawLineKey = L"line";
	m_strCXDrawPolylineKey = L"polyline";
	m_strCXDrawLineRKey = L"liner";
	m_strCXDrawPointKey = L"point";
	m_strCXDrawTextKey = L"text";
	m_strColorKey = L"color";
	m_strForeColorKey = L"fg-color";
	m_strBackColorKey = L"bk-color";
	m_strEnableKey = L"enable";
	m_strShowKey = L"show";
	m_strStateKey = L"state";
	m_strXKey = L"x";
	m_strYKey = L"y";
	m_strPixelKey = L"pixel";
	m_strDrawStyleKey = L"point-style";
	m_strBXKey = L"x-b";
	m_strBYKey = L"y-b";
	m_strEXKey = L"x-e";
	m_strEYKey = L"y-e";
	m_strStyleKey = L"style";
	m_strWidthKey = L"width";
	m_strHeightKey = L"height";
	m_strXCenterKey = L"x-c";
	m_strYCenterKey = L"y-c";
	m_strRadiusXKey = L"x-r";
	m_strRadiusYKey = L"y-r";
	m_strRadiusKey = L"r";
	m_strAngleBeginKey = L"angle-b";
	m_strAngleEndKey = L"angle-e";
	m_strAngleKey = L"angle";
	m_strAxisKey = L"axis";
	m_strXMaxKey = L"x-max";
	m_strYMaxKey = L"y-max";
	m_strXMinKey = L"x-min";
	m_strYMinKey = L"y-min";
}

CXDrawXmlRWKeys::~CXDrawXmlRWKeys()
{
}

CXDrawXmlRWKeys* CXDrawXmlRWKeys::Create()
{
	g_nDWRef++;

	if (g_nDWRef == 1)
	{
		g_pXmlKeys = new CXDrawXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CXDrawXmlRWKeys::Release()
{
	g_nDWRef--;

	if (g_nDWRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CXDrawConstGlobal

long CXDrawConstGlobal::g_nGlobalRef = 0;
CXDrawConstGlobal* CXDrawConstGlobal::g_pGlobal = NULL;


CXDrawConstGlobal::CXDrawConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CXDrawConstGlobal::~CXDrawConstGlobal()
{
}

CXDrawConstGlobal* CXDrawConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CXDrawConstGlobal();
	}

	return g_pGlobal;
}

void CXDrawConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;



void xdraw_DrawPoint(CDC *pDC, CPoint &ptPoint, DWORD dwDrawStyle, COLORREF crForeColor, long nPixel,  double fZoomRatio,const CPoint &ptOffset)
{
	CPoint ptValue = ptPoint;
	ptValue.Offset(ptOffset);
	CPen cp,*pOldPen;

	UINT uiLineStyle = PS_SOLID;
	long nLineWidth = 1;
	cp.CreatePen(uiLineStyle,nLineWidth, crForeColor);
	pOldPen=pDC->SelectObject(&cp);

	CRect rectC;
	CBrush brush,*pOldBrush;
	CGdiObject *pObj1;
	int iLen = (int)(nPixel  * fZoomRatio);

	switch(dwDrawStyle)
	{
	case 0:	////	+ 
		pDC->MoveTo(ptValue.x-iLen+1,ptValue.y);
		pDC->LineTo(ptValue.x+iLen,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen+1);
		pDC->LineTo(ptValue.x,ptValue.y+iLen);
		break;
	case 1:	////	x
		pDC->MoveTo(ptValue.x-iLen+1,ptValue.y-iLen+1);
		pDC->LineTo(ptValue.x+iLen,ptValue.y+iLen);
		pDC->MoveTo(ptValue.x+iLen-1,ptValue.y-iLen+1);
		pDC->LineTo(ptValue.x-iLen,ptValue.y+iLen);
		break;
	case 2:	////	+o	
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen);
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pObj1);
		break;
	case 3:	////	xo
		pDC->MoveTo(ptValue.x-iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x+iLen,ptValue.y+iLen);
		pDC->MoveTo(ptValue.x+iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x-iLen,ptValue.y+iLen);
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pObj1);
		break;
	case 4: ////	+.	
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen);
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		//		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
		//		pDC->SelectObject(pObj1);
		break;
	case 5: ////	x.
		pDC->MoveTo(ptValue.x-iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x+iLen,ptValue.y+iLen);
		pDC->MoveTo(ptValue.x+iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x-iLen,ptValue.y+iLen);
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		//		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
		//		pDC->SelectObject(pObj1);
		break;
	case 6: ////	.
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen);
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		brush.CreateSolidBrush(crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 7:	////	x.
		pDC->MoveTo(ptValue.x-iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x+iLen,ptValue.y+iLen);
		pDC->MoveTo(ptValue.x+iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x-iLen,ptValue.y+iLen+1);
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		brush.CreateSolidBrush(crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 8://.
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		brush.CreateSolidBrush(crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 9:
		rectC=CRect(ptValue.x-3*fZoomRatio,ptValue.y-3*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		brush.CreateSolidBrush(crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 10:
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+4*fZoomRatio,ptValue.y+4*fZoomRatio);
		pObj1=pDC->SelectStockObject(NULL_BRUSH);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pObj1);
		rectC=CRect(ptValue.x-1*fZoomRatio,ptValue.y-1*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		brush.CreateSolidBrush(crForeColor);//(crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		//pDC->Ellipse(rectC);
		{
			pDC->SetPixel(ptValue,crForeColor);
			CPoint pt=ptValue+CPoint(1,0);
			pDC->SetPixel(pt,crForeColor);
			pt=ptValue+CPoint(1,1);
			pDC->SetPixel(pt,crForeColor);
			pt=ptValue+CPoint(0,1);
			pDC->SetPixel(pt,crForeColor);
		}
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 11:
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(PS_SOLID,1,RGB(0,0,0));
		pOldPen=pDC->SelectObject(&cp);
		brush.CreateSolidBrush(crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(uiLineStyle,nLineWidth,crForeColor);
		break;
	case 12:
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(uiLineStyle,2,crForeColor);
		pOldPen=pDC->SelectObject(&cp);
		pDC->MoveTo(ptValue.x-4-2*fZoomRatio,ptValue.y);
		pDC->LineTo(ptValue.x+4+2*fZoomRatio,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-4-2*fZoomRatio);
		pDC->LineTo(ptValue.x,ptValue.y+4+2*fZoomRatio);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(uiLineStyle,nLineWidth,crForeColor);
		pOldPen=pDC->SelectObject(&cp);
		break;
	case 13:
		rectC=CRect(ptValue.x-4*fZoomRatio,ptValue.y-4*fZoomRatio,ptValue.x+(4+1)*fZoomRatio,ptValue.y+(4+1)*fZoomRatio);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(PS_SOLID,1,crForeColor);
		pOldPen=pDC->SelectObject(&cp);
		pObj1=pDC->SelectStockObject(NULL_BRUSH);

		pDC->Ellipse(rectC);

		pDC->SelectObject(pObj1);

		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(uiLineStyle,nLineWidth,crForeColor);
		break;
	default:
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen);
		break;
	}
	pDC->SelectObject(pOldPen);
	cp.DeleteObject();	
}

void xdraw_DrawPointLine(CDC *pDC, CPoint *pPointBuffer, long nCount, DWORD dwDrawStyle, COLORREF crForeColor, long nPixel,  double fZoomRatio,const CPoint &ptOffset)
{
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		xdraw_DrawPoint(pDC, pPointBuffer[nIndex], dwDrawStyle, crForeColor, nPixel, fZoomRatio, ptOffset);
	}
}

