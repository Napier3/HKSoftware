#include "stdafx.h"
#include "tmt_elec_railway_diff_test.h"
#include "../../../SttTestBase/SttXmlSerialize.h"
#include "../../../SttCmd/SttTestCmd.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif
void stt_init_paras(tmt_ElecRailwayDiffParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ElecRailwayDiffParas));
	pParas->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_diff_search_results(tmt_ElecRailwayDiffParas *pParas,tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("搜索起点","SearchBegin","","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize("当前值","CurrSearchVal","","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("搜索终点","SearchEnd","","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize("搜索区间长度","SearchArea","","number",pParas->m_fSearchArea);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("Ialpha(Ie)","TripIalphaIe","Ie","number",pResults->m_fIalphaIe);
	pXmlSierialize->xml_serialize("IalphaA","TripIalphaA","In/A","number",pResults->m_fIalpha);
	pXmlSierialize->xml_serialize("Ibeta(Ie)","TripIbetaIe","Ie","number",pResults->m_fIbetaIe);
	pXmlSierialize->xml_serialize("IbetaA","TripIbetaA","In/A","number",pResults->m_fIbeta);
	pXmlSierialize->xml_serialize("制动电流","Ir","","number",pParas->m_fIbias);
#else
  pXmlSierialize->xml_serialize(/* "搜索起点" */ g_sLangTxt_Native_SearchStart.GetString(), "SearchBegin", "", "number", pParas->m_fSearchBegin);
  pXmlSierialize->xml_serialize(/* "当前值" */ g_sLangTxt_Native_CurrentValue.GetString(), "CurrSearchVal", "", "number", pParas->m_fCurrScanVal);
  pXmlSierialize->xml_serialize(/* "搜索终点" */ g_sLangTxt_Native_SearchEnd.GetString(), "SearchEnd", "", "number", pParas->m_fSearchEnd);
  pXmlSierialize->xml_serialize(/* "搜索区间长度" */ g_sLangTxt_Native_SearchLen.GetString(), "SearchArea", "", "number", pParas->m_fSearchArea);
  pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("Ialpha(Ie)", "TripIalphaIe", "Ie", "number", pResults->m_fIalphaIe);
  pXmlSierialize->xml_serialize("IalphaA", "TripIalphaA", "In/A", "number", pResults->m_fIalpha);
  pXmlSierialize->xml_serialize("Ibeta(Ie)", "TripIbetaIe", "Ie", "number", pResults->m_fIbetaIe);
  pXmlSierialize->xml_serialize("IbetaA", "TripIbetaA", "In/A", "number", pResults->m_fIbeta);
  pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_Native_ControlCurrent.GetString(), "Ir", "", "number", pParas->m_fIbias);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_common_fault_paras(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2023.4.26 zhangyq
#ifdef NOT_USE_XLANGUAGE
	if(!pXmlSierialize->xml_serialize("项目名称", "TestName", "", "string", pParas->m_pszTestName))
#else
  if (!pXmlSierialize->xml_serialize(/* "项目名称" */ g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName))
#endif
	{
		memset(pParas->m_pszTestName,0,32);
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("是否自动搜索","_AutoTest","","number",pParas->m_nAutoSearch);
	pXmlSierialize->xml_serialize("变化始值","BeginVal","In/A","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("变化终值","EndVal","In/A","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("测试精度","Step","In/A","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("制动电流","Ir","A","number",pParas->m_fIbias);
	pXmlSierialize->xml_serialize("差动电流","Id","In/A","number",pParas->m_fIdiff);
	pXmlSierialize->xml_serialize("故障类型","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
	pXmlSierialize->xml_serialize("差动电流定值","IdSetting","A","number",pParas->m_fIdSetting);
#else
  pXmlSierialize->xml_serialize(/* "是否自动搜索" */ g_sLangTxt_Native_AutoSearch.GetString(), "_AutoTest", "", "number", pParas->m_nAutoSearch);
  pXmlSierialize->xml_serialize(/* "变化始值" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "In/A", "number", pParas->m_fScanFrom);
  pXmlSierialize->xml_serialize(/* "变化终值" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "In/A", "number", pParas->m_fScanTo);
  pXmlSierialize->xml_serialize(/* "测试精度" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "In/A", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_State_BrakingCur.GetString(), "Ir", "A", "number", pParas->m_fIbias);
  pXmlSierialize->xml_serialize(/* "差动电流" */ g_sLangTxt_State_DifferentCur.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);
  pXmlSierialize->xml_serialize(/* "故障类型" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuDiffFaultType", pParas->m_nPhase);
  pXmlSierialize->xml_serialize(/* "差动电流定值" */ g_sLangTxt_Native_DiffCurrentSetVal.GetString(), "IdSetting", "A", "number", pParas->m_fIdSetting);
#endif
}

void stt_xml_serialize_common_sys_paras(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	BOOL bFind = pXmlSierialize->xml_serialize("准备时间","PrepareTime","s","number",pParas->m_fPreTime);
	pXmlSierialize->xml_serialize("故障前时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	if(!bFind)
	{
		pParas->m_fPreTime = 0.001f;
	}
	pXmlSierialize->xml_serialize("故障时间","FaultTime","s","number",pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("CT极性","CTPoint","","CTPositionPnv",pParas->m_bCTStarPoint);
	pXmlSierialize->xml_serialize("Ir制动方程","IrEquation","","IrEquationPnv",pParas->m_nIbiasCal);

	pXmlSierialize->xml_serialize("第一组电压输出值","Vg1","V","number",pParas->m_fVg1);
	pXmlSierialize->xml_serialize("第二组电压输出值","Vg2","V","number",pParas->m_fVg2);

	pXmlSierialize->xml_serialize("平衡系数","KplSet","","number",pParas->m_fKpl);
	

	pXmlSierialize->xml_serialize("搜索方法","SearchMode","","SearchModePnv",pParas->m_nSearchMode);

	// 定值相关
	pXmlSierialize->xml_serialize("定值整定方式","MinAxis","","SettingModePnv",pParas->m_bMinAxis);//++++默认标幺值
	pXmlSierialize->xml_serialize("额定电流", "InSet", "A", "number", pParas->m_fIbase);
	pXmlSierialize->xml_serialize("差动速断电流","IQuick","In/A","number",pParas->m_fIsd);
	pXmlSierialize->xml_serialize("差动门槛电流","IDoor","In/A","number",pParas->m_fIcdqd);

	pXmlSierialize->xml_serialize("比率制动拐点1电流","Limp1","","number",pParas->m_fIp1);
	pXmlSierialize->xml_serialize("比率制动拐点2电流","Limp2","","number",pParas->m_fIp2);

	pXmlSierialize->xml_serialize("基波比率制动特性斜率1","Kid1","","number",pParas->m_fKid1);
	pXmlSierialize->xml_serialize("基波比率制动特性斜率2","Kid2","","number",pParas->m_fKid2);

	pXmlSierialize->xml_serialize("变压器接线形式","TranSort","","number",pParas->m_nTranSort);
	pXmlSierialize->xml_serialize("高压侧CT接线方式","RWCTconnect","","number",pParas->m_nRWCTconnect);
	pXmlSierialize->xml_serialize("平衡系数计算方法","KphMode","","number",pParas->m_nKphMode);

	//上位机单用
	pXmlSierialize->xml_serialize("2次谐波制动系数","CoefHarm2","","number",pParas->m_fCoefHarm2);
	pXmlSierialize->xml_serialize("3次谐波制动系数","CoefHarm3","","number",pParas->m_fCoefHarm3);
	pXmlSierialize->xml_serialize("5次谐波制动系数","CoefHarm5","","number",pParas->m_fCoefHarm5);

	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
  pXmlSierialize->xml_serialize(/* "故障前时间" */ g_sLangTxt_Native_PreFautTime.GetString(), "PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
  pXmlSierialize->xml_serialize(/* "故障时间" */ g_sLangTxt_Gradient_FailTime.GetString(), "FaultTime", "s", "number", pParas->m_fFaultTime);
  pXmlSierialize->xml_serialize(/* "CT极性" */ g_sLangTxt_State_CTpolarity.GetString(), "CTPoint", "", "CTPositionPnv", pParas->m_bCTStarPoint);
  pXmlSierialize->xml_serialize(/* "Ir制动方程" */ g_sLangTxt_Native_IrBrakeEq.GetString(), "IrEquation", "", "IrEquationPnv", pParas->m_nIbiasCal);

  pXmlSierialize->xml_serialize(/* "第一组电压输出值" */ g_sLangTxt_Native_FirstGroupVoltageOut.GetString(), "Vg1", "V", "number", pParas->m_fVg1);
  pXmlSierialize->xml_serialize(/* "第二组电压输出值" */ g_sLangTxt_Native_SecondGroupVoltageOut.GetString(), "Vg2", "V", "number", pParas->m_fVg2);

  pXmlSierialize->xml_serialize(/* "平衡系数" */ g_sLangTxt_Native_BalCoeff.GetString(), "KplSet", "", "number", pParas->m_fKpl);

  pXmlSierialize->xml_serialize(/* "搜索方法" */ g_sLangTxt_Native_SearchMeth.GetString(), "SearchMode", "", "SearchModePnv", pParas->m_nSearchMode);

  // 定值相关
  pXmlSierialize->xml_serialize(/* "定值整定方式" */ g_sLangTxt_Native_DevSetMethod.GetString(), "MinAxis", "", "SettingModePnv", pParas->m_bMinAxis);  //++++默认标幺值
  pXmlSierialize->xml_serialize(/* "额定电流" */ g_sLangTxt_Native_EDCurrent.GetString(), "InSet", "A", "number", pParas->m_fIbase);
  pXmlSierialize->xml_serialize(/* "差动速断电流" */ g_sLangTxt_Native_DiffQuickBreakCurr.GetString(), "IQuick", "In/A", "number", pParas->m_fIsd);
  pXmlSierialize->xml_serialize(/* "差动门槛电流" */ g_sLangTxt_Native_DiffThreshCurrent.GetString(), "IDoor", "In/A", "number", pParas->m_fIcdqd);

  pXmlSierialize->xml_serialize(/* "比率制动拐点1电流" */ g_sLangTxt_Native_RatioBrakeTurn1Curr.GetString(), "Limp1", "", "number", pParas->m_fIp1);
  pXmlSierialize->xml_serialize(/* "比率制动拐点2电流" */ g_sLangTxt_Native_RatioBrakeTurn2Curr.GetString(), "Limp2", "", "number", pParas->m_fIp2);

  pXmlSierialize->xml_serialize(/* "基波比率制动特性斜率1" */ g_sLangTxt_Native_FundRatioBrkSlope1.GetString(), "Kid1", "", "number", pParas->m_fKid1);
  pXmlSierialize->xml_serialize(/* "基波比率制动特性斜率2" */ g_sLangTxt_Native_FundRatioBrkSlope2.GetString(), "Kid2", "", "number", pParas->m_fKid2);

  pXmlSierialize->xml_serialize(/* "变压器接线形式" */ g_sLangTxt_Native_TransConnForm.GetString(), "TranSort", "", "number", pParas->m_nTranSort);
  pXmlSierialize->xml_serialize(/* "高压侧CT接线方式" */ g_sLangTxt_Native_HVCTConnectionMode.GetString(), "RWCTconnect", "", "number", pParas->m_nRWCTconnect);
  pXmlSierialize->xml_serialize(/* "平衡系数计算方法" */ g_sLangTxt_Native_BalanceCoeffCalcMethod.GetString(), "KphMode", "", "number", pParas->m_nKphMode);

  // 上位机单用
  pXmlSierialize->xml_serialize(/* "2次谐波制动系数" */ g_sLangTxt_Native_2HarBrkCoef.GetString(), "CoefHarm2", "", "number", pParas->m_fCoefHarm2);
  pXmlSierialize->xml_serialize(/* "3次谐波制动系数" */ g_sLangTxt_Native_3HarBrkCoef.GetString(), "CoefHarm3", "", "number", pParas->m_fCoefHarm3);
  pXmlSierialize->xml_serialize(/* "5次谐波制动系数" */ g_sLangTxt_Native_5HarBrkCoef.GetString(), "CoefHarm5", "", "number", pParas->m_fCoefHarm5);

  pXmlSierialize->xml_serialize(/* "开入逻辑" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_thr(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_thr_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize_rate(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("当前搜索值","CurrentId","In/A","number",pResults->m_fIdiffSettingValue);
	pXmlSierialize->xml_serialize("差动动作值","TripId","In/A","number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("差动动作描述","ActId","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("制动电流","TripIr","In/A","number",pResults->m_fIbiasValue);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("Ialpha(Ie)","TripIalphaIe","Ie","number",pResults->m_fIalphaIe);
	pXmlSierialize->xml_serialize("IalphaA","TripIalphaA","In/A","number",pResults->m_fIalpha);
	pXmlSierialize->xml_serialize("Ibeta(Ie)","TripIbetaIe","Ie","number",pResults->m_fIbetaIe);
	pXmlSierialize->xml_serialize("IbetaA","TripIbetaA","In/A","number",pResults->m_fIbeta);
	pXmlSierialize->xml_serialize("比例制动系数","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "当前搜索值" */ g_sLangTxt_Native_CurrSearchVal.GetString(), "CurrentId", "In/A", "number", pResults->m_fIdiffSettingValue);
  pXmlSierialize->xml_serialize(/* "差动动作值" */ g_sLangTxt_Native_DiffActionVal.GetString(), "TripId", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "差动动作描述" */ g_sLangTxt_Native_DiffActionDesc.GetString(), "ActId", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_Native_ControlCurrent.GetString(), "TripIr", "In/A", "number", pResults->m_fIbiasValue);
  pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("Ialpha(Ie)", "TripIalphaIe", "Ie", "number", pResults->m_fIalphaIe);
  pXmlSierialize->xml_serialize("IalphaA", "TripIalphaA", "In/A", "number", pResults->m_fIalpha);
  pXmlSierialize->xml_serialize("Ibeta(Ie)", "TripIbetaIe", "Ie", "number", pResults->m_fIbetaIe);
  pXmlSierialize->xml_serialize("IbetaA", "TripIbetaA", "In/A", "number", pResults->m_fIbeta);
  pXmlSierialize->xml_serialize(/* "比例制动系数" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_quick(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_quick_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("速断电流", "Isd", "In/A", "number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("动作描述","ActFlag","","number",pResults->m_nActFlag);
#else
  pXmlSierialize->xml_serialize(/* "速断电流" */ g_sLangTxt_Native_InstCurr.GetString(), "Isd", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_harm(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2023.4.26 zhangyq
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("项目名称", "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("是否自动搜索","_AutoTest","","number",pParas->m_nAutoSearch);
	pXmlSierialize->xml_serialize("变化始值","BeginVal","%","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("变化终值","EndVal","%","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("测试精度","Step","%","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("差动电流","Id","In/A","number",pParas->m_fIdiff);
	pXmlSierialize->xml_serialize("谐波次数","HarmIndex","","DiffHarmIndex",pParas->m_nHarmIndex);
	pXmlSierialize->xml_serialize("故障类型","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
	pXmlSierialize->xml_serialize("谐波制动系数定值","RateHarmSet","","number",pParas->m_fCoefHarm2);
#else
  pXmlSierialize->xml_serialize(/* "项目名称" */ g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName);

  pXmlSierialize->xml_serialize(/* "是否自动搜索" */ g_sLangTxt_Native_AutoSearch.GetString(), "_AutoTest", "", "number", pParas->m_nAutoSearch);
  pXmlSierialize->xml_serialize(/* "变化始值" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "%", "number", pParas->m_fScanFrom);
  pXmlSierialize->xml_serialize(/* "变化终值" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "%", "number", pParas->m_fScanTo);
  pXmlSierialize->xml_serialize(/* "测试精度" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "%", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "差动电流" */ g_sLangTxt_State_DifferentCur.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);
  pXmlSierialize->xml_serialize(/* "谐波次数" */ g_sLangTxt_Native_harmonicOrder.GetString(), "HarmIndex", "", "DiffHarmIndex", pParas->m_nHarmIndex);
  pXmlSierialize->xml_serialize(/* "故障类型" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuDiffFaultType", pParas->m_nPhase);
  pXmlSierialize->xml_serialize(/* "谐波制动系数定值" */ g_sLangTxt_Native_HarmonicBrakeCoeff.GetString(), "RateHarmSet", "", "number", pParas->m_fCoefHarm2);
#endif
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_harm_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("谐波制动系数","TripRHarm","A","number",pResults->m_fIrCoef);
	pXmlSierialize->xml_serialize("谐波制动系数描述","ActRHarm","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("A相基波电流","TripABase","A","number",pResults->m_fIRbase[0]);
	pXmlSierialize->xml_serialize("B相基波电流","TripBBase","A","number",pResults->m_fIRbase[1]);
	pXmlSierialize->xml_serialize("C相基波电流","TripCBase","A","number",pResults->m_fIRbase[2]);
	pXmlSierialize->xml_serialize("A相谐波电流","TripAHarm","A","number",pResults->m_fIharm[0]);
	pXmlSierialize->xml_serialize("B相谐波电流","TripBHarm","A","number",pResults->m_fIharm[1]);
	pXmlSierialize->xml_serialize("C相谐波电流","TripCHarm","A","number",pResults->m_fIharm[2]);
#else
  pXmlSierialize->xml_serialize(/* "谐波制动系数" */ g_sLangTxt_State_HarmonicBrakingcoefficient.GetString(), "TripRHarm", "A", "number", pResults->m_fIrCoef);
  pXmlSierialize->xml_serialize(/* "谐波制动系数描述" */ g_sLangTxt_Native_HarmonicBrakeDesc.GetString(), "ActRHarm", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "A相基波电流" */ g_sLangTxt_Native_PhaseACurrent.GetString(), "TripABase", "A", "number", pResults->m_fIRbase[0]);
  pXmlSierialize->xml_serialize(/* "B相基波电流" */ g_sLangTxt_Native_PhaseBCurrent.GetString(), "TripBBase", "A", "number", pResults->m_fIRbase[1]);
  pXmlSierialize->xml_serialize(/* "C相基波电流" */ g_sLangTxt_Native_PhaseCCurrent.GetString(), "TripCBase", "A", "number", pResults->m_fIRbase[2]);
  pXmlSierialize->xml_serialize(/* "A相谐波电流" */ g_sLangTxt_Native_PhaseAHarmCur.GetString(), "TripAHarm", "A", "number", pResults->m_fIharm[0]);
  pXmlSierialize->xml_serialize(/* "B相谐波电流" */ g_sLangTxt_Native_BHarmonicCurrent.GetString(), "TripBHarm", "A", "number", pResults->m_fIharm[1]);
  pXmlSierialize->xml_serialize(/* "C相谐波电流" */ g_sLangTxt_Native_CHarmonicCurrent.GetString(), "TripCHarm", "A", "number", pResults->m_fIharm[2]);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_acttime(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2023.4.26 zhangyq
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("项目名称", "TestName", "", "string", pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("差动电流","Id","In/A","number",pParas->m_fIdiff);
	pXmlSierialize->xml_serialize("制动电流","Ir","In/A","number",pParas->m_fIbias);
	pXmlSierialize->xml_serialize("故障类型","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
#else
  pXmlSierialize->xml_serialize(/* "项目名称" */ g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName);

  pXmlSierialize->xml_serialize(/* "差动电流" */ g_sLangTxt_State_DifferentCur.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);
  pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_State_BrakingCur.GetString(), "Ir", "In/A", "number", pParas->m_fIbias);
  pXmlSierialize->xml_serialize(/* "故障类型" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuDiffFaultType", pParas->m_nPhase);
#endif

	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_acttime_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
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

CSttXmlSerializeBase* stt_xml_serialize(tmt_ElecRailwayDiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
//	stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTest) == 0)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas),  pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("类型", "ThrType", "", "number", ((tmt_ElecRailwayDiffThrTest*)pTests)->m_nThrType);
#else
      pXmlParas->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_ElecRailwayDiffThrTest *)pTests)->m_nThrType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffRateTest) == 0)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("类型", "RateType", "", "number", ((tmt_ElecRailwayDiffRateTest*)pTests)->m_nRateType);
#else
      pXmlParas->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_ElecRailwayDiffRateTest *)pTests)->m_nRateType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffQuickTest) == 0)
		{
			stt_xml_serialize_quick(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffHarmTest) == 0)
		{
			stt_xml_serialize_harm(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTest) == 0)
		{
			stt_xml_serialize_thr(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffRateTest) == 0)
		{
			stt_xml_serialize_rate_elec_railway(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffQuickTest) == 0)
		{
			stt_xml_serialize_quick(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffHarmTest) == 0)
		{
			stt_xml_serialize_harm(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
	}

	return pXmlParas;
}

void stt_xml_serialize(tmt_ElecRailwayDiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("类型", "ThrType", "", "number", ((tmt_ElecRailwayDiffThrTest*)pTests)->m_nThrType);
#else
      pXmlSerialize->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_ElecRailwayDiffThrTest *)pTests)->m_nThrType);
#endif
		}

		stt_xml_serialize_thr(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffRateTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("类型", "RateType", "", "number", ((tmt_ElecRailwayDiffRateTest*)pTests)->m_nRateType);
#else
      pXmlSerialize->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_ElecRailwayDiffRateTest *)pTests)->m_nRateType);
#endif
		}

		stt_xml_serialize_rate_elec_railway(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffQuickTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_quick(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_quick(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffHarmTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_harm(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_harm(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_ElecRailwayDiffTimeTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_acttime(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
}

void stt_xml_serialize_write_ElecRailwayDiffTest()
{
//	tmt_ElecRailwayDiffThrTest oElecRailwayDiffThrTest;
//	oElecRailwayDiffThrTest.init();
//	CSttXmlSerializeTool oSttXmlSerializeTool;
//	CSttTestCmd oSttTestCmd;
//	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
//	pMacro->GetParas();
//	pMacro->GetResults();
//	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
//	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
//	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
//	stt_xml_serialize(&oElecRailwayDiffThrTest, pMacroParas,0,0);
//	CString strXMLPath;
//	strXMLPath = _P_GetConfigPath();
//	strXMLPath += ("ElecRailwayDiffTestDemo.xml");
//	pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
//
//	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
