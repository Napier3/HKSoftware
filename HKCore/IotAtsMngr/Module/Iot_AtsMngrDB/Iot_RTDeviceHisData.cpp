//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RTDeviceHisData.cpp  CIot_RTDeviceHisData


#include "stdafx.h"
#include "Iot_RTDeviceHisData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RTDeviceHisData::CIot_RTDeviceHisData()
{
	//初始化属性
	m_nIndex_His_Data = 0;
	::GetLocalTime(&m_tmTm_Update);
	m_fValue1 = 0.0;
	m_fValue2 = 0.0;
	m_fValue3 = 0.0;
	m_fValue4 = 0.0;
	m_fValue5 = 0.0;
	m_fValue6 = 0.0;
	m_fValue7 = 0.0;
	m_fValue8 = 0.0;
	m_fValue9 = 0.0;
	m_fValue10 = 0.0;
}

CIot_RTDeviceHisData::~CIot_RTDeviceHisData()
{
}

long CIot_RTDeviceHisData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strIndex_His_DataKey, oNode, m_nIndex_His_Data);
	xml_GetElementText(pXmlKeys->m_strSnKey, oNode, m_strSn);
	xml_GetElementText(pXmlKeys->m_strTm_UpdateKey, oNode, m_tmTm_Update);
	xml_GetElementText(pXmlKeys->m_strValue1Key, oNode, m_fValue1);
	xml_GetElementText(pXmlKeys->m_strValue2Key, oNode, m_fValue2);
	xml_GetElementText(pXmlKeys->m_strValue3Key, oNode, m_fValue3);
	xml_GetElementText(pXmlKeys->m_strValue4Key, oNode, m_fValue4);
	xml_GetElementText(pXmlKeys->m_strValue5Key, oNode, m_fValue5);
	xml_GetElementText(pXmlKeys->m_strValue6Key, oNode, m_fValue6);
	xml_GetElementText(pXmlKeys->m_strValue7Key, oNode, m_fValue7);
	xml_GetElementText(pXmlKeys->m_strValue8Key, oNode, m_fValue8);
	xml_GetElementText(pXmlKeys->m_strValue9Key, oNode, m_fValue9);
	xml_GetElementText(pXmlKeys->m_strValue10Key, oNode, m_fValue10);

	return 0;
}

long CIot_RTDeviceHisData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strIndex_His_DataKey, oXMLDoc, oElement, m_nIndex_His_Data);
	xml_SetElementText(pXmlKeys->m_strSnKey, oXMLDoc, oElement, m_strSn);
	xml_SetElementText(pXmlKeys->m_strTm_UpdateKey, oXMLDoc, oElement, m_tmTm_Update);
	xml_SetElementText(pXmlKeys->m_strValue1Key, oXMLDoc, oElement, m_fValue1);
	xml_SetElementText(pXmlKeys->m_strValue2Key, oXMLDoc, oElement, m_fValue2);
	xml_SetElementText(pXmlKeys->m_strValue3Key, oXMLDoc, oElement, m_fValue3);
	xml_SetElementText(pXmlKeys->m_strValue4Key, oXMLDoc, oElement, m_fValue4);
	xml_SetElementText(pXmlKeys->m_strValue5Key, oXMLDoc, oElement, m_fValue5);
	xml_SetElementText(pXmlKeys->m_strValue6Key, oXMLDoc, oElement, m_fValue6);
	xml_SetElementText(pXmlKeys->m_strValue7Key, oXMLDoc, oElement, m_fValue7);
	xml_SetElementText(pXmlKeys->m_strValue8Key, oXMLDoc, oElement, m_fValue8);
	xml_SetElementText(pXmlKeys->m_strValue9Key, oXMLDoc, oElement, m_fValue9);
	xml_SetElementText(pXmlKeys->m_strValue10Key, oXMLDoc, oElement, m_fValue10);

	return 0;
}

long CIot_RTDeviceHisData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_His_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue1);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue2);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue3);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue4);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue5);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue6);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue7);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue8);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue9);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue10);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_His_Data);
		BinarySerializeRead(oBinaryBuffer, m_strSn);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeRead(oBinaryBuffer, m_fValue1);
		BinarySerializeRead(oBinaryBuffer, m_fValue2);
		BinarySerializeRead(oBinaryBuffer, m_fValue3);
		BinarySerializeRead(oBinaryBuffer, m_fValue4);
		BinarySerializeRead(oBinaryBuffer, m_fValue5);
		BinarySerializeRead(oBinaryBuffer, m_fValue6);
		BinarySerializeRead(oBinaryBuffer, m_fValue7);
		BinarySerializeRead(oBinaryBuffer, m_fValue8);
		BinarySerializeRead(oBinaryBuffer, m_fValue9);
		BinarySerializeRead(oBinaryBuffer, m_fValue10);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_His_Data);
		BinarySerializeWrite(oBinaryBuffer, m_strSn);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeWrite(oBinaryBuffer, m_fValue1);
		BinarySerializeWrite(oBinaryBuffer, m_fValue2);
		BinarySerializeWrite(oBinaryBuffer, m_fValue3);
		BinarySerializeWrite(oBinaryBuffer, m_fValue4);
		BinarySerializeWrite(oBinaryBuffer, m_fValue5);
		BinarySerializeWrite(oBinaryBuffer, m_fValue6);
		BinarySerializeWrite(oBinaryBuffer, m_fValue7);
		BinarySerializeWrite(oBinaryBuffer, m_fValue8);
		BinarySerializeWrite(oBinaryBuffer, m_fValue9);
		BinarySerializeWrite(oBinaryBuffer, m_fValue10);
	}
	return 0;
}

