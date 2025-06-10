#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPIK100 : public CSttTestFactory
{
public:
	static CSttTestFactoryPIK100 *Create();
	static void Release();

private:
	CSttTestFactoryPIK100(void);
	virtual ~CSttTestFactoryPIK100(void);

	static int g_nTestFactoryPIK100Ref;
	static CSttTestFactoryPIK100 *g_pTestFactoryPIK100;

};
