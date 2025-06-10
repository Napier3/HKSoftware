#pragma once
#include "../common/SttTestFactoryCom.h"

class CSttTestFactoryPN466 : public CSttTestFactoryCom
{
public:
    static CSttTestFactoryPN466 *Create();
    static void Release();

private:
    CSttTestFactoryPN466(void);
    virtual ~CSttTestFactoryPN466(void);

    static int g_nTestFactoryPN466Ref;
    static CSttTestFactoryPN466 *g_pTestFactoryPN466;

};
