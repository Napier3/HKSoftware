// LINKLIST.h: interface for the CLinkListt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_LINKLIST_H__)
#define _LINKLIST_H__

#ifdef _PSX_IDE_QT_
#include "../OSInterface/QT/CString_QT.h"
#endif


struct __POS { } ;
typedef __POS* POS;

#ifndef TLinkList_BlockSize
#define TLinkList_BlockSize  10
#endif

template <class T> 
class CTLinkList 
{
protected:
	class CListPlex     // warning variable length structure
	{
	public:
		CListPlex* pNext;
// #if (_AFX_PACKING >= 8)
// 		DWORD dwReserved[1];    // align on 8 byte boundary
// #endif
		// BYTE data[maxNum*elementSize];
		
		void* data() { return this+1; }
		
		static CListPlex* Create(CListPlex*& pHead, unsigned int nMax, unsigned int cbElement)
		{
            //ASSERT(nMax > 0 && cbElement > 0);
			CListPlex* p = (CListPlex*) new unsigned char[sizeof(CListPlex) + nMax * cbElement];
			// may throw exception
			p->pNext = pHead;
			pHead = p;  // change head (adds in reverse order for simplicity)
			return p;
		}
		
		
		void FreeDataChain()       // free this one and links
		{
			CListPlex* p = this;
			while (p != NULL)
			{
				CListPlex* pNext = p->pNext;
                delete[] ( (unsigned char*) p);
				p = pNext;
			}
		}
		
	};
	
	struct CNode
	{
		CNode* pNext;
		CNode* pPrev;
		T* data;
	};
	
public:
	
	// Construction
	CTLinkList(int nBlockSize = TLinkList_BlockSize)
	{
		m_nCount = 0;
		m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
		m_pBlocks = NULL;
		m_nBlockSize = nBlockSize;
	}
	virtual ~CTLinkList()
	{
		DeleteAll();
	}
	
	// Attributes (head and tail)
	// count of elements
	int GetCount() const
	{ 
		return m_nCount;
	}
	
	bool IsEmpty() const
	{
		return m_nCount == 0; 
	}
	
	// peek at head or tail
	T* GetHead() const
	{ 
		//ASSERT (m_pNodeHead != NULL);
		return (m_pNodeHead == NULL) ? NULL : m_pNodeHead->data;
	}
	
	T* GetTail() const
	{ 	
		//ASSERT (m_pNodeTail != NULL);
		return (m_pNodeTail == NULL) ? NULL : m_pNodeTail->data;
	}
		
	// add before head or after tail
	POS AddHead(T* newElement)
	{
		CNode* pNewNode = NewNode(NULL, m_pNodeHead);
		pNewNode->data = newElement;

		if (m_pNodeHead != NULL)
			m_pNodeHead->pPrev = pNewNode;
		else
			m_pNodeTail = pNewNode;
		
		m_pNodeHead = pNewNode;
		return (POS) pNewNode;
	}
	
	POS AddTail(T* newElement)
	{
		CNode* pNewNode = NewNode(m_pNodeTail, NULL);
		pNewNode->data = newElement;
		
		if (m_pNodeTail != NULL)
			m_pNodeTail->pNext = pNewNode;
		else
			m_pNodeHead = pNewNode;
		
		m_pNodeTail = pNewNode;
		return (POS)m_pNodeTail;
	}
	POS AddNode(T* newElement)
	{
		return AddTail(newElement);
	}
	
	// remove all elements
	void RemoveAll()
	{
		m_nCount = 0;
		m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;

		if (m_pBlocks != NULL)
		{
			m_pBlocks->FreeDataChain();
		}

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
		CNode* pNode = (CNode*) rPosition;
		rPosition = (POS) pNode->pNext;
		return pNode->data;
	}
	
	T* GetPrev(POS& rPosition) const
	{ 
		CNode* pNode = (CNode*) rPosition;
		rPosition = (POS) pNode->pPrev;
		return pNode->data;
	}
	
