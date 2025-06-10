#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPH05 : public CSttTestFactory
{
public:
    static CSttTestFactoryPH05 *Create();
	static void Release();

private:
    CSttTestFactoryPH05(void);
    virtual ~CSttTestFactoryPH05(void);

    static int g_nTestFactoryPH05Ref;
    static CSttTestFactoryPH05 *g_pTestFactoryPH05;

};
