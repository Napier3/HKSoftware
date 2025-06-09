//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_RTReports.cpp  CAts_RTReports


#include "stdafx.h"
#include "Ats_RTReports.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_RTReports::CAts_RTReports()
{
	//初始化属性

	//初始化成员变量
}

CAts_RTReports::~CAts_RTReports()
{
}

long CAts_RTReports::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_RTReports::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_RTReports::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_RTReports::InitAfterRead()
{
}

BOOL CAts_RTReports::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_RTReports *p = (CAts_RTReports*)pObj;

	return TRUE;
}

BOOL CAts_RTReports::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_RTReports *p = (CAts_RTReports*)pDest;

	return TRUE;
}

CBaseObject* CAts_RTReports::Clone()
{
	CAts_RTReports *p = new CAts_RTReports();
	Copy(p);
	return p;
}

CBaseObject* CAts_RTReports::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_RTReports *p = new CAts_RTReports();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_RTReports::CanPaste(UINT nClassID)
{
	if (nClassID == ATSCLASSID_CATS_RTREPORT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_RTReports::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_RTReportKey)
	{
		pNew = new CAts_RTReport();
	}

	return pNew;
}

CExBaseObject* CAts_RTReports::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSCLASSID_CATS_RTREPORT)
	{
		pNew = new CAts_RTReport();
	}

	return pNew;
}
CExBaseObject* CAts_RTReports::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_RTReport();

	return pNew;
}

BOOL CAts_RTReports::QueryRTRepors(CXDbBaseLib *pXDbLib,long nIndex_Task,long nIndex_TaskBatch)
{
	CString strTable,strIndex_TaskKey,strIndex_TaskBatchKey,strSql;
	strTable = CATSMNGRXmlRWKeys::CAts_RTReportKey();
	strIndex_TaskKey = CATSMNGRXmlRWKeys::Index_TaskKey();
	strIndex_TaskBatchKey = CATSMNGRXmlRWKeys::Index_TaskBatchKey();

	strSql.Format(_T("select * from %s where (%s=%d) and (%s=%d)"),strTable
		,strIndex_TaskBatchKey,nIndex_TaskBatch,strIndex_TaskKey,nIndex_Task);

	return DB_SelectSqlEx(pXDbLib,CATSMNGRXmlRWKeys::g_pXmlKeys,strSql);
}