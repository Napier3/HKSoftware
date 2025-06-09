//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_HisTasks.cpp  CAts_HisTasks


#include "stdafx.h"
#include "Ats_HisTasks.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_HisTasks::CAts_HisTasks()
{
	//初始化属性

	//初始化成员变量
}

CAts_HisTasks::~CAts_HisTasks()
{
}

long CAts_HisTasks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisTasks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisTasks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_HisTasks::InitAfterRead()
{
}

BOOL CAts_HisTasks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_HisTasks *p = (CAts_HisTasks*)pObj;

	return TRUE;
}

BOOL CAts_HisTasks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_HisTasks *p = (CAts_HisTasks*)pDest;

	return TRUE;
}

CBaseObject* CAts_HisTasks::Clone()
{
	CAts_HisTasks *p = new CAts_HisTasks();
	Copy(p);
	return p;
}

CBaseObject* CAts_HisTasks::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_HisTasks *p = new CAts_HisTasks();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_HisTasks::CanPaste(UINT nClassID)
{
	if (nClassID == ATSCLASSID_CATS_HISTASK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_HisTasks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_HisTaskKey)
	{
		pNew = new CAts_HisTask();
	}

	return pNew;
}

CExBaseObject* CAts_HisTasks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSCLASSID_CATS_HISTASK)
	{
		pNew = new CAts_HisTask();
	}

	return pNew;
}
CExBaseObject* CAts_HisTasks::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_HisTask();

	return pNew;
}
