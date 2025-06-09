//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbDataSetTypes.cpp  CGbDataSetTypes


#include "stdafx.h"
#include "GbDataSetTypes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbDataSetTypes::CGbDataSetTypes()
{
	//初始化属性

	//初始化成员变量
}

CGbDataSetTypes::~CGbDataSetTypes()
{
}

long CGbDataSetTypes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CGbDataSetTypes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

