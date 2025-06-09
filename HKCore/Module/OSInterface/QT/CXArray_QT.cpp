
#include "CXArray_QT.h"


/////////////////////////////////////////////////////////////////////////////

CByteArray::CByteArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

CByteArray::~CByteArray()
{

	delete[] (BYTE*)m_pData;
}

void CByteArray::SetSize(int nNewSize, int nGrowBy)
{
	ASSERT(nNewSize >= 0);

	if(nNewSize < 0 )
		ThrowInvalidArgException();

	if (nGrowBy >= 0)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		delete[] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
#ifdef SIZE_T_MAX
		ENSURE_ARG(nNewSize <= SIZE_T_MAX/sizeof(BYTE));    // no overflow
#endif
		m_pData = (BYTE*) new BYTE[nNewSize * sizeof(BYTE)];

		memset(m_pData, 0, nNewSize * sizeof(BYTE));  // zero fill

		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements

			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(BYTE));

		}

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowArrayBy = m_nGrowBy;
		if (nGrowArrayBy == 0)
		{
			// heuristically determine growth when nGrowArrayBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowArrayBy = min(1024, max(4, m_nSize / 8));
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowArrayBy)
			nNewMax = m_nMaxSize + nGrowArrayBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
		
		if(nNewMax  < m_nMaxSize)
			ThrowInvalidArgException();

#ifdef SIZE_T_MAX
		ASSERT(nNewMax <= SIZE_T_MAX/sizeof(BYTE)); // no overflow
#endif
		BYTE* pNewData = (BYTE*) new BYTE[nNewMax * sizeof(BYTE)];

		// copy new data from old 
        memcpy(pNewData, m_pData, m_nSize * sizeof(BYTE));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);

		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(BYTE));


		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

int CByteArray::Append(const CByteArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this == &src)
		ThrowInvalidArgException();

	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);

    memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize * sizeof(BYTE));

	return nOldSize;
}

void CByteArray::Copy(const CByteArray& src)
{
	ASSERT(this != &src);   // cannot append to itself
	
	if(this != &src)
	{
		SetSize(src.m_nSize);

        memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(BYTE));
	}
}

void CByteArray::FreeExtra()
{

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
#ifdef SIZE_T_MAX
		ASSERT(m_nSize <= SIZE_T_MAX/sizeof(BYTE)); // no overflow
#endif
		BYTE* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (BYTE*) new BYTE[m_nSize * sizeof(BYTE)];

			// copy new data from old 
            memcpy(pNewData, m_pData, m_nSize * sizeof(BYTE));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

/////////////////////////////////////////////////////////////////////////////

void CByteArray::SetAtGrow(int nIndex, BYTE newElement)
{
	ASSERT(nIndex >= 0);

	if(nIndex < 0)
		ThrowInvalidArgException();

	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}





void CByteArray::InsertAt(int nIndex, BYTE newElement, int nCount)
{

	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if(nIndex < 0 || nCount <= 0)
		ThrowInvalidArgException();
		
	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount);  // grow it to new size

		// shift old data up to fill gap 
        memmove(&m_pData[nIndex+nCount], &m_pData[nIndex], (nOldSize-nIndex) * sizeof(BYTE));

		// re-init slots we copied from
		memset(&m_pData[nIndex], 0, nCount * sizeof(BYTE));
	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);



	// copy elements into the empty space
	while (nCount--)
		m_pData[nIndex++] = newElement;

}



void CByteArray::RemoveAt(int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	int nUpperBound = nIndex + nCount;
	ASSERT(nUpperBound <= m_nSize && nUpperBound >= nIndex && nUpperBound >= nCount);

	if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
		ThrowInvalidArgException();
		
	// just remove a range
	int nMoveCount = m_nSize - (nUpperBound);

	if (nMoveCount)
	{
        memmove(&m_pData[nIndex], &m_pData[nUpperBound], (size_t)nMoveCount * sizeof(BYTE));
	}

	m_nSize -= nCount;
}

void CByteArray::InsertAt(int nStartIndex, CByteArray* pNewArray)
{
	ASSERT(pNewArray != NULL);
	ASSERT(nStartIndex >= 0);

	if(pNewArray == NULL || nStartIndex < 0)
		ThrowInvalidArgException();

	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}



/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CWordArray::CWordArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

CWordArray::~CWordArray()
{

	delete[] (BYTE*)m_pData;
}

