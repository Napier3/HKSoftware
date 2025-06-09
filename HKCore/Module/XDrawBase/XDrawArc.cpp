//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawArc.cpp  CXDrawArc


#include "stdafx.h"
#include "XDrawArc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawArc::CXDrawArc()
{
	//初始化属性
	m_fXCenter = 0;
	m_fYCenter = 0;
	m_fXRadius = 0;
	m_fYRadius = 0;
	m_fAngleBegin = 0;
	m_fAngleEnd = 0;

	//初始化成员变量
}

CXDrawArc::~CXDrawArc()
{
}

long CXDrawArc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlReadOwn(oNode, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXCenterKey, oNode, m_fXCenter);
	xml_GetAttibuteValue(pXmlKeys->m_strYCenterKey, oNode, m_fYCenter);
	xml_GetAttibuteValue(pXmlKeys->m_strRadiusXKey, oNode, m_fXRadius);
	xml_GetAttibuteValue(pXmlKeys->m_strRadiusYKey, oNode, m_fYRadius);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleBeginKey, oNode, m_fAngleBegin);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleEndKey, oNode, m_fAngleEnd);
// 	m_fYRadius = m_fXRadius;

	return 0;
}

long CXDrawArc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXCenterKey, oElement, m_fXCenter);
	xml_SetAttributeValue(pXmlKeys->m_strYCenterKey, oElement, m_fYCenter);
	xml_SetAttributeValue(pXmlKeys->m_strRadiusXKey, oElement, m_fXRadius);
	xml_SetAttributeValue(pXmlKeys->m_strRadiusYKey, oElement, m_fYRadius);
	xml_SetAttributeValue(pXmlKeys->m_strAngleBeginKey, oElement, m_fAngleBegin);
	xml_SetAttributeValue(pXmlKeys->m_strAngleEndKey, oElement, m_fAngleEnd);
	
	return 0;
}

long CXDrawArc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXDrawBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fXCenter);
		BinarySerializeCalLen(oBinaryBuffer, m_fYCenter);
		BinarySerializeCalLen(oBinaryBuffer, m_fXRadius);
		BinarySerializeCalLen(oBinaryBuffer, m_fYRadius);
		BinarySerializeCalLen(oBinaryBuffer, m_fAngleBegin);
		BinarySerializeCalLen(oBinaryBuffer, m_fAngleEnd);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fXCenter);
		BinarySerializeRead(oBinaryBuffer, m_fYCenter);
		BinarySerializeRead(oBinaryBuffer, m_fXRadius);
		BinarySerializeRead(oBinaryBuffer, m_fYRadius);
		BinarySerializeRead(oBinaryBuffer, m_fAngleBegin);
		BinarySerializeRead(oBinaryBuffer, m_fAngleEnd);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fXCenter);
		BinarySerializeWrite(oBinaryBuffer, m_fYCenter);
		BinarySerializeWrite(oBinaryBuffer, m_fXRadius);
		BinarySerializeWrite(oBinaryBuffer, m_fYRadius);
		BinarySerializeWrite(oBinaryBuffer, m_fAngleBegin);
		BinarySerializeWrite(oBinaryBuffer, m_fAngleEnd);
	}
	return 0;
}

BOOL CXDrawArc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXDrawBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXDrawArc *p = (CXDrawArc*)pObj;

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

	if(m_fAngleBegin != p->m_fAngleBegin)
	{
		return FALSE;
	}

	if(m_fAngleEnd != p->m_fAngleEnd)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXDrawArc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawBase::CopyOwn(pDest);

	CXDrawArc *p = (CXDrawArc*)pDest;

	p->m_fXCenter = m_fXCenter;
	p->m_fYCenter = m_fYCenter;
	p->m_fXRadius = m_fXRadius;
	p->m_fYRadius = m_fYRadius;
	p->m_fAngleBegin = m_fAngleBegin;
	p->m_fAngleEnd = m_fAngleEnd;

	return TRUE;
}

CBaseObject* CXDrawArc::Clone()
{
	CXDrawArc *p = new CXDrawArc();
	Copy(p);
	return p;
}


void CXDrawArc::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	CPoint pt;

	pAxis->LogicPointToDevicePoint(m_fXCenter - m_fXRadius, m_fYCenter - m_fYRadius, &pt);
	m_rcCircle.left = pt.x;
	m_rcCircle.top  = pt.y;

	pAxis->LogicPointToDevicePoint(m_fXCenter + m_fXRadius, m_fYCenter + m_fYRadius, &pt);
	m_rcCircle.right = pt.x;
	m_rcCircle.bottom  = pt.y;

	double dX=0, dY=0;
	dX = m_fXCenter + m_fXRadius * cos(m_fAngleBegin * _PI_D_180);
	dY = m_fYCenter + m_fYRadius * sin(m_fAngleBegin * _PI_D_180);
	pAxis->LogicPointToDevicePoint(dX, dY, &m_ptBegin);

	dX = m_fXCenter + m_fXRadius * cos(m_fAngleEnd * _PI_D_180);
	dY = m_fYCenter + m_fYRadius * sin(m_fAngleEnd * _PI_D_180);
	pAxis->LogicPointToDevicePoint(dX, dY, &m_ptEnd);
}

void CXDrawArc::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CPen oPen,*pOldPen;
	CGdiObject * pObj=pDC->SelectStockObject(NULL_BRUSH);

	switch(m_dwState)
	{
	case XDRAW_STATE_NORMAL:
		{
			oPen.CreatePen(m_nStyle,m_nWidth,m_crForeColor);
			break;
		}
	case XDRAW_STATE_PICKED:
		{
			oPen.CreatePen(m_nPickStyle,m_nPickWidth,m_crPickColor);
			break;
		}
	}

	pOldPen=pDC->SelectObject(&oPen);

    if (IsCW())
    {
        pDC->Arc(m_rcCircle,m_ptEnd,m_ptBegin);
    }
    else
    {
        pDC->Arc(m_rcCircle,m_ptBegin,m_ptEnd);
    }

	//pDC->Ellipse(m_rcCircle);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pObj);
	oPen.DeleteObject();	
	//pDC->SetROP2(dWord);

}

void CXDrawArc::Pick(const CPoint &point, CExBaseList &oList)
{

}

void CXDrawArc::GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	CalMinMax(fMinX, fMinY, fMaxX, fMaxY);
}
