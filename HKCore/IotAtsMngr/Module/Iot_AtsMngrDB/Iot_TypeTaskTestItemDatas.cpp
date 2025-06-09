//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskTestItemDatas.cpp  CIot_TypeTaskTestItemDatas


#include "stdafx.h"
#include "Iot_TypeTaskTestItemDatas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTaskTestItemDatas::CIot_TypeTaskTestItemDatas()
{
	//初始化属性
	m_nIndex_Item_Data = 0;
	m_nIndex_Test = 0;
	m_nIndex_Dev = 0;
	m_nIndex_Items = 0;
	m_nIndex_Item = 0;
	m_nIndex_Task = 0;

	//初始化成员变量
}

CIot_TypeTaskTestItemDatas::~CIot_TypeTaskTestItemDatas()
{
}

long CIot_TypeTaskTestItemDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Item_DataKey, oNode, m_nIndex_Item_Data);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestKey, oNode, m_nIndex_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DevKey, oNode, m_nIndex_Dev);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ItemsKey, oNode, m_nIndex_Items);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ItemKey, oNode, m_nIndex_Item);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strData_TypeKey, oNode, m_strData_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	return 0;
}

long CIot_TypeTaskTestItemDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Item_DataKey, oElement, m_nIndex_Item_Data);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestKey, oElement, m_nIndex_Test);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DevKey, oElement, m_nIndex_Dev);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ItemsKey, oElement, m_nIndex_Items);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ItemKey, oElement, m_nIndex_Item);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strData_TypeKey, oElement, m_strData_Type);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	return 0;
}

long CIot_TypeTaskTestItemDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Item_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dev);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Item);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strData_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Item_Data);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dev);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Item);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strData_Type);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Item_Data);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dev);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Item);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strData_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
	}
	return 0;
}

void CIot_TypeTaskTestItemDatas::InitAfterRead()
{
}

BOOL CIot_TypeTaskTestItemDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_TypeTaskTestItemDatas *p = (CIot_TypeTaskTestItemDatas*)pObj;

	if(m_nIndex_Item_Data != p->m_nIndex_Item_Data)
	{
		return FALSE;
	}

	if(m_nIndex_Test != p->m_nIndex_Test)
	{
		return FALSE;
	}

	if(m_nIndex_Dev != p->m_nIndex_Dev)
	{
		return FALSE;
	}

	if(m_nIndex_Items != p->m_nIndex_Items)
	{
		return FALSE;
	}

	if(m_nIndex_Item != p->m_nIndex_Item)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strData_Type != p->m_strData_Type)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TypeTaskTestItemDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_TypeTaskTestItemDatas *p = (CIot_TypeTaskTestItemDatas*)pDest;

	p->m_nIndex_Item_Data = m_nIndex_Item_Data;
	p->m_nIndex_Test = m_nIndex_Test;
	p->m_nIndex_Dev = m_nIndex_Dev;
	p->m_nIndex_Items = m_nIndex_Items;
	p->m_nIndex_Item = m_nIndex_Item;
	p->m_strValue = m_strValue;
	p->m_strData_Type = m_strData_Type;
	p->m_strUnit = m_strUnit;
	p->m_nIndex_Task = m_nIndex_Task;
	return TRUE;
}

CBaseObject* CIot_TypeTaskTestItemDatas::Clone()
{
	CIot_TypeTaskTestItemDatas *p = new CIot_TypeTaskTestItemDatas();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskTestItemDatas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskTestItemDatas *p = new CIot_TypeTaskTestItemDatas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTaskTestItemDatas::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_ReadFields(pRecordset, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Item_DataKey, m_nIndex_Item_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DevKey, m_nIndex_Dev);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ItemKey, m_nIndex_Item);
	pRecordset->GetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->GetFieldValue(pXmlKeys->m_strData_TypeKey, m_strData_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strUnitKey, m_strUnit);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	return 0;
}

long CIot_TypeTaskTestItemDatas::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_WriteFields(pRecordset, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Item_DataKey, m_nIndex_Item_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DevKey, m_nIndex_Dev);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ItemKey, m_nIndex_Item);
	pRecordset->SetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->SetFieldValue(pXmlKeys->m_strData_TypeKey, m_strData_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strUnitKey, m_strUnit);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	return 0;
}

BOOL CIot_TypeTaskTestItemDatas::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASKTEST)
	{
		m_nIndex_Test = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASKDEV)
	{
		m_nIndex_Dev = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TEMPLATEITEMS)
	{
		m_nIndex_Items = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TEMPLATEITEM)
	{
		m_nIndex_Item = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

