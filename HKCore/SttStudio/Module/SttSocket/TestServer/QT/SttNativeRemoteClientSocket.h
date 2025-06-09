#pragma once

#include "../SttNativeRemoteClientSocketBase.h"
#include "QTcpSocket"

class CSttNativeRemoteClientSocket : public QObject, public CSttNativeRemoteClientSocketBase
{
public:
	CSttNativeRemoteClientSocket();
	virtual ~CSttNativeRemoteClientSocket();

public:
	QTcpSocket *m_pSocket;

	virtual BOOL ConnectServer(const CString &strIPServer,long nPort);
	void CloseSocket();

	virtual long ReceiveBuffer(BYTE *pBuf, long nLen);
	virtual long SendBuffer(BYTE *pBuf, long nLen);

public slots:
	void Connected_Qt();
	void CloseSocket_Qt();
	void ReceiveBuffer_Qt();
	void OnError(QAbstractSocket::SocketError);
};
