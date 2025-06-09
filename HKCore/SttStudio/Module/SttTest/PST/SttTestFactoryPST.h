#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPST : public CSttTestFactory
{
public:
    static CSttTestFactoryPST *Create();
	static void Release();

private:
    CSttTestFactoryPST(void);
    virtual ~CSttTestFactoryPST(void);

    static int g_nTestFactoryPSTRef;
    static CSttTestFactoryPST *g_pTestFactoryPST;

};
