// RtSpy.cpp: implementation of the CRtSpy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtSpy.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char *CRtSpy::g_pszKeySpy         = "spy";
const char *CRtSpy::g_pszKeyRefreshTime = "refresh-time";
const char *CRtSpy::g_pszKeyTimeWnd     = "time-wnd";

CRtSpy::CRtSpy()
{
	m_strName = "RtSpy";
	m_strID = m_strName;	
}

CRtSpy::~CRtSpy()
{
}
// 
// long CRtSpy::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	xml_GetAttibuteValue(g_pszKeyRefreshTime, oNode, m_nRefreshTime);
// 	xml_GetAttibuteValue(g_pszKeyTimeWnd, oNode, m_nTimeWnd);
// 	
// 	return 0;
// }
// 
// long CRtSpy::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }
