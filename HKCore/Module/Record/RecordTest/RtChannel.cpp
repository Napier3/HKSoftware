// RtChannel.cpp: implementation of the CRtChannel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtChannel.h"
#include "RtVariables.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// const char *CRtChannel::g_pszKeyChannel = "channel";

CRtChannel::CRtChannel()
{
	m_pAttachVariable = NULL;
}

CRtChannel::~CRtChannel()
{
}

UINT CRtChannel::GetClassID()
{
	return RTCLASSID_CHANNEL;
}
// 
// long CRtChannel::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CExBaseObject::ReadOwnXml(oNode);
// 	m_strName = m_strID;
// 	m_pAttachVariable = GetAttchVariableByID();
// 	return 1;
// }
// 
// const char* CRtChannel::GetXmlElementKey()
// {
// 	return g_pszKeyChannel;
// }
// 
// long CRtChannel::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }

CRtVariable* CRtChannel::GetAttchVariableByID()
{
	CRtVariable* pObj = NULL;

	CRtVariables* pRtVairiables = (CRtVariables*)GetAncestor(RTCLASSID_VARIABLES);

	if (pRtVairiables == NULL)
	{
		return NULL;
	}
	else
	{
		pObj = pRtVairiables->FindByVariableID(m_strID.GetString());
	}

	return pObj;
}
// 
// BOOL CRtChannel::ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	xml_GetAttibuteValue(CBaseObject::g_pszKeyID, oNode, m_strID);
// 	m_strName = m_strID;
// 
// 	m_pAttachVariable = GetAttchVariableByID();
// 
// 	return TRUE;
// }
// 
// BOOL CRtChannel::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oChannel;
// 	oChannel = oXMLDoc->createElement(_bstr_t(g_pszKeyChannel));
// 	oChannel->setAttribute(_bstr_t(g_pszKeyID), _bstr_t(m_strID));//	oDataAttr->setAttribute(_bstr_t(g_pszKeyID), _bstr_t(m_strID));
// 	oParent->appendChild(oChannel);
// 
// 	return TRUE;
// }

void CRtChannel::SetAttachVariable(CRtVariable* pAttachVariable)
{
	if (pAttachVariable != NULL)
	{
		m_pAttachVariable = pAttachVariable;
		m_strID = pAttachVariable->m_strID;
	}
}

void CRtChannel::InitChannal(const char *pszChName)
{
	CString str = pszChName;

	if (str.IsEmpty())
	{
		return;
	}

	m_strID = pszChName;
	m_pAttachVariable = GetAttchVariableByID();
}