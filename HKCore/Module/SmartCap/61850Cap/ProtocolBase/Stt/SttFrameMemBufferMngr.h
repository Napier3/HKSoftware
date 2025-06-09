#pragma once

#include "../FrameMemBuffer.h"
#include "../../../../../Module/SmDb/XSmMemBufferMngr.h"

class CSttFrameMemBufferMngr : public CXSmMemBufferMngr
{
public:
	CSttFrameMemBufferMngr(void);
	virtual ~CSttFrameMemBufferMngr(void);

	virtual CXSmMemBuffer* NewMemBuffer()
	{
		return new CFrameMemBuffer();
	}

	CFrameMemBuffer* AddFrameBuffer(const SST_AT02_PKT_HEAD *header, const BYTE *pBuffer);
	CFrameMemBuffer* AddFrameBuffer(const BYTE *pBuffer, long nLength);
};

