#pragma once

#include "..\SttCloudServerSocketBase.h"
#include "SttRemoteServerClientSocket.h"

// CSttRemoteServerSocket ÃüÁîÄ¿±ê

class CSttRemoteServerSocket : public CSocket,public CSttCloudServerSocketBase
{
public:
	CSttRemoteServerSocket();
	virtual ~CSttRemoteServerSocket();

public:
	virtual BOOL CreateServer(const CString &strIP, UINT nPort);
	virtual void OnAccept(int nErrorCode);

	virtual void OnSttScktClose(CSttSocketDataBase *pSttSckt);
};


