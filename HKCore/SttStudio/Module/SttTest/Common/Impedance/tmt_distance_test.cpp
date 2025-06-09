#include "stdafx.h"
#include "tmt_distance_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_DistanceParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DistanceParas));
	pParas->init();
}

void stt_init_paras(tmt_DistanceParas_I *pParas)
{
    memset(&pParas, 0, sizeof(tmt_DistanceParas_I));
    pParas->init();
}

void stt_init_paras_ex(tmt_DistanceParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DistanceParasEx));
	pParas->init();
}

void stt_init_results(tmt_DistanceResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DistanceResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_DistanceParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.25 caoxc ������Ŀ���ƺͷ���id
	pXmlSierialize->xml_serialize("��Ŀ����", "TestName", "��", "string",  pParas->m_pszTestName);
	pXmlSierialize->xml_serialize("����", "GroupID", "��", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize("��������", "FaultType", "��", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("�迹��ֵ", "ZSetting", "��", "set", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("�迹��", "ZAng", "��", "set", pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize("����", "Rate", "��", "number",pParas->m_fRate[0]);

	pXmlSierialize->xml_serialize("��������ʱ��", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("��·����", "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
//	pXmlSierialize->xml_serialize("��·��ѹ", "FaultVf", "V", "number", pParas->m_oImpedance.m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize("���Ϸ���", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("��������","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);

	pXmlSierialize->xml_serialize("�������������ʱ��","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
    pXmlSierialize->xml_serialize("���ѹ","UNom","V","number",pParas->m_fUNom);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
		pXmlSierialize->xml_serialize("�������������ʱ��","PostFaultTime","s","number",pParas->m_fPostFaultTime);
	}

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	//����ֵ
	pXmlSierialize->xml_serialize("�ӵؾ���I�ζ�ֵ","Zeset1","��","float",pParas->m_fSettingLN[0]);
	pXmlSierialize->xml_serialize("�ӵؾ���II�ζ�ֵ","Zeset2","��","float",pParas->m_fSettingLN[1]);
	pXmlSierialize->xml_serialize("�ӵؾ���III�ζ�ֵ","Zeset3","��","float",pParas->m_fSettingLN[2]);
	pXmlSierialize->xml_serialize("�ӵؾ���IV�ζ�ֵ","Zeset4","��","float",pParas->m_fSettingLN[3]);
	pXmlSierialize->xml_serialize("�ӵؾ���V�ζ�ֵ","Zeset5","��","float",pParas->m_fSettingLN[4]);

	pXmlSierialize->xml_serialize("�ӵؾ���I��ʱ��","Teset1","s","float",pParas->m_fTSettingLN[0]);
	pXmlSierialize->xml_serialize("�ӵؾ���II��ʱ��","Teset2","s","float",pParas->m_fTSettingLN[1]);
	pXmlSierialize->xml_serialize("�ӵؾ���III��ʱ��","Teset3","s","float",pParas->m_fTSettingLN[2]);
	pXmlSierialize->xml_serialize("�ӵؾ���IV��ʱ��","Teset4","s","float",pParas->m_fTSettingLN[3]);
	pXmlSierialize->xml_serialize("�ӵؾ���V��ʱ��","Teset5","s","float",pParas->m_fTSettingLN[4]);

	pXmlSierialize->xml_serialize("������I�ζ�ֵ","Zxset1","��","float",pParas->m_fSettingLL[0]);
	pXmlSierialize->xml_serialize("������II�ζ�ֵ","Zxset2","��","float",pParas->m_fSettingLL[1]);
	pXmlSierialize->xml_serialize("������III�ζ�ֵ","Zxset3","��","float",pParas->m_fSettingLL[2]);
	pXmlSierialize->xml_serialize("������IV�ζ�ֵ","Zxset4","��","float",pParas->m_fSettingLL[3]);
	pXmlSierialize->xml_serialize("������V�ζ�ֵ","Zxset5","��","float",pParas->m_fSettingLL[4]);

	pXmlSierialize->xml_serialize("������I��ʱ��","Txset1","s","float",pParas->m_fTSettingLL[0]);
	pXmlSierialize->xml_serialize("������II��ʱ��","Txset2","s","float",pParas->m_fTSettingLL[1]);
	pXmlSierialize->xml_serialize("������III��ʱ��","Txset3","s","float",pParas->m_fTSettingLL[2]);
	pXmlSierialize->xml_serialize("������IV��ʱ��","Txset4","s","float",pParas->m_fTSettingLL[3]);
	pXmlSierialize->xml_serialize("������V��ʱ��","Txset5","s","float",pParas->m_fTSettingLL[4]);
#else
	//2022.5.25 caoxc ������Ŀ���ƺͷ���id
	pXmlSierialize->xml_serialize(/* "��Ŀ����" */g_sLangTxt_Native_ProjName.GetString(), "TestName", "��", "string",  pParas->m_pszTestName);
	pXmlSierialize->xml_serialize(/* "����" */g_sLangTxt_Native_Grouping.GetString(), "GroupID", "��", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "��", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "�迹��ֵ" */g_sLangTxt_Native_impedance_setting.GetString(), "ZSetting", "��", "set", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "�迹��" */g_sLangTxt_Native_ImpedanceAngles.GetString(), "ZAng", "��", "set", pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize(/* "����" */g_sLangTxt_Native_Multiple.GetString(), "Rate", "��", "number",pParas->m_fRate[0]);

	pXmlSierialize->xml_serialize(/* "��������ʱ��" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "��·����" */g_sLangTxt_Native_ShortCircuit.GetString(), "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	//	pXmlSierialize->xml_serialize("��·��ѹ", "FaultVf", "V", "number", pParas->m_oImpedance.m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize(/* "���Ϸ���" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);

	pXmlSierialize->xml_serialize(/* "�������������ʱ��" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);

	if (stt_xml_serialize_is_read(pXmlSierialize))//���ݴ���
	{
		pXmlSierialize->xml_serialize(/* "�������������ʱ��" */g_sLangTxt_Native_DurProtTrip.GetString(),"PostFaultTime","s","number",pParas->m_fPostFaultTime);
	}

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	//����ֵ
	pXmlSierialize->xml_serialize(/* "�ӵؾ���I�ζ�ֵ" */g_sLangTxt_Native_GroundDisSetI.GetString(),"Zeset1","��","float",pParas->m_fSettingLN[0]);
	pXmlSierialize->xml_serialize(/* "�ӵؾ���II�ζ�ֵ" */g_sLangTxt_Native_GroundDisSetII.GetString(),"Zeset2","��","float",pParas->m_fSettingLN[1]);
	pXmlSierialize->xml_serialize(/* "�ӵؾ���III�ζ�ֵ" */g_sLangTxt_Native_GroundDisSetIII.GetString(),"Zeset3","��","float",pParas->m_fSettingLN[2]);
	pXmlSierialize->xml_serialize(/* "�ӵؾ���IV�ζ�ֵ" */g_sLangTxt_Native_GroundDisSetIV.GetString(),"Zeset4","��","float",pParas->m_fSettingLN[3]);
	pXmlSierialize->xml_serialize(/* "�ӵؾ���V�ζ�ֵ" */g_sLangTxt_Native_GroundDisSetV.GetString(),"Zeset5","��","float",pParas->m_fSettingLN[4]);

	pXmlSierialize->xml_serialize(/* "�ӵؾ���I��ʱ��" */g_sLangTxt_Native_GroundDisTimeI.GetString(),"Teset1","s","float",pParas->m_fTSettingLN[0]);
	pXmlSierialize->xml_serialize(/* "�ӵؾ���II��ʱ��" */g_sLangTxt_Native_GroundDisTimeII.GetString(),"Teset2","s","float",pParas->m_fTSettingLN[1]);
	pXmlSierialize->xml_serialize(/* "�ӵؾ���III��ʱ��" */g_sLangTxt_Native_GroundDisTimeIII.GetString(),"Teset3","s","float",pParas->m_fTSettingLN[2]);
	pXmlSierialize->xml_serialize(/* "�ӵؾ���IV��ʱ��" */g_sLangTxt_Native_GroundDisTimeIV.GetString(),"Teset4","s","float",pParas->m_fTSettingLN[3]);
	pXmlSierialize->xml_serialize(/* "�ӵؾ���V��ʱ��" */g_sLangTxt_Native_GroundDisTimeV.GetString(),"Teset5","s","float",pParas->m_fTSettingLN[4]);

	pXmlSierialize->xml_serialize(/* "������I�ζ�ֵ" */g_sLangTxt_Native_PhaseDisSetI.GetString(),"Zxset1","��","float",pParas->m_fSettingLL[0]);
	pXmlSierialize->xml_serialize(/* "������II�ζ�ֵ" */g_sLangTxt_Native_PhaseDisSetII.GetString(),"Zxset2","��","float",pParas->m_fSettingLL[1]);
	pXmlSierialize->xml_serialize(/* "������III�ζ�ֵ" */g_sLangTxt_Native_PhaseDisSetIII.GetString(),"Zxset3","��","float",pParas->m_fSettingLL[2]);
	pXmlSierialize->xml_serialize(/* "������IV�ζ�ֵ" */g_sLangTxt_Native_PhaseDisSetIV.GetString(),"Zxset4","��","float",pParas->m_fSettingLL[3]);
	pXmlSierialize->xml_serialize(/* "������V�ζ�ֵ" */g_sLangTxt_Native_PhaseDisSetV.GetString(),"Zxset5","��","float",pParas->m_fSettingLL[4]);

	pXmlSierialize->xml_serialize(/* "������I��ʱ��" */g_sLangTxt_Native_PhaseDisTimeI.GetString(),"Txset1","s","float",pParas->m_fTSettingLL[0]);
	pXmlSierialize->xml_serialize(/* "������II��ʱ��" */g_sLangTxt_Native_PhaseDisTimeII.GetString(),"Txset2","s","float",pParas->m_fTSettingLL[1]);
	pXmlSierialize->xml_serialize(/* "������III��ʱ��" */g_sLangTxt_Native_PhaseDisTimeIII.GetString(),"Txset3","s","float",pParas->m_fTSettingLL[2]);
	pXmlSierialize->xml_serialize(/* "������IV��ʱ��" */g_sLangTxt_Native_PhaseDisTimeIV.GetString(),"Txset4","s","float",pParas->m_fTSettingLL[3]);
	pXmlSierialize->xml_serialize(/* "������V��ʱ��" */g_sLangTxt_Native_PhaseDisTimeV.GetString(),"Txset5","s","float",pParas->m_fTSettingLL[4]);
#endif
	
}

void stt_xml_serialize_I(tmt_DistanceParas_I *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����A", "BinA", "", "DInputState", pParas->m_nBinState[0]);
    pXmlSierialize->xml_serialize("����B", "BinB", "", "DInputState", pParas->m_nBinState[1]);
    pXmlSierialize->xml_serialize("����C", "BinC", "", "DInputState", pParas->m_nBinState[2]);
    pXmlSierialize->xml_serialize("����D", "BinD", "", "DInputState", pParas->m_nBinState[3]);
    pXmlSierialize->xml_serialize("����E", "BinE", "", "DInputState", pParas->m_nBinState[4]);
    pXmlSierialize->xml_serialize("����F", "BinF", "", "DInputState", pParas->m_nBinState[5]);
    pXmlSierialize->xml_serialize("����G", "BinG", "", "DInputState", pParas->m_nBinState[6]);
    pXmlSierialize->xml_serialize("����H", "BinH", "", "DInputState", pParas->m_nBinState[7]);
    pXmlSierialize->xml_serialize("�����߼�", "_AndOr", "", "InPutLogic", pParas->m_nBinLogic);
#else
#endif

}

void stt_xml_serialize_ex(tmt_DistanceParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�迹��ֵ(���ʽ)", "ZSettingExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("����ʱ�䶨ֵ(���ʽ)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	pXmlSierialize->xml_serialize(/* "�迹��ֵ(���ʽ)" */g_sLangTxt_Native_impedance_setExp.GetString(), "ZSettingExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "����ʱ�䶨ֵ(���ʽ)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_DistanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��·�迹", "Zshort", "��", "number", pResults->m_fImp);
	pXmlSierialize->xml_serialize("��·�迹��", "IShortAngle", "��", "number", pResults->m_fImpAngle);
#else
	pXmlSierialize->xml_serialize(/* "��·�迹" */g_sLangTxt_Native_ShortZImp.GetString(), "Zshort", "��", "number", pResults->m_fImp);
	pXmlSierialize->xml_serialize(/* "��·�迹��" */g_sLangTxt_Native_ShortZImpAng.GetString(), "IShortAngle", "��", "number", pResults->m_fImpAngle);
#endif

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_ex(&(pTests->m_oDistanceParas), pXmlParas);	//�ļ��Ķ�д
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize_ex(&(pTests->m_oDistanceParas), pXmlParas);	//���Բ����·�
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize(&pTests->m_oDistanceResults, pXmlResults);
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize(&pTests->m_oDistanceResults, pXmlResults);
		}
	}

	return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceTest_I *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize_I(&(pTests->m_oDistanceParas), pXmlParas);	//�ļ��Ķ�д
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize_I(&(pTests->m_oDistanceParas), pXmlParas);	//���Բ����·�
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize(&pTests->m_oDistanceResults, pXmlResults);
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize(&pTests->m_oDistanceResults, pXmlResults);
        }
    }

    return pXmlParas;
}
