#include "stdafx.h"
#include "tmt_voltage_pnv_test.h"

void stt_init_paras(tmt_VoltagePnvParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_VoltagePnvParas));
    pParas->init(2);
}
void stt_init_paras(tmt_VoltagePnvResults *pParas)
{
    memset(&pParas, 0, sizeof(tmt_VoltagePnvResults));
    pParas->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_Voltage_Pnv(tmt_VoltagePnvParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("动作时间定值", "TSetting", "s", "set", pParas->m_fTSetting);
    pXmlSierialize->xml_serialize("故障时间", "FaultTime","","number",pParas->m_fFaultTime);
    pXmlSierialize->xml_serialize("故障前时间", "PreFaultTime","","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("故障触发方式", "FaultTrigMode","","number",pParas->m_nFaultTrigMode);

	pXmlSierialize->xml_serialize("Ua幅值", "_Ua", "V", "number",  pParas->m_fVolAmp[0]);
	pXmlSierialize->xml_serialize("Ub幅值", "_Ub", "V", "number",  pParas->m_fVolAmp[1]);
	pXmlSierialize->xml_serialize("Uc幅值", "_Uc", "V", "number",  pParas->m_fVolAmp[2]);
	pXmlSierialize->xml_serialize("Uz幅值", "_Uz", "V", "number",  pParas->m_fVolAmp[3]);

	pXmlSierialize->xml_serialize("Ua相位", "_UaPh", "°", "number",  pParas->m_fVolAng[0]);
	pXmlSierialize->xml_serialize("Ub相位", "_UbPh", "°", "number",  pParas->m_fVolAng[1]);
	pXmlSierialize->xml_serialize("Uc相位", "_UcPh", "°", "number",  pParas->m_fVolAng[2]);
    pXmlSierialize->xml_serialize("Uz相位", "_UzPh", "°", "number",  pParas->m_fVolAng[3]);

    pXmlSierialize->xml_serialize("Ia幅值", "_Ia", "A", "number",  pParas->m_fCurAmp[0]);
    pXmlSierialize->xml_serialize("Ib幅值", "_Ib", "A", "number",  pParas->m_fCurAmp[1]);
    pXmlSierialize->xml_serialize("Ic幅值", "_Ic", "A", "number",  pParas->m_fCurAmp[2]);

    pXmlSierialize->xml_serialize("Ia相位", "_IaPh", "°", "number",  pParas->m_fCurAng[0]);
    pXmlSierialize->xml_serialize("Ib相位", "_IbPh", "°", "number",  pParas->m_fCurAng[1]);
    pXmlSierialize->xml_serialize("Ic相位", "_IcPh", "°", "number",  pParas->m_fCurAng[2]);

	pXmlSierialize->xml_serialize("故障Ua幅值", "_FaultUa", "V", "number",  pParas->m_fVolAmp[4]);
	pXmlSierialize->xml_serialize("故障Ub幅值", "_FaultUb", "V", "number",  pParas->m_fVolAmp[5]);
	pXmlSierialize->xml_serialize("故障Uc幅值", "_FaultUc", "V", "number",  pParas->m_fVolAmp[6]);
	pXmlSierialize->xml_serialize("故障Uz幅值", "_FaultUx", "V", "number",  pParas->m_fVolAmp[7]);

	pXmlSierialize->xml_serialize("故障Ua相位", "_FaultUaPh", "°", "number",  pParas->m_fVolAng[4]);
	pXmlSierialize->xml_serialize("故障Ub相位", "_FaultUbPh", "°", "number",  pParas->m_fVolAng[5]);
	pXmlSierialize->xml_serialize("故障Uc相位", "_FaultUcPh", "°", "number",  pParas->m_fVolAng[6]);
    pXmlSierialize->xml_serialize("故障Uz相位", "_FaultUzPh", "°", "number",  pParas->m_fVolAng[7]);


    pXmlSierialize->xml_serialize("故障Ia幅值", "_FaultIa", "A", "number",  pParas->m_fCurAmp[3]);
    pXmlSierialize->xml_serialize("故障Ib幅值", "_FaultIb", "A", "number",  pParas->m_fCurAmp[4]);
    pXmlSierialize->xml_serialize("故障Ic幅值", "_FaultIc", "A", "number",  pParas->m_fCurAmp[5]);

    pXmlSierialize->xml_serialize("故障Ia相位", "_FaultIaPh", "°", "number",  pParas->m_fCurAng[3]);
    pXmlSierialize->xml_serialize("故障Ib相位", "_FaultIbPh", "°", "number",  pParas->m_fCurAng[4]);
    pXmlSierialize->xml_serialize("故障Ic相位", "_FaultIcPh", "°", "number",  pParas->m_fCurAng[5]);

    pXmlSierialize->xml_serialize("开入量选择", "BinSelect","","BinSelect",pParas->m_nBinSelect);
    pXmlSierialize->xml_serialize("开入A", "A", "°", "number",  pParas->m_nInputState[0]);
    pXmlSierialize->xml_serialize("开入B", "B", "°", "number",  pParas->m_nInputState[1]);
    pXmlSierialize->xml_serialize("开入C", "C", "°", "number",  pParas->m_nInputState[2]);
    pXmlSierialize->xml_serialize("开入R", "R", "°", "number",  pParas->m_nInputState[3]);
    pXmlSierialize->xml_serialize("开入E", "E", "°", "number",  pParas->m_nInputState[4]);
    pXmlSierialize->xml_serialize("开入F", "F", "°", "number",  pParas->m_nInputState[5]);
    pXmlSierialize->xml_serialize("开入G", "G", "°", "number",  pParas->m_nInputState[6]);
    pXmlSierialize->xml_serialize("开入H", "H", "°", "number",  pParas->m_nInputState[7]);
    pXmlSierialize->xml_serialize("开出1状态", "_B01", "°", "number",  pParas->m_nBout[0]);
    pXmlSierialize->xml_serialize("开出2状态", "_B02", "°", "number",  pParas->m_nBout[1]);
    pXmlSierialize->xml_serialize("开出3状态", "_B03", "°", "number",  pParas->m_nBout[2]);
    pXmlSierialize->xml_serialize("开出4状态", "_B04", "°", "number",  pParas->m_nBout[3]);
    pXmlSierialize->xml_serialize("开出翻转控制方式", "_OutputSwitchMode", "°", "number",  pParas->m_nOutputSwitchMode);
    pXmlSierialize->xml_serialize("开出翻转延时", "_OutputDelayTime", "°", "number",  pParas->m_fTimeTrig);
    pXmlSierialize->xml_serialize("开出保持时间", "_OutputKeepTime", "°", "number",  pParas->m_fOutputHoldTime);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_Voltage_Pnv(tmt_VoltagePnvResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("开入A动作描述","ActA","","number",pResults->m_nBinSwitchCount[0]);
    pXmlSierialize->xml_serialize("开入B动作描述","ActB","","number",pResults->m_nBinSwitchCount[1]);
    pXmlSierialize->xml_serialize("开入C动作描述","ActC","","number",pResults->m_nBinSwitchCount[2]);

    pXmlSierialize->xml_serialize("A相动作时间","TtripA","s","number",pResults->m_fTimeBinAct[0]);
    pXmlSierialize->xml_serialize("B相动作时间","TtripB","s","number",pResults->m_fTimeBinAct[1]);
    pXmlSierialize->xml_serialize("C相动作时间","TtripC","s","number",pResults->m_fTimeBinAct[2]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CSttXmlSerializeBase* stt_xml_serialize(tmt_VoltagePnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
        stt_xml_serialize_Voltage_Pnv(&(pTests->m_oVoltageParas), pXmlParas);
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
        stt_xml_serialize_Voltage_Pnv(&pTests->m_oVoltageResults, pXmlResults);
	}

	return pXmlParas;
}
