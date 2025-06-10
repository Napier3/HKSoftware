#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPTU300B : public CSttTestFactory
{
public:
	static CSttTestFactoryPTU300B *Create();
	static void Release();

private:
	CSttTestFactoryPTU300B(void);
	virtual ~CSttTestFactoryPTU300B(void);

	static int g_nTestFactoryPTU300BRef;
	static CSttTestFactoryPTU300B *g_pTestFactoryPTU300B;

};
