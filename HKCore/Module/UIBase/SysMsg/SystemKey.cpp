// SystemKey.cpp: implementation of the CSystemKey class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemKey.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CSystemKey::g_pszKeySysKey = "sys-key";

CSystemKey::CSystemKey()
{
	m_nID = 0;	
}

CSystemKey::~CSystemKey()
{
}

long CSystemKey::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
{
	CExBaseObject::ReadOwnXml(oNode);
	
	if (!xml_GetAttibuteValue(g_pszKeyID, oNode, m_nID))
	{
		debug_trace(".................");
	}
		
	return 0;
}
