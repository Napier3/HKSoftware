// SttRemoteServerSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SttXftpServerSocket.h"
#include "..\..\..\Module\Socket\XPing.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CSttRemoteServerSocket

CSttXftpServerSocket::CSttXftpServerSocket()
{
	m_nReceiveBufferLen = STT_FILECMD_MAX_LEN;
}

CSttXftpServerSocket::~CSttXftpServerSocket()
{

}

// CSttRemoteServerSocket ��Ա����
BOOL CSttXftpServerSocket::CreateServer(const char *pszIP, int nPort)
{
	return CWinTcpSocketServer::CreateServer(pszIP, nPort);
}

void CSttXftpServerSocket::CloseSttServer()
{
	CWinTcpSocketServer::CloseServer();
}

//����Ǳ��ض˶�����ƴUnRegister����Ӧ��Զ�̶�
//�����Զ�̶ˣ�ƴLogout���������
void CSttXftpServerSocket::OnSttScktClose(CSttSocketDataBase_File *pSttSckt)
{
	CSttXftpServerSocketBase::OnSttScktClose(pSttSckt);
}

CWinTcpSocketClient* CSttXftpServerSocket::CreateNewSocketClient()
{
	return new CSttXftpServerSocketClient();
}

void CSttXftpServerSocket::OnAccept(CWinTcpSocketClient *pSocket)
{
	CSttXftpServerSocketClient *pClientSocket = (CSttXftpServerSocketClient*)pSocket;

	int nPort = 0;
	char strIP[64];
	pClientSocket->get_RemoteIP_Port(strIP, &nPort);
	pClientSocket->m_strIPRemote = strIP;
	pClientSocket->m_nPortRemote = nPort;
	OnSttSktAccept(pClientSocket);
}
