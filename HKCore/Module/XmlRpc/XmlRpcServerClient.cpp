#include "stdafx.h"

#include "XmlRpcServerClient.h"

#include "XmlRpcSocket.h"
#include "XmlRpc.h"
#include "XmlRpcServerConnection.h"

#include <stdio.h>
#include <stdlib.h>

#include<string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long g_nXmlRpcServerClientCount = 0;
using namespace XmlRpc;

XmlRpcServerClient::XmlRpcServerClient(XmlRpcServerConnection *pServerConnection, unsigned eventMask)
	: XmlRpcSource(-1, FALSE)
{
	g_nXmlRpcServerClientCount++;
//#ifdef _DEBUG
	XmlRpcUtil::log(0, "XmlRpcServerClient::XmlRpcServerClient [g_nXmlRpcServerClientCount=%d]", g_nXmlRpcServerClientCount);
//#endif
	m_pServerConnection = pServerConnection;
	m_dwClient_ThreadID = 0;
	m_hClient_Thread = NULL;
	_disp.addSource(pServerConnection, XmlRpcDispatch::ReadableEvent);
}


XmlRpcServerClient::~XmlRpcServerClient()
{
	g_nXmlRpcServerClientCount--;
//#ifdef _DEBUG
	XmlRpcUtil::log(0, "XmlRpcServerClient::~XmlRpcServerClient [g_nXmlRpcServerClientCount=%d]", g_nXmlRpcServerClientCount);
//#endif
}

// Close the owned fd
void XmlRpcServerClient::close()
{
	if (m_pServerConnection == NULL)
	{
		return;
	}

#ifdef _DEBUG
	XmlRpcUtil::log(1, "XmlRpcServerClient::close()");
#endif

	_disp.exit();
	_disp.removeSource(m_pServerConnection);
	m_pXmlRpcServerRef->CloseServerClient(this);
	XmlRpcSource::close();
	m_pServerConnection = NULL;
	m_pXmlRpcServerRef = NULL;
	delete this;
}

bool XmlRpcServerClient::execute()
{
	::CoInitialize(NULL);
#ifdef _DEBUG
	XmlRpcUtil::log(1, "XmlRpcServerClient::execute");
#endif
	double msTime = 30; 
	_disp.work(msTime, true);
	close();
	::CoUninitialize();
	return true;
}

void XmlRpcServerClient::begin_Client_Thread()
{
	m_hClient_Thread = CreateThread(NULL, 0, Client_Thread, this, 0, &m_dwClient_ThreadID); // 创建线程

}

DWORD WINAPI XmlRpcServerClient::Client_Thread(LPVOID lParam)
{
//#ifdef _DEBUG
	XmlRpcUtil::log(0, ">>XmlRpcServerClient::Client_Thread");
//#endif
	XmlRpcServerClient *pServerClient = (XmlRpcServerClient*)lParam;
	HANDLE hClient_Thread = pServerClient->m_hClient_Thread;
	pServerClient->execute();
//#ifdef _DEBUG
	XmlRpcUtil::log(0, "XmlRpcServerClient::Client_Thread>>");
//#endif
	CloseHandle(hClient_Thread);
	return 0;
}

