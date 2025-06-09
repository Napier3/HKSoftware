
#ifndef __AFXCOLL_H__
#define __AFXCOLL_H__

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//CObject
	// Arrays
	class CByteArray;           // array of BYTE
	class CWordArray;           // array of WORD
	class CDWordArray;          // array of DWORD
	class CUIntArray;           // array of UINT
	class CPtrArray;            // array of void*

	// Special String variants
	class CStringArray;         // array of CStrings
	class CStringList;          // list of CStrings

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////

class CByteArray
{
public:

// Construction
	CByteArray();

// Attributes
	int GetSize() const;
	int GetCount() const;
	BOOL IsEmpty() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	BYTE GetAt(int nIndex) const;
	void SetAt(int nIndex, BYTE newElement);

	BYTE& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const BYTE* GetData() const;
	BYTE* GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, BYTE newElement);

	int Add(BYTE newElement);

	int Append(const CByteArray& src);
	void Copy(const CByteArray& src);

	// overloaded operator helpers
	BYTE operator[](int nIndex) const;
	BYTE& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, BYTE newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CByteArray* pNewArray);

// Implementation
protected:
	BYTE* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount


public:
	~CByteArray();



protected:
	// local typedefs for class templates
	typedef BYTE BASE_TYPE;
	typedef BYTE BASE_ARG_TYPE;
};


////////////////////////////////////////////////////////////////////////////

class CWordArray
{
public:

// Construction
	CWordArray();

// Attributes
	int GetSize() const;
	int GetCount() const;
	BOOL IsEmpty() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	WORD GetAt(int nIndex) const;
	void SetAt(int nIndex, WORD newElement);

	WORD& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const WORD* GetData() const;
	WORD* GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, WORD newElement);

	int Add(WORD newElement);

	int Append(const CWordArray& src);
	void Copy(const CWordArray& src);

	// overloaded operator helpers
	WORD operator[](int nIndex) const;
	WORD& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, WORD newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CWordArray* pNewArray);

// Implementation
protected:
	WORD* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount


public:
	~CWordArray();



protected:
	// local typedefs for class templates
	typedef WORD BASE_TYPE;
	typedef WORD BASE_ARG_TYPE;
};


////////////////////////////////////////////////////////////////////////////

class CDWordArray
{
public:

// Construction
	CDWordArray();

// Attributes
	int GetSize() const;
	int GetCount() const;
	BOOL IsEmpty() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	DWORD GetAt(int nIndex) const;
	void SetAt(int nIndex, DWORD newElement);

	DWORD& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const DWORD* GetData() const;
	DWORD* GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, DWORD newElement);

	int Add(DWORD newElement);

	int Append(const CDWordArray& src);
	void Copy(const CDWordArray& src);

	// overloaded operator helpers
	DWORD operator[](int nIndex) const;
	DWORD& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, DWORD newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CDWordArray* pNewArray);

// Implementation
protected:
	DWORD* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount


public:
	~CDWordArray();



protected:
	// local typedefs for class templates
	typedef DWORD BASE_TYPE;
	typedef DWORD BASE_ARG_TYPE;
};


////////////////////////////////////////////////////////////////////////////

class CUIntArray
{
public:

// Construction
	CUIntArray();

// Attributes
	int GetSize() const;
	int GetCount() const;
	BOOL IsEmpty() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	UINT GetAt(int nIndex) const;
	void SetAt(int nIndex, UINT newElement);

	UINT& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const UINT* GetData() const;
	UINT* GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, UINT newElement);

	int Add(UINT newElement);

	int Append(const CUIntArray& src);
	void Copy(const CUIntArray& src);

	// overloaded operator helpers
	UINT operator[](int nIndex) const;
	UINT& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, UINT newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CUIntArray* pNewArray);

// Implementation
protected:
	UINT* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount


public:
	~CUIntArray();

protected:
	// local typedefs for class templates
	typedef UINT BASE_TYPE;
	typedef UINT BASE_ARG_TYPE;
};


////////////////////////////////////////////////////////////////////////////

class CPtrArray
{
public:

// Construction
	CPtrArray();

// Attributes
	int GetSize() const;
	int GetCount() const;
	BOOL IsEmpty() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	void* GetAt(int nIndex) const;
	void SetAt(int nIndex, void* newElement);

	void*& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const void** GetData() const;
	void** GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, void* newElement);

	int Add(void* newElement);

	int Append(const CPtrArray& src);
	void Copy(const CPtrArray& src);

	// overloaded operator helpers
	void* operator[](int nIndex) const;
	void*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, void* newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CPtrArray* pNewArray);

// Implementation
protected:
	void** m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount


public:
	~CPtrArray();

protected:
	// local typedefs for class templates
	typedef void* BASE_TYPE;
	typedef void* BASE_ARG_TYPE;
};


////////////////////////////////////////////////////////////////////////////

class CStringArray
{
public:

// Construction
	CStringArray();

// Attributes
	int GetSize() const;
	int GetCount() const;
	BOOL IsEmpty() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	const CString& GetAt(int nIndex) const;
	void SetAt(int nIndex, LPCTSTR newElement);

	void SetAt(int nIndex, const CString& newElement);

	CString& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const CString* GetData() const;
	CString* GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, LPCTSTR newElement);

	void SetAtGrow(int nIndex, const CString& newElement);

	int Add(LPCTSTR newElement);

	int Add(const CString& newElement);

	int Append(const CStringArray& src);
	void Copy(const CStringArray& src);

	// overloaded operator helpers
	const CString& operator[](int nIndex) const;
	CString& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, LPCTSTR newElement, int nCount = 1);

	void InsertAt(int nIndex, const CString& newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, const CStringArray* pNewArray);

// Implementation
protected:
	CString* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

	void InsertEmpty(int nIndex, int nCount);


