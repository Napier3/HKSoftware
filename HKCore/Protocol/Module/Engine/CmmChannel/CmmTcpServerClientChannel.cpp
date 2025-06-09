#include "StdAfx.h"
#include "CmmTcpServerChannel.h"
#include "DeviceCmmChannel.h"
#include "../PpEngineThreadBase.h"
#include "../DeviceModel/CmmOnConnect.h"

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

	if (CWinTcpSocket::Send(pBuffer, nLen) <= 0 )
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,  _T("TcpServer Send Failed"));
	}
	else
	{
		pSend->SetSendState(TRUE);
		pSend->LogAndRecordProtocol();
	}
}

BOOL CCmmTcpServerClientChannel::IsConnectSuccessful()
{
	return (m_hSocket != NULL);
}

long CCmmTcpServerClientChannel::OnReceive(BYTE *pRcvBuf, int iLen)
{
	ResetOffsetDataFillBeginPosition();

	long nFillBeginPos = m_pCycleRcvBuffer->GetDataFillBeginPosition();
	CCmmRcvSndTime *pCmmTime = new CCmmRcvSndTime();
	pCmmTime->InitTime();

	LogReceivePackage(m_pszPpLogProtocol, pRcvBuf, iLen);
	m_pCycleRcvBuffer->AppendBuffer(pRcvBuf, iLen);

	m_pCycleRcvBuffer->GetBufferPos(nFillBeginPos, m_nReceiveLen, pCmmTime->m_oCycleBufferPos);
	CCmmChannel::OnChannelReceive(m_pCycleRcvBuffer, pCmmTime, NULL);

	//return m_nReceiveLen;
	return iLen;
}

void CCmmTcpServerClientChannel::OnClose()
{
	CCmmTcpServerChannel *pServer = (CCmmTcpServerChannel*)CBaseObject::GetParent();
	pServer->OnCmmChannelClose(this);
	pServer->RemoveClient(this);

	//CloseOwnSocket();
}

BOOL CCmmTcpServerClientChannel::TerminateChannel()
{
	return TRUE;
}