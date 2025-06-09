//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XMatchList.cpp  CXMatchList


#include "stdafx.h"
#include "XMatchList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchList::CXMatchList()
{
	//��ʼ������

	//��ʼ����Ա����
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
	//�����ж��ƥ���\����ƥ�����Ŀ
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
	//�����ж��ƥ���\����ƥ�����Ŀ
	CExBaseList oListSingleMatch, oListMultiMatch;
	POS pos = GetHeadPosition();
	CXMatchObject *pXMatchObj = NULL;
	CXMatchObject *pXMatchMultiObj = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pXMatchObj = (CXMatchObject *)GetNext(pos);
		//nCount = pXMatchObj->m_listMacthRefObject.GetCount();

		//��ƥ��ɹ����ƶȽ������򣬲�������ƥ��ɹ��ȵĶ�����ӵ�
		//m_listMacthRefObject�б���
		pXMatchObj->FilterSortByRatio();
		pXMatchObj->FilterMatchRatio(nMatchRatio);
		//for debug  ��176���Ƶ��˴�   shaolei 20220517
		nCount = pXMatchObj->m_listMacthRefObject.GetCount();

		//ƥ�����ֻ��һ��ƥ��ɹ�
		if (nCount == 1)
		{
			oListSingleMatch.AddTail(pXMatchObj);
		}
		else if (nCount > 1)
		{//ƥ������ж��ƥ��ɹ�
			oListMultiMatch.AddTail(pXMatchObj);
		}
	}

	//�������ƥ�����Ŀ���Ӷ��ƥ�����Ŀ��ȥ������ƥ�����Ŀ
	POS posMulti = oListMultiMatch.GetHeadPosition();

	while (posMulti != NULL)
	{
		pXMatchMultiObj = (CXMatchObject *)oListMultiMatch.GetNext(posMulti);
		pos = oListSingleMatch.GetHeadPosition();

		while (pos != NULL)
		{
			pXMatchObj = (CXMatchObject *)oListSingleMatch.GetNext(pos);

			//for debug
// 			if (pXMatchMultiObj->m_pRefObject->m_strName == _T("�ӵر�����������") && pXMatchObj->m_pRefObject->m_strName == _T("����������"))
// 			{
// 				int x = 0;
// 			}

			pXMatchMultiObj->FilterMatch(pXMatchObj);//ȥ����һƥ��ɹ��Ķ���
		}
	}

	oListMultiMatch.RemoveAll();
	oListSingleMatch.RemoveAll();
}

CXMatchObject* CXMatchList::CreateMatchObject(CExBaseObject *pRefObj, CXKeyDB *pKeyDb)
{
	return new CXMatchObject(pRefObj, pKeyDb);
}

