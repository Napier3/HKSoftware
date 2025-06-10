#include "stdafx.h"
#include "SttTestFactoryForDebug.h"

#include"SttTestForDebug.h"
#include "../Common/SttStateTest.h"
#include "../Common/SttChMapsConfig.h"
#include "../Common/SttModulesGearSwitch.h"
#include "../Common/SttAuxDCOutput.h"
#include "../Common/State/SttState6U6I_Pnv.h"
#include "../Common/SttAppRatesConfig.h"
#include "../Common/SttManuTest.h"
#include "../Common/UITest/SttUITest12U12I_Pnv.h"
#include "../Common/Sequence/SttSequenceManuTest.h"

#include "../../SttTest/Common/Impedance/SttCBOperateTest.h"
#include "../../SttTest/Common/Impedance/SttDisTanceSearchTest.h"
#include "../../SttTest/Common/Impedance/SttDisTanceTest.h"
#include "../../SttTest/Common/Impedance/SttOverCurrentTest.h"
#include "../../SttTest/Common/Impedance/SttRecloseAccTest.h"
#include "../../SttTest/Common/Impedance/SttZeroCurrentTest.h"
#include"../../SttTest/Common/Impedance/SttStateOverCurrentTest.h"
#include"../../SttTest/Common/Impedance/SttStateZeroCurrentTest.h"
#include"../../SttTest/Common/ActionTime/SttActionTimeTest.h"
#include"../../SttTest/Common/Gradient/SttPowerDirectionTest.h"
#include"../../SttTest/Common/Gradient/SttULockOverCurrentTest.h"
#include"../../SttTest/Common/Gradient/SttCurrentActValueTest.h"
#include"../../SttTest/Common/LowFreqLowVol/SttLowFreqActTest.h"
#include"../../SttTest/Common/LowFreqLowVol/SttLowFreqDfDtTest.h"
#include"../../SttTest/Common/LowFreqLowVol/SttLowFreqILockTest.h"
#include"../../SttTest/Common/LowFreqLowVol/SttLowFreqTimeTest.h"
#include"../../SttTest/Common/LowFreqLowVol/SttLowFreqULockTest.h"
#include"../../SttTest/Common/LowFreqLowVol/SttLowVolActTest.h"
#include"../../SttTest/Common/LowFreqLowVol/SttLowVolDvDtTest.h"
#include"../../SttTest/Common/LowFreqLowVol/SttLowVolTimeTest.h"
#include "../../SttTest/Common/Impedance/SttPowerFreqTest.h"

#include "../../SttTest/Common/Diff/SttDiffActTimeTest.h"
#include "../../SttTest/Common/Diff/SttDiffCurrHarmTest.h"
#include "../../SttTest/Common/Diff/SttDiffCurrQuickTest.h"
#include "../../SttTest/Common/Diff/SttDiffCurrRateTest.h"
#include "../../SttTest/Common/Diff/SttDiffCurrThrTest.h"

#include "../../SttTest/Common/Diff/SttElecRailwayDiffThrTest.h"
#include "../../SttTest/Common/Diff/SttElecRailwayDiffRateTest.h"
#include "../../SttTest/Common/Diff/SttElecRailwayDiffQuickTest.h"
#include "../../SttTest/Common/Diff/SttElecRailwayDiffHarmTest.h"
#include "../../SttTest/Common/Diff/SttElecRailwayDiffActTimeTest.h"

#include "../../SttTest/Common/DCIncrement/SttDcIncrementTest.h"


#include "../../SttTest/Common/Iec61850Config.h"



// #include"RelayTest/Iec61850Config.h"

int CSttTestFactoryForDebug::g_nTestFactoryRelayTestRef = 0;
CSttTestFactoryForDebug *CSttTestFactoryForDebug::g_pTestFactoryRelayTest = NULL;

static const CString g_strPxAppID_Relay = "relay";
static const CString g_strPxAppName_Relay = "继保测试仪";


