//2020-10-25  lijunqing  
//调试用，为SttTestServerDebug调试测试功能用

#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryDebugServer : public CSttTestFactory
{
public:
	static CSttTestFactoryDebugServer *Create();
	static void Release();

private:
	CSttTestFactoryDebugServer(void);
	virtual ~CSttTestFactoryDebugServer(void);

	static int g_nTestFactoryDebugServerRef;
	static CSttTestFactoryDebugServer *g_pTestFactoryDebugServer;

};
