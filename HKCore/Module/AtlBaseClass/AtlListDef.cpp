// CAtlBaseObject.cpp: implementation of the CAtlBaseObject class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "AtlListDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAtlPlex* PASCAL CAtlPlex::Create(CAtlPlex*& pHead, UINT nMax, UINT cbElement)
{
//	ASSERT(nMax > 0 && cbElement > 0);
	CAtlPlex* p = (CAtlPlex*) new BYTE[sizeof(CAtlPlex) + nMax * cbElement];
	// may throw exception
	p->pNext = pHead;
	pHead = p;  // change head (adds in reverse order for simplicity)
	return p;
}

void CAtlPlex::FreeDataChain()     // free this one and links
{
	CAtlPlex* p = this;
	while (p != NULL)
	{
		BYTE* bytes = (BYTE*) p;
		CAtlPlex* pNext = p->pNext;
		delete[] bytes;
		p = pNext;
	}
}
