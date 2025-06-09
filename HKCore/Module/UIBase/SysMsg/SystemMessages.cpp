// SystemMessages.cpp: implementation of the CSystemMessages class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemMessages.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CSystemMessages::g_pszKeySingleSysMsgs = "single-sys-msgs";
const char* CSystemMessages::g_pszKeyMultiSysMsgs = "multi-sys-msgs";

CSystemMessages::CSystemMessages()
{
}

CSystemMessages::~CSystemMessages()
{
}

//XML¶ÁÐ´
CExBaseObject* CSystemMessages::CreateNewChild(LPCTSTR pszClassID)
{
	CExBaseObject *pNew = NULL;
	
	if (stricmp(pszClassID, CSystemMessageMulti::g_pszKeyMultiSysMsg) == 0)
	{
		pNew  = new CSystemMessageMulti();
	}
	else if (stricmp(pszClassID, CSystemMessageSingle::g_pszKeySingleSysMsg) == 0)
	{
		pNew  = new CSystemMessageSingle();
	}
	else
	{
	}

	return pNew;
}

CExBaseObject* CSystemMessages::CreateNewChild(long nClassID)
{
	return NULL;
}


void CSystemMessages::InitSingleSystemMessages(CSystemKeys *pSysKeys)
{
	CExBaseObject *pObj = NULL;
	CSystemMessageSingle *pSysMsg = NULL;
	void *pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pObj = GetNext(pos);
		
		if (pObj->GetClassID() == CLASSID_SYSTEMMESSAGE_SINGLE)
		{
			pSysMsg = (CSystemMessageSingle*)pObj;
			pSysMsg->InitSingleSystemMessage(pSysKeys);
		}
	}
}

void CSystemMessages::InitMultiSystemMessages(CSystemMessages *pSingleSysMsgs)
{
	CExBaseObject *pObj = NULL;
	CSystemMessageMulti *pSysMsg = NULL;
	void *pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pObj = GetNext(pos);
		
		if (pObj->GetClassID() == CLASSID_SYSTEMMESSAGE_MULTI)
		{
			pSysMsg = (CSystemMessageMulti*)pObj;
			pSysMsg->InitMultiSystemMessage(pSingleSysMsgs);
		}
	}
}

CSystemMessageSingle* CSystemMessages::FindSingleSysMsg(UINT nKeyID, long nKeyState)
{
	CExBaseObject *pObj = NULL;
	CSystemMessageSingle *pSysMsg = NULL;
	CSystemMessageSingle *pFind = NULL;

	void *pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (pObj->GetClassID() == CLASSID_SYSTEMMESSAGE_SINGLE)
		{
			pSysMsg = (CSystemMessageSingle*)pObj;

			if (pSysMsg->m_nKeyState == nKeyState && pSysMsg->m_nSysKeyID == nKeyID)
			{
				pFind = pSysMsg;
				break;
			}
		}
	}

	return pFind;
}

