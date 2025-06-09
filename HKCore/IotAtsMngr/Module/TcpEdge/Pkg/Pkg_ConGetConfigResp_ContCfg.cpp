//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ConGetConfigResp_ContCfg.cpp  CPkg_ConGetConfigResp_ContCfg


#include "stdafx.h"
#include "Pkg_ConGetConfigResp_ContCfg.h"
#include "TcpEdgePkgString.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_ConGetConfigResp_ContCfg::CPkg_ConGetConfigResp_ContCfg()
{
	//初始化属性

	//初始化成员变量
	m_pTcpEdgePkgCfgCpu = NULL;
	m_pTcpEdgePkgCfgMem = NULL;
	m_pTcpEdgePkgCfgDisk = NULL;

	m_strObjectName[0] = _T(PkgData_Node_CfgCpu);
	m_strObjectName[1] = _T(PkgData_Node_CfgMem);
	m_strObjectName[2] = _T(PkgData_Node_CfgDisk);

	for(int i = 0; i<3; i++)
	{
		m_bObjectMustExist[i] = FALSE;
	}
}

CPkg_ConGetConfigResp_ContCfg::~CPkg_ConGetConfigResp_ContCfg()
{
}

BOOL CPkg_ConGetConfigResp_ContCfg::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】ConGetConfigResp：[%1]=>[%2$%3]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_ContCfgs).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】ConGetConfigResp：[%1]=>[%2$%3]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_ContCfgs).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}
	return bRet;
}

long CPkg_ConGetConfigResp_ContCfg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);

	XmlReadJsonArray(oNode, pXmlRWKeys, PkgData_Node_Port);
	XmlReadJsonArray(oNode, pXmlRWKeys, PkgData_Node_Mount);
	XmlReadJsonArray(oNode, pXmlRWKeys, PkgData_Node_Dev);
	return 0;
}

long CPkg_ConGetConfigResp_ContCfg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);

	XmlWriteJsonArray(oXMLDoc, oElement, pXmlRWKeys, PkgData_Node_Port);
	XmlWriteJsonArray(oXMLDoc, oElement, pXmlRWKeys, PkgData_Node_Mount);
	XmlWriteJsonArray(oXMLDoc, oElement, pXmlRWKeys, PkgData_Node_Dev);
	return 0;
}

long CPkg_ConGetConfigResp_ContCfg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
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

void CPkg_ConGetConfigResp_ContCfg::InitAfterRead()
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
			m_strErrorInfo += m_pTcpEdgePkgCfgCpu->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgCfgCpu->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgCfgCpu->m_strNecessityErr;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGMEM)
		{
			m_pTcpEdgePkgCfgMem = (CTcpEdgePkgCfgMem*)p;
			m_strErrorInfo += m_pTcpEdgePkgCfgMem->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgCfgMem->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgCfgMem->m_strNecessityErr;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCFGDISK)
		{
			m_pTcpEdgePkgCfgDisk = (CTcpEdgePkgCfgDisk*)p;
			m_strErrorInfo += m_pTcpEdgePkgCfgDisk->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgCfgDisk->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgCfgDisk->m_strNecessityErr;
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

	QString strTemp;
	CString strID(GetXmlElementKey());
	for(int i=0; i<3; i++)
	{
		if(! m_bObjectMustExist[i])
		{
			strTemp = QString("【错误】【必需项缺失】ConGetConfigResp：[%1]=>[%2]必需字段object缺失;\n").arg(PkgData_Node_Data).arg(m_strObjectName[i]);
			m_strErrorInfo += strTemp;
			m_strNecessityLack += strTemp;
		}
	}
}

BOOL CPkg_ConGetConfigResp_ContCfg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ConGetConfigResp_ContCfg *p = (CPkg_ConGetConfigResp_ContCfg*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_ConGetConfigResp_ContCfg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ConGetConfigResp_ContCfg *p = (CPkg_ConGetConfigResp_ContCfg*)pDest;

	p->m_strContainer = m_strContainer;
	return TRUE;
}

CBaseObject* CPkg_ConGetConfigResp_ContCfg::Clone()
{
	CPkg_ConGetConfigResp_ContCfg *p = new CPkg_ConGetConfigResp_ContCfg();
	Copy(p);
	return p;
}

CBaseObject* CPkg_ConGetConfigResp_ContCfg::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_ConGetConfigResp_ContCfg *p = new CPkg_ConGetConfigResp_ContCfg();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_ConGetConfigResp_ContCfg::CanPaste(UINT nClassID)
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

CExBaseObject* CPkg_ConGetConfigResp_ContCfg::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgCpuKey)
	{
		pNew = new CTcpEdgePkgCfgCpu();
		pNew->m_strID = _T("ConGetConfigResp");
		m_bObjectMustExist[0] = TRUE;
		pNew->m_strName = PkgData_Node_ContCfgs;
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgDiskKey)
	{
		pNew = new CTcpEdgePkgCfgDisk();
		pNew->m_strID = _T("ConGetConfigResp");
		m_bObjectMustExist[1] = TRUE;

	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgCfgMemKey)
	{
		pNew = new CTcpEdgePkgCfgMem();
		pNew->m_strID = _T("ConGetConfigResp");
		m_bObjectMustExist[2] = TRUE;
		pNew->m_strName = PkgData_Node_ContCfgs;
	}

	return pNew;
}

CExBaseObject* CPkg_ConGetConfigResp_ContCfg::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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

long CPkg_ConGetConfigResp_ContCfg::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);

	return 0;
}

long CPkg_ConGetConfigResp_ContCfg::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);

	return 0;
}

long CPkg_ConGetConfigResp_ContCfg::XmlReadJsonArray(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys, const char *string)
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

long CPkg_ConGetConfigResp_ContCfg::XmlWriteJsonArray(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys, const char *string)
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

		//CJSON_AddItemToArray(pDatasJson, pStringJson);
	}

	CJSON_AddItemToObject(pJson, string, pDatasJson);

	DeleteByID(string);
	return 0;
}