#include "StdAfx.h"
#include "CmmTcpServerChannel.h"
#include "DeviceCmmChannel.h"
#include "..\PpEngineThread.h"
#include "..\DeviceModel\CmmOnConnect.h"

CCmmTcpServerChannel::CCmmTcpServerChannel(void)
{
	m_pConfig = NULL;
	m_pNetServer = NULL;
	m_bPostConnectFinishMsgAfterAccept = FALSE;
}

CCmmTcpServerChannel::~CCmmTcpServerChannel(void)
{
}

BOOL CCmmTcpServerChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CCmmTcpServerConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	CCmmTcpServer *pTcpServer = CCmmChannelCreateMngr::RegisterTcpServer(this);

	if (pTcpServer->m_bCreateSuccess)
	{
		m_dwConnectState = CONNECT_STATE_SUCCESSFUL;
	}
	else
	{
		m_dwConnectState = CONNECT_STATE_FAILED;
	}

	m_bPostConnectFinishMsgAfterAccept = m_pConfig->m_bPostConnectFinishMsgAfterAccept;

	return (m_dwConnectState == CONNECT_STATE_SUCCESSFUL);
}

void CCmmTcpServerChannel::Send(CExBaseObject *pPkgSend)
{
	m_nSendIndex++;

	CPpPackageSend *pSend = (CPpPackageSend*)pPkgSend;
	
	if (pSend->m_pChannel == NULL)
	{
		SendToAll(pSend);
	}
	else
	{
		//SendTo(pSend);
		SendToAll(pSend);
	}
}

void CCmmTcpServerChannel::SendToAll(CExBaseObject *pPkgSend)
{
	CCmmTcpServerClientChannel *p = NULL;
	POS pos = m_oTcpServerClientChannels.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCmmTcpServerClientChannel*)m_oTcpServerClientChannels.GetNext(pos);
		p->Send(pPkgSend);
	}
}

void CCmmTcpServerChannel::SendTo(CExBaseObject *pPkgSend)
{
	CCmmTcpServerClientChannel *p = NULL;
	POS pos = m_oTcpServerClientChannels.GetHeadPosition();
	BOOL bSend = FALSE;
	CPpPackageSend *pSend = (CPpPackageSend*)pPkgSend;

	while (pos != NULL)
	{
		p = (CCmmTcpServerClientChannel*)m_oTcpServerClientChannels.GetNext(pos);

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

BOOL CCmmTcpServerChannel::Connect()
{
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	//执行过程
// 	CDeviceCmmChannel *pDeviceCmmChannel = (CDeviceCmmChannel*)(CCmmChannel::GetParent());
// 
// 	CMM_OnChannelConnectSucc(m_pConfig, pDeviceCmmChannel->m_pThread);
// 	POS pos = m_pConfig->GetHeadPosition();
// 	CExBaseObject *pObj = NULL;
// 	while (pos != NULL)
// 	{
// 		pObj = m_pConfig->GetNext(pos);
// 		if (pObj != NULL && pObj->GetClassID() == DMCLASSID_CMM_ONCONNECT)
// 		{
// 			((CPpEngineThread*)pDeviceCmmChannel->m_pThread)->RunProcedure(((CCmmOnConnect*)pObj)->m_strText, NULL);
// 		}
// 	}

	if (!m_bPostConnectFinishMsgAfterAccept)
	{
		OnConnectFinished();
	}

	return TRUE;
}

BOOL CCmmTcpServerChannel::DisConnect()
{
	if (m_pNetServer != NULL)
	{
		m_pNetServer->CloseServer(this);
	}

	CCmmTcpServerClientChannel *p = NULL;
	POS pos = m_oTcpServerClientChannels.GetHeadPosition();
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CCmmTcpServerClientChannel*)m_oTcpServerClientChannels.GetNext(pos);
		p->Close();
		m_oTcpServerClientChannels.RemoveAt(posPrev);
		delete p;
		p = NULL;
	}

	m_dwConnectState = CONNECT_STATE_NORMAL;

	return TRUE;
}

