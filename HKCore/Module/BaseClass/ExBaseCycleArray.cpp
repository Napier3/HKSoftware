#include "StdAfx.h"
#include "ExBaseCycleArray.h"
#include "../MemBuffer/XMemBufferBse.h"

CExBaseCycleArray::CExBaseCycleArray(void)
{
// 	m_bAddNewExBaseObject = TRUE;
	m_pdwExBaseObject = NULL;
	m_nMaxCount = 0;
	m_nCurrIndex = 0;
	m_nCurrCount = 0;

	m_nCurrReadIndex = 0;  
	m_nCurrFreeIndex = 0;  
}

CExBaseCycleArray::~CExBaseCycleArray(void)
{
	Free();
}

void CExBaseCycleArray::Free()
{
	if (m_pdwExBaseObject != NULL)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex<m_nMaxCount; nIndex++)
		{
			CExBaseObject *pBuffer = (CExBaseObject*)m_pdwExBaseObject[nIndex];

			if (pBuffer != NULL)
			{
				delete pBuffer;
			}
		}

		delete m_pdwExBaseObject;
		m_pdwExBaseObject = NULL;
	}
}

void CExBaseCycleArray::FreeBuffer(long nIndexFrom, BOOL bDelete)
{
	if (m_nCurrCount == m_nMaxCount)
	{
		if (nIndexFrom < m_nCurrIndex)
		{
			FreeBuffer(nIndexFrom, m_nCurrIndex-1, bDelete);
		}
		else
		{
			FreeBuffer(nIndexFrom, m_nCurrCount-1, bDelete);
			FreeBuffer(0, m_nCurrIndex-1, bDelete);
		}
	}
	else
	{
		FreeBuffer(nIndexFrom, m_nCurrIndex-1, bDelete);
	}
}

void CExBaseCycleArray::FreeBuffer(BOOL bDelete)
{
	long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
	GetFreeIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);

	if (nEnd1 > nBegin1)
	{
		if (!FreeBuffer(nBegin1, nEnd1, bDelete))
		{
			return;
		}
	}

	if (nBegin2 >= 0)
	{
		FreeBuffer(nBegin2, nEnd2, bDelete);
	}
}

BOOL CExBaseCycleArray::FreeBuffer(long nBeginIndex, long nEndIndex, BOOL bDelete)
{
	long nIndex = 0;

	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
	{
		CExBaseObject *pObj = (CExBaseObject*)GetExBaseObject(nIndex);

		if (bDelete)
		{
			delete pObj;
		}
		
		m_pdwExBaseObject[nIndex] = 0;
		m_nCurrFreeIndex = nIndex+1; //下一次free的位置
	}

	return TRUE;
}

void CExBaseCycleArray::SetMaxCount(long nMaxCount)
{
	if (m_nMaxCount == nMaxCount)
	{
		return;
	}

	if (nMaxCount < 0)
	{
		nMaxCount = ExBaseCycleArray_Count;
	}

	m_nMaxCount = nMaxCount;
	long nLen = m_nMaxCount + 10;
	m_pdwExBaseObject = new PSX_OBJ_ADDR[nLen];
	ZeroMemory(m_pdwExBaseObject, m_nMaxCount * sizeof(PSX_OBJ_ADDR));
}

long CExBaseCycleArray::GetCount(long nIndexFrom)
{
	if (m_nCurrCount == m_nMaxCount)
	{
		if (m_nCurrIndex >= nIndexFrom)
		{
			return m_nCurrIndex - nIndexFrom;
		}
		else
		{
			return m_nCurrCount - nIndexFrom + m_nCurrIndex;
		}
	}
	else
	{
		return m_nCurrIndex - nIndexFrom;
	}
}

long CExBaseCycleArray::GetCount()
{
	return GetCount(m_nCurrReadIndex);
}

void CExBaseCycleArray::InitExBaseCycleArray ()
{
	SetMaxCount(ExBaseCycleArray_Count);
}

