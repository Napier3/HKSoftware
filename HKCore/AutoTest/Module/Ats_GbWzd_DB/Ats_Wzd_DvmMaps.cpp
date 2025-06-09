//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_DvmMaps.cpp  CAts_Wzd_DvmMaps


#include "stdafx.h"
#include "Ats_Wzd_DvmMaps.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DvmMaps::CAts_Wzd_DvmMaps()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_DvmMaps::~CAts_Wzd_DvmMaps()
{
}

long CAts_Wzd_DvmMaps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DvmMaps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_DvmMaps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_DvmMaps::InitAfterRead()
{
}

BOOL CAts_Wzd_DvmMaps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_DvmMaps *p = (CAts_Wzd_DvmMaps*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_DvmMaps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_DvmMaps *p = (CAts_Wzd_DvmMaps*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_DvmMaps::Clone()
{
	CAts_Wzd_DvmMaps *p = new CAts_Wzd_DvmMaps();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DvmMaps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DvmMaps *p = new CAts_Wzd_DvmMaps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_DvmMaps::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DVMMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_DvmMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_DvmMapKey)
	{
		pNew = new CAts_Wzd_DvmMap();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_DvmMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DVMMAP)
	{
		pNew = new CAts_Wzd_DvmMap();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_DvmMaps::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_DvmMap();

	return pNew;
}
