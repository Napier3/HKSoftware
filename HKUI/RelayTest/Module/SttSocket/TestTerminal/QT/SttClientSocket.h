#ifndef CSTTCLIENTSOCKET_H
#define CSTTCLIENTSOCKET_H

#include "../SttClientSocketBase.h"
#include <QTcpSocket>

class CSttClientSocket : public QObject, public CSttClientSocketBase
{
public:
	CSttClientSocket();
	virtual ~CSttClientSocket();

    QTcpSocket *m_pSocket;

public:
    virtual BOOL ConnectServer(const char *pszIP, int nPort);
	void CloseSocket();

	virtual long ReceiveBuffer(BYTE *pBuf, long nLen);
	virtual long SendBuffer(BYTE *pBuf, long nLen);

public slots:
    void Connected_Qt();
    void CloseSocket_Qt();
    void ReceiveBuffer_Qt();
    void OnError(QAbstractSocket::SocketError);

};

#endif
