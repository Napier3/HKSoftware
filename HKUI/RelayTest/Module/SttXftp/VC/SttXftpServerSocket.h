#pragma once

#include "..\SttXftpServerSocketBase.h"
#include "SttXftpServerSocketClient.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../Module/Socket/Qt/WinTcpSocketServer.h"
#else
#include "../../../../Module/Socket/WinTcpSocketServer.h"
#endif

class CSttXftpServerSocket : public CWinTcpSocketServer, public CSttXftpServerSocketBase
{
public:
	CSttXftpServerSocket();
	virtual ~CSttXftpServerSocket();

public:
	virtual BOOL CreateServer(const char *pszIP, int nPort);
	virtual void CloseSttServer();

	virtual void OnSttScktClose(CSttSocketDataBase_File *pSttSckt);

	virtual CWinTcpSocketClient* CreateNewSocketClient();
	virtual void OnAccept(CWinTcpSocketClient *pSocket);
};


