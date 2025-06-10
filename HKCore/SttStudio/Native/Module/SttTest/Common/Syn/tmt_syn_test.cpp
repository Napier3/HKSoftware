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
	//整定值
	pXmlSierialize->xml_serialize("导前角", "LAngle", "°", "number", pParas->m_fLAngle);
	pXmlSierialize->xml_serialize("导前时间", "LTime", "s", "number", pParas->m_fLTime);
	pXmlSierialize->xml_serialize("允许压差", "dVzd", "V", "number", pParas->m_fdVzd);
	pXmlSierialize->xml_serialize("允许频差", "dFzd", "Hz", "number", pParas->m_fdFzd);
	pXmlSierialize->xml_serialize("调压周期", "Ut", "s", "number", pParas->m_fUt);
	pXmlSierialize->xml_serialize("调频周期", "Ft", "s", "number", pParas->m_fFt);

	//通用参数
	pXmlSierialize->xml_serialize("系统侧额定电压", "Us", "V", "number", pParas->m_fVs_Mag);
	pXmlSierialize->xml_serialize("系统侧额定频率", "Fs", "Hz", "number", pParas->m_fVs_Fre);
	pXmlSierialize->xml_serialize("待并侧额定电压", "Ug", "V", "number", pParas->m_fVg_Std);
	pXmlSierialize->xml_serialize("电压定义", "UgConnectDef", "", "SynVolDef", pParas->m_nVolDefType);
	pXmlSierialize->xml_serialize("参考相", "Vref", "", "SynVolRef", pParas->m_nRefVolType);

    pXmlSierialize->xml_serialize("测试绕组之间角差（钟点数）", "WindAngs", "", "number", pParas->m_nWindAngs);
    pXmlSierialize->xml_serialize("两侧相位差", "PhaseDiff", "", "number", pParas->m_fPhaseDiff);
	pXmlSierialize->xml_serialize("变压器接线方式", "TansConnect", "", "SynTConnMode", pParas->m_nTransConnMode);
	pXmlSierialize->xml_serialize("最大同步时间", "Tmax", "", "number", pParas->m_fMaxSynTime);

	//开关量
	pXmlSierialize->xml_serialize("开出4输出方式", "KStart", "", "SynBoutType", pParas->m_nBoutType);
	pXmlSierialize->xml_serialize("开出4保持时间", "CloseTime", "", "number", pParas->m_fBoutKeepTime);


	pXmlSierialize->xml_serialize("待并侧电压", "UgStart", "", "number", pParas->m_fVg_Mag);
	pXmlSierialize->xml_serialize("待并侧频率", "FgStart", "", "number", pParas->m_fVg_Fre);


    pXmlSierialize->xml_serialize("同期信号", "_BinSyn", "", "number", pParas->m_binIn_Syn);
    pXmlSierialize->xml_serialize("增压信号", "_BinIncV", "", "number", pParas->m_binIn_IncV);
    pXmlSierialize->xml_serialize("增频信号", "_BinIncF", "", "number", pParas->m_binIn_IncF);
    pXmlSierialize->xml_serialize("减压信号", "_BinDecV", "", "number", pParas->m_binIn_DecV);
    pXmlSierialize->xml_serialize("减频信号", "_BinDecF", "", "number", pParas->m_binIn_DecF);

	CString strName,strID;
	for(int nIndex=0;nIndex<8;nIndex++)
	{
		strName.Format(_T("开出%d"),nIndex+1);
		strID.Format(_T("_Bout%d"),nIndex+1);
		pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "long", pParas->m_binOut[nIndex]);
	}

