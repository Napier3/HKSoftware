//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskTest.cpp  CIot_TypeTaskTest


#include "stdafx.h"
#include "Iot_TypeTaskTest.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTaskTest::CIot_TypeTaskTest()
{
	//初始化属性
	m_nIndex_Test = 0;
	m_nIndex_Task = 0;
	m_nFinal_Report = 0;
	m_nIndex_Bench = 0;
	::GetLocalTime(&m_tmTime_Test_Start);
	::GetLocalTime(&m_tmTime_Test_End);
	m_nState = TYPE_TASK_STATE_NORMAL;

	//初始化成员变量
}

CIot_TypeTaskTest::~CIot_TypeTaskTest()
{
}

long CIot_TypeTaskTest::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestKey, oNode, m_nIndex_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_Sample_DevKey, oNode, m_strSn_Sample_Dev);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_ItemsKey, oNode, m_strSn_Items);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_FileKey, oNode, m_strRpt_File);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_File_SKey, oNode, m_strRpt_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strFinal_ReportKey, oNode, m_nFinal_Report);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	xml_GetAttibuteValue(pXmlKeys->m_strId_UserKey, oNode, m_strId_User);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_nState);
	xml_GetAttibuteValue(pXmlKeys->m_strTime_Test_StartKey, oNode, m_tmTime_Test_Start);
	xml_GetAttibuteValue(pXmlKeys->m_strTime_Test_EndKey, oNode, m_tmTime_Test_End);
	return 0;
}

long CIot_TypeTaskTest::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestKey, oElement, m_nIndex_Test);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strSn_Sample_DevKey, oElement, m_strSn_Sample_Dev);
	xml_SetAttributeValue(pXmlKeys->m_strSn_ItemsKey, oElement, m_strSn_Items);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_FileKey, oElement, m_strRpt_File);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_File_SKey, oElement, m_strRpt_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strFinal_ReportKey, oElement, m_nFinal_Report);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	xml_SetAttributeValue(pXmlKeys->m_strId_UserKey, oElement, m_strId_User);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_nState);
	xml_SetAttributeValue(pXmlKeys->m_strTime_Test_StartKey, oElement, m_tmTime_Test_Start);
	xml_SetAttributeValue(pXmlKeys->m_strTime_Test_EndKey, oElement, m_tmTime_Test_End);
	return 0;
}

long CIot_TypeTaskTest::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn_Items);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_nFinal_Report);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeCalLen(oBinaryBuffer, m_strId_User);
		BinarySerializeCalLen(oBinaryBuffer, m_nState);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTime_Test_Start);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTime_Test_End);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeRead(oBinaryBuffer, m_strSn_Items);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_File);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_File_S);
		BinarySerializeRead(oBinaryBuffer, m_nFinal_Report);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeRead(oBinaryBuffer, m_strId_User);
		BinarySerializeRead(oBinaryBuffer, m_nState);
		BinarySerializeRead(oBinaryBuffer, m_tmTime_Test_Start);
		BinarySerializeRead(oBinaryBuffer, m_tmTime_Test_End);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeWrite(oBinaryBuffer, m_strSn_Items);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_File);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_nFinal_Report);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeWrite(oBinaryBuffer, m_strId_User);
		BinarySerializeWrite(oBinaryBuffer, m_nState);
		BinarySerializeWrite(oBinaryBuffer, m_tmTime_Test_Start);
		BinarySerializeWrite(oBinaryBuffer, m_tmTime_Test_End);
	}
	return 0;
}

void CIot_TypeTaskTest::InitAfterRead()
{
}

