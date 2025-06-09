#include "stdafx.h"
#include "WinTcpSocketServer.h"
#include "../API/StringApi.h"

#ifdef _PSX_QT_LINUX_
#else
#include "../System/TickCount32.h"
#endif

CWinTcpSocketServer::CWinTcpSocketServer()
{
	m_nReceiveBufferLen = 10240;
	m_pThread = NULL;
}

CWinTcpSocketServer::~CWinTcpSocketServer()
{
	Close();

#ifdef _PSX_QT_LINUX_
	while(m_pThread != NULL)
	{
		Sleep(1);
	}
#else
	CTickCount32 oTick;

	while(m_pThread != NULL)
	{
		oTick.DoEvents(1);
		//		Sleep(1);
	}
#endif
}

long CWinTcpSocketServer::OnAccept(SOCKET skt)
{
	CWinTcpSocketClient *pNew = CreateNewSocketClient();
	pNew->Attach(skt);
	pNew->InitSocketClient(20);
	pNew->SetReceiveBuffLen(m_nReceiveBufferLen);
	OnAccept(pNew);

	pNew->CreateRcvThread();

	return 0;
}

CWinTcpSocketClient* CWinTcpSocketServer::CreateNewSocketClient()
{
	return new CWinTcpSocketClient();
}

#ifdef _PSX_QT_LINUX_
void *AcceptThread(LPVOID pData)
#else
UINT AcceptThread(LPVOID pData)
#endif
{
	CWinTcpSocketServer *pServer = (CWinTcpSocketServer*)pData;
	pServer->InitSocket();

#ifdef _PSX_QT_LINUX_
    socklen_t addrLen = 0;
#else
    int addrLen = 0;
#endif

	SOCKADDR_IN clientSockAddr;
	SOCKET serverSocket;
	SOCKET clientSocket;
	addrLen = sizeof (SOCKADDR_IN);
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

#ifdef _PSX_QT_LINUX_
#else
	return 0;
#endif
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

	CString_to_char(strIP,pszBuffer);

	return CreateServer(pszBuffer, nPort);
}

BOOL CWinTcpSocketServer::CreateServer(const char *strIP, UINT nPort)
{
	if (!InitSocket())
	{
		return FALSE;
	}

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

#ifdef _PSX_QT_LINUX_
    pthread_create(&m_pThread,NULL,AcceptThread,(LPVOID)this );
#else
	m_pThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)AcceptThread,(LPVOID)this,0,NULL);
#endif

    CString strMsg;
    strMsg = _T("服务端成功【%s】【%d】");
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, strMsg.GetString(), strIP, nPort);

	return TRUE;

}

BOOL CWinTcpSocketServer::CloseServer()
{
	CWinTcpSocket::Close();
	return TRUE;
}

BOOL CWinTcpSocketServer::IsServerClosed()
{
	return (m_hSocket == NULL);
}
