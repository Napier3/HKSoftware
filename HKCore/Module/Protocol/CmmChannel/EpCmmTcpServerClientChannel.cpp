#include "StdAfx.h"
#include "EpCmmTcpServerChannel.h"
#include "EpDeviceCmmChannel.h"

CEpCmmTcpServerClientChannel::CEpCmmTcpServerClientChannel(void)
{
	SetReceiveBufferLength(1048576); //1024*1024  1M
}

CEpCmmTcpServerClientChannel::~CEpCmmTcpServerClientChannel(void)
{
}

void CEpCmmTcpServerClientChannel::Send(CExBaseObject *pPkgSend)
{
	m_nSendIndex++;

	CEpFrameBase *pSend = (CEpFrameBase*)pPkgSend;
	CCycleMemBuffer *pCycleBuffer = pSend->m_pBuffer;
	char *pBuffer = (char*)pCycleBuffer->GetBuffer();
	long nLen = pCycleBuffer->GetDataLength();

	if (SendOwnSocket(pBuffer, nLen) <= 0 )
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("TcpServer Send Failed"));
	}
	else
	{
		pSend->LogAndRecordProtocol();
	}
}

BOOL CEpCmmTcpServerClientChannel::IsConnectSuccessful()
{
	return (m_hSocket != NULL && ::IsWindow(m_hWnd));
}

long CEpCmmTcpServerClientChannel::OnReceive()
{
	m_nReceiveLen = 0;
	CEpCmmRcvSndTime *pEpCmmTime = new CEpCmmRcvSndTime();

	m_nReceiveLen = ReceiveOwnSocket(m_byteReceiveBuffer, CMM_RECEIVEBUFFER_LENGTH);
	pEpCmmTime->InitTime();
	AppendRcvBuffer(m_byteReceiveBuffer, m_nReceiveLen, pEpCmmTime);
	CEpCmmChannel::OnChannelReceive(pEpCmmTime);

	return m_nReceiveLen;

}

void CEpCmmTcpServerClientChannel::OnClose()
{

	CloseOwnSocket();
}