void CWordArray::SetSize(int nNewSize, int nGrowBy)
{
	ASSERT(nNewSize >= 0);

	if(nNewSize < 0 )
		ThrowInvalidArgException();

	if (nGrowBy >= 0)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		delete[] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
#ifdef SIZE_T_MAX
		ASSERT(nNewSize <= SIZE_T_MAX/sizeof(WORD));    // no overflow
#endif
		m_pData = (WORD*) new BYTE[nNewSize * sizeof(WORD)];

		memset(m_pData, 0, nNewSize * sizeof(WORD));  // zero fill

		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements

			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(WORD));

		}

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowArrayBy = m_nGrowBy;
		if (nGrowArrayBy == 0)
		{
			// heuristically determine growth when nGrowArrayBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowArrayBy = min(1024, max(4, m_nSize / 8));
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowArrayBy)
			nNewMax = m_nMaxSize + nGrowArrayBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
		
		if(nNewMax  < m_nMaxSize)
			ThrowInvalidArgException();

#ifdef SIZE_T_MAX
		ASSERT(nNewMax <= SIZE_T_MAX/sizeof(WORD)); // no overflow
#endif
		WORD* pNewData = (WORD*) new BYTE[nNewMax * sizeof(WORD)];

		// copy new data from old 
        memcpy(pNewData, m_pData, m_nSize * sizeof(WORD));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);

		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(WORD));

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

int CWordArray::Append(const CWordArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this == &src)
		ThrowInvalidArgException();

	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);

    memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize * sizeof(WORD));

	return nOldSize;
}

void CWordArray::Copy(const CWordArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this != &src)
	{
		SetSize(src.m_nSize);

        memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(WORD));
	}

}

void CWordArray::FreeExtra()
{

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
#ifdef SIZE_T_MAX
		ASSERT(m_nSize <= SIZE_T_MAX/sizeof(WORD)); // no overflow
#endif
		WORD* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (WORD*) new BYTE[m_nSize * sizeof(WORD)];

			// copy new data from old 
            memcpy(pNewData, m_pData, m_nSize * sizeof(WORD));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

/////////////////////////////////////////////////////////////////////////////

void CWordArray::SetAtGrow(int nIndex, WORD newElement)
{
	ASSERT(nIndex >= 0);

	if(nIndex < 0)
		ThrowInvalidArgException();

	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}





void CWordArray::InsertAt(int nIndex, WORD newElement, int nCount)
{

	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if(nIndex < 0 || nCount <= 0)
		ThrowInvalidArgException();
		
	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount);  // grow it to new size

		// shift old data up to fill gap 
        memmove(&m_pData[nIndex+nCount], &m_pData[nIndex], (nOldSize-nIndex) * sizeof(WORD));

		// re-init slots we copied from
		memset(&m_pData[nIndex], 0, nCount * sizeof(WORD));
	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);



	// copy elements into the empty space
	while (nCount--)
		m_pData[nIndex++] = newElement;

}



void CWordArray::RemoveAt(int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	int nUpperBound = nIndex + nCount;
	ASSERT(nUpperBound <= m_nSize && nUpperBound >= nIndex && nUpperBound >= nCount);

	if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
		ThrowInvalidArgException();

	// just remove a range
	int nMoveCount = m_nSize - (nUpperBound);

	if (nMoveCount)
	{
        memmove(&m_pData[nIndex], &m_pData[nUpperBound], nMoveCount * sizeof(WORD));
	}

	m_nSize -= nCount;
}

void CWordArray::InsertAt(int nStartIndex, CWordArray* pNewArray)
{
	ASSERT(pNewArray != NULL);
	ASSERT(nStartIndex >= 0);

	if(pNewArray == NULL || nStartIndex < 0)
		ThrowInvalidArgException();

	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}




/////////////////////////////////////////////////////////////////////////////

CDWordArray::CDWordArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

CDWordArray::~CDWordArray()
{

	delete[] (BYTE*)m_pData;
}

void CDWordArray::SetSize(int nNewSize, int nGrowBy)
{
	ASSERT(nNewSize >= 0);

	if(nNewSize < 0 )
		ThrowInvalidArgException();

	if (nGrowBy >= 0)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		delete[] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
#ifdef SIZE_T_MAX
		ASSERT(nNewSize <= SIZE_T_MAX/sizeof(DWORD));    // no overflow
#endif
		m_pData = (DWORD*) new BYTE[nNewSize * sizeof(DWORD)];

		memset(m_pData, 0, nNewSize * sizeof(DWORD));  // zero fill

		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements

			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(DWORD));

		}

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowArrayBy = m_nGrowBy;
		if (nGrowArrayBy == 0)
		{
			// heuristically determine growth when nGrowArrayBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowArrayBy = min(1024, max(4, m_nSize / 8));
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowArrayBy)
			nNewMax = m_nMaxSize + nGrowArrayBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
		
		if(nNewMax  < m_nMaxSize)
			ThrowInvalidArgException();

