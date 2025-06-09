#pragma once

#include "..\SttMqttClientTool.h"
#include "..\..\Module\MySqlApp\MySqlBaseApp.h"
#include "..\..\Module\XHttpServer\XHttpServer.h"
#include "..\xml\JSON\CJSON.h"

class CEdgeHttpServerBaseApp : public CMySqlBaseApp, CXHttpServer
{
public:
	CEdgeHttpServerBaseApp();
	virtual ~CEdgeHttpServerBaseApp();
	CString m_strHttpIP;
	CString	m_strHttpCallbackPath;
	CString	m_strDownloadPath;
	CString	m_strUploadPath;
	CString	m_strMqttIp;
	CString	m_strMqttPort;
	long m_nHttpPort;

	CMqttClient m_oMqttClient;

private:
	static void OnHttpGet(struct evhttp_request* request);
	static void OnHttpPost(struct evhttp_request* request);
	BOOL InitMqttClient();

public:
	void InitEdgeHttpServerBaseApp();
	void ExitEdgeHttpServerBaseApp();

	//边设备认证
	static UINT HttpThread(LPVOID pParam);
	static void GetDeviceMappingID(evhttp_request* request, void* arg);
	static CJSON* CreateTopicJson(const CString& strTopicID, const CString& strTopic, const CString& strDirection);
	static void CreateTopicJson(const CString& strMappingID, CJSON* pArray);
	static char* CreateMappingIDJson(const CString& strMappingID, const CString& strID);

	//文件管理系统
	static CString GetErrorInfo(long nCode);
	static void PrintfLogs(const char* strLogs);
	static void SendFile(evhttp_request* pReq, int nCode, int nfd, long long nSize);
	static void SendReply(evhttp_request* pReq, int nCode, const char* strLogs);
	static long GetBufferData(evbuffer* pInput);
	static CString GetFileName(unsigned char* pszData);
	static int InitFileFd(const char* strPath);
	static void http_request_cb(struct evhttp_request* request, void* arg);
};

extern CEdgeHttpServerBaseApp* g_pEdgeHttpServerBaseApp;