// ..\Module\Engine\CmmChannel\CmmTcpServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CmmTcpServer.h"
#include "CmmTcpServerChannel.h"
#include "CmmChannelCreateMngr.h"

// CCmmTcpServer

CCmmTcpServer::CCmmTcpServer()
{
}

CCmmTcpServer::~CCmmTcpServer()
{
}

BOOL CCmmTcpServer::CreateServer(const CString &strIP, UINT nPort, const CString &strBoardcastIP, long nMulticastPort)
{
	char pszBuffer[MAX_PATH];

	pszBuffer[0] = 0;
	m_strIP = strIP;
    m_nPort = nPort;
	BOOL bTrue = FALSE;
	CString_to_char(strIP, pszBuffer);

	bTrue = CWinTcpSocketServer::CreateServer(pszBuffer, nPort);

	return bTrue;
}

BOOL CCmmTcpServer::CreateServer()
{
	return FALSE;
}

BOOL CCmmTcpServer::CloseServer(CExBaseObject *pChannel)
{
	POS pos = CExBaseList::Find(pChannel);

	if (pos != NULL)
	{
		RemoveAt(pos);
	}

	if (GetCount() == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Close TCP Server %s %d"), m_strIP.GetString(), m_nPort);

		Close();
	}

	return TRUE;
}

BOOL CCmmTcpServer::IsServerClosed()
{
	//2018-2-8
	return (m_hSocket == NULL);// && m_hWnd == NULL);
}



// CCmmTcpServer ��Ա����

/*
����CCmmTcpClientChannel
����������������
	����TcpServer/CDeviceCmmChannel���ж�
	�ж�����:���ӵ�IP�����е�Client�ĵ�ַ��ͬ;���û��Client������û�����ӵ�DeviceCmmChannel
���͡����ӳɹ���Ϣ��
*/

CWinTcpSocketClient* CCmmTcpServer::CreateNewSocketClient()
{
	CCmmTcpServerClientChannel *pTcpServerClientChannel = new CCmmTcpServerClientChannel();
	return pTcpServerClientChannel;
}
/*

void CCmmTcpServer::OnAccept()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CCmmTcpServer::OnAccept"));

	CCmmTcpServerClientChannel *pTcpServerClientChannel = new CCmmTcpServerClientChannel();
	BOOL bIsClient = FALSE;
	
	//����ʧ�ܣ��رղ�ɾ��
	if (AcceptOwnSocket(*pTcpServerClientChannel))
	{
		bIsClient = AddToServer(pTcpServerClientChannel);
	}
	
	if (!bIsClient)
	{
		pTcpServerClientChannel->Close();
		delete pTcpServerClientChannel;
	}
}
// 
// BOOL CCmmTcpServer::AcceptOwnSocket(CCmmTcpServerClientChannel& rConnectedSocket, SOCKADDR* lpSockAddr , int* lpSockAddrLen )
// {
// 	return CThreadSocket::AcceptOwnSocket(rConnectedSocket, lpSockAddr, lpSockAddrLen);
// 
// 	int nLen = sizeof(SOCKADDR);
// 	sockaddr_in addrSocket;	
// 	rConnectedSocket.m_hSocket = accept(m_hSocket, (sockaddr*)&addrSocket, &nLen);
// 
// 	if (rConnectedSocket.m_hSocket == INVALID_SOCKET)
// 	{
// 		return FALSE;
// 	}
// 
// 	rConnectedSocket.m_nIPAddr = addrSocket.sin_addr.S_un.S_addr;
// 	rConnectedSocket.m_nSocketPort = addrSocket.sin_port;
// 
// 	if (WSAAsyncSelect(rConnectedSocket.m_hSocket,m_hWnd,WM_TCPIP,FD_READ|FD_WRITE|FD_ACCEPT))
// 	{
// 		rConnectedSocket.Close();
// 	}
// 
// 	return TRUE;
// 
// }
*/

void CCmmTcpServer::OnAccept(CWinTcpSocketClient *pSocket)
{
	CCmmTcpServerClientChannel *pTcpServerClientChannel = (CCmmTcpServerClientChannel*)pSocket;
	BOOL bIsClient = FALSE;

	bIsClient = AddToServer(pTcpServerClientChannel);
	pTcpServerClientChannel->CreateRcvThread();

	//����ʧ�ܣ��رղ�ɾ��
	if (!bIsClient)
	{
		pTcpServerClientChannel->Close();
		delete pTcpServerClientChannel;
	}
}

BOOL CCmmTcpServer::AddToServer(CExBaseObject *pTcpServerClientChannel)
{
	CCmmTcpServerClientChannel *p = (CCmmTcpServerClientChannel*)pTcpServerClientChannel;
	CCmmTcpServerChannel *pChannel = NULL;
	POS pos = GetHeadPosition();
	BOOL bIsClient = FALSE;

	while (pos != NULL)
	{
		pChannel = (CCmmTcpServerChannel*)GetNext(pos);
		bIsClient = pChannel->AddClient(p);

		if (bIsClient)
		{
			pChannel->OnConnectSucc();
			break;
		}
	}

	return bIsClient;
}

// long CCmmTcpServer::OnReceive(SOCKET s)
// {
// 	CCmmTcpServerChannel *pChannel = (CCmmTcpServerChannel *)GetHead();
// 	if (pChannel == NULL)
// 	{
// 		return 0;
// 	}
// 
// 	pChannel->OnReceive(s);
// 	return 0;
// }

