#include "StdAfx.h"
#include "CmmTcpServerChannel.h"
#include "DeviceCmmChannel.h"
#include "..\PpEngineThread.h"
#include "..\DeviceModel\CmmOnConnect.h"

#include "CmmTcpServerChannel.h"

CCmmTcpServerClientChannel::CCmmTcpServerClientChannel(void)
{
	SetReceiveBufferLength(1048576); //1024*1024  1M
}

CCmmTcpServerClientChannel::~CCmmTcpServerClientChannel(void)
{
}

void CCmmTcpServerClientChannel::Send(CExBaseObject *pPkgSend)
{
	m_nSendIndex++;

	CPpPackageSend *pSend = (CPpPackageSend*)pPkgSend;
	char *pBuffer = (char*)pSend->m_oBuffer.GetBuffer();
	long nLen = pSend->m_oBuffer.GetDataLength();

	if (SendOwnSocket(pBuffer, nLen) <= 0 )
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, L"TcpServer Send Failed");
	}
	else
	{
		pSend->LogAndRecordProtocol();
	}
}

BOOL CCmmTcpServerClientChannel::IsConnectSuccessful()
{
	return (m_hSocket != NULL && ::IsWindow(m_hWnd));
}


long CCmmTcpServerClientChannel::OnReceive()
{
	m_nReceiveLen = 0;
	CCmmRcvSndTime *pCmmTime = new CCmmRcvSndTime();

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

	m_nReceiveLen = ReceiveOwnSocket(m_byteReceiveBuffer, CMM_RECEIVEBUFFER_LENGTH);
	pCmmTime->InitTime();
	AppendRcvBuffer(m_byteReceiveBuffer, m_nReceiveLen, pCmmTime);
	CCmmChannel::OnChannelReceive(pCmmTime);

	return m_nReceiveLen;

}

void CCmmTcpServerClientChannel::OnClose()
{
	CCmmTcpServerChannel *pServer = (CCmmTcpServerChannel*)CBaseObject::GetParent();

	pServer->RemoveClient(this);

	CloseOwnSocket();
}

BOOL CCmmTcpServerClientChannel::TerminateChannel()
{
	return TRUE;
}