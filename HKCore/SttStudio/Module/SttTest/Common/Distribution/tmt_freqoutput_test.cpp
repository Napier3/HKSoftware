#include "stdafx.h"
#include "tmt_freqoutput_test.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              
#endif


void stt_init_paras( tmt_FreqOutputParas *pParas )
{
	memset(&pParas, 0, sizeof(tmt_FreqOutputParas));
	pParas->init();
}


void stt_xml_serialize(tmt_FreqOutputParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize(pParas, pXmlSierialize, MAX_VOLTAGE_COUNT, MAX_CURRENT_COUNT);
}

void stt_xml_serialize_channel(tmt_FreqOutputChannel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize)
{
	CString strID;
	strID.Format(_T("%select"), pszID);
	pXmlSierialize->xml_serialize("ʹ��", strID.GetString(), "", "number", pChannel->m_nSelect);
	strID.Format(_T("%smag"), pszID);
	pXmlSierialize->xml_serialize_sys_pata("��ֵ", strID.GetString(), "V", "number", pChannel->m_fAmp,STT_XML_SERIALIZE_SYS_PARA_ID_VNom);
	strID.Format(_T("%sang"), pszID);
	pXmlSierialize->xml_serialize("��λ", strID.GetString(), "", "float",  pChannel->m_fAngle);
}

