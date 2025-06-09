#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryPiLight : public CSttTestFactory
{
public:
	static CSttTestFactoryPiLight *Create();
	static void Release();

private:
	CSttTestFactoryPiLight(void);
	virtual ~CSttTestFactoryPiLight(void);

	static int g_nTestFactoryPiLightRef;
	static CSttTestFactoryPiLight *g_pTestFactoryPiLight;

};
