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
    pXmlSierialize->xml_serialize("��̬����1״̬","_Bout01","","DOutputState",pParas->m_binOut[0][0].nState);
    pXmlSierialize->xml_serialize("��̬����2״̬","_Bout02","","DOutputState",pParas->m_binOut[0][1].nState);
    pXmlSierialize->xml_serialize("��̬����3״̬","_Bout03","","DOutputState",pParas->m_binOut[0][2].nState);
    pXmlSierialize->xml_serialize("��̬����4״̬","_Bout04","","DOutputState",pParas->m_binOut[0][3].nState);
    pXmlSierialize->xml_serialize("��̬����5״̬","_Bout05","","DOutputState",pParas->m_binOut[0][4].nState);
    pXmlSierialize->xml_serialize("��̬����6״̬","_Bout06","","DOutputState",pParas->m_binOut[0][5].nState);
    pXmlSierialize->xml_serialize("��̬����7״̬","_Bout07","","DOutputState",pParas->m_binOut[0][6].nState);
    pXmlSierialize->xml_serialize("��̬����8״̬","_Bout08","","DOutputState",pParas->m_binOut[0][7].nState);

    pXmlSierialize->xml_serialize("����̬����1״̬","_Bout1","","DOutputState",pParas->m_binOut[1][0].nState);
    pXmlSierialize->xml_serialize("����̬����2״̬","_Bout2","","DOutputState",pParas->m_binOut[1][1].nState);
    pXmlSierialize->xml_serialize("����̬����3״̬","_Bout3","","DOutputState",pParas->m_binOut[1][2].nState);
    pXmlSierialize->xml_serialize("����̬����4״̬","_Bout4","","DOutputState",pParas->m_binOut[1][3].nState);
    pXmlSierialize->xml_serialize("����̬����5״̬","_Bout5","","DOutputState",pParas->m_binOut[1][4].nState);
    pXmlSierialize->xml_serialize("����̬����6״̬","_Bout6","","DOutputState",pParas->m_binOut[1][5].nState);
    pXmlSierialize->xml_serialize("����̬����7״̬","_Bout7","","DOutputState",pParas->m_binOut[1][6].nState);
    pXmlSierialize->xml_serialize("����̬����8״̬","_Bout8","","DOutputState",pParas->m_binOut[1][7].nState);
}

