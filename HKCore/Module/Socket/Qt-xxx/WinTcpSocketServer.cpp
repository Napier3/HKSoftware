#include "stdafx.h"
#include "WinTcpSocketServer.h"

CWinTcpSocketServer::CWinTcpSocketServer()
{
	m_nReceiveBufferLen = 10240;
	m_pThread = NULL;
}

CWinTcpSocketServer::~CWinTcpSocketServer()
{
	Close();

	while(m_pThread != NULL)
	{
		Sleep(1);
	}
}

long CWinTcpSocketServer::OnAccept(SOCKET skt)
{
	CWinTcpSocketClient *pNew = CreateNewSocketClient();
	pNew->Attach(skt);
    pNew->InitSocketClient(20);
	pNew->SetReceiveBuffLen(m_nReceiveBufferLen);
//20210811 先OnAccept(pNew)设置m_pTestEngine，再创建CreateRcvThread
//    pNew->CreateRcvThread();
//
//	OnAccept(pNew);

	OnAccept(pNew);
	pNew->CreateRcvThread();

	return 0;
}

CWinTcpSocketClient* CWinTcpSocketServer::CreateNewSocketClient()
{
	return new CWinTcpSocketClient();
}

void *AcceptThread(LPVOID pData)
{

    socklen_t  addrLen;
	SOCKADDR_IN clientSockAddr;
	SOCKET serverSocket;
	SOCKET clientSocket;
	addrLen = sizeof (SOCKADDR_IN);
	CWinTcpSocketServer *pServer = (CWinTcpSocketServer*)pData;
	serverSocket = pServer->m_hSocket;

	while (1)
	{
		if (pServer->m_hSocket == NULL)
		{
			break;
		}

		clientSocket = accept(serverSocket, (LPSOCKADDR)&clientSockAddr, &addrLen);

		if (clientSocket == INVALID_SOCKET)
		{//xxy:执行WSACleanup后触发：10093
//			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%d"),GetLastError());
			continue;
		}

		pServer->OnAccept(clientSocket);
	}

	pServer->m_pThread = NULL;

    return (void *)0;
}


BOOL CWinTcpSocketServer::CreateServer(const CString &strIP, UINT nPort)
{
	if (m_pThread != NULL)
	{
		return TRUE;
	}

	char pszBuffer[MAX_PATH];
	pszBuffer[0] = 0;
	long strsize = strIP.GetLength();
	size_t sz=0;

#ifdef UNICODE
	wcstombs_s(&sz,pszBuffer,strsize,strIP,_TRUNCATE);
#else
    strcpy(pszBuffer, strIP.GetString());
#endif

	return CreateServer(pszBuffer, nPort);
}

BOOL CWinTcpSocketServer::CreateServer(const char *strIP, UINT nPort)
{
	if (! Create(SOCK_STREAM))
	{
		return FALSE;
	}

#ifdef _PSX_QT_LINUX_
	int optval = 1;
	setsockopt(m_hSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
#endif

	if (!  Bind(strIP, nPort))
	{
		return FALSE;
	}

	if (! Listen(10))
	{
		return FALSE;
	}

    pthread_create(&m_pThread,NULL,AcceptThread,(LPVOID)this );

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("服务端成功【%s】【%d】"), strIP, nPort);

	return TRUE;

}

BOOL CWinTcpSocketServer::CloseServer()
{
	Close();

	return TRUE;
}

BOOL CWinTcpSocketServer::IsServerClosed()
{
	return (m_hSocket == NULL);
}
