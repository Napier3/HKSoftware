//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchDataref.cpp  CXMatchDataref


#include "stdafx.h"
#include "XMatchDataref.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchDataref::CXMatchDataref()
{
	//初始化属性

	//初始化成员变量
}

CXMatchDataref::~CXMatchDataref()
{
}

long CXMatchDataref::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSrcPathKey, oNode, m_strSrcPath);
	xml_GetAttibuteValue(pXmlKeys->m_strDestPathKey, oNode, m_strDestPath);
	return 0;
}

long CXMatchDataref::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSrcPathKey, oElement, m_strSrcPath);
	xml_SetAttributeValue(pXmlKeys->m_strDestPathKey, oElement, m_strDestPath);
	return 0;
}

