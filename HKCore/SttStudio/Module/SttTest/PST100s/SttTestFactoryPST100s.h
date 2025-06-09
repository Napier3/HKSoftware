#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPST100s : public CSttTestFactory
{
public:
    static CSttTestFactoryPST100s *Create();
	static void Release();

private:
    CSttTestFactoryPST100s(void);
    virtual ~CSttTestFactoryPST100s(void);

    static int g_nTestFactoryPST100sRef;
    static CSttTestFactoryPST100s *g_pTestFactoryPST100s;

};
