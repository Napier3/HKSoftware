//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_DeviceUpdateReq.cpp  CTcpEdgePkgData_DeviceUpdateReq


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceUpdateReq.h"
#include "TcpEdgePkgFile.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceUpdateReq::CTcpEdgePkgData_DeviceUpdateReq()
{
	//初始化属性

	//初始化成员变量
	m_pTcpEdgePkgFile = NULL;
	m_arrayNotMust[0] = PkgData_Node_Policy;
}

CTcpEdgePkgData_DeviceUpdateReq::~CTcpEdgePkgData_DeviceUpdateReq()
{
}

long CTcpEdgePkgData_DeviceUpdateReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strJobIdKey, oNode, m_strJobId);
	xml_GetAttibuteValue(pXmlKeys->m_strPolicyKey, oNode, m_strPolicy);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strUpgradeTypeKey, oNode, m_strUpgradeType);
	return 0;
}

long CTcpEdgePkgData_DeviceUpdateReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strJobIdKey, oElement, m_strJobId);
	xml_SetAttributeValue(pXmlKeys->m_strPolicyKey, oElement, m_strPolicy);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strUpgradeTypeKey, oElement, m_strUpgradeType);
	return 0;
}

long CTcpEdgePkgData_DeviceUpdateReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strJobId);
		BinarySerializeCalLen(oBinaryBuffer, m_strPolicy);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strUpgradeType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strJobId);
		BinarySerializeRead(oBinaryBuffer, m_strPolicy);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strUpgradeType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strJobId);
		BinarySerializeWrite(oBinaryBuffer, m_strPolicy);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strUpgradeType);
	}
	return 0;
}

void CTcpEdgePkgData_DeviceUpdateReq::InitAfterRead()
{

}

BOOL CTcpEdgePkgData_DeviceUpdateReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceUpdateReq *p = (CTcpEdgePkgData_DeviceUpdateReq*)pObj;

	if(m_strJobId != p->m_strJobId)
	{
		return FALSE;
	}

	if(m_strPolicy != p->m_strPolicy)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strUpgradeType != p->m_strUpgradeType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_DeviceUpdateReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceUpdateReq *p = (CTcpEdgePkgData_DeviceUpdateReq*)pDest;

	p->m_strJobId = m_strJobId;
	p->m_strPolicy = m_strPolicy;
	p->m_strVersion = m_strVersion;
	p->m_strUpgradeType = m_strUpgradeType;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceUpdateReq::Clone()
{
	CTcpEdgePkgData_DeviceUpdateReq *p = new CTcpEdgePkgData_DeviceUpdateReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceUpdateReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceUpdateReq *p = new CTcpEdgePkgData_DeviceUpdateReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceUpdateReq::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceUpdateReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCTcpEdgePkgFileKey)
	{
		pNew = new CTcpEdgePkgFile();
	}

	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceUpdateReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_DeviceUpdateReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->GetFieldValue(pXmlKeys->m_strPolicyKey, m_strPolicy);
	pRecordset->GetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strUpgradeTypeKey, m_strUpgradeType);
	return 0;
}

long CTcpEdgePkgData_DeviceUpdateReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->SetFieldValue(pXmlKeys->m_strPolicyKey, m_strPolicy);
	pRecordset->SetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strUpgradeTypeKey, m_strUpgradeType);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_DeviceUpdateReq::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_JobId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Policy, 0);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Version);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_UpgradeType);
	CTcpEdgePkgData::AddNewData(pDataset, CTcpEdgePkgFile::ToDataset());

	return pDataset;
}