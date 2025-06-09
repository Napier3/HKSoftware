#include "StdAfx.h"
#include "EpCmmTcpServerChannel.h"
#include "EpDeviceCmmChannel.h"

CEpCmmTcpServerChannel::CEpCmmTcpServerChannel(void)
{
	m_pConfig = NULL;
	m_pNetServer = NULL;
}

CEpCmmTcpServerChannel::~CEpCmmTcpServerChannel(void)
{
}

BOOL CEpCmmTcpServerChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CEpCmmTcpServerConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	CEpCmmChannelCreateMngr::RegisterTcpServer(this);
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	return TRUE;
}

void CEpCmmTcpServerChannel::Send(CExBaseObject *pPkgSend)
{
	m_nSendIndex++;

	CEpFrameBase *pSend = (CEpFrameBase*)pPkgSend;
	
	if (pSend->m_pChannel == NULL)
	{
		SendToAll(pSend);
	}
	else
	{
		SendTo(pSend);
	}
}

void CEpCmmTcpServerChannel::SendToAll(CExBaseObject *pPkgSend)
{
	CEpCmmTcpServerClientChannel *p = NULL;
	POS pos = m_oTcpServerClientChannels.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpCmmTcpServerClientChannel*)m_oTcpServerClientChannels.GetNext(pos);
		p->Send(pPkgSend);
	}
}

void CEpCmmTcpServerChannel::SendTo(CExBaseObject *pPkgSend)
{
	CEpCmmTcpServerClientChannel *p = NULL;
	POS pos = m_oTcpServerClientChannels.GetHeadPosition();
	BOOL bSend = FALSE;
	CEpFrameBase *pSend = (CEpFrameBase*)pPkgSend;

	while (pos != NULL)
	{
		p = (CEpCmmTcpServerClientChannel*)m_oTcpServerClientChannels.GetNext(pos);

		if (p == pSend->m_pChannel)
		{
			bSend = TRUE;
			p->Send(pPkgSend);
			break;
		}
	}

	if (!bSend)
	{
		SendToAll(pPkgSend);
	}
}

BOOL CEpCmmTcpServerChannel::Connect()
{
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	//执行过程
// 	CEpDeviceCmmChannel *pEpDeviceCmmChannel = (CEpDeviceCmmChannel*)(CEpCmmChannel::GetParent());
// 
// 	CMM_OnChannelConnectSucc(m_pConfig, pEpDeviceCmmChannel->m_pThread);
// 	POS pos = m_pConfig->GetHeadPosition();
// 	CExBaseObject *pObj = NULL;
// 	while (pos != NULL)
// 	{
// 		pObj = m_pConfig->GetNext(pos);
// 		if (pObj != NULL && pObj->GetClassID() == EPCLASSID_CMM_ONCONNECT)
// 		{
// 			((CEpEngineThread*)pEpDeviceCmmChannel->m_pThread)->RunProcedure(((CEpCmmOnConnect*)pObj)->m_strText, NULL);
// 		}
// 	}

	OnConnectFinished();
	return TRUE;
}

BOOL CEpCmmTcpServerChannel::DisConnect()
{
	m_pNetServer->CloseServer(this);
	CEpCmmTcpServerClientChannel *p = NULL;
	POS pos = m_oTcpServerClientChannels.GetHeadPosition();
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CEpCmmTcpServerClientChannel*)m_oTcpServerClientChannels.GetNext(pos);
		p->Close();
		m_oTcpServerClientChannels.RemoveAt(posPrev);
		delete p;
	}

	return TRUE;
}

BOOL CEpCmmTcpServerChannel::IsConnectSuccessful()
{
	return ( /*(GetCount() > 0)  &&*/ (m_dwConnectState == CONNECT_STATE_SUCCESSFUL) );
}

void CEpCmmTcpServerChannel::OnConnectSucc()
{
	CEpDeviceCmmChannel *pEpDeviceCmmChannel = (CEpDeviceCmmChannel*)(CEpCmmChannel::GetParent());

	CMM_OnChannelConnectSucc(m_pConfig, pEpDeviceCmmChannel->m_pThread);
}

BOOL CEpCmmTcpServerChannel::IsEpCmmChannelExit()
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

// BOOL CEpCmmTcpServerChannel::IsClientTrue()
// {
// 	if (m_pConfig->m_strClientIP.GetLength() > 7)
// 	{
// 		char pszIP[40];
// 		CString_to_char(m_pConfig->m_strClientIP, pszIP);
// 		sockaddr_in sktBroadCast;
// 		sktBroadCast.sin_addr.S_un.S_addr=inet_addr(pszIP);//广播地址
// 
// 		if (sktBroadCast.sin_addr.S_un.S_addr == m_nIPAddr)
// 		{
// 			return TRUE;
// 		}
// 		else
// 		{
// 			return FALSE;
// 		}
// 	}
// 	else
// 	{
// 		return TRUE;
// 	}
// }

//添加为TcpServer的客户端
//目前只考虑单设备，多设备情况再考虑
//同时整理通讯的配置参数情况
BOOL CEpCmmTcpServerChannel::AddClient(CEpCmmTcpServerClientChannel *pChannel)
{
	BOOL bIsCleint = FALSE;
	POS pos = m_oTcpServerClientChannels.GetHeadPosition();
	POS posPrev = pos;
	CEpCmmTcpServerClientChannel *p = NULL;

	while (pos != NULL)
	{
		pos = posPrev;
		p = (CEpCmmTcpServerClientChannel*)m_oTcpServerClientChannels.GetNext(pos);

		if (p->GetClassID() == EPCMMCLASSID_TCP_SERVER_CLIENT_CHANNEL)
		{
			if (p->IsSame(pChannel))
			{
				m_oTcpServerClientChannels.RemoveAt(pos);
				p->Close();
				delete p;
			}
		}

		posPrev = pos;
	}

	((CBaseObject*)pChannel)->SetParent(this);
	m_oTcpServerClientChannels.AddTail(pChannel);

	return TRUE;
}

