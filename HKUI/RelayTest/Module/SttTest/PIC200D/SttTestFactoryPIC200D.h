#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPIC200D : public CSttTestFactory
{
public:
	static CSttTestFactoryPIC200D *Create();
	static void Release();

private:
	CSttTestFactoryPIC200D(void);
	virtual ~CSttTestFactoryPIC200D(void);

	static int g_nTestFactoryPIC200DRef;
	static CSttTestFactoryPIC200D *g_pTestFactoryPIC200D;

};
