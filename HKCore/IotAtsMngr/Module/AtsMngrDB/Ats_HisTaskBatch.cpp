//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_HisTaskBatch.cpp  CAts_HisTaskBatch


#include "stdafx.h"
#include "Ats_HisTaskBatch.h"
#include "Ats_HisReports.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_HisTaskBatch::CAts_HisTaskBatch()
{
	//初始化属性

	//初始化成员变量
}

CAts_HisTaskBatch::~CAts_HisTaskBatch()
{
}

long CAts_HisTaskBatch::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAts_RTTaskBatch::XmlReadOwn(oNode, pXmlRWKeys);
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisTaskBatch::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAts_RTTaskBatch::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisTaskBatch::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAts_RTTaskBatch::SerializeOwn(oBinaryBuffer);
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

void CAts_HisTaskBatch::InitAfterRead()
{
}

BOOL CAts_HisTaskBatch::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAts_RTTaskBatch::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_HisTaskBatch *p = (CAts_HisTaskBatch*)pObj;

	return TRUE;
}

BOOL CAts_HisTaskBatch::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_RTTaskBatch::CopyOwn(pDest);

	CAts_HisTaskBatch *p = (CAts_HisTaskBatch*)pDest;

	return TRUE;
}

CBaseObject* CAts_HisTaskBatch::Clone()
{
	CAts_HisTaskBatch *p = new CAts_HisTaskBatch();
	Copy(p);
	return p;
}

CBaseObject* CAts_HisTaskBatch::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_HisTaskBatch *p = new CAts_HisTaskBatch();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_HisTaskBatch::CanPaste(UINT nClassID)
{
	if (nClassID == ATSCLASSID_CATS_HISDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_HisTaskBatch::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_HisDeviceKey)
	{
		pNew = new CAts_HisDevice();
	}

	return pNew;
}

CExBaseObject* CAts_HisTaskBatch::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSCLASSID_CATS_HISDEVICE)
	{
		pNew = new CAts_HisDevice();
	}

	return pNew;
}
CExBaseObject* CAts_HisTaskBatch::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_HisDevice();

	return pNew;
}

BOOL CAts_HisTaskBatch::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSCLASSID_CATS_HISTASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

void CAts_HisTaskBatch::ClearPKValue()
{
	m_nIndex_Task = 0;
	m_nIndex_TaskBatch = 0;

	POS pos = GetHeadPosition();
	CAts_HisDevice *pHisDevice = NULL;

	while(pos != NULL)
	{
		pHisDevice = (CAts_HisDevice *)GetNext(pos);
		pHisDevice->ClearPKValue();
	}
}

BOOL CAts_HisTaskBatch::UpdateDBFromRTTaskBatch(CXDbBaseLib *pXDbLib,CAts_RTTaskBatch *pRTTaskBatch,long nIndex_Task)
{
	//拷贝并清除主外键
	pRTTaskBatch->Copy(this);
	ClearPKValue();

	//更新外键
	m_nIndex_Task = nIndex_Task;
	CXDb_PKeyValue oPKeyValue;
	oPKeyValue.SetValue(m_nIndex_Task);
	oPKeyValue.nClassID = ATSCLASSID_CATS_HISTASK;
	DB_SetForeignKeyValue_Children(CATSMNGRXmlRWKeys::g_pXmlKeys, oPKeyValue);

	pXDbLib->StartTransaction();

	//插入历史表：当前任务批次、装置表
	CXDbQueryChildrenMask oXdbQueryMask;
	oXdbQueryMask.SetQueryAll(TRUE);
	DB_Insert(pXDbLib,CATSMNGRXmlRWKeys::g_pXmlKeys,&oXdbQueryMask);

	//删除实时表：当前任务批次、装置表
	pRTTaskBatch->DB_Delete(pXDbLib,CATSMNGRXmlRWKeys::g_pXmlKeys);

	CAts_HisReports oHisReports;
	oHisReports.UpdateDBFromRTTaskBatch(pXDbLib,pRTTaskBatch->m_nIndex_Task,pRTTaskBatch->m_nIndex_TaskBatch
		,m_nIndex_Task,m_nIndex_TaskBatch);

	pXDbLib->Commit();

	return TRUE;
}