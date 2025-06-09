//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_InterVal.cpp  CAts_Wzd_InterVal


#include "stdafx.h"
#include "Ats_Wzd_InterVal.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_InterVal::CAts_Wzd_InterVal()
{
	//初始化属性
	m_nIndex_InterVal = 0;
	m_nIndex_Station = 0;

	//初始化成员变量
}

CAts_Wzd_InterVal::~CAts_Wzd_InterVal()
{
}

long CAts_Wzd_InterVal::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_InterValKey, oNode, m_nIndex_InterVal);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_StationKey, oNode, m_nIndex_Station);
	return 0;
}

long CAts_Wzd_InterVal::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_InterValKey, oElement, m_nIndex_InterVal);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_StationKey, oElement, m_nIndex_Station);
	return 0;
}

long CAts_Wzd_InterVal::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_InterVal);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Station);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_InterVal);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Station);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_InterVal);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Station);
	}
	return 0;
}

void CAts_Wzd_InterVal::InitAfterRead()
{
	m_strName = m_strID;
}

BOOL CAts_Wzd_InterVal::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_InterVal *p = (CAts_Wzd_InterVal*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_nIndex_InterVal != p->m_nIndex_InterVal)
	{
		return FALSE;
	}

	if(m_nIndex_Station != p->m_nIndex_Station)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_InterVal::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_InterVal *p = (CAts_Wzd_InterVal*)pDest;

	p->m_strID = m_strID;
	p->m_nIndex_InterVal = m_nIndex_InterVal;
	p->m_nIndex_Station = m_nIndex_Station;
	return TRUE;
}

CBaseObject* CAts_Wzd_InterVal::Clone()
{
	CAts_Wzd_InterVal *p = new CAts_Wzd_InterVal();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_InterVal::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_InterVal *p = new CAts_Wzd_InterVal();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_InterVal::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strInterValIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_InterValKey, m_nIndex_InterVal);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_StationKey, m_nIndex_Station);
	return 0;
}

long CAts_Wzd_InterVal::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strInterValIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_InterValKey, m_nIndex_InterVal);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_StationKey, m_nIndex_Station);
	return 0;
}

BOOL CAts_Wzd_InterVal::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TRANSSTATION)
	{
		m_nIndex_Station = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

