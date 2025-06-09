//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_ItemGen.cpp  CIot_ItemGen


#include "stdafx.h"
#include "Iot_ItemGen.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_ItemGen::CIot_ItemGen()
{
	//初始化属性
	m_nIndex_Gen = 0;
	m_nIndex_Items = 0;
	m_fPara1_Value = 0;
	m_fPara2_Value = 0;
	m_fPara3_Value = 0;
	m_fPara4_Value = 0;

	//初始化成员变量
}

CIot_ItemGen::~CIot_ItemGen()
{
}

long CIot_ItemGen::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_GenKey, oNode, m_nIndex_Gen);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ItemsKey, oNode, m_nIndex_Items);
	xml_GetAttibuteValue(pXmlKeys->m_strId_ItemsKey, oNode, m_strId_Items);
	xml_GetAttibuteValue(pXmlKeys->m_strPara1_NameKey, oNode, m_strPara1_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strPara1_IdKey, oNode, m_strPara1_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strPara1_ValueKey, oNode, m_fPara1_Value);
	xml_GetAttibuteValue(pXmlKeys->m_strPara2_NameKey, oNode, m_strPara2_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strPara2_IdKey, oNode, m_strPara2_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strPara2_ValueKey, oNode, m_fPara2_Value);
	xml_GetAttibuteValue(pXmlKeys->m_strPara3_NameKey, oNode, m_strPara3_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strPara3_IdKey, oNode, m_strPara3_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strPara3_ValueKey, oNode, m_fPara3_Value);
	xml_GetAttibuteValue(pXmlKeys->m_strPara4_NameKey, oNode, m_strPara4_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strPara4_IdKey, oNode, m_strPara4_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strPara4_ValueKey, oNode, m_fPara4_Value);
	return 0;
}

long CIot_ItemGen::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_GenKey, oElement, m_nIndex_Gen);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ItemsKey, oElement, m_nIndex_Items);
	xml_SetAttributeValue(pXmlKeys->m_strId_ItemsKey, oElement, m_strId_Items);
	xml_SetAttributeValue(pXmlKeys->m_strPara1_NameKey, oElement, m_strPara1_Name);
	xml_SetAttributeValue(pXmlKeys->m_strPara1_IdKey, oElement, m_strPara1_Id);
	xml_SetAttributeValue(pXmlKeys->m_strPara1_ValueKey, oElement, m_fPara1_Value);
	xml_SetAttributeValue(pXmlKeys->m_strPara2_NameKey, oElement, m_strPara2_Name);
	xml_SetAttributeValue(pXmlKeys->m_strPara2_IdKey, oElement, m_strPara2_Id);
	xml_SetAttributeValue(pXmlKeys->m_strPara2_ValueKey, oElement, m_fPara2_Value);
	xml_SetAttributeValue(pXmlKeys->m_strPara3_NameKey, oElement, m_strPara3_Name);
	xml_SetAttributeValue(pXmlKeys->m_strPara3_IdKey, oElement, m_strPara3_Id);
	xml_SetAttributeValue(pXmlKeys->m_strPara3_ValueKey, oElement, m_fPara3_Value);
	xml_SetAttributeValue(pXmlKeys->m_strPara4_NameKey, oElement, m_strPara4_Name);
	xml_SetAttributeValue(pXmlKeys->m_strPara4_IdKey, oElement, m_strPara4_Id);
	xml_SetAttributeValue(pXmlKeys->m_strPara4_ValueKey, oElement, m_fPara4_Value);
	return 0;
}

long CIot_ItemGen::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Gen);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeCalLen(oBinaryBuffer, m_strId_Items);
		BinarySerializeCalLen(oBinaryBuffer, m_strPara1_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strPara1_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_fPara1_Value);
		BinarySerializeCalLen(oBinaryBuffer, m_strPara2_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strPara2_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_fPara2_Value);
		BinarySerializeCalLen(oBinaryBuffer, m_strPara3_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strPara3_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_fPara3_Value);
		BinarySerializeCalLen(oBinaryBuffer, m_strPara4_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strPara4_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_fPara4_Value);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Gen);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeRead(oBinaryBuffer, m_strId_Items);
		BinarySerializeRead(oBinaryBuffer, m_strPara1_Name);
		BinarySerializeRead(oBinaryBuffer, m_strPara1_Id);
		BinarySerializeRead(oBinaryBuffer, m_fPara1_Value);
		BinarySerializeRead(oBinaryBuffer, m_strPara2_Name);
		BinarySerializeRead(oBinaryBuffer, m_strPara2_Id);
		BinarySerializeRead(oBinaryBuffer, m_fPara2_Value);
		BinarySerializeRead(oBinaryBuffer, m_strPara3_Name);
		BinarySerializeRead(oBinaryBuffer, m_strPara3_Id);
		BinarySerializeRead(oBinaryBuffer, m_fPara3_Value);
		BinarySerializeRead(oBinaryBuffer, m_strPara4_Name);
		BinarySerializeRead(oBinaryBuffer, m_strPara4_Id);
		BinarySerializeRead(oBinaryBuffer, m_fPara4_Value);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Gen);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeWrite(oBinaryBuffer, m_strId_Items);
		BinarySerializeWrite(oBinaryBuffer, m_strPara1_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strPara1_Id);
		BinarySerializeWrite(oBinaryBuffer, m_fPara1_Value);
		BinarySerializeWrite(oBinaryBuffer, m_strPara2_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strPara2_Id);
		BinarySerializeWrite(oBinaryBuffer, m_fPara2_Value);
		BinarySerializeWrite(oBinaryBuffer, m_strPara3_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strPara3_Id);
		BinarySerializeWrite(oBinaryBuffer, m_fPara3_Value);
		BinarySerializeWrite(oBinaryBuffer, m_strPara4_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strPara4_Id);
		BinarySerializeWrite(oBinaryBuffer, m_fPara4_Value);
	}
	return 0;
}

