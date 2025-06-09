// XSort.cpp : 实现文件
//

#include "stdafx.h"
#include "XMacthListSort.h"
#include "XMatchList.h"

// CXMacthListSort
CXMacthListSort::CXMacthListSort()
{

}

CXMacthListSort::~CXMacthListSort()
{
}

// CXMacthListSort 消息处理程序
void CXMacthListSort::Sort(CXMatchList *pMatchList)
{
	m_pMatchList = pMatchList;
	InitXMatchObjKeysLength();
	Sort();
	
}

void CXMacthListSort::Sort()
{
	int nCount = m_pMatchList->GetCount();
	CExBaseObject *pMatchA;
	CExBaseObject *pMatchB;
	CExBaseObject *pMatch;

	for (int i=0;i<nCount;i++)
	{
		pMatchA = m_pMatchList->GetAtIndex(i);

		for (int j=i+1;j<nCount;j++)
		{
			pMatchB = m_pMatchList->GetAtIndex(j);

			if (pMatchA->m_dwReserved > pMatchB->m_dwReserved)
			{
				m_pMatchList->ChangePosition(i, j);
				pMatch = pMatchA;
				pMatchA = pMatchB;
				pMatchB = pMatch;
			}
		}
	}
}

void CXMacthListSort::InitXMatchObjKeysLength()
{
	CXMatchObject *pMatchObj = NULL;
	POS pos = m_pMatchList->GetHeadPosition();
	CExBaseObject *pRefObj = NULL; //被匹配的数据
	int nKeysLength = 0;
	int nNameLength = 0;

	while(pos != NULL)
	{
		pMatchObj =(CXMatchObject *) m_pMatchList->GetNext(pos);
		ASSERT(pMatchObj->m_pRefObject != NULL);
		nKeysLength = GetKeysSumLength(&pMatchObj->m_listMatchXKeys);
		nNameLength = pMatchObj->m_pRefObject->m_strName.GetLength();

		if (nNameLength != 0)
		{
			pMatchObj->m_dwReserved = nKeysLength  * 10000 / nNameLength;
		}
		else
		{
			pMatchObj->m_dwReserved = 0;
		}
	}
}

int CXMacthListSort::GetKeysSumLength(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pObj;
	int nLength =0 ;

	while(pos != NULL)
	{
		pObj = pList->GetNext(pos);
		nLength += pObj->m_strName.GetLength();
	}

	return nLength;
}
