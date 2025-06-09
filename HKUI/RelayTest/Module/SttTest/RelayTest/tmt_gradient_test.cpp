#include "stdafx.h"
#include "tmt_gradient_test.h"

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
}

void stt_xml_serialize_binary_in(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("开入逻辑","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
//    pXmlSierialize->xml_serialize("开入防抖时间","_SureTime","s","number",&pParas->m_fStabTime);
    pXmlSierialize->xml_serialize("开入A选择","_BinSelectA","","BOOL",pParas->m_binIn[0].nSelect);
    pXmlSierialize->xml_serialize("开入B选择","_BinSelectB","","BOOL",pParas->m_binIn[1].nSelect);
    pXmlSierialize->xml_serialize("开入C选择","_BinSelectC","","BOOL",pParas->m_binIn[2].nSelect);
    pXmlSierialize->xml_serialize("开入R选择","_BinSelectR","","BOOL",pParas->m_binIn[3].nSelect);
    pXmlSierialize->xml_serialize("开入a选择","_BinSelecta","","BOOL",pParas->m_binIn[4].nSelect);
    pXmlSierialize->xml_serialize("开入b选择","_BinSelectb","","BOOL",pParas->m_binIn[5].nSelect);
    pXmlSierialize->xml_serialize("开入c选择","_BinSelectc","","BOOL",pParas->m_binIn[6].nSelect);
    pXmlSierialize->xml_serialize("开入r选择","_BinSelectr","","BOOL",pParas->m_binIn[7].nSelect);
}

void stt_xml_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("变化始值", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("变化终值", "EndVal", "", "set", pParas->m_fStop );
    pXmlSierialize->xml_serialize("测试精度", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("步长时间", "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("是否测试返回值", "VaryMode", "", "BOOL", pParas->m_nTestMode);
    pXmlSierialize->xml_serialize("递变相别", "VarIndex", "", "UIRampChannel", (int&)pParas->m_nChannel);
    pXmlSierialize->xml_serialize("递变类型", "VarType", "", "UIRampType", pParas->m_nType);

    pXmlSierialize->xml_serialize("Ua1幅值","_Ua","V","number",pParas->m_uiVOL[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua1相位","_UaPh","°","number",pParas->m_uiVOL[2][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua1频率","_UaFre","Hz","number",pParas->m_uiVOL[2][0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub1幅值","_Ub","V","number",pParas->m_uiVOL[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub1相位","_UbPh","°","number",pParas->m_uiVOL[2][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub1频率","_UbFre","Hz","number",pParas->m_uiVOL[2][1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc1幅值","_Uc","V","number",pParas->m_uiVOL[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc1相位","_UcPh","°","number",pParas->m_uiVOL[2][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc1频率","_UcFre","Hz","number",pParas->m_uiVOL[2][2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ua2幅值","_Ua2","V","number",pParas->m_uiVOL[2][3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua2相位","_Ua2Ph","°","number",pParas->m_uiVOL[2][3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua2频率","_Ua2Fre","Hz","number",pParas->m_uiVOL[2][3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub2幅值","_Ub2","V","number",pParas->m_uiVOL[2][4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub2相位","_Ub2Ph","°","number",pParas->m_uiVOL[2][4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub2频率","_Ub2Fre","Hz","number",pParas->m_uiVOL[2][4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc2幅值","_Uc2","V","number",pParas->m_uiVOL[2][5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc2相位","_Uc2Ph","°","number",pParas->m_uiVOL[2][5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc2频率","_Uc2Fre","Hz","number",pParas->m_uiVOL[2][5].Harm[1].fFreq);

    pXmlSierialize->xml_serialize("Ia1幅值","_Ia","A","number",pParas->m_uiCUR[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia1相位","_IaPh","°","number",pParas->m_uiCUR[2][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ia1频率","_IaFre","Hz","number",pParas->m_uiCUR[2][0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib1幅值","_Ib","A","number",pParas->m_uiCUR[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib1相位","_IbPh","°","number",pParas->m_uiCUR[2][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib1频率","_IbFre","Hz","number",pParas->m_uiCUR[2][1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic1幅值","_Ic","A","number",pParas->m_uiCUR[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic1相位","_IcPh","°","number",pParas->m_uiCUR[2][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic1频率","_IcFre","Hz","number",pParas->m_uiCUR[2][2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ia2幅值","_Ia2","A","number",pParas->m_uiCUR[2][3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia2相位","_Ia2Ph","°","number",pParas->m_uiCUR[2][3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ia2频率","_Ia2Fre","Hz","number",pParas->m_uiCUR[2][3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib2幅值","_Ib2","A","number",pParas->m_uiCUR[2][4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib2相位","_Ib2Ph","°","number",pParas->m_uiCUR[2][4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib2频率","_Ib2Fre","Hz","number",pParas->m_uiCUR[2][4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic2幅值","_Ic2","A","number",pParas->m_uiCUR[2][5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic2相位","_Ic2Ph","°","number",pParas->m_uiCUR[2][5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic2频率","_Ic2Fre","Hz","number",pParas->m_uiCUR[2][5].Harm[1].fFreq);

    pXmlSierialize->xml_serialize("edingpinlv","_Freq","Hz","number",pParas->m_fFreq);
    pXmlSierialize->xml_serialize("输出模式","_OutputType","","OutputType",pParas->m_nOutputType);
    pXmlSierialize->xml_serialize("测试前准备时间","_PrepareTime","s","number",pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("故障前时间","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("常态电压幅值","_UPre","V","number",pParas->m_fU);
    pXmlSierialize->xml_serialize("常态电流幅值","_IPre","A","number",pParas->m_fI);
    pXmlSierialize->xml_serialize("常态相角", "Z0Ph", "°", "number",  pParas->m_fAngle0);
    stt_xml_serialize_binary_in(pParas, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
}

void stt_xml_serialize(tmt_GradientResult *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("动作值","TripValue","A/V","number",pParas->m_fTripValue);
    pXmlSierialize->xml_serialize("返回值","ReturnValue","A/V","number",pParas->m_fReturnValue);
    pXmlSierialize->xml_serialize("返回系数","ReturnCoef","","number",pParas->m_fTripValue);
    pXmlSierialize->xml_serialize("动作描述","ActDsec","","number",pParas->m_fTripValue);
    pXmlSierialize->xml_serialize("开入1动作值","TripValueA","A/V","number",pParas->m_fTripValueChl[0]);
    pXmlSierialize->xml_serialize("开入2动作值","TripValueB","A/V","number",pParas->m_fTripValueChl[1]);
    pXmlSierialize->xml_serialize("开入3动作值","TripValueC","A/V","number",pParas->m_fTripValueChl[2]);
    pXmlSierialize->xml_serialize("开入4动作值","TripValueD","A/V","number",pParas->m_fTripValueChl[3]);
    pXmlSierialize->xml_serialize("开入5动作值","TripValueE","A/V","number",pParas->m_fTripValueChl[4]);
    pXmlSierialize->xml_serialize("开入6动作值","TripValueF","A/V","number",pParas->m_fTripValueChl[5]);
    pXmlSierialize->xml_serialize("开入7动作值","TripValueG","A/V","number",pParas->m_fTripValueChl[6]);
    pXmlSierialize->xml_serialize("开入8动作值","TripValueH","A/V","number",pParas->m_fTripValueChl[7]);
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
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
