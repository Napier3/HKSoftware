#pragma once

#define CONTAINER_MIN_BUFF_COUNT 10


template <class T> 
class CDataObjContainer
{
public:
	CDataObjContainer(void)
	{
		m_nCapacity = 0;
		m_nNumOfData = 0;
		m_pDatasBuff = NULL;
	}

	virtual ~CDataObjContainer(void)
	{
		Free();
	}

public:
	long m_nCapacity;   //容量
	long m_nNumOfData;			//数据个数
	T* m_pDatasBuff;     //数据缓冲，可以为单一数据类型也可为结构体


public:
	long GetCount()
	{
		return m_nNumOfData;
	}
	void ResetDatas()
	{
		m_nNumOfData = 0;
	}

	void AddCapacity(long nCount=CONTAINER_MIN_BUFF_COUNT)
	{
		if (nCount <= 0)
		{
			nCount = 1;
		}

		int nNewCount = nCount + m_nCapacity;
		int nTemp = (nNewCount)/CONTAINER_MIN_BUFF_COUNT;

		if (nTemp * CONTAINER_MIN_BUFF_COUNT < nNewCount)
		{
			nNewCount = (nTemp+1) * CONTAINER_MIN_BUFF_COUNT;
		}

		long nBufferLen = nNewCount * sizeof(T);
		T* pNewDatas = (T*)malloc(nBufferLen);
		T* pOld = NULL;
		ZeroMemory(pNewDatas, nBufferLen);

		if (m_pDatasBuff != NULL)
		{
			if (m_nNumOfData > 0)
			{
				memcpy(pNewDatas, m_pDatasBuff, m_nNumOfData * sizeof(T));
			}

			pOld = m_pDatasBuff;
			m_pDatasBuff = pNewDatas;
			m_nCapacity = nNewCount;
			free(pOld);
		}
		else
		{
			m_pDatasBuff = pNewDatas;
			m_nCapacity = nNewCount;
		}
	}

	void Free()
	{
		if (m_pDatasBuff != NULL)
		{
			free(m_pDatasBuff); 
		}

		m_pDatasBuff = NULL;
		m_nCapacity = 0;
		m_nNumOfData = 0;
	}

	BOOL SetData(T* pData, long nIndex)
	{
		if (nIndex >= m_nCapacity)
		{
			return FALSE;
		}

		T *pDest = m_pDatasBuff + nIndex;
		*pDest = *pData;

		return TRUE;
	}

	void AddData(T* pData)
	{
		if (m_nNumOfData+1 >= m_nCapacity)
		{
			AddCapacity();
		}

		T *pDest = m_pDatasBuff + m_nNumOfData;
		*pDest = *pData;
		m_nNumOfData++;
	}

	T* NewData()
	{
		if (m_nNumOfData+1 >= m_nCapacity)
		{
			AddCapacity();
		}

		T *pDest = m_pDatasBuff + m_nNumOfData;
		m_nNumOfData++;
		return pDest;
	}

	T* NewDataEx(long nCount)
	{
		long nCapacityNeed = m_nNumOfData + nCount;

		if (nCapacityNeed >= m_nCapacity)
		{
			AddCapacity(nCapacityNeed - m_nCapacity);
		}

		T *pDest = m_pDatasBuff + m_nNumOfData;
		m_nNumOfData += nCount;
		return (T*)pDest;
	}


	T* GetData(long nIndex)
	{
		if (0 > nIndex || nIndex >= m_nNumOfData)
		{
			ASSERT (FALSE);
			return NULL;
		}
		else
		{
			T *pData = m_pDatasBuff + nIndex;
			ASSERT( pData != NULL);
			return pData;
		}
	}

	//2022-8-4  lijunqing
	T* CurrData()
	{
		if (0 == m_nNumOfData || m_nNumOfData >= m_nCapacity)
		{
			return NULL;
		}
		else
		{
			T *pData = m_pDatasBuff + m_nNumOfData;
			return pData;
		}
	}
	//2022-9-7  lijunqing
	T* PrevData()
	{
		if (1 >= m_nNumOfData || m_nNumOfData >= m_nCapacity)
		{
			return NULL;
		}
		else
		{
			T *pData = m_pDatasBuff + (m_nNumOfData - 2);
			return pData;
		}
	}
};
