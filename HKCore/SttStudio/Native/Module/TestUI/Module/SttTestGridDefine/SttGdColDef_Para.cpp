//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttGdColDef_Para.cpp  CSttGdColDef_Para


#include "stdafx.h"
#include "SttGdColDef_Para.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdColDef_Para::CSttGdColDef_Para()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSttGdColDef_Para::~CSttGdColDef_Para()
{
}

long CSttGdColDef_Para::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdColDef_Para::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdColDef_Para::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CSttGdColDef_Para::InitAfterRead()
{
}

BOOL CSttGdColDef_Para::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdColDef_Para *p = (CSttGdColDef_Para*)pObj;

	return TRUE;
}

BOOL CSttGdColDef_Para::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdColDef_Para *p = (CSttGdColDef_Para*)pDest;

	return TRUE;
}

CBaseObject* CSttGdColDef_Para::Clone()
{
	CSttGdColDef_Para *p = new CSttGdColDef_Para();
	Copy(p);
	return p;
}

CBaseObject* CSttGdColDef_Para::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdColDef_Para *p = new CSttGdColDef_Para();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

