#include "SttTestServerSocket.h"
#include "QDebug"
#include "../../Engine/SttTestServerEngine.h"

CSttTestServerSocket::CSttTestServerSocket()
{
	connect(this,SIGNAL(newConnection()),this,SLOT(OnConnected()));
}

void CSttTestServerSocket::OnConnected()
{
	CSttServerClientSocket *pSttSkt=new CSttServerClientSocket;
    pSttSkt->SetTestEngine(CSttTestServerEngine::GetServerEngine());
	pSttSkt->SetSocket( nextPendingConnection() );

	OnSttSktAccept(pSttSkt);
}

BOOL CSttTestServerSocket::CreateServer(const char *pszIP, int nPort)
{
	return listen(QHostAddress(pszIP), nPort);
}
