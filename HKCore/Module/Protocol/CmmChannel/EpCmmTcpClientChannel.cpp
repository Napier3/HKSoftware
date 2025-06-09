#include "StdAfx.h"
#include "EpCmmTcpClientChannel.h"
#include "EpDeviceCmmChannel.h"

CEpCmmTcpClientChannel::CEpCmmTcpClientChannel(void)
{
	m_pConfig = NULL;
}

CEpCmmTcpClientChannel::~CEpCmmTcpClientChannel(void)
{
	
}


BOOL CEpCmmTcpClientChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CEpCmmTcpClientConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	return TRUE;
}

void CEpCmmTcpClientChannel::Send(CExBaseObject *pPkgSend)
{
	m_nSendIndex++;

	CEpFrameBase *pSend = (CEpFrameBase*)pPkgSend;
	CCycleMemBuffer *pCycleBuffer = pSend->m_pBuffer;
	char *pBuffer = (char*)pCycleBuffer->GetBuffer();
	long nLen = pCycleBuffer->GetDataLength();
	pSend->LogAndRecordProtocol();

	int iReturn = SendOwnSocket(pBuffer, nLen);
}


BOOL CEpCmmTcpClientChannel::Connect()
{
	ASSERT (m_pConfig != NULL);

	if (m_pConfig->m_strRemoteIP.GetLength() < 7)
	{
		return FALSE;
	}

	char pszBuffer[MAX_PATH];

	pszBuffer[0] = 0;

	CString_to_char(m_pConfig->m_strLocalIP, pszBuffer);

	if (!CreateOwnSocket(pszBuffer, m_pConfig->m_nLocalPort))
	{
		// 如果创建Socket失败
		CloseOwnSocket();
		m_dwConnectState = CONNECT_STATE_FAILED;
	}
	else
	{
		CString_to_char(m_pConfig->m_strRemoteIP, pszBuffer);

		if (!ConnectOwnSocket(pszBuffer, m_pConfig->m_nRemotePort))
		{
			CloseOwnSocket();
			m_dwConnectState = CONNECT_STATE_FAILED;
		}
		else
		{
			m_dwConnectState = CONNECT_STATE_SUCCESSFUL;
		}
	}

	if (IsConnectSuccessful())
	{
		//执行过程
		CEpDeviceCmmChannel *pEpDeviceCmmChannel = (CEpDeviceCmmChannel*)(CEpCmmChannel::GetParent());

		CMM_OnChannelConnectSucc(m_pConfig, pEpDeviceCmmChannel->m_pThread);
// 		POS pos = m_pConfig->GetHeadPosition();
// 		CExBaseObject *pObj = NULL;
// 		while (pos != NULL)
// 		{
// 			pObj = m_pConfig->GetNext(pos);
// 			if (pObj != NULL && pObj->GetClassID() == EPCLASSID_CMM_ONCONNECT)
// 			{
// 				((CEpEngineThread*)pEpDeviceCmmChannel->m_pThread)->RunProcedure(((CEpCmmOnConnect*)pObj)->m_strText, NULL);
// 			}
// 		}
		
	}

	OnConnectFinished();

	return IsConnectSuccessful();
}

BOOL CEpCmmTcpClientChannel::DisConnect()
{
	CloseOwnSocket();
	DestroyWindow();
	return TRUE;
}


BOOL CEpCmmTcpClientChannel::IsConnectSuccessful()
{
	return CEpCmmChannel::IsConnectSuccessful();
}

long CEpCmmTcpClientChannel::OnReceive()
{
	m_nReceiveLen = 0;

	CEpCmmRcvSndTime *pEpCmmTime = new CEpCmmRcvSndTime();
	BYTE *pBuffer = m_byteReceiveBuffer;

	while (TRUE)
	{
		long nLen = ReceiveOwnSocket(pBuffer, CMM_RECEIVEBUFFER_LENGTH);
		pEpCmmTime->InitTime();

		if (nLen <= 0)
		{
			break;
		}

		m_nReceiveLen += nLen;
		pBuffer += nLen;

		if (CMM_RECEIVEBUFFER_LENGTH <= m_nReceiveLen)
		{
			AppendRcvBuffer(m_byteReceiveBuffer, m_nReceiveLen, pEpCmmTime);
			CEpCmmChannel::OnChannelReceive(pEpCmmTime);
			m_nReceiveLen = 0;
			pBuffer = m_byteReceiveBuffer;
			pEpCmmTime = new CEpCmmRcvSndTime();
		}
	}

	if (m_nReceiveLen > 0)
	{
		AppendRcvBuffer(m_byteReceiveBuffer, m_nReceiveLen, pEpCmmTime);
		CEpCmmChannel::OnChannelReceive(pEpCmmTime);
	}		
	else
	{
		delete pEpCmmTime;
	}

	return m_nReceiveLen;
}

BOOL CEpCmmTcpClientChannel::IsEpCmmChannelExit()
{
	return (m_hSocket == NULL && m_hWnd == NULL);
}

