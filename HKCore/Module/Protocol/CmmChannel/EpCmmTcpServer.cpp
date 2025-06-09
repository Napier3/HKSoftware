// ..\Module\Engine\EpCmmChannel\EpCmmTcpServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EpCmmTcpServer.h"
#include "EpCmmTcpServerChannel.h"
#include "EpCmmChannelCreateMngr.h"

// CEpCmmTcpServer

CEpCmmTcpServer::CEpCmmTcpServer()
{
}

CEpCmmTcpServer::~CEpCmmTcpServer()
{
}

BOOL CEpCmmTcpServer::CreateServer(const CString &strIP, UINT nPort, const CString &strBoardcastIP, long nMulticastPort)
{
	char pszBuffer[MAX_PATH];

	pszBuffer[0] = 0;

	CString_to_char(strIP, pszBuffer);
	CreateOwnSocket(pszBuffer, nPort);
	ListenOwnSocket();

	return TRUE;
}

BOOL CEpCmmTcpServer::CreateServer()
{
	return FALSE;
}

BOOL CEpCmmTcpServer::CloseServer(CExBaseObject *pChannel)
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

BOOL CEpCmmTcpServer::IsServerClosed()
{
	return (m_hSocket == NULL && m_hWnd == NULL);
}



// CEpCmmTcpServer ��Ա����

/*
����CEpCmmTcpClientChannel
����������������
	����TcpServer/CEpDeviceCmmChannel���ж�
	�ж�����:���ӵ�IP�����е�Client�ĵ�ַ��ͬ;���û��Client������û�����ӵ�EpDeviceCmmChannel
���͡����ӳɹ���Ϣ��
*/
void CEpCmmTcpServer::OnAccept()
{
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("CEpCmmTcpServer::OnAccept"));

	CEpCmmTcpServerClientChannel *pTcpServerClientChannel = new CEpCmmTcpServerClientChannel();
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

BOOL CEpCmmTcpServer::AddToServer(CExBaseObject *pTcpServerClientChannel)
{
	CEpCmmTcpServerClientChannel *p = (CEpCmmTcpServerClientChannel*)pTcpServerClientChannel;
	CEpCmmTcpServerChannel *pChannel = NULL;
	POS pos = GetHeadPosition();
	BOOL bIsClient = FALSE;

	while (pos != NULL)
	{
		pChannel = (CEpCmmTcpServerChannel*)GetNext(pos);
		bIsClient = pChannel->AddClient(p);

		if (bIsClient)
		{
			pChannel->OnConnectSucc();
			break;
		}
	}

	return bIsClient;
}

