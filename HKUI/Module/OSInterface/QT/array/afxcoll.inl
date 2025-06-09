// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

// Inlines for AFXCOLL.H

#pragma once

#ifdef inline

////////////////////////////////////////////////////////////////////////////

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

inline int CObArray::GetSize() const
	{ return m_nSize; }
inline int CObArray::GetCount() const
	{ return m_nSize; }
inline BOOL CObArray::IsEmpty() const
	{ return m_nSize == 0; }
inline int CObArray::GetUpperBound() const
	{ return m_nSize-1; }
inline void CObArray::RemoveAll()
	{ SetSize(0); }
inline CObject* CObArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline void CObArray::SetAt(int nIndex, CObject* newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		m_pData[nIndex] = newElement; }

inline CObject*& CObArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		if( nIndex < 0 || nIndex >= m_nSize )
			AfxThrowInvalidArgException();
		return m_pData[nIndex]; }
inline const CObject** CObArray::GetData() const
	{ return (const CObject**)m_pData; }
inline CObject** CObArray::GetData()
	{ return (CObject**)m_pData; }
inline int CObArray::Add(CObject* newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline CObject* CObArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
inline CObject*& CObArray::operator[](int nIndex)
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


////////////////////////////////////////////////////////////////////////////

inline int CPtrList::GetCount() const
	{ return m_nCount; }
inline int CPtrList::GetSize() const
	{ return m_nCount; }
inline BOOL CPtrList::IsEmpty() const
	{ return m_nCount == 0; }
inline void*& CPtrList::GetHead()
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
inline const void* CPtrList::GetHead() const
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
inline void*& CPtrList::GetTail()
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
inline const void* CPtrList::GetTail() const
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
inline POSITION CPtrList::GetHeadPosition() const
	{ return (POSITION) m_pNodeHead; }
inline POSITION CPtrList::GetTailPosition() const
	{ return (POSITION) m_pNodeTail; }
inline void*& CPtrList::GetNext(POSITION& rPosition) // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
inline const void* CPtrList::GetNext(POSITION& rPosition) const // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
inline void*& CPtrList::GetPrev(POSITION& rPosition) // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
inline const void* CPtrList::GetPrev(POSITION& rPosition) const // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
inline void*& CPtrList::GetAt(POSITION position)
	{ CNode* pNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		return pNode->data; }
inline const void* CPtrList::GetAt(POSITION position) const
	{ CNode* pNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		return pNode->data; }
inline void CPtrList::SetAt(POSITION pos, void* newElement)
	{ CNode* pNode = (CNode*) pos;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		pNode->data = newElement; }



////////////////////////////////////////////////////////////////////////////

inline int CObList::GetCount() const
	{ return m_nCount; }
inline int CObList::GetSize() const
	{ return m_nCount; }
inline BOOL CObList::IsEmpty() const
	{ return m_nCount == 0; }
inline CObject*& CObList::GetHead()
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
inline const CObject* CObList::GetHead() const
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
inline CObject*& CObList::GetTail()
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
inline const CObject* CObList::GetTail() const
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
inline POSITION CObList::GetHeadPosition() const
	{ return (POSITION) m_pNodeHead; }
inline POSITION CObList::GetTailPosition() const
	{ return (POSITION) m_pNodeTail; }
inline CObject*& CObList::GetNext(POSITION& rPosition) // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
inline const CObject* CObList::GetNext(POSITION& rPosition) const // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
inline CObject*& CObList::GetPrev(POSITION& rPosition) // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
inline const CObject* CObList::GetPrev(POSITION& rPosition) const // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
inline CObject*& CObList::GetAt(POSITION position)
	{ CNode* pNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		return pNode->data; }
inline const CObject* CObList::GetAt(POSITION position) const
	{ CNode* pNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		return pNode->data; }
inline void CObList::SetAt(POSITION pos, CObject* newElement)
	{ CNode* pNode = (CNode*) pos;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		pNode->data = newElement; }



////////////////////////////////////////////////////////////////////////////

inline int CStringList::GetCount() const
	{ return m_nCount; }
inline int CStringList::GetSize() const
	{ return m_nCount; }
inline BOOL CStringList::IsEmpty() const
	{ return m_nCount == 0; }
inline CString& CStringList::GetHead()
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
inline const CString& CStringList::GetHead() const
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
inline CString& CStringList::GetTail()
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
inline const CString& CStringList::GetTail() const
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
inline POSITION CStringList::GetHeadPosition() const
	{ return (POSITION) m_pNodeHead; }
inline POSITION CStringList::GetTailPosition() const
	{ return (POSITION) m_pNodeTail; }
inline CString& CStringList::GetNext(POSITION& rPosition) // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
inline const CString& CStringList::GetNext(POSITION& rPosition) const // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
inline CString& CStringList::GetPrev(POSITION& rPosition) // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
inline const CString& CStringList::GetPrev(POSITION& rPosition) const // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
inline CString& CStringList::GetAt(POSITION position)
	{ CNode* pNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		return pNode->data; }
inline const CString& CStringList::GetAt(POSITION position) const
	{ CNode* pNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		return pNode->data; }
inline void CStringList::SetAt(POSITION pos, LPCTSTR newElement)
	{ CNode* pNode = (CNode*) pos;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		pNode->data = newElement; }

inline void CStringList::SetAt(POSITION pos, const CString& newElement)
	{ CNode* pNode = (CNode*) pos;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		if( pNode == NULL )
			AfxThrowInvalidArgException();
		pNode->data = newElement; }



////////////////////////////////////////////////////////////////////////////

inline int CMapWordToPtr::GetCount() const
	{ return m_nCount; }
inline int CMapWordToPtr::GetSize() const
	{ return m_nCount; }
inline BOOL CMapWordToPtr::IsEmpty() const
	{ return m_nCount == 0; }
inline void CMapWordToPtr::SetAt(WORD key, void* newValue)
	{ (*this)[key] = newValue; }
inline POSITION CMapWordToPtr::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapWordToPtr::GetHashTableSize() const
	{ return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////

inline int CMapPtrToWord::GetCount() const
	{ return m_nCount; }
inline int CMapPtrToWord::GetSize() const
	{ return m_nCount; }
inline BOOL CMapPtrToWord::IsEmpty() const
	{ return m_nCount == 0; }
inline void CMapPtrToWord::SetAt(void* key, WORD newValue)
	{ (*this)[key] = newValue; }
inline POSITION CMapPtrToWord::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapPtrToWord::GetHashTableSize() const
	{ return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////

inline int CMapPtrToPtr::GetCount() const
	{ return m_nCount; }
inline int CMapPtrToPtr::GetSize() const
	{ return m_nCount; }
inline BOOL CMapPtrToPtr::IsEmpty() const
	{ return m_nCount == 0; }
inline void CMapPtrToPtr::SetAt(void* key, void* newValue)
	{ (*this)[key] = newValue; }
inline POSITION CMapPtrToPtr::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapPtrToPtr::GetHashTableSize() const
	{ return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////

inline int CMapWordToOb::GetCount() const
	{ return m_nCount; }
inline int CMapWordToOb::GetSize() const
	{ return m_nCount; }
inline BOOL CMapWordToOb::IsEmpty() const
	{ return m_nCount == 0; }
inline void CMapWordToOb::SetAt(WORD key, CObject* newValue)
	{ (*this)[key] = newValue; }
inline POSITION CMapWordToOb::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapWordToOb::GetHashTableSize() const
	{ return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////
inline int CMapStringToPtr::GetCount() const
	{ return m_nCount; }
inline int CMapStringToPtr::GetSize() const
	{ return m_nCount; }
inline BOOL CMapStringToPtr::IsEmpty() const
	{ return m_nCount == 0; }
inline void CMapStringToPtr::SetAt(LPCTSTR key, void* newValue)
	{ (*this)[key] = newValue; }
inline POSITION CMapStringToPtr::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapStringToPtr::GetHashTableSize() const
	{ return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////
inline int CMapStringToOb::GetCount() const
	{ return m_nCount; }
inline int CMapStringToOb::GetSize() const
	{ return m_nCount; }
inline BOOL CMapStringToOb::IsEmpty() const
	{ return m_nCount == 0; }
inline void CMapStringToOb::SetAt(LPCTSTR key, CObject* newValue)
	{ (*this)[key] = newValue; }
inline POSITION CMapStringToOb::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapStringToOb::GetHashTableSize() const
	{ return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////
inline int CMapStringToString::GetCount() const
	{ return m_nCount; }
inline int CMapStringToString::GetSize() const
	{ return m_nCount; }
inline BOOL CMapStringToString::IsEmpty() const
	{ return m_nCount == 0; }
inline void CMapStringToString::SetAt(LPCTSTR key, LPCTSTR newValue)
	{ (*this)[key] = newValue; }
inline POSITION CMapStringToString::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapStringToString::GetHashTableSize() const
	{ return m_nHashTableSize; }

/////////////////////////////////////////////////////////////////////////////

#endif //inline
