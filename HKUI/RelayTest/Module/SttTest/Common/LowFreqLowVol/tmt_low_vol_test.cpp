#include "stdafx.h"
#include "tmt_low_vol_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_LowVolParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_LowVolParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_LowVolParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_LowVolParasEx));
	pParas->init();
}

void stt_init_results(tmt_LowVolResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_LowVolResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_Common(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间","HoldTime","s","number",pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize("稳态时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	// 	pXmlSierialize->xml_serialize("滑差变化模式","ChangeMode","","PsudtChangeMode",pParas->m_nChangeMode);
	// 	pXmlSierialize->xml_serialize("变化时间","ChangeTime","","number",pParas->m_fChangeTime);

	pXmlSierialize->xml_serialize("低压闭锁值","UAct","V","number",pParas->m_fUAct);
	pXmlSierialize->xml_serialize("动作时间","UActTime","s","number",pParas->m_fUActTime);
	pXmlSierialize->xml_serialize("电压变化率闭锁值","DvdtClose","V/s","number",pParas->m_fDvdtClose);
	pXmlSierialize->xml_serialize("闭锁电压定义","USetMode","","VSetMode",pParas->m_nUSetMode);
	pXmlSierialize->xml_serialize("电流","IAct","A","number",pParas->m_fIAct);

	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);

	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
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
	}
#else
	pXmlSierialize->xml_serialize(/* "保持时间" */g_sLangTxt_Native_KeepTime.GetString(),"HoldTime","s","number",pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize(/* "稳态时间" */g_sLangTxt_Native_SteadyTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);
	// 	pXmlSierialize->xml_serialize("滑差变化模式","ChangeMode","","PsudtChangeMode",pParas->m_nChangeMode);
	// 	pXmlSierialize->xml_serialize("变化时间","ChangeTime","","number",pParas->m_fChangeTime);

	pXmlSierialize->xml_serialize(/* "低压闭锁值" */g_sLangTxt_Native_LowVLockVal.GetString(),"UAct","V","number",pParas->m_fUAct);
	pXmlSierialize->xml_serialize(/* "动作时间" */g_sLangTxt_Gradient_ActionTime.GetString(),"UActTime","s","number",pParas->m_fUActTime);
	pXmlSierialize->xml_serialize(/* "电压变化率闭锁值" */g_sLangTxt_Native_VChangeRate_blockVal.GetString(),"DvdtClose","V/s","number",pParas->m_fDvdtClose);
	pXmlSierialize->xml_serialize(/* "闭锁电压定义" */g_sLangTxt_Native_LockVoltDef.GetString(),"USetMode","","VSetMode",pParas->m_nUSetMode);
	pXmlSierialize->xml_serialize(/* "电流" */g_sLangTxt_Native_Current.GetString(),"IAct","A","number",pParas->m_fIAct);

	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);

	pXmlSierialize->xml_serialize(/* "开入逻辑" */g_sLangTxt_Native_InLogic.GetString(),"_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
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
	}
#endif

}

void stt_xml_serialize_PsuLowVolAct(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压滑差","dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize("电压变化始值","Vstart","V","number",pParas->m_fVstart);
	pXmlSierialize->xml_serialize("电压变化终值","Vend","V","number",pParas->m_fVend);
	pXmlSierialize->xml_serialize("电压变化步长","Vstep","V","number",pParas->m_fVstep);
	pXmlSierialize->xml_serialize("故障类型","FaultType","","PsuLowUChangeMode",pParas->m_nFaultType);
#else
	pXmlSierialize->xml_serialize(/* "电压滑差" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize(/* "电压变化始值" */g_sLangTxt_Native_InitVoltChange.GetString(),"Vstart","V","number",pParas->m_fVstart);
	pXmlSierialize->xml_serialize(/* "电压变化终值" */g_sLangTxt_Native_FinalVoltChange.GetString(),"Vend","V","number",pParas->m_fVend);
	pXmlSierialize->xml_serialize(/* "电压变化步长" */g_sLangTxt_Native_VoltChangeStep.GetString(),"Vstep","V","number",pParas->m_fVstep);
	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(),"FaultType","","PsuLowUChangeMode",pParas->m_nFaultType);
