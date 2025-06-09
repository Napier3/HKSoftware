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
    pXmlSierialize->xml_serialize("����ʱ�䶨ֵ", "TSetting", "s", "set", pParas->m_fTSetting);
    pXmlSierialize->xml_serialize("����ʱ��", "FaultTime","","number",pParas->m_fFaultTime);
    pXmlSierialize->xml_serialize("����ǰʱ��", "PreFaultTime","","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("���ϴ�����ʽ", "FaultTrigMode","","number",pParas->m_nFaultTrigMode);

	pXmlSierialize->xml_serialize("Ua��ֵ", "_Ua", "V", "number",  pParas->m_fVolAmp[0]);
	pXmlSierialize->xml_serialize("Ub��ֵ", "_Ub", "V", "number",  pParas->m_fVolAmp[1]);
	pXmlSierialize->xml_serialize("Uc��ֵ", "_Uc", "V", "number",  pParas->m_fVolAmp[2]);
	pXmlSierialize->xml_serialize("Uz��ֵ", "_Uz", "V", "number",  pParas->m_fVolAmp[3]);

	pXmlSierialize->xml_serialize("Ua��λ", "_UaPh", "��", "number",  pParas->m_fVolAng[0]);
	pXmlSierialize->xml_serialize("Ub��λ", "_UbPh", "��", "number",  pParas->m_fVolAng[1]);
	pXmlSierialize->xml_serialize("Uc��λ", "_UcPh", "��", "number",  pParas->m_fVolAng[2]);
    pXmlSierialize->xml_serialize("Uz��λ", "_UzPh", "��", "number",  pParas->m_fVolAng[3]);

    pXmlSierialize->xml_serialize("Ia��ֵ", "_Ia", "A", "number",  pParas->m_fCurAmp[0]);
    pXmlSierialize->xml_serialize("Ib��ֵ", "_Ib", "A", "number",  pParas->m_fCurAmp[1]);
    pXmlSierialize->xml_serialize("Ic��ֵ", "_Ic", "A", "number",  pParas->m_fCurAmp[2]);

    pXmlSierialize->xml_serialize("Ia��λ", "_IaPh", "��", "number",  pParas->m_fCurAng[0]);
    pXmlSierialize->xml_serialize("Ib��λ", "_IbPh", "��", "number",  pParas->m_fCurAng[1]);
    pXmlSierialize->xml_serialize("Ic��λ", "_IcPh", "��", "number",  pParas->m_fCurAng[2]);

	pXmlSierialize->xml_serialize("����Ua��ֵ", "_FaultUa", "V", "number",  pParas->m_fVolAmp[4]);
	pXmlSierialize->xml_serialize("����Ub��ֵ", "_FaultUb", "V", "number",  pParas->m_fVolAmp[5]);
	pXmlSierialize->xml_serialize("����Uc��ֵ", "_FaultUc", "V", "number",  pParas->m_fVolAmp[6]);
	pXmlSierialize->xml_serialize("����Uz��ֵ", "_FaultUx", "V", "number",  pParas->m_fVolAmp[7]);

	pXmlSierialize->xml_serialize("����Ua��λ", "_FaultUaPh", "��", "number",  pParas->m_fVolAng[4]);
	pXmlSierialize->xml_serialize("����Ub��λ", "_FaultUbPh", "��", "number",  pParas->m_fVolAng[5]);
	pXmlSierialize->xml_serialize("����Uc��λ", "_FaultUcPh", "��", "number",  pParas->m_fVolAng[6]);
    pXmlSierialize->xml_serialize("����Uz��λ", "_FaultUzPh", "��", "number",  pParas->m_fVolAng[7]);


    pXmlSierialize->xml_serialize("����Ia��ֵ", "_FaultIa", "A", "number",  pParas->m_fCurAmp[3]);
    pXmlSierialize->xml_serialize("����Ib��ֵ", "_FaultIb", "A", "number",  pParas->m_fCurAmp[4]);
    pXmlSierialize->xml_serialize("����Ic��ֵ", "_FaultIc", "A", "number",  pParas->m_fCurAmp[5]);

    pXmlSierialize->xml_serialize("����Ia��λ", "_FaultIaPh", "��", "number",  pParas->m_fCurAng[3]);
    pXmlSierialize->xml_serialize("����Ib��λ", "_FaultIbPh", "��", "number",  pParas->m_fCurAng[4]);
    pXmlSierialize->xml_serialize("����Ic��λ", "_FaultIcPh", "��", "number",  pParas->m_fCurAng[5]);

    pXmlSierialize->xml_serialize("������ѡ��", "BinSelect","","BinSelect",pParas->m_nBinSelect);
    pXmlSierialize->xml_serialize("����A", "A", "��", "number",  pParas->m_nInputState[0]);
    pXmlSierialize->xml_serialize("����B", "B", "��", "number",  pParas->m_nInputState[1]);
    pXmlSierialize->xml_serialize("����C", "C", "��", "number",  pParas->m_nInputState[2]);
    pXmlSierialize->xml_serialize("����R", "R", "��", "number",  pParas->m_nInputState[3]);
    pXmlSierialize->xml_serialize("����E", "E", "��", "number",  pParas->m_nInputState[4]);
    pXmlSierialize->xml_serialize("����F", "F", "��", "number",  pParas->m_nInputState[5]);
    pXmlSierialize->xml_serialize("����G", "G", "��", "number",  pParas->m_nInputState[6]);
    pXmlSierialize->xml_serialize("����H", "H", "��", "number",  pParas->m_nInputState[7]);
    pXmlSierialize->xml_serialize("����1״̬", "_B01", "��", "number",  pParas->m_nBout[0]);
    pXmlSierialize->xml_serialize("����2״̬", "_B02", "��", "number",  pParas->m_nBout[1]);
    pXmlSierialize->xml_serialize("����3״̬", "_B03", "��", "number",  pParas->m_nBout[2]);
    pXmlSierialize->xml_serialize("����4״̬", "_B04", "��", "number",  pParas->m_nBout[3]);
    pXmlSierialize->xml_serialize("������ת���Ʒ�ʽ", "_OutputSwitchMode", "��", "number",  pParas->m_nOutputSwitchMode);
    pXmlSierialize->xml_serialize("������ת��ʱ", "_OutputDelayTime", "��", "number",  pParas->m_fTimeTrig);
    pXmlSierialize->xml_serialize("��������ʱ��", "_OutputKeepTime", "��", "number",  pParas->m_fOutputHoldTime);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize_Voltage_Pnv(tmt_VoltagePnvResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����A��������","ActA","","number",pResults->m_nBinSwitchCount[0]);
    pXmlSierialize->xml_serialize("����B��������","ActB","","number",pResults->m_nBinSwitchCount[1]);
    pXmlSierialize->xml_serialize("����C��������","ActC","","number",pResults->m_nBinSwitchCount[2]);

    pXmlSierialize->xml_serialize("A�ද��ʱ��","TtripA","s","number",pResults->m_fTimeBinAct[0]);
    pXmlSierialize->xml_serialize("B�ද��ʱ��","TtripB","s","number",pResults->m_fTimeBinAct[1]);
    pXmlSierialize->xml_serialize("C�ද��ʱ��","TtripC","s","number",pResults->m_fTimeBinAct[2]);
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
