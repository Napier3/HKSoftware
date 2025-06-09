// ParaSort.cpp: implementation of the CParaSortObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ParaSort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParaSortObject::CParaSortObject()
{
	m_pDrawVaraible = NULL;
	m_rcClip = CRect(0,0,0,0);
	m_rcPara = CRect(0,0,0,0);
}

CParaSortObject::~CParaSortObject()
{
	m_pDrawVaraible = NULL;
}

CParaSortObject::CParaSortObject(CDrawAnalogVariable* pVariable)
{
	m_pDrawVaraible = pVariable;
#ifdef _SHOW_PARA
	m_rcPara = pVariable->m_oParas.m_rcPara;
#endif
	
}

/////////////////////////
CParaSortGroup::CParaSortGroup()
{
}

CParaSortGroup::~CParaSortGroup()
{
	RemoveAll();
}

void CParaSortGroup::AddTail(CParaSortGroup *pGroup)
{
	POS pos = pGroup->GetHeadPosition();
	CParaSortObject* pObj = NULL;
	
	while (pos != NULL)
	{
		pObj  = pGroup->GetNext(pos);
		AddTail(pObj);
	}

	CalParaGroupRect();
}
			
void CParaSortGroup::AddTail(CParaSortObject *pData)
{
	if (pData->IsParaSortObject()) 
	{
		CParaSortObjectList::AddTail(pData);
		CalParaGroupRect();
	}
	else
	{
		AddTail((CParaSortGroup*)pData);
	}
}	

void CParaSortGroup::AdjustVariablesParaRect()
{
	long nAmount = GetCount();
	long nPerHeight = m_rcPara.Height() / nAmount;
	POS  pos = GetHeadPosition();
	long nTop = m_rcPara.top;
	long nIndex = 0;
	CParaSortObject* pObj = NULL;
	CDrawAnalogVariable* pVariable = NULL;

	while(pos != NULL)
	{
		pObj = GetNext(pos);
		pVariable = pObj->m_pDrawVaraible;
		CRect rect = m_rcPara;
		rect.top = nTop + nIndex * nPerHeight;
		rect.bottom = nTop + (nIndex + 1) * nPerHeight - 1 ;
		pVariable->SetParaRect(rect);
		nIndex++;
	}
}

void CParaSortGroup::CalParaGroupRect()
{

#ifdef _SHOW_PARA
	long nTotalHeight = 0;
	long nChans = 0;
	long nSumCenter = 0;
	POS  pos = GetHeadPosition();
	CParaSortObject* pObj = GetHead();
	CDrawAnalogVariable* pVariable = pObj->m_pDrawVaraible;
	m_rcPara.left = pVariable->m_oParas.m_ptTopLeft.x;//pVariable->m_oParas.m_rcBorder.left;
	m_rcPara.right = pVariable->m_oParas.Right();//pVariable->m_oParas.m_rcBorder.right;
	
	while (pos != NULL)
	{
		pObj = GetNext(pos);
		pVariable = pObj->m_pDrawVaraible;
		nTotalHeight += pVariable->m_oParas.m_nHeight + 1;//pVariable->m_oParas.m_rcBorder.Height() + 1;//让各个通道的参数有1的间隔
		nSumCenter   += pVariable->m_nYCenter;
		nChans++;
	}
	
	long nCenterY = nSumCenter / nChans;
	m_rcPara.top = nCenterY - nTotalHeight / 2;
	m_rcPara.bottom = nCenterY + nTotalHeight / 2;
#endif

}

void CParaSortGroup::AdjustGroupRectByClip(const CRect &rcClip)
{
	long nHeight = m_rcPara.Height();

	if (m_rcPara.top < rcClip.top)
	{
		m_rcPara.top = rcClip.top;
		m_rcPara.bottom = m_rcPara.top + nHeight;
	}

	if (m_rcPara.bottom > rcClip.bottom)
	{
		m_rcPara.bottom = rcClip.bottom;
		m_rcPara.top = m_rcPara.bottom - nHeight;
	}

	AdjustVariablesParaRect();
}

////////////////////////////////////
CParaSortMngr::CParaSortMngr()
{
	m_rcClip = CRect(0,0,0,0);
}

CParaSortMngr::~CParaSortMngr()
{
	POS  pos = GetHeadPosition();

	while (pos != NULL)
	{
		CParaSortObject* pObj = GetNext(pos);

		if (pObj->IsParaSortObject())
		{
			delete pObj;
		}
		else
		{
			CParaSortGroup* pGroup = (CParaSortGroup*)pObj;
			pGroup->DeleteAll();
			delete pObj;
		}

		pObj = NULL;
	}

	RemoveAll();
}

CParaSortMngr::CParaSortMngr(CXDrawElements *pDrawVariables, const CRect &rcClip)
{
	POS  pos = pDrawVariables->GetHeadPosition();
	CParaSortObject *pNew = NULL;
	m_rcClip = rcClip;
	
	while(pos!=NULL)
	{
		CDrawVariable* pObj = (CDrawVariable*)pDrawVariables->GetNext(pos);

		if (pObj->GetClassID() == CMTRDCLASSID_ANALOGVARIABLE
			|| pObj->GetClassID() == CMTRDCLASSID_CMPANALOGVARIABLE)
		{
			pNew = new CParaSortObject((CDrawAnalogVariable*)pObj);
			AddTail(pNew);
		}	
	}
	
	SortByParaRect();
}

BOOL CParaSortMngr::IsParaRectIntersect(CParaSortObject *p1, CParaSortObject *p2)
{
	CRect rect1 = p1->m_rcPara;
	CRect rect2 = p2->m_rcPara;
	
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

BOOL CParaSortMngr::SortByParaRect()
{
	POS  posFirst = GetHeadPosition();
	BOOL bNeedSort = FALSE;

	while (posFirst != NULL)
	{
		if (SortByParaRect(posFirst))
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

BOOL CParaSortMngr::SortByParaRect(POS  posFirst)
{	
	POS  posCurr  = posFirst;
	CParaSortObject* pFirst   = GetNext(posCurr);

	if (posCurr == NULL)
	{
		return FALSE;
	}

	CParaSortObject* pCurr    = GetAt(posCurr);

	BOOL bHasGroup = FALSE;
	CParaSortGroup* pGroup = NULL;
	POS  posTemp = NULL;
	
	while (posCurr != NULL)
	{
		if (IsParaRectIntersect(pFirst,pCurr))
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

CParaSortGroup* CParaSortMngr::CreateGroup(CParaSortObject* pFirst,CParaSortObject* pCurr)
{
	CParaSortGroup* pGroup = new CParaSortGroup();
	pGroup->AddTail(pFirst);
	pGroup->AddTail(pCurr);
	
	if (pFirst->IsParaSortObject() == FALSE)
	{
		CParaSortGroup* pG = (CParaSortGroup*)pFirst;
		pG->RemoveAll();
		delete pFirst;
		pFirst = NULL;
	}
	
	if (pCurr->IsParaSortObject() == FALSE)
	{
		CParaSortGroup* pG = (CParaSortGroup*)pCurr;
		pG->RemoveAll();
		delete pCurr;
		pCurr = NULL;
	}
	
	return pGroup;
}
