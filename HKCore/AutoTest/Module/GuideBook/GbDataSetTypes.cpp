//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbDataSetTypes.cpp  CGbDataSetTypes


#include "stdafx.h"
#include "GbDataSetTypes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbDataSetTypes::CGbDataSetTypes()
{
	//��ʼ������

	//��ʼ����Ա����
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

