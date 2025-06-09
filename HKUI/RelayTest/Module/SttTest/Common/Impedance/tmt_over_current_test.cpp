#include "stdafx.h"
#include "tmt_over_current_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_OverCurrentParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_OverCurrentParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_OverCurrentParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_OverCurrentParasEx));
	pParas->init();
}

void stt_init_results(tmt_OverCurrentResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_OverCurrentResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serializeOverCurrentSetting(tmt_OverCurrentParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//整定值
	pXmlSierialize->xml_serialize("过流I段定值","Iset1","Ω","float",pParas->m_fSettingOverCur[0]);
	pXmlSierialize->xml_serialize("过流II段定值","Iset2","Ω","float",pParas->m_fSettingOverCur[1]);
	pXmlSierialize->xml_serialize("过流III段定值","Iset3","Ω","float",pParas->m_fSettingOverCur[2]);
	pXmlSierialize->xml_serialize("过流IV段定值","Iset4","Ω","float",pParas->m_fSettingOverCur[3]);
	pXmlSierialize->xml_serialize("过流V段定值","Iset5","Ω","float",pParas->m_fSettingOverCur[4]);

	pXmlSierialize->xml_serialize("过流I段时间","Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize("过流II段时间","Tset2","s","float",pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize("过流III段时间","Tset3","s","float",pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize("过流IV段时间","Tset4","s","float",pParas->m_fSettingTime[3]);
	pXmlSierialize->xml_serialize("过流V段时间","Tset5","s","float",pParas->m_fSettingTime[4]);
#else
	//整定值
	pXmlSierialize->xml_serialize(/* "过流I段定值" */g_sLangTxt_Native_OverCurrentI.GetString(),"Iset1","Ω","float",pParas->m_fSettingOverCur[0]);
	pXmlSierialize->xml_serialize(/* "过流II段定值" */g_sLangTxt_Native_OverCurrentII.GetString(),"Iset2","Ω","float",pParas->m_fSettingOverCur[1]);
	pXmlSierialize->xml_serialize(/* "过流III段定值" */g_sLangTxt_Native_OverCurrentIII.GetString(),"Iset3","Ω","float",pParas->m_fSettingOverCur[2]);
	pXmlSierialize->xml_serialize(/* "过流IV段定值" */g_sLangTxt_Native_OverCurrentIV.GetString(),"Iset4","Ω","float",pParas->m_fSettingOverCur[3]);
	pXmlSierialize->xml_serialize(/* "过流V段定值" */g_sLangTxt_Native_OverCurrentV.GetString(),"Iset5","Ω","float",pParas->m_fSettingOverCur[4]);

	pXmlSierialize->xml_serialize(/* "过流I段时间" */g_sLangTxt_Native_OverCurrentITime.GetString(),"Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize(/* "过流II段时间" */g_sLangTxt_Native_OverCurrentIITime.GetString(),"Tset2","s","float",pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize(/* "过流III段时间" */g_sLangTxt_Native_OverCurrentIIITime.GetString(),"Tset3","s","float",pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize(/* "过流IV段时间" */g_sLangTxt_Native_OverCurrentIVTime.GetString(),"Tset4","s","float",pParas->m_fSettingTime[3]);
	pXmlSierialize->xml_serialize(/* "过流V段时间" */g_sLangTxt_Native_OverCurrentVTime.GetString(),"Tset5","s","float",pParas->m_fSettingTime[4]);
#endif

}


void stt_xml_serialize_OverCurrent(tmt_OverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("故障类型", "FaultType", "无", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("整定动作电流", "ISetting", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("倍数", "Rate", "无", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("动作时间定值", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("短路阻抗", "Z", "Ω", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize("短路阻抗角", "ZPh", "°", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize("故障性质","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize("模拟PT断线相别", "ImitPTPhase", "", "PTBreakPnv",pParas->m_nImitPTPhase); 
	//Pnv过流试验,将是否模拟PT断线和PT断线相别分为合并为1个参数,为0时固定不模拟PT断线,依次为1时模拟A相断线;
	//采用固定短路阻抗的方式,未用到短路电压

	pXmlSierialize->xml_serialize("保护动作后持续时间","PostFaultTime","s","number",pParas->m_fPostFaultTime);

	pXmlSierialize->xml_serialize("Ua幅值", "_Ua", "V", "number",  pParas->m_fVolAmp[0]);
	pXmlSierialize->xml_serialize("Ub幅值", "_Ub", "V", "number",  pParas->m_fVolAmp[1]);
	pXmlSierialize->xml_serialize("Uc幅值", "_Uc", "V", "number",  pParas->m_fVolAmp[2]);
	pXmlSierialize->xml_serialize("Uz幅值", "_Uz", "V", "number",  pParas->m_fVolAmp[3]);

	pXmlSierialize->xml_serialize("Ua相位", "_UaPh", "°", "number",  pParas->m_fVolAng[0]);
	pXmlSierialize->xml_serialize("Ub相位", "_UbPh", "°", "number",  pParas->m_fVolAng[1]);
	pXmlSierialize->xml_serialize("Uc相位", "_UcPh", "°", "number",  pParas->m_fVolAng[2]);
	pXmlSierialize->xml_serialize("Uz相位", "_UzPh", "°", "number",  pParas->m_fVolAng[3]);

	pXmlSierialize->xml_serialize("故障Ua幅值", "_FaultUa", "V", "number",  pParas->m_fVolAmp[4]);
	pXmlSierialize->xml_serialize("故障Ub幅值", "_FaultUb", "V", "number",  pParas->m_fVolAmp[5]);
	pXmlSierialize->xml_serialize("故障Uc幅值", "_FaultUc", "V", "number",  pParas->m_fVolAmp[6]);
	pXmlSierialize->xml_serialize("故障Uz幅值", "_FaultUx", "V", "number",  pParas->m_fVolAmp[7]);

	pXmlSierialize->xml_serialize("故障Ua相位", "_FaultUaPh", "°", "number",  pParas->m_fVolAng[4]);
	pXmlSierialize->xml_serialize("故障Ub相位", "_FaultUbPh", "°", "number",  pParas->m_fVolAng[5]);
	pXmlSierialize->xml_serialize("故障Uc相位", "_FaultUcPh", "°", "number",  pParas->m_fVolAng[6]);
	pXmlSierialize->xml_serialize("故障Uz相位", "_FaultUzPh", "°", "number",  pParas->m_fVolAng[7]);
#else
	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", /* "无" */g_sLangTxt_without.GetString(), "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "整定动作电流" */g_sLangTxt_Native_SetPickCurr.GetString(), "ISetting", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "倍数" */g_sLangTxt_Native_Multiple.GetString(), "Rate", /* "无" */g_sLangTxt_without.GetString(), "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "动作时间定值" */g_sLangTxt_Native_OpTimeSet.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "故障方向" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "短路阻抗" */g_sLangTxt_Native_ShortZImp.GetString(), "Z", "Ω", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize(/* "短路阻抗角" */g_sLangTxt_Native_ShortZImpAng.GetString(), "ZPh", "°", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize(/* "故障性质" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize(/* "模拟PT断线相别" */g_sLangTxt_Native_PTLineSimPhase.GetString(), "ImitPTPhase", "", "PTBreakPnv",pParas->m_nImitPTPhase); 
	//Pnv过流试验,将是否模拟PT断线和PT断线相别分为合并为1个参数,为0时固定不模拟PT断线,依次为1时模拟A相断线;
	//采用固定短路阻抗的方式,未用到短路电压

	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */g_sLangTxt_Native_DurProtTrip.GetString(),"PostFaultTime","s","number",pParas->m_fPostFaultTime);

	pXmlSierialize->xml_serialize(/* "Ua幅值" */g_sLangTxt_Native_UaAmplitude.GetString(), "_Ua", "V", "number",  pParas->m_fVolAmp[0]);
	pXmlSierialize->xml_serialize(/* "Ub幅值" */g_sLangTxt_Native_UbAmplitude.GetString(), "_Ub", "V", "number",  pParas->m_fVolAmp[1]);
	pXmlSierialize->xml_serialize(/* "Uc幅值" */g_sLangTxt_Native_UcAmplitude.GetString(), "_Uc", "V", "number",  pParas->m_fVolAmp[2]);
	pXmlSierialize->xml_serialize(/* "Uz幅值" */g_sLangTxt_Native_UzAmp.GetString(), "_Uz", "V", "number",  pParas->m_fVolAmp[3]);

	pXmlSierialize->xml_serialize(/* "Ua相位" */g_sLangTxt_Native_UaPhase.GetString(), "_UaPh", "°", "number",  pParas->m_fVolAng[0]);
	pXmlSierialize->xml_serialize(/* "Ub相位" */g_sLangTxt_Native_UbPhase.GetString(), "_UbPh", "°", "number",  pParas->m_fVolAng[1]);
	pXmlSierialize->xml_serialize(/* "Uc相位" */g_sLangTxt_Native_UcPhase.GetString(), "_UcPh", "°", "number",  pParas->m_fVolAng[2]);
	pXmlSierialize->xml_serialize(/* "Uz相位" */g_sLangTxt_Native_UzPhase.GetString(), "_UzPh", "°", "number",  pParas->m_fVolAng[3]);

	pXmlSierialize->xml_serialize(/* "故障Ua幅值" */g_sLangTxt_Native_ErrUaAmp.GetString(), "_FaultUa", "V", "number",  pParas->m_fVolAmp[4]);
	pXmlSierialize->xml_serialize(/* "故障Ub幅值" */g_sLangTxt_Native_ErrUbAmp.GetString(), "_FaultUb", "V", "number",  pParas->m_fVolAmp[5]);
	pXmlSierialize->xml_serialize(/* "故障Uc幅值" */g_sLangTxt_Native_ErrUcAmp.GetString(), "_FaultUc", "V", "number",  pParas->m_fVolAmp[6]);
	pXmlSierialize->xml_serialize(/* "故障Uz幅值" */g_sLangTxt_Native_ErrUzAmp.GetString(), "_FaultUx", "V", "number",  pParas->m_fVolAmp[7]);

	pXmlSierialize->xml_serialize(/* "故障Ua相位" */g_sLangTxt_Native_ErrUaPh.GetString(), "_FaultUaPh", "°", "number",  pParas->m_fVolAng[4]);
	pXmlSierialize->xml_serialize(/* "故障Ub相位" */g_sLangTxt_Native_ErrUbPh.GetString(), "_FaultUbPh", "°", "number",  pParas->m_fVolAng[5]);
	pXmlSierialize->xml_serialize(/* "故障Uc相位" */g_sLangTxt_Native_ErrUcPh.GetString(), "_FaultUcPh", "°", "number",  pParas->m_fVolAng[6]);
	pXmlSierialize->xml_serialize(/* "故障Uz相位" */g_sLangTxt_Native_ErrUzPh.GetString(), "_FaultUzPh", "°", "number",  pParas->m_fVolAng[7]);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serializeOverCurrentSetting(pParas,pXmlSierialize);
}

void stt_xml_serialize_OverCurrent_ex(tmt_OverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_OverCurrent(pParas,pXmlSierialize);

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("整定动作电流(表达式)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	pXmlSierialize->xml_serialize(/* "整定动作电流(表达式)" */g_sLangTxt_Native_SetActCurExp.GetString(), "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "动作时间定值(表达式)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_StateOverCurrent(tmt_OverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.26 caoxc 增加项目分组ID
	pXmlSierialize->xml_serialize("分组", "GroupID", "无", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize("故障类型", "FaultType", "无", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("整定动作时间", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("整定动作电流", "FaultIf", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("倍数", "Rate", "无", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("短路电压", "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("是否模拟PT断线","PTBreak","","BOOL",pParas->m_bImitatePT); 
	pXmlSierialize->xml_serialize("模拟PT断线相别", "PTBreakPhase", "", "DiffFaultType",pParas->m_nImitPTPhase); //状态序列过流,将是否模拟PT断线和PT断线相别分为两个参数;采用固定短路电压的方式,未用到短路阻抗
	pXmlSierialize->xml_serialize("保护动作后持续时间","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
    if (stt_xml_serialize_is_read(pXmlSierialize))//Pnv
    {
        pXmlSierialize->xml_serialize("短路电流", "ShortCur", "A", "number", pParas->m_fSetting[0]);
        pXmlSierialize->xml_serialize("短路电压", "ShortVol", "V", "number", pParas->m_fSCVoltage[0]);
        //最大故障时间为整定动作时间，但该id被用于故障时间裕度，实际为二者求和，最大故障实际转为故障时间裕度处理
        //pXmlSierialize->xml_serialize("最大故障时间", "FaultTime", "s", "set", pParas->m_fTSetting);
        pXmlSierialize->xml_serialize("故障前电压", "PreFaultUa", "V", "number", pParas->m_fUNom);
        pXmlSierialize->xml_serialize("故障前电流", "PreFaulIa", "A", "number",pParas->m_fIfh);
        pXmlSierialize->xml_serialize("故障前阻抗角", "PreFaulPhi", "°", "number",pParas->m_fPowerAngle);
    }
#else
	//2022.5.26 caoxc 增加项目分组ID
	pXmlSierialize->xml_serialize(/* "分组" */g_sLangTxt_Native_Grouping.GetString(), "GroupID", /* "无" */g_sLangTxt_without.GetString(), "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", /* "无" */g_sLangTxt_without.GetString(), "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "整定动作时间" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "整定动作电流" */g_sLangTxt_Native_SetPickCurr.GetString(), "FaultIf", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "倍数" */g_sLangTxt_Native_SetPickCurr.GetString(), "Rate", /* "无" */g_sLangTxt_without.GetString(), "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "短路电压" */g_sLangTxt_Native_SetPickCurr.GetString(), "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize(/* "故障方向" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "是否模拟PT断线" */g_sLangTxt_Native_PTLineSimulate.GetString(),"PTBreak","","BOOL",pParas->m_bImitatePT); 
	pXmlSierialize->xml_serialize(/* "模拟PT断线相别" */g_sLangTxt_Native_PTLineSimPhase.GetString(), "PTBreakPhase", "", "DiffFaultType",pParas->m_nImitPTPhase); //状态序列过流,将是否模拟PT断线和PT断线相别分为两个参数;采用固定短路电压的方式,未用到短路阻抗
	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serializeOverCurrentSetting(pParas,pXmlSierialize);
}

void stt_xml_serialize_StateOverCurrent_ex(tmt_OverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("整定动作电流(表达式)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	pXmlSierialize->xml_serialize(/* "整定动作电流(表达式)" */g_sLangTxt_Native_SetActCurExp.GetString(), "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "动作时间定值(表达式)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif
	stt_xml_serialize_StateOverCurrent(pParas,pXmlSierialize);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_OverCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("过流值", "IGL", "A", "number", pResults->m_fOverCurrent);
#else
	pXmlSierialize->xml_serialize(/* "过流值" */g_sLangTxt_Native_OverCurrentValue.GetString(), "IGL", "A", "number", pResults->m_fOverCurrent);
#endif
    pXmlSierialize->xml_serialize("开入E动作描述", "ActE", "", "number", pResults->m_nActID[4]);
    pXmlSierialize->xml_serialize("开入F动作描述", "ActF", "", "number", pResults->m_nActID[5]);
    pXmlSierialize->xml_serialize("开入G动作描述", "ActG", "", "number", pResults->m_nActID[6]);
    pXmlSierialize->xml_serialize("开入H动作描述", "ActH", "", "number", pResults->m_nActID[7]);

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_OverCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_OverCurrent) == 0)
		{
			stt_xml_serialize_OverCurrent_ex(&(pTests->m_oOverCurrentParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_StateOverCurrent) == 0)
		{
			stt_xml_serialize_StateOverCurrent_ex(&(pTests->m_oOverCurrentParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oOverCurrentResults, pXmlResults);
	}

	return pXmlParas;
}
