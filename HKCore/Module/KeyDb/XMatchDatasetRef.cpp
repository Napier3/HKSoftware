//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchDatasetRef.cpp  CXMatchDatasetRef


#include "stdafx.h"
#include "XMatchDatasetRef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchDatasetRef::CXMatchDatasetRef()
{
	//初始化属性

	//初始化成员变量
}

CXMatchDatasetRef::~CXMatchDatasetRef()
{
}

long CXMatchDatasetRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CXMatchDatasetRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	return 0;
}

