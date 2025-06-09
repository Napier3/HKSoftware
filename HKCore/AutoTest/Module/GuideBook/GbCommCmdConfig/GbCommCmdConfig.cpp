#include "stdafx.h"
#include "GbCommCmdConfig.h"
#include "../../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// long CGbCommCmdConfig::g_nGbCommCmdConfig = 0;
// CGbCommCmdConfig* CGbCommCmdConfig::g_pGbCommCmdConfig = NULL;

const CString CGbCommCmdConfig::g_strCommCmdConfigFile = _T("CommCmdConfig.xml");

CGbCommCmdConfig::CGbCommCmdConfig()
{
	
}

CGbCommCmdConfig::~CGbCommCmdConfig()
{

}
// 
// CGbCommCmdConfig* CGbCommCmdConfig::CreateGbCommCmdConfig()
// {
// 	g_nGbCommCmdConfig ++ ;
// 
// 	if(g_nGbCommCmdConfig == 1)
// 	{
// 		g_pGbCommCmdConfig = new CGbCommCmdConfig();
// 	}
// 
// 	return g_pGbCommCmdConfig;
// }
// 
// void CGbCommCmdConfig::Release()
// {
// 	g_nGbCommCmdConfig --;
// 
// 	if(g_nGbCommCmdConfig == 0)
// 	{
// 		delete g_pGbCommCmdConfig;
// 		g_pGbCommCmdConfig = NULL;
// 	}
// }

long CGbCommCmdConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CGbCommCmdConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

CExBaseObject* CGbCommCmdConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strCmdKey)
	{
		return new CGbCommCmd();
	}

	if(strClassID == CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strCmdExKey)
	{
		return new CGbCommCmdMms();
	}

	return NULL;
}

BOOL CGbCommCmdConfig::SaveXMLFile()
{
	return NULL;
}

BOOL CGbCommCmdConfig::OpenXmlFile(const CString &strFile)
{
	CCommCmdConfigXMLKeys::CreateConfigXMLKeys();

	CString strFileTemp;
    strFileTemp = _P_GetConfigPath();
    strFileTemp += strFile;

	DeleteAll();
	BOOL b = CBaseObject::OpenXmlFile(strFileTemp, CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strCommCmdConfigKey, CCommCmdConfigXMLKeys::g_pConfigXMLKeys);

	CCommCmdConfigXMLKeys::Release();
	
	//xlang_TranslateByResourceFile(this, strFile);
	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
    xlang_TranslateByResourceFileEx(this, strFile);
#endif

	return b;
}

CGbCommCmdMms* CGbCommCmdConfig::FindCmd_Read(const CString &strDsID)
{
	CGbCommCmdMms *pCmd = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCmd = (CGbCommCmdMms *)GetNext(pos);

		if (pCmd->m_strGbDataID == strDsID && pCmd->IsRead())
		{
			pFind = pCmd;
			break;
		}
	}

	return pFind;
}


CGbCommCmdMms* CGbCommCmdConfig::FindCmd_Write(const CString &strDsID)
{
	CGbCommCmdMms *pCmd = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCmd = (CGbCommCmdMms *)GetNext(pos);

		if (pCmd->m_strGbDataID == strDsID && pCmd->IsWrite())
		{
			pFind = pCmd;
			break;
		}
	}

	return pFind;
}

