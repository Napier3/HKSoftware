#pragma once

#include "../SttClientSocketBase.h"
#define MAX_TESTAPPINFO_LEN    512

class CSttClientSocket : public CSttClientSocketBase
{
public:
	CSttClientSocket();
	virtual ~CSttClientSocket();

public:
	virtual BOOL ConnectServer();
	virtual BOOL ConnectServer(const CString &strIPServer,long nPort);
	virtual void OnClose(int nErrorCode);
	void CloseSocket();

	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
};
