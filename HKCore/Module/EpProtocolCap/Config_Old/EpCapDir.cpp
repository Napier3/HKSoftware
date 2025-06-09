//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDir.cpp  CEpCapDir


#include "stdafx.h"
#include "EpCapDir.h"

CEpCapDir::CEpCapDir()
{
	//初始化属性
	m_nValue = 0;
	m_nIndex1 = 0;
	m_nIndex2 = 0;

	//初始化成员变量
}

CEpCapDir::~CEpCapDir()
{
}

long CEpCapDir::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_nValue);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex1Key, oNode, m_nIndex1);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex2Key, oNode, m_nIndex2);
	return 0;
}

long CEpCapDir::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_nValue);
	xml_SetAttributeValue(pXmlKeys->m_strIndex1Key, oElement, m_nIndex1);
	xml_SetAttributeValue(pXmlKeys->m_strIndex2Key, oElement, m_nIndex2);
	return 0;
}

long CEpCapDir::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nValue);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex1);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex2);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nValue);
		BinarySerializeRead(oBinaryBuffer, m_nIndex1);
		BinarySerializeRead(oBinaryBuffer, m_nIndex2);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nValue);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex1);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex2);
	}
	return 0;
}

void CEpCapDir::InitAfterRead()
{
}

BOOL CEpCapDir::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapDir *p = (CEpCapDir*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nValue != p->m_nValue)
	{
		return FALSE;
	}

	if(m_nIndex1 != p->m_nIndex1)
	{
		return FALSE;
	}

	if(m_nIndex2 != p->m_nIndex2)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapDir::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapDir *p = (CEpCapDir*)pDest;

	p->m_strName = m_strName;
	p->m_nValue = m_nValue;
	p->m_nIndex1 = m_nIndex1;
	p->m_nIndex2 = m_nIndex2;
	return TRUE;
}

CBaseObject* CEpCapDir::Clone()
{
	CEpCapDir *p = new CEpCapDir();
	Copy(p);
	return p;
}

