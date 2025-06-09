#include "stdafx.h"
#include "tmt_power_direction_test.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_PowerDirectionParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_PowerDirectionParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_PowerDirectionParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_PowerDirectionParasEx));
	pParas->init();
}


void stt_init_results(tmt_PowerDirectionResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_PowerDirectionResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_PowerDirectionParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("测试相","TestPhase","","PsuPDTestPhase",pParas->m_nTestPhase);
	pXmlSierialize->xml_serialize("故障相","FaultPhase","","PsuPDFaultPhase",pParas->m_nFaultPhase);
	pXmlSierialize->xml_serialize("故障电压","FaultVolt","V","number",pParas->m_fSCVoltage);
	pXmlSierialize->xml_serialize("故障电流","FaultCurrent","A","number",pParas->m_fSCCurrent);
	pXmlSierialize->xml_serialize("变化始值","StartValue","°","number",pParas->m_fStart);
	pXmlSierialize->xml_serialize("变化终值","EndValue","°","number",pParas->m_fStop);
	pXmlSierialize->xml_serialize("变化步长","StepValue","°","number",pParas->m_fStep);
	pXmlSierialize->xml_serialize("故障时间","FaultTime","s","number",pParas->m_fStepTime);

	pXmlSierialize->xml_serialize("角度定义","AngleMode","","PsuPDAngleMode",pParas->m_nAngleMode);
	pXmlSierialize->xml_serialize("接线方式","ConnectMode","","ConnectType",pParas->m_nConnectMode);
#else
  pXmlSierialize->xml_serialize(/* "测试相" */ g_sLangTxt_State_Testphase.GetString(), "TestPhase", "", "PsuPDTestPhase", pParas->m_nTestPhase);
  pXmlSierialize->xml_serialize(/* "故障相" */ g_sLangTxt_CharLib_FaultPhase.GetString(), "FaultPhase", "", "PsuPDFaultPhase", pParas->m_nFaultPhase);
  pXmlSierialize->xml_serialize(/* "故障电压" */ g_sLangTxt_Native_FaultVoltage.GetString(), "FaultVolt", "V", "number", pParas->m_fSCVoltage);
  pXmlSierialize->xml_serialize(/* "故障电流" */ g_sLangTxt_Native_FaultCurrValue.GetString(), "FaultCurrent", "A", "number", pParas->m_fSCCurrent);
  pXmlSierialize->xml_serialize(/* "变化始值" */ g_sLangTxt_Gradient_Init.GetString(), "StartValue", "°", "number", pParas->m_fStart);
  pXmlSierialize->xml_serialize(/* "变化终值" */ g_sLangTxt_Gradient_Finish.GetString(), "EndValue", "°", "number", pParas->m_fStop);
  pXmlSierialize->xml_serialize(/* "变化步长" */ g_sLangTxt_Gradient_Step.GetString(), "StepValue", "°", "number", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "故障时间" */ g_sLangTxt_Gradient_Time.GetString(), "FaultTime", "s", "number", pParas->m_fStepTime);

  pXmlSierialize->xml_serialize(/* "角度定义" */ g_sLangTxt_Native_AngDef.GetString(), "AngleMode", "", "PsuPDAngleMode", pParas->m_nAngleMode);
  pXmlSierialize->xml_serialize(/* "接线方式" */ g_sLangTxt_Native_ConnMethod.GetString(), "ConnectMode", "", "ConnectType", pParas->m_nConnectMode);
#endif
	stt_xml_serialize_common(pParas,pXmlSierialize);

	//整定值
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("最大灵敏角","MTA","","number",pParas->m_fMaxSensAngle);
	pXmlSierialize->xml_serialize(_T("超前角度"),_T("Lead"),"","number",pParas->m_fLeadAngle);
	pXmlSierialize->xml_serialize(_T("滞后角度"),_T("Lag"),"","number",pParas->m_fLagAngle);
#else
  pXmlSierialize->xml_serialize(/* "最大灵敏角" */ g_sLangTxt_Gradient_MaxAngle.GetString(), "MTA", "", "number", pParas->m_fMaxSensAngle);
  pXmlSierialize->xml_serialize(/* _T("超前角度") */ g_sLangTxt_Native_LeadAngle.GetString(), _T("Lead"), "", "number", pParas->m_fLeadAngle);
  pXmlSierialize->xml_serialize(/* _T("滞后角度") */ g_sLangTxt_Native_LagAngle.GetString(), _T("Lag"), "", "number", pParas->m_fLagAngle);
#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_ex(tmt_PowerDirectionParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("变化始值(表达式)", "BeginValExp", "", "string",pParas->m_pszStart);
	pXmlSierialize->xml_serialize("变化终值(表达式)", "EndValExp", "", "string", pParas->m_pszStop );
	pXmlSierialize->xml_serialize("步长时间(表达式)", "StepTimeExp", "", "string", pParas->m_pszStepTime);
	pXmlSierialize->xml_serialize("短路电压(表达式)", "VSet1Exp", "", "string", pParas->m_pszSCVoltage);
	pXmlSierialize->xml_serialize("短路电流(表达式)", "ISet1Exp", "", "string",pParas->m_pszSCCurrent);
#else
  pXmlSierialize->xml_serialize(/* "变化始值(表达式)" */ g_sLangTxt_Native_VarStartValue.GetString(), "BeginValExp", "", "string", pParas->m_pszStart);
  pXmlSierialize->xml_serialize(/* "变化终值(表达式)" */ g_sLangTxt_Native_VarEndValue.GetString(), "EndValExp", "", "string", pParas->m_pszStop);
  pXmlSierialize->xml_serialize(/* "步长时间(表达式)" */ g_sLangTxt_Native_StepTime.GetString(), "StepTimeExp", "", "string", pParas->m_pszStepTime);
  pXmlSierialize->xml_serialize(/* "短路电压(表达式)" */ g_sLangTxt_Native_ShortVolt.GetString(), "VSet1Exp", "", "string", pParas->m_pszSCVoltage);
  pXmlSierialize->xml_serialize(/* "短路电流(表达式)" */ g_sLangTxt_Native_ShortCurr.GetString(), "ISet1Exp", "", "string", pParas->m_pszSCCurrent);
#endif
	stt_xml_serialize(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_power_dir(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("边界角1","AngleF","","number",pResults->m_oMaxAngle.m_fAngleF);
	pXmlSierialize->xml_serialize("边界角2","AngleS","","number",pResults->m_oMaxAngle.m_fAngleS);
#else
  pXmlSierialize->xml_serialize(/* "边界角1" */ g_sLangTxt_Native_BoundAngle1.GetString(), "AngleF", "", "number", pResults->m_oMaxAngle.m_fAngleF);
  pXmlSierialize->xml_serialize(/* "边界角2" */ g_sLangTxt_Native_BoundAngle2.GetString(), "AngleS", "", "number", pResults->m_oMaxAngle.m_fAngleS);
#endif
	if (stt_xml_serialize_is_write(pXmlSierialize) || stt_xml_serialize_is_register(pXmlSierialize))//兼容处理
	{
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("边界角1(兼容)","Angle1","","number",pResults->m_oMaxAngle.m_fAngleF);
		pXmlSierialize->xml_serialize("边界角2(兼容)","Angle2","","number",pResults->m_oMaxAngle.m_fAngleS);
#else
                 pXmlSierialize->xml_serialize(/* "边界角1(兼容)" */ g_sLangTxt_Native_BoundaryAngle1.GetString(), "Angle1", "", "number", pResults->m_oMaxAngle.m_fAngleF);
                pXmlSierialize->xml_serialize(/* "边界角2(兼容)" */ g_sLangTxt_Native_BoundaryAngle2.GetString(), "Angle2", "", "number", pResults->m_oMaxAngle.m_fAngleS);
#endif
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("最大灵敏角","MaxAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
        pXmlSierialize->xml_serialize(/* "最大灵敏角" */ g_sLangTxt_Gradient_MaxAngle.GetString(), "MaxAngle", "", "number", pResults->m_oMaxAngle.m_fMaxAngle);
        pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);
#endif
}

void stt_xml_serialize_pnv(tmt_PowerDirectionParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{//xxxx
    pXmlSierialize->xml_serialize("边界1定值","AngleSet1","°","number",pParas->m_fStart);
    pXmlSierialize->xml_serialize("边界2定值","AngleSet2","°","number",pParas->m_fStop);
    pXmlSierialize->xml_serialize("测试精度","Step","°","number",pParas->m_fStep);
    pXmlSierialize->xml_serialize("整定动作时间","TSetting","s","number",pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("角度测试偏移","AngleOffset","°","number",pParas->m_fAngleOffset);
    pXmlSierialize->xml_serialize("测试相别","VarIndex","","ArcRampIndex",pParas->m_nVarIndex);

    pXmlSierialize->xml_serialize("相位以电压为参考","AngleRef","","BOOL",pParas->m_nAngleMode);

    pXmlSierialize->xml_serialize("试验前复归时间","RampResetTime","s","number",pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("故障前复归时间","FaultResetTime","s","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("每步时间裕度","StepTimeAdded","s","number",pParas->m_fMarginTime);

    pXmlSierialize->xml_serialize("复归Ua","Ua0","V","number",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Ub","Ub0","V","number",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Uc","Uc0","V","number",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Ia","Ia0","A","number",pParas->m_uiCUR[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Ib","Ib0","A","number",pParas->m_uiCUR[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("复归Ic","Ic0","A","number",pParas->m_uiCUR[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua","Ua","V","number",pParas->m_uiVOL[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub","Ub","V","number",pParas->m_uiVOL[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc","Uc","V","number",pParas->m_uiVOL[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia","Ia","A","number",pParas->m_uiCUR[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib","Ib","A","number",pParas->m_uiCUR[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic","Ic","A","number",pParas->m_uiCUR[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua相位","UaPh","°","number",pParas->m_uiVOL[2][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub相位","UbPh","°","number",pParas->m_uiVOL[2][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc相位","UcPh","°","number",pParas->m_uiVOL[2][2].Harm[1].fAngle);

    pXmlSierialize->xml_serialize("开入A选择", "_BinSelectA", "", "BOOL", pParas->m_binIn[0].nSelect);
    pXmlSierialize->xml_serialize("开入B选择", "_BinSelectB", "", "BOOL", pParas->m_binIn[1].nSelect);
    pXmlSierialize->xml_serialize("开入C选择", "_BinSelectC", "", "BOOL", pParas->m_binIn[2].nSelect);
    pXmlSierialize->xml_serialize("开入R选择", "_BinSelectR", "", "BOOL", pParas->m_binIn[3].nSelect);
    pXmlSierialize->xml_serialize("开入a选择", "_BinSelecta", "", "BOOL", pParas->m_binIn[4].nSelect);
    pXmlSierialize->xml_serialize("开入b选择", "_BinSelectb", "", "BOOL", pParas->m_binIn[5].nSelect);
    pXmlSierialize->xml_serialize("开入c选择", "_BinSelectc", "", "BOOL", pParas->m_binIn[6].nSelect);
    pXmlSierialize->xml_serialize("开入r选择", "_BinSelectr", "", "BOOL", pParas->m_binIn[7].nSelect);
    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

    pXmlSierialize->xml_serialize("开出1","_Bout1","","DOutputState",pParas->m_binOut[0][0].nState);
    pXmlSierialize->xml_serialize("开出2","_Bout2","","DOutputState",pParas->m_binOut[0][1].nState);
    pXmlSierialize->xml_serialize("开出3","_Bout3","","DOutputState",pParas->m_binOut[0][2].nState);
    pXmlSierialize->xml_serialize("开出4","_Bout4","","DOutputState",pParas->m_binOut[0][3].nState);

    pXmlSierialize->xml_serialize("开出1故障状态","_BoutF1","","DOutputState",pParas->m_binOut[1][0].nState);
    pXmlSierialize->xml_serialize("开出2故障状态","_BoutF2","","DOutputState",pParas->m_binOut[1][1].nState);
    pXmlSierialize->xml_serialize("开出3故障状态","_BoutF3","","DOutputState",pParas->m_binOut[1][2].nState);
    pXmlSierialize->xml_serialize("开出4故障状态","_BoutF4","","DOutputState",pParas->m_binOut[1][3].nState);
    pXmlSierialize->xml_serialize("开出保持时间","_BoutHoldTime","s","number",pParas->m_binOut[1][0].fHoldTime);
}

void stt_xml_serialize_pnv_power_dir(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("动作边界1","TripAngle1","","number",pResults->m_oMaxAngle.m_fAngleF);
    pXmlSierialize->xml_serialize("动作边界2","TripAngle2","","number",pResults->m_oMaxAngle.m_fAngleS);
    pXmlSierialize->xml_serialize("灵敏角","LmAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);
    pXmlSierialize->xml_serialize("动作描述","ActDsc","","number",pResults->m_nAct);
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_PowerDirectionTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize_ex(&(pTests->m_oTmtParas),  pXmlParas);	//文件的读写
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize_power_dir(&pTests->m_oTmtResults,  pXmlResults);
	}

	return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_PnvPowerDirectionTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        stt_xml_serialize(&(pTests->m_oTmtParas),  pXmlParas);	//文件的读写
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        stt_xml_serialize_pnv_power_dir(&pTests->m_oTmtResults,  pXmlResults);
    }

    return pXmlParas;
}
