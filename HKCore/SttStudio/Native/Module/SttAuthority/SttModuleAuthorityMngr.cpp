#include "stdafx.h"
#include "SttModuleAuthorityMngr.h"
#include "SttModuleAuthority.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttModuleAuthorityMngr::CSttModuleAuthorityMngr()
{

}

CSttModuleAuthorityMngr::~CSttModuleAuthorityMngr()
{

}

BOOL CSttModuleAuthorityMngr::HasAuthority(const CString &strModuleID)
{
	CSttModuleAuthority *pFind = (CSttModuleAuthority *)FindByID(strModuleID);

	if (pFind != NULL)
	{
		if (pFind->m_nHasAuthority != 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CSttModuleAuthorityMngr::SetAuthority(const CString &strModuleID, long nValue)
{
	CSttModuleAuthority *pFind = (CSttModuleAuthority *)FindByID(strModuleID);

	if (pFind == NULL)
	{
		pFind = new CSttModuleAuthority;
		pFind->m_strID = strModuleID;
		AddNewChild(pFind);
	}

	pFind->m_nHasAuthority = nValue;
}