#include "stdafx.h"
#include "tmt_sequence_manu_test.h"
#include "../tmt_system_config.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"
#endif

void stt_init_paras(tmt_SequenceManuParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_SequenceManuParas));
    pParas->init();
}

void stt_init_results(tmt_SequenceManuResult *pResults)
{
    memset(&pResults, 0, sizeof(tmt_SequenceManuResult));
    pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_SequenceManuParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize(pParas, pXmlSierialize, MAX_VOLTAGE_COUNT / 3, MAX_CURRENT_COUNT / 3);
}

void stt_xml_serialize(tmt_SequenceManuParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVoGroupNum, long nCurGroupNum)
{
    //新版序列化,U1~U18,i1~i18
    CString strID;

    if(nVoGroupNum > (MAX_VOLTAGE_COUNT / 3))
    {
        nVoGroupNum = MAX_VOLTAGE_COUNT / 3;
    }

    for(int nIndex = 0; nIndex < nVoGroupNum; nIndex++)
    {
        strID.Format(_T("U%d_1"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pParas->m_uiVOL[nIndex * 3].Harm[1].fAmp);
        strID.Format(_T("U%d_1Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiVOL[nIndex * 3].Harm[1].fAngle);
        strID.Format(_T("U%d_2"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pParas->m_uiVOL[nIndex * 3 + 1].Harm[1].fAmp);
        strID.Format(_T("U%d_2Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiVOL[nIndex * 3 + 1].Harm[1].fAngle);
        strID.Format(_T("U%d_0"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", pParas->m_uiVOL[nIndex * 3 + 2].Harm[1].fAmp);
        strID.Format(_T("U%d_0Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiVOL[nIndex * 3 + 2].Harm[1].fAngle);
    }

    if(nCurGroupNum > (MAX_CURRENT_COUNT / 3))
    {
        nCurGroupNum = MAX_CURRENT_COUNT / 3;
    }

    for(int nIndex = 0; nIndex < nCurGroupNum; nIndex++)
    {
        strID.Format(_T("I%d_1"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pParas->m_uiCUR[nIndex * 3].Harm[1].fAmp);
        strID.Format(_T("I%d_1Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiCUR[nIndex * 3].Harm[1].fAngle);
        strID.Format(_T("I%d_2"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pParas->m_uiCUR[nIndex * 3 + 1].Harm[1].fAmp);
        strID.Format(_T("I%d_2Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiCUR[nIndex * 3 + 1].Harm[1].fAngle);
        strID.Format(_T("I%d_0"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", pParas->m_uiCUR[nIndex * 3 + 2].Harm[1].fAmp);
        strID.Format(_T("I%d_0Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", pParas->m_uiCUR[nIndex * 3 + 2].Harm[1].fAngle);
    }
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("频率", "Freq", " ", "number", pParas->m_fFreq);
    pXmlSierialize->xml_serialize("是否开入停止", "bBinStop", "", "BOOL", pParas->m_bBinStop);
    pXmlSierialize->xml_serialize("是否老化试验", "bAging", "", "BOOL", pParas->m_bAging);
    pXmlSierialize->xml_serialize("递变通道选择", "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize("递变类型选择", "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
    pXmlSierialize->xml_serialize("变化模式", "Mode", "", "UIVariateMode", pParas->m_oSequenceGradient.nMode);
    pXmlSierialize->xml_serialize("变化始值", "Start", "", "number", pParas->m_oSequenceGradient.fStart);
    pXmlSierialize->xml_serialize("变化终值", "End", "", "number", pParas->m_oSequenceGradient.fEnd);
    pXmlSierialize->xml_serialize("变化步长", "Step", "", "number", pParas->m_oSequenceGradient.fStep);
    pXmlSierialize->xml_serialize("每步时间", "StepTime", "", "number", pParas->m_oSequenceGradient.fStepTime);
    pXmlSierialize->xml_serialize("触发延时", "TrigDelay", "", "number", pParas->m_oSequenceGradient.fTrigDelay);
    pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);
    pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize("是否锁定", "_bLock", "", "BOOL", pParas->m_bLockChanged);
    pXmlSierialize->xml_serialize("是否自动递变", "_bAuto", "", "BOOL", pParas->m_bAuto);
#else
    pXmlSierialize->xml_serialize(/* "频率" */g_sLangTxt_Native_Freq.GetString(), "Freq", " ", "number", pParas->m_fFreq);
    pXmlSierialize->xml_serialize(/* "是否开入停止" */g_sLangTxt_Native_YNInputStop.GetString(), "bBinStop", "", "BOOL", pParas->m_bBinStop);
    pXmlSierialize->xml_serialize(/* "是否老化试验" */g_sLangTxt_Native_YNaging_test.GetString(), "bAging", "", "BOOL", pParas->m_bAging);
    pXmlSierialize->xml_serialize(/* "递变通道选择" */g_sLangTxt_Native_varchannel_select.GetString(), "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize(/* "递变类型选择" */g_sLangTxt_Native_vartype_select.GetString(), "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
    pXmlSierialize->xml_serialize(/* "变化模式" */g_sLangTxt_Native_change_mode.GetString(), "Mode", "", "UIVariateMode", pParas->m_oSequenceGradient.nMode);
    pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "Start", "", "number", pParas->m_oSequenceGradient.fStart);
    pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "End", "", "number", pParas->m_oSequenceGradient.fEnd);
    pXmlSierialize->xml_serialize(/* "变化步长" */g_sLangTxt_Gradient_Step.GetString(), "Step", "", "number", pParas->m_oSequenceGradient.fStep);
    pXmlSierialize->xml_serialize(/* "每步时间" */g_sLangTxt_Native_step_time.GetString(), "StepTime", "", "number", pParas->m_oSequenceGradient.fStepTime);
    pXmlSierialize->xml_serialize(/* "触发延时" */g_sLangTxt_Native_trigger_delay.GetString(), "TrigDelay", "", "number", pParas->m_oSequenceGradient.fTrigDelay);
    pXmlSierialize->xml_serialize(/* "开入逻辑" */g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);
    pXmlSierialize->xml_serialize(/* "测试通道类型" */g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize(/* "是否锁定" */g_sLangTxt_Native_YN_locked.GetString(), "_bLock", "", "BOOL", pParas->m_bLockChanged);
    pXmlSierialize->xml_serialize(/* "是否自动递变" */g_sLangTxt_Native_YN_autoevo.GetString(), "_bAuto", "", "BOOL", pParas->m_bAuto);
#endif

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }

#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("最长输出时间(s)", "OutputTime", " ", "number", pParas->m_fOutPutTime);
    pXmlSierialize->xml_serialize("动作整定时间", "TSet", "s", "float", pParas->m_fTimeSet);
    pXmlSierialize->xml_serialize("电压整定动作值", "USet", "V", "float", pParas->m_fUSet);
    pXmlSierialize->xml_serialize("电流整定动作值", "ISet", "A", "float", pParas->m_fISet);
    pXmlSierialize->xml_serialize("相位整定动作值", "AngleSet", "°", "float", pParas->m_fAngleSet);
    pXmlSierialize->xml_serialize("频率整定动作值", "HzSet", "Hz", "float", pParas->m_fHzSet);
    pXmlSierialize->xml_serialize("返回系数整定值", "RetCoefSet", "", "float", pParas->m_fRetCoefSet);
    pXmlSierialize->xml_serialize("动作时间值绝对误差", "Ttrip_AbsErr", "", "float", pParas->m_fTimeValue_AbsErr);
    pXmlSierialize->xml_serialize("动作时间值相对误差", "Ttrip_RelErr", "", "float", pParas->m_fTimeValue_RelErr);
    pXmlSierialize->xml_serialize("动作时间误差判断逻辑", "TimeValue_ErrorLogic", "", "number", pParas->m_nTimeValue_ErrorLogic);
    pXmlSierialize->xml_serialize("电压动作值绝对误差", "UActVal_AbsErr", "", "float", pParas->m_fUActVal_AbsErr);
    pXmlSierialize->xml_serialize("电压动作值相对误差", "UActVal_RelErr", "", "float", pParas->m_fUActVal_RelErr);
    pXmlSierialize->xml_serialize("电压动作值误差判断逻辑", "UActVal_ErrorLogic", "", "number", pParas->m_nUActVal_ErrorLogic);
    pXmlSierialize->xml_serialize("电流动作值绝对误差", "IActVal_AbsErr", "", "float", pParas->m_fIActVal_AbsErr);
    pXmlSierialize->xml_serialize("电流动作值相对误差", "IActVal_RelErr", "", "float", pParas->m_fIActVal_RelErr);
    pXmlSierialize->xml_serialize("电流动作值误差判断逻辑", "IActVal_ErrorLogic", "", "number", pParas->m_nIActVal_ErrorLogic);
    pXmlSierialize->xml_serialize("相位动作值绝对误差", "AngleActVal_AbsErr", "", "float", pParas->m_fAngleActVal_AbsErr);
    pXmlSierialize->xml_serialize("相位动作值相对误差", "AngleActVal_RelErr", "", "float", pParas->m_fAngleActVal_RelErr);
    pXmlSierialize->xml_serialize("相位动作值误差判断逻辑", "AngleActVal_ErrorLogic", "", "number", pParas->m_nAngleActVal_ErrorLogic);
    //pXmlSierialize->xml_serialize("频率动作值绝对误差","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);
    //pXmlSierialize->xml_serialize("频率动作值相对误差","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);
    //pXmlSierialize->xml_serialize("频率动作值误差判断逻辑","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);
    pXmlSierialize->xml_serialize("返回系数绝对误差", "RetCoef_AbsErr", "", "float", pParas->m_fRetCoef_AbsErr);
    pXmlSierialize->xml_serialize("返回系数相对误差", "RetCoef_RelErr", "", "float", pParas->m_fRetCoef_RelErr);
    pXmlSierialize->xml_serialize("返回系数误差判断逻辑", "RetCoef_ErrorLogic", "", "number", pParas->m_nRetCoef_ErrorLogic);
#else
    pXmlSierialize->xml_serialize(/* "最长输出时间(s)" */g_sLangTxt_Native_max_outputtime.GetString(), "OutputTime", " ", "number", pParas->m_fOutPutTime);
    pXmlSierialize->xml_serialize(/* "动作整定时间" */g_sLangTxt_Native_acttuning_time.GetString(), "TSet", "s", "float", pParas->m_fTimeSet);
    pXmlSierialize->xml_serialize(/* "电压整定动作值" */g_sLangTxt_Native_VolSetActValue.GetString(), "USet", "V", "float", pParas->m_fUSet);
    pXmlSierialize->xml_serialize(/* "电流整定动作值" */g_sLangTxt_Native_CurSetActValue.GetString(), "ISet", "A", "float", pParas->m_fISet);
    pXmlSierialize->xml_serialize(/* "相位整定动作值" */g_sLangTxt_Native_PhSetActValue.GetString(), "AngleSet", "°", "float", pParas->m_fAngleSet);
    pXmlSierialize->xml_serialize(/* "频率整定动作值" */g_sLangTxt_Native_FreqSetActValue.GetString(), "HzSet", "Hz", "float", pParas->m_fHzSet);
    pXmlSierialize->xml_serialize(/* "返回系数整定值" */g_sLangTxt_Native_FeedbackCoefSettingVal.GetString(), "RetCoefSet", "", "float", pParas->m_fRetCoefSet);
    pXmlSierialize->xml_serialize(/* "动作时间值绝对误差" */g_sLangTxt_Native_ActTimeValueAbsErr.GetString(), "Ttrip_AbsErr", "", "float", pParas->m_fTimeValue_AbsErr);
    pXmlSierialize->xml_serialize(/* "动作时间值相对误差" */g_sLangTxt_Native_ActTimeValueRelErr.GetString(), "Ttrip_RelErr", "", "float", pParas->m_fTimeValue_RelErr);
    pXmlSierialize->xml_serialize(/* "动作时间误差判断逻辑" */g_sLangTxt_Native_ActTimeValueErrLogic.GetString(), "TimeValue_ErrorLogic", "", "number", pParas->m_nTimeValue_ErrorLogic);
    pXmlSierialize->xml_serialize(/* "电压动作值绝对误差" */g_sLangTxt_Native_VActionValueAbsErr.GetString(), "UActVal_AbsErr", "", "float", pParas->m_fUActVal_AbsErr);
    pXmlSierialize->xml_serialize(/* "电压动作值相对误差" */g_sLangTxt_Native_VActionValueRelErr.GetString(), "UActVal_RelErr", "", "float", pParas->m_fUActVal_RelErr);
    pXmlSierialize->xml_serialize(/* "电压动作值误差判断逻辑" */g_sLangTxt_Native_VActionValueErrLogic.GetString(), "UActVal_ErrorLogic", "", "number", pParas->m_nUActVal_ErrorLogic);
    pXmlSierialize->xml_serialize(/* "电流动作值绝对误差" */g_sLangTxt_Native_IActionValueAbsErr.GetString(), "IActVal_AbsErr", "", "float", pParas->m_fIActVal_AbsErr);
    pXmlSierialize->xml_serialize(/* "电流动作值相对误差" */g_sLangTxt_Native_IActionValueRelErr.GetString(), "IActVal_RelErr", "", "float", pParas->m_fIActVal_RelErr);
    pXmlSierialize->xml_serialize(/* "电流动作值误差判断逻辑" */g_sLangTxt_Native_IActionValueErrLogic.GetString(), "IActVal_ErrorLogic", "", "number", pParas->m_nIActVal_ErrorLogic);
    pXmlSierialize->xml_serialize(/* "相位动作值绝对误差" */g_sLangTxt_Native_PhaseActValueAbsErr.GetString(), "AngleActVal_AbsErr", "", "float", pParas->m_fAngleActVal_AbsErr);
    pXmlSierialize->xml_serialize(/* "相位动作值相对误差" */g_sLangTxt_Native_PhaseActValueRelErr.GetString(), "AngleActVal_RelErr", "", "float", pParas->m_fAngleActVal_RelErr);
    pXmlSierialize->xml_serialize(/* "相位动作值误差判断逻辑" */g_sLangTxt_Native_PhaseActValueErrLogic.GetString(), "AngleActVal_ErrorLogic", "", "number", pParas->m_nAngleActVal_ErrorLogic);
    //pXmlSierialize->xml_serialize("频率动作值绝对误差","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);
    //pXmlSierialize->xml_serialize("频率动作值相对误差","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);
    //pXmlSierialize->xml_serialize("频率动作值误差判断逻辑","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);
    pXmlSierialize->xml_serialize(/* "返回系数绝对误差" */g_sLangTxt_Native_CoefficientAbsErr.GetString(), "RetCoef_AbsErr", "", "float", pParas->m_fRetCoef_AbsErr);
    pXmlSierialize->xml_serialize(/* "返回系数相对误差" */g_sLangTxt_Native_CoefficientRelErr.GetString(), "RetCoef_RelErr", "", "float", pParas->m_fRetCoef_RelErr);
    pXmlSierialize->xml_serialize(/* "返回系数误差判断逻辑" */g_sLangTxt_Native_CoefficientErrLogic.GetString(), "RetCoef_ErrorLogic", "", "number", pParas->m_nRetCoef_ErrorLogic);
#endif
    
}

void stt_xml_serialize_Sequence(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, tmt_channel *puiVOL, tmt_channel *puiCUR)
{
    float fFreq = 50.0;
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("频率", "Freq", " ", "number", fFreq);
#else
    pXmlSierialize->xml_serialize(/* "频率" */g_sLangTxt_Native_Freq.GetString(), "Freq", " ", "number", fFreq);
#endif
    //新版序列化,18U18I
    CString strID;

    for(int nIndex = 0; nIndex < 6; nIndex++)
    {
        strID.Format(_T("U%d_1"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", puiVOL[nIndex * 3].Harm[1].fAmp);
        strID.Format(_T("U%d_1Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", puiVOL[nIndex * 3].Harm[1].fAngle);
        puiVOL[nIndex * 3].Harm[1].fFreq = fFreq;
        strID.Format(_T("U%d_2"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", puiVOL[nIndex * 3 + 1].Harm[1].fAmp);
        strID.Format(_T("U%d_2Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", puiVOL[nIndex * 3 + 1].Harm[1].fAngle);
        puiVOL[nIndex * 3 + 1].Harm[1].fFreq = fFreq;
        strID.Format(_T("U%d_0"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "V", "number", puiVOL[nIndex * 3 + 2].Harm[1].fAmp);
        strID.Format(_T("U%d_0Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", puiVOL[nIndex * 3 + 2].Harm[1].fAngle);
        puiVOL[nIndex * 3 + 2].Harm[1].fFreq = fFreq;
        strID.Format(_T("I%d_1"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", puiCUR[nIndex * 3].Harm[1].fAmp);
        strID.Format(_T("I%d_1Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", puiCUR[nIndex * 3].Harm[1].fAngle);
        puiCUR[nIndex * 3].Harm[1].fFreq = fFreq;
        strID.Format(_T("I%d_2"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", puiCUR[nIndex * 3 + 1].Harm[1].fAmp);
        strID.Format(_T("I%d_2Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", puiCUR[nIndex * 3 + 1].Harm[1].fAngle);
        puiCUR[nIndex * 3 + 1].Harm[1].fFreq = fFreq;
        strID.Format(_T("I%d_0"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "A", "number", puiCUR[nIndex * 3 + 2].Harm[1].fAmp);
        strID.Format(_T("I%d_0Ph"), nIndex + 1);
        pXmlSierialize->xml_serialize("", strID.GetString(), "°", "number", puiCUR[nIndex * 3 + 2].Harm[1].fAngle);
        puiCUR[nIndex * 3 + 2].Harm[1].fFreq = fFreq;
    }

#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("是否开入停止", "bBinStop", "", "BOOL", pParas->m_bBinStop);
    pXmlSierialize->xml_serialize("递变通道选择", "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize("递变类型选择", "_GradientTpSelect", "", "PsuGradientType", pParas->m_nGradientTpSelect);
    pXmlSierialize->xml_serialize("变化模式", "Mode", "", "UIVariateMode", pParas->m_manuGradient.nMode);
    pXmlSierialize->xml_serialize("变化始值", "Start", "", "number", pParas->m_manuGradient.fStart);
    pXmlSierialize->xml_serialize("变化终值", "End", "", "number", pParas->m_manuGradient.fEnd);
    pXmlSierialize->xml_serialize("变化步长", "Step", "", "number", pParas->m_manuGradient.fStep);
	pXmlSierialize->xml_serialize("每步时间", "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
    pXmlSierialize->xml_serialize("触发延时", "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
    pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);
    pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize("是否锁定", "_bLock", "", "BOOL", pParas->m_bLockChanged);
    pXmlSierialize->xml_serialize("是否自动递变", "_bAuto", "", "BOOL", pParas->m_bAuto);
#else
    pXmlSierialize->xml_serialize(/* "是否开入停止" */g_sLangTxt_Native_YNInputStop.GetString(), "bBinStop", "", "BOOL", pParas->m_bBinStop);
    pXmlSierialize->xml_serialize(/* "递变通道选择" */g_sLangTxt_Native_varchannel_select.GetString(), "_GradientChSelect", "", "PsuGradientChannel", pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize(/* "变化始值" */g_sLangTxt_Gradient_Init.GetString(), "Start", "", "number", pParas->m_manuGradient.fStart);
    pXmlSierialize->xml_serialize(/* "变化终值" */g_sLangTxt_Gradient_Finish.GetString(), "End", "", "number", pParas->m_manuGradient.fEnd);
    pXmlSierialize->xml_serialize(/* "变化步长" */g_sLangTxt_Gradient_Step.GetString(), "Step", "", "number", pParas->m_manuGradient.fStep);
    pXmlSierialize->xml_serialize(/* "每步时间" */g_sLangTxt_Native_step_time.GetString(), "StepTime", "", "number", pParas->m_manuGradient.fStepTime);
    pXmlSierialize->xml_serialize(/* "触发延时" */g_sLangTxt_Native_trigger_delay.GetString(), "TrigDelay", "", "number", pParas->m_manuGradient.fTrigDelay);
    pXmlSierialize->xml_serialize(/* "开入逻辑" */g_sLangTxt_Native_InLogic.GetString(), "_AndOr", "", "InPutLogic_Psu", pParas->m_nBinLogic);
    stt_xml_serialize_binary_in(pParas->m_binIn, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
    stt_xml_serialize_Exbinary_in(pParas->m_binInEx, pXmlSierialize);
    stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);
    pXmlSierialize->xml_serialize(/* "测试通道类型" */g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
    pXmlSierialize->xml_serialize(/* "是否锁定" */g_sLangTxt_Native_YN_locked.GetString(), "_bLock", "", "BOOL", pParas->m_bLockChanged);
    pXmlSierialize->xml_serialize(/* "是否自动递变" */g_sLangTxt_Native_YN_autoevo.GetString(), "_bAuto", "", "BOOL", pParas->m_bAuto);
#endif
    

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        stt_xml_serialize(&pParas->m_oGoosePub[0], pXmlSierialize);
    }

#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("最长输出时间(s)", "OutputTime", " ", "number", pParas->m_fOutPutTime);
    pXmlSierialize->xml_serialize("动作整定时间", "TSet", "s", "float", pParas->m_fTimeSet);
    pXmlSierialize->xml_serialize("电压整定动作值", "USet", "V", "float", pParas->m_fUSet);
    pXmlSierialize->xml_serialize("电流整定动作值", "ISet", "A", "float", pParas->m_fISet);
    pXmlSierialize->xml_serialize("动作时间值绝对误差", "Ttrip_AbsErr", "", "float", pParas->m_fTimeValue_AbsErr);
    pXmlSierialize->xml_serialize("动作时间值相对误差", "Ttrip_RelErr", "", "float", pParas->m_fTimeValue_RelErr);
    pXmlSierialize->xml_serialize("动作时间误差判断逻辑", "TimeValue_ErrorLogic", "", "number", pParas->m_nTimeValue_ErrorLogic);
    pXmlSierialize->xml_serialize("电压动作值绝对误差", "UActVal_AbsErr", "", "float", pParas->m_fUActVal_AbsErr);
    pXmlSierialize->xml_serialize("电压动作值相对误差", "UActVal_RelErr", "", "float", pParas->m_fUActVal_RelErr);
    pXmlSierialize->xml_serialize("电压动作值误差判断逻辑", "UActVal_ErrorLogic", "", "number", pParas->m_nUActVal_ErrorLogic);
    pXmlSierialize->xml_serialize("电流动作值绝对误差", "IActVal_AbsErr", "", "float", pParas->m_fIActVal_AbsErr);
    pXmlSierialize->xml_serialize("电流动作值相对误差", "IActVal_RelErr", "", "float", pParas->m_fIActVal_RelErr);
    pXmlSierialize->xml_serialize("电流动作值误差判断逻辑", "IActVal_ErrorLogic", "", "number", pParas->m_nIActVal_ErrorLogic);
#else
    pXmlSierialize->xml_serialize(/* "最长输出时间(s)" */g_sLangTxt_Native_max_outputtime.GetString(), "OutputTime", " ", "number", pParas->m_fOutPutTime);
    pXmlSierialize->xml_serialize(/* "动作整定时间" */g_sLangTxt_Native_acttuning_time.GetString(), "TSet", "s", "float", pParas->m_fTimeSet);
    pXmlSierialize->xml_serialize(/* "电压整定动作值" */g_sLangTxt_Native_VolSetActValue.GetString(), "USet", "V", "float", pParas->m_fUSet);
    pXmlSierialize->xml_serialize(/* "电流整定动作值" */g_sLangTxt_Native_CurSetActValue.GetString(), "ISet", "A", "float", pParas->m_fISet);
    pXmlSierialize->xml_serialize(/* "动作时间值绝对误差" */g_sLangTxt_Native_ActTimeValueAbsErr.GetString(), "Ttrip_AbsErr", "", "float", pParas->m_fTimeValue_AbsErr);
    pXmlSierialize->xml_serialize(/* "动作时间值相对误差" */g_sLangTxt_Native_ActTimeValueRelErr.GetString(), "Ttrip_RelErr", "", "float", pParas->m_fTimeValue_RelErr);
    pXmlSierialize->xml_serialize(/* "动作时间误差判断逻辑" */g_sLangTxt_Native_ActTimeValueErrLogic.GetString(), "TimeValue_ErrorLogic", "", "number", pParas->m_nTimeValue_ErrorLogic);
    pXmlSierialize->xml_serialize(/* "电压动作值绝对误差" */g_sLangTxt_Native_VActionValueAbsErr.GetString(), "UActVal_AbsErr", "", "float", pParas->m_fUActVal_AbsErr);
    pXmlSierialize->xml_serialize(/* "电压动作值相对误差" */g_sLangTxt_Native_VActionValueRelErr.GetString(), "UActVal_RelErr", "", "float", pParas->m_fUActVal_RelErr);
    pXmlSierialize->xml_serialize(/* "电压动作值误差判断逻辑" */g_sLangTxt_Native_VActionValueErrLogic.GetString(), "UActVal_ErrorLogic", "", "number", pParas->m_nUActVal_ErrorLogic);
    pXmlSierialize->xml_serialize(/* "电流动作值绝对误差" */g_sLangTxt_Native_IActionValueAbsErr.GetString(), "IActVal_AbsErr", "", "float", pParas->m_fIActVal_AbsErr);
    pXmlSierialize->xml_serialize(/* "电流动作值相对误差" */g_sLangTxt_Native_IActionValueRelErr.GetString(), "IActVal_RelErr", "", "float", pParas->m_fIActVal_RelErr);
    pXmlSierialize->xml_serialize(/* "电流动作值误差判断逻辑" */g_sLangTxt_Native_IActionValueErrLogic.GetString(), "IActVal_ErrorLogic", "", "number", pParas->m_nIActVal_ErrorLogic);
#endif
    
}

void stt_xml_serialize_act_rcd(tmt_SequenceManuResult *pResults, CSttXmlSerializeBase *pXmlSierialize)//动作记录,最大64次,根据实际动作情况,上送总的动作信息
{
    CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

    if(pXmlActRcddata == NULL)
    {
        return;
    }

#ifdef NOT_USE_XLANGUAGE
    CString strName, strID, strTemp, strTmp2;
    CString str1 = _T("开入");
    CString str2 = _T("第");
    CString str3 = _T("次动作时间");
#else
    CString strName, strID, strTemp, strTmp2;
    CString str1 = /* _T("开入") */g_sLangTxt_Native_BinX;
    CString str2 = /* _T("第") */g_sLangTxt_Native_Number;
    CString str3 = /* _T("次动作时间") */g_sLangTxt_Native_NActionTime;
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
#ifdef NOT_USE_XLANGUAGE
        for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
            strTemp.Format(_T("扩展%d"), nIndex + 1);

            for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinExSwitchCount[nIndex])); nIndexAct++)
            {
                strTmp2.Format(_T("%d"), nIndexAct + 1);
                strName = str1 + strTemp + str2 + strTmp2 + str3;
                strID.Format("BinEx%dActCount%d", (nIndex + 1), (nIndexAct + 1));
                pXmlActRcdExdata->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_frTimeBinExAct[nIndex][nIndexAct]);
            }
        }
#else
        for(int nIndex = 0; nIndex < g_nBinExCount; nIndex++)
        {
            strTemp.Format(/* _T("扩展%d") */g_sLangTxt_Native_extend, nIndex + 1);

            for(int nIndexAct = 0; ((nIndexAct < 64) && (nIndexAct < pResults->m_nrBinExSwitchCount[nIndex])); nIndexAct++)
            {
                strTmp2.Format(_T("%d"), nIndexAct + 1);
                strName = str1 + strTemp + str2 + strTmp2 + str3;
                strID.Format("BinEx%dActCount%d", (nIndex + 1), (nIndexAct + 1));
                pXmlActRcdExdata->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_frTimeBinExAct[nIndex][nIndexAct]);
            }
        }
#endif
        
    }
}

void stt_xml_serialize(tmt_SequenceManuResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("动作标记", "TripFlag", "", "number", pResults->m_nTripFlag);
    pXmlSierialize->xml_serialize("动作时间", "TripTime", "", "number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("动作值", "ActValue", "", "number", pResults->m_fActValue);
    pXmlSierialize->xml_serialize("返回值", "ReturnValue", "", "number", pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize("返回系数", "ReturnCoef", "", "number", pResults->m_fReturnCoef);
    pXmlSierialize->xml_serialize("返回时间", "ReturnTime", "", "number", pResults->m_fReturnTime);
    CString strName, strID, strTemp;
    CString str1 = _T("开入");
    CString str2 = _T("结果状态");
#else
    pXmlSierialize->xml_serialize(/* "动作标记" */g_sLangTxt_Native_action_mark.GetString(), "TripFlag", "", "number", pResults->m_nTripFlag);
    pXmlSierialize->xml_serialize(/* "动作时间" */g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "", "number", pResults->m_fTripTime);
    pXmlSierialize->xml_serialize(/* "动作值" */g_sLangTxt_State_ActionValue.GetString(), "ActValue", "", "number", pResults->m_fActValue);
    pXmlSierialize->xml_serialize(/* "返回值" */g_sLangTxt_Native_ReturnValue.GetString(), "ReturnValue", "", "number", pResults->m_fReturnValue);
    pXmlSierialize->xml_serialize(/* "返回系数" */g_sLangTxt_Gradient_ReCoefficient.GetString(), "ReturnCoef", "", "number", pResults->m_fReturnCoef);
    pXmlSierialize->xml_serialize(/* "返回时间" */g_sLangTxt_Native_ReturnTime.GetString(), "ReturnTime", "", "number", pResults->m_fReturnTime);
    CString strName, strID, strTemp;
    CString str1 = /* _T("开入") */g_sLangTxt_Native_BinX;
    CString str2 = /* _T("结果状态") */g_sLangTxt_Native_result_status;
#endif

    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("StateBin%d", (nIndex + 1));
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_nrBinSwitchCount[nIndex]);
    }

#ifdef NOT_USE_XLANGUAGE
    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlStateBinEx = pXmlSierialize->xml_serialize("StateBinEx", "StateBinEx", "StateBinEx", stt_ParaGroupKey());

        if(pXmlStateBinEx != NULL)
        {
            for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {
                strTemp.Format(_T("扩展%d"), nIndex + 1);
                strName = str1 + strTemp + str2;
                strID.Format("StateBinEx%d", (nIndex + 1));
                pXmlStateBinEx->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_nrBinExSwitchCount[nIndex]);
            }
        }
    }
#else
    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlStateBinEx = pXmlSierialize->xml_serialize("StateBinEx", "StateBinEx", "StateBinEx", stt_ParaGroupKey());

        if(pXmlStateBinEx != NULL)
        {
            for(int nIndex = 0; nIndex < g_nBinExCount; nIndex++)
            {
                strTemp.Format(/* _T("扩展%d") */g_sLangTxt_Native_extend, nIndex + 1);
                strName = str1 + strTemp + str2;
                strID.Format("StateBinEx%d", (nIndex + 1));
                pXmlStateBinEx->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResults->m_nrBinExSwitchCount[nIndex]);
            }
        }
    }
#endif

    stt_xml_serialize_act_rcd(pResults, pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_SequenceManuTest *pParas, CSttXmlSerializeBase *pXmlSierialize,long nVolGroupNum,long nCurGroupNum)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());
	
	if (pXmlParas != NULL)
	{
		stt_xml_serialize(&pParas->m_oSequenceManuParas, pXmlParas, nVolGroupNum, nCurGroupNum);
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pParas->m_oSequenceManuResult, pXmlResults);
	}

	return pXmlParas;
}


#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_SequenceManuTest()
{
    tmt_SequenceManuTest oManualTest;
    oManualTest.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oManualTest.m_oSequenceManuParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("SequenceManuTestDemo.xml");
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

