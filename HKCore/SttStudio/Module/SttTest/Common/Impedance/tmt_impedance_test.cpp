#include "stdafx.h"
#include "tmt_impedance_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

#ifndef _STT_NOT_IN_TEST_SERVER_
#include "../SttSystemConfig.h"
#endif

void stt_xml_serialize_impedance_paras(tmt_ImpedanceParas *pParas, CSttXmlSerializeBase *pXmlSierialize,BOOL bImpBase)
{
#ifndef _STT_NOT_IN_TEST_SERVER_
	pXmlSierialize->xml_serialize("0-主板的开入开出，1-主板+扩展的开入开出","BinBoutMode","","long",g_theSystemConfig->m_nBinBoutMode);
#endif

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("故障时间裕度","FaultTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("故障前时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);

	pXmlSierialize->xml_serialize("故障触发方式","FaultTrigMode","","FaultTrigModePnv",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize("GPS触发时刻（时）", "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize("GPS触发时刻（分）", "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize("GPS触发时刻（秒）", "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize("零序补偿系数表达方式","K0Mode","无","ZeroCalMode",pParas->m_nK0CalMode);
	pXmlSierialize->xml_serialize("零序补偿系数RE/RL","KlKr","","number",pParas->m_fK0Amp);
	pXmlSierialize->xml_serialize("零序补偿系数XE/XL","AngKx","","number",pParas->m_fK0Angle);

	pXmlSierialize->xml_serialize("负荷电流", "ILoad", "A", "number",pParas->m_fIfh);
	pXmlSierialize->xml_serialize("负荷功角", "ILoadPh", "°", "number",pParas->m_fPowerAngle);

	pXmlSierialize->xml_serialize("PT安装位置","PTPos","","PTPosition",pParas->m_nPTPoint);
	pXmlSierialize->xml_serialize("CT正极性","CTPos","","CTPos",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize("是否模拟断路器延时","SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("断路器跳闸延时","BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("断路器合闸延时","BrkCloseTime","s","number",pParas->m_fCBCloseTime);

	pXmlSierialize->xml_serialize("是否叠加非周期分量","FaultId","s","BOOL",pParas->m_bIPlusDC);
//	pXmlSierialize->xml_serialize("衰减时间常数", "Tao","s","number",pParas->m_fTao);
	pXmlSierialize->xml_serialize("合闸角方式( 0-随机 1-定值)", "FaultAngMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
	pXmlSierialize->xml_serialize("合闸角", "FaultAng", "°", "number", pParas->m_fFaultAngle);
//	pXmlSierialize->xml_serialize("合闸角的起始值", "FaultAng_0", "°", "number", pParas->m_fFaultAng_0);


	if (bImpBase)
	{
		pXmlSierialize->xml_serialize("Vz输出定义", "VzDefine", "", "PsuVzDefine", pParas->m_nVzDefine);	
		pXmlSierialize->xml_serialize("Vz参考相", "VzPhDefine", "", "PsuVzRefPhase", pParas->m_nVzPhDefine);	
		pXmlSierialize->xml_serialize("Vz相角", "VzPh", "°", "number", pParas->m_fUxInput_Ang);	
	}
	else
	{
		pXmlSierialize->xml_serialize("重合闸时间定值","RecloseTime","s","set",pParas->m_fRecloseTime);
		pXmlSierialize->xml_serialize("后加速时间定值","AfterAcceTime","s","set",pParas->m_fAfterAcceTime);
		pXmlSierialize->xml_serialize("辅助电压Ux 输出方式", "UxMode", "", "UxMode", pParas->m_nVzDefine);	
		pXmlSierialize->xml_serialize("同期电压幅值(检同期方式有效)","UxInputMag","V","number",pParas->m_fUxInput_Mag);
		pXmlSierialize->xml_serialize("同期电压相位(检同期方式有效)","UxInputAng","°","number",pParas->m_fUxInput_Ang);
		pXmlSierialize->xml_serialize("有压测试值","UxHigh","V","number",pParas->m_fUxHigh);
		pXmlSierialize->xml_serialize("无压测试值","UxLow","V","number",pParas->m_fUxLow);
	}

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

		pXmlSierialize->xml_serialize("合闸角方式( 0-随机 1-定值)", "FaultIncMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
		pXmlSierialize->xml_serialize("是否叠加非周期分量","bIPlusDC","","BOOL",pParas->m_bIPlusDC);

		pXmlSierialize->xml_serialize("开入A","_BinAMode","","DInputState",pParas->m_nDInputState[0]);
		pXmlSierialize->xml_serialize("开入B","_BinBMode","","DInputState",pParas->m_nDInputState[1]);
		pXmlSierialize->xml_serialize("开入C","_BinCMode","","DInputState",pParas->m_nDInputState[2]);
		pXmlSierialize->xml_serialize("开入R","_BinDMode","","DInputState",pParas->m_nDInputState[3]);
		pXmlSierialize->xml_serialize("开入E","_BinEMode","","DInputState",pParas->m_nDInputState[4]);
		pXmlSierialize->xml_serialize("开入F","_BinFMode","","DInputState",pParas->m_nDInputState[5]);
		pXmlSierialize->xml_serialize("开入G","_BinGMode","","DInputState",pParas->m_nDInputState[6]);
		pXmlSierialize->xml_serialize("开入H","_BinHMode","","DInputState",pParas->m_nDInputState[7]);

        //Pnv新增兼容处理
        pXmlSierialize->xml_serialize("重合闸时间定值","RecloseTime","s","set",pParas->m_fRecloseTime);
        pXmlSierialize->xml_serialize("后加速时间定值","AfterAcceTime","s","set",pParas->m_fAfterAcceTime);
        pXmlSierialize->xml_serialize("辅助电压Ux 输出方式", "UxMode", "", "UxMode", pParas->m_nVzDefine);
        pXmlSierialize->xml_serialize("同期电压幅值(检同期方式有效)","UxInputMag","V","number",pParas->m_fUxInput_Mag);
        pXmlSierialize->xml_serialize("同期电压相位(检同期方式有效)","UxInputAng","°","number",pParas->m_fUxInput_Ang);
        pXmlSierialize->xml_serialize("有压测试值","UxHigh","V","number",pParas->m_fUxHigh);
        pXmlSierialize->xml_serialize("无压测试值","UxLow","V","number",pParas->m_fUxLow);
        pXmlSierialize->xml_serialize("合闸角选择( 0-随机 1-定值)", "FaultIncMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
        pXmlSierialize->xml_serialize("开入A使能","BinA","","DInputState",pParas->m_nDInputState[0]);
        pXmlSierialize->xml_serialize("开入B使能","BinB","","DInputState",pParas->m_nDInputState[1]);
        pXmlSierialize->xml_serialize("开入C使能","BinC","","DInputState",pParas->m_nDInputState[2]);
        pXmlSierialize->xml_serialize("开入R使能","BinR","","DInputState",pParas->m_nDInputState[3]);
        pXmlSierialize->xml_serialize("开入E使能","BinE","","DInputState",pParas->m_nDInputState[4]);
        pXmlSierialize->xml_serialize("开入F使能","BinF","","DInputState",pParas->m_nDInputState[5]);
        pXmlSierialize->xml_serialize("开入G使能","BinG","","DInputState",pParas->m_nDInputState[6]);
        pXmlSierialize->xml_serialize("开入H使能","BinH","","DInputState",pParas->m_nDInputState[7]);
        pXmlSierialize->xml_serialize("开入量选择","AndOr","","BinSelect",pParas->m_nBinSelect);
	}
#else
	pXmlSierialize->xml_serialize(/* "故障时间裕度" */g_sLangTxt_Native_FaultTimeMargin.GetString(),"FaultTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize(/* "故障前时间" */g_sLangTxt_Native_PreFautTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);

	pXmlSierialize->xml_serialize(/* "故障触发方式" */g_sLangTxt_Native_FaultTrigMethod.GetString(),"FaultTrigMode","","FaultTrigModePnv",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize(/* "GPS触发时刻（时）" */g_sLangTxt_Native_GPSTriggerHour.GetString(), "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize(/* "GPS触发时刻（分）" */g_sLangTxt_Native_GPSTriggerMinute.GetString(), "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize(/* "GPS触发时刻（秒）" */g_sLangTxt_Native_GPSTriggerSecond.GetString(), "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize(/* "零序补偿系数表达方式" */g_sLangTxt_Native_ZeroSeqCompExp.GetString(),"K0Mode",/* "无" */g_sLangTxt_without.GetString(),"ZeroCalMode",pParas->m_nK0CalMode);
	pXmlSierialize->xml_serialize(/* "零序补偿系数RE/RL" */g_sLangTxt_Native_ZeroSeqComp_RERL.GetString(),"KlKr","","number",pParas->m_fK0Amp);
	pXmlSierialize->xml_serialize(/* "零序补偿系数XE/XL" */g_sLangTxt_Native_ZeroSeqComp_XEXL.GetString(),"AngKx","","number",pParas->m_fK0Angle);

	pXmlSierialize->xml_serialize(/* "负荷电流" */g_sLangTxt_Native_load_current.GetString(), "ILoad", "A", "number",pParas->m_fIfh);
	pXmlSierialize->xml_serialize(/* "负荷功角" */g_sLangTxt_Native_loadpowerAng.GetString(), "ILoadPh", "°", "number",pParas->m_fPowerAngle);

	pXmlSierialize->xml_serialize(/* "PT安装位置" */g_sLangTxt_Native_PT_installPos.GetString(),"PTPos","","PTPosition",pParas->m_nPTPoint);
	pXmlSierialize->xml_serialize(/* "CT正极性" */g_sLangTxt_Native_CTPolarityPositive.GetString(),"CTPos","","CTPos",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize(/* "是否模拟断路器延时" */g_sLangTxt_Native_SimBrkDel.GetString(),"SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize(/* "断路器跳闸延时" */g_sLangTxt_Native_BrkTripDel.GetString(),"BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize(/* "断路器合闸延时" */g_sLangTxt_Native_BrkClsDel.GetString(),"BrkCloseTime","s","number",pParas->m_fCBCloseTime);

	pXmlSierialize->xml_serialize(/* "是否叠加非周期分量" */g_sLangTxt_Native_superimpose_ornot.GetString(),"FaultId","s","BOOL",pParas->m_bIPlusDC);
	//	pXmlSierialize->xml_serialize("衰减时间常数", "Tao","s","number",pParas->m_fTao);
	pXmlSierialize->xml_serialize(/* "合闸角方式( 0-随机 1-定值)" */g_sLangTxt_Native_closeAngmode01.GetString(), "FaultAngMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
	pXmlSierialize->xml_serialize(/* "合闸角" */g_sLangTxt_Native_closing_angle.GetString(), "FaultAng", "°", "number", pParas->m_fFaultAngle);
	//	pXmlSierialize->xml_serialize("合闸角的起始值", "FaultAng_0", "°", "number", pParas->m_fFaultAng_0);


	if (bImpBase)
	{
		pXmlSierialize->xml_serialize(/* "Vz输出定义" */g_sLangTxt_Native_Vz_outputDef.GetString(), "VzDefine", "", "PsuVzDefine", pParas->m_nVzDefine);	
		pXmlSierialize->xml_serialize(/* "Vz参考相" */g_sLangTxt_Native_Vz_referPhase.GetString(), "VzPhDefine", "", "PsuVzRefPhase", pParas->m_nVzPhDefine);	
		pXmlSierialize->xml_serialize(/* "Vz相角" */g_sLangTxt_Native_Vz_phase_angle.GetString(), "VzPh", "°", "number", pParas->m_fUxInput_Ang);	
	}
	else
	{
		pXmlSierialize->xml_serialize(/* "重合闸时间定值" */g_sLangTxt_Native_reclose_timeset.GetString(),"RecloseTime","s","set",pParas->m_fRecloseTime);
		pXmlSierialize->xml_serialize(/* "后加速时间定值" */g_sLangTxt_Native_PostAccelerat_TimeSet.GetString(),"AfterAcceTime","s","set",pParas->m_fAfterAcceTime);
		pXmlSierialize->xml_serialize(/* "辅助电压Ux 输出方式" */g_sLangTxt_Native_auxiV_UxoutputMode.GetString(), "UxMode", "", "UxMode", pParas->m_nVzDefine);	
		pXmlSierialize->xml_serialize(/* "同期电压幅值(检同期方式有效)" */g_sLangTxt_Native_synchronous_VAmp.GetString(),"UxInputMag","V","number",pParas->m_fUxInput_Mag);
		pXmlSierialize->xml_serialize(/* "同期电压相位(检同期方式有效)" */g_sLangTxt_Native_synchronous_VPh.GetString(),"UxInputAng","°","number",pParas->m_fUxInput_Ang);
		pXmlSierialize->xml_serialize(/* "有压测试值" */g_sLangTxt_Native_pressTestVal.GetString(),"UxHigh","V","number",pParas->m_fUxHigh);
		pXmlSierialize->xml_serialize(/* "无压测试值" */g_sLangTxt_Native_NOpressTestVal.GetString(),"UxLow","V","number",pParas->m_fUxLow);
	}

	pXmlSierialize->xml_serialize(/* "开出翻转控制方式" */g_sLangTxt_Native_openflip_Control.GetString(), "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize(/* "开出翻转延时" */g_sLangTxt_Native_FlipDelay.GetString(), "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
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

		pXmlSierialize->xml_serialize(/* "合闸角方式( 0-随机 1-定值)" */g_sLangTxt_Native_closeAngmode01.GetString(), "FaultIncMode", "", "FaultAngModePnv",pParas->m_nFaultIncMode);
		pXmlSierialize->xml_serialize(/* "是否叠加非周期分量" */g_sLangTxt_Native_superimposed_ornot1.GetString(),"bIPlusDC","","BOOL",pParas->m_bIPlusDC);

		pXmlSierialize->xml_serialize(/* "开入A" */g_sLangTxt_Manual_InA.GetString(),"_BinAMode","","DInputState",pParas->m_nDInputState[0]);
		pXmlSierialize->xml_serialize(/* "开入B" */g_sLangTxt_Manual_InB.GetString(),"_BinBMode","","DInputState",pParas->m_nDInputState[1]);
		pXmlSierialize->xml_serialize(/* "开入C" */g_sLangTxt_Manual_InC.GetString(),"_BinCMode","","DInputState",pParas->m_nDInputState[2]);
		pXmlSierialize->xml_serialize(/* "开入D" */g_sLangTxt_Manual_InD.GetString(),"_BinDMode","","DInputState",pParas->m_nDInputState[3]);
		pXmlSierialize->xml_serialize(/* "开入E" */g_sLangTxt_Manual_InE.GetString(),"_BinEMode","","DInputState",pParas->m_nDInputState[4]);
		pXmlSierialize->xml_serialize(/* "开入F" */g_sLangTxt_Manual_InF.GetString(),"_BinFMode","","DInputState",pParas->m_nDInputState[5]);
		pXmlSierialize->xml_serialize(/* "开入G" */g_sLangTxt_Manual_InG.GetString(),"_BinGMode","","DInputState",pParas->m_nDInputState[6]);
		pXmlSierialize->xml_serialize(/* "开入H" */g_sLangTxt_Manual_InH.GetString(),"_BinHMode","","DInputState",pParas->m_nDInputState[7]);
	}
#endif
	
}


void stt_xml_serialize_impedance_results(tmt_ImpedanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("A相动作时间","TtripA","s","number",pResults->m_fFirstTripTime[0]);
	pXmlSierialize->xml_serialize("B相动作时间","TtripB","s","number",pResults->m_fFirstTripTime[1]);
	pXmlSierialize->xml_serialize("C相动作时间","TtripC","s","number",pResults->m_fFirstTripTime[2]);
	pXmlSierialize->xml_serialize("重合闸动作时间","TtripD","s","number",pResults->m_fRecloseTime);
	pXmlSierialize->xml_serialize("开入E动作时间", "TtripE", "s", "number", pResults->m_fFirstTripTime[4]);
	pXmlSierialize->xml_serialize("开入F动作时间", "TtripF", "s", "number",pResults->m_fFirstTripTime[5]);
	pXmlSierialize->xml_serialize("开入G动作时间", "TtripG", "s", "number",pResults->m_fFirstTripTime[6]);
	pXmlSierialize->xml_serialize("开入H动作时间", "TtripH", "s", "number",pResults->m_fFirstTripTime[7]);
	pXmlSierialize->xml_serialize("动作时间", "TripTime", "", "number",pResults->m_fTripTime);

	pXmlSierialize->xml_serialize("开入A动作描述","ActA","","number",pResults->m_nActA);
	pXmlSierialize->xml_serialize("开入B动作描述","ActB","","number",pResults->m_nActB);
	pXmlSierialize->xml_serialize("开入C动作描述","ActC","","number",pResults->m_nActC);
	pXmlSierialize->xml_serialize("重合闸动作描述","ActD","","number",pResults->m_nActD);

	pXmlSierialize->xml_serialize("后加速动作时间","TtripAcc","s","number",pResults->m_fSecondTripTime);
	pXmlSierialize->xml_serialize("后加速动作描述","ActAcc","","number",pResults->m_nActAcc);

	pXmlSierialize->xml_serialize("实际短路电流","FaultCurrent","","number",pResults->m_fFaultCurrent);
	pXmlSierialize->xml_serialize("实际短路电压","FaultVolt","","number",pResults->m_fFaultVol);
#else
	pXmlSierialize->xml_serialize(/* "A相动作时间" */g_sLangTxt_Native_PhaseATime.GetString(),"TtripA","s","number",pResults->m_fFirstTripTime[0]);
	pXmlSierialize->xml_serialize(/* "B相动作时间" */g_sLangTxt_Native_PhaseBTime.GetString(),"TtripB","s","number",pResults->m_fFirstTripTime[1]);
	pXmlSierialize->xml_serialize(/* "C相动作时间" */g_sLangTxt_Native_PhaseCTime.GetString(),"TtripC","s","number",pResults->m_fFirstTripTime[2]);
	pXmlSierialize->xml_serialize(/* "重合闸动作时间" */g_sLangTxt_Native_RecloseTime.GetString(),"TtripD","s","number",pResults->m_fRecloseTime);
	pXmlSierialize->xml_serialize(/* "开入E动作时间" */g_sLangTxt_Native_InputETime.GetString(), "TtripE", "s", "number", pResults->m_fFirstTripTime[4]);
	pXmlSierialize->xml_serialize(/* "开入F动作时间" */g_sLangTxt_Native_InputFTime.GetString(), "TtripF", "s", "number",pResults->m_fFirstTripTime[5]);
	pXmlSierialize->xml_serialize(/* "开入G动作时间" */g_sLangTxt_Native_InputGTime.GetString(), "TtripG", "s", "number",pResults->m_fFirstTripTime[6]);
	pXmlSierialize->xml_serialize(/* "开入H动作时间" */g_sLangTxt_Native_InputHTime.GetString(), "TtripH", "s", "number",pResults->m_fFirstTripTime[7]);
	pXmlSierialize->xml_serialize(/* "动作时间" */g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number",pResults->m_fTripTime);

	pXmlSierialize->xml_serialize(/* "开入A动作描述" */g_sLangTxt_Native_InputADesc.GetString(),"ActA","","number",pResults->m_nActA);
	pXmlSierialize->xml_serialize(/* "开入B动作描述" */g_sLangTxt_Native_InputBDesc.GetString(),"ActB","","number",pResults->m_nActB);
	pXmlSierialize->xml_serialize(/* "开入C动作描述" */g_sLangTxt_Native_InputCDesc.GetString(),"ActC","","number",pResults->m_nActC);
	pXmlSierialize->xml_serialize(/* "重合闸动作描述" */g_sLangTxt_Native_ReclActDesc.GetString(),"ActD","","number",pResults->m_nActD);

	pXmlSierialize->xml_serialize(/* "后加速动作时间" */g_sLangTxt_Native_PostAccTime.GetString(),"TtripAcc","s","number",pResults->m_fSecondTripTime);
	pXmlSierialize->xml_serialize(/* "后加速动作描述" */g_sLangTxt_Native_PostAccDesc.GetString(),"ActAcc","","number",pResults->m_nActAcc);

	pXmlSierialize->xml_serialize(/* "实际短路电流" */g_sLangTxt_Native_ActShortCur.GetString(),"FaultCurrent","","number",pResults->m_fFaultCurrent);
	pXmlSierialize->xml_serialize(/* "实际短路电压" */g_sLangTxt_Native_ActShortVol.GetString(),"FaultVolt","","number",pResults->m_fFaultVol);
#endif
	
}
