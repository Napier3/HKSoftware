// RtBufferConfig.cpp: implementation of the CRtBufferConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtBufferConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//πÿº¸◊÷ Ù–‘
const char* CRtBufferConfig::g_pszKeyRtBuffer     = "rt-buffer";
const char* CRtBufferConfig::g_pszKeyMaxBuffer    = "max-buffer";
const char* CRtBufferConfig::g_pszKeySpyBuffer    = "spy-buffer";
const char* CRtBufferConfig::g_pszKeyRecordBuffer = "record-buffer";
const char* CRtBufferConfig::g_pszKeyAttrBuffer   = "attr-buffer";
const char* CRtBufferConfig::g_pszKeyAttrTimeGap  = "atr-time-gap";
const char* CRtBufferConfig::g_pszKeyRecordGap    = "record-gap";

CRtBufferConfig::CRtBufferConfig()
{
	//≈‰÷√ Ù–‘
	m_nMaxBuffer    = 400;
	m_nSpyBuffer    = 60;
	m_nRecordBuffer = 300;
	m_nAttrBuffer   = 40; 
	m_nAttrTimeGap  = 500;
	m_nHDBuffer     = 2;

	m_strName = "RtBufferConfig";
	m_strID = m_strName;
	m_nRecordGap = 0;
}

CRtBufferConfig::~CRtBufferConfig()
{

}
// 
// long CRtBufferConfig::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	xml_GetAttibuteValue(g_pszKeyMaxBuffer, oNode, m_nMaxBuffer);
// 	xml_GetAttibuteValue(g_pszKeySpyBuffer, oNode, m_nSpyBuffer);
// 	xml_GetAttibuteValue(g_pszKeyRecordBuffer, oNode, m_nRecordBuffer);
// 	xml_GetAttibuteValue(g_pszKeyAttrBuffer, oNode, m_nAttrBuffer);
// 	xml_GetAttibuteValue(g_pszKeyAttrTimeGap, oNode, m_nAttrTimeGap);
// 	xml_GetAttibuteValue(g_pszKeyRecordGap, oNode, m_nRecordGap);
// 	
// 	if (m_nRecordGap <= 0)
// 	{
// 		m_nRecordGap = 1;
// 	}
// 
// 	if (m_nRecordGap >= 100)
// 	{
// 		m_nRecordGap = 100;
// 	}
// 	
// 	return 0;
// }
// 
// long CRtBufferConfig::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }
// 
// BOOL CRtBufferConfig::ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	ReadOwnXml(oNode);
// 
// 	return TRUE;
// }
// 
// BOOL CRtBufferConfig::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oRtBuffer;
// 	oRtBuffer = oXMLDoc->createElement(_bstr_t(g_pszKeyRtBuffer));
// 
// 	oRtBuffer->setAttribute(_bstr_t(g_pszKeyMaxBuffer), m_nMaxBuffer);
// 	oRtBuffer->setAttribute(_bstr_t(g_pszKeySpyBuffer), m_nSpyBuffer);
// 	oRtBuffer->setAttribute(_bstr_t(g_pszKeyRecordBuffer), m_nRecordBuffer);
// 	oRtBuffer->setAttribute(_bstr_t(g_pszKeyAttrBuffer), m_nAttrBuffer);
// 	oRtBuffer->setAttribute(_bstr_t(g_pszKeyAttrTimeGap), m_nAttrTimeGap);
// 	oRtBuffer->setAttribute(_bstr_t(g_pszKeyRecordGap), m_nRecordGap);
// 
// 	oParent->appendChild(oRtBuffer);
// 	
// 	return TRUE;
// }
