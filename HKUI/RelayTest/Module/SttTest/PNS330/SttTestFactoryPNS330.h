#pragma once
#include "../Common/SttTestFactoryCom.h"

class CSttTestFactoryPNS330 : public CSttTestFactoryCom
{
public:
    static CSttTestFactoryPNS330 *Create();
    static void Release();

private:
    CSttTestFactoryPNS330(void);
    virtual ~CSttTestFactoryPNS330(void);

    static int g_nTestFactoryPNS330Ref;
    static CSttTestFactoryPNS330 *g_pTestFactoryPNS330;

};
