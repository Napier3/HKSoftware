#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPID01 : public CSttTestFactory
{
public:
	static CSttTestFactoryPID01 *Create();
	static void Release();

private:
	CSttTestFactoryPID01(void);
	virtual ~CSttTestFactoryPID01(void);

	static int g_nTestFactoryPID01Ref;
	static CSttTestFactoryPID01 *g_pTestFactoryPID01;

};
