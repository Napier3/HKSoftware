//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_TestApps.cpp  CIot_TestApps


#include "stdafx.h"
#include "Iot_TestApps.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TestApps::CIot_TestApps()
{
	//��ʼ������

	//��ʼ����Ա����
}

CIot_TestApps::~CIot_TestApps()
{
}

long CIot_TestApps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TestApps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TestApps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_TestApps::InitAfterRead()
{
}

BOOL CIot_TestApps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TestApps *p = (CIot_TestApps*)pObj;

	return TRUE;
}

BOOL CIot_TestApps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TestApps *p = (CIot_TestApps*)pDest;

	return TRUE;
}

CBaseObject* CIot_TestApps::Clone()
{
	CIot_TestApps *p = new CIot_TestApps();
	Copy(p);
	return p;
}

CBaseObject* CIot_TestApps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TestApps *p = new CIot_TestApps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TestApps::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TESTAPP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TestApps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TestAppKey)
	{
		pNew = new CIot_TestApp();
	}

	return pNew;
}

CExBaseObject* CIot_TestApps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TESTAPP)
	{
		pNew = new CIot_TestApp();
	}

	return pNew;
}
CExBaseObject* CIot_TestApps::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_TestApp();

	return pNew;
}
