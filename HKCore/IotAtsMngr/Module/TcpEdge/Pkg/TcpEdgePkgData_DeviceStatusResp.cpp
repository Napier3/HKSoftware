//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利
//TcpEdgePkgData_DeviceStatusResp.cpp  CTcpEdgePkgData_DeviceStatusResp


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceStatusResp.h"
#include "Pkg_DeviceStatusResp_LinkState.h"
#include "Pkg_DeviceStatusResp_LinkStates.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceStatusResp::CTcpEdgePkgData_DeviceStatusResp()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_Longitude;
	m_arrayNotMust[1] = PkgData_Node_Latitude;
}

CTcpEdgePkgData_DeviceStatusResp::~CTcpEdgePkgData_DeviceStatusResp()
{
}

BOOL CTcpEdgePkgData_DeviceStatusResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】DeviceStatusResp：[%1]=>[%2]必需字段缺失;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】DeviceStatusResp：[%1]=>[%2]字段类型错误;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_DeviceStatusResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCpuRateKey, oNode, m_strCpuRate);
	xml_GetAttibuteValue(pXmlKeys->m_strDiskUsedKey, oNode, m_strDiskUsed);
	xml_GetAttibuteValue(pXmlKeys->m_strTempValueKey, oNode, m_strTempValue);
	xml_GetAttibuteValue(pXmlKeys->m_strDevDateTimeKey, oNode, m_strDevDateTime);
	xml_GetAttibuteValue(pXmlKeys->m_strDevStDateTimeKey, oNode, m_strDevStDateTime);
	xml_GetAttibuteValue(pXmlKeys->m_strDevRunTimeKey, oNode, m_strDevRunTime);
	xml_GetAttibuteValue(pXmlKeys->m_strLongitudeKey, oNode, m_strLongitude);
	xml_GetAttibuteValue(pXmlKeys->m_strLatitudeKey, oNode, m_strLatitude);
	xml_GetAttibuteValue(pXmlKeys->m_strMemUsedKey, oNode, m_strMemUsed);
	//取到JSON
	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	//检测JSON报文中是否存在LinkState节点，存在则动态创建LinkState并添加
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_LinkState);
	if(pDatasJson)
	{
		CPkg_DeviceStatusResp_LinkStates* pDatas = new CPkg_DeviceStatusResp_LinkStates;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_LinkState;
		AddNewChild(pDatas);

		//遍历Devices，动态创建子结构
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{

			CPkg_DeviceStatusResp_LinkState* pData = new CPkg_DeviceStatusResp_LinkState;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			//调用子类里的函数来解析数据，如果子类中包含数组，去子类的该函数中做类似处理
			pData->m_strErrorInfo = m_strErrorInfo;
			pData->m_strNecessityLack = m_strNecessityLack;
			pData->m_strNecessityErr = m_strNecessityErr;
			pData->m_strRangeOut = m_strRangeOut;
			pData->m_strReturnFalse = m_strReturnFalse;
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			m_strErrorInfo = pData->m_strErrorInfo;
			m_strNecessityLack = pData->m_strNecessityLack;
			m_strNecessityErr = pData->m_strNecessityErr;
			m_strRangeOut = pData->m_strRangeOut;
			m_strReturnFalse = pData->m_strReturnFalse;

			delete pTempJsonNode;
			//解析完成后作为次级报文添加到pDevices
			pDatas->AddNewChild(pData);	

			pDatasChild = pDatasChild->next;
		}
	}
	else
	{
		QString strTemp;
		CString strID(GetXmlElementKey());
		strTemp = QString("【错误】【必需项缺失】DeviceStatusResp：[%1]=>[%2] 必需字段array缺失;\n").arg(strID).arg(PkgData_Node_LinkState);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}

	m_strErrorInfo += CheckRangePer(_T("DeviceStatusResp"), PkgData_Node_CpuRate, m_strCpuRate);
	m_strErrorInfo += CheckRangePer(_T("DeviceStatusResp"), PkgData_Node_MemUsed, m_strMemUsed);
	m_strErrorInfo += CheckRangePer(_T("DeviceStatusResp"), PkgData_Node_DiskUsed, m_strDiskUsed);
	m_strErrorInfo += CheckTimeFormat(_T("DeviceStatusResp"), PkgData_Node_DevDateTime, m_strDevDateTime);
	m_strErrorInfo += CheckTimeFormat(_T("DeviceStatusResp"), PkgData_Node_DevStDateTime, m_strDevStDateTime);

	m_strRangeOut += CheckRangePer(_T("DeviceStatusResp"), PkgData_Node_CpuRate, m_strCpuRate);
	m_strRangeOut += CheckRangePer(_T("DeviceStatusResp"), PkgData_Node_MemUsed, m_strMemUsed);
	m_strRangeOut += CheckRangePer(_T("DeviceStatusResp"), PkgData_Node_DiskUsed, m_strDiskUsed);
	m_strRangeOut += CheckTimeFormat(_T("DeviceStatusResp"), PkgData_Node_DevDateTime, m_strDevDateTime);
	m_strRangeOut += CheckTimeFormat(_T("DeviceStatusResp"), PkgData_Node_DevStDateTime, m_strDevStDateTime);

	return 0;
}

