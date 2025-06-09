#pragma once
#include "../common/SttTestFactoryCom.h"

class CSttTestFactoryPTU200L : public CSttTestFactoryCom
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
