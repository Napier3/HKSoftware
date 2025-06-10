#ifndef _CRingMemBufShmDebug_h__
#define _CRingMemBufShmDebug_h__

#include "RingMemBuf.h"

class CRingMemBufShmDebug : public CRingMemBuf
{
public:
	CRingMemBufShmDebug();
    virtual ~CRingMemBufShmDebug();

protected:
	char *m_pMemBufShmDebug;

public:
	void ShmCreateServer();
	void ShmCreateClient();

};


#endif

