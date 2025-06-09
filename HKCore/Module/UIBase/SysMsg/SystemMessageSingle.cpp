// SystemMessageSingle.cpp: implementation of the CSystemMessageSingle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemMessageSingle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CSystemMessageSingle::g_pszKey_KeyName     = "key-name";
const char* CSystemMessageSingle::g_pszKey_KeyState    = "key-state";
const char* CSystemMessageSingle::g_pszKeySingleSysMsg = "single-sys-msg";

const char* CSystemMessageSingle::g_pszKey_KeyStateDown    = "down";
const char* CSystemMessageSingle::g_pszKey_KeyStateUp      = "up";
const char* CSystemMessageSingle::g_pszKey_KeyStateClick   = "click";
const char* CSystemMessageSingle::g_pszKey_KeyStateDbClick = "dbclick";

CSystemMessageSingle::CSystemMessageSingle()
{
	m_nKeyState = KEYSTATE_ERROR;
	m_nSysKeyID = 0;
	m_strKeyName = "";
}

CSystemMessageSingle::~CSystemMessageSingle()
{
}

long CSystemMessageSingle::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
{
	CSystemMessage::ReadOwnXml(oNode);

	if (!xml_GetAttibuteValue(g_pszKey_KeyName, oNode, m_strKeyName))
	{
		debug_trace(".................");
	}
	
	CString strKeyState;
	
	if (!xml_GetAttibuteValue(g_pszKey_KeyState, oNode, strKeyState))
	{
		debug_trace(".................");
	}
	
	if (stricmp(strKeyState, g_pszKey_KeyStateDown) == 0)
	{
		m_nKeyState = KEYSTATE_DOWN;
	}
	else if (stricmp(strKeyState, g_pszKey_KeyStateUp) == 0)
	{
		m_nKeyState = KEYSTATE_UP;
	}
	else if (stricmp(strKeyState, g_pszKey_KeyStateClick) == 0)
	{
		m_nKeyState = KEYSTATE_CLICK;
	}
	else if (stricmp(strKeyState, g_pszKey_KeyStateDbClick) == 0)
	{
		m_nKeyState = KEYSTATE_DBCLICK;
	}
	else
	{
	}

	return 0;
}

void CSystemMessageSingle::InitSingleSystemMessage(CSystemKeys *pSysKeys)
{
	CSystemKey *pFind = NULL;
	pFind = pSysKeys->FindByKeyName(m_strKeyName);
	
	if (pFind == NULL)
	{
		debug_trace("Error key");
	}
	else
	{
		m_nSysKeyID = pFind->m_nID;
	}
}

CSystemMessage* CSystemMessageSingle::Clone()
{
	CSystemMessageSingle *pMsg = new CSystemMessageSingle();

	pMsg->m_strName     = m_strName;
	pMsg->m_strID       = m_strID;
	pMsg->m_nSysKeyID   = m_nSysKeyID;
	pMsg->m_nID         = m_nID;
	pMsg->m_nIndex      = m_nIndex;
	pMsg->m_dwTickCount = m_dwTickCount;

	pMsg->m_strKeyName = m_strKeyName;
	pMsg->m_nKeyState  = m_nKeyState;

	return pMsg;
}

long CSystemMessageSingle::GetSysKeyState(UINT nMsg, long &nKeyState)
{
	if (nMsg == WM_KEYDOWN || nMsg == WM_SYSKEYDOWN)
	{
		nKeyState = KEYSTATE_DOWN;
	}
	else if (nMsg == WM_KEYUP || nMsg == WM_SYSKEYUP)
	{
		nKeyState = KEYSTATE_UP;
	}
	else
	{
		nKeyState = KEYSTATE_ERROR;
	}
	
	return nKeyState;
}

BOOL SysMsg_IsKeyDown(CSystemMessage *pSysMsg, UINT nKeyID)
{
	if (!SysMsg_IsSingle(pSysMsg))
	{
		return FALSE;
	}

	CSystemMessageSingle *pSingleSysMsg = (CSystemMessageSingle*)pSysMsg;
	return pSingleSysMsg->IsKeyDown(nKeyID);
}

BOOL SysMsg_IsKeyUp(CSystemMessage *pSysMsg, UINT nKeyID)
{
	if (!SysMsg_IsSingle(pSysMsg))
	{
		return FALSE;
	}
	
	CSystemMessageSingle *pSingleSysMsg = (CSystemMessageSingle*)pSysMsg;
	return pSingleSysMsg->IsKeyUp(nKeyID);
}

BOOL SysMsg_IsKeyClick(CSystemMessage *pSysMsg, UINT nKeyID)
{
	if (!SysMsg_IsSingle(pSysMsg))
	{
		return FALSE;
	}
	
	CSystemMessageSingle *pSingleSysMsg = (CSystemMessageSingle*)pSysMsg;
	return pSingleSysMsg->IsKeyClick(nKeyID);
}

BOOL SysMsg_IsKeyDbClick(CSystemMessage *pSysMsg, UINT nKeyID)
{
	if (!SysMsg_IsSingle(pSysMsg))
	{
		return FALSE;
	}
	
	CSystemMessageSingle *pSingleSysMsg = (CSystemMessageSingle*)pSysMsg;
	return pSingleSysMsg->IsKeyDbClick(nKeyID);
}

BOOL SysMsg_IsKeyDown(CSystemMessage *pSysMsg)
{
	if (!SysMsg_IsSingle(pSysMsg))
	{
		return FALSE;
	}
	
	CSystemMessageSingle *pSingleSysMsg = (CSystemMessageSingle*)pSysMsg;
	return pSingleSysMsg->IsKeyDown();
}

BOOL SysMsg_IsKeyUp(CSystemMessage *pSysMsg)
{
	if (!SysMsg_IsSingle(pSysMsg))
	{
		return FALSE;
	}
	
	CSystemMessageSingle *pSingleSysMsg = (CSystemMessageSingle*)pSysMsg;
	return pSingleSysMsg->IsKeyUp();
}

BOOL SysMsg_IsKeyClick(CSystemMessage *pSysMsg)
{
	if (!SysMsg_IsSingle(pSysMsg))
	{
		return FALSE;
	}
	
	CSystemMessageSingle *pSingleSysMsg = (CSystemMessageSingle*)pSysMsg;
	return pSingleSysMsg->IsKeyClick();
}

BOOL SysMsg_IsKeyDbClick(CSystemMessage *pSysMsg)
{
	if (!SysMsg_IsSingle(pSysMsg))
	{
		return FALSE;
	}
	
	CSystemMessageSingle *pSingleSysMsg = (CSystemMessageSingle*)pSysMsg;
	return pSingleSysMsg->IsKeyDbClick();
}

