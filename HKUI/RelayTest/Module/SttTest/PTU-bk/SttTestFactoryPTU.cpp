#include "StdAfx.h"
#include "SttTestFactoryPTU.h"


#include"SttManuTest.h"
#include "SttStateTest.h"
#include "SttHarmTest.h"
#include "SttSoeTest.h"
#include "SttPTTest.h"


int CSttTestFactoryPTU::g_nTestFactoryPTURef = 0;
CSttTestFactoryPTU *CSttTestFactoryPTU::g_pTestFactoryPTU = NULL;

static const CString g_strPxAppID_Relay = "ptu";
static const CString g_strPxAppName_Relay = "≈‰µÁ÷’∂À≤‚ ‘“«";


CSttTestFactoryPTU::CSttTestFactoryPTU()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttSoeTest::m_strMacroName, CSttSoeTest::m_strMacroID, CSttSoeTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttPtTest::m_strMacroName, CSttPtTest::m_strMacroID, CSttPtTest::CreateTest);
}

CSttTestFactoryPTU::~CSttTestFactoryPTU()
{
	
}

CSttTestFactoryPTU *CSttTestFactoryPTU::Create()
{
	g_nTestFactoryPTURef++;

	if (g_nTestFactoryPTURef == 1)
	{
		g_pTestFactoryPTU = new CSttTestFactoryPTU;
		g_pSttTestFactory = g_pTestFactoryPTU;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryPTU;
}

void CSttTestFactoryPTU::Release()
{
	g_nTestFactoryPTURef--;

	if (g_nTestFactoryPTURef == 0)
	{
		delete g_pTestFactoryPTU;
		g_pTestFactoryPTU = NULL;
	}
}
