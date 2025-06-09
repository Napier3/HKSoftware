//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_DeviceConfigReq.cpp  CTcpEdgePkgData_DeviceConfigReq


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceConfigReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceConfigReq::CTcpEdgePkgData_DeviceConfigReq()
{
	//初始化属性

	//初始化成员变量
	m_pTcpEdgePkgTemperature = NULL;
	m_arrayNotMust[0] = PkgData_Node_DevName;
	m_arrayNotMust[1] = PkgData_Node_CpuLmt;
	m_arrayNotMust[2] = PkgData_Node_MemLmt;
	m_arrayNotMust[3] = PkgData_Node_DiskLmt;
	m_arrayNotMust[4] = PkgData_Node_Temperature;
}

CTcpEdgePkgData_DeviceConfigReq::~CTcpEdgePkgData_DeviceConfigReq()
{
}

long CTcpEdgePkgData_DeviceConfigReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDevNameKey, oNode, m_strDevName);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuLmtKey, oNode, m_strCpuLmt);
	xml_GetAttibuteValue(pXmlKeys->m_strMemLmtKey, oNode, m_strMemLmt);
	xml_GetAttibuteValue(pXmlKeys->m_strDiskLmtKey, oNode, m_strDiskLmt);
	return 0;
}

long CTcpEdgePkgData_DeviceConfigReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDevNameKey, oElement, m_strDevName);
	xml_SetAttributeValue(pXmlKeys->m_strCpuLmtKey, oElement, m_strCpuLmt);
	xml_SetAttributeValue(pXmlKeys->m_strMemLmtKey, oElement, m_strMemLmt);
	xml_SetAttributeValue(pXmlKeys->m_strDiskLmtKey, oElement, m_strDiskLmt);
	return 0;
}

long CTcpEdgePkgData_DeviceConfigReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDevName);
		BinarySerializeCalLen(oBinaryBuffer, m_strCpuLmt);
		BinarySerializeCalLen(oBinaryBuffer, m_strMemLmt);
		BinarySerializeCalLen(oBinaryBuffer, m_strDiskLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDevName);
		BinarySerializeRead(oBinaryBuffer, m_strCpuLmt);
		BinarySerializeRead(oBinaryBuffer, m_strMemLmt);
		BinarySerializeRead(oBinaryBuffer, m_strDiskLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDevName);
		BinarySerializeWrite(oBinaryBuffer, m_strCpuLmt);
		BinarySerializeWrite(oBinaryBuffer, m_strMemLmt);
		BinarySerializeWrite(oBinaryBuffer, m_strDiskLmt);
	}
	return 0;
}

void CTcpEdgePkgData_DeviceConfigReq::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CTCPEDGEPKGTEMPERATURE)
		{
			m_pTcpEdgePkgTemperature = (CTcpEdgePkgTemperature*)p;
		}
	}

	if (m_pTcpEdgePkgTemperature == NULL)
	{
		m_pTcpEdgePkgTemperature = (CTcpEdgePkgTemperature*)AddNewChild(new CTcpEdgePkgTemperature());
	}

}

BOOL CTcpEdgePkgData_DeviceConfigReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceConfigReq *p = (CTcpEdgePkgData_DeviceConfigReq*)pObj;

	if(m_strDevName != p->m_strDevName)
	{
		return FALSE;
	}

	if(m_strCpuLmt != p->m_strCpuLmt)
	{
		return FALSE;
	}

	if(m_strMemLmt != p->m_strMemLmt)
	{
		return FALSE;
	}

	if(m_strDiskLmt != p->m_strDiskLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_DeviceConfigReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceConfigReq *p = (CTcpEdgePkgData_DeviceConfigReq*)pDest;

	p->m_strDevName = m_strDevName;
	p->m_strCpuLmt = m_strCpuLmt;
	p->m_strMemLmt = m_strMemLmt;
	p->m_strDiskLmt = m_strDiskLmt;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceConfigReq::Clone()
{
	CTcpEdgePkgData_DeviceConfigReq *p = new CTcpEdgePkgData_DeviceConfigReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceConfigReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceConfigReq *p = new CTcpEdgePkgData_DeviceConfigReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceConfigReq::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CTCPEDGEPKGTEMPERATURE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceConfigReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTcpEdgePkgTemperatureKey)
	{
		pNew = new CTcpEdgePkgTemperature();
	}

	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceConfigReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CTCPEDGEPKGTEMPERATURE)
	{
		pNew = new CTcpEdgePkgTemperature();
	}

	return pNew;
}
long CTcpEdgePkgData_DeviceConfigReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDevNameKey, m_strDevName);
	pRecordset->GetFieldValue(pXmlKeys->m_strCpuLmtKey, m_strCpuLmt);
	pRecordset->GetFieldValue(pXmlKeys->m_strMemLmtKey, m_strMemLmt);
	pRecordset->GetFieldValue(pXmlKeys->m_strDiskLmtKey, m_strDiskLmt);
	return 0;
}

long CTcpEdgePkgData_DeviceConfigReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDevNameKey, m_strDevName);
	pRecordset->SetFieldValue(pXmlKeys->m_strCpuLmtKey, m_strCpuLmt);
	pRecordset->SetFieldValue(pXmlKeys->m_strMemLmtKey, m_strMemLmt);
	pRecordset->SetFieldValue(pXmlKeys->m_strDiskLmtKey, m_strDiskLmt);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_DeviceConfigReq::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DevName, 0);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_CpuLmt, 0);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_MemLmt, 0);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DiskLmt, 0);
	CTcpEdgePkgData::AddNewData(pDataset, CTcpEdgePkgTemperature::ToDataset(), 0);

	return pDataset;
}