#include "stdafx.h"
#include "tmt_prim_freq_manu_test.h"
#include "../tmt_system_config.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              
#endif

void stt_init_paras(tmt_PrimFreqManualParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_PrimFreqManualParas));
    pParas->init();
}

void stt_init_results(tmt_PrimFreqManualResult *pResults)
{
    memset(&pResults, 0, sizeof(tmt_PrimFreqManualResult));
    pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_act_rcd(tmt_PrimFreqManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//������¼,���64��,����ʵ�ʶ������,�����ܵĶ�����Ϣ
{
	CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

	if(pXmlActRcddata == NULL)
	{
		return;
	}

	CString strName, strID, strTemp, strTmp2;

#ifdef NOT_USE_XLANGUAGE
	CString str1 = _T("����");
	CString str2 = _T("��");
	CString str3 = _T("�ζ���ʱ��");
#else
	CString str1 = /*_T("����")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("��")*/g_sLangTxt_Native_Number;
	CString str3 = /*_T("�ζ���ʱ��")*/g_sLangTxt_Native_NActionTime;
#endif

	int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

	for(int nIndex = 0; nIndex < nCnt; nIndex++)
	{
		strTemp.Format(_T("%d"), nIndex + 1);

		for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinSwitchCount[nIndex])); nIndexAct++)
		{
			strTmp2.Format(_T("%d"), nIndexAct + 1);
			strName = str1 + strTemp + str2 + strTmp2 + str3;
			strID.Format("Bin%dActCount%d", (nIndex + 1), (nIndexAct + 1));
			pXmlActRcddata->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_frTimeBinAct[nIndex][nIndexAct]);
		}
	}

	if(g_nBinExCount > 0)
	{
		CSttXmlSerializeBase *pXmlActRcdExdata = pXmlSierialize->xml_serialize("ActRcdEx", "ActRcdEx", "ActRcdEx", stt_ParaGroupKey());

		if(pXmlActRcdExdata == NULL)
		{
			return;
		}

		for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
		{
#ifdef NOT_USE_XLANGUAGE
			strTemp.Format(_T("��չ%d"), nIndex + 1);
#else
			strTemp.Format(/*_T("��չ%d")*/g_sLangTxt_Native_extend.GetString(), nIndex + 1);
#endif
			for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinExSwitchCount[nIndex])); nIndexAct++)
			{
				strTmp2.Format(_T("%d"), nIndexAct + 1);
				strName = str1 + strTemp + str2 + strTmp2 + str3;
				strID.Format("BinEx%dActCount%d", (nIndex + 1), (nIndexAct + 1));
				pXmlActRcdExdata->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_frTimeBinExAct[nIndex][nIndexAct]);
			}
		}
	}
}



