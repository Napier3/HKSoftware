//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmmGroupKeys.cpp  CSmmGroupKeys


#include "stdafx.h"
#include "SmmGroupKeys.h"

CSmmGroupKeys::CSmmGroupKeys()
{
	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
}

CSmmGroupKeys::~CSmmGroupKeys()
{
}

long CSmmGroupKeys::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	return 0;
}

long CSmmGroupKeys::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	return 0;
}

long CSmmGroupKeys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
		BinarySerializeRead(oBinaryBuffer, m_strName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
	}
	return 0;
}

void CSmmGroupKeys::InitAfterRead()
{
}

BOOL CSmmGroupKeys::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmmGroupKeys *p = (CSmmGroupKeys*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSmmGroupKeys::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmmGroupKeys *p = (CSmmGroupKeys*)pDest;

	p->m_strType = m_strType;
	p->m_nIndex = m_nIndex;
	p->m_strName = m_strName;
	return TRUE;
}

CBaseObject* CSmmGroupKeys::Clone()
{
	CSmmGroupKeys *p = new CSmmGroupKeys();
	Copy(p);
	return p;
}

BOOL CSmmGroupKeys::CanPaste(UINT nClassID)
{
	if (nClassID == SMMCLASSID_CSMMREFGROUPKEY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSmmGroupKeys::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CStringMatchMapXmlRWKeys *pXmlKeys = (CStringMatchMapXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSmmRefGroupKeyKey)
	{
		pNew = new CSmmRefGroupKey();
	}

	return pNew;
}

CExBaseObject* CSmmGroupKeys::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == SMMCLASSID_CSMMREFGROUPKEY)
	{
		pNew = new CSmmRefGroupKey();
	}

	return pNew;
}
