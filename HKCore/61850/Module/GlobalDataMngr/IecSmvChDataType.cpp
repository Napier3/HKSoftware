//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecSmvChDataType.cpp  CIecSmvChDataType


#include "stdafx.h"
#include "IecSmvChDataType.h"

CIecSmvChDataType::CIecSmvChDataType()
{
	//��ʼ������

	//��ʼ����Ա����
}

CIecSmvChDataType::~CIecSmvChDataType()
{
}

long CIecSmvChDataType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataType::XmlReadOwn(oNode, pXmlRWKeys);
	CIecGlobalDataMngrXmlRWKeys *pXmlKeys = (CIecGlobalDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecSmvChDataType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataType::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIecGlobalDataMngrXmlRWKeys *pXmlKeys = (CIecGlobalDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecSmvChDataType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataType::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecSmvChDataType *p = (CIecSmvChDataType*)pObj;

	return TRUE;
}

BOOL CIecSmvChDataType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataType::CopyOwn(pDest);

	CIecSmvChDataType *p = (CIecSmvChDataType*)pDest;

	return TRUE;
}

CBaseObject* CIecSmvChDataType::Clone()
{
	CIecSmvChDataType *p = new CIecSmvChDataType();
	Copy(p);
	return p;
}

