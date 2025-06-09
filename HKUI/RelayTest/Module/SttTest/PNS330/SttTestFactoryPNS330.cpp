//#include "StdAfx.h"
#include "../../../../Module/OSInterface/QT/stdafx.h"
#include "SttTestFactoryPNS330.h"
//#include "../common/SttUpdateFPGA.h"
#include "../Common/SttUpdateFPGA.h"

int CSttTestFactoryPNS330::g_nTestFactoryPNS330Ref = 0;
CSttTestFactoryPNS330 *CSttTestFactoryPNS330::g_pTestFactoryPNS330 = NULL;

CSttTestFactoryPNS330::CSttTestFactoryPNS330()
{
    RegisterInit();
    RegisterTestMacro(m_strPxAppID_Relay, CSttUpdateFPGA::m_strMacroName, CSttUpdateFPGA::m_strMacroID, CSttUpdateFPGA::CreateTest);
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
