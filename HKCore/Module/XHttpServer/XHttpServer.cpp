#include "stdafx.h"
#include "XHttpServer.h"

CXHttpServer::CXHttpServer()
{
	m_pHttpEventBase = NULL;
	m_pEvHttp = NULL;
}

CXHttpServer::~CXHttpServer()
{

}

BOOL CXHttpServer::InitHttpServer(std::string strIP, int nPort)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	m_pHttpEventBase = event_base_new();
	m_pEvHttp = evhttp_new(m_pHttpEventBase);

	if(evhttp_bind_socket(m_pEvHttp, strIP.c_str(), nPort) == -1)
	{
		long nerr = GetLastError();
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("evhttp_bind_socket: failed   err=%d"), nerr);
		event_base_free(m_pHttpEventBase);
		evhttp_free(m_pEvHttp);
		m_pHttpEventBase = NULL;
		m_pEvHttp = NULL;
		return FALSE;
	}

	return TRUE;
}

//设置回调函数
//strPath是url的路径
//例如 http://xxxx:xxxx/this 即是指 strPath 为 /this
BOOL CXHttpServer::SetHttpServerCallBack(const char* strPath, void (*cb)(struct evhttp_request *, void *))
{	
	if(m_pEvHttp == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("evHttp: failed"));
		return FALSE;
	}

	long nRes = evhttp_set_cb(m_pEvHttp, strPath, cb, NULL);
	switch(nRes)
	{
	case 0:
		break;
	case -1:
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Callback existed already"));
		return FALSE;
	case -2:
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Callback: failed"));
		return FALSE;
	default:
		break;
	}
	return TRUE;
}

void CXHttpServer::SetHttpServerGenCallBack(void (*cb)(struct evhttp_request *, void *))
{
	evhttp_set_gencb(m_pEvHttp, cb, NULL);
}

//分发消息,启动服务
BOOL CXHttpServer::RunHttpServer()
{
	if(m_pHttpEventBase == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("httpEventBase: failed"));
		return FALSE;
	}

	if(m_pHttpEventBase)
	{
		event_base_dispatch(m_pHttpEventBase);
	}

	return TRUE;
}

void CXHttpServer::ExitHttpServer()
{
	if(m_pHttpEventBase)
	{
		event_base_free(m_pHttpEventBase);
		m_pHttpEventBase = NULL;
	}
	if(m_pEvHttp)
	{
		evhttp_free(m_pEvHttp);
		m_pEvHttp = NULL;
	}
	WSACleanup();
}

