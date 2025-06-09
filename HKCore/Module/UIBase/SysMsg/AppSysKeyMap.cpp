// AppSysKeyMap.cpp: implementation of the CAppSysKeyMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppSysKeyMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CAppSysKeyMap::g_pszKeyAppKey = "app-key";
const char* CAppSysKeyMap::g_pszKeySysKey = "sys-key";

CAppSysKeyMap::CAppSysKeyMap()
{
}

CAppSysKeyMap::~CAppSysKeyMap()
{
}

long CAppSysKeyMap::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
{
	if (!xml_GetAttibuteValue(g_pszKeyAppKey, oNode, m_strName))
	{
		debug_trace(".................");
	}
	
	if (!xml_GetAttibuteValue(g_pszKeySysKey, oNode, m_strName))
	{
		debug_trace(".................");
	}
	
	return 0;
}
