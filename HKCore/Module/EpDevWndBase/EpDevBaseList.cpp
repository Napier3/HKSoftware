#include "stdafx.h"
#include "EpDevBaseList.h"
#include "EpDevWndFactory.h"

CEpDevBaseList::CEpDevBaseList()
{

}

CEpDevBaseList::~CEpDevBaseList()
{

}

long CEpDevBaseList::InsertBefore(long nIndex, CEpDevBase *pObj)
{
	ASSERT(pObj != NULL);
	POS pos = FindIndex(nIndex);

	if (pos == NULL)
	{
		return -1;
	}

	CTLinkList<CEpDevBase>::InsertBefore(pos, pObj);

	return 0;
}

long CEpDevBaseList::InsertAfter(long nIndex, CEpDevBase *pObj)
{
	ASSERT(pObj != NULL);
	POS pos = FindIndex(nIndex);
	
	if (pos == NULL)
	{
		return -1;
	}

	CTLinkList<CEpDevBase>::InsertAfter(pos, pObj);

	return 0;
}

CEpDevBase	*CEpDevBaseList::CreateNewChildObject(long nClassID)
{
	return NULL;
}

long CEpDevBaseList::AdjustChildrenPos(long nLeft,long nTop)
{
	CEpDevBase *pObj = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		pObj->AdjustPos(nLeft, nTop);
	}

	return 0;
}

long CEpDevBaseList::CalChildrenSize(CSize &sz)
{
	POS pos = GetHeadPosition();
	CEpDevBase *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		CSize szChildren(0,0);
	
		if(pObj->IsShow())
		{
			pObj->CalSize(szChildren);
		}

		sz.cx = max(sz.cx, szChildren.cx);
		sz.cy += szChildren.cy /*+EPDWND_GAP_VERT*/;
	}

	return 0;
}

BOOL CEpDevBaseList::UICreateChildren(CWnd *pParent)
{
 	ASSERT (m_pData != NULL);
 
 	if (m_pData == NULL)
 	{
 		return FALSE;
 	}
 
 	//ASSERT (m_pData->IsBaseList());
 
 	if (!m_pData->IsBaseList())
 	{
 		return FALSE;
 	}
 
 	CExBaseList *pList = (CExBaseList*)m_pData;
 	POS pos = pList->GetHeadPosition();
 	CExBaseObject *pChildData = NULL;
 	CEpDevBase *pDevWnd = NULL;
 
 	while (pos != NULL)
 	{
 		pChildData = pList->GetNext(pos);
 		pDevWnd = CEpDevWndFactory::CreateDevWnd(pChildData, pParent);
 
 		ASSERT (pDevWnd != NULL);
 
 		if (pDevWnd != NULL)
 		{
 			AddTail(pDevWnd);
 			pDevWnd->m_pData = pChildData;
 			pDevWnd->UICreate(pParent);
 		}
 	}	

	return TRUE;
}

BOOL CEpDevBaseList::DestroyChildren()
{
	POS pos = GetHeadPosition();
	CEpDevBase *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		pObj->Destroy();
	}

	return TRUE;
}

void CEpDevBaseList::ShowChildren(UINT nShow)
{
	POS pos = GetHeadPosition();
	CEpDevBase *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		pObj->Show(nShow);
	}
}

long CEpDevBaseList::MoveDown(CEpDevBase* pObj)
{	
	POS posNext = Find(pObj);
	POS pos = Find(pObj);
	GetNext(posNext);

	ChangePosition(pos,posNext);

	//改变数据位置
	CEpDevBase* pCur = GetAt(pos);
	CEpDevBase* pNext = GetAt(posNext);
	CExBaseObject* pCurData = pCur->m_pData;
	CExBaseObject* pNextData = pNext->m_pData;

	CExBaseList* pParentData = (CExBaseList*)pCurData->GetParent();
	ASSERT( pParentData != NULL);
	pos = pParentData->Find(pCurData);
	posNext = pParentData->Find(pNextData);

	pParentData->ChangePosition(pos,posNext);

	return 0;	
}