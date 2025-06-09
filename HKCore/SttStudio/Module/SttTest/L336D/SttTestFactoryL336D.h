#pragma once
#include "../common/SttTestFactoryCom.h"

class CSttTestFactoryL336D : public CSttTestFactoryCom
{
public:
	static CSttTestFactoryL336D *Create();
    static void Release();

private:
	CSttTestFactoryL336D(void);
	virtual ~CSttTestFactoryL336D(void);

	static int g_nTestFactoryL336DRef;
	static CSttTestFactoryL336D *g_pTestFactoryL336D;

};
