//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_DeviceModels.cpp  CAts_Wzd_DeviceModels


#include "stdafx.h"
#include "Ats_Wzd_DeviceModels.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DeviceModels::CAts_Wzd_DeviceModels()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_DeviceModels::~CAts_Wzd_DeviceModels()
{
}

long CAts_Wzd_DeviceModels::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DeviceModels::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DeviceModels::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_DeviceModels::InitAfterRead()
{
}

BOOL CAts_Wzd_DeviceModels::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_DeviceModels *p = (CAts_Wzd_DeviceModels*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_DeviceModels::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_DeviceModels *p = (CAts_Wzd_DeviceModels*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_DeviceModels::Clone()
{
	CAts_Wzd_DeviceModels *p = new CAts_Wzd_DeviceModels();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DeviceModels::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DeviceModels *p = new CAts_Wzd_DeviceModels();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_DeviceModels::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICEMODEL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_DeviceModels::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_DeviceModelKey)
	{
		pNew = new CAts_Wzd_DeviceModel();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_DeviceModels::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICEMODEL)
	{
		pNew = new CAts_Wzd_DeviceModel();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_DeviceModels::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_DeviceModel();

	return pNew;
}
