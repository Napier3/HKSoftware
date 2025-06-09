#include "stdafx.h"
#include "tmt_dc_unbalance_test.h"
#include"../../../SttCmd/SttTestCmd.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              
#endif
void stt_init_paras(tmt_DcUnbalanceParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DcUnbalanceParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_DcUnbalanceParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DcUnbalanceParasEx));
	pParas->init();
}

void stt_init_results(tmt_DcUnbalanceResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DcUnbalanceResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_DcUnbalance(tmt_DcUnbalanceParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.26 caoxc 增加项目分组ID
	pXmlSierialize->xml_serialize("电流1通道选择", "Current1Select", "", "long", pParas->m_nCurrent1Select);
	pXmlSierialize->xml_serialize("电流2通道选择", "Current2Select", "", "long", pParas->m_nCurrent2Select);
	pXmlSierialize->xml_serialize("倍数", "Rate", "无", "number",pParas->m_fRate);
	pXmlSierialize->xml_serialize("故障时间裕度","FaultTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("故障前时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("整定值","delt","A","float",pParas->m_fSettingValue);
	pXmlSierialize->xml_serialize("整定动作时间","Tset","s","float",pParas->m_fSettingTime);
	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	pXmlSierialize->xml_serialize("开出翻转控制方式", "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize("开出翻转延时", "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
	pXmlSierialize->xml_serialize("开出保持时间","_OutputKeepTime","s","number",pParas->m_fBoutHoldTime);


	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
}

void stt_xml_serialize_DcUnbalance_ex(tmt_DcUnbalanceParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_DcUnbalance(pParas,pXmlSierialize);
	pXmlSierialize->xml_serialize("整定动作电流(表达式)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "MaxTSettingExp", "", "string", pParas->m_pszTSetting);
	pXmlSierialize->xml_serialize("分组", "GroupID", "无", "string", pParas->m_pszGroupID);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_DcUnbalanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作时间", "TripTime", "", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "动作时间" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);
#endif

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DcUnbalanceTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCUnbalanceTest) == 0)
		{
			stt_xml_serialize_DcUnbalance_ex(&(pTests->m_oDcUnbalanceParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCUnbalanceTest) == 0)
		{
			stt_xml_serialize(&pTests->m_oDcUnbalanceResults, pXmlResults);
		}
	}

	return pXmlParas;
}

#include"../../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_DcUnbalanceTest()
{
	tmt_DcUnbalanceTest oDcUnbalanceTest;
	oDcUnbalanceTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeRegister(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize_DcUnbalance_ex(&oDcUnbalanceTest.m_oDcUnbalanceParas, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("DcUnbalanceTest.xml");

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}