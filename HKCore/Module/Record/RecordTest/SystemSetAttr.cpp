// SystemSetAttr.cpp: implementation of the CSystemSetAttr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemSetAttr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// const char* CSystemSetAttr::g_pszKeySystemSetsAttr  = "attr";
// const char* CSystemSetAttr::g_pszKeyAttrUse			= "use";
// const char* CSystemSetAttr::g_pszKeyHigh			= "high";
// const char* CSystemSetAttr::g_pszKeyHighUse			= "huse";
// const char* CSystemSetAttr::g_pszKeyLow				= "low";
// const char* CSystemSetAttr::g_pszKeyLowUse			= "luse";
// const char* CSystemSetAttr::g_pszKeyMutation		= "mutation";
// const char* CSystemSetAttr::g_pszKeyMutationUse		= "muse";

CSystemSetAttr::CSystemSetAttr()
{
	m_dHighPercentValue		= 0;
	m_dLowPercentValue		= 0;
	m_dMutationPercentValue	= 0;
	
	m_nAttrUse			= 0;
	m_nHighUse			= 0;
	m_nLowUse			= 0;
	m_nMutationUse		= 0;
}

CSystemSetAttr::~CSystemSetAttr()
{

}
// 
// long CSystemSetAttr::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CExBaseObject::ReadOwnXml(oNode);
// 	xml_GetAttibuteValue(g_pszKeyAttrUse, oNode, m_nAttrUse);
// 	xml_GetAttibuteValue(g_pszKeyHigh, oNode, m_dHighPercentValue);
// 	xml_GetAttibuteValue(g_pszKeyHighUse, oNode, m_nHighUse);
// 	xml_GetAttibuteValue(g_pszKeyLow, oNode, m_dLowPercentValue);
// 	xml_GetAttibuteValue(g_pszKeyLowUse, oNode, m_nLowUse);
// 	xml_GetAttibuteValue(g_pszKeyMutation, oNode, m_dMutationPercentValue);
// 	xml_GetAttibuteValue(g_pszKeyMutationUse, oNode, m_nMutationUse);
// 
// 	return 0;
// }
