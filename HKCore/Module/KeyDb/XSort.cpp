// XSort.cpp : ʵ���ļ�
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

// CXSort ��Ϣ�������
void CXSort::Sort(CXMatchList *pMatchList)
{
	CXMatchObject *pMatchObj;
	POS pos = pMatchList->GetHeadPosition();
	CExBaseObject *pRefObj; //��ƥ�������
	CExBaseList *pMatchKeys;  //�ؼ���Keys
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
