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
	pXmlSierialize->xml_serialize("项目名称", "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "Ω", "set", pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("变化起始角度", "BeginValAng", "°", "set",pParas->m_fScanFromAngle);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "Ω", "set", pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("变化终止角度", "EndValAng", "°", "set", pParas->m_fScanToAngle);
	pXmlSierialize->xml_serialize("测试精度","Step", "Ω", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize("故障类型", "FaultType", "无", "SystemFault", pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("整定动作时间", "TSetting", "s", "set",pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("短路电流", "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("短路电压", "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
 	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);//参数固定
 	pXmlSierialize->xml_serialize("故障性质","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);//参数固定
	pXmlSierialize->xml_serialize("待测定值", "ValSetting", "Ω", "set", pParas->m_fSetting[0]);//阻抗定值
	pXmlSierialize->xml_serialize("待测阻抗角度定值", "ValSettingAngle", "°", "set", pParas->m_fSetting[1]);//阻抗角度
	pXmlSierialize->xml_serialize("搜索方式", "SearchMode", " ", "SearchModePnv", pParas->m_nSearchMode);

	pXmlSierialize->xml_serialize("保护动作后持续时间","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
    pXmlSierialize->xml_serialize("额定电压","UNom","V","number",pParas->m_fUNom);
#else
	pXmlSierialize->xml_serialize(/* "项目名称" */g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "Ω", "set", pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize(/* "变化起始角度" */g_sLangTxt_Native_change_startangle.GetString(), "BeginValAng", "°", "set",pParas->m_fScanFromAngle);
	pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "Ω", "set", pParas->m_fScanTo);
	pXmlSierialize->xml_serialize(/* "变化终止角度" */g_sLangTxt_Native_change_endangle.GetString(), "EndValAng", "°", "set", pParas->m_fScanToAngle);
	pXmlSierialize->xml_serialize(/* "测试精度" */g_sLangTxt_Native_TestPrecision.GetString(),"Step", "Ω", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "无", "SystemFault", pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "整定动作时间" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set",pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "短路电流" */g_sLangTxt_Native_ShortCircuit.GetString(), "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "短路电压" */g_sLangTxt_Native_ShortCircuitV.GetString(), "FaultVf", "V", "number", pParas->m_fSCVoltage[0]);
 	pXmlSierialize->xml_serialize(/* "故障方向" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);//参数固定
 	pXmlSierialize->xml_serialize(/* "故障性质" */g_sLangTxt_Native_FaultProp.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);//参数固定
	pXmlSierialize->xml_serialize(/* "待测定值" */g_sLangTxt_Native_UnderTestValue.GetString(), "ValSetting", "Ω", "set", pParas->m_fSetting[0]);//阻抗定值
	pXmlSierialize->xml_serialize(/* "待测阻抗角度定值" */g_sLangTxt_Native_impedanceAng_measured.GetString(), "ValSettingAngle", "°", "set", pParas->m_fSetting[1]);//阻抗角度
	pXmlSierialize->xml_serialize(/* "搜索方式" */g_sLangTxt_Native_search_way.GetString(), "SearchMode", " ", "SearchModePnv", pParas->m_nSearchMode);

	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);
	BOOL bFind = pXmlSierialize->xml_serialize("常态时间","PrepareTime","s","number",pParas->m_fPrepareTime);//距离搜索专用，第一次故障前时间

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
    pXmlSierialize->xml_serialize("开入A", "BinA", "", "DInputState", pParas->m_nBinState[0]);
    pXmlSierialize->xml_serialize("开入B", "BinB", "", "DInputState", pParas->m_nBinState[1]);
    pXmlSierialize->xml_serialize("开入C", "BinC", "", "DInputState", pParas->m_nBinState[2]);
    pXmlSierialize->xml_serialize("开入D", "BinD", "", "DInputState", pParas->m_nBinState[3]);
    pXmlSierialize->xml_serialize("开入E", "BinE", "", "DInputState", pParas->m_nBinState[4]);
    pXmlSierialize->xml_serialize("开入F", "BinF", "", "DInputState", pParas->m_nBinState[5]);
    pXmlSierialize->xml_serialize("开入G", "BinG", "", "DInputState", pParas->m_nBinState[6]);
    pXmlSierialize->xml_serialize("开入H", "BinH", "", "DInputState", pParas->m_nBinState[7]);
    pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic", pParas->m_nBinLogic);
#else
#endif

}
void stt_xml_serialize_SearchReport(tmt_DistanceSearchParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("搜索起点","SearchBegin","Ω","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize("Z搜索起点角度","SearchBeginAngle","°","number",pParas->m_fSearchBeginAngle);
	pXmlSierialize->xml_serialize("Z搜索起点动作","SearchBeginAct","°","number",pParas->m_nTripFlagFrom);
	pXmlSierialize->xml_serialize("当前值","CurrSearchVal","Ω","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("Z当前值角度","CurrSearchValAngle","°","number",pParas->m_fCurrScanValAngle);
	pXmlSierialize->xml_serialize("搜索终点","SearchEnd","Ω","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize("Z搜索终点角度","SearchEndAngle","°","number",pParas->m_fSearchEndAngle);
	pXmlSierialize->xml_serialize("Z搜索终点动作","SearchEndAct","°","number",pParas->m_nTripFlagTo);
	pXmlSierialize->xml_serialize("搜索区间长度","SearchArea","","number",pParas->m_fSearchArea);
#else
	pXmlSierialize->xml_serialize(/* "搜索起点" */g_sLangTxt_Native_SearchStart.GetString(),"SearchBegin","Ω","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize(/* "Z搜索起点角度" */g_sLangTxt_Native_Zsearch_startAng.GetString(),"SearchBeginAngle","°","number",pParas->m_fSearchBeginAngle);
	pXmlSierialize->xml_serialize(/* "Z搜索起点动作" */g_sLangTxt_Native_Zsearch_startAct.GetString(),"SearchBeginAct","°","number",pParas->m_nTripFlagFrom);
	pXmlSierialize->xml_serialize(/* "当前值" */g_sLangTxt_Native_CurrentValue.GetString(),"CurrSearchVal","Ω","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize(/* "Z当前值角度" */g_sLangTxt_Native_ZAng_currentVal.GetString(),"CurrSearchValAngle","°","number",pParas->m_fCurrScanValAngle);
	pXmlSierialize->xml_serialize(/* "搜索终点" */g_sLangTxt_Native_SearchEnd.GetString(),"SearchEnd","Ω","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize(/* "Z搜索终点角度" */g_sLangTxt_Native_Zsearch_endAng.GetString(),"SearchEndAngle","°","number",pParas->m_fSearchEndAngle);
	pXmlSierialize->xml_serialize(/* "Z搜索终点动作" */g_sLangTxt_Native_Zsearch_endAct.GetString(),"SearchEndAct","°","number",pParas->m_nTripFlagTo);
	pXmlSierialize->xml_serialize(/* "搜索区间长度" */g_sLangTxt_Native_SearchLen.GetString(),"SearchArea","","number",pParas->m_fSearchArea);
#endif

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_Search(tmt_DistanceSearchResults *pResults, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作阻抗", "TripZ", "Ω", "number", pResults->m_fImp);
	pXmlSierialize->xml_serialize("动作阻抗角", "TripZAngle", "°", "number", pResults->m_fImpAngle);
	pXmlSierialize->xml_serialize("阻抗动作描述", "ActZ", "", "number", pResults->m_nActZ);
#else
	pXmlSierialize->xml_serialize(/* "动作阻抗" */g_sLangTxt_Native_action_impedance.GetString(), "TripZ", "Ω", "number", pResults->m_fImp);
	pXmlSierialize->xml_serialize(/* "动作阻抗角" */g_sLangTxt_Native_action_impedanceAng.GetString(), "TripZAngle", "°", "number", pResults->m_fImpAngle);
	pXmlSierialize->xml_serialize(/* "阻抗动作描述" */g_sLangTxt_Native_Desc_impedance_Act.GetString(), "ActZ", "", "number", pResults->m_nActZ);
#endif

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceSearchTest *pTests, CSttXmlSerializeBase *pXmlSerialize,long nBinExNum,long nBoutExNum)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_Search(&(pTests->m_oDistanceSearchParas), pXmlParas,nBinExNum,nBoutExNum);	//文件的读写
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize_Search(&(pTests->m_oDistanceSearchParas), pXmlParas,nBinExNum,nBoutExNum);	//测试参数下发
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
            stt_xml_serialize_Search(&(pTests->m_oDistanceSearchParas), pXmlParas,nBinExNum,nBoutExNum);	//文件的读写
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize_Search(&(pTests->m_oDistanceSearchParas), pXmlParas,nBinExNum,nBoutExNum);	//测试参数下发
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
