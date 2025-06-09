//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmmGroupKey.cpp  CSmmGroupKey


#include "stdafx.h"
#include "SmmGroupKey.h"

CSmmGroupKey::CSmmGroupKey()
{
	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
}

CSmmGroupKey::~CSmmGroupKey()
{
}

long CSmmGroupKey::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CSmmGroupKey::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CSmmGroupKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CSmmGroupKey::InitAfterRead()
{
}

BOOL CSmmGroupKey::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmmGroupKey *p = (CSmmGroupKey*)pObj;

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSmmGroupKey::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmmGroupKey *p = (CSmmGroupKey*)pDest;

	p->m_nIndex = m_nIndex;
	p->m_strName = m_strName;
	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CSmmGroupKey::Clone()
{
	CSmmGroupKey *p = new CSmmGroupKey();
	Copy(p);
	return p;
}

BOOL CSmmGroupKey::CanPaste(UINT nClassID)
{
	if (nClassID == SMMCLASSID_CSMMREFKEY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSmmGroupKey::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSmmRefKeyKey)
	{
		pNew = new CSmmRefKey();
	}

	return pNew;
}

CExBaseObject* CSmmGroupKey::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == SMMCLASSID_CSMMREFKEY)
	{
		pNew = new CSmmRefKey();
	}

	return pNew;
}
