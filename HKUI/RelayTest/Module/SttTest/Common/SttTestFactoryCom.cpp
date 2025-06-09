//#include "StdAfx.h"
#include "../../../../Module/OSInterface/QT/stdafx.h"
#include "SttTestFactoryCom.h"

#ifdef _PSX_IDE_QT_
    #include "../../SttTest/Common/SttStateTest.h"
    #include "../../SttTest/Common/SttGradientTest.h"
    #include "../../SttTest/Common/SttGradientMaxAngleTest.h"
    #include "../../SttTest/Common/SttURampTest.h"
    #include "../../SttTest/Common/SttIRampTest.h"
    #include "../../SttTest/Common/SttManuTest.h"
    #include "../../SttTest/Common/Sequence/SttSequenceManuTest.h"
    #include "../../SttTest/Common/Sequence/SttSequenceGradientTest.h"
    #include "../../SttTest/Common/LineVolt/SttLineVoltManuTest.h"
    #include "../../SttTest/Common/LineVolt/SttLineVoltGradientTest.h"
    #include "../../SttTest/Common/SttHarmTest.h"
    #include "../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
    #include "../../SttTest/Common/Adjust/SttAdjust_BinaryOutput.h"
	#include "../../SttTest/Common/Adjust/SttAdjust_BinaryExOutput.h"
    #include "../../SttTest/Common/Adjust/SttAdjust_RegisterTest.h"
    #include "../../SttTest/Common/Replay/LongTime/SttReplayTest.h"
    #include "../../SttTest/Common/Iec61850Config.h"
    #include "../../SttTest/Common/SttChMapsConfig.h"
    #include "../../SttTest/Common/SttSoeTest.h"

    #include "../../SttTest/Common/State/SttState6U6I_Pnv.h"
    #include "../../SttTest/Common/State/SttState4U3I_Pnv.h"
    #include "../../SttTest/Common/State/SttStateDiffCoefTest_Pnv.h"
    #include "../../SttTest/Common/State/SttPsuStateTest.h"
    #include "../../SttTest/Common/UITest/SttUITest12U12I_Pnv.h"

    #include "../../SttTest/Common/Impedance/SttCBOperateTest.h"
    #include "../../SttTest/Common/Impedance/SttDisTanceSearchTest.h"
    #include "../../SttTest/Common/Impedance/SttDisTanceSearchTest_I.h"
    #include "../../SttTest/Common/Impedance/SttDisTanceTest.h"
    #include "../../SttTest/Common/Impedance/SttDisTanceTest_I.h"
    #include "../../SttTest/Common/Impedance/SttOverCurrentTest.h"
    #include "../../SttTest/Common/Impedance/SttOverVoltageTest.h"
    #include "../../SttTest/Common/Impedance/SttVoltageTest_Pnv.h"
    #include "../../SttTest/Common/Impedance/SttRecloseAccTest.h"
#include "../../SttTest/Common/Impedance/SttStateRecloseAccTest.h"
	#include "../../SttTest/Common/Impedance/SttTURecloseAccTest.h"
    #include "../../SttTest/Common/Impedance/SttZeroCurrentTest.h"
    #include"../../SttTest/Common/Impedance/SttStateOverCurrentTest.h"
    #include"../../SttTest/Common/Impedance/SttStateZeroCurrentTest.h"
    #include"../../SttTest/Common/Impedance/SttPowerFreqTest.h"
    #include"../../SttTest/Common/ActionTime/SttActionTimeTest.h"
    #include"../../SttTest/Common/Gradient/SttPowerDirectionTest.h"
    //#include"../../SttTest/Common/Gradient/SttPowerDirectionTest_I.h"
    #include"../../SttTest/Common/Gradient/SttPowerDirectionTest_Pnv.h"
    #include"../../SttTest/Common/Gradient/SttULockOverCurrentTest.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowFreqActTest.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowFreqDfDtTest.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowFreqILockTest.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowFreqTimeTest.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowFreqULockTest.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowVolActTest.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowVolDvDtTest.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowVolTimeTest.h"
	#include"../../SttTest/Common/LowFreqLowVol/SttLowVolILockTest.h"
