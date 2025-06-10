#include "stdafx.h"
#include "tmt_manu_test.h"

void stt_init_paras(tmt_ManualParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_ManualParas));
    pParas->init();
}

void stt_init_results(tmt_ManualResult *pResults)
{
    memset(&pResults, 0, sizeof(tmt_ManualResult));
    pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///

void stt_xml_serialize_binary_out(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("开出1状态","_Bout1","","DOutputState",pParas->m_binOut[0].nState);
    pXmlSierialize->xml_serialize("开出2状态","_Bout2","","DOutputState",pParas->m_binOut[1].nState);
    pXmlSierialize->xml_serialize("开出3状态","_Bout3","","DOutputState",pParas->m_binOut[2].nState);
    pXmlSierialize->xml_serialize("开出4状态","_Bout4","","DOutputState",pParas->m_binOut[3].nState);
    pXmlSierialize->xml_serialize("开出5状态","_Bout5","","DOutputState",pParas->m_binOut[4].nState);
    pXmlSierialize->xml_serialize("开出6状态","_Bout6","","DOutputState",pParas->m_binOut[5].nState);
    pXmlSierialize->xml_serialize("开出7状态","_Bout7","","DOutputState",pParas->m_binOut[6].nState);
    pXmlSierialize->xml_serialize("开出8状态","_Bout8","","DOutputState",pParas->m_binOut[7].nState);
}

void stt_xml_serialize_binary_in(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("Ua1幅值","_Ua","V","number",pParas->m_uiVOL[0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua1相位","_UaPh","°","number",pParas->m_uiVOL[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua1频率","_UaFre","Hz","number",pParas->m_uiVOL[0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub1幅值","_Ub","V","number",pParas->m_uiVOL[1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub1相位","_UbPh","°","number",pParas->m_uiVOL[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub1频率","_UbFre","Hz","number",pParas->m_uiVOL[1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc1幅值","_Uc","V","number",pParas->m_uiVOL[2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc1相位","_UcPh","°","number",pParas->m_uiVOL[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc1频率","_UcFre","Hz","number",pParas->m_uiVOL[2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ua2幅值","_Ua2","V","number",pParas->m_uiVOL[3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua2相位","_Ua2Ph","°","number",pParas->m_uiVOL[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua2频率","_Ua2Fre","Hz","number",pParas->m_uiVOL[3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub2幅值","_Ub2","V","number",pParas->m_uiVOL[4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub2相位","_Ub2Ph","°","number",pParas->m_uiVOL[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub2频率","_Ub2Fre","Hz","number",pParas->m_uiVOL[4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc2幅值","_Uc2","V","number",pParas->m_uiVOL[5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc2相位","_Uc2Ph","°","number",pParas->m_uiVOL[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc2频率","_Uc2Fre","Hz","number",pParas->m_uiVOL[5].Harm[1].fFreq);

    pXmlSierialize->xml_serialize("Ia1幅值","_Ia","A","number",pParas->m_uiCUR[0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia1相位","_IaPh","°","number",pParas->m_uiCUR[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ia1频率","_IaFre","Hz","number",pParas->m_uiCUR[0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib1幅值","_Ib","A","number",pParas->m_uiCUR[1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib1相位","_IbPh","°","number",pParas->m_uiCUR[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib1频率","_IbFre","Hz","number",pParas->m_uiCUR[1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic1幅值","_Ic","A","number",pParas->m_uiCUR[2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic1相位","_IcPh","°","number",pParas->m_uiCUR[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic1频率","_IcFre","Hz","number",pParas->m_uiCUR[2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ia2幅值","_Ia2","A","number",pParas->m_uiCUR[3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia2相位","_Ia2Ph","°","number",pParas->m_uiCUR[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ia2频率","_Ia2Fre","Hz","number",pParas->m_uiCUR[3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib2幅值","_Ib2","A","number",pParas->m_uiCUR[4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib2相位","_Ib2Ph","°","number",pParas->m_uiCUR[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib2频率","_Ib2Fre","Hz","number",pParas->m_uiCUR[4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic2幅值","_Ic2","A","number",pParas->m_uiCUR[5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic2相位","_Ic2Ph","°","number",pParas->m_uiCUR[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic2频率","_Ic2Fre","Hz","number",pParas->m_uiCUR[5].Harm[1].fFreq);

    pXmlSierialize->xml_serialize("是否以直流模式输出","bDC","","BOOL",pParas->m_bDC);
    pXmlSierialize->xml_serialize("是否老化试验","bAging","","BOOL",pParas->m_bAging);

    pXmlSierialize->xml_serialize("辅助直流电压","_UdcAux","V","number",pParas->m_fVolAux);
    pXmlSierialize->xml_serialize("最长输出时间", "OutputTime"," ","number",pParas->m_fOutPutTime);

    stt_xml_serialize_binary_in(pParas, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);

    pXmlSierialize->xml_serialize("是否自动递变","_bAuto","","BOOL",pParas->m_bAuto);
    pXmlSierialize->xml_serialize("递变通道选择","_GradientChSelect","","PsuGradientChannel",pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize("递变类型选择","_GradientTpSelect","","PsuGradientType",pParas->m_nGradientTpSelect);
    pXmlSierialize->xml_serialize("变化模式","Mode","","UIVariateMode",pParas->m_manuGradient.nMode);
    pXmlSierialize->xml_serialize("变化始值","Start","","number",pParas->m_manuGradient.fStart);
    pXmlSierialize->xml_serialize("变化终值","End","","number",pParas->m_manuGradient.fEnd);
    pXmlSierialize->xml_serialize("变化步长","Step","","number",pParas->m_manuGradient.fStep);
    pXmlSierialize->xml_serialize("每步时间","StepTime","","number",pParas->m_manuGradient.fStepTime);
    pXmlSierialize->xml_serialize("触发延时","TrigDelay","","number",pParas->m_manuGradient.fTrigDelay);
    pXmlSierialize->xml_serialize("变化谐波次数","Harm","","number",pParas->m_manuGradient.nHarmIndex);
}

void stt_xml_serialize(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{

}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_manu_test.h"
#include"../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_ManuTest()
{
    tmt_ManualTest oManualTest;
    oManualTest.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oManualTest.m_oManuParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("ManualTestDemo.xml");
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