BOOL CCmmTcpServerChannel::IsConnectSuccessful()
{
	return ( /*(GetCount() > 0)  &&*/ (m_dwConnectState == CONNECT_STATE_SUCCESSFUL) );
}

 long CCmmTcpServerChannel::OnReceive(SOCKET s)
 {
 	m_nReceiveLen = 0;
 	CCmmRcvSndTime *pCmmTime = new CCmmRcvSndTime();
 
#ifdef _use_CMemBufferList
#else
	if (m_pCycleRcvBuffer != NULL)
	{
		BYTE *pBuffer = m_pCycleRcvBuffer->GetBuffer();
		long nLen = 0;

		if (pBuffer != NULL)
		{
			long nFillBeginPos = m_pCycleRcvBuffer->GetDataFillBeginPosition();

			while (TRUE)
			{
				nLen = ReceiveOwnSocket(m_byteReceiveBuffer, CMM_RECEIVEBUFFER_LENGTH);
				pCmmTime->InitTime();

				if (nLen <= 0)
				{
					break;
				}

				LogReceivePackage(m_pszPpLogProtocol, m_byteReceiveBuffer+m_nReceiveLen, nLen);
				m_nReceiveLen += nLen;
				m_pCycleRcvBuffer->AppendBuffer(m_byteReceiveBuffer, nLen);
			}

			if (m_nReceiveLen > 0)
			{
				m_pCycleRcvBuffer->GetBufferPos(nFillBeginPos, m_nReceiveLen, pCmmTime->m_oCycleBufferPos);
				CCmmChannel::OnChannelReceive(m_pCycleRcvBuffer, pCmmTime, NULL);
			}			

			return m_nReceiveLen;
		}
	}
#endif

 	m_nReceiveLen = ReceiveOwnSocket(m_byteReceiveBuffer, CMM_RECEIVEBUFFER_LENGTH);
 	pCmmTime->InitTime();
 	AppendRcvBuffer(m_byteReceiveBuffer, m_nReceiveLen, pCmmTime);

 	CCmmChannel::OnChannelReceive(pCmmTime);
 
 	return m_nReceiveLen;
 }

void CCmmTcpServerChannel::OnConnectSucc()
{
	if (m_bPostConnectFinishMsgAfterAccept)
	{
		OnConnectFinished();
	}

	CDeviceCmmChannel *pDeviceCmmChannel = (CDeviceCmmChannel*)(CCmmChannel::GetParent());

	CMM_OnChannelConnectSucc(m_pConfig, pDeviceCmmChannel->m_pThread);
}

// void CCmmTcpServerChannel::OnClose()
// {
// 	CLogPrint::LogString(XLOGLEVEL_TRACE, L"CCmmTcpServerChannel::OnClose");
// 
// 	CloseOwnSocket();
// }

BOOL CCmmTcpServerChannel::IsCmmChannelExit()
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

// BOOL CCmmTcpServerChannel::IsClientTrue()
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
//同时整理通讯的配置参数情况
BOOL CCmmTcpServerChannel::AddClient(CCmmTcpServerClientChannel *pChannel)
{
	m_listAllRemoveChannels.DeleteAll();

	BOOL bIsCleint = FALSE;
	POS pos = m_oTcpServerClientChannels.GetHeadPosition();
	POS posPrev = pos;
	CCmmTcpServerClientChannel *p = NULL;

	while (pos != NULL)
	{
		pos = posPrev;
		p = (CCmmTcpServerClientChannel*)m_oTcpServerClientChannels.GetNext(pos);

		if (p->GetClassID() == CMMCLASSID_TCP_SERVER_CLIENT_CHANNEL)
		{
			if (p->IsSame(pChannel))
			{
				m_oTcpServerClientChannels.RemoveAt(posPrev);
				p->Close();
				delete p;
				p = NULL;
			}
		}

		posPrev = pos;
	}

	((CBaseObject*)pChannel)->SetParent(this);
	m_oTcpServerClientChannels.AddTail(pChannel);

	return TRUE;
}

BOOL CCmmTcpServerChannel::RemoveClient(CCmmTcpServerClientChannel *pChannel)
{
	BOOL bIsCleint = FALSE;
	POS pos = m_oTcpServerClientChannels.GetHeadPosition();
	POS posPrev = pos;
	CCmmTcpServerClientChannel *p = NULL;

	while (pos != NULL)
	{
		pos = posPrev;
		p = (CCmmTcpServerClientChannel*)m_oTcpServerClientChannels.GetNext(pos);

		if (p == pChannel)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Remove TCP Client %X  %d"), pChannel->m_nIPAddr, pChannel->m_nSocketPort);
			m_oTcpServerClientChannels.RemoveAt(posPrev);
			//p->Close();
			//delete p;
			m_listAllRemoveChannels.AddTail(p);
		}

		posPrev = pos;
	}

	return TRUE;
}

BOOL CCmmTcpServerChannel::TerminateChannel()
{
	return TRUE;
}
