#include "StdAfx.h"
#include "SttTestFactoryPTU.h"

#ifdef _PSX_IDE_QT_
#include "../../SttTest/Common/SttStateTest.h"
#include "../../SttTest/Common/SttGradientTest.h"
#include "../../SttTest/Common/SttURampTest.h"
#include "../../SttTest/Common/SttIRampTest.h"
#include "../../SttTest/Common/SttManuTest.h"
#include "../../SttTest/Common/SttHarmTest.h"
#include "../../SttTest/Common/SttAdjust_ModuleOutput.h"
#include "../../SttTest/Common/SttAdjust_BinaryOutput.h"
#include "../../SttTest/Common/SttReplayTest.h"
#include "../../SttTest/Common/SttChMapsConfig.h"
#endif

int CSttTestFactoryPTU::g_nTestFactoryPTURef = 0;
CSttTestFactoryPTU *CSttTestFactoryPTU::g_pTestFactoryPTU = NULL;

static const CString g_strPxAppID_Relay = "ptu";
static const CString g_strPxAppName_Relay = "≈‰Õ¯≤‚ ‘“«";


CSttTestFactoryPTU::CSttTestFactoryPTU()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);

	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttGradientTest::m_strMacroName, CSttGradientTest::m_strMacroID, CSttGradientTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttURampTest::m_strMacroName, CSttURampTest::m_strMacroID, CSttURampTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttIRampTest::m_strMacroName, CSttIRampTest::m_strMacroID, CSttIRampTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);
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
