//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MmsEngineConfig.cpp  CMmsEngineConfig


#include "stdafx.h"
#include "MmsEngineConfig.h"
#include "../../../Module/API/GlobalConfigApi.h"

CMmsEngineConfig::CMmsEngineConfig()
{
	//初始化属性

	//初始化成员变量
	m_nDebugMode = 0;
	m_nExitAppForException = 0;
	m_nEnumLDAfterReadXml = 0;
	m_nMmsEnumLogCtrl = 0;
	m_nUseDvmMapFile = 1;
	m_nSwitchSGWait = 0;
	m_bMultDevModel = 0;
	m_nUseDsDout = 0;
	m_nAutoGenModelDatas = 0;
}

CMmsEngineConfig::~CMmsEngineConfig()
{
}

long CMmsEngineConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMmsEngineConfigXmlRWKeys *pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDebugModeKey, oNode, m_nDebugMode);
	xml_GetAttibuteValue(pXmlKeys->m_strEnumLDAfterReadXmlKey, oNode, m_nEnumLDAfterReadXml);
	xml_GetAttibuteValue(pXmlKeys->m_strMmsEnumLogCtrKey, oNode, m_nMmsEnumLogCtrl);
	xml_GetAttibuteValue(pXmlKeys->m_strExitAppForExceptionKey, oNode, m_nExitAppForException);
	xml_GetAttibuteValue(pXmlKeys->m_strUseDvmMapFileKey, oNode, m_nUseDvmMapFile);
	xml_GetAttibuteValue(pXmlKeys->m_strSwitchSGWaitKey, oNode, m_nSwitchSGWait);
	xml_GetAttibuteValue(pXmlKeys->m_strMultDevModelKey, oNode, m_bMultDevModel);
	xml_GetAttibuteValue(pXmlKeys->m_strExportModelAutoKey, oNode, m_nExportModelAuto);
	xml_GetAttibuteValue(pXmlKeys->m_strUseDsDoutKey, oNode, m_nUseDsDout);
	xml_GetAttibuteValue(pXmlKeys->m_strAutoGenModelDatasKey, oNode, m_nAutoGenModelDatas);

	return 0;
}

long CMmsEngineConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMmsEngineConfigXmlRWKeys *pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDebugModeKey, oElement, m_nDebugMode);
	xml_SetAttributeValue(pXmlKeys->m_strEnumLDAfterReadXmlKey, oElement, m_nEnumLDAfterReadXml);
	xml_SetAttributeValue(pXmlKeys->m_strMmsEnumLogCtrKey, oElement, m_nMmsEnumLogCtrl);
	xml_SetAttributeValue(pXmlKeys->m_strExitAppForExceptionKey, oElement, m_nExitAppForException);
	xml_SetAttributeValue(pXmlKeys->m_strUseDvmMapFileKey, oElement, m_nUseDvmMapFile);
	xml_SetAttributeValue(pXmlKeys->m_strSwitchSGWaitKey, oElement, m_nSwitchSGWait);
	xml_SetAttributeValue(pXmlKeys->m_strMultDevModelKey, oElement, m_bMultDevModel);
	xml_SetAttributeValue(pXmlKeys->m_strExportModelAutoKey, oElement, m_nExportModelAuto);
	xml_SetAttributeValue(pXmlKeys->m_strUseDsDoutKey, oElement, m_nUseDsDout);
	xml_SetAttributeValue(pXmlKeys->m_strAutoGenModelDatasKey, oElement, m_nAutoGenModelDatas);

	return 0;
}

CBaseObject* CMmsEngineConfig::Clone()
{
	CMmsEngineConfig *p = new CMmsEngineConfig();
	Copy(p);
	return p;
}

BOOL CMmsEngineConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMmsEngineConfig *p = (CMmsEngineConfig*)pDest;

	return TRUE;
}

BOOL CMmsEngineConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMmsEngineConfig *p = (CMmsEngineConfig*)pObj;

	return TRUE;
}

CExBaseObject* CMmsEngineConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMmsEngineConfigXmlRWKeys *pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMmsDatasetsKey)
	{
		pNew = new CMmsEngineDatasets();
	}

	return pNew;
}

CExBaseObject* CMmsEngineConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == MSCFGCLASSID_CMMSENGINEDATASETS)
	{
		pNew = new CMmsEngineDatasets();
	}

	return pNew;
}

CString CMmsEngineConfig::GetMmsEngineConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("mms-engine-config.xml");
	return strFile;
}

void CMmsEngineConfig::ReadMmsEngineConfig()
{
	CString strFile;
	strFile = GetMmsEngineConfigFile();
	OpenXmlFile(strFile, CMmsEngineConfigXmlRWKeys::CMmsEngineConfigKey(), CMmsEngineConfigXmlRWKeys::g_pXmlKeys);
}

void CMmsEngineConfig::SaveMmsEngineConfig()
{
	CString strFile;
	strFile = GetMmsEngineConfigFile();
	SaveXmlFile(strFile, CMmsEngineConfigXmlRWKeys::g_pXmlKeys);
}

BOOL CMmsEngineConfig::IsDatasetUse(const CString &strDsName)
{
	BOOL nRet = FALSE;

	CMmsEngineDatasets *pMmsDatasets = GetMmsDatasetsCfg();

	if (pMmsDatasets != NULL)
	{
		nRet = pMmsDatasets->IsDatasetUse(strDsName);
	}

	return nRet;
}

BOOL CMmsEngineConfig::IsDatasetUse(const char *pDsName)
{
	return IsDatasetUse(CString(pDsName));
}

char* CMmsEngineConfig::mms_GetDatasetKey(const CString &strDatasetID)
{
	const char *pString = NULL;
	CMmsEngineDatasets *pMmsDatasets = GetMmsDatasetsCfg();

	if (pMmsDatasets != NULL)
	{
		pString = pMmsDatasets->mms_GetDatasetKey(strDatasetID);
	}

	return (char*)pString;
}

CMmsEngineDatasets* CMmsEngineConfig::GetMmsDatasetsCfg()
{
	CMmsEngineDatasets *pMmsDatasets = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == MSCFGCLASSID_CMMSENGINEDATASETS)
		{
			pMmsDatasets = ((CMmsEngineDatasets*)p);
			break;
		}
	}

	return pMmsDatasets;
}
