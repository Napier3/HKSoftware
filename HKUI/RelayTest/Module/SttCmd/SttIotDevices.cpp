//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttIotDevices.cpp  CSttIotDevices


#include "stdafx.h"
#include "SttIotDevices.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttIotDevices::CSttIotDevices()
{
	//初始化属性

	//初始化成员变量
}

CSttIotDevices::~CSttIotDevices()
{
}

long CSttIotDevices::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttIotDevices::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttIotDevices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttIotDevices::InitAfterRead()
{
}

BOOL CSttIotDevices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttIotDevices *p = (CSttIotDevices*)pObj;

	return TRUE;
}

BOOL CSttIotDevices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttIotDevices *p = (CSttIotDevices*)pDest;

	return TRUE;
}

CBaseObject* CSttIotDevices::Clone()
{
	CSttIotDevices *p = new CSttIotDevices();
	Copy(p);
	return p;
}

CBaseObject* CSttIotDevices::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttIotDevices *p = new CSttIotDevices();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttIotDevices::CanPaste(UINT nClassID)
{
	if (nClassID == STTCMDCLASSID_CSTTIOTDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttIotDevices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttIotDeviceKey)
	{
		pNew = new CSttIotDevice();
	}

	return pNew;
}

CExBaseObject* CSttIotDevices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTIOTDEVICE)
	{
		pNew = new CSttIotDevice();
	}

	return pNew;
}
