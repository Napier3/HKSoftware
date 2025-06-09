//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmmMultiKey.cpp  CSmmMultiKey


#include "stdafx.h"
#include "SmmMultiKey.h"

CSmmMultiKey::CSmmMultiKey()
{
	//初始化属性

	//初始化成员变量
}

CSmmMultiKey::~CSmmMultiKey()
{
}

long CSmmMultiKey::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	return 0;
}

long CSmmMultiKey::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	return 0;
}

long CSmmMultiKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
	}
	return 0;
}

void CSmmMultiKey::InitAfterRead()
{
}

BOOL CSmmMultiKey::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmmMultiKey *p = (CSmmMultiKey*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSmmMultiKey::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmmMultiKey *p = (CSmmMultiKey*)pDest;

	p->m_strName = m_strName;
	p->m_strType = m_strType;
	p->m_nIndex = m_nIndex;
	return TRUE;
}

CBaseObject* CSmmMultiKey::Clone()
{
	CSmmMultiKey *p = new CSmmMultiKey();
	Copy(p);
	return p;
}

BOOL CSmmMultiKey::CanPaste(UINT nClassID)
{
	if (nClassID == SMMCLASSID_CSMMREFKEY)
	{
		return TRUE;
	}

	if (nClassID == SMMCLASSID_CSMMREFGROUPKEY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSmmMultiKey::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSmmRefKeyKey)
	{
		pNew = new CSmmRefKey();
	}
	else if (strClassID == pXmlKeys->m_strCSmmRefGroupKeyKey)
	{
		pNew = new CSmmRefGroupKey();
	}

	return pNew;
}

CExBaseObject* CSmmMultiKey::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == SMMCLASSID_CSMMREFKEY)
	{
		pNew = new CSmmRefKey();
	}
	else if (nClassID == SMMCLASSID_CSMMREFGROUPKEY)
	{
		pNew = new CSmmRefGroupKey();
	}

	return pNew;
}
