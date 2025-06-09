#include "StdAfx.h"
#include "SttTestFactorytest.h"

#ifdef _PSX_IDE_QT_
    #include "../../SttTest/Common/Iec61850Config.h"
    #include "../../SttTest/Common/SttChMapsConfig.h"

    #include "../../SttTest/Common/Iec/SttIecDetect.h"
    #include "../../SttTest/Common/Iec/SttIecRecord.h"
    #include "SttGoose50ManuTest.h"
#endif

int CSttTestFactoryPNS330::g_nTestFactoryPNS330Ref = 0;
CSttTestFactoryPNS330 *CSttTestFactoryPNS330::g_pTestFactoryPNS330 = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPNS330::CSttTestFactoryPNS330()
{
    RegisterTestMacro(g_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);
    RegisterTestMacro(g_strPxAppID_Relay, CIec61850Config::m_strMacroName, CIec61850Config::m_strMacroID, CIec61850Config::CreateTest);
    RegisterTestMacro(g_strPxAppID_Relay, CSttIecDetect::m_strMacroName, CSttIecDetect::m_strMacroID, CSttIecDetect::CreateTest);
    RegisterTestMacro(g_strPxAppID_Relay, CSttIecRecord::m_strMacroName, CSttIecRecord::m_strMacroID, CSttIecRecord::CreateTest);
    RegisterTestMacro(g_strPxAppID_Relay, CSttGoose50ManuTest::m_strMacroName, "ManualTest", CSttGoose50ManuTest::CreateTest);
    RegisterTestMacro(g_strPxAppID_Relay, CSttGoose50ManuTest::m_strMacroName, CSttGoose50ManuTest::m_strMacroID, CSttGoose50ManuTest::CreateTest);
}

CSttTestFactoryPNS330::~CSttTestFactoryPNS330()
{
}

CSttTestFactoryPNS330 *CSttTestFactoryPNS330::Create()
{
    g_nTestFactoryPNS330Ref++;

    if(g_nTestFactoryPNS330Ref == 1)
    {
        g_pTestFactoryPNS330 = new CSttTestFactoryPNS330;
        g_pSttTestFactory = g_pTestFactoryPNS330;
    }

    return g_pTestFactoryPNS330;
}

void CSttTestFactoryPNS330::Release()
{
    g_nTestFactoryPNS330Ref--;

    if(g_nTestFactoryPNS330Ref == 0)
    {
        delete g_pTestFactoryPNS330;
        g_pTestFactoryPNS330 = NULL;
    }
}
