#include "stdafx.h"
#include "tmt_dc_increment_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_DcIncrementParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DcIncrementParas));
	pParas->init();
}

void stt_init_results(tmt_DcIncrementResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DcIncrementResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_DcIncrement(tmt_DcIncrementParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("Ua初值","U1","V","number",pParas->m_fVolAmp[0]);
	pXmlSierialize->xml_serialize("Ub初值","U2","V","number",pParas->m_fVolAmp[1]);
	pXmlSierialize->xml_serialize("Uc初值","U3","V","number",pParas->m_fVolAmp[2]);
	pXmlSierialize->xml_serialize("Uz初值","U4","V","number",pParas->m_fVolAmp[3]);

	pXmlSierialize->xml_serialize("Ia初值","I1","A","number",pParas->m_fCurAmp[0]);
	pXmlSierialize->xml_serialize("Ib初值","I2","A","number",pParas->m_fCurAmp[1]);
	pXmlSierialize->xml_serialize("Ic初值","I3","A","number",pParas->m_fCurAmp[2]);

	pXmlSierialize->xml_serialize("准备时间","PrepareTime","s","number",pParas->m_fPrepTime);
	pXmlSierialize->xml_serialize("曲线段数","CurveNum","","number",pParas->m_nCurveNum);

	pXmlSierialize->xml_serialize("递变通道","GradientChIndex","","DcIncGradIndex",pParas->m_nGradientChIndex);
	pXmlSierialize->xml_serialize("计时曲线","TimingCurveIndex","","DcIncCurveSel",pParas->m_nTimingCurveIndex);
	pXmlSierialize->xml_serialize("递变选择","GradientSelect","","number",pParas->m_nGradSelected);
	pXmlSierialize->xml_serialize("递变类型(0-斜率1-上升时间2-初值)","GradType","","DcIncGradType",pParas->m_nGradType);
	pXmlSierialize->xml_serialize("递变曲线选择","GradCurveSel","","DcIncCurveSel",pParas->m_nGradCurveSel);

	pXmlSierialize->xml_serialize("递变始值","GradStart","","number",pParas->m_fScanFrom);
	pXmlSierialize->xml_serialize("递变终值","GradEnd","","number",pParas->m_fScanTo);
	pXmlSierialize->xml_serialize("递变步长","GradStep","","number",pParas->m_fStep);
	CString strName,strID,strDesc1,strDesc2,strDesc3,strIndex;
	strDesc1 = _T("曲线");
	strDesc2 = _T("斜率(A/ms)");
	strDesc3 = _T("输出时间(ms)");
#else
  pXmlSierialize->xml_serialize(/* "Ua初值" */ g_sLangTxt_Native_UaInitVal.GetString(), "U1", "V", "number", pParas->m_fVolAmp[0]);
  pXmlSierialize->xml_serialize(/* "Ub初值" */ g_sLangTxt_Native_UbInitVal.GetString(), "U2", "V", "number", pParas->m_fVolAmp[1]);
  pXmlSierialize->xml_serialize(/* "Uc初值" */ g_sLangTxt_Native_UcInitVal.GetString(), "U3", "V", "number", pParas->m_fVolAmp[2]);
  pXmlSierialize->xml_serialize(/* "Uz初值" */ g_sLangTxt_Native_UzInitVal.GetString(), "U4", "V", "number", pParas->m_fVolAmp[3]);

  pXmlSierialize->xml_serialize(/* "Ia初值" */ g_sLangTxt_Native_IaInitVal.GetString(), "I1", "A", "number", pParas->m_fCurAmp[0]);
  pXmlSierialize->xml_serialize(/* "Ib初值" */ g_sLangTxt_Native_IbInitVal.GetString(), "I2", "A", "number", pParas->m_fCurAmp[1]);
  pXmlSierialize->xml_serialize(/* "Ic初值" */ g_sLangTxt_Native_IcInitVal.GetString(), "I3", "A", "number", pParas->m_fCurAmp[2]);

  pXmlSierialize->xml_serialize(/* "准备时间" */ g_sLangTxt_Native_PrepTime, "PrepareTime", "s", "number", pParas->m_fPrepTime);
  pXmlSierialize->xml_serialize(/* "曲线段数" */ g_sLangTxt_Native_CurveSegments.GetString(), "CurveNum", "", "number", pParas->m_nCurveNum);

  pXmlSierialize->xml_serialize(/* "递变通道" */ g_sLangTxt_Native_VarChnl.GetString(), "GradientChIndex", "", "DcIncGradIndex", pParas->m_nGradientChIndex);
  pXmlSierialize->xml_serialize(/* "计时曲线" */ g_sLangTxt_Native_TimingCurve.GetString(), "TimingCurveIndex", "", "DcIncCurveSel", pParas->m_nTimingCurveIndex);
  pXmlSierialize->xml_serialize(/* "递变选择" */ g_sLangTxt_Native_VarSel.GetString(), "GradientSelect", "", "number", pParas->m_nGradSelected);
  pXmlSierialize->xml_serialize(/* "递变类型(0-斜率1-上升时间2-初值)" */ g_sLangTxt_Native_TransType.GetString(), "GradType", "", "DcIncGradType", pParas->m_nGradType);
  pXmlSierialize->xml_serialize(/* "递变曲线选择" */ g_sLangTxt_Native_CurveSelect.GetString(), "GradCurveSel", "", "DcIncCurveSel", pParas->m_nGradCurveSel);

  pXmlSierialize->xml_serialize(/* "递变始值" */ g_sLangTxt_Native_StartValue.GetString(), "GradStart", "", "number", pParas->m_fScanFrom);
  pXmlSierialize->xml_serialize(/* "递变终值" */ g_sLangTxt_Native_EndValue.GetString(), "GradEnd", "", "number", pParas->m_fScanTo);
  pXmlSierialize->xml_serialize(/* "递变步长" */ g_sLangTxt_Native_StepSize.GetString(), "GradStep", "", "number", pParas->m_fStep);
  CString strName, strID, strDesc1, strDesc2, strDesc3, strIndex;
  strDesc1 = /* _T("曲线") */ g_sLangTxt_Native_Curve;
  strDesc2 = /* _T("斜率(A/ms)") */ g_sLangTxt_Native_Slope;
  strDesc3 = /* _T("输出时间(ms)") */ g_sLangTxt_Native_OutputTimems;
#endif

	for (int nIndex = 0;nIndex<pParas->m_nCurveNum;nIndex++)
	{
		strIndex.Format(_T("%ld"),nIndex);
		strName = strDesc1 + strIndex + strDesc2;
		strID.Format(_T("Curve%ld_DaDt"),nIndex);
		pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"A/ms","number",pParas->m_fDaDt[nIndex]);

		strName = strDesc1 + strIndex + strDesc3;
		strID.Format(_T("Curve%ld_OutputTime"),nIndex);
		pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"A/ms","number",pParas->m_fOutputTime[nIndex]);
	}

	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
  pXmlSierialize->xml_serialize(/* "开入逻辑" */ g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_DcIncrement(tmt_DcIncrementResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作值","TripValue","A","number",pResults->m_fActValue);
	pXmlSierialize->xml_serialize("动作时间", "ActTime", "s", "number",pResults->m_fActTime);
	pXmlSierialize->xml_serialize("动作描述", "ActFlag", "", "number",pResults->m_nAct);
#else
  pXmlSierialize->xml_serialize(/* "动作值" */ g_sLangTxt_State_ActionValue.GetString(), "TripValue", "A", "number", pResults->m_fActValue);
  pXmlSierialize->xml_serialize(/* "动作时间" */ g_sLangTxt_Gradient_ActionTime.GetString(), "ActTime", "s", "number", pResults->m_fActTime);
  pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nAct);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttXmlSerializeBase* stt_xml_serialize(tmt_DcIncrementTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_DcIncrementTest) == 0)
		{
			stt_xml_serialize_DcIncrement(&(pTests->m_oDcIncParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_DcIncrementTest) == 0)
		{
			stt_xml_serialize_DcIncrement(&pTests->m_oDcIncResults, pXmlResults);
		}
	}

	return pXmlParas;
}
