#include "StdAfx.h"
#include "EpCmmChannel.h"
#include "config\EpCmmConfigBase.h"
#include "EpDeviceCmmChannel.h"

#include "Iphlpapi.h"


void CEpCmmRcvSndTime::Log()
{
	
}

CEpCmmRcvSndTime* CEpCmmRcvSndTimeMngr::FindTimeByPos(long nPos)
{
	POS pos = GetHeadPosition();
	CEpCmmRcvSndTime *pTime = NULL;
	CEpCmmRcvSndTime *pFind = NULL;

	while (pos != NULL)
	{
		pTime = (CEpCmmRcvSndTime*)GetNext(pos);

		if (pTime->IsInBufferPos(nPos))
		{
			pFind = pTime;
			break;
		}
	}

	return pFind;
}

void CEpCmmRcvSndTimeMngr::DeletePrev(CEpCmmRcvSndTime *pTime)
{
// 	long nCount = GetCount();
// 
// 	if (nCount < 100)
// 	{
// 		return;
// 	}
// 
// 	long nIndex = nCount - 100;
// 	while (nIndex > 0)
// 	{
// 		DeleteHead();
// 	}

	CEpCmmRcvSndTime *p = (CEpCmmRcvSndTime*)GetHead();

	while (p != pTime)
	{
		DeleteHead();
		p = (CEpCmmRcvSndTime*)GetHead();
	}
}

CEpCmmChannel::CEpCmmChannel(void)
{
	m_dwConnectState = CONNECT_STATE_NORMAL;
	m_nSendIndex = 0;
	m_nReceiveLen = 0;
	m_nParserBeginPos = 0;
	m_nSendSpyBeginPos = 0;						//缓冲区监视开始的位置
	m_nReceiveSpyBeginPos = 0;						//缓冲区监视开始的位置
}

CEpCmmChannel::~CEpCmmChannel(void)
{
	RemoveAll();
	FreeBuffer();
}

void CEpCmmChannel::FreeBuffer()
{
	FreeReceiveBuffer();
	FreeSendBuffer();
}

void CEpCmmChannel::FreeReceiveBuffer()
{
	m_oCycleRcvBuffer.DeleteAll();
}

void CEpCmmChannel::FreeSendBuffer()
{
	if (m_bAttachSendBuffer)
	{
		m_pSendBuffer = NULL;
		m_bAttachSendBuffer = FALSE;
	}
	else
	{
		delete m_pSendBuffer;
		m_pSendBuffer = NULL;
	}
}

void CEpCmmChannel::AttacthReceiveBuffer(CCycleMemBuffer *pBuffer)
{
	FreeReceiveBuffer();
}

void CEpCmmChannel::AttacthSendBuffer(CCycleMemBuffer *pBuffer)
{
	FreeSendBuffer();
	m_bAttachSendBuffer = TRUE;
	m_pSendBuffer = pBuffer;
}

// void CEpCmmChannel::SetReceiveBufferLength(long nLen)
// {
// 	FreeReceiveBuffer();
// }

void CEpCmmChannel::SetSendBufferLength(long nLen)
{
	FreeSendBuffer();
	m_pSendBuffer = new CCycleMemBuffer();
	m_pSendBuffer->SetBufferLength(nLen);
}

CBaseObject* CEpCmmChannel::GetEpDeviceCmmChannel()
{
	CBaseObject *pFind = NULL;
	CBaseObject *pParent = GetParent();

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == EPCMMCLASSID_DEVICE_CMM_CHANNEL)
		{
			pFind = pParent;
			break;
		}

		pParent = pParent->GetParent();
	}

	return pFind;
}

void CMM_SetAllSendPkgState(CExBaseList *pList, BOOL bSend)
{
	POS pos = pList->GetHeadPosition();
	CEpFrameBase *p = NULL;

	while (pos != NULL)
	{
		p = (CEpFrameBase*)pList->GetNext(pos);
		p->SetSendState(TRUE);
	}

	pList->RemoveAll();
}