public:
	~CStringArray();



protected:
	// local typedefs for class templates
	typedef CString BASE_TYPE;
	typedef LPCTSTR BASE_ARG_TYPE;
};


inline int CByteArray::GetSize() const
	{ return m_nSize; }
inline int CByteArray::GetCount() const
	{ return m_nSize; }
inline BOOL CByteArray::IsEmpty() const
	{ return m_nSize == 0; }
inline int CByteArray::GetUpperBound() const
	{ return m_nSize-1; }
inline void CByteArray::RemoveAll()
	{ SetSize(0); }
inline BYTE CByteArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline void CByteArray::SetAt(int nIndex, BYTE newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		m_pData[nIndex] = newElement; }

inline BYTE& CByteArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline const BYTE* CByteArray::GetData() const
	{ return (const BYTE*)m_pData; }
inline BYTE* CByteArray::GetData()
	{ return (BYTE*)m_pData; }
inline int CByteArray::Add(BYTE newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline BYTE CByteArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
inline BYTE& CByteArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }


////////////////////////////////////////////////////////////////////////////

inline int CWordArray::GetSize() const
	{ return m_nSize; }
inline int CWordArray::GetCount() const
	{ return m_nSize; }
inline BOOL CWordArray::IsEmpty() const
	{ return m_nSize == 0; }
inline int CWordArray::GetUpperBound() const
	{ return m_nSize-1; }
inline void CWordArray::RemoveAll()
	{ SetSize(0); }
inline WORD CWordArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline void CWordArray::SetAt(int nIndex, WORD newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		m_pData[nIndex] = newElement; }

inline WORD& CWordArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline const WORD* CWordArray::GetData() const
	{ return (const WORD*)m_pData; }
inline WORD* CWordArray::GetData()
	{ return (WORD*)m_pData; }
inline int CWordArray::Add(WORD newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline WORD CWordArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
inline WORD& CWordArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }


////////////////////////////////////////////////////////////////////////////

inline int CDWordArray::GetSize() const
	{ return m_nSize; }
inline int CDWordArray::GetCount() const
	{ return m_nSize; }
inline BOOL CDWordArray::IsEmpty() const
	{ return m_nSize == 0; }
inline int CDWordArray::GetUpperBound() const
	{ return m_nSize-1; }
inline void CDWordArray::RemoveAll()
	{ SetSize(0); }
inline DWORD CDWordArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline void CDWordArray::SetAt(int nIndex, DWORD newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		m_pData[nIndex] = newElement; }

inline DWORD& CDWordArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline const DWORD* CDWordArray::GetData() const
	{ return (const DWORD*)m_pData; }
inline DWORD* CDWordArray::GetData()
	{ return (DWORD*)m_pData; }
inline int CDWordArray::Add(DWORD newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline DWORD CDWordArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
inline DWORD& CDWordArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }


////////////////////////////////////////////////////////////////////////////

inline int CUIntArray::GetSize() const
	{ return m_nSize; }
inline int CUIntArray::GetCount() const
	{ return m_nSize; }
inline BOOL CUIntArray::IsEmpty() const
	{ return m_nSize == 0; }
inline int CUIntArray::GetUpperBound() const
	{ return m_nSize-1; }
inline void CUIntArray::RemoveAll()
	{ SetSize(0); }
inline UINT CUIntArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline void CUIntArray::SetAt(int nIndex, UINT newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		m_pData[nIndex] = newElement; }

inline UINT& CUIntArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline const UINT* CUIntArray::GetData() const
	{ return (const UINT*)m_pData; }
inline UINT* CUIntArray::GetData()
	{ return (UINT*)m_pData; }
inline int CUIntArray::Add(UINT newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline UINT CUIntArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
inline UINT& CUIntArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }


////////////////////////////////////////////////////////////////////////////

inline int CPtrArray::GetSize() const
	{ return m_nSize; }
inline int CPtrArray::GetCount() const
	{ return m_nSize; }
inline BOOL CPtrArray::IsEmpty() const
	{ return m_nSize == 0; }
inline int CPtrArray::GetUpperBound() const
	{ return m_nSize-1; }
inline void CPtrArray::RemoveAll()
	{ SetSize(0); }
inline void* CPtrArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline void CPtrArray::SetAt(int nIndex, void* newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		m_pData[nIndex] = newElement; }

inline void*& CPtrArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline const void** CPtrArray::GetData() const
	{ return (const void**)m_pData; }
inline void** CPtrArray::GetData()
	{ return (void**)m_pData; }
inline int CPtrArray::Add(void* newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline void* CPtrArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
inline void*& CPtrArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }


////////////////////////////////////////////////////////////////////////////

inline int CStringArray::GetSize() const
	{ return m_nSize; }
inline int CStringArray::GetCount() const
	{ return m_nSize; }
inline BOOL CStringArray::IsEmpty() const
	{ return m_nSize == 0; }
inline int CStringArray::GetUpperBound() const
	{ return m_nSize-1; }
inline void CStringArray::RemoveAll()
	{ SetSize(0); }
inline const CString& CStringArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline void CStringArray::SetAt(int nIndex, LPCTSTR newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		m_pData[nIndex] = newElement; }

inline void CStringArray::SetAt(int nIndex, const CString& newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		m_pData[nIndex] = newElement; }

inline CString& CStringArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }

inline const CString* CStringArray::GetData() const
	{ return (const CString*)m_pData; }
inline CString* CStringArray::GetData()
	{ return (CString*)m_pData; }
inline int CStringArray::Add(LPCTSTR newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline int CStringArray::Add(const CString& newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline const CString& CStringArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
inline CString& CStringArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }

#endif //!__AFXCOLL_H__

/////////////////////////////////////////////////////////////////////////////
