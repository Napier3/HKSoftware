#include "stdafx.h"
#include "StationTestMainConfig.h"
#include "../AutoTestXMLRWKeys.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CStationTestMainConfig *CStationTestMainConfig::g_pStationTestMainConfig = NULL;
long CStationTestMainConfig::g_nStationTestMainConfig = 0;

CStationTestMainConfig* CStationTestMainConfig::Create()
{
	g_nStationTestMainConfig++;

	if (g_nStationTestMainConfig == 1)
	{
		g_pStationTestMainConfig = new CStationTestMainConfig();
		g_pStationTestMainConfig->Open();
	}

	return g_pStationTestMainConfig;
}

void CStationTestMainConfig::Release()
{
	g_nStationTestMainConfig--;

	if (g_nStationTestMainConfig == 0)
	{
		delete g_pStationTestMainConfig;
		g_pStationTestMainConfig = NULL;
	}
}

CTestWzdDefines* CStationTestMainConfig::GetCTestWzdDefines()
{
	ASSERT (g_pStationTestMainConfig != NULL);
	ASSERT (g_pStationTestMainConfig->m_pTestWzdDefines != NULL);

	return g_pStationTestMainConfig->m_pTestWzdDefines;
}

void CStationTestMainConfig::SaveConfigFile()
{
	ASSERT (g_pStationTestMainConfig != NULL);
	g_pStationTestMainConfig->Save();
}

CStationTestMainConfig::CStationTestMainConfig()
{
	m_pTestWzdDefines = NULL;
}

CStationTestMainConfig::~CStationTestMainConfig()
{

}

void CStationTestMainConfig::Init()
{

}


void CStationTestMainConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTWZDDEFINES)
		{
			m_pTestWzdDefines = (CTestWzdDefines*)p;
		}
	}
}

CExBaseObject* CStationTestMainConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCTestWzdDefinesKey)
	{
		CTestWzdDefines* pTestWzdDefines = new CTestWzdDefines;
		return pTestWzdDefines;
	}

	return NULL;
}

CExBaseObject* CStationTestMainConfig::CreateNewChild(long nClassID)
{
	return NULL;
}

CString CStationTestMainConfig::GetStationTestMainConfigFile()
{
	CString strFile;

	strFile = _P_GetConfigPath();
	strFile += _T("StationTestMainConfig.xml");

	return strFile;
}

BOOL CStationTestMainConfig::Open()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	CString strFile = GetStationTestMainConfigFile();
	BOOL bTrue = FALSE;

	bTrue = OpenXmlFile(strFile, CAutoTestXMLRWKeys::CStationTestMainConfigKey(), CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
	
	if (!bTrue)
	{
		bTrue = Save();
	}

	return bTrue;
}

BOOL CStationTestMainConfig::Save()
{
	CString strFile = GetStationTestMainConfigFile();

	SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return TRUE;
}

