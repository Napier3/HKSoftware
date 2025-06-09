#include "StdAfx.h"
#include "DvDataType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDvDataType::CDvDataType(void)
{
}

CDvDataType::~CDvDataType(void)
{
}

long CDvDataType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKey->m_strIDKey, oNode, m_nID);

	return 0;
}

long CDvDataType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKey->m_strIDKey, oElement, m_nID);

	return 0;
}

long CDvDataType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CDvDataType::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_nID != ((CDvDataType*)pObj)->m_nID)
	{
		return FALSE;
	}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CDvDataType::Clone()
{
	CDvDataType* pNew = new CDvDataType();
	Copy(pNew);
	return pNew;
}

BOOL CDvDataType::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CDvDataType*)pDest)->m_nID = m_nID;

	return CExBaseObject::CopyOwn(pDest);
}