#pragma once

#include "../../../Module/SttSocket/SttSocketDataBase_File.h"
#include "afxsock.h"

class CSttXftpServerSocketClient : public CSttSocketDataBase_File
{
public:
	CSttXftpServerSocketClient();
	virtual ~CSttXftpServerSocketClient();

	void InitSocketClient();

public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void CloseSocket();

	virtual long ReceiveBuffer(BYTE *pBuf, long nLen);
	virtual long SendBuffer(BYTE *pBuf, long nLen);

	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
};
