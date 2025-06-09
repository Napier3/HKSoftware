//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_Templates.cpp  CAts_Wzd_Templates


#include "stdafx.h"
#include "Ats_Wzd_Templates.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_Templates::CAts_Wzd_Templates()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_Templates::~CAts_Wzd_Templates()
{
}

long CAts_Wzd_Templates::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_Templates::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_Templates::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_Templates::InitAfterRead()
{
}

BOOL CAts_Wzd_Templates::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_Templates *p = (CAts_Wzd_Templates*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_Templates::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_Templates *p = (CAts_Wzd_Templates*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_Templates::Clone()
{
	CAts_Wzd_Templates *p = new CAts_Wzd_Templates();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_Templates::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_Templates *p = new CAts_Wzd_Templates();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_Templates::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_Templates::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_TemplateKey)
	{
		pNew = new CAts_Wzd_Template();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_Templates::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATE)
	{
		pNew = new CAts_Wzd_Template();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_Templates::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_Template();

	return pNew;
}
