#include "StdAfx.h"
#include "SttTestFactoryPTU300B.h"

#ifdef _PSX_IDE_QT_
#include "../../SttTest/Common/SttStateTest.h"
#include "../../SttTest/Common/SttManuTest.h"
#include "../../SttTest/Common/SttHarmTest.h"
#include "../../SttTest/Common/SttAdjust_ModuleOutput.h"
#include "../../SttTest/Common/SttAdjust_BinaryOutput.h"
#endif

int CSttTestFactoryPTU300B::g_nTestFactoryPTU300BRef = 0;
CSttTestFactoryPTU300B *CSttTestFactoryPTU300B::g_pTestFactoryPTU300B = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPTU300B::CSttTestFactoryPTU300B()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);
}

CSttTestFactoryPTU300B::~CSttTestFactoryPTU300B()
{
	
}

CSttTestFactoryPTU300B *CSttTestFactoryPTU300B::Create()
{
	g_nTestFactoryPTU300BRef++;

	if (g_nTestFactoryPTU300BRef == 1)
	{
		g_pTestFactoryPTU300B = new CSttTestFactoryPTU300B;
		g_pSttTestFactory = g_pTestFactoryPTU300B;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryPTU300B;
}

void CSttTestFactoryPTU300B::Release()
{
	g_nTestFactoryPTU300BRef--;

	if (g_nTestFactoryPTU300BRef == 0)
	{
		delete g_pTestFactoryPTU300B;
		g_pTestFactoryPTU300B = NULL;
	}
}
