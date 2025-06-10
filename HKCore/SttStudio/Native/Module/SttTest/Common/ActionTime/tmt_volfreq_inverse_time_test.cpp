#include "stdafx.h"
#include "tmt_volfreq_inverse_time_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_VFInverseTimeParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_VFInverseTimeParas));
	pParas->init();
}

void stt_init_results(tmt_VFInverseTimeResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_VFInverseTimeResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_binary_out(tmt_VFInverseTimeParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("常态开出1状态","_Bout01","","DOutputState",pParas->m_binOut[0][0].nState);
	pXmlSierialize->xml_serialize("常态开出2状态","_Bout02","","DOutputState",pParas->m_binOut[0][1].nState);
	pXmlSierialize->xml_serialize("常态开出3状态","_Bout03","","DOutputState",pParas->m_binOut[0][2].nState);
	pXmlSierialize->xml_serialize("常态开出4状态","_Bout04","","DOutputState",pParas->m_binOut[0][3].nState);
	pXmlSierialize->xml_serialize("常态开出5状态","_Bout05","","DOutputState",pParas->m_binOut[0][4].nState);
	pXmlSierialize->xml_serialize("常态开出6状态","_Bout06","","DOutputState",pParas->m_binOut[0][5].nState);
	pXmlSierialize->xml_serialize("常态开出7状态","_Bout07","","DOutputState",pParas->m_binOut[0][6].nState);
	pXmlSierialize->xml_serialize("常态开出8状态","_Bout08","","DOutputState",pParas->m_binOut[0][7].nState);

	pXmlSierialize->xml_serialize("故障态开出1状态","_Bout1","","DOutputState",pParas->m_binOut[1][0].nState);
	pXmlSierialize->xml_serialize("故障态开出2状态","_Bout2","","DOutputState",pParas->m_binOut[1][1].nState);
	pXmlSierialize->xml_serialize("故障态开出3状态","_Bout3","","DOutputState",pParas->m_binOut[1][2].nState);
	pXmlSierialize->xml_serialize("故障态开出4状态","_Bout4","","DOutputState",pParas->m_binOut[1][3].nState);
	pXmlSierialize->xml_serialize("故障态开出5状态","_Bout5","","DOutputState",pParas->m_binOut[1][4].nState);
	pXmlSierialize->xml_serialize("故障态开出6状态","_Bout6","","DOutputState",pParas->m_binOut[1][5].nState);
	pXmlSierialize->xml_serialize("故障态开出7状态","_Bout7","","DOutputState",pParas->m_binOut[1][6].nState);
	pXmlSierialize->xml_serialize("故障态开出8状态","_Bout8","","DOutputState",pParas->m_binOut[1][7].nState);
#else
  pXmlSierialize->xml_serialize(/* "常态开出1状态" */ g_sLangTxt_Native_NormalOpen1State.GetString(), "_Bout01", "",
                                "DOutputState", pParas->m_binOut[0][0].nState);
  pXmlSierialize->xml_serialize(/* "常态开出2状态" */ g_sLangTxt_Native_NormalOpen2State.GetString(), "_Bout02", "",
                                "DOutputState", pParas->m_binOut[0][1].nState);
  pXmlSierialize->xml_serialize(/* "常态开出3状态" */ g_sLangTxt_Native_NormalOpen3State.GetString(), "_Bout03", "",
                                "DOutputState", pParas->m_binOut[0][2].nState);
  pXmlSierialize->xml_serialize(/* "常态开出4状态" */ g_sLangTxt_Native_NormalOpen4State.GetString(), "_Bout04", "",
                                "DOutputState", pParas->m_binOut[0][3].nState);
  pXmlSierialize->xml_serialize(/* "常态开出5状态" */ g_sLangTxt_Native_NormalOpen5State.GetString(), "_Bout05", "",
                                "DOutputState", pParas->m_binOut[0][4].nState);
  pXmlSierialize->xml_serialize(/* "常态开出6状态" */ g_sLangTxt_Native_NormalOpen6State.GetString(), "_Bout06", "",
                                "DOutputState", pParas->m_binOut[0][5].nState);
  pXmlSierialize->xml_serialize(/* "常态开出7状态" */ g_sLangTxt_Native_NormalOpen7State.GetString(), "_Bout07", "",
                                "DOutputState", pParas->m_binOut[0][6].nState);
  pXmlSierialize->xml_serialize(/* "常态开出8状态" */ g_sLangTxt_Native_NormalOpen8State.GetString(), "_Bout08", "",
                                "DOutputState", pParas->m_binOut[0][7].nState);

  pXmlSierialize->xml_serialize(/* "故障态开出1状态" */ g_sLangTxt_Native_FaultOpen1State.GetString(), "_Bout1", "",
                                "DOutputState", pParas->m_binOut[1][0].nState);
  pXmlSierialize->xml_serialize(/* "故障态开出2状态" */ g_sLangTxt_Native_FaultOpen2State.GetString(), "_Bout2", "",
                                "DOutputState", pParas->m_binOut[1][1].nState);
  pXmlSierialize->xml_serialize(/* "故障态开出3状态" */ g_sLangTxt_Native_FaultOpen3State.GetString(), "_Bout3", "",
                                "DOutputState", pParas->m_binOut[1][2].nState);
  pXmlSierialize->xml_serialize(/* "故障态开出4状态" */ g_sLangTxt_Native_FaultOpen4State.GetString(), "_Bout4", "",
                                "DOutputState", pParas->m_binOut[1][3].nState);
  pXmlSierialize->xml_serialize(/* "故障态开出5状态" */ g_sLangTxt_Native_FaultOpen5State.GetString(), "_Bout5", "",
                                "DOutputState", pParas->m_binOut[1][4].nState);
  pXmlSierialize->xml_serialize(/* "故障态开出6状态" */ g_sLangTxt_Native_FaultOpen6State.GetString(), "_Bout6", "",
                                "DOutputState", pParas->m_binOut[1][5].nState);
  pXmlSierialize->xml_serialize(/* "故障态开出7状态" */ g_sLangTxt_Native_FaultOpen7State.GetString(), "_Bout7", "",
                                "DOutputState", pParas->m_binOut[1][6].nState);
  pXmlSierialize->xml_serialize(/* "故障态开出8状态" */ g_sLangTxt_Native_FaultOpen8State.GetString(), "_Bout8", "",
                                "DOutputState", pParas->m_binOut[1][7].nState);
#endif

}

void stt_xml_serialize(tmt_VFInverseTimeParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("故障前时间(秒)","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("变化方式 0-频率不变,增电压  1-电压不变,降频率", "GradMode", "", "GradMode",  pParas->m_nGradMode);
	pXmlSierialize->xml_serialize("整定动作时间", "SettingTime", "s", "number",  pParas->m_fSettingFaultTime);
	pXmlSierialize->xml_serialize("故障时间裕度", "FaultTime", "s", "number",  pParas->m_fFaultTimeMargin);

	pXmlSierialize->xml_serialize("电压频率比","VolFreqRate","","number",pParas->m_fKuf);
// 	pXmlSierialize->xml_serialize("额定电压","StdVol","V","number",pParas->m_fStdVol);
// 	pXmlSierialize->xml_serialize("额定频率", "StdFreq", "Hz", "number",  pParas->m_fStdFreq);


	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
  pXmlSierialize->xml_serialize(/* "故障前时间(秒)" */ g_sLangTxt_Native_PreFaultTime.GetString(), "_PreFaultTime", "s", "number",
                                pParas->m_fPreFaultTime);
  pXmlSierialize->xml_serialize(/* "变化方式 0-频率不变,增电压  1-电压不变,降频率" */ g_sLangTxt_Native_ChangeMode.GetString(),
                                "GradMode", "", "GradMode", pParas->m_nGradMode);
  pXmlSierialize->xml_serialize(/* "整定动作时间" */ g_sLangTxt_Adjustment_Time.GetString(), "SettingTime", "s", "number",
                                pParas->m_fSettingFaultTime);
  pXmlSierialize->xml_serialize(/* "故障时间裕度" */ g_sLangTxt_Native_FaultTimeMargin.GetString(), "FaultTime", "s", "number",
                                pParas->m_fFaultTimeMargin);

  pXmlSierialize->xml_serialize(/* "电压频率比" */ g_sLangTxt_Native_VoltFreqRatio.GetString(), "VolFreqRate", "", "number",
                                pParas->m_fKuf);
  // 	pXmlSierialize->xml_serialize("额定电压","StdVol","V","number",pParas->m_fStdVol);
  // 	pXmlSierialize->xml_serialize("额定频率", "StdFreq", "Hz", "number",  pParas->m_fStdFreq);

  pXmlSierialize->xml_serialize(/* "开入逻辑" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu",
                                pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
 	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void stt_xml_serialize(tmt_VFInverseTimeResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作时间", "TripTime", "", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
  pXmlSierialize->xml_serialize(/* "动作时间" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number",
                                pResults->m_fTripTime);
  pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number",
                                pResults->m_nAct);
#endif
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_VFInverseTimeTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	//stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize(&(pTests->m_oVolInverseParas),  pXmlParas);	//文件的读写
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oVolInverseResults,  pXmlResults);
	}

	return pXmlParas;
}
