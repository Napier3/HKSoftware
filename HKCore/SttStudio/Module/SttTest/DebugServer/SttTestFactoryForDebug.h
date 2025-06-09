#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryForDebug : public CSttTestFactory
{
public:
	static CSttTestFactoryForDebug *Create();
	static void Release();

private:
	CSttTestFactoryForDebug(void);
	virtual ~CSttTestFactoryForDebug(void);

    static int g_nTestFactoryRelayTestRef;
    static CSttTestFactoryForDebug *g_pTestFactoryRelayTest;

};
