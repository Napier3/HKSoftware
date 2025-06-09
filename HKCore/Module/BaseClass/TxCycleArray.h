#pragma once

#include "ExBaseObject.h"


#define TCycleArray_Count   2000

template <class T> 
class TxCycleArray
{
public:
	TxCycleArray(void)
	{
		m_pdwObject = NULL;
		m_nMaxCount = 0;
		m_nCurrIndex = 0;
		m_nCurrCount = 0;

		m_nCurrReadIndex = 0;  
		m_nCurrFreeIndex = 0;  
	}

	virtual ~TxCycleArray(void)
	{
		Free();
	}

	void FreeBuffer(long nIndexFrom)
	{
		if (m_nCurrCount == m_nMaxCount)
		{
			if (nIndexFrom < m_nCurrIndex)
			{
				FreeBuffer(nIndexFrom, m_nCurrIndex-1);
			}
			else
			{
				FreeBuffer(nIndexFrom, m_nCurrCount-1);
				FreeBuffer(0, m_nCurrIndex-1);
			}
		}
		else
		{
			FreeBuffer(nIndexFrom, m_nCurrIndex-1);
		}
	}

	void FreeBuffer()
	{
		long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
		GetFreeIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);

		if (nEnd1 > nBegin1)
		{
			if (!FreeBuffer(nBegin1, nEnd1))
			{
				return;
			}
		}

		if (nBegin2 >= 0)
		{
			FreeBuffer(nBegin2, nEnd2);
		}
	}

protected:
	BOOL FreeBuffer(long nBeginIndex, long nEndIndex)
	{
		long nIndex = 0;

		for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
		{
			m_pdwObject[nIndex] = 0;
			m_nCurrFreeIndex = nIndex+1; //下一次free的位置
		}

		return TRUE;
	}

protected:
	DWORD *m_pdwObject;

	long m_nMaxCount;
	long m_nCurrIndex;
	long m_nCurrCount;

	long m_nCurrReadIndex;  //当前读取数据的位置
	long m_nCurrFreeIndex;  //当前释放缓存的位置

	void Free()
	{
		if (m_pdwObject != NULL)
		{
			delete m_pdwObject;
			m_pdwObject = NULL;
		}
	}

public:
	void SetMaxCount(long nMaxCount)
	{
		if (m_nMaxCount == nMaxCount)
		{
			return;
		}

		m_nMaxCount = nMaxCount;
		long nLen = m_nMaxCount + 10;
		m_pdwObject = new DWORD[nLen];
		ZeroMemory(m_pdwObject, m_nMaxCount * sizeof(DWORD));
	}

	long GetMaxCount()	{	return m_nMaxCount;		}
	long GetCurrCount()	{	return m_nCurrCount;	}
	long GetCurrIndex()	{	return m_nCurrIndex;	}

	long GetCount(long nIndexFrom)
	{
		if (m_nCurrCount == m_nMaxCount)
		{
			if (m_nCurrIndex >= nIndexFrom)
			{
				return m_nCurrIndex - nIndexFrom;
			}
			else
			{
				return m_nCurrCount - nIndexFrom + m_nCurrIndex;
			}
		}
		else
		{
			return m_nCurrIndex - nIndexFrom;
		}
	}

	long GetCurrReadIndex()	{	return m_nCurrReadIndex;		}
	long GetCurrFreeIndex()	{	return m_nCurrFreeIndex;		}

	void SetCurrReadIndex(long nIndex)	
	{
		m_nCurrReadIndex = nIndex;	

		if (m_nCurrReadIndex >= m_nMaxCount) 
		{
			m_nCurrReadIndex = 0;
		}	
	}

	void SetCurrFreeIndex(long nIndex)
	{
		m_nCurrFreeIndex = nIndex;

		if (m_nCurrFreeIndex >= m_nMaxCount) 
		{
			m_nCurrFreeIndex = 0;
		}	
	}

	void GetReadIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
	{
		long nCurrCount = m_nCurrCount;
		long nCurrIndex = m_nCurrIndex;

		xmem_get_cycle_range_index(m_nMaxCount, nCurrCount, nCurrIndex
			,m_nCurrReadIndex
			, nBegin1, nEnd1, nBegin2, nEnd2);
	}

	void GetFreeIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
	{
		long nCurrCount = m_nCurrCount;
		long nCurrIndex = m_nCurrIndex;

		xmem_get_cycle_range_index(m_nMaxCount, nCurrCount, nCurrIndex
			, m_nCurrFreeIndex
			, nBegin1, nEnd1, nBegin2, nEnd2);
	}

	void DeleteAll()
	{
		T *pObject = NULL;
		long nIndex = 0;
		m_nCurrIndex = 0;

		for (nIndex=0; nIndex<m_nMaxCount; nIndex++)
		{
			m_pdwObject[nIndex] = 0;
		}

		m_nCurrIndex = 0;
		m_nCurrCount = 0;
	}

	inline long GetCurrReadCount()
	{
		return GetCount(m_nCurrReadIndex);
	}

	inline T* GetObject(long nIndex)
	{
		ASSERT (0 <= nIndex && nIndex < m_nMaxCount);
		return (T*)m_pdwObject[nIndex];
	}

	inline T* GetObjectFromCurrRead(long nOffset)
	{
		long nIndex =m_nCurrReadIndex + nOffset;
		
		if (nIndex > m_nMaxCount)
		{
			nIndex %= m_nMaxCount;
		}

		return (T*)m_pdwObject[nIndex];
	}

public:
	virtual void InitCycleArray ()
	{
		SetMaxCount(TCycleArray_Count);
	}

	virtual T* AddObject(T *pObj)
	{
		m_pdwObject[m_nCurrIndex] = (DWORD)pObj;
		m_nCurrIndex++;

		if (m_nCurrIndex >= m_nMaxCount)
		{
			m_nCurrIndex = 0;
		}

		m_nCurrCount++;
		if (m_nCurrCount >= m_nMaxCount)
		{
			m_nCurrCount = m_nMaxCount;
		}

		return pObj;
	}


	//2022-10-19  lijunqing
	T* ReadCurr(int nOffsetIndex=1)
	{
		T *p = GetObject(m_nCurrReadIndex);

		if (nOffsetIndex != 0)
		{
			SetCurrReadIndex(m_nCurrReadIndex+1);
		}

		return p;
	}

	void FreeCurr()
	{
		m_pdwObject[m_nCurrFreeIndex] = 0;
		SetCurrFreeIndex(m_nCurrFreeIndex+1);
	}

};
