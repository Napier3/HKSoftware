#include "StdAfx.h"
#include "SttTestFactoryPFC6A.h"

#ifdef _PSX_IDE_QT_
#include "../../SttTest/Common/SttChMapsConfig.h"
#include "../../SttTest/Common/SttStateTest.h"
#include "../../SttTest/Common/SttManuTest.h"
#include "../../SttTest/Common/SttHarmTest.h"
#include "../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include "../../SttTest/Common/Adjust/SttAdjust_BinaryOutput.h"
#endif

int CSttTestFactoryPFC6A::g_nTestFactoryPFC6ARef = 0;
CSttTestFactoryPFC6A *CSttTestFactoryPFC6A::g_pTestFactoryPFC6A = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPFC6A::CSttTestFactoryPFC6A()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);

	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, _T("SttStateTest"), CSttStateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName,  _T("SttManuTest"), CSttManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttHarmTest::m_strMacroName,  _T("SttHarmTest"), CSttHarmTest::CreateTest);
}

CSttTestFactoryPFC6A::~CSttTestFactoryPFC6A()
{
	
}

CSttTestFactoryPFC6A *CSttTestFactoryPFC6A::Create()
{
	g_nTestFactoryPFC6ARef++;

	if (g_nTestFactoryPFC6ARef == 1)
	{
		g_pTestFactoryPFC6A = new CSttTestFactoryPFC6A;
		g_pSttTestFactory = g_pTestFactoryPFC6A;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryPFC6A;
}

void CSttTestFactoryPFC6A::Release()
{
	g_nTestFactoryPFC6ARef--;

	if (g_nTestFactoryPFC6ARef == 0)
	{
		delete g_pTestFactoryPFC6A;
		g_pTestFactoryPFC6A = NULL;
	}
}
