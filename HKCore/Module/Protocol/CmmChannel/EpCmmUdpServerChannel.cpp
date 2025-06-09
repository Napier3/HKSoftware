#include "StdAfx.h"
#include "EpCmmUdpServerChannel.h"
#include "EpDeviceCmmChannel.h"

CEpCmmUdpServerChannel::CEpCmmUdpServerChannel(void)
{
	m_pConfig = NULL;
	m_pNetServer = NULL;
	memset(&m_oSocketAddrIn, 0, sizeof(struct sockaddr_in));
}

CEpCmmUdpServerChannel::~CEpCmmUdpServerChannel(void)
{
}

BOOL CEpCmmUdpServerChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CEpCmmUdpServerConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	CEpCmmChannelCreateMngr::RegisterUdpServer(this);
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	return TRUE;
}

void CEpCmmUdpServerChannel::Send(CExBaseObject *pPkgSend)
{
	if (m_pNetServer != NULL)
	{
		m_nSendIndex++;
		((CEpCmmUdpServer*)m_pNetServer)->Send(pPkgSend);
	}
}

//
BOOL CEpCmmUdpServerChannel::Connect()
{
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	//启动OnConnect定义的过程
	CEpDeviceCmmChannel *pEpDeviceCmmChannel = (CEpDeviceCmmChannel*)GetParent();

	POS pos = m_pConfig->GetHeadPosition();
	CExBaseObject *pObj = NULL;
// 	while (pos != NULL)
// 	{
// 		pObj = m_pConfig->GetNext(pos);
// 		if (pObj != NULL && pObj->GetClassID() == EPEPCLASSID_CMM_ONCONNECT)
// 		{
// 			((CEpEngineThread*)pEpDeviceCmmChannel->m_pThread)->RunProcedure(((CEpCmmOnConnect*)pObj)->m_strText, NULL);
// 		}
// 	}

	OnConnectFinished();

	return TRUE;
}

BOOL CEpCmmUdpServerChannel::DisConnect()
{
	m_pNetServer->CloseServer(this);
	return TRUE;
}


BOOL CEpCmmUdpServerChannel::IsConnectSuccessful()
{
	return CEpCmmChannel::IsConnectSuccessful();
}

//进行其他的链接
BOOL CEpCmmUdpServerChannel::ConnectOther()
{
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	//目前只考虑一个服务端、一个client端的情况
	CEpDeviceCmmChannel *pEpDeviceCmmChannel = (CEpDeviceCmmChannel*)GetParent();
	pEpDeviceCmmChannel->ConnetAllClient(this);

	OnConnectFinished();
	return TRUE;
}


void CEpCmmUdpServerChannel::OnChannelReceive(CEpCmmRcvSndTime *pEpCmmTime)
{
	if (IsConnectSuccessful())
	{

	}
	else
	{
		ConnectOther();//进行其他的连接

		//执行过程
	}

	CEpCmmChannel::OnChannelReceive(pEpCmmTime);
}


BOOL CEpCmmUdpServerChannel::IsEpCmmChannelExit()
{
	if (m_pNetServer == NULL)
	{
		return TRUE;
	}

	if (m_pNetServer->IsServerClosed())
	{
		CEpCmmChannelCreateMngr::UnRegisterServer(m_pNetServer);
		m_pNetServer = NULL;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CEpCmmUdpServerChannel::OnServerAccept(struct sockaddr_in *pSckAddr)
{
	if (m_pConfig->m_strClientIP.GetLength() >= 7)
	{
		char pszIPBuffer[40];
		CString_to_char(m_pConfig->m_strClientIP, pszIPBuffer);

		sockaddr_in sktBroadCast;
		sktBroadCast.sin_addr.S_un.S_addr=inet_addr(pszIPBuffer);//广播地址

		if (sktBroadCast.sin_addr.S_un.S_addr == pSckAddr->sin_addr.S_un.S_addr)
		{
			m_oSocketAddrIn = *pSckAddr;
		}
	}
	else
	{
		m_oSocketAddrIn = *pSckAddr;
	}
}