#ifdef SIZE_T_MAX
		ASSERT(nNewMax <= SIZE_T_MAX/sizeof(DWORD)); // no overflow
#endif
		DWORD* pNewData = (DWORD*) new BYTE[nNewMax * sizeof(DWORD)];

		// copy new data from old
        memcpy(pNewData, m_pData, m_nSize * sizeof(DWORD));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);

		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(DWORD));


		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

int CDWordArray::Append(const CDWordArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this == &src)
		ThrowInvalidArgException();

	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);

    memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize * sizeof(DWORD));

	return nOldSize;
}

void CDWordArray::Copy(const CDWordArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this != &src)
	{
		SetSize(src.m_nSize);

        memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(DWORD));
	}	

}

void CDWordArray::FreeExtra()
{

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
#ifdef SIZE_T_MAX
		ASSERT(m_nSize <= SIZE_T_MAX/sizeof(DWORD)); // no overflow
#endif
		DWORD* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (DWORD*) new BYTE[m_nSize * sizeof(DWORD)];

			// copy new data from old
            memcpy(pNewData, m_pData, m_nSize * sizeof(DWORD));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

/////////////////////////////////////////////////////////////////////////////

void CDWordArray::SetAtGrow(int nIndex, DWORD newElement)
{
	ASSERT(nIndex >= 0);

	if(nIndex < 0)
		ThrowInvalidArgException();

	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}





void CDWordArray::InsertAt(int nIndex, DWORD newElement, int nCount)
{

	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if(nIndex < 0 || nCount <= 0)
		ThrowInvalidArgException();
		
	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount);  // grow it to new size

		// shift old data up to fill gap 
        memmove(&m_pData[nIndex+nCount],&m_pData[nIndex], (nOldSize-nIndex) * sizeof(DWORD));

		// re-init slots we copied from
		memset(&m_pData[nIndex], 0, nCount * sizeof(DWORD));
	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);



	// copy elements into the empty space
	while (nCount--)
		m_pData[nIndex++] = newElement;
}



void CDWordArray::RemoveAt(int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	int nUpperBound = nIndex + nCount;
	ASSERT(nUpperBound <= m_nSize && nUpperBound >= nIndex && nUpperBound >= nCount);

	if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
		ThrowInvalidArgException();
		
	// just remove a range
	int nMoveCount = m_nSize - (nUpperBound);

	if (nMoveCount)
	{
        memmove(&m_pData[nIndex], &m_pData[nUpperBound], nMoveCount * sizeof(DWORD));
	}

	m_nSize -= nCount;
}

void CDWordArray::InsertAt(int nStartIndex, CDWordArray* pNewArray)
{
	ASSERT(pNewArray != NULL);
	ASSERT(nStartIndex >= 0);

	if(pNewArray == NULL || nStartIndex < 0)
		ThrowInvalidArgException();

	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}



/////////////////////////////////////////////////////////////////////////////

CUIntArray::CUIntArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

CUIntArray::~CUIntArray()
{

	delete[] (BYTE*)m_pData;
}

void CUIntArray::SetSize(int nNewSize, int nGrowBy)
{
	ASSERT(nNewSize >= 0);

	if(nNewSize < 0 )
		ThrowInvalidArgException();

	if (nGrowBy >= 0)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		delete[] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
#ifdef SIZE_T_MAX
		ASSERT(nNewSize <= SIZE_T_MAX/sizeof(UINT));    // no overflow
#endif
		m_pData = (UINT*) new BYTE[nNewSize * sizeof(UINT)];

		memset(m_pData, 0, nNewSize * sizeof(UINT));  // zero fill

		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements

			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(UINT));

		}

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowArrayBy = m_nGrowBy;
		if (nGrowArrayBy == 0)
		{
			// heuristically determine growth when nGrowArrayBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowArrayBy = min(1024, max(4, m_nSize / 8));
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowArrayBy)
			nNewMax = m_nMaxSize + nGrowArrayBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
		
		if(nNewMax  < m_nMaxSize)
			ThrowInvalidArgException();

