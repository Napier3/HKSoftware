#include "stdafx.h"
#include "tmt_low_freq_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_LowFreqParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_LowFreqParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_LowFreqParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_LowFreqParasEx));
	pParas->init();
}

void stt_init_results(tmt_LowFreqResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_LowFreqResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_Common(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间","HoldTime","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("故障时间裕度","MarginTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("稳态时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	// 	pXmlSierialize->xml_serialize("滑差变化模式","ChangeMode","","PsudtChangeMode",pParas->m_nChangeMode);
	// 	pXmlSierialize->xml_serialize("变化时间","ChangeTime","","number",pParas->m_fChangeTime);

	pXmlSierialize->xml_serialize("低频动作值","FAct","Hz","number",pParas->m_fFAct);
	pXmlSierialize->xml_serialize("动作时间","FActTime","s","number",pParas->m_fFActTime);
	pXmlSierialize->xml_serialize("滑差闭锁值","DvdtClose","Hz/s","number",pParas->m_fDfdtClose);
	pXmlSierialize->xml_serialize("闭锁电压","Ulow","V","number",pParas->m_fUlow);
	pXmlSierialize->xml_serialize("闭锁电流","Ilow","A","number",pParas->m_fILow);
	pXmlSierialize->xml_serialize("闭锁电压定义","USetMode","","VSetMode",pParas->m_nUSetMode);
#else
	pXmlSierialize->xml_serialize(/* "保持时间" */g_sLangTxt_Native_KeepTime.GetString(),"HoldTime","s","number",pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize(/* "稳态时间" */g_sLangTxt_Native_SteadyTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);
	// 	pXmlSierialize->xml_serialize("滑差变化模式","ChangeMode","","PsudtChangeMode",pParas->m_nChangeMode);
	// 	pXmlSierialize->xml_serialize("变化时间","ChangeTime","","number",pParas->m_fChangeTime);

	pXmlSierialize->xml_serialize(/* "低频动作值" */g_sLangTxt_Native_LowFreActValue.GetString(),"FAct","Hz","number",pParas->m_fFAct);
	pXmlSierialize->xml_serialize(/* "动作时间" */g_sLangTxt_Gradient_ActionTime.GetString(),"FActTime","s","number",pParas->m_fFActTime);
	pXmlSierialize->xml_serialize(/* "滑差闭锁值" */g_sLangTxt_Native_sliptripValue.GetString(),"DvdtClose","Hz/s","number",pParas->m_fDfdtClose);
	pXmlSierialize->xml_serialize(/* "闭锁电压" */g_sLangTxt_interlock_vol.GetString(),"Ulow","V","number",pParas->m_fUlow);
	pXmlSierialize->xml_serialize(/* "闭锁电流" */g_sLangTxt_interlock_cur.GetString(),"Ilow","A","number",pParas->m_fILow);
	pXmlSierialize->xml_serialize(/* "闭锁电压定义" */g_sLangTxt_Native_LockVoltDef.GetString(),"USetMode","","VSetMode",pParas->m_nUSetMode);
#endif
	

	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Exbinary_out(pParas->m_binOutEx,pXmlSierialize);

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/* "开入逻辑" */g_sLangTxt_Native_InLogic.GetString(),"_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#endif

	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
	#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("开入A选择","_BinAEnable","","BOOL",pParas->m_binIn[0].nSelect);
		pXmlSierialize->xml_serialize("开入B选择","_BinBEnable","","BOOL",pParas->m_binIn[1].nSelect);
		pXmlSierialize->xml_serialize("开入C选择","_BinCEnable","","BOOL",pParas->m_binIn[2].nSelect);
		pXmlSierialize->xml_serialize("开入D选择","_BinDEnable","","BOOL",pParas->m_binIn[3].nSelect);
		pXmlSierialize->xml_serialize("开入E选择","_BinEEnable","","BOOL",pParas->m_binIn[4].nSelect);
		pXmlSierialize->xml_serialize("开入F选择","_BinFEnable","","BOOL",pParas->m_binIn[5].nSelect);
		pXmlSierialize->xml_serialize("开入G选择","_BinGEnable","","BOOL",pParas->m_binIn[6].nSelect);
		pXmlSierialize->xml_serialize("开入H选择","_BinHEnable","","BOOL",pParas->m_binIn[7].nSelect);
		pXmlSierialize->xml_serialize("开入I选择","_BinIEnable","","BOOL",pParas->m_binIn[8].nSelect);
		pXmlSierialize->xml_serialize("开入J选择","_BinJEnable","","BOOL",pParas->m_binIn[9].nSelect);

		pXmlSierialize->xml_serialize("开出1状态","_B01","","DOutputState",pParas->m_binOut[0].nState);
		pXmlSierialize->xml_serialize("开出2状态","_B02","","DOutputState",pParas->m_binOut[1].nState);
		pXmlSierialize->xml_serialize("开出3状态","_B03","","DOutputState",pParas->m_binOut[2].nState);
		pXmlSierialize->xml_serialize("开出4状态","_B04","","DOutputState",pParas->m_binOut[3].nState);
		pXmlSierialize->xml_serialize("开出5状态","_B05","","DOutputState",pParas->m_binOut[4].nState);
		pXmlSierialize->xml_serialize("开出6状态","_B06","","DOutputState",pParas->m_binOut[5].nState);
		pXmlSierialize->xml_serialize("开出7状态","_B07","","DOutputState",pParas->m_binOut[6].nState);
		pXmlSierialize->xml_serialize("开出8状态","_B08","","DOutputState",pParas->m_binOut[7].nState);
	#else
		pXmlSierialize->xml_serialize(/* "开入A选择" */g_sLangTxt_Native_InputASelect.GetString(),"_BinAEnable","","BOOL",pParas->m_binIn[0].nSelect);
		pXmlSierialize->xml_serialize(/* "开入B选择" */g_sLangTxt_Native_InputBSelect.GetString(),"_BinBEnable","","BOOL",pParas->m_binIn[1].nSelect);
		pXmlSierialize->xml_serialize(/* "开入C选择" */g_sLangTxt_Native_InputCSelect.GetString(),"_BinCEnable","","BOOL",pParas->m_binIn[2].nSelect);
		pXmlSierialize->xml_serialize(/* "开入D选择" */g_sLangTxt_Native_InputDSelect.GetString(),"_BinDEnable","","BOOL",pParas->m_binIn[3].nSelect);
		pXmlSierialize->xml_serialize(/* "开入E选择" */g_sLangTxt_Native_InputESelect.GetString(),"_BinEEnable","","BOOL",pParas->m_binIn[4].nSelect);
		pXmlSierialize->xml_serialize(/* "开入F选择" */g_sLangTxt_Native_InputFSelect.GetString(),"_BinFEnable","","BOOL",pParas->m_binIn[5].nSelect);
		pXmlSierialize->xml_serialize(/* "开入G选择" */g_sLangTxt_Native_InputGSelect.GetString(),"_BinGEnable","","BOOL",pParas->m_binIn[6].nSelect);
		pXmlSierialize->xml_serialize(/* "开入H选择" */g_sLangTxt_Native_InputHSelect.GetString(),"_BinHEnable","","BOOL",pParas->m_binIn[7].nSelect);
		pXmlSierialize->xml_serialize(/* "开入I选择" */g_sLangTxt_Native_InputISelect.GetString(),"_BinIEnable","","BOOL",pParas->m_binIn[8].nSelect);
		pXmlSierialize->xml_serialize(/* "开入J选择" */g_sLangTxt_Native_InputJSelect.GetString(),"_BinJEnable","","BOOL",pParas->m_binIn[9].nSelect);

		pXmlSierialize->xml_serialize(/* "开出1状态" */g_sLangTxt_Out1_Situation.GetString(),"_B01","","DOutputState",pParas->m_binOut[0].nState);
		pXmlSierialize->xml_serialize(/* "开出2状态" */g_sLangTxt_Out2_Situation.GetString(),"_B02","","DOutputState",pParas->m_binOut[1].nState);
		pXmlSierialize->xml_serialize(/* "开出3状态" */g_sLangTxt_Out3_Situation.GetString(),"_B03","","DOutputState",pParas->m_binOut[2].nState);
		pXmlSierialize->xml_serialize(/* "开出4状态" */g_sLangTxt_Out4_Situation.GetString(),"_B04","","DOutputState",pParas->m_binOut[3].nState);
		pXmlSierialize->xml_serialize(/* "开出5状态" */g_sLangTxt_Out5_Situation.GetString(),"_B05","","DOutputState",pParas->m_binOut[4].nState);
		pXmlSierialize->xml_serialize(/* "开出6状态" */g_sLangTxt_Out6_Situation.GetString(),"_B06","","DOutputState",pParas->m_binOut[5].nState);
		pXmlSierialize->xml_serialize(/* "开出7状态" */g_sLangTxt_Out7_Situation.GetString(),"_B07","","DOutputState",pParas->m_binOut[6].nState);
		pXmlSierialize->xml_serialize(/* "开出8状态" */g_sLangTxt_Out8_Situation.GetString(),"_B08","","DOutputState",pParas->m_binOut[7].nState);
	#endif
		
	}
}

void stt_xml_serialize_PsuLowFreqAct(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("频率滑差","dvdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize("频率变化始值","Fstart","Hz","number",pParas->m_fFstart);
	pXmlSierialize->xml_serialize("频率变化终值","Fend","Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize("频率变化步长","Fstep","Hz","number",pParas->m_fFstep);
#else
	pXmlSierialize->xml_serialize(/* "频率滑差" */g_sLangTxt_Native_FreqSlip.GetString(),"dvdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize(/* "频率变化始值" */g_sLangTxt_Native_FreInitialValue.GetString(),"Fstart","Hz","number",pParas->m_fFstart);
	pXmlSierialize->xml_serialize(/* "频率变化终值" */g_sLangTxt_Native_FreFinalValue.GetString(),"Fend","Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize(/* "频率变化步长" */g_sLangTxt_Native_FreChangeStep.GetString(),"Fstep","Hz","number",pParas->m_fFstep);
#endif

	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqTime(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("频率滑差","dvdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize("频率变化终值","Fend","Hz","number",pParas->m_fFend);
    pXmlSierialize->xml_serialize("滑差计时设置参数","DfdtTiming","","number",pParas->m_nDfdtTiming);
#else
	pXmlSierialize->xml_serialize(/* "频率滑差" */g_sLangTxt_Native_FreqSlip.GetString(),"dvdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize(/* "频率变化终值" */g_sLangTxt_Native_FreFinalValue.GetString(),"Fend","Hz","number",pParas->m_fFend);
    pXmlSierialize->xml_serialize("滑差计时设置参数","DfdtTiming","","number",pParas->m_nDfdtTiming);
#endif


	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqDfDt(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "Hz/s","number",pParas->m_fDfdtStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "Hz/s","number",pParas->m_fDfdtEnd);
	pXmlSierialize->xml_serialize("变化步长", "Step", "Hz/s","number",pParas->m_fDfdtStep);
	pXmlSierialize->xml_serialize("频率终值", "FreqEnd", "Hz","number",pParas->m_fFend);
	stt_xml_serialize_Common(pParas,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
		pXmlSierialize->xml_serialize("变化始值", "DfdtStart", "Hz/s","number",pParas->m_fDfdtStart);
		pXmlSierialize->xml_serialize("变化终值", "DfdtEnd", "Hz/s","number",pParas->m_fDfdtEnd);
		pXmlSierialize->xml_serialize("变化步长", "DfdtStep", "Hz/s","number",pParas->m_fDfdtStep);
		pXmlSierialize->xml_serialize("频率终值", "Fend", "Hz","number",pParas->m_fFend);
	}
#else
	pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "Hz/s","number",pParas->m_fDfdtStart);
	pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "Hz/s","number",pParas->m_fDfdtEnd);
	pXmlSierialize->xml_serialize(/* "变化步长" */g_sLangTxt_Gradient_Step.GetString(), "Step", "Hz/s","number",pParas->m_fDfdtStep);
	pXmlSierialize->xml_serialize(/* "频率终值" */g_sLangTxt_Native_FreFinal.GetString(), "FreqEnd", "Hz","number",pParas->m_fFend);
	stt_xml_serialize_Common(pParas,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
		pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "DfdtStart", "Hz/s","number",pParas->m_fDfdtStart);
		pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "DfdtEnd", "Hz/s","number",pParas->m_fDfdtEnd);
		pXmlSierialize->xml_serialize(/* "变化步长" */g_sLangTxt_Gradient_Step.GetString(), "DfdtStep", "Hz/s","number",pParas->m_fDfdtStep);
		pXmlSierialize->xml_serialize(/* "频率终值" */g_sLangTxt_Native_FreFinal.GetString(), "Fend", "Hz","number",pParas->m_fFend);
	}
#endif
}

void stt_xml_serialize_PsuLowFreqILock(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "A","number",pParas->m_fIStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "A","number",pParas->m_fIEnd);
	pXmlSierialize->xml_serialize("变化步长", "Step", "A","number",pParas->m_fIStep);
	pXmlSierialize->xml_serialize("频率滑差","Dfdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize("频率终值", "RampTo", "Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize("电流变化相", "IVariable", "","number",pParas->m_nIPhase);
	stt_xml_serialize_Common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "A","number",pParas->m_fIStart);
	pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "A","number",pParas->m_fIEnd);
	pXmlSierialize->xml_serialize(/* "变化步长" */g_sLangTxt_Gradient_Step.GetString(), "Step", "A","number",pParas->m_fIStep);
	pXmlSierialize->xml_serialize(/* "频率滑差" */g_sLangTxt_Native_FreqSlip.GetString(),"Dfdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize(/* "频率终值" */g_sLangTxt_Native_FreFinal.GetString(), "RampTo", "Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize(/* "电流变化相" */g_sLangTxt_Native_IChangePhase.GetString(), "IVariable", "","number",pParas->m_nIPhase);
	stt_xml_serialize_Common(pParas,pXmlSierialize);
#endif
}

void stt_xml_serialize_PsuLowFreqULock(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "A","number",pParas->m_fUStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "A","number",pParas->m_fUEnd);
	pXmlSierialize->xml_serialize("变化步长", "Step", "A","number",pParas->m_fUStep);
	pXmlSierialize->xml_serialize("频率滑差","Dfdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize("频率终值", "RampTo", "Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize("电压变化量", "UVariable", "","number",pParas->m_nUPhase);
	stt_xml_serialize_Common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "A","number",pParas->m_fUStart);
	pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "A","number",pParas->m_fUEnd);
	pXmlSierialize->xml_serialize(/* "变化步长" */g_sLangTxt_Gradient_Step.GetString(), "Step", "A","number",pParas->m_fUStep);
	pXmlSierialize->xml_serialize(/* "频率滑差" */g_sLangTxt_Native_FreqSlip.GetString(),"Dfdt","Hz/s","number",pParas->m_fDfdt);
	pXmlSierialize->xml_serialize(/* "频率终值" */g_sLangTxt_Native_FreFinal.GetString(), "RampTo", "Hz","number",pParas->m_fFend);
	pXmlSierialize->xml_serialize(/* "电压变化量" */g_sLangTxt_Native_VoltChangeAmt.GetString(), "UVariable", "","number",pParas->m_nUPhase);
	stt_xml_serialize_Common(pParas,pXmlSierialize);
#endif

}

void stt_xml_serialize_PnvLowFreqTime(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("频率滑差","Dfdt","Hz/s","number",pParas->m_fDfdt);
    pXmlSierialize->xml_serialize("频率变化终值","RampTo","Hz","number",pParas->m_fFend);
    pXmlSierialize->xml_serialize("保持时间","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("计时启动值","TimerStartValue","Hz","number",pParas->m_fFAct);
    pXmlSierialize->xml_serialize("复归值","ResetValue","Hz","number",pParas->m_fFnom);
    pXmlSierialize->xml_serialize("试验前复归时间","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

    pXmlSierialize->xml_serialize("Ua幅值", "Ua", "V", "number", pParas->m_fUabc[0]);
    pXmlSierialize->xml_serialize("Ua相位", "UaPh", "°", "number", pParas->m_fUabcPh[0]);
    pXmlSierialize->xml_serialize("Ub幅值", "Ub", "V", "number", pParas->m_fUabc[1]);
    pXmlSierialize->xml_serialize("Ub相位", "UbPh", "°", "number", pParas->m_fUabcPh[1]);
    pXmlSierialize->xml_serialize("Uc幅值", "Uc", "V", "number", pParas->m_fUabc[2]);
    pXmlSierialize->xml_serialize("Uc相位", "UcPh", "°", "number", pParas->m_fUabcPh[2]);
    pXmlSierialize->xml_serialize("Ia幅值", "Ia", "A", "number", pParas->m_fIabc[0]);
    pXmlSierialize->xml_serialize("Ia相位", "IaPh", "°", "number", pParas->m_fIabcPh[0]);
    pXmlSierialize->xml_serialize("Ib幅值", "Ib", "A", "number", pParas->m_fIabc[1]);
    pXmlSierialize->xml_serialize("Ib相位", "IbPh", "°", "number", pParas->m_fIabcPh[1]);
    pXmlSierialize->xml_serialize("Ic幅值", "Ic", "A", "number", pParas->m_fIabc[2]);
    pXmlSierialize->xml_serialize("Ic相位", "IcPh", "°", "number", pParas->m_fIabcPh[2]);

    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx,pXmlSierialize);
}
void stt_xml_serialize_PnvLowFreqAct(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("频率变化率","Dfdt","Hz/s","number",pParas->m_fDfdt);
    pXmlSierialize->xml_serialize("变化始值","BeginVal","Hz","number",pParas->m_fFstart);
    pXmlSierialize->xml_serialize("变化终值","EndVal","Hz","number",pParas->m_fFend);
    pXmlSierialize->xml_serialize("测试精度","Step","Hz","number",pParas->m_fFstep);

    pXmlSierialize->xml_serialize("保持时间","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("待测定值","ValSetting","Hz","number",pParas->m_fFAct);
    pXmlSierialize->xml_serialize("复归值","_ResetValue","Hz","number",pParas->m_fFnom);
    pXmlSierialize->xml_serialize("试验前复归时间","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("故障前Ua", "_PreFaultUa", "V", "number", pParas->m_fUabc[0]);
    pXmlSierialize->xml_serialize("故障前Ua相位", "_PreFaultUaPh", "°", "number", pParas->m_fUabcPh[0]);
    pXmlSierialize->xml_serialize("故障前Ub", "_PreFaultUb", "V", "number", pParas->m_fUabc[1]);
    pXmlSierialize->xml_serialize("故障前Ub相位", "_PreFaultUbPh", "°", "number", pParas->m_fUabcPh[1]);
    pXmlSierialize->xml_serialize("故障前Uc", "_PreFaultUc", "V", "number", pParas->m_fUabc[2]);
    pXmlSierialize->xml_serialize("故障前Uc相位", "_PreFaultUcPh", "°", "number", pParas->m_fUabcPh[2]);
    pXmlSierialize->xml_serialize("故障前Ia", "_PreFaultIa", "A", "number", pParas->m_fIabc[0]);
    pXmlSierialize->xml_serialize("故障前Ia相位", "_PreFaultIaPh", "°", "number", pParas->m_fIabcPh[0]);
    pXmlSierialize->xml_serialize("故障前Ib", "_PreFaultIb", "A", "number", pParas->m_fIabc[1]);
    pXmlSierialize->xml_serialize("故障前Ib相位", "_PreFaultIbPh", "°", "number", pParas->m_fIabcPh[1]);
    pXmlSierialize->xml_serialize("故障前Ic", "_PreFaultIc", "A", "number", pParas->m_fIabc[2]);
    pXmlSierialize->xml_serialize("故障前Ic相位", "_PreFaultIcPh", "°", "number", pParas->m_fIabcPh[2]);
    pXmlSierialize->xml_serialize("故障Ua", "_FaultUa", "V", "number", pParas->m_fUabc[3]);
    pXmlSierialize->xml_serialize("故障Ua相位", "_FaultUaPh", "°", "number", pParas->m_fUabcPh[3]);
    pXmlSierialize->xml_serialize("故障Ub", "_FaultUb", "V", "number", pParas->m_fUabc[4]);
    pXmlSierialize->xml_serialize("故障Ub相位", "_FaultUbPh", "°", "number", pParas->m_fUabcPh[4]);
    pXmlSierialize->xml_serialize("故障Uc", "_FaultUc", "V", "number", pParas->m_fUabc[5]);
    pXmlSierialize->xml_serialize("故障Uc相位", "_FaultUcPh", "°", "number", pParas->m_fUabcPh[5]);
    pXmlSierialize->xml_serialize("故障Ia", "_FaultIa", "A", "number", pParas->m_fIabc[3]);
    pXmlSierialize->xml_serialize("故障Ia相位", "_FaultIaPh", "°", "number", pParas->m_fIabcPh[3]);
    pXmlSierialize->xml_serialize("故障Ib", "_FaultIb", "A", "number", pParas->m_fIabc[4]);
    pXmlSierialize->xml_serialize("故障Ib相位", "_FaultIbPh", "°", "number", pParas->m_fIabcPh[4]);
    pXmlSierialize->xml_serialize("故障Ic", "_FaultIc", "A", "number", pParas->m_fIabc[5]);
    pXmlSierialize->xml_serialize("故障Ic相位", "_FaultIcPh", "°", "number", pParas->m_fIabcPh[5]);

    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx,pXmlSierialize);
}
void stt_xml_serialize_PnvLowFreqDfdt(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("变化始值", "BeginVal", "Hz/s","number",pParas->m_fDfdtStart);
    pXmlSierialize->xml_serialize("变化终值", "EndVal", "Hz/s","number",pParas->m_fDfdtEnd);
    pXmlSierialize->xml_serialize("测试精度", "Step", "Hz/s","number",pParas->m_fDfdtStep);
    pXmlSierialize->xml_serialize("频率终值", "FreqEnd", "Hz","number",pParas->m_fFend);

    pXmlSierialize->xml_serialize("保持时间","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("待测定值","ValSetting","Hz","number",pParas->m_fDfdtClose);
    pXmlSierialize->xml_serialize("复归值","ResetValue","Hz","number",pParas->m_fFnom);
    pXmlSierialize->xml_serialize("试验前复归时间","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("故障前Ua", "_PreFaultUa", "V", "number", pParas->m_fUabc[0]);
    pXmlSierialize->xml_serialize("故障前Ua相位", "_PreFaultUaPh", "°", "number", pParas->m_fUabcPh[0]);
    pXmlSierialize->xml_serialize("故障前Ub", "_PreFaultUb", "V", "number", pParas->m_fUabc[1]);
    pXmlSierialize->xml_serialize("故障前Ub相位", "_PreFaultUbPh", "°", "number", pParas->m_fUabcPh[1]);
    pXmlSierialize->xml_serialize("故障前Uc", "_PreFaultUc", "V", "number", pParas->m_fUabc[2]);
    pXmlSierialize->xml_serialize("故障前Uc相位", "_PreFaultUcPh", "°", "number", pParas->m_fUabcPh[2]);
    pXmlSierialize->xml_serialize("故障前Ia", "_PreFaultIa", "A", "number", pParas->m_fIabc[0]);
    pXmlSierialize->xml_serialize("故障前Ia相位", "_PreFaultIaPh", "°", "number", pParas->m_fIabcPh[0]);
    pXmlSierialize->xml_serialize("故障前Ib", "_PreFaultIb", "A", "number", pParas->m_fIabc[1]);
    pXmlSierialize->xml_serialize("故障前Ib相位", "_PreFaultIbPh", "°", "number", pParas->m_fIabcPh[1]);
    pXmlSierialize->xml_serialize("故障前Ic", "_PreFaultIc", "A", "number", pParas->m_fIabc[2]);
    pXmlSierialize->xml_serialize("故障前Ic相位", "_PreFaultIcPh", "°", "number", pParas->m_fIabcPh[2]);
    pXmlSierialize->xml_serialize("故障Ua", "_FaultUa", "V", "number", pParas->m_fUabc[3]);
    pXmlSierialize->xml_serialize("故障Ua相位", "_FaultUaPh", "°", "number", pParas->m_fUabcPh[3]);
    pXmlSierialize->xml_serialize("故障Ub", "_FaultUb", "V", "number", pParas->m_fUabc[4]);
    pXmlSierialize->xml_serialize("故障Ub相位", "_FaultUbPh", "°", "number", pParas->m_fUabcPh[4]);
    pXmlSierialize->xml_serialize("故障Uc", "_FaultUc", "V", "number", pParas->m_fUabc[5]);
    pXmlSierialize->xml_serialize("故障Uc相位", "_FaultUcPh", "°", "number", pParas->m_fUabcPh[5]);
    pXmlSierialize->xml_serialize("故障Ia", "_FaultIa", "A", "number", pParas->m_fIabc[3]);
    pXmlSierialize->xml_serialize("故障Ia相位", "_FaultIaPh", "°", "number", pParas->m_fIabcPh[3]);
    pXmlSierialize->xml_serialize("故障Ib", "_FaultIb", "A", "number", pParas->m_fIabc[4]);
    pXmlSierialize->xml_serialize("故障Ib相位", "_FaultIbPh", "°", "number", pParas->m_fIabcPh[4]);
    pXmlSierialize->xml_serialize("故障Ic", "_FaultIc", "A", "number", pParas->m_fIabc[5]);
    pXmlSierialize->xml_serialize("故障Ic相位", "_FaultIcPh", "°", "number", pParas->m_fIabcPh[5]);

    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx,pXmlSierialize);
}
void stt_xml_serialize_LowFreq_search_results(tmt_LowFreqParas *pParas,tmt_LowFreqResults *pResults,CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSerialize->xml_serialize("当前搜索滑差值(dfdt)","CurrSearchDfdt","","number",pParas->m_fCurrSearchDfdt);
#else
	pXmlSerialize->xml_serialize(/* "当前搜索滑差值(dfdt)" */g_sLangTxt_Native_SearchslipVal.GetString(),"CurrSearchDfdt","","number",pParas->m_fCurrSearchDfdt);
#endif

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_PsuLowFreqAct_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间(表达式)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("频率滑差(表达式)","dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize("频率变化始值(表达式)","FstartExp","","string",pParas->m_pszFstart);
	pXmlSierialize->xml_serialize("频率变化终值(表达式)","FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize("频率变化步长(表达式)","FstepExp","","string",pParas->m_pszFstep);
#else
	pXmlSierialize->xml_serialize(/* "保持时间(表达式)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "频率滑差(表达式)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(),"dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize(/* "频率变化始值(表达式)" */g_sLangTxt_Native_FreInitialValueExp.GetString(),"FstartExp","","string",pParas->m_pszFstart);
	pXmlSierialize->xml_serialize(/* "频率变化终值(表达式)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize(/* "频率变化步长(表达式)" */g_sLangTxt_Native_FreChangeStepExp.GetString(),"FstepExp","","string",pParas->m_pszFstep);
#endif
	
	stt_xml_serialize_PsuLowFreqAct(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqTime_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间(表达式)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("频率滑差(表达式)","dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize("频率变化终值(表达式)","FendExp","","string",pParas->m_pszFend);
#else
	pXmlSierialize->xml_serialize(/* "保持时间(表达式)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "频率滑差(表达式)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(),"dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize(/* "频率变化终值(表达式)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
#endif
	stt_xml_serialize_PsuLowFreqTime(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqDfDt_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间(表达式)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("频率变化终值(表达式)","FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize("滑差变化始值(表达式)", "BeginValExp", "","string",pParas->m_pszDfdtStart);
	pXmlSierialize->xml_serialize("滑差变化终值(表达式)", "EndValExp", "","string",pParas->m_pszDfdtEnd);
	pXmlSierialize->xml_serialize("滑差变化步长(表达式)", "StepExp", "","string",pParas->m_pszDfdtStep);
#else
	pXmlSierialize->xml_serialize(/* "保持时间(表达式)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "频率变化终值(表达式)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize(/* "滑差变化始值(表达式)" */g_sLangTxt_Native_SlipInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszDfdtStart);
	pXmlSierialize->xml_serialize(/* "滑差变化终值(表达式)" */g_sLangTxt_Native_SlipFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszDfdtEnd);
	pXmlSierialize->xml_serialize(/* "滑差变化步长(表达式)" */g_sLangTxt_Native_SlipChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszDfdtStep);
#endif

	stt_xml_serialize_PsuLowFreqDfDt(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqILock_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间(表达式)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("频率滑差(表达式)","dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize("频率变化终值(表达式)","FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize("电流变化始值(表达式)", "BeginValExp", "","string",pParas->m_pszIStart);
	pXmlSierialize->xml_serialize("电流变化终值(表达式)", "EndValExp", "","string",pParas->m_pszIEnd);
	pXmlSierialize->xml_serialize("电流变化步长(表达式)", "StepExp", "","string",pParas->m_pszIStep);
#else
	pXmlSierialize->xml_serialize(/* "保持时间(表达式)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "频率滑差(表达式)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(),"dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize(/* "频率变化终值(表达式)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize(/* "电流变化始值(表达式)" */g_sLangTxt_Native_IInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszIStart);
	pXmlSierialize->xml_serialize(/* "电流变化终值(表达式)" */g_sLangTxt_Native_IFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszIEnd);
	pXmlSierialize->xml_serialize(/* "电流变化步长(表达式)" */g_sLangTxt_Native_IChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszIStep);
#endif
	stt_xml_serialize_PsuLowFreqILock(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowFreqULock_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间(表达式)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("频率滑差(表达式)","dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize("频率变化终值(表达式)","FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize("电压变化始值(表达式)", "BeginValExp", "","string",pParas->m_pszUStart);
	pXmlSierialize->xml_serialize("电压变化终值(表达式)", "EndValExp", "","string",pParas->m_pszUEnd);
	pXmlSierialize->xml_serialize("电压变化步长(表达式)", "StepExp", "","string",pParas->m_pszUStep);
#else
	pXmlSierialize->xml_serialize(/* "保持时间(表达式)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "频率滑差(表达式)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(),"dvdtExp","","string",pParas->m_pszDfdt);
	pXmlSierialize->xml_serialize(/* "频率变化终值(表达式)" */g_sLangTxt_Native_FreFinalValueExp.GetString(),"FendExp","","string",pParas->m_pszFend);
	pXmlSierialize->xml_serialize(/* "电压变化始值(表达式)" */g_sLangTxt_Native_VInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszUStart);
	pXmlSierialize->xml_serialize(/* "电压变化终值(表达式)" */g_sLangTxt_Native_VFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszUEnd);
	pXmlSierialize->xml_serialize(/* "电压变化步长(表达式)" */g_sLangTxt_Native_VChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszUStep);
#endif

	stt_xml_serialize_PsuLowFreqULock(pParas,pXmlSierialize);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_PsuLowFreqAct(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("频率动作值","TripFre","Hz","number",pResults->m_fLowFAct);
	pXmlSierialize->xml_serialize("低周动作描述", "ActFre", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "频率动作值" */g_sLangTxt_Native_FreActValue.GetString(),"TripFre","Hz","number",pResults->m_fLowFAct);
	pXmlSierialize->xml_serialize(/* "低周动作描述" */g_sLangTxt_Native_LowCycleActDesc.GetString(), "ActFre", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PsuLowFreqTime(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("低周减载动作时间","TTripLf","s","number",pResults->m_fLowFActTime);
	pXmlSierialize->xml_serialize("动作描述", "ActLf", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "低周减载动作时间" */g_sLangTxt_lowfreqloadre_ActTime.GetString(),"TTripLf","s","number",pResults->m_fLowFActTime);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActLf", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PsuLowFreqDfDt(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("滑差动作值","TripDfdt","Hz/s","number",pResults->m_fDfdtAct);
	pXmlSierialize->xml_serialize("动作描述", "ActDfdt", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "滑差动作值" */g_sLangID_Native_SlipActValue.GetString(),"TripDfdt","Hz/s","number",pResults->m_fDfdtAct);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActDfdt", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PsuLowFreqILock(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电流闭锁值", "TripILock", "A", "number",pResults->m_fIAct);
	pXmlSierialize->xml_serialize("动作描述", "ActILock", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "电流闭锁值" */g_sLangTxt_Native_IBlockValue.GetString(), "TripILock", "A", "number",pResults->m_fIAct);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActILock", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PsuLowFreqULock(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压闭锁值", "TripULock", "V", "number",pResults->m_fUAct);
	pXmlSierialize->xml_serialize("动作描述", "ActULock", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "电压闭锁值" */g_sLangTxt_Native_VBlockValue.GetString(), "TripULock", "V", "number",pResults->m_fUAct);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActULock", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PnvLowFreqTime(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("低周减载动作时间","TripT","s","number",pResults->m_fLowFActTime);
    pXmlSierialize->xml_serialize("动作描述", "ActT", "", "number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "低周减载动作时间" */g_sLangTxt_lowfreqloadre_ActTime.GetString(),"TripT","s","number",pResults->m_fLowFActTime);
    pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActT", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PnvLowFreqAct(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("低周动作值","TripFreq","Hz","number",pResults->m_fLowFAct);
    pXmlSierialize->xml_serialize("低周动作描述", "ActFreq", "", "number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "低周减载动作时间" */g_sLangTxt_lowfreqloadre_ActTime.GetString(),"TripT","s","number",pResults->m_fLowFActTime);
    pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActT", "", "number",pResults->m_nAct);
#endif
}

void stt_xml_serialize_PnvLowFreqDfdt(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("动作值","TripDfdt","Hz/s","number",pResults->m_fDfdtAct);
    pXmlSierialize->xml_serialize("动作描述", "ActDfdt", "", "number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "低周减载动作时间" */g_sLangTxt_lowfreqloadre_ActTime.GetString(),"TripT","s","number",pResults->m_fLowFActTime);
    pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActT", "", "number",pResults->m_nAct);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttXmlSerializeBase* stt_xml_serialize(tmt_LowFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqAct) == 0)
		{
			stt_xml_serialize_PsuLowFreqAct_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqTime) == 0)
		{
			stt_xml_serialize_PsuLowFreqTime_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqDfdt) == 0)
		{
			stt_xml_serialize_PsuLowFreqDfDt_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqILock) == 0)
		{
			stt_xml_serialize_PsuLowFreqILock_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqULock) == 0)
		{
			stt_xml_serialize_PsuLowFreqULock_ex(&(pTests->m_oLowFreqParas), pXmlParas);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
        {
            stt_xml_serialize_PnvLowFreqTime(&(pTests->m_oLowFreqParas), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqAct) == 0)
        {
            stt_xml_serialize_PnvLowFreqAct(&(pTests->m_oLowFreqParas), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqDfdt) == 0)
        {
            stt_xml_serialize_PnvLowFreqDfdt(&(pTests->m_oLowFreqParas), pXmlParas);
        }
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqAct) == 0)
		{
			stt_xml_serialize_PsuLowFreqAct(&pTests->m_oLowFreqResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqTime) == 0)
		{
			stt_xml_serialize_PsuLowFreqTime(&pTests->m_oLowFreqResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqDfdt) == 0)
		{
			stt_xml_serialize_PsuLowFreqDfDt(&(pTests->m_oLowFreqResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqILock) == 0)
		{
			stt_xml_serialize_PsuLowFreqILock(&(pTests->m_oLowFreqResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqULock) == 0)
		{
			stt_xml_serialize_PsuLowFreqULock(&(pTests->m_oLowFreqResults), pXmlResults);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
        {
            stt_xml_serialize_PnvLowFreqTime(&(pTests->m_oLowFreqResults), pXmlResults);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqAct) == 0)
        {
            stt_xml_serialize_PnvLowFreqAct(&(pTests->m_oLowFreqResults), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqDfdt) == 0)
        {
            stt_xml_serialize_PnvLowFreqDfdt(&(pTests->m_oLowFreqResults), pXmlParas);
        }
	}

	return pXmlParas;
}

void stt_xml_serialize_ex(tmt_LowFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqAct) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqAct_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqAct(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqTime) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqTime_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqTime(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqDfdt) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqDfDt_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqDfDt(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqILock) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqILock_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqILock(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowFreqULock) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_PsuLowFreqULock_ex(&(pTests->m_oLowFreqParas), pXmlSerialize);
		}
		
		stt_xml_serialize_PsuLowFreqULock(&(pTests->m_oLowFreqResults), pXmlSerialize);
	}
    else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
    {
        if(!bResultOnly)
        {
            stt_xml_serialize_PnvLowFreqTime(&(pTests->m_oLowFreqParas), pXmlSerialize);
        }

        stt_xml_serialize_PnvLowFreqTime(&(pTests->m_oLowFreqResults), pXmlSerialize);
    }
    else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
    {
        if(!bResultOnly)
        {
            stt_xml_serialize_PnvLowFreqAct(&(pTests->m_oLowFreqParas), pXmlSerialize);
        }

        stt_xml_serialize_PnvLowFreqAct(&(pTests->m_oLowFreqResults), pXmlSerialize);
    }
    else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowFreqTime) == 0)
    {
        if(!bResultOnly)
        {
            stt_xml_serialize_PnvLowFreqDfdt(&(pTests->m_oLowFreqParas), pXmlSerialize);
        }

        stt_xml_serialize_PnvLowFreqDfdt(&(pTests->m_oLowFreqResults), pXmlSerialize);
    }
}
