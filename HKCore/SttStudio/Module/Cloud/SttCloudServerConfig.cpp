#include "stdafx.h"
#include "SttCloudServerConfig.h"
#include "../../../Module/API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BSTR CSttCloudServerConfig::m_strServerConfigKey = L"stt-cloud-server";
BSTR CSttCloudServerConfig::m_strIPKey = L"ip";
BSTR CSttCloudServerConfig::m_strPortKey = L"port";
BSTR CSttCloudServerConfig::m_strRemoteCtrlHisRootKey = L"remotectrlhis-root";
BSTR CSttCloudServerConfig::m_strMysqlPortKey = L"mysql-port";
BSTR CSttCloudServerConfig::m_strMaxClientCountKey = L"max-client-count";
	
CSttCloudServerConfig* CSttCloudServerConfig::g_pSttCloudServerConfig = NULL;
long CSttCloudServerConfig::g_nSttCloudServerConfigRef = 0;

CSttCloudServerConfig* CSttCloudServerConfig::Create()
{
	g_nSttCloudServerConfigRef++;

	if (g_nSttCloudServerConfigRef == 1)
	{
		g_pSttCloudServerConfig = new CSttCloudServerConfig();

		if (!g_pSttCloudServerConfig->Open())
		{
			g_pSttCloudServerConfig->Save();
		}
	}

	return g_pSttCloudServerConfig;
}

void CSttCloudServerConfig::Release()
{
	g_nSttCloudServerConfigRef--;

	if (g_nSttCloudServerConfigRef == 0)
	{
		delete g_pSttCloudServerConfig;
		g_pSttCloudServerConfig = NULL;
	}
}

CSttCloudServerConfig::CSttCloudServerConfig()
{
	m_strIP = _T("192.168.1.70");
	m_nPort = 9998;

	m_strRemoteCtrlHisRoot = (CString)_P_GetTemplatePath();

	m_nMysqlPort = 3306;
	m_nMaxClientCount = 5;
}

CSttCloudServerConfig::~CSttCloudServerConfig()
{
	
}

long CSttCloudServerConfig::Open()
{
	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += _T("SttCloudServerConfig.xml");

	return OpenXmlFile(m_strFile, m_strServerConfigKey, NULL);
}

long CSttCloudServerConfig::Save()
{
	ClearFileReadOnlyAttr(m_strFile);
	SaveXmlFile(m_strFile, NULL);
		
	return 1;
}

long CSttCloudServerConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetElementText(m_strPortKey, oNode, m_nPort);
	xml_GetElementText(m_strIPKey, oNode, m_strIP);
	xml_GetElementText(m_strRemoteCtrlHisRootKey, oNode, m_strRemoteCtrlHisRoot);
	xml_GetElementText(m_strMysqlPortKey, oNode, m_nMysqlPort);
	xml_GetElementText(m_strMaxClientCountKey, oNode, m_nMaxClientCount);

	return 0;
}

long CSttCloudServerConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetElementText(m_strPortKey, oXMLDoc, oElement, m_nPort);
	xml_SetElementText(m_strIPKey, oXMLDoc, oElement, m_strIP);
	xml_SetElementText(m_strRemoteCtrlHisRootKey, oXMLDoc, oElement, m_strRemoteCtrlHisRoot);
	xml_SetElementText(m_strMysqlPortKey, oXMLDoc, oElement, m_nMysqlPort);
	xml_SetElementText(m_strMaxClientCountKey, oXMLDoc, oElement, m_nMaxClientCount);

	return 0;
}

