#pragma once

#include "XSmMemBuffer.h"
// #define FRAME_MEM_BUFFER_COUNT  480000
#define FRAME_MEM_BUFFER_COUNT     200000

class CXSmMemBufferMngr : public CXMemBufferBse
{
public:
	CXSmMemBufferMngr(void);
	virtual ~CXSmMemBufferMngr(void);

	void SetWriteFinished(BOOL b)	{	m_bWriteFinished = b;		}
	BOOL IsWriteFinished()			{	return m_bWriteFinished;	}
	void SetState(long nIndexFrom, UINT nState);
	void FreeBuffer(long nIndexFrom);
	void FreeBuffer();

	void ResetMngr();

protected:
	void SetState(long nBeginIndex, long nEndIndex, UINT nState);
	BOOL FreeBuffer(long nBeginIndex, long nEndIndex);

protected:
	BOOL m_bWriteFinished;
	DWORD *m_pdwXSmMemBuffer;
	__int64 m_n64CapIndex;
	
	STT_TIME_64 m_oBeginTime;

	long m_nMaxCount;
	long m_nCurrIndex;
	long m_nCurrCount;

	long m_nCurrParseIndex;  //当前解析的位置
	long m_nCurrWriteIndex;  //当前写入数据库的位置
	long m_nCurrFreeIndex;  //当前释放缓存的位置

	long m_nLastParseIndex; //上一次解析的位置

	void Free();

public:
	void SetMaxCount(long nMaxCount);
	long GetMaxCount()	{	return m_nMaxCount;		}
	long GetCurrCount()	{	return m_nCurrCount;	}
	long GetCurrIndex()	{	return m_nCurrIndex;	}
	long GetCount(long nIndexFrom);

	long GetCurrParseIndex()	{	return m_nCurrParseIndex;		}
	long GetCurrWriteIndex()	{	return m_nCurrWriteIndex;		}
	long GetCurrFreeIndex()	{	return m_nCurrFreeIndex;		}

	long GetLastParseIndex()	{	return m_nLastParseIndex;		}

	void SetCurrParseIndex(long nIndex)	
	{
		m_nCurrParseIndex = nIndex;	
	
		if (m_nCurrParseIndex >= m_nMaxCount) 
		{
			m_nCurrParseIndex = 0;
		}	
	}


	void SetCurrWriteIndex(long nIndex)
	{
		m_nCurrWriteIndex = nIndex;

		if (m_nCurrWriteIndex >= m_nMaxCount) 
		{
			m_nCurrWriteIndex = 0;
		}	
	}

	void SetCurrrFreeIndex(long nIndex)
	{
		m_nCurrFreeIndex = nIndex;

		if (m_nCurrFreeIndex >= m_nMaxCount) 
		{
			m_nCurrFreeIndex = 0;
		}	
	}

	void SetLastParseIndex(long nIndex)	
	{
		m_nLastParseIndex = nIndex;	

		if (m_nLastParseIndex >= m_nMaxCount) 
		{
			m_nLastParseIndex = 0;
		}	
	}

	void GetParseIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2);
	void GetWriteIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2);
	void GetFreeIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2);

	void GetLastParseIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2);

	void SetAllBufferPased();
	void DeleteAll(BOOL bClear=FALSE);

	inline CXSmMemBuffer* GetFrameBuffer(long nIndex)
	{
		ASSERT (0 <= nIndex && nIndex < m_nMaxCount);
		return (CXSmMemBuffer*)m_pdwXSmMemBuffer[nIndex];
	}

	double GetCapBeginTime()	{	return m_oBeginTime.dTime;	}
	__int64 GetCapBeginTime64()	{	return m_oBeginTime.n64Time;	}

public:
	virtual void InitXSmMemBufferMngr ();
	virtual CXSmMemBuffer* NewMemBuffer()	{		return new CXSmMemBuffer();	}
	virtual CXSmMemBuffer* AddFrameBuffer(const BYTE *pBuffer, long nLen, __int64 dTimeSnamp);

protected:
	long m_nAllocPos;  //内存引用的起始位置

	BYTE* AllocBuffer(long nLen);
};
