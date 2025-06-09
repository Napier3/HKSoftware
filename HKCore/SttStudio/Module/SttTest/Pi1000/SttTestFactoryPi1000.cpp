#include "StdAfx.h"
#include "SttTestFactoryPi1000.h"
#include "../common/SttUpdateFPGA.h"
#include "../Common/Replay/Pcap/SttPcapReplay.h"
#include "../Common/Async/SttAsyncManuTest.h"
#include "../Common/Async/SttAsyncStateTest.h"
#include "../PiExModule/PIP150/SttPIP150Test.h"

int CSttTestFactoryPi1000::g_nTestFactoryPi1000Ref = 0;
CSttTestFactoryPi1000 *CSttTestFactoryPi1000::g_pTestFactoryPi1000 = NULL;

CSttTestFactoryPi1000::CSttTestFactoryPi1000()
{
    RegisterInit();
    RegisterTestMacro(m_strPxAppID_Relay, CSttUpdateFPGA::m_strMacroName, CSttUpdateFPGA::m_strMacroID, CSttUpdateFPGA::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttPcapReplay::m_strMacroName, CSttPcapReplay::m_strMacroID, CSttPcapReplay::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttPIP150Test::m_strMacroName, CSttPIP150Test::m_strMacroID, CSttPIP150Test::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttAsyncManuTest::m_strMacroName, CSttAsyncManuTest::m_strMacroID, CSttAsyncManuTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttAsyncStateTest::m_strMacroName, CSttAsyncStateTest::m_strMacroID, CSttAsyncStateTest::CreateTest);
}

CSttTestFactoryPi1000::~CSttTestFactoryPi1000()
{
}

CSttTestFactoryPi1000 *CSttTestFactoryPi1000::Create()
{
	g_nTestFactoryPi1000Ref++;

	if(g_nTestFactoryPi1000Ref == 1)
    {
		g_pTestFactoryPi1000 = new CSttTestFactoryPi1000;
		g_pSttTestFactory = g_pTestFactoryPi1000;
        //CXLanguage oXLanguage;
        //oXLanguage.xlang_Buid(g_pTestFactory);
        //xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
    }

	return g_pTestFactoryPi1000;
}

void CSttTestFactoryPi1000::Release()
{
	g_nTestFactoryPi1000Ref--;

	if(g_nTestFactoryPi1000Ref == 0)
    {
		delete g_pTestFactoryPi1000;
		g_pTestFactoryPi1000 = NULL;
    }
}
