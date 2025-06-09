#pragma once

#include "FrameMemBuffer.h"
// #define FRAME_MEM_BUFFER_COUNT  480000
#define FRAME_MEM_BUFFER_COUNT     200000

class CFrameMemBufferMngr 
{
public:
	CFrameMemBufferMngr(void);
	virtual ~CFrameMemBufferMngr(void);
	void InitFrameMemBuffer();

	void SetWriteFinished(BOOL b)	{	m_bWriteFinished = b;		}
	BOOL IsWriteFinished()			{	return m_bWriteFinished;	}
	void SetState(long nIndexFrom, UINT nState);
	void FreeBuffer(long nIndexFrom);

protected:
	void SetState(long nBeginIndex, long nEndIndex, UINT nState);
	void FreeBuffer(long nBeginIndex, long nEndIndex);

protected:
	BOOL m_bWriteFinished;
	DWORD *m_pdwFrameMemBuffer;

	long m_nMaxCount;
	long m_nCurrIndex;
	long m_nCurrCount;
	__int64 m_n64CapIndex;
	double m_dBeginTime;

	void Free()
	{
		if (m_pdwFrameMemBuffer != NULL)
		{
			long nIndex = 0;

			for (nIndex=0; nIndex<m_nMaxCount; nIndex++)
			{
				CFrameMemBuffer *pBuffer = (CFrameMemBuffer*)m_pdwFrameMemBuffer[nIndex];
				delete pBuffer;
			}

			delete m_pdwFrameMemBuffer;
			m_pdwFrameMemBuffer = NULL;
		}
	}

public:
	void SetMaxCount(long nMaxCount);
	long GetMaxCount()	{	return m_nMaxCount;		}
	long GetCurrCount()	{	return m_nCurrCount;	}
	long GetCurrIndex()	{	return m_nCurrIndex;	}
	long GetCount(long nIndexFrom);
	virtual CFrameMemBuffer* NewMemBuffer()
	{
		return new CFrameMemBuffer();
	}

	CFrameMemBuffer* AddFrameBuffer(const struct pcap_pkthdr *header, const BYTE *pBuffer);
	void SetAllBufferPased();
	void DeleteAll();
	CFrameMemBuffer* GetFrameBuffer(long nIndex)
	{
		ASSERT (0 <= nIndex && nIndex < m_nMaxCount);
		return (CFrameMemBuffer*)m_pdwFrameMemBuffer[nIndex];
	}

	double GetCapBeginTime()	{	return m_dBeginTime;	}
};