CExBaseObject* CExBaseCycleArray::AddExBaseObject(CExBaseObject *pObj, BOOL bDeleteCurr)
{
	CExBaseObject *pExBaseObject = GetExBaseObject(m_nCurrIndex);
	
	if (bDeleteCurr)
	{
		if (pExBaseObject != NULL)
		{
			delete pExBaseObject;
		}
	}
	
// 	pExBaseObject = NewExBaseObject(pObj);
	m_pdwExBaseObject[m_nCurrIndex] = (PSX_OBJ_ADDR)pObj;
	m_nCurrIndex++;

	if (m_nCurrIndex >= m_nMaxCount)
	{
		m_nCurrIndex = 0;
	}

	m_nCurrCount++;
	if (m_nCurrCount >= m_nMaxCount)
	{
		m_nCurrCount = m_nMaxCount;
	}

	return pExBaseObject;
}

void CExBaseCycleArray::AddExBaseObjects(CExBaseList *pList, BOOL bDeleteCurr)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		AddExBaseObject(p, bDeleteCurr);
	}
}

void CExBaseCycleArray::GetReadIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
	long nCurrCount = m_nCurrCount;
	long nCurrIndex = m_nCurrIndex;

	xmem_get_cycle_range_index(m_nMaxCount, nCurrCount, nCurrIndex
		,m_nCurrReadIndex
		, nBegin1, nEnd1, nBegin2, nEnd2);
}

void CExBaseCycleArray::GetFreeIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
	long nCurrCount = m_nCurrCount;
	long nCurrIndex = m_nCurrIndex;

	xmem_get_cycle_range_index(m_nMaxCount, nCurrCount, nCurrIndex
		, m_nCurrFreeIndex
		, nBegin1, nEnd1, nBegin2, nEnd2);
}

void CExBaseCycleArray::DeleteAll()
{
	CExBaseObject *pExBaseObject = NULL;
	long nIndex = 0;
	m_nCurrIndex = 0;

	for (nIndex=0; nIndex<m_nMaxCount; nIndex++)
	{
		pExBaseObject = (CExBaseObject*)m_pdwExBaseObject[nIndex];
		delete pExBaseObject;
		m_pdwExBaseObject[nIndex] = 0;
	}

	m_nCurrIndex = 0;
	m_nCurrCount = 0;
}

//2022-10-19  lijunqing
CExBaseObject* CExBaseCycleArray::ReadCurr(int nOffsetIndex, BOOL bSetNull )
{
	CExBaseObject *p = GetExBaseObject(m_nCurrReadIndex);
	
	if (p == NULL)
	{//如果没有对象，则返回，不递增当前读的位置
		return p;
	}

	if (bSetNull)
	{
		m_pdwExBaseObject[m_nCurrReadIndex] = 0;
	}

	if (nOffsetIndex != 0)
	{
		SetCurrReadIndex(m_nCurrReadIndex+1);
	}

	return p;
}


long CExBaseCycleArray::ReadAll(CExBaseList *pList, long nFrom, BOOL bSetNull)
{
	long nCurrIndex = m_nCurrIndex;

	if (nFrom < 0)
	{//表示使用自身的m_nCurrReadIndex
		nFrom = m_nCurrReadIndex;
		m_nCurrReadIndex = nCurrIndex;
	}

	if (m_nCurrCount == m_nMaxCount)
	{
		if (nFrom < nCurrIndex)
		{
			ReadAll(pList, nFrom, nCurrIndex-1, bSetNull);
		}
		else
		{
			ReadAll(pList, nFrom, m_nCurrCount-1, bSetNull);
			ReadAll(pList, 0, nCurrIndex-1, bSetNull);
		}
	}
	else
	{
		ReadAll(pList, nFrom, nCurrIndex-1, bSetNull);
	}

	return nCurrIndex;
}

void CExBaseCycleArray::ReadAll(CExBaseList *pList, long nBeginIndex, long nEndIndex, BOOL bSetNull)
{
	long nIndex = 0;
	CExBaseObject *pObj = NULL;

	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
	{
		pObj = (CExBaseObject*)m_pdwExBaseObject[nIndex];

		if (pObj == NULL)
		{
			continue;
		}

		pList->AddTail(pObj);

		if (bSetNull)
		{
			m_pdwExBaseObject[nIndex] = 0;
		}
	}
}

void CExBaseCycleArray::FreeCurr(BOOL bDelete)
{
	CExBaseObject *pObj = (CExBaseObject*)GetExBaseObject(m_nCurrFreeIndex);

	if (bDelete)
	{
		delete pObj;
	}

	m_pdwExBaseObject[m_nCurrFreeIndex] = 0;
	SetCurrFreeIndex(m_nCurrFreeIndex+1);
}

