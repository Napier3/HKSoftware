#include "stdafx.h"
#include "SttTestFactoryPIS2K.h"


#ifdef _PSX_IDE_QT_
#include"SttPIS2KTest.h"
#include "Adjust/SttAdjust_ModuleOutput.h"
#endif

int CSttTestFactoryPIS2K::g_nTestFactoryPIS2KRef = 0;
CSttTestFactoryPIS2K *CSttTestFactoryPIS2K::g_pTestFactoryPIS2K = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPIS2K::CSttTestFactoryPIS2K()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttPis2kTest::m_strMacroName, CSttPis2kTest::m_strMacroID, CSttPis2kTest::CreateTest);
}

CSttTestFactoryPIS2K::~CSttTestFactoryPIS2K()
{
	
}

CSttTestFactoryPIS2K *CSttTestFactoryPIS2K::Create()
{
	g_nTestFactoryPIS2KRef++;

	if (g_nTestFactoryPIS2KRef == 1)
	{
		g_pTestFactoryPIS2K = new CSttTestFactoryPIS2K;
		g_pSttTestFactory = g_pTestFactoryPIS2K;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryPIS2K;
}

void CSttTestFactoryPIS2K::Release()
{
	g_nTestFactoryPIS2KRef--;

	if (g_nTestFactoryPIS2KRef == 0)
	{
		delete g_pTestFactoryPIS2K;
		g_pTestFactoryPIS2K = NULL;
	}
}
