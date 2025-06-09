//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TestTaskTestapp.cpp  CIot_TestTaskTestapp


#include "stdafx.h"
#include "Iot_TestTaskTestapp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TestTaskTestapp::CIot_TestTaskTestapp()
{
	//初始化属性
	m_nIndex_Test_Testapp = 0;
	m_nIndex_Testapp = 0;
	m_nIndex_Test_Task = 0;
	m_nIndex_Bench = 0;

	//初始化成员变量
}

CIot_TestTaskTestapp::~CIot_TestTaskTestapp()
{
}

long CIot_TestTaskTestapp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_TestappKey, oNode, m_nIndex_Test_Testapp);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestappKey, oNode, m_nIndex_Testapp);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_TaskKey, oNode, m_nIndex_Test_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	return 0;
}

long CIot_TestTaskTestapp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_TestappKey, oElement, m_nIndex_Test_Testapp);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestappKey, oElement, m_nIndex_Testapp);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_TaskKey, oElement, m_nIndex_Test_Task);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	return 0;
}

long CIot_TestTaskTestapp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Testapp);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Testapp);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Testapp);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
	}
	return 0;
}

void CIot_TestTaskTestapp::InitAfterRead()
{
}

BOOL CIot_TestTaskTestapp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TestTaskTestapp *p = (CIot_TestTaskTestapp*)pObj;

	if(m_nIndex_Test_Testapp != p->m_nIndex_Test_Testapp)
	{
		return FALSE;
	}

	if(m_nIndex_Testapp != p->m_nIndex_Testapp)
	{
		return FALSE;
	}

	if(m_nIndex_Test_Task != p->m_nIndex_Test_Task)
	{
		return FALSE;
	}

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TestTaskTestapp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TestTaskTestapp *p = (CIot_TestTaskTestapp*)pDest;

	p->m_nIndex_Test_Testapp = m_nIndex_Test_Testapp;
	p->m_nIndex_Testapp = m_nIndex_Testapp;
	p->m_nIndex_Test_Task = m_nIndex_Test_Task;
	p->m_nIndex_Bench = m_nIndex_Bench;
	return TRUE;
}

CBaseObject* CIot_TestTaskTestapp::Clone()
{
	CIot_TestTaskTestapp *p = new CIot_TestTaskTestapp();
	Copy(p);
	return p;
}

CBaseObject* CIot_TestTaskTestapp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TestTaskTestapp *p = new CIot_TestTaskTestapp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TestTaskTestapp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_TestappKey, m_nIndex_Test_Testapp);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	return 0;
}

long CIot_TestTaskTestapp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_TestappKey, m_nIndex_Test_Testapp);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	return 0;
}

BOOL CIot_TestTaskTestapp::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TESTAPP)
	{
		m_nIndex_Testapp = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_BENCH)
	{
		m_nIndex_Bench = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

