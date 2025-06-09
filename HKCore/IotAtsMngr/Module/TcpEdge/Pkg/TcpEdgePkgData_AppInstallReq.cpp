//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_AppInstallReq.cpp  CTcpEdgePkgData_AppInstallReq


#include "stdafx.h"
#include "TcpEdgePkgData_AppInstallReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppInstallReq::CTcpEdgePkgData_AppInstallReq()
{
	//初始化属性

	//初始化成员变量
	m_pTcpEdgePkgFile = NULL;
	m_pTcpEdgePkgCfgCpu = NULL;
	m_pTcpEdgePkgCfgMem = NULL;

	m_arrayNotMust[0] = PkgData_Node_Policy;
	m_arrayNotMust[1] = PkgData_Node_CfgCpu;
	m_arrayNotMust[2] = PkgData_Node_CfgMem;
	//lmy，20230919注释，Enable是必需项
	//m_arrayNotMust[3] = PkgData_Node_Enable;

	m_strErrorInfo = _T("");
}

CTcpEdgePkgData_AppInstallReq::~CTcpEdgePkgData_AppInstallReq()
{
}

long CTcpEdgePkgData_AppInstallReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strJobIdKey, oNode, m_strJobId);
	xml_GetAttibuteValue(pXmlKeys->m_strPolicyKey, oNode, m_strPolicy);
	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strEnableKey, oNode, m_strEnable);
	return 0;
}

long CTcpEdgePkgData_AppInstallReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strJobIdKey, oElement, m_strJobId);
	xml_SetAttributeValue(pXmlKeys->m_strPolicyKey, oElement, m_strPolicy);
	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strEnableKey, oElement, m_strEnable);
	return 0;
}

long CTcpEdgePkgData_AppInstallReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strJobId);
		BinarySerializeCalLen(oBinaryBuffer, m_strPolicy);
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strEnable);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strJobId);
		BinarySerializeRead(oBinaryBuffer, m_strPolicy);
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
		BinarySerializeRead(oBinaryBuffer, m_strApp);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strEnable);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strJobId);
		BinarySerializeWrite(oBinaryBuffer, m_strPolicy);
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strEnable);
	}
	return 0;
}

void CTcpEdgePkgData_AppInstallReq::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CTCPEDGEPKGFILE)
		{
			m_pTcpEdgePkgFile = (CTcpEdgePkgFile*)p;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
		{
			m_pTcpEdgePkgCfgCpu = (CTcpEdgePkgCfgCpu*)p;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
		{
			m_pTcpEdgePkgCfgMem = (CTcpEdgePkgCfgMem*)p;
		}
	}

	if (m_pTcpEdgePkgFile == NULL)
	{
		m_pTcpEdgePkgFile = (CTcpEdgePkgFile*)AddNewChild(new CTcpEdgePkgFile());
	}

	if (m_pTcpEdgePkgCfgCpu == NULL)
	{
		m_pTcpEdgePkgCfgCpu = (CTcpEdgePkgCfgCpu*)AddNewChild(new CTcpEdgePkgCfgCpu());
	}

	if (m_pTcpEdgePkgCfgMem == NULL)
	{
		m_pTcpEdgePkgCfgMem = (CTcpEdgePkgCfgMem*)AddNewChild(new CTcpEdgePkgCfgMem());
	}

}

BOOL CTcpEdgePkgData_AppInstallReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppInstallReq *p = (CTcpEdgePkgData_AppInstallReq*)pObj;

	if(m_strJobId != p->m_strJobId)
	{
		return FALSE;
	}

	if(m_strPolicy != p->m_strPolicy)
	{
		return FALSE;
	}

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strEnable != p->m_strEnable)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_AppInstallReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppInstallReq *p = (CTcpEdgePkgData_AppInstallReq*)pDest;

	p->m_strJobId = m_strJobId;
	p->m_strPolicy = m_strPolicy;
	p->m_strContainer = m_strContainer;
	p->m_strApp = m_strApp;
	p->m_strVersion = m_strVersion;
	p->m_strEnable = m_strEnable;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppInstallReq::Clone()
{
	CTcpEdgePkgData_AppInstallReq *p = new CTcpEdgePkgData_AppInstallReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppInstallReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppInstallReq *p = new CTcpEdgePkgData_AppInstallReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppInstallReq::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CTCPEDGEPKGFILE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_AppInstallReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTcpEdgePkgFileKey)
	{
		pNew = new CTcpEdgePkgFile();
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgCpuKey)
	{
		pNew = new CTcpEdgePkgCfgCpu();
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgMemKey)
	{
		pNew = new CTcpEdgePkgCfgMem();
	}

	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppInstallReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CTCPEDGEPKGFILE)
	{
		pNew = new CTcpEdgePkgFile();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
	{
		pNew = new CTcpEdgePkgCfgCpu();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
	{
		pNew = new CTcpEdgePkgCfgMem();
	}

	return pNew;
}
long CTcpEdgePkgData_AppInstallReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->GetFieldValue(pXmlKeys->m_strPolicyKey, m_strPolicy);
	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->GetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	pRecordset->GetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strEnableKey, m_strEnable);
	return 0;
}

long CTcpEdgePkgData_AppInstallReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->SetFieldValue(pXmlKeys->m_strPolicyKey, m_strPolicy);
	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->SetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	pRecordset->SetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strEnableKey, m_strEnable);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_AppInstallReq::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_JobId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Policy, 0);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Container);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_App);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Version);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Enable);
	CTcpEdgePkgData::AddNewData(pDataset,CTcpEdgePkgCfgCpu::ToDataset() , 0);
	CTcpEdgePkgData::AddNewData(pDataset,CTcpEdgePkgCfgMem::ToDataset() , 0);
	//20230919,lmy修改, File是必需项
	CTcpEdgePkgData::AddNewData(pDataset,CTcpEdgePkgFile::ToDataset());

	return pDataset;
}