#include"../../SttTest/Common/LowFreqLowVol/SttLowVolActTest_Pnv.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowVolTimeTest_Pnv.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowVolDvDtTest_Pnv.h"

    #include"../../SttTest/Common/Diff/SttDiffCbopTest.h"
    #include"../../SttTest/Common/Diff/SttDiffCurrThrTest.h"
    #include"../../SttTest/Common/Diff/SttDiffCurrRateTest.h"
    #include"../../SttTest/Common/Diff/SttDiffCurrQuickTest.h"
    #include"../../SttTest/Common/Diff/SttDiffCurrHarmTest.h"
    #include"../../SttTest/Common/Diff/SttDiffCurrHarmTest_I.h"
    #include"../../SttTest/Common/Diff/SttDiffActTimeTest.h"

    #include"../../SttTest/Common/Diff/SttElecRailwayDiffThrTest.h"
    #include"../../SttTest/Common/Diff/SttElecRailwayDiffRateTest.h"
    #include"../../SttTest/Common/Diff/SttElecRailwayDiffQuickTest.h"
    #include"../../SttTest/Common/Diff/SttElecRailwayDiffHarmTest.h"
    #include"../../SttTest/Common/Diff/SttElecRailwayDiffActTimeTest.h"

    #include"../../SttTest/Common/Diff/ManuDiff/SttManuDiffCurrThrTest.h"
    #include"../../SttTest/Common/Diff/ManuDiff/SttManuDiffCurrRateTest.h"
    #include"../../SttTest/Common/Diff/ManuDiff/SttManuDiffCurrQuickTest.h"
    #include"../../SttTest/Common/Diff/ManuDiff/SttManuDiffCurrHarmTest.h"

    #include"../../SttTest/Common/Diff/BP2_Diff/SttBP2DiffThrTest.h"
    #include"../../SttTest/Common/Diff/BP2_Diff/SttBP2DiffRateTest.h"
    #include"../../SttTest/Common/Diff/BP2_Diff/SttBP2CBOperateTest.h"

    #include"../../SttTest/Common/ActionTime/SttVolInverseTimeTest.h"
    #include"../../SttTest/Common/ActionTime/SttVFInverseTimeTest.h"

    #include"../../SttTest/Common/Swing/SttSwingTest.h"
    #include"../../SttTest/Common/Syn/SttSynActVolTest.h"
    #include"../../SttTest/Common/Syn/SttSynActFreqTest.h"
    #include"../../SttTest/Common/Syn/SttSynAdjVolTest.h"
    #include"../../SttTest/Common/Syn/SttSynAdjFreqTest.h"
    #include"../../SttTest/Common/Syn/SttSynAutoAdjTest.h"
    #include"../../SttTest/Common/Syn/SttSynLeadAngleTest.h"

    #include"../../SttTest/Common/SttAuxDCOutput.h"
	#include"../../SttTest/Common/SttUartConfig.h"
    #include"../../SttTest/Common/SttModulesGearSwitch.h"
    #include "../../SttTest/Common/Abnormal/SttSmvAbnormalTest.h"
    #include "../../SttTest/Common/Abnormal/SttGseAbnormalTest.h"

    #include "../../SttTest/Common/Iec/SttIecDetect.h"
    #include "../../SttTest/Common/Iec/SttIecRecord.h"

    #include"../../SttTest/Common/Gradient/SttCurrentActValueTest.h"
    #include"../../SttTest/Common/Gradient/SttVolActValueTest.h"
    #include"../../SttTest/Common/Gradient/SttCurrentActValueTest_Pnv.h"
    #include"../../SttTest/Common/Gradient/SttVolActValueTest_Pnv.h"
	#include"../../SttTest/Common/Gradient/SttFaultGradientTest.h"

    #include"../../SttTest/Common/DC/SttDCOverCurrentTest.h"
    #include"../../SttTest/Common/DC/SttDCOverLoadTest.h"
    #include"../../SttTest/Common/DC/SttDCVoltageTest.h"

    #include"../../SttTest/Common/AC/SttOverLoadTest.h"

    #include"../../SttTest/Common/DC/SttDCBreakTest.h"
    #include"../../SttTest/Common/DC/SttFailureProtActValue.h"
    #include"../../SttTest/Common/DC/SttFailureProtActTime.h"
    #include"../../SttTest/Common/DC/SttFailureDidtActValue.h"
    #include"../../SttTest/Common/DC/SttFailureDidtActTime.h"
    #include"../../SttTest/Common/DC/SttDCUnbalanceTest.h"
    #include"../../SttTest/Common/DC/SttDCDiffCurrThrTest.h"
    #include"../../SttTest/Common/DC/SttDCDiffCurrRateTest.h"
    #include"../../SttTest/Common/DC/SttDCDiffActTimeTest.h"
    #include"../../SttTest/Common/SttShortTimeOverTest.h"

	#include"../../SttTest/Common/SttLcPowerTest.h"
	#include"../../SttTest/Common/BinaryTest/SttBinaryManuTest.h"
	#include"../../SttTest/Common/BinaryTest/SttBinaryStateTest.h"

    #include"../../SttTest/Common/Diff/SttDiff6IHarmTest_Pnv.h"
    #include"../../SttTest/Common/Diff/SttDiff6IRateTest_Pnv.h"
    #include"../../SttTest/Common/Diff/SttDiff6IRateRestrainTest_Pnv.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowFreqTimeTest_Pnv.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowFreqActTest_Pnv.h"
    #include"../../SttTest/Common/LowFreqLowVol/SttLowFreqDfDtTest_Pnv.h"

    #include"../../SttTest/Common/Sequence/SttSequenceGradientTest_Pnv.h"
    #include"../../SttTest/Common/Manual/SttManuaImpedTest.h"
    #include"../../SttTest/Common/Manual/SttManualPowerTest.h"
