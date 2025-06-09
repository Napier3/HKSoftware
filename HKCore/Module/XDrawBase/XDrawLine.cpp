//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawLine.cpp  CXDrawLine


#include "stdafx.h"
#include "XDrawLine.h"
#include "../BaseClass/ComplexNumber.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawLine::CXDrawLine()
{
	//初始化属性
	m_fXb = 0;
	m_fYb = 0;
	m_fXe = 0;
	m_fYe = 0;
	m_nStyle = 0;
	m_nWidth = 0;

	//初始化成员变量
}

CXDrawLine::~CXDrawLine()
{
}

long CXDrawLine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlReadOwn(oNode, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBXKey, oNode, m_fXb);
	xml_GetAttibuteValue(pXmlKeys->m_strBYKey, oNode, m_fYb);
	xml_GetAttibuteValue(pXmlKeys->m_strEXKey, oNode, m_fXe);
	xml_GetAttibuteValue(pXmlKeys->m_strEYKey, oNode, m_fYe);
	return 0;
}

long CXDrawLine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strBXKey, oElement, m_fXb);
	xml_SetAttributeValue(pXmlKeys->m_strBYKey, oElement, m_fYb);
	xml_SetAttributeValue(pXmlKeys->m_strEXKey, oElement, m_fXe);
	xml_SetAttributeValue(pXmlKeys->m_strEYKey, oElement, m_fYe);

	return 0;
}

long CXDrawLine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXDrawBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fXb);
		BinarySerializeCalLen(oBinaryBuffer, m_fYb);
		BinarySerializeCalLen(oBinaryBuffer, m_fXe);
		BinarySerializeCalLen(oBinaryBuffer, m_fYe);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fXb);
		BinarySerializeRead(oBinaryBuffer, m_fYb);
		BinarySerializeRead(oBinaryBuffer, m_fXe);
		BinarySerializeRead(oBinaryBuffer, m_fYe);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fXb);
		BinarySerializeWrite(oBinaryBuffer, m_fYb);
		BinarySerializeWrite(oBinaryBuffer, m_fXe);
		BinarySerializeWrite(oBinaryBuffer, m_fYe);
	}
	return 0;
}

BOOL CXDrawLine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXDrawBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXDrawLine *p = (CXDrawLine*)pObj;

	if(m_fXb != p->m_fXb)
	{
		return FALSE;
	}

	if(m_fYb != p->m_fYb)
	{
		return FALSE;
	}

	if(m_fXe != p->m_fXe)
	{
		return FALSE;
	}

	if(m_fYe != p->m_fYe)
	{
		return FALSE;
	}

	if(m_nStyle != p->m_nStyle)
	{
		return FALSE;
	}

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXDrawLine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawBase::CopyOwn(pDest);

	CXDrawLine *p = (CXDrawLine*)pDest;

	p->m_fXb = m_fXb;
	p->m_fYb = m_fYb;
	p->m_fXe = m_fXe;
	p->m_fYe = m_fYe;

	return TRUE;
}

CBaseObject* CXDrawLine::Clone()
{
	CXDrawLine *p = new CXDrawLine();
	Copy(p);
	return p;
}

void CXDrawLine::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	pAxis->LogicPointToDevicePoint(m_fXb, m_fYb, &m_pointBegin);
	pAxis->LogicPointToDevicePoint(m_fXe, m_fYe, &m_pointEnd);
}


void CXDrawLine::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CPen cp,*pOldPen;

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
	default:
		{
			cp.CreatePen(m_nStyle,m_nWidth,m_crForeColor);
			break;
		}
	}

	pOldPen=pDC->SelectObject(&cp);
    pDC->MoveTo(m_pointBegin.x, m_pointBegin.y);
    pDC->LineTo(m_pointEnd.x, m_pointEnd.y);
	pDC->SelectObject(pOldPen);
	cp.DeleteObject();		

}

void CXDrawLine::Pick(const CPoint &point, CExBaseList &oList)
{

}

void CXDrawLine::GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	CalMinMax(fMinX, fMinY, fMaxX, fMaxY);
}


//////////////////////////////////////////////////////////////////////////
//

CXDrawLineR::CXDrawLineR()
{
	//初始化属性
	m_fAngle = 0;

	//初始化成员变量
}

CXDrawLineR::~CXDrawLineR()
{
}

long CXDrawLineR::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawLine::XmlReadOwn(oNode, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_fAngle);

	return 0;
}

long CXDrawLineR::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawLine::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_fAngle);
	
	return 0;
}

long CXDrawLineR::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXDrawLine::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fAngle);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fAngle);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fAngle);
	}

	return 0;
}

BOOL CXDrawLineR::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXDrawLine::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXDrawLineR *p = (CXDrawLineR*)pObj;

	if(m_fAngle != p->m_fAngle)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXDrawLineR::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawLine::CopyOwn(pDest);

	CXDrawLineR *p = (CXDrawLineR*)pDest;

	p->m_fAngle = m_fAngle;

	return TRUE;
}

CBaseObject* CXDrawLineR::Clone()
{
	CXDrawLineR *p = new CXDrawLineR();
	Copy(p);
	return p;
}

void CXDrawLineR::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	double dXmin, dXmax, dYmin, dYmax;
	pAxis->GetAxisMinMax(dXmin, dYmin, dXmax, dYmax);

	CComplexNumber c1, c2, c3, c4, cp, c;
	c1.SetValue(dXmax, dYmax);
	c2.SetValue(dXmin, dYmax);
	c3.SetValue(dXmin, dYmin);
	c4.SetValue(dXmax, dYmin);
	cp.SetValue(m_fXb, m_fYb);

	double dAngle1, dAngle2, dAngle3, dAngle4;

	c = c1-cp;
	dAngle1 = c.GetAngle_0_360();

	c = c2-cp;
	dAngle2 = c.GetAngle_0_360();

	c = c3-cp;
	dAngle3 = c.GetAngle_0_360();

	c = c4-cp;
	dAngle4 = c.GetAngle_0_360();

	if (dAngle1 <= m_fAngle && m_fAngle <= dAngle2)
	{
		m_fYe = dYmax;
		m_fXe = m_fXb + (m_fYe-m_fYb)/tan(m_fAngle*_PI_D_180);
	}
	else if (dAngle2 <= m_fAngle && m_fAngle <= dAngle3)
	{
		m_fXe = dXmin;
		m_fYe = (m_fXe- m_fXb)*tan(m_fAngle*_PI_D_180)+m_fYb;
	}
	else if (dAngle2 <= m_fAngle && m_fAngle <= dAngle3)
	{
		m_fYe = dYmin;
		m_fXe = m_fXb + (m_fYe-m_fYb)/tan(m_fAngle*_PI_D_180);
	}
	else
	{
		m_fXe = dXmax;
		m_fYe = (m_fXe- m_fXb)*tan(m_fAngle*_PI_D_180)+m_fYb;
	}

	CXDrawLine::LogicPointToDevicePoint(pAxis);
}