void stt_xml_serialize(tmt_PrimFreqManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize(pParas, pXmlSierialize, MAX_VOLTAGE_COUNT, MAX_CURRENT_COUNT);
}
void stt_xml_serialize(tmt_PrimFreqManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
{
	/**********����PTU200L��׿*********/
	if(stt_xml_serialize_is_read(pXmlSierialize))
	{
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize_sys_pata("Ua��ֵ", "Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ua��λ", "UaPh", "��", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("UaƵ��", "UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ub��ֵ", "Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ub��λ", "UbPh", "��", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("UbƵ��", "UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Uc��ֵ", "Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Uc��λ", "UcPh", "��", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("UcƵ��", "UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Uap��ֵ", "Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Uap��λ", "UapPh", "��", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("UapƵ��", "UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ubp��ֵ", "Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ubp��λ", "UbpPh", "��", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("UbpƵ��", "UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ucp��ֵ", "Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ucp��λ", "UcpPh", "��", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("UcpƵ��", "UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ia��ֵ", "Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ia��λ", "IaPh", "��", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("IaƵ��", "IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ib��ֵ", "Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ib��λ", "IbPh", "��", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("IbƵ��", "IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ic��ֵ", "Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ic��λ", "IcPh", "��", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("IcƵ��", "IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Iap��ֵ", "Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Iap��λ", "IapPh", "��", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("IapƵ��", "IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ibp��ֵ", "Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ibp��λ", "IbpPh", "��", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("IbpƵ��", "IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Icp��ֵ", "Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Icp��λ", "IcpPh", "��", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("IcpƵ��", "IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#else
		pXmlSierialize->xml_serialize_sys_pata(/*"Ua��ֵ"*/g_sLangTxt_Native_UaAmplitude.GetString(), "Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ua��λ"*/g_sLangTxt_Native_UaPhase.GetString(), "UaPh", "��", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"UaƵ��"*/g_sLangTxt_Native_UaFreq.GetString(), "UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ub��ֵ"*/g_sLangTxt_Native_UbAmplitude.GetString(), "Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ub��λ"*/g_sLangTxt_Native_UbPhase.GetString(), "UbPh", "��", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"UbƵ��"*/g_sLangTxt_Native_UbFreq.GetString(), "UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Uc��ֵ"*/g_sLangTxt_Native_UcAmplitude.GetString(), "Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Uc��λ"*/g_sLangTxt_Native_UcPhase.GetString(), "UcPh", "��", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"UcƵ��"*/g_sLangTxt_Native_UcFreq.GetString(), "UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Uap��ֵ"*/g_sLangTxt_Native_UapAmp.GetString(), "Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Uap��λ"*/g_sLangTxt_Native_UapPhase.GetString(), "UapPh", "��", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"UapƵ��"*/g_sLangTxt_Native_UapFreq.GetString(), "UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ubp��ֵ"*/g_sLangTxt_Native_UbpAmp.GetString(), "Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ubp��λ"*/g_sLangTxt_Native_UbpPhase.GetString(), "UbpPh", "��", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"UbpƵ��"*/g_sLangTxt_Native_UbpFreq.GetString(), "UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ucp��ֵ"*/g_sLangTxt_Native_UcpAmp.GetString(), "Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ucp��λ"*/g_sLangTxt_Native_UcpPhase.GetString(), "UcpPh", "��", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"UcpƵ��"*/g_sLangTxt_Native_UcpFreq.GetString(), "UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ia��ֵ"*/g_sLangTxt_Native_IaAmp.GetString(), "Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ia��λ"*/g_sLangTxt_Native_IaPhase.GetString(), "IaPh", "��", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"IaƵ��"*/g_sLangTxt_Native_IaFreq.GetString(), "IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ib��ֵ"*/g_sLangTxt_Native_IbAmp.GetString(), "Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ib��λ"*/g_sLangTxt_Native_IbPhase.GetString(), "IbPh", "��", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"IbƵ��"*/g_sLangTxt_Native_IbFreq.GetString(), "IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ic��ֵ"*/g_sLangTxt_Native_IcAmp.GetString(), "Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ic��λ"*/g_sLangTxt_Native_IcPhase.GetString(), "IcPh", "��", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"IcƵ��"*/g_sLangTxt_Native_IcFreq.GetString(), "IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Iap��ֵ"*/g_sLangTxt_Native_IapAmp.GetString(), "Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Iap��λ"*/g_sLangTxt_Native_IapPhase.GetString(), "IapPh", "��", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"IapƵ��"*/g_sLangTxt_Native_IapFreq.GetString(), "IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ibp��ֵ"*/g_sLangTxt_Native_IbpAmp.GetString(), "Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ibp��λ"*/g_sLangTxt_Native_IbpPhase.GetString(), "IbpPh", "��", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"IbpƵ��"*/g_sLangTxt_Native_IbpFreq.GetString(), "IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Icp��ֵ"*/g_sLangTxt_Native_IcpAmp.GetString(), "Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Icp��λ"*/g_sLangTxt_Native_IcpPhase.GetString(), "IcpPh", "��", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"IcpƵ��"*/g_sLangTxt_Native_IcpFreq.GetString(), "IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#endif
	}
	//����PsuVm
	if(stt_xml_serialize_is_read(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize_sys_pata("Ua1��ֵ", "_Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ua1��λ", "_UaPh", "��", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("Ua1Ƶ��", "_UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ub1��ֵ", "_Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ub1��λ", "_UbPh", "��", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("Ub1Ƶ��", "_UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Uc1��ֵ", "_Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Uc1��λ", "_UcPh", "��", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("Uc1Ƶ��", "_UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ua2��ֵ", "_Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ua2��λ", "_UapPh", "��", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("Ua2Ƶ��", "_UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Ub2��ֵ", "_Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ub2��λ", "_UbpPh", "��", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("Ub2Ƶ��", "_UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata("Uc2��ֵ", "_Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Uc2��λ", "_UcpPh", "��", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata("Uc2Ƶ��", "_UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);

		char strChabc[4] = "abc";

		CString strName, strID;
		for(int i=0; i<6; i++)
		{
			for(int j=0; j<3; j++)
			{
				strID.Format("_I%c%d",strChabc[j],i+1);
				strName.Format("I%c%d��ֵ",strChabc[j],i+1);
				pXmlSierialize->xml_serialize_sys_pata(strName.GetString(), strID.GetString(), "A", "number", pParas->m_uiCUR[(i*3+j)].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
				strID.Format("_I%c%dPh",strChabc[j],i+1);
				strName.Format("I%c%d��λ",strChabc[j],i+1);
				pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "��", "number", pParas->m_uiCUR[(i*3+j)].Harm[1].fAngle);
				strID.Format("_I%c%dFre",strChabc[j],i+1);
				strName.Format("I%c%dƵ��",strChabc[j],i+1);
				pXmlSierialize->xml_serialize_sys_pata(strName.GetString(), strID.GetString(), "Hz", "number", pParas->m_uiCUR[(i*3+j)].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
			}
		}
	}

	/**********����PTU200L��׿*********/
	//�°����л�,U1~U18,i1~i18
	CString strID;

	if(nVolRsNum > MAX_VOLTAGE_COUNT)
	{
		nVolRsNum = MAX_VOLTAGE_COUNT;
	}

	for(int nIndex = 0; nIndex < nVolRsNum; nIndex++)
	{
		strID.Format(_T("U%d"), nIndex + 1);
		pXmlSierialize->xml_serialize_sys_pata("", strID.GetString(), "V", "number", pParas->m_uiVOL[nIndex].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		strID.Format(_T("U%dPh"), nIndex + 1);
		pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiVOL[nIndex].Harm[1].fAngle);
		strID.Format(_T("U%dFre"), nIndex + 1);
		pXmlSierialize->xml_serialize_sys_pata("", strID.GetString(), "Hz", "number", pParas->m_uiVOL[nIndex].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	}

	if(nCurRsNum > MAX_CURRENT_COUNT)
	{
		nCurRsNum = MAX_CURRENT_COUNT;
	}

	for(int nIndex = 0; nIndex < nCurRsNum; nIndex++)
	{
		strID.Format(_T("I%d"), nIndex + 1);
		pXmlSierialize->xml_serialize_sys_pata("", strID.GetString(), "A", "number", pParas->m_uiCUR[nIndex].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		strID.Format(_T("I%dPh"), nIndex + 1);
		pXmlSierialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiCUR[nIndex].Harm[1].fAngle);
		strID.Format(_T("I%dFre"), nIndex + 1);
		pXmlSierialize->xml_serialize_sys_pata("", strID.GetString(), "Hz", "number", pParas->m_uiCUR[nIndex].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�Ƿ���ֹͣ", "bBinStop", "", "BOOL", pParas->m_bBinStop);
	pXmlSierialize->xml_serialize("�ݱ�ͨ��ѡ��", "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
	pXmlSierialize->xml_serialize("�ݱ�����ѡ��", "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
	pXmlSierialize->xml_serialize("�仯ģʽ", "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
	pXmlSierialize->xml_serialize("�仯ʼֵ", "Start", "", "number", pParas->m_manuGradient.fStart);
	pXmlSierialize->xml_serialize("�仯��ֵ", "End", "", "number", pParas->m_manuGradient.fEnd);
	pXmlSierialize->xml_serialize("�仯����", "Step", "", "number", pParas->m_manuGradient.fStep);
	pXmlSierialize->xml_serialize("ÿ��ʱ��", "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
	pXmlSierialize->xml_serialize("������ʱ", "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	pXmlSierialize->xml_serialize("�仯г������", "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
	pXmlSierialize->xml_serialize("����ͨ������", "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize("�����߼�", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"�Ƿ���ֹͣ"*/g_sLangTxt_Native_YNInputStop.GetString(), "bBinStop", "", "BOOL", pParas->m_bBinStop);
	pXmlSierialize->xml_serialize(/*"�ݱ�ͨ��ѡ��"*/g_sLangTxt_Native_varchannel_select.GetString(), "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
	pXmlSierialize->xml_serialize(/*"�ݱ�����ѡ��"*/g_sLangTxt_Native_vartype_select.GetString(), "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
	pXmlSierialize->xml_serialize(/*"�仯ģʽ"*/g_sLangTxt_Native_change_mode.GetString(), "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
	pXmlSierialize->xml_serialize(/*"�仯ʼֵ"*/g_sLangTxt_Gradient_Init.GetString(), "Start", "", "number", pParas->m_manuGradient.fStart);
	pXmlSierialize->xml_serialize(/*"�仯��ֵ"*/g_sLangTxt_Gradient_Finish.GetString(), "End", "", "number", pParas->m_manuGradient.fEnd);
	pXmlSierialize->xml_serialize(/*"�仯����"*/g_sLangTxt_Gradient_Step.GetString(), "Step", "", "number", pParas->m_manuGradient.fStep);
	pXmlSierialize->xml_serialize(/*"ÿ��ʱ��"*/g_sLangTxt_Native_step_time.GetString(), "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
	pXmlSierialize->xml_serialize(/*"������ʱ"*/g_sLangTxt_Native_trigger_delay.GetString(), "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	pXmlSierialize->xml_serialize(/*"�仯г������"*/g_sLangTxt_Native_VarHarmonicNum.GetString(), "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
	pXmlSierialize->xml_serialize(/*"����ͨ������"*/g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize(/*"�����߼�"*/g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�Ƿ�����", "_bLock", "", "BOOL", pParas->m_bLockChanged);
	pXmlSierialize->xml_serialize("�Ƿ��Զ��ݱ�", "_bAuto", "", "BOOL", pParas->m_bAuto);
	pXmlSierialize->xml_serialize("", "ResultAddBin", "", "BOOL", pParas->m_bResultAddBin);//�Զ�������
#else
	pXmlSierialize->xml_serialize(/*"�Ƿ�����"*/g_sLangTxt_Native_YN_locked.GetString(), "_bLock", "", "BOOL", pParas->m_bLockChanged);
	pXmlSierialize->xml_serialize(/*"�Ƿ��Զ��ݱ�"*/g_sLangTxt_Native_YN_autoevo.GetString(), "_bAuto", "", "BOOL", pParas->m_bAuto);
#endif
// 	if(stt_xml_serialize_is_read(pXmlSierialize))
// 	{
// 		stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
// 		stt_xml_serialize(&pParas->m_oFt3Pub[0], pXmlSierialize);
// 		stt_xml_serialize(&pParas->m_o2MOnePortPub[0], pXmlSierialize);
// 	}

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("����ʱ��(s)", "OutputTime", " ", "number", pParas->m_fOutPutTime);
#else
	pXmlSierialize->xml_serialize(/*"����ʱ��(s)"*/g_sLangTxt_Native_max_outputtime.GetString(), "OutputTime", " ", "number", pParas->m_fOutPutTime);
#endif
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("��������ʱ��","TSet","s","float",pParas->m_fTimeSet);
	pXmlSierialize->xml_serialize("��ѹ��������ֵ","USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize("������������ֵ","ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize("��λ��������ֵ","AngleSet","��","float",pParas->m_fAngleSet);
	pXmlSierialize->xml_serialize("Ƶ����������ֵ","HzSet","Hz","float",pParas->m_fHzSet);
	pXmlSierialize->xml_serialize("����ϵ������ֵ","RetCoefSet","","float",pParas->m_fRetCoefSet);


	pXmlSierialize->xml_serialize("����ʱ��ֵ�������","Ttrip_AbsErr","","float",pParas->m_fTimeValue_AbsErr);
	pXmlSierialize->xml_serialize("����ʱ��ֵ������","Ttrip_RelErr","","float",pParas->m_fTimeValue_RelErr);
	pXmlSierialize->xml_serialize("����ʱ������ж��߼�","TimeValue_ErrorLogic","","number",pParas->m_nTimeValue_ErrorLogic);
	pXmlSierialize->xml_serialize("��ѹ����ֵ�������","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ������","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ����ж��߼�","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("��������ֵ�������","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("��������ֵ������","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("��������ֵ����ж��߼�","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("��λ����ֵ�������","AngleActVal_AbsErr","","float",pParas->m_fAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize("��λ����ֵ������","AngleActVal_RelErr","","float",pParas->m_fAngleActVal_RelErr);
	pXmlSierialize->xml_serialize("��λ����ֵ����ж��߼�","AngleActVal_ErrorLogic","","number",pParas->m_nAngleActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ�������","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ������","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ����ж��߼�","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
	pXmlSierialize->xml_serialize("����ϵ���������","RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize("����ϵ��������","RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize("����ϵ������ж��߼�","RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
#else
	pXmlSierialize->xml_serialize(/*"��������ʱ��"*/g_sLangTxt_Native_acttuning_time.GetString(),"TSet","s","float",pParas->m_fTimeSet);
	pXmlSierialize->xml_serialize(/*"��ѹ��������ֵ"*/g_sLangTxt_Native_VolSetActValue.GetString(),"USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize(/*"������������ֵ"*/g_sLangTxt_Native_CurSetActValue.GetString(),"ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize(/*"��λ��������ֵ"*/g_sLangTxt_Native_PhSetActValue.GetString(),"AngleSet","��","float",pParas->m_fAngleSet);
	pXmlSierialize->xml_serialize(/*"Ƶ����������ֵ"*/g_sLangTxt_Native_FreqSetActValue.GetString(),"HzSet","Hz","float",pParas->m_fHzSet);
	pXmlSierialize->xml_serialize(/*"����ϵ������ֵ"*/g_sLangTxt_Native_FeedbackCoefSettingVal.GetString(),"RetCoefSet","","float",pParas->m_fRetCoefSet);


	pXmlSierialize->xml_serialize(/*"����ʱ��ֵ�������"*/g_sLangTxt_Native_ActTimeValueAbsErr.GetString(),"Ttrip_AbsErr","","float",pParas->m_fTimeValue_AbsErr);
	pXmlSierialize->xml_serialize(/*"����ʱ��ֵ������"*/g_sLangTxt_Native_ActTimeValueRelErr.GetString(),"Ttrip_RelErr","","float",pParas->m_fTimeValue_RelErr);
	pXmlSierialize->xml_serialize(/*"����ʱ������ж��߼�"*/g_sLangTxt_Native_ActTimeValueErrLogic.GetString(),"TimeValue_ErrorLogic","","number",pParas->m_nTimeValue_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"��ѹ����ֵ�������"*/g_sLangTxt_Native_VActionValueAbsErr.GetString(),"UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"��ѹ����ֵ������"*/g_sLangTxt_Native_VActionValueRelErr.GetString(),"UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"��ѹ����ֵ����ж��߼�"*/g_sLangTxt_Native_VActionValueErrLogic.GetString(),"UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"��������ֵ�������"*/g_sLangTxt_Native_IActionValueAbsErr.GetString(),"IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"��������ֵ������"*/g_sLangTxt_Native_IActionValueRelErr.GetString(),"IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"��������ֵ����ж��߼�"*/g_sLangTxt_Native_IActionValueErrLogic.GetString(),"IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"��λ����ֵ�������"*/g_sLangTxt_Native_PhaseActValueAbsErr.GetString(),"AngleActVal_AbsErr","","float",pParas->m_fAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"��λ����ֵ������"*/g_sLangTxt_Native_PhaseActValueRelErr.GetString(),"AngleActVal_RelErr","","float",pParas->m_fAngleActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"��λ����ֵ����ж��߼�"*/g_sLangTxt_Native_PhaseActValueErrLogic.GetString(),"AngleActVal_ErrorLogic","","number",pParas->m_nAngleActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"Ƶ�ʶ���ֵ�������"*/g_sLangTxt_Native_FreqPickAbsErr.GetString(),"HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
	pXmlSierialize->xml_serialize(/*"Ƶ�ʶ���ֵ������"*/g_sLangTxt_Native_FreqPickRelErr.GetString(),"HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
	pXmlSierialize->xml_serialize(/*"Ƶ�ʶ���ֵ����ж��߼�"*/g_sLangTxt_Native_FreqPickErrDetectLogic.GetString(),"HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
	pXmlSierialize->xml_serialize(/*"����ϵ���������"*/g_sLangTxt_Native_CoefficientAbsErr.GetString(),"RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize(/*"����ϵ��������"*/g_sLangTxt_Native_CoefficientRelErr.GetString(),"RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize(/*"����ϵ������ж��߼�"*/g_sLangTxt_Native_CoefficientErrLogic.GetString(),"RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
#endif

	pXmlSierialize->xml_serialize("���ģʽ", "OutputType", "", "number", pParas->m_nOutputType);
	pXmlSierialize->xml_serialize("�����ź�����", "SpeedPulseType", "", "number", pParas->m_nSpeedPulseType);
	pXmlSierialize->xml_serialize("������", "PulseWidth", "ms", "number", pParas->m_nPulseWidth);
	pXmlSierialize->xml_serialize("���ֵѡ��", "PeakToPeakTypeIndex", "", "number", pParas->m_nPeakToPeakTypeIndex);
	pXmlSierialize->xml_serialize("����Ƶ��", "PulseFreqHz", "HZ", "number", pParas->m_fPulseFreqHz);
	pXmlSierialize->xml_serialize("IDc1", "IDc1", "mA", "number", pParas->m_frCurrentDc[0]);
	pXmlSierialize->xml_serialize("IDc2", "IDc2", "mA", "number", pParas->m_frCurrentDc[1]);
	pXmlSierialize->xml_serialize("ֱ���ź�Դģʽ", "DcOutputMode", "", "number", pParas->m_nDcOutputMode);
	pXmlSierialize->xml_serialize("ֱ���ź����ֵ", "DcOutputValue", "", "number", pParas->m_fDcOutputValue);
	pXmlSierialize->xml_serialize("����Ƶ����Сֵ", "FrequencyMinHz", "mA", "number", pParas->m_fGridFrequencyMinHz);
	pXmlSierialize->xml_serialize("����Ƶ�����ֵ", "FrequencyMaxHz", "mA", "number", pParas->m_fGridFrequencyMaxHz);
	pXmlSierialize->xml_serialize("�����ת����Сֵ", "GenSpeedMinRpm", "", "number", pParas->m_fGenSpeedMinRpm);
	pXmlSierialize->xml_serialize("�����ת�����ֵ", "GenSpeedMaxRpm", "", "number", pParas->m_fGenSpeedMaxRpm);

}

void stt_xml_serialize(tmt_PrimFreqManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize, BOOL bBinStatus)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�������", "TripFlag", "", "number", pResults->m_nTripFlag);
	pXmlSierialize->xml_serialize("����ʱ��", "TripTime", "", "number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("����ֵ", "ActValue", "", "number", pResults->m_fActValue);
	pXmlSierialize->xml_serialize("����ֵ", "ReturnValue", "", "number", pResults->m_fReturnValue);
	pXmlSierialize->xml_serialize("����ϵ��", "ReturnCoef", "", "number", pResults->m_fReturnCoef);
	pXmlSierialize->xml_serialize("����ʱ��", "ReturnTime", "", "number", pResults->m_fReturnTime);
#else
	pXmlSierialize->xml_serialize(/*"�������"*/g_sLangTxt_Native_action_mark.GetString(), "TripFlag", "", "number", pResults->m_nTripFlag);
	pXmlSierialize->xml_serialize(/*"����ʱ��"*/g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/*"����ֵ"*/g_sLangTxt_State_ActionValue.GetString(), "ActValue", "", "number", pResults->m_fActValue);
	pXmlSierialize->xml_serialize(/*"����ֵ"*/g_sLangTxt_Native_ReturnValue.GetString(), "ReturnValue", "", "number", pResults->m_fReturnValue);
	pXmlSierialize->xml_serialize(/*"����ϵ��"*/g_sLangTxt_Gradient_ReCoefficient.GetString(), "ReturnCoef", "", "number", pResults->m_fReturnCoef);
	pXmlSierialize->xml_serialize(/*"����ʱ��"*/g_sLangTxt_Native_ReturnTime.GetString(), "ReturnTime", "", "number", pResults->m_fReturnTime);
#endif
	CString strName, strID, strTemp;
#ifdef NOT_USE_XLANGUAGE
	CString str1 = _T("����");
	CString str2 = _T("���״̬");
#else
	CString str1 = /*_T("����")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("���״̬")*/g_sLangTxt_Native_result_status;
#endif
	int nCnt = get_xml_serialize_binary_count(pXmlSierialize);
	for(int nIndex = 0; nIndex < nCnt; nIndex++)
	{
		strTemp.Format(_T("%d"), nIndex + 1);
		strName = str1 + strTemp + str2;
		strID.Format("StateBin%d", (nIndex + 1));
		pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_nrBinSwitchCount[nIndex]);
	}

	if(g_nBinExCount > 0)
	{
		CSttXmlSerializeBase *pXmlStateBinEx = pXmlSierialize->xml_serialize("StateBinEx", "StateBinEx", "StateBinEx", stt_ParaGroupKey());

		if(pXmlStateBinEx != NULL)
		{
			for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
			{
#ifdef NOT_USE_XLANGUAGE
				strTemp.Format(_T("��չ%d"), nIndex + 1);
#else
				strTemp.Format(/*_T("��չ%d")*/g_sLangTxt_Native_extend.GetString(), nIndex + 1);
#endif
				strName = str1 + strTemp + str2;
				strID.Format("StateBinEx%d", (nIndex + 1));
				pXmlStateBinEx->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_nrBinExSwitchCount[nIndex]);
			}
		}
	}

	stt_xml_serialize_act_rcd(pResults, pXmlSierialize);

#ifdef _PSX_QT_LINUX_
#ifndef _STT_NOT_IN_TEST_SERVER_
	if(!bBinStatus)
	{
		return;
	}

	CSttXmlSerializeBase *pXmlBinaryVal = pXmlSierialize->xml_serialize("BinaryVal", "BinaryVal", "BinaryVal", stt_ParaGroupKey());

	BI_STATUS *pBIStatus = &CSttDeviceBase::g_pSttDeviceBase->m_oBIStatus;
	for(int nIndex = 0; nIndex < nCnt; nIndex++)
	{
		strID.Format("Bin%d", (nIndex + 1));
		pXmlBinaryVal->xml_serialize("", strID.GetString(), "", "number", pBIStatus->m_nBin[nIndex]);
	}

	for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
	{
		strID.Format("BinEx%d", (nIndex + 1));
		pXmlBinaryVal->xml_serialize("", strID.GetString(), "", "number", pBIStatus->m_nBinEx[nIndex]);
	}
#endif
#endif
}


#ifdef _PSX_QT_LINUX_
#ifndef _STT_NOT_IN_TEST_SERVER_
	#include "../../SttDevice/SttDeviceBase.h"
#endif
#endif

#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_PrimFreqManuTest()
{
    tmt_PrimFreqManualTest oManualTest;
    oManualTest.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oManualTest.m_oManuParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("PrimFreqManualTestDemo.xml");
//   pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

CSttXmlSerializeBase *stt_xml_serialize(tmt_PrimFreqManualTest *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
{
//	stt_xml_serialize((PTMT_PARAS_HEAD)pParas, pXmlSierialize);
    CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if(pXmlParas  != NULL)
    {
        stt_xml_serialize(&pParas->m_oManuParas, pXmlParas, nVolRsNum, nCurRsNum);
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if(pXmlResults  != NULL)
    {
        stt_xml_serialize(&pParas->m_oManuResult, pXmlResults);
    }

    return pXmlParas;
}

