#include "stdafx.h"
#include "tmt_distance_search_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_DistanceSearchParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DistanceSearchParas));
	pParas->init();
}

void stt_init_paras(tmt_DistanceSearchParas_I *pParas)
{
    memset(&pParas, 0, sizeof(tmt_DistanceSearchParas_I));
    pParas->init();
}

void stt_init_results(tmt_DistanceSearchResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DistanceSearchResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_Search(tmt_DistanceSearchParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
	//2022.5.16 caoxc
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��Ŀ����", "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "��", "set", pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("�仯��ʼ�Ƕ�", "BeginValAng", "��", "set",pParas->m_fScanFromAngle);
	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "��", "set", pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("�仯��ֹ�Ƕ�", "EndValAng", "��", "set", pParas->m_fScanToAngle);
	pXmlSierialize->xml_serialize("���Ծ���","Step", "��", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize("��������", "FaultType", "��", "SystemFault", pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("��������ʱ��", "TSetting", "s", "set",pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("��·����", "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("��·��ѹ", "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
 	pXmlSierialize->xml_serialize("���Ϸ���", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);//�����̶�
 	pXmlSierialize->xml_serialize("��������","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);//�����̶�
	pXmlSierialize->xml_serialize("���ⶨֵ", "ValSetting", "��", "set", pParas->m_fSetting[0]);//�迹��ֵ
	pXmlSierialize->xml_serialize("�����迹�Ƕȶ�ֵ", "ValSettingAngle", "��", "set", pParas->m_fSetting[1]);//�迹�Ƕ�
	pXmlSierialize->xml_serialize("������ʽ", "SearchMode", " ", "SearchModePnv", pParas->m_nSearchMode);

	pXmlSierialize->xml_serialize("�������������ʱ��","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
    pXmlSierialize->xml_serialize("���ѹ","UNom","V","number",pParas->m_fUNom);
#else
	pXmlSierialize->xml_serialize(/* "��Ŀ����" */g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "��", "set", pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize(/* "�仯��ʼ�Ƕ�" */g_sLangTxt_Native_change_startangle.GetString(), "BeginValAng", "��", "set",pParas->m_fScanFromAngle);
	pXmlSierialize->xml_serialize(/* "�仯��ֵ" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "��", "set", pParas->m_fScanTo);
	pXmlSierialize->xml_serialize(/* "�仯��ֹ�Ƕ�" */g_sLangTxt_Native_change_endangle.GetString(), "EndValAng", "��", "set", pParas->m_fScanToAngle);
	pXmlSierialize->xml_serialize(/* "���Ծ���" */g_sLangTxt_Native_TestPrecision.GetString(),"Step", "��", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "��", "SystemFault", pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "��������ʱ��" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set",pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "��·����" */g_sLangTxt_Native_ShortCircuit.GetString(), "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "��·��ѹ" */g_sLangTxt_Native_ShortCircuitV.GetString(), "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
 	pXmlSierialize->xml_serialize(/* "���Ϸ���" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);//�����̶�
 	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_FaultProp.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);//�����̶�
	pXmlSierialize->xml_serialize(/* "���ⶨֵ" */g_sLangTxt_Native_UnderTestValue.GetString(), "ValSetting", "��", "set", pParas->m_fSetting[0]);//�迹��ֵ
	pXmlSierialize->xml_serialize(/* "�����迹�Ƕȶ�ֵ" */g_sLangTxt_Native_impedanceAng_measured.GetString(), "ValSettingAngle", "��", "set", pParas->m_fSetting[1]);//�迹�Ƕ�
	pXmlSierialize->xml_serialize(/* "������ʽ" */g_sLangTxt_Native_search_way.GetString(), "SearchMode", " ", "SearchModePnv", pParas->m_nSearchMode);

	pXmlSierialize->xml_serialize(/* "�������������ʱ��" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);
	BOOL bFind = pXmlSierialize->xml_serialize("��̬ʱ��","PrepareTime","s","number",pParas->m_fPrepareTime);//��������ר�ã���һ�ι���ǰʱ��

	if(!bFind)
	{
		pParas->m_fPrepareTime = pParas->m_fPreFaultTime;
	}

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pParas->CalRX_All();
	}
}

void stt_xml_serialize_Search(tmt_DistanceSearchParas_I *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
    stt_xml_serialize_Search((tmt_DistanceSearchParas*)pParas,pXmlSierialize,nBinExNum,nBoutExNum);
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
void stt_xml_serialize_SearchReport(tmt_DistanceSearchParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������","SearchBegin","��","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize("Z�������Ƕ�","SearchBeginAngle","��","number",pParas->m_fSearchBeginAngle);
	pXmlSierialize->xml_serialize("Z������㶯��","SearchBeginAct","��","number",pParas->m_nTripFlagFrom);
	pXmlSierialize->xml_serialize("��ǰֵ","CurrSearchVal","��","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("Z��ǰֵ�Ƕ�","CurrSearchValAngle","��","number",pParas->m_fCurrScanValAngle);
	pXmlSierialize->xml_serialize("�����յ�","SearchEnd","��","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize("Z�����յ�Ƕ�","SearchEndAngle","��","number",pParas->m_fSearchEndAngle);
	pXmlSierialize->xml_serialize("Z�����յ㶯��","SearchEndAct","��","number",pParas->m_nTripFlagTo);
	pXmlSierialize->xml_serialize("�������䳤��","SearchArea","","number",pParas->m_fSearchArea);
#else
	pXmlSierialize->xml_serialize(/* "�������" */g_sLangTxt_Native_SearchStart.GetString(),"SearchBegin","��","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize(/* "Z�������Ƕ�" */g_sLangTxt_Native_Zsearch_startAng.GetString(),"SearchBeginAngle","��","number",pParas->m_fSearchBeginAngle);
	pXmlSierialize->xml_serialize(/* "Z������㶯��" */g_sLangTxt_Native_Zsearch_startAct.GetString(),"SearchBeginAct","��","number",pParas->m_nTripFlagFrom);
	pXmlSierialize->xml_serialize(/* "��ǰֵ" */g_sLangTxt_Native_CurrentValue.GetString(),"CurrSearchVal","��","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize(/* "Z��ǰֵ�Ƕ�" */g_sLangTxt_Native_ZAng_currentVal.GetString(),"CurrSearchValAngle","��","number",pParas->m_fCurrScanValAngle);
	pXmlSierialize->xml_serialize(/* "�����յ�" */g_sLangTxt_Native_SearchEnd.GetString(),"SearchEnd","��","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize(/* "Z�����յ�Ƕ�" */g_sLangTxt_Native_Zsearch_endAng.GetString(),"SearchEndAngle","��","number",pParas->m_fSearchEndAngle);
	pXmlSierialize->xml_serialize(/* "Z�����յ㶯��" */g_sLangTxt_Native_Zsearch_endAct.GetString(),"SearchEndAct","��","number",pParas->m_nTripFlagTo);
	pXmlSierialize->xml_serialize(/* "�������䳤��" */g_sLangTxt_Native_SearchLen.GetString(),"SearchArea","","number",pParas->m_fSearchArea);
#endif

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_Search(tmt_DistanceSearchResults *pResults, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�����迹", "TripZ", "��", "number", pResults->m_fImp);
	pXmlSierialize->xml_serialize("�����迹��", "TripZAngle", "��", "number", pResults->m_fImpAngle);
	pXmlSierialize->xml_serialize("�迹��������", "ActZ", "", "number", pResults->m_nActZ);
#else
	pXmlSierialize->xml_serialize(/* "�����迹" */g_sLangTxt_Native_action_impedance.GetString(), "TripZ", "��", "number", pResults->m_fImp);
	pXmlSierialize->xml_serialize(/* "�����迹��" */g_sLangTxt_Native_action_impedanceAng.GetString(), "TripZAngle", "��", "number", pResults->m_fImpAngle);
	pXmlSierialize->xml_serialize(/* "�迹��������" */g_sLangTxt_Native_Desc_impedance_Act.GetString(), "ActZ", "", "number", pResults->m_nActZ);
#endif

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceSearchTest *pTests, CSttXmlSerializeBase *pXmlSerialize,long nBinExNum,long nBoutExNum)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_Search(&(pTests->m_oDistanceSearchParas), pXmlParas,nBinExNum,nBoutExNum);	//�ļ��Ķ�д
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize_Search(&(pTests->m_oDistanceSearchParas), pXmlParas,nBinExNum,nBoutExNum);	//���Բ����·�
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_Search(&pTests->m_oDistanceSearchResults, pXmlResults,nBinExNum,nBoutExNum);
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize_Search(&pTests->m_oDistanceSearchResults, pXmlResults,nBinExNum,nBoutExNum);
		}
	}

	return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceSearchTest_I *pTests, CSttXmlSerializeBase *pXmlSerialize,long nBinExNum,long nBoutExNum)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize_Search(&(pTests->m_oDistanceSearchParas), pXmlParas,nBinExNum,nBoutExNum);	//�ļ��Ķ�д
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize_Search(&(pTests->m_oDistanceSearchParas), pXmlParas,nBinExNum,nBoutExNum);	//���Բ����·�
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize_Search(&pTests->m_oDistanceSearchResults, pXmlResults,nBinExNum,nBoutExNum);
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize_Search(&pTests->m_oDistanceSearchResults, pXmlResults,nBinExNum,nBoutExNum);
        }
    }

    return pXmlParas;
}
