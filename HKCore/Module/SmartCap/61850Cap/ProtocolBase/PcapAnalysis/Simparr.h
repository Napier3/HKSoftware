//=========================================================
// File: simparr.h

#ifndef simplearr_h
#define simplearr_h

#define ARR_EMPTY -1

#include <string.h>

template<class T> class SimpleArray
{
public:
	SimpleArray();
	SimpleArray(T* ptArray, int upbound, int size);
	SimpleArray(int nNewSize, int nGrowBy = 1);
	virtual ~SimpleArray();
	SimpleArray(SimpleArray& spaArg);
	operator T*()
	{
		return m_pT;
	}
	int InsertAt(int nIndex, T argT, int nCount = 1);
	void InsertAtRef(int nIndex, T& argT, int nCount = 1);
	int InsertAtGrow(int nIndex, T argT, int nCount = 1);
	void InsertAtGrowRef(int nIndex, T& argT, int nCount = 1);
	int InsertAtGrow (int nIndex, T* pT, int nSrcIndex, int nCount);
	int RemoveAt(int nIndex, int nCount = 1);
	void SetAtGrow(int nIndex, T argT);
	int SetAtGrowRef(int nIndex, T& argT);
	void SetAt(int nIndex, T argT);
	void SetAtRef(int nIndex, T& argT);
	T GetAt(int nIndex);
	T& GetRefAt(int nIndex);
	int GetSize();
	int GetUpperBound();
	int GetLength();
	int GetGrowBy();
	int SetSize(int nNewSize, int nGrowBy = 0);
	void SetGrowBy(int nGrowBy);
	T& operator[](int nIndex) {return m_pT[nIndex];}
	SimpleArray<T>& operator=(SimpleArray<T>& spa);
	void ClearAll(int t);
	int blContainsRef(T& argT);
	int blContains(T argT);
	int nContainsAt(T argT);
	int blIsEmpty();
	void AppendRef(T& argT);
	void Append(T argT);
	void Exchange(int nIndex1, int nIndex2);
	int blCompare(SimpleArray<T>& spa);
	int operator==(SimpleArray<T>& spa);
	int operator!=(SimpleArray<T>& spa);
	int Adopt(T* ptArray, int upbound, int size);
	void SetUpperBound(int upbnd);
	int AppendArray( T* pSrc, int srclen );
	int ExpandToSize();
	int CopyFrom( int index, T* pSrc, int srclen );
	int Replace( int ToReplaceIndex, int ToReplaceLength, T* pReplaceWith, int ReplaceWithLength );

	T* GetBuffer()	{	return m_pT;	}
protected:
	int AddSpace (int nExtend);
	T* m_pT;
	int m_nSize;
	int m_nUpperBound;
	int m_nGrowBy;
};

// A string class.
class SimpleString : public SimpleArray<char>
{
public:
	int IsEmpty();
	SimpleString operator+( SimpleString& str1 );
	SimpleString();
	SimpleString( char* ps );
	int AppendString( char* ps );
	int SetToString( char* ps );
	char* operator=( char* ps );
	SimpleString& operator=( SimpleString str );
	char* operator+=( char* ps );
	int StrLen();
	void Clear();
};

SimpleString operator+( SimpleString ps1, char* ps2 );
SimpleString operator+( char* ps1, SimpleString ps2 );

template<class T> void SimpleArray<T>::SetGrowBy(int nGrowBy)
{
	if(nGrowBy > 0) m_nGrowBy = nGrowBy;
}
//-------------------------------------------------------------------
template<class T> void SimpleArray<T>::ClearAll(int t)
{
	if(m_pT != NULL)
		delete [] m_pT;
	m_pT = NULL;
	m_nSize = 0;
	m_nUpperBound = ARR_EMPTY;
}

//-------------------------------------------------------------------

