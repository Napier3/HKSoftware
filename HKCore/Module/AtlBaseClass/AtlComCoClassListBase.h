// AtlComCoClassList.h: interface for the CBaseAtlComCoClassListt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BASE_ATLCOMCOCLASSLIST_H__)
#define _ATLCOMCOCLASSLIST_H__

#include "AtlListDef.h"
#include "AtlGloblaApi.h"

template <class T> 
class CBaseAtlComCoClassList 
{
protected:
	struct CComCoClassNode
	{
		CComCoClassNode* pNext;
		CComCoClassNode* pPrev;
		T* data;
	};
	
public:
	
	// Construction
	CBaseAtlComCoClassList(int nBlockSize = 10)
	{
		m_nCount = 0;
		m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
		m_pBlocks = NULL;
		m_nBlockSize = nBlockSize;
	}
	~CBaseAtlComCoClassList()
	{
		DeleteAll();
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
		ATLASSERT(m_pNodeHead!=NULL);
		return m_pNodeHead->data; 
	}
	T* GetHeadIDispatch() const
	{ 
		IDispatch *p = NULL;
		m_pNodeHead->data->QueryInterface(IID_IDispatch, (void**)&p);
		ATLASSERT(p!=NULL);
		return p;
	}
	
	T* GetTail() const
	{ 	
		ATLASSERT(m_pNodeTail!=NULL);
		//m_pNodeTail->data->QueryInterface(IID_IDispatch, (void**)&p);
		return m_pNodeTail->data;
	}
	T* GetTailIDispatch() const
	{ 	
		IDispatch *p = NULL;
		m_pNodeTail->data->QueryInterface(IID_IDispatch, (void**)&p);
		ATLSSERT(p!=NULL);
		return p;
	}
		
	// add before head or after tail
	POS AddHead(T* newElement, BOOL bAddRef=TRUE)
	{ 
		CComCoClassNode* pNewNode = NewNode(NULL, m_pNodeHead);
		pNewNode->data = newElement;

		if (bAddRef)
		{
			newElement->AddRef();
		}
		
		if (m_pNodeHead != NULL)
			m_pNodeHead->pPrev = pNewNode;
		else
			m_pNodeTail = pNewNode;
		
		m_pNodeHead = pNewNode;
		return (POS) pNewNode;
	}
	
	POS AddTail(T* newElement, BOOL bAddRef=TRUE)
	{
		CComCoClassNode* pNewNode = NewNode(m_pNodeTail, NULL);
		pNewNode->data = newElement;
		
		if (bAddRef)
		{
			newElement->AddRef();
		}
		
		if (m_pNodeTail != NULL)
			m_pNodeTail->pNext = pNewNode;
		else
			m_pNodeHead = pNewNode;
		
		m_pNodeTail = pNewNode;
		return (POS)pNewNode;
	}
	
	
	// remove all elements
	void RemoveAll()
	{
		m_nCount = 0;
		m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
		m_pBlocks->FreeDataChain();
		m_pBlocks = NULL;
	}
	
	// iteration
	POS GetHeadPosition() const
	{ 
		return (POS) m_pNodeHead; 
	}
	
	
	POS GetTailPosition() const
	{ 
		return (POS) m_pNodeTail; 
	}
	
	T* GetNext(POS& rPosition) const
	{ 
		ATLASSERT(rPosition!=NULL);
		CComCoClassNode* pNode = (CComCoClassNode*) rPosition;
		rPosition = (POS) pNode->pNext;
		return pNode->data;
	}
	T* GetNextIDispatch(POS& rPosition) const
	{ 
		ATLASSERT(rPosition!=NULL);
		CComCoClassNode* pNode = (CComCoClassNode*) rPosition;
		rPosition = (POS) pNode->pNext;

		IDispatch *p = NULL;
		pNode->data->QueryInterface(IID_IDispatch, (void**)&p);
		return p;
	}
	
