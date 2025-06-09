#include "stdafx.h"
#include "tmt_action_time_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_ActionTimeParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ActionTimeParas));
	pParas->init();
}

void stt_init_results(tmt_ActionTimeResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_ActionTimeResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_binary_out(tmt_ActionTimeParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
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
  pXmlSierialize->xml_serialize(/* "��̬����1״̬" */ g_sLangTxt_Native_NormalOpen1State.GetString(), "_Bout01", "",
                                "DOutputState", pParas->m_binOut[0][0].nState);
  pXmlSierialize->xml_serialize(/* "��̬����2״̬" */ g_sLangTxt_Native_NormalOpen2State.GetString(), "_Bout02", "",
                                "DOutputState", pParas->m_binOut[0][1].nState);
  pXmlSierialize->xml_serialize(/* "��̬����3״̬" */ g_sLangTxt_Native_NormalOpen3State.GetString(), "_Bout03", "",
                                "DOutputState", pParas->m_binOut[0][2].nState);
  pXmlSierialize->xml_serialize(/* "��̬����4״̬" */ g_sLangTxt_Native_NormalOpen4State.GetString(), "_Bout04", "",
                                "DOutputState", pParas->m_binOut[0][3].nState);
  pXmlSierialize->xml_serialize(/* "��̬����5״̬" */ g_sLangTxt_Native_NormalOpen5State.GetString(), "_Bout05", "",
                                "DOutputState", pParas->m_binOut[0][4].nState);
  pXmlSierialize->xml_serialize(/* "��̬����6״̬" */ g_sLangTxt_Native_NormalOpen6State.GetString(), "_Bout06", "",
                                "DOutputState", pParas->m_binOut[0][5].nState);
  pXmlSierialize->xml_serialize(/* "��̬����7״̬" */ g_sLangTxt_Native_NormalOpen7State.GetString(), "_Bout07", "",
                                "DOutputState", pParas->m_binOut[0][6].nState);
  pXmlSierialize->xml_serialize(/* "��̬����8״̬" */ g_sLangTxt_Native_NormalOpen8State.GetString(), "_Bout08", "",
                                "DOutputState", pParas->m_binOut[0][7].nState);

  pXmlSierialize->xml_serialize(/* "����̬����1״̬" */ g_sLangTxt_Native_FaultOpen1State.GetString(), "_Bout1", "",
                                "DOutputState", pParas->m_binOut[1][0].nState);
  pXmlSierialize->xml_serialize(/* "����̬����2״̬" */ g_sLangTxt_Native_FaultOpen2State.GetString(), "_Bout2", "",
                                "DOutputState", pParas->m_binOut[1][1].nState);
  pXmlSierialize->xml_serialize(/* "����̬����3״̬" */ g_sLangTxt_Native_FaultOpen3State.GetString(), "_Bout3", "",
                                "DOutputState", pParas->m_binOut[1][2].nState);
  pXmlSierialize->xml_serialize(/* "����̬����4״̬" */ g_sLangTxt_Native_FaultOpen4State.GetString(), "_Bout4", "",
                                "DOutputState", pParas->m_binOut[1][3].nState);
  pXmlSierialize->xml_serialize(/* "����̬����5״̬" */ g_sLangTxt_Native_FaultOpen5State.GetString(), "_Bout5", "",
                                "DOutputState", pParas->m_binOut[1][4].nState);
  pXmlSierialize->xml_serialize(/* "����̬����6״̬" */ g_sLangTxt_Native_FaultOpen6State.GetString(), "_Bout6", "",
                                "DOutputState", pParas->m_binOut[1][5].nState);
  pXmlSierialize->xml_serialize(/* "����̬����7״̬" */ g_sLangTxt_Native_FaultOpen7State.GetString(), "_Bout7", "",
                                "DOutputState", pParas->m_binOut[1][6].nState);
  pXmlSierialize->xml_serialize(/* "����̬����8״̬" */ g_sLangTxt_Native_FaultOpen8State.GetString(), "_Bout8", "",
                                "DOutputState", pParas->m_binOut[1][7].nState);
#endif
}

void stt_xml_serialize(tmt_ActionTimeParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ǰʱ��(��)","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("����ǰ��ѹ��ֵ","_UPre","V","number",pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize("����ǰ������ֵ","_IPre","A","number",pParas->m_fPreFaultCur);
	pXmlSierialize->xml_serialize("����ǰ��ѹ�������(U-I)", "PreAngle", "��", "number",  pParas->m_fPreFaultAngle);

	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ","SettingTime","s","number",pParas->m_fSettingFaultTime);
	pXmlSierialize->xml_serialize("����ʱ��ԣ��","FaultTime","s","number",pParas->m_fFaultTimeAdd);

	pXmlSierialize->xml_serialize("���ϵ�ѹ","FaultVolt","V","number",pParas->m_fFaultVol);
	pXmlSierialize->xml_serialize("���ϵ���","FaultCurrent","A","number",pParas->m_fFaultCur);
	pXmlSierialize->xml_serialize("����̬��ѹ�������(U-I)", "FaultAngle", "��", "number",  pParas->m_fFaultAngle);

	pXmlSierialize->xml_serialize("��������", "FaultType", "��", "SystemFault",  pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("��·��ѹ���", "FaultVolType", "��", "FaultVolType",  pParas->m_nFaultVolType);

	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
  pXmlSierialize->xml_serialize(/* "����ǰʱ��(��)" */ g_sLangTxt_Native_PreFaultTime.GetString(), "_PreFaultTime", "s", "number",
                                pParas->m_fPreFaultTime);
  pXmlSierialize->xml_serialize(/* "����ǰ��ѹ��ֵ" */ g_sLangTxt_Native_FaultPreVoltageAmp.GetString(), "_UPre", "V", "number",
                                pParas->m_fPreFaultVol);
  pXmlSierialize->xml_serialize(/* "����ǰ������ֵ" */ g_sLangTxt_Native_FaultPreCurrentAmp.GetString(), "_IPre", "A", "number",
                                pParas->m_fPreFaultCur);
  pXmlSierialize->xml_serialize(/* "����ǰ��ѹ�������(U-I)" */ g_sLangTxt_Native_FaultPreVoltageCurrentPhase.GetString(),
                                "PreAngle", "��", "number", pParas->m_fPreFaultAngle);

  pXmlSierialize->xml_serialize(/* "����ʱ�䶨ֵ" */ g_sLangTxt_Native_OpTimeSet.GetString(), "SettingTime", "s", "number",
                                pParas->m_fSettingFaultTime);
  pXmlSierialize->xml_serialize(/* "����ʱ��ԣ��" */ g_sLangTxt_Native_FaultTimeMargin.GetString(), "FaultTime", "s", "number",
                                pParas->m_fFaultTimeAdd);

  pXmlSierialize->xml_serialize(/* "���ϵ�ѹ" */ g_sLangTxt_Native_FaultVoltage.GetString(), "FaultVolt", "V", "number",
                                pParas->m_fFaultVol);
  pXmlSierialize->xml_serialize(/* "���ϵ���" */ g_sLangTxt_Native_FaultCurrValue.GetString(), "FaultCurrent", "A", "number",
                                pParas->m_fFaultCur);
  pXmlSierialize->xml_serialize(/* "����̬��ѹ�������(U-I)" */ g_sLangTxt_Native_FaultVoltageCurrentPhase.GetString(),
                                "FaultAngle", "��", "number", pParas->m_fFaultAngle);

  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "��", "SystemFault",
                                pParas->m_nFaultType);
  pXmlSierialize->xml_serialize(/* "��·��ѹ���" */ g_sLangTxt_Native_ShortCircuitVoltageType.GetString(), "FaultVolType", "��",
                                "FaultVolType", pParas->m_nFaultVolType);

  pXmlSierialize->xml_serialize(/* "�����߼�" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu",
                                pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
 	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize,nBinExNum);
 	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
 	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,nBoutExNum,FALSE);
 	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,nBoutExNum,TRUE);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_ActionTimeResults *pResults, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number",
                                pResults->m_fTripTime);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number",
                                pResults->m_nAct);
#endif
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_ActionTimeTest *pTests, CSttXmlSerializeBase *pXmlSerialize,long nBinExNum,long nBoutExNum)
{
	stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize(&(pTests->m_oActionTimeParas),  pXmlParas,nBinExNum,nBoutExNum);	//�ļ��Ķ�д
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oActionTimeResults,  pXmlResults,nBinExNum,nBoutExNum);
	}

	return pXmlParas;
}