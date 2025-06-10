#ifndef STTTESTSERVERSOCKET_H
#define STTTESTSERVERSOCKET_H

#include "../SttTestServerSocketBase.h"
#include "../QT/SttServerClientSocket.h"
#include "../../../Engine/QT/SttTestServerEngine.h"
#include "QTcpServer"

class CSttTestServerSocket:public QTcpServer, public CSttTestServerSocketBase
{
	Q_OBJECT
public:
	CSttTestServerSocket();
public slots:
	void OnConnected();
	
    virtual BOOL CreateServer(const char *pszIP, int nPort);
};

#endif // STTTESTSERVERSOCKET_H
