#include "stdafx.h"
#include "tmt_manu_test.h"
#include "tmt_system_config.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

void stt_init_paras(tmt_ManualParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_ManualParas));
    pParas->init();
}

void stt_init_results(tmt_ManualResult *pResults)
{
    memset(&pResults, 0, sizeof(tmt_ManualResult));
    pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///
void stt_xml_serialize_dc(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    int bDC = 0;

    if(pXmlSierialize->get_serialize_mode() == STT_XML_SERIALIZE_MODE_READ)
    {
#ifdef NOT_USE_XLANGUAGE
        pXmlSierialize->xml_serialize("�Ƿ���ֱ��ģʽ���", "bDC", "", "BOOL", bDC);
#else
		        pXmlSierialize->xml_serialize(/*"�Ƿ���ֱ��ģʽ���"*/g_sLangTxt_Native_DCOutputMode.GetString(), "bDC", "", "BOOL", bDC);
#endif
        pParas->setDC(bDC);
    }
//     else//zhouhj 2024.1.3 ��дģʽʱ,�˴��ظ���,�ڵ��øýӿ�ǰ,�Ѿ�д��,�˴��ظ���
//     {
//         if(pParas->m_bDC)
//         {
//             bDC = 1;
//         }
// 
// #ifdef NOT_USE_XLANGUAGE
//         pXmlSierialize->xml_serialize("�Ƿ���ֱ��ģʽ���", "bDC", "", "BOOL", bDC);
// #else
// 		        pXmlSierialize->xml_serialize(/*"�Ƿ���ֱ��ģʽ���"*/g_sLangTxt_Native_DCOutputMode.GetString(), "bDC", "", "BOOL", bDC);
// #endif
//     }
}

void stt_xml_serialize_Harm(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
{
    CSttXmlSerializeBase *pHarmSelSerialize = NULL;
#ifdef NOT_USE_XLANGUAGE
    pHarmSelSerialize = pXmlSierialize->xml_serialize("г������", "Harm", "HarmSel", stt_ParaGroupKey());
#else
	    pHarmSelSerialize = pXmlSierialize->xml_serialize(/*"г������"*/g_sLangTxt_Native_HarmSuperposition.GetString(), "Harm", "HarmSel", stt_ParaGroupKey());
#endif

    if(pHarmSelSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pHarmSelSerialize->xml_serialize("г��ѡ��", "HarmSel", "", "number", pParas->m_nSelHarm);
    pHarmSelSerialize->xml_serialize("г������", "HarmIndex", "", "number", pParas->m_nHarmIndex);
#else
	pHarmSelSerialize->xml_serialize(/*"г��ѡ��"*/g_sLangTxt_Native_HarmSelection.GetString(), "HarmSel", "", "number", pParas->m_nSelHarm);
	pHarmSelSerialize->xml_serialize(/*"г������"*/g_sLangTxt_Native_harmonicOrder.GetString(), "HarmIndex", "", "number", pParas->m_nHarmIndex);
#endif

    if(pParas->m_nSelHarm == 0)
    {
        return;
    }

    if((pParas->m_nHarmIndex < 0) || (pParas->m_nHarmIndex >= MAX_HARM_COUNT))
    {
        return;
    }

    CString strID;

    if(nVolRsNum > MAX_VOLTAGE_COUNT)
    {
        nVolRsNum = MAX_VOLTAGE_COUNT;
    }

    for(int nIndex = 0; nIndex < nVolRsNum; nIndex++)
    {
        strID.Format(_T("U%d_Harm%d"), nIndex + 1, pParas->m_nHarmIndex);
        pHarmSelSerialize->xml_serialize_sys_pata("", strID.GetString(), "V", "number", pParas->m_uiVOL[nIndex].Harm[pParas->m_nHarmIndex].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        strID.Format(_T("U%dPh_Harm%d"), nIndex + 1, pParas->m_nHarmIndex);
        pHarmSelSerialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiVOL[nIndex].Harm[pParas->m_nHarmIndex].fAngle);
        pParas->m_uiVOL[nIndex].Harm[pParas->m_nHarmIndex].fFreq = pParas->m_uiVOL[nIndex].Harm[1].fFreq * pParas->m_nHarmIndex;
    }

    if(nCurRsNum > MAX_CURRENT_COUNT)
    {
        nCurRsNum = MAX_CURRENT_COUNT;
    }

    for(int nIndex = 0; nIndex < nCurRsNum; nIndex++)
    {
        strID.Format(_T("I%d_Harm%d"), nIndex + 1, pParas->m_nHarmIndex);
        pHarmSelSerialize->xml_serialize_sys_pata("", strID.GetString(), "A", "number", pParas->m_uiCUR[nIndex].Harm[pParas->m_nHarmIndex].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
        strID.Format(_T("I%dPh_Harm%d"), nIndex + 1, pParas->m_nHarmIndex);
        pHarmSelSerialize->xml_serialize("", strID.GetString(), "��", "number", pParas->m_uiCUR[nIndex].Harm[pParas->m_nHarmIndex].fAngle);
        pParas->m_uiCUR[nIndex].Harm[pParas->m_nHarmIndex].fFreq = pParas->m_uiCUR[nIndex].Harm[1].fFreq * pParas->m_nHarmIndex;
    }
}

void stt_xml_serialize_MU(tmt_MuParas *pMuParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pMuParasSerialize = NULL;
#ifdef NOT_USE_XLANGUAGE
    pMuParasSerialize = pXmlSierialize->xml_serialize("�ϲ���Ԫ", "MU", "MU", stt_ParaGroupKey());
#else
	    pMuParasSerialize = pXmlSierialize->xml_serialize(/*"�ϲ���Ԫ"*/g_sLangTxt_Native_MrgUnit.GetString(), "MU", "MU", stt_ParaGroupKey());
#endif

    if(pMuParasSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pMuParasSerialize->xml_serialize("�㷨ѡ��(0:��ֵ��  1:ͬ����)", "AlgorithmType", "", "number", pMuParas->nAlgorithmType);
    pMuParasSerialize->xml_serialize("PPS����(0:��������Ч  1:�½�����Ч 2:��PPS)", "PPS_SetType", "", "number", pMuParas->nPPS_SetType);
    pMuParasSerialize->xml_serialize("����ѹ(��Ư����)", "StdVoltage", "", "number", pMuParas->fUn);
    pMuParasSerialize->xml_serialize("������(��Ư����)", "StdCurrent", "", "number", pMuParas->fIn);
    pMuParasSerialize->xml_serialize("��ʱ���Ȳ���ʱͬ��ʱ��(��λ:s)", "SynTime", "", "number", pMuParas->nSynTime);
//    pMuParasSerialize->xml_serialize("��PPSʱ��ʱ����ֵ(��ʱ��ʱ������,��λ:��s)", "DelayCompens_NoPPS", "", "number", pMuParas->fDelayCompens_NoPPS);
	pMuParasSerialize->xml_serialize("�Ƿ�ʹ���Զ��屨�����(�ϲ���Ԫ)","UseSetRpt","","number",pMuParas->m_nUseSetRpt);
	pMuParasSerialize->xml_serialize("�Զ��屨����Դ���(�ϲ���Ԫ)","MUTestMaxTestCount","","number",pMuParas->m_nMaxTestCount);
	pMuParasSerialize->xml_serialize("ÿ�β���ʱ��(�ϲ���Ԫ,��λ��)","TimeOneCount","","number",pMuParas->m_fTimeOneCount);
#else
	pMuParasSerialize->xml_serialize(/*"�㷨ѡ��(0:��ֵ��  1:ͬ����)"*/g_sLangTxt_Native_AlgorithmSelection.GetString(), "AlgorithmType", "", "number", pMuParas->nAlgorithmType);
	pMuParasSerialize->xml_serialize(/*"PPS����(0:��������Ч  1:�½�����Ч 2:��PPS)"*/g_sLangTxt_Native_PPSConfiguration.GetString(), "PPS_SetType", "", "number", pMuParas->nPPS_SetType);
	pMuParasSerialize->xml_serialize(/*"����ѹ(��Ư����)"*/g_sLangTxt_Native_RatedV_Phase_ZeroDriftCalc.GetString(), "StdVoltage", "", "number", pMuParas->fUn);
	pMuParasSerialize->xml_serialize(/*"������(��Ư����)"*/g_sLangTxt_Native_RatedI_Phase_ZeroDriftCalc.GetString(), "StdCurrent", "", "number", pMuParas->fIn);
	pMuParasSerialize->xml_serialize(/*"��ʱ���Ȳ���ʱͬ��ʱ��(��λ:s)"*/g_sLangTxt_Native_SyncDur_TAT.GetString(), "SynTime", "", "number", pMuParas->nSynTime);
	//pMuParasSerialize->xml_serialize(/*"��PPSʱ��ʱ����ֵ(��ʱ��ʱ������,��λ:��s)"*/g_sLangTxt_Native_DelayComp_NoPPS.GetString(), "DelayCompens_NoPPS", "", "number", pMuParas->fDelayCompens_NoPPS);
	pMuParasSerialize->xml_serialize(/*"�Ƿ�ʹ���Զ��屨�����(�ϲ���Ԫ)"*/g_sLangTxt_Native_CustomRepCnt_Use_MU.GetString(),"UseSetRpt","","number",pMuParas->m_nUseSetRpt);
	pMuParasSerialize->xml_serialize(/*"�Զ��屨����Դ���(�ϲ���Ԫ)"*/g_sLangTxt_Native_CustomRepTestCnt_MU.GetString(),"MUTestMaxTestCount","","number",pMuParas->m_nMaxTestCount);
	pMuParasSerialize->xml_serialize(/*"ÿ�β���ʱ��(�ϲ���Ԫ,��λ��)"*/g_sLangTxt_Native_TestDurPerTest_MU_sec.GetString(),"TimeOneCount","","number",pMuParas->m_fTimeOneCount);
#endif
}

void stt_xml_serialize_MuTime(tmt_MuTimeResult *pMuTimeRlt, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pMuTimeSerialize = NULL;
#ifdef NOT_USE_XLANGUAGE
    pMuTimeSerialize = pXmlSierialize->xml_serialize("MUʱ����Խ��", "MuTime", "MuTime", stt_ParaGroupKey());
#else
    pMuTimeSerialize = pXmlSierialize->xml_serialize(/*"MUʱ����Խ��"*/g_sLangTxt_Native_MUTimeTestResults.GetString(), "MuTime", "MuTime", stt_ParaGroupKey());
#endif
    if(pMuTimeSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pMuTimeSerialize->xml_serialize("�Ѳ���ʱ��", "HasUsingTime", "", "number", pMuTimeRlt->m_fHasUsingTime);
//	pMuTimeSerialize->xml_serialize("��ǰ���ʱ��","CurrErrTime","","number",pMuTimeRlt->m_fCurrErrTime);
    pMuTimeSerialize->xml_serialize("������ʱ��", "MaxErrTime", "", "number", pMuTimeRlt->m_fMaxErrTime);
    pMuTimeSerialize->xml_serialize("��С���ʱ��", "MinErrTime", "", "number", pMuTimeRlt->m_fMinErrTime);
    pMuTimeSerialize->xml_serialize("ƽ�����ʱ��", "AverageErrTime", "", "number", pMuTimeRlt->m_fAverageErrTime);
    pMuTimeSerialize->xml_serialize("ʱ�侫�Ȳ��Խ��", "MUTimeResult", "", "number", pMuTimeRlt->m_nTimeTestResult);
#else
	pMuTimeSerialize->xml_serialize(/*"�Ѳ���ʱ��"*/g_sLangTxt_Native_TestedDur.GetString(), "HasUsingTime", "", "number", pMuTimeRlt->m_fHasUsingTime);
	//	pMuTimeSerialize->xml_serialize("��ǰ���ʱ��","CurrErrTime","","number",pMuTimeRlt->m_fCurrErrTime);
	pMuTimeSerialize->xml_serialize(/*"������ʱ��"*/g_sLangTxt_Native_MaxErrTime.GetString(), "MaxErrTime", "", "number", pMuTimeRlt->m_fMaxErrTime);
	pMuTimeSerialize->xml_serialize(/*"��С���ʱ��"*/g_sLangTxt_Native_MinErrTime.GetString(), "MinErrTime", "", "number", pMuTimeRlt->m_fMinErrTime);
	pMuTimeSerialize->xml_serialize(/*"ƽ�����ʱ��"*/g_sLangTxt_Native_AvgErrTime.GetString(), "AverageErrTime", "", "number", pMuTimeRlt->m_fAverageErrTime);
	pMuTimeSerialize->xml_serialize(/*"ʱ�侫�Ȳ��Խ��"*/g_sLangTxt_Native_TimeAccTestResults.GetString(), "MUTimeResult", "", "number", pMuTimeRlt->m_nTimeTestResult);
#endif
}

// void stt_xml_serialize_Aging(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
// {
// 	int bAging = 0;
// 	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
// 	{
// 		pXmlSierialize->xml_serialize("�Ƿ��ϻ�����", "bAging", "", "BOOL", bAging);
// 		pParas->m_bAging = bAging;
// 	}
// 	else
// 	{
// 		if (pParas->m_bAging)
// 		{
// 			bAging = 1;
// 		}
// 		pXmlSierialize->xml_serialize("�Ƿ��ϻ�����", "bAging", "", "BOOL", bAging);
// 	}
// }

// void stt_xml_serialize_Lock(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
// {
// 	int bLock = 0;
// 	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
// 	{
// 		pXmlSierialize->xml_serialize("�Ƿ�����", "_bLock", "", "BOOL", bLock);
// 		pParas->m_bLockChanged = bLock;
// 	}
// 	else
// 	{
// 		if (pParas->m_bLockChanged)
// 		{
// 			bLock = 1;
// 		}
// 		pXmlSierialize->xml_serialize("�Ƿ�����", "_bLock", "", "BOOL", bLock);
// 	}
// }

// void stt_xml_serialize_Auto(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
// {
// 	int bAuto = 0;
// 	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
// 	{
// 		pXmlSierialize->xml_serialize("�Ƿ��Զ��ݱ�", "_bAuto", "", "BOOL", bAuto);
// 		pParas->m_bAuto = bAuto;
// 	}
// 	else
// 	{
// 		if (pParas->m_bAuto)
// 		{
// 			bAuto = 1;
// 		}
// 		pXmlSierialize->xml_serialize("�Ƿ��Զ��ݱ�", "_bAuto", "", "BOOL", bAuto);
// 	}
// }

void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize(pParas, pXmlSierialize, MAX_VOLTAGE_COUNT, MAX_CURRENT_COUNT);
}

void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
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
    pXmlSierialize->xml_serialize("���Թ������(0:��ͨ�ֶ�����1:MU���Ȳ���2:MU��Ư����)", "FuncType", "", "number", pParas->m_nFuncType);
    pXmlSierialize->xml_serialize("�Ƿ���ֹͣ", "bBinStop", "", "BOOL", pParas->m_bBinStop);
//	pXmlSierialize->xml_serialize("������ʱ","fOverload","s","number",pParas->m_fOverloadDelaytime);
    pXmlSierialize->xml_serialize("�Ƿ���ֱ��ģʽ���", "bDC", "", "BOOL", pParas->m_bDC);
    pXmlSierialize->xml_serialize("�Ƿ��ϻ�����", "bAging", "", "BOOL", pParas->m_bAging);
    pXmlSierialize->xml_serialize("����ֱ������", "fCurAux", "mA", "number", pParas->m_fCurAux);
    pXmlSierialize->xml_serialize("����ֱ����ѹ", "_UdcAux", "V", "number", pParas->m_fVolAux);
    pXmlSierialize->xml_serialize("�ݱ�ͨ��ѡ��", "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize("�ݱ�����ѡ��", "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
    pXmlSierialize->xml_serialize("�仯ģʽ", "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
    pXmlSierialize->xml_serialize("�仯ʼֵ", "Start", "", "number", pParas->m_manuGradient.fStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "End", "", "number", pParas->m_manuGradient.fEnd);
    pXmlSierialize->xml_serialize("�仯����", "Step", "", "number", pParas->m_manuGradient.fStep);
    pXmlSierialize->xml_serialize("ÿ��ʱ��", "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
    pXmlSierialize->xml_serialize("������ʱ", "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	// pXmlSierialize->xml_serialize("�仯г������", "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
	pXmlSierialize->xml_serialize("����ͨ������", "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize("�����߼�", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"���Թ������(0:��ͨ�ֶ�����1:MU���Ȳ���2:MU��Ư����)"*/g_sLangTxt_Native_TestFuncCategory.GetString(), "FuncType", "", "number", pParas->m_nFuncType);
	pXmlSierialize->xml_serialize(/*"�Ƿ���ֹͣ"*/g_sLangTxt_Native_YNInputStop.GetString(), "bBinStop", "", "BOOL", pParas->m_bBinStop);
	//	pXmlSierialize->xml_serialize("������ʱ","fOverload","s","number",pParas->m_fOverloadDelaytime);
	pXmlSierialize->xml_serialize(/*"�Ƿ���ֱ��ģʽ���"*/g_sLangTxt_Native_DCOutputMode.GetString(), "bDC", "", "BOOL", pParas->m_bDC);
	pXmlSierialize->xml_serialize(/*"�Ƿ��ϻ�����"*/g_sLangTxt_Native_YNaging_test.GetString(), "bAging", "", "BOOL", pParas->m_bAging);
	pXmlSierialize->xml_serialize(/*"����ֱ������"*/g_sLangTxt_Native_AuxiDCI.GetString(), "fCurAux", "mA", "number", pParas->m_fCurAux);
	pXmlSierialize->xml_serialize(/*"����ֱ����ѹ"*/g_sLangTxt_Native_AuxiDCV.GetString(), "_UdcAux", "V", "number", pParas->m_fVolAux);
	pXmlSierialize->xml_serialize(/*"�ݱ�ͨ��ѡ��"*/g_sLangTxt_Native_varchannel_select.GetString(), "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
	pXmlSierialize->xml_serialize(/*"�ݱ�����ѡ��"*/g_sLangTxt_Native_vartype_select.GetString(), "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
	pXmlSierialize->xml_serialize(/*"�仯ģʽ"*/g_sLangTxt_Native_change_mode.GetString(), "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
	pXmlSierialize->xml_serialize(/*"�仯ʼֵ"*/g_sLangTxt_Gradient_Init.GetString(), "Start", "", "number", pParas->m_manuGradient.fStart);
	pXmlSierialize->xml_serialize(/*"�仯��ֵ"*/g_sLangTxt_Gradient_Finish.GetString(), "End", "", "number", pParas->m_manuGradient.fEnd);
	pXmlSierialize->xml_serialize(/*"�仯����"*/g_sLangTxt_Gradient_Step.GetString(), "Step", "", "number", pParas->m_manuGradient.fStep);
	pXmlSierialize->xml_serialize(/*"ÿ��ʱ��"*/g_sLangTxt_Native_step_time.GetString(), "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
	pXmlSierialize->xml_serialize(/*"������ʱ"*/g_sLangTxt_Native_trigger_delay.GetString(), "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	// pXmlSierialize->xml_serialize(/*"�仯г������"*/g_sLangTxt_Native_VarHarmonicNum.GetString(), "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
	pXmlSierialize->xml_serialize(/*"����ͨ������"*/g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize(/*"�����߼�"*/g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    //Ex
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);
    stt_xml_serialize_dc(pParas, pXmlSierialize);
//	stt_xml_serialize_Aging(pParas,pXmlSierialize);  zhouhj 20210828 �ظ����л�
//	stt_xml_serialize_Lock(pParas,pXmlSierialize);
//	stt_xml_serialize_Auto(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("�Ƿ�����", "_bLock", "", "BOOL", pParas->m_bLockChanged);
    pXmlSierialize->xml_serialize("�Ƿ��Զ��ݱ�", "_bAuto", "", "BOOL", pParas->m_bAuto);
	pXmlSierialize->xml_serialize("", "ResultAddBin", "", "BOOL", pParas->m_bResultAddBin);//�Զ�������
#else
	pXmlSierialize->xml_serialize(/*"�Ƿ�����"*/g_sLangTxt_Native_YN_locked.GetString(), "_bLock", "", "BOOL", pParas->m_bLockChanged);
	pXmlSierialize->xml_serialize(/*"�Ƿ��Զ��ݱ�"*/g_sLangTxt_Native_YN_autoevo.GetString(), "_bAuto", "", "BOOL", pParas->m_bAuto);
#endif
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
        stt_xml_serialize(&pParas->m_oFt3Pub[0], pXmlSierialize);
        stt_xml_serialize(&pParas->m_o2MOnePortPub[0], pXmlSierialize);
    }

    stt_xml_serialize_Harm(pParas, pXmlSierialize, nVolRsNum, nCurRsNum); //����г��
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����ʱ��(s)", "OutputTime", " ", "number", pParas->m_fOutPutTime);
#else
	    pXmlSierialize->xml_serialize(/*"����ʱ��(s)"*/g_sLangTxt_Native_max_outputtime.GetString(), "OutputTime", " ", "number", pParas->m_fOutPutTime);
#endif
//	pXmlSierialize->xml_serialize("��ʼ����ʱ���ͱ���", "UploadRpt_Started"," ","number",pParas->m_nUploadRpt_Started);

    if(pParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)
    {
        stt_xml_serialize_MU(&pParas->m_oMuParas, pXmlSierialize); // �ϲ���Ԫ����
    }

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
}

void stt_xml_serialize_act_rcd(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//������¼,���64��,����ʵ�ʶ������,�����ܵĶ�����Ϣ
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

#ifdef _PSX_QT_LINUX_
#ifndef _STT_NOT_IN_TEST_SERVER_
	#include "../../SttDevice/SttDeviceBase.h"
#endif
#endif

void stt_xml_serialize(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize, BOOL bBinStatus)
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
    stt_xml_serialize_MuTime(&pResults->m_oMuTimeRlt, pXmlSierialize);

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

void stt_xml_serialize_binary_out_Pnv(tmt_BinaryOut *pbOut, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����1״̬", "_BO01", "", "DOutputState", pbOut[0].nState);
    pXmlSierialize->xml_serialize("����2״̬", "_BO02", "", "DOutputState", pbOut[1].nState);
    pXmlSierialize->xml_serialize("����3״̬", "_BO03", "", "DOutputState", pbOut[2].nState);
    pXmlSierialize->xml_serialize("����4״̬", "_BO04", "", "DOutputState", pbOut[3].nState);
    pXmlSierialize->xml_serialize("����5״̬", "_BO05", "", "DOutputState", pbOut[4].nState);
    pXmlSierialize->xml_serialize("����6״̬", "_BO06", "", "DOutputState", pbOut[5].nState);
    pXmlSierialize->xml_serialize("����7״̬", "_BO07", "", "DOutputState", pbOut[6].nState);
    pXmlSierialize->xml_serialize("����8״̬", "_BO08", "", "DOutputState", pbOut[7].nState);
#else
	pXmlSierialize->xml_serialize(/*"����1״̬"*/g_sLangTxt_Out1_Situation.GetString(), "_BO01", "", "DOutputState", pbOut[0].nState);
	pXmlSierialize->xml_serialize(/*"����2״̬"*/g_sLangTxt_Out2_Situation.GetString(), "_BO02", "", "DOutputState", pbOut[1].nState);
	pXmlSierialize->xml_serialize(/*"����3״̬"*/g_sLangTxt_Out3_Situation.GetString(), "_BO03", "", "DOutputState", pbOut[2].nState);
	pXmlSierialize->xml_serialize(/*"����4״̬"*/g_sLangTxt_Out4_Situation.GetString(), "_BO04", "", "DOutputState", pbOut[3].nState);
	pXmlSierialize->xml_serialize(/*"����5״̬"*/g_sLangTxt_Out5_Situation.GetString(), "_BO05", "", "DOutputState", pbOut[4].nState);
	pXmlSierialize->xml_serialize(/*"����6״̬"*/g_sLangTxt_Out6_Situation.GetString(), "_BO06", "", "DOutputState", pbOut[5].nState);
	pXmlSierialize->xml_serialize(/*"����7״̬"*/g_sLangTxt_Out7_Situation.GetString(), "_BO07", "", "DOutputState", pbOut[6].nState);
	pXmlSierialize->xml_serialize(/*"����8״̬"*/g_sLangTxt_Out8_Situation.GetString(), "_BO08", "", "DOutputState", pbOut[7].nState);
#endif
}

void stt_xml_serialize_12u12i_pnv(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize_sys_pata("Ua��ֵ", "_Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ua��λ", "_UaPh", "��", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UaƵ��", "_UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq, STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ub��ֵ", "_Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ub��λ", "_UbPh", "��", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UbƵ��", "_UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uc��ֵ", "_Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uc��λ", "_UcPh", "��", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UcƵ��", "_UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uap��ֵ", "_Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uap��λ", "_UapPh", "��", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UapƵ��", "_UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ubp��ֵ", "_Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ubp��λ", "_UbpPh", "��", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UbpƵ��", "_UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ucp��ֵ", "_Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ucp��λ", "_UcpPh", "��", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UcpƵ��", "_UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uas��ֵ", "_Uas", "V", "number", pParas->m_uiVOL[6].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uas��λ", "_UasPh", "��", "number", pParas->m_uiVOL[6].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UasƵ��", "_UasFre", "Hz", "number", pParas->m_uiVOL[6].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ubs��ֵ", "_Ubs", "V", "number", pParas->m_uiVOL[7].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ubs��λ", "_UbsPh", "��", "number", pParas->m_uiVOL[7].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UbsƵ��", "_UbsFre", "Hz", "number", pParas->m_uiVOL[7].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ucs��ֵ", "_Ucs", "V", "number", pParas->m_uiVOL[8].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ucs��λ", "_UcsPh", "��", "number", pParas->m_uiVOL[8].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UcsƵ��", "_UcsFre", "Hz", "number", pParas->m_uiVOL[8].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uat��ֵ", "_Uat", "V", "number", pParas->m_uiVOL[9].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uat��λ", "_UatPh", "��", "number", pParas->m_uiVOL[9].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UatƵ��", "_UatFre", "Hz", "number", pParas->m_uiVOL[9].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ubt��ֵ", "_Ubt", "V", "number", pParas->m_uiVOL[10].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ubt��λ", "_UbtPh", "��", "number", pParas->m_uiVOL[10].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UbtƵ��", "_UbtFre", "Hz", "number", pParas->m_uiVOL[10].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uct��ֵ", "_Uct", "V", "number", pParas->m_uiVOL[11].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uct��λ", "_UctPh", "��", "number", pParas->m_uiVOL[11].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("UctƵ��", "_UctFre", "Hz", "number", pParas->m_uiVOL[11].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ia��ֵ", "_Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ia��λ", "_IaPh", "��", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IaƵ��", "_IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ib��ֵ", "_Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ib��λ", "_IbPh", "��", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IbƵ��", "_IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ic��ֵ", "_Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ic��λ", "_IcPh", "��", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IcƵ��", "_IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Iap��ֵ", "_Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Iap��λ", "_IapPh", "��", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IapƵ��", "_IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ibp��ֵ", "_Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ibp��λ", "_IbpPh", "��", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IbpƵ��", "_IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Icp��ֵ", "_Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Icp��λ", "_IcpPh", "��", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IcpƵ��", "_IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ias��ֵ", "_Ias", "A", "number", pParas->m_uiCUR[6].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ias��λ", "_IasPh", "��", "number", pParas->m_uiCUR[6].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IasƵ��", "_IasFre", "Hz", "number", pParas->m_uiCUR[6].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ibs��ֵ", "_Ibs", "A", "number", pParas->m_uiCUR[7].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ibs��λ", "_IbsPh", "��", "number", pParas->m_uiCUR[7].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IbsƵ��", "_IbsFre", "Hz", "number", pParas->m_uiCUR[7].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ics��ֵ", "_Ics", "A", "number", pParas->m_uiCUR[8].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ics��λ", "_IcsPh", "��", "number", pParas->m_uiCUR[8].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IcsƵ��", "_IcsFre", "Hz", "number", pParas->m_uiCUR[8].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Iat��ֵ", "_Iat", "A", "number", pParas->m_uiCUR[9].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Iat��λ", "_IatPh", "��", "number", pParas->m_uiCUR[9].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IatƵ��", "_IatFre", "Hz", "number", pParas->m_uiCUR[9].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ibt��ֵ", "_Ibt", "A", "number", pParas->m_uiCUR[10].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ibt��λ", "_IbtPh", "��", "number", pParas->m_uiCUR[10].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IbtƵ��", "_IbtFre", "Hz", "number", pParas->m_uiCUR[10].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ict��ֵ", "_Ict", "A", "number", pParas->m_uiCUR[11].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ict��λ", "_IctPh", "��", "number", pParas->m_uiCUR[11].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("IctƵ��", "_IctFre", "Hz", "number", pParas->m_uiCUR[11].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#else
	pXmlSierialize->xml_serialize_sys_pata(/*"Ua��ֵ"*/g_sLangTxt_Native_UaAmplitude.GetString(), "_Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ua��λ"*/g_sLangTxt_Native_UaPhase.GetString(), "_UaPh", "��", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UaƵ��"*/g_sLangTxt_Native_UaFreq.GetString(), "_UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ub��ֵ"*/g_sLangTxt_Native_UbAmplitude.GetString(), "_Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ub��λ"*/g_sLangTxt_Native_UbPhase.GetString(), "_UbPh", "��", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UbƵ��"*/g_sLangTxt_Native_UbFreq.GetString(), "_UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uc��ֵ"*/g_sLangTxt_Native_UcAmplitude.GetString(), "_Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uc��λ"*/g_sLangTxt_Native_UcPhase.GetString(), "_UcPh", "��", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UcƵ��"*/g_sLangTxt_Native_UcFreq.GetString(), "_UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uap��ֵ"*/g_sLangTxt_Native_UapAmp.GetString(), "_Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uap��λ"*/g_sLangTxt_Native_UapPhase.GetString(), "_UapPh", "��", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UapƵ��"*/g_sLangTxt_Native_UapFreq.GetString(), "_UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ubp��ֵ"*/g_sLangTxt_Native_UbpAmp.GetString(), "_Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ubp��λ"*/g_sLangTxt_Native_UbpPhase.GetString(), "_UbpPh", "��", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UbpƵ��"*/g_sLangTxt_Native_UbpFreq.GetString(), "_UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ucp��ֵ"*/g_sLangTxt_Native_UcpAmp.GetString(), "_Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ucp��λ"*/g_sLangTxt_Native_UcpPhase.GetString(), "_UcpPh", "��", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UcpƵ��"*/g_sLangTxt_Native_UcpFreq.GetString(), "_UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uas��ֵ"*/g_sLangTxt_Native_UasAmp.GetString(), "_Uas", "V", "number", pParas->m_uiVOL[6].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uas��λ"*/g_sLangTxt_Native_UasPhase.GetString(), "_UasPh", "��", "number", pParas->m_uiVOL[6].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UasƵ��"*/g_sLangTxt_Native_UasFreq.GetString(), "_UasFre", "Hz", "number", pParas->m_uiVOL[6].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ubs��ֵ"*/g_sLangTxt_Native_UbsAmp.GetString(), "_Ubs", "V", "number", pParas->m_uiVOL[7].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ubs��λ"*/g_sLangTxt_Native_UbsPhase.GetString(), "_UbsPh", "��", "number", pParas->m_uiVOL[7].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UbsƵ��"*/g_sLangTxt_Native_UbsFreq.GetString(), "_UbsFre", "Hz", "number", pParas->m_uiVOL[7].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ucs��ֵ"*/g_sLangTxt_Native_UcsAmp.GetString(), "_Ucs", "V", "number", pParas->m_uiVOL[8].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ucs��λ"*/g_sLangTxt_Native_UcsPhase.GetString(), "_UcsPh", "��", "number", pParas->m_uiVOL[8].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UcsƵ��"*/g_sLangTxt_Native_UcsFreq.GetString(), "_UcsFre", "Hz", "number", pParas->m_uiVOL[8].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uat��ֵ"*/g_sLangTxt_Native_UatAmp.GetString(), "_Uat", "V", "number", pParas->m_uiVOL[9].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uat��λ"*/g_sLangTxt_Native_UatPhase.GetString(), "_UatPh", "��", "number", pParas->m_uiVOL[9].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UatƵ��"*/g_sLangTxt_Native_UatFreq.GetString(), "_UatFre", "Hz", "number", pParas->m_uiVOL[9].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ubt��ֵ"*/g_sLangTxt_Native_UbtAmp.GetString(), "_Ubt", "V", "number", pParas->m_uiVOL[10].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ubt��λ"*/g_sLangTxt_Native_UbtPhase.GetString(), "_UbtPh", "��", "number", pParas->m_uiVOL[10].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UbtƵ��"*/g_sLangTxt_Native_UbtFreq.GetString(), "_UbtFre", "Hz", "number", pParas->m_uiVOL[10].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uct��ֵ"*/g_sLangTxt_Native_UctAmp.GetString(), "_Uct", "V", "number", pParas->m_uiVOL[11].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uct��λ"*/g_sLangTxt_Native_UctPhase.GetString(), "_UctPh", "��", "number", pParas->m_uiVOL[11].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"UctƵ��"*/g_sLangTxt_Native_UctFreq.GetString(), "_UctFre", "Hz", "number", pParas->m_uiVOL[11].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ia��ֵ"*/g_sLangTxt_Native_IaAmp.GetString(), "_Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ia��λ"*/g_sLangTxt_Native_IaPhase.GetString(), "_IaPh", "��", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IaƵ��"*/g_sLangTxt_Native_IaFreq.GetString(), "_IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ib��ֵ"*/g_sLangTxt_Native_IbAmp.GetString(), "_Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ib��λ"*/g_sLangTxt_Native_IbPhase.GetString(), "_IbPh", "��", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IbƵ��"*/g_sLangTxt_Native_IbFreq.GetString(), "_IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ic��ֵ"*/g_sLangTxt_Native_IcAmp.GetString(), "_Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ic��λ"*/g_sLangTxt_Native_IcPhase.GetString(), "_IcPh", "��", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IcƵ��"*/g_sLangTxt_Native_IcFreq.GetString(), "_IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Iap��ֵ"*/g_sLangTxt_Native_IapAmp.GetString(), "_Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Iap��λ"*/g_sLangTxt_Native_IapPhase.GetString(), "_IapPh", "��", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IapƵ��"*/g_sLangTxt_Native_IapFreq.GetString(), "_IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ibp��ֵ"*/g_sLangTxt_Native_IbpAmp.GetString(), "_Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ibp��λ"*/g_sLangTxt_Native_IbpPhase.GetString(), "_IbpPh", "��", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IbpƵ��"*/g_sLangTxt_Native_IbpFreq.GetString(), "_IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Icp��ֵ"*/g_sLangTxt_Native_IcpAmp.GetString(), "_Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Icp��λ"*/g_sLangTxt_Native_IcpPhase.GetString(), "_IcpPh", "��", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IcpƵ��"*/g_sLangTxt_Native_IcpFreq.GetString(), "_IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ias��ֵ"*/g_sLangTxt_Native_IasAmp.GetString(), "_Ias", "A", "number", pParas->m_uiCUR[6].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ias��λ"*/g_sLangTxt_Native_IasPhase.GetString(), "_IasPh", "��", "number", pParas->m_uiCUR[6].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IasƵ��"*/g_sLangTxt_Native_IasFreq.GetString(), "_IasFre", "Hz", "number", pParas->m_uiCUR[6].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ibs��ֵ"*/g_sLangTxt_Native_IbsAmp.GetString(), "_Ibs", "A", "number", pParas->m_uiCUR[7].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ibs��λ"*/g_sLangTxt_Native_IbsPhase.GetString(), "_IbsPh", "��", "number", pParas->m_uiCUR[7].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IbsƵ��"*/g_sLangTxt_Native_IbsFreq.GetString(), "_IbsFre", "Hz", "number", pParas->m_uiCUR[7].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ics��ֵ"*/g_sLangTxt_Native_IcsAmp.GetString(), "_Ics", "A", "number", pParas->m_uiCUR[8].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ics��λ"*/g_sLangTxt_Native_IcsPhase.GetString(), "_IcsPh", "��", "number", pParas->m_uiCUR[8].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IcsƵ��"*/g_sLangTxt_Native_IcsFreq.GetString(), "_IcsFre", "Hz", "number", pParas->m_uiCUR[8].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Iat��ֵ"*/g_sLangTxt_Native_IatAmp.GetString(), "_Iat", "A", "number", pParas->m_uiCUR[9].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Iat��λ"*/g_sLangTxt_Native_IatPhase.GetString(), "_IatPh", "��", "number", pParas->m_uiCUR[9].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IatƵ��"*/g_sLangTxt_Native_IatFreq.GetString(), "_IatFre", "Hz", "number", pParas->m_uiCUR[9].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ibt��ֵ"*/g_sLangTxt_Native_IbtAmp.GetString(), "_Ibt", "A", "number", pParas->m_uiCUR[10].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ibt��λ"*/g_sLangTxt_Native_IbtPhase.GetString(), "_IbtPh", "��", "number", pParas->m_uiCUR[10].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IbtƵ��"*/g_sLangTxt_Native_IbtFreq.GetString(), "_IbtFre", "Hz", "number", pParas->m_uiCUR[10].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ict��ֵ"*/g_sLangTxt_Native_IctAmp.GetString(), "_Ict", "A", "number", pParas->m_uiCUR[11].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ict��λ"*/g_sLangTxt_Native_IctPhase.GetString(), "_IctPh", "��", "number", pParas->m_uiCUR[11].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"IctƵ��"*/g_sLangTxt_Native_IctFreq.GetString(), "_IctFre", "Hz", "number", pParas->m_uiCUR[11].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#endif
    //�°����л�,U1~U18,i1~i18
    CString strID;
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("�Ƿ���ֹͣ", "bBinStop", "", "BOOL", pParas->m_bBinStop);
    //	pXmlSierialize->xml_serialize("������ʱ","fOverload","s","number",pParas->m_fOverloadDelaytime);
    pXmlSierialize->xml_serialize("�Ƿ���ֱ��ģʽ���", "bDC", "", "BOOL", pParas->m_bDC);
    pXmlSierialize->xml_serialize("�Ƿ��ϻ�����", "bAging", "", "BOOL", pParas->m_bAging);
    pXmlSierialize->xml_serialize("����ֱ������", "fCurAux", "mA", "number", pParas->m_fCurAux);
    pXmlSierialize->xml_serialize("����ֱ����ѹ", "_UdcAux", "V", "number", pParas->m_fVolAux);
    pXmlSierialize->xml_serialize("�ݱ�ͨ��ѡ��", "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize("�ݱ�����ѡ��", "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
    pXmlSierialize->xml_serialize("�仯ģʽ", "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
    pXmlSierialize->xml_serialize("�仯ʼֵ", "Start", "", "number", pParas->m_manuGradient.fStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "End", "", "number", pParas->m_manuGradient.fEnd);
    pXmlSierialize->xml_serialize("�仯����", "Step", "", "number", pParas->m_manuGradient.fStep);
    pXmlSierialize->xml_serialize("ÿ��ʱ��", "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
    pXmlSierialize->xml_serialize("������ʱ", "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	// pXmlSierialize->xml_serialize("�仯г������", "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
    pXmlSierialize->xml_serialize("�����߼�", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"�Ƿ���ֹͣ"*/g_sLangTxt_Native_YNInputStop.GetString(), "bBinStop", "", "BOOL", pParas->m_bBinStop);
	//	pXmlSierialize->xml_serialize("������ʱ","fOverload","s","number",pParas->m_fOverloadDelaytime);
	pXmlSierialize->xml_serialize(/*"�Ƿ���ֱ��ģʽ���"*/g_sLangTxt_Native_DCOutputMode.GetString(), "bDC", "", "BOOL", pParas->m_bDC);
	pXmlSierialize->xml_serialize(/*"�Ƿ��ϻ�����"*/g_sLangTxt_Native_YNaging_test.GetString(), "bAging", "", "BOOL", pParas->m_bAging);
	pXmlSierialize->xml_serialize(/*"����ֱ������"*/g_sLangTxt_Native_AuxiDCI.GetString(), "fCurAux", "mA", "number", pParas->m_fCurAux);
	pXmlSierialize->xml_serialize(/*"����ֱ����ѹ"*/g_sLangTxt_Native_AuxiDCV.GetString(), "_UdcAux", "V", "number", pParas->m_fVolAux);
	pXmlSierialize->xml_serialize(/*"�ݱ�ͨ��ѡ��"*/g_sLangTxt_Native_varchannel_select.GetString(), "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
	pXmlSierialize->xml_serialize(/*"�ݱ�����ѡ��"*/g_sLangTxt_Native_vartype_select.GetString(), "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
	pXmlSierialize->xml_serialize(/*"�仯ģʽ"*/g_sLangTxt_Native_change_mode.GetString(), "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
	pXmlSierialize->xml_serialize(/*"�仯ʼֵ"*/g_sLangTxt_Gradient_Init.GetString(), "Start", "", "number", pParas->m_manuGradient.fStart);
	pXmlSierialize->xml_serialize(/*"�仯��ֵ"*/g_sLangTxt_Gradient_Finish.GetString(), "End", "", "number", pParas->m_manuGradient.fEnd);
	pXmlSierialize->xml_serialize(/*"�仯����"*/g_sLangTxt_Gradient_Step.GetString(), "Step", "", "number", pParas->m_manuGradient.fStep);
	pXmlSierialize->xml_serialize(/*"ÿ��ʱ��"*/g_sLangTxt_Native_step_time.GetString(), "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
	pXmlSierialize->xml_serialize(/*"������ʱ"*/g_sLangTxt_Native_trigger_delay.GetString(), "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	// pXmlSierialize->xml_serialize(/*"�仯г������"*/g_sLangTxt_Native_VarHarmonicNum.GetString(), "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
	pXmlSierialize->xml_serialize(/*"�����߼�"*/g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_binary_out_Pnv(pParas->m_binOut, pXmlSierialize);
    //Ex
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);
    stt_xml_serialize_dc(pParas, pXmlSierialize);
    //	stt_xml_serialize_Aging(pParas,pXmlSierialize);  zhouhj 20210828 �ظ����л�
    //	stt_xml_serialize_Lock(pParas,pXmlSierialize);
    //	stt_xml_serialize_Auto(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("�Ƿ�����", "_bLock", "", "BOOL", pParas->m_bLockChanged);
    pXmlSierialize->xml_serialize("�Ƿ��Զ��ݱ�", "_bAuto", "", "BOOL", pParas->m_bAuto);
#else
	pXmlSierialize->xml_serialize(/*"�Ƿ�����"*/g_sLangTxt_Native_YN_locked.GetString(), "_bLock", "", "BOOL", pParas->m_bLockChanged);
	pXmlSierialize->xml_serialize(/*"�Ƿ��Զ��ݱ�"*/g_sLangTxt_Native_YN_autoevo.GetString(), "_bAuto", "", "BOOL", pParas->m_bAuto);
#endif
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
        stt_xml_serialize(&pParas->m_oFt3Pub[0], pXmlSierialize);
        stt_xml_serialize(&pParas->m_o2MOnePortPub[0], pXmlSierialize);
    }

// 	stt_xml_serialize_Harm(pParas,pXmlSierialize,nVolRsNum,nCurRsNum);//����г��
//
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("����ʱ��(s)", "_TimeMax", " ", "number", pParas->m_fOutPutTime);
#else
	pXmlSierialize->xml_serialize(/*"����ʱ��(s)"*/g_sLangTxt_Native_max_outputtime.GetString(), "_TimeMax", " ", "number", pParas->m_fOutPutTime);
#endif
// 	//	pXmlSierialize->xml_serialize("��ʼ����ʱ���ͱ���", "UploadRpt_Started"," ","number",pParas->m_nUploadRpt_Started);
//
// 	if (pParas->m_nFuncType>TMT_MANU_FUNC_TYPE_Common)
// 	{
// 		stt_xml_serialize_MU(&pParas->m_oMuParas,pXmlSierialize);// �ϲ���Ԫ����
// 	}
}



#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_ManuTest()
{
    tmt_ManualTest oManualTest;
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
    strXMLPath += ("ManualTestDemo.xml");
//   pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

//void stt_xml_serialize_write_SysOutput()
//{
//	TMT_SYSTEM_DEFAULT_OUTPUT_PARAS oSysOutput;
//	oSysOutput.init();
//	CSttXmlSerializeTool oSttXmlSerializeTool;
//	CSttTestCmd oSttTestCmd;
//	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
//	pMacro->GetParas();
//	pMacro->GetResults();
//	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
//	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
//	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
//	stt_xml_serialize(&oSysOutput, pMacroParas);
//	CString strXMLPath;
//	strXMLPath = _P_GetConfigPath();
//	strXMLPath += ("SysOutputDemo.xml");
//	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

//	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
//}

CSttXmlSerializeBase *stt_xml_serialize(tmt_ManualTest *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
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

