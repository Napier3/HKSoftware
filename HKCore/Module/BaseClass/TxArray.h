#pragma once

#include "../OSInterface/OSInterface.h"

#define TxArray_Count   2000

template <class T> 
class TxArray
{
public:
	TxArray(void)
	{
		m_pdwObject = NULL;
		m_nMaxCount = 0;
	}

	virtual ~TxArray(void)
	{
		Free();
	}

	void FreeBuffer()
	{
		long nIndex = 0;

		for (nIndex=0; nIndex< m_nMaxCount; nIndex++)
		{
			m_pdwObject[nIndex] = 0;
		}
	}

protected:
	PSX_OBJ_ADDR *m_pdwObject;
	long m_nMaxCount;

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

		Free();
		
		m_nMaxCount = nMaxCount;
		long nLen = m_nMaxCount + 1;
		m_pdwObject = new PSX_OBJ_ADDR[nLen];
		ZeroMemory(m_pdwObject, nLen * sizeof(PSX_OBJ_ADDR));
	}

	long GetMaxCount()	{	return m_nMaxCount;		}
	
	inline T* GetObject(long nIndex)
	{
		ASSERT (0 <= nIndex && nIndex < m_nMaxCount);
		return (T*)m_pdwObject[nIndex];
	}

	virtual void IniTxArray ()
	{
		SetMaxCount(TxArray_Count);
	}

	virtual void AddObject(T *pObj)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex< m_nMaxCount; nIndex++)
		{
			if (m_pdwObject[nIndex] == NULL)
			{
				m_pdwObject[nIndex] = (PSX_OBJ_ADDR)pObj;
				break;
			}
		}
	}
	
	inline void FreeObject(T *pObj)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex< m_nMaxCount; nIndex++)
		{
			if (m_pdwObject[nIndex] == (PSX_OBJ_ADDR)pObj)
			{
				m_pdwObject[nIndex] = NULL;
				break;
			}
		}
	}

	inline long GetObjectCount()
	{
		long nIndex = 0;
		long nCount = 0;

		for (nIndex=0; nIndex< m_nMaxCount; nIndex++)
		{
			if (m_pdwObject[nIndex] != 0)
			{
				nCount++;
			}
		}

		return nCount;
	}

	inline BOOL HasObject(T *pObj)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex< m_nMaxCount; nIndex++)
		{
			if (m_pdwObject[nIndex] == (PSX_OBJ_ADDR)pObj)
			{
				return TRUE;
			}
		}

		return FALSE;
	}
};