void CIot_RTDeviceHisData::InitAfterRead()
{
}

BOOL CIot_RTDeviceHisData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RTDeviceHisData *p = (CIot_RTDeviceHisData*)pObj;

	if(m_nIndex_His_Data != p->m_nIndex_His_Data)
	{
		return FALSE;
	}

	if(m_strSn != p->m_strSn)
	{
		return FALSE;
	}

	if(m_fValue1 != p->m_fValue1)
	{
		return FALSE;
	}

	if(m_fValue2 != p->m_fValue2)
	{
		return FALSE;
	}

	if(m_fValue3 != p->m_fValue3)
	{
		return FALSE;
	}

	if(m_fValue4 != p->m_fValue4)
	{
		return FALSE;
	}

	if(m_fValue5 != p->m_fValue5)
	{
		return FALSE;
	}

	if(m_fValue6 != p->m_fValue6)
	{
		return FALSE;
	}

	if(m_fValue7 != p->m_fValue7)
	{
		return FALSE;
	}

	if(m_fValue8 != p->m_fValue8)
	{
		return FALSE;
	}

	if(m_fValue9 != p->m_fValue9)
	{
		return FALSE;
	}

	if(m_fValue10 != p->m_fValue10)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RTDeviceHisData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RTDeviceHisData *p = (CIot_RTDeviceHisData*)pDest;

	p->m_nIndex_His_Data = m_nIndex_His_Data;
	p->m_strSn = m_strSn;
	p->m_tmTm_Update = m_tmTm_Update;
	p->m_fValue1 = m_fValue1;
	p->m_fValue2 = m_fValue2;
	p->m_fValue3 = m_fValue3;
	p->m_fValue4 = m_fValue4;
	p->m_fValue5 = m_fValue5;
	p->m_fValue6 = m_fValue6;
	p->m_fValue7 = m_fValue7;
	p->m_fValue8 = m_fValue8;
	p->m_fValue9 = m_fValue9;
	p->m_fValue10 = m_fValue10;
	return TRUE;
}

CBaseObject* CIot_RTDeviceHisData::Clone()
{
	CIot_RTDeviceHisData *p = new CIot_RTDeviceHisData();
	Copy(p);
	return p;
}

CBaseObject* CIot_RTDeviceHisData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RTDeviceHisData *p = new CIot_RTDeviceHisData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RTDeviceHisData::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_His_DataKey, m_nIndex_His_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue1Key, m_fValue1);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue2Key, m_fValue2);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue3Key, m_fValue3);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue4Key, m_fValue4);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue5Key, m_fValue5);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue6Key, m_fValue6);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue7Key, m_fValue7);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue8Key, m_fValue8);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue9Key, m_fValue9);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue10Key, m_fValue10);
	return 0;
}

long CIot_RTDeviceHisData::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_His_DataKey, m_nIndex_His_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue1Key, m_fValue1);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue2Key, m_fValue2);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue3Key, m_fValue3);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue4Key, m_fValue4);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue5Key, m_fValue5);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue6Key, m_fValue6);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue7Key, m_fValue7);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue8Key, m_fValue8);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue9Key, m_fValue9);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue10Key, m_fValue10);
	return 0;
}

void CIot_RTDeviceHisData::UpdateValue(const CString &strData, const CString &strValue)
{
	float fValue = CString_To_double(strValue);

	if (strData == _T("value1"))
	{
		m_fValue1 = fValue;
	}

	if (strData == _T("value2"))
	{
		m_fValue2 = fValue;
	}

	if (strData == _T("value3"))
	{
		m_fValue3 = fValue;
	}

	if (strData == _T("value4"))
	{
		m_fValue4 = fValue;
	}

	if (strData == _T("value5"))
	{
		m_fValue5 = fValue;
	}

	if (strData == _T("value6"))
	{
		m_fValue6 = fValue;
	}

	if (strData == _T("value7"))
	{
		m_fValue7 = fValue;
	}

	if (strData == _T("value8"))
	{
		m_fValue8 = fValue;
	}

	if (strData == _T("value9"))
	{
		m_fValue9 = fValue;
	}

	if (strData == _T("value10"))
	{
		m_fValue10 = fValue;
	}
}