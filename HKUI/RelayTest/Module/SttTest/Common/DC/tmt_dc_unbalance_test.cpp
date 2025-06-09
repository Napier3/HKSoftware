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
	//2022.5.26 caoxc ������Ŀ����ID
	pXmlSierialize->xml_serialize("����1ͨ��ѡ��", "Current1Select", "", "long", pParas->m_nCurrent1Select);
	pXmlSierialize->xml_serialize("����2ͨ��ѡ��", "Current2Select", "", "long", pParas->m_nCurrent2Select);
	pXmlSierialize->xml_serialize("����", "Rate", "��", "number",pParas->m_fRate);
	pXmlSierialize->xml_serialize("����ʱ��ԣ��","FaultTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("����ǰʱ��","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("����ֵ","delt","A","float",pParas->m_fSettingValue);
	pXmlSierialize->xml_serialize("��������ʱ��","Tset","s","float",pParas->m_fSettingTime);
	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	pXmlSierialize->xml_serialize("������ת���Ʒ�ʽ", "_OutputSwitchMode", " ", "OutputSwitchMode", pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize("������ת��ʱ", "_OutputDelayTime", "s", "number", pParas->m_fBoutTimeTrig);
	pXmlSierialize->xml_serialize("��������ʱ��","_OutputKeepTime","s","number",pParas->m_fBoutHoldTime);


	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
}

void stt_xml_serialize_DcUnbalance_ex(tmt_DcUnbalanceParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_DcUnbalance(pParas,pXmlSierialize);
	pXmlSierialize->xml_serialize("������������(���ʽ)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ(���ʽ)", "MaxTSettingExp", "", "string", pParas->m_pszTSetting);
	pXmlSierialize->xml_serialize("����", "GroupID", "��", "string", pParas->m_pszGroupID);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_DcUnbalanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);
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