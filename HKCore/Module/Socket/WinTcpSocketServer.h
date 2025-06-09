#ifndef  _WINTCPSOCKET_SERVER_H__
#define  _WINTCPSOCKET_SERVER_H__

#include "WinTcpSocketClient.h"

class CWinTcpSocketServer : public CWinTcpSocket
{
public:
	CWinTcpSocketServer();
	virtual ~CWinTcpSocketServer();

	long m_nReceiveBufferLen;
public:
	virtual BOOL CreateServer(const CString &strIP, UINT nPort);
	virtual BOOL CreateServer(const char *strIP, UINT nPort);
	virtual BOOL CloseServer();
	virtual BOOL IsServerClosed();

	virtual long OnAccept(SOCKET skt);
	virtual CWinTcpSocketClient* CreateNewSocketClient();
	virtual void OnAccept(CWinTcpSocketClient *pSocket)	{};

public:
#ifdef _PSX_QT_LINUX_
    pthread_t m_pThread;
#else
	HANDLE m_pThread;
#endif

};

#ifdef _PSX_QT_LINUX_
void *AcceptThread(LPVOID pParam);
#else
	static UINT AcceptThread(LPVOID pData);
#endif

#endif