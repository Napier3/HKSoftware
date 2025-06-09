//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetHisEventResp_Device.cpp  CPkg_GetHisEventResp_Device


#include "stdafx.h"
#include "Pkg_GetHisEventResp_Device.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_GetHisEventResp_Device::CPkg_GetHisEventResp_Device()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetHisEventResp_Device::~CPkg_GetHisEventResp_Device()
{
}

BOOL CPkg_GetHisEventResp_Device::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);

	if(!strAttrVal.GetLength())
	{
		//值不存在时检查是否必需
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString("【错误】【必需项缺失】GetHisEventResp：[%1]=>[%2$%3]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】GetHisEventResp：[%1]=>[%2$%3]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	if(strAttrName == L"Value")
	{
		if(m_strResult != _T("1"))
		{
			if(m_strResult == _T("0"))
			{
				strTemp = QString(_T("【执行失败】GetHisEventResp：从设备[%1]中查询历史操作记录失败;\n")).arg(m_strDeviceId);
				m_strErrorInfo += strTemp;
				m_strReturnFalse += strTemp;
			}
			else
			{
				strTemp = QString(_T("【错误】【超过范围】GetHisEventResp：[%1]=>[%2$Result]字段超出范围, 无法判断执行状态;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_Devices);
				m_strErrorInfo += strTemp;
				m_strRangeOut += strTemp;
			}
		}
	}

	if(strAttrName == L"EventDesc")
	{
		if(strAttrVal != _T("遥控选择") && strAttrVal != _T("遥控执行") && strAttrVal != _T("遥控取消") && strAttrVal != _T("遥控直控")
			&& strAttrVal != _T("遥调选择") && strAttrVal != _T("遥调执行") && strAttrVal != _T("遥调取消") && strAttrVal != _T("遥调直控"))
		{
			m_arrayNotMust[1] = PkgData_Node_DataRefer;
			m_arrayNotMust[2] = PkgData_Node_DataDesc;
			m_arrayNotMust[3] = PkgData_Node_Value;
		}
	}
		
	return bRet;
}

long CPkg_GetHisEventResp_Device::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTimeStampKey, oNode, m_strTimeStamp);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceDescKey, oNode, m_strDeviceDesc);
	xml_GetAttibuteValue(pXmlKeys->m_strEventDescKey, oNode, m_strEventDesc);
	xml_GetAttibuteValue(pXmlKeys->m_strResultKey, oNode, m_strResult);
	xml_GetAttibuteValue(pXmlKeys->m_strDataReferKey, oNode, m_strDataRefer);
	xml_GetAttibuteValue(pXmlKeys->m_strDataDescKey, oNode, m_strDataDesc);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	//lmy，20230915修改
	//m_strErrorInfo += CheckTimeFormat(_T("DataReadResp"), PkgData_Node_Devices, PkgData_Node_TimeStamp, 
	//	_T(""), _T(""), m_strTimeStamp);
	//m_strRangeOut += CheckTimeFormat(_T("DataReadResp"), PkgData_Node_Devices, PkgData_Node_TimeStamp, 
	//	_T(""), _T(""), m_strTimeStamp);
	m_strErrorInfo += CheckTimeFormat(_T("GetHisEventResp"), PkgData_Node_Devices, PkgData_Node_TimeStamp, 
		_T(""), _T(""), m_strTimeStamp);
	m_strRangeOut += CheckTimeFormat(_T("GetHisEventResp"), PkgData_Node_Devices, PkgData_Node_TimeStamp, 
		_T(""), _T(""), m_strTimeStamp);

	return 0;
}

long CPkg_GetHisEventResp_Device::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTimeStampKey, oElement, m_strTimeStamp);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceDescKey, oElement, m_strDeviceDesc);
	xml_SetAttributeValue(pXmlKeys->m_strEventDescKey, oElement, m_strEventDesc);
	xml_SetAttributeValue(pXmlKeys->m_strResultKey, oElement, m_strResult);
	xml_SetAttributeValue(pXmlKeys->m_strDataReferKey, oElement, m_strDataRefer);
	xml_SetAttributeValue(pXmlKeys->m_strDataDescKey, oElement, m_strDataDesc);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CPkg_GetHisEventResp_Device::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTimeStamp);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceDesc);
		BinarySerializeCalLen(oBinaryBuffer, m_strEventDesc);
		BinarySerializeCalLen(oBinaryBuffer, m_strResult);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataRefer);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataDesc);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTimeStamp);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceDesc);
		BinarySerializeRead(oBinaryBuffer, m_strEventDesc);
		BinarySerializeRead(oBinaryBuffer, m_strResult);
		BinarySerializeRead(oBinaryBuffer, m_strDataRefer);
		BinarySerializeRead(oBinaryBuffer, m_strDataDesc);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTimeStamp);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceDesc);
		BinarySerializeWrite(oBinaryBuffer, m_strEventDesc);
		BinarySerializeWrite(oBinaryBuffer, m_strResult);
		BinarySerializeWrite(oBinaryBuffer, m_strDataRefer);
		BinarySerializeWrite(oBinaryBuffer, m_strDataDesc);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CPkg_GetHisEventResp_Device::InitAfterRead()
{
}

BOOL CPkg_GetHisEventResp_Device::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetHisEventResp_Device *p = (CPkg_GetHisEventResp_Device*)pObj;

	if(m_strTimeStamp != p->m_strTimeStamp)
	{
		return FALSE;
	}

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strDeviceDesc != p->m_strDeviceDesc)
	{
		return FALSE;
	}

	if(m_strEventDesc != p->m_strEventDesc)
	{
		return FALSE;
	}

	if(m_strResult != p->m_strResult)
	{
		return FALSE;
	}

	if(m_strDataRefer != p->m_strDataRefer)
	{
		return FALSE;
	}

	if(m_strDataDesc != p->m_strDataDesc)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetHisEventResp_Device::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetHisEventResp_Device *p = (CPkg_GetHisEventResp_Device*)pDest;

	p->m_strTimeStamp = m_strTimeStamp;
	p->m_strDeviceId = m_strDeviceId;
	p->m_strDeviceDesc = m_strDeviceDesc;
	p->m_strEventDesc = m_strEventDesc;
	p->m_strResult = m_strResult;
	p->m_strDataRefer = m_strDataRefer;
	p->m_strDataDesc = m_strDataDesc;
	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CPkg_GetHisEventResp_Device::Clone()
{
	CPkg_GetHisEventResp_Device *p = new CPkg_GetHisEventResp_Device();
	Copy(p);
	return p;
}

CBaseObject* CPkg_GetHisEventResp_Device::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_GetHisEventResp_Device *p = new CPkg_GetHisEventResp_Device();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_GetHisEventResp_Device::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetHisEventResp_Device::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetHisEventResp_Device::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetHisEventResp_Device::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strTimeStampKey, m_strTimeStamp);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceDescKey, m_strDeviceDesc);
	pRecordset->GetFieldValue(pXmlKeys->m_strEventDescKey, m_strEventDesc);
	pRecordset->GetFieldValue(pXmlKeys->m_strResultKey, m_strResult);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataDescKey, m_strDataDesc);
	pRecordset->GetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	return 0;
}

long CPkg_GetHisEventResp_Device::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strTimeStampKey, m_strTimeStamp);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceDescKey, m_strDeviceDesc);
	pRecordset->SetFieldValue(pXmlKeys->m_strEventDescKey, m_strEventDesc);
	pRecordset->SetFieldValue(pXmlKeys->m_strResultKey, m_strResult);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataDescKey, m_strDataDesc);
	pRecordset->SetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	return 0;
}

