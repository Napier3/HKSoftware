#pragma once

#include "ExBaseList.h"

#define ExBaseCycleArray_Count   2000

class CExBaseCycleArray
{
public:
	CExBaseCycleArray(void);
	virtual ~CExBaseCycleArray(void);

	void FreeBuffer(long nIndexFrom, BOOL bDelete=TRUE);
	void FreeBuffer(BOOL bDelete=TRUE);

// 	void SetAddNewExBaseObject(BOOL b = TRUE)	{	m_bAddNewExBaseObject = b;	}
protected:
	BOOL FreeBuffer(long nBeginIndex, long nEndIndex, BOOL bDelete);

protected:
	PSX_OBJ_ADDR *m_pdwExBaseObject;

	long m_nMaxCount;
	long m_nCurrIndex;
	long m_nCurrCount;

	long m_nCurrReadIndex;  //��ǰ��ȡ���ݵ�λ��
	long m_nCurrFreeIndex;  //��ǰ�ͷŻ����λ��

// 	BOOL m_bAddNewExBaseObject;   //2023-3-8  lijunqing ����ģʽʹ�ò����㣬ȥ��
	void Free();

public:
	void SetMaxCount(long nMaxCount);
	long GetMaxCount()	{	return m_nMaxCount;		}
	long GetCurrCount()	{	return m_nCurrCount;	}
	long GetCurrIndex()	{	return m_nCurrIndex;	}
	long GetCount(long nIndexFrom);
	long GetCount();

	long GetCurrReadIndex()	{	return m_nCurrReadIndex;		}
	long GetCurrFreeIndex()	{	return m_nCurrFreeIndex;		}

	void SetCurrReadIndex(long nIndex)	
	{
		m_nCurrReadIndex = nIndex;	
	
		if (m_nCurrReadIndex >= m_nMaxCount) 
		{
			m_nCurrReadIndex = 0;
		}	
	}

	void SetCurrFreeIndex(long nIndex)
	{
		m_nCurrFreeIndex = nIndex;

		if (m_nCurrFreeIndex >= m_nMaxCount) 
		{
			m_nCurrFreeIndex = 0;
		}	
	}

	void GetReadIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2);
	void GetFreeIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2);
	void DeleteAll();

	inline CExBaseObject* GetExBaseObject(long nIndex)
	{
		ASSERT (0 <= nIndex && nIndex < m_nMaxCount);
		return (CExBaseObject*)m_pdwExBaseObject[nIndex];
	}
	
// 	inline CExBaseObject* NewExBaseObject(CExBaseObject *pObj)
// 	{
// 		if (m_bAddNewExBaseObject)
// 		{
// 			return (CExBaseObject*)pObj->Clone();
// 		}
// 		else
// 		{
// 			return pObj;
// 		}
// 	}

public:
	virtual void InitExBaseCycleArray ();
	virtual CExBaseObject* AddExBaseObject(CExBaseObject *pObj, BOOL bDeleteCurr=FALSE);
	virtual void AddExBaseObjects(CExBaseList *pList, BOOL bDeleteCurr=FALSE);

	//2022-10-19  lijunqing
	CExBaseObject* ReadCurr(int nOffsetIndex=1, BOOL bSetNull = FALSE);
	CExBaseObject* GetCurr()	{	return GetExBaseObject(m_nCurrReadIndex);	}

	//nFrom < 0����ʾʹ������Read�����ص�ǰ��λ��
	//bSetNull=NULL����ʾ���޸Ļ���λ�õ����ݣ�����ֻ������
	long ReadAll(CExBaseList *pList, long nFrom, BOOL bSetNull); 

	void FreeCurr(BOOL bDelete);

private:
	void ReadAll(CExBaseList *pList, long nBeginIndex, long nEndIndex, BOOL bSetNull);
};
