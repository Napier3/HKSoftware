#include "stdafx.h"
#include "tmt_overload_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_OverLoadParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_OverLoadParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_OverLoadParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_OverLoadParasEx));
	pParas->init();
}

void stt_init_results(tmt_OverLoadTestResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_OverLoadTestResults));
	pResults->init();
}

void stt_xml_serialize_binary_out(tmt_OverLoadParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��̬����1״̬","_Bout01","","DOutputState",pParas->m_binOut[0][0].nState);
	pXmlSierialize->xml_serialize("��̬����2״̬","_Bout02","","DOutputState",pParas->m_binOut[0][1].nState);
	pXmlSierialize->xml_serialize("��̬����3״̬","_Bout03","","DOutputState",pParas->m_binOut[0][2].nState);
	pXmlSierialize->xml_serialize("��̬����4״̬","_Bout04","","DOutputState",pParas->m_binOut[0][3].nState);
	pXmlSierialize->xml_serialize("��̬����5״̬","_Bout05","","DOutputState",pParas->m_binOut[0][4].nState);
	pXmlSierialize->xml_serialize("��̬����6״̬","_Bout06","","DOutputState",pParas->m_binOut[0][5].nState);
	pXmlSierialize->xml_serialize("��̬����7״̬","_Bout07","","DOutputState",pParas->m_binOut[0][6].nState);
	pXmlSierialize->xml_serialize("��̬����8״̬","_Bout08","","DOutputState",pParas->m_binOut[0][7].nState);

	pXmlSierialize->xml_serialize("����̬����1״̬","_Bout1","","DOutputState",pParas->m_binOut[1][0].nState);
	pXmlSierialize->xml_serialize("����̬����2״̬","_Bout2","","DOutputState",pParas->m_binOut[1][1].nState);
	pXmlSierialize->xml_serialize("����̬����3״̬","_Bout3","","DOutputState",pParas->m_binOut[1][2].nState);
	pXmlSierialize->xml_serialize("����̬����4״̬","_Bout4","","DOutputState",pParas->m_binOut[1][3].nState);
	pXmlSierialize->xml_serialize("����̬����5״̬","_Bout5","","DOutputState",pParas->m_binOut[1][4].nState);
	pXmlSierialize->xml_serialize("����̬����6״̬","_Bout6","","DOutputState",pParas->m_binOut[1][5].nState);
	pXmlSierialize->xml_serialize("����̬����7״̬","_Bout7","","DOutputState",pParas->m_binOut[1][6].nState);
	pXmlSierialize->xml_serialize("����̬����8״̬","_Bout8","","DOutputState",pParas->m_binOut[1][7].nState);
#else
	pXmlSierialize->xml_serialize(/* "��̬����1״̬" */ g_sLangTxt_Native_NormalOpen1State.GetString(), "_Bout01", "", "DOutputState", pParas->m_binOut[0][0].nState);
	pXmlSierialize->xml_serialize(/* "��̬����2״̬" */ g_sLangTxt_Native_NormalOpen2State.GetString(), "_Bout02", "", "DOutputState", pParas->m_binOut[0][1].nState);
	pXmlSierialize->xml_serialize(/* "��̬����3״̬" */ g_sLangTxt_Native_NormalOpen3State.GetString(), "_Bout03", "", "DOutputState", pParas->m_binOut[0][2].nState);
	pXmlSierialize->xml_serialize(/* "��̬����4״̬" */ g_sLangTxt_Native_NormalOpen4State.GetString(), "_Bout04", "", "DOutputState", pParas->m_binOut[0][3].nState);
	pXmlSierialize->xml_serialize(/* "��̬����5״̬" */ g_sLangTxt_Native_NormalOpen5State.GetString(), "_Bout05", "", "DOutputState", pParas->m_binOut[0][4].nState);
	pXmlSierialize->xml_serialize(/* "��̬����6״̬" */ g_sLangTxt_Native_NormalOpen6State.GetString(), "_Bout06", "", "DOutputState", pParas->m_binOut[0][5].nState);
	pXmlSierialize->xml_serialize(/* "��̬����7״̬" */ g_sLangTxt_Native_NormalOpen7State.GetString(), "_Bout07", "", "DOutputState", pParas->m_binOut[0][6].nState);
	pXmlSierialize->xml_serialize(/* "��̬����8״̬" */ g_sLangTxt_Native_NormalOpen8State.GetString(), "_Bout08", "", "DOutputState", pParas->m_binOut[0][7].nState);

	pXmlSierialize->xml_serialize(/* "����̬����1״̬" */ g_sLangTxt_Native_FaultOpen1State.GetString(), "_Bout1", "", "DOutputState", pParas->m_binOut[1][0].nState);
	pXmlSierialize->xml_serialize(/* "����̬����2״̬" */ g_sLangTxt_Native_FaultOpen2State.GetString(), "_Bout2", "", "DOutputState", pParas->m_binOut[1][1].nState);
	pXmlSierialize->xml_serialize(/* "����̬����3״̬" */ g_sLangTxt_Native_FaultOpen3State.GetString(), "_Bout3", "", "DOutputState", pParas->m_binOut[1][2].nState);
	pXmlSierialize->xml_serialize(/* "����̬����4״̬" */ g_sLangTxt_Native_FaultOpen4State.GetString(), "_Bout4", "", "DOutputState", pParas->m_binOut[1][3].nState);
	pXmlSierialize->xml_serialize(/* "����̬����5״̬" */ g_sLangTxt_Native_FaultOpen5State.GetString(), "_Bout5", "", "DOutputState", pParas->m_binOut[1][4].nState);
	pXmlSierialize->xml_serialize(/* "����̬����6״̬" */ g_sLangTxt_Native_FaultOpen6State.GetString(), "_Bout6", "", "DOutputState", pParas->m_binOut[1][5].nState);
	pXmlSierialize->xml_serialize(/* "����̬����7״̬" */ g_sLangTxt_Native_FaultOpen7State.GetString(), "_Bout7", "", "DOutputState", pParas->m_binOut[1][6].nState);
	pXmlSierialize->xml_serialize(/* "����̬����8״̬" */ g_sLangTxt_Native_FaultOpen8State.GetString(), "_Bout8", "", "DOutputState", pParas->m_binOut[1][7].nState);
#endif
}

