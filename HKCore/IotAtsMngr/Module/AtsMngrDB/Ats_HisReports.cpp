//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_HisReports.cpp  CAts_HisReports


#include "stdafx.h"
#include "Ats_HisReports.h"
#include "Ats_RTReports.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_HisReports::CAts_HisReports()
{
	//初始化属性

	//初始化成员变量
}

CAts_HisReports::~CAts_HisReports()
{
}

long CAts_HisReports::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisReports::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisReports::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_HisReports::InitAfterRead()
{
}

BOOL CAts_HisReports::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_HisReports *p = (CAts_HisReports*)pObj;

	return TRUE;
}

BOOL CAts_HisReports::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_HisReports *p = (CAts_HisReports*)pDest;

	return TRUE;
}

CBaseObject* CAts_HisReports::Clone()
{
	CAts_HisReports *p = new CAts_HisReports();
	Copy(p);
	return p;
}

CBaseObject* CAts_HisReports::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_HisReports *p = new CAts_HisReports();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_HisReports::CanPaste(UINT nClassID)
{
	if (nClassID == ATSCLASSID_CATS_HISREPORT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_HisReports::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_HisReportKey)
	{
		pNew = new CAts_HisReport();
	}

	return pNew;
}

CExBaseObject* CAts_HisReports::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSCLASSID_CATS_HISREPORT)
	{
		pNew = new CAts_HisReport();
	}

	return pNew;
}
CExBaseObject* CAts_HisReports::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_HisReport();

	return pNew;
}

void CAts_HisReports::ClearPKValue()
{
	POS pos = GetHeadPosition();
	CAts_HisReport *p = NULL;

	while(pos != NULL)
	{
		p = (CAts_HisReport *)GetNext(pos);

		p->m_nIndex_Report = 0;
		p->m_nIndex_Task = 0;
		p->m_nIndex_TaskBatch = 0;
	}
}

BOOL CAts_HisReports::UpdateDBFromRTTaskBatch(CXDbBaseLib *pXDbLib,long nIndex_RTTask,long nIndex_RTTaskBatch
											  ,long nIndex_HisTask,long nIndex_HisTaskBatch)
{
	//查询实时报告
	CAts_RTReports oRTReports;
	oRTReports.QueryRTRepors(pXDbLib,nIndex_RTTask,nIndex_RTTaskBatch);

	//拷贝并清除主外键
	oRTReports.Copy(this);
	ClearPKValue();

	//更新外键m_nIndex_Task
	CXDb_PKeyValue oPKeyValue;
	oPKeyValue.SetValue(nIndex_HisTask);
	oPKeyValue.nClassID = ATSCLASSID_CATS_HISTASK;
	DB_SetForeignKeyValue_Children(CATSMNGRXmlRWKeys::g_pXmlKeys, oPKeyValue);

	//更新外键m_nIndex_TaskBatch
	oPKeyValue.SetValue(nIndex_HisTaskBatch);
	oPKeyValue.nClassID = ATSCLASSID_CATS_HISTASKBATCH;
	DB_SetForeignKeyValue_Children(CATSMNGRXmlRWKeys::g_pXmlKeys, oPKeyValue);

	//插入历史表
	DB_Insert_Children(pXDbLib,CATSMNGRXmlRWKeys::g_pXmlKeys,NULL);

	//删除实时表
	oRTReports.DB_DeleteChildren(pXDbLib,CATSMNGRXmlRWKeys::g_pXmlKeys);

	return TRUE;
}