//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Bench.cpp  CIot_Bench


#include "stdafx.h"
#include "Iot_Bench.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Bench::CIot_Bench()
{
	//初始化属性
	m_nIndex_Bench = 0;
	m_nIndex_Dept = 0;
	m_nIndex_Device_Classify = 0;
	m_nStatus = TEST_BENCH_STATE_NORMAL;
	::GetLocalTime(&m_tmCreate_Time);
	m_nIndex_Test_Task = 0;
	m_nIndex_Items = 0;

	//初始化成员变量
}

CIot_Bench::~CIot_Bench()
{
}

long CIot_Bench::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeptKey, oNode, m_nIndex_Dept);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strCodeKey, oNode, m_strCode);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_nStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_TaskKey, oNode, m_nIndex_Test_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ItemsKey, oNode, m_nIndex_Items);
	xml_GetAttibuteValue(pXmlKeys->m_strName_Template_FileKey, oNode, m_strName_Template_File);
	xml_GetAttibuteValue(pXmlKeys->m_strId_UserKey, oNode, m_strId_User);
	return 0;
}

long CIot_Bench::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeptKey, oElement, m_nIndex_Dept);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strCodeKey, oElement, m_strCode);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_nStatus);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_TaskKey, oElement, m_nIndex_Test_Task);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ItemsKey, oElement, m_nIndex_Items);
	xml_SetAttributeValue(pXmlKeys->m_strName_Template_FileKey, oElement, m_strName_Template_File);
	xml_SetAttributeValue(pXmlKeys->m_strId_UserKey, oElement, m_strId_User);
	return 0;
}

long CIot_Bench::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeCalLen(oBinaryBuffer, m_strCode);
		BinarySerializeCalLen(oBinaryBuffer, m_nStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_Template_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strId_User);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeRead(oBinaryBuffer, m_strCode);
		BinarySerializeRead(oBinaryBuffer, m_nStatus);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeRead(oBinaryBuffer, m_strName_Template_File);
		BinarySerializeRead(oBinaryBuffer, m_strId_User);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeWrite(oBinaryBuffer, m_strCode);
		BinarySerializeWrite(oBinaryBuffer, m_nStatus);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeWrite(oBinaryBuffer, m_strName_Template_File);
		BinarySerializeWrite(oBinaryBuffer, m_strId_User);
	}
	return 0;
}

void CIot_Bench::InitAfterRead()
{
}

BOOL CIot_Bench::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Bench *p = (CIot_Bench*)pObj;

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	if(m_nIndex_Dept != p->m_nIndex_Dept)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Classify != p->m_nIndex_Device_Classify)
	{
		return FALSE;
	}

	if(m_strCode != p->m_strCode)
	{
		return FALSE;
	}

	if(m_nStatus != p->m_nStatus)
	{
		return FALSE;
	}

	if(m_nIndex_Test_Task != p->m_nIndex_Test_Task)
	{
		return FALSE;
	}
	
	if(m_nIndex_Items != p->m_nIndex_Items)
	{
		return FALSE;
	}
	
	if(m_strName_Template_File != p->m_strName_Template_File)
	{
		return FALSE;
	}
	
	if(m_strId_User != p->m_strId_User)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Bench::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Bench *p = (CIot_Bench*)pDest;

	p->m_nIndex_Bench = m_nIndex_Bench;
	p->m_nIndex_Dept = m_nIndex_Dept;
	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	p->m_strCode = m_strCode;
	p->m_nStatus = m_nStatus;
	p->m_tmCreate_Time = m_tmCreate_Time;
	p->m_nIndex_Test_Task = m_nIndex_Test_Task;
	p->m_nIndex_Items = m_nIndex_Items;
	p->m_strName_Template_File = m_strName_Template_File;
	p->m_strId_User = m_strId_User;
	return TRUE;
}

CBaseObject* CIot_Bench::Clone()
{
	CIot_Bench *p = new CIot_Bench();
	Copy(p);
	return p;
}

CBaseObject* CIot_Bench::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Bench *p = new CIot_Bench();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Bench::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CIot_Bench::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CIot_Bench::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CIot_Bench::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_nStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_Template_FileKey, m_strName_Template_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_UserKey, m_strId_User);

	return 0;
}

long CIot_Bench::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_nStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_Template_FileKey, m_strName_Template_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_UserKey, m_strId_User);
	return 0;
}

BOOL CIot_Bench::QueryBenchBySN(CXDbBaseLib *pXDbLib,const CString &strBenchSN)
{
	CString strBenchTable,strSql;
	strBenchTable = CIot_AtsMngrXmlRWKeys::CIot_BenchKey();

	strSql.Format(_T("select * from %s where code=\"%s\" limit 1"),strBenchTable,strBenchSN);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

BOOL CIot_Bench::UpdateBenchState(CXDbBaseLib *pXDbLib,const CString &strBenchSN,long nState)
{
	BOOL bRet = QueryBenchBySN(pXDbLib, strBenchSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oBench.QueryBenchBySN failed![%s]"),strBenchSN);
		return FALSE;
	}
	m_nStatus = nState;

	//更新测试台状态
	return DB_Update(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
CIot_Benchs::CIot_Benchs()
{
	//初始化属性

	//初始化成员变量
}

CIot_Benchs::~CIot_Benchs()
{
}

long CIot_Benchs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Benchs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Benchs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_Benchs::InitAfterRead()
{
}

BOOL CIot_Benchs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Benchs *p = (CIot_Benchs*)pObj;

	return TRUE;
}

BOOL CIot_Benchs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Benchs *p = (CIot_Benchs*)pDest;

	return TRUE;
}

CBaseObject* CIot_Benchs::Clone()
{
	CIot_Benchs *p = new CIot_Benchs();
	Copy(p);
	return p;
}

CBaseObject* CIot_Benchs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Benchs *p = new CIot_Benchs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Benchs::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_BENCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Benchs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_BenchKey)
	{
		pNew = new CIot_Bench();
	}

	return pNew;
}

CExBaseObject* CIot_Benchs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_BENCH)
	{
		pNew = new CIot_Bench();
	}

	return pNew;
}

CExBaseObject* CIot_Benchs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

	pNew = new CIot_Bench();

	return pNew;
}

BOOL CIot_Benchs::QueryAllBenchs(CXDbBaseLib *pXDbLib)
{
	CString strBenchTable, strSql;
	strBenchTable = CIot_AtsMngrXmlRWKeys::CIot_BenchKey();
	strSql.Format(_T("select * from %s"),strBenchTable);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}