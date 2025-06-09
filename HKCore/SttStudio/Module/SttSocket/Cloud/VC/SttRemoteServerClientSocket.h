#pragma once

#include "..\SttCloudServerClientSocketBase.h"

class CSttRemoteServerClientSocket : public CSocket, public CSttCloudServerClientSocketBase
{
public:
	CSttRemoteServerClientSocket();
	virtual ~CSttRemoteServerClientSocket();

public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	virtual long ReceiveBuffer(char *pBuf, long nLen);
	virtual long SendBuffer(char *pBuf, long nLen);

};
