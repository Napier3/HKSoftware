#include "stdafx.h"
#include "EdgeHttpServerBaseApp.h"
#include "EdgeEngineServerCfg.h"
#include "EdgeCmd\EdgeCmdMngrGlobal.h"
#include "EdgeCmd\EdgeAuth.h"
#include <fcntl.h>
#include <sys\stat.h>
#include <io.h>

CEdgeHttpServerBaseApp *g_pEdgeHttpServerBaseApp = NULL;

CEdgeHttpServerBaseApp::CEdgeHttpServerBaseApp()
{
	m_nHttpPort = 0;
}

CEdgeHttpServerBaseApp::~CEdgeHttpServerBaseApp()
{

}

void CEdgeHttpServerBaseApp::OnHttpGet(struct evhttp_request* request)
{
	const evhttp_uri* url = evhttp_request_get_evhttp_uri(request);
	const char* strPath = evhttp_uri_get_path(url);
	const char* pQuery = evhttp_uri_get_query(url);
	const char* strHost = evhttp_request_get_host(request);

	int fd = InitFileFd(strPath);
	if (fd < 0)
	{
		SendReply(request, HTTP_NOTFOUND, NULL);
		PrintfLogs(_T("Download error: file not found!"));
		return;
	}

	struct stat st;
	if (fstat(fd, &st) < 0)
	{
		SendReply(request, HTTP_NOTFOUND, _T("file: not found!"));
		PrintfLogs(_T("Download error: file not found!"));
	}
	else
	{
		SendFile(request, HTTP_OK, fd, st.st_size);
		CString strLogs = g_pEdgeHttpServerBaseApp->m_strDownloadPath + CString(strPath) + " download success!";
		PrintfLogs(strLogs.GetString());
	}
}

void CEdgeHttpServerBaseApp::OnHttpPost(struct evhttp_request* request)
{
	const evhttp_uri* url = evhttp_request_get_evhttp_uri(request);
	const char* strPath = evhttp_uri_get_path(url);
	const char* strHost = evhttp_request_get_host(request);

	evbuffer* pInput = evhttp_request_get_input_buffer(request);

	long nLen = EVBUFFER_LENGTH(pInput);
	unsigned char* strData = EVBUFFER_DATA(pInput);
	strData[nLen] = '\0';

	CString strName = GetFileName(strData);
	CString strFilePath = g_pEdgeHttpServerBaseApp->m_strUploadPath + strPath + strName;

	FILE* fp = NULL;
	fopen_s(&fp, strFilePath.GetString(), "wb");

	if (fp != NULL)
	{
		long nOutputLen = GetBufferData(pInput);
		fwrite(EVBUFFER_DATA(pInput), 1, nOutputLen, fp);
		fclose(fp);
		SendReply(request, HTTP_OK, "{\"code\":200}");
		CString strLogs = strFilePath + " upload success!";
		PrintfLogs(strLogs.GetString());
	}
	else
	{
		SendReply(request, HTTP_NOTFOUND, NULL);

		PrintfLogs(_T("Upload error: path not found!"));
	}
}

void CEdgeHttpServerBaseApp::InitEdgeHttpServerBaseApp()
{
	_P_InitSystemPath();

	CDataMngrXmlRWKeys::Create();
	CEdgeEngineServerConfig::Create();
	CEdgeCmdMngrXmlRWKeys::Create();
	
	CEdgeEngineServerConfig::GetHttpServerIP(m_strHttpIP);
	CEdgeEngineServerConfig::GetHttpServerPort(m_nHttpPort);
	CEdgeEngineServerConfig::GetHttpCallback(m_strHttpCallbackPath);
	CEdgeEngineServerConfig::GetHttpDownloadPath(m_strDownloadPath);
	CEdgeEngineServerConfig::GetHttpUploadPath(m_strUploadPath);
	CEdgeEngineServerConfig::GetMqttIp(m_strMqttIp);
	CEdgeEngineServerConfig::GetMqttPort(m_strMqttPort);

	CDBServerInfoBase oDBServerInfo;
	oDBServerInfo.m_strDbName = _T("tyh");//数据库名称
	oDBServerInfo.m_strUserName = _T("root");
	oDBServerInfo.m_strPasswd = _T("123456");
	oDBServerInfo.m_strHostIp = m_strHttpIP;
	oDBServerInfo.m_iPort = 3306;
	oDBServerInfo.m_strEncoding = _T("utf8mb4");
	InitMySqlDB(oDBServerInfo);

	long nRes = InitHttpServer(m_strHttpIP.GetString(), m_nHttpPort);
	SetHttpServerCallBack(m_strHttpCallbackPath, &CEdgeHttpServerBaseApp::GetDeviceMappingID);
	SetHttpServerGenCallBack(&CEdgeHttpServerBaseApp::http_request_cb);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("边设备认证IP=[%s],认证端口=[%d]"), m_strHttpIP.GetString(), m_nHttpPort);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("边设备认证地址=[%s]"), m_strHttpCallbackPath.GetString());
	AfxBeginThread(HttpThread, this);

	if(InitMqttClient() == FALSE)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Mqtt物联管理平台[%s,%s]连接失败!"), m_strMqttIp, m_strMqttPort);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Mqtt物联管理平台[%s,%s]连接成功!"), m_strMqttIp, m_strMqttPort);
	}
}

