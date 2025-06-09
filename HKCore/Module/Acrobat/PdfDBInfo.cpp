//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PdfDBInfo.cpp  CPdfDBInfo


#include "stdafx.h"
#include "PdfDBInfo.h"

CPdfDBInfo::CPdfDBInfo()
{
	//初始化属性

	//初始化成员变量
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