#ifdef SIZE_T_MAX
		ASSERT(nNewMax <= SIZE_T_MAX/sizeof(UINT)); // no overflow
#endif
		UINT* pNewData = (UINT*) new BYTE[nNewMax * sizeof(UINT)];

		// copy new data from old
        memcpy(pNewData, m_pData, m_nSize * sizeof(UINT));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);

		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(UINT));

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

int CUIntArray::Append(const CUIntArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this == &src)
		ThrowInvalidArgException();

	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);

    memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize * sizeof(UINT));

	return nOldSize;
}

void CUIntArray::Copy(const CUIntArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this != &src)
	{
		SetSize(src.m_nSize);

        memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(UINT));
	}

}

void CUIntArray::FreeExtra()
{

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
#ifdef SIZE_T_MAX
		ASSERT(m_nSize <= SIZE_T_MAX/sizeof(UINT)); // no overflow
#endif
		UINT* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (UINT*) new BYTE[m_nSize * sizeof(UINT)];

			// copy new data from old 
            memcpy(pNewData, m_pData, m_nSize * sizeof(UINT));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

/////////////////////////////////////////////////////////////////////////////

void CUIntArray::SetAtGrow(int nIndex, UINT newElement)
{
	ASSERT(nIndex >= 0);

	if(nIndex < 0)
		ThrowInvalidArgException();

	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}





void CUIntArray::InsertAt(int nIndex, UINT newElement, int nCount)
{

	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if(nIndex < 0 || nCount <= 0)
		ThrowInvalidArgException();

	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount);  // grow it to new size

		// shift old data up to fill gap 
        memmove(&m_pData[nIndex+nCount], &m_pData[nIndex], (nOldSize-nIndex) * sizeof(UINT));

		// re-init slots we copied from
		memset(&m_pData[nIndex], 0, nCount * sizeof(UINT));
	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);



	// copy elements into the empty space
	while (nCount--)
		m_pData[nIndex++] = newElement;

}



void CUIntArray::RemoveAt(int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	int nUpperBound = nIndex + nCount;
	ASSERT(nUpperBound <= m_nSize && nUpperBound >= nIndex && nUpperBound >= nCount);

	if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
		ThrowInvalidArgException();

	// just remove a range
	int nMoveCount = m_nSize - (nUpperBound);

	if (nMoveCount)
	{
        memmove(&m_pData[nIndex], &m_pData[nUpperBound], (size_t)nMoveCount * sizeof(UINT));
	}

	m_nSize -= nCount;
}

void CUIntArray::InsertAt(int nStartIndex, CUIntArray* pNewArray)
{
	ASSERT(pNewArray != NULL);
	ASSERT(nStartIndex >= 0);

	if(pNewArray == NULL || nStartIndex < 0)
		ThrowInvalidArgException();

	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}


/////////////////////////////////////////////////////////////////////////////

CPtrArray::CPtrArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

CPtrArray::~CPtrArray()
{

	delete[] (BYTE*)m_pData;
}

void CPtrArray::SetSize(int nNewSize, int nGrowBy)
{
	ASSERT(nNewSize >= 0);

	if(nNewSize < 0 )
		ThrowInvalidArgException();

	if (nGrowBy >= 0)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		delete[] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
#ifdef SIZE_T_MAX
		ASSERT(nNewSize <= SIZE_T_MAX/sizeof(void*));    // no overflow
#endif
		m_pData = (void**) new BYTE[nNewSize * sizeof(void*)];

		memset(m_pData, 0, nNewSize * sizeof(void*));  // zero fill

		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements

			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(void*));

		}

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowArrayBy = m_nGrowBy;
		if (nGrowArrayBy == 0)
		{
			// heuristically determine growth when nGrowArrayBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowArrayBy = min(1024, max(4, m_nSize / 8));
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowArrayBy)
			nNewMax = m_nMaxSize + nGrowArrayBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
		
		if(nNewMax  < m_nMaxSize)
			ThrowInvalidArgException();

#ifdef SIZE_T_MAX
		ASSERT(nNewMax <= SIZE_T_MAX/sizeof(void*)); // no overflow
#endif
		void** pNewData = (void**) new BYTE[nNewMax * sizeof(void*)];

		// copy new data from old
        memcpy(pNewData, m_pData, m_nSize * sizeof(void*));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);

		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(void*));

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

