#pragma once
#include "../common/SttTestFactoryCom.h"

class CSttTestFactoryPi1000 : public CSttTestFactoryCom
{
public:
	static CSttTestFactoryPi1000 *Create();
    static void Release();

private:
	CSttTestFactoryPi1000(void);
	virtual ~CSttTestFactoryPi1000(void);

	static int g_nTestFactoryPi1000Ref;
	static CSttTestFactoryPi1000 *g_pTestFactoryPi1000;

};
