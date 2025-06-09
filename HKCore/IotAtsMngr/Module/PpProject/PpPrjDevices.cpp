//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpPrjDevices.cpp  CPpPrjDevices


#include "stdafx.h"
#include "PpPrjDevices.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPpPrjDevices::CPpPrjDevices()
{
	//初始化属性

	//初始化成员变量
}

CPpPrjDevices::~CPpPrjDevices()
{
}

long CPpPrjDevices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPpPrjXmlRWKeys *pXmlKeys = (CPpPrjXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpPrjDevices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPpPrjXmlRWKeys *pXmlKeys = (CPpPrjXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpPrjDevices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPpPrjDevices::InitAfterRead()
{
}

BOOL CPpPrjDevices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPpPrjDevices *p = (CPpPrjDevices*)pObj;

	return TRUE;
}

BOOL CPpPrjDevices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPpPrjDevices *p = (CPpPrjDevices*)pDest;

	return TRUE;
}

CBaseObject* CPpPrjDevices::Clone()
{
	CPpPrjDevices *p = new CPpPrjDevices();
	Copy(p);
	return p;
}

CBaseObject* CPpPrjDevices::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPpPrjDevices *p = new CPpPrjDevices();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPpPrjDevices::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CPPPRJDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpPrjDevices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPpPrjXmlRWKeys *pXmlKeys = (CPpPrjXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpPrjDeviceKey)
	{
		pNew = new CPpPrjDevice();
	}

	return pNew;
}

CExBaseObject* CPpPrjDevices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CPPPRJDEVICE)
	{
		pNew = new CPpPrjDevice();
	}

	return pNew;
}