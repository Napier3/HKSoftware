// SystemMessage.cpp: implementation of the CSystemMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemMessage::CSystemMessage()
{
	m_nID = 0;
	m_nIndex = -1;
	m_dwTickCount = 0;
	m_bMsgHasPosted = FALSE;
}

CSystemMessage::~CSystemMessage()
{
}

long CSystemMessage::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
{
	CExBaseObject::ReadOwnXml(oNode);

	if (!xml_GetAttibuteValue(g_pszKeyID, oNode, m_nID))
	{
		debug_trace(".................");
	}
	
	return 0;
}
