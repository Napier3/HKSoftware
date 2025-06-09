//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_DeviceInfoResp.cpp  CTcpEdgePkgData_DeviceInfoResp


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceInfoResp.h"
#include "TcpEdgePkgData_DeviceInfoResp_Links.h"
#include "TcpEdgePkgData_DeviceInfoResp_Link.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceInfoResp::CTcpEdgePkgData_DeviceInfoResp()
{
	//初始化属性

	//初始化成员变量
	m_pTcpEdgePkgDev = NULL;
	m_pTcpEdgePkgCpu = NULL;
	m_pTcpEdgePkgMem = NULL;
	m_pTcpEdgePkgDisk = NULL;
	m_pTcpEdgePkgTemperature = NULL;
	m_pTcpEdgePkgOs = NULL;

	m_strObjectName[0] = _T(PkgData_Node_Dev);
	m_strObjectName[1] = _T(PkgData_Node_Cpu);
	m_strObjectName[2] = _T(PkgData_Node_Mem);
	m_strObjectName[3] = _T(PkgData_Node_Disk);
	m_strObjectName[4] = _T(PkgData_Node_Os);

	for(int i = 0; i<5; i++)
	{
		m_bObjectMustExist[i] = FALSE;
	}

}

CTcpEdgePkgData_DeviceInfoResp::~CTcpEdgePkgData_DeviceInfoResp()
{
}

long CTcpEdgePkgData_DeviceInfoResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);   //会自动生成name和id，不需要故注释
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CString strTemp;
	CString strID(GetXmlElementKey());

	//取到JSON
	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}
	

	//检测JSON报文中是否存在Links节点，存在则动态创建Links并添加
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Links);
	if(pDatasJson)
	{
		CTcpEdgePkgData_DeviceInfoResp_Links* pDatas = new CTcpEdgePkgData_DeviceInfoResp_Links;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Links;
		AddNewChild(pDatas);

		//遍历Devices，动态创建子结构
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{

			CTcpEdgePkgData_DeviceInfoResp_Link* pData = new CTcpEdgePkgData_DeviceInfoResp_Link;

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

	return 0;
}

long CTcpEdgePkgData_DeviceInfoResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	if(pJson == NULL)
	{
		return 0;
	}

	CTcpEdgePkgData_DeviceInfoResp_Links* pDatas = (CTcpEdgePkgData_DeviceInfoResp_Links*)FindByID(PkgData_Node_Links);
	if(pDatas == NULL)
	{
		return 0;
	}

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while(pos)
	{
		CTcpEdgePkgData_DeviceInfoResp_Link* pData = (CTcpEdgePkgData_DeviceInfoResp_Link*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_Links, pDatasJson);

	DeleteByID(PkgData_Node_Links);

	return 0;
}

long CTcpEdgePkgData_DeviceInfoResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CTcpEdgePkgData_DeviceInfoResp::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CTCPEDGEPKGDEV)
		{
			m_pTcpEdgePkgDev = (CTcpEdgePkgDev*)p;
			m_strErrorInfo += m_pTcpEdgePkgDev->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgDev->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgDev->m_strNecessityErr;
			m_strRangeOut += m_pTcpEdgePkgDev->m_strRangeOut;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCPU)
		{
			m_pTcpEdgePkgCpu = (CTcpEdgePkgCpu*)p;
			m_strErrorInfo += m_pTcpEdgePkgCpu->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgCpu->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgCpu->m_strNecessityErr;
			m_strRangeOut += m_pTcpEdgePkgCpu->m_strRangeOut;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGMEM)
		{
			m_pTcpEdgePkgMem = (CTcpEdgePkgMem*)p;
			m_strErrorInfo += m_pTcpEdgePkgMem->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgMem->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgMem->m_strNecessityErr;
			m_strRangeOut += m_pTcpEdgePkgMem->m_strRangeOut;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGDISK)
		{
			m_pTcpEdgePkgDisk = (CTcpEdgePkgDisk*)p;
			m_strErrorInfo += m_pTcpEdgePkgDisk->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgDisk->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgDisk->m_strNecessityErr;
			m_strRangeOut += m_pTcpEdgePkgDisk->m_strRangeOut;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGTEMPERATURE)
		{
			m_pTcpEdgePkgTemperature = (CTcpEdgePkgTemperature*)p;
			m_strErrorInfo += m_pTcpEdgePkgTemperature->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgTemperature->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgTemperature->m_strNecessityErr;
			m_strRangeOut += m_pTcpEdgePkgTemperature->m_strRangeOut;
		}
		else if (nClassID == MNGRCLASSID_CTCPEDGEPKGOS)
		{
			m_pTcpEdgePkgOs = (CTcpEdgePkgOs*)p;
			m_strErrorInfo += m_pTcpEdgePkgOs->m_strErrorInfo;
			m_strNecessityLack += m_pTcpEdgePkgOs->m_strNecessityLack;
			m_strNecessityErr += m_pTcpEdgePkgOs->m_strNecessityErr;
			m_strRangeOut += m_pTcpEdgePkgOs->m_strRangeOut;
		}
	}

	if (m_pTcpEdgePkgDev == NULL)
	{
		m_pTcpEdgePkgDev = (CTcpEdgePkgDev*)AddNewChild(new CTcpEdgePkgDev());
	}

	if (m_pTcpEdgePkgCpu == NULL)
	{
		m_pTcpEdgePkgCpu = (CTcpEdgePkgCpu*)AddNewChild(new CTcpEdgePkgCpu());
	}

	if (m_pTcpEdgePkgMem == NULL)
	{
		m_pTcpEdgePkgMem = (CTcpEdgePkgMem*)AddNewChild(new CTcpEdgePkgMem());
	}

	if (m_pTcpEdgePkgDisk == NULL)
	{
		m_pTcpEdgePkgDisk = (CTcpEdgePkgDisk*)AddNewChild(new CTcpEdgePkgDisk());
	}

	if (m_pTcpEdgePkgTemperature == NULL)
	{
		m_pTcpEdgePkgTemperature = (CTcpEdgePkgTemperature*)AddNewChild(new CTcpEdgePkgTemperature());
	}

	if (m_pTcpEdgePkgOs == NULL)
	{
		m_pTcpEdgePkgOs = (CTcpEdgePkgOs*)AddNewChild(new CTcpEdgePkgOs());
	}

	QString strTemp;
	CString strID(GetXmlElementKey());
	for(int i=0; i<5; i++)
	{
		if(! m_bObjectMustExist[i])
		{
			strTemp = QString("【错误】【必需项缺失】DeviceInfoResp：[%1]=>[%2]必需字段object缺失;\n").arg(strID).arg(m_strObjectName[i]);
			m_strErrorInfo += strTemp;
			m_strNecessityLack += strTemp;
		}
	}

}