int CPtrArray::Append(const CPtrArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this == &src)
		ThrowInvalidArgException();

	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);

    memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize * sizeof(void*));

	return nOldSize;
}

void CPtrArray::Copy(const CPtrArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this != &src)
	{
		SetSize(src.m_nSize);

        memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(void*));
	}

}

void CPtrArray::FreeExtra()
{

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
#ifdef SIZE_T_MAX
		ASSERT(m_nSize <= SIZE_T_MAX/sizeof(void*)); // no overflow
#endif
		void** pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (void**) new BYTE[m_nSize * sizeof(void*)];

			// copy new data from old 
            memcpy(pNewData, m_pData, m_nSize * sizeof(void*));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

/////////////////////////////////////////////////////////////////////////////

void CPtrArray::SetAtGrow(int nIndex, void* newElement)
{
	ASSERT(nIndex >= 0);

	if(nIndex < 0)
		ThrowInvalidArgException();

	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}





void CPtrArray::InsertAt(int nIndex, void* newElement, int nCount)
{

	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if(nIndex < 0 || nCount <= 0)
		ThrowInvalidArgException();
		
	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount);  // grow it to new size

		// shift old data up to fill gap 
        memmove(&m_pData[nIndex+nCount], &m_pData[nIndex], (nOldSize-nIndex) * sizeof(void*));

		// re-init slots we copied from
		memset(&m_pData[nIndex], 0, nCount * sizeof(void*));
	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);



	// copy elements into the empty space
	while (nCount--)
		m_pData[nIndex++] = newElement;

}



void CPtrArray::RemoveAt(int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	int nUpperBound = nIndex + nCount;
	ASSERT(nUpperBound <= m_nSize && nUpperBound >= nIndex && nUpperBound >= nCount);

	if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
		ThrowInvalidArgException();
		
	// just remove a range
	int nMoveCount = m_nSize - (nUpperBound);

	if (nMoveCount)
	{
        memmove(&m_pData[nIndex], &m_pData[nUpperBound], nMoveCount * sizeof(void*));
	}

	m_nSize -= nCount;
}

void CPtrArray::InsertAt(int nStartIndex, CPtrArray* pNewArray)
{
	ASSERT(pNewArray != NULL);
	ASSERT(nStartIndex >= 0);

	if(pNewArray == NULL || nStartIndex < 0)
		ThrowInvalidArgException();

	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}


/////////////////////////////////////////////////////////////////////////////

static inline void ConstructElement(CString* pNewData)
{
    new( pNewData ) CString;
}

static inline void DestructElement(CString* pOldData)
{
    pOldData->~CString();
}

static inline void CopyElement(CString* pSrc, CString* pDest)
{
    *pSrc = *pDest;
}

static void _ConstructElements(CString* pNewData, int nCount)
{
	ASSERT(nCount >= 0);

	while (nCount--)
	{
		ConstructElement(pNewData);
		pNewData++;
	}
}

static void _DestructElements(CString* pOldData, int nCount)
{
	ASSERT(nCount >= 0);

	while (nCount--)
	{
		DestructElement(pOldData);
		pOldData++;
	}
}

static void _CopyElements(CString* pDest, CString* pSrc, int nCount)
{
	ASSERT(nCount >= 0);

	while (nCount--)
	{
		*pDest = *pSrc;
		++pDest;
		++pSrc;
	}
}

/////////////////////////////////////////////////////////////////////////////

CStringArray::CStringArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

CStringArray::~CStringArray()
{
    _DestructElements(m_pData, m_nSize);
    delete[] (BYTE*)m_pData;
}

void CStringArray::SetSize(int nNewSize, int nGrowBy)
{
	ASSERT(nNewSize >= 0);

	if(nNewSize < 0 )
		ThrowInvalidArgException();

	if (nGrowBy >= 0)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing

		_DestructElements(m_pData, m_nSize);
		delete[] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
#ifdef SIZE_T_MAX
		ASSERT(nNewSize <= SIZE_T_MAX/sizeof(CString));    // no overflow
#endif
		m_pData = (CString*) new BYTE[nNewSize * sizeof(CString)];

		_ConstructElements(m_pData, nNewSize);

		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements

			_ConstructElements(&m_pData[m_nSize], nNewSize-m_nSize);

		}

		else if (m_nSize > nNewSize)  // destroy the old elements
			_DestructElements(&m_pData[nNewSize], m_nSize-nNewSize);

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowArrayBy = m_nGrowBy;
		if (nGrowArrayBy == 0)
		{
			// heuristically determine growth when nGrowArrayBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowArrayBy = min(1024, max(4, m_nSize / 8));
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowArrayBy)
			nNewMax = m_nMaxSize + nGrowArrayBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
		
		if(nNewMax  < m_nMaxSize)
			ThrowInvalidArgException();