#endif

	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolTime(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压滑差","dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize("电压变化终值","Vend","V","number",pParas->m_fVend);
    pXmlSierialize->xml_serialize("滑差计时设置参数","DvdtTiming","","number",pParas->m_nDvdtTiming);
#else
	pXmlSierialize->xml_serialize(/* "电压滑差" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize(/* "电压变化终值" */g_sLangTxt_Native_FinalVoltChange.GetString(),"Vend","V","number",pParas->m_fVend);
    pXmlSierialize->xml_serialize("滑差计时设置参数","DvdtTiming","","number",pParas->m_nDvdtTiming);
#endif


	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolDvDt(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
 	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "V/s","number",pParas->m_fDvdtStart);
 	pXmlSierialize->xml_serialize("变化终值", "EndVal", "V/s","number",pParas->m_fDvdtEnd);
 	pXmlSierialize->xml_serialize("变化步长", "Step", "V/s","number",pParas->m_fDvdtStep);
 	pXmlSierialize->xml_serialize("电压变化终值", "Vend", "V","number",pParas->m_fVend);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
		pXmlSierialize->xml_serialize("变化始值", "DvdtStart", "V/s","number",pParas->m_fDvdtStart);
		pXmlSierialize->xml_serialize("变化终值", "DvdtEnd", "V/s","number",pParas->m_fDvdtEnd);
		pXmlSierialize->xml_serialize("变化步长", "DvdtStep", "V/s","number",pParas->m_fDvdtStep);
	}
#else
 	pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "V/s","number",pParas->m_fDvdtStart);
 	pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "V/s","number",pParas->m_fDvdtEnd);
 	pXmlSierialize->xml_serialize(/* "变化步长" */g_sLangTxt_Gradient_Step.GetString(), "Step", "V/s","number",pParas->m_fDvdtStep);
 	pXmlSierialize->xml_serialize(/* "电压变化终值" */g_sLangTxt_Native_FinalVoltChange.GetString(), "Vend", "V","number",pParas->m_fVend);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
		pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "DvdtStart", "V/s","number",pParas->m_fDvdtStart);
		pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "DvdtEnd", "V/s","number",pParas->m_fDvdtEnd);
		pXmlSierialize->xml_serialize(/* "变化步长" */g_sLangTxt_Gradient_Step.GetString(), "DvdtStep", "V/s","number",pParas->m_fDvdtStep);
	}
#endif

	stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolILock( tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize )
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压滑差","dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "A","number",pParas->m_fIStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "A","number",pParas->m_fIEnd);
	pXmlSierialize->xml_serialize("变化步长", "Step", "A","number",pParas->m_fIStep);
	pXmlSierialize->xml_serialize("电流输出相", "IVariable", "","number",pParas->m_nIPhase);
	pXmlSierialize->xml_serialize("电压变化终值", "Vend", "V","number",pParas->m_fVend);

#else
	pXmlSierialize->xml_serialize(/* "电压滑差" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdt","V/s","number",pParas->m_fDvdt);
	pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "A","number",pParas->m_fIStart);
	pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "A","number",pParas->m_fIEnd);
	pXmlSierialize->xml_serialize(/* "变化步长" */g_sLangTxt_Gradient_Step.GetString(), "Step", "A","number",pParas->m_fIStep);
	pXmlSierialize->xml_serialize(/* "电流输出相" */g_sLangTxt_Native_IChangePhase.GetString(), "IVariable", "","number",pParas->m_nIPhase);
	pXmlSierialize->xml_serialize(/* "电压变化终值" */g_sLangTxt_Native_FinalVoltChange.GetString(), "Vend", "V","number",pParas->m_fVend);
#endif

	stt_xml_serialize_Common(pParas,pXmlSierialize);

}

