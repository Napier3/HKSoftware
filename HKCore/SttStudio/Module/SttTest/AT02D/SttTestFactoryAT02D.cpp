#include "StdAfx.h"
#include "SttTestFactoryAT02D.h"

#include"../Common/SttManuTest.h"
#include"../Common/SttStateTest.h"
#include"../Common/SttChMapsConfig.h"
#include"../Common/SttLcPowerTest.h"
#include"../Common/Iec/SttIecDetect.h"
#include"../Common/Iec/SttIecRecord.h"
#include"../AT02D/SttTimeMeasureTest.h"
#include"../AT02D/SttRecordAndBinTest.h"
#include "../Common/Iec61850Config.h"
#include "../Common/SttUpdateFPGA.h"


int CSttTestFactoryAT02D::g_nTestFactoryAT02DRef = 0;
CSttTestFactoryAT02D *CSttTestFactoryAT02D::g_pTestFactoryAT02D = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "继保测试仪";


CSttTestFactoryAT02D::CSttTestFactoryAT02D()
{
	//SetParameter时不更新g_pCSttServerTestCtrlCntr->m_pCurrSttTest
	m_oMacroIDGroup.AddNewData(CSttIecDetect::m_strMacroID,"");
	m_oMacroIDGroup.AddNewData(CSttIecRecord::m_strMacroID,"");
	m_oMacroIDGroup.AddNewData(CSttLcPowerTest::m_strMacroID,"");
	//

	RegisterTestMacro(g_strPxAppID_Relay, CSttUpdateFPGA::m_strMacroName, CSttUpdateFPGA::m_strMacroID, CSttUpdateFPGA::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);//"ManualTest"
    RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
    RegisterTestMacro(g_strPxAppID_Relay, CIec61850Config::m_strMacroName, CIec61850Config::m_strMacroID, CIec61850Config::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttIecDetect::m_strMacroName, CSttIecDetect::m_strMacroID, CSttIecDetect::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttIecRecord::m_strMacroName, CSttIecRecord::m_strMacroID, CSttIecRecord::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttTimeMeasureTest::m_strMacroName, CSttTimeMeasureTest::m_strMacroID, CSttTimeMeasureTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttRecordAndBinTest::m_strMacroName, CSttRecordAndBinTest::m_strMacroID, CSttRecordAndBinTest::CreateTest);
}

CSttTestFactoryAT02D::~CSttTestFactoryAT02D()
{

}

CSttTestFactoryAT02D *CSttTestFactoryAT02D::Create()
{
    g_nTestFactoryAT02DRef++;

    if (g_nTestFactoryAT02DRef == 1)
    {
        g_pTestFactoryAT02D = new CSttTestFactoryAT02D;
        g_pSttTestFactory = g_pTestFactoryAT02D;

        //CXLanguage oXLanguage;
        //oXLanguage.xlang_Buid(g_pTestFactory);
        //xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
    }

    return g_pTestFactoryAT02D;
}

void CSttTestFactoryAT02D::Release()
{
    g_nTestFactoryAT02DRef--;

    if (g_nTestFactoryAT02DRef == 0)
    {
        delete g_pTestFactoryAT02D;
        g_pTestFactoryAT02D = NULL;
    }
}