#endif
CSttTestFactoryCom::CSttTestFactoryCom()
{
    m_strPxAppID_Relay = "relay";
    m_strPxAppName_Relay = "继保测试仪";
}

CSttTestFactoryCom::~CSttTestFactoryCom()
{
}

void CSttTestFactoryCom::RegisterInit()
{
	//SetParameter时不更新g_pCSttServerTestCtrlCntr->m_pCurrSttTest
	m_oMacroIDGroup.AddNewData(CSttAuxDCOutput::m_strMacroID,"");
	m_oMacroIDGroup.AddNewData(CSttIecDetect::m_strMacroID,"");
	m_oMacroIDGroup.AddNewData(CSttIecRecord::m_strMacroID,"");
	m_oMacroIDGroup.AddNewData(_T("PIP150Test"),"");
	m_oMacroIDGroup.AddNewData(CSttLcPowerTest::m_strMacroID,"");
    //m_oMacroIDGroup.AddNewData(CSttUartConfig::m_strMacroID,"");
	//

    RegisterTestMacro(m_strPxAppID_Relay, CSttChMapsConfig::m_strMacroName, CSttChMapsConfig::m_strMacroID, CSttChMapsConfig::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CIec61850Config::m_strMacroName, CIec61850Config::m_strMacroID, CIec61850Config::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, _T("IECConfig"), _T("IECConfig"), CIec61850Config::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttAdjust_ModuleOutput::m_strMacroName, CSttAdjust_ModuleOutput::m_strMacroID, CSttAdjust_ModuleOutput::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttAdjust_BinaryOutput::m_strMacroName, CSttAdjust_BinaryOutput::m_strMacroID, CSttAdjust_BinaryOutput::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttAdjust_BinaryExOutput::m_strMacroName, CSttAdjust_BinaryExOutput::m_strMacroID, CSttAdjust_BinaryExOutput::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttAdjust_RegisterTest::m_strMacroName, CSttAdjust_RegisterTest::m_strMacroID, CSttAdjust_RegisterTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttStateTest::m_strMacroName, CSttStateTest::m_strMacroID, CSttStateTest::CreateTest);//"StateTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttGradientTest::m_strMacroName, CSttGradientTest::m_strMacroID, CSttGradientTest::CreateTest);//"GradientTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttGradientMaxAngleTest::m_strMacroName, CSttGradientMaxAngleTest::m_strMacroID, CSttGradientMaxAngleTest::CreateTest);//"GradientMaxAngleTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttURampTest::m_strMacroName, CSttURampTest::m_strMacroID, CSttURampTest::CreateTest);//"GradientU"
    RegisterTestMacro(m_strPxAppID_Relay, CSttIRampTest::m_strMacroName, CSttIRampTest::m_strMacroID, CSttIRampTest::CreateTest);//"GradientI"
    RegisterTestMacro(m_strPxAppID_Relay, CSttManuTest::m_strMacroName, CSttManuTest::m_strMacroID, CSttManuTest::CreateTest);//"ManualTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttSequenceManuTest::m_strMacroName, CSttSequenceManuTest::m_strMacroID, CSttSequenceManuTest::CreateTest);//"SttSequenceManuTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttSequenceGradientTest::m_strMacroName, CSttSequenceGradientTest::m_strMacroID, CSttSequenceGradientTest::CreateTest);//"SequenceGradient"
    RegisterTestMacro(m_strPxAppID_Relay, CSttLineVoltManuTest::m_strMacroName, CSttLineVoltManuTest::m_strMacroID, CSttLineVoltManuTest::CreateTest);//"LineVoltManualTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttLineVoltGradientTest::m_strMacroName, CSttLineVoltGradientTest::m_strMacroID, CSttLineVoltGradientTest::CreateTest);//"LineVoltGradient"
    RegisterTestMacro(m_strPxAppID_Relay, CSttHarmTest::m_strMacroName, CSttHarmTest::m_strMacroID, CSttHarmTest::CreateTest);//"HarmTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttReplayTest::m_strMacroName, CSttReplayTest::m_strMacroID, CSttReplayTest::CreateTest);//"ReplayTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttSoeTest::m_strMacroName, CSttSoeTest::m_strMacroID, CSttSoeTest::CreateTest);//"SoeTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttSmvAbnTest::m_strMacroName, CSttSmvAbnTest::m_strMacroID, CSttSmvAbnTest::CreateTest);//"SmvAbnTest"
    RegisterTestMacro(m_strPxAppID_Relay, CSttGseAbnTest::m_strMacroName, CSttGseAbnTest::m_strMacroID, CSttGseAbnTest::CreateTest);//"GseAbnTest"
    //兼容模板
	RegisterTestMacro(m_strPxAppID_Relay, _T("State18U18I"), _T("State18U18I"), CSttStateTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, _T("PsuManualTest"), _T("PsuManualTest"), CSttManuTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, _T("MUAccuracyTest"), _T("MUAccuracyTest"), CSttMUAccuracyTest::CreateTest);//20220812 zhouhj
	RegisterTestMacro(m_strPxAppID_Relay, _T("MUHarmTest"), _T("MUHarmTest"), CSttMUHarmTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, _T("MUZeroDriftTest"), _T("MUZeroDriftTest"), CSttManuTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, _T("MUTimingAccurTest"), _T("MUTimingAccurTest"), CSttManuTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, _T("MUPunctAccurTest"), _T("MUPunctAccurTest"), CSttManuTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, _T("PsuHarmTest"), _T("PsuHarmTest"), CSttHarmTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttUITest12U12I_Pnv::m_strMacroName, CSttUITest12U12I_Pnv::m_strMacroID, CSttUITest12U12I_Pnv::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttState6U6I_Pnv::m_strMacroName, CSttState6U6I_Pnv::m_strMacroID, CSttState6U6I_Pnv::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttState4U3I_Pnv::m_strMacroName, CSttState4U3I_Pnv::m_strMacroID, CSttState4U3I_Pnv::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiffCoefPnvTest::m_strMacroName, CSttDiffCoefPnvTest::m_strMacroID, CSttDiffCoefPnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttPsuStateTest::m_strMacroName, CSttPsuStateTest::m_strMacroID, CSttPsuStateTest::CreateTest);

    //高级实验
    RegisterTestMacro(m_strPxAppID_Relay, CSttCBOperateTest::m_strMacroName, CSttCBOperateTest::m_strMacroID, CSttCBOperateTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDisTanceSearchTest::m_strMacroName, CSttDisTanceSearchTest::m_strMacroID, CSttDisTanceSearchTest::CreateTest);
    //RegisterTestMacro(m_strPxAppID_Relay, CSttDisTanceSearchTest_I::m_strMacroName, CSttDisTanceSearchTest_I::m_strMacroID, CSttDisTanceSearchTest_I::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDisTanceTest::m_strMacroName, CSttDisTanceTest::m_strMacroID, CSttDisTanceTest::CreateTest);
    //RegisterTestMacro(m_strPxAppID_Relay, CSttDisTanceTest_I::m_strMacroName, CSttDisTanceTest_I::m_strMacroID, CSttDisTanceTest_I::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttOverCurrentTest::m_strMacroName, CSttOverCurrentTest::m_strMacroID, CSttOverCurrentTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttOverVoltageTest::m_strMacroName, CSttOverVoltageTest::m_strMacroID, CSttOverVoltageTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttOverLoadTest::m_strMacroName, CSttOverLoadTest::m_strMacroID, CSttOverLoadTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttRecloseAccTest::m_strMacroName, CSttRecloseAccTest::m_strMacroID, CSttRecloseAccTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttStateRecloseAccTest::m_strMacroName, CSttStateRecloseAccTest::m_strMacroID, CSttStateRecloseAccTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttTURecloseAccTest::m_strMacroName, CSttTURecloseAccTest::m_strMacroID, CSttTURecloseAccTest::CreateTest);//用于配电终端自动测试
	RegisterTestMacro(m_strPxAppID_Relay, CSttStateOverCurrentTest::m_strMacroName, CSttStateOverCurrentTest::m_strMacroID, CSttStateOverCurrentTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttZeroCurrentTest::m_strMacroName, CSttZeroCurrentTest::m_strMacroID, CSttZeroCurrentTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttStateZeroCurrentTest::m_strMacroName, CSttStateZeroCurrentTest::m_strMacroID, CSttStateZeroCurrentTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttPowerFreqTest::m_strMacroName, CSttPowerFreqTest::m_strMacroID, CSttPowerFreqTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttActionTimeTest::m_strMacroName, CSttActionTimeTest::m_strMacroID, CSttActionTimeTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttPowerDirectionTest::m_strMacroName, CSttPowerDirectionTest::m_strMacroID, CSttPowerDirectionTest::CreateTest);
    //RegisterTestMacro(m_strPxAppID_Relay, CSttPowerDirectionTest_I::m_strMacroName, CSttPowerDirectionTest_I::m_strMacroID, CSttPowerDirectionTest_I::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttULockOverCurrentTest::m_strMacroName, CSttULockOverCurrentTest::m_strMacroID, CSttULockOverCurrentTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttFaultGradientTest::m_strMacroName, CSttFaultGradientTest::m_strMacroID, CSttFaultGradientTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttLowFreqActTest::m_strMacroName, CSttLowFreqActTest::m_strMacroID, CSttLowFreqActTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowFreqDfDtTest::m_strMacroName, CSttLowFreqDfDtTest::m_strMacroID, CSttLowFreqDfDtTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowFreqILockTest::m_strMacroName, CSttLowFreqILockTest::m_strMacroID, CSttLowFreqILockTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowFreqTimeTest::m_strMacroName, CSttLowFreqTimeTest::m_strMacroID, CSttLowFreqTimeTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowFreqULockTest::m_strMacroName, CSttLowFreqULockTest::m_strMacroID, CSttLowFreqULockTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowVolActTest::m_strMacroName, CSttLowVolActTest::m_strMacroID, CSttLowVolActTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowVolTimeTest::m_strMacroName, CSttLowVolTimeTest::m_strMacroID, CSttLowVolTimeTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowVolDvDtTest::m_strMacroName, CSttLowVolDvDtTest::m_strMacroID, CSttLowVolDvDtTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttLowVolILockTest::m_strMacroName, CSttLowVolILockTest::m_strMacroID, CSttLowVolILockTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiffCbopTest::m_strMacroName, CSttDiffCbopTest::m_strMacroID, CSttDiffCbopTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiffCurrThrTest::m_strMacroName, CSttDiffCurrThrTest::m_strMacroID, CSttDiffCurrThrTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiffCurrRateTest::m_strMacroName, CSttDiffCurrRateTest::m_strMacroID, CSttDiffCurrRateTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiffCurrQuickTest::m_strMacroName, CSttDiffCurrQuickTest::m_strMacroID, CSttDiffCurrQuickTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiffCurrHarmTest::m_strMacroName, CSttDiffCurrHarmTest::m_strMacroID, CSttDiffCurrHarmTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiffCurrHarmTest_I::m_strMacroName, CSttDiffCurrHarmTest_I::m_strMacroID, CSttDiffCurrHarmTest_I::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiffActTimeTest::m_strMacroName, CSttDiffActTimeTest::m_strMacroID, CSttDiffActTimeTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttElecRailwayDiffThrTest::m_strMacroName, CSttElecRailwayDiffThrTest::m_strMacroID, CSttElecRailwayDiffThrTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttElecRailwayDiffRateTest::m_strMacroName, CSttElecRailwayDiffRateTest::m_strMacroID, CSttElecRailwayDiffRateTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttElecRailwayDiffQuickTest::m_strMacroName, CSttElecRailwayDiffQuickTest::m_strMacroID, CSttElecRailwayDiffQuickTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttElecRailwayDiffHarmTest::m_strMacroName, CSttElecRailwayDiffHarmTest::m_strMacroID, CSttElecRailwayDiffHarmTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttElecRailwayDiffActTimeTest::m_strMacroName, CSttElecRailwayDiffActTimeTest::m_strMacroID, CSttElecRailwayDiffActTimeTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttSwingTest::m_strMacroName, CSttSwingTest::m_strMacroID, CSttSwingTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttSynActVolTest::m_strMacroName, CSttSynActVolTest::m_strMacroID, CSttSynActVolTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttSynActFreqTest::m_strMacroName, CSttSynActFreqTest::m_strMacroID, CSttSynActFreqTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttSynAdjVolTest::m_strMacroName, CSttSynAdjVolTest::m_strMacroID, CSttSynAdjVolTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttSynAdjFreqTest::m_strMacroName, CSttSynAdjFreqTest::m_strMacroID, CSttSynAdjFreqTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttSynAutoAdjTest::m_strMacroName, CSttSynAutoAdjTest::m_strMacroID, CSttSynAutoAdjTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttSynLeadAngleTest::m_strMacroName, CSttSynLeadAngleTest::m_strMacroID, CSttSynLeadAngleTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttAuxDCOutput::m_strMacroName, CSttAuxDCOutput::m_strMacroID, CSttAuxDCOutput::CreateTest);
    //RegisterTestMacro(m_strPxAppID_Relay, CSttUartConfig::m_strMacroName, CSttUartConfig::m_strMacroID, CSttUartConfig::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttModulesGearSwitch::m_strMacroName, CSttModulesGearSwitch::m_strMacroID, CSttModulesGearSwitch::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttManuDiffCurrThrTest::m_strMacroName, CSttManuDiffCurrThrTest::m_strMacroID, CSttManuDiffCurrThrTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttManuDiffCurrRateTest::m_strMacroName, CSttManuDiffCurrRateTest::m_strMacroID, CSttManuDiffCurrRateTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttManuDiffCurrQuickTest::m_strMacroName, CSttManuDiffCurrQuickTest::m_strMacroID, CSttManuDiffCurrQuickTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttManuDiffCurrHarmTest::m_strMacroName, CSttManuDiffCurrHarmTest::m_strMacroID, CSttManuDiffCurrHarmTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttManuaImpedTest::m_strMacroName, CSttManuaImpedTest::m_strMacroID, CSttManuaImpedTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttManualPowerTest::m_strMacroName, CSttManualPowerTest::m_strMacroID, CSttManualPowerTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttBP2DiffThrTest::m_strMacroName, CSttBP2DiffThrTest::m_strMacroID, CSttBP2DiffThrTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttBP2DiffRateTest::m_strMacroName, CSttBP2DiffRateTest::m_strMacroID, CSttBP2DiffRateTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttBP2CBOperateTest::m_strMacroName, CSttBP2CBOperateTest::m_strMacroID, CSttBP2CBOperateTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttVolInverseTimeTest::m_strMacroName, CSttVolInverseTimeTest::m_strMacroID, CSttVolInverseTimeTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttVFInverseTimeTest::m_strMacroName, CSttVFInverseTimeTest::m_strMacroID, CSttVFInverseTimeTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttIecDetect::m_strMacroName, CSttIecDetect::m_strMacroID, CSttIecDetect::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttIecRecord::m_strMacroName, CSttIecRecord::m_strMacroID, CSttIecRecord::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttCurrentActValueTest::m_strMacroName, CSttCurrentActValueTest::m_strMacroID, CSttCurrentActValueTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttVolActValueTest::m_strMacroName, CSttVolActValueTest::m_strMacroID, CSttVolActValueTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttVolActValuePnvTest::m_strMacroName, CSttVolActValuePnvTest::m_strMacroID, CSttVolActValuePnvTest::CreateTest);
    //RegisterTestMacro(m_strPxAppID_Relay, CSttCurrentActValuePnvTest::m_strMacroName, CSttCurrentActValuePnvTest::m_strMacroID, CSttCurrentActValuePnvTest::CreateTest);
    //DC
    RegisterTestMacro(m_strPxAppID_Relay, CSttDCOverCurrentTest::m_strMacroName, CSttDCOverCurrentTest::m_strMacroID, CSttDCOverCurrentTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDCOverLoadTest::m_strMacroName, CSttDCOverLoadTest::m_strMacroID, CSttDCOverLoadTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDCVoltageTest::m_strMacroName, CSttDCVoltageTest::m_strMacroID, CSttDCVoltageTest::CreateTest);

    RegisterTestMacro(m_strPxAppID_Relay, CSttDCBreakTest::m_strMacroName, CSttDCBreakTest::m_strMacroID, CSttDCBreakTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttFailureProtActValue::m_strMacroName, CSttFailureProtActValue::m_strMacroID, CSttFailureProtActValue::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttFailureProtActTime::m_strMacroName, CSttFailureProtActTime::m_strMacroID, CSttFailureProtActTime::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttFailureDidtActValue::m_strMacroName, CSttFailureDidtActValue::m_strMacroID, CSttFailureDidtActValue::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttFailureDidtActTime::m_strMacroName, CSttFailureDidtActTime::m_strMacroID, CSttFailureDidtActTime::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDCUnbalanceTest::m_strMacroName, CSttDCUnbalanceTest::m_strMacroID, CSttDCUnbalanceTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDCDiffCurrThrTest::m_strMacroName, CSttDCDiffCurrThrTest::m_strMacroID, CSttDCDiffCurrThrTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDCDiffCurrRateTest::m_strMacroName, CSttDCDiffCurrRateTest::m_strMacroID, CSttDCDiffCurrRateTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDCDiffActTimeTest::m_strMacroName, CSttDCDiffActTimeTest::m_strMacroID, CSttDCDiffActTimeTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttShortTimeOverTest::m_strMacroName, CSttShortTimeOverTest::m_strMacroID, CSttShortTimeOverTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttBinaryManuTest::m_strMacroName, CSttBinaryManuTest::m_strMacroID, CSttBinaryManuTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttBinaryStateTest::m_strMacroName, CSttBinaryStateTest::m_strMacroID, CSttBinaryStateTest::CreateTest);
	RegisterTestMacro(m_strPxAppID_Relay, CSttLcPowerTest::m_strMacroName, CSttLcPowerTest::m_strMacroID, CSttLcPowerTest::CreateTest);

    RegisterTestMacro(m_strPxAppID_Relay, CSttDiff6IHarmPnvTest::m_strMacroName, CSttDiff6IHarmPnvTest::m_strMacroID, CSttDiff6IHarmPnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiff6IRatePnvTest::m_strMacroName, CSttDiff6IRatePnvTest::m_strMacroID, CSttDiff6IRatePnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttDiff6IRateRestrainTest::m_strMacroName, CSttDiff6IRateRestrainTest::m_strMacroID, CSttDiff6IRateRestrainTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowFreqTimePnvTest::m_strMacroName, CSttLowFreqTimePnvTest::m_strMacroID, CSttLowFreqTimePnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowFreqActPnvTest::m_strMacroName, CSttLowFreqActPnvTest::m_strMacroID, CSttLowFreqActPnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowFreqDfDtPnvTest::m_strMacroName, CSttLowFreqDfDtPnvTest::m_strMacroID, CSttLowFreqDfDtPnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttSequenceGradientPnvTest::m_strMacroName, CSttSequenceGradientPnvTest::m_strMacroID, CSttSequenceGradientPnvTest::CreateTest);
    //RegisterTestMacro(m_strPxAppID_Relay, CSttPowerDirectionPnvTest::m_strMacroName, CSttPowerDirectionPnvTest::m_strMacroID, CSttPowerDirectionPnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowVolActPnvTest::m_strMacroName, CSttLowVolActPnvTest::m_strMacroID, CSttLowVolActPnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowVolTimePnvTest::m_strMacroName, CSttLowVolTimePnvTest::m_strMacroID, CSttLowVolTimePnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttLowVolDvDtPnvTest::m_strMacroName, CSttLowVolDvDtPnvTest::m_strMacroID, CSttLowVolDvDtPnvTest::CreateTest);
    RegisterTestMacro(m_strPxAppID_Relay, CSttVoltagePnvTest::m_strMacroName, CSttVoltagePnvTest::m_strMacroID, CSttVoltagePnvTest::CreateTest);

}
