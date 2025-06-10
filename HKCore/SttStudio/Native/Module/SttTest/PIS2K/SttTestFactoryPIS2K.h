#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPIS2K : public CSttTestFactory
{
public:
	static CSttTestFactoryPIS2K *Create();
	static void Release();

private:
	CSttTestFactoryPIS2K(void);
	virtual ~CSttTestFactoryPIS2K(void);

	static int g_nTestFactoryPIS2KRef;
	static CSttTestFactoryPIS2K *g_pTestFactoryPIS2K;

};
