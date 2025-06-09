#pragma once

#include "..\SttCloudServerSocketBase.h"
#include "SttRemoteServerClientSocket.h"

// CSttRemoteServerSocket 命令目标

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


