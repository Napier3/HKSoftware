//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBatchDataMap.cpp  CRptBatchDataMap


#include "stdafx.h"
#include "RptBatchDataMap.h"

CRptBatchDataMap::CRptBatchDataMap()
{
	//初始化属性
	m_nRepeatIndex = 0;
	m_strPrecision ;
	m_nMapIndex = 0;
	m_pDataRef = NULL;

	//初始化成员变量
}

CRptBatchDataMap::~CRptBatchDataMap()
{
}

long CRptBatchDataMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRepeatIndexKey, oNode, m_nRepeatIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strDataAttrKey, oNode, m_strDataAttr);
	xml_GetAttibuteValue(pXmlKeys->m_strPrecisionKey, oNode, m_strPrecision);
	xml_GetAttibuteValue(pXmlKeys->m_strMapIndexKey, oNode, m_nMapIndex);
	return 0;
}

long CRptBatchDataMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRepeatIndexKey, oElement, m_nRepeatIndex);
	xml_SetAttributeValue(pXmlKeys->m_strDataAttrKey, oElement, m_strDataAttr);
	xml_SetAttributeValue(pXmlKeys->m_strPrecisionKey, oElement, m_strPrecision);
	xml_SetAttributeValue(pXmlKeys->m_strMapIndexKey, oElement, m_nMapIndex);
	return 0;
}

BOOL CRptBatchDataMap::IsMaped()
{
	return ( (m_strID.GetLength() > 0) && (m_pDataRef != NULL) );
}

