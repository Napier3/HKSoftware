#include "stdafx.h"
#include "tmt_zero_current_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_ZeroCurrentParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ZeroCurrentParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_ZeroCurrentParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ZeroCurrentParasEx));
	pParas->init();
}

void stt_init_results(tmt_ZeroCurrentResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_ZeroCurrentResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_ZeroSetting(tmt_ZeroCurrentParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//整定值
	pXmlSierialize->xml_serialize("零序I段定值","I0set1","Ω","float",pParas->m_fSettingZeroCur[0]);
	pXmlSierialize->xml_serialize("零序II段定值","I0set2","Ω","float",pParas->m_fSettingZeroCur[1]);
	pXmlSierialize->xml_serialize("零序III段定值","I0set3","Ω","float",pParas->m_fSettingZeroCur[2]);
	pXmlSierialize->xml_serialize("零序IV段定值","I0set4","Ω","float",pParas->m_fSettingZeroCur[3]);
	pXmlSierialize->xml_serialize("零序V段定值","I0set5","Ω","float",pParas->m_fSettingZeroCur[4]);

	pXmlSierialize->xml_serialize("零序I段时间","Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize("零序II段时间","Tset2","s","float",pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize("零序III段时间","Tset3","s","float",pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize("零序IV段时间","Tset4","s","float",pParas->m_fSettingTime[3]);
	pXmlSierialize->xml_serialize("零序V段时间","Tset5","s","float",pParas->m_fSettingTime[4]);
#else
	//整定值
	pXmlSierialize->xml_serialize(/* "零序I段定值" */g_sLangTxt_Native_0SeqISet.GetString(),"I0set1","Ω","float",pParas->m_fSettingZeroCur[0]);
	pXmlSierialize->xml_serialize(/* "零序II段定值" */g_sLangTxt_Native_0SeqIISet.GetString(),"I0set2","Ω","float",pParas->m_fSettingZeroCur[1]);
	pXmlSierialize->xml_serialize(/* "零序III段定值" */g_sLangTxt_Native_0SeqIIISet.GetString(),"I0set3","Ω","float",pParas->m_fSettingZeroCur[2]);
	pXmlSierialize->xml_serialize(/* "零序IV段定值" */g_sLangTxt_Native_0SeqIVSet.GetString(),"I0set4","Ω","float",pParas->m_fSettingZeroCur[3]);
	pXmlSierialize->xml_serialize(/* "零序V段定值" */g_sLangTxt_Native_0SeqVSet.GetString(),"I0set5","Ω","float",pParas->m_fSettingZeroCur[4]);

	pXmlSierialize->xml_serialize(/* "零序I段时间" */g_sLangTxt_Native_0SeqITime.GetString(),"Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize(/* "零序II段时间" */g_sLangTxt_Native_0SeqIITime.GetString(),"Tset2","s","float",pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize(/* "零序III段时间" */g_sLangTxt_Native_0SeqIIITime.GetString(),"Tset3","s","float",pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize(/* "零序IV段时间" */g_sLangTxt_Native_0SeqIVTime.GetString(),"Tset4","s","float",pParas->m_fSettingTime[3]);
	pXmlSierialize->xml_serialize(/* "零序V段时间" */g_sLangTxt_Native_0SeqVTime.GetString(),"Tset5","s","float",pParas->m_fSettingTime[4]);
#endif

}

void stt_xml_serialize_ZeroCurrent(tmt_ZeroCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.26 caoxc 增加项目名称和分组
	pXmlSierialize->xml_serialize("项目名称", "TestName", "无", "string",  pParas->m_pszTestName);
	pXmlSierialize->xml_serialize("分组", "GroupID", "无", "string",  pParas->m_pszGroupID);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
	pXmlSierialize->xml_serialize("额定电压", "UNom", "V", "number",  pParas->m_fUnom);
	}

	pXmlSierialize->xml_serialize("故障类型", "FaultType", "无", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("整定动作电流", "ISetting", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("倍数", "Rate", "无", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("整定动作时间", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("短路阻抗", "Z", "Ω", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize("短路阻抗角", "ZPh", "°", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize("故障性质","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize("保护动作后持续时间","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serialize_ZeroSetting(pParas,pXmlSierialize);

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
	//2022.5.26 caoxc 增加项目名称和分组
	pXmlSierialize->xml_serialize(/* "项目名称" */g_sLangTxt_Native_ProjName.GetString(), "TestName", "无", "string",  pParas->m_pszTestName);
	pXmlSierialize->xml_serialize(/* "分组" */g_sLangTxt_Native_Grouping.GetString(), "GroupID", "无", "string",  pParas->m_pszGroupID);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
	pXmlSierialize->xml_serialize(/* "额定电压" */g_sLangTxt_Report_Vnom.GetString(), "UNom", "V", "number",  pParas->m_fUnom);
	}

	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "无", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "整定动作电流" */g_sLangTxt_Native_SetPickCurr.GetString(), "ISetting", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "倍数" */g_sLangTxt_Native_Multiple.GetString(), "Rate", "无", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "整定动作时间" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "故障方向" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "短路阻抗" */g_sLangTxt_Native_ShortZImp.GetString(), "Z", "Ω", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize(/* "短路阻抗角" */g_sLangTxt_Native_ShortZImpAng.GetString(), "ZPh", "°", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize(/* "故障性质" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serialize_ZeroSetting(pParas,pXmlSierialize);

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

}

void stt_xml_serialize_ZeroCurrent_ex(tmt_ZeroCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	stt_xml_serialize_ZeroCurrent(pParas,pXmlSierialize);
	pXmlSierialize->xml_serialize("整定动作电流(表达式)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	stt_xml_serialize_ZeroCurrent(pParas,pXmlSierialize);
	pXmlSierialize->xml_serialize(/* "整定动作电流(表达式)" */g_sLangTxt_Native_SetActCurExp.GetString(), "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "动作时间定值(表达式)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_StateZeroCurrent(tmt_ZeroCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.30 caoxc 增加项目名称和分组
	pXmlSierialize->xml_serialize("项目名称", "TestName", "无", "string",  pParas->m_pszTestName);
	pXmlSierialize->xml_serialize("分组", "GroupID", "无", "string",  pParas->m_pszGroupID);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize("是否自动测试模式", "IsAutoTest", "", "number",  pParas->m_nIsAutoTest);
	pXmlSierialize->xml_serialize("额定电压", "UNom", "V", "number",  pParas->m_fUnom);
	}

	pXmlSierialize->xml_serialize("故障类型", "FaultType", "无", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("整定动作时间", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("阻抗角", "ZAng", "°", "set", pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize("零序电流定值", "3I0", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("倍数", "Rate", "无", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("故障性质","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize("保护动作后持续时间","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#else
	//2022.5.30 caoxc 增加项目名称和分组
	pXmlSierialize->xml_serialize(/* "项目名称" */g_sLangTxt_Native_ProjName.GetString(), "TestName", "无", "string",  pParas->m_pszTestName);
	pXmlSierialize->xml_serialize(/* "分组" */g_sLangTxt_Native_Grouping.GetString(), "GroupID", "无", "string",  pParas->m_pszGroupID);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize(/* "是否自动测试模式" */g_sLangTxt_Native_YN_autoTestMode.GetString(), "IsAutoTest", "", "number",  pParas->m_nIsAutoTest);
	pXmlSierialize->xml_serialize(/* "额定电压" */g_sLangTxt_Report_Vnom.GetString(), "UNom", "V", "number",  pParas->m_fUnom);
	}

	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "无", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "整定动作时间" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "阻抗角" */g_sLangTxt_Native_ImpedanceAngles.GetString(), "ZAng", "°", "set", pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize(/* "零序电流定值" */g_sLangTxt_Native_0seqISet.GetString(), "3I0", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "倍数" */g_sLangTxt_Native_Multiple.GetString(), "Rate", "无", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "故障方向" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "故障性质" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serialize_ZeroSetting(pParas,pXmlSierialize);
}

void stt_xml_serialize_StateZeroCurrent_ex(tmt_ZeroCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	stt_xml_serialize_StateZeroCurrent(pParas,pXmlSierialize);
	pXmlSierialize->xml_serialize("整定动作电流(表达式)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	stt_xml_serialize_StateZeroCurrent(pParas,pXmlSierialize);
	pXmlSierialize->xml_serialize(/* "整定动作电流(表达式)" */g_sLangTxt_Native_SetActCurExp.GetString(), "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "动作时间定值(表达式)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_ZeroCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_ZeroCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ZeroCurrent) == 0)
		{
			stt_xml_serialize_ZeroCurrent_ex(&(pTests->m_oZeroCurrentParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_StateI0Current) == 0)
		{
			stt_xml_serialize_StateZeroCurrent_ex(&(pTests->m_oZeroCurrentParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oZeroCurrentResults, pXmlResults);
	}

	return pXmlParas;
}
