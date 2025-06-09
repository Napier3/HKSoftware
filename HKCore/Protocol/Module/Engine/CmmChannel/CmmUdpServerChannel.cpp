#include "StdAfx.h"
#include "CmmUdpServerChannel.h"
#include "DeviceCmmChannel.h"
#include "../PpEngineThreadBase.h"
#include "../DeviceModel/CmmOnConnect.h"

CCmmUdpServerChannel::CCmmUdpServerChannel(void)
{
	m_pConfig = NULL;
	m_pNetServer = NULL;
	memset(&m_oSocketAddrIn, 0, sizeof(struct sockaddr_in));
}

CCmmUdpServerChannel::~CCmmUdpServerChannel(void)
{
}

BOOL CCmmUdpServerChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CCmmUdpServerConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	CCmmChannelCreateMngr::RegisterUdpServer(this);
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	return TRUE;
}

void CCmmUdpServerChannel::Send(CExBaseObject *pPkgSend)
{
	if (m_pNetServer != NULL)
	{
		m_nSendIndex++;
		((CCmmUdpServer*)m_pNetServer)->Send(pPkgSend);
	}
}

//
BOOL CCmmUdpServerChannel::Connect()
{
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	//启动OnConnect定义的过程
	CDeviceCmmChannel *pDeviceCmmChannel = (CDeviceCmmChannel*)GetParent();

	POS pos = m_pConfig->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	while (pos != NULL)
	{
		pObj = m_pConfig->GetNext(pos);
		if (pObj != NULL && pObj->GetClassID() == DMCLASSID_CMM_ONCONNECT)
		{
			((CPpEngineThreadBase*)pDeviceCmmChannel->m_pThread)->RunProcedure(((CCmmOnConnect*)pObj)->m_strText, NULL, TRUE);
		}
	}

	OnConnectFinished();

	return TRUE;
}

BOOL CCmmUdpServerChannel::DisConnect()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CCmmUdpServerChannel::DisConnect"));

	if (m_pNetServer != NULL)
	{
		m_pNetServer->CloseServer(this);
	}
	m_dwConnectState = CONNECT_STATE_NORMAL;

	return TRUE;
}


BOOL CCmmUdpServerChannel::IsConnectSuccessful()
{
	return CCmmChannel::IsConnectSuccessful();
}

//进行其他的链接
BOOL CCmmUdpServerChannel::ConnectOther()
{
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	//目前只考虑一个服务端、一个client端的情况
	CDeviceCmmChannel *pDeviceCmmChannel = (CDeviceCmmChannel*)GetParent();
	pDeviceCmmChannel->ConnetAllClient(this);

	OnConnectFinished();
	return TRUE;
}


void CCmmUdpServerChannel::OnChannelReceive(CCmmRcvSndTime *pCmmTime)
{
	if (IsConnectSuccessful())
	{

	}
	else
	{
		ConnectOther();//进行其他的连接

		//执行过程
	}

	CCmmChannel::OnChannelReceive(m_pCycleRcvBuffer, pCmmTime, NULL);
}

// void CCmmUdpServerChannel::OnChannelReceive(CCycleMemBuffer *pReceiveBuffer, CCmmRcvSndTime *pCmmTime, PCYCLEMEMBUFFERPOS pBufPos)
// {
// 	CCmmChannel::OnChannelReceive(pReceiveBuffer, pCmmTime, pBufPos);
// }

BOOL CCmmUdpServerChannel::IsCmmChannelExit()
{
	if (m_pNetServer == NULL)
	{
		return TRUE;
	}

	if (m_pNetServer->IsServerClosed())
	{
		CCmmChannelCreateMngr::UnRegisterServer(m_pNetServer);
		m_pNetServer = NULL;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CCmmUdpServerChannel::OnServerAccept(struct sockaddr_in *pSckAddr)
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

BOOL CCmmUdpServerChannel::TerminateChannel()
{
	return TRUE;
}