#include "StdAfx.h"
#include "SttTestFactoryPNS331.h"


int CSttTestFactoryPNS331::g_nTestFactoryPNS331Ref = 0;
CSttTestFactoryPNS331 *CSttTestFactoryPNS331::g_pTestFactoryPNS331 = NULL;


CSttTestFactoryPNS331::CSttTestFactoryPNS331()
{
    RegisterInit();
}

CSttTestFactoryPNS331::~CSttTestFactoryPNS331()
{
}

CSttTestFactoryPNS331 *CSttTestFactoryPNS331::Create()
{
    g_nTestFactoryPNS331Ref++;

    if(g_nTestFactoryPNS331Ref == 1)
    {
        g_pTestFactoryPNS331 = new CSttTestFactoryPNS331;
        g_pSttTestFactory = g_pTestFactoryPNS331;
    }

    return g_pTestFactoryPNS331;
}

void CSttTestFactoryPNS331::Release()
{
    g_nTestFactoryPNS331Ref--;

    if(g_nTestFactoryPNS331Ref == 0)
    {
        delete g_pTestFactoryPNS331;
        g_pTestFactoryPNS331 = NULL;
    }
}
