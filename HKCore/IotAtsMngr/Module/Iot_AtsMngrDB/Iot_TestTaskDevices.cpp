//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_TestTaskDevices.cpp  CIot_TestTaskDevices


#include "stdafx.h"
#include "Iot_TestTaskDevices.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TestTaskDevices::CIot_TestTaskDevices()
{
	//��ʼ������

	//��ʼ����Ա����
}

CIot_TestTaskDevices::~CIot_TestTaskDevices()
{
}

long CIot_TestTaskDevices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TestTaskDevices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TestTaskDevices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CIot_TestTaskDevices::InitAfterRead()
{
}

BOOL CIot_TestTaskDevices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TestTaskDevices *p = (CIot_TestTaskDevices*)pObj;

	return TRUE;
}

BOOL CIot_TestTaskDevices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TestTaskDevices *p = (CIot_TestTaskDevices*)pDest;

	return TRUE;
}

CBaseObject* CIot_TestTaskDevices::Clone()
{
	CIot_TestTaskDevices *p = new CIot_TestTaskDevices();
	Copy(p);
	return p;
}

CBaseObject* CIot_TestTaskDevices::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TestTaskDevices *p = new CIot_TestTaskDevices();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TestTaskDevices::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CIot_TestTaskDevices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CIot_TestTaskDevices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
