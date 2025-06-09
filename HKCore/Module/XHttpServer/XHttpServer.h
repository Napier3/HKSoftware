#pragma once

#include<WinSock2.h>
#include <string>

#include "event\event2\event.h"
#include "event\event2\http_struct.h"
#include "event\event2\http.h"
#include "event\event2\buffer_compat.h"
#include "event\event2\buffer.h"

class CXHttpServer
{
public:
	CXHttpServer();
	virtual ~CXHttpServer();

	event_base *m_pHttpEventBase;
	evhttp* m_pEvHttp;
public:
	BOOL InitHttpServer(std::string strIP, int nPort);
	BOOL SetHttpServerCallBack(const char* strPath, void (*cb)(struct evhttp_request *, void *));
	void SetHttpServerGenCallBack(void (*cb)(struct evhttp_request *, void *));
	BOOL RunHttpServer();
	void ExitHttpServer();

private:
	
};
