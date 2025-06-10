#include "stdafx.h"
#include "tmt_over_voltage_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_OverVoltageParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_OverVoltageParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_OverVoltageParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_OverVoltageParasEx));
	pParas->init();
}

void stt_init_results(tmt_OverVoltageResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_OverVoltageResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serializeOverVoltageSetting(tmt_OverVoltageParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//整定值
	pXmlSierialize->xml_serialize("过流I段定值","Uset","V","float",pParas->m_fSettingOverVol);

	pXmlSierialize->xml_serialize("过流I段时间","Tset","s","float",pParas->m_fSettingTime);
#else
	//整定值
	pXmlSierialize->xml_serialize(/* "过流I段定值" */g_sLangTxt_Native_OverCurrentI.GetString(),"Uset","V","float",pParas->m_fSettingOverVol);

	pXmlSierialize->xml_serialize(/* "过流I段时间" */g_sLangTxt_Native_OverCurrentITime.GetString(),"Tset","s","float",pParas->m_fSettingTime);
#endif

}


void stt_xml_serialize_OverVoltage(tmt_OverVoltageParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("分组", "GroupID", "无", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize("故障类型", "FaultType", "无", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("整定动作时间", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("整定动作电压", "USetting", "v", "set", pParas->m_fUSetting);
	pXmlSierialize->xml_serialize("短路电流", "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("倍数", "Rate", "无", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("短路电压", "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("保护动作后持续时间","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#else
	pXmlSierialize->xml_serialize(/* "分组" */g_sLangTxt_Native_Grouping.GetString(), "GroupID", /* "无" */g_sLangTxt_None.GetString(), "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", /* "无" */g_sLangTxt_None.GetString(), "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "整定动作时间" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("整定动作电压", "USetting", "v", "set", pParas->m_fUSetting);
	pXmlSierialize->xml_serialize(/* "短路电流" */g_sLangTxt_Native_ShortCircuit.GetString(), "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "倍数" */g_sLangTxt_Native_Multiple.GetString(), "Rate", /* "无" */g_sLangTxt_None.GetString(), "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "短路电压" */g_sLangTxt_Native_ShortCircuitV.GetString(), "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize(/* "故障方向" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serializeOverVoltageSetting(pParas,pXmlSierialize);
}

void stt_xml_serialize_OverVoltage_ex(tmt_OverVoltageParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_OverVoltage(pParas,pXmlSierialize);

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("整定动作电压(表达式)", "FaultUfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	pXmlSierialize->xml_serialize(/* "整定动作电压(表达式)" */g_sLangTxt_Native_ActionVoltExpr.GetString(), "FaultUfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "动作时间定值(表达式)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_OverVoltageResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("过压值", "UGL", "V", "number", pResults->m_fDcVoltage);
#else
	pXmlSierialize->xml_serialize(/* "过压值" */g_sLangTxt_Native_OverVoltVal.GetString(), "UGL", "V", "number", pResults->m_fDcVoltage);
#endif

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_OverVoltageTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize_OverVoltage_ex(&(pTests->m_oOverVoltageParas), pXmlParas);
		
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oOverVoltageResults, pXmlResults);
	}

	return pXmlParas;
}
