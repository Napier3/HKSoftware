// RtCfgVariables.cpp: implementation of the CRtCfgVariables class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtCfgVariables.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *CRtCfgVariables::g_pszKeyVariables    = "variables";

CRtCfgVariables::CRtCfgVariables()
{
	m_strName = "Variables";
}

CRtCfgVariables::~CRtCfgVariables()
{
	m_oUVariList.RemoveAll();	
	m_oIVariList.RemoveAll();
}

CExBaseObject* CRtCfgVariables::CreateNewChild(const char *pszClassID)
{
	CRtCfgVariable *pNew = NULL;

	if (strcmp(pszClassID, CRtCfgVariable::g_pszKeyBinaryVariable) == 0)
	{
		pNew  = new CRtCfgVariable();
		pNew->m_bIsBinaryVariable = TRUE;
	}
	else if (strcmp(pszClassID, CRtCfgVariable::g_pszKeySingleVariable) == 0)
	{
		pNew  = new CRtCfgVariable();
		pNew->m_bIsBinaryVariable = FALSE;
	}
	else
	{
	}

	return pNew;
}

