#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPFC6A : public CSttTestFactory
{
public:
	static CSttTestFactoryPFC6A *Create();
	static void Release();

private:
	CSttTestFactoryPFC6A(void);
	virtual ~CSttTestFactoryPFC6A(void);

	static int g_nTestFactoryPFC6ARef;
	static CSttTestFactoryPFC6A *g_pTestFactoryPFC6A;

};
