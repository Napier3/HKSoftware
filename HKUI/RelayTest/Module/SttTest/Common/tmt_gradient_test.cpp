#include "stdafx.h"
#include "tmt_gradient_test.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

void stt_init_paras(tmt_GradientParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_GradientParas));
	pParas->init();
}

void stt_init_results(tmt_GradientResult *pResult)
{
	memset(&pResult, 0, sizeof(tmt_GradientResult));
	pResult->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///
///
void stt_xml_serialize_binary_out(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("常态开出1状态","_Bout01","","DOutputState",pParas->m_binOut[0][0].nState);
	pXmlSierialize->xml_serialize("常态开出2状态","_Bout02","","DOutputState",pParas->m_binOut[0][1].nState);
	pXmlSierialize->xml_serialize("常态开出3状态","_Bout03","","DOutputState",pParas->m_binOut[0][2].nState);
	pXmlSierialize->xml_serialize("常态开出4状态","_Bout04","","DOutputState",pParas->m_binOut[0][3].nState);
	pXmlSierialize->xml_serialize("常态开出5状态","_Bout05","","DOutputState",pParas->m_binOut[0][4].nState);
	pXmlSierialize->xml_serialize("常态开出6状态","_Bout06","","DOutputState",pParas->m_binOut[0][5].nState);
	pXmlSierialize->xml_serialize("常态开出7状态","_Bout07","","DOutputState",pParas->m_binOut[0][6].nState);
	pXmlSierialize->xml_serialize("常态开出8状态","_Bout08","","DOutputState",pParas->m_binOut[0][7].nState);

	pXmlSierialize->xml_serialize("故障态开出1状态","_Bout1","","DOutputState",pParas->m_binOut[1][0].nState);
	pXmlSierialize->xml_serialize("故障态开出2状态","_Bout2","","DOutputState",pParas->m_binOut[1][1].nState);
	pXmlSierialize->xml_serialize("故障态开出3状态","_Bout3","","DOutputState",pParas->m_binOut[1][2].nState);
	pXmlSierialize->xml_serialize("故障态开出4状态","_Bout4","","DOutputState",pParas->m_binOut[1][3].nState);
	pXmlSierialize->xml_serialize("故障态开出5状态","_Bout5","","DOutputState",pParas->m_binOut[1][4].nState);
	pXmlSierialize->xml_serialize("故障态开出6状态","_Bout6","","DOutputState",pParas->m_binOut[1][5].nState);
	pXmlSierialize->xml_serialize("故障态开出7状态","_Bout7","","DOutputState",pParas->m_binOut[1][6].nState);
	pXmlSierialize->xml_serialize("故障态开出8状态","_Bout8","","DOutputState",pParas->m_binOut[1][7].nState);
#else
	pXmlSierialize->xml_serialize(/*"常态开出1状态"*/g_sLangTxt_Native_NormalOpen1State.GetString(),"_Bout01","","DOutputState",pParas->m_binOut[0][0].nState);
	pXmlSierialize->xml_serialize(/*"常态开出2状态"*/g_sLangTxt_Native_NormalOpen2State.GetString(),"_Bout02","","DOutputState",pParas->m_binOut[0][1].nState);
	pXmlSierialize->xml_serialize(/*"常态开出3状态"*/g_sLangTxt_Native_NormalOpen3State.GetString(),"_Bout03","","DOutputState",pParas->m_binOut[0][2].nState);
	pXmlSierialize->xml_serialize(/*"常态开出4状态"*/g_sLangTxt_Native_NormalOpen4State.GetString(),"_Bout04","","DOutputState",pParas->m_binOut[0][3].nState);
	pXmlSierialize->xml_serialize(/*"常态开出5状态"*/g_sLangTxt_Native_NormalOpen5State.GetString(),"_Bout05","","DOutputState",pParas->m_binOut[0][4].nState);
	pXmlSierialize->xml_serialize(/*"常态开出6状态"*/g_sLangTxt_Native_NormalOpen6State.GetString(),"_Bout06","","DOutputState",pParas->m_binOut[0][5].nState);
	pXmlSierialize->xml_serialize(/*"常态开出7状态"*/g_sLangTxt_Native_NormalOpen7State.GetString(),"_Bout07","","DOutputState",pParas->m_binOut[0][6].nState);
	pXmlSierialize->xml_serialize(/*"常态开出8状态"*/g_sLangTxt_Native_NormalOpen8State.GetString(),"_Bout08","","DOutputState",pParas->m_binOut[0][7].nState);

	pXmlSierialize->xml_serialize(/*"故障态开出1状态"*/g_sLangTxt_Native_FaultOpen1State.GetString(),"_Bout1","","DOutputState",pParas->m_binOut[1][0].nState);
	pXmlSierialize->xml_serialize(/*"故障态开出2状态"*/g_sLangTxt_Native_FaultOpen2State.GetString(),"_Bout2","","DOutputState",pParas->m_binOut[1][1].nState);
	pXmlSierialize->xml_serialize(/*"故障态开出3状态"*/g_sLangTxt_Native_FaultOpen3State.GetString(),"_Bout3","","DOutputState",pParas->m_binOut[1][2].nState);
	pXmlSierialize->xml_serialize(/*"故障态开出4状态"*/g_sLangTxt_Native_FaultOpen4State.GetString(),"_Bout4","","DOutputState",pParas->m_binOut[1][3].nState);
	pXmlSierialize->xml_serialize(/*"故障态开出5状态"*/g_sLangTxt_Native_FaultOpen5State.GetString(),"_Bout5","","DOutputState",pParas->m_binOut[1][4].nState);
	pXmlSierialize->xml_serialize(/*"故障态开出6状态"*/g_sLangTxt_Native_FaultOpen6State.GetString(),"_Bout6","","DOutputState",pParas->m_binOut[1][5].nState);
	pXmlSierialize->xml_serialize(/*"故障态开出7状态"*/g_sLangTxt_Native_FaultOpen7State.GetString(),"_Bout7","","DOutputState",pParas->m_binOut[1][6].nState);
	pXmlSierialize->xml_serialize(/*"故障态开出8状态"*/g_sLangTxt_Native_FaultOpen8State.GetString(),"_Bout8","","DOutputState",pParas->m_binOut[1][7].nState);
#endif
}

void stt_xml_serializeGradientSetting(tmt_GradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压整定动作值","USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize("电流整定动作值","ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize("相位整定动作值","AngleSet","°","float",pParas->m_fAngleSet);
	pXmlSierialize->xml_serialize("频率整定动作值","HzSet","Hz","float",pParas->m_fHzSet);
	pXmlSierialize->xml_serialize("返回系数整定值","RetCoefSet","","float",pParas->m_fRetCoefSet);
	pXmlSierialize->xml_serialize("边界角1整定值","AngleFSet","°","float",pParas->m_fAngleFSet);
	pXmlSierialize->xml_serialize("边界角2整定值","AngleSSet","°","float",pParas->m_fAngleSSet);
	pXmlSierialize->xml_serialize("最大灵敏角整定值","MaxAngleSet","°","float",pParas->m_fMaxAngleSet);
#else
	pXmlSierialize->xml_serialize(/*"电压整定动作值"*/g_sLangTxt_Native_VolSetActValue.GetString(),"USet","V","float",pParas->m_fUSet);
	pXmlSierialize->xml_serialize(/*"电流整定动作值"*/g_sLangTxt_Native_CurSetActValue.GetString(),"ISet","A","float",pParas->m_fISet);
	pXmlSierialize->xml_serialize(/*"相位整定动作值"*/g_sLangTxt_Native_PhSetActValue.GetString(),"AngleSet","°","float",pParas->m_fAngleSet);
	pXmlSierialize->xml_serialize(/*"频率整定动作值"*/g_sLangTxt_Native_FreqSetActValue.GetString(),"HzSet","Hz","float",pParas->m_fHzSet);
	pXmlSierialize->xml_serialize(/*"返回系数整定值"*/g_sLangTxt_Native_FeedbackCoefSettingVal.GetString(),"RetCoefSet","","float",pParas->m_fRetCoefSet);
	pXmlSierialize->xml_serialize(/*"边界角1整定值"*/g_sLangTxt_Native_BoundaryAngle1SetVal.GetString(),"AngleFSet","°","float",pParas->m_fAngleFSet);
	pXmlSierialize->xml_serialize(/*"边界角2整定值"*/g_sLangTxt_Native_BoundaryAngle2SetVal.GetString(),"AngleSSet","°","float",pParas->m_fAngleSSet);
	pXmlSierialize->xml_serialize(/*"最大灵敏角整定值"*/g_sLangTxt_Native_MaxSensitivityAngleSetVal.GetString(),"MaxAngleSet","°","float",pParas->m_fMaxAngleSet);
#endif
}

void stt_xml_serialize_base(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("递变模式(0-单机模式1-电压递变 2-电流递变 3-单机分组模式)", "SttTestMode", "", "number", pParas->m_nSttTestMode);

	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);

	pXmlSierialize->xml_serialize("变化始值2", "BeginVal2", "", "set", pParas->m_fStart2);
	pXmlSierialize->xml_serialize("变化终值2", "EndVal2", "", "set", pParas->m_fStop2 );
	pXmlSierialize->xml_serialize("测试精度2", "Step2", "", "set", pParas->m_fStep2);

	pXmlSierialize->xml_serialize("步长时间(秒)", "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize("测试返回系数", "VaryMode", "", "number", pParas->m_nTestMode);
	pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize("递变相别", "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
	pXmlSierialize->xml_serialize("递变类型", "VarType", "", "UIRampType", pParas->m_nType);
	pXmlSierialize->xml_serialize("递变相别2", "VarIndex2", "", "UIRampChannel", pParas->m_nChannel2);
	pXmlSierialize->xml_serialize("递变类型2", "VarType2", "", "UIRampType", pParas->m_nType2);
	pXmlSierialize->xml_serialize("相位递变方向(0:逆时针 1:顺时针)", "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);

//	pXmlSierialize->xml_serialize("额定频率","_Freq","Hz","number",pParas->m_fEDFreq);
	pXmlSierialize->xml_serialize("测试前时间(秒)","_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("故障前时间(秒)","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("故障时间裕度","MarginTime","s","number",pParas->m_fMarginTime);
//	pXmlSierialize->xml_serialize("额定电压幅值","_UPre","V","number",pParas->m_fEDU);
	pXmlSierialize->xml_serialize("变化前电流幅值","_IPre","A","number",pParas->m_fEDI);
	pXmlSierialize->xml_serialize("故障前电压电流相角(U-I)", "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);

#else
	pXmlSierialize->xml_serialize(/*"递变模式(0-单机模式1-电压递变 2-电流递变 3-单机分组模式)"*/g_sLangTxt_Native_VariableMode0123.GetString(), "SttTestMode", "", "number", pParas->m_nSttTestMode);

	pXmlSierialize->xml_serialize(/*"变化始值"*/g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize(/*"变化终值"*/g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize(/*"测试精度"*/g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);


	pXmlSierialize->xml_serialize("变化始值2", "BeginVal2", "", "set", pParas->m_fStart2);
	pXmlSierialize->xml_serialize("变化终值2", "EndVal2", "", "set", pParas->m_fStop2);
	pXmlSierialize->xml_serialize("测试精度2", "Step2", "", "set", pParas->m_fStep2);

	pXmlSierialize->xml_serialize(/*"步长时间(秒)"*/g_sLangTxt_Native_StepTimeSec.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize(/*"测试返回系数"*/g_sLangTxt_Native_TestReturnCoefficient.GetString(), "VaryMode", "", "number", pParas->m_nTestMode);
	pXmlSierialize->xml_serialize(/*"测试通道类型"*/g_sLangTxt_Native_TestChannelType.GetString(), "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize(/*"递变相别"*/g_sLangTxt_Native_VariablePhaseChange.GetString(), "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
	pXmlSierialize->xml_serialize(/*"递变类型"*/g_sLangTxt_Native_VariableType.GetString(), "VarType", "", "UIRampType", pParas->m_nType);
	pXmlSierialize->xml_serialize("递变相别2", "VarIndex2", "", "UIRampChannel", pParas->m_nChannel2);
	pXmlSierialize->xml_serialize("递变类型2", "VarType2", "", "UIRampType", pParas->m_nType2);
	pXmlSierialize->xml_serialize(/*"相位递变方向(0:逆时针 1:顺时针)"*/g_sLangTxt_Native_PhaseShiftDir01.GetString(), "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);

	//	pXmlSierialize->xml_serialize("额定频率","_Freq","Hz","number",pParas->m_fEDFreq);
	pXmlSierialize->xml_serialize(/*"测试前时间(秒)"*/g_sLangTxt_Native_PreTestTimeS.GetString(),"_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize(/*"故障前时间(秒)"*/g_sLangTxt_Native_FaultPreTimeS.GetString(),"_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	//	pXmlSierialize->xml_serialize("额定电压幅值","_UPre","V","number",pParas->m_fEDU);
	pXmlSierialize->xml_serialize(/*"变化前电流幅值"*/g_sLangTxt_Native_IBeforeChange.GetString(),"_IPre","A","number",pParas->m_fEDI);
	pXmlSierialize->xml_serialize(/*"故障前电压电流相角(U-I)"*/g_sLangTxt_Native_FaultPreVoltageCurrentPhase.GetString(), "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);
#endif
	//根据变化前电流初始化故障前电流
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pParas->m_fG1Current=pParas->m_fEDI;
		pParas->m_fG2Current=pParas->m_fEDI;
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("故障态组1电压幅值","_UFaultG1","V","number",pParas->m_fG1Volt);
	pXmlSierialize->xml_serialize("故障态组2电压幅值","_UFaultG2","V","number",pParas->m_fG2Volt);
	pXmlSierialize->xml_serialize("故障态组1电流幅值","_IFaultG1","V","number",pParas->m_fG1Current);
	pXmlSierialize->xml_serialize("故障态组2电流幅值","_IFaultG2","V","number",pParas->m_fG2Current);
	pXmlSierialize->xml_serialize("故障态两组电流角差","_DiffIAngle","°","number",pParas->m_fDiffIAngle);
	pXmlSierialize->xml_serialize("故障态频率","_FreqFault","Hz","number",pParas->m_fHz);

	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"故障态组1电压幅值"*/g_sLangTxt_Native_FaultGroup1VAmp.GetString(),"_UFaultG1","V","number",pParas->m_fG1Volt);
	pXmlSierialize->xml_serialize(/*"故障态组2电压幅值"*/g_sLangTxt_Native_FSG2VoltageAmplitude.GetString(),"_UFaultG2","V","number",pParas->m_fG2Volt);
	pXmlSierialize->xml_serialize(/*"故障态组1电流幅值"*/g_sLangTxt_Native_FaultGroup1IAmp.GetString(),"_IFaultG1","V","number",pParas->m_fG1Current);
	pXmlSierialize->xml_serialize(/*"故障态组2电流幅值"*/g_sLangTxt_Native_FSG2CurrentAmplitude.GetString(),"_IFaultG2","V","number",pParas->m_fG2Current);
	pXmlSierialize->xml_serialize(/*"故障态两组电流角差"*/g_sLangTxt_Native_FaultGroupIPhaseDiff.GetString(),"_DiffIAngle","°","number",pParas->m_fDiffIAngle);
	pXmlSierialize->xml_serialize(/*"故障态频率"*/g_sLangTxt_Native_FaultGroupFreq.GetString(),"_FreqFault","Hz","number",pParas->m_fHz);

	pXmlSierialize->xml_serialize(/*"开入逻辑"*/g_sLangTxt_Native_InLogic.GetString(),"_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,TRUE);

	stt_xml_serializeGradientSetting(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("电压动作值绝对误差","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("电压动作值相对误差","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("电压动作值误差判断逻辑","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("电流动作值绝对误差","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("电流动作值相对误差","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("电流动作值误差判断逻辑","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("相位动作值绝对误差","AngleActVal_AbsErr","","float",pParas->m_fAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize("相位动作值相对误差","AngleActVal_RelErr","","float",pParas->m_fAngleActVal_RelErr);
	pXmlSierialize->xml_serialize("相位动作值误差判断逻辑","AngleActVal_ErrorLogic","","number",pParas->m_nAngleActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("频率动作值绝对误差","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
	pXmlSierialize->xml_serialize("频率动作值相对误差","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
	pXmlSierialize->xml_serialize("频率动作值误差判断逻辑","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
	pXmlSierialize->xml_serialize("返回系数绝对误差","RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize("返回系数相对误差","RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize("返回系数误差判断逻辑","RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
	pXmlSierialize->xml_serialize("最大灵敏角绝对误差","MaxAngle_AbsErr","°","float",pParas->m_fMaxAngle_AbsErr);	
	pXmlSierialize->xml_serialize("最大灵敏角相对误差","MaxAngle_RelErr","","float",pParas->m_fMaxAngle_RelErr);
	pXmlSierialize->xml_serialize("最大灵敏角误差判断逻辑","MaxAngle_ErrorLogic","","number",pParas->m_nMaxAngle_ErrorLogic);	
	pXmlSierialize->xml_serialize("边界角1绝对误差","AngleF_AbsErr","°","float",pParas->m_fAngleF_AbsErr);	
	pXmlSierialize->xml_serialize("边界角1相对误差","AngleF_RelErr","","float",pParas->m_fAngleF_RelErr);	
	pXmlSierialize->xml_serialize("边界角1误差判断逻辑","AngleF_ErrorLogic","","number",pParas->m_nAngleF_ErrorLogic);
	pXmlSierialize->xml_serialize("边界角2绝对误差","AngleS_AbsErr","°","float",pParas->m_fAngleS_AbsErr);	
	pXmlSierialize->xml_serialize("边界角2相对误差","AngleS_RelErr","","float",pParas->m_fAngleS_RelErr);
	pXmlSierialize->xml_serialize("边界角2误差判断逻辑","AngleS_ErrorLogic","","number",pParas->m_nAngleS_ErrorLogic);
#else
	pXmlSierialize->xml_serialize(/*"电压动作值绝对误差"*/g_sLangTxt_Native_VActionValueAbsErr.GetString(),"UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"电压动作值相对误差"*/g_sLangTxt_Native_VActionValueRelErr.GetString(),"UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"电压动作值误差判断逻辑"*/g_sLangTxt_Native_VActionValueErrLogic.GetString(),"UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"电流动作值绝对误差"*/g_sLangTxt_Native_IActionValueAbsErr.GetString(),"IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"电流动作值相对误差"*/g_sLangTxt_Native_IActionValueRelErr.GetString(),"IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"电流动作值误差判断逻辑"*/g_sLangTxt_Native_IActionValueErrLogic.GetString(),"IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"相位动作值绝对误差"*/g_sLangTxt_Native_PhaseActValueAbsErr.GetString(),"AngleActVal_AbsErr","","float",pParas->m_fAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize(/*"相位动作值相对误差"*/g_sLangTxt_Native_PhaseActValueRelErr.GetString(),"AngleActVal_RelErr","","float",pParas->m_fAngleActVal_RelErr);
	pXmlSierialize->xml_serialize(/*"相位动作值误差判断逻辑"*/g_sLangTxt_Native_PhaseActValueErrLogic.GetString(),"AngleActVal_ErrorLogic","","number",pParas->m_nAngleActVal_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"频率动作值绝对误差"*/g_sLangTxt_Native_FreqPickAbsErr.GetString(),"HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
	pXmlSierialize->xml_serialize(/*"频率动作值相对误差"*/g_sLangTxt_Native_FreqPickRelErr.GetString(),"HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
	pXmlSierialize->xml_serialize(/*"频率动作值误差判断逻辑"*/g_sLangTxt_Native_FreqPickErrDetectLogic.GetString(),"HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
	pXmlSierialize->xml_serialize(/*"返回系数绝对误差"*/g_sLangTxt_Native_CoefficientAbsErr.GetString(),"RetCoef_AbsErr","","float",pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize(/*"返回系数相对误差"*/g_sLangTxt_Native_CoefficientRelErr.GetString(),"RetCoef_RelErr","","float",pParas->m_fRetCoef_RelErr);	
	pXmlSierialize->xml_serialize(/*"返回系数误差判断逻辑"*/g_sLangTxt_Native_CoefficientErrLogic.GetString(),"RetCoef_ErrorLogic","","number",pParas->m_nRetCoef_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"最大灵敏角绝对误差"*/g_sLangTxt_Native_MaxSensAngAbsErr.GetString(),"MaxAngle_AbsErr","°","float",pParas->m_fMaxAngle_AbsErr);	
	pXmlSierialize->xml_serialize(/*"最大灵敏角相对误差"*/g_sLangTxt_Native_MaxSensAngRelErr.GetString(),"MaxAngle_RelErr","","float",pParas->m_fMaxAngle_RelErr);
	pXmlSierialize->xml_serialize(/*"最大灵敏角误差判断逻辑"*/g_sLangTxt_Native_MaxSensAngErrDetectLogic.GetString(),"MaxAngle_ErrorLogic","","number",pParas->m_nMaxAngle_ErrorLogic);	
	pXmlSierialize->xml_serialize(/*"边界角1绝对误差"*/g_sLangTxt_Native_BndryAng1AbsErr.GetString(),"AngleF_AbsErr","°","float",pParas->m_fAngleF_AbsErr);	
	pXmlSierialize->xml_serialize(/*"边界角1相对误差"*/g_sLangTxt_Native_BndryAng1RelErr.GetString(),"AngleF_RelErr","","float",pParas->m_fAngleF_RelErr);	
	pXmlSierialize->xml_serialize(/*"边界角1误差判断逻辑"*/g_sLangTxt_Native_BndryAng1ErrDetectLogic.GetString(),"AngleF_ErrorLogic","","number",pParas->m_nAngleF_ErrorLogic);
	pXmlSierialize->xml_serialize(/*"边界角2绝对误差"*/g_sLangTxt_Native_BndryAng2AbsErr.GetString(),"AngleS_AbsErr","°","float",pParas->m_fAngleS_AbsErr);	
	pXmlSierialize->xml_serialize(/*"边界角2相对误差"*/g_sLangTxt_Native_BndryAng2RelErr.GetString(),"AngleS_RelErr","","float",pParas->m_fAngleS_RelErr);
	pXmlSierialize->xml_serialize(/*"边界角2误差判断逻辑"*/g_sLangTxt_Native_BndryAng2ErrDetectLogic.GetString(),"AngleS_ErrorLogic","","number",pParas->m_nAngleS_ErrorLogic);
#endif
}

//STT_MACRO_ID_GradientU  STT_MACRO_ID_GradientI两个模块使用
void stt_xml_serialize_AtsRamp(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize("步长时间(秒)", "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize("故障时间裕度","MarginTime","s","number",pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("测试返回系数", "VaryMode", "", "number", pParas->m_nTestMode);
//	pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize("递变相别", "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
//	pXmlSierialize->xml_serialize("递变类型", "VarType", "", "UIRampType", pParas->m_nType);
	pXmlSierialize->xml_serialize("相位递变方向(0:逆时针 1:顺时针)", "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);

	pXmlSierialize->xml_serialize("额定频率","_Freq","Hz","number",pParas->m_fEDFreq);
	pXmlSierialize->xml_serialize("测试前时间(秒)","_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("故障前时间(秒)","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("额定电压幅值","_UPre","V","number",pParas->m_fEDU);
	pXmlSierialize->xml_serialize("变化前电流幅值","_IPre","A","number",pParas->m_fEDI);
	pXmlSierialize->xml_serialize("故障前电压电流相角(U-I)", "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);

	pXmlSierialize->xml_serialize("常态电压相序","_UPhSet","","PhaseSet",pParas->m_nPhaseSet[0]);
	pXmlSierialize->xml_serialize("常态电流相序","_IPhSet","","PhaseSet",pParas->m_nPhaseSet[1]);
#else
	pXmlSierialize->xml_serialize(/*"变化始值"*/g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize(/*"变化终值"*/g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize(/*"测试精度"*/g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize(/*"步长时间(秒)"*/g_sLangTxt_Native_StepTimeSec.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize(/*"测试返回系数"*/g_sLangTxt_Native_TestReturnCoefficient.GetString(), "VaryMode", "", "number", pParas->m_nTestMode);
	//	pXmlSierialize->xml_serialize("测试通道类型", "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize(/*"递变相别"*/g_sLangTxt_Native_VariablePhaseChange.GetString(), "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
	//	pXmlSierialize->xml_serialize("递变类型", "VarType", "", "UIRampType", pParas->m_nType);
	pXmlSierialize->xml_serialize(/*"相位递变方向(0:逆时针 1:顺时针)"*/g_sLangTxt_Native_PhaseShiftDir01.GetString(), "PhaseGradDir", "", "number", pParas->m_nPhaseGradDir);

	pXmlSierialize->xml_serialize(/*"额定频率"*/g_sLangTxt_Report_Fnom.GetString(),"_Freq","Hz","number",pParas->m_fEDFreq);
	pXmlSierialize->xml_serialize(/*"测试前时间(秒)"*/g_sLangTxt_Native_PreTestTimeS.GetString(),"_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize(/*"故障前时间(秒)"*/g_sLangTxt_Native_FaultPreTimeS.GetString(),"_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize(/*"额定电压幅值"*/g_sLangTxt_Native_RatedVoltageAmplitude.GetString(),"_UPre","V","number",pParas->m_fEDU);
	pXmlSierialize->xml_serialize(/*"变化前电流幅值"*/g_sLangTxt_Native_IBeforeChange.GetString(),"_IPre","A","number",pParas->m_fEDI);
	pXmlSierialize->xml_serialize(/*"故障前电压电流相角(U-I)"*/g_sLangTxt_Native_FaultPreVoltageCurrentPhase.GetString(), "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);

	pXmlSierialize->xml_serialize(/*"常态电压相序"*/g_sLangTxt_Native_NomVoltPhaseSeq.GetString(),"_UPhSet","","PhaseSet",pParas->m_nPhaseSet[0]);
	pXmlSierialize->xml_serialize(/*"常态电流相序"*/g_sLangTxt_Native_NomCurrPhaseSeq.GetString(),"_IPhSet","","PhaseSet",pParas->m_nPhaseSet[1]);
#endif
	//根据变化前电流初始化故障前电流
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		pParas->m_fG1Current=pParas->m_fEDI;
		pParas->m_fG2Current=pParas->m_fEDI;

		pParas->m_fG1Volt = pParas->m_fEDU;
		pParas->m_fG2Volt = pParas->m_fEDU;

		pParas->m_fHz = pParas->m_fEDFreq;
	}

// 	pXmlSierialize->xml_serialize("故障态组1电压幅值","_UFaultG1","V","number",pParas->m_fG1Volt);
// 	pXmlSierialize->xml_serialize("故障态组2电压幅值","_UFaultG2","V","number",pParas->m_fG2Volt);
// 	pXmlSierialize->xml_serialize("故障态组1电流幅值","_IFaultG1","V","number",pParas->m_fG1Current);
// 	pXmlSierialize->xml_serialize("故障态组2电流幅值","_IFaultG2","V","number",pParas->m_fG2Current);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("故障态两组电流角差","_DiffIAngle","°","number",pParas->m_fDiffIAngle);
//	pXmlSierialize->xml_serialize("故障态频率","_FreqFault","Hz","number",pParas->m_fHz);

	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"故障态两组电流角差"*/g_sLangTxt_Native_FaultGroupIPhaseDiff.GetString(),"_DiffIAngle","°","number",pParas->m_fDiffIAngle);
	//	pXmlSierialize->xml_serialize("故障态频率","_FreqFault","Hz","number",pParas->m_fHz);

	pXmlSierialize->xml_serialize(/*"开入逻辑"*/g_sLangTxt_Native_InLogic.GetString(),"_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,TRUE);

	stt_xml_serializeGradientSetting(pParas,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
#ifdef NOT_USE_XLANGUAGE
		//自动测试传参
		pXmlSierialize->xml_serialize_sys_pata("Ua1幅值","UaAmp","V","number",pParas->m_uiVOL[2][0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ua1相位","UaPh","°","number",pParas->m_uiVOL[2][0].Harm[1].fAngle);
		//           pXmlSierialize->xml_serialize("Ua1频率","UaFre","Hz","number",pParas->m_uiVOL[2][0].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Ub1幅值","UbAmp","V","number",pParas->m_uiVOL[2][1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ub1相位","UbPh","°","number",pParas->m_uiVOL[2][1].Harm[1].fAngle);
		//           pXmlSierialize->xml_serialize("Ub1频率","UbFre","Hz","number",pParas->m_uiVOL[2][1].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Uc1幅值","UcAmp","V","number",pParas->m_uiVOL[2][2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Uc1相位","UcPh","°","number",pParas->m_uiVOL[2][2].Harm[1].fAngle);
		//           pXmlSierialize->xml_serialize("Uc1频率","UcFre","Hz","number",pParas->m_uiVOL[2][2].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Ua2幅值","UapAmp","V","number",pParas->m_uiVOL[2][3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ua2相位","UapPh","°","number",pParas->m_uiVOL[2][3].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ua2频率","UapFre","Hz","number",pParas->m_uiVOL[2][3].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Ub2幅值","UbpAmp","V","number",pParas->m_uiVOL[2][4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Ub2相位","UbpPh","°","number",pParas->m_uiVOL[2][4].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ub2频率","UbpFre","Hz","number",pParas->m_uiVOL[2][4].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Uc2幅值","UcpAmp","V","number",pParas->m_uiVOL[2][5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize("Uc2相位","UcpPh","°","number",pParas->m_uiVOL[2][5].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Uc2频率","UcpFre","Hz","number",pParas->m_uiVOL[2][5].Harm[1].fFreq);

		pXmlSierialize->xml_serialize_sys_pata("Ia1幅值","IaAmp","A","number",pParas->m_uiCUR[2][0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ia1相位","IaPh","°","number",pParas->m_uiCUR[2][0].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ia1频率","IaFre","Hz","number",pParas->m_uiCUR[2][0].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Ib1幅值","IbAmp","A","number",pParas->m_uiCUR[2][1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ib1相位","IbPh","°","number",pParas->m_uiCUR[2][1].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ib1频率","IbFre","Hz","number",pParas->m_uiCUR[2][1].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Ic1幅值","IcAmp","A","number",pParas->m_uiCUR[2][2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ic1相位","IcPh","°","number",pParas->m_uiCUR[2][2].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ic1频率","IcFre","Hz","number",pParas->m_uiCUR[2][2].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Ia2幅值","IapAmp","A","number",pParas->m_uiCUR[2][3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ia2相位","IapPh","°","number",pParas->m_uiCUR[2][3].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ia2频率","IapFre","Hz","number",pParas->m_uiCUR[2][3].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Ib2幅值","IbpAmp","A","number",pParas->m_uiCUR[2][4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ib2相位","IbpPh","°","number",pParas->m_uiCUR[2][4].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ib2频率","IbpFre","Hz","number",pParas->m_uiCUR[2][4].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata("Ic2幅值","IcpAmp","A","number",pParas->m_uiCUR[2][5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize("Ic2相位","IcpPh","°","number",pParas->m_uiCUR[2][5].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ic2频率","IcpFre","Hz","number",pParas->m_uiCUR[2][5].Harm[1].fFreq);
#else
		//自动测试传参
		pXmlSierialize->xml_serialize_sys_pata(/*"Ua1幅值"*/g_sLangTxt_Native_Ua1Amp.GetString(),"UaAmp","V","number",pParas->m_uiVOL[2][0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ua1相位"*/g_sLangTxt_Native_Ua1Ph.GetString(),"UaPh","°","number",pParas->m_uiVOL[2][0].Harm[1].fAngle);
		//           pXmlSierialize->xml_serialize("Ua1频率","UaFre","Hz","number",pParas->m_uiVOL[2][0].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ub1幅值"*/g_sLangTxt_Native_Ub1Amp.GetString(),"UbAmp","V","number",pParas->m_uiVOL[2][1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ub1相位"*/g_sLangTxt_Native_Ub1Ph.GetString(),"UbPh","°","number",pParas->m_uiVOL[2][1].Harm[1].fAngle);
		//           pXmlSierialize->xml_serialize("Ub1频率","UbFre","Hz","number",pParas->m_uiVOL[2][1].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Uc1幅值"*/g_sLangTxt_Native_Uc1Amp.GetString(),"UcAmp","V","number",pParas->m_uiVOL[2][2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Uc1相位"*/g_sLangTxt_Native_Uc1Ph.GetString(),"UcPh","°","number",pParas->m_uiVOL[2][2].Harm[1].fAngle);
		//           pXmlSierialize->xml_serialize("Uc1频率","UcFre","Hz","number",pParas->m_uiVOL[2][2].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ua2幅值"*/g_sLangTxt_Native_Ua2Amp.GetString(),"UapAmp","V","number",pParas->m_uiVOL[2][3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ua2相位"*/g_sLangTxt_Native_Ua2Ph.GetString(),"UapPh","°","number",pParas->m_uiVOL[2][3].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ua2频率","UapFre","Hz","number",pParas->m_uiVOL[2][3].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ub2幅值"*/g_sLangTxt_Native_Ub2Amp.GetString(),"UbpAmp","V","number",pParas->m_uiVOL[2][4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Ub2相位"*/g_sLangTxt_Native_Ub2Ph.GetString(),"UbpPh","°","number",pParas->m_uiVOL[2][4].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ub2频率","UbpFre","Hz","number",pParas->m_uiVOL[2][4].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Uc2幅值"*/g_sLangTxt_Native_Uc2Amp.GetString(),"UcpAmp","V","number",pParas->m_uiVOL[2][5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
		pXmlSierialize->xml_serialize(/*"Uc2相位"*/g_sLangTxt_Native_Uc2Ph.GetString(),"UcpPh","°","number",pParas->m_uiVOL[2][5].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Uc2频率","UcpFre","Hz","number",pParas->m_uiVOL[2][5].Harm[1].fFreq);

		pXmlSierialize->xml_serialize_sys_pata(/*"Ia1幅值"*/g_sLangTxt_Native_Ia1Amp.GetString(),"IaAmp","A","number",pParas->m_uiCUR[2][0].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ia1相位"*/g_sLangTxt_Native_Ia1Ph.GetString(),"IaPh","°","number",pParas->m_uiCUR[2][0].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ia1频率","IaFre","Hz","number",pParas->m_uiCUR[2][0].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ib1幅值"*/g_sLangTxt_Native_Ib1Amp.GetString(),"IbAmp","A","number",pParas->m_uiCUR[2][1].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ib1相位"*/g_sLangTxt_Native_Ib1Ph.GetString(),"IbPh","°","number",pParas->m_uiCUR[2][1].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ib1频率","IbFre","Hz","number",pParas->m_uiCUR[2][1].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ic1幅值"*/g_sLangTxt_Native_Ic1Amp.GetString(),"IcAmp","A","number",pParas->m_uiCUR[2][2].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ic1相位"*/g_sLangTxt_Native_Ic1Ph.GetString(),"IcPh","°","number",pParas->m_uiCUR[2][2].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ic1频率","IcFre","Hz","number",pParas->m_uiCUR[2][2].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ia2幅值"*/g_sLangTxt_Native_Ia2Amp.GetString(),"IapAmp","A","number",pParas->m_uiCUR[2][3].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ia2相位"*/g_sLangTxt_Native_Ia2Ph.GetString(),"IapPh","°","number",pParas->m_uiCUR[2][3].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ia2频率","IapFre","Hz","number",pParas->m_uiCUR[2][3].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ib2幅值"*/g_sLangTxt_Native_Ib2Amp.GetString(),"IbpAmp","A","number",pParas->m_uiCUR[2][4].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ib2相位"*/g_sLangTxt_Native_Ib2Ph.GetString(),"IbpPh","°","number",pParas->m_uiCUR[2][4].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ib2频率","IbpFre","Hz","number",pParas->m_uiCUR[2][4].Harm[1].fFreq);
		pXmlSierialize->xml_serialize_sys_pata(/*"Ic2幅值"*/g_sLangTxt_Native_Ic2Amp.GetString(),"IcpAmp","A","number",pParas->m_uiCUR[2][5].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
		pXmlSierialize->xml_serialize(/*"Ic2相位"*/g_sLangTxt_Native_Ic2Ph.GetString(),"IcpPh","°","number",pParas->m_uiCUR[2][5].Harm[1].fAngle);
		//            pXmlSierialize->xml_serialize("Ic2频率","IcpFre","Hz","number",pParas->m_uiCUR[2][5].Harm[1].fFreq);	
#endif
	}	

// 	if (stt_xml_serialize_is_read(pXmlSierialize))
// 	{
// 		stt_xml_serialize(&pParas->m_oGoosePub[0],pXmlSierialize);
// 	}
}


//用于高级试验模块,非单独递变模块使用
void stt_xml_serialize_common(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("测试前时间(秒)","_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("故障前时间(秒)","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("故障时间裕度","MarginTime","s","number",pParas->m_fMarginTime);

	pXmlSierialize->xml_serialize("常态电压幅值","_UPre","V","number",pParas->m_fG1Volt);
	pXmlSierialize->xml_serialize("常态电压相序","_UPhSet","","PhaseSet",pParas->m_nPhaseSet[0]);
	pXmlSierialize->xml_serialize("常态电流幅值","_IPre","A","number",pParas->m_fG1Current);
	pXmlSierialize->xml_serialize("常态电流相序","_IPhSet","","PhaseSet",pParas->m_nPhaseSet[1]);
	pXmlSierialize->xml_serialize("故障前电压电流相角(U-I)", "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);
#else
	pXmlSierialize->xml_serialize(/*"测试前时间(秒)"*/g_sLangTxt_Native_PreTestTimeS.GetString(),"_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize(/*"故障前时间(秒)"*/g_sLangTxt_Native_FaultPreTimeS.GetString(),"_PreFaultTime","s","number",pParas->m_fPreFaultTime);

	pXmlSierialize->xml_serialize(/*"常态电压幅值"*/g_sLangTxt_Native_NomVoltAmplitude.GetString(),"_UPre","V","number",pParas->m_fG1Volt);
	pXmlSierialize->xml_serialize(/*"常态电压相序"*/g_sLangTxt_Native_NomVoltPhaseSeq.GetString(),"_UPhSet","","PhaseSet",pParas->m_nPhaseSet[0]);
	pXmlSierialize->xml_serialize(/*"常态电流幅值"*/g_sLangTxt_Native_NomCurrAmplitude.GetString(),"_IPre","A","number",pParas->m_fG1Current);
	pXmlSierialize->xml_serialize(/*"常态电流相序"*/g_sLangTxt_Native_NomCurrPhaseSeq.GetString(),"_IPhSet","","PhaseSet",pParas->m_nPhaseSet[1]);
	pXmlSierialize->xml_serialize(/*"故障前电压电流相角(U-I)"*/g_sLangTxt_Native_FaultPreVoltageCurrentPhase.GetString(), "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);
#endif
	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,TRUE);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
		pXmlSierialize->xml_serialize(/*"开入逻辑"*/g_sLangTxt_Native_InLogic.GetString(),"_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#endif
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("测试前时间(秒)","PrepareTime","s","number",pParas->m_fPrepareTime);
		pXmlSierialize->xml_serialize("故障前时间(秒)","PrepareTime","s","number",pParas->m_fPreFaultTime);

		pXmlSierialize->xml_serialize("常态电压幅值","PreVol","V","number",pParas->m_fG1Volt);
		pXmlSierialize->xml_serialize("常态电流幅值","PreCur","A","number",pParas->m_fG1Current);
		pXmlSierialize->xml_serialize("故障前电压电流相角(U-I)", "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);

		pXmlSierialize->xml_serialize("开入A选择","_BinAEnable","","BOOL",pParas->m_binIn[0].nSelect);
		pXmlSierialize->xml_serialize("开入B选择","_BinBEnable","","BOOL",pParas->m_binIn[1].nSelect);
		pXmlSierialize->xml_serialize("开入C选择","_BinCEnable","","BOOL",pParas->m_binIn[2].nSelect);
		pXmlSierialize->xml_serialize("开入D选择","_BinDEnable","","BOOL",pParas->m_binIn[3].nSelect);
		pXmlSierialize->xml_serialize("开入E选择","_BinEEnable","","BOOL",pParas->m_binIn[4].nSelect);
		pXmlSierialize->xml_serialize("开入F选择","_BinFEnable","","BOOL",pParas->m_binIn[5].nSelect);
		pXmlSierialize->xml_serialize("开入G选择","_BinGEnable","","BOOL",pParas->m_binIn[6].nSelect);
		pXmlSierialize->xml_serialize("开入H选择","_BinHEnable","","BOOL",pParas->m_binIn[7].nSelect);
		pXmlSierialize->xml_serialize("开入I选择","_BinIEnable","","BOOL",pParas->m_binIn[8].nSelect);
		pXmlSierialize->xml_serialize("开入J选择","_BinJEnable","","BOOL",pParas->m_binIn[9].nSelect);

		pXmlSierialize->xml_serialize("常态开出1状态","_B0_01","","DOutputState",pParas->m_binOut[0][0].nState);
		pXmlSierialize->xml_serialize("常态开出2状态","_B0_02","","DOutputState",pParas->m_binOut[0][1].nState);
		pXmlSierialize->xml_serialize("常态开出3状态","_B0_03","","DOutputState",pParas->m_binOut[0][2].nState);
		pXmlSierialize->xml_serialize("常态开出4状态","_B0_04","","DOutputState",pParas->m_binOut[0][3].nState);
		pXmlSierialize->xml_serialize("常态开出5状态","_B0_05","","DOutputState",pParas->m_binOut[0][4].nState);
		pXmlSierialize->xml_serialize("常态开出6状态","_B0_06","","DOutputState",pParas->m_binOut[0][5].nState);
		pXmlSierialize->xml_serialize("常态开出7状态","_B0_07","","DOutputState",pParas->m_binOut[0][6].nState);
		pXmlSierialize->xml_serialize("常态开出8状态","_B0_08","","DOutputState",pParas->m_binOut[0][7].nState);

		pXmlSierialize->xml_serialize("故障态开出1状态","_B1_01","","DOutputState",pParas->m_binOut[1][0].nState);
		pXmlSierialize->xml_serialize("故障态开出2状态","_B1_02","","DOutputState",pParas->m_binOut[1][1].nState);
		pXmlSierialize->xml_serialize("故障态开出3状态","_B1_03","","DOutputState",pParas->m_binOut[1][2].nState);
		pXmlSierialize->xml_serialize("故障态开出4状态","_B1_04","","DOutputState",pParas->m_binOut[1][3].nState);
		pXmlSierialize->xml_serialize("故障态开出5状态","_B1_05","","DOutputState",pParas->m_binOut[1][4].nState);
		pXmlSierialize->xml_serialize("故障态开出6状态","_B1_06","","DOutputState",pParas->m_binOut[1][5].nState);
		pXmlSierialize->xml_serialize("故障态开出7状态","_B1_07","","DOutputState",pParas->m_binOut[1][6].nState);
		pXmlSierialize->xml_serialize("故障态开出8状态","_B1_08","","DOutputState",pParas->m_binOut[1][7].nState);
#else
		pXmlSierialize->xml_serialize(/*"测试前时间(秒)"*/g_sLangTxt_Native_PreTestTimeS.GetString(),"PrepareTime","s","number",pParas->m_fPrepareTime);
		pXmlSierialize->xml_serialize(/*"故障前时间(秒)"*/g_sLangTxt_Native_FaultPreTimeS.GetString(),"PrepareTime","s","number",pParas->m_fPreFaultTime);

		pXmlSierialize->xml_serialize(/*"常态电压幅值"*/g_sLangTxt_Native_NomVoltAmplitude.GetString(),"PreVol","V","number",pParas->m_fG1Volt);
		pXmlSierialize->xml_serialize(/*"常态电流幅值"*/g_sLangTxt_Native_NomCurrAmplitude.GetString(),"PreCur","A","number",pParas->m_fG1Current);
		pXmlSierialize->xml_serialize(/*"故障前电压电流相角(U-I)"*/g_sLangTxt_Native_FaultPreVoltageCurrentPhase.GetString(), "PreAngle", "°", "number",  pParas->m_fEDUaIaAngle);

		pXmlSierialize->xml_serialize(/*"开入A选择"*/g_sLangTxt_Native_InputASelect.GetString(),"_BinAEnable","","BOOL",pParas->m_binIn[0].nSelect);
		pXmlSierialize->xml_serialize(/*"开入B选择"*/g_sLangTxt_Native_InputBSelect.GetString(),"_BinBEnable","","BOOL",pParas->m_binIn[1].nSelect);
		pXmlSierialize->xml_serialize(/*"开入C选择"*/g_sLangTxt_Native_InputCSelect.GetString(),"_BinCEnable","","BOOL",pParas->m_binIn[2].nSelect);
		pXmlSierialize->xml_serialize(/*"开入D选择"*/g_sLangTxt_Native_InputDSelect.GetString(),"_BinDEnable","","BOOL",pParas->m_binIn[3].nSelect);
		pXmlSierialize->xml_serialize(/*"开入E选择"*/g_sLangTxt_Native_InputESelect.GetString(),"_BinEEnable","","BOOL",pParas->m_binIn[4].nSelect);
		pXmlSierialize->xml_serialize(/*"开入F选择"*/g_sLangTxt_Native_InputFSelect.GetString(),"_BinFEnable","","BOOL",pParas->m_binIn[5].nSelect);
		pXmlSierialize->xml_serialize(/*"开入G选择"*/g_sLangTxt_Native_InputGSelect.GetString(),"_BinGEnable","","BOOL",pParas->m_binIn[6].nSelect);
		pXmlSierialize->xml_serialize(/*"开入H选择"*/g_sLangTxt_Native_InputHSelect.GetString(),"_BinHEnable","","BOOL",pParas->m_binIn[7].nSelect);
		pXmlSierialize->xml_serialize(/*"开入I选择"*/g_sLangTxt_Native_InputISelect.GetString(),"_BinIEnable","","BOOL",pParas->m_binIn[8].nSelect);
		pXmlSierialize->xml_serialize(/*"开入J选择"*/g_sLangTxt_Native_InputJSelect.GetString(),"_BinJEnable","","BOOL",pParas->m_binIn[9].nSelect);

		pXmlSierialize->xml_serialize(/*"常态开出1状态"*/g_sLangTxt_Native_NormalOpen1State.GetString(),"_B0_01","","DOutputState",pParas->m_binOut[0][0].nState);
		pXmlSierialize->xml_serialize(/*"常态开出2状态"*/g_sLangTxt_Native_NormalOpen2State.GetString(),"_B0_02","","DOutputState",pParas->m_binOut[0][1].nState);
		pXmlSierialize->xml_serialize(/*"常态开出3状态"*/g_sLangTxt_Native_NormalOpen3State.GetString(),"_B0_03","","DOutputState",pParas->m_binOut[0][2].nState);
		pXmlSierialize->xml_serialize(/*"常态开出4状态"*/g_sLangTxt_Native_NormalOpen4State.GetString(),"_B0_04","","DOutputState",pParas->m_binOut[0][3].nState);
		pXmlSierialize->xml_serialize(/*"常态开出5状态"*/g_sLangTxt_Native_NormalOpen5State.GetString(),"_B0_05","","DOutputState",pParas->m_binOut[0][4].nState);
		pXmlSierialize->xml_serialize(/*"常态开出6状态"*/g_sLangTxt_Native_NormalOpen6State.GetString(),"_B0_06","","DOutputState",pParas->m_binOut[0][5].nState);
		pXmlSierialize->xml_serialize(/*"常态开出7状态"*/g_sLangTxt_Native_NormalOpen7State.GetString(),"_B0_07","","DOutputState",pParas->m_binOut[0][6].nState);
		pXmlSierialize->xml_serialize(/*"常态开出8状态"*/g_sLangTxt_Native_NormalOpen8State.GetString(),"_B0_08","","DOutputState",pParas->m_binOut[0][7].nState);

		pXmlSierialize->xml_serialize(/*"故障态开出1状态"*/g_sLangTxt_Native_FaultOpen1State.GetString(),"_B1_01","","DOutputState",pParas->m_binOut[1][0].nState);
		pXmlSierialize->xml_serialize(/*"故障态开出2状态"*/g_sLangTxt_Native_FaultOpen2State.GetString(),"_B1_02","","DOutputState",pParas->m_binOut[1][1].nState);
		pXmlSierialize->xml_serialize(/*"故障态开出3状态"*/g_sLangTxt_Native_FaultOpen3State.GetString(),"_B1_03","","DOutputState",pParas->m_binOut[1][2].nState);
		pXmlSierialize->xml_serialize(/*"故障态开出4状态"*/g_sLangTxt_Native_FaultOpen4State.GetString(),"_B1_04","","DOutputState",pParas->m_binOut[1][3].nState);
		pXmlSierialize->xml_serialize(/*"故障态开出5状态"*/g_sLangTxt_Native_FaultOpen5State.GetString(),"_B1_05","","DOutputState",pParas->m_binOut[1][4].nState);
		pXmlSierialize->xml_serialize(/*"故障态开出6状态"*/g_sLangTxt_Native_FaultOpen6State.GetString(),"_B1_06","","DOutputState",pParas->m_binOut[1][5].nState);
		pXmlSierialize->xml_serialize(/*"故障态开出7状态"*/g_sLangTxt_Native_FaultOpen7State.GetString(),"_B1_07","","DOutputState",pParas->m_binOut[1][6].nState);
		pXmlSierialize->xml_serialize(/*"故障态开出8状态"*/g_sLangTxt_Native_FaultOpen8State.GetString(),"_B1_08","","DOutputState",pParas->m_binOut[1][7].nState);
#endif
	}
}

void stt_xml_serialize_Chs(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	CString strID,strTypeID[3];
	strTypeID[0] = _T("_Prepare");
	strTypeID[1] = _T("_PreFault");
	strTypeID[2] = _T("_Fault");

	for (int nTypeIndex = 0;nTypeIndex < 3;nTypeIndex++)
	{
		for(int nIndex=0;nIndex<6;nIndex++)
		{
			strID.Format(_T("U%d%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize_sys_pata("",strID.GetString(),"V","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
			strID.Format(_T("U%dPh%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
			pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fAngle);
			strID.Format(_T("U%dFre%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize_sys_pata("",strID.GetString(),"Hz","number",pParas->m_uiVOL[nTypeIndex][nIndex].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		}

		for(int nIndex=0;nIndex<6;nIndex++)
		{
			strID.Format(_T("I%d%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize_sys_pata("",strID.GetString(),"A","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_INom);
			strID.Format(_T("I%dPh%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
			pXmlSierialize->xml_serialize("",strID.GetString(),"°","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fAngle);
			strID.Format(_T("I%dFre%s"),nIndex+1,strTypeID[nTypeIndex].GetString());
            pXmlSierialize->xml_serialize_sys_pata("",strID.GetString(),"Hz","number",pParas->m_uiCUR[nTypeIndex][nIndex].Harm[1].fFreq,STT_XML_SERIALIZE_SYS_PARA_ID_FNom);
		}
	}
}

void stt_xml_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{	
	/*pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize("步长时间(秒)", "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize("测试返回系数", "VaryMode", "", "number", pParas->m_nTestMode);
	pXmlSierialize->xml_serialize("递变相别", "VarIndex", "", "UIRampChannel", pParas->m_nChannel);
	pXmlSierialize->xml_serialize("递变类型", "VarType", "", "UIRampType", pParas->m_nType);

	pXmlSierialize->xml_serialize("额定频率","_Freq","Hz","number",pParas->m_fEDFreq);
	pXmlSierialize->xml_serialize("测试前时间(秒)","_PrepareTime","s","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("故障前时间(秒)","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("额定电压幅值","_UPre","V","number",pParas->m_fEDU);
	pXmlSierialize->xml_serialize("额定电流幅值","_IPre","A","number",pParas->m_fEDI);
	pXmlSierialize->xml_serialize("额定电压电流相角", "Phi0", "°", "number",  pParas->m_fEDUaIaAngle);

	pXmlSierialize->xml_serialize("故障态组1电压幅值","_UFault","V","number",pParas->m_fG1Volt);
	pXmlSierialize->xml_serialize("故障态组2电压幅值","_UFault","V","number",pParas->m_fG2Volt);
	pXmlSierialize->xml_serialize("故障态组1电流幅值","_IFault","V","number",pParas->m_fG1Current);
	pXmlSierialize->xml_serialize("故障态组2电流幅值","_IFault","V","number",pParas->m_fG2Current);
	pXmlSierialize->xml_serialize("故障态两组电流角差","_DiffIAngle","°","number",pParas->m_fDiffIAngle);
	pXmlSierialize->xml_serialize("故障态频率","_FreqFault","Hz","number",pParas->m_fHz);*/

	stt_xml_serialize_base(pParas, pXmlSierialize);

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		if(pParas->m_nSttTestMode == GradientTest_Base_1)
		{
			stt_xml_serialize_Chs(pParas, pXmlSierialize);
		}
	}

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
		stt_xml_serialize(&pParas->m_oGoosePub[0],pXmlSierialize);
	}
	/*pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[0],pXmlSierialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx[1],pXmlSierialize,TRUE);*/
}

void stt_xml_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("动作值","TripValue","A/V","number",pResults->m_fTripValue);
	pXmlSierialize->xml_serialize("动作时间","TripTime","s","number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("返回值","ReturnValue","A/V","number",pResults->m_fReturnValue);
	pXmlSierialize->xml_serialize("返回系数","ReturnCoef","","number",pResults->m_fReturnCoef);
	pXmlSierialize->xml_serialize("边界角1","AngleF","","number",pResults->m_oMaxAngle.m_fAngleF);
	pXmlSierialize->xml_serialize("边界角2","AngleS","","number",pResults->m_oMaxAngle.m_fAngleS);
	pXmlSierialize->xml_serialize("最大灵敏角","MaxAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);
	pXmlSierialize->xml_serialize("电压动作值误差","TripUErrVal","","number",pResults->m_fTripUErrVal);
	pXmlSierialize->xml_serialize("电流动作值误差","TripIErrVal","","number",pResults->m_fTripIErrVal);
	pXmlSierialize->xml_serialize("频率动作值误差","TripHzErrVal","","number",pResults->m_fTripHzErrVal);
	pXmlSierialize->xml_serialize("相位动作值误差","TripAngleErrVal","","number",pResults->m_fTripAngleErrVal);
	pXmlSierialize->xml_serialize("返回系数误差","RetCoefErrVal","","number",pResults->m_fRetCoefErrVal);
	pXmlSierialize->xml_serialize("最大灵敏角误差","MaxAngleErrVal","","number",pResults->m_fMaxAngleErrVal);
	pXmlSierialize->xml_serialize("边界角1误差","AngleFErrVal","","number",pResults->m_fAngleFErrVal);
	pXmlSierialize->xml_serialize("边界角2误差","AngleSErrVal","","number",pResults->m_fAngleSErrVal);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
	pXmlSierialize->xml_serialize("开入1动作值","TripValueA","A/V","number",pResults->m_fTripValueChl[0]);
	pXmlSierialize->xml_serialize("开入2动作值","TripValueB","A/V","number",pResults->m_fTripValueChl[1]);
	pXmlSierialize->xml_serialize("开入3动作值","TripValueC","A/V","number",pResults->m_fTripValueChl[2]);
	pXmlSierialize->xml_serialize("开入4动作值","TripValueD","A/V","number",pResults->m_fTripValueChl[3]);
	pXmlSierialize->xml_serialize("开入5动作值","TripValueE","A/V","number",pResults->m_fTripValueChl[4]);
	pXmlSierialize->xml_serialize("开入6动作值","TripValueF","A/V","number",pResults->m_fTripValueChl[5]);
	pXmlSierialize->xml_serialize("开入7动作值","TripValueG","A/V","number",pResults->m_fTripValueChl[6]);
	pXmlSierialize->xml_serialize("开入8动作值","TripValueH","A/V","number",pResults->m_fTripValueChl[7]);
#else
	pXmlSierialize->xml_serialize(/*"动作值"*/g_sLangTxt_State_ActionValue.GetString(),"TripValue","A/V","number",pResults->m_fTripValue);
	pXmlSierialize->xml_serialize(/*"动作时间"*/g_sLangTxt_Gradient_ActionTime.GetString(),"TripTime","s","number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/*"返回值"*/g_sLangTxt_Native_ReturnValue.GetString(),"ReturnValue","A/V","number",pResults->m_fReturnValue);
	pXmlSierialize->xml_serialize(/*"返回系数"*/g_sLangTxt_Gradient_ReCoefficient.GetString(),"ReturnCoef","","number",pResults->m_fReturnCoef);
	pXmlSierialize->xml_serialize(/*"边界角1"*/g_sLangTxt_Native_BoundAngle1.GetString(),"AngleF","","number",pResults->m_oMaxAngle.m_fAngleF);
	pXmlSierialize->xml_serialize(/*"边界角2"*/g_sLangTxt_Native_BoundAngle2.GetString(),"AngleS","","number",pResults->m_oMaxAngle.m_fAngleS);
	pXmlSierialize->xml_serialize(/*"最大灵敏角"*/g_sLangTxt_Gradient_MaxAngle.GetString(),"MaxAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);
	pXmlSierialize->xml_serialize(/*"电压动作值误差"*/g_sLangTxt_Native_VActionValueErr.GetString(),"TripUErrVal","","number",pResults->m_fTripUErrVal);
	pXmlSierialize->xml_serialize(/*"电流动作值误差"*/g_sLangTxt_Native_IActionValueErr.GetString(),"TripIErrVal","","number",pResults->m_fTripIErrVal);
	pXmlSierialize->xml_serialize(/*"频率动作值误差"*/g_sLangTxt_Native_FreqTripValErr.GetString(),"TripHzErrVal","","number",pResults->m_fTripHzErrVal);
	pXmlSierialize->xml_serialize(/*"相位动作值误差"*/g_sLangTxt_Native_PhaseTripValErr.GetString(),"TripAngleErrVal","","number",pResults->m_fTripAngleErrVal);
	pXmlSierialize->xml_serialize(/*"返回系数误差"*/g_sLangTxt_Native_RetCoeffError.GetString(),"RetCoefErrVal","","number",pResults->m_fRetCoefErrVal);
	pXmlSierialize->xml_serialize(/*"最大灵敏角误差"*/g_sLangTxt_Native_MaxSensAngleErr.GetString(),"MaxAngleErrVal","","number",pResults->m_fMaxAngleErrVal);
	pXmlSierialize->xml_serialize(/*"边界角1误差"*/g_sLangTxt_Native_BndryAngle1Err.GetString(),"AngleFErrVal","","number",pResults->m_fAngleFErrVal);
	pXmlSierialize->xml_serialize(/*"边界角2误差"*/g_sLangTxt_Native_BndryAngle2Err.GetString(),"AngleSErrVal","","number",pResults->m_fAngleSErrVal);
	pXmlSierialize->xml_serialize(/*"动作描述"*/g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
	pXmlSierialize->xml_serialize(/*"开入1动作值"*/g_sLangTxt_Native_input1_ActionVal.GetString(),"TripValueA","A/V","number",pResults->m_fTripValueChl[0]);
	pXmlSierialize->xml_serialize(/*"开入2动作值"*/g_sLangTxt_Native_input2_ActionVal.GetString(),"TripValueB","A/V","number",pResults->m_fTripValueChl[1]);
	pXmlSierialize->xml_serialize(/*"开入3动作值"*/g_sLangTxt_Native_input3_ActionVal.GetString(),"TripValueC","A/V","number",pResults->m_fTripValueChl[2]);
	pXmlSierialize->xml_serialize(/*"开入4动作值"*/g_sLangTxt_Native_input4_ActionVal.GetString(),"TripValueD","A/V","number",pResults->m_fTripValueChl[3]);
	pXmlSierialize->xml_serialize(/*"开入5动作值"*/g_sLangTxt_Native_input5_ActionVal.GetString(),"TripValueE","A/V","number",pResults->m_fTripValueChl[4]);
	pXmlSierialize->xml_serialize(/*"开入6动作值"*/g_sLangTxt_Native_input6_ActionVal.GetString(),"TripValueF","A/V","number",pResults->m_fTripValueChl[5]);
	pXmlSierialize->xml_serialize(/*"开入7动作值"*/g_sLangTxt_Native_input7_ActionVal.GetString(),"TripValueG","A/V","number",pResults->m_fTripValueChl[6]);
	pXmlSierialize->xml_serialize(/*"开入8动作值"*/g_sLangTxt_Native_input8_ActionVal.GetString(),"TripValueH","A/V","number",pResults->m_fTripValueChl[7]);
#endif

// 	CString strName1 = _T("开入扩展"),strName2 = _T("动作值");
// 	CString strID,strTmp,strName;
// 
// 	for (int nIndex = 0; nIndex<MAX_ExBINARY_COUNT;nIndex++)
// 	{
// 		strTmp.Format(_T("%d"),nIndex+1);
// 		strName = strName1 + strTmp + strName2;
// 		strID.Format("TripValueEx%d",nIndex+1);
// 		pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"A/V","number",pParas->m_fTripValueExChl[nIndex]);
// 	}

	if (g_nBinExCount>0)
	{
		CSttXmlSerializeBase *pXmlTripValueEx = pXmlSierialize->xml_serialize("TripValueEx", "TripValueEx", "TripValueEx", stt_ParaGroupKey());

		if (pXmlTripValueEx != NULL)
		{
			CString strName,strID,strTemp;
#ifdef NOT_USE_XLANGUAGE
			CString str1 = _T("开入");
			CString str1Ex = _T("开入扩展");
			CString str2 = _T("动作值");
#else
			CString str1 = /*_T("开入")*/g_sLangTxt_Native_BinX;
			CString str1Ex = /*_T("开入扩展")*/g_sLangTxt_Native_InputExpand;
			CString str2 = /*_T("动作值")*/g_sLangTxt_State_ActionValue;
#endif

			for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
			{
				strTemp.Format(_T("%d"),nIndex+1);
				strName = str1Ex + strTemp + str2;

				strID.Format("TripValueEx%d",(nIndex+1));
				pXmlTripValueEx->xml_serialize(strName.GetString(),strID.GetString(),"","A/V",pResults->m_fTripValueExChl[nIndex]);
			}
		}
	}
}

void stt_xml_serialize_ex(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	/*pGradientSerialize->xml_serialize("变化始值", "BeginVal", "", "set", oPara.m_fStart);
	pGradientSerialize->xml_serialize("变化终值", "EndVal", "", "set", oPara.m_fStop );
	pGradientSerialize->xml_serialize("测试精度", "Step", "", "set", oPara.m_fStep);
	pGradientSerialize->xml_serialize("步长时间(秒)", "StepTime", "s", "set", oPara.m_fStepTime);
	pGradientSerialize->xml_serialize("测试返回系数", "VaryMode", "", "number", oPara.m_nTestMode);
	pGradientSerialize->xml_serialize("递变相别", "VarIndex", "", "UIRampChannel", oPara.m_nChannel);
	pGradientSerialize->xml_serialize("递变类型", "VarType", "", "UIRampType", oPara.m_nType);

	pGradientSerialize->xml_serialize("额定频率","_Freq","Hz","number",oPara.m_fEDFreq);
	pGradientSerialize->xml_serialize("测试前时间(秒)","_PrepareTime","s","number",oPara.m_fPrepareTime);
	pGradientSerialize->xml_serialize("故障前时间(秒)","_PreFaultTime","s","number",oPara.m_fPreFaultTime);
	pGradientSerialize->xml_serialize("额定电压幅值","_UPre","V","number",oPara.m_fEDU);
	pGradientSerialize->xml_serialize("额定电流幅值","_IPre","A","number",oPara.m_fEDI);
	pGradientSerialize->xml_serialize("额定电压电流相角", "Phi0", "°", "number",  oPara.m_fEDUaIaAngle);

	pGradientSerialize->xml_serialize("故障态组1电压幅值","_UFault1","V","number",oPara.m_fG1Volt);
	pGradientSerialize->xml_serialize("故障态组2电压幅值","_UFault2","V","number",oPara.m_fG2Volt);
	pGradientSerialize->xml_serialize("故障态组1电流幅值","_IFault1","V","number",oPara.m_fG1Current);
	pGradientSerialize->xml_serialize("故障态组2电流幅值","_IFault2","V","number",oPara.m_fG2Current);
	pGradientSerialize->xml_serialize("故障态两组电流角差","_DiffIAngle","°","number",oPara.m_fDiffIAngle);
	pGradientSerialize->xml_serialize("故障态频率","_FreqFault","Hz","number",oPara.m_fHz);

	pGradientSerialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",oPara.m_nBinLogic);
	stt_xml_serialize_binary_in(oPara.m_binIn,pGradientSerialize);
	stt_xml_serialize_Exbinary_in(oPara.m_binInEx,pGradientSerialize);
	stt_xml_serialize_binary_out(&oPara, pGradientSerialize);
	stt_xml_serialize_Gradient_Exbinary_out(oPara.m_binOutEx[0],pGradientSerialize,FALSE);
	stt_xml_serialize_Gradient_Exbinary_out(oPara.m_binOutEx[1],pGradientSerialize,TRUE);*/

	stt_xml_serialize_base(pParas, pXmlSierialize);
	stt_xml_serialize_Chs(pParas, pXmlSierialize);

	tmt_GradientParasEx* pParasEx = (tmt_GradientParasEx*)pParas;

	//判据条件
	int bVal = 0;
	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("相对误差有效","_XD","","number",bVal);
		pParasEx->sCondition.bXD = bVal;
		pXmlSierialize->xml_serialize("相对误差","_XDVal","","number",pParasEx->sCondition.fXD);
#else
		pXmlSierialize->xml_serialize(/*"相对误差有效"*/g_sLangTxt_Native_relativeErr.GetString(),"_XD","","number",bVal);
		pParasEx->sCondition.bXD = bVal;
		pXmlSierialize->xml_serialize(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError.GetString(),"_XDVal","","number",pParasEx->sCondition.fXD);
#endif
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		if(pParasEx->sCondition.bXD){	bVal = 1;	}
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("相对误差有效","_XD","","number",bVal);
		pXmlSierialize->xml_serialize("相对误差","_XDVal","","number",pParasEx->sCondition.fXD);
#else
		pXmlSierialize->xml_serialize(/*"相对误差有效"*/g_sLangTxt_Native_relativeErr.GetString(),"_XD","","number",bVal);
		pXmlSierialize->xml_serialize(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError.GetString(),"_XDVal","","number",pParasEx->sCondition.fXD);
#endif
	}

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("绝对误差有效","_JD","","number",bVal);
		pParasEx->sCondition.bJD = bVal;
		pXmlSierialize->xml_serialize("绝对误差","_JDVal","","number",pParasEx->sCondition.fJD);
#else
		pXmlSierialize->xml_serialize(/*"绝对误差有效"*/g_sLangTxt_Native_AbsErrValid.GetString(),"_JD","","number",bVal);
		pParasEx->sCondition.bJD = bVal;
		pXmlSierialize->xml_serialize(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError.GetString(),"_JDVal","","number",pParasEx->sCondition.fJD);
#endif
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		bVal = 0;
		if(pParasEx->sCondition.bJD){	bVal = 1;	}
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("绝对误差有效","_JD","","number",bVal);
		pXmlSierialize->xml_serialize("绝对误差","_JDVal","","number",pParasEx->sCondition.fJD);
#else
		pXmlSierialize->xml_serialize(/*"绝对误差有效"*/g_sLangTxt_Native_AbsErrValid.GetString(),"_JD","","number",bVal);
		pXmlSierialize->xml_serialize(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError.GetString(),"_JDVal","","number",pParasEx->sCondition.fJD);
#endif
	}

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("返回系数有效","_Coeff","","number",bVal);
		pParasEx->sCondition.bCoeff = bVal;
		pXmlSierialize->xml_serialize("返回系数","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
#else
		pXmlSierialize->xml_serialize(/*"返回系数有效"*/g_sLangTxt_Native_RetCoeffValid.GetString(),"_Coeff","","number",bVal);
		pParasEx->sCondition.bCoeff = bVal;
		pXmlSierialize->xml_serialize(/*"返回系数"*/g_sLangTxt_Native_ReturnCoeff.GetString(),"_CoeffVal","","number",pParasEx->sCondition.fCoeff);
#endif
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		bVal = 0;
		if(pParasEx->sCondition.bCoeff){	bVal = 1;	}
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("返回系数有效","_Coeff","","number",bVal);
		pXmlSierialize->xml_serialize("返回系数","_CoeffVal","","number",pParasEx->sCondition.fCoeff);
#else
		pXmlSierialize->xml_serialize(/*"返回系数有效"*/g_sLangTxt_Native_RetCoeffValid.GetString(),"_Coeff","","number",bVal);
		pXmlSierialize->xml_serialize(/*"返回系数"*/g_sLangTxt_Native_ReturnCoeff.GetString(),"_CoeffVal","","number",pParasEx->sCondition.fCoeff);
#endif
	}

	if (stt_xml_serialize_is_read(pXmlSierialize))
	{
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("判据逻辑","_LogicOrAnd","°","number",bVal);
#else
		pXmlSierialize->xml_serialize(/*"判据逻辑"*/g_sLangTxt_Native_criteria_logic.GetString(),"_LogicOrAnd","°","number",bVal);
#endif
		pParasEx->sCondition.bLogicOr = bVal;
	}
	else if (stt_xml_serialize_is_register(pXmlSierialize))
	{
		bVal = 0;
		if(pParasEx->sCondition.bLogicOr){		bVal = 1;	}
#ifdef NOT_USE_XLANGUAGE
		pXmlSierialize->xml_serialize("判据逻辑","_LogicOrAnd","°","number",bVal);
#else
				pXmlSierialize->xml_serialize(/*"判据逻辑"*/g_sLangTxt_Native_criteria_logic.GetString(),"_LogicOrAnd","°","number",bVal);
#endif
	}
}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_gradient_test.h"
#include"../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_GradientTest()
{
	tmt_GradientTest oGradientTest;
	oGradientTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oGradientTest.m_oGradientParas, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("GradientTestDemo.xml");
//  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_gradient_test_ex *pParas, CSttXmlSerializeBase *pXmlSerialize)
{
//	stt_xml_serialize((PTMT_PARAS_HEAD)pParas, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_ex(&pParas->m_oGradientParasEx, pXmlParas);	//文件的读写
		}
		else if (pParas->m_nSelected)
		{
			stt_xml_serialize_ex(&pParas->m_oGradientParasEx, pXmlParas);	//测试参数下发
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize(&pParas->m_oResultParas, pXmlResults);
		}
		else if (pParas->m_nSelected)
		{
			stt_xml_serialize(&pParas->m_oResultParas, pXmlResults);
		}
	}

	return pXmlParas;
}