void CIot_ItemGen::InitAfterRead()
{
}

BOOL CIot_ItemGen::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_ItemGen *p = (CIot_ItemGen*)pObj;

	if(m_nIndex_Gen != p->m_nIndex_Gen)
	{
		return FALSE;
	}

	if(m_nIndex_Items != p->m_nIndex_Items)
	{
		return FALSE;
	}

	if(m_strId_Items != p->m_strId_Items)
	{
		return FALSE;
	}

	if(m_strPara1_Name != p->m_strPara1_Name)
	{
		return FALSE;
	}

	if(m_strPara1_Id != p->m_strPara1_Id)
	{
		return FALSE;
	}

	if(m_fPara1_Value != p->m_fPara1_Value)
	{
		return FALSE;
	}

	if(m_strPara2_Name != p->m_strPara2_Name)
	{
		return FALSE;
	}

	if(m_strPara2_Id != p->m_strPara2_Id)
	{
		return FALSE;
	}

	if(m_fPara2_Value != p->m_fPara2_Value)
	{
		return FALSE;
	}

	if(m_strPara3_Name != p->m_strPara3_Name)
	{
		return FALSE;
	}

	if(m_strPara3_Id != p->m_strPara3_Id)
	{
		return FALSE;
	}

	if(m_fPara3_Value != p->m_fPara3_Value)
	{
		return FALSE;
	}

	if(m_strPara4_Name != p->m_strPara4_Name)
	{
		return FALSE;
	}

	if(m_strPara4_Id != p->m_strPara4_Id)
	{
		return FALSE;
	}

	if(m_fPara4_Value != p->m_fPara4_Value)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_ItemGen::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_ItemGen *p = (CIot_ItemGen*)pDest;

	p->m_nIndex_Gen = m_nIndex_Gen;
	p->m_nIndex_Items = m_nIndex_Items;
	p->m_strId_Items = m_strId_Items;
	p->m_strPara1_Name = m_strPara1_Name;
	p->m_strPara1_Id = m_strPara1_Id;
	p->m_fPara1_Value = m_fPara1_Value;
	p->m_strPara2_Name = m_strPara2_Name;
	p->m_strPara2_Id = m_strPara2_Id;
	p->m_fPara2_Value = m_fPara2_Value;
	p->m_strPara3_Name = m_strPara3_Name;
	p->m_strPara3_Id = m_strPara3_Id;
	p->m_fPara3_Value = m_fPara3_Value;
	p->m_strPara4_Name = m_strPara4_Name;
	p->m_strPara4_Id = m_strPara4_Id;
	p->m_fPara4_Value = m_fPara4_Value;
	return TRUE;
}

CBaseObject* CIot_ItemGen::Clone()
{
	CIot_ItemGen *p = new CIot_ItemGen();
	Copy(p);
	return p;
}

CBaseObject* CIot_ItemGen::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_ItemGen *p = new CIot_ItemGen();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_ItemGen::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_GenKey, m_nIndex_Gen);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_ItemsKey, m_strId_Items);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara1_NameKey, m_strPara1_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara1_IdKey, m_strPara1_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara1_ValueKey, m_fPara1_Value);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara2_NameKey, m_strPara2_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara2_IdKey, m_strPara2_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara2_ValueKey, m_fPara2_Value);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara3_NameKey, m_strPara3_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara3_IdKey, m_strPara3_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara3_ValueKey, m_fPara3_Value);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara4_NameKey, m_strPara4_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara4_IdKey, m_strPara4_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strPara4_ValueKey, m_fPara4_Value);
	return 0;
}

long CIot_ItemGen::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_GenKey, m_nIndex_Gen);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_ItemsKey, m_strId_Items);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara1_NameKey, m_strPara1_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara1_IdKey, m_strPara1_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara1_ValueKey, m_fPara1_Value);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara2_NameKey, m_strPara2_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara2_IdKey, m_strPara2_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara2_ValueKey, m_fPara2_Value);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara3_NameKey, m_strPara3_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara3_IdKey, m_strPara3_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara3_ValueKey, m_fPara3_Value);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara4_NameKey, m_strPara4_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara4_IdKey, m_strPara4_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strPara4_ValueKey, m_fPara4_Value);
	return 0;
}

BOOL CIot_ItemGen::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TEMPLATEITEMS)
	{
		m_nIndex_Items = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

