//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawText.cpp  CXDrawText


#include "stdafx.h"
#include "XDrawText.h"
#include "../../Module/API/GloblaDrawFunctions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawText::CXDrawText()
{
	//初始化属性
	m_fX = 0;
	m_fY = 0;
	m_fWidth = 1;
	m_fHeight = 1;

	//初始化成员变量
	m_ptWidthHeight.x = 0;
	m_ptWidthHeight.y = 0;
	m_ptPoint.x = 0;
	m_ptPoint.y = 0;
}

CXDrawText::~CXDrawText()
{
}

long CXDrawText::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlReadOwn(oNode, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_fX);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_fY);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_fWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strHeightKey, oNode, m_fHeight);
	xml_GetAttibuteValue(pXmlKeys->m_strCXDrawTextKey, oNode, m_strText);

	return 0;
}

long CXDrawText::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXDrawBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_fX);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_fY);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_fWidth);
	xml_SetAttributeValue(pXmlKeys->m_strHeightKey, oElement, m_fHeight);
	xml_SetAttributeValue(pXmlKeys->m_strCXDrawTextKey, oElement, m_strText);

	return 0;
}

long CXDrawText::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXDrawBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fX);
		BinarySerializeCalLen(oBinaryBuffer, m_fY);
		BinarySerializeCalLen(oBinaryBuffer, m_fWidth);
		BinarySerializeCalLen(oBinaryBuffer, m_fHeight);
		BinarySerializeCalLen(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fX);
		BinarySerializeRead(oBinaryBuffer, m_fY);
		BinarySerializeRead(oBinaryBuffer, m_fWidth);
		BinarySerializeRead(oBinaryBuffer, m_fHeight);
		BinarySerializeRead(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fX);
		BinarySerializeWrite(oBinaryBuffer, m_fY);
		BinarySerializeWrite(oBinaryBuffer, m_fWidth);
		BinarySerializeWrite(oBinaryBuffer, m_fHeight);
		BinarySerializeWrite(oBinaryBuffer, m_strText);
	}

	return 0;
}

BOOL CXDrawText::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXDrawBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXDrawText *p = (CXDrawText*)pObj;

	if(m_fX != p->m_fX)
	{
		return FALSE;
	}

	if(m_fY != p->m_fY)
	{
		return FALSE;
	}

	if(m_strText != p->m_strText)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXDrawText::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawBase::CopyOwn(pDest);

	CXDrawText *p = (CXDrawText*)pDest;

	p->m_fX = m_fX;
	p->m_fY = m_fY;
	p->m_fWidth = m_fWidth;
	p->m_fHeight = m_fHeight;
	p->m_strText = m_strText;

	return TRUE;
}

CBaseObject* CXDrawText::Clone()
{
	CXDrawText *p = new CXDrawText();
	Copy(p);
	return p;
}

void CXDrawText::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	pAxis->LogicPointToDevicePoint(m_fX, m_fY, &m_ptPoint);
	pAxis->LogicPointToDevicePoint(m_fWidth, m_fHeight, &m_ptWidthHeight);
}

void CXDrawText::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CRect rcText;
	rcText.left = m_ptPoint.x;
	rcText.top = m_ptPoint.y;

	if (math_IsEqual(m_fWidth, 0) || math_IsEqual(m_fHeight, 0))
	{
		CRect rc(0, 0, 1000, 20);
		pDC->DrawText(m_strText, rc, DT_CALCRECT);
		rcText.right = m_ptPoint.x+rc.Width() + 6;
		rcText.bottom = m_ptPoint.y + rc.Height() + 2;
	}
	else
	{
		rcText.right = m_ptPoint.x+m_ptWidthHeight.x;
		rcText.bottom = m_ptPoint.y + m_ptWidthHeight.y;
	}

	//xdraw_DrawPoint(pDC, m_ptPoint, 1, m_crForeColor, 2, fZoomRatio, ptOffset);
	CmDrawTextRect(pDC, m_strText, m_crForeColor, rcText, m_crBkColor, g_lfGlobalFont14
		, TRANSPARENT,DT_VCENTER|DT_CENTER,0);
}

void CXDrawText::Pick(const CPoint &point, CExBaseList &oList)
{
	
}

void CXDrawText::GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	fMinY = min(m_fY, fMinY);
	fMinY = min(m_fY, fMinY);

	fMinX = min(m_fX, fMinX);
	fMinX = min(m_fX, fMinX);
}
