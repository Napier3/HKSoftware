// NameSort.cpp: implementation of the CNameSortObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NameSort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNameSortObject::CNameSortObject()
{
	m_pDrawVaraible = NULL;
	m_nType = Name_Sort;
	m_rcName = CRect(0,0,0,0);
	m_rcClip = CRect(0,0,0,0);
}

CNameSortObject::~CNameSortObject()
{
	m_pDrawVaraible = NULL;
}

CNameSortObject::CNameSortObject(CDrawVariable* pVariable,UINT nType)
{
	m_pDrawVaraible = pVariable;
	m_rcName = pVariable->m_rcNameRectOrigin;
}

/////////////////////////
CNameSortGroup::CNameSortGroup()
{
}

CNameSortGroup::~CNameSortGroup()
{
	RemoveAll();
}

void CNameSortGroup::AddTail(CNameSortGroup *pGroup)
{
	POS pos = pGroup->GetHeadPosition();
	CNameSortObject* pObj = NULL;
	
	while (pos != NULL)
	{
		pObj  = (CNameSortObject*)pGroup->GetNext(pos);
		CNameSortObjectList::AddTail(pObj);
	}

	CalNameGroupRect();
}
			
void CNameSortGroup::AddTail(CNameSortObject *pData)
{
	if (pData->IsNameSortObject()) 
	{
		CNameSortObjectList::AddTail(pData);
		CalNameGroupRect();
	}
	else
	{
		AddTail((CNameSortGroup*)pData);
	}
}	

void CNameSortGroup::AdjustVariablesNameRect()
{
	long nAmount = GetCount();
	long nPerHeight = m_rcName.Height() / nAmount;
	POS pos = GetHeadPosition();
	long nTop = m_rcName.top;
	long nIndex = 0;
	CNameSortObject* pObj = NULL;
	CDrawVariable* pVariable = NULL;

	while(pos != NULL)
	{
		pObj = (CNameSortObject*)GetNext(pos);
		pVariable = pObj->m_pDrawVaraible;
//		pVariable->m_rcName.top = nTop + nIndex * nPerHeight;
//		pVariable->m_rcName.bottom = nTop + (nIndex + 1) * nPerHeight;
		pVariable->SetNameRectTop(nTop + nIndex * nPerHeight);
		pVariable->SetNameRectBottom(nTop + (nIndex + 1) * nPerHeight);
		nIndex++;
	}
}

void CNameSortGroup::CalNameGroupRect()
{
	long nTotalHeight = 0;
	long nChans = 0;
	long nSumCenter = 0;
	POS  pos = GetHeadPosition();
	CNameSortObject* pObj = GetHead();
	CDrawVariable* pVariable = pObj->m_pDrawVaraible;
	m_rcName.left = pVariable->m_rcNameRectOrigin.left;
	m_rcName.right = pVariable->m_rcNameRectOrigin.right;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		pVariable = pObj->m_pDrawVaraible;
		nTotalHeight += pVariable->m_rcNameRectOrigin.Height();
		nSumCenter   += pVariable->m_nYCenter;
		nChans++;
	}
	
	long nCenterY = nSumCenter / nChans;
	m_rcName.top = nCenterY - nTotalHeight / 2;
	m_rcName.bottom = nCenterY + nTotalHeight / 2;

}

void CNameSortGroup::AdjustGroupRectByClip(const CRect &rcClip)
{
	long nHeight = m_rcName.Height();

	if (m_rcName.top < rcClip.top)
	{
		m_rcName.top = rcClip.top;
		m_rcName.bottom = m_rcName.top + nHeight;
	}

	if (m_rcName.bottom > rcClip.bottom)
	{
		m_rcName.bottom = rcClip.bottom;
		m_rcName.top = m_rcName.bottom - nHeight;
	}

	AdjustVariablesNameRect();
}

////////////////////////////////////
CNameSortMngr::CNameSortMngr()
{
	m_rcClip = CRect(0,0,0,0);
}

CNameSortMngr::~CNameSortMngr()
{
	POS  pos = GetHeadPosition();

	while (pos != NULL)
	{
		CNameSortObject* pObj = GetNext(pos);

		if (pObj->IsNameSortObject())
		{
			delete pObj;
		}
		else
		{
			CNameSortGroup* pGroup = (CNameSortGroup*)pObj;
			pGroup->DeleteAll();
			delete pObj;
		}

		pObj = NULL;
	}

	RemoveAll();
}

CNameSortMngr::CNameSortMngr(CXDrawElements *pDrawVariables, const CRect &rcClip,UINT nType)
{
	POS pos = pDrawVariables->GetHeadPosition();
	CNameSortObject *pNew = NULL;
	m_rcClip = rcClip;
	
	while(pos!=NULL)
	{
		CDrawVariable* pObj = (CDrawVariable*)pDrawVariables->GetNext(pos);
		pNew = new CNameSortObject(pObj,nType);
		AddTail(pNew);
	}
	
	SortByNameRect();
}

BOOL CNameSortMngr::IsNameRectIntersect(CNameSortObject *p1, CNameSortObject *p2)
{
	CRect rect1 = p1->m_rcName;
	CRect rect2 = p2->m_rcName;
	
	if((rect1.top >= rect2.top && rect1.top < rect2.bottom) || (rect2.top >= rect1.top && rect2.top < rect1.bottom))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CNameSortMngr::SortByNameRect()
{
	POS  posFirst = GetHeadPosition();
	BOOL bNeedSort = FALSE;

	while (posFirst != NULL)
	{
		if (SortByNameRect(posFirst))
		{
			bNeedSort = TRUE;
			GetNext(posFirst);
		}
		else
		{
			GetNext(posFirst);
		}
	}
	
	return bNeedSort;
}

BOOL CNameSortMngr::SortByNameRect(POS  posFirst)
{	
	POS  posCurr  = posFirst;
	CNameSortObject* pFirst   = GetNext(posCurr);

	if (posCurr == NULL)
	{
		return FALSE;
	}

	CNameSortObject* pCurr    = GetAt(posCurr);

	BOOL bHasGroup = FALSE;
	CNameSortGroup* pGroup = NULL;
	POS  posTemp = NULL;
	
	while (posCurr != NULL)
	{
		if (IsNameRectIntersect(pFirst,pCurr))
		{
			pGroup = CreateGroup(pFirst, pCurr);
			pGroup->AdjustGroupRectByClip(m_rcClip);

			pFirst = pGroup;
			SetAt(posFirst, pFirst);
			posTemp = posCurr;
			pCurr = GetNext(posCurr);
			RemoveAt(posTemp);
			bHasGroup = TRUE;

			if (posCurr != NULL)
			{
				pCurr = GetAt(posCurr);
			}
		}
		else
		{
			pCurr = GetNext(posCurr);
		}
	}
	
	return bHasGroup;
}

CNameSortGroup* CNameSortMngr::CreateGroup(CNameSortObject* pFirst,CNameSortObject* pCurr)
{
	CNameSortGroup* pGroup = new CNameSortGroup();
	pGroup->AddTail(pFirst);
	pGroup->AddTail(pCurr);
	
	if (pFirst->IsNameSortObject() == FALSE)
	{
		CNameSortGroup* pG = (CNameSortGroup*)pFirst;
		pG->RemoveAll();
		delete pFirst;
		pFirst = NULL;
	}
	
	if (pCurr->IsNameSortObject() == FALSE)
	{
		CNameSortGroup* pG = (CNameSortGroup*)pCurr;
		pG->RemoveAll();
		delete pCurr;
		pCurr = NULL;
	}
	
	return pGroup;
}
