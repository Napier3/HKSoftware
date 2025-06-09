#include "stdafx.h"
#include "../../Module/api/GlobalConfigApi.h"
#include "../../Module/api/GloblaDrawFunctions.h"
#include "GbDevConfig.h"

#include "..\..\Module\UserDB\XUser.h"
#include "..\..\Module\Api\FileApi.h"


#define g_strGbDevConfigFile  _T("GbDevConfig.xml")


CGbDevConfig* CGbDevConfig::g_pGbDevConfig = NULL;
long CGbDevConfig::g_nGbDevConfigRef = 0;

#define WORD_PAGE_DIR_ID_HORZ     _T("horz")
#define WORD_PAGE_DIR_ID_VERT     _T("vert")
#define WORD_PAGE_DIR_INDEX_HORZ  1
#define WORD_PAGE_DIR_INDEX_VERT  0

CGbDevConfig* CGbDevConfig::Create()
{
	g_nGbDevConfigRef++;

	if (g_nGbDevConfigRef == 1)
	{
		CAutoTestXMLRWKeys::Create();
		g_pGbDevConfig = new CGbDevConfig();
		g_pGbDevConfig->Open();
	}

	return g_pGbDevConfig;
}

void CGbDevConfig::Release()
{
	g_nGbDevConfigRef--;

	if (g_nGbDevConfigRef == 0)
	{
		CAutoTestXMLRWKeys::Release();
		delete g_pGbDevConfig;
		g_pGbDevConfig = NULL;
	}
}

CGbDevConfig::CGbDevConfig()
{
	m_nWordPageOrientation = WORD_PAGE_DIR_INDEX_VERT;
	m_strWordPageOrientation = WORD_PAGE_DIR_ID_VERT;
	
}

CGbDevConfig::~CGbDevConfig()
{

}

long CGbDevConfig::Open()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	m_strFile = (CString)_P_GetConfigPath();
	m_strFile += g_strGbDevConfigFile;

	return OpenXmlFile(m_strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTCtrlCntrKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
}

long CGbDevConfig::Save()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	CString strFile = (CString)_P_GetConfigPath();
	strFile += g_strGbDevConfigFile;
	SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return 1;
}

long CGbDevConfig::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
//long CGbDevConfig::XmlRead(CXmlRWNodeBase &oElement,CXmlRWKeys *pXmlRWKeys)
{
	CAutoTestXMLRWKeys* pXmlKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;
	CString strValue;


	xml_GetElementText(pXmlKeys->m_strWordPageOrientationKey, oElement, m_strWordPageOrientation);

	if (m_strWordPageOrientation == WORD_PAGE_DIR_ID_VERT)
	{
		m_nWordPageOrientation = WORD_PAGE_DIR_INDEX_VERT;
	}
	else
	{
		m_nWordPageOrientation = WORD_PAGE_DIR_INDEX_HORZ;
	}

	return 0;
}

long CGbDevConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// long CGbDevConfig::XmlWrite(CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oElement,CXmlRWKeys *pXmlRWKeys)
{

	CAutoTestXMLRWKeys* pXmlKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;
	CString strValue;

	xml_SetElementText(pXmlKeys->m_strWordPageOrientationKey, oXMLDoc, oElement, m_strWordPageOrientation);

	return 0;
}

BOOL CGbDevConfig::IsWordPageDir_Horz()
{
	ASSERT (g_pGbDevConfig != NULL);

	return (g_pGbDevConfig->m_nWordPageOrientation == WORD_PAGE_DIR_INDEX_HORZ);
}

BOOL CGbDevConfig::IsWordPageDir_Vert()
{
	ASSERT (g_pGbDevConfig != NULL);

	return (g_pGbDevConfig->m_nWordPageOrientation == WORD_PAGE_DIR_INDEX_VERT);
}

void CGbDevConfig::SetWordPageDir_Horz()
{
	ASSERT (g_pGbDevConfig != NULL);

	g_pGbDevConfig->m_nWordPageOrientation   = WORD_PAGE_DIR_INDEX_HORZ;
	g_pGbDevConfig->m_strWordPageOrientation = WORD_PAGE_DIR_ID_HORZ;
}

void CGbDevConfig::SetWordPageDir_Vert()
{
	ASSERT (g_pGbDevConfig != NULL);

	g_pGbDevConfig->m_nWordPageOrientation   = WORD_PAGE_DIR_INDEX_VERT;
	g_pGbDevConfig->m_strWordPageOrientation = WORD_PAGE_DIR_ID_VERT;
}

