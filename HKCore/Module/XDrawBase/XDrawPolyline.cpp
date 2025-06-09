//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawPolyline.cpp  CXDrawPolyline


#include "stdafx.h"
#include "XDrawPolyline.h"
#include "../BaseClass/ComplexNumber.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawPolyline::CXDrawPolyline()
{
	//初始化属性

	//初始化成员变量
	m_nPointBuffer = 0;
	m_pPointBuffer = NULL;
}

CXDrawPolyline::~CXDrawPolyline()
{
	delete m_pPointBuffer;
}

long CXDrawPolyline::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlReadOwn(oNode, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPointsKey, oNode, m_nPoints);
	
	return 0;
}

long CXDrawPolyline::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPointsKey, oElement, m_nPoints);

	return 0;
}

long CXDrawPolyline::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXDrawBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nPoints);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nPoints);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nPoints);
	}

	return 0;
}

BOOL CXDrawPolyline::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXDrawBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXDrawPolyline *p = (CXDrawPolyline*)pObj;

	return TRUE;
}

BOOL CXDrawPolyline::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawBase::CopyOwn(pDest);

	CXDrawPolyline *p = (CXDrawPolyline*)pDest;

	CXDrawData_Points::DataCopy(p);

	return TRUE;
}

CBaseObject* CXDrawPolyline::Clone()
{
	CXDrawPolyline *p = new CXDrawPolyline();
	Copy(p);
	return p;
}

void CXDrawPolyline::FreePointBuffer()
{
	if (m_nPointBuffer != NULL)
	{
		delete []m_pPointBuffer;
	}

	m_pPointBuffer = NULL;
	m_nPointBuffer = 0;
}

void CXDrawPolyline::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	if (m_nPoints <= 0)
	{
		FreePointBuffer();
		return;
	}

	long nIndex = 0;
	long nNeedPoints = m_nPoints;

	if (m_bIsAutoClose)
	{
		nNeedPoints++;
	}

	if (nNeedPoints >= m_nPointBuffer)
	{
		FreePointBuffer();
		m_pPointBuffer = new CPoint[m_nPoints];
		m_nPointBuffer = m_nPoints;
	}

	for (nIndex=0; nIndex<m_nPoints; nIndex++)
	{
		pAxis->LogicPointToDevicePoint(m_pPoints[nIndex].m_fX, m_pPoints[nIndex].m_fY, m_pPointBuffer + nIndex);
	}

	if (m_bIsAutoClose)
	{
		pAxis->LogicPointToDevicePoint(m_pPoints[m_nPoints].m_fX, m_pPoints[m_nPoints].m_fY, m_pPointBuffer + m_nPoints);
	}
}


void CXDrawPolyline::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
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
	pDC->Polyline(m_pPointBuffer, m_nPointBuffer);
	pDC->SelectObject(pOldPen);
	cp.DeleteObject();		

}

void CXDrawPolyline::Pick(const CPoint &point, CExBaseList &oList)
{

}

void CXDrawPolyline::GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	CalMinMax(fMinX, fMinY, fMaxX, fMaxY);
}

