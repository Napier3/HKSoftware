// LINKLIST.h: interface for the CLinkListt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_TLinkList_DW_H_)
#define _TLinkList_DW_H_


#ifdef _USE_CTLinkList_DW__

#include "..\API\GlobalApi.h"

#ifndef TLinkList_BlockSize
#define TLinkList_BlockSize  10
#endif

typedef DWORD* POS;


template <class T> 
class CTLinkList
{
protected:
	DWORD *m_pdwBuffer;
	long  m_nCount;
	long  m_nMaxBufferCount;

	void ExpandBuffer(long nExpand=TLinkList_BlockSize)
	{
		long nCount = m_nMaxBufferCount + nExpand;
		SetBufferCount(nCount);
	}	
	
	void SetBufferCount(long nCount)
	{
		if (m_nMaxBufferCount > nCount)
		{
			return;
		}
		else
		{
			nCount = max(nCount, m_nMaxBufferCount + TLinkList_BlockSize);
			DWORD *pNew = new DWORD[nCount];
			ZeroMemory(pNew, sizeof(DWORD)*nCount);

			if (m_pdwBuffer != NULL)
			{
				memcpy(pNew, m_pdwBuffer, sizeof(DWORD) * m_nCount);
				DWORD *pTemp = m_pdwBuffer;
				m_pdwBuffer = pNew;
				delete pTemp;
			}
			else
			{
				m_pdwBuffer = pNew;
			}

			m_nMaxBufferCount = nCount;
		}
	}
	
	void ExpandForAdd(long nCount)
	{
		long nMax = nCount + m_nCount;
		
		if (m_nMaxBufferCount < nMax)
		{
			SetBufferCount(nCount);
		}
		else
		{
			if (nMax >= m_nMaxBufferCount)
			{
				ExpandBuffer(max(TLinkList_BlockSize, nCount));
			}
		}
	}
	
	void MemMoveBack(long nPos, long nCount)
	{
		DWORD *pFrom = m_pdwBuffer + m_nCount - 1;
		DWORD *pTo = pFrom + nCount;
		DWORD *pPos = m_pdwBuffer + nPos;
		
		while (pFrom >= pPos)
		{
			*pTo = *pFrom;
			pTo--;
			pFrom--;
		}
	}

	void MemMovePrev(long nPos, long nCount)
	{
		DWORD *pTo = m_pdwBuffer + nPos;
		DWORD *pFrom = pTo + nCount;
		DWORD *pPos = m_pdwBuffer + m_nCount;

		while (pFrom < pPos)
		{
			*pTo = *pFrom;
			pTo++;
			pFrom++;
		}

		while(pTo < pPos)
		{
			*pTo = 0;
			pTo++;
		}
	}

	void ResetBuffert(long nCount)
	{
		if (nCount == m_nMaxBufferCount)
		{
			ZeroMemory(m_pdwBuffer, sizeof(DWORD) * nCount);
		}
		else
		{
			delete m_pdwBuffer;
			m_pdwBuffer = new DWORD[nCount];
			ZeroMemory(m_pdwBuffer, sizeof(DWORD) * nCount);
		}

		m_nMaxBufferCount = nCount;
		m_nCount = 0;
	}

public:
	
	// Construction
	CTLinkList(int nBlockSize = TLinkList_BlockSize)
	{
		m_pdwBuffer = NULL;
		m_nCount = 0;
		m_nMaxBufferCount = 0;
		SetBufferCount(nBlockSize);
	}
	virtual ~CTLinkList()
	{
		DeleteAll();
		delete m_pdwBuffer;
	}
	
	// Attributes (head and tail)
	// count of elements
	int GetCount() const
	{ 
		return m_nCount;
	}
	
	BOOL IsEmpty() const
	{
		return m_nCount == 0; 
	}
	
	// peek at head or tail
	T* GetHead() const
	{ 
		//ASSERT (m_pNodeHead != NULL);
		return (m_nCount == 0) ? NULL : ((T*)m_pdwBuffer[0]);
	}
	
	T* GetTail() const
	{ 	
		//ASSERT (m_pNodeTail != NULL);
		return (m_nCount == 0) ? NULL : (T*)m_pdwBuffer[m_nCount - 1];
	}
		
	// add before head or after tail
	POS AddHead(T* newElement)
	{
		ExpandForAdd(1);
		
		if (m_nCount > 0)
		{
			MemMoveBack(0, 1);
		}

		m_pdwBuffer[0] = (DWORD)newElement;
		m_nCount++;

		return (POS)m_pdwBuffer;
	}
	
