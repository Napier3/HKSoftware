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
	//����ֵ
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("������ʽ","SetMethod","��","number",pParas->m_nSettingMethod);
	pXmlSierialize->xml_serialize("һ�ζ����","Iset","A","number",pParas->m_fRatePrimaryCurr);
	pXmlSierialize->xml_serialize("����I�ζ�ֵ","Iset1","��","float",pParas->m_fSettingDCOverCur[0]);
	pXmlSierialize->xml_serialize("����II�ζ�ֵ","Iset2","��","float",pParas->m_fSettingDCOverCur[1]);
	pXmlSierialize->xml_serialize("����III�ζ�ֵ","Iset3","��","float",pParas->m_fSettingDCOverCur[2]);
	pXmlSierialize->xml_serialize("����IV�ζ�ֵ","Iset4","��","float",pParas->m_fSettingDCOverCur[3]);

	pXmlSierialize->xml_serialize("����I��ʱ��","Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize("����II��ʱ��","Tset2","s","float",pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize("����III��ʱ��","Tset3","s","float",pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize("����IV��ʱ��","Tset4","s","float",pParas->m_fSettingTime[3]);
#else
	pXmlSierialize->xml_serialize(/* "����I�ζ�ֵ" */ g_sLangTxt_Native_OverCurrentI.GetString(), "Iset1", "��", "float", pParas->m_fSettingDCOverCur[0]);
	pXmlSierialize->xml_serialize(/* "����II�ζ�ֵ" */ g_sLangTxt_Native_OverCurrentII.GetString(), "Iset2", "��", "float", pParas->m_fSettingDCOverCur[1]);
	pXmlSierialize->xml_serialize(/* "����III�ζ�ֵ" */ g_sLangTxt_Native_OverCurrentIII.GetString(), "Iset3", "��", "float", pParas->m_fSettingDCOverCur[2]);
	pXmlSierialize->xml_serialize(/* "����IV�ζ�ֵ" */ g_sLangTxt_Native_OverCurrentIV.GetString(), "Iset4", "��", "float", pParas->m_fSettingDCOverCur[3]);

	pXmlSierialize->xml_serialize(/* "����I��ʱ��" */ g_sLangTxt_Native_OverCurrentITime.GetString(), "Tset1", "s", "float", pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize(/* "����II��ʱ��" */ g_sLangTxt_Native_OverCurrentIITime.GetString(), "Tset2", "s", "float", pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize(/* "����III��ʱ��" */ g_sLangTxt_Native_OverCurrentIIITime.GetString(), "Tset3", "s", "float", pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize(/* "����IV��ʱ��" */ g_sLangTxt_Native_OverCurrentIVTime.GetString(), "Tset4", "s", "float", pParas->m_fSettingTime[3]);
#endif
}


void stt_xml_serialize_DCOverCurrent(tmt_DCOverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����", "GroupID", "��", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize("����ͨ��", "FaultChannel", "��", "UIRampChannel",  pParas->m_nFaultChannel);
	pXmlSierialize->xml_serialize("������������", "FaultIf", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("����", "Rate", "��", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("������ʱ��", "TSet1", "s","number",pParas->m_fMaxFaultTime);
	pXmlSierialize->xml_serialize("��������ʱ��", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("��ѹ", "Voltage", "kV", "number", pParas->m_fVoltage);
	pXmlSierialize->xml_serialize("һ�ζ��ѹ","PreFaultVol","kV","number",pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize("����ǰ����","PreFaultCur","A","number",pParas->m_fPreFaultCur);

	pXmlSierialize->xml_serialize("��·�迹", "Z", "��", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize("��·�迹��", "ZPh", "��", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize("�������������ʱ��","PostFaultTime","s","number",pParas->m_fAfterTriggerFaultTime);
//     pXmlSierialize->xml_serialize("����ʱ��ԣ��","FaultTime","s","number",pParas->m_fFaultTime);//20240617 suyang���û���Ĳ������·�����IDһ���Ĳ��� 
    pXmlSierialize->xml_serialize("�����߼�","_OutputSwitchMode","s","number",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/* "����" */ g_sLangTxt_Native_Grouping.GetString(), "GroupID", /*  "��" */ g_sLangTxt_None.GetString(), "string",pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize(/* "����ͨ��" */ g_sLangTxt_Native_FaultChnl.GetString(), "FaultChannel", /*  "��" */ g_sLangTxt_None.GetString(),"UIRampChannel", pParas->m_nFaultChannel);
	pXmlSierialize->xml_serialize(/* "������������" */ g_sLangTxt_Native_SetPickCurr.GetString(), "FaultIf", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "����" */ g_sLangTxt_Native_Multiple.GetString(), "Rate", /*  "��" */ g_sLangTxt_None.GetString(), "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "������ʱ��" */ g_sLangTxt_Native_MaxTimeMalf.GetString(), "TSet1", "s", "number", pParas->m_fMaxFaultTime);
	pXmlSierialize->xml_serialize(/* "��������ʱ��" */ g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "��ѹ" */ g_sLangTxt_Native_Voltage.GetString(), "Voltage", "V", "number", pParas->m_fVoltage);
	pXmlSierialize->xml_serialize(/* "����ǰ��ѹ" */ g_sLangTxt_Native_PreFaultVolt.GetString(), "PreFaultVol", "V", "number", pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize(/* "����ǰ����" */ g_sLangTxt_Native_PreFaultCurr.GetString(), "PreFaultCur", "A", "number", pParas->m_fPreFaultCur);

	pXmlSierialize->xml_serialize(/* "��·�迹" */ g_sLangTxt_Native_ShortZImp.GetString(), "Z", "��", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize(/* "��·�迹��" */ g_sLangTxt_Native_ShortZImpAng.GetString(), "ZPh", "��", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize(/* "�������������ʱ��" */ g_sLangTxt_Native_DurProtTrip.GetString(), "PostFaultTime", "s", "number",pParas->m_fAfterTriggerFaultTime);
#endif

	if(stt_xml_serialize_is_write(pXmlSierialize))//�·�
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
	pXmlSierialize->xml_serialize("������������(���ʽ)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ(���ʽ)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
    pXmlSierialize->xml_serialize(/* "������������(���ʽ)" */ g_sLangTxt_Native_SetActCurExp.GetString(), "FaultIfExp", "", "string", pParas->m_pszSetting);
    pXmlSierialize->xml_serialize(/* "����ʱ�䶨ֵ(���ʽ)" */ g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string",pParas->m_pszTSetting);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_DCOverCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ֵ", "IGL", "A", "number", pResults->m_fOverCurrent);
#else
    pXmlSierialize->xml_serialize(/* "����ֵ" */ g_sLangTxt_Native_OverCurrentValue.GetString(), "IGL", "A", "number", pResults->m_fOverCurrent);
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
