#pragma once

#include "..\SttCloudServerClientSocketBase.h"
#include "..\..\..\Module\Socket\WinTcpSocketClient.h"

class CSttCloudServerClientSocket : public CSttCloudServerClientSocketBase
{
public:
	CSttCloudServerClientSocket();
	virtual ~CSttCloudServerClientSocket();

public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void CloseSocket();

	virtual long ReceiveBuffer(BYTE *pBuf, long nLen);
	virtual long SendBuffer(BYTE *pBuf, long nLen);

	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
};
