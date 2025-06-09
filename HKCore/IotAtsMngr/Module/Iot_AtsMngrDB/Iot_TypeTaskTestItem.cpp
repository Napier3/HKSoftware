//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskTestItem.cpp  CIot_TypeTaskTestItem


#include "stdafx.h"
#include "Iot_TypeTaskTestItem.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTaskTestItem::CIot_TypeTaskTestItem()
{
	//初始化属性
	m_nIndex_Item = 0;
	m_nIndex_Task = 0;
	m_nIndex_Test = 0;

	//初始化成员变量
	m_nState = TYPE_TASK_STATE_NORMAL;
}

CIot_TypeTaskTestItem::~CIot_TypeTaskTestItem()
{
}

long CIot_TypeTaskTestItem::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ItemKey, oNode, m_nIndex_Item);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_ItemsKey, oNode, m_strSn_Items);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_nState);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_TestKey, oNode, m_strTm_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strTempretureKey, oNode, m_strTempreture);
	xml_GetAttibuteValue(pXmlKeys->m_strHumidityKey, oNode, m_strHumidity);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_FileKey, oNode, m_strRpt_File);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_File_SKey, oNode, m_strRpt_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strType_ItemKey, oNode, m_strType_Item);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestKey, oNode, m_nIndex_Test);
	return 0;
}

long CIot_TypeTaskTestItem::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_ItemKey, oElement, m_nIndex_Item);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strSn_ItemsKey, oElement, m_strSn_Items);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_nState);
	xml_SetAttributeValue(pXmlKeys->m_strTm_TestKey, oElement, m_strTm_Test);
	xml_SetAttributeValue(pXmlKeys->m_strTempretureKey, oElement, m_strTempreture);
	xml_SetAttributeValue(pXmlKeys->m_strHumidityKey, oElement, m_strHumidity);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_FileKey, oElement, m_strRpt_File);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_File_SKey, oElement, m_strRpt_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strType_ItemKey, oElement, m_strType_Item);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestKey, oElement, m_nIndex_Test);
	return 0;
}

long CIot_TypeTaskTestItem::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Item);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn_Items);
		BinarySerializeCalLen(oBinaryBuffer, m_nState);
		BinarySerializeCalLen(oBinaryBuffer, m_strTm_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_strTempreture);
		BinarySerializeCalLen(oBinaryBuffer, m_strHumidity);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strType_Item);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Item);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strSn_Items);
		BinarySerializeRead(oBinaryBuffer, m_nState);
		BinarySerializeRead(oBinaryBuffer, m_strTm_Test);
		BinarySerializeRead(oBinaryBuffer, m_strTempreture);
		BinarySerializeRead(oBinaryBuffer, m_strHumidity);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_File);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strType_Item);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Item);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strSn_Items);
		BinarySerializeWrite(oBinaryBuffer, m_nState);
		BinarySerializeWrite(oBinaryBuffer, m_strTm_Test);
		BinarySerializeWrite(oBinaryBuffer, m_strTempreture);
		BinarySerializeWrite(oBinaryBuffer, m_strHumidity);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_File);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strType_Item);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test);
	}
	return 0;
}

void CIot_TypeTaskTestItem::InitAfterRead()
{
}

BOOL CIot_TypeTaskTestItem::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_TypeTaskTestItem *p = (CIot_TypeTaskTestItem*)pObj;

	if(m_nIndex_Item != p->m_nIndex_Item)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_strSn_Items != p->m_strSn_Items)
	{
		return FALSE;
	}

	if(m_nState != p->m_nState)
	{
		return FALSE;
	}

	if(m_strTm_Test != p->m_strTm_Test)
	{
		return FALSE;
	}

	if(m_strTempreture != p->m_strTempreture)
	{
		return FALSE;
	}

	if(m_strHumidity != p->m_strHumidity)
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

	if(m_strType_Item != p->m_strType_Item)
	{
		return FALSE;
	}

	if(m_nIndex_Test != p->m_nIndex_Test)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TypeTaskTestItem::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_TypeTaskTestItem *p = (CIot_TypeTaskTestItem*)pDest;

	p->m_nIndex_Item = m_nIndex_Item;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strSn_Items = m_strSn_Items;
	p->m_nState = m_nState;
	p->m_strTm_Test = m_strTm_Test;
	p->m_strTempreture = m_strTempreture;
	p->m_strHumidity = m_strHumidity;
	p->m_strRpt_File = m_strRpt_File;
	p->m_strRpt_File_S = m_strRpt_File_S;
	p->m_strType_Item = m_strType_Item;
	p->m_nIndex_Test = m_nIndex_Test;
	return TRUE;
}

CBaseObject* CIot_TypeTaskTestItem::Clone()
{
	CIot_TypeTaskTestItem *p = new CIot_TypeTaskTestItem();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskTestItem::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskTestItem *p = new CIot_TypeTaskTestItem();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTaskTestItem::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_ReadFields(pRecordset, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ItemKey, m_nIndex_Item);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_ItemsKey, m_strSn_Items);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_TestKey, m_strTm_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strTempretureKey, m_strTempreture);
	pRecordset->GetFieldValue(pXmlKeys->m_strHumidityKey, m_strHumidity);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_FileKey, m_strRpt_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_File_SKey, m_strRpt_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strType_ItemKey, m_strType_Item);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	return 0;
}

long CIot_TypeTaskTestItem::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_WriteFields(pRecordset, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ItemKey, m_nIndex_Item);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_ItemsKey, m_strSn_Items);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_TestKey, m_strTm_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strTempretureKey, m_strTempreture);
	pRecordset->SetFieldValue(pXmlKeys->m_strHumidityKey, m_strHumidity);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_FileKey, m_strRpt_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_File_SKey, m_strRpt_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strType_ItemKey, m_strType_Item);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	return 0;
}

BOOL CIot_TypeTaskTestItem::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASKTEST)
	{
		m_nIndex_Test = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

