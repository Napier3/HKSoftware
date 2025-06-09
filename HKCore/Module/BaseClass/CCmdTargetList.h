// CCmdTargetList.h: interface for the CCmdTargetList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CCmdTargetList_H__)
#define _CCmdTargetList_H__

#include "TLinkList.h"
#include "..\AtlBaseClass\AtlGloblaApi.h"

class CCmdTargetList 
{
private:
	struct  CPlex     // warning variable length structure
	{
		CPlex* pNext;
#if (_AFX_PACKING >= 8)
		DWORD dwReserved[1];    // align on 8 byte boundary
#endif
		// BYTE data[maxNum*elementSize];

		void* data() { return this+1; }

		static CPlex* PASCAL Create(CPlex*& pHead, UINT nMax, UINT cbElement)
		{
			//	ASSERT(nMax > 0 && cbElement > 0);
			CPlex* p = (CPlex*) new BYTE[sizeof(CPlex) + nMax * cbElement];
			// may throw exception
			p->pNext = pHead;
			pHead = p;  // change head (adds in reverse order for simplicity)
			return p;
		}
		// like 'calloc' but no zero fill
		// may throw memory exceptions

		void FreeDataChain()       // free this one and links
		{
			CPlex* p = this;
			while (p != NULL)
			{
				BYTE* bytes = (BYTE*) p;
				CPlex* pNext = p->pNext;
				delete[] bytes;
				p = pNext;
			}
		}
	};

protected:
	struct CCmdTargetNode
	{
		CCmdTargetNode* pNext;
		CCmdTargetNode* pPrev;
		CCmdTarget* data;
	};
	
public:
	
	// Construction
	CCmdTargetList(int nBlockSize = 10)
	{
		m_nCount = 0;
		m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
		m_pBlocks = NULL;
		m_nBlockSize = nBlockSize;
	}
	~CCmdTargetList()
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
	CCmdTarget* GetHead() const
	{ 
		ASSERT(m_pNodeHead!=NULL);
		return m_pNodeHead->data; 
	}

	IDispatch* GetHeadIDispatch() const
	{ 
		return m_pNodeHead->data->GetIDispatch(TRUE);
	}
	
	CCmdTarget* GetTail() const
	{ 	
		ASSERT(m_pNodeTail !=NULL);

		if (m_pNodeTail == NULL)
		{
			return NULL;
		}
		else
		{
			return m_pNodeTail->data;
		}
	}

	IDispatch* GetTailIDispatch() const
	{ 	
		ASSERT(m_pNodeTail !=NULL);

		if (m_pNodeTail == NULL)
		{
			return NULL;
		}
		else
		{
			return m_pNodeHead->data->GetIDispatch(TRUE);
		}
	}
		
	// add before head or after tail
	POS AddHead(CCmdTarget* newElement, BOOL bAddRef=TRUE)
	{ 
		CCmdTargetNode* pNewNode = NewNode(NULL, m_pNodeHead);
		pNewNode->data = newElement;

		if (bAddRef)
		{
			newElement->ExternalAddRef();
		}
		
		if (m_pNodeHead != NULL)
			m_pNodeHead->pPrev = pNewNode;
		else
			m_pNodeTail = pNewNode;
		
		m_pNodeHead = pNewNode;

		return (POS) pNewNode;
	}
	
