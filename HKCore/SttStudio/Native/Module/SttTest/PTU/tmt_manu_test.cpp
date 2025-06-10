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

void stt_xml_serialize_binary_out(tmt_BinaryOut *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("����1״̬","_Bout1","","DOutputState",pParas[0].nState);
	pXmlSierialize->xml_serialize("����2״̬","_Bout2","","DOutputState",pParas[1].nState);
	pXmlSierialize->xml_serialize("����3״̬","_Bout3","","DOutputState",pParas[2].nState);
	pXmlSierialize->xml_serialize("����4״̬","_Bout4","","DOutputState",pParas[3].nState);
	pXmlSierialize->xml_serialize("����5״̬","_Bout5","","DOutputState",pParas[4].nState);
	pXmlSierialize->xml_serialize("����6״̬","_Bout6","","DOutputState",pParas[5].nState);
	pXmlSierialize->xml_serialize("����7״̬","_Bout7","","DOutputState",pParas[6].nState);
	pXmlSierialize->xml_serialize("����8״̬","_Bout8","","DOutputState",pParas[7].nState);
}

void stt_xml_serialize_binary_in(tmt_BinaryIn *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("����Aѡ��","_BinSelectA","","BOOL",pParas[0].nSelect);
	pXmlSierialize->xml_serialize("����Bѡ��","_BinSelectB","","BOOL",pParas[1].nSelect);
	pXmlSierialize->xml_serialize("����Cѡ��","_BinSelectC","","BOOL",pParas[2].nSelect);
	pXmlSierialize->xml_serialize("����Rѡ��","_BinSelectR","","BOOL",pParas[3].nSelect);
	pXmlSierialize->xml_serialize("����aѡ��","_BinSelecta","","BOOL",pParas[4].nSelect);
	pXmlSierialize->xml_serialize("����bѡ��","_BinSelectb","","BOOL",pParas[5].nSelect);
	pXmlSierialize->xml_serialize("����cѡ��","_BinSelectc","","BOOL",pParas[6].nSelect);
	pXmlSierialize->xml_serialize("����rѡ��","_BinSelectr","","BOOL",pParas[7].nSelect);
}

void stt_xml_serialize_dc(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	int bDC = 0;
	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
	{
		pXmlSierialize->xml_serialize("�Ƿ���ֱ��ģʽ���", "bDC", "", "BOOL", bDC);
		pParas->setDC(bDC);
	}
	else if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_WRITE)
	{
		if (pParas->m_bDC)
		{
			bDC = 1;
		}
		pXmlSierialize->xml_serialize("�Ƿ���ֱ��ģʽ���", "bDC", "", "BOOL", bDC);
	}
}

void stt_xml_serialize_Aging(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	int bAging = 0;
	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
	{
		pXmlSierialize->xml_serialize("�Ƿ��ϻ�����", "bAging", "", "BOOL", bAging);
		pParas->m_bAging = bAging;
	}
	else if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_WRITE)
	{
		if (pParas->m_bAging)
		{
			bAging = 1;
		}
		pXmlSierialize->xml_serialize("�Ƿ��ϻ�����", "bAging", "", "BOOL", bAging);
	}
}

void stt_xml_serialize_Lock(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	int bLock = 0;
	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
	{
		pXmlSierialize->xml_serialize("�Ƿ�����", "_bLock", "", "BOOL", bLock);
		pParas->m_bLockChanged = bLock;
	}
	else if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_WRITE)
	{
		if (pParas->m_bLockChanged)
		{
			bLock = 1;
		}
		pXmlSierialize->xml_serialize("�Ƿ�����", "_bLock", "", "BOOL", bLock);
	}
}

void stt_xml_serialize_Auto(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	int bAuto = 0;
	if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_READ)
	{
		pXmlSierialize->xml_serialize("�Ƿ��Զ��ݱ�", "_bAuto", "", "BOOL", bAuto);
		pParas->m_bAuto = bAuto;
	}
	else if (pXmlSierialize->get_serialize_mode()==STT_XML_SERIALIZE_MODE_WRITE)
	{
		if (pParas->m_bAuto)
		{
			bAuto = 1;
		}
		pXmlSierialize->xml_serialize("�Ƿ��Զ��ݱ�", "_bAuto", "", "BOOL", bAuto);
	}
}

