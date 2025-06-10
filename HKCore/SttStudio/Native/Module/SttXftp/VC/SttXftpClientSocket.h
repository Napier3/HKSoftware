#pragma once

#include "../../../Module/SttSocket/SttSocketDataBase_File.h"

#ifndef _PSX_IDE_QT_
#include "afxsock.h"
#endif

class CSttXftpClientSocket : public CSttSocketDataBase_File
{
public:
	CSttXftpClientSocket();
	virtual ~CSttXftpClientSocket();

public:
	virtual BOOL ConnectServer(const CString &strIPServer,long nPort);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void CloseSocket();

	virtual long ReceiveBuffer(BYTE *pBuf, long nLen);
	virtual long SendBuffer(BYTE *pBuf, long nLen);

	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
};
