//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeParam.cpp  CEdgeParam


#include "stdafx.h"
#include "EdgeParam.h"
#include "EdgeGlobalDef.h"

#include "EdgeLinkState.h"
#include "EdgeDeviceInfos.h"
#include "EdgeDeviceStatuses.h"
#include "EdgeContStatus.h"
#include "EdgeApps.h"
#include "EdgeData.h"
#include "EdgeContPara.h"
#include "EdgeAppCfgs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeParam::CEdgeParam()
{
	//初始化属性

	//初始化成员变量
	m_pEdgeParas = NULL;
	m_pEdgeCpu = NULL;
	m_pEdgeCpuLmt = NULL;
	m_pEdgeDev = NULL;
	m_pEdgeDisk = NULL;
	m_pEdgeDiskLmt = NULL;
	m_pEdgeFile = NULL;
	m_pEdgeImage = NULL;
	m_pEdgeMem = NULL;
	m_pEdgeMemLmt = NULL;
	m_pEdgeMemUsed = NULL;
	m_pEdgeOs = NULL;
	m_pEdgeRepPeriod = NULL;
	m_pEdgeTemperature = NULL;
	m_pEdgeWithApp = NULL;
	m_pEdgeCfgCpu = NULL;
	m_pEdgeCfgMem = NULL;
	m_pEdgeCfgDisk = NULL;

	m_pDeviceIdsJson = NULL;
	m_pMountJson = NULL;
	m_pDevJson = NULL;
	m_pDeviceDataJson = NULL;
	m_pContParaJson = NULL;
	m_pLinksJson = NULL;
	m_pAppsJson = NULL;
	m_pLinkStateJson = NULL;
	m_pContStatusJson =NULL;
	m_pAppCfgsJson = NULL;
	m_pDeviceInfosJson = NULL;
}

CEdgeParam::~CEdgeParam()
{
	CJSON_Delete(m_pDeviceIdsJson);
	CJSON_Delete(m_pMountJson);
	CJSON_Delete(m_pDevJson);
	CJSON_Delete(m_pDeviceDataJson);
	CJSON_Delete(m_pLinksJson);
	CJSON_Delete(m_pLinkStateJson);
	CJSON_Delete(m_pContParaJson);
	CJSON_Delete(m_pAppsJson);
	CJSON_Delete(m_pContStatusJson);
	CJSON_Delete(m_pAppCfgsJson);
	CJSON_Delete(m_pDeviceInfosJson);
}

long CEdgeParam::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CEdgeParaDatas::XmlReadOwn(oNode, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	if(oNode.GetXmlRWType() != _JSON_TYPE_)
		return 0;

	CJsonNode *pJsonNode = (CJsonNode *)(&oNode);
	CJSON *pNode = pJsonNode->m_pJsonNode;
	CJSON *pChild = pNode->child;
	CString strValue = _T(""),strID = _T("");

	while(pChild != NULL)
	{
		if (pChild->type == CJSON_Object)
		{
			pChild = pChild->next;
			continue;
		}

		strID = pChild->string;

		if (pChild->type == CJSON_False || pChild->type == CJSON_True)
		{
			strValue.Format(_T("%d"),pChild->valueint);
			AddNewData(strID,strID,EDGE_DATATYPE_LONG,strValue);
		}
		else if (pChild->type == CJSON_Number)
		{
			if (pChild->numType == CJSON_Double)
			{
				strValue.Format(_T("%.3f"),pChild->valuedouble);
				AddNewData(strID,strID,EDGE_DATATYPE_DOUBLE,strValue);
			}
			else
			{
				strValue.Format(_T("%d"),pChild->valueint);
				AddNewData(strID,strID,EDGE_DATATYPE_LONG,strValue);
			}
		}
		else if (pChild->type == CJSON_String)
		{
			strValue = pChild->valuestring;
			AddNewData(strID,strID,EDGE_DATATYPE_STRING,strValue);
		}
		else if (pChild->type == CJSON_Array)
		{
			if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_deviceIds) == 0)
			{
				m_pDeviceIdsJson = CJSON_Duplicate(pChild, TRUE);
			}
			else if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_dev) == 0)
			{
				m_pDevJson = CJSON_Duplicate(pChild, TRUE);
			}
			else if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_mount) == 0)
			{
				m_pMountJson = CJSON_Duplicate(pChild, TRUE);
			}
			else if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_links) == 0)
			{
				m_pLinksJson = CJSON_Duplicate(pChild, TRUE);
			}
			else if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_linkState) == 0)
			{
				m_pLinkStateJson = CJSON_Duplicate(pChild, TRUE);
			}
			else if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_contPara) == 0)
			{
				m_pContParaJson = CJSON_Duplicate(pChild, TRUE);
			}
			else if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_apps) == 0)
			{
				m_pAppsJson = CJSON_Duplicate(pChild, TRUE);
			}		
			else if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_contStatus) == 0)
			{
				m_pContStatusJson = CJSON_Duplicate(pChild, TRUE);
			}		
			else if (strcmp(pChild->string, EDGE_PROCEDURE_VAR_appCfgs) == 0)
			{
				m_pAppCfgsJson = CJSON_Duplicate(pChild, TRUE);
			}
			else if (strcmp(pChild->string, EDGE_PROCEDURE_VAR_deviceInfos) == 0)
			{
				m_pDeviceInfosJson = CJSON_Duplicate(pChild, TRUE);
			}
		}
		CheckIsError(pChild);

		pChild = pChild->next;
	}

	return 0;
}

long CEdgeParam::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeParaDatas::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;
	return 0;
}

long CEdgeParam::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEdgeParaDatas::SerializeOwn(oBinaryBuffer);
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

