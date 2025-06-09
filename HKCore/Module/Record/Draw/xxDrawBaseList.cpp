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

}

CDrawBase* CDrawBaseList::GetNextByObj(CDrawBase* pData)
{
	CDrawBase* pObj = NULL;
	POS pPos		= NULL;
	pPos = Find(pData);

	pObj = (CDrawBase*)GetNext(pPos);
	pObj = (CDrawBase*)GetAt(pPos);

	if (pObj == NULL)
	{
		pObj = (CDrawBase*)GetHead();
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
		pCurrentObj = (CDrawBase*)GetNext(pCurrentPos);
		pCurrentObj = (CDrawBase*)GetAt(pCurrentPos);
		
		if (pCurrentObj == pData)
		{
			pPrePos = pPos;
			break;
		}
	}

	if (pPrePos == NULL)
	{
		pObj = (CDrawBase*)GetTail();
	}
	else
	{
		pObj = (CDrawBase*)GetAt(pPrePos);
	}
	
	return pObj;
} 