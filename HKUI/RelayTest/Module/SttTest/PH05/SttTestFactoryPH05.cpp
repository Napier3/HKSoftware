#include "StdAfx.h"
#include "SttTestFactoryPH05.h"

#ifdef _PSX_IDE_QT_

#include "../../SttTest/Common/SttManuTest.h"
#include "../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include "../../SttTest/Common/Adjust/SttAdjust_BinaryOutput.h"
#include "../../SttTest/PH05/Replay/SttReplayTest.h"
#include "../../SttTest/Common/Iec61850Config.h"
#include "../../SttTest/Common/SttChMapsConfig.h"

#endif

int CSttTestFactoryPH05::g_nTestFactoryPH05Ref = 0;
CSttTestFactoryPH05 *CSttTestFactoryPH05::g_pTestFactoryPH05 = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPH05::CSttTestFactoryPH05()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CIec61850Config::m_strMacroName, CIec61850Config::m_strMacroID, CIec61850Config::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);

    RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);//"ManualTest"
    RegisterTestMacro(g_strPxAppID_Relay, CSttReplayTest::m_strMacroName, CSttReplayTest::m_strMacroID, CSttReplayTest::CreateTest);//"ReplayTest"
}

CSttTestFactoryPH05::~CSttTestFactoryPH05()
{
	
}

CSttTestFactoryPH05 *CSttTestFactoryPH05::Create()
{
    g_nTestFactoryPH05Ref++;

    if (g_nTestFactoryPH05Ref == 1)
	{
        g_pTestFactoryPH05 = new CSttTestFactoryPH05;
        g_pSttTestFactory = g_pTestFactoryPH05;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

    return g_pTestFactoryPH05;
}

void CSttTestFactoryPH05::Release()
{
    g_nTestFactoryPH05Ref--;

    if (g_nTestFactoryPH05Ref == 0)
	{
        delete g_pTestFactoryPH05;
        g_pTestFactoryPH05 = NULL;
	}
}
