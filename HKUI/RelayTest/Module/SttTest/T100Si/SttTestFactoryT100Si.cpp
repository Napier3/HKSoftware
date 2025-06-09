#include "StdAfx.h"
#include "SttTestFactoryT100Si.h"

#ifdef _PSX_IDE_QT_
#include "../../SttTest/Common/SttStateTest.h"
#include "../../SttTest/Common/SttGradientTest.h"
#include "../../SttTest/Common/SttManuTest.h"
#include "../../SttTest/Common/SttHarmTest.h"
#include "../../SttTest/Common/SttAdjust_ModuleOutput.h"
#include "../../SttTest/Common/SttAdjust_BinaryOutput.h"
#include "../../SttTest/Common/SttChMapsConfig.h"
#endif

int CSttTestFactoryT100Si::g_nTestFactoryT100SiRef = 0;
CSttTestFactoryT100Si *CSttTestFactoryT100Si::g_pTestFactoryT100Si = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryT100Si::CSttTestFactoryT100Si()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttGradientTest::m_strMacroName, CSttGradientTest::m_strMacroID, CSttGradientTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);
}

CSttTestFactoryT100Si::~CSttTestFactoryT100Si()
{
	
}

CSttTestFactoryT100Si *CSttTestFactoryT100Si::Create()
{
	g_nTestFactoryT100SiRef++;

	if (g_nTestFactoryT100SiRef == 1)
	{
		g_pTestFactoryT100Si = new CSttTestFactoryT100Si;
		g_pSttTestFactory = g_pTestFactoryT100Si;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryT100Si;
}

void CSttTestFactoryT100Si::Release()
{
	g_nTestFactoryT100SiRef--;

	if (g_nTestFactoryT100SiRef == 0)
	{
		delete g_pTestFactoryT100Si;
		g_pTestFactoryT100Si = NULL;
	}
}
