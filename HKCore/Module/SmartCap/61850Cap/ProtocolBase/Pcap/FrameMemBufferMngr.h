#pragma once

#include "../FrameMemBuffer.h"
#include "../../Module/Smdb/XSmMemBufferMngr.h"

class CFrameMemBufferMngr : public CXSmMemBufferMngr
{
public:
	CFrameMemBufferMngr(void);
	virtual ~CFrameMemBufferMngr(void);

	virtual CXSmMemBuffer* NewMemBuffer()
	{
		return new CFrameMemBuffer();
	}

	CFrameMemBuffer* AddFrameBuffer(const struct pcap_pkthdr *header, const BYTE *pBuffer);
};
