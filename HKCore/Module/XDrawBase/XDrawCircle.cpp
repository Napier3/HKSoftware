//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawCircle.cpp  CXDrawCircle


#include "stdafx.h"
#include "XDrawCircle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawCircle::CXDrawCircle()
{
	//初始化属性
// 	m_fXCenter = 0;
// 	m_fYCenter = 0;
// 	m_fXRadius = 1;
// 	m_fYRadius = 1;

	//初始化成员变量
}

CXDrawCircle::~CXDrawCircle()
{
}

long CXDrawCircle::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlReadOwn(oNode, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXCenterKey, oNode, m_fXCenter);
	xml_GetAttibuteValue(pXmlKeys->m_strYCenterKey, oNode, m_fYCenter);
	xml_GetAttibuteValue(pXmlKeys->m_strRadiusXKey, oNode, m_fXRadius);
	xml_GetAttibuteValue(pXmlKeys->m_strRadiusYKey, oNode, m_fYRadius);

	return 0;
}

long CXDrawCircle::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXCenterKey, oElement, m_fXCenter);
	xml_SetAttributeValue(pXmlKeys->m_strYCenterKey, oElement, m_fYCenter);
	xml_SetAttributeValue(pXmlKeys->m_strRadiusXKey, oElement, m_fXRadius);
	xml_SetAttributeValue(pXmlKeys->m_strRadiusYKey, oElement, m_fYRadius);

	return 0;
}

long CXDrawCircle::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXDrawBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fXCenter);
		BinarySerializeCalLen(oBinaryBuffer, m_fYCenter);
		BinarySerializeCalLen(oBinaryBuffer, m_fXRadius);
		BinarySerializeCalLen(oBinaryBuffer, m_fYRadius);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fXCenter);
		BinarySerializeRead(oBinaryBuffer, m_fYCenter);
		BinarySerializeRead(oBinaryBuffer, m_fXRadius);
		BinarySerializeRead(oBinaryBuffer, m_fYRadius);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fXCenter);
		BinarySerializeWrite(oBinaryBuffer, m_fYCenter);
		BinarySerializeWrite(oBinaryBuffer, m_fXRadius);
		BinarySerializeWrite(oBinaryBuffer, m_fYRadius);
	}
	return 0;
}

BOOL CXDrawCircle::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXDrawBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXDrawCircle *p = (CXDrawCircle*)pObj;

	if(m_fXCenter != p->m_fXCenter)
	{
		return FALSE;
	}

	if(m_fYCenter != p->m_fYCenter)
	{
		return FALSE;
	}

	if(m_fXRadius != p->m_fXRadius)
	{
		return FALSE;
	}

	if(m_fYRadius != p->m_fYRadius)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXDrawCircle::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawBase::CopyOwn(pDest);

	CXDrawCircle *p = (CXDrawCircle*)pDest;

	p->m_fXCenter = m_fXCenter;
	p->m_fYCenter = m_fYCenter;
	p->m_fXRadius = m_fXRadius;
	p->m_fYRadius = m_fYRadius;

	return TRUE;
}

CBaseObject* CXDrawCircle::Clone()
{
	CXDrawCircle *p = new CXDrawCircle();
	Copy(p);
	return p;
}


void CXDrawCircle::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	CPoint pt;

	pAxis->LogicPointToDevicePoint(m_fXCenter - m_fXRadius, m_fYCenter - m_fYRadius, &pt);
	m_rcCircle.left = pt.x;
	m_rcCircle.top  = pt.y;

	pAxis->LogicPointToDevicePoint(m_fXCenter + m_fXRadius, m_fYCenter + m_fYRadius, &pt);
	m_rcCircle.right = pt.x;
	m_rcCircle.bottom  = pt.y;

}

void CXDrawCircle::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CPen cp,*pOldPen;
	CGdiObject * pObj=pDC->SelectStockObject(NULL_BRUSH);

	switch(m_dwState)
	{
	case XDRAW_STATE_NORMAL:
		{
			cp.CreatePen(m_nStyle,m_nWidth,m_crForeColor);
			break;
		}
	case XDRAW_STATE_PICKED:
		{
			cp.CreatePen(m_nPickStyle,m_nPickWidth,m_crPickColor);
			break;
		}
	}

	pOldPen=pDC->SelectObject(&cp);
	pDC->Ellipse(m_rcCircle);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pObj);
	cp.DeleteObject();	
	//pDC->SetROP2(dWord);
}

void CXDrawCircle::Pick(const CPoint &point, CExBaseList &oList)
{

}

void CXDrawCircle::GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	CalMinMax(fMinX, fMinY, fMaxX, fMaxY);
}