CSttTestFactoryForDebug::CSttTestFactoryForDebug()
{
	RegisterTestMacro(g_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);//增加通道映射注册
    RegisterTestMacro(g_strPxAppID_Relay, CSttTestForDebug::m_strMacroName, CSttTestForDebug::m_strMacroID, CSttTestForDebug::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttModulesGearSwitch::m_strMacroName, CSttModulesGearSwitch::m_strMacroID, CSttModulesGearSwitch::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttAuxDCOutput::m_strMacroName, CSttAuxDCOutput::m_strMacroID, CSttAuxDCOutput::CreateTest);
//	RegisterTestMacro(g_strPxAppID_Relay, CSttAppRatesConfig::m_strMacroName, CSttAppRatesConfig::m_strMacroID, CSttAppRatesConfig::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttSequenceManuTest::m_strMacroName, CSttSequenceManuTest::m_strMacroID, CSttSequenceManuTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttState6U6I_Pnv::m_strMacroName, CSttState6U6I_Pnv::m_strMacroID, CSttState6U6I_Pnv::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttUITest12U12I_Pnv::m_strMacroName, CSttUITest12U12I_Pnv::m_strMacroID, CSttUITest12U12I_Pnv::CreateTest);

	RegisterTestMacro(g_strPxAppID_Relay, CIec61850Config::m_strMacroName, CIec61850Config::m_strMacroID, CIec61850Config::CreateTest);

	//高级实验
	RegisterTestMacro(g_strPxAppID_Relay, CSttCBOperateTest::m_strMacroName, CSttCBOperateTest::m_strMacroID, CSttCBOperateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttDisTanceSearchTest::m_strMacroName, CSttDisTanceSearchTest::m_strMacroID, CSttDisTanceSearchTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttDisTanceTest::m_strMacroName, CSttDisTanceTest::m_strMacroID, CSttDisTanceTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttOverCurrentTest::m_strMacroName, CSttOverCurrentTest::m_strMacroID, CSttOverCurrentTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttRecloseAccTest::m_strMacroName, CSttRecloseAccTest::m_strMacroID, CSttRecloseAccTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateOverCurrentTest::m_strMacroName, CSttStateOverCurrentTest::m_strMacroID, CSttStateOverCurrentTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttZeroCurrentTest::m_strMacroName, CSttZeroCurrentTest::m_strMacroID, CSttZeroCurrentTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttStateZeroCurrentTest::m_strMacroName, CSttStateZeroCurrentTest::m_strMacroID, CSttStateZeroCurrentTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttActionTimeTest::m_strMacroName, CSttActionTimeTest::m_strMacroID, CSttActionTimeTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttPowerDirectionTest::m_strMacroName, CSttPowerDirectionTest::m_strMacroID, CSttPowerDirectionTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttULockOverCurrentTest::m_strMacroName, CSttULockOverCurrentTest::m_strMacroID, CSttULockOverCurrentTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLowFreqActTest::m_strMacroName, CSttLowFreqActTest::m_strMacroID, CSttLowFreqActTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLowFreqDfDtTest::m_strMacroName, CSttLowFreqDfDtTest::m_strMacroID, CSttLowFreqDfDtTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLowFreqILockTest::m_strMacroName, CSttLowFreqILockTest::m_strMacroID, CSttLowFreqILockTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLowFreqTimeTest::m_strMacroName, CSttLowFreqTimeTest::m_strMacroID, CSttLowFreqTimeTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLowFreqULockTest::m_strMacroName, CSttLowFreqULockTest::m_strMacroID, CSttLowFreqULockTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLowVolActTest::m_strMacroName, CSttLowVolActTest::m_strMacroID, CSttLowVolActTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLowVolTimeTest::m_strMacroName, CSttLowVolTimeTest::m_strMacroID, CSttLowVolTimeTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttLowVolDvDtTest::m_strMacroName, CSttLowVolDvDtTest::m_strMacroID, CSttLowVolDvDtTest::CreateTest);

	RegisterTestMacro(g_strPxAppID_Relay, CSttPowerFreqTest::m_strMacroName, CSttPowerFreqTest::m_strMacroID, CSttPowerFreqTest::CreateTest);

	RegisterTestMacro(g_strPxAppID_Relay, CSttCurrentActValueTest::m_strMacroName, CSttCurrentActValueTest::m_strMacroID, CSttCurrentActValueTest::CreateTest);

	RegisterTestMacro(g_strPxAppID_Relay, CSttDiffActTimeTest::m_strMacroName, CSttDiffActTimeTest::m_strMacroID, CSttDiffActTimeTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttDiffCurrHarmTest::m_strMacroName, CSttDiffCurrHarmTest::m_strMacroID, CSttDiffCurrHarmTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttDiffCurrQuickTest::m_strMacroName, CSttDiffCurrQuickTest::m_strMacroID, CSttDiffCurrQuickTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttDiffCurrRateTest::m_strMacroName, CSttDiffCurrRateTest::m_strMacroID, CSttDiffCurrRateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttDiffCurrThrTest::m_strMacroName, CSttDiffCurrThrTest::m_strMacroID, CSttDiffCurrThrTest::CreateTest);

	RegisterTestMacro(g_strPxAppID_Relay, CSttElecRailwayDiffThrTest::m_strMacroName, CSttElecRailwayDiffThrTest::m_strMacroID, CSttElecRailwayDiffThrTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttElecRailwayDiffRateTest::m_strMacroName, CSttElecRailwayDiffRateTest::m_strMacroID, CSttElecRailwayDiffRateTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttElecRailwayDiffQuickTest::m_strMacroName, CSttElecRailwayDiffQuickTest::m_strMacroID, CSttElecRailwayDiffQuickTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttElecRailwayDiffHarmTest::m_strMacroName, CSttElecRailwayDiffHarmTest::m_strMacroID, CSttElecRailwayDiffHarmTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttElecRailwayDiffActTimeTest::m_strMacroName, CSttElecRailwayDiffActTimeTest::m_strMacroID, CSttElecRailwayDiffActTimeTest::CreateTest);
	RegisterTestMacro(g_strPxAppID_Relay, CSttDcIncrementTest::m_strMacroName, CSttDcIncrementTest::m_strMacroID, CSttDcIncrementTest::CreateTest);

 // RegisterTestMacro(g_strPxAppID_Relay, CIec61850Config::m_strMacroName, CIec61850Config::m_strMacroID, CIec61850Config::CreateTest);
}

CSttTestFactoryForDebug::~CSttTestFactoryForDebug()
{
	
}

CSttTestFactoryForDebug *CSttTestFactoryForDebug::Create()
{
    g_nTestFactoryRelayTestRef++;

    if (g_nTestFactoryRelayTestRef == 1)
	{
        g_pTestFactoryRelayTest = new CSttTestFactoryForDebug;
        g_pSttTestFactory = g_pTestFactoryRelayTest;
    }

    return g_pTestFactoryRelayTest;
}

void CSttTestFactoryForDebug::Release()
{
    g_nTestFactoryRelayTestRef--;

    if (g_nTestFactoryRelayTestRef == 0)
	{
        delete g_pTestFactoryRelayTest;
        g_pTestFactoryRelayTest = NULL;
	}
}
