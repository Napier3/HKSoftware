#include "StdAfx.h"
#include "CapCycleMemBufferMngr.h"
#include "CapCycleMemBuffer.h"


CCapCycleMemBufferMngr::CCapCycleMemBufferMngr(void)
{
	m_bWriteFinished = FALSE;
}

CCapCycleMemBufferMngr::~CCapCycleMemBufferMngr(void)
{
}

CCapCycleMemBuffer* CCapCycleMemBufferMngr::AddCapBuffer(const CAPTIMEVAL &ts
														  , const EP_ETHER_CAP_IP_GROUP &ipGroup
														  , const BYTE *pBuffer, long nLen
														  , UINT nCapType)
{
	if (nLen > 1024)
	{
		nLen = 1024;
	}

	CCapCycleMemBuffer *pCapBuffer = (CCapCycleMemBuffer*)AddBuffer(pBuffer, nLen, FALSE);
	ep_cap_timeval_to_64time(ts, pCapBuffer->m_ts); 
	pCapBuffer->m_ipGroup = ipGroup;
	Ep_SetProtocol_CapType(pCapBuffer->m_nProtocol, nCapType);
	AddTail(pCapBuffer);
	return pCapBuffer;
}

CCapCycleMemBuffer* CCapCycleMemBufferMngr::AddCapBuffer(const EP_ETHER_CAP_IP_GROUP &ipGroup
														 , const BYTE *pBuffer, long nLen
														 , UINT nCapType)
{
	if (nLen > 1024)
	{
		nLen = 1024;
	}

	EPTIME64EX tm;
	Ep_GetLocalTm_TIME64EX(tm);
	CCapCycleMemBuffer *pCapBuffer = (CCapCycleMemBuffer*)AddBuffer(pBuffer, nLen, FALSE);
	Ep_TIME64EX_to_TIME64(tm,pCapBuffer->m_ts); 
	pCapBuffer->m_ipGroup = ipGroup;
	Ep_SetProtocol_CapType(pCapBuffer->m_nProtocol, nCapType);
	AddTail(pCapBuffer);
	return pCapBuffer;
}


CCapCycleMemBuffer* CCapCycleMemBufferMngr::AddCapBuffer(const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	CCapCycleMemBuffer *pCapBuffer = (CCapCycleMemBuffer*)AddBuffer(pkt_data, header->len, FALSE);
	pCapBuffer->pkt_data_ref = pkt_data;
	ep_cap_timeval_to_64time(header->ts, pCapBuffer->m_ts); 
	//pCapBuffer->m_ipGroup = ipGroup;
	//Ep_SetProtocol_CapType(pCapBuffer->m_nProtocol, nCapType);
	AddTail(pCapBuffer);
	return pCapBuffer;
}

void CCapCycleMemBufferMngr::SetAllBufferPased()
{
	CCapCycleMemBuffer *pCapBuffer = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCapBuffer = (CCapCycleMemBuffer *)GetNext(pos);
		pCapBuffer->SetState(EBS_BEPARSED);
		Ep_SetProtocol_ProtoType(pCapBuffer->m_nProtocol, 0x0FF);
		Ep_SetProtocol_FrameType(pCapBuffer->m_nProtocol, 0x0FF);
	}
}


CCapCycleMemBuffer* CCapCycleMemBufferMngr::SplitBuffer(CCapCycleMemBuffer *pCapBuffer)
{
	long nPos = pCapBuffer->m_nCurrPos;
	long nDataLength = pCapBuffer->GetDataLength();
	long nLen = nDataLength - nPos;

	if (nLen == 0)
	{
		return NULL;
	}

	BYTE *pBuffer = pCapBuffer->GetBuffer();
	CCapCycleMemBuffer *pNew = new CCapCycleMemBuffer();

	pNew->m_ts = pCapBuffer->m_ts; 
	pNew->m_ipGroup = pCapBuffer->m_ipGroup;
	pNew->m_nProtocol = pCapBuffer->m_nProtocol;

	pNew->SetBufferLength(nLen+BUFFER_LENGTH_ADD);
	pNew->CopyBuffer(pBuffer + nPos, nLen, 0);

	POS pos = Find(pCapBuffer);
	InsertAfter(pos, pNew);

	return pNew;
}