void stt_xml_serialize(tmt_FreqOutputParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
{
	CString strID;

	if(nVolRsNum > MAX_VOLTAGE_COUNT)
	{
		nVolRsNum = MAX_VOLTAGE_COUNT;
	}

	for(int nIndex = 0; nIndex < nVolRsNum; nIndex++)
	{
		strID.Format(_T("U%d"),nIndex+1);
		stt_xml_serialize_channel(&pParas->m_uiVOL[nIndex], strID.GetString(),pXmlSierialize);
	}

	if(nCurRsNum > MAX_CURRENT_COUNT)
	{
		nCurRsNum = MAX_CURRENT_COUNT;
	}

	for(int nIndex = 0; nIndex < nCurRsNum; nIndex++)
	{
		strID.Format(_T("I%d"), nIndex + 1);
		stt_xml_serialize_channel(&pParas->m_uiCUR[nIndex], strID.GetString(),pXmlSierialize);
	}


	pXmlSierialize->xml_serialize("�������","OutPutType","","number",pParas->m_nOutPutType);
	pXmlSierialize->xml_serialize("�����ź�����","PulseType","","number",pParas->m_nPulseType);
	pXmlSierialize->xml_serialize("������","PulseWidth","","number",pParas->m_fPulseWidth);
	pXmlSierialize->xml_serialize("���ֵ","PeakValueType","","number",pParas->m_nPeakValueType);
	pXmlSierialize->xml_serialize("Idc1","Idc1","","number",pParas->m_nIdc[0]);
	pXmlSierialize->xml_serialize("Idc2","Idc2","","number",pParas->m_nIdc[1]);
	pXmlSierialize->xml_serialize("״̬��", "StateCount", "", "number", pParas->m_nStateCount);
	long nStateCount = pParas->m_nStateCount;

	for(int nIndex = 0; nIndex < nStateCount; nIndex++)
	{
		strID.Format(_T("State%d"), nIndex);
		stt_xml_serialize_freqchangePoint(&pParas->m_oFreqOutputPara[nIndex], strID.GetString(),pXmlSierialize);
	}
	
	
	CSttXmlSerializeBase *pFileSerialize = pXmlSierialize->xml_serialize("�½��ļ�", "NewFile", "", stt_ParaGroupKey());
	if(pFileSerialize == NULL)
	{
		return;
	}
	if(!stt_xml_serialize_is_write(pFileSerialize))//���·�
	{		
		stt_xml_serialize_newfile(&pParas->m_oFreqOutputNewFile,pFileSerialize);
	}
}

void stt_state_paras_delete(tmt_FreqOutputParas *pParas, int nIndex)
{
	if (nIndex >= pParas->m_nStateCount || nIndex < 0)
	{
		return;
	}

	for (int i = nIndex; i < pParas->m_nStateCount; i++)
	{
		pParas->m_oFreqOutputPara[i] = pParas->m_oFreqOutputPara[i + 1];
	}
	pParas->m_nStateCount--;
}


void stt_xml_serialize_freqchangePoint(tmt_FreqOutputPara *pParas, const char *pszID,CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pXmlSerializeBase = pXmlSierialize->xml_serialize(pszID, pszID, "", stt_ParaGroupKey());

	if (pXmlSerializeBase == NULL)
	{
		return;
	}
	pXmlSerializeBase->xml_serialize("����ʱ��", "HoldTime", "", "number", pParas->m_fHoldTime);
	pXmlSerializeBase->xml_serialize("����Ƶ��", "Fre", "", "number", pParas->m_fFrequency);
	pXmlSerializeBase->xml_serialize("ת������Ƶ��", "PluseFre", "", "number", pParas->m_fPluseFrequency);
	pXmlSerializeBase->xml_serialize("ֱ������", "CurrentDc", "", "number", pParas->m_fDCCurrent);
}


void stt_xml_serialize_newfile( tmt_FreqOutputNewFile *pParas, CSttXmlSerializeBase *pXmlSierialize )
{
	pXmlSierialize->xml_serialize("�½�����","SetType","","number",pParas->m_nSetType);
	pXmlSierialize->xml_serialize("����","RowCount","","number",pParas->m_nRowCount);
	pXmlSierialize->xml_serialize("Ĭ�����ó���ʱ��","OutPutTime","","number",pParas->m_fOutPutTime);
	pXmlSierialize->xml_serialize("Ĭ������Ƶ��","Frequency","","number",pParas->m_fFrequency);
	pXmlSierialize->xml_serialize("Ĭ������ֱ������","DCCurrent","","number",pParas->m_fDCCurrent);
	pXmlSierialize->xml_serialize("Ĭ��ת������Ƶ��","FreqPluse","","number",pParas->m_fFreqPluse);

	pXmlSierialize->xml_serialize("Ƶ�ʵݱ�Ƶ��ʼֵ","StartFreq","","number",pParas->m_fStartFreq);
	pXmlSierialize->xml_serialize("Ƶ�ʵݱ�Ƶ����ֵ","EndFreq","","number",pParas->m_fEndFreq);
	pXmlSierialize->xml_serialize("Ƶ�ʵݱ�Ƶ�ʲ���","StepFreq","","number",pParas->m_fStepFreq);
	pXmlSierialize->xml_serialize("Ƶ�ʵݱ�Ƶ�ʱ仯��ʽ","FreqChangeMode","","number",pParas->m_nFreqChangeMode);
	pXmlSierialize->xml_serialize("Ƶ�ʵݱ�Ƶ�ʳ���ʱ��","FreqOutPutTime","","number",pParas->m_fFreqOutPutTime);

	pXmlSierialize->xml_serialize("ת������Ƶ�ʵݱ�Ƶ��ʼֵ","StartFreqPluse","","number",pParas->m_fStartFreqPluse);
	pXmlSierialize->xml_serialize("ת������Ƶ�ʵݱ�Ƶ����ֵ","EndFreqPluse","","number",pParas->m_fEndFreqPluse);
	pXmlSierialize->xml_serialize("ת������Ƶ�ʵݱ�Ƶ�ʲ���","StepFreqPluse","","number",pParas->m_fStepFreqPluse);
	pXmlSierialize->xml_serialize("ת������Ƶ�ʵݱ�Ƶ�ʱ仯��ʽ","FreqChangeModePluse","","number",pParas->m_nFreqChangeModePluse);
	pXmlSierialize->xml_serialize("ת������Ƶ�ʵݱ�Ƶ�ʳ���ʱ��","FreqOutPutTimePluse","","number",pParas->m_fFreqOutPutTimePluse);

	pXmlSierialize->xml_serialize("ֱ�������ݱ�ʼֵ","StartCurrent","","number",pParas->m_fStartCurrent);
	pXmlSierialize->xml_serialize("ֱ�������ݱ���ֵ","EndCurrent","","number",pParas->m_fEndCurrent);
	pXmlSierialize->xml_serialize("ֱ�������ݱ䲽��","StepCurrent","","number",pParas->m_fStepCurrent);
	pXmlSierialize->xml_serialize("ֱ�������ݱ�仯��ʽ","CurrentChangeMode","","number",pParas->m_nCurrentChangeMode);
	pXmlSierialize->xml_serialize("ֱ�������ݱ����ʱ��","CurrentOutPutTime","","number",pParas->m_fCurrentOutPutTime);
}

#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_FreqOutputTest()
{
// 	tmt_FreqOutputTest oFreqOutputTest;
// 	oFreqOutputTest.init();
// 	CSttXmlSerializeTool oSttXmlSerializeTool;
// 	CSttTestCmd oSttTestCmd;
// 	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
// 	pMacro->GetParas();
// 	pMacro->GetResults();
// 	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
// 	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
// 	stt_xml_serialize(&oFreqOutputTest.m_oFreqOutputParas, pMacroParas);
// 	CString strXMLPath;
// 	strXMLPath = _P_GetConfigPath();
// 	strXMLPath += ("FreqOutputTestDemo.xml");
// 	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

CSttXmlSerializeBase *stt_xml_serialize(tmt_FreqOutputTest *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSierialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if(pXmlParas  != NULL)
	{
		stt_xml_serialize(&pParas->m_oFreqOutputParas, pXmlParas, nVolRsNum, nCurRsNum);
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSierialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if(pXmlResults  != NULL)
	{
		//stt_xml_serialize(&pParas->m_oFreqOutputResult, pXmlResults);
	}

	return pXmlParas;
}