	// getting/modifying an element at a given position
	T* GetAt(POS position) const
	{
		CNode* pNode = (CNode*) position;
		return pNode->data;
	}
	T* GetAt(long nIndex) const
	{
		return GetAtIndex(nIndex);
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
	void SetAt(POS pos, T* newElement)
	{ 
		CNode* pNode = (CNode*) pos;
		pNode->data = newElement; 
	}
	T* RemoveAt(long nIndex)
	{
		POS position = FindIndex(nIndex);
		return RemoveAt(position);
	}
	T* RemoveAt(POS position)
	{
		CNode* pOldNode = (CNode*) position;
		T *pData = NULL;
		pData = pOldNode->data;
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

		return pData;
	}

	T* RemoveHead()
	{
		if (m_pNodeHead == NULL)
		{
			return NULL;
		}

		CNode* pOldNode =m_pNodeHead;
		T *pData = pOldNode->data;
		m_pNodeHead = m_pNodeHead->pNext;

		if (m_pNodeHead == NULL)
		{
			m_pNodeTail = NULL;
		}

		FreeNode(pOldNode);

		return pData;
	}
	
	T* RemoveTail()
	{
		if (m_pNodeTail == NULL)
		{
			return NULL;
		}

		CNode* pOldNode =m_pNodeTail;
		T *pData = m_pNodeTail->data;
		m_pNodeTail = m_pNodeTail->pPrev;

		if (m_pNodeTail == NULL)
		{
			m_pNodeHead = NULL;
		}

		FreeNode(pOldNode);

		return pData;
	}

	// inserting before or after a given position
	POS InsertBefore(POS position, T* newElement)
	{
		if (position == NULL)
			return AddHead(newElement); // insert before nothing -> head of the list
		
		// Insert it before position
		CNode* pOldNode = (CNode*) position;
		CNode* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
		pNewNode->data = newElement;
		
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
		CNode* pOldNode = (CNode*) position;
		CNode* pNewNode = NewNode(pOldNode, pOldNode->pNext);
		pNewNode->data = newElement;
		
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
		CNode* pNode = (CNode*) startAfter;
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
		
		CNode* pNode = m_pNodeHead;
		
		while (nIndex--)
		{
			pNode = pNode->pNext;
		}
		return (POS) pNode;
	}

	long FindIndex(POS pos)
	{
		// Create a pointer to hold each current node and the next node	
		CNode *pCurrNode = NULL;
		long nIndex = 0;
		long nIndexFind = -1;
		
		// Set the current node to the head of the list
		pCurrNode = m_pNodeHead;
		
		// Traverse the list
		while ( pCurrNode != NULL )
		{
			//Find the node
			if (pCurrNode == (CNode*)pos)
			{
				nIndexFind = nIndex;
				break;
			}

			// Save the pointer to the next node before Removeing the current one
			pCurrNode = pCurrNode->pNext;
			nIndex++;
		}
		
		return nIndexFind;
	}
	
	long FindIndex(T *pData)
	{
		// Create a pointer to hold each current node and the next node	
		CNode *pCurrNode = NULL;
		long nIndex = 0;
		long nIndexFind = -1;

		// Set the current node to the head of the list
		pCurrNode = m_pNodeHead;

		// Traverse the list
		while ( pCurrNode != NULL )
		{
			//Find the node
			if (pCurrNode->data == pData)
			{
				nIndexFind = nIndex;
				break;
			}

			// Save the pointer to the next node before Removeing the current one
			pCurrNode = pCurrNode->pNext;
			nIndex++;
		}

		return nIndexFind;
	}

	
	
	bool Delete(long nIndex)
	{
		return DeleteAtIndex(nIndex);
	}

	bool Delete(T *pData)
	{
		POS pos = Find(pData);

		if (pos != NULL)
		{
			DeleteAt(pos);
			return 1;
		}
		else
		{
			return 0;
		}
	}

	bool Remove(T *pData)
	{
		POS pos = Find(pData);

		if (pos != NULL)
		{
			RemoveAt(pos);
			return 1;
		}
		else
		{
			return 0;
		}
	}
public:
	//////////////////////////////////////////////////////////////////////////
	//delete operations 
	virtual void DeleteAll()
	{
		CNode* pNode = m_pNodeHead;
		CNode* pNodeTemp = m_pNodeHead;
		
		while (pNode != NULL)
		{
			pNodeTemp = pNode->pNext;
			delete ((T*)pNode->data);
			FreeNode2(pNode);
			pNode = pNodeTemp;
		}

		RemoveAll();
		
		m_nCount = 0;
		m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;

		if (m_pBlocks != NULL)
		{
			m_pBlocks->FreeDataChain();
		}

		m_pBlocks = NULL;
	}
	virtual bool DeleteAt(long nIndex)
	{
		POS pos = FindIndex(nIndex);
		return DeleteAt(pos);
	}
	virtual bool DeleteAt(POS position)
	{
		T *pObj = GetAt(position);
		if (pObj != NULL)	{	delete pObj;	RemoveAt(position);	return 1;	}
		else				{	return 0;	}
	}
	virtual bool DeleteAtIndex(long nIndex)
	{
		POS position = FindIndex(nIndex);
		return DeleteAt(position);
	}

	virtual void DeleteHead()
	{
		if (m_pNodeHead == NULL)
		{
			return;
		}

		CNode *pNode = m_pNodeHead;
		m_pNodeHead = m_pNodeHead->pNext;
		delete pNode->data;
		FreeNode(pNode);
	}
	virtual void DeleteTail()
	{
		DeleteAt(GetCount()-1);
	}
	virtual void ChangePosition(POS pos1, POS pos2)
	{
		T* p1 = GetAt(pos1);
		T* p2 = GetAt(pos2);
		SetAt(pos1, p2);
		SetAt(pos2, p1);
	}
	
	virtual void ChangePosition(long nIndex1, long nIndex2)
	{
		POS pos1 = NULL, pos2 = NULL;
		pos1 = FindIndex(nIndex1);
		pos2 = FindIndex(nIndex2);
		
		if ((pos1 == NULL) || (pos2 == NULL))
		{
		}
		else
		{
			ChangePosition(pos1, pos2);
		}
	}

	virtual void ChangePosition(T *p1, T *p2)
	{
		POS pos1 = NULL, pos2 = NULL;
		pos1 = Find(p1);
		pos2 = Find(p2);

		if ((pos1 != NULL) && (pos2 != NULL))
		{
			SetAt(pos1, p2);
			SetAt(pos2, p1);
		}
	}

	virtual void BringToTail(long nIndex)
	{
		POS pos = NULL;
		pos = FindIndex(nIndex);
		
		if (pos != NULL)
		{
			T* p = GetAt(pos);
			RemoveAt(pos);
			AddTail(p);
		}
	}
	virtual void BringToTail(POS pos)
	{
		if (pos != NULL)
		{
			T* p = GetAt(pos);
			RemoveAt(pos);
			AddTail(p);
		}
	}
	virtual void BringToTail(T *p)
	{
		POS pos = Find(p);

		if ( (pos != NULL) && (pos != (POS)m_pNodeTail) )
		{
			T* p = GetAt(pos);
			RemoveAt(pos);
			AddTail(p);
		}
	}

	virtual void BringToHead(long nIndex)
	{
		POS pos = NULL;
		pos = FindIndex(nIndex);
		
		if (pos != NULL)
		{
			T* p = GetAt(pos);
			RemoveAt(pos);
			AddHead(p);
		}
	}
	virtual void BringToHead(POS pos)
	{
		if (pos != NULL)
		{
			T* p = GetAt(pos);
			RemoveAt(pos);
			AddHead(p);
		}
	}
	virtual void BringToHead(T *p)
	{
		POS pos = Find(p);

		if ( (pos != NULL) && (pos != (POS)m_pNodeHead) )
		{
			T* p = GetAt(pos);
			RemoveAt(pos);
			AddHead(p);
		}
	}
	
	T* operator[](long nIndex)
	{
		return GetAt(nIndex);
	}

	T* FindByName(const CString &strName)
	{
		T* pTemp = NULL;
		T* pFind = NULL;

		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strName == strName)
			{
				pFind = pTemp;
				break;
			}
		}

