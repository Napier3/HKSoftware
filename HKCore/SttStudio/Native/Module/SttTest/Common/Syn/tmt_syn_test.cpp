#include "stdafx.h"
#include "tmt_syn_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_SynParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_SynParas));
	pParas->init();
}

void stt_init_results(tmt_SynResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_SynResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_common(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//����ֵ
	pXmlSierialize->xml_serialize("��ǰ��", "LAngle", "��", "number", pParas->m_fLAngle);
	pXmlSierialize->xml_serialize("��ǰʱ��", "LTime", "s", "number", pParas->m_fLTime);
	pXmlSierialize->xml_serialize("����ѹ��", "dVzd", "V", "number", pParas->m_fdVzd);
	pXmlSierialize->xml_serialize("����Ƶ��", "dFzd", "Hz", "number", pParas->m_fdFzd);
	pXmlSierialize->xml_serialize("��ѹ����", "Ut", "s", "number", pParas->m_fUt);
	pXmlSierialize->xml_serialize("��Ƶ����", "Ft", "s", "number", pParas->m_fFt);

	//ͨ�ò���
	pXmlSierialize->xml_serialize("ϵͳ����ѹ", "Us", "V", "number", pParas->m_fVs_Mag);
	pXmlSierialize->xml_serialize("ϵͳ��Ƶ��", "Fs", "Hz", "number", pParas->m_fVs_Fre);
	pXmlSierialize->xml_serialize("��������ѹ", "Ug", "V", "number", pParas->m_fVg_Std);
	pXmlSierialize->xml_serialize("��ѹ����", "UgConnectDef", "", "SynVolDef", pParas->m_nVolDefType);
	pXmlSierialize->xml_serialize("�ο���", "Vref", "", "SynVolRef", pParas->m_nRefVolType);

    pXmlSierialize->xml_serialize("��������֮��ǲ�ӵ�����", "WindAngs", "", "number", pParas->m_nWindAngs);
    pXmlSierialize->xml_serialize("������λ��", "PhaseDiff", "", "number", pParas->m_fPhaseDiff);
	pXmlSierialize->xml_serialize("��ѹ�����߷�ʽ", "TansConnect", "", "SynTConnMode", pParas->m_nTransConnMode);
	pXmlSierialize->xml_serialize("���ͬ��ʱ��", "Tmax", "", "number", pParas->m_fMaxSynTime);

	//������
	pXmlSierialize->xml_serialize("����4�����ʽ", "KStart", "", "SynBoutType", pParas->m_nBoutType);
	pXmlSierialize->xml_serialize("����4����ʱ��", "CloseTime", "", "number", pParas->m_fBoutKeepTime);


	pXmlSierialize->xml_serialize("�������ѹ", "UgStart", "", "number", pParas->m_fVg_Mag);
	pXmlSierialize->xml_serialize("������Ƶ��", "FgStart", "", "number", pParas->m_fVg_Fre);


    pXmlSierialize->xml_serialize("ͬ���ź�", "_BinSyn", "", "number", pParas->m_binIn_Syn);
    pXmlSierialize->xml_serialize("��ѹ�ź�", "_BinIncV", "", "number", pParas->m_binIn_IncV);
    pXmlSierialize->xml_serialize("��Ƶ�ź�", "_BinIncF", "", "number", pParas->m_binIn_IncF);
    pXmlSierialize->xml_serialize("��ѹ�ź�", "_BinDecV", "", "number", pParas->m_binIn_DecV);
    pXmlSierialize->xml_serialize("��Ƶ�ź�", "_BinDecF", "", "number", pParas->m_binIn_DecF);

	CString strName,strID;
	for(int nIndex=0;nIndex<8;nIndex++)
	{
		strName.Format(_T("����%d"),nIndex+1);
		strID.Format(_T("_Bout%d"),nIndex+1);
		pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "long", pParas->m_binOut[nIndex]);
	}

#else
	//����ֵ
	pXmlSierialize->xml_serialize( /* "��ǰ��" */g_sLangTxt_LeadingAngle.GetString() , "LAngle", "��", "number", pParas->m_fLAngle);
	pXmlSierialize->xml_serialize( /* "��ǰʱ��"  */g_sLangTxt_LeadingTime.GetString(), "LTime", "s", "number", pParas->m_fLTime);
	pXmlSierialize->xml_serialize( /* "����ѹ��"  */g_sLangTxt_Allow_VolDifference.GetString(), "dVzd", "V", "number", pParas->m_fdVzd);
	pXmlSierialize->xml_serialize( /* "����Ƶ��" */g_sLangTxt_Allow_FreqDifference.GetString() , "dFzd", "Hz", "number", pParas->m_fdFzd);
	pXmlSierialize->xml_serialize( /* "��ѹ����" */g_sLangTxt_Vol_ReguPeriod.GetString() , "Ut", "s", "number", pParas->m_fUt);
	pXmlSierialize->xml_serialize( /* "��Ƶ����" */g_sLangTxt_Freq_ReguPeriod.GetString() , "Ft", "s", "number", pParas->m_fFt);

	//ͨ�ò���
	pXmlSierialize->xml_serialize(/* "ϵͳ����ѹ" */g_sLangTxt_System_Rated_Voltage.GetString() , "Us", "V", "number", pParas->m_fVs_Mag);
	pXmlSierialize->xml_serialize(/* "ϵͳ��Ƶ��" */g_sLangTxt_System_Rated_Frequency.GetString() , "Fs", "Hz", "number", pParas->m_fVs_Fre);
	pXmlSierialize->xml_serialize(/* "��������ѹ" */g_sLangTxt_Grid_Rated_Voltage.GetString() , "Ug", "V", "number", pParas->m_fVg_Std);
	pXmlSierialize->xml_serialize(/* "��ѹ����" */g_sLangTxt_Native_volDefinition1.GetString() , "UgConnectDef", "", "SynVolDef", pParas->m_nVolDefType);
	pXmlSierialize->xml_serialize(/* "�ο���" */g_sLangTxt_Native_refphase.GetString() , "Vref", "", "SynVolRef", pParas->m_nRefVolType);

	pXmlSierialize->xml_serialize(/* "��ѹ�����߷�ʽ" */g_sLangTxt_Native_transfConnection.GetString() , "TansConnect", "", "SynTConnMode", pParas->m_nTransConnMode);
	pXmlSierialize->xml_serialize(/* "���ͬ��ʱ��" */g_sLangTxt_Native_maxSyncTime.GetString() , "Tmax", "", "number", pParas->m_fMaxSynTime);

	//������
	pXmlSierialize->xml_serialize(/* "����4�����ʽ" */g_sLangTxt_Out4_Mode.GetString() , "KStart", "", "SynBoutType", pParas->m_nBoutType);
	pXmlSierialize->xml_serialize(/* "����4����ʱ��" */g_sLangTxt_Native_breaker4HoldTime.GetString() , "CloseTime", "", "number", pParas->m_fBoutKeepTime);


	pXmlSierialize->xml_serialize(/* "�������ѹ" */g_sLangTxt_Native_Grid_Vol.GetString(), "UgStart", "", "number", pParas->m_fVg_Mag);
	pXmlSierialize->xml_serialize(/* "������Ƶ��" */g_sLangTxt_Grid_FreqHZ.GetString(), "FgStart", "", "number", pParas->m_fVg_Fre);


    pXmlSierialize->xml_serialize(/* "ͬ���ź�" */g_sLangTxt_Native_syncSignal.GetString(), "_BinSyn", "", "number", pParas->m_binIn_Syn);
    pXmlSierialize->xml_serialize(/* "��ѹ�ź�" */g_sLangTxt_Native_boostSignal.GetString(), "_BinIncV", "", "number", pParas->m_binIn_IncV);
    pXmlSierialize->xml_serialize(/* "��Ƶ�ź�" */g_sLangTxt_Native_boostFreqSignal.GetString(), "_BinIncF", "", "number", pParas->m_binIn_IncF);
    pXmlSierialize->xml_serialize(/* "��ѹ�ź�" */g_sLangTxt_Native_reducePresSignal.GetString(), "_BinDecV", "", "number", pParas->m_binIn_DecV);
    pXmlSierialize->xml_serialize(/* "��Ƶ�ź�" */g_sLangTxt_Native_reduceFreqSignal.GetString(), "_BinDecF", "", "number", pParas->m_binIn_DecF);

	CString strName,strID;
	for(int nIndex=0;nIndex<8;nIndex++)
	{
		strName.Format(/* _T("����%d") */g_sLangTxt_Native_OutPut.GetString(),nIndex+1);
		strID.Format(_T("_Bout%d"),nIndex+1);
		pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "long", pParas->m_binOut[nIndex]);
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_ActVol(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������ѹ�仯����", "UgMagStep", "", "number", pParas->m_fDvStep);

	stt_xml_serialize_common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "�������ѹ�仯����" */g_sLangTxt_Native_GvolChangeStep.GetString(), "UgMagStep", "", "number", pParas->m_fDvStep);

	stt_xml_serialize_common(pParas,pXmlSierialize);
#endif
}

