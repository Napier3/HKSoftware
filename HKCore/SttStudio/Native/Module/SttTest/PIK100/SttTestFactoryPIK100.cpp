#include "stdafx.h"
#include "SttTestFactoryPIK100.h"


#ifdef _PSX_IDE_QT_
#include"SttPIK100Test.h"
#endif

int CSttTestFactoryPIK100::g_nTestFactoryPIK100Ref = 0;
CSttTestFactoryPIK100 *CSttTestFactoryPIK100::g_pTestFactoryPIK100 = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPIK100::CSttTestFactoryPIK100()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttPik100Test::m_strMacroName, CSttPik100Test::m_strMacroID, CSttPik100Test::CreateTest);
}

CSttTestFactoryPIK100::~CSttTestFactoryPIK100()
{
	
}

CSttTestFactoryPIK100 *CSttTestFactoryPIK100::Create()
{
	g_nTestFactoryPIK100Ref++;

	if (g_nTestFactoryPIK100Ref == 1)
	{
		g_pTestFactoryPIK100 = new CSttTestFactoryPIK100;
		g_pSttTestFactory = g_pTestFactoryPIK100;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryPIK100;
}

void CSttTestFactoryPIK100::Release()
{
	g_nTestFactoryPIK100Ref--;

	if (g_nTestFactoryPIK100Ref == 0)
	{
		delete g_pTestFactoryPIK100;
		g_pTestFactoryPIK100 = NULL;
	}
}