BOOL CTcpEdgePkgData_DeviceInfoResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceInfoResp *p = (CTcpEdgePkgData_DeviceInfoResp*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_DeviceInfoResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceInfoResp *p = (CTcpEdgePkgData_DeviceInfoResp*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceInfoResp::Clone()
{
	CTcpEdgePkgData_DeviceInfoResp *p = new CTcpEdgePkgData_DeviceInfoResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceInfoResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceInfoResp *p = new CTcpEdgePkgData_DeviceInfoResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceInfoResp::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CTCPEDGEPKGDEV)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGCPU)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGMEM)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGDISK)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGTEMPERATURE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CTCPEDGEPKGOS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceInfoResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTcpEdgePkgDevKey)
	{
		pNew = new CTcpEdgePkgDev();
		pNew->m_strID = _T("DeviceInfoResp");
		m_bObjectMustExist[0] = TRUE;
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgCpuKey)
	{
		pNew = new CTcpEdgePkgCpu();
		pNew->m_strID = _T("DeviceInfoResp");
		m_bObjectMustExist[1] = TRUE;
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgMemKey)
	{
		pNew = new CTcpEdgePkgMem();
		pNew->m_strID = _T("DeviceInfoResp");
		m_bObjectMustExist[2] = TRUE;
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgDiskKey)
	{
		pNew = new CTcpEdgePkgDisk();
		pNew->m_strID = _T("DeviceInfoResp");
		m_bObjectMustExist[3] = TRUE;
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgTemperatureKey)
	{
		pNew = new CTcpEdgePkgTemperature();
		pNew->m_strID = _T("DeviceInfoResp");
	}
	else if (strClassID == pXmlKeys->m_strCTcpEdgePkgOsKey)
	{
		pNew = new CTcpEdgePkgOs();
		pNew->m_strID = _T("DeviceInfoResp");
		m_bObjectMustExist[4] = TRUE;
	}

	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceInfoResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CTCPEDGEPKGDEV)
	{
		pNew = new CTcpEdgePkgDev();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGCPU)
	{
		pNew = new CTcpEdgePkgCpu();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGMEM)
	{
		pNew = new CTcpEdgePkgMem();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGDISK)
	{
		pNew = new CTcpEdgePkgDisk();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGTEMPERATURE)
	{
		pNew = new CTcpEdgePkgTemperature();
	}
	else if (nClassID == MNGRCLASSID_CTCPEDGEPKGOS)
	{
		pNew = new CTcpEdgePkgOs();
	}

	return pNew;
}