	T* GetPrev(POS& rPosition) const
	{ 
		ATLASSERT(rPosition!=NULL);
		CComCoClassNode* pNode = (CComCoClassNode*) rPosition;
		rPosition = (POS) pNode->pPrev;
		return pNode->data;
	}
	T* GetPrevIDispatch(POS& rPosition) const
	{ 
		ATLASSERT(rPosition!=NULL);
		CComCoClassNode* pNode = (CComCoClassNode*) rPosition;
		rPosition = (POS) pNode->pPrev;

		IDispatch *p = NULL;
		pNode->data->QueryInterface(IID_IDispatch, (void**)&p);
		return p;
	}
	
	// getting/modifying an element at a given position
	T* GetAt(POS position) const
	{
		ATLASSERT(position!=NULL);
		CComCoClassNode* pNode = (CComCoClassNode*) position;
		ATLASSERT(pNode!=NULL);
		return pNode->data;
	}
	IDispatch* GetAtIDispatch(POS position) const
	{
		ATLASSERT(rPosition!=NULL);
		CComCoClassNode* pNode = (CComCoClassNode*) position;
		IDispatch *p = NULL;
		pNode->data->QueryInterface(IID_IDispatch, (void**)&p);
		return p;
	}
	
	T* GetAtIndex(long nIndex) const
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
	T* GetAtIndexIDispatch(long nIndex) const
	{
		POS pos = FindIndex(nIndex);
		if (pos == NULL)
		{
			return NULL;
		}
		else
		{
			return GetAtIDispatch(pos);
		}
	}
	void SetAt(POS pos, T* newElement)
	{ 
		CComCoClassNode* pNode = (CComCoClassNode*) pos;
		pNode->data = newElement; 
	}
	void RemoveAt(POS position)
	{
		ATLASSERT(position!=NULL);
		CComCoClassNode* pOldNode = (CComCoClassNode*) position;
		// remove pOldNode from list
		if (pOldNode == m_pNodeHead)
		{
			m_pNodeHead = pOldNode->pNext;
		}
		else
		{
			pOldNode->pPrev->pNext = pOldNode->pNext;
		}
		if (pOldNode == m_pNodeTail)
		{
			m_pNodeTail = pOldNode->pPrev;
		}
		else
		{
			pOldNode->pNext->pPrev = pOldNode->pPrev;
		}
		FreeNode(pOldNode);
	}
	
	// inserting before or after a given position
	POS InsertBefore(POS position, T* newElement)
	{
		if (position == NULL)
			return AddHead(newElement); // insert before nothing -> head of the list
		
		// Insert it before position
		CComCoClassNode* pOldNode = (CComCoClassNode*) position;
		CComCoClassNode* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
		pNewNode->data = newElement;
		newElement->AddRef();
		
		if (pOldNode->pPrev != NULL)
		{
			pOldNode->pPrev->pNext = pNewNode;
		}
		else
		{
			m_pNodeHead = pNewNode;
		}
		pOldNode->pPrev = pNewNode;
		return (POS) pNewNode;
		
	}
	
	POS InsertAfter(POS position, T* newElement)
	{
		if (position == NULL)
			return AddTail(newElement); // insert after nothing -> tail of the list
		
		// Insert it before position
		CComCoClassNode* pOldNode = (CComCoClassNode*) position;
		CComCoClassNode* pNewNode = NewNode(pOldNode, pOldNode->pNext);
		pNewNode->data = newElement;
		newElement->AddRef();
		
		if (pOldNode->pNext != NULL)
		{
			pOldNode->pNext->pPrev = pNewNode;
		}
		else
		{
			m_pNodeTail = pNewNode;
		}
		pOldNode->pNext = pNewNode;
		return (POS) pNewNode;
		
	}
	
	// helper functions (note: O(n) speed)
	POS Find(T* searchValue, POS startAfter = NULL) const
	{
		CComCoClassNode* pNode = (CComCoClassNode*) startAfter;
		if (pNode == NULL)
		{
			pNode = m_pNodeHead;  // start at head
		}
		else
		{
			pNode = pNode->pNext;  // start after the one specified
		}
		
		for (; pNode != NULL; pNode = pNode->pNext)
		{
			if (pNode->data == searchValue)
				return (POS) pNode;
		}
		
		return NULL;
	}

