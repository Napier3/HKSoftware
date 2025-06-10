#include "stdafx.h"
#include "tmt_diff_curr_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

#ifndef _STT_NOT_IN_TEST_SERVER_
#include "../SttSystemConfig.h"
#endif

void stt_init_paras(tmt_DiffCurrParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DiffCurrParas));
	pParas->init();
}

void stt_init_results(tmt_DiffCurrResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DiffCurrResults));
	pResults->init();
}

void stt_xml_serialize_diff_6i_binary_in_pnv(tmt_BinaryIn *pbin, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("开入A选择", "BinSelectA", "", "BOOL", pbin[0].nSelect);
    pXmlSierialize->xml_serialize("开入B选择", "BinSelectB", "", "BOOL", pbin[1].nSelect);
    pXmlSierialize->xml_serialize("开入C选择", "BinSelectC", "", "BOOL", pbin[2].nSelect);
    pXmlSierialize->xml_serialize("开入R选择", "BinSelectR", "", "BOOL", pbin[3].nSelect);
    pXmlSierialize->xml_serialize("开入a选择", "BinSelecta", "", "BOOL", pbin[4].nSelect);
    pXmlSierialize->xml_serialize("开入b选择", "BinSelectb", "", "BOOL", pbin[5].nSelect);
    pXmlSierialize->xml_serialize("开入c选择", "BinSelectc", "", "BOOL", pbin[6].nSelect);
    pXmlSierialize->xml_serialize("开入r选择", "BinSelectr", "", "BOOL", pbin[7].nSelect);
}

