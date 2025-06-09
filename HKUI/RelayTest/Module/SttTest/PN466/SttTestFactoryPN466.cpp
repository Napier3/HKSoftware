#include "StdAfx.h"
#include "SttTestFactoryPN466.h"
#include "../common/SttUpdateFPGA.h"
#include "../common/SttBinMeasure.h"
#include "../common/SttBinConfig.h"
#include "../common/SttDcMeasCfg.h"
#include "../Common/Replay/Pcap/SttPcapReplay.h"
#include "../Common/Async/SttAsyncManuTest.h"
#include "../Common/Async/SttAsyncStateTest.h"

int CSttTestFactoryPN466::g_nTestFactoryPN466Ref = 0;
CSttTestFactoryPN466 *CSttTestFactoryPN466::g_pTestFactoryPN466 = NULL;

CSttTestFactoryPN466::CSttTestFactoryPN466()
{
    RegisterInit();
    RegisterTestMacro(m_strPxAppID_Relay, CSttUpdateFPGA::m_strMacroName, CSttUpdateFPGA::m_strMacroID, CSttUpdateFPGA::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttBinMeasure::m_strMacroName, CSttBinMeasure::m_strMacroID, CSttBinMeasure::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttBinConfig::m_strMacroName, CSttBinConfig::m_strMacroID, CSttBinConfig::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttDcMeasCfg::m_strMacroName, CSttDcMeasCfg::m_strMacroID, CSttDcMeasCfg::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttPcapReplay::m_strMacroName, CSttPcapReplay::m_strMacroID, CSttPcapReplay::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttAsyncManuTest::m_strMacroName, CSttAsyncManuTest::m_strMacroID, CSttAsyncManuTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttAsyncStateTest::m_strMacroName, CSttAsyncStateTest::m_strMacroID, CSttAsyncStateTest::CreateTest);
}

CSttTestFactoryPN466::~CSttTestFactoryPN466()
{
}

CSttTestFactoryPN466 *CSttTestFactoryPN466::Create()
{
    g_nTestFactoryPN466Ref++;

    if(g_nTestFactoryPN466Ref == 1)
    {
        g_pTestFactoryPN466 = new CSttTestFactoryPN466;
        g_pSttTestFactory = g_pTestFactoryPN466;
        //CXLanguage oXLanguage;
        //oXLanguage.xlang_Buid(g_pTestFactory);
        //xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
    }

    return g_pTestFactoryPN466;
}

void CSttTestFactoryPN466::Release()
{
    g_nTestFactoryPN466Ref--;

    if(g_nTestFactoryPN466Ref == 0)
    {
        delete g_pTestFactoryPN466;
        g_pTestFactoryPN466 = NULL;
    }
}
