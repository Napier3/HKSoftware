#include "stdafx.h"
#include "tmt_state_diff_coef_pnv_test.h"

void stt_init_paras(tmt_DiffCoefPnvParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_DiffCoefPnvParas));
    pParas->init(2);
}
void stt_init_paras(tmt_DiffCoefPnvResults *pParas)
{
    memset(&pParas, 0, sizeof(tmt_DiffCoefPnvResults));
    pParas->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_DiffCoef_Pnv(tmt_DiffCoefPnvParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("递变相选择", "RampIndex","","number",pParas->m_nRampIndex);
    pXmlSierialize->xml_serialize("故障前时间", "PreFaultTime","","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("变化始值", "BeginVal","","number",pParas->m_fBeginVal);
    pXmlSierialize->xml_serialize("变化终值", "EndVal","","number",pParas->m_fEndVal);
    pXmlSierialize->xml_serialize("变化步长", "StepVal","","number",pParas->m_fStepVal);
    pXmlSierialize->xml_serialize("每步时间", "StepTime","","number",pParas->m_fStepTime);
    pXmlSierialize->xml_serialize("频率", "Freq","","number",pParas->m_fFreq);

    const char* strings[] = { "a", "b", "c", "ap", "bp" ,"cp", "sa", "sb", "sc"};
    CString strName, strID;
    for(int i = 0; i<9; i++)
    {
        strName.Format("复归U%s", strings[i]);
        strID.Format("U%s0", strings[i]);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString() ,"","number",pParas->m_fVolAmp[0][i]);

        strName.Format("复归U%s", strings[i]);
        strID.Format("U%sPh0", strings[i]);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString() ,"","number",pParas->m_fVolAng[0][i]);

        strName.Format("复归I%s", strings[i]);
        strID.Format("I%s0", strings[i]);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString() ,"","number",pParas->m_fCurAmp[0][i]);

        strName.Format("复归I%s", strings[i]);
        strID.Format("I%sPh0", strings[i]);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString() ,"","number",pParas->m_fCurAng[0][i]);

        strName.Format("U%s", strings[i]);
        strID.Format("U%s", strings[i]);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString() ,"","number",pParas->m_fVolAmp[1][i]);

        strName.Format("U%s", strings[i]);
        strID.Format("U%sPh", strings[i]);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString() ,"","number",pParas->m_fVolAng[1][i]);

        strName.Format("I%s", strings[i]);
        strID.Format("I%s", strings[i]);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString() ,"","number",pParas->m_fCurAmp[1][i]);

        strName.Format("I%s", strings[i]);
        strID.Format("I%sPh", strings[i]);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString() ,"","number",pParas->m_fCurAng[1][i]);
    }

    pXmlSierialize->xml_serialize("开入逻辑", "_AndOr","","InPutLogic",pParas->m_nBinLogic);
    pXmlSierialize->xml_serialize("开入A", "_BinSelectA", "°", "number",  pParas->m_nInputState[0]);
    pXmlSierialize->xml_serialize("开入B", "_BinSelectB", "°", "number",  pParas->m_nInputState[1]);
    pXmlSierialize->xml_serialize("开入C", "_BinSelectC", "°", "number",  pParas->m_nInputState[2]);
    pXmlSierialize->xml_serialize("开入R", "_BinSelectR", "°", "number",  pParas->m_nInputState[3]);
    pXmlSierialize->xml_serialize("开入a", "_BinSelecta", "°", "number",  pParas->m_nInputState[4]);
    pXmlSierialize->xml_serialize("开入b", "_BinSelectb", "°", "number",  pParas->m_nInputState[5]);
    pXmlSierialize->xml_serialize("开入c", "_BinSelectc", "°", "number",  pParas->m_nInputState[6]);
    pXmlSierialize->xml_serialize("开入r", "_BinSelectr", "°", "number",  pParas->m_nInputState[7]);
    pXmlSierialize->xml_serialize("故障前开出1", "_Bout0_1", "°", "number",  pParas->m_nBout[0][0]);
    pXmlSierialize->xml_serialize("故障前开出2", "_Bout0_2", "°", "number",  pParas->m_nBout[0][1]);
    pXmlSierialize->xml_serialize("故障前开出3", "_Bout0_3", "°", "number",  pParas->m_nBout[0][2]);
    pXmlSierialize->xml_serialize("故障前开出4", "_Bout0_4", "°", "number",  pParas->m_nBout[0][3]);
    pXmlSierialize->xml_serialize("故障前开出5", "_Bout0_5", "°", "number",  pParas->m_nBout[0][4]);
    pXmlSierialize->xml_serialize("故障前开出6", "_Bout0_6", "°", "number",  pParas->m_nBout[0][5]);
    pXmlSierialize->xml_serialize("故障前开出7", "_Bout0_7", "°", "number",  pParas->m_nBout[0][6]);
    pXmlSierialize->xml_serialize("故障前开出8", "_Bout0_8", "°", "number",  pParas->m_nBout[0][7]);
    pXmlSierialize->xml_serialize("故障态开出1", "_Bout1_1", "°", "number",  pParas->m_nBout[1][0]);
    pXmlSierialize->xml_serialize("故障态开出2", "_Bout1_2", "°", "number",  pParas->m_nBout[1][1]);
    pXmlSierialize->xml_serialize("故障态开出3", "_Bout1_3", "°", "number",  pParas->m_nBout[1][2]);
    pXmlSierialize->xml_serialize("故障态开出4", "_Bout1_4", "°", "number",  pParas->m_nBout[1][3]);
    pXmlSierialize->xml_serialize("故障态开出5", "_Bout1_5", "°", "number",  pParas->m_nBout[1][4]);
    pXmlSierialize->xml_serialize("故障态开出6", "_Bout1_6", "°", "number",  pParas->m_nBout[1][5]);
    pXmlSierialize->xml_serialize("故障态开出7", "_Bout1_7", "°", "number",  pParas->m_nBout[1][6]);
    pXmlSierialize->xml_serialize("故障态开出8", "_Bout1_8", "°", "number",  pParas->m_nBout[1][7]);
    pXmlSierialize->xml_serialize("开出翻转控制方式", "_OutputSwitchMode", "°", "number",  pParas->m_nOutputSwitchMode);
    pXmlSierialize->xml_serialize("开出翻转时刻", "_OutputDelayTime", "°", "number",  pParas->m_fHoldTime);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_DiffCoef_Pnv(tmt_DiffCoefPnvResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("开入A动作描述","ActA","","number",pResults->m_nBinSwitchCount[0]);
    pXmlSierialize->xml_serialize("开入B动作描述","ActB","","number",pResults->m_nBinSwitchCount[1]);
    pXmlSierialize->xml_serialize("开入C动作描述","ActC","","number",pResults->m_nBinSwitchCount[2]);

    pXmlSierialize->xml_serialize("A相动作时间","TtripA","s","number",pResults->m_fTimeBinAct[0]);
    pXmlSierialize->xml_serialize("B相动作时间","TtripB","s","number",pResults->m_fTimeBinAct[1]);
    pXmlSierialize->xml_serialize("C相动作时间","TtripC","s","number",pResults->m_fTimeBinAct[2]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CSttXmlSerializeBase* stt_xml_serialize(tmt_DiffCoefPnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
        stt_xml_serialize_DiffCoef_Pnv(&(pTests->m_oDiffCoefParas), pXmlParas);
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
        stt_xml_serialize_DiffCoef_Pnv(&pTests->m_oDiffCoefResults, pXmlResults);
	}

	return pXmlParas;
}
