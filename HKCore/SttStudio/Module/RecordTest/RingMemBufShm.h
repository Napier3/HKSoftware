#ifndef _CRingMemBufShm_h__
#define _CRingMemBufShm_h__

#include "RingMemBuf.h"

class CRingMemBufShm : public CRingMemBuf
{
public:
	CRingMemBufShm();
    virtual ~CRingMemBufShm();

public:
	void ShmCreateServer();
	void ShmCreateClient();

protected:
    void *m_shm;// = NULL;
    int m_nShareMemoryId;// = -1;
    long m_nShmkey;// = 1234;
};


#endif

