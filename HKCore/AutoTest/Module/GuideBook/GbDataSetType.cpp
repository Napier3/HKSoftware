//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbDataSetType.cpp  CGbDataSetType


#include "stdafx.h"
#include "GbDataSetType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbDataSetType::CGbDataSetType()
{
	//��ʼ������
	m_nCanWrite = 0;

	//��ʼ����Ա����
}

CGbDataSetType::~CGbDataSetType()
{
}

long CGbDataSetType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCanWriteKey, oElement, m_nCanWrite);
	return 0;
}

long CGbDataSetType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCanWriteKey, oNode, m_nCanWrite);
	return 0;
}

