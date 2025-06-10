#include "StdAfx.h"
#include "SttTestFactoryPNI302.h"

#include"../Common/Iec61850Config.h"
#include "../Common/SttRecord.h"
#include "../Common/SttAdjust_ModuleOutput.h"
#include "../PNI302/SttStep6U6I.h"
#include "../PNI302/SttIecDetectTest.h"
#include "../PNI302/Stt_GSEtoBin_Test.h"
#include "../PNI302/Stt_BotoGSE_Test.h"
#include "../PNI302/SttMUTimeTest.h"


int CSttTestFactoryPNI302::g_nTestFactoryPNI302Ref = 0;
CSttTestFactoryPNI302 *CSttTestFactoryPNI302::g_pTestFactoryPNI302 = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPNI302::CSttTestFactoryPNI302()
{
	RegisterTestMacro(g_strPxAppID_Relay, CIec61850Config::m_strMacroName, CIec61850Config::m_strMacroID, CIec61850Config::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttStep6U6I::m_strMacroName, CSttStep6U6I::m_strMacroID, CSttStep6U6I::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttIecDetectTest::m_strMacroName, CSttIecDetectTest::m_strMacroID, CSttIecDetectTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttGSEtoBinTest::m_strMacroName, CSttGSEtoBinTest::m_strMacroID, CSttGSEtoBinTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttBOtoGSETest::m_strMacroName, CSttBOtoGSETest::m_strMacroID, CSttBOtoGSETest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttMUTimeTest::m_strMacroName, CSttMUTimeTest::m_strMacroID, CSttMUTimeTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
}

CSttTestFactoryPNI302::~CSttTestFactoryPNI302()
{

}

CSttTestFactoryPNI302 *CSttTestFactoryPNI302::Create()
{
	g_nTestFactoryPNI302Ref++;

	if (g_nTestFactoryPNI302Ref == 1)
	{
		g_pTestFactoryPNI302 = new CSttTestFactoryPNI302;
		g_pSttTestFactory = g_pTestFactoryPNI302;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryPNI302;
}

void CSttTestFactoryPNI302::Release()
{
	g_nTestFactoryPNI302Ref--;

	if (g_nTestFactoryPNI302Ref == 0)
	{
		delete g_pTestFactoryPNI302;
		g_pTestFactoryPNI302 = NULL;
	}
}
