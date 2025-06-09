#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPTU : public CSttTestFactory
{
public:
	static CSttTestFactoryPTU *Create();
	static void Release();

private:
	CSttTestFactoryPTU(void);
	virtual ~CSttTestFactoryPTU(void);

	static int g_nTestFactoryPTURef;
	static CSttTestFactoryPTU *g_pTestFactoryPTU;

};
