#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryAT02D : public CSttTestFactory
{
public:
        static CSttTestFactoryAT02D *Create();
	static void Release();

private:
        CSttTestFactoryAT02D(void);
        virtual ~CSttTestFactoryAT02D(void);

    static int g_nTestFactoryAT02DRef;
    static CSttTestFactoryAT02D *g_pTestFactoryAT02D;

};
