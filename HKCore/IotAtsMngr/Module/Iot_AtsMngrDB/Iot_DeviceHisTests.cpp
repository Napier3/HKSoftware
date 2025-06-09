//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceHisTests.cpp  CIot_DeviceHisTests


#include "stdafx.h"
#include "Iot_DeviceHisTests.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceHisTests::CIot_DeviceHisTests()
{
	//初始化属性

	//初始化成员变量
}

CIot_DeviceHisTests::~CIot_DeviceHisTests()
{
}

long CIot_DeviceHisTests::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceHisTests::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_DeviceHisTests::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_DeviceHisTests::InitAfterRead()
{
}

BOOL CIot_DeviceHisTests::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceHisTests *p = (CIot_DeviceHisTests*)pObj;

	return TRUE;
}

BOOL CIot_DeviceHisTests::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceHisTests *p = (CIot_DeviceHisTests*)pDest;

	return TRUE;
}

CBaseObject* CIot_DeviceHisTests::Clone()
{
	CIot_DeviceHisTests *p = new CIot_DeviceHisTests();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceHisTests::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceHisTests *p = new CIot_DeviceHisTests();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_DeviceHisTests::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICEHISTEST)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_DeviceHisTests::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceHisTestKey)
	{
		pNew = new CIot_DeviceHisTest();
	}

	return pNew;
}

CExBaseObject* CIot_DeviceHisTests::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICEHISTEST)
	{
		pNew = new CIot_DeviceHisTest();
	}

	return pNew;
}
CExBaseObject* CIot_DeviceHisTests::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_DeviceHisTest();

	return pNew;
}