void stt_xml_serialize_ActVolEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������ѹ(���ʽ)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("������Ƶ��(���ʽ)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);
	pXmlSierialize->xml_serialize("�������ѹ�仯����(���ʽ)", "UgMagStepExp", "", "string",  pParas->m_pszDvStep);
	stt_xml_serialize_ActVol(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "�������ѹ(���ʽ)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "������Ƶ��(���ʽ)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);
	pXmlSierialize->xml_serialize(/* "�������ѹ�仯����(���ʽ)" */g_sLangTxt_Native_GvolChangeStepExp.GetString(), "UgMagStepExp", "", "string",  pParas->m_pszDvStep);
	stt_xml_serialize_ActVol(pParas,pXmlSierialize);
#endif
}

void stt_xml_serialize_ActFreq(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("������Ƶ�ʱ仯����", "UgFreqStep", "", "number", pParas->m_fDfStep);

    stt_xml_serialize_common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "������Ƶ�ʱ仯����" */g_sLangTxt_Native_GfreqChangeStep.GetString(), "UgFreqStep", "", "number", pParas->m_fDfStep);

    stt_xml_serialize_common(pParas,pXmlSierialize);
#endif
}

void stt_xml_serialize_ActFreqEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������ѹ(���ʽ)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("������Ƶ��(���ʽ)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);
	pXmlSierialize->xml_serialize("������Ƶ�ʱ仯����(���ʽ)", "UgFreqStepExp", "", "string", pParas->m_pszDfStep);

	stt_xml_serialize_ActFreq(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "�������ѹ(���ʽ)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "������Ƶ��(���ʽ)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);
	pXmlSierialize->xml_serialize(/* "������Ƶ�ʱ仯����(���ʽ)" */g_sLangTxt_Native_GfreqChangeStepExp.GetString(), "UgFreqStepExp", "", "string", pParas->m_pszDfStep);

	stt_xml_serialize_ActFreq(pParas,pXmlSierialize);
#endif

}