template<class T> int SimpleArray<T>::GetLength()
{
	return m_nUpperBound+1;
}
//-------------------------------------------------------------------
template<class T> int SimpleArray<T>::SetSize(int nNewSize, int nGrowBy )
{
	if(nNewSize < 0)
		return FALSE;
	if (nNewSize == m_nSize)
		return TRUE;
	if( nNewSize == 0 )
	{
		ClearAll(0);
		return TRUE;
	}

	T* pT = new T[nNewSize];
	if (pT == NULL)
		return FALSE;
	int i;
	if(m_nUpperBound < nNewSize)
	{
		for(i = 0; i <= m_nUpperBound; i++)
			pT[i] = m_pT[i];
	}
	else
	{
		for(i = 0; i < nNewSize; i++)
			pT[i] = m_pT[i];
		m_nUpperBound = nNewSize - 1;
	}

	if(m_pT != NULL)
		delete [] m_pT;
	m_pT = pT;
	m_nSize = nNewSize;
	if(nGrowBy > 0)
		m_nGrowBy = nGrowBy;
	return TRUE;
}
template<class T> int SimpleArray<T>::AppendArray( T* pSrc, int srclen )
{
	if( srclen <= 0 )
		return FALSE;

	if( m_nUpperBound + 1 + srclen > m_nSize )
	{
		// Not enough space, so get some.
		if( !AddSpace( srclen ) )
			return FALSE;
	}
	// Enough space to append without growing. Copy the data.
	int i;
	for( i=0; i<srclen; i++ )
	{
		m_pT[ m_nUpperBound + 1 + i ] = pSrc[i];
	}
	m_nUpperBound += srclen;
	return TRUE;
}
template<class T> int SimpleArray<T>::AddSpace(int nExtend)
{
	int newsize = m_nSize + (((nExtend-1) / m_nGrowBy) + 1) * m_nGrowBy;
	T* pT = new T[newsize];
	if (pT != NULL)
	{
		int i;
		for(i = 0; i < m_nSize; i++)
			pT[i] = m_pT[i];
		if(m_pT != NULL)
			delete [] m_pT;
		m_pT = pT;
		m_nSize = newsize;
		return TRUE;
	}
	else
		return FALSE;
}

template<class T> void SimpleArray<T>::SetUpperBound(int upbnd)
{
	if(upbnd < m_nSize)
		m_nUpperBound = upbnd;
}
template<class T> T SimpleArray<T>::GetAt(int nIndex)
{
	if (nIndex<0)
	{
		return 0;
	}
	return m_pT[nIndex];
}
//-------------------------------------------------------------------
template<class T> SimpleArray<T>::SimpleArray()
{
	m_pT = NULL;
	m_nSize = 0;
	m_nUpperBound = ARR_EMPTY;
	m_nGrowBy = 1;
}

//-------------------------------------------------------------------
template<class T> SimpleArray<T>::SimpleArray(int nNewSize, int nGrowBy)
: m_nGrowBy(nGrowBy), m_nUpperBound(ARR_EMPTY), m_nSize(nNewSize)
{
	m_pT = new T[m_nSize];
}

//-------------------------------------------------------------------
template<class T> SimpleArray<T>::SimpleArray(T* ptArray, int upbound, int size)
: m_nGrowBy(1), m_pT(ptArray), m_nUpperBound(upbound), m_nSize(size)
{
#ifdef _DEBUG
	if(m_pT == NULL || m_nUpperBound<0 || m_nSize<=0 || m_nUpperBound >= m_nSize)
	{
		m_nSize = 0;
		m_nUpperBound = ARR_EMPTY;
	}
#endif
}

//-------------------------------------------------------------------
template<class T> SimpleArray<T>::SimpleArray(SimpleArray& spaArg)
: m_nSize(spaArg.m_nSize), m_nUpperBound(spaArg.m_nUpperBound),
m_nGrowBy(spaArg.m_nGrowBy)
{
	m_pT = new T[m_nSize];
	int k;
	for(k = 0; k <= m_nUpperBound; k++)
		m_pT[k] = spaArg.m_pT[k];
}

