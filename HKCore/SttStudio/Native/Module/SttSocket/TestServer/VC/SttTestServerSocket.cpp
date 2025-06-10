#include "stdafx.h"

#include "SttTestServerSocket.h"
#include "../../../Engine/SttTestServerBase.h"
#include "SttServerClientSocket.h"

CSttTestServerSocket::CSttTestServerSocket()
{
	m_nReceiveBufferLen = STT_FILECMD_MAX_LEN;
}

CSttTestServerSocket::~CSttTestServerSocket()
{
	
}

// CSttRemoteServerSocket ��Ա����
BOOL CSttTestServerSocket::CreateServer(const char *pszIP, int nPort)
{
	m_strIPLocal = pszIP;
	return CWinTcpSocketServer::CreateServer(pszIP, nPort);
}

//2020-4-6  lijq
void CSttTestServerSocket::CloseSttServer()
{
	CWinTcpSocketServer::CloseServer();

	CSttServerSocketDataBase::CloseSttServer();
}

//����Ǳ��ض˶�����ƴUnRegister����Ӧ��Զ�̶�
//�����Զ�̶ˣ�ƴLogout���������
void CSttTestServerSocket::OnSttScktClose(CSttSocketDataBase *pSttSckt, BOOL bDeleteSocket)
{
    CSttServerSocketDataBase::OnSttScktClose(pSttSckt, bDeleteSocket);
}

CWinTcpSocketClient* CSttTestServerSocket::CreateNewSocketClient()
{
	return new CSttServerClientSocket();
}

void CSttTestServerSocket::OnAccept(CWinTcpSocketClient *pSocket)
{
	CSttServerClientSocket *pClientSocket = (CSttServerClientSocket*)pSocket;

	int nPort = 0;
	char strIP[64];
	pClientSocket->get_RemoteIP_Port(strIP, &nPort);
	pClientSocket->m_strIPRemote = strIP;
	pClientSocket->m_nPortRemote = nPort;

	pClientSocket->SetTestEngine(m_pTestEngine);
	OnSttSktAccept(pClientSocket);
}
