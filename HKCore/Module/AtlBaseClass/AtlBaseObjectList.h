// AtlBaseObject.h: interface for the CAtlBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ATLBASEOBJECTLIST_H__)
#define _ATLBASEOBJECTLIST_H__

#include "AtlListDef.h"
#include "AtlBaseObject.h"

class  CAtlBaseObjectList : public CAtlBaseObject
{
protected:
	struct CNode
	{
		CNode* pNext;
		CNode* pPrev;
		void* data;
	};
public:

// Construction
	CAtlBaseObjectList(int nBlockSize = 10);

// Attributes (head and tail)
	// count of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// peek at head or tail
	CAtlBaseObject*& GetHead();
	CAtlBaseObject* GetHead() const;
	CAtlBaseObject*& GetTail();
	CAtlBaseObject* GetTail() const;

// Operations
	// get head or tail (and remove it) - don't call on empty list!
	CAtlBaseObject* RemoveHead();
	CAtlBaseObject* RemoveTail();

	// add before head or after tail
	POS AddHead(CAtlBaseObject* newElement);
	POS AddTail(CAtlBaseObject* newElement);


	// add another list of elements before head or after tail
	void AddHead(CAtlBaseObjectList* pNewList);
	void AddTail(CAtlBaseObjectList* pNewList);

	// remove all elements
	void RemoveAll();

	// iteration
	POS GetHeadPosition() const;
	POS GetTailPosition() const;
	CAtlBaseObject*& GetNext(POS& rPosition); // return *Position++
	CAtlBaseObject* GetNext(POS& rPosition) const; // return *Position++
	CAtlBaseObject*& GetPrev(POS& rPosition); // return *Position--
	CAtlBaseObject* GetPrev(POS& rPosition) const; // return *Position--

	// getting/modifying an element at a given position
	CAtlBaseObject* GetAt(POS position) const;
	CAtlBaseObject*& GetAt(POS position);
	CAtlBaseObject* GetAtIndex(long nIndex) const;
	void SetAt(POS pos, CAtlBaseObject* newElement);

	void RemoveAt(POS position);

	// inserting before or after a given position
	POS InsertBefore(POS position, CAtlBaseObject* newElement);
	POS InsertAfter(POS position, CAtlBaseObject* newElement);


	// helper functions (note: O(n) speed)
	POS Find(CAtlBaseObject* searchValue, POS startAfter = NULL) const;
						// defaults to starting at the HEAD
						// return NULL if not found
	POS FindIndex(int nIndex) const;
						// get the 'nIndex'th element (may return NULL)

public:
	//////////////////////////////////////////////////////////////////////////
	//delete operations 
	virtual void DeleteAll();
	virtual BOOL DeleteAt(POS position)
	{
		CAtlBaseObject *pObj = GetAt(position);
		if (pObj != NULL)		{	delete pObj;	RemoveAt(position);	}
		return (pObj != NULL);
	}
	virtual BOOL DeleteAtIndex(long nIndex)
	{
		POS position = FindIndex(nIndex);
		return DeleteAt(position);
	}
	
// Implementation
protected:
	CNode* m_pNodeHead;
	CNode* m_pNodeTail;
	int m_nCount;
	CNode* m_pNodeFree;
	struct CAtlPlex* m_pBlocks;
	int m_nBlockSize;

	CNode* NewNode(CNode*, CNode*);
	void FreeNode(CNode*);

public:
	~CAtlBaseObjectList();

	// local typedefs for class templates
	typedef CAtlBaseObject* BASE_TYPE;
	typedef CAtlBaseObject* BASE_ARG_TYPE;
};

inline int CAtlBaseObjectList::GetCount() const
{ 
	return m_nCount;
}
inline BOOL CAtlBaseObjectList::IsEmpty() const
{
	return m_nCount == 0; 
}
inline CAtlBaseObject*& CAtlBaseObjectList::GetHead()
{ 	
	return (CAtlBaseObject*&)(m_pNodeHead->data);
}
inline CAtlBaseObject* CAtlBaseObjectList::GetHead() const
{ 
	return (CAtlBaseObject*)(m_pNodeHead->data); 
}
inline CAtlBaseObject*& CAtlBaseObjectList::GetTail()
{ 
	return (CAtlBaseObject*&)(m_pNodeTail->data);
}
inline CAtlBaseObject* CAtlBaseObjectList::GetTail() const
{ 	
	return (CAtlBaseObject*)(m_pNodeTail->data); 
}
inline POS CAtlBaseObjectList::GetHeadPosition() const
{ 
	return (POS) m_pNodeHead; 
}
inline POS CAtlBaseObjectList::GetTailPosition() const
{ 
	return (POS) m_pNodeTail; 
}
inline CAtlBaseObject*& CAtlBaseObjectList::GetNext(POS& rPosition) // return *Position++
{ 
	CNode* pNode = (CNode*) rPosition;
	rPosition = (POS) pNode->pNext;
	return (CAtlBaseObject*&)(pNode->data);
}
inline CAtlBaseObject* CAtlBaseObjectList::GetNext(POS& rPosition) const // return *Position++
{ 
	CNode* pNode = (CNode*) rPosition;
	rPosition = (POS) pNode->pNext;
	return (CAtlBaseObject*)(pNode->data); 
}
inline CAtlBaseObject*& CAtlBaseObjectList::GetPrev(POS& rPosition) // return *Position--
{ 
	CNode* pNode = (CNode*) rPosition;
	rPosition = (POS) pNode->pPrev;
	return (CAtlBaseObject*&)(pNode->data); 
}
inline CAtlBaseObject* CAtlBaseObjectList::GetPrev(POS& rPosition) const // return *Position--
{ 
	CNode* pNode = (CNode*) rPosition;
	rPosition = (POS) pNode->pPrev;
	return (CAtlBaseObject*)(pNode->data); 
}
inline CAtlBaseObject*& CAtlBaseObjectList::GetAt(POS position)
{ 
	CNode* pNode = (CNode*) position;
	return (CAtlBaseObject*&)(pNode->data); 
}
inline CAtlBaseObject* CAtlBaseObjectList::GetAt(POS position) const
{
	CNode* pNode = (CNode*) position;
	return (CAtlBaseObject*)(pNode->data); 
}

inline CAtlBaseObject* CAtlBaseObjectList::GetAtIndex(long nIndex) const
{
	POS pos = FindIndex(nIndex);
	if (pos == NULL)
	{
		return NULL;
	}
	else
	{
		return GetAt(pos);
	}
}
inline void CAtlBaseObjectList::SetAt(POS pos, CAtlBaseObject* newElement)
{ 
	CNode* pNode = (CNode*) pos;
	pNode->data = newElement; 
}


#endif // !defined(_ATLBASEOBJECTLIST_H__)