void stt_xml_serialize_PnvLowVolAct(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("电压滑差","Dvdt","V/s","number",pParas->m_fDvdt);
    pXmlSierialize->xml_serialize("变化始值","BeginVal","V","number",pParas->m_fVstart);
    pXmlSierialize->xml_serialize("变化终值","EndVal","V","number",pParas->m_fVend);
    pXmlSierialize->xml_serialize("测试精度","Step","V","number",pParas->m_fVstep);

    pXmlSierialize->xml_serialize("电压变化量","VolVari","","LowVolVari",pParas->m_nFaultType);
    pXmlSierialize->xml_serialize("保持时间","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("试验前复归时间","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("待测定值","ValSetting","V","number",pParas->m_fUAct);
    pXmlSierialize->xml_serialize("电压定义","VSetMode","","VSetMode",pParas->m_nUSetMode);

    pXmlSierialize->xml_serialize("故障Ia","_FaultIa","A","set",pParas->m_uiCUR[1][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障Ib","_FaultIb","A","set",pParas->m_uiCUR[1][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障Ic","_FaultIc","A","set",pParas->m_uiCUR[1][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障Ia相位","_FaultIaPh","°","number",pParas->m_uiCUR[1][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障Ib相位","_FaultIbPh","°","number",pParas->m_uiCUR[1][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障Ic相位","_FaultIcPh","°","number",pParas->m_uiCUR[1][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障Ua相位","_FaultUaPh","°","number",pParas->m_uiVOL[1][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障Ub相位","_FaultUbPh","°","number",pParas->m_uiVOL[1][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障Uc相位","_FaultUcPh","°","number",pParas->m_uiVOL[1][2].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("故障前Ia","_PreFaultIa","A","set",pParas->m_uiCUR[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ib","_PreFaultIb","A","set",pParas->m_uiCUR[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ic","_PreFaultIc","A","set",pParas->m_uiCUR[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ia相位","_PreFaultIaPh","°","number",pParas->m_uiCUR[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Ib相位","_PreFaultIbPh","°","number",pParas->m_uiCUR[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Ic相位","_PreFaultIcPh","°","number",pParas->m_uiCUR[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Ua","_PreFaultUa","V","set",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ub","_PreFaultUb","V","set",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Uc","_PreFaultUc","V","set",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ua相位","_PreFaultUaPh","°","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Ub相位","_PreFaultUbPh","°","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Uc相位","_PreFaultUcPh","°","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);


    stt_xml_serialize_binary_out(pParas->m_binOut,pXmlSierialize);
    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);

}

void stt_xml_serialize_PnvLowVolTime(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("电压滑差","Dvdt","V/s","number",pParas->m_fDvdt);
    pXmlSierialize->xml_serialize("变化终止值","RampTo","V","number",pParas->m_fVend);

    pXmlSierialize->xml_serialize("保持时间","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("试验前复归时间","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("计时启动值","TimerStartValue","V","number",pParas->m_fUActTime);
    pXmlSierialize->xml_serialize("闭锁电压定义","VSetMode","","VSetMode",pParas->m_nUSetMode);

    pXmlSierialize->xml_serialize("Ia","Ia","A","set",pParas->m_uiCUR[1][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib","Ib","A","set",pParas->m_uiCUR[1][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic","Ic","A","set",pParas->m_uiCUR[1][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia相位","IaPh","°","number",pParas->m_uiCUR[1][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib相位","IbPh","°","number",pParas->m_uiCUR[1][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic相位","IcPh","°","number",pParas->m_uiCUR[1][2].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("故障前Ua","_PreFaultUa","V","set",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ub","_PreFaultUb","V","set",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Uc","_PreFaultUc","V","set",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ua相位","_PreFaultUaPh","°","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Ub相位","_PreFaultUbPh","°","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Uc相位","_PreFaultUcPh","°","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);

    stt_xml_serialize_binary_out(pParas->m_binOut,pXmlSierialize);
    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);

}

void stt_xml_serialize_PnvLowVolDvDt(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("变化始值", "BeginVal", "V/s","number",pParas->m_fDvdtStart);
    pXmlSierialize->xml_serialize("变化终值", "EndVal", "V/s","number",pParas->m_fDvdtEnd);
    pXmlSierialize->xml_serialize("变化步长", "Step", "V/s","number",pParas->m_fDvdtStep);
    pXmlSierialize->xml_serialize("电压变化终值", "Vend", "V","number",pParas->m_fVend);

    pXmlSierialize->xml_serialize("保持时间","TimeAfterTrig","s","number",pParas->m_fHoldTime);
    pXmlSierialize->xml_serialize("试验前复归时间","RampResetTime","s","number",pParas->m_fPreFaultTime);

    pXmlSierialize->xml_serialize("待测定值","ValSetting","V","number",pParas->m_fDvdtClose);
    pXmlSierialize->xml_serialize("电压定义","VSetMode","","VSetMode",pParas->m_nUSetMode);

    pXmlSierialize->xml_serialize("故障Ia","_FaultIa","A","set",pParas->m_uiCUR[1][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障Ib","_FaultIb","A","set",pParas->m_uiCUR[1][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障Ic","_FaultIc","A","set",pParas->m_uiCUR[1][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障Ia相位","_FaultIaPh","°","number",pParas->m_uiCUR[1][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障Ib相位","_FaultIbPh","°","number",pParas->m_uiCUR[1][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障Ic相位","_FaultIcPh","°","number",pParas->m_uiCUR[1][2].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("故障前Ia","_PreFaultIa","A","set",pParas->m_uiCUR[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ib","_PreFaultIb","A","set",pParas->m_uiCUR[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ic","_PreFaultIc","A","set",pParas->m_uiCUR[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ia相位","_PreFaultIaPh","°","number",pParas->m_uiCUR[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Ib相位","_PreFaultIbPh","°","number",pParas->m_uiCUR[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Ic相位","_PreFaultIcPh","°","number",pParas->m_uiCUR[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Ua","_PreFaultUa","V","set",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ub","_PreFaultUb","V","set",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Uc","_PreFaultUc","V","set",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("故障前Ua相位","_PreFaultUaPh","°","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Ub相位","_PreFaultUbPh","°","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("故障前Uc相位","_PreFaultUcPh","°","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);


    stt_xml_serialize_binary_out(pParas->m_binOut,pXmlSierialize);
    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic",pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);

}

void stt_xml_serialize_LowVol_search_results(tmt_LowVolParas *pParas,tmt_LowVolResults *pResults,CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSerialize->xml_serialize("当前搜索滑差值(dvdt)","CurrSearchDvdt","","number",pParas->m_fCurrSearchDvdt);
#else
	pXmlSerialize->xml_serialize(/* "当前搜索滑差值(dvdt)" */g_sLangTxt_Native_SearchslipVal2.GetString(),"CurrSearchDvdt","","number",pParas->m_fCurrSearchDvdt);
#endif

}

void stt_xml_serialize_PsuLowVolAct_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间(表达式)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("电压滑差(表达式)","dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize("电压变化始值(表达式)","VstartExp","","string",pParas->m_pszVstart);
	pXmlSierialize->xml_serialize("电压变化终值(表达式)","VendExp","","string",pParas->m_pszVend);
	pXmlSierialize->xml_serialize("电压变化步长(表达式)","VstepExp","","string",pParas->m_pszVstep);
#else
	pXmlSierialize->xml_serialize(/* "保持时间(表达式)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "电压滑差(表达式)" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize(/* "电压变化始值(表达式)" */g_sLangTxt_Native_VInitialValueExp.GetString(),"VstartExp","","string",pParas->m_pszVstart);
	pXmlSierialize->xml_serialize(/* "电压变化终值(表达式)" */g_sLangTxt_Native_VFinalValueExp.GetString(),"VendExp","","string",pParas->m_pszVend);
	pXmlSierialize->xml_serialize(/* "电压变化步长(表达式)" */g_sLangTxt_Native_VChangeStepExp.GetString(),"VstepExp","","string",pParas->m_pszVstep);
#endif
	stt_xml_serialize_PsuLowVolAct(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolTime_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间(表达式)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("电压滑差(表达式)","dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize("电压变化终值(表达式)","VendExp","","string",pParas->m_pszVend);
#else
	pXmlSierialize->xml_serialize(/* "保持时间(表达式)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "电压滑差(表达式)" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize(/* "电压变化终值(表达式)" */g_sLangTxt_Native_VFinalValueExp.GetString(),"VendExp","","string",pParas->m_pszVend);
#endif

	stt_xml_serialize_PsuLowVolTime(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolDvDt_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保持时间(表达式)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("电压变化终值(表达式)","VendExp","","string",pParas->m_pszVend);

	pXmlSierialize->xml_serialize("滑差变化始值(表达式)", "BeginValExp", "","string",pParas->m_pszDvdtStart);
	pXmlSierialize->xml_serialize("滑差变化终值(表达式)", "EndValExp", "","string",pParas->m_pszDvdtEnd);
	pXmlSierialize->xml_serialize("滑差变化步长(表达式)", "StepExp", "","string",pParas->m_pszDvdtStep);
#else
	pXmlSierialize->xml_serialize(/* "保持时间(表达式)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "电压变化终值(表达式)" */g_sLangTxt_Native_VFinalValueExp.GetString(),"VendExp","","string",pParas->m_pszVend);

	pXmlSierialize->xml_serialize(/* "滑差变化始值(表达式)" */g_sLangTxt_Native_SlipInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszDvdtStart);
	pXmlSierialize->xml_serialize(/* "滑差变化终值(表达式)" */g_sLangTxt_Native_SlipFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszDvdtEnd);
	pXmlSierialize->xml_serialize(/* "滑差变化步长(表达式)" */g_sLangTxt_Native_SlipChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszDvdtStep);
#endif

	stt_xml_serialize_PsuLowVolDvDt(pParas,pXmlSierialize);
}

void stt_xml_serialize_PsuLowVolILock_ex( tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize )
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压滑差(表达式)","dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize("电压变化终值(表达式)","VendExp","","string",pParas->m_pszVend);
	pXmlSierialize->xml_serialize("保持时间(表达式)","HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize("电流变化始值(表达式)", "BeginValExp", "","string",pParas->m_pszIStart);
	pXmlSierialize->xml_serialize("电流变化终值(表达式)", "EndValExp", "","string",pParas->m_pszIEnd);
	pXmlSierialize->xml_serialize("电流变化步长(表达式)", "StepExp", "","string",pParas->m_pszIStep);
#else
	pXmlSierialize->xml_serialize(/* "电压滑差(表达式)" */g_sLangTxt_Native_VoltSlip.GetString(),"dvdtExp","","string",pParas->m_pszDvdt);
	pXmlSierialize->xml_serialize(/* "电压变化终值(表达式)" */g_sLangTxt_Native_VFinalValueExp.GetString(),"VendExp","","string",pParas->m_pszVend);
	pXmlSierialize->xml_serialize(/* "保持时间(表达式)" */g_sLangTxt_Native_KeepTimeExp.GetString(),"HoldTimeExp","","string",pParas->m_pszHoldTime);
	pXmlSierialize->xml_serialize(/* "电流变化始值(表达式)" */g_sLangTxt_Native_IInitialValueExp.GetString(), "BeginValExp", "","string",pParas->m_pszIStart);
	pXmlSierialize->xml_serialize(/* "电流变化终值(表达式)" */g_sLangTxt_Native_IFinalValueExp.GetString(), "EndValExp", "","string",pParas->m_pszIEnd);
	pXmlSierialize->xml_serialize(/* "电流变化步长(表达式)" */g_sLangTxt_Native_IChangeStepExp.GetString(), "StepExp", "","string",pParas->m_pszIStep);
#endif
	stt_xml_serialize_PsuLowVolILock(pParas,pXmlSierialize);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_PsuLowVolAct(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("低压减载动作值","TripVol","V","number",pResults->m_fLowUAct);
	pXmlSierialize->xml_serialize("低压动作描述", "ActVol", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "低压减载动作值" */g_sLangTxt_Native_LowVoltUnderloadTripSet.GetString(),"TripVol","V","number",pResults->m_fLowUAct);
	pXmlSierialize->xml_serialize(/* "低压动作描述" */g_sLangTxt_Native_LowVActionDesc.GetString(), "ActVol", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PsuLowVolTime(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("低压减载动作时间","TTripLv","s","number",pResults->m_fLowUActTime);
	pXmlSierialize->xml_serialize("动作描述", "ActLv", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "低压减载动作时间" */g_sLangTxt_Native_LowVoltUnderloadTripSet.GetString(),"TTripLv","s","number",pResults->m_fLowUActTime);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActLv", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PsuLowVolDvDt(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压滑差动作值", "TripDvdt", "V/s", "number",pResults->m_fDvdtAct);
	pXmlSierialize->xml_serialize("动作描述", "ActDvdt", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "电压滑差动作值" */g_sLangTxt_Native_VoltSlipAct.GetString(), "TripDvdt", "V/s", "number",pResults->m_fDvdtAct);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActDvdt", "", "number",pResults->m_nAct);
#endif

}
void stt_xml_serialize_PsuLowVolILock( tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize )
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("低电流闭锁值测试", "TripILock", "A", "number",pResults->m_fIAct);
	pXmlSierialize->xml_serialize("动作描述", "ActILock", "", "number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize( "低电流闭锁值测试" , "TripILock", "A", "number",pResults->m_fIAct);
	pXmlSierialize->xml_serialize( "动作描述" , "ActILock", "", "number",pResults->m_nAct);
#endif
}
void stt_xml_serialize_PnvLowVolAct(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("低压减载动作值","TripVol","V","number",pResults->m_fLowUAct);
    pXmlSierialize->xml_serialize("低压动作描述", "ActVol", "", "number",pResults->m_nAct);
    pXmlSierialize->xml_serialize("结果判断","RsltJdg","","number",pResults->m_nAct);
    pXmlSierialize->xml_serialize("结果描述","RsltDsc","","number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "低压减载动作值" */g_sLangTxt_Native_LowVoltUnderloadTripSet.GetString(),"TripVol","V","number",pResults->m_fLowUAct);
    pXmlSierialize->xml_serialize(/* "低压动作描述" */g_sLangTxt_Native_LowVActionDesc.GetString(), "ActVol", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PnvLowVolTime(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("低压减载动作时间","TTripLv","s","number",pResults->m_fLowUActTime);
    pXmlSierialize->xml_serialize("动作描述", "ActLv", "", "number",pResults->m_nAct);
    pXmlSierialize->xml_serialize("结果判断","RsltJdg","","number",pResults->m_nAct);
    pXmlSierialize->xml_serialize("结果描述","RsltDsc","","number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "低压减载动作时间" */g_sLangTxt_Native_LowVoltUnderloadTripSet.GetString(),"TTripLv","s","number",pResults->m_fLowUActTime);
    pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActLv", "", "number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_PnvLowVolDvDt(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("动作值", "TripDvdt", "V/s", "number",pResults->m_fDvdtAct);
    pXmlSierialize->xml_serialize("动作描述", "ActDfdt", "", "number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "电压滑差动作值" */g_sLangTxt_Native_VoltSlipAct.GetString(), "TripDvdt", "V/s", "number",pResults->m_fDvdtAct);
    pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActDvdt", "", "number",pResults->m_nAct);
#endif

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttXmlSerializeBase* stt_xml_serialize(tmt_LowVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolAct) == 0)
		{
			stt_xml_serialize_PsuLowVolAct_ex(&(pTests->m_oLowVolParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolTime) == 0)
		{
			stt_xml_serialize_PsuLowVolTime_ex(&(pTests->m_oLowVolParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolDvdt) == 0)
		{
			stt_xml_serialize_PsuLowVolDvDt_ex(&(pTests->m_oLowVolParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolILock) == 0)
		{
			stt_xml_serialize_PsuLowVolILock_ex(&(pTests->m_oLowVolParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolAct) == 0)
		{
			stt_xml_serialize_PsuLowVolAct(&pTests->m_oLowVolResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolTime) == 0)
		{
			stt_xml_serialize_PsuLowVolTime(&pTests->m_oLowVolResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolDvdt) == 0)
		{
			stt_xml_serialize_PsuLowVolDvDt(&(pTests->m_oLowVolResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuLowVolILock) == 0)
		{
			stt_xml_serialize_PsuLowVolILock(&(pTests->m_oLowVolResults), pXmlResults);
		}
	}

	return pXmlParas;
}
CSttXmlSerializeBase* stt_xml_serialize(tmt_PnvLowVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolAct) == 0)
        {
            stt_xml_serialize_PnvLowVolAct(&(pTests->m_oLowVolParas), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolTime) == 0)
        {
            stt_xml_serialize_PnvLowVolTime(&(pTests->m_oLowVolParas), pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolDvdt) == 0)
        {
            stt_xml_serialize_PnvLowVolDvDt(&(pTests->m_oLowVolParas), pXmlParas);
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolAct) == 0)
        {
            stt_xml_serialize_PnvLowVolAct(&pTests->m_oLowVolResults, pXmlResults);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolTime) == 0)
        {
            stt_xml_serialize_PnvLowVolTime(&pTests->m_oLowVolResults, pXmlResults);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PnvLowVolDvdt) == 0)
        {
            stt_xml_serialize_PnvLowVolDvDt(&(pTests->m_oLowVolResults), pXmlParas);
        }
    }

    return pXmlParas;
}
