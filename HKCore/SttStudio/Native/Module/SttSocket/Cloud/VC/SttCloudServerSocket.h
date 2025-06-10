#pragma once

#include "..\SttCloudServerSocketBase.h"
#include "SttCloudServerClientSocket.h"

#include "..\..\..\..\..\Module\Socket\WinTcpSocketServer.h"

// CSttRemoteServerSocket ÃüÁîÄ¿±ê

class CSttCloudServerSocket : public CWinTcpSocketServer, public CSttCloudServerSocketBase
{
public:
	CSttCloudServerSocket();
	virtual ~CSttCloudServerSocket();

public:
	virtual BOOL CreateServer(const char *pszIP, int nPort);
	virtual void CloseSttServer();

//	virtual void OnSttScktClose(CSttSocketDataBase *pSttSckt);

	virtual CWinTcpSocketClient* CreateNewSocketClient();
	virtual void OnAccept(CWinTcpSocketClient *pSocket);
};


