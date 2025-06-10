#include "StdAfx.h"
#include "SttTestFactoryPST.h"

#ifdef _PSX_IDE_QT_
//#include "../../SttTest/Common/SttManuTest.h"
#endif

int CSttTestFactoryPST::g_nTestFactoryPSTRef = 0;
CSttTestFactoryPST *CSttTestFactoryPST::g_pTestFactoryPST = NULL;

static const CString g_strPxAppID_Relay = "";
static const CString g_strPxAppName_Relay = "Œ»øÿ≤‚ ‘“«";


CSttTestFactoryPST::CSttTestFactoryPST()
{
//    RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);//"ManualTest"
}

CSttTestFactoryPST::~CSttTestFactoryPST()
{
	
}

CSttTestFactoryPST *CSttTestFactoryPST::Create()
{
    g_nTestFactoryPSTRef++;

    if (g_nTestFactoryPSTRef == 1)
	{
        g_pTestFactoryPST = new CSttTestFactoryPST;
        g_pSttTestFactory = g_pTestFactoryPST;
	}

    return g_pTestFactoryPST;
}

void CSttTestFactoryPST::Release()
{
    g_nTestFactoryPSTRef--;

    if (g_nTestFactoryPSTRef == 0)
	{
        delete g_pTestFactoryPST;
        g_pTestFactoryPST = NULL;
	}
}
