//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskDev.cpp  CIot_TypeTaskDev


#include "stdafx.h"
#include "Iot_TypeTaskDev.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTaskDev::CIot_TypeTaskDev()
{
	//初始化属性
	m_nIndex_Dev = 0;
	m_nIndex_Task = 0;

	m_nTest_State = DEV_TEST_STATE_NOMAL;
	m_nConnect_State = DEV_CONNECT_STATE_OFF;
	//初始化成员变量
}

CIot_TypeTaskDev::~CIot_TypeTaskDev()
{
}

long CIot_TypeTaskDev::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DevKey, oNode, m_nIndex_Dev);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_Sample_DevKey, oNode, m_strSn_Sample_Dev);
	xml_GetAttibuteValue(pXmlKeys->m_strNumber_Sample_DevKey, oNode, m_strNumber_Sample_Dev);
	xml_GetAttibuteValue(pXmlKeys->m_strTest_StateKey, oNode, m_nTest_State);
	xml_GetAttibuteValue(pXmlKeys->m_strConnect_StateKey, oNode, m_nConnect_State);	
	return 0;
}

long CIot_TypeTaskDev::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_DevKey, oElement, m_nIndex_Dev);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strSn_Sample_DevKey, oElement, m_strSn_Sample_Dev);
	xml_SetAttributeValue(pXmlKeys->m_strNumber_Sample_DevKey, oElement, m_strNumber_Sample_Dev);
	xml_SetAttributeValue(pXmlKeys->m_strTest_StateKey, oElement, m_nTest_State);
	xml_SetAttributeValue(pXmlKeys->m_strConnect_StateKey, oElement, m_nConnect_State);
	return 0;
}

long CIot_TypeTaskDev::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dev);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeCalLen(oBinaryBuffer, m_strNumber_Sample_Dev);
		BinarySerializeCalLen(oBinaryBuffer, m_nTest_State);
		BinarySerializeCalLen(oBinaryBuffer, m_nConnect_State);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dev);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeRead(oBinaryBuffer, m_strNumber_Sample_Dev);
		BinarySerializeRead(oBinaryBuffer, m_nTest_State);
		BinarySerializeRead(oBinaryBuffer, m_nConnect_State);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dev);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeWrite(oBinaryBuffer, m_strNumber_Sample_Dev);
		BinarySerializeWrite(oBinaryBuffer, m_nTest_State);
		BinarySerializeWrite(oBinaryBuffer, m_nConnect_State);
	}
	return 0;
}

void CIot_TypeTaskDev::InitAfterRead()
{
}

BOOL CIot_TypeTaskDev::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTaskDev *p = (CIot_TypeTaskDev*)pObj;

	if(m_nIndex_Dev != p->m_nIndex_Dev)
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

	if(m_strNumber_Sample_Dev != p->m_strNumber_Sample_Dev)
	{
		return FALSE;
	}

	if(m_nConnect_State != p->m_nConnect_State)
	{
		return FALSE;
	}

	if(m_nTest_State != p->m_nTest_State)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TypeTaskDev::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTaskDev *p = (CIot_TypeTaskDev*)pDest;

	p->m_nIndex_Dev = m_nIndex_Dev;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strSn_Sample_Dev = m_strSn_Sample_Dev;
	p->m_strNumber_Sample_Dev = m_strNumber_Sample_Dev;
	p->m_nTest_State = m_nTest_State;
	p->m_nConnect_State = m_nConnect_State;
	return TRUE;
}

CBaseObject* CIot_TypeTaskDev::Clone()
{
	CIot_TypeTaskDev *p = new CIot_TypeTaskDev();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskDev::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskDev *p = new CIot_TypeTaskDev();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTaskDev::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DevKey, m_nIndex_Dev);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
	pRecordset->GetFieldValue(pXmlKeys->m_strNumber_Sample_DevKey, m_strNumber_Sample_Dev);
	pRecordset->GetFieldValue(pXmlKeys->m_strTest_StateKey, m_nTest_State);
	pRecordset->GetFieldValue(pXmlKeys->m_strConnect_StateKey, m_nConnect_State);
	return 0;
}

long CIot_TypeTaskDev::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DevKey, m_nIndex_Dev);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
	pRecordset->SetFieldValue(pXmlKeys->m_strNumber_Sample_DevKey, m_strNumber_Sample_Dev);
	pRecordset->SetFieldValue(pXmlKeys->m_strTest_StateKey, m_nTest_State);
	pRecordset->SetFieldValue(pXmlKeys->m_strConnect_StateKey, m_nConnect_State);
	return 0;
}

BOOL CIot_TypeTaskDev::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

BOOL CIot_TypeTaskDev::QueryByDeviceSN(CXDbBaseLib *pXDbLib,const CString &strDeviceSN)
{
	if (strDeviceSN.IsEmpty())
	{
		return FALSE;
	}

	CString strTable,strSNKey,strSql;
	strTable = CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevKey();
	strSNKey = CIot_AtsMngrXmlRWKeys::Sn_Sample_DevKey();  //设备序列号

	strSql.Format(_T("select * from %s where %s=\"%s\" limit 1"),strTable,strSNKey,strDeviceSN);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}