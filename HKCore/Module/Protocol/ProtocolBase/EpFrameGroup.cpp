// EpFrameGroup.cpp: implementation of the CEpFrameGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpFrameGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpFrameGroup::CEpFrameGroup()
{ 
	m_strName = "EpFrameGroup";
}

CEpFrameGroup::~CEpFrameGroup()
{

}

long CEpFrameGroup::IsEqual(CExBaseObject* pObj)
{
	CEpFrameGroup *p = (CEpFrameGroup*)pObj;

	return 0;
}

long CEpFrameGroup::Copy(CExBaseObject* pDesObj)
{
	CEpFrameGroup *p = (CEpFrameGroup*)pDesObj;

	return 0;
}

CBaseObject* CEpFrameGroup::Clone()
{
	CEpFrameGroup *pNew = new CEpFrameGroup();

	return pNew;
}

DWORD CEpFrameGroup::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	ASSERT (FALSE);
	return 0;
}

CEpFrameBase* CEpFrameGroup::Match(PEPBUFFERPOS pBufferPos)
{
	CEpFrameBase *p = NULL;
	CEpFrameBase *pMatch = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		EPBUFFERPOS oEpBufPos;
		Ep_BackBufferPos(*pBufferPos, oEpBufPos);
		p = (CEpFrameBase*)GetNext(pos);

		if (p->Match(pBufferPos))
		{
			pMatch = p;
			break;
		}

		Ep_BackBufferPos(oEpBufPos, *pBufferPos);
	}

	return pMatch;
}

DWORD CEpFrameGroup::Produce(PEPBUFFERPOS pBufferPos)
{
	ASSERT (FALSE);
	return 0;
}

void CEpFrameGroup::AddFrameAsdu(CEpFrameAsdu *pAsdu)
{
	AddNewChild(pAsdu);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpFrameGroups::CEpFrameGroups()
{ 
	m_strName = "EpFrameGroup";
}

CEpFrameGroups::~CEpFrameGroups()
{

}

long CEpFrameGroups::IsEqual(CExBaseObject* pObj)
{
	CEpFrameGroups *p = (CEpFrameGroups*)pObj;

	return 0;
}

long CEpFrameGroups::Copy(CExBaseObject* pDesObj)
{
	CEpFrameGroups *p = (CEpFrameGroups*)pDesObj;

	return 0;
}

CBaseObject* CEpFrameGroups::Clone()
{
	CEpFrameGroups *pNew = new CEpFrameGroups();

	return pNew;
}

CEpFrameBase* CEpFrameGroups::Match(PEPBUFFERPOS pBufferPos)
{
	CEpFrameGroup *p = NULL;
	CEpFrameBase *pMatch = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		EPBUFFERPOS oEpBufPos;
		Ep_BackBufferPos(*pBufferPos, oEpBufPos);

		p = (CEpFrameGroup*)GetNext(pos);
		pMatch = p->Match(pBufferPos);


		if (pMatch != NULL)
		{
			break;
		}

		Ep_BackBufferPos(oEpBufPos, *pBufferPos);
	}

	return pMatch;
}


CExBaseObject* CEpFrameGroups::FindByClassID(DWORD dwClassID)
{
	CEpFrameGroup *pGroup = NULL;
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pGroup = (CEpFrameGroup*)GetNext(pos);
		p = pGroup->FindByClassID(dwClassID);

		if (p != NULL)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}
