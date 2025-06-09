#pragma once

#include "../../Module/DataMngr/DataGroup.h"

#define STT_HTTP_CONFIG_ID_ServerIP			_T("http-server-ip")
#define STT_HTTP_CONFIG_ID_ServerPort		_T("http-server-port")
#define STT_HTTP_CONFIG_ID_Callback			_T("http-callback")
#define STT_HTTP_CONFIG_ID_MqttIp			_T("mqtt-ip")
#define STT_HTTP_CONFIG_ID_MqttPort			_T("mqtt-port")
#define STT_HTTP_CONFIG_ID_DownloadPath		_T("http-download-path")	
#define STT_HTTP_CONFIG_ID_UploadPath		_T("http-upload-path")	

class CEdgeEngineServerConfig : public CDataGroup
{
private:
	CEdgeEngineServerConfig();
	virtual ~CEdgeEngineServerConfig();

	static CEdgeEngineServerConfig *g_pEdgeEngineServerConfig;
	static long g_nEdgeEngineServerConfigRef;

	CDataGroup *m_pSubcribeTopics;

public:
	static CEdgeEngineServerConfig *Create();
	static void Release();

	static BOOL GetHttpServerIP(CString &strIP);
	static BOOL GetHttpServerPort(long &nPort);
	static BOOL GetHttpCallback(CString &strCallbackPath);
	static BOOL GetHttpDownloadPath(CString &strDownloadPath);
	static BOOL GetHttpUploadPath(CString &strUploadPath);
	static BOOL	GetMqttIp(CString &strMqttIp);
	static BOOL	GetMqttPort(CString &strMqttPort);

protected:
	void GetDefaultConfigFile();
};