//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	//初始化属性

	//初始化成员变量
}

CIot_TestTaskDevices::~CIot_TestTaskDevices()
{
}

long CIot_TestTaskDevices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TestTaskDevices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

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
	if (nClassID == IOTCLASSID_CIOT_TESTTASKDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TestTaskDevices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TestTaskDeviceKey)
	{
		pNew = new CIot_TestTaskDevice();
	}

	return pNew;
}

CExBaseObject* CIot_TestTaskDevices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TESTTASKDEVICE)
	{
		pNew = new CIot_TestTaskDevice();
	}

	return pNew;
}
CExBaseObject* CIot_TestTaskDevices::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_TestTaskDevice();

	return pNew;
}
