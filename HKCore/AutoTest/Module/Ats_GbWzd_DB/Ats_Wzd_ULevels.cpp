//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_ULevels.cpp  CAts_Wzd_ULevels


#include "stdafx.h"
#include "Ats_Wzd_ULevels.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_ULevels::CAts_Wzd_ULevels()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_ULevels::~CAts_Wzd_ULevels()
{
}

long CAts_Wzd_ULevels::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_ULevels::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_ULevels::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_ULevels::InitAfterRead()
{
}

BOOL CAts_Wzd_ULevels::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_ULevels *p = (CAts_Wzd_ULevels*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_ULevels::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_ULevels *p = (CAts_Wzd_ULevels*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_ULevels::Clone()
{
	CAts_Wzd_ULevels *p = new CAts_Wzd_ULevels();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_ULevels::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_ULevels *p = new CAts_Wzd_ULevels();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_ULevels::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_ULEVEL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_ULevels::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_ULevelKey)
	{
		pNew = new CAts_Wzd_ULevel();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_ULevels::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_ULEVEL)
	{
		pNew = new CAts_Wzd_ULevel();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_ULevels::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_ULevel();

	return pNew;
}
