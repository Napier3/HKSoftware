// SystemKeys.cpp: implementation of the CSystemKeys class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemKeys.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CSystemKeys::g_pszKeySysKeys = "sys-keys";

CSystemKeys::CSystemKeys()
{
}

CSystemKeys::~CSystemKeys()
{
}

//XML¶ÁÐ´
CExBaseObject* CSystemKeys::CreateNewChild(LPCTSTR pszClassID)
{
	return new CSystemKey();
}

CExBaseObject* CSystemKeys::CreateNewChild(long nClassID)
{
	return NULL;
}

CSystemKey* CSystemKeys::FindByKeyName(const CString &strKeyName)
{
	CSystemKey* pFind = (CSystemKey*)FindByName(strKeyName);

	return pFind;
}

CSystemKey* CSystemKeys::FindByKeyID(long nKeyID)
{
	CSystemKey *pFind = NULL;
	CSystemKey *pKey = NULL;

	void *pos = GetHeadPosition();

	while (pos != NULL)
	{
		pKey = (CSystemKey*)GetNext(pos);

		if (pKey->m_nID == nKeyID)
		{
			pFind = pKey;
			break;
		}
	}

	return pFind;
}
