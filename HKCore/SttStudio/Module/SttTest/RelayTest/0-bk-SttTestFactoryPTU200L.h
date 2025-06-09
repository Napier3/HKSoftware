#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPTU200L : public CSttTestFactory
{
public:
	static CSttTestFactoryPTU200L *Create();
	static void Release();

private:
	CSttTestFactoryPTU200L(void);
	virtual ~CSttTestFactoryPTU200L(void);

	static int g_nTestFactoryPTU200LRef;
	static CSttTestFactoryPTU200L *g_pTestFactoryPTU200L;

};
