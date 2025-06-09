#include "stdafx.h"
#include "tmt_vol_act_value_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_VolActValueParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_VolActValueParas));
	pParas->init();
}

void stt_init_results(tmt_VolActValueResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_VolActValueResults));
	pResults->init();
}
void stt_init_paras(tmt_VolActValuePnvParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_VolActValuePnvParas));
    pParas->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_VolActValueParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize("���Ծ���", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("����ʱ��(��)", "FaultTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize("��������", "VarIndex", "", "SystemFault", pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("�����迹��","ZLAng_Fault","","number",pParas->m_fImpAngle);
	pXmlSierialize->xml_serialize("��·����","FaultCurrent","","number",pParas->m_fFaultCurrent);
#else
  pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
  pXmlSierialize->xml_serialize(/* "�仯��ֵ" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop);
  pXmlSierialize->xml_serialize(/* "���Ծ���" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "����ʱ��(��)" */ g_sLangTxt_Native_StepTimeSec.GetString(), "FaultTime", "s", "set", pParas->m_fStepTime);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Gradient_FailType.GetString(), "VarIndex", "", "SystemFault", pParas->m_nFaultType);
  pXmlSierialize->xml_serialize(/* "�����迹��" */ g_sLangTxt_Native_FaultImpedanceAngle.GetString(), "ZLAng_Fault", "", "number", pParas->m_fImpAngle);
  pXmlSierialize->xml_serialize(/* "��·����" */ g_sLangTxt_Native_ShortCircuit.GetString(), "FaultCurrent", "", "number", pParas->m_fFaultCurrent);
#endif
	stt_xml_serialize_common(pParas,pXmlSierialize);

}

