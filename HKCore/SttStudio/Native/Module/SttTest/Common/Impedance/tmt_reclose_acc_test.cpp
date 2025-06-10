#include "stdafx.h"
#include "tmt_reclose_acc_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_RecloseAccParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_RecloseAccParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_RecloseAccParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_RecloseAccParasEx));
	pParas->init();
}

void stt_init_results(tmt_RecloseAccResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_RecloseAccResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_RecloseAccParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.26 caoxc ������Ŀ����
	pXmlSierialize->xml_serialize("��Ŀ����","TestName","","number",pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("��һ�ι�������","FaultType1","","number",pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("��һ�ι��ϵ���", "ISet1", "A","number",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("��һ�ι��϶���ʱ��", "TSet1", "s","number",pParas->m_fTSetting[0]);
	//zhouhj 20220719 ���ǵ�����ʱ��ģ���·���ֺ�բʱ���ͻ,�Ҹô���ʱ������ʵ������ɾ���˽ڵ�,ԭ��λ��������˲�������Ϊ���������󱣳�ʱ��,�����غ�բ����,�ò���������
//	pXmlSierialize->xml_serialize("��һ�ι��϶�������ʱ", "TAfterTrig1", "s","number",pParas->m_fTAfterTrig[0]);  
	pXmlSierialize->xml_serialize("��һ�ι��϶�·�迹", "Z1", "V","number",pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize("��һ�ι��϶�·�迹��", "Z1Ph", "��","number",pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize("�ڶ��ι�������","FaultType2","","number",pParas->m_nFaultType[1]);
	pXmlSierialize->xml_serialize("�ڶ��ι��ϵ���", "ISet2", "A","number",pParas->m_fSCCurrent[1]);
	pXmlSierialize->xml_serialize("�ڶ��ι��϶���ʱ��", "TSet2", "s","number",pParas->m_fTSetting[1]);
	//zhouhj 20220719 ���ǵ�����ʱ��ģ���·���ֺ�բʱ���ͻ,�Ҹô���ʱ������ʵ������ɾ���˽ڵ�,ԭ��λ��������˲�������Ϊ���������󱣳�ʱ��,�����غ�բ����,�ò���������
//	pXmlSierialize->xml_serialize("�ڶ��ι��϶�������ʱ", "TAfterTrig2", "s","number",pParas->m_fTAfterTrig[1]);
	pXmlSierialize->xml_serialize("�ڶ��ι��϶�·�迹", "Z2", "V","number",pParas->m_fImpedance[1]);
	pXmlSierialize->xml_serialize("�ڶ��ι��϶�·�迹��", "Z2Ph", "��","number",pParas->m_fImpAngle[1]);

	pXmlSierialize->xml_serialize("��������","FaultPermanent","","number",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize("���ѹ","UNom","","number",pParas->m_fUnom);
    pXmlSierialize->xml_serialize("��ȡ��ѹƵ��","VZFreq","","number",pParas->m_fVzFreq);
#else
	//2022.5.26 caoxc ������Ŀ����
	pXmlSierialize->xml_serialize(/* "��Ŀ����" */g_sLangTxt_Native_ProjName.GetString(),"TestName","","number",pParas->m_pszTestName);

	pXmlSierialize->xml_serialize(/* "��һ�ι�������" */g_sLangTxt_Native_first_fault_type.GetString(),"FaultType1","","number",pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "��һ�ι��ϵ���" */g_sLangTxt_Native_first_fault_current.GetString(), "ISet1", "A","number",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "��һ�ι��϶���ʱ��" */g_sLangTxt_Native_first_faultact_time.GetString(), "TSet1", "s","number",pParas->m_fTSetting[0]);
	//zhouhj 20220719 ���ǵ�����ʱ��ģ���·���ֺ�բʱ���ͻ,�Ҹô���ʱ������ʵ������ɾ���˽ڵ�,ԭ��λ��������˲�������Ϊ���������󱣳�ʱ��,�����غ�բ����,�ò���������
	//	pXmlSierialize->xml_serialize("��һ�ι��϶�������ʱ", "TAfterTrig1", "s","number",pParas->m_fTAfterTrig[0]);  
	pXmlSierialize->xml_serialize(/* "��һ�ι��϶�·�迹" */g_sLangTxt_Native_first_fault_impedance.GetString(), "Z1", "V","number",pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize(/* "��һ�ι��϶�·�迹��" */g_sLangTxt_Native_first_fault_impedance_angle.GetString(), "Z1Ph", "��","number",pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize(/* "�ڶ��ι�������" */g_sLangTxt_Native_second_fault_type.GetString(),"FaultType2","","number",pParas->m_nFaultType[1]);
	pXmlSierialize->xml_serialize(/* "�ڶ��ι��ϵ���" */g_sLangTxt_Native_second_fault_current.GetString(), "ISet2", "A","number",pParas->m_fSCCurrent[1]);
	pXmlSierialize->xml_serialize(/* "�ڶ��ι��϶���ʱ��" */g_sLangTxt_Native_second_faultact_time.GetString(), "TSet2", "s","number",pParas->m_fTSetting[1]);
	//zhouhj 20220719 ���ǵ�����ʱ��ģ���·���ֺ�բʱ���ͻ,�Ҹô���ʱ������ʵ������ɾ���˽ڵ�,ԭ��λ��������˲�������Ϊ���������󱣳�ʱ��,�����غ�բ����,�ò���������
	//	pXmlSierialize->xml_serialize("�ڶ��ι��϶�������ʱ", "TAfterTrig2", "s","number",pParas->m_fTAfterTrig[1]);
	pXmlSierialize->xml_serialize(/* "�ڶ��ι��϶�·�迹" */g_sLangTxt_Native_second_fault_impedance.GetString(), "Z2", "V","number",pParas->m_fImpedance[1]);
	pXmlSierialize->xml_serialize(/* "�ڶ��ι��϶�·�迹��" */g_sLangTxt_Native_second_fault_impedance_angle.GetString(), "Z2Ph", "��","number",pParas->m_fImpAngle[1]);

	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","number",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize(/* "���ѹ" */g_sLangTxt_Report_Vnom.GetString(),"UNom","","number",pParas->m_fUnom);
    pXmlSierialize->xml_serialize("��ȡ��ѹƵ��","VZFreq","","number",pParas->m_fVzFreq);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize, false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_ex(tmt_RecloseAccParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��һ�ι��϶�·�迹(���ʽ)", "Z1Exp", "","string",pParas->m_pszImpedance[0]);
	pXmlSierialize->xml_serialize("��һ�ι��϶�·�迹��(���ʽ)", "Z1PhExp", "","string",pParas->m_pszImpAngle[0]);
	pXmlSierialize->xml_serialize("�ڶ��ι��϶�·�迹(���ʽ)", "Z2Exp", "","string",pParas->m_pszImpedance[1]);
	pXmlSierialize->xml_serialize("�ڶ��ι��϶�·�迹��(���ʽ)", "Z2PhExp", "","string",pParas->m_pszImpAngle[1]);
	pXmlSierialize->xml_serialize("ͬ�ڵ�ѹ��ֵ(���ʽ)","UxInputMagExp","","string",pParas->m_pszUxInput_Mag);
	pXmlSierialize->xml_serialize("ͬ�ڵ�ѹ��λ(���ʽ)","UxInputAngExp","","string",pParas->m_pszUxInput_Ang);
	pXmlSierialize->xml_serialize("�迹��ֵ(��ֵ)","ImpdanceSetting","","number",pParas->m_fImpdanceSetting);
	pXmlSierialize->xml_serialize("�迹��(��ֵ)","ImpAngleSetting","","number",pParas->m_fImpAngleSetting);
	pXmlSierialize->xml_serialize("��ͬ�ں�բ��(��ֵ)","SynAngleSetting","","number",pParas->m_fSynAngleSetting);
	pXmlSierialize->xml_serialize("����������","TestItemName","","string",pParas->m_pszTestItemName);
#else
	pXmlSierialize->xml_serialize(/* "��һ�ι��϶�·�迹(���ʽ)" */g_sLangTxt_Native_first_fault_impAmp.GetString(), "Z1Exp", "","string",pParas->m_pszImpedance[0]);
	pXmlSierialize->xml_serialize(/* "��һ�ι��϶�·�迹��(���ʽ)" */g_sLangTxt_Native_first_fault_impAngAmp.GetString(), "Z1PhExp", "","string",pParas->m_pszImpAngle[0]);
	pXmlSierialize->xml_serialize(/* "�ڶ��ι��϶�·�迹(���ʽ)" */g_sLangTxt_Native_second_fault_impAmp.GetString(), "Z2Exp", "","string",pParas->m_pszImpedance[1]);
	pXmlSierialize->xml_serialize(/* "�ڶ��ι��϶�·�迹��(���ʽ)" */g_sLangTxt_Native_second_fault_impAngAmp.GetString(), "Z2PhExp", "","string",pParas->m_pszImpAngle[1]);
	pXmlSierialize->xml_serialize(/* "ͬ�ڵ�ѹ��ֵ(���ʽ)" */g_sLangTxt_Native_synchronous_VAmpExp.GetString(),"UxInputMagExp","","string",pParas->m_pszUxInput_Mag);
	pXmlSierialize->xml_serialize(/* "ͬ�ڵ�ѹ��λ(���ʽ)" */g_sLangTxt_Native_synchronous_VPhExp.GetString(),"UxInputAngExp","","string",pParas->m_pszUxInput_Ang);
	pXmlSierialize->xml_serialize(/* "�迹��ֵ(��ֵ)" */g_sLangTxt_Native_impedance_Set.GetString(),"ImpdanceSetting","","number",pParas->m_fImpdanceSetting);
	pXmlSierialize->xml_serialize(/* "�迹��(��ֵ)" */g_sLangTxt_Native_ImpedanceAnglesSet.GetString(),"ImpAngleSetting","","number",pParas->m_fImpAngleSetting);
	pXmlSierialize->xml_serialize(/* "��ͬ�ں�բ��(��ֵ)" */g_sLangTxt_Native_Syn_closure_AngSet.GetString(),"SynAngleSetting","","number",pParas->m_fSynAngleSetting);
	pXmlSierialize->xml_serialize(/* "����������" */g_sLangTxt_Native_test_item_name.GetString(),"TestItemName","","string",pParas->m_pszTestItemName);
#endif

	stt_xml_serialize(pParas,pXmlSierialize);
}

void stt_xml_serialize_pnv(tmt_RecloseAccParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize(pParas,pXmlSierialize);
    pXmlSierialize->xml_serialize("����ǰ����","_State1BOut","","number",pParas->m_nState1BOut);
    pXmlSierialize->xml_serialize("����̬����","_State2BOut","","number",pParas->m_nState2BOut);
    pXmlSierialize->xml_serialize("�غ�բ����","_State3BOut","","number",pParas->m_nState3BOut);
    pXmlSierialize->xml_serialize("����ٿ���","_State4BOut","","number",pParas->m_nState4BOut);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize(tmt_RecloseAccResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
}


CSttXmlSerializeBase* stt_xml_serialize(tmt_RecloseAccTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	//stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_ex(&(pTests->m_oRecloseAccParas),  pXmlParas);	//�ļ��Ķ�д
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize_ex(&(pTests->m_oRecloseAccParas),  pXmlParas);	//���Բ����·�
		}
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize(&pTests->m_oRecloseAccResults,  pXmlResults);
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize(&pTests->m_oRecloseAccResults,  pXmlResults);
		}
	}

	return pXmlParas;
}
CSttXmlSerializeBase* stt_xml_serialize(tmt_RecloseAccPnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    //stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize_pnv(&(pTests->m_oRecloseAccParas),  pXmlParas);	//�ļ��Ķ�д
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize_pnv(&(pTests->m_oRecloseAccParas),  pXmlParas);	//���Բ����·�
        }
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize(&pTests->m_oRecloseAccResults,  pXmlResults);
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize(&pTests->m_oRecloseAccResults,  pXmlResults);
        }
    }

    return pXmlParas;
}
