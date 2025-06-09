// RtComplexVariable.cpp: implementation of the CRtComplexVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtComplexVariable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// const char *CRtComplexVariable::g_pszKeyComplexVariable		= "complex-variable";

CRtComplexVariable::CRtComplexVariable()
{
}

CRtComplexVariable::~CRtComplexVariable()
{
}
// 
// //ÖØÔØµÄº¯Êý
// long CRtComplexVariable::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CRtSingleVariable::ReadOwnXml(oNode);
// 
// 	return 0;
// }
// 
// const char* CRtComplexVariable::GetXmlElementKey()
// {
// 	return g_pszKeySingleVariable;
// }
// 
// long CRtComplexVariable::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	CRtSingleVariable::WriteOwnXml(oXMLDoc, oElement);
// 
// 	return 0;
// }
// 
// BOOL CRtComplexVariable::ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CRtVariable::ReadSetsValueXml(oNode);	
// 	return TRUE;
// }
// 
// BOOL CRtComplexVariable::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oComplexVariable;
// 	oComplexVariable = oXMLDoc->createElement(_bstr_t(g_pszKeyComplexVariable));
// 	oComplexVariable->setAttribute(_bstr_t(g_pszKeyName), _bstr_t(m_strName));
// 	oComplexVariable->setAttribute(_bstr_t(g_pszKeyID), _bstr_t(m_strID));
// 	oComplexVariable->setAttribute(_bstr_t(g_pszKeyType), _bstr_t(RT_GetStringUIBType(m_nType)));
// 	oComplexVariable->setAttribute(_bstr_t(g_pszKeyDCAC), _bstr_t(m_strDCAC));
// 	oComplexVariable->setAttribute(_bstr_t(g_pszKeyVariableUse), m_nVariableUse);
// 	
// 	CRtDataAttributes *pDataAttrs = m_pDataAttrs;
// 	
// 	if (pDataAttrs != NULL)
// 	{
// 		pDataAttrs->WriteSetsValueXml(oXMLDoc, oComplexVariable);
// 	}
// 	
// 	oParent->appendChild(oComplexVariable);
// 	
// 	return TRUE;
// }
// 
// 
