#include "StdAfx.h"
#include "SttTestFactoryL336D.h"
#include "../common/SttUpdateFPGA.h"
#include "../Common/Replay/Pcap/SttPcapReplay.h"

int CSttTestFactoryL336D::g_nTestFactoryL336DRef = 0;
CSttTestFactoryL336D *CSttTestFactoryL336D::g_pTestFactoryL336D = NULL;

CSttTestFactoryL336D::CSttTestFactoryL336D()
{
    RegisterInit();
    RegisterTestMacro(m_strPxAppID_Relay, CSttUpdateFPGA::m_strMacroName, CSttUpdateFPGA::m_strMacroID, CSttUpdateFPGA::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttPcapReplay::m_strMacroName, CSttPcapReplay::m_strMacroID, CSttPcapReplay::CreateTest);
}

CSttTestFactoryL336D::~CSttTestFactoryL336D()
{
}

CSttTestFactoryL336D *CSttTestFactoryL336D::Create()
{
	g_nTestFactoryL336DRef++;

	if(g_nTestFactoryL336DRef == 1)
    {
		g_pTestFactoryL336D = new CSttTestFactoryL336D;
		g_pSttTestFactory = g_pTestFactoryL336D;
        //CXLanguage oXLanguage;
        //oXLanguage.xlang_Buid(g_pTestFactory);
        //xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
    }

	return g_pTestFactoryL336D;
}

void CSttTestFactoryL336D::Release()
{
	g_nTestFactoryL336DRef--;

	if(g_nTestFactoryL336DRef == 0)
    {
		delete g_pTestFactoryL336D;
		g_pTestFactoryL336D = NULL;
    }
}
