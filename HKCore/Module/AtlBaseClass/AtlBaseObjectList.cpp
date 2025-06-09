// CAtlBaseObject.cpp: implementation of the CAtlBaseObject class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "AtlBaseObjectList.h"


CAtlBaseObjectList::CAtlBaseObjectList(int nBlockSize)
{
	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}

void CAtlBaseObjectList::RemoveAll()
{
	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

void CAtlBaseObjectList::DeleteAll()
{
	CNode* pNode = m_pNodeHead;
	CNode* pNodeTemp = m_pNodeHead;
	CAtlBaseObject* pObject = NULL;

	while (pNode != NULL)
	{
		pNodeTemp = pNode->pNext;
		pObject = (CAtlBaseObject*)pNode->data;
		delete pObject;
		FreeNode(pNode);
		pNode = pNodeTemp;
	}
	
	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}


CAtlBaseObjectList::~CAtlBaseObjectList()
{
	DeleteAll();
}

CAtlBaseObjectList::CNode* CAtlBaseObjectList::NewNode(CAtlBaseObjectList::CNode* pPrev, CAtlBaseObjectList::CNode* pNext)
{
	if (m_pNodeFree == NULL)
	{
		// add another block
		CAtlPlex* pNewBlock = CAtlPlex::Create(m_pBlocks, m_nBlockSize,
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

	CAtlBaseObjectList::CNode* pNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNode->pPrev = pPrev;
	pNode->pNext = pNext;
	m_nCount++;
	pNode->data = 0; // start with zero

	return pNode;
}

void CAtlBaseObjectList::FreeNode(CAtlBaseObjectList::CNode* pNode)
{

	pNode->pNext = m_pNodeFree;
	m_pNodeFree = pNode;
	m_nCount--;

	if (m_nCount == 0)
		RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////

POS CAtlBaseObjectList::AddHead(CAtlBaseObject* newElement)
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



POS CAtlBaseObjectList::AddTail(CAtlBaseObject* newElement)
{
	CNode* pNewNode = NewNode(m_pNodeTail, NULL);
	pNewNode->data = newElement;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;
	return (POS) pNewNode;

}



void CAtlBaseObjectList::AddHead(CAtlBaseObjectList* pNewList)
{
	POS pos = pNewList->GetTailPosition();
	while (pos != NULL)
		AddHead(pNewList->GetPrev(pos));
}

void CAtlBaseObjectList::AddTail(CAtlBaseObjectList* pNewList)
{
	POS pos = pNewList->GetHeadPosition();
	while (pos != NULL)
		AddTail(pNewList->GetNext(pos));
}

CAtlBaseObject* CAtlBaseObjectList::RemoveHead()
{
	CNode* pOldNode = m_pNodeHead;
	CAtlBaseObject* returnValue = (CAtlBaseObject*)(pOldNode->data);

	m_pNodeHead = pOldNode->pNext;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;
	FreeNode(pOldNode);

	return returnValue;
}

CAtlBaseObject* CAtlBaseObjectList::RemoveTail()
{
	CNode* pOldNode = m_pNodeTail;
	CAtlBaseObject* returnValue = (CAtlBaseObject*)(pOldNode->data);

	m_pNodeTail = pOldNode->pPrev;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;
	FreeNode(pOldNode);

	return returnValue;
}

POS CAtlBaseObjectList::InsertBefore(POS position, CAtlBaseObject* newElement)
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



POS CAtlBaseObjectList::InsertAfter(POS position, CAtlBaseObject* newElement)
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



void CAtlBaseObjectList::RemoveAt(POS position)
{
	CNode* pOldNode = (CNode*) position;
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


/////////////////////////////////////////////////////////////////////////////
// slow operations

POS CAtlBaseObjectList::FindIndex(int nIndex) const
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

POS CAtlBaseObjectList::Find(CAtlBaseObject* searchValue, POS startAfter) const
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
