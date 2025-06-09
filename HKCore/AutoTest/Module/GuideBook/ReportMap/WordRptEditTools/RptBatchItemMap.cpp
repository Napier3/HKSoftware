//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptBatchItemMap.cpp  CRptBatchItemMap


#include "stdafx.h"
#include "RptBatchItemMap.h"

CRptBatchItemMap::CRptBatchItemMap()
{
	//��ʼ������
	m_nItemIndex = -1;
	m_nMapIndex = -1;

	//��ʼ����Ա����
	m_pItemRef = NULL;
}

CRptBatchItemMap::~CRptBatchItemMap()
{
}

long CRptBatchItemMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strItemIndexKey, oNode, m_nItemIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strMapIndexKey, oNode, m_nMapIndex);
	return 0;
}

long CRptBatchItemMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strItemIndexKey, oElement, m_nItemIndex);
	xml_SetAttributeValue(pXmlKeys->m_strMapIndexKey, oElement, m_nMapIndex);
	return 0;
}

