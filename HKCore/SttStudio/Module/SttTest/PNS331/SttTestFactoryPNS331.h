#pragma once
#include "../common/SttTestFactoryCom.h"

class CSttTestFactoryPNS331 : public CSttTestFactoryCom
{
public:
    static CSttTestFactoryPNS331 *Create();
    static void Release();

private:
    CSttTestFactoryPNS331(void);
    virtual ~CSttTestFactoryPNS331(void);

    static int g_nTestFactoryPNS331Ref;
    static CSttTestFactoryPNS331 *g_pTestFactoryPNS331;

};
