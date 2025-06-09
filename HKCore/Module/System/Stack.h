// Stack.h: interface for the CStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACK_H__841C4364_B786_4C28_858D_EA73F9B1BDA4__INCLUDED_)
#define AFX_STACK_H__841C4364_B786_4C28_858D_EA73F9B1BDA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BaseClass/TLinkList.h"

template <class T> 
class CStack : public  CTLinkList<T>
{
public:
        CStack() : CTLinkList(10)
	{

	}
	virtual ~CStack()
	{
	}

	void Push(T *pObj)
	{
		ASSERT (pObj != NULL);

		AddHead(pObj);
	}

	T* Pop()
	{
		T *pObj = NULL;
		POS pos = GetHeadPosition();

		if (pos)
		{
			pObj = (T*)GetAt(pos);
			RemoveAt(pos);
		}

		return pObj;
	}

	T* Top()
	{
		T *pObj = NULL;
                POS pos = GetHeadPosition();
		if (pos)
		{
			pObj = (T*)GetAt(pos);
		}
		return pObj;	
	}

	BOOL HasMoreElements()
	{
		return (GetCount() > 0);
	}

	T* NextTop()
	{
		int iIndex = 1;
		T *pObj = NULL;
                POS pos = FindIndex(iIndex);
		if (pos)
		{
			pObj = (T*)GetAt(pos);
		}
		return pObj;	
	}

	void Pop2Push(T *pObj)
	{
		int nCount = GetCount();
		T *pTemp = NULL;
		if (nCount >= 2) 
		{
			pTemp = Pop();
			delete pTemp;
			pTemp = Pop();
			delete pTemp;
			Push(pObj);
		}
		else
		{
			Push(pObj);	
		}
	}

	void Empty()
	{
		DeleteAll();
	}

	T* Peek()
	{
		return GetHead();
	}
};

#endif // !defined(AFX_STACK_H__841C4364_B786_4C28_858D_EA73F9B1BDA4__INCLUDED_)
