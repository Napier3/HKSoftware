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
    pXmlSierialize->xml_serialize("����1״̬","_Bout1","","DOutputState",pParas->m_binOut[0].nState);
    pXmlSierialize->xml_serialize("����2״̬","_Bout2","","DOutputState",pParas->m_binOut[1].nState);
    pXmlSierialize->xml_serialize("����3״̬","_Bout3","","DOutputState",pParas->m_binOut[2].nState);
    pXmlSierialize->xml_serialize("����4״̬","_Bout4","","DOutputState",pParas->m_binOut[3].nState);
    pXmlSierialize->xml_serialize("����5״̬","_Bout5","","DOutputState",pParas->m_binOut[4].nState);
    pXmlSierialize->xml_serialize("����6״̬","_Bout6","","DOutputState",pParas->m_binOut[5].nState);
    pXmlSierialize->xml_serialize("����7״̬","_Bout7","","DOutputState",pParas->m_binOut[6].nState);
    pXmlSierialize->xml_serialize("����8״̬","_Bout8","","DOutputState",pParas->m_binOut[7].nState);
}

void stt_xml_serialize_binary_in(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
//    pXmlSierialize->xml_serialize("�������ʱ��","_SureTime","s","number",&pParas->m_fStabTime);
    pXmlSierialize->xml_serialize("����Aѡ��","_BinSelectA","","BOOL",pParas->m_binIn[0].nSelect);
    pXmlSierialize->xml_serialize("����Bѡ��","_BinSelectB","","BOOL",pParas->m_binIn[1].nSelect);
    pXmlSierialize->xml_serialize("����Cѡ��","_BinSelectC","","BOOL",pParas->m_binIn[2].nSelect);
    pXmlSierialize->xml_serialize("����Rѡ��","_BinSelectR","","BOOL",pParas->m_binIn[3].nSelect);
    pXmlSierialize->xml_serialize("����aѡ��","_BinSelecta","","BOOL",pParas->m_binIn[4].nSelect);
    pXmlSierialize->xml_serialize("����bѡ��","_BinSelectb","","BOOL",pParas->m_binIn[5].nSelect);
    pXmlSierialize->xml_serialize("����cѡ��","_BinSelectc","","BOOL",pParas->m_binIn[6].nSelect);
    pXmlSierialize->xml_serialize("����rѡ��","_BinSelectr","","BOOL",pParas->m_binIn[7].nSelect);
}

void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("Ua1��ֵ","_Ua","V","number",pParas->m_uiVOL[0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua1��λ","_UaPh","��","number",pParas->m_uiVOL[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua1Ƶ��","_UaFre","Hz","number",pParas->m_uiVOL[0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub1��ֵ","_Ub","V","number",pParas->m_uiVOL[1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub1��λ","_UbPh","��","number",pParas->m_uiVOL[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub1Ƶ��","_UbFre","Hz","number",pParas->m_uiVOL[1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc1��ֵ","_Uc","V","number",pParas->m_uiVOL[2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc1��λ","_UcPh","��","number",pParas->m_uiVOL[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc1Ƶ��","_UcFre","Hz","number",pParas->m_uiVOL[2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ua2��ֵ","_Ua2","V","number",pParas->m_uiVOL[3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua2��λ","_Ua2Ph","��","number",pParas->m_uiVOL[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua2Ƶ��","_Ua2Fre","Hz","number",pParas->m_uiVOL[3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub2��ֵ","_Ub2","V","number",pParas->m_uiVOL[4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub2��λ","_Ub2Ph","��","number",pParas->m_uiVOL[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub2Ƶ��","_Ub2Fre","Hz","number",pParas->m_uiVOL[4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc2��ֵ","_Uc2","V","number",pParas->m_uiVOL[5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc2��λ","_Uc2Ph","��","number",pParas->m_uiVOL[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc2Ƶ��","_Uc2Fre","Hz","number",pParas->m_uiVOL[5].Harm[1].fFreq);

    pXmlSierialize->xml_serialize("Ia1��ֵ","_Ia","A","number",pParas->m_uiCUR[0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia1��λ","_IaPh","��","number",pParas->m_uiCUR[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ia1Ƶ��","_IaFre","Hz","number",pParas->m_uiCUR[0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib1��ֵ","_Ib","A","number",pParas->m_uiCUR[1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib1��λ","_IbPh","��","number",pParas->m_uiCUR[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib1Ƶ��","_IbFre","Hz","number",pParas->m_uiCUR[1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic1��ֵ","_Ic","A","number",pParas->m_uiCUR[2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic1��λ","_IcPh","��","number",pParas->m_uiCUR[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic1Ƶ��","_IcFre","Hz","number",pParas->m_uiCUR[2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ia2��ֵ","_Ia2","A","number",pParas->m_uiCUR[3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia2��λ","_Ia2Ph","��","number",pParas->m_uiCUR[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ia2Ƶ��","_Ia2Fre","Hz","number",pParas->m_uiCUR[3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib2��ֵ","_Ib2","A","number",pParas->m_uiCUR[4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib2��λ","_Ib2Ph","��","number",pParas->m_uiCUR[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib2Ƶ��","_Ib2Fre","Hz","number",pParas->m_uiCUR[4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic2��ֵ","_Ic2","A","number",pParas->m_uiCUR[5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic2��λ","_Ic2Ph","��","number",pParas->m_uiCUR[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic2Ƶ��","_Ic2Fre","Hz","number",pParas->m_uiCUR[5].Harm[1].fFreq);

    pXmlSierialize->xml_serialize("�Ƿ���ֱ��ģʽ���","bDC","","BOOL",pParas->m_bDC);
    pXmlSierialize->xml_serialize("�Ƿ��ϻ�����","bAging","","BOOL",pParas->m_bAging);

    pXmlSierialize->xml_serialize("����ֱ����ѹ","_UdcAux","V","number",pParas->m_fVolAux);
    pXmlSierialize->xml_serialize("����ʱ��", "OutputTime"," ","number",pParas->m_fOutPutTime);

    stt_xml_serialize_binary_in(pParas, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);

    pXmlSierialize->xml_serialize("�Ƿ��Զ��ݱ�","_bAuto","","BOOL",pParas->m_bAuto);
    pXmlSierialize->xml_serialize("�ݱ�ͨ��ѡ��","_GradientChSelect","","PsuGradientChannel",pParas->m_nGradientChSelect);
    pXmlSierialize->xml_serialize("�ݱ�����ѡ��","_GradientTpSelect","","PsuGradientType",pParas->m_nGradientTpSelect);
    pXmlSierialize->xml_serialize("�仯ģʽ","Mode","","UIVariateMode",pParas->m_manuGradient.nMode);
    pXmlSierialize->xml_serialize("�仯ʼֵ","Start","","number",pParas->m_manuGradient.fStart);
    pXmlSierialize->xml_serialize("�仯��ֵ","End","","number",pParas->m_manuGradient.fEnd);
    pXmlSierialize->xml_serialize("�仯����","Step","","number",pParas->m_manuGradient.fStep);
    pXmlSierialize->xml_serialize("ÿ��ʱ��","StepTime","","number",pParas->m_manuGradient.fStepTime);
    pXmlSierialize->xml_serialize("������ʱ","TrigDelay","","number",pParas->m_manuGradient.fTrigDelay);
    pXmlSierialize->xml_serialize("�仯г������","Harm","","number",pParas->m_manuGradient.nHarmIndex);
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
