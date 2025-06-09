#include "stdafx.h"
#include "SttMqttClientEngineConfig.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "../../Module/API/FileApi.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  


CSttMqttClientEngineConfig *CSttMqttClientEngineConfig::g_pSttMqttClientEngineConfig = NULL;
long CSttMqttClientEngineConfig::g_nSttMqttClientEngineConfigRef = 0;

CSttMqttClientEngineConfig::CSttMqttClientEngineConfig()
{
	m_pSubcribeTopics = NULL;
}

CSttMqttClientEngineConfig::~CSttMqttClientEngineConfig()
{

}

CSttMqttClientEngineConfig *CSttMqttClientEngineConfig::Create(const CString &strFile)
{
	g_nSttMqttClientEngineConfigRef++;

	if (g_nSttMqttClientEngineConfigRef == 1)
	{
		g_pSttMqttClientEngineConfig = new CSttMqttClientEngineConfig;

		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;

		//2021-7-19  lijunqing
		//g_pSttMqttClientEngineConfig->OpenXmlFile(strFile,CDataMngrXmlRWKeys::g_pXmlKeys);
		g_pSttMqttClientEngineConfig->OpenMqttClientEngineConfig(strFile);
		g_pSttMqttClientEngineConfig->m_strFile = strFile;

		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	}

	return g_pSttMqttClientEngineConfig;
}

void CSttMqttClientEngineConfig::Release()
{
	g_nSttMqttClientEngineConfigRef--;

	if (g_nSttMqttClientEngineConfigRef == 0)
	{
		//g_pSttMqttClientEngineConfig->SaveMqttClientEngineConfig(g_pSttMqttClientEngineConfig->m_strFile);
		delete g_pSttMqttClientEngineConfig;
		g_pSttMqttClientEngineConfig = NULL;
	}
}

BOOL CSttMqttClientEngineConfig::GetMqttServerIP(CString &strIP)
{
	strIP = _T("127.0.0.1");
	return g_pSttMqttClientEngineConfig->GetDataValue(STT_MQTT_CONFIG_ID_ServerIP,strIP);
}

BOOL CSttMqttClientEngineConfig::GetMqttServerPort(long &nPort)
{
	nPort = 1883;
	return g_pSttMqttClientEngineConfig->GetDataValue(STT_MQTT_CONFIG_ID_ServerPort,nPort);
}

BOOL CSttMqttClientEngineConfig::GetMqttClientID(CString &strClientID)
{
	strClientID = _T("ClientID_1");
	return g_pSttMqttClientEngineConfig->GetDataValue(STT_MQTT_CONFIG_ID_ClientID,strClientID);
}

BOOL CSttMqttClientEngineConfig::GetMqttDefualtQos(long &nQos)
{
	nQos = 0;
	return g_pSttMqttClientEngineConfig->GetDataValue(STT_MQTT_CONFIG_ID_DefualtQos,nQos);
}

BOOL CSttMqttClientEngineConfig::GetMqttDefualtTimeOut(long &nTimeOut)
{
	nTimeOut = 5000;
	return g_pSttMqttClientEngineConfig->GetDataValue(STT_MQTT_CONFIG_ID_DefualtTimeout,nTimeOut);
}

BOOL CSttMqttClientEngineConfig::GetMqttDeviceID(CString &strDeviceID)
{
	strDeviceID = _T("DeviceID_1");
	return g_pSttMqttClientEngineConfig->GetDataValue(STT_MQTT_CONFIG_ID_DeviceID,strDeviceID);
}

BOOL CSttMqttClientEngineConfig::GetMqttFtpServerIP(CString &strIP)
{
	strIP = _T("127.0.0.1");
	return g_pSttMqttClientEngineConfig->GetDataValue(STT_MQTT_CONFIG_ID_FTPSERVERIP,strIP);
}

BOOL CSttMqttClientEngineConfig::GetMqttFtpRoot(CString &strRoot)
{
	strRoot = _T("d:\\FtpRoot\\");
	return g_pSttMqttClientEngineConfig->GetDataValue(STT_MQTT_CONFIG_ID_FTPROOT,strRoot);
}

