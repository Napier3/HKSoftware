#ifndef STTTESTSERVERSOCKET_H
#define STTTESTSERVERSOCKET_H

#include "../SttTestServerSocketBase.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../../Module/Socket/WinTcpSocketServer.h"
#else
#include "../../../../../Module/Socket/WinTcpSocketServer.h"
#endif

class CSttTestServerSocket : public CWinTcpSocketServer, public CSttTestServerSocketBase
{
public:
	CSttTestServerSocket();
	virtual ~CSttTestServerSocket();
	
public:
	virtual BOOL CreateServer(const char *pszIP, int nPort);	
	virtual void CloseSttServer();//2020-4-6  lijq

	virtual void OnSttScktClose(CSttSocketDataBase *pSttSckt, BOOL bDeleteSocket = TRUE);

	virtual CWinTcpSocketClient* CreateNewSocketClient();
	virtual void OnAccept(CWinTcpSocketClient *pSocket);
};

#endif // STTTESTSERVERSOCKET_H
