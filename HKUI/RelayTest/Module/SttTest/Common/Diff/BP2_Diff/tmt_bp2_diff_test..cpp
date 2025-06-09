#include "stdafx.h"
#include "tmt_bp2_diff_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_BP2DiffParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_BP2DiffParas));
	pParas->init();
}

void stt_init_results(tmt_BP2DiffResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_BP2DiffResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_diff_search_results(tmt_BP2DiffParas *pParas,tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("搜索起点","SearchBegin","","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize("当前值","CurrSearchVal","","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("搜索终点","SearchEnd","","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize("搜索区间长度","SearchArea","","number",pParas->m_fSearchArea);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
#else
  pXmlSierialize->xml_serialize(/* "搜索起点" */ g_sLangTxt_Native_SearchStart.GetString(), "SearchBegin", "", "number", pParas->m_fSearchBegin);
  pXmlSierialize->xml_serialize(/* "当前值" */ g_sLangTxt_Native_CurrentValue.GetString(), "CurrSearchVal", "", "number", pParas->m_fCurrScanVal);
  pXmlSierialize->xml_serialize(/* "搜索终点" */ g_sLangTxt_Native_SearchEnd.GetString(), "SearchEnd", "", "number", pParas->m_fSearchEnd);
  pXmlSierialize->xml_serialize(/* "搜索区间长度" */ g_sLangTxt_Native_SearchLen.GetString(), "SearchArea", "", "number", pParas->m_fSearchArea);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_common_fault_paras(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("是否自动搜索","_AutoTest","","number",pParas->m_nAutoSearch);
	pXmlSierialize->xml_serialize("变化始值","BeginVal","In/A","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("变化终值","EndVal","In/A","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("测试精度","Step","In/A","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("复式制动电流(Ir-Id)","Ir","A","number",pParas->m_fIr_Id);
	pXmlSierialize->xml_serialize("差动电流定值","IdSetting","A","number",pParas->m_fIdSetting);
#else
  pXmlSierialize->xml_serialize(/* "是否自动搜索" */ g_sLangTxt_Native_AutoSearch.GetString(), "_AutoTest", "", "number", pParas->m_nAutoSearch);
  pXmlSierialize->xml_serialize(/* "变化始值" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "In/A", "number", pParas->m_fScanFrom);
  pXmlSierialize->xml_serialize(/* "变化终值" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "In/A", "number", pParas->m_fScanTo);
  pXmlSierialize->xml_serialize(/* "测试精度" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "In/A", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "复式制动电流(Ir-Id)" */ g_sLangTxt_Native_ComplexBrakeCurrent.GetString(), "Ir", "A", "number", pParas->m_fIr_Id);
  pXmlSierialize->xml_serialize(/* "差动电流定值" */ g_sLangTxt_Native_DiffCurrentSetVal.GetString(), "IdSetting", "A", "number", pParas->m_fIdSetting);
#endif
}

void stt_xml_serialize_common_sys_paras(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("差动类别(0-大差试验 1-小差试验)","DiffType","","number",pParas->m_nDiffType);
	pXmlSierialize->xml_serialize("故障前时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("故障时间","FaultTime","s","number",pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("Ua幅值","UaMag","V","number",pParas->m_fUmag[0]);
	pXmlSierialize->xml_serialize("Ub幅值","UbMag","V","number",pParas->m_fUmag[1]);
	pXmlSierialize->xml_serialize("Uc幅值","UbMag","V","number",pParas->m_fUmag[2]);

	pXmlSierialize->xml_serialize("Ua相位","UaAng","°","number",pParas->m_fUang[0]);
	pXmlSierialize->xml_serialize("Ub相位","UbAng","°","number",pParas->m_fUang[1]);
	pXmlSierialize->xml_serialize("Uc相位","UcAng","°","number",pParas->m_fUang[2]);

	pXmlSierialize->xml_serialize("间隔1TA变比","TA1","","number",pParas->m_fTA1);
	pXmlSierialize->xml_serialize("间隔2TA变比","TA2","","number",pParas->m_fTA2);
	pXmlSierialize->xml_serialize("间隔3TA变比","TA3","","number",pParas->m_fTA3);
	pXmlSierialize->xml_serialize("最大TA变比","TAmax","","number",pParas->m_fTAmax);
	pXmlSierialize->xml_serialize("搜索方法","SearchMode","","SearchModePnv",pParas->m_nSearchMode);

	// 定值相关
	pXmlSierialize->xml_serialize("差动门槛电流","IDoor","In/A","number",pParas->m_fIcdqd);

	pXmlSierialize->xml_serialize("复式比率系数高值","CompoundKh","","number",pParas->m_fCompoundKh);
	pXmlSierialize->xml_serialize("复式比率系数低值","CompoundKl","","number",pParas->m_fCompoundKl);

	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

#else
  pXmlSierialize->xml_serialize(/* "差动类别(0-大差试验 1-小差试验)" */ g_sLangTxt_Native_DiffType.GetString(), "DiffType", "", "number", pParas->m_nDiffType);
  pXmlSierialize->xml_serialize(/* "故障前时间" */ g_sLangTxt_Native_PreFautTime.GetString(), "PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
  pXmlSierialize->xml_serialize(/* "故障时间" */ g_sLangTxt_Gradient_Time.GetString(), "FaultTime", "s", "number", pParas->m_fFaultTime);
  pXmlSierialize->xml_serialize(/* "Ua幅值" */ g_sLangTxt_Native_UaAmplitude.GetString(), "UaMag", "V", "number", pParas->m_fUmag[0]);
  pXmlSierialize->xml_serialize(/* "Ub幅值" */ g_sLangTxt_Native_UbAmplitude.GetString(), "UbMag", "V", "number", pParas->m_fUmag[1]);
  pXmlSierialize->xml_serialize(/* "Uc幅值" */ g_sLangTxt_Native_UcAmplitude.GetString(), "UbMag", "V", "number", pParas->m_fUmag[2]);

  pXmlSierialize->xml_serialize(/* "Ua相位" */ g_sLangTxt_Native_UaPhase.GetString(), "UaAng", "°", "number", pParas->m_fUang[0]);
  pXmlSierialize->xml_serialize(/* "Ub相位" */ g_sLangTxt_Native_UbPhase.GetString(), "UbAng", "°", "number", pParas->m_fUang[1]);
  pXmlSierialize->xml_serialize(/* "Uc相位" */ g_sLangTxt_Native_UcPhase.GetString(), "UcAng", "°", "number", pParas->m_fUang[2]);

  pXmlSierialize->xml_serialize(/* "间隔1TA变比" */ g_sLangTxt_Native_Gap1TARatio.GetString(), "TA1", "", "number", pParas->m_fTA1);
  pXmlSierialize->xml_serialize(/* "间隔2TA变比" */ g_sLangTxt_Native_Gap2TARatio.GetString(), "TA2", "", "number", pParas->m_fTA2);
  pXmlSierialize->xml_serialize(/* "间隔3TA变比" */ g_sLangTxt_Native_Gap3TARatio.GetString(), "TA3", "", "number", pParas->m_fTA3);
  pXmlSierialize->xml_serialize(/* "最大TA变比" */ g_sLangTxt_Native_MaxTARatio.GetString(), "TAmax", "", "number", pParas->m_fTAmax);
  pXmlSierialize->xml_serialize(/* "搜索方法" */ g_sLangTxt_Native_SearchMeth.GetString(), "SearchMode", "", "SearchModePnv", pParas->m_nSearchMode);

  // 定值相关
  pXmlSierialize->xml_serialize(/* "差动门槛电流" */ g_sLangTxt_Native_DiffThreshCurrent.GetString(), "IDoor", "In/A", "number", pParas->m_fIcdqd);

  pXmlSierialize->xml_serialize(/* "复式比率系数高值" */ g_sLangTxt_Native_HighCompRatioCoef.GetString(), "CompoundKh", "", "number", pParas->m_fCompoundKh);
  pXmlSierialize->xml_serialize(/* "复式比率系数低值" */ g_sLangTxt_Native_LowCompRatioCoef.GetString(), "CompoundKl", "", "number", pParas->m_fCompoundKl);

  pXmlSierialize->xml_serialize(/* "开入逻辑" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize,nBinExNum);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,nBoutExNum,FALSE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_thr(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize,nBinExNum,nBoutExNum);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize,nBinExNum,nBoutExNum);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_thr(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("差动动作值", "Iqd", "In/A", "number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("动作描述","ActFlag","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("比例制动系数","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "差动动作值" */ g_sLangTxt_Native_DiffActionVal.GetString(), "Iqd", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "比例制动系数" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize,nBinExNum,nBoutExNum);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize,nBinExNum,nBoutExNum);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("当前搜索值","CurrentId","In/A","number",pResults->m_fIdiffSettingValue);
	pXmlSierialize->xml_serialize("差动动作值","TripId","In/A","number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("差动动作描述","ActId","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("制动电流","TripIr","In/A","number",pResults->m_fIbiasValue);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
	pXmlSierialize->xml_serialize("比例制动系数","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "当前搜索值" */ g_sLangTxt_Native_CurrSearchVal.GetString(), "CurrentId", "In/A", "number", pResults->m_fIdiffSettingValue);
  pXmlSierialize->xml_serialize(/* "差动动作值" */ g_sLangTxt_Native_DiffActionVal.GetString(), "TripId", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "差动动作描述" */ g_sLangTxt_Native_DiffActionDesc.GetString(), "ActId", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_Native_ControlCurrent.GetString(), "TripIr", "In/A", "number", pResults->m_fIbiasValue);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
  pXmlSierialize->xml_serialize(/* "比例制动系数" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_cboperate(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("差动电流","Id","In/A","number",pParas->m_fIdiff);
	pXmlSierialize->xml_serialize("复式制动电流(Ir-Id)","Ir","In/A","number",pParas->m_fIr_Id);
	pXmlSierialize->xml_serialize("电压闭锁元件","ULockType","","BP2ULockType",pParas->m_nULockType);
	pXmlSierialize->xml_serialize("闭锁电压值","ULockValue","","number",pParas->m_fULockValue);
#else
  pXmlSierialize->xml_serialize(/* "差动电流" */ g_sLangTxt_Native_DiffCurrents.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);
  pXmlSierialize->xml_serialize(/* "复式制动电流(Ir-Id)" */ g_sLangTxt_Native_ComplexBrakeCurrent.GetString(), "Ir", "In/A", "number", pParas->m_fIr_Id);
  pXmlSierialize->xml_serialize(/* "电压闭锁元件" */ g_sLangTxt_Native_VoltLockElem.GetString(), "ULockType", "", "BP2ULockType", pParas->m_nULockType);
  pXmlSierialize->xml_serialize(/* "闭锁电压值" */ g_sLangTxt_Native_LockVoltValue.GetString(), "ULockValue", "", "number", pParas->m_fULockValue);
#endif
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize,nBinExNum,nBoutExNum);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_cboperate(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作时间", "TripTime", "s", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("动作描述","ActFlag","","number",pResults->m_nActFlag);
#else
  pXmlSierialize->xml_serialize(/* "动作时间" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);
  pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttXmlSerializeBase* stt_xml_serialize(tmt_BP2DiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,long nBinExNum,long nBoutExNum)
{
//	stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest) == 0)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas),  pXmlParas,nBinExNum,nBoutExNum);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("类型", "ThrType", "", "number", ((tmt_BP2DiffThrTest*)pTests)->m_nThrType);
#else
      pXmlParas->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_BP2DiffThrTest *)pTests)->m_nThrType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest) == 0)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlParas,nBinExNum,nBoutExNum);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("类型", "RateType", "", "number", ((tmt_BP2DiffRateTest*)pTests)->m_nRateType);
#else
      pXmlParas->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_BP2DiffRateTest *)pTests)->m_nRateType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest) == 0)
		{
			stt_xml_serialize_cboperate(&(pTests->m_oDiffCurrParas),  pXmlParas,nBinExNum,nBoutExNum);
		}
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest) == 0)
		{
			stt_xml_serialize_thr(&pTests->m_oDiffCurrResults,  pXmlResults,nBinExNum,nBoutExNum);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest) == 0)
		{
			stt_xml_serialize_rate(&pTests->m_oDiffCurrResults,  pXmlResults,nBinExNum,nBoutExNum);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest) == 0)
		{
			stt_xml_serialize_cboperate(&pTests->m_oDiffCurrResults,  pXmlResults,nBinExNum,nBoutExNum);
		}
	}

	return pXmlParas;
}

void stt_xml_serialize(tmt_BP2DiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,long nBinExNum,long nBoutExNum,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffTCurrTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas), pXmlSerialize, nBinExNum, nBoutExNum);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("类型", "ThrType", "", "number", ((tmt_BP2DiffThrTest*)pTests)->m_nThrType);
#else
      pXmlSerialize->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_BP2DiffThrTest *)pTests)->m_nThrType);
#endif
		}

		stt_xml_serialize_thr(&(pTests->m_oDiffCurrResults), pXmlSerialize, nBinExNum, nBoutExNum);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2DiffRateTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlSerialize, nBinExNum, nBoutExNum);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("类型", "RateType", "", "number", ((tmt_BP2DiffRateTest*)pTests)->m_nRateType);
#else
      pXmlSerialize->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_BP2DiffRateTest *)pTests)->m_nRateType);
#endif
		}

		stt_xml_serialize_rate(&(pTests->m_oDiffCurrResults), pXmlSerialize, nBinExNum, nBoutExNum);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_BP2CBOperateTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_cboperate(&(pTests->m_oDiffCurrParas), pXmlSerialize, nBinExNum, nBoutExNum);
		}

		stt_xml_serialize_cboperate(&(pTests->m_oDiffCurrResults), pXmlSerialize, nBinExNum, nBoutExNum);
	}
}