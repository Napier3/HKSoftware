#include "StdAfx.h"
#include "SttTestFactoryPID01.h"
#include "SttPID01Test.h"
#include "SttPID16Test.h"


int CSttTestFactoryPID01::g_nTestFactoryPID01Ref = 0;
CSttTestFactoryPID01 *CSttTestFactoryPID01::g_pTestFactoryPID01 = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPID01::CSttTestFactoryPID01()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttPid01Test::m_strMacroName, CSttPid01Test::m_strMacroID, CSttPid01Test::CreateTest);
    RegisterTestMacro(g_strPxAppID_Relay, CSttPid16Test::m_strMacroName, CSttPid16Test::m_strMacroID, CSttPid16Test::CreateTest);
}

CSttTestFactoryPID01::~CSttTestFactoryPID01()
{
	
}

CSttTestFactoryPID01 *CSttTestFactoryPID01::Create()
{
	g_nTestFactoryPID01Ref++;

	if (g_nTestFactoryPID01Ref == 1)
	{
		g_pTestFactoryPID01 = new CSttTestFactoryPID01;
		g_pSttTestFactory = g_pTestFactoryPID01;
	}

	return g_pTestFactoryPID01;
}

void CSttTestFactoryPID01::Release()
{
	g_nTestFactoryPID01Ref--;

	if (g_nTestFactoryPID01Ref == 0)
	{
		delete g_pTestFactoryPID01;
		g_pTestFactoryPID01 = NULL;
	}
}