//-------------------------------------------------------------------
template<class T> SimpleArray<T>::~SimpleArray()
{
	if(m_pT != NULL) delete [] m_pT;
}

//-------------------------------------------------------------------
template<class T> int SimpleArray<T>::InsertAtGrow(int nIndex, T argT, int nCount)
{
	if(nIndex<0 || nCount<1)
		return FALSE;
	int i;
	if(nIndex > m_nUpperBound)
	{
		for(i = 0; i < nCount; i++)
			SetAtGrow(nIndex + i, argT);
		return TRUE;
	}
	else
	{
		if(m_nSize < m_nUpperBound + 1 + nCount)
		{
			if (AddSpace(nCount) == FALSE)
				return FALSE;
		}
		for(i = m_nUpperBound + nCount; i > nIndex; i--)
		{
			m_pT[i] = m_pT[i-nCount];
		}
		for(i = 0; i < nCount; i++)
			m_pT[nIndex + i] = argT;
		m_nUpperBound += nCount;
		return TRUE;
	}
}

//-------------------------------------------------------------------
template<class T> int SimpleArray<T>::InsertAtGrow (int nIndex, T* pT, int nSrcIndex, int nCount)
{
	if(nIndex<0 || nCount<1)
		return FALSE;
	int i;
	if(nIndex > m_nUpperBound)
	{
		for(i = 0; i < nCount; i++)
		{
			if (SetAtGrowRef(nIndex + i, pT[nSrcIndex+i]) == FALSE)
				return FALSE;
		}
		return TRUE;
	}
	else
	{
		if(m_nSize < m_nUpperBound + 1 + nCount)
		{
			if (AddSpace(nCount) == FALSE)
				return FALSE;
		}
		for(i = m_nUpperBound + nCount; i > nIndex; i--)
		{
			m_pT[i] = m_pT[i-nCount];
		}
		for(i = 0; i < nCount; i++)
			m_pT[nIndex + i] = pT[nSrcIndex+i];
		m_nUpperBound += nCount;
		return TRUE;
	}
}

//-------------------------------------------------------------------
template<class T> void SimpleArray<T>::InsertAtGrowRef(int nIndex, T& argT, int nCount)
{
	if(nIndex<0 || nCount<1) return;
	int i;
	if(nIndex > m_nUpperBound)
	{
		for(i = 0; i < nCount; i++)
			SetAtGrowRef(nIndex + i, argT);
		return;
	}
	else
	{
		if(m_nSize < m_nUpperBound + 1 + nCount)
			AddSpace(nCount);
		for(i = m_nUpperBound + nCount; i > nIndex; i--)
		{
			m_pT[i] = m_pT[i-nCount];
		}
		for(i = 0; i < nCount; i++)
			m_pT[nIndex + i] = argT;
		m_nUpperBound += nCount;
	}
}
template<class T> int SimpleArray<T>::GetSize()
{
	return m_nSize;
}
template<class T> SimpleArray<T>& SimpleArray<T>::operator=( SimpleArray<T>& spa )
{
	// Can't assign to itself: "sa1 = sa1;" not allowed.
	if( &spa != this )
	{
		// If this array is not empty then delete it.
		ClearAll();
		// Allocate memory.
		m_pT = new T[ spa.m_nSize ];
		// Copy the valid elements.
		if( m_pT != NULL )
		{
			// This array now is just large enough to contain the valid elements of spa.
			m_nUpperBound = spa.m_nUpperBound;
			m_nSize = m_nUpperBound + 1;
			// GrowBy rate is also copied.
			m_nGrowBy = spa.m_nGrowBy;
			int k;
			for(k = 0; k <= m_nUpperBound; k++)
				m_pT[k] = spa.m_pT[k];
		}
		// If no memory could be allocated, then this array remains empty.
	}
	return *this;
}

//-------------------------------------------------------------------
#endif // simplearr_h
