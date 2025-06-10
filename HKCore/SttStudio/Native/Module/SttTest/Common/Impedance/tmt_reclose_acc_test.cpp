#include "stdafx.h"
#include "tmt_reclose_acc_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_RecloseAccParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_RecloseAccParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_RecloseAccParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_RecloseAccParasEx));
	pParas->init();
}

void stt_init_results(tmt_RecloseAccResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_RecloseAccResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_RecloseAccParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.26 caoxc 增加项目名称
	pXmlSierialize->xml_serialize("项目名称","TestName","","number",pParas->m_pszTestName);

	pXmlSierialize->xml_serialize("第一次故障类型","FaultType1","","number",pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("第一次故障电流", "ISet1", "A","number",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize("第一次故障动作时间", "TSet1", "s","number",pParas->m_fTSetting[0]);
	//zhouhj 20220719 考虑到该延时与模拟断路器分合闸时间冲突,且该处延时参数无实际意义删除此节点,原上位机软件将此参数设置为保护动作后保持时间,对于重合闸试验,该参数无意义
//	pXmlSierialize->xml_serialize("第一次故障动作后延时", "TAfterTrig1", "s","number",pParas->m_fTAfterTrig[0]);  
	pXmlSierialize->xml_serialize("第一次故障短路阻抗", "Z1", "V","number",pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize("第一次故障短路阻抗角", "Z1Ph", "°","number",pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize("第二次故障类型","FaultType2","","number",pParas->m_nFaultType[1]);
	pXmlSierialize->xml_serialize("第二次故障电流", "ISet2", "A","number",pParas->m_fSCCurrent[1]);
	pXmlSierialize->xml_serialize("第二次故障动作时间", "TSet2", "s","number",pParas->m_fTSetting[1]);
	//zhouhj 20220719 考虑到该延时与模拟断路器分合闸时间冲突,且该处延时参数无实际意义删除此节点,原上位机软件将此参数设置为保护动作后保持时间,对于重合闸试验,该参数无意义
//	pXmlSierialize->xml_serialize("第二次故障动作后延时", "TAfterTrig2", "s","number",pParas->m_fTAfterTrig[1]);
	pXmlSierialize->xml_serialize("第二次故障短路阻抗", "Z2", "V","number",pParas->m_fImpedance[1]);
	pXmlSierialize->xml_serialize("第二次故障短路阻抗角", "Z2Ph", "°","number",pParas->m_fImpAngle[1]);

	pXmlSierialize->xml_serialize("故障性质","FaultPermanent","","number",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize("额定电压","UNom","","number",pParas->m_fUnom);
    pXmlSierialize->xml_serialize("抽取电压频率","VZFreq","","number",pParas->m_fVzFreq);
#else
	//2022.5.26 caoxc 增加项目名称
	pXmlSierialize->xml_serialize(/* "项目名称" */g_sLangTxt_Native_ProjName.GetString(),"TestName","","number",pParas->m_pszTestName);

	pXmlSierialize->xml_serialize(/* "第一次故障类型" */g_sLangTxt_Native_first_fault_type.GetString(),"FaultType1","","number",pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "第一次故障电流" */g_sLangTxt_Native_first_fault_current.GetString(), "ISet1", "A","number",pParas->m_fSCCurrent[0]);
	pXmlSierialize->xml_serialize(/* "第一次故障动作时间" */g_sLangTxt_Native_first_faultact_time.GetString(), "TSet1", "s","number",pParas->m_fTSetting[0]);
	//zhouhj 20220719 考虑到该延时与模拟断路器分合闸时间冲突,且该处延时参数无实际意义删除此节点,原上位机软件将此参数设置为保护动作后保持时间,对于重合闸试验,该参数无意义
	//	pXmlSierialize->xml_serialize("第一次故障动作后延时", "TAfterTrig1", "s","number",pParas->m_fTAfterTrig[0]);  
	pXmlSierialize->xml_serialize(/* "第一次故障短路阻抗" */g_sLangTxt_Native_first_fault_impedance.GetString(), "Z1", "V","number",pParas->m_fImpedance[0]);
	pXmlSierialize->xml_serialize(/* "第一次故障短路阻抗角" */g_sLangTxt_Native_first_fault_impedance_angle.GetString(), "Z1Ph", "°","number",pParas->m_fImpAngle[0]);

	pXmlSierialize->xml_serialize(/* "第二次故障类型" */g_sLangTxt_Native_second_fault_type.GetString(),"FaultType2","","number",pParas->m_nFaultType[1]);
	pXmlSierialize->xml_serialize(/* "第二次故障电流" */g_sLangTxt_Native_second_fault_current.GetString(), "ISet2", "A","number",pParas->m_fSCCurrent[1]);
	pXmlSierialize->xml_serialize(/* "第二次故障动作时间" */g_sLangTxt_Native_second_faultact_time.GetString(), "TSet2", "s","number",pParas->m_fTSetting[1]);
	//zhouhj 20220719 考虑到该延时与模拟断路器分合闸时间冲突,且该处延时参数无实际意义删除此节点,原上位机软件将此参数设置为保护动作后保持时间,对于重合闸试验,该参数无意义
	//	pXmlSierialize->xml_serialize("第二次故障动作后延时", "TAfterTrig2", "s","number",pParas->m_fTAfterTrig[1]);
	pXmlSierialize->xml_serialize(/* "第二次故障短路阻抗" */g_sLangTxt_Native_second_fault_impedance.GetString(), "Z2", "V","number",pParas->m_fImpedance[1]);
	pXmlSierialize->xml_serialize(/* "第二次故障短路阻抗角" */g_sLangTxt_Native_second_fault_impedance_angle.GetString(), "Z2Ph", "°","number",pParas->m_fImpAngle[1]);

	pXmlSierialize->xml_serialize(/* "故障性质" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","number",pParas->m_nFaultProperty);
	pXmlSierialize->xml_serialize(/* "额定电压" */g_sLangTxt_Report_Vnom.GetString(),"UNom","","number",pParas->m_fUnom);
    pXmlSierialize->xml_serialize("抽取电压频率","VZFreq","","number",pParas->m_fVzFreq);
#endif

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize, false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_ex(tmt_RecloseAccParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("第一次故障短路阻抗(表达式)", "Z1Exp", "","string",pParas->m_pszImpedance[0]);
	pXmlSierialize->xml_serialize("第一次故障短路阻抗角(表达式)", "Z1PhExp", "","string",pParas->m_pszImpAngle[0]);
	pXmlSierialize->xml_serialize("第二次故障短路阻抗(表达式)", "Z2Exp", "","string",pParas->m_pszImpedance[1]);
	pXmlSierialize->xml_serialize("第二次故障短路阻抗角(表达式)", "Z2PhExp", "","string",pParas->m_pszImpAngle[1]);
	pXmlSierialize->xml_serialize("同期电压幅值(表达式)","UxInputMagExp","","string",pParas->m_pszUxInput_Mag);
	pXmlSierialize->xml_serialize("同期电压相位(表达式)","UxInputAngExp","","string",pParas->m_pszUxInput_Ang);
	pXmlSierialize->xml_serialize("阻抗定值(定值)","ImpdanceSetting","","number",pParas->m_fImpdanceSetting);
	pXmlSierialize->xml_serialize("阻抗角(定值)","ImpAngleSetting","","number",pParas->m_fImpAngleSetting);
	pXmlSierialize->xml_serialize("检同期合闸角(定值)","SynAngleSetting","","number",pParas->m_fSynAngleSetting);
	pXmlSierialize->xml_serialize("测试项名称","TestItemName","","string",pParas->m_pszTestItemName);
#else
	pXmlSierialize->xml_serialize(/* "第一次故障短路阻抗(表达式)" */g_sLangTxt_Native_first_fault_impAmp.GetString(), "Z1Exp", "","string",pParas->m_pszImpedance[0]);
	pXmlSierialize->xml_serialize(/* "第一次故障短路阻抗角(表达式)" */g_sLangTxt_Native_first_fault_impAngAmp.GetString(), "Z1PhExp", "","string",pParas->m_pszImpAngle[0]);
	pXmlSierialize->xml_serialize(/* "第二次故障短路阻抗(表达式)" */g_sLangTxt_Native_second_fault_impAmp.GetString(), "Z2Exp", "","string",pParas->m_pszImpedance[1]);
	pXmlSierialize->xml_serialize(/* "第二次故障短路阻抗角(表达式)" */g_sLangTxt_Native_second_fault_impAngAmp.GetString(), "Z2PhExp", "","string",pParas->m_pszImpAngle[1]);
	pXmlSierialize->xml_serialize(/* "同期电压幅值(表达式)" */g_sLangTxt_Native_synchronous_VAmpExp.GetString(),"UxInputMagExp","","string",pParas->m_pszUxInput_Mag);
	pXmlSierialize->xml_serialize(/* "同期电压相位(表达式)" */g_sLangTxt_Native_synchronous_VPhExp.GetString(),"UxInputAngExp","","string",pParas->m_pszUxInput_Ang);
	pXmlSierialize->xml_serialize(/* "阻抗定值(定值)" */g_sLangTxt_Native_impedance_Set.GetString(),"ImpdanceSetting","","number",pParas->m_fImpdanceSetting);
	pXmlSierialize->xml_serialize(/* "阻抗角(定值)" */g_sLangTxt_Native_ImpedanceAnglesSet.GetString(),"ImpAngleSetting","","number",pParas->m_fImpAngleSetting);
	pXmlSierialize->xml_serialize(/* "检同期合闸角(定值)" */g_sLangTxt_Native_Syn_closure_AngSet.GetString(),"SynAngleSetting","","number",pParas->m_fSynAngleSetting);
	pXmlSierialize->xml_serialize(/* "测试项名称" */g_sLangTxt_Native_test_item_name.GetString(),"TestItemName","","string",pParas->m_pszTestItemName);
#endif

	stt_xml_serialize(pParas,pXmlSierialize);
}

void stt_xml_serialize_pnv(tmt_RecloseAccParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize(pParas,pXmlSierialize);
    pXmlSierialize->xml_serialize("故障前开出","_State1BOut","","number",pParas->m_nState1BOut);
    pXmlSierialize->xml_serialize("故障态开出","_State2BOut","","number",pParas->m_nState2BOut);
    pXmlSierialize->xml_serialize("重合闸开出","_State3BOut","","number",pParas->m_nState3BOut);
    pXmlSierialize->xml_serialize("后加速开出","_State4BOut","","number",pParas->m_nState4BOut);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize(tmt_RecloseAccResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
}


CSttXmlSerializeBase* stt_xml_serialize(tmt_RecloseAccTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	//stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_ex(&(pTests->m_oRecloseAccParas),  pXmlParas);	//文件的读写
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize_ex(&(pTests->m_oRecloseAccParas),  pXmlParas);	//测试参数下发
		}
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize(&pTests->m_oRecloseAccResults,  pXmlResults);
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize(&pTests->m_oRecloseAccResults,  pXmlResults);
		}
	}

	return pXmlParas;
}
CSttXmlSerializeBase* stt_xml_serialize(tmt_RecloseAccPnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    //stt_xml_serialize((PTMT_PARAS_HEAD)pTests, pXmlSerialize);

    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize_pnv(&(pTests->m_oRecloseAccParas),  pXmlParas);	//文件的读写
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize_pnv(&(pTests->m_oRecloseAccParas),  pXmlParas);	//测试参数下发
        }
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize(&pTests->m_oRecloseAccResults,  pXmlResults);
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize(&pTests->m_oRecloseAccResults,  pXmlResults);
        }
    }

    return pXmlParas;
}