	// defaults to starting at the HEAD
	// return NULL if not found
	POS FindIndex(int nIndex) const
	{
		if (nIndex >= m_nCount || nIndex < 0)
			return NULL;  // went too far
		
		CComCoClassNode* pNode = m_pNodeHead;
		
		while (nIndex--)
		{
			pNode = pNode->pNext;
		}
		return (POS) pNode;
	}
	
	virtual T* FindByName(BSTR bstrName)
	{
		T* pFind = NULL;
		//pFind = T->FindByName(BSTR bstrName);

		return pFind;
	}

	virtual T* FindByID(BSTR bstrID)
	{
		T* pFind = NULL;
		//pFind = T->FindByID(BSTR bstrID);
		
		return pFind;
	}
	BOOL Delete(VARIANT *vIndex, long *pnReturn)
	{
		long nIndex = 0;
		BSTR bstrIndex;
		BOOL bReturn = FALSE;
		
		if (VARIANT_to_long(*vIndex, nIndex))
		{
			bReturn = DeleteAtIndex(nIndex);
		}
		else if (VARIANT_to_CComBSTR(*vIndex, &bstrIndex))
		{
			T *pTemp = FindByID(bstrIndex);
			if (pTemp != NULL)
			{
				POS pos = Find(pTemp);
				if (pos != NULL)
				{
					DeleteAt(pos);
					bReturn = TRUE;
				}
			}
		}
		else
		{
		}
		
		*pnReturn = bReturn;
		return bReturn;
	}

public:
	//////////////////////////////////////////////////////////////////////////
	//delete operations 
	virtual void DeleteAll()
	{
		CComCoClassNode* pNode = m_pNodeHead;
		CComCoClassNode* pNodeTemp = m_pNodeHead;
		T* pObject = NULL;
		
		while (pNode != NULL)
		{
			pNodeTemp = pNode->pNext;
			pObject = (T*)pNode->data;
			pObject->Release();//此函数调用并不通过_QIThunk::Release()函数，故输出没显示。
			FreeNode(pNode);
			pNode = pNodeTemp;
		}
		
		m_nCount = 0;
		m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
		m_pBlocks->FreeDataChain();
		m_pBlocks = NULL;
	}
	virtual BOOL DeleteAt(POS position)
	{
		T *pObj = GetAt(position);
		if (pObj != NULL)	{	pObj->Release();	RemoveAt(position);	return TRUE;	}
		else				{	return FALSE;	}
	}
	virtual BOOL DeleteAtIndex(long nIndex)
	{
		POS position = FindIndex(nIndex);
		return DeleteAt(position);
	}

	virtual void ChangePosition(POS pos1, POS pos2)
	{
		T* p1 = GetAt(pos1);
		T* p2 = GetAt(pos2);
		SetAt(pos1, p2);
		SetAt(pos2, p1);
	}
	
	virtual void ChangePosition(VARIANT *vIndex1, VARIANT *vIndex2)
	{
		POS pos1 = NULL, pos2 = NULL;
		long nIndex1 = 0, nIndex2 = 0;
		BSTR bstrVariable1 = NULL, bstrVariable2 = NULL;
		T *pTemp = NULL;
		
		if (VARIANT_to_long(*vIndex1, nIndex1))
		{
			pos1 = FindIndex(nIndex1);
		}
		else if (VARIANT_to_CComBSTR(*vIndex1, &bstrVariable1))
		{
			pTemp = FindByID(bstrVariable1);
			pos1 = Find(pTemp);
		}
		else
		{
			pos1 = NULL;
		}
		
		if (VARIANT_to_long(*vIndex2, nIndex2))
		{
			pos2 = FindIndex(nIndex2);
		}
		else if (VARIANT_to_CComBSTR(*vIndex2, &bstrVariable2))
		{
			pTemp = FindByID(bstrVariable2);
			pos2 = Find(pTemp);
		}
		else
		{
			pos2 = NULL;
		}
		
		if ((pos1 == NULL) || (pos2 == NULL))
		{
		}
		else
		{
			ChangePosition(pos1, pos2);
		}
	}

