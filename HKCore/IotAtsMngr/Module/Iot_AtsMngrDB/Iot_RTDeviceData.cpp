//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RTDeviceData.cpp  CIot_RTDeviceData


#include "stdafx.h"
#include "Iot_RTDeviceData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RTDeviceData::CIot_RTDeviceData()
{
	//初始化属性
	m_nIndex_Device_Data = 0;
	m_nIndex_Device = 0;
	::GetLocalTime(&m_tmTm_Update);
	m_nIs_Warning = 0;

	//初始化成员变量
}

CIot_RTDeviceData::~CIot_RTDeviceData()
{
}

long CIot_RTDeviceData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strIndex_Device_DataKey, oNode, m_nIndex_Device_Data);
	xml_GetElementText(pXmlKeys->m_strIndex_Device_DataKey, oNode, m_nIndex_Device);
	xml_GetElementText(pXmlKeys->m_strSnKey, oNode, m_strSn);
	xml_GetElementText(pXmlKeys->m_strData_FormatKey, oNode, m_strData_Format);
	xml_GetElementText(pXmlKeys->m_strDataKey, oNode, m_strData);
	xml_GetElementText(pXmlKeys->m_strTm_UpdateKey, oNode, m_tmTm_Update);
	xml_GetElementText(pXmlKeys->m_strIs_WarningKey, oNode, m_nIs_Warning);

	return 0;
}

long CIot_RTDeviceData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strIndex_Device_DataKey, oXMLDoc, oElement, m_nIndex_Device_Data);
	xml_SetElementText(pXmlKeys->m_strIndex_Device_DataKey, oXMLDoc, oElement, m_nIndex_Device);
	xml_SetElementText(pXmlKeys->m_strSnKey, oXMLDoc, oElement, m_strSn);
	xml_SetElementText(pXmlKeys->m_strData_FormatKey, oXMLDoc, oElement, m_strData_Format);
	xml_SetElementText(pXmlKeys->m_strDataKey, oXMLDoc, oElement, m_strData);
	xml_SetElementText(pXmlKeys->m_strTm_UpdateKey, oXMLDoc, oElement, m_tmTm_Update);
	xml_SetElementText(pXmlKeys->m_strIs_WarningKey, oXMLDoc, oElement, m_nIs_Warning);

	return 0;
}

long CIot_RTDeviceData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn);
		BinarySerializeCalLen(oBinaryBuffer, m_strData_Format);
		BinarySerializeCalLen(oBinaryBuffer, m_strData);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeCalLen(oBinaryBuffer, m_nIs_Warning);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Data);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_strSn);
		BinarySerializeRead(oBinaryBuffer, m_strData_Format);
		BinarySerializeRead(oBinaryBuffer, m_strData);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeRead(oBinaryBuffer, m_nIs_Warning);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Data);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_strSn);
		BinarySerializeWrite(oBinaryBuffer, m_strData_Format);
		BinarySerializeWrite(oBinaryBuffer, m_strData);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeWrite(oBinaryBuffer, m_nIs_Warning);
	}
	return 0;
}

void CIot_RTDeviceData::InitAfterRead()
{
}

BOOL CIot_RTDeviceData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RTDeviceData *p = (CIot_RTDeviceData*)pObj;

	if(m_nIndex_Device_Data != p->m_nIndex_Device_Data)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_strSn != p->m_strSn)
	{
		return FALSE;
	}

	if(m_strData_Format != p->m_strData_Format)
	{
		return FALSE;
	}

	if(m_strData != p->m_strData)
	{
		return FALSE;
	}

	if(m_nIs_Warning != p->m_nIs_Warning)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RTDeviceData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RTDeviceData *p = (CIot_RTDeviceData*)pDest;

	p->m_nIndex_Device_Data = m_nIndex_Device_Data;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_strSn = m_strSn;
	p->m_strData_Format = m_strData_Format;
	p->m_strData = m_strData;
	p->m_tmTm_Update = m_tmTm_Update;
	p->m_nIs_Warning = m_nIs_Warning;
	return TRUE;
}

CBaseObject* CIot_RTDeviceData::Clone()
{
	CIot_RTDeviceData *p = new CIot_RTDeviceData();
	Copy(p);
	return p;
}

CBaseObject* CIot_RTDeviceData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RTDeviceData *p = new CIot_RTDeviceData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RTDeviceData::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_DataKey, m_nIndex_Device_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->GetFieldValue(pXmlKeys->m_strData_FormatKey, m_strData_Format);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataKey, m_strData);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	pRecordset->GetFieldValue(pXmlKeys->m_strIs_WarningKey, m_nIs_Warning);
	return 0;
}

long CIot_RTDeviceData::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_DataKey, m_nIndex_Device_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->SetFieldValue(pXmlKeys->m_strData_FormatKey, m_strData_Format);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataKey, m_strData);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	pRecordset->SetFieldValue(pXmlKeys->m_strIs_WarningKey, m_nIs_Warning);
	return 0;
}

//2021-10-10  lijunqing  暂时放在这里，后面放到基类进行处理
long CIot_RTDeviceData::ReadFromBuffer(char *pszBuffer)
{
	long nLen = strlen(pszBuffer);

	if (*pszBuffer == '{')
	{//JSON
		SetXml_UTF8(pszBuffer,nLen, CIot_AtsMngrXmlRWKeys::g_pXmlKeys,_JSON_TYPE_);
	}
	else
	{//XML
		SetXml_UTF8(pszBuffer, nLen, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}

	return 0;
}

#include "..\..\..\Module\MySqlApp\MySqlBaseApp.h"
#include "Iot_Device.h"

long CIot_RTDeviceData::WriteToDB_ByBuffer(char *pszBuffer)
{
	ReadFromBuffer(pszBuffer);

	CString strSql,strRtDeviceDataTable,strSNKey;
	strRtDeviceDataTable = CIot_AtsMngrXmlRWKeys::CIot_RTDeviceDataKey();
	strSNKey = CIot_AtsMngrXmlRWKeys::SnKey();

	strSql.Format(_T("select * from %s where %s=\"%s\" limit 1"),strRtDeviceDataTable,strSNKey,m_strSn);
	BOOL bRet = DB_Select_OwnEx(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys,strSql);

	if (bRet)
	{
		DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		//不存在，则查询装置表，得到Index_device
		CString strDeviceTable;
		strDeviceTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();

		CIot_Device oDevice;
		strSql.Format(_T("select * from %s where %s=\"%s\" limit 1"),strDeviceTable,strSNKey,m_strSn);

		bRet = oDevice.DB_Select_OwnEx(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys,strSql);
	
		if (!bRet)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("UpdateRTDeviceData:查询装置信息[%s]失败！"),m_strSn);
			return FALSE;
		}

		m_nIndex_Device = oDevice.m_nIndex_Device;
		DB_Insert_Own(g_pTheMySqlApp, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);
	}

	return 0;
}