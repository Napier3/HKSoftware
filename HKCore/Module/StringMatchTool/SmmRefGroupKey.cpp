//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmmRefGroupKey.cpp  CSmmRefGroupKey


#include "stdafx.h"
#include "SmmRefGroupKey.h"

CSmmRefGroupKey::CSmmRefGroupKey()
{
	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
}

CSmmRefGroupKey::~CSmmRefGroupKey()
{
}

long CSmmRefGroupKey::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	return 0;
}

long CSmmRefGroupKey::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	return 0;
}

long CSmmRefGroupKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSmmRefGroupKey::InitAfterRead()
{
}

BOOL CSmmRefGroupKey::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmmRefGroupKey *p = (CSmmRefGroupKey*)pObj;

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSmmRefGroupKey::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmmRefGroupKey *p = (CSmmRefGroupKey*)pDest;

	p->m_nIndex = m_nIndex;
	return TRUE;
}

CBaseObject* CSmmRefGroupKey::Clone()
{
	CSmmRefGroupKey *p = new CSmmRefGroupKey();
	Copy(p);
	return p;
}

