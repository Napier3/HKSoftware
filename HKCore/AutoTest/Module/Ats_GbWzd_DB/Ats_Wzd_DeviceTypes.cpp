//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_DeviceTypes.cpp  CAts_Wzd_DeviceTypes


#include "stdafx.h"
#include "Ats_Wzd_DeviceTypes.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DeviceTypes::CAts_Wzd_DeviceTypes()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_DeviceTypes::~CAts_Wzd_DeviceTypes()
{
}

long CAts_Wzd_DeviceTypes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DeviceTypes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DeviceTypes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_DeviceTypes::InitAfterRead()
{
}

BOOL CAts_Wzd_DeviceTypes::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_DeviceTypes *p = (CAts_Wzd_DeviceTypes*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_DeviceTypes::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_DeviceTypes *p = (CAts_Wzd_DeviceTypes*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_DeviceTypes::Clone()
{
	CAts_Wzd_DeviceTypes *p = new CAts_Wzd_DeviceTypes();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DeviceTypes::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DeviceTypes *p = new CAts_Wzd_DeviceTypes();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_DeviceTypes::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICETYPE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_DeviceTypes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_DeviceTypeKey)
	{
		pNew = new CAts_Wzd_DeviceType();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_DeviceTypes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICETYPE)
	{
		pNew = new CAts_Wzd_DeviceType();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_DeviceTypes::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_DeviceType();

	return pNew;
}