	POS AddTail(T* newElement)
	{
		ExpandForAdd(1);
		m_pdwBuffer[m_nCount] = (DWORD)newElement;
		m_nCount++;
		return (POS)(m_pdwBuffer+m_nCount-1);
	}

	POS AddNode(T* newElement)
	{
		return AddTail(newElement);
	}
	
	// remove all elements
	void RemoveAll()
	{
		m_nCount = 0;
		delete m_pdwBuffer;
		m_pdwBuffer = NULL;
		m_nMaxBufferCount = 0;
	}
	
	// iteration
	POS GetHeadPosition() const
	{ 
		if (m_nCount == 0)
		{
			return NULL;
		}

		return (POS) m_pdwBuffer; 
	}
	
	
	POS GetTailPosition() const
	{ 
		if (m_nCount == 0)
		{
			return NULL;
		}
		else
		{
			return (POS) (m_pdwBuffer + m_nCount-1); 
		}
	}
	
	T* GetNext(POS& rPosition) const
	{ 
		if (rPosition < m_pdwBuffer || rPosition >= m_pdwBuffer + m_nCount)
		{
			rPosition = NULL;
			return NULL;
		}

		T* pData = (T*)(*rPosition);
		rPosition++;

		if (rPosition - m_pdwBuffer >= m_nCount)
		{
			rPosition = NULL;
		}

		return pData;
	}
	
	T* GetPrev(POS& rPosition) const
	{ 
		T* pData = (T*)(*rPosition);
		rPosition--;

		if (rPosition < m_pdwBuffer)
		{
			rPosition = NULL;
		}

		return pData;
	}
	
	// getting/modifying an element at a given position
	T* GetAt(POS position) const
	{
		if (m_pdwBuffer == NULL)
		{
			return NULL;
		}

		if (position < m_pdwBuffer || position > m_pdwBuffer + m_nCount)
		{
			return NULL;
		}

		return (T*)(*position);
	}
	T* GetAt(long nIndex) const
	{
		return GetAtIndex(nIndex);
	}
	
	T* GetAtIndex(long nIndex) const
	{
		if (nIndex < 0 || nIndex >= m_nCount)
		{
			return NULL;
		}
		
		return (T*)(m_pdwBuffer[nIndex]);
	}
	void SetAt(POS pos, T* newElement)
	{ 
		if (pos < m_pdwBuffer || pos >=( m_pdwBuffer + m_nCount))
		{
			return;
		}

		*pos = (DWORD)newElement;
	}
	T* RemoveAt(long nIndex)
	{
		if (0 > nIndex || nIndex >= m_nCount)
		{
			return NULL;
		}

		T *pData = (T*)m_pdwBuffer[nIndex];
		memcpy(m_pdwBuffer+nIndex, m_pdwBuffer + nIndex + 1, sizeof(DWORD) * (m_nCount - nIndex - 1));
		m_pdwBuffer[m_nCount - 1] = 0;
		m_nCount--;

		return pData;
	}
	T* RemoveAt(POS position)
	{
		long nIndex = position - m_pdwBuffer;

		return RemoveAt(nIndex);
	}
	
	// inserting before or after a given position
	POS InsertBefore(POS position, T* newElement)
	{
		if (position < m_pdwBuffer || position >= m_pdwBuffer + m_nCount)
		{
			return AddHead(newElement);
		}

		long nIndex = position - m_pdwBuffer;
		ExpandForAdd(1);
		MemMoveBack(nIndex, 1);
		m_pdwBuffer[nIndex] = (DWORD)newElement;
		m_nCount++;
		return (m_pdwBuffer + nIndex);
	}
	
	POS InsertAfter(POS position, T* newElement)
	{
		if (position < m_pdwBuffer || position >= m_pdwBuffer + m_nCount)
		{
			return AddTail(newElement);
		}

		long nIndex = position - m_pdwBuffer;
		ExpandForAdd(1);
		MemMoveBack(nIndex+1, 1);
		m_pdwBuffer[nIndex+1] = (DWORD)newElement;
		m_nCount++;

		return (POS) (m_pdwBuffer+nIndex+1);
	}
	
	// helper functions (note: O(n) speed)
	POS Find(T* searchValue, POS startAfter = NULL) const
	{
		POS posBegin;

		if (startAfter == NULL)
		{
			posBegin = m_pdwBuffer;
		}
		else
		{
			if (startAfter < m_pdwBuffer || startAfter > m_pdwBuffer + m_nCount)
			{
				posBegin = m_pdwBuffer;
			}
			else
			{
				posBegin = startAfter+1;
			}
		}

		POS posEnd = m_pdwBuffer + m_nCount;

		while (posBegin < posEnd)
		{
			if ((DWORD)searchValue == *posBegin)
			{
				return posBegin;
			}

			posBegin++;
		}
				
		return NULL;
	}

