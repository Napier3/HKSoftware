#include "stdafx.h"
#include "tmt_dc_break_test.h"
#include"../../../SttCmd/SttTestCmd.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif
void stt_init_paras(tmt_DcBreakParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DcBreakParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_DcBreakParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DcBreakParasEx));
	pParas->init();
}

void stt_init_results(tmt_DcBreakResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DcBreakResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serializeDcBreakSetting(tmt_DcBreakParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
	//整定值
	pXmlSierialize->xml_serialize("开关I段定值","Iset1","A","float",pParas->m_fSettingBreak[0]);
	pXmlSierialize->xml_serialize("开关II段定值","Iset2","A","float",pParas->m_fSettingBreak[1]);

	pXmlSierialize->xml_serialize("开关I段时间","Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize("开关II段时间","Tset2","s","float",pParas->m_fSettingTime[1]);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_DcBreak(tmt_DcBreakParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.26 caoxc 增加项目分组ID
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("故障通道", "FaultVarIndex", "", "UIRampChannel", pParas->m_nFaultChannel);
	pXmlSierialize->xml_serialize("整定动作电流", "FaultIf", "A", "number", pParas->m_fISetting);
	pXmlSierialize->xml_serialize("倍数", "Rate", "无", "number",pParas->m_fRate);
	pXmlSierialize->xml_serialize("最大故障时间", "TSetting", "s","number",pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("故障时间裕度","FaultTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("故障前时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("保护动作后持续时间","PostFaultTime","s","number",pParas->m_fPostFaultTime);
	pXmlSierialize->xml_serialize("故障触发方式","FaultTrigMode","","FaultTrigModePnv",pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize("是否模拟断路器延时","SimulateBreakerDelay","s","number",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("断路器跳闸延时","BrkBreakTime","s","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("断路器合闸延时","BrkCloseTime","s","number",pParas->m_fCBCloseTime);
	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
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
#else
	pXmlSierialize->xml_serialize(/* "故障通道" */ g_sLangTxt_Native_FaultChnl.GetString(), "FaultVarIndex", "", "UIRampChannel", pParas->m_nFaultChannel);
	pXmlSierialize->xml_serialize(/* "整定动作电流" */ g_sLangTxt_Native_SetPickCurr.GetString(), "FaultIf", "A", "number", pParas->m_fISetting);
	pXmlSierialize->xml_serialize(/* "倍数" */ g_sLangTxt_Native_Multiple.GetString(), "Rate", "无", "number", pParas->m_fRate);
	pXmlSierialize->xml_serialize(/* "最大故障时间" */ g_sLangTxt_Native_MaxTimeMalf.GetString(), "TSetting", "s", "number", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "故障时间裕度" */ g_sLangTxt_Native_FaultTimeMargin.GetString(), "FaultTime", "s", "number", pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize(/* "故障前时间" */ g_sLangTxt_Native_PreFautTime.GetString(), "PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */ g_sLangTxt_Native_DurProtTrip.GetString(), "PostFaultTime", "s", "number", pParas->m_fPostFaultTime);
	pXmlSierialize->xml_serialize(/* "故障触发方式" */ g_sLangTxt_Native_FaultTrigMethod.GetString(), "FaultTrigMode", "", "FaultTrigModePnv", pParas->m_nFaultTrigMode);
	pXmlSierialize->xml_serialize(/* "是否模拟断路器延时" */ g_sLangTxt_Native_SimBrkDel.GetString(), "SimulateBreakerDelay", "s", "number", pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize(/* "断路器跳闸延时" */ g_sLangTxt_Native_BrkTripDel.GetString(), "BrkBreakTime", "s", "number", pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize(/* "断路器合闸延时" */ g_sLangTxt_Native_BrkClsDel.GetString(), "BrkCloseTime", "s", "number", pParas->m_fCBCloseTime);
	pXmlSierialize->xml_serialize(/* "开入逻辑" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
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
#endif
	stt_xml_serializeDcBreakSetting(pParas,pXmlSierialize);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	
}

void stt_xml_serialize_DcBreak_ex(tmt_DcBreakParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_DcBreak(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("整定动作电流(表达式)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "MaxTSettingExp", "", "string", pParas->m_pszTSetting);
	pXmlSierialize->xml_serialize("分组", "GroupID", "无", "string", pParas->m_pszGroupID);
#else
	pXmlSierialize->xml_serialize("整定动作电流(表达式)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "MaxTSettingExp", "", "string", pParas->m_pszTSetting);
	pXmlSierialize->xml_serialize("分组", "GroupID", "无", "string", pParas->m_pszGroupID);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_DcBreakResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
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

#else
	pXmlSierialize->xml_serialize(/* "A相动作时间" */ g_sLangTxt_Native_PhaseATime.GetString(), "TtripA", "s", "number", pResults->m_fFirstTripTime[0]);
	pXmlSierialize->xml_serialize(/* "B相动作时间" */ g_sLangTxt_Native_PhaseBTime.GetString(), "TtripB", "s", "number", pResults->m_fFirstTripTime[1]);
	pXmlSierialize->xml_serialize(/* "C相动作时间" */ g_sLangTxt_Native_PhaseCTime.GetString(), "TtripC", "s", "number", pResults->m_fFirstTripTime[2]);
	pXmlSierialize->xml_serialize(/* "重合闸动作时间" */ g_sLangTxt_Native_RecloseTime.GetString(), "TtripD", "s", "number", pResults->m_fRecloseTime);
	pXmlSierialize->xml_serialize(/* "开入E动作时间" */ g_sLangTxt_Native_InputETime.GetString(), "TtripE", "s", "number", pResults->m_fFirstTripTime[4]);
	pXmlSierialize->xml_serialize(/* "开入F动作时间" */ g_sLangTxt_Native_InputFTime.GetString(), "TtripF", "s", "number", pResults->m_fFirstTripTime[5]);
	pXmlSierialize->xml_serialize(/* "开入G动作时间" */ g_sLangTxt_Native_InputGTime.GetString(), "TtripG", "s", "number", pResults->m_fFirstTripTime[6]);
	pXmlSierialize->xml_serialize(/* "开入H动作时间" */ g_sLangTxt_Native_InputHTime.GetString(), "TtripH", "s", "number", pResults->m_fFirstTripTime[7]);
	pXmlSierialize->xml_serialize(/* "动作时间" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);

	pXmlSierialize->xml_serialize(/* "开入A动作描述" */ g_sLangTxt_Native_InputADesc.GetString(), "ActA", "", "number", pResults->m_nActA);
	pXmlSierialize->xml_serialize(/* "开入B动作描述" */ g_sLangTxt_Native_InputBDesc.GetString(), "ActB", "", "number", pResults->m_nActB);
	pXmlSierialize->xml_serialize(/* "开入C动作描述" */ g_sLangTxt_Native_InputCDesc.GetString(), "ActC", "", "number", pResults->m_nActC);
	pXmlSierialize->xml_serialize(/* "重合闸动作描述" */ g_sLangTxt_Native_ReclActDesc.GetString(), "ActD", "", "number", pResults->m_nActD);
	pXmlSierialize->xml_serialize(/* "后加速动作时间" */ g_sLangTxt_Native_PostAccTime.GetString(), "TtripAcc", "s", "number", pResults->m_fSecondTripTime);
	pXmlSierialize->xml_serialize(/* "后加速动作描述" */ g_sLangTxt_Native_PostAccDesc.GetString(), "ActAcc", "", "number", pResults->m_nActAcc);

#endif
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DcBreakTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCBreakTest) == 0)
		{
			stt_xml_serialize_DcBreak_ex(&(pTests->m_oDcBreakParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCBreakTest) == 0)
		{
			stt_xml_serialize(&pTests->m_oDcBreakResults, pXmlResults);
		}
	}

	return pXmlParas;
}

#include"../../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_DcBreakTest()
{
	tmt_DcBreakTest oDcBreakTest;
	oDcBreakTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeRegister(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize_DcBreak_ex(&oDcBreakTest.m_oDcBreakParas, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("DcBreakTestDemo.xml");
	//  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}