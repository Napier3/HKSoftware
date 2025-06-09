//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_OperMaintainCops.cpp  CAts_Wzd_OperMaintainCops


#include "stdafx.h"
#include "Ats_Wzd_OperMaintainCops.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_OperMaintainCops::CAts_Wzd_OperMaintainCops()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_OperMaintainCops::~CAts_Wzd_OperMaintainCops()
{
}

long CAts_Wzd_OperMaintainCops::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_OperMaintainCops::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_OperMaintainCops::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_OperMaintainCops::InitAfterRead()
{
}

BOOL CAts_Wzd_OperMaintainCops::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_OperMaintainCops *p = (CAts_Wzd_OperMaintainCops*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_OperMaintainCops::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_OperMaintainCops *p = (CAts_Wzd_OperMaintainCops*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_OperMaintainCops::Clone()
{
	CAts_Wzd_OperMaintainCops *p = new CAts_Wzd_OperMaintainCops();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_OperMaintainCops::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_OperMaintainCops *p = new CAts_Wzd_OperMaintainCops();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_OperMaintainCops::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_OPERMAINTAINCOP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_OperMaintainCops::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_OperMaintainCopKey)
	{
		pNew = new CAts_Wzd_OperMaintainCop();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_OperMaintainCops::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_OPERMAINTAINCOP)
	{
		pNew = new CAts_Wzd_OperMaintainCop();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_OperMaintainCops::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_OperMaintainCop();

	return pNew;
}
