//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmmRefKey.cpp  CSmmRefKey


#include "stdafx.h"
#include "SmmRefKey.h"

CSmmRefKey::CSmmRefKey()
{
	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
}

CSmmRefKey::~CSmmRefKey()
{
}

long CSmmRefKey::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	return 0;
}

long CSmmRefKey::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	return 0;
}

long CSmmRefKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
	}
	return 0;
}

void CSmmRefKey::InitAfterRead()
{
}

BOOL CSmmRefKey::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmmRefKey *p = (CSmmRefKey*)pObj;

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSmmRefKey::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmmRefKey *p = (CSmmRefKey*)pDest;

	p->m_nIndex = m_nIndex;
	return TRUE;
}

CBaseObject* CSmmRefKey::Clone()
{
	CSmmRefKey *p = new CSmmRefKey();
	Copy(p);
	return p;
}

