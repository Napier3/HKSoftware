#pragma once

/**************************************
CSttMqttClientEngineConfig:
**************************************/

#include "../../Module/DataMngr/DataGroup.h"

#define STT_MQTT_CONFIG_ID_ServerIP			_T("mqtt-server-ip")
#define STT_MQTT_CONFIG_ID_ServerPort		_T("mqtt-server-port")
#define STT_MQTT_CONFIG_ID_ClientID			_T("mqtt-clientid")
#define STT_MQTT_CONFIG_ID_DefualtQos		_T("mqtt-defualt-qos")
#define STT_MQTT_CONFIG_ID_DefualtTimeout	_T("mqtt-default-timeout")
#define STT_MQTT_CONFIG_ID_DeviceID			_T("mqtt-device-id")
#define STT_MQTT_CONFIG_ID_FTPSERVERIP			_T("mqtt-ftpserver-ip")
#define STT_MQTT_CONFIG_ID_FTPROOT			_T("mqtt-ftp-root")

#define HTTP_URL_HEAD			_T("http-url-head")
#define MYSQL_SERVER_DBName     _T("mysql-server-dbname")
#define MYSQL_SERVER_IP			_T("mysql-server-ip")
#define MYSQL_SERVER_PORT		_T("mysql-server-port")
#define MYSQL_SERVER_PASSWORD	_T("mysql-server-password")
#define MYSQL_SERVER_ENCODING	_T("mysql-server-encoding")

#define LOCAL_MODE		_T("local-mode")
#define VIEW_MODE	_T("view-mode")
#define POWER_IP		_T("power-ip")
#define POWER_VAL	_T("power-val")

class CSttMqttClientEngineConfig : public CDataGroup
{
private:
	CSttMqttClientEngineConfig();
	virtual ~CSttMqttClientEngineConfig();

	static CSttMqttClientEngineConfig *g_pSttMqttClientEngineConfig;
	static long g_nSttMqttClientEngineConfigRef;

	CDataGroup *m_pSubcribeTopics;
	CString m_strFile;

public:
	static CSttMqttClientEngineConfig *Create(const CString &strFile=_T(""));
	static void Release();

	static BOOL GetMqttServerIP(CString &strIP);
	static BOOL GetMqttServerPort(long &nPort);
	static BOOL GetMqttClientID(CString &strClientID);
	static BOOL GetMqttDefualtQos(long &nQos);
	static BOOL GetMqttDefualtTimeOut(long &nTimeOut);
	static BOOL GetMqttDeviceID(CString &strDeviceID);
	static BOOL GetMqttFtpServerIP(CString &strIP);
	static BOOL GetMqttFtpRoot(CString &strRoot);
	static BOOL GetHttpUrlHead(CString &strHttpUrlHead);
	static BOOL GetMysqlServerDBName(CString &strDBName);
	static BOOL GetMysqlServerIP(CString &strIP);
	static BOOL GetMysqlServerPort(long &nPort);
	static BOOL GetMysqlServerPassword(CString &strPassword);
	static BOOL GetMysqlServerDBEncoding(CString &strEncoding);
	static BOOL GetLocalMode(CString &strLocalMode);
	static BOOL GetViewMode(CString &strViewMode);
	static BOOL GetPowerIP(CString &strIP);
	static BOOL GetPowerVal(CString &strValue);
	

    static void SetPowerIP(const CString &strIP);
    static void SetPowerVal(const CString &strValue);
	//2021-7-19  lijunqing 
	static CString GetMqttServerIP();
	static long GetMqttServerPort();

protected:
	//2021-7-19  lijunqing  使用缺省文件
	void OpenMqttClientEngineConfig(const CString &strFile);
	void GetDefaultConfigFile(CString &strFile);
	void SaveMqttClientEngineConfig(const CString &strFile);

};
