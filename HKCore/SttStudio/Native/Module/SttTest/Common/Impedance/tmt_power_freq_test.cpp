#include "stdafx.h"
#include "tmt_power_freq_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_PowerFreqParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_PowerFreqParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_PowerFreqParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_PowerFreqParasEx));
	pParas->init();
}

void stt_init_results(tmt_PowerFreqResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_PowerFreqResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_PowerFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.26 caoxc 增加项目名称
	pXmlSierialize->xml_serialize("项目名称", "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("故障类型", "FaultType1", "", "NegFault", pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("计算系数", "CalCoef", "", "number", pParas->m_fCalCoef);
	pXmlSierialize->xml_serialize("短路阻抗角", "Z1Ph", "°", "number",pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize("短路电流", "ISet1", "A", "set",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("故障性质","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize("最大故障时间", "TSet1", "s", "set",pParas->m_fTSetting);

	pXmlSierialize->xml_serialize("故障前时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("保护动作后持续时间(s)", "TAfterTrig1", "s", "number", pParas->m_fPostFaultTime);

	//整定值参数
	pXmlSierialize->xml_serialize("工频变化量阻抗定值","DZset","Ω","number",pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("正序灵敏角","PHLM","°","number",pParas->m_fPostSensAngle);
	pXmlSierialize->xml_serialize("接地距离偏移角","PHPYXD","°","number",pParas->m_fOffsetAngleLN);
	pXmlSierialize->xml_serialize("相间距离偏移角","PHPYXX","°","number",pParas->m_fOffsetAngleLL);
	pXmlSierialize->xml_serialize("零序补偿系数","KO","","number",pParas->m_fK0Amp);

	pXmlSierialize->xml_serialize("故障触发方式","FaultTrigMode","","number",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize("GPS触发时刻（时）", "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize("GPS触发时刻（分）", "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize("GPS触发时刻（秒）", "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize("PT安装位置","PTPos","","PTPosition",pParas->m_nPTPoint);
	pXmlSierialize->xml_serialize("CT正极性","CTPos","","CTPos",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize("是否模拟断路器延时","SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("断路器跳闸延时","BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("断路器合闸延时","BrkCloseTime","s","number",pParas->m_fCBCloseTime);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	pXmlSierialize->xml_serialize("开出翻转控制方式", "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize("开出翻转延时", "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
	pXmlSierialize->xml_serialize("开出保持时间","_OutputKeepTime","s","number",pParas->m_fBoutHoldTime);
	pXmlSierialize->xml_serialize("常态开出1状态","_B01","","DOutputState",pParas->m_nStateBOut[0]);
	pXmlSierialize->xml_serialize("常态开出2状态","_B02","","DOutputState",pParas->m_nStateBOut[1]);
	pXmlSierialize->xml_serialize("常态开出3状态","_B03","","DOutputState",pParas->m_nStateBOut[2]);
	pXmlSierialize->xml_serialize("常态开出4状态","_B04","","DOutputState",pParas->m_nStateBOut[3]);
	pXmlSierialize->xml_serialize("常态开出5状态","_B05","","DOutputState",pParas->m_nStateBOut[4]);
	pXmlSierialize->xml_serialize("常态开出6状态","_B06","","DOutputState",pParas->m_nStateBOut[5]);
	pXmlSierialize->xml_serialize("常态开出7状态","_B07","","DOutputState",pParas->m_nStateBOut[6]);
	pXmlSierialize->xml_serialize("常态开出8状态","_B08","","DOutputState",pParas->m_nStateBOut[7]);

	pXmlSierialize->xml_serialize("开入A","A","","DInputState",pParas->m_nDInputState[0]);
	pXmlSierialize->xml_serialize("开入B","B","","DInputState",pParas->m_nDInputState[1]);
	pXmlSierialize->xml_serialize("开入C","C","","DInputState",pParas->m_nDInputState[2]);
	pXmlSierialize->xml_serialize("开入R","R","","DInputState",pParas->m_nDInputState[3]);
	pXmlSierialize->xml_serialize("开入E","E","","DInputState",pParas->m_nDInputState[4]);
	pXmlSierialize->xml_serialize("开入F","F","","DInputState",pParas->m_nDInputState[5]);
	pXmlSierialize->xml_serialize("开入G","G","","DInputState",pParas->m_nDInputState[6]);
	pXmlSierialize->xml_serialize("开入H","H","","DInputState",pParas->m_nDInputState[7]);
	pXmlSierialize->xml_serialize("开入量选择","BinSelect","","BinSelect",pParas->m_nBinSelect);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		//兼容以前接口程序处理
		pXmlSierialize->xml_serialize("GPS触发时刻（时）", "GpsH"," ","number",pParas->m_tGps.nHour);
		pXmlSierialize->xml_serialize("GPS触发时刻（分）", "GpsM"," ","number",pParas->m_tGps.nMinutes);
		pXmlSierialize->xml_serialize("GPS触发时刻（秒）", "GpsS"," ","number",pParas->m_tGps.nSeconds);
		pXmlSierialize->xml_serialize("开入量选择","_BinSelect","","BinSelect",pParas->m_nBinSelect);

		pXmlSierialize->xml_serialize("开入A","_BinAMode","","DInputState",pParas->m_nDInputState[0]);
		pXmlSierialize->xml_serialize("开入B","_BinBMode","","DInputState",pParas->m_nDInputState[1]);
		pXmlSierialize->xml_serialize("开入C","_BinCMode","","DInputState",pParas->m_nDInputState[2]);
		pXmlSierialize->xml_serialize("开入R","_BinDMode","","DInputState",pParas->m_nDInputState[3]);
		pXmlSierialize->xml_serialize("开入E","_BinEMode","","DInputState",pParas->m_nDInputState[4]);
		pXmlSierialize->xml_serialize("开入F","_BinFMode","","DInputState",pParas->m_nDInputState[5]);
		pXmlSierialize->xml_serialize("开入G","_BinGMode","","DInputState",pParas->m_nDInputState[6]);
		pXmlSierialize->xml_serialize("开入H","_BinHMode","","DInputState",pParas->m_nDInputState[7]);
	}
#else
	//2022.5.26 caoxc 增加项目名称
	pXmlSierialize->xml_serialize(/* "项目名称" */g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType1", "", "NegFault", pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "计算系数" */g_sLangTxt_Native_CalcCoef.GetString(), "CalCoef", "", "number", pParas->m_fCalCoef);
	pXmlSierialize->xml_serialize(/* "短路阻抗角" */g_sLangTxt_Native_ShortZImpAng.GetString(), "Z1Ph", "°", "number",pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize(/* "短路电流" */g_sLangTxt_Native_ShortCircuit.GetString(), "ISet1", "A", "set",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "故障方向" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "故障性质" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize(/* "最大故障时间" */g_sLangTxt_Native_MaxTimeMalf.GetString(), "TSet1", "s", "set",pParas->m_fTSetting);

	pXmlSierialize->xml_serialize(/* "故障前时间" */g_sLangTxt_Native_PreFautTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize(/* "保护动作后持续时间(s)" */g_sLangTxt_Native_DurProtTrip.GetString(), "TAfterTrig1", "s", "number", pParas->m_fPostFaultTime);

	//整定值参数
	pXmlSierialize->xml_serialize(/* "工频变化量阻抗定值" */g_sLangTxt_Native_FreqChgZSetting.GetString(),"DZset","Ω","number",pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "正序灵敏角" */g_sLangTxt_Native_PosSeqSensAng.GetString(),"PHLM","°","number",pParas->m_fPostSensAngle);
	pXmlSierialize->xml_serialize(/* "接地距离偏移角" */g_sLangTxt_Native_GndDistOffset.GetString(),"PHPYXD","°","number",pParas->m_fOffsetAngleLN);
	pXmlSierialize->xml_serialize(/* "相间距离偏移角" */g_sLangTxt_Native_PhaseDistOffset.GetString(),"PHPYXX","°","number",pParas->m_fOffsetAngleLL);
	pXmlSierialize->xml_serialize(/* "零序补偿系数" */g_sLangTxt_State_ZeroCoeff.GetString(),"KO","","number",pParas->m_fK0Amp);

	pXmlSierialize->xml_serialize(/* "故障触发方式" */g_sLangTxt_Native_FaultTrigMethod.GetString(),"FaultTrigMode","","number",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize(/* "GPS触发时刻（时）" */g_sLangTxt_Native_GPSTriggerHour.GetString(), "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize(/* "GPS触发时刻（分）" */g_sLangTxt_Native_GPSTriggerMinute.GetString(), "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize(/* "GPS触发时刻（秒）" */g_sLangTxt_Native_GPSTriggerSecond.GetString(), "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize(/* "PT安装位置" */g_sLangTxt_Native_PT_installPos.GetString(),"PTPos","","PTPosition",pParas->m_nPTPoint);
	pXmlSierialize->xml_serialize(/* "CT正极性" */g_sLangTxt_Native_CTPolarityPositive.GetString(),"CTPos","","CTPos",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize(/* "是否模拟断路器延时" */g_sLangTxt_Native_SimBrkDel.GetString(),"SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize(/* "断路器跳闸延时" */g_sLangTxt_Native_BrkTripDel.GetString(),"BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize(/* "断路器合闸延时" */g_sLangTxt_Native_BrkClsDel.GetString(),"BrkCloseTime","s","number",pParas->m_fCBCloseTime);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	pXmlSierialize->xml_serialize(/* "开出翻转控制方式" */g_sLangTxt_Native_openflip_Control.GetString(), "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize(/* "开出翻转延时" */g_sLangTxt_Native_openflip_delay.GetString(), "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
	pXmlSierialize->xml_serialize(/* "开出保持时间" */g_sLangTxt_Native_OutputHoldTimeS.GetString(),"_OutputKeepTime","s","number",pParas->m_fBoutHoldTime);
	pXmlSierialize->xml_serialize(/* "常态开出1状态" */g_sLangTxt_Native_NormalOpen1State.GetString(),"_B01","","DOutputState",pParas->m_nStateBOut[0]);
	pXmlSierialize->xml_serialize(/* "常态开出2状态" */g_sLangTxt_Native_NormalOpen2State.GetString(),"_B02","","DOutputState",pParas->m_nStateBOut[1]);
	pXmlSierialize->xml_serialize(/* "常态开出3状态" */g_sLangTxt_Native_NormalOpen3State.GetString(),"_B03","","DOutputState",pParas->m_nStateBOut[2]);
	pXmlSierialize->xml_serialize(/* "常态开出4状态" */g_sLangTxt_Native_NormalOpen4State.GetString(),"_B04","","DOutputState",pParas->m_nStateBOut[3]);
	pXmlSierialize->xml_serialize(/* "常态开出5状态" */g_sLangTxt_Native_NormalOpen5State.GetString(),"_B05","","DOutputState",pParas->m_nStateBOut[4]);
	pXmlSierialize->xml_serialize(/* "常态开出6状态" */g_sLangTxt_Native_NormalOpen6State.GetString(),"_B06","","DOutputState",pParas->m_nStateBOut[5]);
	pXmlSierialize->xml_serialize(/* "常态开出7状态" */g_sLangTxt_Native_NormalOpen7State.GetString(),"_B07","","DOutputState",pParas->m_nStateBOut[6]);
	pXmlSierialize->xml_serialize(/* "常态开出8状态" */g_sLangTxt_Native_NormalOpen8State.GetString(),"_B08","","DOutputState",pParas->m_nStateBOut[7]);

	pXmlSierialize->xml_serialize(/* "开入A" */g_sLangTxt_Manual_InA.GetString(),"A","","DInputState",pParas->m_nDInputState[0]);
	pXmlSierialize->xml_serialize(/* "开入B" */g_sLangTxt_Manual_InB.GetString(),"B","","DInputState",pParas->m_nDInputState[1]);
	pXmlSierialize->xml_serialize(/* "开入C" */g_sLangTxt_Manual_InC.GetString(),"C","","DInputState",pParas->m_nDInputState[2]);
	pXmlSierialize->xml_serialize(/* "开入R" */g_sLangTxt_Manual_InD.GetString(),"R","","DInputState",pParas->m_nDInputState[3]);
	pXmlSierialize->xml_serialize(/* "开入E" */g_sLangTxt_Manual_InE.GetString(),"E","","DInputState",pParas->m_nDInputState[4]);
	pXmlSierialize->xml_serialize(/* "开入F" */g_sLangTxt_Manual_InF.GetString(),"F","","DInputState",pParas->m_nDInputState[5]);
	pXmlSierialize->xml_serialize(/* "开入G" */g_sLangTxt_Manual_InG.GetString(),"G","","DInputState",pParas->m_nDInputState[6]);
	pXmlSierialize->xml_serialize(/* "开入H" */g_sLangTxt_Manual_InH.GetString(),"H","","DInputState",pParas->m_nDInputState[7]);
	pXmlSierialize->xml_serialize(/* "开入量选择" */g_sLangTxt_Native_input_selection.GetString(),"BinSelect","","BinSelect",pParas->m_nBinSelect);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		//兼容以前接口程序处理
		pXmlSierialize->xml_serialize(/* "GPS触发时刻（时）" */g_sLangTxt_Native_GPSTriggerHour.GetString(), "GpsH"," ","number",pParas->m_tGps.nHour);
		pXmlSierialize->xml_serialize(/* "GPS触发时刻（分）" */g_sLangTxt_Native_GPSTriggerMinute.GetString(), "GpsM"," ","number",pParas->m_tGps.nMinutes);
		pXmlSierialize->xml_serialize(/* "GPS触发时刻（秒）" */g_sLangTxt_Native_GPSTriggerSecond.GetString(), "GpsS"," ","number",pParas->m_tGps.nSeconds);
		pXmlSierialize->xml_serialize(/* "开入量选择" */g_sLangTxt_Native_input_selection.GetString(),"_BinSelect","","BinSelect",pParas->m_nBinSelect);

		pXmlSierialize->xml_serialize(/* "开入A" */g_sLangTxt_Manual_InA.GetString(),"_BinAMode","","DInputState",pParas->m_nDInputState[0]);
		pXmlSierialize->xml_serialize(/* "开入B" */g_sLangTxt_Manual_InB.GetString(),"_BinBMode","","DInputState",pParas->m_nDInputState[1]);
		pXmlSierialize->xml_serialize(/* "开入C" */g_sLangTxt_Manual_InC.GetString(),"_BinCMode","","DInputState",pParas->m_nDInputState[2]);
		pXmlSierialize->xml_serialize(/* "开入R" */g_sLangTxt_Manual_InD.GetString(),"_BinDMode","","DInputState",pParas->m_nDInputState[3]);
		pXmlSierialize->xml_serialize(/* "开入E" */g_sLangTxt_Manual_InE.GetString(),"_BinEMode","","DInputState",pParas->m_nDInputState[4]);
		pXmlSierialize->xml_serialize(/* "开入F" */g_sLangTxt_Manual_InF.GetString(),"_BinFMode","","DInputState",pParas->m_nDInputState[5]);
		pXmlSierialize->xml_serialize(/* "开入G" */g_sLangTxt_Manual_InG.GetString(),"_BinGMode","","DInputState",pParas->m_nDInputState[6]);
		pXmlSierialize->xml_serialize(/* "开入H" */g_sLangTxt_Manual_InH.GetString(),"_BinHMode","","DInputState",pParas->m_nDInputState[7]);
	}
#endif
	
}

void stt_xml_serialize_ex(tmt_PowerFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("短路阻抗角(表达式)", "Z1PhExp","","string",pParas->m_pszImpAngle);
#else
	pXmlSierialize->xml_serialize(/* "短路阻抗角(表达式)" */g_sLangTxt_Native_ShortZImpAngExp.GetString(), "Z1PhExp","","string",pParas->m_pszImpAngle);
#endif

	stt_xml_serialize(pParas,pXmlSierialize);
}


void stt_init_paras_LFPGP(tmt_PowerFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
// 	pXmlSierialize->xml_serialize("故障类型", "FaultType1", "", "NegFault", pParas->m_nFaultType[0]);
// 	pXmlSierialize->xml_serialize("计算系数", "CalCoef", "", "number", pParas->m_fCalCoef);
// 	pXmlSierialize->xml_serialize("短路阻抗角", "Z1Ph", "°", "number",pParas->m_fImpAngle[0]);
// 	pXmlSierialize->xml_serialize("短路电流", "ISet1", "A", "set",pParas->m_fSCCurrent[0]);
// 	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
// 	pXmlSierialize->xml_serialize("故障性质","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
// 	pXmlSierialize->xml_serialize("最大故障时间", "TSet1", "s", "set",pParas->m_fTSetting);
// 
// 	pXmlSierialize->xml_serialize("故障前时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);
// 	pXmlSierialize->xml_serialize("动作后延时", "TAfterTrig1", "s", "number", pParas->m_fPostFaultTime);
// 
// 	//整定值参数
// 	pXmlSierialize->xml_serialize("工频变化量阻抗定值","DZset","Ω","number",pParas->m_fSetting[0]);
// 	pXmlSierialize->xml_serialize("正序灵敏角","PHLM","°","number",pParas->m_fPostSensAngle);
// 	pXmlSierialize->xml_serialize("接地距离偏移角","PHPYXD","°","number",pParas->m_fOffsetAngleLN);
// 	pXmlSierialize->xml_serialize("相间距离偏移角","PHPYXX","°","number",pParas->m_fOffsetAngleLL);
// 	pXmlSierialize->xml_serialize("零序补偿系数","KO","","number",pParas->m_fK0Amp);
// 
// 	pXmlSierialize->xml_serialize("故障触发方式","FaultTrigMode","","number",pParas->m_nFaultTrigMode);
// 	pXmlSierialize->xml_serialize("GPS触发时刻（时）", "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
// 	pXmlSierialize->xml_serialize("GPS触发时刻（分）", "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
// 	pXmlSierialize->xml_serialize("GPS触发时刻（秒）", "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);
// 
// 	pXmlSierialize->xml_serialize("PT安装位置","PTPos","","PTPosition",pParas->m_nPTPoint);
// 	pXmlSierialize->xml_serialize("CT正极性","CTPos","","CTPos",pParas->m_nCTPoint);
// 	pXmlSierialize->xml_serialize("是否模拟断路器延时","SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
// 	pXmlSierialize->xml_serialize("断路器跳闸延时","BrkBreakTime","s","number",pParas->m_fCBTripTime);
// 	pXmlSierialize->xml_serialize("断路器合闸延时","BrkCloseTime","s","number",pParas->m_fCBCloseTime);
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 	pXmlSierialize->xml_serialize("开出翻转控制方式", "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
// 	pXmlSierialize->xml_serialize("开出翻转延时", "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
// 	pXmlSierialize->xml_serialize("开出保持时间","_OutputKeepTime","s","number",pParas->m_fBoutHoldTime);
// 	pXmlSierialize->xml_serialize("常态开出1状态","_B01","","DOutputState",pParas->m_nStateBOut[0]);
// 	pXmlSierialize->xml_serialize("常态开出2状态","_B02","","DOutputState",pParas->m_nStateBOut[1]);
// 	pXmlSierialize->xml_serialize("常态开出3状态","_B03","","DOutputState",pParas->m_nStateBOut[2]);
// 	pXmlSierialize->xml_serialize("常态开出4状态","_B04","","DOutputState",pParas->m_nStateBOut[3]);
// 	pXmlSierialize->xml_serialize("常态开出5状态","_B05","","DOutputState",pParas->m_nStateBOut[4]);
// 	pXmlSierialize->xml_serialize("常态开出6状态","_B06","","DOutputState",pParas->m_nStateBOut[5]);
// 	pXmlSierialize->xml_serialize("常态开出7状态","_B07","","DOutputState",pParas->m_nStateBOut[6]);
// 	pXmlSierialize->xml_serialize("常态开出8状态","_B08","","DOutputState",pParas->m_nStateBOut[7]);
// 
// 	pXmlSierialize->xml_serialize("开入A","A","","DInputState",pParas->m_nDInputState[0]);
// 	pXmlSierialize->xml_serialize("开入B","B","","DInputState",pParas->m_nDInputState[1]);
// 	pXmlSierialize->xml_serialize("开入C","C","","DInputState",pParas->m_nDInputState[2]);
// 	pXmlSierialize->xml_serialize("开入R","R","","DInputState",pParas->m_nDInputState[3]);
// 	pXmlSierialize->xml_serialize("开入E","E","","DInputState",pParas->m_nDInputState[4]);
// 	pXmlSierialize->xml_serialize("开入F","F","","DInputState",pParas->m_nDInputState[5]);
// 	pXmlSierialize->xml_serialize("开入G","G","","DInputState",pParas->m_nDInputState[6]);
// 	pXmlSierialize->xml_serialize("开入H","H","","DInputState",pParas->m_nDInputState[7]);
// 	pXmlSierialize->xml_serialize("开入量选择","BinSelect","","BinSelect",pParas->m_nBinSelect);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_PowerFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_PowerFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuPowerFreqDist) == 0)
		{
			stt_xml_serialize_ex(&(pTests->m_oPowerFreqParas), pXmlParas);	//文件的读写
		}
// 		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_LFPGP) == 0)
// 		{
// 			stt_xml_serialize(&(pTests->m_oPowerFreqParas), pXmlParas,nBinExNum,nBoutExNum);	//测试参数下发
// 		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
//		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuPowerFreqDist) == 0)
		{
			stt_xml_serialize(&pTests->m_oPowerFreqResults, pXmlResults);
		}
// 		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_LFPGP) == 0)
// 		{
// 			stt_xml_serialize(&pTests->m_oPowerFreqResults, pXmlResults,nBinExNum,nBoutExNum);
// 		}
	}

	return pXmlParas;
}