long CTcpEdgePkgData_DeviceStatusResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCpuRateKey, oElement, m_strCpuRate);
	xml_SetAttributeValue(pXmlKeys->m_strDiskUsedKey, oElement, m_strDiskUsed);
	xml_SetAttributeValue(pXmlKeys->m_strTempValueKey, oElement, m_strTempValue);
	xml_SetAttributeValue(pXmlKeys->m_strDevDateTimeKey, oElement, m_strDevDateTime);
	xml_SetAttributeValue(pXmlKeys->m_strDevStDateTimeKey, oElement, m_strDevStDateTime);
	xml_SetAttributeValue(pXmlKeys->m_strDevRunTimeKey, oElement, m_strDevRunTime);
	xml_SetAttributeValue(pXmlKeys->m_strLongitudeKey, oElement, m_strLongitude);
	xml_SetAttributeValue(pXmlKeys->m_strLatitudeKey, oElement, m_strLatitude);
	xml_SetAttributeValue(pXmlKeys->m_strMemUsedKey, oElement, m_strMemUsed);
	
	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	CPkg_DeviceStatusResp_LinkStates* pDatas = (CPkg_DeviceStatusResp_LinkStates*)FindByID(PkgData_Node_LinkState);
	if(pDatas == NULL)
	{
		return 0;
	}

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while(pos)
	{
		CPkg_DeviceStatusResp_LinkState* pData = (CPkg_DeviceStatusResp_LinkState*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_LinkState, pDatasJson);

	DeleteByID(PkgData_Node_LinkState);
	return 0;
}

long CTcpEdgePkgData_DeviceStatusResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCpuRate);
		BinarySerializeCalLen(oBinaryBuffer, m_strDiskUsed);
		BinarySerializeCalLen(oBinaryBuffer, m_strTempValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevDateTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevStDateTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevRunTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strLongitude);
		BinarySerializeCalLen(oBinaryBuffer, m_strLatitude);
		BinarySerializeCalLen(oBinaryBuffer, m_strMemUsed);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCpuRate);
		BinarySerializeRead(oBinaryBuffer, m_strDiskUsed);
		BinarySerializeRead(oBinaryBuffer, m_strTempValue);
		BinarySerializeRead(oBinaryBuffer, m_strDevDateTime);
		BinarySerializeRead(oBinaryBuffer, m_strDevStDateTime);
		BinarySerializeRead(oBinaryBuffer, m_strDevRunTime);
		BinarySerializeRead(oBinaryBuffer, m_strLongitude);
		BinarySerializeRead(oBinaryBuffer, m_strLatitude);
		BinarySerializeRead(oBinaryBuffer, m_strMemUsed);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCpuRate);
		BinarySerializeWrite(oBinaryBuffer, m_strDiskUsed);
		BinarySerializeWrite(oBinaryBuffer, m_strTempValue);
		BinarySerializeWrite(oBinaryBuffer, m_strDevDateTime);
		BinarySerializeWrite(oBinaryBuffer, m_strDevStDateTime);
		BinarySerializeWrite(oBinaryBuffer, m_strDevRunTime);
		BinarySerializeWrite(oBinaryBuffer, m_strLongitude);
		BinarySerializeWrite(oBinaryBuffer, m_strLatitude);
		BinarySerializeWrite(oBinaryBuffer, m_strMemUsed);
	}
	return 0;
}

