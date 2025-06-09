//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PdfDBHead.cpp  CPdfDBHead


#include "stdafx.h"
#include "PdfDBHead.h"

CPdfDBHead::CPdfDBHead()
{
	//��ʼ������
	m_nNameHead = -1;
	m_nDWHead = -1;
	m_nValueHead = -1;
	m_nExistHead = -1;

	//��ʼ����Ա����
}

CPdfDBHead::~CPdfDBHead()
{
}

long CPdfDBHead::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CPdfHLParseXmlRWKeys *pXmlKeys = (CPdfHLParseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameHeadKey, oNode, m_nNameHead);
	xml_GetAttibuteValue(pXmlKeys->m_strDWHeadKey, oNode, m_nDWHead);
	xml_GetAttibuteValue(pXmlKeys->m_strValueHeadKey, oNode, m_nValueHead);
	xml_GetAttibuteValue(pXmlKeys->m_strExistHeadKey, oNode, m_nExistHead);
	return 0;
}

long CPdfDBHead::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CPdfHLParseXmlRWKeys *pXmlKeys = (CPdfHLParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameHeadKey, oElement, m_nNameHead);
	xml_SetAttributeValue(pXmlKeys->m_strDWHeadKey, oElement, m_nDWHead);
	xml_SetAttributeValue(pXmlKeys->m_strValueHeadKey, oElement, m_nValueHead);
	xml_SetAttributeValue(pXmlKeys->m_strExistHeadKey, oElement, m_nExistHead);
	return 0;
}

