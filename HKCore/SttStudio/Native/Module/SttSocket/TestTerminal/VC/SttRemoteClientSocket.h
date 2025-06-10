#pragma once

#include "../SttRemoteClientSocketBase.h"

class CSttRemoteClientSocket : public CSocket, public CSttRemoteClientSocketBase
{
public:
	CSttRemoteClientSocket();
	virtual ~CSttRemoteClientSocket();

public:
	virtual BOOL ConnectServer(const CString &strIPServer,long nPort);
	virtual void OnReceive(int nErrorCode);
	void CloseSocket()	{	Close();	}

	virtual long ReceiveBuffer(BYTE *pBuf, long nLen);
	virtual long SendBuffer(BYTE *pBuf, long nLen);

};