	virtual void BringToTail(VARIANT *vIndex)
	{
		long nIndex = 0;
		BSTR bstrIndex;
		POS pos = NULL;
		
		if (VARIANT_to_long(*vIndex, nIndex))
		{
			pos = FindIndex(nIndex);
		}
		else if (VARIANT_to_CComBSTR(*vIndex, &bstrIndex))
		{
			T *pTemp = FindByID(bstrIndex);
			if (pTemp != NULL)
			{
				pos = Find(pTemp);
			}
		}
		else
		{
		}
		
		if (pos != NULL)
		{
			T* p = GetAt(pos);
			RemoveAt(pos);
			AddTail(p, FALSE);
		}
	}

	virtual void BringToHead(VARIANT *vIndex)
	{
		long nIndex = 0;
		BSTR bstrIndex;
		POS pos = NULL;
		
		if (VARIANT_to_long(*vIndex, nIndex))
		{
			pos = FindIndex(nIndex);
		}
		else if (VARIANT_to_CComBSTR(*vIndex, &bstrIndex))
		{
			T *pTemp = FindByID(bstrIndex);
			if (pTemp != NULL)
			{
				pos = Find(pTemp);
			}
		}
		else
		{
		}
		
		if (pos != NULL)
		{
			T* p = GetAt(pos);
			RemoveAt(pos);
			AddHead(p, FALSE);
		}
	}
	
	// Implementation
protected:
	CComCoClassNode* m_pNodeHead;
	CComCoClassNode* m_pNodeTail;
	int m_nCount;
	CComCoClassNode* m_pNodeFree;
	struct CAtlPlex* m_pBlocks;
	int m_nBlockSize;
	
	CComCoClassNode* NewNode(CComCoClassNode*, CComCoClassNode*);
	void FreeNode(CComCoClassNode*);
	
public:
	
	// local typedefs for class templates
	typedef T* BASE_TYPE;
	typedef T* BASE_ARG_TYPE;
	
};


template <class T>
inline typename CBaseAtlComCoClassList<T>::CComCoClassNode* CBaseAtlComCoClassList<T>::NewNode(CComCoClassNode* pPrev, CComCoClassNode* pNext)
{
	if (m_pNodeFree == NULL)
	{
		// add another block
		CAtlPlex* pNewBlock = CAtlPlex::Create(m_pBlocks, m_nBlockSize,
				 sizeof(CComCoClassNode));

		// chain them into free list
		CComCoClassNode* pNode = (CComCoClassNode*) pNewBlock->data();
		// free in reverse order to make it easier to debug
		pNode += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
		{
			pNode->pNext = m_pNodeFree;
			m_pNodeFree = pNode;
		}
	}

	CComCoClassNode* pNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNode->pPrev = pPrev;
	pNode->pNext = pNext;
	m_nCount++;
	pNode->data = 0; // start with zero

	return pNode;
}

template <class T>
inline void CBaseAtlComCoClassList<T>::FreeNode(CComCoClassNode* pNode)
{

	pNode->pNext = m_pNodeFree;
	m_pNodeFree = pNode;
	m_nCount--;

	if (m_nCount == 0)
		RemoveAll();
}


template <class T> 
class CAtlComCoClassListex : public CBaseAtlComCoClassList <T>
{
	virtual T* FindByName(BSTR bstrName)
	{
		T* pTemp = NULL;
		T* pFind = NULL;
		
		POS pos = GetHeadPosition();
		
		while (pos != NULL)
		{
			pTemp = GetNext(pos);
			
			if(pTemp->m_strName == bstrName)
			{
				pFind = pTemp;
				break;
			}
		}
		
		return pFind;
	}
	
	virtual T* FindByID(BSTR bstrID)
	{
		T* pTemp = NULL;
		T* pFind = NULL;
		
		POS pos = GetHeadPosition();
		
		while (pos != NULL)
		{
			pTemp = GetNext(pos);
			
			if(pTemp->m_strID == bstrID)
			{
				pFind = pTemp;
				break;
			}
		}
		
		return pFind;
	}	
};



#endif // !defined(_ATLCOMCOCLASSLIST_H__)
