#include "StdAfx.h"
#include "SttTestFactoryRelayTest.h"

#ifdef _PSX_IDE_QT_
#include"SttStateTest.h"
#include"Iec61850Config.h"
#include"SttGradientTest.h"
#include"SttManuTest.h"
#include "SttHarmTest.h"
#include "SttAbnormalTest.h"
#include "SttShakeTest.h"
#include "SttRecord.h"
//#include "SttReplayTest.h"
#include "SttTimeMeasureTest.h"
#include "SttStep6U6I.h"
#include "SttIecDetectTest.h"
#include "SttIEDTest.h"
#endif

#include "SttReplayTest.h"

int CSttTestFactoryRelayTest::g_nTestFactoryRelayTestRef = 0;
CSttTestFactoryRelayTest *CSttTestFactoryRelayTest::g_pTestFactoryRelayTest = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryRelayTest::CSttTestFactoryRelayTest()
{  
#ifdef _PSX_IDE_QT_
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CIec61850Config::m_strMacroName, CIec61850Config::m_strMacroID, CIec61850Config::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttGradientTest::m_strMacroName, CSttGradientTest::m_strMacroID, CSttGradientTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAbnormalTest::m_strMacroName, CSttAbnormalTest::m_strMacroID, CSttAbnormalTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttShakeTest::m_strMacroName, CSttShakeTest::m_strMacroID, CSttShakeTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttRecord::m_strMacroName, CSttRecord::m_strMacroID, CSttRecord::CreateTest);
	//RegisterTestMacro(g_strPxAppID_Relay, CSttReplayTest::m_strMacroName, CSttReplayTest::m_strMacroID, CSttReplayTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttTimeMeasureTest::m_strMacroName, CSttTimeMeasureTest::m_strMacroID, CSttTimeMeasureTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttStep6U6I::m_strMacroName, CSttStep6U6I::m_strMacroID, CSttStep6U6I::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttIecDetectTest::m_strMacroName, CSttIecDetectTest::m_strMacroID, CSttIecDetectTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttIEDTest::m_strMacroName, CSttIEDTest::m_strMacroID, CSttIEDTest::CreateTest);
#endif

	RegisterTestMacro(g_strPxAppID_Relay, CSttReplayTest::m_strMacroName, CSttReplayTest::m_strMacroID, CSttReplayTest::CreateTest);
}

CSttTestFactoryRelayTest::~CSttTestFactoryRelayTest()
{
	
}

CSttTestFactoryRelayTest *CSttTestFactoryRelayTest::Create()
{
    g_nTestFactoryRelayTestRef++;

    if (g_nTestFactoryRelayTestRef == 1)
	{
        g_pTestFactoryRelayTest = new CSttTestFactoryRelayTest;
        g_pSttTestFactory = g_pTestFactoryRelayTest;

        //CXLanguage oXLanguage;
        //oXLanguage.xlang_Buid(g_pTestFactory);
        //xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
    }

    return g_pTestFactoryRelayTest;
}

void CSttTestFactoryRelayTest::Release()
{
    g_nTestFactoryRelayTestRef--;

    if (g_nTestFactoryRelayTestRef == 0)
	{
        delete g_pTestFactoryRelayTest;
        g_pTestFactoryRelayTest = NULL;
	}
}
