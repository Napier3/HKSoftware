//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpEngineConfig.cpp  CPpEngineConfig


#include "stdafx.h"
#include "PpEngineConfig.h"
#include "../PpEngineBaseApp.h"
#include "../../../../Module/API/GlobalConfigApi.h"

CPpEngineConfig::CPpEngineConfig()
{
	CPpEngineConfigXmlRWKeys::Create();
	//初始化属性

	//初始化成员变量
	m_nDebugMode = 0;
	m_nLogPkg = 0;
	m_nLogDataBind = 0;
	m_nLogPkgInfor = 0;
    m_nLogDebugInfor = 1;
	m_nNoChangeWhenSame = 1;

	ReadPpEngineConfig();
}

CPpEngineConfig::~CPpEngineConfig()
{
	CPpEngineConfigXmlRWKeys::Release();
}

long CPpEngineConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPpEngineConfigXmlRWKeys *pXmlKeys = (CPpEngineConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDebugModeKey, oNode, m_nDebugMode);
	xml_GetAttibuteValue(pXmlKeys->m_strLogDataBindKey, oNode, m_nLogDataBind);
	xml_GetAttibuteValue(pXmlKeys->m_strPkgDataInforKey, oNode, m_nLogPkgInfor);
	xml_GetAttibuteValue(pXmlKeys->m_strLogPkgKey, oNode, m_nLogPkg);
	xml_GetAttibuteValue(pXmlKeys->m_strLogDebugInforKey, oNode, m_nLogDebugInfor);
	xml_GetAttibuteValue(pXmlKeys->m_strNoChangeWhenSameKey, oNode, m_nNoChangeWhenSame);
	xml_GetAttibuteValue(pXmlKeys->m_strOnlyWriteLogFileKey, oNode, g_bOnlyWriteLogFile);

	return 0;
}

long CPpEngineConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPpEngineConfigXmlRWKeys *pXmlKeys = (CPpEngineConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDebugModeKey, oElement, m_nDebugMode);
	xml_SetAttributeValue(pXmlKeys->m_strLogDataBindKey, oElement, m_nLogDataBind);
	xml_SetAttributeValue(pXmlKeys->m_strPkgDataInforKey, oElement, m_nLogPkgInfor);
	xml_SetAttributeValue(pXmlKeys->m_strLogPkgKey, oElement, m_nLogPkg);
	xml_SetAttributeValue(pXmlKeys->m_strLogDebugInforKey, oElement, m_nLogDebugInfor);
	xml_SetAttributeValue(pXmlKeys->m_strNoChangeWhenSameKey, oElement, m_nNoChangeWhenSame);
	xml_SetAttributeValue(pXmlKeys->m_strOnlyWriteLogFileKey, oElement, g_bOnlyWriteLogFile);

	return 0;
}

CBaseObject* CPpEngineConfig::Clone()
{
	CPpEngineConfig *p = new CPpEngineConfig();
	Copy(p);
	return p;
}

BOOL CPpEngineConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPpEngineConfig *p = (CPpEngineConfig*)pDest;

	return TRUE;
}

BOOL CPpEngineConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPpEngineConfig *p = (CPpEngineConfig*)pObj;

	return TRUE;
}

CExBaseObject* CPpEngineConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPpEngineConfigXmlRWKeys *pXmlKeys = (CPpEngineConfigXmlRWKeys*)pXmlRWKeys;

	return pNew;
}

CExBaseObject* CPpEngineConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	return pNew;
}

CString CPpEngineConfig::GetPpEngineConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("pp-engine-config.xml");
	return strFile;
}

void CPpEngineConfig::ReadPpEngineConfig()
{
	CString strFile;
	strFile = GetPpEngineConfigFile();
	OpenXmlFile(strFile, CPpEngineConfigXmlRWKeys::CPpEngineConfigKey(), CPpEngineConfigXmlRWKeys::g_pPpEngineCfgXmlKeys);
}

void CPpEngineConfig::SavePpEngineConfig()
{
	m_nLogDataBind = g_bLogBindQueryErrorInfor;
	m_nLogPkgInfor = g_bLogPackageInfor;
	m_nLogDebugInfor = g_bLogEngineDebugInfor;

	m_nLogPkg =g_pTheEngineApp->GetProtocolSpy();
	m_nDebugMode = g_pTheEngineApp->m_bDebugMode;

	CString strFile;
	strFile = GetPpEngineConfigFile();
	SaveXmlFile(strFile, CPpEngineConfigXmlRWKeys::g_pPpEngineCfgXmlKeys);
}

void CPpEngineConfig::InitAfterRead()
{
	g_bLogBindQueryErrorInfor = m_nLogDataBind;
	g_bLogPackageInfor = m_nLogPkgInfor;
	g_bLogEngineDebugInfor = m_nLogDebugInfor;

	g_pTheEngineApp->SetProtocolSpy(m_nLogPkg);
	g_pTheEngineApp->m_bDebugMode = m_nDebugMode;
}

