// SystemSetsConfig.cpp: implementation of the CSystemSetsConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemSetsConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char* CSystemSetsConfig::g_pszKeySystemSetsConfig = "systemsetsconfig";
const char* CSystemSetsConfig::g_pszKeyTotalTime		= "total-record-time";
const char* CSystemSetsConfig::g_pszKeyLookBackTime		= "time-look-back";
const char* CSystemSetsConfig::g_pszKeyRecordGap		= "record-gap";
const char* CSystemSetsConfig::g_pszKeyChannelUse		= "chan-use";

const char* CSystemSetsConfig::g_pszKeySystemSetsConfigFile = "SystemsetsConfig.xml";

CSystemSetsConfig::CSystemSetsConfig()
{
	m_dTotalRecordTime  = 10;
	m_dLookBackTime		= 0.04;
	m_nRecordGap		= 1;
	m_nChannelUse		= 1;
	
	//CString strSetsConfig;
	//strSetsConfig.Format("%s%s",_P_GetConfigPath(),CSystemSetsConfig::g_pszKeySystemSetsConfigFile);
	//ReadSystemSetsConfigFromFile(strSetsConfig);
}

CSystemSetsConfig::~CSystemSetsConfig()
{

}
// 
// long CSystemSetsConfig::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CExBaseObject::ReadOwnXml(oNode);
// 
// 	xml_GetAttibuteValue(g_pszKeyTotalTime, oNode, m_dTotalRecordTime);
// 	xml_GetAttibuteValue(g_pszKeyLookBackTime, oNode, m_dLookBackTime);
// 	xml_GetAttibuteValue(g_pszKeyRecordGap, oNode, m_nRecordGap);
// 	xml_GetAttibuteValue(g_pszKeyChannelUse, oNode, m_nChannelUse);
// 
// 	return 0;
// }
// 
// CExBaseObject* CSystemSetsConfig::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CExBaseObject* pNew = NULL;
// 	
// 	if (_stricmp(pszClassID, CSystemSetAttr::g_pszKeySystemSetsAttr) == 0)
// 	{
// 		pNew = new CSystemSetAttr();
// 	}
// 
// 	return pNew;
// }
// 
// BOOL CSystemSetsConfig::ReadSystemSetsConfigFromFile(const CString &strFile)
// {
// 	MSXML::IXMLDOMDocumentPtr oDoc = NULL;
// 	HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML::DOMDocument));
// 	
// 	if(!SUCCEEDED(hr)) 
// 	{ 
// 		return FALSE;
// 	} 
// 	
// 	MSXML::IXMLDOMNodePtr oSystemSetsConfig = NULL;
// 	BSTR bstrFile = strFile.AllocSysString();
// 	BOOL bTrue = oDoc->load(bstrFile);
// 	::SysFreeString(bstrFile);
// 	
// 	if (!bTrue)
// 	{
// 		TRACE("\nRead SystemSets file failed......\n");
// 	}
// 	
// 	oSystemSetsConfig = oDoc->selectSingleNode(_bstr_t(g_pszKeySystemSetsConfig));
// 	
// 	if (oSystemSetsConfig == NULL)
// 	{
// 		return FALSE;
// 	}
// 	
// 	
// 	ReadXml(oSystemSetsConfig);
// 
// 	return TRUE;
// }

CSystemSetAttr* CSystemSetsConfig::FindSystemSetAttrByID(const CString& strID)
{
	CSystemSetAttr* pFind = NULL;

	pFind = (CSystemSetAttr*)FindByID(strID);

	return pFind;
}