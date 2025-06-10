#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryRelayTest : public CSttTestFactory
{
public:
	static CSttTestFactoryRelayTest *Create();
	static void Release();

private:
	CSttTestFactoryRelayTest(void);
	virtual ~CSttTestFactoryRelayTest(void);

    static int g_nTestFactoryRelayTestRef;
    static CSttTestFactoryRelayTest *g_pTestFactoryRelayTest;

};
