//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_HisTask.cpp  CAts_HisTask


#include "stdafx.h"
#include "Ats_HisTask.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_HisTask::CAts_HisTask()
{
	//初始化属性

	//初始化成员变量
}

CAts_HisTask::~CAts_HisTask()
{
}

long CAts_HisTask::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAts_RTTask::XmlReadOwn(oNode, pXmlRWKeys);
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisTask::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAts_RTTask::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisTask::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAts_RTTask::SerializeOwn(oBinaryBuffer);
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

void CAts_HisTask::InitAfterRead()
{
}

BOOL CAts_HisTask::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAts_RTTask::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_HisTask *p = (CAts_HisTask*)pObj;

	return TRUE;
}

BOOL CAts_HisTask::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_RTTask::CopyOwn(pDest);

	CAts_HisTask *p = (CAts_HisTask*)pDest;

	return TRUE;
}

CBaseObject* CAts_HisTask::Clone()
{
	CAts_HisTask *p = new CAts_HisTask();
	Copy(p);
	return p;
}

CBaseObject* CAts_HisTask::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_HisTask *p = new CAts_HisTask();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_HisTask::CanPaste(UINT nClassID)
{
	if (nClassID == ATSCLASSID_CATS_HISTASKBATCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_HisTask::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_HisTaskBatchKey)
	{
		pNew = new CAts_HisTaskBatch();
	}

	return pNew;
}

CExBaseObject* CAts_HisTask::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSCLASSID_CATS_HISTASKBATCH)
	{
		pNew = new CAts_HisTaskBatch();
	}

	return pNew;
}
CExBaseObject* CAts_HisTask::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_HisTaskBatch();

	return pNew;
}

void CAts_HisTask::ClearPKValue()
{
	m_nIndex_Task = 0;

	POS pos = GetHeadPosition();
	CAts_HisTaskBatch *pHisTaskBatch = NULL;

	while(pos != NULL)
	{
		pHisTaskBatch = (CAts_HisTaskBatch *)GetNext(pos);
		pHisTaskBatch->ClearPKValue();
	}
}

long CAts_HisTask::UpdateDBFromRTTask(CXDbBaseLib *pXDbLib,CAts_RTTask *pRTTask)
{
	pRTTask->CopyOwn(this);

	m_nIndex_Task = 0;
	DB_Insert_Own(pXDbLib,NULL,CATSMNGRXmlRWKeys::g_pXmlKeys,NULL);

	return m_nIndex_Task;
}