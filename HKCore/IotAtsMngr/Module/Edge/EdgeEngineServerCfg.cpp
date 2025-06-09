#include "stdafx.h"
#include "EdgeEngineServerCfg.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  


CEdgeEngineServerConfig *CEdgeEngineServerConfig::g_pEdgeEngineServerConfig = NULL;
long CEdgeEngineServerConfig::g_nEdgeEngineServerConfigRef = 0;

CEdgeEngineServerConfig::CEdgeEngineServerConfig()
{
	m_pSubcribeTopics = NULL;
}

CEdgeEngineServerConfig::~CEdgeEngineServerConfig()
{

}

CEdgeEngineServerConfig *CEdgeEngineServerConfig::Create()
{
	g_nEdgeEngineServerConfigRef++;

	if (g_nEdgeEngineServerConfigRef == 1)
	{
		g_pEdgeEngineServerConfig = new CEdgeEngineServerConfig;


		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;

		g_pEdgeEngineServerConfig->GetDefaultConfigFile();

		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	}

	return g_pEdgeEngineServerConfig;
}

void CEdgeEngineServerConfig::Release()
{
	g_nEdgeEngineServerConfigRef--;

	if (g_nEdgeEngineServerConfigRef == 0)
	{
		delete g_pEdgeEngineServerConfig;
		g_pEdgeEngineServerConfig = NULL;
	}
}

BOOL CEdgeEngineServerConfig::GetHttpServerIP(CString &strIP)
{
	strIP = _T("0.0.0.0");
	return g_pEdgeEngineServerConfig->GetDataValue(STT_HTTP_CONFIG_ID_ServerIP, strIP);
}

BOOL CEdgeEngineServerConfig::GetHttpServerPort(long &nPort)
{
	nPort = 23106;
	return g_pEdgeEngineServerConfig->GetDataValue(STT_HTTP_CONFIG_ID_ServerPort, nPort);
}

BOOL CEdgeEngineServerConfig::GetHttpCallback(CString &strCallbackPath)
{
	strCallbackPath = _T("/iot/devices/auth/gateway");
	return g_pEdgeEngineServerConfig->GetDataValue(STT_HTTP_CONFIG_ID_Callback, strCallbackPath);
}

BOOL CEdgeEngineServerConfig::GetHttpDownloadPath(CString &strDownloadPath)
{
	strDownloadPath = "D:";
	return g_pEdgeEngineServerConfig->GetDataValue(STT_HTTP_CONFIG_ID_DownloadPath, strDownloadPath);
}

BOOL CEdgeEngineServerConfig::GetHttpUploadPath(CString &strUploadPath)
{
	strUploadPath = "D:";
	return g_pEdgeEngineServerConfig->GetDataValue(STT_HTTP_CONFIG_ID_UploadPath, strUploadPath);
}

BOOL CEdgeEngineServerConfig::GetMqttIp(CString &strMqttIp)
{
	strMqttIp = "127.0.0.1";
	return g_pEdgeEngineServerConfig->GetDataValue(STT_HTTP_CONFIG_ID_MqttIp, strMqttIp);
}

BOOL CEdgeEngineServerConfig::GetMqttPort(CString &strMqttPort)
{
	strMqttPort = "1883";
	return g_pEdgeEngineServerConfig->GetDataValue(STT_HTTP_CONFIG_ID_MqttPort, strMqttPort);
}

void CEdgeEngineServerConfig::GetDefaultConfigFile()
{
	CString strFile = _P_GetConfigPath();
	strFile += _T("EdgeHttpServerCfg.xml");
	OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}