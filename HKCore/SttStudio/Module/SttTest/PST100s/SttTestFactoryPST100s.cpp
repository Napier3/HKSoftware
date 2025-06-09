#include "StdAfx.h"
#include "SttTestFactoryPST100s.h"

#ifdef _PSX_IDE_QT_
//#include "../../SttTest/Common/SttManuTest.h"
#endif

int CSttTestFactoryPST100s::g_nTestFactoryPST100sRef = 0;
CSttTestFactoryPST100s *CSttTestFactoryPST100s::g_pTestFactoryPST100s = NULL;

static const CString g_strPxAppID_Relay = "";
static const CString g_strPxAppName_Relay = "Œ»øÿ≤‚ ‘“«";


CSttTestFactoryPST100s::CSttTestFactoryPST100s()
{
//    RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);//"ManualTest"
}

CSttTestFactoryPST100s::~CSttTestFactoryPST100s()
{
	
}

CSttTestFactoryPST100s *CSttTestFactoryPST100s::Create()
{
    g_nTestFactoryPST100sRef++;

    if (g_nTestFactoryPST100sRef == 1)
	{
        g_pTestFactoryPST100s = new CSttTestFactoryPST100s;
        g_pSttTestFactory = g_pTestFactoryPST100s;
	}

    return g_pTestFactoryPST100s;
}

void CSttTestFactoryPST100s::Release()
{
    g_nTestFactoryPST100sRef--;

    if (g_nTestFactoryPST100sRef == 0)
	{
        delete g_pTestFactoryPST100s;
        g_pTestFactoryPST100s = NULL;
	}
}
