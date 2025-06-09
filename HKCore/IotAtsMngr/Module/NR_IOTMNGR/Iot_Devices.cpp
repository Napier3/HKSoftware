//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Devices.cpp  CIot_Devices


#include "stdafx.h"
#include "Iot_Devices.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Devices::CIot_Devices()
{
	//初始化属性

	//初始化成员变量
}

CIot_Devices::~CIot_Devices()
{
}

long CIot_Devices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Devices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Devices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Devices::InitAfterRead()
{
}

BOOL CIot_Devices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Devices *p = (CIot_Devices*)pObj;

	return TRUE;
}

BOOL CIot_Devices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Devices *p = (CIot_Devices*)pDest;

	return TRUE;
}

CBaseObject* CIot_Devices::Clone()
{
	CIot_Devices *p = new CIot_Devices();
	Copy(p);
	return p;
}

CBaseObject* CIot_Devices::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Devices *p = new CIot_Devices();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Devices::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_DEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Devices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_DeviceKey)
	{
		pNew = new CIot_Device();
	}

	return pNew;
}

CExBaseObject* CIot_Devices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_DEVICE)
	{
		pNew = new CIot_Device();
	}

	return pNew;
}
CExBaseObject* CIot_Devices::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Device();

	return pNew;
}
