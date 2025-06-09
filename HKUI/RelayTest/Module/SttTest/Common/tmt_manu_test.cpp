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
        pXmlSierialize->xml_serialize("是否以直流模式输出", "bDC", "", "BOOL", bDC);
#else
		        pXmlSierialize->xml_serialize(/*"是否以直流模式输出"*/g_sLangTxt_Native_DCOutputMode.GetString(), "bDC", "", "BOOL", bDC);
#endif
        pParas->setDC(bDC);
    }
//     else//zhouhj 2024.1.3 在写模式时,此处重复了,在调用该接口前,已经写了,此处重复了
//     {
//         if(pParas->m_bDC)
//         {
//             bDC = 1;
//         }
// 
// #ifdef NOT_USE_XLANGUAGE
//         pXmlSierialize->xml_serialize("是否以直流模式输出", "bDC", "", "BOOL", bDC);
// #else
// 		        pXmlSierialize->xml_serialize(/*"是否以直流模式输出"*/g_sLangTxt_Native_DCOutputMode.GetString(), "bDC", "", "BOOL", bDC);
// #endif
//     }
}

void stt_xml_serialize_Harm(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
{
    CSttXmlSerializeBase *pHarmSelSerialize = NULL;
#ifdef NOT_USE_XLANGUAGE
    pHarmSelSerialize = pXmlSierialize->xml_serialize("谐波叠加", "Harm", "HarmSel", stt_ParaGroupKey());
#else
	    pHarmSelSerialize = pXmlSierialize->xml_serialize(/*"谐波叠加"*/g_sLangTxt_Native_HarmSuperposition.GetString(), "Harm", "HarmSel", stt_ParaGroupKey());
#endif

    if(pHarmSelSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pHarmSelSerialize->xml_serialize("谐波选择", "HarmSel", "", "number", pParas->m_nSelHarm);
    pHarmSelSerialize->xml_serialize("谐波次数", "HarmIndex", "", "number", pParas->m_nHarmIndex);
#else
	pHarmSelSerialize->xml_serialize(/*"谐波选择"*/g_sLangTxt_Native_HarmSelection.GetString(), "HarmSel", "", "number", pParas->m_nSelHarm);
	pHarmSelSerialize->xml_serialize(/*"谐波次数"*/g_sLangTxt_Native_harmonicOrder.GetString(), "HarmIndex", "", "number", pParas->m_nHarmIndex);
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
        pHarmSelSerialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiVOL[nIndex].Harm[pParas->m_nHarmIndex].fAngle);
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
        pHarmSelSerialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiCUR[nIndex].Harm[pParas->m_nHarmIndex].fAngle);
        pParas->m_uiCUR[nIndex].Harm[pParas->m_nHarmIndex].fFreq = pParas->m_uiCUR[nIndex].Harm[1].fFreq * pParas->m_nHarmIndex;
    }
}

