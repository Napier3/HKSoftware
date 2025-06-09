// DrawVariablesMngr.cpp: implementation of the CDrawVariablesMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawVariablesMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawVariablesMngr::CDrawVariablesMngr()
{
}

CDrawVariablesMngr::~CDrawVariablesMngr()
{
	DeleteAll();
}

CDrawVariable* CDrawVariablesMngr::FindVariable(CMemBuffer_Long *pBuffer)
{
	POS pos = GetHeadPosition();
	CDrawVariable *pVariable = NULL;
	CDrawVariable *pFind = NULL;

	while (pos != NULL)
	{
		pVariable = (CDrawVariable *)GetNext(pos);
		
		if (pVariable->m_pnAttachBuffer == pBuffer)
		{
			pFind = pVariable;
			break;
		}
	}

	return pFind;
}

