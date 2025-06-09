// XSort.cpp : 实现文件
//

#include "stdafx.h"
#include "XSort.h"
#include "XMatchList.h"

// CXSort
CXSort::CXSort()
{

}

CXSort::~CXSort()
{
}

// CXSort 消息处理程序
void CXSort::Sort(CXMatchList *pMatchList)
{
	CXMatchObject *pMatchObj;
	POS pos = pMatchList->GetHeadPosition();
	CExBaseObject *pRefObj; //被匹配的数据
	CExBaseList *pMatchKeys;  //关键字Keys
	int NumRefObj;
	int NumKeys;

	while(pos != NULL)
	{
		pMatchObj =(CXMatchObject *) pMatchList->GetNext(pos);
		pRefObj = pMatchObj->m_pRefObject;
		pMatchKeys =& pMatchObj->m_listMatchXKeys;
		NumRefObj = pRefObj->m_strName.GetLength();
		NumKeys = NumOfKeys(pMatchKeys);

		if (NumKeys != 0)
		{
			pMatchObj->m_dwReserved = NumKeys  * 1000000/ NumRefObj;
		}
		else
		{
			pMatchObj->m_dwReserved = 0;
		}
	}

	int nIndex ;
	nIndex = pMatchList->GetCount();
	CExBaseObject *pMatchA;
	CExBaseObject *pMatchB;

	for (int i=0;i<nIndex;i++)
	{
		pMatchA = pMatchList->GetAtIndex(i);

		for (int j=i+1;j<nIndex;j++)
		{
			pMatchB = pMatchList->GetAtIndex(j);

			if (pMatchA->m_dwReserved > pMatchB->m_dwReserved)
			{
				pMatchList->ChangePosition(pMatchA,pMatchB);
			}
		}
	}
}

int CXSort::NumOfKeys(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pObj;
	int nIndex =0 ;

	while(pos != NULL)
	{
		pObj = pList->GetNext(pos);
		nIndex += pObj->m_strName.GetLength();
	}

	return nIndex;
}
