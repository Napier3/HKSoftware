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

	CString_to_char(strIP, pszBuffer);
	CreateOwnSocket(pszBuffer, nPort);
	ListenOwnSocket();

	return TRUE;
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
		CloseOwnSocket();
		DestroyWindow();
	}

	return TRUE;
}

BOOL CCmmTcpServer::IsServerClosed()
{
	return (m_hSocket == NULL && m_hWnd == NULL);
}



// CCmmTcpServer ��Ա����

/*
����CCmmTcpClientChannel
����������������
	����TcpServer/CDeviceCmmChannel���ж�
	�ж�����:���ӵ�IP�����е�Client�ĵ�ַ��ͬ;���û��Client������û�����ӵ�DeviceCmmChannel
���͡����ӳɹ���Ϣ��
*/
void CCmmTcpServer::OnAccept()
{
	CLogPrint::LogString(LOGLEVEL_TRACE, L"CCmmTcpServer::OnAccept");

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

long CCmmTcpServer::OnReceive(SOCKET s)
{
	CCmmTcpServerChannel *pChannel = (CCmmTcpServerChannel *)GetHead();
	if (pChannel == NULL)
	{
		return 0;
	}

	pChannel->OnReceive(s);
	return 0;
}

