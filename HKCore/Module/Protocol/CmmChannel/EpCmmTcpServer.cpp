// ..\Module\Engine\EpCmmChannel\EpCmmTcpServer.cpp : 实现文件
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



// CEpCmmTcpServer 成员函数

/*
创建CEpCmmTcpClientChannel
遍历链表，分配连接
	根据TcpServer/CEpDeviceCmmChannel来判断
	判断依据:连接的IP与其中的Client的地址相同;如果没有Client则分配给没有连接的EpDeviceCmmChannel
发送“连接成功消息”
*/
void CEpCmmTcpServer::OnAccept()
{
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("CEpCmmTcpServer::OnAccept"));

	CEpCmmTcpServerClientChannel *pTcpServerClientChannel = new CEpCmmTcpServerClientChannel();
	BOOL bIsClient = FALSE;
	
	//接受失败，关闭并删除
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

