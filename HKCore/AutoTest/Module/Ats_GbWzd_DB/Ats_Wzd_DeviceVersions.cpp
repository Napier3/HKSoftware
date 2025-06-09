//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_DeviceVersions.cpp  CAts_Wzd_DeviceVersions


#include "stdafx.h"
#include "Ats_Wzd_DeviceVersions.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DeviceVersions::CAts_Wzd_DeviceVersions()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_DeviceVersions::~CAts_Wzd_DeviceVersions()
{
}

long CAts_Wzd_DeviceVersions::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DeviceVersions::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DeviceVersions::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_DeviceVersions::InitAfterRead()
{
}

BOOL CAts_Wzd_DeviceVersions::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_DeviceVersions *p = (CAts_Wzd_DeviceVersions*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_DeviceVersions::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_DeviceVersions *p = (CAts_Wzd_DeviceVersions*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_DeviceVersions::Clone()
{
	CAts_Wzd_DeviceVersions *p = new CAts_Wzd_DeviceVersions();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DeviceVersions::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DeviceVersions *p = new CAts_Wzd_DeviceVersions();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_DeviceVersions::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICEVERSION)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_DeviceVersions::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_DeviceVersionKey)
	{
		pNew = new CAts_Wzd_DeviceVersion();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_DeviceVersions::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICEVERSION)
	{
		pNew = new CAts_Wzd_DeviceVersion();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_DeviceVersions::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_DeviceVersion();

	return pNew;
}
