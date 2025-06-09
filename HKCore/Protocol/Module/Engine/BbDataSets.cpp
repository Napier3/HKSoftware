#include "StdAfx.h"

#include "BbDataSets.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBbDataSets::CBbDataSets(void)
{
	
// 	 m_strSetCountMax=0;
// 	 m_strSetCountMin=0;

}

CBbDataSets::~CBbDataSets(void)
{

}

long CBbDataSets::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_strMaxKey, oNode,m_strSetCountMax );
	xml_GetAttibuteValue(pKeys->m_strMinKey,oNode,m_strSetCountMin);
	
	return 0;
}

long CBbDataSets::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKeys->m_strMaxKey, oElement,m_strSetCountMax );
	xml_SetAttributeValue(pKeys->m_strMinKey,oElement,m_strSetCountMin);

	return 0;
}

long CBbDataSets::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CBbDataSets::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return NULL;
}

CExBaseObject* CBbDataSets::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CBbDataSets::IsEqualOwn(CBaseObject* pObj)
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

	if (m_strSetCountMax != ((CBbDataSets*)pObj)->m_strSetCountMax)
	{
		return FALSE;
	}

	if (m_strSetCountMin != ((CBbDataSets*)pObj)->m_strSetCountMin)
	{
		return FALSE;
	}

	return CByteBlocks::IsEqualOwn(pObj);
}

CBaseObject* CBbDataSets::Clone()
{
	CBbDataSets* pNew = new CBbDataSets();
	Copy(pNew);
	return pNew;
}

BOOL CBbDataSets::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CBbDataSets*)pDest)->m_strSetCountMax = m_strSetCountMax;
	((CBbDataSets*)pDest)->m_strSetCountMin = m_strSetCountMin;

	return CByteBlocks::CopyOwn(pDest);
}