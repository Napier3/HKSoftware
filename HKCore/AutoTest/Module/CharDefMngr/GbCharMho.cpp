//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharMho.cpp  CGbCharMho


#include "stdafx.h"
#include "GbCharMho.h"

CGbCharMho::CGbCharMho()
{
	//初始化属性

	//初始化成员变量
}

CGbCharMho::~CGbCharMho()
{
}

long CGbCharMho::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strReachKey, oNode, m_strReach);
	xml_GetAttibuteValue(pXmlKeys->m_strOffsetKey, oNode, m_strOffset);
	return 0;
}

long CGbCharMho::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strReachKey, oElement, m_strReach);
	xml_SetAttributeValue(pXmlKeys->m_strOffsetKey, oElement, m_strOffset);
	return 0;
}

long CGbCharMho::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strReach);
		BinarySerializeCalLen(oBinaryBuffer, m_strOffset);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAngle);
		BinarySerializeRead(oBinaryBuffer, m_strReach);
		BinarySerializeRead(oBinaryBuffer, m_strOffset);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strReach);
		BinarySerializeWrite(oBinaryBuffer, m_strOffset);
	}
	return 0;
}

BOOL CGbCharMho::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharMho *p = (CGbCharMho*)pObj;

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

	return TRUE;
}

BOOL CGbCharMho::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharMho *p = (CGbCharMho*)pDest;

	p->m_strAngle = m_strAngle;
	p->m_strReach = m_strReach;
	p->m_strOffset = m_strOffset;
	return TRUE;
}

CBaseObject* CGbCharMho::Clone()
{
	CGbCharMho *p = new CGbCharMho();
	Copy(p);
	return p;
}

