//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_ConInstallReq.cpp  CTcpEdgePkgData_ConInstallReq


#include "stdafx.h"
#include "TcpEdgePkgData_ConInstallReq.h"
#include "TcpEdgePkgString.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_ConInstallReq::CTcpEdgePkgData_ConInstallReq()
{
	//初始化属性

	//初始化成员变量
	m_pTcpEdgePkgCfgCpu = NULL;
	m_pTcpEdgePkgCfgMem = NULL;
	m_pTcpEdgePkgCfgDisk = NULL;
	m_arrayNotMust[0] = PkgData_Node_CfgCpu;
	m_arrayNotMust[1] = PkgData_Node_CfgMem;
	m_arrayNotMust[2] = PkgData_Node_CfgDisk;
	m_arrayNotMust[3] = PkgData_Node_Port;
	m_arrayNotMust[4] = PkgData_Node_Mount;
	m_arrayNotMust[5] = PkgData_Node_Dev;
}

CTcpEdgePkgData_ConInstallReq::~CTcpEdgePkgData_ConInstallReq()
{
}

long CTcpEdgePkgData_ConInstallReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	
	XmlReadJsonArray(oNode, pXmlRWKeys, PkgData_Node_Port);
	XmlReadJsonArray(oNode, pXmlRWKeys, PkgData_Node_Mount);
	XmlReadJsonArray(oNode, pXmlRWKeys, PkgData_Node_Dev);

	return 0;
}

long CTcpEdgePkgData_ConInstallReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);

	XmlWriteJsonArray(oXMLDoc, oElement, pXmlRWKeys, PkgData_Node_Port);
	XmlWriteJsonArray(oXMLDoc, oElement, pXmlRWKeys, PkgData_Node_Mount);
	XmlWriteJsonArray(oXMLDoc, oElement, pXmlRWKeys, PkgData_Node_Dev);

	return 0;
}

long CTcpEdgePkgData_ConInstallReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
	}
	return 0;
}

void CTcpEdgePkgData_ConInstallReq::InitAfterRead()
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
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGDISK)
		{
			m_pTcpEdgePkgCfgDisk = (CTcpEdgePkgCfgDisk*)p;
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

	if (m_pTcpEdgePkgCfgDisk == NULL)
	{
		m_pTcpEdgePkgCfgDisk = (CTcpEdgePkgCfgDisk*)AddNewChild(new CTcpEdgePkgCfgDisk());
	}

}

BOOL CTcpEdgePkgData_ConInstallReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ConInstallReq *p = (CTcpEdgePkgData_ConInstallReq*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_ConInstallReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ConInstallReq *p = (CTcpEdgePkgData_ConInstallReq*)pDest;

	p->m_strContainer = m_strContainer;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ConInstallReq::Clone()
{
	CTcpEdgePkgData_ConInstallReq *p = new CTcpEdgePkgData_ConInstallReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_ConInstallReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_ConInstallReq *p = new CTcpEdgePkgData_ConInstallReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_ConInstallReq::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGDISK)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ConInstallReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgCpuKey)
	{
		pNew = new CTcpEdgePkgCfgCpu();
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgDiskKey)
	{
		pNew = new CTcpEdgePkgCfgDisk();
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgMemKey)
	{
		pNew = new CTcpEdgePkgCfgMem();
	}

	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ConInstallReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGCPU)
	{
		pNew = new CTcpEdgePkgCfgCpu();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGDISK)
	{
		pNew = new CTcpEdgePkgCfgDisk();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
	{
		pNew = new CTcpEdgePkgCfgMem();
	}

	return pNew;
}
long CTcpEdgePkgData_ConInstallReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	return 0;
}

long CTcpEdgePkgData_ConInstallReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	return 0;
}

long CTcpEdgePkgData_ConInstallReq::XmlReadJsonArray(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys, const char *string)
{
	//取到JSON
	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	//检测JSON报文中是否存在LinkState节点，存在则动态创建LinkState并添加
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, string);
	if(pDatasJson)
	{
		CTcpEdgePkgString* pDatas = new CTcpEdgePkgString;
		pDatas->m_strID = pDatas->m_strName = string;
		AddNewChild(pDatas);

		//遍历Devices，动态创建子结构
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			//字符串数组
			CTcpEdgePkgString* pString = new CTcpEdgePkgString;
			pString->m_strValue = pDatasChild->valuestring;
			pDatas->AddNewChild(pString);
			

			//CPkg_DeviceStatusResp_LinkState* pData = new CPkg_DeviceStatusResp_LinkState;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			//调用子类里的函数来解析数据，如果子类中包含数组，去子类的该函数中做类似处理
			//pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			delete pTempJsonNode;
			//解析完成后作为次级报文添加到pDevices
			//pDatas->AddNewChild(pData);	

			pDatasChild = pDatasChild->next;
		}
	}

	return 0;
}

long CTcpEdgePkgData_ConInstallReq::XmlWriteJsonArray(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys, const char *string)
{
	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	CTcpEdgePkgString* pDatas = (CTcpEdgePkgString*)FindByID(string);
	if(pDatas == NULL)
	{
		return 0;
	}

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while(pos)
	{
		//字符串数组
		CTcpEdgePkgString* pData = (CTcpEdgePkgString*)pDatas->GetNext(pos);
		CJSON* pStringJson = CJSON_CreateString(pData->m_strValue.GetString());
		CJSON_AddItemToArray(pDatasJson,pStringJson);
		
		CJsonNode* pTempJsonNode = new CJsonNode(pStringJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;
	}

// 	if(pDatasJson->child)
// 	{
		CJSON_AddItemToObject(pJson, string, pDatasJson);
//	}

	DeleteByID(string);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_ConInstallReq::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Container);
	CTcpEdgePkgData::AddNewData(pDataset, CTcpEdgePkgCfgCpu::ToDataset(), 0);
	CTcpEdgePkgData::AddNewData(pDataset, CTcpEdgePkgCfgMem::ToDataset(), 0);
	CTcpEdgePkgData::AddNewData(pDataset, CTcpEdgePkgCfgDisk::ToDataset(), 0);
	CTcpEdgePkgData::AddNewDatas(pDataset, PkgData_Node_Port, 0);
	CTcpEdgePkgData::AddNewDatas(pDataset, PkgData_Node_Mount, 0);
	CTcpEdgePkgData::AddNewDatas(pDataset, PkgData_Node_Dev, 0);

	return pDataset;
}