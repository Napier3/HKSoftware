//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrRsTestAppRef.cpp  CAtsSvrRsTestAppRef


#include "stdafx.h"
#include "AtsSvrRsTestAppRef.h"

CAtsSvrRsTestAppRef::CAtsSvrRsTestAppRef()
{
	//��ʼ������

	//��ʼ����Ա����
}

CAtsSvrRsTestAppRef::~CAtsSvrRsTestAppRef()
{
}

long CAtsSvrRsTestAppRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrRsTestAppRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrRsTestAppRef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

CBaseObject* CAtsSvrRsTestAppRef::Clone()
{
	CAtsSvrRsTestAppRef *p = new CAtsSvrRsTestAppRef();
	Copy(p);
	return p;
}

BOOL CAtsSvrRsTestAppRef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrRsTestAppRef *p = (CAtsSvrRsTestAppRef*)pObj;

	return TRUE;
}

BOOL CAtsSvrRsTestAppRef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrRsTestAppRef *p = (CAtsSvrRsTestAppRef*)pDest;

	return TRUE;
}

