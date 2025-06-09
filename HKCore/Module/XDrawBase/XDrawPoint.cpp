//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawPoint.cpp  CXDrawPoint


#include "stdafx.h"
#include "XDrawPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawPoint::CXDrawPoint()
{
	//初始化属性
	m_fX = 0;
	m_fY = 0;
	m_nPixel = 4;

	//初始化成员变量
	m_dwDrawStyle = 0;
}

CXDrawPoint::~CXDrawPoint()
{
}

long CXDrawPoint::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlReadOwn(oNode, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_fX);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_fY);
	xml_GetAttibuteValue(pXmlKeys->m_strPixelKey, oNode, m_nPixel);
	xml_GetAttibuteValue(pXmlKeys->m_strDrawStyleKey, oNode, m_dwDrawStyle);
	return 0;
}

long CXDrawPoint::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_fX);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_fY);
	xml_SetAttributeValue(pXmlKeys->m_strPixelKey, oElement, m_nPixel);
	xml_SetAttributeValue(pXmlKeys->m_strDrawStyleKey, oElement, m_dwDrawStyle);
	return 0;
}

long CXDrawPoint::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXDrawBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fX);
		BinarySerializeCalLen(oBinaryBuffer, m_fY);
		BinarySerializeCalLen(oBinaryBuffer, m_nPixel);
		BinarySerializeCalLen(oBinaryBuffer, m_dwDrawStyle);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fX);
		BinarySerializeRead(oBinaryBuffer, m_fY);
		BinarySerializeRead(oBinaryBuffer, m_nPixel);
		BinarySerializeRead(oBinaryBuffer, m_dwDrawStyle);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fX);
		BinarySerializeWrite(oBinaryBuffer, m_fY);
		BinarySerializeWrite(oBinaryBuffer, m_nPixel);
		BinarySerializeWrite(oBinaryBuffer, m_dwDrawStyle);
	}
	return 0;
}

BOOL CXDrawPoint::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXDrawBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXDrawPoint *p = (CXDrawPoint*)pObj;

	if(m_fX != p->m_fX)
	{
		return FALSE;
	}

	if(m_fY != p->m_fY)
	{
		return FALSE;
	}

	if(m_nPixel != p->m_nPixel)
	{
		return FALSE;
	}

	if(m_dwDrawStyle != p->m_dwDrawStyle)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXDrawPoint::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawBase::CopyOwn(pDest);

	CXDrawPoint *p = (CXDrawPoint*)pDest;

	p->m_fX = m_fX;
	p->m_fY = m_fY;
	p->m_nPixel = m_nPixel;
	p->m_dwDrawStyle = m_dwDrawStyle;
	return TRUE;
}

CBaseObject* CXDrawPoint::Clone()
{
	CXDrawPoint *p = new CXDrawPoint();
	Copy(p);
	return p;
}

void CXDrawPoint::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	pAxis->LogicPointToDevicePoint(m_fX, m_fY, &m_ptPoint);
}

void CXDrawPoint::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	xdraw_DrawPoint(pDC, m_ptPoint, m_dwDrawStyle, m_crForeColor, m_nPixel, fZoomRatio, ptOffset);
/*
	CPoint ptValue = m_ptPoint;
	ptValue.Offset(ptOffset);
	CPen cp,*pOldPen;

	UINT uiLineStyle = PS_SOLID;
	long nLineWidth = 1;
	cp.CreatePen(uiLineStyle,nLineWidth, m_crForeColor);
	pOldPen=pDC->SelectObject(&cp);

	CRect rectC;
	CBrush brush,*pOldBrush;
	CGdiObject *pObj1;
	int iLen = (int)(m_nPixel  * fZoomRatio);

	switch(m_dwDrawStyle)
	{
	case 0:	////	+ 
		pDC->MoveTo(ptValue.x-iLen,ptValue.y);
		pDC->LineTo(ptValue.x+iLen,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-iLen);
		pDC->LineTo(ptValue.x,ptValue.y+iLen);
		break;
	case 1:	////	x
		pDC->MoveTo(ptValue.x-iLen,ptValue.y-iLen);
		pDC->LineTo(ptValue.x+iLen,ptValue.y+iLen);
		pDC->MoveTo(ptValue.x+iLen,ptValue.y-iLen);
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
		brush.CreateSolidBrush(m_crForeColor);
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
		brush.CreateSolidBrush(m_crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 8://.
		rectC=CRect(ptValue.x-2*fZoomRatio,ptValue.y-2*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		brush.CreateSolidBrush(m_crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		break;
	case 9:
		rectC=CRect(ptValue.x-3*fZoomRatio,ptValue.y-3*fZoomRatio,ptValue.x+3*fZoomRatio,ptValue.y+3*fZoomRatio);
		brush.CreateSolidBrush(m_crForeColor);
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
		brush.CreateSolidBrush(m_crForeColor);//(m_crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		//pDC->Ellipse(rectC);
		{
			pDC->SetPixel(ptValue,m_crForeColor);
			CPoint pt=ptValue+CPoint(1,0);
			pDC->SetPixel(pt,m_crForeColor);
			pt=ptValue+CPoint(1,1);
			pDC->SetPixel(pt,m_crForeColor);
			pt=ptValue+CPoint(0,1);
			pDC->SetPixel(pt,m_crForeColor);
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
		brush.CreateSolidBrush(m_crForeColor);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(rectC);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(uiLineStyle,nLineWidth,m_crForeColor);
		break;
	case 12:
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(uiLineStyle,2,m_crForeColor);
		pOldPen=pDC->SelectObject(&cp);
		pDC->MoveTo(ptValue.x-4-2*fZoomRatio,ptValue.y);
		pDC->LineTo(ptValue.x+4+2*fZoomRatio,ptValue.y);
		pDC->MoveTo(ptValue.x,ptValue.y-4-2*fZoomRatio);
		pDC->LineTo(ptValue.x,ptValue.y+4+2*fZoomRatio);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(uiLineStyle,nLineWidth,m_crForeColor);
		pOldPen=pDC->SelectObject(&cp);
		break;
	case 13:
		rectC=CRect(ptValue.x-4*fZoomRatio,ptValue.y-4*fZoomRatio,ptValue.x+(4+1)*fZoomRatio,ptValue.y+(4+1)*fZoomRatio);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(PS_SOLID,1,m_crForeColor);
		pOldPen=pDC->SelectObject(&cp);
		pObj1=pDC->SelectStockObject(NULL_BRUSH);

		pDC->Ellipse(rectC);

		pDC->SelectObject(pObj1);

		pDC->SelectObject(pOldPen);
		cp.DeleteObject();
		cp.CreatePen(uiLineStyle,nLineWidth,m_crForeColor);
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
*/
}

void CXDrawPoint::Pick(const CPoint &point, CExBaseList &oList)
{
	
}

void CXDrawPoint::GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	fMinY = min(m_fY, fMinY);
	fMinY = min(m_fY, fMinY);

	fMinX = min(m_fX, fMinX);
	fMinX = min(m_fX, fMinX);
}
