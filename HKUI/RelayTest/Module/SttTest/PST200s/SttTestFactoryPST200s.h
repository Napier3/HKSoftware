#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPST200s : public CSttTestFactory
{
public:
    static CSttTestFactoryPST200s *Create();
	static void Release();

private:
    CSttTestFactoryPST200s(void);
    virtual ~CSttTestFactoryPST200s(void);

    static int g_nTestFactoryPST200sRef;
    static CSttTestFactoryPST200s *g_pTestFactoryPST200s;

};
