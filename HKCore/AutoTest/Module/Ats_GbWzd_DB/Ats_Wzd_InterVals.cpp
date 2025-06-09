//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_InterVals.cpp  CAts_Wzd_InterVals


#include "stdafx.h"
#include "Ats_Wzd_InterVals.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_InterVals::CAts_Wzd_InterVals()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_InterVals::~CAts_Wzd_InterVals()
{
}

long CAts_Wzd_InterVals::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_InterVals::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_InterVals::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_InterVals::InitAfterRead()
{
}

BOOL CAts_Wzd_InterVals::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_InterVals *p = (CAts_Wzd_InterVals*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_InterVals::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_InterVals *p = (CAts_Wzd_InterVals*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_InterVals::Clone()
{
	CAts_Wzd_InterVals *p = new CAts_Wzd_InterVals();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_InterVals::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_InterVals *p = new CAts_Wzd_InterVals();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_InterVals::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_INTERVAL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_InterVals::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_InterValKey)
	{
		pNew = new CAts_Wzd_InterVal();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_InterVals::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_INTERVAL)
	{
		pNew = new CAts_Wzd_InterVal();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_InterVals::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_InterVal();

	return pNew;
}
