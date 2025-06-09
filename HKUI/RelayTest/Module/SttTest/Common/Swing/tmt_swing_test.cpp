#include "stdafx.h"
#include "tmt_swing_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_SwingParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_SwingParas));
	pParas->init();
}

void stt_init_results(tmt_SwingResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_SwingResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_SwingParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE

	pXmlSierialize->xml_serialize("功角始值", "PAngleStart", "°", "number", pParas->m_fPowerAngleBegin);
	pXmlSierialize->xml_serialize("功角终值", "PAngleEnd", "°", "number", pParas->m_fPowerAngleEnd);
	pXmlSierialize->xml_serialize("振荡周期", "SwingCycle", "s", "number", pParas->m_fCycle);//？？？
	pXmlSierialize->xml_serialize("振荡次数", "SwingCount", "", "number", pParas->m_nSwingCount);//？？？
	pXmlSierialize->xml_serialize("|Em|/|En|", "EmEnRate", "", "number", pParas->m_fRate);
	pXmlSierialize->xml_serialize("跳闸接入点", "TripPoint", "", "PsuTripBin", pParas->m_nTripPoint);//？？？
	pXmlSierialize->xml_serialize("加速信号接点", "TripSpeedUp", "", "PsuTripBin", pParas->m_nTripSpeedUp);//？？？
	pXmlSierialize->xml_serialize("减速信号接点", "TripSpeedDown", "", "PsuTripBin", pParas->m_nTripSpeedDown);//？？？
	pXmlSierialize->xml_serialize("是否往复振荡","bReciprocating","","BOOL",pParas->m_bReciprocating);
	pXmlSierialize->xml_serialize("速度变化选择","AccelerateSlct","","PsuAccelerateSlct",pParas->m_nAccelerate);
	pXmlSierialize->xml_serialize("是否变阻抗","bDzdt","","BOOL",pParas->m_bDzdt);//？？？
	pXmlSierialize->xml_serialize("阻抗变化率", "Dzdt", "Ω/s", "number", pParas->m_fDzdt);//？？？

	pXmlSierialize->xml_serialize("是否转换性故障","_FaultTrans","","BOOL",pParas->m_bTransFault);
	pXmlSierialize->xml_serialize("故障类型", "FaultType1", "", "SystemFault", pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("短路阻抗", "Z1", "Ω", "number", pParas->m_fImpedance);
	pXmlSierialize->xml_serialize("短路电流", "ISet1", "A", "set", pParas->m_fSCurrent);
	pXmlSierialize->xml_serialize("故障时间", "FaultTime", "s", "set", pParas->m_fFaultTime);//？？？
	pXmlSierialize->xml_serialize("零序补偿系数计算方式","K0Mode","无","ZeroCalModePnv",pParas->m_nK0CalMode);
	pXmlSierialize->xml_serialize("零序补偿系数(|K0|$KR$|Z0/Z1|)","KlKr","","set",pParas->m_fK0Amp);
	pXmlSierialize->xml_serialize("零序补偿系数(Phi(K0)$KX$Phi(Z0/Z1))","AngKx","","set",pParas->m_fK0Angle);

	pXmlSierialize->xml_serialize("振荡前时间","PreFaultTime","s","number",pParas->m_fPreFaultTime);//？？？
	pXmlSierialize->xml_serialize("CT正极性","CTPos","","CTPosPnv",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize("系统侧阻抗","ImpSys","Ω","number",pParas->m_fImpSys);
	pXmlSierialize->xml_serialize("系统侧阻抗角","ImpSysPh","°","number",pParas->m_fImpSysPh);
	pXmlSierialize->xml_serialize("变压器阻抗","ImpTf","Ω","number",pParas->m_fImpTf);
	pXmlSierialize->xml_serialize("变压器阻抗角","ImpTfPh","°","number",pParas->m_fImpTfPh);
	pXmlSierialize->xml_serialize("发电机暂态阻抗","ImpTs","Ω","number",pParas->m_fImpTs);
	pXmlSierialize->xml_serialize("动作时间定值","TimeActSetting","s","number",pParas->m_fActTimeSet);


// 	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
//  	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize,nBinExNum);
 	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
		pXmlSierialize->xml_serialize("开出1状态","_B01","","DOutputState",pParas->m_binOut[0].nState);
		pXmlSierialize->xml_serialize("开出2状态","_B02","","DOutputState",pParas->m_binOut[1].nState);
		pXmlSierialize->xml_serialize("开出3状态","_B03","","DOutputState",pParas->m_binOut[2].nState);
		pXmlSierialize->xml_serialize("开出4状态","_B04","","DOutputState",pParas->m_binOut[3].nState);
		pXmlSierialize->xml_serialize("开出5状态","_B05","","DOutputState",pParas->m_binOut[4].nState);
		pXmlSierialize->xml_serialize("开出6状态","_B06","","DOutputState",pParas->m_binOut[5].nState);
		pXmlSierialize->xml_serialize("开出7状态","_B07","","DOutputState",pParas->m_binOut[6].nState);
		pXmlSierialize->xml_serialize("开出8状态","_B08","","DOutputState",pParas->m_binOut[7].nState);

        stt_xml_serialize(&pParas->m_oGoosePub[0],pXmlSierialize);
	}
#else
	pXmlSierialize->xml_serialize(/* "功角始值" */g_sLangTxt_Native_AngleStartPar1.GetString(), "PAngleStart", "°", "number", pParas->m_fPowerAngleBegin);
	pXmlSierialize->xml_serialize(/* "功角终值" */g_sLangTxt_Native_AngleEndPar1.GetString(), "PAngleEnd", "°", "number", pParas->m_fPowerAngleEnd);
	pXmlSierialize->xml_serialize(/* "振荡周期" */g_sLangTxt_Native_OscilPeriod1.GetString(), "SwingCycle", "s", "number", pParas->m_fCycle);//？？？
	pXmlSierialize->xml_serialize(/* "振荡次数" */g_sLangTxt_Native_OscilCount.GetString(), "SwingCount", "", "number", pParas->m_nSwingCount);//？？？
	pXmlSierialize->xml_serialize("|Em|/|En|", "EmEnRate", "", "number", pParas->m_fRate);
	pXmlSierialize->xml_serialize(/* "跳闸接入点" */g_sLangTxt_Native_TripAccessPoint.GetString(), "TripPoint", "", "PsuTripBin", pParas->m_nTripPoint);//？？？
	pXmlSierialize->xml_serialize(/* "加速信号接点" */g_sLangTxt_Native_AccelSignalCont.GetString(), "TripSpeedUp", "", "PsuTripBin", pParas->m_nTripSpeedUp);//？？？
	pXmlSierialize->xml_serialize(/* "减速信号接点" */g_sLangTxt_Native_DecelSignalCont.GetString(), "TripSpeedDown", "", "PsuTripBin", pParas->m_nTripSpeedDown);//？？？
	pXmlSierialize->xml_serialize(/* "是否往复振荡" */g_sLangTxt_Native_ReOscillat_ornot.GetString(),"bReciprocating","","BOOL",pParas->m_bReciprocating);
	pXmlSierialize->xml_serialize(/* "速度变化选择" */g_sLangTxt_Native_SpeedChange.GetString(),"AccelerateSlct","","PsuAccelerateSlct",pParas->m_nAccelerate);
	pXmlSierialize->xml_serialize(/* "是否变阻抗" */g_sLangTxt_Native_ImpedanceChange_ornot.GetString(),"bDzdt","","BOOL",pParas->m_bDzdt);//？？？
	pXmlSierialize->xml_serialize(/* "阻抗变化率" */g_sLangTxt_Native_ImpedanceRateChange.GetString(), "Dzdt", "Ω/s", "number", pParas->m_fDzdt);//？？？

	pXmlSierialize->xml_serialize(/* "是否转换性故障" */g_sLangTxt_Native_TransientFault.GetString(),"_FaultTrans","","BOOL",pParas->m_bTransFault);
	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType1", "", "SystemFault", pParas->m_nFaultType);
	pXmlSierialize->xml_serialize(/* "短路阻抗" */g_sLangTxt_Native_ShortZImp.GetString(), "Z1", "Ω", "number", pParas->m_fImpedance);
	pXmlSierialize->xml_serialize(/* "短路电流" */g_sLangTxt_Native_FaultCurrValue.GetString(), "ISet1", "A", "set", pParas->m_fSCurrent);
	pXmlSierialize->xml_serialize(/* "故障时间" */g_sLangTxt_Gradient_Time.GetString(), "FaultTime", "s", "set", pParas->m_fFaultTime);//？？？
	pXmlSierialize->xml_serialize(/* "零序补偿系数计算方式" */g_sLangTxt_Native_zeroseq_comp_calculat1.GetString(),"K0Mode",/* "无" */g_sLangTxt_None.GetString(),"ZeroCalModePnv",pParas->m_nK0CalMode);
	pXmlSierialize->xml_serialize(/* "零序补偿系数(|K0|$KR$|Z0/Z1|)" */g_sLangTxt_Native_ZeroSeqComp1.GetString(),"KlKr","","set",pParas->m_fK0Amp);
	pXmlSierialize->xml_serialize(/* "零序补偿系数(Phi(K0)$KX$Phi(Z0/Z1))" */g_sLangTxt_Native_ZeroSeqComp2.GetString(),"AngKx","","set",pParas->m_fK0Angle);

	pXmlSierialize->xml_serialize(/* "振荡前时间" */g_sLangTxt_Native_PreOscTime.GetString(),"PreFaultTime","s","number",pParas->m_fPreFaultTime);//？？？
	pXmlSierialize->xml_serialize(/* "CT正极性" */g_sLangTxt_Native_CTPolarityPositive.GetString(),"CTPos","","CTPosPnv",pParas->m_nCTPoint);
	pXmlSierialize->xml_serialize(/* "系统侧阻抗" */g_sLangTxt_Native_SysImp.GetString(),"ImpSys","Ω","number",pParas->m_fImpSys);
	pXmlSierialize->xml_serialize(/* "系统侧阻抗角" */g_sLangTxt_Native_SysImpedAngle.GetString(),"ImpSysPh","°","number",pParas->m_fImpSysPh);
	pXmlSierialize->xml_serialize(/* "变压器阻抗" */g_sLangTxt_Native_TransImp.GetString(),"ImpTf","Ω","number",pParas->m_fImpTf);
	pXmlSierialize->xml_serialize(/* "变压器阻抗角" */g_sLangTxt_Native_TransImpedAngle.GetString(),"ImpTfPh","°","number",pParas->m_fImpTfPh);
	pXmlSierialize->xml_serialize(/* "发电机暂态阻抗" */g_sLangTxt_Native_GeneTransImped.GetString(),"ImpTs","Ω","number",pParas->m_fImpTs);
	pXmlSierialize->xml_serialize(/* "动作时间定值" */g_sLangTxt_Native_OpTimeSet.GetString(),"TimeActSetting","s","number",pParas->m_fActTimeSet);

	pXmlSierialize->xml_serialize(/* "误差类型" */g_sLangTxt_StateEstimate_ErrorType.GetString(),"Ttrip_ErrorLogic","","number",pParas->m_nTtripErrorLogic);//？？？
	pXmlSierialize->xml_serialize(/* "相对误差" */g_sLangTxt_StateEstimate_RelError.GetString(),"Ttrip_RelErr","","float",pParas->m_fTtripRelErr);
	pXmlSierialize->xml_serialize(/* "绝对误差" */g_sLangTxt_StateEstimate_AbsError.GetString(),"Ttrip_AbsErr","","float",pParas->m_fTtripAbsErr);
    pXmlSierialize->xml_serialize(/* "绝对误差(-)" */g_sLangTxt_StateEstimate_AbsError_Neg.GetString(),"Ttrip_AbsErr_Neg","","float",pParas->m_fTtripAbsErr_Neg);

// 	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
//  	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize,nBinExNum);
 	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Gradient_Exbinary_out(pParas->m_binOutEx,pXmlSierialize,FALSE);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
		pXmlSierialize->xml_serialize(/* "开出1状态" */g_sLangTxt_Out1_Situation.GetString(),"_B01","","DOutputState",pParas->m_binOut[0].nState);
		pXmlSierialize->xml_serialize(/* "开出2状态" */g_sLangTxt_Out2_Situation.GetString(),"_B02","","DOutputState",pParas->m_binOut[1].nState);
		pXmlSierialize->xml_serialize(/* "开出3状态" */g_sLangTxt_Out3_Situation.GetString(),"_B03","","DOutputState",pParas->m_binOut[2].nState);
		pXmlSierialize->xml_serialize(/* "开出4状态" */g_sLangTxt_Out4_Situation.GetString(),"_B04","","DOutputState",pParas->m_binOut[3].nState);
		pXmlSierialize->xml_serialize(/* "开出5状态" */g_sLangTxt_Out5_Situation.GetString(),"_B05","","DOutputState",pParas->m_binOut[4].nState);
		pXmlSierialize->xml_serialize(/* "开出6状态" */g_sLangTxt_Out6_Situation.GetString(),"_B06","","DOutputState",pParas->m_binOut[5].nState);
		pXmlSierialize->xml_serialize(/* "开出7状态" */g_sLangTxt_Out7_Situation.GetString(),"_B07","","DOutputState",pParas->m_binOut[6].nState);
		pXmlSierialize->xml_serialize(/* "开出8状态" */g_sLangTxt_Out8_Situation.GetString(),"_B08","","DOutputState",pParas->m_binOut[7].nState);

        stt_xml_serialize(&pParas->m_oGoosePub[0],pXmlSierialize);
	}
#endif
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_SwingResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("保护出口时间", "TripTime", "", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("加速信号出口时间", "SpeedUp", "", "number",pResults->m_fSpeedUp);
	pXmlSierialize->xml_serialize("减速信号出口时间", "SpeedDown", "", "number",pResults->m_fSpeedDown);
	pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pResults->m_nAct);
#else
	pXmlSierialize->xml_serialize(/* "保护出口时间" */g_sLangTxt_Native_ProtRelayTime1.GetString(), "TripTime", "", "number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize(/* "加速信号出口时间" */g_sLangTxt_Native_AccelSigOutTime1.GetString(), "SpeedUp", "", "number",pResults->m_fSpeedUp);
	pXmlSierialize->xml_serialize(/* "减速信号出口时间" */g_sLangTxt_Native_DecelSigOutTime1.GetString(), "SpeedDown", "", "number",pResults->m_fSpeedDown);
	pXmlSierialize->xml_serialize(/* "动作描述" */g_sLangTxt_Native_ActionDesc.GetString(),"ActDsec","","number",pResults->m_nAct);
#endif

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_SwingTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

 	if (pXmlParas != NULL)
 	{
		stt_xml_serialize(&(pTests->m_oSwingParas), pXmlParas);
 	}
 
 	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());
 
 	if (pXmlResults != NULL)
 	{
		stt_xml_serialize(&pTests->m_oSwingResults,  pXmlResults);
 	}

	return pXmlParas;
}
