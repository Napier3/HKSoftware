#ifndef CSTTSERVERCLIENTSOCKET_H
#define CSTTSERVERCLIENTSOCKET_H
#include "../SttServerClientSocketBase.h"
#include "QTcpSocket"

class CSttServerClientSocket :public QObject, public CSttServerClientSocketBase
{
	Q_OBJECT
public:
	QTcpSocket *m_pSocket;
	CSttServerClientSocket();
    virtual ~CSttServerClientSocket();

    virtual long SendBuffer(BYTE *pBuf,long nLen);
	virtual long ReceiveBuffer(BYTE *pBuf,long nLen);
	virtual void CloseSocket();
	void SetSocket(QTcpSocket* pSocket);
public slots:
	void OnSocketClose_Qt();
	void ReceiveBuffer_Qt();
};

#endif // CSTTSERVERCLIENTSOCKET_H
