//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchList.cpp  CXMatchList


#include "stdafx.h"
#include "XMatchList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchList::CXMatchList()
{
	//初始化属性

	//初始化成员变量
	m_pListRefObject = NULL;
}

CXMatchList::~CXMatchList()
{
}

BOOL CXMatchList::IsXMatchValid()
{
	BOOL bTrue = TRUE;
	POS pos = GetHeadPosition();
	CXMatchObject *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject *)GetNext(pos);

		if (p->GetMatchRefCount() != 1)
		{
			bTrue = FALSE;
		}
	}

	return bTrue;
}

BOOL CXMatchList::IsXMatchValid_LEqual_1()
{
	BOOL bTrue = TRUE;
	POS pos = GetHeadPosition();
	CXMatchObject *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject *)GetNext(pos);

		if (p->GetMatchRefCount() > 1)
		{
			bTrue = FALSE;
		}
	}

	return bTrue;
}

void CXMatchList::FreeMatch()
{
	POS pos = GetHeadPosition();
	CXMatchObject *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject *)GetNext(pos);
		p->FreeMatch();
	}
}

void CXMatchList::Match(CXMatchList *pMachList, long nMatchRatio, CThreadProgressInterface *pThradProgress, BOOL bUseFullMatchString)
{
	AddMatch(pMachList, nMatchRatio, pThradProgress, TRUE, bUseFullMatchString);

	FilterMatch(nMatchRatio);
	FilterMatch(pMachList);
}

void CXMatchList::AddMatch(CXMatchList *pMachList, long nMatchRatio, CThreadProgressInterface *pThradProgress, BOOL bFreeMatchList, BOOL bUseFullMatchString)
{
	POS pos = GetHeadPosition();
	CXMatchObject *p = NULL;

	if (pThradProgress == NULL)
	{
		while (pos != NULL)
		{
			p = (CXMatchObject *)GetNext(pos);
			p->Match(pMachList, bFreeMatchList, bUseFullMatchString);
		}
	}
	else
	{
		while (pos != NULL)
		{
			p = (CXMatchObject *)GetNext(pos);
			p->Match(pMachList, bFreeMatchList, bUseFullMatchString);
			pThradProgress->StepIt();
		}
	}
}

void CXMatchList::FilterMatch(CXMatchList *pMachList, long nMatchRatio)
{
	FilterMatch(nMatchRatio);
	FilterMatch(pMachList);
}

void CXMatchList::Init(CExBaseList *pListRefObj, CXKeyDB *pKeyDb, CThreadProgressInterface *pThradProgress)
{
	m_pListRefObject = pListRefObj;
	CExBaseObject *p = NULL;
	POS pos = pListRefObj->GetHeadPosition();
	CXMatchObject *pNew = NULL;

	if (pThradProgress == NULL)
	{
		while (pos != NULL)
		{
			p = pListRefObj->GetNext(pos);
			pNew = CreateMatchObject(p, pKeyDb);
			AddTail(pNew);
		}
	}
	else
	{
		while (pos != NULL)
		{
			p = pListRefObj->GetNext(pos);
			pNew = CreateMatchObject(p, pKeyDb);
			AddTail(pNew);
			pThradProgress->StepIt();
		}
	}
}

void CXMatchList::FilterMatch(CXMatchList *pList)
{
	//检索有多个匹配的\单个匹配的项目
	POS pos = pList->GetHeadPosition();
	POS pos2 = NULL;
	CXMatchObject *pXMatchObj = NULL;
	CXMatchObject *pXMatchObj2 = NULL;

	while (pos != NULL)
	{
		pXMatchObj = (CXMatchObject *)pList->GetNext(pos);
		pos2 = GetHeadPosition();

		while (pos2 != NULL)
		{
			pXMatchObj2 = (CXMatchObject *)GetNext(pos2);
			pXMatchObj2->FilterMatch(pXMatchObj);
		}
	}
}

void CXMatchList::FilterMatch(long nMatchRatio)
{
	//检索有多个匹配的\单个匹配的项目
	CExBaseList oListSingleMatch, oListMultiMatch;
	POS pos = GetHeadPosition();
	CXMatchObject *pXMatchObj = NULL;
	CXMatchObject *pXMatchMultiObj = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pXMatchObj = (CXMatchObject *)GetNext(pos);
		//nCount = pXMatchObj->m_listMacthRefObject.GetCount();

		//对匹配成功相似度进行排序，并将满足匹配成功度的对象添加到
		//m_listMacthRefObject列表中
		pXMatchObj->FilterSortByRatio();
		pXMatchObj->FilterMatchRatio(nMatchRatio);
		//for debug  从176行移到此处   shaolei 20220517
		nCount = pXMatchObj->m_listMacthRefObject.GetCount();

		//匹配对象只有一个匹配成功
		if (nCount == 1)
		{
			oListSingleMatch.AddTail(pXMatchObj);
		}
		else if (nCount > 1)
		{//匹配对象有多个匹配成功
			oListMultiMatch.AddTail(pXMatchObj);
		}
	}

	//遍历多个匹配的项目，从多个匹配的项目中去掉单个匹配的项目
	POS posMulti = oListMultiMatch.GetHeadPosition();

	while (posMulti != NULL)
	{
		pXMatchMultiObj = (CXMatchObject *)oListMultiMatch.GetNext(posMulti);
		pos = oListSingleMatch.GetHeadPosition();

		while (pos != NULL)
		{
			pXMatchObj = (CXMatchObject *)oListSingleMatch.GetNext(pos);

			//for debug
// 			if (pXMatchMultiObj->m_pRefObject->m_strName == _T("接地变零序过流Ⅱ段") && pXMatchObj->m_pRefObject->m_strName == _T("零序过流Ⅱ段"))
// 			{
// 				int x = 0;
// 			}

			pXMatchMultiObj->FilterMatch(pXMatchObj);//去掉单一匹配成功的对象
		}
	}

	oListMultiMatch.RemoveAll();
	oListSingleMatch.RemoveAll();
}

CXMatchObject* CXMatchList::CreateMatchObject(CExBaseObject *pRefObj, CXKeyDB *pKeyDb)
{
	return new CXMatchObject(pRefObj, pKeyDb);
}