#else
	//整定值
	pXmlSierialize->xml_serialize( /* "导前角" */g_sLangTxt_LeadingAngle.GetString() , "LAngle", "°", "number", pParas->m_fLAngle);
	pXmlSierialize->xml_serialize( /* "导前时间"  */g_sLangTxt_LeadingTime.GetString(), "LTime", "s", "number", pParas->m_fLTime);
	pXmlSierialize->xml_serialize( /* "允许压差"  */g_sLangTxt_Allow_VolDifference.GetString(), "dVzd", "V", "number", pParas->m_fdVzd);
	pXmlSierialize->xml_serialize( /* "允许频差" */g_sLangTxt_Allow_FreqDifference.GetString() , "dFzd", "Hz", "number", pParas->m_fdFzd);
	pXmlSierialize->xml_serialize( /* "调压周期" */g_sLangTxt_Vol_ReguPeriod.GetString() , "Ut", "s", "number", pParas->m_fUt);
	pXmlSierialize->xml_serialize( /* "调频周期" */g_sLangTxt_Freq_ReguPeriod.GetString() , "Ft", "s", "number", pParas->m_fFt);

	//通用参数
	pXmlSierialize->xml_serialize(/* "系统侧额定电压" */g_sLangTxt_System_Rated_Voltage.GetString() , "Us", "V", "number", pParas->m_fVs_Mag);
	pXmlSierialize->xml_serialize(/* "系统侧额定频率" */g_sLangTxt_System_Rated_Frequency.GetString() , "Fs", "Hz", "number", pParas->m_fVs_Fre);
	pXmlSierialize->xml_serialize(/* "待并侧额定电压" */g_sLangTxt_Grid_Rated_Voltage.GetString() , "Ug", "V", "number", pParas->m_fVg_Std);
	pXmlSierialize->xml_serialize(/* "电压定义" */g_sLangTxt_Native_volDefinition1.GetString() , "UgConnectDef", "", "SynVolDef", pParas->m_nVolDefType);
	pXmlSierialize->xml_serialize(/* "参考相" */g_sLangTxt_Native_refphase.GetString() , "Vref", "", "SynVolRef", pParas->m_nRefVolType);

	pXmlSierialize->xml_serialize(/* "变压器接线方式" */g_sLangTxt_Native_transfConnection.GetString() , "TansConnect", "", "SynTConnMode", pParas->m_nTransConnMode);
	pXmlSierialize->xml_serialize(/* "最大同步时间" */g_sLangTxt_Native_maxSyncTime.GetString() , "Tmax", "", "number", pParas->m_fMaxSynTime);

	//开关量
	pXmlSierialize->xml_serialize(/* "开出4输出方式" */g_sLangTxt_Out4_Mode.GetString() , "KStart", "", "SynBoutType", pParas->m_nBoutType);
	pXmlSierialize->xml_serialize(/* "开出4保持时间" */g_sLangTxt_Native_breaker4HoldTime.GetString() , "CloseTime", "", "number", pParas->m_fBoutKeepTime);


	pXmlSierialize->xml_serialize(/* "待并侧电压" */g_sLangTxt_Native_Grid_Vol.GetString(), "UgStart", "", "number", pParas->m_fVg_Mag);
	pXmlSierialize->xml_serialize(/* "待并侧频率" */g_sLangTxt_Grid_FreqHZ.GetString(), "FgStart", "", "number", pParas->m_fVg_Fre);


    pXmlSierialize->xml_serialize(/* "同期信号" */g_sLangTxt_Native_syncSignal.GetString(), "_BinSyn", "", "number", pParas->m_binIn_Syn);
    pXmlSierialize->xml_serialize(/* "增压信号" */g_sLangTxt_Native_boostSignal.GetString(), "_BinIncV", "", "number", pParas->m_binIn_IncV);
    pXmlSierialize->xml_serialize(/* "增频信号" */g_sLangTxt_Native_boostFreqSignal.GetString(), "_BinIncF", "", "number", pParas->m_binIn_IncF);
    pXmlSierialize->xml_serialize(/* "减压信号" */g_sLangTxt_Native_reducePresSignal.GetString(), "_BinDecV", "", "number", pParas->m_binIn_DecV);
    pXmlSierialize->xml_serialize(/* "减频信号" */g_sLangTxt_Native_reduceFreqSignal.GetString(), "_BinDecF", "", "number", pParas->m_binIn_DecF);

	CString strName,strID;
	for(int nIndex=0;nIndex<8;nIndex++)
	{
		strName.Format(/* _T("开出%d") */g_sLangTxt_Native_OutPut.GetString(),nIndex+1);
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
	pXmlSierialize->xml_serialize("待并侧电压变化步长", "UgMagStep", "", "number", pParas->m_fDvStep);

	stt_xml_serialize_common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "待并侧电压变化步长" */g_sLangTxt_Native_GvolChangeStep.GetString(), "UgMagStep", "", "number", pParas->m_fDvStep);

	stt_xml_serialize_common(pParas,pXmlSierialize);
