//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AinExpand.cpp  CAinExpand


#include "stdafx.h"
#include "AinExpand.h"

CAinExpand::CAinExpand()
{
	//初始化属性
	m_nAbs = 0;
	m_nReal = 0;
	m_nRslt = 0;

	//初始化成员变量
}

CAinExpand::~CAinExpand()
{
}

long CAinExpand::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAbsKey, oNode, m_nAbs);
	xml_GetAttibuteValue(pXmlKeys->m_strRealKey, oNode, m_nReal);
	xml_GetAttibuteValue(pXmlKeys->m_strRsltKey, oNode, m_nRslt);
	return 0;
}

long CAinExpand::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAbsKey, oElement, m_nAbs);
	xml_SetAttributeValue(pXmlKeys->m_strRealKey, oElement, m_nReal);
	xml_SetAttributeValue(pXmlKeys->m_strRsltKey, oElement, m_nRslt);
	return 0;
}

long CAinExpand::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nAbs);
		BinarySerializeCalLen(oBinaryBuffer, m_nReal);
		BinarySerializeCalLen(oBinaryBuffer, m_nRslt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nAbs);
		BinarySerializeRead(oBinaryBuffer, m_nReal);
		BinarySerializeRead(oBinaryBuffer, m_nRslt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nAbs);
		BinarySerializeWrite(oBinaryBuffer, m_nReal);
		BinarySerializeWrite(oBinaryBuffer, m_nRslt);
	}
	return 0;
}

void CAinExpand::InitAfterRead()
{
}

BOOL CAinExpand::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAinExpand *p = (CAinExpand*)pObj;

	if(m_nAbs != p->m_nAbs)
	{
		return FALSE;
	}

	if(m_nReal != p->m_nReal)
	{
		return FALSE;
	}

	if(m_nRslt != p->m_nRslt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAinExpand::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAinExpand *p = (CAinExpand*)pDest;

	p->m_nAbs = m_nAbs;
	p->m_nReal = m_nReal;
	p->m_nRslt = m_nRslt;
	return TRUE;
}

CBaseObject* CAinExpand::Clone()
{
	CAinExpand *p = new CAinExpand();
	Copy(p);
	return p;
}