void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("Ua��ֵ","_Ua","V","number",pParas->m_uiVOL[0].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ua��λ","_UaPh","��","number",pParas->m_uiVOL[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("UaƵ��","_UaFre","Hz","number",pParas->m_uiVOL[0].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ub��ֵ","_Ub","V","number",pParas->m_uiVOL[1].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ub��λ","_UbPh","��","number",pParas->m_uiVOL[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("UbƵ��","_UbFre","Hz","number",pParas->m_uiVOL[1].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Uc��ֵ","_Uc","V","number",pParas->m_uiVOL[2].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Uc��λ","_UcPh","��","number",pParas->m_uiVOL[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("UcƵ��","_UcFre","Hz","number",pParas->m_uiVOL[2].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Uz��ֵ","_Uz","V","number",pParas->m_uiVOL[3].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Uz��λ","_UzPh","��","number",pParas->m_uiVOL[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("UzƵ��","_UzFre","Hz","number",pParas->m_uiVOL[3].Harm[1].fFreq);

	pXmlSierialize->xml_serialize("Ia��ֵ","_Ia","A","number",pParas->m_uiCUR[0].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ia��λ","_IaPh","��","number",pParas->m_uiCUR[0].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("IaƵ��","_IaFre","Hz","number",pParas->m_uiCUR[0].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ib��ֵ","_Ib","A","number",pParas->m_uiCUR[1].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ib��λ","_IbPh","��","number",pParas->m_uiCUR[1].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("IbƵ��","_IbFre","Hz","number",pParas->m_uiCUR[1].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("Ic��ֵ","_Ic","A","number",pParas->m_uiCUR[2].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("Ic��λ","_IcPh","��","number",pParas->m_uiCUR[2].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("IcƵ��","_IcFre","Hz","number",pParas->m_uiCUR[2].Harm[1].fFreq);
	pXmlSierialize->xml_serialize("I0��ֵ","_I0","A","number",pParas->m_uiCUR[3].Harm[1].fAmp);
	pXmlSierialize->xml_serialize("I0��λ","_I0Ph","��","number",pParas->m_uiCUR[3].Harm[1].fAngle);
	pXmlSierialize->xml_serialize("I0Ƶ��","_I0Fre","Hz","number",pParas->m_uiCUR[3].Harm[1].fFreq);

	pXmlSierialize->xml_serialize("������ʱ","fOverload","s","number",pParas->m_fOverloadDelaytime);
    pXmlSierialize->xml_serialize("����ʱ��", "OutputTime"," ","number",pParas->m_fOutPutTime);
	pXmlSierialize->xml_serialize("����ֱ������","fCurAux","mA","number",pParas->m_fCurAux);
	pXmlSierialize->xml_serialize("����ֱ����ѹ","fVolAux","V","number",pParas->m_fVolAux);
	
	pXmlSierialize->xml_serialize("�ݱ�ͨ��ѡ��","_GradientChSelect","","PsuGradientChannel",pParas->m_nGradientChSelect);
	pXmlSierialize->xml_serialize("�ݱ�����ѡ��","_GradientTpSelect","","PsuGradientType",pParas->m_nGradientTpSelect);
	pXmlSierialize->xml_serialize("�仯ģʽ","Mode","","UIVariateMode",pParas->m_manuGradient.nMode);
	pXmlSierialize->xml_serialize("�仯ʼֵ","Start","","number",pParas->m_manuGradient.fStart);
	pXmlSierialize->xml_serialize("�仯��ֵ","End","","number",pParas->m_manuGradient.fEnd);
	pXmlSierialize->xml_serialize("�仯����","Step","","number",pParas->m_manuGradient.fStep);
	pXmlSierialize->xml_serialize("ÿ��ʱ��","StepTime","","number",pParas->m_manuGradient.fStepTime);
	pXmlSierialize->xml_serialize("������ʱ","TrigDelay","","number",pParas->m_manuGradient.fTrigDelay);
	pXmlSierialize->xml_serialize("�仯г������","Harm","","number",pParas->m_manuGradient.nHarmIndex);

	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
	stt_xml_serialize_binary_out(pParas->m_binOut,pXmlSierialize);
	stt_xml_serialize_dc(pParas,pXmlSierialize);
	stt_xml_serialize_Aging(pParas,pXmlSierialize);
	stt_xml_serialize_Lock(pParas,pXmlSierialize);
	stt_xml_serialize_Auto(pParas,pXmlSierialize);
}

void stt_xml_serialize(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{

}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_manu_test.h"
#include"../../../Module/API/GlobalConfigApi.h"
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
