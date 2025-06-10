#include "SttTestServerSocket.h"
#include "QDebug"
#include "../../../Engine/QT/SttTestServerEngine.h"

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
	BOOL bRet = listen(QHostAddress(pszIP), nPort);
	return bRet;
}
