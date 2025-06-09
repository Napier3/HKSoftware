#include "stdafx.h"
#include "tmt_current_act_value_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_CurrentActValueParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_CurrentActValueParas));
	pParas->init();
}

void stt_init_results(tmt_CurrentActValueResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_CurrentActValueResults));
	pResults->init();
}

void stt_init_paras(tmt_CurActValuePnvParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_CurActValuePnvParas));
    pParas->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_CurrentActValueParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize("动作时间定值", "TSetting", "s", "set", pParas->m_fSettingActTime);
	pXmlSierialize->xml_serialize("故障类型", "VarIndex", "", "SystemFault", pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("待测定值", "ValSetting", "", "set", pParas->m_fSettingValue);
	pXmlSierialize->xml_serialize("故障时间裕度","StepTimeAdded","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("故障阻抗角","ZLAng_Fault","","number",pParas->m_fImpAngle);
	pXmlSierialize->xml_serialize("短路电压","FaultVf","","number",pParas->m_fFaultVol);
	pXmlSierialize->xml_serialize("是否模拟PT断线","PTBreak","","BOOL",pParas->m_bImitatePT); 
	pXmlSierialize->xml_serialize("模拟PT断线相别", "PTBreakPhase", "", "DiffFaultType",pParas->m_nImitPTPhase); //状态序列过流,将是否模拟PT断线和PT断线相别分为两个参数;采用固定短路电压的方式,未用到短路阻抗
	pXmlSierialize->xml_serialize("故障方向","FaultDirection","","FaultDirection",pParas->m_nFaultDir); 
#else
        pXmlSierialize->xml_serialize(/* "变化始值" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
        pXmlSierialize->xml_serialize(/* "变化终值" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop);
        pXmlSierialize->xml_serialize(/* "测试精度" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
        pXmlSierialize->xml_serialize(/* "动作时间定值" */ g_sLangTxt_Native_OpTimeSet.GetString(), "TSetting", "s", "set", pParas->m_fSettingActTime);
        pXmlSierialize->xml_serialize(/* "故障类型" */ g_sLangTxt_Gradient_FailType.GetString(), "VarIndex", "", "SystemFault", pParas->m_nFaultType);
  pXmlSierialize->xml_serialize(/* "待测定值" */ g_sLangTxt_Native_UnderTestValue.GetString(), "ValSetting", "", "set", pParas->m_fSettingValue);
  pXmlSierialize->xml_serialize(/* "故障时间裕度" */ g_sLangTxt_Native_FaultTimeMargin.GetString(), "StepTimeAdded", "s", "number", pParas->m_fMarginTime);
  pXmlSierialize->xml_serialize(/* "故障阻抗角" */ g_sLangTxt_Native_FaultImpedanceAngle.GetString(), "ZLAng_Fault", "", "number", pParas->m_fImpAngle);
  pXmlSierialize->xml_serialize(/* "短路电压" */ g_sLangTxt_Native_ShortCircuitV.GetString(), "FaultVf", "", "number", pParas->m_fFaultVol);
  pXmlSierialize->xml_serialize(/* "是否模拟PT断线" */ g_sLangTxt_Native_PTLineSimulate.GetString(), "PTBreak", "", "BOOL", pParas->m_bImitatePT);
  pXmlSierialize->xml_serialize(/* "模拟PT断线相别" */ g_sLangTxt_Native_PTLineSimPhase.GetString(), "PTBreakPhase", "", "DiffFaultType",
                                pParas->m_nImitPTPhase);  // 状态序列过流,将是否模拟PT断线和PT断线相别分为两个参数;采用固定短路电压的方式,未用到短路阻抗
  pXmlSierialize->xml_serialize(/* "故障方向" */ g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir);
#endif
	stt_xml_serialize_common(pParas,pXmlSierialize);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize(tmt_CurActValuePnvParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
    pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("整定动作时间", "TSetting", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("试验前复归时间","RampResetTime","s","number",pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("故障前复归时间","FaultResetTime","s","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("每步时间裕度","StepTimeAdded","s","number",pParas->m_fMarginTime);
    pXmlSierialize->xml_serialize("测试相别", "VarIndex", "", "URampIndex", pParas->m_nFaultType);

    pXmlSierialize->xml_serialize("Ia","Ia","A","set",pParas->m_uiCUR[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib","Ib","A","set",pParas->m_uiCUR[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic","Ic","A","set",pParas->m_uiCUR[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia相位","IaPh","°","number",pParas->m_uiCUR[2][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib相位","IbPh","°","number",pParas->m_uiCUR[2][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic相位","IcPh","°","number",pParas->m_uiCUR[2][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua","Ua","V","set",pParas->m_uiVOL[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub","Ub","V","set",pParas->m_uiVOL[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc","Uc","V","set",pParas->m_uiVOL[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uz","Uz","V","set",pParas->m_uiVOL[2][3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua相位","UaPh","°","number",pParas->m_uiVOL[2][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub相位","UbPh","°","number",pParas->m_uiVOL[2][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc相位","UcPh","°","number",pParas->m_uiVOL[2][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uz相位","UzPh","°","number",pParas->m_uiVOL[2][3].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("复归Ia","Ia0","A","set",pParas->m_uiCUR[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Ib","Ib0","A","set",pParas->m_uiCUR[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Ic","Ic0","A","set",pParas->m_uiCUR[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Ia相位","Ia0Ph","°","number",pParas->m_uiCUR[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("复归Ib相位","Ib0Ph","°","number",pParas->m_uiCUR[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("复归Ic相位","Ic0Ph","°","number",pParas->m_uiCUR[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("复归Ua","Ua0","V","set",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Ub","Ub0","V","set",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Uc","Uc0","V","set",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Uz","Uz0","V","set",pParas->m_uiVOL[0][3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Ua相位","Ua0Ph","°","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("复归Ub相位","Ub0Ph","°","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("复归Uc相位","Uc0Ph","°","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("复归Uz相位","Uz0Ph","°","number",pParas->m_uiVOL[0][3].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic",pParas->m_nBinLogic);
    pXmlSierialize->xml_serialize("开入A选择", "_BinSelectA", "", "BOOL", pParas->m_binIn[0].nSelect);
    pXmlSierialize->xml_serialize("开入B选择", "_BinSelectB", "", "BOOL", pParas->m_binIn[1].nSelect);
    pXmlSierialize->xml_serialize("开入C选择", "_BinSelectC", "", "BOOL", pParas->m_binIn[2].nSelect);
    pXmlSierialize->xml_serialize("开入R选择", "_BinSelectR", "", "BOOL", pParas->m_binIn[3].nSelect);
    pXmlSierialize->xml_serialize("开入a选择", "_BinSelecta", "", "BOOL", pParas->m_binIn[4].nSelect);
    pXmlSierialize->xml_serialize("开入b选择", "_BinSelectb", "", "BOOL", pParas->m_binIn[5].nSelect);
    pXmlSierialize->xml_serialize("开入c选择", "_BinSelectc", "", "BOOL", pParas->m_binIn[6].nSelect);
    pXmlSierialize->xml_serialize("开入r选择", "_BinSelectr", "", "BOOL", pParas->m_binIn[7].nSelect);

    pXmlSierialize->xml_serialize("开出1","_Bout1","","DOutputState",pParas->m_binOut[0][0].nState);
    pXmlSierialize->xml_serialize("开出2","_Bout2","","DOutputState",pParas->m_binOut[0][1].nState);
    pXmlSierialize->xml_serialize("开出3","_Bout3","","DOutputState",pParas->m_binOut[0][2].nState);
    pXmlSierialize->xml_serialize("开出4","_Bout4","","DOutputState",pParas->m_binOut[0][3].nState);

    pXmlSierialize->xml_serialize("开出1故障状态","_BoutF1","","DOutputState",pParas->m_binOut[1][0].nState);
    pXmlSierialize->xml_serialize("开出2故障状态","_BoutF2","","DOutputState",pParas->m_binOut[1][1].nState);
    pXmlSierialize->xml_serialize("开出3故障状态","_BoutF3","","DOutputState",pParas->m_binOut[1][2].nState);
    pXmlSierialize->xml_serialize("开出4故障状态","_BoutF4","","DOutputState",pParas->m_binOut[1][3].nState);
    pXmlSierialize->xml_serialize("开出保持时间","_BoutHoldTime","s","number",pParas->m_binOut[1][0].fHoldTime);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_current_actvalue(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作值","TripValue","A/V","number",pResults->m_fTripValue);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
	pXmlSierialize->xml_serialize("开入1动作值","TripValueA","A/V","number",pResults->m_fTripValueChl[0]);
	pXmlSierialize->xml_serialize("开入2动作值","TripValueB","A/V","number",pResults->m_fTripValueChl[1]);
	pXmlSierialize->xml_serialize("开入3动作值","TripValueC","A/V","number",pResults->m_fTripValueChl[2]);
	pXmlSierialize->xml_serialize("开入4动作值","TripValueD","A/V","number",pResults->m_fTripValueChl[3]);
	pXmlSierialize->xml_serialize("开入5动作值","TripValueE","A/V","number",pResults->m_fTripValueChl[4]);
	pXmlSierialize->xml_serialize("开入6动作值","TripValueF","A/V","number",pResults->m_fTripValueChl[5]);
	pXmlSierialize->xml_serialize("开入7动作值","TripValueG","A/V","number",pResults->m_fTripValueChl[6]);
	pXmlSierialize->xml_serialize("开入8动作值","TripValueH","A/V","number",pResults->m_fTripValueChl[7]);
#else
  pXmlSierialize->xml_serialize(/* "动作值" */ g_sLangTxt_State_ActionValue.GetString(), "TripValue", "A/V", "number", pResults->m_fTripValue);
  pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);
  pXmlSierialize->xml_serialize(/* "开入1动作值" */ g_sLangTxt_Native_input1_ActionVal.GetString(), "TripValueA", "A/V", "number", pResults->m_fTripValueChl[0]);
  pXmlSierialize->xml_serialize(/* "开入2动作值" */ g_sLangTxt_Native_input2_ActionVal.GetString(), "TripValueB", "A/V", "number", pResults->m_fTripValueChl[1]);
  pXmlSierialize->xml_serialize(/* "开入3动作值" */ g_sLangTxt_Native_input3_ActionVal.GetString(), "TripValueC", "A/V", "number", pResults->m_fTripValueChl[2]);
  pXmlSierialize->xml_serialize(/* "开入4动作值" */ g_sLangTxt_Native_input4_ActionVal.GetString(), "TripValueD", "A/V", "number", pResults->m_fTripValueChl[3]);
  pXmlSierialize->xml_serialize(/* "开入5动作值" */ g_sLangTxt_Native_input5_ActionVal.GetString(), "TripValueE", "A/V", "number", pResults->m_fTripValueChl[4]);
  pXmlSierialize->xml_serialize(/* "开入6动作值" */ g_sLangTxt_Native_input6_ActionVal.GetString(), "TripValueF", "A/V", "number", pResults->m_fTripValueChl[5]);
  pXmlSierialize->xml_serialize(/* "开入7动作值" */ g_sLangTxt_Native_input7_ActionVal.GetString(), "TripValueG", "A/V", "number", pResults->m_fTripValueChl[6]);
  pXmlSierialize->xml_serialize(/* "开入8动作值" */ g_sLangTxt_Native_input8_ActionVal.GetString(), "TripValueH", "A/V", "number", pResults->m_fTripValueChl[7]);
#endif
}

void stt_xml_serialize_cur_actvalue_pnv(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("动作值","TripValue","A/V","number",pResults->m_fTripValue);
    pXmlSierialize->xml_serialize("返回值","ReturnValue","A/V","number",pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_CurrentActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize_ex(&(pTests->m_oTmtParas),  pXmlParas);	//文件的读写
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize_current_actvalue(&pTests->m_oTmtResults,  pXmlResults);
	}

	return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_CurActValuePnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        stt_xml_serialize(&(pTests->m_oTmtParas),  pXmlParas);	//文件的读写
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        stt_xml_serialize_cur_actvalue_pnv(&pTests->m_oTmtResults,  pXmlResults);
    }

    return pXmlParas;
}