BOOL CEdgeHttpServerBaseApp::InitMqttClient()
{
	if (m_oMqttClient.IsConnectSuccessful())
	{
		return TRUE;
	}

	BOOL bRet = m_oMqttClient.InitMqttClient(m_strMqttIp, CString_To_long(m_strMqttPort), _T("EdgeHttpServer_MqttClient"));
	return bRet;
}

void CEdgeHttpServerBaseApp::ExitEdgeHttpServerBaseApp()
{
	CEdgeCmdMngrXmlRWKeys::Release();
	CEdgeEngineServerConfig::Release();
	CDataMngrXmlRWKeys::Release();
}


UINT CEdgeHttpServerBaseApp::HttpThread(LPVOID pParam)
{
	return ((CEdgeHttpServerBaseApp*)pParam)->RunHttpServer();
}

void CEdgeHttpServerBaseApp::GetDeviceMappingID(evhttp_request* request, void* arg)
{
	//从request对象获取请求的uri对象
	const struct evhttp_uri* pUrl = evhttp_request_get_evhttp_uri(request);
	//获取post数据
	char *pData = (char*)EVBUFFER_DATA(request->input_buffer);
	pData[request->body_size] = '\0';

	//获取sn、厂家等信息并查询数据库分配id
	CString strID, strVersion, strSN, strModule/*, strAlgID, strCheckID*/;
	CJSON* pJson = CJSON_Parse(pData);
	strID.Format("%d", CJSON_GetObjectItem(pJson, _T("id"))->valueint);
	strVersion = CJSON_GetObjectItem(pJson, _T("version"))->valuestring;
	CJSON* pBody = CJSON_GetObjectItem(pJson, _T("body"));
	strSN = CJSON_GetObjectItem(pBody, _T("sn"))->valuestring;
	strModule = CJSON_GetObjectItem(pBody, _T("module"))->valuestring;
	//strAlgID = CJSON_GetObjectItem(pBody, _T("algId"))->valuestring;
	//strCheckID = CJSON_GetObjectItem(pBody, _T("checkID"))->valuestring;
	CEdgeAuth oAuth;
	CString strMappingID = oAuth.QuenryEdgeMappingID(strSN, strModule, g_pTheMySqlApp, CEdgeCmdMngrXmlRWKeys::g_pXmlKeys);

	//生成回复报文
	char* strReport = CreateMappingIDJson(strMappingID, strID);

	//返回报文
	struct evbuffer* evbuf = evbuffer_new();
	evbuffer_add_printf(evbuf, strReport);
	evhttp_send_reply(request, HTTP_OK, "OK", evbuf);
	evbuffer_free(evbuf);

	//发送到EdgeServer
	CString strTopic, strCallbackPath;
	strTopic.Format(_T("/v1/%s/device/request"), _T("edge_auth_id"));
	g_pEdgeHttpServerBaseApp->m_oMqttClient.PublicTopic(strTopic.GetString(), const_cast<char*>(strMappingID.GetString()), strMappingID.GetLength());
	strTopic.Format(_T("/v1/%s%s/device/request"), _T("edge_auth_topic_"), strMappingID);
	strCallbackPath.Format(_T("%s:%d%s"), g_pEdgeHttpServerBaseApp->m_strHttpIP, g_pEdgeHttpServerBaseApp->m_nHttpPort, g_pEdgeHttpServerBaseApp->m_strHttpCallbackPath);
	g_pEdgeHttpServerBaseApp->m_oMqttClient.PublicTopic(strTopic.GetString(), const_cast<char*>(strCallbackPath.GetString()), strCallbackPath.GetLength());
	strTopic.Format(_T("/v1/%s%s/device/request"), _T("edge_auth_request_"), strMappingID);
	g_pEdgeHttpServerBaseApp->m_oMqttClient.PublicTopic(strTopic.GetString(), pData, strlen(pData));
	strTopic.Format(_T("/v1/%s%s/device/request"), _T("edge_auth_response_"), strMappingID);
	g_pEdgeHttpServerBaseApp->m_oMqttClient.PublicTopic(strTopic.GetString(), strReport, strlen(strReport));
}

