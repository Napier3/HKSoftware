// ExBaseListUpdateToolBase.cpp : 实现文件
//

#include "stdafx.h"
#include "ExBaseListUpdateToolBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// CExBaseListUpdateToolBase

CExBaseListUpdateToolBase::CExBaseListUpdateToolBase()
{
	
}

CExBaseListUpdateToolBase::~CExBaseListUpdateToolBase()
{

}

BOOL CExBaseListUpdateToolBase::Update_Own(CExBaseObject *pSrc, CExBaseObject *pDest)
{
	pSrc->UpdateOwn(pDest);

	return TRUE;
}

BOOL CExBaseListUpdateToolBase::Update_ByName(CExBaseObject *pSrc, CExBaseObject *pDest)
{
	if (Update_Own(pSrc, pDest))
	{
		return TRUE;
	}

	if (pSrc->IsBaseList() && pDest->IsBaseList())
	{
		Update_ByName((CExBaseList*)pSrc, (CExBaseList*)pDest);
	}

	return TRUE;
}

BOOL CExBaseListUpdateToolBase::Update_ByName(CExBaseList *pSrc, CExBaseList *pDest)
{
	POS pos = pSrc->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;

	while (pos != NULL)
	{
		p = pSrc->GetNext(pos);

		if (p->m_strName.GetLength() == 0)
		{
			continue;
		}

		pFind = pDest->FindByName(p->m_strName);

		if (pFind != NULL)
		{
			Update_ByName(p, pFind);
		}
	}

	return TRUE;
}


BOOL CExBaseListUpdateToolBase::Update_ByID(CExBaseObject *pSrc, CExBaseObject *pDest)
{
	if (Update_Own(pSrc, pDest))
	{
		return TRUE;
	}

	if (pSrc->IsBaseList() && pDest->IsBaseList())
	{
		Update_ByID((CExBaseList*)pSrc, (CExBaseList*)pDest);
	}

	return TRUE;
}

BOOL CExBaseListUpdateToolBase::Update_ByID(CExBaseList *pSrc, CExBaseList *pDest)
{
	POS pos = pSrc->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;

	while (pos != NULL)
	{
		p = pSrc->GetNext(pos);

		if (p->m_strID.GetLength() == 0)
		{
			continue;
		}

		pFind = pDest->FindByID(p->m_strID);

		if (pFind != NULL)
		{
			Update_ByID(p, pFind);
		}
	}

	return TRUE;
}


BOOL CExBaseListUpdateToolBase::Update_ByClassID(CExBaseObject *pSrc, CExBaseObject *pDest)
{
	if (Update_Own(pSrc, pDest))
	{
		return TRUE;
	}

	if (pSrc->IsBaseList() && pDest->IsBaseList())
	{
		Update_ByClassID((CExBaseList*)pSrc, (CExBaseList*)pDest);
	}

	return TRUE;
}

BOOL CExBaseListUpdateToolBase::Update_ByClassID(CExBaseList *pSrc, CExBaseList *pDest)
{
	POS pos = pSrc->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;

	while (pos != NULL)
	{
		p = pSrc->GetNext(pos);
		pFind = pDest->FindByClassID(p->GetClassID());

		if (pFind != NULL)
		{
			Update_ByClassID(p, pFind);
		}
	}

	return TRUE;
}

