// SttRemoteServerSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SttCloudServerSocket.h"
#include "..\..\..\Module\Socket\XPing.h"
#include "..\..\..\Cloud\SttCloudServerConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CSttRemoteServerSocket

CSttCloudServerSocket::CSttCloudServerSocket()
{
	m_nReceiveBufferLen = STT_FILECMD_MAX_LEN;
}

CSttCloudServerSocket::~CSttCloudServerSocket()
{

}

// CSttRemoteServerSocket ��Ա����
BOOL CSttCloudServerSocket::CreateServer(const char *pszIP, int nPort)
{
	return CWinTcpSocketServer::CreateServer(pszIP, nPort);
}

void CSttCloudServerSocket::CloseSttServer()
{
	CWinTcpSocketServer::CloseServer();
}

//����Ǳ��ض˶�����ƴUnRegister����Ӧ��Զ�̶�
//�����Զ�̶ˣ�ƴLogout���������
// void CSttCloudServerSocket::OnSttScktClose(CSttSocketDataBase *pSttSckt)
// {
// 	CSttCloudServerSocketBase::OnSttScktClose(pSttSckt);
// }

CWinTcpSocketClient* CSttCloudServerSocket::CreateNewSocketClient()
{
	return new CSttCloudServerClientSocket();
}

void CSttCloudServerSocket::OnAccept(CWinTcpSocketClient *pSocket)
{
	CSttCloudServerClientSocket *pClientSocket = (CSttCloudServerClientSocket*)pSocket;

	int nPort = 0;
	char strIP[64];
	pClientSocket->get_RemoteIP_Port(strIP, &nPort);
	pClientSocket->m_strIPRemote = strIP;
	pClientSocket->m_nPortRemote = nPort;

	OnSttSktAccept(pClientSocket);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��%s��connect"), pClientSocket->m_strIPRemote);
}