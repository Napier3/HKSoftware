// appsyskeymaps.cpp: implementation of the CAppSysKeyMaps class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "appsyskeymaps.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CAppSysKeyMaps::g_pszKeyAppName = "app-name";
const char* CAppSysKeyMaps::g_pszKeyKeyMaps = "key-maps";

CAppSysKeyMaps::CAppSysKeyMaps()
{
	m_strAppName = "";
}

CAppSysKeyMaps::~CAppSysKeyMaps()
{
}

//XML¶ÁÐ´
CExBaseObject* CAppSysKeyMaps::CreateNewChild(LPCTSTR pszClassID)
{
	return new CAppSysKeyMap();
}

CExBaseObject* CAppSysKeyMaps::CreateNewChild(long nClassID)
{
	return new CAppSysKeyMap();
}

long CAppSysKeyMaps::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
{
	if (!xml_GetAttibuteValue(g_pszKeyAppName, oNode, m_strAppName))
	{
		debug_trace(".................");
	}
	
	return 0;
}
