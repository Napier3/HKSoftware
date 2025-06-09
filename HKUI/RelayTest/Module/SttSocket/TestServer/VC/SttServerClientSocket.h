#ifndef CSTTSERVERCLIENTSOCKET_H
#define CSTTSERVERCLIENTSOCKET_H

#include "../SttServerClientSocketBase.h"

class CSttServerClientSocket : public CSttServerClientSocketBase
{
public:
	CSttServerClientSocket();
    virtual ~CSttServerClientSocket();
	
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void CloseSocket();

	virtual long ReceiveBuffer(BYTE *pBuf, long nLen);
	virtual long SendBuffer(BYTE *pBuf, long nLen);

	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
	
};

#endif // CSTTSERVERCLIENTSOCKET_H