void stt_xml_serialize_LeadAng(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{

	stt_xml_serialize_common(pParas,pXmlSierialize);
}

void stt_xml_serialize_LeadAngEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������ѹ(���ʽ)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("������Ƶ��(���ʽ)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_LeadAng(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "�������ѹ(���ʽ)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "������Ƶ��(���ʽ)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_LeadAng(pParas,pXmlSierialize);
#endif

}


void stt_xml_serialize_AutoAdj(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ����", "DvDt", "", "number", pParas->m_fdVg_dt);
	pXmlSierialize->xml_serialize("Ƶ�ʻ���", "DfDt", "", "number", pParas->m_fdFg_dt);

    stt_xml_serialize_common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ����" */g_sLangTxt_Native_VoltSlip.GetString(), "DvDt", "", "number", pParas->m_fdVg_dt);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���" */g_sLangTxt_Native_FreqSlip.GetString(), "DfDt", "", "number", pParas->m_fdFg_dt);

    stt_xml_serialize_common(pParas,pXmlSierialize);
#endif

}

void stt_xml_serialize_AutoAdjEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������ѹ(���ʽ)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("������Ƶ��(���ʽ)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	pXmlSierialize->xml_serialize("��ѹ����(���ʽ)", "DvDtExp", "", "string", pParas->m_pszdVg_dt);
	pXmlSierialize->xml_serialize("Ƶ�ʻ���(���ʽ)", "DfDtExp", "", "string", pParas->m_pszdFg_dt);

	stt_xml_serialize_AutoAdj(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "�������ѹ(���ʽ)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "������Ƶ��(���ʽ)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	pXmlSierialize->xml_serialize(/* "��ѹ����(���ʽ)" */g_sLangTxt_Native_VoltSlip.GetString(), "DvDtExp", "", "string", pParas->m_pszdVg_dt);
	pXmlSierialize->xml_serialize(/* "Ƶ�ʻ���(���ʽ)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(), "DfDtExp", "", "string", pParas->m_pszdFg_dt);

	stt_xml_serialize_AutoAdj(pParas,pXmlSierialize);
#endif

}

void stt_xml_serialize_AdjVolCycle(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_common(pParas,pXmlSierialize);
}

void stt_xml_serialize_AdjVolCycleEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������ѹ(���ʽ)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("������Ƶ��(���ʽ)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_AdjVolCycle(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "�������ѹ(���ʽ)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "������Ƶ��(���ʽ)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_AdjVolCycle(pParas,pXmlSierialize);
#endif

}

void stt_xml_serialize_AdjFreqCycle(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_common(pParas,pXmlSierialize);
}

void stt_xml_serialize_AdjFreqCycleEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������ѹ(���ʽ)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("������Ƶ��(���ʽ)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_AdjFreqCycle(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "�������ѹ(���ʽ)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "������Ƶ��(���ʽ)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_AdjFreqCycle(pParas,pXmlSierialize);
#endif

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_ActVol(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
 	pXmlSierialize->xml_serialize("��ѹ�߽�ֵ", "VolBordValue", "", "number",pResults->m_fVolBordValue);
	pXmlSierialize->xml_serialize("ѹ��", "VolDeltValue", "", "number",pResults->m_fVolDelt);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
 	pXmlSierialize->xml_serialize(/* "��ѹ�߽�ֵ" */g_sLangTxt_Vol_BoundValue.GetString(), "VolBordValue", "", "number",pResults->m_fVolBordValue);
	pXmlSierialize->xml_serialize(/* "ѹ��" */g_sLangTxt_VolDif.GetString(), "VolDeltValue", "", "number",pResults->m_fVolDelt);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_ActFreq(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("Ƶ�ʱ߽�ֵ", "FreqBordValue", "", "number",pResults->m_fFreqBordValue);
	pXmlSierialize->xml_serialize("Ƶ��", "FreqDeltValue", "", "number",pResults->m_fFreqDelt);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "Ƶ�ʱ߽�ֵ" */g_sLangTxt_Freq_BoundValue.GetString(), "FreqBordValue", "", "number",pResults->m_fFreqBordValue);
	pXmlSierialize->xml_serialize(/* "Ƶ��" */g_sLangTxt_FreqDif.GetString(), "FreqDeltValue", "", "number",pResults->m_fFreqDelt);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_LeadAng(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("��ǰ��", "LeaderAngle", "", "number",pResults->m_fLeaderAngle);
    pXmlSierialize->xml_serialize("��ǰʱ��", "LeaderTime", "", "number",pResults->m_fLeaderTime);
    pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "��ǰ��" */g_sLangTxt_LeadingAngle.GetString(), "LeaderAngle", "", "number",pResults->m_fLeaderAngle);
    pXmlSierialize->xml_serialize(/* "��ǰʱ��" */g_sLangTxt_LeadingTime.GetString(), "LeaderTime", "", "number",pResults->m_fLeaderTime);
    pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_AutoAdj(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("ѹ��", "VolDeltValue", "", "number",pResults->m_fVolDelt);
	pXmlSierialize->xml_serialize("Ƶ��", "FreqDeltValue", "", "number",pResults->m_fFreqDelt);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "ѹ��" */g_sLangTxt_VolDif.GetString(), "VolDeltValue", "", "number",pResults->m_fVolDelt);
	pXmlSierialize->xml_serialize(/* "Ƶ��" */g_sLangTxt_FreqDif.GetString(), "FreqDeltValue", "", "number",pResults->m_fFreqDelt);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_AdjVolCycle(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��ѹ����", "AdjVolCycle", "", "number",pResults->m_fUAdjTime);
	pXmlSierialize->xml_serialize("��ѹ����", "AdjVolWidth", "", "number",pResults->m_fUAdjWidth);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "��ѹ����" */g_sLangTxt_Vol_ReguPeriod.GetString(), "AdjVolCycle", "", "number",pResults->m_fUAdjTime);
	pXmlSierialize->xml_serialize(/* "��ѹ����" */g_sLangTxt_Native_RegulatePulseWidth.GetString(), "AdjVolWidth", "", "number",pResults->m_fUAdjWidth);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}


void stt_xml_serialize_AdjFreqCycle(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��Ƶ����", "AdjFreqCycle", "", "number",pResults->m_fFAdjTime);
	pXmlSierialize->xml_serialize("��Ƶ����", "AdjFreqWidth", "", "number",pResults->m_fFAdjWidth);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "��Ƶ����" */g_sLangTxt_Freq_ReguPeriod.GetString(), "AdjFreqCycle", "", "number",pResults->m_fFAdjTime);
	pXmlSierialize->xml_serialize(/* "��Ƶ����" */g_sLangTxt_Native_RegulatePulseWidth.GetString(), "AdjFreqWidth", "", "number",pResults->m_fFAdjWidth);
	pXmlSierialize->xml_serialize(/* "��������" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_SynActVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

 	if (pXmlParas != NULL)
 	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynActVoltageTest) == 0)
		{
			stt_xml_serialize_ActVolEx(&(pTests->m_oSynParas), pXmlParas);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynActFreqTest) == 0
                 /*|| strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynLeadAngTest) == 0*/)
		{
			stt_xml_serialize_ActFreqEx(&(pTests->m_oSynParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynAutoAdjTest) == 0)
		{
			stt_xml_serialize_AutoAdjEx(&(pTests->m_oSynParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynAdjVolTest) == 0)
		{
			stt_xml_serialize_AdjVolCycleEx(&(pTests->m_oSynParas), pXmlParas);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynAdjFreqTest) == 0)
		{
			stt_xml_serialize_AdjFreqCycleEx(&(pTests->m_oSynParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynLeadAngTest) == 0)
		{
			stt_xml_serialize_LeadAngEx(&(pTests->m_oSynParas), pXmlParas);
		}

 	}
 
 	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());
 
 	if (pXmlResults != NULL)
 	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynActVoltageTest) == 0)
		{
			stt_xml_serialize_ActVol(&pTests->m_oSynResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynActFreqTest) == 0)
		{
			stt_xml_serialize_ActFreq(&pTests->m_oSynResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynAutoAdjTest) == 0)
		{
			stt_xml_serialize_AutoAdj(&pTests->m_oSynResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynAdjVolTest) == 0)
		{
			stt_xml_serialize_AdjVolCycle(&pTests->m_oSynResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynAdjFreqTest) == 0)
		{
			stt_xml_serialize_AdjFreqCycle(&pTests->m_oSynResults,  pXmlResults);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_SynLeadAngTest) == 0)
        {
            stt_xml_serialize_LeadAng(&pTests->m_oSynResults,  pXmlResults);
        }
 	}

	return pXmlParas;
}
