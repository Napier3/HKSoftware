//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_TransStation.cpp  CAts_Wzd_TransStation


#include "stdafx.h"
#include "Ats_Wzd_TransStation.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_TransStation::CAts_Wzd_TransStation()
{
	//初始化属性
	m_nIndex_Station = 0;
	m_nIndex_Company = 0;

	//初始化成员变量
}

CAts_Wzd_TransStation::~CAts_Wzd_TransStation()
{
}

long CAts_Wzd_TransStation::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_StationKey, oNode, m_nIndex_Station);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_CompanyKey, oNode, m_nIndex_Company);
	return 0;
}

long CAts_Wzd_TransStation::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_StationKey, oElement, m_nIndex_Station);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_CompanyKey, oElement, m_nIndex_Company);
	return 0;
}

long CAts_Wzd_TransStation::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Station);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Company);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Station);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Company);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Station);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Company);
	}
	return 0;
}

void CAts_Wzd_TransStation::InitAfterRead()
{
	m_strName = m_strID;
}

BOOL CAts_Wzd_TransStation::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_TransStation *p = (CAts_Wzd_TransStation*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_nIndex_Station != p->m_nIndex_Station)
	{
		return FALSE;
	}

	if(m_nIndex_Company != p->m_nIndex_Company)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_TransStation::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_TransStation *p = (CAts_Wzd_TransStation*)pDest;

	p->m_strID = m_strID;
	p->m_nIndex_Station = m_nIndex_Station;
	p->m_nIndex_Company = m_nIndex_Company;
	return TRUE;
}

CBaseObject* CAts_Wzd_TransStation::Clone()
{
	CAts_Wzd_TransStation *p = new CAts_Wzd_TransStation();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_TransStation::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_TransStation *p = new CAts_Wzd_TransStation();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_TransStation::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strStationIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_StationKey, m_nIndex_Station);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_CompanyKey, m_nIndex_Company);
	return 0;
}

long CAts_Wzd_TransStation::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strStationIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_StationKey, m_nIndex_Station);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_CompanyKey, m_nIndex_Company);
	return 0;
}

BOOL CAts_Wzd_TransStation::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_OPERMAINTAINCOP)
	{
		m_nIndex_Company = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