void stt_xml_serialize(tmt_OverLoadParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��Ŀ����","TestName","","string",pParas->m_pszTestName);
	pXmlSierialize->xml_serialize("�ȹ�����ʱ�䳣��","_Time","","number",pParas->m_fTime);
	pXmlSierialize->xml_serialize("�ȹ����ɻ�������","BaseCur","A","number",pParas->m_fBaseCur);
	pXmlSierialize->xml_serialize("�ȹ����ɶ�����ֵ","BaseActionSet","","number",pParas->m_fBaseActionSet);
	pXmlSierialize->xml_serialize("�����ɵ���ͨ��", "FaultCurChannel", "��", "UIRampChannel",  pParas->m_nFaultCurChannel);
	pXmlSierialize->xml_serialize("�����ɵ���","FaultCur","A","number",pParas->m_fFaultCur);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ","SettingTime","s","number",pParas->m_fFaultSettingTime);
	pXmlSierialize->xml_serialize("��̬ʱ��","Normaltime","s","number",pParas->m_fNormaltime);
	pXmlSierialize->xml_serialize("����ʱ��ԣ��","FaultMarginTime","s","number",pParas->m_fFaultMarginTime);
	pXmlSierialize->xml_serialize("����ǰ��ѹ","PreFaultVol","V","number",pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize("����ǰ����","PreFaultCur","A","number",pParas->m_fPreFaultCur);
	pXmlSierialize->xml_serialize("�����仯ʼֵ", "fStartCur", "", "number",  pParas->m_fStartCur);
	pXmlSierialize->xml_serialize("�����仯��ֵ", "EndCur", "", "number",  pParas->m_fEndCur);
	pXmlSierialize->xml_serialize("�����仯����", "StepCur", "", "number",  pParas->m_fStepCur);


	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
  
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,TRUE);
}

void stt_xml_serialize_ex(tmt_OverLoadParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�ȹ�����ʱ�䳣��(���ʽ)", "SettingTimeCoefExp", "", "string",  pParas->m_pszTimeCoef);
	pXmlSierialize->xml_serialize("�ȹ����ɻ�������(���ʽ)","BaseCurExp","","string",pParas->m_pszCur);
	pXmlSierialize->xml_serialize("�ȹ����ɶ�����ֵ(���ʽ)","ActionSetExp","","string",pParas->m_pszActionSet);
#else
  pXmlSierialize->xml_serialize(/* "�ȹ�����ʱ�䳣��(���ʽ)" */ g_sLangTxt_Native_HotOverloadTime.GetString(), "SettingTimeCoefExp", "", "string", pParas->m_pszTimeCoef);
  pXmlSierialize->xml_serialize(/* "�ȹ����ɻ�������(���ʽ)" */ g_sLangTxt_Native_HotOverloadBaseCurr.GetString(), "BaseCurExp", "", "string", pParas->m_pszCur);
  pXmlSierialize->xml_serialize(/* "�ȹ����ɶ�����ֵ(���ʽ)" */ g_sLangTxt_Native_HotOverloadActionValues.GetString(), "ActionSetExp", "", "string", pParas->m_pszActionSet);
#endif
	stt_xml_serialize(pParas,pXmlSierialize);
}

void stt_xml_serialize(tmt_OverLoadTestResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);
#endif
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_OverLoadTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize_ex(&(pTests->m_oOverLoadParas),  pXmlParas);	//�ļ��Ķ�д
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oOverLoadTestResults,  pXmlResults);
	}
	return pXmlParas;
}
