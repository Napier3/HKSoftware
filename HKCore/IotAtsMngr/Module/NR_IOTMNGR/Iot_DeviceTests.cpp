//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceTests.cpp  CIot_DeviceTests


#include "stdafx.h"
#include "Iot_DeviceTests.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceTests::CIot_DeviceTests()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceTests::~CIot_DeviceTests()
{
}

long CIot_DeviceTests::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceTests::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceTests::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceTests::InitAfterRead()
{
}

BOOL CIot_DeviceTests::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceTests *p = (CIot_DeviceTests*)pObj;

	return TRUE;
}

BOOL CIot_DeviceTests::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceTests *p = (CIot_DeviceTests*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceTests::Clone()
{
	CIot_DeviceTests *p = new CIot_DeviceTests();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceTests::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceTests *p = new CIot_DeviceTests();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceTests::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICETEST)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceTests::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceTestKey)
	{
		pNew = new CIot_DeviceTest();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceTests::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICETEST)
	{
		pNew = new CIot_DeviceTest();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceTests::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceTest();

	return pNew;
}
