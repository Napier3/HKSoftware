// FrameBaseList.cpp: implementation of the CFrameBaseList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FrameBaseList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrameBaseList::CFrameBaseList()
{

}

CFrameBaseList::~CFrameBaseList()
{

}

CFrameBase* CFrameBaseList::FindByClassID(UINT nClassID)
{
	CFrameBase *p = NULL;
	CFrameBase *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CFrameBase*)GetNext(pos);

		if (p->GetClassID() == nClassID)
		{
			pFind = p;
			break;
		}
	}

	return p;
}

CFrameBase* CFrameBaseList::FindByOwnClassID(UINT nClassID)
{
	CFrameBase *p = NULL;
	CFrameBase *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CFrameBase*)GetNext(pos);

		if ( ( p->GetClassID() && STPROTCOLCLASSID_OWN_MASK )== nClassID)
		{
			pFind = p;
			break;
		}
	}

	return p;
}


CFrameBase* CFrameBaseList::Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)
{
	ASSERT (FALSE);
	return NULL;
}

CFrameBase* CFrameBaseList::Parse(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return NULL;
}

CFrameBase* CFrameBaseList::Match(PEPBUFFERPOS pBufferPos)
{
	CFrameBase *p = NULL;
	CFrameBase *pMatch = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		EPBUFFERPOS oStBufPos;
		Ep_BackBufferPos(*pBufferPos, oStBufPos);
		p = (CFrameBase*)GetNext(pos);

		if (p->Match(pBufferPos))
		{
			pMatch = p;
			break;
		}

		Ep_BackBufferPos(oStBufPos, *pBufferPos);
	}

	return pMatch;
}

DWORD CFrameBaseList::Produce(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return 0;
}