void CEpCmmChannel::OnChannelReceive(CEpCmmRcvSndTime *pEpCmmTime)
{
	CEpDeviceCmmChannel *pDeviceChannel = (CEpDeviceCmmChannel*)GetEpDeviceCmmChannel();
	ASSERT (pDeviceChannel != NULL);

	if (pDeviceChannel != NULL)
	{
		pDeviceChannel->OnReceive(this, pEpCmmTime);
	}
}

void CEpCmmChannel::ResetSendSpyBeginPos()
{
	if (m_pSendBuffer != NULL)
	{
		m_nSendSpyBeginPos = m_pSendBuffer->GetDataFillBeginPosition();
	}
}

void CEpCmmChannel::ResetReceiveSpyBeginPos()
{
	m_nReceiveSpyBeginPos = 0;
}

void CEpCmmChannel::GetReceiveBufferPos(EPBUFFERPOS &oCycleBufPos)
{
	CEpCycleMemBuffer *pBuffer = m_oCycleRcvBuffer.GetBufferNeedParse();
	Ep_GetCycleMemBuffer(pBuffer, &oCycleBufPos);
}

void CEpCmmChannel::AppendRcvBuffer(BYTE *pReceiveBuffer, long nLen, CEpCmmRcvSndTime *pEpCmmTime)
{
	CEpCycleMemBuffer *pBuffer = m_oCycleRcvBuffer.AddBuffer(pReceiveBuffer, nLen);
	pEpCmmTime->m_pBuffer = pBuffer;
}

void CEpCmmChannel::Send(CExBaseObject *pPkgSend)
{
	AddTail(pPkgSend);
}

void CEpCmmChannel::OffsetParserBeginPos(EPBUFFERPOS &oCycleBufPos)
{
	long nLen = Ep_GetEpFramePos(&oCycleBufPos);
	OffsetParserBeginPos(nLen);
}

void CEpCmmChannel::OffsetParserBeginPos(long nLen)
{
	m_oCycleRcvBuffer.OffsetBufferPos(nLen);
}

//连接完成
void CEpCmmChannel::OnConnectFinished()
{
	CEpDeviceCmmChannel *pDeviceChannel = (CEpDeviceCmmChannel*)GetEpDeviceCmmChannel();
	ASSERT (pDeviceChannel != NULL);

	if (pDeviceChannel != NULL)
	{
		pDeviceChannel->OnCmmChannelConnectFinish();
	}
}

BOOL CEpCmmChannel::IsEpCmmChannelExit()
{
	return FALSE;
}

BOOL CEpCmmChannel::DataIsEnoughForParse(long nMinLen)
{
	ASSERT (nMinLen >= 1);

	long nLen = m_oCycleRcvBuffer.GetUnparseBufferLen();

	return (nLen >= nMinLen);
}

CExBaseObject* CEpCmmChannel::GetFrameSend()
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);

	CExBaseObject* pPkgSend = GetHead();

	oLock.Free();
	return pPkgSend;
}


void CEpCmmChannel::RemoveHead()
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);
	long nIndex = 0;
	RemoveAt(nIndex);
	oLock.Free();
}

void CMM_OnChannelConnectSucc(CExBaseList *pEpCmmConfig, CWinThread *pThread)
{
// 	POS pos = pEpCmmConfig->GetHeadPosition();
// 	CEpCmmOnConnect *pObj = NULL;
// 	CEpEngineThread *pEngineThread = (CEpEngineThread*)pThread;
// 
// 	while (pos != NULL)
// 	{
// 		pObj = (CEpCmmOnConnect*)pEpCmmConfig->GetNext(pos);
// 		if (pObj != NULL && pObj->GetClassID() == EPCLASSID_CMM_ONCONNECT)
// 		{
// 			CLogPrint::LogFormatString(g_pLogTracePrint, LOGLEVEL_TRACE, L"RunProcedure(%s)", pObj->m_strText);
// 
// 			pEngineThread->RunProcedure(pObj->m_strText, NULL);
// 		}
// 	}
}


