//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmmRefGroupKeys.cpp  CSmmRefGroupKeys


#include "stdafx.h"
#include "SmmRefGroupKeys.h"

CSmmRefGroupKeys::CSmmRefGroupKeys()
{
	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
}

CSmmRefGroupKeys::~CSmmRefGroupKeys()
{
}

long CSmmRefGroupKeys::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	return 0;
}

long CSmmRefGroupKeys::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	return 0;
}

long CSmmRefGroupKeys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSmmRefGroupKeys::InitAfterRead()
{
}

BOOL CSmmRefGroupKeys::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmmRefGroupKeys *p = (CSmmRefGroupKeys*)pObj;

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSmmRefGroupKeys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmmRefGroupKeys *p = (CSmmRefGroupKeys*)pDest;

	p->m_nIndex = m_nIndex;
	return TRUE;
}

CBaseObject* CSmmRefGroupKeys::Clone()
{
	CSmmRefGroupKeys *p = new CSmmRefGroupKeys();
	Copy(p);
	return p;
}