void CTcpEdgePkgData_DeviceStatusResp::InitAfterRead()
{

}

BOOL CTcpEdgePkgData_DeviceStatusResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceStatusResp *p = (CTcpEdgePkgData_DeviceStatusResp*)pObj;

	if(m_strCpuRate != p->m_strCpuRate)
	{
		return FALSE;
	}

	if(m_strDiskUsed != p->m_strDiskUsed)
	{
		return FALSE;
	}

	if(m_strTempValue != p->m_strTempValue)
	{
		return FALSE;
	}

	if(m_strDevDateTime != p->m_strDevDateTime)
	{
		return FALSE;
	}

	if(m_strDevStDateTime != p->m_strDevStDateTime)
	{
		return FALSE;
	}

	if(m_strDevRunTime != p->m_strDevRunTime)
	{
		return FALSE;
	}

	if(m_strLongitude != p->m_strLongitude)
	{
		return FALSE;
	}

	if(m_strLatitude != p->m_strLatitude)
	{
		return FALSE;
	}

	if(m_strMemUsed != p->m_strMemUsed)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CTcpEdgePkgData_DeviceStatusResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceStatusResp *p = (CTcpEdgePkgData_DeviceStatusResp*)pDest;

	p->m_strCpuRate = m_strCpuRate;
	p->m_strDiskUsed = m_strDiskUsed;
	p->m_strTempValue = m_strTempValue;
	p->m_strDevDateTime = m_strDevDateTime;
	p->m_strDevStDateTime = m_strDevStDateTime;
	p->m_strDevRunTime = m_strDevRunTime;
	p->m_strLongitude = m_strLongitude;
	p->m_strLatitude = m_strLatitude;
	p->m_strMemUsed = m_strMemUsed;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceStatusResp::Clone()
{
	CTcpEdgePkgData_DeviceStatusResp *p = new CTcpEdgePkgData_DeviceStatusResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceStatusResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceStatusResp *p = new CTcpEdgePkgData_DeviceStatusResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceStatusResp::CanPaste(UINT nClassID)
{

	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceStatusResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceStatusResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_DeviceStatusResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strCpuRateKey, m_strCpuRate);
	pRecordset->GetFieldValue(pXmlKeys->m_strDiskUsedKey, m_strDiskUsed);
	pRecordset->GetFieldValue(pXmlKeys->m_strTempValueKey, m_strTempValue);
	pRecordset->GetFieldValue(pXmlKeys->m_strDevDateTimeKey, m_strDevDateTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strDevStDateTimeKey, m_strDevStDateTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strDevRunTimeKey, m_strDevRunTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strLongitudeKey, m_strLongitude);
	pRecordset->GetFieldValue(pXmlKeys->m_strLatitudeKey, m_strLatitude);
	pRecordset->GetFieldValue(pXmlKeys->m_strMemUsedKey, m_strMemUsed);
	return 0;
}

long CTcpEdgePkgData_DeviceStatusResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strCpuRateKey, m_strCpuRate);
	pRecordset->SetFieldValue(pXmlKeys->m_strDiskUsedKey, m_strDiskUsed);
	pRecordset->SetFieldValue(pXmlKeys->m_strTempValueKey, m_strTempValue);
	pRecordset->SetFieldValue(pXmlKeys->m_strDevDateTimeKey, m_strDevDateTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strDevStDateTimeKey, m_strDevStDateTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strDevRunTimeKey, m_strDevRunTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strLongitudeKey, m_strLongitude);
	pRecordset->SetFieldValue(pXmlKeys->m_strLatitudeKey, m_strLatitude);
	pRecordset->SetFieldValue(pXmlKeys->m_strMemUsedKey, m_strMemUsed);
	return 0;
}

