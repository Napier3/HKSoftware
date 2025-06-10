#include "StdAfx.h"
#include "SttTestFactoryPiLight.h"

#ifdef _PSX_IDE_QT_
#include "../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include "../../SttTest/Common/Adjust/SttAdjust_BinaryOutput.h"
#include "../../SttTest/Common/Iec61850Config.h"
#include "../../SttTest/Common/SttChMapsConfig.h"
#include "../../SttTest/PiLight/SttLightTest.h"
#include "../../SttTest/PiLight/SttLightAngleCtrl.h"
#include "../../SttTest/PiLight/SttLightGetAngle.h"
#endif

int CSttTestFactoryPiLight::g_nTestFactoryPiLightRef = 0;
CSttTestFactoryPiLight *CSttTestFactoryPiLight::g_pTestFactoryPiLight = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "ª°π‚≤‚ ‘“«";


CSttTestFactoryPiLight::CSttTestFactoryPiLight()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);

	RegisterTestMacro(g_strPxAppID_Relay, CSttLightTest::m_strMacroName, CSttLightTest::m_strMacroID, CSttLightTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLightAngleCtrl::m_strMacroName, CSttLightAngleCtrl::m_strMacroID, CSttLightAngleCtrl::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLightGetAngle::m_strMacroName, CSttLightGetAngle::m_strMacroID, CSttLightGetAngle::CreateTest);
}

CSttTestFactoryPiLight::~CSttTestFactoryPiLight()
{
	
}

CSttTestFactoryPiLight *CSttTestFactoryPiLight::Create()
{
	g_nTestFactoryPiLightRef++;

	if (g_nTestFactoryPiLightRef == 1)
	{
		g_pTestFactoryPiLight = new CSttTestFactoryPiLight;
		g_pSttTestFactory = g_pTestFactoryPiLight;

		//CXLanguage oXLanguage;
		//oXLanguage.xlang_Buid(g_pTestFactory);
		//xlang_TranslateByResourceFile(g_pTestFactory, _T("TestMacro.xml"));
	}

	return g_pTestFactoryPiLight;
}

void CSttTestFactoryPiLight::Release()
{
	g_nTestFactoryPiLightRef--;

	if (g_nTestFactoryPiLightRef == 0)
	{
		delete g_pTestFactoryPiLight;
		g_pTestFactoryPiLight = NULL;
	}
}