void stt_xml_serialize_binary_in(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
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

void stt_xml_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set", pParas->m_fStart);
    pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop );
    pXmlSierialize->xml_serialize("���Ծ���", "Step", "", "set", pParas->m_fStep);
    pXmlSierialize->xml_serialize("����ʱ��", "StepTime", "s", "set", pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("�Ƿ���Է���ֵ", "VaryMode", "", "BOOL", pParas->m_nTestMode);
    pXmlSierialize->xml_serialize("�ݱ����", "VarIndex", "", "UIRampChannel", (int&)pParas->m_nChannel);
    pXmlSierialize->xml_serialize("�ݱ�����", "VarType", "", "UIRampType", pParas->m_nType);

    pXmlSierialize->xml_serialize("Ua1��ֵ","_Ua","V","number",pParas->m_uiVOL[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua1��λ","_UaPh","��","number",pParas->m_uiVOL[2][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua1Ƶ��","_UaFre","Hz","number",pParas->m_uiVOL[2][0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub1��ֵ","_Ub","V","number",pParas->m_uiVOL[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub1��λ","_UbPh","��","number",pParas->m_uiVOL[2][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub1Ƶ��","_UbFre","Hz","number",pParas->m_uiVOL[2][1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc1��ֵ","_Uc","V","number",pParas->m_uiVOL[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc1��λ","_UcPh","��","number",pParas->m_uiVOL[2][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc1Ƶ��","_UcFre","Hz","number",pParas->m_uiVOL[2][2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ua2��ֵ","_Ua2","V","number",pParas->m_uiVOL[2][3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua2��λ","_Ua2Ph","��","number",pParas->m_uiVOL[2][3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ua2Ƶ��","_Ua2Fre","Hz","number",pParas->m_uiVOL[2][3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub2��ֵ","_Ub2","V","number",pParas->m_uiVOL[2][4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub2��λ","_Ub2Ph","��","number",pParas->m_uiVOL[2][4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ub2Ƶ��","_Ub2Fre","Hz","number",pParas->m_uiVOL[2][4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc2��ֵ","_Uc2","V","number",pParas->m_uiVOL[2][5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc2��λ","_Uc2Ph","��","number",pParas->m_uiVOL[2][5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Uc2Ƶ��","_Uc2Fre","Hz","number",pParas->m_uiVOL[2][5].Harm[1].fFreq);

    pXmlSierialize->xml_serialize("Ia1��ֵ","_Ia","A","number",pParas->m_uiCUR[2][0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia1��λ","_IaPh","��","number",pParas->m_uiCUR[2][0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ia1Ƶ��","_IaFre","Hz","number",pParas->m_uiCUR[2][0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib1��ֵ","_Ib","A","number",pParas->m_uiCUR[2][1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib1��λ","_IbPh","��","number",pParas->m_uiCUR[2][1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib1Ƶ��","_IbFre","Hz","number",pParas->m_uiCUR[2][1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic1��ֵ","_Ic","A","number",pParas->m_uiCUR[2][2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic1��λ","_IcPh","��","number",pParas->m_uiCUR[2][2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic1Ƶ��","_IcFre","Hz","number",pParas->m_uiCUR[2][2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ia2��ֵ","_Ia2","A","number",pParas->m_uiCUR[2][3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia2��λ","_Ia2Ph","��","number",pParas->m_uiCUR[2][3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ia2Ƶ��","_Ia2Fre","Hz","number",pParas->m_uiCUR[2][3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib2��ֵ","_Ib2","A","number",pParas->m_uiCUR[2][4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib2��λ","_Ib2Ph","��","number",pParas->m_uiCUR[2][4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ib2Ƶ��","_Ib2Fre","Hz","number",pParas->m_uiCUR[2][4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic2��ֵ","_Ic2","A","number",pParas->m_uiCUR[2][5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic2��λ","_Ic2Ph","��","number",pParas->m_uiCUR[2][5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("Ic2Ƶ��","_Ic2Fre","Hz","number",pParas->m_uiCUR[2][5].Harm[1].fFreq);

    pXmlSierialize->xml_serialize("edingpinlv","_Freq","Hz","number",pParas->m_fFreq);
    pXmlSierialize->xml_serialize("���ģʽ","_OutputType","","OutputType",pParas->m_nOutputType);
    pXmlSierialize->xml_serialize("����ǰ׼��ʱ��","_PrepareTime","s","number",pParas->m_fPrepareTime);
    pXmlSierialize->xml_serialize("����ǰʱ��","_PreFaultTime","s","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("��̬��ѹ��ֵ","_UPre","V","number",pParas->m_fU);
    pXmlSierialize->xml_serialize("��̬������ֵ","_IPre","A","number",pParas->m_fI);
    pXmlSierialize->xml_serialize("��̬���", "Z0Ph", "��", "number",  pParas->m_fAngle0);
    stt_xml_serialize_binary_in(pParas, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas, pXmlSierialize);
}

void stt_xml_serialize(tmt_GradientResult *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����ֵ","TripValue","A/V","number",pParas->m_fTripValue);
    pXmlSierialize->xml_serialize("����ֵ","ReturnValue","A/V","number",pParas->m_fReturnValue);
    pXmlSierialize->xml_serialize("����ϵ��","ReturnCoef","","number",pParas->m_fTripValue);
    pXmlSierialize->xml_serialize("��������","ActDsec","","number",pParas->m_fTripValue);
    pXmlSierialize->xml_serialize("����1����ֵ","TripValueA","A/V","number",pParas->m_fTripValueChl[0]);
    pXmlSierialize->xml_serialize("����2����ֵ","TripValueB","A/V","number",pParas->m_fTripValueChl[1]);
    pXmlSierialize->xml_serialize("����3����ֵ","TripValueC","A/V","number",pParas->m_fTripValueChl[2]);
    pXmlSierialize->xml_serialize("����4����ֵ","TripValueD","A/V","number",pParas->m_fTripValueChl[3]);
    pXmlSierialize->xml_serialize("����5����ֵ","TripValueE","A/V","number",pParas->m_fTripValueChl[4]);
    pXmlSierialize->xml_serialize("����6����ֵ","TripValueF","A/V","number",pParas->m_fTripValueChl[5]);
    pXmlSierialize->xml_serialize("����7����ֵ","TripValueG","A/V","number",pParas->m_fTripValueChl[6]);
    pXmlSierialize->xml_serialize("����8����ֵ","TripValueH","A/V","number",pParas->m_fTripValueChl[7]);
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
