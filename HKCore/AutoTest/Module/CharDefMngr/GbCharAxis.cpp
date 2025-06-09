//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharAxis.cpp  CGbCharAxis


#include "stdafx.h"
#include "GbCharAxis.h"

CGbCharAxis::CGbCharAxis()
{
	//初始化属性

	//初始化成员变量
}

CGbCharAxis::~CGbCharAxis()
{
}

long CGbCharAxis::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAxisKey, oNode, m_strAxis);
	xml_GetAttibuteValue(pXmlKeys->m_strXNameKey, oNode, m_strXName);
	xml_GetAttibuteValue(pXmlKeys->m_strYNameKey, oNode, m_strYName);
	xml_GetAttibuteValue(pXmlKeys->m_strXMinKey, oNode, m_strXMin);
	xml_GetAttibuteValue(pXmlKeys->m_strYMinKey, oNode, m_strYMin);
	xml_GetAttibuteValue(pXmlKeys->m_strXMaxKey, oNode, m_strXMax);
	xml_GetAttibuteValue(pXmlKeys->m_strYMaxKey, oNode, m_strYMax);
	return 0;
}

long CGbCharAxis::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAxisKey, oElement, m_strAxis);
	xml_SetAttributeValue(pXmlKeys->m_strXNameKey, oElement, m_strXName);
	xml_SetAttributeValue(pXmlKeys->m_strYNameKey, oElement, m_strYName);
	xml_SetAttributeValue(pXmlKeys->m_strXMinKey, oElement, m_strXMin);
	xml_SetAttributeValue(pXmlKeys->m_strYMinKey, oElement, m_strYMin);
	xml_SetAttributeValue(pXmlKeys->m_strXMaxKey, oElement, m_strXMax);
	xml_SetAttributeValue(pXmlKeys->m_strYMaxKey, oElement, m_strYMax);
	return 0;
}

long CGbCharAxis::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAxis);
		BinarySerializeCalLen(oBinaryBuffer, m_strXName);
		BinarySerializeCalLen(oBinaryBuffer, m_strYName);
		BinarySerializeCalLen(oBinaryBuffer, m_strXMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strYMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strXMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strYMax);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAxis);
		BinarySerializeRead(oBinaryBuffer, m_strXName);
		BinarySerializeRead(oBinaryBuffer, m_strYName);
		BinarySerializeRead(oBinaryBuffer, m_strXMin);
		BinarySerializeRead(oBinaryBuffer, m_strYMin);
		BinarySerializeRead(oBinaryBuffer, m_strXMax);
		BinarySerializeRead(oBinaryBuffer, m_strYMax);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAxis);
		BinarySerializeWrite(oBinaryBuffer, m_strXName);
		BinarySerializeWrite(oBinaryBuffer, m_strYName);
		BinarySerializeWrite(oBinaryBuffer, m_strXMin);
		BinarySerializeWrite(oBinaryBuffer, m_strYMin);
		BinarySerializeWrite(oBinaryBuffer, m_strXMax);
		BinarySerializeWrite(oBinaryBuffer, m_strYMax);
	}
	return 0;
}

BOOL CGbCharAxis::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharAxis *p = (CGbCharAxis*)pObj;

	if(m_strAxis != p->m_strAxis)
	{
		return FALSE;
	}

	if(m_strXName != p->m_strXName)
	{
		return FALSE;
	}

	if(m_strYName != p->m_strYName)
	{
		return FALSE;
	}

	if(m_strXMin != p->m_strXMin)
	{
		return FALSE;
	}

	if(m_strYMin != p->m_strYMin)
	{
		return FALSE;
	}

	if(m_strXMax != p->m_strXMax)
	{
		return FALSE;
	}

	if(m_strYMax != p->m_strYMax)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbCharAxis::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharAxis *p = (CGbCharAxis*)pDest;

	p->m_strAxis = m_strAxis;
	p->m_strXName = m_strXName;
	p->m_strYName = m_strYName;
	p->m_strXMin = m_strXMin;
	p->m_strYMin = m_strYMin;
	p->m_strXMax = m_strXMax;
	p->m_strYMax = m_strYMax;
	return TRUE;
}

CBaseObject* CGbCharAxis::Clone()
{
	CGbCharAxis *p = new CGbCharAxis();
	Copy(p);
	return p;
}

CExBaseObject* CGbCharAxis::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCGbCharLineDrawKey)
	{
		pNew = new CGbCharLineDraw();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharPointDrawKey)
	{
		pNew = new CGbCharPointDraw();
	}

	return pNew;
}

CExBaseObject* CGbCharAxis::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHRCLASSID_CGBCHARLINEDRAW)
	{
		pNew = new CGbCharLineDraw();
	}
	else if (nClassID == CHRCLASSID_CGBCHARPOINTDRAW)
	{
		pNew = new CGbCharPointDraw();
	}

	return pNew;
}
