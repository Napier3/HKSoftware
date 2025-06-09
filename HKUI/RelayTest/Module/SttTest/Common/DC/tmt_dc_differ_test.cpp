#include "stdafx.h"
#include "tmt_dc_differ_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_DcDifferCurParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DcDifferCurParas));
	pParas->init();
}

void stt_init_results(tmt_DcDifferCurResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DcDifferCurResults));
	pResults->init();
}

void stt_xml_serialize_diff_search_results(tmt_DcDifferCurParas *pParas,tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("当前值","CurrSearchVal","","number",pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2(Ie)","TripI2Ie","Ie","number",pResults->m_fI2Ie);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
	pXmlSierialize->xml_serialize("制动电流","Ir","","number",pParas->m_fIbias);
#else
	pXmlSierialize->xml_serialize(/* "当前值" */ g_sLangTxt_Native_CurrentValue.GetString(), "CurrSearchVal", "", "number", pParas->m_fCurrScanVal);
	pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2(Ie)", "TripI2Ie", "Ie", "number", pResults->m_fI2Ie);
	pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
	pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_Native_ControlCurrent.GetString(), "Ir", "", "number", pParas->m_fIbias);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
void stt_xml_serialize_common_fault_paras(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.12 caoxc
	if(!pXmlSierialize->xml_serialize("项目名称", "TestName", "", "string", pParas->m_pszTestName))
	{
		memset(pParas->m_pszTestName, 0, EXPR_MAX_COUNT);
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("变化始值","BeginVal","In/A","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("变化终值","EndVal","In/A","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("测试精度","Step","In/A","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("制动电流","Ir","A","number",pParas->m_fIbias);
#else
	pXmlSierialize->xml_serialize(/* "变化始值" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "In/A", "number", pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize(/* "变化终值" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "In/A", "number", pParas->m_fScanTo);
	pXmlSierialize->xml_serialize(/* "测试精度" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "In/A", "number", pParas->m_fStep);
	pXmlSierialize->xml_serialize(/* "制动电流" */ g_sLangTxt_State_BrakingCur.GetString(), "Ir", "A", "number", pParas->m_fIbias);
#endif
}

void stt_xml_serialize_common_sys_paras(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//通用参数相关
	pXmlSierialize->xml_serialize("变化前时间", "PrepareTime", "s", "number", pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("故障前时间", "PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("故障时间裕度", "MarginTime", "s", "number", pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("平衡系数1", "BalK1", "", "number", pParas->m_fK1);
	pXmlSierialize->xml_serialize("平衡系数2", "BalK2", "", "number", pParas->m_fK2);
	pXmlSierialize->xml_serialize("电流1通道", "CurChannel1", "", "UIRampChannel", pParas->m_nCurChannel1);
	pXmlSierialize->xml_serialize("电流2通道", "CurChannel2", "", "UIRampChannel", pParas->m_nCurChannel2);
	pXmlSierialize->xml_serialize("搜索模式", "SearchMode", "", "SearchModePnv", pParas->m_nSearchMode);

	pXmlSierialize->xml_serialize("Ir制动方程", "IrEquation", "", "IrEquationPnv", pParas->m_nIbiasCal);
	pXmlSierialize->xml_serialize("差动方程", "DiffEquation", "", "IrEquationPnv", pParas->m_nDiffCal);

	pXmlSierialize->xml_serialize("K1", "K1", "", "set", pParas->m_fFactor1);
	pXmlSierialize->xml_serialize("K2", "K2", "", "number", pParas->m_fFactor2);
	pXmlSierialize->xml_serialize("测试精度", "Step", "", "number", pParas->m_fStep);

	// 定值相关
	pXmlSierialize->xml_serialize("启动电流", "CurrStart", "", "number", pParas->m_fIStart);
        pXmlSierialize->xml_serialize("启动段斜率","Kid0","","number",pParas->m_fKid0);
	pXmlSierialize->xml_serialize("比率制动拐点数", "KneePoints", "", "number", pParas->m_nKneePoints);
	pXmlSierialize->xml_serialize("比率制动拐点1电流", "Limp1", "", "number", pParas->m_fIp1);
	pXmlSierialize->xml_serialize("比率制动拐点2电流", "Limp2", "", "number", pParas->m_fIp2);
	pXmlSierialize->xml_serialize("比率制动系数1", "KRation1", "", "number", pParas->m_fKRation1);
	pXmlSierialize->xml_serialize("比率制动系数2", "KRation2", "", "number", pParas->m_fKRation2);
	pXmlSierialize->xml_serialize("动作时间", "ActTime", "", "number", pParas->m_fActTime);
	pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);
}

void stt_xml_serialize_thr(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

void stt_xml_serialize_thr(tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("差动动作值", "Iqd", "In/A", "number",pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize("动作描述","ActFlag","","number",pResults->m_nActFlag);
	pXmlSierialize->xml_serialize("比例制动系数","RateKid","","number",pResults->m_fRateKid);
#else
	pXmlSierialize->xml_serialize(/* "差动动作值" */ g_sLangTxt_Native_DiffActionVal.GetString(), "Iqd", "In/A", "number", pResults->m_fIdiffActValue);
	pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
	pXmlSierialize->xml_serialize(/* "比例制动系数" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);
#endif
}

void stt_xml_serialize_rate(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_common_fault_paras(pParas,pXmlSierialize);
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}

void stt_xml_serialize_rate(tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("当前搜索值","CurrentId","In/A","number",pResults->m_fIdiffSettingValue);
	pXmlSierialize->xml_serialize("I1(Ie)","TripI1Ie","Ie","number",pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A","TripI1A","In/A","number",pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2(Ie)","TripI2Ie","Ie","number",pResults->m_fI2Ie);
	pXmlSierialize->xml_serialize("I2A","TripI2A","In/A","number",pResults->m_fI2);
	pXmlSierialize->xml_serialize("比例制动系数","RateKid","","number",pResults->m_fRateKid); //yyj add 
#else
	pXmlSierialize->xml_serialize(/* "当前搜索值" */ g_sLangTxt_Native_CurrSearchVal.GetString(), "CurrentId", "In/A", "number", pResults->m_fIdiffSettingValue);
	pXmlSierialize->xml_serialize("I1(Ie)", "TripI1Ie", "Ie", "number", pResults->m_fI1Ie);
	pXmlSierialize->xml_serialize("I1A", "TripI1A", "In/A", "number", pResults->m_fI1);
	pXmlSierialize->xml_serialize("I2(Ie)", "TripI2Ie", "Ie", "number", pResults->m_fI2Ie);
	pXmlSierialize->xml_serialize("I2A", "TripI2A", "In/A", "number", pResults->m_fI2);
	pXmlSierialize->xml_serialize(/* "比例制动系数" */ g_sLangTxt_Native_ProportionalBrakingFactor.GetString(), "RateKid", "", "number", pResults->m_fRateKid);
#endif
}

void stt_xml_serialize_acttime(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	//2022.5.16 caoxc
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("项目名称", "TestName", "", "string", pParas->m_pszTestName);
	pXmlSierialize->xml_serialize("制动电流","Ir","In/A","number",pParas->m_fIbias);
	pXmlSierialize->xml_serialize("差动电流","Id","In/A","number",pParas->m_fIdiff);
#else
	pXmlSierialize->xml_serialize(/* "项目名称" */ g_sLangTxt_Native_ProjName.GetString(), "TestName", "", "string", pParas->m_pszTestName);
	pXmlSierialize->xml_serialize( "制动电流" , "Ir", "In/A", "number", pParas->m_fIbias);
	pXmlSierialize->xml_serialize(/* "差动电流" */ g_sLangTxt_State_DifferentCur.GetString(), "Id", "In/A", "number", pParas->m_fIdiff);

#endif
	stt_xml_serialize_common_sys_paras(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_acttime(tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作时间", "TripTime", "s", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("动作描述","ActFlag","","number",pResults->m_nActFlag);
#else
	pXmlSierialize->xml_serialize(/* "动作时间" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
#endif
}


CSttXmlSerializeBase* stt_xml_serialize(tmt_DcDifferCurTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	//	stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferCurrTest) == 0)
		{
			stt_xml_serialize_thr(&(pTests->m_oDcDifferCurParas),  pXmlParas);
#ifdef NOT_USE_XLANGUAGE
            pXmlParas->xml_serialize("类型", "ThrType", "", "number", ((tmt_DcDifferCurTest*)pTests)->m_nThrType);
#else
			pXmlParas->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_DcDifferCurTest *)pTests)->m_nThrType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferRateTest) == 0)
		{
			stt_xml_serialize_rate(&(pTests->m_oDcDifferCurParas), pXmlParas);
#ifdef NOT_USE_XLANGUAGE
			pXmlParas->xml_serialize("类型", "RateType", "", "number", ((tmt_DcDifferCurRateTest*)pTests)->m_nRateType);
#else
			pXmlParas->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_DcDifferCurRateTest *)pTests)->m_nRateType);
#endif
		}
		else if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDcDifferCurParas),  pXmlParas);
		}
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferCurrTest) == 0)
		{
			stt_xml_serialize_thr(&pTests->m_oDcDifferCurResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferRateTest) == 0)
		{
			stt_xml_serialize_rate(&pTests->m_oDcDifferCurResults, pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferTimeTest) == 0)
		{
			stt_xml_serialize_acttime(&pTests->m_oDcDifferCurResults, pXmlResults);
		}
		
	}

	return pXmlParas;
}

void stt_xml_serialize(tmt_DcDifferCurTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferCurrTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_thr(&(pTests->m_oDcDifferCurParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("类型", "ThrType", "", "number", ((tmt_DcDifferCurTest*)pTests)->m_nThrType);
#else
			pXmlSerialize->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "ThrType", "", "number", ((tmt_DcDifferCurTest *)pTests)->m_nThrType);
#endif
		}

		stt_xml_serialize_thr(&(pTests->m_oDcDifferCurResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferRateTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_rate(&(pTests->m_oDcDifferCurParas), pXmlSerialize);
#ifdef NOT_USE_XLANGUAGE
			pXmlSerialize->xml_serialize("类型", "RateType", "", "number", ((tmt_DcDifferCurRateTest*)pTests)->m_nRateType);
#else
			pXmlSerialize->xml_serialize(/* "类型" */ g_sLangTxt_Type.GetString(), "RateType", "", "number", ((tmt_DcDifferCurRateTest *)pTests)->m_nRateType);
#endif
		}

		stt_xml_serialize_rate(&(pTests->m_oDcDifferCurResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferTimeTest) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_acttime(&(pTests->m_oDcDifferCurParas), pXmlSerialize);
		}

		stt_xml_serialize_acttime(&(pTests->m_oDcDifferCurResults), pXmlSerialize);
	}
}

#include"../../../../../Module/API/GlobalConfigApi.h"
#include"../../../SttCmd/SttTestCmd.h"
void stt_xml_serialize_write_DCDifferTest()
{
	tmt_DcDifferCurTest oDcDifferTest;
	oDcDifferTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeRegister(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
// 	if (strcmp(oDcDifferTest->m_pszMacroID, STT_MACRO_ID_DCDifferCurrTest) == 0)
// 	{
// 		stt_xml_serialize_thr(&(oDcDifferTest->m_oDcDifferCurParas),  pXmlParas);
// 	}
// 	else if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferRateTest) == 0)
// 	{
// 		stt_xml_serialize_rate(&(pTests->m_oDcDifferCurParas), pXmlSerialize);
// 	}
// 	else if (strcmp(pTests->m_pszMacroID, STT_MACRO_ID_DCDifferTimeTest) == 0)
// 	{
// 		stt_xml_serialize_acttime(&(pTests->m_oDcDifferCurParas), pXmlSerialize);
// 	}
	stt_xml_serialize_common_fault_paras(&oDcDifferTest.m_oDcDifferCurParas,pMacroParas);
	stt_xml_serialize_common_sys_paras(&oDcDifferTest.m_oDcDifferCurParas, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("DcDifferTestDemo.xml");
	//  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
