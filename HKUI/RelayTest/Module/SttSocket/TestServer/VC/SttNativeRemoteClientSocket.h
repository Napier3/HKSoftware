#pragma once

#include "../SttNativeRemoteClientSocketBase.h"

class CSttNativeRemoteClientSocket : public CSttNativeRemoteClientSocketBase
{
public:
	CSttNativeRemoteClientSocket();
	virtual ~CSttNativeRemoteClientSocket();

public:
	virtual BOOL ConnectServer(const CString &strIPServer,long nPort);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void CloseSocket();

	virtual long ReceiveBuffer(BYTE *pBuf, long nLen);
	virtual long SendBuffer(BYTE *pBuf, long nLen);

	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
};
