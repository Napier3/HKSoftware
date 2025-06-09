#include "stdafx.h"
#include "tmt_dc_overcurrent_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_DCOverCurrentParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DCOverCurrentParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_DCOverCurrentParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DCOverCurrentParasEx));
	pParas->init();
}

void stt_init_results(tmt_DCOverCurrentResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DCOverCurrentResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serializeDCOverCurrentSetting(tmt_DCOverCurrentParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
	//整定值
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("整定方式","SetMethod","无","number",pParas->m_nSettingMethod);
	pXmlSierialize->xml_serialize("一次额定电流","Iset","A","number",pParas->m_fRatePrimaryCurr);
	pXmlSierialize->xml_serialize("过流I段定值","Iset1","Ω","float",pParas->m_fSettingDCOverCur[0]);
	pXmlSierialize->xml_serialize("过流II段定值","Iset2","Ω","float",pParas->m_fSettingDCOverCur[1]);
	pXmlSierialize->xml_serialize("过流III段定值","Iset3","Ω","float",pParas->m_fSettingDCOverCur[2]);
	pXmlSierialize->xml_serialize("过流IV段定值","Iset4","Ω","float",pParas->m_fSettingDCOverCur[3]);

	pXmlSierialize->xml_serialize("过流I段时间","Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize("过流II段时间","Tset2","s","float",pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize("过流III段时间","Tset3","s","float",pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize("过流IV段时间","Tset4","s","float",pParas->m_fSettingTime[3]);
#else
	pXmlSierialize->xml_serialize(/* "过流I段定值" */ g_sLangTxt_Native_OverCurrentI.GetString(), "Iset1", "Ω", "float", pParas->m_fSettingDCOverCur[0]);
	pXmlSierialize->xml_serialize(/* "过流II段定值" */ g_sLangTxt_Native_OverCurrentII.GetString(), "Iset2", "Ω", "float", pParas->m_fSettingDCOverCur[1]);
	pXmlSierialize->xml_serialize(/* "过流III段定值" */ g_sLangTxt_Native_OverCurrentIII.GetString(), "Iset3", "Ω", "float", pParas->m_fSettingDCOverCur[2]);
	pXmlSierialize->xml_serialize(/* "过流IV段定值" */ g_sLangTxt_Native_OverCurrentIV.GetString(), "Iset4", "Ω", "float", pParas->m_fSettingDCOverCur[3]);

	pXmlSierialize->xml_serialize(/* "过流I段时间" */ g_sLangTxt_Native_OverCurrentITime.GetString(), "Tset1", "s", "float", pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize(/* "过流II段时间" */ g_sLangTxt_Native_OverCurrentIITime.GetString(), "Tset2", "s", "float", pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize(/* "过流III段时间" */ g_sLangTxt_Native_OverCurrentIIITime.GetString(), "Tset3", "s", "float", pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize(/* "过流IV段时间" */ g_sLangTxt_Native_OverCurrentIVTime.GetString(), "Tset4", "s", "float", pParas->m_fSettingTime[3]);
#endif
}


void stt_xml_serialize_DCOverCurrent(tmt_DCOverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("分组", "GroupID", "无", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize("故障通道", "FaultChannel", "无", "UIRampChannel",  pParas->m_nFaultChannel);
	pXmlSierialize->xml_serialize("整定动作电流", "FaultIf", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("倍数", "Rate", "无", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("最大故障时间", "TSet1", "s","number",pParas->m_fMaxFaultTime);
	pXmlSierialize->xml_serialize("整定动作时间", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("电压", "Voltage", "kV", "number", pParas->m_fVoltage);
	pXmlSierialize->xml_serialize("一次额定电压","PreFaultVol","kV","number",pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize("故障前电流","PreFaultCur","A","number",pParas->m_fPreFaultCur);

	pXmlSierialize->xml_serialize("短路阻抗", "Z", "Ω", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize("短路阻抗角", "ZPh", "°", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize("保护动作后持续时间","PostFaultTime","s","number",pParas->m_fAfterTriggerFaultTime);
//     pXmlSierialize->xml_serialize("故障时间裕度","FaultTime","s","number",pParas->m_fFaultTime);//20240617 suyang采用基类的参数，下发两次ID一样的参数 
    pXmlSierialize->xml_serialize("开入逻辑","_OutputSwitchMode","s","number",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/* "分组" */ g_sLangTxt_Native_Grouping.GetString(), "GroupID", /*  "无" */ g_sLangTxt_None.GetString(), "string",pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize(/* "故障通道" */ g_sLangTxt_Native_FaultChnl.GetString(), "FaultChannel", /*  "无" */ g_sLangTxt_None.GetString(),"UIRampChannel", pParas->m_nFaultChannel);
	pXmlSierialize->xml_serialize(/* "整定动作电流" */ g_sLangTxt_Native_SetPickCurr.GetString(), "FaultIf", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "倍数" */ g_sLangTxt_Native_Multiple.GetString(), "Rate", /*  "无" */ g_sLangTxt_None.GetString(), "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "最大故障时间" */ g_sLangTxt_Native_MaxTimeMalf.GetString(), "TSet1", "s", "number", pParas->m_fMaxFaultTime);
	pXmlSierialize->xml_serialize(/* "整定动作时间" */ g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "电压" */ g_sLangTxt_Native_Voltage.GetString(), "Voltage", "V", "number", pParas->m_fVoltage);
	pXmlSierialize->xml_serialize(/* "故障前电压" */ g_sLangTxt_Native_PreFaultVolt.GetString(), "PreFaultVol", "V", "number", pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize(/* "故障前电流" */ g_sLangTxt_Native_PreFaultCurr.GetString(), "PreFaultCur", "A", "number", pParas->m_fPreFaultCur);

	pXmlSierialize->xml_serialize(/* "短路阻抗" */ g_sLangTxt_Native_ShortZImp.GetString(), "Z", "Ω", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize(/* "短路阻抗角" */ g_sLangTxt_Native_ShortZImpAng.GetString(), "ZPh", "°", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */ g_sLangTxt_Native_DurProtTrip.GetString(), "PostFaultTime", "s", "number",pParas->m_fAfterTriggerFaultTime);
#endif

	if(stt_xml_serialize_is_write(pXmlSierialize))//下发
	{
		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			pParas->m_nDInputState[i] = pParas->m_binIn[i].nSelect;
			pParas->m_nStateBOut[i] = pParas->m_binOut[0][i].nState;
		}
	}

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serializeDCOverCurrentSetting(pParas,pXmlSierialize);
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			pParas->m_binIn[i].nSelect = pParas->m_nDInputState[i];
			pParas->m_binOut[0][i].nState = pParas->m_nStateBOut[i];
		}
	}
}

void stt_xml_serialize_DCOverCurrent_ex(tmt_DCOverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_DCOverCurrent(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("整定动作电流(表达式)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
    pXmlSierialize->xml_serialize(/* "整定动作电流(表达式)" */ g_sLangTxt_Native_SetActCurExp.GetString(), "FaultIfExp", "", "string", pParas->m_pszSetting);
    pXmlSierialize->xml_serialize(/* "动作时间定值(表达式)" */ g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string",pParas->m_pszTSetting);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_DCOverCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("过流值", "IGL", "A", "number", pResults->m_fOverCurrent);
#else
    pXmlSierialize->xml_serialize(/* "过流值" */ g_sLangTxt_Native_OverCurrentValue.GetString(), "IGL", "A", "number", pResults->m_fOverCurrent);
#endif
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DCOverCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_DCOverCurrentTest) == 0)
		{
			stt_xml_serialize_DCOverCurrent_ex(&(pTests->m_oDCOverCurrentParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oDCOverCurrentResults, pXmlResults);
	}

	return pXmlParas;
}