CJSON* CEdgeHttpServerBaseApp::CreateTopicJson(const CString& strTopicID, const CString& strTopic, const CString& strDirection)
{
	CJSON* pJson = CJSON_CreateObject();
	CJSON_AddStringToObject(pJson, _T("topicId"), strTopicID);
	CJSON_AddNumberToObject(pJson, _T("qos"), 0);
	CJSON_AddStringToObject(pJson, _T("topic"), strTopic);
	CJSON_AddStringToObject(pJson, _T("direction"), strDirection);
	return pJson;
}

void CEdgeHttpServerBaseApp::CreateTopicJson(const CString& strMappingID, CJSON* pArray)
{
	CString strHead;
	strHead.Format("/v1/%s", strMappingID);
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("DEV_CMD"), strHead + _T("/device/command"), _T("down")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("TOPO_REQ"), strHead + _T("/topo/request"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("TOPO_RESP"), strHead + _T("/topo/response"), _T("down")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("DEV_REPLY"), strHead + _T("/device/reply"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("DEV_DATA"), strHead + _T("/device/data"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("DEV_RESP"), strHead + _T("/device/response"), _T("down")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("DEV_REQ"), strHead + _T("/device/request"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("SER_DATA"), strHead + _T("/service/data"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("SER_CMD"), strHead + _T("/service/command"), _T("down")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("SER_REPLY"), strHead + _T("/service/reply"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("SER_RESP"), strHead + _T("/service/response"), _T("down")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("SER_REQ"), strHead + _T("/service/request"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("SER_EVENT"), strHead + _T("/service/event"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("APP_CMD"), strHead + _T("/app/command"), _T("down")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("APP_REPLY"), strHead + _T("/app/reply"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("APP_DATA"), strHead + _T("/app/data"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("CONTAINER_CMD"), strHead + _T("/container/command"), _T("down")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("CONTAINER_REPLY"), strHead + _T("/container/reply"), _T("up")));
	CJSON_AddItemToArray(pArray, CreateTopicJson(_T("CONTAINER_DATA"), strHead + _T("/container/data"), _T("up")));
}

char* CEdgeHttpServerBaseApp::CreateMappingIDJson(const CString& strMappingID, const CString& strID)
{
	CJSON* pJson = CJSON_CreateObject();

	if(!strMappingID.GetLength())
	{
		CJSON_AddNumberToObject(pJson, _T("code"), 4009);
		CJSON_AddStringToObject(pJson, _T("errMsg"), _T("设备没有注册!"));
		CJSON_AddStringToObject(pJson, _T("id"), strID);
	}
	else
	{
		//基础信息 code errMsg id
		CJSON_AddNumberToObject(pJson, _T("code"), 2000);
		CJSON_AddStringToObject(pJson, _T("errMsg"), _T("成功"));
		CJSON_AddStringToObject(pJson, _T("id"), strID);
		//附加信息 devId channelList profile...
		//value
		CJSON* pValue = CJSON_CreateObject();
		CJSON_AddItemToObject(pJson, _T("value"), pValue);
		//devId
		CJSON_AddStringToObject(pValue, _T("devId"), strMappingID);
		//channelList
		CJSON *pChannel = CJSON_CreateArray();
		CJSON_AddItemToObject(pValue, _T("channelList"), pChannel);
		CJSON *pChannelChild = CJSON_CreateObject();
		CJSON_AddStringToObject(pChannelChild, _T("protocol"), _T("http"));
		CJSON_AddStringToObject(pChannelChild, _T("addr"), g_pEdgeHttpServerBaseApp->m_strHttpCallbackPath);
		CJSON_AddStringToObject(pChannelChild, _T("channelId"), _T("CHANNEL_HTTP_FILE"));
		CJSON_AddItemToArray(pChannel, pChannelChild);
		//profile
		CJSON* pProfile = CJSON_CreateObject();
		CJSON_AddItemToObject(pValue, _T("profile"), pProfile);
		//tenancy
		CJSON_AddNumberToObject(pValue, _T("tenancy"), 2592111);
		//topicList
		CJSON* pTopicList = CJSON_CreateArray();
		CJSON_AddItemToObject(pValue, _T("profile"), pTopicList);
		CreateTopicJson(strMappingID, pTopicList);
	}

	char* strJson = CJSON_Print(pJson);
	CJSON_Delete(pJson);
	return strJson;
}

CString CEdgeHttpServerBaseApp::GetErrorInfo(long nCode)
{
	switch(nCode)
	{
	case HTTP_OK: return _T("OK");
	case HTTP_NOCONTENT:	return _T("204");
	case HTTP_MOVEPERM:		return _T("301");
	case HTTP_MOVETEMP:		return _T("302");
	case HTTP_NOTMODIFIED:	return _T("304");
	case HTTP_BADREQUEST:		return _T("400");
	case HTTP_NOTFOUND:		return _T("404");
	case HTTP_BADMETHOD:		return _T("405");
	case HTTP_ENTITYTOOLARGE:	return _T("413");
	case HTTP_EXPECTATIONFAILED: return _T("417");
	case HTTP_INTERNAL:   return _T("500");       
	case HTTP_NOTIMPLEMENTED:   return _T("501");
	case HTTP_SERVUNAVAIL:	return _T("503");
	default:
		break;
	}
	return _T("0");
}

void CEdgeHttpServerBaseApp::PrintfLogs(const char* strLogs)
{
	SYSTEMTIME tm;
	GetSystemTime(&tm);
	CString strTime;
	strTime.Format("[%d-%d-%d %d:%d:%d]: %s \n",tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, strLogs);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, strTime);
}

void CEdgeHttpServerBaseApp::SendFile(evhttp_request* pReq, int nCode, int nfd, long long nSize)
{
	struct evbuffer* outBuf;
	outBuf = evbuffer_new();
	evbuffer_add_file(outBuf, nfd, 0, nSize);
	if(nCode == HTTP_OK)
	{
		evhttp_send_reply(pReq, nCode, GetErrorInfo(nCode).GetString(), outBuf);
	}
	else
	{
		evhttp_send_error(pReq, nCode, GetErrorInfo(nCode).GetString());
	}
	evbuffer_free(outBuf);
}

void CEdgeHttpServerBaseApp::SendReply(evhttp_request* pReq, int nCode, const char* strLogs)
{
	struct evbuffer* outBuf;
	outBuf = evbuffer_new();
	evbuffer_add_printf(outBuf, "%s", strLogs);
	if(nCode == HTTP_OK)
	{
		evhttp_send_reply(pReq, nCode, GetErrorInfo(nCode).GetString(), outBuf);
	}
	else
	{
		evhttp_send_error(pReq, nCode, GetErrorInfo(nCode).GetString());
	}
	evbuffer_free(outBuf);
}

long CEdgeHttpServerBaseApp::GetBufferData(evbuffer* pInput)
{
	//确定该数据块的分隔符字符串
	evbuffer_lock(pInput);
	char* strHeader = evbuffer_readln(pInput, 0, EVBUFFER_EOL_CRLF);
	long nLen = strlen(strHeader);
	evbuffer_readln(pInput, 0, EVBUFFER_EOL_CRLF);
	evbuffer_readln(pInput, 0, EVBUFFER_EOL_CRLF);
	evbuffer_readln(pInput, 0, EVBUFFER_EOL_CRLF);

	long nOutputLen = EVBUFFER_LENGTH(pInput) - nLen - 6;

	evbuffer_unlock(pInput);
	return nOutputLen;
}

CString CEdgeHttpServerBaseApp::GetFileName(unsigned char* pszData)
{
	CString strData = (char*)pszData;
	//查询filename
	const char* filename = "filename=\"";
	long nFilename = strlen(filename);
	CString strName = strData.Mid(strData.Find(filename) + nFilename);
	strName = strName.Mid(0, strName.Find('\"'));
	return strName;
}

int CEdgeHttpServerBaseApp::InitFileFd(const char* strPath)
{
	int fd = 0;
	CString strFilePath = g_pEdgeHttpServerBaseApp->m_strDownloadPath + strPath;
	_sopen_s(&fd, strFilePath.GetString(), O_RDONLY | O_BINARY, _SH_DENYWR, _S_IREAD);
	return fd;
}

void CEdgeHttpServerBaseApp::http_request_cb(struct evhttp_request* request, void* arg)
{
	evhttp_cmd_type nType = evhttp_request_get_command(request);
	if (nType == EVHTTP_REQ_GET)
	{
		OnHttpGet(request);
	}
	else if (nType == EVHTTP_REQ_POST)
	{
		OnHttpPost(request);
	}
	else
	{
		SendReply(request, HTTP_BADMETHOD, _T("method: not allowed!"));
		PrintfLogs(_T("Upload error: method not allowed!"));
	}
}