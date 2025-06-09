//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrDevices.cpp  CAtsSvrDevices


#include "stdafx.h"
#include "AtsSvrDevices.h"

CAtsSvrDevices::CAtsSvrDevices()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrDevices::~CAtsSvrDevices()
{
}

long CAtsSvrDevices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrDevices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrDevices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAtsSvrDevices::InitAfterRead()
{
}

BOOL CAtsSvrDevices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAtsSvrDevices *p = (CAtsSvrDevices*)pObj;

	return TRUE;
}

BOOL CAtsSvrDevices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAtsSvrDevices *p = (CAtsSvrDevices*)pDest;

	return TRUE;
}

CBaseObject* CAtsSvrDevices::Clone()
{
	CAtsSvrDevices *p = new CAtsSvrDevices();
	Copy(p);
	return p;
}

BOOL CAtsSvrDevices::CanPaste(UINT nClassID)
{
	if (nClassID == ATSVRCLASSID_CATSSVRDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAtsSvrDevices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrDeviceKey)
	{
		pNew = new CAtsSvrDevice();
	}

	return pNew;
}

CExBaseObject* CAtsSvrDevices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRDEVICE)
	{
		pNew = new CAtsSvrDevice();
	}

	return pNew;
}
