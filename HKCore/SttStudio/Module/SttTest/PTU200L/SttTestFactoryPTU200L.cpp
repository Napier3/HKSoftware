#include "StdAfx.h"
#include "SttTestFactoryPTU200L.h"
#include "../common/SttUpdateFPGA.h"

#ifdef _PSX_IDE_QT_
	#include "../../SttTest/Common/SttStateTest.h"
	#include "../../SttTest/Common/SttGradientTest.h"
	#include "../../SttTest/Common/SttGradientMaxAngleTest.h"
	#include "../../SttTest/Common/SttURampTest.h"
	#include "../../SttTest/Common/SttIRampTest.h"
	#include "../../SttTest/Common/SttManuTest.h"
	#include "../../SttTest/Common/SttHarmTest.h"
	#include "../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
	#include "../../SttTest/Common/Adjust/SttAdjust_BinaryOutput.h"
	#include "../../SttTest/Common/Adjust/SttAdjust_BinaryExOutput.h"
	#include "../../SttTest/Common/Adjust/SttAdjust_RegisterTest.h"
	#include "../../SttTest/Common/Replay/LongTime/SttReplayTest.h"
	#include "../../SttTest/Common/SttChMapsConfig.h"
	#include "../../SttTest/Common/SttSoeTest.h"
	#include"../../SttTest/Common/SttModulesGearSwitch.h"
	#include"../../SttTest/PTU200L/SttPTTest.h"
#endif

int CSttTestFactoryPTU200L::g_nTestFactoryPTU200LRef = 0;
CSttTestFactoryPTU200L *CSttTestFactoryPTU200L::g_pTestFactoryPTU200L = NULL;

CSttTestFactoryPTU200L::CSttTestFactoryPTU200L()
{
	RegisterTestMacro(m_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttGradientTest::m_strMacroName, CSttGradientTest::m_strMacroID, CSttGradientTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttPtTest::m_strMacroName, CSttPtTest::m_strMacroID, CSttPtTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttReplayTest::m_strMacroName, CSttReplayTest::m_strMacroID, CSttReplayTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttSoeTest::m_strMacroName, CSttSoeTest::m_strMacroID, CSttSoeTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttModulesGearSwitch::m_strMacroName, CSttModulesGearSwitch::m_strMacroID, CSttModulesGearSwitch::CreateTest);

	//兼容之前深瑞安卓的模板
	RegisterTestMacro(m_strPxAppID_Relay, CSttStateTest::m_strMacroName, _T("SttStateTest"), CSttStateTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttReplayTest::m_strMacroName, _T("SttReplayTest"), CSttReplayTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttManuTest::m_strMacroName, _T("SttManuTest"), CSttManuTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttHarmTest::m_strMacroName, _T("SttHarmTest"), CSttHarmTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttSoeTest::m_strMacroName, _T("SttSoeTest"), CSttSoeTest::CreateTest);

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
