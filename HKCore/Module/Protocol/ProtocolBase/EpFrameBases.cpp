// EpFrameBases.cpp: implementation of the CEpFrameBases class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpFrameBases.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpFrameBases::CEpFrameBases()
{

}

CEpFrameBases::~CEpFrameBases()
{

}

CEpFrameBase* CEpFrameBases::FindByClassID(UINT nClassID)
{
	CEpFrameBase *p = NULL;
	CEpFrameBase *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpFrameBase*)GetNext(pos);

		if (p->GetClassID() == nClassID)
		{
			pFind = p;
			break;
		}
	}

	return p;
}

CEpFrameBase* CEpFrameBases::FindByOwnClassID(UINT nClassID)
{
	CEpFrameBase *p = NULL;
	CEpFrameBase *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpFrameBase*)GetNext(pos);

		if ( ( p->GetClassID() && EPCLASSID_OWN_MASK )== nClassID)
		{
			pFind = p;
			break;
		}
	}

	return p;
}
