//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PdfDBTable.cpp  CPdfDBTable


#include "stdafx.h"
#include "PdfDBTable.h"

CPdfDBTable::CPdfDBTable()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPdfDBTable::~CPdfDBTable()
{
}

long CPdfDBTable::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CPdfHLParseXmlRWKeys *pXmlKeys = (CPdfHLParseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPdfDBTable::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CPdfHLParseXmlRWKeys *pXmlKeys = (CPdfHLParseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CPdfDBTable::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPdfHLParseXmlRWKeys *pXmlKeys = (CPdfHLParseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPdfDBHeadKey)
	{
		pNew = new CPdfDBHead();
	}

	return pNew;
}