		return pFind;
	}
	T* FindByID(const CString &strID)
	{
		T* pTemp = NULL;
		T* pFind = NULL;

		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strID == strID)
			{
				pFind = pTemp;
				break;
			}
		}

		return pFind;
	}
	T* FindByIDNoCase(const CString &strID)
	{
		T* pTemp = NULL;
		T* pFind = NULL;

		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strID.CompareNoCase(strID) == 0)
			{
				pFind = pTemp;
				break;
			}
		}

		return pFind;
	}

	T* FindByIDEx(const CString &strID)
	{
		T* p = FindByID(strID);

		if (p != NULL)
		{
			return p;
		}

		return FindByIDNoCase(strID);
	}


	long FindIndexByID(const CString &strID)
	{
		T* pTemp = NULL;
		long nIndex = 0;
		long nIndexFind = -1;

		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strID == strID)
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
		POS posPrev = NULL;

		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			posPrev = pos;
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strID == strID)
			{
				posFind = posPrev;
				break;
			}
		}

		return posFind;
	}

	long FindIndexByName(const CString &strName)
	{
		T* pTemp = NULL;
		long nIndex = 0;
		long nIndexFind = -1;

		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strName == strName)
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
		POS posPrev = NULL;

		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			posPrev = pos;
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strName == strName)
			{
				posFind = posPrev;
				break;
			}
		}

		return posFind;
	}

	long SearchByName(const CString &strName)
	{
		T* pTemp = NULL;
		long nCount = 0;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strName == strName)
			{
				nCount++;
			}
		}

		return nCount;
	}

	long SearchByID(const CString &strID)
	{
		T* pTemp = NULL;
		long nCount = 0;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strID == strID)
			{
				nCount++;
			}
		}

		return nCount;
	}

	long SearchByName(const CString &strName, CTLinkList<T> &oList)
	{
		T* pTemp = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strName == strName)
			{
				oList.AddTail(pTemp);
			}
		}

		return oList.GetCount();
	}

	long SearchByID(const CString &strID, CTLinkList<T> &oList)
	{
		T* pTemp = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = GetNext(pos);

			if (pTemp != NULL && pTemp->m_strID == strID)
			{
				oList.AddTail(pTemp);
			}
		}

		return oList.GetCount();
	}

    void XAppend(CTLinkList<T> &oListSrc)
    {
        POS pos = oListSrc.GetHeadPosition();
        T *p = NULL;

        while (pos != NULL)
        {
            p = oListSrc.GetNext(pos);
            AddTail(p);
        }
    }
	// Implementation