	// defaults to starting at the HEAD
	// return NULL if not found
	POS FindIndex(int nIndex) const
	{
		if (nIndex >= m_nCount || nIndex < 0)
			return NULL;  // went too far
		
		return (POS) (m_pdwBuffer+nIndex);
	}

	long FindIndex(POS pos)
	{
		if (pos < m_pdwBuffer || pos > m_pdwBuffer + m_nCount)
		{
			return -1;
		}
		
		return pos - m_pdwBuffer;
	}
	
	long FindIndex(T *pData)
	{
		long nIndex = 0;
		long nIndexFind = -1;

		for (nIndex=0; nIndex<m_nCount; nIndex++)
		{
			if ((DWORD)pData == m_pdwBuffer[nIndex])
			{
				nIndexFind = nIndex;
				break;
			}
		}

		return nIndexFind;
	}

	
	
	BOOL Delete(long nIndex)
	{
		if (m_nCount == 0)
		{
			return FALSE;
		}

		if (nIndex < 0 || nIndex >= m_nCount)
		{
			return FALSE;
		}

		T *pData = (T*)m_pdwBuffer[nIndex];
		MemMovePrev(nIndex, 1);
		delete pData;
		m_nCount--;

		return TRUE;
	}

	BOOL Delete(T *pData)
	{
		long nIndex = FindIndex(pData);
		return Delete(nIndex);
	}

	BOOL Remove(T *pData)
	{
		long nIndex = FindIndex(pData);

		if (nIndex >= 0)
		{
			RemoveAt(nIndex);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
public:
	//////////////////////////////////////////////////////////////////////////
	//delete operations 
	virtual void DeleteAll()
	{
		long nIndex = 0;
		T *pData = NULL;

		for (nIndex=0; nIndex<m_nCount; nIndex++)
		{
			pData = (T*)m_pdwBuffer[nIndex];
			delete pData;
		}

		RemoveAll();
	}
	virtual BOOL DeleteAt(long nIndex)
	{
		return Delete(nIndex);
	}
	virtual BOOL DeleteAt(POS position)
	{
		if (position == NULL)
		{
			return FALSE;
		}

		if (position < m_pdwBuffer || position > m_pdwBuffer + m_nCount)
		{
			return FALSE;
		}

		return Delete(position - m_pdwBuffer);
	}
	virtual BOOL DeleteAtIndex(long nIndex)
	{
		return Delete(nIndex);
	}

	virtual void DeleteHead()
	{
		Delete((long)0);
	}
	virtual void DeleteTail()
	{
		if (m_nCount == 0)
		{
			return;
		}

		Delete(m_nCount - 1);
	}
	virtual void ChangePosition(POS pos1, POS pos2)
	{
		if ((pos1 < m_pdwBuffer || pos1 >= m_pdwBuffer + m_nCount)
			|| (pos2 < m_pdwBuffer || pos2 >= m_pdwBuffer + m_nCount))
		{
			return;
		}

		T* p1 = (T*)(*pos1);
		T* p2 = (T*)(*pos2);
		*pos2 = (DWORD)p1;
		*pos1 = (DWORD)p2;
	}
	
	virtual void ChangePosition(long nIndex1, long nIndex2)
	{
		if ((nIndex1 < 0 || nIndex1 >= m_nCount)
			|| (nIndex2 < 0 || nIndex2 >=  m_nCount))
		{
			return;
		}
		
		T* p1 = (T*)(m_pdwBuffer[nIndex1]);
		T* p2 = (T*)(m_pdwBuffer[nIndex2]);
		m_pdwBuffer[nIndex2] = (DWORD)p1;
		m_pdwBuffer[nIndex1] = (DWORD)p2;
	}

	virtual void ChangePosition(T *p1, T *p2)
	{
		long nIndex1 = 0, nIndex2 = 0;
		nIndex1 = FindIndex(p1);
		nIndex2 = FindIndex(p2);

		if ((nIndex1 >= 0) && (nIndex2 >= 0))
		{
			ChangePosition(nIndex1, nIndex2);
		}
	}

	virtual void BringToTail(long nIndex)
	{
		if (nIndex < 0 || nIndex >= m_nCount-1)
		{
			return;
		}
		
		POS pos = m_pdwBuffer + nIndex;
		T *pData = (T*)m_pdwBuffer[nIndex];
		POS posEnd = m_pdwBuffer + m_nCount - 1;

		while (pos < posEnd)
		{
			*pos = *(pos + 1);
			pos++;
		}

		*pos = (DWORD)pData;
	}

	virtual void BringToTail(POS pos)
	{
		if (m_nCount == 0)
		{
			return;
		}

		if (pos < m_pdwBuffer || pos > m_pdwBuffer + m_nCount)
		{
			return;
		}

		BringToTail(pos - m_pdwBuffer);
	}

	virtual void BringToTail(T *p)
	{
		long nIndex = FindIndex(p);

		if (nIndex < 0)
		{
			return;
		}

		BringToTail(nIndex);
	}

	virtual void BringToHead(long nIndex)
	{
		if (nIndex <=0 || nIndex >= m_nCount)
		{
			return;
		}

		T *pData = (T*)m_pdwBuffer[nIndex];
		POS pos = m_pdwBuffer+nIndex;

		while (pos > m_pdwBuffer)
		{
			*pos = *(pos - 1);
			pos--;
		}

		m_pdwBuffer[0] = (DWORD)pData;
	}
	virtual void BringToHead(POS pos)
	{
		if (pos != NULL)
		{
			BringToHead(pos - m_pdwBuffer);
		}
	}
	virtual void BringToHead(T *p)
	{
		long nIndex = FindIndex(p);
		BringToHead(nIndex);
	}
	
	T* operator[](long nIndex)
	{
		return GetAt(nIndex);
	}

	// Implementation
protected:
	void GetAllDataAddr(DWORD *pdwDataBuffer)
	{
		memcpy(pdwDataBuffer, sizeof(DWORD) * m_nCount);
	}

};

template <class T> 
class CTLinkListEx : public  CTLinkList<T>
{
public:
	CTLinkListEx() : CTLinkList(TLinkList_BlockSize)
	{

	}
	virtual ~CTLinkListEx()
	{
	}

	T* FindByName(const CString &strName)
	{
		T* pTemp = NULL;
		T* pFind = NULL;
		long nIndex = 0;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strName == strName)
			{
				pFind = pTemp;
				break;
			}

			nIndex++;
		}

		return pFind;
	}
	T* FindByID(const CString &strID)
	{
		T* pTemp = NULL;
		T* pFind = NULL;
		long nIndex = 0;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strID == strID)
			{
				pFind = pTemp;
				break;
			}

