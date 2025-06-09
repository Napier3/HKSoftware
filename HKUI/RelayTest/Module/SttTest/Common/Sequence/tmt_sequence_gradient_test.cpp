#include "stdafx.h"
#include "tmt_sequence_gradient_test.h"
#include"../../../SttCmd/SttTestCmd.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///
///

#ifndef _STT_NOT_IN_TEST_SERVER_
#include "../SttSystemConfig.h"

void stt_xml_serialize_Sequence(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize,
                                tmt_channel *puiVOL1, tmt_channel *puiVOL2, tmt_channel *puiVOL3,
                                tmt_channel *puiCUR1, tmt_channel *puiCUR2, tmt_channel *puiCUR3)
{
#ifdef NOT_USE_XLANGUAGE
    CString strID, strTypeID[3];
    strTypeID[0] = _T("_Prepare");
    strTypeID[1] = _T("_PreFault");
    strTypeID[2] = _T("_Fault");
    float fFreq = g_theSystemConfig->m_fFNom;
//    pXmlSierialize->xml_serialize("频率", "Freq", " ", "number", fFreq);
    tmt_channel *pU, *pI;

    for(int nTypeIndex = 0; nTypeIndex < 3; nTypeIndex++)
    {
        switch(nTypeIndex)
        {
            case 0:
                pU = puiVOL1;
                pI = puiCUR1;
                break;

            case 1:
                pU = puiVOL2;
                pI = puiCUR2;
                break;

            case 2:
                pU = puiVOL3;
                pI = puiCUR3;
                break;
        }

        pU[0].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[0].Harm[1].fAmp);
        strID.Format(_T("U1_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pU[0].Harm[1].fAngle);
        pU[1].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[1].Harm[1].fAmp);
        strID.Format(_T("U1_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pU[1].Harm[1].fAngle);
        pU[2].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_0%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[2].Harm[1].fAmp);
        strID.Format(_T("U1_0Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pU[2].Harm[1].fAngle);
        pI[0].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[0].Harm[1].fAmp);
        strID.Format(_T("I1_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pI[0].Harm[1].fAngle);
        pI[1].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[1].Harm[1].fAmp);
        strID.Format(_T("I1_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pI[1].Harm[1].fAngle);
        pI[2].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_0%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[2].Harm[1].fAmp);
        strID.Format(_T("I1_0Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pI[2].Harm[1].fAngle);
    }

    pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop);
    pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("步长时间(秒)", "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize("故障时间裕度","MarginTime","s","number",pParas->m_fMarginTime);
    pXmlSierialize->xml_serialize("递变相别", "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize("递变类型", "VarType", "", "UIRampType", pParas->m_nType);
    pXmlSierialize->xml_serialize("测试前时间(秒)", "_PrepareTime", "s", "number", pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("故障前时间(秒)", "_PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0], pXmlSierialize, FALSE);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1], pXmlSierialize, TRUE);
    pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }
#else
 	CString strID, strTypeID[3];
    strTypeID[0] = _T("_Prepare");
    strTypeID[1] = _T("_PreFault");
    strTypeID[2] = _T("_Fault");
    float fFreq = 50.0;
    pXmlSierialize->xml_serialize(/* "频率" */g_sLangTxt_Native_Freq.GetString(), "Freq", " ", "number", fFreq);
    tmt_channel *pU, *pI;

    for(int nTypeIndex = 0; nTypeIndex < 3; nTypeIndex++)
    {
        switch(nTypeIndex)
        {
            case 0:
                pU = puiVOL1;
                pI = puiCUR1;
                break;

            case 1:
                pU = puiVOL2;
                pI = puiCUR2;
                break;

            case 2:
                pU = puiVOL3;
                pI = puiCUR3;
                break;
        }

        pU[0].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[0].Harm[1].fAmp);
        strID.Format(_T("U1_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pU[0].Harm[1].fAngle);
        pU[1].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[1].Harm[1].fAmp);
        strID.Format(_T("U1_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pU[1].Harm[1].fAngle);
        pU[2].Harm[1].fFreq = fFreq;
        strID.Format(_T("U1_0%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pU[2].Harm[1].fAmp);
        strID.Format(_T("U1_0Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pU[2].Harm[1].fAngle);
        pI[0].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_1%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[0].Harm[1].fAmp);
        strID.Format(_T("I1_1Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pI[0].Harm[1].fAngle);
        pI[1].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_2%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[1].Harm[1].fAmp);
        strID.Format(_T("I1_2Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pI[1].Harm[1].fAngle);
        pI[2].Harm[1].fFreq = fFreq;
        strID.Format(_T("I1_0%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pI[2].Harm[1].fAmp);
        strID.Format(_T("I1_0Ph%s"), strTypeID[nTypeIndex].GetString());
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pI[2].Harm[1].fAngle);
    }

    pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop);
    pXmlSierialize->xml_serialize(/* "测试精度" */g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize(/* "步长时间(秒)" */g_sLangTxt_State_StepTime.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize(/* "递变相别" */g_sLangTxt_Native_VariablePhaseChange.GetString(), "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize(/* "测试前时间(秒)" */g_sLangTxt_Native_PreTestTimeS.GetString(), "_PrepareTime", "s", "number", pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize(/* "故障前时间(秒)" */g_sLangTxt_Native_FaultPreTimeS.GetString(), "_PreFaultTime", "s", "number", pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize(/* "故障前电压电流相角(U-I)" */g_sLangTxt_Native_FaultPreUIPhaseAngle.GetString(), "PreAngle", "°", "number",  pParas->m_fDiffIAngle);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0], pXmlSierialize, FALSE);
    stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1], pXmlSierialize, TRUE);
    pXmlSierialize->xml_serialize(/* "开入逻辑" */g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);

    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }
#endif
   
}
#endif

void stt_xml_serializeSequenceGradientSetting(tmt_GradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压整定动作值","USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize("电流整定动作值","ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize("返回系数整定值","RetCoefSet","","float",pParas->m_fRetCoefSet);
#else
	pXmlSierialize->xml_serialize(/* "电压整定动作值" */g_sLangTxt_Native_VolSetActValue.GetString(),"USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize(/* "电流整定动作值" */g_sLangTxt_Native_CurSetActValue.GetString(),"ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize(/* "返回系数整定值" */g_sLangTxt_Native_PhSetActValue.GetString(),"RetCoefSet","","float",pParas->m_fRetCoefSet);
#endif

}

void stt_xml_serialize_sequence_base(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("递变模式(0-单机模式1-电压递变 2-电流递变 3-单机分组模式)", "SttTestMode", "", "number", pParas->m_nSttTestMode);

    pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
    pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("步长时间(秒)", "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("测试返回系数", "VaryMode", "", "number", pParas->m_nTestMode);
    pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize("递变相别", "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize("递变类型", "VarType", "", "UIRampType", pParas->m_nType);
    pXmlSierialize->xml_serialize("相位递变方向(0:逆时针 1:顺时针)", "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);
	pXmlSierialize->xml_serialize("测试前时间(秒)","_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("故障前时间(秒)","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("变化前电流幅值","_IPre","A","number",pParas->m_fEDI);
    pXmlSierialize->xml_serialize("故障前电压电流相角(U-I)", "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);
	pXmlSierialize->xml_serialize("变化前电流幅值","_IPre","A","number",pParas->m_fEDI);
    pXmlSierialize->xml_serialize("故障前电压电流相角(U-I)", "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);
    //根据变化前电流初始化故障前电流
    if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pParas->m_fG1Current=pParas->m_fEDI;
		pParas->m_fG2Current=pParas->m_fEDI;
	}

	pXmlSierialize->xml_serialize("故障态组1电压幅值","_UFaultG1","V","number",pParas->m_fG1Volt);
	pXmlSierialize->xml_serialize("故障态组1电流幅值","_IFaultG1","A","number",pParas->m_fG1Current);
	pXmlSierialize->xml_serialize("故障态两组电流角差","_DiffIAngle","°","number",pParas->m_fDiffIAngle);
	pXmlSierialize->xml_serialize("故障态频率","_FreqFault","Hz","number",pParas->m_fHz);
	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);

	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,TRUE);

	stt_xml_serializeSequenceGradientSetting(pParas,pXmlSierialize);

	pXmlSierialize->xml_serialize("电压动作值绝对误差","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("电压动作值相对误差","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("电压动作值误差判断逻辑","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("电流动作值绝对误差","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("电流动作值相对误差","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("电流动作值误差判断逻辑","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("返回系数绝对误差","RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize("返回系数相对误差","RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize("返回系数误差判断逻辑","RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
#else
	pXmlSierialize->xml_serialize(/* "递变模式(0-单机模式1-电压递变 2-电流递变 3-单机分组模式)" */g_sLangTxt_Native_VariableMode0123.GetString(), "SttTestMode", "", "number", pParas->m_nSttTestMode);

	pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize(/* "测试精度" */g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize(/* "步长时间(秒)" */g_sLangTxt_State_StepTime.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize(/* "测试返回系数" */g_sLangTxt_Native_TestReturnCoefficient.GetString(), "VaryMode", "", "number", pParas->m_nTestMode);
	pXmlSierialize->xml_serialize(/* "测试通道类型" */g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize(/* "递变相别" */g_sLangTxt_Native_VariablePhaseChange.GetString(), "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
	pXmlSierialize->xml_serialize(/* "递变类型" */g_sLangTxt_Native_VariableType.GetString(), "VarType", "", "UIRampType", pParas->m_nType);
	pXmlSierialize->xml_serialize(/* "相位递变方向(0:逆时针 1:顺时针)" */g_sLangTxt_Native_PhaseShiftDir01.GetString(), "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);
	pXmlSierialize->xml_serialize(/* "测试前时间(秒)" */g_sLangTxt_Native_PreTestTimeS.GetString(),"_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize(/* "故障前时间(秒)" */g_sLangTxt_Native_FaultPreTimeS.GetString(),"_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize(/* "变化前电流幅值" */g_sLangTxt_Native_IBeforeChange.GetString(),"_IPre","A","number",pParas->m_fEDI);
	pXmlSierialize->xml_serialize(/* "故障前电压电流相角(U-I)" */g_sLangTxt_Native_FaultPreUIPhaseAngle.GetString(), "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);
	pXmlSierialize->xml_serialize(/* "变化前电流幅值" */g_sLangTxt_Native_IBeforeChange.GetString(),"_IPre","A","number",pParas->m_fEDI);
	pXmlSierialize->xml_serialize(/* "故障前电压电流相角(U-I)" */g_sLangTxt_Native_FaultPreUIPhaseAngle.GetString(), "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);
	//根据变化前电流初始化故障前电流
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pParas->m_fG1Current=pParas->m_fEDI;
		pParas->m_fG2Current=pParas->m_fEDI;
	}

	pXmlSierialize->xml_serialize(/* "故障态组1电压幅值" */g_sLangTxt_Native_FaultGroup1VAmp.GetString(),"_UFaultG1","V","number",pParas->m_fG1Volt);
	pXmlSierialize->xml_serialize(/* "故障态组1电流幅值" */g_sLangTxt_Native_FaultGroup1IAmp.GetString(),"_IFaultG1","A","number",pParas->m_fG1Current);
	pXmlSierialize->xml_serialize(/* "故障态两组电流角差" */g_sLangTxt_Native_FaultGroupIPhaseDiff.GetString(),"_DiffIAngle","°","number",pParas->m_fDiffIAngle);
	pXmlSierialize->xml_serialize(/* "故障态频率" */g_sLangTxt_Native_FaultGroupFreq.GetString(),"_FreqFault","Hz","number",pParas->m_fHz);
	pXmlSierialize->xml_serialize(/* "开入逻辑" */g_sLangTxt_Native_InLogic.GetString(),"_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,TRUE);

	stt_xml_serializeSequenceGradientSetting(pParas,pXmlSierialize);

	pXmlSierialize->xml_serialize(/* "电压动作值绝对误差" */g_sLangTxt_Native_VActionValueAbsErr.GetString(),"UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize(/* "电压动作值相对误差" */g_sLangTxt_Native_VActionValueRelErr.GetString(),"UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize(/* "电压动作值误差判断逻辑" */g_sLangTxt_Native_VActionValueErrLogic.GetString(),"UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/* "电流动作值绝对误差" */g_sLangTxt_Native_IActionValueAbsErr.GetString(),"IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize(/* "电流动作值相对误差" */g_sLangTxt_Native_IActionValueRelErr.GetString(),"IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize(/* "电流动作值误差判断逻辑" */g_sLangTxt_Native_IActionValueErrLogic.GetString(),"IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/* "返回系数绝对误差" */g_sLangTxt_Native_CoefficientAbsErr.GetString(),"RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize(/* "返回系数相对误差" */g_sLangTxt_Native_CoefficientRelErr.GetString(),"RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize(/* "返回系数误差判断逻辑" */g_sLangTxt_Native_CoefficientErrLogic.GetString(),"RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
#endif
	
}

void stt_xml_serialize_sequence_Chs(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	CString strID,strTypeID[3];
    strTypeID[0] = _T("_Prepare");
    strTypeID[1] = _T("_PreFault");
    strTypeID[2] = _T("_Fault");

	for (int nTypeIndex = 0; nTypeIndex < 3; nTypeIndex++)
    {
        for(int nIndex = 0; nIndex < 3; nIndex++)
        {
			if (nIndex == 2)
            {
				strID.Format(_T("U1_0%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"V","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAmp);
				strID.Format(_T("U1_0Ph%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAngle);
				strID.Format(_T("U1_0Fre%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fFreq);
            }
            else
            {
				strID.Format(_T("U1_%d%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"V","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAmp);
				strID.Format(_T("U1_%dPh%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAngle);
				strID.Format(_T("U1_%dFre%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fFreq);
            }

        }

        for(int nIndex = 0; nIndex < 3; nIndex++)
        {
			if (nIndex == 2)
            {
				strID.Format(_T("I1_0%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"A","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAmp);
				strID.Format(_T("I1_0Ph%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAngle);
				strID.Format(_T("I1_0Fre%s"),strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fFreq);
            }
            else
            {
				strID.Format(_T("I1_%d%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"A","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAmp);
				strID.Format(_T("I1_%dPh%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAngle);
				strID.Format(_T("I1_%dFre%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
				pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fFreq);
            }
        }
    }
}

void stt_xml_serialize_sequence_ex(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_sequence_base(pParas, pXmlSierialize);
    stt_xml_serialize_sequence_Chs(pParas, pXmlSierialize);

	tmt_GradientParasEx* pParasEx = (tmt_GradientParasEx*)pParas;

    //判据条件
    int bVal = 0;
	if (stt_xml_serialize_is_read(pXmlSierialize))
    {
		pXmlSierialize->xml_serialize("相对误差有效","_XD","","number",bVal);
        pParasEx->sCondition.bXD = bVal;
		pXmlSierialize->xml_serialize("相对误差","_XDVal","","number",pParasEx->sCondition.fXD);
    }
	else if (stt_xml_serialize_is_register(pXmlSierialize))
    {
		if(pParasEx->sCondition.bXD){	bVal = 1;	}
		pXmlSierialize->xml_serialize("相对误差有效","_XD","","number",bVal);
		pXmlSierialize->xml_serialize("相对误差","_XDVal","","number",pParasEx->sCondition.fXD);
    }

	if (stt_xml_serialize_is_read(pXmlSierialize))
    {
		pXmlSierialize->xml_serialize("绝对误差有效","_JD","","number",bVal);
        pParasEx->sCondition.bJD = bVal;
		pXmlSierialize->xml_serialize("绝对误差","_JDVal","","number",pParasEx->sCondition.fJD);
    }
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		bVal = 0;
		if(pParasEx->sCondition.bJD){	bVal = 1;	}
		pXmlSierialize->xml_serialize("绝对误差有效","_JD","","number",bVal);
		pXmlSierialize->xml_serialize("绝对误差","_JDVal","","number",pParasEx->sCondition.fJD);
	}

	// 	if (stt_xml_serialize_is_read(pXmlSierialize))
	// 	{
	// 		pXmlSierialize->xml_serialize("返回系数有效","_Coeff","","number",bVal);
	// 		pParasEx->sCondition.bCoeff = bVal;
	// 		pXmlSierialize->xml_serialize("返回系数","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
	// 	}
	// 	else if (stt_xml_serialize_is_register(pXmlSierialize))
	// 	{
	// 		bVal = 0;
	// 		if(pParasEx->sCondition.bCoeff){	bVal = 1;	}
	// 		pXmlSierialize->xml_serialize("返回系数有效","_Coeff","","number",bVal);
	// 		pXmlSierialize->xml_serialize("返回系数","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
	// 	}

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize("判据逻辑","_LogicOrAnd","°","number",bVal);
		pParasEx->sCondition.bLogicOr = bVal;
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bLogicOr){		bVal = 1;	}
		pXmlSierialize->xml_serialize("判据逻辑","_LogicOrAnd","°","number",bVal);
	}
#else
	stt_xml_serialize_sequence_base(pParas, pXmlSierialize);
	stt_xml_serialize_sequence_Chs(pParas, pXmlSierialize);

	tmt_GradientParasEx* pParasEx = (tmt_GradientParasEx*)pParas;

	//判据条件
	int bVal = 0;
	if (stt_xml_serialize_is_read(pXmlSierialize))
        {
		pXmlSierialize->xml_serialize(/* "相对误差有效" */g_sLangTxt_Native_relativeErr.GetString(),"_XD","","number",bVal);
		pParasEx->sCondition.bXD = bVal;
		pXmlSierialize->xml_serialize(/* "相对误差" */g_sLangTxt_StateEstimate_RelError.GetString(),"_XDVal","","number",pParasEx->sCondition.fXD);
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		if(pParasEx->sCondition.bXD){	bVal = 1;	}
		pXmlSierialize->xml_serialize(/* "相对误差有效" */g_sLangTxt_Native_relativeErr.GetString(),"_XD","","number",bVal);
		pXmlSierialize->xml_serialize(/* "相对误差" */g_sLangTxt_StateEstimate_RelError.GetString(),"_XDVal","","number",pParasEx->sCondition.fXD);//g_sLangTxt_StateEstimate_RelError
        }

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pXmlSierialize->xml_serialize(/* "绝对误差有效" */g_sLangTxt_Native_relativeErr.GetString(),"_JD","","number",bVal);
		pParasEx->sCondition.bJD = bVal;
		pXmlSierialize->xml_serialize(/* "绝对误差" */g_sLangTxt_StateEstimate_RelError.GetString(),"_JDVal","","number",pParasEx->sCondition.fJD);//g_sLangTxt_StateEstimate_AbsError
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		bVal = 0;
		if(pParasEx->sCondition.bJD){	bVal = 1;	}
		pXmlSierialize->xml_serialize(/* "绝对误差有效" */g_sLangTxt_Native_relativeErr.GetString(),"_JD","","number",bVal);
		pXmlSierialize->xml_serialize(/* "绝对误差" */g_sLangTxt_StateEstimate_RelError.GetString(),"_JDVal","","number",pParasEx->sCondition.fJD);
    }

// 	if (stt_xml_serialize_is_read(pXmlSierialize))
// 	{
// 		pXmlSierialize->xml_serialize("返回系数有效","_Coeff","","number",bVal);
// 		pParasEx->sCondition.bCoeff = bVal;
// 		pXmlSierialize->xml_serialize("返回系数","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
// 	}
// 	else if (stt_xml_serialize_is_register(pXmlSierialize))
// 	{
// 		bVal = 0;
// 		if(pParasEx->sCondition.bCoeff){	bVal = 1;	}
// 		pXmlSierialize->xml_serialize("返回系数有效","_Coeff","","number",bVal);
// 		pXmlSierialize->xml_serialize("返回系数","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
// 	}

	if (stt_xml_serialize_is_read(pXmlSierialize))
    {
		pXmlSierialize->xml_serialize(/* "判据逻辑" */g_sLangTxt_Native_criteria_logic.GetString(),"_LogicOrAnd","°","number",bVal);
        pParasEx->sCondition.bLogicOr = bVal;
    }
	else if (stt_xml_serialize_is_register(pXmlSierialize))
    {
        bVal = 0;
		if(pParasEx->sCondition.bLogicOr){		bVal = 1;	}
		pXmlSierialize->xml_serialize(/* "判据逻辑" */g_sLangTxt_Native_criteria_logic.GetString(),"_LogicOrAnd","°","number",bVal);
	}
#endif
	
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_sequence_gradient_test_ex *pParas, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_sequence_ex(&pParas->m_oSequenceGradientParasEx, pXmlParas);	//文件的读写
		}
		else if (pParas->m_nSelected)//测试项是否被选择
		{
			stt_xml_serialize_sequence_ex(&pParas->m_oSequenceGradientParasEx, pXmlParas);	//测试参数下发
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_sequence_serialize(&pParas->m_oSequenceResultParas, pXmlResults);
		}
		else if (pParas->m_nSelected)
        {
			stt_xml_sequence_serialize(&pParas->m_oSequenceResultParas, pXmlResults);
		}
	}

	return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_SequenceGradientPnvTest *pParas, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_sequence_pnv_serialize(&pParas->m_oSequenceGradientParas, pXmlParas);	//文件的读写
        }
        else if (pParas->m_nSelected)//测试项是否被选择
        {
            stt_xml_sequence_pnv_serialize(&pParas->m_oSequenceGradientParas, pXmlParas);	//测试参数下发
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_sequence_pnv_serialize(&pParas->m_oSequenceResultParas, pXmlResults);
        }
        else if (pParas->m_nSelected)
        {
            stt_xml_sequence_pnv_serialize(&pParas->m_oSequenceResultParas, pXmlResults);
        }
    }

    return pXmlParas;
}

void stt_xml_sequence_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_sequence_base(pParas, pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		if(pParas->m_nSttTestMode == GradientTest_Base_1)
		{
			stt_xml_serialize_sequence_Chs(pParas, pXmlSierialize);
		}
		else
		{
			CString strID;
			for(int nIndex=0;nIndex<3;nIndex++)
			{
				if (nIndex == 2)
				{
					strID.Format(_T("U1_0"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"V","number",pParas->m_uiVOL[2][nIndex].Harm[1].fAmp);
					strID.Format(_T("U1_0Ph"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiVOL[2][nIndex].Harm[1].fAngle);
					strID.Format(_T("U1_0Fre"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiVOL[2][nIndex].Harm[1].fFreq);
				}
				else
				{
					strID.Format(_T("U1_%d"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"V","number",pParas->m_uiVOL[2][nIndex].Harm[1].fAmp);
					strID.Format(_T("U1_%dPh"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiVOL[2][nIndex].Harm[1].fAngle);
					strID.Format(_T("U1_%dFre"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiVOL[2][nIndex].Harm[1].fFreq);
				}
        }

			for(int nIndex=0;nIndex<3;nIndex++)
			{
				if (nIndex == 2)
				{
					strID.Format(_T("I1_0"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"A","number",pParas->m_uiCUR[2][nIndex].Harm[1].fAmp);
					strID.Format(_T("I1_0Ph"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiCUR[2][nIndex].Harm[1].fAngle);
					strID.Format(_T("I1_0Fre"));
					pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiCUR[2][nIndex].Harm[1].fFreq);
				}
				else
				{
					strID.Format(_T("I1_%d"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"A","number",pParas->m_uiCUR[2][nIndex].Harm[1].fAmp);
					strID.Format(_T("I1_%dPh"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiCUR[2][nIndex].Harm[1].fAngle);
					strID.Format(_T("I1_%dFre"),nIndex+1);
					pXmlSierialize->xml_serialize("",strID.GetString(),"Hz","number",pParas->m_uiCUR[2][nIndex].Harm[1].fFreq);
				}
			}
		}
	}
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		stt_xml_serialize(&pParas->m_oGoosePub[0],pXmlSierialize);
    }
}

void stt_xml_sequence_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("动作值", "TripValue", "A/V", "number", pResults->m_fTripValue);
    pXmlSierialize->xml_serialize("动作时间", "TripTime", "s", "number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("电压动作值误差", "TripUErrVal", "", "number", pResults->m_fTripUErrVal);
    pXmlSierialize->xml_serialize("电流动作值误差", "TripIErrVal", "", "number", pResults->m_fTripIErrVal);
    pXmlSierialize->xml_serialize("动作描述", "ActDsec", "", "number", pResults->m_nAct);
    pXmlSierialize->xml_serialize("开入1动作值", "TripValueA", "A/V", "number", pResults->m_fTripValueChl[0]);
    pXmlSierialize->xml_serialize("开入2动作值", "TripValueB", "A/V", "number", pResults->m_fTripValueChl[1]);
    pXmlSierialize->xml_serialize("开入3动作值", "TripValueC", "A/V", "number", pResults->m_fTripValueChl[2]);
    pXmlSierialize->xml_serialize("开入4动作值", "TripValueD", "A/V", "number", pResults->m_fTripValueChl[3]);
    pXmlSierialize->xml_serialize("开入5动作值", "TripValueE", "A/V", "number", pResults->m_fTripValueChl[4]);
    pXmlSierialize->xml_serialize("开入6动作值", "TripValueF", "A/V", "number", pResults->m_fTripValueChl[5]);
    pXmlSierialize->xml_serialize("开入7动作值", "TripValueG", "A/V", "number", pResults->m_fTripValueChl[6]);
    pXmlSierialize->xml_serialize("开入8动作值", "TripValueH", "A/V", "number", pResults->m_fTripValueChl[7]);

    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlTripValueEx = pXmlSierialize->xml_serialize("TripValueEx", "TripValueEx", "TripValueEx", stt_ParaGroupKey());

        if(pXmlTripValueEx != NULL)
        {
            CString strName, strID, strTemp;
            CString str1 = _T("开入");
            CString str1Ex = _T("开入扩展");
            CString str2 = _T("动作值");

            for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {
                strTemp.Format(_T("%d"), nIndex + 1);
                strName = str1Ex + strTemp + str2;

                strID.Format("TripValueEx%d", (nIndex + 1));
                pXmlTripValueEx->xml_serialize(strName.GetString(), strID.GetString(), "", "A/V", pResults->m_fTripValueExChl[nIndex]);
            }
        }
    }
#else
	pXmlSierialize->xml_serialize(/* "动作值" */g_sLangTxt_State_ActionValue.GetString(), "TripValue", "A/V", "number", pResults->m_fTripValue);//g_sLangTxt_State_ActionValue
    pXmlSierialize->xml_serialize(/* "动作时间" */g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);//g_sLangTxt_Gradient_ActionTime
    pXmlSierialize->xml_serialize(/* "电压动作值误差" */g_sLangTxt_Native_VActionValueErr.GetString(), "TripUErrVal", "", "number", pResults->m_fTripUErrVal);
    pXmlSierialize->xml_serialize(/* "电流动作值误差" */g_sLangTxt_Native_IActionValueErr.GetString(), "TripIErrVal", "", "number", pResults->m_fTripIErrVal);
    pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(), "ActDsec", "", "number", pResults->m_nAct);//g_sLangTxt_Native_ActionDesc
    pXmlSierialize->xml_serialize(/* "开入1动作值" */g_sLangTxt_Native_input1_ActionVal.GetString(), "TripValueA", "A/V", "number", pResults->m_fTripValueChl[0]);
    pXmlSierialize->xml_serialize(/* "开入2动作值" */g_sLangTxt_Native_input2_ActionVal.GetString(), "TripValueB", "A/V", "number", pResults->m_fTripValueChl[1]);
    pXmlSierialize->xml_serialize(/* "开入3动作值" */g_sLangTxt_Native_input3_ActionVal.GetString(), "TripValueC", "A/V", "number", pResults->m_fTripValueChl[2]);
    pXmlSierialize->xml_serialize(/* "开入4动作值" */g_sLangTxt_Native_input4_ActionVal.GetString(), "TripValueD", "A/V", "number", pResults->m_fTripValueChl[3]);
    pXmlSierialize->xml_serialize(/* "开入5动作值" */g_sLangTxt_Native_input5_ActionVal.GetString(), "TripValueE", "A/V", "number", pResults->m_fTripValueChl[4]);
    pXmlSierialize->xml_serialize(/* "开入6动作值" */g_sLangTxt_Native_input6_ActionVal.GetString(), "TripValueF", "A/V", "number", pResults->m_fTripValueChl[5]);
    pXmlSierialize->xml_serialize(/* "开入7动作值" */g_sLangTxt_Native_input7_ActionVal.GetString(), "TripValueG", "A/V", "number", pResults->m_fTripValueChl[6]);
    pXmlSierialize->xml_serialize(/* "开入8动作值" */g_sLangTxt_Native_input8_ActionVal.GetString(), "TripValueH", "A/V", "number", pResults->m_fTripValueChl[7]);

    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlTripValueEx = pXmlSierialize->xml_serialize("TripValueEx", "TripValueEx", "TripValueEx", stt_ParaGroupKey());

        if(pXmlTripValueEx != NULL)
        {
            CString strName, strID, strTemp;
            CString str1 = /* _T("开入") */g_sLangTxt_Native_BinX;
            CString str1Ex = /* _T("开入扩展") */g_sLangTxt_Native_InputExpand;
            CString str2 = /* _T("动作值") */g_sLangTxt_State_ActionValue;

            for(int nIndex = 0; nIndex < g_nBinExCount; nIndex++)
            {
                strTemp.Format(_T("%d"), nIndex + 1);
                strName = str1Ex + strTemp + str2;

                strID.Format("TripValueEx%d", (nIndex + 1));
                pXmlTripValueEx->xml_serialize(strName.GetString(), strID.GetString(), "", "A/V", pResults->m_fTripValueExChl[nIndex]);
            }
        }
    }
#endif
}

void stt_xml_sequence_pnv_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
    pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("整定动作时间", "TSetting", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("测试返回系数", "VaryMode", "", "number", pParas->m_nTestMode);
    pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize("递变相别", "VarPhase", "", "UIRampChannel", pParas->m_nChannel);
    pXmlSierialize->xml_serialize("递变类型", "VarType", "", "UIRampType", pParas->m_nType);
    pXmlSierialize->xml_serialize("试验前复归时间(秒)","RampResetTime","s","number",pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("故障前复归时间(秒)","FaultResetTime","s","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("每步时间裕度","StepTimeAdded","s","number",pParas->m_fMarginTime);

    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
    pXmlSierialize->xml_serialize("开入A选择", "_BinSelectA", "", "BOOL", pParas->m_binIn[0].nSelect);
    pXmlSierialize->xml_serialize("开入B选择", "_BinSelectB", "", "BOOL", pParas->m_binIn[1].nSelect);
    pXmlSierialize->xml_serialize("开入C选择", "_BinSelectC", "", "BOOL", pParas->m_binIn[2].nSelect);
    pXmlSierialize->xml_serialize("开入R选择", "_BinSelectR", "", "BOOL", pParas->m_binIn[3].nSelect);
    pXmlSierialize->xml_serialize("开入a选择", "_BinSelecta", "", "BOOL", pParas->m_binIn[4].nSelect);
    pXmlSierialize->xml_serialize("开入b选择", "_BinSelectb", "", "BOOL", pParas->m_binIn[5].nSelect);
    pXmlSierialize->xml_serialize("开入c选择", "_BinSelectc", "", "BOOL", pParas->m_binIn[6].nSelect);
    pXmlSierialize->xml_serialize("开入r选择", "_BinSelectr", "", "BOOL", pParas->m_binIn[7].nSelect);

    pXmlSierialize->xml_serialize("开出1","_Bout1","","DOutputState",pParas->m_binOut[0][0].nState);
    pXmlSierialize->xml_serialize("开出2","_Bout2","","DOutputState",pParas->m_binOut[0][1].nState);
    pXmlSierialize->xml_serialize("开出3","_Bout3","","DOutputState",pParas->m_binOut[0][2].nState);
    pXmlSierialize->xml_serialize("开出4","_Bout4","","DOutputState",pParas->m_binOut[0][3].nState);
    pXmlSierialize->xml_serialize("开出1故障状态","_BoutF1","","DOutputState",pParas->m_binOut[1][0].nState);
    pXmlSierialize->xml_serialize("开出2故障状态","_BoutF2","","DOutputState",pParas->m_binOut[1][1].nState);
    pXmlSierialize->xml_serialize("开出3故障状态","_BoutF3","","DOutputState",pParas->m_binOut[1][2].nState);
    pXmlSierialize->xml_serialize("开出4故障状态","_BoutF4","","DOutputState",pParas->m_binOut[1][3].nState);
    pXmlSierialize->xml_serialize("开出保持时间","_BoutHoldTime","","number",pParas->m_binOut[1][0].fHoldTime);

    pXmlSierialize->xml_serialize("V1初始幅值","V10_Amp","V","number",pParas->m_uiVOL[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("V1初始相位","V10_Ph","°","number",pParas->m_uiVOL[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("V2初始幅值","V20_Amp","V","number",pParas->m_uiVOL[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("V2初始相位","V20_Ph","°","number",pParas->m_uiVOL[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("V0初始幅值","V00_Amp","V","number",pParas->m_uiVOL[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("V0初始相位","V00_Ph","°","number",pParas->m_uiVOL[0][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("I1初始幅值","I10_Amp","A","number",pParas->m_uiCUR[0][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("I1初始相位","I10_Ph","°","number",pParas->m_uiCUR[0][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("I2初始幅值","I20_Amp","A","number",pParas->m_uiCUR[0][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("I2初始相位","I20_Ph","°","number",pParas->m_uiCUR[0][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("I0初始幅值","I00_Amp","A","number",pParas->m_uiCUR[0][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("I0初始相位","I00_Ph","°","number",pParas->m_uiCUR[0][0].Harm[1].fAngle);
}

void stt_xml_sequence_pnv_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("动作值", "TripValue", "A", "number", pResults->m_fTripValue);
    pXmlSierialize->xml_serialize("返回值", "ReturnValue", "V", "number", pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize("返回系数", "ReturnCoef", "", "number", pResults->m_fReturnCoef);
    pXmlSierialize->xml_serialize("动作描述", "ActDsc", "", "number", pResults->m_nAct);
}

#include "../../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_SequenceGradientTest()
{
	tmt_SequenceGradientTest oSequenceGradientTest;
	oSequenceGradientTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeRegister(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_sequence_serialize(&oSequenceGradientTest.m_oSequenceGradientParas, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("SequenceGradientTestDemo.xml");
	//  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
