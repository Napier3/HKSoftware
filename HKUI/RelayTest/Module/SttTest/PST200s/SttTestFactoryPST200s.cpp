#include "StdAfx.h"
#include "SttTestFactoryPST200s.h"

#ifdef _PSX_IDE_QT_
#include "../../SttTest/Common/SttManuTest.h"
#endif

int CSttTestFactoryPST200s::g_nTestFactoryPST200sRef = 0;
CSttTestFactoryPST200s *CSttTestFactoryPST200s::g_pTestFactoryPST200s = NULL;

static const CString g_strPxAppID_Relay = "";
static const CString g_strPxAppName_Relay = "稳控测试仪";


CSttTestFactoryPST200s::CSttTestFactoryPST200s()
{
    RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);//"ManualTest"
}

CSttTestFactoryPST200s::~CSttTestFactoryPST200s()
{
	
}

CSttTestFactoryPST200s *CSttTestFactoryPST200s::Create()
{
    g_nTestFactoryPST200sRef++;

    if (g_nTestFactoryPST200sRef == 1)
	{
        g_pTestFactoryPST200s = new CSttTestFactoryPST200s;
        g_pSttTestFactory = g_pTestFactoryPST200s;
	}

    return g_pTestFactoryPST200s;
}

void CSttTestFactoryPST200s::Release()
{
    g_nTestFactoryPST200sRef--;

    if (g_nTestFactoryPST200sRef == 0)
	{
        delete g_pTestFactoryPST200s;
        g_pTestFactoryPST200s = NULL;
	}
}