void stt_xml_serialize_diff_6i_binary_out_pnv(tmt_BinaryOut *pbOut, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("开出1状态", "_FaultBO01", "", "DOutputState", pbOut[0].nState);
    pXmlSierialize->xml_serialize("开出2状态", "_FaultBO02", "", "DOutputState", pbOut[1].nState);
    pXmlSierialize->xml_serialize("开出3状态", "_FaultBO03", "", "DOutputState", pbOut[2].nState);
    pXmlSierialize->xml_serialize("开出4状态", "_FaultBO04", "", "DOutputState", pbOut[3].nState);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_diff_search_results(tmt_DiffCurrParas *pParas,tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("搜索起点","SearchBegin","","number",pParas->m_fSearchBegin);
	pXmlSierialize->xml_serialize("当前值","CurrSearchVal","","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("搜索终点","SearchEnd","","number",pParas->m_fSearchEnd);
	pXmlSierialize->xml_serialize("搜索区间长度","SearchArea","","number",pParas->m_fSearchArea);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2(Ie)","TripI2Ie","Ie","number",pResults->m_fI2Ie);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
	pXmlSierialize->xml_serialize("制动电流","Ir","","number",pParas->m_fIbias);
#else
  pXmlSierialize->xml_serialize(/* "搜索起点" */ g_sLangTxt_Native_SearchStart.GetString(), "SearchBegin", "", "number", pParas->m_fSearchBegin);
  pXmlSierialize->xml_serialize(/* "当前值" */ g_sLangTxt_Native_CurrentValue.GetString(), "CurrSearchVal", "", "number", pParas->m_fCurrScanVal);
  pXmlSierialize->xml_serialize(/* "搜索终点" */ g_sLangTxt_Native_SearchEnd.GetString(), "SearchEnd", "", "number", pParas->m_fSearchEnd);
  pXmlSierialize->xml_serialize(/* "搜索区间长度" */ g_sLangTxt_Native_SearchLen.GetString(), "SearchArea", "", "number", pParas->m_fSearchArea);
  pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("I2(Ie)", "TripI2Ie", "Ie", "number", pResults->m_fI2Ie);
  pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
  pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_Native_ControlCurrent.GetString(), "Ir", "", "number", pParas->m_fIbias);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_common_fault_paras(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.12 caoxc
	if(!pXmlSierialize->xml_serialize("项目名称", "TestName", "", "string", pParas->m_pszTestName))
	{
		memset(pParas->m_pszTestName,0,32);
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("是否自动搜索","_AutoTest","","number",pParas->m_nAutoSearch);
	pXmlSierialize->xml_serialize("变化始值","BeginVal","In/A","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("变化终值","EndVal","In/A","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("测试精度","Step","In/A","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("制动电流","Ir","A","number",pParas->m_fIbias);
	pXmlSierialize->xml_serialize("故障类型","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
	pXmlSierialize->xml_serialize("差动电流定值","IdSetting","A","number",pParas->m_fIdSetting);
#else
  pXmlSierialize->xml_serialize(/* "是否自动搜索" */ g_sLangTxt_Native_AutoSearch.GetString(), "_AutoTest", "", "number", pParas->m_nAutoSearch);
  pXmlSierialize->xml_serialize(/* "变化始值" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "In/A", "number", pParas->m_fScanFrom);
  pXmlSierialize->xml_serialize(/* "变化终值" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "In/A", "number", pParas->m_fScanTo);
  pXmlSierialize->xml_serialize(/* "测试精度" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "In/A", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_State_BrakingCur.GetString(), "Ir", "A", "number", pParas->m_fIbias);
  pXmlSierialize->xml_serialize(/* "故障类型" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuDiffFaultType", pParas->m_nPhase);
  pXmlSierialize->xml_serialize(/* "差动电流定值" */ g_sLangTxt_Native_DiffCurrentSetVal.GetString(), "IdSetting", "A", "number", pParas->m_fIdSetting);
#endif
}

void stt_xml_serialize_common_sys_paras(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	BOOL bFind = pXmlSierialize->xml_serialize("准备时间","PrepareTime","s","number",pParas->m_fPreTime);
	pXmlSierialize->xml_serialize("故障前时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);
	if(!bFind)
	{
		pParas->m_fPreTime = pParas->m_fPreFaultTime;
	}
	pXmlSierialize->xml_serialize("故障时间","FaultTime","s","number",pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("CT极性","CTPoint","","CTPositionPnv",pParas->m_bCTStarPoint);
	pXmlSierialize->xml_serialize("Ir制动方程","IrEquation","","IrEquationPnv",pParas->m_nIbiasCal);
	pXmlSierialize->xml_serialize("K1","K","","set",pParas->m_fFactor1);
	pXmlSierialize->xml_serialize("K2","K2","","number",pParas->m_fFactor2);
// 	pXmlSierialize->xml_serialize("额定电流","Inom","","number",pParas->m_fInom);
// 	pXmlSierialize->xml_serialize("额定电压","Vnom","","number",pParas->m_fVnom);
// 	pXmlSierialize->xml_serialize("额定频率","Fnom","Hz","number",pParas->m_fFnom);
	pXmlSierialize->xml_serialize("第一组电压常态输出值","Vg1","V","number",pParas->m_fVg1);
	pXmlSierialize->xml_serialize("第二组电压常态输出值","Vg2","V","number",pParas->m_fVg2);
	pXmlSierialize->xml_serialize("第一组电压故障态故障相输出值","Vg1_fault","V","number",pParas->m_fVg1_fault);
	pXmlSierialize->xml_serialize("第二组电压故障态故障相输出值","Vg2_fault","V","number",pParas->m_fVg2_fault);

	pXmlSierialize->xml_serialize("平衡系数设置方式","KPSetMode","","KpSetMode",pParas->m_nKcal );
	pXmlSierialize->xml_serialize("高压侧差动平衡系数设置值","KphSet","","number",pParas->m_fKph);
	pXmlSierialize->xml_serialize("中压侧差动平衡系数设置值","KpmSet","","number",pParas->m_fKpm);
	pXmlSierialize->xml_serialize("低压侧差动平衡系数设置值","KplSet","","number",pParas->m_fKpl);
	pXmlSierialize->xml_serialize("变压器额定容量","Sn","MVA","number",pParas->m_fSN);
	pXmlSierialize->xml_serialize("高压侧额定电压","HUn","kV","number",pParas->m_fUh);
	pXmlSierialize->xml_serialize("高压侧CT变比","HCt","","number",pParas->m_fCTh);
	pXmlSierialize->xml_serialize("中压侧额定电压","MUn","kV","number",pParas->m_fUm);
	pXmlSierialize->xml_serialize("中压侧CT变比","MCt","","number",pParas->m_fCTm);
	pXmlSierialize->xml_serialize("低压侧额定电压","LUn","kV","number",pParas->m_fUl);
	pXmlSierialize->xml_serialize("低压侧CT变比","LCt","","number",pParas->m_fCTl);
	pXmlSierialize->xml_serialize("高压侧绕组接线型式","WindH","","DiffConnectMode",pParas->m_nWindH);
	pXmlSierialize->xml_serialize("中压侧绕组接线型式","WindM","","DiffConnectMode",pParas->m_nWindM);
	pXmlSierialize->xml_serialize("低压侧绕组接线型式","WindL","","DiffConnectMode",pParas->m_nWindL);
	pXmlSierialize->xml_serialize("参与试验的绕组","AdoptWind","","TransHMLSel",pParas->m_nWindSide);
	pXmlSierialize->xml_serialize("保护内部相位校正方式","PhCorrectMode","","TransPhCorrectModePnv",pParas->m_nAngleMode);
	pXmlSierialize->xml_serialize("测试绕组之间角差(钟点数)","TransGroupMode","","ConnModePnv",pParas->m_nConnectMode);
	pXmlSierialize->xml_serialize("平衡系数计算","JXFactor","","JXFactorPnv",pParas->m_nJXFactor);
	pXmlSierialize->xml_serialize("搜索方法","SearchMode","","SearchModePnv",pParas->m_nSearchMode);
	//上位机单用
	pXmlSierialize->xml_serialize("高压侧CT一次值","CTPh","","number",pParas->m_fCTPh);
	pXmlSierialize->xml_serialize("中压侧CT一次值","CTPm","","number",pParas->m_fCTPm);
	pXmlSierialize->xml_serialize("低压侧CT一次值","CTPl","","number",pParas->m_fCTPl);
	pXmlSierialize->xml_serialize("高压侧CT二次值","CTSh","","number",pParas->m_fCTSh);
	pXmlSierialize->xml_serialize("中压侧CT二次值","CTSm","","number",pParas->m_fCTSm);
	pXmlSierialize->xml_serialize("低压侧CT二次值","CTSl","","number",pParas->m_fCTSl);

	// 定值相关
	pXmlSierialize->xml_serialize("定值整定方式","MinAxis","","SettingModePnv",pParas->m_bMinAxis);//++++默认标幺值
	pXmlSierialize->xml_serialize("基准电流选择", "InSel", "", "CurrentSelPnv", pParas->m_nInSel);
	pXmlSierialize->xml_serialize("基准电流设定值", "InSet", "A", "number", pParas->m_fIbase);
	pXmlSierialize->xml_serialize("差动速断电流","IQuick","In/A","number",pParas->m_fIsd);
	pXmlSierialize->xml_serialize("差动门槛电流","IDoor","In/A","number",pParas->m_fIcdqd);

	pXmlSierialize->xml_serialize("比率制动拐点数","KneePoints","","number",pParas->m_nKneePoints);
	pXmlSierialize->xml_serialize("比率制动拐点1电流","Limp1","","number",pParas->m_fIp1);
	pXmlSierialize->xml_serialize("比率制动拐点2电流","Limp2","","number",pParas->m_fIp2);
	pXmlSierialize->xml_serialize("比率制动拐点3电流","Limp3","","number",pParas->m_fIp3);

	pXmlSierialize->xml_serialize("启动段斜率","Kid0","","number",pParas->m_fKid0);
	pXmlSierialize->xml_serialize("基波比率制动特性斜率1","Kid1","","number",pParas->m_fKid1);
	pXmlSierialize->xml_serialize("基波比率制动特性斜率2","Kid2","","number",pParas->m_fKid2);
	pXmlSierialize->xml_serialize("基波比率制动特性斜率3","Kid3","","number",pParas->m_fKid3);

	//2022.5.16 caoxc
	pXmlSierialize->xml_serialize("二次谐波制动系数","CoefHarm2","","number",pParas->m_fCoefHarm2);
	pXmlSierialize->xml_serialize("三次谐波制动系数","CoefHarm3","","number",pParas->m_fCoefHarm3);
	pXmlSierialize->xml_serialize("五次谐波制动系数","CoefHarm5","","number",pParas->m_fCoefHarm5);

	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
  //	pXmlSierialize->xml_serialize("准备时间","PrepareTime","s","number",pParas->m_fPreTime);
  pXmlSierialize->xml_serialize(/* "故障前时间" */ g_sLangTxt_Native_PreFautTime.GetString(), "PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
  pXmlSierialize->xml_serialize(/* "故障时间" */ g_sLangTxt_Gradient_FailTime.GetString(), "FaultTime", "s", "number", pParas->m_fFaultTime);
  pXmlSierialize->xml_serialize(/* "CT极性" */ g_sLangTxt_State_CTpolarity.GetString(), "CTPoint", "", "CTPositionPnv", pParas->m_bCTStarPoint);
  pXmlSierialize->xml_serialize(/* "Ir制动方程" */ g_sLangTxt_Native_IrBrakeEq.GetString(), "IrEquation", "", "IrEquationPnv", pParas->m_nIbiasCal);
  pXmlSierialize->xml_serialize("K1", "K", "", "set", pParas->m_fFactor1);
  pXmlSierialize->xml_serialize("K2", "K2", "", "number", pParas->m_fFactor2);
  // 	pXmlSierialize->xml_serialize("额定电流","Inom","","number",pParas->m_fInom);
  // 	pXmlSierialize->xml_serialize("额定电压","Vnom","","number",pParas->m_fVnom);
  // 	pXmlSierialize->xml_serialize("额定频率","Fnom","Hz","number",pParas->m_fFnom);
  pXmlSierialize->xml_serialize(/* "第一组电压常态输出值" */ g_sLangTxt_Native_FirstVoltNormOutput.GetString(), "Vg1", "V", "number", pParas->m_fVg1);
  pXmlSierialize->xml_serialize(/* "第二组电压常态输出值" */ g_sLangTxt_Native_SecondVoltNormOutput.GetString(), "Vg2", "V", "number", pParas->m_fVg2);
  pXmlSierialize->xml_serialize(/* "第一组电压故障态故障相输出值" */ g_sLangTxt_Native_VoltFaultState.GetString(), "Vg1_fault", "V", "number", pParas->m_fVg1_fault);
  pXmlSierialize->xml_serialize(/* "第二组电压故障态故障相输出值" */ g_sLangTxt_Native_VoltFaultState2.GetString(), "Vg2_fault", "V", "number", pParas->m_fVg2_fault);

  pXmlSierialize->xml_serialize(/* "平衡系数设置方式" */ g_sLangTxt_Native_BalanceMode.GetString(), "KPSetMode", "", "KpSetMode", pParas->m_nKcal);
  pXmlSierialize->xml_serialize(/* "高压侧差动平衡系数设置值" */ g_sLangTxt_Native_HVBalanceCoeff.GetString(), "KphSet", "", "number", pParas->m_fKph);
  pXmlSierialize->xml_serialize(/* "中压侧差动平衡系数设置值" */ g_sLangTxt_Native_MVBalanceCoeff.GetString(), "KpmSet", "", "number", pParas->m_fKpm);
  pXmlSierialize->xml_serialize(/* "低压侧差动平衡系数设置值" */ g_sLangTxt_Native_LVBalanceCoeff.GetString(), "KplSet", "", "number", pParas->m_fKpl);
  pXmlSierialize->xml_serialize(/* "变压器额定容量" */ g_sLangTxt_Native_TransfRatedCapacity.GetString(), "Sn", "MVA", "number", pParas->m_fSN);
  pXmlSierialize->xml_serialize(/* "高压侧额定电压" */ g_sLangTxt_Native_HighVoltSideRatedVolt.GetString(), "HUn", "kV", "number", pParas->m_fUh);
  pXmlSierialize->xml_serialize(/* "高压侧CT变比" */ g_sLangTxt_Native_HVCTRatio.GetString(), "HCt", "", "number", pParas->m_fCTh);
  pXmlSierialize->xml_serialize(/* "中压侧额定电压" */ g_sLangTxt_Native_MedVoltSideRatedVolt.GetString(), "MUn", "kV", "number", pParas->m_fUm);
  pXmlSierialize->xml_serialize(/* "中压侧CT变比" */ g_sLangTxt_Native_MVCTRatio.GetString(), "MCt", "", "number", pParas->m_fCTm);
  pXmlSierialize->xml_serialize(/* "低压侧额定电压" */ g_sLangTxt_Native_LowVoltSideRatedVolt.GetString(), "LUn", "kV", "number", pParas->m_fUl);
  pXmlSierialize->xml_serialize(/* "低压侧CT变比" */ g_sLangTxt_Native_LVCTRatio.GetString(), "LCt", "", "number", pParas->m_fCTl);
  pXmlSierialize->xml_serialize(/* "高压侧绕组接线型式" */ g_sLangTxt_State_Hswindwirtype.GetString(), "WindH", "", "DiffConnectMode", pParas->m_nWindH);
  pXmlSierialize->xml_serialize(/* "中压侧绕组接线型式" */ g_sLangTxt_Native_MedVoltWindingConnType.GetString(), "WindM", "", "DiffConnectMode", pParas->m_nWindM);
  pXmlSierialize->xml_serialize(/* "低压侧绕组接线型式" */ g_sLangTxt_State_Lswindwirtype.GetString(), "WindL", "", "DiffConnectMode", pParas->m_nWindL);
  pXmlSierialize->xml_serialize(/* "参与试验的绕组" */ g_sLangTxt_Native_TestCoil.GetString(), "AdoptWind", "", "TransHMLSel", pParas->m_nWindSide);
  pXmlSierialize->xml_serialize(/* "保护内部相位校正方式" */ g_sLangTxt_Native_ProtPhaseCorr.GetString(), "PhCorrectMode", "", "TransPhCorrectModePnv", pParas->m_nAngleMode);
  pXmlSierialize->xml_serialize(/* "测试绕组之间角差(钟点数)" */ g_sLangTxt_Native_AngleDiffClockHrsTestWindings.GetString(), "TransGroupMode", "", "ConnModePnv", pParas->m_nConnectMode);
  pXmlSierialize->xml_serialize(/* "平衡系数计算" */ g_sLangTxt_State_Bfactorcalculation.GetString(), "JXFactor", "", "JXFactorPnv", pParas->m_nJXFactor);
  pXmlSierialize->xml_serialize(/* "搜索方法" */ g_sLangTxt_Native_SearchMeth.GetString(), "SearchMode", "", "SearchModePnv", pParas->m_nSearchMode);
  // 上位机单用
  pXmlSierialize->xml_serialize(/* "高压侧CT一次值" */ g_sLangTxt_Native_HVSideCTPrimVal.GetString(), "CTPh", "", "number", pParas->m_fCTPh);
  pXmlSierialize->xml_serialize(/* "中压侧CT一次值" */ g_sLangTxt_Native_MVSideCTPrimVal.GetString(), "CTPm", "", "number", pParas->m_fCTPm);
  pXmlSierialize->xml_serialize(/* "低压侧CT一次值" */ g_sLangTxt_Native_LVSideCTPrimVal.GetString(), "CTPl", "", "number", pParas->m_fCTPl);
  pXmlSierialize->xml_serialize(/* "高压侧CT二次值" */ g_sLangTxt_Native_HVSide2CTPrimVal.GetString(), "CTSh", "", "number", pParas->m_fCTSh);
  pXmlSierialize->xml_serialize(/* "中压侧CT二次值" */ g_sLangTxt_Native_MVSide2CTPrimVal.GetString(), "CTSm", "", "number", pParas->m_fCTSm);
  pXmlSierialize->xml_serialize(/* "低压侧CT二次值" */ g_sLangTxt_Native_LVSide2CTPrimVal.GetString(), "CTSl", "", "number", pParas->m_fCTSl);

  // 定值相关
  pXmlSierialize->xml_serialize(/* "定值整定方式" */ g_sLangTxt_Native_DevSetMethod.GetString(), "MinAxis", "", "SettingModePnv", pParas->m_bMinAxis);  //++++默认标幺值
  pXmlSierialize->xml_serialize(/* "基准电流选择" */ g_sLangTxt_Native_RefCurrentSel.GetString(), "InSel", "", "CurrentSelPnv", pParas->m_nInSel);
  pXmlSierialize->xml_serialize(/* "基准电流设定值" */ g_sLangTxt_Native_BaseCurrSet.GetString(), "InSet", "A", "number", pParas->m_fIbase);
  pXmlSierialize->xml_serialize(/* "差动速断电流" */ g_sLangTxt_Native_DiffQuickBreakCurr.GetString(), "IQuick", "In/A", "number", pParas->m_fIsd);
  pXmlSierialize->xml_serialize(/* "差动门槛电流" */ g_sLangTxt_Native_DiffThreshCurrent.GetString(), "IDoor", "In/A", "number", pParas->m_fIcdqd);

  pXmlSierialize->xml_serialize(/* "比率制动拐点数" */ g_sLangTxt_Native_RatioBrakeTurnPts.GetString(), "KneePoints", "", "number", pParas->m_nKneePoints);
  pXmlSierialize->xml_serialize(/* "比率制动拐点1电流" */ g_sLangTxt_Native_RatioBrakeTurn1Curr.GetString(), "Limp1", "", "number", pParas->m_fIp1);
  pXmlSierialize->xml_serialize(/* "比率制动拐点2电流" */ g_sLangTxt_Native_RatioBrakeTurn2Curr.GetString(), "Limp2", "", "number", pParas->m_fIp2);
  pXmlSierialize->xml_serialize(/* "比率制动拐点3电流" */ g_sLangTxt_Native_RatioBrakeTurn3Curr.GetString(), "Limp3", "", "number", pParas->m_fIp3);

  pXmlSierialize->xml_serialize(/* "启动段斜率" */ g_sLangTxt_Native_StartSegSlope.GetString(), "Kid0", "", "number", pParas->m_fKid0);
  pXmlSierialize->xml_serialize(/* "基波比率制动特性斜率1" */ g_sLangTxt_Native_FundRatioBrkSlope1.GetString(), "Kid1", "", "number", pParas->m_fKid1);
  pXmlSierialize->xml_serialize(/* "基波比率制动特性斜率2" */ g_sLangTxt_Native_FundRatioBrkSlope2.GetString(), "Kid2", "", "number", pParas->m_fKid2);
  pXmlSierialize->xml_serialize(/* "基波比率制动特性斜率3" */ g_sLangTxt_Native_FundRatioBrkSlope3.GetString(), "Kid3", "", "number", pParas->m_fKid3);

  // 2022.5.16 caoxc
  pXmlSierialize->xml_serialize(/* "二次谐波制动系数" */ g_sLangTxt_Native_SecHarBrkCoef.GetString(), "CoefHarm2", "", "number", pParas->m_fCoefHarm2);
  pXmlSierialize->xml_serialize(/* "三次谐波制动系数" */ g_sLangTxt_Native_ThiHarBrkCoef.GetString(), "CoefHarm3", "", "number", pParas->m_fCoefHarm3);
  pXmlSierialize->xml_serialize(/* "五次谐波制动系数" */ g_sLangTxt_Native_FivHarBrkCoef.GetString(), "CoefHarm5", "", "number", pParas->m_fCoefHarm5);

  pXmlSierialize->xml_serialize(/* "开入逻辑" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_thr(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_thr(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("差动动作值", "Iqd", "In/A", "number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("动作描述","ActFlag","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("比例制动系数","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "差动动作值" */ g_sLangTxt_Native_DiffActionVal.GetString(), "Iqd", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "比例制动系数" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);  // yyj add
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_rate(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("当前搜索值","CurrentId","In/A","number",pResults->m_fIdiffSettingValue);
	pXmlSierialize->xml_serialize("差动动作值","TripId","In/A","number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("差动动作描述","ActId","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("制动电流","TripIr","In/A","number",pResults->m_fIbiasValue);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2(Ie)","TripI2Ie","Ie","number",pResults->m_fI2Ie);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
	pXmlSierialize->xml_serialize("比例制动系数","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
  pXmlSierialize->xml_serialize(/* "当前搜索值" */ g_sLangTxt_Native_CurrSearchVal.GetString(), "CurrentId", "In/A", "number", pResults->m_fIdiffSettingValue);
  pXmlSierialize->xml_serialize(/* "差动动作值" */ g_sLangTxt_Native_DiffActionVal.GetString(), "TripId", "In/A", "number", pResults->m_fIdiffActValue);
  pXmlSierialize->xml_serialize(/* "差动动作描述" */ g_sLangTxt_Native_DiffActionDesc.GetString(), "ActId", "", "number", pResults->m_nActFlag);
  pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_Native_ControlCurrent.GetString(), "TripIr", "In/A", "number", pResults->m_fIbiasValue);
  pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
  pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
  pXmlSierialize->xml_serialize("I2(Ie)", "TripI2Ie", "Ie", "number", pResults->m_fI2Ie);
  pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
  pXmlSierialize->xml_serialize(/* "比例制动系数" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_quick(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_quick(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize_harm(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.16 caoxc
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

void stt_xml_serialize_harm(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize_acttime(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.16 caoxc
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

void stt_xml_serialize_acttime(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作时间", "TripTime", "s", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("动作描述","ActFlag","","number",pResults->m_nActFlag);
#else
  pXmlSierialize->xml_serialize(/* "动作时间" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);
  pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
#endif
}

void stt_xml_serialize_6i_rate_pnv(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
    stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
    pXmlSierialize->xml_serialize("故障后持续时间","AfterFaultTime","s","number",pParas->m_fAfterFaultTime);
    pXmlSierialize->xml_serialize("故障前电流","m_PreFaultIp","","number",pParas->m_fPreFaultIp);
    pXmlSierialize->xml_serialize("输出电压幅值","VzAmp","","number",pParas->m_fVzAmp);
    pXmlSierialize->xml_serialize("差动电流定值","IdSet","A","number",pParas->m_fIdSetting);
    pXmlSierialize->xml_serialize("I1侧电流补偿系数","KP1","","number",pParas->m_fKph);//按照高低侧存储，后续根据绕组赋值xuzhantao240301
    pXmlSierialize->xml_serialize("I2侧电流补偿系数","KP2","","number",pParas->m_fKpl);
    pXmlSierialize->xml_serialize("开入逻辑","AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

#ifndef _STT_NOT_IN_TEST_SERVER_
	pXmlSierialize->xml_serialize("0-主板的开入开出，1-主板+扩展的开入开出","BinBoutMode","","long",g_theSystemConfig->m_nBinBoutMode);
#endif

    stt_xml_serialize_diff_6i_binary_in_pnv(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_diff_6i_binary_out_pnv(pParas->m_binOut, pXmlSierialize);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_6i_rate_pnv(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
    {
    stt_xml_serialize_rate(pResults,pXmlSierialize);
    pXmlSierialize->xml_serialize("动作标记","TripFlag","","number",pResults->m_nActFlag);
    pXmlSierialize->xml_serialize("结果判断","RsltJdg","","number",pResults->m_nActFlag);
    pXmlSierialize->xml_serialize("结果描述","RsltDsc","","number",pResults->m_nActFlag);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_6i_harm_pnv(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("变化始值","BeginVal","%","number",pParas->m_fScanFrom);
    pXmlSierialize->xml_serialize("变化终值","EndVal","%","number",pParas->m_fScanTo);
    pXmlSierialize->xml_serialize("测试精度","Step","%","number",pParas->m_fStep);
    pXmlSierialize->xml_serialize("差动电流","Id","In/A","number",pParas->m_fIdiff);
    pXmlSierialize->xml_serialize("谐波次数","HarmIndex","","DiffHarmIndex",pParas->m_nHarmIndex);
    pXmlSierialize->xml_serialize("故障类型","FaultType","","PsuDiffFaultType",pParas->m_nPhase);
    pXmlSierialize->xml_serialize("谐波制动系数定值","RateHarmSet","","number",pParas->m_fCoefHarm2);
    pXmlSierialize->xml_serialize("故障后持续时间","AfterFaultTime","s","number",pParas->m_fAfterFaultTime);
    pXmlSierialize->xml_serialize("输出电压幅值","VzAmp","","number",pParas->m_fVzAmp);
    pXmlSierialize->xml_serialize("I1侧电流补偿系数","KP1","","number",pParas->m_fKph);//按照高低侧存储，后续根据绕组赋值xuzhantao240301
    pXmlSierialize->xml_serialize("I2侧电流补偿系数","KP2","","number",pParas->m_fKpl);
    pXmlSierialize->xml_serialize("开入逻辑","AndOr","","InPutLogic",pParas->m_nBinLogic);
    pXmlSierialize->xml_serialize("谐波施加侧","HarmPos","","HarmPos",pParas->m_nHarmPos);
    pXmlSierialize->xml_serialize("Ir制动方程","IrEquation","","IrEquationI1I2",pParas->m_nIdiffCal);
    pXmlSierialize->xml_serialize("保护内部零序修正方式","PhCorrectMode","","TransPhCorrectMode",pParas->m_nY0CorrectMode);
    stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
    stt_xml_serialize_diff_6i_binary_in_pnv(pParas->m_binIn,pXmlSierialize);
    stt_xml_serialize_diff_6i_binary_out_pnv(pParas->m_binOut, pXmlSierialize);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_6i_harm_pnv(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_harm(pResults,pXmlSierialize);
    pXmlSierialize->xml_serialize("动作标记","TripFlag","","number",pResults->m_nActFlag);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttXmlSerializeBase* stt_xml_serialize(tmt_DiffCurrThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
//	stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest) == 0)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas),  pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("类型", "ThrType", "", "number", ((tmt_DiffCurrThrTest*)pTests)->m_nThrType);
#else
      pXmlParas->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_DiffCurrThrTest *)pTests)->m_nThrType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest) == 0)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("类型", "RateType", "", "number", ((tmt_DiffCurrRateTest*)pTests)->m_nRateType);
#else
      pXmlParas->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_DiffCurrRateTest *)pTests)->m_nRateType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest) == 0)
		{
			stt_xml_serialize_quick(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest) == 0)
		{
			stt_xml_serialize_harm(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDiffCurrParas),  pXmlParas);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IRateRestrainSearchTest) == 0)
        {
            stt_xml_serialize_6i_rate_pnv(&(pTests->m_oDiffCurrParas),  pXmlParas);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IHarmRestrainSearchTest) == 0)
        {
            stt_xml_serialize_6i_harm_pnv(&(pTests->m_oDiffCurrParas),  pXmlParas);
        }
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest) == 0)
		{
			stt_xml_serialize_thr(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest) == 0)
		{
			stt_xml_serialize_rate(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest) == 0)
		{
			stt_xml_serialize_quick(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest) == 0)
		{
			stt_xml_serialize_harm(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&pTests->m_oDiffCurrResults,  pXmlResults);
		}
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IRateRestrainSearchTest) == 0)
        {
            stt_xml_serialize_6i_rate_pnv(&pTests->m_oDiffCurrResults,  pXmlResults);
        }
        else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IHarmRestrainSearchTest) == 0)
        {
            stt_xml_serialize_6i_harm_pnv(&pTests->m_oDiffCurrResults,  pXmlResults);
        }
	}

	return pXmlParas;
}

void stt_xml_serialize(tmt_DiffCurrThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTCurrTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffTCurrTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_thr(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("类型", "ThrType", "", "number", ((tmt_DiffCurrThrTest*)pTests)->m_nThrType);
#else
      pXmlSerialize->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_DiffCurrThrTest *)pTests)->m_nThrType);
#endif
		}

		stt_xml_serialize_thr(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffRateTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffRateTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_rate(&(pTests->m_oDiffCurrParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("类型", "RateType", "", "number", ((tmt_DiffCurrRateTest*)pTests)->m_nRateType);
#else
      pXmlSerialize->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_DiffCurrRateTest *)pTests)->m_nRateType);
#endif
		}

		stt_xml_serialize_rate(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffQuickTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffQuickTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_quick(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_quick(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffHarmTest) == 0 || strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuManuDiffHarmTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_harm(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_harm(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_PsuDiffTimeTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDiffCurrParas), pXmlSerialize);
		}

		stt_xml_serialize_acttime(&(pTests->m_oDiffCurrResults), pXmlSerialize);
	}

     else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IRateRestrainSearchTest) == 0)
      {
            if(!bResultOnly)
            {
                stt_xml_serialize_6i_rate_pnv(&(pTests->m_oDiffCurrParas), pXmlSerialize);
            }

            stt_xml_serialize_6i_rate_pnv(&(pTests->m_oDiffCurrParas), pXmlSerialize);
    }
    else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_Diff6IHarmRestrainSearchTest) == 0)
     {
           if(!bResultOnly)
           {
               stt_xml_serialize_6i_harm_pnv(&(pTests->m_oDiffCurrParas), pXmlSerialize);
           }

           stt_xml_serialize_6i_harm_pnv(&(pTests->m_oDiffCurrParas), pXmlSerialize);
   }
}
