//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PdfDBInfo.cpp  CPdfDBInfo


#include "stdafx.h"
#include "PdfDBInfo.h"

CPdfDBInfo::CPdfDBInfo()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPdfDBInfo::~CPdfDBInfo()
{
}

long CPdfDBInfo::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPdfHLParseXmlRWKeys *pXmlKeys = (CPdfHLParseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPdfDBInfo::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPdfHLParseXmlRWKeys *pXmlKeys = (CPdfHLParseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CPdfDBInfo::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPdfHLParseXmlRWKeys *pXmlKeys = (CPdfHLParseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPdfDBTableKey)
	{
		pNew = new CPdfDBTable();
	}

	return pNew;
}
