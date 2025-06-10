#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryT100Si : public CSttTestFactory
{
public:
	static CSttTestFactoryT100Si *Create();
	static void Release();

private:
	CSttTestFactoryT100Si(void);
	virtual ~CSttTestFactoryT100Si(void);

	static int g_nTestFactoryT100SiRef;
	static CSttTestFactoryT100Si *g_pTestFactoryT100Si;

};
