//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XMatchDatasetRef.cpp  CXMatchDatasetRef


#include "stdafx.h"
#include "XMatchDatasetRef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchDatasetRef::CXMatchDatasetRef()
{
	//��ʼ������

	//��ʼ����Ա����
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