BOOL CIot_TypeTaskTest::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTaskTest *p = (CIot_TypeTaskTest*)pObj;

	if(m_nIndex_Test != p->m_nIndex_Test)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_strSn_Sample_Dev != p->m_strSn_Sample_Dev)
	{
		return FALSE;
	}

	if(m_strSn_Items != p->m_strSn_Items)
	{
		return FALSE;
	}

	if(m_strRpt_File != p->m_strRpt_File)
	{
		return FALSE;
	}

	if(m_strRpt_File_S != p->m_strRpt_File_S)
	{
		return FALSE;
	}

	if(m_nFinal_Report != p->m_nFinal_Report)
	{
		return FALSE;
	}

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	if(m_strId_User != p->m_strId_User)
	{
		return FALSE;
	}

	if(m_nState != p->m_nState)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TypeTaskTest::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTaskTest *p = (CIot_TypeTaskTest*)pDest;

	p->m_nIndex_Test = m_nIndex_Test;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strSn_Sample_Dev = m_strSn_Sample_Dev;
	p->m_strSn_Items = m_strSn_Items;
	p->m_strRpt_File = m_strRpt_File;
	p->m_strRpt_File_S = m_strRpt_File_S;
	p->m_nFinal_Report = m_nFinal_Report;
	p->m_nIndex_Bench = m_nIndex_Bench;
	p->m_strId_User = m_strId_User;
	p->m_nState = m_nState;
	p->m_tmTime_Test_Start = m_tmTime_Test_Start;
	p->m_tmTime_Test_End = m_tmTime_Test_End;
	return TRUE;
}

CBaseObject* CIot_TypeTaskTest::Clone()
{
	CIot_TypeTaskTest *p = new CIot_TypeTaskTest();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskTest::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskTest *p = new CIot_TypeTaskTest();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTaskTest::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_ItemsKey, m_strSn_Items);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_FileKey, m_strRpt_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_File_SKey, m_strRpt_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strFinal_ReportKey, m_nFinal_Report);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_UserKey, m_strId_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->GetFieldValue(pXmlKeys->m_strTime_Test_StartKey, m_tmTime_Test_Start);
	pRecordset->GetFieldValue(pXmlKeys->m_strTime_Test_EndKey, m_tmTime_Test_End);
	return 0;
}

long CIot_TypeTaskTest::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_ItemsKey, m_strSn_Items);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_FileKey, m_strRpt_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_File_SKey, m_strRpt_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strFinal_ReportKey, m_nFinal_Report);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_UserKey, m_strId_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->SetFieldValue(pXmlKeys->m_strTime_Test_StartKey, m_tmTime_Test_Start);
	pRecordset->SetFieldValue(pXmlKeys->m_strTime_Test_EndKey, m_tmTime_Test_End);
	return 0;
}

BOOL CIot_TypeTaskTest::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
CIot_TypeTaskTests::CIot_TypeTaskTests()
{
	//初始化属性

	//初始化成员变量
}

CIot_TypeTaskTests::~CIot_TypeTaskTests()
{
}

long CIot_TypeTaskTests::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TypeTaskTests::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TypeTaskTests::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_TypeTaskTests::InitAfterRead()
{
}

BOOL CIot_TypeTaskTests::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTaskTests *p = (CIot_TypeTaskTests*)pObj;

	return TRUE;
}

BOOL CIot_TypeTaskTests::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTaskTests *p = (CIot_TypeTaskTests*)pDest;

	return TRUE;
}

CBaseObject* CIot_TypeTaskTests::Clone()
{
	CIot_TypeTaskTests *p = new CIot_TypeTaskTests();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskTests::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskTests *p = new CIot_TypeTaskTests();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TypeTaskTests::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_BENCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TypeTaskTests::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TypeTaskTestKey)
	{
		pNew = new CIot_TypeTaskTest();
	}

	return pNew;
}

CExBaseObject* CIot_TypeTaskTests::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TYPETASKTEST)
	{
		pNew = new CIot_TypeTaskTest();
	}

	return pNew;
}

CExBaseObject* CIot_TypeTaskTests::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

	pNew = new CIot_TypeTaskTest();

	return pNew;
}

BOOL CIot_TypeTaskTests::QueryAllTaskTests_FinalRpt(CXDbBaseLib *pXDbLib, long nIndex_Task)
{
	CString strTable, strKey, strFinalRpt, strSql;
	strTable = CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestKey();
	strKey = CIot_AtsMngrXmlRWKeys::Index_TaskKey();
	strFinalRpt = CIot_AtsMngrXmlRWKeys::Final_ReportKey();
	strSql.Format(_T("select * from %s where %s=\"%d\" and %s=1 "),strTable, strKey, nIndex_Task, strFinalRpt);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}