void stt_xml_serialize_MU(tmt_MuParas *pMuParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pMuParasSerialize = NULL;
#ifdef NOT_USE_XLANGUAGE
    pMuParasSerialize = pXmlSierialize->xml_serialize("合并单元", "MU", "MU", stt_ParaGroupKey());
#else
	    pMuParasSerialize = pXmlSierialize->xml_serialize(/*"合并单元"*/g_sLangTxt_Native_MrgUnit.GetString(), "MU", "MU", stt_ParaGroupKey());
#endif

    if(pMuParasSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pMuParasSerialize->xml_serialize("算法选择(0:插值法  1:同步法)", "AlgorithmType", "", "number", pMuParas->nAlgorithmType);
    pMuParasSerialize->xml_serialize("PPS设置(0:上升沿有效  1:下降沿有效 2:无PPS)", "PPS_SetType", "", "number", pMuParas->nPPS_SetType);
    pMuParasSerialize->xml_serialize("额定相电压(零漂计算)", "StdVoltage", "", "number", pMuParas->fUn);
    pMuParasSerialize->xml_serialize("额定相电流(零漂计算)", "StdCurrent", "", "number", pMuParas->fIn);
    pMuParasSerialize->xml_serialize("守时精度测试时同步时长(单位:s)", "SynTime", "", "number", pMuParas->nSynTime);
//    pMuParasSerialize->xml_serialize("无PPS时延时补偿值(对时守时测试用,单位:μs)", "DelayCompens_NoPPS", "", "number", pMuParas->fDelayCompens_NoPPS);
	pMuParasSerialize->xml_serialize("是否使用自定义报告次数(合并单元)","UseSetRpt","","number",pMuParas->m_nUseSetRpt);
	pMuParasSerialize->xml_serialize("自定义报告测试次数(合并单元)","MUTestMaxTestCount","","number",pMuParas->m_nMaxTestCount);
	pMuParasSerialize->xml_serialize("每次测试时间(合并单元,单位秒)","TimeOneCount","","number",pMuParas->m_fTimeOneCount);
#else
	pMuParasSerialize->xml_serialize(/*"算法选择(0:插值法  1:同步法)"*/g_sLangTxt_Native_AlgorithmSelection.GetString(), "AlgorithmType", "", "number", pMuParas->nAlgorithmType);
	pMuParasSerialize->xml_serialize(/*"PPS设置(0:上升沿有效  1:下降沿有效 2:无PPS)"*/g_sLangTxt_Native_PPSConfiguration.GetString(), "PPS_SetType", "", "number", pMuParas->nPPS_SetType);
	pMuParasSerialize->xml_serialize(/*"额定相电压(零漂计算)"*/g_sLangTxt_Native_RatedV_Phase_ZeroDriftCalc.GetString(), "StdVoltage", "", "number", pMuParas->fUn);
	pMuParasSerialize->xml_serialize(/*"额定相电流(零漂计算)"*/g_sLangTxt_Native_RatedI_Phase_ZeroDriftCalc.GetString(), "StdCurrent", "", "number", pMuParas->fIn);
	pMuParasSerialize->xml_serialize(/*"守时精度测试时同步时长(单位:s)"*/g_sLangTxt_Native_SyncDur_TAT.GetString(), "SynTime", "", "number", pMuParas->nSynTime);
	//pMuParasSerialize->xml_serialize(/*"无PPS时延时补偿值(对时守时测试用,单位:μs)"*/g_sLangTxt_Native_DelayComp_NoPPS.GetString(), "DelayCompens_NoPPS", "", "number", pMuParas->fDelayCompens_NoPPS);
	pMuParasSerialize->xml_serialize(/*"是否使用自定义报告次数(合并单元)"*/g_sLangTxt_Native_CustomRepCnt_Use_MU.GetString(),"UseSetRpt","","number",pMuParas->m_nUseSetRpt);
	pMuParasSerialize->xml_serialize(/*"自定义报告测试次数(合并单元)"*/g_sLangTxt_Native_CustomRepTestCnt_MU.GetString(),"MUTestMaxTestCount","","number",pMuParas->m_nMaxTestCount);
	pMuParasSerialize->xml_serialize(/*"每次测试时间(合并单元,单位秒)"*/g_sLangTxt_Native_TestDurPerTest_MU_sec.GetString(),"TimeOneCount","","number",pMuParas->m_fTimeOneCount);
#endif
}

void stt_xml_serialize_MuTime(tmt_MuTimeResult *pMuTimeRlt, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pMuTimeSerialize = NULL;
#ifdef NOT_USE_XLANGUAGE
    pMuTimeSerialize = pXmlSierialize->xml_serialize("MU时间测试结果", "MuTime", "MuTime", stt_ParaGroupKey());
#else
    pMuTimeSerialize = pXmlSierialize->xml_serialize(/*"MU时间测试结果"*/g_sLangTxt_Native_MUTimeTestResults.GetString(), "MuTime", "MuTime", stt_ParaGroupKey());
#endif
    if(pMuTimeSerialize == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pMuTimeSerialize->xml_serialize("已测试时长", "HasUsingTime", "", "number", pMuTimeRlt->m_fHasUsingTime);
//	pMuTimeSerialize->xml_serialize("当前误差时间","CurrErrTime","","number",pMuTimeRlt->m_fCurrErrTime);
    pMuTimeSerialize->xml_serialize("最大误差时间", "MaxErrTime", "", "number", pMuTimeRlt->m_fMaxErrTime);
    pMuTimeSerialize->xml_serialize("最小误差时间", "MinErrTime", "", "number", pMuTimeRlt->m_fMinErrTime);
    pMuTimeSerialize->xml_serialize("平均误差时间", "AverageErrTime", "", "number", pMuTimeRlt->m_fAverageErrTime);
    pMuTimeSerialize->xml_serialize("时间精度测试结果", "MUTimeResult", "", "number", pMuTimeRlt->m_nTimeTestResult);
#else
	pMuTimeSerialize->xml_serialize(/*"已测试时长"*/g_sLangTxt_Native_TestedDur.GetString(), "HasUsingTime", "", "number", pMuTimeRlt->m_fHasUsingTime);
	//	pMuTimeSerialize->xml_serialize("当前误差时间","CurrErrTime","","number",pMuTimeRlt->m_fCurrErrTime);
	pMuTimeSerialize->xml_serialize(/*"最大误差时间"*/g_sLangTxt_Native_MaxErrTime.GetString(), "MaxErrTime", "", "number", pMuTimeRlt->m_fMaxErrTime);
	pMuTimeSerialize->xml_serialize(/*"最小误差时间"*/g_sLangTxt_Native_MinErrTime.GetString(), "MinErrTime", "", "number", pMuTimeRlt->m_fMinErrTime);
	pMuTimeSerialize->xml_serialize(/*"平均误差时间"*/g_sLangTxt_Native_AvgErrTime.GetString(), "AverageErrTime", "", "number", pMuTimeRlt->m_fAverageErrTime);
	pMuTimeSerialize->xml_serialize(/*"时间精度测试结果"*/g_sLangTxt_Native_TimeAccTestResults.GetString(), "MUTimeResult", "", "number", pMuTimeRlt->m_nTimeTestResult);
#endif
}

// void stt_xml_serialize_Aging(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
// {
// 	int bAging = 0;
// 	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
// 	{
// 		pXmlSierialize->xml_serialize("是否老化试验", "bAging", "", "BOOL", bAging);
// 		pParas->m_bAging = bAging;
// 	}
// 	else
// 	{
// 		if (pParas->m_bAging)
// 		{
// 			bAging = 1;
// 		}
// 		pXmlSierialize->xml_serialize("是否老化试验", "bAging", "", "BOOL", bAging);
// 	}
// }

// void stt_xml_serialize_Lock(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
// {
// 	int bLock = 0;
// 	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
// 	{
// 		pXmlSierialize->xml_serialize("是否锁定", "_bLock", "", "BOOL", bLock);
// 		pParas->m_bLockChanged = bLock;
// 	}
// 	else
// 	{
// 		if (pParas->m_bLockChanged)
// 		{
// 			bLock = 1;
// 		}
// 		pXmlSierialize->xml_serialize("是否锁定", "_bLock", "", "BOOL", bLock);
// 	}
// }

// void stt_xml_serialize_Auto(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
// {
// 	int bAuto = 0;
// 	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
// 	{
// 		pXmlSierialize->xml_serialize("是否自动递变", "_bAuto", "", "BOOL", bAuto);
// 		pParas->m_bAuto = bAuto;
// 	}
// 	else
// 	{
// 		if (pParas->m_bAuto)
// 		{
// 			bAuto = 1;
// 		}
// 		pXmlSierialize->xml_serialize("是否自动递变", "_bAuto", "", "BOOL", bAuto);
// 	}
// }

void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize(pParas, pXmlSierialize, MAX_VOLTAGE_COUNT, MAX_CURRENT_COUNT);
}

void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
{
    /**********兼容PTU200L安卓*********/
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
#ifdef NOT_USE_XLANGUAGE
        pXmlSierialize->xml_serialize_sys_pata("Ua幅值", "Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Ua相位", "UaPh", "°", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ua频率", "UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ub幅值", "Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Ub相位", "UbPh", "°", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ub频率", "UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Uc幅值", "Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Uc相位", "UcPh", "°", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Uc频率", "UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Uap幅值", "Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Uap相位", "UapPh", "°", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Uap频率", "UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ubp幅值", "Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Ubp相位", "UbpPh", "°", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ubp频率", "UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ucp幅值", "Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Ucp相位", "UcpPh", "°", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ucp频率", "UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ia幅值", "Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
        pXmlSierialize->xml_serialize("Ia相位", "IaPh", "°", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ia频率", "IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ib幅值", "Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
        pXmlSierialize->xml_serialize("Ib相位", "IbPh", "°", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ib频率", "IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ic幅值", "Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
        pXmlSierialize->xml_serialize("Ic相位", "IcPh", "°", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ic频率", "IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Iap幅值", "Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
        pXmlSierialize->xml_serialize("Iap相位", "IapPh", "°", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Iap频率", "IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ibp幅值", "Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
        pXmlSierialize->xml_serialize("Ibp相位", "IbpPh", "°", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ibp频率", "IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Icp幅值", "Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
        pXmlSierialize->xml_serialize("Icp相位", "IcpPh", "°", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Icp频率", "IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#else
		pXmlSierialize->xml_serialize_sys_pata(/*"Ua幅值"*/g_sLangTxt_Native_UaAmplitude.GetString(), "Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ua相位"*/g_sLangTxt_Native_UaPhase.GetString(), "UaPh", "°", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ua频率"*/g_sLangTxt_Native_UaFreq.GetString(), "UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ub幅值"*/g_sLangTxt_Native_UbAmplitude.GetString(), "Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ub相位"*/g_sLangTxt_Native_UbPhase.GetString(), "UbPh", "°", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ub频率"*/g_sLangTxt_Native_UbFreq.GetString(), "UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Uc幅值"*/g_sLangTxt_Native_UcAmplitude.GetString(), "Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Uc相位"*/g_sLangTxt_Native_UcPhase.GetString(), "UcPh", "°", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Uc频率"*/g_sLangTxt_Native_UcFreq.GetString(), "UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Uap幅值"*/g_sLangTxt_Native_UapAmp.GetString(), "Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Uap相位"*/g_sLangTxt_Native_UapPhase.GetString(), "UapPh", "°", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Uap频率"*/g_sLangTxt_Native_UapFreq.GetString(), "UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ubp幅值"*/g_sLangTxt_Native_UbpAmp.GetString(), "Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ubp相位"*/g_sLangTxt_Native_UbpPhase.GetString(), "UbpPh", "°", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ubp频率"*/g_sLangTxt_Native_UbpFreq.GetString(), "UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ucp幅值"*/g_sLangTxt_Native_UcpAmp.GetString(), "Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ucp相位"*/g_sLangTxt_Native_UcpPhase.GetString(), "UcpPh", "°", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ucp频率"*/g_sLangTxt_Native_UcpFreq.GetString(), "UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ia幅值"*/g_sLangTxt_Native_IaAmp.GetString(), "Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ia相位"*/g_sLangTxt_Native_IaPhase.GetString(), "IaPh", "°", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ia频率"*/g_sLangTxt_Native_IaFreq.GetString(), "IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ib幅值"*/g_sLangTxt_Native_IbAmp.GetString(), "Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ib相位"*/g_sLangTxt_Native_IbPhase.GetString(), "IbPh", "°", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ib频率"*/g_sLangTxt_Native_IbFreq.GetString(), "IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ic幅值"*/g_sLangTxt_Native_IcAmp.GetString(), "Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ic相位"*/g_sLangTxt_Native_IcPhase.GetString(), "IcPh", "°", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ic频率"*/g_sLangTxt_Native_IcFreq.GetString(), "IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Iap幅值"*/g_sLangTxt_Native_IapAmp.GetString(), "Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Iap相位"*/g_sLangTxt_Native_IapPhase.GetString(), "IapPh", "°", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Iap频率"*/g_sLangTxt_Native_IapFreq.GetString(), "IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ibp幅值"*/g_sLangTxt_Native_IbpAmp.GetString(), "Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ibp相位"*/g_sLangTxt_Native_IbpPhase.GetString(), "IbpPh", "°", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ibp频率"*/g_sLangTxt_Native_IbpFreq.GetString(), "IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		pXmlSierialize->xml_serialize_sys_pata(/*"Icp幅值"*/g_sLangTxt_Native_IcpAmp.GetString(), "Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Icp相位"*/g_sLangTxt_Native_IcpPhase.GetString(), "IcpPh", "°", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
		pXmlSierialize->xml_serialize_sys_pata(/*"Icp频率"*/g_sLangTxt_Native_IcpFreq.GetString(), "IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#endif
    }
    //兼容PsuVm
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        pXmlSierialize->xml_serialize_sys_pata("Ua1幅值", "_Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Ua1相位", "_UaPh", "°", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ua1频率", "_UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ub1幅值", "_Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Ub1相位", "_UbPh", "°", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ub1频率", "_UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Uc1幅值", "_Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Uc1相位", "_UcPh", "°", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Uc1频率", "_UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ua2幅值", "_Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Ua2相位", "_UapPh", "°", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ua2频率", "_UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Ub2幅值", "_Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Ub2相位", "_UbpPh", "°", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Ub2频率", "_UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
        pXmlSierialize->xml_serialize_sys_pata("Uc2幅值", "_Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
        pXmlSierialize->xml_serialize("Uc2相位", "_UcpPh", "°", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
        pXmlSierialize->xml_serialize_sys_pata("Uc2频率", "_UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);

        char strChabc[4] = "abc";

        CString strName, strID;
        for(int i=0; i<6; i++)
        {
            for(int j=0; j<3; j++)
            {
                strID.Format("_I%c%d",strChabc[j],i+1);
                strName.Format("I%c%d幅值",strChabc[j],i+1);
                pXmlSierialize->xml_serialize_sys_pata(strName.GetString(), strID.GetString(), "A", "number", pParas->m_uiCUR[(i*3+j)].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
                strID.Format("_I%c%dPh",strChabc[j],i+1);
                strName.Format("I%c%d相位",strChabc[j],i+1);
                pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "°", "number", pParas->m_uiCUR[(i*3+j)].Harm[1].fAngle);
                strID.Format("_I%c%dFre",strChabc[j],i+1);
                strName.Format("I%c%d频率",strChabc[j],i+1);
                pXmlSierialize->xml_serialize_sys_pata(strName.GetString(), strID.GetString(), "Hz", "number", pParas->m_uiCUR[(i*3+j)].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
            }
        }
    }

    /**********兼容PTU200L安卓*********/
    //新版序列化,U1~U18,i1~i18
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
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiVOL[nIndex].Harm[1].fAngle);
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
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiCUR[nIndex].Harm[1].fAngle);
        strID.Format(_T("I%dFre"), nIndex + 1);
        pXmlSierialize->xml_serialize_sys_pata("", strID.GetString(), "Hz", "number", pParas->m_uiCUR[nIndex].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    }
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("测试功能类别(0:普通手动试验1:MU精度测试2:MU零漂测试)", "FuncType", "", "number", pParas->m_nFuncType);
    pXmlSierialize->xml_serialize("是否开入停止", "bBinStop", "", "BOOL", pParas->m_bBinStop);
//	pXmlSierialize->xml_serialize("过载延时","fOverload","s","number",pParas->m_fOverloadDelaytime);
    pXmlSierialize->xml_serialize("是否以直流模式输出", "bDC", "", "BOOL", pParas->m_bDC);
    pXmlSierialize->xml_serialize("是否老化试验", "bAging", "", "BOOL", pParas->m_bAging);
    pXmlSierialize->xml_serialize("辅助直流电流", "fCurAux", "mA", "number", pParas->m_fCurAux);
    pXmlSierialize->xml_serialize("辅助直流电压", "_UdcAux", "V", "number", pParas->m_fVolAux);
    pXmlSierialize->xml_serialize("递变通道选择", "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize("递变类型选择", "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
    pXmlSierialize->xml_serialize("变化模式", "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
    pXmlSierialize->xml_serialize("变化始值", "Start", "", "number", pParas->m_manuGradient.fStart);
    pXmlSierialize->xml_serialize("变化终值", "End", "", "number", pParas->m_manuGradient.fEnd);
    pXmlSierialize->xml_serialize("变化步长", "Step", "", "number", pParas->m_manuGradient.fStep);
    pXmlSierialize->xml_serialize("每步时间", "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
    pXmlSierialize->xml_serialize("触发延时", "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	// pXmlSierialize->xml_serialize("变化谐波次数", "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
	pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"测试功能类别(0:普通手动试验1:MU精度测试2:MU零漂测试)"*/g_sLangTxt_Native_TestFuncCategory.GetString(), "FuncType", "", "number", pParas->m_nFuncType);
	pXmlSierialize->xml_serialize(/*"是否开入停止"*/g_sLangTxt_Native_YNInputStop.GetString(), "bBinStop", "", "BOOL", pParas->m_bBinStop);
	//	pXmlSierialize->xml_serialize("过载延时","fOverload","s","number",pParas->m_fOverloadDelaytime);
	pXmlSierialize->xml_serialize(/*"是否以直流模式输出"*/g_sLangTxt_Native_DCOutputMode.GetString(), "bDC", "", "BOOL", pParas->m_bDC);
	pXmlSierialize->xml_serialize(/*"是否老化试验"*/g_sLangTxt_Native_YNaging_test.GetString(), "bAging", "", "BOOL", pParas->m_bAging);
	pXmlSierialize->xml_serialize(/*"辅助直流电流"*/g_sLangTxt_Native_AuxiDCI.GetString(), "fCurAux", "mA", "number", pParas->m_fCurAux);
	pXmlSierialize->xml_serialize(/*"辅助直流电压"*/g_sLangTxt_Native_AuxiDCV.GetString(), "_UdcAux", "V", "number", pParas->m_fVolAux);
	pXmlSierialize->xml_serialize(/*"递变通道选择"*/g_sLangTxt_Native_varchannel_select.GetString(), "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
	pXmlSierialize->xml_serialize(/*"递变类型选择"*/g_sLangTxt_Native_vartype_select.GetString(), "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
	pXmlSierialize->xml_serialize(/*"变化模式"*/g_sLangTxt_Native_change_mode.GetString(), "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
	pXmlSierialize->xml_serialize(/*"变化始值"*/g_sLangTxt_Gradient_Init.GetString(), "Start", "", "number", pParas->m_manuGradient.fStart);
	pXmlSierialize->xml_serialize(/*"变化终值"*/g_sLangTxt_Gradient_Finish.GetString(), "End", "", "number", pParas->m_manuGradient.fEnd);
	pXmlSierialize->xml_serialize(/*"变化步长"*/g_sLangTxt_Gradient_Step.GetString(), "Step", "", "number", pParas->m_manuGradient.fStep);
	pXmlSierialize->xml_serialize(/*"每步时间"*/g_sLangTxt_Native_step_time.GetString(), "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
	pXmlSierialize->xml_serialize(/*"触发延时"*/g_sLangTxt_Native_trigger_delay.GetString(), "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	// pXmlSierialize->xml_serialize(/*"变化谐波次数"*/g_sLangTxt_Native_VarHarmonicNum.GetString(), "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
	pXmlSierialize->xml_serialize(/*"测试通道类型"*/g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize(/*"开入逻辑"*/g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    //Ex
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);
    stt_xml_serialize_dc(pParas, pXmlSierialize);
//	stt_xml_serialize_Aging(pParas,pXmlSierialize);  zhouhj 20210828 重复串行化
//	stt_xml_serialize_Lock(pParas,pXmlSierialize);
//	stt_xml_serialize_Auto(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("是否锁定", "_bLock", "", "BOOL", pParas->m_bLockChanged);
    pXmlSierialize->xml_serialize("是否自动递变", "_bAuto", "", "BOOL", pParas->m_bAuto);
	pXmlSierialize->xml_serialize("", "ResultAddBin", "", "BOOL", pParas->m_bResultAddBin);//自动测试用
#else
	pXmlSierialize->xml_serialize(/*"是否锁定"*/g_sLangTxt_Native_YN_locked.GetString(), "_bLock", "", "BOOL", pParas->m_bLockChanged);
	pXmlSierialize->xml_serialize(/*"是否自动递变"*/g_sLangTxt_Native_YN_autoevo.GetString(), "_bAuto", "", "BOOL", pParas->m_bAuto);
#endif
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
        stt_xml_serialize(&pParas->m_oFt3Pub[0], pXmlSierialize);
        stt_xml_serialize(&pParas->m_o2MOnePortPub[0], pXmlSierialize);
    }

    stt_xml_serialize_Harm(pParas, pXmlSierialize, nVolRsNum, nCurRsNum); //叠加谐波
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("最长输出时间(s)", "OutputTime", " ", "number", pParas->m_fOutPutTime);
#else
	    pXmlSierialize->xml_serialize(/*"最长输出时间(s)"*/g_sLangTxt_Native_max_outputtime.GetString(), "OutputTime", " ", "number", pParas->m_fOutPutTime);
#endif
//	pXmlSierialize->xml_serialize("开始测试时上送报告", "UploadRpt_Started"," ","number",pParas->m_nUploadRpt_Started);

    if(pParas->m_nFuncType > TMT_MANU_FUNC_TYPE_Common)
    {
        stt_xml_serialize_MU(&pParas->m_oMuParas, pXmlSierialize); // 合并单元测试
    }

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作整定时间","TSet","s","float",pParas->m_fTimeSet);
	pXmlSierialize->xml_serialize("电压整定动作值","USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize("电流整定动作值","ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize("相位整定动作值","AngleSet","°","float",pParas->m_fAngleSet);
	pXmlSierialize->xml_serialize("频率整定动作值","HzSet","Hz","float",pParas->m_fHzSet);
	pXmlSierialize->xml_serialize("返回系数整定值","RetCoefSet","","float",pParas->m_fRetCoefSet);


	pXmlSierialize->xml_serialize("动作时间值绝对误差","Ttrip_AbsErr","","float",pParas->m_fTimeValue_AbsErr);
	pXmlSierialize->xml_serialize("动作时间值相对误差","Ttrip_RelErr","","float",pParas->m_fTimeValue_RelErr);
	pXmlSierialize->xml_serialize("动作时间误差判断逻辑","TimeValue_ErrorLogic","","number",pParas->m_nTimeValue_ErrorLogic);
	pXmlSierialize->xml_serialize("电压动作值绝对误差","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("电压动作值相对误差","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("电压动作值误差判断逻辑","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("电流动作值绝对误差","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("电流动作值相对误差","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("电流动作值误差判断逻辑","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("相位动作值绝对误差","AngleActVal_AbsErr","","float",pParas->m_fAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize("相位动作值相对误差","AngleActVal_RelErr","","float",pParas->m_fAngleActVal_RelErr);
	pXmlSierialize->xml_serialize("相位动作值误差判断逻辑","AngleActVal_ErrorLogic","","number",pParas->m_nAngleActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("频率动作值绝对误差","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
	pXmlSierialize->xml_serialize("频率动作值相对误差","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
	pXmlSierialize->xml_serialize("频率动作值误差判断逻辑","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
	pXmlSierialize->xml_serialize("返回系数绝对误差","RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize("返回系数相对误差","RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize("返回系数误差判断逻辑","RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
#else
	pXmlSierialize->xml_serialize(/*"动作整定时间"*/g_sLangTxt_Native_acttuning_time.GetString(),"TSet","s","float",pParas->m_fTimeSet);
	pXmlSierialize->xml_serialize(/*"电压整定动作值"*/g_sLangTxt_Native_VolSetActValue.GetString(),"USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize(/*"电流整定动作值"*/g_sLangTxt_Native_CurSetActValue.GetString(),"ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize(/*"相位整定动作值"*/g_sLangTxt_Native_PhSetActValue.GetString(),"AngleSet","°","float",pParas->m_fAngleSet);
	pXmlSierialize->xml_serialize(/*"频率整定动作值"*/g_sLangTxt_Native_FreqSetActValue.GetString(),"HzSet","Hz","float",pParas->m_fHzSet);
	pXmlSierialize->xml_serialize(/*"返回系数整定值"*/g_sLangTxt_Native_FeedbackCoefSettingVal.GetString(),"RetCoefSet","","float",pParas->m_fRetCoefSet);


	pXmlSierialize->xml_serialize(/*"动作时间值绝对误差"*/g_sLangTxt_Native_ActTimeValueAbsErr.GetString(),"Ttrip_AbsErr","","float",pParas->m_fTimeValue_AbsErr);
	pXmlSierialize->xml_serialize(/*"动作时间值相对误差"*/g_sLangTxt_Native_ActTimeValueRelErr.GetString(),"Ttrip_RelErr","","float",pParas->m_fTimeValue_RelErr);
	pXmlSierialize->xml_serialize(/*"动作时间误差判断逻辑"*/g_sLangTxt_Native_ActTimeValueErrLogic.GetString(),"TimeValue_ErrorLogic","","number",pParas->m_nTimeValue_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"电压动作值绝对误差"*/g_sLangTxt_Native_VActionValueAbsErr.GetString(),"UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"电压动作值相对误差"*/g_sLangTxt_Native_VActionValueRelErr.GetString(),"UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"电压动作值误差判断逻辑"*/g_sLangTxt_Native_VActionValueErrLogic.GetString(),"UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"电流动作值绝对误差"*/g_sLangTxt_Native_IActionValueAbsErr.GetString(),"IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"电流动作值相对误差"*/g_sLangTxt_Native_IActionValueRelErr.GetString(),"IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"电流动作值误差判断逻辑"*/g_sLangTxt_Native_IActionValueErrLogic.GetString(),"IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"相位动作值绝对误差"*/g_sLangTxt_Native_PhaseActValueAbsErr.GetString(),"AngleActVal_AbsErr","","float",pParas->m_fAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"相位动作值相对误差"*/g_sLangTxt_Native_PhaseActValueRelErr.GetString(),"AngleActVal_RelErr","","float",pParas->m_fAngleActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"相位动作值误差判断逻辑"*/g_sLangTxt_Native_PhaseActValueErrLogic.GetString(),"AngleActVal_ErrorLogic","","number",pParas->m_nAngleActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"频率动作值绝对误差"*/g_sLangTxt_Native_FreqPickAbsErr.GetString(),"HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
	pXmlSierialize->xml_serialize(/*"频率动作值相对误差"*/g_sLangTxt_Native_FreqPickRelErr.GetString(),"HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
	pXmlSierialize->xml_serialize(/*"频率动作值误差判断逻辑"*/g_sLangTxt_Native_FreqPickErrDetectLogic.GetString(),"HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
	pXmlSierialize->xml_serialize(/*"返回系数绝对误差"*/g_sLangTxt_Native_CoefficientAbsErr.GetString(),"RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize(/*"返回系数相对误差"*/g_sLangTxt_Native_CoefficientRelErr.GetString(),"RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize(/*"返回系数误差判断逻辑"*/g_sLangTxt_Native_CoefficientErrLogic.GetString(),"RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
#endif
}

void stt_xml_serialize_act_rcd(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//动作记录,最大64次,根据实际动作情况,上送总的动作信息
{
    CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

    if(pXmlActRcddata == NULL)
    {
        return;
    }

    CString strName, strID, strTemp, strTmp2;

#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开入");
    CString str2 = _T("第");
    CString str3 = _T("次动作时间");
#else
	CString str1 = /*_T("开入")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("第")*/g_sLangTxt_Native_Number;
	CString str3 = /*_T("次动作时间")*/g_sLangTxt_Native_NActionTime;
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
            strTemp.Format(_T("扩展%d"), nIndex + 1);
#else
	    strTemp.Format(/*_T("扩展%d")*/g_sLangTxt_Native_extend.GetString(), nIndex + 1);
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
    pXmlSierialize->xml_serialize("动作标记", "TripFlag", "", "number", pResults->m_nTripFlag);
    pXmlSierialize->xml_serialize("动作时间", "TripTime", "", "number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("动作值", "ActValue", "", "number", pResults->m_fActValue);
    pXmlSierialize->xml_serialize("返回值", "ReturnValue", "", "number", pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize("返回系数", "ReturnCoef", "", "number", pResults->m_fReturnCoef);
    pXmlSierialize->xml_serialize("返回时间", "ReturnTime", "", "number", pResults->m_fReturnTime);
#else
	pXmlSierialize->xml_serialize(/*"动作标记"*/g_sLangTxt_Native_action_mark.GetString(), "TripFlag", "", "number", pResults->m_nTripFlag);
	pXmlSierialize->xml_serialize(/*"动作时间"*/g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/*"动作值"*/g_sLangTxt_State_ActionValue.GetString(), "ActValue", "", "number", pResults->m_fActValue);
	pXmlSierialize->xml_serialize(/*"返回值"*/g_sLangTxt_Native_ReturnValue.GetString(), "ReturnValue", "", "number", pResults->m_fReturnValue);
	pXmlSierialize->xml_serialize(/*"返回系数"*/g_sLangTxt_Gradient_ReCoefficient.GetString(), "ReturnCoef", "", "number", pResults->m_fReturnCoef);
	pXmlSierialize->xml_serialize(/*"返回时间"*/g_sLangTxt_Native_ReturnTime.GetString(), "ReturnTime", "", "number", pResults->m_fReturnTime);
#endif
    CString strName, strID, strTemp;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开入");
    CString str2 = _T("结果状态");
#else
	CString str1 = /*_T("开入")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("结果状态")*/g_sLangTxt_Native_result_status;
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
                strTemp.Format(_T("扩展%d"), nIndex + 1);
#else
		strTemp.Format(/*_T("扩展%d")*/g_sLangTxt_Native_extend.GetString(), nIndex + 1);
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
    pXmlSierialize->xml_serialize("开出1状态", "_BO01", "", "DOutputState", pbOut[0].nState);
    pXmlSierialize->xml_serialize("开出2状态", "_BO02", "", "DOutputState", pbOut[1].nState);
    pXmlSierialize->xml_serialize("开出3状态", "_BO03", "", "DOutputState", pbOut[2].nState);
    pXmlSierialize->xml_serialize("开出4状态", "_BO04", "", "DOutputState", pbOut[3].nState);
    pXmlSierialize->xml_serialize("开出5状态", "_BO05", "", "DOutputState", pbOut[4].nState);
    pXmlSierialize->xml_serialize("开出6状态", "_BO06", "", "DOutputState", pbOut[5].nState);
    pXmlSierialize->xml_serialize("开出7状态", "_BO07", "", "DOutputState", pbOut[6].nState);
    pXmlSierialize->xml_serialize("开出8状态", "_BO08", "", "DOutputState", pbOut[7].nState);
#else
	pXmlSierialize->xml_serialize(/*"开出1状态"*/g_sLangTxt_Out1_Situation.GetString(), "_BO01", "", "DOutputState", pbOut[0].nState);
	pXmlSierialize->xml_serialize(/*"开出2状态"*/g_sLangTxt_Out2_Situation.GetString(), "_BO02", "", "DOutputState", pbOut[1].nState);
	pXmlSierialize->xml_serialize(/*"开出3状态"*/g_sLangTxt_Out3_Situation.GetString(), "_BO03", "", "DOutputState", pbOut[2].nState);
	pXmlSierialize->xml_serialize(/*"开出4状态"*/g_sLangTxt_Out4_Situation.GetString(), "_BO04", "", "DOutputState", pbOut[3].nState);
	pXmlSierialize->xml_serialize(/*"开出5状态"*/g_sLangTxt_Out5_Situation.GetString(), "_BO05", "", "DOutputState", pbOut[4].nState);
	pXmlSierialize->xml_serialize(/*"开出6状态"*/g_sLangTxt_Out6_Situation.GetString(), "_BO06", "", "DOutputState", pbOut[5].nState);
	pXmlSierialize->xml_serialize(/*"开出7状态"*/g_sLangTxt_Out7_Situation.GetString(), "_BO07", "", "DOutputState", pbOut[6].nState);
	pXmlSierialize->xml_serialize(/*"开出8状态"*/g_sLangTxt_Out8_Situation.GetString(), "_BO08", "", "DOutputState", pbOut[7].nState);
#endif
}

void stt_xml_serialize_12u12i_pnv(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize_sys_pata("Ua幅值", "_Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ua相位", "_UaPh", "°", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ua频率", "_UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq, STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ub幅值", "_Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ub相位", "_UbPh", "°", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ub频率", "_UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uc幅值", "_Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uc相位", "_UcPh", "°", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Uc频率", "_UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uap幅值", "_Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uap相位", "_UapPh", "°", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Uap频率", "_UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ubp幅值", "_Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ubp相位", "_UbpPh", "°", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ubp频率", "_UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ucp幅值", "_Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ucp相位", "_UcpPh", "°", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ucp频率", "_UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uas幅值", "_Uas", "V", "number", pParas->m_uiVOL[6].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uas相位", "_UasPh", "°", "number", pParas->m_uiVOL[6].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Uas频率", "_UasFre", "Hz", "number", pParas->m_uiVOL[6].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ubs幅值", "_Ubs", "V", "number", pParas->m_uiVOL[7].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ubs相位", "_UbsPh", "°", "number", pParas->m_uiVOL[7].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ubs频率", "_UbsFre", "Hz", "number", pParas->m_uiVOL[7].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ucs幅值", "_Ucs", "V", "number", pParas->m_uiVOL[8].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ucs相位", "_UcsPh", "°", "number", pParas->m_uiVOL[8].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ucs频率", "_UcsFre", "Hz", "number", pParas->m_uiVOL[8].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uat幅值", "_Uat", "V", "number", pParas->m_uiVOL[9].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uat相位", "_UatPh", "°", "number", pParas->m_uiVOL[9].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Uat频率", "_UatFre", "Hz", "number", pParas->m_uiVOL[9].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ubt幅值", "_Ubt", "V", "number", pParas->m_uiVOL[10].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Ubt相位", "_UbtPh", "°", "number", pParas->m_uiVOL[10].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ubt频率", "_UbtFre", "Hz", "number", pParas->m_uiVOL[10].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Uct幅值", "_Uct", "V", "number", pParas->m_uiVOL[11].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
    pXmlSierialize->xml_serialize("Uct相位", "_UctPh", "°", "number", pParas->m_uiVOL[11].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Uct频率", "_UctFre", "Hz", "number", pParas->m_uiVOL[11].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ia幅值", "_Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ia相位", "_IaPh", "°", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ia频率", "_IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ib幅值", "_Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ib相位", "_IbPh", "°", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ib频率", "_IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ic幅值", "_Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ic相位", "_IcPh", "°", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ic频率", "_IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Iap幅值", "_Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Iap相位", "_IapPh", "°", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Iap频率", "_IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ibp幅值", "_Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ibp相位", "_IbpPh", "°", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ibp频率", "_IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Icp幅值", "_Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Icp相位", "_IcpPh", "°", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Icp频率", "_IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ias幅值", "_Ias", "A", "number", pParas->m_uiCUR[6].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ias相位", "_IasPh", "°", "number", pParas->m_uiCUR[6].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ias频率", "_IasFre", "Hz", "number", pParas->m_uiCUR[6].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ibs幅值", "_Ibs", "A", "number", pParas->m_uiCUR[7].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ibs相位", "_IbsPh", "°", "number", pParas->m_uiCUR[7].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ibs频率", "_IbsFre", "Hz", "number", pParas->m_uiCUR[7].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ics幅值", "_Ics", "A", "number", pParas->m_uiCUR[8].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ics相位", "_IcsPh", "°", "number", pParas->m_uiCUR[8].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ics频率", "_IcsFre", "Hz", "number", pParas->m_uiCUR[8].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Iat幅值", "_Iat", "A", "number", pParas->m_uiCUR[9].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Iat相位", "_IatPh", "°", "number", pParas->m_uiCUR[9].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Iat频率", "_IatFre", "Hz", "number", pParas->m_uiCUR[9].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ibt幅值", "_Ibt", "A", "number", pParas->m_uiCUR[10].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ibt相位", "_IbtPh", "°", "number", pParas->m_uiCUR[10].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ibt频率", "_IbtFre", "Hz", "number", pParas->m_uiCUR[10].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
    pXmlSierialize->xml_serialize_sys_pata("Ict幅值", "_Ict", "A", "number", pParas->m_uiCUR[11].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
    pXmlSierialize->xml_serialize("Ict相位", "_IctPh", "°", "number", pParas->m_uiCUR[11].Harm[1].fAngle);
    pXmlSierialize->xml_serialize_sys_pata("Ict频率", "_IctFre", "Hz", "number", pParas->m_uiCUR[11].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#else
	pXmlSierialize->xml_serialize_sys_pata(/*"Ua幅值"*/g_sLangTxt_Native_UaAmplitude.GetString(), "_Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ua相位"*/g_sLangTxt_Native_UaPhase.GetString(), "_UaPh", "°", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ua频率"*/g_sLangTxt_Native_UaFreq.GetString(), "_UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ub幅值"*/g_sLangTxt_Native_UbAmplitude.GetString(), "_Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ub相位"*/g_sLangTxt_Native_UbPhase.GetString(), "_UbPh", "°", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ub频率"*/g_sLangTxt_Native_UbFreq.GetString(), "_UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uc幅值"*/g_sLangTxt_Native_UcAmplitude.GetString(), "_Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uc相位"*/g_sLangTxt_Native_UcPhase.GetString(), "_UcPh", "°", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uc频率"*/g_sLangTxt_Native_UcFreq.GetString(), "_UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uap幅值"*/g_sLangTxt_Native_UapAmp.GetString(), "_Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uap相位"*/g_sLangTxt_Native_UapPhase.GetString(), "_UapPh", "°", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uap频率"*/g_sLangTxt_Native_UapFreq.GetString(), "_UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ubp幅值"*/g_sLangTxt_Native_UbpAmp.GetString(), "_Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ubp相位"*/g_sLangTxt_Native_UbpPhase.GetString(), "_UbpPh", "°", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ubp频率"*/g_sLangTxt_Native_UbpFreq.GetString(), "_UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ucp幅值"*/g_sLangTxt_Native_UcpAmp.GetString(), "_Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ucp相位"*/g_sLangTxt_Native_UcpPhase.GetString(), "_UcpPh", "°", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ucp频率"*/g_sLangTxt_Native_UcpFreq.GetString(), "_UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uas幅值"*/g_sLangTxt_Native_UasAmp.GetString(), "_Uas", "V", "number", pParas->m_uiVOL[6].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uas相位"*/g_sLangTxt_Native_UasPhase.GetString(), "_UasPh", "°", "number", pParas->m_uiVOL[6].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uas频率"*/g_sLangTxt_Native_UasFreq.GetString(), "_UasFre", "Hz", "number", pParas->m_uiVOL[6].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ubs幅值"*/g_sLangTxt_Native_UbsAmp.GetString(), "_Ubs", "V", "number", pParas->m_uiVOL[7].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ubs相位"*/g_sLangTxt_Native_UbsPhase.GetString(), "_UbsPh", "°", "number", pParas->m_uiVOL[7].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ubs频率"*/g_sLangTxt_Native_UbsFreq.GetString(), "_UbsFre", "Hz", "number", pParas->m_uiVOL[7].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ucs幅值"*/g_sLangTxt_Native_UcsAmp.GetString(), "_Ucs", "V", "number", pParas->m_uiVOL[8].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ucs相位"*/g_sLangTxt_Native_UcsPhase.GetString(), "_UcsPh", "°", "number", pParas->m_uiVOL[8].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ucs频率"*/g_sLangTxt_Native_UcsFreq.GetString(), "_UcsFre", "Hz", "number", pParas->m_uiVOL[8].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uat幅值"*/g_sLangTxt_Native_UatAmp.GetString(), "_Uat", "V", "number", pParas->m_uiVOL[9].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uat相位"*/g_sLangTxt_Native_UatPhase.GetString(), "_UatPh", "°", "number", pParas->m_uiVOL[9].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uat频率"*/g_sLangTxt_Native_UatFreq.GetString(), "_UatFre", "Hz", "number", pParas->m_uiVOL[9].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ubt幅值"*/g_sLangTxt_Native_UbtAmp.GetString(), "_Ubt", "V", "number", pParas->m_uiVOL[10].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Ubt相位"*/g_sLangTxt_Native_UbtPhase.GetString(), "_UbtPh", "°", "number", pParas->m_uiVOL[10].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ubt频率"*/g_sLangTxt_Native_UbtFreq.GetString(), "_UbtFre", "Hz", "number", pParas->m_uiVOL[10].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uct幅值"*/g_sLangTxt_Native_UctAmp.GetString(), "_Uct", "V", "number", pParas->m_uiVOL[11].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	pXmlSierialize->xml_serialize(/*"Uct相位"*/g_sLangTxt_Native_UctPhase.GetString(), "_UctPh", "°", "number", pParas->m_uiVOL[11].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Uct频率"*/g_sLangTxt_Native_UctFreq.GetString(), "_UctFre", "Hz", "number", pParas->m_uiVOL[11].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ia幅值"*/g_sLangTxt_Native_IaAmp.GetString(), "_Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ia相位"*/g_sLangTxt_Native_IaPhase.GetString(), "_IaPh", "°", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ia频率"*/g_sLangTxt_Native_IaFreq.GetString(), "_IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ib幅值"*/g_sLangTxt_Native_IbAmp.GetString(), "_Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ib相位"*/g_sLangTxt_Native_IbPhase.GetString(), "_IbPh", "°", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ib频率"*/g_sLangTxt_Native_IbFreq.GetString(), "_IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ic幅值"*/g_sLangTxt_Native_IcAmp.GetString(), "_Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ic相位"*/g_sLangTxt_Native_IcPhase.GetString(), "_IcPh", "°", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ic频率"*/g_sLangTxt_Native_IcFreq.GetString(), "_IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Iap幅值"*/g_sLangTxt_Native_IapAmp.GetString(), "_Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Iap相位"*/g_sLangTxt_Native_IapPhase.GetString(), "_IapPh", "°", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Iap频率"*/g_sLangTxt_Native_IapFreq.GetString(), "_IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ibp幅值"*/g_sLangTxt_Native_IbpAmp.GetString(), "_Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ibp相位"*/g_sLangTxt_Native_IbpPhase.GetString(), "_IbpPh", "°", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ibp频率"*/g_sLangTxt_Native_IbpFreq.GetString(), "_IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Icp幅值"*/g_sLangTxt_Native_IcpAmp.GetString(), "_Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Icp相位"*/g_sLangTxt_Native_IcpPhase.GetString(), "_IcpPh", "°", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Icp频率"*/g_sLangTxt_Native_IcpFreq.GetString(), "_IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ias幅值"*/g_sLangTxt_Native_IasAmp.GetString(), "_Ias", "A", "number", pParas->m_uiCUR[6].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ias相位"*/g_sLangTxt_Native_IasPhase.GetString(), "_IasPh", "°", "number", pParas->m_uiCUR[6].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ias频率"*/g_sLangTxt_Native_IasFreq.GetString(), "_IasFre", "Hz", "number", pParas->m_uiCUR[6].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ibs幅值"*/g_sLangTxt_Native_IbsAmp.GetString(), "_Ibs", "A", "number", pParas->m_uiCUR[7].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ibs相位"*/g_sLangTxt_Native_IbsPhase.GetString(), "_IbsPh", "°", "number", pParas->m_uiCUR[7].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ibs频率"*/g_sLangTxt_Native_IbsFreq.GetString(), "_IbsFre", "Hz", "number", pParas->m_uiCUR[7].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ics幅值"*/g_sLangTxt_Native_IcsAmp.GetString(), "_Ics", "A", "number", pParas->m_uiCUR[8].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ics相位"*/g_sLangTxt_Native_IcsPhase.GetString(), "_IcsPh", "°", "number", pParas->m_uiCUR[8].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ics频率"*/g_sLangTxt_Native_IcsFreq.GetString(), "_IcsFre", "Hz", "number", pParas->m_uiCUR[8].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Iat幅值"*/g_sLangTxt_Native_IatAmp.GetString(), "_Iat", "A", "number", pParas->m_uiCUR[9].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Iat相位"*/g_sLangTxt_Native_IatPhase.GetString(), "_IatPh", "°", "number", pParas->m_uiCUR[9].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Iat频率"*/g_sLangTxt_Native_IatFreq.GetString(), "_IatFre", "Hz", "number", pParas->m_uiCUR[9].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ibt幅值"*/g_sLangTxt_Native_IbtAmp.GetString(), "_Ibt", "A", "number", pParas->m_uiCUR[10].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ibt相位"*/g_sLangTxt_Native_IbtPhase.GetString(), "_IbtPh", "°", "number", pParas->m_uiCUR[10].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ibt频率"*/g_sLangTxt_Native_IbtFreq.GetString(), "_IbtFre", "Hz", "number", pParas->m_uiCUR[10].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ict幅值"*/g_sLangTxt_Native_IctAmp.GetString(), "_Ict", "A", "number", pParas->m_uiCUR[11].Harm[1].fAmp, STT_XML_SERIALIZE_SYS_PARA_ID_INom);
	pXmlSierialize->xml_serialize(/*"Ict相位"*/g_sLangTxt_Native_IctPhase.GetString(), "_IctPh", "°", "number", pParas->m_uiCUR[11].Harm[1].fAngle);
	pXmlSierialize->xml_serialize_sys_pata(/*"Ict频率"*/g_sLangTxt_Native_IctFreq.GetString(), "_IctFre", "Hz", "number", pParas->m_uiCUR[11].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
#endif
    //新版序列化,U1~U18,i1~i18
    CString strID;
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("是否开入停止", "bBinStop", "", "BOOL", pParas->m_bBinStop);
    //	pXmlSierialize->xml_serialize("过载延时","fOverload","s","number",pParas->m_fOverloadDelaytime);
    pXmlSierialize->xml_serialize("是否以直流模式输出", "bDC", "", "BOOL", pParas->m_bDC);
    pXmlSierialize->xml_serialize("是否老化试验", "bAging", "", "BOOL", pParas->m_bAging);
    pXmlSierialize->xml_serialize("辅助直流电流", "fCurAux", "mA", "number", pParas->m_fCurAux);
    pXmlSierialize->xml_serialize("辅助直流电压", "_UdcAux", "V", "number", pParas->m_fVolAux);
    pXmlSierialize->xml_serialize("递变通道选择", "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize("递变类型选择", "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
    pXmlSierialize->xml_serialize("变化模式", "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
    pXmlSierialize->xml_serialize("变化始值", "Start", "", "number", pParas->m_manuGradient.fStart);
    pXmlSierialize->xml_serialize("变化终值", "End", "", "number", pParas->m_manuGradient.fEnd);
    pXmlSierialize->xml_serialize("变化步长", "Step", "", "number", pParas->m_manuGradient.fStep);
    pXmlSierialize->xml_serialize("每步时间", "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
    pXmlSierialize->xml_serialize("触发延时", "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	// pXmlSierialize->xml_serialize("变化谐波次数", "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
    pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"是否开入停止"*/g_sLangTxt_Native_YNInputStop.GetString(), "bBinStop", "", "BOOL", pParas->m_bBinStop);
	//	pXmlSierialize->xml_serialize("过载延时","fOverload","s","number",pParas->m_fOverloadDelaytime);
	pXmlSierialize->xml_serialize(/*"是否以直流模式输出"*/g_sLangTxt_Native_DCOutputMode.GetString(), "bDC", "", "BOOL", pParas->m_bDC);
	pXmlSierialize->xml_serialize(/*"是否老化试验"*/g_sLangTxt_Native_YNaging_test.GetString(), "bAging", "", "BOOL", pParas->m_bAging);
	pXmlSierialize->xml_serialize(/*"辅助直流电流"*/g_sLangTxt_Native_AuxiDCI.GetString(), "fCurAux", "mA", "number", pParas->m_fCurAux);
	pXmlSierialize->xml_serialize(/*"辅助直流电压"*/g_sLangTxt_Native_AuxiDCV.GetString(), "_UdcAux", "V", "number", pParas->m_fVolAux);
	pXmlSierialize->xml_serialize(/*"递变通道选择"*/g_sLangTxt_Native_varchannel_select.GetString(), "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
	pXmlSierialize->xml_serialize(/*"递变类型选择"*/g_sLangTxt_Native_vartype_select.GetString(), "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
	pXmlSierialize->xml_serialize(/*"变化模式"*/g_sLangTxt_Native_change_mode.GetString(), "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
	pXmlSierialize->xml_serialize(/*"变化始值"*/g_sLangTxt_Gradient_Init.GetString(), "Start", "", "number", pParas->m_manuGradient.fStart);
	pXmlSierialize->xml_serialize(/*"变化终值"*/g_sLangTxt_Gradient_Finish.GetString(), "End", "", "number", pParas->m_manuGradient.fEnd);
	pXmlSierialize->xml_serialize(/*"变化步长"*/g_sLangTxt_Gradient_Step.GetString(), "Step", "", "number", pParas->m_manuGradient.fStep);
	pXmlSierialize->xml_serialize(/*"每步时间"*/g_sLangTxt_Native_step_time.GetString(), "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
	pXmlSierialize->xml_serialize(/*"触发延时"*/g_sLangTxt_Native_trigger_delay.GetString(), "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
	// pXmlSierialize->xml_serialize(/*"变化谐波次数"*/g_sLangTxt_Native_VarHarmonicNum.GetString(), "Harm", "", "number", pParas->m_manuGradient.nHarmIndex);
	pXmlSierialize->xml_serialize(/*"开入逻辑"*/g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_binary_out_Pnv(pParas->m_binOut, pXmlSierialize);
    //Ex
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);
    stt_xml_serialize_dc(pParas, pXmlSierialize);
    //	stt_xml_serialize_Aging(pParas,pXmlSierialize);  zhouhj 20210828 重复串行化
    //	stt_xml_serialize_Lock(pParas,pXmlSierialize);
    //	stt_xml_serialize_Auto(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("是否锁定", "_bLock", "", "BOOL", pParas->m_bLockChanged);
    pXmlSierialize->xml_serialize("是否自动递变", "_bAuto", "", "BOOL", pParas->m_bAuto);
#else
	pXmlSierialize->xml_serialize(/*"是否锁定"*/g_sLangTxt_Native_YN_locked.GetString(), "_bLock", "", "BOOL", pParas->m_bLockChanged);
	pXmlSierialize->xml_serialize(/*"是否自动递变"*/g_sLangTxt_Native_YN_autoevo.GetString(), "_bAuto", "", "BOOL", pParas->m_bAuto);
#endif
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
        stt_xml_serialize(&pParas->m_oFt3Pub[0], pXmlSierialize);
        stt_xml_serialize(&pParas->m_o2MOnePortPub[0], pXmlSierialize);
    }

// 	stt_xml_serialize_Harm(pParas,pXmlSierialize,nVolRsNum,nCurRsNum);//叠加谐波
//
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("最长输出时间(s)", "_TimeMax", " ", "number", pParas->m_fOutPutTime);
#else
	pXmlSierialize->xml_serialize(/*"最长输出时间(s)"*/g_sLangTxt_Native_max_outputtime.GetString(), "_TimeMax", " ", "number", pParas->m_fOutPutTime);
#endif
// 	//	pXmlSierialize->xml_serialize("开始测试时上送报告", "UploadRpt_Started"," ","number",pParas->m_nUploadRpt_Started);
//
// 	if (pParas->m_nFuncType>TMT_MANU_FUNC_TYPE_Common)
// 	{
// 		stt_xml_serialize_MU(&pParas->m_oMuParas,pXmlSierialize);// 合并单元测试
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

