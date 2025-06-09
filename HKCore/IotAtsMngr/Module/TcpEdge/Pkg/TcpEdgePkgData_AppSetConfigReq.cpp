//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_AppSetConfigReq.cpp  CTcpEdgePkgData_AppSetConfigReq


#include "stdafx.h"
#include "TcpEdgePkgData_AppSetConfigReq.h"
#include "TcpEdgePkgCfgCpu.h"
#include "TcpEdgePkgCfgMem.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppSetConfigReq::CTcpEdgePkgData_AppSetConfigReq()
{
	//初始化属性
	m_pTcpEdgePkgCfgCpu = NULL;
	m_pTcpEdgePkgCfgMem = NULL;
	//初始化成员变量
}

CTcpEdgePkgData_AppSetConfigReq::~CTcpEdgePkgData_AppSetConfigReq()
{
}

long CTcpEdgePkgData_AppSetConfigReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCfgCpuKey, oNode, m_strCfgCpu);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCfgMemKey, oNode, m_strCfgMem);
	return 0;
}

long CTcpEdgePkgData_AppSetConfigReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
// 	xml_SetAttributeValue(pXmlKeys->m_strCfgCpuKey, oElement, m_strCfgCpu);
// 	xml_SetAttributeValue(pXmlKeys->m_strCfgMemKey, oElement, m_strCfgMem);
	return 0;
}

long CTcpEdgePkgData_AppSetConfigReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strCfgCpu);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strCfgMem);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
		BinarySerializeRead(oBinaryBuffer, m_strApp);
// 		BinarySerializeRead(oBinaryBuffer, m_strCfgCpu);
// 		BinarySerializeRead(oBinaryBuffer, m_strCfgMem);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
// 		BinarySerializeWrite(oBinaryBuffer, m_strCfgCpu);
// 		BinarySerializeWrite(oBinaryBuffer, m_strCfgMem);
	}
	return 0;
}

void CTcpEdgePkgData_AppSetConfigReq::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
		{
			m_pTcpEdgePkgCfgCpu = (CTcpEdgePkgCfgCpu*)p;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
		{
			m_pTcpEdgePkgCfgMem = (CTcpEdgePkgCfgMem*)p;
		}
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

BOOL CTcpEdgePkgData_AppSetConfigReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppSetConfigReq *p = (CTcpEdgePkgData_AppSetConfigReq*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

// 	if(m_strCfgCpu != p->m_strCfgCpu)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_strCfgMem != p->m_strCfgMem)
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}

BOOL CTcpEdgePkgData_AppSetConfigReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppSetConfigReq *p = (CTcpEdgePkgData_AppSetConfigReq*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strApp = m_strApp;
	//p->m_strCfgCpu = m_strCfgCpu;
	//p->m_strCfgMem = m_strCfgMem;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppSetConfigReq::Clone()
{
	CTcpEdgePkgData_AppSetConfigReq *p = new CTcpEdgePkgData_AppSetConfigReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppSetConfigReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppSetConfigReq *p = new CTcpEdgePkgData_AppSetConfigReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppSetConfigReq::CanPaste(UINT nClassID)
{
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

CExBaseObject* CTcpEdgePkgData_AppSetConfigReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgCpuKey)
	{
		pNew = new CTcpEdgePkgCfgCpu();
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgMemKey)
	{
		pNew = new CTcpEdgePkgCfgMem();
	}

	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppSetConfigReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
	{
		pNew = new CTcpEdgePkgCfgCpu();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
	{
		pNew = new CTcpEdgePkgCfgMem();
	}

	return pNew;
}
long CTcpEdgePkgData_AppSetConfigReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->GetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
// 	pRecordset->GetFieldValue(pXmlKeys->m_strCfgCpuKey, m_strCfgCpu);
// 	pRecordset->GetFieldValue(pXmlKeys->m_strCfgMemKey, m_strCfgMem);
	return 0;
}

long CTcpEdgePkgData_AppSetConfigReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->SetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
// 	pRecordset->SetFieldValue(pXmlKeys->m_strCfgCpuKey, m_strCfgCpu);
// 	pRecordset->SetFieldValue(pXmlKeys->m_strCfgMemKey, m_strCfgMem);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_AppSetConfigReq:: ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Container);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_App);

	CTcpEdgePkgData::AddNewData(pDataset, CTcpEdgePkgCfgCpu::ToDataset(),0);
	CTcpEdgePkgData::AddNewData(pDataset, CTcpEdgePkgCfgMem::ToDataset(),0);


	return pDataset;
}