void CEdgeParam::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EDGECMDCLASSID_CEDGEPARAS)
		{
			m_pEdgeParas = (CEdgeParas*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGECPU)
		{
			m_pEdgeCpu = (CEdgeCpu*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGECPULMT)
		{
			m_pEdgeCpuLmt = (CEdgeCpuLmt*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEDEV)
		{
			m_pEdgeDev = (CEdgeDev*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEDISK)
		{
			m_pEdgeDisk = (CEdgeDisk*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEDISKLMT)
		{
			m_pEdgeDiskLmt = (CEdgeDiskLmt*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEFILE)
		{
			m_pEdgeFile = (CEdgeFile*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEIMAGE)
		{
			m_pEdgeImage = (CEdgeImage*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEMEM)
		{
			m_pEdgeMem = (CEdgeMem*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEMEMLMT)
		{
			m_pEdgeMemLmt = (CEdgeMemLmt*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEMEMUSED)
		{
			m_pEdgeMemUsed = (CEdgeMemUsed*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEOS)
		{
			m_pEdgeOs = (CEdgeOs*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEREPPERIOD)
		{
			m_pEdgeRepPeriod = (CEdgeRepPeriod*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGETEMPERATURE)
		{
			m_pEdgeTemperature = (CEdgeTemperature*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEWITHAPP)
		{
			m_pEdgeWithApp = (CEdgeWithApp*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGECFGCPU)
		{
			m_pEdgeCfgCpu = (CEdgeCfgCpu*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGECFGMEM)
		{
			m_pEdgeCfgMem = (CEdgeCfgMem*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGECFGDISK)
		{
			m_pEdgeCfgDisk = (CEdgeCfgDisk*)p;
		}
	}
}

BOOL CEdgeParam::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEdgeParaDatas::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEdgeParam *p = (CEdgeParam*)pObj;

	return TRUE;
}

BOOL CEdgeParam::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeParaDatas::CopyOwn(pDest);

	CEdgeParam *p = (CEdgeParam*)pDest;

	return TRUE;
}

CBaseObject* CEdgeParam::Clone()
{
	CEdgeParam *p = new CEdgeParam();
	Copy(p);
	return p;
}

CBaseObject* CEdgeParam::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeParam *p = new CEdgeParam();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeParam::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGEPARAS)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEDEV)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGECPU)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEMEM)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEDISK)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEOS)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGELINKS)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEMEMUSED)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGETEMPERATURE)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEREPPERIOD)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEFILE)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEIMAGE)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEWITHAPP)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGECPULMT)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEMEMLMT)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEDISKLMT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeParam::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeParasKey)
	{
		pNew = new CEdgeParas();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDevKey)
	{
		pNew = new CEdgeDev();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeCpuKey)
	{
		pNew = new CEdgeCpu();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeMemKey)
	{
		pNew = new CEdgeMem();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDiskKey)
	{
		pNew = new CEdgeDisk();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeOsKey)
	{
		pNew = new CEdgeOs();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeMemUsedKey)
	{
		pNew = new CEdgeMemUsed();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeTemperatureKey)
	{
		pNew = new CEdgeTemperature();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeRepPeriodKey)
	{
		pNew = new CEdgeRepPeriod();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeFileKey)
	{
		pNew = new CEdgeFile();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeImageKey)
	{
		pNew = new CEdgeImage();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeWithAppKey)
	{
		pNew = new CEdgeWithApp();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeCpuLmtKey)
	{
		pNew = new CEdgeCpuLmt();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeMemLmtKey)
	{
		pNew = new CEdgeMemLmt();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDiskLmtKey)
	{
		pNew = new CEdgeDiskLmt();
	}
	else if(strClassID == pXmlKeys->m_strCEdgeDeviceInfosKey)
	{
		pNew = new CEdgeDeviceInfos();
	}
	else if(strClassID == pXmlKeys->m_strCEdgeDeviceStatusesKey)
	{
		pNew = new CEdgeDeviceStatuses();
	}
	else if(strClassID == pXmlKeys->m_strCEdgeContStatusKey)
	{
		pNew = new CEdgeContStatus();
	}
	else if(strClassID == pXmlKeys->m_strCEdgeAppsKey)
	{
		pNew = new CEdgeApps();
	}
	else if(strClassID == pXmlKeys->m_strCEdgeDataKey)
	{
		pNew = new CEdgeData();
	}
	else if(strClassID == pXmlKeys->m_strCEdgeContParaKey)
	{
		pNew = new CEdgeContPara();
	}
	else if(strClassID == pXmlKeys->m_strCEdgeAppCfgsKey)
	{
		pNew = new CEdgeAppCfgs();
	}

	return pNew;
}

CExBaseObject* CEdgeParam::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGEPARAS)
	{
		pNew = new CEdgeParas();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEDEV)
	{
		pNew = new CEdgeDev();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGECPU)
	{
		pNew = new CEdgeCpu();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEMEM)
	{
		pNew = new CEdgeMem();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEDISK)
	{
		pNew = new CEdgeDisk();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEOS)
	{
		pNew = new CEdgeOs();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEMEMUSED)
	{
		pNew = new CEdgeMemUsed();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGETEMPERATURE)
	{
		pNew = new CEdgeTemperature();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEREPPERIOD)
	{
		pNew = new CEdgeRepPeriod();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEFILE)
	{
		pNew = new CEdgeFile();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEIMAGE)
	{
		pNew = new CEdgeImage();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEWITHAPP)
	{
		pNew = new CEdgeWithApp();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGECPULMT)
	{
		pNew = new CEdgeCpuLmt();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEMEMLMT)
	{
		pNew = new CEdgeMemLmt();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEDISKLMT)
	{
		pNew = new CEdgeDiskLmt();
	}

	return pNew;
}