protected:
	CNode* m_pNodeHead;
	CNode* m_pNodeTail;
	int m_nCount;
	CNode* m_pNodeFree;
	CListPlex* m_pBlocks;
	int m_nBlockSize;
	
	CNode* NewNode(CNode* pPrev, CNode* pNext)
	{
		if (m_pNodeFree == NULL)
		{
			// add another block
			CListPlex* pNewBlock = CListPlex::Create(m_pBlocks, m_nBlockSize,
				sizeof(CNode));

			// chain them into free list
			CNode* pNode = (CNode*) pNewBlock->data();
			// free in reverse order to make it easier to debug
			pNode += m_nBlockSize - 1;
			for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
			{
				pNode->pNext = m_pNodeFree;
				m_pNodeFree = pNode;
			}
		}

		CNode* pNode = m_pNodeFree;
		m_pNodeFree = m_pNodeFree->pNext;
		pNode->pPrev = pPrev;
		pNode->pNext = pNext;
		m_nCount++;
		pNode->data = 0; // start with zero

		return pNode;
	}

	void FreeNode(CNode* pNode)
	{
		pNode->pNext = m_pNodeFree;
		m_pNodeFree = pNode;
		m_nCount--;

		if (m_nCount == 0)
			RemoveAll();
	}
	void FreeNode2(CNode* pNode)
	{
		pNode->pNext = m_pNodeFree;
		m_pNodeFree = pNode;
		m_nCount--;
	}


    void GetAllDataAddr(unsigned long *pdwDataBuffer)
	{
		POS pos = GetHeadPosition();
		T *pData = NULL;

		while (pos != NULL)
		{
			pData = (T*)GetNext(pos);
            *pdwDataBuffer = (unsigned long)pData;
			pdwDataBuffer++;
		}
	}

};

// 
// template <class T>
// inline CTLinkList<T>::CNode* CTLinkList<T>::NewNode(CNode* pPrev, CNode* pNext)
// {
// 	if (m_pNodeFree == NULL)
// 	{
// 		// add another block
// 		CListPlex* pNewBlock = CListPlex::Create(m_pBlocks, m_nBlockSize,
// 				 sizeof(CNode));
// 
// 		// chain them into free list
// 		CNode* pNode = (CNode*) pNewBlock->data();
// 		// free in reverse order to make it easier to debug
// 		pNode += m_nBlockSize - 1;
// 		for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
// 		{
// 			pNode->pNext = m_pNodeFree;
// 			m_pNodeFree = pNode;
// 		}
// 	}
// 
// 	CNode* pNode = m_pNodeFree;
// 	m_pNodeFree = m_pNodeFree->pNext;
// 	pNode->pPrev = pPrev;
// 	pNode->pNext = pNext;
// 	m_nCount++;
// 	pNode->data = 0; // start with zero
// 
// 	return pNode;
// }
// 
// template <class T>
// inline void CTLinkList<T>::FreeNode(CNode* pNode)
// {
// 
// 	pNode->pNext = m_pNodeFree;
// 	m_pNodeFree = pNode;
// 	m_nCount--;
// 
// 	if (m_nCount == 0)
// 		RemoveAll();
// }
// 

/*
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


};
*/

#define CTLinkListEx CTLinkList


#endif // !defined(_LINKLIST_H__)
