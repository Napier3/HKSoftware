#include "stdafx.h"
#include "tmt_distance_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_DistanceParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DistanceParas));
	pParas->init();
}

void stt_init_paras(tmt_DistanceParas_I *pParas)
{
    memset(&pParas, 0, sizeof(tmt_DistanceParas_I));
    pParas->init();
}

void stt_init_paras_ex(tmt_DistanceParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DistanceParasEx));
	pParas->init();
}

void stt_init_results(tmt_DistanceResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DistanceResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_DistanceParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	//2022.5.25 caoxc 增加项目名称和分组id
	pXmlSierialize->xml_serialize("项目名称", "TestName", "无", "string",  pParas->m_pszTestName);
	pXmlSierialize->xml_serialize("分组", "GroupID", "无", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize("故障类型", "FaultType", "无", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize("阻抗定值", "ZSetting", "Ω", "set", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize("阻抗角", "ZAng", "°", "set", pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize("倍数", "Rate", "无", "number",pParas->m_fRate[0]);

	pXmlSierialize->xml_serialize("整定动作时间", "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize("短路电流", "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
//	pXmlSierialize->xml_serialize("短路电压", "FaultVf", "V", "number", pParas->m_oImpedance.m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize("故障方向", "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize("故障性质","FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);

	pXmlSierialize->xml_serialize("保护动作后持续时间","TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);
    pXmlSierialize->xml_serialize("额定电压","UNom","V","number",pParas->m_fUNom);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
		pXmlSierialize->xml_serialize("保护动作后持续时间","PostFaultTime","s","number",pParas->m_fPostFaultTime);
	}

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	//整定值
	pXmlSierialize->xml_serialize("接地距离I段定值","Zeset1","Ω","float",pParas->m_fSettingLN[0]);
	pXmlSierialize->xml_serialize("接地距离II段定值","Zeset2","Ω","float",pParas->m_fSettingLN[1]);
	pXmlSierialize->xml_serialize("接地距离III段定值","Zeset3","Ω","float",pParas->m_fSettingLN[2]);
	pXmlSierialize->xml_serialize("接地距离IV段定值","Zeset4","Ω","float",pParas->m_fSettingLN[3]);
	pXmlSierialize->xml_serialize("接地距离V段定值","Zeset5","Ω","float",pParas->m_fSettingLN[4]);

	pXmlSierialize->xml_serialize("接地距离I段时间","Teset1","s","float",pParas->m_fTSettingLN[0]);
	pXmlSierialize->xml_serialize("接地距离II段时间","Teset2","s","float",pParas->m_fTSettingLN[1]);
	pXmlSierialize->xml_serialize("接地距离III段时间","Teset3","s","float",pParas->m_fTSettingLN[2]);
	pXmlSierialize->xml_serialize("接地距离IV段时间","Teset4","s","float",pParas->m_fTSettingLN[3]);
	pXmlSierialize->xml_serialize("接地距离V段时间","Teset5","s","float",pParas->m_fTSettingLN[4]);

	pXmlSierialize->xml_serialize("相间距离I段定值","Zxset1","Ω","float",pParas->m_fSettingLL[0]);
	pXmlSierialize->xml_serialize("相间距离II段定值","Zxset2","Ω","float",pParas->m_fSettingLL[1]);
	pXmlSierialize->xml_serialize("相间距离III段定值","Zxset3","Ω","float",pParas->m_fSettingLL[2]);
	pXmlSierialize->xml_serialize("相间距离IV段定值","Zxset4","Ω","float",pParas->m_fSettingLL[3]);
	pXmlSierialize->xml_serialize("相间距离V段定值","Zxset5","Ω","float",pParas->m_fSettingLL[4]);

	pXmlSierialize->xml_serialize("相间距离I段时间","Txset1","s","float",pParas->m_fTSettingLL[0]);
	pXmlSierialize->xml_serialize("相间距离II段时间","Txset2","s","float",pParas->m_fTSettingLL[1]);
	pXmlSierialize->xml_serialize("相间距离III段时间","Txset3","s","float",pParas->m_fTSettingLL[2]);
	pXmlSierialize->xml_serialize("相间距离IV段时间","Txset4","s","float",pParas->m_fTSettingLL[3]);
	pXmlSierialize->xml_serialize("相间距离V段时间","Txset5","s","float",pParas->m_fTSettingLL[4]);
#else
	//2022.5.25 caoxc 增加项目名称和分组id
	pXmlSierialize->xml_serialize(/* "项目名称" */g_sLangTxt_Native_ProjName.GetString(), "TestName", "无", "string",  pParas->m_pszTestName);
	pXmlSierialize->xml_serialize(/* "分组" */g_sLangTxt_Native_Grouping.GetString(), "GroupID", "无", "string",  pParas->m_pszGroupID);

	pXmlSierialize->xml_serialize(/* "故障类型" */g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "无", "SystemFault",  pParas->m_nFaultType[0]);
	pXmlSierialize->xml_serialize(/* "阻抗定值" */g_sLangTxt_Native_impedance_setting.GetString(), "ZSetting", "Ω", "set", pParas->m_fSetting[0]);
	pXmlSierialize->xml_serialize(/* "阻抗角" */g_sLangTxt_Native_ImpedanceAngles.GetString(), "ZAng", "°", "set", pParas->m_fImpAngle[0]);
	pXmlSierialize->xml_serialize(/* "倍数" */g_sLangTxt_Native_Multiple.GetString(), "Rate", "无", "number",pParas->m_fRate[0]);

	pXmlSierialize->xml_serialize(/* "整定动作时间" */g_sLangTxt_Adjustment_Time.GetString(), "TSetting", "s", "set", pParas->m_fTSetting);
	pXmlSierialize->xml_serialize(/* "短路电流" */g_sLangTxt_Native_ShortCircuit.GetString(), "FaultIf", "A", "number", pParas->m_fSCCurrent[0]);
	//	pXmlSierialize->xml_serialize("短路电压", "FaultVf", "V", "number", pParas->m_oImpedance.m_fSCVoltage[0]);
	pXmlSierialize->xml_serialize(/* "故障方向" */g_sLangTxt_Gradient_FailDirect.GetString(), "FaultDirection", "", "FaultDirection", pParas->m_nFaultDir[0]);
	pXmlSierialize->xml_serialize(/* "故障性质" */g_sLangTxt_Native_NatureMalf.GetString(),"FaultPermanent","","FaultCharacter",pParas->m_nFaultProperty);

	pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */g_sLangTxt_Native_DurProtTrip.GetString(),"TimeAfterTrigger","s","number",pParas->m_fPostFaultTime);

	if (stt_xml_serialize_is_read(pXmlSierialize))//兼容处理
	{
		pXmlSierialize->xml_serialize(/* "保护动作后持续时间" */g_sLangTxt_Native_DurProtTrip.GetString(),"PostFaultTime","s","number",pParas->m_fPostFaultTime);
	}

	stt_xml_serialize_impedance_paras(pParas,pXmlSierialize,TRUE);

	//整定值
	pXmlSierialize->xml_serialize(/* "接地距离I段定值" */g_sLangTxt_Native_GroundDisSetI.GetString(),"Zeset1","Ω","float",pParas->m_fSettingLN[0]);
	pXmlSierialize->xml_serialize(/* "接地距离II段定值" */g_sLangTxt_Native_GroundDisSetII.GetString(),"Zeset2","Ω","float",pParas->m_fSettingLN[1]);
	pXmlSierialize->xml_serialize(/* "接地距离III段定值" */g_sLangTxt_Native_GroundDisSetIII.GetString(),"Zeset3","Ω","float",pParas->m_fSettingLN[2]);
	pXmlSierialize->xml_serialize(/* "接地距离IV段定值" */g_sLangTxt_Native_GroundDisSetIV.GetString(),"Zeset4","Ω","float",pParas->m_fSettingLN[3]);
	pXmlSierialize->xml_serialize(/* "接地距离V段定值" */g_sLangTxt_Native_GroundDisSetV.GetString(),"Zeset5","Ω","float",pParas->m_fSettingLN[4]);

	pXmlSierialize->xml_serialize(/* "接地距离I段时间" */g_sLangTxt_Native_GroundDisTimeI.GetString(),"Teset1","s","float",pParas->m_fTSettingLN[0]);
	pXmlSierialize->xml_serialize(/* "接地距离II段时间" */g_sLangTxt_Native_GroundDisTimeII.GetString(),"Teset2","s","float",pParas->m_fTSettingLN[1]);
	pXmlSierialize->xml_serialize(/* "接地距离III段时间" */g_sLangTxt_Native_GroundDisTimeIII.GetString(),"Teset3","s","float",pParas->m_fTSettingLN[2]);
	pXmlSierialize->xml_serialize(/* "接地距离IV段时间" */g_sLangTxt_Native_GroundDisTimeIV.GetString(),"Teset4","s","float",pParas->m_fTSettingLN[3]);
	pXmlSierialize->xml_serialize(/* "接地距离V段时间" */g_sLangTxt_Native_GroundDisTimeV.GetString(),"Teset5","s","float",pParas->m_fTSettingLN[4]);

	pXmlSierialize->xml_serialize(/* "相间距离I段定值" */g_sLangTxt_Native_PhaseDisSetI.GetString(),"Zxset1","Ω","float",pParas->m_fSettingLL[0]);
	pXmlSierialize->xml_serialize(/* "相间距离II段定值" */g_sLangTxt_Native_PhaseDisSetII.GetString(),"Zxset2","Ω","float",pParas->m_fSettingLL[1]);
	pXmlSierialize->xml_serialize(/* "相间距离III段定值" */g_sLangTxt_Native_PhaseDisSetIII.GetString(),"Zxset3","Ω","float",pParas->m_fSettingLL[2]);
	pXmlSierialize->xml_serialize(/* "相间距离IV段定值" */g_sLangTxt_Native_PhaseDisSetIV.GetString(),"Zxset4","Ω","float",pParas->m_fSettingLL[3]);
	pXmlSierialize->xml_serialize(/* "相间距离V段定值" */g_sLangTxt_Native_PhaseDisSetV.GetString(),"Zxset5","Ω","float",pParas->m_fSettingLL[4]);

	pXmlSierialize->xml_serialize(/* "相间距离I段时间" */g_sLangTxt_Native_PhaseDisTimeI.GetString(),"Txset1","s","float",pParas->m_fTSettingLL[0]);
	pXmlSierialize->xml_serialize(/* "相间距离II段时间" */g_sLangTxt_Native_PhaseDisTimeII.GetString(),"Txset2","s","float",pParas->m_fTSettingLL[1]);
	pXmlSierialize->xml_serialize(/* "相间距离III段时间" */g_sLangTxt_Native_PhaseDisTimeIII.GetString(),"Txset3","s","float",pParas->m_fTSettingLL[2]);
	pXmlSierialize->xml_serialize(/* "相间距离IV段时间" */g_sLangTxt_Native_PhaseDisTimeIV.GetString(),"Txset4","s","float",pParas->m_fTSettingLL[3]);
	pXmlSierialize->xml_serialize(/* "相间距离V段时间" */g_sLangTxt_Native_PhaseDisTimeV.GetString(),"Txset5","s","float",pParas->m_fTSettingLL[4]);
#endif
	
}

void stt_xml_serialize_I(tmt_DistanceParas_I *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("开入A", "BinA", "", "DInputState", pParas->m_nBinState[0]);
    pXmlSierialize->xml_serialize("开入B", "BinB", "", "DInputState", pParas->m_nBinState[1]);
    pXmlSierialize->xml_serialize("开入C", "BinC", "", "DInputState", pParas->m_nBinState[2]);
    pXmlSierialize->xml_serialize("开入D", "BinD", "", "DInputState", pParas->m_nBinState[3]);
    pXmlSierialize->xml_serialize("开入E", "BinE", "", "DInputState", pParas->m_nBinState[4]);
    pXmlSierialize->xml_serialize("开入F", "BinF", "", "DInputState", pParas->m_nBinState[5]);
    pXmlSierialize->xml_serialize("开入G", "BinG", "", "DInputState", pParas->m_nBinState[6]);
    pXmlSierialize->xml_serialize("开入H", "BinH", "", "DInputState", pParas->m_nBinState[7]);
    pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "", "InPutLogic", pParas->m_nBinLogic);
#else
#endif

}

void stt_xml_serialize_ex(tmt_DistanceParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize(pParas,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("阻抗定值(表达式)", "ZSettingExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize("动作时间定值(表达式)", "TSettingExp", "", "string", pParas->m_pszTSetting);
#else
	pXmlSierialize->xml_serialize(/* "阻抗定值(表达式)" */g_sLangTxt_Native_impedance_setExp.GetString(), "ZSettingExp", "", "string", pParas->m_pszSetting);
	pXmlSierialize->xml_serialize(/* "动作时间定值(表达式)" */g_sLangTxt_Native_ActionTimeSetValueExpr.GetString(), "TSettingExp", "", "string", pParas->m_pszTSetting);
#endif

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_DistanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_impedance_results(pResults,pXmlSierialize);
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("短路阻抗", "Zshort", "Ω", "number", pResults->m_fImp);
	pXmlSierialize->xml_serialize("短路阻抗角", "IShortAngle", "°", "number", pResults->m_fImpAngle);
#else
	pXmlSierialize->xml_serialize(/* "短路阻抗" */g_sLangTxt_Native_ShortZImp.GetString(), "Zshort", "Ω", "number", pResults->m_fImp);
	pXmlSierialize->xml_serialize(/* "短路阻抗角" */g_sLangTxt_Native_ShortZImpAng.GetString(), "IShortAngle", "°", "number", pResults->m_fImpAngle);
#endif

}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize_ex(&(pTests->m_oDistanceParas), pXmlParas);	//文件的读写
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize_ex(&(pTests->m_oDistanceParas), pXmlParas);	//测试参数下发
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
		{
			stt_xml_serialize(&pTests->m_oDistanceResults, pXmlResults);
		}
		else if (pTests->m_nSelected)
		{
			stt_xml_serialize(&pTests->m_oDistanceResults, pXmlResults);
		}
	}

	return pXmlParas;
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceTest_I *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize_I(&(pTests->m_oDistanceParas), pXmlParas);	//文件的读写
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize_I(&(pTests->m_oDistanceParas), pXmlParas);	//测试参数下发
        }
    }

    CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        if(stt_xml_serialize_is_read(pXmlParas) || stt_xml_serialize_is_register(pXmlParas))
        {
            stt_xml_serialize(&pTests->m_oDistanceResults, pXmlResults);
        }
        else if (pTests->m_nSelected)
        {
            stt_xml_serialize(&pTests->m_oDistanceResults, pXmlResults);
        }
    }

    return pXmlParas;
}
