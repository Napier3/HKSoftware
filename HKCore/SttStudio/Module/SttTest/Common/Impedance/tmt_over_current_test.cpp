#include "stdafx.h"
#include "tmt_over_current_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_OverCurrentParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_OverCurrentParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_OverCurrentParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_OverCurrentParasEx));
	pParas->init();
}

void stt_init_results(tmt_OverCurrentResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_OverCurrentResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serializeOverCurrentSetting(tmt_OverCurrentParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//����ֵ
	pXmlSierialize->xml_serialize("����I�ζ�ֵ","Iset1","��","float",pParas->m_fSettingOverCur[0]);
	pXmlSierialize->xml_serialize("����II�ζ�ֵ","Iset2","��","float",pParas->m_fSettingOverCur[1]);
	pXmlSierialize->xml_serialize("����III�ζ�ֵ","Iset3","��","float",pParas->m_fSettingOverCur[2]);
	pXmlSierialize->xml_serialize("����IV�ζ�ֵ","Iset4","��","float",pParas->m_fSettingOverCur[3]);
	pXmlSierialize->xml_serialize("����V�ζ�ֵ","Iset5","��","float",pParas->m_fSettingOverCur[4]);

	pXmlSierialize->xml_serialize("����I��ʱ��","Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize("����II��ʱ��","Tset2","s","float",pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize("����III��ʱ��","Tset3","s","float",pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize("����IV��ʱ��","Tset4","s","float",pParas->m_fSettingTime[3]);
	pXmlSierialize->xml_serialize("����V��ʱ��","Tset5","s","float",pParas->m_fSettingTime[4]);
#else
	//����ֵ
	pXmlSierialize->xml_serialize(/* "����I�ζ�ֵ" */g_sLangTxt_Native_OverCurrentI.GetString(),"Iset1","��","float",pParas->m_fSettingOverCur[0]);
	pXmlSierialize->xml_serialize(/* "����II�ζ�ֵ" */g_sLangTxt_Native_OverCurrentII.GetString(),"Iset2","��","float",pParas->m_fSettingOverCur[1]);
	pXmlSierialize->xml_serialize(/* "����III�ζ�ֵ" */g_sLangTxt_Native_OverCurrentIII.GetString(),"Iset3","��","float",pParas->m_fSettingOverCur[2]);
	pXmlSierialize->xml_serialize(/* "����IV�ζ�ֵ" */g_sLangTxt_Native_OverCurrentIV.GetString(),"Iset4","��","float",pParas->m_fSettingOverCur[3]);
	pXmlSierialize->xml_serialize(/* "����V�ζ�ֵ" */g_sLangTxt_Native_OverCurrentV.GetString(),"Iset5","��","float",pParas->m_fSettingOverCur[4]);

	pXmlSierialize->xml_serialize(/* "����I��ʱ��" */g_sLangTxt_Native_OverCurrentITime.GetString(),"Tset1","s","float",pParas->m_fSettingTime[0]);
	pXmlSierialize->xml_serialize(/* "����II��ʱ��" */g_sLangTxt_Native_OverCurrentIITime.GetString(),"Tset2","s","float",pParas->m_fSettingTime[1]);
	pXmlSierialize->xml_serialize(/* "����III��ʱ��" */g_sLangTxt_Native_OverCurrentIIITime.GetString(),"Tset3","s","float",pParas->m_fSettingTime[2]);
	pXmlSierialize->xml_serialize(/* "����IV��ʱ��" */g_sLangTxt_Native_OverCurrentIVTime.GetString(),"Tset4","s","float",pParas->m_fSettingTime[3]);
	pXmlSierialize->xml_serialize(/* "����V��ʱ��" */g_sLangTxt_Native_OverCurrentVTime.GetString(),"Tset5","s","float",pParas->m_fSettingTime[4]);
#endif

}


void stt_xml_serialize_OverCurrent(tmt_OverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��������", "FaultType", "��", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("������������", "ISetting", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("����", "Rate", "��", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("���Ϸ���", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("��·�迹", "Z", "��", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize("��·�迹��", "ZPh", "��", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize("��������","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize("ģ��PT�������", "ImitPTPhase", "", "PTBreakPnv",pParas->m_nImitPTPhase); 
	//Pnv��������,���Ƿ�ģ��PT���ߺ�PT��������Ϊ�ϲ�Ϊ1������,Ϊ0ʱ�̶���ģ��PT����,����Ϊ1ʱģ��A�����;
	//���ù̶���·�迹�ķ�ʽ,δ�õ���·��ѹ

	pXmlSierialize->xml_serialize("�������������ʱ��","PostFaultTime","s","number",pParas->m_fPostFaultTime);

	pXmlSierialize->xml_serialize("Ua��ֵ", "_Ua", "V", "number",  pParas->m_fVolAmp[0]);
	pXmlSierialize->xml_serialize("Ub��ֵ", "_Ub", "V", "number",  pParas->m_fVolAmp[1]);
	pXmlSierialize->xml_serialize("Uc��ֵ", "_Uc", "V", "number",  pParas->m_fVolAmp[2]);
	pXmlSierialize->xml_serialize("Uz��ֵ", "_Uz", "V", "number",  pParas->m_fVolAmp[3]);

	pXmlSierialize->xml_serialize("Ua��λ", "_UaPh", "��", "number",  pParas->m_fVolAng[0]);
	pXmlSierialize->xml_serialize("Ub��λ", "_UbPh", "��", "number",  pParas->m_fVolAng[1]);
	pXmlSierialize->xml_serialize("Uc��λ", "_UcPh", "��", "number",  pParas->m_fVolAng[2]);
	pXmlSierialize->xml_serialize("Uz��λ", "_UzPh", "��", "number",  pParas->m_fVolAng[3]);

	pXmlSierialize->xml_serialize("����Ua��ֵ", "_FaultUa", "V", "number",  pParas->m_fVolAmp[4]);
	pXmlSierialize->xml_serialize("����Ub��ֵ", "_FaultUb", "V", "number",  pParas->m_fVolAmp[5]);
	pXmlSierialize->xml_serialize("����Uc��ֵ", "_FaultUc", "V", "number",  pParas->m_fVolAmp[6]);
	pXmlSierialize->xml_serialize("����Uz��ֵ", "_FaultUx", "V", "number",  pParas->m_fVolAmp[7]);

	pXmlSierialize->xml_serialize("����Ua��λ", "_FaultUaPh", "��", "number",  pParas->m_fVolAng[4]);
	pXmlSierialize->xml_serialize("����Ub��λ", "_FaultUbPh", "��", "number",  pParas->m_fVolAng[5]);
	pXmlSierialize->xml_serialize("����Uc��λ", "_FaultUcPh", "��", "number",  pParas->m_fVolAng[6]);
	pXmlSierialize->xml_serialize("����Uz��λ", "_FaultUzPh", "��", "number",  pParas->m_fVolAng[7]);
#else
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", /* "��" */g_sLangTxt_without.GetString(), "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "������������" */g_sLangTxt_Native_SetPickCurr.GetString(), "ISetting", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "����" */g_sLangTxt_Native_Multiple.GetString(), "Rate", /* "��" */g_sLangTxt_without.GetString(), "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "����ʱ�䶨ֵ" */g_sLangTxt_Native_OpTimeSet.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "���Ϸ���" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "��·�迹" */g_sLangTxt_Native_ShortZImp.GetString(), "Z", "��", "set", pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize(/* "��·�迹��" */g_sLangTxt_Native_ShortZImpAng.GetString(), "ZPh", "��", "set", pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize(/* "ģ��PT�������" */g_sLangTxt_Native_PTLineSimPhase.GetString(), "ImitPTPhase", "", "PTBreakPnv",pParas->m_nImitPTPhase); 
	//Pnv��������,���Ƿ�ģ��PT���ߺ�PT��������Ϊ�ϲ�Ϊ1������,Ϊ0ʱ�̶���ģ��PT����,����Ϊ1ʱģ��A�����;
	//���ù̶���·�迹�ķ�ʽ,δ�õ���·��ѹ

	pXmlSierialize->xml_serialize(/* "�������������ʱ��" */g_sLangTxt_Native_DurProtTrip.GetString(),"PostFaultTime","s","number",pParas->m_fPostFaultTime);

	pXmlSierialize->xml_serialize(/* "Ua��ֵ" */g_sLangTxt_Native_UaAmplitude.GetString(), "_Ua", "V", "number",  pParas->m_fVolAmp[0]);
	pXmlSierialize->xml_serialize(/* "Ub��ֵ" */g_sLangTxt_Native_UbAmplitude.GetString(), "_Ub", "V", "number",  pParas->m_fVolAmp[1]);
	pXmlSierialize->xml_serialize(/* "Uc��ֵ" */g_sLangTxt_Native_UcAmplitude.GetString(), "_Uc", "V", "number",  pParas->m_fVolAmp[2]);
	pXmlSierialize->xml_serialize(/* "Uz��ֵ" */g_sLangTxt_Native_UzAmp.GetString(), "_Uz", "V", "number",  pParas->m_fVolAmp[3]);

	pXmlSierialize->xml_serialize(/* "Ua��λ" */g_sLangTxt_Native_UaPhase.GetString(), "_UaPh", "��", "number",  pParas->m_fVolAng[0]);
	pXmlSierialize->xml_serialize(/* "Ub��λ" */g_sLangTxt_Native_UbPhase.GetString(), "_UbPh", "��", "number",  pParas->m_fVolAng[1]);
	pXmlSierialize->xml_serialize(/* "Uc��λ" */g_sLangTxt_Native_UcPhase.GetString(), "_UcPh", "��", "number",  pParas->m_fVolAng[2]);
	pXmlSierialize->xml_serialize(/* "Uz��λ" */g_sLangTxt_Native_UzPhase.GetString(), "_UzPh", "��", "number",  pParas->m_fVolAng[3]);

	pXmlSierialize->xml_serialize(/* "����Ua��ֵ" */g_sLangTxt_Native_ErrUaAmp.GetString(), "_FaultUa", "V", "number",  pParas->m_fVolAmp[4]);
	pXmlSierialize->xml_serialize(/* "����Ub��ֵ" */g_sLangTxt_Native_ErrUbAmp.GetString(), "_FaultUb", "V", "number",  pParas->m_fVolAmp[5]);
	pXmlSierialize->xml_serialize(/* "����Uc��ֵ" */g_sLangTxt_Native_ErrUcAmp.GetString(), "_FaultUc", "V", "number",  pParas->m_fVolAmp[6]);
	pXmlSierialize->xml_serialize(/* "����Uz��ֵ" */g_sLangTxt_Native_ErrUzAmp.GetString(), "_FaultUx", "V", "number",  pParas->m_fVolAmp[7]);

	pXmlSierialize->xml_serialize(/* "����Ua��λ" */g_sLangTxt_Native_ErrUaPh.GetString(), "_FaultUaPh", "��", "number",  pParas->m_fVolAng[4]);
	pXmlSierialize->xml_serialize(/* "����Ub��λ" */g_sLangTxt_Native_ErrUbPh.GetString(), "_FaultUbPh", "��", "number",  pParas->m_fVolAng[5]);
	pXmlSierialize->xml_serialize(/* "����Uc��λ" */g_sLangTxt_Native_ErrUcPh.GetString(), "_FaultUcPh", "��", "number",  pParas->m_fVolAng[6]);
	pXmlSierialize->xml_serialize(/* "����Uz��λ" */g_sLangTxt_Native_ErrUzPh.GetString(), "_FaultUzPh", "��", "number",  pParas->m_fVolAng[7]);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serializeOverCurrentSetting(pParas,pXmlSierialize);
}

void stt_xml_serialize_OverCurrent_ex(tmt_OverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_OverCurrent(pParas,pXmlSierialize);

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("������������(���ʽ)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ(���ʽ)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	pXmlSierialize->xml_serialize(/* "������������(���ʽ)" */g_sLangTxt_Native_SetActCurExp.GetString(), "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "����ʱ�䶨ֵ(���ʽ)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_StateOverCurrent(tmt_OverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.26 caoxc ������Ŀ����ID
	pXmlSierialize->xml_serialize("����", "GroupID", "��", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize("��������", "FaultType", "��", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("��������ʱ��", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("������������", "FaultIf", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("����", "Rate", "��", "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize("��·��ѹ", "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize("���Ϸ���", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("�Ƿ�ģ��PT����","PTBreak","","BOOL",pParas->m_bImitatePT); 
	pXmlSierialize->xml_serialize("ģ��PT�������", "PTBreakPhase", "", "DiffFaultType",pParas->m_nImitPTPhase); //״̬���й���,���Ƿ�ģ��PT���ߺ�PT��������Ϊ��������;���ù̶���·��ѹ�ķ�ʽ,δ�õ���·�迹
	pXmlSierialize->xml_serialize("�������������ʱ��","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
    if (stt_xml_serialize_is_read(pXmlSierialize))//Pnv
    {
        pXmlSierialize->xml_serialize("��·����", "ShortCur", "A", "number", pParas->m_fSetting[0]);
        pXmlSierialize->xml_serialize("��·��ѹ", "ShortVol", "V", "number", pParas->m_fSCVoltage[0]);
        //������ʱ��Ϊ��������ʱ�䣬����id�����ڹ���ʱ��ԣ�ȣ�ʵ��Ϊ������ͣ�������ʵ��תΪ����ʱ��ԣ�ȴ���
        //pXmlSierialize->xml_serialize("������ʱ��", "FaultTime", "s", "set", pParas->m_fTSetting);
        pXmlSierialize->xml_serialize("����ǰ��ѹ", "PreFaultUa", "V", "number", pParas->m_fUNom);
        pXmlSierialize->xml_serialize("����ǰ����", "PreFaulIa", "A", "number",pParas->m_fIfh);
        pXmlSierialize->xml_serialize("����ǰ�迹��", "PreFaulPhi", "��", "number",pParas->m_fPowerAngle);
    }
#else
	//2022.5.26 caoxc ������Ŀ����ID
	pXmlSierialize->xml_serialize(/* "����" */g_sLangTxt_Native_Grouping.GetString(), "GroupID", /* "��" */g_sLangTxt_without.GetString(), "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", /* "��" */g_sLangTxt_without.GetString(), "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "��������ʱ��" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "������������" */g_sLangTxt_Native_SetPickCurr.GetString(), "FaultIf", "A", "number", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "����" */g_sLangTxt_Native_SetPickCurr.GetString(), "Rate", /* "��" */g_sLangTxt_without.GetString(), "number",pParas->m_fRate[0]);
	pXmlSierialize->xml_serialize(/* "��·��ѹ" */g_sLangTxt_Native_SetPickCurr.GetString(), "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize(/* "���Ϸ���" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "�Ƿ�ģ��PT����" */g_sLangTxt_Native_PTLineSimulate.GetString(),"PTBreak","","BOOL",pParas->m_bImitatePT); 
	pXmlSierialize->xml_serialize(/* "ģ��PT�������" */g_sLangTxt_Native_PTLineSimPhase.GetString(), "PTBreakPhase", "", "DiffFaultType",pParas->m_nImitPTPhase); //״̬���й���,���Ƿ�ģ��PT���ߺ�PT��������Ϊ��������;���ù̶���·��ѹ�ķ�ʽ,δ�õ���·�迹
	pXmlSierialize->xml_serialize(/* "�������������ʱ��" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	stt_xml_serializeOverCurrentSetting(pParas,pXmlSierialize);
}

void stt_xml_serialize_StateOverCurrent_ex(tmt_OverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("������������(���ʽ)", "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ(���ʽ)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	pXmlSierialize->xml_serialize(/* "������������(���ʽ)" */g_sLangTxt_Native_SetActCurExp.GetString(), "FaultIfExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "����ʱ�䶨ֵ(���ʽ)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif
	stt_xml_serialize_StateOverCurrent(pParas,pXmlSierialize);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_OverCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ֵ", "IGL", "A", "number", pResults->m_fOverCurrent);
#else
	pXmlSierialize->xml_serialize(/* "����ֵ" */g_sLangTxt_Native_OverCurrentValue.GetString(), "IGL", "A", "number", pResults->m_fOverCurrent);
#endif
    pXmlSierialize->xml_serialize("����E��������", "ActE", "", "number", pResults->m_nActID[4]);
    pXmlSierialize->xml_serialize("����F��������", "ActF", "", "number", pResults->m_nActID[5]);
    pXmlSierialize->xml_serialize("����G��������", "ActG", "", "number", pResults->m_nActID[6]);
    pXmlSierialize->xml_serialize("����H��������", "ActH", "", "number", pResults->m_nActID[7]);

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_OverCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_OverCurrent) == 0)
		{
			stt_xml_serialize_OverCurrent_ex(&(pTests->m_oOverCurrentParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_StateOverCurrent) == 0)
		{
			stt_xml_serialize_StateOverCurrent_ex(&(pTests->m_oOverCurrentParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oOverCurrentResults, pXmlResults);
	}

	return pXmlParas;
}
