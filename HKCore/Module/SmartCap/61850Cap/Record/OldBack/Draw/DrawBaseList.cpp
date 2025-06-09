// DrawBaseList.cpp: implementation of the CDrawBaseList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawBaseList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDrawBaseList::CDrawBaseList()
{
}

CDrawBaseList::~CDrawBaseList()
{
	DeleteAll();
}


void CDrawBaseList::Append(CDrawBaseList &oListSrc)
{
	POS pos = oListSrc.GetHeadPosition();
	CDrawBase *pObj = NULL;

	while (pos != NULL)
	{
		pObj = oListSrc.GetNext(pos);
		AddTail(pObj);
	}
}

CDrawBase* CDrawBaseList::GetNextByObj(CDrawBase* pData)
{
	CDrawBase* pObj = NULL;
	POS pPos		= NULL;
	pPos = Find(pData);

	pObj = GetNext(pPos);
	pObj = GetAt(pPos);

	if (pObj == NULL)
	{
		pObj = GetHead();
	}
	else
	{		
	}
		
	return pObj;
}

CDrawBase* CDrawBaseList::GetPrevByObj(CDrawBase* pData) 
{
	CDrawBase* pObj        = NULL;
	POS pPos		       = NULL;	
	POS pPrePos		   = NULL;
	CDrawBase* pCurrentObj = NULL;
	POS pCurrentPos	   = GetHeadPosition();

	while (pCurrentPos != NULL)
	{
		pPos = pCurrentPos;
		pCurrentObj = GetNext(pCurrentPos);
		pCurrentObj = GetAt(pCurrentPos);
		
		if (pCurrentObj == pData)
		{
			pPrePos = pPos;
			break;
		}
	}

	if (pPrePos == NULL)
	{
		pObj = GetTail();
	}
	else
	{
		pObj = GetAt(pPrePos);
	}
	
	return pObj;
} 