BOOL CSttMqttClientEngineConfig::GetHttpUrlHead(CString &strHttpUrlHead)
{
	strHttpUrlHead = _T("http://121.41.92.56:3000");
	return g_pSttMqttClientEngineConfig->GetDataValue(HTTP_URL_HEAD,strHttpUrlHead);
}

BOOL CSttMqttClientEngineConfig::GetMysqlServerDBName(CString &strDBName)
{
	strDBName = _T("tyh");
	return g_pSttMqttClientEngineConfig->GetDataValue(MYSQL_SERVER_DBName,strDBName);
}

BOOL CSttMqttClientEngineConfig::GetMysqlServerIP(CString &strIP)
{
	strIP = _T("127.0.0.1");
	return g_pSttMqttClientEngineConfig->GetDataValue(MYSQL_SERVER_IP,strIP);
}

BOOL CSttMqttClientEngineConfig::GetMysqlServerPort(long &nPort)
{
	nPort = 3306;
	return g_pSttMqttClientEngineConfig->GetDataValue(MYSQL_SERVER_PORT,nPort);
}

BOOL CSttMqttClientEngineConfig::GetMysqlServerPassword(CString &strPassword)
{
	strPassword = _T("123456");
	return g_pSttMqttClientEngineConfig->GetDataValue(MYSQL_SERVER_PASSWORD,strPassword);
}

BOOL CSttMqttClientEngineConfig::GetMysqlServerDBEncoding(CString &strEncoding)
{
	strEncoding = _T("utf8mb4");
	return g_pSttMqttClientEngineConfig->GetDataValue(MYSQL_SERVER_ENCODING,strEncoding);
}

void CSttMqttClientEngineConfig::GetDefaultConfigFile(CString &strFile)
{
	strFile = _P_GetConfigPath();
	strFile += _T("SttMqttClientEngineCfg.xml");
}

//2021-7-19  lijunqing 
CString CSttMqttClientEngineConfig::GetMqttServerIP()
{
	CString strIp;
	GetMqttServerIP(strIp);
	return strIp;
}

long CSttMqttClientEngineConfig::GetMqttServerPort()
{
	long nPort = 0;
	GetMqttServerPort(nPort);
	return nPort;
}

BOOL CSttMqttClientEngineConfig::GetLocalMode(CString &strLocalMode)
{
	strLocalMode = _T("1");
	return g_pSttMqttClientEngineConfig->GetDataValue(LOCAL_MODE,strLocalMode);
}

BOOL CSttMqttClientEngineConfig::GetViewMode(CString &strViewMode)
{
	strViewMode = _T("1");
	return g_pSttMqttClientEngineConfig->GetDataValue(VIEW_MODE,strViewMode);
}

BOOL CSttMqttClientEngineConfig::GetPowerIP(CString &strIP)
{
	strIP = _T("127.0.0.1");
	return g_pSttMqttClientEngineConfig->GetDataValue(POWER_IP,strIP);
}

BOOL CSttMqttClientEngineConfig::GetPowerVal(CString &strValue)
{
	strValue = _T("220");
	return g_pSttMqttClientEngineConfig->GetDataValue(POWER_VAL,strValue);
}

void CSttMqttClientEngineConfig::SetPowerIP(const CString &strIP)
{
	g_pSttMqttClientEngineConfig->SetDataValue(POWER_IP, strIP);
}

void CSttMqttClientEngineConfig::SetPowerVal(const CString &strValue)
{
	g_pSttMqttClientEngineConfig->SetDataValue(POWER_VAL, strValue);
}

void CSttMqttClientEngineConfig::OpenMqttClientEngineConfig(const CString &strFile)
{//2021-7-19  lijunqing  娴ｈ法鏁ょ紓铏规阜閺傚洣娆?
	CString strPath = strFile;
	
	if (strPath.GetLength() <= 5)
	{
		GetDefaultConfigFile(strPath);
	}
	else
	{
		if (!IsFileExist(strPath))
		{
			GetDefaultConfigFile(strPath);
		}
	}
	
	OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
}
void CSttMqttClientEngineConfig::SaveMqttClientEngineConfig(const CString &strFile)
{
	CString strPath = strFile;

	if (strPath.GetLength() <= 5)
	{
		GetDefaultConfigFile(strPath);
	}
	else
	{
		if (!IsFileExist(strPath))
		{
			GetDefaultConfigFile(strPath);
		}
	}

	SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
}