#ifdef SIZE_T_MAX
		ASSERT(nNewMax <= SIZE_T_MAX/sizeof(CString)); // no overflow
#endif
		CString* pNewData = (CString*) new BYTE[(size_t)nNewMax * sizeof(CString)];

		// copy new data from old 
        memcpy(pNewData, m_pData, (size_t)m_nSize * sizeof(CString));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);

		_ConstructElements(&pNewData[m_nSize], nNewSize-m_nSize);

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

int CStringArray::Append(const CStringArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this == &src)
		ThrowInvalidArgException();

	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);

	_CopyElements(m_pData + nOldSize, src.m_pData, src.m_nSize);

	return nOldSize;
}

void CStringArray::Copy(const CStringArray& src)
{
	ASSERT(this != &src);   // cannot append to itself

	if(this != &src)
	{
		SetSize(src.m_nSize);
		_CopyElements(m_pData, src.m_pData, src.m_nSize);
	}
}

void CStringArray::FreeExtra()
{

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
#ifdef SIZE_T_MAX
		ASSERT(m_nSize <= SIZE_T_MAX/sizeof(CString)); // no overflow
#endif
		CString* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (CString*) new BYTE[m_nSize * sizeof(CString)];

			// copy new data from old 
            memcpy(pNewData, m_pData, m_nSize * sizeof(CString));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

/////////////////////////////////////////////////////////////////////////////

void CStringArray::SetAtGrow(int nIndex, wchar_t* newElement)
{
	ASSERT(nIndex >= 0);

	if(nIndex < 0)
		ThrowInvalidArgException();

	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}


void CStringArray::SetAtGrow(int nIndex, const CString& newElement)
{
	ASSERT(nIndex >= 0);

	if(nIndex < 0)
		ThrowInvalidArgException();

	if (nIndex >= m_nSize)
	{
		SetSize(nIndex+1);
	}
	m_pData[nIndex] = newElement;
}



void CStringArray::InsertEmpty(int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if(nIndex < 0 || nCount <= 0)
		ThrowInvalidArgException();

	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		int nOverlapSize = min(nCount, nOldSize - nIndex);

		SetSize(m_nSize + nCount);  // grow it to new size

		// destroy slots we are about to overwrite
		_DestructElements(&m_pData[m_nSize - nOverlapSize], nOverlapSize);

		// shift old data up to fill gap 
        memmove(&m_pData[nIndex+nCount], &m_pData[nIndex], (nOldSize-nIndex) * sizeof(CString));

		// re-init the now-vacant slots we moved data from
		_ConstructElements(&m_pData[nIndex], nOverlapSize);
	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);
}


void CStringArray::InsertAt(int nIndex, wchar_t* newElement, int nCount)
{

	// make room for new elements
	InsertEmpty(nIndex, nCount);

	// copy elements into the empty space

    CString temp;
    temp= newElement;
	while (nCount--)
		m_pData[nIndex++] = temp;

}


void CStringArray::InsertAt(int nIndex, const CString& newElement, int nCount)
{
	// make room for new elements
	InsertEmpty(nIndex, nCount);

	// copy elements into the empty space
	while (nCount--)
		m_pData[nIndex++] = newElement;
}


void CStringArray::RemoveAt(int nIndex, int nCount)
{
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	int nUpperBound = nIndex + nCount;
	ASSERT(nUpperBound <= m_nSize && nUpperBound >= nIndex && nUpperBound >= nCount);

	if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
		ThrowInvalidArgException();
		
	// just remove a range
	int nMoveCount = m_nSize - (nUpperBound);

	_DestructElements(&m_pData[nIndex], nCount);

	if (nMoveCount)
	{
        memmove(&m_pData[nIndex], &m_pData[nUpperBound], nMoveCount * sizeof(CString));
	}

	m_nSize -= nCount;
}

void CStringArray::InsertAt(int nStartIndex, const CStringArray* pNewArray)
{
	ASSERT(pNewArray != NULL);
	ASSERT(nStartIndex >= 0);

	if(pNewArray == NULL || nStartIndex < 0)
		ThrowInvalidArgException();

	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}
