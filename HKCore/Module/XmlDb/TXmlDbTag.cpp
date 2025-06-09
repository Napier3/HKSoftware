#include "StdAfx.h"
#include "TXmlDbTag.h"

CTXmlDbTag::CTXmlDbTag(void)
{
	m_strID = _T("tg");
}

CTXmlDbTag::~CTXmlDbTag(void)
{
}

void CTXmlDbTag::Init()
{
	//
}

long CTXmlDbTag::InitAfterSerialize()
{
	//
	return 0;
}

//´®ÐÐ»¯
long CTXmlDbTag::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer->IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsKey);
	}
	else if (oBinaryBuffer->IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_nIsKey);
	}
	else if (oBinaryBuffer->IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_nIsKey);
	}

	return 0;
}

long CTXmlDbTag::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
		
	CXmlDbKeys *pXmlDbKeys = (CXmlDbKeys *)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlDbKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlDbKeys->m_strIsKeyKey, oNode, m_nIsKey);

	return 0;
}

long CTXmlDbTag::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);
	
	CXmlDbKeys *pXmlDbKeys = (CXmlDbKeys *)pXmlRWKeys;
	oElemen->setAttribute(pXmlDbKeys->m_strDataTypeKey, _bstr_t(m_strDataType));
	oElemen->setAttribute(pXmlDbKeys->m_strIsKeyKey, _bstr_t(m_nIsKey));

	return 0;
}

//±à¼­
BOOL CTXmlDbTag::IsEqualOwn(CBaseObject* pObj)
{
	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	ASSERT(pObj->GetClassID() == CLASSID_TXMLDBTAG);
	CTXmlDbTag *pTag = (CTXmlDbTag *)pObj;

	if (m_strDataType != pTag->m_strDataType)
	{
		return FALSE;
	}
	else if (m_nIsKey != pTag->m_nIsKey)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTXmlDbTag::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);
	ASSERT(pDest->GetClassID() == CLASSID_TXMLDBTAG);

	if(!CExBaseObject::CopyOwn(pDest))
	{
		return FALSE;
	}

	CTXmlDbTag *pTag = (CTXmlDbTag *)pDest;
	pTag->m_strDataType = m_strDataType;
	pTag->m_nIsKey = m_nIsKey;

	return TRUE;
}

CBaseObject *CTXmlDbTag::Clone()
{
	CTXmlDbTag* pNew = new CTXmlDbTag();

	if (Copy(pNew))
	{
		return pNew;
	}

	return NULL;
}
