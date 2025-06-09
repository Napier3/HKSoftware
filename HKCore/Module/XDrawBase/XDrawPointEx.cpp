//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawPoint.cpp  CXDrawPoint_Ex


#include "stdafx.h"
#include "XDrawPointEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawPoint_Ex::CXDrawPoint_Ex()
{
	//初始化属性
	m_fX = 0;
	m_fY = 0;
	m_nPixel = 4;

	//初始化成员变量
	m_dwDrawStyle = 0;
}

CXDrawPoint_Ex::CXDrawPoint_Ex(double *x, double *y)
: CXDrawData_Point_Ex(x, y)
{
	//初始化属性
	m_nPixel = 4;

	//初始化成员变量
	m_dwDrawStyle = 0;
}

CXDrawPoint_Ex::~CXDrawPoint_Ex()
{
}
// 
// long CXDrawPoint_Ex::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	CXDrawBase::XmlReadOwn(oNode, pXmlRWKeys);
// 	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_fX);
// 	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_fY);
// 	xml_GetAttibuteValue(pXmlKeys->m_strPixelKey, oNode, m_nPixel);
// 	xml_GetAttibuteValue(pXmlKeys->m_strDrawStyleKey, oNode, m_dwDrawStyle);
// 	return 0;
// }
// 
// long CXDrawPoint_Ex::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	CXDrawBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
// 	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_fX);
// 	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_fY);
// 	xml_SetAttributeValue(pXmlKeys->m_strPixelKey, oElement, m_nPixel);
// 	xml_SetAttributeValue(pXmlKeys->m_strDrawStyleKey, oElement, m_dwDrawStyle);
// 	return 0;
// }
// 
// long CXDrawPoint_Ex::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
// {
// 	CXDrawBase::SerializeOwn(oBinaryBuffer);
// 	if(oBinaryBuffer.IsCalSizeMode())
// 	{
// 		BinarySerializeCalLen(oBinaryBuffer, m_fX);
// 		BinarySerializeCalLen(oBinaryBuffer, m_fY);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nPixel);
// 		BinarySerializeCalLen(oBinaryBuffer, m_dwDrawStyle);
// 	}
// 	else if(oBinaryBuffer.IsReadMode())
// 	{
// 		BinarySerializeRead(oBinaryBuffer, m_fX);
// 		BinarySerializeRead(oBinaryBuffer, m_fY);
// 		BinarySerializeRead(oBinaryBuffer, m_nPixel);
// 		BinarySerializeRead(oBinaryBuffer, m_dwDrawStyle);
// 	}
// 	else if(oBinaryBuffer.IsWriteMode())
// 	{
// 		BinarySerializeWrite(oBinaryBuffer, m_fX);
// 		BinarySerializeWrite(oBinaryBuffer, m_fY);
// 		BinarySerializeWrite(oBinaryBuffer, m_nPixel);
// 		BinarySerializeWrite(oBinaryBuffer, m_dwDrawStyle);
// 	}
// 	return 0;
// }

BOOL CXDrawPoint_Ex::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXDrawBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXDrawPoint_Ex *p = (CXDrawPoint_Ex*)pObj;

	if(*m_fX != *p->m_fX)
	{
		return FALSE;
	}

	if(*m_fY != *p->m_fY)
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

BOOL CXDrawPoint_Ex::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawBase::CopyOwn(pDest);

	CXDrawPoint_Ex *p = (CXDrawPoint_Ex*)pDest;

	p->m_fX = m_fX;
	p->m_fY = m_fY;
	p->m_nPixel = m_nPixel;
	p->m_dwDrawStyle = m_dwDrawStyle;
	return TRUE;
}

CBaseObject* CXDrawPoint_Ex::Clone()
{
	CXDrawPoint_Ex *p = new CXDrawPoint_Ex();
	Copy(p);
	return p;
}

void CXDrawPoint_Ex::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	pAxis->LogicPointToDevicePoint(*m_fX, *m_fY, &m_ptPoint);
}

void CXDrawPoint_Ex::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	xdraw_DrawPoint(pDC, m_ptPoint, m_dwDrawStyle, m_crForeColor, m_nPixel, fZoomRatio, ptOffset);
}

void CXDrawPoint_Ex::Pick(const CPoint &point, CExBaseList &oList)
{
	
}

void CXDrawPoint_Ex::GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	fMinY = min(*m_fY, fMinY);
	fMinY = min(*m_fY, fMinY);

	fMinX = min(*m_fX, fMinX);
	fMinX = min(*m_fX, fMinX);
}
