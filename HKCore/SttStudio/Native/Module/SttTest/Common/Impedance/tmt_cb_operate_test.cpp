#include "stdafx.h"
#include "tmt_cb_operate_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_CBOperateParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_CBOperateParas));
	pParas->init();
}

void stt_init_results(tmt_CBOperateResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_CBOperateResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_CBOperateParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("系统计算模型(0-电流不变 1-电压不变 2-系统阻抗不变)","CalcuMode","","UIZCalMode",pParas->m_nCalMode);
	pXmlSierialize->xml_serialize("系统电源阻抗","Zs_Mag","Ω","number",pParas->m_fZs);
	pXmlSierialize->xml_serialize("系统电源阻抗角","Zs_Ang","°","number",pParas->m_fPhis);

	pXmlSierialize->xml_serialize("故障类型","FaultType1","","number",pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("短路电流", "ISet1", "A","number",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("短路电压", "VSet1", "V","number",pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize("短路阻抗", "Z1", "V","number",pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize("短路阻抗角", "Z1Ph", "°","number",pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("故障性质","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);

	pXmlSierialize->xml_serialize("最大故障时间", "TSet1", "s","number",pParas->m_fMaxFaultTime);
//	pXmlSierialize->xml_serialize("动作后延时", "TAfterTrig1", "s","number",pParas->m_fTAfterTrig[0]);

	pXmlSierialize->xml_serialize("是否转换性故障","_FaultTrans","","BOOL",pParas->m_bTransFault);
	pXmlSierialize->xml_serialize("故障转换时间", "FaultTransT", "s", "number",  pParas->m_fTransTime);

	pXmlSierialize->xml_serialize("转换故障类型","FaultType2","","number",pParas->m_nFaultType[1]);
	pXmlSierialize->xml_serialize("转换故障短路阻抗", "Z2", "V","number",pParas->m_fImpedance[1]);
	pXmlSierialize->xml_serialize("转换故障短路阻抗角", "Z2Ph", "°","number",pParas->m_fImpAngle[1]);
	pXmlSierialize->xml_serialize("转换故障短路电流", "ISet2", "A","number",pParas->m_fSCCurrent[1]);
	pXmlSierialize->xml_serialize("转换故障短路电压", "VSet2", "V","number",pParas->m_fSCVoltage[1]);
	pXmlSierialize->xml_serialize("转换故障故障方向", "FaultDirection2", "", "FaultDirection", pParas->m_nFaultDir[1]);

	pXmlSierialize->xml_serialize("动作时间误差判断","Ttrip_Check","","long",pParas->m_nTtripCheck);
	pXmlSierialize->xml_serialize("重合闸动作时间误差判断", "TtripD_Check", "","long",pParas->m_nTtripDCheck);
	pXmlSierialize->xml_serialize("后加速动作时间误差判断", "TtripAcc_Check", "","long",pParas->m_nTtripAccCheck);
	pXmlSierialize->xml_serialize("动作时间绝对误差限(s)","Ttrip_AbsErr","","number",pParas->m_fTtripAbsErr);
	pXmlSierialize->xml_serialize("动作时间相对误差限(%)", "Ttrip_RelErr", "","number",pParas->m_fTtripRelErr);
	pXmlSierialize->xml_serialize("动作时间整定值(s)", "TSetting", "","number",pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("重合闸动作时间绝对误差限(s)", "TtripD_AbsErr", "","number",pParas->m_fTtripDAbsErr);
	pXmlSierialize->xml_serialize("重合闸动作时间相对误差限(%)", "TtripD_RelErr", "","number",pParas->m_fTtripDRelErr);
	pXmlSierialize->xml_serialize("重合闸动作时间整定值(s)", "DTSetting", "", "number", pParas->m_fDTSetting);
	pXmlSierialize->xml_serialize("后加速动作时间绝对误差限(s)", "TtripAcc_AbsErr", "","number",pParas->m_fTtripAccAbsErr);
	pXmlSierialize->xml_serialize("后加速动作时间相对误差限(%)", "TtripAcc_RelErr", "","number",pParas->m_fTtripAccRelErr);
	pXmlSierialize->xml_serialize("后加速动作时间整定值(s)", "AccTSetting", "", "number", pParas->m_fAccTSetting);
	pXmlSierialize->xml_serialize("动作时间误差逻辑判断","Ttrip_ErrorLogic","","long",pParas->m_nTtripErrorLogic);
	pXmlSierialize->xml_serialize("重合闸动作时间误差逻辑判断", "TtripD_ErrorLogic", "","long",pParas->m_nTtripDErrorLogic);
	pXmlSierialize->xml_serialize("后加速动作时间误差逻辑判断", "TtripAcc_ErrorLogic", "","long",pParas->m_nTtripAccErrorLogic);

	pXmlSierialize->xml_serialize("试验过程","TestProcess","","PsuTestProcCtrl",pParas->m_nTestProcCtrlMode);
	// 以下参数当m_nTestProcCtrlMode==时间控制时有效
	pXmlSierialize->xml_serialize("重合方式","RecloseMode","","PsuRecloseMode",pParas->m_nRecloseMode);
//	pXmlSierialize->xml_serialize("开关跳开后持续时间","AfterRecloseTime","s","number",pParas->m_fTAfterReclose);
	pXmlSierialize->xml_serialize("重合持续时间","RecloseTime","s","set",pParas->m_fRecloseTime);
	pXmlSierialize->xml_serialize("保护动作后持续时间","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
	pXmlSierialize->xml_serialize("后加速开关跳开后持续时间", "TAfterAccTrig", "s","number",pParas->m_fTAfterAccTrig);

	if(stt_xml_serialize_is_read(pXmlSierialize))//20230505 读取做兼容处理PsuVm
	{
		pXmlSierialize->xml_serialize("系统计算模型(0-电流不变 1-电压不变 2-系统阻抗不变)","CalMode","","UIZCalMode",pParas->m_nCalMode);
		pXmlSierialize->xml_serialize("后加速开关跳开后持续时间", "AfterAccTime", "s","number",pParas->m_fTAfterAccTrig);
		pXmlSierialize->xml_serialize("额定电压","Unom","V","number",pParas->m_fUnom);

		pXmlSierialize->xml_serialize("系统电源阻抗","Zs","Ω","number",pParas->m_fZs);
		pXmlSierialize->xml_serialize("系统电源阻抗角","ZsPh","°","number",pParas->m_fPhis);
	}
#else
	pXmlSierialize->xml_serialize(/* "系统计算模型(0-电流不变 1-电压不变 2-系统阻抗不变)" */g_sLangTxt_Native_syscomputModel012.GetString(),"CalcuMode","","UIZCalMode",pParas->m_nCalMode);
	pXmlSierialize->xml_serialize(/* "系统电源阻抗" */g_sLangTxt_Native_syspowerImp.GetString(),"Zs_Mag","Ω","number",pParas->m_fZs);
	pXmlSierialize->xml_serialize(/* "系统电源阻抗角" */g_sLangTxt_Native_syspowerImpangle.GetString(),"Zs_Ang","°","number",pParas->m_fPhis);


	pXmlSierialize->xml_serialize("动作时间误差判断","Ttrip_Check","","long",pParas->m_nTtripCheck);
	pXmlSierialize->xml_serialize("重合闸动作时间误差判断", "TtripD_Check", "","long",pParas->m_nTtripDCheck);
	pXmlSierialize->xml_serialize("后加速动作时间误差判断", "TtripAcc_Check", "","long",pParas->m_nTtripAccCheck);
	pXmlSierialize->xml_serialize("动作时间绝对误差限(s)","Ttrip_AbsErr","","number",pParas->m_fTtripAbsErr);
	pXmlSierialize->xml_serialize("动作时间相对误差限(%)", "Ttrip_RelErr", "","number",pParas->m_fTtripRelErr);
	pXmlSierialize->xml_serialize("动作时间整定值(s)", "TSetting", "","number",pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("重合闸动作时间绝对误差限(s)", "TtripD_AbsErr", "","number",pParas->m_fTtripDAbsErr);
	pXmlSierialize->xml_serialize("重合闸动作时间相对误差限(%)", "TtripD_RelErr", "","number",pParas->m_fTtripDRelErr);
	pXmlSierialize->xml_serialize("重合闸动作时间整定值(s)", "DTSetting", "", "number", pParas->m_fDTSetting);
	pXmlSierialize->xml_serialize("后加速动作时间绝对误差限(s)", "TtripAcc_AbsErr", "","number",pParas->m_fTtripAccAbsErr);
	pXmlSierialize->xml_serialize("后加速动作时间相对误差限(%)", "TtripAcc_RelErr", "","number",pParas->m_fTtripAccRelErr);
	pXmlSierialize->xml_serialize("后加速动作时间整定值(s)", "AccTSetting", "", "number", pParas->m_fAccTSetting);
	pXmlSierialize->xml_serialize("动作时间误差逻辑判断","Ttrip_ErrorLogic","","long",pParas->m_nTtripErrorLogic);
	pXmlSierialize->xml_serialize("重合闸动作时间误差逻辑判断", "TtripD_ErrorLogic", "","long",pParas->m_nTtripDErrorLogic);
	pXmlSierialize->xml_serialize("后加速动作时间误差逻辑判断", "TtripAcc_ErrorLogic", "","long",pParas->m_nTtripAccErrorLogic);

	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(),"FaultType1","","number",pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "短路电流" */g_sLangTxt_Native_ShortCircuit.GetString(), "ISet1", "A","number",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "短路电压" */g_sLangTxt_Native_ShortCircuitV.GetString(), "VSet1", "V","number",pParas->m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize(/* "短路阻抗" */g_sLangTxt_Native_ShortZImp.GetString(), "Z1", "V","number",pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize(/* "短路阻抗角" */g_sLangTxt_Native_ShortZImpAng.GetString(), "Z1Ph", "°","number",pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize(/* "故障方向" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "故障性质" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);

	pXmlSierialize->xml_serialize(/* "最大故障时间" */g_sLangTxt_Native_MaxTimeMalf.GetString(), "TSet1", "s","number",pParas->m_fMaxFaultTime);
	//	pXmlSierialize->xml_serialize("动作后延时", "TAfterTrig1", "s","number",pParas->m_fTAfterTrig[0]);

	pXmlSierialize->xml_serialize(/* "是否转换性故障" */g_sLangTxt_Native_TransientFault.GetString(),"_FaultTrans","","BOOL",pParas->m_bTransFault);
	pXmlSierialize->xml_serialize(/* "故障转换时间" */g_sLangTxt_Native_fault_switchtime.GetString(), "FaultTransT", "s", "number",  pParas->m_fTransTime);

	pXmlSierialize->xml_serialize(/* "转换故障类型" */g_sLangTxt_Native_switchErrtype.GetString(),"FaultType2","","number",pParas->m_nFaultType[1]);
	pXmlSierialize->xml_serialize(/* "转换故障短路阻抗" */g_sLangTxt_Native_switchErr_shortImp.GetString(), "Z2", "V","number",pParas->m_fImpedance[1]);
	pXmlSierialize->xml_serialize(/* "转换故障短路阻抗角" */g_sLangTxt_Native_switchErr_shortImpAng.GetString(), "Z2Ph", "°","number",pParas->m_fImpAngle[1]);
	pXmlSierialize->xml_serialize(/* "转换故障短路电流" */g_sLangTxt_Native_switchErr_shortI.GetString(), "ISet2", "A","number",pParas->m_fSCCurrent[1]);
	pXmlSierialize->xml_serialize(/* "转换故障短路电压" */g_sLangTxt_Native_switchErr_shortV.GetString(), "VSet2", "V","number",pParas->m_fSCVoltage[1]);
	pXmlSierialize->xml_serialize(/* "转换故障故障方向" */g_sLangTxt_Native_switchErr_direction.GetString(), "FaultDirection2", "", "FaultDirection", pParas->m_nFaultDir[1]);

	pXmlSierialize->xml_serialize(/* "试验过程" */g_sLangTxt_Native_test_process.GetString(),"TestProcess","","PsuTestProcCtrl",pParas->m_nTestProcCtrlMode);
	// 以下参数当m_nTestProcCtrlMode==时间控制时有效
	pXmlSierialize->xml_serialize(/* "重合方式" */g_sLangTxt_Native_redundancy_mode.GetString(),"RecloseMode","","PsuRecloseMode",pParas->m_nRecloseMode);
	//	pXmlSierialize->xml_serialize("开关跳开后持续时间","AfterRecloseTime","s","number",pParas->m_fTAfterReclose);
	pXmlSierialize->xml_serialize(/* "重合持续时间" */g_sLangTxt_Native_redundancy_duration.GetString(),"RecloseTime","s","set",pParas->m_fRecloseTime);
	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
	pXmlSierialize->xml_serialize(/* "后加速开关跳开后持续时间" */g_sLangTxt_Native_postswitch_duration.GetString(), "TAfterAccTrig", "s","number",pParas->m_fTAfterAccTrig);

	if(stt_xml_serialize_is_read(pXmlSierialize))//20230505 读取做兼容处理PsuVm
	{
		pXmlSierialize->xml_serialize(/* "系统计算模型(0-电流不变 1-电压不变 2-系统阻抗不变)" */g_sLangTxt_Native_syscomputModel012.GetString(),"CalMode","","UIZCalMode",pParas->m_nCalMode);
		pXmlSierialize->xml_serialize(/* "后加速开关跳开后持续时间" */g_sLangTxt_Native_postswitch_duration.GetString(), "AfterAccTime", "s","number",pParas->m_fTAfterAccTrig);
		pXmlSierialize->xml_serialize(/* "额定电压" */g_sLangTxt_Report_Vnom.GetString(),"Unom","V","number",pParas->m_fUnom);

		pXmlSierialize->xml_serialize(/* "系统电源阻抗" */g_sLangTxt_Native_syspowerImp.GetString(),"Zs","Ω","number",pParas->m_fZs);
		pXmlSierialize->xml_serialize(/* "系统电源阻抗角" */g_sLangTxt_Native_syspowerImpangle.GetString(),"ZsPh","°","number",pParas->m_fPhis);
	}
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,true);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_CBOperateResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_CBOperateTest *pTests, CSttXmlSerializeBase *pXmlSerialize, long nVolRsNum, long nCurRsNum)
{
	//stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);//mym 2021-7-26 zhuxiao掉;因为前面已经串行化过了，所以这里注销掉;

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize(&(pTests->m_oCBOperateParas),  pXmlParas);	//文件的读写
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize(&(pTests->m_oCBOperateParas),  pXmlParas);	//测试参数下发
		}
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize(&pTests->m_oCBOperateResults,  pXmlResults);
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize(&pTests->m_oCBOperateResults,  pXmlResults);
		}
	}

	return pXmlParas;
}
