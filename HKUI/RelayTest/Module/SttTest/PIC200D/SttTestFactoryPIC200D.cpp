#include "stdafx.h"
#include "SttTestFactoryPIC200D.h"


#ifdef _PSX_IDE_QT_
#include"SttPIC200DTest.h"
#include"SttPIC200DIOTest.h"
#include "Adjust/SttAdjust_ModuleOutput.h"
#endif

int CSttTestFactoryPIC200D::g_nTestFactoryPIC200DRef = 0;
CSttTestFactoryPIC200D *CSttTestFactoryPIC200D::g_pTestFactoryPIC200D = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ºÃ±£≤‚ ‘“«";


CSttTestFactoryPIC200D::CSttTestFactoryPIC200D()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttPic200dTest::m_strMacroName, CSttPic200dTest::m_strMacroID, CSttPic200dTest::CreateTest);
    RegisterTestMacro(g_strPxAppID_Relay, CSttPic200dIoTest::m_strMacroName, CSttPic200dIoTest::m_strMacroID, CSttPic200dIoTest::CreateTest);
}

CSttTestFactoryPIC200D::~CSttTestFactoryPIC200D()
{
	
}

CSttTestFactoryPIC200D *CSttTestFactoryPIC200D::Create()
{
	g_nTestFactoryPIC200DRef++;

	if (g_nTestFactoryPIC200DRef == 1)
	{
		g_pTestFactoryPIC200D = new CSttTestFactoryPIC200D;
		g_pSttTestFactory = g_pTestFactoryPIC200D;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryPIC200D;
}

void CSttTestFactoryPIC200D::Release()
{
	g_nTestFactoryPIC200DRef--;

	if (g_nTestFactoryPIC200DRef == 0)
	{
		delete g_pTestFactoryPIC200D;
		g_pTestFactoryPIC200D = NULL;
	}
}
