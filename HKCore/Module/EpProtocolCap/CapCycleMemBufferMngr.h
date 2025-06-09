#pragma once

#include "..\ProtocolBase\EpCycleMemBufferMngr.h"
#include "CapCycleMemBuffer.h"

class CCapCycleMemBufferMngr :	public CEpCycleMemBufferMngr
{
public:
	CCapCycleMemBufferMngr(void);
	virtual ~CCapCycleMemBufferMngr(void);

	void SetWriteFinished(BOOL b)	{	m_bWriteFinished = b;		}
	BOOL IsWriteFinished()			{	return m_bWriteFinished;	}

protected:
	BOOL m_bWriteFinished;

public:

	virtual CCycleMemBuffer* NewCycleMemBuffer()
	{
		return new CCapCycleMemBuffer();
	}

	CCapCycleMemBuffer* AddCapBuffer(const CAPTIMEVAL &ts, const EP_ETHER_CAP_IP_GROUP &ipGroup, const BYTE *pBuffer, long nLen, UINT nCapType);
	CCapCycleMemBuffer* AddCapBuffer(const EP_ETHER_CAP_IP_GROUP &ipGroup, const BYTE *pBuffer, long nLen, UINT nCapType);
	void SetAllBufferPased();
	CCapCycleMemBuffer* AddCapBuffer(const struct pcap_pkthdr *header, const u_char *pkt_data);

	CCapCycleMemBuffer* SplitBuffer(CCapCycleMemBuffer *pBuffer);
};