			nIndex++;
		}

		return pFind;
	}

	long FindIndexByID(const CString &strID)
	{
		T* pTemp = NULL;
		long nIndex = 0;
		long nIndexFind = -1;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strID == strID)
			{
				nIndexFind = nIndex;
				break;
			}

			nIndex++;
		}

		return nIndexFind;
	}

	POS FindPosByID(const CString &strID)
	{
		T* pTemp = NULL;
		POS posFind = NULL;
		long nIndex = 0;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strID == strID)
			{
				posFind = m_pdwBuffer + nIndex;
				break;
			}

			nIndex++;
		}

		return posFind;
	}

	long FindIndexByName(const CString &strName)
	{
		T* pTemp = NULL;
		long nIndexFind = -1, nIndex = 0;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strName == strName)
			{
				nIndexFind = nIndex;
				break;
			}

			nIndex++;
		}

		return nIndexFind;
	}

	POS FindPosByName(const CString &strName)
	{
		T* pTemp = NULL;
		POS posFind = NULL;
		long nIndex = 0;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strName == strName)
			{
				posFind = m_pdwBuffer + nIndex;
				break;
			}

			nIndex++;
		}

		return posFind;
	}

	long SearchByName(const CString &strName)
	{
		T* pTemp = NULL;
		long nCount = 0;
		long nIndex = 0;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strName == strName)
			{
				nCount++;
			}

			nIndex++;
		}

		return nCount;
	}

	long SearchByID(const CString &strID)
	{
		T* pTemp = NULL;
		long nCount = 0;
		long nIndex = 0;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strID == strID)
			{
				nCount++;
			}

			nIndex++;
		}

		return nCount;
	}

	long SearchByName(const CString &strName, CTLinkList<T> &oList)
	{
		T* pTemp = NULL;
		long nIndex = 0;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strName == strName)
			{
				oList.AddTail(pTemp);
			}

			nIndex++;
		}

		return oList.GetCount();
	}

	long SearchByID(const CString &strID, CTLinkList<T> &oList)
	{
		T* pTemp = NULL;
		long nIndex = 0;

		while (nIndex < m_nCount)
		{
			pTemp = (T*)(m_pdwBuffer[nIndex]);

			if (pTemp->m_strID == strID)
			{
				oList.AddTail(pTemp);
			}

			nIndex++;
		}

		return oList.GetCount();
	}
};

#endif //_USE_CTLinkList_DW__

#endif // !defined(_TLinkList_DW_H_)
