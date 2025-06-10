#include "StdAfx.h"
#include "SttTestFactoryPTU200L.h"

#ifdef _PSX_IDE_QT_
#include "../../SttTest/Common/SttStateTest.h"
#include "../../SttTest/Common/SttGradientTest.h"
#include "../../SttTest/Common/SttManuTest.h"
#include "../../SttTest/Common/SttHarmTest.h"
#include "../../SttTest/Common/SttAdjust_ModuleOutput.h"
#include "../../SttTest/Common/SttAdjust_BinaryOutput.h"
#include "../../SttTest/PTU200L/SttPTTest.h"
#endif

int CSttTestFactoryPTU200L::g_nTestFactoryPTU200LRef = 0;
CSttTestFactoryPTU200L *CSttTestFactoryPTU200L::g_pTestFactoryPTU200L = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPTU200L::CSttTestFactoryPTU200L()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttGradientTest::m_strMacroName, CSttGradientTest::m_strMacroID, CSttGradientTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttPtTest::m_strMacroName, CSttPtTest::m_strMacroID, CSttPtTest::CreateTest);
}

CSttTestFactoryPTU200L::~CSttTestFactoryPTU200L()
{
	
}

CSttTestFactoryPTU200L *CSttTestFactoryPTU200L::Create()
{
	g_nTestFactoryPTU200LRef++;

	if (g_nTestFactoryPTU200LRef == 1)
	{
		g_pTestFactoryPTU200L = new CSttTestFactoryPTU200L;
		g_pSttTestFactory = g_pTestFactoryPTU200L;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryPTU200L;
}

void CSttTestFactoryPTU200L::Release()
{
	g_nTestFactoryPTU200LRef--;

	if (g_nTestFactoryPTU200LRef == 0)
	{
		delete g_pTestFactoryPTU200L;
		g_pTestFactoryPTU200L = NULL;
	}
}
