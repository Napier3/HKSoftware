//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharLenTomato.cpp  CGbCharLenTomato


#include "stdafx.h"
#include "GbCharLenTomato.h"

CGbCharLenTomato::CGbCharLenTomato()
{
	//初始化属性

	//初始化成员变量
}

CGbCharLenTomato::~CGbCharLenTomato()
{
}

long CGbCharLenTomato::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strReachKey, oNode, m_strReach);
	xml_GetAttibuteValue(pXmlKeys->m_strOffsetKey, oNode, m_strOffset);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_strWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strABKey, oNode, m_strAB);
	return 0;
}

long CGbCharLenTomato::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strReachKey, oElement, m_strReach);
	xml_SetAttributeValue(pXmlKeys->m_strOffsetKey, oElement, m_strOffset);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_strWidth);
	xml_SetAttributeValue(pXmlKeys->m_strABKey, oElement, m_strAB);
	return 0;
}

long CGbCharLenTomato::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strReach);
		BinarySerializeCalLen(oBinaryBuffer, m_strOffset);
		BinarySerializeCalLen(oBinaryBuffer, m_strWidth);
		BinarySerializeCalLen(oBinaryBuffer, m_strAB);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAngle);
		BinarySerializeRead(oBinaryBuffer, m_strReach);
		BinarySerializeRead(oBinaryBuffer, m_strOffset);
		BinarySerializeRead(oBinaryBuffer, m_strWidth);
		BinarySerializeRead(oBinaryBuffer, m_strAB);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strReach);
		BinarySerializeWrite(oBinaryBuffer, m_strOffset);
		BinarySerializeWrite(oBinaryBuffer, m_strWidth);
		BinarySerializeWrite(oBinaryBuffer, m_strAB);
	}
	return 0;
}

BOOL CGbCharLenTomato::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharLenTomato *p = (CGbCharLenTomato*)pObj;

	if(m_strAngle != p->m_strAngle)
	{
		return FALSE;
	}

	if(m_strReach != p->m_strReach)
	{
		return FALSE;
	}

	if(m_strOffset != p->m_strOffset)
	{
		return FALSE;
	}

	if(m_strWidth != p->m_strWidth)
	{
		return FALSE;
	}

	if(m_strAB != p->m_strAB)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbCharLenTomato::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharLenTomato *p = (CGbCharLenTomato*)pDest;

	p->m_strAngle = m_strAngle;
	p->m_strReach = m_strReach;
	p->m_strOffset = m_strOffset;
	p->m_strWidth = m_strWidth;
	p->m_strAB = m_strAB;
	return TRUE;
}

CBaseObject* CGbCharLenTomato::Clone()
{
	CGbCharLenTomato *p = new CGbCharLenTomato();
	Copy(p);
	return p;
}