#endif
}

void stt_xml_serialize_ActVolEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("待并侧电压(表达式)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("待并侧频率(表达式)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);
	pXmlSierialize->xml_serialize("待并侧电压变化步长(表达式)", "UgMagStepExp", "", "string",  pParas->m_pszDvStep);
	stt_xml_serialize_ActVol(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "待并侧电压(表达式)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "待并侧频率(表达式)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);
	pXmlSierialize->xml_serialize(/* "待并侧电压变化步长(表达式)" */g_sLangTxt_Native_GvolChangeStepExp.GetString(), "UgMagStepExp", "", "string",  pParas->m_pszDvStep);
	stt_xml_serialize_ActVol(pParas,pXmlSierialize);
#endif
}

void stt_xml_serialize_ActFreq(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("待并侧频率变化步长", "UgFreqStep", "", "number", pParas->m_fDfStep);

    stt_xml_serialize_common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "待并侧频率变化步长" */g_sLangTxt_Native_GfreqChangeStep.GetString(), "UgFreqStep", "", "number", pParas->m_fDfStep);

    stt_xml_serialize_common(pParas,pXmlSierialize);
#endif
}

void stt_xml_serialize_ActFreqEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("待并侧电压(表达式)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("待并侧频率(表达式)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);
	pXmlSierialize->xml_serialize("待并侧频率变化步长(表达式)", "UgFreqStepExp", "", "string", pParas->m_pszDfStep);

	stt_xml_serialize_ActFreq(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "待并侧电压(表达式)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "待并侧频率(表达式)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);
	pXmlSierialize->xml_serialize(/* "待并侧频率变化步长(表达式)" */g_sLangTxt_Native_GfreqChangeStepExp.GetString(), "UgFreqStepExp", "", "string", pParas->m_pszDfStep);

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
	pXmlSierialize->xml_serialize("待并侧电压(表达式)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("待并侧频率(表达式)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_LeadAng(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "待并侧电压(表达式)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "待并侧频率(表达式)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_LeadAng(pParas,pXmlSierialize);
#endif

}


void stt_xml_serialize_AutoAdj(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压滑差", "DvDt", "", "number", pParas->m_fdVg_dt);
	pXmlSierialize->xml_serialize("频率滑差", "DfDt", "", "number", pParas->m_fdFg_dt);

    stt_xml_serialize_common(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "电压滑差" */g_sLangTxt_Native_VoltSlip.GetString(), "DvDt", "", "number", pParas->m_fdVg_dt);
	pXmlSierialize->xml_serialize(/* "频率滑差" */g_sLangTxt_Native_FreqSlip.GetString(), "DfDt", "", "number", pParas->m_fdFg_dt);

    stt_xml_serialize_common(pParas,pXmlSierialize);
#endif

}

void stt_xml_serialize_AutoAdjEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("待并侧电压(表达式)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("待并侧频率(表达式)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	pXmlSierialize->xml_serialize("电压滑差(表达式)", "DvDtExp", "", "string", pParas->m_pszdVg_dt);
	pXmlSierialize->xml_serialize("频率滑差(表达式)", "DfDtExp", "", "string", pParas->m_pszdFg_dt);

	stt_xml_serialize_AutoAdj(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "待并侧电压(表达式)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "待并侧频率(表达式)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	pXmlSierialize->xml_serialize(/* "电压滑差(表达式)" */g_sLangTxt_Native_VoltSlip.GetString(), "DvDtExp", "", "string", pParas->m_pszdVg_dt);
	pXmlSierialize->xml_serialize(/* "频率滑差(表达式)" */g_sLangTxt_Native_FreqSlip_Exp.GetString(), "DfDtExp", "", "string", pParas->m_pszdFg_dt);

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
	pXmlSierialize->xml_serialize("待并侧电压(表达式)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("待并侧频率(表达式)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_AdjVolCycle(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "待并侧电压(表达式)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "待并侧频率(表达式)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);

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
	pXmlSierialize->xml_serialize("待并侧电压(表达式)", "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize("待并侧频率(表达式)", "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_AdjFreqCycle(pParas,pXmlSierialize);
#else
	pXmlSierialize->xml_serialize(/* "待并侧电压(表达式)" */g_sLangTxt_Native_GridVol_Exp.GetString(), "UgStartExp", "", "string", pParas->m_pszVg_Mag);
	pXmlSierialize->xml_serialize(/* "待并侧频率(表达式)" */g_sLangTxt_Native_GridFreq_Exp.GetString(), "FgStartExp", "", "string", pParas->m_pszVg_Freq);

	stt_xml_serialize_AdjFreqCycle(pParas,pXmlSierialize);
#endif

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_ActVol(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
 	pXmlSierialize->xml_serialize("电压边界值", "VolBordValue", "", "number",pResults->m_fVolBordValue);
	pXmlSierialize->xml_serialize("压差", "VolDeltValue", "", "number",pResults->m_fVolDelt);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
 	pXmlSierialize->xml_serialize(/* "电压边界值" */g_sLangTxt_Vol_BoundValue.GetString(), "VolBordValue", "", "number",pResults->m_fVolBordValue);
	pXmlSierialize->xml_serialize(/* "压差" */g_sLangTxt_VolDif.GetString(), "VolDeltValue", "", "number",pResults->m_fVolDelt);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_ActFreq(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("频率边界值", "FreqBordValue", "", "number",pResults->m_fFreqBordValue);
	pXmlSierialize->xml_serialize("频差", "FreqDeltValue", "", "number",pResults->m_fFreqDelt);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "频率边界值" */g_sLangTxt_Freq_BoundValue.GetString(), "FreqBordValue", "", "number",pResults->m_fFreqBordValue);
	pXmlSierialize->xml_serialize(/* "频差" */g_sLangTxt_FreqDif.GetString(), "FreqDeltValue", "", "number",pResults->m_fFreqDelt);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_LeadAng(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("导前角", "LeaderAngle", "", "number",pResults->m_fLeaderAngle);
    pXmlSierialize->xml_serialize("导前时间", "LeaderTime", "", "number",pResults->m_fLeaderTime);
    pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
    pXmlSierialize->xml_serialize(/* "导前角" */g_sLangTxt_LeadingAngle.GetString(), "LeaderAngle", "", "number",pResults->m_fLeaderAngle);
    pXmlSierialize->xml_serialize(/* "导前时间" */g_sLangTxt_LeadingTime.GetString(), "LeaderTime", "", "number",pResults->m_fLeaderTime);
    pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_AutoAdj(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("压差", "VolDeltValue", "", "number",pResults->m_fVolDelt);
	pXmlSierialize->xml_serialize("频差", "FreqDeltValue", "", "number",pResults->m_fFreqDelt);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "压差" */g_sLangTxt_VolDif.GetString(), "VolDeltValue", "", "number",pResults->m_fVolDelt);
	pXmlSierialize->xml_serialize(/* "频差" */g_sLangTxt_FreqDif.GetString(), "FreqDeltValue", "", "number",pResults->m_fFreqDelt);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

void stt_xml_serialize_AdjVolCycle(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("调压周期", "AdjVolCycle", "", "number",pResults->m_fUAdjTime);
	pXmlSierialize->xml_serialize("调压脉宽", "AdjVolWidth", "", "number",pResults->m_fUAdjWidth);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "调压周期" */g_sLangTxt_Vol_ReguPeriod.GetString(), "AdjVolCycle", "", "number",pResults->m_fUAdjTime);
	pXmlSierialize->xml_serialize(/* "调压脉宽" */g_sLangTxt_Native_RegulatePulseWidth.GetString(), "AdjVolWidth", "", "number",pResults->m_fUAdjWidth);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}


void stt_xml_serialize_AdjFreqCycle(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("调频周期", "AdjFreqCycle", "", "number",pResults->m_fFAdjTime);
	pXmlSierialize->xml_serialize("调频脉宽", "AdjFreqWidth", "", "number",pResults->m_fFAdjWidth);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "调频周期" */g_sLangTxt_Freq_ReguPeriod.GetString(), "AdjFreqCycle", "", "number",pResults->m_fFAdjTime);
	pXmlSierialize->xml_serialize(/* "调频脉宽" */g_sLangTxt_Native_RegulatePulseWidth.GetString(), "AdjFreqWidth", "", "number",pResults->m_fFAdjWidth);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
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
