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
	//����ֵ
	pXmlSierialize->xml_serialize("����I�ζ�ֵ","Uset","V","float",pParas->m_fSettingOverVol);

	pXmlSierialize->xml_serialize("����I��ʱ��","Tset","s","float",pParas->m_fSettingTime);
#else
	//����ֵ
	pXmlSierialize->xml_serialize(/* "����I�ζ�ֵ" */g_sLangTxt_Native_OverCurrentI.GetString(),"Uset","V","float",pParas->m_fSettingOverVol);

	pXmlSierialize->xml_serialize(/* "����I��ʱ��" */g_sLangTxt_Native_OverCurrentITime.GetString(),"Tset","s","float",pParas->m_fSettingTime);
#endif

}


void stt_xml_serialize_OverVoltage(tmt_OverVoltageParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����", "GroupID", "��", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize("��������", "FaultType", "��", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("��������ʱ��", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("����������ѹ", "USetting", "v", "set", pParas->m_fUSetting);
	pXmlSierialize->xml_serialize("��·����", "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("����", "Rate", "��", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("��·��ѹ", "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize("���Ϸ���", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("�������������ʱ��","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#else
	pXmlSierialize->xml_serialize(/* "����" */g_sLangTxt_Native_Grouping.GetString(), "GroupID", /* "��" */g_sLangTxt_None.GetString(), "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", /* "��" */g_sLangTxt_None.GetString(), "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "��������ʱ��" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("����������ѹ", "USetting", "v", "set", pParas->m_fUSetting);
	pXmlSierialize->xml_serialize(/* "��·����" */g_sLangTxt_Native_ShortCircuit.GetString(), "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "����" */g_sLangTxt_Native_Multiple.GetString(), "Rate", /* "��" */g_sLangTxt_None.GetString(), "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "��·��ѹ" */g_sLangTxt_Native_ShortCircuitV.GetString(), "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize(/* "���Ϸ���" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "�������������ʱ��" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serializeOverVoltageSetting(pParas,pXmlSierialize);
}

void stt_xml_serialize_OverVoltage_ex(tmt_OverVoltageParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_OverVoltage(pParas,pXmlSierialize);

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����������ѹ(���ʽ)", "FaultUfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ(���ʽ)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	pXmlSierialize->xml_serialize(/* "����������ѹ(���ʽ)" */g_sLangTxt_Native_ActionVoltExpr.GetString(), "FaultUfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "����ʱ�䶨ֵ(���ʽ)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_OverVoltageResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹֵ", "UGL", "V", "number", pResults->m_fDcVoltage);
#else
	pXmlSierialize->xml_serialize(/* "��ѹֵ" */g_sLangTxt_Native_OverVoltVal.GetString(), "UGL", "V", "number", pResults->m_fDcVoltage);
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
