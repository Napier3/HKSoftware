//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrDevice.cpp  CAtsSvrDevice


#include "stdafx.h"
#include "AtsSvrDevice.h"

CAtsSvrDevice::CAtsSvrDevice()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrDevice::~CAtsSvrDevice()
{
}

long CAtsSvrDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAtsSvrDevice::InitAfterRead()
{
}

BOOL CAtsSvrDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAtsSvrDevice *p = (CAtsSvrDevice*)pObj;

	return TRUE;
}

BOOL CAtsSvrDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAtsSvrDevice *p = (CAtsSvrDevice*)pDest;

	return TRUE;
}

CBaseObject* CAtsSvrDevice::Clone()
{
	CAtsSvrDevice *p = new CAtsSvrDevice();
	Copy(p);
	return p;
}

CExBaseObject* CAtsSvrDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CAtsSvrDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
BOOL CAtsSvrDevice::CanPaste(UINT nClassID)
{
	return FALSE;
}