	void AddTail(CCmdTarget* newElement, BOOL bAddRef=TRUE)
	{
		CCmdTargetNode* pNewNode = NewNode(m_pNodeTail, NULL);
		pNewNode->data = newElement;
		
		if (bAddRef)
		{
			newElement->ExternalAddRef();
		}
		
		if (m_pNodeTail != NULL)
			m_pNodeTail->pNext = pNewNode;
		else
			m_pNodeHead = pNewNode;
		
		m_pNodeTail = pNewNode;
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
	
	CCmdTarget* GetNext(POS& rPosition) const
	{ 
		ASSERT(rPosition!=NULL);
		CCmdTargetNode* pNode = (CCmdTargetNode*) rPosition;
		rPosition = (POS) pNode->pNext;
		return pNode->data;
	}

	IDispatch* GetNextIDispatch(POS& rPosition) const
	{ 
		ASSERT(rPosition!=NULL);
		CCmdTargetNode* pNode = (CCmdTargetNode*) rPosition;
		rPosition = (POS) pNode->pNext;

		return pNode->data->GetIDispatch(TRUE);;
	}
	
	CCmdTarget* GetPrev(POS& rPosition) const
	{ 
		ASSERT(rPosition!=NULL);
		CCmdTargetNode* pNode = (CCmdTargetNode*) rPosition;
		rPosition = (POS) pNode->pPrev;
		return pNode->data;
	}
	
	IDispatch* GetPrevIDispatch(POS& rPosition) const
	{ 
		ASSERT(rPosition!=NULL);
		CCmdTargetNode* pNode = (CCmdTargetNode*) rPosition;
		rPosition = (POS) pNode->pPrev;

		return pNode->data->GetIDispatch(TRUE);
	}
	
	// getting/modifying an element at a given position
	CCmdTarget* GetAt(POS position) const
	{
		ASSERT(position!=NULL);
		CCmdTargetNode* pNode = (CCmdTargetNode*) position;
		ASSERT(pNode!=NULL);
		return pNode->data;
	}

	IDispatch* GetAtIDispatch(POS position) const
	{
		ASSERT(position!=NULL);
		CCmdTargetNode* pNode = (CCmdTargetNode*) position;
		return pNode->data->GetIDispatch(TRUE);
	}
	
	CCmdTarget* GetAtIndex(long nIndex) const
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

	IDispatch* GetAtIndexIDispatch(long nIndex) const
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

	void SetAt(POS pos, CCmdTarget* newElement)
	{ 
		CCmdTargetNode* pNode = (CCmdTargetNode*) pos;
		pNode->data = newElement; 
	}

	void RemoveAt(POS position)
	{
		ASSERT(position!=NULL);
		CCmdTargetNode* pOldNode = (CCmdTargetNode*) position;
	
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
	POS InsertBefore(POS position, CCmdTarget* newElement, BOOL bAddRef=TRUE)
	{
		if (position == NULL)
			return AddHead(newElement); // insert before nothing -> head of the list
		
		// Insert it before position
		CCmdTargetNode* pOldNode = (CCmdTargetNode*) position;
		CCmdTargetNode* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
		pNewNode->data = newElement;

		if (bAddRef)
		{
			newElement->ExternalAddRef();
		}
		
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
	
	POS InsertAfter(POS position, CCmdTarget* newElement, BOOL bAddRef=TRUE)
	{
		if (position == NULL)
		{
			AddTail(newElement, bAddRef); // insert after nothing -> tail of the list
			return (POS)m_pNodeTail;
		}
		
		// Insert it before position
		CCmdTargetNode* pOldNode = (CCmdTargetNode*) position;
		CCmdTargetNode* pNewNode = NewNode(pOldNode, pOldNode->pNext);
		pNewNode->data = newElement;
	
		if (bAddRef)
		{
			newElement->ExternalAddRef();
		}

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
	POS Find(CCmdTarget* searchValue, POS startAfter = NULL) const
	{
		CCmdTargetNode* pNode = (CCmdTargetNode*) startAfter;

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
			{
				return (POS) pNode;
			}
		}
		
		return NULL;
	}

	// defaults to starting at the HEAD
	// return NULL if not found
	POS FindIndex(int nIndex) const
	{
		if (nIndex >= m_nCount || nIndex < 0)
		{
			return NULL;  // went too far
		}
		
		CCmdTargetNode* pNode = m_pNodeHead;
		
		while (nIndex--)
		{
			if (pNode == NULL)
			{
				break;
			}

			pNode = pNode->pNext;
		}

		return (POS) pNode;
	}
	
// 	CCmdTarget* FindByName(BSTR bstrName)
// 	{
// 		CCmdTarget* pTemp = NULL;
// 		CCmdTarget* pFind = NULL;
// 
// 		POS pos = GetHeadPosition();
// 
// 		while (pos != NULL)
// 		{
// 			pTemp = GetNext(pos);
// 
// 			if(pTemp->m_strName == bstrName)
// 			{
// 				pFind = pTemp;
// 				break;
// 			}
// 		}
// 
// 		return pFind;
// 	}
// 
// 	CCmdTarget* FindByID(BSTR bstrID)
// 	{
// 		CCmdTarget* pTemp = NULL;
// 		CCmdTarget* pFind = NULL;
// 		
// 		POS pos = GetHeadPosition();
// 		
// 		while (pos != NULL)
// 		{
// 			pTemp = GetNext(pos);
// 			
// 			if(pTemp->m_strID == bstrID)
// 			{
// 				pFind = pTemp;
// 				break;
// 			}
// 		}
// 		
// 		return pFind;
// 	}
// 
// 	BOOL Delete(VARIANT *vIndex, long *pnReturn)
// 	{
// 		long nIndex = 0;
// 		BSTR bstrIndex;
// 		BOOL bReturn = FALSE;
// 		
// 		if (VARIANT_to_long(*vIndex, nIndex))
// 		{
// 			bReturn = DeleteAtIndex(nIndex);
// 		}
// 		else if (VARIANT_to_CComBSTR(*vIndex, &bstrIndex))
// 		{
// 			CCmdTarget *pTemp = FindByID(bstrIndex);
// 			if (pTemp != NULL)
// 			{
// 				POS pos = Find(pTemp);
// 				if (pos != NULL)
// 				{
// 					DeleteAt(pos);
// 					bReturn = TRUE;
// 				}
// 			}
// 		}
// 		else
// 		{
// 		}
// 		
// 		*pnReturn = bReturn;
// 		return bReturn;
// 	}

public:
	//////////////////////////////////////////////////////////////////////////
	//delete operations 
	virtual void DeleteAll()
	{
		CCmdTargetNode* pNode = m_pNodeHead;
		CCmdTargetNode* pNodeTemp = m_pNodeHead;
		CCmdTarget* pObject = NULL;
		
		while (pNode != NULL)
		{
			pNodeTemp = pNode->pNext;
			pObject = (CCmdTarget*)pNode->data;
			pObject->ExternalRelease();
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
		CCmdTarget *pObj = GetAt(position);
		if (pObj != NULL)	
		{	
			pObj->ExternalRelease();	
			RemoveAt(position);	
			return TRUE;	
		}
		else				
		{	
			return FALSE;	
		}
	}

	virtual BOOL DeleteAtIndex(long nIndex)
	{
		POS position = FindIndex(nIndex);
		return DeleteAt(position);
	}

	virtual void ChangePosition(POS pos1, POS pos2)
	{
		CCmdTarget* p1 = GetAt(pos1);
		CCmdTarget* p2 = GetAt(pos2);
		SetAt(pos1, p2);
		SetAt(pos2, p1);
	}
	
	virtual void ChangePosition(VARIANT *vIndex1, VARIANT *vIndex2)
	{
		POS pos1 = NULL, pos2 = NULL;
		long nIndex1 = 0, nIndex2 = 0;
		BSTR bstrVariable1 = NULL, bstrVariable2 = NULL;
		CCmdTarget *pTemp = NULL;
		
		if (VARIANT_to_long(*vIndex1, nIndex1))
		{
			pos1 = FindIndex(nIndex1);
		}
// 		else if (VARIANT_to_CComBSTR(*vIndex1, &bstrVariable1))
// 		{
// 			pTemp = FindByID(bstrVariable1);
// 			pos1 = Find(pTemp);
// 		}
		else
		{
			pos1 = NULL;
		}
		
		if (VARIANT_to_long(*vIndex2, nIndex2))
		{
			pos2 = FindIndex(nIndex2);
		}
// 		else if (VARIANT_to_CComBSTR(*vIndex2, &bstrVariable2))
// 		{
// 			pTemp = FindByID(bstrVariable2);
// 			pos2 = Find(pTemp);
// 		}
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
//		BSTR bstrIndex;
		POS pos = NULL;
		
		if (VARIANT_to_long(*vIndex, nIndex))
		{
			pos = FindIndex(nIndex);
		}
// 		else if (VARIANT_to_CComBSTR(*vIndex, &bstrIndex))
// 		{
// 			CCmdTarget *pTemp = FindByID(bstrIndex);
// 			if (pTemp != NULL)
// 			{
// 				pos = Find(pTemp);
// 			}
// 		}
		else
		{
		}
		
		if (pos != NULL)
		{
			CCmdTarget* p = GetAt(pos);
			RemoveAt(pos);
			AddTail(p, FALSE);
		}
	}

	virtual void BringToHead(VARIANT *vIndex)
	{
		long nIndex = 0;
//		BSTR bstrIndex;
		POS pos = NULL;
		
		if (VARIANT_to_long(*vIndex, nIndex))
		{
			pos = FindIndex(nIndex);
		}
// 		else if (VARIANT_to_CComBSTR(*vIndex, &bstrIndex))
// 		{
// 			CCmdTarget *pTemp = FindByID(bstrIndex);
// 			if (pTemp != NULL)
// 			{
// 				pos = Find(pTemp);
// 			}
// 		}
		else
		{
		}
		
		if (pos != NULL)
		{
			CCmdTarget* p = GetAt(pos);
			RemoveAt(pos);
			AddHead(p, FALSE);
		}
	}
	
	// Implementation
protected:
	CCmdTargetNode* m_pNodeHead;
	CCmdTargetNode* m_pNodeTail;
	int m_nCount;
	CCmdTargetNode* m_pNodeFree;
	struct CPlex* m_pBlocks;
	int m_nBlockSize;
	
	CCmdTargetNode* NewNode(CCmdTargetNode* pPrev, CCmdTargetNode* pNext)
	{
		if (m_pNodeFree == NULL)
		{
			// add another block
			CPlex* pNewBlock = CPlex::Create(m_pBlocks, m_nBlockSize,
				sizeof(CCmdTargetNode));

			// chain them into free list
			CCmdTargetNode* pNode = (CCmdTargetNode*) pNewBlock->data();
			// free in reverse order to make it easier to debug
			pNode += m_nBlockSize - 1;
			for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
			{
				pNode->pNext = m_pNodeFree;
				m_pNodeFree = pNode;
			}
		}

		CCmdTargetNode* pNode = m_pNodeFree;
		m_pNodeFree = m_pNodeFree->pNext;
		pNode->pPrev = pPrev;
		pNode->pNext = pNext;
		m_nCount++;
		pNode->data = 0; // start with zero

		return pNode;
	}
	void FreeNode(CCmdTargetNode*);
	
public:
	
	// local typedefs for class templates
	typedef CCmdTarget* BASE_TYPE;
	typedef CCmdTarget* BASE_ARG_TYPE;
	
};


// inline CCmdTargetList::CCmdTargetNode* CCmdTargetList::CCmdTargetNode* CCmdTargetList::NewNode(CCmdTargetNode* pPrev, CCmdTargetNode* pNext)
// {
// 	if (m_pNodeFree == NULL)
// 	{
// 		// add another block
// 		CPlex* pNewBlock = CPlex::Create(m_pBlocks, m_nBlockSize,
// 				 sizeof(CCmdTargetNode));
// 
// 		// chain them into free list
// 		CCmdTargetNode* pNode = (CCmdTargetNode*) pNewBlock->data();
// 		// free in reverse order to make it easier to debug
// 		pNode += m_nBlockSize - 1;
// 		for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
// 		{
// 			pNode->pNext = m_pNodeFree;
// 			m_pNodeFree = pNode;
// 		}
// 	}
// 
// 	CCmdTargetNode* pNode = m_pNodeFree;
// 	m_pNodeFree = m_pNodeFree->pNext;
// 	pNode->pPrev = pPrev;
// 	pNode->pNext = pNext;
// 	m_nCount++;
// 	pNode->data = 0; // start with zero
// 
// 	return pNode;
// }

inline void CCmdTargetList::FreeNode(CCmdTargetNode* pNode)
{

	pNode->pNext = m_pNodeFree;
	m_pNodeFree = pNode;
	m_nCount--;

	if (m_nCount == 0)
		RemoveAll();
}


#endif // !defined(_ATLCmdTargetLIST_H__)
