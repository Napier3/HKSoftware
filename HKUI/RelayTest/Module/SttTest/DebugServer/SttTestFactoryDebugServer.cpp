#include "StdAfx.h"
#include "SttTestFactoryDebugServer.h"

#include "../Common/SttStateTest.h"
//#include "../Common/SttGradientTest.h"
//#include "../Common/SttManuTest.h"
//#include "../Common/SttHarmTest.h"
//#include "../Common/SttAdjust_ModuleOutput.h"
//#include "../Common/SttAdjust_BinaryOutput.h"
//#include "../PTU200L/SttPTTest.h"

int CSttTestFactoryDebugServer::g_nTestFactoryDebugServerRef = 0;
CSttTestFactoryDebugServer *CSttTestFactoryDebugServer::g_pTestFactoryDebugServer = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "继保测试仪";


CSttTestFactoryDebugServer::CSttTestFactoryDebugServer()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	//RegisterTestMacro(g_strPxAppID_Relay, CSttGradientTest::m_strMacroName, CSttGradientTest::m_strMacroID, CSttGradientTest::CreateTest);
	//RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	//RegisterTestMacro(g_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);
	//RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	//RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);
	//RegisterTestMacro(g_strPxAppID_Relay, CSttPtTest::m_strMacroName, CSttPtTest::m_strMacroID, CSttPtTest::CreateTest);
}

CSttTestFactoryDebugServer::~CSttTestFactoryDebugServer()
{
	
}

CSttTestFactoryDebugServer *CSttTestFactoryDebugServer::Create()
{
	g_nTestFactoryDebugServerRef++;

	if (g_nTestFactoryDebugServerRef == 1)
	{
		g_pTestFactoryDebugServer = new CSttTestFactoryDebugServer;
		g_pSttTestFactory = g_pTestFactoryDebugServer;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryDebugServer;
}

void CSttTestFactoryDebugServer::Release()
{
	g_nTestFactoryDebugServerRef--;

	if (g_nTestFactoryDebugServerRef == 0)
	{
		delete g_pTestFactoryDebugServer;
		g_pTestFactoryDebugServer = NULL;
	}
}
