#include "StdAfx.h"
#include "BbDataSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBbDataSet::CBbDataSet(void)
{
	
// 	 m_strDataCountMin=0;
// 	 m_strDataCountMax=0;

}

CBbDataSet::~CBbDataSet(void)
{

}

long CBbDataSet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_strMaxKey, oNode,m_strDataCountMax );
	xml_GetAttibuteValue(pKeys->m_strMinKey,oNode,m_strDataCountMin);
	
	return 0;
}

long CBbDataSet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKeys->m_strMaxKey, oElement,m_strDataCountMax);
	xml_SetAttributeValue(pKeys->m_strMinKey,oElement,m_strDataCountMin);

	return 0;
}

long CBbDataSet::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CBbDataSet::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return NULL;
}

CExBaseObject* CBbDataSet::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CBbDataSet::IsEqualOwn(CBaseObject* pObj)
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

	if (m_strDataCountMin != ((CBbDataSet*)pObj)->m_strDataCountMin)
	{
		return FALSE;
	}

	if (m_strDataCountMax != ((CBbDataSet*)pObj)->m_strDataCountMax)
	{
		return FALSE;
	}

	return CByteBlocks::IsEqualOwn(pObj);
}

CBaseObject* CBbDataSet::Clone()
{
	CBbDataSet* pNew = new CBbDataSet();
	Copy(pNew);
	return pNew;
}

BOOL CBbDataSet::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CBbDataSet*)pDest)->m_strDataCountMin = m_strDataCountMin;
	((CBbDataSet*)pDest)->m_strDataCountMax = m_strDataCountMax;

	return CByteBlocks::CopyOwn(pDest);
}