void stt_xml_serialize(tmt_VolActValuePnvParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop );
    pXmlSierialize->xml_serialize("���Ծ���", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("��������ʱ��", "TSetting", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��","RampResetTime","s","number",pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("����ǰ����ʱ��","FaultResetTime","s","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("ÿ��ʱ��ԣ��","StepTimeAdded","s","number",pParas->m_fMarginTime);
    pXmlSierialize->xml_serialize("�������", "VarIndex", "", "URampIndex", pParas->m_nFaultType);
    pXmlSierialize->xml_serialize("��ѹ����ֵ","UabcResetValue","V","number",pParas->m_fG1Volt);
    pXmlSierialize->xml_serialize("����Ia","Ia","A","set",pParas->m_uiCUR[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ib","Ib","A","set",pParas->m_uiCUR[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("����Ic","Ic","A","set",pParas->m_uiCUR[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia��λ","IaPh","��","number",pParas->m_uiCUR[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib��λ","IbPh","��","number",pParas->m_uiCUR[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic��λ","IcPh","��","number",pParas->m_uiCUR[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua��λ","UaPh","��","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub��λ","UbPh","��","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc��λ","UcPh","��","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uz��λ","UzPh","��","number",pParas->m_uiVOL[0][3].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic",pParas->m_nBinLogic);

    pXmlSierialize->xml_serialize("����Aѡ��", "_BinSelectA", "", "BOOL", pParas->m_binIn[0].nSelect);
    pXmlSierialize->xml_serialize("����Bѡ��", "_BinSelectB", "", "BOOL", pParas->m_binIn[1].nSelect);
    pXmlSierialize->xml_serialize("����Cѡ��", "_BinSelectC", "", "BOOL", pParas->m_binIn[2].nSelect);
    pXmlSierialize->xml_serialize("����Rѡ��", "_BinSelectR", "", "BOOL", pParas->m_binIn[3].nSelect);
    pXmlSierialize->xml_serialize("����aѡ��", "_BinSelecta", "", "BOOL", pParas->m_binIn[4].nSelect);
    pXmlSierialize->xml_serialize("����bѡ��", "_BinSelectb", "", "BOOL", pParas->m_binIn[5].nSelect);
    pXmlSierialize->xml_serialize("����cѡ��", "_BinSelectc", "", "BOOL", pParas->m_binIn[6].nSelect);
    pXmlSierialize->xml_serialize("����rѡ��", "_BinSelectr", "", "BOOL", pParas->m_binIn[7].nSelect);

    pXmlSierialize->xml_serialize("����1","_Bout1","","DOutputState",pParas->m_binOut[0][0].nState);
    pXmlSierialize->xml_serialize("����2","_Bout2","","DOutputState",pParas->m_binOut[0][1].nState);
    pXmlSierialize->xml_serialize("����3","_Bout3","","DOutputState",pParas->m_binOut[0][2].nState);
    pXmlSierialize->xml_serialize("����4","_Bout4","","DOutputState",pParas->m_binOut[0][3].nState);

    pXmlSierialize->xml_serialize("����1����״̬","_BoutF1","","DOutputState",pParas->m_binOut[1][0].nState);
    pXmlSierialize->xml_serialize("����2����״̬","_BoutF2","","DOutputState",pParas->m_binOut[1][1].nState);
    pXmlSierialize->xml_serialize("����3����״̬","_BoutF3","","DOutputState",pParas->m_binOut[1][2].nState);
    pXmlSierialize->xml_serialize("����4����״̬","_BoutF4","","DOutputState",pParas->m_binOut[1][3].nState);
    pXmlSierialize->xml_serialize("��������ʱ��","_BoutHoldTime","s","number",pParas->m_binOut[1][0].fHoldTime);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_vol_actvalue(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ֵ","TripValue","A/V","number",pResults->m_fTripValue);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
	pXmlSierialize->xml_serialize("����1����ֵ","TripValueA","A/V","number",pResults->m_fTripValueChl[0]);
	pXmlSierialize->xml_serialize("����2����ֵ","TripValueB","A/V","number",pResults->m_fTripValueChl[1]);
	pXmlSierialize->xml_serialize("����3����ֵ","TripValueC","A/V","number",pResults->m_fTripValueChl[2]);
	pXmlSierialize->xml_serialize("����4����ֵ","TripValueD","A/V","number",pResults->m_fTripValueChl[3]);
	pXmlSierialize->xml_serialize("����5����ֵ","TripValueE","A/V","number",pResults->m_fTripValueChl[4]);
	pXmlSierialize->xml_serialize("����6����ֵ","TripValueF","A/V","number",pResults->m_fTripValueChl[5]);
	pXmlSierialize->xml_serialize("����7����ֵ","TripValueG","A/V","number",pResults->m_fTripValueChl[6]);
	pXmlSierialize->xml_serialize("����8����ֵ","TripValueH","A/V","number",pResults->m_fTripValueChl[7]);
#else
  pXmlSierialize->xml_serialize(/* "����ֵ" */ g_sLangTxt_State_ActionValue.GetString(), "TripValue", "A/V", "number", pResults->m_fTripValue);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);
  pXmlSierialize->xml_serialize(/* "����1����ֵ" */ g_sLangTxt_Native_input1_ActionVal.GetString(), "TripValueA", "A/V", "number", pResults->m_fTripValueChl[0]);
  pXmlSierialize->xml_serialize(/* "����2����ֵ" */ g_sLangTxt_Native_input2_ActionVal.GetString(), "TripValueB", "A/V", "number", pResults->m_fTripValueChl[1]);
  pXmlSierialize->xml_serialize(/* "����3����ֵ" */ g_sLangTxt_Native_input3_ActionVal.GetString(), "TripValueC", "A/V", "number", pResults->m_fTripValueChl[2]);
  pXmlSierialize->xml_serialize(/* "����4����ֵ" */ g_sLangTxt_Native_input4_ActionVal.GetString(), "TripValueD", "A/V", "number", pResults->m_fTripValueChl[3]);
  pXmlSierialize->xml_serialize(/* "����5����ֵ" */ g_sLangTxt_Native_input5_ActionVal.GetString(), "TripValueE", "A/V", "number", pResults->m_fTripValueChl[4]);
  pXmlSierialize->xml_serialize(/* "����6����ֵ" */ g_sLangTxt_Native_input6_ActionVal.GetString(), "TripValueF", "A/V", "number", pResults->m_fTripValueChl[5]);
  pXmlSierialize->xml_serialize(/* "����7����ֵ" */ g_sLangTxt_Native_input7_ActionVal.GetString(), "TripValueG", "A/V", "number", pResults->m_fTripValueChl[6]);
  pXmlSierialize->xml_serialize(/* "����8����ֵ" */ g_sLangTxt_Native_input8_ActionVal.GetString(), "TripValueH", "A/V", "number", pResults->m_fTripValueChl[7]);
#endif
}

void stt_xml_serialize_vol_actvalue_pnv(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����ֵ","TripValue","A/V","number",pResults->m_fTripValue);
    pXmlSierialize->xml_serialize("����ֵ","ReturnValue","A/V","number",pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_VolActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize_ex(&(pTests->m_oTmtParas),  pXmlParas);	//�ļ��Ķ�д
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize_vol_actvalue(&pTests->m_oTmtResults,  pXmlResults);
	}

	return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_VolActValuePnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        stt_xml_serialize(&(pTests->m_oTmtParas),  pXmlParas);	//�ļ��Ķ�д
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        stt_xml_serialize_vol_actvalue_pnv(&pTests->m_oTmtResults,  pXmlResults);
    }

    return pXmlParas;
}


